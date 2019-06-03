#include "ResetMotionState.h"


#pragma warning(disable: 4102) // Unreferenced Label



WORD Game_ResetMotionState_buttonMask[16] =
{
	GAMEPAD_LEFT_TRIGGER,
	GAMEPAD_RIGHT_TRIGGER,
	GAMEPAD_LEFT_SHOULDER,
	GAMEPAD_RIGHT_SHOULDER,
	GAMEPAD_Y,
	GAMEPAD_B,
	GAMEPAD_A,
	GAMEPAD_X,
	GAMEPAD_BACK,
	GAMEPAD_LEFT_THUMB,
	GAMEPAD_RIGHT_THUMB,
	GAMEPAD_START,
	GAMEPAD_DPAD_UP,
	GAMEPAD_DPAD_RIGHT,
	GAMEPAD_DPAD_DOWN,
	GAMEPAD_DPAD_LEFT,
};

















static void ResetMotionState()
{
	//BYTE ** actorBaseAddr = (BYTE **)(appBaseAddr + 0x4CB6BA0 + 8);
	//if (!actorBaseAddr[ACTOR_ONE])
	//{
	//	return;
	//}
	//BYTE & motionState = *(BYTE *)(actorBaseAddr[ACTOR_ONE] + 1);
	//motionState = 0;

	
	
	BYTE * addr = *(BYTE **)(appBaseAddr + 0x60ACD0);
	if (!addr)
	{
		return;
	}

	DWORD & motionState = *(DWORD *)addr;
	motionState = 1;




	
	/*
	dmc1.exe+60ACD0
	*/







}

static DWORD ResetMotionStateThread(LPVOID parameter)
{
	LogFunction();
	do
	{
		LoopStart:
		{
			if (!Config.Game.ResetMotionState.enable)
			{
				goto LoopEnd;
			}
			static bool execute = true;
			WORD state = GetButtonState();
			if (state & Config.Game.ResetMotionState.button)
			{
				if (execute)
				{
					ResetMotionState();
					execute = false;
				}
			}
			else
			{
				execute = true;
			}
		}
		LoopEnd:
		Sleep(Config.Game.ResetMotionState.updateRate);
	}
	while (true);
	return 1;
}

void Game_ResetMotionState_Init()
{
	LogFunction();
	CreateThread(0, 4096, ResetMotionStateThread, 0, 0, 0);
}
