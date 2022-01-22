// @Todo: Bangle of Time.

export module Training;

import Core;

#include "../Core/Macros.h"

import Vars;





export void ToggleInfiniteHitPoints(bool enable)
{
	LogFunction(enable);

	static bool run = false;



	// Player Actor
	{
		auto addr = (appBaseAddr + 0x4FA0A);
		constexpr uint64 size = 3;
		/*
		dmc1.exe+4FA0A - 66 2B C8             - sub cx,ax
		dmc1.exe+4FA0D - 66 41 89 8A A2170000 - mov [r10+000017A2],cx
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

	// Enemy Actor
	{
		auto addr = (appBaseAddr + 0x4FA28);
		constexpr uint64 size = 8;
		/*
		dmc1.exe+4FA28 - 66 41 29 82 A2170000 - sub [r10+000017A2],ax
		dmc1.exe+4FA30 - 79 0B                - jns dmc1.exe+4FA3D
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

	{
		auto addr = (appBaseAddr + 0x4FA30);
		constexpr uint64 size = 2;
		/*
		dmc1.exe+4FA30 - 79 0B    - jns dmc1.exe+4FA3D
		dmc1.exe+4FA32 - 83 C8 FF - or eax,-01
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

export void ToggleInfiniteMagicPoints(bool enable)
{
	LogFunction(enable);

	static bool run = false;



	#pragma region Human

	// Devil Form Leave
	{
		auto addr = (appBaseAddr + 0x2ECFA7);
		constexpr uint64 size = 7;
		/*
		dmc1.exe+2ECFA7 - 66 89 83 CE1B0000 - mov [rbx+00001BCE],ax
		dmc1.exe+2ECFAE - EB 07             - jmp dmc1.exe+2ECFB7
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

	// Devil Form Run Out
	{
		auto addr = (appBaseAddr + 0x2ECFB0);
		constexpr uint64 size = 7;
		/*
		dmc1.exe+2ECFB0 - 66 89 BB CE1B0000 - mov [rbx+00001BCE],di
		dmc1.exe+2ECFB7 - B8 0A000000       - mov eax,0000000A
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

	// Nightmare Beta Charge
	{
		auto addr = (appBaseAddr + 0x2F78CB);
		constexpr uint64 size = 4;
		/*
		dmc1.exe+2F78CB - 66 83 E8 78       - sub ax,78
		dmc1.exe+2F78CF - 66 89 83 CE1B0000 - mov [rbx+00001BCE],ax
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

	{
		auto addr = (appBaseAddr + 0x2F7AF0);
		constexpr uint64 size = 4;
		/*
		dmc1.exe+2F7AF0 - 66 83 E8 02       - sub ax,02
		dmc1.exe+2F7AF4 - 66 89 83 CE1B0000 - mov [rbx+00001BCE],ax
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

	// Nightmare Beta Charge Run Out
	{
		auto addr = (appBaseAddr + 0x2F7AFD);
		constexpr uint64 size = 8;
		/*
		dmc1.exe+2F7AFD - 66 44 89 BB CE1B0000 - mov [rbx+00001BCE],r15w
		dmc1.exe+2F7B05 - 44 89 BB 541E0000    - mov [rbx+00001E54],r15d
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

	// Nobody Drain
	{
		auto addr = (appBaseAddr + 0x17AE9C);
		constexpr uint64 size = 8;
		/*
		dmc1.exe+17AE9C - 66 83 87 CE1B0000 FE - add word ptr [rdi+00001BCE],-02
		dmc1.exe+17AEA4 - B8 10270000          - mov eax,00002710
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

	// Sparda Dragon
	{
		auto addr = (appBaseAddr + 0x2D4FE4);
		constexpr uint64 size = 8;
		/*
		dmc1.exe+2D4FE4 - 66 44 89 BB CE1B0000 - mov [rbx+00001BCE],r15w
		dmc1.exe+2D4FEC - 44 38 BB 530E0000    - cmp [rbx+00000E53],r15l
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

	#pragma endregion

	#pragma region Devil

	// Devil Form Enter
	{
		auto addr = (appBaseAddr + 0x2ECC99);
		constexpr uint64 size = 7;
		/*
		dmc1.exe+2ECC99 - 66 89 93 D21B0000          - mov [rbx+00001BD2],dx
		dmc1.exe+2ECCA0 - 41 81 88 801F0000 00100000 - or [r8+00001F80],00001000
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

	// Devil Form Drain
	{
		auto addr = (appBaseAddr + 0x2ECD80);
		constexpr uint64 size = 7;
		/*
		dmc1.exe+2ECD80 - 66 FF 8B D21B0000 - dec word ptr [rbx+00001BD2]
		dmc1.exe+2ECD87 - 0FB6 83 CD1B0000  - movzx eax,byte ptr [rbx+00001BCD]
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

	// Devil Form Leave
	{
		auto addr = (appBaseAddr + 0x2ECF7D);
		constexpr uint64 size = 7;
		/*
		dmc1.exe+2ECF7D - 66 01 83 D21B0000 - add [rbx+00001BD2],ax
		dmc1.exe+2ECF84 - 0FB7 8B D21B0000  - movzx ecx,word ptr [rbx+00001BD2]
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

	// Alastor Melee Attack
	{
		auto addr = (appBaseAddr + 0x2D6583);
		constexpr uint64 size = 8;
		/*
		dmc1.exe+2D6583 - 66 83 A9 D21B0000 01 - sub word ptr [rcx+00001BD2],01
		dmc1.exe+2D658B - 79 08                - jns dmc1.exe+2D6595
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

	{
		auto addr = (appBaseAddr + 0x2D658B);
		constexpr uint64 size = 2;
		/*
		dmc1.exe+2D658B - 79 08                - jns dmc1.exe+2D6595
		dmc1.exe+2D658D - 66 44 89 B1 D21B0000 - mov [rcx+00001BD2],r14w
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

	// Alastor Air Raid
	{
		auto addr = (appBaseAddr + 0x2ECD9B);
		constexpr uint64 size = 3;
		/*
		dmc1.exe+2ECD9B - 66 FF C9          - dec cx
		dmc1.exe+2ECD9E - 66 89 8B D21B0000 - mov [rbx+00001BD2],cx
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

	// Ifrit Kick 13
	{
		auto addr = (appBaseAddr + 0x2D9807);
		constexpr uint64 size = 8;
		/*
		dmc1.exe+2D9807 - 66 83 81 D21B0000 FC - add word ptr [rcx+00001BD2],-04
		dmc1.exe+2D980F - 79 08                - jns dmc1.exe+2D9819
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

	{
		auto addr = (appBaseAddr + 0x2D980F);
		constexpr uint64 size = 2;
		/*
		dmc1.exe+2D980F - 79 08                - jns dmc1.exe+2D9819
		dmc1.exe+2D9811 - 66 44 89 B9 D21B0000 - mov [rcx+00001BD2],r15w
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

	// Ifrit Meteor
	{
		auto addr = (appBaseAddr + 0x2DCE9A);
		constexpr uint64 size = 3;
		/*
		dmc1.exe+2DCE9A - 66 FF C8          - dec ax
		dmc1.exe+2DCE9D - 66 89 87 D21B0000 - mov [rdi+00001BD2],ax
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

	// Ifrit Inferno
	{
		auto addr = (appBaseAddr + 0x2DC758);
		constexpr uint64 size = 8;
		/*
		dmc1.exe+2DC758 - 66 83 83 D21B0000 F8 - add word ptr [rbx+00001BD2],-08
		dmc1.exe+2DC760 - 79 07                - jns dmc1.exe+2DC769
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

	{
		auto addr = (appBaseAddr + 0x2DC760);
		constexpr uint64 size = 2;
		/*
		dmc1.exe+2DC760 - 79 07             - jns dmc1.exe+2DC769
		dmc1.exe+2DC762 - 66 89 B3 D21B0000 - mov [rbx+00001BD2],si
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



	// Sparda Small Fireball
	{
		auto addr = (appBaseAddr + 0x2D58EB);
		constexpr uint64 size = 8;
		/*
		dmc1.exe+2D58EB - 66 83 83 D21B0000 F6 - add word ptr [rbx+00001BD2],-0A
		dmc1.exe+2D58F3 - 79 09                - jns dmc1.exe+2D58FE
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

	{
		auto addr = (appBaseAddr + 0x2D58F3);
		constexpr uint64 size = 2;
		/*
		dmc1.exe+2D58F3 - 79 09 - jns dmc1.exe+2D58FE
		dmc1.exe+2D58F5 - 33 C0 - xor eax,eax
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



	// Sparda Charged Fireball
	{
		auto addr = (appBaseAddr + 0x2D61CB);
		constexpr uint64 size = 8;
		/*
		dmc1.exe+2D61CB - 66 83 87 D21B0000 FE - add word ptr [rdi+00001BD2],-02
		dmc1.exe+2D61D3 - 66 89 87 101A0000    - mov [rdi+00001A10],ax
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

	{
		auto addr = (appBaseAddr + 0x2D61DA);
		constexpr uint64 size = 2;
		/*
		dmc1.exe+2D61DA - 79 07             - jns dmc1.exe+2D61E3
		dmc1.exe+2D61DC - 66 89 9F D21B0000 - mov [rdi+00001BD2],bx
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

	{
		auto addr = (appBaseAddr + 0x2D6267);
		constexpr uint64 size = 3;
		/*
		dmc1.exe+2D6267 - 66 FF C8          - dec ax
		dmc1.exe+2D626A - 66 89 87 D21B0000 - mov [rdi+00001BD2],ax
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

	#pragma endregion



	run = true;
}

export void ToggleDisableTimer(bool enable)
{
	LogFunction(enable);

	static bool run = false;



	// Main
	{
		auto addr = (appBaseAddr + 0x257872);
		constexpr uint64 size = 2;
		/*
		dmc1.exe+257872 - FF C8                  - dec eax
		dmc1.exe+257874 - 66 C7 05 F6985602 0101 - mov word ptr [dmc1.exe+27C1173],0101
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



	// Show Timer
	{
		auto addr = (appBaseAddr + 0x2522FA);
		constexpr uint64 size = 6;
		/*
		dmc1.exe+2522FA - 0F84 07010000    - je dmc1.exe+252407
		dmc1.exe+252300 - 0FB6 0D 6DEE5602 - movzx ecx,byte ptr [dmc1.exe+27C1174]
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			Write<byte16>(addr, 0xE990);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}



	run = true;
}
