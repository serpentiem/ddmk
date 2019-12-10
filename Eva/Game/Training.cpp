#include "Training.h"

void Game_Training_ToggleInfiniteHitPoints(bool enable)
{
	LogFunction(enable);
	if (enable)
	{
		vp_memset((appBaseAddr + 0x4FA0A), 0x90, 3);
		vp_memset((appBaseAddr + 0x4FA28), 0x90, 8);
		Write<BYTE>((appBaseAddr + 0x4FA30), 0xEB);
	}
	else
	{
		{
			BYTE payload[] =
			{
				0x66, 0x2B, 0xC8, //sub cx,ax
			};
			vp_memcpy((appBaseAddr + 0x4FA0A), payload, sizeof(payload));
		}
		{
			BYTE payload[] =
			{
				0x66, 0x41, 0x29, 0x82, 0xA2, 0x17, 0x00, 0x00, //sub [r10+000017A2],ax
			};
			vp_memcpy((appBaseAddr + 0x4FA28), payload, sizeof(payload));
			Write<BYTE>((appBaseAddr + 0x4FA30), 0x79);
		}
	}
}

void Game_Training_ToggleInfiniteMagicPoints(bool enable)
{
	LogFunction(enable);
	if (enable)
	{
		vp_memset((appBaseAddr + 0x2ECD80), 0x90, 7); // Devil Default
		vp_memset((appBaseAddr + 0x2ECD9B), 0x90, 3); // Alastor Aerial
		Write<int8>((appBaseAddr + 0x2D980E), 0);     // Ifrit Kick 13
		vp_memset((appBaseAddr + 0x2DCE9A), 0x90, 3); // Ifrit Meteor
		Write<int8>((appBaseAddr + 0x2DC75F), 0);     // Ifrit Inferno
		vp_memset((appBaseAddr + 0x2D4FE4), 0x90, 8); // Sparda Aerial Summon Dragon
		Write<int8>((appBaseAddr + 0x2D658A), 0);     // Sparda Melee Attack
		Write<int8>((appBaseAddr + 0x2D58F2), 0);     // Sparda Fireball
		Write<int8>((appBaseAddr + 0x2D61D2), 0);     // Sparda Fireball Charging
		vp_memset((appBaseAddr + 0x2D6267), 0x90, 3); // Sparda Fireball Charging
		Write<int8>((appBaseAddr + 0x2ECD7A), 0);     // Bangle of Time
		Write<int16>((appBaseAddr + 0x2ECF79), 0);    // Devil Revert
		vp_memset((appBaseAddr + 0x2ECFA7), 0x90, 7); // Human Revert
		Write<uint8>(appBaseAddr + 0x2F78CE, 0);      // Nightmare Beta Shot
		Write<uint8>(appBaseAddr + 0x2F7AF3, 0);      // .. Charge
		Write<uint8>(appBaseAddr + 0x2F4723, 0);      // .. Aerial Shot
	}
	else
	{
		{
			BYTE buffer[] =
			{
				0x66, 0xFF, 0x8B, 0xD2, 0x1B, 0x00, 0x00, //dec word ptr [rbx+00001BD2]
			};
			vp_memcpy((appBaseAddr + 0x2ECD80), buffer, sizeof(buffer));
		}
		{
			BYTE buffer[] =
			{
				0x66, 0xFF, 0xC9, //dec cx
			};
			vp_memcpy((appBaseAddr + 0x2ECD9B), buffer, sizeof(buffer));
		}
		Write<int8>((appBaseAddr + 0x2D980E), -4);
		{
			BYTE buffer[] =
			{
				0x66, 0xFF, 0xC8, //dec ax
			};
			vp_memcpy((appBaseAddr + 0x2DCE9A), buffer, sizeof(buffer));
		}
		Write<int8>((appBaseAddr + 0x2DC75F), -8);
		{
			BYTE buffer[] =
			{
				0x66, 0x44, 0x89, 0xBB, 0xCE, 0x1B, 0x00, 0x00, //mov [rbx+00001BCE],r15w
			};
			vp_memcpy((appBaseAddr + 0x2D4FE4), buffer, sizeof(buffer));
		}
		Write<int8>((appBaseAddr + 0x2D658A), 1);
		Write<int8>((appBaseAddr + 0x2D58F2), -10);
		Write<int8>((appBaseAddr + 0x2D61D2), -2);
		{
			BYTE buffer[] =
			{
				0x66, 0xFF, 0xC8, //dec ax
			};
			vp_memcpy((appBaseAddr + 0x2D6267), buffer, sizeof(buffer));
		}
		Write<int8>((appBaseAddr + 0x2ECD7A), -2);
		Write<int16>((appBaseAddr + 0x2ECF79), -200);
		{
			BYTE buffer[] =
			{
				0x66, 0x89, 0x83, 0xCE, 0x1B, 0x00, 0x00, //mov [rbx+00001BCE],ax
			};
			vp_memcpy((appBaseAddr + 0x2ECFA7), buffer, sizeof(buffer));
		}
		Write<uint8>(appBaseAddr + 0x2F78CE, 120);
		Write<uint8>(appBaseAddr + 0x2F7AF3, 2);
		Write<uint8>(appBaseAddr + 0x2F4723, 120);
	}
}

void Game_Training_ToggleDisableTimer(bool enable)
{
	LogFunction(enable);
	if (enable)
	{
		vp_memset((appBaseAddr + 0x252374), 0x90, 2);  // Sub Timer
		Write<WORD>((appBaseAddr + 0x2522FA), 0xE990); // Hide Timer
	}
	else
	{
		BYTE payload[] =
		{
			0xFF, 0xC9, //dec ecx
		};
		vp_memcpy((appBaseAddr + 0x252374), payload, sizeof(payload));
		Write<WORD>((appBaseAddr + 0x2522FA), 0x840F);
	}
}
