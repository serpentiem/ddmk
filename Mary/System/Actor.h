#pragma once
#include "../../Core/Core.h"
#include "../Config.h"
#include "Cache.h"
#include "State.h"
#include "../Vars.h"

extern bool System_Actor_enable;
extern BYTE * actorBaseAddr[MAX_ACTOR];
extern bool updateModelAttributes[MAX_ACTOR];

typedef void(* UpdateDevilForm_t)(BYTE *);
typedef void(* UpdateFlux_t)(BYTE *, uint8);

extern UpdateDevilForm_t UpdateDevilForm;
extern UpdateFlux_t      UpdateFlux;

uint8 GetActorId(BYTE * baseAddr);
uint8 GetActorCount();
void ResetDevilModel();
void UpdateDevilModel(uint8 model);
void System_Actor_Init();
void System_Actor_Toggle();
//void System_Actor_QueueToggle();
