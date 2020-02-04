#include "../Core/DataTypes.h"
#include "../Core/Log.h"
#include "../Core/String.h"
#include "../Core/Utility.h"

const char * Log_directory = "logs";
const char * Log_file      = "dinput8.txt";

const char * libName  = "dinput8.dll";
const char * funcName = "DirectInput8Create";

HMODULE   lib[2]   = {};
void    * procAddr = 0;

extern "C" void Create()
{
	return ((void(__fastcall *)())procAddr)();
}

//#pragma comment(linker, "/export:DirectInput8Create=Create")

bool Init()
{
	LogFunction();

	char directory[128];
	char path[256];
	GetSystemDirectoryA(directory, sizeof(directory));
	snprintf(path, sizeof(path), "%s\\%s", directory, libName);

	lib[0] = LoadLibraryA(path);
	if (!lib[0])
	{
		Log("Critical error: LoadLibrary failed. %s %X", path, GetLastError());
		return false;
	}
	procAddr = GetProcAddress(lib[0], funcName);
	if (!procAddr)
	{
		Log("Critical error: GetProcAddress failed. %s %X", funcName, GetLastError());
		return false;
	}
	return true;
}

void Load()
{
	LogFunction();
	MODULEENTRY32 me32 = {};
	me32.dwSize = sizeof(MODULEENTRY32);
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetCurrentProcessId());
	Module32First(snapshot, &me32);
	const char * str[][2] =
	{
		{
			"dmc1.exe",
			"Eva.dll",
		},
		{
			"dmc2.exe",
			"Lucia.dll",
		},
		{
			"dmc3.exe",
			"Mary.dll",
		},
		{
			"DevilMayCry4SpecialEdition.exe",
			"Kyrie.dll",
		}
	};
	const char * libName = 0;
	for (uint8 i = 0; i < countof(str); i++)
	{
		if (_stricmp(me32.szModule, str[i][0]) == 0)
		{
			libName = str[i][1];
			break;
		}
	}
	if (!libName)
	{
		Log("Warning: No match.");
		return;
	}
	lib[1] = LoadLibraryA(libName);
	if (!lib[1])
	{
		Log("Critical error: LoadLibrary failed. %s %X", libName, GetLastError());
	}
}

DWORD DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		Log_Init();
		Log("Session started.");
		if (!Init())
		{
			return 0;
		}
		Load();
	}
	return 1;
}
