#pragma once
#include "../../Core/Core.h"

#include "../ActorData.h"
#include "../Config.h"
#include "../Internal.h"
#include "../Vars.h"

#include "File.h"

#include "../Cosmetics/Color.h"
#include "../Cosmetics/Model.h"

extern vector<byte8 *, 128> System_Actor_actorBaseAddr;

byte8 * CreateActor
(
	uint8 character,
	uint8 actor
);

void System_Actor_Init();









