#include "Event.h"

void System_Event_ToggleReplaceAutosaveStart(bool enable)
{
	LogFunctionBool(enable);
	if (enable)
	{
		Write<BYTE *>((appBaseAddr + 0x10B1E2), (appBaseAddr + 0xC27DC0));
		Write<BYTE *>((appBaseAddr + 0x10B248), (appBaseAddr + 0xC27DC0));
	}
	else
	{
		Write<BYTE *>((appBaseAddr + 0x10B1E2), (appBaseAddr + 0xC1FF20));
		Write<BYTE *>((appBaseAddr + 0x10B248), (appBaseAddr + 0xC1FF20));
	}
}

void System_Event_EvaluateToggleReplaceAutosaveStart()
{
	LogFunction();
	if (Config.System.Media.skipIntro)
	{
		System_Event_ToggleReplaceAutosaveStart(true);
	}
	else
	{
		System_Event_ToggleReplaceAutosaveStart(false);
	}
}
