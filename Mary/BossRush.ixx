module;
// #include "../Core/Core.h"

// #include "Vars.h"

#include <string.h>


#include "../Core/Macros.h" //

export module BossRush;

import Core;


import Vars;

// #define memset SetMemory
// #define memcpy CopyMemory

import Config;
import Internal;

export void BossRush_SetRoom()
{
	if (!activeConfig.BossRush.enable)
	{
		return;
	}

	LogFunction();

	IntroduceSessionData();
	IntroduceEventData(return);
	IntroduceNextEventData(return);
	IntroduceEventFlags(return);
	
	auto SetNextEventData = [&](uint8 boss)
	{
		nextEventData.room     = bossHelper[boss].room;
		nextEventData.position = bossHelper[boss].position;
	};

	if (nextEventData.room == missionStartHelper[sessionData.mission].room)
	{
		switch (sessionData.mission)
		{
		case 3:
		{
			SetNextEventData(BOSS_CERBERUS);
			eventFlags[20] = 1;
			break;
		}
		case 4:
		{
			SetNextEventData(BOSS_GIGAPEDE);
			break;
		}
		case 5:
		{
			if (!activeConfig.BossRush.Mission5.skipJester)
			{
				SetNextEventData(BOSS_JESTER_1);
			}
			else
			{
				SetNextEventData(BOSS_AGNI_RUDRA);
				eventFlags[20] = 1;
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
			auto pool1 = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E10);
			if (!pool1)
			{
				break;
			}
			if (!pool1[12])
			{
				break;
			}
			auto pool2 = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E30);
			if (!pool2)
			{
				break;
			}
			*reinterpret_cast<uint8 *>(reinterpret_cast<byte8 *>(pool2) + 0x6A) = 1;
			*reinterpret_cast<byte8 *>(pool1[12] + 0x7DF) = 0x40;
			break;
		}
		case 9:
		{
			SetNextEventData(BOSS_NEVAN);
			eventFlags[20] = 1;
			break;
		}
		case 11:
		{
			SetNextEventData(BOSS_BEOWULF);
			eventFlags[20] = 1;
			break;
		}
		case 12:
		{
			if (!activeConfig.BossRush.Mission12.skipJester)
			{
				SetNextEventData(BOSS_JESTER_2);
			}
			else if (!activeConfig.BossRush.Mission12.skipGeryonPart1)
			{
				SetNextEventData(BOSS_GERYON_PART_1);
				eventFlags[20] = 1;
			}
			else
			{
				SetNextEventData(BOSS_GERYON_PART_2);
				eventFlags[20] = 2;
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
			eventFlags[20] = 1;
			break;
		}
		case 17:
		{
			if (!activeConfig.BossRush.Mission17.skipJester)
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
			if (!activeConfig.BossRush.Mission19.skipArkhamPart1)
			{
				SetNextEventData(BOSS_ARKHAM_PART_1);
			}
			else
			{
				SetNextEventData(BOSS_ARKHAM_PART_2);
				eventFlags[20] = 1;
			}
			break;
		}
		}
	}
}

export void BossRush_SetNextRoom()
{
	if (!activeConfig.BossRush.enable)
	{
		return;
	}

	LogFunction();

	IntroduceSessionData();
	IntroduceEventData(return);
	IntroduceNextEventData(return);
	IntroduceEventFlags(return);

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
			eventFlags[20] = 1;
		}
		break;
	}
	case 12:
	{
		if (eventData.room == bossHelper[BOSS_JESTER_2].room)
		{
			if (!activeConfig.BossRush.Mission12.skipGeryonPart1)
			{
				SetNextEventData(BOSS_GERYON_PART_1);
				eventFlags[20] = 1;
			}
			else
			{
				SetNextEventData(BOSS_GERYON_PART_2);
				eventFlags[20] = 2;
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
			eventFlags[14] = 0x3FE;
			eventFlags[15] = 0x1FF;
			break;
		}
		}
		break;
	}
	}
}

export void BossRush_SetContinueRoom()
{
	if (!activeConfig.BossRush.enable)
	{
		return;
	}

	LogFunction();

	IntroduceSessionData();
	IntroduceEventData(return);
	IntroduceNextEventData(return);
	IntroduceEventFlags(return);

	nextEventData.room     = static_cast<uint16>(eventData.room    );
	nextEventData.position = static_cast<uint16>(eventData.position);
}

export bool BossRush_SetTrack(const char * filename)
{
	if (!activeConfig.BossRush.enable)
	{
		return true;
	}

	LogFunction();

	IntroduceSessionData();
	IntroduceEventData(return true);
	IntroduceNextEventData(return true);
	IntroduceEventFlags(return true);

	if
	(
		(sessionData.mission == 5) &&
		(strcmp(filename, "afs/sound/Battle_03.adx") == 0)
	)
	{
		return false;
	}

	if
	(
		(sessionData.mission == 5) &&
		(eventData.room == bossHelper[BOSS_AGNI_RUDRA].room) &&
		(strcmp(filename, bossHelper[BOSS_JESTER_1].track) == 0)
	)
	{
		return false;
	}

	return true;
}

export void BossRush_Main()
{
	if (!activeConfig.BossRush.enable)
	{
		return;
	}

	LogFunction();

	IntroduceSessionData();
	IntroduceEventData(return);
	IntroduceNextEventData(return);
	IntroduceEventFlags(return);

	auto PlayTrack = [](const char * filename)
	{
		func_32BE20((appBaseAddr + 0xCF3700));
		func_32BA90((appBaseAddr + 0xCF3708), filename, 0, 0);
	};

	switch (sessionData.mission)
	{
	case 3:
	{
		if ((eventData.room == bossHelper[BOSS_CERBERUS].room) && (eventFlags[20] == 1))
		{
			PlayTrack(bossHelper[BOSS_CERBERUS].track);
		}
		break;
	}
	case 5:
	{
		if ((eventData.room == bossHelper[BOSS_AGNI_RUDRA].room) && (eventFlags[20] == 1))
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
		if ((eventData.room == bossHelper[BOSS_NEVAN].room) && (eventFlags[20] == 1))
		{
			PlayTrack(bossHelper[BOSS_NEVAN].track);
		}
		break;
	}
	case 11:
	{
		if ((eventData.room == bossHelper[BOSS_BEOWULF].room) && (eventFlags[20] == 1))
		{
			PlayTrack(bossHelper[BOSS_BEOWULF].track);
		}
		break;
	}
	case 12:
	{
		if ((eventData.room == bossHelper[BOSS_GERYON_PART_1].room) && (eventFlags[20] == 1))
		{
			PlayTrack(bossHelper[BOSS_GERYON_PART_1].track);
		}
		else if ((eventData.room == bossHelper[BOSS_GERYON_PART_2].room) && (eventFlags[20] == 2))
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
		if ((eventData.room == bossHelper[BOSS_DOPPELGANGER].room) && (eventFlags[20] == 0))
		{
			PlayTrack(bossHelper[BOSS_DOPPELGANGER].track);
		}
		break;
	}
	case 19:
	{
		if ((eventData.room == bossHelper[BOSS_ARKHAM_PART_1].room) && (eventFlags[20] == 0))
		{
			PlayTrack(bossHelper[BOSS_ARKHAM_PART_1].track);
		}
		else if ((eventData.room == bossHelper[BOSS_ARKHAM_PART_2].room) && (eventFlags[20] == 1))
		{
			PlayTrack(bossHelper[BOSS_ARKHAM_PART_2].track);
		}
		break;
	}
	}
}
