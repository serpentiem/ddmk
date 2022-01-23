module;
#include "../ThirdParty/ImGui/imgui.h"
export module Hooks;

import Core;
import Core_ImGui;

#include "../Core/Macros.h"

import Windows;
import DXGI;
import D3D10;
import DI8;
import XI;

using namespace Windows;
using namespace DXGI;
using namespace D3D10;
using namespace DI8;
using namespace XI;

import HooksBase;

import Config;
import Global;
import Graphics; // Toggle, UpdateFrameRate
import GUI;      // keyBindings
import Scene;    // SetScene
import Window;   // ToggleBorderless
import Vars;

#define debug false



namespaceStart(Hook::Windows);

void CreateFileA_Function(LPCSTR lpFileName)
{
	SetScene(lpFileName);
}

namespaceEnd();



namespaceStart(Hook::DXGI);

void Present_Function()
{
	if (g_update3D)
	{
		g_update3D = false;

		ToggleBorderless(activeConfig.borderless);
	}
}

namespaceEnd();



namespaceStart(Hook::D3D10);

void D3D10CreateDeviceAndSwapChain_Function()
{
	Graphics::Toggle(false);
	Graphics::Toggle(true);

	UpdateFrameRate();
}

namespaceEnd();



void UpdateKeyboard_Function(DI8::DIKEYBOARDSTATE * stateAddr)
{
	if (!stateAddr)
	{
		return;
	}
	auto & state = *stateAddr;



	auto & keyBinding = characterSwitchControllerKeyBinding;

	keyBinding.UpdateKeyData(state.keys);
	keyBinding.Check(state.keys);
}



namespaceStart(Hooks);

export void Init()
{
	LogFunction();



	Install
	(
		(appBaseAddr + 0xB732F0),
		::Base::Windows::RegisterClassExW,
		::Hook::Windows::RegisterClassExW
	);

	Install
	(
		(appBaseAddr + 0xB73328),
		::Base::Windows::CreateWindowExW,
		::Hook::Windows::CreateWindowExW
	);

	Install
	(
		(appBaseAddr + 0xB73128),
		::Base::Windows::CreateFileA,
		::Hook::Windows::CreateFileA
	);

	::Hook::Windows::CreateFileA_func = ::Hook::Windows::CreateFileA_Function;

	Install
	(
		(appBaseAddr + 0xB73090),
		::Base::Windows::CreateFileW,
		::Hook::Windows::CreateFileW
	);

	::Hook::DXGI::Present_func = ::Hook::DXGI::Present_Function;

	::Hook::D3D10::D3D10CreateDeviceAndSwapChain_func = ::Hook::D3D10::D3D10CreateDeviceAndSwapChain_Function;

	Install
	(
		(appBaseAddr + 0xB733CC),
		::Base::D3D10::D3D10CreateDeviceAndSwapChain,
		::Hook::D3D10::D3D10CreateDeviceAndSwapChain
	);

	UpdateKeyboard_func = UpdateKeyboard_Function;



	constexpr bool enable = true;
	static bool run = false;



	// GetDeviceStateAKeyboard
	{
		auto addr     = (appBaseAddr + 0x6E9E50);
		auto jumpAddr = (appBaseAddr + 0x6E9E55);
		constexpr new_size_t size = 5;
		/*
		dmc4.exe+6E9E50 - 8B 41 24 - mov eax,[ecx+24]
		dmc4.exe+6E9E53 - FF D0    - call eax
		dmc4.exe+6E9E55 - 85 C0    - test eax,eax
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x83, 0xEC, 0x10,             // sub esp,10
			0x51,                         // push ecx
			0x56,                         // push esi
			0x57,                         // push edi
			0xB9, 0x03, 0x00, 0x00, 0x00, // mov ecx,00000003
			0x8D, 0x74, 0x24, 0x1C,       // lea esi,[esp+1C]
			0x8D, 0x7C, 0x24, 0x0C,       // lea edi,[esp+0C]
			0xF3, 0xA5,                   // repe movsd
			0xB9, 0x03, 0x00, 0x00, 0x00, // mov ecx,00000003
			0x8D, 0x74, 0x24, 0x0C,       // lea esi,[esp+0C]
			0x8D, 0x7C, 0x24, 0x18,       // lea edi,[esp+18]
			0xF3, 0xA5,                   // repe movsd
			0x5F,                         // pop edi
			0x5E,                         // pop esi
			0x59,                         // pop ecx
			0x8B, 0x41, 0x24,             // mov eax,[ecx+24]
			0xFF, 0xD0,                   // call eax
			0x89, 0x44, 0x24, 0x0C,       // mov [esp+0C],eax
		};

		constexpr byte8 sect2[] =
		{
			0x58, // pop eax
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(::Hook::DI8::GetDeviceStateA, jumpAddr, false, true, sizeof(sect0), 0, sizeof(sect2));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
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

	// GetDeviceStateAMouse
	{
		auto addr     = (appBaseAddr + 0x6EA709);
		auto jumpAddr = (appBaseAddr + 0x6EA70E);
		constexpr new_size_t size = 5;
		/*
		dmc4.exe+6EA709 - 8B 41 24 - mov eax,[ecx+24]
		dmc4.exe+6EA70C - FF D0    - call eax
		dmc4.exe+6EA70E - 85 C0    - test eax,eax
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x83, 0xEC, 0x10,             // sub esp,10
			0x51,                         // push ecx
			0x56,                         // push esi
			0x57,                         // push edi
			0xB9, 0x03, 0x00, 0x00, 0x00, // mov ecx,00000003
			0x8D, 0x74, 0x24, 0x1C,       // lea esi,[esp+1C]
			0x8D, 0x7C, 0x24, 0x0C,       // lea edi,[esp+0C]
			0xF3, 0xA5,                   // repe movsd
			0xB9, 0x03, 0x00, 0x00, 0x00, // mov ecx,00000003
			0x8D, 0x74, 0x24, 0x0C,       // lea esi,[esp+0C]
			0x8D, 0x7C, 0x24, 0x18,       // lea edi,[esp+18]
			0xF3, 0xA5,                   // repe movsd
			0x5F,                         // pop edi
			0x5E,                         // pop esi
			0x59,                         // pop ecx
			0x8B, 0x41, 0x24,             // mov eax,[ecx+24]
			0xFF, 0xD0,                   // call eax
			0x89, 0x44, 0x24, 0x0C,       // mov [esp+0C],eax
		};

		constexpr byte8 sect2[] =
		{
			0x58, // pop eax
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(::Hook::DI8::GetDeviceStateA, jumpAddr, false, true, sizeof(sect0), 0, sizeof(sect2));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
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

	// GetDeviceStateAGamepad
	{
		auto addr     = (appBaseAddr + 0x6EE146);
		auto jumpAddr = (appBaseAddr + 0x6EE14E);
		constexpr new_size_t size = 6;
		/*
		dmc4.exe+6EE146 - 68 10010000 - push 00000110
		dmc4.exe+6EE14B - 57          - push edi
		dmc4.exe+6EE14C - FF D1       - call ecx
		dmc4.exe+6EE14E - 85 C0       - test eax,eax
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x83, 0xEC, 0x10,             // sub esp,10
			0x51,                         // push ecx
			0x56,                         // push esi
			0x57,                         // push edi
			0xB9, 0x03, 0x00, 0x00, 0x00, // mov ecx,00000003
			0x8D, 0x74, 0x24, 0x1C,       // lea esi,[esp+1C]
			0x8D, 0x7C, 0x24, 0x0C,       // lea edi,[esp+0C]
			0xF3, 0xA5,                   // repe movsd
			0xB9, 0x03, 0x00, 0x00, 0x00, // mov ecx,00000003
			0x8D, 0x74, 0x24, 0x0C,       // lea esi,[esp+0C]
			0x8D, 0x7C, 0x24, 0x18,       // lea edi,[esp+18]
			0xF3, 0xA5,                   // repe movsd
			0x5F,                         // pop edi
			0x5E,                         // pop esi
			0x59,                         // pop ecx
			0xFF, 0xD1,                   // call ecx
			0x89, 0x44, 0x24, 0x0C,       // mov [esp+0C],eax
		};

		constexpr byte8 sect2[] =
		{
			0x58, // pop eax
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(::Hook::DI8::GetDeviceStateA, jumpAddr, false, true, (size + sizeof(sect0)), 0, sizeof(sect2));
			CopyMemory(func.sect0, addr, size, MemoryFlags_VirtualProtectSource);
			CopyMemory((func.sect0 + size), sect0, sizeof(sect0));
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



	//CreateThread(0, 4096, ::DI8::CreateMouseThread, 0, 0, 0);



	// SetCooperativeLevelKeyboard
	{
		auto addr = (appBaseAddr + 0x6E9BE0);
		constexpr uint32 size = 2;
		/*
		dmc4.exe+6E9BE0 - 6A 15 - push 15
		dmc4.exe+6E9BE2 - 52    - push edx
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			Write<byte8>((addr + 1), (DISCL_NONEXCLUSIVE | DISCL_FOREGROUND));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// SetCooperativeLevelMouse
	{
		auto addr = (appBaseAddr + 0x6EA8AF);
		constexpr uint32 size = 2;
		/*
		dmc4.exe+6EA8AF - 6A 0A - push 0A
		dmc4.exe+6EA8B1 - 52    - push edx
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			Write<byte8>((addr + 1), (DISCL_NONEXCLUSIVE | DISCL_FOREGROUND));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// SetCooperativeLevelGamepad
	{
		auto addr = (appBaseAddr + 0x6ED9E5);
		constexpr uint32 size = 2;
		/*
		dmc4.exe+6ED9E5 - 6A 09 - push 09
		dmc4.exe+6ED9E7 - 51    - push ecx
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			Write<byte8>((addr + 1), (DISCL_NONEXCLUSIVE | DISCL_FOREGROUND));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}



	// GetState
	{
		auto addr     = (appBaseAddr + 0x6EB4DF);
		auto jumpAddr = (appBaseAddr + 0x6EB4E4);
		constexpr new_size_t size = 5;
		/*
		dmc4.exe+6EB4DF - E8 B46D3D00 - call dmc4.exe+AC2298
		dmc4.exe+6EB4E4 - 85 C0       - test eax,eax
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x83, 0xEC, 0x0C,             // sub esp,0C
			0x51,                         // push ecx
			0x56,                         // push esi
			0x57,                         // push edi
			0xB9, 0x02, 0x00, 0x00, 0x00, // mov ecx,00000002
			0x8D, 0x74, 0x24, 0x18,       // lea esi,[esp+18]
			0x8D, 0x7C, 0x24, 0x0C,       // lea edi,[esp+0C]
			0xF3, 0xA5,                   // repe movsd
			0xB9, 0x02, 0x00, 0x00, 0x00, // mov ecx,00000002
			0x8D, 0x74, 0x24, 0x0C,       // lea esi,[esp+0C]
			0x8D, 0x7C, 0x24, 0x14,       // lea edi,[esp+14]
			0xF3, 0xA5,                   // repe movsd
			0x5F,                         // pop edi
			0x5E,                         // pop esi
			0x59,                         // pop ecx
			0xE8, 0x00, 0x00, 0x00, 0x00, // call dmc4.exe+AC2298
			0x89, 0x44, 0x24, 0x08,       // mov [esp+08],eax
		};

		constexpr byte8 sect2[] =
		{
			0x58, // pop eax
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(::Hook::XI::XInputGetState, jumpAddr, false, true, sizeof(sect0), 0, sizeof(sect2));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
			WriteCall((func.sect0 + 0x27), (appBaseAddr + 0xAC2298));
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

	{
		auto addr     = (appBaseAddr + 0x6EC996);
		auto jumpAddr = (appBaseAddr + 0x6EC99B);
		constexpr new_size_t size = 5;
		/*
		dmc4.exe+6EC996 - E8 FD583D00 - call dmc4.exe+AC2298
		dmc4.exe+6EC99B - 85 C0       - test eax,eax
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x83, 0xEC, 0x0C,             // sub esp,0C
			0x51,                         // push ecx
			0x56,                         // push esi
			0x57,                         // push edi
			0xB9, 0x02, 0x00, 0x00, 0x00, // mov ecx,00000002
			0x8D, 0x74, 0x24, 0x18,       // lea esi,[esp+18]
			0x8D, 0x7C, 0x24, 0x0C,       // lea edi,[esp+0C]
			0xF3, 0xA5,                   // repe movsd
			0xB9, 0x02, 0x00, 0x00, 0x00, // mov ecx,00000002
			0x8D, 0x74, 0x24, 0x0C,       // lea esi,[esp+0C]
			0x8D, 0x7C, 0x24, 0x14,       // lea edi,[esp+14]
			0xF3, 0xA5,                   // repe movsd
			0x5F,                         // pop edi
			0x5E,                         // pop esi
			0x59,                         // pop ecx
			0xE8, 0x00, 0x00, 0x00, 0x00, // call dmc4.exe+AC2298
			0x89, 0x44, 0x24, 0x08,       // mov [esp+08],eax
		};

		constexpr byte8 sect2[] =
		{
			0x58, // pop eax
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(::Hook::XI::XInputGetState, jumpAddr, false, true, sizeof(sect0), 0, sizeof(sect2));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
			WriteCall((func.sect0 + 0x27), (appBaseAddr + 0xAC2298));
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

	{
		auto addr     = (appBaseAddr + 0x6EDE33);
		auto jumpAddr = (appBaseAddr + 0x6EDE38);
		constexpr new_size_t size = 5;
		/*
		dmc4.exe+6EDE33 - E8 60443D00 - call dmc4.exe+AC2298
		dmc4.exe+6EDE38 - 85 C0       - test eax,eax
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x83, 0xEC, 0x0C,             // sub esp,0C
			0x51,                         // push ecx
			0x56,                         // push esi
			0x57,                         // push edi
			0xB9, 0x02, 0x00, 0x00, 0x00, // mov ecx,00000002
			0x8D, 0x74, 0x24, 0x18,       // lea esi,[esp+18]
			0x8D, 0x7C, 0x24, 0x0C,       // lea edi,[esp+0C]
			0xF3, 0xA5,                   // repe movsd
			0xB9, 0x02, 0x00, 0x00, 0x00, // mov ecx,00000002
			0x8D, 0x74, 0x24, 0x0C,       // lea esi,[esp+0C]
			0x8D, 0x7C, 0x24, 0x14,       // lea edi,[esp+14]
			0xF3, 0xA5,                   // repe movsd
			0x5F,                         // pop edi
			0x5E,                         // pop esi
			0x59,                         // pop ecx
			0xE8, 0x00, 0x00, 0x00, 0x00, // call dmc4.exe+AC2298
			0x89, 0x44, 0x24, 0x08,       // mov [esp+08],eax
		};

		constexpr byte8 sect2[] =
		{
			0x58, // pop eax
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(::Hook::XI::XInputGetState, jumpAddr, false, true, sizeof(sect0), 0, sizeof(sect2));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
			WriteCall((func.sect0 + 0x27), (appBaseAddr + 0xAC2298));
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

	{
		auto addr     = (appBaseAddr + 0x6EDF64);
		auto jumpAddr = (appBaseAddr + 0x6EDF69);
		constexpr new_size_t size = 5;
		/*
		dmc4.exe+6EDF64 - E8 2F433D00 - call dmc4.exe+AC2298
		dmc4.exe+6EDF69 - 85 C0       - test eax,eax
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x83, 0xEC, 0x0C,             // sub esp,0C
			0x51,                         // push ecx
			0x56,                         // push esi
			0x57,                         // push edi
			0xB9, 0x02, 0x00, 0x00, 0x00, // mov ecx,00000002
			0x8D, 0x74, 0x24, 0x18,       // lea esi,[esp+18]
			0x8D, 0x7C, 0x24, 0x0C,       // lea edi,[esp+0C]
			0xF3, 0xA5,                   // repe movsd
			0xB9, 0x02, 0x00, 0x00, 0x00, // mov ecx,00000002
			0x8D, 0x74, 0x24, 0x0C,       // lea esi,[esp+0C]
			0x8D, 0x7C, 0x24, 0x14,       // lea edi,[esp+14]
			0xF3, 0xA5,                   // repe movsd
			0x5F,                         // pop edi
			0x5E,                         // pop esi
			0x59,                         // pop ecx
			0xE8, 0x00, 0x00, 0x00, 0x00, // call dmc4.exe+AC2298
			0x89, 0x44, 0x24, 0x08,       // mov [esp+08],eax
		};

		constexpr byte8 sect2[] =
		{
			0x58, // pop eax
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(::Hook::XI::XInputGetState, jumpAddr, false, true, sizeof(sect0), 0, sizeof(sect2));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
			WriteCall((func.sect0 + 0x27), (appBaseAddr + 0xAC2298));
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

	{
		auto addr     = (appBaseAddr + 0x6EE0A2);
		auto jumpAddr = (appBaseAddr + 0x6EE0A7);
		constexpr new_size_t size = 5;
		/*
		dmc4.exe+6EE0A2 - E8 F1413D00 - call dmc4.exe+AC2298
		dmc4.exe+6EE0A7 - 85 C0       - test eax,eax
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x83, 0xEC, 0x0C,             // sub esp,0C
			0x51,                         // push ecx
			0x56,                         // push esi
			0x57,                         // push edi
			0xB9, 0x02, 0x00, 0x00, 0x00, // mov ecx,00000002
			0x8D, 0x74, 0x24, 0x18,       // lea esi,[esp+18]
			0x8D, 0x7C, 0x24, 0x0C,       // lea edi,[esp+0C]
			0xF3, 0xA5,                   // repe movsd
			0xB9, 0x02, 0x00, 0x00, 0x00, // mov ecx,00000002
			0x8D, 0x74, 0x24, 0x0C,       // lea esi,[esp+0C]
			0x8D, 0x7C, 0x24, 0x14,       // lea edi,[esp+14]
			0xF3, 0xA5,                   // repe movsd
			0x5F,                         // pop edi
			0x5E,                         // pop esi
			0x59,                         // pop ecx
			0xE8, 0x00, 0x00, 0x00, 0x00, // call dmc4.exe+AC2298
			0x89, 0x44, 0x24, 0x08,       // mov [esp+08],eax
		};

		constexpr byte8 sect2[] =
		{
			0x58, // pop eax
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(::Hook::XI::XInputGetState, jumpAddr, false, true, sizeof(sect0), 0, sizeof(sect2));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
			WriteCall((func.sect0 + 0x27), (appBaseAddr + 0xAC2298));
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
