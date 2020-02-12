#include "Motion.h"





bool System_Motion_update[MAX_ACTOR] = {};

void SetUpdateFlag(byte8 * baseAddr)
{
	auto actor = System_Actor_GetActorId(baseAddr);
	System_Motion_update[actor] = true;


	//auto & motionGroup = *(uint8 *)(baseAddr + 0x39B3);
	//auto & motionIndex = *(uint8 *)(baseAddr + 0x39B2);

	//if (motionGroup == MOT_VERGIL_FORCE_EDGE)
	//{
	//	if (motionIndex == 11)
	//	{

	//		motionGroup = MOT_VERGIL_YAMATO;
	//		motionIndex = 12;


	//	}
	//}



}

void System_Motion_Init()
{
	LogFunction();
	{
		byte8 sect0[] =
		{
			0x66, 0x89, 0xAE, 0xB2, 0x39, 0x00, 0x00, //mov [rsi+000039B2],bp
		};
		byte8 sect1[] =
		{
			0x48, 0x8B, 0xCE, //mov rcx,rsi
		};
		FUNC func = CreateFunction(SetUpdateFlag, (appBaseAddr + 0x1EFC8D), true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		//WriteJump((appBaseAddr + 0x1EFC86), func.addr, 2);
	}
}
