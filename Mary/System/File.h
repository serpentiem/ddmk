#pragma once
#include "../../Core/Core.h"

#define ZIP_STATIC
#include "../../Zip/zip.h"

#include "../Config.h"

bool ExtractFile(const char * str);
byte * LoadFile(const char * str);
void AdjustPointers(byte * addr);
void System_File_Init();
