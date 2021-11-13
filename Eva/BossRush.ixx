export module BossRush;

import Core;

#include "../Core/Macros.h"

import Windows;

using namespace Windows;

import Config;
import Global;
import Vars;

#define debug false

// #include "Macros.h"


















namespaceStart(BossRush);

















export void MissionStartSetIndex()
{
	if (!activeConfig.BossRush.enable)
	{
		return;
	}

	LogFunction();

	IntroduceSessionData(return);



	// Because we change the mission start rooms sometimes the wrong screen effects
	// will be applied and the screen may end up black.

	auto dataAddr = *reinterpret_cast<ScreenEffectData **>(appBaseAddr + 0x60AF18);
	if (!dataAddr)
	{
		return;
	}

	for_all(index, 4)
	{
		auto & data = dataAddr[index];

		data.status = 0;

		DebugLog("&data.status %llX", &data.status);
	}



	if (sessionData.mission == 15)
	{
		ToggleSkipText(true);
	}



	// switch (sessionData.mission)
	// {
	// 	// case 3:
	// 	// {
	// 	// 	ToggleAutoExamine(true);

	// 	// 	break;
	// 	// }
	// 	case 15:
	// 	{
	// 		ToggleSkipText(true);

	// 		break;
	// 	}
	// }
}



// export void Mission3CutsceneStart()
// {
// 	if (!activeConfig.BossRush.enable)
// 	{
// 		return;
// 	}

// 	LogFunction();

// 	IntroduceSessionData(return);

// 	if (sessionData.mission == 3)
// 	{
// 		ToggleAutoExamine(false);
// 	}
// }





















export void SetRoom()
{
	if (!activeConfig.BossRush.enable)
	{
		return;
	}

	LogFunction();

	IntroduceSessionData(return);
	IntroduceEventData(return);

	switch (sessionData.mission)
	{
		case 3:
		{
			// Phantom

			eventData.track = 1;
			eventData.room = 10;

			sessionData.var_1F98 = 1;
			sessionData.var_1F9C = 0xE0000004;

			break;
		}
		case 4:
		{
			// Nero Angelo

			eventData.track = 1;
			eventData.room = 18;

			break;
		}
		case 8:
		{
			// Phantom

			eventData.track = 1;
			eventData.room = 4;

			break;
		}
		case 9:
		{
			// Griffin

			eventData.track = 2;
			eventData.room = 1;

			sessionData.var_1FD4 = 0x800;

			break;
		}
		case 11:
		{
			// Nero Angelo

			eventData.track = 2;
			eventData.room = 7;

			sessionData.var_1FD4 = 0x10000;

			ItemData item =
			{
				5,
				ITEM_5::SIGN_OF_CHASTITY,
				1
			};

			AddUniqueItem(item);

			break;
		}
		case 12:
		{
			// Griffin

			eventData.track = 5;
			eventData.room = 6;

			break;
		}
		case 15:
		{
			// Griffin

			eventData.track = 2;
			eventData.room = 3;

			break;
		}
		case 16:
		{
			// Nightmare

			eventData.track = 3;
			eventData.room = 10;

			break;
		}
		case 17:
		{
			// Nero Angelo

			eventData.track = 3;
			eventData.room = 21;

			break;
		}
		case 18:
		{
			// Nightmare

			eventData.track = 3;
			eventData.room = 13;

			ItemData item =
			{
				6,
				ITEM_6::PHILOSOPHERS_EGG,
				1
			};

			AddUniqueItem(item);

			break;
		}
		case 20:
		{
			// Nightmare

			eventData.track = 4;
			eventData.room = 1;

			break;
		}
		case 22:
		{
			// Mundus

			eventData.track = 4;
			eventData.room = (activeConfig.BossRush.Mission22.skipMundusPart1) ? 9 : 11;

			break;
		}
		case 23:
		{
			// Mundus

			eventData.track = 4;
			eventData.room = 10;

			break;
		}
	}
}

export void SetPosition()
{
	if (!activeConfig.BossRush.enable)
	{
		return;
	}

	LogFunction();

	auto & nextPosition = *reinterpret_cast<vec4 *>(appBaseAddr + 0x27E82A0);

	IntroduceSessionData(return);
	IntroduceEventData(return);

	IntroduceMainActorData(actorData, return);

	// nextPosition's a is rotation.

	switch (sessionData.mission)
	{
		case 3:
		{
			// Phantom

			nextPosition =
			{
				2200,
				400,
				-5200,
				-2
			};

			break;
		}
		case 4:
		{
			// Nero Angelo

			nextPosition =
			{
				5952,
				0,
				-9573,
				-0.42f
			};

			break;
		}
		case 8:
		{
			// Phantom

			nextPosition =
			{
				8500,
				6000,
				-13000,
				0
			};

			break;
		}
		case 9:
		{
			// Griffin

			nextPosition =
			{
				0,
				0,
				12850,
				-2.8f
			};

			break;
		}
		case 11:
		{
			// Nero Angelo

			nextPosition =
			{
				3500,
				2200,
				-2000,
				2
			};

			break;
		}
		case 12:
		{
			// Griffin

			nextPosition =
			{
				78,
				1234,
				-9301,
				0
			};

			break;
		}
		case 15:
		{
			// Griffin

			nextPosition =
			{
				1850,
				250,
				0,
				-1.5f
			};

			break;
		}
		case 16:
		{
			// Nightmare

			nextPosition =
			{
				15850,
				0,
				-400,
				-2.95f
			};

			break;
		}
		case 17:
		{
			// Nero Angelo

			nextPosition =
			{
				0,
				0,
				5100,
				0
			};

			break;
		}
		case 18:
		{
			// Nightmare

			nextPosition =
			{
				3100,
				0,
				0,
				2
			};

			break;
		}
		case 20:
		{
			// Nightmare

			nextPosition =
			{
				-165,
				75,
				7750,
				0
			};

			break;
		}
		case 22:
		{
			// Mundus

			nextPosition = {};

			break;
		}
		case 23:
		{
			// Mundus

			nextPosition =
			{
				38000,
				0,
				-4000,
				0
			};

			break;
		}
	}
}





export void TextEnd()
{
	if (!activeConfig.BossRush.enable)
	{
		return;
	}

	LogFunction();

	IntroduceSessionData(return);



	if (sessionData.mission == 15)
	{
		ToggleSkipText(false);
	}
}



















namespaceEnd();
