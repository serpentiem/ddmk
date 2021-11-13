module;

export module Speed;

import Core;

#include "../Core/Macros.h"

import Config;
import Global;
//import Input;
import Vars;

#define debug false

// // #include "Macros.h"



void SetMainSpeed()
{


















	// @Todo: Add to prep.
	auto addr = *reinterpret_cast<byte8 **>(appBaseAddr + 0xF2429C); // dmc4.exe+5E9A64 - 8B 0D 9C423201 - mov ecx,[dmc4.exe+F2429C]
	if (!addr)
	{
		return;
	}
	auto & speed = *reinterpret_cast<float *>(addr + 0x7C);



	if
	(
		(g_scene == SCENE::MAIN           ) ||
		(g_scene == SCENE::MISSION_SELECT ) ||
		(g_scene == SCENE::CUTSCENE_SELECT) ||
		(g_scene == SCENE::MISSION_START  ) ||
		(g_scene == SCENE::GAME_OVER      ) ||
		(g_scene == SCENE::MISSION_RESULT)
	)
	{
		speed = activeConfig.menuSpeed;
	}
	else if (g_scene == SCENE::CUTSCENE)
	{
		speed = activeConfig.cutsceneSpeed;
	}
	else
	{
		speed = activeConfig.mainSpeed;
	}



	// Game
	[&]()
	{
		IntroduceEventData(return);

		if (g_scene != SCENE::GAME)
		{
			return;
		}

		if
		(
			(eventData.event == EVENT::PAUSE) ||
			(eventData.event == EVENT::ITEM )
		)
		{
			speed = activeConfig.menuSpeed;
		}
		else if (eventData.event == EVENT::CUTSCENE)
		{
			speed = activeConfig.cutsceneSpeed;
		}
	}();


















}



namespaceStart(Speed);

export void Toggle(bool enable)
{
	LogFunction();

	static bool run = false;



	// Main
	{
		auto addr     = (appBaseAddr + 0x6E8621);
		auto jumpAddr = (appBaseAddr + 0x6E8626);
		constexpr size_t size = 5;
		/*
		dmc4.exe+6E8621 - F3 0F10 46 7C - movss xmm0,[esi+7C]
		dmc4.exe+6E8626 - F3 0F59 46 70 - mulss xmm0,[esi+70]
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(SetMainSpeed, jumpAddr, true, true, 0, 0, size);
			CopyMemory(func.sect2, addr, size, MemoryFlags_VirtualProtectSource);
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
