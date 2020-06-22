#include "WeaponSwitcher.h"


////#pragma warning(disable: 4102) // Unreferenced Label





uint8 Game_WeaponSwitcher_Melee_weaponMap[4] =
{
	WEAPON_FORCE_EDGE,
	WEAPON_ALASTOR,
	WEAPON_IFRIT,
	WEAPON_SPARDA,
};

uint8 Game_WeaponSwitcher_Ranged_weaponMap[4] =
{
	WEAPON_HANDGUN,
	WEAPON_SHOTGUN,
	WEAPON_GRENADEGUN,
	WEAPON_NIGHTMARE_BETA,
};

















uint8 Melee_index = 0;

float32 Melee_timer = 12;

//uint8 Ranged_index = 0;
//
//uint8 Melee_weapon[3] =
//{
//	WEAPON_ALASTOR,
//	WEAPON_IFRIT,
//	WEAPON_SPARDA,
//};

static DWORD Thread(LPVOID parameter)
{
	do
	{
		LoopStart:
		if (!Config.Game.WeaponSwitcher.enable)
		{
			goto LoopEnd;
		}
		if (!InGame())
		{
			goto LoopEnd;
		}
		static bool execute = false;
		if (GetButtonState() & GAMEPAD_RIGHT_TRIGGER)
		{
			if (execute)
			{
				execute = false;
				// @Todo: Add timeout!
				Melee_index++;
				if (Melee_index >= Config.Game.WeaponSwitcher.Melee.count)
				{
					Melee_index = 0;
				}
				BYTE * addr = *(BYTE **)(appBaseAddr + 0x60ACD0);
				uint8 & weapon = *(uint8 *)(addr + 0x1BCC);
				weapon = Config.Game.WeaponSwitcher.Melee.weapon[Melee_index];
			}
		}
		else
		{
			execute = true;
		}
		LoopEnd:
		Sleep(10);
	}
	while (true);
}

void Game_WeaponSwitcher_Init()
{
	LogFunction();
	CreateThread(0, 4096, Thread, 0, 0, 0);
}

void Game_WeaponSwitcher_Toggle(bool enable)
{
	LogFunction(enable);
	if (enable)
	{
		Write<BYTE>((appBaseAddr + 0x2ED3FD), 0xEB);                  // Disable Quick Swap
		Write<WORD>((appBaseAddr + 0x569D3A), GAMEPAD_RIGHT_TRIGGER); // Quick Swap Binding
		Write<WORD>((appBaseAddr + 0x569D40), GAMEPAD_RIGHT_THUMB);   // Taunt Binding
	}
	else
	{
		Write<BYTE>((appBaseAddr + 0x2ED3FD), 0x75);
		Write<WORD>((appBaseAddr + 0x569D3A), GAMEPAD_RIGHT_THUMB);
		Write<WORD>((appBaseAddr + 0x569D40), GAMEPAD_RIGHT_TRIGGER);
	}
}
