export module Scene;

import Core;

#include "../Core/Macros.h"

import Actor;
import Config;
import Global;
import Vars;



void SetScene
(
	uint8 scene,
	bool updateConfig = false
)
{
	g_scene = scene;

	if (updateConfig)
	{
		CopyMemory
		(
			&activeConfig,
			&queuedConfig,
			sizeof(Config)
		);
	}
}

void SceneMain()
{
	LogFunction();

	SetScene(SCENE_MAIN, true);

	Actor_SceneMain();
}

void SceneMissionSelect()
{
	LogFunction();

	SetScene(SCENE_MISSION_SELECT, true);

	Actor_SceneMissionSelect();
}

void SceneGame()
{
	LogFunction();

	SetScene(SCENE_GAME);
}

void SceneCutscene()
{
	LogFunction();

	SetScene(SCENE_CUTSCENE);
}

void SceneMissionStart()
{
	LogFunction();

	SetScene(SCENE_MISSION_START, true);

	Actor_SceneMissionStart();
}

void SceneMissionResult()
{
	LogFunction();

	SetScene(SCENE_MISSION_RESULT);
}

// @Todo: Update.
export void Scene_Init()
{
	LogFunction();

	{
		constexpr byte8 sect0[] =
		{
			0xC7, 0x41, 0x38, 0x02, 0x00, 0x00, 0x00, // mov [rcx+38],00000002
		};
		auto func = CreateFunction(SceneMain, (appBaseAddr + 0x24058C), true, true, sizeof(sect0));
		CopyMemory(func.sect0, sect0, sizeof(sect0));
		WriteJump((appBaseAddr + 0x240585), func.addr, 2);
		/*
		dmc3.exe+240585 - C7 41 38 02000000 - mov [rcx+38],00000002
		dmc3.exe+24058C - 33 C0             - xor eax,eax
		*/
	}

	{
		constexpr byte8 sect0[] =
		{
			0x41, 0xC7, 0x41, 0x38, 0x03, 0x00, 0x00, 0x00, // mov [r9+38],00000003
		};
		auto func = CreateFunction(SceneMissionSelect, (appBaseAddr + 0x2405F4), true, true, sizeof(sect0));
		CopyMemory(func.sect0, sect0, sizeof(sect0));
		WriteJump((appBaseAddr + 0x2405EC), func.addr, 3);
		/*
		dmc3.exe+2405EC - 41 C7 41 38 03000000 - mov [r9+38],00000003
		dmc3.exe+2405F4 - 33 C0                - xor eax,eax
		*/
	}

// @Todo: Update!

static bool run = false;

constexpr bool enable = true;

{
	auto addr     = (appBaseAddr + 0x2405A7);
	auto jumpAddr = (appBaseAddr + 0x2405AE);
	constexpr uint32 size = 7;
	/*
	dmc3.exe+2405A7 - C7 41 38 03000000 - mov [rcx+38],00000003
	dmc3.exe+2405AE - 33 C0             - xor eax,eax
	*/

	static Function func = {};

	if (!run)
	{
		backupHelper.Save(addr, size);
		func = CreateFunction(SceneMissionSelect, jumpAddr, true, true, size);
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

run = false;





	{
		constexpr byte8 sect0[] =
		{
			0xC7, 0x41, 0x38, 0x05, 0x00, 0x00, 0x00, // mov [rcx+38],00000005
		};
		auto func = CreateFunction(SceneGame, (appBaseAddr + 0x2404B5), true, true, sizeof(sect0));
		CopyMemory(func.sect0, sect0, sizeof(sect0));
		WriteJump((appBaseAddr + 0x2404AE), func.addr, 2);
		/*
		dmc3.exe+2404AE - C7 41 38 05000000 - mov [rcx+38],00000005
		dmc3.exe+2404B5 - 33 C0             - xor eax,eax
		*/
	}

	{
		constexpr byte8 sect0[] =
		{
			0xB8, 0x06, 0x00, 0x00, 0x00, // mov eax,00000006
		};
		auto func = CreateFunction(SceneCutscene, (appBaseAddr + 0x23A590), true, true, sizeof(sect0));
		CopyMemory(func.sect0, sect0, sizeof(sect0));
		WriteJump((appBaseAddr + 0x23A58B), func.addr);
		/*
		dmc3.exe+23A58B - B8 06000000 - mov eax,00000006
		dmc3.exe+23A590 - 89 43 50    - mov [rbx+50],eax
		*/
	}

	{
		constexpr byte8 sect0[] =
		{
			0xC7, 0x41, 0x38, 0x06, 0x00, 0x00, 0x00, // mov [rcx+38],00000006
		};
		auto func = CreateFunction(SceneCutscene, (appBaseAddr + 0x2404E1), true, true, sizeof(sect0));
		CopyMemory(func.sect0, sect0, sizeof(sect0));
		WriteJump((appBaseAddr + 0x2404DA), func.addr, 2);
		/*
		dmc3.exe+2404DA - C7 41 38 06000000 - mov [rcx+38],00000006
		dmc3.exe+2404E1 - 33 C0             - xor eax,eax
		*/
	}

	{
		constexpr byte8 sect0[] =
		{
			0xC7, 0x43, 0x50, 0x07, 0x00, 0x00, 0x00, // mov [rbx+50],00000007
		};
		auto func = CreateFunction(SceneMissionStart, (appBaseAddr + 0x23A57C), true, true, sizeof(sect0));
		CopyMemory(func.sect0, sect0, sizeof(sect0));
		WriteJump((appBaseAddr + 0x23A575), func.addr, 2);
		/*
		dmc3.exe+23A575 - C7 43 50 07000000 - mov [rbx+50],00000007
		dmc3.exe+23A57C - C6 05 8E90A600 00 - mov byte ptr [dmc3.exe+CA3611],00
		*/
	}

	{
		constexpr byte8 sect0[] =
		{
			0xC7, 0x41, 0x38, 0x07, 0x00, 0x00, 0x00, // mov [rcx+38],00000007
		};
		auto func = CreateFunction(SceneMissionStart, (appBaseAddr + 0x2404EB), true, true, sizeof(sect0));
		CopyMemory(func.sect0, sect0, sizeof(sect0));
		WriteJump((appBaseAddr + 0x2404E4), func.addr, 2);
		/*
		dmc3.exe+2404E4 - C7 41 38 07000000 - mov [rcx+38],00000007
		dmc3.exe+2404EB - 33 C0             - xor eax,eax
		*/
	}

	{
		constexpr byte8 sect0[] =
		{
			0xC7, 0x41, 0x38, 0x08, 0x00, 0x00, 0x00, // mov [rcx+38],00000008
		};
		auto func = CreateFunction(SceneMissionResult, (appBaseAddr + 0x24048F), true, true, sizeof(sect0));
		CopyMemory(func.sect0, sect0, sizeof(sect0));
		WriteJump((appBaseAddr + 0x240488), func.addr, 2);
		/*
		dmc3.exe+240488 - C7 41 38 08000000 - mov [rcx+38],00000008
		dmc3.exe+24048F - 33 C0             - xor eax,eax
		*/
	}
}

#ifdef __GARBAGE__
#endif
