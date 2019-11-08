//dmc3.exe+32BA90

//afs/sound/Boss_05.adx


#include "Event.h"



#pragma warning(disable: 4003) // Zero args for macro provided.

//#pragma warning(disable: 4102) // Unreferenced label.









#define InitVars(result)                              \
byte * addr = *(byte **)(appBaseAddr + 0xCA8918);     \
if (!addr)                                            \
{                                                     \
	return result;                                    \
}                                                     \
addr = *(byte **)(addr + 0x40);                       \
if (!addr)                                            \
{                                                     \
	return result;                                    \
}                                                     \
uint32 & room     = *(uint32 *)(addr + 0x18);         \
uint32 & position = *(uint32 *)(addr + 0x1C);         \
                                                      \
addr = *(byte **)(appBaseAddr + 0xCA8918);            \
addr = *(byte **)(addr + 0x60);                       \
if (!addr)                                            \
{                                                     \
	return result;                                    \
}                                                     \
uint16 & nextRoom     = *(uint16 *)(addr + 0x164);    \
uint16 & nextPosition = *(uint16 *)(addr + 0x166);    \
                                                      \
addr = *(byte **)(appBaseAddr + 0xC90E30);            \
if (!addr)                                            \
{                                                     \
	return result;                                    \
}                                                     \
addr = *(byte **)(addr + 8);                          \
if (!addr)                                            \
{                                                     \
	return result;                                    \
}                                                     \
dword * flags = (dword *)addr;                        \
                                                      \
uint32 mission = *(uint32 *)(appBaseAddr + 0xC8F250);











static void Arcade_InitSession()
{
	if (!Config.Game.Arcade.enable)
	{
		return;
	}
	byte * addr = (appBaseAddr + 0xC8F250);
	uint32  & mission            = *(uint32  *)addr;
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

	mission = Config.Game.Arcade.mission;

	ModeStart:
	{
		if ((Config.Game.Arcade.mission == 0) || (Config.Game.Arcade.mission == 21))
		{
			goto ModeEnd;
		}
		if (Config.Game.Arcade.mode == 5)
		{
			mode = MODE_HARD;
			oneHitKill = true;
		}
		else
		{
			mode = Config.Game.Arcade.mode;
		}
	}
	ModeEnd:

	enableTutorial = false;
	useGoldOrb = true;

	if (Config.Game.Arcade.mission == 21)
	{
		bloodyPalace = true;
	}

	goldOrbCount = 3;

	memset(unlock, true, 14);

	if (Config.Game.Arcade.character == CHAR_DANTE)
	{
		vp_memcpy(equipment, Config.Game.Arcade.equipment, 4);
	}



	costume = Config.Game.Arcade.costume;

	unlockDevilTrigger = true;

	hitPoints = Config.Game.Arcade.hitPoints;
	magicPoints = Config.Game.Arcade.magicPoints;

	if (Config.Game.Arcade.character == CHAR_DANTE)
	{
		style = Config.Game.Arcade.style;
	}



	
	memset(styleLevel, 0, (MAX_STYLE * 4));
	for (uint8 styleId = 0; styleId < 4; styleId++)
	{
		styleLevel[styleId] = 2;
	}





	





	memset(styleExperience, 0, (MAX_STYLE * 4));

	memset(expertise, 0xFFFFFFFF, 32);






	uint32 & controllerMagic = *(uint32 *)(appBaseAddr + 0x553000);

	controllerMagic = 0;




}

static void Arcade_SetCharacter(byte * addr)
{
	if (!Config.Game.Arcade.enable)
	{
		return;
	}
	uint8 & character = *(uint8 *)(addr + 0x4565);
	character = Config.Game.Arcade.character;
}

static void Arcade_SetRoom()
{
	if (!Config.Game.Arcade.enable)
	{
		return;
	}
	InitVars();
	if (!Config.Game.Arcade.ignoreRoom)
	{
		nextRoom = Config.Game.Arcade.room;
	}
	if (!Config.Game.Arcade.ignorePosition)
	{
		nextPosition = Config.Game.Arcade.position;
	}
	if (mission == 21)
	{
		uint16 room[] =
		{
			423, //floor 1
			424, //floor 2
			425, //floor 3
			426, //floor 4
			427, //floor 5
			428, //floor 6
			429, //floor 7
			430, //floor 8
			431, //floor 9
			432, //floor 10
			433, //cerberus
			434, //gigapede
			435, //agni rudra
			436, //nevan
			437, //beowulf
			438, //geryon
			439, //doppelganger
			440, //heart of leviathan
			441, //damned chessmen
			442, //vergil 1
			443, //vergil 2
			444, //vergil 3
			445, //lady
			446, //arkham
			422, //jester 1
			448, //jester 2
			449, //jester 3
		};
		uint16 position[] =
		{
			0, //floor 1
			0, //floor 2
			0, //floor 3
			0, //floor 4
			0, //floor 5
			0, //floor 6
			0, //floor 7
			0, //floor 8
			0, //floor 9
			0, //floor 10
			0, //cerberus
			0, //gigapede
			0, //agni rudra
			0, //nevan
			0, //beowulf
			2, //geryon
			0, //doppelganger
			0, //heart of leviathan
			0, //damned chessmen
			0, //vergil 1
			0, //vergil 2
			0, //vergil 3
			2, //lady
			0, //arkham
			0, //jester 1
			0, //jester 2
			0, //jester 3
		};
		nextRoom     = room    [Config.Game.Arcade.BloodyPalace.floor];
		nextPosition = position[Config.Game.Arcade.BloodyPalace.floor];
	}

	Log("arcade too");

}

static void BossRush_SetRoom()
{
	if (!Config.Game.BossRush.enable)
	{
		return;
	}

	

	InitVars();
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
			addr = *(byte **)(appBaseAddr + 0xC90E30);
			if (!addr)
			{
				break;
			}
			*(uint8 *)(addr + 0x6A) = 1;
			addr = *(byte **)(appBaseAddr + 0xCA8918);
			if (!addr)
			{
				break;
			}
			addr = *(byte **)(addr + 0x60);
			if (!addr)
			{
				break;
			}
			*(byte *)(addr + 0x7DF) = 0x40;
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



	Log("reach here");








}

static void BossRush_SetNextRoom()
{
	if (!Config.Game.BossRush.enable)
	{
		return;
	}

	Log("yup br");

	InitVars();
	

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
			nextRoom     = ROOM_CERBERUS_REBORN;
			nextPosition = POSITION_CERBERUS_REBORN;
			break;
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
			/*
			addr = *(byte **)(appBaseAddr + 0xCA8918);
			if (!addr)
			{
				break;
			}
			addr = *(byte **)(addr + 0x60);
			if (!addr)
			{
				break;
			}
			*(word *)(addr + 0x38) = 0x3FE;
			*(word *)(addr + 0x3C) = 0x1FF;
			*/
			flags[14] = 0x3FE;
			flags[15] = 0x1FF;
			break;
		}
		break;
	}
}

static void BossRush_SetContinueRoom()
{
	if (!Config.Game.BossRush.enable)
	{
		return;
	}
	InitVars();
	nextRoom     = (uint16)room;
	nextPosition = (uint16)position;
}


































static void InitSession()
{
	LogFunction();
	Arcade_InitSession();
}

static void SetCharacter(byte * addr)
{
	LogFunction();
	Arcade_SetCharacter(addr);
}

static void SetRoom()
{
	LogFunction();
	Arcade_SetRoom();
	BossRush_SetRoom();
}

static void SetNextRoom()
{
	LogFunction();
	BossRush_SetNextRoom();
}

static void SetContinueRoom()
{
	LogFunction();
	BossRush_SetContinueRoom();
}

static const char * SetTrack(void *, const char * path, uint32, uint32)
{
	Log("%s %s", FUNC_NAME, path);
	mediaError = MEDIA_NO_ERROR;
	if (_stricmp(path, "afs/sound/continue.adx") == 0)
	{
		mediaSkipTrack = false;
	}
	if (mediaSkipTrack)
	{
		mediaSkipTrack = false;
		mediaError = MEDIA_SKIP_TRACK;
		return 0;
	}
	if (!Config.Game.BossRush.enable)
	{
		return 0;
	}
	InitVars(0);
	switch (mission)
	{
	case 5:
		if (_stricmp(path, "afs/sound/Battle_03.adx") == 0)
		{
			mediaError = MEDIA_SKIP_TRACK;
			return 0;
		}
		if (nextRoom == ROOM_AGNI_RUDRA)
		{
			if (_stricmp(path, TRACK_JESTER_1) == 0)
			{
				mediaError = MEDIA_SKIP_TRACK;
				return 0;
			}
		}
		break;
	case 12:
		if (nextRoom == ROOM_GERYON)
		{
			if (_stricmp(path, TRACK_JESTER_2) == 0)
			{
				mediaError = MEDIA_SKIP_TRACK;
				return 0;
			}
		}
		break;
	case 17:
		if (nextRoom == ROOM_DOPPELGANGER)
		{
			if (_stricmp(path, TRACK_JESTER_3) == 0)
			{
				mediaError = MEDIA_SKIP_TRACK;
				return 0;
			}
		}
		break;
	}
	return 0;
}




























static void BossRush_StageLoadComplete()
{
	if (!Config.Game.BossRush.enable)
	{
		return;
	}
	InitVars();
	switch (mission)
	{
	case 3:
		if ((room == ROOM_CERBERUS) && (flags[20] == 1))
		{
			PlayTrack(TRACK_CERBERUS);
		}
		break;
	case 5:
		if ((room == ROOM_AGNI_RUDRA) && (flags[20] == 1))
		{
			PlayTrack(TRACK_AGNI_RUDRA);
		}
		break;
	case 7:
		if (room == ROOM_VERGIL_1)
		{
			PlayTrack(TRACK_VERGIL_1);
		}
		break;
	case 9:
		if ((room == ROOM_NEVAN) && (flags[20] == 1))
		{
			PlayTrack(TRACK_NEVAN);
		}
		break;
	case 11:
		if ((room == ROOM_BEOWULF) && (flags[20] == 1))
		{
			PlayTrack(TRACK_BEOWULF);
		}
		break;
	case 12:
		if (room == ROOM_GERYON)
		{
			if (flags[20] == 1)
			{
				PlayTrack(TRACK_GERYON);
				mediaSkipTrack = true;
			}
			else if (flags[20] == 2)
			{
				PlayTrack(TRACK_GERYON);
			}
		}
		break;
	case 13:
		if (room == ROOM_VERGIL_2)
		{
			PlayTrack(TRACK_VERGIL_2);
		}
		break;
	case 16:
		if (room == ROOM_LADY)
		{
			PlayTrack(TRACK_LADY);
		}
		break;
	case 17:
		if ((room == ROOM_DOPPELGANGER) && (flags[20] == 0))
		{
			PlayTrack(TRACK_DOPPELGANGER);
		}
		break;
	case 19:
		if (room == ROOM_ARKHAM)
		{
			if (flags[20] == 0)
			{
				PlayTrack(TRACK_ARKHAM_1);
				mediaSkipTrack = true;
			}
			else if (flags[20] == 1)
			{
				PlayTrack(TRACK_ARKHAM_2);
			}
		}
		break;
	}
}





static void Actor_StageLoadComplete()
{
	LogFunction();
	if (!System_Actor_enable)
	{
		return;
	}

	


	// Update Ids
	for (uint8 actor = 0; actor < GetActorCount(); actor++)
	{
		uint8 & id = *(uint8 *)(actorBaseAddr[actor] + 0x118);
		id = actor;
		Log("Actor id %u", id);
	}
	//// Fix Style Level
	//if (Config.Game.Multiplayer.enable)
	//{
	//	for (uint8 actor = 0; actor < GetActorCount(); actor++)
	//	{
	//		uint32 & style = *(uint32 *)(actorBaseAddr[actor] + 0x6338);
	//		if (style == STYLE_DOPPELGANGER)
	//		{
	//			style = STYLE_TRICKSTER;
	//			uint32 & level = *(uint32 *)(actorBaseAddr[actor] + 0x6358);
	//			byte * session = *(byte **)(appBaseAddr + 0xC90E30);
	//			if (!session)
	//			{
	//				level = 2;
	//				continue;
	//			}
	//			level = *(uint32 *)(session + 0x11C + (style * 4));
	//		}
	//	}
	//}




	// Set Doppelganger Flags
	uint8 character = *(uint8 *)(actorBaseAddr[ACTOR_ONE] + 0x78);
	if (!Config.Game.Multiplayer.enable && (Config.Game.StyleSwitcher.enable || (character == CHAR_DANTE)))
	{
		bool & isDoppelganger = *(bool *)(actorBaseAddr[ACTOR_TWO] + 0x11C);
		isDoppelganger = true;
		uint8 & shadow = *(uint8 *)(actorBaseAddr[ACTOR_TWO] + 0x3A18);
		shadow = 0;
		*(uint32 *)(actorBaseAddr[ACTOR_TWO] + 0x6338) = *(uint32 *)(actorBaseAddr[ACTOR_ONE] + 0x6338);
	}
}

static void StageLoadComplete()
{
	LogFunction();
	Actor_StageLoadComplete();
	BossRush_StageLoadComplete();
}





#undef InitVars






















void System_Event_Init()
{
	LogFunction();
	{
		byte sect0[] =
		{
			0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc3.exe+212760
		};
		FUNC func = CreateFunction(InitSession, (appBaseAddr + 0x2432CB), true, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteCall(func.sect0, (appBaseAddr + 0x212760));
		WriteJump((appBaseAddr + 0x2432C6), func.addr);
	}
	{
		byte sect1[] =
		{
			0x48, 0x8B, 0xC8, //mov rcx,rax
		};
		byte sect2[] =
		{
			0x0F, 0xB6, 0x88, 0x65, 0x45, 0x00, 0x00, //movzx ecx,byte ptr [rax+00004565]
		};
		FUNC func = CreateFunction(SetCharacter, (appBaseAddr + 0x24350B), true, true, 0, sizeof(sect1), sizeof(sect2));
		memcpy(func.sect1, sect1, sizeof(sect1));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteJump((appBaseAddr + 0x243504), func.addr, 2);
	}
	{
		byte sect0[] =
		{
			0x66, 0x89, 0x82, 0x64, 0x01, 0x00, 0x00, //mov [rdx+00000164],ax
		};
		byte sect1[] =
		{
			0x48, 0x8B, 0xCA, //mov rcx,rdx
		};
		FUNC func = CreateFunction(SetRoom, (appBaseAddr + 0x1AA8CC), true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteJump((appBaseAddr + 0x1AA8C5), func.addr, 2);
	}
	{
		byte sect0[] =
		{
			0x66, 0x89, 0x90, 0x66, 0x01, 0x00, 0x00, //mov [rax+00000166],dx
		};
		byte sect1[] =
		{
			0x48, 0x8B, 0xC8, //mov rcx,rax
		};
		FUNC func = CreateFunction(SetNextRoom, (appBaseAddr + 0x1A6002), true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteJump((appBaseAddr + 0x1A5FFB), func.addr, 2);
	}
	{
		byte sect0[] =
		{
			0x66, 0x89, 0x81, 0x66, 0x01, 0x00, 0x00, //mov [rcx+00000166],ax
		};
		FUNC func = CreateFunction(SetContinueRoom, (appBaseAddr + 0x1AA3CC), true, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteJump((appBaseAddr + 0x1AA3C5), func.addr, 2);
	}









	// @Audit: Not sure if this shouldn't be part of Media.cpp.


	{
		byte sect0[] =
		{
			0x48, 0x89, 0x5C, 0x24, 0x08, //mov [rsp+08],rbx
		};
		byte sect2[] =
		{
			0x48, 0x85, 0xC0,                                           //test rax,rax
			0x74, 0x03,                                                 //je short
			0x48, 0x8B, 0xD0,                                           //mov rdx,rax
			0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rax,&mediaError
			0x8B, 0x00,                                                 //mov eax,[rax]
			0x3D, 0x00, 0x00, 0x00, 0x00,                               //cmp eax,MEDIA_SKIP_TRACK
			0x75, 0x01,                                                 //jne short
			0xC3,                                                       //ret
		};
		FUNC func = CreateFunction(SetTrack, (appBaseAddr + 0x32BA95), true, false, sizeof(sect0), 0, sizeof(sect2));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect2, sect2, sizeof(sect2));
		*(dword **)(func.sect2 + 0xA) = &mediaError;
		*(dword *)(func.sect2 + 0x15) = MEDIA_SKIP_TRACK;
		WriteJump((appBaseAddr + 0x32BA90), func.addr);
	}
	{
		byte sect0[] =
		{
			0xC7, 0x47, 0x20, 0x01, 0x00, 0x00, 0x00, //mov [rdi+20],00000001
		};
		FUNC func = CreateFunction(StageLoadComplete, (appBaseAddr + 0x23D0AB), true, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteJump((appBaseAddr + 0x23D0A4), func.addr, 2);
	}
}
