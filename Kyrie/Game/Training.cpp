#include "Training.h"

void Game_Training_ToggleInfiniteHitPoints(bool enable)
{
	LogFunctionBool(enable);
	if (enable)
	{
		vp_memset((appBaseAddr + 0x22DDD4), 0x90, 4);
	}
	else
	{
		BYTE buffer[] =
		{
			0xF3, 0x0F, 0x5C, 0xC1, //subss xmm0,xmm1
		};
		vp_memcpy((appBaseAddr + 0x22DDD4), buffer, sizeof(buffer));
	}
}

void Game_Training_ToggleInfiniteMagicPoints(bool enable)
{
	LogFunctionBool(enable);
	if (enable)
	{
		vp_memset((appBaseAddr + 0x4C87A9), 0x90, 8); // Dante, Nero, Vergil, Trish Flux
		vp_memset((appBaseAddr + 0x4C889E), 0x90, 8); // Dante, Nero, Vergil, Trish Periodic
		vp_memset((appBaseAddr + 0x4D004B), 0x90, 8); // Dante Stinger Kick 13, Vergil Lunar Phase Rising Sun Stinger
		vp_memset((appBaseAddr + 0x5028FC), 0x90, 8); // Dante Lucifer Pin-Up
		vp_memset((appBaseAddr + 0x8E42C ), 0x90, 8); // Lady Burst Attack
		vp_memset((appBaseAddr + 0x8E436 ), 0x90, 8); // Lady Burst Attack Reset
		vp_memset((appBaseAddr + 0x8E9FB ), 0x90, 8); // Lady Burst Attack Air
		vp_memset((appBaseAddr + 0x8EA05 ), 0x90, 8); // Lady Burst Attack Reset Air
	}
	else
	{
		{
			BYTE buffer[] =
			{
				0xF3, 0x0F, 0x11, 0x86, 0x04, 0x25, 0x00, 0x00, //movss [esi+00002504],xmm0
			};
			vp_memcpy((appBaseAddr + 0x4C87A9), buffer, sizeof(buffer));
		}
		{
			BYTE buffer[] =
			{
				0xF3, 0x0F, 0x11, 0x86, 0x04, 0x25, 0x00, 0x00, //movss [esi+00002504],xmm0
			};
			vp_memcpy((appBaseAddr + 0x4C889E), buffer, sizeof(buffer));
		}
		{
			BYTE buffer[] =
			{
				0xF3, 0x0F, 0x11, 0x86, 0x04, 0x25, 0x00, 0x00, //movss [esi+00002504],xmm0
			};
			vp_memcpy((appBaseAddr + 0x4D004B), buffer, sizeof(buffer));
		}
		{
			BYTE buffer[] =
			{
				0xF3, 0x0F, 0x11, 0x86, 0x04, 0x25, 0x00, 0x00, //movss [esi+00002504],xmm0
			};
			vp_memcpy((appBaseAddr + 0x5028FC), buffer, sizeof(buffer));
		}
		{
			BYTE buffer[] =
			{
				0xF3, 0x0F, 0x11, 0x86, 0x04, 0x25, 0x00, 0x00, //movss [esi+00002504],xmm0
			};
			vp_memcpy((appBaseAddr + 0x8E42C), buffer, sizeof(buffer));
		}
		{
			BYTE buffer[] =
			{
				0xF3, 0x0F, 0x11, 0x8E, 0x04, 0x25, 0x00, 0x00, //movss [esi+00002504],xmm1
			};
			vp_memcpy((appBaseAddr + 0x8E436), buffer, sizeof(buffer));
		}
		{
			BYTE buffer[] =
			{
				0xF3, 0x0F, 0x11, 0x86, 0x04, 0x25, 0x00, 0x00, //movss [esi+00002504],xmm0
			};
			vp_memcpy((appBaseAddr + 0x8E9FB), buffer, sizeof(buffer));
		}
		{
			BYTE buffer[] =
			{
				0xF3, 0x0F, 0x11, 0x8E, 0x04, 0x25, 0x00, 0x00, //movss [esi+00002504],xmm1
			};
			vp_memcpy((appBaseAddr + 0x8EA05), buffer, sizeof(buffer));
		}
	}
}

void Game_Training_ToggleDisableTimer(bool enable)
{
	LogFunctionBool(enable);
	if (enable)
	{
		Write<BYTE>((appBaseAddr + 0x1540E1), 0xEB);
	}
	else
	{
		Write<BYTE>((appBaseAddr + 0x1540E1), 0x74);
	}
}
