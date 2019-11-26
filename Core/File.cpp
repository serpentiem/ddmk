#include "File.h"

byte * LoadFile(const char * fileName, uint32 * size)
{
	byte * addr = 0;
	dword error = 0;
	SetLastError(0);
	HANDLE file = CreateFileA(fileName, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	error = GetLastError();
	if (file == INVALID_HANDLE_VALUE)
	{
		Log("CreateFile failed. %s error %X", fileName, error);
		return 0;
	}
	BY_HANDLE_FILE_INFORMATION fi = {};
	GetFileInformationByHandle(file, &fi);
	SetLastError(0);
	// @Todo: Create custom allocator.
	addr = (byte *)VirtualAlloc(0, fi.nFileSizeLow, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	error = GetLastError();
	if (!addr)
	{
		Log("VirtualAlloc failed. error %X", error);
		return 0;
	}
	dword bytesRead = 0;
	OVERLAPPED overlap = {};
	ReadFile(file, addr, fi.nFileSizeLow, &bytesRead, &overlap);
	CloseHandle(file);
	if (size)
	{
		*size = fi.nFileSizeLow;
	}
	return addr;
}

bool SaveFile(byte * addr, uint32 size, const char * fileName)
{
	dword error = 0;
	SetLastError(0);
	HANDLE file = CreateFileA(fileName, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	error = GetLastError();
	if (file == INVALID_HANDLE_VALUE)
	{
		Log("CreateFile failed. %s error %X", fileName, error);
		return false;
	}
	dword bytesWritten = 0;
	OVERLAPPED overlap = {};
	WriteFile(file, addr, size, &bytesWritten, &overlap);
	CloseHandle(file);
	return true;
}
