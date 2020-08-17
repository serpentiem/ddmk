#ifndef __MODULE_HUD__
#define __MODULE_HUD__

module;
#include "../Core/Core.h"

#include "Vars.h"
export module ModuleName(HUD);

import ModuleName(File);
import ModuleName(Internal);
import ModuleName(Model);

#ifdef __INTELLISENSE__
#include "File.ixx"
#include "Internal.ixx"
#include "Model.ixx"
#endif

struct HUDIconHelper
{
	byte8 * modelFile;
	byte8 * textureFile;
};

HUDIconHelper styleIcons[MAX_STYLE] = {};
HUDIconHelper darkSlayerIcon = {};
HUDIconHelper weaponIcons[MAX_WEAPON] = {};

void InitIcons()
{
	// Style Icons
	{
		constexpr uint8 fileIndices[MAX_STYLE] =
		{
			20,
			22,
			18,
			24,
			26,
			28,
		};
		for_all(uint8, style, countof(fileIndices))
		{
			auto & item = styleIcons[style];
			auto & fileIndex = fileIndices[style];
			item.modelFile   = File_staticFiles[id100][(fileIndex + 1)];
			item.textureFile = File_staticFiles[id100][(fileIndex + 0)];
		}

		darkSlayerIcon.modelFile   = File_staticFiles[id100V][(18 + 1)];
		darkSlayerIcon.textureFile = File_staticFiles[id100V][(18 + 0)];
	}

	// Weapon Icons Dante
	{
		constexpr uint8 fileIndices[] =
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
		for_all(uint8, weapon, countof(fileIndices))
		{
			auto & item = weaponIcons[(WEAPON_DANTE_REBELLION + weapon)];
			auto & fileIndex = fileIndices[weapon];
			item.modelFile   = File_staticFiles[id100][(fileIndex + 1)];
			item.textureFile = File_staticFiles[id100][(fileIndex + 0)];
		}
	}

	// Weapon Icons Vergil
	{
		constexpr uint8 fileIndices[] =
		{
			42,
			44,
			30,
		};
		for_all(uint8, weapon, countof(fileIndices))
		{
			auto & item = weaponIcons[(WEAPON_VERGIL_YAMATO + weapon)];
			auto & fileIndex = fileIndices[weapon];
			item.modelFile   = File_staticFiles[id100V][(fileIndex + 1)];
			item.textureFile = File_staticFiles[id100V][(fileIndex + 0)];
		}
	}
}

export void HUD_UpdateStyleIcon
(
	uint8 style,
	uint8 character = CHAR_DANTE
)
{
	if (style >= MAX_STYLE)
	{
		return;
	}

	IntroduceHUDPointers(return);

	auto & modelData = *reinterpret_cast<ModelData *>(hudTop + hudTopOffs[HUD_TOP_STYLE_ICON]);

	ResetModel(modelData);

	byte8 * modelFile   = 0;
	byte8 * textureFile = 0;

	modelFile   = styleIcons[style].modelFile;
	textureFile = styleIcons[style].textureFile;

	if ((character == CHAR_VERGIL) && (style == STYLE_VERGIL_DARK_SLAYER))
	{
		modelFile = darkSlayerIcon.modelFile;
		textureFile = darkSlayerIcon.textureFile;
	}

	func_89960(modelData, modelFile, textureFile);
	func_89E30(modelData, 1);

	auto map = reinterpret_cast<uint8 *>(appBaseAddr + 0x4E9070);
	auto & effect = *reinterpret_cast<uint8 *>(hudTop + 0x690E) = map[style];
}

export void HUD_UpdateWeaponIcon
(
	uint8 index,
	uint8 weapon
)
{
	if (weapon >= MAX_WEAPON)
	{
		return;
	}

	IntroduceHUDPointers(return);

	auto & modelData = *reinterpret_cast<ModelData *>(hudBottom + hudBottomOffs[index]);

	ResetModel(modelData);

	byte8 * modelFile   = 0;
	byte8 * textureFile = 0;

	modelFile   = weaponIcons[weapon].modelFile;
	textureFile = weaponIcons[weapon].textureFile;

	func_89960(modelData, modelFile, textureFile);
	func_89E30(modelData, 1);
}

export void HUD_Init()
{
	LogFunction();

	InitIcons();
}

#endif

#ifdef __GARBAGE__



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



#endif
