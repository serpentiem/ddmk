module;
#include "../Core/Core.h"

#include <d3d11.h>

#include "Vars.h"
export module Global;

export bool  g_pause                 = false;
export uint8 g_scene                 = 0;
export bool  g_quicksilver           = false;
export uint8 g_character             = 0;
export uint8 g_costume               = 0;
export bool  g_disableCameraRotation = false;

export ID3D11Device           * D3D11_device           = 0;
export ID3D11DeviceContext    * D3D11_deviceContext    = 0;
export ID3D11RenderTargetView * D3D11_renderTargetView = 0;

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
