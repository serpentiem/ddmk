#include "Camera.h"

DWORD UpdateCameraThread(LPVOID)
{
	LogFunction();
	do
	{
		Start:
		{
			if (!Config.System.Camera.apply)
			{
				goto End;
			}
			if (!InGame())
			{
				goto End;
			}
			BYTE * addr = *(BYTE **)(appBaseAddr + 0xF59F00);
			if (!addr)
			{
				goto End;
			}
			addr = *(BYTE **)(addr + 0x140);
			if (!addr)
			{
				goto End;
			}
			addr = *(BYTE **)(addr + 0x468);
			if (!addr)
			{
				goto End;
			}
			float32 & height     = *(float32 *)(addr + 0xD0);
			float32 & tilt       = *(float32 *)(addr + 0xD4);
			float32 & zoom1      = *(float32 *)(addr + 0xD8);
			float32 & zoomLockOn = *(float32 *)(addr + 0xDC);
			float32 & zoom2      = *(float32 *)(addr + 0xE4);
			height     = Config.System.Camera.height;
			tilt       = Config.System.Camera.tilt;
			zoom1      = Config.System.Camera.zoom1;
			zoomLockOn = Config.System.Camera.zoomLockOn;
			zoom2      = Config.System.Camera.zoom2;
		}
		End:
		Sleep(Config.System.Camera.rate);
	}
	while (true);
	return 1;
}

void System_Camera_Init()
{
	LogFunction();
	CreateThread(0, 4096, UpdateCameraThread, 0, 0, 0);
}
