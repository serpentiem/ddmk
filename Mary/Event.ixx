module;

#include "../Core/Macros.h" //

// #include "../Core/Core.h"

// #include "Vars.h"
export module Event;

import Core;


import Vars;

#define memset SetMemory
#define memcpy CopyMemory

import Actor;
import Arcade;
import BossRush;
import Config;
import Enemy;
import File;
import Global;
import Item;
import Model;
import Sound;

#define debug false

bool Event_run[MAX_EVENT] = {};
bool MainLoopOnce_run     = false;
bool MainLoopOnceSync_run = false;
bool ActorLoopOnce_run    = false;

























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
	//Actor_SetNextRoom();
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



void CreateMainActor(byte8 * actorBaseAddr)
{
	memset(Event_run, 0, MAX_EVENT);

	MainLoopOnce_run     = false;
	MainLoopOnceSync_run = false;
	ActorLoopOnce_run    = false;

	Actor_CreateMainActor(actorBaseAddr);

	Arcade_CreateMainActor(actorBaseAddr);

	Enemy_CreateMainActor(actorBaseAddr);
}

void Main_CreateMainActor(byte8 * actorBaseAddr)
{
	LogFunction(actorBaseAddr);

	return CreateMainActor(actorBaseAddr);
}

void Customize_CreateMainActor(byte8 * actorBaseAddr)
{
	LogFunction(actorBaseAddr);

	return CreateMainActor(actorBaseAddr);
}



void CreateCloneActor(byte8 * actorBaseAddr)
{
	Actor_CreateCloneActor(actorBaseAddr);
}

void Main_CreateCloneActor(byte8 * actorBaseAddr)
{
	LogFunction(actorBaseAddr);

	return CreateCloneActor(actorBaseAddr);
}

void UpdateActorDante_CreateCloneActor(byte8 * actorBaseAddr)
{
	LogFunction(actorBaseAddr);

	return CreateCloneActor(actorBaseAddr);
}


// @Todo: Remove bool.
// @Todo: Update names.
bool EventOnce(EventData & eventData)
{
	auto event = eventData.event;
	if (event >= MAX_EVENT)
	{
		return false;
	}

	auto & run = Event_run[event];
	if (run)
	{
		return false;
	}

	run = true;

	switch (eventData.event)
	{
		case EVENT_MAIN:
		{
			Log("Main");
			//Actor_Main();
			BossRush_Main();

			Sound::EventMain();



			break;
		}
		case EVENT_TELEPORT:
		{
			Log("Teleport");

			break;
		}
		case EVENT_DEATH:
		{
			Log("Death");

			break;
		}
		case EVENT_CUSTOMIZE:
		{
			Log("Customize");

			// @Todo: Remove.
			Actor_Customize();

			break;
		}
		case EVENT_DELETE:
		{
			Log("Delete %u", eventData.subevent);

			Actor_Delete();
			Enemy_Delete();
			Sound::EventDelete();

			Item::EventDelete();


			// g_showItemWindow     = false;
			// g_lastShowItemWindow = false;

			break;
		}
	}

	return false;
}

void EventLoop(EventData & eventData)
{

	switch (eventData.event)
	{
		case EVENT_MAIN:
		{
			Enemy_Main();

			break;
		}
	}





	//return;
}

void EventHandler(EventData & eventData)
{
	EventOnce(eventData);
	EventLoop(eventData);

	// if ()
	// {
	// 	return;
	// }
}




// @Todo: Move to Camera.

float cameraTimeout = 0;

void UpdateCamera()
{

	if (cameraTimeout > 0)
	{
		cameraTimeout -= 10.0f;
	}
	else if (cameraTimeout < 0)
	{
		cameraTimeout = 0;
	}

	if (cameraTimeout > 0)
	{
		return;
	}

	if (!activeConfig.Camera.applyConfig)
	{
		return;
	}

	IntroduceCameraData(return);

	cameraData.height         = activeConfig.Camera.height;
	cameraData.tilt           = activeConfig.Camera.tilt;
	cameraData.distance       = activeConfig.Camera.distance;
	cameraData.distanceLockOn = activeConfig.Camera.distanceLockOn;

	cameraTimeout = 500.0f; // @Todo: Include frame rate.
}









void MainLoopOnce()
{
	if (!MainLoopOnce_run)
	{
		MainLoopOnce_run = true;

		LogFunction();

		Actor_MainLoopOnce();
		Enemy_MainLoopOnce();
	}
}

void MainLoopOnceSync()
{
	if (InCutscene())
	{
		return;
	}

	if (!MainLoopOnceSync_run)
	{
		MainLoopOnceSync_run = true;

		LogFunction();

		//Actor_MainLoopOnceSync();
	}
}

void MainLoop()
{
	MainLoopOnce();

	MainLoopOnceSync();

	UpdateCamera();

	CharacterSwitchController();
}














// void ActorLoopOnce(byte8 * actorBaseAddr)
// {
// 	if (!ActorLoopOnce_run)
// 	{
// 		ActorLoopOnce_run = true;

// 		LogFunction(actorBaseAddr);

// 		Actor_ActorLoopOnce(actorBaseAddr);
// 	}
// }

void ActorLoop(byte8 * actorBaseAddr)
{
	// ActorLoopOnce(actorBaseAddr);

	Actor_ActorLoop(actorBaseAddr);
}



void InGameCutsceneStart()
{
	LogFunction();

	Actor_InGameCutsceneStart();
}

void InGameCutsceneEnd()
{
	LogFunction();

	Actor_InGameCutsceneEnd();
}





void EventContinue()
{
	LogFunction();

	Actor_EventContinue();
}














void UpdateEnemyCount(byte8 * addr)
{
	if (!addr)
	{
		return;
	}

	auto & count = *reinterpret_cast<uint32 *>(addr + 0x28);

	Log("%s %u", FUNC_NAME, count);

	Sound::UpdateEnemyCount(addr);
}





















void TriggerCustomizeMenu()
{
	LogFunction();

	Item::EventTriggerCustomizeMenu();
}

// void TriggerRestartMission(EventData & eventData)
// {
// 	LogFunction();

// 	Actor_TriggerRestartMission(eventData);

// 	if (!g_pauseForceQuitMission)
// 	{
// 		return;
// 	}

// 	g_pauseForceQuitMission = false;

// 	eventData.nextScreen = SCREEN_MISSION_SELECT;


// 	//auto & index = *reinterpret_cast<uint32 *>(addr + 0xCC) = 2;
// }




void SetNextScreen(EventData & eventData)
{
	Log("%s %u", FUNC_NAME, eventData.nextScreen);

	Actor_SetNextScreen(eventData);
}










void MissionSelectCheckConfirm(byte8 * addr)
{
	if (!g_missionSelectForceConfirm)
	{
		return;
	}

	g_missionSelectForceConfirm = false;

	auto & var_8 = *reinterpret_cast<uint8 *>(addr + 8) = 9;
	auto & var_6280 = *reinterpret_cast<uint32 *>(addr + 0x6280) = 1;

	/*
	dmc3.exe+29A200 - 80 79 08 09    - cmp byte ptr [rcx+08],09
	dmc3.exe+29A209 - 8B 81 80620000 - mov eax,[rcx+00006280]
	*/
}







export void Event_Toggle(bool enable)
{
	LogFunction(enable);

	static bool run = false;

	// Update Enemy Count
	{
		auto addr     = (appBaseAddr + 0x1A5348);
		auto jumpAddr = (appBaseAddr + 0x1A534F);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1A5348 - 89 73 28    - mov [rbx+28],esi
		dmc3.exe+1A534B - 66 89 73 25 - mov [rbx+25],si
		dmc3.exe+1A534F - C6 43 24 01 - mov byte ptr [rbx+24],01
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(UpdateEnemyCount, jumpAddr, true, true, size, sizeof(sect1));
			CopyMemory(func.sect0, addr, size, MemoryFlags_VirtualProtectSource);
			CopyMemory(func.sect1, sect1, sizeof(sect1));
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
		auto addr     = (appBaseAddr + 0x1A4F82);
		auto jumpAddr = (appBaseAddr + 0x1A4F8A);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+1A4F82 - 41 FF 42 28       - inc [r10+28]
		dmc3.exe+1A4F86 - 44 8B 4A 78       - mov r9d,[rdx+78]
		dmc3.exe+1A4F8A - 48 8B 05 97BEAE00 - mov rax,[dmc3.exe+C90E28]
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_r10,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(UpdateEnemyCount, jumpAddr, true, true, size, sizeof(sect1));
			CopyMemory(func.sect0, addr, size, MemoryFlags_VirtualProtectSource);
			CopyMemory(func.sect1, sect1, sizeof(sect1));
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
		auto addr     = (appBaseAddr + 0x1A4FED);
		auto jumpAddr = (appBaseAddr + 0x1A4FF4);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1A4FED - FF 4B 28    - dec [rbx+28]
		dmc3.exe+1A4FF0 - 83 7F 78 1B - cmp dword ptr [rdi+78],1B
		dmc3.exe+1A4FF4 - 75 03       - jne dmc3.exe+1A4FF9
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(UpdateEnemyCount, jumpAddr, true, true, size, sizeof(sect1));
			CopyMemory(func.sect0, addr, size, MemoryFlags_VirtualProtectSource);
			CopyMemory(func.sect1, sect1, sizeof(sect1));
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

	// Trigger Customize Menu
	{
		auto addr     = (appBaseAddr + 0x1A9609);
		auto jumpAddr = (appBaseAddr + 0x1A9610);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1A9609 - 48 8B 8B B00A0000 - mov rcx,[rbx+00000AB0]
		dmc3.exe+1A9610 - 33 D2             - xor edx,edx
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(TriggerCustomizeMenu, jumpAddr, true, true, size);
			CopyMemory(func.sect0, addr, size, MemoryFlags_VirtualProtectSource);
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

	// // Trigger Restart Mission
	// {
	// 	auto addr     = (appBaseAddr + 0x29FE12);
	// 	auto jumpAddr = (appBaseAddr + 0x29FE17);
	// 	constexpr uint32 size = 5;
	// 	/*
	// 	dmc3.exe+29FE12 - E8 A9930900 - call dmc3.exe+3391C0
	// 	dmc3.exe+29FE17 - FE 45 09    - inc byte ptr [rbp+09]
	// 	*/

	// 	static Function func = {};

	// 	constexpr byte8 sect0[] =
	// 	{
	// 		mov_rcx_rbp,
	// 	};

	// 	if (!run)
	// 	{
	// 		backupHelper.Save(addr, size);
	// 		func = CreateFunction(TriggerRestartMission, jumpAddr, true, true, (size + sizeof(sect0)));
	// 		CopyMemory((func.sect0 + size), sect0, sizeof(sect0));
	// 		WriteCall(func.sect0, (appBaseAddr + 0x3391C0));
	// 	}

	// 	if (enable)
	// 	{
	// 		WriteJump(addr, func.addr, (size - 5));
	// 	}
	// 	else
	// 	{
	// 		backupHelper.Restore(addr);
	// 	}
	// }

	// Mission Select Check Confirm
	{
		auto addr     = (appBaseAddr + 0x1BDDD4);
		auto jumpAddr = (appBaseAddr + 0x1BDDD9);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+1BDDD4 - E8 27C40D00 - call dmc3.exe+29A200
		dmc3.exe+1BDDD9 - 89 43 44    - mov [rbx+44],eax
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(MissionSelectCheckConfirm, jumpAddr, true, true, 0, 0, size);
			WriteCall(func.sect2, (appBaseAddr + 0x29A200));
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








	// Pause Restart Mission
	{
		auto addr     = (appBaseAddr + 0x23D80E);
		auto jumpAddr = (appBaseAddr + 0x23D815);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+23D80E - C7 43 2C 07000000 - mov [rbx+2C],00000007
		dmc3.exe+23D815 - EB B2             - jmp dmc3.exe+23D7C9
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(SetNextScreen, jumpAddr, true, true, size, sizeof(sect1));
			CopyMemory(func.sect0, addr, size, MemoryFlags_VirtualProtectSource);
			CopyMemory(func.sect1, sect1, sizeof(sect1));
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

	// Continue Restart Mission
	{
		auto addr     = (appBaseAddr + 0x23BD5D);
		auto jumpAddr = (appBaseAddr + 0x23BD64);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+23BD5D - C7 43 2C 07000000 - mov [rbx+2C],00000007
		dmc3.exe+23BD64 - EB 99             - jmp dmc3.exe+23BCFF
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(SetNextScreen, jumpAddr, true, true, size, sizeof(sect1));
			CopyMemory(func.sect0, addr, size, MemoryFlags_VirtualProtectSource);
			CopyMemory(func.sect1, sect1, sizeof(sect1));
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

export void Event_Init()
{
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












	// Set Next Room
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
		auto func = CreateFunction(SetNextRoom, (appBaseAddr + 0x1A6114), true, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteJump((appBaseAddr + 0x1A610D), func.addr, 2);
		/*
		dmc3.exe+1A610D - 66 89 81 66010000 - mov [rcx+00000166],ax
		dmc3.exe+1A6114 - 89 A9 60010000    - mov [rcx+00000160],ebp
		*/
	}
	{
		constexpr byte8 sect0[] =
		{
			0x66, 0x89, 0x8E, 0x66, 0x01, 0x00, 0x00, // mov [rsi+00000166],cx
		};
		constexpr byte8 sect1[] =
		{
			mov_rcx_rsi,
		};
		auto func = CreateFunction(SetNextRoom, (appBaseAddr + 0x1A6687), true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteJump((appBaseAddr + 0x1A6680), func.addr, 2);
		/*
		dmc3.exe+1A6680 - 66 89 8E 66010000 - mov [rsi+00000166],cx
		dmc3.exe+1A6687 - 40 38 BE C6000000 - cmp [rsi+000000C6],dil
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

	// Create Main Actor
	{
		constexpr byte8 sect0[] =
		{
			0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc3.exe+1DE820
		};
		constexpr byte8 sect1[] =
		{
			mov_rcx_rax,
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
			mov_rcx_rax,
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

	// Create Clone Actor
	{
		constexpr byte8 sect0[] =
		{
			0xE8, 0x00, 0x00, 0x00, 0x00, // call dmc3.exe+1DE820
		};
		constexpr byte8 sect1[] =
		{
			mov_rcx_rax,
		};
		auto func = CreateFunction(Main_CreateCloneActor, (appBaseAddr + 0x211E88), true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteCall(func.sect0, (appBaseAddr + 0x1DE820));
		WriteJump((appBaseAddr + 0x211E83), func.addr);
		/*
		dmc3.exe+211E83 - E8 98C9FCFF       - call dmc3.exe+1DE820
		dmc3.exe+211E88 - 48 89 83 78640000 - mov [rbx+00006478],rax
		*/
	}
	{
		constexpr byte8 sect0[] =
		{
			0xE8, 0x00, 0x00, 0x00, 0x00, // call dmc3.exe+1DE820
		};
		constexpr byte8 sect1[] =
		{
			mov_rcx_rax,
		};
		auto func = CreateFunction(UpdateActorDante_CreateCloneActor, (appBaseAddr + 0x2134E3), true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteCall(func.sect0, (appBaseAddr + 0x1DE820));
		WriteJump((appBaseAddr + 0x2134DE), func.addr);
		/*
		dmc3.exe+2134DE - E8 3DB3FCFF       - call dmc3.exe+1DE820
		dmc3.exe+2134E3 - 48 89 86 78640000 - mov [rsi+00006478],rax
		*/
	}






















	// Event Handler
	{
		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};
		constexpr byte8 sect2[] =
		{
			0x48, 0x03, 0xCA, // add rcx,rdx
			0xFF, 0xE1,       // jmp rcx
		};
		auto func = CreateFunction(EventHandler, 0, true, true, 0, sizeof(sect1), sizeof(sect2));
		memcpy(func.sect1, sect1, sizeof(sect1));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteJump((appBaseAddr + 0x23B41F), func.addr);
		/*
		dmc3.exe+23B41F - 48 03 CA - add rcx,rdx
		dmc3.exe+23B422 - FF E1    - jmp rcx
		*/
	}




	// Loops





	{
		constexpr byte8 sect0[] =
		{
			0xE8, 0x00, 0x00, 0x00, 0x00, // call dmc3.exe+23D230
		};
		auto func = CreateFunction(MainLoop, (appBaseAddr + 0x23B43C), true, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteCall(func.sect0, (appBaseAddr + 0x23D230));
		WriteJump((appBaseAddr + 0x23B437), func.addr);
		/*
		dmc3.exe+23B437 - E8 F41D0000 - call dmc3.exe+23D230
		dmc3.exe+23B43C - 33 C0       - xor eax,eax
		*/
	}










	// {
	// 	constexpr byte8 sect0[] =
	// 	{
	// 		0xE8, 0x00, 0x00, 0x00, 0x00, // call dmc3.exe+23B060
	// 	};
	// 	auto func = CreateFunction(MainLoop, (appBaseAddr + 0x23D4B7), true, true, sizeof(sect0));
	// 	memcpy(func.sect0, sect0, sizeof(sect0));
	// 	WriteCall(func.sect0, (appBaseAddr + 0x23B060));
	// 	WriteJump((appBaseAddr + 0x23D4B2), func.addr);
	// 	/*
	// 	dmc3.exe+23D4B2 - E8 A9DBFFFF - call dmc3.exe+23B060
	// 	dmc3.exe+23D4B7 - 84 C0       - test al,al
	// 	*/
	// }
	{
		constexpr byte8 sect0[] =
		{
			0xE8, 0x00, 0x00, 0x00, 0x00, // call dmc3.exe+1F83A0
		};
		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};
		auto func = CreateFunction(ActorLoop, (appBaseAddr + 0x1DFA9B), true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteCall(func.sect0, (appBaseAddr + 0x1F83A0));
		WriteJump((appBaseAddr + 0x1DFA96), func.addr);
		/*
		dmc3.exe+1DFA96 - E8 05890100 - call dmc3.exe+1F83A0
		dmc3.exe+1DFA9B - EB 08       - jmp dmc3.exe+1DFAA5
		*/
	}

	// In-Game Cutscenes
	{
		constexpr byte8 sect0[] =
		{
			0xC6, 0x05, 0x00, 0x00, 0x00, 0x00, 0x01, // mov byte ptr [dmc3.exe+5D113D],01
		};
		auto func = CreateFunction(InGameCutsceneStart, (appBaseAddr + 0x23DD73), true, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteAddress(func.sect0, (appBaseAddr + 0x5D113D), 7, 0, 0, 0, 1);
		WriteJump((appBaseAddr + 0x23DD6C), func.addr, 2);
		/*
		dmc3.exe+23DD6C - C6 05 CA333900 01 - mov byte ptr [dmc3.exe+5D113D],01
		dmc3.exe+23DD73 - E8 988B0E00       - call dmc3.exe+326910
		*/
	}
	{
		constexpr byte8 sect0[] =
		{
			0xC6, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, // mov byte ptr [dmc3.exe+5D113D],00
		};
		auto func = CreateFunction(InGameCutsceneEnd, (appBaseAddr + 0x23DEAA), true, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteAddress(func.sect0, (appBaseAddr + 0x5D113D), 7, 0, 0, 0, 1);
		WriteJump((appBaseAddr + 0x23DEA3), func.addr, 2);
		/*
		dmc3.exe+23DEA3 - C6 05 93323900 00       - mov byte ptr [dmc3.exe+5D113D],00
		dmc3.exe+23DEAA - C7 05 ECAAA700 00000000 - mov [dmc3.exe+CB89A0],00000000
		*/
	}

	// Continue
	{
		auto func = CreateFunction(EventContinue, (appBaseAddr + 0x23BD66));
		WriteAddress((appBaseAddr + 0x23BCA0), func.addr, 6);
		/*
		dmc3.exe+23BCA0 - 0F84 C0000000 - je dmc3.exe+23BD66
		dmc3.exe+23BCA6 - 83 E8 01      - sub eax,01
		*/
	}
}





#ifdef __GARBAGE__









	// {
	// 	constexpr byte8 sect0[] =
	// 	{
	// 		0x40, 0x88, 0xB7, 0x9B, 0x3E, 0x00, 0x00, // mov [rdi+00003E9B],sil
	// 	};
	// 	constexpr byte8 sect1[] =
	// 	{
	// 		mov_rcx_rdi,
	// 	};
	// 	auto func = CreateFunction(DeactivateDevilForm, (appBaseAddr + 0x1E78C6), true, true, sizeof(sect0), sizeof(sect1));
	// 	memcpy(func.sect0, sect0, sizeof(sect0));
	// 	memcpy(func.sect1, sect1, sizeof(sect1));
	// 	WriteJump((appBaseAddr + 0x1E78BF), func.addr, 2);
	// 	/*
	// 	dmc3.exe+1E78BF - 40 88 B7 9B3E0000 - mov [rdi+00003E9B],sil
	// 	dmc3.exe+1E78C6 - 48 8B CF          - mov rcx,rdi
	// 	*/
	// }













// void SkyStarReset(byte8 * baseAddr)
// {
// 	Mobility::SkyStarReset(baseAddr);
// }



// void DeactivateDevilForm(byte8 * baseAddr)
// {
// 	if (!baseAddr)
// 	{
// 		return;
// 	}

// 	Actor_DeactivateDevilForm(baseAddr);
// }

	// {
	// 	constexpr byte8 sect0[] =
	// 	{
	// 		0x48, 0x89, 0x15, 0x00, 0x00, 0x00, 0x00, //mov [dmc3.exe+C90E28],rdx
	// 	};
	// 	auto func = CreateFunction(SetPool, (appBaseAddr + 0x23E69F), true, true, sizeof(sect0));
	// 	memcpy(func.sect0, sect0, sizeof(sect0));
	// 	WriteAddress(func.sect0, (appBaseAddr + 0xC90E28), 7);
	// 	WriteJump((appBaseAddr + 0x23E698), func.addr, 2);
	// 	/*
	// 	dmc3.exe+23E698 - 48 89 15 8927A500 - mov [dmc3.exe+C90E28],rdx
	// 	dmc3.exe+23E69F - 48 8D 83 D06A0000 - lea rax,[rbx+00006AD0]
	// 	*/
	// }
	// {
	// 	constexpr byte8 sect0[] =
	// 	{
	// 		0x48, 0x89, 0x0D, 0x00, 0x00, 0x00, 0x00, //mov [dmc3.exe+C90E28],rcx
	// 	};
	// 	auto func = CreateFunction(ClearPool, (appBaseAddr + 0x23B39A), true, true, sizeof(sect0));
	// 	memcpy(func.sect0, sect0, sizeof(sect0));
	// 	WriteAddress(func.sect0, (appBaseAddr + 0xC90E28), 7);
	// 	WriteJump((appBaseAddr + 0x23B393), func.addr, 2);
	// 	/*
	// 	dmc3.exe+23B393 - 48 89 0D 8E5AA500 - mov [dmc3.exe+C90E28],rcx
	// 	dmc3.exe+23B39A - 48 89 0D 975AA500 - mov [dmc3.exe+C90E38],rcx
	// 	*/
	// }

		/*
		dmc3.exe+1E25EB - E8 F0820000 - call dmc3.exe+1EA8E0 - Weapon Switch Controller Dante
		dmc3.exe+1F900E - E8 5D94FEFF - call dmc3.exe+1E2470 - Actor Input Handler
		dmc3.exe+1DFA96 - E8 05890100 - call dmc3.exe+1F83A0 - Actor Main Update
		*/






//bool MainLoop_run = false;











// export void LockActor(byte8 * baseAddr)
// {
// 	auto & actorData = *reinterpret_cast<ActorData *>(baseAddr);
// 	actorData.newButtonMask = 0;
// 	actorData.newEnableRightStick = false;
// 	actorData.newEnableLeftStick = false;
// }


// export void UnlockActor(byte8 * baseAddr)
// {
// 	auto & actorData = *reinterpret_cast<ActorData *>(baseAddr);
// 	actorData.newButtonMask = 0xFFFF;
// 	actorData.newEnableRightStick = true;
// 	actorData.newEnableLeftStick = true;
// }










/*
void Camera_Update(CONFIG & config)
{
	// @Todo: Add to vars.
	auto addr = *(byte8 **)(appBaseAddr + 0xC8FBD0);
	if (!addr)
	{
		return;
	}
	addr = *(byte8 **)(addr + 0x498);
	if (!addr)
	{
		return;
	}
	auto & height     = *(float32 *)(addr + 0xD0) = config.Camera.height;
	auto & tilt       = *(float32 *)(addr + 0xD4) = config.Camera.tilt;
	auto & zoom       = *(float32 *)(addr + 0xD8) = config.Camera.zoom;
	auto & zoomLockOn = *(float32 *)(addr + 0xE0) = config.Camera.zoomLockOn;
}
*/

















//bool Main_run = false;
//bool Teleport_run = false;
//bool Customize_run = false;
//bool Delete_run = false;


#endif
