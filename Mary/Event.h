#pragma once
#include "../Core/Core.h"

#include "Actor.h"
#include "Config.h"
#include "File.h"
#include "State.h"
#include "Vars.h"

#include "Game/Arcade.h"

//#include "System/Actor.h"
//#include "System/Media.h"
//#include "System/State.h"
//#include "System/Weapon.h"

//#include "Game/Arcade.h"

//#include "Cosmetics/Color.h"

extern bool spawnActors;

void Event_Init();
void Event_ToggleSkipIntro(bool enable);
void Event_ToggleSkipCutscenes(bool enable);
