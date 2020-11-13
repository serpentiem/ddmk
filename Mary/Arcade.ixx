module;
#include "../Core/Core.h"

#include "Vars.h"
export module Arcade;

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

	sessionData.enableTutorial = false;
	sessionData.useGoldOrb = true;

	if (activeConfig.Arcade.mission == 21)
	{
		sessionData.bloodyPalace = true;
	}

	sessionData.goldOrbCount = 3;

	memset(sessionData.unlock, 1, 14);

	if (activeConfig.Arcade.character == CHAR_DANTE)
	{
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
	return;
	
	if (!activeConfig.Arcade.enable)
	{
		return;
	}

	LogFunction(baseAddr);

	// Unlock Weapon Files
	{
		auto pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);
		if (!pool)
		{
			return;
		}
		if (!pool[6])
		{
			return;
		}
		auto unlock = reinterpret_cast<byte8 *>(pool[6] + 0x7E2);
		memset(unlock, 0xFF, 8);
		/*
		dmc3.exe+2A9F6D - 48 8B 05 B46E9E00    - mov rax,[dmc3.exe+C90E28]
		dmc3.exe+2A9F74 - 48 8B 50 30          - mov rdx,[rax+30]
		dmc3.exe+2A9F7C - 41 84 84 10 E2070000 - test [r8+rdx+000007E2],al
		*/
	}
}

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
