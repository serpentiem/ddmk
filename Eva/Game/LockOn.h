#pragma once
#include "../../Core/Core.h"
#include "../Config.h"
#include "../Vars.h"
#include "../System/Input.h"
#include "../System/State.h"

extern WORD Game_LockOn_buttonMap[16];

void Game_LockOn_Init();
void Game_LockOn_Toggle(bool enable);
