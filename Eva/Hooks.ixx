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
import GUI;      // keyBindings
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



namespaceStart(Hook::DI8);

void GetDeviceStateA_Function(byte8 * state)
{
	for_all(index, countof(keyBindings))
	{
		auto & keyBinding = keyBindings[index];

		keyBinding.UpdateKeyData(state);
		keyBinding.Check(state);
	}
}

namespaceEnd();



namespaceStart(Hooks);

export void Init()
{
	LogFunction();



	Install
	(
		(appBaseAddr + 0x407318),
		::Base::Windows::RegisterClassExW,
		::Hook::Windows::RegisterClassExW
	);

	Install
	(
		(appBaseAddr + 0x4072A8),
		::Base::Windows::CreateWindowExW,
		::Hook::Windows::CreateWindowExW
	);

	::Hook::D3D11::D3D11CreateDeviceAndSwapChain_func = ::Hook::D3D11::D3D11CreateDeviceAndSwapChain_Function;

	Install
	(
		(appBaseAddr + 0x407628),
		::Base::D3D11::D3D11CreateDeviceAndSwapChain,
		::Hook::D3D11::D3D11CreateDeviceAndSwapChain
	);

	::Hook::DI8::GetDeviceStateA_func = ::Hook::DI8::GetDeviceStateA_Function;



	constexpr bool enable = true;
	static bool run = false;



	{
		auto addr     = (appBaseAddr + 0x156CB);
		auto jumpAddr = (appBaseAddr + 0x156D3);
		constexpr uint32 size = 5;
		/*
		dmc1.exe+156CB - BA 00010000 - mov edx,00000100
		dmc1.exe+156D0 - FF 50 48    - call qword ptr [rax+48]
		dmc1.exe+156D3 - 85 C0       - test eax,eax
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
			func = old_CreateFunction(::Hook::DI8::GetDeviceStateA<DEVICE_TYPE::KEYBOARD>, jumpAddr, false, true, (size + sizeof(sect0)), 0, sizeof(sect2));
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

	{
		auto addr     = (appBaseAddr + 0x189DD);
		auto jumpAddr = (appBaseAddr + 0x189E5);
		constexpr uint32 size = 5;
		/*
		dmc1.exe+189DD - BA 00010000 - mov edx,00000100
		dmc1.exe+189E2 - FF 50 48    - call qword ptr [rax+48]
		dmc1.exe+189E5 - 85 C0       - test eax,eax
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
			func = old_CreateFunction(::Hook::DI8::GetDeviceStateA<DEVICE_TYPE::KEYBOARD>, jumpAddr, false, true, (size + sizeof(sect0)), 0, sizeof(sect2));
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



	CreateThread(0, 4096, ::DI8::CreateMouseThread, 0, 0, 0);



	// SetCooperativeLevelKeyboard
	{
		auto addr = (appBaseAddr + 0x18752);
		constexpr uint32 size = 6;
		/*
		dmc1.exe+18752 - 41 B8 05000000    - mov r8d,00000005
		dmc1.exe+18758 - 48 8B 15 A12BBF00 - mov rdx,[dmc1.exe+C0B300]
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
		auto addr     = (appBaseAddr + 0x154C9);
		auto jumpAddr = (appBaseAddr + 0x154CF);
		constexpr uint32 size = 6;
		/*
		dmc1.exe+154C9 - FF 15 291F3F00 - call qword ptr [dmc1.exe+4073F8]
		dmc1.exe+154CF - 85 C0          - test eax,eax
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x50,                               // push rax
			0x51,                               // push rcx
			0x52,                               // push rdx
			0x55,                               // push rbp
			0x48, 0x8B, 0xEC,                   // mov rbp,rsp
			0x40, 0x80, 0xE4, 0xF0,             // and spl,F0
			0x48, 0x83, 0xEC, 0x20,             // sub rsp,20
			0xFF, 0x15, 0x00, 0x00, 0x00, 0x00, // call qword ptr [dmc1.exe+4073F8]
			0x48, 0x89, 0x45, 0x18,             // mov [rbp+18],rax
			0x48, 0x8B, 0x4D, 0x10,             // mov rcx,[rbp+10]
			0x48, 0x8B, 0x55, 0x08,             // mov rdx,[rbp+08]
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
			WriteAddress((func.sect0 + 0xF), (appBaseAddr + 0x4073F8), 6);
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
