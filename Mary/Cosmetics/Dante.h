#pragma once
#include "../../Core/Core.h"

#include "../Config.h"
#include "../Vars.h"

#include "../System/Actor.h"
#include "../System/State.h"

typedef void(* ApplyDefaultModelAttributes_t)(BYTE *);
typedef void(* ApplyBeowulfModelAttributes_t)(BYTE *);

extern ApplyDefaultModelAttributes_t ApplyDefaultModelAttributes;
extern ApplyBeowulfModelAttributes_t ApplyBeowulfModelAttributes;

void Cosmetics_Dante_Init();
void Cosmetics_Dante_Beowulf_LiveUpdate();
void Cosmetics_Dante_ToggleHideBeowulf(bool enable);
