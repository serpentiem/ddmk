#ifndef __MODULE_COLOR__
#define __MODULE_COLOR__

module;
#include "../Core/Core.h"

#include "Vars.h"
export module ModuleName(Color);

import ModuleName(Config);

#ifdef __INTELLISENSE__
#include "Config.ixx"
#endif

void SetColor
(
	ActorData & actorData,
	byte8 * dest
)
{
	uint8 character = static_cast<uint8>(actorData.character);

	switch (character)
	{
		case CHAR_DANTE:
		{
			break;
		}
		case CHAR_VERGIL:
		{
			auto & actorData2 = *reinterpret_cast<ActorDataVergil *>(&actorData);

			if (actorData2.neroAngelo)
			{
				memcpy(dest, activeConfig.Color.Aura.neroAngelo, 4);
			}
			else
			{
				uint8 activeMeleeWeaponIndex = static_cast<uint8>(actorData2.activeMeleeWeaponIndex);
				if (activeMeleeWeaponIndex >= MAX_MELEE_WEAPON_VERGIL)
				{
					activeMeleeWeaponIndex = 0;
				}

				memcpy(dest, activeConfig.Color.Aura.vergil[activeMeleeWeaponIndex], 4);
			}
			break;
		}
	}
}


void UpdateColor(byte8 * baseAddr)
{
	auto addr = *reinterpret_cast<byte8 **>(baseAddr + 0x28);
	if (!addr)
	{
		return;
	}
	auto actorBaseAddr = *reinterpret_cast<byte8 **>(addr + 0xC0);
	if (!actorBaseAddr)
	{
		return;
	}
	auto & actorData = *reinterpret_cast<ActorData *>(actorBaseAddr);

	auto dest = (baseAddr + 0xE0);

	SetColor(actorData, dest);







}




export void Color_Init()
{
	return;


	{
		constexpr byte8 sect0[] =
		{
			0x48, 0x8D, 0x54, 0x24, 0x30, // lea rdx,[rsp+30]
		};
		auto func = CreateFunction(SetColor, (appBaseAddr + 0x90C63), true, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		//WriteJump((appBaseAddr + 0x90C41), func.addr, 1);
		/*
		dmc3.exe+90C41 - 38 99 9F3E0000 - cmp [rcx+00003E9F],bl
		dmc3.exe+90C63 - 48 8B 06       - mov rax,[rsi]
		*/
	}




//vp_memset((appBaseAddr + 0x8E412), 0x90, 5);

/*
dmc3.exe+8E412 - E8 E9E8FFFF - call dmc3.exe+8CD00
*/


	// {
	// 	constexpr byte8 sect0[] =
	// 	{
	// 		0x48, 0x8D, 0x55, 0xA7, // lea rdx,[rbp-59]
	// 	};
	// 	constexpr byte8 sect2[] =
	// 	{
	// 		0xBA, 0x01, 0x00, 0x00, 0x00, // mov edx,00000001
	// 	};
	// 	auto func = CreateFunction(SetColor, (appBaseAddr + 0x8E457), true, true, sizeof(sect0), 0, sizeof(sect2));
	// 	memcpy(func.sect0, sect0, sizeof(sect0));
	// 	memcpy(func.sect2, sect2, sizeof(sect2));
	// 	//WriteJump((appBaseAddr + 0x8E452), func.addr);
	// 	/*
	// 	dmc3.exe+8E452 - BA 01000000 - mov edx,00000001
	// 	dmc3.exe+8E457 - E8 34C61600 - call dmc3.exe+1FAA90
	// 	*/
	// }



	// {
	// 	constexpr byte8 sect1[] =
	// 	{
	// 		mov_rcx_rbx,
	// 	};
	// 	constexpr byte8 sect2[] =
	// 	{
	// 		0x44, 0x0F, 0xB6, 0x83, 0xE0, 0x00, 0x00, 0x00, // movzx r8d,byte ptr [rbx+000000E0]
	// 	};
	// 	auto func = CreateFunction(UpdateColor, (appBaseAddr + 0x2E5F53), true, true, 0, sizeof(sect1), sizeof(sect2));
	// 	memcpy(func.sect1, sect1, sizeof(sect1));
	// 	memcpy(func.sect2, sect2, sizeof(sect2));
	// 	WriteJump((appBaseAddr + 0x2E5F4B), func.addr, 3);
	// 	/*
	// 	dmc3.exe+2E5F4B - 44 0FB6 83 E0000000 - movzx r8d,byte ptr [rbx+000000E0]
	// 	dmc3.exe+2E5F53 - 44 0FB6 8B E1000000 - movzx r9d,byte ptr [rbx+000000E1]
	// 	*/
	// }




}




//export void Color_UpdateactiveConfig(activeConfig & config)
//{
//	LogFunction();
//
//	constexpr uint8 count = (sizeof(CONFIG::Color) / 4);
//
//	auto vars = reinterpret_cast<float32 *>(config.Color.airHike);
//
//	for_all(uint8, index, count)
//	{
//		vars[index] /= 255;
//	}
//}

#endif
