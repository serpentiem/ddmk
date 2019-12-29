#pragma once
#include "../../Core/Core.h"

#include "../Config.h"
#include "../Vars.h"

#include "../System/Actor.h"
#include "../System/HUD.h"
#include "../System/Input.h"
#include "../System/State.h"

#include "Dante.h"

extern uint64 Game_StyleSwitcher_counter;

void Game_StyleSwitcher_Controller();
void Game_StyleSwitcher_Init();
void Game_StyleSwitcher_Toggle(bool enable);
