#pragma once
#include "DataTypes.h"
#include "Log.h"

#include "Utility.h"

#include "Windows.h"

extern uint32   appProcessId;
extern BYTE   * appBaseAddr;
extern HANDLE   appProcess;
extern HWND     mainWindow;

extern BYTE   * mainChunk;
extern uint32   mainChunkSize;
extern uint32   mainChunkPos;





template <typename T>
void Write(BYTE * addr, T value, uint32 padSize = 0, BYTE padValue = 0x90)
{
	uint32 size = sizeof(T);
	DWORD p = 0;
	VirtualProtectEx(appProcess, addr, (size + padSize), PAGE_EXECUTE_READWRITE, &p);
	*(T *)addr = value;
	if (padSize)
	{
		memset((addr + size), padValue, padSize);
	}
	VirtualProtectEx(appProcess, addr, (size + padSize), p, &p);
}

void WriteAddress   ( BYTE * addr, BYTE * dest, uint32 size,        BYTE header   = 0,   uint32 padSize = 0, BYTE padValue = 0x90 );
void WriteCall      ( BYTE * addr, BYTE * dest, uint32 padSize = 0, BYTE padValue = 0x90                                          );
void WriteJump      ( BYTE * addr, BYTE * dest, uint32 padSize = 0, BYTE padValue = 0x90                                          );
void WriteShortJump ( BYTE * addr, BYTE * dest, uint32 padSize = 0, BYTE padValue = 0x90                                          );

void vp_memset (void * addr, BYTE   value, uint32 size);
void vp_memcpy (void * dest, void * addr,  uint32 size);

struct FUNC
{
	BYTE *  addr;
	BYTE *  sect0;
	BYTE *  sect1;
	BYTE *  sect2;
	BYTE ** cache;
};

//FUNC CreateFunction
//(
//	void   * funcAddr      = 0,
//	void   * jumpAddr      = 0,
//	bool     saveRegisters = true,
//	bool     noResult      = true,
//	uint32   size0         = 0,
//	uint32   size1         = 0,
//	uint32   size2         = 0,
//	uint32   cacheSize     = 0
//);









#define Feed()                                   \
memcpy((payload + pos), buffer, sizeof(buffer)); \
pos += sizeof(buffer);

template <typename T>
FUNC CreateFunction
(
	void   * funcAddr      = 0,
	T        jumpAddr      = 0,
	bool     saveRegisters = true,
	bool     noResult      = true,
	uint32   size0         = 0,
	uint32   size1         = 0,
	uint32   size2         = 0,
	uint32   cacheSize     = 0,
	bool     noReturn      = false
)
{
	BYTE payload[2048];
	uint32 pos = 0;

	uint32 off0;
	uint32 off1;
	uint32 off2;
	uint32 offJump;

	bool updateJump = false;

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
	if constexpr (typematch(T, int))
	{
		if (!noReturn)
		{
			if (jumpAddr == 0)
			{
				BYTE buffer[] =
				{
					0xC3, //ret
				};
				Feed();
			}
			else
			{
				BYTE buffer[] =
				{
					0xC2, 0x00, 0x00, //ret
				};
				uint16 & size = *(uint16 *)(buffer + 1);
				size = (uint16)(jumpAddr * 4);
				Feed();
			}
		}
	}
	else
	{
		BYTE buffer[] =
		{
			0xE9, 0x00, 0x00, 0x00, 0x00, //jmp
		};
		Feed();
		updateJump = true;
	}

	FUNC func = {};
	if (mainChunkPos % 0x10)
	{
		mainChunkPos += (0x10 - (mainChunkPos % 0x10));
	}
	func.addr = (mainChunk + mainChunkPos);
	memcpy(func.addr, payload, pos);
	mainChunkPos += pos;

	if (updateJump)
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


































bool Memory_Init();
