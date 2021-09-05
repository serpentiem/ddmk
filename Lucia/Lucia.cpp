import Core;

#include "../Core/Macros.h"

import Windows;

import Config;
import Global;
import Graphics;
import Hooks;
import Vars;
import Window;

using namespace Windows;

#define debug false

uint32 DllMain
(
	HINSTANCE instance,
	uint32 reason,
	LPVOID reserved
)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		Core_Log_Init("logs", "Lucia.txt");

		Log("Session started.");

		if (!Core_Memory_Init())
		{
			Log("Core_Memory_Init failed.");

			return 0;
		}

		if (!memoryData.InitData(64 * 1024 * 1024))
		{
			Log("memoryData.InitData failed.");

			return 0;
		}

		SetMemory
		(
			memoryData.dataAddr,
			0xCC,
			memoryData.dataSize
		);

		if (!protectionHelper.Init(4096))
		{
			Log("protectionHelper.Init failed.");

			return 0;
		}

		if
		(
			!backupHelper.Init
			(
				(8 * 1024 * 1024),
				(1 * 1024 * 1024)
			)
		)
		{
			Log("backupHelper.Init failed.");

			return 0;
		}

		Config_Init("configs", "Lucia.bin");

		LoadConfig();





		Graphics::Init();
		UpdateFrameRate();

		ToggleForceWindowFocus(false);
		ToggleForceWindowFocus(activeConfig.forceWindowFocus);










		// // Remove labels.
		// SetMemory
		// (
		// 	(appBaseAddr + 0x50CDE6),
		// 	0,
		// 	35,
		// 	MemoryFlags_VirtualProtectDestination
		// );

		Hooks::Init();
	}

	return 1;
}
