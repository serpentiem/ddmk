#include "../Core/Core.h"

#include "Config.h"

#include "Event.h"

#include "FMOD.h"
#include "Hooks.h"

#include "System/Actor.h"
#include "System/Animation.h"
#include "System/Cache.h"
#include "System/Camera.h"
//#include "System/Event.h"



#include "System/File.h"
#include "System/Media.h"
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
#include "Game/Speed.h"
//#include "Game/Style.h"
#include "Game/StyleSwitcher.h"
#include "Game/Training.h"
#include "Game/Vergil.h"
#include "Game/WeaponSwitcher.h"

#include "Cosmetics/Color.h"
#include "Cosmetics/Dante.h"
#include "Cosmetics/Other.h"
#include "Cosmetics/Vergil.h"
#include "Cosmetics/Weapon.h"

const char * Log_directory = "logs";
const char * Log_file      = "Mary.txt";

uint64 mainChunkSize = (64 * 1024 * 1024);

dword DllMain(HINSTANCE instance, dword reason, LPVOID reserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		Log_Init();
		Log("Session started.");
		if (!Memory_Init())
		{
			return 0;
		}
		Config_Init();
		Cosmetics_Color_AdjustConfig();
		LoadConfig();
		Hooks_Init();

		FMOD_Init();







		System_Actor_Init();
		System_Actor_Toggle();
		System_Animation_Init();
		System_Cache_Init();

		System_Camera_ToggleInvertX(Config.System.Camera.invertX);

		Event_Init();
		Event_ToggleSkipIntro(Config.System.Event.skipIntro);
		Event_ToggleSkipCutscenes(Config.System.Event.skipCutscenes);




		System_File_Init();





		System_Input_extend = Config.Game.Multiplayer.enable;
		System_Input_Init();


		// @Todo: Move to Event.

		System_Media_Init();





		System_Sound_Init();

		System_Weapon_Init();
		System_Weapon_Toggle();
		System_Window_ToggleForceFocus(Config.System.Window.forceFocus);

		Game_Arcade_Toggle(Config.Game.Arcade.enable);
		//Game_Attack_Init();



		Game_Dante_Init();

		Game_Doppelganger_Init();
		Game_Doppelganger_ToggleUseEXVersion(Config.Game.Doppelganger.useEXVersion);




		////Game_Dante_Rebellion_ToggleInfiniteSwordPierce(Config.Game.Dante.Rebellion.infiniteSwordPierce);
		////Game_Dante_EbonyIvory_ToggleFoursomeTime(Config.Game.Dante.EbonyIvory.foursomeTime);
		////Game_Dante_EbonyIvory_ToggleInfiniteRainStorm(Config.Game.Dante.EbonyIvory.infiniteRainStorm);
		////Game_Dante_Artemis_ToggleSwap(Config.Game.Dante.Artemis.swap);
		////Game_Dante_Artemis_ToggleInstant(Config.Game.Dante.Artemis.instant);
		////Game_Dante_AirHike_ToggleCoreAbility(Config.Game.Dante.AirHike.coreAbility);
		////Game_Dante_CrazyCombo_SetLevelMultiplier(Config.Game.Dante.CrazyCombo.levelMultiplier);
		//Game_Dante_WeaponSwitchTimeout_MeleeToggle(Config.Game.Dante.WeaponSwitchTimeout.melee);
		//Game_Dante_WeaponSwitchTimeout_RangedToggle(Config.Game.Dante.WeaponSwitchTimeout.ranged);
		////Game_Mobility_Init();
		////Game_Mobility_Toggle(Config.Game.Mobility.enable);
		////Game_Other_Init();
		////Game_Other_Toggle(Config.Game.Other.enable);
		////Game_ResetMotionState_Init();




		// @Todo: Move to root.

		//Game_Speed_Init();
		//Game_Speed_Toggle(Config.Game.Speed.enable);



		//Game_Style_Init();
		//Game_Style_Doppelganger_ToggleUseEXVersion(Config.Game.Style.Doppelganger.useEXVersion);
		Game_StyleSwitcher_Init();
		Game_StyleSwitcher_Toggle(Config.Game.StyleSwitcher.enable);

		////// @Bug: If module is disabled, but any of these options are true, will cause problems.
		////// @Todo: Add enable check to all multi-module sections.

		Game_Training_ToggleInfiniteHitPoints(Config.Game.Training.infiniteHitPoints);
		Game_Training_ToggleInfiniteMagicPoints(Config.Game.Training.infiniteMagicPoints);
		Game_Training_ToggleDisableTimer(Config.Game.Training.disableTimer);
		////Game_Vergil_Init();
		////Game_Vergil_ForceEdge_ToggleInfiniteRoundTrip(Config.Game.Vergil.ForceEdge.infiniteRoundTrip);
		////Game_Vergil_SummonedSwords_ToggleChronoSwords(Config.Game.Vergil.SummonedSwords.chronoSwords);
		////Game_Vergil_WeaponSwitchTimeout_MeleeToggle(Config.Game.Vergil.WeaponSwitchTimeout.melee);
		Game_WeaponSwitcher_Init();
		Game_WeaponSwitcher_Toggle(Config.Game.WeaponSwitcher.enable);
		if (Config.Game.WeaponSwitcher.enable)
		{
			Config.Cosmetics.Weapon.instantModelUpdate = true;
			SaveConfig();
		}
		Cosmetics_Color_Init();
		Cosmetics_Color_Toggle(Config.Cosmetics.Color_enable);
		Cosmetics_Dante_Init();
		Cosmetics_Dante_ToggleHideBeowulf(Config.Cosmetics.Dante.hideBeowulf);
		Cosmetics_Other_Init();
		Cosmetics_Other_ToggleNoDevilForm(Config.Cosmetics.Other.noDevilForm);
		Cosmetics_Vergil_ToggleHideBeowulf(Config.Cosmetics.Vergil.hideBeowulf);
		Cosmetics_Weapon_Init();
		Cosmetics_Weapon_ToggleInstantModelUpdate(Config.Cosmetics.Weapon.instantModelUpdate);

		//Write<word>((appBaseAddr + 0x88517), 0xF390); // Hit Points Sub Full
		//Write<byte>((appBaseAddr + 0x1AA791), 0xEB);  // Skip Orb Notifications
		//vp_memset((appBaseAddr + 0x1F2A38), 0x90, 5); // Idle Timer Sub Dante
		//vp_memset((appBaseAddr + 0x1F29AE), 0x90, 5); // Idle Timer Sub Vergil
	}
	return 1;
}
