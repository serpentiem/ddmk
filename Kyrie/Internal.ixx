module;
#include <xmmintrin.h>
export module Internal;

import Core;

#include "../Core/Macros.h"

import Vars;



// $DataStart

export typedef byte8 *(__stdcall * func_5F1540_t)(const char *, byte8 *); // Get Map Table
export typedef bool(__fastcall * func_6C32E0_t)(byte8 *, void *, uint8, byte8 *, uint32, uint32); // Spawn

export func_5F1540_t func_5F1540 = 0;
export func_6C32E0_t func_6C32E0 = 0;

export void Internal_Init()
{
	LogFunction();

	{
		constexpr byte8 sect1[] =
		{
			0x83, 0xEC, 0x08,             // sub esp,08
			0x51,                         // push ecx
			0x56,                         // push esi
			0x57,                         // push edi
			0xB9, 0x02, 0x00, 0x00, 0x00, // mov ecx,00000002
			0x8D, 0x75, 0x24,             // lea esi,[ebp+24]
			0x8D, 0x7C, 0x24, 0x0C,       // lea edi,[esp+0C]
			0xF3, 0xA5,                   // repe movsd
			0x5F,                         // pop edi
			0x5E,                         // pop esi
			0x59,                         // pop ecx
		};
		constexpr byte8 sect2[] =
		{
			0xC2, 0x08, 0x00, // ret 0008
		};

		auto func = CreateFunction((appBaseAddr + 0x5F1540), 0, (FunctionFlags_SaveRegisters | FunctionFlags_NoReturn), 0, sizeof(sect1), sizeof(sect2));
		CopyMemory(func.sect1, sect1, sizeof(sect1));
		CopyMemory(func.sect2, sect2, sizeof(sect2));
		func_5F1540 = reinterpret_cast<func_5F1540_t>(func.addr);
	}
	{
		constexpr byte8 sect1[] =
		{
			0x83, 0xEC, 0x10,             // sub esp,10
			0x51,                         // push ecx
			0x56,                         // push esi
			0x57,                         // push edi
			0xB9, 0x04, 0x00, 0x00, 0x00, // mov ecx,00000004
			0x8D, 0x75, 0x24,             // lea esi,[ebp+24]
			0x8D, 0x7C, 0x24, 0x0C,       // lea edi,[esp+0C]
			0xF3, 0xA5,                   // repe movsd
			0x5F,                         // pop edi
			0x5E,                         // pop esi
			0x59,                         // pop ecx
		};
		constexpr byte8 sect2[] =
		{
			0xC2, 0x10, 0x00, // ret 0010
		};

		auto func = CreateFunction((appBaseAddr + 0x6C32E0), 0, (FunctionFlags_SaveRegisters | FunctionFlags_NoReturn), 0, sizeof(sect1), sizeof(sect2));
		CopyMemory(func.sect1, sect1, sizeof(sect1));
		CopyMemory(func.sect2, sect2, sizeof(sect2));
		func_6C32E0 = reinterpret_cast<func_6C32E0_t>(func.addr);
	}
}

// $DataEnd
