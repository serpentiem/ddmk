// @Todo: Update imports.
// @Todo: Update inits.

import Core;

#include "../Core/Macros.h"

import Windows;

import Vars;

import Actor;
import Arcade;
import BossRush;
import Camera;
import Config;
import Enemy;
import Event;
import File;
import FMOD;
import Global;
import Graphics;
import GUI;
import Hooks;
import HUD;
import Input;
import Internal;
import Memory;
import Model;
import Scene;
import Sound;
import Speed;
import Training;
import Window;

using namespace Windows;

#define debug false

uint32 DllMain
(
	HINSTANCE instance,
	uint32 reason,
	LPVOID reserved
)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		Core_Log_Init("logs", "Mary.txt");

		Log("Session started.");

		if (!Core_Memory_Init())
		{
			Log("Core_Memory_Init failed.");

			return 0;
		}

		if (!memoryData.InitData(64 * 1024 * 1024))
		{
			Log("memoryData.InitData failed.");

			return 0;
		}

		SetMemory
		(
			memoryData.dataAddr,
			0xCC,
			memoryData.dataSize
		);

		if (!protectionHelper.Init(4096))
		{
			Log("protectionHelper.Init failed.");

			return 0;
		}
		else if
		(
			!backupHelper.Init
			(
				(8 * 1024 * 1024),
				(1 * 1024 * 1024)
			)
		)
		{
			Log("backupHelper.Init failed.");

			return 0;
		}

		Config_Init("configs", "Mary.bin");

		LoadConfig();



		if (!Memory_Init())
		{
			Log("Memory_Init failed.");

			return 0;
		}

		Memory_ToggleExtendVectors(true);

		Internal_Init();

		if (!File_Init())
		{
			Log("File_Init failed.");

			return 0;
		}

		if (!FMOD_Init())
		{
			Log("FMOD_Init failed.");

			return 0;
		}



		ToggleDisableGetInput(false);





		Actor_Init();

		Actor_Toggle(false);

		if (activeConfig.Actor.enable)
		{
			Actor_Toggle(activeConfig.Actor.enable);
		}



		Camera_Toggle(false);
		Camera_Toggle(true);

		ToggleDeplete(false);
		ToggleDeplete(true);

		ToggleOrbReach(false);
		ToggleOrbReach(true);

		ToggleDamage(false);
		ToggleDamage(true);



		UpdateCrazyComboLevelMultiplier();

		ToggleAirHikeCoreAbility               (activeConfig.airHikeCoreAbility                );
		ToggleRoyalguardForceJustFrameRelease  (activeConfig.Royalguard.forceJustFrameRelease  );
		ToggleRebellionInfiniteSwordPierce     (activeConfig.Rebellion.infiniteSwordPierce     );
		ToggleYamatoForceEdgeInfiniteRoundTrip (activeConfig.YamatoForceEdge.infiniteRoundTrip );
		ToggleEbonyIvoryFoursomeTime           (activeConfig.EbonyIvory.foursomeTime           );
		ToggleEbonyIvoryInfiniteRainStorm      (activeConfig.EbonyIvory.infiniteRainStorm      );
		ToggleArtemisSwapNormalShotAndMultiLock(activeConfig.Artemis.swapNormalShotAndMultiLock);
		ToggleArtemisInstantFullCharge         (activeConfig.Artemis.instantFullCharge         );
		ToggleChronoSwords                     (activeConfig.SummonedSwords.chronoSwords       );



		Arcade_Toggle(activeConfig.Arcade.enable);

		Camera_ToggleInvertX(activeConfig.Camera.invertX);


		Event_Toggle(false);
		Event_Toggle(true);


		Event_Init();
		ToggleSkipIntro    (activeConfig.skipIntro    );
		ToggleSkipCutscenes(activeConfig.skipCutscenes);

		Graphics::Init();
		UpdateFrameRate();

		HUD_Init();

		Scene_Init();



		if (!Sound_Init())
		{
			Log("Sound_Init failed.");

			return 0;
		}

		Sound::ToggleRelocations(false);

		if (activeConfig.Actor.enable)
		{
			Sound::ToggleRelocations(activeConfig.Actor.enable);
		}



		Speed_Init();
		UpdateSpeedValues();

		Training_ToggleInfiniteHitPoints  (activeConfig.infiniteHitPoints  );
		Training_ToggleInfiniteMagicPoints(activeConfig.infiniteMagicPoints);
		Training_ToggleDisableTimer       (activeConfig.disableTimer       );

		Window::ToggleForceFocus(true);

		Hooks_Init();





		Log("&leftStickDirection[0] %X", offsetof(ENGINE_GAMEPAD, leftStickDirection[0]));

		//Log("&g_showItemWindow %llX", &g_show)



		SetMemory((appBaseAddr + 0x5505B5), 0, 23, MemoryFlags_VirtualProtectDestination); // Remove FMODGetCodecDescription label.

		if constexpr (debug)
		{
			// Disable Idle Timer
			SetMemory((appBaseAddr + 0x1F2A38), 0x90, 5, MemoryFlags_VirtualProtectDestination); // Dante
			SetMemory((appBaseAddr + 0x1F29AE), 0x90, 5, MemoryFlags_VirtualProtectDestination); // Vergil

			// Force Visible HUD
			Write<byte8>((appBaseAddr + 0x27E800), 0xEB);
			Write<byte8>((appBaseAddr + 0x27DF3E), 0xEB);
			Write<byte16>((appBaseAddr + 0x280DB9), 0xE990);

			// Disable Style Rank Sub
			SetMemory((appBaseAddr + 0x27A39C), 0x90, 5, MemoryFlags_VirtualProtectDestination);

			// Force Collect Orbs
			WriteAddress((appBaseAddr + 0x1B6597), (appBaseAddr + 0x1B6599), 2);
		}
	}

	return 1;
}
