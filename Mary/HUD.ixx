export module HUD;

import Core;

#include "../Core/Macros.h"

import File;
import Global;
import Internal;
import Model;
import Vars;

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



export void ToggleHideMainHUD(bool enable)
{
	LogFunction(enable);

	static bool run = false;



	// Top
	{
		auto addr = (appBaseAddr + 0x27E59C);
		constexpr uint32 size = 2;
		/*
		dmc3.exe+27E59C - 75 0F    - jne dmc3.exe+27E5AD
		dmc3.exe+27E59E - 48 8B D7 - mov rdx,rdi
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			Write<byte8>(addr, 0xEB);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Bottom
	{
		auto addr = (appBaseAddr + 0x2810F8);
		constexpr uint32 size = 2;
		/*
		dmc3.exe+2810F8 - 75 0F    - jne dmc3.exe+281109
		dmc3.exe+2810FA - 49 8B D6 - mov rdx,r14
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			Write<byte8>(addr, 0xEB);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Style Rank
	{
		auto addr = (appBaseAddr + 0x2BB194);
		constexpr uint32 size = 6;
		/*
		dmc3.exe+2BB194 - 0F85 18020000     - jne dmc3.exe+2BB3B2
		dmc3.exe+2BB19A - 83 B9 203D0000 00 - cmp dword ptr [rcx+00003D20],00
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			Write<byte16>(addr, 0xE990);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}



	run = true;
}

export void ToggleHideLockOn(bool enable)
{
	LogFunction(enable);

	static bool run = false;



	{
		auto addr = (appBaseAddr + 0x296E77);
		constexpr uint32 size = 2;
		/*
		dmc3.exe+296E77 - 75 14    - jne dmc3.exe+296E8D
		dmc3.exe+296E79 - 48 8B D3 - mov rdx,rbx
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			Write<byte8>(addr, 0xEB);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}



	run = true;
}

export void ToggleHideBossHUD(bool enable)
{
	LogFunction(enable);

	static bool run = false;



	{
		auto addr = (appBaseAddr + 0x27FF69);
		constexpr uint32 size = 2;
		/*
		dmc3.exe+27FF69 - 75 0F    - jne dmc3.exe+27FF7A
		dmc3.exe+27FF6B - 48 8B D7 - mov rdx,rdi
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			Write<byte8>(addr, 0xEB);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}



	run = true;
}

#ifdef __GARBAGE__
#endif
