#pragma once
#include "../Core/Core.h"

struct LOCALE
{
	struct
	{
		struct
		{
			const char * header = "Multiplayer";
			const char * enable = "Enable";
			struct
			{
				const char * items[5] =
				{
					"Dante",
					"Nero",
					"Vergil",
					"Trish",
					"Lady",
				};
			}
			Character;
			const char * spawnDelay = "Spawn Delay";
			const char * reset = "Reset";
		}
		Multiplayer;
	}
	Game;
	struct
	{
		const char * label[4] =
		{
			"Game",
			"System",
			"Tools",
			"Debug",
		};
	}
	Main;
	struct
	{
		struct
		{
			const char * header = "Actor";
			const char * disableIdleTimer = "Disable Idle Timer";
		}
		Actor;
		struct
		{
			const char * header = "Media";
			const char * skipIntro = "Skip Intro";
			struct
			{
				const char * label = "Game";
				const char * items[3] =
				{
					"Dante / Nero",
					"Vergil",
					"Trish / Lady",
				};
			}
			skipIntroGame;
		}
		Media;
	}
	System;
};

extern LOCALE Locale;
