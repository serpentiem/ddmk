#include "Pause.h"

bool pause = false;

void Pause(bool enable)
{
	LogFunction(enable);
	if (enable)
	{
		ToggleCursor(true);
	}
	else
	{
		if (Config.System.Input.hideMouseCursor)
		{
			ToggleCursor(false);
		}
	}
}
