#pragma once
#include "../Core/Core.h"

#include "ActorData.h"
#include "File.h"
#include "Internal.h"
#include "Input.h"
#include "Vars.h"

extern vector<byte8 *, 128> Actor_actorBaseAddr;

void ToggleUpdateWeapon(bool enable);
ACTOR_DATA_DANTE * CreateActorDante();
ACTOR_DATA_VERGIL * CreateActorVergil();

void Actor_Init();
