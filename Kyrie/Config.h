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
			bool    enable         = false;
			uint32  game           = 0;
			uint32  mission        = 1;
			uint32  mode           = MODE_DEVIL_HUNTER;
			uint32  room           = 0;
			bool    ignoreRoom     = false;
			uint32  position       = 0;
			bool    ignorePosition = false;
			uint8   character      = CHAR_DANTE;
			uint32  costume        = 0;
			float32 hitPoints      = 6000;
			float32 magicPoints    = 3000;
		}
		Arcade;
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
			bool skipIntro = false;
		}
		Event;
		struct
		{
			struct
			{
				bool hideCursor = true;
			}
			Mouse;
		}
		Input;
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





	struct
	{
		float32 global = 1;
		float32 menu   = 1;
	}
	Speed;












};
#pragma pack(pop)

extern CONFIG Config;
extern CONFIG DefaultConfig;
