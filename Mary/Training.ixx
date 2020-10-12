module;
#include "../Core/Core.h"

#include "Vars.h"
export module Training;

import State;

export void Training_ToggleInfiniteHitPoints(bool enable)
{
	LogFunction(enable);
	if (enable)
	{
		vp_memset((appBaseAddr + 0x88517), 0x90, 5);
	}
	else
	{
		byte8 buffer[] =
		{
			0xF3, 0x41, 0x0F, 0x5C, 0xC0, //subss xmm0,xmm8
		};
		vp_memcpy((appBaseAddr + 0x88517), buffer, sizeof(buffer));
	}
}

export void Training_ToggleInfiniteMagicPoints(bool enable)
{
	LogFunction(enable);
	if (enable)
	{
		vp_memset((appBaseAddr + 0x1E1842), 0x90, 4); // Tick
		vp_memset((appBaseAddr + 0x1E788A), 0x90, 4); // Charge
		//if (InGame())
		//{
		//	//auto count = System_Actor_GetActorCount();
		//	//for (uint8 actor = 0; actor < count; actor++)
		//	//{
		//	//	auto & baseAddr = System_Actor_actorBaseAddr[actor];
		//	//	if (!baseAddr)
		//	//	{
		//	//		continue;
		//	//	}
		//	//	float32 & magicPoints    = *(float32 *)(baseAddr + 0x3EB8);
		//	//	float32 & maxMagicPoints = *(float32 *)(baseAddr + 0x3EBC);
		//	//	magicPoints = maxMagicPoints;
		//	//}
		//}
	}
	else
	{
		{
			constexpr byte8 buffer[] =
			{
				0xF3, 0x0F, 0x5C, 0xC8, //subss xmm1,xmm0
			};
			vp_memcpy((appBaseAddr + 0x1E1842), buffer, sizeof(buffer));
		}
		{
			constexpr byte8 buffer[] =
			{
				0xF3, 0x0F, 0x5C, 0xC1, //subss xmm0,xmm1
			};
			vp_memcpy((appBaseAddr + 0x1E788A), buffer, sizeof(buffer));
		}
	}
}

export void Training_ToggleDisableTimer(bool enable)
{
	LogFunction(enable);
	if (enable)
	{
		vp_memset((appBaseAddr + 0x27EF74), 0x90, 4);
	}
	else
	{
		constexpr byte8 buffer[] =
		{
			0xF3, 0x0F, 0x5C, 0xC8, //subss xmm1,xmm0
		};
		vp_memcpy((appBaseAddr + 0x27EF74), buffer, sizeof(buffer));
	}
	Write<byte8>((appBaseAddr + 0x27F332), (enable) ? 0xEB : 0x74);
}
