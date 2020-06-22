module;
#include "../Core/Core.h"

#include "Vars.h"
export module ModuleName(Arcade);

import ModuleName(Config);

#ifdef __INTELLISENSE__
#include "Config.ixx"
#endif

export uint8 Arcade_modeIndex = 0;
export uint32 Arcade_modeMap[6] =
{
	MODE_EASY,
	MODE_NORMAL,
	MODE_HARD,
	MODE_VERY_HARD,
	MODE_DANTE_MUST_DIE,
	MODE_HARD,
};

export void Arcade_UpdateModeIndex()
{
	auto & modeIndex = Arcade_modeIndex;
	auto & modeMap   = Arcade_modeMap;
	for (uint8 index = 0; index < countof(modeMap); index++)
	{
		if (modeMap[index] == Config.Game.Arcade.mode)
		{
			modeIndex = index;
			break;
		}
	}
}

export void Arcade_Toggle(bool enable)
{
	LogFunction(enable);
	Write<byte8>((appBaseAddr + 0x2433FB), (enable) ? 0xEB : 0x74); // Force new game.
	Write<byte8>((appBaseAddr + 0x243299), (enable) ? 0xEB : 0x74); // Skip mission select menu.
	//Write<byte8>((appBaseAddr + 0x2411F5), (enable) ? 0xEB : 0x74); // Force start mission.
	// Force costume.
	WriteAddress((appBaseAddr + 0x217991), (enable) ? (appBaseAddr + 0x217993) : (appBaseAddr + 0x2179A2), 2);
	WriteAddress((appBaseAddr + 0x21799A), (enable) ? (appBaseAddr + 0x21799C) : (appBaseAddr + 0x2179A2), 2);
	// @Todo: Lazy solution, update proper vars!
	Write<byte8>((appBaseAddr + 0x1AA791), (enable) ? 0xEB : 0x75); // Skip orb notifications.
}
