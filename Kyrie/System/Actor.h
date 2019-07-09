#pragma once
#include "../../Core/Core.h"

#include "../Config.h"
#include "../Vars.h"

extern BYTE * actorBaseAddr[MAX_ACTOR];

typedef BYTE *(* CreateActor_t)();
typedef BYTE *(* InitActor_t  )(BYTE *);
typedef bool  (* SpawnActor_t )(uint8, BYTE *, uint32, uint32);

extern CreateActor_t CreateActor[MAX_CHAR];
extern InitActor_t   InitActor[MAX_CHAR];
extern SpawnActor_t  SpawnActor;

void System_Actor_Init();
