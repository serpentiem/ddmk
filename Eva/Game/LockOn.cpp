#include "LockOn.h"

////#pragma warning(disable: 4102) // Unreferenced Label

WORD Game_LockOn_buttonMap[16] =
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

static DWORD DisableHoldRestrictionThread(LPVOID parameter)
{
	float32 timer = 0;
	do
	{
		LoopStart:
		{
			if (!Config.Game.LockOn.enable)
			{
				goto LoopEnd;
			}
			if (!InGame())
			{
				goto LoopEnd;
			}
			BYTE * actorBaseAddr = *(BYTE **)(appBaseAddr + 0x60ACD0);
			uint8 meleeWeapon = *(uint8 *)(actorBaseAddr + 0x1BCC);
			if (meleeWeapon == WEAPON_SPARDA_AERIAL)
			{
				goto LoopEnd;
			}
			uint8 weapon = *(uint8 *)(actorBaseAddr + 0x1C48);
			if (GetButtonState() & Config.Game.LockOn.button)
			{
				switch (weapon)
				{
				case WEAPON_HANDGUN:
					timer = 300;
					break;
				case WEAPON_SHOTGUN:
					timer = 900;
					break;
				case WEAPON_GRENADEGUN:
					timer = 1700;
					break;
				case WEAPON_NIGHTMARE_BETA:
					timer = 1200;
					break;
				}
				WriteAddress((appBaseAddr + 0x2CB31E), (appBaseAddr + 0x2CB320), 2); // Enable
			}
			if (timer > 0)
			{
				timer -= 10;
			}
			else
			{
				WriteAddress((appBaseAddr + 0x2CB31E), (appBaseAddr + 0x2CB336), 2); // Disable
			}
		}
		LoopEnd:
		Sleep(10);
	}
	while (true);
	return 1;
}

DWORD OmniChargeThread(LPVOID parameter)
{
	do
	{
		LoopStart:
		{
			if (!Config.Game.LockOn.enable)
			{
				goto LoopEnd;
			}
			if (!InGame())
			{
				goto LoopEnd;
			}
			BYTE * actorBaseAddr = *(BYTE **)(appBaseAddr + 0x60ACD0);
			int16 & chargeEffect = *(int16 *)(actorBaseAddr + 0x1C66);
			int16 & chargeAttack = *(int16 *)(actorBaseAddr + 0x1C68);

			if (GetButtonState() & GAMEPAD_X)
			{
				if (chargeAttack == 0)
				{
					chargeEffect += 12;
				}
			}
			else
			{
				if (chargeEffect >= 100)
				{
					chargeAttack = 30;
				}
				chargeEffect -= 12;
			}

			if (chargeEffect > 120)
			{
				chargeEffect = 120;
			}

			if (chargeEffect < 0)
			{
				chargeEffect = 0;
			}
		}
		LoopEnd:
		Sleep(100);
	}
	while (true);
	return 1;
}

void Game_LockOn_Init()
{
	LogFunction();
	CreateThread(0, 4096, DisableHoldRestrictionThread, 0, 0, 0);
	CreateThread(0, 4096, OmniChargeThread, 0, 0, 0);
}

void Game_LockOn_Toggle(bool enable)
{
	LogFunction(enable);
	if (enable)
	{
		vp_memset((appBaseAddr + 0x2CB655), 0x90, 7);                        // Remove Write Instructions
		vp_memset((appBaseAddr + 0x2F0734), 0x90, 7);                        // ..
		vp_memset((appBaseAddr + 0x2F0691), 0x90, 7);                        // ..
		vp_memset((appBaseAddr + 0x2F06DC), 0x90, 7);                        // ..
		vp_memset((appBaseAddr + 0x2F0756), 0x90, 7);                        // ..
		vp_memset((appBaseAddr + 0x2F071B), 0x90, 7);                        // Fix Auto-Shoot
		WriteAddress((appBaseAddr + 0x2ECAD1), (appBaseAddr + 0x2ECAD3), 2); // .. Aerial
	}
	else
	{
		{
			BYTE buffer[] =
			{
				0x66, 0x89, 0xB3, 0x66, 0x1C, 0x00, 0x00, //mov [rbx+00001C66],si
			};
			vp_memcpy((appBaseAddr + 0x2CB655), buffer, sizeof(buffer));
		}
		{
			BYTE buffer[] =
			{
				0x66, 0x89, 0x91, 0x66, 0x1C, 0x00, 0x00, //mov [rcx+00001C66],dx
			};
			vp_memcpy((appBaseAddr + 0x2F0734), buffer, sizeof(buffer));
		}
		{
			BYTE buffer[] =
			{
				0x66, 0xFF, 0x81, 0x66, 0x1C, 0x00, 0x00, //inc word ptr [rcx+00001C66]
			};
			vp_memcpy((appBaseAddr + 0x2F0691), buffer, sizeof(buffer));
		}
		{
			BYTE buffer[] =
			{
				0x66, 0x89, 0x83, 0x66, 0x1C, 0x00, 0x00, //mov [rbx+00001C66],ax
			};
			vp_memcpy((appBaseAddr + 0x2F06DC), buffer, sizeof(buffer));
		}
		{
			BYTE buffer[] =
			{
				0x66, 0x89, 0x93, 0x66, 0x1C, 0x00, 0x00, //mov [rbx+00001C66],dx
			};
			vp_memcpy((appBaseAddr + 0x2F0756), buffer, sizeof(buffer));
		}
		{
			BYTE buffer[] =
			{
				0xC6, 0x81, 0xE0, 0x1B, 0x00, 0x00, 0x08, //mov byte ptr [rcx+00001BE0],08
			};
			vp_memcpy((appBaseAddr + 0x2F071B), buffer, sizeof(buffer));
		}
		WriteAddress((appBaseAddr + 0x2ECAD1), (appBaseAddr + 0x2ECAD9), 2);
	}
}
