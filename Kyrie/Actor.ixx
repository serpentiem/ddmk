export module Actor;

import Core;

#include "../Core/Macros.h"

import Windows;

using namespace Windows;

import Config;
import File;
import Global;
import Input;
import Internal;
import Vars;

#define debug false











export void SetMainActor(byte8 * actorBaseAddr)
{
	auto addr = *reinterpret_cast<byte8 **>(appBaseAddr + 0xF59F00);
	if (!addr)
	{
		return;
	}
	*reinterpret_cast<byte8 **>(addr + 0x24) = actorBaseAddr;
}



export void TogglePlayerActor
(
	PlayerActorData & actorData,
	bool enable
)
{
	actorData.enable = enable;
}



export void TogglePlayerActors(bool enable)
{
	for_all(playerIndex, activeConfig.Actor.playerCount)
	{
		IntroduceData(g_newActorData[playerIndex].baseAddr, actorData, PlayerActorData, continue);

		TogglePlayerActor(actorData, enable);
	}
}





export void TogglePlayerActorsByActivePlayerIndex()
{
	for_all(playerIndex, activeConfig.Actor.playerCount)
	{
		IntroduceData(g_newActorData[playerIndex].baseAddr, actorData, PlayerActorData, continue);

		TogglePlayerActor(actorData, (playerIndex == activePlayerIndex));
	}
}

export void TogglePlayerActorsByMainActor()
{
	IntroduceData(g_newActorData[0].baseAddr, mainActorData, PlayerActorData, return);

	for_each(playerIndex, 1, activeConfig.Actor.playerCount)
	{
		IntroduceData(g_newActorData[playerIndex].baseAddr, actorData, PlayerActorData, continue);

		TogglePlayerActor(actorData, mainActorData.enable);
	}
}

























typedef byte8 *(* CreateActor_t)();

CreateActor_t CreateActor[CHARACTER::COUNT] = {};



byte8 * CreatePlayerActor(new_size_t playerIndex)
{
	byte8 * actorBaseAddr = 0;

	auto & playerData = activeConfig.Actor.playerData[playerIndex];

	auto character = playerData.character;
	if (character >= CHARACTER::COUNT)
	{
		character = 0;
	}



	actorBaseAddr = CreateActor[character]();
	if (!actorBaseAddr)
	{
		Log("CreateActor[%u] failed.", character);

		return 0;
	}
	auto & actorData = *reinterpret_cast<PlayerActorData *>(actorBaseAddr);



	bool enable = (playerIndex == activePlayerIndex);

	TogglePlayerActor(actorData, enable);


	// [&]()
	// {
	// 	if
	// 	(
	// 		!activeConfig.enableCharacterSwitchController ||
	// 		(activePlayerIndex == playerIndex)
	// 	)
	// 	{
	// 		//Log("somethin %u %u", playerIndex, activePlayerIndex);

	// 		return;
	// 	}

	// 	SetMemory
	// 	(
	// 		&actorData.size,
	// 		0,
	// 		sizeof(actorData.size)
	// 	);

	// 	//actorData.event = 0;

	// 	//Log("stuffed");
	// }();



	return actorBaseAddr;
}



bool SpawnActor(byte8 * actorBaseAddr)
{
	auto entityManager = *reinterpret_cast<byte8 **>(appBaseAddr + 0xF240A4);
	if (!entityManager)
	{
		return false;
	}

	return func_6C32E0
	(
		entityManager,
		0,
		ENTITY_TYPE::PLAYER_ACTOR,
		actorBaseAddr,
		0,
		0
	);

	/*
	dmc4.exe+1165F3 - 8B 0D A4403201 - mov ecx,[dmc4.exe+F240A4]
	dmc4.exe+1165F9 - 33 DB          - xor ebx,ebx
	dmc4.exe+1165FB - 53             - push ebx
	dmc4.exe+1165FC - 53             - push ebx
	dmc4.exe+1165FD - 50             - push eax
	dmc4.exe+1165FE - 6A 0D          - push 0D
	dmc4.exe+116600 - E8 DBCC5A00    - call dmc4.exe+6C32E0
	*/
}

void SpawnPlayerActor(new_size_t playerIndex)
{
	auto actorBaseAddr = CreatePlayerActor(playerIndex);


	Log("%s %X", FUNC_NAME, actorBaseAddr);


	if (!actorBaseAddr)
	{
		return;
	}

	auto & newActorData = g_newActorData[playerIndex];

	newActorData.baseAddr = actorBaseAddr;



	SpawnActor(actorBaseAddr);
}

void SpawnPlayerActors()
{
	LogFunction();

	for_each(playerIndex, 1, activeConfig.Actor.playerCount)
	{
		SpawnPlayerActor(playerIndex);
	}
}



#pragma region GetCharacterData

byte8 * __fastcall GetCharacterData
(
	byte8 * actorBaseAddr,
	void *,
	byte8 * dest
)
{
	constexpr new_size_t size = sizeof(CharacterDataBase);



	SetMemory
	(
		dest,
		0,
		size
	);



	IntroduceData(actorBaseAddr, actorData, PlayerActorData, return dest);
	IntroduceSessionData(return dest);
	IntroduceCharacterData(return dest);



	void * addr = &sessionData.characterData;

	using namespace CHARACTER;

	switch (actorData.character)
	{
		case DANTE:
		{
			addr = &characterData.Dante;

			break;
		}
		case NERO:
		{
			addr = &characterData.Nero;

			break;
		}
		case VERGIL:
		{
			addr = &characterData.Vergil;

			break;
		}
		case TRISH:
		{
			addr = &characterData.Trish;

			break;
		}
		case LADY:
		{
			addr = &characterData.Lady;

			break;
		}
	}



	CopyMemory
	(
		dest,
		addr,
		size
	);



	return dest;
}

byte8 * __fastcall GetCharacterDataDanteTrish
(
	byte8 * actorBaseAddr,
	void *,
	byte8 * dest
)
{
	constexpr new_size_t size = 32;



	SetMemory
	(
		dest,
		0,
		size
	);



	IntroduceData(actorBaseAddr, actorData, PlayerActorData, return dest);
	IntroduceSessionData(return dest);
	IntroduceCharacterData(return dest);



	void * addr = &sessionData.characterData;

	using namespace CHARACTER;

	switch (actorData.character)
	{
		case DANTE:
		{
			addr = &characterData.Dante;

			break;
		}
		case NERO:
		{
			addr = &characterData.Nero;

			break;
		}
		case VERGIL:
		{
			addr = &characterData.Vergil;

			break;
		}
		case TRISH:
		{
			addr = &characterData.Trish;

			break;
		}
		case LADY:
		{
			addr = &characterData.Lady;

			break;
		}
	}



	CopyMemory
	(
		dest,
		(reinterpret_cast<byte8 *>(addr) + sizeof(CharacterDataBase)),
		size
	);



	return dest;
}

byte8 * __fastcall GetCharacterDataLady
(
	byte8 * actorBaseAddr,
	void *,
	byte8 * dest
)
{
	constexpr new_size_t size = 16;



	SetMemory
	(
		dest,
		0,
		size
	);



	IntroduceData(actorBaseAddr, actorData, PlayerActorData, return dest);
	IntroduceSessionData(return dest);
	IntroduceCharacterData(return dest);



	void * addr = &sessionData.characterData;

	using namespace CHARACTER;

	switch (actorData.character)
	{
		case DANTE:
		{
			addr = &characterData.Dante;

			break;
		}
		case NERO:
		{
			addr = &characterData.Nero;

			break;
		}
		case VERGIL:
		{
			addr = &characterData.Vergil;

			break;
		}
		case TRISH:
		{
			addr = &characterData.Trish;

			break;
		}
		case LADY:
		{
			addr = &characterData.Lady;

			break;
		}
	}



	CopyMemory
	(
		dest,
		(reinterpret_cast<byte8 *>(addr) + sizeof(CharacterDataBase)),
		size
	);



	return dest;
}

byte8 * __fastcall GetCharacterDataNero
(
	byte8 * actorBaseAddr,
	void *,
	byte8 * dest
)
{
	constexpr new_size_t size = 7;



	SetMemory
	(
		dest,
		0,
		size
	);



	IntroduceData(actorBaseAddr, actorData, PlayerActorData, return dest);
	IntroduceSessionData(return dest);
	IntroduceCharacterData(return dest);



	void * addr = &sessionData.characterData;

	using namespace CHARACTER;

	switch (actorData.character)
	{
		case DANTE:
		{
			addr = &characterData.Dante;

			break;
		}
		case NERO:
		{
			addr = &characterData.Nero;

			break;
		}
		case VERGIL:
		{
			addr = &characterData.Vergil;

			break;
		}
		case TRISH:
		{
			addr = &characterData.Trish;

			break;
		}
		case LADY:
		{
			addr = &characterData.Lady;

			break;
		}
	}



	CopyMemory
	(
		dest,
		(reinterpret_cast<byte8 *>(addr) + sizeof(CharacterDataBase)),
		size
	);



	return dest;
}

#pragma endregion



#pragma region GetCostume

uint32 __fastcall GetCostume(byte8 * actorBaseAddr)
{
	IntroduceData(actorBaseAddr, actorData, PlayerActorData, return 0);
	IntroduceCharacterData(return 0);



	uint32 character = ValidateCharacter(actorData.character);
	uint32 costume   = 0;



	bool match = false;

	for_each(playerIndex, 1, activeConfig.Actor.playerCount)
	{
		auto & playerData = activeConfig.Actor.playerData[playerIndex];
		auto & newActorData = g_newActorData[playerIndex];

		if (newActorData.baseAddr != actorBaseAddr)
		{
			continue;
		}

		costume = playerData.costume;

		match = true;

		break;
	}



	if (!match)
	{
		using namespace CHARACTER;

		costume =
		(character == DANTE ) ? characterData.Dante.costume  :
		(character == NERO  ) ? characterData.Nero.costume   :
		(character == VERGIL) ? characterData.Vergil.costume :
		(character == TRISH ) ? characterData.Trish.costume  :
		(character == LADY  ) ? characterData.Lady.costume   :
		0;
	}



	return ValidateCostume(character, costume);
}

void __fastcall LadyCostumeFix(byte8 * baseAddr)
{
	Log("%s %X", FUNC_NAME, baseAddr);

	if (!baseAddr)
	{
		return;
	}

	auto dest = *reinterpret_cast<byte8 **>(baseAddr + 0x106C0);
	if (!dest)
	{
		return;
	}

	dest = *reinterpret_cast<byte8 **>(dest + 0x74);
	if (!dest)
	{
		return;
	}

	auto & magic = *reinterpret_cast<float *>(dest + 0x3C);

	magic = 0;
}

#pragma endregion



void ClearActorData()
{
	SetMemory
	(
		g_newActorData,
		0,
		sizeof(g_newActorData)
	);
}








// @Todo: Active in GUI as well for consistency.
void MoveToActivePlayerActor()
{






	IntroduceData(g_newActorData[activePlayerIndex].baseAddr, activeActorData, PlayerActorData, return);




	for_all(playerIndex, activeConfig.Actor.playerCount)
	{

		IntroduceData(g_newActorData[playerIndex].baseAddr, actorData, PlayerActorData, continue);




		if (playerIndex == activePlayerIndex)
		{
			continue;
		}

		actorData.position = activeActorData.position;
		actorData.rotation = activeActorData.rotation;

	}






}









export void CharacterSwitchController_Reset()
{
	LogFunction();

	activePlayerIndex = 0;

	UpdateGamepadPlayerIndices();
}


export void CharacterSwitchController_Toggle(bool enable)
{
	LogFunction(enable);

	CharacterSwitchController_Reset();

	if (!InGame())
	{
		return;
	}

	if (enable)
	{
		TogglePlayerActorsByActivePlayerIndex();
	}
	else
	{
		IntroduceData(mainActorBaseAddr, g_newActorData[0].baseAddr, mainActorData, PlayerActorData, return);

		SetMainActor(mainActorBaseAddr);

		TogglePlayerActors(true);
	}
}






















export void CharacterSwitchController_Update()
{
	MoveToActivePlayerActor();



	activePlayerIndex++;

	if (activePlayerIndex >= activeConfig.Actor.playerCount)
	{
		activePlayerIndex = 0;
	}



	IntroduceData(activeActorBaseAddr, g_newActorData[activePlayerIndex].baseAddr, activeActorData, PlayerActorData, return);

	SetMainActor(activeActorBaseAddr);

	//CharacterSwitchController_TogglePlayerActors();

	TogglePlayerActorsByActivePlayerIndex();








	// // Update Sizes
	// {
	// 	activeActorData.size.x = 1;
	// 	activeActorData.size.y = 1;
	// 	activeActorData.size.z = 1;
	// 	activeActorData.size.a = 0;

	// 	for_all(playerIndex, activeConfig.Actor.playerCount)
	// 	{
	// 		IntroduceData(g_newActorData[playerIndex].baseAddr, actorData, PlayerActorData, continue);

	// 		if (playerIndex == activePlayerIndex)
	// 		{
	// 			continue;
	// 		}

	// 		SetMemory
	// 		(
	// 			&actorData.size,
	// 			0,
	// 			sizeof(actorData.size)
	// 		);
	// 	}
	// }





}




















export void CharacterSwitchController()
{
	if
	(
		!activeConfig.Actor.enable ||
		!activeConfig.enableCharacterSwitchController
	)
	{
		return;
	}














	auto keyboardAddr = DI8::GetKeyboardAddr();
	if (!keyboardAddr)
	{
		return;
	}



	static byte8 state[256] = {};


	keyboardAddr->GetDeviceState
	(
		sizeof(state),
		state
	);





	static bool executes[2] = {};



	//constexpr new_size_t key = DI8::KEY::P;


{

	auto & activeKeyData = activeConfig.characterSwitchControllerKeyData;


	auto & execute  = executes[0];
	auto & keys     = activeKeyData.keys;
	auto & keyCount = activeKeyData.keyCount;




	new_size_t keysDown = 0;

	if (keyCount < 1)
	{
		return;
	}

	for_all(keyIndex, keyCount)
	{
		auto & key = keys[keyIndex];

		if (state[key] & 0x80)
		{
			keysDown++;
		}
	}

	if (keysDown == keyCount)
	{
		if (execute)
		{
			execute = false;

			CharacterSwitchController_Update();
		}
	}
	else
	{
		execute = true;
	}
}







	// {
	// 	auto & execute = executes[0];

	// 	if (state[key] & 0x80)
	// 	{
	// 		if (execute)
	// 		{
	// 			execute = false;

	// 			CharacterSwitchController_Update();
	// 		}
	// 	}
	// 	else
	// 	{
	// 		execute = true;
	// 	}
	// }


















	{
		auto & execute = executes[1];

		auto flags = GetGamepadFlags(activePlayerIndex);



		if (flags & activeConfig.characterSwitchControllerButton)
		{
			if (execute)
			{
				execute = false;

				CharacterSwitchController_Update();
			}
		}
		else
		{
			execute = true;
		}
	}




}

















namespaceStart(Actor);

export void Toggle(bool enable)
{
	LogFunction(enable);

	static bool run = false;



	if (!run)
	{
		constexpr off_t offs[CHARACTER::COUNT][2] =
		{
			{ 0x4D27D0, 0x4D2800 },
			{ 0x50EE10, 0x50EEF0 },
			{ 0xCB400 , 0xCB430  },
			{ 0xC69C0 , 0xC69F0  },
			{ 0xC5140 , 0xC5170  },
		};

		for_all(character, CHARACTER::COUNT)
		{
			off_t pos = 0;

			byte8 sect1[64] = {};

			auto Feed = [&]
			(
				const void * addr,
				new_size_t size
			)
			{
				CopyMemory
				(
					(sect1 + pos),
					addr,
					size
				);

				pos += size;
			};



			{
				constexpr byte8 buffer[] =
				{
					0xE8, 0x00, 0x00, 0x00, 0x00, // call
				};
				Feed(buffer, sizeof(buffer));
			}

			if (character == CHARACTER::VERGIL)
			{
				constexpr byte8 buffer[] =
				{
					0x8B, 0xF8, // mov edi,eax
				};
				Feed(buffer, sizeof(buffer));
			}
			else
			{
				constexpr byte8 buffer[] =
				{
					0x8B, 0xF0, // mov esi,eax
				};
				Feed(buffer, sizeof(buffer));
			}

			{
				constexpr byte8 buffer[] =
				{
					0xE8, 0x00, 0x00, 0x00, 0x00, // call
				};
				Feed(buffer, sizeof(buffer));
			}



			auto func = CreateFunction(0, 0, FunctionFlags_SaveRegisters, 0, pos);
			CopyMemory(func.sect1, sect1, pos);

			WriteCall(func.sect1      , (appBaseAddr + offs[character][0]));
			WriteCall((func.sect1 + 7), (appBaseAddr + offs[character][1]));

			CreateActor[character] = reinterpret_cast<CreateActor_t>(func.addr);

			DebugLog("CreateActor %u %X", character, func.addr);
		}
	}



	// GetCharacterData
	{
		auto addr     = (appBaseAddr + 0xB4090);
		constexpr new_size_t size = 6;
		/*
		dmc4.exe+B4090 - 55       - push ebp
		dmc4.exe+B4091 - 8B EC    - mov ebp,esp
		dmc4.exe+B4093 - 83 E4 F8 - and esp,-08
		dmc4.exe+B4096 - 8B 45 08 - mov eax,[ebp+08]
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(GetCharacterData, 0, (FunctionFlags_Jump | FunctionFlags_NoReturn));
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

	// GetCharacterDataDanteTrish
	{
		auto addr     = (appBaseAddr + 0xB40D0);
		constexpr new_size_t size = 6;
		/*
		dmc4.exe+B40D0 - 55             - push ebp
		dmc4.exe+B40D1 - 8B EC          - mov ebp,esp
		dmc4.exe+B40D3 - 83 E4 F8       - and esp,-08
		dmc4.exe+B40D6 - 81 EC 08010000 - sub esp,00000108
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(GetCharacterDataDanteTrish, 0, (FunctionFlags_Jump | FunctionFlags_NoReturn));
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

	// GetCharacterDataLady
	{
		auto addr     = (appBaseAddr + 0x9E040);
		constexpr new_size_t size = 6;
		/*
		dmc4.exe+9E040 - 55             - push ebp
		dmc4.exe+9E041 - 8B EC          - mov ebp,esp
		dmc4.exe+9E043 - 83 E4 F8       - and esp,-08
		dmc4.exe+9E046 - 81 EC 08010000 - sub esp,00000108
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(GetCharacterDataLady, 0, (FunctionFlags_Jump | FunctionFlags_NoReturn));
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

	// GetCharacterDataNero
	{
		auto addr     = (appBaseAddr + 0x50FD30);
		constexpr new_size_t size = 6;
		/*
		dmc4.exe+50FD30 - 55             - push ebp
		dmc4.exe+50FD31 - 8B EC          - mov ebp,esp
		dmc4.exe+50FD33 - 83 E4 F8       - and esp,-08
		dmc4.exe+50FD36 - 81 EC 08010000 - sub esp,00000108
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(GetCharacterDataNero, 0, (FunctionFlags_Jump | FunctionFlags_NoReturn));
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



	// GetCostumeDante
	{
		auto addr     = (appBaseAddr + 0x4D4675);
		auto jumpAddr = (appBaseAddr + 0x4D467B);
		constexpr new_size_t size = 6;
		/*
		dmc4.exe+4D4675 - 8B 80 A0010000 - mov eax,[eax+000001A0]
		dmc4.exe+4D467B - 56             - push esi
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(GetCostume, jumpAddr, FunctionFlags_SaveRegisters);
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

	// GetCostumeNero
	{
		auto addr     = (appBaseAddr + 0x5108C5);
		auto jumpAddr = (appBaseAddr + 0x5108CB);
		constexpr new_size_t size = 6;
		/*
		dmc4.exe+5108C5 - 8B 80 A8020000 - mov eax,[eax+000002A8]
		dmc4.exe+5108CB - 56             - push esi
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(GetCostume, jumpAddr, FunctionFlags_SaveRegisters);
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

	// GetCostumeVergil
	{
		auto addr     = (appBaseAddr + 0xD8745);
		auto jumpAddr = (appBaseAddr + 0xD874B);
		constexpr new_size_t size = 6;
		/*
		dmc4.exe+D8745 - 8B 80 98030000 - mov eax,[eax+00000398]
		dmc4.exe+D874B - 89 81 A8190000 - mov [ecx+000019A8],eax
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(GetCostume, jumpAddr, FunctionFlags_SaveRegisters);
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

	// GetCostumeTrish
	{
		auto addr     = (appBaseAddr + 0xB2C95);
		auto jumpAddr = (appBaseAddr + 0xB2C9B);
		constexpr new_size_t size = 6;
		/*
		dmc4.exe+B2C95 - 8B 80 94040000 - mov eax,[eax+00000494]
		dmc4.exe+B2C9B - 56             - push esi
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(GetCostume, jumpAddr, FunctionFlags_SaveRegisters);
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

	// GetCostumeLady
	{
		auto addr     = (appBaseAddr + 0x9BFE5);
		auto jumpAddr = (appBaseAddr + 0x9BFEB);
		constexpr new_size_t size = 6;
		/*
		dmc4.exe+9BFE5 - 8B 80 9C050000 - mov eax,[eax+0000059C]
		dmc4.exe+9BFEB - 53             - push ebx
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(GetCostume, jumpAddr, FunctionFlags_SaveRegisters);
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

	// LadyCostumeFix
	{
		auto addr     = (appBaseAddr + 0x9C2DD);
		auto jumpAddr = (appBaseAddr + 0x9C2E3);
		constexpr new_size_t size = 6;
		/*
		dmc4.exe+9C2DD - 89 86 C0060100 - mov [esi+000106C0],eax
		dmc4.exe+9C2E3 - C3             - ret
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			0x8B, 0xCE, // mov ecx,esi
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(LadyCostumeFix, jumpAddr, (FunctionFlags_SaveRegisters | FunctionFlags_NoResult), size, sizeof(sect1));
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




// Second Jump Fix
{
	auto addr     = (appBaseAddr + 0x53A45F);
	auto jumpAddr = (appBaseAddr + 0x53A464);
	constexpr new_size_t size = 5;
	/*
	dmc4.exe+53A45F - E8 FCBDC7FF - call dmc4.exe+1B6260
	dmc4.exe+53A464 - 3C 01       - cmp al,01
	*/

	static Function func = {};

	constexpr byte8 sect0[] =
	{
		0x83, 0xC4, 0x04,             // add esp,04
		0x57,                         // push edi
		0x56,                         // push esi
		0xE8, 0x00, 0x00, 0x00, 0x00, // call dmc4.exe+1B6260
	};

	if (!run)
	{
		backupHelper.Save(addr, size);
		func = CreateFunction(0, jumpAddr, 0, sizeof(sect0));
		CopyMemory(func.sect0, sect0, sizeof(sect0));
		WriteCall((func.sect0 + 5), (appBaseAddr + 0x1B6260));
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
	auto addr     = (appBaseAddr + 0x53A491);
	auto jumpAddr = (appBaseAddr + 0x53A496);
	constexpr new_size_t size = 5;
	/*
	dmc4.exe+53A491 - E8 CABDC7FF - call dmc4.exe+1B6260
	dmc4.exe+53A496 - 3C 01       - cmp al,01
	*/

	static Function func = {};

	constexpr byte8 sect0[] =
	{
		0x83, 0xC4, 0x04,             // add esp,04
		0x57,                         // push edi
		0x56,                         // push esi
		0xE8, 0x00, 0x00, 0x00, 0x00, // call dmc4.exe+1B6260
	};

	if (!run)
	{
		backupHelper.Save(addr, size);
		func = CreateFunction(0, jumpAddr, 0, sizeof(sect0));
		CopyMemory(func.sect0, sect0, sizeof(sect0));
		WriteCall((func.sect0 + 5), (appBaseAddr + 0x1B6260));
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
	auto addr = (appBaseAddr + 0x1B636C);
	constexpr new_size_t size = 8;
	/*
	dmc4.exe+1B636C - A1 009F3501 - mov eax,[dmc4.exe+F59F00]
	dmc4.exe+1B6371 - 8B 40 24    - mov eax,[eax+24]
	dmc4.exe+1B6374 - F3 0F59 CE  - mulss xmm1,xmm6
	*/

	constexpr byte8 sect0[] =
	{
		0x8B, 0x44, 0x24, 0x18, // mov eax,[esp+18]
	};

	if (!run)
	{
		backupHelper.Save(addr, size);
	}

	if (enable)
	{
		SetMemory(addr, 0x90, size, MemoryFlags_VirtualProtectDestination);
		CopyMemory(addr, sect0, sizeof(sect0), MemoryFlags_VirtualProtectDestination);
	}
	else
	{
		backupHelper.Restore(addr);
	}
}

{
	auto addr = (appBaseAddr + 0x1B6456);
	constexpr new_size_t size = 3;
	/*
	dmc4.exe+1B6456 - C2 0400 - ret 0004
	dmc4.exe+1B6459 - 5F      - pop edi
	*/

	if (!run)
	{
		backupHelper.Save(addr, size);
	}

	if (enable)
	{
		Write<uint16>((addr + 1), 8);
	}
	else
	{
		backupHelper.Restore(addr);
	}
}

{
	auto addr = (appBaseAddr + 0x1B645F);
	constexpr new_size_t size = 3;
	/*
	dmc4.exe+1B645F - C2 0400 - ret 0004
	dmc4.exe+1B6462 - CC      - int 3
	*/

	if (!run)
	{
		backupHelper.Save(addr, size);
	}

	if (enable)
	{
		Write<uint16>((addr + 1), 8);
	}
	else
	{
		backupHelper.Restore(addr);
	}
}









	File::ToggleLoadAssets(enable);
	//Input::ToggleExtensions(enable);



	run = true;
}

namespaceEnd();



export void ToggleDisablePlayerActorIdleTimer(bool enable)
{
	LogFunction(enable);

	static bool run = false;

	{
		auto addr = (appBaseAddr + 0x5573C1);
		constexpr new_size_t size = 5;
		/*
		dmc4.exe+5573C1 - F3 0F5C 46 1C - subss xmm0,[esi+1C]
		dmc4.exe+5573C6 - 0F2F C8       - comiss xmm1,xmm0
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			SetMemory(addr, 0x90, size, MemoryFlags_VirtualProtectDestination);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	run = true;
}





















#pragma region Scenes

namespaceStart(Actor);

export void SceneMain()
{
	LogFunction();

	Actor::Toggle(activeConfig.Actor.enable);
}

export void SceneMissionSelect()
{
	LogFunction();

	Actor::Toggle(activeConfig.Actor.enable);
}

export void SceneMissionStart()
{
	LogFunction();

	activePlayerIndex = 0;
}




namespaceEnd();

#pragma endregion



#pragma region Events

namespaceStart(Actor);

export void EventSpawnMainActor(byte8 * actorBaseAddr)
{
	if (!activeConfig.Actor.enable)
	{
		return;
	}

	LogFunction(actorBaseAddr);



	ClearActorData();

	g_newActorData[0].baseAddr = actorBaseAddr;

	SpawnPlayerActors();
}





export void EventMain()
{
	if (!activeConfig.Actor.enable)
	{
		return;
	}

	LogFunction();

	CharacterSwitchController_Reset();
}





export void NewEventMain()
{
	if (!activeConfig.Actor.enable)
	{
		return;
	}

	LogFunction();

	TogglePlayerActorsByMainActor();



	//CharacterSwitchController_Reset();

	if (!activeConfig.enableCharacterSwitchController)
	{
		return;
	}

	TogglePlayerActorsByActivePlayerIndex();
}

export void NewEventCutscene()
{
	if (!activeConfig.Actor.enable)
	{
		return;
	}

	LogFunction();

	TogglePlayerActorsByMainActor();



	//CharacterSwitchController_Reset();

	if (!activeConfig.enableCharacterSwitchController)
	{
		return;
	}

	TogglePlayerActorsByActivePlayerIndex();
}





namespaceEnd();

#pragma endregion



export void ToggleOneHitKill(bool enable)
{
	LogFunction(enable);

	static bool run = false;

	{
		auto addr = (appBaseAddr + 0x22DDD4);
		constexpr new_size_t size = 4;
		/*
		dmc4.exe+22DDD4 - F3 0F5C C1 - subss xmm0,xmm1
		dmc4.exe+22DDD8 - 0F2F D0    - comiss xmm2,xmm0
		*/

		constexpr byte8 sect0[] =
		{
			0xF3, 0x0F, 0x5C, 0xC0, // subss xmm0,xmm0
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			CopyMemory(addr, sect0, sizeof(sect0), MemoryFlags_VirtualProtectDestination);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	run = true;
}



















