#pragma once
#include "../Core/Core.h"

struct LOCALE
{
	struct
	{
		const char * label[3] =
		{
			"Game",
			"System",
			"Tools",
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
				const char * label = "Mission";
				const char * items[25] =
				{
					"Prologue",
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
					"Mission 21",
					"Mission 22",
					"Mission 23",
					"Mission 24",
				};
			}
			Mission;
			struct
			{
				const char * label = "Mode";
				const char * items[4] =
				{
					"Easy",
					"Normal",
					"Hard",
					"Dante Must Die",
				};
			}
			Mode;
			const char * room = "Room";
			const char * ignoreRoom = "Ignore";
			struct
			{
				const char * label = "Character";
				const char * items[3] =
				{
					"Dante",
					"LDK",
					"Super Dante",
				};
			}
			Character;
			struct
			{
				const char * label = "Melee Weapon";
				const char * items[4] =
				{
					"Force Edge",
					"Alastor",
					"Ifrit",
					"Sparda",
				};
				const char * sparda = "Sparda";
				const char * yamato = "Yamato";
			}
			MeleeWeapon;
			struct
			{
				const char * label = "Ranged Weapon";
				const char * items[4] =
				{
					"Handgun",
					"Shotgun",
					"Grenadegun",
					"Nightmare Beta",
				};
			}
			RangedWeapon;
			const char * hitPointsUnitCount = "Hit Points Unit Count";
			const char * magicPointsUnitCount = "Magic Points Unit Count";
			const char * reset = "Reset";
		}
		Arcade;
		struct
		{
			const char * header = "Boss Rush";
			const char * enable = "Enable";
			struct
			{
				const char * header = "Mission 22";
				const char * skipAerialBattle = "Skip Aerial Battle";
			}
			Mission22;
			const char * reset = "Reset";
		}
		BossRush;
		struct
		{
			const char * header = "Dante";
			const char * enable = "Enable";
			struct
			{
				const char * header = "Force Edge";
				const char * unlockStinger = "Unlock Stinger";
				const char * unlockRoundTrip = "Unlock Round Trip";
			}
			ForceEdge;
			struct
			{
				const char * header = "Sparda";
				const char * unlockDevilTrigger = "Unlock Devil Trigger";
				const char * forceLoadAssets = "Force Load Assets";
			}
			Sparda;
			struct
			{
				const char * header = "Yamato";
				const char * unlock = "Unlock";
				const char * acquire = "Acquire";
			}
			Yamato;
			struct
			{
				const char * header = "Air Hike";
				const char * coreAbility = "Core Ability";
			}
			AirHike;
			const char * reset = "Reset";
		}
		Dante;
		struct
		{
			const char * header = "Lock-On";
			const char * enable = "Enable";
			struct
			{
				const char * label = "Button";
				const char * items[16] =
				{
					"Left Trigger",
					"Right Trigger",
					"Left Shoulder",
					"Right Shoulder",
					"Y",
					"B",
					"A",
					"X",
					"Back",
					"Left Thumb",
					"Right Thumb",
					"Start",
					"D-Pad Up",
					"D-Pad Right",
					"D-Pad Down",
					"D-Pad Left",
				};
			}
			Button;
			const char * reset = "Reset";
		}
		LockOn;
		struct
		{
			const char * header = "Mission Select";
			const char * enable = "Enable";
			struct
			{
				const char * label = "Mission";
				const char * items[25] =
				{
					"Prologue",
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
					"Mission 21",
					"Mission 22",
					"Mission 23",
					"Mission 24",
				};
			}
			Mission;
			struct
			{
				const char * label = "Mode";
				const char * items[4] =
				{
					"Easy",
					"Normal",
					"Hard",
					"Dante Must Die",
				};
			}
			Mode;
			const char * reset = "Reset";
		}
		MissionSelect;
		struct
		{
			const char * header = "Reset Motion State";
			const char * enable = "Enable";
			struct
			{
				const char * label = "Button";
				const char * items[16] =
				{
					"Left Trigger",
					"Right Trigger",
					"Left Shoulder",
					"Right Shoulder",
					"Y",
					"B",
					"A",
					"X",
					"Back",
					"Left Thumb",
					"Right Thumb",
					"Start",
					"D-Pad Up",
					"D-Pad Right",
					"D-Pad Down",
					"D-Pad Left",
				};
			}
			Button;
			const char * updateRate = "Update Rate";
			const char * reset = "Reset";
		}
		ResetMotionState;
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
		struct
		{
			const char * header = "Weapon Switcher";
			const char * enable = "Enable";
			struct
			{
				const char * header = "Melee";
				const char * weapon[4] =
				{
					"Force Edge",
					"Alastor",
					"Ifrit",
					"Sparda",
				};
				const char * sparda = "Sparda";
				const char * yamato = "Yamato";
				const char * timeout = "Timeout";
			}
			Melee;
			struct
			{
				const char * header = "Ranged";
				const char * weapon[4] =
				{
					"Handgun",
					"Shotgun",
					"Grenadegun",
					"Nightmare Beta",
				};
				const char * timeout = "Timeout";
			}
			Ranged;
			const char * reset = "Reset";
		}
		WeaponSwitcher;
	}
	Game;
	struct
	{
		struct
		{
			const char * header = "Input";
			struct
			{
				const char * header = "Mouse";
				const char * hideCursor = "Hide Cursor";
				const char * updateRate = "Update Rate";
			}
			Mouse;
			const char * reset = "Reset";
		}
		Input;
		struct
		{
			const char * header = "Window";
			const char * forceFocus = "Force Focus";
		}
		Window;
	}
	System;
	struct
	{
		const char * teleporter = "Teleporter";
	}
	Tools;
};

extern LOCALE Locale;
