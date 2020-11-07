module;
#include "../Core/Core.h"

#include "Vars.h"
export module Config;

#define debug false

#pragma pack(push, 1)
export struct Config
{
	struct
	{
		bool enable = true;
		uint8 playerCount = 1;
		PlayerData playerData[PLAYER_COUNT] = {};
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
		uint32  mode           = MODE_DANTE_MUST_DIE;
		uint32  room           = 900;
		uint32  position       = 0;
		bool    ignoreRoom     = false;
		bool    ignorePosition = false;
		uint8   floor          = 0;
		float32 hitPoints      = 20000;
		float32 magicPoints    = 10000;
		uint8   character      = CHAR_DANTE;
		uint8   costume        = 0;
		uint32  style          = STYLE_DOPPELGANGER;
		uint8 weapons[4] =
		{
			WEAPON_REBELLION,
			WEAPON_CERBERUS,
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
		float timeout        = 500; // @Todo: Remove.
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
	uint8 crazyComboLevelMultiplier = 2; // 6
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
	uint8 dotShadow = DOT_SHADOW_ENABLE;
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
		double frameRate = 60.0;
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
		float32 quicksilver  = 13.75f;
		float32 doppelganger = 16.5f;
		float32 devil        = 11.0f;
	}
	MagicPointsDepletionValues;
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
	bool removeBusyFlag = false;
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

		float main  = 1.0f;
		float turbo = 1.2f;
		float enemy = 1.0f;

		float quicksilverActor = 1.05f;
		float quicksilverEnemy = 0.33f;

		float human = 1.0f;
		float devilDante[6] =
		{
			1.1f,
			1.2f,
			1.05f,
			1.1f,
			1.05f,
			1.1f,
		};
		float devilVergil[5] =
		{
			1.2f,
			1.2f,
			1.2f,
			1.0f,
			1.0f,
		};
	}
	Speed;
	struct
	{
		bool chronoSwords = false;
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
	struct
	{
		bool infiniteRoundTrip = false;
		float32 stingerDuration   [2] = { 16 , 16  };
		float32 stingerRange      [2] = { 560, 560 };
		float32 airStingerDuration[2] = { 16 , 16  };
		float32 airStingerRange   [2] = { 560, 560 };
	}
	YamatoForceEdge;
};
#pragma pack(pop)

export Config defaultConfig;
export Config activeConfig;
export Config queuedConfig;

char g_path[64] = {};

// $GetDataStart

export PlayerData & GetDefaultPlayerData(uint8 playerIndex)
{
	return defaultConfig.Actor.playerData[playerIndex];
}

export PlayerData & GetActivePlayerData(uint8 playerIndex)
{
	return activeConfig.Actor.playerData[playerIndex];
}

export PlayerData & GetQueuedPlayerData(uint8 playerIndex)
{
	return queuedConfig.Actor.playerData[playerIndex];
}

export PlayerData & GetPlayerData(uint8 playerIndex)
{
	return GetActivePlayerData(playerIndex);
}

export template <typename T>
PlayerData & GetDefaultPlayerData(T & actorData)
{
	return GetDefaultPlayerData(actorData.newPlayerIndex);
}

export template <typename T>
PlayerData & GetActivePlayerData(T & actorData)
{
	return GetActivePlayerData(actorData.newPlayerIndex);
}

export template <typename T>
PlayerData & GetQueuedPlayerData(T & actorData)
{
	return GetQueuedPlayerData(actorData.newPlayerIndex);
}

export template <typename T>
PlayerData & GetPlayerData(T & actorData)
{
	return GetPlayerData(actorData.newPlayerIndex);
}

export CharacterData & GetDefaultCharacterData
(
	uint8 playerIndex,
	uint8 characterIndex,
	uint8 entityIndex
)
{
	auto & playerData = GetDefaultPlayerData(playerIndex);

	return playerData.characterData[characterIndex][entityIndex];
}

export CharacterData & GetActiveCharacterData
(
	uint8 playerIndex,
	uint8 characterIndex,
	uint8 entityIndex
)
{
	auto & playerData = GetActivePlayerData(playerIndex);

	return playerData.characterData[characterIndex][entityIndex];
}

export CharacterData & GetQueuedCharacterData
(
	uint8 playerIndex,
	uint8 characterIndex,
	uint8 entityIndex
)
{
	auto & playerData = GetQueuedPlayerData(playerIndex);

	return playerData.characterData[characterIndex][entityIndex];
}

export CharacterData & GetCharacterData
(
	uint8 playerIndex,
	uint8 characterIndex,
	uint8 entityIndex
)
{
	auto & playerData = GetPlayerData(playerIndex);

	return playerData.characterData[characterIndex][entityIndex];
}

export template <typename T>
CharacterData & GetDefaultCharacterData(T & actorData)
{
	return GetDefaultCharacterData
	(
		actorData.newPlayerIndex,
		actorData.newCharacterIndex,
		actorData.newEntityIndex
	);
}

export template <typename T>
CharacterData & GetActiveCharacterData(T & actorData)
{
	return GetActiveCharacterData
	(
		actorData.newPlayerIndex,
		actorData.newCharacterIndex,
		actorData.newEntityIndex
	);
}

export template <typename T>
CharacterData & GetQueuedCharacterData(T & actorData)
{
	return GetQueuedCharacterData
	(
		actorData.newPlayerIndex,
		actorData.newCharacterIndex,
		actorData.newEntityIndex
	);
}

export template <typename T>
CharacterData & GetCharacterData(T & actorData)
{
	return GetCharacterData
	(
		actorData.newPlayerIndex,
		actorData.newCharacterIndex,
		actorData.newEntityIndex
	);
}

// $GetDataEnd

export void ApplyDefaultCharacterData
(
	CharacterData & characterData,
	uint8 character
)
{
	memset
	(
		&characterData,
		0,
		sizeof(CharacterData)
	);

	switch (character)
	{
		case CHAR_DANTE:
		{
			characterData =
			{
				CHAR_DANTE,
				0,
				false,
				CHAR_DANTE,
				{
					{
						STYLE_TRICKSTER,
						STYLE_TRICKSTER,
					},
					{
						STYLE_SWORDMASTER,
						STYLE_QUICKSILVER,
					},
					{
						STYLE_ROYALGUARD,
						STYLE_ROYALGUARD,
					},
					{
						STYLE_GUNSLINGER,
						STYLE_DOPPELGANGER,
					},
				},
				{},
				{
					GAMEPAD_UP,
					GAMEPAD_RIGHT,
					GAMEPAD_DOWN,
					GAMEPAD_LEFT,
				},
				0,
				MELEE_WEAPON_COUNT_DANTE,
				{
					WEAPON_REBELLION,
					WEAPON_CERBERUS,
					WEAPON_AGNI_RUDRA,
					WEAPON_NEVAN,
					WEAPON_BEOWULF_DANTE,
				},
				0,
				RANGED_WEAPON_COUNT_DANTE,
				{
					WEAPON_EBONY_IVORY,
					WEAPON_SHOTGUN,
					WEAPON_ARTEMIS,
					WEAPON_SPIRAL,
					WEAPON_KALINA_ANN,
				},
				0
			};

			break;
		};
		case CHAR_BOB:
		{
			characterData =
			{
				CHAR_BOB
			};

			break;
		};
		case CHAR_LADY:
		{
			characterData =
			{
				CHAR_LADY
			};
			
			break;
		};
		case CHAR_VERGIL:
		{
			characterData =
			{
				CHAR_VERGIL,
				0,
				false,
				CHAR_DANTE,
				{
					{
						STYLE_DARK_SLAYER,
						STYLE_DARK_SLAYER,
					},
					{
						STYLE_DARK_SLAYER,
						STYLE_QUICKSILVER,
					},
					{
						STYLE_DARK_SLAYER,
						STYLE_DARK_SLAYER,
					},
					{
						STYLE_DARK_SLAYER,
						STYLE_DOPPELGANGER,
					},
				},
				{},
				{
					GAMEPAD_UP,
					GAMEPAD_RIGHT,
					GAMEPAD_DOWN,
					GAMEPAD_LEFT,
				},
				0,
				MELEE_WEAPON_COUNT_VERGIL,
				{
					WEAPON_YAMATO_VERGIL,
					WEAPON_BEOWULF_VERGIL,
					WEAPON_YAMATO_FORCE_EDGE,
				},
				0
			};

			break;
		};
	}
}

export void ApplyDefaultPlayerData(PlayerData & playerData)
{
	playerData.characterCount = 2;
	playerData.characterIndex = 0;

	for_all(uint8, characterIndex, CHARACTER_COUNT){
	for_all(uint8, entityIndex   , ENTITY_COUNT   )
	{
		ApplyDefaultCharacterData
		(
			playerData.characterData[characterIndex][entityIndex],
			(characterIndex == 1) ? CHAR_VERGIL : CHAR_DANTE
		);
	}}
}

export void SaveConfig()
{
	if constexpr (debug)
	{
		LogFunction();
	}

	SaveFile(g_path, reinterpret_cast<byte8 *>(&queuedConfig), sizeof(Config));
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

	for_all(uint8, playerIndex, PLAYER_COUNT)
	{
		ApplyDefaultPlayerData(defaultConfig.Actor.playerData[playerIndex]);
		ApplyDefaultPlayerData(activeConfig.Actor.playerData[playerIndex]);
		ApplyDefaultPlayerData(queuedConfig.Actor.playerData[playerIndex]);
	}
}
