#pragma once
#include "DataTypes.h"
#include "Log.h"
#include "Memory.h"
#include "Windows.h"

// @Research: Consider void *.

byte8 * LoadFile
(
	const char * filename,
	uint32     * size = 0,
	byte8      * dest = 0
);

bool SaveFile
(
	const char * filename,
	byte8      * addr,
	uint32       size
);
