// @Todo: Review.

module;
#include "../Core/Core.h"

#include "../ImGui/imgui.h"
export module Window;

export uint32 Window_width  = 0;
export uint32 Window_height = 0;

// @Todo: Update.
export void Window_UpdateSize(uint32 width, uint32 height)
{
	Log("%s %u %u", FUNC_NAME, width, height);
	Window_width  = width;
	Window_height = height;
	ImGui::GetIO().DisplaySize = ImVec2((float32)width, (float32)height);
}

export void Window_ToggleForceFocus(bool enable)
{
	LogFunction(enable);
	Write<byte16>((appBaseAddr + 0x487F6), (enable) ? 0xE990 : 0x850F);
	// Enable Background Gamepad Input
	WriteAddress((appBaseAddr + 0x41C0A), (enable) ? (appBaseAddr + 0x41C10) : (appBaseAddr + 0x42016), 6);
}
