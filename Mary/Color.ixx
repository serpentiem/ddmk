#ifndef __MODULE_COLOR__
#define __MODULE_COLOR__

module;
#include "../Core/Core.h"
export module ModuleName(Color);

import ModuleName(Config);

#ifdef __INTELLISENSE__
#include "Config.ixx"
#endif

export void Color_UpdateConfig(CONFIG & config)
{
	LogFunction();

	constexpr uint8 count = (sizeof(CONFIG::Color) / 4);

	auto vars = reinterpret_cast<float32 *>(config.Color.Dante.airHike);

	for_all(uint8, index, count)
	{
		vars[index] /= 255;
	}
}

#endif
