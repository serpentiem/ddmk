export module Input;

import Core;

#include "../Core/Macros.h"

import Config;
import Global;
import Vars;



Keyboard dummyKeyboard = {};

Gamepad dummyGamepad = {};
Gamepad gamepads[PLAYER::COUNT] = {};
byte8 * gamepadAddrs[PLAYER::COUNT] = {};



export void ToggleCursor()
{
	if (g_show)
	{
		Windows_ToggleCursor(true);
	}
	else
	{
		Windows_ToggleCursor(!activeConfig.hideMouseCursor);
	}
}



auto GetKeyboard()
{
	return *reinterpret_cast<Keyboard **>(appBaseAddr + 0xF242E4);
	/*
	dmc4.exe+4CA179 - 8B 35 E4423201 - mov esi,[dmc4.exe+F242E4]
	dmc4.exe+4CA17F - 85 F6          - test esi,esi
	*/
}

Keyboard * __fastcall GetKeyboardByActor(byte8 * actorBaseAddr)
{
	auto keyboard = GetKeyboard();

	if (!actorBaseAddr)
	{
		return keyboard;
	}



	for_all(playerIndex, activeConfig.Actor.playerCount)
	{
		auto & playerData = activeConfig.Actor.playerData[playerIndex];
		auto & newActorData = g_newActorData[playerIndex];

		if
		(
			(newActorData.baseAddr != actorBaseAddr) ||
			(playerIndex != activeConfig.Actor.keyboard)
		)
		{
			continue;
		}

		return keyboard;
	}



	return &dummyKeyboard;
}

Keyboard * __fastcall GetKeyboardByData(byte8 * dataAddr)
{
	auto keyboard = GetKeyboard();

	if (!dataAddr)
	{
		return keyboard;
	}



	auto actorBaseAddr = (dataAddr - 0x1884);
	/*
	dmc4.exe+4C98AF - 8D B7 84180000 - lea esi,[edi+00001884]
	dmc4.exe+4C98B5 - 56             - push esi
	dmc4.exe+4C98B6 - E8 05750000    - call dmc4.exe+4D0DC0
	*/

	return GetKeyboardByActor(actorBaseAddr);
}



void __fastcall InitGamepads(byte8 * baseAddr)
{
	gamepadAddrs[0] = (baseAddr + 0xBC0);

	for_each(playerIndex, 1, PLAYER::COUNT)
	{
		auto & gamepad = gamepads[playerIndex];

		gamepad.addr = (baseAddr + 0x3C + (0x2CC * playerIndex));

		gamepadAddrs[playerIndex] = reinterpret_cast<byte8 *>(&gamepad);
	}
}



auto GetGamepad()
{
	return *reinterpret_cast<Gamepad **>(appBaseAddr + 0xF2432C);
	/*
	dmc4.exe+4D0DC9 - A1 2C433201         - mov eax,[dmc4.exe+F2432C]
	dmc4.exe+4D0DCE - F3 0F7E 80 D40B0000 - movq xmm0,[eax+00000BD4]
	*/
}

Gamepad * __fastcall GetGamepadByActor(byte8 * actorBaseAddr)
{
	auto gamepad = GetGamepad();

	if (!actorBaseAddr)
	{
		return gamepad;
	}



	for_all(playerIndex, activeConfig.Actor.playerCount)
	{
		auto & playerData = activeConfig.Actor.playerData[playerIndex];
		auto & newActorData = g_newActorData[playerIndex];
		auto & gamepadAddr = gamepadAddrs[playerIndex];

		if (newActorData.baseAddr != actorBaseAddr)
		{
			continue;
		}

		gamepad = reinterpret_cast<Gamepad *>(gamepadAddr - 0xBC0);

		return gamepad;
	}



	return &dummyGamepad;
}

Gamepad * __fastcall GetGamepadByData(byte8 * dataAddr)
{
	auto gamepad = GetGamepad();

	if (!dataAddr)
	{
		return gamepad;
	}



	auto actorBaseAddr = (dataAddr - 0x1884);
	/*
	dmc4.exe+4C98AF - 8D B7 84180000 - lea esi,[edi+00001884]
	dmc4.exe+4C98B5 - 56             - push esi
	dmc4.exe+4C98B6 - E8 05750000    - call dmc4.exe+4D0DC0
	*/

	return GetGamepadByActor(actorBaseAddr);
}



namespaceStart(Input);

export void ToggleExtensions(bool enable)
{
	LogFunction(enable);

	static bool run = false;



	// GetKeyboard X
	{
		auto addr     = (appBaseAddr + 0x4D0FC3);
		auto jumpAddr = (appBaseAddr + 0x4D0FC9);
		constexpr size_t size = 6;
		/*
		dmc4.exe+4D0FC3 - 8B 15 E4423201 - mov edx,[dmc4.exe+F242E4]
		dmc4.exe+4D0FC9 - 8B C8          - mov ecx,eax
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x50, // push eax
		};
		constexpr byte8 sect1[] =
		{
			0x8B, 0x45, 0x0C, // mov eax,[ebp+0C]
			0x8B, 0x48, 0x08, // mov ecx,[eax+08]
		};
		constexpr byte8 sect2[] =
		{
			0x8B, 0xD0, // mov edx,eax
			0x58,       // pop eax
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(GetKeyboardByData, jumpAddr, FunctionFlags_SaveRegisters, sizeof(sect0), sizeof(sect1), sizeof(sect2));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			CopyMemory(func.sect1, sect1, sizeof(sect1));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
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

	// GetKeyboard Y
	{
		auto addr     = (appBaseAddr + 0x4D10C8);
		auto jumpAddr = (appBaseAddr + 0x4D10CE);
		constexpr size_t size = 6;
		/*
		dmc4.exe+4D10C8 - 8B 15 E4423201 - mov edx,[dmc4.exe+F242E4]
		dmc4.exe+4D10CE - 8B C8          - mov ecx,eax
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x50, // push eax
		};
		constexpr byte8 sect1[] =
		{
			0x8B, 0x45, 0x0C, // mov eax,[ebp+0C]
			0x8B, 0x48, 0x08, // mov ecx,[eax+08]
		};
		constexpr byte8 sect2[] =
		{
			0x8B, 0xD0, // mov edx,eax
			0x58,       // pop eax
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(GetKeyboardByData, jumpAddr, FunctionFlags_SaveRegisters, sizeof(sect0), sizeof(sect1), sizeof(sect2));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			CopyMemory(func.sect1, sect1, sizeof(sect1));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
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

	// GetKeyboard Main
	{
		auto addr     = (appBaseAddr + 0x4CA179);
		auto jumpAddr = (appBaseAddr + 0x4CA17F);
		constexpr size_t size = 6;
		/*
		dmc4.exe+4CA179 - 8B 35 E4423201 - mov esi,[dmc4.exe+F242E4]
		dmc4.exe+4CA17F - 85 F6          - test esi,esi
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x50, // push eax
		};
		constexpr byte8 sect1[] =
		{
			0x8B, 0x4D, 0x0C, // mov ecx,[ebp+0C]
		};
		constexpr byte8 sect2[] =
		{
			0x8B, 0xF0, // mov esi,eax
			0x58,       // pop eax
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(GetKeyboardByActor, jumpAddr, FunctionFlags_SaveRegisters, sizeof(sect0), sizeof(sect1), sizeof(sect2));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			CopyMemory(func.sect1, sect1, sizeof(sect1));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
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



	// InitGamepads
	{
		auto addr     = (appBaseAddr + 0x6EF90B);
		auto jumpAddr = (appBaseAddr + 0x6EF911);
		constexpr size_t size = 6;
		/*
		dmc4.exe+6EF90B - 89 35 2C433201 - mov [dmc4.exe+F2432C],esi
		dmc4.exe+6EF911 - 53             - push ebx
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			0x8B, 0xCE, // mov ecx,esi
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(InitGamepads, jumpAddr, (FunctionFlags_SaveRegisters | FunctionFlags_NoResult), size, sizeof(sect1));
			CopyMemory(func.sect0, addr, size, MemoryFlags_VirtualProtectSource);
			CopyMemory(func.sect1, sect1, sizeof(sect1));
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

	// UpdateGamepads
	{
		auto addr     = (appBaseAddr + 0x18CEE5);
		auto jumpAddr = (appBaseAddr + 0x18CEEA);
		constexpr size_t size = 5;
		/*
		dmc4.exe+18CEE5 - E8 560B0000    - call dmc4.exe+18DA40
		dmc4.exe+18CEEA - 8B 97 E00F0000 - mov edx,[edi+00000FE0]
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			0xBE, 0x00, 0x00, 0x00, 0x00, // mov esi
			0xE8, 0x00, 0x00, 0x00, 0x00, // call dmc4.exe+18DA40
		};

		constexpr size_t size1 = (sizeof(sect1) * (PLAYER::COUNT - 1));

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(0, jumpAddr, 0, size, size1);
			CopyMemory(func.sect0, addr, size, MemoryFlags_VirtualProtectSource);
			WriteCall(func.sect0, (appBaseAddr + 0x18DA40));



			off_t pos = 0;

			for_each(playerIndex, 1, PLAYER::COUNT)
			{
				auto & gamepad = gamepads[playerIndex];

				auto dest = (func.sect1 + pos);

				CopyMemory(dest, sect1, sizeof(sect1));
				*reinterpret_cast<Gamepad **>(dest + 1) = &gamepad;
				WriteCall((dest + 5), (appBaseAddr + 0x18DA40));

				pos += sizeof(sect1);
			}
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

	// GetGamepad
	{
		auto addr     = (appBaseAddr + 0x4D0DC9);
		auto jumpAddr = (appBaseAddr + 0x4D0DCE);
		constexpr size_t size = 5;
		/*
		dmc4.exe+4D0DC9 - A1 2C433201         - mov eax,[dmc4.exe+F2432C]
		dmc4.exe+4D0DCE - F3 0F7E 80 D40B0000 - movq xmm0,[eax+00000BD4]
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			0x8B, 0x45, 0x0C, // mov eax,[ebp+0C]
			0x8B, 0x48, 0x08, // mov ecx,[eax+08]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(GetGamepadByData, jumpAddr, FunctionFlags_SaveRegisters, 0, sizeof(sect1));
			CopyMemory(func.sect1, sect1, sizeof(sect1));
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

namespaceEnd();
