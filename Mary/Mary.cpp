#include "../Core/Core.h"

import Actor;
import Arcade;
import Camera;
import Config;
import Event;
import File;
import FMOD;
import Graphics;
import GUI;
import Hooks;
import HUD;
import Internal;
import Memory;
import Other;
import Scene;
import Sound;
import Speed;
import Training;
import Window;

#define debug true

uint32 DllMain(HINSTANCE instance, uint32 reason, LPVOID reserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		Core_Log_Init("logs", "Mary.txt");

		Log("Session started.");

		if (!Core_Memory_Init(64 * 1024 * 1024))
		{
			Log("Core_Memory_Init failed.");

			return 0;
		}
		else if
		(
			!backupHelper.Init
			(
				(8 * 1024 * 1024),
				4096
			)
		)
		{
			Log("backupHelper.Init failed.");

			return 0;
		}

		Config_Init("configs", "Mary.bin");
		LoadConfig();

		{
			// auto & activePlayerData = GetActivePlayerData(0);
			// auto & queuedPlayerData = GetQueuedPlayerData(0);
			// ApplyDefaultCharacterData
			// (
			// 	activePlayerData.characterData[0][0],
			// 	3
			// );
			// ApplyDefaultCharacterData
			// (
			// 	queuedPlayerData.characterData[0][0],
			// 	3
			// );
			auto & activeCharacterData = GetActiveCharacterData
			(
				0,
				0,
				0
			);
			auto & queuedCharacterData = GetQueuedCharacterData
			(
				0,
				0,
				0
			);
			activeCharacterData.costume = 1;
			queuedCharacterData.costume = 1;
		}

		{
			// auto & activePlayerData = GetActivePlayerData(0);
			// auto & queuedPlayerData = GetQueuedPlayerData(0);
			// ApplyDefaultCharacterData
			// (
			// 	activePlayerData.characterData[0][0],
			// 	3
			// );
			// ApplyDefaultCharacterData
			// (
			// 	queuedPlayerData.characterData[0][0],
			// 	3
			// );
			auto & activeCharacterData = GetActiveCharacterData
			(
				0,
				0,
				1
			);
			auto & queuedCharacterData = GetQueuedCharacterData
			(
				0,
				0,
				1
			);
			activeCharacterData.costume = 1;
			queuedCharacterData.costume = 1;
		}



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

		Actor_Init();
		Actor_Toggle(activeConfig.Actor.enable);

		UpdateCrazyComboLevelMultiplier();

		Arcade_Toggle(activeConfig.Arcade.enable);

		ToggleArtemisSwapNormalShotAndMultiLock(activeConfig.Artemis.swapNormalShotAndMultiLock);
		ToggleArtemisInstantFullCharge         (activeConfig.Artemis.instantFullCharge         );

		Camera_ToggleInvertX(activeConfig.Camera.invertX);

		Event_Init();
		Event_ToggleSkipIntro    (activeConfig.Event.skipIntro);
		Event_ToggleSkipCutscenes(activeConfig.Event.skipCutscenes);

		Graphics_Init();
		UpdateFrameRate();

		Hooks_Init();

		HUD_Init();

		Other_Init();
		UpdateOrbReach();

		Scene_Init();

		if (!Sound_Init())
		{
			Log("Sound_Init failed.");

			return 0;
		}

		// Sound_Init();
		// Sound_Toggle(true);

		Speed_Init();
		UpdateSpeedValues();

		Training_ToggleInfiniteHitPoints  (activeConfig.Training.infiniteHitPoints  );
		Training_ToggleInfiniteMagicPoints(activeConfig.Training.infiniteMagicPoints);
		Training_ToggleDisableTimer       (activeConfig.Training.disableTimer       );

		Window_ToggleForceFocus(true);

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
