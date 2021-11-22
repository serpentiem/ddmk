module;
#include <stdio.h>
#include <string.h>
export module Config;

import Core;

#include "../Core/Macros.h"

import Windows;
import DI8;

using namespace Windows;
using namespace DI8;

import Vars;

#define debug false



#define _(size) struct { byte8 Prep_Merge(padding_, __LINE__)[size]; }

#pragma pack(push, 1)



export struct Config
{
	bool welcome = true;



	struct
	{
		bool enable = (debug) ? true : false;
		uint8 playerCount = 1;
		PlayerData playerData[PLAYER_COUNT] = {};
	}
	Actor;

	bool airHikeCoreAbility = false;

	struct
	{
		bool   enable         = (debug) ? true : false;
		uint32 mission        = 17;
		uint32 mode           = MODE::DANTE_MUST_DIE;
		uint32 room           = 900;
		bool   ignoreRoom     = (debug) ? false : true;
		uint32 position       = 0;
		bool   ignorePosition = (debug) ? false : true;
		uint8  floor          = 0;
		uint16 level          = 0;
		float  hitPoints      = 20000;
		float  magicPoints    = 10000;
		uint8  character      = CHARACTER::DANTE;
		uint8  costume        = (debug) ? 1 : 0;
		uint32 style          = STYLE::TRICKSTER;
		uint8  weapons[4]     =
		{
			WEAPON::REBELLION,
			WEAPON::CERBERUS,
			WEAPON::EBONY_IVORY,
			WEAPON::SHOTGUN,
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












	uint8 dotShadow = DOT_SHADOW::DEFAULT;
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
	float orbReach = (debug) ? 9000.0f : 300.0f;
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








	bool resetPermissions = false;



















	struct
	{
		float main  = 1.0f;
		float turbo = 1.2f;
		float enemy = 1.0f;

		float quicksilverPlayerActor = 1.05f;
		float quicksilverEnemyActor  = 0.33f;

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
	bool infiniteMagicPoints = (debug) ? true : false;
	bool disableTimer        = false;
	bool infiniteBullets     = false;





	float linearWeaponSwitchTimeout = (debug) ? 6 : 12;








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
	float channelVolumes[CHANNEL::MAX] =
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


	bool forceIconFocus = false;









	float damageActorMultiplier = 1.0f;
	float damageEnemyMultiplier = 1.0f;
	uint32 damageStyleRank = STYLE_RANK::NONE;



	bool skipIntro     = (debug) ? true : false;
	bool skipCutscenes = (debug) ? true : false;

	bool preferLocalFiles = true;

	float frameRate = 60;
	uint8 vSync     = 0;

	bool hideMouseCursor = false;





	int32 windowPosX = 0;
	int32 windowPosY = 0;
	bool forceWindowFocus = true;




	float globalScale = 1;






	uint8 enemyCount = 1;
	ConfigCreateEnemyActorData configCreateEnemyActorData[30] = {};

	bool enemyAutoSpawn = false;










	struct OverlayData
	{
		bool enable = false;
		vec2 pos = { 8, 8 };
		float color[4] = { 1.0f, 0, 0, 1.0f };
	};

	struct MainOverlayData : OverlayData
	{
		bool showFocus               = true;
		bool showFPS                 = true;
		bool showSizes               = true;
		bool showFrameRateMultiplier = true;
		bool showEventData           = true;
		bool showPosition            = true;
		bool showRegionData          = false;

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





	OverlayData newMovesOverlayDataDante;
	OverlayData newMovesOverlayDataVergil;
	OverlayData newMovesOverlayDataBossLady;
	OverlayData newMovesOverlayDataBossVergil;








	struct
	{
		bool forceJustFrameRelease = false;
	}
	Royalguard;





	// To avoid surprises by using __declspec(align) we prefer _(n) and
	// static_assert to get the correct alignment.

	_(8);
	float kalinaAnnHookGrenadeHeight = 1280.0f;
	_(12);
	float kalinaAnnHookGrenadeTime = 90.0f;
	_(12);
	vec4 kalinaAnnHookMultiplier =
	{
		1.0f,
		1.0f,
		1.0f,
		1.0f,
	};






	bool  cameraInvertX       = (debug) ? true : false;
	uint8 cameraAutoAdjust    = 0;
	bool  disableCenterCamera = (debug) ? true : false;
	bool  disableBossCamera   = false;








	bool enableBossLadyFixes   = false;
	bool enableBossVergilFixes = false;
	bool enablePVPFixes        = false;


	bool hideMainHUD = false;
	bool hideLockOn = false;
	bool hideBossHUD = false;










	bool soundIgnoreEnemyData = false;







	bool enableRebellionAirStinger          = (debug) ? true : false;
	bool enableRebellionNewDrive            = (debug) ? true : false;
	bool enableRebellionQuickDrive          = (debug) ? true : false;
	bool enableCerberusAirRevolver          = (debug) ? true : false;
	bool enableNevanNewVortex               = (debug) ? true : false;

	bool enableYamatoVergilNewJudgementCut  = (debug) ? true : false;
	bool enableBeowulfVergilAirRisingSun    = (debug) ? true : false;
	bool enableBeowulfVergilAirLunarPhase   = (debug) ? true : false;
	bool enableYamatoForceEdgeNewComboPart4 = (debug) ? true : false;
	bool enableYamatoForceEdgeAirStinger    = (debug) ? true : false;
	bool enableYamatoForceEdgeNewRoundTrip  = (debug) ? true : false;





	uint8 dergil = 0;


	uint8 beowulfVergilAirRisingSunCount[2] = { 1, 1 };


	bool forceVisibleHUD = false;

	_(6);




	struct BarsData
	{
		bool enable = false;
		bool run = false;
		vec2 size = { 200, 30 };
		vec2 pos = { 8, 8 };
		uint32 lastX = 0;
		uint32 lastY = 0;
		float hitColor[4] = { 0, 1, 0, 1 };
		float magicColor[4] = { 0, 0, 1, 1 };
	};

	BarsData barsData[PLAYER_COUNT];



	bool forceSyncHitMagicPoints = false;

	bool updateLockOns = true;


	bool showCredits = true;





	KeyData keyData[3] =
	{
		{
			{
				KEY::LEFT_CONTROL,
				KEY::D
			},
			2
		},
		{},
		{},
	};
};

static_assert((offsetof(Config, kalinaAnnHookGrenadeHeight) % 0x10) == 0);
static_assert((offsetof(Config, kalinaAnnHookGrenadeTime  ) % 0x10) == 0);
static_assert((offsetof(Config, kalinaAnnHookMultiplier   ) % 0x10) == 0);
static_assert((offsetof(Config, barsData                  ) % 0x10) == 0);



#pragma pack(pop)

#undef _



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
	// if constexpr (debug)
	// {
	// 	LogFunction();

	// 	Log("size %u", sizeof(activeData));
	// }

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


// export template <typename T>
// void SetConfigHelper
// (
// 	T & activeData,
// 	T & queuedData,
// 	T & defaultData,
// 	T value
// )
// {
// 	activeData = queuedData = value;
// }






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
		case CHARACTER::DANTE:
		{
			characterData =
			{
				CHARACTER::DANTE,
				0,
				false,
				false,
				CHARACTER::DANTE,
				0,
				{
					{
						STYLE::TRICKSTER,
						STYLE::TRICKSTER,
					},
					{
						STYLE::SWORDMASTER,
						STYLE::QUICKSILVER,
					},
					{
						STYLE::ROYALGUARD,
						STYLE::ROYALGUARD,
					},
					{
						STYLE::GUNSLINGER,
						STYLE::DOPPELGANGER,
					},
				},
				{},
				{
					GAMEPAD::UP,
					GAMEPAD::RIGHT,
					GAMEPAD::DOWN,
					GAMEPAD::LEFT,
				},
				0,
				MELEE_WEAPON_COUNT_DANTE,
				{
					WEAPON::REBELLION,
					WEAPON::CERBERUS,
					WEAPON::AGNI_RUDRA,
					WEAPON::NEVAN,
					WEAPON::BEOWULF_DANTE,
				},
				0,
				0,
				WEAPON_SWITCH_TYPE::LINEAR,
				RIGHT_STICK,
				RANGED_WEAPON_COUNT_DANTE,
				{
					WEAPON::EBONY_IVORY,
					WEAPON::SHOTGUN,
					WEAPON::ARTEMIS,
					WEAPON::SPIRAL,
					WEAPON::KALINA_ANN,
				},
				0,
				0,
				WEAPON_SWITCH_TYPE::LINEAR,
				RIGHT_STICK
			};

			break;
		};
		case CHARACTER::BOB:
		{
			characterData =
			{
				CHARACTER::BOB
			};

			break;
		};
		case CHARACTER::LADY:
		{
			characterData =
			{
				CHARACTER::LADY
			};
			
			break;
		};
		case CHARACTER::VERGIL:
		{
			characterData =
			{
				CHARACTER::VERGIL,
				0,
				false,
				false,
				CHARACTER::DANTE,
				0,
				{
					{
						STYLE::DARK_SLAYER,
						STYLE::DARK_SLAYER,
					},
					{
						STYLE::DARK_SLAYER,
						STYLE::QUICKSILVER,
					},
					{
						STYLE::DARK_SLAYER,
						STYLE::DARK_SLAYER,
					},
					{
						STYLE::DARK_SLAYER,
						STYLE::DOPPELGANGER,
					},
				},
				{},
				{
					GAMEPAD::UP,
					GAMEPAD::RIGHT,
					GAMEPAD::DOWN,
					GAMEPAD::LEFT,
				},
				0,
				MELEE_WEAPON_COUNT_VERGIL,
				{
					WEAPON::YAMATO_VERGIL,
					WEAPON::BEOWULF_VERGIL,
					WEAPON::YAMATO_FORCE_EDGE,
				},
				0,
				0,
				WEAPON_SWITCH_TYPE::LINEAR,
				RIGHT_STICK
			};

			break;
		};
		case CHARACTER::BOSS_LADY:
		{
			characterData =
			{
				CHARACTER::BOSS_LADY
			};
			
			break;
		};
		case CHARACTER::BOSS_VERGIL:
		{
			characterData =
			{
				CHARACTER::BOSS_VERGIL
			};
			
			break;
		};
	}
}

export void ApplyDefaultPlayerData(PlayerData & playerData)
{
	playerData.button = GAMEPAD::RIGHT_THUMB;

	playerData.characterCount = 2;
	playerData.characterIndex = 0;

	old_for_all(uint8, characterIndex, CHARACTER_COUNT){
	old_for_all(uint8, entityIndex   , ENTITY_COUNT   )
	{
		ApplyDefaultCharacterData
		(
			playerData.characterData[characterIndex][entityIndex],
			(characterIndex == 1) ? CHARACTER::VERGIL : CHARACTER::DANTE
		);
	}}
}

export void SaveConfig()
{
	DebugLogFunction();



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
	DebugLogFunction();



	HANDLE file = 0;
	uint64 size = 0;

	file = OpenFile
	(
		g_path,
		FileFlags_Read
	);
	if (file == reinterpret_cast<HANDLE>(INVALID_HANDLE_VALUE))
	{
		Log("OpenFile failed.");

		Log("New Config");

		SaveConfig();

		return;
	}



	size = GetFileSize(file);

	Log("fileSize      %llu", size                 );
	Log("Config        %llu", sizeof(Config)       );
	Log("activeConfig  %llu", sizeof(activeConfig) );
	Log("queuedConfig  %llu", sizeof(queuedConfig) );
	Log("defaultConfig %llu", sizeof(defaultConfig));



	if (size != sizeof(Config))
	{
		Log("Size mismatch.");

		if (!CloseFile(file))
		{
			Log("CloseFile failed.");
		}

		Log("New Config");

		SaveConfig();

		return;
	}



	Log("Valid Config");



	[&]()
	{
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
			Log("LoadFile failed.");

			return;
		}

		CopyMemory
		(
			&queuedConfig,
			&activeConfig,
			sizeof(queuedConfig)
		);
	}();



	if (!CloseFile(file))
	{
		Log("CloseFile failed.");
	}
}








export void Config_Init
(
	const char * directoryName,
	const char * filename
)
{
	LogFunction();

	CreateDirectoryA(directoryName, 0);

	snprintf
	(
		g_path,
		sizeof(g_path),
		"%s\\%s",
		directoryName,
		filename
	);

	old_for_all(uint8, playerIndex, PLAYER_COUNT)
	{
		ApplyDefaultPlayerData(defaultConfig.Actor.playerData[playerIndex]);
		ApplyDefaultPlayerData(activeConfig.Actor.playerData[playerIndex]);
		ApplyDefaultPlayerData(queuedConfig.Actor.playerData[playerIndex]);
	}

	DebugLog("kalinaAnnHookGrenadeHeight %llX", offsetof(Config, kalinaAnnHookGrenadeHeight));
	DebugLog("kalinaAnnHookGrenadeTime   %llX", offsetof(Config, kalinaAnnHookGrenadeTime  ));
	DebugLog("kalinaAnnHookMultiplier    %llX", offsetof(Config, kalinaAnnHookMultiplier   ));
	DebugLog("barsData                   %llX", offsetof(Config, barsData                  ));
}
