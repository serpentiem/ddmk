module;
#include <xmmintrin.h>
export module Internal;

import Core;

#include "../Core/Macros.h"

import Vars;

#include "Macros.h"

// $DataStart

export typedef void(__fastcall * func_2C99C0_t)(uint32 meleeWeapon, uint32 playAuraEffect); // Update Melee Weapon
export typedef void(__fastcall * func_2C4A00_t)(uint32 meleeWeaponForm); // Update Melee Weapon Form
export typedef void(__fastcall * func_2C4C50_t)(uint32 rangedWeapon); // Update Ranged Weapon
export typedef void(__fastcall * func_3C8DC0_t)(); // Update Weapons
export typedef void(__fastcall * func_2F0610_t)(PlayerActorData & actorData); // Charge Update

export func_2C99C0_t func_2C99C0 = 0; // (uint32 meleeWeapon, uint32 playAuraEffect)
export func_2C4A00_t func_2C4A00 = 0; // (uint32 meleeWeaponForm)
export func_2C4C50_t func_2C4C50 = 0; // (uint32 rangedWeapon)
export func_3C8DC0_t func_3C8DC0 = 0; // ()
export func_2F0610_t func_2F0610 = 0; // (PlayerActorData & actorData)

export void Internal_Init()
{
	LogFunction();
	{
		auto func = CreateFunction((appBaseAddr + 0x2C99C0));
		func_2C99C0 = (func_2C99C0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x2C4A00));
		func_2C4A00 = (func_2C4A00_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x2C4C50));
		func_2C4C50 = (func_2C4C50_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x3C8DC0));
		func_3C8DC0 = (func_3C8DC0_t)func.addr;
	}
	{
		auto func = CreateFunction((appBaseAddr + 0x2F0610));
		func_2F0610 = (func_2F0610_t)func.addr;
	}
}

// $DataEnd
