// @Cleanup



export module Global;

import Core;

#include "../Core/Macros.h"

import DXGI;
import D3D11;
import DI8;

import Vars;

using namespace DXGI;
using namespace D3D11;
using namespace DI8;


#define debug false

#include "Macros.h"









export namespace DXGI
{
	IDXGISwapChain * swapChain = 0;
}

export namespace D3D11
{
	ID3D11Device           * device           = 0;
	ID3D11DeviceContext    * deviceContext    = 0;
	ID3D11RenderTargetView * renderTargetView = 0;
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

export uint8 g_scene                 = 0;
export bool  g_quicksilver           = false;
export bool  g_disableCameraRotation = false;

//export uint32 g_actorMode = 0;

export bool g_haywireNeoGenerator = false;




export bool g_resetBossVergil[PLAYER_COUNT] = {};




export Vector<byte8 *> g_playerActorBaseAddrs = {};
//export Vector<byte8 *> g_enemyActorBaseAddrs = {};


export NewActorData g_defaultNewActorData[ENTITY_COUNT] = {};
export NewActorData g_newActorData[PLAYER_COUNT][CHARACTER_COUNT][ENTITY_COUNT] = {};


export void ClearActorData()
{
	LogFunction();

	g_playerActorBaseAddrs.Clear();
	//g_enemyActorBaseAddrs.Clear();

	SetMemory
	(
		g_defaultNewActorData,
		0,
		sizeof(g_defaultNewActorData)
	);

	SetMemory
	(
		g_newActorData,
		0,
		sizeof(g_newActorData)
	);
}










// @Research: Could add out of range handling.
export auto & GetNewActorData
(
	uint8 playerIndex,
	uint8 characterIndex,
	uint8 entityIndex
)
{
	return g_newActorData[playerIndex][characterIndex][entityIndex];
}








export uint8 g_helperIndices[CHANNEL::MAX] = {};

export bool g_show               = false;
export bool g_lastShow           = false;
export bool g_showItemWindow     = false;
export bool g_lastShowItemWindow = false;

// export bool g_pauseForceQuitMission     = false;
export bool g_missionSelectForceConfirm = false;





// @Todo: Remove.
export float g_timeout = 0;
export bool g_visible = false;
export float g_characterSwitchTimeout[4] = {};
export uint32 g_eventNevan = 0;
export bool g_setEventNevan = false;



export namespaceStart(BossVergil);

uint32 variant = 0;

namespaceEnd();


// uint32 g_bossVergilVariant = 0;
// uint32 g_variantBossVergil = 0;










// @Todo: Update.
export void ToggleSkipIntro(bool enable)
{
	LogFunction(enable);

	WriteAddress((appBaseAddr + 0x2383F2), (enable) ? (appBaseAddr + 0x2383F8) : (appBaseAddr + 0x238527), 6); // Skip Message
	WriteAddress((appBaseAddr + 0x241789), (enable) ? (appBaseAddr + 0x24178B) : (appBaseAddr + 0x2417A6), 2); // Skip Video
	Write<uint8>((appBaseAddr + 0x238704), (enable) ? 0 : 1); // Hide Rebellion

	// Disable Video Timer
	{
		auto dest = (appBaseAddr + 0x243531);
		if (enable)
		{
			SetMemory
			(
				dest,
				0x90,
				2,
				MemoryFlags_VirtualProtectDestination
			);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0xFF, 0xC8, //dec eax
			};
			CopyMemory
			(
				dest,
				buffer,
				sizeof(buffer),
				MemoryFlags_VirtualProtectDestination
			);
		}
	}
}

export void ToggleSkipCutscenes(bool enable)
{
	LogFunction(enable);

	WriteAddress((appBaseAddr + 0x238CCA), (enable) ? (appBaseAddr + 0x238CD0) : (appBaseAddr + 0x238E62), 6);
	/*
	dmc3.exe+238CCA - 0F85 92010000 - jne dmc3.exe+238E62
	dmc3.exe+238CD0 - 8B 43 1C      - mov eax,[rbx+1C]
	*/

	WriteAddress((appBaseAddr + 0x23918A), (enable) ? (appBaseAddr + 0x23918C) : (appBaseAddr + 0x2391A4), 2);
	/*
	dmc3.exe+23918A - 75 18    - jne dmc3.exe+2391A4
	dmc3.exe+23918C - 8B 43 1C - mov eax,[rbx+1C]
	*/
}










// @Todo: Re-evaluate reasons for these being in here.
export template <typename T>
void ActorForAll(T & func)
{
	old_for_all(uint64, actorIndex, g_playerActorBaseAddrs.count)
	{
		auto actorBaseAddr = g_playerActorBaseAddrs[actorIndex];

		if (func(actorBaseAddr))
		{
			break;
		}
	}
}

export template <typename T>
void EnemyForAll(T & func)
{
	// Not necessary. Some enemies don't even use this. Gigapede for example.

	// auto firstBaseAddr = *reinterpret_cast<byte8 **>(appBaseAddr + 0xCF2550);
	// auto lastBaseAddr = *reinterpret_cast<byte8 **>(appBaseAddr + 0xCF2750);
	auto pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);

	if
	(
		// !firstBaseAddr ||
		// !lastBaseAddr ||
		!pool ||
		!pool[8]
	)
	{
		return;
	}

	auto & count = *reinterpret_cast<uint32 *>(pool[8] + 0x28);
	auto dataAddr = reinterpret_cast<EnemyVectorDataMetadata *>(pool[8] + 0x48);

	old_for_all(uint32, index, 50)
	{
		auto & data = dataAddr[index];

		if
		(
			!data.baseAddr
			// (data.baseAddr < firstBaseAddr) ||
			// (data.baseAddr > lastBaseAddr)
		)
		{
			continue;
		}

		if (func(data.baseAddr))
		{
			break;
		}
	}
}



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

// @Todo: Rename to IsTurbo.
export auto & IsTurbo()
{
	return *reinterpret_cast<bool *>(appBaseAddr + 0xD6CEA9);
}

export auto & InCutscene()
{
	return *reinterpret_cast<bool *>(appBaseAddr + 0x5D113D);
}

export bool InCredits()
{
	auto pool = *reinterpret_cast<byte8 **>(appBaseAddr + 0xC90E28);
	if (!pool)
	{
		return false;
	}

	return *reinterpret_cast<bool *>(pool + 0x11);
}


// export bool IsBorderless()
// {
// 	return *reinterpret_cast<bool *>(appBaseAddr + 0x5EA130 + 0x679);
// 	/*
// 	dmc3.exe+47DEA - 48 8D 0D 3F235A00 - lea rcx,[dmc3.exe+5EA130]
// 	dmc3.exe+36E60 - 0FB6 81 79060000  - movzx eax,byte ptr [rcx+00000679]
// 	*/
// }


// @Research: Consider SCENE::MISSION_START as well.
export bool IsActorConfigScene()
{
	if
	(
		(g_scene == SCENE::MAIN          ) ||
		(g_scene == SCENE::MISSION_SELECT)
	)
	{
		return true;
	}

	return false;
}









