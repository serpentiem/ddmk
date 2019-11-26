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

enum FMOD_
{
	FMOD_OK,
	FMOD_CACHE_SIZE = (128 * 1024 * 1024),
};

#define FMOD_CREATECOMPRESSEDSAMPLE 0x00000200
#define FMOD_OPENMEMORY             0x00000800
#define FMOD_LOWMEM                 0x08000000

bool FMOD_Init();
