#pragma once
#include "../Core/Core.h"
#include "../Core/GUI.h"

#include "../ImGui/imgui.h"
#include "../ImGui/imgui_internal.h"

#include "Config.h"
#include "Locale.h"
#include "Pause.h"
//#include "Speed.h"
#include "Vars.h"

#include "System/Graphics.h"
#include "System/State.h"
#include "System/Window.h"

#include "Game/Arcade.h"
#include "Game/BossRush.h"
#include "Game/Dante.h"
#include "Game/LockOn.h"
#include "Game/MissionSelect.h"
#include "Game/ResetMotionState.h"
#include "Game/Training.h"
#include "Game/WeaponSwitcher.h"

void GUI_Render();
void GUI_Init();
