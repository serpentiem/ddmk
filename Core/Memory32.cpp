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












