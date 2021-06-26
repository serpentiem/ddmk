export module ActorBase;

import Core;

#include "../Core/Macros.h"

import Vars;

#define debug false



export typedef byte8 *(__fastcall * GetPlayerActorBaseAddressByEffectData_t)(byte8 * effectDataAddr);

export GetPlayerActorBaseAddressByEffectData_t GetPlayerActorBaseAddressByEffectData = 0;



namespaceStart(Actor);

export void ToggleBase(bool enable)
{
	static bool run = false;

	// GetPlayerActorBaseAddressByEffectData
	{
		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0x8B, 0x81, 0xC0, 0x00, 0x00, 0x00, // mov rax,[rcx+000000C0]
			0x48, 0x85, 0xC0,                         // test rax,rax
			0x75, 0x0B,                               // jne short
			0x48, 0x8B, 0x05, 0x00, 0x00, 0x00, 0x00, // mov rax,[dmc3.exe+C90E28]
			0x48, 0x8B, 0x40, 0x18,                   // mov rax,[rax+18]
			0xC3,                                     // ret
		};

		if (!run)
		{
			func = CreateFunction(0, 0, false, false, sizeof(sect0), 0, 0, 0, 0, true);
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteAddress((func.sect0 + 0xC), (appBaseAddr + 0xC90E28), 7);
			GetPlayerActorBaseAddressByEffectData = reinterpret_cast<GetPlayerActorBaseAddressByEffectData_t>(func.addr);
		}
	}

	run = true;
}

namespaceEnd();
