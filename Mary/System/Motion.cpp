#include "Motion.h"

bool System_Motion_update[MAX_ACTOR] = {};

void SetUpdateFlag(byte8 * baseAddr)
{
	auto actor = GetActorId(baseAddr);
	System_Motion_update[actor] = true;
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
		WriteJump((appBaseAddr + 0x1EFC86), func.addr, 2);
	}
}
