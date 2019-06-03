#pragma once
#include "../Core/Core.h"
#include "../Windows/Windows.h"
#include "../ImGui/imgui.h"

namespace ImGui::User
{
	void Init();
	void UpdateMouseCursor(HWND window);
}
