
// @Todo: Auto vars and add Input namespace.

#include "Doppelganger.h"

PrivateStart;

byte8 * DoppelgangerRateControllerProxy = 0;
byte8 * AdjustDevilSound                = 0;

void DoppelgangerRateController(byte8 * baseAddr)
{
	static bool execute = false;
	if ((System_Input_GetButtonState(ACTOR_ONE) & System_Input_GetBinding(CMD_LOCK_ON)) && (System_Input_GetButtonState(ACTOR_ONE) & System_Input_GetBinding(CMD_TAUNT)))
	{
		if (execute)
		{
			uint32 & rate = *(uint32 *)(baseAddr + 0x6450);
			rate++;
			if (rate > 2)
			{
				rate = 0;
			}
			execute = false;
		}
	}
	else
	{
		execute = true;
	}
}

PrivateEnd;

void Game_Doppelganger_Init()
{
	LogFunction();
	{
		FUNC func = CreateFunction(DoppelgangerRateController);
		DoppelgangerRateControllerProxy = func.addr;
	}
	{
		byte8 sect0[] =
		{
			0x80, 0xBF, 0x62, 0x63, 0x00, 0x00, 0x01, //cmp byte ptr [rdi+00006362],01
			0x0F, 0x84, 0x00, 0x00, 0x00, 0x00,       //je dmc3.exe+1F8FA1
			0x80, 0xBF, 0x9B, 0x3E, 0x00, 0x00, 0x01, //cmp byte ptr [rdi+00003E9B],01
			0x0F, 0x85, 0x00, 0x00, 0x00, 0x00,       //jne dmc3.exe+1F8FA1
		};
		FUNC func = CreateFunction(0, (appBaseAddr + 0x1F8F35), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteAddress((func.sect0 + 7), (appBaseAddr + 0x1F8FA1), 6);
		WriteAddress((func.sect0 + 0x14), (appBaseAddr + 0x1F8FA1), 6);
		WriteJump((func.sect0 + 0x1A), (appBaseAddr + 0x1F8F35));
		AdjustDevilSound = func.addr;
	}
}

void Game_Doppelganger_ToggleEnableDevilTrigger(bool enable)
{
	LogFunction(enable);
	if (enable)
	{
		WriteCall((appBaseAddr + 0x1E25CD), DoppelgangerRateControllerProxy);
		WriteJump((appBaseAddr + 0x1F8F2C), AdjustDevilSound, 2);
		// Fixes
		Write<uint32>((appBaseAddr + 0x1E92BB), 0);                          // Disable Doppelganger Activation Devil Form
		Write<byte>((appBaseAddr + 0x1EAA07), 0xEB);                         // Disable Doppelganger Melee Weapon Change Devil Form Update
		Write<byte>((appBaseAddr + 0x1E7775), 0xEB);                         // Enable Devil Trigger Activation
		Write<byte>((appBaseAddr + 0x1F94A1), 0xEB);                         // Enable Devil Trigger Deactivation
		WriteAddress((appBaseAddr + 0x1E752B), (appBaseAddr + 0x1E752D), 2); // Enable ACTOR_TWO Devil Trigger
		Write<uint32>((appBaseAddr + 0x1F7D3F), 0);                          // Bob Set Visible Flag
	}
	else
	{
		WriteCall((appBaseAddr + 0x1E25CD), (appBaseAddr + 0x1E8F00));
		{
			byte buffer[] =
			{
				0x80, 0xBF, 0x9B, 0x3E, 0x00, 0x00, 0x01, //cmp byte ptr [rdi+00003E9B],01
			};
			vp_memcpy((appBaseAddr + 0x1F8F2C), buffer, sizeof(buffer));
		}
		Write<uint32>((appBaseAddr + 0x1E92BB), 1);
		Write<byte>((appBaseAddr + 0x1EAA07), 0x75);
		Write<byte>((appBaseAddr + 0x1E7775), 0x75);
		Write<byte>((appBaseAddr + 0x1F94A1), 0x74);
		WriteAddress((appBaseAddr + 0x1E752B), (appBaseAddr + 0x1E7516), 2);
		Write<uint32>((appBaseAddr + 0x1F7D3F), 1);
	}
}
