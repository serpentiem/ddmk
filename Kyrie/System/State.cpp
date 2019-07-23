#include "State.h"

bool ActorAvailable()
{
	BYTE * addr = *(BYTE **)(appBaseAddr + 0xF240A4);
	if (!addr)
	{
		return false;
	}
	addr = *(BYTE **)(addr + 0x6CC);
	if (!addr)
	{
		return false;
	}
	addr = *(BYTE **)(addr + 0);
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
	BYTE * addr = *(BYTE **)(appBaseAddr + 0xF23F38);
	if (!addr)
	{
		return false;
	}
	addr = *(BYTE **)(addr + 0x3838);
	if (!addr)
	{
		return false;
	}
	uint8 event = *(uint8 *)(addr + 4);
	if (event != EVENT_GAME)
	{
		return false;
	}
	return true;
}
