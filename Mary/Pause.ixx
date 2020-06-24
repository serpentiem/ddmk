#ifndef __MODULE_PAUSE__
#define __MODULE_PAUSE__

module;
#include "../Core/Core.h"
export module ModuleName(Pause);

import ModuleName(Config);

#ifdef __INTELLISENSE__
#include "Config.ixx"
#endif

export bool pause = false;

export void Pause(bool enable)
{
	if (enable)
	{
		Windows_ToggleCursor(true);
	}
	else
	{
		if (Config.Input.hideMouseCursor)
		{
			Windows_ToggleCursor(false);
		}
	}
}

#endif
