#pragma once
#include "../../Core/Core.h"
#include "../Vars.h"

extern uint8 Game_Arcade_modeMask[4];
extern uint8 Game_Arcade_meleeWeaponMask[4];
extern uint8 Game_Arcade_rangedWeaponMask[4];

void Game_Arcade_Toggle(bool enable);
