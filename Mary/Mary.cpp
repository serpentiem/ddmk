#include "../Core/Core.h"

import Actor;
import Arcade;
import Camera;
import Config;
import Event;
import File;
import Graphics;
import GUI;
import Hooks;
import HUD;
import Internal;
import Memory;
import Model;
import Scene;
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

		if (!Core_Memory_Init((64 * 1024 * 1024)))
		{
			Log("Core_Memory_Init failed.");
			return 0;
		}

		Config_Init("configs", "Mary.bin");
		LoadConfig();




		

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

		Graphics_Init();


		Actor_Init();
		Actor_Toggle(activeConfig.Actor.enable);


		//Camera_Init();

		//Color_Init();


		Event_Init();




		Event_ToggleSkipIntro    (activeConfig.Event.skipIntro);
		//Event_ToggleSkipCutscenes(activeConfig.Event.skipCutscenes);
		Event_ToggleSkipCutscenes(false);
		//FMOD_Init();
		Hooks_Init();
		//Internal_Init();
		//Speed_Init();
		//Speed_Update(Config);

		HUD_Init();


		Scene_Init();

		Speed_Init();


		Training_ToggleInfiniteHitPoints  (activeConfig.Training.infiniteHitPoints  );
		Training_ToggleInfiniteMagicPoints(activeConfig.Training.infiniteMagicPoints);
		Training_ToggleDisableTimer       (activeConfig.Training.disableTimer       );


		//Speed_Init();



		Camera_ToggleInvertX(activeConfig.Camera.invertX);


		//Dante_Init();



		//Update_Init();


		//Mobility_Toggle(true);




		//Mobility::Init();
		//Mobility::Toggle(true);






		//Model_Init();

		






		// OrbReach_Init();
		// OrbReach_Update();

		//return 1;



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














		//System_Animation_Init();



		//Log("pl021_00_4[11] %.16llX", File_staticFiles[pl021_00_4][11]);
		//Log("pl000_00_5[20] %.16llX", File_staticFiles[pl000_00_5][20]);
		//Log("pl000_00_3[14] %.16llX", File_staticFiles[pl000_00_3][14]);




		
		//System_Cache_Init();










		//System_Camera_ToggleInvertX(activeConfig.System.Camera.invertX);
		//System_Graphics_UpdateFrameRate(Config);
		//System_HUD_Init();

		//System_Input_Init();
		//System_Input_ToggleRangeExtension  (activeConfig.Game.Multiplayer.enable);
		//System_Input_ToggleMultiplayerFixes(activeConfig.Game.Multiplayer.enable);

		//System_Input_ToggleRangeExtension  (true);
		//System_Input_ToggleMultiplayerFixes(true);



		//System_Media_Init();
		//System_Motion_Init();
		//System_Sound_Init();
		//System_Weapon_Init();
		//System_Weapon_ToggleUpdateWeapon(true);
		//System_Weapon_ToggleDoppelgangerFixes(true);
		//System_Weapon_ToggleModelFixes(true);






		Window_ToggleForceFocus(true);

		//Arcade_UpdateModeIndex();
		Arcade_Toggle(activeConfig.Arcade.enable);





		//Game_Attack_Init();
		//Game_Dante_Init();
		//Game_Dante_Rebellion_ToggleInfiniteSwordPierce(activeConfig.Game.Dante.Rebellion.infiniteSwordPierce);
		//Game_Dante_EbonyIvory_ToggleFoursomeTime      (activeConfig.Game.Dante.EbonyIvory.foursomeTime      );
		//Game_Dante_EbonyIvory_ToggleInfiniteRainStorm (activeConfig.Game.Dante.EbonyIvory.infiniteRainStorm );
		//Game_Dante_Artemis_ToggleSwap                 (activeConfig.Game.Dante.Artemis.swap                 );
		//Game_Dante_Artemis_ToggleInstant              (activeConfig.Game.Dante.Artemis.instant              );
		//Game_Dante_AirHike_ToggleCoreAbility          (activeConfig.Game.Dante.AirHike.coreAbility          );
		//Game_Dante_CrazyCombo_SetLevelMultiplier      (activeConfig.Game.Dante.CrazyCombo.levelMultiplier   );
		//Game_Dante_WeaponSwitchTimeout_Melee_Toggle   (activeConfig.Game.Dante.WeaponSwitchTimeout.melee    );
		//Game_Dante_WeaponSwitchTimeout_Ranged_Toggle  (activeConfig.Game.Dante.WeaponSwitchTimeout.ranged   );
		//Game_Doppelganger_Init();
		//Game_Doppelganger_ToggleEnableDevilTrigger(activeConfig.Game.Doppelganger.enableDevilTrigger);
		//Game_Mobility_Init();
		//Game_Mobility_Toggle(activeConfig.Game.Mobility.enable);
		//Game_Other_Init();
		//Game_Other_Toggle(activeConfig.Game.Other.enable);
		//Game_ResetMotionState_UpdateButtonIndex();
		//Game_StyleSwitcher_Init();
		//Game_StyleSwitcher_Toggle(activeConfig.Game.StyleSwitcher.enable);

		//Training_ToggleInfiniteHitPoints  (activeConfig.Game.Training.infiniteHitPoints  );
		//Training_ToggleInfiniteMagicPoints(activeConfig.Game.Training.infiniteMagicPoints);
		//Training_ToggleDisableTimer       (activeConfig.Game.Training.disableTimer       );



		//Game_Vergil_Init();
		//Game_Vergil_ForceEdge_ToggleInfiniteRoundTrip(activeConfig.Game.Vergil.ForceEdge.infiniteRoundTrip);
		//Game_Vergil_SummonedSwords_ToggleChronoSwords(activeConfig.Game.Vergil.SummonedSwords.chronoSwords);
		//Game_Vergil_WeaponSwitchTimeout_MeleeToggle  (activeConfig.Game.Vergil.WeaponSwitchTimeout.melee  );
		//Game_WeaponSwitcher_Init();
		//Game_WeaponSwitcher_Toggle(activeConfig.Game.WeaponSwitcher.enable);

		//Cosmetics_Color_Init();
		//Cosmetics_Color_UpdateColors(Config);
		//Cosmetics_Dante_Init();
		//Cosmetics_Dante_ToggleHideBeowulf(activeConfig.Cosmetics.Dante.Beowulf.hideModel);
		//Cosmetics_Object_Init();

		//Cosmetics_Model_Init();

		//Cosmetics_Other_Init();
		//Cosmetics_Other_ToggleNoDevilForm(activeConfig.Cosmetics.Other.noDevilForm);
		//Cosmetics_Vergil_ToggleHideBeowulf(activeConfig.Cosmetics.Vergil.Beowulf.hideModel);



		//HoboBreak();







		if constexpr (debug)
		{
			// Disable Idle Timer
			vp_memset((appBaseAddr + 0x1F2A38), 0x90, 5); // Dante
			vp_memset((appBaseAddr + 0x1F29AE), 0x90, 5); // Vergil

			// Force Visible HUD
			Write<byte8>((appBaseAddr + 0x27E800), 0xEB);
			Write<byte8>((appBaseAddr + 0x27DF3E), 0xEB);
			Write<byte16>((appBaseAddr + 0x280DB9), 0xE990);

			// Disable Style Rank Sub
			vp_memset((appBaseAddr + 0x27A39C), 0x90, 5);

			// Force Collect Orbs
			WriteAddress((appBaseAddr + 0x1B6597), (appBaseAddr + 0x1B6599), 2);
		}
	}
	return 1;
}
