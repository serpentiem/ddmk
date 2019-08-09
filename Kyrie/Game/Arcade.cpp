#include "Arcade.h"


// @Todo: Create Auto Confirm for Bloody Palace Start Menu.
// Get room and position events.




// Get start position for every mission.




uint32 Game_Arcade_missionMap[21] =
{
	1,
	2,
	3,
	4,
	5,
	6,
	7,
	8,
	9,
	10,
	11,
	12,
	13,
	14,
	15,
	16,
	17,
	18,
	19,
	20,
	50,
};

uint32 Game_Arcade_modeMap[7] =
{
	MODE_HUMAN,
	MODE_DEVIL_HUNTER,
	MODE_SON_OF_SPARDA,
	MODE_DANTE_MUST_DIE,
	MODE_LEGENDARY_DARK_KNIGHT,
	MODE_SON_OF_SPARDA,
	MODE_SON_OF_SPARDA,
};

void Game_Arcade_Toggle(bool enable)
{
	LogFunctionBool(enable);
	if (enable)
	{
		// Main Menu Auto Confirm
		WriteAddress((appBaseAddr + 0x7CC2D), (appBaseAddr + 0x7CC33), 6); // Press Any Button
		Write<BYTE>((appBaseAddr + 0x7CFC2), 0xEB);                        // Level 1 Keyboard
		Write<BYTE>((appBaseAddr + 0x7C00E), 0xEB);                        // Level 2 Keyboard
		// Init Session
		WriteAddress((appBaseAddr + 0x7B265), (appBaseAddr + 0x7B26B), 6); // Force Load Game Route
		Write<BYTE>((appBaseAddr + 0x7B2AB), 0xEB);                        // Force Skip Mission Select
		// Mission Start Menu Auto Confirm
		WriteAddress((appBaseAddr + 0x77DED), (appBaseAddr + 0x77DF3), 6);
	}
	else
	{
		WriteAddress((appBaseAddr + 0x7CC2D), (appBaseAddr + 0x7CCBA), 6);
		Write<BYTE>((appBaseAddr + 0x7CFC2), 0x75);
		Write<BYTE>((appBaseAddr + 0x7C00E), 0x75);
		WriteAddress((appBaseAddr + 0x7B265), (appBaseAddr + 0x7B54B), 6);
		Write<BYTE>((appBaseAddr + 0x7B2AB), 0x75);
		WriteAddress((appBaseAddr + 0x77DED), (appBaseAddr + 0x77EE4), 6);
	}
}
