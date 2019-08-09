#pragma once
#include "../../Core/Core.h"

#include "../Config.h"
#include "../Steam.h"

typedef BYTE *(* GetMapTable_t)(const char *, BYTE *);

extern GetMapTable_t GetMapeTable;

void System_Event_Init();
void System_Event_ToggleSkipIntro(bool enable);
