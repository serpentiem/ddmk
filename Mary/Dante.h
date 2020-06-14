#pragma once
#include "../Core/Core.h"



#include "Vars.h"


#include "ActorData.h"

#include "Config.h"




void Mobility_Toggle(bool enable);

//void Mobility_Init();


extern byte8 * Dante_rainStorm;

void Dante_Init();

inline void Dante_AirHike_ToggleCoreAbility(bool enable)
{
	LogFunction(enable);
	Write<byte8>((appBaseAddr + 0x1E9B0E), (enable) ? 0xEB : 0x74);
}

inline void Dante_Rebellion_ToggleInfiniteSwordPierce(bool enable)
{
	LogFunction(enable);
	if (enable)
	{
		vp_memset((appBaseAddr + 0x1CC9A4), 0x90, 5);
		vp_memset((appBaseAddr + 0x1CDA1B), 0x90, 4);
		vp_memset((appBaseAddr + 0x1CDD64), 0x90, 5);
		vp_memset((appBaseAddr + 0x1CDDCE), 0x90, 4);
		vp_memset((appBaseAddr + 0x21562E), 0x90, 5);
	}
	else
	{
		{
			constexpr byte8 buffer[] =
			{
				0xF3, 0x0F, 0x5C, 0x4B, 0x14, //subss xmm1,[rbx+14]
			};
			vp_memcpy((appBaseAddr + 0x1CC9A4), buffer, sizeof(buffer));
		}
		{
			constexpr byte8 buffer[] =
			{
				0xF3, 0x0F, 0x5C, 0xC1, //subss xmm0,xmm1
			};
			vp_memcpy((appBaseAddr + 0x1CDA1B), buffer, sizeof(buffer));
		}
		{
			constexpr byte8 buffer[] =
			{
				0xF3, 0x0F, 0x5C, 0x4B, 0x14, //subss xmm1,[rbx+14]
			};
			vp_memcpy((appBaseAddr + 0x1CDD64), buffer, sizeof(buffer));
		}
		{
			constexpr byte8 buffer[] =
			{
				0xF3, 0x0F, 0x5C, 0xCA, //subss xmm1,xmm2
			};
			vp_memcpy((appBaseAddr + 0x1CDDCE), buffer, sizeof(buffer));
		}
		{
			constexpr byte8 buffer[] =
			{
				0xF3, 0x0F, 0x5C, 0x47, 0x14, //subss xmm0,[rdi+14]
			};
			vp_memcpy((appBaseAddr + 0x21562E), buffer, sizeof(buffer));
		}
	}
}

inline void Dante_EbonyIvory_ToggleFoursomeTime(bool enable)
{
	LogFunction(enable);
	WriteAddress((appBaseAddr + 0x1E24F6), (enable) ? (appBaseAddr + 0x1E24FC) : (appBaseAddr + 0x1E259C), 6);
	WriteAddress((appBaseAddr + 0x20D188), (enable) ? (appBaseAddr + 0x20D18A) : (appBaseAddr + 0x20D1AB), 2);
}

inline void Dante_EbonyIvory_ToggleInfiniteRainStorm(bool enable)
{
	LogFunction(enable);
	if (enable)
	{
		WriteJump((appBaseAddr + 0x20CC0F), Dante_rainStorm);
	}
	else
	{
		constexpr byte8 buffer[] =
		{
			0x0F, 0xA3, 0xC1, //bt ecx,eax
			0x72, 0x0C,       //jb dmc3.exe+20CC20
		};
		vp_memcpy((appBaseAddr + 0x20CC0F), buffer, sizeof(buffer));
	}
}

inline void Dante_Artemis_ToggleSwap(bool enable)
{
	LogFunction(enable);
	if (enable)
	{
		constexpr byte8 buffer[] =
		{
			0xC6, 0x87, 0x80, 0xB8, 0x00, 0x00, 0x01, //mov byte ptr [rdi+0000B880],01
		};
		vp_memcpy((appBaseAddr + 0x215C78), buffer, sizeof(buffer));
	}
	else
	{
		constexpr byte8 buffer[] =
		{
			0x44, 0x88, 0xB7, 0x80, 0xB8, 0x00, 0x00, //mov [rdi+0000B880],r14l
		};
		vp_memcpy((appBaseAddr + 0x215C78), buffer, sizeof(buffer));
	}
	Write<uint8>((appBaseAddr + 0x215CDA), (enable) ? 0 : 1);
}

inline void Dante_Artemis_ToggleInstant(bool enable)
{
	LogFunction(enable);
	WriteAddress((appBaseAddr + 0x215E42), (enable) ? (appBaseAddr + 0x215E48) : (appBaseAddr + 0x215F78), 6);
}

inline void Dante_CrazyCombo_SetLevelMultiplier(uint8 multiplier)
{
	LogFunction(multiplier);
	Write<uint8>((appBaseAddr + 0x5898DE), multiplier);
	Write<uint8>((appBaseAddr + 0x58999E), multiplier);
	Write<uint8>((appBaseAddr + 0x589A5E), multiplier);
}
