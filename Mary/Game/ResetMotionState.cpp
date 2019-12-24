#include "ResetMotionState.h"

uint8 Game_ResetMotionState_buttonIndex = 0;
byte16 Game_ResetMotionState_buttonMap[16] =
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
	GAMEPAD_UP,
	GAMEPAD_RIGHT,
	GAMEPAD_DOWN,
	GAMEPAD_LEFT,
};

PrivateStart;

uint32 Thread(LPVOID parameter)
{
	do
	{
		LoopStart:
		{
			if (!Config.Game.ResetMotionState.enable)
			{
				goto LoopEnd;
			}
			if (!InGame())
			{
				goto LoopEnd;
			}
			static bool execute[MAX_ACTOR] = {};
			auto count = GetActorCount();
			for (uint8 actor = 0; actor < count; actor++)
			{
				if (System_Input_GetButtonState(actor) & Config.Game.ResetMotionState.button)
				{
					if (execute[actor])
					{
						auto & motionState = *(byte8 *)(System_Actor_actorBaseAddr[actor] + 0x3E66) = 0;
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
		Sleep(10);
	}
	while (true);
	return 1;
}

PrivateEnd;

void Game_ResetMotionState_Init()
{
	LogFunction();
	CreateThread(0, 4096, Thread, 0, 0, 0);
}
