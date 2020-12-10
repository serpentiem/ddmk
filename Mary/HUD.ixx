module;
#include "../Core/Core.h"

#include "Vars.h"
export module HUD;

import File;
import Global;
import Internal;
import Model;

#define debug false

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
			auto & item = weaponIcons[(WEAPON_REBELLION + weapon)];
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
			auto & item = weaponIcons[(WEAPON_YAMATO_VERGIL + weapon)];
			auto & fileIndex = fileIndices[weapon];
			item.modelFile   = File_staticFiles[id100V][(fileIndex + 1)];
			item.textureFile = File_staticFiles[id100V][(fileIndex + 0)];
		}
	}
}

export void HUD_UpdateStyleIcon
(
	uint8 style,
	uint8 character
)
{
	if
	(
		(InCutscene()) ||
		(InCredits()) ||
		(style >= MAX_STYLE)
	)
	{
		return;
	}

	IntroduceHUDPointers(return);

	if constexpr (debug)
	{
		LogFunction();
	}

	auto & modelData = *reinterpret_cast<ModelData *>(hudTop + hudTopOffs[HUD_TOP_STYLE_ICON]);

	ResetModel(modelData);

	auto modelFile   = styleIcons[style].modelFile;
	auto textureFile = styleIcons[style].textureFile;

	if
	(
		(
			(character == CHAR_BOB   ) ||
			(character == CHAR_VERGIL)
		) &&
		(style == STYLE_DARK_SLAYER)
	)
	{
		modelFile   = darkSlayerIcon.modelFile;
		textureFile = darkSlayerIcon.textureFile;
	}

	func_89960(modelData, modelFile, textureFile);
	func_89E30(modelData, 1);

	auto map = reinterpret_cast<uint8 *>(appBaseAddr + 0x4E9070);
	auto & effect = *reinterpret_cast<uint8 *>(hudTop + 0x690E) = map[style];
}

export bool HUD_UpdateWeaponIcon
(
	uint8 index,
	uint8 weapon
)
{
	if
	(
		(InCutscene()) ||
		(InCredits()) ||
		(weapon >= MAX_WEAPON)
	)
	{
		return false;
	}

	IntroduceHUDPointers(return false);

	if constexpr (debug)
	{
		LogFunction();
	}

	auto & modelData = *reinterpret_cast<ModelData *>(hudBottom + hudBottomOffs[index]);

	ResetModel(modelData);

	auto modelFile   = weaponIcons[weapon].modelFile;
	auto textureFile = weaponIcons[weapon].textureFile;

	func_89960(modelData, modelFile, textureFile);
	func_89E30(modelData, 1);

	return true;
}

export void HUD_Init()
{
	LogFunction();

	InitIcons();
}

#ifdef __GARBAGE__
#endif
