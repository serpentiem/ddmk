

// @Cleanup







export module Global;

import Core;
import Core_Input;

#include "../Core/Macros.h"




import Windows;
import DXGI;
import D3D10;
import D3D11;
import DI8;
import XI;

using namespace Windows;

import Vars;

#define debug false







namespaceStart(DXGI);

export IDXGISwapChain * swapChain = 0;

namespaceEnd();



namespaceStart(D3D10);

export ID3D10Device           * device           = 0;
export ID3D10RenderTargetView * renderTargetView = 0;

namespaceEnd();



namespaceStart(D3D11);

export ID3D11Device           * device           = 0;
export ID3D11DeviceContext    * deviceContext    = 0;
export ID3D11RenderTargetView * renderTargetView = 0;

namespaceEnd();



export Keyboard keyboard = {};
export Mouse    mouse    = {};
export Gamepad  gamepad  = {};










export namespaceStart(XI);

XINPUT_STATE state = {};

namespaceEnd();








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





export bool g_show     = false;
export bool g_lastShow = false;
export bool g_showMain = false;
export bool g_showShop = false;





export float g_shopTimer   = 0;
export float g_shopTimeout = 100; // in ms







export bool g_missionSelectForceConfirm = false;




export float g_hitPoints  [PLAYER_COUNT] = {};
export float g_magicPoints[PLAYER_COUNT] = {};















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




export new_size_t g_saveIndex     = 0;
export new_size_t g_lastSaveIndex = 0;



export uint32 g_secretMission = 0;



export void ClearGlobalSecretMission()
{
	LogFunction();

	g_secretMission = 0;
}

export void SetGlobalSecretMission()
{
	IntroduceEventData(return);
	IntroduceMainActorData(actorData, return);

	LogFunction();



	auto & room = eventData.room;
	auto & x    = actorData.position.x;
	auto & y    = actorData.position.y;
	auto & z    = actorData.position.z;



	g_secretMission =
	(
		(room == 5) &&
		(x >= 5300) &&
		(x <= 5500) &&
		(z >= 2700) &&
		(z <= 3000)
	) ? 1 :
	(
		(room == 113) &&
		(x >= 2700) &&
		(x <= 3000) &&
		(z >= 1500) &&
		(z <= 1700)
	) ? 2 :
	(
		(room == 127) &&
		(x >= 2900) &&
		(x <= 3100) &&
		(z >= 1200) &&
		(z <= 1400)
	) ? 3 :
	(
		(room == 300) &&
		(x >= 5100) &&
		(x <= 5300) &&
		(z >= -200) &&
		(z <= 0)
	) ? 4 :
	(
		(room == 209) &&
		(x >= 1800) &&
		(x <= 2200) &&
		(z >= 2600) &&
		(z <= 3000)
	) ? 5 :
	(
		(room == 206) &&
		(x >= 10200) &&
		(x <= 10400) &&
		(z >= 7000) &&
		(z <= 7200)
	) ? 6 :
	(
		(room == 212) &&
		(x >= 2200) &&
		(x <= 2500) &&
		(z >= 3000) &&
		(z <= 3300)
	) ? 7 :
	(
		(room == 230) &&
		(x >= 3500) &&
		(x <= 3800) &&
		(z >= 3400) &&
		(z <= 3600)
	) ? 8 :
	(
		(room == 233) &&
		(x >= 2800) &&
		(x <= 3100) &&
		(z >= 1000) &&
		(z <= 1300)
	) ? 9 :
	(
		(room == 146) &&
		(x >= 3500) &&
		(x <= 4000) &&
		(z >= 2400) &&
		(z <= 2600)
	) ? 10 :
	(
		(room == 140) &&
		(x >= 2300) &&
		(x <= 2600) &&
		(z >= 2300) &&
		(z <= 2600)
	) ? 11 :
	(
		(room == 402) &&
		(x >= 2200) &&
		(x <= 2500) &&
		(z >= -3300) &&
		(z <= -3000)
	) ? 12 :
	0;
}
































// export bool g_isSecretMission = false;


export bool g_noTeleport = false;




/*

((mission == 4) && (nextRoom == 5)) ? 1 :
((mission == 4) && (nextRoom == 5)) ? 2 :
((mission == 4) && (nextRoom == 5)) ? 3 :
0;

g_isSecretMission =
((mission == 4) && (nextRoom == 5)) ||
((mission == 4) && (nextRoom == 5)) ||
((mission == 4) && (nextRoom == 5));


(
	(mission == 4) &&
	(nextRoom == 5)
) ||



*/





