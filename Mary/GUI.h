#pragma once
#include "../Core/Core.h"
#include "../Core/GUI.h"

#include "../ImGui/imgui.h"
#include "../ImGui/imgui_internal.h"

#include "Config.h"
#include "Locale.h"
#include "Pause.h"



#include "Restart.h"

#include "Speed.h"


#include "System/Actor.h"
#include "System/Cache.h"
#include "System/Camera.h"
#include "System/Graphics.h"
#include "System/Input.h"
#include "System/Media.h"
#include "System/State.h"
#include "System/Weapon.h"
#include "System/Window.h"

#include "Game/Arcade.h"
#include "Game/Dante.h"

#include "Game/Doppelganger.h"

#include "Game/Mobility.h"
#include "Game/Other.h"
#include "Game/ResetMotionState.h"
//#include "Game/Speed.h"
//#include "Game/Style.h"
#include "Game/StyleSwitcher.h"
#include "Game/Training.h"
#include "Game/Vergil.h"
#include "Game/WeaponSwitcher.h"

#include "Cosmetics/Color.h"
#include "Cosmetics/Dante.h"
#include "Cosmetics/Other.h"
#include "Cosmetics/Vergil.h"
//#include "Cosmetics/Weapon.h"

void GUI_Render();
void GUI_Init();
