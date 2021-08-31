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

export func_2C99C0_t func_2C99C0 = 0; // (uint32 meleeWeapon, uint32 playAuraEffect)
export func_2C4A00_t func_2C4A00 = 0; // (uint32 meleeWeaponForm)
export func_2C4C50_t func_2C4C50 = 0; // (uint32 rangedWeapon)
export func_3C8DC0_t func_3C8DC0 = 0; // ()

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
}

// $DataEnd
