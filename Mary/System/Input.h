#pragma once
#include "../../Core/Core.h"

#include "../Vars.h"




extern bool System_Input_extend;

extern word buttonMask[17];



// @Todo: Inline!

word GetButtonState(uint8 actorId);
word GetBinding(uint8 commandId);
void System_Input_Init();
