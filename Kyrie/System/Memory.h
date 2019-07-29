#pragma once
#include "../../Core/Core.h"

extern bool System_Memory_enableReplaceAllocationFunctions;

void System_Memory_Init();
void System_Memory_ToggleReplaceAllocationFunctions(bool enable);
