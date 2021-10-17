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

		MainOverlayData()
		{
			if constexpr (debug)
			{
				enable = true;
			}
		}
	}
	mainOverlayData;

	bool skipIntro = (debug) ? true : false;

	double frameRate = (debug) ? 80 : 60;
	uint8 vSync      = (debug) ? 1  : 0;

	bool hideMouseCursor = false;

	bool forceWindowFocus = true;

	float globalScale = 1;

	bool showCredits = true;
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
