#include "FMOD.h"

bool FMOD_Init()
{
	LogFunction();
	dword error = 0;
	const char * libName = "fmod64.dll";
	const char * procName = "FMOD_System_CreateSound";
	SetLastError(0);
	HMODULE lib = LoadLibraryA(libName);
	error = GetLastError();
	if (!lib)
	{
		Log("LoadLibrary failed. %s error %X", libName, error);
		return false;
	}
	SetLastError(0);
	FARPROC proc = GetProcAddress(lib, procName);
	error = GetLastError();
	if (!proc)
	{
		Log("GetProcAddress failed. %s error %X", procName, error);
		return false;
	}
	FMOD_System_CreateSound = (FMOD_System_CreateSound_t)proc;
	return true;
}
