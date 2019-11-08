#pragma once
#include "Core.h"

#define DIRECTINPUT_VERSION 0x800
#include <dinput.h>
#include "../ImGui/imgui.h"

void ImGui_DirectInput8_Init();
void ImGui_DirectInput8_UpdateKeyboard(byte * state);
void ImGui_DirectInput8_UpdateMouse(HWND window, DIMOUSESTATE2 * state);
