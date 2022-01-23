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

#define debug false



const char * directoryName = "configs";
const char * fileName      = "Lucia.json";

char location[64] = {};



#define _(size) struct { byte8 Prep_Merge(padding_, __LINE__)[size]; }

#pragma pack(push, 1)



export struct Config
{
	bool welcome = (debug) ? false : true;



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

		MainOverlayData()
		{
			if constexpr (debug)
			{
				enable = true;
			}
		}
	}
	mainOverlayData;



	float frameRate = 60;
	uint8 vSync     = 0;

	bool hideMouseCursor = false;



	int32 windowPosX = 0;
	int32 windowPosY = 0;
	bool forceWindowFocus = true;

	float globalScale = 1;

	bool showCredits = (debug) ? false : true;



	KeyData keyData[1] =
	{
		{
			{
				KEY::LEFT_CONTROL,
				KEY::D
			},
			2
		},
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

	auto & member = root;
	auto & config = Prep_arg(config);

	Create<bool>(member, "welcome", config.welcome);



	{
		auto & member2 = Create<struct_t>(member, "mainOverlayData");
		auto & config2 = config.mainOverlayData;

		CreateMembers_OverlayDataContent(member2, config2);

		Create<bool>(member2, "showFocus"              , config2.showFocus              );
		Create<bool>(member2, "showFPS"                , config2.showFPS                );
		Create<bool>(member2, "showSizes"              , config2.showSizes              );
		Create<bool>(member2, "showFrameRateMultiplier", config2.showFrameRateMultiplier);
	}



	Create<float>(member, "frameRate"       , config.frameRate       );
	Create<uint8>(member, "vSync"           , config.vSync           );
	Create<bool >(member, "hideMouseCursor" , config.hideMouseCursor );
	Create<int32>(member, "windowPosX"      , config.windowPosX      );
	Create<int32>(member, "windowPosY"      , config.windowPosY      );
	Create<bool >(member, "forceWindowFocus", config.forceWindowFocus);
	Create<float>(member, "globalScale"     , config.globalScale     );
	Create<bool >(member, "showCredits"     , config.showCredits     );



	{
		auto & member = CreateArray<struct_t, 1>(root, "keyData");
		auto & config = Prep_arg(config).keyData;

		for_all(index, 1)
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

	Set<bool>(member["showFocus"], config.showFocus);
	Set<bool>(member["showFPS"], config.showFPS);
	Set<bool>(member["showSizes"], config.showSizes);
	Set<bool>(member["showFrameRateMultiplier"], config.showFrameRateMultiplier);
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

	auto & member = root;
	auto & config = Prep_arg(config);

	Set<bool>(member["welcome"], config.welcome);



	ToJSON_MainOverlayData(member["mainOverlayData"], config.mainOverlayData);



	Set<float>(member["frameRate"       ], config.frameRate       );
	Set<uint8>(member["vSync"           ], config.vSync           );
	Set<bool >(member["hideMouseCursor" ], config.hideMouseCursor );
	Set<int32>(member["windowPosX"      ], config.windowPosX      );
	Set<int32>(member["windowPosY"      ], config.windowPosY      );
	Set<bool >(member["forceWindowFocus"], config.forceWindowFocus);
	Set<float>(member["globalScale"     ], config.globalScale     );
	Set<bool >(member["showCredits"     ], config.showCredits     );



	for_all(index, 1)
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

	auto & config = Prep_arg(config);
	auto & member = root;

	config.welcome = Get<bool>(member["welcome"]);



	ToConfig_MainOverlayData(config.mainOverlayData             , member["mainOverlayData"             ]);



	config.frameRate        = Get<float>(member["frameRate"       ]);
	config.vSync            = Get<uint8>(member["vSync"           ]);
	config.hideMouseCursor  = Get<bool >(member["hideMouseCursor" ]);
	config.windowPosX       = Get<int32>(member["windowPosX"      ]);
	config.windowPosY       = Get<int32>(member["windowPosY"      ]);
	config.forceWindowFocus = Get<bool >(member["forceWindowFocus"]);
	config.globalScale      = Get<float>(member["globalScale"     ]);
	config.showCredits      = Get<bool >(member["showCredits"     ]);



	for_all(index, 1)
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
