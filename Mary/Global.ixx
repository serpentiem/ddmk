

// @Cleanup







export module Global;

import Core;

#include "../Core/Macros.h"

import Windows;
import DXGI;
import D3D10;
import D3D11;
import DI8;

using namespace Windows;

import Vars;

#define debug false









export namespace DXGI
{
	IDXGISwapChain * swapChain = 0;
}

export namespace D3D10
{
	ID3D10Device           * device           = 0;
	ID3D10RenderTargetView * renderTargetView = 0;
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




export uint8 g_scene                 = 0;

export bool g_eventRun[EVENT::COUNT] = {};












export bool  g_quicksilver           = false;
export bool  g_disableCameraRotation = false;




export bool g_haywireNeoGenerator = false;













export Vector<byte8 *> g_playerActorBaseAddrs = {};




export NewActorData g_defaultNewActorData[ENTITY_COUNT] = {};
export NewActorData g_newActorData[PLAYER_COUNT][CHARACTER_COUNT][ENTITY_COUNT] = {};


export void ClearActorData()
{
	LogFunction();

	g_playerActorBaseAddrs.Clear();

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



export bool g_missionSelectForceConfirm = false;




export float g_hitPoints  [PLAYER_COUNT] = {};
export float g_magicPoints[PLAYER_COUNT] = {};









// // @Remove

// export bool g_visible = false;
// export float g_characterSwitchTimeout[4] = {};
// export uint32 g_eventNevan = 0;
// export bool g_setEventNevan = false;



// export namespaceStart(BossVergil);

// uint32 variant = 0;

// namespaceEnd();


// // uint32 g_bossVergilVariant = 0;
// // uint32 g_variantBossVergil = 0;










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








