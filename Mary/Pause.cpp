#include "Pause.h"





bool pause = false;

void Pause(bool enable)
{
	//Log("%s %u", FUNC_NAME, enable);
	if (enable)
	{
		Windows_ToggleCursor(true);
	}
	else
	{
		if (Config.System.Input.hideMouseCursor)
		{
			Windows_ToggleCursor(false);
		}
	}
}
