#include "Memory.h"

constexpr bool debug = false;

byte8  * appBaseAddr = 0;
uint32   appSize     = 0;
HWND     appWindow   = 0;

PrivateStart;

SYSTEM_INFO   systemInfo = {};
byte8       * g_addr     = 0;
uint32        g_pos      = 0;

PrivateEnd;

byte8 * Alloc(uint32 size)
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

byte8 * AllocEx
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

void WriteAddress
(
	byte8  * addr,
	byte8  * dest,
	uint32   size,
	byte8    header,
	uint32   padSize,
	byte8    padValue
)
{
	byte32 protection = 0;
	VirtualProtect(addr, (size + padSize), PAGE_EXECUTE_READWRITE, &protection);
	{
		if (header)
		{
			addr[0] = header;
		}
		if (size == 2)
		{
			*(int8 *)(addr + (size - 1)) = (int8)(dest - addr - size);
		}
		else
		{
			*(int32 *)(addr + (size - 4)) = (int32)(dest - addr - size);
		}
		if (padSize)
		{
			memset((addr + size), padValue, padSize);
		}
	}
	VirtualProtect(addr, (size + padSize), protection, &protection);
}

void vp_memset
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

void vp_memcpy
(
	void   * dest,
	void   * addr,
	uint32   size
)
{
	byte32 protection = 0;
	VirtualProtect(dest, size, PAGE_EXECUTE_READWRITE, &protection);
	{
		memcpy(dest, addr, size);
	}
	VirtualProtect(dest, size, protection, &protection);
}

// @Todo: Add xmm register saving.
// @Todo: Add size3 for stuff directly after the call.
// @Todo: Add noReturn argument.
FUNC CreateFunction
(
	void   * funcAddr,
	byte8  * jumpAddr,
	bool     saveRegisters,
	bool     noResult,
	uint32   size0,
	uint32   size1,
	uint32   size2,
	uint32   cacheSize,
	uint32   count
)
{
	byte8 payload[2048];
	uint32 pos = 0;
	uint32 off0;
	uint32 off1;
	uint32 off2;
	uint32 offJump;
	FUNC func = {};

	auto Feed = [&](byte8 * buffer, uint32 size)
	{
		memcpy((payload + pos), buffer, size);
		pos += size;
	};

	off0 = pos;
	pos += size0;

	if (saveRegisters)
	{
		if (noResult)
		{
			byte8 buffer[] =
			{
				0x50, //push rax
			};
			Feed(buffer, sizeof(buffer));
		}
		if (count)
		{
			if (noResult)
			{
				byte8 buffer[] =
				{
					0x48, 0x8D, 0x44, 0x24, 0x08, //lea rax,[rsp+08]
				};
				Feed(buffer, sizeof(buffer));
			}
			else
			{
				byte8 buffer[] =
				{
					0x48, 0x8B, 0xC4, //mov rax,rsp
				};
				Feed(buffer, sizeof(buffer));
			}
		}
		{
			byte8 buffer[] =
			{
				0x51,                   //push rcx
				0x52,                   //push rdx
				0x53,                   //push rbx
				0x54,                   //push rsp
				0x55,                   //push rbp
				0x56,                   //push rsi
				0x57,                   //push rdi
				0x41, 0x50,             //push r8
				0x41, 0x51,             //push r9
				0x41, 0x52,             //push r10
				0x41, 0x53,             //push r11
				0x41, 0x54,             //push r12
				0x41, 0x55,             //push r13
				0x41, 0x56,             //push r14
				0x41, 0x57,             //push r15
				0x9C,                   //pushfq
				0x48, 0x8B, 0xEC,       //mov rbp,rsp
				0x40, 0x80, 0xE4, 0xF0, //and spl,F0
			};
			Feed(buffer, sizeof(buffer));
		}


		// @Todo: Merge and set 4 as default argument.

		if (count)
		{
			byte8 buffer[] =
			{
				0x48, 0x81, 0xEC, 0x00, 0x00, 0x00, 0x00, //sub rsp
			};
			auto & sub = *(uint32 *)(buffer + 3) += (count * 8);
			if (count & (1 << 0))
			{
				sub += 8;
			}
			sub += 0x20;
			Feed(buffer, sizeof(buffer));
		}
		else
		{
			byte8 buffer[] =
			{
				0x48, 0x83, 0xEC, 0x20, //sub rsp,20
			};
			Feed(buffer, sizeof(buffer));
		}






		// @Research: rbp might be a better fit, will result in wide offset though.

		// @Todo: if count > 4

		if (count)
		{
			byte8 buffer[] =
			{
				0x51,                         //push rcx
				0x56,                         //push rsi
				0x57,                         //push rdi
				0xB9, 0x00, 0x00, 0x00, 0x00, //mov ecx,count
				0x48, 0x8D, 0x70, 0x28,       //lea rsi,[rax+28] return addr + shadow space
				0x48, 0x8D, 0x7C, 0x24, 0x38, //lea rdi,[rsp+38] rdi + rsi + rcx + shadow space
				0xF3, 0x48, 0xA5,             //repe movsq
				0x5F,                         //pop rdi
				0x5E,                         //pop rsi
				0x59,                         //pop rcx
			};
			*(uint32 *)(buffer + 4) = count;
			Feed(buffer, sizeof(buffer));
		}
	}

	off1 = pos;
	pos += size1;

	if (funcAddr)
	{
		byte8 buffer[] =
		{
			0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rax,funcAddr
			0xFF, 0xD0,                                                 //call rax
		};
		*(void **)(buffer + 2) = funcAddr;
		Feed(buffer, sizeof(buffer));
	}
	if (saveRegisters)
	{
		byte8 buffer[] =
		{
			0x48, 0x8B, 0xE5, //mov rsp,rbp
			0x9D,             //popfq
			0x41, 0x5F,       //pop r15
			0x41, 0x5E,       //pop r14
			0x41, 0x5D,       //pop r13
			0x41, 0x5C,       //pop r12
			0x41, 0x5B,       //pop r11
			0x41, 0x5A,       //pop r10
			0x41, 0x59,       //pop r9
			0x41, 0x58,       //pop r8
			0x5F,             //pop rdi
			0x5E,             //pop rsi
			0x5D,             //pop rbp
			0x5C,             //pop rsp
			0x5B,             //pop rbx
			0x5A,             //pop rdx
			0x59,             //pop rcx
		};
		Feed(buffer, sizeof(buffer));
		if (noResult)
		{
			byte8 buffer[] =
			{
				0x58, //pop rax
			};
			Feed(buffer, sizeof(buffer));
		}
	}

	off2 = pos;
	pos += size2;

	offJump = pos;
	if (jumpAddr)
	{
		byte8 buffer[] =
		{
			0xE9, 0x00, 0x00, 0x00, 0x00, //jmp
		};
		Feed(buffer, sizeof(buffer));
	}
	else
	{
		byte8 buffer[] =
		{
			0xC3, //ret
		};
		Feed(buffer, sizeof(buffer));
	}

	Align<uint32>(g_pos, 0x10);
	func.addr = (g_addr + g_pos);
	memcpy(func.addr, payload, pos);
	g_pos += pos;

	if (jumpAddr)
	{
		WriteJump((func.addr + offJump), jumpAddr);
	}

	func.sect0 = (func.addr + off0);
	func.sect1 = (func.addr + off1);
	func.sect2 = (func.addr + off2);

	if (cacheSize)
	{
		Align<uint32>(g_pos, 0x10);
		func.cache = (byte8 **)(g_addr + g_pos);
		g_pos += cacheSize;
	}

	return func;
}

bool Core_Memory_Init(uint32 size)
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

	Log("appStart %llX", appBaseAddr            );
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
