// @Cleanup
// @Todo: Remove File_dynamicFiles and update UpdateMotionArchives.

module;
#include <stdio.h>
export module Actor;

import Core;

#include "../Core/Macros.h"

import Windows;

using namespace Windows;

import ActorBase;
import ActorRelocations;
import Config;
import File;
import Global;
import HUD;
import Internal;
import Input;
import Memory;
import Model;
import SoundRelocations;
import Sound;
import Vars;

#define debug false

// #include "Macros.h"


#define g_enableLockOnFixes true





#define Break(name) MessageBoxA(0, name, 0, 0)


bool lastEnable = false;
bool updateConfig = false;



// float lastHitPoints  [PLAYER_COUNT] = {};
// float lastMagicPoints[PLAYER_COUNT] = {};


//float hitPoints[PLAYER_COUNT] = {};



















#pragma region Enemy

















export byte8 * CreateEnemyActor
(
	const CreateEnemyActorData & createEnemyActorData,
	byte64 flags = 0
)
{
	if constexpr (debug)
	{
		LogFunction();
	}

	byte8 * actorBaseAddr = 0;



	IntroduceEnemyVectorData(return 0);

	auto count            = enemyVectorData.count;
	auto lastMetadataAddr = enemyVectorData.lastMetadataAddr;
	auto nextMetadataAddr = enemyVectorData.nextMetadataAddr;

	EnemyVectorDataMetadata nextMetadata = {};

	[&]()
	{
		if (!nextMetadataAddr)
		{
			return;
		}

		CopyMemory
		(
			&nextMetadata,
			nextMetadataAddr,
			sizeof(nextMetadata)
		);
	}();



	auto addr = *reinterpret_cast<byte8 **>(appBaseAddr + 0xC90E10);
	if (!addr)
	{
		return 0;
	}
	auto & fileDataMetadataAddr = *reinterpret_cast<FileDataMetadata **>(addr + 0xA80 + 0x628);

	auto lastFileDataMetadataAddr = fileDataMetadataAddr;



	auto addr2 = *reinterpret_cast<byte8 **>(appBaseAddr + 0xC90E10);
	if (!addr2)
	{
		return 0;
	}
	addr2 = *reinterpret_cast<byte8 **>(addr2 + 0x28);
	if (!addr2)
	{
		return 0;
	}
	addr2 += 0xCB0;



	fileDataMetadataAddr = enemyFileDataMetadata;

	actorBaseAddr = func_1A4680
	(
		addr2,
		createEnemyActorData
	);

	fileDataMetadataAddr = lastFileDataMetadataAddr;

	if (flags & CreateEnemyActorFlags_Reset)
	{
		enemyVectorData.count            = count;
		enemyVectorData.lastMetadataAddr = lastMetadataAddr;
		enemyVectorData.nextMetadataAddr = nextMetadataAddr;

		[&]()
		{
			if (!nextMetadataAddr)
			{
				return;
			}

			CopyMemory
			(
				nextMetadataAddr,
				&nextMetadata,
				sizeof(nextMetadata)
			);
		}();
	}



	return actorBaseAddr;
}

export byte8 * CreateEnemyActor
(
	const ConfigCreateEnemyActorData & configCreateEnemyActorData,
	byte64 flags = 0
)
{
	DebugLogFunction();

	CreateEnemyActorData createEnemyActorData = {};

	createEnemyActorData.enemy       = configCreateEnemyActorData.enemy;
	createEnemyActorData.position    = configCreateEnemyActorData.position;
	createEnemyActorData.rotation    = configCreateEnemyActorData.rotation;
	createEnemyActorData.spawnMethod = configCreateEnemyActorData.spawnMethod;
	createEnemyActorData.variant     = configCreateEnemyActorData.variant;

	[&]()
	{
		if (!configCreateEnemyActorData.useMainActorData)
		{
			return;
		}

		IntroduceMainActorData(mainActorData, return);

		createEnemyActorData.position = mainActorData.position;
		createEnemyActorData.rotation = mainActorData.rotation;
	}();



	return CreateEnemyActor
	(
		createEnemyActorData,
		flags
	);
}




































// export byte8 * CreateEnemyActor(Config::CreateEnemyActorData & configCreateEnemyActorData)
// {
// 	if constexpr (debug)
// 	{
// 		LogFunction();
// 	}

// 	IntroduceMainActorData(mainActorData, return 0);

// 	CreateEnemyActorData createEnemyActorData = {};

// 	createEnemyActorData.enemy = configCreateEnemyActorData.enemy;
// 	createEnemyActorData.position = (configCreateEnemyActorData.useMainActorData) ? mainActorData.position : configCreateEnemyActorData.position;
// 	createEnemyActorData.position.a = 1.0f;
// 	createEnemyActorData.rotation = (configCreateEnemyActorData.useMainActorData) ? mainActorData.rotation : configCreateEnemyActorData.rotation;
// 	createEnemyActorData.spawnMethod = configCreateEnemyActorData.spawnMethod;
// 	createEnemyActorData.variant = configCreateEnemyActorData.variant;



// 	return CreateEnemyActor(createEnemyActorData);
// }





















// @Todo: Remove.
// export void KillEnemy(uint8 index)
// {
// 	if
// 	(
// 		(index >= CREATE_ENEMY_COUNT) ||
// 		!InGame()
// 	)
// 	{
// 		return;
// 	}

// 	// @Todo: Introduce Enemy Data.
// 	auto enemyBaseAddr = Enemy_enemyBaseAddr[index];
// 	if (!enemyBaseAddr)
// 	{
// 		return;
// 	}
// 	auto & enemyData = *reinterpret_cast<EnemyActorData *>(enemyBaseAddr);

// 	switch (enemyData.enemy)
// 	{
// 		case ENEMY::LADY:
// 		{
// 			// @Todo: Enemy Data Lady.
// 			auto & event = *reinterpret_cast<uint32 *>(enemyBaseAddr + 0x180 + 0x5808);
// 			auto & isFriend = *reinterpret_cast<bool *>(enemyBaseAddr + 0x180 + 0x58AE);

// 			isFriend = false;
// 			event = 20;

// 			break;
// 		}
// 	}
// }




// namespaceStart(Actor);

// // @Remove
// export void Watchdog()
// {


// 	//bool yes = false;


// 	// old_for_all(uint64, index, g_enemyActorBaseAddrs.count)
// 	// {
// 	// 	LoopStart:;

// 	// 	{
// 	// 		IntroduceData(g_enemyActorBaseAddrs[index], actorData, EnemyActorData, continue);


// 	// 		// if (yes)
// 	// 		// {
// 	// 		// 	yes = false;

// 	// 		// 	char buffer[128];

// 	// 		// 	snprintf
// 	// 		// 	(
// 	// 		// 		buffer,
// 	// 		// 		sizeof(buffer),
// 	// 		// 		"Continuing with %llu %llX",
// 	// 		// 		index,
// 	// 		// 		reinterpret_cast<byte8 *>(&actorData)
// 	// 		// 	);

// 	// 		// 	Log(buffer);
// 	// 		// }



// 	// 		if (!actorData.baseAddr)
// 	// 		{
// 	// 			// if constexpr (debug)
// 	// 			// {
// 	// 			// 	char buffer[128];

// 	// 			// 	snprintf
// 	// 			// 	(
// 	// 			// 		buffer,
// 	// 			// 		sizeof(buffer),
// 	// 			// 		"Remove %llu %llX",
// 	// 			// 		index,
// 	// 			// 		reinterpret_cast<byte8 *>(&actorData)
// 	// 			// 	);

// 	// 			// 	Log(buffer);

// 	// 			// 	yes = true;
// 	// 			// }



// 	// 			Log("Remove %llu", index);
// 	// 			g_enemyActorBaseAddrs.Remove(index);











// 	// 			goto LoopStart;
// 	// 		}

// 	// 		//continue;
// 	// 	}

// 	// 	//goto LoopStart;
// 	// }
// }



// namespaceEnd();




// void EnemyWatchdog()
// {

// 	// static bool run = false;
// 	// if (!run)
// 	// {
// 	// 	run = true;

// 	// 	HoboBreak();

// 	// 	LogFunction();
// 	// }



// 	auto Function = [&](auto & enemyBaseAddr)
// 	{
// 		// @Todo: IntroduceEnemyDataNoBaseAddress.
// 		if (!enemyBaseAddr)
// 		{
// 			return;
// 		}
// 		auto & enemyData = *reinterpret_cast<EnemyActorData *>(enemyBaseAddr);

// 		if (!enemyData.baseAddr)
// 		{
// 			enemyBaseAddr = 0;
// 		}




// 	};

// 	Enemy_enemyBaseAddr.ForEach
// 	(
// 		0,
// 		CREATE_ENEMY_COUNT,
// 		Function
// 	);
// }










// export void Enemy_Main()
// {
// 	EnemyWatchdog();
// }

// // @Research: Check if both are still required.
// export void Enemy_CreateMainActor(byte8 * actorBaseAddr)
// {
// 	Enemy_enemyBaseAddr.Clear();
// }

// export void Enemy_Delete()
// {
// 	Enemy_enemyBaseAddr.Clear();
// }






#pragma endregion























#pragma region Main











































//export Vector<byte8 *> g_playerActorBaseAddrs = {};





typedef void(__fastcall * ResetLockOn_t)(PlayerActorData & actorData);

ResetLockOn_t ResetLockOn = 0;

typedef bool(__fastcall * UpdateLockOn_t)
(
	byte8 * actorBaseAddr,
	byte8 * dest
);

UpdateLockOn_t UpdateLockOn = 0;












typedef WeaponData *(__fastcall * RegisterWeapon_t)
(
	byte8 * actorData,
	uint32 weapon
);

RegisterWeapon_t RegisterWeapon[WEAPON::MAX] = {};











// template <typename T>
// void SetStyleData(T & actorData)
// {
// 	auto pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);
// 	if
// 	(
// 		!pool ||
// 		!pool[12]
// 	)
// 	{
// 		return;
// 	}
// 	auto dest = *reinterpret_cast<byte8 **>(pool[12]);
// 	if (!dest)
// 	{
// 		return;
// 	}
// 	*reinterpret_cast<StyleData **>(dest + 0x3D10) = &actorData.styleData;

// 	DebugLog("Updated Style Data");
// }







export template <typename T>
void SetMainActor(T & actorData)
{
	DebugLogFunction(actorData.operator byte8 *());

	auto actorBaseAddr = reinterpret_cast<byte8 *>(&actorData);



	// FileData
	[&]()
	{
		IntroduceSessionData();

		auto character = static_cast<uint8>(actorData.character);
		auto costume = actorData.costume;

		uint16 costumeFileId = 0;



		switch (character)
		{
			case CHARACTER::DANTE:
			{
				if (costume >= COSTUME::MAX_DANTE)
				{
					costume = 0;
				}

				costumeFileId = costumeFileIdsDante[costume];

				break;
			}
			case CHARACTER::BOB:
			{
				if (costume >= COSTUME::MAX_BOB)
				{
					costume = 0;
				}

				costumeFileId = costumeFileIdsBob[costume];

				break;
			}
			case CHARACTER::LADY:
			{
				if (costume >= COSTUME::MAX_LADY)
				{
					costume = 0;
				}

				costumeFileId = costumeFileIdsLady[costume];

				break;
			}
			case CHARACTER::VERGIL:
			{
				if (costume >= COSTUME::MAX_VERGIL)
				{
					costume = 0;
				}

				costumeFileId = costumeFileIdsVergil[costume];

				break;
			}
		}



		File_UpdateFileData
		(
			static_cast<uint16>(character),
			costumeFileId
		);



		if (actorData.character == CHARACTER::DANTE)
		{
			uint16 swordFileId = plwp_sword;

			if (sessionData.unlockDevilTrigger)
			{
				swordFileId = plwp_sword2;
			}

			if (actorData.sparda)
			{
				swordFileId = plwp_sword3;
			}

			File_UpdateFileData
			(
				140,
				swordFileId
			);
		}
	}();



	// Main
	[&]()
	{
		auto pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);
		if (!pool)
		{
			return;
		}
		pool[3] = actorBaseAddr;
	}();



	// Life, Cutscenes
	[&]()
	{
		auto pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E10);
		if
		(
			!pool ||
			!pool[5]
		)
		{
			return;
		}
		*reinterpret_cast<byte8 **>(pool[5] + 0x2CB8) = actorBaseAddr;
	}();



	// Style Data
	[&]()
	{
		auto pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);
		if
		(
			!pool ||
			!pool[12]
		)
		{
			return;
		}
		auto dest = *reinterpret_cast<byte8 **>(pool[12]);
		if (!dest)
		{
			return;
		}
		*reinterpret_cast<StyleData **>(dest + 0x3D10) = &actorData.styleData;

		DebugLog("Updated Style Data");
	}();


	//SetStyleData(actorData);


}

// @Todo: Prefer uint64.
export void SetMainActor(uint32 index)
{
	IntroducePlayerActorData(actorBaseAddr, g_playerActorBaseAddrs[index], actorData, return);

	SetMainActor(actorData);
}















template
<
	typename T1,
	typename T2
>
void CopyState
(
	T1 & activeActorData,
	T2 & actorData,
	byte32 flags = 0
)
{
	actorData.position                 = activeActorData.position;
	actorData.verticalPull             = activeActorData.verticalPull;
	actorData.verticalPullMultiplier   = activeActorData.verticalPullMultiplier;
	actorData.rotation                 = activeActorData.rotation;
	actorData.horizontalPull           = activeActorData.horizontalPull;
	actorData.horizontalPullMultiplier = activeActorData.horizontalPullMultiplier;

	if (flags & CopyStateFlags_EventData)
	{
		CopyMemory
		(
			actorData.eventData,
			activeActorData.eventData,
			sizeof(actorData.eventData)
		);

		CopyMemory
		(
			actorData.var_3E10,
			activeActorData.var_3E10,
			sizeof(actorData.var_3E10)
		);
	}

	if (flags & CopyStateFlags_Mode)
	{
		actorData.mode = activeActorData.mode;
	}

	actorData.dead = activeActorData.dead;

	actorData.hitPoints      = activeActorData.hitPoints;
	actorData.maxHitPoints   = activeActorData.maxHitPoints;
	actorData.magicPoints    = activeActorData.magicPoints;
	actorData.maxMagicPoints = activeActorData.maxMagicPoints;

	actorData.styleData.rank     = activeActorData.styleData.rank;
	actorData.styleData.meter    = activeActorData.styleData.meter;
	actorData.styleData.quotient = activeActorData.styleData.quotient;
	actorData.styleData.dividend = activeActorData.styleData.dividend;
	actorData.styleData.divisor  = activeActorData.styleData.divisor;

	CopyMemory
	(
		actorData.nextActionRequestPolicy,
		activeActorData.nextActionRequestPolicy,
		sizeof(actorData.nextActionRequestPolicy)
	);

	actorData.idleTimer = 600.0f;

	actorData.permissions = activeActorData.permissions;
	actorData.state       = activeActorData.state;
	actorData.lastState   = activeActorData.lastState;

	actorData.newAirHikeCount    = activeActorData.newAirHikeCount;
	actorData.newKickJumpCount   = activeActorData.newKickJumpCount;
	actorData.newWallHikeCount   = activeActorData.newWallHikeCount;
	actorData.newDashCount       = activeActorData.newDashCount;
	actorData.newSkyStarCount    = activeActorData.newSkyStarCount;
	actorData.newAirTrickCount   = activeActorData.newAirTrickCount;
	actorData.newTrickUpCount    = activeActorData.newTrickUpCount;
	actorData.newTrickDownCount  = activeActorData.newTrickDownCount;
	actorData.newAirStingerCount = activeActorData.newAirStingerCount;











	// @Todo: Update.
	// [&]()
	// {
	// 	IntroducePlayerActorData(actorBaseAddr, g_playerActorBaseAddrs[2], actorData, return);

	// 	actorData.speedMode = actorData.speedMode;
	// 	actorData.quicksilver = actorData.quicksilver;
	// }();
}





// void CopyState
// (
// 	T1 & activeActorData,
// 	T2 & idleActorData,
// 	byte32 flags = 0
// )



void CopyState
(
	CharacterData & activeCharacterData,
	NewActorData & activeNewActorData,
	CharacterData & characterData,
	NewActorData & newActorData,
	byte32 flags = 0
)
{
	if
	(
		!(
			(activeCharacterData.character < CHARACTER::MAX) &&
			(characterData.character < CHARACTER::MAX)
		)
	)
	{
		return;
	}

	IntroduceData(activeNewActorData.baseAddr, activeActorData, PlayerActorData, return);
	IntroduceData(newActorData.baseAddr      , actorData      , PlayerActorData, return);

	CopyState
	(
		activeActorData,
		actorData
	);







	if (flags & CopyStateFlags_FixPermissions)
	{
		actorData.permissions = 0x1C1B;
	}


	actorData.state = (actorData.state & STATE::IN_AIR) ? STATE::IN_AIR : STATE::ON_FLOOR;


	// High Time Launch Fix
	if
	(
		(actorData.permissions == 0x400) &&
		(actorData.state & STATE::IN_AIR) &&
		(actorData.lastState & STATE::ON_FLOOR)
	)
	{
		actorData.permissions |= PERMISSION::UPDATE;
	}






}















template <typename T>
uint8 GetNextMeleeAction
(
	T & activeActorData,
	T & actorData
)
{
	uint8 action = 0;

	auto & gamepad = GetGamepad(actorData.newPlayerIndex);

	auto tiltDirection = GetRelativeTiltDirection(actorData);

	auto inAir = (activeActorData.state & STATE::IN_AIR);


	auto lockOn = (gamepad.buttons[0] & GetBinding(BINDING::LOCK_ON));



	switch (actorData.character)
	{
		case CHARACTER::DANTE:
		{
			using namespace ACTION_DANTE;

			// @Todo: Use GetMeleeWeapon.
			auto weapon = actorData.newWeapons[actorData.meleeWeaponIndex];

			switch (weapon)
			{
				case WEAPON::REBELLION:
				{
					if (inAir)
					{
						action = REBELLION_HELM_BREAKER;
					}
					else
					{
						action = REBELLION_COMBO_1_PART_1;

						if (lockOn)
						{
							if (tiltDirection == TILT_DIRECTION::UP)
							{
								action = REBELLION_STINGER_LEVEL_2;
							}
							else if (tiltDirection == TILT_DIRECTION::DOWN)
							{
								action = REBELLION_HIGH_TIME;
							}
						}
					}

					break;
				}
				case WEAPON::CERBERUS:
				{
					if (inAir)
					{
						action = CERBERUS_SWING;
					}
					else
					{
						action = CERBERUS_COMBO_1_PART_1;

						if (lockOn)
						{
							if (tiltDirection == TILT_DIRECTION::UP)
							{
								action = CERBERUS_REVOLVER_LEVEL_2;
							}
							else if (tiltDirection == TILT_DIRECTION::DOWN)
							{
								action = CERBERUS_WINDMILL;
							}
						}
					}

					break;
				}
				case WEAPON::AGNI_RUDRA:
				{
					if (inAir)
					{
						action = AGNI_RUDRA_AERIAL_CROSS;
					}
					else
					{
						action = AGNI_RUDRA_COMBO_1_PART_1;

						if (lockOn)
						{
							if (tiltDirection == TILT_DIRECTION::UP)
							{
								action = AGNI_RUDRA_JET_STREAM_LEVEL_3;
							}
							else if (tiltDirection == TILT_DIRECTION::DOWN)
							{
								action = AGNI_RUDRA_WHIRLWIND;
							}
						}
					}

					break;
				}
				case WEAPON::NEVAN:
				{
					if (inAir)
					{
						action = NEVAN_AIR_PLAY;
					}
					else
					{
						action = NEVAN_TUNE_UP;

						if (lockOn)
						{
							if (tiltDirection == TILT_DIRECTION::UP)
							{
								action = NEVAN_REVERB_SHOCK_LEVEL_2;
							}
							else if (tiltDirection == TILT_DIRECTION::DOWN)
							{
								action = NEVAN_BAT_RIFT_LEVEL_1;
							}
						}
					}

					break;
				}
				case WEAPON::BEOWULF_DANTE:
				{
					if (inAir)
					{
						action = BEOWULF_KILLER_BEE;
					}
					else
					{
						action = BEOWULF_COMBO_1_PART_1;

						if (lockOn)
						{
							if (tiltDirection == TILT_DIRECTION::UP)
							{
								action = BEOWULF_STRAIGHT_LEVEL_2;
							}
							else if (tiltDirection == TILT_DIRECTION::DOWN)
							{
								action = BEOWULF_RISING_DRAGON;
							}
						}
					}

					break;
				}
			}

			break;
		}
		case CHARACTER::VERGIL:
		{
			using namespace ACTION_VERGIL;

			// @Todo: Use GetMeleeWeapon.
			auto weapon = actorData.newWeapons[actorData.activeMeleeWeaponIndex];

			switch (weapon)
			{
				case WEAPON::YAMATO_VERGIL:
				{
					if (inAir)
					{
						action = YAMATO_AERIAL_RAVE_PART_1;
					}
					else
					{
						action = YAMATO_COMBO_PART_1;

						if (lockOn)
						{
							if (tiltDirection == TILT_DIRECTION::UP)
							{
								action = YAMATO_RAPID_SLASH_LEVEL_2;
							}
							else if (tiltDirection == TILT_DIRECTION::DOWN)
							{
								action = YAMATO_UPPER_SLASH_PART_1;
							}
						}
					}

					break;
				}
				case WEAPON::BEOWULF_VERGIL:
				{
					if (inAir)
					{
						action = BEOWULF_STARFALL_LEVEL_2;
					}
					else
					{
						action = BEOWULF_COMBO_PART_1;

						if (lockOn)
						{
							if (tiltDirection == TILT_DIRECTION::UP)
							{
								action = BEOWULF_LUNAR_PHASE_LEVEL_2;
							}
							else if (tiltDirection == TILT_DIRECTION::DOWN)
							{
								action = BEOWULF_RISING_SUN;
							}
						}
					}

					break;
				}
				case WEAPON::YAMATO_FORCE_EDGE:
				{
					if (inAir)
					{
						action = YAMATO_FORCE_EDGE_HELM_BREAKER_LEVEL_2;
					}
					else
					{
						action = YAMATO_FORCE_EDGE_COMBO_PART_1;

						if (lockOn)
						{
							if (tiltDirection == TILT_DIRECTION::UP)
							{
								action = YAMATO_FORCE_EDGE_STINGER_LEVEL_2;
							}
							else if (tiltDirection == TILT_DIRECTION::DOWN)
							{
								action = YAMATO_FORCE_EDGE_HIGH_TIME;
							}
						}
					}

					break;
				}
			}

			break;
		}
	}



	return action;
}

uint8 GetNextMeleeAction
(
	CharacterData & activeCharacterData,
	NewActorData & activeNewActorData,
	CharacterData & characterData,
	NewActorData & newActorData
)
{
	if
	(
		!(
			(activeCharacterData.character < CHARACTER::MAX) &&
			(characterData.character < CHARACTER::MAX)
		)
	)
	{
		return 0;
	}

	IntroduceData(activeNewActorData.baseAddr, activeActorData, PlayerActorData, return 0);
	IntroduceData(newActorData.baseAddr      , actorData      , PlayerActorData, return 0);

	return GetNextMeleeAction
	(
		activeActorData,
		actorData
	);
}



template <typename T>
void SetNextMeleeAction
(
	T & activeActorData,
	T & actorData
)
{
	auto action = GetNextMeleeAction
	(
		activeActorData,
		actorData
	);

	if (action > 0)
	{
		actorData.bufferedAction = action;
	}
}

void SetNextMeleeAction
(
	CharacterData & activeCharacterData,
	NewActorData & activeNewActorData,
	CharacterData & characterData,
	NewActorData & newActorData
)
{
	if
	(
		!(
			(activeCharacterData.character < CHARACTER::MAX) &&
			(characterData.character < CHARACTER::MAX)
		)
	)
	{
		return;
	}

	IntroduceData(activeNewActorData.baseAddr, activeActorData, PlayerActorData, return);
	IntroduceData(newActorData.baseAddr      , actorData      , PlayerActorData, return);

	return SetNextMeleeAction
	(
		activeActorData,
		actorData
	);
}




























template <typename T>
uint8 GetNextStyleAction
(
	T & activeActorData,
	T & actorData
)
{
	uint8 action = 0;

	auto & gamepad = GetGamepad(actorData.newPlayerIndex);

	auto tiltDirection = GetRelativeTiltDirection(actorData);

	auto inAir = (activeActorData.state & STATE::IN_AIR);

	auto lockOn = (gamepad.buttons[0] & GetBinding(BINDING::LOCK_ON));



	if (actorData.character != CHARACTER::DANTE)
	{
		return 0;
	}

	using namespace ACTION_DANTE;

	if (actorData.style == STYLE::SWORDMASTER)
	{
		// @Todo: Use GetMeleeWeapon.
		auto weapon = actorData.newWeapons[actorData.meleeWeaponIndex];

		switch (weapon)
		{
			case WEAPON::REBELLION:
			{
				if (inAir)
				{
					action = REBELLION_AERIAL_RAVE_PART_1;
				}
				else
				{
					action = REBELLION_PROP_SHREDDER_1;

					if (lockOn)
					{
						if (tiltDirection == TILT_DIRECTION::UP)
						{
							action = REBELLION_SWORD_PIERCE;
						}
						else if (tiltDirection == TILT_DIRECTION::DOWN)
						{
							action = REBELLION_DANCE_MACABRE_PART_1;
						}
					}
				}

				break;
			}
			case WEAPON::CERBERUS:
			{
				if (inAir)
				{
					action = CERBERUS_FLICKER;
				}
				else
				{
					action = CERBERUS_AIR_FLICKER;

					if (lockOn)
					{
						if (tiltDirection == TILT_DIRECTION::UP)
						{
							action = CERBERUS_CRYSTAL;
						}
						else if (tiltDirection == TILT_DIRECTION::DOWN)
						{
							action = CERBERUS_ICE_AGE;
						}
					}
				}

				break;
			}
			case WEAPON::AGNI_RUDRA:
			{
				if (inAir)
				{
					action = AGNI_RUDRA_SKY_DANCE_PART_1;
				}
				else
				{
					action = AGNI_RUDRA_CROSSED_SWORDS;

					if (lockOn)
					{
						if (tiltDirection == TILT_DIRECTION::UP)
						{
							action = AGNI_RUDRA_CRAWLER;
						}
						else if (tiltDirection == TILT_DIRECTION::DOWN)
						{
							action = AGNI_RUDRA_TWISTER;
						}
					}
				}

				break;
			}
			case WEAPON::NEVAN:
			{
				if (inAir)
				{
					action = NEVAN_AIR_SLASH_PART_1;
				}
				else
				{
					action = NEVAN_SLASH;

					if (lockOn)
					{
						if (tiltDirection == TILT_DIRECTION::UP)
						{
							action = NEVAN_FEEDBACK;
						}
						else if (tiltDirection == TILT_DIRECTION::DOWN)
						{
							action = NEVAN_DISTORTION;
						}
					}
				}

				break;
			}
			case WEAPON::BEOWULF_DANTE:
			{
				if (inAir)
				{
					action = BEOWULF_THE_HAMMER;

					if (lockOn)
					{
						if (tiltDirection == TILT_DIRECTION::UP)
						{
							action = BEOWULF_AIR_VOLCANO;
						}
					}
				}
				else
				{
					action = BEOWULF_ZODIAC;

					if (lockOn)
					{
						if (tiltDirection == TILT_DIRECTION::UP)
						{
							action = BEOWULF_VOLCANO;
						}
						else if (tiltDirection == TILT_DIRECTION::DOWN)
						{
							action = BEOWULF_REAL_IMPACT;
						}
					}
				}

				break;
			}
		}
	}
	else if (actorData.style == STYLE::GUNSLINGER)
	{
		// @Todo: Use GetRangedWeapon.
		auto weapon = actorData.newWeapons[actorData.rangedWeaponIndex];

		switch (weapon)
		{
			case WEAPON::EBONY_IVORY:
			{
				if (inAir)
				{
					action = EBONY_IVORY_RAIN_STORM;
				}
				else
				{
					action = EBONY_IVORY_TWOSOME_TIME;
				}

				break;
			}
			case WEAPON::SHOTGUN:
			{
				if (inAir)
				{
					action = SHOTGUN_AIR_FIREWORKS;
				}
				else
				{
					action = SHOTGUN_FIREWORKS;

					if (lockOn)
					{
						if (tiltDirection == TILT_DIRECTION::UP)
						{
							action = SHOTGUN_GUN_STINGER;
						}
					}
				}

				break;
			}
			case WEAPON::ARTEMIS:
			{
				if (inAir)
				{
					action = ARTEMIS_AIR_MULTI_LOCK_SHOT;
				}
				else
				{
					action = ARTEMIS_MULTI_LOCK_SHOT;

					if (lockOn)
					{
						if (tiltDirection == TILT_DIRECTION::UP)
						{
							action = ARTEMIS_SPHERE;
						}
					}
				}

				break;
			}
			case WEAPON::SPIRAL:
			{
				if (inAir)
				{
					action = 0;
				}
				else
				{
					action = SPIRAL_TRICK_SHOT;

					if (lockOn)
					{
						if (tiltDirection == TILT_DIRECTION::UP)
						{
							action = SPIRAL_SNIPER;
						}
					}
				}

				break;
			}
			case WEAPON::KALINA_ANN:
			{
				if (inAir)
				{
					action = 0;
				}
				else
				{
					action = KALINA_ANN_HYSTERIC;

					if (lockOn)
					{
						if (tiltDirection == TILT_DIRECTION::UP)
						{
							action = KALINA_ANN_GRAPPLE;
						}
					}
				}

				break;
			}
		}
	}



	return action;
}

uint8 GetNextStyleAction
(
	CharacterData & activeCharacterData,
	NewActorData & activeNewActorData,
	CharacterData & characterData,
	NewActorData & newActorData
)
{
	if
	(
		!(
			(activeCharacterData.character < CHARACTER::MAX) &&
			(characterData.character < CHARACTER::MAX)
		)
	)
	{
		return 0;
	}

	IntroduceData(activeNewActorData.baseAddr, activeActorData, PlayerActorData, return 0);
	IntroduceData(newActorData.baseAddr      , actorData      , PlayerActorData, return 0);

	return GetNextStyleAction
	(
		activeActorData,
		actorData
	);
}



template <typename T>
void SetNextStyleAction
(
	T & activeActorData,
	T & actorData
)
{
	auto action = GetNextStyleAction
	(
		activeActorData,
		actorData
	);

	if (action > 0)
	{
		actorData.bufferedAction = action;
	}
}

void SetNextStyleAction
(
	CharacterData & activeCharacterData,
	NewActorData & activeNewActorData,
	CharacterData & characterData,
	NewActorData & newActorData
)
{
	if
	(
		!(
			(activeCharacterData.character < CHARACTER::MAX) &&
			(characterData.character < CHARACTER::MAX)
		)
	)
	{
		return;
	}

	IntroduceData(activeNewActorData.baseAddr, activeActorData, PlayerActorData, return);
	IntroduceData(newActorData.baseAddr      , actorData      , PlayerActorData, return);

	return SetNextStyleAction
	(
		activeActorData,
		actorData
	);
}





template <typename T>
void EndMotion(T & actorData)
{
	actorData.eventData[0].event = 2;
}







































template <typename T>
void ToggleInput
(
	T & actorData,
	bool enable
)
{
	actorData.newButtonMask = (enable) ? 0xFFFF : 0;
	actorData.newEnableRightStick = enable;
	actorData.newEnableLeftStick = enable;
}

export template <typename T>
void ToggleActor
(
	T & actorData,
	bool enable
)
{
	auto & newActorData = GetNewActorData
	(
		actorData.newPlayerIndex,
		actorData.newCharacterIndex,
		actorData.newEntityIndex
	);

	newActorData.visibility = (enable) ? Visibility_Default : Visibility_Hide;

	newActorData.enableCollision = enable;





	if (enable)
	{
		actorData.visibility = (g_quicksilver) ? 2 : 1;
	}
	else
	{
		actorData.visibility = 0;
	}




	auto playerIndex    = actorData.newPlayerIndex;
	auto characterIndex = actorData.newCharacterIndex;
	auto entityIndex    = actorData.newEntityIndex;



	auto & playerData = GetPlayerData(playerIndex);


	auto actorBaseAddr = reinterpret_cast<byte8 *>(&actorData);


	// Quicksilver Fix

	// Time-Lag's effect is bound to the actor that triggered it.
	// If we hide the actor the effect is also hidden.

	if
	(
		!enable &&
		g_quicksilver &&
		(actorBaseAddr == g_playerActorBaseAddrs[2]) &&
		(actorData.newCharacterIndex != playerData.activeCharacterIndex)
	)
	{
		newActorData.visibility = Visibility_Default;

		actorData.visibility = 0;
	}

















	if
	(
		enable &&
		!actorData.doppelganger
	)
	{
		actorData.shadow = 1;
	}
	else
	{
		actorData.shadow = 0;
	}

	actorData.lastShadow = 0;

	ToggleInput(actorData, enable);
}

export void ToggleActor
(
	uint32 index,
	bool enable
)
{
	IntroducePlayerActorData(actorBaseAddr, g_playerActorBaseAddrs[index], actorData, return);

	ToggleActor(actorData, enable);
}







void ToggleActor
(
	CharacterData & characterData,
	NewActorData & newActorData,
	bool enable
)
{
	if (characterData.character == CHARACTER::BOSS_LADY)
	{
		auto & actorData = *reinterpret_cast<EnemyActorDataLady *>(newActorData.baseAddr);

		newActorData.visibility = (enable) ? Visibility_Default : Visibility_Hide;

		newActorData.enableCollision = enable;
	}
	else if (characterData.character == CHARACTER::BOSS_VERGIL)
	{
		auto & actorData = *reinterpret_cast<EnemyActorDataVergil *>(newActorData.baseAddr);

		newActorData.visibility = (enable) ? Visibility_Default : Visibility_Hide;

		newActorData.enableCollision = enable;
	}
	else
	{
		auto & actorData = *reinterpret_cast<PlayerActorData *>(newActorData.baseAddr);

		ToggleActor(actorData, enable);
	}
};







template <typename T>
void CommissionActor(T & actorData)
{
	LogFunction(actorData.operator byte8 *());

	auto & playerData = GetPlayerData(actorData);

	if
	(
		(actorData.newCharacterIndex == playerData.activeCharacterIndex) &&
		(actorData.newEntityIndex == ENTITY::MAIN)
	)
	{
		ToggleActor(actorData, true);

		if (actorData.newPlayerIndex == 0)
		{
			SetMainActor(actorData);
		}
	}
	else
	{
		ToggleActor(actorData, false);
	}

	[&]()
	{
		IntroduceData(g_playerActorBaseAddrs[0], mainActorData, PlayerActorData, return);

		CopyState
		(
			mainActorData,
			actorData,
			CopyStateFlags_EventData |
			CopyStateFlags_Mode
		);
	}();










	// if (actorData.mode == ACTOR_MODE::MISSION_19)
	// {
	// 	actorData.mode = ACTOR_MODE::DEFAULT;
	// }
}


































export template <typename T>
struct GetCharacterId
{
	enum
	{
		value =
		(TypeMatch<T, PlayerActorDataDante >::value) ? CHARACTER::DANTE  :
		(TypeMatch<T, PlayerActorDataBob   >::value) ? CHARACTER::BOB    :
		(TypeMatch<T, PlayerActorDataLady  >::value) ? CHARACTER::LADY   :
		(TypeMatch<T, PlayerActorDataVergil>::value) ? CHARACTER::VERGIL :
		0
	};
};








struct CharacterModelData
{
	uint8 character;
	uint8 costume;
	uint16 costumeFileId;
	bool coat;

	template <typename T>
	void Update(T & actorData);
};

template <typename T>
void CharacterModelData::Update(T & actorData)
{
	character = (actorData.newForceFiles) ? actorData.newForceFilesCharacter : static_cast<uint8>(actorData.character);
	if (character >= CHARACTER::MAX)
	{
		character = 0;
	}
	//costume = actorData.costume;

	costume = (actorData.newForceFiles) ? actorData.newForceFilesCostume : actorData.costume;



	costumeFileId = 0;
	coat = false;

	switch (character)
	{
		case CHARACTER::DANTE:
		{
			if (costume >= COSTUME::MAX_DANTE)
			{
				costume = 0;
			}

			costumeFileId = costumeFileIdsDante[costume];

			switch (costume)
			{
				case COSTUME::DANTE_DEFAULT:
				case COSTUME::DANTE_DEFAULT_TORN:
				case COSTUME::DANTE_DMC1:
				case COSTUME::DANTE_SPARDA:
				case COSTUME::DANTE_DEFAULT_TORN_INFINITE_MAGIC_POINTS:
				case COSTUME::DANTE_SPARDA_INFINITE_MAGIC_POINTS:
				{
					coat = true;

					break;
				}
			}

			break;
		}
		case CHARACTER::BOB:
		{
			if (costume >= COSTUME::MAX_BOB)
			{
				costume = 0;
			}
			costumeFileId = costumeFileIdsBob[costume];
			coat = false;
			break;
		}
		case CHARACTER::LADY:
		{
			if (costume >= COSTUME::MAX_LADY)
			{
				costume = 0;
			}
			costumeFileId = costumeFileIdsLady[costume];
			coat = false;
			break;
		}
		case CHARACTER::VERGIL:
		{
			if (costume >= COSTUME::MAX_VERGIL)
			{
				costume = 0;
			}
			costumeFileId = costumeFileIdsVergil[costume];

			switch (costume)
			{
				case COSTUME::VERGIL_DEFAULT:
				case COSTUME::VERGIL_DEFAULT_INFINITE_MAGIC_POINTS:
				case COSTUME::VERGIL_NERO_ANGELO:
				case COSTUME::VERGIL_NERO_ANGELO_INFINITE_MAGIC_POINTS:
				{
					coat = true;

					break;
				}
			}

			break;
		}
	}
}





// @Todo: Move.
void ToggleFixWeaponShadows(bool enable)
{
	LogFunction(enable);

	// Rebellion
	WriteAddress((appBaseAddr + 0x2313A6), (enable) ? (appBaseAddr + 0x2313A8) : (appBaseAddr + 0x231419), 2);
	/*
	dmc3.exe+2313A6 - 75 71    - jne dmc3.exe+231419
	dmc3.exe+2313A8 - 49 8B 10 - mov rdx,[r8]
	*/

	// Cerberus
	WriteAddress((appBaseAddr + 0x22F23C), (enable) ? (appBaseAddr + 0x22F23E) : (appBaseAddr + 0x22F2A3), 2);
	/*
	dmc3.exe+22F23C - 75 65    - jne dmc3.exe+22F2A3
	dmc3.exe+22F23E - 48 8B 11 - mov rdx,[rcx]
	*/

	// Agni & Rudra
	WriteAddress((appBaseAddr + 0x227B6F), (enable) ? (appBaseAddr + 0x227B71) : (appBaseAddr + 0x227BDB), 2);
	/*
	dmc3.exe+227B6F - 75 6A    - jne dmc3.exe+227BDB
	dmc3.exe+227B71 - 48 8B 11 - mov rdx,[rcx]
	*/

	// Nevan
	WriteAddress((appBaseAddr + 0x22A4EC), (enable) ? (appBaseAddr + 0x22A4EE) : (appBaseAddr + 0x22A560), 2);
	/*
	dmc3.exe+22A4EC - 75 72    - jne dmc3.exe+22A560
	dmc3.exe+22A4EE - 49 8B 10 - mov rdx,[r8]
	*/

	// Ebony & Ivory
	WriteAddress((appBaseAddr + 0x22B2FD), (enable) ? (appBaseAddr + 0x22B303) : (appBaseAddr + 0x22B40D), 6);
	/*
	dmc3.exe+22B2FD - 0F85 0A010000 - jne dmc3.exe+22B40D
	dmc3.exe+22B303 - 48 8B 01      - mov rax,[rcx]
	*/

	// Shotgun
	WriteAddress((appBaseAddr + 0x23096E), (enable) ? (appBaseAddr + 0x230974) : (appBaseAddr + 0x230A0D), 6);
	/*
	dmc3.exe+23096E - 0F85 99000000 - jne dmc3.exe+230A0D
	dmc3.exe+230974 - 48 8B 01      - mov rax,[rcx]
	*/

	// Artemis
	WriteAddress((appBaseAddr + 0x22C770), (enable) ? (appBaseAddr + 0x22C776) : (appBaseAddr + 0x22C811), 6);
	/*
	dmc3.exe+22C770 - 0F85 9B000000 - jne dmc3.exe+22C811
	dmc3.exe+22C776 - 49 8B 00      - mov rax,[r8]
	*/

	// Spiral
	WriteAddress((appBaseAddr + 0x23026C), (enable) ? (appBaseAddr + 0x230272) : (appBaseAddr + 0x23030B), 6);
	/*
	dmc3.exe+23026C - 0F85 99000000 - jne dmc3.exe+23030B
	dmc3.exe+230272 - 48 8B 01      - mov rax,[rcx]
	*/

	// Kalina Ann
	WriteAddress((appBaseAddr + 0x22BD2E), (enable) ? (appBaseAddr + 0x22BD30) : (appBaseAddr + 0x22BDA1), 2);
	/*
	dmc3.exe+22BD2E - 75 71    - jne dmc3.exe+22BDA1
	dmc3.exe+22BD30 - 48 8B 11 - mov rdx,[rcx]
	*/

	// Yamato
	WriteAddress((appBaseAddr + 0x22E53B), (enable) ? (appBaseAddr + 0x22E541) : (appBaseAddr + 0x22E5EE), 6);
	/*
	dmc3.exe+22E53B - 0F85 AD000000 - jne dmc3.exe+22E5EE
	dmc3.exe+22E541 - 0FB7 45 78    - movzx eax,word ptr [rbp+78]
	*/

	// Yamato & Force Edge
	WriteAddress((appBaseAddr + 0x229B92), (enable) ? (appBaseAddr + 0x229B94) : (appBaseAddr + 0x229C05), 2);
	/*
	dmc3.exe+229B92 - 75 71    - jne dmc3.exe+229C05
	dmc3.exe+229B94 - 49 8B 10 - mov rdx,[r8]
	*/
}










bool IsDanteMeleeWeapon(uint8 weapon)
{
	if
	(
		(weapon >= WEAPON::REBELLION    ) &&
		(weapon <= WEAPON::BEOWULF_DANTE)
	)
	{
		return true;
	}

	return false;
}

bool IsVergilMeleeWeapon(uint8 weapon)
{
	if
	(
		(weapon >= WEAPON::YAMATO_VERGIL) &&
		(weapon <= WEAPON::YAMATO_FORCE_EDGE   )
	)
	{
		return true;
	}

	return false;
}

bool IsDanteRangedWeapon(uint8 weapon)
{
	if
	(
		(weapon >= WEAPON::EBONY_IVORY) &&
		(weapon <= WEAPON::KALINA_ANN )
	)
	{
		return true;
	}

	return false;
}

bool IsDanteWeapon(uint8 weapon)
{
	if (IsDanteMeleeWeapon(weapon))
	{
		return true;
	}
	else if (IsDanteRangedWeapon(weapon))
	{
		return true;
	}

	return false;
}

bool IsVergilWeapon(uint8 weapon)
{
	if (IsVergilMeleeWeapon(weapon))
	{
		return true;
	}

	return false;
}









template <typename T>
bool IsWeaponActive
(
	T & actorData,
	uint8 weapon
)
{
	auto & motionData = actorData.motionData[UPPER_BODY];

	if (motionData.index == 0)
	{
		return false;
	}

	switch (actorData.character)
	{
		case CHARACTER::DANTE:
		{

			if (!IsDanteWeapon(weapon))
			{
				return false;
			}

			if (motionData.group == (MOTION_GROUP_DANTE::REBELLION + weapon))
			{
				return true;
			}
			else if (motionData.group == (MOTION_GROUP_DANTE::SWORDMASTER_REBELLION + weapon))
			{
				return true;
			}

			break;
		}
		case CHARACTER::VERGIL:
		{
			if (!IsVergilWeapon(weapon))
			{
				return false;
			}

			if (motionData.group == (MOTION_GROUP_VERGIL::YAMATO + (weapon - WEAPON::YAMATO_VERGIL)))
			{
				return true;
			}

			break;
		}
	}

	return false;
}

// Character switch instead of specialization so we can use plain ActorData type.

// @Todo: Add remaining idle ranged weapon indices.
export template <typename T>
bool IsWeaponActive(T & actorData)
{
	auto & motionData = actorData.motionData[UPPER_BODY];

	switch (actorData.character)
	{
		case CHARACTER::DANTE:
		{
			if
			(
				(motionData.group >= MOTION_GROUP_DANTE::REBELLION ) &&
				(motionData.group <= MOTION_GROUP_DANTE::KALINA_ANN) &&
				(motionData.index > 0)
			)
			{
				if (motionData.group == MOTION_GROUP_DANTE::EBONY_IVORY)
				{
					switch (motionData.index)
					{
						case 2:
						case 4:
						case 5:
						{
							return false;
						}
					}
				}

				return true;
			}
			else if
			(
				(motionData.group >= MOTION_GROUP_DANTE::SWORDMASTER_REBELLION) &&
				(motionData.group <= MOTION_GROUP_DANTE::GUNSLINGER_KALINA_ANN)
			)
			{
				return true;
			}

			break;
		}
		case CHARACTER::BOB:
		{
			if
			(
				(motionData.group == MOTION_GROUP_BOB::YAMATO ) &&
				(motionData.index > 0)
			)
			{
				return true;
			}

			break;
		}
		case CHARACTER::VERGIL:
		{
			if
			(
				(motionData.group >= MOTION_GROUP_VERGIL::YAMATO    ) &&
				(motionData.group <= MOTION_GROUP_VERGIL::YAMATO_FORCE_EDGE) &&
				(motionData.index > 0)
			)
			{
				return true;
			}
			else if
			(
				(motionData.group >= MOTION_GROUP_VERGIL::NERO_ANGELO_YAMATO ) &&
				(motionData.group <= MOTION_GROUP_VERGIL::NERO_ANGELO_BEOWULF) &&
				(motionData.index > 0)
			)
			{
				return true;
			}

			break;
		}
	}

	return false;
}

export template <typename T>
bool IsActive(T & actorData)
{
	auto & motionData = actorData.motionData[UPPER_BODY];

	switch (actorData.character)
	{
		case CHARACTER::DANTE:
		{
			using namespace MOTION_GROUP_DANTE;

			if (motionData.group == BASE)
			{
				// switch (motionData.index)
				// {
				// 	case 0:
				// 	case 1:
				// 	case 2:
				// 	case 3:
				// 	case 4:
				// 	case 5:
				// 	case 7:
				// 	case 8:
				// 	case 9:
				// 	case 17:
				// 	case 31:
				// 	case 32:
				// 	case 38:
				// 	case 39:
				// 	{
				// 		return false;
				// 	}
				// }

				return false;
			}
			else if
			(
				(motionData.group >= DAMAGE) &&
				(motionData.group <= TAUNTS)
			)
			{
				return true;
			}
			// else if (motionData.group == REBELLION)
			// {
			// 	switch (motionData.index)
			// 	{
			// 		case 13:
			// 		{
			// 			return false;
			// 		}
			// 	}

			// 	return true;
			// }
			else if (IsWeaponActive(actorData))
			{
				return true;
			}
			else if
			(
				(motionData.group >= TRICKSTER   ) &&
				(motionData.group <= DOPPELGANGER)
			)
			{
				return true;
			}

			break;
		}
		case CHARACTER::BOB:
		{
			using namespace MOTION_GROUP_BOB;

			// if (motionData.group == BASE)
			// {
			// 	// switch (motionData.index)
			// 	// {
			// 	// 	case 0:
			// 	// 	case 3:
			// 	// 	{
			// 	// 		return false;
			// 	// 	}
			// 	// }

			// 	return true;
			// }
			if
			(
				(motionData.group >= DAMAGE) &&
				(motionData.group <= TAUNTS)
			)
			{
				return true;
			}
			else if (IsWeaponActive(actorData))
			{
				return true;
			}

			break;
		}
		case CHARACTER::LADY:
		{
			using namespace MOTION_GROUP_LADY;

			// if (motionData.group == BASE)
			// {
			// 	switch (motionData.index)
			// 	{
			// 		case 0:
			// 		case 3:
			// 		{
			// 			return false;
			// 		}
			// 	}

			// 	return true;
			// }
			if
			(
				(motionData.group >= DAMAGE) &&
				(motionData.group <= TAUNTS)
			)
			{
				return true;
			}

			break;
		}
		case CHARACTER::VERGIL:
		{
			using namespace MOTION_GROUP_VERGIL;

			// if (motionData.group == BASE)
			// {
			// 	switch (motionData.index)
			// 	{
			// 		case 0:
			// 		case 3:
			// 		{
			// 			return false;
			// 		}
			// 	}

			// 	return true;
			// }
			if
			(
				(motionData.group >= DAMAGE) &&
				(motionData.group <= TAUNTS)
			)
			{
				return true;
			}
			else if (IsWeaponActive(actorData))
			{
				return true;
			}
			else if (motionData.group == DARK_SLAYER)
			{
				return true;
			}

			break;
		}
	}

	return false;
}

#pragma region IsWeaponReady

bool IsMeleeWeaponReady
(
	PlayerActorData & actorData,
	uint8 weapon
)
{
	if (weapon >= WEAPON::MAX)
	{
		return true;
	}

	switch (actorData.character)
	{
		case CHARACTER::DANTE:
		{
			if (actorData.devil)
			{
				if (actorData.sparda)
				{
					if (weapon == WEAPON::BEOWULF_DANTE)
					{
						return false;
					}
				}
				else
				{
					if (actorData.activeDevil == weaponDevilIds[weapon])
					{
						return true;
					}
				}
			}
			else
			{
				if ((weapon == WEAPON::BEOWULF_DANTE) && activeConfig.hideBeowulfDante)
				{
					return false;
				}
			}

			if (IsWeaponActive(actorData, weapon))
			{
				return true;
			}

			old_for_all(uint8, index, MELEE_WEAPON_COUNT_DANTE)
			{
				uint8 weapon2 = (WEAPON::REBELLION + index);

				if (weapon2 == weapon)
				{
					continue;
				}

				if (IsWeaponActive(actorData, weapon2))
				{
					return false;
				}
			}

			if (actorData.devil && actorData.sparda)
			{
				return false;
			}

			if (actorData.meleeWeaponIndex == weapon)
			{
				return true;
			}

			break;
		}
		case CHARACTER::VERGIL:
		{
			if (actorData.devil)
			{
				if (actorData.neroAngelo)
				{
					return false;
				}
				else
				{
					if (actorData.activeDevil == weaponDevilIds[weapon])
					{
						return true;
					}
				}
			}
			else
			{
				if ((weapon == WEAPON::BEOWULF_VERGIL) && activeConfig.hideBeowulfVergil)
				{
					return false;
				}
			}

			if (IsWeaponActive(actorData, weapon))
			{
				return true;
			}

			old_for_all(uint8, index, MELEE_WEAPON_COUNT_VERGIL)
			{
				uint8 weapon2 = (WEAPON::YAMATO_VERGIL + index);

				if (weapon2 == weapon)
				{
					continue;
				}

				if (IsWeaponActive(actorData, weapon2))
				{
					return false;
				}
			}

			if (actorData.activeMeleeWeaponIndex == (weapon - WEAPON::YAMATO_VERGIL))
			{
				return true;
			}

			break;
		}
	}

	return false;
}

bool IsMeleeWeaponReady(WeaponData & weaponData)
{
	IntroducePlayerActorData(actorBaseAddr, weaponData.actorBaseAddr, actorData, return true);

	return IsMeleeWeaponReady(actorData, weaponData.weapon);
}

bool IsRangedWeaponReady
(
	PlayerActorDataDante & actorData,
	uint8 weapon
)
{
	if (IsWeaponActive(actorData, weapon))
	{
		return true;
	}

	old_for_all(uint8, index, RANGED_WEAPON_COUNT_DANTE)
	{
		uint8 weapon2 = (WEAPON::EBONY_IVORY + index);

		if (weapon2 == weapon)
		{
			continue;
		}

		if (IsWeaponActive(actorData, weapon2))
		{
			return false;
		}
	}

	if (actorData.rangedWeaponIndex == weapon)
	{
		return true;
	}

	return false;
}

bool IsRangedWeaponReady(WeaponData & weaponData)
{
	if (!weaponData.actorBaseAddr)
	{
		return true;
	}
	auto & actorData = *reinterpret_cast<PlayerActorDataDante *>(weaponData.actorBaseAddr);

	return IsRangedWeaponReady(actorData, weaponData.weapon);
}

void IsMeleeWeaponReadyVergilFix(PlayerActorData & actorData)
{
	if (actorData.activeMeleeWeaponIndex != actorData.queuedMeleeWeaponIndex)
	{
		uint8 weapon = (WEAPON::YAMATO_VERGIL + static_cast<uint8>(actorData.activeMeleeWeaponIndex));

		if (!IsWeaponActive(actorData, weapon))
		{
			actorData.activeMeleeWeaponIndex = actorData.queuedMeleeWeaponIndex;
		}
	}
}

void ToggleIsWeaponReady(bool enable)
{
	LogFunction(enable);

	static bool run = false;

	static byte8 * IsMeleeWeaponReadyAddr      = 0;
	static byte8 * IsMeleeWeaponReadyShowAddr  = 0;
	static byte8 * IsRangedWeaponReadyAddr     = 0;
	static byte8 * IsRangedWeaponReadyShowAddr = 0;

	// Melee
	{
		if (!run)
		{
			auto func = old_CreateFunction(static_cast<bool(__fastcall *)(WeaponData &)>(IsMeleeWeaponReady), 0, true, false);
			IsMeleeWeaponReadyAddr = func.addr;
		}
	}
	{
		constexpr byte8 sect2[] =
		{
			0x84, 0xC0,                         // test al,al
			0x0F, 0x85, 0x00, 0x00, 0x00, 0x00, // jne dmc3.exe+1FDE10
		};

		if (!run)
		{
			auto func = old_CreateFunction(static_cast<bool(__fastcall *)(WeaponData &)>(IsMeleeWeaponReady), 0, true, false, 0, 0, sizeof(sect2));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
			WriteAddress((func.sect2 + 2), (appBaseAddr + 0x1FDE10), 6);
			IsMeleeWeaponReadyShowAddr = func.addr;
		}
	}

	// Ranged
	{
		if (!run)
		{
			auto func = old_CreateFunction(static_cast<bool(__fastcall *)(WeaponData &)>(IsRangedWeaponReady), 0, true, false);
			IsRangedWeaponReadyAddr = func.addr;
		}
	}
	{
		constexpr byte8 sect2[] =
		{
			0x84, 0xC0,                         // test al,al
			0x0F, 0x85, 0x00, 0x00, 0x00, 0x00, // jne dmc3.exe+1FDE10
		};

		if (!run)
		{
			auto func = old_CreateFunction(static_cast<bool(__fastcall *)(WeaponData &)>(IsRangedWeaponReady), 0, true, false, 0, 0, sizeof(sect2));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
			WriteAddress((func.sect2 + 2), (appBaseAddr + 0x1FDE10), 6);
			IsRangedWeaponReadyShowAddr = func.addr;
		}
	}

	// Rebellion
	{
		auto addr = (appBaseAddr + 0x23162E);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+23162E - E8 ADBDFCFF - call dmc3.exe+1FD3E0
		dmc3.exe+231633 - 84 C0       - test al,al
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			WriteCall(addr, IsMeleeWeaponReadyAddr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Cerberus
	{
		auto addr = (appBaseAddr + 0x22FAD4);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+22FAD4 - E8 07D9FCFF - call dmc3.exe+1FD3E0
		dmc3.exe+22FAD9 - 84 C0       - test al,al
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			WriteCall(addr, IsMeleeWeaponReadyAddr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Agni & Rudra
	{
		auto addr = (appBaseAddr + 0x2288A4);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+2288A4 - E8 374BFDFF      - call dmc3.exe+1FD3E0
		dmc3.exe+2288A9 - 44 0F28 74 24 30 - movaps xmm14,[rsp+30]
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			WriteCall(addr, IsMeleeWeaponReadyAddr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Nevan
	{
		auto addr = (appBaseAddr + 0x22AD2D);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+22AD2D - E8 AE26FDFF    - call dmc3.exe+1FD3E0
		dmc3.exe+22AD32 - 48 8B 74 24 40 - mov rsi,[rsp+40]
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			WriteCall(addr, IsMeleeWeaponReadyAddr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Beowulf
	{
		auto addr = (appBaseAddr + 0x2295B7);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+2295B7 - E8 5448FDFF    - call dmc3.exe+1FDE10
		dmc3.exe+2295BC - 48 8B 7C 24 50 - mov rdi,[rsp+50]
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			WriteCall(addr, IsMeleeWeaponReadyShowAddr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Artemis
	{
		auto addr = (appBaseAddr + 0x22CBC8);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+22CBC8 - E8 4312FDFF    - call dmc3.exe+1FDE10
		dmc3.exe+22CBCD - 48 8B 5C 24 48 - mov rbx,[rsp+48]
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			WriteCall(addr, IsRangedWeaponReadyShowAddr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	run = true;
}

#pragma endregion






































// @Todo: Remove.
template <typename T>
bool SystemButtonCheck(T & actorData)
{
	// switch (activeConfig.Actor.system)
	// {
	// 	case ACTOR_SYSTEM_DOPPELGANGER:
	// 	{
	// 		if (actorData.newIndex == ENTITY::MAIN)
	// 		{
	// 			if (actorData.buttons[0] & GetBinding(BINDING::DEFAULT_CAMERA))
	// 			{
	// 				return false;
	// 			}
	// 		}
	// 		else
	// 		{
	// 			if (!(actorData.buttons[0] & GetBinding(BINDING::DEFAULT_CAMERA)))
	// 			{
	// 				return false;
	// 			}
	// 		}

	// 		break;
	// 	}
	// 	case ACTOR_SYSTEM_CHARACTER_SWITCHER:
	// 	{
	// 		if (actorData.buttons[0] & GetBinding(BINDING::DEFAULT_CAMERA))
	// 		{
	// 			return false;
	// 		}

	// 		break;
	// 	}
	// }

	return true;
}




export template <typename T>
bool IsNeroAngelo(T & actorData)
{
	return
	(
		(actorData.character == CHARACTER::VERGIL) &&
		actorData.neroAngelo &&
		actorData.devil
	);
}













#pragma endregion

#pragma region File

// struct FileDataHelper
// {
// 	uint16 fileDataId; // file data id index
// 	uint16 fileId; // cache file id index
// };

struct FileDataHelper
{
	uint16 fileDataIndex; // file data id index
	uint16 cacheFileIndex; // cache file id index
};

// export void File_UpdateFileData
// (
// 	uint16 fileDataIndex,
// 	uint16 cacheFileIndex
// )




constexpr FileDataHelper fileDataHelperDante[] =
{
	{ 0  , pl000         },
	{ 200, pl005         },
	{ 201, pl006         },
	{ 202, pl007         },
	{ 203, pl008         },
	{ 204, pl009         },
	{ 205, pl017         },
	{ 140, plwp_sword    },
	{ 141, plwp_nunchaku },
	{ 142, plwp_2sword   },
	{ 143, plwp_guitar   },
	{ 144, plwp_fight    },
	{ 145, plwp_gun      },
	{ 146, plwp_shotgun  },
	{ 147, plwp_laser    },
	{ 148, plwp_rifle    },
	{ 149, plwp_ladygun  },
};

constexpr FileDataHelper fileDataHelperBob[] =
{
	{ 1  , pl001            },
	{ 207, pl010            },
	{ 169, plwp_vergilsword },
};

constexpr FileDataHelper fileDataHelperLady[] =
{
	{ 2, pl002 },
};

constexpr FileDataHelper fileDataHelperVergil[] =
{
	{ 3  , pl021               },
	{ 221, pl010               },
	{ 222, pl014               },
	{ 223, pl025               },
	{ 196, plwp_newvergilsword },
	{ 189, plwp_newvergilfight },
	{ 198, plwp_forceedge      },
	{ 187, plwp_nerosword      },
};

template<uint8 itemCount>
void UpdateFileDataFunction(const FileDataHelper(&items)[itemCount])
{
	old_for_all(uint8, itemIndex, itemCount)
	{
		auto & item = items[itemIndex];

		File_UpdateFileData
		(
			item.fileDataIndex,
			item.cacheFileIndex
		);
	}
}

template <typename T>
void UpdateFileData(T & actorData)
{
	if constexpr (TypeMatch<T, PlayerActorDataDante>::value)
	{
		UpdateFileDataFunction(fileDataHelperDante);
	}
	else if constexpr (TypeMatch<T, PlayerActorDataBob>::value)
	{
		UpdateFileDataFunction(fileDataHelperBob);
	}
	else if constexpr (TypeMatch<T, PlayerActorDataLady>::value)
	{
		UpdateFileDataFunction(fileDataHelperLady);
	}
	else if constexpr (TypeMatch<T, PlayerActorDataVergil>::value)
	{
		UpdateFileDataFunction(fileDataHelperVergil);
	}
}

















template <typename T>
void UpdateCostumeFileData(T & actorData)
{
	IntroduceSessionData();

	CharacterModelData characterModelData;

	characterModelData.Update(actorData);

	auto & character     = characterModelData.character;
	auto & costume       = characterModelData.costume;
	auto & costumeFileId = characterModelData.costumeFileId;
	auto & coat          = characterModelData.coat;

	File_UpdateFileData(static_cast<uint16>(character), costumeFileId);

	if constexpr (TypeMatch<T, PlayerActorDataDante>::value)
	{
		uint16 swordFileId = plwp_sword;

		if (sessionData.unlockDevilTrigger)
		{
			swordFileId = plwp_sword2;
		}

		if (actorData.sparda)
		{
			swordFileId = plwp_sword3;
		}

		File_UpdateFileData(140, swordFileId);
	}
}

#pragma endregion

#pragma region Actor Management

template <typename T>
void InitActor
(
	T & actorData,
	ActiveMissionActorData & activeMissionActorData
)
{
	if constexpr      (TypeMatch<T, PlayerActorDataDante >::value) { func_217B90(actorData, activeMissionActorData); }
	else if constexpr (TypeMatch<T, PlayerActorDataBob   >::value) { func_226F10(actorData, activeMissionActorData); }
	else if constexpr (TypeMatch<T, PlayerActorDataLady  >::value) { func_219660(actorData, activeMissionActorData); }
	else if constexpr (TypeMatch<T, PlayerActorDataVergil>::value) { func_223CB0(actorData, activeMissionActorData); }
}

template <typename T>
void UpdateActor(T & actorData)
{
	if constexpr      (TypeMatch<T, PlayerActorDataDante >::value) { func_212BE0(actorData); }
	else if constexpr (TypeMatch<T, PlayerActorDataBob   >::value) { func_225D70(actorData); }
	else if constexpr (TypeMatch<T, PlayerActorDataLady  >::value) { func_219260(actorData); }
	else if constexpr (TypeMatch<T, PlayerActorDataVergil>::value) { func_220970(actorData); }
}

template <typename T>
void InitModel
(
	T & actorData,
	uint32 modelIndex
)
{
	func_8A000
	(
		actorData.newModelData[modelIndex],
		actorData.motionArchives[0],
		actorData.newModelPhysicsMetadataPool[modelIndex]
	);

	actorData.newModelData[modelIndex].Motion.init = false;

	// Not sure if required, but legit.
	{
		auto dest = reinterpret_cast<byte8 *>(actorData.newModelPhysicsMetadataPool[0][(1 + modelIndex)]);
		*reinterpret_cast<RecoveryData **>(dest + 0x100) = &actorData.newRecoveryData[modelIndex];
	}

	auto & recoveryData = actorData.newRecoveryData[modelIndex];
	recoveryData.init = false;
	SetMemory(recoveryData.data, 0, 32);

	// Log("InitModel for %llX", actorData.operator byte8 *());
	// Log("character %u", actorData.character);






	

	// Dante file is different.

	auto file = File_staticFiles[pl000][5]; // @Todo: Update.

	func_594B0
	(
		actorData.newBodyPartData[modelIndex][UPPER_BODY],
		file,
		UPPER_BODY,
		0,
		actorData.motionArchives,
		&actorData.newModelData[modelIndex].funcAddrs,
		actorData.newModelPhysicsMetadataPool[modelIndex],
		&actorData.motionSpeed,
		&actorData.collisionData
	);

	func_594B0
	(
		actorData.newBodyPartData[modelIndex][LOWER_BODY],
		file,
		LOWER_BODY,
		0,
		actorData.motionArchives,
		&actorData.newModelData[modelIndex].funcAddrs,
		actorData.newModelPhysicsMetadataPool[modelIndex],
		&actorData.motionSpeed,
		0
	);

	auto dest = func_8A520(actorData.newModelData[modelIndex]);
	func_30E630(dest, 0);
}

// @Todo: Add LogFunctionStart and verbose switch.
template <typename T>
void UpdateModel(T & actorData)
{
	if constexpr (debug)
	{
		LogFunction(actorData.operator byte8 *());
	}

	CharacterModelData characterModelData;

	characterModelData.Update(actorData);

	auto & character     = characterModelData.character;
	auto & costume       = characterModelData.costume;
	auto & costumeFileId = characterModelData.costumeFileId;
	auto & coat          = characterModelData.coat;

	auto & file = File_staticFiles[costumeFileId];

	byte8 * modelFile   = 0;
	byte8 * textureFile = 0;
	byte8 * shadowFile  = 0;
	byte8 * physicsFile = 0;

	uint8 modelIndex    = 0;
	uint8 submodelIndex = 0;

	// Main

	modelFile   = file[1];
	textureFile = file[0];
	shadowFile  = file[8];

	if ((character == CHARACTER::LADY) && (costume == COSTUME::LADY_LEATHER_JUMPSUIT))
	{
		modelFile   = file[32];
		textureFile = file[31];
		shadowFile  = file[16];
	}

	RegisterModel
	(
		actorData.newModelData[modelIndex],
		modelFile,
		textureFile
	);

	RegisterShadow
	(
		actorData.newModelData[modelIndex],
		actorData.newModelShadowData[modelIndex],
		shadowFile
	);

	{
		auto g_vertices = reinterpret_cast<vec4 *>(appBaseAddr + 0x58B260);

		old_for_all(uint8, index, 6)
		{
			uint8 off = (index * 3);
			actorData.modelMetadata[index].count = 4;
			actorData.modelMetadata[index].vertices[0] = g_vertices[(off + 0)];
			actorData.modelMetadata[index].vertices[1] = g_vertices[(off + 1)];
			actorData.modelMetadata[index].vertices[2] = g_vertices[(off + 2)];
		}
	}

	// Coat

	modelFile   = file[12];
	textureFile = file[0 ];
	//shadowFile  = (coat) ? file[14] : 0;
	shadowFile  = file[14];
	physicsFile = file[13];

	if ((character == CHARACTER::LADY) && (costume == COSTUME::LADY_LEATHER_JUMPSUIT))
	{
		modelFile   = file[17];
		textureFile = file[31];
		physicsFile = file[18];
	}

	// Log("reach here. 1");



	RegisterModel
	(
		actorData.newSubmodelData[submodelIndex],
		modelFile,
		textureFile
	);


	// Log("reach here. 2");

	func_8A000
	(
		actorData.newSubmodelData[submodelIndex],
		0,
		&actorData.submodelPhysicsMetadataPool[0]
	);

	// Log("reach here. 3");

	actorData.newSubmodelInit[submodelIndex] = true;

	if ((character == CHARACTER::LADY))
	{
		return;
	}

	if (coat && shadowFile)
	{
		RegisterShadow
		(
			actorData.newSubmodelData[submodelIndex],
			actorData.newSubmodelShadowData[submodelIndex],
			shadowFile
		);
	}

	// Log("reach here. 4");

	actorData.newSubmodelInit[submodelIndex] = true;

	RegisterPhysics
	(
		physicsFile,
		&actorData.submodelPhysicsData,
		&actorData.submodelPhysicsMetadataPool[0]
	);

	// Log("reach here. 5");

	func_2CA2F0
	(
		actorData.submodelPhysicsData,
		actorData.newModelPhysicsMetadataPool[modelIndex],
		(appBaseAddr + ((coat) ? 0x58B380 : 0x58B054)),
		actorData.modelMetadata,
		(coat) ? 6 : 1
	);

	// Log("reach here. 6");

	if (coat)
	{
		auto g_vertices = reinterpret_cast<vec4 *>(appBaseAddr + 0x35D580);
		auto & submodelPhysicsMetadata = *actorData.submodelPhysicsMetadataPool[0];

		submodelPhysicsMetadata.vertices[0] = g_vertices[0];
		submodelPhysicsMetadata.vertices[1] = g_vertices[1];
		submodelPhysicsMetadata.vertices[2] = g_vertices[2];
		submodelPhysicsMetadata.vertices[3] = g_vertices[3];
	}
	else
	{
		auto g_vertices = reinterpret_cast<vec4 *>(appBaseAddr + 0x58B260);

		actorData.modelMetadata[0].count = 4;
		actorData.modelMetadata[0].vertices[0] = g_vertices[23];
		actorData.modelMetadata[0].vertices[1] = g_vertices[24];
		actorData.modelMetadata[0].vertices[2] = g_vertices[25];
	}

	// Log("reach here. 7");
}

template <typename T>
void UpdateDevilModel
(
	T & actorData,
	uint8 devil,
	uint8 devilModelIndex
)
{
	if constexpr (debug)
	{
		LogFunction(actorData.operator byte8 *());
	}

	auto devilFileId = devilFileIdsDante[devil];

	auto & file = File_staticFiles[devilFileId];

	byte8 * modelFile = 0;
	byte8 * textureFile = 0;
	byte8 * shadowFile = 0;
	byte8 * physicsFile = 0;

	//uint8 modelIndex = (devilModelIndex == 0) ? 1 : 2;
	//uint8 submodelIndex = (devilModelIndex == 0) ? 1 : 3;
	//uint8 devilSubmodelIndex = (devilModelIndex == 0) ? 0 : 2;

	auto & devilModelMetadata = actorData.devilModelMetadata[devil];

	uint8 modelIndex = (1 + devilModelIndex);
	uint8 submodelIndex = (1 + (devilModelIndex * 2));
	uint8 devilSubmodelIndex = (devilModelIndex * 2);

	uint8 modelPhysicsMetadataIndex = 0;
	uint8 devilModelPhysicsMetadataIndex = 0;

	// @Todo: Update.
	auto LinkModelPhysicsData = [&]
	(
		uint8 _devilSubmodelPhysicsLinkDataIndex,
		uint8 _modelPhysicsMetadataIndex,
		uint8 _devilModelPhysicsMetadataIndex
	)
	{
		auto & devilSubmodelPhysicsLinkData = actorData.newDevilSubmodelPhysicsLinkData[devilSubmodelIndex][_devilSubmodelPhysicsLinkDataIndex];

		auto modelPhysicsMetadataAddr = actorData.newModelPhysicsMetadataPool[modelIndex][(modelPhysicsMetadataIndex + _modelPhysicsMetadataIndex)];
		if (!modelPhysicsMetadataAddr)
		{
			Log("LinkModelPhysicsData failed.");
			Log("modelPhysicsMetadataAddr");
			return;
		}
		auto & modelPhysicsMetadata = *modelPhysicsMetadataAddr;

		auto devilModelPhysicsMetadataAddr = actorData.newDevilModelPhysicsMetadataPool[devilModelIndex][(devilModelPhysicsMetadataIndex + _devilModelPhysicsMetadataIndex)];
		if (!devilModelPhysicsMetadataAddr)
		{
			Log("LinkModelPhysicsData failed.");
			Log("devilModelPhysicsMetadataAddr");
			return;
		}
		auto & devilPhysicsMetadata = *devilModelPhysicsMetadataAddr;

		devilSubmodelPhysicsLinkData.enable = 1;
		devilSubmodelPhysicsLinkData.physicsData = modelPhysicsMetadata.physicsData;
		CopyMemory(devilSubmodelPhysicsLinkData.data, (appBaseAddr + 0x35D580), 64);

		devilPhysicsMetadata.physicsLinkData = &devilSubmodelPhysicsLinkData;
	};

	actorData.newDevilModels[modelIndex] = devil;

	// Main

	modelFile = file[1];
	textureFile = file[0];

	if (devil == DEVIL::AGNI_RUDRA)
	{
		shadowFile = file[2];
	}
	else if
	(
		(devil == DEVIL::CERBERUS) ||
		(devil == DEVIL::BEOWULF ) ||
		(devil == DEVIL::SPARDA  )
	)
	{
		shadowFile = file[4];
	}
	else if
	(
		(devil == DEVIL::REBELLION) ||
		(devil == DEVIL::NEVAN    )
	)
	{
		shadowFile = file[6];
	}

	RegisterModel
	(
		actorData.newModelData[modelIndex],
		modelFile,
		textureFile
	);

	InitModel
	(
		actorData,
		modelIndex
	);

	RegisterShadow
	(
		actorData.newModelData[modelIndex],
		actorData.newModelShadowData[modelIndex],
		shadowFile
	);

	devilModelMetadata.modelIndex = modelIndex;
	devilModelMetadata.modelPhysicsMetadataIndex = ((modelIndex * 24) + modelPhysicsMetadataIndex);

	if (devil == DEVIL::AGNI_RUDRA)
	{
		return;
	}

	// Wings

	modelFile   = file[2];
	textureFile = file[0];
	physicsFile = file[3];

	if
	(
		(devil == DEVIL::REBELLION) ||
		(devil == DEVIL::NEVAN    )
	)
	{
		shadowFile = file[7];
	}
	else if
	(
		(devil == DEVIL::CERBERUS) ||
		(devil == DEVIL::BEOWULF ) ||
		(devil == DEVIL::SPARDA  )
	)
	{
		shadowFile = file[5];
	}

	RegisterModel
	(
		actorData.newSubmodelData[submodelIndex],
		modelFile,
		textureFile
	);

	func_8A000
	(
		actorData.newSubmodelData[submodelIndex],
		0,
		&actorData.newDevilModelPhysicsMetadataPool[devilModelIndex][devilModelPhysicsMetadataIndex]
	);

	RegisterShadow
	(
		actorData.newSubmodelData[submodelIndex],
		actorData.newSubmodelShadowData[submodelIndex],
		shadowFile
	);

	actorData.newSubmodelInit[submodelIndex] = true;

	RegisterPhysics
	(
		physicsFile,
		&actorData.newDevilSubmodelPhysicsData[devilSubmodelIndex],
		&actorData.newDevilModelPhysicsMetadataPool[devilModelIndex][devilModelPhysicsMetadataIndex]
	);

	if
	(
		(devil == DEVIL::REBELLION) ||
		(devil == DEVIL::NEVAN    )
	)
	{
		LinkModelPhysicsData(0, 3, 1 );
		LinkModelPhysicsData(1, 2, 12);
	}
	else if
	(
		(devil == DEVIL::CERBERUS) ||
		(devil == DEVIL::BEOWULF )
	)
	{
		LinkModelPhysicsData(0, 3 , 1);
		LinkModelPhysicsData(1, 6 , 2);
		LinkModelPhysicsData(2, 10, 8);
	}

	devilModelMetadata.devilSubmodelMetadata[0].submodelIndex = submodelIndex;
	devilModelMetadata.devilSubmodelMetadata[0].devilModelPhysicsMetadataIndex = ((devilModelIndex * 36) + devilModelPhysicsMetadataIndex);
	devilModelMetadata.devilSubmodelMetadata[0].devilSubmodelIndex = devilSubmodelIndex;

	submodelIndex++;
	devilModelPhysicsMetadataIndex += 9;
	devilSubmodelIndex++;

	// Coat

	if
	(
	!(
		(devil == DEVIL::REBELLION) ||
		(devil == DEVIL::NEVAN    )
	)
	)
	{
		return;
	}

	modelFile   = file[4];
	textureFile = file[0];
	shadowFile  = file[8];
	physicsFile = file[5];

	RegisterModel
	(
		actorData.newSubmodelData[submodelIndex],
		modelFile,
		textureFile
	);

	func_8A000
	(
		actorData.newSubmodelData[submodelIndex],
		0,
		&actorData.newDevilModelPhysicsMetadataPool[devilModelIndex][devilModelPhysicsMetadataIndex]
	);

	RegisterShadow
	(
		actorData.newSubmodelData[submodelIndex],
		actorData.newSubmodelShadowData[submodelIndex],
		shadowFile
	);

	actorData.newSubmodelInit[submodelIndex] = true;

	RegisterPhysics
	(
		physicsFile,
		&actorData.newDevilSubmodelPhysicsData[devilSubmodelIndex],
		&actorData.newDevilModelPhysicsMetadataPool[devilModelIndex][devilModelPhysicsMetadataIndex]
	);

	func_2CA2F0
	(
		actorData.newDevilSubmodelPhysicsData[devilSubmodelIndex],
		actorData.newModelPhysicsMetadataPool[modelIndex],
		(appBaseAddr + 0x58B380),
		actorData.modelMetadata,
		6
	);

	LinkModelPhysicsData(0, 2 , 1);
	LinkModelPhysicsData(1, 14, 2);

	devilModelMetadata.devilSubmodelMetadata[1].submodelIndex = submodelIndex;
	devilModelMetadata.devilSubmodelMetadata[1].devilModelPhysicsMetadataIndex = ((devilModelIndex * 36) + devilModelPhysicsMetadataIndex);
	devilModelMetadata.devilSubmodelMetadata[1].devilSubmodelIndex = devilSubmodelIndex;
}

void UpdateModelPartitions(PlayerActorData & actorData)
{
	IntroduceSessionData();

	CharacterModelData characterModelData;

	characterModelData.Update(actorData);

	auto & character     = characterModelData.character;
	auto & costume       = characterModelData.costume;
	auto & costumeFileId = characterModelData.costumeFileId;
	auto & coat          = characterModelData.coat;

	auto modelPartitionData = actorData.newModelData[0].modelPartitionData;
	if (!modelPartitionData)
	{
		return;
	}

	bool beowulf = false;

	switch (actorData.character)
	{
		case CHARACTER::DANTE:
		{
			beowulf = IsMeleeWeaponReady(actorData, WEAPON::BEOWULF_DANTE);

			break;
		}
		case CHARACTER::VERGIL:
		{
			beowulf = IsMeleeWeaponReady(actorData, WEAPON::BEOWULF_VERGIL);

			break;
		}
	}

	switch (character)
	{
		case CHARACTER::DANTE:
		{
			switch (costume)
			{
				case COSTUME::DANTE_DEFAULT:
				{
					modelPartitionData[0 ].value = (beowulf) ? 2 : 3; // Hands
					modelPartitionData[1 ].value = (beowulf) ? 3 : 2; // Fists
					modelPartitionData[2 ].value = 3; // Shoulders
					modelPartitionData[3 ].value = (beowulf) ? 2 : 3; // Lower Arms
					modelPartitionData[4 ].value = (beowulf) ? 3 : 2; // Lower Arms Half
					modelPartitionData[5 ].value = (beowulf) ? 3 : 2; // Lower Legs Half
					modelPartitionData[6 ].value = (beowulf) ? 2 : 3; // Lower Legs and Feet
					modelPartitionData[7 ].value = 3; // Upper Legs
					modelPartitionData[8 ].value = 3; // Accessories
					modelPartitionData[9 ].value = 3; // Upper Body
					modelPartitionData[10].value = 3; // Face
					modelPartitionData[11].value = 3; // Hair Base
					modelPartitionData[12].value = 3; // Hair Back Layer 1
					modelPartitionData[13].value = 3; // Hair Back Layer 2
					modelPartitionData[14].value = 3; // Hair Sides
					modelPartitionData[15].value = 3; // Hair Back Layer 3
					modelPartitionData[16].value = 3; // Hair Main

					break;
				}
				case COSTUME::DANTE_DEFAULT_NO_COAT:
				{
					modelPartitionData[0 ].value = (beowulf) ? 2 : 3; // Hands
					modelPartitionData[1 ].value = (beowulf) ? 3 : 2; // Fists
					modelPartitionData[2 ].value = 3; // Upper Body
					modelPartitionData[3 ].value = 2; // Filler
					modelPartitionData[4 ].value = 2; // Filler
					modelPartitionData[5 ].value = (beowulf) ? 3 : 2; // Lower Legs Half
					modelPartitionData[6 ].value = (beowulf) ? 2 : 3; // Lower Legs and Feet
					modelPartitionData[7 ].value = 3; // Upper Legs
					modelPartitionData[8 ].value = 3; // Accessories
					modelPartitionData[9 ].value = 3; // Face
					modelPartitionData[10].value = 3; // Hair Base
					modelPartitionData[11].value = 3; // Hair Back Layer 1
					modelPartitionData[12].value = 3; // Hair Back Layer 2
					modelPartitionData[13].value = 3; // Hair Sides
					modelPartitionData[14].value = 3; // Hair Back Layer 3
					modelPartitionData[15].value = 3; // Hair Main

					break;
				}
				case COSTUME::DANTE_DEFAULT_TORN:
				case COSTUME::DANTE_DEFAULT_TORN_INFINITE_MAGIC_POINTS:
				{
					modelPartitionData[0 ].value = (beowulf) ? 2 : 3; // Hands
					modelPartitionData[1 ].value = (beowulf) ? 3 : 2; // Fists
					modelPartitionData[2 ].value = 3; // Shoulders
					modelPartitionData[3 ].value = (beowulf) ? 2 : 3; // Lower Arms
					modelPartitionData[4 ].value = (beowulf) ? 3 : 2; // Lower Arms Half
					modelPartitionData[5 ].value = (beowulf) ? 3 : 2; // Lower Legs Half
					modelPartitionData[6 ].value = (beowulf) ? 2 : 3; // Lower Legs and Feet
					modelPartitionData[7 ].value = 3; // Upper Legs
					modelPartitionData[8 ].value = 3; // Accessories
					modelPartitionData[9 ].value = 3; // Upper Body
					modelPartitionData[10].value = 3; // Lower Right Arm
					modelPartitionData[11].value = 3; // Face
					modelPartitionData[12].value = 3; // Hair Base
					modelPartitionData[13].value = 3; // Hair Back Layer 1
					modelPartitionData[14].value = 3; // Hair Back Layer 2
					modelPartitionData[15].value = 3; // Hair Sides
					modelPartitionData[16].value = 3; // Hair Back Layer 3
					modelPartitionData[17].value = 3; // Hair Main

					break;
				}
				case COSTUME::DANTE_DMC1:
				{
					modelPartitionData[0 ].value = (beowulf) ? 2 : 3; // Hands
					modelPartitionData[1 ].value = (beowulf) ? 3 : 2; // Fists
					modelPartitionData[2 ].value = 3; // Shoulders and Arms
					modelPartitionData[3 ].value = 2; // Filler
					modelPartitionData[4 ].value = 2; // Filler
					modelPartitionData[5 ].value = (beowulf) ? 3 : 2; // Lower Legs Half
					modelPartitionData[6 ].value = (beowulf) ? 2 : 3; // Lower Legs and Feet
					modelPartitionData[7 ].value = 3; // Upper Legs
					modelPartitionData[8 ].value = 3; // Vest
					modelPartitionData[9 ].value = 3; // Upper Body
					modelPartitionData[10].value = 3; // Face
					modelPartitionData[11].value = 3; // Hair Base
					modelPartitionData[12].value = 3; // Hair Back Layer 1
					modelPartitionData[13].value = 3; // Hair Back Layer 2
					modelPartitionData[14].value = 3; // Hair Back Layer 3
					modelPartitionData[15].value = 3; // Hair Main

					break;
				}
				case COSTUME::DANTE_DMC1_NO_COAT:
				{
					modelPartitionData[0 ].value = (beowulf) ? 2 : 3; // Hands
					modelPartitionData[1 ].value = (beowulf) ? 3 : 2; // Fists
					modelPartitionData[2 ].value = 3; // Upper Body
					modelPartitionData[3 ].value = 2; // Filler
					modelPartitionData[4 ].value = 2; // Filler
					modelPartitionData[5 ].value = (beowulf) ? 3 : 2; // Lower Legs Half
					modelPartitionData[6 ].value = (beowulf) ? 2 : 3; // Lower Legs and Feet
					modelPartitionData[7 ].value = 3; // Upper Legs
					modelPartitionData[8 ].value = 3; // Collar
					modelPartitionData[9 ].value = 3; // Face
					modelPartitionData[10].value = 3; // Hair Base
					modelPartitionData[11].value = 3; // Hair Back Layer 1
					modelPartitionData[12].value = 3; // Hair Back Layer 2
					modelPartitionData[13].value = 3; // Hair Back Layer 3
					modelPartitionData[14].value = 3; // Hair Main

					break;
				}
				case COSTUME::DANTE_SPARDA:
				case COSTUME::DANTE_SPARDA_INFINITE_MAGIC_POINTS:
				{
					modelPartitionData[0 ].value = (beowulf) ? 2 : 3; // Hands
					modelPartitionData[1 ].value = (beowulf) ? 3 : 2; // Fists
					modelPartitionData[2 ].value = 3; // Shoulders
					modelPartitionData[3 ].value = (beowulf) ? 2 : 3; // Lower Arms
					modelPartitionData[4 ].value = (beowulf) ? 3 : 2; // Lower Arms Half
					modelPartitionData[5 ].value = (beowulf) ? 3 : 2; // Lower Legs Half
					modelPartitionData[6 ].value = (beowulf) ? 2 : 3; // Lower Legs and Feet
					modelPartitionData[7 ].value = 3; // Upper Legs
					modelPartitionData[8 ].value = 3; // Upper Body
					modelPartitionData[9 ].value = 3; // Monocle
					modelPartitionData[10].value = 3; // Collar
					modelPartitionData[11].value = 3; // Neck
					modelPartitionData[12].value = 3; // Face
					modelPartitionData[13].value = 3; // Hair
					
					break;
				}
			}

			break;
		}
		case CHARACTER::LADY:
		{
			switch (costume)
			{
				case COSTUME::LADY_DEFAULT:
				{
					modelPartitionData[0].value = 3; // Body
					modelPartitionData[1].value = 3; // Face
					modelPartitionData[2].value = 3; // Hands
					modelPartitionData[3].value = 3; // Accessories
					modelPartitionData[4].value = (sessionData.mission >= 14) ? 3 : 2; // Bandage

					break;
				}
				case COSTUME::LADY_LEATHER_JUMPSUIT:
				{
					modelPartitionData[0].value = 3; // Body
					modelPartitionData[1].value = 3; // Face
					modelPartitionData[2].value = 3; // Hands
					modelPartitionData[3].value = 3; // Accessories
					modelPartitionData[4].value = 2; // Millenium Puzzle
					modelPartitionData[5].value = 3; // Feet
					modelPartitionData[6].value = 3; // Belt
					modelPartitionData[7].value = 3; // Zippers

					break;
				}
			}

			break;
		}
		case CHARACTER::VERGIL:
		{
			switch (costume)
			{
				case COSTUME::VERGIL_DEFAULT:
				case COSTUME::VERGIL_DEFAULT_INFINITE_MAGIC_POINTS:
				{
					modelPartitionData[0 ].value = 3; // Body
					modelPartitionData[1 ].value = 3; // Shoulders
					modelPartitionData[2 ].value = (beowulf) ? 2 : 3; // Hands
					modelPartitionData[3 ].value = 3; // Face
					modelPartitionData[4 ].value = (beowulf) ? 3 : 2; // Fists
					modelPartitionData[5 ].value = 3; // Hair Base
					modelPartitionData[6 ].value = 3; // Hair Main
					modelPartitionData[7 ].value = (beowulf) ? 3 : 2; // Lower Legs Half
					modelPartitionData[8 ].value = (beowulf) ? 2 : 3; // Lower Legs and Feet
					modelPartitionData[9 ].value = (beowulf) ? 3 : 2; // Lower Arms Half
					modelPartitionData[10].value = (beowulf) ? 2 : 3; // Lower Arms

					break;
				}
				case COSTUME::VERGIL_DEFAULT_NO_COAT:
				{
					modelPartitionData[0 ].value = 3; // Body
					modelPartitionData[1 ].value = 3; // Arms
					modelPartitionData[2 ].value = (beowulf) ? 2 : 3; // Hands
					modelPartitionData[3 ].value = 3; // Face
					modelPartitionData[4 ].value = (beowulf) ? 3 : 2; // Fists
					modelPartitionData[5 ].value = 3; // Hair Base
					modelPartitionData[6 ].value = 3; // Hair Main
					modelPartitionData[7 ].value = (beowulf) ? 3 : 2; // Lower Legs Half
					modelPartitionData[8 ].value = (beowulf) ? 2 : 3; // Lower Legs and Feet
					modelPartitionData[9 ].value = 2; // Filler
					modelPartitionData[10].value = 2; // Filler

					break;
				}
				case COSTUME::VERGIL_NERO_ANGELO:
				case COSTUME::VERGIL_NERO_ANGELO_INFINITE_MAGIC_POINTS:
				{
					modelPartitionData[0 ].value = 3; // Neck
					modelPartitionData[1 ].value = 3; // Face
					modelPartitionData[2 ].value = (beowulf) ? 2 : 3; // Hands
					modelPartitionData[3 ].value = 3; // Eyes
					modelPartitionData[4 ].value = (beowulf) ? 3 : 2; // Fists
					modelPartitionData[5 ].value = 3; // Hair Base
					modelPartitionData[6 ].value = 3; // Hair Main
					modelPartitionData[7 ].value = (beowulf) ? 3 : 2; // Lower Legs Half
					modelPartitionData[8 ].value = (beowulf) ? 2 : 3; // Lower Legs and Feet
					modelPartitionData[9 ].value = (beowulf) ? 3 : 2; // Lower Arms Half
					modelPartitionData[10].value = (beowulf) ? 2 : 3; // Lower Arms
					modelPartitionData[11].value = 3; // Collar
					modelPartitionData[12].value = 3; // Lower Legs
					modelPartitionData[13].value = 3; // Shoulders
					modelPartitionData[14].value = 3; // Body

					break;
				}
			}

			break;
		}
	}
}

















void UpdateActorDante(PlayerActorDataDante & actorData)
{
	LogFunction(actorData.operator byte8 *());

	actorData.devilModelMetadata.Rebellion.devilSubmodelMetadata[0].submodelIndex = 255;
	actorData.devilModelMetadata.Rebellion.devilSubmodelMetadata[1].submodelIndex = 255;
	actorData.devilModelMetadata.Cerberus.devilSubmodelMetadata.submodelIndex = 255;
	actorData.devilModelMetadata.Nevan.devilSubmodelMetadata[0].submodelIndex = 255;
	actorData.devilModelMetadata.Nevan.devilSubmodelMetadata[1].submodelIndex = 255;
	actorData.devilModelMetadata.Beowulf.devilSubmodelMetadata.submodelIndex = 255;
	actorData.devilModelMetadata.Sparda.devilSubmodelMetadata.submodelIndex = 255;
	/*
	dmc3.exe+212C20 - C6 81 02B60000 FF - mov byte ptr [rcx+0000B602],-01
	dmc3.exe+212C2B - C6 81 05B60000 FF - mov byte ptr [rcx+0000B605],-01
	dmc3.exe+212C32 - C6 81 0AB60000 FF - mov byte ptr [rcx+0000B60A],-01
	dmc3.exe+212C39 - C6 81 11B60000 FF - mov byte ptr [rcx+0000B611],-01
	dmc3.exe+212C40 - C6 81 14B60000 FF - mov byte ptr [rcx+0000B614],-01
	dmc3.exe+212C47 - C6 81 19B60000 FF - mov byte ptr [rcx+0000B619],-01
	dmc3.exe+212C4E - C6 81 1EB60000 FF - mov byte ptr [rcx+0000B61E],-01
	*/

	UpdateModel(actorData);

	// Log("reach here 8");

	func_1EF040(actorData, 0);

	// Log("reach here 9");

	func_1EEF80(actorData);

	// Log("reach here 10");


	func_1EF040(actorData, 3);

	// Log("reach here 11");



	if (actorData.sparda)
	{
		UpdateDevilModel(actorData, DEVIL::SPARDA, 0);
	}
	else
	{
		old_for_all(uint8, index, 5)
		{
			UpdateDevilModel(actorData, (DEVIL::REBELLION + index), index);
		}
	}

	// func_2EE060(actorData.var_6410, 60);
	// /*
	// dmc3.exe+2134C6 - 48 8D 8E 10640000 - lea rcx,[rsi+00006410]
	// dmc3.exe+2134CD - BA 3C000000       - mov edx,0000003C
	// dmc3.exe+2134D2 - E8 89AB0D00       - call dmc3.exe+2EE060
	// */

	// func_2C6150(actorData.var_6458, 0x49000, -2);
	// /*
	// dmc3.exe+214B37 - 48 8D 8E 58640000 - lea rcx,[rsi+00006458]
	// dmc3.exe+214B3E - BA 00900400       - mov edx,00049000
	// dmc3.exe+214B43 - 41 B8 FEFFFFFF    - mov r8d,FFFFFFFE
	// dmc3.exe+214B49 - E8 02160B00       - call dmc3.exe+2C6150
	// */

	actorData.actionData[0] = *reinterpret_cast<byte8 **>(appBaseAddr + 0x590598);
	actorData.actionData[1] = *reinterpret_cast<byte8 **>(appBaseAddr + 0x58A2A0);
	actorData.actionData[2] = (appBaseAddr + 0x5905B0);
	actorData.actionData[3] = File_staticFiles[pl000][9];
	actorData.actionData[4] = File_staticFiles[pl000][10];
	actorData.actionData[5] = File_staticFiles[pl000][11];
	/*
	dmc3.exe+214B50 - 48 8B 05 41BA3700 - mov rax,[dmc3.exe+590598]
	dmc3.exe+214B5E - 48 89 86 D03D0000 - mov [rsi+00003DD0],rax

	dmc3.exe+214B65 - 48 8B 05 34573700 - mov rax,[dmc3.exe+58A2A0]
	dmc3.exe+214B6C - 48 89 86 D83D0000 - mov [rsi+00003DD8],rax

	dmc3.exe+214B73 - 48 8D 05 36BA3700 - lea rax,[dmc3.exe+5905B0]
	dmc3.exe+214B7A - 48 89 86 E03D0000 - mov [rsi+00003DE0],rax

	dmc3.exe+212C27 - 45 8D 4F 09       - lea r9d,[r15+09]
	dmc3.exe+212C5C - E8 5F56FAFF       - call __GET_FILE__
	dmc3.exe+212C6C - 48 89 86 E83D0000 - mov [rsi+00003DE8],rax

	dmc3.exe+212C66 - 45 8D 4F 0A       - lea r9d,[r15+0A]
	dmc3.exe+212C7A - E8 4156FAFF       - call __GET_FILE__
	dmc3.exe+212C8A - 48 89 86 F03D0000 - mov [rsi+00003DF0],rax

	dmc3.exe+212C84 - 45 8D 4F 0B       - lea r9d,[r15+0B]
	dmc3.exe+212C98 - E8 2356FAFF       - call __GET_FILE__
	dmc3.exe+212CA0 - 48 89 86 F83D0000 - mov [rsi+00003DF8],rax
	*/

	func_2EE3D0(actorData.var_3C50);
	/*
	dmc3.exe+214B57 - 48 8D 8E 503C0000 - lea rcx,[rsi+00003C50]
	dmc3.exe+214B81 - E8 4A980D00       - call dmc3.exe+2EE3D0
	*/

	func_1FAF40(actorData);
}




export void ToggleNoDevilForm(bool enable)
{
	LogFunction(enable);

	static bool run = false;



	// Use activeModelIndexMirror instead activeModelIndex.

	// Motion
	{
		auto addr = (appBaseAddr + 0x1F5397);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1F5397 - 44 39 B3 6C3E0000 - cmp [rbx+00003E6C],r14d
		dmc3.exe+1F539E - 75 08             - jne dmc3.exe+1F53A8
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			Write<uint32>((addr + 3), offsetof(PlayerActorData, activeModelIndexMirror));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Aura
	{
		auto addr = (appBaseAddr + 0x90B60);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+90B60 - 49 63 86 6C3E0000    - movsxd  rax,dword ptr [r14+00003E6C]
		dmc3.exe+90B67 - 41 8B 8C 86 743E0000 - mov ecx,[r14+rax*4+00003E74]
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			Write<uint32>((addr + 3), offsetof(PlayerActorData, activeModelIndexMirror));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}



	run = true;
}








template <typename T>
void UpdateForm(T & actorData)
{
	DebugLogFunction(actorData.operator byte8 *());



	actorData.queuedModelIndex       = 0;
	actorData.activeModelIndexMirror = 0;
	actorData.airRaid                = 0;



	if (actorData.devil)
	{
		if constexpr (TypeMatch<T, PlayerActorDataDante>::value)
		{
			if (actorData.sparda)
			{
				actorData.queuedModelIndex       = 1;
				actorData.activeModelIndexMirror = 1;
				actorData.activeDevil            = DEVIL::SPARDA;
				actorData.airRaid                = 0;

				if (activeConfig.noDevilForm)
				{
					actorData.queuedModelIndex = 0;
				}
			}
			else
			{
				auto weapon = (WEAPON::REBELLION + actorData.meleeWeaponIndex);
				if (weapon > WEAPON::BEOWULF_DANTE)
				{
					weapon = WEAPON::REBELLION;
				}

				actorData.queuedModelIndex       = (1 + weapon);
				actorData.activeModelIndexMirror = (1 + weapon);
				actorData.activeDevil            = static_cast<uint32>(weaponDevilIds[weapon]);
				actorData.airRaid                = 0;

				if (activeConfig.noDevilForm)
				{
					actorData.queuedModelIndex = 0;
				}

				func_1F97F0(actorData, true);
			}
		}
		else if constexpr (TypeMatch<T, PlayerActorDataVergil>::value)
		{
			if (actorData.neroAngelo)
			{
				actorData.queuedModelIndex       = 1;
				actorData.activeModelIndexMirror = 1;
				actorData.activeDevil            = DEVIL::NERO_ANGELO;
				actorData.airRaid                = 0;

				if (activeConfig.noDevilForm)
				{
					actorData.queuedModelIndex = 0;
				}
			}
			else
			{
				auto weapon = (WEAPON::YAMATO_VERGIL + actorData.queuedMeleeWeaponIndex);
				if
				(
					(weapon < WEAPON::YAMATO_VERGIL    ) ||
					(weapon > WEAPON::YAMATO_FORCE_EDGE)
				)
				{
					weapon = WEAPON::YAMATO_VERGIL;
				}

				actorData.queuedModelIndex       = (weapon == WEAPON::BEOWULF_VERGIL) ? 2 : 1;
				actorData.activeModelIndexMirror = (weapon == WEAPON::BEOWULF_VERGIL) ? 2 : 1;
				actorData.activeDevil            = static_cast<uint32>(weaponDevilIds[weapon]);
				actorData.airRaid                = 0;

				if (activeConfig.noDevilForm)
				{
					actorData.queuedModelIndex = 0;
				}

				func_1F97F0(actorData, true);
			}
		}
	}
}

// @Todo: Update.
template <typename T>
void UpdateMotionArchives(T & actorData)
{
	constexpr uint8 count =
	(TypeMatch<T, PlayerActorDataDante >::value) ? static_cast<uint8>(countof(motionArchiveHelperDante )) :
	(TypeMatch<T, PlayerActorDataBob   >::value) ? static_cast<uint8>(countof(motionArchiveHelperBob   )) :
	(TypeMatch<T, PlayerActorDataLady  >::value) ? static_cast<uint8>(countof(motionArchiveHelperLady  )) :
	(TypeMatch<T, PlayerActorDataVergil>::value) ? static_cast<uint8>(countof(motionArchiveHelperVergil)) :
	0;

	const MotionArchiveHelper * motionArchiveHelper =
	(TypeMatch<T, PlayerActorDataDante >::value) ? motionArchiveHelperDante  :
	(TypeMatch<T, PlayerActorDataBob   >::value) ? motionArchiveHelperBob    :
	(TypeMatch<T, PlayerActorDataLady  >::value) ? motionArchiveHelperLady   :
	(TypeMatch<T, PlayerActorDataVergil>::value) ? motionArchiveHelperVergil :
	0;

	old_for_all(uint8, index, count)
	{
		auto & group = motionArchiveHelper[index].group;
		auto & cacheFileId = motionArchiveHelper[index].cacheFileId;

		auto & metadata = File_staticFiles[cacheFileId];

		actorData.motionArchives[group] = File_dynamicFiles.Push(metadata.addr, metadata.size);
	}
}

// template <typename T>
// void InitStyle(T & actorData)
// {
// 	if constexpr (TypeMatch<T, PlayerActorDataDante>::value)
// 	{
// 		actorData.style = STYLE::TRICKSTER;
// 	}
// 	else if constexpr (TypeMatch<T, PlayerActorDataBob>::value)
// 	{
// 		actorData.style = STYLE::DARK_SLAYER;
// 	}
// 	else if constexpr (TypeMatch<T, PlayerActorDataVergil>::value)
// 	{
// 		actorData.style = STYLE::DARK_SLAYER;
// 	}
// }

// @Todo: Update.
template <typename T>
void InitWeapons(T & actorData)
{
	SetMemory
	(
		(reinterpret_cast<byte8 *>(&actorData) + offsetof(PlayerActorDataVergil, activeMeleeWeaponIndex)),
		0,
		(offsetof(PlayerActorDataVergil, styleData) - offsetof(PlayerActorDataVergil, activeMeleeWeaponIndex))
	);

	// @Research: Suspicious.
	SetMemory(actorData.newWeapons, WEAPON::VOID, sizeof(actorData.newWeapons));
	SetMemory(actorData.newWeaponStatus, WEAPON_STATUS::DISABLED, sizeof(actorData.newWeaponStatus));

	constexpr uint8 count =
	(TypeMatch<T, PlayerActorDataDante >::value) ? WEAPON_COUNT_DANTE  :
	(TypeMatch<T, PlayerActorDataBob >::value) ? WEAPON_COUNT_BOB  :
	(TypeMatch<T, PlayerActorDataVergil>::value) ? WEAPON_COUNT_VERGIL :
	0;

	old_for_all(uint8, index, count)
	{
		uint8 weapon =
		(TypeMatch<T, PlayerActorDataDante >::value) ? (WEAPON::REBELLION     + index) :
		(TypeMatch<T, PlayerActorDataBob >::value) ? (WEAPON::YAMATO_BOB     + index) :
		(TypeMatch<T, PlayerActorDataVergil>::value) ? (WEAPON::YAMATO_VERGIL + index) :
		0;

		actorData.newWeapons[index] = weapon;
		actorData.newWeaponDataAddr[index] = RegisterWeapon[weapon](actorData, weapon);
		actorData.newWeaponStatus[index] = WEAPON_STATUS::READY;
	}

	if constexpr (TypeMatch<T, PlayerActorDataDante>::value)
	{
		actorData.meleeWeaponIndex = 0;
		actorData.rangedWeaponIndex = 5;
	}
	else if constexpr (TypeMatch<T, PlayerActorDataBob>::value)
	{
		actorData.meleeWeaponIndex = 0;
	}
	else if constexpr (TypeMatch<T, PlayerActorDataVergil>::value)
	{
		actorData.activeMeleeWeaponIndex = 0;
		actorData.queuedMeleeWeaponIndex = 0;

		if (actorData.neroAngelo)
		{
			actorData.newWeaponDataAddr[3] = func_22CF00(actorData, 0);
		}
	}
}







auto GetStyle(CharacterData & characterData)
{
	auto & styleIndex = characterData.styleIndices[characterData.styleButtonIndex];

	return characterData.styles[characterData.styleButtonIndex][styleIndex];
}

template <typename T>
auto GetStyle(T & actorData)
{
	auto & characterData = GetCharacterData(actorData);

	return GetStyle(characterData);
}

template <typename T>
auto GetMeleeWeapon(T & actorData)
{
	auto & characterData = GetCharacterData(actorData);

	return characterData.meleeWeapons[characterData.meleeWeaponIndex];
}

template <typename T>
auto GetRangedWeapon(T & actorData)
{
	auto & characterData = GetCharacterData(actorData);

	return characterData.rangedWeapons[characterData.rangedWeaponIndex];
}












template <typename T>
void UpdateStyle(T & actorData)
{
	if constexpr (debug)
	{
		LogFunction(actorData.operator byte8 *());
	}
	
	// auto & characterData = GetCharacterData(actorData);

	// auto & styleIndex = characterData.styleIndices[characterData.styleButtonIndex];
	// auto & style = characterData.styles[characterData.styleButtonIndex][styleIndex];

	actorData.style = GetStyle(actorData);
}

template <typename T>
void UpdateMeleeWeapon(T & actorData)
{
	DebugLogFunction(actorData.operator byte8 *());

	auto & characterData = GetCharacterData(actorData);

	if (characterData.meleeWeaponIndex >= characterData.meleeWeaponCount)
	{
		characterData.meleeWeaponIndex = 0;
	}

	auto weapon = GetMeleeWeapon(actorData);

	if constexpr (TypeMatch<T, PlayerActorDataDante>::value)
	{
		if (IsDanteMeleeWeapon(weapon))
		{
			actorData.meleeWeaponIndex = weapon;
		}
	}
	else if constexpr (TypeMatch<T, PlayerActorDataVergil>::value)
	{
		if (IsVergilMeleeWeapon(weapon))
		{
			actorData.queuedMeleeWeaponIndex = (weapon - WEAPON::YAMATO_VERGIL);
		}
	}
}

template <typename T>
void UpdateRangedWeapon(T & actorData)
{
	DebugLogFunction(actorData.operator byte8 *());

	auto & characterData = GetCharacterData(actorData);

	if (characterData.rangedWeaponIndex >= characterData.rangedWeaponCount)
	{
		characterData.rangedWeaponIndex = 0;
	}

	auto weapon = GetRangedWeapon(actorData);

	if constexpr (TypeMatch<T, PlayerActorDataDante>::value)
	{
		if (IsDanteRangedWeapon(weapon))
		{
			actorData.rangedWeaponIndex = weapon;
		}
	}
}

template <typename T>
void UpdateWeapons(T & actorData)
{
	DebugLogFunction(actorData.operator byte8 *());

	UpdateMeleeWeapon (actorData);
	UpdateRangedWeapon(actorData);
}












template <typename T>
byte8 * CreatePlayerActor
(
	uint8 playerIndex,
	uint8 characterIndex,
	uint8 entityIndex
)
{


	//HoboBreak();



	// LogFunction
	// (
	// 	playerIndex,
	// 	characterIndex,
	// 	entityIndex
	// );

	auto & playerData = GetPlayerData(playerIndex);
	auto & characterData = GetCharacterData
	(
		playerIndex,
		characterIndex,
		entityIndex
	);

	// auto & newActorData = GetNewActorData
	// (
	// 	playerIndex,
	// 	characterIndex,
	// 	entityIndex
	// );





	IntroduceSessionData();
	IntroduceMissionActorData(return 0);

	auto actorBaseAddr = func_1DE820(characterData.character, 0, false);
	if (!actorBaseAddr)
	{
		return 0;
	}
	auto & actorData = *reinterpret_cast<T *>(actorBaseAddr);

	UpdateFileData(actorData);

	InitActor(actorData, activeMissionActorData);

	actorData.shadow = 1;
	actorData.lastShadow = 1;
	actorData.costume = (characterData.ignoreCostume) ? sessionData.costume : characterData.costume;

	// Necessary when for example character is Vergil and session character is Dante.
	// Since Dante has more costumes, the index could go out of range.
	{
		auto character = characterData.character;
		if (character >= CHARACTER::MAX)
		{
			character = 0;
		}

		auto & costumeCount = costumeCounts[character];

		if (actorData.costume >= costumeCount)
		{
			actorData.costume = 0;
		}
	}

	// @Todo: Update.
	{
		bool value = false;

		if constexpr (TypeMatch<T, PlayerActorDataDante>::value)
		{
			switch (actorData.costume)
			{
				case COSTUME::DANTE_DMC1:
				case COSTUME::DANTE_DMC1_NO_COAT:
				case COSTUME::DANTE_SPARDA:
				case COSTUME::DANTE_SPARDA_INFINITE_MAGIC_POINTS:
				{
					value = true;

					break;
				}
			}

			actorData.sparda = value;
		}
		else if constexpr (TypeMatch<T, PlayerActorDataVergil>::value)
		{
			switch (actorData.costume)
			{
				case COSTUME::VERGIL_NERO_ANGELO:
				case COSTUME::VERGIL_NERO_ANGELO_INFINITE_MAGIC_POINTS:
				{
					value = true;

					break;
				}
			}

			actorData.neroAngelo = value;
		}
	}

	UpdateCostumeFileData(actorData);

	actorData.newPlayerIndex         = playerIndex;
	actorData.newCharacterIndex      = characterIndex;
	actorData.newEntityIndex         = entityIndex;
	actorData.newForceFiles          = characterData.forceFiles;
	actorData.newForceFilesCharacter = characterData.forceFilesCharacter;
	actorData.newForceFilesCostume = characterData.forceFilesCostume;
	actorData.newGamepad             = playerIndex;

	if constexpr (TypeMatch<T, PlayerActorDataDante>::value)
	{
		UpdateActorDante(actorData);
	}
	else
	{
		UpdateActor(actorData);
	}

	if (entityIndex == ENTITY::MAIN)
	{
		func_2EE060(actorData.var_6410, 60);
		/*
		dmc3.exe+2134C6 - 48 8D 8E 10640000 - lea rcx,[rsi+00006410]
		dmc3.exe+2134CD - BA 3C000000       - mov edx,0000003C
		dmc3.exe+2134D2 - E8 89AB0D00       - call dmc3.exe+2EE060
		*/

		func_2C6150(actorData.var_6458, 0x49000, -2);
		/*
		dmc3.exe+214B37 - 48 8D 8E 58640000 - lea rcx,[rsi+00006458]
		dmc3.exe+214B3E - BA 00900400       - mov edx,00049000
		dmc3.exe+214B43 - 41 B8 FEFFFFFF    - mov r8d,FFFFFFFE
		dmc3.exe+214B49 - E8 02160B00       - call dmc3.exe+2C6150
		*/
	}

	UpdateMotionArchives(actorData);

	UpdateStyle(actorData);

	if
	(
		(playerIndex == 0) &&
		(characterIndex == playerData.activeCharacterIndex) &&
		(entityIndex == ENTITY::MAIN)
	)
	{
		HUD_UpdateStyleIcon
		(
			GetStyle(actorData),
			characterData.character
		);
	}

	InitWeapons(actorData);

	UpdateWeapons(actorData);

	SetMemory
	(
		actorData.expertise,
		0xFF,
		sizeof(actorData.expertise)
	);

	actorData.styleLevel = 2;

	if constexpr (TypeMatch<T, PlayerActorDataDante>::value)
	{
		old_for_each(uint8, weaponIndex, WEAPON::EBONY_IVORY, WEAPON_COUNT_DANTE)
		{
			actorData.newWeaponLevels[weaponIndex] = 2;
		}
	}

	if (entityIndex == ENTITY::CLONE)
	{
		actorData.newIsClone = true;
	}

	func_1DFC20(actorData);

	g_playerActorBaseAddrs.Push(actorBaseAddr);



	CommissionActor(actorData);



	return actorBaseAddr;
}



byte8 * SpawnActor
(
	uint8 playerIndex,
	uint8 characterIndex,
	uint8 entityIndex
)
{
	byte8 * actorBaseAddr = 0;

	auto & characterData = GetCharacterData(playerIndex, characterIndex, entityIndex);
	auto & newActorData  = GetNewActorData (playerIndex, characterIndex, entityIndex);



	Log("SpawnActor %u %u %u", playerIndex, characterIndex, entityIndex);
	Log("character %u", characterData.character);



	switch (characterData.character)
	{
		case CHARACTER::DANTE:
		{
			actorBaseAddr = CreatePlayerActor<PlayerActorDataDante>
			(
				playerIndex,
				characterIndex,
				entityIndex
			);

			break;
		}
		case CHARACTER::BOB:
		{
			actorBaseAddr = CreatePlayerActor<PlayerActorDataBob>
			(
				playerIndex,
				characterIndex,
				entityIndex
			);

			break;
		}
		case CHARACTER::LADY:
		{
			actorBaseAddr = CreatePlayerActor<PlayerActorDataLady>
			(
				playerIndex,
				characterIndex,
				entityIndex
			);

			break;
		}
		case CHARACTER::VERGIL:
		{
			actorBaseAddr = CreatePlayerActor<PlayerActorDataVergil>
			(
				playerIndex,
				characterIndex,
				entityIndex
			);

			break;
		}
		case CHARACTER::BOSS_LADY:
		{
			[&]()
			{
				IntroduceMainActorData(mainActorBaseAddr, mainActorData, return);

				CreateEnemyActorData data = {};

				data.enemy = ENEMY::LADY;
				data.position = mainActorData.position;
				data.rotation = mainActorData.rotation;

				actorBaseAddr = CreateEnemyActor(data, CreateEnemyActorFlags_Reset);
			}();

			break;
		}
		case CHARACTER::BOSS_VERGIL:
		{
			[&]()
			{
				IntroduceMainActorData(mainActorBaseAddr, mainActorData, return);

				CreateEnemyActorData data = {};

				data.enemy = ENEMY::VERGIL;
				data.variant = 2;
				data.position = mainActorData.position;
				data.rotation = mainActorData.rotation;

				actorBaseAddr = CreateEnemyActor(data, CreateEnemyActorFlags_Reset);
			}();

			break;
		}
	}

	newActorData.baseAddr = actorBaseAddr;



	return actorBaseAddr;
}

export void SpawnActors()
{
	LogFunction();



	old_for_all(uint8, playerIndex, activeConfig.Actor.playerCount)
	{
		auto & playerData = GetPlayerData(playerIndex);

		if (playerData.characterIndex >= playerData.characterCount)
		{
			playerData.characterIndex = 0;
		}

		playerData.activeCharacterIndex = playerData.lastCharacterIndex = playerData.characterIndex;



		old_for_all(uint8, characterIndex, playerData.characterCount)
		{
			auto actorBaseAddr = SpawnActor
			(
				playerIndex,
				characterIndex,
				ENTITY::MAIN
			);

			if (!actorBaseAddr)
			{
				Log("SpawnActor failed.");

				return;
			}
			auto & actorData = *reinterpret_cast<PlayerActorData *>(actorBaseAddr);



			// Commission Enemy Actor

			auto & characterData = GetCharacterData(playerIndex, characterIndex, ENTITY::MAIN);
			auto & newActorData  = GetNewActorData (playerIndex, characterIndex, ENTITY::MAIN);

			if
			(
				(characterData.character == CHARACTER::BOSS_LADY  ) ||
				(characterData.character == CHARACTER::BOSS_VERGIL)
			)
			{
				ToggleActor
				(
					characterData,
					newActorData,
					(playerData.activeCharacterIndex == characterIndex) ? true : false
				);

				continue;
			}



			actorData.cloneActorBaseAddr = SpawnActor
			(
				playerIndex,
				characterIndex,
				ENTITY::CLONE
			);
		}
	}
}

#pragma endregion

#pragma region Controllers

// @Todo: Move.
void ResetPermissionsController(byte8 * actorBaseAddr)
{
	if
	(
		!activeConfig.resetPermissions ||
		!actorBaseAddr ||
		(actorBaseAddr == g_playerActorBaseAddrs[0]) ||
		(actorBaseAddr == g_playerActorBaseAddrs[1])
	)
	{
		return;
	}

	IntroducePlayerActorData(actorBaseAddr, actorData, return);

	if (actorData.buttons[2] & GetBinding(BINDING::TAUNT))
	{
		actorData.permissions = 0x1C1B;
	}
}





void RemoveBusyFlagController(byte8 * actorBaseAddr)
{
	if
	(
		!actorBaseAddr ||
		(actorBaseAddr == g_playerActorBaseAddrs[0]) ||
		(actorBaseAddr == g_playerActorBaseAddrs[1])
	)
	{
		return;
	}

	IntroduceData(actorBaseAddr, actorData, PlayerActorData, return);



	auto playerIndex = actorData.newPlayerIndex;
	if (playerIndex >= PLAYER_COUNT)
	{
		playerIndex = 0;
	}

	auto characterIndex = actorData.newCharacterIndex;
	if (characterIndex >= CHARACTER_COUNT)
	{
		characterIndex = 0;
	}

	auto entityIndex = actorData.newEntityIndex;
	if (entityIndex >= ENTITY_COUNT)
	{
		entityIndex = 0;
	}

	auto & playerData = GetPlayerData(playerIndex);

	auto & gamepad = GetGamepad(playerIndex);

	static bool executes[PLAYER_COUNT][CHARACTER_COUNT][ENTITY_COUNT][4] = {};



	if (!playerData.removeBusyFlag)
	{
		return;
	}



	old_for_all(uint8, buttonIndex, 4)
	{
		auto & execute = executes[playerIndex][characterIndex][entityIndex][buttonIndex];

		auto & button = playerData.removeBusyFlagButtons[buttonIndex];



		if (gamepad.buttons[0] & button)
		{
			if (execute)
			{
				execute = false;

				actorData.state &= ~STATE::BUSY;

				DebugLog
				(
					"%u %X %llX",
					buttonIndex,
					button,
					actorData.baseAddr
				);
			}
		}
		else
		{
			execute = true;
		}
	}
}








template <typename T>
void StyleSwitchController(T & actorData)
{
	auto & playerData = GetPlayerData(actorData);
	auto & characterData = GetCharacterData(actorData);

	bool update = false;

	{
		bool condition = (actorData.buttons[0] & playerData.button);

		if (actorData.newEntityIndex == ENTITY::MAIN)
		{
			if (condition)
			{
				return;
			}
		}
		else
		{
			if (!condition)
			{
				return;
			}
		}
	}

	old_for_all(uint8, styleButtonIndex, STYLE_COUNT)
	{
		auto & styleButton = characterData.styleButtons[styleButtonIndex];
		auto & styleIndex = characterData.styleIndices[styleButtonIndex];

		auto lastStyleIndex = styleIndex;

		if (actorData.buttons[2] & styleButton)
		{
			if (characterData.styleButtonIndex == styleButtonIndex)
			{
				styleIndex++;

				if (styleIndex >= 2)
				{
					styleIndex = 0;
				}
			}
			else
			{
				styleIndex = 0;
			}

			auto style = characterData.styles[styleButtonIndex][styleIndex];

			switch (style)
			{
				case STYLE::QUICKSILVER:
				{
					if
					(
						(actorData.newPlayerIndex != 0) ||
						(actorData.newCharacterIndex != 0) ||
						(actorData.newEntityIndex != ENTITY::MAIN)
					)
					{
						styleIndex = lastStyleIndex;

						goto LoopContinue;
					}

					break;
				}
				case STYLE::DOPPELGANGER:
				{
					if (actorData.newEntityIndex != ENTITY::MAIN)
					{
						styleIndex = lastStyleIndex;

						goto LoopContinue;
					}

					break;
				}
			}

			characterData.styleButtonIndex = styleButtonIndex;

			update = true;

			break;
		}

		LoopContinue:;
	}

	if (!update)
	{
		return;
	}

	UpdateStyle(actorData);

	// if (activeConfig.removeBusyFlag)
	// {
	// 	actorData.state &= ~STATE::BUSY;

	// 	if constexpr (debug)
	// 	{
	// 		Log("%llX Remove Busy Flag", actorData.operator byte8 *());
	// 	}
	// }

	if (actorData.newPlayerIndex != 0)
	{
		return;
	}
	else if (actorData.newEntityIndex != ENTITY::MAIN)
	{
		return;
	}

	HUD_UpdateStyleIcon
	(
		GetStyle(actorData),
		characterData.character
	);
}

// @Todo: Update Nero Angelo fix.
template <typename T>
void LinearMeleeWeaponSwitchController(T & actorData)
{
	auto & playerData = GetPlayerData(actorData);
	auto & characterData = GetCharacterData(actorData);

	bool update = false;

	bool forward = false;
	bool back = false;

	{
		bool condition = (actorData.buttons[0] & playerData.button);

		if (actorData.newEntityIndex == ENTITY::MAIN)
		{
			if (condition)
			{
				return;
			}
		}
		else
		{
			if (!condition)
			{
				return;
			}
		}
	}

	if (0 < actorData.meleeWeaponSwitchTimeout)
	{
		return;
	}
	else if (characterData.meleeWeaponCount < 2)
	{
		return;
	}

	auto Forward = [&]()
	{
		if (characterData.meleeWeaponIndex == (characterData.meleeWeaponCount - 1))
		{
			characterData.meleeWeaponIndex = 0;
		}
		else
		{
			characterData.meleeWeaponIndex++;
		}
		update = true;

		forward = true;
	};

	auto Back = [&]()
	{
		if (characterData.meleeWeaponIndex == 0)
		{
			characterData.meleeWeaponIndex = (characterData.meleeWeaponCount - 1);
		}
		else
		{
			characterData.meleeWeaponIndex--;
		}
		update = true;

		back = true;
	};

	if (actorData.buttons[2] & GetBinding(BINDING::CHANGE_DEVIL_ARMS))
	{
		if (actorData.buttons[0] & GetBinding(BINDING::TAUNT))
		{
			Back();
		}
		else
		{
			Forward();
		}
	}
	else if (actorData.buttons[2] & GetBinding(BINDING::CHANGE_GUN))
	{
		if constexpr (TypeMatch<T, PlayerActorDataVergil>::value)
		{
			Back();
		}
	}

	if (!update)
	{
		return;
	}

	actorData.meleeWeaponSwitchTimeout = activeConfig.linearWeaponSwitchTimeout;

	// Nero Angelo Fix
	{
		auto weapon = GetMeleeWeapon(actorData);

		if
		(
			IsNeroAngelo(actorData) &&
			(weapon == WEAPON::YAMATO_FORCE_EDGE)
		)
		{
			if (forward)
			{
				Forward();
			}
			else if (back)
			{
				Back();
			}
		}
	}

	UpdateMeleeWeapon(actorData);

	UpdateForm(actorData);

	if (actorData.newPlayerIndex != 0)
	{
		return;
	}
	else if (actorData.newEntityIndex != ENTITY::MAIN)
	{
		return;
	}

	[&]()
	{
		IntroduceHUDPointers(return);

		if
		(
			HUD_UpdateWeaponIcon
			(
				HUD_BOTTOM::MELEE_WEAPON_1,
				GetMeleeWeapon(actorData)
			)
		)
		{
			func_280120(hudBottom, 1, 0); // @Todo: Enums.
		}
	}();

	func_1EB0E0(actorData, 4);
}

template <typename T>
void LinearRangedWeaponSwitchController(T & actorData)
{
	auto & playerData = GetPlayerData(actorData);
	auto & characterData = GetCharacterData(actorData);

	bool update = false;

	{
		bool condition = (actorData.buttons[0] & playerData.button);

		if (actorData.newEntityIndex == ENTITY::MAIN)
		{
			if (condition)
			{
				return;
			}
		}
		else
		{
			if (!condition)
			{
				return;
			}
		}
	}

	if (0 < actorData.rangedWeaponSwitchTimeout)
	{
		return;
	}
	else if (characterData.rangedWeaponCount < 2)
	{
		return;
	}

	auto Forward = [&]()
	{
		if (characterData.rangedWeaponIndex == (characterData.rangedWeaponCount - 1))
		{
			characterData.rangedWeaponIndex = 0;
		}
		else
		{
			characterData.rangedWeaponIndex++;
		}
		update = true;
	};

	auto Back = [&]()
	{
		if (characterData.rangedWeaponIndex == 0)
		{
			characterData.rangedWeaponIndex = (characterData.rangedWeaponCount - 1);
		}
		else
		{
			characterData.rangedWeaponIndex--;
		}
		update = true;
	};

	if (actorData.buttons[2] & GetBinding(BINDING::CHANGE_GUN))
	{
		if (actorData.buttons[0] & GetBinding(BINDING::TAUNT))
		{
			Back();
		}
		else
		{
			Forward();
		}
	}

	if (!update)
	{
		return;
	}

	actorData.rangedWeaponSwitchTimeout = activeConfig.linearWeaponSwitchTimeout;

	UpdateRangedWeapon(actorData);

	if (actorData.newPlayerIndex != 0)
	{
		return;
	}
	else if (actorData.newEntityIndex != ENTITY::MAIN)
	{
		return;
	}

	[&]()
	{
		IntroduceHUDPointers(return);

		if
		(
			HUD_UpdateWeaponIcon
			(
				HUD_BOTTOM::RANGED_WEAPON_1,
				GetRangedWeapon(actorData)
			)
		)
		{
			func_280120(hudBottom, 0, 0); // @Todo: Enums.
		}
	}();

	func_1EB0E0(actorData, 4);
}

// @Research: Consider weapon type template.
template <typename T>
void ArbitraryMeleeWeaponSwitchController(T & actorData)
{
	auto & characterData = GetCharacterData(actorData);

	auto & gamepad = GetGamepad(actorData.newPlayerIndex);

	auto leftStick = (characterData.meleeWeaponSwitchStick == LEFT_STICK);

	auto radius = (leftStick) ? gamepad.leftStickRadius   : gamepad.rightStickRadius;
	auto pos    = (leftStick) ? gamepad.leftStickPosition : gamepad.rightStickPosition;



	if (!(gamepad.buttons[0] & GetBinding(BINDING::CHANGE_DEVIL_ARMS)))
	{
		return;
	}

	g_disableCameraRotation = true; // @Research: Consider !leftStick.

	if (radius < RIGHT_STICK_DEADZONE)
	{
		return;
	}



	uint8 meleeWeaponIndex = 0;
	uint8 meleeWeaponCount = characterData.meleeWeaponCount;

	if
	(
		(
			(pos <= -26214) &&
			(pos >= -32768)
		) ||
		(
			(pos <= 32767) &&
			(pos >= 26214)
		)
	)
	{
		meleeWeaponIndex = 0;
	}
	else if
	(
		(pos < 26214) &&
		(pos >= 13107)
	)
	{
		meleeWeaponIndex = 1;
	}
	else if
	(
		(pos < 13107) &&
		(pos >= 0)
	)
	{
		meleeWeaponIndex = 2;
	}
	else if
	(
		(pos <= -1) &&
		(pos > -13107)
	)
	{
		meleeWeaponIndex = 3;
	}
	else if
	(
		(pos <= -13107) &&
		(pos > -26214)
	)
	{
		meleeWeaponIndex = 4;
	}

	if (IsNeroAngelo(actorData))
	{
		meleeWeaponCount = 2;
	}

	if (meleeWeaponIndex >= meleeWeaponCount)
	{
		return;
	}

	characterData.meleeWeaponIndex = meleeWeaponIndex;

	if (characterData.lastMeleeWeaponIndex != characterData.meleeWeaponIndex)
	{
		characterData.lastMeleeWeaponIndex = characterData.meleeWeaponIndex;

		UpdateMeleeWeapon(actorData);

		UpdateForm(actorData);

		PlaySound(0, 12);
	}
}

template <typename T>
void ArbitraryRangedWeaponSwitchController(T & actorData)
{
	auto & characterData = GetCharacterData(actorData);

	auto & gamepad = GetGamepad(actorData.newPlayerIndex);

	auto leftStick = (characterData.rangedWeaponSwitchStick == LEFT_STICK);

	auto radius = (leftStick) ? gamepad.leftStickRadius   : gamepad.rightStickRadius;
	auto pos    = (leftStick) ? gamepad.leftStickPosition : gamepad.rightStickPosition;



	if (!(gamepad.buttons[0] & GetBinding(BINDING::CHANGE_GUN)))
	{
		return;
	}

	g_disableCameraRotation = true;

	if (radius < RIGHT_STICK_DEADZONE)
	{
		return;
	}



	uint8 rangedWeaponIndex = 0;
	uint8 rangedWeaponCount = characterData.rangedWeaponCount;

	if
	(
		(
			(pos <= -26214) &&
			(pos >= -32768)
		) ||
		(
			(pos <= 32767) &&
			(pos >= 26214)
		)
	)
	{
		rangedWeaponIndex = 0;
	}
	else if
	(
		(pos < 26214) &&
		(pos >= 13107)
	)
	{
		rangedWeaponIndex = 1;
	}
	else if
	(
		(pos < 13107) &&
		(pos >= 0)
	)
	{
		rangedWeaponIndex = 2;
	}
	else if
	(
		(pos <= -1) &&
		(pos > -13107)
	)
	{
		rangedWeaponIndex = 3;
	}
	else if
	(
		(pos <= -13107) &&
		(pos > -26214)
	)
	{
		rangedWeaponIndex = 4;
	}

	if (rangedWeaponIndex >= rangedWeaponCount)
	{
		return;
	}

	characterData.rangedWeaponIndex = rangedWeaponIndex;

	if (characterData.lastRangedWeaponIndex != characterData.rangedWeaponIndex)
	{
		characterData.lastRangedWeaponIndex = characterData.rangedWeaponIndex;

		UpdateRangedWeapon(actorData);

		PlaySound(0, 12);
	}
}

template <typename T>
bool WeaponSwitchController(byte8 * actorBaseAddr)
{
	if
	(
		!actorBaseAddr ||
		(actorBaseAddr == g_playerActorBaseAddrs[0]) ||
		(actorBaseAddr == g_playerActorBaseAddrs[1]) ||
		InCutscene()
	)
	{
		return true;
	}
	auto & actorData = *reinterpret_cast<T *>(actorBaseAddr);

	auto & playerData = GetPlayerData(actorData);

	auto & characterData = GetCharacterData(actorData);




	if (actorData.mode == ACTOR_MODE::MISSION_18)
	{
		return true;
	}
	else if (actorData.var_3F19)
	{
		return false;
	}








	StyleSwitchController(actorData);

	if
	(
		(actorData.newPlayerIndex == 0) &&
		(actorData.newCharacterIndex == playerData.activeCharacterIndex) &&
		(actorData.newEntityIndex == ENTITY::MAIN)
	)
	{
		g_disableCameraRotation = false;

		if (characterData.meleeWeaponSwitchType == WEAPON_SWITCH_TYPE::ARBITRARY)
		{
			ArbitraryMeleeWeaponSwitchController(actorData);
		}
		else
		{
			LinearMeleeWeaponSwitchController(actorData);
		}

		if constexpr (TypeMatch<T, PlayerActorDataDante>::value)
		{
			if (characterData.rangedWeaponSwitchType == WEAPON_SWITCH_TYPE::ARBITRARY)
			{
				ArbitraryRangedWeaponSwitchController(actorData);
			}
			else
			{
				LinearRangedWeaponSwitchController(actorData);
			}
		}
	}
	else
	{
		LinearMeleeWeaponSwitchController(actorData);

		if constexpr (TypeMatch<T, PlayerActorDataDante>::value)
		{
			LinearRangedWeaponSwitchController(actorData);
		}
	}



	RemoveBusyFlagController(actorData);

	ResetPermissionsController(actorData);



	return true;
}











bool IsBossVergilActive(EnemyActorDataVergil & actorData)
{
	using namespace EVENT_BOSS_VERGIL;

	switch (actorData.event)
	{
		case TAUNT:
		case DAMAGE:
		case BLOCK:
		case DAMAGE_2:
		case DAMAGE_3:
		case DAMAGE_4:
		case DAMAGE_5:
		case STRONG_SHIELD:
		case YAMATO_SUPER_JUDGEMENT_CUT:
		case YAMATO_SUPER_JUDGEMENT_CUT_FOLLOW:
		case SHIELD:
		case YAMATO_DEFLECT:
		case REST_IN_PEACE:
		{
			return true;
		}
	}

	return false;
}

bool IsBossLadyActive(EnemyActorDataLady & actorData)
{
	using namespace EVENT_BOSS_LADY;

	switch (actorData.event)
	{
		case SMG_ROUNDHOUSE:
		case KALINA_ANN_CHARGED_SHOT:
		case KALINA_ANN_HYSTERIC:
		case KALINA_ANN_HOOK:
		case GRENADE_THROW:
		case FALL_BACK_SHOOT:
		case FALL_BACK_RECOVER:
		case FALL_BACK_RECOVER_CROSSBOW:
		case TROOPER_ROLL:
		case WHEEL_BACK:
		case WHEEL_RIGHT:
		case WHEEL_LEFT:
		case PISTOL_RELOAD:
		case SMG_RELOAD:
		{
			return true;
		}
	}

	return false;
}







template <typename T>
bool CanQueueMeleeAttack(T & actorData)
{
	using namespace NEXT_ACTION_REQUEST_POLICY;

	auto & policy = actorData.nextActionRequestPolicy[MELEE_ATTACK];

	if
	(
		(policy == BUFFER) ||
		(policy == EXECUTE)
	)
	{
		return true;
	}

	return false;
}

template <typename T>
bool CanQueueStyleAction(T & actorData)
{
	using namespace NEXT_ACTION_REQUEST_POLICY;

	switch (actorData.style)
	{
		case STYLE::SWORDMASTER:
		case STYLE::GUNSLINGER:
		{
			auto & policy = actorData.nextActionRequestPolicy[SWORDMASTER_GUNSLINGER];

			if
			(
				(policy == BUFFER) ||
				(policy == EXECUTE)
			)
			{
				return true;
			}

			break;
		}
		case STYLE::TRICKSTER:
		{
			auto & policy = actorData.nextActionRequestPolicy[TRICKSTER_DARK_SLAYER];

			if
			(
				(policy == BUFFER) ||
				(policy == EXECUTE)
			)
			{
				return true;
			}

			break;
		}
		case STYLE::ROYALGUARD:
		{
			auto & policy = actorData.nextActionRequestPolicy[ROYALGUARD];

			if
			(
				(policy == BUFFER) ||
				(policy == EXECUTE)
			)
			{
				return true;
			}

			break;
		}
	}

	return false;
}



export void CharacterSwitchController()
{
	if
	(
		!activeConfig.Actor.enable ||
		InCutscene()
	)
	{
		return;
	}



	static bool executes[PLAYER_COUNT] = {};


	// static float hitPoints  [PLAYER_COUNT] = {};
	// static float magicPoints[PLAYER_COUNT] = {};








	old_for_all(uint8, playerIndex, activeConfig.Actor.playerCount)
	{
		auto & gamepad = GetGamepad(playerIndex);


		{
			auto & playerData = GetPlayerData(playerIndex);

			if (playerData.characterCount < 2)
			{
				continue;
			}
		}



		auto IsDoppelgangerActive = [&]() -> bool
		{
			IntroducePlayerCharacterNewActorData(playerIndex);

			if (activeCharacterData.character >= CHARACTER::MAX)
			{
				return false;
			}

			IntroduceData(activeNewActorData.baseAddr, activeActorData, PlayerActorData, return false);

			return activeActorData.doppelganger;
		};



		if (IsDoppelgangerActive())
		{
			continue;
		}



		{
			auto & execute = executes[playerIndex];

			auto & playerData = GetPlayerData(playerIndex);

			if (gamepad.buttons[0] & playerData.button)
			{
				if (execute)
				{
					execute = false;

					playerData.characterIndex++;

					if (playerData.characterIndex >= playerData.characterCount)
					{
						playerData.characterIndex = 0;
					}
				}
			}
			else
			{
				execute = true;
			}
		}



		IntroducePlayerCharacterNewActorData(playerIndex);

		IntroduceData(leadNewActorData.baseAddr, leadActorData, PlayerActorData, continue);



		if
		(
			!activeNewActorData.baseAddr ||
			!newActorData.baseAddr
		)
		{
			continue;
		}



		if (playerData.lastCharacterIndex != playerData.characterIndex)
		{
			playerData.lastCharacterIndex = playerData.characterIndex;

			// @Todo: Prefer < CHARACTER::MAX.

			if (activeCharacterData.character == CHARACTER::BOSS_LADY)
			{
				auto & activeActorData = *reinterpret_cast<EnemyActorDataLady *>(activeNewActorData.baseAddr);
			}
			else if (activeCharacterData.character == CHARACTER::BOSS_VERGIL)
			{
				auto & activeActorData = *reinterpret_cast<EnemyActorDataVergil *>(activeNewActorData.baseAddr);
			}
			else
			{
				auto & activeActorData = *reinterpret_cast<PlayerActorData *>(activeNewActorData.baseAddr);

				ToggleInput(activeActorData, (playerData.characterIndex == playerData.activeCharacterIndex) ? true : false);
			}
		}



		if (playerData.characterIndex == playerData.activeCharacterIndex)
		{
			continue;
		}

		// At this point we have a valid new character index and we know that
		// we want another character.



		// @Research: Consider Save instead.
		auto UpdateHitMagicPoints = [&]()
		{
			IntroducePlayerCharacterNewActorData(playerIndex);

			if (activeCharacterData.character >= CHARACTER::MAX)
			{
				return;
			}

			IntroduceData(activeNewActorData.baseAddr, activeActorData, PlayerActorData, return);

			g_hitPoints  [playerIndex] = activeActorData.hitPoints;
			g_magicPoints[playerIndex] = activeActorData.magicPoints;
		};



		auto Update = [&]()
		{
			playerData.activeCharacterIndex = playerData.characterIndex;

			ToggleActor
			(
				activeCharacterData,
				activeNewActorData,
				false
			);

			ToggleActor
			(
				characterData,
				newActorData,
				true
			);



			[&]()
			{
				if (playerIndex != 0)
				{
					return;
				}



				if (characterData.character >= CHARACTER::MAX)
				{
					SetMainActor(leadActorData);

					return;
				}

				IntroduceData(newActorData.baseAddr, actorData, PlayerActorData, return);

				SetMainActor(actorData);



				HUD_UpdateStyleIcon
				(
					GetStyle(actorData),
					characterData.character
				);
			}();



			// If Boss enable lead actor's lock-on system.
			{
				auto & activeCharacterData = GetCharacterData
				(
					playerIndex,
					playerData.activeCharacterIndex,
					ENTITY::MAIN
				);

				if
				(
					(activeCharacterData.character == CHARACTER::BOSS_LADY  ) ||
					(activeCharacterData.character == CHARACTER::BOSS_VERGIL)
				)
				{
					leadActorData.newButtonMask =
					GetBinding(BINDING::LOCK_ON) |
					GetBinding(BINDING::CHANGE_TARGET);
				}
			}
		};



		if (activeCharacterData.character == CHARACTER::BOSS_LADY)
		{
			auto & activeActorData = *reinterpret_cast<EnemyActorDataLady *>(activeNewActorData.baseAddr);

			if (IsBossLadyActive(activeActorData))
			{
				continue;
			}
			else
			{
				Update();
			}
		}
		else if (activeCharacterData.character == CHARACTER::BOSS_VERGIL)
		{
			auto & activeActorData = *reinterpret_cast<EnemyActorDataVergil *>(activeNewActorData.baseAddr);

			if (IsBossVergilActive(activeActorData))
			{
				continue;
			}
			else
			{
				Update();
			}
		}
		else
		{
			auto & activeActorData = *reinterpret_cast<PlayerActorData *>(activeNewActorData.baseAddr);

			if (IsActive(activeActorData))
			{
				if
				(
					CanQueueMeleeAttack(activeActorData) &&
					(gamepad.buttons[0] & GetBinding(BINDING::MELEE_ATTACK)) &&
					(
						GetNextMeleeAction
						(
							activeCharacterData,
							activeNewActorData,
							characterData,
							newActorData
						) > 0
					)
				)
				{
					UpdateHitMagicPoints();

					CopyState
					(
						activeCharacterData,
						activeNewActorData,
						characterData,
						newActorData
					);

					EndMotion(activeActorData);

					Update();

					SetNextMeleeAction
					(
						activeCharacterData,
						activeNewActorData,
						characterData,
						newActorData
					);
				}
				else if
				(
					CanQueueStyleAction(activeActorData) &&
					(gamepad.buttons[0] & GetBinding(BINDING::STYLE_ACTION)) &&
					(
						GetNextStyleAction
						(
							activeCharacterData,
							activeNewActorData,
							characterData,
							newActorData
						) > 0
					)
				)
				{
					UpdateHitMagicPoints();

					CopyState
					(
						activeCharacterData,
						activeNewActorData,
						characterData,
						newActorData
					);

					EndMotion(activeActorData);

					Update();

					SetNextStyleAction
					(
						activeCharacterData,
						activeNewActorData,
						characterData,
						newActorData
					);
				}
			}
			else
			{
				UpdateHitMagicPoints();

				CopyState
				(
					activeCharacterData,
					activeNewActorData,
					characterData,
					newActorData,
					CopyStateFlags_FixPermissions
				);

				Update();
			}
		}
	}



	old_for_all(uint8, playerIndex   , activeConfig.Actor.playerCount){
	old_for_all(uint8, characterIndex, CHARACTER_COUNT               ){
	old_for_all(uint8, entityIndex   , ENTITY_COUNT                  )
	{
		IntroducePlayerCharacterNewActorData(playerIndex, characterIndex, entityIndex);

		IntroduceData(leadNewActorData.baseAddr, leadActorData, PlayerActorData, continue);

		auto & gamepad = GetGamepad(playerIndex);

		vec4 * activePositionAddr = 0;
		vec4 * positionAddr = 0;

		uint16 * activeRotationAddr = 0;
		uint16 * rotationAddr = 0;

		CollisionData * activeCollisionDataAddr = 0;
		CollisionData * collisionDataAddr = 0;



		if (!newActorData.baseAddr)
		{
			continue;
		}



		// Check if character is active character.

		if
		(
			(characterIndex == playerData.activeCharacterIndex) &&
			(entityIndex == ENTITY::MAIN)
		)
		{
			continue;
		}



		auto IsDoppelgangerActive = [&]() -> bool
		{
			if (mainCharacterData.character >= CHARACTER::MAX)
			{
				return false;
			}

			IntroduceData(mainNewActorData.baseAddr, mainActorData, PlayerActorData, return false);

			return mainActorData.doppelganger;
		};



		if
		(
			(characterData.character < CHARACTER::MAX) &&
			(entityIndex == ENTITY::CLONE) &&
			IsDoppelgangerActive()
		)
		{
			continue;
		}



		if (activeCharacterData.character == CHARACTER::BOSS_LADY)
		{
			auto & activeActorData = *reinterpret_cast<EnemyActorDataLady *>(activeNewActorData.baseAddr);

			activePositionAddr = &activeActorData.position;
			activeRotationAddr = &activeActorData.rotation2;
			/*
			Lady uses another variable for rotation and writes it to the default one.

			dmc3.exe+1711DA - 0FBF 86 205A0000  - movsx eax,word ptr [rsi+00005A20]
			dmc3.exe+1711E1 - 66 89 86 C0000000 - mov [rsi+000000C0],ax
			*/
			activeCollisionDataAddr = &activeActorData.collisionData;
		}
		else if (activeCharacterData.character == CHARACTER::BOSS_VERGIL)
		{
			auto & activeActorData = *reinterpret_cast<EnemyActorDataVergil *>(activeNewActorData.baseAddr);

			activePositionAddr = &activeActorData.position;
			activeRotationAddr = &activeActorData.rotation;
			activeCollisionDataAddr = &activeActorData.collisionData;
		}
		else
		{
			auto & activeActorData = *reinterpret_cast<PlayerActorData *>(activeNewActorData.baseAddr);

			activePositionAddr = &activeActorData.position;
			activeRotationAddr = &activeActorData.rotation;
			activeCollisionDataAddr = &activeActorData.collisionData;
		}



		if (characterData.character == CHARACTER::BOSS_LADY)
		{
			auto & actorData = *reinterpret_cast<EnemyActorDataLady *>(newActorData.baseAddr);

			positionAddr = &actorData.position;
			rotationAddr = &actorData.rotation2;
			/*
			Lady uses another variable for rotation and writes it to the default one.

			dmc3.exe+1711DA - 0FBF 86 205A0000  - movsx eax,word ptr [rsi+00005A20]
			dmc3.exe+1711E1 - 66 89 86 C0000000 - mov [rsi+000000C0],ax
			*/
			collisionDataAddr = &actorData.collisionData;
		}
		else if (characterData.character == CHARACTER::BOSS_VERGIL)
		{
			auto & actorData = *reinterpret_cast<EnemyActorDataVergil *>(newActorData.baseAddr);

			positionAddr = &actorData.position;
			rotationAddr = &actorData.rotation;
			collisionDataAddr = &actorData.collisionData;
		}
		else
		{
			auto & actorData = *reinterpret_cast<PlayerActorData *>(newActorData.baseAddr);

			positionAddr = &actorData.position;
			rotationAddr = &actorData.rotation;
			collisionDataAddr = &actorData.collisionData;
		}



		// Position

		[&]()
		{
			if
			(
				!activePositionAddr ||
				!positionAddr
			)
			{
				return;
			}

			auto & activePosition = *activePositionAddr;
			auto & position = *positionAddr;

			position = activePosition;
			position.a = 1.0f;
		}();



		// Rotation

		[&]()
		{
			if
			(
				!activeRotationAddr ||
				!rotationAddr
			)
			{
				return;
			}

			auto & activeRotation = *activeRotationAddr;
			auto & rotation = *rotationAddr;

			rotation = activeRotation;
		}();



		// CollisionData

		[&]()
		{
			if
			(
				!activeCollisionDataAddr ||
				!collisionDataAddr
			)
			{
				return;
			}

			auto & activeCollisionData = *activeCollisionDataAddr;
			auto & collisionData = *collisionDataAddr;

			auto activeMetadataAddr = activeCollisionData.metadataAddr;
			auto metadataAddr = collisionData.metadataAddr;



			if
			(
				!activeMetadataAddr ||
				!metadataAddr
			)
			{
				return;
			}

			auto & activeMetadata = *activeMetadataAddr;
			auto & metadata = *metadataAddr;



			metadata.data2[0] = activeMetadata.data2[0];
			metadata.data2[1] = activeMetadata.data2[1];
			metadata.data2[2] = activeMetadata.data2[2];

			//metadata.data2[0] = activePosition;
			metadata.data2[0].a = 1.0f;

			//metadata.data2[1] = activePosition;
			metadata.data2[1].a = 1.0f;

			//metadata.data2[2] = activePosition;
			metadata.data2[2].a = 1.0f;
		}();
	}}}



	// Set default actor position.
	[&]()
	{
		IntroduceData(g_newActorData[0][0][0].baseAddr , activeActorData, PlayerActorData, return);
		IntroduceData(g_defaultNewActorData[0].baseAddr, actorData      , PlayerActorData, return);

		actorData.position = activeActorData.position;
		actorData.rotation = activeActorData.rotation;
	}();



	// Force Sync Hit & Magic Points
	[&]()
	{
		if (!activeConfig.forceSyncHitMagicPoints)
		{
			return;
		}

		old_for_all(uint8, playerIndex   , activeConfig.Actor.playerCount){
		old_for_all(uint8, characterIndex, CHARACTER_COUNT               ){
		old_for_all(uint8, entityIndex   , ENTITY_COUNT                  )
		{
			IntroducePlayerCharacterNewActorData(playerIndex, characterIndex, entityIndex);

			IntroduceData(activeNewActorData.baseAddr, activeActorData, PlayerActorData, continue);
			IntroduceData(newActorData.baseAddr      , actorData      , PlayerActorData, continue);

			if
			(
				(
					(characterIndex == playerData.activeCharacterIndex) &&
					(entityIndex == ENTITY::MAIN)
				) ||
				(characterData.character >= CHARACTER::MAX)
			)
			{
				continue;
			}

			if (activeCharacterData.character >= CHARACTER::MAX)
			{
				actorData.hitPoints   = g_hitPoints  [playerIndex];
				actorData.magicPoints = g_magicPoints[playerIndex];
			}
			else
			{
				actorData.hitPoints   = activeActorData.hitPoints;
				actorData.magicPoints = activeActorData.magicPoints;
			}
		}}}
	}();
}



export void BossLadyController()
{
	IntroducePlayerCharacterNewActorData();

	IntroduceData(activeNewActorData.baseAddr, activeActorData, EnemyActorDataLady, return);

	IntroduceData(leadNewActorData.baseAddr, leadActorData, PlayerActorData, return);

	static bool executes[8] = {};

	auto & gamepad = GetGamepad(0);

	auto tiltDirection = GetRelativeTiltDirection(leadActorData);

	auto lockOn = (gamepad.buttons[0] & GetBinding(BINDING::LOCK_ON));



	// We don't have to check for idle stuff, the character switch controller
	// will take care of that for us.



	if (activeCharacterData.character != CHARACTER::BOSS_LADY)
	{
		return;
	}

	// At this point we know that all necessary variables are available and
	// the player's active character is Boss Lady.



	// Check if lead actor is ready or Boss Lady is already doing something.

	if
	(
		IsActive(leadActorData) ||
		IsBossLadyActive(activeActorData)
	)
	{
		return;
	}



	using namespace EVENT_BOSS_LADY;

	// Wheel
	{
		auto & execute = executes[0];

		if (gamepad.buttons[0] & GetBinding(BINDING::JUMP))
		{
			if (execute)
			{
				execute = false;

				uint32 event = 0;

				if (lockOn)
				{
					if (tiltDirection == TILT_DIRECTION::UP)
					{
						event = TROOPER_ROLL;
					}
					else if (tiltDirection == TILT_DIRECTION::RIGHT)
					{
						event = WHEEL_RIGHT;
					}
					else if (tiltDirection == TILT_DIRECTION::DOWN)
					{
						event = WHEEL_BACK;
					}
					else if (tiltDirection == TILT_DIRECTION::LEFT)
					{
						event = WHEEL_LEFT;
					}
				}

				if (event > 0)
				{
					activeActorData.event = event;
					activeActorData.state = 0;
				}
			}
		}
		else
		{
			execute = true;
		}
	}

	// Reload Pistol
	{
		auto & execute = executes[1];

		if (gamepad.buttons[0] & GetBinding(BINDING::CHANGE_DEVIL_ARMS))
		{
			if (execute)
			{
				execute = false;

				activeActorData.event = PISTOL_RELOAD;
				activeActorData.state = 0;
			}
		}
		else
		{
			execute = true;
		}
	}

	// Reload SMG
	{
		auto & execute = executes[2];

		if (gamepad.buttons[0] & GetBinding(BINDING::CHANGE_GUN))
		{
			if (execute)
			{
				execute = false;

				activeActorData.event = SMG_RELOAD;
				activeActorData.state = 0;
			}
		}
		else
		{
			execute = true;
		}
	}

	// Pistol
	{
		auto & execute = executes[3];

		if (gamepad.buttons[0] & GetBinding(BINDING::SHOOT))
		{
			if (execute)
			{
				execute = false;

				uint32 event = 0;

				if (lockOn)
				{
					if (tiltDirection == TILT_DIRECTION::DOWN)
					{
						event = FALL_BACK_SHOOT;
					}
				}

				if (event > 0)
				{
					activeActorData.event = event;
					activeActorData.state = 0;
				}
			}
		}
		else
		{
			execute = true;
		}
	}

	// SMG
	{
		auto & execute = executes[4];

		if (gamepad.buttons[0] & GetBinding(BINDING::STYLE_ACTION))
		{
			if (execute)
			{
				execute = false;

				activeActorData.event = SMG_ROUNDHOUSE;
				activeActorData.state = 0;
			}
		}
		else
		{
			execute = true;
		}
	}

	// Kalina Ann
	{
		auto & execute = executes[5];

		if (gamepad.buttons[0] & GetBinding(BINDING::MELEE_ATTACK))
		{
			if (execute)
			{
				execute = false;

				uint32 event = KALINA_ANN_HOOK;

				if (lockOn)
				{
					if (tiltDirection == TILT_DIRECTION::UP)
					{
						event = KALINA_ANN_CHARGED_SHOT;
					}
					else if (tiltDirection == TILT_DIRECTION::DOWN)
					{
						event = KALINA_ANN_HYSTERIC;
					}
				}

				activeActorData.event = event;
				activeActorData.state = 0;
			}
		}
		else
		{
			execute = true;
		}
	}

	// Grenade
	{
		auto & execute = executes[6];

		if (gamepad.buttons[0] & GetBinding(BINDING::DEVIL_TRIGGER))
		{
			if (execute)
			{
				execute = false;

				uint32 event = GRENADE_THROW;

				activeActorData.event = event;
				activeActorData.state = 0;
			}
		}
		else
		{
			execute = true;
		}
	}
}

export void BossVergilController()
{
	IntroducePlayerCharacterNewActorData();

	IntroduceData(activeNewActorData.baseAddr, activeActorData, EnemyActorDataVergil, return);

	IntroduceData(leadNewActorData.baseAddr, leadActorData, PlayerActorData, return);

	static bool executes[8] = {};

	auto & gamepad = GetGamepad(0);

	auto tiltDirection = GetRelativeTiltDirection(leadActorData);

	auto lockOn = (gamepad.buttons[0] & GetBinding(BINDING::LOCK_ON));



	// We don't have to check for idle stuff, the character switch controller
	// will take care of that for us.



	if (activeCharacterData.character != CHARACTER::BOSS_VERGIL)
	{
		return;
	}

	// At this point we know that all necessary variables are available and
	// the player's active character is Boss Vergil.



	// Check if lead actor is ready or Boss Vergil is already doing something.

	if
	(
		IsActive(leadActorData) ||
		IsBossVergilActive(activeActorData)
	)
	{
		return;
	}



	using namespace EVENT_BOSS_VERGIL;

	// Boss Vergil Judgement Cut
	{
		auto & execute = executes[0];

		if (gamepad.buttons[0] & GetBinding(BINDING::MELEE_ATTACK))
		{
			if (execute)
			{
				execute = false;

				uint32 event = YAMATO_DEFLECT;

				if (lockOn)
				{
					if (tiltDirection == TILT_DIRECTION::UP)
					{
						event = YAMATO_SUPER_JUDGEMENT_CUT_FOLLOW;
					}
					else if (tiltDirection == TILT_DIRECTION::DOWN)
					{
						event = YAMATO_SUPER_JUDGEMENT_CUT;
					}
				}

				activeActorData.event = event;
				activeActorData.state = 0;
			}
		}
		else
		{
			execute = true;
		}
	}

	// Boss Vergil Block
	{
		auto & execute = executes[1];

		if (gamepad.buttons[0] & GetBinding(BINDING::STYLE_ACTION))
		{
			if (execute)
			{
				execute = false;

				activeActorData.event = BLOCK;
				activeActorData.state = 0;
			}
		}
		else
		{
			execute = true;
		}
	}

	// Boss Vergil Shield
	{
		auto & execute = executes[2];

		if (gamepad.buttons[0] & GetBinding(BINDING::SHOOT))
		{
			if (execute)
			{
				execute = false;

				uint32 event = SHIELD;

				if (lockOn)
				{
					if (tiltDirection == TILT_DIRECTION::UP)
					{
						event = STRONG_SHIELD;
						activeActorData.variant = 1;
					}
					else if (tiltDirection == TILT_DIRECTION::DOWN)
					{
						event = STRONG_SHIELD;
						activeActorData.variant = 2;
					}
				}

				activeActorData.event = event;
				activeActorData.state = 0;
			}
		}
		else
		{
			execute = true;
		}
	}

	// Boss Vergil Toggle Devil
	{
		auto & execute = executes[3];

		if (gamepad.buttons[0] & GetBinding(BINDING::DEVIL_TRIGGER))
		{
			if (execute)
			{
				execute = false;

				activeActorData.event = (activeActorData.devil) ? LEAVE_DEVIL_FORM : IDLE;
				activeActorData.state = 0;
				activeActorData.toggleDevil = true;
			}
		}
		else
		{
			execute = true;
		}
	}

	// Boss Vergil Taunt
	{
		auto & execute = executes[4];

		if (gamepad.buttons[0] & GetBinding(BINDING::CHANGE_GUN))
		{
			if (execute)
			{
				execute = false;

				activeActorData.event = TAUNT;
				activeActorData.state = 0;

				static uint32 variant = 2;

				variant++;

				if (variant >= 3)
				{
					variant = 0;
				}

				activeActorData.variant = variant;
			}
		}
		else
		{
			execute = true;
		}
	}

	// Boss Vergil Taunt 2
	{
		auto & execute = executes[5];

		if (gamepad.buttons[0] & GetBinding(BINDING::CHANGE_DEVIL_ARMS))
		{
			if (execute)
			{
				execute = false;

				activeActorData.event = REST_IN_PEACE;
				activeActorData.state = 4;
			}
		}
		else
		{
			execute = true;
		}
	}
}















// Used by all Hells, Hell Vanguard and Abyss.

void SetNewEventEnemy
(
	byte8 * dest,
	uint32 newEvent
)
{
	if (!activeConfig.enablePVPFixes)
	{
		return;
	}

	// LogFunction();

	// auto baseAddr = (*reinterpret_cast<byte8 **>(dest + 0x20) - 0x60);

	// Log("baseAddr %llX", baseAddr);

	auto & event = *reinterpret_cast<uint32 *>(dest + 0xF4);
	auto & state = *reinterpret_cast<uint32 *>(dest + 0xF8);
	/*
	dmc3.exe+65880 - 89 91 F4000000          - mov [rcx+000000F4],edx
	dmc3.exe+65886 - C7 81 F8000000 00000000 - mov [rcx+000000F8],00000000
	*/

	using namespace EVENT_ENEMY;



	if (newEvent != SPAWN)
	{
		event = IDLE;
		state = 0;
	}
}

void SetNewEventBossLady
(
	EnemyActorDataLady & actorData,
	uint32 newEvent
)
{
	if (!activeConfig.enableBossLadyFixes)
	{
		actorData.event = newEvent;
		actorData.state = 0;

		return;
	}



	auto & gamepad = GetGamepad(0);

	using namespace EVENT_BOSS_LADY;



	if (actorData.event == FALL_BACK_SHOOT)
	{
		actorData.event = (gamepad.buttons[0] & GetBinding(BINDING::SHOOT)) ? FALL_BACK_RECOVER_CROSSBOW : FALL_BACK_RECOVER;
		actorData.state = 0;

		return;
	}



	actorData.event = IDLE;
	actorData.state = 0;
	actorData.phase = 1;
}

void SetNewEventBossVergil
(
	EnemyActorDataVergil & actorData,
	uint32 newEvent
)
{
	if (!activeConfig.enableBossVergilFixes)
	{
		actorData.event = newEvent;
		actorData.state = 0;

		return;
	}



	actorData.event = 0;
	actorData.state = 0;
	actorData.variant = 2;
}




// @Todo: Update order.
export void ToggleBossLadyFixes(bool enable)
{
	LogFunction(enable);

	static bool run = false;



	// Disable HUD
	{
		auto addr = (appBaseAddr + 0x16FD32);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+16FD32 - E8 097F0400       - call dmc3.exe+1B7C40
		dmc3.exe+16FD37 - 48 8D 93 F8560000 - lea rdx,[rbx+000056F8]
		*/

		constexpr byte8 sect0[] =
		{
			0x48, 0x31, 0xC0, // xor rax,rax
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

	// Disable HUD 2
	{
		auto addr = (appBaseAddr + 0x16FD48);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+16FD48 - E8 A3F61000       - call dmc3.exe+27F3F0
		dmc3.exe+16FD4D - 48 89 83 00590000 - mov [rbx+00005900],rax
		*/

		constexpr byte8 sect0[] =
		{
			0x48, 0x31, 0xC0, // xor rax,rax
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















	// Disable Lock-On Update
	{
		auto addr = (appBaseAddr + 0x171387);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+171387 - E8 B4A20400         - call dmc3.exe+1BB640
		dmc3.exe+17138C - F3 0F10 86 58590000 - movss xmm0,[rsi+00005958]
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

	// Disable Set Boss Camera
	{
		auto addr = (appBaseAddr + 0x16FF3E);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+16FF3E - E8 9D701500 - call dmc3.exe+2C6FE0
		dmc3.exe+16FF43 - FE 43 A8    - inc byte ptr [rbx-58]
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



	#pragma region Update Position

	// Default
	{
		auto addr     = (appBaseAddr + 0x16FC65);
		auto jumpAddr = (appBaseAddr + 0x16FC70);
		constexpr uint32 size = 11;
		/*
		dmc3.exe+16FC65 - 48 8B 81 10010000 - mov rax,[rcx+00000110]
		dmc3.exe+16FC6C - 48 83 C0 30       - add rax,30
		dmc3.exe+16FC70 - 48 83 C4 28       - add rsp,28
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0x8B, 0x05, 0x00, 0x00, 0x00, 0x00, // mov rax,[dmc3.exe+C90E28]
			0x48, 0x8B, 0x40, 0x18,                   // mov rax,[rax+18]
			0x48, 0x05, 0x00, 0x63, 0x00, 0x00,       // add rax,00006300
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteAddress(func.sect0, (appBaseAddr + 0xC90E28), 7);
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

	// Kalina Ann Charged Shot
	{
		auto addr     = (appBaseAddr + 0x173D68);
		auto jumpAddr = (appBaseAddr + 0x173D6D);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+173D68 - E8 030B0D00       - call dmc3.exe+244870
		dmc3.exe+173D6D - 48 8B 05 B4D0B100 - mov rax,[dmc3.exe+C90E28]
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0x8B, 0x15, 0x00, 0x00, 0x00, 0x00, // mov rdx,[dmc3.exe+C90E28]
			0x48, 0x8B, 0x52, 0x18,                   // mov rdx,[rdx+18]
			0x48, 0x81, 0xC2, 0x00, 0x63, 0x00, 0x00, // add rdx,00006300
			0xE8, 0x00, 0x00, 0x00, 0x00,             // call dmc3.exe+244870
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteAddress(func.sect0, (appBaseAddr + 0xC90E28), 7);
			WriteAddress((func.sect0 + 0x12), (appBaseAddr + 0x244870), 5);
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

	// Kalina Ann Hysteric
	{
		auto addr     = (appBaseAddr + 0x17307A);
		auto jumpAddr = (appBaseAddr + 0x173085);
		constexpr uint32 size = 11;
		/*
		dmc3.exe+17307A - 48 8B 99 10010000 - mov rbx,[rcx+00000110]
		dmc3.exe+173081 - 48 83 C3 30       - add rbx,30
		dmc3.exe+173085 - 80 BF 5E050000 00 - cmp byte ptr [rdi+0000055E],00
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0x8B, 0x1D, 0x00, 0x00, 0x00, 0x00, // mov rbx,[dmc3.exe+C90E28]
			0x48, 0x8B, 0x5B, 0x18,                   // mov rbx,[rbx+18]
			0x48, 0x81, 0xC3, 0x00, 0x63, 0x00, 0x00, // add rbx,00006300
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteAddress(func.sect0, (appBaseAddr + 0xC90E28), 7);
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

	// Kalina Ann Hysteric 2
	{
		auto addr = (appBaseAddr + 0x17308C);
		constexpr uint32 size = 2;
		/*
		dmc3.exe+17308C - 75 74             - jne dmc3.exe+173102
		dmc3.exe+17308E - 83 BF 58050000 03 - cmp dword ptr [rdi+00000558],03
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




	// Kalina Ann Hook SMG Shoot
	{
		auto addr = (appBaseAddr + 0x171D02);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+171D02 - F3 0F10 80 80000000 - movss xmm0,[rax+00000080]
		dmc3.exe+171D0A - F3 0F5C 83 80000000 - subss xmm0,[rbx+00000080]
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			*reinterpret_cast<byte32 *>(addr + 4) = 0x6300;
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Kalina Ann Hook SMG Shoot 2
	{
		auto addr = (appBaseAddr + 0x171D1C);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+171D1C - F3 0F10 88 84000000 - movss xmm1,[rax+00000084]
		dmc3.exe+171D24 - F3 0F5C 8B 84000000 - subss xmm1,[rbx+00000084]
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			*reinterpret_cast<byte32 *>(addr + 4) = 0x6300 + 4;
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Kalina Ann Hook SMG Shoot 3
	{
		auto addr = (appBaseAddr + 0x171D3B);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+171D3B - F3 0F10 80 88000000 - movss xmm0,[rax+00000088]
		dmc3.exe+171D43 - F3 0F5C 83 88000000 - subss xmm0,[rbx+00000088]
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			*reinterpret_cast<byte32 *>(addr + 4) = 0x6300 + 8;
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Kalina Ann Hook Disable Random Position
	{
		auto addr = (appBaseAddr + 0x16CF98);
		constexpr uint32 size = 2;
		/*
		dmc3.exe+16CF98 - 89 06          - mov [rsi],eax
		dmc3.exe+16CF9A - 8B 87 C8590000 - mov eax,[rdi+000059C8]
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

	// Kalina Ann Hook Disable Random Position 2
	{
		auto addr = (appBaseAddr + 0x16CFA8);
		constexpr uint32 size = 16;
		/*
		dmc3.exe+16CFA8 - C7 87 8C000000 0000803F - mov [rdi+0000008C],3F800000
		dmc3.exe+16CFB2 - 89 87 88000000          - mov [rdi+00000088],eax
		dmc3.exe+16CFB8 - 48 8B 8F 98590000       - mov rcx,[rdi+00005998]
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

















	#pragma endregion

	#pragma region Disable Rotation Update

	// Wheel Forward
	{
		auto addr = (appBaseAddr + 0x16BE08);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+16BE08 - E8 D3B41500       - call dmc3.exe+2C72E0
		dmc3.exe+16BE0D - 48 8D 8B 90510000 - lea rcx,[rbx+00005190]
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

	// Wheel Back
	{
		auto addr = (appBaseAddr + 0x16B86E);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+16B86E - E8 6DBA1500       - call dmc3.exe+2C72E0
		dmc3.exe+16B873 - 48 8D 8B 90510000 - lea rcx,[rbx+00005190]
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

	// Pistol Fall Back
	{
		auto addr = (appBaseAddr + 0x16BB4E);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+16BB4E - E8 8DB71500       - call dmc3.exe+2C72E0
		dmc3.exe+16BB53 - 48 8D 8B 50020000 - lea rcx,[rbx+00000250]
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

	// SMG Roundhouse
	{
		auto addr = (appBaseAddr + 0x16D44A);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+16D44A - E8 919E1500       - call dmc3.exe+2C72E0
		dmc3.exe+16D44F - 48 8D 8B 50020000 - lea rcx,[rbx+00000250]
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

	// Kalina Ann Hook
	{
		auto addr = (appBaseAddr + 0x16CB47);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+16CB47 - E8 94A71500       - call dmc3.exe+2C72E0
		dmc3.exe+16CB4C - 48 8B 87 50020000 - mov rax,[rdi+00000250]
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




/*

dmc3.exe+2CBC62 - E8 9950D6FF           - call dmc3.exe+30D00

dmc3.exe+16CB77 - F3 0F10 05 8DE84000   - movss xmm0,[dmc3.exe+57B40C] { (1820.00) }







*/


















	// Kalina Ann Hook 2
	{
		auto addr = (appBaseAddr + 0x16CB8E);
		constexpr uint32 size = 6;
		/*
		dmc3.exe+16CB8E - 0F86 C5050000     - jbe dmc3.exe+16D159
		dmc3.exe+16CB94 - 48 8B 87 50020000 - mov rax,[rdi+00000250]
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			WriteAddress(addr, (appBaseAddr + 0x16CB94), size);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Kalina Ann Charged Shot
	{
		auto addr = (appBaseAddr + 0x16DC18);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+16DC18 - E8 C3961500       - call dmc3.exe+2C72E0
		dmc3.exe+16DC1D - 48 8D 8B 50020000 - lea rcx,[rbx+00000250]
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

	// Kalina Ann Charged Shot 2
	{
		auto addr = (appBaseAddr + 0x16DB81);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+16DB81 - E8 5A971500 - call dmc3.exe+2C72E0
		dmc3.exe+16DB86 - 45 33 C0    - xor r8d,r8d
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

	// Kalina Ann Hysteric
	{
		auto addr = (appBaseAddr + 0x16D60F);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+16D60F - E8 CC9C1500       - call dmc3.exe+2C72E0
		dmc3.exe+16D614 - 48 8B 86 50020000 - mov rax,[rsi+00000250]
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

	// Kalina Ann Hysteric 2
	{
		auto addr = (appBaseAddr + 0x16D567);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+16D567 - E8 749D1500       - call dmc3.exe+2C72E0
		dmc3.exe+16D56C - 48 8D 9E 50020000 - lea rbx,[rsi+00000250]
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

	// Grenade Throw
	{
		auto addr = (appBaseAddr + 0x16D80A);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+16D80A - E8 D19A1500       - call dmc3.exe+2C72E0
		dmc3.exe+16D80F - 48 8B 83 50020000 - mov rax,[rbx+00000250]
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

	// Grenade Throw Jump
	{
		auto addr = (appBaseAddr + 0x16D8B5);
		constexpr uint32 size = 2;
		/*
		dmc3.exe+16D8B5 - 76 18       - jna dmc3.exe+16D8CF
		dmc3.exe+16D8B7 - E8 548F1500 - call dmc3.exe+2C6810
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

	// Grenade Throw Jump 2
	{
		auto addr = (appBaseAddr + 0x16D8CF);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+16D8CF - E8 3C8F1500    - call dmc3.exe+2C6810
		dmc3.exe+16D8D4 - 48 8B 74 24 40 - mov rsi,[rsp+40]
		*/

		constexpr byte8 sect0[] =
		{
			0x66, 0x8B, 0x07, // mov ax,[rdi]
		};
		/*
		dmc3.exe+16D7E8 - 48 8D BB 205A0000 - lea rdi,[rbx+00005A20]
		dmc3.exe+16D7EF - 66 2B 07          - sub ax,[rdi]
		*/

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

	#pragma endregion

	#pragma region Update Collision Flags

	// Pistol Fall Back Recover Crossbow
	{
		auto addr = (appBaseAddr + 0x175E47);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+175E47 - C7 83 C0020000 43040300 - mov [rbx+000002C0],00030443
		dmc3.exe+175E51 - EB 17                   - jmp dmc3.exe+175E6A
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			*reinterpret_cast<byte32 *>(addr + 6) = CollisionFlags_Enemy;
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// SMG Roundhouse
	{
		auto addr = (appBaseAddr + 0x172505);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+172505 - C7 83 C0020000 43040300 - mov [rbx+000002C0],00030443
		dmc3.exe+17250F - EB 17                   - jmp dmc3.exe+172528
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			*reinterpret_cast<byte32 *>(addr + 6) = CollisionFlags_Enemy;
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Kalina Ann Charged Shot
	{
		auto addr = (appBaseAddr + 0x173B5D);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+173B5D - C7 86 D0020000 43040300 - mov [rsi+000002D0],00030443
		dmc3.exe+173B67 - EB 17                   - jmp dmc3.exe+173B80
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			*reinterpret_cast<byte32 *>(addr + 6) = CollisionFlags_Enemy;
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Kalina Ann Hysteric
	{
		auto addr = (appBaseAddr + 0x172DF6);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+172DF6 - C7 87 C0020000 43040300 - mov [rdi+000002C0],00030443
		dmc3.exe+172E00 - 48 8D 8F 80010000       - lea rcx,[rdi+00000180]
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			*reinterpret_cast<byte32 *>(addr + 6) = CollisionFlags_Enemy;
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Grenade Throw
	{
		auto addr = (appBaseAddr + 0x175672);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+175672 - C7 87 C0020000 43040300 - mov [rdi+000002C0],00030443
		dmc3.exe+17567C - 48 8D 8F 80010000       - lea rcx,[rdi+00000180]
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			*reinterpret_cast<byte32 *>(addr + 6) = CollisionFlags_Enemy;
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	#pragma endregion




// Kalina Ann Hook Multiplier
{
	auto addr     = (appBaseAddr + 0x16CC10);
	auto jumpAddr = (appBaseAddr + 0x16CC15);
	constexpr uint32 size = 5;
	/*
	dmc3.exe+16CC10 - E8 FB290000         - call dmc3.exe+16F610
	dmc3.exe+16CC15 - F3 0F10 05 43E84000 - movss xmm0,[dmc3.exe+57B460]
	*/

	static Function func = {};

	constexpr byte8 sect0[] =
	{
		0xE8, 0x00, 0x00, 0x00, 0x00,                               // call dmc3.exe+16F610
		0x0F, 0x28, 0x87, 0xD0, 0x59, 0x00, 0x00,                   // movaps xmm0,[rdi+000059D0]
		0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rax
		0x0F, 0x59, 0x00,                                           // mulps xmm0,[rax]
		0x0F, 0x29, 0x87, 0xD0, 0x59, 0x00, 0x00,                   // movaps [rdi+000059D0],xmm0
	};

	if (!run)
	{
		backupHelper.Save(addr, size);
		func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
		CopyMemory(func.sect0, sect0, sizeof(sect0));
		WriteAddress(func.sect0, (appBaseAddr + 0x16F610), 5);
		*reinterpret_cast<vec4 **>(func.sect0 + 0xE) = &activeConfig.kalinaAnnHookMultiplier;
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






// Kalina Ann Hook Add Grenade Throw
{
	auto addr     = (appBaseAddr + 0x16CC61);
	auto jumpAddr = (appBaseAddr + 0x16CC66);
	constexpr uint32 size = 5;
	/*
	dmc3.exe+16CC61 - E8 EAA61800 - call dmc3.exe+2F7350
	dmc3.exe+16CC66 - E9 EE040000 - jmp dmc3.exe+16D159
	*/

	static Function func = {};

	constexpr byte8 sect0[] =
	{
		0xE8, 0x00, 0x00, 0x00, 0x00,                               // call dmc3.exe+2F7350
		0x0F, 0x28, 0x87, 0x80, 0x00, 0x00, 0x00,                   // movaps xmm0,[rdi+00000080]
		0x0F, 0x29, 0x44, 0x24, 0x20,                               // movaps [rsp+20],xmm0
		0xF3, 0x0F, 0x10, 0x44, 0x24, 0x24,                         // movss xmm0,[rsp+24]
		0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rax
		0xF3, 0x0F, 0x58, 0x00,                                     // addss xmm0,dword ptr [rax]
		0xF3, 0x0F, 0x11, 0x44, 0x24, 0x24,                         // movss [rsp+24],xmm0
		0x0F, 0x57, 0xC0,                                           // xorps xmm0,xmm0
		0x0F, 0x29, 0x44, 0x24, 0x30,                               // movaps [rsp+30],xmm0
		0xC7, 0x44, 0x24, 0x3C, 0x00, 0x00, 0x80, 0x3F,             // mov [rsp+3C],3F800000
		0x48, 0x8D, 0x4C, 0x24, 0x20,                               // lea rcx,[rsp+20]
		0x48, 0x8D, 0x54, 0x24, 0x30,                               // lea rdx,[rsp+30]
		0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rax
		0xF3, 0x0F, 0x10, 0x10,                                     // movss xmm2,[rax]
		0xE8, 0x00, 0x00, 0x00, 0x00,                               // call dmc3.exe+175210
	};

	if (!run)
	{
		backupHelper.Save(addr, size);
		func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
		CopyMemory(func.sect0, sect0, sizeof(sect0));
		WriteAddress(func.sect0, (appBaseAddr + 0x2F7350), 5);
		*reinterpret_cast<float **>(func.sect0 + 0x19) = &activeConfig.kalinaAnnHookGrenadeHeight;
		*reinterpret_cast<float **>(func.sect0 + 0x47) = &activeConfig.kalinaAnnHookGrenadeTime;
		WriteAddress((func.sect0 + 0x53), (appBaseAddr + 0x175210), 5);
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



// @Todo: Dante Sword Pierce IsActive exception.








// @Todo: Update order.


export void ToggleBossVergilFixes(bool enable)
{
	LogFunction(enable);

	static bool run = false;



	// Disable HUD
	{
		auto addr = (appBaseAddr + 0x181942);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+181942 - E8 F9620300         - call dmc3.exe+1B7C40
		dmc3.exe+181947 - F3 0F10 97 C8EA0000 - movss xmm2,[rdi+0000EAC8]
		*/

		constexpr byte8 sect0[] =
		{
			0x48, 0x31, 0xC0, // xor rax,rax
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

	// Disable HUD 2
	{
		auto addr = (appBaseAddr + 0x18195C);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+18195C - E8 8FDA0F00       - call dmc3.exe+27F3F0
		dmc3.exe+181961 - 48 8B 8F E01B0000 - mov rcx,[rdi+00001BE0]
		*/

		constexpr byte8 sect0[] =
		{
			0x48, 0x31, 0xC0, // xor rax,rax
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







	// Disable Lock-On Update
	{
		auto addr = (appBaseAddr + 0x185732);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+185732 - E8 095F0300         - call dmc3.exe+1BB640
		dmc3.exe+185737 - F3 0F10 87 24ED0000 - movss xmm0,[rdi+0000ED24]
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

	// Disable Set Boss Camera
	{
		auto addr = (appBaseAddr + 0x181B05);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+181B05 - E8 D6541400 - call dmc3.exe+2C6FE0
		dmc3.exe+181B0A - 48 8B CE    - mov rcx,rsi
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



	#pragma region Update Position

	// Yamato Super Judgement Cut
	{
		auto addr     = (appBaseAddr + 0x17D69E);
		auto jumpAddr = (appBaseAddr + 0x17D6A9);
		constexpr uint32 size = 11;
		/*
		dmc3.exe+17D69E - 48 8B 81 10010000 - mov rax,[rcx+00000110]
		dmc3.exe+17D6A5 - 0F28 48 30        - movaps xmm1,[rax+30]
		dmc3.exe+17D6A9 - 83 AF B4ED0000 01 - sub dword ptr [rdi+0000EDB4],01
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0x8B, 0x05, 0x00, 0x00, 0x00, 0x00, // mov rax,[dmc3.exe+C90E28]
			0x48, 0x8B, 0x40, 0x18,                   // mov rax,[rax+18]
			0x48, 0x05, 0x00, 0x63, 0x00, 0x00,       // add rax,00006300
			0x0F, 0x28, 0x08,                         // movaps xmm1,[rax]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteAddress(func.sect0, (appBaseAddr + 0xC90E28), 7);
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

	// Yamato Super Judgement Cut Follow
	{
		auto addr     = (appBaseAddr + 0x17DA0D);
		auto jumpAddr = (appBaseAddr + 0x17DA18);
		constexpr uint32 size = 11;
		/*
		dmc3.exe+17DA0D - 48 8B 89 10010000 - mov rcx,[rcx+00000110]
		dmc3.exe+17DA14 - 48 83 C1 30       - add rcx,30
		dmc3.exe+17DA18 - 0F28 01           - movaps xmm0,[rcx]
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, // mov rcx,[dmc3.exe+C90E28]
			0x48, 0x8B, 0x49, 0x18,                   // mov rcx,[rcx+18]
			0x48, 0x81, 0xC1, 0x00, 0x63, 0x00, 0x00, // add rcx,00006300
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteAddress(func.sect0, (appBaseAddr + 0xC90E28), 7);
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

	// Default Summoned Swords
	{
		auto addr     = (appBaseAddr + 0x1892B7);
		auto jumpAddr = (appBaseAddr + 0x1892C2);
		constexpr uint32 size = 11;
		/*
		dmc3.exe+1892B7 - 48 8B 81 10010000 - mov rax,[rcx+00000110]
		dmc3.exe+1892BE - 0F28 40 30        - movaps xmm0,[rax+30]
		dmc3.exe+1892C2 - 0F5C 86 80000000  - subps xmm0,[rsi+00000080]
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0x8B, 0x05, 0x00, 0x00, 0x00, 0x00, // mov rax,[dmc3.exe+C90E28]
			0x48, 0x8B, 0x40, 0x18,                   // mov rax,[rax+18]
			0x48, 0x05, 0x00, 0x63, 0x00, 0x00,       // add rax,00006300
			0x0F, 0x28, 0x00,                         // movaps xmm0,[rax]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteAddress(func.sect0, (appBaseAddr + 0xC90E28), 7);
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

	// Strong Summoned Swords
	{
		auto addr     = (appBaseAddr + 0x188FB8);
		auto jumpAddr = (appBaseAddr + 0x188FC3);
		constexpr uint32 size = 11;
		/*
		dmc3.exe+188FB8 - 48 8B 99 10010000 - mov rbx,[rcx+00000110]
		dmc3.exe+188FBF - 48 83 C3 30       - add rbx,30
		dmc3.exe+188FC3 - 0F28 03           - movaps xmm0,[rbx]
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0x8B, 0x1D, 0x00, 0x00, 0x00, 0x00, // mov rbx,[dmc3.exe+C90E28]
			0x48, 0x8B, 0x5B, 0x18,                   // mov rbx,[rbx+18]
			0x48, 0x81, 0xC3, 0x00, 0x63, 0x00, 0x00, // add rbx,00006300
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteAddress(func.sect0, (appBaseAddr + 0xC90E28), 7);
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

	#pragma endregion

	#pragma region Disable Rotation Update

	// Taunt
	{
		auto addr = (appBaseAddr + 0x17F070);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+17F070 - E8 6B821400       - call dmc3.exe+2C72E0
		dmc3.exe+17F075 - 48 8B 83 80010000 - mov rax,[rbx+00000180]
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

	// Yamato Deflect
	{
		auto addr = (appBaseAddr + 0x17E35F);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+17E35F - E8 7C8F1400 - call dmc3.exe+2C72E0
		dmc3.exe+17E364 - 48 8B CB    - mov rcx,rbx
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

	// Yamato Super Judgement Cut
	{
		auto addr = (appBaseAddr + 0x178D22);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+178D22 - E8 B9E51400 - call dmc3.exe+2C72E0
		dmc3.exe+178D27 - E9 A8000000 - jmp dmc3.exe+178DD4
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

	// Yamato Super Judgement Cut 2
	{
		auto addr = (appBaseAddr + 0x17D4F0);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+17D4F0 - 66 89 87 C0000000 - mov [rdi+000000C0],ax
		dmc3.exe+17D4F7 - E9 7B040000       - jmp dmc3.exe+17D977
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

	#pragma endregion

	#pragma region Update Collision Flags

	// Yamato Super Judgement Cut
	{
		auto addr = (appBaseAddr + 0x188825);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+188825 - C7 83 C0020000 40040000 - mov [rbx+000002C0],00000440
		dmc3.exe+18882F - BA 11000000             - mov edx,00000011
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			*reinterpret_cast<byte32 *>(addr + 6) = CollisionFlags_Enemy;
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Summoned Sword
	{
		auto addr = (appBaseAddr + 0x189C43);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+189C43 - C7 85 F0020000 43040000 - mov [rbp+000002F0],00000443
		dmc3.exe+189C4D - 48 8D 8D B0010000       - lea rcx,[rbp+000001B0]
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			*reinterpret_cast<byte32 *>(addr + 6) = CollisionFlags_Enemy;
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Default Summoned Swords
	{
		auto addr = (appBaseAddr + 0x18A226);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+18A226 - C7 40 14 43040300 - mov [rax+14],00030443
		dmc3.exe+18A22D - 33 D2             - xor edx,edx
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			*reinterpret_cast<byte32 *>(addr + 3) = CollisionFlags_Enemy;
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Strong Summoned Swords
	{
		auto addr = (appBaseAddr + 0x189845);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+189845 - C7 40 14 43040300 - mov [rax+14],00030443
		dmc3.exe+18984C - 48 8B 4C 24 40    - mov rcx,[rsp+40]
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			*reinterpret_cast<byte32 *>(addr + 3) = CollisionFlags_Enemy;
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Strong Summoned Swords Low
	{
		auto addr = (appBaseAddr + 0x18A4C7);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+18A4C7 - C7 40 14 43040300 - mov [rax+14],00030443
		dmc3.exe+18A4CE - 48 8B 4C 24 40    - mov rcx,[rsp+40]
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			*reinterpret_cast<byte32 *>(addr + 3) = CollisionFlags_Enemy;
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	#pragma endregion

	#pragma region Disable Random Devil Trigger

	// Default
	{
		auto addr = (appBaseAddr + 0x17F361);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+17F361 - C6 83 99ED0000 01 - mov byte ptr [rbx+0000ED99],01
		dmc3.exe+17F368 - C6 83 A0ED0000 00 - mov byte ptr [rbx+0000EDA0],00
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

	// After Block
	{
		auto addr = (appBaseAddr + 0x17F314);
		constexpr uint32 size = 6;
		/*
		dmc3.exe+17F314 - 88 83 99ED0000 - mov [rbx+0000ED99],al
		dmc3.exe+17F31A - 8B 87 10EF0000 - mov eax,[rdi+0000EF10]
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

	// After Rest in Peace
	{
		auto addr = (appBaseAddr + 0x179DD3);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+179DD3 - C6 87 19EF0000 01 - mov byte ptr [rdi+0000EF19],01
		dmc3.exe+179DDA - 80 BF 24EF0000 01 - cmp byte ptr [rdi+0000EF24],01
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

	// // Shield
	// {
	// 	auto addr = (appBaseAddr + 0x1786A5);
	// 	constexpr uint32 size = 7;
	// 	/*
	// 	dmc3.exe+1786A5 - C6 81 C9EC0000 00 - mov byte ptr [rcx+0000ECC9],00
	// 	dmc3.exe+1786AC - 8B 86 10EF0000    - mov eax,[rsi+0000EF10]
	// 	*/

	// 	if (!run)
	// 	{
	// 		backupHelper.Save(addr, size);
	// 	}

	// 	if (enable)
	// 	{
	// 		SetMemory(addr, 0x90, size, MemoryFlags_VirtualProtectDestination);
	// 	}
	// 	else
	// 	{
	// 		backupHelper.Restore(addr);
	// 	}
	// }

	#pragma endregion

	#pragma region Disable Next Event Timer Update

	// Taunt
	{
		auto addr = (appBaseAddr + 0x179377);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+179377 - F3 0F58 05 ED411E00 - addss xmm0,dword ptr [dmc3.exe+35D56C]
		dmc3.exe+17937F - F3 0F11 43 58       - movss [rbx+58],xmm0
		*/

		constexpr byte8 sect0[] =
		{
			0x0F, 0x57, 0xC0, // xorps xmm0,xmm0
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

	// Yamato Deflect
	{
		auto addr = (appBaseAddr + 0x1795B0);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+1795B0 - F3 0F58 43 58 - addss xmm0,dword ptr [rbx+58]
		dmc3.exe+1795B5 - F3 0F11 43 58 - movss [rbx+58],xmm0
		*/

		constexpr byte8 sect0[] =
		{
			0x0F, 0x57, 0xC0, // xorps xmm0,xmm0
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

	// Yamato Deflect 2
	{
		auto addr = (appBaseAddr + 0x1795DC);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+1795DC - F3 0F58 05 883F1E00 - addss xmm0,dword ptr [dmc3.exe+35D56C]
		dmc3.exe+1795E4 - F3 0F11 43 58       - movss [rbx+58],xmm0
		*/

		constexpr byte8 sect0[] =
		{
			0x0F, 0x57, 0xC0, // xorps xmm0,xmm0
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

	// Yamato Deflect 3
	{
		auto addr = (appBaseAddr + 0x1805B3);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+1805B3 - F3 0F58 83 78010000 - addss xmm0,dword ptr [rbx+00000178]
		dmc3.exe+1805BB - F3 0F11 83 78010000 - movss [rbx+00000178],xmm0
		*/

		constexpr byte8 sect0[] =
		{
			0x0F, 0x57, 0xC0, // xorps xmm0,xmm0
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

	#pragma endregion



	run = true;
}

















































// @Todo: If boss set characterIndex to 0.



// void SetCutsceneMotionArchive
// (
// 	byte8 * mainActorBaseAddr,
// 	byte8 * archive
// )
// {
// 	LogFunction();

// 	IntroduceData(g_playerActorBaseAddrs[0], mainActorData, PlayerActorData, return);

// 	using namespace MOTION_GROUP;

// 	old_for_each(uint64, actorIndex, 2, g_playerActorBaseAddrs.count)
// 	{
// 		IntroduceData(g_playerActorBaseAddrs[actorIndex], actorData, PlayerActorData, continue);

// 		actorData.motionArchives[CUTSCENE] = mainActorData.motionArchives[CUTSCENE];
// 	}
// }







bool BelongsToPlayer(byte8 * baseAddr)
{
	if (!baseAddr)
	{
		return false;
	}

	old_for_all(uint8, playerIndex   , activeConfig.Actor.playerCount){
	old_for_all(uint8, characterIndex, CHARACTER_COUNT               ){
	old_for_all(uint8, entityIndex   , ENTITY_COUNT                  )
	{
		auto & newActorData = GetNewActorData
		(
			playerIndex,
			characterIndex,
			entityIndex
		);

		if (baseAddr == newActorData.baseAddr)
		{
			return true;
		}
	}}}

	return false;
}


void SetCollisionData(CollisionData & collisionData)
{
	if (!collisionData.baseAddr)
	{
		return;
	}

	old_for_all(uint8, playerIndex   , activeConfig.Actor.playerCount){
	old_for_all(uint8, characterIndex, CHARACTER_COUNT               ){
	old_for_all(uint8, entityIndex   , ENTITY_COUNT                  )
	{
		IntroducePlayerCharacterNewActorData(playerIndex, characterIndex, entityIndex);

		if
		(
			(!newActorData.baseAddr) ||
			(collisionData.baseAddr != newActorData.baseAddr)
		)
		{
			continue;
		}

		collisionData.group = playerData.collisionGroup;

		return;
	}}}
}



/*
dmc3.exe+1E893E - 48 8D BB 00630000 - lea rdi,[rbx+00006300]

dmc3.exe+1E89BA - 48 8D BB 00630000 - lea rdi,[rbx+00006300]
dmc3.exe+1E89C1 - 48 8B D7          - mov rdx,rdi
dmc3.exe+1E89C4 - 48 8B CD          - mov rcx,rbp
dmc3.exe+1E89C7 - E8 B423FDFF       - call dmc3.exe+1BAD80

dmc3.exe+1BAEBE - 8B 42 30          - mov eax,[rdx+30]
dmc3.exe+1BAEC1 - 89 06             - mov [rsi],eax
dmc3.exe+1BAEC3 - 8B 42 34          - mov eax,[rdx+34]
dmc3.exe+1BAEC6 - 89 46 04          - mov [rsi+04],eax
dmc3.exe+1BAEC9 - 8B 42 38          - mov eax,[rdx+38]
dmc3.exe+1BAECC - 89 46 08          - mov [rsi+08],eax
dmc3.exe+1BAECF - C7 46 0C 0000803F - mov [rsi+0C],3F800000

dmc3.exe+1BAD80

rcx 41C0 LockOnData
rdx 6300 targetPosition

dmc3.exe+1BAD9D - 48 8B F2 - mov rsi,rdx
dmc3.exe+1BADA0 - 48 8B D9 - mov rbx,rcx
*/














// @Todo: Update.


// @Research: Maybe prefer ModelData position.

bool SetLockOnTargetPosition(byte8 * dest)
{
	if
	(
		!dest ||
		!activeConfig.enablePVPFixes ||
		(activeConfig.Actor.playerCount < 2)
	)
	{
		return false;
	}








	auto baseAddr = (dest - offsetof(PlayerActorData, lockOnData.targetPosition));

	old_for_all(uint8, playerIndex   , activeConfig.Actor.playerCount){
	old_for_all(uint8, characterIndex, CHARACTER_COUNT               ){
	old_for_all(uint8, entityIndex   , ENTITY_COUNT                  )
	{
		auto & characterData = GetCharacterData(playerIndex, characterIndex, entityIndex);
		auto & newActorData  = GetNewActorData (playerIndex, characterIndex, entityIndex);



		if
		(
			(!newActorData.baseAddr) ||
			(baseAddr != newActorData.baseAddr) ||
			(characterData.character >= CHARACTER::MAX)
		)
		{
			continue;
		}

		IntroduceData(newActorData.baseAddr, actorData, PlayerActorData, continue);

		auto & player1NewActorData = GetNewActorData(0, 0, ENTITY::MAIN);
		auto & player2NewActorData = GetNewActorData(1, 0, ENTITY::MAIN);

		IntroduceData(player1NewActorData.baseAddr, player1ActorData, PlayerActorData, continue);
		IntroduceData(player2NewActorData.baseAddr, player2ActorData, PlayerActorData, continue);

		if (playerIndex == 0)
		{
			[&]()
			{
				auto dataAddr = reinterpret_cast<byte8 *>(player2ActorData.newModelPhysicsMetadataPool[player2ActorData.activeModelIndex][3]);
				if (!dataAddr)
				{
					return;
				}

				dataAddr = *reinterpret_cast<byte8 **>(dataAddr + 0x110);
				if (!dataAddr)
				{
					return;
				}

				auto & data = *reinterpret_cast<vec4 *>(dataAddr + 0x30);

				actorData.lockOnData.targetPosition = data;
			}();
		}
		else
		{
			[&]()
			{
				auto dataAddr = reinterpret_cast<byte8 *>(player1ActorData.newModelPhysicsMetadataPool[player1ActorData.activeModelIndex][3]);
				if (!dataAddr)
				{
					return;
				}

				dataAddr = *reinterpret_cast<byte8 **>(dataAddr + 0x110);
				if (!dataAddr)
				{
					return;
				}

				auto & data = *reinterpret_cast<vec4 *>(dataAddr + 0x30);

				actorData.lockOnData.targetPosition = data;
			}();
		}

		return true;
	}}}



	return false;
}

bool SetLockOnTargetPositionGUI(byte8 * dest)
{
	if
	(
		!dest ||
		!activeConfig.enablePVPFixes ||
		(activeConfig.Actor.playerCount < 2)
	)
	{
		return false;
	}

	auto & position = *reinterpret_cast<vec4 *>(dest);

	auto & player2NewActorData = GetNewActorData(1, 0, ENTITY::MAIN);

	IntroduceData(player2NewActorData.baseAddr, player2ActorData, PlayerActorData, return false);







	auto dataAddr = reinterpret_cast<byte8 *>(player2ActorData.newModelPhysicsMetadataPool[player2ActorData.activeModelIndex][3]);
	if (!dataAddr)
	{
		return false;
	}

	dataAddr = *reinterpret_cast<byte8 **>(dataAddr + 0x110);
	if (!dataAddr)
	{
		return false;
	}

	auto & data = *reinterpret_cast<vec4 *>(dataAddr + 0x30);





	position = data;


	return true;





}





// Hack to avoid xmm registers.


uint32 GetHitPoints(uint32 value)
{


	// if (!activeConfig.enablePVPFixes)
	// {
	// 	return value;
	// }


	if
	(
		!activeConfig.enablePVPFixes ||
		(activeConfig.Actor.playerCount < 2)
	)
	{
		return value;
	}


	auto & player2NewActorData = GetNewActorData(1, 0, ENTITY::MAIN);

	IntroduceData(player2NewActorData.baseAddr, player2ActorData, PlayerActorData, return value);

	return *reinterpret_cast<uint32 *>(&player2ActorData.hitPoints);






	//return hitPoints;
}

uint32 GetMaxHitPoints(uint32 value)
{

	if
	(
		!activeConfig.enablePVPFixes ||
		(activeConfig.Actor.playerCount < 2)
	)
	{
		return value;
	}


	auto & player2NewActorData = GetNewActorData(1, 0, ENTITY::MAIN);

	IntroduceData(player2NewActorData.baseAddr, player2ActorData, PlayerActorData, return value);

	return *reinterpret_cast<uint32 *>(&player2ActorData.maxHitPoints);


}


/*
257E3800
2573800



*/





uint32 PlayMotionRebellionDrive
(
	PlayerActorData & actorData,
	uint32 group,
	uint32 index
)
{
	if (actorData.newQuickDrive)
	{
		actorData.newQuickDrive = false;

		index = 30;
	}

	return index;
}







#pragma endregion




#pragma region Mobility





bool MobilityFunction
(
	PlayerActorData & actorData,
	uint8 & var,
	uint8(&array)[2]
)
{
	uint8 index = (actorData.devil) ? 1 : 0;

	if (var >= array[index])
	{
		return false;
	}

	var++;

	return true;
}

bool AirHike(PlayerActorData & actorData)
{
	if (actorData.character != CHARACTER::DANTE)
	{
		return false;
	}

	return MobilityFunction
	(
		actorData,
		actorData.newAirHikeCount,
		activeConfig.airHikeCount
	);
}

bool KickJump(PlayerActorData & actorData)
{
	return MobilityFunction
	(
		actorData,
		actorData.newKickJumpCount,
		activeConfig.kickJumpCount
	);
}

bool WallHike(PlayerActorData & actorData)
{
	return MobilityFunction
	(
		actorData,
		actorData.newWallHikeCount,
		activeConfig.wallHikeCount
	);
}

template <uint32 event>
uint32 MobilityFunction
(
	PlayerActorData & actorData,
	uint8 action,
	uint8 & var,
	uint8(&array)[2]
)
{
	uint8 index = (actorData.devil) ? 1 : 0;

	// Required, because there is no reset when hitting the floor.
	if constexpr (event != ACTOR_EVENT::TRICKSTER_DASH)
	{
		if (actorData.state & STATE::ON_FLOOR)
		{
			var = 0;
		}
	}

	if (var >= array[index])
	{
		return 0;
	}

	var++;

	actorData.lastAction = actorData.action;
	actorData.action = action;

	return event;
}

auto Dash
(
	PlayerActorData & actorData,
	uint8 action
)
{
	return MobilityFunction<ACTOR_EVENT::TRICKSTER_DASH>
	(
		actorData,
		action,
		actorData.newDashCount,
		activeConfig.dashCount
	);
}

auto SkyStar
(
	PlayerActorData & actorData,
	uint8 action
)
{
	return MobilityFunction<ACTOR_EVENT::TRICKSTER_SKY_STAR>
	(
		actorData,
		action,
		actorData.newSkyStarCount,
		activeConfig.skyStarCount
	);
}

auto AirTrickDante
(
	PlayerActorData & actorData,
	uint8 action
)
{
	actorData.var_3E10[26] = (actorData.state & STATE::ON_FLOOR) ? 1 : 0;

	return MobilityFunction<ACTOR_EVENT::TRICKSTER_AIR_TRICK>
	(
		actorData,
		action,
		actorData.newAirTrickCount,
		activeConfig.airTrickCountDante
	);
}

auto AirTrickVergil
(
	PlayerActorData & actorData,
	uint8 action
)
{
	return MobilityFunction<ACTOR_EVENT::DARK_SLAYER_AIR_TRICK>
	(
		actorData,
		action,
		actorData.newAirTrickCount,
		activeConfig.airTrickCountVergil
	);
}

auto TrickUp
(
	PlayerActorData & actorData,
	uint8 action
)
{
	return MobilityFunction<ACTOR_EVENT::DARK_SLAYER_TRICK_UP>
	(
		actorData,
		action,
		actorData.newTrickUpCount,
		activeConfig.trickUpCount
	);
}

auto TrickDown
(
	PlayerActorData & actorData,
	uint8 action
)
{
	return MobilityFunction<ACTOR_EVENT::DARK_SLAYER_TRICK_DOWN>
	(
		actorData,
		action,
		actorData.newTrickDownCount,
		activeConfig.trickDownCount
	);
}



























void ResetDash(PlayerActorData & actorData)
{
	if constexpr (debug)
	{
		LogFunction(actorData.operator byte8 *());
	}

	actorData.newDashCount = 0;
}

void ResetSkyStar(PlayerActorData & actorData)
{
	DebugLogFunction(actorData.operator byte8 *());



	bool inAir     = (actorData.state     & STATE::IN_AIR);
	bool lastInAir = (actorData.lastState & STATE::IN_AIR);

	DebugLog("action     %u", actorData.action    );
	DebugLog("lastAction %u", actorData.lastAction);
	DebugLog("inAir      %u", inAir               );
	DebugLog("lastInAir  %u", lastInAir           );



	if
	(
		// Dante Air Stinger
		(
			(actorData.character == CHARACTER::DANTE) &&
			(actorData.action == 0) &&
			(actorData.lastAction == ACTION_DANTE::REBELLION_STINGER_LEVEL_2) &&
			!inAir &&
			lastInAir
		) ||
		// Vergil Air Rising Sun
		(
			(actorData.character == CHARACTER::VERGIL) &&
			(actorData.action == ACTION_VERGIL::BEOWULF_RISING_SUN) &&
			inAir &&
			lastInAir
		) ||
		// Vergil Air Stinger
		(
			(actorData.character == CHARACTER::VERGIL) &&
			(actorData.action == 0) &&
			(actorData.lastAction == ACTION_VERGIL::YAMATO_FORCE_EDGE_STINGER_LEVEL_2) &&
			!inAir &&
			lastInAir
		)
	)
	{
		return;
	}



	actorData.newAirHikeCount    = 0;
	actorData.newKickJumpCount   = 0;
	actorData.newWallHikeCount   = 0;
	actorData.newDashCount       = 0;
	actorData.newSkyStarCount    = 0;
	actorData.newAirTrickCount   = 0;
	actorData.newTrickUpCount    = 0;
	actorData.newTrickDownCount  = 0;
	actorData.newAirStingerCount = 0;

	if
	(
		(actorData.character == CHARACTER::VERGIL) &&
		(actorData.action == ACTION_VERGIL::BEOWULF_RISING_SUN) &&
		inAir &&
		!lastInAir
	)
	{
		actorData.newAirRisingSunCount = 1;
	}
	else
	{
		actorData.newAirRisingSunCount = 0;
	}



	if (actorData.state & STATE::ON_FLOOR)
	{
		switch (actorData.character)
		{
			case CHARACTER::DANTE:
			{
				switch (actorData.eventData[0].event)
				{
					case ACTOR_EVENT::TRICKSTER_AIR_TRICK:
					{
						actorData.newAirTrickCount = 1;

						break;
					}
				}

				break;
			}
			case CHARACTER::VERGIL:
			{
				switch (actorData.eventData[0].event)
				{
					case ACTOR_EVENT::DARK_SLAYER_AIR_TRICK:
					{
						actorData.newAirTrickCount = 1;

						break;
					}
					case ACTOR_EVENT::DARK_SLAYER_TRICK_UP:
					{
						actorData.newTrickUpCount = 1;

						break;
					}
					case ACTOR_EVENT::DARK_SLAYER_TRICK_DOWN:
					{
						actorData.newTrickDownCount = 1;

						break;
					}
				}

				break;
			}
		}
	}
}

void ToggleMobility(bool enable)
{
	LogFunction(enable);

	static bool run = false;

	// Air Hike
	{
		WriteAddress((appBaseAddr + 0x1E9AB0), (enable) ? (appBaseAddr + 0x1E9AB6) : (appBaseAddr + 0x1E9B3A), 6);
		/*
		dmc3.exe+1E9AB0 - 0F8E 84000000  - jng dmc3.exe+1E9B3A
		dmc3.exe+1E9AB6 - 48 89 7C 24 30 - mov [rsp+30],rdi
		*/
	}
	{
		auto addr     = (appBaseAddr + 0x1E9B4E);
		auto jumpAddr = (appBaseAddr + 0x1E9B53);
		/*
		dmc3.exe+1E9B4E - BA 02000000 - mov edx,00000002
		dmc3.exe+1E9B53 - 48 8B CB    - mov rcx,rbx
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};
		constexpr byte8 sect2[] =
		{
			0x84, 0xC0,                         // test al,al
			0x0F, 0x84, 0x00, 0x00, 0x00, 0x00, // je dmc3.exe+1E9B3A
		};
		constexpr uint32 size0 = 5;
		constexpr uint32 size1 = sizeof(sect1);
		constexpr uint32 size2 = sizeof(sect2);

		if (!run)
		{
			func = old_CreateFunction(AirHike, jumpAddr, true, false, size0, size1, size2);
			CopyMemory(func.sect0, addr, size0, MemoryFlags_VirtualProtectSource);
			CopyMemory(func.sect1, sect1, size1);
			CopyMemory(func.sect2, sect2, size2);
			WriteAddress((func.sect2 + 2), (appBaseAddr + 0x1E9B3A), 6);
			backupHelper.Save(addr, size0);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size0 - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Kick Jump
	{
		WriteAddress((appBaseAddr + 0x1EA231), (enable) ? (appBaseAddr + 0x1EA233) : (appBaseAddr + 0x1EA222), 2);
		/*
		dmc3.exe+1EA231 - 7E EF          - jle dmc3.exe+1EA222
		dmc3.exe+1EA233 - 48 89 7C 24 48 - mov [rsp+48],rdi
		*/
	}
	{
		auto addr     = (appBaseAddr + 0x1EA384);
		auto jumpAddr = (appBaseAddr + 0x1EA389);
		/*
		dmc3.exe+1EA384 - BA 03000000       - mov edx,00000003
		dmc3.exe+1EA389 - C6 83 093F0000 04 - mov byte ptr [rbx+00003F09],04
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};
		constexpr byte8 sect2[] =
		{
			0x84, 0xC0,                         // test al,al
			0x0F, 0x84, 0x00, 0x00, 0x00, 0x00, // je dmc3.exe+1EA3DF
		};
		constexpr uint32 size0 = 5;
		constexpr uint32 size1 = sizeof(sect1);
		constexpr uint32 size2 = sizeof(sect2);

		if (!run)
		{
			func = old_CreateFunction(KickJump, jumpAddr, true, false, size0, size1, size2);
			CopyMemory(func.sect0, addr, size0, MemoryFlags_VirtualProtectSource);
			CopyMemory(func.sect1, sect1, size1);
			CopyMemory(func.sect2, sect2, size2);
			WriteAddress((func.sect2 + 2), (appBaseAddr + 0x1EA3DF), 6);
			backupHelper.Save(addr, size0);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size0 - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Wall Hike
	{
		WriteAddress((appBaseAddr + 0x1E6084), (enable) ? (appBaseAddr + 0x1E608A) : (appBaseAddr + 0x1E62B5), 6);
		/*
		dmc3.exe+1E6084 - 0F8E 2B020000     - jng dmc3.exe+1E62B5
		dmc3.exe+1E608A - 48 8B 83 E83D0000 - mov rax,[rbx+00003DE8]
		*/
	}
	{
		auto addr     = (appBaseAddr + 0x1E6549);
		auto jumpAddr = (appBaseAddr + 0x1E654E);
		/*
		dmc3.exe+1E6549 - E8 F2A1FFFF - call dmc3.exe+1E0740
		dmc3.exe+1E654E - B0 01       - mov al,01
		*/

		static Function func = {};

		constexpr byte8 sect2[] =
		{
			0x84, 0xC0,                         // test al,al
			0x0F, 0x84, 0x00, 0x00, 0x00, 0x00, // je dmc3.exe+1E64A9
			0xE8, 0x00, 0x00, 0x00, 0x00,       // call dmc3.exe+1E0740
		};
		constexpr uint32 size0 = 5;
		constexpr uint32 size2 = sizeof(sect2);

		if (!run)
		{
			func = old_CreateFunction(WallHike, jumpAddr, true, false, 0, 0, size2);
			CopyMemory(func.sect2, sect2, size2);
			WriteAddress((func.sect2 + 2), (appBaseAddr + 0x1E64A9), 6);
			WriteCall((func.sect2 + 8), (appBaseAddr + 0x1E0740));
			backupHelper.Save(addr, size0);
		}

		if (enable)
		{
			WriteJump(addr, func.addr);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	auto CreateMobilityFunction = [](void * funcAddr)
	{
		auto jumpAddr = (appBaseAddr + 0x1E666D);

		constexpr byte8 sect1[] =
		{
			0x48, 0x8B, 0xCB, // mov rcx,rbx
			0x8A, 0x57, 0x08, // mov dl,[rdi+08]
		};
		constexpr byte8 sect2[] =
		{
			0x85, 0xC0,                         // test eax,eax
			0x0F, 0x84, 0x00, 0x00, 0x00, 0x00, // je dmc3.exe+1E64A9
			0x8B, 0xD0,                         // mov edx,eax
		};
		constexpr uint32 size1 = sizeof(sect1);
		constexpr uint32 size2 = sizeof(sect2);
		auto func = old_CreateFunction(funcAddr, jumpAddr, true, false, 0, size1, size2);
		CopyMemory(func.sect1, sect1, size1);
		CopyMemory(func.sect2, sect2, size2);
		WriteAddress((func.sect2 + 2), (appBaseAddr + 0x1E64A9), 6);

		return func;
	};

	// Dash
	{
		auto addr = (appBaseAddr + 0x1E66CB);
		/*
		dmc3.exe+1E66CB - 8B 8B 58630000 - mov ecx,[rbx+00006358]
		dmc3.exe+1E66D1 - 85 C9          - test ecx,ecx
		*/

		static Function func = {};

		constexpr uint32 size0 = 6;

		if (!run)
		{
			func = CreateMobilityFunction(Dash);
			backupHelper.Save(addr, size0);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size0 - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Sky Star
	{
		auto addr = (appBaseAddr + 0x1E6689);
		/*
		dmc3.exe+1E6689 - 83 BB 58630000 01 - cmp dword ptr [rbx+00006358],01
		dmc3.exe+1E6690 - 0F8C 13FEFFFF     - jl dmc3.exe+1E64A9
		*/

		static Function func = {};

		constexpr uint32 size0 = 7;

		if (!run)
		{
			func = CreateMobilityFunction(SkyStar);
			backupHelper.Save(addr, size0);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size0 - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Air Trick Dante
	{
		auto addr = (appBaseAddr + 0x1E6612);
		/*
		dmc3.exe+1E6612 - 83 BB 58630000 02 - cmp dword ptr [rbx+00006358],02
		dmc3.exe+1E6619 - 0F85 8AFEFFFF     - jne dmc3.exe+1E64A9
		*/

		static Function func = {};

		constexpr uint32 size0 = 7;

		if (!run)
		{
			func = CreateMobilityFunction(AirTrickDante);
			backupHelper.Save(addr, size0);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size0 - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Air Trick Vergil
	{
		auto addr = (appBaseAddr + 0x1E6842);
		/*
		dmc3.exe+1E6842 - 8B 83 643E0000 - mov eax,[rbx+00003E64]
		dmc3.exe+1E6848 - A8 01          - test al,01
		*/

		static Function func = {};

		constexpr uint32 size0 = 6;

		if (!run)
		{
			func = CreateMobilityFunction(AirTrickVergil);
			backupHelper.Save(addr, size0);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size0 - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Trick Up
	{
		auto addr = (appBaseAddr + 0x1E67D5);
		/*
		dmc3.exe+1E67D5 - 83 BB 58630000 01 - cmp dword ptr [rbx+00006358],01
		dmc3.exe+1E67DC - 0F8C C7FCFFFF     - jl dmc3.exe+1E64A9
		*/

		static Function func = {};

		constexpr uint32 size0 = 7;

		if (!run)
		{
			func = CreateMobilityFunction(TrickUp);
			backupHelper.Save(addr, size0);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size0 - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Trick Down
	{
		auto addr = (appBaseAddr + 0x1E6768);
		/*
		dmc3.exe+1E6768 - 83 BB 58630000 02 - cmp dword ptr [rbx+00006358],02
		dmc3.exe+1E676F - 0F85 34FDFFFF     - jne dmc3.exe+1E64A9
		*/

		static Function func = {};

		constexpr uint32 size0 = 7;

		if (!run)
		{
			func = CreateMobilityFunction(TrickDown);
			backupHelper.Save(addr, size0);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size0 - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Reset Dash
	{
		auto addr     = (appBaseAddr + 0x1E0AFE);
		auto jumpAddr = (appBaseAddr + 0x1E0B05);
		/*
		dmc3.exe+1E0AFE - 40 88 BB 5C630000 - mov [rbx+0000635C],dil
		dmc3.exe+1E0B05 - 8B 83 003E0000    - mov eax,[rbx+00003E00]
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};
		constexpr uint32 size0 = 7;
		constexpr uint32 size1 = sizeof(sect1);

		if (!run)
		{
			func = old_CreateFunction(ResetDash, jumpAddr, true, true, size0, size1);
			CopyMemory(func.sect0, addr, size0, MemoryFlags_VirtualProtectSource);
			CopyMemory(func.sect1, sect1, size1);
			backupHelper.Save(addr, size0);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size0 - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x1F8059);
		auto jumpAddr = (appBaseAddr + 0x1F8060);
		/*
		dmc3.exe+1F8059 - 40 88 BB 5C630000 - mov [rbx+0000635C],dil
		dmc3.exe+1F8060 - C6 83 153F0000 04 - mov byte ptr [rbx+00003F15],04
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};
		constexpr uint32 size0 = 7;
		constexpr uint32 size1 = sizeof(sect1);

		if (!run)
		{
			func = old_CreateFunction(ResetDash, jumpAddr, true, true, size0, size1);
			CopyMemory(func.sect0, addr, size0, MemoryFlags_VirtualProtectSource);
			CopyMemory(func.sect1, sect1, size1);
			backupHelper.Save(addr, size0);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size0 - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x1F8383);
		auto jumpAddr = (appBaseAddr + 0x1F838A);
		/*
		dmc3.exe+1F8383 - 40 88 BB 5C630000 - mov [rbx+0000635C],dil
		dmc3.exe+1F838A - 48 89 BB C43E0000 - mov [rbx+00003EC4],rdi
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};
		constexpr uint32 size0 = 7;
		constexpr uint32 size1 = sizeof(sect1);

		if (!run)
		{
			func = old_CreateFunction(ResetDash, jumpAddr, true, true, size0, size1);
			CopyMemory(func.sect0, addr, size0, MemoryFlags_VirtualProtectSource);
			CopyMemory(func.sect1, sect1, size1);
			backupHelper.Save(addr, size0);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size0 - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Reset Sky Star
	{
		auto addr     = (appBaseAddr + 0x1DFEAE);
		auto jumpAddr = (appBaseAddr + 0x1DFEB4);
		/*
		dmc3.exe+1DFEAE - 88 8B 5D630000 - mov [rbx+0000635D],cl
		dmc3.exe+1DFEB4 - 89 AB 74630000 - mov [rbx+00006374],ebp
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};
		constexpr uint32 size0 = 6;
		constexpr uint32 size1 = sizeof(sect1);

		if (!run)
		{
			func = old_CreateFunction(ResetSkyStar, jumpAddr, true, true, size0, size1);
			CopyMemory(func.sect0, addr, size0, MemoryFlags_VirtualProtectSource);
			CopyMemory(func.sect1, sect1, size1);
			backupHelper.Save(addr, size0);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size0 - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x1DFFB6);
		auto jumpAddr = (appBaseAddr + 0x1DFFBC);
		/*
		dmc3.exe+1DFFB6 - 88 8B 5D630000    - mov [rbx+0000635D],cl
		dmc3.exe+1DFFBC - 40 88 AB AE3F0000 - mov [rbx+00003FAE],bpl
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};
		constexpr uint32 size0 = 6;
		constexpr uint32 size1 = sizeof(sect1);

		if (!run)
		{
			func = old_CreateFunction(ResetSkyStar, jumpAddr, true, true, size0, size1);
			CopyMemory(func.sect0, addr, size0, MemoryFlags_VirtualProtectSource);
			CopyMemory(func.sect1, sect1, size1);
			backupHelper.Save(addr, size0);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size0 - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x1E07A2);
		auto jumpAddr = (appBaseAddr + 0x1E07A9);
		/*
		dmc3.exe+1E07A2 - 41 88 89 5D630000 - mov [r9+0000635D],cl
		dmc3.exe+1E07A9 - EB 06             - jmp dmc3.exe+1E07B1
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_r9,
		};
		constexpr uint32 size0 = 7;
		constexpr uint32 size1 = sizeof(sect1);

		if (!run)
		{
			func = old_CreateFunction(ResetSkyStar, jumpAddr, true, true, size0, size1);
			CopyMemory(func.sect0, addr, size0, MemoryFlags_VirtualProtectSource);
			CopyMemory(func.sect1, sect1, size1);
			backupHelper.Save(addr, size0);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size0 - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x1E0D81);
		auto jumpAddr = (appBaseAddr + 0x1E0D87);
		/*
		dmc3.exe+1E0D81 - 88 8B 5D630000 - mov [rbx+0000635D],cl
		dmc3.exe+1E0D87 - 39 7B 78       - cmp [rbx+78],edi
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};
		constexpr uint32 size0 = 6;
		constexpr uint32 size1 = sizeof(sect1);

		if (!run)
		{
			func = old_CreateFunction(ResetSkyStar, jumpAddr, true, true, size0, size1);
			CopyMemory(func.sect0, addr, size0, MemoryFlags_VirtualProtectSource);
			CopyMemory(func.sect1, sect1, size1);
			backupHelper.Save(addr, size0);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size0 - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x1E0F64);
		auto jumpAddr = (appBaseAddr + 0x1E0F6B);
		/*
		dmc3.exe+1E0F64 - 41 88 88 5D630000 - mov [r8+0000635D],cl
		dmc3.exe+1E0F6B - EB 5E             - jmp dmc3.exe+1E0FCB
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_r8,
		};
		constexpr uint32 size0 = 7;
		constexpr uint32 size1 = sizeof(sect1);

		if (!run)
		{
			func = old_CreateFunction(ResetSkyStar, jumpAddr, true, true, size0, size1);
			CopyMemory(func.sect0, addr, size0, MemoryFlags_VirtualProtectSource);
			CopyMemory(func.sect1, sect1, size1);
			backupHelper.Save(addr, size0);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size0 - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x1E0FBD);
		auto jumpAddr = (appBaseAddr + 0x1E0FC4);
		/*
		dmc3.exe+1E0FBD - 41 88 88 5D630000 - mov [r8+0000635D],cl
		dmc3.exe+1E0FC4 - 41 FE 88 133F0000 - dec [r8+00003F13]
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_r8,
		};
		constexpr uint32 size0 = 7;
		constexpr uint32 size1 = sizeof(sect1);

		if (!run)
		{
			func = old_CreateFunction(ResetSkyStar, jumpAddr, true, true, size0, size1);
			CopyMemory(func.sect0, addr, size0, MemoryFlags_VirtualProtectSource);
			CopyMemory(func.sect1, sect1, size1);
			backupHelper.Save(addr, size0);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size0 - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x1E16D2);
		auto jumpAddr = (appBaseAddr + 0x1E16D8);
		/*
		dmc3.exe+1E16D2 - 88 8B 5D630000 - mov [rbx+0000635D],cl
		dmc3.exe+1E16D8 - 39 7B 78       - cmp [rbx+78],edi
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};
		constexpr uint32 size0 = 6;
		constexpr uint32 size1 = sizeof(sect1);

		if (!run)
		{
			func = old_CreateFunction(ResetSkyStar, jumpAddr, true, true, size0, size1);
			CopyMemory(func.sect0, addr, size0, MemoryFlags_VirtualProtectSource);
			CopyMemory(func.sect1, sect1, size1);
			backupHelper.Save(addr, size0);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size0 - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	run = true;
}







void PlayQuicksilverMotion
(
	byte8 * actorBaseAddr,
	uint32 archiveIndex,
	uint32 fileIndex
)
{
	if (!actorBaseAddr)
	{
		return;
	}
	auto & actorData = *reinterpret_cast<PlayerActorData *>(actorBaseAddr);

	auto PlayMotion = [&]()
	{
		func_1EFB90
		(
			actorBaseAddr,
			archiveIndex,
			fileIndex,
			-1.0f,
			-1,
			2,
			5
		);
	};

	if (actorData.character == CHARACTER::VERGIL)
	{
		auto & motionArchive = actorData.motionArchives[3];
		auto lastMotionArchive = motionArchive;

		motionArchive = File_staticFiles[pl000_00_25];

		PlayMotion();

		motionArchive = lastMotionArchive;
	}
	else
	{
		PlayMotion();
	}
}








































#pragma endregion

#pragma region Color

void SetAirHikeColor
(
	PlayerActorDataDante & actorData,
	byte8 * dest
)
{
	uint8 meleeWeaponIndex = static_cast<uint8>(actorData.meleeWeaponIndex);
	if (meleeWeaponIndex >= MELEE_WEAPON_COUNT_DANTE)
	{
		meleeWeaponIndex = 0;
	}

	CopyMemory(dest, activeConfig.Color.airHike[meleeWeaponIndex], 4);
}

void SetDevilAuraColor
(
	PlayerActorData & actorData,
	byte8 * dest
)
{
	uint8 character = static_cast<uint8>(actorData.character);

	switch (character)
	{
		case CHARACTER::DANTE:
		{
			auto & actorData2 = *reinterpret_cast<PlayerActorDataDante *>(&actorData);

			if (actorData2.sparda)
			{
				CopyMemory(dest, activeConfig.Color.Aura.sparda, 4);
			}
			else
			{
				uint8 meleeWeaponIndex = static_cast<uint8>(actorData2.meleeWeaponIndex);
				if (meleeWeaponIndex >= MELEE_WEAPON_COUNT_DANTE)
				{
					meleeWeaponIndex = 0;
				}

				CopyMemory(dest, activeConfig.Color.Aura.dante[meleeWeaponIndex], 4);
			}
			break;
		}
		case CHARACTER::VERGIL:
		{
			auto & actorData2 = *reinterpret_cast<PlayerActorDataVergil *>(&actorData);

			if (actorData2.neroAngelo)
			{
				CopyMemory(dest, activeConfig.Color.Aura.neroAngelo, 4);
			}
			else
			{
				uint8 activeMeleeWeaponIndex = static_cast<uint8>(actorData2.activeMeleeWeaponIndex);
				if (activeMeleeWeaponIndex >= MELEE_WEAPON_COUNT_VERGIL)
				{
					activeMeleeWeaponIndex = 0;
				}

				CopyMemory(dest, activeConfig.Color.Aura.vergil[activeMeleeWeaponIndex], 4);
			}
			break;
		}
	}
}

void ToggleColor(bool enable)
{
	LogFunction(enable);

	static bool run = false;

	// Air Hike
	{
		auto addr = (appBaseAddr + 0x1F66DD);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+1F66DD - E8 1E66E9FF   - call dmc3.exe+8CD00
		dmc3.exe+1F66E2 - 0FB6 44 24 44 - movzx eax,byte ptr [rsp+44]
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(SetAirHikeColor, 0, true, true, 0, sizeof(sect1));
			CopyMemory(func.sect1, sect1, sizeof(sect1));
		}

		if (enable)
		{
			WriteCall(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Trickster Sky Star
	{
		auto addr     = (appBaseAddr + 0x8E330);
		auto jumpAddr = (appBaseAddr + 0x8E340);
		constexpr uint32 size = 9;
		/*
		dmc3.exe+8E330 - 66 C7 80 E0000000 FF00  - mov word ptr [rax+000000E0],00FF
		dmc3.exe+8E340 - C7 80 DC000000 02000000 - mov [rax+000000DC],00000002
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx
			0x8B, 0x09,                                                 // mov ecx,[rcx]
			0x89, 0x88, 0xE0, 0x00, 0x00, 0x00,                         // mov [rax+000000E0],ecx
			pop_rcx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 3) = activeConfig.Color.Trickster.skyStar;
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

	// Royalguard Ultimate Start
	{
		auto addr     = (appBaseAddr + 0x8E83C);
		auto jumpAddr = (appBaseAddr + 0x8E84C);
		constexpr uint32 size = 9;
		/*
		dmc3.exe+8E83C - 66 C7 80 E0000000 8F70  - mov word ptr [rax+000000E0],708F
		dmc3.exe+8E84C - C7 80 DC000000 02000000 - mov [rax+000000DC],00000002
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx
			0x8B, 0x09,                                                 // mov ecx,[rcx]
			0x89, 0x88, 0xE0, 0x00, 0x00, 0x00,                         // mov [rax+000000E0],ecx
			pop_rcx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 3) = activeConfig.Color.Royalguard.ultimate;
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

	// Royalguard Ultimate End
	{
		auto addr     = (appBaseAddr + 0x91144);
		auto jumpAddr = (appBaseAddr + 0x91154);
		constexpr uint32 size = 9;
		/*
		dmc3.exe+91144 - 66 C7 80 E0000000 8F70  - mov word ptr [rax+000000E0],708F
		dmc3.exe+91154 - C7 80 DC000000 02000000 - mov [rax+000000DC],00000002
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rcx
			0x8B, 0x09,                                                 // mov ecx,[rcx]
			0x89, 0x88, 0xE0, 0x00, 0x00, 0x00,                         // mov [rax+000000E0],ecx
			pop_rcx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 3) = activeConfig.Color.Royalguard.ultimate;
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

	// Doppelganger Clone
	{
		auto addr     = (appBaseAddr + 0x1FCD73);
		auto jumpAddr = (appBaseAddr + 0x1FCD7D);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+1FCD73 - C7 87 283A0000 10101030 - mov [rdi+00003A28],30101010
		dmc3.exe+1FCD7D - 89 87 243A0000          - mov [rdi+00003A24],eax
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rax,
			0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rax
			0x8B, 0x00,                                                 // mov eax,[rax]
			0x89, 0x87, 0x28, 0x3A, 0x00, 0x00,                         // mov [rdi+00003A28],eax
			pop_rax,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint8 **>(func.sect0 + 3) = activeConfig.Color.Doppelganger.clone;
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

	// Devil Aura Start
	{
		auto addr     = (appBaseAddr + 0x8E452);
		auto jumpAddr = (appBaseAddr + 0x8E457);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+8E452 - BA 01000000 - mov edx,00000001
		dmc3.exe+8E457 - E8 34C61600 - call dmc3.exe+1FAA90
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0x8D, 0x45, 0xA7, // lea rax,[rbp-59]
		};
		constexpr byte8 sect1[] =
		{
			mov_rdx_rax,
			mov_rcx_rbx,
			call,
			mov_rcx_rax,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(SetDevilAuraColor, jumpAddr, true, true, sizeof(sect0), sizeof(sect1), size);
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			CopyMemory(func.sect1, sect1, sizeof(sect1));
			CopyMemory(func.sect2, addr, size, MemoryFlags_VirtualProtectSource);
			WriteCall((func.sect1 + 6), GetPlayerActorBaseAddressByEffectData);
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

	// Devil Aura Loop
	{
		auto addr     = (appBaseAddr + 0x90C9D);
		auto jumpAddr = (appBaseAddr + 0x90CA4);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+90C9D - 0FB6 8F D4000000 - movzx ecx,byte ptr [rdi+000000D4]
		dmc3.exe+90CA4 - 85 C9            - test ecx,ecx
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0x8D, 0x44, 0x24, 0x30, // lea rax,[rsp+30]
		};
		constexpr byte8 sect1[] =
		{
			mov_rdx_rax,
			mov_rcx_rdi,
			call,
			mov_rcx_rax,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(SetDevilAuraColor, jumpAddr, true, true, sizeof(sect0), sizeof(sect1), size);
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			CopyMemory(func.sect1, sect1, sizeof(sect1));
			CopyMemory(func.sect2, addr, size, MemoryFlags_VirtualProtectSource);
			WriteCall((func.sect1 + 6), GetPlayerActorBaseAddressByEffectData);
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

	// Devil Aura Vergil Fix
	{
		auto addr = (appBaseAddr + 0x90C32);
		constexpr uint32 size = 4;
		/*
		dmc3.exe+90C32 - 44 0FB6 EB        - movzx r13d,bl
		dmc3.exe+90C36 - C6 05 6322C000 0E - mov byte ptr [dmc3.exe+C92EA0],0E
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

#pragma endregion

#pragma region Speed

//byte8 * UpdateActorSpeedAddr = 0;



// When hit by Geryon's Time Lag, Quicksilver is turned off.


// @Todo: Simplify again and if nothing matches use player1LeadActorData value.
// @Todo: Add IsEnemy lambda.


/*

if no match check type id for player and apply player 1 speed





*/







void UpdateActorSpeed(byte8 * baseAddr)
{


	if (!baseAddr)
	{
		return;
	}


	auto & player1LeadNewActorData = GetNewActorData(0, 0, ENTITY::MAIN);

	IntroduceData(player1LeadNewActorData.baseAddr, player1LeadActorData, PlayerActorData, return);

	auto & quicksilver      = player1LeadActorData.quicksilver;
	auto & quicksilverStage = player1LeadActorData.quicksilverStage;


	IntroduceMainActorData(mainActorData, return);





	// NewActorData

	old_for_all(uint8, playerIndex   , PLAYER_COUNT   ){
	old_for_all(uint8, characterIndex, CHARACTER_COUNT){
	old_for_all(uint8, entityIndex   , ENTITY_COUNT   )
	{
		IntroducePlayerCharacterNewActorData(playerIndex, characterIndex, entityIndex);













		auto actorBaseAddr = newActorData.baseAddr;

		if (baseAddr != actorBaseAddr)
		{
			// At this point we only know it's not the actor, but it could be a weapon from that actor.



			if (characterData.character >= CHARACTER::MAX)
			{
				continue;
			}



			IntroduceData(actorBaseAddr, actorData, PlayerActorData, continue);



			bool match = false;

			old_for_all(uint8, weaponIndex, countof(actorData.newWeaponDataAddr))
			{
				auto weaponDataAddr = actorData.newWeaponDataAddr[weaponIndex];
				if (!weaponDataAddr)
				{
					continue;
				}
				auto & weaponData = *weaponDataAddr;



				if (baseAddr == weaponData.baseAddr)
				{
					match = true;

					actorBaseAddr = weaponData.actorBaseAddr;

					break;
				}
			}



			if (!match)
			{
				continue;
			}
		}



		// At this point we know it's one of our actors.








		IntroduceData(actorBaseAddr, actorData, PlayerActorData, continue);



		auto value = (IsTurbo()) ? activeConfig.Speed.turbo : activeConfig.Speed.main;




		if (mainActorData.styleData.rank >= STYLE_RANK::SWEET)
		{
			value *= 1.05f;
		}











		using namespace QUICKSILVER_STAGE;

		if (quicksilver)
		{
			// Weird, but that's the default behaviour.
			if
			(
				(quicksilverStage == TO_ON) &&
				(actorData.action != 0)
			)
			{
				value = 0;
			}
			else if (quicksilverStage == ON)
			{
				value *= activeConfig.Speed.quicksilverPlayerActor;
			}

			goto Return;
		}
		else
		{
			// At this point we only know that OUR Quicksilver is off.
			// Geryon's Quicksilver could be on.

			switch (quicksilverStage)
			{
				case TO_ON:
				{
					value = 0;

					goto Return;
				}
				case ON:
				{
					value *= 0.2f;

					goto Return;
				}
			}
		}

		// At this point we know that neither our own nor another Quicksilver is on.



		if (characterData.character >= CHARACTER::MAX)
		{
			goto Return;
		}



		if (!actorData.devil)
		{
			value *= activeConfig.Speed.human;

			goto Return;
		}



		switch (actorData.character)
		{
			case CHARACTER::DANTE:
			{
				auto devilIndex = actorData.meleeWeaponIndex;
				if (devilIndex > 4)
				{
					devilIndex = 0;
				}

				if (actorData.sparda)
				{
					devilIndex = DEVIL_SPEED::DANTE_SPARDA;
				}

				value *= activeConfig.Speed.devilDante[devilIndex];

				break;
			}
			case CHARACTER::VERGIL:
			{
				auto devilIndex = actorData.queuedMeleeWeaponIndex;
				if (devilIndex > 2)
				{
					devilIndex = 0;
				}

				if (actorData.neroAngelo)
				{
					if (devilIndex > 1)
					{
						devilIndex = 0;
					}

					devilIndex += 3;
				}

				value *= activeConfig.Speed.devilVergil[devilIndex];

				break;
			}
		}




		Return:;


		actorData.speed = value;


		if (characterData.character >= CHARACTER::MAX)
		{
			return;
		}



		old_for_all(uint8, weaponIndex, countof(actorData.newWeaponDataAddr))
		{
			auto weaponDataAddr = actorData.newWeaponDataAddr[weaponIndex];
			if (!weaponDataAddr)
			{
				continue;
			}
			auto & weaponData = *weaponDataAddr;

			weaponData.speed = value;
		}





		return;
	}}}


















	// // EnemyVectorData

	// IntroduceEnemyVectorData(return);

	// old_for_all(uint32, enemyIndex, countof(enemyVectorData.metadata))
	// {
	// 	auto & metadata = enemyVectorData.metadata[enemyIndex];

	// 	if (baseAddr != metadata.baseAddr)
	// 	{
	// 		continue;
	// 	}

	// 	IntroduceData(metadata.baseAddr, actorData, EnemyActorData, continue);

	// 	auto value = (IsTurbo()) ? activeConfig.Speed.turbo : activeConfig.Speed.main;



	// 	using namespace QUICKSILVER_STAGE;

	// 	if (quicksilverStage == TO_ON)
	// 	{
	// 		value = 0;
	// 	}
	// 	else if
	// 	(
	// 		quicksilver &&
	// 		(quicksilverStage == ON)
	// 	)
	// 	{
	// 		value *= activeConfig.Speed.quicksilverEnemyActor;
	// 	}



	// 	value *= activeConfig.Speed.enemy;

	// 	actorData.speed = value;

	// 	return;
	// }
}





















void ToggleSpeed(bool enable)
{
	LogFunction(enable);

	static bool run = false;

	// Update Actor Speed
	{
		auto addr     = (appBaseAddr + 0x3261CD);
		auto jumpAddr = (appBaseAddr + 0x3261D2);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+3261CD - F3 0F11 43 14 - movss [rbx+14],xmm0
		dmc3.exe+3261D2 - 48 83 C4 20   - add rsp,20
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(UpdateActorSpeed, jumpAddr, true, true, size, sizeof(sect1));
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

	// Devil Speed Values Dante
	{
		auto items = reinterpret_cast<float *>(appBaseAddr + 0x58B0B8);
		/*
		dmc3.exe+1F8C24 - F3 41 0F10 84 8C B8B05800 - MOVSS XMM0,[R12+RCX*4+0058B0B8]
		*/

		if (enable)
		{
			old_for_all(uint8, itemIndex, countof(activeConfig.Speed.devilDante))
			{
				auto & item = items[itemIndex];

				Write<float>(&item, 1.0f);
			}
		}
		else
		{
			CopyMemory(items, defaultConfig.Speed.devilDante, sizeof(defaultConfig.Speed.devilDante), MemoryFlags_VirtualProtectDestination);
		}
	}

	// Devil Speed Values Vergil
	{
		auto items = reinterpret_cast<float *>(appBaseAddr + 0x58B0D8);
		/*
		dmc3.exe+1F8C48 - F3 41 0F10 84 8C D8B05800 - MOVSS XMM0,[R12+RCX*4+0058B0D8]
		*/

		if (enable)
		{
			old_for_all(uint8, itemIndex, countof(activeConfig.Speed.devilVergil))
			{
				auto & item = items[itemIndex];

				Write<float>(&item, 1.0f);
			}
		}
		else
		{
			CopyMemory(items, defaultConfig.Speed.devilVergil, sizeof(defaultConfig.Speed.devilVergil), MemoryFlags_VirtualProtectDestination);
		}
	}

	run = true;
}







#pragma endregion

#pragma region Sound






// @Todo: Add missing ids.
// constexpr uint32 g_bodyPartDataOffs[] =
// {


// 	offsetof(PlayerActorData, newBodyPartData[0][0]),
// 	offsetof(PlayerActorData, newBodyPartData[0][1]),

// 	offsetof(PlayerActorData, newBodyPartData[1][0]),
// 	offsetof(PlayerActorData, newBodyPartData[1][1]),

// 	offsetof(PlayerActorData, newBodyPartData[2][0]),
// 	offsetof(PlayerActorData, newBodyPartData[2][1]),

// 	offsetof(PlayerActorData, newBodyPartData[3][0]),
// 	offsetof(PlayerActorData, newBodyPartData[3][1]),

// 	offsetof(PlayerActorData, newBodyPartData[4][0]),
// 	offsetof(PlayerActorData, newBodyPartData[4][1]),

// 	offsetof(PlayerActorData, newBodyPartData[5][0]),
// 	offsetof(PlayerActorData, newBodyPartData[5][1]),

// 	offsetof(PlayerActorData, newBodyPartData[6][0]),
// 	offsetof(PlayerActorData, newBodyPartData[6][1]),



// 	// Boss Lady Base
// 	(0x5070 + (sizeof(BodyPartData) * 0)),
// 	(0x5070 + (sizeof(BodyPartData) * 1)),
// 	(0x5070 + (sizeof(BodyPartData) * 2)),


// 	// Boss Vergil Base
// 	(0xDE80 + (sizeof(BodyPartData) * 0)),
// 	(0xDE80 + (sizeof(BodyPartData) * 1)),
// 	(0xDE80 + (sizeof(BodyPartData) * 2)),
// 	(0xDE80 + (sizeof(BodyPartData) * 3)),
// };

// inline void UpdateGlobalCharacterCostume(byte8 * actorBaseAddr)
// {
// 	if (!actorBaseAddr)
// 	{
// 		return;
// 	}
// 	auto & actorData = *reinterpret_cast<PlayerActorData *>(actorBaseAddr);

// 	g_character = static_cast<uint8>(actorData.character);
// 	g_costume = actorData.costume;
// }

// template <typename T>
// void UpdateGlobalCharacterCostumeByData(byte8 * dataAddr)
// {
// 	if (!dataAddr)
// 	{
// 		return;
// 	}

// 	byte8 * actorBaseAddr = 0;

// 	if constexpr (TypeMatch<T, BodyPartData>::value)
// 	{
// 		auto & bodyPartData = *reinterpret_cast<BodyPartData *>(dataAddr);

// 		actorBaseAddr = (reinterpret_cast<byte8 *>(bodyPartData.motionArchives) - offsetof(PlayerActorData, motionArchives));
// 	}
// 	else if constexpr (TypeMatch<T, SummonedSwordsData>::value)
// 	{
// 		auto & summonedSwordsData = *reinterpret_cast<SummonedSwordsData *>(dataAddr);

// 		actorBaseAddr = summonedSwordsData.actorBaseAddr;
// 	}

// 	UpdateGlobalCharacterCostume(actorBaseAddr);
// }

// void ToggleSound(bool enable)
// {
// 	static bool run = false;

// 	// Taunt & Style
// 	{
// 		auto addr     = (appBaseAddr + 0x59DFB);
// 		auto jumpAddr = (appBaseAddr + 0x59E00);
// 		constexpr uint32 size = 5;
// 		/*
// 		dmc3.exe+59DFB - E8 20F52D00       - call dmc3.exe+339320
// 		dmc3.exe+59E00 - C6 83 08010000 01 - mov byte ptr [rbx+00000108],01
// 		*/

// 		static Function func = {};

// 		constexpr byte8 sect1[] =
// 		{
// 			mov_rcx_rbx,
// 		};

// 		if (!run)
// 		{
// 			backupHelper.Save(addr, size);
// 			func = old_CreateFunction(UpdateGlobalCharacterCostumeByData<BodyPartData>, jumpAddr, true, true, 0, sizeof(sect1), size);
// 			CopyMemory(func.sect1, sect1, sizeof(sect1));
// 			CopyMemory(func.sect2, addr, size, MemoryFlags_VirtualProtectSource);
// 			WriteCall(func.sect2, (appBaseAddr + 0x339320));
// 		}

// 		if (enable)
// 		{
// 			WriteJump(addr, func.addr, (size - 5));
// 		}
// 		else
// 		{
// 			backupHelper.Restore(addr);
// 		}
// 	}

// 	// Melee Weapon
// 	{
// 		auto addr     = (appBaseAddr + 0x59E3B);
// 		auto jumpAddr = (appBaseAddr + 0x59E40);
// 		constexpr uint32 size = 5;
// 		/*
// 		dmc3.exe+59E3B - E8 F0FA2D00       - call dmc3.exe+339930
// 		dmc3.exe+59E40 - C6 83 09010000 01 - mov byte ptr [rbx+00000109],01
// 		*/

// 		static Function func = {};

// 		constexpr byte8 sect1[] =
// 		{
// 			mov_rcx_rbx,
// 		};

// 		if (!run)
// 		{
// 			backupHelper.Save(addr, size);
// 			func = old_CreateFunction(UpdateGlobalCharacterCostumeByData<BodyPartData>, jumpAddr, true, true, 0, sizeof(sect1), size);
// 			CopyMemory(func.sect1, sect1, sizeof(sect1));
// 			CopyMemory(func.sect2, addr, size, MemoryFlags_VirtualProtectSource);
// 			WriteCall(func.sect2, (appBaseAddr + 0x339930));
// 		}

// 		if (enable)
// 		{
// 			WriteJump(addr, func.addr, (size - 5));
// 		}
// 		else
// 		{
// 			backupHelper.Restore(addr);
// 		}
// 	}

// 	// Ebony & Ivory
// 	{
// 		auto addr     = (appBaseAddr + 0x216CC3);
// 		auto jumpAddr = (appBaseAddr + 0x216CC8);
// 		constexpr uint32 size = 5;
// 		/*
// 		dmc3.exe+216CC3 - E8 682C1200 - call dmc3.exe+339930
// 		dmc3.exe+216CC8 - 83 FB 09    - cmp ebx,09
// 		*/

// 		static Function func = {};

// 		constexpr byte8 sect1[] =
// 		{
// 			mov_rcx_rdi,
// 		};

// 		if (!run)
// 		{
// 			backupHelper.Save(addr, size);
// 			func = old_CreateFunction(UpdateGlobalCharacterCostume, jumpAddr, true, true, 0, sizeof(sect1), size);
// 			CopyMemory(func.sect1, sect1, sizeof(sect1));
// 			CopyMemory(func.sect2, addr, size, MemoryFlags_VirtualProtectSource);
// 			WriteCall(func.sect2, (appBaseAddr + 0x339930));
// 		}

// 		if (enable)
// 		{
// 			WriteJump(addr, func.addr, (size - 5));
// 		}
// 		else
// 		{
// 			backupHelper.Restore(addr);
// 		}
// 	}

// 	// Shotgun
// 	{
// 		auto addr     = (appBaseAddr + 0x218212);
// 		auto jumpAddr = (appBaseAddr + 0x218217);
// 		constexpr uint32 size = 5;
// 		/*
// 		dmc3.exe+218212 - E8 19171200 - call dmc3.exe+339930
// 		dmc3.exe+218217 - 40 0FB6 C6  - movzx eax,sil
// 		*/

// 		static Function func = {};

// 		constexpr byte8 sect1[] =
// 		{
// 			mov_rcx_rbx,
// 		};

// 		if (!run)
// 		{
// 			backupHelper.Save(addr, size);
// 			func = old_CreateFunction(UpdateGlobalCharacterCostume, jumpAddr, true, true, 0, sizeof(sect1), size);
// 			CopyMemory(func.sect1, sect1, sizeof(sect1));
// 			CopyMemory(func.sect2, addr, size, MemoryFlags_VirtualProtectSource);
// 			WriteCall(func.sect2, (appBaseAddr + 0x339930));
// 		}

// 		if (enable)
// 		{
// 			WriteJump(addr, func.addr, (size - 5));
// 		}
// 		else
// 		{
// 			backupHelper.Restore(addr);
// 		}
// 	}

// 	// Artemis
// 	{
// 		auto addr     = (appBaseAddr + 0x216042);
// 		auto jumpAddr = (appBaseAddr + 0x216047);
// 		constexpr uint32 size = 5;
// 		/*
// 		dmc3.exe+216042 - E8 E9381200    - call dmc3.exe+339930
// 		dmc3.exe+216047 - FE 87 7EB80000 - inc byte ptr [rdi+0000B87E]
// 		*/

// 		static Function func = {};

// 		constexpr byte8 sect1[] =
// 		{
// 			mov_rcx_rdi,
// 		};

// 		if (!run)
// 		{
// 			backupHelper.Save(addr, size);
// 			func = old_CreateFunction(UpdateGlobalCharacterCostume, jumpAddr, true, true, 0, sizeof(sect1), size);
// 			CopyMemory(func.sect1, sect1, sizeof(sect1));
// 			CopyMemory(func.sect2, addr, size, MemoryFlags_VirtualProtectSource);
// 			WriteCall(func.sect2, (appBaseAddr + 0x339930));
// 		}

// 		if (enable)
// 		{
// 			WriteJump(addr, func.addr, (size - 5));
// 		}
// 		else
// 		{
// 			backupHelper.Restore(addr);
// 		}
// 	}

// 	// Spiral
// 	{
// 		auto addr     = (appBaseAddr + 0x20877F);
// 		auto jumpAddr = (appBaseAddr + 0x208784);
// 		constexpr uint32 size = 5;
// 		/*
// 		dmc3.exe+20877F - E8 AC111300    - call dmc3.exe+339930
// 		dmc3.exe+208784 - FE 83 153E0000 - inc byte ptr [rbx+00003E15]
// 		*/

// 		static Function func = {};

// 		constexpr byte8 sect1[] =
// 		{
// 			mov_rcx_rbx,
// 		};

// 		if (!run)
// 		{
// 			backupHelper.Save(addr, size);
// 			func = old_CreateFunction(UpdateGlobalCharacterCostume, jumpAddr, true, true, 0, sizeof(sect1), size);
// 			CopyMemory(func.sect1, sect1, sizeof(sect1));
// 			CopyMemory(func.sect2, addr, size, MemoryFlags_VirtualProtectSource);
// 			WriteCall(func.sect2, (appBaseAddr + 0x339930));
// 		}

// 		if (enable)
// 		{
// 			WriteJump(addr, func.addr, (size - 5));
// 		}
// 		else
// 		{
// 			backupHelper.Restore(addr);
// 		}
// 	}

// 	// Kalina Ann
// 	{
// 		auto addr     = (appBaseAddr + 0x206212);
// 		auto jumpAddr = (appBaseAddr + 0x206217);
// 		constexpr uint32 size = 5;
// 		/*
// 		dmc3.exe+206212 - E8 19371300    - call dmc3.exe+339930
// 		dmc3.exe+206217 - FE 83 153E0000 - inc byte ptr [rbx+00003E15]
// 		*/

// 		static Function func = {};

// 		constexpr byte8 sect1[] =
// 		{
// 			mov_rcx_rbx,
// 		};

// 		if (!run)
// 		{
// 			backupHelper.Save(addr, size);
// 			func = old_CreateFunction(UpdateGlobalCharacterCostume, jumpAddr, true, true, 0, sizeof(sect1), size);
// 			CopyMemory(func.sect1, sect1, sizeof(sect1));
// 			CopyMemory(func.sect2, addr, size, MemoryFlags_VirtualProtectSource);
// 			WriteCall(func.sect2, (appBaseAddr + 0x339930));
// 		}

// 		if (enable)
// 		{
// 			WriteJump(addr, func.addr, (size - 5));
// 		}
// 		else
// 		{
// 			backupHelper.Restore(addr);
// 		}
// 	}

// 	// Summoned Swords
// 	{
// 		auto addr     = (appBaseAddr + 0x1DBA94);
// 		auto jumpAddr = (appBaseAddr + 0x1DBA99);
// 		constexpr uint32 size = 5;
// 		/*
// 		dmc3.exe+1DBA94 - E8 97DE1500      - call dmc3.exe+339930
// 		dmc3.exe+1DBA99 - 0FB6 8B F20D0000 - movzx ecx,byte ptr [rbx+00000DF2]
// 		*/

// 		static Function func = {};

// 		constexpr byte8 sect1[] =
// 		{
// 			mov_rcx_rbx,
// 		};

// 		if (!run)
// 		{
// 			backupHelper.Save(addr, size);
// 			func = old_CreateFunction(UpdateGlobalCharacterCostumeByData<SummonedSwordsData>, jumpAddr, true, true, 0, sizeof(sect1), size);
// 			CopyMemory(func.sect1, sect1, sizeof(sect1));
// 			CopyMemory(func.sect2, addr, size, MemoryFlags_VirtualProtectSource);
// 			WriteCall(func.sect2, (appBaseAddr + 0x339930));
// 		}

// 		if (enable)
// 		{
// 			WriteJump(addr, func.addr, (size - 5));
// 		}
// 		else
// 		{
// 			backupHelper.Restore(addr);
// 		}
// 	}

// 	run = true;
// }






















































#pragma endregion

#pragma region Damage

float ApplyDamage
(
	byte8 * dest,
	float value
)
{
	if constexpr (debug)
	{
		Log
		(
			"%llX %f",
			dest,
			value
		);
	}

	bool match = false;

	// Main Actor
	[&]()
	{
		IntroduceMainActorData(actorBaseAddr, actorData, return);

		if (((dest + 8) - offsetof(PlayerActorData, hitPoints)) == actorBaseAddr)
		{
			match = true;

			value *= activeConfig.damageActorMultiplier;
		}
	}();

	// Actor
	if (!match)
	{
		old_for_all(uint32, actorIndex, g_playerActorBaseAddrs.count)
		{
			IntroducePlayerActorData(actorBaseAddr, g_playerActorBaseAddrs[actorIndex], actorData, continue);

			if (((dest + 8) - offsetof(PlayerActorData, hitPoints)) != actorBaseAddr)
			{
				continue;
			}

			match = true;

			value *= activeConfig.damageActorMultiplier;

			break;
		}
	}

	// Enemy
	if (!match)
	{
		value *= activeConfig.damageEnemyMultiplier;

		IntroduceMainActorData(actorData, return value);

		if (actorData.styleData.rank < activeConfig.damageStyleRank)
		{
			return 0;
		}
	}

	return value;
}

/*
rsp 0000006277AFFA80
rsp 0000006277AFF9F8
rsp 0000006277AFF8F8

rsp 0000006277AFF8F8
rsp 0000006277AFF9F8
rsp 0000006277AFFA80
*/










#pragma endregion





















// @Todo: Recheck and move to Toggle.
void ToggleMainActorFixes(bool enable)
{
	LogFunction(enable);


	// Disable Doppelganger rotation update during camera angle update.
	Write<byte8>((appBaseAddr + 0x55F6F), (enable) ? 0xEB : 0x75);
	/*
	dmc3.exe+55F6F - 75 10       - jne dmc3.exe+55F81
	dmc3.exe+55F71 - 48 8B 49 20 - mov rcx,[rcx+20]
	*/


	static bool run = false;

	run = true;

	{
		auto dest = (appBaseAddr + 0x1F83D7);
		if (enable)
		{
			SetMemory(dest, 0x90, 18, MemoryFlags_VirtualProtectDestination);
			constexpr byte8 buffer[] =
			{
				0x40, 0x38, 0xB7, 0x62, 0x63, 0x00, 0x00, // cmp [rdi+00006362],sil
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0x48, 0x8B, 0x0D, 0x4A, 0x8A, 0xA9, 0x00, // mov rcx,[dmc3.exe+C90E28]
				0x48, 0x8B, 0x41, 0x18,                   // mov rax,[rcx+18]
				0x40, 0x38, 0xB0, 0x62, 0x63, 0x00, 0x00, // cmp [rax+00006362],sil
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+1F83D7 - 48 8B 0D 4A8AA900 - mov rcx,[dmc3.exe+C90E28]
		dmc3.exe+1F83DE - 48 8B 41 18       - mov rax,[rcx+18]
		dmc3.exe+1F83E2 - 40 38 B0 62630000 - cmp [rax+00006362],sil
		dmc3.exe+1F83E9 - 75 0E             - jne dmc3.exe+1F83F9
		*/
	}

	// @Todo: Update comments.
	Write<uint32>((appBaseAddr + 0x1F5FC6 + 2), (enable) ? offsetof(PlayerActorData, newIsClone) : offsetof(PlayerActorData, isClone));
	/*
	dmc3.exe+1F5FC6 - 83 B9 C8CA0100 01 - cmp dword ptr [rcx+0001CAC8],01
	dmc3.exe+1F5FCD - 48 8B D9          - mov rbx,rcx
	*/
}

// @Update
void ToggleStyleFixes(bool enable)
{
	// Disable Menu Controller
	Write<bool>((appBaseAddr + 0x23B110 + 1), (enable) ? false : true); // dmc3.exe+23B110 - B0 01 - mov al,01
	Write<bool>((appBaseAddr + 0x23B15D + 1), (enable) ? false : true); // dmc3.exe+23B15D - B0 01 - mov al,01
	Write<bool>((appBaseAddr + 0x23B1A1 + 1), (enable) ? false : true); // dmc3.exe+23B1A1 - B0 01 - mov al,01
	Write<bool>((appBaseAddr + 0x23B1E5 + 1), (enable) ? false : true); // dmc3.exe+23B1E5 - B0 01 - mov al,01

	// Force Style Updates
	{
		WriteAddress((appBaseAddr + 0x1F87BB), (enable) ? (appBaseAddr + 0x1F87DC) : (appBaseAddr + 0x1F8AC6), 6); // dmc3.exe+1F87BB - 0F84 05030000 - je dmc3.exe+1F8AC6
		WriteAddress((appBaseAddr + 0x1F87C4), (enable) ? (appBaseAddr + 0x1F87DC) : (appBaseAddr + 0x1F8AAC), 6); // dmc3.exe+1F87C4 - 0F84 E2020000 - je dmc3.exe+1F8AAC
		WriteAddress((appBaseAddr + 0x1F87CD), (enable) ? (appBaseAddr + 0x1F87DC) : (appBaseAddr + 0x1F8A00), 6); // dmc3.exe+1F87CD - 0F84 2D020000 - je dmc3.exe+1F8A00
		WriteAddress((appBaseAddr + 0x1F87D6), (enable) ? (appBaseAddr + 0x1F87DC) : (appBaseAddr + 0x1F8AF8), 6); // dmc3.exe+1F87D6 - 0F85 1C030000 - jne dmc3.exe+1F8AF8
		// Doppelganger
		WriteAddress((appBaseAddr + 0x1F880B), (enable) ? (appBaseAddr + 0x1F8A00) : (appBaseAddr + 0x1F8AF8), 6); // dmc3.exe+1F880B - 0F85 E7020000 - jne dmc3.exe+1F8AF8
		WriteAddress((appBaseAddr + 0x1F8852), (enable) ? (appBaseAddr + 0x1F8A00) : (appBaseAddr + 0x1F8AF8), 6); // dmc3.exe+1F8852 - 0F85 A0020000 - jne dmc3.exe+1F8AF8
		WriteAddress((appBaseAddr + 0x1F8862), (enable) ? (appBaseAddr + 0x1F8A00) : (appBaseAddr + 0x1F8AF8), 5); // dmc3.exe+1F8862 - E9 91020000   - jmp dmc3.exe+1F8AF8
		WriteAddress((appBaseAddr + 0x1F886E), (enable) ? (appBaseAddr + 0x1F8A00) : (appBaseAddr + 0x1F8AF8), 6); // dmc3.exe+1F886E - 0F84 84020000 - je dmc3.exe+1F8AF8
		WriteAddress((appBaseAddr + 0x1F89E1), (enable) ? (appBaseAddr + 0x1F8A00) : (appBaseAddr + 0x1F8AF8), 6); // dmc3.exe+1F89E1 - 0F82 11010000 - jb dmc3.exe+1F8AF8
		WriteAddress((appBaseAddr + 0x1F89FB), (enable) ? (appBaseAddr + 0x1F8A00) : (appBaseAddr + 0x1F8AF8), 5); // dmc3.exe+1F89FB - E9 F8000000   - jmp dmc3.exe+1F8AF8
		// Quicksilver
		WriteAddress((appBaseAddr + 0x1F8A07), (enable) ? (appBaseAddr + 0x1F8AAC) : (appBaseAddr + 0x1F8AF8), 6); // dmc3.exe+1F8A07 - 0F85 EB000000 - jne dmc3.exe+1F8AF8
		WriteAddress((appBaseAddr + 0x1F8A7D), (enable) ? (appBaseAddr + 0x1F8AAC) : (appBaseAddr + 0x1F8AF8), 2); // dmc3.exe+1F8A7D - 72 79         - jb dmc3.exe+1F8AF8
		WriteAddress((appBaseAddr + 0x1F8AAA), (enable) ? (appBaseAddr + 0x1F8AAC) : (appBaseAddr + 0x1F8AF8), 2); // dmc3.exe+1F8AAA - EB 4C         - jmp dmc3.exe+1F8AF8
		// Royalguard
		WriteAddress((appBaseAddr + 0x1F8AC4), (enable) ? (appBaseAddr + 0x1F8AC6) : (appBaseAddr + 0x1F8AF8), 2); // dmc3.exe+1F8AC4 - EB 32 - jmp dmc3.exe+1F8AF8
	}

	// Gunslinger Fixes
	{
		// Allow Charging
		WriteAddress((appBaseAddr + 0x21607C), (enable) ? (appBaseAddr + 0x216082) : (appBaseAddr + 0x216572), 6);
		/*
		dmc3.exe+21606F - 83 BF 38630000 01 - cmp dword ptr [rdi+00006338],01
		dmc3.exe+21607C - 0F85 F0040000     - jne dmc3.exe+216572
		dmc3.exe+216082 - 83 BF 943E0000 02 - cmp dword ptr [rdi+00003E94],02
		*/

		// Allow Charged Shot
		WriteAddress((appBaseAddr + 0x1E6AAD), (enable) ? (appBaseAddr + 0x1E6AB3) : (appBaseAddr + 0x1E64A9), 6);
		/*
		dmc3.exe+1E6AA7 - 3B 83 38630000 - cmp eax,[rbx+00006338]
		dmc3.exe+1E6AAD - 0F85 F6F9FFFF  - jne dmc3.exe+1E64A9
		dmc3.exe+1E6AB3 - 83 7B 78 00    - cmp dword ptr [rbx+78],00
		*/

		// Allow Wild Stomp
		Write<byte8>((appBaseAddr + 0x1E7F5F), (enable) ? 0xEB : 0x74);
		/*
		dmc3.exe+1E7F55 - 83 B9 38630000 01 - cmp dword ptr [rcx+00006338],01
		dmc3.exe+1E7F5F - 74 15             - je dmc3.exe+1E7F76
		*/
	}

	// Disable Dante Check
	Write<byte8>((appBaseAddr + 0x1E8F98), (enable) ? 0xEB : 0x74);
	/*
	dmc3.exe+1E8F98 - 74 0D - je dmc3.exe+1E8FA7
	dmc3.exe+1E8F9A - 32 C0 - xor al,al
	*/
}










bool DevilButtonCheck(PlayerActorData & actorData)
{
	auto & playerData = GetPlayerData(actorData);

	bool condition = (actorData.buttons[0] & playerData.button);

	if (actorData.newEntityIndex == ENTITY::MAIN)
	{
		if (condition)
		{
			return false;
		}
	}
	else
	{
		if (!condition)
		{
			return false;
		}
	}

	return true;
}

// @Todo: Update.
void ActivateDevil(PlayerActorData & actorData)
{
	switch (actorData.character)
	{
		case CHARACTER::DANTE:
		{
			auto & actorData2 = *reinterpret_cast<PlayerActorDataDante *>(&actorData);
			UpdateForm(actorData2);
			break;
		}
		case CHARACTER::VERGIL:
		{
			auto & actorData2 = *reinterpret_cast<PlayerActorDataVergil *>(&actorData);
			UpdateForm(actorData2);
			break;
		}
	}

	func_1F94D0(actorData, DEVIL_FLUX::START);
}

void DeactivateDevil(PlayerActorData & actorData)
{
	switch (actorData.character)
	{
		case CHARACTER::DANTE:
		{
			auto & actorData2 = *reinterpret_cast<PlayerActorDataDante *>(&actorData);
			UpdateForm(actorData2);
			break;
		}
		case CHARACTER::VERGIL:
		{
			auto & actorData2 = *reinterpret_cast<PlayerActorDataVergil *>(&actorData);
			UpdateForm(actorData2);
			break;
		}
	}

	func_1F94D0(actorData, DEVIL_FLUX::END);
}








void UpdateColorMatrices(PlayerActorData & actorData)
{
	if constexpr (debug)
	{
		LogFunction(actorData.operator byte8 *());
	}

	if (actorData.visibility != 0)
	{
		actorData.visibility = (g_quicksilver) ? 2 : 1;
	}

	uint16 value = (g_quicksilver) ? 128 : 0;

	old_for_all(uint8, index, countof(actorData.newModelData))
	{
		if (!actorData.newModelData[index].visible)
		{
			continue;
		}

		auto dest = reinterpret_cast<byte8 *>(&actorData.newModelData[index]);

		*reinterpret_cast<uint16 *>(dest + 0x80 + 0x214) = value;
	}

	if (actorData.character == CHARACTER::BOB)
	{
		auto dest = reinterpret_cast<byte8 *>(&actorData);

		*reinterpret_cast<uint16 *>(dest + 0x13E10 + 0x214) = value;
	}

	old_for_all(uint8, weaponIndex, WEAPON_COUNT)
	{
		auto & weapon = actorData.newWeapons[weaponIndex];
		if (weapon >= WEAPON::MAX)
		{
			continue;
		}

		auto weaponDataAddr = actorData.newWeaponDataAddr[weaponIndex];
		if (!weaponDataAddr)
		{
			continue;
		}

		auto dest = reinterpret_cast<byte8 *>(weaponDataAddr);

		constexpr uint32 offs[WEAPON::MAX] =
		{
			0x280,
			0x880,
			0x340,
			0x300,
			0x3C0,
			0,
			0x280,
			0x400,
			0x200,
			0x280,
			0,
			0,
			0x3C0,
			0x280,
			0,
		};

		auto off = offs[weapon];

		switch (weapon)
		{
			case WEAPON::EBONY_IVORY:
			{
				*reinterpret_cast<uint16 *>(dest + 0x200 + 0x214) = value;
				*reinterpret_cast<uint16 *>(dest + 0x980 + 0x214) = value;

				break;
			}
			case WEAPON::YAMATO_VERGIL:
			case WEAPON::YAMATO_BOB:
			{
				*reinterpret_cast<uint16 *>(dest + 0xF00  + 0x214) = value;
				*reinterpret_cast<uint16 *>(dest + 0x1680 + 0x214) = value;

				break;
			}
			default:
			{
				*reinterpret_cast<uint16 *>(dest + off + 0x214) = value;

				break;
			}
		}
	}
}

inline void QuicksilverFunction
(
	byte8 * actorBaseAddr,
	bool enable
)
{
	if (!actorBaseAddr)
	{
		return;
	}
	else if (actorBaseAddr != g_playerActorBaseAddrs[2])
	{
		return;
	}

	g_quicksilver = enable;

	old_for_all(uint32, index, g_playerActorBaseAddrs.count)
	{
		IntroducePlayerActorData(actorBaseAddr2, g_playerActorBaseAddrs[index], actorData2, continue);

		UpdateColorMatrices(actorData2);
	}
}

void ActivateQuicksilver(byte8 * actorBaseAddr)
{
	if constexpr (debug)
	{
		LogFunction(actorBaseAddr);
	}

	QuicksilverFunction
	(
		actorBaseAddr,
		true
	);


	// [&]()
	// {
	// 	if (actorBaseAddr != g_playerActorBaseAddrs[2])
	// 	{
	// 		return;
	// 	}

	// 	IntroduceData(g_playerActorBaseAddrs[2], actorData, PlayerActorData, return);

	// 	auto dest = reinterpret_cast<byte8 *>(actorData.newModelPhysicsMetadataPool[0][3]);

	// 	dest = *reinterpret_cast<byte8 **>(dest + 0x110);

	// 	dest += 0x30;

	// 	func_27AA90
	// 	(
	// 		&actorData.var_63D0,
	// 		0,
	// 		dest,
	// 		60.0f
	// 	);
	// 	/*
	// 	dmc3.exe+1E9489 - E8 02160900 - call dmc3.exe+27AA90
	// 	dmc3.exe+1E948E - 3C 01       - cmp al,01
	// 	*/
	// }();







}

void DeactivateQuicksilver(byte8 * actorBaseAddr)
{
	if constexpr (debug)
	{
		LogFunction(actorBaseAddr);
	}

	QuicksilverFunction
	(
		actorBaseAddr,
		false
	);
}

void ActivateDoppelganger(PlayerActorData & actorData)
{
	LogFunction(actorData.operator byte8 *());

	if (!actorData.cloneActorBaseAddr)
	{
		return;
	}
	auto & cloneActorData = *reinterpret_cast<PlayerActorData *>(actorData.cloneActorBaseAddr);

	SetMemory(actorData.var_6438, 0, (actorData.var_6440 * 46));
	/*
	dmc3.exe+1E9222 - 33 D2             - xor edx,edx
	dmc3.exe+1E92A3 - 48 63 87 40640000 - movsxd rax,dword ptr [rdi+00006440]
	dmc3.exe+1E92AA - 48 8B 8F 38640000 - mov rcx,[rdi+00006438]
	dmc3.exe+1E92B1 - 4C 6B C0 2E       - imul r8,rax,2E
	dmc3.exe+1E92B5 - E8 30D91500       - call dmc3.exe+346BEA
	*/

	actorData.cloneRate = 0;

	func_1EAE60(actorData, 0);
	/*
	dmc3.exe+1E92D7 - 33 D2       - xor edx,edx
	dmc3.exe+1E92D9 - 48 8B CF    - mov rcx,rdi
	dmc3.exe+1E92DC - E8 7F1B0000 - call dmc3.exe+1EAE60
	*/

	ToggleActor(cloneActorData, true);
}

void DeactivateDoppelganger(PlayerActorData & actorData)
{
	LogFunction(actorData.operator byte8 *());

	// if (!actorData.cloneActorBaseAddr)
	// {
	// 	return;
	// }
	// auto & cloneActorData = *reinterpret_cast<PlayerActorData *>(actorData.cloneActorBaseAddr);

	IntroduceData(actorData.cloneActorBaseAddr, cloneActorData, PlayerActorData, return);

	func_1EAE60(actorData, 1);
	/*
	dmc3.exe+1E9339 - B2 01       - mov dl,01
	dmc3.exe+1E9351 - 48 8B CF    - mov rcx,rdi
	dmc3.exe+1E9354 - E8 071B0000 - call dmc3.exe+1EAE60
	*/

	if (cloneActorData.devil)
	{
		cloneActorData.devil = false;

		DeactivateDevil(cloneActorData);
	}

	ToggleActor(cloneActorData, false);

	EndMotion(cloneActorData);
}

bool DeactivateDoppelgangerDeathCheck(PlayerActorData & actorData)
{
	IntroduceData(actorData.cloneActorBaseAddr, cloneActorData, PlayerActorData, return true); // true to avoid clone crash.



	if (actorData.dead)
	{
		DeactivateDoppelganger(actorData);

		cloneActorData.doppelganger = actorData.doppelganger = false;
		actorData.var_6340 = 0;
		actorData.cloneStatus = CLONE_STATUS::IDLE;
		/*
		dmc3.exe+1E2AD8 - C6 81 62630000 00       - mov byte ptr [rcx+00006362],00
		dmc3.exe+1E2ADF - C6 80 62630000 00       - mov byte ptr [rax+00006362],00
		dmc3.exe+1E2AEC - C7 81 40630000 00000000 - mov [rcx+00006340],00000000
		dmc3.exe+1E2AF6 - C7 81 54640000 00000000 - mov [rcx+00006454],00000000
		*/



		return true;
	}



	return false;
}





void DecommissionDoppelgangers()
{
	old_for_all(uint64, actorIndex, g_playerActorBaseAddrs.count)
	{
		IntroduceData(g_playerActorBaseAddrs[actorIndex], actorData, PlayerActorData, continue);

		if
		(
			(actorData.newEntityIndex != ENTITY::MAIN) ||
			!actorData.doppelganger
		)
		{
			continue;
		}

		actorData.cloneStatus = CLONE_STATUS::DECOMMISSION;

		DeactivateDoppelganger(actorData);
	}
}































bool EbonyIvoryRainStormCheck(PlayerActorData & actorData)
{
	if (actorData.buttons[0] & GetBinding(BINDING::STYLE_ACTION))
	{
		return true;
	}

	return false;
}




bool DotShadowCheck(byte8 * dest)
{
	if (!dest)
	{
		return false;
	}

	switch (activeConfig.dotShadow)
	{
		case DOT_SHADOW::DISABLE:
		{
			return true;
		}
		case DOT_SHADOW::DISABLE_PLAYER_ACTORS_ONLY:
		{
			auto baseAddr = *reinterpret_cast<byte8 **>(dest + 0xC0);
			if (!baseAddr)
			{
				break;
			}

			// Main Actor
			{
				IntroduceMainActorData(actorBaseAddr, actorData, break);

				if (baseAddr == actorBaseAddr)
				{
					return true;
				}
			}

			// Actor
			{
				if (!activeConfig.Actor.enable)
				{
					break;
				}

				old_for_all(uint32, actorIndex, g_playerActorBaseAddrs.count)
				{
					IntroducePlayerActorData(actorBaseAddr, g_playerActorBaseAddrs[actorIndex], actorData, continue);

					if (baseAddr == actorBaseAddr)
					{
						return true;
					}
				}
			}

			break;
		}
	}

	return false;
}











uint8 VisibilityCheck(byte8 * baseAddr)
{
	if (!baseAddr)
	{
		return 0;
	}



	old_for_all(uint8, entityIndex, ENTITY_COUNT)
	{
		auto & newActorData = g_defaultNewActorData[entityIndex];

		IntroduceData(newActorData.baseAddr, actorData, PlayerActorData, continue);

		if (baseAddr == newActorData.baseAddr)
		{
			return newActorData.visibility;
		}

		old_for_all(uint8, weaponIndex, WEAPON_COUNT)
		{
			auto weaponDataAddr = actorData.newWeaponDataAddr[weaponIndex];
			auto weaponBaseAddr = reinterpret_cast<byte8 *>(weaponDataAddr);

			if (baseAddr == weaponBaseAddr)
			{
				return newActorData.visibility;
			}
		}
	}



	old_for_all(uint8, playerIndex   , PLAYER_COUNT   ){
	old_for_all(uint8, characterIndex, CHARACTER_COUNT){
	old_for_all(uint8, entityIndex   , ENTITY_COUNT   )
	{
		IntroducePlayerCharacterNewActorData(playerIndex, characterIndex, entityIndex);

		IntroduceData(newActorData.baseAddr, actorData, PlayerActorData, continue);

		if (baseAddr == newActorData.baseAddr)
		{
			return newActorData.visibility;
		}

		// Could be boss.
		if (characterData.character >= CHARACTER::MAX)
		{
			continue;
		}

		old_for_all(uint8, weaponIndex, WEAPON_COUNT)
		{
			auto weaponDataAddr = actorData.newWeaponDataAddr[weaponIndex];
			auto weaponBaseAddr = reinterpret_cast<byte8 *>(weaponDataAddr);

			if (baseAddr == weaponBaseAddr)
			{
				return newActorData.visibility;
			}
		}
	}}}



	return 0;
}

bool CollisionCheck(byte8 * collisionDataAddr)
{
	if (!collisionDataAddr)
	{
		return false;
	}



	old_for_all(uint8, entityIndex, ENTITY_COUNT)
	{
		auto & newActorData = g_defaultNewActorData[entityIndex];

		auto baseAddr = (collisionDataAddr - offsetof(PlayerActorData, collisionData));

		if (baseAddr != newActorData.baseAddr)
		{
			continue;
		}

		return !newActorData.enableCollision;
	}



	old_for_all(uint8, playerIndex   , PLAYER_COUNT   ){
	old_for_all(uint8, characterIndex, CHARACTER_COUNT){
	old_for_all(uint8, entityIndex   , ENTITY_COUNT   )
	{
		IntroducePlayerCharacterNewActorData(playerIndex, characterIndex, entityIndex);

		byte8 * baseAddr = 0;

		if (characterData.character == CHARACTER::BOSS_LADY)
		{
			baseAddr = (collisionDataAddr - offsetof(EnemyActorDataLady, collisionData));
		}
		else if (characterData.character == CHARACTER::BOSS_VERGIL)
		{
			baseAddr = (collisionDataAddr - offsetof(EnemyActorDataVergil, collisionData));
		}
		else
		{
			baseAddr = (collisionDataAddr - offsetof(PlayerActorData, collisionData));
		}

		if (baseAddr != newActorData.baseAddr)
		{
			continue;
		}

		return !newActorData.enableCollision;
	}}}



	return false;
}

bool VerticalPullCheck(byte8 * actorBaseAddr)
{
	if (!actorBaseAddr)
	{
		return false;
	}



	old_for_all(uint8, entityIndex, ENTITY_COUNT)
	{
		auto & newActorData = g_defaultNewActorData[entityIndex];

		if (actorBaseAddr != newActorData.baseAddr)
		{
			continue;
		}

		return !newActorData.enableCollision;
	}



	old_for_all(uint8, playerIndex   , PLAYER_COUNT   ){
	old_for_all(uint8, characterIndex, CHARACTER_COUNT){
	old_for_all(uint8, entityIndex   , ENTITY_COUNT   )
	{
		IntroducePlayerCharacterNewActorData(playerIndex, characterIndex, entityIndex);

		if (actorBaseAddr != newActorData.baseAddr)
		{
			continue;
		}

		return !newActorData.enableCollision;
	}}}



	return false;
}

































void ResetVisibility(PlayerActorData & actorData)
{
	if (actorData.visibility != 0)
	{
		actorData.visibility = (g_quicksilver) ? 2 : 1;
	}
}







float * GetRebellionStingerDuration(PlayerActorData & actorData)
{
	uint8 index = (actorData.devil) ? 1 : 0;

	return (actorData.state & STATE::IN_AIR) ?
	&activeConfig.Rebellion.airStingerDuration[index] :
	&activeConfig.Rebellion.stingerDuration[index];
}

float * GetRebellionStingerRange(PlayerActorData & actorData)
{
	uint8 index = (actorData.devil) ? 1 : 0;

	return (actorData.state & STATE::IN_AIR) ?
	&activeConfig.Rebellion.airStingerRange[index] :
	&activeConfig.Rebellion.stingerRange[index];
}



float * GetYamatoForceEdgeStingerDuration(PlayerActorData & actorData)
{
	uint8 index = (actorData.devil) ? 1 : 0;

	return (actorData.state & STATE::IN_AIR) ?
	&activeConfig.YamatoForceEdge.airStingerDuration[index] :
	&activeConfig.YamatoForceEdge.stingerDuration[index];
}

float * GetYamatoForceEdgeStingerRange(PlayerActorData & actorData)
{
	uint8 index = (actorData.devil) ? 1 : 0;

	return (actorData.state & STATE::IN_AIR) ?
	&activeConfig.YamatoForceEdge.airStingerRange[index] :
	&activeConfig.YamatoForceEdge.stingerRange[index];
}


uint32 GetYamatoJudgementCutCount(PlayerActorData & actorData)
{
	uint8 index = (actorData.devil) ? 1 : 0;

	return static_cast<uint32>(activeConfig.Yamato.judgementCutCount[index]);
}





void SetAction(byte8 * actorBaseAddr)
{
	IntroduceData(actorBaseAddr, actorData, PlayerActorData, return);

	uint8 index = (actorData.devil) ? 1 : 0;

	auto lockOn = (actorData.buttons[0] & GetBinding(BINDING::LOCK_ON));

	auto tiltDirection = GetRelativeTiltDirection(actorData);



	DebugLog("%s %llX %u", FUNC_NAME, actorBaseAddr, actorData.action);



	switch (actorData.character)
	{
		case CHARACTER::DANTE:
		{
			using namespace ACTION_DANTE;

			actorData.motionArchives[MOTION_GROUP_DANTE::REBELLION] = File_staticFiles[pl000_00_3];



			if
			(
				activeConfig.enableRebellionAirStinger &&
				(actorData.action == REBELLION_HELM_BREAKER) &&
				(actorData.newAirStingerCount < activeConfig.Rebellion.airStingerCount[index]) &&
				lockOn &&
				(tiltDirection == TILT_DIRECTION::UP)
			)
			{
				actorData.action = REBELLION_STINGER_LEVEL_2;

				actorData.newAirStingerCount++;
			}
			else if
			(
				activeConfig.enableRebellionNewDrive &&
				(actorData.action == REBELLION_COMBO_1_PART_1) &&
				lockOn &&
				(tiltDirection == TILT_DIRECTION::LEFT)
			)
			{
				actorData.action = REBELLION_DRIVE_1;
			}
			else if
			(
				activeConfig.enableRebellionQuickDrive &&
				(demo_pl000_00_3 != 0) &&
				(actorData.action == REBELLION_COMBO_1_PART_2) &&
				(actorData.style == STYLE::SWORDMASTER) &&
				(actorData.buttons[0] & GetBinding(BINDING::STYLE_ACTION))
			)
			{
				actorData.action = REBELLION_DRIVE_1;

				actorData.motionArchives[MOTION_GROUP_DANTE::REBELLION] = demo_pl000_00_3;

				actorData.newQuickDrive = true;
			}
			else if
			(
				activeConfig.enableCerberusAirRevolver &&
				(actorData.action == CERBERUS_SWING) &&
				lockOn &&
				(tiltDirection == TILT_DIRECTION::UP)
			)
			{
				actorData.action = CERBERUS_REVOLVER_LEVEL_2;
			}
			else if
			(
				activeConfig.enableNevanNewVortex &&
				(actorData.action == NEVAN_AIR_PLAY) &&
				actorData.devil &&
				(tiltDirection != TILT_DIRECTION::NEUTRAL)
			)
			{
				actorData.action = NEVAN_VORTEX;
			}



			break;
		}
		case CHARACTER::VERGIL:
		{
			using namespace ACTION_VERGIL;



			if
			(
				activeConfig.enableYamatoVergilNewJudgementCut &&
				(actorData.action == YAMATO_COMBO_PART_1) &&
				lockOn &&
				(tiltDirection == TILT_DIRECTION::LEFT)
			)
			{
				actorData.action = YAMATO_JUDGEMENT_CUT_LEVEL_2;
			}
			// else if (actorData.action == BEOWULF_RISING_SUN)
			// {
			// 	actorData.newAirRisingSunCount = 1;
			// }
			else if
			(
				activeConfig.enableBeowulfVergilAirRisingSun &&
				(actorData.action == BEOWULF_STARFALL_LEVEL_2) &&
				(actorData.newAirRisingSunCount < activeConfig.beowulfVergilAirRisingSunCount[index]) &&
				lockOn &&
				(tiltDirection == TILT_DIRECTION::DOWN)
			)
			{
				actorData.action = BEOWULF_RISING_SUN;

				actorData.newAirRisingSunCount++;
			}
			else if
			(
				activeConfig.enableBeowulfVergilAirLunarPhase &&
				(actorData.action == BEOWULF_STARFALL_LEVEL_2) &&
				lockOn &&
				(tiltDirection == TILT_DIRECTION::UP)
			)
			{
				actorData.action = BEOWULF_LUNAR_PHASE_LEVEL_2;
			}
			else if
			(
				activeConfig.enableYamatoForceEdgeNewComboPart4 &&
				(actorData.action == YAMATO_FORCE_EDGE_COMBO_PART_1) &&
				lockOn &&
				(tiltDirection == TILT_DIRECTION::RIGHT)
			)
			{
				actorData.action = YAMATO_FORCE_EDGE_COMBO_PART_4;
			}
			else if
			(
				activeConfig.enableYamatoForceEdgeAirStinger &&
				(actorData.action == YAMATO_FORCE_EDGE_HELM_BREAKER_LEVEL_2) &&
				(actorData.newAirStingerCount < activeConfig.YamatoForceEdge.airStingerCount[index]) &&
				lockOn &&
				(tiltDirection == TILT_DIRECTION::UP)
			)
			{
				actorData.action = YAMATO_FORCE_EDGE_STINGER_LEVEL_2;

				actorData.newAirStingerCount++;
			}
			else if
			(
				activeConfig.enableYamatoForceEdgeNewRoundTrip &&
				(actorData.action == YAMATO_FORCE_EDGE_COMBO_PART_1) &&
				lockOn &&
				(tiltDirection == TILT_DIRECTION::LEFT)
			)
			{
				actorData.action = YAMATO_FORCE_EDGE_ROUND_TRIP;
			}



			break;
		}
	}
}



bool AirActionCheck(PlayerActorData & actorData)
{
	switch (actorData.character)
	{
		case CHARACTER::DANTE:
		{
			if
			(
				(actorData.state & STATE::IN_AIR) &&
				(actorData.action == ACTION_DANTE::REBELLION_STINGER_LEVEL_2) &&
				(actorData.motionData[1].group == MOTION_GROUP_DANTE::REBELLION)
			)
			{
				return true;
			}
			else if
			(
				(actorData.state & STATE::IN_AIR) &&
				(actorData.action == ACTION_DANTE::CERBERUS_REVOLVER_LEVEL_2) &&
				(actorData.motionData[1].group == MOTION_GROUP_DANTE::CERBERUS)
			)
			{
				return true;
			}

			break;
		}
		case CHARACTER::VERGIL:
		{
			if
			(
				(actorData.state & STATE::IN_AIR) &&
				(actorData.action == ACTION_VERGIL::YAMATO_FORCE_EDGE_STINGER_LEVEL_2) &&
				(actorData.motionData[1].group == MOTION_GROUP_VERGIL::YAMATO_FORCE_EDGE)
			)
			{
				return true;
			}

			break;
		}
	}

	return false;
}



















bool EndActionLedge(byte8 * actorBaseAddr)
{
	IntroducePlayerActorData(actorBaseAddr, actorData, return false);

	if (AirActionCheck(actorData))
	{
		return true;
	}

	return false;
}

bool DecreaseAltitude(byte8 * actorBaseAddr)
{
	IntroducePlayerActorData(actorBaseAddr, actorData, return false);

	if (AirActionCheck(actorData))
	{
		return true;
	}

	return false;
}
















// export void Actor_Init()
// {
// 	LogFunction();

// 	// Reset Actor Mode
// 	{
// 		constexpr byte8 sect0[] =
// 		{
// 			0x48, 0x8B, 0x5C, 0x24, 0x50, // mov rbx,[rsp+50]
// 		};
// 		auto func = old_CreateFunction(ResetActorMode, (appBaseAddr + 0x1E14E6), true, true, sizeof(sect0));
// 		CopyMemory(func.sect0, sect0, sizeof(sect0));
// 		ResetActorModeAddr = func.addr;
// 		/*
// 		dmc3.exe+1E14E1 - 48 8B 5C 24 50 - mov rbx,[rsp+50]
// 		dmc3.exe+1E14E6 - 48 83 C4 40    - add rsp,40
// 		*/
// 	}
// }




void UpdateLockOns(byte8 * dataAddr)
{
	if (!activeConfig.updateLockOns)
	{
		return;
	}

	// IntroduceMainActorData(mainActorBaseAddr, mainActorData, return);


/*

dmc3.exe+215ED5 - 83 BC 87 70CA0100 02  - cmp dword ptr [rdi+rax*4+0001CA70],02 { 2 }


*/


	// // Artemis Fix
	// {
	// 	auto & actorData = *reinterpret_cast<PlayerActorDataDante *>(mainActorBaseAddr);

	// 	auto rangedWeapon = actorData.newWeapons[actorData.rangedWeaponIndex];

	// 	if
	// 	(
	// 		(actorData.character == CHARACTER::DANTE) &&
	// 		(rangedWeapon == WEAPON::ARTEMIS) &&
	// 		(actorData.artemisStatus != 0)
	// 		// (
	// 		// 	(actorData.buttons[0] & GAMEPAD::X) ||
	// 		// 	(
	// 		// 		(actorData.style == STYLE::GUNSLINGER) &&
	// 		// 		(actorData.buttons[0] & GAMEPAD::B)
	// 		// 	)
	// 		// )
	// 	)
	// 	{
	// 		return;
	// 	}
	// }



	for_all(actorIndex, g_playerActorBaseAddrs.count)
	{
		IntroducePlayerActorData(actorBaseAddr, g_playerActorBaseAddrs[actorIndex], actorData, continue);

		// if (actorBaseAddr == mainActorBaseAddr)
		// {
		// 	continue;
		// }

		UpdateLockOn(actorBaseAddr, dataAddr);
	}
}




export void ToggleDeplete(bool enable)
{
	LogFunction(enable);

	static bool run = false;

	// Deplete Quicksilver
	{
		auto addr     = (appBaseAddr + 0x1F8A40);
		auto jumpAddr = (appBaseAddr + 0x1F8A48);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+1F8A40 - F3 0F59 88 70010000 - mulss xmm1,[rax+00000170]
		dmc3.exe+1F8A48 - E8 238DFEFF         - call dmc3.exe+1E1770
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rax
			0xF3, 0x0F, 0x59, 0x08,                                     // mulss xmm1,[rax]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<float **>(func.sect0 + 2) = &activeConfig.depleteQuicksilver;
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

	// Deplete Doppelganger
	{
		auto addr     = (appBaseAddr + 0x1F89D1);
		auto jumpAddr = (appBaseAddr + 0x1F89D9);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+1F89D1 - F3 0F59 88 74010000 - mulss xmm1,[rax+00000174]
		dmc3.exe+1F89D9 - E8 928DFEFF         - call dmc3.exe+1E1770
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rax
			0xF3, 0x0F, 0x59, 0x08,                                     // mulss xmm1,[rax]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<float **>(func.sect0 + 2) = &activeConfig.depleteDoppelganger;
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

	// Deplete Devil
	{
		auto addr     = (appBaseAddr + 0x1F8B49);
		auto jumpAddr = (appBaseAddr + 0x1F8B51);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+1F8B49 - F3 0F59 88 78010000 - mulss xmm1,[rax+00000178]
		dmc3.exe+1F8B51 - E8 1A8CFEFF         - call dmc3.exe+1E1770
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rax
			0xF3, 0x0F, 0x59, 0x08,                                     // mulss xmm1,[rax]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<float **>(func.sect0 + 2) = &activeConfig.depleteDevil;
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

export void ToggleOrbReach(bool enable)
{
	LogFunction(enable);

	static bool run = false;

	{
		auto addr     = (appBaseAddr + 0x1B655F);
		auto jumpAddr = (appBaseAddr + 0x1B6567);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+1B655F - F3 0F10 35 2DFB3000 - movss xmm6,[dmc3.exe+4C6094]
		dmc3.exe+1B6567 - EB 2B               - jmp dmc3.exe+1B6594
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x50,                                                       // push rax
			0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rax
			0xF3, 0x0F, 0x10, 0x30,                                     // movss xmm6,[rax]
			0x58,                                                       // pop rax
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<float **>(func.sect0 + 3) = &activeConfig.orbReach;
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

export void ToggleDamage(bool enable)
{
	LogFunction(enable);

	static bool run = false;

	// Apply Damage
	{
		auto addr     = (appBaseAddr + 0x88512);
		auto jumpAddr = (appBaseAddr + 0x88517);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+88512 - F3 0F10 40 08 - movss xmm0,[rax+08]
		dmc3.exe+88517 - F3 41 0F5C C0 - subss xmm0,xmm8
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rax,
			0xF3, 0x41, 0x0F, 0x10, 0xC8, // movss xmm1,xmm8
		};

		constexpr byte8 sect2[] =
		{
			0xF3, 0x44, 0x0F, 0x10, 0xC0, // movss xmm8,xmm0
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(ApplyDamage, jumpAddr, true, true, 0, sizeof(sect1), (sizeof(sect2) + size), 0, 0, true, true, false);
			CopyMemory(func.sect1, sect1, sizeof(sect1));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
			CopyMemory((func.sect2 + sizeof(sect2)), addr, size, MemoryFlags_VirtualProtectSource);
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




byte8 * SaveFix(byte8 * actorBaseAddr)
{
	auto newActorBaseAddr = g_playerActorBaseAddrs[0];
	if (newActorBaseAddr != 0)
	{
		return newActorBaseAddr;
	}

	return actorBaseAddr;
}




// // @Remove
// bool WriteVisibleFalse(byte8 * baseAddr)
// {
// 	if (!baseAddr)
// 	{
// 		return false;
// 	}




// 	if (g_visible)
// 	{
// 		return true;
// 	}



// 	return false;
// }

// // @Remove
// bool WriteVisibleTrue(byte8 * baseAddr)
// {
// 	if (!baseAddr)
// 	{
// 		return false;
// 	}





// 	if (g_visible)
// 	{
// 		return true;
// 	}


// 	return false;
// }
























bool SetVisible(byte8 * actorBaseAddr)
{


	IntroduceData(actorBaseAddr, actorData, PlayerActorData, return false);

	auto playerIndex    = actorData.newPlayerIndex;
	auto characterIndex = actorData.newCharacterIndex;
	auto entityIndex    = actorData.newEntityIndex;



	auto & playerData = GetPlayerData(playerIndex);



	if
	(
		g_quicksilver &&
		(actorBaseAddr == g_playerActorBaseAddrs[2]) &&
		(actorData.newCharacterIndex != playerData.activeCharacterIndex)
	)
	{
		return true;
	}





	return false;
}







export void ToggleDergil(uint8 value)
{
	LogFunction(value);

	static bool run = false;

	using namespace DERGIL;



// New Color
{
	auto addr = (appBaseAddr + 0x18412F);
	constexpr uint32 size = 6;
	/*
	dmc3.exe+18412F - 83 79 78 03 - cmp dword ptr [rcx+78],03
	dmc3.exe+184133 - 75 0F       - jne dmc3.exe+184144
	dmc3.exe+184135 - 49 8B 45 00 - mov rax,[r13+00]
	*/

	if (!run)
	{
		backupHelper.Save(addr, size);
	}

	backupHelper.Restore(addr);

	if (value == FORCE_OFF)
	{
		Write<byte8>((addr + 4), 0xEB);
	}
	else if (value == FORCE_ON)
	{
		SetMemory(addr, 0x90, size, MemoryFlags_VirtualProtectDestination);
	}
}

// New Color 2
{
	auto addr = (appBaseAddr + 0x184251);
	constexpr uint32 size = 6;
	/*
	dmc3.exe+184251 - 83 79 78 03 - cmp dword ptr [rcx+78],03
	dmc3.exe+184255 - 75 0E       - jne dmc3.exe+184265
	dmc3.exe+184257 - 48 8B 07    - mov rax,[rdi]
	*/

	if (!run)
	{
		backupHelper.Save(addr, size);
	}

	backupHelper.Restore(addr);

	if (value == FORCE_OFF)
	{
		Write<byte8>((addr + 4), 0xEB);
	}
	else if (value == FORCE_ON)
	{
		SetMemory(addr, 0x90, size, MemoryFlags_VirtualProtectDestination);
	}
}


// Teleport
{
	auto addr = (appBaseAddr + 0x180C1B);
	constexpr uint32 size = 6;
	/*
	dmc3.exe+180C1B - 83 7A 78 03       - cmp dword ptr [rdx+78],03
	dmc3.exe+180C1F - 75 2F             - jne dmc3.exe+180C50
	dmc3.exe+180C21 - 83 B9 10EF0000 01 - cmp dword ptr [rcx+0000EF10],01
	*/

	if (!run)
	{
		backupHelper.Save(addr, size);
	}

	backupHelper.Restore(addr);

	if (value == FORCE_OFF)
	{
		Write<byte8>((addr + 4), 0xEB);
	}
	else if (value == FORCE_ON)
	{
		SetMemory(addr, 0x90, size, MemoryFlags_VirtualProtectDestination);
	}
}


// Teleport 2
{
	auto addr = (appBaseAddr + 0x17A68E);
	constexpr uint32 size = 10;
	/*
	dmc3.exe+17A68E - 83 7A 78 03       - cmp dword ptr [rdx+78],03
	dmc3.exe+17A692 - 0F85 BE030000     - jne dmc3.exe+17AA56
	dmc3.exe+17A698 - 83 BB 10EF0000 01 - cmp dword ptr [rbx+0000EF10],01
	*/

	if (!run)
	{
		backupHelper.Save(addr, size);
	}

	backupHelper.Restore(addr);

	if (value == FORCE_OFF)
	{
		Write<byte16>((addr + 4), 0xE990);
	}
	else if (value == FORCE_ON)
	{
		SetMemory(addr, 0x90, size, MemoryFlags_VirtualProtectDestination);
	}
}






	// Color
	{
		auto addr = (appBaseAddr + 0x186414);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+186414 - 83 7A 78 03    - cmp dword ptr [rdx+78],03
		dmc3.exe+186418 - 0F85 84010000  - jne dmc3.exe+1865A2
		dmc3.exe+18641E - 48 89 5C 24 30 - mov [rsp+30],rbx
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		backupHelper.Restore(addr);

		if (value == FORCE_OFF)
		{
			Write<byte16>((addr + 4), 0xE990);
		}
		else if (value == FORCE_ON)
		{
			SetMemory(addr, 0x90, size, MemoryFlags_VirtualProtectDestination);
		}
	}

	// Color 2
	{
		auto addr = (appBaseAddr + 0x18642F);
		constexpr uint32 size = 6;
		/*
		dmc3.exe+18642F - 83 7A 78 03 - cmp dword ptr [rdx+78],03
		dmc3.exe+186433 - 75 63       - jne dmc3.exe+186498
		dmc3.exe+186435 - 48 8B 03    - mov rax,[rbx]
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		backupHelper.Restore(addr);

		if (value == FORCE_ON)
		{
			SetMemory(addr, 0x90, size, MemoryFlags_VirtualProtectDestination);
		}
	}

	// Color 3
	{
		auto addr = (appBaseAddr + 0x1864A8);
		constexpr uint32 size = 6;
		/*
		dmc3.exe+1864A8 - 83 79 78 03 - cmp dword ptr [rcx+78],03
		dmc3.exe+1864AC - 75 6F       - jne dmc3.exe+18651D
		dmc3.exe+1864AE - 48 8B 03    - mov rax,[rbx]
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		backupHelper.Restore(addr);

		if (value == FORCE_ON)
		{
			SetMemory(addr, 0x90, size, MemoryFlags_VirtualProtectDestination);
		}
	}

	// Color 4
	{
		auto addr = (appBaseAddr + 0x186534);
		constexpr uint32 size = 6;
		/*
		dmc3.exe+186534 - 83 79 78 03 - cmp dword ptr [rcx+78],03
		dmc3.exe+186538 - 75 63       - jne dmc3.exe+18659D
		dmc3.exe+18653A - 48 8B 03    - mov rax,[rbx]
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		backupHelper.Restore(addr);

		if (value == FORCE_ON)
		{
			SetMemory(addr, 0x90, size, MemoryFlags_VirtualProtectDestination);
		}
	}

	// Sparda Aura
	{
		auto addr = (appBaseAddr + 0x178A04);
		constexpr uint32 size = 2;
		/*
		dmc3.exe+178A04 - 75 05       - jne dmc3.exe+178A0B
		dmc3.exe+178A06 - BA F7000000 - mov edx,000000F7
		dmc3.exe+178A0B - E8 90F21600 - call dmc3.exe+2E7CA0
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		backupHelper.Restore(addr);

		if (value == FORCE_OFF)
		{
			Write<byte8>(addr, 0xEB);
		}
		else if (value == FORCE_ON)
		{
			SetMemory(addr, 0x90, size, MemoryFlags_VirtualProtectDestination);
		}
	}

	// Devil Aura
	{
		auto addr = (appBaseAddr + 0x178A59);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+178A59 - 83 79 78 03      - cmp dword ptr [rcx+78],03
		dmc3.exe+178A5D - 0F84 B1000000    - je dmc3.exe+178B14
		dmc3.exe+178A63 - 0F28 05 164B1E00 - movaps xmm0,[dmc3.exe+35D580]
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		backupHelper.Restore(addr);

		if (value == FORCE_OFF)
		{
			SetMemory(addr, 0x90, size, MemoryFlags_VirtualProtectDestination);
		}
		else if (value == FORCE_ON)
		{
			Write<byte16>((addr + 4), 0xE990);
		}
	}



	run = true;
}













// $ActorToggleStart



namespaceStart(Actor);

export void Toggle(bool enable)
{
	LogFunction(enable);

	static bool run = false;

	if (!run)
	{
		if (!g_playerActorBaseAddrs.Init(512))
		{
			Log("g_playerActorBaseAddrs.Init failed.");

			return;
		}
		// else if (!g_enemyActorBaseAddrs.Init(512))
		// {
		// 	Log("g_enemyActorBaseAddrs.Init failed.");

		// 	return;
		// }
		// else if (!g_enableCollisions.Init(512))
		// {
		// 	Log("g_enableCollisions.Init failed.");

		// 	return;
		// }
	}



	// Register Weapon
	{
		if (!run)
		{
			RegisterWeapon[WEAPON::REBELLION        ] = func_2310B0;
			RegisterWeapon[WEAPON::CERBERUS         ] = func_22EC90;
			RegisterWeapon[WEAPON::AGNI_RUDRA       ] = func_227870;
			RegisterWeapon[WEAPON::NEVAN            ] = func_22A1E0;
			RegisterWeapon[WEAPON::BEOWULF_DANTE    ] = func_228CF0;
			RegisterWeapon[WEAPON::EBONY_IVORY      ] = func_22B0C0;
			RegisterWeapon[WEAPON::SHOTGUN          ] = func_2306B0;
			RegisterWeapon[WEAPON::ARTEMIS          ] = func_22C4A0;
			RegisterWeapon[WEAPON::SPIRAL           ] = func_2300A0;
			RegisterWeapon[WEAPON::KALINA_ANN       ] = func_22BA30;
			RegisterWeapon[WEAPON::YAMATO_VERGIL    ] = func_22D960;
			RegisterWeapon[WEAPON::BEOWULF_VERGIL   ] = func_228CF0;
			RegisterWeapon[WEAPON::YAMATO_FORCE_EDGE] = func_2298E0;
			RegisterWeapon[WEAPON::YAMATO_BOB       ] = func_231A30;
		}
	}

	// Actor Data Size
	{
		constexpr uint32 size = (128 * 1024);
		// Dante
		Write<uint32>((appBaseAddr + 0x1DEBE1 + 1), (enable) ? size : PLAYER_ACTOR_DATA_SIZE::DANTE); // dmc3.exe+1DEBE1 - BA C0B80000 - mov edx,0000B8C0
		// Bob
		Write<uint32>((appBaseAddr + 0x1DEAC8 + 1), (enable) ? size : PLAYER_ACTOR_DATA_SIZE::BOB); // dmc3.exe+1DEAC8 - BA 80B60000 - mov edx,0000B680
		// Lady
		Write<uint32>((appBaseAddr + 0x1DE9CC + 1), (enable) ? size : PLAYER_ACTOR_DATA_SIZE::LADY); // dmc3.exe+1DE9CC - BA 80820000 - mov edx,00008280
		// Vergil
		Write<uint32>((appBaseAddr + 0x1DE8B3 + 1), (enable) ? size : PLAYER_ACTOR_DATA_SIZE::VERGIL); // dmc3.exe+1DE8B3 - BA C0B80000 - mov edx,0000B8C0
	}

	Actor::ToggleBase                  (enable);
	Actor::ToggleRelocations           (enable);
	Sound::ToggleRelocations           (enable);
	Actor::ToggleModelCountAdjustments (enable);
	Actor::ToggleWeaponCountAdjustments(enable);
	Actor::ToggleEffectRelocations     (enable);

	//ToggleHideDefaultActors(enable);




	// Model Physics Metadata Pool Offsets
	{
		static uint32 * offs = 0;
		auto defaultOffs = reinterpret_cast<uint32 *>(appBaseAddr + 0x4E0328);

		if (!run)
		{
			offs = reinterpret_cast<uint32 *>(HighAlloc(64));
			if (!offs)
			{
				Log("HighAlloc failed.");

				return;
			}

			old_for_all(uint32, index, 7)
			{
				offs[index] = (index * 24);
			}
		}

		WriteAddress((appBaseAddr + 0x1FA60B), (enable) ? offs : defaultOffs, 7); // dmc3.exe+1FA60B - 48 8D 0D 165D2E00 - lea rcx,[dmc3.exe+4E0328]
		WriteAddress((appBaseAddr + 0x1FAA57), (enable) ? offs : defaultOffs, 7); // dmc3.exe+1FAA57 - 48 8D 0D CA582E00 - lea rcx,[dmc3.exe+4E0328]
		WriteAddress((appBaseAddr + 0x1FAA77), (enable) ? offs : defaultOffs, 7); // dmc3.exe+1FAA77 - 48 8D 15 AA582E00 - lea rdx,[dmc3.exe+4E0328]
		WriteAddress((appBaseAddr + 0x1FAA97), (enable) ? offs : defaultOffs, 7); // dmc3.exe+1FAA97 - 4C 8D 05 8A582E00 - lea r8,[dmc3.exe+4E0328]
		WriteAddress((appBaseAddr + 0x1FB031), (enable) ? offs : defaultOffs, 7); // dmc3.exe+1FB031 - 48 8D 3D F0522E00 - lea rdi,[dmc3.exe+4E0328]
		WriteAddress((appBaseAddr + 0x1FBAC4), (enable) ? offs : defaultOffs, 7); // dmc3.exe+1FBAC4 - 48 8D 3D 5D482E00 - lea rdi,[dmc3.exe+4E0328]
	}

	// Update Model Dante
	{
		auto addr = (appBaseAddr + 0x212CB3);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+212CB3 - E8 98200000       - call dmc3.exe+214D50
		dmc3.exe+212CB8 - 48 8D 86 A0380000 - lea rax,[rsi+000038A0]
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(UpdateModel<PlayerActorDataDante>);
		}

		if (enable)
		{
			WriteCall(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Update Model Vergil
	{
		auto addr = (appBaseAddr + 0x220A30);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+220A30 - E8 AB150000          - call dmc3.exe+221FE0
		dmc3.exe+220A35 - 49 8D 84 24 A0380000 - lea rax,[r12+000038A0]
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(UpdateModel<PlayerActorDataVergil>);
		}

		if (enable)
		{
			WriteCall(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Coat Update Dante
	{
		auto addr     = (appBaseAddr + 0x2120C4);
		auto jumpAddr = (appBaseAddr + 0x2120CB);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+2120C4 - 48 8B 96 98180000 - mov rdx,[rsi+00001898]
		dmc3.exe+2120CB - 48 8D 8E 40750000 - lea rcx,[rsi+00007540]
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x80, 0xBE, 0x00, 0x00, 0x00, 0x00, 0x01, // cmp byte ptr [rsi+0000B8C0],01
			0x75, 0x12,                               // jne short
			0x80, 0xBE, 0x00, 0x00, 0x00, 0x00, 0x00, // cmp byte ptr [rsi+0000B8C0],02
			0x75, 0x09,                               // jne short
			0x48, 0x8B, 0x96, 0x00, 0x00, 0x00, 0x00, // mov rdx,[rsi+000018A8]
			0xEB, 0x07,                               // jmp short
			0x48, 0x8B, 0x96, 0x00, 0x00, 0x00, 0x00, // mov rdx,[rsi+00001898]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(func.sect0 + 2) = offsetof(PlayerActorData, newForceFiles);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xB) = offsetof(PlayerActorData, newForceFilesCharacter);
			*reinterpret_cast<uint8 *>(func.sect0 + 0xF) = CHARACTER::LADY;
			*reinterpret_cast<uint32 *>(func.sect0 + 0x15) = offsetof(PlayerActorData, newModelPhysicsMetadataPool[0][5]);
			*reinterpret_cast<uint32 *>(func.sect0 + 0x1E) = offsetof(PlayerActorData, newModelPhysicsMetadataPool[0][3]);
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

	// Coat Update Vergil
	{
		auto addr     = (appBaseAddr + 0x220506);
		auto jumpAddr = (appBaseAddr + 0x22050D);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+220506 - 48 8B 96 98180000 - mov rdx,[rsi+00001898]
		dmc3.exe+22050D - 48 8D 8E 40750000 - lea rcx,[rsi+00007540]
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x80, 0xBE, 0xC0, 0xB8, 0x00, 0x00, 0x01, // cmp byte ptr [rsi+0000B8C0],01
			0x75, 0x12,                               // jne short
			0x80, 0xBE, 0x00, 0x00, 0x00, 0x00, 0x00, // cmp byte ptr [rsi+0000B8C0],02
			0x75, 0x09,                               // jne short
			0x48, 0x8B, 0x96, 0x00, 0x00, 0x00, 0x00, // mov rdx,[rsi+000018A8]
			0xEB, 0x07,                               // jmp short
			0x48, 0x8B, 0x96, 0x00, 0x00, 0x00, 0x00, // mov rdx,[rsi+00001898]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(func.sect0 + 2) = offsetof(PlayerActorData, newForceFiles);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xB) = offsetof(PlayerActorData, newForceFilesCharacter);
			*reinterpret_cast<uint8 *>(func.sect0 + 0xF) = CHARACTER::LADY;
			*reinterpret_cast<uint32 *>(func.sect0 + 0x15) = offsetof(PlayerActorData, newModelPhysicsMetadataPool[0][5]);
			*reinterpret_cast<uint32 *>(func.sect0 + 0x1E) = offsetof(PlayerActorData, newModelPhysicsMetadataPool[0][3]);
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

	// Devil Coat Update Ignore Range Check
	{
		WriteAddress((appBaseAddr + 0x218982), (enable) ? (appBaseAddr + 0x218988) : (appBaseAddr + 0x218F81), 6);
		/*
		dmc3.exe+218982 - 0F87 F9050000     - ja dmc3.exe+218F81
		dmc3.exe+218988 - 83 BF 183A0000 01 - cmp dword ptr [rdi+00003A18],01
		*/
	}

	// Update Model Partitions Dante
	{
		auto addr = (appBaseAddr + 0x215577);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+215577 - E8 74140000       - call dmc3.exe+2169F0
		dmc3.exe+21557C - 48 81 C7 40750000 - add rdi,00007540
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

	// Update Model Partitions Vergil
	{
		auto addr = (appBaseAddr + 0x22285C);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+22285C - E8 BF0B0000       - call dmc3.exe+223420
		dmc3.exe+222861 - 48 8D B7 40750000 - lea rsi,[rdi+00007540]
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

	// Position Update Ebony & Ivory
	{
		auto addr     = (appBaseAddr + 0x22B60F);
		auto jumpAddr = (appBaseAddr + 0x22B616);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+22B60F - 0FB6 90 9E3E0000 - movzx edx,byte ptr [rax+00003E9E]
		dmc3.exe+22B616 - 8D 42 FD         - lea eax,[rdx-03]
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x80, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x01, // cmp byte ptr [rax+0000B8C0],01
			0x0F, 0x84, 0x00, 0x00, 0x00, 0x00,       // je dmc3.exe+22B7E2
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, (sizeof(sect0) + size));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			CopyMemory((func.sect0 + sizeof(sect0)), addr, size, MemoryFlags_VirtualProtectSource);
			*reinterpret_cast<uint32 *>(func.sect0 + 2) = offsetof(PlayerActorData, newForceFiles);
			WriteAddress((func.sect0 + 7), (appBaseAddr + 0x22B7E2), 6);
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

	// Position Update Artemis
	{
		auto addr     = (appBaseAddr + 0x22EC27);
		auto jumpAddr = (appBaseAddr + 0x22EC2E);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+22EC27 - 0FB6 82 9E3E0000 - movzx eax,byte ptr [rdx+00003E9E]
		dmc3.exe+22EC2E - 3C 07            - cmp al,07
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x80, 0xBA, 0x00, 0x00, 0x00, 0x00, 0x01, // cmp byte ptr [rdx+0000B8C0],01
			0x0F, 0x84, 0x00, 0x00, 0x00, 0x00,       // je dmc3.exe+22EC65
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, (sizeof(sect0) + size));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			CopyMemory((func.sect0 + sizeof(sect0)), addr, size, MemoryFlags_VirtualProtectSource);
			*reinterpret_cast<uint32 *>(func.sect0 + 2) = offsetof(PlayerActorData, newForceFiles);
			WriteAddress((func.sect0 + 7), (appBaseAddr + 0x22EC65), 6);
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

	// Weapon Switch Controller Dante
	{
		auto addr = (appBaseAddr + 0x1E25EB);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+1E25EB - E8 F0820000 - call dmc3.exe+1EA8E0
		dmc3.exe+1E25F0 - 48 8B CB    - mov rcx,rbx
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(WeaponSwitchController<PlayerActorDataDante>, 0, true, false);
		}

		if (enable)
		{
			WriteCall(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Weapon Switch Controller Vergil
	{
		auto addr = (appBaseAddr + 0x1E25E1);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+1E25E1 - E8 EA470000 - call dmc3.exe+1E6DD0
		dmc3.exe+1E25E6 - EB 08       - jmp dmc3.exe+1E25F0
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(WeaponSwitchController<PlayerActorDataVergil>, 0, true, false);
		}

		if (enable)
		{
			WriteCall(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Activate Quicksilver
	{
		auto addr     = (appBaseAddr + 0x1E94AA);
		auto jumpAddr = (appBaseAddr + 0x1E94B1);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1E94AA - C6 87 61630000 01       - mov byte ptr [rdi+00006361],01
		dmc3.exe+1E94B1 - C7 87 40630000 02000000 - mov [rdi+00006340],00000002
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rdi,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(ActivateQuicksilver, jumpAddr, true, true, size, sizeof(sect1));
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

	// Deactivate Quicksilver
	{
		auto addr     = (appBaseAddr + 0x1E9551);
		auto jumpAddr = (appBaseAddr + 0x1E9558);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1E9551 - 40 88 B7 61630000 - mov [rdi+00006361],sil
		dmc3.exe+1E9558 - 89 B7 40630000    - mov [rdi+00006340],esi
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rdi,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(DeactivateQuicksilver, jumpAddr, true, true, size, sizeof(sect1));
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


/*
dmc3.exe+1F8AEE - C7 87 20010000 01000000 - mov [rdi+00000120],00000001 { 1 }

*/

	// Deactivate Quicksilver 2
	{
		auto addr     = (appBaseAddr + 0x1EAC19);
		auto jumpAddr = (appBaseAddr + 0x1EAC20);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1EAC19 - C6 81 61630000 00       - mov byte ptr [rcx+00006361],00
		dmc3.exe+1EAC20 - C7 81 40630000 00000000 - mov [rcx+00006340],00000000
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(DeactivateQuicksilver, jumpAddr, true, true, size);
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

	// Activate Doppelganger
	{
		auto addr     = (appBaseAddr + 0x1E9235);
		auto jumpAddr = (appBaseAddr + 0x1E930E);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+1E9235 - C7 87 54640000 01000000 - mov [rdi+00006454],00000001
		dmc3.exe+1E923F - 8B 88 EC010000          - mov ecx,[rax+000001EC]
		dmc3.exe+1E930E - B0 01                   - mov al,01
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rdi,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(ActivateDoppelganger, jumpAddr, true, true, size, sizeof(sect1));
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

	// DeactivateDoppelganger
	{
		auto addr     = (appBaseAddr + 0x1E933B);
		auto jumpAddr = (appBaseAddr + 0x1E930E);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+1E933B - C7 87 54640000 02000000 - mov [rdi+00006454],00000002
		dmc3.exe+1E9345 - 8B 88 EC010000          - mov ecx,[rax+000001EC]
		dmc3.exe+1E930E - B0 01                   - mov al,01
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rdi,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(DeactivateDoppelganger, jumpAddr, true, true, size, sizeof(sect1));
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

	// DeactivateDoppelganger 2
	{
		auto addr     = (appBaseAddr + 0x1F89E9);
		auto jumpAddr = (appBaseAddr + 0x1F8A00);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+1F89E9 - C7 87 54640000 02000000 - mov [rdi+00006454],00000002
		dmc3.exe+1F89F3 - 48 8B CF                - mov rcx,rdi
		dmc3.exe+1F8A00 - 80 BF 61630000 01       - cmp byte ptr [rdi+00006361],01
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rdi,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(DeactivateDoppelganger, jumpAddr, true, true, size, sizeof(sect1));
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




// DeactivateDoppelgangerDeathCheck
{
	auto addr     = (appBaseAddr + 0x1E2AD1);
	auto jumpAddr = (appBaseAddr + 0x1E2AD8);
	constexpr uint32 size = 7;
	/*
	dmc3.exe+1E2AD1 - 48 8B 81 78640000 - mov rax,[rcx+00006478]
	dmc3.exe+1E2AD8 - C6 81 62630000 00 - mov byte ptr [rcx+00006362],00
	*/

	static Function func = {};

	constexpr byte8 sect2[] =
	{
		0x84, 0xC0,                               // test al,al
		0x0F, 0x85, 0x00, 0x00, 0x00, 0x00,       // jne dmc3.exe+1E2B63
		0x48, 0x8B, 0x81, 0x78, 0x64, 0x00, 0x00, // mov rax,[rcx+00006478]
	};

	if (!run)
	{
		backupHelper.Save(addr, size);
		func = old_CreateFunction(DeactivateDoppelgangerDeathCheck, jumpAddr, true, false, 0, 0, sizeof(sect2));
		CopyMemory(func.sect2, sect2, sizeof(sect2));
		WriteAddress((func.sect2 + 2), (appBaseAddr + 0x1E2B63), 6);
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






















	// Disable Doppelganger Rate Controller
	{
		Write<byte8>((appBaseAddr + 0x1E25C8), (enable) ? 0xEB : 0x75);
		/*
		dmc3.exe+1E25C8 - 75 08    - jne dmc3.exe+1E25D2
		dmc3.exe+1E25CA - 48 8B CB - mov rcx,rbx
		*/
	}

	// Devil Disable Doppelganger Check
	{
		Write<byte8>((appBaseAddr + 0x1E7775), (enable) ? 0xEB : 0x75);
		/*
		dmc3.exe+1E7775 - 75 0E             - jne dmc3.exe+1E7785
		dmc3.exe+1E7777 - 40 88 B7 AF3E0000 - mov [rdi+00003EAF],sil
		*/
	}

	// Devil Button Check
	{
		auto addr     = (appBaseAddr + 0x1E77DC);
		auto jumpAddr = (appBaseAddr + 0x1E77E9);
		constexpr uint32 size = 13;
		/*
		dmc3.exe+1E77DC - 40 38 B7 9B3E0000   - cmp [rdi+00003E9B],sil
		dmc3.exe+1E77E3 - 0F85 D4000000       - jne dmc3.exe+1E78BD
		dmc3.exe+1E77E9 - F3 0F10 87 B83E0000 - movss xmm0,[rdi+00003EB8]
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rdi,
		};
		constexpr byte8 sect2[] =
		{
			0x84, 0xC0,                         // test al,al
			0x0F, 0x84, 0x00, 0x00, 0x00, 0x00, // je dmc3.exe+1E7926
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(DevilButtonCheck, jumpAddr, true, false, 0, sizeof(sect1), (sizeof(sect2) + size));
			CopyMemory(func.sect1, sect1, sizeof(sect1));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
			CopyMemory((func.sect2 + sizeof(sect2)), addr, size, MemoryFlags_VirtualProtectSource);
			WriteAddress((func.sect2 + 2), (appBaseAddr + 0x1E7926), 6);
			WriteAddress((func.sect2 + sizeof(sect2) + 7), (appBaseAddr + 0x1E78BD), 6);
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

	// Activate Devil Disable Flux
	{
		auto addr = (appBaseAddr + 0x1E78A5);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+1E78A5 - E8 161A0100 - call dmc3.exe+1F92C0
		dmc3.exe+1E78AA - B2 01       - mov dl,01
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

	// Activate Devil
	{
		auto addr = (appBaseAddr + 0x1E78AF);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+1E78AF - E8 1C1C0100       - call dmc3.exe+1F94D0
		dmc3.exe+1E78B4 - C6 87 AE3E0000 01 - mov byte ptr [rdi+00003EAE],01
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(ActivateDevil);
		}

		if (enable)
		{
			WriteCall(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Deactivate Devil Disable Flux
	{
		auto addr = (appBaseAddr + 0x1E78C9);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+1E78C9 - E8 F2190100       - call dmc3.exe+1F92C0
		dmc3.exe+1E78CE - 48 8B 87 E83D0000 - mov rax,[rdi+00003DE8]
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

	// Deactivate Devil
	{
		auto addr = (appBaseAddr + 0x1E78E6);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+1E78E6 - E8 E51B0100 - call dmc3.exe+1F94D0
		dmc3.exe+1E78EB - BA 01000000 - mov edx,00000001
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(DeactivateDevil);
		}

		if (enable)
		{
			WriteCall(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Input Update Disable Actor Id Check
	{
		WriteAddress((appBaseAddr + 0x1EBD1E), (enable) ? (appBaseAddr + 0x1EBD24) : (appBaseAddr + 0x1EBDBF), 6);
		/*
		dmc3.exe+1EBD1E - 0F85 9B000000 - jne dmc3.exe+1EBDBF
		dmc3.exe+1EBD24 - 33 D2         - xor edx,edx
		*/
	}

	// Input Update
	{
		auto addr     = (appBaseAddr + 0x1EBD2D);
		auto jumpAddr = (appBaseAddr + 0x1EBD32);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+1EBD2D - E8 3E0F1400 - call dmc3.exe+32CC70
		dmc3.exe+1EBD32 - 33 D2       - xor edx,edx
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x0F, 0xB6, 0x93, 0x00, 0x00, 0x00, 0x00, // movzx edx,byte ptr [rbx+0000B8C0]
			0xE8, 0x00, 0x00, 0x00, 0x00,             // call dmc3.exe+32CC70
			0x66, 0x23, 0x83, 0x00, 0x00, 0x00, 0x00, // and ax,[rbx+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(func.sect0 + 3) = offsetof(PlayerActorData, newGamepad);
			WriteCall((func.sect0 + 7), (appBaseAddr + 0x32CC70));
			*reinterpret_cast<uint32 *>(func.sect0 + 0xF) = offsetof(PlayerActorData, newButtonMask);
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

	// Input Update 2
	{
		auto addr     = (appBaseAddr + 0x1EBD42);
		auto jumpAddr = (appBaseAddr + 0x1EBD47);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+1EBD42 - E8 390F1400      - call dmc3.exe+32CC80
		dmc3.exe+1EBD47 - 0FB7 93 E0740000 - movzx edx,word ptr [rbx+000074E0]
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x0F, 0xB6, 0x93, 0x00, 0x00, 0x00, 0x00, // movzx edx,byte ptr [rbx+0000B8C0]
			0xE8, 0x00, 0x00, 0x00, 0x00,             // call dmc3.exe+32CC80
			0x66, 0x23, 0x83, 0x00, 0x00, 0x00, 0x00, // and ax,[rbx+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(func.sect0 + 3) = offsetof(PlayerActorData, newGamepad);
			WriteCall((func.sect0 + 7), (appBaseAddr + 0x32CC80));
			*reinterpret_cast<uint32 *>(func.sect0 + 0xF) = offsetof(PlayerActorData, newButtonMask);
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

	// Input Update 3
	{
		auto addr     = (appBaseAddr + 0x1EBD64);
		auto jumpAddr = (appBaseAddr + 0x1EBD6B);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1EBD64 - 66 89 8B E4740000 - mov [rbx+000074E4],cx
		dmc3.exe+1EBD6B - 66 23 D0          - and dx,ax
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x66, 0x23, 0x8B, 0x00, 0x00, 0x00, 0x00, //and cx,[rbx+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, (sizeof(sect0) + size));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			CopyMemory((func.sect0 + sizeof(sect0)), addr, size, MemoryFlags_VirtualProtectSource);
			*reinterpret_cast<uint32 *>(func.sect0 + 3) = offsetof(PlayerActorData, newButtonMask);
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

	// Input Update 4
	{
		auto addr     = (appBaseAddr + 0x1EBD75);
		auto jumpAddr = (appBaseAddr + 0x1EBD7C);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1EBD75 - 66 89 93 E6740000 - mov [rbx+000074E6],dx
		dmc3.exe+1EBD7C - 33 D2             - xor edx,edx
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x66, 0x23, 0x93, 0x00, 0x00, 0x00, 0x00, //and dx,[rbx+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, (sizeof(sect0) + size));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			CopyMemory((func.sect0 + sizeof(sect0)), addr, size, MemoryFlags_VirtualProtectSource);
			*reinterpret_cast<uint32 *>(func.sect0 + 3) = offsetof(PlayerActorData, newButtonMask);
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

	// Input Update 5
	{
		auto addr     = (appBaseAddr + 0x1EBD7E);
		auto jumpAddr = (appBaseAddr + 0x1EBD83);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+1EBD7E - E8 8D0E1400 - call dmc3.exe+32CC10
		dmc3.exe+1EBD83 - 33 D2       - xor edx,edx
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x0F, 0xB6, 0x93, 0x00, 0x00, 0x00, 0x00, // movzx edx,byte ptr [rbx+0000B8C0]
			0xE8, 0x00, 0x00, 0x00, 0x00,             // call dmc3.exe+32CC10
			0x80, 0xBB, 0x00, 0x00, 0x00, 0x00, 0x01, // cmp byte ptr [rbx+0000B8C0],01
			0x74, 0x03,                               // je short
			0x66, 0x31, 0xC0,                         // xor ax,ax
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(func.sect0 + 3) = offsetof(PlayerActorData, newGamepad);
			WriteCall((func.sect0 + 7), (appBaseAddr + 0x32CC10));
			*reinterpret_cast<uint32 *>(func.sect0 + 0xE) = offsetof(PlayerActorData, newEnableRightStick);
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

	// Input Update 6
	{
		auto addr     = (appBaseAddr + 0x1EBD97);
		auto jumpAddr = (appBaseAddr + 0x1EBD9C);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+1EBD97 - E8 740E1400 - call dmc3.exe+32CC10
		dmc3.exe+1EBD9C - 45 33 C0    - xor r8d,r8d
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x0F, 0xB6, 0x93, 0x00, 0x00, 0x00, 0x00, // movzx edx,byte ptr [rbx+0000B8C0]
			0xE8, 0x00, 0x00, 0x00, 0x00,             // call dmc3.exe+32CC10
			0x80, 0xBB, 0x00, 0x00, 0x00, 0x00, 0x01, // cmp byte ptr [rbx+0000B8C0],01
			0x74, 0x03,                               // je short
			0x66, 0x31, 0xC0,                         // xor ax,ax
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(func.sect0 + 3) = offsetof(PlayerActorData, newGamepad);
			WriteCall((func.sect0 + 7), (appBaseAddr + 0x32CC10));
			*reinterpret_cast<uint32 *>(func.sect0 + 0xE) = offsetof(PlayerActorData, newEnableLeftStick);
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

	// Input Update 7
	{
		auto addr     = (appBaseAddr + 0x1EBDAF);
		auto jumpAddr = (appBaseAddr + 0x1EBDB4);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+1EBDAF - E8 9C0E1400 - call dmc3.exe+32CC50
		dmc3.exe+1EBDB4 - 33 D2       - xor edx,edx
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x0F, 0xB6, 0x93, 0x00, 0x00, 0x00, 0x00, // movzx edx,byte ptr [rbx+0000B8C0]
			0xE8, 0x00, 0x00, 0x00, 0x00,             // call dmc3.exe+32CC50
			0x80, 0xBB, 0x00, 0x00, 0x00, 0x00, 0x01, // cmp byte ptr [rbx+0000B8C0],01
			0x74, 0x03,                               // je short
			0x66, 0x31, 0xC0,                         // xor ax,ax
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(func.sect0 + 3) = offsetof(PlayerActorData, newGamepad);
			WriteCall((func.sect0 + 7), (appBaseAddr + 0x32CC50));
			*reinterpret_cast<uint32 *>(func.sect0 + 0xE) = offsetof(PlayerActorData, newEnableRightStick);
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

	// Input Update 8
	{
		auto addr     = (appBaseAddr + 0x1EBE98);
		auto jumpAddr = (appBaseAddr + 0x1EBE9D);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+1EBE98 - E8 B30D1400       - call dmc3.exe+32CC50
		dmc3.exe+1EBE9D - 66 89 83 0A750000 - mov [rbx+0000750A],ax
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x0F, 0xB6, 0x93, 0x00, 0x00, 0x00, 0x00, // movzx edx,byte ptr [rbx+0000B8C0]
			0xE8, 0x00, 0x00, 0x00, 0x00,             // call dmc3.exe+32CC50
			0x80, 0xBB, 0x00, 0x00, 0x00, 0x00, 0x01, // cmp byte ptr [rbx+0000B8C0],01
			0x74, 0x03,                               // je short
			0x66, 0x31, 0xC0,                         // xor ax,ax
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(func.sect0 + 3) = offsetof(PlayerActorData, newGamepad);
			WriteCall((func.sect0 + 7), (appBaseAddr + 0x32CC50));
			*reinterpret_cast<uint32 *>(func.sect0 + 0xE) = offsetof(PlayerActorData, newEnableLeftStick);
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

	// Extend Input Loop
	{
		WriteAddress((appBaseAddr + 0x32D0AA), (enable) ? (appBaseAddr + 0x32D0B0) : (appBaseAddr + 0x32D346), 6);
		/*
		dmc3.exe+32D0AA - 0F85 96020000  - jne dmc3.exe+32D346
		dmc3.exe+32D0B0 - 4C 8D 44 24 38 - lea r8,[rsp+38]
		*/
	}

	// Extend Input Loop 2
	{
		Write<uint8>((appBaseAddr + 0x2AF8F + 2), (enable) ? 3 : 1);
		/*
		dmc3.exe+2AF8F - 83 F9 01 - cmp ecx,01
		dmc3.exe+2AF92 - 76 11    - jna dmc3.exe+2AFA5
		*/
	}

	// Extend Input Loop 3
	{
		auto addr     = (appBaseAddr + 0x2AFA5);
		auto jumpAddr = (appBaseAddr + 0x2AFC6);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+2AFA5 - E8 26FDFFFF - call dmc3.exe+2ACD0
		dmc3.exe+2AFC6 - 49 6B C8 2C - imul rcx,r8,2C
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0xE8, 0x00, 0x00, 0x00, 0x00, // call dmc3.exe+2ACD0
			0x44, 0x8B, 0xC7,             // mov r8d,edi
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall(func.sect0, (appBaseAddr + 0x2ACD0));
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

	// Extend Input Loop 4
	{
		Write<byte32>((appBaseAddr + 0x32CFB6 + 3), (enable) ? 0x63C : 0x624);
		/*
		dmc3.exe+32CFB6 - 48 81 FE 24060000 - cmp rsi,00000624
		dmc3.exe+32CFBD - 0F8C 7DFEFFFF     - jl dmc3.exe+32CE40
		*/
	}



	




	// New Reset Lock-On
	{
		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x4C, 0x8D, 0x81, 0xC0, 0x41, 0x00, 0x00, // lea r8,[rcx+000041C0]
			0x41, 0xB9, 0xFF, 0x00, 0x00, 0x00,       // mov r9d,000000FF
			0xBA, 0x01, 0x00, 0x00, 0x00,             // mov edx,00000001
			0x45, 0x33, 0xDB,                         // xor r11d,r11d
			0x49, 0x8D, 0x40, 0x10,                   // lea rax,[r8+10]
			0x4D, 0x89, 0x98, 0x10, 0x10, 0x00, 0x00, // mov [r8+00001010],r11
			0x49, 0x89, 0x80, 0x18, 0x10, 0x00, 0x00, // mov [r8+00001018],rax
			0x49, 0x8D, 0x40, 0x18,                   // lea rax,[r8+18]
			0x90,                                     // nop
			0x90,                                     // nop
			0x90,                                     // nop
			0x90,                                     // nop
			0x90,                                     // nop
			0x48, 0x63, 0xCA,                         // movsxd  rcx,edx
			0x48, 0x8D, 0x40, 0x10,                   // lea rax,[rax+10]
			0x48, 0xC1, 0xE1, 0x04,                   // shl rcx,04
			0xFF, 0xC2,                               // inc edx
			0x48, 0x83, 0xC1, 0x10,                   // add rcx,10
			0x49, 0x03, 0xC8,                         // add rcx,r8
			0x48, 0x89, 0x48, 0xF0,                   // mov [rax-10],rcx
			0x49, 0x83, 0xE9, 0x01,                   // sub r9,01
			0x75, 0xE2,                               // jne short
			0x4D, 0x89, 0x98, 0x08, 0x10, 0x00, 0x00, // mov [r8+00001008],r11
			0x45, 0x89, 0x98, 0x48, 0x20, 0x00, 0x00, // mov [r8+00002048],r11d
			0xC3,                                     // ret
		};

		if (!run)
		{
			//backupHelper.Save(addr, size);
			func = old_CreateFunction(0, 0, false, true, sizeof(sect0), 0, 0, 0, 0, true);
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			ResetLockOn = reinterpret_cast<ResetLockOn_t>(func.addr);
		}

		// if (enable)
		// {
		// 	WriteJump(addr, func.addr, (size - 5));
		// }
		// else
		// {
		// 	backupHelper.Restore(addr);
		// }
	}


	// // Old Reset Lock-On
	// {
	// 	static Function func = {};

	// 	constexpr byte8 sect0[] =
	// 	{
	// 		0x41, 0xB9, 0xFF, 0x00, 0x00, 0x00,       // mov r9d,000000FF
	// 		0x4C, 0x8D, 0x81, 0xC8, 0x41, 0x00, 0x00, // lea r8,[rcx+000041C8]
	// 		0xBA, 0x01, 0x00, 0x00, 0x00,             // mov edx,00000001
	// 		0x45, 0x33, 0xDB,                         // xor r11d,r11d
	// 		0x49, 0x8D, 0x40, 0x08,                   // lea rax,[r8+08]
	// 		0x4D, 0x89, 0x98, 0x08, 0x10, 0x00, 0x00, // mov [r8+00001008],r11
	// 		0x49, 0x89, 0x80, 0x10, 0x10, 0x00, 0x00, // mov [r8+00001010],rax
	// 		0x49, 0x8D, 0x40, 0x10,                   // lea rax,[r8+10]
	// 		0x48, 0x63, 0xCA,                         // movsxd rcx,edx
	// 		0x48, 0x8D, 0x40, 0x10,                   // lea rax,[rax+10]
	// 		0x48, 0xC1, 0xE1, 0x04,                   // shl rcx,04
	// 		0xFF, 0xC2,                               // inc edx
	// 		0x48, 0x83, 0xC1, 0x08,                   // add rcx,08
	// 		0x49, 0x03, 0xC8,                         // add rcx,r8
	// 		0x48, 0x89, 0x48, 0xF0,                   // mov [rax-10],rcx
	// 		0x49, 0x83, 0xE9, 0x01,                   // sub r9,01
	// 		0x75, 0xE2,                               // jne short
	// 		0x4D, 0x89, 0x98, 0x00, 0x10, 0x00, 0x00, // mov [r8+00001000],r11
	// 		0x45, 0x89, 0x98, 0x40, 0x20, 0x00, 0x00, // mov [r8+00002040],r11d
	// 		0xC3,                                     // ret
	// 	};

	// 	if (!run)
	// 	{
	// 		func = old_CreateFunction(0, 0, false, true, sizeof(sect0), 0, 0, 0, 0, true);
	// 		CopyMemory(func.sect0, sect0, sizeof(sect0));
	// 		ResetLockOn = reinterpret_cast<ResetLockOn_t>(func.addr);
	// 	}
	// }

	// Reset Lock-On 2
	{
		auto addr     = (appBaseAddr + 0x1F8408);
		auto jumpAddr = (appBaseAddr + 0x1F840D);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+1F8408 - E8 5321FCFF         - call dmc3.exe+1BA560
		dmc3.exe+1F840D - 44 0FB6 87 18010000 - movzx r8d,byte ptr [rdi+00000118]
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			mov_rcx_rdi,
			call,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 3), ResetLockOn);
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

	// Reset Lock-On 3
	{
		auto addr     = (appBaseAddr + 0x1F90CB);
		auto jumpAddr = (appBaseAddr + 0x1F90D0);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+1F90CB - E8 9014FCFF      - call dmc3.exe+1BA560
		dmc3.exe+1F90D0 - 0FBF 87 C0000000 - movsx eax,word ptr [rdi+000000C0]
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			mov_rcx_rdi,
			call,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 3), ResetLockOn);
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



	#if g_enableLockOnFixes




	// New Update Lock-On
	{
		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x53,                                     // push rbx
			0x48, 0x8B, 0xDA,                         // mov rbx,rdx
			0xFF, 0x81, 0x08, 0x62, 0x00, 0x00,       // inc [rcx+00006208]
			0x48, 0x8B, 0x91, 0xD8, 0x51, 0x00, 0x00, // mov rdx,[rcx+000051D8]
			0x48, 0x85, 0xD2,                         // test rdx,rdx
			0x74, 0x20,                               // je short
			0x48, 0x8B, 0x42, 0x08,                   // mov rax,[rdx+08]
			0x48, 0x89, 0x81, 0xD8, 0x51, 0x00, 0x00, // mov [rcx+000051D8],rax
			0x48, 0x89, 0x1A,                         // mov [rdx],rbx
			0x48, 0x8B, 0x81, 0xD0, 0x51, 0x00, 0x00, // mov rax,[rcx+000051D0]
			0x48, 0x89, 0x42, 0x08,                   // mov [rdx+08],rax
			0x48, 0x89, 0x91, 0xD0, 0x51, 0x00, 0x00, // mov [rcx+000051D0],rdx
			0x5B,                                     // pop rbx
			0xC3,                                     // ret
		};

		if (!run)
		{
			func = old_CreateFunction(0, 0, false, true, sizeof(sect0), 0, 0, 0, 0, true);
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			UpdateLockOn = reinterpret_cast<UpdateLockOn_t>(func.addr);
		}
	}




{
	auto addr     = (appBaseAddr + 0x1BB77C);
	auto jumpAddr = (appBaseAddr + 0x1BB781);
	constexpr uint64 size = 5;
	/*
	dmc3.exe+1BB77C - 48 8B 5C 24 30 - mov rbx,[rsp+30]
	dmc3.exe+1BB781 - 48 83 C4 20    - add rsp,20
	*/

	static Function func = {};

	constexpr byte8 sect1[] =
	{
		mov_rcx_rbx,
	};

	if (!run)
	{
		backupHelper.Save(addr, size);
		func = old_CreateFunction(UpdateLockOns, jumpAddr, true, true, 0, sizeof(sect1), size);
		CopyMemory(func.sect1, sect1, sizeof(sect1));
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

{
	auto addr     = (appBaseAddr + 0x1BB789);
	auto jumpAddr = (appBaseAddr + 0x1BB78E);
	constexpr uint64 size = 5;
	/*
	dmc3.exe+1BB789 - 48 8B 5C 24 30 - mov rbx,[rsp+30]
	dmc3.exe+1BB78E - 48 83 C4 20    - add rsp,20
	*/

	static Function func = {};

	constexpr byte8 sect1[] =
	{
		mov_rcx_rbx,
	};

	if (!run)
	{
		backupHelper.Save(addr, size);
		func = old_CreateFunction(UpdateLockOns, jumpAddr, true, true, 0, sizeof(sect1), size);
		CopyMemory(func.sect1, sect1, sizeof(sect1));
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

















	// // Old Update Lock-On
	// {
	// 	static Function func = {};

	// 	constexpr byte8 sect0[] =
	// 	{
	// 		0x53,                                     // push rbx
	// 		0x48, 0x8B, 0xDA,                         // mov rbx,rdx
	// 		0xFF, 0x81, 0x08, 0x62, 0x00, 0x00,       // inc [rcx+00006208]
	// 		0x48, 0x8B, 0x91, 0xD8, 0x51, 0x00, 0x00, // mov rdx,[rcx+000051D8]
	// 		0x48, 0x85, 0xD2,                         // test rdx,rdx
	// 		0x74, 0x24,                               // je short
	// 		0x48, 0x8B, 0x42, 0x08,                   // mov rax,[rdx+08]
	// 		0x48, 0x89, 0x81, 0xD8, 0x51, 0x00, 0x00, // mov [rcx+000051D8],rax
	// 		0x48, 0x89, 0x1A,                         // mov [rdx],rbx
	// 		0x48, 0x8B, 0x81, 0xD0, 0x51, 0x00, 0x00, // mov rax,[rcx+000051D0]
	// 		0x48, 0x89, 0x42, 0x08,                   // mov [rdx+08],rax
	// 		0x48, 0x89, 0x91, 0xD0, 0x51, 0x00, 0x00, // mov [rcx+000051D0],rdx
	// 		0xB0, 0x01,                               // mov al,01
	// 		0x5B,                                     // pop rbx
	// 		0xC3,                                     // ret
	// 		0x30, 0xC0,                               // xor al,al
	// 		0x5B,                                     // pop rbx
	// 		0xC3,                                     // ret
	// 	};

	// 	if (!run)
	// 	{
	// 		func = old_CreateFunction(0, 0, false, false, sizeof(sect0), 0, 0, 0, 0, true);
	// 		CopyMemory(func.sect0, sect0, sizeof(sect0));
	// 		UpdateLockOn = reinterpret_cast<UpdateLockOn_t>(func.addr);
	// 	}
	// }

	// // Old Update Lock-On 2
	// {
	// 	auto addr     = (appBaseAddr + 0x1BB6FC);
	// 	auto jumpAddr = (appBaseAddr + 0x1BB706);
	// 	constexpr uint32 size = 10;
	// 	/*
	// 	dmc3.exe+1BB6FC - 48 8B 47 18    - mov rax,[rdi+18]
	// 	dmc3.exe+1BB700 - FF 80 08620000 - inc [rax+00006208]
	// 	dmc3.exe+1BB706 - 48 8B 47 20    - mov rax,[rdi+20]
	// 	*/

	// 	static Function func = {};

	// 	constexpr byte8 sect1[] =
	// 	{
	// 		mov_rcx_rbx,
	// 	};

	// 	if (!run)
	// 	{
	// 		backupHelper.Save(addr, size);
	// 		func = old_CreateFunction(UpdateLockOns, jumpAddr, true, true, 0, sizeof(sect1), size);
	// 		CopyMemory(func.sect1, sect1, sizeof(sect1));
	// 		CopyMemory(func.sect2, addr, size, MemoryFlags_VirtualProtectSource);
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

	#endif








	// Dot Shadow Check
	{
		auto addr     = (appBaseAddr + 0x93D60);
		auto jumpAddr = (appBaseAddr + 0x93D66);
		constexpr uint32 size = 6;
		/*
		dmc3.exe+93D60 - 40 53       - push rbx
		dmc3.exe+93D62 - 48 83 EC 20 - sub rsp,20
		dmc3.exe+93D66 - 48 8B D9    - mov rbx,rcx
		*/

		static Function func = {};

		constexpr byte8 sect2[] =
		{
			0x84, 0xC0, // test al,al
			0x74, 0x01, // je short
			0xC3,       // ret
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(DotShadowCheck, jumpAddr, true, false, 0, 0, (sizeof(sect2) + size));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
			CopyMemory((func.sect2 + sizeof(sect2)), addr, size, MemoryFlags_VirtualProtectSource);
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














	// Reset Visibility Air Trick Dante
	{
		auto addr     = (appBaseAddr + 0x1F1F2C);
		auto jumpAddr = (appBaseAddr + 0x1F1F32);
		constexpr uint32 size = 6;
		/*
		dmc3.exe+1F1F2C - 89 8F 20010000 - mov [rdi+00000120],ecx
		dmc3.exe+1F1F32 - 48 8B CF       - mov rcx,rdi
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rdi,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(ResetVisibility, jumpAddr, true, true, size, sizeof(sect1));
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

	// Reset Visibility Air Trick Vergil, Trick Up & Trick Down
	{
		auto addr     = (appBaseAddr + 0x1F071E);
		auto jumpAddr = (appBaseAddr + 0x1F0724);
		constexpr uint32 size = 6;
		/*
		dmc3.exe+1F071E - 89 BB 20010000    - mov [rbx+00000120],edi
		dmc3.exe+1F0724 - 66 39 BB 1A3E0000 - cmp [rbx+00003E1A],di
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(ResetVisibility, jumpAddr, true, true, size, sizeof(sect1));
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













	// Play Quicksilver Motion
	{
		auto addr     = (appBaseAddr + 0x1F63B2);
		auto jumpAddr = (appBaseAddr + 0x1F63B7);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+1F63B2 - E8 D997FFFF - call dmc3.exe+1EFB90
		dmc3.exe+1F63B7 - BA 01000000 - mov edx,00000001
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(PlayQuicksilverMotion, jumpAddr);
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

	// Play Quicksilver Motion 2
	{
		auto addr     = (appBaseAddr + 0x1F63D6);
		auto jumpAddr = (appBaseAddr + 0x1F63DB);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+1F63D6 - E8 B597FFFF    - call dmc3.exe+1EFB90
		dmc3.exe+1F63DB - FE 83 103E0000 - inc byte ptr [rbx+00003E10]
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(PlayQuicksilverMotion, jumpAddr);
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

	// Disable Set Style Data
	{
		auto addr = (appBaseAddr + 0x2BAA90);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+2BAA90 - 48 89 91 103D0000 - mov [rcx+00003D10],rdx
		dmc3.exe+2BAA97 - C3                - ret
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


	#pragma region Mostly Air Stinger Stuff


	// Set Action Melee Attack
	{
		auto addr     = (appBaseAddr + 0x1E6D8A);
		auto jumpAddr = (appBaseAddr + 0x1E6D90);
		constexpr uint32 size = 6;
		/*
		dmc3.exe+1E6D8A - 88 83 A43F0000    - mov [rbx+00003FA4],al
		dmc3.exe+1E6D90 - 48 63 83 90640000 - movsxd  rax,dword ptr [rbx+00006490]
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(SetAction, jumpAddr, true, true, size, sizeof(sect1));
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

	// Set Action Style Attack
	{
		auto addr     = (appBaseAddr + 0x1E65CF);
		auto jumpAddr = (appBaseAddr + 0x1E65D5);
		constexpr uint32 size = 6;
		/*
		dmc3.exe+1E65CF - 88 83 A43F0000 - mov [rbx+00003FA4],al
		dmc3.exe+1E65D5 - 41 8D 51 12    - lea edx,[r9+12]
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(SetAction, jumpAddr, true, true, size, sizeof(sect1));
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

	// Set Action Lock-On
	{
		auto addr     = (appBaseAddr + 0x1E699C);
		auto jumpAddr = (appBaseAddr + 0x1E69A2);
		constexpr uint32 size = 6;
		/*
		dmc3.exe+1E699C - 88 83 A43F0000 - mov [rbx+00003FA4],al
		dmc3.exe+1E69A2 - 0FB6 4F 13     - movzx ecx,byte ptr [rdi+13]
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(SetAction, jumpAddr, true, true, size, sizeof(sect1));
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

	// Get Rebellion Stinger Duration
	{
		auto addr     = (appBaseAddr + 0x20932C);
		auto jumpAddr = (appBaseAddr + 0x209331);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+20932C - F3 0F10 48 28       - movss xmm1,[rax+28]
		dmc3.exe+209331 - F3 0F11 8F 343E0000 - movss [rdi+00003E34],xmm1
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rdi,
		};
		constexpr byte8 sect2[] =
		{
			0xF3, 0x0F, 0x10, 0x08, // movss xmm1,[rax]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(GetRebellionStingerDuration, jumpAddr, true, false, 0, sizeof(sect1), sizeof(sect2));
			CopyMemory(func.sect1, sect1, sizeof(sect1));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
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

	// Get Rebellion Stinger Range
	{
		auto addr     = (appBaseAddr + 0x209340);
		auto jumpAddr = (appBaseAddr + 0x209345);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+209340 - F3 0F10 40 2C - movss xmm0,[rax+2C]
		dmc3.exe+209345 - F3 0F5E C1    - divss xmm0,xmm1
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rdi,
		};
		constexpr byte8 sect2[] =
		{
			0xF3, 0x0F, 0x10, 0x00, // movss xmm0,[rax]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(GetRebellionStingerRange, jumpAddr, true, false, 0, sizeof(sect1), sizeof(sect2));
			CopyMemory(func.sect1, sect1, sizeof(sect1));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
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

	// Air Stinger Dante
	{
		auto addr     = (appBaseAddr + 0x209199);
		auto jumpAddr = (appBaseAddr + 0x2091A0);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+209199 - C6 87 2A3E0000 00 - mov byte ptr [rdi+00003E2A],00
		dmc3.exe+2091A0 - 48 8B CF          - mov rcx,rdi
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0xF6, 0x87, 0x64, 0x3E, 0x00, 0x00, 0x02,                   // test byte ptr [rdi+00003E64],02
			0x74, 0x0A,                                                 // je short
			0xC7, 0x87, 0x60, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov [rdi+00003E60]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, (size + sizeof(sect0)));
			CopyMemory(func.sect0, addr, size, MemoryFlags_VirtualProtectSource);
			CopyMemory((func.sect0 + size), sect0, sizeof(sect0));
			*reinterpret_cast<byte32 *>(func.sect0 + size + 0xF) = 0xC08;
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

	// Air Stinger Dante 2
	{
		auto addr     = (appBaseAddr + 0x209459);
		auto jumpAddr = (appBaseAddr + 0x209462);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+209459 - 80 BF 2A3E0000 01 - cmp byte ptr [rdi+00003E2A],01
		dmc3.exe+209460 - 75 45             - jne dmc3.exe+2094A7
		dmc3.exe+209462 - 0FB7 97 C0000000  - movzx edx,word ptr [rdi+000000C0]
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0xF6, 0x87, 0x64, 0x3E, 0x00, 0x00, 0x02, // test byte ptr [rdi+00003E64],02
			0x0F, 0x85, 0x00, 0x00, 0x00, 0x00,       // jne dmc3.exe+2094A7
			0x80, 0xBF, 0x2A, 0x3E, 0x00, 0x00, 0x01, // cmp byte ptr [rdi+00003E2A],01
			0x0F, 0x85, 0x00, 0x00, 0x00, 0x00,       // jne dmc3.exe+2094A7
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteAddress((func.sect0 + 7), (appBaseAddr + 0x2094A7), 6);
			WriteAddress((func.sect0 + 0x14), (appBaseAddr + 0x2094A7), 6);
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

	// Get Yamato Judgement Cut Count
	{
		auto addr     = (appBaseAddr + 0x21C94E);
		auto jumpAddr = (appBaseAddr + 0x21C95D);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+21C94E - 48 8B 83 F83D0000   - mov rax,[rbx+00003DF8]
		dmc3.exe+21C955 - F3 0F2C 88 88010000 - cvttss2si ecx,[rax+00000188]
		dmc3.exe+21C95D - 66 39 8B 1A3E0000   - cmp [rbx+00003E1A],cx
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};
		constexpr byte8 sect2[] =
		{
			mov_ecx_eax,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(GetYamatoJudgementCutCount, jumpAddr, true, false, 0, sizeof(sect1), sizeof(sect2));
			CopyMemory(func.sect1, sect1, sizeof(sect1));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
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

	// Get Yamato & Force Edge Stinger Duration
	{
		auto addr     = (appBaseAddr + 0x21F69E);
		auto jumpAddr = (appBaseAddr + 0x21F6A6);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+21F69E - F3 0F10 88 9C000000 - movss xmm1,[rax+0000009C]
		dmc3.exe+21F6A6 - F3 0F11 8F 343E0000 - movss [rdi+00003E34],xmm1
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rdi,
		};
		constexpr byte8 sect2[] =
		{
			0xF3, 0x0F, 0x10, 0x08, // movss xmm1,[rax]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(GetYamatoForceEdgeStingerDuration, jumpAddr, true, false, 0, sizeof(sect1), sizeof(sect2));
			CopyMemory(func.sect1, sect1, sizeof(sect1));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
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

	// Get Yamato & Force Edge Stinger Range
	{
		auto addr     = (appBaseAddr + 0x21F6B5);
		auto jumpAddr = (appBaseAddr + 0x21F6BD);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+21F6B5 - F3 0F10 80 A0000000 - movss xmm0,[rax+000000A0]
		dmc3.exe+21F6BD - F3 0F5E C1          - divss xmm0,xmm1
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rdi,
		};
		constexpr byte8 sect2[] =
		{
			0xF3, 0x0F, 0x10, 0x00, // movss xmm0,[rax]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(GetYamatoForceEdgeStingerRange, jumpAddr, true, false, 0, sizeof(sect1), sizeof(sect2));
			CopyMemory(func.sect1, sect1, sizeof(sect1));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
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

	// Air Stinger Vergil
	{
		auto addr     = (appBaseAddr + 0x21F555);
		auto jumpAddr = (appBaseAddr + 0x21F55C);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+21F555 - C6 87 2A3E0000 00 - mov byte ptr [rdi+00003E2A],00
		dmc3.exe+21F55C - 48 8B CF          - mov rcx,rdi
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0xF6, 0x87, 0x64, 0x3E, 0x00, 0x00, 0x02,                   // test byte ptr [rdi+00003E64],02
			0x74, 0x0A,                                                 // je short
			0xC7, 0x87, 0x60, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov [rdi+00003E60],00000000
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, (size + sizeof(sect0)));
			CopyMemory(func.sect0, addr, size, MemoryFlags_VirtualProtectSource);
			CopyMemory((func.sect0 + size), sect0, sizeof(sect0));
			*reinterpret_cast<byte32 *>(func.sect0 + size + 0xF) = 0xC08;
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

	// Air Stinger Vergil 2
	{
		auto addr     = (appBaseAddr + 0x21F7CA);
		auto jumpAddr = (appBaseAddr + 0x21F7DD);
		constexpr uint32 size = 7;
		auto addr2 = (appBaseAddr + 0x21F7D1);
		constexpr uint32 size2 = 10;
		/*
		dmc3.exe+21F7CA - 80 BF 2A3E0000 01 - cmp byte ptr [rdi+00003E2A],01
		dmc3.exe+21F7D1 - 0F28 7C 24 40     - movaps xmm7,[rsp+40]
		dmc3.exe+21F7D6 - 0F28 74 24 50     - movaps xmm6,[rsp+50]
		dmc3.exe+21F7DB - 75 4A             - jne dmc3.exe+21F827
		dmc3.exe+21F7DD - 0FB7 97 C0000000  - movzx edx,word ptr [rdi+000000C0]
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0xF6, 0x87, 0x64, 0x3E, 0x00, 0x00, 0x02, // test byte ptr [rdi+00003E64],02
			0x0F, 0x85, 0x00, 0x00, 0x00, 0x00,       // jne dmc3.exe+21F827
			0x80, 0xBF, 0x2A, 0x3E, 0x00, 0x00, 0x01, // cmp byte ptr [rdi+00003E2A],01
			0x0F, 0x85, 0x00, 0x00, 0x00, 0x00,       // jne dmc3.exe+21F827
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, (size2 + sizeof(sect0)));
			CopyMemory(func.sect0, addr2, size2, MemoryFlags_VirtualProtectSource);
			CopyMemory((func.sect0 + size2), sect0, sizeof(sect0));
			WriteAddress((func.sect0 + size2 + 7), (appBaseAddr + 0x21F827), 6);
			WriteAddress((func.sect0 + size2 + 0x14), (appBaseAddr + 0x21F827), 6);
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

	// EndActionLedge
	{
		auto addr     = (appBaseAddr + 0x1E7BF2);
		auto jumpAddr = (appBaseAddr + 0x1E7BF7);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+1E7BF2 - E8 A981FFFF - call dmc3.exe+1DFDA0
		dmc3.exe+1E7BF7 - B0 01       - mov al,01
		*/

		static Function func = {};

		constexpr byte8 sect2[] =
		{
			0x84, 0xC0,                   // test al,al
			0x75, 0x05,                   // jne short
			0xE8, 0x00, 0x00, 0x00, 0x00, // call dmc3.exe+1DFDA0
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(EndActionLedge, jumpAddr, true, false, 0, 0, sizeof(sect2));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
			WriteCall((func.sect2 + 4), (appBaseAddr + 0x1DFDA0));
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

	// Decrease Altitude
	{
		auto addr     = (appBaseAddr + 0x1F9189);
		auto jumpAddr = (appBaseAddr + 0x1F9191);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+1F9189 - F3 0F5C 05 AFCD2C00 - subss xmm0,[dmc3.exe+4C5F40]
		dmc3.exe+1F9191 - F3 0F11 87 84000000 - movss [rdi+00000084],xmm0
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rdi,
		};
		constexpr byte8 sect2[] =
		{
			0x84, 0xC0, // test al,al
			0x75, 0x08, // jne short
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(DecreaseAltitude, jumpAddr, true, false, 0, sizeof(sect1), (sizeof(sect2) + size));
			CopyMemory(func.sect1, sect1, sizeof(sect1));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
			CopyMemory((func.sect2 + sizeof(sect2)), addr, size, MemoryFlags_VirtualProtectSource);
			WriteAddress((func.sect2 + sizeof(sect2)), (appBaseAddr + 0x4C5F40), size);
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

	#pragma endregion



	// Disable Default Free Clone Data
	{
		auto addr = (appBaseAddr + 0x212013);
		constexpr uint32 size = 24;
		/*
		dmc3.exe+212013 - 48 8D 8B 10640000 - lea rcx,[rbx+00006410]
		dmc3.exe+21201A - E8 A1BF0D00       - call dmc3.exe+2EDFC0
		dmc3.exe+21201F - 48 8D 8B 58640000 - lea rcx,[rbx+00006458]
		dmc3.exe+212026 - E8 E5561200       - call dmc3.exe+337710
		dmc3.exe+21202B - 48 8B 8B 78640000 - mov rcx,[rbx+00006478]
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

	ToggleMainActorFixes  (enable);
	ToggleStyleFixes      (enable);
	ToggleIsWeaponReady   (enable);
	ToggleMobility        (enable);
	ToggleColor(enable);
	ToggleSpeed           (enable);
	ToggleFixWeaponShadows(enable);
	Actor::ToggleFixDevilAura    (enable);
	//ToggleSound           (enable);



	// Disable Trigger Customize Menu
	{
		auto addr = (appBaseAddr + 0x1A9619);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+1A9619 - E8 F21B0900 - call dmc3.exe+23B210
		dmc3.exe+1A961E - EB B0       - jmp dmc3.exe+1A95D0
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

	// Save Fix
	{
		auto addr     = (appBaseAddr + 0x32B0DF);
		auto jumpAddr = (appBaseAddr + 0x32B0E6);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+32B0DF - 48 8D 93 6C010000 - lea rdx,[rbx+0000016C]
		dmc3.exe+32B0E6 - 48 8B 01          - mov rax,[rcx]
		*/

		static Function func = {};

		constexpr byte8 sect2[] =
		{
			mov_rcx_rax,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(SaveFix, jumpAddr, true, false, size, 0, sizeof(sect2));
			CopyMemory(func.sect0, addr, size, MemoryFlags_VirtualProtectSource);
			CopyMemory(func.sect2, sect2, sizeof(sect2));
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
































	// Visibility Check
	{
		auto addr     = (appBaseAddr + 0x326890);
		auto jumpAddr = (appBaseAddr + 0x326896);
		constexpr uint32 size = 6;
		/*
		dmc3.exe+326890 - 80 7B 5D 01 - cmp byte ptr [rbx+5D],01
		dmc3.exe+326894 - 75 09       - jne dmc3.exe+32689F
		dmc3.exe+326896 - 48 8B 03    - mov rax,[rbx]
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};
		constexpr byte8 sect2[] =
		{
			0x3C, 0x01,                         // cmp al,01
			0x0F, 0x84, 0x00, 0x00, 0x00, 0x00, // je dmc3.exe+326896
			0x3C, 0x02,                         // cmp al,02
			0x0F, 0x84, 0x00, 0x00, 0x00, 0x00, // je dmc3.exe+32689F
			0x80, 0x7B, 0x5D, 0x01,             // cmp byte ptr [rbx+5D],01
			0x0F, 0x85, 0x00, 0x00, 0x00, 0x00, // jne dmc3.exe+32689F
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(VisibilityCheck, jumpAddr, true, false, 0, sizeof(sect1), sizeof(sect2));
			CopyMemory(func.sect1, sect1, sizeof(sect1));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
			WriteAddress((func.sect2 + 2), (appBaseAddr + 0x326896), 6);
			WriteAddress((func.sect2 + 0xA), (appBaseAddr + 0x32689F), 6);
			WriteAddress((func.sect2 + 0x14), (appBaseAddr + 0x32689F), 6);
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

	// SetVisible
	{
		auto addr     = (appBaseAddr + 0x1F8AEE);
		auto jumpAddr = (appBaseAddr + 0x1F8AF8);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+1F8AEE - C7 87 20010000 01000000 - mov [rdi+00000120],00000001
		dmc3.exe+1F8AF8 - 80 BF 9B3E0000 01       - cmp byte ptr [rdi+00003E9B],01
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rax,
		};
		constexpr byte8 sect1[] =
		{
			mov_rcx_rdi,
		};
		constexpr byte8 sect2[] =
		{
			0x84, 0xC0,                                                 // test al,al
			0x75, 0x0A,                                                 // jne short
			0xC7, 0x87, 0x20, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, // mov [rdi+00000120],00000001
			pop_rax,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(SetVisible, jumpAddr, true, false, sizeof(sect0), sizeof(sect1), sizeof(sect2));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			CopyMemory(func.sect1, sect1, sizeof(sect1));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
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

	// VerticalPullCheck
	{
		auto addr     = (appBaseAddr + 0x1FB3BA);
		auto jumpAddr = (appBaseAddr + 0x1FB3C2);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+1FB3BA - F3 0F58 97 94000000 - addss xmm2,dword ptr [rdi+00000094]
		dmc3.exe+1FB3C2 - 0F2F C2             - comiss xmm0,xmm2
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rdi,
		};
		constexpr byte8 sect2[] =
		{
			0x84, 0xC0,                                     // test al,al
			0x75, 0x08,                                     // jne short
			0xF3, 0x0F, 0x58, 0x97, 0x94, 0x00, 0x00, 0x00, // addss xmm2,dword ptr [rdi+00000094]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(VerticalPullCheck, jumpAddr, true, false, 0, sizeof(sect1), sizeof(sect2));
			CopyMemory(func.sect1, sect1, sizeof(sect1));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
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

	// SetCollisionData
	{
		auto addr     = (appBaseAddr + 0x5C310);
		auto jumpAddr = (appBaseAddr + 0x5C317);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+5C310 - 0F29 81 80020000 - movaps [rcx+00000280],xmm0
		dmc3.exe+5C317 - C3               - ret
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(SetCollisionData, jumpAddr, true, true, size);
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

	// CollisionCheck
	{
		auto addr     = (appBaseAddr + 0x5C320);
		auto jumpAddr = (appBaseAddr + 0x5C325);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+5C320 - 48 89 5C 24 08 - mov [rsp+08],rbx
		dmc3.exe+5C325 - 48 89 74 24 10 - mov [rsp+10],rsi
		*/

		static Function func = {};

		constexpr byte8 sect2[] =
		{
			0x84, 0xC0, // test al,al
			0x74, 0x01, // je short
			0xC3,       // ret
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(CollisionCheck, jumpAddr, true, false, 0, 0, (sizeof(sect2) + size));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
			CopyMemory((func.sect2 + sizeof(sect2)), addr, size, MemoryFlags_VirtualProtectSource);
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

	#pragma region Enemy

	// SetNewEventEnemy
	{
		auto addr     = (appBaseAddr + 0x65880);
		auto jumpAddr = (appBaseAddr + 0x65890);
		constexpr uint32 size = 16;
		/*
		dmc3.exe+65880 - 89 91 F4000000          - mov [rcx+000000F4],edx
		dmc3.exe+65886 - C7 81 F8000000 00000000 - mov [rcx+000000F8],00000000
		dmc3.exe+65890 - C3                      - ret
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(SetNewEventEnemy, jumpAddr, true, true, size);
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

	// SetNewEventBossLady
	{
		auto addr     = (appBaseAddr + 0x16E9F4);
		auto jumpAddr = (appBaseAddr + 0x16EA01);
		constexpr uint32 size = 13;
		/*
		dmc3.exe+16E9F4 - 89 91 08580000    - mov [rcx+00005808],edx
		dmc3.exe+16E9FA - C6 81 14580000 00 - mov byte ptr [rcx+00005814],00
		dmc3.exe+16EA01 - C3                - ret
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			0x48, 0x81, 0xE9, 0x80, 0x01, 0x00, 0x00, // sub rcx,00000180
		};
		/*
		dmc3.exe+171A45 - 48 8D 8B 80010000 - lea rcx,[rbx+00000180]
		dmc3.exe+171A51 - FF 90 58010000    - call qword ptr [rax+00000158]
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(SetNewEventBossLady, jumpAddr, true, true, 0, sizeof(sect1));
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

	// SetNewEventBossVergil
	{
		auto addr     = (appBaseAddr + 0x17F4DC);
		auto jumpAddr = (appBaseAddr + 0x17F4E9);
		constexpr uint32 size = 13;
		/*
		dmc3.exe+17F4DC - 89 B3 F4EB0000    - mov [rbx+0000EBF4],esi
		dmc3.exe+17F4E2 - C6 83 04EC0000 00 - mov byte ptr [rbx+0000EC04],00
		dmc3.exe+17F4E9 - 40 80 FD 01       - cmp bpl,01
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
			0x48, 0x81, 0xE9, 0x80, 0x01, 0x00, 0x00, // sub rcx,00000180
			mov_edx_esi,
		};
		/*
		dmc3.exe+17B7FD - 48 8D 8E 80010000 - lea rcx,[rsi+00000180]
		dmc3.exe+17B80C - FF 90 58010000    - call qword ptr [rax+00000158]
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(SetNewEventBossVergil, jumpAddr, true, true, 0, sizeof(sect1));
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

	// Enemy Get Main Actor Position
	{
		auto addr     = (appBaseAddr + 0x616EB);
		auto jumpAddr = (appBaseAddr + 0x616F2);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+616EB - 0F28 82 80000000 - movaps xmm0,[rdx+00000080]
		dmc3.exe+616F2 - 0F29 41 40       - movaps [rcx+40],xmm0
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			0x48, 0x81, 0xE9, 0x80, 0x01, 0x00, 0x00, // sub rcx,00000180
		};
		constexpr byte8 sect2[] =
		{
			0x84, 0xC0,                               // test al,al
			0x74, 0x09,                               // je short
			0x0F, 0x28, 0x82, 0x00, 0x63, 0x00, 0x00, // movaps xmm0,[rdx+00006300]
			0xEB, 0x07,                               // jmp short
			0x0F, 0x28, 0x82, 0x80, 0x00, 0x00, 0x00, // movaps xmm0,[rdx+00000080]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(BelongsToPlayer, jumpAddr, true, false, 0, sizeof(sect1), sizeof(sect2));
			CopyMemory(func.sect1, sect1, sizeof(sect1));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
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

	// Enemy Update AI Timer
	{
		auto addr     = (appBaseAddr + 0x60DB7);
		auto jumpAddr = (appBaseAddr + 0x60DBC);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+60DB7 - F3 0F58 43 58 - addss xmm0,dword ptr [rbx+58]
		dmc3.exe+60DBC - F3 0F11 43 58 - movss [rbx+58],xmm0
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			0x48, 0x8D, 0x8B, 0x80, 0xFE, 0xFF, 0xFF, // lea rcx,[rbx-00000180]
		};

		constexpr byte8 sect2[] =
		{
			0x84, 0xC0,                   // test al,al
			0x74, 0x05,                   // je short
			0x0F, 0x57, 0xC0,             // xorps xmm0,xmm0
			0xEB, 0x05,                   // jmp short
			0xF3, 0x0F, 0x58, 0x43, 0x58, // addss xmm0,dword ptr [rbx+58]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(BelongsToPlayer, jumpAddr, true, false, 0, sizeof(sect1), sizeof(sect2));
			CopyMemory(func.sect1, sect1, sizeof(sect1));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
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

	#pragma endregion

	#pragma region PVP Fixes

	#if g_enableLockOnFixes

	// SetLockOnTargetPosition
	{
		auto addr     = (appBaseAddr + 0x1BAEBE);
		auto jumpAddr = (appBaseAddr + 0x1BAEC3);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+1BAEBE - 8B 42 30 - mov eax,[rdx+30]
		dmc3.exe+1BAEC1 - 89 06    - mov [rsi],eax
		dmc3.exe+1BAEC3 - 8B 42 34 - mov eax,[rdx+34]
		dmc3.exe+1BAED6 - 48 8B C1 - mov rax,rcx
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rsi,
		};
		constexpr byte8 sect2[] =
		{
			0x84, 0xC0,                         // test al,al
			0x0F, 0x85, 0x00, 0x00, 0x00, 0x00, // jne dmc3.exe+1BAED6
			0x8B, 0x42, 0x30,                   // mov eax,[rdx+30]
			0x89, 0x06,                         // mov [rsi],eax
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(SetLockOnTargetPosition, jumpAddr, true, false, 0, sizeof(sect1), sizeof(sect2));
			CopyMemory(func.sect1, sect1, sizeof(sect1));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
			WriteAddress((func.sect2 + 2), (appBaseAddr + 0x1BAED6), 6);
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

	// SetLockOnTargetPositionGUI
	{
		auto addr     = (appBaseAddr + 0x1BB676);
		auto jumpAddr = (appBaseAddr + 0x1BB67B);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+1BB676 - 8B 41 30          - mov eax,[rcx+30]
		dmc3.exe+1BB679 - 89 02             - mov [rdx],eax
		dmc3.exe+1BB67B - 8B 41 34          - mov eax,[rcx+34]
		dmc3.exe+1BB68E - 48 8B 05 9357AD00 - mov rax,[dmc3.exe+C90E28]
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rdx,
		};
		constexpr byte8 sect2[] =
		{
			0x84, 0xC0,                         // test al,al
			0x0F, 0x85, 0x00, 0x00, 0x00, 0x00, // jne dmc3.exe+1BB68E
			0x8B, 0x41, 0x30,                   // mov eax,[rcx+30]
			0x89, 0x02,                         // mov [rdx],eax
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(SetLockOnTargetPositionGUI, jumpAddr, true, false, 0, sizeof(sect1), sizeof(sect2));
			CopyMemory(func.sect1, sect1, sizeof(sect1));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
			WriteAddress((func.sect2 + 2), (appBaseAddr + 0x1BB68E), 6);
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

	#endif

	// GetHitPoints
	{
		auto addr     = (appBaseAddr + 0x1C20F0);
		auto jumpAddr = (appBaseAddr + 0x1C20F6);
		constexpr uint32 size = 6;
		/*
		dmc3.exe+1C20F0 - 8B 81 FC2D0000 - mov eax,[rcx+00002DFC]
		dmc3.exe+1C20F6 - 89 02          - mov [rdx],eax
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_ecx_eax,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(GetHitPoints, jumpAddr, true, false, size, sizeof(sect1));
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

	// GetMaxHitPoints
	{
		auto addr     = (appBaseAddr + 0x1C2100);
		auto jumpAddr = (appBaseAddr + 0x1C2106);
		constexpr uint32 size = 6;
		/*
		dmc3.exe+1C2100 - 8B 81 CC2D0000 - mov eax,[rcx+00002DCC]
		dmc3.exe+1C2106 - 89 02          - mov [rdx],eax
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_ecx_eax,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(GetMaxHitPoints, jumpAddr, true, false, size, sizeof(sect1));
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

	#pragma endregion

	// PlayMotionRebellionDrive
	{
		auto addr     = (appBaseAddr + 0x21189A);
		auto jumpAddr = (appBaseAddr + 0x21189F);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+21189A - E8 F1E2FDFF       - call dmc3.exe+1EFB90
		dmc3.exe+21189F - 48 8B 86 F83D0000 - mov rax,[rsi+00003DF8]
		*/

		static Function func = {};

		constexpr byte8 sect2[] =
		{
			0x44, 0x8B, 0xC0,             // mov r8d,eax
			0xE8, 0x00, 0x00, 0x00, 0x00, // call dmc3.exe+1EFB90
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(PlayMotionRebellionDrive, jumpAddr, true, false, 0, 0, sizeof(sect2));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
			WriteAddress((func.sect2 + 3), (appBaseAddr + 0x1EFB90), 5);
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



	// Disable Default Set Player Actor Speed
	{
		auto dest = (appBaseAddr + 0x1F8CC0);
		/*
		dmc3.exe+1F8CC0 - C6 05 65A1AF00 01 - mov byte ptr [dmc3.exe+CF2E2C],01
		dmc3.exe+1F8CC7 - 48 8B CF          - mov rcx,rdi
		*/

		{
			auto addr = (appBaseAddr + 0x1F8C2E);
			constexpr uint32 size = 5;
			/*
			dmc3.exe+1F8C2E - E9 85000000       - jmp dmc3.exe+1F8CB8
			dmc3.exe+1F8C33 - 80 BF 9F3E0000 01 - cmp byte ptr [rdi+00003E9F],01
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

		{
			auto addr = (appBaseAddr + 0x1F8C52);
			constexpr uint32 size = 2;
			/*
			dmc3.exe+1F8C52 - EB 64             - jmp dmc3.exe+1F8CB8
			dmc3.exe+1F8C54 - 48 63 87 88640000 - movsxd  rax,dword ptr [rdi+00006488]
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

		{
			auto addr = (appBaseAddr + 0x1F8C65);
			constexpr uint32 size = 2;
			/*
			dmc3.exe+1F8C65 - EB 51             - jmp dmc3.exe+1F8CB8
			dmc3.exe+1F8C67 - 83 BF 943E0000 03 - cmp dword ptr [rdi+00003E94],03
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

		{
			auto addr = (appBaseAddr + 0x1F8CAE);
			constexpr uint32 size = 2;
			/*
			dmc3.exe+1F8CAE - EB 08               - jmp dmc3.exe+1F8CB8
			dmc3.exe+1F8CB0 - F3 0F10 05 40602D00 - movss xmm0,[dmc3.exe+4CECF8]
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

		// @Todo: Move up.
		{
			auto addr = (appBaseAddr + 0x1F8C90);
			constexpr uint32 size = 7;
			/*
			dmc3.exe+1F8C90 - 83 BF 1C010000 01 - cmp dword ptr [rdi+0000011C],01
			dmc3.exe+1F8C97 - 74 2E             - je dmc3.exe+1F8CC7
			*/

			if (!run)
			{
				backupHelper.Save(addr, size);
			}

			if (enable)
			{
				WriteNop(addr, size);
				WriteShortJump(addr, dest);
			}
			else
			{
				backupHelper.Restore(addr);
			}
		}
	}








	run = true;
}

namespaceEnd();

// $ActorToggleEnd






















export void ToggleAirHikeCoreAbility(bool enable)
{
	LogFunction(enable);

	Write<byte8>((appBaseAddr + 0x1E9B0E), (enable) ? 0xEB : 0x74);
	/*
	dmc3.exe+1E9B0E - 74 32    - je dmc3.exe+1E9B42
	dmc3.exe+1E9B10 - 80 F9 02 - cmp cl,02
	*/
}


export void ToggleRoyalguardForceJustFrameRelease(bool enable)
{
	LogFunction(enable);

	static bool run = false;

	// Release
	{
		auto addr = (appBaseAddr + 0x20B714);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+20B714 - C6 83 103E0000 01 - mov byte ptr [rbx+00003E10],01
		dmc3.exe+20B71B - 0F2F BB 30400000  - comiss xmm7,[rbx+00004030]
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			Write<uint32>((addr + 2), offsetof(PlayerActorData, action));
			Write<uint8>((addr + 6), ACTION_DANTE::ROYALGUARD_RELEASE_2);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Air Release
	{
		auto addr = (appBaseAddr + 0x20BCF8);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+20BCF8 - C6 83 103E0000 01 - mov byte ptr [rbx+00003E10],01
		dmc3.exe+20BCFF - 0F2F BB 30400000  - comiss xmm7,[rbx+00004030]
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			Write<uint32>((addr + 2), offsetof(PlayerActorData, action));
			Write<uint8>((addr + 6), ACTION_DANTE::ROYALGUARD_AIR_RELEASE_2);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	run = true;
}










// @Todo: Update.
export void ToggleRebellionInfiniteSwordPierce(bool enable)
{
	LogFunction(enable);

	{
		auto dest = (appBaseAddr + 0x1CC9A4);
		if (enable)
		{
			SetMemory(dest, 0x90, 5, MemoryFlags_VirtualProtectDestination);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0xF3, 0x0F, 0x5C, 0x4B, 0x14, // subss xmm1,[rbx+14]
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+1CC9A4 - F3 0F5C 4B 14 - subss xmm1,[rbx+14]
		dmc3.exe+1CC9A9 - 0F2F C1       - comiss xmm0,xmm1
		*/
	}
	{
		auto dest = (appBaseAddr + 0x1CDA1B);
		if (enable)
		{
			SetMemory(dest, 0x90, 4, MemoryFlags_VirtualProtectDestination);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0xF3, 0x0F, 0x5C, 0xC1, // subss xmm0,xmm1
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+1CDA1B - F3 0F5C C1             - subss xmm0,xmm1
		dmc3.exe+1CDA1F - 44 0F29 9C 24 A0000000 - movaps [rsp+000000A0],xmm11
		*/
	}
	{
		auto dest = (appBaseAddr + 0x1CDD64);
		if (enable)
		{
			SetMemory(dest, 0x90, 5, MemoryFlags_VirtualProtectDestination);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0xF3, 0x0F, 0x5C, 0x4B, 0x14, // subss xmm1,[rbx+14]
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+1CDD64 - F3 0F5C 4B 14 - subss xmm1,[rbx+14]
		dmc3.exe+1CDD69 - 0F2F C1       - comiss xmm0,xmm1
		*/
	}
	{
		auto dest = (appBaseAddr + 0x1CDDCE);
		if (enable)
		{
			SetMemory(dest, 0x90, 4, MemoryFlags_VirtualProtectDestination);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0xF3, 0x0F, 0x5C, 0xCA, // subss xmm1,xmm2
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+1CDDCE - F3 0F5C CA - subss xmm1,xmm2
		dmc3.exe+1CDDD2 - 0F2F C1    - comiss xmm0,xmm1
		*/
	}
	{
		auto dest = (appBaseAddr + 0x21562E);
		if (enable)
		{
			SetMemory(dest, 0x90, 5, MemoryFlags_VirtualProtectDestination);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0xF3, 0x0F, 0x5C, 0x47, 0x14, // subss xmm0,[rdi+14]
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+21562E - F3 0F5C 47 14 - subss xmm0,[rdi+14]
		dmc3.exe+215633 - 0F2F F0       - comiss xmm6,xmm0
		*/
	}
}

export void ToggleYamatoForceEdgeInfiniteRoundTrip(bool enable)
{
	LogFunction(enable);

	{
		auto dest = (appBaseAddr + 0x1D86DD);
		if (enable)
		{
			SetMemory(dest, 0x90, 5, MemoryFlags_VirtualProtectDestination);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0xF3, 0x0F, 0x5C, 0x47, 0x14, // subss xmm0,[rdi+14]
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+1D86DD - F3 0F5C 47 14 - subss xmm0,[rdi+14]
		dmc3.exe+1D86E2 - 0F2F F0       - comiss xmm6,xmm0
		*/
	}
	{
		auto dest = (appBaseAddr + 0x222921);
		if (enable)
		{
			SetMemory(dest, 0x90, 5, MemoryFlags_VirtualProtectDestination);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0xF3, 0x0F, 0x5C, 0x47, 0x14, // subss xmm0,[rdi+14]
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+222921 - F3 0F5C 47 14 - subss xmm0,[rdi+14]
		dmc3.exe+222926 - 0F2F F0       - comiss xmm6,xmm0
		*/
	}
}

export void ToggleEbonyIvoryFoursomeTime(bool enable)
{
	LogFunction(enable);

	WriteAddress((appBaseAddr + 0x1E24F6), (enable) ? (appBaseAddr + 0x1E24FC) : (appBaseAddr + 0x1E259C), 6);
	/*
	dmc3.exe+1E24F6 - 0F85 A0000000  - jne dmc3.exe+1E259C
	dmc3.exe+1E24FC - 48 89 7C 24 30 - mov [rsp+30],rdi
	*/

	WriteAddress((appBaseAddr + 0x20D188), (enable) ? (appBaseAddr + 0x20D18A) : (appBaseAddr + 0x20D1AB), 2);
	/*
	dmc3.exe+20D188 - 75 21               - jne dmc3.exe+20D1AB
	dmc3.exe+20D18A - F3 0F10 83 2C690000 - movss xmm0,[rbx+0000692C]
	*/
}

export void ToggleEbonyIvoryInfiniteRainStorm(bool enable)
{
	LogFunction(enable);

	static bool run = false;

	// Rain Storm Check
	{
		auto addr     = (appBaseAddr + 0x20CC0F);
		auto jumpAddr = (appBaseAddr + 0x20CC14);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+20CC0F - 0FA3 C1             - bt ecx,eax
		dmc3.exe+20CC12 - 72 0C               - jb dmc3.exe+20CC20
		dmc3.exe+20CC14 - BF 01000000         - mov edi,00000001
		dmc3.exe+20CC19 - 66 89 BB 1C3E0000   - mov [rbx+00003E1C],di
		dmc3.exe+20CC20 - F3 0F10 83 383E0000 - movss xmm0,[rbx+00003E38]
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
		};
		constexpr byte8 sect2[] =
		{
			0x84, 0xC0,                         // test al,al
			0x0F, 0x85, 0x00, 0x00, 0x00, 0x00, // jne dmc3.exe+20CC20
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(EbonyIvoryRainStormCheck, jumpAddr, true, false, 0, sizeof(sect1), sizeof(sect2));
			CopyMemory(func.sect1, sect1, sizeof(sect1));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
			WriteAddress((func.sect2 + 2), (appBaseAddr + 0x20CC20), 6);
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







export void ToggleArtemisSwapNormalShotAndMultiLock(bool enable)
{
	LogFunction(enable);

	{
		auto dest = (appBaseAddr + 0x215C78);
		if (enable)
		{
			constexpr byte8 buffer[] =
			{
				0xC6, 0x87, 0x80, 0xB8, 0x00, 0x00, 0x01, // mov byte ptr [rdi+0000B880],01
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0x44, 0x88, 0xB7, 0x80, 0xB8, 0x00, 0x00, // mov [rdi+0000B880],r14l
			};
			CopyMemory(dest, buffer, sizeof(buffer), MemoryFlags_VirtualProtectDestination);
		}
		/*
		dmc3.exe+215C78 - 44 88 B7 80B80000 - mov [rdi+0000B880],r14l
		dmc3.exe+215C7F - 83 F8 02          - cmp eax,02
		*/
	}

	Write<uint8>((appBaseAddr + 0x215CD4 + 6), (enable) ? 0 : 1);
	/*
	dmc3.exe+215CD4 - C6 87 80B80000 01 - mov byte ptr [rdi+0000B880],01
	dmc3.exe+215CDB - 44 0F28 C7        - movaps xmm8,xmm7
	*/
}

export void ToggleArtemisInstantFullCharge(bool enable)
{
	LogFunction(enable);

	WriteAddress((appBaseAddr + 0x215E42), (enable) ? (appBaseAddr + 0x215E48) : (appBaseAddr + 0x215F78), 6);
	/*
	dmc3.exe+215E42 - 0F82 30010000 - jb dmc3.exe+215F78
	dmc3.exe+215E48 - 0F2F C1       - comiss xmm0,xmm1
	*/
}

export void UpdateCrazyComboLevelMultiplier()
{
	LogFunction();

	Write<uint8>((appBaseAddr + 0x5898DE), activeConfig.crazyComboLevelMultiplier);
	Write<uint8>((appBaseAddr + 0x58999E), activeConfig.crazyComboLevelMultiplier);
	Write<uint8>((appBaseAddr + 0x589A5E), activeConfig.crazyComboLevelMultiplier);
}

// @Todo: Update name.
export void ToggleChronoSwords(bool enable)
{
	LogFunction(enable);

	static bool run = false;

	// Quicksilver Check
	{
		auto addr     = (appBaseAddr + 0x1DB8F8);
		auto jumpAddr = (appBaseAddr + 0x1DB8FD);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+1DB8F8 - F3 0F5C 43 14 - subss xmm0,[rbx+14]
		dmc3.exe+1DB8FD - 0F2F F0       - comiss xmm6,xmm0
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rax
			0x8A, 0x00,                                                 // mov al,[rax]
			0x84, 0xC0,                                                 // test al,al
			0x0F, 0x85, 0x00, 0x00, 0x00, 0x00,                         // jne dmc3.exe+1DB8FD
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, (sizeof(sect0) + size));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<bool **>(func.sect0 + 2) = &g_quicksilver;
			WriteAddress((func.sect0 + 0xE), (appBaseAddr + 0x1DB8FD), 6);
			CopyMemory((func.sect0 + sizeof(sect0)), addr, size, MemoryFlags_VirtualProtectSource);
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






















#pragma region Events






namespaceStart(Actor);







export void EventCreateMainActor(byte8 * actorBaseAddr)
{


	if (!activeConfig.Actor.enable)
	{
		return;
	}



	LogFunction(actorBaseAddr);



	ClearActorData();

	g_playerActorBaseAddrs[0] = actorBaseAddr;
	g_playerActorBaseAddrs.count = 2;

	g_defaultNewActorData[0].baseAddr = actorBaseAddr;

	g_defaultNewActorData[0].visibility = Visibility_Hide;








	// @Remove
	File_dynamicFiles.Clear();
}

export void EventCreateCloneActor(byte8 * actorBaseAddr)
{


	if (!activeConfig.Actor.enable)
	{
		return;
	}



	LogFunction(actorBaseAddr);

	g_playerActorBaseAddrs[1] = actorBaseAddr;

	g_defaultNewActorData[1].baseAddr = actorBaseAddr;
}












export void EventDelete()
{








	if (updateConfig)
	{
		updateConfig = false;





		// We only get here if updateConfig was set by SceneGame.
		// So if we're here, the actor module was off.


		activeConfig.Actor.enable = lastEnable;

		Log("Config updated.");












		return;
	}






	// @Todo: Create test scenario.
	// 2 rooms, one toggles false, the other true.




	if (!activeConfig.Actor.enable)
	{
		return;
	}


	LogFunction();








	// Copy Data
	[&]()
	{
		IntroduceData(g_newActorData[0][0][0].baseAddr , activeActorData, PlayerActorData, return);
		IntroduceData(g_defaultNewActorData[0].baseAddr, actorData      , PlayerActorData, return);

		actorData.hitPoints      = activeActorData.hitPoints;
		actorData.maxHitPoints   = activeActorData.maxHitPoints;
		actorData.magicPoints    = activeActorData.magicPoints;
		actorData.maxMagicPoints = activeActorData.maxMagicPoints;

		actorData.styleData.rank     = activeActorData.styleData.rank;
		actorData.styleData.meter    = activeActorData.styleData.meter;
		actorData.styleData.quotient = activeActorData.styleData.quotient;
		actorData.styleData.dividend = activeActorData.styleData.dividend;
		actorData.styleData.divisor  = activeActorData.styleData.divisor;

		DebugLog("EventDelete Copy StyleData");
	}();









	SetMainActor(0);





	//Log("SetMainActor");


	//HoboBreak();




	old_for_all(uint64, index, g_playerActorBaseAddrs.count)
	{
		IntroducePlayerActorData(actorBaseAddr, g_playerActorBaseAddrs[index], actorData, continue);

		if (actorData.newEntityIndex == ENTITY::MAIN)
		{
			func_2EDFC0(actorData.var_6410);
			func_337710(actorData.var_6458);
			/*
			dmc3.exe+212013 - 48 8D 8B 10640000 - lea rcx,[rbx+00006410]
			dmc3.exe+21201A - E8 A1BF0D00       - call dmc3.exe+2EDFC0
			dmc3.exe+21201F - 48 8D 8B 58640000 - lea rcx,[rbx+00006458]
			dmc3.exe+212026 - E8 E5561200       - call dmc3.exe+337710
			dmc3.exe+21202B - 48 8B 8B 78640000 - mov rcx,[rbx+00006478]
			*/
		}
	}






	ClearActorData();














	// @Remove
	File_dynamicFiles.Clear();





}





export void EventDeath()
{
	if (!activeConfig.Actor.enable)
	{
		return;
	}

	LogFunction();

	DecommissionDoppelgangers();
}

// export void EventContinue()
// {
// 	if (!activeConfig.Actor.enable)
// 	{
// 		return;
// 	}

// 	LogFunction();

// 	SetMainActor(0);
// }

// export void EventTeleport()
// {
// 	if (!activeConfig.Actor.enable)
// 	{
// 		return;
// 	}

// 	LogFunction();

// 	SetMainActor(0);
// }

export void InGameCutsceneStart()
{

	if (!activeConfig.Actor.enable)
	{
		return;
	}



	LogFunction();

	IntroduceData(g_playerActorBaseAddrs[0], mainActorData, PlayerActorData, return);

	using namespace MOTION_GROUP;

	old_for_each(uint64, actorIndex, 2, g_playerActorBaseAddrs.count)
	{
		IntroduceData(g_playerActorBaseAddrs[actorIndex], actorData, PlayerActorData, continue);

		actorData.motionArchives[CUTSCENE] = mainActorData.motionArchives[CUTSCENE];
	}

	DecommissionDoppelgangers();


}

// export void EventInGameCutsceneEnd()
// {
// 	LogFunction();

// }





export void EventMain()
{
	if (!activeConfig.Actor.enable)
	{
		return;
	}

	LogFunction();

	SpawnActors();



	[&]()
	{
		if (!activeConfig.enemyAutoSpawn)
		{
			return;
		}

		old_for_all(uint8, index, activeConfig.enemyCount)
		{
			auto & configCreateEnemyActorData = activeConfig.configCreateEnemyActorData[index];

			CreateEnemyActor(configCreateEnemyActorData);
		}
	}();
}





export void PlayerActorLoop(byte8 * actorBaseAddr)
{
	if (!activeConfig.Actor.enable)
	{
		return;
	}




	IntroducePlayerActorData(actorBaseAddr, actorData, return);



	if (!actorData.newActorLoopRun)
	{
		actorData.newActorLoopRun = true;

		LogFunction(actorBaseAddr);
	}



	UpdateModelPartitions(actorData);

	if (actorData.character == CHARACTER::VERGIL)
	{
		IsMeleeWeaponReadyVergilFix(actorData);
	}
}



export void SetNextScreen(EventData & eventData)
{
	if (!activeConfig.Actor.enable)
	{
		return;
	}

	LogFunction();

	switch (eventData.nextScreen)
	{
		case SCREEN::MISSION_START:
		{
			eventData.nextScreen = SCREEN::MISSION_SELECT;

			g_missionSelectForceConfirm = true;

			ToggleSkipCutscenes(true);

			break;
		}
	}
}





namespaceEnd();




#pragma endregion

#pragma region Scenes


namespaceStart(Actor);


export void SceneMissionStart()
{





	// IntroduceSessionData();

	// DebugLog("mission %u", sessionData.mission);

	//HoboBreak();



	LogFunction();

	old_for_all(uint8, playerIndex, PLAYER_COUNT)
	{
		auto & playerData = GetPlayerData(playerIndex);

		playerData.activeCharacterIndex = playerData.lastCharacterIndex = playerData.characterIndex = 0;

		old_for_all(uint8, characterIndex, CHARACTER_COUNT){
		old_for_all(uint8, entityIndex   , ENTITY_COUNT   )
		{
			auto & characterData = GetCharacterData
			(
				playerIndex,
				characterIndex,
				entityIndex
			);

			SetMemory
			(
				characterData.styleIndices,
				0,
				sizeof(characterData.styleIndices)
			);

			characterData.styleButtonIndex = 0;

			characterData.lastMeleeWeaponIndex = characterData.meleeWeaponIndex = 0;

			characterData.lastRangedWeaponIndex = characterData.rangedWeaponIndex = 0;
		}}
	}



	ToggleSkipCutscenes(activeConfig.skipCutscenes);





	// if (!activeConfig.Actor.enable)
	// {
	// 	return;
	// }





}









export void SceneGame()
{
	// Preserve Indices

	old_for_all(uint8, playerIndex, PLAYER_COUNT)
	{
		auto & activePlayerData = GetActivePlayerData(playerIndex);
		auto & queuedPlayerData = GetQueuedPlayerData(playerIndex);

		queuedPlayerData.characterIndex       = activePlayerData.characterIndex;
		queuedPlayerData.lastCharacterIndex   = activePlayerData.lastCharacterIndex;
		queuedPlayerData.activeCharacterIndex = activePlayerData.activeCharacterIndex;

		old_for_all(uint8, characterIndex, CHARACTER_COUNT){
		old_for_all(uint8, entityIndex   , ENTITY_COUNT   )
		{
			auto & activeCharacterData = GetActiveCharacterData(playerIndex, characterIndex, entityIndex);
			auto & queuedCharacterData = GetQueuedCharacterData(playerIndex, characterIndex, entityIndex);

			CopyMemory
			(
				queuedCharacterData.styleIndices,
				activeCharacterData.styleIndices,
				sizeof(queuedCharacterData.styleIndices)
			);

			queuedCharacterData.styleButtonIndex = activeCharacterData.styleButtonIndex;

			queuedCharacterData.meleeWeaponIndex     = activeCharacterData.meleeWeaponIndex;
			queuedCharacterData.lastMeleeWeaponIndex = activeCharacterData.lastMeleeWeaponIndex;

			queuedCharacterData.rangedWeaponIndex     = activeCharacterData.rangedWeaponIndex;
			queuedCharacterData.lastRangedWeaponIndex = activeCharacterData.lastRangedWeaponIndex;
		}}
	}



	// // Update Hit & Magic Points

	// old_for_all(uint8, playerIndex, PLAYER_COUNT)
	// {
	// 	IntroducePlayerCharacterNewActorData(playerIndex, continue);

	// 	IntroduceData(activeNewActorData.baseAddr, activeActorData, PlayerActorData, continue);

	// 	lastHitPoints  [playerIndex] = activeActorData.hitPoints;
	// 	lastMagicPoints[playerIndex] = activeActorData.magicPoints;
	// }



	CopyMemory
	(
		&activeConfig.Actor,
		&queuedConfig.Actor,
		sizeof(activeConfig.Actor)
	);



	IntroduceSessionData();
	IntroduceEventData(return);
	IntroduceNextEventData(return);
	IntroduceEventFlags(return);

	LogFunction();

	DebugLog("room          %u", eventData.room        );
	DebugLog("position      %u", eventData.position    );
	DebugLog("next room     %u", nextEventData.room    );
	DebugLog("next position %u", nextEventData.position);
	DebugLog("flags         %X", eventFlags[20]        );



	if
	(
		g_haywireNeoGenerator ||
		(
			(sessionData.mission == 18) &&
			(nextEventData.room == 403)
		) ||
		(
			(sessionData.mission == 19) &&
			(nextEventData.room == 421) &&
			(eventFlags[20] == 1)
		) ||
		(
			(sessionData.mission == 20) &&
			(nextEventData.room == 12)
		)
	)
	{
		lastEnable = activeConfig.Actor.enable;
		updateConfig = true;
		activeConfig.Actor.enable = false;
	}



	Actor::Toggle(activeConfig.Actor.enable);



	// if (!activeConfig.Actor.enable)
	// {
	// 	return;
	// }
}




namespaceEnd();




#pragma endregion

#ifdef __GARBAGE__
#endif
