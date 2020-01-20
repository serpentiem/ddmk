#include "Update.h"

uint64 ticksPerSecond      = 0;
uint64 ticksPerMillisecond = 0;
uint64 savedTickCount      = 0;

// uint64 counter = 0;

//void InGameMenuAccess()
//{
//	Game_StyleSwitcher_Controller();
//	Game_ResetMotionState_Controller();
//	System_HUD_Update();
//}

void MainLoop()
{
	uint64 tickCount           = 0;
	uint32 elapsedMilliseconds = 0;

	Windows_GetTickCount(&tickCount);
	elapsedMilliseconds = (uint32)((tickCount - savedTickCount) / ticksPerMillisecond);

	if (elapsedMilliseconds >= 1000)
	{
		savedTickCount = tickCount;
	}

	InGameStart:
	{
		if (!InGame())
		{
			goto InGameEnd;
		}
		if (Config.Game.StyleSwitcher.enable)
		{
			Game_StyleSwitcher_Controller();
		}
		if (Config.Game.ResetMotionState.enable)
		{
			Game_ResetMotionState_Controller();
		}
		System_HUD_Update();

		CameraStart:
		{
			if (!Config.Camera.applyConfig)
			{
				goto CameraEnd;
			}
			uint32 remainder = (elapsedMilliseconds % Config.Camera.rate);
			if (!remainder)
			{
				Camera_Update(Config);
			}
		}
		CameraEnd:;
	}
	InGameEnd:;
}

// Wow, same crap.

void Update_Init()
{
	LogFunction();
	Windows_GetTicksPerSecond(&ticksPerSecond);
	ticksPerMillisecond = (ticksPerSecond / 1000);
	Windows_GetTickCount(&savedTickCount);
	{
		byte8 sect0[] =
		{
			0x48, 0x8D, 0x4C, 0x24, 0x20, //lea rcx,[rsp+20]
		};
		auto func = CreateFunction(MainLoop, (appBaseAddr + 0x2C5EB5), true, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteJump((appBaseAddr + 0x2C5EB0), func.addr);
		/*
		dmc3.exe+2C5EB0 - 48 8D 4C 24 20 - lea rcx,[rsp+20]
		dmc3.exe+2C5EB5 - FF 15 1D930800 - call qword ptr [dmc3.exe+34F1D8]
		*/
	}
	{
		//byte8 sect0[] =
		//{
		//	0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc3.exe+23B060
		//};
		//FUNC func = CreateFunction(MainLoop, (appBaseAddr + 0x23D4B7), true, true, sizeof(sect0));
		//memcpy(func.sect0, sect0, sizeof(sect0));
		//WriteCall(func.sect0, (appBaseAddr + 0x23B060));
		//WriteJump((appBaseAddr + 0x23D4B2), func.addr);
		/*
		dmc3.exe+23D4B2 - E8 A9DBFFFF           - call dmc3.exe+23B060
		dmc3.exe+23D4B7 - 84 C0                 - test al,al
		*/
	}
}
