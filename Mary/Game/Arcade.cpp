

// @Todo: Add WEAPON_NONE and add weapon menu for Vergil.


#include "Arcade.h"

uint8 Game_Arcade_modeIndex = 0;
uint32 Game_Arcade_modeMap[6] =
{
	MODE_EASY,
	MODE_NORMAL,
	MODE_HARD,
	MODE_VERY_HARD,
	MODE_DANTE_MUST_DIE,
	MODE_HARD,
};

void Game_Arcade_UpdateModeIndex()
{
	auto & modeIndex = Game_Arcade_modeIndex;
	auto & modeMap   = Game_Arcade_modeMap;
	for (uint8 index = 0; index < countof(modeMap); index++)
	{
		if (modeMap[index] == Config.Game.Arcade.mode)
		{
			modeIndex = index;
			break;
		}
	}
}

void Game_Arcade_Toggle(bool enable)
{
	LogFunction(enable);
	Write<byte8>((appBaseAddr + 0x2433FB), (enable) ? 0xEB : 0x74); // Force new game.
	Write<byte8>((appBaseAddr + 0x243299), (enable) ? 0xEB : 0x74); // Skip mission select menu.
	Write<byte8>((appBaseAddr + 0x2411F5), (enable) ? 0xEB : 0x74); // Force start mission.
	// Force costume.
	WriteAddress((appBaseAddr + 0x217991), (enable) ? (appBaseAddr + 0x217993) : (appBaseAddr + 0x2179A2), 2);
	WriteAddress((appBaseAddr + 0x21799A), (enable) ? (appBaseAddr + 0x21799C) : (appBaseAddr + 0x2179A2), 2);
	// @Todo: Lazy solution, update proper vars!
	Write<byte8>((appBaseAddr + 0x1AA791), (enable) ? 0xEB : 0x75); // Skip orb notifications.
}
