export module Steam;

import Core;

#include "../Core/Macros.h"

import Windows;

using namespace Windows;

// import Config;
// import Global;
// import Vars;

// #define debug false





struct ISteamApps
{
	virtual void func0() = 0;
	virtual void func1() = 0;
	virtual void func2() = 0;
	virtual void func3() = 0;
	virtual void func4() = 0;
	virtual void func5() = 0;
	virtual void func6() = 0;
	virtual bool IsDLCInstalled(uint32 id) = 0;
};



typedef ISteamApps *(* SteamApps_t)();

SteamApps_t SteamApps = 0;



export bool IsDLCInstalled(uint32 id)
{
	auto steamApps = SteamApps();
	if (!steamApps)
	{
		return false;
	}

	return steamApps->IsDLCInstalled(id);
}



namespaceStart(Steam);

export void Toggle(bool enable)
{
	LogFunction(enable);

	static bool run = false;



	if (!run)
	{
		byte32 error = 0;

		const char * libName = "steam_api.dll";

		SetLastError(0);

		auto lib = LoadLibraryA(libName);
		if (!lib)
		{
			error = GetLastError();

			Log("LoadLibraryA failed. %s %X", libName, error);

			return;
		}

		// SteamApps
		{
			const char * funcName = "SteamApps";

			SetLastError(0);

			auto funcAddr = GetProcAddress(lib, funcName);
			if (!funcAddr)
			{
				error = GetLastError();

				Log("GetProcAddress failed. %s %X", funcName, error);

				return;
			}

			SteamApps = reinterpret_cast<SteamApps_t>(funcAddr);

			Log("SteamApps %X", SteamApps);
		}
	}



	run = true;
}

namespaceEnd();
