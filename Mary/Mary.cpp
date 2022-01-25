import Core;
import Core_Input;

#include "../Core/Macros.h"

import Windows;

using namespace Windows;

import ActorBase;
import ActorRelocations;
import Actor;
import Arcade;
import BossRush;
import Camera;
import Config;
import Event;
import Exp;
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
import Vars;
import Window;

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
		InitLog("logs", "Mary.txt");

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



		InitConfig();
		LoadConfig();



		InitExp();
		LoadExp();



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

		Actor::Toggle(false);
		Actor::Toggle(activeConfig.Actor.enable);



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



		Arcade::Toggle(false);
		Arcade::Toggle(activeConfig.Arcade.enable);



		// @Merge
		Event_Toggle(false);
		Event_Toggle(true);

		Event_Init();



		ToggleSkipIntro    (activeConfig.skipIntro    );
		ToggleSkipCutscenes(activeConfig.skipCutscenes);



		HUD_Init();

		ToggleHideMainHUD(false);
		ToggleHideMainHUD(activeConfig.hideMainHUD);

		ToggleHideLockOn(false);
		ToggleHideLockOn(activeConfig.hideLockOn);

		ToggleHideBossHUD(false);
		ToggleHideBossHUD(activeConfig.hideBossHUD);

		ToggleForceVisibleHUD(false);
		ToggleForceVisibleHUD(activeConfig.forceVisibleHUD);



		Scene::Toggle(false);
		Scene::Toggle(true);

		Speed::Toggle(false);
		Speed::Toggle(true);



		ToggleInfiniteHitPoints  (activeConfig.infiniteHitPoints  );
		ToggleInfiniteMagicPoints(activeConfig.infiniteMagicPoints);
		ToggleDisableTimer       (activeConfig.disableTimer       );
		ToggleInfiniteBullets    (activeConfig.infiniteBullets    );



		ToggleForceWindowFocus(false);
		ToggleForceWindowFocus(activeConfig.forceWindowFocus);



		ToggleDisablePlayerActorIdleTimer(false);
		ToggleDisablePlayerActorIdleTimer(activeConfig.disablePlayerActorIdleTimer);

		ToggleRebellionInfiniteShredder(false);
		ToggleRebellionInfiniteShredder(activeConfig.rebellionInfiniteShredder);

		ToggleRebellionHoldDrive(false);
		ToggleRebellionHoldDrive(activeConfig.rebellionHoldDrive);



		XI::new_Init("xinput9_1_0.dll");

		Hooks::Init();



		// Remove FMODGetCodecDescription Label
		SetMemory
		(
			(appBaseAddr + 0x5505B5),
			0,
			23,
			MemoryFlags_VirtualProtectDestination
		);
	}

	return 1;
}
