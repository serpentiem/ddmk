#pragma once
#include "../../Core/Core.h"

#include "../Vars.h"

extern bool System_Input_enableExtension;
extern MGO  System_Input_gamepad[MAX_ACTOR];

void System_Input_Init();
void System_Input_ToggleExtension(bool enable);
