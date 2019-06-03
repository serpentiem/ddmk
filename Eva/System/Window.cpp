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
			Write<WORD>((appBaseAddr + 0x1807B), 0xE990);
		}
		else
		{
			Write<WORD>((appBaseAddr + 0x1807B), 0x850F);
		}
	}
}
