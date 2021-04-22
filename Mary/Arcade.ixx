module;

#include "../Core/Macros.h" //
// #include "../Core/Core.h"

// #include "Vars.h"
export module Arcade;


import Core;


import Vars;


#define memset SetMemory
#define memcpy CopyMemory

import Config;

export void Arcade_InitSession()
{
	if (!activeConfig.Arcade.enable)
	{
		return;
	}

	LogFunction();

	IntroduceSessionData();

	sessionData.mission = activeConfig.Arcade.mission;

	if ((sessionData.mission >= 1) && (sessionData.mission <= 20))
	{
		sessionData.mode = activeConfig.Arcade.mode;
	}

	sessionData.enableTutorial = true;
	sessionData.useGoldOrb = true;

	if (activeConfig.Arcade.mission == 21)
	{
		sessionData.bloodyPalace = true;
	}

	//sessionData.goldOrbCount = 3;
	sessionData.itemCounts[ITEM_GOLD_ORB] = 3;


	if constexpr (debug)
	{
		sessionData.redOrbs = 1500000;
	}






	SetMemory
	(
		sessionData.unlock,
		1,
		sizeof(sessionData.unlock)
	);

	if (activeConfig.Arcade.character == CHAR_DANTE)
	{
		// @Todo: Update.
		memcpy
		(
			sessionData.weapons,
			activeConfig.Arcade.weapons,
			4
		);
		// sessionData.weapons[0] = activeConfig.Arcade.meleeWeapons[0];
		// sessionData.weapons[1] = activeConfig.Arcade.meleeWeapons[1];
		// sessionData.weapons[2] = activeConfig.Arcade.rangedWeapons[0];
		// sessionData.weapons[3] = activeConfig.Arcade.rangedWeapons[1];
	}

	sessionData.rangedWeaponLevels[0] = 2;
	sessionData.rangedWeaponLevels[1] = 2;
	sessionData.rangedWeaponLevels[2] = 2;
	sessionData.rangedWeaponLevels[3] = 2;
	sessionData.rangedWeaponLevels[4] = 2;



	sessionData.costume = activeConfig.Arcade.costume;
	sessionData.unlockDevilTrigger = true;
	sessionData.hitPoints = activeConfig.Arcade.hitPoints;
	sessionData.magicPoints = activeConfig.Arcade.magicPoints;

	if (activeConfig.Arcade.character == CHAR_DANTE)
	{
		sessionData.style = activeConfig.Arcade.style;
	}

	memset(sessionData.styleLevel, 0, (MAX_STYLE * 4));

	sessionData.styleLevel[0] = 2;
	sessionData.styleLevel[1] = 2;
	sessionData.styleLevel[2] = 2;
	sessionData.styleLevel[3] = 2;

	memset(sessionData.styleExperience, 0, (MAX_STYLE * 4));

	memset(sessionData.expertise, 0xFF, (8 * 4));

	auto & controllerMagic = *reinterpret_cast<uint32 *>(appBaseAddr + 0x553000) = 0;
}

export void Arcade_SetCharacter(byte8 * dest)
{
	if (!activeConfig.Arcade.enable)
	{
		return;
	}

	LogFunction(dest);
	auto & character = *reinterpret_cast<uint8 *>(dest + 0x4565) = activeConfig.Arcade.character;
}

export void Arcade_SetRoom()
{
	if (!activeConfig.Arcade.enable || activeConfig.BossRush.enable)
	{
		return;
	}

	LogFunction();

	IntroduceSessionData();
	IntroduceNextEventData(return);

	if ((sessionData.mission >= 1) && (sessionData.mission <= 20))
	{
		if (!activeConfig.Arcade.ignoreRoom)
		{
			nextEventData.room = static_cast<uint16>(activeConfig.Arcade.room);
		}

		if (!activeConfig.Arcade.ignorePosition)
		{
			nextEventData.position = static_cast<uint16>(activeConfig.Arcade.position);
		}
	}

	if (sessionData.mission == 21)
	{
		auto floor = activeConfig.Arcade.floor;
		if (floor >= countof(Arcade_floorHelper))
		{
			floor = 0;
		}

		nextEventData.room     = Arcade_floorHelper[floor].room;
		nextEventData.position = Arcade_floorHelper[floor].position;
	}
}

export void Arcade_CreateMainActor(byte8 * baseAddr)
{
	if (!activeConfig.Arcade.enable)
	{
		return;
	}

	LogFunction(baseAddr);

	// Unlock Files
	[&]()
	{
		auto pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);
		if
		(
			!pool ||
			!pool[1] ||
			!pool[6]
		)
		{
			return;
		}

		SetMemory((pool[1] + 0x82), 0xFF, 11);
		SetMemory((pool[1] + 0x8E), 0xFF, 1);
		SetMemory((pool[6] + 0x7E4), 0xFF, 6);
	}();

	auto & unlock = *reinterpret_cast<byte32(*)[4]>(appBaseAddr + 0x564594);

	unlock[0] |= 1;

	/*
	dmc3.exe+2AADD0 - 44 84 94 19 82000000 - test [rcx+rbx+00000082],r10l
	dmc3.exe+2AA003 - 41 84 84 10 8A000000 - test [r8+rdx+0000008A],al
	dmc3.exe+2AA1BF - 0FB6 99 8E000000     - movzx ebx,byte ptr [rcx+0000008E]
	dmc3.exe+2A9F7C - 41 84 84 10 E2070000 - test [r8+rdx+000007E2],al
	*/
}















// @Todo: Update.
export void Arcade_Toggle(bool enable)
{
	LogFunction(enable);
	Write<byte8>((appBaseAddr + 0x2433FB), (enable) ? 0xEB : 0x74); // Force new game.
	Write<byte8>((appBaseAddr + 0x243299), (enable) ? 0xEB : 0x74); // Skip mission select menu.
	Write<byte8>((appBaseAddr + 0x2411F5), (enable) ? 0xEB : 0x74); // Force start mission.
	// Force costume.
	WriteAddress((appBaseAddr + 0x217991), (enable) ? (appBaseAddr + 0x217993) : (appBaseAddr + 0x2179A2), 2);
	WriteAddress((appBaseAddr + 0x21799A), (enable) ? (appBaseAddr + 0x21799C) : (appBaseAddr + 0x2179A2), 2);
	// @Todo: Lazy solution, update proper vars!
	Write<byte8>((appBaseAddr + 0x1AA791), (enable) ? 0xEB : 0x75); // Skip orb notifications.
}
