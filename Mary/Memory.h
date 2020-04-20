#pragma once
#include "../Core/Core.h"

extern byte8 * Memory_addr;

bool Memory_Init();
void Memory_ToggleExtendVectors(bool enable);
