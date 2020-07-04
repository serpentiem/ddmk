#ifndef __MODULE_EVENT__
#define __MODULE_EVENT__

module;
#include "../Core/Core.h"

#include "ActorData.h"
#include "Internal.h"
#include "Vars.h"
export module ModuleName(Event);

import ModuleName(Actor);
import ModuleName(Arcade);
import ModuleName(BossRush);
import ModuleName(Config);
import ModuleName(File);
import ModuleName(Mobility);

#ifdef __INTELLISENSE__
#include "Actor.ixx"
#include "Arcade.ixx"
#include "BossRush.ixx"
#include "Config.ixx"
#include "File.ixx"
#include "Mobility.ixx"
#endif

constexpr bool debug = true;




//bool MainLoop_run = false;










void SetPool()
{
	LogFunction();
}

void ClearPool()
{
	LogFunction();
	File_dynamicFiles.Clear();
	Actor_actorBaseAddr.Clear();
}

































bool MainLoopOnce_run = false;
bool MainLoopOnceSync_run = false;










void InitSession()
{
	LogFunction();
	Arcade_InitSession();
}

void SetCharacter(byte8 * dest)
{
	LogFunction();
	Arcade_SetCharacter(dest);
}

void SetRoom()
{
	LogFunction();
	Arcade_SetRoom();
	BossRush_SetRoom();
}

void SetNextRoom()
{
	LogFunction();
	BossRush_SetNextRoom();
}

void SetContinueRoom()
{
	LogFunction();
	BossRush_SetContinueRoom();
}

bool SetTrack
(
	byte8 * dest,
	const char * filename,
	uint32 arg3,
	uint32 arg4
)
{
	Log("%s %llX %s %u %u", FUNC_NAME, dest, filename, arg3, arg4);

	return BossRush_SetTrack(filename);
}







void UnlockActor(byte8 * baseAddr)
{
	auto & actorData = *reinterpret_cast<ACTOR_DATA *>(baseAddr);
	actorData.newButtonMask = 0xFFFF;
	actorData.newEnableRightStick = true;
	actorData.newEnableLeftStick = true;
}





void CreateMainActor(byte8 * baseAddr)
{
	MainLoopOnce_run = false;
	MainLoopOnceSync_run = false;

	Actor_CreateMainActor(baseAddr);

	UnlockActor(baseAddr);



	//Actor_Main();



	//SpawnActors();



}

void Main_CreateMainActor(byte8 * baseAddr)
{
	LogFunction();

	return CreateMainActor(baseAddr);
}


void Customize_CreateMainActor(byte8 * baseAddr)
{
	LogFunction();

	return CreateMainActor(baseAddr);
}

















void Main()
{
	LogFunction();

	Actor_Main();


}

void Customize_Main()
{
	LogFunction();




}








void Main_Teleport()
{
	LogFunction();

	//Actor_Teleport();

}




void Main_Customize()
{
	LogFunction();



	//Actor_Customize();

}









void MissionClear()
{
	LogFunction();





}

void GameOver()
{
	LogFunction();
}

void MissionStart()
{
	LogFunction();

	//Actor_MissionStart();

}

void MissionSelect()
{
	LogFunction();

	//Actor_MissionSelect();



}

void Pause_Sub(SCENE_DATA & sceneData)
{
	switch (sceneData.subscene)
	{
	case SUBSCENE_MISSION_CLEAR:
	{
		MissionClear();
		break;
	}
	case SUBSCENE_GAME_OVER:
	{
		GameOver();
		break;
	}
	case SUBSCENE_MISSION_START:
	{
		MissionStart();
		break;
	}
	case SUBSCENE_MISSION_SELECT:
	{
		MissionSelect();
		break;
	}
	}
}












void MainLoopOnce()
{
	if (!MainLoopOnce_run)
	{
		MainLoopOnce_run = true;

		LogFunction();

		Actor_MainLoopOnce();
	}
}

void MainLoopOnceSync()
{
	auto & cutsceneBar = *reinterpret_cast<bool *>(appBaseAddr + 0x5D113D);
	if (cutsceneBar)
	{
		return;
	}

	if (!MainLoopOnceSync_run)
	{
		MainLoopOnceSync_run = true;

		LogFunction();

		Actor_MainLoopOnceSync();
	}
}

void MainLoop()
{
	MainLoopOnce();
	MainLoopOnceSync();
}




































//void CreateMainClone(byte8 * baseAddr)
//{
//	LogFunction(baseAddr);
//	Actor_actorBaseAddr[1] = baseAddr;
//}






void SkyStarReset(byte8 * baseAddr)
{
	Mobility::SkyStarReset(baseAddr);
}






































export void Event_Init()
{



	vp_memset((appBaseAddr + 0x27A39C), 0x90, 5); // Disable Style Rank Sub


	
	/*

	dmc3.exe+27A39C - F3 0F11 4B 04         - movss [rbx+04],xmm1


	*/















	LogFunction();

	// Main
	{
		constexpr byte8 sect0[] =
		{
			0xE8, 0x00, 0x00, 0x00, 0x00, // call dmc3.exe+212760
		};
		auto func = CreateFunction(InitSession, (appBaseAddr + 0x2432CB), true, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteCall(func.sect0, (appBaseAddr + 0x212760));
		WriteJump((appBaseAddr + 0x2432C6), func.addr);
		/*
		dmc3.exe+2432C6 - E8 95F4FCFF - call dmc3.exe+212760
		dmc3.exe+2432CB - 33 FF       - xor edi,edi
		*/
	}
	{
		constexpr byte8 sect1[] =
		{
			0x48, 0x8B, 0xC8, //mov rcx,rax
		};
		constexpr byte8 sect2[] =
		{
			0x0F, 0xB6, 0x88, 0x65, 0x45, 0x00, 0x00, // movzx ecx,byte ptr [rax+00004565]
		};
		auto func = CreateFunction(SetCharacter, (appBaseAddr + 0x24350B), true, true, 0, sizeof(sect1), sizeof(sect2));
		memcpy(func.sect1, sect1, sizeof(sect1));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteJump((appBaseAddr + 0x243504), func.addr, 2);
		/*
		dmc3.exe+243504 - 0FB6 88 65450000 - movzx ecx,byte ptr [rax+00004565]
		dmc3.exe+24350B - 88 0D 53BDA400   - mov [dmc3.exe+C8F264],cl
		*/
	}
	{
		constexpr byte8 sect0[] =
		{
			0x66, 0x89, 0x82, 0x64, 0x01, 0x00, 0x00, // mov [rdx+00000164],ax
		};
		constexpr byte8 sect1[] =
		{
			0x48, 0x8B, 0xCA, //mov rcx,rdx
		};
		auto func = CreateFunction(SetRoom, (appBaseAddr + 0x1AA8CC), true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteJump((appBaseAddr + 0x1AA8C5), func.addr, 2);
		/*
		dmc3.exe+1AA8C5 - 66 89 82 64010000 - mov [rdx+00000164],ax
		dmc3.exe+1AA8CC - C3                - ret
		*/
	}
	{
		constexpr byte8 sect0[] =
		{
			0x66, 0x89, 0x90, 0x66, 0x01, 0x00, 0x00, // mov [rax+00000166],dx
		};
		constexpr byte8 sect1[] =
		{
			0x48, 0x8B, 0xC8, //mov rcx,rax
		};
		auto func = CreateFunction(SetNextRoom, (appBaseAddr + 0x1A6002), true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteJump((appBaseAddr + 0x1A5FFB), func.addr, 2);
		/*
		dmc3.exe+1A5FFB - 66 89 90 66010000 - mov [rax+00000166],dx
		dmc3.exe+1A6002 - EB 23             - jmp dmc3.exe+1A6027
		*/
	}
	{
		constexpr byte8 sect0[] =
		{
			0x66, 0x89, 0x81, 0x66, 0x01, 0x00, 0x00, // mov [rcx+00000166],ax
		};
		auto func = CreateFunction(SetContinueRoom, (appBaseAddr + 0x1AA3CC), true, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteJump((appBaseAddr + 0x1AA3C5), func.addr, 2);
		/*
		dmc3.exe+1AA3C5 - 66 89 81 66010000       - mov [rcx+00000166],ax
		dmc3.exe+1AA3CC - C7 81 60010000 00000000 - mov [rcx+00000160],00000000
		*/
	}
	{
		constexpr byte8 sect0[] =
		{
			0x48, 0x89, 0x5C, 0x24, 0x08, // mov [rsp+08],rbx
		};
		constexpr byte8 sect2[] =
		{
			0x84, 0xC0, // test al,al
			0x75, 0x01, // jne short
			0xC3,       // ret
		};
		auto func = CreateFunction(SetTrack, (appBaseAddr + 0x32BA95), true, false, sizeof(sect0), 0, sizeof(sect2));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteJump((appBaseAddr + 0x32BA90), func.addr);
		/*
		dmc3.exe+32BA90 - 48 89 5C 24 08 - mov [rsp+08],rbx
		dmc3.exe+32BA95 - 48 89 6C 24 10 - mov [rsp+10],rbp
		*/
	}

	// CreateMainActor
	{
		constexpr byte8 sect0[] =
		{
			0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc3.exe+1DE820
		};
		constexpr byte8 sect1[] =
		{
			0x48, 0x8B, 0xC8, //mov rcx,rax
		};
		auto func = CreateFunction(Main_CreateMainActor, (appBaseAddr + 0x23C77E), true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteCall(func.sect0, (appBaseAddr + 0x1DE820));
		WriteJump((appBaseAddr + 0x23C779), func.addr);
		/*
		dmc3.exe+23C779 - E8 A220FAFF       - call dmc3.exe+1DE820
		dmc3.exe+23C77E - 48 89 87 B82C0000 - mov [rdi+00002CB8],rax
		*/
	}
	{
		constexpr byte8 sect0[] =
		{
			0xE8, 0x00, 0x00, 0x00, 0x00, // call dmc3.exe+1DE820
		};
		constexpr byte8 sect1[] =
		{
			0x48, 0x8B, 0xC8, // mov rcx,rax
		};
		auto func = CreateFunction(Customize_CreateMainActor, (appBaseAddr + 0x23B7B8), true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteCall(func.sect0, (appBaseAddr + 0x1DE820));
		WriteJump((appBaseAddr + 0x23B7B3), func.addr);
		/*
		dmc3.exe+23B7B3 - E8 6830FAFF       - call dmc3.exe+1DE820
		dmc3.exe+23B7B8 - 48 89 87 B82C0000 - mov [rdi+00002CB8],rax
		*/
	}

	// Scenes
	{
		constexpr byte8 sect0[] =
		{
			0xC7, 0x47, 0x20, 0x01, 0x00, 0x00, 0x00, // mov [rdi+20],00000001
		};
		auto func = CreateFunction(Main, (appBaseAddr + 0x23D0AB), true, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteJump((appBaseAddr + 0x23D0A4), func.addr, 2);
		/*
		dmc3.exe+23D0A4 - C7 47 20 01000000 - mov [rdi+20],00000001
		dmc3.exe+23D0AB - 40 88 77 24       - mov [rdi+24],sil
		*/
	}
	{
		constexpr byte8 sect0[] =
		{
			0xC7, 0x47, 0x20, 0x01, 0x00, 0x00, 0x00, // mov [rdi+20],00000001
		};
		auto func = CreateFunction(Customize_Main, (appBaseAddr + 0x23BB71), true, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteJump((appBaseAddr + 0x23BB6A), func.addr, 2);
		/*
		dmc3.exe+23BB6A - C7 47 20 01000000 - mov [rdi+20],00000001
		dmc3.exe+23BB71 - BA 00000080       - mov edx,80000000
		*/
	}
	{
		constexpr byte8 sect0[] =
		{
			0xC7, 0x41, 0x20, 0x02, 0x00, 0x00, 0x00, // mov [rcx+20],00000002
		};
		auto func = CreateFunction(Main_Teleport, (appBaseAddr + 0x23B3DA), true, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteJump((appBaseAddr + 0x23B3D3), func.addr, 2);
		/*
		dmc3.exe+23B3D3 - C7 41 20 02000000 - mov [rcx+20],00000002
		dmc3.exe+23B3DA - C6 41 24 00       - mov byte ptr [rcx+24],00
		*/
	}
	{
		constexpr byte8 sect0[] =
		{
			0xC7, 0x41, 0x20, 0x09, 0x00, 0x00, 0x00, // mov [rcx+20],00000009
		};
		auto func = CreateFunction(Main_Customize, (appBaseAddr + 0x23B21D), true, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteJump((appBaseAddr + 0x23B216), func.addr, 2);
		/*
		dmc3.exe+23B216 - C7 41 20 09000000 - mov [rcx+20],00000009
		dmc3.exe+23B21D - C6 41 24 00       - mov byte ptr [rcx+24],00
		*/
	}
	{
		constexpr byte8 sect0[] =
		{
			0xC7, 0x43, 0x20, 0x0B, 0x00, 0x00, 0x00, // mov [rbx+20],0000000B
		};
		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};
		auto func = CreateFunction(Pause_Sub, (appBaseAddr + 0x23D7D7), true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteJump((appBaseAddr + 0x23D7D0), func.addr, 2);
		/*
		dmc3.exe+23D7D0 - C7 43 20 0B000000 - mov [rbx+20],0000000B
		dmc3.exe+23D7D7 - C6 43 24 00       - mov byte ptr [rbx+24],00
		*/
	}

























	// Loops
	{
		constexpr byte8 sect0[] =
		{
			0xE8, 0x00, 0x00, 0x00, 0x00, // call dmc3.exe+23B060
		};
		auto func = CreateFunction(MainLoop, (appBaseAddr + 0x23D4B7), true, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteCall(func.sect0, (appBaseAddr + 0x23B060));
		WriteJump((appBaseAddr + 0x23D4B2), func.addr);
		/*
		dmc3.exe+23D4B2 - E8 A9DBFFFF - call dmc3.exe+23B060
		dmc3.exe+23D4B7 - 84 C0       - test al,al
		*/
	}


















	

	//// Main



	//// Teleport


	//// Customize


	//// Sub
	//{
	//	constexpr byte8 sect0[] =
	//	{
	//		0xC7, 0x43, 0x20, 0x0B, 0x00, 0x00, 0x00, // mov [rbx+20],0000000B
	//	};
	//	constexpr byte8 sect1[] =
	//	{
	//		mov_rcx_rbx,
	//	};
	//	auto func = CreateFunction(SetScene, (appBaseAddr + 0x23C380), true, true, sizeof(sect0), sizeof(sect1));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	memcpy(func.sect1, sect1, sizeof(sect1));
	//	WriteJump((appBaseAddr + 0x23C379), func.addr, 2);
	//	/*
	//	dmc3.exe+23C379 - C7 43 20 0B000000 - mov [rbx+20],0000000B
	//	dmc3.exe+23C380 - 40 88 7B 24       - mov [rbx+24],dil
	//	*/
	//}













































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















	






















































	{
		constexpr byte8 sect0[] =
		{
			0x48, 0x89, 0x15, 0x00, 0x00, 0x00, 0x00, //mov [dmc3.exe+C90E28],rdx
		};
		auto func = CreateFunction(SetPool, (appBaseAddr + 0x23E69F), true, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteAddress(func.sect0, (appBaseAddr + 0xC90E28), 7);
		WriteJump((appBaseAddr + 0x23E698), func.addr, 2);
		/*
		dmc3.exe+23E698 - 48 89 15 8927A500 - mov [dmc3.exe+C90E28],rdx
		dmc3.exe+23E69F - 48 8D 83 D06A0000 - lea rax,[rbx+00006AD0]
		*/
	}
	{
		constexpr byte8 sect0[] =
		{
			0x48, 0x89, 0x0D, 0x00, 0x00, 0x00, 0x00, //mov [dmc3.exe+C90E28],rcx
		};
		auto func = CreateFunction(ClearPool, (appBaseAddr + 0x23B39A), true, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteAddress(func.sect0, (appBaseAddr + 0xC90E28), 7);
		WriteJump((appBaseAddr + 0x23B393), func.addr, 2);
		/*
		dmc3.exe+23B393 - 48 89 0D 8E5AA500 - mov [dmc3.exe+C90E28],rcx
		dmc3.exe+23B39A - 48 89 0D 975AA500 - mov [dmc3.exe+C90E38],rcx
		*/
	}



	



	//{
	//	byte8 sect0[] =
	//	{
	//		0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc3.exe+1DE820
	//	};
	//	byte8 sect1[] =
	//	{
	//		0x48, 0x8B, 0xC8, //mov rcx,rax
	//	};
	//	auto func = CreateFunction(CreateMainClone, (appBaseAddr + 0x2134E3), true, true, sizeof(sect0), sizeof(sect1));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	memcpy(func.sect1, sect1, sizeof(sect1));
	//	WriteCall(func.sect0, (appBaseAddr + 0x1DE820));
	//	WriteJump((appBaseAddr + 0x2134DE), func.addr);
	//	/*
	//	dmc3.exe+2134DE - E8 3DB3FCFF       - call dmc3.exe+1DE820
	//	dmc3.exe+2134E3 - 48 89 86 78640000 - mov [rsi+00006478],rax
	//	*/
	//}
	//{
	//	byte8 sect0[] =
	//	{
	//		0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc3.exe+1DE820
	//	};
	//	byte8 sect1[] =
	//	{
	//		0x48, 0x8B, 0xC8, //mov rcx,rax
	//	};
	//	auto func = CreateFunction(CreateMainClone, (appBaseAddr + 0x211E88), true, true, sizeof(sect0), sizeof(sect1));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	memcpy(func.sect1, sect1, sizeof(sect1));
	//	WriteCall(func.sect0, (appBaseAddr + 0x1DE820));
	//	WriteJump((appBaseAddr + 0x211E83), func.addr);
	//	/*
	//	dmc3.exe+211E83 - E8 98C9FCFF       - call dmc3.exe+1DE820
	//	dmc3.exe+211E88 - 48 89 83 78640000 - mov [rbx+00006478],rax
	//	*/
	//}
}

export void Event_ToggleSkipIntro(bool enable)
{
	LogFunction(enable);
	WriteAddress((appBaseAddr + 0x2383F2), (enable) ? (appBaseAddr + 0x2383F8) : (appBaseAddr + 0x238527), 6); // Skip Message
	WriteAddress((appBaseAddr + 0x241789), (enable) ? (appBaseAddr + 0x24178B) : (appBaseAddr + 0x2417A6), 2); // Skip Video
	Write<uint8>((appBaseAddr + 0x238704), (enable) ? 0 : 1); // Hide Rebellion
	// Disable Video Timer
	{
		auto dest = (appBaseAddr + 0x243531);
		if (enable)
		{
			vp_memset(dest, 0x90, 2);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0xFF, 0xC8, //dec eax
			};
			vp_memcpy(dest, buffer, sizeof(buffer));
		}
	}
}

export void Event_ToggleSkipCutscenes(bool enable)
{
	LogFunction(enable);
	WriteAddress((appBaseAddr + 0x238CCA), (enable) ? (appBaseAddr + 0x238CD0) : (appBaseAddr + 0x238E62), 6);
	WriteAddress((appBaseAddr + 0x238CD8), (enable) ? (appBaseAddr + 0x238CDE) : (appBaseAddr + 0x238E62), 6);
	WriteAddress((appBaseAddr + 0x238CE3), (enable) ? (appBaseAddr + 0x238CE9) : (appBaseAddr + 0x238E62), 6);
}

#ifdef __GARBAGE__

// @Reaseach: Probably no longer needed.

void ActorInitComplete(byte8 * baseAddr)
{
	LogFunction(baseAddr);

	//if (baseAddr == System_Actor_actorBaseAddr[0])
	//{
	//	return;
	//}
	//if (baseAddr == System_Actor_actorBaseAddr[1])
	//{
	//	return;
	//}

	//auto & actorData = *(ACTOR_DATA *)baseAddr;
	//actorData.shadow = 1;
	//actorData.collisionIndex = 1;



	auto & actorData = *reinterpret_cast<ACTOR_DATA *>(baseAddr);
	//actorData.collisionIndex = 1;
	//actorData.newButtonMask = 0xFFFF


	//actorData.newAirStingerCount = 1;


	{
		byte8 sect0[] =
		{
			0x66, 0xC7, 0x43, 0x08, 0x01, 0x00, //mov word ptr [rbx+08],0001
		};
		byte8 sect1[] =
		{
			0x48, 0x8B, 0xCB, //mov rcx,rbx
		};
		auto func = CreateFunction(ActorInitComplete, (appBaseAddr + 0x1F7D87), true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteJump((appBaseAddr + 0x1F7D81), func.addr, 1);
		/*
		dmc3.exe+1F7D81 - 66 C7 43 08 0100 - mov word ptr [rbx+08],0001
		dmc3.exe+1F7D87 - 48 8B 5C 24 58   - mov rbx,[rsp+58]
		*/
	}


}






















static void Actor_StageLoadComplete()
{


	// Adjust style.

	//{
	//	auto & baseAddr1 = System_Actor_actorBaseAddr[ACTOR_ONE];
	//	if (!baseAddr1)
	//	{
	//		goto sect0;
	//	}
	//	auto & style = *(uint32 *)(baseAddr1 + 0x6338);
	//	if ((style == STYLE_DANTE_DOPPELGANGER) && Config.System.Actor.forceSingleActor)
	//	{
	//		style = STYLE_DANTE_TRICKSTER;
	//	}
	//}
	//sect0:









	return;


	//return;


	//auto & baseAddr = System_Actor_actorBaseAddr[ACTOR_TWO];
	//if (!baseAddr)
	//{
	//	return;
	//}
	//Cosmetics_Color_ApplyColor(baseAddr, 6, 0);
	//return;




	//HoboBreak();

	//if (Config.Multiplayer.enable)
	//{
	//	return;
	//}
	//auto count = System_Actor_GetActorCount();
	//for (uint8 actor = ACTOR_TWO; actor < count; actor++)
	//{
	//	auto & baseAddr = System_Actor_actorBaseAddr[actor];
	//	if (!baseAddr)
	//	{
	//		continue;
	//	}
	//	auto & isDoppelganger = *(bool *)(baseAddr + 0x11C) = true;
	//	auto & shadow = *(uint8 *)(baseAddr + 0x3A18) = 0;
	//}
}

#pragma endregion

#pragma region Arcade



#pragma endregion








































#pragma endregion

#pragma region Game Events


// @Todo: Private and debug.

//static void DevilForm_Activate(byte8 * baseAddr)
//{
//	LogFunction(baseAddr);
//	auto actor = System_Actor_GetActorId(baseAddr);
//	auto & doppelganger = *(bool *)(baseAddr + 0x6362);
//	//if (actor != ACTOR_ONE)
//	//{
//	//	return;
//	//}
//	//if (doppelganger)
//	//{
//	//	return;
//	//}
//	System_Actor_UpdateFlux(baseAddr, DEVIL_FLUX_START);
//}

//static void DevilForm_Deactivate(byte * baseAddr)
//{
//	LogFunction(baseAddr);
//	auto actor = System_Actor_GetActorId(baseAddr);
//	auto & doppelganger = *(bool *)(baseAddr + 0x6362);
//	//if (actor != ACTOR_ONE)
//	//{
//	//	return;
//	//}
//	//if (doppelganger)
//	//{
//	//	return;
//	//}
//	System_Actor_UpdateFlux(baseAddr, DEVIL_FLUX_END);
//}















// @Todo: Update with ternary operator.

inline void Doppelganger_ToggleForceActorUpdate(bool enable)
{
	LogFunction(enable);
	if (enable)
	{
		Write<byte8>((appBaseAddr + 0x1F83D0), 0xEB);
	}
	else
	{
		Write<byte8>((appBaseAddr + 0x1F83D0), 0x75);
	}
}

// @Todo: Ugh, update.
// @Todo: Debug only.

//static void Doppelganger_Activate(byte * baseAddr)
//{
//	Log("%s %llX", FUNC_NAME, baseAddr);
//
//	uint8 actor = System_Actor_GetActorId(baseAddr);
//	if (actor != ACTOR_ONE)
//	{
//		return;
//	}
//
//
//	Doppelganger_ToggleForceActorUpdate(true);
//
//
//	auto & noColor = Config.Cosmetics.Doppelganger.noColor;
//	auto & baseAddr1 = System_Actor_actorBaseAddr[ACTOR_ONE];
//	auto & baseAddr2 = System_Actor_actorBaseAddr[ACTOR_TWO];
//	if (!baseAddr1 || !baseAddr2)
//	{
//		return;
//	}
//	auto & shadow1 = *(uint32 *)(baseAddr1 + 0x3A18) = (noColor) ? 1 : 0;
//	auto & shadow2 = *(uint32 *)(baseAddr2 + 0x3A18) = (noColor) ? 1 : 0;
//
//
//
//
//
//
//
//
//
//
//
//	//if (!Config.Doppelganger.enableDevilTrigger)
//	//{
//	//	System_Actor_UpdateFlux(baseAddr, DEVIL_FLUX_END);
//	//	return;
//	//}
//	bool devil = *(bool *)(baseAddr + 0x3E9B);
//	//if (devil)
//	//{
//	//	System_Actor_UpdateFlux(baseAddr, DEVIL_FLUX_END);
//	//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//	//uint8 & shadow = *(uint8 *)(actorBaseAddr[ACTOR_TWO] + 0x3A18) = 0;
//
//	*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E6C) = *(uint32 *)(baseAddr + 0x3E6C);
//	*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E70) = *(uint32 *)(baseAddr + 0x3E70);
//	*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E88) = *(uint32 *)(baseAddr + 0x3E88);
//	*(bool   *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E9B) = *(bool   *)(baseAddr + 0x3E9B);
//	uint8 character = *(uint8 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x78);
//	//if (character == CHAR_BOB)
//	//{
//	//	if (devil)
//	//	{
//	//		*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E6C) = DEVIL_BOB_YAMATO;
//	//		*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E70) = DEVIL_BOB_YAMATO;
//	//		*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E88) = DEVIL_BOB_YAMATO;
//	//	}
//	//	else
//	//	{
//	//		*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E6C) = 0;
//	//		*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E70) = 0;
//	//		*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E88) = 0;
//	//	}
//	//}
//	if (character == CHAR_LADY)
//	{
//		*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E6C) = 0;
//		*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E70) = 0;
//		*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E88) = 0;
//		*(bool   *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E9B) = false;
//	}
//	else if (character == CHAR_VERGIL)
//	{
//		uint8 devilForm[] =
//		{
//			DEVIL_VERGIL_YAMATO,
//			DEVIL_VERGIL_BEOWULF,
//			//DEVIL_VERGIL_FORCE_EDGE,
//		};
//		uint8 selectedWeapon = *(uint8 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x6488);
//		if (selectedWeapon > 1)
//		{
//			selectedWeapon = 0;
//		}
//		if (devil)
//		{
//			*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E6C) = devilForm[selectedWeapon];
//			*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E70) = devilForm[selectedWeapon];
//			*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E88) = devilForm[selectedWeapon];
//		}
//		else
//		{
//			*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E6C) = 0;
//			*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E70) = 0;
//			*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E88) = 0;
//		}
//	}
//	if (character != CHAR_LADY)
//	{
//		//System_Actor_UpdateDevilForm(System_Actor_actorBaseAddr[ACTOR_TWO]);
//	}
//}

//static void Doppelganger_Deactivate(byte * baseAddr)
//{
//	Log("%s %llX", FUNC_NAME, baseAddr);
//
//	uint8 actor = System_Actor_GetActorId(baseAddr);
//	if (actor != ACTOR_ONE)
//	{
//		return;
//	}
//
//	Doppelganger_ToggleForceActorUpdate(false);
//
//	if (!Config.Doppelganger.enableDevilTrigger)
//	{
//		*(uint32 *)(baseAddr + 0x3E6C) = 0;
//		*(uint32 *)(baseAddr + 0x3E70) = 0;
//		*(uint32 *)(baseAddr + 0x3E88) = 0;
//		System_Actor_UpdateDevilForm(baseAddr);
//		System_Actor_UpdateFlux(baseAddr, DEVIL_FLUX_END);
//		System_Actor_Relax(baseAddr);
//		return;
//	}
//	bool devil = *(bool *)(baseAddr + 0x3E9B);
//	if (devil)
//	{
//		System_Actor_UpdateFlux(baseAddr, DEVIL_FLUX_START);
//	}
//	*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E6C) = 0;
//	*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E70) = 0;
//	*(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E88) = 0;
//	*(bool   *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x3E9B) = false;
//}









#pragma endregion





#pragma endregion










//const char * BossRush_SetTrack(const char * path)
//{
//	//LogFunctionStart();
//
//	//VARS vars = {};
//	//if (!vars.init)
//	//{
//	//	return 0;
//	//}
//	//uint32 & room         = *vars.room;
//	//uint32 & position     = *vars.position;
//	//uint16 & nextRoom     = *vars.nextRoom;
//	//uint16 & nextPosition = *vars.nextPosition;
//	//byte32 * flags        = vars.flags;
//	//uint32 & mission      = *vars.mission;
//
//	//switch (mission)
//	//{
//	//case 5:
//	//	if (_stricmp(path, "afs/sound/Battle_03.adx") == 0)
//	//	{
//	//		mediaError = MEDIA_SKIP_TRACK;
//	//		return 0;
//	//	}
//	//	if (nextRoom == ROOM_AGNI_RUDRA)
//	//	{
//	//		if (_stricmp(path, TRACK_JESTER_1) == 0)
//	//		{
//	//			mediaError = MEDIA_SKIP_TRACK;
//	//			return 0;
//	//		}
//	//	}
//	//	break;
//	//case 12:
//	//	if (nextRoom == ROOM_GERYON)
//	//	{
//	//		if (_stricmp(path, TRACK_JESTER_2) == 0)
//	//		{
//	//			mediaError = MEDIA_SKIP_TRACK;
//	//			return 0;
//	//		}
//	//	}
//	//	break;
//	//case 17:
//	//	if (nextRoom == ROOM_DOPPELGANGER)
//	//	{
//	//		if (_stricmp(path, TRACK_JESTER_3) == 0)
//	//		{
//	//			mediaError = MEDIA_SKIP_TRACK;
//	//			return 0;
//	//		}
//	//	}
//	//	break;
//	//}
//
//	//LogFunctionEnd();
//
//	return 0;
//}









































//
//void Main()
//{
//	LogFunction();
//}
//
//void Teleport()
//{
//	LogFunction();
//}
//
//void EnterCustomizeMenu()
//{
//	if constexpr (debug)
//	{
//		LogFunction();
//	}
//}
//
//void LeaveCustomizeMenu();


// EnterCustomizeMenuFromMain
// EnterMainFromCustomizeMenu

// EnterPauseMenuFromMain
// EnterMainFromPauseMenu

// PauseMenuMain
// MainPauseMenu


// CustomizeMain
// CustomizeMenuMain

// MainCustomizeMenu
// MissionStartCustomizeMenu


// MissionStart_EnterCustomizeMenu
// MissionStart_LeaveCustomizeMenu

// Main_EnterPauseMenu
// Main_LeavePauseMenu

// PauseMenu_EnterMain
// PauseMenu_EnterMissionSelectMenu


// MissionStart_CustomizeMenu
// CustomizeMenu_MissionStart

// Main_CustomizeMenu
// Main_PauseMenu

// PauseMenu_












/*
dmc3.exe+23C779 - E8 A220FAFF           - call dmc3.exe+1DE820 Main
dmc3.exe+2134DE - E8 3DB3FCFF           - call dmc3.exe+1DE820 Doppelganger
dmc3.exe+211E83 - E8 98C9FCFF           - call dmc3.exe+1DE820 Bob













dmc3.exe+1BB02D - 48 8B 05 F45DAD00     - mov rax,[dmc3.exe+C90E28] { (01A44800) }
dmc3.exe+1BB034 - 33 F6                 - xor esi,esi
dmc3.exe+1BB036 - 0FB6 8D 88000000      - movzx ecx,byte ptr [rbp+00000088]
dmc3.exe+1BB03D - 8B FE                 - mov edi,esi
dmc3.exe+1BB03F - C7 44 24 6C 0000803F  - mov [rsp+6C],3F800000 { (0) }
dmc3.exe+1BB047 - 48 8B 4C C8 18        - mov rcx,[rax+rcx*8+18]




*/


//bool spawnActors = false;



//extern bool MainLoop_run;



//PrivateStart;



//export bool MainLoop_run = false;













// @Audit: Not sure if this shouldn't be part of Media.cpp.
//{
//	byte sect0[] =
//	{
//		0x48, 0x89, 0x5C, 0x24, 0x08, //mov [rsp+08],rbx
//	};
//	byte sect2[] =
//	{
//		0x48, 0x85, 0xC0,                                           //test rax,rax
//		0x74, 0x03,                                                 //je short
//		0x48, 0x8B, 0xD0,                                           //mov rdx,rax
//		0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rax,&mediaError
//		0x8B, 0x00,                                                 //mov eax,[rax]
//		0x3D, 0x00, 0x00, 0x00, 0x00,                               //cmp eax,MEDIA_SKIP_TRACK
//		0x75, 0x01,                                                 //jne short
//		0xC3,                                                       //ret
//	};
//	FUNC func = CreateFunction(SetTrack, (appBaseAddr + 0x32BA95), true, false, sizeof(sect0), 0, sizeof(sect2));
//	memcpy(func.sect0, sect0, sizeof(sect0));
//	memcpy(func.sect2, sect2, sizeof(sect2));
//	*(dword **)(func.sect2 + 0xA) = &mediaError;
//	*(dword *)(func.sect2 + 0x15) = MEDIA_SKIP_TRACK;
//	//WriteJump((appBaseAddr + 0x32BA90), func.addr);
//}









/*
dmc3.exe+23C779 - E8 A220FAFF           - call dmc3.exe+1DE820 Main
dmc3.exe+2134DE - E8 3DB3FCFF           - call dmc3.exe+1DE820 Doppelganger
dmc3.exe+211E83 - E8 98C9FCFF           - call dmc3.exe+1DE820 Bob
*/






























#pragma region System Events












#pragma endregion
#pragma region Game Events
//{
//	FUNC func = CreateFunction(DevilForm_Activate, (appBaseAddr + 0x1E78B4));
//	WriteJump((appBaseAddr + 0x1E78AF), func.addr);
//}
//{
//	FUNC func = CreateFunction(DevilForm_Deactivate, (appBaseAddr + 0x1E78EB));
//	WriteJump((appBaseAddr + 0x1E78E6), func.addr);
//}
//{
//	byte sect0[] =
//	{
//		0x50, //push rax
//	};
//	byte sect1[] =
//	{
//		0x48, 0x8B, 0xCF, //mov rcx,rdi
//	};
//	byte sect2[] =
//	{
//		0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rax,&Config.Doppelganger.enable
//		0x8A, 0x00,                                                 //mov al,[rax]
//		0x84, 0xC0,                                                 //test al,al
//		0x74, 0x06,                                                 //je short
//		0x58,                                                       //pop rax
//		0xE9, 0x00, 0x00, 0x00, 0x00,                               //jmp dmc3.exe+1E930E
//		0x58,                                                       //pop rax
//		0x80, 0xBF, 0x9B, 0x3E, 0x00, 0x00, 0x01,                   //cmp byte ptr [rdi+00003E9B],01
//		0x0F, 0x85, 0x00, 0x00, 0x00, 0x00,                         //jne dmc3.exe+1E930E
//		0xE9, 0x00, 0x00, 0x00, 0x00,                               //jmp dmc3.exe+1E92EA
//	};
//	// @Todo: Update CreateFunction. Add noReturn.
//	FUNC func = CreateFunction(Doppelganger_Activate, 0, true, false, sizeof(sect0), sizeof(sect1), sizeof(sect2));
//	memcpy(func.sect0, sect0, sizeof(sect0));
//	memcpy(func.sect1, sect1, sizeof(sect1));
//	memcpy(func.sect2, sect2, sizeof(sect2));
//	*(bool **)(func.sect2 + 2) = &Config.Doppelganger.enable;
//	WriteAddress((func.sect2 + 0x11), (appBaseAddr + 0x1E930E), 5);
//	WriteAddress((func.sect2 + 0x1E), (appBaseAddr + 0x1E930E), 6);
//	WriteAddress((func.sect2 + 0x24), (appBaseAddr + 0x1E92EA), 5);
//	WriteJump((appBaseAddr + 0x1E92E1), func.addr, 2);
//}
//{
//	byte sect0[] =
//	{
//		0x50, //push rax
//	};
//	byte sect1[] =
//	{
//		0x48, 0x8B, 0xCB, //mov rcx,rbx
//	};
//	byte sect2[] =
//	{
//		0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rax,&Config.Doppelganger.enable
//		0x8A, 0x00,                                                 //mov al,[rax]
//		0x84, 0xC0,                                                 //test al,al
//		0x74, 0x06,                                                 //je short
//		0x58,                                                       //pop rax
//		0xE9, 0x00, 0x00, 0x00, 0x00,                               //jmp dmc3.exe+1E2B63
//		0x58,                                                       //pop rax
//		0x80, 0xBB, 0x9B, 0x3E, 0x00, 0x00, 0x00,                   //cmp byte ptr [rbx+00003E9B],00
//		0x0F, 0x85, 0x00, 0x00, 0x00, 0x00,                         //jne dmc3.exe+1E2B63
//		0xE9, 0x00, 0x00, 0x00, 0x00,                               //jmp dmc3.exe+1E2B2D
//	};
//	FUNC func = CreateFunction(Doppelganger_Deactivate, 0, true, false, sizeof(sect0), sizeof(sect1), sizeof(sect2));
//	memcpy(func.sect0, sect0, sizeof(sect0));
//	memcpy(func.sect1, sect1, sizeof(sect1));
//	memcpy(func.sect2, sect2, sizeof(sect2));
//	*(bool **)(func.sect2 + 2) = &Config.Doppelganger.enable;
//	WriteAddress((func.sect2 + 0x11), (appBaseAddr + 0x1E2B63), 5);
//	WriteAddress((func.sect2 + 0x1E), (appBaseAddr + 0x1E2B63), 6);
//	WriteAddress((func.sect2 + 0x24), (appBaseAddr + 0x1E2B2D), 5);
//	WriteJump((appBaseAddr + 0x1E2B24), func.addr, 2);
//}
//CreateThread(0, 4096, Doppelganger_Watchdog, 0, 0, 0);
#pragma endregion





#endif




















#endif
