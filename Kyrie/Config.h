#pragma once
#include "../Core/Core.h"

#include "Vars.h"

#pragma pack(push, 1)
struct CONFIG
{
	struct
	{
		struct
		{
			bool   enable                     = false;
			uint8  actorCount                 = 1;
			uint8  character[(MAX_ACTOR - 1)] = {};
			uint8  costume  [(MAX_ACTOR - 1)] = {};
			uint32 spawnDelay                 = 3000;
		}
		Multiplayer;
		struct
		{
			bool enable              = false;
			bool infiniteHitPoints   = false;
			bool infiniteMagicPoints = false;
			bool disableTimer        = false;
		}
		Training;
	}
	Game;
	struct
	{
		struct
		{
			bool disableIdleTimer = false;
		}
		Actor;
		struct
		{
			struct
			{
				bool   hideCursor = true;
				uint32 updateRate = 10;
			}
			Mouse;
		}
		Input;
		struct
		{
			bool   skipIntro     = false;
			uint32 skipIntroGame = 0;
		}
		Media;
		struct
		{
			bool replaceAllocationFunctions = false;
		}
		Memory;
		struct
		{
			bool forceFocus = true;
			bool borderless = false;
		}
		Window;
	}
	System;
};
#pragma pack(pop)

extern CONFIG Config;
extern CONFIG DefaultConfig;
