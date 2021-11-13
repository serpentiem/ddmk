export module Input;

import Core;

#include "../Core/Macros.h"

import Windows;
import DI8;

import Config;
import Global;
import Vars;



KeyboardData dummyKeyboardData = {};









GamepadManager newGamepadManagers[PLAYER::COUNT] = {};




GamepadManager dummyGamepadManager = {};






namespaceStart(DI8);

export IDirectInputDevice8A * GetKeyboardAddr()
{
	auto addr = *reinterpret_cast<byte8 **>(appBaseAddr + 0xF2429C);
	if (!addr)
	{
		return 0;
	}

	addr = *reinterpret_cast<byte8 **>(addr + 0x28288);
	if (!addr)
	{
		return 0;
	}

	return *reinterpret_cast<IDirectInputDevice8A **>(addr + 0xA08);

	/*
	dmc4.exe+6E69A0 - A1 9C423201    - mov eax,[dmc4.exe+F2429C]
	dmc4.exe+5E9B6A - 8B 8E 88820200 - mov ecx,[esi+00028288]
	dmc4.exe+6E9E3A - 8B 86 080A0000 - mov eax,[esi+00000A08]
	*/
}

namespaceEnd();





export auto GetKeyboardDataAddr()
{
	return *reinterpret_cast<KeyboardData **>(appBaseAddr + 0xF242E4);
	/*
	dmc4.exe+4CA179 - 8B 35 E4423201 - mov esi,[dmc4.exe+F242E4]
	dmc4.exe+4CA17F - 85 F6          - test esi,esi
	*/
}



export auto GetGamepadManagerAddr()
{
	return *reinterpret_cast<GamepadManager **>(appBaseAddr + 0xF2432C);
	/*
	dmc4.exe+4D0DC9 - A1 2C433201         - mov eax,[dmc4.exe+F2432C]
	dmc4.exe+4D0DCE - F3 0F7E 80 D40B0000 - movq xmm0,[eax+00000BD4]
	*/
}


















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




#pragma region Keyboard











KeyboardData * __fastcall GetKeyboardDataAddrByActorBaseAddr(byte8 * actorBaseAddr)
{
	auto keyboardDataAddr = GetKeyboardDataAddr();
	if (!keyboardDataAddr)
	{
		return &dummyKeyboardData;
	}
	auto & keyboardData = *keyboardDataAddr;



	if (activeConfig.enableCharacterSwitchController)
	{
		return &keyboardData;
	}



	for_all(playerIndex, activeConfig.Actor.playerCount)
	{
		auto & newActorData = g_newActorData[playerIndex];

		if
		(
			(newActorData.baseAddr != actorBaseAddr) ||
			(playerIndex != activeConfig.keyboardPlayerIndex)
		)
		{
			continue;
		}



		return &keyboardData;
	}



	return &dummyKeyboardData;
}

KeyboardData * __fastcall GetKeyboardDataAddrByActorInputDataAddr(byte8 * actorInputDataAddr)
{
	auto actorBaseAddr = (actorInputDataAddr - 0x1884);
	/*
	dmc4.exe+4C98AF - 8D B7 84180000 - lea esi,[edi+00001884]
	dmc4.exe+4C98B5 - 56             - push esi
	dmc4.exe+4C98B6 - E8 05750000    - call dmc4.exe+4D0DC0
	*/

	return GetKeyboardDataAddrByActorBaseAddr(actorBaseAddr);
}

#pragma endregion



















void __fastcall InitGamepadManager(GamepadManager * gamepadManagerAddr)
{
	if (!gamepadManagerAddr)
	{
		return;
	}
	auto & gamepadManager = *gamepadManagerAddr;



	for_all(playerIndex, PLAYER::COUNT)
	{
		auto & gamepadMetadata   = gamepadManager.gamepadMetadata[playerIndex];
		auto & newGamepadManager = newGamepadManagers[playerIndex];
		auto & gamepadData       = newGamepadManager.gamepadData[0];

		gamepadData.gamepadMetadataAddr = &gamepadMetadata;
	}
}







export void UpdateGamepadPlayerIndices()
{
	auto gamepadManagerAddr = GetGamepadManagerAddr();
	if (!gamepadManagerAddr)
	{
		return;
	}
	auto & gamepadManager = *gamepadManagerAddr;



	for_all(playerIndex, PLAYER::COUNT)
	{
		auto & gamepadMetadata = gamepadManager.gamepadMetadata[playerIndex];

		gamepadMetadata.playerIndex = (activeConfig.enableCharacterSwitchController) ? 0 : playerIndex;
	}
}























// @Research: Consider reference.
GamepadManager * __fastcall GetGamepadManagerAddrByActorBaseAddr(byte8 * actorBaseAddr)
{
	auto gamepadManagerAddr = GetGamepadManagerAddr();
	if
	(
		!actorBaseAddr ||
		!gamepadManagerAddr
	)
	{
		return &dummyGamepadManager;
	}
	auto & gamepadManager = *gamepadManagerAddr;



	for_all(playerIndex, activeConfig.Actor.playerCount)
	{
		auto & newActorData      = g_newActorData[playerIndex];
		auto & newGamepadManager = newGamepadManagers[playerIndex];

		if (newActorData.baseAddr != actorBaseAddr)
		{
			continue;
		}

		if (playerIndex == 0)
		{
			return &gamepadManager;
		}



		return &newGamepadManager;
	}



	return &dummyGamepadManager;
}














GamepadManager * __fastcall GetGamepadManagerAddrByActorInputDataAddr(byte8 * actorInputDataAddr)
{
	auto actorBaseAddr = (actorInputDataAddr - 0x1884);
	/*
	dmc4.exe+4C98AF - 8D B7 84180000 - lea esi,[edi+00001884]
	dmc4.exe+4C98B5 - 56             - push esi
	dmc4.exe+4C98B6 - E8 05750000    - call dmc4.exe+4D0DC0
	*/

	return GetGamepadManagerAddrByActorBaseAddr(actorBaseAddr);
}











export byte32 GetGamepadFlags(size_t playerIndex = 0)
{
	auto gamepadManagerAddr = GetGamepadManagerAddr();
	if (!gamepadManagerAddr)
	{
		return 0;
	}
	auto & gamepadManager = *gamepadManagerAddr;

	auto & gamepadMetadata = gamepadManager.gamepadMetadata[playerIndex];

	return gamepadMetadata.flags[0];
}
















namespaceStart(Input);

export void ToggleExtensions(bool enable)
{
	LogFunction(enable);

	static bool run = false;



	// GetKeyboardData X
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
			func = CreateFunction(GetKeyboardDataAddrByActorInputDataAddr, jumpAddr, FunctionFlags_SaveRegisters, sizeof(sect0), sizeof(sect1), sizeof(sect2));
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

	// GetKeyboardData Y
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
			func = CreateFunction(GetKeyboardDataAddrByActorInputDataAddr, jumpAddr, FunctionFlags_SaveRegisters, sizeof(sect0), sizeof(sect1), sizeof(sect2));
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

	// GetKeyboardData Main
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
			func = CreateFunction(GetKeyboardDataAddrByActorBaseAddr, jumpAddr, FunctionFlags_SaveRegisters, sizeof(sect0), sizeof(sect1), sizeof(sect2));
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



	// InitGamepadManager
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
			func = CreateFunction(InitGamepadManager, jumpAddr, (FunctionFlags_SaveRegisters | FunctionFlags_NoResult), size, sizeof(sect1));
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

	// UpdateGamepadData
	{
		auto addr     = (appBaseAddr + 0x18CEDF);
		auto jumpAddr = (appBaseAddr + 0x18CEEA);
		constexpr size_t size = 11;
		/*
		dmc4.exe+18CEDF - 8D B7 C00B0000 - lea esi,[edi+00000BC0]
		dmc4.exe+18CEE5 - E8 560B0000    - call dmc4.exe+18DA40
		dmc4.exe+18CEEA - 8B 97 E00F0000 - mov edx,[edi+00000FE0]
		*/




		static Function func = {};

		constexpr byte8 sect1[] =
		{
			0xBE, 0x00, 0x00, 0x00, 0x00, // mov esi
			0xE8, 0x00, 0x00, 0x00, 0x00, // call dmc4.exe+18DA40
		};







		//constexpr size_t size0 = (sizeof(sect0) * PLAYER::COUNT);
		constexpr size_t size1 = (sizeof(sect1) * (PLAYER::COUNT - 1));

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(0, jumpAddr, 0, size, size1);
			//func = CreateFunction(0, jumpAddr, 0, size0);
			CopyMemory(func.sect0, addr, size, MemoryFlags_VirtualProtectSource);
			WriteCall((func.sect0 + 6), (appBaseAddr + 0x18DA40));








			off_t pos = 0;





			for_each(playerIndex, 1, PLAYER::COUNT)
			//for_all(playerIndex, PLAYER::COUNT)
			{
				auto & newGamepadManager = newGamepadManagers[playerIndex];
				auto & gamepadData = newGamepadManager.gamepadData[0];

				auto dest = (func.sect1 + pos);

				CopyMemory(dest, sect1, sizeof(sect1));
				*reinterpret_cast<GamepadData **>(dest + 1) = &gamepadData;
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
			func = CreateFunction(GetGamepadManagerAddrByActorInputDataAddr, jumpAddr, FunctionFlags_SaveRegisters, 0, sizeof(sect1));
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
