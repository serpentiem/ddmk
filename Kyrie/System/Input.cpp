#include "Input.h"

bool System_Input_enableExtension = false;

BYTE gamepad[MAX_ACTOR][TIER2_GAMEPAD_SIZE] = {};

BYTE * gamepadAddr[MAX_ACTOR] = {};

BYTE keyboard[MAX_ACTOR][KEYBOARD_SIZE] = {};

BYTE * keyboardAddr[MAX_ACTOR] = {};

BYTE * InitTier2GamepadsProxy   = 0;
BYTE * InitKeyboardProxy        = 0;
BYTE * Tier1GamepadsUpdateLoop  = 0;
BYTE * UpdateActorInputGamepad  = 0;
BYTE * UpdateActorInputKeyboard = 0;

void System_Input_UpdateKeyboardAddr()
{
	LogFunction();
	for (uint8 actor = 0; actor < MAX_ACTOR; actor++)
	{
		keyboardAddr[actor] = keyboard[actor];
	}
	BYTE * rootAddr = *(BYTE **)(appBaseAddr + 0xF242E4);
	uint8 & actor = Config.Game.Multiplayer.keyboardActor;
	if (actor >= MAX_ACTOR)
	{
		actor = 0;
	}
	keyboardAddr[actor] = rootAddr;
}

static void InitTier2Gamepads(BYTE * rootAddr)
{
	LogFunction();
	DWORD off[MAX_ACTOR] =
	{
		0x3C,
		0x308,
		0x5D4,
		0x8A0
	};
	for (uint8 actor = 0; actor < MAX_ACTOR; actor++)
	{
		BYTE * & addr = *(BYTE **)(gamepad[actor] + 4);
		addr = (rootAddr + off[actor]);
		gamepadAddr[actor] = gamepad[actor];
	}
	gamepadAddr[ACTOR_ONE] = (rootAddr + 0xBC0);
}

static void InitKeyboard(BYTE * rootAddr)
{
	LogFunction();
	System_Input_UpdateKeyboardAddr();
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
		FUNC func = CreateFunction(InitTier2Gamepads, (appBaseAddr + 0x6EF911), true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*(BYTE **)(func.sect0 + 2) = (appBaseAddr + 0xF2432C);
		memcpy(func.sect1, sect1, sizeof(sect1));
		InitTier2GamepadsProxy = func.addr;
	}
	{
		BYTE sect0[] =
		{
			0x89, 0x35, 0x00, 0x00, 0x00, 0x00, //mov [dmc4.exe+F242E4],esi
		};
		BYTE sect1[] =
		{
			0x56, //push esi
		};
		FUNC func = CreateFunction(InitKeyboard, (appBaseAddr + 0x6E9AA2), true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*(BYTE **)(func.sect0 + 2) = (appBaseAddr + 0xF242E4);
		memcpy(func.sect1, sect1, sizeof(sect1));
		InitKeyboardProxy = func.addr;
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
			*(BYTE **)(func.sect1 + pos + 1) = gamepad[actor];
			WriteCall((func.sect1 + pos + 5), (appBaseAddr + 0x18DA40));
			pos += sizeof(sect1);
		}
		Tier1GamepadsUpdateLoop = func.addr;
	}
	{
		BYTE sect0[] =
		{
			0xA1, 0x00, 0x00, 0x00, 0x00, //mov eax,[dmc4.exe+F2432C]
		};
		BYTE sect1[] =
		{
			0x50,                                     //push eax
			0x51,                                     //push ecx
			0x52,                                     //push edx
			0x8B, 0x4D, 0x08,                         //mov ecx,[ebp+08]
			0x81, 0xE9, 0x84, 0x18, 0x00, 0x00,       //sub ecx,00001884
			0x85, 0xC9,                               //test ecx,ecx
			0x75, 0x04,                               //jne short
			0x5A,                                     //pop edx
			0x59,                                     //pop ecx
			0x58,                                     //pop eax
			0xC3,                                     //ret
			0x31, 0xD2,                               //xor edx,edx
			0x8B, 0x04, 0x95, 0x00, 0x00, 0x00, 0x00, //mov eax,[edx*4+actorBaseAddr]
			0x39, 0xC1,                               //cmp ecx,eax
			0x74, 0x0A,                               //je short
			0x42,                                     //inc edx
			0x83, 0xFA, 0x00,                         //cmp edx,MAX_ACTOR
			0x72, 0xEF,                               //jb short
			0x5A,                                     //pop edx
			0x59,                                     //pop ecx
			0x58,                                     //pop eax
			0xC3,                                     //ret
			0x8B, 0x04, 0x95, 0x00, 0x00, 0x00, 0x00, //mov eax,[edx*4+gamepadAddr]
			0x2D, 0xC0, 0x0B, 0x00, 0x00,             //sub eax,00000BC0
			0x5A,                                     //pop edx
			0x59,                                     //pop ecx
			0x83, 0xC4, 0x04,                         //add esp,04
			0xC3,                                     //ret
		};
		FUNC func = CreateFunction(0, 0, false, true, sizeof(sect0), sizeof(sect1), 0, 0, true);
		memcpy(func.sect0, sect0, sizeof(sect0));
		*(BYTE **)(func.sect0 + 1) = (appBaseAddr + 0xF2432C);
		memcpy(func.sect1, sect1, sizeof(sect1));
		*(BYTE ***)(func.sect1 + 0x19) = actorBaseAddr;
		*(uint8 *)(func.sect1 + 0x24) = MAX_ACTOR;
		*(BYTE ***)(func.sect1 + 0x2E) = gamepadAddr;
		UpdateActorInputGamepad = func.addr;
	}
	{
		BYTE sect0[] =
		{
			0x8B, 0x15, 0x00, 0x00, 0x00, 0x00, //mov edx,[dmc4.exe+F242E4]
		};
		BYTE sect1[] =
		{
			0x50,                                     //push eax
			0x51,                                     //push ecx
			0x52,                                     //push edx
			0x8B, 0x4D, 0x08,                         //mov ecx,[ebp+08]
			0x81, 0xE9, 0x84, 0x18, 0x00, 0x00,       //sub ecx,00001884
			0x85, 0xC9,                               //test ecx,ecx
			0x75, 0x04,                               //jne short
			0x5A,                                     //pop edx
			0x59,                                     //pop ecx
			0x58,                                     //pop eax
			0xC3,                                     //ret
			0x31, 0xD2,                               //xor edx,edx
			0x8B, 0x04, 0x95, 0x00, 0x00, 0x00, 0x00, //mov eax,[edx*4+actorBaseAddr]
			0x39, 0xC1,                               //cmp ecx,eax
			0x74, 0x0A,                               //je short
			0x42,                                     //inc edx
			0x83, 0xFA, 0x00,                         //cmp edx,MAX_ACTOR
			0x72, 0xEF,                               //jb short
			0x5A,                                     //pop edx
			0x59,                                     //pop ecx
			0x58,                                     //pop eax
			0xC3,                                     //ret
			0x8B, 0x14, 0x95, 0x00, 0x00, 0x00, 0x00, //mov edx,[edx*4+keyboardAddr]
			0x83, 0xC4, 0x04,                         //add esp,04
			0x59,                                     //pop ecx
			0x58,                                     //pop eax
			0xC3,                                     //ret
		};
		FUNC func = CreateFunction(0, 0, false, true, sizeof(sect0), sizeof(sect1), 0, 0, true);
		memcpy(func.sect0, sect0, sizeof(sect0));
		*(BYTE **)(func.sect0 + 2) = (appBaseAddr + 0xF242E4);
		memcpy(func.sect1, sect1, sizeof(sect1));
		*(BYTE ***)(func.sect1 + 0x19) = actorBaseAddr;
		*(uint8 *)(func.sect1 + 0x24) = MAX_ACTOR;
		*(BYTE ***)(func.sect1 + 0x2E) = keyboardAddr;
		UpdateActorInputKeyboard = func.addr;
	}

	Log("InitTier2Gamepads        %X", InitTier2GamepadsProxy);
	Log("Tier1GamepadsUpdateLoop  %X", Tier1GamepadsUpdateLoop);
	Log("UpdateActorInputGamepad  %X", UpdateActorInputGamepad);
	Log("UpdateActorInputKeyboard %X", UpdateActorInputKeyboard);

	Log("gamepad         %X", gamepad);
	for (uint8 actor = 0; actor < MAX_ACTOR; actor++)
	{
		Log("gamepad[%u]     %X", actor, gamepad[actor]);
		Log("&gamepad[%u]    %X", actor, &gamepad[actor]);
		Log("&gamepad[%u][0] %X", actor, &gamepad[actor][0]);
	}
}

void System_Input_ToggleExtension(bool enable)
{
	LogFunctionBool(enable);
	System_Input_enableExtension = enable;
	if (enable)
	{
		WriteJump((appBaseAddr + 0x6EF90B), InitTier2GamepadsProxy, 1);
		WriteJump((appBaseAddr + 0x6E9A9C), InitKeyboardProxy, 1);
		WriteJump((appBaseAddr + 0x18CEE5), Tier1GamepadsUpdateLoop);
		WriteCall((appBaseAddr + 0x4D0DC9), UpdateActorInputGamepad);
		WriteCall((appBaseAddr + 0x4D0FC3), UpdateActorInputKeyboard, 1); // Left Right X
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
		{
			BYTE * addr = (appBaseAddr + 0x6E9A9C);
			BYTE buffer[] =
			{
				0x89, 0x35, 0x00, 0x00, 0x00, 0x00, //mov [dmc4.exe+F242E4],esi
			};
			vp_memcpy(addr, buffer, sizeof(buffer));
			Write<BYTE *>((addr + 2), (appBaseAddr + 0xF242E4));
		}
		WriteCall((appBaseAddr + 0x18CEE5), (appBaseAddr + 0x18DA40));
		{
			BYTE * addr = (appBaseAddr + 0x4D0DC9);
			BYTE buffer[] =
			{
				0xA1, 0x00, 0x00, 0x00, 0x00, //mov eax,[dmc4.exe+F2432C]
			};
			vp_memcpy(addr, buffer, sizeof(buffer));
			Write<BYTE *>((addr + 1), (appBaseAddr + 0xF2432C));
		}
		{
			BYTE * addr = (appBaseAddr + 0x4D0FC3);
			BYTE buffer[] =
			{
				0x8B, 0x15, 0x00, 0x00, 0x00, 0x00, //mov edx,[dmc4.exe+F242E4]
			};
			vp_memcpy(addr, buffer, sizeof(buffer));
			Write<BYTE *>((addr + 2), (appBaseAddr + 0xF242E4));
		}
	}
}
