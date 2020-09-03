#ifndef __MODULE_MOBILITY__
#define __MODULE_MOBILITY__

module;
#include "../Core/Core.h"

#include "Vars.h"
export module ModuleName(Mobility);

import ModuleName(Config);

#ifdef __INTELLISENSE__
#include "Config.ixx"
#endif

namespace Mobility
{
	byte8 * dashProxy           = 0;
	byte8 * skyStarProxy        = 0;
	byte8 * airTrickDanteProxy  = 0;
	byte8 * airTrickVergilProxy = 0;
	byte8 * trickUpProxy        = 0;
	byte8 * trickDownProxy      = 0;
	byte8 * airTrickDanteFix    = 0;
	byte8 * airTrickVergilFix   = 0;

	template
	<
		uint32 index,
		typename T
	>
	uint32 MobilityFunction(T & actorData, uint8 & var, uint8(&array)[2])
	{
		uint8 track = (actorData.devil) ? 1 : 0;

		// Required since there is no reset when hitting the floor.
		if constexpr (index != ACTOR_EVENT_DANTE_DASH)
		{
			if (actorData.state & STATE_ON_FLOOR)
			{
				var = 0;
			}
		}

		if (var >= array[track])
		{
			return 0;
		}

		var++;

		return index;
	}

	auto Dash(ActorDataDante & actorData)
	{
		return MobilityFunction<ACTOR_EVENT_DANTE_DASH>(actorData, actorData.dashCount, activeConfig.Trickster.dashCount);
	}

	auto SkyStar(ActorDataDante & actorData)
	{
		return MobilityFunction<ACTOR_EVENT_DANTE_SKY_STAR>(actorData, actorData.skyStarCount, activeConfig.Trickster.skyStarCount);
	}

	auto AirTrickDante(ActorDataDante & actorData)
	{
		actorData.var_3E10[26] = (actorData.state & STATE_ON_FLOOR) ? 1 : 0;

		return MobilityFunction<ACTOR_EVENT_DANTE_AIR_TRICK>(actorData, actorData.airTrickCount, activeConfig.Trickster.airTrickCount);
	}

	auto AirTrickVergil(ActorDataVergil & actorData)
	{
		return MobilityFunction<ACTOR_EVENT_VERGIL_AIR_TRICK>(actorData, actorData.airTrickCount, activeConfig.DarkSlayer.airTrickCount);
	}

	auto TrickUp(ActorDataVergil & actorData)
	{
		return MobilityFunction<ACTOR_EVENT_VERGIL_TRICK_UP>(actorData, actorData.trickUpCount, activeConfig.DarkSlayer.trickUpCount);
	}

	auto TrickDown(ActorDataVergil & actorData)
	{
		return MobilityFunction<ACTOR_EVENT_VERGIL_TRICK_DOWN>(actorData, actorData.trickDownCount, activeConfig.DarkSlayer.trickDownCount);
	}

	template <typename T>
	void SkyStarResetFunction(T & actorData)
	{
		if constexpr (TypeMatch<T, ActorDataDante>::value)
		{
			actorData.skyStarCount = 0;
			actorData.newAirStingerCount = 0;
		}

		if (actorData.state & STATE_ON_FLOOR)
		{
			auto & event = actorData.eventData[1].index;

			if constexpr (TypeMatch<T, ActorDataDante>::value)
			{
				if (event == ACTOR_EVENT_DANTE_AIR_TRICK)
				{
					actorData.airTrickCount = 1;
				}
			}
			else if constexpr (TypeMatch<T, ActorDataVergil>::value)
			{
				if (event == ACTOR_EVENT_VERGIL_AIR_TRICK)
				{
					actorData.airTrickCount = 1;
				}
				else if (event == ACTOR_EVENT_VERGIL_TRICK_UP)
				{
					actorData.trickUpCount = 1;
				}
				else if (event == ACTOR_EVENT_VERGIL_TRICK_DOWN)
				{
					actorData.trickDownCount = 1;
				}
			}
		}
	}

	export void SkyStarReset(byte8 * baseAddr)
	{
		auto & actorData = *reinterpret_cast<ActorData *>(baseAddr);

		if (actorData.character == CHAR_DANTE)
		{
			auto & actorData = *reinterpret_cast<ActorDataDante *>(baseAddr);

			SkyStarResetFunction(actorData);
		}
		else if (actorData.character == CHAR_VERGIL)
		{
			auto & actorData = *reinterpret_cast<ActorDataVergil *>(baseAddr);

			SkyStarResetFunction(actorData);
		}
	}

	export void Init()
	{
		LogFunction();

		auto CreateMobilityFunction = [](void * dest)
		{
			constexpr byte8 sect1[] =
			{
				0x48, 0x8B, 0xCB, //mov rcx,rbx
			};
			constexpr byte8 sect2[] =
			{
				0x85, 0xC0,                         //test eax,eax
				0x0F, 0x84, 0x00, 0x00, 0x00, 0x00, //je dmc3.exe+1E64A9
				0x8B, 0xD0,                         //mov edx,eax
			};
			auto func = CreateFunction(dest, (appBaseAddr + 0x1E666D), true, false, 0, sizeof(sect1), sizeof(sect2));
			memcpy(func.sect1, sect1, sizeof(sect1));
			memcpy(func.sect2, sect2, sizeof(sect2));
			WriteAddress((func.sect2 + 2), (appBaseAddr + 0x1E64A9), 6);
			return func.addr;
		};

		dashProxy           = CreateMobilityFunction(Dash          );
		skyStarProxy        = CreateMobilityFunction(SkyStar       );
		airTrickDanteProxy  = CreateMobilityFunction(AirTrickDante );
		airTrickVergilProxy = CreateMobilityFunction(AirTrickVergil);
		trickUpProxy        = CreateMobilityFunction(TrickUp       );
		trickDownProxy      = CreateMobilityFunction(TrickDown     );

		// Trick Up and Trick Down are reset when hitting the floor, Air Trick is not. Let's fix it.
		{
			constexpr byte8 sect0[] =
			{
				0xC6, 0x83, 0x5E, 0x63, 0x00, 0x00, 0x00, //mov byte ptr [rbx+0000635E],00
				0xC6, 0x83, 0x10, 0x3E, 0x00, 0x00, 0x03, //mov byte ptr [rbx+00003E10],03
			};
			auto func = CreateFunction(0, (appBaseAddr + 0x1F07DD), false, true, sizeof(sect0));
			memcpy(func.sect0, sect0, sizeof(sect0));
			airTrickVergilFix = func.addr;
			/*
			dmc3.exe+1F07D6 - C6 83 103E0000 03 - mov byte ptr [rbx+00003E10],03
			dmc3.exe+1F07DD - E9 3C060000       - jmp dmc3.exe+1F0E1E
			*/
		}
	}

	export void Toggle(bool enable)
	{
		// Dash
		{
			auto dest = (appBaseAddr + 0x1E66CB);
			if (enable)
			{
				WriteJump(dest, dashProxy, 1);
			}
			else
			{
				constexpr byte8 buffer[] =
				{
					0x8B, 0x8B, 0x58, 0x63, 0x00, 0x00, //mov ecx,[rbx+00006358]
				};
				vp_memcpy(dest, buffer, sizeof(buffer));
			}
			/*
			dmc3.exe+1E66CB - 8B 8B 58630000 - mov ecx,[rbx+00006358]
			*/
		}

		// Sky Star
		{
			auto dest = (appBaseAddr + 0x1E6689);

			if (enable)
			{
				WriteJump(dest, skyStarProxy, 2);
			}
			else
			{
				constexpr byte8 buffer[] =
				{
					0x83, 0xBB, 0x58, 0x63, 0x00, 0x00, 0x01, //cmp dword ptr [rbx+00006358],01
				};

				vp_memcpy(dest, buffer, sizeof(buffer));
			}
			/*
			dmc3.exe+1E6689 - 83 BB 58630000 01 - cmp dword ptr [rbx+00006358],01
			*/
		}

		// Air Trick Dante
		{
			auto dest = (appBaseAddr + 0x1E6612);

			if (enable)
			{
				WriteJump(dest, airTrickDanteProxy, 2);
			}
			else
			{
				constexpr byte8 buffer[] =
				{
					0x83, 0xBB, 0x58, 0x63, 0x00, 0x00, 0x02, //cmp dword ptr [rbx+00006358],02
				};

				vp_memcpy(dest, buffer, sizeof(buffer));
			}
			/*
			dmc3.exe+1E6612 - 83 BB 58630000 02 - cmp dword ptr [rbx+00006358],02
			*/
		}

		// Air Trick Vergil
		{
			auto dest = (appBaseAddr + 0x1E6842);

			if (enable)
			{
				WriteJump(dest, airTrickVergilProxy, 1);
			}
			else
			{
				constexpr byte8 buffer[] =
				{
					0x8B, 0x83, 0x64, 0x3E, 0x00, 0x00, //mov eax,[rbx+00003E64]
				};

				vp_memcpy(dest, buffer, sizeof(buffer));
			}
			/*
			dmc3.exe+1E6842 - 8B 83 643E0000 - mov eax,[rbx+00003E64]
			*/
		}

		// Trick Up
		{
			auto dest = (appBaseAddr + 0x1E67D5);

			if (enable)
			{
				WriteJump(dest, trickUpProxy, 2);
			}
			else
			{
				constexpr byte8 buffer[] =
				{
					0x83, 0xBB, 0x58, 0x63, 0x00, 0x00, 0x01, //cmp dword ptr [rbx+00006358],01
				};

				vp_memcpy(dest, buffer, sizeof(buffer));
			}
			/*
			dmc3.exe+1E67D5 - 83 BB 58630000 01 - cmp dword ptr [rbx+00006358],01
			*/
		}

		// Trick Down
		{
			auto dest = (appBaseAddr + 0x1E6768);

			if (enable)
			{
				WriteJump(dest, trickDownProxy, 2);
			}
			else
			{
				constexpr byte8 buffer[] =
				{
					0x83, 0xBB, 0x58, 0x63, 0x00, 0x00, 0x02, //cmp dword ptr [rbx+00006358],02
				};

				vp_memcpy(dest, buffer, sizeof(buffer));
			}
			/*
			dmc3.exe+1E6768 - 83 BB 58630000 02 - cmp dword ptr [rbx+00006358],02
			*/
		}

		// Adjust Reset Values
		// Air Trick, Trick Up
		Write<uint16>((appBaseAddr + 0x1DFEA5 + 7), (enable) ? 0 : 257);
		Write<uint16>((appBaseAddr + 0x1DFFA6 + 7), (enable) ? 0 : 257);
		Write<uint16>((appBaseAddr + 0x1E0790 + 8), (enable) ? 0 : 257);
		Write<uint16>((appBaseAddr + 0x1E0D64 + 7), (enable) ? 0 : 257);
		Write<uint16>((appBaseAddr + 0x1E0F52 + 8), (enable) ? 0 : 257);
		Write<uint16>((appBaseAddr + 0x1E0FAB + 8), (enable) ? 0 : 257);
		Write<uint16>((appBaseAddr + 0x1E16B5 + 7), (enable) ? 0 : 257);
		// Trick Up, Trick Down
		Write<uint16>((appBaseAddr + 0x1F07CD + 7), (enable) ? 0 : 257);
		// Trick Up
		Write<uint8>((appBaseAddr + 0x1DFE9E + 6), (enable) ? 0 : 1);
		Write<uint8>((appBaseAddr + 0x1DFFAF + 6), (enable) ? 0 : 1);
		Write<uint8>((appBaseAddr + 0x1E079A + 7), (enable) ? 0 : 1);
		Write<uint8>((appBaseAddr + 0x1E0D6D + 6), (enable) ? 0 : 1);
		Write<uint8>((appBaseAddr + 0x1E0F5C + 7), (enable) ? 0 : 1);
		Write<uint8>((appBaseAddr + 0x1E0FB5 + 7), (enable) ? 0 : 1);
		Write<uint8>((appBaseAddr + 0x1E16BE + 6), (enable) ? 0 : 1);

		// Air Trick Dante Floor
		{
			auto dest = (appBaseAddr + 0x1F2228);
			if (enable)
			{
				vp_memset(dest, 0x90, 7);
			}
			else
			{
				constexpr byte8 buffer[] =
				{
					0xC6, 0x87, 0x5E, 0x63, 0x00, 0x00, 0x00, //mov byte ptr [rdi+0000635E],00
				};
				vp_memcpy(dest, buffer, sizeof(buffer));
			}
			/*
			dmc3.exe+1F2228 - C6 87 5E630000 00 - mov byte ptr [rdi+0000635E],00
			*/
		}

		// Air Trick Vergil Floor
		{
			auto dest = (appBaseAddr + 0x1F0C92);
			if (enable)
			{
				vp_memset(dest, 0x90, 7);
			}
			else
			{
				constexpr byte8 buffer[] =
				{
					0x40, 0x88, 0xBB, 0x5E, 0x63, 0x00, 0x00, //mov [rbx+0000635E],dil
				};
				vp_memcpy(dest, buffer, sizeof(buffer));
			}
			/*
			dmc3.exe+1F0C92 - 40 88 BB 5E630000 - mov [rbx+0000635E],dil
			*/
		}

		// Trick Up Floor
		{
			auto dest = (appBaseAddr + 0x1F0B2A);
			if (enable)
			{
				vp_memset(dest, 0x90, 7);
			}
			else
			{
				constexpr byte8 buffer[] =
				{
					0x40, 0x88, 0xBB, 0x5F, 0x63, 0x00, 0x00, //mov [rbx+0000635F],dil
				};
				vp_memcpy(dest, buffer, sizeof(buffer));
			}
			/*
			dmc3.exe+1F0B2A - 40 88 BB 5F630000 - mov [rbx+0000635F],dil
			*/
		}

		// Trick Down Floor
		{
			auto dest = (appBaseAddr + 0x1F0A33);
			if (enable)
			{
				vp_memset(dest, 0x90, 7);
			}
			else
			{
				constexpr byte8 buffer[] =
				{
					0x40, 0x88, 0xBB, 0x60, 0x63, 0x00, 0x00, //mov [rbx+00006360],dil
				};
				vp_memcpy(dest, buffer, sizeof(buffer));
			}
			/*
			dmc3.exe+1F0A33 - 40 88 BB 60630000 - mov [rbx+00006360],dil
			*/
		}

		// Air Trick Vergil Fix
		{
			auto dest = (appBaseAddr + 0x1F07D6);
			if (enable)
			{
				WriteJump(dest, airTrickVergilFix, 2);
			}
			else
			{
				constexpr byte8 buffer[] =
				{
					0xC6, 0x83, 0x10, 0x3E, 0x00, 0x00, 0x03, //mov byte ptr [rbx+00003E10],03
				};
				vp_memcpy(dest, buffer, sizeof(buffer));
			}
			/*
			dmc3.exe+1F07D6 - C6 83 103E0000 03 - mov byte ptr [rbx+00003E10],03
			dmc3.exe+1F07DD - E9 3C060000       - jmp dmc3.exe+1F0E1E
			*/
		}
	}
}

#endif
