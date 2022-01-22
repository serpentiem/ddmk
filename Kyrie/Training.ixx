export module Training;

import Core;

#include "../Core/Macros.h"

import Vars;



export void ToggleInfiniteHitPoints(bool enable)
{
	LogFunction(enable);

	static bool run = false;



	{
		auto addr = (appBaseAddr + 0x22DDD4);
		constexpr new_size_t size = 4;
		/*
		dmc4.exe+22DDD4 - F3 0F5C C1 - subss xmm0,xmm1
		dmc4.exe+22DDD8 - 0F2F D0    - comiss xmm2,xmm0
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



	// Devil Flux
	{
		auto addr = (appBaseAddr + 0x4C87A9);
		constexpr new_size_t size = 8;
		/*
		dmc4.exe+4C87A9 - F3 0F11 86 04250000 - movss [esi+00002504],xmm0
		dmc4.exe+4C87B1 - 76 08               - jna dmc4.exe+4C87BB
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

	// Devil Tick
	{
		auto addr = (appBaseAddr + 0x4C889E);
		constexpr new_size_t size = 8;
		/*
		dmc4.exe+4C889E - F3 0F11 86 04250000 - movss [esi+00002504],xmm0
		dmc4.exe+4C88A6 - 76 08               - jna dmc4.exe+4C88B0
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

	// Stinger, Kick 13, Lunar Phase, Rising Sun
	{
		auto addr = (appBaseAddr + 0x4D004B);
		constexpr new_size_t size = 8;
		/*
		dmc4.exe+4D004B - F3 0F11 86 04250000 - movss [esi+00002504],xmm0
		dmc4.exe+4D0053 - 76 08               - jna dmc4.exe+4D005D
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

	// Pin-Up
	{
		auto addr = (appBaseAddr + 0x5028FC);
		constexpr new_size_t size = 8;
		/*
		dmc4.exe+5028FC - F3 0F11 86 04250000 - movss [esi+00002504],xmm0
		dmc4.exe+502904 - 76 08               - jna dmc4.exe+50290E
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

	// Burst Attack
	{
		auto addr = (appBaseAddr + 0x8E42C);
		constexpr new_size_t size = 8;
		/*
		dmc4.exe+8E42C - F3 0F11 86 04250000 - movss [esi+00002504],xmm0
		dmc4.exe+8E434 - 76 08               - jna dmc4.exe+8E43E
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

	// Burst Attack Reset
	{
		auto addr = (appBaseAddr + 0x8E436);
		constexpr new_size_t size = 8;
		/*
		dmc4.exe+8E436 - F3 0F11 8E 04250000 - movss [esi+00002504],xmm1
		dmc4.exe+8E43E - F3 0F10 86 08250000 - movss xmm0,[esi+00002508]
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

	// Burst Attack Air
	{
		auto addr = (appBaseAddr + 0x8E9FB);
		constexpr new_size_t size = 8;
		/*
		dmc4.exe+8E9FB - F3 0F11 86 04250000 - movss [esi+00002504],xmm0
		dmc4.exe+8EA03 - 76 08               - jna dmc4.exe+8EA0D
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

	// Burst Attack Reset Air
	{
		auto addr = (appBaseAddr + 0x8EA05);
		constexpr new_size_t size = 8;
		/*
		dmc4.exe+8EA05 - F3 0F11 8E 04250000 - movss [esi+00002504],xmm1
		dmc4.exe+8EA0D - F3 0F10 86 08250000 - movss xmm0,[esi+00002508]
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



	{
		auto addr = (appBaseAddr + 0x1540E1);
		constexpr new_size_t size = 2;
		/*
		dmc4.exe+1540E1 - 74 05       - je dmc4.exe+1540E8
		dmc4.exe+1540E3 - E8 98750400 - call dmc4.exe+19B680
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
