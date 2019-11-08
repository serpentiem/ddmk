#include "State.h"

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
