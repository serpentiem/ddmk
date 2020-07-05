#ifndef __MODULE_ARCADE__
#define __MODULE_ARCADE__

module;
#include "../Core/Core.h"

#include "Vars.h"
export module ModuleName(Arcade);

import ModuleName(Config);

#ifdef __INTELLISENSE__
#include "Config.ixx"
#endif

export void Arcade_InitSession()
{
	if (!Config.Arcade.enable)
	{
		return;
	}

	IntroduceSessionData();

	sessionData.mission = Config.Arcade.mission;

	if ((sessionData.mission >= 1) && (sessionData.mission <= 20))
	{
		sessionData.mode = Config.Arcade.mode;
	}

	sessionData.enableTutorial = false;
	sessionData.useGoldOrb = true;

	if (Config.Arcade.mission == 21)
	{
		sessionData.bloodyPalace = true;
	}

	sessionData.goldOrbCount = 3;

	memset(sessionData.unlock, 1, 14);

	if (Config.Arcade.character == CHAR_DANTE)
	{
		sessionData.weapons[0] = Config.Arcade.meleeWeapons[0];
		sessionData.weapons[1] = Config.Arcade.meleeWeapons[1];
		sessionData.weapons[2] = Config.Arcade.rangedWeapons[0];
		sessionData.weapons[3] = Config.Arcade.rangedWeapons[1];
	}

	sessionData.costume = Config.Arcade.costume;
	sessionData.unlockDevilTrigger = true;
	sessionData.hitPoints = Config.Arcade.hitPoints;
	sessionData.magicPoints = Config.Arcade.magicPoints;

	if (Config.Arcade.character == CHAR_DANTE)
	{
		sessionData.style = Config.Arcade.style;
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
	if (!Config.Arcade.enable)
	{
		return;
	}

	LogFunction(dest);
	auto & character = *reinterpret_cast<uint8 *>(dest + 0x4565) = Config.Arcade.character;
}

export void Arcade_SetRoom()
{
	if (!Config.Arcade.enable || Config.BossRush.enable)
	{
		return;
	}

	LogFunction();

	IntroduceSessionData();
	IntroduceNextSceneData(return);

	if ((sessionData.mission >= 1) && (sessionData.mission <= 20))
	{
		if (!Config.Arcade.ignoreRoom)
		{
			nextSceneData.room = static_cast<uint16>(Config.Arcade.room);
		}

		if (!Config.Arcade.ignorePosition)
		{
			nextSceneData.position = static_cast<uint16>(Config.Arcade.position);
		}
	}

	if (sessionData.mission == 21)
	{
		auto floor = Config.Arcade.floor;
		if (floor >= countof(Arcade_floorHelper))
		{
			floor = 0;
		}

		nextSceneData.room     = Arcade_floorHelper[floor].room;
		nextSceneData.position = Arcade_floorHelper[floor].position;
	}
}

export void Arcade_CreateMainActor(byte8 * baseAddr)
{
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
	//Write<byte8>((appBaseAddr + 0x2411F5), (enable) ? 0xEB : 0x74); // Force start mission.
	// Force costume.
	WriteAddress((appBaseAddr + 0x217991), (enable) ? (appBaseAddr + 0x217993) : (appBaseAddr + 0x2179A2), 2);
	WriteAddress((appBaseAddr + 0x21799A), (enable) ? (appBaseAddr + 0x21799C) : (appBaseAddr + 0x2179A2), 2);
	// @Todo: Lazy solution, update proper vars!
	Write<byte8>((appBaseAddr + 0x1AA791), (enable) ? 0xEB : 0x75); // Skip orb notifications.
}

#endif
