module;
#include "../ThirdParty/ImGui/imgui.h"
export module Hooks;

import Core;
import Core_ImGui;

#include "../Core/Macros.h"

import Windows;
import DXGI;
import D3D11;
import DI8;
import XI;

using namespace Windows;
using namespace DXGI;
using namespace D3D11;
using namespace DI8;
using namespace XI;

import HooksBase;

import Config;
import Global;
import Graphics; // Toggle, UpdateFrameRate
import GUI;      // keyBindings, ToggleShowMain
import Vars;

#define debug false



namespaceStart(Hook::D3D11);

void D3D11CreateDeviceAndSwapChain_Function()
{
	Graphics::Toggle(false);
	Graphics::Toggle(true);

	UpdateFrameRate();
}

namespaceEnd();






//namespaceStart(DI8);

// void UpdateKeyboard_Function(DI8::DIKEYBOARDSTATE * stateAddr)
// {

// 	if (!stateAddr)
// 	{
// 		return;
// 	}

// 	auto & state = *stateAddr;



// 	for_all(index, countof(keyBindings))
// 	{
// 		auto & keyBinding = keyBindings[index];

// 		keyBinding.UpdateKeyData(state.keys);
// 		keyBinding.Check(state.keys);
// 	}
// }




// void UpdateGamepad_Function(DI8::DIJOYSTATE * stateAddr)
// {
// 	if (!stateAddr)
// 	{
// 		return;
// 	}
// 	auto & state = *stateAddr;


// 	auto button = activeConfig.gamepadButton;
// 	if (button > countof(state.rgbButtons))
// 	{
// 		button = 0;
// 	}

// 	static bool execute = false;

// 	if (state.rgbButtons[button])
// 	{
// 		if (execute)
// 		{
// 			execute = false;

// 			ToggleShowMain();
// 		}
// 	}
// 	else
// 	{
// 		execute = true;
// 	}
// }


















//namespaceEnd();






namespaceStart(Hooks);

export void Init()
{
	LogFunction();



	Install
	(
		(appBaseAddr + 0x34F308),
		::Base::Windows::RegisterClassExW,
		::Hook::Windows::RegisterClassExW
	);

	Install
	(
		(appBaseAddr + 0x34F300),
		::Base::Windows::CreateWindowExW,
		::Hook::Windows::CreateWindowExW
	);

	::Hook::D3D11::D3D11CreateDeviceAndSwapChain_func = ::Hook::D3D11::D3D11CreateDeviceAndSwapChain_Function;

	Install
	(
		(appBaseAddr + 0x34F650),
		::Base::D3D11::D3D11CreateDeviceAndSwapChain,
		::Hook::D3D11::D3D11CreateDeviceAndSwapChain
	);



	// UpdateKeyboard_func = UpdateKeyboard_Function;
	// UpdateGamepad_func = UpdateGamepad_Function;



	constexpr bool enable = true;
	static bool run = false;



	{
		auto addr     = (appBaseAddr + 0x41DA0);
		auto jumpAddr = (appBaseAddr + 0x41DA6);
		constexpr uint32 size = 6;
		constexpr uint32 size2 = 3;
		/*
		dmc3.exe+41DA0 - 48 8B 01 - mov rax,[rcx]
		dmc3.exe+41DA3 - FF 50 48 - call qword ptr [rax+48]
		dmc3.exe+41DA6 - 85 C0    - test eax,eax
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x50,                   // push rax
			0x51,                   // push rcx
			0x52,                   // push rdx
			0x41, 0x50,             // push r8
			0x55,                   // push rbp
			0x48, 0x8B, 0xEC,       // mov rbp,rsp
			0x40, 0x80, 0xE4, 0xF0, // and spl,F0
			0x48, 0x83, 0xEC, 0x20, // sub rsp,20
			0xFF, 0x50, 0x48,       // call qword ptr [rax+48]
			0x48, 0x89, 0x45, 0x20, // mov [rbp+20],rax
			0x48, 0x8B, 0x4D, 0x18, // mov rcx,[rbp+18]
			0x48, 0x8B, 0x55, 0x10, // mov rdx,[rbp+10]
			0x4C, 0x8B, 0x45, 0x08, // mov r8,[rbp+08]
		};
		constexpr byte8 sect2[] =
		{
			0x48, 0x8B, 0xE5, // mov rsp,rbp
			0x5D,             // pop rbp
			0x41, 0x58,       // pop r8
			0x5A,             // pop rdx
			0x59,             // pop rcx
			0x58,             // pop rax
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(::Hook::DI8::GetDeviceStateA, jumpAddr, false, true, (size2 + sizeof(sect0)), 0, sizeof(sect2));
			CopyMemory(func.sect0, addr, size2, MemoryFlags_VirtualProtectSource);
			CopyMemory((func.sect0 + size2), sect0, sizeof(sect0));
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

	{
		auto addr     = (appBaseAddr + 0x482AD);
		auto jumpAddr = (appBaseAddr + 0x482B5);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+482AD - BA 00010000 - mov edx,00000100
		dmc3.exe+482B2 - FF 50 48    - call qword ptr [rax+48]
		dmc3.exe+482B5 - 85 C0       - test eax,eax
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x50,                   // push rax
			0x51,                   // push rcx
			0x52,                   // push rdx
			0x41, 0x50,             // push r8
			0x55,                   // push rbp
			0x48, 0x8B, 0xEC,       // mov rbp,rsp
			0x40, 0x80, 0xE4, 0xF0, // and spl,F0
			0x48, 0x83, 0xEC, 0x20, // sub rsp,20
			0xFF, 0x50, 0x48,       // call qword ptr [rax+48]
			0x48, 0x89, 0x45, 0x20, // mov [rbp+20],rax
			0x48, 0x8B, 0x4D, 0x18, // mov rcx,[rbp+18]
			0x48, 0x8B, 0x55, 0x10, // mov rdx,[rbp+10]
			0x4C, 0x8B, 0x45, 0x08, // mov r8,[rbp+08]
		};
		constexpr byte8 sect2[] =
		{
			0x48, 0x8B, 0xE5, // mov rsp,rbp
			0x5D,             // pop rbp
			0x41, 0x58,       // pop r8
			0x5A,             // pop rdx
			0x59,             // pop rcx
			0x58,             // pop rax
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







	// SetCooperativeLevelKeyboard
	{
		auto addr = (appBaseAddr + 0x47F56);
		constexpr uint32 size = 6;
		/*
		dmc3.exe+47F56 - 41 B8 05000000    - mov r8d,00000005
		dmc3.exe+47F5C - 48 8B 15 6D0BBD00 - mov rdx,[dmc3.exe+C18AD0]
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			Write<byte32>((addr + 2), DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}



	{
		auto addr     = (appBaseAddr + 0x41A83);
		auto jumpAddr = (appBaseAddr + 0x41A88);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+41A83 - E8 6E393000 - call dmc3.exe+3453F6
		dmc3.exe+41A88 - 85 C0       - test eax,eax
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x50,                         // push rax
			0x51,                         // push rcx
			0x52,                         // push rdx
			0x55,                         // push rbp
			0x48, 0x8B, 0xEC,             // mov rbp,rsp
			0x40, 0x80, 0xE4, 0xF0,       // and spl,F0
			0x48, 0x83, 0xEC, 0x20,       // sub rsp,20
			0xE8, 0x00, 0x00, 0x00, 0x00, // call dmc3.exe+3453F6
			0x48, 0x89, 0x45, 0x18,       // mov [rbp+18],rax
			0x48, 0x8B, 0x4D, 0x10,       // mov rcx,[rbp+10]
			0x48, 0x8B, 0x55, 0x08,       // mov rdx,[rbp+08]
		};
		constexpr byte8 sect2[] =
		{
			0x48, 0x8B, 0xE5, // mov rsp,rbp
			0x5D,             // pop rbp
			0x5A,             // pop rdx
			0x59,             // pop rcx
			0x58,             // pop rax
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(::Hook::XI::XInputGetState, jumpAddr, false, true, sizeof(sect0), 0, sizeof(sect2));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
			WriteCall((func.sect0 + 0xF), (appBaseAddr + 0x3453F6));
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
		auto addr     = (appBaseAddr + 0x41AFA);
		auto jumpAddr = (appBaseAddr + 0x41AFF);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+41AFA - E8 F7383000 - call dmc3.exe+3453F6
		dmc3.exe+41AFF - 85 C0       - test eax,eax
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x50,                         // push rax
			0x51,                         // push rcx
			0x52,                         // push rdx
			0x55,                         // push rbp
			0x48, 0x8B, 0xEC,             // mov rbp,rsp
			0x40, 0x80, 0xE4, 0xF0,       // and spl,F0
			0x48, 0x83, 0xEC, 0x20,       // sub rsp,20
			0xE8, 0x00, 0x00, 0x00, 0x00, // call dmc3.exe+3453F6
			0x48, 0x89, 0x45, 0x18,       // mov [rbp+18],rax
			0x48, 0x8B, 0x4D, 0x10,       // mov rcx,[rbp+10]
			0x48, 0x8B, 0x55, 0x08,       // mov rdx,[rbp+08]
		};
		constexpr byte8 sect2[] =
		{
			0x48, 0x8B, 0xE5, // mov rsp,rbp
			0x5D,             // pop rbp
			0x5A,             // pop rdx
			0x59,             // pop rcx
			0x58,             // pop rax
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(::Hook::XI::XInputGetState, jumpAddr, false, true, sizeof(sect0), 0, sizeof(sect2));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
			WriteCall((func.sect0 + 0xF), (appBaseAddr + 0x3453F6));
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
		auto addr     = (appBaseAddr + 0x41C40);
		auto jumpAddr = (appBaseAddr + 0x41C45);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+41C40 - E8 B1373000 - call dmc3.exe+3453F6
		dmc3.exe+41C45 - 85 C0       - test eax,eax
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x50,                         // push rax
			0x51,                         // push rcx
			0x52,                         // push rdx
			0x55,                         // push rbp
			0x48, 0x8B, 0xEC,             // mov rbp,rsp
			0x40, 0x80, 0xE4, 0xF0,       // and spl,F0
			0x48, 0x83, 0xEC, 0x20,       // sub rsp,20
			0xE8, 0x00, 0x00, 0x00, 0x00, // call dmc3.exe+3453F6
			0x48, 0x89, 0x45, 0x18,       // mov [rbp+18],rax
			0x48, 0x8B, 0x4D, 0x10,       // mov rcx,[rbp+10]
			0x48, 0x8B, 0x55, 0x08,       // mov rdx,[rbp+08]
		};
		constexpr byte8 sect2[] =
		{
			0x48, 0x8B, 0xE5, // mov rsp,rbp
			0x5D,             // pop rbp
			0x5A,             // pop rdx
			0x59,             // pop rcx
			0x58,             // pop rax
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(::Hook::XI::XInputGetState, jumpAddr, false, true, sizeof(sect0), 0, sizeof(sect2));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
			WriteCall((func.sect0 + 0xF), (appBaseAddr + 0x3453F6));
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
