#pragma once
#include "../Core/Core.h"

typedef void *(* SteamApps_t)();
typedef bool(* IsDLCInstalled_t)(uint32);

extern SteamApps_t      SteamApps;
extern IsDLCInstalled_t IsDLCInstalled;

bool Steam_Init();
