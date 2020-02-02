#pragma once
#include "../../Core/Core.h"

#include "../Config.h"
#include "../Vars.h"

#include "Actor.h"
#include "File.h"

#include "../Cosmetics/Dante.h"

extern bool System_Weapon_enableUpdateWeapon;
extern bool System_Weapon_enableDoppelgangerFixes;
extern bool System_Weapon_enableModelFixes;

extern byte8 * System_Weapon_weaponMetadata[MAX_ACTOR][MAX_WEAPON];

typedef void(* System_Weapon_Dante_UpdateExpertise_t)(byte8 * baseAddr);

extern System_Weapon_Dante_UpdateExpertise_t System_Weapon_Dante_UpdateExpertise;

void System_Weapon_Dante_Ranged_UpdateLevels(byte8 * baseAddr);
void System_Weapon_Init();
void System_Weapon_ToggleUpdateWeapon(bool enable);
void System_Weapon_ToggleDoppelgangerFixes(bool enable);
void System_Weapon_ToggleModelFixes(bool enable);
