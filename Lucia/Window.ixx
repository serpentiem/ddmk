export module Window;

import Core;

#include "../Core/Macros.h"

import Core_ImGui;

import Config;
import Global;
import Vars;



export void ToggleForceWindowFocus(bool enable)
{
	static bool run = false;



	{
		auto addr = (appBaseAddr + 0x42533);
		constexpr uint32 size = 6;
		/*
		dmc2.exe+42533 - 0F85 97000000 - jne dmc2.exe+425D0
		dmc2.exe+42539 - B9 01000000   - mov ecx,00000001
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
		auto addr = (appBaseAddr + 0x30CF9);
		auto dest = (appBaseAddr + 0x30CFF);
		constexpr uint32 size = 6;
		/*
		dmc2.exe+30CF9 - 0F84 86080000        - je dmc2.exe+31585
		dmc2.exe+30CFF - 48 89 AC 24 C8000000 - mov [rsp+000000C8],rbp
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
