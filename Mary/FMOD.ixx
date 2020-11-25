module;
#include "../Core/Core.h"

#include "Vars.h"
export module FMOD;

#define debug true

enum
{
	FMOD_OK                     = 0,
	FMOD_CREATECOMPRESSEDSAMPLE = 0x00000200,
	FMOD_OPENMEMORY             = 0x00000800,
	FMOD_LOWMEM                 = 0x08000000,
	FMOD_CACHE_SIZE             = (128 * 1024 * 1024),
};

typedef int32  FMOD_RESULT;
typedef uint32 FMOD_MODE;
typedef void   FMOD_SYSTEM;
typedef void   FMOD_SOUND;

#define _(size) struct { byte8 Prep_Merge(padding_, __LINE__)[size]; }

#pragma pack(push, 1)

struct FMOD_CREATESOUNDEXINFO
{
	int32 cbsize;
	uint32 length;
	_(224);
};

#pragma pack(pop)

#undef _

typedef FMOD_RESULT(__fastcall * FMOD_System_CreateSound_t)
(
	FMOD_SYSTEM            *  system,
	void                   *  addr,
	FMOD_MODE                 mode,
	FMOD_CREATESOUNDEXINFO *  info,
	FMOD_SOUND             ** sound
);

FMOD_System_CreateSound_t FMOD_System_CreateSound = 0;

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














	// // Set cache size.
	// Write<dword>((appBaseAddr + 0x32636), FMOD_CACHE_SIZE);
	// Write<dword>((appBaseAddr + 0x32659), FMOD_CACHE_SIZE);
	// return true;


	return true;
}
