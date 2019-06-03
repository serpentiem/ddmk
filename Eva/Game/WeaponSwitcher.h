#pragma once
#include "../../Core/Core.h"
#include "../Config.h"
#include "../Vars.h"
#include "../System/Input.h"
#include "../System/State.h"

extern uint8 Game_WeaponSwitcher_Melee_weaponMask[4];
extern uint8 Game_WeaponSwitcher_Ranged_weaponMask[4];

void Game_WeaponSwitcher_Init();
void Game_WeaponSwitcher_Toggle(bool enable);
