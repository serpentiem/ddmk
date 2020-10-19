#include "Speed.h"

static DWORD SetGlobalSpeedThread(LPVOID)
{
	LogFunction();
	do
	{
		LoopStart:
		{
			BYTE * addr = *(BYTE **)(appBaseAddr + 0xF2429C);
			if (!addr)
			{
				goto LoopEnd;
			}
			float & globalSpeed = *(float *)(addr + 0x7C);
			if (InGame())
			{
				globalSpeed = Config.Speed.global;
			}
			else
			{
				globalSpeed = Config.Speed.menu;
			}
		}
		LoopEnd:
		Sleep(100);
	}
	while (true);
	return 1;
}

void Speed_Init()
{
	LogFunction();
	CreateThread(0, 4096, SetGlobalSpeedThread, 0, 0, 0);
}
