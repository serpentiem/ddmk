#include "Steam.h"

typedef void *(* SteamApps_t)();

SteamApps_t      SteamApps      = 0;
IsDLCInstalled_t IsDLCInstalled = 0;

static DWORD Steam_Thread(LPVOID)
{
	LogFunction();
	Start:
	{
		const char * libName = "steam_api.dll";
		HMODULE lib = LoadLibraryA(libName);
		if (!lib)
		{
			Log("LoadLibrary failed. %s %X", libName, GetLastError());
			goto End;
		}
		const char * procName = "SteamApps";
		FARPROC proc = GetProcAddress(lib, procName);
		if (!proc)
		{
			Log("GetProcAddress failed. %s %X", procName, GetLastError());
			goto End;
		}
		SteamApps = (SteamApps_t)proc;
		void * ISteamApps = 0;
		do
		{
			ISteamApps = SteamApps();
			if (ISteamApps)
			{
				break;
			}
			Sleep(10);
		}
		while (true);
		Log("ISteamApps %X", ISteamApps);
		BYTE ** funcAddr = *(BYTE ***)ISteamApps;
		if (!funcAddr)
		{
			goto End;
		}
		{
			BYTE sect1[] =
			{
				0xB9, 0x00, 0x00, 0x00, 0x00, //mov ecx
				0xFF, 0x74, 0x24, 0x24,       //push [esp+24]
				0xB8, 0x00, 0x00, 0x00, 0x00, //mov eax
				0xFF, 0xD0,                   //call eax
			};
			FUNC func = CreateFunction(0, 1, true, false, 0, sizeof(sect1));
			memcpy(func.sect1, sect1, sizeof(sect1));
			*(void **)(func.sect1 + 1) = ISteamApps;
			*(BYTE **)(func.sect1 + 0xA) = funcAddr[7];
			IsDLCInstalled = (IsDLCInstalled_t)func.addr;
		}
		Log("IsDLCInstalled %X", IsDLCInstalled);
		Log("DLC_TRISH_LADY_COSTUMES %u", IsDLCInstalled(DLC_TRISH_LADY_COSTUMES));
	}
	End:
	return 1;
}

void Steam_Init()
{
	LogFunction();
	CreateThread(0, 4096, Steam_Thread, 0, 0, 0);
}
