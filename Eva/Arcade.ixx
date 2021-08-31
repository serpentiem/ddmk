export module Arcade;

import Core;

#include "../Core/Macros.h"



import Config;
import Global;
import Vars;

#define debug false

#include "Macros.h"



// @Todo: extend missionstartsetindex to update weapons.

// for proper yamato and stuff





namespaceStart(Arcade);

export void InitSession()
{
	if (!activeConfig.Arcade.enable)
	{
		return;
	}

	LogFunction();

	IntroduceSessionData(return);







	sessionData.mission = activeConfig.Arcade.mission;

	sessionData.mode = activeConfig.Arcade.mode;

	sessionData.character = activeConfig.Arcade.character;













	if constexpr (debug)
	{
		sessionData.redOrbs = 1500000;
	}


	// @Todo: Set OrbFlags.





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

export void SetExpertise()
{
	if (!activeConfig.Arcade.enable)
	{
		return;
	}

	LogFunction();

	IntroduceSessionData(return);

	IntroduceMainActorData(actorData, return);



	sessionData.hitPoints = activeConfig.Arcade.hitPoints;
	sessionData.magicPoints = activeConfig.Arcade.magicPoints;



	actorData.hitPoints = (activeConfig.Arcade.hitPoints * 100);
	actorData.maxHitPoints = actorData.hitPoints;
	/*
	dmc1.exe+2C3C11 - 6B C0 64          - imul eax,eax,64
	dmc1.exe+2C3C14 - 66 89 BB CE1B0000 - mov [rbx+00001BCE],di
	*/



	actorData.magicPointsHuman = (activeConfig.Arcade.magicPoints * 120);
	actorData.maxMagicPointsHuman = actorData.magicPointsHuman;
	/*
	dmc1.exe+2C3C31 - 6B C0 78          - imul eax,eax,78
	dmc1.exe+2C3C34 - 41 89 B8 6C240000 - mov [r8+0000246C],edi
	*/



	actorData.magicPointsDevil = (activeConfig.Arcade.magicPoints * 200);
	actorData.maxMagicPointsDevil = actorData.magicPointsDevil;
	/*
	dmc1.exe+2C3C49 - B8 C8000000 - mov eax,000000C8
	dmc1.exe+2C3C57 - 0FAF C8     - imul ecx,eax
	*/


















	actorData.meleeWeapon = activeConfig.Arcade.meleeWeapon;
	actorData.rangedWeapon = activeConfig.Arcade.rangedWeapon;
	actorData.meleeWeaponForm = activeConfig.Arcade.meleeWeaponForm;



	// switch (actorData.meleeWeapon)
	// {
	// 	case WEAPON::FORCE_EDGE:
	// 	{
	// 		if (activeConfig.Arcade.sparda)
	// 		{
	// 			actorData.meleeWeaponForm = MELEE_WEAPON_FORM::SPARDA;
	// 		}

	// 		break;
	// 	}
	// 	case WEAPON::ALASTOR:
	// 	{
	// 		if (activeConfig.Arcade.yamato)
	// 		{
	// 			actorData.meleeWeaponForm = MELEE_WEAPON_FORM::YAMATO;
	// 		}

	// 		break;
	// 	}
	// 	case WEAPON::SPARDA:
	// 	{
	// 		actorData.meleeWeaponForm = MELEE_WEAPON_FORM::SPARDA;

	// 		break;
	// 	}
	// }



	sessionData.expertise = 0xFFFFFFFF;
}




export void MissionStartSetIndex()
{
	if (!activeConfig.Arcade.enable)
	{
		return;
	}

	LogFunction();

	IntroduceSessionData(return);



	new_for_all(itemIndex, 10)
	{
		ItemData item =
		{
			0,
			static_cast<uint8>(itemIndex),
			1
		};

		AddUniqueItem(item);
	}




	// for_all(uint64, itemDataIndex)





	// // Unlock Weapons

	// for_all(uint64, index, 10)
	// {
	// 	auto & itemData = sessionData.itemData[index];

	// 	itemData.category = 0;
	// 	itemData.id = static_cast<uint8>(index);
	// 	itemData.count = 1;
	// }





	// // Unlock Bangle of Time

	// {
	// 	auto & itemData = sessionData.itemData[10];

	// 	itemData.category = 1;
	// 	itemData.id = ITEM_1::BANGLE_OF_TIME;
	// 	itemData.count = 1;
	// }





	//sessionData.itemCount = 11;




	sessionData.var_1F9C = 6; // Unlock Quick Swap




}








export void SetRoom()
{
	if (!activeConfig.Arcade.enable)
	{
		return;
	}

	LogFunction();

	IntroduceEventData(return);

	if (!activeConfig.Arcade.ignoreTrack)
	{
		eventData.track = activeConfig.Arcade.track;
	}

	if (!activeConfig.Arcade.ignoreRoom)
	{
		eventData.room = activeConfig.Arcade.room;
	}
}

export void SetPosition()
{
	if (!activeConfig.Arcade.enable)
	{
		return;
	}

	LogFunction();

	auto & nextPosition = *reinterpret_cast<vec4 *>(appBaseAddr + 0x27E82A0);

	if (!activeConfig.Arcade.ignorePosition)
	{
		nextPosition = activeConfig.Arcade.position;
	}
}





// export void SetEquipment()
// {
// 	LogFunction();


// }





export void Toggle(bool enable)
{
	LogFunction(enable);



	static bool run = false;



	// Auto Confirm
	{
		auto addr = (appBaseAddr + 0x3F8C2F);
		auto dest = (appBaseAddr + 0x3F8C35);
		constexpr uint32 size = 6;
		/*
		dmc1.exe+3F8C2F - 0F84 D8000000 - je dmc1.exe+3F8D0D
		dmc1.exe+3F8C35 - 0FBE 4B 12    - movsx ecx,byte ptr [rbx+12]
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

	// Skip Load Data
	{
		auto addr = (appBaseAddr + 0x3F8C43);
		auto dest = (appBaseAddr + 0x3F8C49);
		constexpr uint32 size = 6;
		/*
		dmc1.exe+3F8C43 - 0F84 9E000000 - je dmc1.exe+3F8CE7
		dmc1.exe+3F8C49 - 83 E9 01      - sub ecx,01
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

	// Force New Game
	{
		auto addr = (appBaseAddr + 0x3F8C4C);
		constexpr uint32 size = 2;
		/*
		dmc1.exe+3F8C4C - 74 2F    - je dmc1.exe+3F8C7D
		dmc1.exe+3F8C4E - 83 F9 01 - cmp ecx,01
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			Write<byte8>(addr, 0xEB);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Character Change Auto Confirm
	{
		auto addr = (appBaseAddr + 0x3F8FBA);
		auto dest = (appBaseAddr + 0x3F8FBC);
		constexpr uint32 size = 2;
		/*
		dmc1.exe+3F8FBA - 74 5E      - je dmc1.exe+3F901A
		dmc1.exe+3F8FBC - 0FBE 4B 13 - movsx ecx,byte ptr [rbx+13]
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

	// Select Difficulty Auto Confirm
	{
		auto addr = (appBaseAddr + 0x3F9163);
		auto dest = (appBaseAddr + 0x3F9165);
		constexpr uint32 size = 2;
		/*
		dmc1.exe+3F9163 - 74 3B      - je dmc1.exe+3F91A0
		dmc1.exe+3F9165 - 0FBE 4B 13 - movsx ecx,byte ptr [rbx+13]
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

	// Better Skip Mission Screen
	{
		auto addr = (appBaseAddr + 0x3DC265);
		auto dest = (appBaseAddr + 0x3DC267);
		constexpr uint64 size = 2;
		/*
		dmc1.exe+3DC265 - 74 D1             - je dmc1.exe+3DC238
		dmc1.exe+3DC267 - 48 8B 05 1AE92000 - mov rax,[dmc1.exe+5EAB88]
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



	run = true;
}

namespaceEnd();
