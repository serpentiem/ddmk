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




export bool  g_pause                 = false;
export uint8 g_scene                 = 0;
export bool  g_quicksilver           = false;
export bool  g_disableCameraRotation = false;

export Vector<byte8 *> Actor_actorBaseAddrs = {};

export uint8 g_helperIndices[MAX_CHANNEL] = {};


export bool g_showItemWindow = false;
export bool g_lastShowItemWindow = false;




export bool InGame()
{
	if (g_scene != SCENE_GAME)
	{
		return false;
	}

	IntroduceEventData(return false);

	if (eventData.event != EVENT_MAIN)
	{
		return false;
	}

	return true;
}

export auto & GetTurbo()
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









