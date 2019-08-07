#pragma once
#include "../Core/Core.h"

struct LOCALE
{
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
			const char * header = "Arcade";
			const char * enable = "Enable";
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
			Game;
			struct
			{
				const char * label = "Mission";
				const char * items[21] =
				{
					"Mission 1",
					"Mission 2",
					"Mission 3",
					"Mission 4",
					"Mission 5",
					"Mission 6",
					"Mission 7",
					"Mission 8",
					"Mission 9",
					"Mission 10",
					"Mission 11",
					"Mission 12",
					"Mission 13",
					"Mission 14",
					"Mission 15",
					"Mission 16",
					"Mission 17",
					"Mission 18",
					"Mission 19",
					"Mission 20",
					"Bloody Palace",
				};
			}
			Mission;
			struct
			{
				const char * label = "Mode";
				const char * items[7] =
				{
					"Human",
					"Devil Hunter",
					"Son of Sparda",
					"Dante Must Die",
					"Legendary Dark Knight",
					"Heaven or Hell",
					"Hell and Hell",
				};
			}
			Mode;

			const char * room = "Room";
			const char * ignoreRoom = "Ignore";
			const char * position = "Position";
			const char * ignorePosition = "Ignore";


			struct
			{
				const char * label = "Character";
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
			const char * hitPoints = "Hit Points";
			const char * magicPoints = "Magic Points";
			const char * reset = "Reset";
		}
		Arcade;
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
		struct
		{
			const char * header = "Training";
			const char * enable = "Enable";
			const char * infiniteHitPoints = "Infinite Hit Points";
			const char * infiniteMagicPoints = "Infinite Magic Points";
			const char * disableTimer = "Disable Timer";
			const char * reset = "Reset";
		}
		Training;
	}
	Game;
	struct
	{
		//struct
		//{
		//	const char * header = "Media";
		//	const char * skipIntro = "Skip Intro";
		//	struct
		//	{
		//		const char * label = "Game";
		//		const char * items[3] =
		//		{
		//			"Dante / Nero",
		//			"Vergil",
		//			"Trish / Lady",
		//		};
		//	}
		//	skipIntroGame;
		//}
		//Media;
		//struct
		//{
		//	const char * header = "Speed";
		//	const char * global = "Global";
		//	const char * menu = "Menu";
		//	const char * reset = "Reset";

		//}
		//Speed;
		struct
		{
			const char * header = "Window";
			const char * forceFocus = "Force Focus";
			const char * borderless = "Borderless";

		}
		Window;
	}
	System;
	//struct
	//{
	//	struct
	//	{
	//		const char * header = "Fixes";
	//		const char * replaceMemoryAllocationFunctions = "Replace Memory Allocation Functions";
	//	}
	//	Fixes;
	//	struct
	//	{
	//		const char * header = "Timers";
	//		const char * disableActorIdleTimer = "Disable Actor Idle Timer";
	//		const char * disableAutosaveMenuTimer = "Disable Autosave Menu Timer";
	//		const char * disableMainMenuTimer = "Disable Main Menu Timer";
	//	}
	//	Timers;
	//}
	//Debug;











	const char * restart = "Restart App!";
};

extern LOCALE Locale;
