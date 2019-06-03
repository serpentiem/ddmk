#pragma once
#include "../../Core/Core.h"
#include "../../ImGui/imgui.h"
#include "../../Windows/Windows.h"

namespace System::Window
{
	extern LONG width;
	extern LONG height;

	void UpdateWindowSize(uint32 width, uint32 height);
	void ToggleForceFocus(bool enable);
}
