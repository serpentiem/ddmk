#pragma once
#include "../../Core/Core.h"

extern bool System_Memory_enableExtendVectors;

extern byte8 * System_Memory_addr;

constexpr uint32 System_Memory_size     = (1 * 1024 * 1024 * 1024);
constexpr uint32 System_Memory_mainSize = (     300 * 1024 * 1024);

void System_Memory_Init();
void System_Memory_ToggleExtendVectors(bool enable);
