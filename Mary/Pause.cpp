#include "Pause.h"





bool pause = false;

void Pause(bool enable)
{
	Log("%s %u", FUNC_NAME, enable);
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
