#pragma once
#include "../../Core/Core.h"

#include "../Config.h"
#include "../Steam.h"
#include "../Vars.h"

extern bool System_Actor_enableSpawnExtension;
extern bool System_Actor_enableCharacterDataConverter;
extern bool System_Actor_enableCostumeFixes;

extern BYTE * actorBaseAddr[MAX_ACTOR];

typedef BYTE *(* CreateActor_t)();
typedef BYTE *(* InitActor_t  )(BYTE *);
typedef bool  (* SpawnActor_t )(uint8, BYTE *, uint32, uint32);

extern CreateActor_t CreateActor[MAX_CHAR];
extern InitActor_t   InitActor[MAX_CHAR];
extern SpawnActor_t  SpawnActor;

uint8 GetActorId(BYTE * baseAddr);
uint8 GetActorCount();
void System_Actor_Init();
void System_Actor_ToggleSpawnExtension(bool enable);
void System_Actor_ToggleCharacterDataConverter(bool enable);
void System_Actor_ToggleCostumeFixes(bool enable);
void System_Actor_ToggleDisableIdleTimer(bool enable);
