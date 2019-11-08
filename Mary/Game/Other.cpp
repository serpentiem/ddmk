#include "Other.h"

float32 * orbReach                              = 0;
float32 * MagicPointsDepletionRate_devil        = 0;
float32 * MagicPointsDepletionRate_quicksilver  = 0;
float32 * MagicPointsDepletionRate_doppelganger = 0;

void Game_Other_Update()
{
	LogFunction();
	// Orb Reach
	{
		*orbReach = Config.Game.Other.orbReach;
		WriteAddress((appBaseAddr + 0x1B655F), (byte *)orbReach, 8);
	}
	// Magic Points Depletion Rate
	{
		*MagicPointsDepletionRate_devil = Config.Game.Other.MagicPointsDepletionRate.devil;
		Write<byte>((appBaseAddr + 0x1F8B4C), 0x0D);
		WriteAddress((appBaseAddr + 0x1F8B49), (byte *)MagicPointsDepletionRate_devil, 8);
		*MagicPointsDepletionRate_quicksilver = Config.Game.Other.MagicPointsDepletionRate.quicksilver;
		Write<byte>((appBaseAddr + 0x1F8A43), 0x0D);
		WriteAddress((appBaseAddr + 0x1F8A40), (byte *)MagicPointsDepletionRate_quicksilver, 8);
		*MagicPointsDepletionRate_doppelganger = Config.Game.Other.MagicPointsDepletionRate.doppelganger;
		Write<byte>((appBaseAddr + 0x1F89D4), 0x0D);
		WriteAddress((appBaseAddr + 0x1F89D1), (byte *)MagicPointsDepletionRate_doppelganger, 8);
	}
}

void Game_Other_Reset()
{
	LogFunction();
	// Orb Reach
	WriteAddress((appBaseAddr + 0x1B655F), (appBaseAddr + 0x4C6094), 8);
	// Magic Points Depletion Rate
	{
		byte buffer[] =
		{
			0xF3, 0x0F, 0x59, 0x88, 0x78, 0x01, 0x00, 0x00, //mulss xmm1,[rax+00000178]
		};
		vp_memcpy((appBaseAddr + 0x1F8B49), buffer, sizeof(buffer));
	}
	{
		byte buffer[] =
		{
			0xF3, 0x0F, 0x59, 0x88, 0x70, 0x01, 0x00, 0x00, //mulss xmm1,[rax+00000170]
		};
		vp_memcpy((appBaseAddr + 0x1F8A40), buffer, sizeof(buffer));
	}
	{
		byte buffer[] =
		{
			0xF3, 0x0F, 0x59, 0x88, 0x74, 0x01, 0x00, 0x00, //mulss xmm1,[rax+00000174]
		};
		vp_memcpy((appBaseAddr + 0x1F89D1), buffer, sizeof(buffer));
	}
}

void Game_Other_Init()
{
	LogFunction();
	byte * addr = (byte *)HighAlloc(64);
	orbReach                              = (float32 *)( addr       );
	MagicPointsDepletionRate_devil        = (float32 *)( addr + 4   );
	MagicPointsDepletionRate_quicksilver  = (float32 *)( addr + 8   );
	MagicPointsDepletionRate_doppelganger = (float32 *)( addr + 0xC );
}

void Game_Other_Toggle(bool enable)
{
	LogFunction();
	if (enable)
	{
		Game_Other_Update();
	}
	else
	{
		Game_Other_Reset();
	}
}
