export module Window;

import Core;

#include "../Core/Macros.h"

import Config;
import Global;
import Vars;



export void ToggleForceWindowFocus(bool enable)
{
	LogFunction(enable);

	static bool run = false;



	{
		auto addr = (appBaseAddr + 0x1807B);
		constexpr uint32 size = 6;
		/*
		dmc1.exe+1807B - 0F85 E7000000     - jne dmc1.exe+18168
		dmc1.exe+18081 - 48 8B 0D C0005C00 - mov rcx,[dmc1.exe+5D8148]
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			Write<byte16>(addr, 0xE990);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Force gamepad focus.
	{
		auto addr = (appBaseAddr + 0x154AC);
		auto dest = (appBaseAddr + 0x154B2);
		constexpr uint32 size = 6;
		/*
		dmc1.exe+154AC - 0F84 DF030000        - je dmc1.exe+15891
		dmc1.exe+154B2 - 48 89 9C 24 60010000 - mov [rsp+00000160],rbx
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			WriteAddress(addr, dest, size);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}



	run = true;
}
