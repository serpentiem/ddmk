#pragma once
#include "../../Core/Core.h"

#include "../Config.h"
#include "../Vars.h"

#include "File.h"

#include "../Cosmetics/Color.h"

extern bool System_Actor_enableArrayExtension;
extern bool System_Actor_enableCreateActor;
extern bool System_Actor_enableUpdateActor;
extern bool System_Actor_enableDoppelgangerFixes;
extern bool System_Actor_enableModelFixes;

extern byte8 * System_Actor_actorBaseAddr[MAX_ACTOR];

typedef void(* System_Actor_UpdateDevilForm_t)(byte8 *       );
typedef void(* System_Actor_UpdateFlux_t     )(byte8 *, uint8);
typedef void(* System_Actor_Relax_t          )(byte8 *       );

extern System_Actor_UpdateDevilForm_t System_Actor_UpdateDevilForm;
extern System_Actor_UpdateFlux_t      System_Actor_UpdateFlux;
extern System_Actor_Relax_t           System_Actor_Relax;

uint8 System_Actor_GetActorId(byte8 * baseAddr);
uint8 System_Actor_GetActorCount();
void System_Actor_ResetDevilModel();
void System_Actor_UpdateDevilModel(uint8 model);
void System_Actor_Init();
void System_Actor_ToggleArrayExtension(bool enable);
void System_Actor_ToggleCreateActorOne(bool enable);
void System_Actor_ToggleUpdateActor(bool enable);
void System_Actor_ToggleDoppelgangerFixes(bool enable);
void System_Actor_ToggleModelFixes(bool enable);
void System_Actor_ToggleDisableIdleTimer(bool enable);
