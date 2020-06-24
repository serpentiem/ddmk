#ifndef __MODULE_EVENT__
#define __MODULE_EVENT__

module;
#include "../Core/Core.h"

#include "ActorData.h"
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

void Main()
{
	LogFunction();
}

void Teleport()
{
	LogFunction();
}

void EnterCustomizeMenu()
{
	if constexpr (debug)
	{
		LogFunction();
	}
}

void LeaveCustomizeMenu();


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

//PrivateEnd;













#pragma region FUCK




void func()
{















}















//CRITICAL_SECTION Doppelganger_critSectWatchdog;



#pragma region System Events

#pragma region Actor














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

	//if (Config.Game.Multiplayer.enable)
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

static void Arcade_InitSession()
{
	LogFunctionStart();

	// @Todo: Auto and specifiy VARS.

	// @Todo: Create SESSION_DATA struct.


	byte8 * addr = (appBaseAddr + 0xC8F250);
	uint32  & mission            = *(uint32  *)(addr        );
	uint32  & mode               = *(uint32  *)(addr + 0xC  );
	bool    & oneHitKill         = *(bool    *)(addr + 0x10 );
	bool    & enableTutorial     = *(bool    *)(addr + 0x12 );
	bool    & useGoldOrb         = *(bool    *)(addr + 0x13 );
	bool    & bloodyPalace       = *(bool    *)(addr + 0x1C );
	uint8   & goldOrbCount       = *(uint8   *)(addr + 0x35 );
	bool    * unlock             =  (bool    *)(addr + 0x46 );
	uint8   * equipment          =  (uint8   *)(addr + 0x84 );
	uint8   & costume            = *(uint8   *)(addr + 0xD0 );
	bool    & unlockDevilTrigger = *(bool    *)(addr + 0xD1 );
	float32 & hitPoints          = *(float32 *)(addr + 0xD4 );
	float32 & magicPoints        = *(float32 *)(addr + 0xD8 );
	uint32  & style              = *(uint32  *)(addr + 0xDC );
	uint32  * styleLevel         =  (uint32  *)(addr + 0xE0 );
	float32 * styleExperience    =  (float32 *)(addr + 0xF8 );
	uint32  * expertise          =  (uint32  *)(addr + 0x110);

	mission = Config.Arcade.mission;

	//mission = 17;



	// @Todo: Use map instead.
	//ModeStart:
	{
		if ((Config.Arcade.mission == 0) || (Config.Arcade.mission == 21))
		{
			goto ModeEnd;
		}
		//if (Game_Arcade_modeIndex == 5)
		//{
		//	mode = MODE_HARD;
		//	oneHitKill = true;
		//}
		//else
		{
			mode = Config.Arcade.mode;
		}
	}
	ModeEnd:

	enableTutorial = false;
	useGoldOrb = true;

	if (Config.Arcade.mission == 21)
	{
		bloodyPalace = true;
	}

	goldOrbCount = 3;

	//memset(unlock, true, 14);

	if (Config.Arcade.character == CHAR_DANTE)
	{
		vp_memcpy(equipment, Config.Arcade.weapon, 4);
	}



	costume = Config.Arcade.costume;

	unlockDevilTrigger = true;

	hitPoints = Config.Arcade.hitPoints;
	magicPoints = Config.Arcade.magicPoints;

	if (Config.Arcade.character == CHAR_DANTE)
	{
		if ((Config.Arcade.style == STYLE_DANTE_DOPPELGANGER) && Config.System.Actor.forceSingleActor)
		{
			style = STYLE_DANTE_TRICKSTER;
		}
		else
		{
			style = Config.Arcade.style;
		}
	}



	
	memset(styleLevel, 0, (MAX_STYLE * 4));
	//for (uint8 styleId = 0; styleId < 4; styleId++)
	//{
	//	styleLevel[styleId] = 2;
	//}

	styleLevel[0] = 2;
	styleLevel[1] = 2;
	styleLevel[2] = 2;
	styleLevel[3] = 2;





	





	memset(styleExperience, 0, (MAX_STYLE * 4));

	//memset(expertise, 0xFFFFFFFF, 32);
	//memset(expertise, 0xFFFFFFFF, 32);

	memset(expertise, 0xFF, (8 * 4));




	uint32 & controllerMagic = *(uint32 *)(appBaseAddr + 0x553000);

	controllerMagic = 0;




	LogFunctionEnd();
}

static void Arcade_SetCharacter(byte8 * addr)
{
	LogFunctionStart();
	uint8 & character = *(uint8 *)(addr + 0x4565);
	character = Config.Arcade.character;
	LogFunctionEnd();
}

static void Arcade_SetRoom()
{
	LogFunctionStart();


	// @Todo: Use EVENT_DATA instead.

	VARS vars = {};
	if (!vars.init)
	{
		return;
	}
	uint32 & room         = *vars.room;
	uint32 & position     = *vars.position;
	uint16 & nextRoom     = *vars.nextRoom;
	uint16 & nextPosition = *vars.nextPosition;
	byte32 * flags        = vars.flags;
	uint32 & mission      = *vars.mission;

	if (!Config.Arcade.ignoreRoom)
	{
		nextRoom = static_cast<uint16>(Config.Arcade.room);
	}
	if (!Config.Arcade.ignorePosition)
	{
		nextPosition = static_cast<uint16>(Config.Arcade.position);
	}
	if (mission == 21)
	{

		// @Todo: constexpr helper.

		struct DPS
		{
			uint16 room;
			uint16 position;
		};

		// @Todo: Ugh, constexpr please.

		DPS var[] =
		{
			{ 423, 0 }, // floor 1
			{ 424, 0 }, // floor 2
			{ 425, 0 }, // floor 3
			{ 426, 0 }, // floor 4
			{ 427, 0 }, // floor 5
			{ 428, 0 }, // floor 6
			{ 429, 0 }, // floor 7
			{ 430, 0 }, // floor 8
			{ 431, 0 }, // floor 9
			{ 432, 0 }, // floor 10
			{ 433, 0 }, // cerberus
			{ 434, 0 }, // gigapede
			{ 435, 0 }, // agni rudra
			{ 436, 0 }, // nevan
			{ 437, 0 }, // beowulf
			{ 438, 2 }, // geryon
			{ 439, 0 }, // doppelganger
			{ 440, 0 }, // heart of leviathan
			{ 441, 0 }, // damned chessmen
			{ 442, 0 }, // vergil 1
			{ 443, 0 }, // vergil 2
			{ 444, 0 }, // vergil 3
			{ 445, 2 }, // lady
			{ 446, 0 }, // arkham
			{ 422, 0 }, // jester 1
			{ 448, 0 }, // jester 2
			{ 449, 0 }, // jester 3
		};
		nextRoom     = var[Config.Arcade.floor].room;
		nextPosition = var[Config.Arcade.floor].position;
	}
	LogFunctionEnd();
}

#pragma endregion

#pragma region BossRush

static void BossRush_SetRoom()
{
	LogFunctionStart();

	VARS vars = {};
	if (!vars.init)
	{
		return;
	}
	uint32 & room         = *vars.room;
	uint32 & position     = *vars.position;
	uint16 & nextRoom     = *vars.nextRoom;
	uint16 & nextPosition = *vars.nextPosition;
	byte32 * flags        = vars.flags;
	uint32 & mission      = *vars.mission;

	switch (mission)
	{
	case 3:
		if (nextRoom == ROOM_START_3)
		{
			nextRoom     = ROOM_CERBERUS;
			nextPosition = POSITION_CERBERUS;
			flags[20] = 1;
		}
		break;
	case 4:
		if (nextRoom == ROOM_START_4)
		{
			nextRoom     = ROOM_GIGAPEDE;
			nextPosition = POSITION_GIGAPEDE;
		}
		break;
	case 5:
		if (nextRoom == ROOM_START_5)
		{
			if (!Config.Game.BossRush.Mission5.skipJester)
			{
				nextRoom     = ROOM_JESTER_1;
				nextPosition = POSITION_JESTER_1;
			}
			else
			{
				nextRoom     = ROOM_AGNI_RUDRA;
				nextPosition = POSITION_AGNI_RUDRA;
				flags[20] = 1;
			}
		}
		break;
	case 7:
		if (nextRoom == ROOM_START_7)
		{
			nextRoom     = ROOM_VERGIL_1;
			nextPosition = POSITION_VERGIL_1;
		}
		break;
	case 8:
		if (nextRoom == ROOM_START_8)
		{
			nextRoom     = ROOM_LEVIATHAN;
			nextPosition = POSITION_LEVIATHAN;
			byte8 * addr = *(byte8 **)(appBaseAddr + 0xC90E30);
			if (!addr)
			{
				break;
			}
			*(uint8 *)(addr + 0x6A) = 1;
			addr = *(byte8 **)(appBaseAddr + 0xCA8918); // wrong, should be dmc3.exe+C90E10.
			if (!addr)
			{
				break;
			}
			addr = *(byte8 **)(addr + 0x60);
			if (!addr)
			{
				break;
			}
			*(byte8 *)(addr + 0x7DF) = 0x40;
		}
		break;
	case 9:
		if (nextRoom == ROOM_START_9)
		{
			nextRoom     = ROOM_NEVAN;
			nextPosition = POSITION_NEVAN;
			flags[20] = 1;
		}
		break;
	case 11:
		if (nextRoom == ROOM_START_11)
		{
			nextRoom     = ROOM_BEOWULF;
			nextPosition = POSITION_BEOWULF;
			flags[20] = 1;
		}
		break;
	case 12:
		if (nextRoom == ROOM_START_12)
		{
			if (!Config.Game.BossRush.Mission12.skipJester)
			{
				nextRoom     = ROOM_JESTER_2;
				nextPosition = POSITION_JESTER_2;
			}
			else if (!Config.Game.BossRush.Mission12.skipGeryonBridgeBattle)
			{
				nextRoom     = ROOM_GERYON;
				nextPosition = POSITION_GERYON_BRIDGE;
				flags[20] = 1;
			}
			else
			{
				nextRoom     = ROOM_GERYON;
				nextPosition = POSITION_GERYON_GROUND;
				flags[20] = 2;
			}
		}
		break;
	case 13:
		if (nextRoom == ROOM_START_13)
		{
			nextRoom     = ROOM_VERGIL_2;
			nextPosition = POSITION_VERGIL_2;
		}
		break;
	case 16:
		if (nextRoom == ROOM_START_16)
		{
			nextRoom     = ROOM_LADY;
			nextPosition = POSITION_LADY;
			flags[20] = 1;
		}
		break;
	case 17:
		if (nextRoom == ROOM_START_17)
		{
			if (!Config.Game.BossRush.Mission17.skipJester)
			{
				nextRoom     = ROOM_JESTER_3;
				nextPosition = POSITION_JESTER_3;
			}
			else
			{
				nextRoom     = ROOM_DOPPELGANGER;
				nextPosition = POSITION_DOPPELGANGER;
			}
		}
		break;
	case 18:
		if (nextRoom == ROOM_START_18)
		{
			nextRoom     = ROOM_TAIZAI_REBORN;
			nextPosition = POSITION_TAIZAI_REBORN;
		}
		break;
	case 19:
		if (nextRoom == ROOM_START_19)
		{
			nextRoom     = ROOM_ARKHAM;
			nextPosition = POSITION_ARKHAM;
			if (Config.Game.BossRush.Mission19.skipFirstPart)
			{
				flags[20] = 1;
			}
		}
		break;
	}

	LogFunctionEnd();
}

static void BossRush_SetNextRoom()
{
	LogFunctionStart();

	VARS vars = {};
	if (!vars.init)
	{
		return;
	}
	uint32 & room         = *vars.room;
	uint32 & position     = *vars.position;
	uint16 & nextRoom     = *vars.nextRoom;
	uint16 & nextPosition = *vars.nextPosition;
	byte32 * flags        = vars.flags;
	uint32 & mission      = *vars.mission;

	switch (mission)
	{
	case 5:
		if (room == ROOM_JESTER_1)
		{
			nextRoom     = ROOM_AGNI_RUDRA;
			nextPosition = POSITION_AGNI_RUDRA;
			flags[20] = 1;
		}
		break;
	case 12:
		if (room == ROOM_JESTER_2)
		{
			if (!Config.Game.BossRush.Mission12.skipGeryonBridgeBattle)
			{
				nextRoom     = ROOM_GERYON;
				nextPosition = POSITION_GERYON_BRIDGE;
				flags[20] = 1;
			}
			else
			{
				nextRoom     = ROOM_GERYON;
				nextPosition = POSITION_GERYON_GROUND;
				flags[20] = 2;
			}
		}
		break;
	case 17:
		if (room == ROOM_JESTER_3)
		{
			nextRoom     = ROOM_DOPPELGANGER;
			nextPosition = POSITION_DOPPELGANGER;
		}
		break;
	case 18:
		switch (room)
		{
		case ROOM_TAIZAI_REBORN:
		{
			nextRoom     = ROOM_CERBERUS_REBORN;
			nextPosition = POSITION_CERBERUS_REBORN;
			break;
		}
		case ROOM_CERBERUS_REBORN:
			nextRoom     = ROOM_GIGAPEDE_REBORN;
			nextPosition = POSITION_GIGAPEDE_REBORN;
			break;
		case ROOM_GIGAPEDE_REBORN:
			nextRoom     = ROOM_AGNI_RUDRA_REBORN;
			nextPosition = POSITION_AGNI_RUDRA_REBORN;
			break;
		case ROOM_AGNI_RUDRA_REBORN:
			nextRoom     = ROOM_LEVIATHAN_REBORN;
			nextPosition = POSITION_LEVIATHAN_REBORN;
			break;
		case ROOM_LEVIATHAN_REBORN:
			nextRoom     = ROOM_NEVAN_REBORN;
			nextPosition = POSITION_NEVAN_REBORN;
			break;
		case ROOM_NEVAN_REBORN:
			nextRoom     = ROOM_BEOWULF_REBORN;
			nextPosition = POSITION_BEOWULF_REBORN;
			break;
		case ROOM_BEOWULF_REBORN:
			nextRoom     = ROOM_GERYON_REBORN;
			nextPosition = POSITION_GERYON_REBORN;
			break;
		case ROOM_GERYON_REBORN:
			nextRoom     = ROOM_DOPPELGANGER_REBORN;
			nextPosition = POSITION_DOPPELGANGER_REBORN;
			break;
		case ROOM_DOPPELGANGER_REBORN:
			nextRoom     = 403;
			nextPosition = 2;
			flags[14] = 0x3FE;
			flags[15] = 0x1FF;
			break;
		}
		break;
	}

	LogFunctionEnd();
}

static void BossRush_SetContinueRoom()
{
	LogFunctionStart();

	VARS vars = {};
	if (!vars.init)
	{
		return;
	}
	uint32 & room         = *vars.room;
	uint32 & position     = *vars.position;
	uint16 & nextRoom     = *vars.nextRoom;
	uint16 & nextPosition = *vars.nextPosition;
	byte32 * flags        = vars.flags;
	uint32 & mission      = *vars.mission;

	nextRoom     = (uint16)room;
	nextPosition = (uint16)position;

	LogFunctionEnd();
}

static const char * BossRush_SetTrack(const char * path)
{
	//LogFunctionStart();

	//VARS vars = {};
	//if (!vars.init)
	//{
	//	return 0;
	//}
	//uint32 & room         = *vars.room;
	//uint32 & position     = *vars.position;
	//uint16 & nextRoom     = *vars.nextRoom;
	//uint16 & nextPosition = *vars.nextPosition;
	//byte32 * flags        = vars.flags;
	//uint32 & mission      = *vars.mission;

	//switch (mission)
	//{
	//case 5:
	//	if (_stricmp(path, "afs/sound/Battle_03.adx") == 0)
	//	{
	//		mediaError = MEDIA_SKIP_TRACK;
	//		return 0;
	//	}
	//	if (nextRoom == ROOM_AGNI_RUDRA)
	//	{
	//		if (_stricmp(path, TRACK_JESTER_1) == 0)
	//		{
	//			mediaError = MEDIA_SKIP_TRACK;
	//			return 0;
	//		}
	//	}
	//	break;
	//case 12:
	//	if (nextRoom == ROOM_GERYON)
	//	{
	//		if (_stricmp(path, TRACK_JESTER_2) == 0)
	//		{
	//			mediaError = MEDIA_SKIP_TRACK;
	//			return 0;
	//		}
	//	}
	//	break;
	//case 17:
	//	if (nextRoom == ROOM_DOPPELGANGER)
	//	{
	//		if (_stricmp(path, TRACK_JESTER_3) == 0)
	//		{
	//			mediaError = MEDIA_SKIP_TRACK;
	//			return 0;
	//		}
	//	}
	//	break;
	//}

	//LogFunctionEnd();

	return 0;
}

static void BossRush_StageLoadComplete()
{
	//LogFunctionStart();

	//VARS vars = {};
	//if (!vars.init)
	//{
	//	return;
	//}
	//uint32 & room         = *vars.room;
	//uint32 & position     = *vars.position;
	//uint16 & nextRoom     = *vars.nextRoom;
	//uint16 & nextPosition = *vars.nextPosition;
	//byte32 * flags        = vars.flags;
	//uint32 & mission      = *vars.mission;

	//switch (mission)
	//{
	//case 3:
	//	if ((room == ROOM_CERBERUS) && (flags[20] == 1))
	//	{
	//		PlayTrack(TRACK_CERBERUS);
	//	}
	//	break;
	//case 5:
	//	if ((room == ROOM_AGNI_RUDRA) && (flags[20] == 1))
	//	{
	//		PlayTrack(TRACK_AGNI_RUDRA);
	//	}
	//	break;
	//case 7:
	//	if (room == ROOM_VERGIL_1)
	//	{
	//		PlayTrack(TRACK_VERGIL_1);
	//	}
	//	break;
	//case 9:
	//	if ((room == ROOM_NEVAN) && (flags[20] == 1))
	//	{
	//		PlayTrack(TRACK_NEVAN);
	//	}
	//	break;
	//case 11:
	//	if ((room == ROOM_BEOWULF) && (flags[20] == 1))
	//	{
	//		PlayTrack(TRACK_BEOWULF);
	//	}
	//	break;
	//case 12:
	//	if (room == ROOM_GERYON)
	//	{
	//		if (flags[20] == 1)
	//		{
	//			PlayTrack(TRACK_GERYON);
	//			mediaSkipTrack = true;
	//		}
	//		else if (flags[20] == 2)
	//		{
	//			PlayTrack(TRACK_GERYON);
	//		}
	//	}
	//	break;
	//case 13:
	//	if (room == ROOM_VERGIL_2)
	//	{
	//		PlayTrack(TRACK_VERGIL_2);
	//	}
	//	break;
	//case 16:
	//	if (room == ROOM_LADY)
	//	{
	//		PlayTrack(TRACK_LADY);
	//	}
	//	break;
	//case 17:
	//	if ((room == ROOM_DOPPELGANGER) && (flags[20] == 0))
	//	{
	//		PlayTrack(TRACK_DOPPELGANGER);
	//	}
	//	break;
	//case 19:
	//	if (room == ROOM_ARKHAM)
	//	{
	//		if (flags[20] == 0)
	//		{
	//			PlayTrack(TRACK_ARKHAM_1);
	//			mediaSkipTrack = true;
	//		}
	//		else if (flags[20] == 1)
	//		{
	//			PlayTrack(TRACK_ARKHAM_2);
	//		}
	//	}
	//	break;
	//}

	//LogFunctionEnd();
}

#pragma endregion

static void InitSession()
{
	LogFunctionStart();
	if (Config.Arcade.enable)
	{
		Arcade_InitSession();
	}
	LogFunctionEnd();
}

static void SetCharacter(byte8 * addr)
{
	LogFunctionStart();
	if (Config.Arcade.enable)
	{
		Arcade_SetCharacter(addr);
	}
	LogFunctionEnd();
}

static void SetRoom()
{
	LogFunctionStart();
	if (Config.Arcade.enable)
	{
		Arcade_SetRoom();
	}
	if (Config.Game.BossRush.enable)
	{
		BossRush_SetRoom();
	}
	LogFunctionEnd();
}

static void SetNextRoom()
{
	LogFunctionStart();
	if (Config.Game.BossRush.enable)
	{
		BossRush_SetNextRoom();
	}
	LogFunctionEnd();
}

static void SetContinueRoom()
{
	LogFunctionStart();
	if (Config.Game.BossRush.enable)
	{
		BossRush_SetContinueRoom();
	}
	LogFunctionEnd();
}

// @Check: Why are both enum and bool required?

static const char * SetTrack(void *, const char * path, uint32, uint32)
{
	//Log("%s %s", FUNC_NAME, path);

	//mediaError = MEDIA_NO_ERROR;
	//if (_stricmp(path, "afs/sound/continue.adx") == 0)
	//{
	//	mediaSkipTrack = false;
	//}
	//if (mediaSkipTrack)
	//{
	//	mediaSkipTrack = false;
	//	mediaError = MEDIA_SKIP_TRACK;
	//	return 0;
	//}
	//if (Config.Game.BossRush.enable)
	//{
	//	return BossRush_SetTrack(path);
	//}

	return 0;
}

static void StageLoadComplete()
{
	LogFunctionStart();
	// @Todo: Too broad. Separate into smaller chunks.
	//if (System_Actor_enableArrayExtension)
	//{
	Actor_StageLoadComplete();
	//}
	if (Config.Game.BossRush.enable)
	{
		BossRush_StageLoadComplete();
	}
	LogFunctionEnd();
}

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
//	//if (!Config.Game.Doppelganger.enableDevilTrigger)
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
//	if (!Config.Game.Doppelganger.enableDevilTrigger)
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


}


























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













export void Event_Init()
{
	LogFunction();








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
	{
		byte8 sect0[] =
		{
			0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc3.exe+212760
		};
		FUNC func = CreateFunction(InitSession, (appBaseAddr + 0x2432CB), true, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteCall(func.sect0, (appBaseAddr + 0x212760));
		WriteJump((appBaseAddr + 0x2432C6), func.addr);
	}
	{
		byte8 sect1[] =
		{
			0x48, 0x8B, 0xC8, //mov rcx,rax
		};
		byte8 sect2[] =
		{
			0x0F, 0xB6, 0x88, 0x65, 0x45, 0x00, 0x00, //movzx ecx,byte ptr [rax+00004565]
		};
		FUNC func = CreateFunction(SetCharacter, (appBaseAddr + 0x24350B), true, true, 0, sizeof(sect1), sizeof(sect2));
		memcpy(func.sect1, sect1, sizeof(sect1));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteJump((appBaseAddr + 0x243504), func.addr, 2);
	}
	{
		byte8 sect0[] =
		{
			0x66, 0x89, 0x82, 0x64, 0x01, 0x00, 0x00, //mov [rdx+00000164],ax
		};
		byte8 sect1[] =
		{
			0x48, 0x8B, 0xCA, //mov rcx,rdx
		};
		FUNC func = CreateFunction(SetRoom, (appBaseAddr + 0x1AA8CC), true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteJump((appBaseAddr + 0x1AA8C5), func.addr, 2);
	}
	{
		byte8 sect0[] =
		{
			0x66, 0x89, 0x90, 0x66, 0x01, 0x00, 0x00, //mov [rax+00000166],dx
		};
		byte8 sect1[] =
		{
			0x48, 0x8B, 0xC8, //mov rcx,rax
		};
		FUNC func = CreateFunction(SetNextRoom, (appBaseAddr + 0x1A6002), true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteJump((appBaseAddr + 0x1A5FFB), func.addr, 2);
	}
	{
		byte8 sect0[] =
		{
			0x66, 0x89, 0x81, 0x66, 0x01, 0x00, 0x00, //mov [rcx+00000166],ax
		};
		FUNC func = CreateFunction(SetContinueRoom, (appBaseAddr + 0x1AA3CC), true, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteJump((appBaseAddr + 0x1AA3C5), func.addr, 2);
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


	//{
	//	constexpr byte8 sect0[] =
	//	{
	//		0xC7, 0x47, 0x20, 0x01, 0x00, 0x00, 0x00, //mov [rdi+20],00000001
	//	};
	//	FUNC func = CreateFunction(StageLoadComplete, (appBaseAddr + 0x23D0AB), true, true, sizeof(sect0));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	WriteJump((appBaseAddr + 0x23D0A4), func.addr, 2);
	//}



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
	//		0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rax,&Config.Game.Doppelganger.enable
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
	//	*(bool **)(func.sect2 + 2) = &Config.Game.Doppelganger.enable;
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
	//		0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rax,&Config.Game.Doppelganger.enable
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
	//	*(bool **)(func.sect2 + 2) = &Config.Game.Doppelganger.enable;
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

#endif
