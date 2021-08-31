export module Camera;

import Core;

#include "../Core/Macros.h"

import Config;
import Global;
import Vars;


#define debug false

#include "Macros.h"


namespaceStart(Camera);

export void Toggle(bool enable)
{
	LogFunction(enable);

	static bool run = false;



	// Turn Right
	{
		auto addr     = (appBaseAddr + 0x57720);
		auto jumpAddr = (appBaseAddr + 0x57725);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+57720 - E8 0B552D00 - call dmc3.exe+32CC30
		dmc3.exe+57725 - B9 00200000 - mov ecx,00002000
		dmc3.exe+5772A - 66 85 C1    - test cx,ax
		dmc3.exe+5772D - 74 11       - je dmc3.exe+57740
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rax
			0x8A, 0x00,                                                 // mov al,[rax]
			0x84, 0xC0,                                                 // test al,al
			0x0F, 0x85, 0x00, 0x00, 0x00, 0x00,                         // jne dmc3.exe+57740
			0xE8, 0x00, 0x00, 0x00, 0x00,                               // call dmc3.exe+32CC30
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<bool **>(func.sect0 + 2) = &g_disableCameraRotation;
			WriteAddress((func.sect0 + 0xE), (appBaseAddr + 0x57740), 6);
			WriteCall((func.sect0 + 0x14), (appBaseAddr + 0x32CC30));
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Turn Left
	{
		auto addr     = (appBaseAddr + 0x5774C);
		auto jumpAddr = (appBaseAddr + 0x57751);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+5774C - E8 DF542D00 - call dmc3.exe+32CC30
		dmc3.exe+57751 - B9 00800000 - mov ecx,00008000
		dmc3.exe+57756 - 66 85 C1    - test cx,ax
		dmc3.exe+57759 - 74 3A       - je dmc3.exe+57795
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rax
			0x8A, 0x00,                                                 // mov al,[rax]
			0x84, 0xC0,                                                 // test al,al
			0x0F, 0x85, 0x00, 0x00, 0x00, 0x00,                         // jne dmc3.exe+57795
			0xE8, 0x00, 0x00, 0x00, 0x00,                               // call dmc3.exe+32CC30
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<bool **>(func.sect0 + 2) = &g_disableCameraRotation;
			WriteAddress((func.sect0 + 0xE), (appBaseAddr + 0x57795), 6);
			WriteCall((func.sect0 + 0x14), (appBaseAddr + 0x32CC30));
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Camera Auto Adjust
	{
		auto addr     = (appBaseAddr + 0x579F2);
		auto jumpAddr = (appBaseAddr + 0x579FD);
		constexpr uint32 size = 11;
		/*
		dmc3.exe+579F2 - 0F29 47 70       - movaps [rdi+70],xmm0
		dmc3.exe+579F6 - 0F29 8F 80000000 - movaps [rdi+00000080],xmm1
		dmc3.exe+579FD - E8 5EFA2600      - call dmc3.exe+2C7460
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rax
			0x8A, 0x00,                                                 // mov al,[rax]
			0x84, 0xC0,                                                 // test al,al
			0x74, 0x0E,                                                 // je short
			0x3C, 0x01,                                                 // cmp al,01
			0x75, 0x15,                                                 // jne short
			0x8A, 0x87, 0xD8, 0x01, 0x00, 0x00,                         // mov al,[rdi+000001D8]
			0x84, 0xC0,                                                 // test al,al
			0x74, 0x0B,                                                 // je short
			0x0F, 0x29, 0x47, 0x70,                                     // movaps [rdi+70],xmm0
			0x0F, 0x29, 0x8F, 0x80, 0x00, 0x00, 0x00,                   // movaps [rdi+00000080],xmm1
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 2) = &activeConfig.cameraAutoAdjust;
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Center Camera
	{
		auto addr     = (appBaseAddr + 0x577BA);
		auto jumpAddr = (appBaseAddr + 0x577BF);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+577BA - E8 D1542D00 - call dmc3.exe+32CC90
		dmc3.exe+577BF - 66 85 C3    - test bx,ax
		dmc3.exe+577C2 - 74 3B       - je dmc3.exe+577FF
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rax
			0x8A, 0x00,                                                 // mov al,[rax]
			0x84, 0xC0,                                                 // test al,al
			0x0F, 0x85, 0x00, 0x00, 0x00, 0x00,                         // jne dmc3.exe+577FF
			0xE8, 0x00, 0x00, 0x00, 0x00,                               // call dmc3.exe+32CC90
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<bool **>(func.sect0 + 2) = &activeConfig.disableCenterCamera;
			WriteAddress((func.sect0 + 0xE), (appBaseAddr + 0x577FF), 6);
			WriteCall((func.sect0 + 0x14), (appBaseAddr + 0x32CC90));
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}



	run = true;
}

// @Todo: Update.
export void ToggleInvertX(bool enable)
{
	LogFunction(enable);

	Write<byte32>((appBaseAddr + 0x57726), (enable) ? GAMEPAD_RIGHT : GAMEPAD_LEFT ); // Turn right.
	Write<byte32>((appBaseAddr + 0x57752), (enable) ? GAMEPAD_LEFT  : GAMEPAD_RIGHT); // Turn left.
	Write<byte32>((appBaseAddr + 0x51267), (enable) ? GAMEPAD_LEFT  : GAMEPAD_RIGHT); // Fast turn left.
	Write<byte32>((appBaseAddr + 0x51296), (enable) ? GAMEPAD_RIGHT : GAMEPAD_LEFT ); // Fast turn right.
}



/*
dmc3.exe+55FC0 - 0FB6 05 69B8C300      - movzx eax,byte ptr [dmc3.exe+C91830] { (9) }

*/


export void ToggleDisableBossCamera(bool enable)
{
	LogFunction(enable);

	static bool run = false;



	{
		auto addr = (appBaseAddr + 0x55FD2);
		constexpr uint32 size = 14;
		/*
		dmc3.exe+55FD2 - 48 89 83 98040000 - mov [rbx+00000498],rax
		dmc3.exe+55FD9 - 4C 89 A3 B0040000 - mov [rbx+000004B0],r12
		dmc3.exe+55FE0 - EB 15             - jmp dmc3.exe+55FF7
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

namespaceEnd();
