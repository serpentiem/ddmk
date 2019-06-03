#include "State.h"

bool ActorAvailable()
{
	BYTE * addr = *(BYTE **)(appBaseAddr + 0xC90E28);
	if (!addr)
	{
		return false;
	}
	addr = *(BYTE **)(addr + 0x18);
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
	BYTE * addr = *(BYTE **)(appBaseAddr + 0xCA8918);
	if (!addr)
	{
		return false;
	}
	addr = *(BYTE **)(addr + 0x40);
	if (!addr)
	{
		return false;
	}
	DWORD event = *(DWORD *)(addr + 0x20);
	if (event != EVENT_GAME)
	{
		return false;
	}
	return true;
}
