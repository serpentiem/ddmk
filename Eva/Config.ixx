module;
#include <stdio.h>
#include <string.h>
export module Config;

import Core;

#include "../Core/Macros.h"

import Windows;

using namespace Windows;

import Vars;

#define debug false



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
		uint8  character       = CHARACTER::DANTE;
		uint8  hitPoints       = 30;
		uint8  magicPoints     = 10;
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
		bool showSizes = true;
		bool showEventData = true;
		bool showPosition = true;

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

	double frameRate = (debug) ? 80 : 60;
	uint8 vSync      = (debug) ? 1  : 0;

	bool hideMouseCursor = (debug) ? false : true;

	bool forceWindowFocus = true;

	bool infiniteHitPoints   = false;
	bool infiniteMagicPoints = false;
	bool disableTimer        = false;



	bool disableIdleTimer          = (debug) ? true : false;
	bool screenEffectForceMaxTimer = (debug) ? true : false;
	bool forceVisibleHUD           = false;

	float globalScale = 1;
};

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

	snprintf(g_path, sizeof(g_path), "%s\\%s", directoryName, filename);




}
