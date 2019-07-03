#pragma once
#include "../../Core/Core.h"

#include "../Config.h"

typedef void(* ApplyColor_t)(BYTE *, uint32);

extern ApplyColor_t ApplyColor;

void Cosmetics_Color_Init();
void Cosmetics_Color_AdjustConfig();
void Cosmetics_Color_UpdateRGB();
void Cosmetics_Color_ResetRGB();
void Cosmetics_Color_Toggle(bool enable);
