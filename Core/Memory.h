#pragma once
#include "DataTypes.h"
#include "Log.h"
#include "Windows.h"

extern uint32   appProcessId;
extern byte   * appBaseAddr;
extern HANDLE   appProcess;
extern HWND     mainWindow;
extern byte   * mainChunk;
extern uint64   mainChunkSize;

void * Alloc(uint64 size, void * pos, void * end);
void * HighAlloc(uint64 size);

template <typename T>
void Write(byte * addr, T value, uint64 padSize = 0, byte padValue = 0x90)
{
	uint64 size = sizeof(T);
	dword p = 0;
	VirtualProtectEx(appProcess, addr, (size + padSize), PAGE_EXECUTE_READWRITE, &p);
	*(T *)addr = value;
	if (padSize)
	{
		memset((addr + size), padValue, padSize);
	}
	VirtualProtectEx(appProcess, addr, (size + padSize), p, &p);
}

void WriteAddress   ( byte * addr, byte * dest, uint64 size,        byte header   = 0,   uint64 padSize = 0, byte padValue = 0x90 );
void WriteCall      ( byte * addr, byte * dest, uint64 padSize = 0, byte padValue = 0x90                                          );
void WriteJump      ( byte * addr, byte * dest, uint64 padSize = 0, byte padValue = 0x90                                          );
void WriteShortJump ( byte * addr, byte * dest, uint64 padSize = 0, byte padValue = 0x90                                          );

void vp_memset (void * addr, byte   value, uint64 size);
void vp_memcpy (void * dest, void * addr,  uint64 size);

struct FUNC
{
	byte *  addr;
	byte *  sect0;
	byte *  sect1;
	byte *  sect2;
	byte ** cache;
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

#define HoboBreak() \
MessageBoxA(0, "break", 0, 0); \
MessageBoxA(0, "break", 0, 0);

template <typename T>
void Align(T & pos, T boundary, byte * addr = 0, uint8 pad = 0)
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
}
