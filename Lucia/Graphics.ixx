export module Graphics;

import Core;

#include "../Core/Macros.h"

import Config;
import Global;
import Vars;

#define debug false

//#include "Macros.h"




double g_defaultFrequency = 0;

double * g_frequencyAddr = 0;





namespaceStart(Graphics);

export void Init()
{
	LogFunction();

	g_defaultFrequency = *reinterpret_cast<double *>(appBaseAddr + 0x5A58C8);
	/*
	dmc2.exe+25CAAE - F2 0F10 3D 128E3400    - movsd xmm7,[dmc2.exe+5A58C8]
	dmc2.exe+25CAB6 - F3 44 0F10 05 89F70A00 - movss xmm8,[dmc2.exe+30C248]
	*/

	g_frequencyAddr = reinterpret_cast<double *>(HighAlloc(8));
	if (!g_frequencyAddr)
	{
		Log("HighAlloc failed.");

		return;
	}

	*g_frequencyAddr = g_defaultFrequency;



	constexpr bool enable = true;
	static bool run = false;



	{
		auto addr     = (appBaseAddr + 0x25CAC6);
		auto jumpAddr = (appBaseAddr + 0x25CACB);
		constexpr uint32 size = 5;
		/*
		dmc2.exe+25CAC6 - 48 8D 4C 24 70 - lea rcx,[rsp+70]
		dmc2.exe+25CACB - E8 CA640900    - call dmc2.exe+2F2F9A
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0xF2, 0x0F, 0x10, 0x3D, 0x00, 0x00, 0x00, 0x00, // movsd xmm7,[]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(0, jumpAddr, false, true, (sizeof(sect0) + size));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			CopyMemory((func.sect0 + sizeof(sect0)), addr, size, MemoryFlags_VirtualProtectSource);
			WriteAddress(func.sect0, g_frequencyAddr, 8);
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

	*g_frequencyAddr = (g_defaultFrequency * (60.0 / activeConfig.frameRate));
}




