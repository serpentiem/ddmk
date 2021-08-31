export module Input;

import Core;

#include "../Core/Macros.h"

import Vars;

import Config;
import Global;

export void ToggleCursor()
{
	if (g_show)
	{
		Windows_ToggleCursor(true);
	}
	else
	{
		Windows_ToggleCursor(!activeConfig.hideMouseCursor);
	}
}
