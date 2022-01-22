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

import Steam;
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



export bool g_show     = false;
export bool g_lastShow = false;
export bool g_showMain = false;
export bool g_showShop = false;



export bool g_update3D = false;

export new_size_t activePlayerIndex = 0;

export uint32 g_position = 0;



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



export uint8 g_scene                 = 0;

export bool g_eventRun[EVENT::COUNT] = {};

export NewActorData g_newActorData[PLAYER::COUNT] = {};



export void ToggleSkipIntro(bool enable)
{
	LogFunction(enable);

	static bool run = false;



	// Force main menu scene instead of autosave scene.
	{
		auto addr = (appBaseAddr + 0x10B1E0);
		constexpr new_size_t size = 6;
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
		constexpr new_size_t size = 6;
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
