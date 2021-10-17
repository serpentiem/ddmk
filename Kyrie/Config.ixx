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
		bool enable = false;
		size_t playerCount = 1;
		PlayerData playerData[PLAYER::COUNT] = {};
		size_t keyboard = 0;
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
		float  hitPoints      = 20000;
		float  magicPoints    = 10000;
		uint8  character      = CHARACTER::LADY;
		uint32 costume        = 3;
	}
	Arcade;



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
		bool showFocus = true;
		bool showFPS = true;
		bool showSizes = true;
		bool showFrameRateMultiplier = true;
		bool showEventData = true;
		bool showSpeed = true;

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

	float baseFrameRate   = 120.0f;
	float targetFrameRate = 120.0f;
	uint8 vSync           = 0;

	int32 windowPosX = 0;
	int32 windowPosY = 0;
	bool borderless = (debug) ? true : false;
	bool forceWindowFocus = true;



	bool infiniteHitPoints   = false;
	bool infiniteMagicPoints = false;
	bool disableTimer        = false;










	float globalScale = 1.0f;


	bool disableFilters[countof(filterHelpers)] = {};



	bool showCredits = true;


};






#pragma pack(pop)

#undef _



export Config defaultConfig;
export Config activeConfig;
export Config queuedConfig;




// @Todo: Prefer location.

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
	size_t size = 0;

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

	Log("fileSize      %u", size                 );
	Log("Config        %u", sizeof(Config)       );
	Log("activeConfig  %u", sizeof(activeConfig) );
	Log("queuedConfig  %u", sizeof(queuedConfig) );
	Log("defaultConfig %u", sizeof(defaultConfig));



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

	Log("Loaded Config");



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
