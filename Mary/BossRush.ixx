module;
#include <string.h>
export module BossRush;

import Core;

#include "../Core/Macros.h"



import Config;
import Internal;
import Vars;


#define debug false









namespaceStart(BossRush);






export void SetRoom()
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
		nextEventData.room     = bossHelpers[boss].room;
		nextEventData.position = bossHelpers[boss].position;
	};

	if (nextEventData.room == missionStartHelpers[sessionData.mission].room)
	{
		switch (sessionData.mission)
		{
		case 3:
		{
			SetNextEventData(BOSS::CERBERUS);
			eventFlags[20] = 1;
			break;
		}
		case 4:
		{
			SetNextEventData(BOSS::GIGAPEDE);
			break;
		}
		case 5:
		{
			if (!activeConfig.BossRush.Mission5.skipJester)
			{
				SetNextEventData(BOSS::JESTER_1);
			}
			else
			{
				SetNextEventData(BOSS::AGNI_RUDRA);
				eventFlags[20] = 1;
			}
			break;
		}
		case 7:
		{
			SetNextEventData(BOSS::VERGIL_1);
			break;
		}
		case 8:
		{
			SetNextEventData(BOSS::LEVIATHAN);
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
			SetNextEventData(BOSS::NEVAN);
			eventFlags[20] = 1;
			break;
		}
		case 11:
		{
			SetNextEventData(BOSS::BEOWULF);
			eventFlags[20] = 1;
			break;
		}
		case 12:
		{
			if (!activeConfig.BossRush.Mission12.skipJester)
			{
				SetNextEventData(BOSS::JESTER_2);
			}
			else if (!activeConfig.BossRush.Mission12.skipGeryonPart1)
			{
				SetNextEventData(BOSS::GERYON_PART_1);
				eventFlags[20] = 1;
			}
			else
			{
				SetNextEventData(BOSS::GERYON_PART_2);
				eventFlags[20] = 2;
			}
			break;
		}
		case 13:
		{
			SetNextEventData(BOSS::VERGIL_2);
			break;
		}
		case 16:
		{
			SetNextEventData(BOSS::LADY);
			eventFlags[20] = 1;
			break;
		}
		case 17:
		{
			if (!activeConfig.BossRush.Mission17.skipJester)
			{
				SetNextEventData(BOSS::JESTER_3);
			}
			else
			{
				SetNextEventData(BOSS::DOPPELGANGER);
			}
			break;
		}
		case 18:
		{
			SetNextEventData(BOSS::TAIZAI_REBORN);
			break;
		}
		case 19:
		{
			if (!activeConfig.BossRush.Mission19.skipArkhamPart1)
			{
				SetNextEventData(BOSS::ARKHAM_PART_1);
			}
			else
			{
				SetNextEventData(BOSS::ARKHAM_PART_2);
				eventFlags[20] = 1;
			}
			break;
		}
		}
	}
}

export void SetNextRoom()
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
		nextEventData.room     = bossHelpers[boss].room;
		nextEventData.position = bossHelpers[boss].position;
	};

	switch (sessionData.mission)
	{
	case 5:
	{
		if (eventData.room == bossHelpers[BOSS::JESTER_1].room)
		{
			SetNextEventData(BOSS::AGNI_RUDRA);
			eventFlags[20] = 1;
		}
		break;
	}
	case 12:
	{
		if (eventData.room == bossHelpers[BOSS::JESTER_2].room)
		{
			if (!activeConfig.BossRush.Mission12.skipGeryonPart1)
			{
				SetNextEventData(BOSS::GERYON_PART_1);
				eventFlags[20] = 1;
			}
			else
			{
				SetNextEventData(BOSS::GERYON_PART_2);
				eventFlags[20] = 2;
			}
		}
		break;
	}
	case 17:
	{
		if (eventData.room == bossHelpers[BOSS::JESTER_3].room)
		{
			SetNextEventData(BOSS::DOPPELGANGER);
		}
		break;
	}
	case 18:
	{
		switch (static_cast<uint16>(eventData.room))
		{
		case bossHelpers[BOSS::TAIZAI_REBORN].room:
		{
			SetNextEventData(BOSS::CERBERUS_REBORN);
			break;
		}
		case bossHelpers[BOSS::CERBERUS_REBORN].room:
		{
			SetNextEventData(BOSS::GIGAPEDE_REBORN);
			break;
		}
		case bossHelpers[BOSS::GIGAPEDE_REBORN].room:
		{
			SetNextEventData(BOSS::AGNI_RUDRA_REBORN);
			break;
		}
		case bossHelpers[BOSS::AGNI_RUDRA_REBORN].room:
		{
			SetNextEventData(BOSS::LEVIATHAN_REBORN);
			break;
		}
		case bossHelpers[BOSS::LEVIATHAN_REBORN].room:
		{
			SetNextEventData(BOSS::NEVAN_REBORN);
			break;
		}
		case bossHelpers[BOSS::NEVAN_REBORN].room:
		{
			SetNextEventData(BOSS::BEOWULF_REBORN);
			break;
		}
		case bossHelpers[BOSS::BEOWULF_REBORN].room:
		{
			SetNextEventData(BOSS::GERYON_REBORN);
			break;
		}
		case bossHelpers[BOSS::GERYON_REBORN].room:
		{
			SetNextEventData(BOSS::DOPPELGANGER_REBORN);
			break;
		}
		case bossHelpers[BOSS::DOPPELGANGER_REBORN].room:
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

export void SetContinueRoom()
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

export bool SetTrack(const char * filename)
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
		(eventData.room == bossHelpers[BOSS::AGNI_RUDRA].room) &&
		(strcmp(filename, bossHelpers[BOSS::JESTER_1].track) == 0)
	)
	{
		return false;
	}

	return true;
}

export void EventMain()
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
		if ((eventData.room == bossHelpers[BOSS::CERBERUS].room) && (eventFlags[20] == 1))
		{
			PlayTrack(bossHelpers[BOSS::CERBERUS].track);
		}
		break;
	}
	case 5:
	{
		if ((eventData.room == bossHelpers[BOSS::AGNI_RUDRA].room) && (eventFlags[20] == 1))
		{
			PlayTrack(bossHelpers[BOSS::AGNI_RUDRA].track);
		}
		break;
	}
	case 7:
	{
		if (eventData.room == bossHelpers[BOSS::VERGIL_1].room)
		{
			PlayTrack(bossHelpers[BOSS::VERGIL_1].track);
		}
		break;
	}
	case 9:
	{
		if ((eventData.room == bossHelpers[BOSS::NEVAN].room) && (eventFlags[20] == 1))
		{
			PlayTrack(bossHelpers[BOSS::NEVAN].track);
		}
		break;
	}
	case 11:
	{
		if ((eventData.room == bossHelpers[BOSS::BEOWULF].room) && (eventFlags[20] == 1))
		{
			PlayTrack(bossHelpers[BOSS::BEOWULF].track);
		}
		break;
	}
	case 12:
	{
		if ((eventData.room == bossHelpers[BOSS::GERYON_PART_1].room) && (eventFlags[20] == 1))
		{
			PlayTrack(bossHelpers[BOSS::GERYON_PART_1].track);
		}
		else if ((eventData.room == bossHelpers[BOSS::GERYON_PART_2].room) && (eventFlags[20] == 2))
		{
			PlayTrack(bossHelpers[BOSS::GERYON_PART_2].track);
		}
		break;
	}
	case 13:
	{
		if (eventData.room == bossHelpers[BOSS::VERGIL_2].room)
		{
			PlayTrack(bossHelpers[BOSS::VERGIL_2].track);
		}
		break;
	}
	case 16:
	{
		if (eventData.room == bossHelpers[BOSS::LADY].room)
		{
			PlayTrack(bossHelpers[BOSS::LADY].track);
		}
		break;
	}
	case 17:
	{
		if ((eventData.room == bossHelpers[BOSS::DOPPELGANGER].room) && (eventFlags[20] == 0))
		{
			PlayTrack(bossHelpers[BOSS::DOPPELGANGER].track);
		}
		break;
	}
	case 19:
	{
		if ((eventData.room == bossHelpers[BOSS::ARKHAM_PART_1].room) && (eventFlags[20] == 0))
		{
			PlayTrack(bossHelpers[BOSS::ARKHAM_PART_1].track);
		}
		else if ((eventData.room == bossHelpers[BOSS::ARKHAM_PART_2].room) && (eventFlags[20] == 1))
		{
			PlayTrack(bossHelpers[BOSS::ARKHAM_PART_2].track);
		}
		break;
	}
	}
}




namespaceEnd();









