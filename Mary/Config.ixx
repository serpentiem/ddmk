module;
#include <stdio.h>
#include <string.h>
#include "../Core/RapidJSON.h"
export module Config;

import Core;

#include "../Core/Macros.h"

import Windows;
import DI8;

using namespace Windows;
using namespace DI8;

import Vars;

#define debug true



const char * directoryName = "configs";
const char * fileName      = "Mary.json";

char location[64] = {};



#define _(size) struct { byte8 Prep_Merge(padding_, __LINE__)[size]; }

#pragma pack(push, 1)



export struct Config
{
	struct
	{
		bool enable = (debug) ? true : false;
		uint8 playerCount = 1;
		PlayerData playerData[PLAYER_COUNT] = {};
	}
	Actor;



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



	struct
	{
		bool foursomeTime      = false;
		bool infiniteRainStorm = false;
	}
	EbonyIvory;



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



	struct
	{
		bool forceJustFrameRelease = false;
	}
	Royalguard;



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



	bool welcome = (debug) ? false : true;

	bool hideBeowulfDante = false;
	bool hideBeowulfVergil = false;



	bool airHikeCoreAbility = false;

	uint8 crazyComboLevelMultiplier = 6;


	uint8 dotShadow = DOT_SHADOW::DEFAULT;



	float depleteQuicksilver  = 13.75f;
	float depleteDoppelganger = 16.5f;
	float depleteDevil        = 11.0f;




	bool noDevilForm = false;
	float orbReach = (debug) ? 9000.0f : 300.0f;


	bool resetPermissions = false;


	bool infiniteHitPoints   = false;
	bool infiniteMagicPoints = (debug) ? true : false;
	bool disableTimer        = false;
	bool infiniteBullets     = false;


	float linearWeaponSwitchTimeout = (debug) ? 6 : 12;



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



	float damagePlayerActorMultiplier = 1.0f;
	float damageEnemyActorMultiplier = 1.0f;
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
	OverlayData bossLadyActionsOverlayData;
	OverlayData bossVergilActionsOverlayData;



	// To avoid surprises by using __declspec(align) we prefer _(n) and
	// static_assert to get the correct alignment.

	_(10);
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
	bool hideLockOn  = false;
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

	bool showCredits = (debug) ? false : true;



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



	bool absoluteUnit = false;



	char gamepadName[128] = "Wireless Controller";
	byte8 gamepadButton = 13;



	bool disablePlayerActorIdleTimer = false;
};

static_assert((offsetof(Config, kalinaAnnHookGrenadeHeight) % 0x10) == 0);
static_assert((offsetof(Config, kalinaAnnHookGrenadeTime  ) % 0x10) == 0);
static_assert((offsetof(Config, kalinaAnnHookMultiplier   ) % 0x10) == 0);
static_assert((offsetof(Config, barsData                  ) % 0x10) == 0);



#pragma pack(pop)

#undef _



export Config defaultConfig;
export Config queuedConfig;
export Config activeConfig;



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
	SetMemory
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



namespaceStart(JSON);

#include "../Core/JSON.h"

#pragma region CreateMembers

void CreateMembers_CharacterDataContent
(
	rapidjson::Value & member,
	CharacterData & config
)
{
	Create<uint8>(member, "character"          , config.character          );
	Create<uint8>(member, "costume"            , config.costume            );
	Create<bool >(member, "ignoreCostume"      , config.ignoreCostume      );
	Create<bool >(member, "forceFiles"         , config.forceFiles         );
	Create<uint8>(member, "forceFilesCharacter", config.forceFilesCharacter);
	Create<uint8>(member, "forceFilesCostume"  , config.forceFilesCostume  );

	CreateArray2<uint8, STYLE_COUNT, 2>(member, "styles", config.styles);

	CreateArray<uint8, STYLE_COUNT>(member, "styleIndices", config.styleIndices);

	CreateArray<byte16, STYLE_COUNT>(member, "styleButtons", config.styleButtons);

	Create<uint8>(member, "styleButtonIndex", config.styleButtonIndex);



	Create<uint8>(member, "meleeWeaponCount", config.meleeWeaponCount);

	CreateArray<uint8, MELEE_WEAPON_COUNT>(member, "meleeWeapons", config.meleeWeapons);

	Create<uint8>(member, "meleeWeaponIndex"      , config.meleeWeaponIndex      );
	Create<uint8>(member, "lastMeleeWeaponIndex"  , config.lastMeleeWeaponIndex  );
	Create<uint8>(member, "meleeWeaponSwitchType" , config.meleeWeaponSwitchType );
	Create<uint8>(member, "meleeWeaponSwitchStick", config.meleeWeaponSwitchStick);



	Create<uint8>(member, "rangedWeaponCount", config.rangedWeaponCount);

	CreateArray<uint8, RANGED_WEAPON_COUNT>(member, "rangedWeapons", config.rangedWeapons);

	Create<uint8>(member, "rangedWeaponIndex"      , config.rangedWeaponIndex      );
	Create<uint8>(member, "lastRangedWeaponIndex"  , config.lastRangedWeaponIndex  );
	Create<uint8>(member, "rangedWeaponSwitchType" , config.rangedWeaponSwitchType );
	Create<uint8>(member, "rangedWeaponSwitchStick", config.rangedWeaponSwitchStick);
}



void CreateMembers_PlayerDataContent
(
	rapidjson::Value & member,
	PlayerData & config
)
{
	Create<uint8 >(member, "collisionGroup"      , config.collisionGroup      );
	Create<uint16>(member, "button"              , config.button              );
	Create<uint8 >(member, "characterCount"      , config.characterCount      );
	Create<uint8 >(member, "characterIndex"      , config.characterIndex      );
	Create<uint8 >(member, "lastCharacterIndex"  , config.lastCharacterIndex  );
	Create<uint8 >(member, "activeCharacterIndex", config.activeCharacterIndex);



	auto & characterData = CreateArray2<struct_t, CHARACTER_COUNT, ENTITY_COUNT>(member, "characterData");

	for_all(characterIndex, CHARACTER_COUNT){
	for_all(entityIndex   , ENTITY_COUNT   )
	{
		auto & member2 = characterData[characterIndex][entityIndex];
		auto & config2 = config.characterData[characterIndex][entityIndex];

		CreateMembers_CharacterDataContent(member2, config2);
	}}



	Create<bool>(member, "removeBusyFlag", config.removeBusyFlag);

	CreateArray<byte16, 4>(member, "removeBusyFlagButtons", config.removeBusyFlagButtons);
}



template
<
	typename T,
	new_size_t length
>
rapidjson::Value & CreateMembers_Vec2
(
	rapidjson::Value & member,
	T (&name)[length],
	vec2 & config
)
{
	auto & newMember = Create<struct_t>(member, name);

	Create<float>(newMember, "x", config.x);
	Create<float>(newMember, "y", config.y);

	return newMember;
}

template
<
	typename T,
	new_size_t length
>
rapidjson::Value & CreateMembers_Vec4
(
	rapidjson::Value & member,
	T (&name)[length],
	vec4 & config
)
{
	auto & newMember = Create<struct_t>(member, name);

	Create<float>(newMember, "x", config.x);
	Create<float>(newMember, "y", config.y);
	Create<float>(newMember, "z", config.z);
	Create<float>(newMember, "a", config.a);

	return newMember;
}



void CreateMembers_TextureDataContent
(
	rapidjson::Value & member,
	Config::TextureData & config
)
{
	CreateMembers_Vec2(member, "size", config.size);
	CreateMembers_Vec2(member, "pos" , config.pos );
}

template
<
	typename T,
	new_size_t length
>
rapidjson::Value & CreateMembers_TextureData
(
	rapidjson::Value & member,
	T (&name)[length],
	Config::TextureData & config
)
{
	auto & newMember = Create<struct_t>(member, name);

	CreateMembers_TextureDataContent(newMember, config);

	return newMember;
}

template
<
	typename T,
	new_size_t length
>
rapidjson::Value & CreateMembers_TextureDataArray
(
	rapidjson::Value & member,
	T (&name)[length],
	Config::TextureData (&config)[5]
)
{
	auto & newMember = CreateArray<struct_t, 5>(member, name);

	for_all(index, 5)
	{
		auto & member2 = newMember[index];
		auto & config2 = config   [index];

		CreateMembers_TextureDataContent(member2, config2);
	}

	return newMember;
}



template
<
	typename T,
	new_size_t length
>
rapidjson::Value & CreateMembers_WeaponSwitchControllerTextureData
(
	rapidjson::Value & member,
	T (&name)[length],
	Config::WeaponSwitchControllerTextureData & config
)
{
	auto & newMember = Create<struct_t>(member, name);

	CreateMembers_TextureDataArray(newMember, "backgrounds", config.backgrounds);
	CreateMembers_TextureDataArray(newMember, "icons"      , config.icons      );
	CreateMembers_TextureDataArray(newMember, "highlights" , config.highlights );
	CreateMembers_TextureData     (newMember, "arrow"      , config.arrow      );

	return newMember;
}



void CreateMembers_ConfigCreateEnemyActorDataContent
(
	rapidjson::Value & member,
	ConfigCreateEnemyActorData & config
)
{
	Create<uint32>    (member, "enemy"           , config.enemy           );
	Create<uint32>    (member, "variant"         , config.variant         );
	CreateMembers_Vec4(member, "position"        , config.position        );
	Create<uint16>    (member, "rotation"        , config.rotation        );
	Create<bool  >    (member, "useMainActorData", config.useMainActorData);
	Create<uint16>    (member, "spawnMethod"     , config.spawnMethod     );
}



void CreateMembers_OverlayDataContent
(
	rapidjson::Value & member,
	Config::OverlayData & config
)
{
	Create<bool>         (member, "enable", config.enable);
	CreateMembers_Vec2   (member, "pos"   , config.pos   );
	CreateArray<float, 4>(member, "color" , config.color );
}



void CreateMembers_BarsDataContent
(
	rapidjson::Value & member,
	Config::BarsData & config
)
{
	Create<bool>      (member, "enable", config.enable);
	Create<bool>      (member, "run"   , config.run   );
	CreateMembers_Vec2(member, "size"  , config.size  );
	CreateMembers_Vec2(member, "pos"   , config.pos   );
	Create<uint32>    (member, "lastX" , config.lastX );
	Create<uint32>    (member, "lastY" , config.lastY );

	CreateArray<float, 4>(member, "hitColor"  , config.hitColor  );
	CreateArray<float, 4>(member, "magicColor", config.magicColor);
}



void CreateMembers_KeyDataContent
(
	rapidjson::Value & member,
	KeyData & config
)
{
	CreateArray<byte8, 4>(member, "keys", config.keys);

	Create<new_size_t>(member, "keyCount", config.keyCount);
}



void CreateMembers(Config & Prep_arg(config))
{
	{
		auto & member = Create<struct_t>(root, "Actor");
		auto & config = Prep_arg(config).Actor;

		Create<bool >(member, "enable"     , config.enable     );
		Create<uint8>(member, "playerCount", config.playerCount);

		auto & playerData = CreateArray<struct_t, PLAYER_COUNT>(member, "playerData");

		for_all(playerIndex, PLAYER_COUNT)
		{
			auto & member2 = playerData[playerIndex];
			auto & config2 = config.playerData[playerIndex];

			CreateMembers_PlayerDataContent(member2, config2);
		}
	}



	{
		auto & member = Create<struct_t>(root, "Arcade");
		auto & config = Prep_arg(config).Arcade;

		Create<bool  >(member, "enable"        , config.enable        );
		Create<uint32>(member, "mission"       , config.mission       );
		Create<uint32>(member, "mode"          , config.mode          );
		Create<uint32>(member, "room"          , config.room          );
		Create<bool  >(member, "ignoreRoom"    , config.ignoreRoom    );
		Create<uint32>(member, "position"      , config.position      );
		Create<bool  >(member, "ignorePosition", config.ignorePosition);
		Create<uint8 >(member, "floor"         , config.floor         );
		Create<uint16>(member, "level"         , config.level         );
		Create<float >(member, "hitPoints"     , config.hitPoints     );
		Create<float >(member, "magicPoints"   , config.magicPoints   );
		Create<uint8 >(member, "character"     , config.character     );
		Create<uint8 >(member, "costume"       , config.costume       );
		Create<uint32>(member, "style"         , config.style         );

		CreateArray<uint8, 4>(member, "weapons", config.weapons);
	}



	{
		auto & member = Create<struct_t>(root, "Artemis");
		auto & config = Prep_arg(config).Artemis;

		Create<bool>(member, "swapNormalShotAndMultiLock", config.swapNormalShotAndMultiLock);
		Create<bool>(member, "instantFullCharge"         , config.instantFullCharge         );
	}



	{
		auto & member = Create<struct_t>(root, "BossRush");
		auto & config = Prep_arg(config).BossRush;

		Create<bool>(member, "enable", config.enable);

		{
			auto & member2 = Create<struct_t>(member, "Mission5");
			auto & config2 = config.Mission5;

			Create<bool>(member2, "skipJester", config2.skipJester);
		}

		{
			auto & member2 = Create<struct_t>(member, "Mission12");
			auto & config2 = config.Mission12;

			Create<bool>(member2, "skipJester"     , config2.skipJester     );
			Create<bool>(member2, "skipGeryonPart1", config2.skipGeryonPart1);
		}

		{
			auto & member2 = Create<struct_t>(member, "Mission17");
			auto & config2 = config.Mission17;

			Create<bool>(member2, "skipJester", config2.skipJester);
		}

		{
			auto & member2 = Create<struct_t>(member, "Mission19");
			auto & config2 = config.Mission19;

			Create<bool>(member2, "skipArkhamPart1", config2.skipArkhamPart1);
		}
	}



	{
		auto & member = Create<struct_t>(root, "Color");
		auto & config = Prep_arg(config).Color;

		CreateArray2<uint8, 5, 4>(member, "airHike", config.airHike);



		{
			auto & member2 = Create<struct_t>(member, "Trickster");
			auto & config2 = config.Trickster;

			CreateArray<uint8, 4>(member2, "skyStar", config2.skyStar);
		}

		{
			auto & member2 = Create<struct_t>(member, "Royalguard");
			auto & config2 = config.Royalguard;

			CreateArray<uint8, 4>(member2, "ultimate", config2.ultimate);
		}

		{
			auto & member2 = Create<struct_t>(member, "Doppelganger");
			auto & config2 = config.Doppelganger;

			CreateArray<uint8, 4>(member2, "clone", config2.clone);
		}



		{
			auto & member2 = Create<struct_t>(member, "Aura");
			auto & config2 = config.Aura;

			CreateArray2<uint8, 5, 4>(member2, "dante"     , config2.dante     );
			CreateArray <uint8, 4   >(member2, "sparda"    , config2.sparda    );
			CreateArray2<uint8, 3, 4>(member2, "vergil"    , config2.vergil    );
			CreateArray <uint8, 4   >(member2, "neroAngelo", config2.neroAngelo);
		}
	}



	{
		auto & member = Create<struct_t>(root, "EbonyIvory");
		auto & config = Prep_arg(config).EbonyIvory;

		Create<bool>(member, "foursomeTime"     , config.foursomeTime     );
		Create<bool>(member, "infiniteRainStorm", config.infiniteRainStorm);
	}



	{
		auto & member = Create<struct_t>(root, "Rebellion");
		auto & config = Prep_arg(config).Rebellion;

		Create<bool>(member, "infiniteSwordPierce", config.infiniteSwordPierce);

		CreateArray<float, 2>(member, "stingerDuration"   , config.stingerDuration   );
		CreateArray<float, 2>(member, "stingerRange"      , config.stingerRange      );
		CreateArray<uint8, 2>(member, "airStingerCount"   , config.airStingerCount   );
		CreateArray<float, 2>(member, "airStingerDuration", config.airStingerDuration);
		CreateArray<float, 2>(member, "airStingerRange"   , config.airStingerRange   );
	}



	{
		auto & member = Create<struct_t>(root, "Royalguard");
		auto & config = Prep_arg(config).Royalguard;

		Create<bool>(member, "forceJustFrameRelease", config.forceJustFrameRelease);
	}



	{
		auto & member = Create<struct_t>(root, "Speed");
		auto & config = Prep_arg(config).Speed;

		Create<float>(member, "main"                  , config.main                  );
		Create<float>(member, "turbo"                 , config.turbo                 );
		Create<float>(member, "enemy"                 , config.enemy                 );
		Create<float>(member, "quicksilverPlayerActor", config.quicksilverPlayerActor);
		Create<float>(member, "quicksilverEnemyActor" , config.quicksilverEnemyActor );
		Create<float>(member, "human"                 , config.human                 );

		CreateArray<float, 6>(member, "devilDante" , config.devilDante );
		CreateArray<float, 5>(member, "devilVergil", config.devilVergil);
	}



	{
		auto & member = Create<struct_t>(root, "SummonedSwords");
		auto & config = Prep_arg(config).SummonedSwords;

		Create<bool>(member, "chronoSwords", config.chronoSwords);
	}



	{
		auto & member = Create<struct_t>(root, "Yamato");
		auto & config = Prep_arg(config).Yamato;

		CreateArray<uint8, 2>(member, "judgementCutCount", config.judgementCutCount);
	}



	{
		auto & member = Create<struct_t>(root, "YamatoForceEdge");
		auto & config = Prep_arg(config).YamatoForceEdge;

		Create<bool>(member, "infiniteRoundTrip", config.infiniteRoundTrip);

		CreateArray<float, 2>(member, "stingerDuration"   , config.stingerDuration   );
		CreateArray<float, 2>(member, "stingerRange"      , config.stingerRange      );
		CreateArray<uint8, 2>(member, "airStingerCount"   , config.airStingerCount   );
		CreateArray<float, 2>(member, "airStingerDuration", config.airStingerDuration);
		CreateArray<float, 2>(member, "airStingerRange"   , config.airStingerRange   );
	}



	auto & member = root;
	auto & config = Prep_arg(config);

	Create<bool >(member, "welcome"                  , config.welcome                  );
	Create<bool >(member, "hideBeowulfDante"         , config.hideBeowulfDante         );
	Create<bool >(member, "hideBeowulfVergil"        , config.hideBeowulfVergil        );
	Create<bool >(member, "airHikeCoreAbility"       , config.airHikeCoreAbility       );
	Create<uint8>(member, "crazyComboLevelMultiplier", config.crazyComboLevelMultiplier);
	Create<uint8>(member, "dotShadow"                , config.dotShadow                );
	Create<float>(member, "depleteQuicksilver"       , config.depleteQuicksilver       );
	Create<float>(member, "depleteDoppelganger"      , config.depleteDoppelganger      );
	Create<float>(member, "depleteDevil"             , config.depleteDevil             );
	Create<bool >(member, "noDevilForm"              , config.noDevilForm              );
	Create<float>(member, "orbReach"                 , config.orbReach                 );
	Create<bool >(member, "resetPermissions"         , config.resetPermissions         );
	Create<bool >(member, "infiniteHitPoints"        , config.infiniteHitPoints        );
	Create<bool >(member, "infiniteMagicPoints"      , config.infiniteMagicPoints      );
	Create<bool >(member, "disableTimer"             , config.disableTimer             );
	Create<bool >(member, "infiniteBullets"          , config.infiniteBullets          );
	Create<float>(member, "linearWeaponSwitchTimeout", config.linearWeaponSwitchTimeout);

	CreateArray<uint8, 2>(member, "airHikeCount"       , config.airHikeCount       );
	CreateArray<uint8, 2>(member, "kickJumpCount"      , config.kickJumpCount      );
	CreateArray<uint8, 2>(member, "wallHikeCount"      , config.wallHikeCount      );
	CreateArray<uint8, 2>(member, "dashCount"          , config.dashCount          );
	CreateArray<uint8, 2>(member, "skyStarCount"       , config.skyStarCount       );
	CreateArray<uint8, 2>(member, "airTrickCountDante" , config.airTrickCountDante );
	CreateArray<uint8, 2>(member, "airTrickCountVergil", config.airTrickCountVergil);
	CreateArray<uint8, 2>(member, "trickUpCount"       , config.trickUpCount       );
	CreateArray<uint8, 2>(member, "trickDownCount"     , config.trickDownCount     );

	CreateArray<float, CHANNEL::MAX>(member, "channelVolumes", config.channelVolumes);

	CreateMembers_WeaponSwitchControllerTextureData(member, "meleeWeaponSwitchControllerTextureData" , config.meleeWeaponSwitchControllerTextureData );
	CreateMembers_WeaponSwitchControllerTextureData(member, "rangedWeaponSwitchControllerTextureData", config.rangedWeaponSwitchControllerTextureData);

	Create<bool  >(member, "forceIconFocus"             , config.forceIconFocus             );
	Create<float >(member, "damagePlayerActorMultiplier", config.damagePlayerActorMultiplier);
	Create<float >(member, "damageEnemyActorMultiplier" , config.damageEnemyActorMultiplier );
	Create<uint32>(member, "damageStyleRank"            , config.damageStyleRank            );
	Create<bool  >(member, "skipIntro"                  , config.skipIntro                  );
	Create<bool  >(member, "skipCutscenes"              , config.skipCutscenes              );
	Create<bool  >(member, "preferLocalFiles"           , config.preferLocalFiles           );
	Create<float >(member, "frameRate"                  , config.frameRate                  );
	Create<uint8 >(member, "vSync"                      , config.vSync                      );
	Create<bool  >(member, "hideMouseCursor"            , config.hideMouseCursor            );
	Create<int32 >(member, "windowPosX"                 , config.windowPosX                 );
	Create<int32 >(member, "windowPosY"                 , config.windowPosY                 );
	Create<bool  >(member, "forceWindowFocus"           , config.forceWindowFocus           );
	Create<float >(member, "globalScale"                , config.globalScale                );



	Create<uint8>(member, "enemyCount", config.enemyCount);

	{
		auto & newMember = CreateArray<struct_t, 30>(member, "configCreateEnemyActorData");

		for_all(index, 30)
		{
			auto & member2 = newMember[index];
			auto & config2 = config.configCreateEnemyActorData[index];

			CreateMembers_ConfigCreateEnemyActorDataContent(member2, config2);
		}
	}

	Create<bool>(member, "enemyAutoSpawn", config.enemyAutoSpawn);



	{
		auto & member2 = Create<struct_t>(member, "mainOverlayData");
		auto & config2 = config.mainOverlayData;

		CreateMembers_OverlayDataContent(member2, config2);

		Create<bool>(member2, "showFocus"              , config2.showFocus              );
		Create<bool>(member2, "showFPS"                , config2.showFPS                );
		Create<bool>(member2, "showSizes"              , config2.showSizes              );
		Create<bool>(member2, "showFrameRateMultiplier", config2.showFrameRateMultiplier);
		Create<bool>(member2, "showEventData"          , config2.showEventData          );
		Create<bool>(member2, "showPosition"           , config2.showPosition           );
		Create<bool>(member2, "showRegionData"         , config2.showRegionData         );
	}



	{
		auto & member2 = Create<struct_t>(member, "missionOverlayData");
		auto & config2 = config.missionOverlayData;

		CreateMembers_OverlayDataContent(member2, config2);
	}

	{
		auto & member2 = Create<struct_t>(member, "bossLadyActionsOverlayData");
		auto & config2 = config.bossLadyActionsOverlayData;

		CreateMembers_OverlayDataContent(member2, config2);
	}

	{
		auto & member2 = Create<struct_t>(member, "bossVergilActionsOverlayData");
		auto & config2 = config.bossVergilActionsOverlayData;

		CreateMembers_OverlayDataContent(member2, config2);
	}



	Create<float>     (member, "kalinaAnnHookGrenadeHeight", config.kalinaAnnHookGrenadeHeight);
	Create<float>     (member, "kalinaAnnHookGrenadeTime"  , config.kalinaAnnHookGrenadeTime  );
	CreateMembers_Vec4(member, "kalinaAnnHookMultiplier"   , config.kalinaAnnHookMultiplier   );



	Create<bool >(member, "cameraInvertX"                     , config.cameraInvertX                     );
	Create<uint8>(member, "cameraAutoAdjust"                  , config.cameraAutoAdjust                  );
	Create<bool >(member, "disableCenterCamera"               , config.disableCenterCamera               );
	Create<bool >(member, "disableBossCamera"                 , config.disableBossCamera                 );
	Create<bool >(member, "enableBossLadyFixes"               , config.enableBossLadyFixes               );
	Create<bool >(member, "enableBossVergilFixes"             , config.enableBossVergilFixes             );
	Create<bool >(member, "enablePVPFixes"                    , config.enablePVPFixes                    );
	Create<bool >(member, "hideMainHUD"                       , config.hideMainHUD                       );
	Create<bool >(member, "hideLockOn"                        , config.hideLockOn                        );
	Create<bool >(member, "hideBossHUD"                       , config.hideBossHUD                       );
	Create<bool >(member, "soundIgnoreEnemyData"              , config.soundIgnoreEnemyData              );
	Create<bool >(member, "enableRebellionAirStinger"         , config.enableRebellionAirStinger         );
	Create<bool >(member, "enableRebellionNewDrive"           , config.enableRebellionNewDrive           );
	Create<bool >(member, "enableRebellionQuickDrive"         , config.enableRebellionQuickDrive         );
	Create<bool >(member, "enableCerberusAirRevolver"         , config.enableCerberusAirRevolver         );
	Create<bool >(member, "enableNevanNewVortex"              , config.enableNevanNewVortex              );
	Create<bool >(member, "enableYamatoVergilNewJudgementCut" , config.enableYamatoVergilNewJudgementCut );
	Create<bool >(member, "enableBeowulfVergilAirRisingSun"   , config.enableBeowulfVergilAirRisingSun   );
	Create<bool >(member, "enableBeowulfVergilAirLunarPhase"  , config.enableBeowulfVergilAirLunarPhase  );
	Create<bool >(member, "enableYamatoForceEdgeNewComboPart4", config.enableYamatoForceEdgeNewComboPart4);
	Create<bool >(member, "enableYamatoForceEdgeAirStinger"   , config.enableYamatoForceEdgeAirStinger   );
	Create<bool >(member, "enableYamatoForceEdgeNewRoundTrip" , config.enableYamatoForceEdgeNewRoundTrip );
	Create<uint8>(member, "dergil"                            , config.dergil                            );

	CreateArray<uint8, 2>(member, "beowulfVergilAirRisingSunCount", config.beowulfVergilAirRisingSunCount);

	Create<bool>(member, "forceVisibleHUD", config.forceVisibleHUD);



	{
		auto & member = CreateArray<struct_t, PLAYER_COUNT>(root, "barsData");
		auto & config = Prep_arg(config).barsData;

		for_all(playerIndex, PLAYER_COUNT)
		{
			auto & member2 = member[playerIndex];
			auto & config2 = config[playerIndex];

			CreateMembers_BarsDataContent(member2, config2);
		}
	}



	Create<bool>(member, "forceSyncHitMagicPoints", config.forceSyncHitMagicPoints);
	Create<bool>(member, "updateLockOns"          , config.updateLockOns          );
	Create<bool>(member, "showCredits"            , config.showCredits            );

	{
		auto & member = CreateArray<struct_t, 3>(root, "keyData");
		auto & config = Prep_arg(config).keyData;

		for_all(index, 3)
		{
			auto & member2 = member[index];
			auto & config2 = config[index];

			CreateMembers_KeyDataContent(member2, config2);
		}
	}



	Create<bool >(member, "absoluteUnit"               , config.absoluteUnit               );
	CreateString (member, "gamepadName"                , config.gamepadName                );
	Create<byte8>(member, "gamepadButton"              , config.gamepadButton              );
	Create<bool >(member, "disablePlayerActorIdleTimer", config.disablePlayerActorIdleTimer);
}

#pragma endregion



#pragma region ToJSON

void ToJSON_CharacterData
(
	rapidjson::Value & member,
	CharacterData & config
)
{
	Set<uint8>(member["character"          ], config.character          );
	Set<uint8>(member["costume"            ], config.costume            );
	Set<bool >(member["ignoreCostume"      ], config.ignoreCostume      );
	Set<bool >(member["forceFiles"         ], config.forceFiles         );
	Set<uint8>(member["forceFilesCharacter"], config.forceFilesCharacter);
	Set<uint8>(member["forceFilesCostume"  ], config.forceFilesCostume  );

	SetArray2<uint8 , STYLE_COUNT, 2>(member["styles"      ], config.styles      );
	SetArray <uint8 , STYLE_COUNT   >(member["styleIndices"], config.styleIndices);
	SetArray <byte16, STYLE_COUNT   >(member["styleButtons"], config.styleButtons);

	Set<uint8>(member["styleButtonIndex"], config.styleButtonIndex);



	Set<uint8>(member["meleeWeaponCount"], config.meleeWeaponCount);

	SetArray<uint8, MELEE_WEAPON_COUNT>(member["meleeWeapons"], config.meleeWeapons);

	Set<uint8>(member["meleeWeaponIndex"      ], config.meleeWeaponIndex      );
	Set<uint8>(member["lastMeleeWeaponIndex"  ], config.lastMeleeWeaponIndex  );
	Set<uint8>(member["meleeWeaponSwitchType" ], config.meleeWeaponSwitchType );
	Set<uint8>(member["meleeWeaponSwitchStick"], config.meleeWeaponSwitchStick);



	Set<uint8>(member["rangedWeaponCount"], config.rangedWeaponCount);

	SetArray<uint8, RANGED_WEAPON_COUNT>(member["rangedWeapons"], config.rangedWeapons);

	Set<uint8>(member["rangedWeaponIndex"      ], config.rangedWeaponIndex      );
	Set<uint8>(member["lastRangedWeaponIndex"  ], config.lastRangedWeaponIndex  );
	Set<uint8>(member["rangedWeaponSwitchType" ], config.rangedWeaponSwitchType );
	Set<uint8>(member["rangedWeaponSwitchStick"], config.rangedWeaponSwitchStick);
}



void ToJSON_PlayerData
(
	rapidjson::Value & member,
	PlayerData & config
)
{
	Set<uint8 >(member["collisionGroup"      ], config.collisionGroup      );
	Set<byte16>(member["button"              ], config.button              );
	Set<uint8 >(member["characterCount"      ], config.characterCount      );
	Set<uint8 >(member["characterIndex"      ], config.characterIndex      );
	Set<uint8 >(member["lastCharacterIndex"  ], config.lastCharacterIndex  );
	Set<uint8 >(member["activeCharacterIndex"], config.activeCharacterIndex);



	for_all(characterIndex, CHARACTER_COUNT){
	for_all(entityIndex   , ENTITY_COUNT   )
	{
		ToJSON_CharacterData
		(
			member["characterData"][characterIndex][entityIndex],
			config.characterData   [characterIndex][entityIndex]
		);
	}}



	Set<bool>(member["removeBusyFlag"], config.removeBusyFlag);

	SetArray<byte16, 4>(member["removeBusyFlagButtons"], config.removeBusyFlagButtons);
}



void ToJSON_Vec2
(
	rapidjson::Value & member,
	vec2 & config
)
{
	Set<float>(member["x"], config.x);
	Set<float>(member["y"], config.y);
}

void ToJSON_Vec4
(
	rapidjson::Value & member,
	vec4 & config
)
{
	Set<float>(member["x"], config.x);
	Set<float>(member["y"], config.y);
	Set<float>(member["z"], config.z);
	Set<float>(member["a"], config.a);
}



void ToJSON_TextureData
(
	rapidjson::Value & member,
	Config::TextureData & config
)
{
	ToJSON_Vec2(member["size"], config.size);
	ToJSON_Vec2(member["pos" ], config.pos );
}

void ToJSON_TextureDataArray
(
	rapidjson::Value & member,
	Config::TextureData (&config)[5]
)
{
	for_all(index, 5)
	{
		auto & member2 = member[index];
		auto & config2 = config[index];

		ToJSON_TextureData(member2, config2);
	}
}

void ToJSON_WeaponSwitchControllerTextureData
(
	rapidjson::Value & member,
	Config::WeaponSwitchControllerTextureData & config
)
{
	ToJSON_TextureDataArray(member["backgrounds"], config.backgrounds);
	ToJSON_TextureDataArray(member["icons"      ], config.icons      );
	ToJSON_TextureDataArray(member["highlights" ], config.highlights );
	ToJSON_TextureData     (member["arrow"      ], config.arrow      );
}



void ToJSON_ConfigCreateEnemyActorData
(
	rapidjson::Value & member,
	ConfigCreateEnemyActorData & config
)
{
	Set<uint32>(member["enemy"           ], config.enemy           );
	Set<uint32>(member["variant"         ], config.variant         );
	ToJSON_Vec4(member["position"        ], config.position        );
	Set<uint16>(member["rotation"        ], config.rotation        );
	Set<bool  >(member["useMainActorData"], config.useMainActorData);
	Set<uint16>(member["spawnMethod"     ], config.spawnMethod     );
}



void ToJSON_OverlayData
(
	rapidjson::Value & member,
	Config::OverlayData & config
)
{
	Set<bool>(member["enable"], config.enable);

	ToJSON_Vec2(member["pos"], config.pos);

	SetArray<float, 4>(member["color"], config.color);
}

void ToJSON_MainOverlayData
(
	rapidjson::Value & member,
	Config::MainOverlayData & config
)
{
	ToJSON_OverlayData(member, config);

	Set<bool>(member["showFocus"              ], config.showFocus              );
	Set<bool>(member["showFPS"                ], config.showFPS                );
	Set<bool>(member["showSizes"              ], config.showSizes              );
	Set<bool>(member["showFrameRateMultiplier"], config.showFrameRateMultiplier);
	Set<bool>(member["showEventData"          ], config.showEventData          );
	Set<bool>(member["showPosition"           ], config.showPosition           );
	Set<bool>(member["showRegionData"         ], config.showRegionData         );
}



void ToJSON_BarsData
(
	rapidjson::Value & member,
	Config::BarsData & config
)
{
	Set<bool>(member["enable"], config.enable);
	Set<bool>(member["run"], config.run);

	ToJSON_Vec2(member["size"], config.size);
	ToJSON_Vec2(member["pos" ], config.pos );

	Set<uint32>(member["lastX"], config.lastX);
	Set<uint32>(member["lastY"], config.lastY);

	SetArray<float, 4>(member["hitColor"  ], config.hitColor  );
	SetArray<float, 4>(member["magicColor"], config.magicColor);
}



void ToJSON_KeyData
(
	rapidjson::Value & member,
	KeyData & config
)
{
	SetArray<byte8, 4>(member["keys"], config.keys);

	Set<new_size_t>(member["keyCount"], config.keyCount);
}



void ToJSON(Config & Prep_arg(config))
{
	{
		auto & member = root["Actor"];
		auto & config = Prep_arg(config).Actor;

		Set<bool >(member["enable"     ], config.enable     );
		Set<uint8>(member["playerCount"], config.playerCount);



		for_all(playerIndex, PLAYER_COUNT)
		{
			ToJSON_PlayerData
			(
				member["playerData"][playerIndex],
				config.playerData   [playerIndex]
			);
		}
	}



	{
		auto & member = root["Arcade"];
		auto & config = Prep_arg(config).Arcade;

		Set<bool  >(member["enable"        ], config.enable        );
		Set<uint32>(member["mission"       ], config.mission       );
		Set<uint32>(member["mode"          ], config.mode          );
		Set<uint32>(member["room"          ], config.room          );
		Set<bool  >(member["ignoreRoom"    ], config.ignoreRoom    );
		Set<uint32>(member["position"      ], config.position      );
		Set<bool  >(member["ignorePosition"], config.ignorePosition);
		Set<uint8 >(member["floor"         ], config.floor         );
		Set<uint16>(member["level"         ], config.level         );
		Set<float >(member["hitPoints"     ], config.hitPoints     );
		Set<float >(member["magicPoints"   ], config.magicPoints   );
		Set<uint8 >(member["character"     ], config.character     );
		Set<uint8 >(member["costume"       ], config.costume       );
		Set<uint32>(member["style"         ], config.style         );

		SetArray<uint8 , 4>(member["weapons"], config.weapons);
	}



	{
		auto & member = root["Artemis"];
		auto & config = Prep_arg(config).Artemis;

		Set<bool>(member["swapNormalShotAndMultiLock"], config.swapNormalShotAndMultiLock);
		Set<bool>(member["instantFullCharge"         ], config.instantFullCharge         );
	}



	{
		auto & member = root["BossRush"];
		auto & config = Prep_arg(config).BossRush;

		Set<bool>(member["enable"], config.enable);

		{
			auto & member2 = member["Mission5"];
			auto & config2 = config.Mission5;

			Set<bool>(member2["skipJester"], config2.skipJester);
		}

		{
			auto & member2 = member["Mission12"];
			auto & config2 = config.Mission12;

			Set<bool>(member2["skipJester"     ], config2.skipJester     );
			Set<bool>(member2["skipGeryonPart1"], config2.skipGeryonPart1);
		}

		{
			auto & member2 = member["Mission17"];
			auto & config2 = config.Mission17;

			Set<bool>(member2["skipJester"], config2.skipJester);
		}

		{
			auto & member2 = member["Mission19"];
			auto & config2 = config.Mission19;

			Set<bool>(member2["skipArkhamPart1"], config2.skipArkhamPart1);
		}
	}



	{
		auto & member = root["Color"];
		auto & config = Prep_arg(config).Color;

		SetArray2<uint8, 5, 4>(member["airHike"], config.airHike);

		{
			auto & member2 = member["Trickster"];
			auto & config2 = config.Trickster;

			SetArray<uint8, 4>(member2["skyStar"], config2.skyStar);
		}

		{
			auto & member2 = member["Royalguard"];
			auto & config2 = config.Royalguard;

			SetArray<uint8, 4>(member2["ultimate"], config2.ultimate);
		}

		{
			auto & member2 = member["Doppelganger"];
			auto & config2 = config.Doppelganger;

			SetArray<uint8, 4>(member2["clone"], config2.clone);
		}

		{
			auto & member2 = member["Aura"];
			auto & config2 = config.Aura;

			SetArray2<uint8, 5, 4>(member2["dante"     ], config2.dante     );
			SetArray <uint8, 4   >(member2["sparda"    ], config2.sparda    );
			SetArray2<uint8, 3, 4>(member2["vergil"    ], config2.vergil    );
			SetArray <uint8, 4   >(member2["neroAngelo"], config2.neroAngelo);
		}
	}



	{
		auto & member = root["EbonyIvory"];
		auto & config = Prep_arg(config).EbonyIvory;

		Set<bool>(member["foursomeTime"     ], config.foursomeTime     );
		Set<bool>(member["infiniteRainStorm"], config.infiniteRainStorm);
	}



	{
		auto & member = root["Rebellion"];
		auto & config = Prep_arg(config).Rebellion;

		Set<bool>(member["infiniteSwordPierce"], config.infiniteSwordPierce);

		SetArray<float, 2>(member["stingerDuration"   ], config.stingerDuration   );
		SetArray<float, 2>(member["stingerRange"      ], config.stingerRange      );
		SetArray<uint8, 2>(member["airStingerCount"   ], config.airStingerCount   );
		SetArray<float, 2>(member["airStingerDuration"], config.airStingerDuration);
		SetArray<float, 2>(member["airStingerRange"   ], config.airStingerRange   );
	}



	{
		auto & member = root["Royalguard"];
		auto & config = Prep_arg(config).Royalguard;

		Set<bool>(member["forceJustFrameRelease"], config.forceJustFrameRelease);
	}



	{
		auto & member = root["Speed"];
		auto & config = Prep_arg(config).Speed;

		Set<float>(member["main"                  ], config.main                  );
		Set<float>(member["turbo"                 ], config.turbo                 );
		Set<float>(member["enemy"                 ], config.enemy                 );
		Set<float>(member["quicksilverPlayerActor"], config.quicksilverPlayerActor);
		Set<float>(member["quicksilverEnemyActor" ], config.quicksilverEnemyActor );
		Set<float>(member["human"                 ], config.human                 );

		SetArray<float, 6>(member["devilDante" ], config.devilDante );
		SetArray<float, 5>(member["devilVergil"], config.devilVergil);
	}



	{
		auto & member = root["SummonedSwords"];
		auto & config = Prep_arg(config).SummonedSwords;

		Set<bool>(member["chronoSwords"], config.chronoSwords);
	}



	{
		auto & member = root["Yamato"];
		auto & config = Prep_arg(config).Yamato;

		SetArray<uint8, 2>(member["judgementCutCount"], config.judgementCutCount);
	}



	{
		auto & member = root["YamatoForceEdge"];
		auto & config = Prep_arg(config).YamatoForceEdge;

		Set<bool>(member["infiniteRoundTrip"], config.infiniteRoundTrip);

		SetArray<float, 2>(member["stingerDuration"   ], config.stingerDuration   );
		SetArray<float, 2>(member["stingerRange"      ], config.stingerRange      );
		SetArray<uint8, 2>(member["airStingerCount"   ], config.airStingerCount   );
		SetArray<float, 2>(member["airStingerDuration"], config.airStingerDuration);
		SetArray<float, 2>(member["airStingerRange"   ], config.airStingerRange   );
	}



	auto & member = root;
	auto & config = Prep_arg(config);

	Set<bool >(member["welcome"                  ], config.welcome                  );
	Set<bool >(member["hideBeowulfDante"         ], config.hideBeowulfDante         );
	Set<bool >(member["hideBeowulfVergil"        ], config.hideBeowulfVergil        );
	Set<bool >(member["airHikeCoreAbility"       ], config.airHikeCoreAbility       );
	Set<uint8>(member["crazyComboLevelMultiplier"], config.crazyComboLevelMultiplier);
	Set<uint8>(member["dotShadow"                ], config.dotShadow                );
	Set<float>(member["depleteQuicksilver"       ], config.depleteQuicksilver       );
	Set<float>(member["depleteDoppelganger"      ], config.depleteDoppelganger      );
	Set<float>(member["depleteDevil"             ], config.depleteDevil             );
	Set<bool >(member["noDevilForm"              ], config.noDevilForm              );
	Set<float>(member["orbReach"                 ], config.orbReach                 );
	Set<bool >(member["resetPermissions"         ], config.resetPermissions         );
	Set<bool >(member["infiniteHitPoints"        ], config.infiniteHitPoints        );
	Set<bool >(member["infiniteMagicPoints"      ], config.infiniteMagicPoints      );
	Set<bool >(member["disableTimer"             ], config.disableTimer             );
	Set<bool >(member["infiniteBullets"          ], config.infiniteBullets          );
	Set<float>(member["linearWeaponSwitchTimeout"], config.linearWeaponSwitchTimeout);

	SetArray<uint8, 2>(member["airHikeCount"       ], config.airHikeCount       );
	SetArray<uint8, 2>(member["kickJumpCount"      ], config.kickJumpCount      );
	SetArray<uint8, 2>(member["wallHikeCount"      ], config.wallHikeCount      );
	SetArray<uint8, 2>(member["dashCount"          ], config.dashCount          );
	SetArray<uint8, 2>(member["skyStarCount"       ], config.skyStarCount       );
	SetArray<uint8, 2>(member["airTrickCountDante" ], config.airTrickCountDante );
	SetArray<uint8, 2>(member["airTrickCountVergil"], config.airTrickCountVergil);
	SetArray<uint8, 2>(member["trickUpCount"       ], config.trickUpCount       );
	SetArray<uint8, 2>(member["trickDownCount"     ], config.trickDownCount     );

	SetArray<float, CHANNEL::MAX>(member["channelVolumes"], config.channelVolumes);



	ToJSON_WeaponSwitchControllerTextureData(member["meleeWeaponSwitchControllerTextureData" ], config.meleeWeaponSwitchControllerTextureData );
	ToJSON_WeaponSwitchControllerTextureData(member["rangedWeaponSwitchControllerTextureData"], config.rangedWeaponSwitchControllerTextureData);



	Set<bool  >(member["forceIconFocus"             ], config.forceIconFocus             );
	Set<float >(member["damagePlayerActorMultiplier"], config.damagePlayerActorMultiplier);
	Set<float >(member["damageEnemyActorMultiplier" ], config.damageEnemyActorMultiplier );
	Set<uint32>(member["damageStyleRank"            ], config.damageStyleRank            );
	Set<bool  >(member["skipIntro"                  ], config.skipIntro                  );
	Set<bool  >(member["skipCutscenes"              ], config.skipCutscenes              );
	Set<bool  >(member["preferLocalFiles"           ], config.preferLocalFiles           );
	Set<float >(member["frameRate"                  ], config.frameRate                  );
	Set<uint8 >(member["vSync"                      ], config.vSync                      );
	Set<bool  >(member["hideMouseCursor"            ], config.hideMouseCursor            );
	Set<int32 >(member["windowPosX"                 ], config.windowPosX                 );
	Set<int32 >(member["windowPosY"                 ], config.windowPosY                 );
	Set<bool  >(member["forceWindowFocus"           ], config.forceWindowFocus           );
	Set<float >(member["globalScale"                ], config.globalScale                );



	Set<uint8>(member["enemyCount"], config.enemyCount);

	for_all(index, 30)
	{
		ToJSON_ConfigCreateEnemyActorData(member["configCreateEnemyActorData"][index], config.configCreateEnemyActorData[index]);
	}

	Set<bool>(member["enemyAutoSpawn"], config.enemyAutoSpawn);



	ToJSON_MainOverlayData(member["mainOverlayData"             ], config.mainOverlayData             );
	ToJSON_OverlayData    (member["missionOverlayData"          ], config.missionOverlayData          );
	ToJSON_OverlayData    (member["bossLadyActionsOverlayData"  ], config.bossLadyActionsOverlayData  );
	ToJSON_OverlayData    (member["bossVergilActionsOverlayData"], config.bossVergilActionsOverlayData);



	Set<float>(member["kalinaAnnHookGrenadeHeight"        ], config.kalinaAnnHookGrenadeHeight        );
	Set<float>(member["kalinaAnnHookGrenadeTime"          ], config.kalinaAnnHookGrenadeTime          );
	Set<vec4 >(member["kalinaAnnHookMultiplier"           ], config.kalinaAnnHookMultiplier           );
	Set<bool >(member["cameraInvertX"                     ], config.cameraInvertX                     );
	Set<uint8>(member["cameraAutoAdjust"                  ], config.cameraAutoAdjust                  );
	Set<bool >(member["disableCenterCamera"               ], config.disableCenterCamera               );
	Set<bool >(member["disableBossCamera"                 ], config.disableBossCamera                 );
	Set<bool >(member["enableBossLadyFixes"               ], config.enableBossLadyFixes               );
	Set<bool >(member["enableBossVergilFixes"             ], config.enableBossVergilFixes             );
	Set<bool >(member["enablePVPFixes"                    ], config.enablePVPFixes                    );
	Set<bool >(member["hideMainHUD"                       ], config.hideMainHUD                       );
	Set<bool >(member["hideLockOn"                        ], config.hideLockOn                        );
	Set<bool >(member["hideBossHUD"                       ], config.hideBossHUD                       );
	Set<bool >(member["soundIgnoreEnemyData"              ], config.soundIgnoreEnemyData              );
	Set<bool >(member["enableRebellionAirStinger"         ], config.enableRebellionAirStinger         );
	Set<bool >(member["enableRebellionNewDrive"           ], config.enableRebellionNewDrive           );
	Set<bool >(member["enableRebellionQuickDrive"         ], config.enableRebellionQuickDrive         );
	Set<bool >(member["enableCerberusAirRevolver"         ], config.enableCerberusAirRevolver         );
	Set<bool >(member["enableNevanNewVortex"              ], config.enableNevanNewVortex              );
	Set<bool >(member["enableYamatoVergilNewJudgementCut" ], config.enableYamatoVergilNewJudgementCut );
	Set<bool >(member["enableBeowulfVergilAirRisingSun"   ], config.enableBeowulfVergilAirRisingSun   );
	Set<bool >(member["enableBeowulfVergilAirLunarPhase"  ], config.enableBeowulfVergilAirLunarPhase  );
	Set<bool >(member["enableYamatoForceEdgeNewComboPart4"], config.enableYamatoForceEdgeNewComboPart4);
	Set<bool >(member["enableYamatoForceEdgeAirStinger"   ], config.enableYamatoForceEdgeAirStinger   );
	Set<bool >(member["enableYamatoForceEdgeNewRoundTrip" ], config.enableYamatoForceEdgeNewRoundTrip );
	Set<uint8>(member["dergil"                            ], config.dergil                            );

	SetArray<uint8, 2>(member["beowulfVergilAirRisingSunCount"], config.beowulfVergilAirRisingSunCount);

	Set<bool>(member["forceVisibleHUD"], config.forceVisibleHUD);



	for_all(playerIndex, PLAYER_COUNT)
	{
		ToJSON_BarsData(member["barsData"][playerIndex], config.barsData[playerIndex]);
	}



	Set<bool>(member["forceSyncHitMagicPoints"], config.forceSyncHitMagicPoints);
	Set<bool>(member["updateLockOns"          ], config.updateLockOns          );
	Set<bool>(member["showCredits"            ], config.showCredits            );



	for_all(index, 3)
	{
		ToJSON_KeyData(member["keyData"][index], config.keyData[index]);
	}



	Set<bool >(member["absoluteUnit"               ], config.absoluteUnit               );
	SetString (member["gamepadName"                ], config.gamepadName                );
	Set<byte8>(member["gamepadButton"              ], config.gamepadButton              );
	Set<bool >(member["disablePlayerActorIdleTimer"], config.disablePlayerActorIdleTimer);
}

#pragma endregion



#pragma region ToConfig

void ToConfig_CharacterData
(
	CharacterData & config,
	rapidjson::Value & member
)
{
	config.character           = Get<uint8>(member["character"          ]);
	config.costume             = Get<uint8>(member["costume"            ]);
	config.ignoreCostume       = Get<bool >(member["ignoreCostume"      ]);
	config.forceFiles          = Get<bool >(member["forceFiles"         ]);
	config.forceFilesCharacter = Get<uint8>(member["forceFilesCharacter"]);
	config.forceFilesCostume   = Get<uint8>(member["forceFilesCostume"  ]);



	GetArray2<uint8 , STYLE_COUNT, 2>(config.styles      , member["styles"      ]);
	GetArray <uint8 , STYLE_COUNT   >(config.styleIndices, member["styleIndices"]);
	GetArray <byte16, STYLE_COUNT   >(config.styleButtons, member["styleButtons"]);

	config.styleButtonIndex = Get<uint8>(member["styleButtonIndex"]);



	config.meleeWeaponCount = Get<uint8>(member["meleeWeaponCount"]);

	GetArray<uint8, MELEE_WEAPON_COUNT>(config.meleeWeapons, member["meleeWeapons"]);

	config.meleeWeaponIndex       = Get<uint8>(member["meleeWeaponIndex"      ]);
	config.lastMeleeWeaponIndex   = Get<uint8>(member["lastMeleeWeaponIndex"  ]);
	config.meleeWeaponSwitchType  = Get<uint8>(member["meleeWeaponSwitchType" ]);
	config.meleeWeaponSwitchStick = Get<uint8>(member["meleeWeaponSwitchStick"]);



	config.rangedWeaponCount = Get<uint8>(member["rangedWeaponCount"]);

	GetArray<uint8, RANGED_WEAPON_COUNT>(config.rangedWeapons, member["rangedWeapons"]);

	config.rangedWeaponIndex       = Get<uint8>(member["rangedWeaponIndex"      ]);
	config.lastRangedWeaponIndex   = Get<uint8>(member["lastRangedWeaponIndex"  ]);
	config.rangedWeaponSwitchType  = Get<uint8>(member["rangedWeaponSwitchType" ]);
	config.rangedWeaponSwitchStick = Get<uint8>(member["rangedWeaponSwitchStick"]);
}



void ToConfig_PlayerData
(
	PlayerData & config,
	rapidjson::Value & member
)
{
	config.collisionGroup       = Get<uint8 >(member["collisionGroup"      ]);
	config.button               = Get<byte16>(member["button"              ]);
	config.characterCount       = Get<uint8 >(member["characterCount"      ]);
	config.characterIndex       = Get<uint8 >(member["characterIndex"      ]);
	config.lastCharacterIndex   = Get<uint8 >(member["lastCharacterIndex"  ]);
	config.activeCharacterIndex = Get<uint8 >(member["activeCharacterIndex"]);



	for_all(characterIndex, CHARACTER_COUNT){
	for_all(entityIndex   , ENTITY_COUNT   )
	{
		ToConfig_CharacterData
		(
			config.characterData   [characterIndex][entityIndex],
			member["characterData"][characterIndex][entityIndex]
		);
	}}



	config.removeBusyFlag = Get<bool>(member["removeBusyFlag"]);

	GetArray<byte16, 4>(config.removeBusyFlagButtons, member["removeBusyFlagButtons"]);
}



void ToConfig_Vec2
(
	vec2 & config,
	rapidjson::Value & member
)
{
	config.x = Get<float>(member["x"]);
	config.y = Get<float>(member["y"]);
}

void ToConfig_Vec4
(
	vec4 & config,
	rapidjson::Value & member
)
{
	config.x = Get<float>(member["x"]);
	config.y = Get<float>(member["y"]);
	config.z = Get<float>(member["z"]);
	config.a = Get<float>(member["a"]);
}



void ToConfig_TextureData
(
	Config::TextureData & config,
	rapidjson::Value & member
)
{
	ToConfig_Vec2(config.size, member["size"]);
	ToConfig_Vec2(config.pos , member["pos" ]);
}

void ToConfig_TextureDataArray
(
	Config::TextureData (&config)[5],
	rapidjson::Value & member
)
{
	for_all(index, 5)
	{
		auto & config2 = config[index];
		auto & member2 = member[index];

		ToConfig_TextureData(config2, member2);
	}
}

void ToConfig_WeaponSwitchControllerTextureData
(
	Config::WeaponSwitchControllerTextureData & config,
	rapidjson::Value & member
)
{
	ToConfig_TextureDataArray(config.backgrounds, member["backgrounds"]);
	ToConfig_TextureDataArray(config.icons      , member["icons"      ]);
	ToConfig_TextureDataArray(config.highlights , member["highlights" ]);
	ToConfig_TextureData     (config.arrow      , member["arrow"      ]);
}



void ToConfig_ConfigCreateEnemyActorData
(
	ConfigCreateEnemyActorData & config,
	rapidjson::Value & member
)
{
	config.enemy   = Get<uint32>(member["enemy"  ]);
	config.variant = Get<uint32>(member["variant"]);

	ToConfig_Vec4(config.position, member["position"]);

	config.rotation         = Get<uint16>(member["rotation"        ]);
	config.useMainActorData = Get<bool  >(member["useMainActorData"]);
	config.spawnMethod      = Get<uint16>(member["spawnMethod"     ]);
}



void ToConfig_OverlayData
(
	Config::OverlayData & config,
	rapidjson::Value & member
)
{
	config.enable = Get<bool>(member["enable"]);

	ToConfig_Vec2(config.pos, member["pos"]);

	GetArray<float, 4>(config.color, member["color"]);
}

void ToConfig_MainOverlayData
(
	Config::MainOverlayData & config,
	rapidjson::Value & member
)
{
	ToConfig_OverlayData(config, member);

	config.showFocus               = Get<bool>(member["showFocus"              ]);
	config.showFPS                 = Get<bool>(member["showFPS"                ]);
	config.showSizes               = Get<bool>(member["showSizes"              ]);
	config.showFrameRateMultiplier = Get<bool>(member["showFrameRateMultiplier"]);
	config.showEventData           = Get<bool>(member["showEventData"          ]);
	config.showPosition            = Get<bool>(member["showPosition"           ]);
	config.showRegionData          = Get<bool>(member["showRegionData"         ]);
}



void ToConfig_BarsData
(
	Config::BarsData & config,
	rapidjson::Value & member
)
{
	config.enable = Get<bool>(member["enable"]);
	config.run    = Get<bool>(member["run"   ]);

	ToConfig_Vec2(config.size, member["size"]);
	ToConfig_Vec2(config.pos , member["pos" ]);

	config.lastX = Get<uint32>(member["lastX"]);
	config.lastY = Get<uint32>(member["lastY"]);

	GetArray<float, 4>(config.hitColor  , member["hitColor"  ]);
	GetArray<float, 4>(config.magicColor, member["magicColor"]);
}



void ToConfig_KeyData
(
	KeyData & config,
	rapidjson::Value & member
)
{
	GetArray<byte8, 4>(config.keys, member["keys"]);

	config.keyCount = Get<new_size_t>(member["keyCount"]);
}



void ToConfig(Config & Prep_arg(config))
{
	{
		auto & config = Prep_arg(config).Actor;
		auto & member = root["Actor"];

		config.enable      = Get<bool >(member["enable"     ]);
		config.playerCount = Get<uint8>(member["playerCount"]);

		for_all(playerIndex, PLAYER_COUNT)
		{
			ToConfig_PlayerData
			(
				config.playerData   [playerIndex],
				member["playerData"][playerIndex]
			);
		}
	}



	{
		auto & config = Prep_arg(config).Arcade;
		auto & member = root["Arcade"];

		config.enable         = Get<bool  >(member["enable"        ]);
		config.mission        = Get<uint32>(member["mission"       ]);
		config.mode           = Get<uint32>(member["mode"          ]);
		config.room           = Get<uint32>(member["room"          ]);
		config.ignoreRoom     = Get<bool  >(member["ignoreRoom"    ]);
		config.position       = Get<uint32>(member["position"      ]);
		config.ignorePosition = Get<bool  >(member["ignorePosition"]);
		config.floor          = Get<uint8 >(member["floor"         ]);
		config.level          = Get<uint16>(member["level"         ]);
		config.hitPoints      = Get<float >(member["hitPoints"     ]);
		config.magicPoints    = Get<float >(member["magicPoints"   ]);
		config.character      = Get<uint8 >(member["character"     ]);
		config.costume        = Get<uint8 >(member["costume"       ]);
		config.style          = Get<uint32>(member["style"         ]);

		GetArray<uint8, 4>(config.weapons, member["weapons"]);
	}



	{
		auto & config = Prep_arg(config).Artemis;
		auto & member = root["Artemis"];

		config.swapNormalShotAndMultiLock = Get<bool>(member["swapNormalShotAndMultiLock"]);
		config.instantFullCharge          = Get<bool>(member["instantFullCharge"         ]);
	}



	{
		auto & config = Prep_arg(config).BossRush;
		auto & member = root["BossRush"];

		config.enable = Get<bool>(member["enable"]);

		{
			auto & config2 = config.Mission5;
			auto & member2 = member["Mission5"];

			config2.skipJester = Get<bool>(member2["skipJester"]);
		}

		{
			auto & config2 = config.Mission12;
			auto & member2 = member["Mission12"];

			config2.skipJester      = Get<bool>(member2["skipJester"     ]);
			config2.skipGeryonPart1 = Get<bool>(member2["skipGeryonPart1"]);
		}

		{
			auto & config2 = config.Mission17;
			auto & member2 = member["Mission17"];

			config2.skipJester = Get<bool>(member2["skipJester"]);
		}

		{
			auto & config2 = config.Mission19;
			auto & member2 = member["Mission19"];

			config2.skipArkhamPart1 = Get<bool>(member2["skipArkhamPart1"]);
		}
	}



	{
		
		auto & config = Prep_arg(config).Color;
		auto & member = root["Color"];

		GetArray2<uint8, 5, 4>(config.airHike, member["airHike"]);

		{
			auto & config2 = config.Trickster;
			auto & member2 = member["Trickster"];

			GetArray<uint8, 4>(config2.skyStar, member2["skyStar"]);
		}

		{
			auto & config2 = config.Royalguard;
			auto & member2 = member["Royalguard"];

			GetArray<uint8, 4>(config2.ultimate, member2["ultimate"]);
		}

		{
			auto & config2 = config.Doppelganger;
			auto & member2 = member["Doppelganger"];

			GetArray<uint8, 4>(config2.clone, member2["clone"]);
		}

		{
			auto & config2 = config.Aura;
			auto & member2 = member["Aura"];

			GetArray2<uint8, 5, 4>(config2.dante     , member2["dante"     ]);
			GetArray <uint8, 4   >(config2.sparda    , member2["sparda"    ]);
			GetArray2<uint8, 3, 4>(config2.vergil    , member2["vergil"    ]);
			GetArray <uint8, 4   >(config2.neroAngelo, member2["neroAngelo"]);
		}
	}



	{
		auto & config = Prep_arg(config).EbonyIvory;
		auto & member = root["EbonyIvory"];

		config.foursomeTime      = Get<bool>(member["foursomeTime"     ]);
		config.infiniteRainStorm = Get<bool>(member["infiniteRainStorm"]);
	}



	{
		auto & config = Prep_arg(config).Rebellion;
		auto & member = root["Rebellion"];

		config.infiniteSwordPierce = Get<bool>(member["infiniteSwordPierce"]);

		GetArray<float, 2>(config.stingerDuration   , member["stingerDuration"   ]);
		GetArray<float, 2>(config.stingerRange      , member["stingerRange"      ]);
		GetArray<uint8, 2>(config.airStingerCount   , member["airStingerCount"   ]);
		GetArray<float, 2>(config.airStingerDuration, member["airStingerDuration"]);
		GetArray<float, 2>(config.airStingerRange   , member["airStingerRange"   ]);
	}



	{
		auto & config = Prep_arg(config).Royalguard;
		auto & member = root["Royalguard"];

		config.forceJustFrameRelease = Get<bool>(member["forceJustFrameRelease"]);
	}



	{
		auto & config = Prep_arg(config).Speed;
		auto & member = root["Speed"];

		config.main                   = Get<float>(member["main"                  ]);
		config.turbo                  = Get<float>(member["turbo"                 ]);
		config.enemy                  = Get<float>(member["enemy"                 ]);
		config.quicksilverPlayerActor = Get<float>(member["quicksilverPlayerActor"]);
		config.quicksilverEnemyActor  = Get<float>(member["quicksilverEnemyActor" ]);
		config.human                  = Get<float>(member["human"                 ]);

		GetArray<float, 6>(config.devilDante , member["devilDante" ]);
		GetArray<float, 5>(config.devilVergil, member["devilVergil"]);
	}



	{
		auto & config = Prep_arg(config).SummonedSwords;
		auto & member = root["SummonedSwords"];

		config.chronoSwords = Get<bool>(member["chronoSwords"]);
	}



	{
		auto & config = Prep_arg(config).Yamato;
		auto & member = root["Yamato"];

		GetArray<uint8, 2>(config.judgementCutCount, member["judgementCutCount"]);
	}



	{
		auto & config = Prep_arg(config).YamatoForceEdge;
		auto & member = root["YamatoForceEdge"];

		config.infiniteRoundTrip = Get<bool>(member["infiniteRoundTrip"]);

		GetArray<float, 2>(config.stingerDuration   , member["stingerDuration"   ]);
		GetArray<float, 2>(config.stingerRange      , member["stingerRange"      ]);
		GetArray<uint8, 2>(config.airStingerCount   , member["airStingerCount"   ]);
		GetArray<float, 2>(config.airStingerDuration, member["airStingerDuration"]);
		GetArray<float, 2>(config.airStingerRange   , member["airStingerRange"   ]);
	}



	auto & config = Prep_arg(config);
	auto & member = root;

	config.welcome                   = Get<bool >(member["welcome"                  ]);
	config.hideBeowulfDante          = Get<bool >(member["hideBeowulfDante"         ]);
	config.hideBeowulfVergil         = Get<bool >(member["hideBeowulfVergil"        ]);
	config.airHikeCoreAbility        = Get<bool >(member["airHikeCoreAbility"       ]);
	config.crazyComboLevelMultiplier = Get<uint8>(member["crazyComboLevelMultiplier"]);
	config.dotShadow                 = Get<uint8>(member["dotShadow"                ]);
	config.depleteQuicksilver        = Get<float>(member["depleteQuicksilver"       ]);
	config.depleteDoppelganger       = Get<float>(member["depleteDoppelganger"      ]);
	config.depleteDevil              = Get<float>(member["depleteDevil"             ]);
	config.noDevilForm               = Get<bool >(member["noDevilForm"              ]);
	config.orbReach                  = Get<float>(member["orbReach"                 ]);
	config.resetPermissions          = Get<bool >(member["resetPermissions"         ]);
	config.infiniteHitPoints         = Get<bool >(member["infiniteHitPoints"        ]);
	config.infiniteMagicPoints       = Get<bool >(member["infiniteMagicPoints"      ]);
	config.disableTimer              = Get<bool >(member["disableTimer"             ]);
	config.infiniteBullets           = Get<bool >(member["infiniteBullets"          ]);
	config.linearWeaponSwitchTimeout = Get<float>(member["linearWeaponSwitchTimeout"]);

	GetArray<uint8, 2>(config.airHikeCount       , member["airHikeCount"       ]);
	GetArray<uint8, 2>(config.kickJumpCount      , member["kickJumpCount"      ]);
	GetArray<uint8, 2>(config.wallHikeCount      , member["wallHikeCount"      ]);
	GetArray<uint8, 2>(config.dashCount          , member["dashCount"          ]);
	GetArray<uint8, 2>(config.skyStarCount       , member["skyStarCount"       ]);
	GetArray<uint8, 2>(config.airTrickCountDante , member["airTrickCountDante" ]);
	GetArray<uint8, 2>(config.airTrickCountVergil, member["airTrickCountVergil"]);
	GetArray<uint8, 2>(config.trickUpCount       , member["trickUpCount"       ]);
	GetArray<uint8, 2>(config.trickDownCount     , member["trickDownCount"     ]);

	GetArray<float, CHANNEL::MAX>(config.channelVolumes, member["channelVolumes"]);

	ToConfig_WeaponSwitchControllerTextureData(config.meleeWeaponSwitchControllerTextureData , member["meleeWeaponSwitchControllerTextureData" ]);
	ToConfig_WeaponSwitchControllerTextureData(config.rangedWeaponSwitchControllerTextureData, member["rangedWeaponSwitchControllerTextureData"]);

	config.forceIconFocus              = Get<bool  >(member["forceIconFocus"             ]);
	config.damagePlayerActorMultiplier = Get<float >(member["damagePlayerActorMultiplier"]);
	config.damageEnemyActorMultiplier  = Get<float >(member["damageEnemyActorMultiplier" ]);
	config.damageStyleRank             = Get<uint32>(member["damageStyleRank"            ]);
	config.skipIntro                   = Get<bool  >(member["skipIntro"                  ]);
	config.skipCutscenes               = Get<bool  >(member["skipCutscenes"              ]);
	config.preferLocalFiles            = Get<bool  >(member["preferLocalFiles"           ]);
	config.frameRate                   = Get<float >(member["frameRate"                  ]);
	config.vSync                       = Get<uint8 >(member["vSync"                      ]);
	config.hideMouseCursor             = Get<bool  >(member["hideMouseCursor"            ]);
	config.windowPosX                  = Get<int32 >(member["windowPosX"                 ]);
	config.windowPosY                  = Get<int32 >(member["windowPosY"                 ]);
	config.forceWindowFocus            = Get<bool  >(member["forceWindowFocus"           ]);
	config.globalScale                 = Get<float >(member["globalScale"                ]);



	config.enemyCount = Get<uint8>(member["enemyCount"]);

	for_all(index, 30)
	{
		ToConfig_ConfigCreateEnemyActorData(config.configCreateEnemyActorData[index], member["configCreateEnemyActorData"][index]);
	}

	config.enemyAutoSpawn = Get<bool>(member["enemyAutoSpawn"]);



	ToConfig_MainOverlayData(config.mainOverlayData             , member["mainOverlayData"             ]);
	ToConfig_OverlayData    (config.missionOverlayData          , member["missionOverlayData"          ]);
	ToConfig_OverlayData    (config.bossLadyActionsOverlayData  , member["bossLadyActionsOverlayData"  ]);
	ToConfig_OverlayData    (config.bossVergilActionsOverlayData, member["bossVergilActionsOverlayData"]);



	config.kalinaAnnHookGrenadeHeight = Get<float>(member["kalinaAnnHookGrenadeHeight"]);
	config.kalinaAnnHookGrenadeTime   = Get<float>(member["kalinaAnnHookGrenadeTime"  ]);

	ToConfig_Vec4(config.kalinaAnnHookMultiplier, member["kalinaAnnHookMultiplier"]);

	config.cameraInvertX                      = Get<bool >(member["cameraInvertX"                     ]);
	config.cameraAutoAdjust                   = Get<uint8>(member["cameraAutoAdjust"                  ]);
	config.disableCenterCamera                = Get<bool >(member["disableCenterCamera"               ]);
	config.disableBossCamera                  = Get<bool >(member["disableBossCamera"                 ]);
	config.enableBossLadyFixes                = Get<bool >(member["enableBossLadyFixes"               ]);
	config.enableBossVergilFixes              = Get<bool >(member["enableBossVergilFixes"             ]);
	config.enablePVPFixes                     = Get<bool >(member["enablePVPFixes"                    ]);
	config.hideMainHUD                        = Get<bool >(member["hideMainHUD"                       ]);
	config.hideLockOn                         = Get<bool >(member["hideLockOn"                        ]);
	config.hideBossHUD                        = Get<bool >(member["hideBossHUD"                       ]);
	config.soundIgnoreEnemyData               = Get<bool >(member["soundIgnoreEnemyData"              ]);
	config.enableRebellionAirStinger          = Get<bool >(member["enableRebellionAirStinger"         ]);
	config.enableRebellionNewDrive            = Get<bool >(member["enableRebellionNewDrive"           ]);
	config.enableRebellionQuickDrive          = Get<bool >(member["enableRebellionQuickDrive"         ]);
	config.enableCerberusAirRevolver          = Get<bool >(member["enableCerberusAirRevolver"         ]);
	config.enableNevanNewVortex               = Get<bool >(member["enableNevanNewVortex"              ]);
	config.enableYamatoVergilNewJudgementCut  = Get<bool >(member["enableYamatoVergilNewJudgementCut" ]);
	config.enableBeowulfVergilAirRisingSun    = Get<bool >(member["enableBeowulfVergilAirRisingSun"   ]);
	config.enableBeowulfVergilAirLunarPhase   = Get<bool >(member["enableBeowulfVergilAirLunarPhase"  ]);
	config.enableYamatoForceEdgeNewComboPart4 = Get<bool >(member["enableYamatoForceEdgeNewComboPart4"]);
	config.enableYamatoForceEdgeAirStinger    = Get<bool >(member["enableYamatoForceEdgeAirStinger"   ]);
	config.enableYamatoForceEdgeNewRoundTrip  = Get<bool >(member["enableYamatoForceEdgeNewRoundTrip" ]);
	config.dergil                             = Get<uint8>(member["dergil"                            ]);

	GetArray<uint8, 2>(config.beowulfVergilAirRisingSunCount, member["beowulfVergilAirRisingSunCount"]);

	config.forceVisibleHUD = Get<bool>(member["forceVisibleHUD"]);



	for_all(playerIndex, PLAYER_COUNT)
	{
		ToConfig_BarsData(config.barsData[playerIndex], member["barsData"][playerIndex]);
	}



	config.forceSyncHitMagicPoints = Get<bool>(member["forceSyncHitMagicPoints"]);
	config.updateLockOns           = Get<bool>(member["updateLockOns"          ]);
	config.showCredits             = Get<bool>(member["showCredits"            ]);



	for_all(index, 3)
	{
		ToConfig_KeyData(config.keyData[index], member["keyData"][index]);
	}



	config.absoluteUnit = Get<bool>(member["absoluteUnit"]);

	GetString
	(
		config.gamepadName,
		sizeof(config.gamepadName),
		member["gamepadName"]
	);

	config.gamepadButton               = Get<byte8>(member["gamepadButton"              ]);
	config.disablePlayerActorIdleTimer = Get<bool >(member["disablePlayerActorIdleTimer"]);
}

#pragma endregion

namespaceEnd();



#define NO_INIT
#include "../ConfigFunctions.h"



export void InitConfig()
{
	LogFunction();

	InitConfigFunction();



	old_for_all(uint8, playerIndex, PLAYER_COUNT)
	{
		ApplyDefaultPlayerData(defaultConfig.Actor.playerData[playerIndex]);
		ApplyDefaultPlayerData(queuedConfig.Actor.playerData[playerIndex]);
		ApplyDefaultPlayerData(activeConfig.Actor.playerData[playerIndex]);
	}



	DebugLog("kalinaAnnHookGrenadeHeight %llX", offsetof(Config, kalinaAnnHookGrenadeHeight));
	DebugLog("kalinaAnnHookGrenadeTime   %llX", offsetof(Config, kalinaAnnHookGrenadeTime  ));
	DebugLog("kalinaAnnHookMultiplier    %llX", offsetof(Config, kalinaAnnHookMultiplier   ));
	DebugLog("barsData                   %llX", offsetof(Config, barsData                  ));

	DebugLog("activeConfig.gamepadName %llX", activeConfig.gamepadName);
}
