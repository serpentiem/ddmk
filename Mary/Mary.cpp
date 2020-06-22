#include "../Core/Core.h"

#include "Internal.h"

import ModuleName(Actor);
import ModuleName(Arcade);
import ModuleName(Camera);
import ModuleName(Config);
import ModuleName(Dante);
import ModuleName(Event);
import ModuleName(File);
import ModuleName(GUI);
import ModuleName(Hooks);
import ModuleName(HUD);
import ModuleName(Memory);
import ModuleName(Training);
import ModuleName(Update);
import ModuleName(Window);

#ifdef __INTELLISENSE__
#include "Actor.ixx"
#include "Arcade.ixx"
#include "Camera.ixx"
#include "Config.ixx"
#include "Dante.ixx"
#include "Event.ixx"
#include "File.ixx"
#include "GUI.ixx"
#include "Hooks.ixx"
#include "HUD.ixx"
#include "Memory.ixx"
#include "Training.ixx"
#include "Update.ixx"
#include "Window.ixx"
#endif

uint32 DllMain(HINSTANCE instance, uint32 reason, LPVOID reserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		Core_Log_Init("logs", "Mary.txt");
		Log("Session started.");

		Core_Config_Init("configs", "Mary.bin", &Config, sizeof(CONFIG));
		LoadConfig();

		if (!Core_Memory_Init((64 * 1024 * 1024)))
		{
			Log("Core_Memory_Init failed.");
			return 0;
		}



		

		vp_memset((appBaseAddr + 0x5505B5), 0, 23); // Remove FMODGetCodecDescription label.








		if (!Memory_Init())
		{
			Log("Memory_Init failed.");
			return 0;
		}


		Internal_Init();




		Memory_ToggleExtendVectors(true);




		if (!File_Init())
		{
			Log("File_Init failed.");
			return 0;
		}

		Actor_Init();


		//Camera_Init();



		Event_Init();




		Event_ToggleSkipIntro    (Config.System.Event.skipIntro    );
		Event_ToggleSkipCutscenes(Config.System.Event.skipCutscenes);
		//FMOD_Init();
		Hooks_Init();
		//Internal_Init();
		//Speed_Init();
		//Speed_Update(Config);

		HUD_Init();

		Training_ToggleInfiniteHitPoints  (Config.Training.infiniteHitPoints);
		Training_ToggleInfiniteMagicPoints(true);
		Training_ToggleDisableTimer       (true);


		//Speed_Init();



		//Camera_ToggleInvertX(true);


		Dante_Init();



		Update_Init();


		Mobility_Toggle(true);




		//ToggleUpdateWeapon(true);




		//// Order is required.
		//System_Memory_Init();
		//System_Memory_ToggleExtendVectors(true);
		//System_File_Init();





		//System_Actor_Init();
		//System_Actor_ToggleArrayExtension(true);
		//System_Actor_ToggleCreateActorOne(true);


		////System_Actor_ToggleUpdateActor(true);


		//System_Actor_ToggleDoppelgangerFixes(true);
		//System_Actor_ToggleModelFixes(true);
		//System_Actor_ToggleDisableIdleTimer(true);








		// Disable Idle Timer

		{
			vp_memset((appBaseAddr + 0x1F2A38), 0x90, 5); // Dante
			vp_memset((appBaseAddr + 0x1F29AE), 0x90, 5); // Vergil
		}

















		//System_Animation_Init();



		//Log("pl021_00_4[11] %.16llX", File_staticFiles[pl021_00_4][11]);
		//Log("pl000_00_5[20] %.16llX", File_staticFiles[pl000_00_5][20]);
		//Log("pl000_00_3[14] %.16llX", File_staticFiles[pl000_00_3][14]);




		
		//System_Cache_Init();










		//System_Camera_ToggleInvertX(Config.System.Camera.invertX);
		//System_Graphics_UpdateFrameRate(Config);
		//System_HUD_Init();

		//System_Input_Init();
		//System_Input_ToggleRangeExtension  (Config.Game.Multiplayer.enable);
		//System_Input_ToggleMultiplayerFixes(Config.Game.Multiplayer.enable);

		//System_Input_ToggleRangeExtension  (true);
		//System_Input_ToggleMultiplayerFixes(true);



		//System_Media_Init();
		//System_Motion_Init();
		//System_Sound_Init();
		//System_Weapon_Init();
		//System_Weapon_ToggleUpdateWeapon(true);
		//System_Weapon_ToggleDoppelgangerFixes(true);
		//System_Weapon_ToggleModelFixes(true);






		Window_ToggleForceFocus(Config.System.Window.forceFocus);

		Arcade_UpdateModeIndex();
		Arcade_Toggle(Config.Game.Arcade.enable);





		//Game_Attack_Init();
		//Game_Dante_Init();
		//Game_Dante_Rebellion_ToggleInfiniteSwordPierce(Config.Game.Dante.Rebellion.infiniteSwordPierce);
		//Game_Dante_EbonyIvory_ToggleFoursomeTime      (Config.Game.Dante.EbonyIvory.foursomeTime      );
		//Game_Dante_EbonyIvory_ToggleInfiniteRainStorm (Config.Game.Dante.EbonyIvory.infiniteRainStorm );
		//Game_Dante_Artemis_ToggleSwap                 (Config.Game.Dante.Artemis.swap                 );
		//Game_Dante_Artemis_ToggleInstant              (Config.Game.Dante.Artemis.instant              );
		//Game_Dante_AirHike_ToggleCoreAbility          (Config.Game.Dante.AirHike.coreAbility          );
		//Game_Dante_CrazyCombo_SetLevelMultiplier      (Config.Game.Dante.CrazyCombo.levelMultiplier   );
		//Game_Dante_WeaponSwitchTimeout_Melee_Toggle   (Config.Game.Dante.WeaponSwitchTimeout.melee    );
		//Game_Dante_WeaponSwitchTimeout_Ranged_Toggle  (Config.Game.Dante.WeaponSwitchTimeout.ranged   );
		//Game_Doppelganger_Init();
		//Game_Doppelganger_ToggleEnableDevilTrigger(Config.Game.Doppelganger.enableDevilTrigger);
		//Game_Mobility_Init();
		//Game_Mobility_Toggle(Config.Game.Mobility.enable);
		//Game_Other_Init();
		//Game_Other_Toggle(Config.Game.Other.enable);
		//Game_ResetMotionState_UpdateButtonIndex();
		//Game_StyleSwitcher_Init();
		//Game_StyleSwitcher_Toggle(Config.Game.StyleSwitcher.enable);

		//Training_ToggleInfiniteHitPoints  (Config.Game.Training.infiniteHitPoints  );
		//Training_ToggleInfiniteMagicPoints(Config.Game.Training.infiniteMagicPoints);
		//Training_ToggleDisableTimer       (Config.Game.Training.disableTimer       );



		//Game_Vergil_Init();
		//Game_Vergil_ForceEdge_ToggleInfiniteRoundTrip(Config.Game.Vergil.ForceEdge.infiniteRoundTrip);
		//Game_Vergil_SummonedSwords_ToggleChronoSwords(Config.Game.Vergil.SummonedSwords.chronoSwords);
		//Game_Vergil_WeaponSwitchTimeout_MeleeToggle  (Config.Game.Vergil.WeaponSwitchTimeout.melee  );
		//Game_WeaponSwitcher_Init();
		//Game_WeaponSwitcher_Toggle(Config.Game.WeaponSwitcher.enable);

		//Cosmetics_Color_Init();
		//Cosmetics_Color_UpdateColors(Config);
		//Cosmetics_Dante_Init();
		//Cosmetics_Dante_ToggleHideBeowulf(Config.Cosmetics.Dante.Beowulf.hideModel);
		//Cosmetics_Object_Init();

		//Cosmetics_Model_Init();

		//Cosmetics_Other_Init();
		//Cosmetics_Other_ToggleNoDevilForm(Config.Cosmetics.Other.noDevilForm);
		//Cosmetics_Vergil_ToggleHideBeowulf(Config.Cosmetics.Vergil.Beowulf.hideModel);



		//HoboBreak();






	}
	return 1;
}
