#pragma once
#include "../../Core/Core.h"

#include "../Config.h"

typedef void(* Cosmetics_Color_ApplyColor_t)(byte8 * baseAddr, uint32 preset, byte32 customColor);

extern Cosmetics_Color_ApplyColor_t Cosmetics_Color_ApplyColor;

void Cosmetics_Color_Init();
void Cosmetics_Color_AdjustConfig();
void Cosmetics_Color_UpdateColors(CONFIG & config);
