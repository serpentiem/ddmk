





export module Global;

import Core;

#include "../Core/Macros.h"

import Windows;
import DXGI;
import D3D10;
import DI8;

import Steam;
import Vars;

using namespace Windows;
using namespace DXGI;
using namespace D3D10;
using namespace DI8;


#define debug false

// #include "Macros.h"





export auto ValidateCharacter(uint32 character)
{
	if (character >= CHARACTER::COUNT)
	{
		character = 0;
	}

	return character;
}

export auto ValidateCostume
(
	uint32 character,
	uint32 costume
)
{
	if
	(
		(costume >= COSTUME::COUNT) ||
		(
			(
				(character == CHARACTER::TRISH) ||
				(character == CHARACTER::LADY )
			) &&
			(
				(
					(costume == 1) &&
					!IsDLCInstalled(DLC::LADY_TRISH_COSTUMES)
				) ||
				(costume == 2)
			)
		)
	)
	{
		costume = 0;
	}

	return costume;
}







// export uint32 g_room     = 0;
// export uint32 g_position = 0;



export uint8 g_scene                 = 0;




export namespace DXGI
{
	IDXGISwapChain * swapChain = 0;
}

export namespace D3D10
{
	ID3D10Device           * device           = 0;
	ID3D10RenderTargetView * renderTargetView = 0;
}









export namespace DI8
{
	IDirectInput8W       * deviceInterface = 0;
	IDirectInputDevice8W * mouse           = 0;
	DIMOUSESTATE2          mouseState      = {};
}

export vec2 g_windowSize = {};
export vec2 g_clientSize = {};
export vec2 g_renderSize = {};









// @Todo: Add to Core.
export POINT GetWindowSize(HWND windowHandle)
{
	POINT point = {};
	RECT  rect  = {};

	if (!windowHandle)
	{
		return point;
	}

	GetWindowRect
	(
		windowHandle,
		&rect
	);

	point.x = (rect.right  - rect.left);
	point.y = (rect.bottom - rect.top );

	return point;
}

export POINT GetClientSize(HWND windowHandle)
{
	POINT point = {};
	RECT  rect  = {};
	RECT  rect2 = {};

	if (!windowHandle)
	{
		return point;
	}

	GetWindowRect
	(
		appWindow,
		&rect
	);

	auto style = GetWindowLongA
	(
		appWindow,
		GWL_STYLE
	);

	AdjustWindowRect
	(
		&rect2,
		style,
		0
	);

	rect.left   -= rect2.left;
	rect.top    -= rect2.top;
	rect.right  -= rect2.right;
	rect.bottom -= rect2.bottom;

	point.x = (rect.right  - rect.left);
	point.y = (rect.bottom - rect.top );

	return point;
}





export void UpdateGlobalWindowSize()
{
	if (!appWindow)
	{
		return;
	}

	auto size = GetWindowSize(appWindow);

	g_windowSize =
	{
		static_cast<float>(size.x),
		static_cast<float>(size.y)
	};

	Log
	(
		"%s %g %g",
		FUNC_NAME,
		g_windowSize.x,
		g_windowSize.y
	);
}

export void UpdateGlobalClientSize()
{
	if (!appWindow)
	{
		return;
	}

	auto size = GetClientSize(appWindow);

	g_clientSize =
	{
		static_cast<float>(size.x),
		static_cast<float>(size.y)
	};

	Log
	(
		"%s %g %g",
		FUNC_NAME,
		g_clientSize.x,
		g_clientSize.y
	);
}

export void UpdateGlobalRenderSize
(
	uint32 width,
	uint32 height
)
{
	g_renderSize =
	{
		static_cast<float>(width),
		static_cast<float>(height)
	};

	Log
	(
		"%s %g %g",
		FUNC_NAME,
		g_renderSize.x,
		g_renderSize.y
	);
}



export void GetWindowPos
(
	HWND window,
	POINT & point
)
{
	if (!window)
	{
		return;
	}

	RECT rect = {};

	GetWindowRect
	(
		window,
		&rect
	);

	point.x = rect.left;
	point.y = rect.top;
}







export bool g_update3D = false;



































// export uint8 g_scene                 = 0;
// export bool  g_quicksilver           = false;
// export bool  g_disableCameraRotation = false;

// //export uint32 g_actorMode = 0;

// export bool g_haywireNeoGenerator = false;


export float g_frameRateMultiplier = 1.0f;






// // @Remove
// export bool g_resetBossVergil[PLAYER_COUNT] = {};




//export Vector<byte8 *> g_playerActorBaseAddrs = {};




export NewActorData g_newActorData[PLAYER::COUNT] = {};



// //export Vector<byte8 *> g_enemyActorBaseAddrs = {};


// export NewActorData g_defaultNewActorData[ENTITY_COUNT] = {};
// export NewActorData g_newActorData[PLAYER_COUNT][CHARACTER_COUNT][ENTITY_COUNT] = {};


// export void ClearActorData()
// {
// 	LogFunction();

// 	g_playerActorBaseAddrs.Clear();
// 	//g_enemyActorBaseAddrs.Clear();

// 	SetMemory
// 	(
// 		g_defaultNewActorData,
// 		0,
// 		sizeof(g_defaultNewActorData)
// 	);

// 	SetMemory
// 	(
// 		g_newActorData,
// 		0,
// 		sizeof(g_newActorData)
// 	);
// }










// // @Research: Could add out of range handling.
// export auto & GetNewActorData
// (
// 	uint8 playerIndex,
// 	uint8 characterIndex,
// 	uint8 entityIndex
// )
// {
// 	return g_newActorData[playerIndex][characterIndex][entityIndex];
// }








// export uint8 g_helperIndices[CHANNEL::MAX] = {};

export bool g_show               = false;
export bool g_lastShow           = false;
export bool g_showItemWindow     = false;
export bool g_lastShowItemWindow = false;




export void ToggleSkipIntro(bool enable)
{
	LogFunction(enable);

	static bool run = false;



	// Force main menu scene instead of autosave scene.
	{
		auto addr = (appBaseAddr + 0x10B1E0);
		constexpr size_t size = 6;
		/*
		dmc4.exe+10B1E0 - C7 06 20FF0101 - mov [esi],dmc4.exe+C1FF20
		dmc4.exe+10B1E6 - E8 A54F4F00    - call dmc4.exe+600190
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			Write<byte8 *>((addr + 2), (appBaseAddr + 0xC27DC0));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x10B246);
		constexpr size_t size = 6;
		/*
		dmc4.exe+10B246 - C7 06 20FF0101 - mov [esi],dmc4.exe+C1FF20
		dmc4.exe+10B24C - 85 C9          - test ecx,ecx
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			Write<byte8 *>((addr + 2), (appBaseAddr + 0xC27DC0));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}



	run = true;
}


































// // export bool g_pauseForceQuitMission     = false;
// export bool g_missionSelectForceConfirm = false;




// export float g_hitPoints  [PLAYER_COUNT] = {};
// export float g_magicPoints[PLAYER_COUNT] = {};









// // @Remove
// export float g_timeout = 0;
// export bool g_visible = false;
// export float g_characterSwitchTimeout[4] = {};
// export uint32 g_eventNevan = 0;
// export bool g_setEventNevan = false;



// export namespaceStart(BossVergil);

// uint32 variant = 0;

// namespaceEnd();


// // uint32 g_bossVergilVariant = 0;
// // uint32 g_variantBossVergil = 0;










// // @Todo: Update.
// export void ToggleSkipIntro(bool enable)
// {
// 	LogFunction(enable);

// 	WriteAddress((appBaseAddr + 0x2383F2), (enable) ? (appBaseAddr + 0x2383F8) : (appBaseAddr + 0x238527), 6); // Skip Message
// 	WriteAddress((appBaseAddr + 0x241789), (enable) ? (appBaseAddr + 0x24178B) : (appBaseAddr + 0x2417A6), 2); // Skip Video
// 	Write<uint8>((appBaseAddr + 0x238704), (enable) ? 0 : 1); // Hide Rebellion

// 	// Disable Video Timer
// 	{
// 		auto dest = (appBaseAddr + 0x243531);
// 		if (enable)
// 		{
// 			SetMemory
// 			(
// 				dest,
// 				0x90,
// 				2,
// 				MemoryFlags_VirtualProtectDestination
// 			);
// 		}
// 		else
// 		{
// 			constexpr byte8 buffer[] =
// 			{
// 				0xFF, 0xC8, //dec eax
// 			};
// 			CopyMemory
// 			(
// 				dest,
// 				buffer,
// 				sizeof(buffer),
// 				MemoryFlags_VirtualProtectDestination
// 			);
// 		}
// 	}
// }




// export void ToggleSkipCutscenes(bool enable)
// {
// 	LogFunction(enable);

// 	WriteAddress((appBaseAddr + 0x238CCA), (enable) ? (appBaseAddr + 0x238CD0) : (appBaseAddr + 0x238E62), 6);
// 	/*
// 	dmc3.exe+238CCA - 0F85 92010000 - jne dmc3.exe+238E62
// 	dmc3.exe+238CD0 - 8B 43 1C      - mov eax,[rbx+1C]
// 	*/

// 	WriteAddress((appBaseAddr + 0x23918A), (enable) ? (appBaseAddr + 0x23918C) : (appBaseAddr + 0x2391A4), 2);
// 	/*
// 	dmc3.exe+23918A - 75 18    - jne dmc3.exe+2391A4
// 	dmc3.exe+23918C - 8B 43 1C - mov eax,[rbx+1C]
// 	*/
// }








// // @Remove

// // @Todo: Re-evaluate reasons for these being in here.
// // export template <typename T>
// // void ActorForAll(T & func)
// // {
// // 	old_for_all(uint64, actorIndex, g_playerActorBaseAddrs.count)
// // 	{
// // 		auto actorBaseAddr = g_playerActorBaseAddrs[actorIndex];

// // 		if (func(actorBaseAddr))
// // 		{
// // 			break;
// // 		}
// // 	}
// // }

// // export template <typename T>
// // void EnemyForAll(T & func)
// // {
// // 	// Not necessary. Some enemies don't even use this. Gigapede for example.

// // 	// auto firstBaseAddr = *reinterpret_cast<byte8 **>(appBaseAddr + 0xCF2550);
// // 	// auto lastBaseAddr = *reinterpret_cast<byte8 **>(appBaseAddr + 0xCF2750);
// // 	auto pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);

// // 	if
// // 	(
// // 		// !firstBaseAddr ||
// // 		// !lastBaseAddr ||
// // 		!pool ||
// // 		!pool[8]
// // 	)
// // 	{
// // 		return;
// // 	}

// // 	auto & count = *reinterpret_cast<uint32 *>(pool[8] + 0x28);
// // 	auto dataAddr = reinterpret_cast<EnemyVectorDataMetadata *>(pool[8] + 0x48);

// // 	old_for_all(uint32, index, 50)
// // 	{
// // 		auto & data = dataAddr[index];

// // 		if
// // 		(
// // 			!data.baseAddr
// // 			// (data.baseAddr < firstBaseAddr) ||
// // 			// (data.baseAddr > lastBaseAddr)
// // 		)
// // 		{
// // 			continue;
// // 		}

// // 		if (func(data.baseAddr))
// // 		{
// // 			break;
// // 		}
// // 	}
// // }



export bool InGame()
{
	if (g_scene != SCENE::GAME)
	{
		return false;
	}

	IntroduceEventData(return false);

	if (eventData.event != EVENT::MAIN)
	{
		return false;
	}

	return true;
}


// export bool InGame()
// {
// 	if (g_scene != SCENE::GAME)
// 	{
// 		return false;
// 	}

// 	IntroduceEventData(return false);

// 	if (eventData.event != EVENT::MAIN)
// 	{
// 		return false;
// 	}

// 	return true;
// }




// export auto & IsTurbo()
// {
// 	return *reinterpret_cast<bool *>(appBaseAddr + 0xD6CEA9);
// }

// export auto & InCutscene()
// {
// 	return *reinterpret_cast<bool *>(appBaseAddr + 0x5D113D);
// }

// export bool InCredits()
// {
// 	auto pool = *reinterpret_cast<byte8 **>(appBaseAddr + 0xC90E28);
// 	if (!pool)
// 	{
// 		return false;
// 	}

// 	return *reinterpret_cast<bool *>(pool + 0x11);
// }


// // @Remove

// // export bool IsBorderless()
// // {
// // 	return *reinterpret_cast<bool *>(appBaseAddr + 0x5EA130 + 0x679);
// // 	/*
// // 	dmc3.exe+47DEA - 48 8D 0D 3F235A00 - lea rcx,[dmc3.exe+5EA130]
// // 	dmc3.exe+36E60 - 0FB6 81 79060000  - movzx eax,byte ptr [rcx+00000679]
// // 	*/
// // }


// // @Research: Consider SCENE::MISSION_START as well.
// // export bool IsActorConfigScene()
// // {
// // 	if
// // 	(
// // 		(g_scene == SCENE::MAIN          ) ||
// // 		(g_scene == SCENE::MISSION_SELECT)
// // 	)
// // 	{
// // 		return true;
// // 	}

// // 	return false;
// // }









