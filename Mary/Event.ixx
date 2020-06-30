#ifndef __MODULE_EVENT__
#define __MODULE_EVENT__

module;
#include "../Core/Core.h"

#include "ActorData.h"
#include "Internal.h"
#include "Vars.h"
export module ModuleName(Event);

import ModuleName(Actor);
import ModuleName(Arcade);
import ModuleName(Config);
import ModuleName(File);
import ModuleName(Mobility);

#ifdef __INTELLISENSE__
#include "Actor.ixx"
#include "Arcade.ixx"
#include "Config.ixx"
#include "File.ixx"
#include "Mobility.ixx"
#endif

constexpr bool debug = true;













bool skipTrack = false;

bool SetTrack
(
	byte8 * dest,
	const char * filename,
	uint32 arg3,
	uint32 arg4
)
{
	Log("%s %llX %s %u %u", FUNC_NAME, dest, filename, arg3, arg4);

	//if (!Config.BossRush.enable)
	//{
	//	return true;
	//}

	if (skipTrack)
	{
		skipTrack = false;

		return false;
	}

	return true;
}

























void Arcade_InitSession()
{
	if (!Config.Arcade.enable)
	{
		return;
	}

	auto & sessionData = *reinterpret_cast<SESSION_DATA *>(appBaseAddr + 0xC8F250);

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

void Arcade_SetCharacter(byte8 * dest)
{
	if (!Config.Arcade.enable)
	{
		return;
	}

	LogFunction(dest);
	auto & character = *reinterpret_cast<uint8 *>(dest + 0x4565) = Config.Arcade.character;
}

void Arcade_SetRoom()
{
	if (!Config.Arcade.enable || Config.BossRush.enable)
	{
		return;
	}

	LogFunction();

	auto & sessionData = *reinterpret_cast<SESSION_DATA *>(appBaseAddr + 0xC8F250);

	auto pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E10);
	if (!pool)
	{
		return;
	}
	if (!pool[8])
	{
		return;
	}
	if (!pool[12])
	{
		return;
	}
	auto & eventData = *reinterpret_cast<EVENT_DATA *>(pool[8]);
	auto & nextEventData = *reinterpret_cast<NEXT_EVENT_DATA *>(pool[12]);

	if ((sessionData.mission >= 1) && (sessionData.mission <= 20))
	{
		if (!Config.Arcade.ignoreRoom)
		{
			nextEventData.room = static_cast<uint16>(Config.Arcade.room);
		}

		if (!Config.Arcade.ignorePosition)
		{
			nextEventData.position = static_cast<uint16>(Config.Arcade.position);
		}
	}

	if (sessionData.mission == 21)
	{
		auto floor = Config.Arcade.floor;
		if (floor >= countof(Arcade_floorHelper))
		{
			floor = 0;
		}

		nextEventData.room     = Arcade_floorHelper[floor].room;
		nextEventData.position = Arcade_floorHelper[floor].position;
	}
}

void BossRush_SetRoom()
{
	if (!Config.BossRush.enable)
	{
		return;
	}

	LogFunction();

	auto & sessionData = *reinterpret_cast<SESSION_DATA *>(appBaseAddr + 0xC8F250);

	auto pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E10);
	if (!pool)
	{
		return;
	}
	if (!pool[8])
	{
		return;
	}
	if (!pool[12])
	{
		return;
	}
	auto & eventData = *reinterpret_cast<EVENT_DATA *>(pool[8]);
	auto & nextEventData = *reinterpret_cast<NEXT_EVENT_DATA *>(pool[12]);

	auto pool2 = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E30);
	if (!pool2)
	{
		return;
	}
	if (!pool2[1])
	{
		return;
	}
	auto flags = reinterpret_cast<byte32 *>(pool2[1]);

	auto SetNextEventData = [&](uint8 boss)
	{
		nextEventData.room     = bossHelper[boss].room;
		nextEventData.position = bossHelper[boss].position;
	};

	if (nextEventData.room = missionStartHelper[sessionData.mission].room)
	{
		switch (sessionData.mission)
		{
		case 3:
		{
			SetNextEventData(BOSS_CERBERUS);
			flags[20] = 1;
			break;
		}
		case 4:
		{
			SetNextEventData(BOSS_GIGAPEDE);
			break;
		}
		case 5:
		{
			skipTrack = true;

			if (!Config.BossRush.Mission5.skipJester)
			{
				SetNextEventData(BOSS_JESTER_1);
			}
			else
			{
				SetNextEventData(BOSS_AGNI_RUDRA);
				flags[20] = 1;
			}
			break;
		}
		case 7:
		{
			SetNextEventData(BOSS_VERGIL_1);
			break;
		}
		case 8:
		{
			SetNextEventData(BOSS_LEVIATHAN);
			*reinterpret_cast<uint8 *>(reinterpret_cast<byte8 *>(pool2) + 0x6A) = 1;
			*reinterpret_cast<byte8 *>(pool[12] + 0x7DF) = 0x40;
			break;
		}
		case 9:
		{
			SetNextEventData(BOSS_NEVAN);
			flags[20] = 1;
			break;
		}
		case 11:
		{
			SetNextEventData(BOSS_BEOWULF);
			flags[20] = 1;
			break;
		}
		case 12:
		{
			if (!Config.BossRush.Mission12.skipJester)
			{
				SetNextEventData(BOSS_JESTER_2);
			}
			else if (!Config.BossRush.Mission12.skipGeryonPart1)
			{
				SetNextEventData(BOSS_GERYON_PART_1);
				flags[20] = 1;
			}
			else
			{
				SetNextEventData(BOSS_GERYON_PART_2);
				flags[20] = 2;
			}
			break;
		}
		case 13:
		{
			SetNextEventData(BOSS_VERGIL_2);
			break;
		}
		case 16:
		{
			SetNextEventData(BOSS_LADY);
			flags[20] = 1;
			break;
		}
		case 17:
		{
			if (!Config.BossRush.Mission17.skipJester)
			{
				SetNextEventData(BOSS_JESTER_3);
			}
			else
			{
				SetNextEventData(BOSS_DOPPELGANGER);
			}
			break;
		}
		case 18:
		{
			SetNextEventData(BOSS_TAIZAI_REBORN);
			break;
		}
		case 19:
		{
			if (!Config.BossRush.Mission19.skipArkhamPart1)
			{
				SetNextEventData(BOSS_ARKHAM_PART_1);
			}
			else
			{
				SetNextEventData(BOSS_ARKHAM_PART_2);
				flags[20] = 1;
			}
			break;
		}
		}
	}
}

void BossRush_SetNextRoom()
{
	if (!Config.BossRush.enable)
	{
		return;
	}

	LogFunction();

	auto & sessionData = *reinterpret_cast<SESSION_DATA *>(appBaseAddr + 0xC8F250);

	auto pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E10);
	if (!pool)
	{
		return;
	}
	if (!pool[8])
	{
		return;
	}
	if (!pool[12])
	{
		return;
	}
	auto & eventData = *reinterpret_cast<EVENT_DATA *>(pool[8]);
	auto & nextEventData = *reinterpret_cast<NEXT_EVENT_DATA *>(pool[12]);

	auto pool2 = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E30);
	if (!pool2)
	{
		return;
	}
	if (!pool2[1])
	{
		return;
	}
	auto flags = reinterpret_cast<byte32 *>(pool2[1]);

	auto SetNextEventData = [&](uint8 boss)
	{
		nextEventData.room     = bossHelper[boss].room;
		nextEventData.position = bossHelper[boss].position;
	};

	switch (sessionData.mission)
	{
	case 5:
	{
		if (eventData.room == bossHelper[BOSS_JESTER_1].room)
		{
			SetNextEventData(BOSS_AGNI_RUDRA);
			flags[20] = 1;
		}
		break;
	}
	case 12:
	{
		if (eventData.room == bossHelper[BOSS_JESTER_2].room)
		{
			if (!Config.BossRush.Mission12.skipGeryonPart1)
			{
				SetNextEventData(BOSS_GERYON_PART_1);
				flags[20] = 1;
			}
			else
			{
				SetNextEventData(BOSS_GERYON_PART_2);
				flags[20] = 2;
			}
		}
		break;
	}
	case 17:
	{
		if (eventData.room == bossHelper[BOSS_JESTER_3].room)
		{
			SetNextEventData(BOSS_DOPPELGANGER);
		}
		break;
	}
	case 18:
	{
		switch (static_cast<uint16>(eventData.room))
		{
		case bossHelper[BOSS_TAIZAI_REBORN].room:
		{
			SetNextEventData(BOSS_CERBERUS_REBORN);
			break;
		}
		case bossHelper[BOSS_CERBERUS_REBORN].room:
		{
			SetNextEventData(BOSS_GIGAPEDE_REBORN);
			break;
		}
		case bossHelper[BOSS_GIGAPEDE_REBORN].room:
		{
			SetNextEventData(BOSS_AGNI_RUDRA_REBORN);
			break;
		}
		case bossHelper[BOSS_AGNI_RUDRA_REBORN].room:
		{
			SetNextEventData(BOSS_LEVIATHAN_REBORN);
			break;
		}
		case bossHelper[BOSS_LEVIATHAN_REBORN].room:
		{
			SetNextEventData(BOSS_NEVAN_REBORN);
			break;
		}
		case bossHelper[BOSS_NEVAN_REBORN].room:
		{
			SetNextEventData(BOSS_BEOWULF_REBORN);
			break;
		}
		case bossHelper[BOSS_BEOWULF_REBORN].room:
		{
			SetNextEventData(BOSS_GERYON_REBORN);
			break;
		}
		case bossHelper[BOSS_GERYON_REBORN].room:
		{
			SetNextEventData(BOSS_DOPPELGANGER_REBORN);
			break;
		}
		case bossHelper[BOSS_DOPPELGANGER_REBORN].room:
		{
			nextEventData.room     = 403;
			nextEventData.position = 2;
			flags[14] = 0x3FE;
			flags[15] = 0x1FF;
			break;
		}
		}
		break;
	}
	}
}

void BossRush_SetContinueRoom()
{
	if (!Config.BossRush.enable)
	{
		return;
	}

	LogFunction();

	auto & sessionData = *reinterpret_cast<SESSION_DATA *>(appBaseAddr + 0xC8F250);

	auto pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E10);
	if (!pool)
	{
		return;
	}
	if (!pool[8])
	{
		return;
	}
	if (!pool[12])
	{
		return;
	}
	auto & eventData = *reinterpret_cast<EVENT_DATA *>(pool[8]);
	auto & nextEventData = *reinterpret_cast<NEXT_EVENT_DATA *>(pool[12]);

	nextEventData.room     = static_cast<uint16>(eventData.room    );
	nextEventData.position = static_cast<uint16>(eventData.position);
}



































//const char * BossRush_SetTrack(const char * path)
//{
//	//LogFunctionStart();
//
//	//VARS vars = {};
//	//if (!vars.init)
//	//{
//	//	return 0;
//	//}
//	//uint32 & room         = *vars.room;
//	//uint32 & position     = *vars.position;
//	//uint16 & nextRoom     = *vars.nextRoom;
//	//uint16 & nextPosition = *vars.nextPosition;
//	//byte32 * flags        = vars.flags;
//	//uint32 & mission      = *vars.mission;
//
//	//switch (mission)
//	//{
//	//case 5:
//	//	if (_stricmp(path, "afs/sound/Battle_03.adx") == 0)
//	//	{
//	//		mediaError = MEDIA_SKIP_TRACK;
//	//		return 0;
//	//	}
//	//	if (nextRoom == ROOM_AGNI_RUDRA)
//	//	{
//	//		if (_stricmp(path, TRACK_JESTER_1) == 0)
//	//		{
//	//			mediaError = MEDIA_SKIP_TRACK;
//	//			return 0;
//	//		}
//	//	}
//	//	break;
//	//case 12:
//	//	if (nextRoom == ROOM_GERYON)
//	//	{
//	//		if (_stricmp(path, TRACK_JESTER_2) == 0)
//	//		{
//	//			mediaError = MEDIA_SKIP_TRACK;
//	//			return 0;
//	//		}
//	//	}
//	//	break;
//	//case 17:
//	//	if (nextRoom == ROOM_DOPPELGANGER)
//	//	{
//	//		if (_stricmp(path, TRACK_JESTER_3) == 0)
//	//		{
//	//			mediaError = MEDIA_SKIP_TRACK;
//	//			return 0;
//	//		}
//	//	}
//	//	break;
//	//}
//
//	//LogFunctionEnd();
//
//	return 0;
//}



void BossRush_StageLoadComplete()
{
	if (!Config.BossRush.enable)
	{
		return;
	}

	LogFunction();

	auto & sessionData = *reinterpret_cast<SESSION_DATA *>(appBaseAddr + 0xC8F250);

	auto pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E10);
	if (!pool)
	{
		return;
	}
	if (!pool[8])
	{
		return;
	}
	if (!pool[12])
	{
		return;
	}
	auto & eventData = *reinterpret_cast<EVENT_DATA *>(pool[8]);
	auto & nextEventData = *reinterpret_cast<NEXT_EVENT_DATA *>(pool[12]);

	auto pool2 = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E30);
	if (!pool2)
	{
		return;
	}
	if (!pool2[1])
	{
		return;
	}
	auto flags = reinterpret_cast<byte32 *>(pool2[1]);

	auto SetNextEventData = [&](uint8 boss)
	{
		nextEventData.room     = bossHelper[boss].room;
		nextEventData.position = bossHelper[boss].position;
	};

	auto PlayTrack = [](const char * filename)
	{
		func_32BE20((appBaseAddr + 0xCF3700));
		func_32BA90((appBaseAddr + 0xCF3708), filename, 0, 0);
	};

	switch (sessionData.mission)
	{
	case 3:
	{
		if ((eventData.room == bossHelper[BOSS_CERBERUS].room) && (flags[20] == 1))
		{
			PlayTrack(bossHelper[BOSS_CERBERUS].track);
		}
		break;
	}
	case 5:
	{
		if ((eventData.room == bossHelper[BOSS_AGNI_RUDRA].room) && (flags[20] == 1))
		{
			PlayTrack(bossHelper[BOSS_AGNI_RUDRA].track);
		}
		break;
	}
	case 7:
	{
		if (eventData.room == bossHelper[BOSS_VERGIL_1].room)
		{
			PlayTrack(bossHelper[BOSS_VERGIL_1].track);
		}
		break;
	}
	case 9:
	{
		if ((eventData.room == bossHelper[BOSS_NEVAN].room) && (flags[20] == 1))
		{
			PlayTrack(bossHelper[BOSS_NEVAN].track);
		}
		break;
	}
	case 11:
	{
		if ((eventData.room == bossHelper[BOSS_BEOWULF].room) && (flags[20] == 1))
		{
			PlayTrack(bossHelper[BOSS_BEOWULF].track);
		}
		break;
	}
	case 12:
	{
		if ((eventData.room == bossHelper[BOSS_GERYON_PART_1].room) && (flags[20] == 1))
		{
			PlayTrack(bossHelper[BOSS_GERYON_PART_1].track);
			//skipTrack = true;
		}
		else if ((eventData.room == bossHelper[BOSS_GERYON_PART_2].room) && (flags[20] == 2))
		{
			PlayTrack(bossHelper[BOSS_GERYON_PART_2].track);
		}
		break;
	}
	case 13:
	{
		if (eventData.room == bossHelper[BOSS_VERGIL_2].room)
		{
			PlayTrack(bossHelper[BOSS_VERGIL_2].track);
		}
		break;
	}
	case 16:
	{
		if (eventData.room == bossHelper[BOSS_LADY].room)
		{
			PlayTrack(bossHelper[BOSS_LADY].track);
		}
		break;
	}
	case 17:
	{
		if ((eventData.room == bossHelper[BOSS_DOPPELGANGER].room) && (flags[20] == 0))
		{
			PlayTrack(bossHelper[BOSS_DOPPELGANGER].track);
		}
		break;
	}
	case 19:
	{
		if ((eventData.room == bossHelper[BOSS_ARKHAM_PART_1].room) && (flags[20] == 0))
		{
			PlayTrack(bossHelper[BOSS_ARKHAM_PART_1].track);
			//skipTrack = true;
		}
		else if ((eventData.room == bossHelper[BOSS_ARKHAM_PART_2].room) && (flags[20] == 1))
		{
			PlayTrack(bossHelper[BOSS_ARKHAM_PART_2].track);
		}
		break;
	}
	}
}













































































//
//void Main()
//{
//	LogFunction();
//}
//
//void Teleport()
//{
//	LogFunction();
//}
//
//void EnterCustomizeMenu()
//{
//	if constexpr (debug)
//	{
//		LogFunction();
//	}
//}
//
//void LeaveCustomizeMenu();


// EnterCustomizeMenuFromMain
// EnterMainFromCustomizeMenu

// EnterPauseMenuFromMain
// EnterMainFromPauseMenu

// PauseMenuMain
// MainPauseMenu


// CustomizeMain
// CustomizeMenuMain

// MainCustomizeMenu
// MissionStartCustomizeMenu


// MissionStart_EnterCustomizeMenu
// MissionStart_LeaveCustomizeMenu

// Main_EnterPauseMenu
// Main_LeavePauseMenu

// PauseMenu_EnterMain
// PauseMenu_EnterMissionSelectMenu


// MissionStart_CustomizeMenu
// CustomizeMenu_MissionStart

// Main_CustomizeMenu
// Main_PauseMenu

// PauseMenu_












/*
dmc3.exe+23C779 - E8 A220FAFF           - call dmc3.exe+1DE820 Main
dmc3.exe+2134DE - E8 3DB3FCFF           - call dmc3.exe+1DE820 Doppelganger
dmc3.exe+211E83 - E8 98C9FCFF           - call dmc3.exe+1DE820 Bob













dmc3.exe+1BB02D - 48 8B 05 F45DAD00     - mov rax,[dmc3.exe+C90E28] { (01A44800) }
dmc3.exe+1BB034 - 33 F6                 - xor esi,esi
dmc3.exe+1BB036 - 0FB6 8D 88000000      - movzx ecx,byte ptr [rbp+00000088]
dmc3.exe+1BB03D - 8B FE                 - mov edi,esi
dmc3.exe+1BB03F - C7 44 24 6C 0000803F  - mov [rsp+6C],3F800000 { (0) }
dmc3.exe+1BB047 - 48 8B 4C C8 18        - mov rcx,[rax+rcx*8+18]




*/


//bool spawnActors = false;



//extern bool MainLoop_run;



//PrivateStart;



//export bool MainLoop_run = false;





void SetPool()
{
	LogFunction();
	//MainLoop_run = true;
}

void ClearPool()
{
	LogFunction();
	File_dynamicFiles.Clear();
	Actor_actorBaseAddr.Clear();
}


















void Main_CreateMainActor(byte8 * baseAddr)
{
	LogFunction(baseAddr);

	Actor_CreateMainActor(baseAddr);
	Arcade_CreateMainActor(baseAddr);
}

void Customize_CreateMainActor(byte8 * baseAddr)
{
	LogFunction(baseAddr);

	Actor_CreateMainActor(baseAddr);
	Arcade_CreateMainActor(baseAddr);
}




















void CreateMainClone(byte8 * baseAddr)
{
	LogFunction(baseAddr);
	Actor_actorBaseAddr[1] = baseAddr;
}

















static void Actor_StageLoadComplete()
{


	// Adjust style.

	//{
	//	auto & baseAddr1 = System_Actor_actorBaseAddr[ACTOR_ONE];
	//	if (!baseAddr1)
	//	{
	//		goto sect0;
	//	}
	//	auto & style = *(uint32 *)(baseAddr1 + 0x6338);
	//	if ((style == STYLE_DANTE_DOPPELGANGER) && Config.System.Actor.forceSingleActor)
	//	{
	//		style = STYLE_DANTE_TRICKSTER;
	//	}
	//}
	//sect0:




	




	return;


	//return;


	//auto & baseAddr = System_Actor_actorBaseAddr[ACTOR_TWO];
	//if (!baseAddr)
	//{
	//	return;
	//}
	//Cosmetics_Color_ApplyColor(baseAddr, 6, 0);
	//return;




	//HoboBreak();

	//if (Config.Multiplayer.enable)
	//{
	//	return;
	//}
	//auto count = System_Actor_GetActorCount();
	//for (uint8 actor = ACTOR_TWO; actor < count; actor++)
	//{
	//	auto & baseAddr = System_Actor_actorBaseAddr[actor];
	//	if (!baseAddr)
	//	{
	//		continue;
	//	}
	//	auto & isDoppelganger = *(bool *)(baseAddr + 0x11C) = true;
	//	auto & shadow = *(uint8 *)(baseAddr + 0x3A18) = 0;
	//}
}

#pragma endregion

#pragma region Arcade



#pragma endregion








































#pragma endregion

#pragma region Game Events


// @Todo: Private and debug.

//static void DevilForm_Activate(byte8 * baseAddr)
//{
//	LogFunction(baseAddr);
//	auto actor = System_Actor_GetActorId(baseAddr);
//	auto & doppelganger = *(bool *)(baseAddr + 0x6362);
//	//if (actor != ACTOR_ONE)
//	//{
//	//	return;
//	//}
//	//if (doppelganger)
//	//{
//	//	return;
//	//}
//	System_Actor_UpdateFlux(baseAddr, DEVIL_FLUX_START);
//}

//static void DevilForm_Deactivate(byte * baseAddr)
//{
//	LogFunction(baseAddr);
//	auto actor = System_Actor_GetActorId(baseAddr);
//	auto & doppelganger = *(bool *)(baseAddr + 0x6362);
//	//if (actor != ACTOR_ONE)
//	//{
//	//	return;
//	//}
//	//if (doppelganger)
//	//{
//	//	return;
//	//}
//	System_Actor_UpdateFlux(baseAddr, DEVIL_FLUX_END);
//}















// @Todo: Update with ternary operator.

inline void Doppelganger_ToggleForceActorUpdate(bool enable)
{
	LogFunction(enable);
	if (enable)
	{
		Write<byte8>((appBaseAddr + 0x1F83D0), 0xEB);
	}
	else
	{
		Write<byte8>((appBaseAddr + 0x1F83D0), 0x75);
	}
}

// @Todo: Ugh, update.
// @Todo: Debug only.

//static void Doppelganger_Activate(byte * baseAddr)
//{
//	Log("%s %llX", FUNC_NAME, baseAddr);
//
//	uint8 actor = System_Actor_GetActorId(baseAddr);
//	if (actor != ACTOR_ONE)
//	{
//		return;
//	}
//
//
//	Doppelganger_ToggleForceActorUpdate(true);
//
//
//	auto & noColor = Config.Cosmetics.Doppelganger.noColor;
//	auto & baseAddr1 = System_Actor_actorBaseAddr[ACTOR_ONE];
//	auto & baseAddr2 = System_Actor_actorBaseAddr[ACTOR_TWO];
//	if (!baseAddr1 || !baseAddr2)
//	{
//		return;
//	}
//	auto & shadow1 = *(uint32 *)(baseAddr1 + 0x3A18) = (noColor) ? 1 : 0;
//	auto & shadow2 = *(uint32 *)(baseAddr2 + 0x3A18) = (noColor) ? 1 : 0;
//
//
//
//
//
//
//
//
//
//
//
//	//if (!Config.Doppelganger.enableDevilTrigger)
//	//{
//	//	System_Actor_UpdateFlux(baseAddr, DEVIL_FLUX_END);
//	//	return;
//	//}
//	bool devil = *(bool *)(baseAddr + 0x3E9B);
//	//if (devil)
//	//{
//	//	System_Actor_UpdateFlux(baseAddr, DEVIL_FLUX_END);
//	//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//	//uint8 & shadow = *(uint8 *)(actorBaseAddr[ACTOR_TWO] + 0x3A18) = 0;
//
//	*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E6C) = *(uint32 *)(baseAddr + 0x3E6C);
//	*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E70) = *(uint32 *)(baseAddr + 0x3E70);
//	*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E88) = *(uint32 *)(baseAddr + 0x3E88);
//	*(bool   *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E9B) = *(bool   *)(baseAddr + 0x3E9B);
//	uint8 character = *(uint8 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x78);
//	//if (character == CHAR_BOB)
//	//{
//	//	if (devil)
//	//	{
//	//		*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E6C) = DEVIL_BOB_YAMATO;
//	//		*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E70) = DEVIL_BOB_YAMATO;
//	//		*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E88) = DEVIL_BOB_YAMATO;
//	//	}
//	//	else
//	//	{
//	//		*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E6C) = 0;
//	//		*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E70) = 0;
//	//		*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E88) = 0;
//	//	}
//	//}
//	if (character == CHAR_LADY)
//	{
//		*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E6C) = 0;
//		*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E70) = 0;
//		*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E88) = 0;
//		*(bool   *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E9B) = false;
//	}
//	else if (character == CHAR_VERGIL)
//	{
//		uint8 devilForm[] =
//		{
//			DEVIL_VERGIL_YAMATO,
//			DEVIL_VERGIL_BEOWULF,
//			//DEVIL_VERGIL_FORCE_EDGE,
//		};
//		uint8 selectedWeapon = *(uint8 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x6488);
//		if (selectedWeapon > 1)
//		{
//			selectedWeapon = 0;
//		}
//		if (devil)
//		{
//			*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E6C) = devilForm[selectedWeapon];
//			*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E70) = devilForm[selectedWeapon];
//			*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E88) = devilForm[selectedWeapon];
//		}
//		else
//		{
//			*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E6C) = 0;
//			*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E70) = 0;
//			*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E88) = 0;
//		}
//	}
//	if (character != CHAR_LADY)
//	{
//		//System_Actor_UpdateDevilForm(System_Actor_actorBaseAddr[ACTOR_TWO]);
//	}
//}

//static void Doppelganger_Deactivate(byte * baseAddr)
//{
//	Log("%s %llX", FUNC_NAME, baseAddr);
//
//	uint8 actor = System_Actor_GetActorId(baseAddr);
//	if (actor != ACTOR_ONE)
//	{
//		return;
//	}
//
//	Doppelganger_ToggleForceActorUpdate(false);
//
//	if (!Config.Doppelganger.enableDevilTrigger)
//	{
//		*(uint32 *)(baseAddr + 0x3E6C) = 0;
//		*(uint32 *)(baseAddr + 0x3E70) = 0;
//		*(uint32 *)(baseAddr + 0x3E88) = 0;
//		System_Actor_UpdateDevilForm(baseAddr);
//		System_Actor_UpdateFlux(baseAddr, DEVIL_FLUX_END);
//		System_Actor_Relax(baseAddr);
//		return;
//	}
//	bool devil = *(bool *)(baseAddr + 0x3E9B);
//	if (devil)
//	{
//		System_Actor_UpdateFlux(baseAddr, DEVIL_FLUX_START);
//	}
//	*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E6C) = 0;
//	*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E70) = 0;
//	*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E88) = 0;
//	*(bool   *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E9B) = false;
//}









#pragma endregion





#pragma endregion

























































void Main_Customize()
{
	LogFunction();

	auto & mainActorData = *reinterpret_cast<ACTOR_DATA *>(Actor_actorBaseAddr[0]);
	auto & actorData     = *reinterpret_cast<ACTOR_DATA *>(Actor_actorBaseAddr[2]);

	// @Research: Update collisionIndex.
	//mainActorData.position = actorData.position;
	//actorData.position.y = 10500;

	SetMainActor(mainActorData);
}

void Customize_Main()
{
	LogFunction();

	auto & mainActorData = *reinterpret_cast<ACTOR_DATA *>(Actor_actorBaseAddr[0]);
	auto & actorData     = *reinterpret_cast<ACTOR_DATA *>(Actor_actorBaseAddr[2]);

	//actorData.position = mainActorData.position;
	//mainActorData.position.y = 10500;

	//SetMainActor(actorData);
}




















void SkyStarReset(byte8 * baseAddr)
{
	Mobility::SkyStarReset(baseAddr);
}






























void InitSession()
{
	LogFunction();
	Arcade_InitSession();
}

void SetCharacter(byte8 * addr)
{
	LogFunction();
	Arcade_SetCharacter(addr);
}

void SetRoom()
{
	LogFunction();
	Arcade_SetRoom();
	BossRush_SetRoom();
}

void SetNextRoom()
{
	LogFunction();
	BossRush_SetNextRoom();
}

void SetContinueRoom()
{
	LogFunction();
	BossRush_SetContinueRoom();
}

void StageLoadComplete()
{
	LogFunction();
	BossRush_StageLoadComplete();
}

export void Event_Init()
{
	LogFunction();

	{
		constexpr byte8 sect0[] =
		{
			0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc3.exe+212760
		};
		auto func = CreateFunction(InitSession, (appBaseAddr + 0x2432CB), true, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteCall(func.sect0, (appBaseAddr + 0x212760));
		WriteJump((appBaseAddr + 0x2432C6), func.addr);
	}
	{
		constexpr byte8 sect1[] =
		{
			0x48, 0x8B, 0xC8, //mov rcx,rax
		};
		constexpr byte8 sect2[] =
		{
			0x0F, 0xB6, 0x88, 0x65, 0x45, 0x00, 0x00, //movzx ecx,byte ptr [rax+00004565]
		};
		auto func = CreateFunction(SetCharacter, (appBaseAddr + 0x24350B), true, true, 0, sizeof(sect1), sizeof(sect2));
		memcpy(func.sect1, sect1, sizeof(sect1));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteJump((appBaseAddr + 0x243504), func.addr, 2);
	}
	{
		constexpr byte8 sect0[] =
		{
			0x66, 0x89, 0x82, 0x64, 0x01, 0x00, 0x00, //mov [rdx+00000164],ax
		};
		constexpr byte8 sect1[] =
		{
			0x48, 0x8B, 0xCA, //mov rcx,rdx
		};
		auto func = CreateFunction(SetRoom, (appBaseAddr + 0x1AA8CC), true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteJump((appBaseAddr + 0x1AA8C5), func.addr, 2);
	}
	{
		constexpr byte8 sect0[] =
		{
			0x66, 0x89, 0x90, 0x66, 0x01, 0x00, 0x00, //mov [rax+00000166],dx
		};
		constexpr byte8 sect1[] =
		{
			0x48, 0x8B, 0xC8, //mov rcx,rax
		};
		auto func = CreateFunction(SetNextRoom, (appBaseAddr + 0x1A6002), true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteJump((appBaseAddr + 0x1A5FFB), func.addr, 2);
	}
	{
		constexpr byte8 sect0[] =
		{
			0x66, 0x89, 0x81, 0x66, 0x01, 0x00, 0x00, //mov [rcx+00000166],ax
		};
		auto func = CreateFunction(SetContinueRoom, (appBaseAddr + 0x1AA3CC), true, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteJump((appBaseAddr + 0x1AA3C5), func.addr, 2);
	}

	 // @Research: Main event rather.
	{
		constexpr byte8 sect0[] =
		{
			0xC7, 0x47, 0x20, 0x01, 0x00, 0x00, 0x00, //mov [rdi+20],00000001
		};
		auto func = CreateFunction(StageLoadComplete, (appBaseAddr + 0x23D0AB), true, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteJump((appBaseAddr + 0x23D0A4), func.addr, 2);
	}



	{
		constexpr byte8 sect0[] =
		{
			0x48, 0x89, 0x5C, 0x24, 0x08, // mov [rsp+08],rbx
		};		constexpr byte8 sect2[] =
		{
			0x84, 0xC0, // test al,al
			0x75, 0x01, // jne short
			0xC3,       // ret
		};		auto func = CreateFunction(SetTrack, (appBaseAddr + 0x32BA95), true, false, sizeof(sect0), 0, sizeof(sect2));		memcpy(func.sect0, sect0, sizeof(sect0));		memcpy(func.sect2, sect2, sizeof(sect2));		WriteJump((appBaseAddr + 0x32BA90), func.addr);		/*		dmc3.exe+32BA90 - 48 89 5C 24 08 - mov [rsp+08],rbx
		dmc3.exe+32BA95 - 48 89 6C 24 10 - mov [rsp+10],rbp		*/
	}








	// @Audit: Not sure if this shouldn't be part of Media.cpp.
	//{
	//	byte sect0[] =
	//	{
	//		0x48, 0x89, 0x5C, 0x24, 0x08, //mov [rsp+08],rbx
	//	};
	//	byte sect2[] =
	//	{
	//		0x48, 0x85, 0xC0,                                           //test rax,rax
	//		0x74, 0x03,                                                 //je short
	//		0x48, 0x8B, 0xD0,                                           //mov rdx,rax
	//		0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rax,&mediaError
	//		0x8B, 0x00,                                                 //mov eax,[rax]
	//		0x3D, 0x00, 0x00, 0x00, 0x00,                               //cmp eax,MEDIA_SKIP_TRACK
	//		0x75, 0x01,                                                 //jne short
	//		0xC3,                                                       //ret
	//	};
	//	FUNC func = CreateFunction(SetTrack, (appBaseAddr + 0x32BA95), true, false, sizeof(sect0), 0, sizeof(sect2));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	memcpy(func.sect2, sect2, sizeof(sect2));
	//	*(dword **)(func.sect2 + 0xA) = &mediaError;
	//	*(dword *)(func.sect2 + 0x15) = MEDIA_SKIP_TRACK;
	//	//WriteJump((appBaseAddr + 0x32BA90), func.addr);
	//}






























	// Sky Star Reset
	{
		constexpr byte8 sect0[] =
		{
			0x88, 0x8B, 0x5D, 0x63, 0x00, 0x00, //mov [rbx+0000635D],cl
		};
		constexpr byte8 sect1[] =
		{
			0x48, 0x8B, 0xCB, //mov rcx,rbx
		};
		auto func = CreateFunction(SkyStarReset, 0, true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteCall((appBaseAddr + 0x1DFEAE), func.addr, 1);
		/*
		dmc3.exe+1DFEAE - 88 8B 5D630000 - mov [rbx+0000635D],cl
		*/
	}
	{
		constexpr byte8 sect0[] =
		{
			0x88, 0x8B, 0x5D, 0x63, 0x00, 0x00, //mov [rbx+0000635D],cl
		};
		constexpr byte8 sect1[] =
		{
			0x48, 0x8B, 0xCB, //mov rcx,rbx
		};
		auto func = CreateFunction(SkyStarReset, 0, true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteCall((appBaseAddr + 0x1DFFB6), func.addr, 1);
		/*
		dmc3.exe+1DFFB6 - 88 8B 5D630000 - mov [rbx+0000635D],cl
		*/
	}
	{
		constexpr byte8 sect0[] =
		{
			0x41, 0x88, 0x89, 0x5D, 0x63, 0x00, 0x00, //mov [r9+0000635D],cl
		};
		constexpr byte8 sect1[] =
		{
			0x49, 0x8B, 0xC9, //mov rcx,r9
		};
		auto func = CreateFunction(SkyStarReset, 0, true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteCall((appBaseAddr + 0x1E07A2), func.addr, 2);
		/*
		dmc3.exe+1E07A2 - 41 88 89 5D630000 - mov [r9+0000635D],cl
		*/
	}
	{
		constexpr byte8 sect0[] =
		{
			0x88, 0x8B, 0x5D, 0x63, 0x00, 0x00, //mov [rbx+0000635D],cl
		};
		constexpr byte8 sect1[] =
		{
			0x48, 0x8B, 0xCB, //mov rcx,rbx
		};
		auto func = CreateFunction(SkyStarReset, 0, true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteCall((appBaseAddr + 0x1E0D81), func.addr, 1);
		/*
		dmc3.exe+1E0D81 - 88 8B 5D630000 - mov [rbx+0000635D],cl
		*/
	}
	{
		constexpr byte8 sect0[] =
		{
			0x41, 0x88, 0x88, 0x5D, 0x63, 0x00, 0x00, //mov [r8+0000635D],cl
		};
		constexpr byte8 sect1[] =
		{
			0x49, 0x8B, 0xC8, //mov rcx,r8
		};
		auto func = CreateFunction(SkyStarReset, 0, true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteCall((appBaseAddr + 0x1E0F64), func.addr, 2);
		/*
		dmc3.exe+1E0F64 - 41 88 88 5D630000 - mov [r8+0000635D],cl
		*/
	}
	{
		constexpr byte8 sect0[] =
		{
			0x41, 0x88, 0x88, 0x5D, 0x63, 0x00, 0x00, //mov [r8+0000635D],cl
		};
		constexpr byte8 sect1[] =
		{
			0x49, 0x8B, 0xC8, //mov rcx,r8
		};
		auto func = CreateFunction(SkyStarReset, 0, true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteCall((appBaseAddr + 0x1E0FBD), func.addr, 2);
		/*
		dmc3.exe+1E0FBD - 41 88 88 5D630000 - mov [r8+0000635D],cl
		*/
	}
	{
		constexpr byte8 sect0[] =
		{
			0x88, 0x8B, 0x5D, 0x63, 0x00, 0x00, //mov [rbx+0000635D],cl
		};
		constexpr byte8 sect1[] =
		{
			0x48, 0x8B, 0xCB, //mov rcx,rbx
		};
		auto func = CreateFunction(SkyStarReset, 0, true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteCall((appBaseAddr + 0x1E16D2), func.addr, 1);
		/*
		dmc3.exe+1E16D2 - 88 8B 5D630000 - mov [rbx+0000635D],cl
		*/
	}
	{
		constexpr byte8 sect0[] =
		{
			0x88, 0x83, 0x5D, 0x63, 0x00, 0x00, //mov [rbx+0000635D],al
		};
		constexpr byte8 sect1[] =
		{
			0x48, 0x8B, 0xCB, //mov rcx,rbx
		};
		auto func = CreateFunction(SkyStarReset, 0, true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteCall((appBaseAddr + 0x1E66AC), func.addr, 1);
		/*
		dmc3.exe+1E66AC - 88 83 5D630000 - mov [rbx+0000635D],al
		*/
	}






























	{
		constexpr byte8 sect0[] =
		{
			0xC7, 0x41, 0x20, 0x09, 0x00, 0x00, 0x00, // mov [rcx+20],00000009
		};
		auto func = CreateFunction(Main_Customize, (appBaseAddr + 0x23B21D), true, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteJump((appBaseAddr + 0x23B216), func.addr, 2);
		/*
		dmc3.exe+23B216 - C7 41 20 09000000 - mov [rcx+20],00000009
		dmc3.exe+23B21D - C6 41 24 00       - mov byte ptr [rcx+24],00
		*/
	}

	{
		constexpr byte8 sect0[] =
		{
			0xC7, 0x47, 0x20, 0x01, 0x00, 0x00, 0x00, // mov [rdi+20],00000001
		};
		auto func = CreateFunction(Customize_Main, (appBaseAddr + 0x23BB71), true, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteJump((appBaseAddr + 0x23BB6A), func.addr, 2);
		/*
		dmc3.exe+23BB6A - C7 47 20 01000000 - mov [rdi+20],00000001
		dmc3.exe+23BB71 - BA 00000080       - mov edx,80000000
		*/
	}





	{
		constexpr byte8 sect0[] =
		{
			0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc3.exe+1DE820
		};
		constexpr byte8 sect1[] =
		{
			0x48, 0x8B, 0xC8, //mov rcx,rax
		};
		auto func = CreateFunction(Main_CreateMainActor, (appBaseAddr + 0x23C77E), true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteCall(func.sect0, (appBaseAddr + 0x1DE820));
		WriteJump((appBaseAddr + 0x23C779), func.addr);
		/*
		dmc3.exe+23C779 - E8 A220FAFF       - call dmc3.exe+1DE820
		dmc3.exe+23C77E - 48 89 87 B82C0000 - mov [rdi+00002CB8],rax
		*/
	}



	{
		constexpr byte8 sect0[] =
		{
			0xE8, 0x00, 0x00, 0x00, 0x00, // call dmc3.exe+1DE820
		};
		constexpr byte8 sect1[] =
		{
			0x48, 0x8B, 0xC8, // mov rcx,rax
		};
		auto func = CreateFunction(Customize_CreateMainActor, (appBaseAddr + 0x23B7B8), true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteCall(func.sect0, (appBaseAddr + 0x1DE820));
		WriteJump((appBaseAddr + 0x23B7B3), func.addr);
		/*
		dmc3.exe+23B7B3 - E8 6830FAFF       - call dmc3.exe+1DE820
		dmc3.exe+23B7B8 - 48 89 87 B82C0000 - mov [rdi+00002CB8],rax
		*/
	}

















































	{
		constexpr byte8 sect0[] =
		{
			0x48, 0x89, 0x15, 0x00, 0x00, 0x00, 0x00, //mov [dmc3.exe+C90E28],rdx
		};
		auto func = CreateFunction(SetPool, (appBaseAddr + 0x23E69F), true, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteAddress(func.sect0, (appBaseAddr + 0xC90E28), 7);
		WriteJump((appBaseAddr + 0x23E698), func.addr, 2);
		/*
		dmc3.exe+23E698 - 48 89 15 8927A500 - mov [dmc3.exe+C90E28],rdx
		dmc3.exe+23E69F - 48 8D 83 D06A0000 - lea rax,[rbx+00006AD0]
		*/
	}
	{
		constexpr byte8 sect0[] =
		{
			0x48, 0x89, 0x0D, 0x00, 0x00, 0x00, 0x00, //mov [dmc3.exe+C90E28],rcx
		};
		auto func = CreateFunction(ClearPool, (appBaseAddr + 0x23B39A), true, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteAddress(func.sect0, (appBaseAddr + 0xC90E28), 7);
		WriteJump((appBaseAddr + 0x23B393), func.addr, 2);
		/*
		dmc3.exe+23B393 - 48 89 0D 8E5AA500 - mov [dmc3.exe+C90E28],rcx
		dmc3.exe+23B39A - 48 89 0D 975AA500 - mov [dmc3.exe+C90E38],rcx
		*/
	}


	{
		byte8 sect0[] =
		{
			0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc3.exe+1DE820
		};
		byte8 sect1[] =
		{
			0x48, 0x8B, 0xC8, //mov rcx,rax
		};
		auto func = CreateFunction(CreateMainClone, (appBaseAddr + 0x2134E3), true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteCall(func.sect0, (appBaseAddr + 0x1DE820));
		WriteJump((appBaseAddr + 0x2134DE), func.addr);
		/*
		dmc3.exe+2134DE - E8 3DB3FCFF       - call dmc3.exe+1DE820
		dmc3.exe+2134E3 - 48 89 86 78640000 - mov [rsi+00006478],rax
		*/
	}
	{
		byte8 sect0[] =
		{
			0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc3.exe+1DE820
		};
		byte8 sect1[] =
		{
			0x48, 0x8B, 0xC8, //mov rcx,rax
		};
		auto func = CreateFunction(CreateMainClone, (appBaseAddr + 0x211E88), true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteCall(func.sect0, (appBaseAddr + 0x1DE820));
		WriteJump((appBaseAddr + 0x211E83), func.addr);
		/*
		dmc3.exe+211E83 - E8 98C9FCFF       - call dmc3.exe+1DE820
		dmc3.exe+211E88 - 48 89 83 78640000 - mov [rbx+00006478],rax
		*/
	}




































	/*
dmc3.exe+23C779 - E8 A220FAFF           - call dmc3.exe+1DE820 Main
dmc3.exe+2134DE - E8 3DB3FCFF           - call dmc3.exe+1DE820 Doppelganger
dmc3.exe+211E83 - E8 98C9FCFF           - call dmc3.exe+1DE820 Bob
	*/






























	#pragma region System Events












	#pragma endregion
	#pragma region Game Events
	//{
	//	FUNC func = CreateFunction(DevilForm_Activate, (appBaseAddr + 0x1E78B4));
	//	WriteJump((appBaseAddr + 0x1E78AF), func.addr);
	//}
	//{
	//	FUNC func = CreateFunction(DevilForm_Deactivate, (appBaseAddr + 0x1E78EB));
	//	WriteJump((appBaseAddr + 0x1E78E6), func.addr);
	//}
	//{
	//	byte sect0[] =
	//	{
	//		0x50, //push rax
	//	};
	//	byte sect1[] =
	//	{
	//		0x48, 0x8B, 0xCF, //mov rcx,rdi
	//	};
	//	byte sect2[] =
	//	{
	//		0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rax,&Config.Doppelganger.enable
	//		0x8A, 0x00,                                                 //mov al,[rax]
	//		0x84, 0xC0,                                                 //test al,al
	//		0x74, 0x06,                                                 //je short
	//		0x58,                                                       //pop rax
	//		0xE9, 0x00, 0x00, 0x00, 0x00,                               //jmp dmc3.exe+1E930E
	//		0x58,                                                       //pop rax
	//		0x80, 0xBF, 0x9B, 0x3E, 0x00, 0x00, 0x01,                   //cmp byte ptr [rdi+00003E9B],01
	//		0x0F, 0x85, 0x00, 0x00, 0x00, 0x00,                         //jne dmc3.exe+1E930E
	//		0xE9, 0x00, 0x00, 0x00, 0x00,                               //jmp dmc3.exe+1E92EA
	//	};
	//	// @Todo: Update CreateFunction. Add noReturn.
	//	FUNC func = CreateFunction(Doppelganger_Activate, 0, true, false, sizeof(sect0), sizeof(sect1), sizeof(sect2));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	memcpy(func.sect1, sect1, sizeof(sect1));
	//	memcpy(func.sect2, sect2, sizeof(sect2));
	//	*(bool **)(func.sect2 + 2) = &Config.Doppelganger.enable;
	//	WriteAddress((func.sect2 + 0x11), (appBaseAddr + 0x1E930E), 5);
	//	WriteAddress((func.sect2 + 0x1E), (appBaseAddr + 0x1E930E), 6);
	//	WriteAddress((func.sect2 + 0x24), (appBaseAddr + 0x1E92EA), 5);
	//	WriteJump((appBaseAddr + 0x1E92E1), func.addr, 2);
	//}
	//{
	//	byte sect0[] =
	//	{
	//		0x50, //push rax
	//	};
	//	byte sect1[] =
	//	{
	//		0x48, 0x8B, 0xCB, //mov rcx,rbx
	//	};
	//	byte sect2[] =
	//	{
	//		0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rax,&Config.Doppelganger.enable
	//		0x8A, 0x00,                                                 //mov al,[rax]
	//		0x84, 0xC0,                                                 //test al,al
	//		0x74, 0x06,                                                 //je short
	//		0x58,                                                       //pop rax
	//		0xE9, 0x00, 0x00, 0x00, 0x00,                               //jmp dmc3.exe+1E2B63
	//		0x58,                                                       //pop rax
	//		0x80, 0xBB, 0x9B, 0x3E, 0x00, 0x00, 0x00,                   //cmp byte ptr [rbx+00003E9B],00
	//		0x0F, 0x85, 0x00, 0x00, 0x00, 0x00,                         //jne dmc3.exe+1E2B63
	//		0xE9, 0x00, 0x00, 0x00, 0x00,                               //jmp dmc3.exe+1E2B2D
	//	};
	//	FUNC func = CreateFunction(Doppelganger_Deactivate, 0, true, false, sizeof(sect0), sizeof(sect1), sizeof(sect2));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	memcpy(func.sect1, sect1, sizeof(sect1));
	//	memcpy(func.sect2, sect2, sizeof(sect2));
	//	*(bool **)(func.sect2 + 2) = &Config.Doppelganger.enable;
	//	WriteAddress((func.sect2 + 0x11), (appBaseAddr + 0x1E2B63), 5);
	//	WriteAddress((func.sect2 + 0x1E), (appBaseAddr + 0x1E2B63), 6);
	//	WriteAddress((func.sect2 + 0x24), (appBaseAddr + 0x1E2B2D), 5);
	//	WriteJump((appBaseAddr + 0x1E2B24), func.addr, 2);
	//}
	//CreateThread(0, 4096, Doppelganger_Watchdog, 0, 0, 0);
	#pragma endregion
}











export void Event_ToggleSkipIntro(bool enable)
{
	LogFunction(enable);
	WriteAddress((appBaseAddr + 0x2383F2), (enable) ? (appBaseAddr + 0x2383F8) : (appBaseAddr + 0x238527), 6); // Skip Message
	WriteAddress((appBaseAddr + 0x241789), (enable) ? (appBaseAddr + 0x24178B) : (appBaseAddr + 0x2417A6), 2); // Skip Video
	Write<uint8>((appBaseAddr + 0x238704), (enable) ? 0 : 1); // Hide Rebellion
	// Disable Video Timer
	{
		auto dest = (appBaseAddr + 0x243531);
		if (enable)
		{
			vp_memset(dest, 0x90, 2);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0xFF, 0xC8, //dec eax
			};
			vp_memcpy(dest, buffer, sizeof(buffer));
		}
	}
}

export void Event_ToggleSkipCutscenes(bool enable)
{
	LogFunction(enable);
	WriteAddress((appBaseAddr + 0x238CCA), (enable) ? (appBaseAddr + 0x238CD0) : (appBaseAddr + 0x238E62), 6);
	WriteAddress((appBaseAddr + 0x238CD8), (enable) ? (appBaseAddr + 0x238CDE) : (appBaseAddr + 0x238E62), 6);
	WriteAddress((appBaseAddr + 0x238CE3), (enable) ? (appBaseAddr + 0x238CE9) : (appBaseAddr + 0x238E62), 6);
}






#ifdef __GARBAGE__

// @Reaseach: Probably no longer needed.

void ActorInitComplete(byte8 * baseAddr)
{
	LogFunction(baseAddr);

	//if (baseAddr == System_Actor_actorBaseAddr[0])
	//{
	//	return;
	//}
	//if (baseAddr == System_Actor_actorBaseAddr[1])
	//{
	//	return;
	//}

	//auto & actorData = *(ACTOR_DATA *)baseAddr;
	//actorData.shadow = 1;
	//actorData.collisionIndex = 1;



	auto & actorData = *reinterpret_cast<ACTOR_DATA *>(baseAddr);
	//actorData.collisionIndex = 1;
	//actorData.newButtonMask = 0xFFFF


	//actorData.newAirStingerCount = 1;


	{
		byte8 sect0[] =
		{
			0x66, 0xC7, 0x43, 0x08, 0x01, 0x00, //mov word ptr [rbx+08],0001
		};
		byte8 sect1[] =
		{
			0x48, 0x8B, 0xCB, //mov rcx,rbx
		};
		auto func = CreateFunction(ActorInitComplete, (appBaseAddr + 0x1F7D87), true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteJump((appBaseAddr + 0x1F7D81), func.addr, 1);
		/*
		dmc3.exe+1F7D81 - 66 C7 43 08 0100 - mov word ptr [rbx+08],0001
		dmc3.exe+1F7D87 - 48 8B 5C 24 58   - mov rbx,[rsp+58]
		*/
	}


}


#endif




















#endif
