#include "Pause.h"

bool pause = false;

void Pause(bool enable)
{
	LogFunction();
	if (enable)
	{
		ToggleCursor(true);
	}
	else
	{
		if (Config.System.Input.Mouse.hideCursor)
		{
			ToggleCursor(false);
		}
	}
}
