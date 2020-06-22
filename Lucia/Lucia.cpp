#include "../Core/Core.h"

#include "Hooks.h"

#include "System/Graphics.h"
#include "System/Window.h"

const char * Log_directory = "logs";
const char * Log_file      = "Lucia.txt";

uint32 Memory_size = (64 * 1024 * 1024);

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

		System_Graphics_UpdateFrameRate(Config);
		System_Window_ToggleForceFocus(Config.System.Window.forceFocus);
	}
	return 1;
}
