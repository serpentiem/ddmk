#include "Update.h"

uint64 ticksPerSecond      = 0;
uint64 ticksPerMillisecond = 0;
uint64 savedTickCount      = 0;

bool millionStab = false;

void VergilMillionStab()
{
	auto addr = *(byte8 ***)(appBaseAddr + 0xC90E28);
	if (!addr)
	{
		return;
	}
	if (!addr[3])
	{
		return;
	}

	auto baseAddr = addr[3];

	auto & motionGroup           = *(uint8  *)(baseAddr + 0x39B3);
	auto & motionIndex           = *(uint8  *)(baseAddr + 0x39B2);
	auto & move                  = *(uint8  *)(baseAddr + 0x3FA4);
	auto & meleeInputBufferLevel = *(uint8  *)(baseAddr + 0x6738);


	if (move == 39) // Force Edge Stinger Level 2
	{
		if (motionGroup == 5)
		{
			if (motionIndex == 11)
			{
				if (meleeInputBufferLevel >= 6)
				{
					Log("Trigger Million Stab!");
					if (!millionStab)
					{
						millionStab = true;


						addr[3] = System_Actor_actorBaseAddr[ACTOR_ONE];
						addr[4] = System_Actor_actorBaseAddr[ACTOR_TWO];






						baseAddr = addr[3];



						
						auto & x1 = *(float32 *)(baseAddr + 0x80);
						auto & y1 = *(float32 *)(baseAddr + 0x84);
						auto & z1 = *(float32 *)(baseAddr + 0x88);

						auto & x2 = *(float32 *)(addr[4] + 0x80);
						auto & y2 = *(float32 *)(addr[4] + 0x84);
						auto & z2 = *(float32 *)(addr[4] + 0x88);

						auto x = x2;
						auto y = y2;
						auto z = z2;

						x2 = x1;
						y2 = y1;
						z2 = z1;

						x1 = x;
						y1 = y;
						z1 = z;



						auto & actorId1 = *(uint8 *)(baseAddr + 0x118) = 0;
						auto & actorId2 = *(uint8 *)(addr[4] + 0x118) = 1;


						auto & motionState1          = *(byte32 *)(baseAddr + 0x3E00);
						auto & motionState2          = *(byte32 *)(baseAddr + 0x3E04);
						auto & motionState3          = *(byte32 *)(baseAddr + 0x3E08);
						auto & motionState4          = *(byte32 *)(baseAddr + 0x3E0C);
						auto & motionState5          = *(byte32 *)(baseAddr + 0x3E60);
						auto & motionState6          = *(byte32 *)(baseAddr + 0x3E64);
						auto & motionState7          = *(byte32 *)(baseAddr + 0x3E68);
						auto & move                  = *(uint8  *)(baseAddr + 0x3FA4);


						motionState1 = 0x11;
						motionState2 = 1;
						motionState3 = 0x11;
						motionState4 = 0x11;

						motionState5 = 0x401;
						motionState6 = 0x10001;
						motionState7 = 0x10001;

						move = 14;











					}










				}






			}
		}




	}













}



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



	VergilMillionStab();










	InGameStart:
	{
		//if (!InGame())
		//{
		//	goto InGameEnd;
		//}
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
	//{
	//	byte8 sect0[] =
	//	{
	//		0x48, 0x8D, 0x4C, 0x24, 0x20, //lea rcx,[rsp+20]
	//	};
	//	auto func = CreateFunction(MainLoop, (appBaseAddr + 0x2C5EB5), true, true, sizeof(sect0));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	WriteJump((appBaseAddr + 0x2C5EB0), func.addr);
	//	/*
	//	dmc3.exe+2C5EB0 - 48 8D 4C 24 20 - lea rcx,[rsp+20]
	//	dmc3.exe+2C5EB5 - FF 15 1D930800 - call qword ptr [dmc3.exe+34F1D8]
	//	*/
	//}
	{
		byte8 sect0[] =
		{
			0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc3.exe+23B060
		};
		FUNC func = CreateFunction(MainLoop, (appBaseAddr + 0x23D4B7), true, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteCall(func.sect0, (appBaseAddr + 0x23B060));
		WriteJump((appBaseAddr + 0x23D4B2), func.addr);
		/*
		dmc3.exe+23D4B2 - E8 A9DBFFFF - call dmc3.exe+23B060
		dmc3.exe+23D4B7 - 84 C0       - test al,al
		*/
	}
}
