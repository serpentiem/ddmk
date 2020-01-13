#pragma once
#include "../../Core/Core.h"

#define ZIP_STATIC
#include "../../Zip/zip.h"

#include "../Config.h"

bool System_File_ExtractFile(const char * fileName);
byte8 * System_File_LoadFile(const char * fileName, uint32 * size = 0, byte8 * dest = 0);
void System_File_AdjustPointers(byte8 * addr);
void System_File_Init();
