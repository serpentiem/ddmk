module;
#include "../Core/Core.h"

#include "Vars.h"
export module Graphics;

import Config;

double g_defaultFrequency = 0;

double * g_frequencyAddr = 0;

export void Graphics_Init()
{
	LogFunction();

	g_defaultFrequency = *reinterpret_cast<double *>(appBaseAddr + 0x505E38);

	g_frequencyAddr = reinterpret_cast<double *>(HighAlloc(8));
	if (!g_frequencyAddr)
	{
		Log("HighAlloc failed.");

		return;
	}

	*g_frequencyAddr = g_defaultFrequency;

	{
		constexpr byte8 sect0[] =
		{
			0xF2, 0x0F, 0x10, 0x3D, 0x00, 0x00, 0x00, 0x00, // movsd xmm7,[]
			0x48, 0x8D, 0x4C, 0x24, 0x20,                   // lea rcx,[rsp+20]
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x2C5EB5), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteAddress(func.sect0, g_frequencyAddr, 8);
		WriteJump((appBaseAddr + 0x2C5EB0), func.addr);
		/*
		dmc3.exe+2C5EB0 - 48 8D 4C 24 20 - lea rcx,[rsp+20]
		dmc3.exe+2C5EB5 - FF 15 1D930800 - call qword ptr [dmc3.exe+34F1D8]
		*/
	}
}

export void UpdateFrameRate()
{
	LogFunction();

	*g_frequencyAddr = (g_defaultFrequency * (60.0 / activeConfig.Graphics.frameRate));
}
