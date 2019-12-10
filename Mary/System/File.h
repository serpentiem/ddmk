#pragma once
#include "../../Core/Core.h"

#define ZIP_STATIC
#include "../../Zip/zip.h"

#include "../Config.h"

bool ExtractGameFile(const char * fileName);
byte8 * LoadGameFile(const char * fileName, uint32 * size = 0, byte8 * dest = 0);

void AdjustPointers(byte8 * addr);
void System_File_Init();
