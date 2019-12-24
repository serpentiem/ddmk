
// @Todo: Create Helpers.

#include "Event.h"





#pragma region System Events

#pragma region Actor

static void Actor_StageLoadComplete()
{

	return;


	auto & baseAddr = System_Actor_actorBaseAddr[ACTOR_TWO];

	
	if (!baseAddr)
	{
		return;
	}

	Cosmetics_Color_ApplyColor(baseAddr, 6, 0);

	return;




	//HoboBreak();

	if (Config.Game.Multiplayer.enable)
	{
		return;
	}
	uint8 count = GetActorCount();
	for (uint8 actor = ACTOR_TWO; actor < count; actor++)
	{
		auto & baseAddr = System_Actor_actorBaseAddr[actor];
		if (!baseAddr)
		{
			continue;
		}
		bool & isDoppelganger = *(bool *)(baseAddr + 0x11C) = true;
		uint8 & shadow = *(uint8 *)(baseAddr + 0x3A18) = 0;
	}
}

#pragma endregion

#pragma region Arcade

static void Arcade_InitSession()
{
	LogFunctionStart();

	byte * addr = (appBaseAddr + 0xC8F250);
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

	mission = Config.Game.Arcade.mission;

	ModeStart:
	{
		if ((Config.Game.Arcade.mission == 0) || (Config.Game.Arcade.mission == 21))
		{
			goto ModeEnd;
		}
		// @Todo: Create modeMap.
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




	LogFunctionEnd();
}

static void Arcade_SetCharacter(byte * addr)
{
	LogFunctionStart();
	uint8 & character = *(uint8 *)(addr + 0x4565);
	character = Config.Game.Arcade.character;
	LogFunctionEnd();
}

static void Arcade_SetRoom()
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
		struct DPS
		{
			uint16 room;
			uint16 position;
		};
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
		nextRoom     = var[Config.Game.Arcade.BloodyPalace.floor].room;
		nextPosition = var[Config.Game.Arcade.BloodyPalace.floor].position;
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
			byte * addr = *(byte **)(appBaseAddr + 0xC90E30);
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
	LogFunctionStart();

	VARS vars = {};
	if (!vars.init)
	{
		return 0;
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

	LogFunctionEnd();

	return 0;
}

static void BossRush_StageLoadComplete()
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

	LogFunctionEnd();
}

#pragma endregion

static void InitSession()
{
	LogFunctionStart();
	if (Config.Game.Arcade.enable)
	{
		Arcade_InitSession();
	}
	LogFunctionEnd();
}

static void SetCharacter(byte * addr)
{
	LogFunctionStart();
	if (Config.Game.Arcade.enable)
	{
		Arcade_SetCharacter(addr);
	}
	LogFunctionEnd();
}

static void SetRoom()
{
	LogFunctionStart();
	if (Config.Game.Arcade.enable)
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
	if (Config.Game.BossRush.enable)
	{
		return BossRush_SetTrack(path);
	}

	return 0;
}

static void StageLoadComplete()
{
	LogFunctionStart();
	// @Todo: Too broad. Separate into smaller chunks.
	if (System_Actor_enableArrayExtension)
	{
		Actor_StageLoadComplete();
	}
	if (Config.Game.BossRush.enable)
	{
		BossRush_StageLoadComplete();
	}
	LogFunctionEnd();
}

#pragma endregion

#pragma region Game Events

static void DevilForm_Activate(byte8 * baseAddr)
{
	LogFunction(baseAddr);
	auto actor = GetActorId(baseAddr);
	auto & doppelganger = *(bool *)(baseAddr + 0x6362);
	if (actor != ACTOR_ONE)
	{
		return;
	}
	if (doppelganger)
	{
		return;
	}
	UpdateFlux(baseAddr, DEVIL_FLUX_START);
}

static void DevilForm_Deactivate(byte * baseAddr)
{
	LogFunction(baseAddr);
	auto actor = GetActorId(baseAddr);
	auto & doppelganger = *(bool *)(baseAddr + 0x6362);
	if (actor != ACTOR_ONE)
	{
		return;
	}
	if (doppelganger)
	{
		return;
	}
	UpdateFlux(baseAddr, DEVIL_FLUX_END);
}

inline void Doppelganger_ToggleForceActorUpdate(bool enable)
{
	LogFunction(enable);
	if (enable)
	{
		Write<byte>((appBaseAddr + 0x1F83D0), 0xEB);
	}
	else
	{
		Write<byte>((appBaseAddr + 0x1F83D0), 0x75);
	}
}

// @Todo: Ugh, update.

static void Doppelganger_Activate(byte * baseAddr)
{
	Log("%s %llX", FUNC_NAME, baseAddr);

	uint8 actor = GetActorId(baseAddr);
	if (actor != ACTOR_ONE)
	{
		return;
	}

	Doppelganger_ToggleForceActorUpdate(true);

	if (!Config.Game.Doppelganger.enableDevilTrigger)
	{
		UpdateFlux(baseAddr, DEVIL_FLUX_END);
		return;
	}
	bool devil = *(bool *)(baseAddr + 0x3E9B);
	if (devil)
	{
		UpdateFlux(baseAddr, DEVIL_FLUX_END);
	}

	//uint8 & shadow = *(uint8 *)(actorBaseAddr[ACTOR_TWO] + 0x3A18) = 0;

	*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E6C) = *(uint32 *)(baseAddr + 0x3E6C);
	*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E70) = *(uint32 *)(baseAddr + 0x3E70);
	*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E88) = *(uint32 *)(baseAddr + 0x3E88);
	*(bool   *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E9B) = *(bool   *)(baseAddr + 0x3E9B);
	uint8 character = *(uint8 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x78);
	if (character == CHAR_BOB)
	{
		if (devil)
		{
			*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E6C) = DEVIL_BOB_YAMATO;
			*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E70) = DEVIL_BOB_YAMATO;
			*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E88) = DEVIL_BOB_YAMATO;
		}
		else
		{
			*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E6C) = 0;
			*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E70) = 0;
			*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E88) = 0;
		}
	}
	else if (character == CHAR_LADY)
	{
		*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E6C) = 0;
		*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E70) = 0;
		*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E88) = 0;
		*(bool   *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E9B) = false;
	}
	else if (character == CHAR_VERGIL)
	{
		uint8 devilForm[] =
		{
			DEVIL_VERGIL_YAMATO,
			DEVIL_VERGIL_BEOWULF,
			DEVIL_VERGIL_FORCE_EDGE,
		};
		uint8 selectedWeapon = *(uint8 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x6488);
		if (selectedWeapon > 2)
		{
			selectedWeapon = 0;
		}
		if (devil)
		{
			*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E6C) = devilForm[selectedWeapon];
			*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E70) = devilForm[selectedWeapon];
			*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E88) = devilForm[selectedWeapon];
		}
		else
		{
			*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E6C) = 0;
			*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E70) = 0;
			*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E88) = 0;
		}
	}
	if (character != CHAR_LADY)
	{
		UpdateDevilForm(System_Actor_actorBaseAddr[ACTOR_TWO]);
	}
}

static void Doppelganger_Deactivate(byte * baseAddr)
{
	Log("%s %llX", FUNC_NAME, baseAddr);

	uint8 actor = GetActorId(baseAddr);
	if (actor != ACTOR_ONE)
	{
		return;
	}

	Doppelganger_ToggleForceActorUpdate(false);

	if (!Config.Game.Doppelganger.enableDevilTrigger)
	{
		*(uint32 *)(baseAddr + 0x3E6C) = 0;
		*(uint32 *)(baseAddr + 0x3E70) = 0;
		*(uint32 *)(baseAddr + 0x3E88) = 0;
		UpdateDevilForm(baseAddr);
		UpdateFlux(baseAddr, DEVIL_FLUX_END);
		Relax(baseAddr);
		return;
	}
	bool devil = *(bool *)(baseAddr + 0x3E9B);
	if (devil)
	{
		UpdateFlux(baseAddr, DEVIL_FLUX_START);
	}
	*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E6C) = 0;
	*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E70) = 0;
	*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E88) = 0;
	*(bool   *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E9B) = false;
}

byte32 Doppelganger_Watchdog(void * parameter)
{
	LogFunction();
	do
	{
		LoopStart:
		{
			bool state = ActorAvailable();
			static bool savedState = state;
			if (savedState != state)
			{
				savedState = state;
				Doppelganger_ToggleForceActorUpdate(false);
			}
		}
		LoopEnd:
		Sleep(100);
	}
	while (true);
	return 1;
}

#pragma endregion

void Event_Init()
{
	LogFunction();
	#pragma region System Events
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
	#pragma endregion
	#pragma region Game Events
	{
		FUNC func = CreateFunction(DevilForm_Activate, (appBaseAddr + 0x1E78B4));
		WriteJump((appBaseAddr + 0x1E78AF), func.addr);
	}
	{
		FUNC func = CreateFunction(DevilForm_Deactivate, (appBaseAddr + 0x1E78EB));
		WriteJump((appBaseAddr + 0x1E78E6), func.addr);
	}
	{
		byte sect0[] =
		{
			0x50, //push rax
		};
		byte sect1[] =
		{
			0x48, 0x8B, 0xCF, //mov rcx,rdi
		};
		byte sect2[] =
		{
			0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rax,&Config.Game.Doppelganger.enable
			0x8A, 0x00,                                                 //mov al,[rax]
			0x84, 0xC0,                                                 //test al,al
			0x74, 0x06,                                                 //je short
			0x58,                                                       //pop rax
			0xE9, 0x00, 0x00, 0x00, 0x00,                               //jmp dmc3.exe+1E930E
			0x58,                                                       //pop rax
			0x80, 0xBF, 0x9B, 0x3E, 0x00, 0x00, 0x01,                   //cmp byte ptr [rdi+00003E9B],01
			0x0F, 0x85, 0x00, 0x00, 0x00, 0x00,                         //jne dmc3.exe+1E930E
			0xE9, 0x00, 0x00, 0x00, 0x00,                               //jmp dmc3.exe+1E92EA
		};
		// @Todo: Update CreateFunction. Add noReturn.
		FUNC func = CreateFunction(Doppelganger_Activate, 0, true, false, sizeof(sect0), sizeof(sect1), sizeof(sect2));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		memcpy(func.sect2, sect2, sizeof(sect2));
		*(bool **)(func.sect2 + 2) = &Config.Game.Doppelganger.enable;
		WriteAddress((func.sect2 + 0x11), (appBaseAddr + 0x1E930E), 5);
		WriteAddress((func.sect2 + 0x1E), (appBaseAddr + 0x1E930E), 6);
		WriteAddress((func.sect2 + 0x24), (appBaseAddr + 0x1E92EA), 5);
		WriteJump((appBaseAddr + 0x1E92E1), func.addr, 2);
	}
	{
		byte sect0[] =
		{
			0x50, //push rax
		};
		byte sect1[] =
		{
			0x48, 0x8B, 0xCB, //mov rcx,rbx
		};
		byte sect2[] =
		{
			0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rax,&Config.Game.Doppelganger.enable
			0x8A, 0x00,                                                 //mov al,[rax]
			0x84, 0xC0,                                                 //test al,al
			0x74, 0x06,                                                 //je short
			0x58,                                                       //pop rax
			0xE9, 0x00, 0x00, 0x00, 0x00,                               //jmp dmc3.exe+1E2B63
			0x58,                                                       //pop rax
			0x80, 0xBB, 0x9B, 0x3E, 0x00, 0x00, 0x00,                   //cmp byte ptr [rbx+00003E9B],00
			0x0F, 0x85, 0x00, 0x00, 0x00, 0x00,                         //jne dmc3.exe+1E2B63
			0xE9, 0x00, 0x00, 0x00, 0x00,                               //jmp dmc3.exe+1E2B2D
		};
		FUNC func = CreateFunction(Doppelganger_Deactivate, 0, true, false, sizeof(sect0), sizeof(sect1), sizeof(sect2));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		memcpy(func.sect2, sect2, sizeof(sect2));
		*(bool **)(func.sect2 + 2) = &Config.Game.Doppelganger.enable;
		WriteAddress((func.sect2 + 0x11), (appBaseAddr + 0x1E2B63), 5);
		WriteAddress((func.sect2 + 0x1E), (appBaseAddr + 0x1E2B63), 6);
		WriteAddress((func.sect2 + 0x24), (appBaseAddr + 0x1E2B2D), 5);
		WriteJump((appBaseAddr + 0x1E2B24), func.addr, 2);
	}
	CreateThread(0, 4096, Doppelganger_Watchdog, 0, 0, 0);
	#pragma endregion
}

void Event_ToggleSkipIntro(bool enable)
{
	LogFunction(enable);
	if (enable)
	{
		WriteAddress((appBaseAddr + 0x2383F2), (appBaseAddr + 0x2383F8), 6); // Skip Message
		WriteAddress((appBaseAddr + 0x241789), (appBaseAddr + 0x24178B), 2); // Skip Video
		vp_memset((appBaseAddr + 0x243531), 0x90, 2);                        // Disable Video Timer
		Write<byte>((appBaseAddr + 0x238704), 0x00);                         // Hide Rebellion
	}
	else
	{
		WriteAddress((appBaseAddr + 0x2383F2), (appBaseAddr + 0x238527), 6);
		WriteAddress((appBaseAddr + 0x241789), (appBaseAddr + 0x2417A6), 2);
		{
			byte payload[] =
			{
				0xFF, 0xC8, //dec eax
			};
			vp_memcpy((appBaseAddr + 0x243531), payload, sizeof(payload));
		}
		Write<byte>((appBaseAddr + 0x238704), 0x01);
	}
}

void Event_ToggleSkipCutscenes(bool enable)
{
	LogFunction(enable);
	if (enable)
	{
		WriteAddress((appBaseAddr + 0x238CCA), (appBaseAddr + 0x238CD0), 6);
		WriteAddress((appBaseAddr + 0x238CD8), (appBaseAddr + 0x238CDE), 6);
		WriteAddress((appBaseAddr + 0x238CE3), (appBaseAddr + 0x238CE9), 6);
	}
	else
	{
		WriteAddress((appBaseAddr + 0x238CCA), (appBaseAddr + 0x238E62), 6);
		WriteAddress((appBaseAddr + 0x238CD8), (appBaseAddr + 0x238E62), 6);
		WriteAddress((appBaseAddr + 0x238CE3), (appBaseAddr + 0x238E62), 6);
	}
}
