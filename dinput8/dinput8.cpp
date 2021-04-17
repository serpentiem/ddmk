// @Todo: Update.

#include "../Core/Core.h"

typedef void(__fastcall * DirectInput8_Create_t)();

DirectInput8_Create_t DirectInput8_Create = 0;

extern "C" void Create()
{
	return DirectInput8_Create();
}

bool Init()
{
	LogFunction();

	byte32 error = 0;
	const char * libName = "dinput8.dll";
	char directory[128];
	char path[256];

	GetSystemDirectoryA
	(
		directory,
		sizeof(directory)
	);

	snprintf
	(
		path,
		sizeof(path),
		"%s\\%s",
		directory,
		libName
	);

	SetLastError(0);

	auto lib = LoadLibraryA(path);

	error = GetLastError();

	if (!lib)
	{
		Log("LoadLibraryA failed. %X", error);

		return false;
	}

	// DirectInput8_Create
	{
		const char * funcName = "DirectInput8Create";

		SetLastError(0);

		auto funcAddr = GetProcAddress(lib, funcName);

		error = GetLastError();

		if (!funcAddr)
		{
			Log("GetProcAddress failed. %s %X", funcName, error);

			return false;
		}

		DirectInput8_Create = reinterpret_cast<DirectInput8_Create_t>(funcAddr);
	}

	return true;
}

void Load()
{
	LogFunction();

	byte32 error = 0;

	MODULEENTRY32 me32 = {};
	me32.dwSize = sizeof(MODULEENTRY32);

	auto snapshot = CreateToolhelp32Snapshot
	(
		TH32CS_SNAPMODULE,
		0
	);

	Module32First(snapshot, &me32);

	const char * names[][2] =
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

	for_all(uint8, index, countof(names))
	{
		auto moduleName = names[index][0];
		auto libName    = names[index][1];

		if
		(
			strncmp
			(
				me32.szModule,
				moduleName,
				sizeof(moduleName)
			) == 0
		)
		{
			Log(moduleName);
			Log(libName);

			SetLastError(0);

			auto lib = LoadLibraryA(libName);

			error = GetLastError();

			if (!lib)
			{
				Log("LoadLibraryA failed. %X", error);
			}

			break;
		}
	}
}

byte32 DllMain
(
	HINSTANCE instance,
	byte32 reason,
	void * reserved
)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		Core_Log_Init("logs", "dinput8.txt");

		Log("Session started.");

		if (!Init())
		{
			return 0;
		}

		Load();
	}

	return 1;
}

#ifdef __GARBAGE__
#endif
