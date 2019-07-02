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
	LogFunctionBool(enable);
	if (enable)
	{
		Write<WORD>((appBaseAddr + 0x1807B), 0xE990);
	}
	else
	{
		Write<WORD>((appBaseAddr + 0x1807B), 0x850F);
	}
}
