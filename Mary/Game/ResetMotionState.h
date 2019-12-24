#pragma once
#include "../../Core/Core.h"

#include "../Config.h"
#include "../Vars.h"

#include "../System/Actor.h"
#include "../System/Input.h"
#include "../System/State.h"

extern uint8 Game_ResetMotionState_buttonIndex;
extern byte16 Game_ResetMotionState_buttonMap[16];

void Game_ResetMotionState_Init();
