#pragma once
#include "../Core/Core.h"
#include "../Windows/Windows.h"
#include <d3d11.h>
#include <dxgi.h>
#define DIRECTINPUT_VERSION 0x800
#include <dinput.h>
#include <Xinput.h>
#include "../ImGui/imgui.h"
#include "ImGui_User.h"
#include "ImGui_D3D11.h"
#include "ImGui_DirectInput8.h"
#include "Config.h"
#include "System/Window.h"
#include "Pause.h"
#include "Hotkeys.h"
#include "System/Message.h"
#include "GUI.h"

namespace Hooks
{
	void Init();
}
