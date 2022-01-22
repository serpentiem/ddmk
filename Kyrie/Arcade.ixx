module;
#include <stdio.h>
export module Arcade;

import Core;

#include "../Core/Macros.h"



import Config;
import Global;
import Internal;
import Steam;
import Vars;

#define debug false






struct FloorHelper
{
	uint32 level;
	uint32 room;
};


FloorHelper floorHelpers[] =
{
	{ 1  , 705 },
	{ 20 , 503 },
	{ 21 , 704 },
	{ 40 , 504 },
	{ 41 , 703 },
	{ 60 , 505 },
	{ 61 , 701 },
	{ 80 , 507 },
	{ 81 , 702 },
	{ 100, 506 },
	{ 101, 700 },
};

static_assert(countof(floorHelpers) == 11);




namespaceStart(Arcade);

export void InitSession()
{
	if (!activeConfig.Arcade.enable)
	{
		return;
	}

	LogFunction();

	IntroduceSessionData(return);
	IntroduceCharacterData(return);

	sessionData.mission = activeConfig.Arcade.mission;
	sessionData.game    = activeConfig.Arcade.game;
	sessionData.mode    = activeConfig.Arcade.mode;

	characterData.hitPoints   = activeConfig.Arcade.hitPoints;
	characterData.magicPoints = activeConfig.Arcade.magicPoints;



	auto character = ValidateCharacter(activeConfig.Arcade.character);
	auto costume = ValidateCostume(character, activeConfig.Arcade.costume);






	characterData.Dante.costume  =
	characterData.Nero.costume   =
	characterData.Vergil.costume =
	characterData.Trish.costume  =
	characterData.Lady.costume   = costume;




	//static_assert(TypeMatch<decltype(CharacterDataDante::costume), uint32>::value);


	// @Todo: Test without save.


	// Dante
	{
		SetMemory
		(
			characterData.Dante.unlocks,
			1,
			sizeof(characterData.Dante.unlocks)
		);

		SetMemory
		(
			characterData.Dante.expertise,
			0xFF,
			sizeof(characterData.Dante.expertise)
		);
	}

	// Nero
	{
		SetMemory
		(
			characterData.Nero.unlocks,
			1,
			sizeof(characterData.Nero.unlocks)
		);

		SetMemory
		(
			characterData.Nero.expertise,
			0xFF,
			sizeof(characterData.Nero.expertise)
		);
	}

	// Vergil
	{
		SetMemory
		(
			characterData.Vergil.unlocks,
			1,
			sizeof(characterData.Vergil.unlocks)
		);

		SetMemory
		(
			characterData.Vergil.expertise,
			0xFF,
			sizeof(characterData.Vergil.expertise)
		);
	}

	// Trish
	{
		SetMemory
		(
			characterData.Trish.unlocks,
			1,
			sizeof(characterData.Trish.unlocks)
		);

		SetMemory
		(
			characterData.Trish.expertise,
			0xFF,
			sizeof(characterData.Trish.expertise)
		);
	}

	// Lady
	{
		SetMemory
		(
			characterData.Lady.unlocks,
			1,
			sizeof(characterData.Lady.unlocks)
		);

		SetMemory
		(
			characterData.Lady.expertise,
			0xFF,
			sizeof(characterData.Lady.expertise)
		);
	}


	// if constexpr (debug)
	// {
	// 	characterData.Dante.unlocks[3] = false;
	// 	characterData.Lady.unlocks[3] = false;
	// }




}


export void SetRoomPosition
(
	byte8 ** dataAddr,
	uint32 * positionAddr
)
{

	if (!activeConfig.Arcade.enable)
	{
		return;
	}


	LogFunction();









	if
	(
		(activeConfig.Arcade.mission >= 1 ) &&
		(activeConfig.Arcade.mission <= 20)
	)
	{
		if (!activeConfig.Arcade.ignoreRoom)
		{
			char roomName[128];

			snprintf
			(
				roomName,
				sizeof(roomName),
				"aRoom%03u",
				activeConfig.Arcade.room
			);

			*dataAddr = func_5F1540
			(
				roomName,
				(appBaseAddr + 0xC9C000)
			);
		}

		if (!activeConfig.Arcade.ignorePosition)
		{
			*positionAddr = activeConfig.Arcade.position;
		}
	}



	if (activeConfig.Arcade.mission == 50)
	{

		auto floor = activeConfig.Arcade.floor;
		if (floor >= FLOOR::COUNT)
		{
			floor = 0;
		}

		auto & floorHelper = floorHelpers[floor];

		char roomName[128];

		snprintf
		(
			roomName,
			sizeof(roomName),
			"aRoom%03u",
			floorHelper.room
		);

		*dataAddr = func_5F1540
		(
			roomName,
			(appBaseAddr + 0xC9C000)
		);

		*positionAddr = 0;
	}






}






export void SetBloodyPalaceLevel()
{
	if (!activeConfig.Arcade.enable)
	{
		return;
	}

	LogFunction();


	IntroduceNextEventData(return);



	auto floor = activeConfig.Arcade.floor;
	if (floor >= FLOOR::COUNT)
	{
		floor = 0;
	}

	auto & floorHelper = floorHelpers[floor];


	nextEventData.level = floorHelper.level;




}















export void SetCharacter()
{


	if (!activeConfig.Arcade.enable)
	{
		return;
	}



	LogFunction();

	IntroduceSessionEventData(return);

	sessionEventData.character = activeConfig.Arcade.character;
}












// export void SetHitPoints()
// {
// 	if (!activeConfig.Arcade.enable)
// 	{
// 		return;
// 	}

// 	LogFunction();

// 	IntroduceSessionData(return);



// 	sessionData.hitPoints = activeConfig.Arcade.hitPoints;
// 	sessionData.magicPoints = activeConfig.Arcade.magicPoints;
// }

// export void SetExpertise()
// {
// 	if (!activeConfig.Arcade.enable)
// 	{
// 		return;
// 	}

// 	LogFunction();

// 	IntroduceSessionData(return);

// 	IntroduceMainActorData(actorData, return);



// 	sessionData.hitPoints = activeConfig.Arcade.hitPoints;
// 	sessionData.magicPoints = activeConfig.Arcade.magicPoints;



// 	actorData.hitPoints = (activeConfig.Arcade.hitPoints * 100);
// 	actorData.maxHitPoints = actorData.hitPoints;
// 	/*
// 	dmc1.exe+2C3C11 - 6B C0 64          - imul eax,eax,64
// 	dmc1.exe+2C3C14 - 66 89 BB CE1B0000 - mov [rbx+00001BCE],di
// 	*/



// 	actorData.magicPointsHuman = (activeConfig.Arcade.magicPoints * 120);
// 	actorData.maxMagicPointsHuman = actorData.magicPointsHuman;
// 	/*
// 	dmc1.exe+2C3C31 - 6B C0 78          - imul eax,eax,78
// 	dmc1.exe+2C3C34 - 41 89 B8 6C240000 - mov [r8+0000246C],edi
// 	*/



// 	actorData.magicPointsDevil = (activeConfig.Arcade.magicPoints * 200);
// 	actorData.maxMagicPointsDevil = actorData.magicPointsDevil;
// 	/*
// 	dmc1.exe+2C3C49 - B8 C8000000 - mov eax,000000C8
// 	dmc1.exe+2C3C57 - 0FAF C8     - imul ecx,eax
// 	*/


















// 	actorData.meleeWeapon = activeConfig.Arcade.meleeWeapon;
// 	actorData.rangedWeapon = activeConfig.Arcade.rangedWeapon;
// 	actorData.meleeWeaponForm = activeConfig.Arcade.meleeWeaponForm;



// 	// switch (actorData.meleeWeapon)
// 	// {
// 	// 	case WEAPON::FORCE_EDGE:
// 	// 	{
// 	// 		if (activeConfig.Arcade.sparda)
// 	// 		{
// 	// 			actorData.meleeWeaponForm = MELEE_WEAPON_FORM::SPARDA;
// 	// 		}

// 	// 		break;
// 	// 	}
// 	// 	case WEAPON::ALASTOR:
// 	// 	{
// 	// 		if (activeConfig.Arcade.yamato)
// 	// 		{
// 	// 			actorData.meleeWeaponForm = MELEE_WEAPON_FORM::YAMATO;
// 	// 		}

// 	// 		break;
// 	// 	}
// 	// 	case WEAPON::SPARDA:
// 	// 	{
// 	// 		actorData.meleeWeaponForm = MELEE_WEAPON_FORM::SPARDA;

// 	// 		break;
// 	// 	}
// 	// }



// 	sessionData.expertise = 0xFFFFFFFF;
// }




// export void MissionStartSetIndex()
// {
// 	if (!activeConfig.Arcade.enable)
// 	{
// 		return;
// 	}

// 	LogFunction();

// 	IntroduceSessionData(return);



// 	for_all(itemIndex, 10)
// 	{
// 		ItemData item =
// 		{
// 			0,
// 			static_cast<uint8>(itemIndex),
// 			1
// 		};

// 		AddUniqueItem(item);
// 	}




// 	// for_all(uint64, itemDataIndex)





// 	// // Unlock Weapons

// 	// for_all(uint64, index, 10)
// 	// {
// 	// 	auto & itemData = sessionData.itemData[index];

// 	// 	itemData.category = 0;
// 	// 	itemData.id = static_cast<uint8>(index);
// 	// 	itemData.count = 1;
// 	// }





// 	// // Unlock Bangle of Time

// 	// {
// 	// 	auto & itemData = sessionData.itemData[10];

// 	// 	itemData.category = 1;
// 	// 	itemData.id = ITEM_1::BANGLE_OF_TIME;
// 	// 	itemData.count = 1;
// 	// }





// 	//sessionData.itemCount = 11;




// 	sessionData.var_1F9C = 6; // Unlock Quick Swap




// }








// export void SetRoom()
// {
// 	if (!activeConfig.Arcade.enable)
// 	{
// 		return;
// 	}

// 	LogFunction();

// 	IntroduceEventData(return);

// 	if (!activeConfig.Arcade.ignoreTrack)
// 	{
// 		eventData.track = activeConfig.Arcade.track;
// 	}

// 	if (!activeConfig.Arcade.ignoreRoom)
// 	{
// 		eventData.room = activeConfig.Arcade.room;
// 	}
// }

// export void SetPosition()
// {
// 	if (!activeConfig.Arcade.enable)
// 	{
// 		return;
// 	}

// 	LogFunction();

// 	auto & nextPosition = *reinterpret_cast<vec4 *>(appBaseAddr + 0x27E82A0);

// 	if (!activeConfig.Arcade.ignorePosition)
// 	{
// 		nextPosition = activeConfig.Arcade.position;
// 	}
// }





// export void SetEquipment()
// {
// 	LogFunction();


// }





export void Toggle(bool enable)
{
	LogFunction(enable);



	static bool run = false;


/*
db 83 EC 08          // sub esp,08
db 56                // push esi
db 57                // push edi
db 53                // push ebx
db 55                // push ebp

db 8B 35 00 9F 35 01 // mov esi,[dmc4.exe+F59F00]
db 33 FF             // xor edi,edi
db BB 01 00 00 00    // mov ebx,00000001
db 8B 2D 10 9F 35 01 // mov ebp,[dmc4.exe+F59F10]

db 5D                // pop ebp
db 5B                // pop ebx
db 5F                // pop edi
db 5E                // pop esi
db 83 C4 08          // add esp,08
*/



/*
dmc4.exe+7B1A0 - 83 EC 08         - sub esp,08
dmc4.exe+7B1A3 - 56               - push esi
dmc4.exe+7B1C0 - 57               - push edi
dmc4.exe+7B1E4 - 53               - push ebx
dmc4.exe+7B271 - 55               - push ebp

dmc4.exe+7B26B - 8B 35 009F3501   - mov esi,[dmc4.exe+F59F00]
dmc4.exe+7B1C1 - 33 FF            - xor edi,edi
dmc4.exe+7B1E5 - BB 01000000      - mov ebx,00000001
dmc4.exe+7B272 - 8B 2D 109F3501   - mov ebp,[dmc4.exe+F59F10]

dmc4.exe+7B2BF - 5D               - pop ebp
dmc4.exe+7B2C0 - 5B               - pop ebx
dmc4.exe+7B2C1 - 5F               - pop edi
dmc4.exe+7B2C4 - 5E               - pop esi
dmc4.exe+7B2C5 - 83 C4 08         - add esp,08
*/




// Skip Main Menu
{
	auto addr     = (appBaseAddr + 0x7B1A0);
	auto jumpAddr = (appBaseAddr + 0x7B2C9);
	constexpr new_size_t size = 6;
	/*
	dmc4.exe+7B1A0 - 83 EC 08         - sub esp,08
	dmc4.exe+7B1A3 - 56               - push esi
	dmc4.exe+7B1A4 - 8B F1            - mov esi,ecx

	dmc4.exe+7B1C0 - 57               - push edi
	dmc4.exe+7B1C1 - 33 FF            - xor edi,edi

	dmc4.exe+7B1E4 - 53               - push ebx
	dmc4.exe+7B1E5 - BB 01000000      - mov ebx,00000001

	dmc4.exe+7B26B - 8B 35 009F3501   - mov esi,[dmc4.exe+F59F00]

	dmc4.exe+7B271 - 55               - push ebp
	dmc4.exe+7B272 - 8B 2D 109F3501   - mov ebp,[dmc4.exe+F59F10]

	dmc4.exe+7B2BD - FF D2            - call edx
	dmc4.exe+7B2BF - 5D               - pop ebp
	dmc4.exe+7B2C0 - 5B               - pop ebx
	dmc4.exe+7B2C1 - 5F               - pop edi
	dmc4.exe+7B2C4 - 5E               - pop esi
	dmc4.exe+7B2C5 - 83 C4 08         - add esp,08
	dmc4.exe+7B2C8 - C3               - ret
	dmc4.exe+7B2C9 - 0FB6 85 A4000000 - movzx eax,byte ptr [ebp+000000A4]
	*/

	static Function func = {};

	constexpr byte8 sect0[] =
	{
		0x83, 0xEC, 0x08,                   // sub esp,08
		0x56,                               // push esi
		0x57,                               // push edi
		0x53,                               // push ebx
		0x55,                               // push ebp
		0x8B, 0x35, 0x00, 0x00, 0x00, 0x00, // mov esi,[dmc4.exe+F59F00]
		0x33, 0xFF,                         // xor edi,edi
		0xBB, 0x01, 0x00, 0x00, 0x00,       // mov ebx,00000001
		0x8B, 0x2D, 0x00, 0x00, 0x00, 0x00, // mov ebp,[dmc4.exe+F59F10]
	};

	if (!run)
	{
		backupHelper.Save(addr, size);
		func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
		CopyMemory(func.sect0, sect0, sizeof(sect0));
		*reinterpret_cast<byte8 **>(func.sect0 + 9) = (appBaseAddr + 0xF59F00);
		*reinterpret_cast<byte8 **>(func.sect0 + 0x16) = (appBaseAddr + 0xF59F10);
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



// Auto Confirm Mission Start
{
	auto addr = (appBaseAddr + 0x77DED);
	auto dest = (appBaseAddr + 0x77DF3);
	constexpr new_size_t size = 6;
	/*
	dmc4.exe+77DED - 0F84 F1000000  - je dmc4.exe+77EE4
	dmc4.exe+77DF3 - 39 B5 80020000 - cmp [ebp+00000280],esi
	*/

	if (!run)
	{
		backupHelper.Save(addr, size);
	}

	if (enable)
	{
		WriteAddress(addr, dest, size);
	}
	else
	{
		backupHelper.Restore(addr);
	}
}


// Auto Confirm Bloody Palace Start
{
	auto addr = (appBaseAddr + 0x46C32);
	auto dest = (appBaseAddr + 0x46C38);
	constexpr new_size_t size = 6;
	/*
	dmc4.exe+46C32 - 0F84 B4000000     - je dmc4.exe+46CEC
	dmc4.exe+46C38 - 83 BF 80020000 02 - cmp dword ptr [edi+00000280],02
	*/

	if (!run)
	{
		backupHelper.Save(addr, size);
	}

	if (enable)
	{
		WriteAddress(addr, dest, size);
	}
	else
	{
		backupHelper.Restore(addr);
	}
}








	// // Auto Confirm
	// {
	// 	auto addr = (appBaseAddr + 0x3F8C2F);
	// 	auto dest = (appBaseAddr + 0x3F8C35);
	// 	constexpr uint32 size = 6;
	// 	/*
	// 	dmc1.exe+3F8C2F - 0F84 D8000000 - je dmc1.exe+3F8D0D
	// 	dmc1.exe+3F8C35 - 0FBE 4B 12    - movsx ecx,byte ptr [rbx+12]
	// 	*/

	// 	if (!run)
	// 	{
	// 		backupHelper.Save(addr, size);
	// 	}

	// 	if (enable)
	// 	{
	// 		WriteAddress(addr, dest, size);
	// 	}
	// 	else
	// 	{
	// 		backupHelper.Restore(addr);
	// 	}
	// }

	// // Skip Load Data
	// {
	// 	auto addr = (appBaseAddr + 0x3F8C43);
	// 	auto dest = (appBaseAddr + 0x3F8C49);
	// 	constexpr uint32 size = 6;
	// 	/*
	// 	dmc1.exe+3F8C43 - 0F84 9E000000 - je dmc1.exe+3F8CE7
	// 	dmc1.exe+3F8C49 - 83 E9 01      - sub ecx,01
	// 	*/

	// 	if (!run)
	// 	{
	// 		backupHelper.Save(addr, size);
	// 	}

	// 	if (enable)
	// 	{
	// 		WriteAddress(addr, dest, size);
	// 	}
	// 	else
	// 	{
	// 		backupHelper.Restore(addr);
	// 	}
	// }

	// // Force New Game
	// {
	// 	auto addr = (appBaseAddr + 0x3F8C4C);
	// 	constexpr uint32 size = 2;
	// 	/*
	// 	dmc1.exe+3F8C4C - 74 2F    - je dmc1.exe+3F8C7D
	// 	dmc1.exe+3F8C4E - 83 F9 01 - cmp ecx,01
	// 	*/

	// 	if (!run)
	// 	{
	// 		backupHelper.Save(addr, size);
	// 	}

	// 	if (enable)
	// 	{
	// 		Write<byte8>(addr, 0xEB);
	// 	}
	// 	else
	// 	{
	// 		backupHelper.Restore(addr);
	// 	}
	// }

	// // Character Change Auto Confirm
	// {
	// 	auto addr = (appBaseAddr + 0x3F8FBA);
	// 	auto dest = (appBaseAddr + 0x3F8FBC);
	// 	constexpr uint32 size = 2;
	// 	/*
	// 	dmc1.exe+3F8FBA - 74 5E      - je dmc1.exe+3F901A
	// 	dmc1.exe+3F8FBC - 0FBE 4B 13 - movsx ecx,byte ptr [rbx+13]
	// 	*/

	// 	if (!run)
	// 	{
	// 		backupHelper.Save(addr, size);
	// 	}

	// 	if (enable)
	// 	{
	// 		WriteAddress(addr, dest, size);
	// 	}
	// 	else
	// 	{
	// 		backupHelper.Restore(addr);
	// 	}
	// }

	// // Select Difficulty Auto Confirm
	// {
	// 	auto addr = (appBaseAddr + 0x3F9163);
	// 	auto dest = (appBaseAddr + 0x3F9165);
	// 	constexpr uint32 size = 2;
	// 	/*
	// 	dmc1.exe+3F9163 - 74 3B      - je dmc1.exe+3F91A0
	// 	dmc1.exe+3F9165 - 0FBE 4B 13 - movsx ecx,byte ptr [rbx+13]
	// 	*/

	// 	if (!run)
	// 	{
	// 		backupHelper.Save(addr, size);
	// 	}

	// 	if (enable)
	// 	{
	// 		WriteAddress(addr, dest, size);
	// 	}
	// 	else
	// 	{
	// 		backupHelper.Restore(addr);
	// 	}
	// }

	// // Better Skip Mission Screen
	// {
	// 	auto addr = (appBaseAddr + 0x3DC265);
	// 	auto dest = (appBaseAddr + 0x3DC267);
	// 	constexpr uint64 size = 2;
	// 	/*
	// 	dmc1.exe+3DC265 - 74 D1             - je dmc1.exe+3DC238
	// 	dmc1.exe+3DC267 - 48 8B 05 1AE92000 - mov rax,[dmc1.exe+5EAB88]
	// 	*/

	// 	if (!run)
	// 	{
	// 		backupHelper.Save(addr, size);
	// 	}

	// 	if (enable)
	// 	{
	// 		WriteAddress(addr, dest, size);
	// 	}
	// 	else
	// 	{
	// 		backupHelper.Restore(addr);
	// 	}
	// }



	run = true;
}

namespaceEnd();
