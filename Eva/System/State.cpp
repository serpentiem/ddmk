#include "State.h"








bool InGame()
{
	BYTE * actorBaseAddr = *(BYTE **)(appBaseAddr + 0x4CB6BA0 + 8);
	if (!actorBaseAddr)
	{
		return false;
	}
	BYTE * addr = *(BYTE **)(appBaseAddr + 0x5EAB88);
	if (!addr)
	{
		return false;
	}
	DWORD event = *(DWORD *)(addr + 0x1CA4);
	if (!(event & 0x2000))
	{
		return false;
	}
	if (!(event & 0x8000))
	{
		return false;
	}
	return true;
}
