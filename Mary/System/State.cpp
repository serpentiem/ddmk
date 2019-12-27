#include "State.h"

// @Todo: Update.

bool ActorAvailable()
{
	byte * addr = *(byte **)(appBaseAddr + 0xC90E28);
	if (!addr)
	{
		return false;
	}
	addr = *(byte **)(addr + 0x18);
	if (!addr)
	{
		return false;
	}
	return true;
}

bool InGame()
{
	if (!ActorAvailable())
	{
		return false;
	}
	byte * addr = *(byte **)(appBaseAddr + 0xCA8918);
	if (!addr)
	{
		return false;
	}
	addr = *(byte **)(addr + 0x40);
	if (!addr)
	{
		return false;
	}
	dword event = *(dword *)(addr + 0x20);
	if (event != EVENT_GAME)
	{
		return false;
	}
	return true;
}

bool HUD_IsVisible()
{
	if (!InGame())
	{
		return false;
	}
	byte ** addr = (byte **)(appBaseAddr + 0xCF2520);
	byte * item = addr[44];
	if (!item)
	{
		return false;
	}
	uint8 & alpha = *(uint8 *)(item + 0x6920);
	return (alpha > 0) ? true : false;
}
