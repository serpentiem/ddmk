module;
#include <stdio.h>
export module Actor;

import Core;

#include "../Core/Macros.h"

import Windows;

using namespace Windows;

import Config;
import Global;
import Internal;
import Vars;

#define debug false

// #include "Macros.h"



#pragma region Main

bool IsMundusPart2()
{
	IntroduceSessionData(return false);
	IntroduceEventData(return false);

	if
	(
		(sessionData.mission != 22) ||
		(eventData.room != 9)
	)
	{
		return false;
	}

	return true;
}

void UpdateMeleeWeapon()
{
	DebugLogFunction();

	IntroduceSessionData(return);
	IntroduceMainActorData(actorData, return);

	auto & meleeWeapons         = activeConfig.Actor.meleeWeapons;
	auto & meleeWeaponCount     = activeConfig.Actor.meleeWeaponCount;
	auto & meleeWeaponIndex     = activeConfig.Actor.meleeWeaponIndex;
	auto & lastMeleeWeaponIndex = activeConfig.Actor.lastMeleeWeaponIndex;
	auto & meleeWeaponForms     = activeConfig.Actor.meleeWeaponForms;

	if (meleeWeaponIndex >= meleeWeaponCount)
	{
		meleeWeaponIndex = 0;
	}

	auto & meleeWeapon     = meleeWeapons[meleeWeaponIndex];
	auto & meleeWeaponForm = meleeWeaponForms[meleeWeaponIndex];





	// auto & sparda          = activeConfig.Actor.sparda[meleeWeaponIndex];
	// auto & yamato          = activeConfig.Actor.yamato[meleeWeaponIndex];

	// if
	// (
	// 	(meleeWeapon == WEAPON::ALASTOR) &&
	// 	yamato
	// )
	// {
	// 	meleeWeaponForm = MELEE_WEAPON_FORM::YAMATO;
	// }
	// else if
	// (
	// 	(meleeWeapon == WEAPON::SPARDA) ||
	// 	(
	// 		(meleeWeapon == WEAPON::FORCE_EDGE) &&
	// 		sparda
	// 	)
	// )
	// {
	// 	meleeWeaponForm = MELEE_WEAPON_FORM::SPARDA;
	// }

	actorData.meleeWeapon     = meleeWeapon;
	actorData.meleeWeaponForm = meleeWeaponForm;



	func_2C4A00(actorData.meleeWeaponForm);

	func_2C99C0(actorData.meleeWeapon, false);
}

void UpdateRangedWeapon()
{
	DebugLogFunction();

	IntroduceSessionData(return);
	IntroduceMainActorData(actorData, return);

	auto & rangedWeapons         = activeConfig.Actor.rangedWeapons;
	auto & rangedWeaponCount     = activeConfig.Actor.rangedWeaponCount;
	auto & rangedWeaponIndex     = activeConfig.Actor.rangedWeaponIndex;
	auto & lastRangedWeaponIndex = activeConfig.Actor.lastRangedWeaponIndex;

	if (rangedWeaponIndex >= rangedWeaponCount)
	{
		rangedWeaponIndex = 0;
	}

	auto & rangedWeapon = rangedWeapons[rangedWeaponIndex];

	actorData.rangedWeapon = rangedWeapon;

	func_2C4C50(actorData.rangedWeapon);
}

#pragma endregion

#pragma region Controllers

void MeleeWeaponSwitchController()
{
	if (!activeConfig.enableMeleeWeaponSwitchController)
	{
		return;
	}

	IntroduceSessionData(return);
	IntroduceMainActorData(actorData, return);

	auto & meleeWeapons         = activeConfig.Actor.meleeWeapons;
	auto & meleeWeaponCount     = activeConfig.Actor.meleeWeaponCount;
	auto & meleeWeaponIndex     = activeConfig.Actor.meleeWeaponIndex;
	auto & lastMeleeWeaponIndex = activeConfig.Actor.lastMeleeWeaponIndex;



	static bool execute = false;

	if (sessionData.buttons[0] & activeConfig.meleeWeaponSwitchButton)
	{
		if (execute)
		{
			execute = false;

			meleeWeaponIndex++;

			if (meleeWeaponIndex >= meleeWeaponCount)
			{
				meleeWeaponIndex = 0;
			}
		}
	}
	else
	{
		execute = true;
	}



	if (lastMeleeWeaponIndex != meleeWeaponIndex)
	{
		lastMeleeWeaponIndex = meleeWeaponIndex;

		UpdateMeleeWeapon();
	}
}

void RangedWeaponSwitchController()
{
	if (!activeConfig.enableRangedWeaponSwitchController)
	{
		return;
	}

	IntroduceSessionData(return);
	IntroduceMainActorData(actorData, return);

	auto & rangedWeapons         = activeConfig.Actor.rangedWeapons;
	auto & rangedWeaponCount     = activeConfig.Actor.rangedWeaponCount;
	auto & rangedWeaponIndex     = activeConfig.Actor.rangedWeaponIndex;
	auto & lastRangedWeaponIndex = activeConfig.Actor.lastRangedWeaponIndex;



	static bool execute = false;

	if (sessionData.buttons[0] & activeConfig.rangedWeaponSwitchButton)
	{
		if (execute)
		{
			execute = false;

			rangedWeaponIndex++;

			if (rangedWeaponIndex >= rangedWeaponCount)
			{
				rangedWeaponIndex = 0;
			}
		}
	}
	else
	{
		execute = true;
	}



	if (lastRangedWeaponIndex != rangedWeaponIndex)
	{
		lastRangedWeaponIndex = rangedWeaponIndex;

		UpdateRangedWeapon();
	}
}

void TauntController()
{
	if (!activeConfig.enableMeleeWeaponSwitchController)
	{
		return;
	}

	IntroduceSessionData(return);
	IntroduceMainActorData(actorData, return);

	static bool execute = false;

	if
	(
		(sessionData.rightStickY <= 50 ) ||
		(sessionData.rightStickY >= 200)
	)
	{
		if (execute)
		{
			execute = false;

			*reinterpret_cast<byte64 *>(actorData.state) = 0x4201;
			/*
			dmc1.exe+2ED3C7 - 48 C7 01 01420000 - mov qword ptr [rcx],00004201
			dmc1.exe+2ED3CE - B8 01000000       - mov eax,00000001
			*/
		}
	}
	else
	{
		execute = true;
	}
}

void RoundTripReturnController()
{
	if (!activeConfig.enableRoundTripReturnController)
	{
		return;
	}

	IntroduceSessionData(return);

	auto addr = *reinterpret_cast<byte8 **>(appBaseAddr + 0x60AFB0);
	if (!addr)
	{
		return;
	}
	auto & timer = *reinterpret_cast<uint16 *>(addr + 0x19F4);

	static bool execute = false;

	if (sessionData.buttons[0] & activeConfig.roundTripReturnButton)
	{
		if (execute)
		{
			execute = false;

			timer = 0;
		}
	}
	else
	{
		execute = true;
	}
}

void ResetStateController()
{
	if (!activeConfig.enableResetStateController)
	{
		return;
	}

	IntroduceSessionData(return);
	IntroduceMainActorData(actorData, return);

	constexpr uint64 count = countof(activeConfig.resetStateButtons);
	static bool executes[count] = {};

	for_all(index, count)
	{
		auto & button = activeConfig.resetStateButtons[index];
		auto & execute = executes[index];

		if (sessionData.buttons[0] & button)
		{
			if (execute)
			{
				execute = false;

				*reinterpret_cast<byte64 *>(actorData.state) = 1;
			}
		}
		else
		{
			execute = true;
		}
	}
}










void ChargeController()
{
	if (!activeConfig.enableChargeController)
	{
		return;
	}

	IntroduceSessionData(return);
	IntroduceMainActorData(actorData, return);

	using namespace WEAPON;



	if (actorData.rangedWeapon == NIGHTMARE_BETA)
	{
		return;
	}



	auto & load = actorData.chargeTimers[0];
	auto & fire = actorData.chargeTimers[1];

	constexpr int16 loadValue = 1;
	constexpr int16 fireValue = 1;

	int16 maxLoadValue = 60;
	int16 maxFireValue = 30;

	switch (actorData.rangedWeapon)
	{
		case SHOTGUN:
		case GRENADEGUN:
		{
			maxLoadValue = 120;
			maxFireValue = 90;

			break;
		}
	}



	if (sessionData.buttons[0] & activeConfig.chargeButton)
	{
		if (fire < 1)
		{
			load += loadValue;
		}
	}
	else
	{
		if (load >= maxLoadValue)
		{
			fire = maxFireValue;
		}

		load = 0;
	}



	if (load < 1)
	{
		fire -= fireValue;
	}



	if (load > maxLoadValue)
	{
		load = maxLoadValue;
	}
	else if (load < 0)
	{
		load = 0;
	}



	if (fire >= maxFireValue)
	{
		fire = maxFireValue;
	}
	else if (fire < 0)
	{
		fire = 0;
	}
}










#pragma endregion



namespaceStart(Actor);

export void MissionStartSetIndex()
{
	LogFunction();

	activeConfig.Actor.meleeWeaponIndex  = queuedConfig.Actor.meleeWeaponIndex  = 0;
	activeConfig.Actor.rangedWeaponIndex = queuedConfig.Actor.rangedWeaponIndex = 0;

	if (activeConfig.enableMeleeWeaponSwitchController)
	{
		UpdateMeleeWeapon();
	}

	if (activeConfig.enableRangedWeaponSwitchController)
	{
		UpdateRangedWeapon();
	}
}

export void MainLoop()
{
	MeleeWeaponSwitchController();
	RangedWeaponSwitchController();
	RoundTripReturnController();
	ResetStateController();
	ChargeController();
}

namespaceEnd();



#pragma region Toggles

export void ToggleMeleeWeaponSwitchController(bool enable)
{
	LogFunction(enable);

	static bool run = false;

	auto bindings = reinterpret_cast<byte16 *>(appBaseAddr + 0x569D20);



	// Remove Taunt Binding
	{
		auto addr = &bindings[16];
		constexpr uint64 size = 2;

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			SetMemory(addr, 0, size, MemoryFlags_VirtualProtectDestination);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Disable Right Stick Right Trigger Input
	{
		auto addr = (appBaseAddr + 0x2B8A55);
		constexpr uint64 size = 5;
		/*
		dmc1.exe+2B8A55 - 66 41 83 08 02       - or word ptr [r8],02
		dmc1.exe+2B8A5A - 49 C7 40 3A 00000000 - mov qword ptr [r8+3A],00000000
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

	// TauntController
	{
		auto addr     = (appBaseAddr + 0x2ED3A0);
		auto jumpAddr = (appBaseAddr + 0x2ED3A7);
		constexpr uint64 size = 7;
		/*
		dmc1.exe+2ED3A0 - 48 8B 15 E1D72F00 - mov rdx,[dmc1.exe+5EAB88]
		dmc1.exe+2ED3A7 - 48 8B 0D 22D93100 - mov rcx,[dmc1.exe+60ACD0]
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(TauntController, jumpAddr, true, true, 0, 0, size);
			CopyMemory(func.sect2, addr, size, MemoryFlags_VirtualProtectSource);
			WriteAddress(func.sect2, (appBaseAddr + 0x5EAB88), 7);
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

export void ToggleRangedWeaponSwitchController(bool enable)
{
	LogFunction(enable);

	static bool run = false;

	auto bindings = reinterpret_cast<byte16 *>(appBaseAddr + 0x569D20);

	// Disable Map Binding
	{
		auto addr = &bindings[30];
		constexpr uint64 size = 2;

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			SetMemory(addr, 0, size, MemoryFlags_VirtualProtectDestination);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	run = true;
}








export void ToggleForceEdgeFixes(bool enable)
{
	LogFunction(enable);

	static bool run = false;



	// Stinger
	{
		auto addr = (appBaseAddr + 0x2EAD70);
		constexpr uint64 size = 4;
		/*
		dmc1.exe+2EAD70 - 41 0F47 F7  - cmova esi,r15d
		dmc1.exe+2EAD74 - E8 67FEFFFF - call dmc1.exe+2EABE0
		*/

		constexpr byte8 sect0[] =
		{
			mov_esi_r15d,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			SetMemory(addr, 0x90, size, MemoryFlags_VirtualProtectDestination);
			CopyMemory(addr, sect0, sizeof(sect0), MemoryFlags_VirtualProtectDestination);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}



	// Combo 1 Part 1 Round Trip
	{
		auto addr = (appBaseAddr + 0x2DD6F0);
		auto dest = (appBaseAddr + 0x2DD6F2);
		constexpr uint64 size = 2;
		/*
		dmc1.exe+2DD6F0 - 74 C0             - je dmc1.exe+2DD6B2
		dmc1.exe+2DD6F2 - 48 C7 03 01410000 - mov qword ptr [rbx],00004101
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			WriteAddress(addr, dest, size);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Combo 1 Part 2 Round Trip
	{
		auto addr = (appBaseAddr + 0x2DDA45);
		auto dest = (appBaseAddr + 0x2DDA47);
		constexpr uint64 size = 2;
		/*
		dmc1.exe+2DDA45 - 74 12          - je dmc1.exe+2DDA59
		dmc1.exe+2DDA47 - C7 03 01410000 - mov [rbx],00004101
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			WriteAddress(addr, dest, size);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Combo 2 Part 3 Round Trip
	{
		auto addr = (appBaseAddr + 0x2DE723);
		auto dest = (appBaseAddr + 0x2DE725);
		constexpr uint64 size = 2;
		/*
		dmc1.exe+2DE723 - 74 0F          - je dmc1.exe+2DE734
		dmc1.exe+2DE725 - C7 03 01410000 - mov [rbx],00004101
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			WriteAddress(addr, dest, size);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Million Slash Round Trip
	{
		auto addr = (appBaseAddr + 0x2DF82D);
		auto dest = (appBaseAddr + 0x2DF82F);
		constexpr uint64 size = 2;
		/*
		dmc1.exe+2DF82D - 74 12          - je dmc1.exe+2DF841
		dmc1.exe+2DF82F - C7 03 01410000 - mov [rbx],00004101
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			WriteAddress(addr, dest, size);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}



	run = true;
}

export void ToggleSpardaFixes(bool enable)
{
	LogFunction(enable);

	static bool run = false;



	// Disable Reset Melee Weapon
	{
		auto addr = (appBaseAddr + 0x2C579F);
		constexpr uint64 size = 7;
		/*
		dmc1.exe+2C579F - 44 88 A7 CC1B0000 - mov [rdi+00001BCC],r12l
		dmc1.exe+2C57A6 - 0FB6 87 CC1B0000  - movzx eax,byte ptr [rdi+00001BCC]
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

	// Disable Skip Load Assets Evaluation
	{
		auto addr = (appBaseAddr + 0x2C57AD);
		constexpr uint64 size = 9;
		/*
		dmc1.exe+2C57AD - 44 3A C0      - cmp r8l,al
		dmc1.exe+2C57B0 - 0F84 99000000 - je dmc1.exe+2C584F
		dmc1.exe+2C57B6 - 0FB6 C8       - movzx ecx,al
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



	/*
	Effect Manager

	dmc1.exe+831DF - FF 94 C6 40284800   - call qword ptr [rsi+rax*8+00482840]
	dmc1.exe+831E6 - F3 0F10 83 00010000 - movss xmm0,[rbx+00000100]

	Some sparda-specific effect ids:



	33 Small Fireball

	dmc1.exe+73210 - 8B 41 08 - mov eax,[rcx+08]



	35 Giant Slash

	dmc1.exe+748C0 - 8B 41 08 - mov eax,[rcx+08]



	45 Big Fireball

	dmc1.exe+75AA0 - 8B 41 08 - mov eax,[rcx+08]



	Giant Slash and Big Fireball require resources from Mundus part 2.
	If they are not available the game will crash.
	*/

	// Giant Slash
	{
		auto funcAddrs = reinterpret_cast<byte8 **>(appBaseAddr + 0x482840);
		auto addr = reinterpret_cast<byte8 *>(&funcAddrs[35]);
		constexpr uint64 size = 8;

		static Function func = {};

		constexpr byte8 sect2[] =
		{
			0x84, 0xC0,                         // test al,al
			0x0F, 0x85, 0x00, 0x00, 0x00, 0x00, // jne dmc1.exe+748C0
			0xC3,                               // ret
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(IsMundusPart2, 0, true, false, 0, 0, sizeof(sect2), 0, 0, true);
			CopyMemory(func.sect2, sect2, sizeof(sect2));
			WriteAddress((func.sect2 + 2), (appBaseAddr + 0x748C0), 6);
		}

		if (enable)
		{
			Write<byte8 *>(addr, func.addr);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Big Fireball
	{
		auto funcAddrs = reinterpret_cast<byte8 **>(appBaseAddr + 0x482840);
		auto addr = reinterpret_cast<byte8 *>(&funcAddrs[45]);
		constexpr uint64 size = 8;

		static Function func = {};

		constexpr byte8 sect2[] =
		{
			0x84, 0xC0,                         // test al,al
			0x0F, 0x85, 0x00, 0x00, 0x00, 0x00, // jne dmc1.exe+75AA0
			0xC3,                               // ret
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(IsMundusPart2, 0, true, false, 0, 0, sizeof(sect2), 0, 0, true);
			CopyMemory(func.sect2, sect2, sizeof(sect2));
			WriteAddress((func.sect2 + 2), (appBaseAddr + 0x75AA0), 6);
		}

		if (enable)
		{
			Write<byte8 *>(addr, func.addr);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}



	// Equip Sparda
	{
		auto addr = (appBaseAddr + 0x3F257B);
		constexpr uint64 size = 7;
		/*
		dmc1.exe+3F257B - C6 86 CC1B0000 04 - mov byte ptr [rsi+00001BCC],04
		dmc1.exe+3F2582 - 40 88 AB A1AC0000 - mov [rbx+0000ACA1],bpl
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			Write<uint8>((addr + 6), WEAPON::SPARDA);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}



	run = true;
}

export void ToggleYamatoFixes(bool enable)
{
	LogFunction(enable);

	static bool run = false;



	// Model
	{
		auto addr = (appBaseAddr + 0x2CDE98);
		auto dest = (appBaseAddr + 0x2CDE9A);
		constexpr uint64 size = 2;
		/*
		dmc1.exe+2CDE98 - 75 6C          - jne dmc1.exe+2CDF06
		dmc1.exe+2CDE9A - 8B 87 801F0000 - mov eax,[rdi+00001F80]
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			WriteAddress(addr, dest, size);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Melee Weapons Menu
	{
		auto addr = (appBaseAddr + 0x3EBAE3);
		auto dest = (appBaseAddr + 0x3EBAE5);
		constexpr uint64 size = 2;
		/*
		dmc1.exe+3EBAE3 - 75 07       - jne dmc1.exe+3EBAEC
		dmc1.exe+3EBAE5 - 0D CE000000 - or eax,00CE
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			WriteAddress(addr, dest, size);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}



	run = true;
}

export void ToggleDisableIdleTimer(bool enable)
{
	LogFunction(enable);

	static bool run = false;

	{
		auto addr = (appBaseAddr + 0x2C64D7);
		constexpr uint64 size = 4;
		/*
		dmc1.exe+2C64D7 - 66 41 FF CA          - dec r10w
		dmc1.exe+2C64DB - 66 44 89 93 101A0000 - mov [rbx+00001A10],r10w
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

export void ToggleAirHikeCoreAbility(bool enable)
{
	LogFunction(enable);

	static bool run = false;

	{
		auto addr = (appBaseAddr + 0x2EC755);
		constexpr uint64 size = 2;
		/*
		dmc1.exe+2EC755 - 74 14 - je dmc1.exe+2EC76B
		dmc1.exe+2EC757 - 3C 03 - cmp al,03
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

export void ToggleInfiniteRoundTrip(bool enable)
{
	LogFunction(enable);

	static bool run = false;



	{
		auto addr = (appBaseAddr + 0x2CE8CD);
		constexpr uint64 size = 3;
		/*
		dmc1.exe+2CE8CD - 66 FF C8          - dec ax
		dmc1.exe+2CE8D0 - 66 89 83 F4190000 - mov [rbx+000019F4],ax
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
		auto addr = (appBaseAddr + 0x2CE1F7);
		constexpr uint64 size = 3;
		/*
		dmc1.exe+2CE1F7 - 66 FF C8          - dec ax
		dmc1.exe+2CE1FA - 66 89 83 F4190000 - mov [rbx+000019F4],ax
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

export void ToggleDisableWeaponRestrictions(bool enable)
{
	LogFunction(enable);

	static bool run = false;

	// Disable track check. Allows equipping weapons other than Sparda against Mundus.
	{
		auto addr = (appBaseAddr + 0x3C8A89);
		constexpr uint64 size = 6;
		/*
		dmc1.exe+3C8A89 - 0F85 22030000  - jne dmc1.exe+3C8DB1
		dmc1.exe+3C8A8F - 8B 80 74020000 - mov eax,[rax+00000274]
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






export void ToggleChargeFixes(bool enable)
{
	//return;




	LogFunction(enable);

	static bool run = false;



	// Update
	{
		auto addr = (appBaseAddr + 0x2CB655);
		constexpr uint64 size = 7;
		/*
		dmc1.exe+2CB655 - 66 89 B3 661C0000 - mov [rbx+00001C66],si
		dmc1.exe+2CB65C - 41 8B 80 081D0000 - mov eax,[r8+00001D08]
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

	// Lock-On Update
	{
		auto addr = (appBaseAddr + 0x2F0734);
		constexpr uint64 size = 7;
		/*
		dmc1.exe+2F0734 - 66 89 91 661C0000       - mov [rcx+00001C66],dx
		dmc1.exe+2F073B - F7 87 40200000 00001000 - test [rdi+00002040],100000
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

	// Lock-On Charging
	{
		auto addr = (appBaseAddr + 0x2F0691);
		constexpr uint64 size = 7;
		/*
		dmc1.exe+2F0691 - 66 FF 81 661C0000 - inc word ptr [rcx+00001C66]
		dmc1.exe+2F0698 - 0FB6 83 481C0000  - movzx eax,byte ptr [rbx+00001C48]
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

	// Lock-On Charging Maybe Alastor-specific
	{
		auto addr = (appBaseAddr + 0x2F06DC);
		constexpr uint64 size = 7;
		/*
		dmc1.exe+2F06DC - 66 89 83 661C0000 - mov [rbx+00001C66],ax
		dmc1.exe+2F06E3 - EB 56             - jmp dmc1.exe+2F073B
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

	// Lock-On Charge Shot Let Go Reset
	{
		auto addr = (appBaseAddr + 0x2F0756);
		constexpr uint64 size = 7;
		/*
		dmc1.exe+2F0756 - 66 89 93 661C0000 - mov [rbx+00001C66],dx
		dmc1.exe+2F075D - 80 BF 661E0000 02 - cmp byte ptr [rdi+00001E66],02
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



	// Set Max Active Charge
	{
		auto addr = (appBaseAddr + 0x2F072D);
		constexpr uint64 size = 7;
		/*
		dmc1.exe+2F072D - 66 89 81 681C0000 - mov [rcx+00001C68],ax
		dmc1.exe+2F0734 - 66 89 91 661C0000 - mov [rcx+00001C66],dx
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

	// Sub Active Charge
	{
		auto addr = (appBaseAddr + 0x2CB17A);
		constexpr uint64 size = 7;
		/*
		dmc1.exe+2CB17A - 66 89 83 681C0000 - mov [rbx+00001C68],ax
		dmc1.exe+2CB181 - 0FB7 83 D81B0000  - movzx eax,word ptr [rbx+00001BD8]
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

















#pragma endregion
