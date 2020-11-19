module;
#include "Includes.h"
export module Core_Memory;

import Core_Log;

#define debug false

export enum REGISTER
{
	RAX,
	RCX,
	RDX,
	RBX,
	RSP,
	RBP,
	RSI,
	RDI,
	R8,
	R9,
	R10,
	R11,
	R12,
	R13,
	R14,
	R15,
	MAX_REGISTER,
};

export byte8  * appBaseAddr = 0;
export uint32   appSize     = 0;
export HWND     appWindow   = 0;

SYSTEM_INFO   systemInfo = {};
byte8       * g_addr     = 0;
uint32        g_pos      = 0;

export template <typename T>
bool Align(T & pos, T boundary, byte8 * addr = 0, byte8 pad = 0)
{
	T remainder = (pos % boundary);
	if (remainder)
	{
		T size = (boundary - remainder);
		if (addr)
		{
			memset((addr + pos), pad, size);
		}
		pos += size;
		return true;
	}
	return false;
}

export byte8 * Alloc(uint32 size)
{
	byte8 * addr = 0;
	byte32 error = 0;

	SetLastError(0);
	addr = reinterpret_cast<byte8 *>(VirtualAlloc(0, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE));
	error = GetLastError();
	if (!addr)
	{
		Log("VirtualAlloc failed. %X", error);
		return 0;
	}

	return addr;
}

export byte8 * AllocEx
(
	uint32 size,
	uint64 pos,
	uint64 end
)
{
	MEMORY_BASIC_INFORMATION mbi = {};
	bool match = false;
	byte8 * addr = 0;
	byte32 error = 0;

	if constexpr (debug)
	{
		LogFunction();
		Log("size %X", size);
		Log("pos  %llX", pos);
		Log("end  %llX", end);
	}

	do
	{
		VirtualQuery(reinterpret_cast<void *>(pos), &mbi, sizeof(mbi));
		if ((mbi.RegionSize >= size) && (mbi.State == MEM_FREE))
		{
			if constexpr (debug)
			{
				Log("pos        %llX", pos           );
				Log("regionSize %llX", mbi.RegionSize);
				Log("state      %X"  , mbi.State     );
			}
			auto result = Align<uint64>(pos, systemInfo.dwAllocationGranularity);
			if (!result)
			{
				match = true;
				break;
			}
			continue;
		}
		pos += mbi.RegionSize;
	}
	while (pos < end);

	if (!match)
	{
		return 0;
	}

	addr = reinterpret_cast<byte8 *>(mbi.BaseAddress);

	SetLastError(0);
	addr = reinterpret_cast<byte8 *>(VirtualAlloc(addr, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE));
	error = GetLastError();
	if (!addr)
	{
		Log("VirtualAlloc failed. %X", error);
		return 0;
	}

	VirtualQuery(addr, &mbi, sizeof(mbi));

	if constexpr (debug)
	{
		Log("addr  %llX", addr);
		Log("state %X", mbi.State);
	}

	return addr;
}

export inline byte8 * LowAlloc(uint32 size)
{
	return AllocEx
	(
		size,
		0x10000,
		0x7FFFFFFF
	);
}

export inline byte8 * HighAlloc(uint32 size)
{
	return AllocEx
	(
		size,
		reinterpret_cast<uint64>(appBaseAddr + appSize),
		reinterpret_cast<uint64>(appBaseAddr + 0x7FFFFFFF)
	);
}

// @Todo: Update.
export template <typename T>
void Write
(
	//byte8  * addr,
	void   * addr,
	T        value,
	uint32   padSize  = 0,
	byte8    padValue = 0x90
)
{
	constexpr uint32 size = sizeof(T);
	byte32 protection = 0;
	VirtualProtect(addr, (size + padSize), PAGE_EXECUTE_READWRITE, &protection);
	{
		*(T *)addr = value;
		if (padSize)
		{
			//memset((addr + size), padValue, padSize);
			memset((reinterpret_cast<byte8 *>(addr) + size), padValue, padSize);
		}
	}
	VirtualProtect(addr, (size + padSize), protection, &protection);
}

export void WriteAddress
(
	byte8  * addr,
	void   * dest,
	uint32   size,
	byte8    value    = 0,
	uint32   padSize  = 0,
	byte8    padValue = 0x90,
	uint32   off      = 0
)
{
	byte32 protection = 0;

	VirtualProtect(addr, (size + padSize), PAGE_EXECUTE_READWRITE, &protection);

	if (value)
	{
		addr[0] = value;
	}

	if (size == 2)
	{
		*reinterpret_cast<int8 *>(addr + (size - 1 - off)) = static_cast<int8>(reinterpret_cast<byte8 *>(dest) - addr - size);
	}
	else
	{
		*reinterpret_cast<int32 *>(addr + (size - 4 - off)) = static_cast<int32>(reinterpret_cast<byte8 *>(dest) - addr - size);
	}

	if (padSize)
	{
		memset((addr + size), padValue, padSize);
	}

	VirtualProtect(addr, (size + padSize), protection, &protection);
}

export inline void WriteCall
(
	byte8  * addr,
	void   * dest,
	uint32   padSize  = 0,
	byte8    padValue = 0x90
)
{
	WriteAddress(addr, dest, 5, 0xE8, padSize, padValue);
}

export inline void WriteJump
(
	byte8  * addr,
	void   * dest,
	uint32   padSize  = 0,
	byte8    padValue = 0x90
)
{
	WriteAddress(addr, dest, 5, 0xE9, padSize, padValue);
}

// @Todo: SetMemory.
export void vp_memset
(
	void   * addr,
	byte8    value,
	uint32   size
)
{
	byte32 protection = 0;
	VirtualProtect(addr, size, PAGE_EXECUTE_READWRITE, &protection);
	{
		memset(addr, value, size);
	}
	VirtualProtect(addr, size, protection, &protection);
}

// @Todo: Mark obsolete.
export void vp_memcpy
(
	void       * dest,
	const void * addr,
	uint32       size
)
{
	byte32 protection = 0;
	VirtualProtect(dest, size, PAGE_EXECUTE_READWRITE, &protection);
	{
		memcpy(dest, addr, size);
	}
	VirtualProtect(dest, size, protection, &protection);
}

export enum
{
	CopyMemoryFlags_VirtualProtectDestination = 1 << 0,
	CopyMemoryFlags_VirtualProtectSource      = 1 << 1,
};

export void CopyMemory
(
	void * destination,
	const void * source,
	uint32 size,
	byte32 flags = 0
)
{
	byte32 protectionDestination = 0;
	byte32 protectionSource = 0;

	if (flags & CopyMemoryFlags_VirtualProtectDestination)
	{
		VirtualProtect
		(
			destination,
			size,
			PAGE_EXECUTE_READWRITE,
			&protectionDestination
		);
	}

	if (flags & CopyMemoryFlags_VirtualProtectSource)
	{
		VirtualProtect
		(
			const_cast<void *>(source),
			size,
			PAGE_EXECUTE_READWRITE,
			&protectionSource
		);
	}

	memcpy
	(
		destination,
		source,
		size
	);

	if (flags & CopyMemoryFlags_VirtualProtectDestination)
	{
		VirtualProtect
		(
			destination,
			size,
			protectionDestination,
			&protectionDestination
		);
	}

	if (flags & CopyMemoryFlags_VirtualProtectSource)
	{
		VirtualProtect
		(
			const_cast<void *>(source),
			size,
			protectionSource,
			&protectionSource
		);
	}
}

export struct BackupHelper
{
	struct Metadata
	{
		byte8 * addr;
		uint32 size;
		byte8 * dataAddr;
	};

	byte8 * dataAddr;
	uint32 pos;
	Metadata * metadataAddr;
	uint32 count;

	bool Init
	(
		uint32 dataSize,
		uint32 metadataSize
	);
	void Save
	(
		byte8 * addr,
		uint32 size
	);
	void Restore
	(
		byte8 * addr
	);
};

bool BackupHelper::Init
(
	uint32 dataSize,
	uint32 metadataSize
)
{
	dataAddr = HighAlloc(dataSize);
	if (!dataAddr)
	{
		Log("HighAlloc failed.");

		return false;
	}

	metadataAddr = reinterpret_cast<Metadata *>(HighAlloc(metadataSize));
	if (!metadataAddr)
	{
		Log("HighAlloc failed.");

		return false;
	}

	return true;
}

void BackupHelper::Save
(
	byte8 * addr,
	uint32 size
)
{
	byte32 protection = 0;

	VirtualProtect
	(
		addr,
		size,
		PAGE_EXECUTE_READWRITE,
		&protection
	);

	CopyMemory
	(
		(dataAddr + pos),
		addr,
		size
	);

	auto & metadata = metadataAddr[count];

	metadata.addr = addr;
	metadata.size = size;
	metadata.dataAddr = (dataAddr + pos);

	pos += size;

	count++;

	VirtualProtect
	(
		addr,
		size,
		protection,
		&protection
	);
}

void BackupHelper::Restore(byte8 * addr)
{
	for_all(uint32, metadataIndex, count)
	{
		auto & metadata = metadataAddr[metadataIndex];

		if (metadata.addr != addr)
		{
			continue;
		}

		CopyMemory
		(
			metadata.addr,
			metadata.dataAddr,
			metadata.size,
			CopyMemoryFlags_VirtualProtectDestination
		);

		return;
	}

	auto off = static_cast<uint32>(addr - appBaseAddr);

	Log("%s failed.", FUNC_NAME);

	Log("No Match dmc3.exe+%X", off);
}

export BackupHelper backupHelper = {};

export struct FunctionData
{
	byte8 *  addr;
	byte8 *  sect0;
	byte8 *  sect1;
	byte8 *  sect2;
	byte8 ** cache;
};

// @Research: Add xmm register saving.
export FunctionData CreateFunction
(
	void   * funcAddr      = 0,
	byte8  * jumpAddr      = 0,
	bool     saveRegisters = true,
	bool     noResult      = true,
	uint32   size0         = 0,
	uint32   size1         = 0,
	uint32   size2         = 0,
	uint32   cacheSize     = 0,
	uint32   count         = 0,
	bool     noReturn      = false
)
{
	FunctionData func = {};
	uint32       pos  = 0;

	auto Feed = [&]
	(
		const byte8 * buffer,
		uint32 bufferSize,
		bool adjustPosition = true
	)
	{
		memcpy
		(
			(func.addr + pos),
			buffer,
			bufferSize
		);

		if (!adjustPosition)
		{
			return;
		}

		pos += bufferSize;
	};

	Align<uint32>(g_pos, 0x10);

	func.addr = (g_addr + g_pos);

	func.sect0 = (func.addr + pos);
	pos += size0;

	if (saveRegisters)
	{
		if (noResult)
		{
			constexpr byte8 buffer[] =
			{
				0x50, // push rax
			};
			Feed(buffer, sizeof(buffer));
		}

		if (count)
		{
			if (noResult)
			{
				constexpr byte8 buffer[] =
				{
					0x48, 0x8D, 0x44, 0x24, 0x08, // lea rax,[rsp+08]
				};
				Feed(buffer, sizeof(buffer));
			}
			else
			{
				constexpr byte8 buffer[] =
				{
					0x48, 0x8B, 0xC4, // mov rax,rsp
				};
				Feed(buffer, sizeof(buffer));
			}
		}

		{
			constexpr byte8 buffer[] =
			{
				0x51,                   // push rcx
				0x52,                   // push rdx
				0x53,                   // push rbx
				0x54,                   // push rsp
				0x55,                   // push rbp
				0x56,                   // push rsi
				0x57,                   // push rdi
				0x41, 0x50,             // push r8
				0x41, 0x51,             // push r9
				0x41, 0x52,             // push r10
				0x41, 0x53,             // push r11
				0x41, 0x54,             // push r12
				0x41, 0x55,             // push r13
				0x41, 0x56,             // push r14
				0x41, 0x57,             // push r15
				0x9C,                   // pushfq
				0x48, 0x8B, 0xEC,       // mov rbp,rsp
			};
			Feed(buffer, sizeof(buffer));
		}

		if (count)
		{
			constexpr byte8 buffer[] =
			{
				0x48, 0x81, 0xEC, 0x20, 0x00, 0x00, 0x00, // sub rsp,00000020
			};
			Feed(buffer, sizeof(buffer), false);
			*reinterpret_cast<uint32 *>(func.addr + pos + 3) += (count * 8);
			pos += sizeof(buffer);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0x48, 0x83, 0xEC, 0x20, // sub rsp,20
			};
			Feed(buffer, sizeof(buffer));
		}

		{
			constexpr byte8 buffer[] =
			{
				0x40, 0x80, 0xE4, 0xF0, // and spl,F0
			};
			Feed(buffer, sizeof(buffer));
		}

		if (count)
		{
			constexpr byte8 buffer[] =
			{
				0x51,                         // push rcx
				0x56,                         // push rsi
				0x57,                         // push rdi
				0xB9, 0x00, 0x00, 0x00, 0x00, // mov ecx
				0x48, 0x8D, 0x70, 0x28,       // lea rsi,[rax+28] return addr + shadow space
				0x48, 0x8D, 0x7C, 0x24, 0x38, // lea rdi,[rsp+38] rdi + rsi + rcx + shadow space
				0xF3, 0x48, 0xA5,             // repe movsq
				0x5F,                         // pop rdi
				0x5E,                         // pop rsi
				0x59,                         // pop rcx
			};
			Feed(buffer, sizeof(buffer), false);
			*reinterpret_cast<uint32 *>(func.addr + pos + 4) = count;
			pos += sizeof(buffer);
		}
	}

	func.sect1 = (func.addr + pos);
	pos += size1;

	if (funcAddr)
	{
		constexpr byte8 buffer[] =
		{
			0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rax
			0xFF, 0xD0,                                                 // call rax
		};
		Feed(buffer, sizeof(buffer), false);
		*reinterpret_cast<void **>(func.addr + pos + 2) = funcAddr;
		pos += sizeof(buffer);
	}

	if (saveRegisters)
	{
		constexpr byte8 buffer[] =
		{
			0x48, 0x8B, 0xE5, // mov rsp,rbp
			0x9D,             // popfq
			0x41, 0x5F,       // pop r15
			0x41, 0x5E,       // pop r14
			0x41, 0x5D,       // pop r13
			0x41, 0x5C,       // pop r12
			0x41, 0x5B,       // pop r11
			0x41, 0x5A,       // pop r10
			0x41, 0x59,       // pop r9
			0x41, 0x58,       // pop r8
			0x5F,             // pop rdi
			0x5E,             // pop rsi
			0x5D,             // pop rbp
			0x5C,             // pop rsp
			0x5B,             // pop rbx
			0x5A,             // pop rdx
			0x59,             // pop rcx
		};
		Feed(buffer, sizeof(buffer));

		if (noResult)
		{
			constexpr byte8 buffer[] =
			{
				0x58, // pop rax
			};
			Feed(buffer, sizeof(buffer));
		}
	}

	func.sect2 = (func.addr + pos);
	pos += size2;

	if (jumpAddr)
	{
		WriteJump((func.addr + pos), jumpAddr);

		pos += 5;
	}
	else
	{
		if (!noReturn)
		{
			constexpr byte8 buffer[] =
			{
				0xC3, // ret
			};
			Feed(buffer, sizeof(buffer));
		}
	}

	g_pos += pos;

	if (cacheSize)
	{
		Align<uint32>(g_pos, 0x10);

		func.cache = reinterpret_cast<byte8 **>(g_addr + g_pos);

		g_pos += cacheSize;
	}

	return func;
}

// void Compare
// (
// 	byte8 * addr,
// 	const byte8 * addr2,
// 	uint32 size
// )
// {
// 	bool mismatch = false;

// 	byte32 protection = 0;

// 	VirtualProtect
// 	(
// 		addr,
// 		size,
// 		PAGE_EXECUTE_READWRITE,
// 		&protection
// 	);

// 	for_all(uint32, index, size)
// 	{
// 		if (addr[index] != addr2[index])
// 		{
// 			mismatch = true;

// 			break;
// 		}
// 	}

// 	if (mismatch)
// 	{
// 		char buffer[512];
// 		uint32 pos;

// 		auto off = static_cast<uint32>(addr - appBaseAddr);

// 		snprintf
// 		(
// 			buffer,
// 			sizeof(buffer),
// 			"Data Mismatch dmc3.exe+%X",
// 			off
// 		);

// 		Log(buffer);

// 		snprintf
// 		(
// 			buffer,
// 			sizeof(buffer),
// 			"app"
// 		);

// 		pos = 3;

// 		for_all(uint32, index, size)
// 		{
// 			snprintf
// 			(
// 				(buffer + pos),
// 				(sizeof(buffer) - pos),
// 				" %02X",
// 				addr[index]
// 			);

// 			pos += 3;
// 		}

// 		Log(buffer);

// 		snprintf
// 		(
// 			buffer,
// 			sizeof(buffer),
// 			"mod"
// 		);

// 		pos = 3;

// 		for_all(uint32, index, size)
// 		{
// 			snprintf
// 			(
// 				(buffer + pos),
// 				(sizeof(buffer) - pos),
// 				" %02X",
// 				addr2[index]
// 			);

// 			pos += 3;
// 		}

// 		Log(buffer);

// 		MessageBoxA
// 		(
// 			0,
// 			"Data Mismatch",
// 			0,
// 			MB_ICONERROR
// 		);
// 	}

// 	VirtualProtect
// 	(
// 		addr,
// 		size,
// 		protection,
// 		&protection
// 	);
// }

export bool Core_Memory_Init(uint32 size = 0)
{
	LogFunction();

	MODULEENTRY32 moduleEntry = {};
	HANDLE snapshot = 0;

	moduleEntry.dwSize = sizeof(MODULEENTRY32);
	snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, 0);
	Module32First(snapshot, &moduleEntry);

	appBaseAddr = moduleEntry.modBaseAddr;
	appSize = moduleEntry.modBaseSize;

	Log("%u %s", moduleEntry.th32ProcessID, moduleEntry.szModule);

	Log("appStart %llX", appBaseAddr);
	Log("appEnd   %llX", (appBaseAddr + appSize));

	if (!size)
	{
		return true;
	}

	GetSystemInfo(&systemInfo);

	g_addr = HighAlloc(size);
	if (!g_addr)
	{
		Log("HighAlloc failed.");
		return false;
	}

	memset(g_addr, 0xCC, size);

	return true;
}
