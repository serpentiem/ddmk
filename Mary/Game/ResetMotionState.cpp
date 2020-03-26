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

void Game_ResetMotionState_UpdateButtonIndex()
{
	auto & buttonIndex = Game_ResetMotionState_buttonIndex;
	auto & buttonMap   = Game_ResetMotionState_buttonMap;
	for (uint8 index = 0; index < countof(buttonMap); index++)
	{
		if (buttonMap[index] == Config.Game.ResetMotionState.button)
		{
			buttonIndex = index;
			break;
		}
	}
}

void Game_ResetMotionState_Controller()
{
	//if (!Config.Game.ResetMotionState.enable)
	//{
	//	return;
	//}
	//static bool execute[MAX_ACTOR] = {};
	//auto count = System_Actor_GetActorCount();
	//for (uint8 actor = 0; actor < count; actor++)
	//{
	//	if (System_Input_GetButtonState(actor) & Config.Game.ResetMotionState.button)
	//	{
	//		if (execute[actor])
	//		{
	//			//auto & motionState = *(byte8 *)(System_Actor_actorBaseAddr[actor] + 0x3E66) = 0;
	//			execute[actor] = false;
	//		}
	//	}
	//	else
	//	{
	//		execute[actor] = true;
	//	}
	//}
}
