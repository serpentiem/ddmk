export module Training;

import Core;

#include "../Core/Macros.h"

import Vars;



//namespaceStart(Training);



export void ToggleInfiniteHitPoints(bool enable)
{
	LogFunction(enable);

	static bool run = false;

	// Main
	{
		auto addr = (appBaseAddr + 0x88517);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+88517 - F3 41 0F5C C0 - subss xmm0,xmm8
		dmc3.exe+8851C - F3 0F11 40 08 - movss [rax+08],xmm0
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			SetMemory(addr, 0x90, size, MemoryFlags_VirtualProtectDestination);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Arkham Drain
	{
		auto addr = (appBaseAddr + 0x1E1884);
		constexpr uint32 size = 4;
		/*
		dmc3.exe+1E1884 - F3 0F5C C8 - subss xmm1,xmm0
		dmc3.exe+1E1888 - 0F57 C0    - xorps xmm0,xmm0
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			SetMemory(addr, 0x90, size, MemoryFlags_VirtualProtectDestination);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	run = true;
}

export void ToggleInfiniteMagicPoints(bool enable)
{
	LogFunction(enable);

	static bool run = false;

	// Tick
	{
		auto addr = (appBaseAddr + 0x1E1842);
		constexpr uint32 size = 4;
		/*
		dmc3.exe+1E1842 - F3 0F5C C8 - subss xmm1,xmm0
		dmc3.exe+1E1846 - 0F57 C0    - xorps xmm0,xmm0
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			SetMemory(addr, 0x90, size, MemoryFlags_VirtualProtectDestination);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Charge
	{
		auto addr = (appBaseAddr + 0x1E788A);
		constexpr uint32 size = 4;
		/*
		dmc3.exe+1E788A - F3 0F5C C1          - subss xmm0,xmm1
		dmc3.exe+1E788E - F3 0F11 87 B83E0000 - movss [rdi+00003EB8],xmm0
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			SetMemory(addr, 0x90, size, MemoryFlags_VirtualProtectDestination);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	run = true;
}

export void ToggleDisableTimer(bool enable)
{
	LogFunction(enable);

	static bool run = false;

	// Main
	{
		auto addr = (appBaseAddr + 0x27EF74);
		constexpr uint32 size = 4;
		/*
		dmc3.exe+27EF74 - F3 0F5C C8 - subss xmm1,xmm0
		dmc3.exe+27EF78 - 0F57 C0    - xorps xmm0,xmm0
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			SetMemory(addr, 0x90, size, MemoryFlags_VirtualProtectDestination);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Hide Timer
	{
		auto addr = (appBaseAddr + 0x27F332);
		constexpr uint32 size = 2;
		/*
		dmc3.exe+27F332 - 74 17             - je dmc3.exe+27F34B
		dmc3.exe+27F334 - 48 8D 8B 804A0000 - lea rcx,[rbx+00004A80]
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			Write<byte8>(addr, 0xEB);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	run = true;
}

export void ToggleInfiniteBullets(bool enable)
{
	LogFunction(enable);

	static bool run = false;

	// Boss Lady Pistol
	{
		auto addr = (appBaseAddr + 0x169CFE);
		constexpr uint32 size = 6;
		/*
		dmc3.exe+169CFE - FF 8E A0590000 - dec [rsi+000059A0]
		dmc3.exe+169D04 - FE 87 E3570000 - inc byte ptr [rdi+000057E3]
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			SetMemory(addr, 0x90, size, MemoryFlags_VirtualProtectDestination);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Boss Lady SMG
	{
		auto addr = (appBaseAddr + 0x171DF0);
		constexpr uint32 size = 6;
		/*
		dmc3.exe+171DF0 - FF 8B B8590000      - dec [rbx+000059B8]
		dmc3.exe+171DF6 - F3 0F10 83 045A0000 - movss xmm0,[rbx+00005A04]
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			SetMemory(addr, 0x90, size, MemoryFlags_VirtualProtectDestination);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	run = true;
}



//namespaceEnd();
