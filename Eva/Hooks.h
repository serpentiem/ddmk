#pragma once
#include "../Core/Core.h"
#include "../Core/ImGui_D3D11.h"
#include "../Core/ImGui_DirectInput8.h"
#include "../Core/ImGui_User.h"

#include <d3d11.h>
#define DIRECTINPUT_VERSION 0x800
#include <dinput.h>
#include <dxgi.h>
#include "../ImGui/imgui.h"
#include <Xinput.h>

#include "Config.h"
#include "GUI.h"
#include "Hotkeys.h"
#include "Pause.h"

#include "System/Message.h"
#include "System/Window.h"

void Hooks_Init();
