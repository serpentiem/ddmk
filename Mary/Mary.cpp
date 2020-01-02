#include "../Core/Core.h"

#include "Config.h"
#include "Event.h"
#include "FMOD.h"
#include "Hooks.h"
#include "Speed.h"
#include "Update.h"

#include "System/Actor.h"
#include "System/Animation.h"
#include "System/Cache.h"
#include "System/Camera.h"
#include "System/File.h"
#include "System/Graphics.h"
#include "System/HUD.h"
#include "System/Input.h"
#include "System/Media.h"
#include "System/Motion.h"
#include "System/Sound.h"
#include "System/Weapon.h"
#include "System/Window.h"

#include "Game/Arcade.h"
#include "Game/Attack.h"
#include "Game/Dante.h"
#include "Game/Doppelganger.h"
#include "Game/Mobility.h"
#include "Game/Other.h"
#include "Game/ResetMotionState.h"
#include "Game/StyleSwitcher.h"
#include "Game/Training.h"
#include "Game/Vergil.h"
#include "Game/WeaponSwitcher.h"

#include "Cosmetics/Color.h"
#include "Cosmetics/Dante.h"
#include "Cosmetics/Other.h"
#include "Cosmetics/Vergil.h"

const char * Log_directory = "logs";
const char * Log_file      = "Mary.txt";

uint64 mainChunkSize = (64 * 1024 * 1024);

uint32 DllMain(HINSTANCE instance, uint32 reason, LPVOID reserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		Log_Init();
		Log("Session started.");
		Config_Init();
		Cosmetics_Color_AdjustConfig();
		LoadConfig();
		if (!Memory_Init())
		{
			return 0;
		}

		Event_Init();
		Event_ToggleSkipIntro    (Config.System.Event.skipIntro    );
		Event_ToggleSkipCutscenes(Config.System.Event.skipCutscenes);
		FMOD_Init();
		Hooks_Init();
		Speed_Init();
		Speed_Update(Config);
		Update_Init();

		System_Actor_Init();
		System_Actor_ToggleArrayExtension(true);
		System_Actor_ToggleCreateActorOne(true);
		System_Actor_ToggleUpdateActor(true);
		System_Actor_ToggleDoppelgangerFixes(true);
		System_Actor_ToggleDisableIdleTimer(Config.System.Actor.disableIdleTimer);
		System_Animation_Init();
		System_File_Init(); // Cache requires AdjustPointers.
		System_Cache_Init();
		System_Cache_ToggleExtendVectors(true);
		System_Camera_ToggleInvertX(Config.System.Camera.invertX);
		System_Graphics_UpdateFrameRate(Config);
		System_HUD_Init();
		System_Input_Init();
		System_Input_ToggleRangeExtension  (Config.Game.Multiplayer.enable);
		System_Input_ToggleMultiplayerFixes(Config.Game.Multiplayer.enable);
		System_Media_Init();
		System_Motion_Init();
		System_Sound_Init();
		System_Weapon_Init();
		System_Weapon_ToggleUpdateWeapon(true);
		System_Weapon_ToggleDoppelgangerFixes(true);
		System_Weapon_ToggleModelFixes(true);
		System_Window_ToggleForceFocus(Config.System.Window.forceFocus);

		Game_Arcade_UpdateModeIndex();
		Game_Arcade_Toggle(Config.Game.Arcade.enable);
		Game_Attack_Init();
		Game_Dante_Init();
		Game_Dante_Rebellion_ToggleInfiniteSwordPierce(Config.Game.Dante.Rebellion.infiniteSwordPierce);
		Game_Dante_EbonyIvory_ToggleFoursomeTime      (Config.Game.Dante.EbonyIvory.foursomeTime      );
		Game_Dante_EbonyIvory_ToggleInfiniteRainStorm (Config.Game.Dante.EbonyIvory.infiniteRainStorm );
		Game_Dante_Artemis_ToggleSwap                 (Config.Game.Dante.Artemis.swap                 );
		Game_Dante_Artemis_ToggleInstant              (Config.Game.Dante.Artemis.instant              );
		Game_Dante_AirHike_ToggleCoreAbility          (Config.Game.Dante.AirHike.coreAbility          );
		Game_Dante_CrazyCombo_SetLevelMultiplier      (Config.Game.Dante.CrazyCombo.levelMultiplier   );
		Game_Dante_WeaponSwitchTimeout_Melee_Toggle   (Config.Game.Dante.WeaponSwitchTimeout.melee    );
		Game_Dante_WeaponSwitchTimeout_Ranged_Toggle  (Config.Game.Dante.WeaponSwitchTimeout.ranged   );
		Game_Doppelganger_Init();
		Game_Doppelganger_ToggleEnableDevilTrigger(Config.Game.Doppelganger.enableDevilTrigger);
		Game_Mobility_Init();
		Game_Mobility_Toggle(Config.Game.Mobility.enable);
		Game_Other_Init();
		Game_Other_Toggle(Config.Game.Other.enable);
		Game_ResetMotionState_UpdateButtonIndex();
		Game_StyleSwitcher_Init();
		Game_StyleSwitcher_Toggle(Config.Game.StyleSwitcher.enable);
		Game_Training_ToggleInfiniteHitPoints  (Config.Game.Training.infiniteHitPoints  );
		Game_Training_ToggleInfiniteMagicPoints(Config.Game.Training.infiniteMagicPoints);
		Game_Training_ToggleDisableTimer       (Config.Game.Training.disableTimer       );
		Game_Vergil_Init();
		Game_Vergil_ForceEdge_ToggleInfiniteRoundTrip(Config.Game.Vergil.ForceEdge.infiniteRoundTrip);
		Game_Vergil_SummonedSwords_ToggleChronoSwords(Config.Game.Vergil.SummonedSwords.chronoSwords);
		Game_Vergil_WeaponSwitchTimeout_MeleeToggle  (Config.Game.Vergil.WeaponSwitchTimeout.melee  );
		Game_WeaponSwitcher_Init();
		Game_WeaponSwitcher_Toggle(Config.Game.WeaponSwitcher.enable);

		Cosmetics_Color_Init();
		Cosmetics_Color_UpdateColors(Config);
		Cosmetics_Dante_Init();
		Cosmetics_Dante_ToggleHideBeowulf(Config.Cosmetics.Dante.hideBeowulf);
		Cosmetics_Other_Init();
		Cosmetics_Other_ToggleNoDevilForm(Config.Cosmetics.Other.noDevilForm);
		Cosmetics_Vergil_ToggleHideBeowulf(Config.Cosmetics.Vergil.hideBeowulf);
	}
	return 1;
}
