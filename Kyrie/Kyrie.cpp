#include "../Core/Core.h"

#include "Hooks.h"
#include "Steam.h"

#include "System/Actor.h"
#include "System/Event.h"
#include "System/File.h"
#include "System/Memory.h"
#include "System/Path.h"
#include "System/Window.h"

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
		Log("trish lady costume dlc unlocked %u", IsDLCInstalled(359496));
		Log("crappy orb dlc unlocked %u", IsDLCInstalled(123));






		System_Actor_Init();
		System_Actor_Toggle(true);
		System_Actor_ToggleDisableIdleTimer(Config.System.Actor.disableIdleTimer);



		System_Event_Init();




		System_File_Init();
		System_File_Toggle(true);






		//System_Media_Init();
		//System_Media_ToggleSkipIntro(Config.System.Media.skipIntro);

		System_Memory_Init();
		System_Memory_Toggle(true);






		System_Path_Init();
		System_Window_Init();

		Write<BYTE>((appBaseAddr + 0xB569  ), 0xEB); // Intro Button Infinite Timer
		//Write<BYTE>((appBaseAddr + 0xF362  ), 0xEB); // Skip Dialog
		Write<BYTE>((appBaseAddr + 0x1540E1), 0xEB); // Disable Timer
	}
	return 1;
}
