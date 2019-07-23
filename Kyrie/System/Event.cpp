#include "Event.h"

#pragma warning(disable: 4102) // Unreferenced label.

static void MissionSelect_Init()
{
	LogFunction();
	SkipIntroStart:
	{
		static bool run = false;
		if (!run)
		{
			run = true;
			if (!Config.System.Media.skipIntro)
			{
				goto SkipIntroEnd;
			}
			BYTE * addr = *(BYTE **)(appBaseAddr + 0xF59F00);
			if (!addr)
			{
				goto SkipIntroEnd;
			}
			uint32 & game = *(uint32 *)(addr + 0x1BC);
			game = Config.System.Media.skipIntroGame;
		}
	}
	SkipIntroEnd:
	return;
}

void System_Event_Init()
{
	LogFunction();
	{
		BYTE sect2[] =
		{
			0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc4.exe+1FE60
		};
		FUNC func = CreateFunction(MissionSelect_Init, (appBaseAddr + 0x110D17), true, true, 0, 0, sizeof(sect2));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteCall(func.sect2, (appBaseAddr + 0x1FE60));
		WriteJump((appBaseAddr + 0x110D12), func.addr);
	}
}
