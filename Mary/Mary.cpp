// @Todo: Update imports.
// @Todo: Update inits.

import Core;

#include "../Core/Macros.h"

import Windows;

import Vars;

import ActorBase;
import ActorRelocations;
import Actor;
import Arcade;
import BossRush;
import Camera;
import Config;
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
import SoundRelocations;
import Sound;
import Speed;
import Training;
import Window;

using namespace Windows;

#define debug true

#include "Macros.h"

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




		if
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



		// Global_Toggle(false);
		// Global_Toggle(true);


		// ActorBase::Toggle(false);
		// ActorBase::Toggle(true);



		//Actor_Init();

		// @Todo: Re-evaluate.
		if (!Sound_Init())
		{
			Log("Sound_Init failed.");

			return 0;
		}



		/*
		Tldr: We often run toggle functions twice with false first to ensure that
		backupHelper gets the correct data.

		Toggle and ToggleRelocations share some addresses.

		If ToggleRelocations runs first Toggle will now push the modified data
		instead of the default one to backupHelper.

		This becomes problematic when the data is later restored.

		ToggleRelocations correctly writes the default data, but Toggle will write
		the modified data and this will likely cause a crash later.

		To avoid this we run the toggle functions twice. The first time with false.

		This way, ToggleRelocations writes the default data and Toggle will also
		push the default data to backupHelper.
		*/

		Actor_Toggle(false);

		if (activeConfig.Actor.enable)
		{
			Actor_Toggle(activeConfig.Actor.enable);
		}


		ToggleBossLadyFixes(false);
		ToggleBossLadyFixes(activeConfig.enableBossLadyFixes);

		ToggleBossVergilFixes(false);
		ToggleBossVergilFixes(activeConfig.enableBossVergilFixes);


		ToggleDergil(false);
		ToggleDergil(activeConfig.dergil);



		Camera::Toggle(false);
		Camera::Toggle(true);

		Camera::ToggleInvertX(false);
		Camera::ToggleInvertX(activeConfig.cameraInvertX);

		Camera::ToggleDisableBossCamera(false);
		Camera::ToggleDisableBossCamera(activeConfig.disableBossCamera);







		ToggleNoDevilForm(false);
		ToggleNoDevilForm(activeConfig.noDevilForm);




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



		Arcade::Toggle(activeConfig.Arcade.enable);







		Event_Toggle(false);
		Event_Toggle(true);

		// @Remove
		Event_Init();




		ToggleSkipIntro    (activeConfig.skipIntro    );
		ToggleSkipCutscenes(activeConfig.skipCutscenes);

		Graphics::Init();
		UpdateFrameRate();

		HUD_Init();

		ToggleHideMainHUD(false);
		ToggleHideMainHUD(activeConfig.hideMainHUD);

		ToggleHideLockOn(false);
		ToggleHideLockOn(activeConfig.hideLockOn);

		ToggleHideBossHUD(false);
		ToggleHideBossHUD(activeConfig.hideBossHUD);

		ToggleForceVisibleHUD(false);
		ToggleForceVisibleHUD(activeConfig.forceVisibleHUD);



		Scene_Init();



		Speed::Toggle(false);
		Speed::Toggle(true);



		// Speed_Init();
		// UpdateSpeedValues();

		Training::ToggleInfiniteHitPoints  (activeConfig.infiniteHitPoints  );
		Training::ToggleInfiniteMagicPoints(activeConfig.infiniteMagicPoints);
		Training::ToggleDisableTimer       (activeConfig.disableTimer       );
		Training::ToggleInfiniteBullets    (activeConfig.infiniteBullets    );

		// @Update
		Window::ToggleForceFocus(true);

		Hooks::Init();


		Log("barsData %llX", offsetof(Config, barsData));





		//Log("&leftStickDirection[0] %X", offsetof(ENGINE_GAMEPAD, leftStickDirection[0]));

		//Log("&g_showItemWindow %llX", &g_show)


		



		SetMemory((appBaseAddr + 0x5505B5), 0, 23, MemoryFlags_VirtualProtectDestination); // Remove FMODGetCodecDescription label.

		if constexpr (debug)
		{
			// Disable Idle Timer
			SetMemory((appBaseAddr + 0x1F2A38), 0x90, 5, MemoryFlags_VirtualProtectDestination); // Dante
			SetMemory((appBaseAddr + 0x1F29AE), 0x90, 5, MemoryFlags_VirtualProtectDestination); // Vergil



// Disable Set Boss Camera

// SetMemory
// (
// 	(appBaseAddr + 0x55FD2),
// 	0x90,
// 	7,
// 	MemoryFlags_VirtualProtectDestination
// );

/*
dmc3.exe+55FD2 - 48 89 83 98040000 - mov [rbx+00000498],rax
dmc3.exe+55FD9 - 4C 89 A3 B0040000 - mov [rbx+000004B0],r12
*/








	// // Disable Style Rank Sub
	// SetMemory((appBaseAddr + 0x27A39C), 0x90, 5, MemoryFlags_VirtualProtectDestination);

	// // Force Collect Orbs
	// WriteAddress((appBaseAddr + 0x1B6597), (appBaseAddr + 0x1B6599), 2);



		}

		//HoboBreak();
	}

	return 1;
}
