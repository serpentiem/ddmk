#pragma once
#include "../../Core/Core.h"

typedef void(* Cosmetics_Dante_ApplyDefaultModelAttributes_t)(byte8 * baseAddr);
typedef void(* Cosmetics_Dante_ApplyBeowulfModelAttributes_t)(byte8 * baseAddr);

extern Cosmetics_Dante_ApplyDefaultModelAttributes_t Cosmetics_Dante_ApplyDefaultModelAttributes;
extern Cosmetics_Dante_ApplyBeowulfModelAttributes_t Cosmetics_Dante_ApplyBeowulfModelAttributes;

void Cosmetics_Dante_Init();
void Cosmetics_Dante_ToggleHideBeowulf(bool enable);
