#include "State.h"

// @Todo: Update.

bool ActorAvailable()
{
	byte8 * addr = *(byte8 **)(appBaseAddr + 0xC90E28);
	if (!addr)
	{
		return false;
	}
	addr = *(byte8 **)(addr + 0x18);
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
	byte8 * addr = *(byte8 **)(appBaseAddr + 0xCA8918);
	if (!addr)
	{
		return false;
	}
	addr = *(byte8 **)(addr + 0x40);
	if (!addr)
	{
		return false;
	}
	byte32 event = *(byte32 *)(addr + 0x20);
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
	byte8 ** addr = (byte8 **)(appBaseAddr + 0xCF2520);
	byte8 * item = addr[44];
	if (!item)
	{
		return false;
	}
	uint8 & alpha = *(uint8 *)(item + 0x6920);
	return (alpha > 0) ? true : false;
}
