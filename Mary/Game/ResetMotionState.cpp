#include "ResetMotionState.h"

////#pragma warning(disable: 4102) // unreferenced label


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


//static void Reset(BYTE * baseAddr)
//{
//	DWORD & motionState = *(DWORD *)(baseAddr + 0x3E64);
//	motionState = 1;
//}

static DWORD Thread(LPVOID parameter)
{
	do
	{
		LoopStart:
		{
			if (!Config.Game.ResetMotionState.enable)
			{
				goto LoopEnd;
			}
			if (!System_Actor_enable)
			{
				goto LoopEnd;
			}
			if (!InGame())
			{
				goto LoopEnd;
			}
			static bool execute[MAX_ACTOR] = {};
			uint8 actorCount = GetActorCount();
			for (uint8 actor = 0; actor < actorCount; actor++)
			{
				if (GetButtonState(actor) & Config.Game.ResetMotionState.button)
				{
					if (execute[actor])
					{
						//Reset(actorBaseAddr[actor]);


						BYTE & motionState = *(BYTE *)(actorBaseAddr[actor] + 0x3E66);
						motionState = 0;


						//DWORD & motionState = *(DWORD *)(baseAddr + 0x3E64);
						//motionState = 1;




						execute[actor] = false;
					}
				}
				else
				{
					execute[actor] = true;
				}
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
	CreateThread(0, 4096, Thread, 0, 0, 0);
}
