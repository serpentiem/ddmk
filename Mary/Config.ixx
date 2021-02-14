// @Todo: Clean.
// @Todo: Create order script.

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
		bool enable = false;
		uint8 playerCount = 1;
		PlayerData playerData[PLAYER_COUNT] = {};
	}
	Actor;
	bool airHikeCoreAbility = false;
	struct
	{
		bool   enable         = false;
		uint32 mission        = 17;
		uint32 mode           = MODE_NORMAL;
		uint32 room           = 900;
		uint32 position       = 0;
		bool   ignoreRoom     = false;
		bool   ignorePosition = false;
		uint8  floor          = 0;
		float  hitPoints      = 20000;
		float  magicPoints    = 10000;
		uint8  character      = CHAR_DANTE;
		uint8  costume        = 0;
		uint32 style          = STYLE_TRICKSTER;
		uint8  weapons[4]     =
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



	bool hideBeowulfDante = false;
	bool hideBeowulfVergil = false;









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
		bool  invertX        = false;
		float height         = 140.0f;
		float tilt           = 0.25f;
		float distance       = 460.0f;
		float distanceLockOn = 400.0f;
		bool  applyConfig    = false;
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












	uint8 dotShadow = DOT_SHADOW_ENABLE;
	struct
	{
		bool foursomeTime      = false;
		bool infiniteRainStorm = false;
	}
	EbonyIvory;
















	float depleteQuicksilver  = 13.75f;
	float depleteDoppelganger = 16.5f;
	float depleteDevil        = 11.0f;



















	bool noDevilForm = false;
	float orbReach = 300.0f;
	struct
	{
		bool  infiniteSwordPierce = false;
		float stingerDuration   [2] = { 16 , 16  };
		float stingerRange      [2] = { 560, 560 };
		uint8 airStingerCount   [2] = { 1  , 1   };
		float airStingerDuration[2] = { 4  , 4   };
		float airStingerRange   [2] = { 140, 140 };
	}
	Rebellion;
	bool removeBusyFlag = false;
	bool resetPermissions = false;



















	struct
	{
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











	bool infiniteHitPoints   = false;
	bool infiniteMagicPoints = false;
	bool disableTimer        = false;





	float linearWeaponSwitchTimeout = 12;








	struct
	{
		uint8 judgementCutCount[2] = { 2, 2 };
	}
	Yamato;






	struct
	{
		bool infiniteRoundTrip = false;
		float stingerDuration   [2] = { 16 , 16  };
		float stingerRange      [2] = { 560, 560 };
		uint8 airStingerCount   [2] = { 1  , 1   };
		float airStingerDuration[2] = { 4  , 4   };
		float airStingerRange   [2] = { 140, 140 };
	}
	YamatoForceEdge;






	uint8 airHikeCount       [2] = { 1, 1 };
	uint8 kickJumpCount      [2] = { 1, 1 };
	uint8 wallHikeCount      [2] = { 1, 1 };
	uint8 dashCount          [2] = { 3, 3 };
	uint8 skyStarCount       [2] = { 1, 1 };
	uint8 airTrickCountDante [2] = { 1, 1 };
	uint8 airTrickCountVergil[2] = { 1, 1 };
	uint8 trickUpCount       [2] = { 1, 1 };
	uint8 trickDownCount     [2] = { 1, 1 };
	float channelVolumes[MAX_CHANNEL] =
	{
		1.0f,
		1.0f,
		1.0f,
		1.0f,
		1.0f,
		1.0f,
		1.0f,
		1.0f,
		1.0f,
		1.0f,
		1.0f,
	};







	struct TextureData
	{
		vec2 size;
		vec2 pos;
	};

	struct WeaponSwitchControllerTextureData
	{
		TextureData backgrounds[5];
		TextureData icons[5];
		TextureData highlights[5];
		TextureData arrow;
	};

	WeaponSwitchControllerTextureData meleeWeaponSwitchControllerTextureData =
	{
		{
			{
				{ 256 , 256 },
				{ 1442, 403 },
			},
			{
				{ 256 , 256 },
				{ 1651, 555 },
			},
			{
				{ 256 , 256 },
				{ 1571, 801 },
			},
			{
				{ 256 , 256 },
				{ 1313, 801 },
			},
			{
				{ 256 , 256 },
				{ 1233, 555 },
			},
		},
		{
			{
				{ 256 , 256 },
				{ 1442, 403 },
			},
			{
				{ 256 , 256 },
				{ 1651, 555 },
			},
			{
				{ 256 , 256 },
				{ 1571, 801 },
			},
			{
				{ 256 , 256 },
				{ 1313, 801 },
			},
			{
				{ 256 , 256 },
				{ 1233, 555 },
			},
		},
		{
			{
				{ 256 , 256 },
				{ 1442, 403 },
			},
			{
				{ 256 , 256 },
				{ 1651, 555 },
			},
			{
				{ 256 , 256 },
				{ 1571, 801 },
			},
			{
				{ 256 , 256 },
				{ 1313, 801 },
			},
			{
				{ 256 , 256 },
				{ 1233, 555 },
			},
		},
		{
			{ 128 , 128 },
			{ 1506, 671 },
		},
	};
	WeaponSwitchControllerTextureData rangedWeaponSwitchControllerTextureData =
	{
		{
			{
				{ 256, 256 },
				{ 222, 403 },
			},
			{
				{ 256, 256 },
				{ 431, 555 },
			},
			{
				{ 256, 256 },
				{ 351, 801 },
			},
			{
				{ 256, 256 },
				{ 93 , 801 },
			},
			{
				{ 256, 256 },
				{ 13 , 555 },
			},
		},
		{
			{
				{ 256, 256 },
				{ 222, 403 },
			},
			{
				{ 256, 256 },
				{ 431, 555 },
			},
			{
				{ 256, 256 },
				{ 351, 801 },
			},
			{
				{ 256, 256 },
				{ 93 , 801 },
			},
			{
				{ 256, 256 },
				{ 13 , 555 },
			},
		},
		{
			{
				{ 256, 256 },
				{ 222, 403 },
			},
			{
				{ 256, 256 },
				{ 431, 555 },
			},
			{
				{ 256, 256 },
				{ 351, 801 },
			},
			{
				{ 256, 256 },
				{ 93 , 801 },
			},
			{
				{ 256, 256 },
				{ 13 , 555 },
			},
		},
		{
			{ 128, 128 },
			{ 286, 671 },
		},
	};






	bool disableCenterCamera = false;


	// @Todo: Create struct.
	float damageActorMultiplier = 1.0f;
	float damageEnemyMultiplier = 1.0f;
	uint32 damageStyleRank = STYLE_RANK_NONE;



	bool skipIntro     = false;
	bool skipCutscenes = false;

	bool preferLocalFiles = true;

	double frameRate = 60.0;
	uint8  vSync     = 0;

	bool hideMouseCursor = true;

	bool forceWindowFocus = true;



	struct CreateEnemyData
	{
		uint32 enemy;
		uint32 variant;
		vec4 position;
		uint16 rotation;
		bool useMainActorData;
		uint16 spawnMethod;
		bool autoSpawn;
	};
	uint8 createEnemyCount = 1;
	CreateEnemyData createEnemyData[30] = {};










	struct OverlayData
	{
		bool enable = false;
		vec2 pos = { 8, 8 };
		float color[4] = { 1.0f, 0, 0, 1.0f };
	};

	struct MainOverlayData : OverlayData
	{
		bool showFocus = true;
		bool showFPS = true;
		bool showScene = true;
		bool showEventData = true;
		bool showPosition = true;
		bool showRegionData = true;

		MainOverlayData()
		{
			if constexpr (debug)
			{
				enable = true;
			}
		}
	}
	mainOverlayData;

	OverlayData missionOverlayData;



	struct
	{
		bool forceJustFrameRelease = false;
	}
	Royalguard;









	//MainOverlay, Overlay3;
//OverlayData MissionOverlay;








};
#pragma pack(pop)

export Config defaultConfig;
export Config activeConfig;
export Config queuedConfig;

export template <typename T>
void ResetConfigHelper
(
	T & activeData,
	T & queuedData,
	T & defaultData
)
{
	if constexpr (debug)
	{
		LogFunction();

		Log("size %u", sizeof(activeData));
	}

	CopyMemory
	(
		&queuedData,
		&defaultData,
		sizeof(queuedData)
	);
	CopyMemory
	(
		&activeData,
		&queuedData,
		sizeof(activeData)
	);
}

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
				false,
				CHAR_DANTE,
				0,
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
				0,
				WEAPON_SWITCH_TYPE_LINEAR,
				RANGED_WEAPON_COUNT_DANTE,
				{
					WEAPON_EBONY_IVORY,
					WEAPON_SHOTGUN,
					WEAPON_ARTEMIS,
					WEAPON_SPIRAL,
					WEAPON_KALINA_ANN,
				},
				0,
				0,
				WEAPON_SWITCH_TYPE_LINEAR
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
				false,
				CHAR_DANTE,
				0,
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
				0,
				0,
				WEAPON_SWITCH_TYPE_LINEAR
			};

			break;
		};
	}
}

export void ApplyDefaultPlayerData(PlayerData & playerData)
{
	playerData.button = GAMEPAD_RIGHT_THUMB;

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


	if
	(
		!SaveFile
		(
			g_path,
			&queuedConfig,
			sizeof(Config)
		)
	)
	{
		Log("SaveFile failed.");
	}
}

export void LoadConfig()
{
	if constexpr (debug)
	{
		LogFunction();
	}

	HANDLE file = 0;
	uint64 size = 0;

	file = OpenFile
	(
		g_path,
		FileFlags_Read
	);
	if (file == INVALID_HANDLE_VALUE)
	{

		Log("Invalid handle bro.");


		SaveConfig();

		return;
	}

	size = GetFileSize(file);
	if (size != sizeof(Config))
	{
		Log("Size mismatch.");

		if (!CloseFile(file))
		{
			Log("CloseFile failed.");
		}

		SaveConfig();

		return;
	}

	Log("Very valid file.");


	//HoboBreak();

	if
	(
		!LoadFile
		(
			file,
			size,
			&activeConfig
		)
	)
	{
		Log("LoadFile failed. &activeConfig");
	}

	if
	(
		!LoadFile
		(
			file,
			size,
			&queuedConfig
		)
	)
	{
		Log("LoadFile failed. &queuedConfig");
	}



	// LoadFile
	// (
	// 	file,
	// 	size,
	// 	&queuedConfig
	// )



	if (!CloseFile(file))
	{
		Log("CloseFile failed.");
	}





	// CopyMemory(&activeConfig, file, size);
	// CopyMemory(&queuedConfig, file, size);
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
