#pragma once
#include "../Core/Core.h"

typedef uint32 FMOD_MODE;
typedef int32  FMOD_RESULT;
typedef byte   FMOD_SOUND;
typedef byte   FMOD_SYSTEM;

struct FMOD_CREATESOUNDEXINFO
{
	int32 cbsize;
	uint32 length;
	byte unknown[224];
	FMOD_CREATESOUNDEXINFO()
	{
		cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
	}
};

typedef FMOD_RESULT(__fastcall * FMOD_System_CreateSound_t)
(
	FMOD_SYSTEM            *  system,
	byte                   *  addr,
	FMOD_MODE                 mode,
	FMOD_CREATESOUNDEXINFO *  info,
	FMOD_SOUND             ** sound
);

extern FMOD_System_CreateSound_t FMOD_System_CreateSound;

bool FMOD_Init();
