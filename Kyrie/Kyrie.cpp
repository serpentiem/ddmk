#include "../Core/Core.h"

#include "Hooks.h"
#include "Speed.h"
#include "Steam.h"
#include "Vars.h"

#include "System/Actor.h"
#include "System/Event.h"
#include "System/File.h"
#include "System/Input.h"
#include "System/Memory.h"
#include "System/Window.h"

#include "Game/Arcade.h"
#include "Game/Training.h"

const char * Log_directory = "logs";
const char * Log_file      = "Kyrie.txt";

uint32 mainChunkSize = (64 * 1024 * 1024);

DWORD DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		Log_Init();
		Log("Session started.");
		if (!Memory_Init())
		{
			return 0;
		}
		Config_Init();
		LoadConfig();
		Hooks_Init();
		Speed_Init();
		if (!Steam_Init())
		{
			return 0;
		}
		System_Actor_Init();
		System_Actor_ToggleSpawnExtension(Config.Game.Multiplayer.enable);
		System_Actor_ToggleCharacterDataConverter(Config.Game.Multiplayer.enable);
		System_Actor_ToggleCostumeFixes(Config.Game.Multiplayer.enable);
		System_Actor_ToggleDisableIdleTimer(Config.System.Actor.disableIdleTimer);
		System_Event_Init();
		System_Event_ToggleSkipIntro(Config.System.Event.skipIntro);
		System_File_Init();
		System_File_ToggleLoadAssetsExtension(Config.Game.Multiplayer.enable);
		System_Memory_Init();
		System_Memory_ToggleReplaceAllocationFunctions(Config.System.Memory.replaceAllocationFunctions);
		System_Window_Init();
		System_Window_ToggleForceFocus(Config.System.Window.forceFocus);

		Game_Arcade_Toggle(Config.Game.Arcade.enable);
		if (Config.Game.Training.enable)
		{
			Game_Training_ToggleInfiniteHitPoints(Config.Game.Training.infiniteHitPoints);
			Game_Training_ToggleInfiniteMagicPoints(Config.Game.Training.infiniteMagicPoints);
			Game_Training_ToggleDisableTimer(Config.Game.Training.disableTimer);
		}
	}
	return 1;
}
