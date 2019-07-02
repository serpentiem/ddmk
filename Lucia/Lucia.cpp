#include "../Core/Core.h"

#include "Hooks.h"

#include "System/Window.h"

const char * Log_directory = "logs";
const char * Log_file      = "Lucia.txt";

uint64 mainChunkSize = (64 * 1024 * 1024);

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

		System_Window_ToggleForceFocus(true);
	}
	return 1;
}
