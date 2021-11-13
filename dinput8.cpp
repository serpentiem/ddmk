import Core;

#include "Core/Macros.h"

import Windows;
import DI8;

using namespace Windows;
using namespace DI8;

#include <stdio.h>
#include <string.h>

#define debug false



namespaceStart(DI8);

typedef decltype(DirectInput8Create) * DirectInput8Create_t;

namespaceEnd();



namespaceStart(Base::DI8);

::DI8::DirectInput8Create_t DirectInput8Create = 0;

namespaceEnd();



namespaceStart(Hook::DI8);

HRESULT DirectInput8Create
(
	HINSTANCE hinst,
	DWORD dwVersion,
	const IID& riidltf,
	LPVOID* ppvOut,
	LPUNKNOWN punkOuter
)
{
	#pragma comment(linker, "/EXPORT:DirectInput8Create=" DECORATED_FUNCTION_NAME)



	return ::Base::DI8::DirectInput8Create
	(
		hinst,
		dwVersion,
		riidltf,
		ppvOut,
		punkOuter
	);
}

namespaceEnd();



void Init()
{
	LogFunction();



	byte32 error = 0;

	const char * libName = "dinput8.dll";

	char directory[128];
	char location[512];



	GetSystemDirectoryA
	(
		directory,
		sizeof(directory)
	);

	snprintf
	(
		location,
		sizeof(location),
		"%s\\%s",
		directory,
		libName
	);



	SetLastError(0);

	auto lib = LoadLibraryA(location);
	if (!lib)
	{
		error = GetLastError();

		Log("LoadLibraryA failed. %s %X", location, error);

		return;
	}

	// DirectInput8Create
	{
		const char * funcName = "DirectInput8Create";

		SetLastError(0);

		auto funcAddr = GetProcAddress(lib, funcName);
		if (!funcAddr)
		{
			error = GetLastError();

			Log("GetProcAddress failed. %s %X", funcName, error);

			return;
		}

		::Base::DI8::DirectInput8Create = reinterpret_cast<::DI8::DirectInput8Create_t>(funcAddr);

		Log("DirectInput8Create %X", DirectInput8Create);
	}
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
			"dmc4.exe",
			"Kyrie.dll",
		},
		{
			"DevilMayCry4SpecialEdition.exe",
			"Kyrie.dll",
		}
	};



	for_all(index, countof(names))
	{
		auto appName = names[index][0];
		auto libName = names[index][1];

		if
		(
			strncmp
			(
				me32.szModule,
				appName,
				sizeof(appName) // @Research: Pretty sure that should be strlen. sizeof includes the terminating zero, strlen doesn't.
			) == 0
		)
		{
			Log("%s %s", appName, libName);



			SetLastError(0);

			auto lib = LoadLibraryA(libName);
			if (!lib)
			{
				error = GetLastError();

				Log("LoadLibraryA failed. %s %X", libName, error);
			}



			return;
		}
	}



	Log("No Match");
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

		Init();
		Load();
	}

	return 1;
}
