#pragma once
#include "../Core/Core.h"

#include "Config.h"
#include "Vars.h"

#include "System/Actor.h"
#include "System/Media.h"
#include "System/State.h"
#include "System/Weapon.h"

void Event_Init();
void Event_ToggleSkipIntro(bool enable);
void Event_ToggleSkipCutscenes(bool enable);
