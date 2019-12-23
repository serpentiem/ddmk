#include "Memory.h"

uint32        appProcessId = 0;
byte        * appBaseAddr  = 0;
HANDLE        appProcess   = 0;
HWND          mainWindow   = 0;
byte        * mainChunk    = 0;
uint64        mainChunkPos = 0;
SYSTEM_INFO   si           = {};
uint64        appSize      = 0;

void * Alloc(uint64 size, void * pos, void * end)
{
	void * addr = 0;
	MEMORY_BASIC_INFORMATION mbi;
	bool match = false;
	Log("Begin search. %llX %llX", pos, end);
	do
	{







		addr = 0;
		mbi = {};
		VirtualQueryEx(appProcess, pos, &mbi, sizeof(mbi));
		uint64 inc = mbi.RegionSize;
		if ((mbi.RegionSize >= size) && (mbi.State == MEM_FREE))
		{
			addr = mbi.BaseAddress;
			Log("%llX %llX %llX %X", pos, addr, mbi.RegionSize, mbi.State);



			dword rem = (qword)addr % si.dwAllocationGranularity;
			if (!rem)
			{
				match = true;
				Log("Match found.");
				break;
			}



			inc = (si.dwAllocationGranularity - rem);






			Log("%llX", inc);
		}
		pos = (byte *)pos + inc;
	}
	while (pos < end);
	if (!match)
	{
		Log("No match found. %llX", pos);
		SetLastError(ERROR_INVALID_ADDRESS);
		return 0;
	}
	if (addr != VirtualAllocEx(appProcess, addr, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE))
	{
		Log("VirtualAllocEx failed. %X", GetLastError());
		SetLastError(ERROR_INVALID_ADDRESS);
		return 0;
	}
	mbi = {};
	VirtualQueryEx(appProcess, addr, &mbi, sizeof(mbi));
	Log("Allocation was successful. %llX %X", addr, mbi.State);
	SetLastError(0);
	return addr;
}

void * HighAlloc(uint64 size)
{
	LogFunction();
	void * pos = (appBaseAddr + appSize);
	void * end = (appBaseAddr + 0x7FFFFFFF);
	return Alloc(size, pos, end);
}

// @Todo: Add template support or use void *.

void WriteAddress(byte * addr, byte * dest, uint64 size, byte header, uint64 padSize, byte padValue)
{
	dword p = 0;
	VirtualProtectEx(appProcess, addr, (size + padSize), PAGE_EXECUTE_READWRITE, &p);
	if (header)
	{
		*(byte *)addr = header;
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
	VirtualProtectEx(appProcess, addr, (size + padSize), p, &p);
}

void WriteCall(byte * addr, byte * dest, uint64 padSize, byte padValue)
{
	WriteAddress(addr, dest, 5, 0xE8, padSize, padValue);
}

void WriteJump(byte * addr, byte * dest, uint64 padSize, byte padValue)
{
	WriteAddress(addr, dest, 5, 0xE9, padSize, padValue);
}

void WriteShortJump(byte * addr, byte * dest, uint64 padSize, byte padValue)
{
	WriteAddress(addr, dest, 2, 0xEB, padSize, padValue);
}

void vp_memset(void * addr, byte value, uint64 size)
{
	dword p = 0;
	VirtualProtectEx(appProcess, addr, size, PAGE_EXECUTE_READWRITE, &p);
	memset(addr, value, size);
	VirtualProtectEx(appProcess, addr, size, p, &p);
}

void vp_memcpy(void * dest, void * addr, uint64 size)
{
	dword p = 0;
	VirtualProtectEx(appProcess, dest, size, PAGE_EXECUTE_READWRITE, &p);
	memcpy(dest, addr, size);
	VirtualProtectEx(appProcess, dest, size, p, &p);
}

#define Feed()                                   \
memcpy((payload + pos), buffer, sizeof(buffer)); \
pos += sizeof(buffer);

FUNC CreateFunction
(
	void   * funcAddr,
	void   * jumpAddr,
	bool     saveRegisters,
	bool     noResult,
	uint64   size0,
	uint64   size1,
	uint64   size2,
	uint64   cacheSize
)
{
	byte payload[2048];
	uint64 pos = 0;

	uint64 off0;
	uint64 off1;
	uint64 off2;
	uint64 offJump;

	off0 = pos;
	pos += size0;

	if (saveRegisters)
	{
		if (noResult)
		{
			byte buffer[] =
			{
				0x50, //push rax
			};
			Feed();
		}
		byte buffer[] =
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
			0x48, 0x83, 0xEC, 0x20, //sub rsp,20
		};
		Feed();
	}

	off1 = pos;
	pos += size1;

	if (funcAddr)
	{
		byte buffer[] =
		{
			0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rax,funcAddr
			0xFF, 0xD0,                                                 //call rax
		};
		*(void **)(buffer + 2) = funcAddr;
		Feed();
	}
	if (saveRegisters)
	{
		byte buffer[] =
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
		Feed();
		if (noResult)
		{
			byte buffer[] =
			{
				0x58, //pop rax
			};
			Feed();
		}
	}

	off2 = pos;
	pos += size2;

	offJump = pos;
	if (jumpAddr)
	{
		byte buffer[] =
		{
			0xE9, 0x00, 0x00, 0x00, 0x00, //jmp
		};
		Feed();
	}
	else
	{
		byte buffer[] =
		{
			0xC3, //ret
		};
		Feed();
	}

	FUNC func = {};
	if (mainChunkPos % 0x10)
	{
		mainChunkPos += (0x10 - (mainChunkPos % 0x10));
	}
	func.addr = (mainChunk + mainChunkPos);
	memcpy(func.addr, payload, pos);
	mainChunkPos += pos;

	if (jumpAddr)
	{
		WriteJump((func.addr + offJump), (byte *)jumpAddr);
	}

	func.sect0 = (func.addr + off0);
	func.sect1 = (func.addr + off1);
	func.sect2 = (func.addr + off2);

	if (cacheSize)
	{
		if (mainChunkPos % 0x10)
		{
			mainChunkPos += (0x10 - (mainChunkPos % 0x10));
		}
		func.cache = (byte **)(mainChunk + mainChunkPos);
		mainChunkPos += cacheSize;
	}

	return func;
}

#undef Feed

bool Memory_Init()
{
	LogFunction();
	appProcessId = GetCurrentProcessId();
	MODULEENTRY32 me32 = {};
	me32.dwSize = sizeof(MODULEENTRY32);
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, appProcessId);
	Module32First(snapshot, &me32);
	appBaseAddr = me32.modBaseAddr;
	Log("%u %s %llX", appProcessId, me32.szModule, appBaseAddr);
	appProcess = OpenProcess(PROCESS_ALL_ACCESS, false, appProcessId);
	if (!appProcess)
	{
		Log("OpenProcess failed. %X", GetLastError());
		return false;
	}
	if (!mainChunkSize)
	{
		Log("No chunk desired.");
		return true;
	}
	GetSystemInfo(&si);
	mainChunk = (byte *)HighAlloc(mainChunkSize);
	dword error = GetLastError();
	if (!mainChunk && error)
	{
		Log("VirtualAllocEx failed. %X", error);
		return false;
	}
	memset(mainChunk, 0xCC, mainChunkSize);
	return true;
}
