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
const char * fileName      = "Eva.json";

char location[64] = {};



#define _(size) struct { byte8 Prep_Merge(padding_, __LINE__)[size]; }

#pragma pack(push, 1)



export struct Config
{
	struct
	{
		uint8 meleeWeapons[MELEE_WEAPON_COUNT] =
		{
			WEAPON::FORCE_EDGE,
			WEAPON::ALASTOR,
			WEAPON::IFRIT,
			WEAPON::SPARDA,
		};
		uint8 meleeWeaponCount     = 4;
		uint8 meleeWeaponIndex     = 0;
		uint8 lastMeleeWeaponIndex = 0;

		uint8 meleeWeaponForms[MELEE_WEAPON_COUNT] =
		{
			MELEE_WEAPON_FORM::DEFAULT,
			MELEE_WEAPON_FORM::DEFAULT,
			MELEE_WEAPON_FORM::DEFAULT,
			MELEE_WEAPON_FORM::SPARDA,
		};

		uint8 rangedWeapons[RANGED_WEAPON_COUNT] =
		{
			WEAPON::HANDGUN,
			WEAPON::SHOTGUN,
			WEAPON::GRENADEGUN,
			WEAPON::NIGHTMARE_BETA,
		};
		uint8 rangedWeaponCount     = 4;
		uint8 rangedWeaponIndex     = 0;
		uint8 lastRangedWeaponIndex = 0;
	}
	Actor;



	struct
	{
		bool   enable          = (debug) ? true : false;
		uint8  mission         = 17;
		uint8  mode            = MODE::DANTE_MUST_DIE;
		uint32 track           = 0;
		bool   ignoreTrack     = true;
		uint32 room            = 0;
		bool   ignoreRoom      = true;
		vec4   position        = {};
		bool   ignorePosition  = true;
		uint8  hitPoints       = 30;
		uint8  magicPoints     = 10;
		uint8  character       = CHARACTER::DANTE;
		uint8  meleeWeapon     = WEAPON::FORCE_EDGE;
		uint8  meleeWeaponForm = MELEE_WEAPON_FORM::DEFAULT;
		uint8  rangedWeapon    = WEAPON::HANDGUN;
	}
	Arcade;



	struct
	{
		bool enable = false;
		struct
		{
			bool skipMundusPart1 = false;
		}
		Mission22;
	}
	BossRush;



	struct
	{
		bool  enable  = false;
		uint8 mission = 17;
		uint8 mode    = MODE::DANTE_MUST_DIE;
	}
	MissionSelect;



	bool welcome = (debug) ? false : true;

	bool enableForceEdgeFixes = (debug) ? true : false;
	bool enableSpardaFixes    = (debug) ? true : false;
	bool enableYamatoFixes    = (debug) ? true : false;

	bool airHikeCoreAbility = (debug) ? true : false;

	bool infiniteRoundTrip = false;

	bool   enableRoundTripReturnController             = false;
	byte16 roundTripReturnButton                       = GAMEPAD::B;

	bool   enableMeleeWeaponSwitchController           = false;
	byte16 meleeWeaponSwitchButton                     = GAMEPAD::RIGHT_TRIGGER;

	bool   enableRangedWeaponSwitchController          = false;
	byte16 rangedWeaponSwitchButton                    = GAMEPAD::LEFT_TRIGGER;

	bool   enableResetStateController                  = false;
	byte16 resetStateButtons[RESET_STATE_BUTTON_COUNT] =
	{
		GAMEPAD::UP,
		GAMEPAD::RIGHT,
		GAMEPAD::DOWN,
		GAMEPAD::LEFT,
	};

	bool   enableChargeController = false;
	byte16 chargeButton           = GAMEPAD::X;



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

		MainOverlayData()
		{
			if constexpr (debug)
			{
				enable = true;
			}
		}
	}
	mainOverlayData;



	bool skipIntro                = (debug) ? true : false;
	bool disablePauseRestrictions = (debug) ? true : false;

	float frameRate = (debug) ? 80 : 60;
	uint8 vSync     = (debug) ? 1  : 0;

	bool hideMouseCursor = false;


	int32 windowPosX = 0;
	int32 windowPosY = 0;
	bool forceWindowFocus = true;

	bool infiniteHitPoints   = false;
	bool infiniteMagicPoints = false;
	bool disableTimer        = false;



	bool disablePlayerActorIdleTimer = false;

	bool screenEffectForceMaxTimer = (debug) ? true : false;
	bool forceVisibleHUD           = false;

	float globalScale = 1;

	bool showCredits = (debug) ? false : true;



	KeyData keyData[2] =
	{
		{
			{
				KEY::LEFT_CONTROL,
				KEY::D
			},
			2
		},
		{},
	};



	char gamepadName[128] = "Wireless Controller";
	byte8 gamepadButton = 13;
};



#pragma pack(pop)

#undef _



export Config defaultConfig;
export Config activeConfig;
export Config queuedConfig;



namespaceStart(JSON);

#include "../Core/JSON.h"

#pragma region CreateMembers

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
	DebugLogFunction();

	{
		auto & member = Create<struct_t>(root, "Actor");
		auto & config = Prep_arg(config).Actor;

		CreateArray<uint8, MELEE_WEAPON_COUNT>(member, "meleeWeapons", config.meleeWeapons);

		Create<uint8>(member, "meleeWeaponCount"    , config.meleeWeaponCount    );
		Create<uint8>(member, "meleeWeaponIndex"    , config.meleeWeaponIndex    );
		Create<uint8>(member, "lastMeleeWeaponIndex", config.lastMeleeWeaponIndex);

		CreateArray<uint8, MELEE_WEAPON_COUNT >(member, "meleeWeaponForms", config.meleeWeaponForms);
		CreateArray<uint8, RANGED_WEAPON_COUNT>(member, "rangedWeapons"   , config.rangedWeapons   );

		Create<uint8>(member, "rangedWeaponCount"    , config.rangedWeaponCount    );
		Create<uint8>(member, "rangedWeaponIndex"    , config.rangedWeaponIndex    );
		Create<uint8>(member, "lastRangedWeaponIndex", config.lastRangedWeaponIndex);
	}



	{
		auto & member = Create<struct_t>(root, "Arcade");
		auto & config = Prep_arg(config).Arcade;


		Create<bool  >(member, "enable"     , config.enable     );
		Create<uint8 >(member, "mission"    , config.mission    );
		Create<uint8 >(member, "mode"       , config.mode       );
		Create<uint32>(member, "track"      , config.track      );
		Create<bool  >(member, "ignoreTrack", config.ignoreTrack);
		Create<uint32>(member, "room"       , config.room       );
		Create<bool  >(member, "ignoreRoom" , config.ignoreRoom );

		CreateMembers_Vec4(member, "position", config.position);

		Create<bool >(member, "ignorePosition" , config.ignorePosition );
		Create<uint8>(member, "hitPoints"      , config.hitPoints      );
		Create<uint8>(member, "magicPoints"    , config.magicPoints    );
		Create<uint8>(member, "character"      , config.character      );
		Create<uint8>(member, "meleeWeapon"    , config.meleeWeapon    );
		Create<uint8>(member, "meleeWeaponForm", config.meleeWeaponForm);
		Create<uint8>(member, "rangedWeapon"   , config.rangedWeapon   );
	}



	{
		auto & member = Create<struct_t>(root, "BossRush");
		auto & config = Prep_arg(config).BossRush;

		Create<bool>(member, "enable", config.enable);

		{
			auto & member2 = Create<struct_t>(member, "Mission22");
			auto & config2 = config.Mission22;

			Create<bool>(member2, "skipMundusPart1", config2.skipMundusPart1);
		}
	}



	{
		auto & member = Create<struct_t>(root, "MissionSelect");
		auto & config = Prep_arg(config).MissionSelect;

		Create<bool >(member, "enable" , config.enable );
		Create<uint8>(member, "mission", config.mission);
		Create<uint8>(member, "mode"   , config.mode   );
	}



	auto & member = root;
	auto & config = Prep_arg(config);



	Create<bool  >(member, "welcome"                           , config.welcome                           );
	Create<bool  >(member, "enableForceEdgeFixes"              , config.enableForceEdgeFixes              );
	Create<bool  >(member, "enableSpardaFixes"                 , config.enableSpardaFixes                 );
	Create<bool  >(member, "enableYamatoFixes"                 , config.enableYamatoFixes                 );
	Create<bool  >(member, "airHikeCoreAbility"                , config.airHikeCoreAbility                );
	Create<bool  >(member, "infiniteRoundTrip"                 , config.infiniteRoundTrip                 );
	Create<bool  >(member, "enableRoundTripReturnController"   , config.enableRoundTripReturnController   );
	Create<byte16>(member, "roundTripReturnButton"             , config.roundTripReturnButton             );
	Create<bool  >(member, "enableMeleeWeaponSwitchController" , config.enableMeleeWeaponSwitchController );
	Create<byte16>(member, "meleeWeaponSwitchButton"           , config.meleeWeaponSwitchButton           );
	Create<bool  >(member, "enableRangedWeaponSwitchController", config.enableRangedWeaponSwitchController);
	Create<byte16>(member, "rangedWeaponSwitchButton"          , config.rangedWeaponSwitchButton          );
	Create<bool  >(member, "enableResetStateController"        , config.enableResetStateController        );

	CreateArray<byte16, RESET_STATE_BUTTON_COUNT>(member, "resetStateButtons", config.resetStateButtons);

	Create<bool>(member, "enableChargeController", config.enableChargeController);

	Create<byte16>(member, "chargeButton", config.chargeButton);



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
	}



	Create<bool >(member, "skipIntro"                  , config.skipIntro                  );
	Create<bool >(member, "disablePauseRestrictions"   , config.disablePauseRestrictions   );
	Create<float>(member, "frameRate"                  , config.frameRate                  );
	Create<uint8>(member, "vSync"                      , config.vSync                      );
	Create<bool >(member, "hideMouseCursor"            , config.hideMouseCursor            );
	Create<int32>(member, "windowPosX"                 , config.windowPosX                 );
	Create<int32>(member, "windowPosY"                 , config.windowPosY                 );
	Create<bool >(member, "forceWindowFocus"           , config.forceWindowFocus           );
	Create<bool >(member, "infiniteHitPoints"          , config.infiniteHitPoints          );
	Create<bool >(member, "infiniteMagicPoints"        , config.infiniteMagicPoints        );
	Create<bool >(member, "disableTimer"               , config.disableTimer               );
	Create<bool >(member, "disablePlayerActorIdleTimer", config.disablePlayerActorIdleTimer);
	Create<bool >(member, "screenEffectForceMaxTimer"  , config.screenEffectForceMaxTimer  );
	Create<bool >(member, "forceVisibleHUD"            , config.forceVisibleHUD            );
	Create<float>(member, "globalScale"                , config.globalScale                );
	Create<bool >(member, "showCredits"                , config.showCredits                );



	{
		auto & member = CreateArray<struct_t, 2>(root, "keyData");
		auto & config = Prep_arg(config).keyData;

		for_all(index, 2)
		{
			auto & member2 = member[index];
			auto & config2 = config[index];

			CreateMembers_KeyDataContent(member2, config2);
		}
	}



	CreateString (member, "gamepadName"  , config.gamepadName  );
	Create<byte8>(member, "gamepadButton", config.gamepadButton);
}

#pragma endregion



#pragma region ToJSON

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
	DebugLogFunction();

	{
		auto & member = root["Actor"];
		auto & config = Prep_arg(config).Actor;

		SetArray<uint8, MELEE_WEAPON_COUNT>(member["meleeWeapons"], config.meleeWeapons);

		Set<uint8>(member["meleeWeaponCount"    ], config.meleeWeaponCount    );
		Set<uint8>(member["meleeWeaponIndex"    ], config.meleeWeaponIndex    );
		Set<uint8>(member["lastMeleeWeaponIndex"], config.lastMeleeWeaponIndex);

		SetArray<uint8, MELEE_WEAPON_COUNT >(member["meleeWeaponForms"], config.meleeWeaponForms);
		SetArray<uint8, RANGED_WEAPON_COUNT>(member["rangedWeapons"   ], config.rangedWeapons   );

		Set<uint8>(member["rangedWeaponCount"    ], config.rangedWeaponCount    );
		Set<uint8>(member["rangedWeaponIndex"    ], config.rangedWeaponIndex    );
		Set<uint8>(member["lastRangedWeaponIndex"], config.lastRangedWeaponIndex);
	}



	{
		auto & member = root["Arcade"];
		auto & config = Prep_arg(config).Arcade;

		Set<bool  >(member["enable"         ], config.enable         );
		Set<uint8 >(member["mission"        ], config.mission        );
		Set<uint8 >(member["mode"           ], config.mode           );
		Set<uint32>(member["track"          ], config.track          );
		Set<bool  >(member["ignoreTrack"    ], config.ignoreTrack    );
		Set<uint32>(member["room"           ], config.room           );
		Set<bool  >(member["ignoreRoom"     ], config.ignoreRoom     );
		ToJSON_Vec4(member["position"       ], config.position       );
		Set<bool  >(member["ignorePosition" ], config.ignorePosition );
		Set<uint8 >(member["hitPoints"      ], config.hitPoints      );
		Set<uint8 >(member["magicPoints"    ], config.magicPoints    );
		Set<uint8 >(member["character"      ], config.character      );
		Set<uint8 >(member["meleeWeapon"    ], config.meleeWeapon    );
		Set<uint8 >(member["meleeWeaponForm"], config.meleeWeaponForm);
		Set<uint8 >(member["rangedWeapon"   ], config.rangedWeapon   );
	}



	{
		auto & member = root["BossRush"];
		auto & config = Prep_arg(config).BossRush;

		Set<bool>(member["enable"], config.enable);

		{
			auto & member2 = member["Mission22"];
			auto & config2 = config.Mission22;

			Set<bool>(member2["skipMundusPart1"], config2.skipMundusPart1);
		}
	}



	{
		auto & member = root["MissionSelect"];
		auto & config = Prep_arg(config).MissionSelect;

		Set<bool >(member["enable" ], config.enable );
		Set<uint8>(member["mission"], config.mission);
		Set<uint8>(member["mode"   ], config.mode   );
	}



	auto & member = root;
	auto & config = Prep_arg(config);

	Set<bool  >(member["welcome"                           ], config.welcome                           );
	Set<bool  >(member["enableForceEdgeFixes"              ], config.enableForceEdgeFixes              );
	Set<bool  >(member["enableSpardaFixes"                 ], config.enableSpardaFixes                 );
	Set<bool  >(member["enableYamatoFixes"                 ], config.enableYamatoFixes                 );
	Set<bool  >(member["airHikeCoreAbility"                ], config.airHikeCoreAbility                );
	Set<bool  >(member["infiniteRoundTrip"                 ], config.infiniteRoundTrip                 );
	Set<bool  >(member["enableRoundTripReturnController"   ], config.enableRoundTripReturnController   );
	Set<byte16>(member["roundTripReturnButton"             ], config.roundTripReturnButton             );
	Set<bool  >(member["enableMeleeWeaponSwitchController" ], config.enableMeleeWeaponSwitchController );
	Set<byte16>(member["meleeWeaponSwitchButton"           ], config.meleeWeaponSwitchButton           );
	Set<bool  >(member["enableRangedWeaponSwitchController"], config.enableRangedWeaponSwitchController);
	Set<byte16>(member["rangedWeaponSwitchButton"          ], config.rangedWeaponSwitchButton          );
	Set<bool  >(member["enableResetStateController"        ], config.enableResetStateController        );

	SetArray<byte16, RESET_STATE_BUTTON_COUNT>(member["resetStateButtons"], config.resetStateButtons);

	Set<bool  >(member["enableChargeController"], config.enableChargeController);
	Set<byte16>(member["chargeButton"          ], config.chargeButton          );



	ToJSON_MainOverlayData(member["mainOverlayData"             ], config.mainOverlayData             );



	Set<bool >(member["skipIntro"                  ], config.skipIntro                  );
	Set<bool >(member["disablePauseRestrictions"   ], config.disablePauseRestrictions   );
	Set<float>(member["frameRate"                  ], config.frameRate                  );
	Set<uint8>(member["vSync"                      ], config.vSync                      );
	Set<bool >(member["hideMouseCursor"            ], config.hideMouseCursor            );
	Set<int32>(member["windowPosX"                 ], config.windowPosX                 );
	Set<int32>(member["windowPosY"                 ], config.windowPosY                 );
	Set<bool >(member["forceWindowFocus"           ], config.forceWindowFocus           );
	Set<bool >(member["infiniteHitPoints"          ], config.infiniteHitPoints          );
	Set<bool >(member["infiniteMagicPoints"        ], config.infiniteMagicPoints        );
	Set<bool >(member["disableTimer"               ], config.disableTimer               );
	Set<bool >(member["disablePlayerActorIdleTimer"], config.disablePlayerActorIdleTimer);
	Set<bool >(member["screenEffectForceMaxTimer"  ], config.screenEffectForceMaxTimer  );
	Set<bool >(member["forceVisibleHUD"            ], config.forceVisibleHUD            );
	Set<float>(member["globalScale"                ], config.globalScale                );
	Set<bool >(member["showCredits"                ], config.showCredits                );



	for_all(index, 2)
	{
		ToJSON_KeyData(member["keyData"][index], config.keyData[index]);
	}



	SetString (member["gamepadName"  ], config.gamepadName  );
	Set<byte8>(member["gamepadButton"], config.gamepadButton);
}

#pragma endregion



#pragma region ToConfig

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
	DebugLogFunction();

	{
		auto & config = Prep_arg(config).Actor;
		auto & member = root["Actor"];

		GetArray<uint8, MELEE_WEAPON_COUNT>(config.meleeWeapons, member["meleeWeapons"]);

		config.meleeWeaponCount     = Get<uint8>(member["meleeWeaponCount"    ]);
		config.meleeWeaponIndex     = Get<uint8>(member["meleeWeaponIndex"    ]);
		config.lastMeleeWeaponIndex = Get<uint8>(member["lastMeleeWeaponIndex"]);

		GetArray<uint8, MELEE_WEAPON_COUNT>(config.meleeWeaponForms, member["meleeWeaponForms"]);

		GetArray<uint8, RANGED_WEAPON_COUNT>(config.rangedWeapons, member["rangedWeapons"]);

		config.rangedWeaponCount     = Get<uint8>(member["rangedWeaponCount"    ]);
		config.rangedWeaponIndex     = Get<uint8>(member["rangedWeaponIndex"    ]);
		config.lastRangedWeaponIndex = Get<uint8>(member["lastRangedWeaponIndex"]);
	}



	{
		auto & config = Prep_arg(config).Arcade;
		auto & member = root["Arcade"];

		config.enable          = Get<bool  >(member["enable"     ]);
		config.mission         = Get<uint8 >(member["mission"    ]);
		config.mode            = Get<uint8 >(member["mode"       ]);
		config.track           = Get<uint32>(member["track"      ]);
		config.ignoreTrack     = Get<bool  >(member["ignoreTrack"]);
		config.room            = Get<uint32>(member["room"       ]);
		config.ignoreRoom      = Get<bool  >(member["ignoreRoom" ]);

		ToConfig_Vec4(config.position, member["position"]);

		config.ignorePosition  = Get<bool >(member["ignorePosition" ]);
		config.hitPoints       = Get<uint8>(member["hitPoints"      ]);
		config.magicPoints     = Get<uint8>(member["magicPoints"    ]);
		config.character       = Get<uint8>(member["character"      ]);
		config.meleeWeapon     = Get<uint8>(member["meleeWeapon"    ]);
		config.meleeWeaponForm = Get<uint8>(member["meleeWeaponForm"]);
		config.rangedWeapon    = Get<uint8>(member["rangedWeapon"   ]);
	}



	{
		auto & config = Prep_arg(config).BossRush;
		auto & member = root["BossRush"];

		config.enable = Get<bool>(member["enable"]);

		{
			auto & config2 = config.Mission22;
			auto & member2 = member["Mission22"];

			config2.skipMundusPart1 = Get<bool>(member2["skipMundusPart1"]);
		}
	}



	{
		auto & config = Prep_arg(config).MissionSelect;
		auto & member = root["MissionSelect"];

		config.enable  = Get<bool >(member["enable" ]);
		config.mission = Get<uint8>(member["mission"]);
		config.mode    = Get<uint8>(member["mode"   ]);
	}



	auto & config = Prep_arg(config);
	auto & member = root;



	config.welcome                            = Get<bool  >(member["welcome"                           ]);
	config.enableForceEdgeFixes               = Get<bool  >(member["enableForceEdgeFixes"              ]);
	config.enableSpardaFixes                  = Get<bool  >(member["enableSpardaFixes"                 ]);
	config.enableYamatoFixes                  = Get<bool  >(member["enableYamatoFixes"                 ]);
	config.airHikeCoreAbility                 = Get<bool  >(member["airHikeCoreAbility"                ]);
	config.infiniteRoundTrip                  = Get<bool  >(member["infiniteRoundTrip"                 ]);
	config.enableRoundTripReturnController    = Get<bool  >(member["enableRoundTripReturnController"   ]);
	config.roundTripReturnButton              = Get<byte16>(member["roundTripReturnButton"             ]);
	config.enableMeleeWeaponSwitchController  = Get<bool  >(member["enableMeleeWeaponSwitchController" ]);
	config.meleeWeaponSwitchButton            = Get<byte16>(member["meleeWeaponSwitchButton"           ]);
	config.enableRangedWeaponSwitchController = Get<bool  >(member["enableRangedWeaponSwitchController"]);
	config.rangedWeaponSwitchButton           = Get<byte16>(member["rangedWeaponSwitchButton"          ]);
	config.enableResetStateController         = Get<bool  >(member["enableResetStateController"        ]);

	GetArray<byte16, RESET_STATE_BUTTON_COUNT>(config.resetStateButtons, member["resetStateButtons"]);

	config.enableChargeController = Get<bool  >(member["enableChargeController"]);
	config.chargeButton           = Get<byte16>(member["chargeButton"          ]);

	ToConfig_MainOverlayData(config.mainOverlayData, member["mainOverlayData"]);

	config.skipIntro                   = Get<bool >(member["skipIntro"                  ]);
	config.disablePauseRestrictions    = Get<bool >(member["disablePauseRestrictions"   ]);
	config.frameRate                   = Get<float>(member["frameRate"                  ]);
	config.vSync                       = Get<uint8>(member["vSync"                      ]);
	config.hideMouseCursor             = Get<bool >(member["hideMouseCursor"            ]);
	config.windowPosX                  = Get<int32>(member["windowPosX"                 ]);
	config.windowPosY                  = Get<int32>(member["windowPosY"                 ]);
	config.forceWindowFocus            = Get<bool >(member["forceWindowFocus"           ]);
	config.infiniteHitPoints           = Get<bool >(member["infiniteHitPoints"          ]);
	config.infiniteMagicPoints         = Get<bool >(member["infiniteMagicPoints"        ]);
	config.disableTimer                = Get<bool >(member["disableTimer"               ]);
	config.disablePlayerActorIdleTimer = Get<bool >(member["disablePlayerActorIdleTimer"]);
	config.screenEffectForceMaxTimer   = Get<bool >(member["screenEffectForceMaxTimer"  ]);
	config.forceVisibleHUD             = Get<bool >(member["forceVisibleHUD"            ]);
	config.globalScale                 = Get<float>(member["globalScale"                ]);
	config.showCredits                 = Get<bool >(member["showCredits"                ]);



	for_all(index, 2)
	{
		ToConfig_KeyData(config.keyData[index], member["keyData"][index]);
	}



	GetString
	(
		config.gamepadName,
		sizeof(config.gamepadName),
		member["gamepadName"]
	);

	config.gamepadButton = Get<byte8>(member["gamepadButton"]);
}

#pragma endregion

namespaceEnd();



#include "../ConfigFunctions.h"
