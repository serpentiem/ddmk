#include "BossRush.h"

void Game_BossRush_Toggle(bool enable)
{
	LogFunctionBool(enable);
	if (enable)
	{
		Write<BYTE>((appBaseAddr + 0x3A7CC2), 0); // Darkness Mission 22
		Write<BYTE>((appBaseAddr + 0x39BE2A), 0); // Darkness Mission 22 Skip Aerial Battle
	}
	else
	{
		Write<BYTE>((appBaseAddr + 0x3A7CC2), 0x80);
		Write<BYTE>((appBaseAddr + 0x39BE2A), 0x80);
	}
}
