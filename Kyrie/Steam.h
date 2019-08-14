#pragma once
#include "../Core/Core.h"

#include "Vars.h"

typedef bool (* IsDLCInstalled_t)(uint32);

extern IsDLCInstalled_t IsDLCInstalled;

void Steam_Init();
