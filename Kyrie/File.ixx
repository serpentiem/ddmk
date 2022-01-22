module;
#include <stdio.h>
#include <string.h>
export module File;

import Core;

#include "../Core/Macros.h"

import Windows;

using namespace Windows;

import Config;
import Global;
import Vars;

#define debug false



struct Helper
{
	const char * name;
	uint32 id;
};

constexpr Helper helpers[] =
{
	{ "Dante" , 6  },
	{ "Nero"  , 0  },
	{ "Vergil", 30 },
	{ "Trish" , 7  },
	{ "Lady"  , 8  },
};



const char * baseLocations[CHARACTER::COUNT] = {};
const char * costumeLocations[CHARACTER::COUNT][COSTUME::COUNT] = {};



typedef byte8 *(__fastcall * NewLoadFile_t)(byte8 *, void *, byte8 *, const char *, uint32);

byte8 * NewLoadFile(const char * location)
{
	auto dataAddr = *reinterpret_cast<byte8 **>(appBaseAddr + 0xF23E44);
	if (!dataAddr)
	{
		return 0;
	}



	auto funcAddr = *reinterpret_cast<byte8 **>(dataAddr);
	if (!funcAddr)
	{
		return 0;
	}

	funcAddr = *reinterpret_cast<byte8 **>(funcAddr + 0x30);
	if (!funcAddr)
	{
		return 0;
	}

	auto func = reinterpret_cast<NewLoadFile_t>(funcAddr);



	return func
	(
		dataAddr,
		0,
		(appBaseAddr + 0xF23F18),
		location,
		LOAD_TYPE::QUEUE
	);
}



void LoadAssets()
{
	LogFunction();



	for_each(playerIndex, 1, activeConfig.Actor.playerCount)
	{
		auto & playerData = activeConfig.Actor.playerData[playerIndex];

		auto character = ValidateCharacter(playerData.character);
		auto costume = ValidateCostume(character, playerData.costume);



		NewLoadFile(costumeLocations[character][0]);
		NewLoadFile(costumeLocations[character][costume]);
		NewLoadFile(baseLocations[character]);
	}
}



namespaceStart(File);

export void Toggle(bool enable)
{
	LogFunction(enable);

	static bool run = false;



	if (!run)
	{
		Container strings = {};

		if
		(
			!strings.Init
			(
				2048,
				512
			)
		)
		{
			Log("strings.Init failed.");
		}


		char buffer[2048];


		for_all(characterIndex, CHARACTER::COUNT)
		{
			auto & helper = helpers[characterIndex];
			auto & baseLocation = baseLocations[characterIndex];

			snprintf
			(
				buffer,
				sizeof(buffer),
				"rom\\player\\uPlayer%s",
				helper.name
			);

			strings.Push
			(
				buffer,
				(strlen(buffer) + 1)
			);

			baseLocation = const_cast<const char *>(reinterpret_cast<char *>(strings.Last()));
		}

		for_all(characterIndex, CHARACTER::COUNT){
		for_all(costumeIndex  , COSTUME::COUNT  )
		{
			auto & helper = helpers[characterIndex];
			auto & costumeLocation = costumeLocations[characterIndex][costumeIndex];

			auto name =
			(costumeIndex == 1) ? "rom\\player\\costume\\plmod_pl%.3u_ex00" :
			(costumeIndex == 3) ? "rom\\player\\costume\\plmod_pl%.3u_ex01" :
			"rom\\player\\costume\\plmod_pl%.3u";

			snprintf
			(
				buffer,
				sizeof(buffer),
				name,
				helper.id
			);

			strings.Push
			(
				buffer,
				(strlen(buffer) + 1)
			);

			costumeLocation = const_cast<const char *>(reinterpret_cast<char *>(strings.Last()));
		}}



		if constexpr (debug)
		{
			for_all(index, strings.count)
			{
				auto name = reinterpret_cast<char *>(strings[index]);

				Log(name);
			}
		}
	}



	run = true;
}



export void ToggleLoadAssets(bool enable)
{
	LogFunction(enable);

	static bool run = false;



	// LoadAssets
	{
		auto addr     = (appBaseAddr + 0x10C894);
		auto jumpAddr = (appBaseAddr + 0x10C89A);
		constexpr new_size_t size = 6;
		/*
		dmc4.exe+10C894 - 0FB6 4E 30     - movzx ecx,byte ptr [esi+30]
		dmc4.exe+10C898 - 2B CB          - sub ecx,ebx
		dmc4.exe+10C89A - 89 86 98000000 - mov [esi+00000098],eax
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(LoadAssets, jumpAddr, (FunctionFlags_SaveRegisters | FunctionFlags_NoResult), 0, 0, size);
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
