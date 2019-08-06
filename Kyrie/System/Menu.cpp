#include "Menu.h"

void System_Menu_Autosave_ToggleDisableTimer(bool enable)
{
	LogFunctionBool(enable);
	if (enable)
	{
		vp_memset((appBaseAddr + 0xB542), 0x90, 8);
		BYTE buffer[] =
		{
			0x0F, 0x57, 0xC0, //xorps xmm0,xmm0
		};
		vp_memcpy((appBaseAddr + 0xB542), buffer, sizeof(buffer));
	}
	else
	{
		BYTE buffer[] =
		{
			0xF3, 0x0F, 0x58, 0x86, 0xD4, 0x02, 0x00, 0x00, //addss xmm0,dword ptr [esi+000002D4]
		};
		vp_memcpy((appBaseAddr + 0xB542), buffer, sizeof(buffer));
	}
}

void System_Menu_Main_ToggleAutoConfirm(bool enable)
{
	LogFunctionBool(enable);
	if (enable)
	{
		WriteAddress((appBaseAddr + 0x7CC2D), (appBaseAddr + 0x7CC33), 6); // Press Any Button
		Write<BYTE>((appBaseAddr + 0x7CFC2), 0xEB);                        // Level 1 Keyboard
		Write<BYTE>((appBaseAddr + 0x7C00E), 0xEB);                        // Level 2 Keyboard
	}
	else
	{
		WriteAddress((appBaseAddr + 0x7CC2D), (appBaseAddr + 0x7CCBA), 6);
		Write<BYTE>((appBaseAddr + 0x7CFC2), 0x75);
		Write<BYTE>((appBaseAddr + 0x7C00E), 0x75);
	}
}

void System_Menu_Main_EvaluateToggleAutoConfirm()
{
	LogFunction();
	if (Config.Game.Arcade.enable)
	{
		System_Menu_Main_ToggleAutoConfirm(true);
	}
	else
	{
		System_Menu_Main_ToggleAutoConfirm(false);
	}
}

void System_Menu_Main_ToggleDisableTimer(bool enable)
{
	LogFunctionBool(enable);
	if (enable)
	{
		vp_memset((appBaseAddr + 0x11DBD2), 0x90, 3);
	}
	else
	{
		BYTE buffer[] =
		{
			0xFF, 0x47, 0x54, //inc [edi+54]
		};
		vp_memcpy((appBaseAddr + 0x11DBD2), buffer, sizeof(buffer));
	}
}

void System_Menu_MissionStart_ToggleAutoConfirm(bool enable)
{
	LogFunctionBool(enable);
	if (enable)
	{
		WriteAddress((appBaseAddr + 0x77DED), (appBaseAddr + 0x77DF3), 6);
	}
	else
	{
		WriteAddress((appBaseAddr + 0x77DED), (appBaseAddr + 0x77EE4), 6);
	}
}

void System_Menu_MissionStart_EvaluateToggleAutoConfirm()
{
	LogFunction();
	if (Config.Game.Arcade.enable)
	{
		System_Menu_MissionStart_ToggleAutoConfirm(true);
	}
	else
	{
		System_Menu_MissionStart_ToggleAutoConfirm(false);
	}
}
