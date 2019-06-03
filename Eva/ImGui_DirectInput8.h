#pragma once
#include "../Core/Core.h"
#include "../Windows/Windows.h"
#include "../ImGui/imgui.h"
#ifdef DIRECTINPUT_VERSION
#undef DIRECTINPUT_VERSION
#endif
#define DIRECTINPUT_VERSION 0x800
#include <dinput.h>

namespace ImGui::DirectInput8
{
	void Init();
	void UpdateKeyboard(BYTE * buffer);
	void UpdateMouse(HWND window, DIMOUSESTATE2 * state);
}
