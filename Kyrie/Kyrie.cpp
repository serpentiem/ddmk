#include "../Core/Core.h"

#include "Hooks.h"
#include "Steam.h"
#include "Vars.h"

#include "System/Actor.h"
#include "System/Event.h"
#include "System/File.h"
#include "System/Memory.h"
#include "System/Path.h"
#include "System/Window.h"

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
		if (!Steam_Init())
		{
			return 0;
		}










		System_Actor_Init();
		if (Config.Game.Multiplayer.enable)
		{
			System_Actor_ToggleSpawnExtension(true);
		}
		if (Config.Game.Multiplayer.enable)
		{
			System_Actor_ToggleCharacterDataConverter(true);
		}
		if (Config.Game.Multiplayer.enable)
		{
			System_Actor_ToggleCostumeFixes(true);
		}
		System_Actor_ToggleDisableIdleTimer(Config.System.Actor.disableIdleTimer);
		System_Event_Init();
		System_File_Init();
		if (Config.Game.Multiplayer.enable)
		{
			System_File_ToggleLoadAssetsExtension(true);
		}
		System_Memory_Init();
		if (Config.System.Memory.replaceAllocationFunctions)
		{
			System_Memory_ToggleReplaceAllocationFunctions(true);
		}





		System_Path_Init();
		System_Window_Init();


		if (Config.Game.Training.enable)
		{
			Game_Training_ToggleInfiniteHitPoints(Config.Game.Training.infiniteHitPoints);
			Game_Training_ToggleInfiniteMagicPoints(Config.Game.Training.infiniteMagicPoints);
			Game_Training_ToggleDisableTimer(Config.Game.Training.disableTimer);
		}


		System_Actor_ToggleSpawnExtension(true);
		System_Actor_ToggleCharacterDataConverter(true);






		Write<BYTE>((appBaseAddr + 0xB569  ), 0xEB); // Intro Button Infinite Timer
		//Write<BYTE>((appBaseAddr + 0xF362  ), 0xEB); // Skip Dialog
		//Write<BYTE>((appBaseAddr + 0x1540E1), 0xEB); // Disable Timer
	}
	return 1;
}
