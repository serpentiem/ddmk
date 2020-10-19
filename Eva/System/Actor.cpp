#include "Actor.h"

static void LoadActor()
{
	LogFunction();
	if (!Config.Game.Arcade.enable)
	{
		return;
	}
	BYTE * addr = *(BYTE **)(appBaseAddr + 0x5EAB88);
	if (!addr)
	{
		return;
	}
	uint8 & hitPointsUnitCount   = *(uint8 *)(addr + 0x2464);
	uint8 & magicPointsUnitCount = *(uint8 *)(addr + 0x2465);
	DWORD & expertise            = *(DWORD *)(addr + 0x2468);
	addr = *(BYTE **)(appBaseAddr + 0x60ACD0);
	if (!addr)
	{
		return;
	}
	uint16 & hitPoints           = *(uint16 *)(addr + 0x17A2);
	uint16 & maxHitPoints        = *(uint16 *)(addr + 0x1BC8);
	uint16 & magicPointsHuman    = *(uint16 *)(addr + 0x1BCE);
	uint16 & maxMagicPointsHuman = *(uint16 *)(addr + 0x1BD0);
	uint16 & magicPointsDevil    = *(uint16 *)(addr + 0x1BD2);
	uint16 & maxMagicPointsDevil = *(uint16 *)(addr + 0x1BD4);

	//uint16 & meleeWeapon = *(uint16 *)(addr + 0x1BCC);
	//meleeWeapon = WEAPON_SPARDA_AERIAL;


	hitPointsUnitCount = Config.Game.Arcade.hitPointsUnitCount;
	hitPoints          = hitPointsUnitCount * 100;
	maxHitPoints       = hitPointsUnitCount * 100;

	magicPointsUnitCount = Config.Game.Arcade.magicPointsUnitCount;
	magicPointsHuman     = magicPointsUnitCount * 120;
	maxMagicPointsHuman  = magicPointsUnitCount * 120;
	magicPointsDevil     = magicPointsUnitCount * 200;
	maxMagicPointsDevil  = magicPointsUnitCount * 200;

	expertise = 0xFFFFFFFF;

	//DWORD & orbFlags = *(DWORD *)(addr + 0x247C);
	//orbFlags += OrbFlags_GreenOrbTaken | OrbFlags_RedOrbTaken;
}

void System_Actor_Init()
{
	LogFunction();
	{
		BYTE sect0[] =
		{
			0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc1.exe+2C3B30
		};
		FUNC func = CreateFunction(LoadActor, (appBaseAddr + 0x24F672), true, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteCall(func.sect0, (appBaseAddr + 0x2C3B30));
		WriteJump((appBaseAddr + 0x24F66D), func.addr);
	}
}
