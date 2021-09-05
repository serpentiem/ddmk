import Core;

#include "../Core/Macros.h"

import Windows;

import Actor;
import Arcade;
import Config;
import Event;
import Global;
import Graphics;
import Hooks;
import HUD;
import Internal;
import Training;
import Vars;
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
		Core_Log_Init("logs", "Eva.txt");

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

		Config_Init("configs", "Eva.bin");

		LoadConfig();



		Internal_Init();




		ToggleForceEdgeFixes(false);
		ToggleForceEdgeFixes(activeConfig.enableForceEdgeFixes);

		ToggleSpardaFixes(false);
		ToggleSpardaFixes(activeConfig.enableSpardaFixes);

		ToggleYamatoFixes(false);
		ToggleYamatoFixes(activeConfig.enableYamatoFixes);

		ToggleAirHikeCoreAbility(false);
		ToggleAirHikeCoreAbility(activeConfig.airHikeCoreAbility);

		ToggleInfiniteRoundTrip(false);
		ToggleInfiniteRoundTrip(activeConfig.infiniteRoundTrip);

		ToggleMeleeWeaponSwitchController(false);
		ToggleMeleeWeaponSwitchController(activeConfig.enableMeleeWeaponSwitchController);

		ToggleRangedWeaponSwitchController(false);
		ToggleRangedWeaponSwitchController(activeConfig.enableRangedWeaponSwitchController);

		ToggleChargeFixes(false);
		ToggleChargeFixes(activeConfig.enableChargeController);



		Arcade::Toggle(false);
		Arcade::Toggle(activeConfig.Arcade.enable);

		ToggleSkipIntro(false);
		ToggleSkipIntro(activeConfig.skipIntro);

		ToggleDisablePauseRestrictions(false);
		ToggleDisablePauseRestrictions(activeConfig.disablePauseRestrictions);

		Graphics::Init();
		UpdateFrameRate();

		ToggleForceWindowFocus(false);
		ToggleForceWindowFocus(activeConfig.forceWindowFocus);

		ToggleInfiniteHitPoints(false);
		ToggleInfiniteHitPoints(activeConfig.infiniteHitPoints);

		ToggleInfiniteMagicPoints(false);
		ToggleInfiniteMagicPoints(activeConfig.infiniteMagicPoints);

		ToggleDisableTimer(false);
		ToggleDisableTimer(activeConfig.disableTimer);



		Event::Toggle(false);
		Event::Toggle(true);

		ToggleAutoExamine(false);
		ToggleSkipText   (false);



		if constexpr (debug)
		{
			ToggleDisableIdleTimer(false);
			ToggleDisableIdleTimer(activeConfig.disableIdleTimer);

			ToggleScreenEffectForceMaxTimer(false);
			ToggleScreenEffectForceMaxTimer(activeConfig.screenEffectForceMaxTimer);

			ToggleForceVisibleHUD(false);
			ToggleForceVisibleHUD(activeConfig.forceVisibleHUD);
		}



		// Remove labels.
		SetMemory
		(
			(appBaseAddr + 0x50CDE6),
			0,
			35,
			MemoryFlags_VirtualProtectDestination
		);

		Hooks::Init();
	}

	return 1;
}
