#pragma once
#include "../../Core/Core.h"

#include "../Config.h"
#include "../Steam.h"
#include "../Vars.h"

extern bool System_File_enableLoadAssetsExtension;

typedef BYTE *(* LoadFile_t)(BYTE *, const char *, uint32);

extern LoadFile_t LoadFile;

void System_File_Init();
void System_File_ToggleLoadAssetsExtension(bool enable);
