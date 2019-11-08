#include "Speed.h"

float32 * Game_Speed_turbo             = 0;
float32 * Game_Speed_actor             = 0;
float32 * Game_Speed_Quicksilver_actor = 0;
float32 * Game_Speed_Quicksilver_enemy = 0;

void Game_Speed_Update()
{
	LogFunction();
	// Main
	{
		Write<float32>((appBaseAddr + 0x326950), Config.Game.Speed.Main.base);
		*Game_Speed_turbo = Config.Game.Speed.Main.turbo;
		WriteAddress((appBaseAddr + 0x23E639), (byte *)Game_Speed_turbo, 8);
		*Game_Speed_actor = Config.Game.Speed.Main.actor;
		WriteAddress((appBaseAddr + 0x1F8CA6), (byte *)Game_Speed_actor, 8);
		Write<float32>((appBaseAddr + 0x326ADD), Config.Game.Speed.Main.enemy);
	}
	// Devil
	{
		float32 * speed = (float32 *)(appBaseAddr + 0x58B0B8);
		speed[SPEED_DANTE_REBELLION]        = Config.Game.Speed.Dante.rebellion;
		speed[SPEED_DANTE_CERBERUS]         = Config.Game.Speed.Dante.cerberus;
		speed[SPEED_DANTE_AGNI_RUDRA]       = Config.Game.Speed.Dante.agniRudra;
		speed[SPEED_DANTE_NEVAN]            = Config.Game.Speed.Dante.nevan;
		speed[SPEED_DANTE_BEOWULF]          = Config.Game.Speed.Dante.beowulf;
		speed[SPEED_DANTE_SPARDA]           = Config.Game.Speed.Dante.sparda;
		speed[SPEED_VERGIL_YAMATO]          = Config.Game.Speed.Vergil.yamato;
		speed[SPEED_VERGIL_BEOWULF]         = Config.Game.Speed.Vergil.beowulf;
		speed[SPEED_VERGIL_FORCE_EDGE]      = Config.Game.Speed.Vergil.forceEdge;
		speed[SPEED_NERO_ANGELO_YAMATO]     = Config.Game.Speed.NeroAngelo.yamato;
		speed[SPEED_NERO_ANGELO_BEOWULF]    = Config.Game.Speed.NeroAngelo.beowulf;
		speed[SPEED_NERO_ANGELO_FORCE_EDGE] = Config.Game.Speed.NeroAngelo.forceEdge;
	}
	// Quicksilver
	{
		*Game_Speed_Quicksilver_actor = Config.Game.Speed.Quicksilver.actor;
		WriteAddress((appBaseAddr + 0x27A982), (byte *)Game_Speed_Quicksilver_actor, 8);
		*Game_Speed_Quicksilver_enemy = Config.Game.Speed.Quicksilver.enemy;
		WriteAddress((appBaseAddr + 0x27A98A), (byte *)Game_Speed_Quicksilver_enemy, 8);
	}
	// Live
	if (ActorAvailable())
	{
		float32 & speed = *(float32 *)(appBaseAddr + 0xCF2D90);
		bool turbo = *(bool *)(appBaseAddr + 0xD6CEA9);
		if (!turbo)
		{
			speed = Config.Game.Speed.Main.base;
		}
		else
		{
			speed = Config.Game.Speed.Main.turbo;
		}
	}
}

void Game_Speed_Reset()
{
	LogFunction();
	// Main
	{
		Write<float32>((appBaseAddr + 0x326950), DefaultConfig.Game.Speed.Main.base);
		*Game_Speed_turbo = DefaultConfig.Game.Speed.Main.turbo;
		WriteAddress((appBaseAddr + 0x23E639), (appBaseAddr + 0x4CC640), 8);
		*Game_Speed_actor = DefaultConfig.Game.Speed.Main.actor;
		WriteAddress((appBaseAddr + 0x1F8CA6), (appBaseAddr + 0x35D56C), 8);
		Write<float32>((appBaseAddr + 0x326ADD), DefaultConfig.Game.Speed.Main.enemy);
	}
	// Devil
	{
		float32 * speed = (float32 *)(appBaseAddr + 0x58B0B8);
		speed[SPEED_DANTE_REBELLION]        = DefaultConfig.Game.Speed.Dante.rebellion;
		speed[SPEED_DANTE_CERBERUS]         = DefaultConfig.Game.Speed.Dante.cerberus;
		speed[SPEED_DANTE_AGNI_RUDRA]       = DefaultConfig.Game.Speed.Dante.agniRudra;
		speed[SPEED_DANTE_NEVAN]            = DefaultConfig.Game.Speed.Dante.nevan;
		speed[SPEED_DANTE_BEOWULF]          = DefaultConfig.Game.Speed.Dante.beowulf;
		speed[SPEED_DANTE_SPARDA]           = DefaultConfig.Game.Speed.Dante.sparda;
		speed[SPEED_VERGIL_YAMATO]          = DefaultConfig.Game.Speed.Vergil.yamato;
		speed[SPEED_VERGIL_BEOWULF]         = DefaultConfig.Game.Speed.Vergil.beowulf;
		speed[SPEED_VERGIL_FORCE_EDGE]      = DefaultConfig.Game.Speed.Vergil.forceEdge;
		speed[SPEED_NERO_ANGELO_YAMATO]     = DefaultConfig.Game.Speed.NeroAngelo.yamato;
		speed[SPEED_NERO_ANGELO_BEOWULF]    = DefaultConfig.Game.Speed.NeroAngelo.beowulf;
		speed[SPEED_NERO_ANGELO_FORCE_EDGE] = DefaultConfig.Game.Speed.NeroAngelo.forceEdge;
	}
	// Quicksilver
	{
		*Game_Speed_Quicksilver_actor = DefaultConfig.Game.Speed.Quicksilver.actor;
		WriteAddress((appBaseAddr + 0x27A982), (appBaseAddr + 0x4CECF8), 8);
		*Game_Speed_Quicksilver_enemy = DefaultConfig.Game.Speed.Quicksilver.enemy;
		WriteAddress((appBaseAddr + 0x27A98A), (appBaseAddr + 0x4D84EC), 8);
	}
	// Live
	if (ActorAvailable())
	{
		float32 & speed = *(float32 *)(appBaseAddr + 0xCF2D90);
		bool turbo = *(bool *)(appBaseAddr + 0xD6CEA9);
		if (!turbo)
		{
			speed = DefaultConfig.Game.Speed.Main.base;
		}
		else
		{
			speed = DefaultConfig.Game.Speed.Main.turbo;
		}
	}
}

void Game_Speed_Init()
{
	LogFunction();
	byte * addr = (byte *)HighAlloc(64);
	Game_Speed_turbo             = (float32 *)( addr       );
	Game_Speed_actor             = (float32 *)( addr + 4   );
	Game_Speed_Quicksilver_actor = (float32 *)( addr + 8   );
	Game_Speed_Quicksilver_enemy = (float32 *)( addr + 0xC );
}

void Game_Speed_Toggle(bool enable)
{
	Log("%s %u", FUNC_NAME, enable);
	if (enable)
	{
		Game_Speed_Update();
	}
	else
	{
		Game_Speed_Reset();
	}
}
