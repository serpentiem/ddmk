#include "Memory32.h"

uint32        appProcessId = 0;
BYTE        * appBaseAddr  = 0;
HANDLE        appProcess   = 0;
HWND          mainWindow   = 0;
BYTE        * mainChunk    = 0;
uint32        mainChunkPos = 0;
SYSTEM_INFO   si           = {};
uint32        appSize      = 0;

void WriteAddress(BYTE * addr, BYTE * dest, uint32 size, BYTE header, uint32 padSize, BYTE padValue)
{
	DWORD p = 0;
	VirtualProtectEx(appProcess, addr, (size + padSize), PAGE_EXECUTE_READWRITE, &p);
	if (header)
	{
		*(BYTE *)addr = header;
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

void WriteCall(BYTE * addr, BYTE * dest, uint32 padSize, BYTE padValue)
{
	WriteAddress(addr, dest, 5, 0xE8, padSize, padValue);
}

void WriteJump(BYTE * addr, BYTE * dest, uint32 padSize, BYTE padValue)
{
	WriteAddress(addr, dest, 5, 0xE9, padSize, padValue);
}

void WriteShortJump(BYTE * addr, BYTE * dest, uint32 padSize, BYTE padValue)
{
	WriteAddress(addr, dest, 2, 0xEB, padSize, padValue);
}

void vp_memset(void * addr, BYTE value, uint32 size)
{
	DWORD p = 0;
	VirtualProtectEx(appProcess, addr, size, PAGE_EXECUTE_READWRITE, &p);
	memset(addr, value, size);
	VirtualProtectEx(appProcess, addr, size, p, &p);
}

void vp_memcpy(void * dest, void * addr, uint32 size)
{
	DWORD p = 0;
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
	uint32   size0,
	uint32   size1,
	uint32   size2,
	uint32   cacheSize
)
{
	BYTE payload[2048];
	uint32 pos = 0;

	uint32 off0;
	uint32 off1;
	uint32 off2;
	uint32 offJump;

	off0 = pos;
	pos += size0;

	if (saveRegisters)
	{
		if (noResult)
		{
			BYTE buffer[] =
			{
				0x50, //push eax
			};
			Feed();
		}
		BYTE buffer[] =
		{
			0x51, //push ecx
			0x52, //push edx
			0x53, //push ebx
			0x54, //push esp
			0x55, //push ebp
			0x56, //push esi
			0x57, //push edi
			0x9C, //pushfd
		};
		Feed();
	}

	off1 = pos;
	pos += size1;

	if (funcAddr)
	{
		BYTE buffer[] =
		{
			0xB8, 0x00, 0x00, 0x00, 0x00, //mov eax,funcAddr
			0xFF, 0xD0,                   //call eax
		};
		*(void **)(buffer + 1) = funcAddr;
		Feed();
	}
	if (saveRegisters)
	{
		BYTE buffer[] =
		{
			0x9D, //popfd
			0x5F, //pop edi
			0x5E, //pop esi
			0x5D, //pop ebp
			0x5C, //pop esp
			0x5B, //pop ebx
			0x5A, //pop edx
			0x59, //pop ecx
		};
		Feed();
		if (noResult)
		{
			BYTE buffer[] =
			{
				0x58, //pop eax
			};
			Feed();
		}
	}

	off2 = pos;
	pos += size2;

	offJump = pos;
	if (jumpAddr)
	{
		BYTE buffer[] =
		{
			0xE9, 0x00, 0x00, 0x00, 0x00, //jmp
		};
		Feed();
	}
	else
	{
		BYTE buffer[] =
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
		WriteJump((func.addr + offJump), (BYTE *)jumpAddr);
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
		func.cache = (BYTE **)(mainChunk + mainChunkPos);
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


	//mainChunk = (BYTE *)HighAlloc(mainChunkSize);

	// @Todo: Make sure memory is allocated after appBaseAddr
	// For now we make do with a random position.

	mainChunk = (BYTE *)VirtualAlloc(0, mainChunkSize, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);



	DWORD error = GetLastError();
	if (!mainChunk && error)
	{
		Log("VirtualAllocEx failed. %X", error);
		return false;
	}
	memset(mainChunk, 0xCC, mainChunkSize);
	return true;
}












