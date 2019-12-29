#pragma once
#include "../../Core/Core.h"

#include "State.h"

extern bool System_HUD_updateStyleIcon;

typedef void(* System_HUD_UpdateStyleIcon_t)();

extern System_HUD_UpdateStyleIcon_t System_HUD_UpdateStyleIcon;

void System_HUD_Update();
void System_HUD_Init();
