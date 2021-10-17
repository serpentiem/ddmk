export module Event;

import Core;

#include "../Core/Macros.h"

import Windows;

using namespace Windows;

import Actor;
import Arcade;
import Config;
import Global;
import Internal;
import Vars;

#define debug false



bool Event_run[EVENT::COUNT] = {};



void InitSession()
{
	LogFunction();

	Arcade::InitSession();
}

void SetCharacter()
{
	LogFunction();

	Arcade::SetCharacter();
}

void SetRoomPosition
(
	byte8 ** dataAddr,
	uint32 * positionAddr
)
{
	LogFunction();

	Arcade::SetRoomPosition
	(
		dataAddr,
		positionAddr
	);
}

bool __fastcall SpawnMainActor
(
	byte8 * manager,
	void * ignore0,
	uint8 type,
	byte8 * actorBaseAddr,
	uint32 ignore1,
	uint32 ignore2
)
{
	Log("%s %X", FUNC_NAME, actorBaseAddr);



	SetMemory
	(
		Event_run,
		0,
		sizeof(Event_run)
	);



	Actor::EventSpawnMainActor(actorBaseAddr);



	return func_6C32E0
	(
		manager,
		ignore0,
		type,
		actorBaseAddr,
		ignore1,
		ignore2
	);
}



void EventMain()
{
	LogFunction();
}

void EventPause()
{
	LogFunction();
}

void EventTeleport()
{
	LogFunction();
}

void EventItem()
{
	LogFunction();
}

void EventCutscene()
{
	LogFunction();
}



void EventHandler()
{
	IntroduceEventData(return);

	using namespace EVENT;

	[&]()
	{
		auto event = eventData.event;
		if (event >= COUNT)
		{
			return;
		}

		auto & run = Event_run[event];
		if (run)
		{
			return;
		}

		run = true;



		switch (event)
		{
			case MAIN:
			{
				EventMain();

				break;
			}
			case PAUSE:
			{
				EventPause();

				break;
			}
			case TELEPORT:
			{
				EventTeleport();

				break;
			}
			case ITEM:
			{
				EventItem();

				break;
			}
			case CUTSCENE:
			{
				EventCutscene();

				break;
			}
		}
	}();
}



namespaceStart(Event);

export void Toggle(bool enable)
{
	LogFunction(enable);

	static bool run = false;



	// InitSession
	{
		auto addr     = (appBaseAddr + 0x7B425);
		auto jumpAddr = (appBaseAddr + 0x7B42C);
		constexpr size_t size = 7;
		/*
		dmc4.exe+7B425 - 80 BE 83060000 00 - cmp byte ptr [esi+00000683],00
		dmc4.exe+7B42C - 74 7E             - je dmc4.exe+7B4AC
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = OldCreateFunction(InitSession, jumpAddr, true, true, 0, 0, size);
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

	// SetCharacter
	{
		auto addr     = (appBaseAddr + 0x10C1F9);
		auto jumpAddr = (appBaseAddr + 0x10C1FE);
		constexpr size_t size = 5;
		/*
		dmc4.exe+10C1F9 - 68 FFFF0000 - push 0000FFFF
		dmc4.exe+10C1FE - 68 AC930001 - push dmc4.exe+C093AC
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = OldCreateFunction(SetCharacter, jumpAddr, true, true, 0, 0, size);
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

	// SetRoomPosition
	{
		constexpr off_t offs[] =
		{
			0x5E5661,
			0x5E57F1,
			0x5E5AAE,
			0x5E5C21,
			0x5E5E01,
			0x5E5FC1,
			0x5E6161,
			0x5E62D1,
			0x5E64B1,
			0x5E6631,
			0x5E67B1,
			0x5E6921,
			0x5E6AF1,
			0x5E6CA1,
			0x5E6E51,
			0x5E7031,
			0x5E71CE,
			0x5E739E,
			0x5E751E,
			0x5E766E,
			0x5E5381,
		};

		static Function funcs[countof(offs)] = {};

		for_all(index, countof(offs))
		{
			auto off = offs[index];

			auto addr     = (appBaseAddr + off);
			auto jumpAddr = (appBaseAddr + off + 5);
			constexpr size_t size = 5;

			auto & func = funcs[index];

			constexpr byte8 sect1[] =
			{
				0x83, 0xEC, 0x08,       // sub esp,08
				0x8D, 0x45, 0x24,       // lea eax,[ebp+24]
				0x89, 0x04, 0x24,       // mov [esp],eax
				0x8D, 0x45, 0x28,       // lea eax,[ebp+28]
				0x89, 0x44, 0x24, 0x04, // mov [esp+04],eax
			};

			if (!run)
			{
				backupHelper.Save(addr, size);
				func = OldCreateFunction(SetRoomPosition, jumpAddr, true, true, size, sizeof(sect1));
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
	}

	// SpawnMainActor
	{
		auto addr     = (appBaseAddr + 0x116600);
		auto jumpAddr = (appBaseAddr + 0x116605);
		constexpr size_t size = 5;
		/*
		dmc4.exe+116600 - E8 DBCC5A00 - call dmc4.exe+6C32E0
		dmc4.exe+116605 - 68 10C53501 - push dmc4.exe+F5C510
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(SpawnMainActor, jumpAddr);
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

	// EventHandler
	{
		auto addr     = (appBaseAddr + 0x1131E1);
		auto jumpAddr = (appBaseAddr + 0x1131E6);
		constexpr size_t size = 5;
		/*
		dmc4.exe+1131E1 - 0FB6 46 04 - movzx eax,byte ptr [esi+04]
		dmc4.exe+1131E5 - 48         - dec eax
		dmc4.exe+1131E6 - 83 F8 06   - cmp eax,06
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(EventHandler, jumpAddr, (FunctionFlags_SaveRegisters | FunctionFlags_NoResult), size);
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
