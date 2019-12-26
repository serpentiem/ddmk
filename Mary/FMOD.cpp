#include "FMOD.h"





FMOD_System_CreateSound_t FMOD_System_CreateSound = 0;

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
	// Set cache size.
	Write<dword>((appBaseAddr + 0x32636), FMOD_CACHE_SIZE);
	Write<dword>((appBaseAddr + 0x32659), FMOD_CACHE_SIZE);
	return true;
}
