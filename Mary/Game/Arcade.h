#pragma once
#include "../../Core/Core.h"

#include "../Config.h"
#include "../Vars.h"

extern uint8 Game_Arcade_modeIndex;
extern uint32 Game_Arcade_modeMap[6];

void Game_Arcade_UpdateModeIndex();
void Game_Arcade_Toggle(bool enable);
