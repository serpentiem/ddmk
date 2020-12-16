// @Todo: Update byte8 * addr philosophy.
// @Todo: Move helpers.
// @Todo: Eradicate last memsets and memcpys.
// @Todo: Merge File, Log and Memory when doing the Windows module.

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

SYSTEM_INFO systemInfo = {};

export template <typename T>
T Align
(
	T & pos,
	T boundary,
	byte8 * addr = 0,
	byte8 pad = 0
)
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
	}

	return remainder;
}

export byte8 * Alloc
(
	uint32 size,
	byte8 * dest = 0
)
{
	byte8 * addr = 0;
	byte32 error = 0;

	SetLastError(0);

	addr = reinterpret_cast<byte8 *>
	(
		VirtualAlloc
		(
			dest,
			size,
			MEM_COMMIT | MEM_RESERVE,
			PAGE_EXECUTE_READWRITE
		)
	);

	error = GetLastError();

	if (!addr)
	{
		Log("VirtualAlloc failed. %X", error);
	}

	return addr;
}

export byte8 * AllocEx
(
	uint32 size,
	uint64 start,
	uint64 end
)
{
	if constexpr (debug)
	{
		LogFunction();

		Log("size  %X", size);
		Log("start %llX", start);
		Log("end   %llX", end);
	}

	byte8 * addr = 0;

	auto pos = start;

	MEMORY_BASIC_INFORMATION mbi = {};
	bool match = false;
	byte32 error = 0;

	do
	{
		SetLastError(0);

		if
		(
			VirtualQuery
			(
				reinterpret_cast<void *>(pos),
				&mbi,
				sizeof(mbi)
			) == 0
		)
		{
			error = GetLastError();

			Log("VirtualQuery failed. %X", error);
		}

		if
		(
			(mbi.RegionSize >= size) &&
			(mbi.State == MEM_FREE)
		)
		{
			if constexpr (debug)
			{
				Log("pos        %llX", pos);
				Log("regionSize %llX", mbi.RegionSize);
				Log("state      %X", mbi.State);
			}

			auto remainder = Align<uint64>(pos, systemInfo.dwAllocationGranularity);
			if (!remainder)
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

	addr = Alloc(size, addr);

	SetLastError(0);

	if
	(
		VirtualQuery
		(
			addr,
			&mbi,
			sizeof(mbi)
		) == 0
	)
	{
		error = GetLastError();

		Log("VirtualQuery failed. %X", error);
	}

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

export struct MemoryData
{
	byte8 * dataAddr;
	uint32 pos;
	uint32 end;
	uint32 count;

	bool Init(uint32 dataSize);
};

bool MemoryData::Init(uint32 dataSize)
{
	dataAddr = HighAlloc(dataSize);
	if (!dataAddr)
	{
		Log("HighAlloc failed.");

		return false;
	}

	memset(dataAddr, 0xCC, dataSize);

	end = dataSize;

	return true;
}

export MemoryData memoryData = {};

// @Research: Prefer void *.
export struct ProtectionHelper
{
	struct Metadata
	{
		byte8 * addr;
		uint32 size;
		byte32 protection;
	};

	Metadata * metadataAddr;
	uint32 count;

	bool Init(uint32 metadataSize);

	void Push
	(
		byte8 * addr,
		uint32 size
	);

	void Pop();
};

bool ProtectionHelper::Init(uint32 metadataSize)
{
	metadataAddr = reinterpret_cast<Metadata *>(HighAlloc(metadataSize));
	if (!metadataAddr)
	{
		Log("HighAlloc failed.");

		return false;
	}

	return true;
}

void ProtectionHelper::Push
(
	byte8 * addr,
	uint32 size
)
{
	if constexpr (debug)
	{
		LogFunction();

		Log("count %u", count);
	}

	auto & metadata = metadataAddr[count];

	byte32 error = 0;
	byte32 protection = 0;

	SetLastError(0);

	if
	(
		VirtualProtect
		(
			addr,
			size,
			PAGE_EXECUTE_READWRITE,
			&protection
		) == 0
	)
	{
		error = GetLastError();

		Log("VirtualProtect failed. %X", error);
	}

	metadata.addr = addr;
	metadata.size = size;
	metadata.protection = protection;

	if constexpr (debug)
	{
		Log("metadata.addr       %llX", metadata.addr);
		Log("metadata.size       %u", metadata.size);
		Log("metadata.protection %X", metadata.protection);
	}

	count++;
}

void ProtectionHelper::Pop()
{
	if constexpr (debug)
	{
		LogFunction();

		Log("count %u", count);
	}

	if (count < 1)
	{
		return;
	}

	auto & metadata = metadataAddr[(count - 1)];

	byte32 error = 0;
	byte32 protection = 0;

	SetLastError(0);

	if
	(
		VirtualProtect
		(
			metadata.addr,
			metadata.size,
			metadata.protection,
			&protection
		) == 0
	)
	{
		error = GetLastError();

		Log("VirtualProtect failed. %X", error);
	}

	if constexpr (debug)
	{
		Log("metadata.addr       %llX", metadata.addr);
		Log("metadata.size       %u", metadata.size);
		Log("metadata.protection %X", metadata.protection);
	}

	metadata.addr = 0;
	metadata.size = 0;
	metadata.protection = 0;

	count--;
}

export ProtectionHelper protectionHelper = {};

export enum
{
	MemoryFlags_VirtualProtectDestination = 1 << 0,
	MemoryFlags_VirtualProtectSource      = 1 << 1,
};

export void SetMemory
(
	void * addr,
	byte8 value,
	uint32 size,
	byte32 flags = 0
)
{
	if (flags & MemoryFlags_VirtualProtectDestination)
	{
		protectionHelper.Push(reinterpret_cast<byte8 *>(addr), size);
	}

	memset
	(
		addr,
		value,
		size
	);

	if (flags & MemoryFlags_VirtualProtectDestination)
	{
		protectionHelper.Pop();
	}
}

export void CopyMemory
(
	void * destination,
	const void * source,
	uint32 size,
	byte32 flags = 0
)
{
	if (flags & MemoryFlags_VirtualProtectDestination)
	{
		protectionHelper.Push(reinterpret_cast<byte8 *>(destination), size);
	}

	if (flags & MemoryFlags_VirtualProtectSource)
	{
		protectionHelper.Push(reinterpret_cast<byte8 *>(const_cast<void *>(source)), size);
	}

	memcpy
	(
		destination,
		source,
		size
	);

	if (flags & MemoryFlags_VirtualProtectSource)
	{
		protectionHelper.Pop();
	}

	if (flags & MemoryFlags_VirtualProtectDestination)
	{
		protectionHelper.Pop();
	}
}

export struct BackupHelper
{
	// @Research: addr first, off last.
	struct Metadata
	{
		uint32 off;
		uint32 size;
		byte8 * addr;
	};

	byte8 * dataAddr;
	uint32 pos;
	uint32 end;
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

	end = dataSize;

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
	CopyMemory
	(
		(dataAddr + pos),
		addr,
		size,
		MemoryFlags_VirtualProtectSource
	);

	auto & metadata = metadataAddr[count];

	metadata.off = pos;
	metadata.size = size;
	metadata.addr = addr;

	pos += size;

	count++;
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
			(dataAddr + metadata.off),
			metadata.size,
			MemoryFlags_VirtualProtectDestination
		);

		return;
	}

	auto off = static_cast<uint32>(addr - appBaseAddr);

	Log("%s failed.", FUNC_NAME);

	Log("No Match dmc3.exe+%X", off);
}

export BackupHelper backupHelper = {};

export template <typename T>
void Write
(
	void   * addr,
	T        value,
	uint32   padSize  = 0,
	byte8    padValue = 0x90
)
{
	constexpr uint32 size = sizeof(T);

	protectionHelper.Push(reinterpret_cast<byte8 *>(addr), size);

	*reinterpret_cast<T *>(addr) = value;

	if (padSize)
	{
		SetMemory
		(
			(reinterpret_cast<byte8 *>(addr) + size),
			padValue,
			padSize
		);
	}

	protectionHelper.Pop();
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
	protectionHelper.Push(addr, (size + padSize));

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
		SetMemory
		(
			(addr + size),
			padValue,
			padSize
		);
	}

	protectionHelper.Pop();
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

export struct Function
{
	byte8 *  addr;
	byte8 *  sect0;
	byte8 *  sect1;
	byte8 *  sect2;
	byte8 ** cache;
};

// @Research: Add xmm register saving.
export Function CreateFunction
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
	Function func = {};
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

	Align<uint32>(memoryData.pos, 0x10);

	func.addr = (memoryData.dataAddr + memoryData.pos);

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

	memoryData.pos += pos;

	if (cacheSize)
	{
		Align<uint32>(memoryData.pos, 0x10);

		func.cache = reinterpret_cast<byte8 **>(memoryData.dataAddr + memoryData.pos);

		memoryData.pos += cacheSize;
	}

	return func;
}

export bool Core_Memory_Init()
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

	GetSystemInfo(&systemInfo);

	return true;
}
