module;
#include "../Core/Core.h"

#include "Vars.h"
export module Enemy;

import Config;
import File;
import Global;
import Internal;

#define debug false

export Array
<
	byte8 *,
	CREATE_ENEMY_COUNT
>
Enemy_enemyBaseAddr = {};

static_assert(countof(Enemy_enemyBaseAddr.dataAddr) == 30);

export byte8 * CreateEnemy
(
	Config::CreateEnemyData & configData,
	uint8 index
)
{
	if constexpr (debug)
	{
		LogFunction();
	}

	if
	(
		(index >= CREATE_ENEMY_COUNT) ||
		!InGame()
	)
	{
		return 0;
	}

	IntroduceMainActorData(actorBaseAddr, actorData, return 0);

	auto & result = Enemy_enemyBaseAddr[index];

	if (result != 0)
	{
		Log("Already in use. %llu", index);

		return 0;
	}

	CreateEnemyData data = {};

	data.enemy = configData.enemy;
	data.position = (configData.useMainActorData) ? actorData.position : configData.position;
	data.position.a = 1.0f;
	data.rotation = (configData.useMainActorData) ? actorData.rotation : configData.rotation;
	data.spawnMethod = configData.spawnMethod;
	data.variant = configData.variant;



	auto addr = *reinterpret_cast<byte8 **>(appBaseAddr + 0xC90E10);
	if (!addr)
	{
		return 0;
	}
	addr = *reinterpret_cast<byte8 **>(addr + 0x28);
	if (!addr)
	{
		return 0;
	}
	addr += 0xCB0;



	auto addr2 = *reinterpret_cast<byte8 **>(appBaseAddr + 0xC90E10);
	if (!addr2)
	{
		return 0;
	}
	auto & metadataAddr = *reinterpret_cast<FileDataMetadata **>(addr2 + 0xA80 + 0x628);

	auto lastMetadataAddr = metadataAddr;



	metadataAddr = enemyFileDataMetadata;

	result = func_1A4680(addr, data);

	metadataAddr = lastMetadataAddr;



	return result;
}

export void KillEnemy(uint8 index)
{
	if
	(
		(index >= CREATE_ENEMY_COUNT) ||
		!InGame()
	)
	{
		return;
	}

	// @Todo: Introduce Enemy Data.
	auto enemyBaseAddr = Enemy_enemyBaseAddr[index];
	if (!enemyBaseAddr)
	{
		return;
	}
	auto & enemyData = *reinterpret_cast<EnemyData *>(enemyBaseAddr);

	switch (enemyData.enemy)
	{
		case ENEMY_LADY:
		{
			// @Todo: Enemy Data Lady.
			auto & event = *reinterpret_cast<uint32 *>(enemyBaseAddr + 0x180 + 0x5808);
			auto & isFriend = *reinterpret_cast<bool *>(enemyBaseAddr + 0x180 + 0x58AE);

			isFriend = false;
			event = 20;

			break;
		}
	}
}






void Watchdog()
{

	// static bool run = false;
	// if (!run)
	// {
	// 	run = true;

	// 	HoboBreak();

	// 	LogFunction();
	// }



	auto Function = [&](auto & enemyBaseAddr)
	{
		// @Todo: IntroduceEnemyDataNoBaseAddress.
		if (!enemyBaseAddr)
		{
			return;
		}
		auto & enemyData = *reinterpret_cast<EnemyData *>(enemyBaseAddr);

		if (!enemyData.baseAddr)
		{
			enemyBaseAddr = 0;
		}




	};

	Enemy_enemyBaseAddr.ForEach
	(
		0,
		CREATE_ENEMY_COUNT,
		Function
	);
}






export void Enemy_MainLoopOnce()
{
	LogFunction();

	for_all(uint8, index, activeConfig.createEnemyCount)
	{
		auto & activeConfigData = activeConfig.createEnemyData[index];

		if (!activeConfigData.autoSpawn)
		{
			continue;
		}

		CreateEnemy(activeConfigData, index);
	}
}



export void Enemy_Main()
{
	Watchdog();
}

// @Research: Check if both are still required.
export void Enemy_CreateMainActor(byte8 * actorBaseAddr)
{
	Enemy_enemyBaseAddr.Clear();
}

export void Enemy_Delete()
{
	Enemy_enemyBaseAddr.Clear();
}



#ifdef __GARBAGE__
#endif
