export module HUD;

import Core;

#include "../Core/Macros.h"

import File;
import Global;
import Internal;
import Model;
import Vars;

#define debug false



export void ToggleForceVisibleHUD(bool enable)
{
	static bool run = false;



	// Main
	{
		auto addr = (appBaseAddr + 0x3CCC18);
		constexpr uint32 size = 4;
		/*
		dmc1.exe+3CCC18 - 66 41 FF 09      - dec word ptr [r9]
		dmc1.exe+3CCC1C - 0FB7 93 A2170000 - movzx edx,word ptr [rbx+000017A2]
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			SetMemory(addr, 0x90, size, MemoryFlags_VirtualProtectDestination);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}



	// Red Orbs
	{
		auto addr = (appBaseAddr + 0x3CE991);
		constexpr uint32 size = 4;
		/*
		dmc1.exe+3CE991 - 66 FF 43 18 - inc word ptr [rbx+18]
		dmc1.exe+3CE995 - 0FBF 43 18  - movsx eax,word ptr [rbx+18]
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			SetMemory(addr, 0x90, size, MemoryFlags_VirtualProtectDestination);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}



	run = true;
}

#ifdef __GARBAGE__
#endif
