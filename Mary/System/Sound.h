#pragma once
#include "../../Core/Core.h"

struct HEAD
{
	byte signature[4];
	byte unknown[8];
	uint32 size;
	uint32 waveSize;
	dword progOff;
	dword smplOff;
	dword vagiOff;
};

struct PROG
{
	byte signature[4];
	uint32 size;
	uint32 sectCount; // Default: Starting from 0. Special: Starting from 1.
};

struct PROG_SECTION
{
	uint8 itemCount;
	byte unknown[7];
};

struct PROG_ITEM
{
	byte unknown[12];
	uint16 id;
};

struct SMPL
{
	byte signature[4];
	uint32 size;
	uint32 itemCount; // Starting from 0.
};

struct SMPL_ITEM
{
	byte unknown[10];
	uint16 id;
};

struct VAGI
{
	byte signature[4];
	uint32 size;
	uint32 itemCount; // Starting from 0.
};

struct VAGI_ITEM
{
	dword off;
	uint32 size;
	byte unknown[4];
	uint32 sampleRate;
};
