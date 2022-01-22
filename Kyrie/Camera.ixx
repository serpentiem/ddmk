export module Camera;

import Core;

#include "../Core/Macros.h"

import Config;
import Global;
import Vars;

#define debug false



export void ToggleDisableCenterCamera(bool enable)
{
	LogFunction(enable);

	static bool run = false;



	{
		auto addr = (appBaseAddr + 0x12BEB4);
		constexpr new_size_t size = 8;
		/*
		dmc4.exe+12BEB4 - F3 0F11 86 28020000 - movss [esi+00000228],xmm0
		dmc4.exe+12BEBC - 0F57 C0             - xorps xmm0,xmm0
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

	{
		auto addr = (appBaseAddr + 0x12BEBF);
		constexpr new_size_t size = 24;
		/*
		dmc4.exe+12BEBF - F3 0F11 96 20020000 - movss [esi+00000220],xmm2
		dmc4.exe+12BEC7 - F3 0F11 8E 24020000 - movss [esi+00000224],xmm1
		dmc4.exe+12BECF - F3 0F11 86 2C020000 - movss [esi+0000022C],xmm0
		dmc4.exe+12BED7 - 00 9E 85020000      - add [esi+00000285],bl
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
