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
			bool   enable               = false;
			uint8  mission              = 1;
			uint8  mode                 = MODE_NORMAL;
			uint16 room                 = 0;
			bool   ignoreRoom           = false;
			uint8  character            = CHAR_DANTE;
			uint8  meleeWeapon          = WEAPON_FORCE_EDGE;
			bool   meleeWeaponSparda    = false;
			bool   meleeWeaponYamato    = false;
			uint8  rangedWeapon         = WEAPON_HANDGUN;
			uint8  hitPointsUnitCount   = 10;
			uint8  magicPointsUnitCount = 3;
		}
		Arcade;
		struct
		{
			bool enable = false;
			struct
			{
				bool skipAerialBattle = false;
			}
			Mission22;
		}
		BossRush;
		struct
		{
			bool enable = false;
			struct
			{
				bool unlockStinger   = false;
				bool unlockRoundTrip = false;
			}
			ForceEdge;
			struct
			{
				bool unlockDevilTrigger = false;
				bool forceLoadAssets    = false;
			}
			Sparda;
			struct
			{
				bool unlock = false;
			}
			Yamato;
			struct
			{
				bool coreAbility = false;
			}
			AirHike;
		}
		Dante;
		struct
		{
			bool enable = false;
			WORD button = GAMEPAD_X;
		}
		LockOn;
		struct
		{
			bool  enable  = false;
			uint8 mission = 1;
			uint8 mode    = MODE_NORMAL;
		}
		MissionSelect;
		struct
		{
			bool   enable     = false;
			WORD   button     = GAMEPAD_DPAD_UP;
			uint32 updateRate = 10;
		}
		ResetMotionState;
		struct
		{
			bool enable              = false;
			bool infiniteHitPoints   = false;
			bool infiniteMagicPoints = false;
			bool disableTimer        = false;
		}
		Training;
		struct
		{
			bool enable = false;
			struct
			{
				uint8 count     = 4;
				uint8 weapon[4] =
				{
					WEAPON_FORCE_EDGE,
					WEAPON_ALASTOR,
					WEAPON_IFRIT,
					WEAPON_SPARDA,
				};
				bool  sparda[4] = {};
				bool  yamato[4] = {};
				float32 timeout   = 12;
			}
			Melee;
			struct
			{
				uint8 count     = 4;
				uint8 weapon[4] =
				{
					WEAPON_HANDGUN,
					WEAPON_SHOTGUN,
					WEAPON_GRENADEGUN,
					WEAPON_NIGHTMARE_BETA,
				};
				float32 timeout = 12;
			}
			Ranged;
		}
		WeaponSwitcher;
	}
	Game;
	struct
	{
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
			bool forceFocus = true;
		}
		Window;
	}
	System;
};
#pragma pack(pop)

extern CONFIG Config;
extern CONFIG DefaultConfig;
