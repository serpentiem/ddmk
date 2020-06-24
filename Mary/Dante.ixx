#ifndef __MODULE_DANTE__
#define __MODULE_DANTE__

module;
#include "../Core/Core.h"

#include "ActorData.h"
#include "Vars.h"
export module ModuleName(Dante);

import ModuleName(Config);

#ifdef __INTELLISENSE__
#include "Config.ixx"
#endif

byte8 * Dante_rainStorm = 0;




export void Dante_Init()
{
	LogFunction();


	






	// @Todo: Update input!
	{
		constexpr byte8 sect0[] =
		{
			0x66, 0x8B, 0x05, 0x00, 0x00, 0x00, 0x00, //mov ax,[dmc3.exe+D6CE88+E]
			0x66, 0x85, 0x83, 0xE0, 0x74, 0x00, 0x00, //test [rbx+000074E0],ax
			0x0F, 0x85, 0x00, 0x00, 0x00, 0x00,       //jne dmc3.exe+20CC20
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x20CC14), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteAddress(func.sect0, (appBaseAddr + 0xD6CE88 + 0xE), 7);
		WriteAddress((func.sect0 + 0xE), (appBaseAddr + 0x20CC20), 6);
		Dante_rainStorm = func.addr;
	}
}









export void Dante_AirHike_ToggleCoreAbility(bool enable)
{
	LogFunction(enable);
	Write<byte8>((appBaseAddr + 0x1E9B0E), (enable) ? 0xEB : 0x74);
}

export void Dante_Rebellion_ToggleInfiniteSwordPierce(bool enable)
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

export void Dante_EbonyIvory_ToggleFoursomeTime(bool enable)
{
	LogFunction(enable);
	WriteAddress((appBaseAddr + 0x1E24F6), (enable) ? (appBaseAddr + 0x1E24FC) : (appBaseAddr + 0x1E259C), 6);
	WriteAddress((appBaseAddr + 0x20D188), (enable) ? (appBaseAddr + 0x20D18A) : (appBaseAddr + 0x20D1AB), 2);
}

export void Dante_EbonyIvory_ToggleInfiniteRainStorm(bool enable)
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

export void Dante_Artemis_ToggleSwap(bool enable)
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

export void Dante_Artemis_ToggleInstant(bool enable)
{
	LogFunction(enable);
	WriteAddress((appBaseAddr + 0x215E42), (enable) ? (appBaseAddr + 0x215E48) : (appBaseAddr + 0x215F78), 6);
}

export void Dante_CrazyCombo_SetLevelMultiplier(uint8 multiplier)
{
	LogFunction(multiplier);
	Write<uint8>((appBaseAddr + 0x5898DE), multiplier);
	Write<uint8>((appBaseAddr + 0x58999E), multiplier);
	Write<uint8>((appBaseAddr + 0x589A5E), multiplier);
}

#ifdef __GARBAGE__
#endif

#endif
