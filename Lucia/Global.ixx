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



export bool g_show     = false;
export bool g_lastShow = false;
export bool g_showMain = false;
export bool g_showShop = false;
