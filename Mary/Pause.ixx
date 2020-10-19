// @Todo: Review.

module;
#include "../Core/Core.h"
export module Pause;

import Config;

export bool pause = false;

export void Pause(bool enable)
{
	if (enable)
	{
		Windows_ToggleCursor(true);
	}
	else
	{
		if (activeConfig.Input.hideMouseCursor)
		{
			Windows_ToggleCursor(false);
		}
	}
}
