#include "Speed.h"

float32 * Speed_turbo             = 0;
float32 * Speed_actor             = 0;
float32 * Speed_Quicksilver_actor = 0;
float32 * Speed_Quicksilver_enemy = 0;

void Speed_Update(CONFIG & config)
{
	LogFunction();

	*Speed_turbo             = config.Speed.Main.turbo;
	*Speed_actor             = config.Speed.Main.actor;
	*Speed_Quicksilver_actor = config.Speed.Quicksilver.actor;
	*Speed_Quicksilver_enemy = config.Speed.Quicksilver.enemy;

	// Main
	{
		Write<float32>((appBaseAddr + 0x326950), config.Speed.Main.base);
		WriteAddress((appBaseAddr + 0x23E639), (byte8 *)Speed_turbo, 8);
		WriteAddress((appBaseAddr + 0x1F8CA6), (byte8 *)Speed_actor, 8);
		Write<float32>((appBaseAddr + 0x326ADD), config.Speed.Main.enemy);
	}
	// Devil
	{
		float32 * speed = (float32 *)(appBaseAddr + 0x58B0B8);
		vp_memcpy
		(
			&speed[SPEED_DEVIL_DANTE_REBELLION],
			config.Speed.Devil.dante,
			sizeof(config.Speed.Devil.dante)
		);
		vp_memcpy
		(
			&speed[SPEED_DEVIL_VERGIL_YAMATO],
			config.Speed.Devil.vergil,
			sizeof(config.Speed.Devil.vergil)
		);
		vp_memcpy
		(
			&speed[SPEED_DEVIL_NERO_ANGELO_YAMATO],
			config.Speed.Devil.neroAngelo,
			sizeof(config.Speed.Devil.neroAngelo)
		);
	}
	// Quicksilver
	{
		WriteAddress((appBaseAddr + 0x27A982), (byte8 *)Speed_Quicksilver_actor, 8);
		WriteAddress((appBaseAddr + 0x27A98A), (byte8 *)Speed_Quicksilver_enemy, 8);
	}
	// Live
	{
		auto & speed = *(float32 *)(appBaseAddr + 0xCF2D90);
		auto & turbo = *(bool    *)(appBaseAddr + 0xD6CEA9);
		if (!InGame())
		{
			return;
		}
		speed = (turbo) ? config.Speed.Main.turbo : config.Speed.Main.base;
	}
}

void Speed_Init()
{
	LogFunction();
	auto addr = (float32 *)HighAlloc(16);
	if (!addr)
	{
		Log("HighAlloc failed.");
		return;
	}
	Speed_turbo             = &addr[0];
	Speed_actor             = &addr[1];
	Speed_Quicksilver_actor = &addr[2];
	Speed_Quicksilver_enemy = &addr[3];
}
