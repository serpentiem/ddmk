#include "Dante.h"

byte8 * Dante_rainStorm = 0;



PrivateStart;

void ResetMobilityCounters(byte8 * baseAddr)
{
	LogFunction(baseAddr);

	auto & actorData = *reinterpret_cast<ACTOR_DATA_DANTE *>(baseAddr);
	memset(&actorData.dashCount, 0, 5);

	//{
	//	auto & actorData = *reinterpret_cast<ACTOR_DATA_VERGIL *>(baseAddr);
	//	actorData.trickUpCount = 23;
	//}


	//if (actorData.state & STATE_ON_FLOOR)
	//{
	//	actorData.airTrickCount = 1;
	//}


}




template
<
	uint32 index,
	typename T
>
uint32 MobilityFunction(T & actorData, uint8 & var, uint8(&array)[2])
{
	uint8 track = (actorData.devil) ? 1 : 0;

	

	if (var >= array[track])
	{
		return 0;
	}


	var++;




	return index;
}

auto Dash(ACTOR_DATA_DANTE & actorData)
{
	return MobilityFunction<22>(actorData, actorData.dashCount, Config.Dante.Trickster.dashCount);
}

auto SkyStar(ACTOR_DATA_DANTE & actorData)
{
	return MobilityFunction<23>(actorData, actorData.skyStarCount, Config.Dante.Trickster.skyStarCount);
}

auto AirTrick(ACTOR_DATA_DANTE & actorData)
{

	actorData.var_3E10[26] = (actorData.state & STATE_ON_FLOOR) ? 1 : 0;




	if (actorData.state & STATE_ON_FLOOR)
	{
		actorData.airTrickCount = 1;
	}







	return MobilityFunction<24>(actorData, actorData.airTrickCount, Config.Dante.Trickster.airTrickCount);
}








PrivateEnd;


void Mobility_Init()
{




	{
		constexpr byte8 sect0[] =
		{
			0x41, 0x88, 0x88, 0x5D, 0x63, 0x00, 0x00, //mov [r8+0000635D],cl
		};
		constexpr byte8 sect1[] =
		{
			0x49, 0x8B, 0xC8, //mov rcx,r8
		};
		auto func = CreateFunction(ResetMobilityCounters, (appBaseAddr + 0x1E0F6B), true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteJump((appBaseAddr + 0x1E0F64), func.addr, 2);
		/*
		dmc3.exe+1E0F64 - 41 88 88 5D630000 - mov [r8+0000635D],cl
		dmc3.exe+1E0F6B - EB 5E             - jmp dmc3.exe+1E0FCB
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
		auto func = CreateFunction(ResetMobilityCounters, (appBaseAddr + 0x1E07A9), true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteJump((appBaseAddr + 0x1E07A2), func.addr, 2);
		/*
		dmc3.exe+1E07A2 - 41 88 89 5D630000 - mov [r9+0000635D],cl
		dmc3.exe+1E07A9 - EB 06             - jmp dmc3.exe+1E07B1
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



	auto dashProxy     = CreateMobilityFunction(Dash    );
	auto skyStarProxy  = CreateMobilityFunction(SkyStar );
	auto airTrickProxy = CreateMobilityFunction(AirTrick);
	


	WriteAddress((appBaseAddr + 0x1E655E), dashProxy    , 6);
	WriteAddress((appBaseAddr + 0x1E6567), skyStarProxy , 6);
	WriteAddress((appBaseAddr + 0x1E6570), airTrickProxy, 6);




	// Air Trick Fix
	{
		constexpr byte8 sect0[] =
		{
			0xE8, 0x00, 0x00, 0x00, 0x00,             //call dmc3.exe+1E0EE0
			0xC6, 0x87, 0x5E, 0x63, 0x00, 0x00, 0x01, //mov byte ptr [rdi+0000635E],01
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x1F2214), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteCall(func.sect0, (appBaseAddr + 0x1E0EE0));
		WriteJump((appBaseAddr + 0x1F220F), func.addr);
		/*
		dmc3.exe+1F220F - E8 CCECFEFF - call dmc3.exe+1E0EE0
		dmc3.exe+1F2214 - EB 0B       - jmp dmc3.exe+1F2221
		*/
	}


	/*
	dmc3.exe+1F2228 - C6 87 5E630000 00     - mov byte ptr [rdi+0000635E],00 { 0 }
	*/


	vp_memset((appBaseAddr + 0x1F2228), 0x90, 7);









	//{
	//	constexpr byte8 sect1[] =
	//	{
	//		0x48, 0x8B, 0xCB, //mov rcx,rbx
	//	};
	//	constexpr byte8 sect2[] =
	//	{
	//		0x84, 0xC0,                               //test al,al
	//		0x0F, 0x84, 0x00, 0x00, 0x00, 0x00,       //je dmc3.exe+1E64A9
	//		0xBA, 0x16, 0x00, 0x00, 0x00,             //mov edx,00000016
	//		0xFE, 0x83, 0x5C, 0x63, 0x00, 0x00,       //inc byte ptr [rbx+0000635C]
	//		0x0F, 0xB6, 0x83, 0xA4, 0x3F, 0x00, 0x00, //movzx eax,byte ptr [rbx+00003FA4]
	//	};
	//	auto func = CreateFunction(Dash, (appBaseAddr + 0x1E671C), true, false, 0, sizeof(sect1), sizeof(sect2));
	//	memcpy(func.sect1, sect1, sizeof(sect1));
	//	memcpy(func.sect2, sect2, sizeof(sect2));
	//	WriteAddress((func.sect2 + 2), (appBaseAddr + 0x1E64A9), 6);
	//	WriteJump((appBaseAddr + 0x1E66CB), func.addr, 1);
	//	/*
	//	dmc3.exe+1E66CB - 8B 8B 58630000 - mov ecx,[rbx+00006358]
	//	dmc3.exe+1E66D1 - 85 C9          - test ecx,ecx
	//	*/
	//	/*
	//	dmc3.exe+1E671C - 88 83 A53F0000 - mov [rbx+00003FA5],al
	//	dmc3.exe+1E6722 - 0FB6 47 08     - movzx eax,byte ptr [rdi+08]
	//	*/
	//}



	//{
	//	constexpr byte8 sect1[] =
	//	{
	//		0x48, 0x8B, 0xCB, //mov rcx,rbx
	//	};
	//	constexpr byte8 sect2[] =
	//	{
	//		0x84, 0xC0,                               //test al,al
	//		0x0F, 0x84, 0x00, 0x00, 0x00, 0x00,       //je dmc3.exe+1E64A9
	//		0xBA, 0x17, 0x00, 0x00, 0x00,             //mov edx,00000017
	//		0xFE, 0x83, 0x5D, 0x63, 0x00, 0x00,       //inc byte ptr [rbx+0000635D]
	//		0x0F, 0xB6, 0x83, 0xA4, 0x3F, 0x00, 0x00, //movzx eax,byte ptr [rbx+00003FA4]
	//	};
	//	auto func = CreateFunction(SkyStar, (appBaseAddr + 0x1E66B9), true, false, 0, sizeof(sect1), sizeof(sect2));
	//	memcpy(func.sect1, sect1, sizeof(sect1));
	//	memcpy(func.sect2, sect2, sizeof(sect2));
	//	WriteAddress((func.sect2 + 2), (appBaseAddr + 0x1E64A9), 6);
	//	WriteJump((appBaseAddr + 0x1E6689), func.addr, 2);
	//	/*
	//	dmc3.exe+1E6689 - 83 BB 58630000 01 - cmp dword ptr [rbx+00006358],01
	//	dmc3.exe+1E6690 - 0F8C 13FEFFFF     - jl dmc3.exe+1E64A9
	//	*/
	//	/*
	//	dmc3.exe+1E66B9 - 88 83 A53F0000 - mov [rbx+00003FA5],al
	//	dmc3.exe+1E66BF - 0FB6 47 08     - movzx eax,byte ptr [rdi+08]
	//	*/
	//}


	//{
	//	constexpr byte8 sect1[] =
	//	{
	//		0x48, 0x8B, 0xCB, //mov rcx,rbx
	//	};
	//	constexpr byte8 sect2[] =
	//	{
	//		0x84, 0xC0,                               //test al,al
	//		0x0F, 0x84, 0x00, 0x00, 0x00, 0x00,       //je dmc3.exe+1E64A9
	//		0xBA, 0x18, 0x00, 0x00, 0x00,             //mov edx,00000018
	//		0xFE, 0x83, 0x5E, 0x63, 0x00, 0x00,       //inc byte ptr [rbx+0000635E]
	//		0x0F, 0xB6, 0x83, 0xA4, 0x3F, 0x00, 0x00, //movzx eax,byte ptr [rbx+00003FA4]
	//	};
	//	auto func = CreateFunction(AirTrick, (appBaseAddr + 0x1E6652), true, false, 0, sizeof(sect1), sizeof(sect2));
	//	memcpy(func.sect1, sect1, sizeof(sect1));
	//	memcpy(func.sect2, sect2, sizeof(sect2));
	//	WriteAddress((func.sect2 + 2), (appBaseAddr + 0x1E64A9), 6);
	//	WriteJump((appBaseAddr + 0x1E6612), func.addr, 2);
	//	/*
	//	dmc3.exe+1E6612 - 83 BB 58630000 02 - cmp dword ptr [rbx+00006358],02
	//	dmc3.exe+1E6619 - 0F85 8AFEFFFF     - jne dmc3.exe+1E64A9
	//	*/
	//	/*
	//	dmc3.exe+1E6652 - 88 83 A53F0000 - mov [rbx+00003FA5],al
	//	dmc3.exe+1E6658 - 85 C9          - test ecx,ecx
	//	*/
	//}

















	//{
	//	constexpr byte8 sect1[] =
	//	{
	//		0x48, 0x8B, 0xCB, //mov rcx,rbx
	//	};
	//	constexpr byte8 sect2[] =
	//	{
	//		0x84, 0xC0,                         //test al,al
	//		0x0F, 0x84, 0x00, 0x00, 0x00, 0x00, //je dmc3.exe+1E64A9
	//		0xBA, 0x17, 0x00, 0x00, 0x00,       //mov edx,00000017
	//		0xFE, 0x83, 0x5D, 0x63, 0x00, 0x00, //inc byte ptr [rbx+0000635D]
	//	};
	//	auto func = CreateFunction(SkyStar, (appBaseAddr + 0x1E66B2), true, false, 0, sizeof(sect1), sizeof(sect2));
	//	memcpy(func.sect1, sect1, sizeof(sect1));
	//	memcpy(func.sect2, sect2, sizeof(sect2));
	//	WriteAddress((func.sect2 + 2), (appBaseAddr + 0x1E64A9), 6);
	//	//WriteJump((appBaseAddr + 0x1E6696), func.addr, 2);
	//	/*
	//	dmc3.exe+1E6696 - 0FB6 83 5D630000 - movzx eax,byte ptr [rbx+0000635D]
	//	dmc3.exe+1E669D - 84 C0            - test al,al
	//	dmc3.exe+1E669F - 0F8E 04FEFFFF    - jng dmc3.exe+1E64A9
	//	dmc3.exe+1E66A5 - FE C8            - dec al
	//	dmc3.exe+1E66A7 - BA 17000000      - mov edx,00000017
	//	dmc3.exe+1E66AC - 88 83 5D630000   - mov [rbx+0000635D],al
	//	dmc3.exe+1E66B2 - 0FB6 83 A43F0000 - movzx eax,byte ptr [rbx+00003FA4]
	//	*/
	//}


	//{
	//	constexpr byte8 sect1[] =
	//	{
	//		0x48, 0x8B, 0xCB, //mov rcx,rbx
	//	};
	//	constexpr byte8 sect2[] =
	//	{
	//		0x84, 0xC0,                               //test al,al
	//		0x0F, 0x84, 0x00, 0x00, 0x00, 0x00,       //je dmc3.exe+1E64A9
	//		0xBA, 0x18, 0x00, 0x00, 0x00,             //mov edx,00000018
	//		0xFE, 0x83, 0x5E, 0x63, 0x00, 0x00,       //inc byte ptr [rbx+0000635E]
	//		0x0F, 0xB6, 0x83, 0xA4, 0x3F, 0x00, 0x00, //movzx eax,byte ptr [rbx+00003FA4]
	//	};
	//	auto func = CreateFunction(AirTrick, (appBaseAddr + 0x1E6652), true, false, 0, sizeof(sect1), sizeof(sect2));
	//	memcpy(func.sect1, sect1, sizeof(sect1));
	//	memcpy(func.sect2, sect2, sizeof(sect2));
	//	WriteAddress((func.sect2 + 2), (appBaseAddr + 0x1E64A9), 6);
	//	//WriteJump((appBaseAddr + 0x1E6634), func.addr, 1);
	//	/*
	//	dmc3.exe+1E6634 - 38 8B 5E630000   - cmp [rbx+0000635E],cl
	//	dmc3.exe+1E663A - 0F8E 69FEFFFF    - jng dmc3.exe+1E64A9
	//	dmc3.exe+1E6640 - 0FB6 83 A43F0000 - movzx eax,byte ptr [rbx+00003FA4]
	//	dmc3.exe+1E6647 - BA 18000000      - mov edx,00000018
	//	dmc3.exe+1E664C - FE 8B 5E630000   - dec [rbx+0000635E]
	//	dmc3.exe+1E6652 - 88 83 A53F0000   - mov [rbx+00003FA5],al
	//	*/
	//}







	//Write<byte8>((appBaseAddr + 0x1E0FF8), 0x80);
	//Write<byte8>((appBaseAddr + 0x1E66A6), 0xC0);
	//Write<byte8>((appBaseAddr + 0x1E664D), 0x83);
}















void Dante_Init()
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
