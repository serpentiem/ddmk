module;
#include "../Core/Core.h"

#include "Vars.h"
export module Other;

import Config;

float32 * orbReachAddr = 0;

export void UpdateOrbReach()
{
	LogFunction();

	*orbReachAddr = activeConfig.orbReach;
}

export void Other_Init()
{
	LogFunction();

	// Orb Reach
	{
		auto dest = HighAlloc(4);
		if (!dest)
		{
			Log("HighAlloc failed.");

			return;
		}

		orbReachAddr = reinterpret_cast<float32 *>(dest);

		WriteAddress((appBaseAddr + 0x1B655F), dest, 8);
		/*
		dmc3.exe+1B655F - F3 0F10 35 2DFB3000- movss xmm6,[dmc3.exe+4C6094]
		dmc3.exe+1B6567 - EB 2B              - jmp dmc3.exe+1B6594
		*/
	}
}
