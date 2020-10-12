module;
#include "../Core/Core.h"

#include "Vars.h"
export module Camera;

import Config;

// @Todo: Update with CAMERA_DATA.
export void Camera_Update(Config & config)
{
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
	auto & height = *(float32 *)(addr + 0xD0) = config.Camera.height;
	auto & tilt = *(float32 *)(addr + 0xD4) = config.Camera.tilt;
	auto & zoom = *(float32 *)(addr + 0xD8) = config.Camera.zoom;
	auto & zoomLockOn = *(float32 *)(addr + 0xE0) = config.Camera.zoomLockOn;
}

export void Camera_ToggleInvertX(bool enable)
{
	LogFunction(enable);
	Write<byte32>((appBaseAddr + 0x57726), (enable) ? GAMEPAD_RIGHT : GAMEPAD_LEFT ); // Turn right.
	Write<byte32>((appBaseAddr + 0x57752), (enable) ? GAMEPAD_LEFT  : GAMEPAD_RIGHT); // Turn left.
	Write<byte32>((appBaseAddr + 0x51267), (enable) ? GAMEPAD_LEFT  : GAMEPAD_RIGHT); // Fast turn left.
	Write<byte32>((appBaseAddr + 0x51296), (enable) ? GAMEPAD_RIGHT : GAMEPAD_LEFT ); // Fast turn right.
}
