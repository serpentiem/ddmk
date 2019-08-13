#pragma once
#include "../../Core/Core.h"

#include "../Vars.h"

#include "Actor.h"

extern bool System_Input_enableExtension;

void System_Input_UpdateKeyboardAddr();
void System_Input_Init();
void System_Input_ToggleExtension(bool enable);
