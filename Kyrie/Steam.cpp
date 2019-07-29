#include "Steam.h"

//#pragma warning(disable: 4102) // Unreferenced label.

SteamApps_t      SteamApps      = 0;
IsDLCInstalled_t IsDLCInstalled = 0;

bool Steam_Init()
{
	LogFunction();
	const char * libName = "steam_api.dll";
	HMODULE lib = LoadLibraryA(libName);
	if (!lib)
	{
		Log("LoadLibrary failed. %s %X", libName, GetLastError());
		return false;
	}
	const char * procName = "SteamApps";
	FARPROC proc = GetProcAddress(lib, procName);
	if (!proc)
	{
		Log("GetProcAddress failed. %s %X", procName, GetLastError());
		return false;
	}
	SteamApps = (SteamApps_t)proc;
	Log("SteamApps %X", SteamApps);
	void * ISteamApps = SteamApps();
	if (!ISteamApps)
	{
		return false;
	}
	Log("ISteamApps %X", ISteamApps);
	BYTE ** funcAddr = *(BYTE ***)ISteamApps;
	if (!funcAddr)
	{
		return false;
	}
	IsDLCInstalled = (IsDLCInstalled_t)funcAddr[7];
	Log("IsDLCInstalled %X", IsDLCInstalled);
	return true;
}
