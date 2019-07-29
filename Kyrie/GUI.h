#pragma once
#include "../Core/Core.h"
#include "../Core/GUI.h"

#include "../ImGui/imgui.h"
#include "../ImGui/imgui_internal.h"

#include "Config.h"
#include "Locale.h"
#include "Pause.h"
#include "Restart.h"

#include "System/Actor.h"
#include "System/File.h"
#include "System/Memory.h"
#include "System/State.h"
#include "System/Window.h"

void GUI_Render();
void GUI_Init();
