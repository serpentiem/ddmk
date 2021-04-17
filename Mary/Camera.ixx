module;
// #include "../Core/Core.h"

// #include "Vars.h"

#include "../Core/Macros.h" //

export module Camera;

import Core;


import Vars;

// #define memset SetMemory
// #define memcpy CopyMemory

import Config;
import Global;








export void Camera_Toggle(bool enable)
{
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
export void Camera_ToggleInvertX(bool enable)
{
	LogFunction(enable);

	Write<byte32>((appBaseAddr + 0x57726), (enable) ? GAMEPAD_RIGHT : GAMEPAD_LEFT ); // Turn right.
	Write<byte32>((appBaseAddr + 0x57752), (enable) ? GAMEPAD_LEFT  : GAMEPAD_RIGHT); // Turn left.
	Write<byte32>((appBaseAddr + 0x51267), (enable) ? GAMEPAD_LEFT  : GAMEPAD_RIGHT); // Fast turn left.
	Write<byte32>((appBaseAddr + 0x51296), (enable) ? GAMEPAD_RIGHT : GAMEPAD_LEFT ); // Fast turn right.
}




















