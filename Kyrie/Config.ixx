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
const char * fileName      = "Kyrie.json";

char location[64] = {};



#define _(size) struct { byte8 Prep_Merge(padding_, __LINE__)[size]; }

#pragma pack(push, 1)



export struct Config
{
	struct
	{
		bool enable = (debug) ? true : false;
		new_size_t playerCount = (debug) ? 2 : 1;
		PlayerData playerData[PLAYER::COUNT] = {};
	}
	Actor;



	struct
	{
		bool   enable         = (debug) ? true : false;
		uint32 game           = GAME::LADY_TRISH;
		uint32 mission        = 17;
		uint32 mode           = MODE::DANTE_MUST_DIE;
		uint32 room           = 9;
		bool   ignoreRoom     = (debug) ? false : true;
		uint32 position       = 2;
		bool   ignorePosition = (debug) ? false : true;
		uint8  floor          = 0;
		float  hitPoints      = 20000;
		float  magicPoints    = 10000;
		uint8  character      = CHARACTER::LADY;
		uint32 costume        = 3;
	}
	Arcade;



	bool welcome = (debug) ? false : true;

	new_size_t keyboardPlayerIndex = 0;

	bool enableCharacterSwitchController = (debug) ? true : false;
	byte32 characterSwitchControllerButton = GAMEPAD::RIGHT_THUMB;



	KeyData characterSwitchControllerKeyData =
	{
		{
			KEY::P
		},
		1
	};



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

	BarsData barsData[PLAYER::COUNT];



	struct OverlayData
	{
		bool enable = false;
		vec2 pos = { 8, 8 };
		float color[4] = { 1, 0, 0, 1 };
	};

	struct MainOverlayData : OverlayData
	{
		bool showFocus               = true;
		bool showFPS                 = true;
		bool showSizes               = true;
		bool showFrameRateMultiplier = true;
		bool showEventData           = true;
		bool showSpeed               = true;

		MainOverlayData()
		{
			if constexpr (debug)
			{
				enable = true;
			}
		}
	}
	mainOverlayData;



	float mainSpeed     = 1.0f;
	float menuSpeed     = 5.0f;
	float cutsceneSpeed = 1.0f;



	bool skipIntro = (debug) ? true : false;

	bool hideMouseCursor = false;

	float baseFrameRate   = 60;
	float targetFrameRate = 60;
	uint8 vSync           = 0;

	int32 windowPosX = 0;
	int32 windowPosY = 0;
	bool borderless = (debug) ? true : false;
	bool forceWindowFocus = true;



	bool infiniteHitPoints   = false;
	bool infiniteMagicPoints = (debug) ? true : false;
	bool disableTimer        = false;



	float globalScale = 1.0f;

	bool disableFilters[countof(filterHelpers)] = {};

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



	bool disableCenterCamera = false;



	char gamepadName[128] = "Wireless Controller";
	byte8 gamepadButton = 13;



	bool disablePlayerActorIdleTimer = false;
};



#pragma pack(pop)

#undef _



export Config defaultConfig;
export Config activeConfig;
export Config queuedConfig;



#pragma region JSON

namespaceStart(JSON);

#include "../Core/JSON.h"



#pragma region CreateMembers

void CreateMembers_PlayerDataContent
(
	rapidjson::Value & member,
	PlayerData & config
)
{
	Create<uint32>(member, "character", config.character);
	Create<uint32>(member, "costume"  , config.costume  );
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

		Create<bool      >(member, "enable"     , config.enable     );
		Create<new_size_t>(member, "playerCount", config.playerCount);

		auto & playerData = CreateArray<struct_t, PLAYER::COUNT>(member, "playerData");

		for_all(playerIndex, PLAYER::COUNT)
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
		Create<uint32>(member, "game"          , config.game          );
		Create<uint32>(member, "mission"       , config.mission       );
		Create<uint32>(member, "mode"          , config.mode          );
		Create<uint32>(member, "room"          , config.room          );
		Create<bool  >(member, "ignoreRoom"    , config.ignoreRoom    );
		Create<uint32>(member, "position"      , config.position      );
		Create<bool  >(member, "ignorePosition", config.ignorePosition);
		Create<uint8 >(member, "floor"         , config.floor         );
		Create<float >(member, "hitPoints"     , config.hitPoints     );
		Create<float >(member, "magicPoints"   , config.magicPoints   );
		Create<uint8 >(member, "character"     , config.character     );
		Create<uint32>(member, "costume"       , config.costume       );
	}



	auto & member = root;
	auto & config = Prep_arg(config);

	Create<bool      >(member, "welcome"                        , config.welcome                        );
	Create<new_size_t>(member, "keyboardPlayerIndex"            , config.keyboardPlayerIndex            );
	Create<bool      >(member, "enableCharacterSwitchController", config.enableCharacterSwitchController);
	Create<byte32    >(member, "characterSwitchControllerButton", config.characterSwitchControllerButton);



	{
		auto & member2 = Create<struct_t>(member, "characterSwitchControllerKeyData");
		auto & config2 = config.characterSwitchControllerKeyData;

		CreateMembers_KeyDataContent(member2, config2);
	}



	{
		auto & member = CreateArray<struct_t, PLAYER::COUNT>(root, "barsData");
		auto & config = Prep_arg(config).barsData;

		for_all(playerIndex, PLAYER::COUNT)
		{
			auto & member2 = member[playerIndex];
			auto & config2 = config[playerIndex];

			CreateMembers_BarsDataContent(member2, config2);
		}
	}



	{
		auto & member2 = Create<struct_t>(member, "mainOverlayData");
		auto & config2 = config.mainOverlayData;

		CreateMembers_OverlayDataContent(member2, config2);

		Create<bool>(member2, "showFocus"              , config2.showFocus              );
		Create<bool>(member2, "showFPS"                , config2.showFPS                );
		Create<bool>(member2, "showSizes"              , config2.showSizes              );
		Create<bool>(member2, "showFrameRateMultiplier", config2.showFrameRateMultiplier);
		Create<bool>(member2, "showEventData"          , config2.showEventData          );
		Create<bool>(member2, "showSpeed"              , config2.showSpeed              );
	}



	Create<float>(member, "mainSpeed"          , config.mainSpeed          );
	Create<float>(member, "menuSpeed"          , config.menuSpeed          );
	Create<float>(member, "cutsceneSpeed"      , config.cutsceneSpeed      );
	Create<bool >(member, "skipIntro"          , config.skipIntro          );
	Create<bool >(member, "hideMouseCursor"    , config.hideMouseCursor    );
	Create<float>(member, "baseFrameRate"      , config.baseFrameRate      );
	Create<float>(member, "targetFrameRate"    , config.targetFrameRate    );
	Create<uint8>(member, "vSync"              , config.vSync              );
	Create<int32>(member, "windowPosX"         , config.windowPosX         );
	Create<int32>(member, "windowPosY"         , config.windowPosY         );
	Create<bool >(member, "borderless"         , config.borderless         );
	Create<bool >(member, "forceWindowFocus"   , config.forceWindowFocus   );
	Create<bool >(member, "infiniteHitPoints"  , config.infiniteHitPoints  );
	Create<bool >(member, "infiniteMagicPoints", config.infiniteMagicPoints);
	Create<bool >(member, "disableTimer"       , config.disableTimer       );
	Create<float>(member, "globalScale"        , config.globalScale        );

	CreateArray<bool, countof(filterHelpers)>(member, "disableFilters", config.disableFilters);

	Create<bool>(member, "showCredits", config.showCredits);

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

	Create<bool>(member, "disableCenterCamera", config.disableCenterCamera);

	CreateString (member, "gamepadName"                , config.gamepadName                );
	Create<byte8>(member, "gamepadButton"              , config.gamepadButton              );
	Create<bool >(member, "disablePlayerActorIdleTimer", config.disablePlayerActorIdleTimer);
}

#pragma endregion



#pragma region ToJSON

void ToJSON_PlayerData
(
	rapidjson::Value & member,
	PlayerData & config
)
{
	Set<uint32>(member["character"], config.character);
	Set<uint32>(member["costume"  ], config.costume  );
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
	Set<bool>(member["showSpeed"              ], config.showSpeed              );
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

		Set<bool      >(member["enable"     ], config.enable     );
		Set<new_size_t>(member["playerCount"], config.playerCount);

		for_all(playerIndex, PLAYER::COUNT)
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
		Set<uint32>(member["game"          ], config.game          );
		Set<uint32>(member["mission"       ], config.mission       );
		Set<uint32>(member["mode"          ], config.mode          );
		Set<uint32>(member["room"          ], config.room          );
		Set<bool  >(member["ignoreRoom"    ], config.ignoreRoom    );
		Set<uint32>(member["position"      ], config.position      );
		Set<bool  >(member["ignorePosition"], config.ignorePosition);
		Set<uint8 >(member["floor"         ], config.floor         );
		Set<float >(member["hitPoints"     ], config.hitPoints     );
		Set<float >(member["magicPoints"   ], config.magicPoints   );
		Set<uint8 >(member["character"     ], config.character     );
		Set<uint32>(member["costume"       ], config.costume       );
	}



	auto & member = root;
	auto & config = Prep_arg(config);

	Set<bool      >(member["welcome"                        ], config.welcome                        );
	Set<new_size_t>(member["keyboardPlayerIndex"            ], config.keyboardPlayerIndex            );
	Set<bool      >(member["enableCharacterSwitchController"], config.enableCharacterSwitchController);
	Set<byte32    >(member["characterSwitchControllerButton"], config.characterSwitchControllerButton);

	ToJSON_KeyData(member["characterSwitchControllerKeyData"], config.characterSwitchControllerKeyData);

	for_all(playerIndex, PLAYER::COUNT)
	{
		ToJSON_BarsData(member["barsData"][playerIndex], config.barsData[playerIndex]);
	}

	ToJSON_MainOverlayData(member["mainOverlayData"], config.mainOverlayData);

	Set<float>(member["mainSpeed"          ], config.mainSpeed          );
	Set<float>(member["menuSpeed"          ], config.menuSpeed          );
	Set<float>(member["cutsceneSpeed"      ], config.cutsceneSpeed      );
	Set<bool >(member["skipIntro"          ], config.skipIntro          );
	Set<bool >(member["hideMouseCursor"    ], config.hideMouseCursor    );
	Set<float>(member["baseFrameRate"      ], config.baseFrameRate      );
	Set<float>(member["targetFrameRate"    ], config.targetFrameRate    );
	Set<uint8>(member["vSync"              ], config.vSync              );
	Set<int32>(member["windowPosX"         ], config.windowPosX         );
	Set<int32>(member["windowPosY"         ], config.windowPosY         );
	Set<bool >(member["borderless"         ], config.borderless         );
	Set<bool >(member["forceWindowFocus"   ], config.forceWindowFocus   );
	Set<bool >(member["infiniteHitPoints"  ], config.infiniteHitPoints  );
	Set<bool >(member["infiniteMagicPoints"], config.infiniteMagicPoints);
	Set<bool >(member["disableTimer"       ], config.disableTimer       );
	Set<float>(member["globalScale"        ], config.globalScale        );

	SetArray<bool, countof(filterHelpers)>(member["disableFilters"], config.disableFilters);

	Set<bool>(member["showCredits"], config.showCredits);

	for_all(index, 3)
	{
		ToJSON_KeyData(member["keyData"][index], config.keyData[index]);
	}

	Set<bool>(member["disableCenterCamera"], config.disableCenterCamera);

	SetString (member["gamepadName"                ], config.gamepadName                );
	Set<byte8>(member["gamepadButton"              ], config.gamepadButton              );
	Set<bool >(member["disablePlayerActorIdleTimer"], config.disablePlayerActorIdleTimer);
}

#pragma endregion



#pragma region ToConfig

void ToConfig_PlayerData
(
	PlayerData & config,
	rapidjson::Value & member
)
{
	config.character = Get<uint32>(member["character"]);
	config.costume   = Get<uint32>(member["costume"  ]);
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
	config.showSpeed               = Get<bool>(member["showSpeed"              ]);
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

		config.enable      = Get<bool      >(member["enable"     ]);
		config.playerCount = Get<new_size_t>(member["playerCount"]);

		for_all(playerIndex, PLAYER::COUNT)
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
		config.game           = Get<uint32>(member["game"          ]);
		config.mission        = Get<uint32>(member["mission"       ]);
		config.mode           = Get<uint32>(member["mode"          ]);
		config.room           = Get<uint32>(member["room"          ]);
		config.ignoreRoom     = Get<bool  >(member["ignoreRoom"    ]);
		config.position       = Get<uint32>(member["position"      ]);
		config.ignorePosition = Get<bool  >(member["ignorePosition"]);
		config.floor          = Get<uint8 >(member["floor"         ]);
		config.hitPoints      = Get<float >(member["hitPoints"     ]);
		config.magicPoints    = Get<float >(member["magicPoints"   ]);
		config.character      = Get<uint8 >(member["character"     ]);
		config.costume        = Get<uint32>(member["costume"       ]);
	}



	auto & config = Prep_arg(config);
	auto & member = root;

	config.welcome                         = Get<bool      >(member["welcome"                        ]);
	config.keyboardPlayerIndex             = Get<new_size_t>(member["keyboardPlayerIndex"            ]);
	config.enableCharacterSwitchController = Get<bool      >(member["enableCharacterSwitchController"]);
	config.characterSwitchControllerButton = Get<byte32    >(member["characterSwitchControllerButton"]);

	ToConfig_KeyData(config.characterSwitchControllerKeyData, member["characterSwitchControllerKeyData"]);

	for_all(playerIndex, PLAYER::COUNT)
	{
		ToConfig_BarsData(config.barsData[playerIndex], member["barsData"][playerIndex]);
	}

	ToConfig_MainOverlayData(config.mainOverlayData, member["mainOverlayData"]);

	config.mainSpeed           = Get<float>(member["mainSpeed"          ]);
	config.menuSpeed           = Get<float>(member["menuSpeed"          ]);
	config.cutsceneSpeed       = Get<float>(member["cutsceneSpeed"      ]);
	config.skipIntro           = Get<bool >(member["skipIntro"          ]);
	config.hideMouseCursor     = Get<bool >(member["hideMouseCursor"    ]);
	config.baseFrameRate       = Get<float>(member["baseFrameRate"      ]);
	config.targetFrameRate     = Get<float>(member["targetFrameRate"    ]);
	config.vSync               = Get<uint8>(member["vSync"              ]);
	config.windowPosX          = Get<int32>(member["windowPosX"         ]);
	config.windowPosY          = Get<int32>(member["windowPosY"         ]);
	config.borderless          = Get<bool >(member["borderless"         ]);
	config.forceWindowFocus    = Get<bool >(member["forceWindowFocus"   ]);
	config.infiniteHitPoints   = Get<bool >(member["infiniteHitPoints"  ]);
	config.infiniteMagicPoints = Get<bool >(member["infiniteMagicPoints"]);
	config.disableTimer        = Get<bool >(member["disableTimer"       ]);
	config.globalScale         = Get<float>(member["globalScale"        ]);

	GetArray<bool, countof(filterHelpers)>(config.disableFilters, member["disableFilters"]);

	config.showCredits = Get<bool>(member["showCredits"]);

	for_all(index, 3)
	{
		ToConfig_KeyData(config.keyData[index], member["keyData"][index]);
	}

	config.disableCenterCamera = Get<bool>(member["disableCenterCamera"]);

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

#pragma endregion



#include "../ConfigFunctions.h"
