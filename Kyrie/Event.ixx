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



//bool Event_run[EVENT::COUNT] = {};



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

	g_position = *positionAddr;
}

void SetBloodyPalaceLevel()
{
	LogFunction();

	Arcade::SetBloodyPalaceLevel();
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
		g_eventRun,
		0,
		sizeof(g_eventRun)
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






const char * eventFuncNames[] =
{
	"EventMain",
	"EventPause",
	"EventTeleport",
	"EventItem",
	"EventCutscene",
};

static_assert(countof(eventFuncNames) == EVENT::COUNT);

const char * newEventFuncNames[] =
{
	"NewEventMain",
	"NewEventPause",
	"NewEventTeleport",
	"NewEventItem",
	"NewEventCutscene",
};

static_assert(countof(newEventFuncNames) == EVENT::COUNT);







void EventHandler()
{
	IntroduceEventData(return);

	using namespace EVENT;



	auto event = eventData.event;
	if (event >= COUNT)
	{
		// @Adjust: Once is enough.
		static new_size_t count = 0;

		if (count < 10)
		{
			Log("__UNKNOWN_EVENT__ %u", event);

			count++;
		}

		return;
	}



	[&]()
	{
		auto funcName = eventFuncNames[event];

		auto & run = g_eventRun[event];

		if (!run)
		{
			run = true;

			switch (event)
			{
				case MAIN:
				{
					Log(funcName);

					Actor::EventMain();

					break;
				}
				case PAUSE:
				{
					Log(funcName);

					break;
				}
				case TELEPORT:
				{
					Log(funcName);

					break;
				}
				case ITEM:
				{
					Log(funcName);

					break;
				}
				case CUTSCENE:
				{
					Log(funcName);

					break;
				}
			}
		}
	}();



	[&]()
	{
		auto funcName = newEventFuncNames[event];

		static uint8 lastEvent = COUNT;

		if (lastEvent != event)
		{
			lastEvent = event;



			switch (event)
			{
				case MAIN:
				{
					Log(funcName);

					Actor::NewEventMain();

					break;
				}
				case PAUSE:
				{
					Log(funcName);

					break;
				}
				case TELEPORT:
				{
					Log(funcName);

					break;
				}
				case ITEM:
				{
					Log(funcName);

					break;
				}
				case CUTSCENE:
				{
					Log(funcName);

					Actor::NewEventCutscene();

					break;
				}
			}
		}
	}();



	switch (event)
	{
		case MAIN:
		{
			CharacterSwitchController();

			break;
		}
		// case PAUSE:
		// {
		// 	break;
		// }
		// case TELEPORT:
		// {
		// 	break;
		// }
		// case ITEM:
		// {
		// 	break;
		// }
		// case CUTSCENE:
		// {
		// 	break;
		// }
	}
}













// void EventCutsceneStart()
// {
// 	LogFunction();

// 	Actor::EventCutsceneStart();
// }

// void EventCutsceneEnd()
// {
// 	LogFunction();

// 	Actor::EventCutsceneEnd();
// }



// void __fastcall SetActorEvent(byte8 * actorBaseAddr)
// {
// 	//Log("%s %X", FUNC_NAME, actorBaseAddr);


// 	Actor::SetActorEvent(actorBaseAddr);


// }







namespaceStart(Event);

export void Toggle(bool enable)
{
	LogFunction(enable);

	static bool run = false;



	// InitSession
	{
		auto addr     = (appBaseAddr + 0x7B425);
		auto jumpAddr = (appBaseAddr + 0x7B42C);
		constexpr new_size_t size = 7;
		/*
		dmc4.exe+7B425 - 80 BE 83060000 00 - cmp byte ptr [esi+00000683],00
		dmc4.exe+7B42C - 74 7E             - je dmc4.exe+7B4AC
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(InitSession, jumpAddr, true, true, 0, 0, size);
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
		constexpr new_size_t size = 5;
		/*
		dmc4.exe+10C1F9 - 68 FFFF0000 - push 0000FFFF
		dmc4.exe+10C1FE - 68 AC930001 - push dmc4.exe+C093AC
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(SetCharacter, jumpAddr, true, true, 0, 0, size);
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
			constexpr new_size_t size = 5;

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
				func = old_CreateFunction(SetRoomPosition, jumpAddr, true, true, size, sizeof(sect1));
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
		constexpr new_size_t size = 5;
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
		constexpr new_size_t size = 5;
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

	// // EventCutsceneStart
	// {
	// 	auto addr     = (appBaseAddr + 0x4C828B);
	// 	auto jumpAddr = (appBaseAddr + 0x4C8292);
	// 	constexpr new_size_t size = 7;
	// 	/*
	// 	dmc4.exe+4C828B - 66 89 9E 1D1A0000 - mov [esi+00001A1D],bx
	// 	dmc4.exe+4C8292 - 8B C6             - mov eax,esi
	// 	*/

	// 	static Function func = {};

	// 	if (!run)
	// 	{
	// 		backupHelper.Save(addr, size);
	// 		func = CreateFunction(EventCutsceneStart, jumpAddr, (FunctionFlags_SaveRegisters | FunctionFlags_NoResult), size);
	// 		CopyMemory(func.sect0, addr, size, MemoryFlags_VirtualProtectSource);
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

	// {
	// 	auto addr     = (appBaseAddr + 0x153A6A);
	// 	auto jumpAddr = (appBaseAddr + 0x153A73);
	// 	constexpr new_size_t size = 9;
	// 	/*
	// 	dmc4.exe+153A6A - 66 C7 80 1D1A0000 0000 - mov word ptr [eax+00001A1D],0000
	// 	dmc4.exe+153A73 - 83 43 04 02            - add dword ptr [ebx+04],02
	// 	*/

	// 	static Function func = {};

	// 	if (!run)
	// 	{
	// 		backupHelper.Save(addr, size);
	// 		func = CreateFunction(EventCutsceneStart, jumpAddr, (FunctionFlags_SaveRegisters | FunctionFlags_NoResult), size);
	// 		CopyMemory(func.sect0, addr, size, MemoryFlags_VirtualProtectSource);
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

	// // EventCutsceneEnd
	// {
	// 	auto addr     = (appBaseAddr + 0x153A98);
	// 	auto jumpAddr = (appBaseAddr + 0x153A9F);
	// 	constexpr new_size_t size = 7;
	// 	/*
	// 	dmc4.exe+153A98 - C6 80 1D1A0000 01 - mov byte ptr [eax+00001A1D],01
	// 	dmc4.exe+153A9F - 83 43 04 02       - add dword ptr [ebx+04],02
	// 	*/

	// 	static Function func = {};

	// 	if (!run)
	// 	{
	// 		backupHelper.Save(addr, size);
	// 		func = CreateFunction(EventCutsceneEnd, jumpAddr, (FunctionFlags_SaveRegisters | FunctionFlags_NoResult), size);
	// 		CopyMemory(func.sect0, addr, size, MemoryFlags_VirtualProtectSource);
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


	// SetBloodyPalaceLevel
	{
		auto addr     = (appBaseAddr + 0x5E539A);
		auto jumpAddr = (appBaseAddr + 0x5E53A4);
		constexpr new_size_t size = 10;
		/*
		dmc4.exe+5E539A - C7 80 90000000 01000000 - mov [eax+00000090],00000001
		dmc4.exe+5E53A4 - A1 F49E3501             - mov eax,[dmc4.exe+F59EF4]
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(SetBloodyPalaceLevel, jumpAddr, (FunctionFlags_SaveRegisters | FunctionFlags_NoResult), size);
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





// // SetActorEvent
// {
// 	auto addr = (appBaseAddr + 0x23C968);
// 	constexpr new_size_t size = 6;
// 	/*
// 	dmc4.exe+23C968 - 89 41 10 - mov [ecx+10],eax
// 	dmc4.exe+23C96B - C2 0400  - ret 0004
// 	dmc4.exe+23C96E - CC       - int 3
// 	*/

// 	constexpr byte8 sect0[] =
// 	{
// 		0x89, 0x41, 0x10, // mov [ecx+10],eax
// 	};
// 	constexpr byte8 sect2[] =
// 	{
// 		0xC2, 0x04, 0x00, // ret 0004
// 	};

// 	static Function func = {};

// 	if (!run)
// 	{
// 		backupHelper.Save(addr, size);
// 		func = CreateFunction(SetActorEvent, 0, (FunctionFlags_SaveRegisters | FunctionFlags_NoResult | FunctionFlags_NoReturn), sizeof(sect0), 0, sizeof(sect2));
// 		CopyMemory(func.sect0, sect0, sizeof(sect0));
// 		CopyMemory(func.sect2, sect2, sizeof(sect2));
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
















	run = true;
}

namespaceEnd();







#pragma region Hotkeys








// void WindowSize1(byte8 * state)
// {





// 	static bool execute = true;




// 	constexpr byte8 keys[] =
// 	{
// 		DIK_LCONTROL,
// 		DIK_1,
// 	};


// 	uint8 keysDown = 0;



// 	old_for_all(uint8, index, countof(keys))
// 	{
// 		auto & key = keys[index];
// 		if (state[key] & 0x80)
// 		{
// 			keysDown++;
// 		}
// 	}




// 	if (keysDown == countof(keys))
// 	{
// 		if (execute)
// 		{
// 			execute = false;
// 			SetWindowPos
// 			(
// 				appWindow,
// 				0,
// 				0,
// 				0,
// 				640,
// 				360,
// 				0
// 			);
// 		}
// 	}
// 	else
// 	{
// 		execute = true;
// 	}
// }






#pragma endregion
























