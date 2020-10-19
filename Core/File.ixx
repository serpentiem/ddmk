module;
#include "Includes.h"
export module Core_File;

import Core_Log;
import Core_Memory;

export byte8 * LoadFile
(
	const char * filename,
	uint32     * size = 0,
	byte8      * dest = 0
)
{
	byte8 * addr = dest;
	HANDLE file = 0;
	BY_HANDLE_FILE_INFORMATION fi = {};
	uint32 bytesRead = 0;
	byte32 error = 0;

	SetLastError(0);
	file = CreateFileA(filename, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	error = GetLastError();
	if (file == INVALID_HANDLE_VALUE)
	{
		Log("CreateFile failed. %X %s", error, filename);
		return 0;
	}

	GetFileInformationByHandle(file, &fi);

	if (!addr)
	{
		addr = Alloc(fi.nFileSizeLow);
		if (!addr)
		{
			Log("Alloc failed.");
			return 0;
		}
	}
	ReadFile(file, addr, fi.nFileSizeLow, &bytesRead, 0);
	CloseHandle(file);

	if (size)
	{
		*size = fi.nFileSizeLow;
	}

	return addr;
}

export bool SaveFile
(
	const char * filename,
	byte8      * addr,
	uint32       size
)
{
	HANDLE file = 0;
	uint32 bytesWritten = 0;
	byte32 error = 0;

	SetLastError(0);
	file = CreateFileA(filename, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	error = GetLastError();
	if (file == INVALID_HANDLE_VALUE)
	{
		Log("CreateFile failed. %X %s", error, filename);
		return false;
	}

	WriteFile(file, addr, size, &bytesWritten, 0);
	CloseHandle(file);

	return true;
}

export bool CheckFile(const char * filename)
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
