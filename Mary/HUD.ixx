#ifndef __MODULE_HUD__
#define __MODULE_HUD__

module;
#include "../Core/Core.h"

#include "Vars.h"
export module ModuleName(HUD);

import ModuleName(File);
import ModuleName(Internal);

#ifdef __INTELLISENSE__
#include "File.ixx"
#include "Internal.ixx"
#endif

// @Todo: Move to vars.
// @Todo: Solve unknown enums.
export enum HUD_TOP
{
	TOP_HIT_POINTS_FRAME,
	TOP_HIT_POINTS_BAR,
	TOP_HIT_POINTS_BACKGROUND,
	BOTTOM_HIT_POINTS_FRAME,
	BOTTOM_HIT_POINTS_BAR,
	BOTTOM_HIT_POINTS_BACKGROUND,
	MAGIC_ORBS,
	STYLE_ICON,
	RED_ORB_COUNTER,
	UNKNOWN_1,
	UNKNOWN_2,
	FLUX,
	UNKNOWN_3,
};

export enum HUD_BOTTOM
{
	RANGED_WEAPON_1,
	RANGED_WEAPON_2,
	MELEE_WEAPON_1,
	MELEE_WEAPON_2,
};

constexpr uint32 HUD_topOff[] =
{
	0x700,
	0xE80,
	0x1600,
	0x1D80,
	0x2500,
	0x2C80,
	0x3400,
	0x3B80,
	0x4300,
	0x4A80,
	0x5200,
	0x5980,
	0x6100,
};

constexpr uint32 HUD_bottomOff[] =
{
	0x880,
	0x1000,
	0x1780,
	0x1F00,
};

export struct HUDIconHelper
{
	byte8 * model;
	byte8 * texture;
};

extern HUDIconHelper HUD_styleIconDante[MAX_STYLE];
extern HUDIconHelper HUD_styleIconVergil[MAX_STYLE];
extern HUDIconHelper HUD_weaponIcon[MAX_WEAPON];

//inline bool HUD_IsVisible()
//{
//	if (!InGame())
//	{
//		return false;
//	}
//	// @Todo: Update pointer!
//	byte8 ** addr = (byte8 **)(appBaseAddr + 0xCF2520);
//	byte8 * item = addr[44];
//	if (!item)
//	{
//		return false;
//	}
//	uint8 & alpha = *(uint8 *)(item + 0x6920);
//	return (alpha > 0) ? true : false;
//}

export HUDIconHelper HUD_styleIconDante [MAX_STYLE ] = {};
export HUDIconHelper HUD_styleIconVergil[MAX_STYLE ] = {};

export HUDIconHelper HUD_weaponIcon     [MAX_WEAPON] = {};

// @Research: Make map local.
constexpr uint8 styleIconMapDante[MAX_STYLE] =
{
	20,
	22,
	18,
	24,
	26,
	28,
};

constexpr uint8 weaponIconMapDante[] =
{
	42,
	44,
	46,
	48,
	50,
	30,
	32,
	34,
	36,
	38,
};

constexpr uint8 weaponIconMapVergil[] =
{
	42,
	44,
	30,
};

// @Todo: Either create helper for this or access actor data.
//bool HUD_updateStyleIcon = false;
//
//void HUD_Update()
//{
//	if (!HUD_updateStyleIcon)
//	{
//		return;
//	}
//	if (!HUD_IsVisible())
//	{
//		return;
//	}
//	HUD_updateStyleIcon = false;
//	//HUD_UpdateStyleIcon();
//}


















export void HUD_UpdateStyleIcon
(
	uint8 style,
	byte8 * model,
	byte8 * texture
)
{
	auto addr = *reinterpret_cast<byte8 **>(appBaseAddr + 0xC90E28);
	if (!addr)
	{
		return;
	}
	addr -= 0x180;
	auto top    = *reinterpret_cast<byte8 **>(addr + 0x1B070);
	auto bottom = *reinterpret_cast<byte8 **>(addr + 0x1B078);

	auto styleIcon = (top + 0x3B80);

	func_897B0(styleIcon);
	func_89450(styleIcon);
	memset(styleIcon, 0, 0x780);
	func_89270(styleIcon);

	auto map = reinterpret_cast<uint8 *>(appBaseAddr + 0x4E9070);
	auto & effect = *reinterpret_cast<uint8 *>(top + 0x690E) = map[style];

	func_89960(styleIcon, model, texture);
	func_89E30(styleIcon, 1);
}

export void HUD_UpdateWeaponIcon
(
	uint8 index,
	byte8 * model,
	byte8 * texture
)
{
	auto addr = *reinterpret_cast<byte8 **>(appBaseAddr + 0xC90E28);
	if (!addr)
	{
		return;
	}
	addr -= 0x180; // @Todo: Add source.
	auto top    = *reinterpret_cast<byte8 **>(addr + 0x1B070);
	auto bottom = *reinterpret_cast<byte8 **>(addr + 0x1B078);

	auto dest = (bottom + HUD_bottomOff[index]);

	func_897B0(dest);
	func_89450(dest);
	memset(dest, 0, 0x780);
	func_89270(dest);

	func_89960(dest, model, texture);
	func_89E30(dest, 1);
}

export void HUD_Init()
{
	LogFunction();

	// Init Icons
	{
		for_all(uint8, index, countof(styleIconMapDante))
		{
			auto & fileIndex = styleIconMapDante[index];
			HUD_styleIconDante[index].model   = File_staticFiles[id100][(fileIndex + 1)];
			HUD_styleIconDante[index].texture = File_staticFiles[id100][(fileIndex + 0)];
		}

		HUD_styleIconVergil[STYLE_VERGIL_DARK_SLAYER].model   = File_staticFiles[id100V][(18 + 1)];
		HUD_styleIconVergil[STYLE_VERGIL_DARK_SLAYER].texture = File_staticFiles[id100V][(18 + 0)];

		for_all(uint8, index, countof(weaponIconMapDante))
		{
			auto & fileIndex = weaponIconMapDante[index];
			HUD_weaponIcon[(WEAPON_DANTE_REBELLION + index)].model   = File_staticFiles[id100][(fileIndex + 1)];
			HUD_weaponIcon[(WEAPON_DANTE_REBELLION + index)].texture = File_staticFiles[id100][(fileIndex + 0)];
		}

		for_all(uint8, index, countof(weaponIconMapVergil))
		{
			auto & fileIndex = weaponIconMapVergil[index];
			HUD_weaponIcon[(WEAPON_VERGIL_YAMATO + index)].model   = File_staticFiles[id100V][(fileIndex + 1)];
			HUD_weaponIcon[(WEAPON_VERGIL_YAMATO + index)].texture = File_staticFiles[id100V][(fileIndex + 0)];
		}
	}


	for_all(uint8, index, countof(HUD_weaponIcon))
	{
		Log("%u %llX", index, HUD_weaponIcon[index].model);
	}
}

#endif
