#pragma once
#include "../../Core/Core.h"

#include "../Config.h"
#include "../Vars.h"

#include "Cache.h"
#include "State.h"

extern bool System_Actor_enable;
extern byte * actorBaseAddr[MAX_ACTOR];
extern bool updateModelAttributes[MAX_ACTOR];

typedef void(* UpdateDevilForm_t)(byte *);
typedef void(* UpdateFlux_t)(byte *, uint8);

extern UpdateDevilForm_t UpdateDevilForm;
extern UpdateFlux_t      UpdateFlux;

uint8 GetActorId(byte * baseAddr);
uint8 GetActorCount();
void ResetDevilModel();
void UpdateDevilModel(uint8 model);
void System_Actor_Init();
void System_Actor_Toggle();
//void System_Actor_QueueToggle();
