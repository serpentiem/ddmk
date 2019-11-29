
// @Todo: Reset Magic Points if infinite option is active.

#include "Training.h"

void Game_Training_ToggleInfiniteHitPoints(bool enable)
{
	Log("%s %u", FUNC_NAME, enable);
	if (enable)
	{
		vp_memset((appBaseAddr + 0x88517), 0x90, 5);
	}
	else
	{
		byte buffer[] =
		{
			0xF3, 0x41, 0x0F, 0x5C, 0xC0, //subss xmm0,xmm8
		};
		vp_memcpy((appBaseAddr + 0x88517), buffer, sizeof(buffer));
	}
}

void Game_Training_ToggleInfiniteMagicPoints(bool enable)
{
	Log("%s %u", FUNC_NAME, enable);
	if (enable)
	{
		vp_memset((appBaseAddr + 0x1E1842), 0x90, 4); // Tick
		vp_memset((appBaseAddr + 0x1E788A), 0x90, 4); // Charge
	}
	else
	{
		{
			byte buffer[] =
			{
				0xF3, 0x0F, 0x5C, 0xC8, //subss xmm1,xmm0
			};
			vp_memcpy((appBaseAddr + 0x1E1842), buffer, sizeof(buffer));
		}
		{
			byte buffer[] =
			{
				0xF3, 0x0F, 0x5C, 0xC1, //subss xmm0,xmm1
			};
			vp_memcpy((appBaseAddr + 0x1E788A), buffer, sizeof(buffer));
		}
	}
}

void Game_Training_ToggleDisableTimer(bool enable)
{
	Log("%s %u", FUNC_NAME, enable);
	if (enable)
	{
		vp_memset((appBaseAddr + 0x27EF74), 0x90, 4);
		Write<byte>((appBaseAddr + 0x27F332), 0xEB);
	}
	else
	{
		byte buffer[] =
		{
			0xF3, 0x0F, 0x5C, 0xC8, //subss xmm1,xmm0
		};
		vp_memcpy((appBaseAddr + 0x27EF74), buffer, sizeof(buffer));
		Write<byte>((appBaseAddr + 0x27F332), 0x74);
	}
}
