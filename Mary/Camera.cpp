#include "Camera.h"

void Camera_Update(CONFIG & config)
{
	// @Todo: Add to vars.
	auto addr = *(byte8 **)(appBaseAddr + 0xC8FBD0);
	if (!addr)
	{
		return;
	}
	addr = *(byte8 **)(addr + 0x498);
	if (!addr)
	{
		return;
	}
	auto & height     = *(float32 *)(addr + 0xD0) = config.Camera.height;
	auto & tilt       = *(float32 *)(addr + 0xD4) = config.Camera.tilt;
	auto & zoom       = *(float32 *)(addr + 0xD8) = config.Camera.zoom;
	auto & zoomLockOn = *(float32 *)(addr + 0xE0) = config.Camera.zoomLockOn;
}



byte8 * Camera_followBaseAddr = 0;


void Camera_Init()
{


	// @Research: Maybe a toggle is better.
	{
		constexpr byte8 sect0[] =
		{
			0x48, 0xBA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rdx,Camera_followBaseAddr
			0x48, 0x8B, 0x12,                                           //mov rdx,[rdx]
			0x0F, 0x28, 0x82, 0x80, 0x00, 0x00, 0x00,                   //movaps xmm0,[rdx+00000080]
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x571C3), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*reinterpret_cast<byte8 ***>(func.sect0 + 2) = &Camera_followBaseAddr;
		//WriteJump((appBaseAddr + 0x571BC), func.addr, 2);
		/*
		dmc3.exe+571BC - 0F28 82 80000000 - movaps xmm0,[rdx+00000080]
		dmc3.exe+571C3 - 0F29 81 90010000 - movaps [rcx+00000190],xmm0
		*/
	}




}








