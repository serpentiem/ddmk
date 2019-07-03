#include "Arcade.h"

uint8 Game_Arcade_modeMap[4] =
{
	MODE_EASY,
	MODE_NORMAL,
	MODE_HARD,
	MODE_DANTE_MUST_DIE,
};
uint8 Game_Arcade_meleeWeaponMap[4] =
{
	WEAPON_FORCE_EDGE,
	WEAPON_ALASTOR,
	WEAPON_IFRIT,
	WEAPON_SPARDA,
};
uint8 Game_Arcade_rangedWeaponMap[4] =
{
	WEAPON_HANDGUN,
	WEAPON_SHOTGUN,
	WEAPON_GRENADEGUN,
	WEAPON_NIGHTMARE_BETA,
};

void Game_Arcade_Toggle(bool enable)
{
	LogFunctionBool(enable);
	if (enable)
	{
		WriteAddress((appBaseAddr + 0x3F8C2F), (appBaseAddr + 0x3F8C35), 6); // Force New Game
		WriteAddress((appBaseAddr + 0x3F8C3B), (appBaseAddr + 0x3F8C41), 6);
		WriteAddress((appBaseAddr + 0x3F8C43), (appBaseAddr + 0x3F8C49), 6);
		Write<BYTE>((appBaseAddr + 0x3F8C4C), 0xEB);
		WriteAddress((appBaseAddr + 0x3F8FBA), (appBaseAddr + 0x3F8FBC), 2);
		WriteAddress((appBaseAddr + 0x3F9163), (appBaseAddr + 0x3F9165), 2);
		WriteAddress((appBaseAddr + 0x3DC5B6), (appBaseAddr + 0x3DC5B8), 2); // Force Mission Start
		WriteAddress((appBaseAddr + 0x3DCADC), (appBaseAddr + 0x3DCADE), 2);
		//Write<WORD>((appBaseAddr + 0x3DC588), 0x9011);
	}
	else
	{
		WriteAddress((appBaseAddr + 0x3F8C2F), (appBaseAddr + 0x3F8D0D), 6);
		WriteAddress((appBaseAddr + 0x3F8C3B), (appBaseAddr + 0x3F8D0D), 6);
		WriteAddress((appBaseAddr + 0x3F8C43), (appBaseAddr + 0x3F8CE7), 6);
		Write<BYTE>((appBaseAddr + 0x3F8C4C), 0x74);
		WriteAddress((appBaseAddr + 0x3F8FBA), (appBaseAddr + 0x3F901A), 2);
		WriteAddress((appBaseAddr + 0x3F9163), (appBaseAddr + 0x3F91A0), 2);
		WriteAddress((appBaseAddr + 0x3DC5B6), (appBaseAddr + 0x3DC5C9), 2);
		WriteAddress((appBaseAddr + 0x3DCADC), (appBaseAddr + 0x3DCB1E), 2);
		//Write<WORD>((appBaseAddr + 0x3DC588), 0xC114);
	}
}
