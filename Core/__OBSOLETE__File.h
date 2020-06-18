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





inline bool CheckFile(const char * filename)
{
	HANDLE file = 0;
	byte32 error = 0;

	SetLastError(0);
	file = CreateFileA(filename, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	error = GetLastError();
	if (file == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	return true;
}
















