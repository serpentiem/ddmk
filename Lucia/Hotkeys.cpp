#include "Hotkeys.h"

void Hotkeys_TogglePause(BYTE * state)
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
		if (state[keys[i]] & 0x80)
		{
			keysDown++;
		}
	}
	if (keysDown == countof(keys))
	{
		if (execute)
		{
			pause = !pause;
			PostMessageA(appWindow, DM_PAUSE, 0, 0);
			execute = false;
		}
	}
	else
	{
		execute = true;
	}
}
