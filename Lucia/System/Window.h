#pragma once
#include "../../Core/Core.h"

#include "../../ImGui/imgui.h"

extern uint32 System_Window_width;
extern uint32 System_Window_height;

void System_Window_UpdateSize(uint32 width, uint32 height);
void System_Window_ToggleForceFocus(bool enable);
