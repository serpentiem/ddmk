export module Graphics;

import Core;

#include "../Core/Macros.h"

import Config;
import Global;
import Vars;

#define debug false



double   defaultFrequency = 0;
double * frequencyAddr    = 0;



namespaceStart(Graphics);

export void Toggle(bool enable)
{
	LogFunction(enable);

	static bool run = false;



	if (!run)
	{
		defaultFrequency = *reinterpret_cast<double *>(appBaseAddr + 0x4E29A8);
		/*
		dmc1.exe+260AFA - F2 44 0F10 2D A51E2800 - movsd xmm13,[dmc1.exe+4E29A8]
		dmc1.exe+260B03 - 44 0F29 B4 24 20010000 - movaps [rsp+00000120],xmm14
		*/

		frequencyAddr = reinterpret_cast<double *>(HighAlloc(8));
		if (!frequencyAddr)
		{
			Log("HighAlloc failed.");

			return;
		}

		*frequencyAddr = defaultFrequency;
	}



	{
		auto addr     = (appBaseAddr + 0x260B63);
		auto jumpAddr = (appBaseAddr + 0x260B68);
		constexpr uint32 size = 5;
		/*
		dmc1.exe+260B63 - 48 8D 4C 24 20 - lea rcx,[rsp+20]
		dmc1.exe+260B68 - FF 15 AA651A00 - call qword ptr [dmc1.exe+407118]
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0xF2, 0x44, 0x0F, 0x10, 0x2D, 0x00, 0x00, 0x00, 0x00, // movsd xmm13,[]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, (sizeof(sect0) + size));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			CopyMemory((func.sect0 + sizeof(sect0)), addr, size, MemoryFlags_VirtualProtectSource);
			WriteAddress(func.sect0, frequencyAddr, 9);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}



	run = true;
}

namespaceEnd();



export void UpdateFrameRate()
{
	LogFunction();

	g_frameRateMultiplier = (60 / activeConfig.frameRate);

	*frequencyAddr = (defaultFrequency * static_cast<double>(g_frameRateMultiplier));
}
