#include "Hotkeys.h"

void Hotkeys::TogglePause(BYTE * buffer)
{
	static bool execute = true;
	BYTE keys[] =
	{
		DIK_LCONTROL,
		DIK_D,
	};
	uint8 keysDown = 0;
	for (uint8 i = 0; i < countof(keys); i++)
	{
		if (buffer[keys[i]] & 0x80)
		{
			keysDown++;
		}
	}
	if (keysDown == countof(keys))
	{
		if (execute)
		{
			pause = !pause;
			PostMessageA(mainWindow, DM_PAUSE, 0, 0);
			execute = false;
		}
	}
	else
	{
		execute = true;
	}
}
