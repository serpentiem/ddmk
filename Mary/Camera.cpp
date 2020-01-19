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
