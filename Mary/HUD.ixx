export module HUD;

import Core;

#include "../Core/Macros.h"

import File;
import Global;
import Internal;
import Model;
import Vars;

#define debug false

#include "Macros.h"



struct HUDIconHelper
{
	byte8 * modelFile;
	byte8 * textureFile;
};

HUDIconHelper styleIcons[STYLE::MAX] = {};
HUDIconHelper darkSlayerIcon = {};
HUDIconHelper weaponIcons[WEAPON::MAX] = {};

void InitIcons()
{
	// Style Icons
	{
		constexpr uint8 fileIndices[STYLE::MAX] =
		{
			20,
			22,
			18,
			24,
			26,
			28,
		};
		old_for_all(uint8, style, countof(fileIndices))
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
		old_for_all(uint8, weapon, countof(fileIndices))
		{
			auto & item = weaponIcons[(WEAPON::REBELLION + weapon)];
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
		old_for_all(uint8, weapon, countof(fileIndices))
		{
			auto & item = weaponIcons[(WEAPON::YAMATO_VERGIL + weapon)];
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
		(style >= STYLE::MAX)
	)
	{
		return;
	}

	IntroduceHUDPointers(return);

	if constexpr (debug)
	{
		LogFunction();
	}

	auto & modelData = *reinterpret_cast<ModelData *>(hudTop + hudTopOffs[HUD_TOP::STYLE_ICON]);

	ResetModel(modelData);

	auto modelFile   = styleIcons[style].modelFile;
	auto textureFile = styleIcons[style].textureFile;

	if
	(
		(
			(character == CHARACTER::BOB   ) ||
			(character == CHARACTER::VERGIL)
		) &&
		(style == STYLE::DARK_SLAYER)
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
		(weapon >= WEAPON::MAX)
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

export void ToggleForceVisibleHUD(bool enable)
{
	static bool run = false;



	{
		auto addr = (appBaseAddr + 0x27E800);
		constexpr uint32 size = 2;
		/*
		dmc3.exe+27E800 - 74 63          - je dmc3.exe+27E865
		dmc3.exe+27E802 - 8B 86 28690000 - mov eax,[rsi+00006928]
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

	{
		auto addr = (appBaseAddr + 0x27DF3E);
		constexpr uint32 size = 2;
		/*
		dmc3.exe+27DF3E - 75 59               - jne dmc3.exe+27DF99
		dmc3.exe+27DF40 - F3 0F10 8F 18690000 - movss xmm1,[rdi+00006918]
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

	{
		auto addr = (appBaseAddr + 0x280DB9);
		constexpr uint32 size = 6;
		/*
		dmc3.exe+280DB9 - 0F86 3F020000 - jbe dmc3.exe+280FFE
		dmc3.exe+280DBF - 41 FE 07      - inc byte ptr [r15]
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

#ifdef __GARBAGE__
#endif
