#pragma once
#include "../../Core/Core.h"

#include "../Config.h"
#include "../Vars.h"

#include "Actor.h"
#include "Cache.h"

#include "../Game/Dante.h"

extern bool System_Weapon_enable;
extern byte * weaponMetadata[MAX_ACTOR][MAX_WEAPON];
//extern bool System_Weapon_Ranged_resetLevel;

void System_Weapon_Ranged_UpdateLevels(byte * baseAddr);

void System_Weapon_Init();
void System_Weapon_Toggle();
