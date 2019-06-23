#pragma once
#include "Core.h"
#include "../Windows/Windows.h"
#include "../ImGui/imgui.h"
#ifdef DIRECTINPUT_VERSION
#undef DIRECTINPUT_VERSION
#endif
#define DIRECTINPUT_VERSION 0x800
#include <dinput.h>

void ImGui_DirectInput8_Init();
void ImGui_DirectInput8_UpdateKeyboard(BYTE * buffer);
void ImGui_DirectInput8_UpdateMouse(HWND window, DIMOUSESTATE2 * state);
