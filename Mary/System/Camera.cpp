#include "Camera.h"

void System_Camera_ToggleInvertX(bool enable)
{
	LogFunction(enable);
	Write<byte32>((appBaseAddr + 0x57726), (enable) ? GAMEPAD_RIGHT : GAMEPAD_LEFT ); // Turn right.
	Write<byte32>((appBaseAddr + 0x57752), (enable) ? GAMEPAD_LEFT  : GAMEPAD_RIGHT); // Turn left.
	Write<byte32>((appBaseAddr + 0x51267), (enable) ? GAMEPAD_LEFT  : GAMEPAD_RIGHT); // Fast turn left.
	Write<byte32>((appBaseAddr + 0x51296), (enable) ? GAMEPAD_RIGHT : GAMEPAD_LEFT ); // Fast turn right.
}
