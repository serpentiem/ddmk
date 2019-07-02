#pragma once
#include "DataTypes.h"
#include "Log.h"
#include "Windows.h"

extern uint32   appProcessId;
extern BYTE   * appBaseAddr;
extern HANDLE   appProcess;
extern HWND     mainWindow;
extern BYTE   * mainChunk;
extern uint64   mainChunkSize;

void * Alloc(uint64 size, void * pos, void * end);
void * HighAlloc(uint64 size);

template <typename T>
void Write(BYTE * addr, T value, uint64 padSize = 0, BYTE padValue = 0x90)
{
	uint64 size = sizeof(T);
	DWORD p = 0;
	VirtualProtectEx(appProcess, addr, (size + padSize), PAGE_EXECUTE_READWRITE, &p);
	*(T *)addr = value;
	if (padSize)
	{
		memset((addr + size), padValue, padSize);
	}
	VirtualProtectEx(appProcess, addr, (size + padSize), p, &p);
}

void WriteAddress   ( BYTE * addr, BYTE * dest, uint64 size,        BYTE header   = 0,   uint64 padSize = 0, BYTE padValue = 0x90 );
void WriteCall      ( BYTE * addr, BYTE * dest, uint64 padSize = 0, BYTE padValue = 0x90                                          );
void WriteJump      ( BYTE * addr, BYTE * dest, uint64 padSize = 0, BYTE padValue = 0x90                                          );
void WriteShortJump ( BYTE * addr, BYTE * dest, uint64 padSize = 0, BYTE padValue = 0x90                                          );

void vp_memset (void * addr, BYTE   value, uint64 size);
void vp_memcpy (void * dest, void * addr,  uint64 size);

struct FUNC
{
	BYTE *  addr;
	BYTE *  sect0;
	BYTE *  sect1;
	BYTE *  sect2;
	BYTE ** cache;
};

FUNC CreateFunction
(
	void   * funcAddr      = 0,
	void   * jumpAddr      = 0,
	bool     saveRegisters = true,
	bool     noResult      = true,
	uint64   size0         = 0,
	uint64   size1         = 0,
	uint64   size2         = 0,
	uint64   cacheSize     = 0
);

bool Memory_Init();
