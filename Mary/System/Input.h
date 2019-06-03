#pragma once
#include "../../Core/Core.h"

#include "../Vars.h"




extern bool System_Input_extend;

extern WORD buttonMask[17];

WORD GetButtonState(uint8 actorId);
WORD GetBinding(uint8 commandId);
void System_Input_Init();
