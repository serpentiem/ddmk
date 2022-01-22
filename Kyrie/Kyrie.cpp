import Core;
import Core_Input;

#include "../Core/Macros.h"

import Windows;

using namespace Windows;

import Actor;
import Arcade;
import Camera;
import Config;
import Event;
import File;
import Global;
import Graphics;
import Hooks;
import Input;
import Internal;
import Speed;
import Steam;
import Training;
import Vars;
import Window;

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
		InitLog("logs", "Kyrie.txt");

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



		InitConfig();
		LoadConfig();



		Internal_Init();



		File::Toggle(false);
		File::Toggle(true);

		Input::ToggleExtensions(false);
		Input::ToggleExtensions(activeConfig.Actor.enable);

		Actor::Toggle(false);
		Actor::Toggle(activeConfig.Actor.enable);

		Arcade::Toggle(false);
		Arcade::Toggle(activeConfig.Arcade.enable);

		ToggleDisableCenterCamera(false);
		ToggleDisableCenterCamera(activeConfig.disableCenterCamera);

		ToggleSkipIntro(false);
		ToggleSkipIntro(activeConfig.skipIntro);



		UpdateFilters();



		ToggleForceWindowFocus(false);
		ToggleForceWindowFocus(activeConfig.forceWindowFocus);

		ToggleInfiniteHitPoints(false);
		ToggleInfiniteHitPoints(activeConfig.infiniteHitPoints);

		ToggleInfiniteMagicPoints(false);
		ToggleInfiniteMagicPoints(activeConfig.infiniteMagicPoints);

		ToggleDisableTimer(false);
		ToggleDisableTimer(activeConfig.disableTimer);



		Event::Toggle(false);
		Event::Toggle(true);

		Speed::Toggle(false);
		Speed::Toggle(true);



		ToggleDisablePlayerActorIdleTimer(false);
		ToggleDisablePlayerActorIdleTimer(activeConfig.disablePlayerActorIdleTimer);



		Steam::Toggle(false);
		Steam::Toggle(true);

		Window::Toggle(false);
		Window::Toggle(true);



		XI::new_Init("xinput1_3.dll");

		Hooks::Init();
	}

	return 1;
}
