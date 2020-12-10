module;
#include "../Core/Core.h"

#include "Vars.h"
export module FMOD;

#define debug false

export bool FMOD_init = false;

export enum
{
	FMOD_OK                     = 0,
	FMOD_CREATECOMPRESSEDSAMPLE = 0x00000200,
	FMOD_OPENMEMORY             = 0x00000800,
	FMOD_LOWMEM                 = 0x08000000,
	FMOD_CACHE_SIZE             = (128 * 1024 * 1024),
};

export typedef int32  FMOD_RESULT;
export typedef uint32 FMOD_MODE;
export typedef void   FMOD_SYSTEM;
export typedef void   FMOD_SOUND;
export typedef void   FMOD_CHANNEL;

#define _(size) struct { byte8 Prep_Merge(padding_, __LINE__)[size]; }

#pragma pack(push, 1)

export struct FMOD_CREATESOUNDEXINFO
{
	int32 cbsize;
	uint32 length;
	_(224);
};

#pragma pack(pop)

#undef _

export typedef FMOD_RESULT(__fastcall * FMOD_System_CreateSound_t)
(
	FMOD_SYSTEM            *  system,
	void                   *  addr,
	FMOD_MODE                 mode,
	FMOD_CREATESOUNDEXINFO *  info,
	FMOD_SOUND             ** sound
);

export FMOD_System_CreateSound_t FMOD_System_CreateSound = 0;

export typedef FMOD_RESULT(__fastcall * FMOD_Channel_SetVolume_t)
(
	FMOD_CHANNEL * channel,
	float          volume
);

export FMOD_Channel_SetVolume_t FMOD_Channel_SetVolume = 0;

export bool FMOD_Init()
{
	LogFunction();

	byte32 error = 0;

	const char * libName = "fmod64.dll";


	SetLastError(0);

	auto lib = LoadLibraryA(libName);

	error = GetLastError();

	if (!lib)
	{
		Log("LoadLibraryA failed. %X", error);

		return false;
	}




	// FMOD_System_CreateSound
	{
		const char * funcName = "FMOD_System_CreateSound";

		SetLastError(0);

		auto funcAddr = GetProcAddress(lib, funcName);

		error = GetLastError();

		if (!funcAddr)
		{
			Log("GetProcAddress failed. %s %X", funcName, error);

			return false;
		}

		FMOD_System_CreateSound = reinterpret_cast<FMOD_System_CreateSound_t>(funcAddr);
	}


	Log("FMOD_System_CreateSound %llX", FMOD_System_CreateSound);


	// FMOD_Channel_SetVolume
	{
		const char * funcName = "FMOD_Channel_SetVolume";

		SetLastError(0);

		auto funcAddr = GetProcAddress(lib, funcName);

		error = GetLastError();

		if (!funcAddr)
		{
			Log("GetProcAddress failed. %s %X", funcName, error);

			return false;
		}

		FMOD_Channel_SetVolume = reinterpret_cast<FMOD_Channel_SetVolume_t>(funcAddr);
	}


	Log("FMOD_Channel_SetVolume %llX", FMOD_Channel_SetVolume);




















	// @Todo: Update.
	Write<uint32>((appBaseAddr + 0x32635 + 1), FMOD_CACHE_SIZE);
	/*
	dmc3.exe+32635 - B9 00003002    - mov ecx,02300000
	dmc3.exe+3263A - FF 15 20CE3100 - call qword ptr [dmc3.exe+34F460]
	*/

	Write<uint32>((appBaseAddr + 0x32658 + 1), FMOD_CACHE_SIZE);
	/*
	dmc3.exe+32658 - BA 00003002 - mov edx,02300000
	dmc3.exe+3265D - E8 A62D3100 - call dmc3.exe+345408
	*/






	// // Set cache size.
	// Write<dword>((appBaseAddr + 0x32636), FMOD_CACHE_SIZE);
	// Write<dword>((appBaseAddr + 0x32659), FMOD_CACHE_SIZE);
	// return true;


	return true;
}
