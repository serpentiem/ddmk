#ifndef __MODULE_CONFIG__
#define __MODULE_CONFIG__

module;
#include "../Core/Core.h"

#include "Vars.h"
export module ModuleName(Config);

#define debug true

#pragma pack(push, 1)
export struct Config
{
	struct
	{
		bool enable = true;
		PlayerData playerData[MAX_PLAYER][MAX_ENTITY] = {};
		uint8 playerCount = 1;
		bool enableQuicksilver[MAX_PLAYER] =
		{
			true,
			true,
			true,
			true,
		};
		bool enableDoppelganger[MAX_PLAYER] = {};
	}
	Actor;
	struct
	{
		float32 jetStreamDuration[2] = {};
		float32 jetStreamRange   [2] = {};
	}
	AgniRudra;
	struct
	{
		bool coreAbility = false;
		uint8 count[2] = { 1, 1 };
	}
	AirHike;
	struct
	{
		bool    enable         = true;
		uint32  mission        = 17;
		uint32  mode           = MODE_NORMAL;
		uint32  room           = 900;
		uint32  position       = 0;
		bool    ignoreRoom     = false;
		bool    ignorePosition = false;
		uint8   floor          = 0;
		float32 hitPoints      = 6000;
		float32 magicPoints    = 3000;
		uint8   character      = CHAR_DANTE;
		uint8   costume        = 0;
		uint32  style          = STYLE_TRICKSTER;
		// @Todo: Change to weapons.
		uint8 meleeWeapons[2] =
		{
			WEAPON_REBELLION,
			WEAPON_CERBERUS,
		};
		uint8 rangedWeapons[2] =
		{
			WEAPON_EBONY_IVORY,
			WEAPON_SHOTGUN,
		};
	}
	Arcade;
	struct
	{
		bool swapNormalShotAndMultiLock = false;
		bool instantFullCharge          = false;
	}
	Artemis;
	struct
	{
		bool hide = false;
		float32 straightDuration   [2] = { 7   , 7    };
		float32 straightRange      [2] = { 350 , 350  };
		float32 airStraightDuration[2] = { 7   , 7    };
		float32 airStraightRange   [2] = { 350 , 350  };
	}
	BeowulfDante;
	struct
	{
		bool hide = false;
	}
	BeowulfVergil;
	struct
	{
		bool enable = false;
		struct
		{
			bool skipJester = false;
		}
		Mission5;
		struct
		{
			bool skipJester      = false;
			bool skipGeryonPart1 = false;
		}
		Mission12;
		struct
		{
			bool skipJester = false;
		}
		Mission17;
		struct
		{
			bool skipArkhamPart1 = false;
		}
		Mission19;
	}
	BossRush;
	struct
	{
		bool    invertX     = true;
		float32 height      = 140;
		float32 tilt        = 0.25f;
		float32 zoom        = 460;
		float32 zoomLockOn  = 400;
		bool    applyConfig = false;
		uint32  rate        = 1000;
	}
	Camera;
	struct
	{
		uint8 airHike[5][4] =
		{
			{ 128,   0,   0, 200 },
			{  96, 128, 144, 200 },
			{ 160,  64,  16, 200 },
			{ 112,  64, 160, 200 },
			{ 128, 128, 128, 200 },
		};
		struct
		{
			uint8 skyStar[4] = { 255, 0, 0, 200 };
		}
		Trickster;
		struct
		{
			uint8 ultimate[4] = { 143, 112, 48, 200 };
		}
		Royalguard;
		struct
		{
			uint8 clone[4] = { 16, 16, 16, 48 };
		}
		Doppelganger;
		struct
		{
			uint8 dante[5][4] =
			{
				{ 128,   0,   0, 200 },
				{  96, 128, 144, 200 },
				{ 160,  64,  16, 200 },
				{ 112,  64, 160, 200 },
				{ 128, 128, 128, 200 },
			};
			uint8 sparda[4] = { 128, 0, 0, 200 };
			uint8 vergil[3][4] =
			{
				{ 32, 64, 128, 200 },
				{ 32, 64, 128, 200 },
				{ 32, 64, 128, 200 },
			};
			uint8 neroAngelo[4] = { 64, 0, 255, 200 };
		}
		Aura;
	}
	Color;
	uint8 crazyComboLevelMultiplier = 6;
	struct
	{
		uint8 airTrickCount [2] = { 1, 1 };
		uint8 trickUpCount  [2] = { 1, 1 };
		uint8 trickDownCount[2] = { 1, 1 };
	}
	DarkSlayer;
	struct
	{
		bool noColor = false;
	}
	Doppelganger;
	struct
	{
		bool foursomeTime      = false;
		bool infiniteRainStorm = false;
	}
	EbonyIvory;
	struct
	{
		bool skipIntro     = true;
		bool skipCutscenes = true;
	}
	Event;
	struct
	{
		bool preferLocalFiles = true;
	}
	File;
	struct
	{
		bool infiniteRoundTrip = false;
		float32 stingerDuration   [2] = { 16 , 16  };
		float32 stingerRange      [2] = { 560, 560 };
		float32 airStingerDuration[2] = { 16 , 16  };
		float32 airStingerRange   [2] = { 560, 560 };
	}
	ForceEdge;
	struct
	{
		uint32 frameRate = 60;
		uint8  vSync     = 0;
	}
	Graphics;
	struct
	{
		bool hideMouseCursor = true;
	}
	Input;
	struct
	{
		float32 quicksilver  = 16.5f;
		float32 doppelganger = 16.5f;
		float32 devil        = 11;
	}
	MagicPointsDepletionRate;
	struct
	{
		float32 reverbShockDuration[2] = { 12 , 12  };
		float32 reverbShockRange   [2] = { 300, 300 };
	}
	Nevan;
	bool noDevilForm = false;
	float32 orbReach = 300;
	struct
	{
		bool infiniteSwordPierce = false;
		float32 stingerDuration   [2] = { 16 , 16  };
		float32 stingerRange      [2] = { 560, 560 };
		float32 airStingerDuration[2] = { 16 , 16  };
		float32 airStingerRange   [2] = { 560, 560 };
	}
	Rebellion;
	struct
	{
		bool   enable = false;
		byte16 button = GAMEPAD_UP;
	}
	RemoveBusyFlag;
	struct
	{
		bool   enable = false;
		byte16 button = GAMEPAD_BACK;
	}
	ResetPermissions;
	struct
	{
		float32 gunStingerDuration   [2] = { 8  , 8   };
		float32 gunStingerRange      [2] = { 200, 200 };
		float32 airGunStingerDuration[2] = { 8  , 8   };
		float32 airGunStingerRange   [2] = { 200, 200 };
	}
	Shotgun;
	struct
	{
		bool enable = false;
		struct
		{
			float32 base  = 1;
			float32 turbo = 1.2f;
			float32 actor = 1;
			float32 enemy = 1;
		}
		Main;
		struct
		{
			float32 actor = 1.05f;
			float32 enemy = 0.33f;
		}
		Quicksilver;
		struct
		{
			float32 dante[6] =
			{
				1.1f,
				1.2f,
				1.05f,
				1.1f,
				1.05f,
				1.1f,
			};
			float32 vergil[3] =
			{
				1.2f,
				1.2f,
				1.2f,
			};
			float32 neroAngelo[3] =
			{
				1,
				1,
				1,
			};
		}
		Devil;
	}
	Speed;
	// struct
	// {
	// 	bool noDoubleTap = false;
	// }
	// StyleSwitchController;
	struct
	{
		bool chronoSwords = false;
		//bool dante        = false;
	}
	SummonedSwords;
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
		uint8 dashCount    [2] = { 3, 3 };
		uint8 skyStarCount [2] = { 1, 1 };
		uint8 airTrickCount[2] = { 1, 1 };
	}
	Trickster;
	float32 weaponSwitchTimeout = 1;
	struct
	{
		bool forceFocus = true;
	}
	Window;
	struct
	{
		float32 rapidSlashDuration[2] = { 5  , 5   };
		float32 rapidSlashRange   [2] = { 330, 330 };
		float32 judgementCutCount [2] = { 2  , 2   };
		float32 judgementCutRange [2] = { 500, 500 };
	}
	Yamato;
};
#pragma pack(pop)

export Config defaultConfig;
export Config activeConfig;
export Config queuedConfig;

char g_path[64] = {};

export void ApplyDefaultPlayerData
(
	PlayerData & playerData,
	uint8 character
)
{
	memset(&playerData, 0, sizeof(PlayerData));

	switch (character)
	{
	case CHAR_DANTE:
	{
		playerData =
		{
			CHAR_DANTE,
			0,
			false,
			CHAR_DANTE,
			STYLE_TRICKSTER,
			STYLE_TRICKSTER,
			{
				WEAPON_REBELLION,
				WEAPON_CERBERUS,
				WEAPON_AGNI_RUDRA,
				WEAPON_NEVAN,
				WEAPON_BEOWULF_DANTE,
			},
			MELEE_WEAPON_COUNT_DANTE,
			0,
			{
				WEAPON_EBONY_IVORY,
				WEAPON_SHOTGUN,
				WEAPON_ARTEMIS,
				WEAPON_SPIRAL,
				WEAPON_KALINA_ANN,
			},
			RANGED_WEAPON_COUNT_DANTE,
			0
		};
		break;
	};
	case CHAR_BOB:
	{
		playerData =
		{
			CHAR_BOB
		};
		break;
	};
	case CHAR_LADY:
	{
		playerData =
		{
			CHAR_LADY
		};
		break;
	};
	case CHAR_VERGIL:
	{
		playerData =
		{
			CHAR_VERGIL,
			0,
			false,
			CHAR_DANTE,
			STYLE_DARK_SLAYER,
			STYLE_DARK_SLAYER,
			{
				WEAPON_YAMATO_VERGIL,
				WEAPON_BEOWULF_VERGIL,
				WEAPON_FORCE_EDGE,
			},
			MELEE_WEAPON_COUNT_VERGIL,
			0
		};
		break;
	};
	}
}

export void SaveConfig()
{
	if constexpr (debug)
	{
		LogFunction();
	}

	SaveFile(g_path, reinterpret_cast<byte8 *>(&activeConfig), sizeof(Config));
}

export void LoadConfig()
{
	if constexpr (debug)
	{
		LogFunction();
	}

	byte8 * file = 0;
	uint32 size = 0;

	file = LoadFile(g_path, &size);
	if (!file)
	{
		SaveConfig();
		return;
	}

	if (size != sizeof(Config))
	{
		Log("Size mismatch.");

		SaveConfig();
		return;
	}

	memcpy(&activeConfig, file, size);
	memcpy(&queuedConfig, file, size);
}

export void Config_Init
(
	const char * directoryName,
	const char * filename
)
{
	LogFunction();

	CreateDirectoryA(directoryName, 0);

	snprintf(g_path, sizeof(g_path), "%s\\%s", directoryName, filename);

	for_all(uint8, player, MAX_PLAYER){
	for_all(uint8, entity, MAX_ENTITY)
	{
		ApplyDefaultPlayerData(defaultConfig.Actor.playerData[player][entity], CHAR_DANTE);
		ApplyDefaultPlayerData(activeConfig.Actor.playerData [player][entity], CHAR_DANTE);
		ApplyDefaultPlayerData(queuedConfig.Actor.playerData [player][entity], CHAR_DANTE);
	}}
}

#endif
