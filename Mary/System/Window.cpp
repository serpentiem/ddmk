#include "Window.h"

namespace System::Window
{
	LONG width  = 0;
	LONG height = 0;

	void UpdateWindowSize(uint32 width, uint32 height)
	{
		Log("%s %u %u", FUNC_NAME, width, height);
		System::Window::width = (LONG)width;
		System::Window::height = (LONG)height;
		ImGui::GetIO().DisplaySize = ImVec2
		(
			(float32)width,
			(float32)height
		);
	}

	void ToggleForceFocus(bool enable)
	{
		Log("%s %u", FUNC_NAME, enable);
		if (enable)
		{
			Write<WORD>((appBaseAddr + 0x487F6), 0xE990);
			WriteAddress((appBaseAddr + 0x41C0A), (appBaseAddr + 0x41C10), 6); // Enable Background Gamepad Input
		}
		else
		{
			Write<WORD>((appBaseAddr + 0x487F6), 0x850F);
			WriteAddress((appBaseAddr + 0x41C0A), (appBaseAddr + 0x42016), 6);
		}
	}
}
