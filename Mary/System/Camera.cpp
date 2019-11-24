#include "Camera.h"

void System_Camera_ToggleInvertX(bool enable)
{
	Log("%s %u", FUNC_NAME, enable);
	if (enable)
	{
		// Default
		Write<dword>((appBaseAddr + 0x57726), GAMEPAD_RIGHT); // turn camera right
		Write<dword>((appBaseAddr + 0x57752), GAMEPAD_LEFT ); // turn camera left
		// Fast Camera
		Write<dword>((appBaseAddr + 0x51267), GAMEPAD_LEFT ); // turn camera left
		Write<dword>((appBaseAddr + 0x51296), GAMEPAD_RIGHT); // turn camera right
	}
	else
	{
		Write<dword>((appBaseAddr + 0x57726), GAMEPAD_LEFT );
		Write<dword>((appBaseAddr + 0x57752), GAMEPAD_RIGHT);
		Write<dword>((appBaseAddr + 0x51267), GAMEPAD_RIGHT);
		Write<dword>((appBaseAddr + 0x51296), GAMEPAD_LEFT );
	}
}
