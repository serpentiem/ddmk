export module Scene;

import Core;

#include "../Core/Macros.h"

import Actor;
import Config;
import Global;
import Vars;



#pragma region Item

namespaceStart(Item);

void SceneMain()
{
	if (!activeConfig.Actor.enable)
	{
		return;
	}

	LogFunction();

	IntroduceSessionData();

	g_haywireNeoGenerator = false;
}

void SceneMissionSelect()
{
	if (!activeConfig.Actor.enable)
	{
		return;
	}

	LogFunction();

	IntroduceSessionData();

	g_haywireNeoGenerator = false;
}

void SceneMissionStart()
{
	if (!activeConfig.Actor.enable)
	{
		return;
	}

	LogFunction();

	IntroduceSessionData();

	g_haywireNeoGenerator =
	(
		(sessionData.mission == 12) &&
		!activeConfig.BossRush.enable
	) ? true : false;
}

namespaceEnd();

#pragma endregion



const char * sceneFuncNames[] =
{
	"SceneBoot",
	"SceneIntro",
	"SceneMain",
	"SceneMissionSelect",
	"SceneLoad",
	"SceneGame",
	"SceneCutscene",
	"SceneMissionStart",
	"SceneMissionResult",
	"SceneGameOver",
};

static_assert(countof(sceneFuncNames) == SCENE::COUNT);



void SceneHandler()
{
	using namespace SCENE;

	auto scene = g_scene;
	if (scene >= COUNT)
	{
		Log("__UNKNOWN_SCENE__ %u", scene);

		return;
	}

	auto funcName = sceneFuncNames[scene];



	switch (scene)
	{
		case MAIN:
		case MISSION_SELECT:
		case MISSION_START:
		{
			CopyMemory
			(
				&activeConfig,
				&queuedConfig,
				sizeof(activeConfig)
			);

			break;
		}
	}



	switch (scene)
	{
		case BOOT:
		{
			Log(funcName);

			break;
		}
		case INTRO:
		{
			Log(funcName);

			break;
		}
		case MAIN:
		{
			Log(funcName);

			Item::SceneMain();

			break;
		}
		case MISSION_SELECT:
		{
			Log(funcName);

			Item::SceneMissionSelect();

			break;
		}
		case LOAD:
		{
			Log(funcName);

			break;
		}
		case GAME:
		{
			Log(funcName);

			Actor::SceneGame();

			break;
		}
		case CUTSCENE:
		{
			Log(funcName);

			break;
		}
		case MISSION_START:
		{
			Log(funcName);

			Actor::SceneMissionStart();

			Item::SceneMissionStart();

			break;
		}
		case MISSION_RESULT:
		{
			Log(funcName);

			break;
		}
		case GAME_OVER:
		{
			Log(funcName);

			break;
		}
	}
}

template<uint8 scene>
void SetScene()
{
	g_scene = scene;

	SceneHandler();
}



namespaceStart(Scene);

export void Toggle(bool enable)
{
	LogFunction(enable);

	static bool run = false;



	{
		auto addr     = (appBaseAddr + 0x240585);
		auto jumpAddr = (appBaseAddr + 0x24058C);
		constexpr size_t size = 7;
		/*
		dmc3.exe+240585 - C7 41 38 02000000 - mov [rcx+38],00000002
		dmc3.exe+24058C - 33 C0             - xor eax,eax
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(SetScene<2>, jumpAddr, (FunctionFlags_SaveRegisters | FunctionFlags_NoResult), size);
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

	{
		auto addr     = (appBaseAddr + 0x2405EC);
		auto jumpAddr = (appBaseAddr + 0x2405F4);
		constexpr size_t size = 8;
		/*
		dmc3.exe+2405EC - 41 C7 41 38 03000000 - mov [r9+38],00000003
		dmc3.exe+2405F4 - 33 C0                - xor eax,eax
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(SetScene<3>, jumpAddr, (FunctionFlags_SaveRegisters | FunctionFlags_NoResult), size);
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

	{
		auto addr     = (appBaseAddr + 0x2405A7);
		auto jumpAddr = (appBaseAddr + 0x2405AE);
		constexpr size_t size = 7;
		/*
		dmc3.exe+2405A7 - C7 41 38 03000000 - mov [rcx+38],00000003
		dmc3.exe+2405AE - 33 C0             - xor eax,eax
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(SetScene<3>, jumpAddr, (FunctionFlags_SaveRegisters | FunctionFlags_NoResult), size);
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

	{
		auto addr     = (appBaseAddr + 0x2404AE);
		auto jumpAddr = (appBaseAddr + 0x2404B5);
		constexpr size_t size = 7;
		/*
		dmc3.exe+2404AE - C7 41 38 05000000 - mov [rcx+38],00000005
		dmc3.exe+2404B5 - 33 C0             - xor eax,eax
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(SetScene<5>, jumpAddr, (FunctionFlags_SaveRegisters | FunctionFlags_NoResult), size);
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

	{
		auto addr     = (appBaseAddr + 0x23A58B);
		auto jumpAddr = (appBaseAddr + 0x23A590);
		constexpr size_t size = 5;
		/*
		dmc3.exe+23A58B - B8 06000000 - mov eax,00000006
		dmc3.exe+23A590 - 89 43 50    - mov [rbx+50],eax
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(SetScene<6>, jumpAddr, (FunctionFlags_SaveRegisters | FunctionFlags_NoResult), size);
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

	{
		auto addr     = (appBaseAddr + 0x2404DA);
		auto jumpAddr = (appBaseAddr + 0x2404E1);
		constexpr size_t size = 7;
		/*
		dmc3.exe+2404DA - C7 41 38 06000000 - mov [rcx+38],00000006
		dmc3.exe+2404E1 - 33 C0             - xor eax,eax
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(SetScene<6>, jumpAddr, (FunctionFlags_SaveRegisters | FunctionFlags_NoResult), size);
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

	{
		auto addr     = (appBaseAddr + 0x23A575);
		auto jumpAddr = (appBaseAddr + 0x23A57C);
		constexpr size_t size = 7;
		/*
		dmc3.exe+23A575 - C7 43 50 07000000 - mov [rbx+50],00000007
		dmc3.exe+23A57C - C6 05 8E90A600 00 - mov byte ptr [dmc3.exe+CA3611],00
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(SetScene<7>, jumpAddr, (FunctionFlags_SaveRegisters | FunctionFlags_NoResult), size);
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

	{
		auto addr     = (appBaseAddr + 0x2404E4);
		auto jumpAddr = (appBaseAddr + 0x2404EB);
		constexpr size_t size = 7;
		/*
		dmc3.exe+2404E4 - C7 41 38 07000000 - mov [rcx+38],00000007
		dmc3.exe+2404EB - 33 C0             - xor eax,eax
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(SetScene<7>, jumpAddr, (FunctionFlags_SaveRegisters | FunctionFlags_NoResult), size);
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

	{
		auto addr     = (appBaseAddr + 0x240488);
		auto jumpAddr = (appBaseAddr + 0x24048F);
		constexpr size_t size = 7;
		/*
		dmc3.exe+240488 - C7 41 38 08000000 - mov [rcx+38],00000008
		dmc3.exe+24048F - 33 C0             - xor eax,eax
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(SetScene<8>, jumpAddr, (FunctionFlags_SaveRegisters | FunctionFlags_NoResult), size);
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



	run = true;
}

namespaceEnd();
