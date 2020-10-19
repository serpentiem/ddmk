#pragma once
#include "../../Core/Core.h"

#include "../Config.h"
#include "../Steam.h"

#include "../Game/Arcade.h"

typedef BYTE *(* GetMapTable_t)(const char *, BYTE *);

extern GetMapTable_t GetMapTable;

void System_Event_Init();
void System_Event_ToggleSkipIntro(bool enable);
