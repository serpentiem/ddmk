#include "Input.h"

bool System_Input_enableExtension    = false;
MGO  System_Input_gamepad[MAX_ACTOR] = {};

BYTE * LinkGamepadsProxy = 0;


// @Todo: Not a real proxy.

BYTE * ExtendLoopProxy   = 0;

static void LinkGamepads(BYTE * rootAddr)
{
	LogFunction();
	uint32 off[MAX_ACTOR] =
	{
		0x3C,
		0x308,
		0x5D4,
		0x8A0
	};
	for (uint8 actor = ACTOR_TWO; actor < MAX_ACTOR; actor++)
	{
		// The BYTE * cast shouldn't be necessary.
		// Sometimes the compiler is seriously fucked up.
		BYTE * & addr = *(BYTE **)((BYTE *)&System_Input_gamepad[actor] + 4);
		addr = (rootAddr + off[actor]);
	}
}

void System_Input_Init()
{
	LogFunction();
	{
		BYTE sect0[] =
		{
			0x89, 0x35, 0x00, 0x00, 0x00, 0x00, //mov [dmc4.exe+F2432C],esi
		};
		BYTE sect1[] =
		{
			0x56, //push esi
		};
		FUNC func = CreateFunction(LinkGamepads, (appBaseAddr + 0x6EF911), true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		*(BYTE **)(func.sect0 + 2) = (appBaseAddr + 0xF2432C);
		LinkGamepadsProxy = func.addr;
	}
	{
		BYTE sect0[] =
		{
			0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc4.exe+18DA40
		};
		BYTE sect1[] =
		{
			0xBE, 0x00, 0x00, 0x00, 0x00, //mov esi
			0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc4.exe+18DA40
		};
		FUNC func = CreateFunction(0, (appBaseAddr + 0x18CEEA), false, false, sizeof(sect0), (sizeof(sect1) * (MAX_ACTOR - 1)));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteCall(func.sect0, (appBaseAddr + 0x18DA40));
		uint32 pos = 0;
		for (uint8 actor = ACTOR_TWO; actor < MAX_ACTOR; actor++)
		{
			memcpy((func.sect1 + pos), sect1, sizeof(sect1));
			*(MGO **)(func.sect1 + pos + 1) = &System_Input_gamepad[actor];
			WriteCall((func.sect1 + pos + 5), (appBaseAddr + 0x18DA40));
			pos += sizeof(sect1);
		}
		
		
		
		
		ExtendLoopProxy = func.addr;
	}
	Log("LinkGamepads %X", LinkGamepadsProxy);
	Log("ExtendLoop   %X", ExtendLoopProxy);



	Log("System_Input_gamepad %X", System_Input_gamepad);
	Log("&System_Input_gamepad[0] %X", &System_Input_gamepad[0]);
	Log("&System_Input_gamepad %X", &System_Input_gamepad);
	






}

void System_Input_ToggleExtension(bool enable)
{
	LogFunctionBool(enable);
	System_Input_enableExtension = enable;
	if (enable)
	{
		WriteJump((appBaseAddr + 0x6EF90B), LinkGamepadsProxy, 1);
		WriteJump((appBaseAddr + 0x18CEE5), ExtendLoopProxy);
	}
	else
	{
		{
			BYTE * addr = (appBaseAddr + 0x6EF90B);
			BYTE buffer[] =
			{
				0x89, 0x35, 0x00, 0x00, 0x00, 0x00, //mov [dmc4.exe+F2432C],esi
			};
			vp_memcpy(addr, buffer, sizeof(buffer));
			Write<BYTE *>((addr + 2), (appBaseAddr + 0xF2432C));
		}
		WriteCall((appBaseAddr + 0x18CEE5), (appBaseAddr + 0x18DA40));
	}
}
