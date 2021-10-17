module;
#include <string.h>
export module Graphics;

import Core;

#include "../Core/Macros.h"

import Config;
import Global;
import Vars;

#define debug false



uint64   defaultFrequency = 0;
uint64 * frequencyAddr    = 0;



namespaceStart(Graphics);

export void Toggle(bool enable)
{
	LogFunction(enable);

	static bool run = false;



	if (!run)
	{
		auto & frequency = *reinterpret_cast<uint64 *>(appBaseAddr + 0xF292E0);
		/*
		dmc4.exe+AEB8A5 - A3 E0923201    - mov [dmc4.exe+F292E0],eax
		dmc4.exe+AEB8AA - 89 15 E4923201 - mov [dmc4.exe+F292E4],edx
		*/

		defaultFrequency = frequency;
		frequencyAddr    = &frequency;
	}



	run = true;
}

namespaceEnd();







export void UpdateFrameRate()
{
	LogFunction();

	g_frameRateMultiplier = (activeConfig.baseFrameRate / activeConfig.targetFrameRate);

	*frequencyAddr = static_cast<uint64>(static_cast<float>(defaultFrequency) * g_frameRateMultiplier);
}



export void UpdateFilters()
{
	LogFunction();

	const char * name = "_";
	auto size = strlen(name);

	for_all(index, countof(filterHelpers))
	{
		auto & filterHelper = filterHelpers[index];
		auto & disableFilter = activeConfig.disableFilters[index];

		auto dest = (appBaseAddr + filterHelper.off);

		if (disableFilter)
		{
			CopyMemory
			(
				dest,
				name,
				size,
				MemoryFlags_VirtualProtectDestination
			);
		}
	}
}










