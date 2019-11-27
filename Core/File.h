
// @Todo: Add AppendFile.

#pragma once
#include "DataTypes.h"
#include "Log.h"
#include "Windows.h"

byte * LoadFile(const char * fileName, uint32 * size = 0, byte * dest = 0);

// @Philosophy: Put destination first.

bool SaveFile
(
	byte * addr,
	uint32 size,
	const char * fileName
);
