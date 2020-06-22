module;
#include "../Core/Core.h"

#include "ActorData.h"
#include "Vars.h"
export module ModuleName(Dante);

import ModuleName(Config);

#ifdef __INTELLISENSE__
#include "Config.ixx"
#endif

byte8 * Dante_rainStorm = 0;

template <typename T>
void SkyStarResetFunction(T & actorData)
{
	if constexpr (typematch(T, ACTOR_DATA_DANTE))
	{
		actorData.skyStarCount = 0;
		actorData.newAirStingerCount = 0;
	}

	if (actorData.state & STATE_ON_FLOOR)
	{
		auto & event = actorData.eventData[1].index;

		if constexpr (typematch(T, ACTOR_DATA_DANTE))
		{
			if (event == ACTOR_EVENT_DANTE_AIR_TRICK)
			{
				actorData.airTrickCount = 1;
			}
		}
		else if constexpr (typematch(T, ACTOR_DATA_VERGIL))
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

void SkyStarReset(byte8 * baseAddr)
{
	auto & actorData = *reinterpret_cast<ACTOR_DATA *>(baseAddr);

	if (actorData.character == CHAR_DANTE)
	{
		auto & actorData = *reinterpret_cast<ACTOR_DATA_DANTE *>(baseAddr);

		SkyStarResetFunction(actorData);
	}
	else if (actorData.character == CHAR_VERGIL)
	{
		auto & actorData = *reinterpret_cast<ACTOR_DATA_VERGIL *>(baseAddr);

		SkyStarResetFunction(actorData);
	}
}

template
<
	uint32 index,
	typename T
>
uint32 MobilityFunction(T & actorData, uint8 & var, uint8(&array)[2])
{

	//actorData.newEvent = index;




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

auto Dash(ACTOR_DATA_DANTE & actorData)
{
	return MobilityFunction<ACTOR_EVENT_DANTE_DASH>(actorData, actorData.dashCount, Config.Dante.Trickster.dashCount);
}

auto SkyStar(ACTOR_DATA_DANTE & actorData)
{
	return MobilityFunction<ACTOR_EVENT_DANTE_SKY_STAR>(actorData, actorData.skyStarCount, Config.Dante.Trickster.skyStarCount);
}

auto AirTrickDante(ACTOR_DATA_DANTE & actorData)
{
	actorData.var_3E10[26] = (actorData.state & STATE_ON_FLOOR) ? 1 : 0;

	return MobilityFunction<ACTOR_EVENT_DANTE_AIR_TRICK>(actorData, actorData.airTrickCount, Config.Dante.Trickster.airTrickCount);
}

auto AirTrickVergil(ACTOR_DATA_VERGIL & actorData)
{
	return MobilityFunction<ACTOR_EVENT_VERGIL_AIR_TRICK>(actorData, actorData.airTrickCount, Config.Vergil.DarkSlayer.airTrickCount);
}

auto TrickUp(ACTOR_DATA_VERGIL & actorData)
{
	return MobilityFunction<ACTOR_EVENT_VERGIL_TRICK_UP>(actorData, actorData.trickUpCount, Config.Vergil.DarkSlayer.trickUpCount);
}

auto TrickDown(ACTOR_DATA_VERGIL & actorData)
{
	return MobilityFunction<ACTOR_EVENT_VERGIL_TRICK_DOWN>(actorData, actorData.trickDownCount, Config.Vergil.DarkSlayer.trickDownCount);
}




byte8 * dashProxy = 0;
byte8 * skyStarProxy = 0;
byte8 * airTrickDanteProxy = 0;
byte8 * airTrickVergilProxy = 0;
byte8 * trickUpProxy = 0;
byte8 * trickDownProxy = 0;

byte8 * airTrickDanteFix = 0;
byte8 * airTrickVergilFix = 0;









////PrivateEnd;


export void Mobility_Init()
{





	// Sky Star Reset
	{
		constexpr byte8 sect0[] =
		{
			0x88, 0x8B, 0x5D, 0x63, 0x00, 0x00, //mov [rbx+0000635D],cl
		};
		constexpr byte8 sect1[] =
		{
			0x48, 0x8B, 0xCB, //mov rcx,rbx
		};
		auto func = CreateFunction(SkyStarReset, 0, true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteCall((appBaseAddr + 0x1DFEAE), func.addr, 1);
		/*
		dmc3.exe+1DFEAE - 88 8B 5D630000 - mov [rbx+0000635D],cl
		*/
	}
	{
		constexpr byte8 sect0[] =
		{
			0x88, 0x8B, 0x5D, 0x63, 0x00, 0x00, //mov [rbx+0000635D],cl
		};
		constexpr byte8 sect1[] =
		{
			0x48, 0x8B, 0xCB, //mov rcx,rbx
		};
		auto func = CreateFunction(SkyStarReset, 0, true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteCall((appBaseAddr + 0x1DFFB6), func.addr, 1);
		/*
		dmc3.exe+1DFFB6 - 88 8B 5D630000 - mov [rbx+0000635D],cl
		*/
	}
	{
		constexpr byte8 sect0[] =
		{
			0x41, 0x88, 0x89, 0x5D, 0x63, 0x00, 0x00, //mov [r9+0000635D],cl
		};
		constexpr byte8 sect1[] =
		{
			0x49, 0x8B, 0xC9, //mov rcx,r9
		};
		auto func = CreateFunction(SkyStarReset, 0, true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteCall((appBaseAddr + 0x1E07A2), func.addr, 2);
		/*
		dmc3.exe+1E07A2 - 41 88 89 5D630000 - mov [r9+0000635D],cl
		*/
	}
	{
		constexpr byte8 sect0[] =
		{
			0x88, 0x8B, 0x5D, 0x63, 0x00, 0x00, //mov [rbx+0000635D],cl
		};
		constexpr byte8 sect1[] =
		{
			0x48, 0x8B, 0xCB, //mov rcx,rbx
		};
		auto func = CreateFunction(SkyStarReset, 0, true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteCall((appBaseAddr + 0x1E0D81), func.addr, 1);
		/*
		dmc3.exe+1E0D81 - 88 8B 5D630000 - mov [rbx+0000635D],cl
		*/
	}
	{
		constexpr byte8 sect0[] =
		{
			0x41, 0x88, 0x88, 0x5D, 0x63, 0x00, 0x00, //mov [r8+0000635D],cl
		};
		constexpr byte8 sect1[] =
		{
			0x49, 0x8B, 0xC8, //mov rcx,r8
		};
		auto func = CreateFunction(SkyStarReset, 0, true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteCall((appBaseAddr + 0x1E0F64), func.addr, 2);
		/*
		dmc3.exe+1E0F64 - 41 88 88 5D630000 - mov [r8+0000635D],cl
		*/
	}
	{
		constexpr byte8 sect0[] =
		{
			0x41, 0x88, 0x88, 0x5D, 0x63, 0x00, 0x00, //mov [r8+0000635D],cl
		};
		constexpr byte8 sect1[] =
		{
			0x49, 0x8B, 0xC8, //mov rcx,r8
		};
		auto func = CreateFunction(SkyStarReset, 0, true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteCall((appBaseAddr + 0x1E0FBD), func.addr, 2);
		/*
		dmc3.exe+1E0FBD - 41 88 88 5D630000 - mov [r8+0000635D],cl
		*/
	}
	{
		constexpr byte8 sect0[] =
		{
			0x88, 0x8B, 0x5D, 0x63, 0x00, 0x00, //mov [rbx+0000635D],cl
		};
		constexpr byte8 sect1[] =
		{
			0x48, 0x8B, 0xCB, //mov rcx,rbx
		};
		auto func = CreateFunction(SkyStarReset, 0, true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteCall((appBaseAddr + 0x1E16D2), func.addr, 1);
		/*
		dmc3.exe+1E16D2 - 88 8B 5D630000 - mov [rbx+0000635D],cl
		*/
	}
	{
		constexpr byte8 sect0[] =
		{
			0x88, 0x83, 0x5D, 0x63, 0x00, 0x00, //mov [rbx+0000635D],al
		};
		constexpr byte8 sect1[] =
		{
			0x48, 0x8B, 0xCB, //mov rcx,rbx
		};
		auto func = CreateFunction(SkyStarReset, 0, true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteCall((appBaseAddr + 0x1E66AC), func.addr, 1);
		/*
		dmc3.exe+1E66AC - 88 83 5D630000 - mov [rbx+0000635D],al
		*/
	}






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
	

	








	// Trick Up and Trick Down are reset when touching the ground again, Air Trick is not. Let's fix it.


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


















export void Mobility_Toggle(bool enable)
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

export void Dante_Init()
{
	LogFunction();


	Mobility_Init();




	// @Todo: Update input!
	{
		constexpr byte8 sect0[] =
		{
			0x66, 0x8B, 0x05, 0x00, 0x00, 0x00, 0x00, //mov ax,[dmc3.exe+D6CE88+E]
			0x66, 0x85, 0x83, 0xE0, 0x74, 0x00, 0x00, //test [rbx+000074E0],ax
			0x0F, 0x85, 0x00, 0x00, 0x00, 0x00,       //jne dmc3.exe+20CC20
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x20CC14), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteAddress(func.sect0, (appBaseAddr + 0xD6CE88 + 0xE), 7);
		WriteAddress((func.sect0 + 0xE), (appBaseAddr + 0x20CC20), 6);
		Dante_rainStorm = func.addr;
	}
}









export void Dante_AirHike_ToggleCoreAbility(bool enable)
{
	LogFunction(enable);
	Write<byte8>((appBaseAddr + 0x1E9B0E), (enable) ? 0xEB : 0x74);
}

export void Dante_Rebellion_ToggleInfiniteSwordPierce(bool enable)
{
	LogFunction(enable);
	if (enable)
	{
		vp_memset((appBaseAddr + 0x1CC9A4), 0x90, 5);
		vp_memset((appBaseAddr + 0x1CDA1B), 0x90, 4);
		vp_memset((appBaseAddr + 0x1CDD64), 0x90, 5);
		vp_memset((appBaseAddr + 0x1CDDCE), 0x90, 4);
		vp_memset((appBaseAddr + 0x21562E), 0x90, 5);
	}
	else
	{
		{
			constexpr byte8 buffer[] =
			{
				0xF3, 0x0F, 0x5C, 0x4B, 0x14, //subss xmm1,[rbx+14]
			};
			vp_memcpy((appBaseAddr + 0x1CC9A4), buffer, sizeof(buffer));
		}
		{
			constexpr byte8 buffer[] =
			{
				0xF3, 0x0F, 0x5C, 0xC1, //subss xmm0,xmm1
			};
			vp_memcpy((appBaseAddr + 0x1CDA1B), buffer, sizeof(buffer));
		}
		{
			constexpr byte8 buffer[] =
			{
				0xF3, 0x0F, 0x5C, 0x4B, 0x14, //subss xmm1,[rbx+14]
			};
			vp_memcpy((appBaseAddr + 0x1CDD64), buffer, sizeof(buffer));
		}
		{
			constexpr byte8 buffer[] =
			{
				0xF3, 0x0F, 0x5C, 0xCA, //subss xmm1,xmm2
			};
			vp_memcpy((appBaseAddr + 0x1CDDCE), buffer, sizeof(buffer));
		}
		{
			constexpr byte8 buffer[] =
			{
				0xF3, 0x0F, 0x5C, 0x47, 0x14, //subss xmm0,[rdi+14]
			};
			vp_memcpy((appBaseAddr + 0x21562E), buffer, sizeof(buffer));
		}
	}
}

export void Dante_EbonyIvory_ToggleFoursomeTime(bool enable)
{
	LogFunction(enable);
	WriteAddress((appBaseAddr + 0x1E24F6), (enable) ? (appBaseAddr + 0x1E24FC) : (appBaseAddr + 0x1E259C), 6);
	WriteAddress((appBaseAddr + 0x20D188), (enable) ? (appBaseAddr + 0x20D18A) : (appBaseAddr + 0x20D1AB), 2);
}

export void Dante_EbonyIvory_ToggleInfiniteRainStorm(bool enable)
{
	LogFunction(enable);
	if (enable)
	{
		WriteJump((appBaseAddr + 0x20CC0F), Dante_rainStorm);
	}
	else
	{
		constexpr byte8 buffer[] =
		{
			0x0F, 0xA3, 0xC1, //bt ecx,eax
			0x72, 0x0C,       //jb dmc3.exe+20CC20
		};
		vp_memcpy((appBaseAddr + 0x20CC0F), buffer, sizeof(buffer));
	}
}

export void Dante_Artemis_ToggleSwap(bool enable)
{
	LogFunction(enable);
	if (enable)
	{
		constexpr byte8 buffer[] =
		{
			0xC6, 0x87, 0x80, 0xB8, 0x00, 0x00, 0x01, //mov byte ptr [rdi+0000B880],01
		};
		vp_memcpy((appBaseAddr + 0x215C78), buffer, sizeof(buffer));
	}
	else
	{
		constexpr byte8 buffer[] =
		{
			0x44, 0x88, 0xB7, 0x80, 0xB8, 0x00, 0x00, //mov [rdi+0000B880],r14l
		};
		vp_memcpy((appBaseAddr + 0x215C78), buffer, sizeof(buffer));
	}
	Write<uint8>((appBaseAddr + 0x215CDA), (enable) ? 0 : 1);
}

export void Dante_Artemis_ToggleInstant(bool enable)
{
	LogFunction(enable);
	WriteAddress((appBaseAddr + 0x215E42), (enable) ? (appBaseAddr + 0x215E48) : (appBaseAddr + 0x215F78), 6);
}

export void Dante_CrazyCombo_SetLevelMultiplier(uint8 multiplier)
{
	LogFunction(multiplier);
	Write<uint8>((appBaseAddr + 0x5898DE), multiplier);
	Write<uint8>((appBaseAddr + 0x58999E), multiplier);
	Write<uint8>((appBaseAddr + 0x589A5E), multiplier);
}

#ifdef __GARBAGE__


//struct ResetHelper
//{
//	uint32 off;
//	const byte8 * buffer;
//	uint32 bufferSize;
//};
//
//constexpr byte8 buffer_1DFEA5[] =
//{
//	0x66, 0xC7, 0x83, 0x5E, 0x63, 0x00, 0x00, 0x01, 0x01, //mov word ptr [rbx+0000635E],0101
//};
//constexpr byte8 buffer_1DFFA6[] =
//{
//	0x66, 0xC7, 0x83, 0x5E, 0x63, 0x00, 0x00, 0x01, 0x01, //mov word ptr [rbx+0000635E],0101
//};
//constexpr byte8 buffer_1E0790[] =
//{
//	0x66, 0x41, 0xC7, 0x81, 0x5E, 0x63, 0x00, 0x00, 0x01, 0x01, //mov word ptr [r9+0000635E],0101
//};
//constexpr byte8 buffer_1E0D64[] =
//{
//	0x66, 0xC7, 0x83, 0x5E, 0x63, 0x00, 0x00, 0x01, 0x01, //mov word ptr [rbx+0000635E],0101
//};
//constexpr byte8 buffer_1E0F52[] =
//{
//	0x66, 0x41, 0xC7, 0x80, 0x5E, 0x63, 0x00, 0x00, 0x01, 0x01, //mov word ptr [r8+0000635E],0101
//};
//constexpr byte8 buffer_1E0FAB[] =
//{
//	0x66, 0x41, 0xC7, 0x80, 0x5E, 0x63, 0x00, 0x00, 0x01, 0x01, //mov word ptr [r8+0000635E],0101
//};
//constexpr byte8 buffer_1E16B5[] =
//{
//	0x66, 0xC7, 0x83, 0x5E, 0x63, 0x00, 0x00, 0x01, 0x01, //mov word ptr [rbx+0000635E],0101
//};
//constexpr byte8 buffer_1F0C92[] =
//{
//	0x40, 0x88, 0xBB, 0x5E, 0x63, 0x00, 0x00, //mov [rbx+0000635E],dil
//};
//constexpr byte8 buffer_1F2228[] =
//{
//	0xC6, 0x87, 0x5E, 0x63, 0x00, 0x00, 0x00, //mov byte ptr [rdi+0000635E],00
//};
//constexpr byte8 buffer_1F07CD[] =
//{
//	0x66, 0xC7, 0x83, 0x5F, 0x63, 0x00, 0x00, 0x01, 0x01, //mov word ptr [rbx+0000635F],0101
//};
//constexpr byte8 buffer_1F0B2A[] =
//{
//	0x40, 0x88, 0xBB, 0x5F, 0x63, 0x00, 0x00, //mov [rbx+0000635F],dil
//};
//constexpr byte8 buffer_1DFE9E[] =
//{
//	0xC6, 0x83, 0x60, 0x63, 0x00, 0x00, 0x01, //mov byte ptr [rbx+00006360],01
//};
//constexpr byte8 buffer_1DFFAF[] =
//{
//	0xC6, 0x83, 0x60, 0x63, 0x00, 0x00, 0x01, //mov byte ptr [rbx+00006360],01
//};
//constexpr byte8 buffer_1E079A[] =
//{
//	0x41, 0xC6, 0x81, 0x60, 0x63, 0x00, 0x00, 0x01, //mov byte ptr [r9+00006360],01
//};
//constexpr byte8 buffer_1E0D6D[] =
//{
//	0xC6, 0x83, 0x60, 0x63, 0x00, 0x00, 0x01, //mov byte ptr [rbx+00006360],01
//};
//constexpr byte8 buffer_1E0F5C[] =
//{
//	0x41, 0xC6, 0x80, 0x60, 0x63, 0x00, 0x00, 0x01, //mov byte ptr [r8+00006360],01
//};
//constexpr byte8 buffer_1E0FB5[] =
//{
//	0x41, 0xC6, 0x80, 0x60, 0x63, 0x00, 0x00, 0x01, //mov byte ptr [r8+00006360],01
//};
//constexpr byte8 buffer_1E16BE[] =
//{
//	0xC6, 0x83, 0x60, 0x63, 0x00, 0x00, 0x01, //mov byte ptr [rbx+00006360],01
//};
//constexpr byte8 buffer_1F0A33[] =
//{
//	0x40, 0x88, 0xBB, 0x60, 0x63, 0x00, 0x00, //mov [rbx+00006360],dil
//};
//
//constexpr ResetHelper resetHelper[] =
//{
//	{ 0x1DFEA5, buffer_1DFEA5, 9  },
//	{ 0x1DFFA6, buffer_1DFFA6, 9  },
//	{ 0x1E0790, buffer_1E0790, 10 },
//	{ 0x1E0D64, buffer_1E0D64, 9  },
//	{ 0x1E0F52, buffer_1E0F52, 10 },
//	{ 0x1E0FAB, buffer_1E0FAB, 10 },
//	{ 0x1E16B5, buffer_1E16B5, 9  },
//	{ 0x1F0C92, buffer_1F0C92, 7  },
//	{ 0x1F2228, buffer_1F2228, 7  },
//	{ 0x1F07CD, buffer_1F07CD, 9  },
//	{ 0x1F0B2A, buffer_1F0B2A, 7  },
//	{ 0x1DFE9E, buffer_1DFE9E, 7  },
//	{ 0x1DFFAF, buffer_1DFFAF, 7  },
//	{ 0x1E079A, buffer_1E079A, 8  },
//	{ 0x1E0D6D, buffer_1E0D6D, 7  },
//	{ 0x1E0F5C, buffer_1E0F5C, 8  },
//	{ 0x1E0FB5, buffer_1E0FB5, 8  },
//	{ 0x1E16BE, buffer_1E16BE, 7  },
//	{ 0x1F0A33, buffer_1F0A33, 7  },
//};








//void Toggle(bool enable)
//{
//
//}
//
//


// void Init2()
// {

// }















// @Todo: Cleanup, capture SkyStarReset event.





// void ResetMobilityCounters(byte8 * baseAddr)
// {

// }
	//// Required since there is no reset when hitting the floor.
	//if (actorData.state & STATE_ON_FLOOR)
	//{
	//	if constexpr (typematch(T, ACTOR_DATA_DANTE))
	//	{
	//		actorData.skyStarCount = 0;
	//		actorData.airTrickCount = 0;
	//	}
	//	else if constexpr (typematch(T, ACTOR_DATA_VERGIL))
	//	{
	//		actorData.airTrickCount = 0;
	//		actorData.trickUpCount = 0;
	//		actorData.trickDownCount = 0;
	//	}
	//}




	//if constexpr (typematch(T, ACTOR_DATA_VERGIL))
	//{
	//	if (actorData.state & STATE_ON_FLOOR)
	//	{
	//		var = 1;
	//		return index;
	//	}
	//}


	//if constexpr (index != 22)
	//{
	//	if (actorData.state & STATE_ON_FLOOR)
	//	{
	//		var = 1;
	//		return index;
	//	}
	//}


	//if (actorData.state & STATE_ON_FLOOR)
	//{
	//	if (actorData.eventData[1].index == index)
	//	{
	//		var = 1;
	//		return index;
	//	}
	//}


	// // Jump, leap and enemy jump
	// {
	// 	constexpr byte8 sect0[] =
	// 	{
	// 		0x41, 0x88, 0x88, 0x5D, 0x63, 0x00, 0x00, //mov [r8+0000635D],cl
	// 	};
	// 	constexpr byte8 sect1[] =
	// 	{
	// 		0x49, 0x8B, 0xC8, //mov rcx,r8
	// 	};
	// 	auto func = CreateFunction(ResetMobilityCounters, (appBaseAddr + 0x1E0F6B), true, true, sizeof(sect0), sizeof(sect1));
	// 	memcpy(func.sect0, sect0, sizeof(sect0));
	// 	memcpy(func.sect1, sect1, sizeof(sect1));
	// 	WriteJump((appBaseAddr + 0x1E0F64), func.addr, 2);
	// 	/*
	// 	dmc3.exe+1E0F64 - 41 88 88 5D630000 - mov [r8+0000635D],cl
	// 	dmc3.exe+1E0F6B - EB 5E             - jmp dmc3.exe+1E0FCB
	// 	*/
	// }

	// // Wall Hike from floor
	// {
	// 	constexpr byte8 sect0[] =
	// 	{
	// 		0x41, 0x88, 0x89, 0x5D, 0x63, 0x00, 0x00, //mov [r9+0000635D],cl
	// 	};
	// 	constexpr byte8 sect1[] =
	// 	{
	// 		0x49, 0x8B, 0xC9, //mov rcx,r9
	// 	};
	// 	auto func = CreateFunction(ResetMobilityCounters, (appBaseAddr + 0x1E07A9), true, true, sizeof(sect0), sizeof(sect1));
	// 	memcpy(func.sect0, sect0, sizeof(sect0));
	// 	memcpy(func.sect1, sect1, sizeof(sect1));
	// 	//WriteJump((appBaseAddr + 0x1E07A2), func.addr, 2);
	// 	/*
	// 	dmc3.exe+1E07A2 - 41 88 89 5D630000 - mov [r9+0000635D],cl
	// 	dmc3.exe+1E07A9 - EB 06             - jmp dmc3.exe+1E07B1
	// 	*/
	// }

	// // Fall off ledge
	// {
	// 	constexpr byte8 sect0[] =
	// 	{
	// 		0x88, 0x8B, 0x5D, 0x63, 0x00, 0x00, //mov [rbx+0000635D],cl
	// 	};
	// 	constexpr byte8 sect1[] =
	// 	{
	// 		0x48, 0x8B, 0xCB, //mov rcx,rbx
	// 	};
	// 	auto func = CreateFunction(ResetMobilityCounters, (appBaseAddr + 0x1DFFBC), true, true, sizeof(sect0), sizeof(sect1));
	// 	memcpy(func.sect0, sect0, sizeof(sect0));
	// 	memcpy(func.sect1, sect1, sizeof(sect1));
	// 	//WriteJump((appBaseAddr + 0x1DFFB6), func.addr, 1);
	// 	/*
	// 	dmc3.exe+1DFFB6 - 88 8B 5D630000    - mov [rbx+0000635D],cl
	// 	dmc3.exe+1DFFBC - 40 88 AB AE3F0000 - mov [rbx+00003FAE],bpl
	// 	*/
	// }




	//WriteAddress((appBaseAddr + 0x1E655E), dashProxy    , 6);
	//WriteAddress((appBaseAddr + 0x1E6567), skyStarProxy , 6);
	//WriteAddress((appBaseAddr + 0x1E6570), airTrickProxy, 6);




	// // Air Trick Dante Fix
	// // We can't do this in the reset function, because when the reset function is triggered when we
	// // for example do a normal jump the actor state has not been updated yet.
	// // It could still have STATE_ON_FLOOR set and airTrickCount would be 1 even though we didn't use it.
	// {
	// 	constexpr byte8 sect0[] =
	// 	{
	// 		0xE8, 0x00, 0x00, 0x00, 0x00,             //call dmc3.exe+1E0EE0
	// 		0xC6, 0x87, 0x5E, 0x63, 0x00, 0x00, 0x01, //mov byte ptr [rdi+0000635E],01
	// 	};
	// 	auto func = CreateFunction(0, (appBaseAddr + 0x1F2214), false, true, sizeof(sect0));
	// 	memcpy(func.sect0, sect0, sizeof(sect0));
	// 	WriteCall(func.sect0, (appBaseAddr + 0x1E0EE0));
	// 	airTrickDanteFix = func.addr;
	// 	/*
	// 	dmc3.exe+1F220F - E8 CCECFEFF - call dmc3.exe+1E0EE0
	// 	dmc3.exe+1F2214 - EB 0B       - jmp dmc3.exe+1F2221
	// 	*/
	// }

	// {
	// 	constexpr byte8 sect0[] =
	// 	{
	// 		0xE8, 0x00, 0x00, 0x00, 0x00,             //call dmc3.exe+1E0EE0
	// 		0xC6, 0x83, 0x5E, 0x63, 0x00, 0x00, 0x01, //mov byte ptr [rbx+0000635E],01
	// 		0xC6, 0x83, 0x5F, 0x63, 0x00, 0x00, 0x01, //mov byte ptr [rbx+0000635F],01
	// 		0xC6, 0x83, 0x60, 0x63, 0x00, 0x00, 0x01, //mov byte ptr [rbx+00006360],01
	// 	};
	// 	auto func = CreateFunction(0, (appBaseAddr + 0x1F0984), false, true, sizeof(sect0));
	// 	memcpy(func.sect0, sect0, sizeof(sect0));
	// 	WriteCall(func.sect0, (appBaseAddr + 0x1E0EE0));
	// 	airTrickVergilFix = func.addr;
	// 	/*
	// 	dmc3.exe+1F097F - E8 5C05FFFF - call dmc3.exe+1E0EE0
	// 	dmc3.exe+1F0984 - 33 D2       - xor edx,edx
	// 	*/
	// }






	// // Air Trick Dante Fix
	// {
	// 	auto dest = (appBaseAddr + 0x1F220F);

	// 	if (enable)
	// 	{
	// 		WriteJump(dest, airTrickDanteFix);
	// 	}
	// 	else
	// 	{
	// 		WriteCall(dest, (appBaseAddr + 0x1E0EE0));
	// 	}
	// 	/*
	// 	dmc3.exe+1F220F - E8 CCECFEFF - call dmc3.exe+1E0EE0
	// 	dmc3.exe+1F2214 - EB 0B       - jmp dmc3.exe+1F2221
	// 	*/
	// }


	// // Air Trick Vergil Fix
	// {
	// 	auto dest = (appBaseAddr + 0x1F097F);

	// 	if (enable)
	// 	{
	// 		WriteJump(dest, airTrickVergilFix);
	// 	}
	// 	else
	// 	{
	// 		WriteCall(dest, (appBaseAddr + 0x1E0EE0));
	// 	}
	// 	/*
	// 	dmc3.exe+1F097F - E8 5C05FFFF - call dmc3.exe+1E0EE0
	// 	dmc3.exe+1F0984 - 33 D2       - xor edx,edx
	// 	*/
	// }





	// Disable default resets for Air Trick, Trick Up and Trick Down.
	//for_all(uint8, index, countof<uint8>(resetHelper))
	//{
	//	auto & item = resetHelper[index];

	//	if (enable)
	//	{
	//		vp_memset((appBaseAddr + item.off), 0x90, item.bufferSize);
	//	}
	//	else
	//	{
	//		vp_memcpy((appBaseAddr + item.off), item.buffer, item.bufferSize);
	//	}
	//}



#endif
