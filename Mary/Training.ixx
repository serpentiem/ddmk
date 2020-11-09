module;
#include "../Core/Core.h"

#include "Vars.h"
export module Training;

export void Training_ToggleInfiniteHitPoints(bool enable)
{
	LogFunction(enable);

	{
		auto dest = (appBaseAddr + 0x88517);
		if (enable)
		{
			vp_memset(dest, 0x90, 5);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0xF3, 0x41, 0x0F, 0x5C, 0xC0, // subss xmm0,xmm8
			};
			vp_memcpy(dest, buffer, sizeof(buffer));
		}
		/*
		dmc3.exe+88517 - F3 41 0F5C C0 - subss xmm0,xmm8
		dmc3.exe+8851C - F3 0F11 40 08 - movss [rax+08],xmm0
		*/
	}
}

export void Training_ToggleInfiniteMagicPoints(bool enable)
{
	LogFunction(enable);

	// Tick
	{
		auto dest = (appBaseAddr + 0x1E1842);
		if (enable)
		{
			vp_memset(dest, 0x90, 4);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0xF3, 0x0F, 0x5C, 0xC8, // subss xmm1,xmm0
			};
			vp_memcpy(dest, buffer, sizeof(buffer));
		}
		/*
		dmc3.exe+1E1842 - F3 0F5C C8 - subss xmm1,xmm0
		dmc3.exe+1E1846 - 0F57 C0    - xorps xmm0,xmm0
		*/
	}

	// Charge
	{
		auto dest = (appBaseAddr + 0x1E788A);
		if (enable)
		{
			vp_memset(dest, 0x90, 4);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0xF3, 0x0F, 0x5C, 0xC1, // subss xmm0,xmm1
			};
			vp_memcpy(dest, buffer, sizeof(buffer));
		}
		/*
		dmc3.exe+1E788A - F3 0F5C C1          - subss xmm0,xmm1
		dmc3.exe+1E788E - F3 0F11 87 B83E0000 - movss [rdi+00003EB8],xmm0
		*/
	}
}

export void Training_ToggleDisableTimer(bool enable)
{
	LogFunction(enable);

	{
		auto dest = (appBaseAddr + 0x27EF74);
		if (enable)
		{
			vp_memset(dest, 0x90, 4);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0xF3, 0x0F, 0x5C, 0xC8, // subss xmm1,xmm0
			};
			vp_memcpy(dest, buffer, sizeof(buffer));
		}
		/*
		dmc3.exe+27EF74 - F3 0F5C C8 - subss xmm1,xmm0
		dmc3.exe+27EF78 - 0F57 C0    - xorps xmm0,xmm0
		*/
	}

	Write<byte8>((appBaseAddr + 0x27F332), (enable) ? 0xEB : 0x74);
	/*
	dmc3.exe+27F332 - 74 17             - je dmc3.exe+27F34B
	dmc3.exe+27F334 - 48 8D 8B 804A0000 - lea rcx,[rbx+00004A80]
	*/
}
