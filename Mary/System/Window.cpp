#include "Window.h"





uint32 System_Window_width  = 0;
uint32 System_Window_height = 0;

void System_Window_UpdateSize(uint32 width, uint32 height)
{
	Log("%s %u %u", FUNC_NAME, width, height);
	System_Window_width  = width;
	System_Window_height = height;
	ImGui::GetIO().DisplaySize = ImVec2((float32)width, (float32)height);
}

void System_Window_ToggleForceFocus(bool enable)
{
	Log("%s %u", FUNC_NAME, enable);
	if (enable)
	{
		Write<word>((appBaseAddr + 0x487F6), 0xE990);
		WriteAddress((appBaseAddr + 0x41C0A), (appBaseAddr + 0x41C10), 6); // Enable Background Gamepad Input
	}
	else
	{
		Write<word>((appBaseAddr + 0x487F6), 0x850F);
		WriteAddress((appBaseAddr + 0x41C0A), (appBaseAddr + 0x42016), 6);
	}
}
