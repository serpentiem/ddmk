#pragma once
#include "../../Core/Core.h"

#include "../System/File.h"

void Game_Dante_Init();
void Game_Dante_Rebellion_ToggleInfiniteSwordPierce(bool enable);
void Game_Dante_EbonyIvory_ToggleFoursomeTime(bool enable);
void Game_Dante_EbonyIvory_ToggleInfiniteRainStorm(bool enable);
void Game_Dante_Artemis_ToggleSwap(bool enable);
void Game_Dante_Artemis_ToggleInstant(bool enable);
void Game_Dante_AirHike_ToggleCoreAbility(bool enable);
void Game_Dante_CrazyCombo_SetLevelMultiplier(uint8 multiplier);
void Game_Dante_WeaponSwitchTimeout_Melee_Toggle(float32 var);
void Game_Dante_WeaponSwitchTimeout_Ranged_Toggle(float32 var);
