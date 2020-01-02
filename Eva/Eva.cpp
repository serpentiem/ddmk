#include "../Core/Core.h"

#include "Config.h"
#include "Hooks.h"
//#include "Speed.h"

#include "System/Actor.h"
#include "System/Event.h"
#include "System/Graphics.h"
#include "System/Window.h"

#include "Game/Arcade.h"
#include "Game/BossRush.h"
#include "Game/Dante.h"
#include "Game/LockOn.h"
#include "Game/ResetMotionState.h"
#include "Game/Training.h"
#include "Game/WeaponSwitcher.h"

const char * Log_directory = "logs";
const char * Log_file      = "Eva.txt";

uint64 mainChunkSize = (64 * 1024 * 1024);

DWORD DllMain(HINSTANCE instance, DWORD reason, LPVOID reserved)
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
		LoadConfig();
		Hooks_Init();

		//Speed_Init();
		//Speed_Update(Config);

		System_Actor_Init();
		System_Event_Init();

		System_Graphics_UpdateFrameRate(Config);


		System_Window_ToggleForceFocus(Config.System.Window.forceFocus);

		Game_Arcade_Toggle(Config.Game.Arcade.enable);
		Game_BossRush_Toggle(Config.Game.BossRush.enable);
		Game_Dante_Init();
		Game_Dante_ForceEdge_ToggleUnlockStinger(Config.Game.Dante.ForceEdge.unlockStinger);
		Game_Dante_ForceEdge_ToggleUnlockRoundTrip(Config.Game.Dante.ForceEdge.unlockRoundTrip);
		Game_Dante_Sparda_ToggleUnlockDevilTrigger(Config.Game.Dante.Sparda.unlockDevilTrigger);
		Game_Dante_Sparda_ToggleForceLoadAssets(Config.Game.Dante.Sparda.forceLoadAssets);
		Game_Dante_Yamato_ToggleUnlock(Config.Game.Dante.Yamato.unlock);
		Game_Dante_AirHike_ToggleCoreAbility(Config.Game.Dante.AirHike.coreAbility);
		Game_LockOn_Init();
		Game_LockOn_Toggle(Config.Game.LockOn.enable);
		Game_ResetMotionState_Init();
		Game_Training_ToggleInfiniteHitPoints(Config.Game.Training.infiniteHitPoints);
		Game_Training_ToggleInfiniteMagicPoints(Config.Game.Training.infiniteMagicPoints);
		Game_Training_ToggleDisableTimer(Config.Game.Training.disableTimer);
		Game_WeaponSwitcher_Init();
		Game_WeaponSwitcher_Toggle(Config.Game.WeaponSwitcher.enable);





		//Write<BYTE>((appBaseAddr + 0x4FA2B), 0x8A);   // Hit Points Sub Full
		//vp_memset((appBaseAddr + 0x3F8D18), 0x90, 2); // Disable Main Menu Video Countdown
		//vp_memset((appBaseAddr + 0x2C64D7), 0x90, 4); // Disable Player Idle Timer Sub
		//Game::Training::ToggleInfiniteMagicPoints(true);
		// Force Sparda Devil
		//vp_memset((appBaseAddr + 0x2C56F1), 0x90, 24);
		//vp_memset((appBaseAddr + 0x2C5697), 0x90, 2);
		//Write<WORD>((appBaseAddr + 0x2C56A0), 0x8B90);
		//vp_memset((appBaseAddr + 0x2C56B5), 0x90, 3);
		//vp_memset((appBaseAddr + 0x2C56AC), 0x90, 2);
		//vp_memset((appBaseAddr + 0x2C56C3), 0x90, 2);
		//Write<BYTE>((appBaseAddr + 0x2C56CC), 0xEB);
		//vp_memset((appBaseAddr + 0x2C57B0), 0x90, 6);
		//vp_memset((appBaseAddr + 0x2C57D5), 0x90, 2);
		//vp_memset((appBaseAddr + 0x2C57E2), 0x90, 2);
		//vp_memset((appBaseAddr + 0x2C5A8B), 0x90, 2);
		//Write<BYTE>((appBaseAddr + 0x2C5A94), 0xEB);
		//vp_memset((appBaseAddr + 0x2C5B10), 0x90, 2);
		//Write<BYTE>((appBaseAddr + 0x2C5B1C), 0xEB);








	}
	return 1;
}
