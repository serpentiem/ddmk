#pragma once
#include "DataTypes.h"
#include "Log.h"
#include "Windows.h"

extern byte8 * appBaseAddr;
extern uint32  appSize;
extern HWND    appWindow;

struct FUNC
{
	byte8 *  addr;
	byte8 *  sect0;
	byte8 *  sect1;
	byte8 *  sect2;
	byte8 ** cache;
};

byte8 * Alloc(uint32 size);

byte8 * AllocEx
(
	uint32 size,
	uint64 pos,
	uint64 end
);

inline byte8 * LowAlloc(uint32 size)
{
	return AllocEx
	(
		size,
		0x10000,
		0x7FFFFFFF
	);
}

inline byte8 * HighAlloc(uint32 size)
{
	return AllocEx
	(
		size,
		(uint64)(appBaseAddr + appSize),
		(uint64)(appBaseAddr + 0x7FFFFFFF)
	);
}

template <typename T>
void Write
(
	byte8  * addr,
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
			memset((addr + size), padValue, padSize);
		}
	}
	VirtualProtect(addr, (size + padSize), protection, &protection);
}

void WriteAddress
(
	byte8  * addr,
	byte8  * dest,
	uint32   size,
	byte8    header   = 0,
	uint32   padSize  = 0,
	byte8    padValue = 0x90
);

inline void WriteCall
(
	byte8  * addr,
	byte8  * dest,
	uint32   padSize  = 0,
	byte8    padValue = 0x90
)
{
	WriteAddress(addr, dest, 5, 0xE8, padSize, padValue);
}

inline void WriteJump
(
	byte8  * addr,
	byte8  * dest,
	uint32   padSize  = 0,
	byte8    padValue = 0x90
)
{
	WriteAddress(addr, dest, 5, 0xE9, padSize, padValue);
}

void vp_memset
(
	void   * addr,
	byte8    value,
	uint32   size
);

void vp_memcpy
(
	void   * dest,
	void   * addr,
	uint32   size
);

FUNC CreateFunction
(
	void   * funcAddr      = 0,
	byte8  * jumpAddr      = 0,
	bool     saveRegisters = true,
	bool     noResult      = true,
	uint32   size0         = 0,
	uint32   size1         = 0,
	uint32   size2         = 0,
	uint32   cacheSize     = 0,
	uint32   count         = 0
);

bool Memory_Init();

#define HoboBreak() \
MessageBoxA(0, "break", 0, 0); \
MessageBoxA(0, "break", 0, 0);

template <typename T>
bool Align(T & pos, T boundary, byte8 * addr = 0, uint8 pad = 0)
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
