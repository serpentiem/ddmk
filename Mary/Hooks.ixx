







module;
#include "../ImGui/imgui.h"
export module Hooks;

import Core;

#include "../Core/Macros.h"

import Windows;
import DXGI;
import D3D11;
import DI8;
import XI;

import Core_ImGui;

import Config;
import Global;
import Graphics;
import GUI;
import Input;
import Window;
import Vars;

using namespace Windows;
using namespace DXGI;
using namespace D3D11;
using namespace DI8;
using namespace XI;

#define debug false

#include "Macros.h"

















POINT GetWindowSize(HWND windowHandle)
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

POINT GetClientSize(HWND windowHandle)
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

















void UpdateGlobalWindowSize()
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

void UpdateGlobalClientSize()
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

void UpdateGlobalRenderSize
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







//namespaceStart(ImGui::DI8);

void UpdateMousePositionMultiplier()
{
	using namespace ImGui::DI8;

	if
	(
		(g_clientSize.x < 1) ||
		(g_clientSize.y < 1) ||
		(g_renderSize.x < 1) ||
		(g_renderSize.y < 1)
	)
	{
		mousePositionMultiplier.x = 1;
		mousePositionMultiplier.y = 1;
	}
	else
	{
		mousePositionMultiplier.x = (g_renderSize.x / g_clientSize.x);
		mousePositionMultiplier.y = (g_renderSize.y / g_clientSize.y);
	}

	Log
	(
		"%s %g %g",
		FUNC_NAME,
		mousePositionMultiplier.x,
		mousePositionMultiplier.y
	);
}

//namespaceEnd();


















template
<
	typename T,
	typename T2
>
void Install
(
	void * dest,
	T & baseFuncAddr,
	T2 & hookFuncAddr
)
{
	auto & funcAddr = *reinterpret_cast<T *>(dest);

	// @Research: Prefer dest and move up.
	protectionHelper.Push
	(
		&funcAddr,
		8
	);

	baseFuncAddr = funcAddr;

	funcAddr = hookFuncAddr;

	protectionHelper.Pop();
}



















#pragma region Windows

namespaceStart(Windows);

typedef WNDPROC WindowProc_t;
typedef decltype(RegisterClassExW) * RegisterClassExW_t;
typedef decltype(CreateWindowExW) * CreateWindowExW_t;

namespaceEnd();



namespaceStart(Base::Windows);

::Windows::WindowProc_t WindowProc = 0;
::Windows::RegisterClassExW_t RegisterClassExW = 0;
::Windows::CreateWindowExW_t CreateWindowExW = 0;

namespaceEnd();



namespaceStart(Hook::Windows);

LRESULT WindowProc
(
	HWND windowHandle,
	UINT message,
	WPARAM wParameter,
	LPARAM lParameter
)
{

	// static UINT lastMessage = 0;


	// if (lastMessage != 0)
	// {
	// 	switch (lastMessage)
	// 	{
	// 		case WM_STYLECHANGED:
	// 		{


	// 		// Log("WM_STYLECHANGED");

	// 		// UpdateGlobalWindowSize();
	// 		// UpdateGlobalClientSize();
	// 		// ImGui::DI8::UpdateMousePositionMultiplier
	// 		// (
	// 		// 	g_clientSize,
	// 		// 	g_renderSize
	// 		// );

	// 		lastMessage = 0;

	// 			break;


	// 		}
	// 	}
	// }




	auto result = ::Base::Windows::WindowProc
	(
		windowHandle,
		message,
		wParameter,
		lParameter
	);

	auto error = GetLastError();









	static bool run = false;
	if (!run)
	{
		run = true;

		Log
		(
			"%s "
			"%llX "
			"%X "
			"%llX "
			"%llX",
			FUNC_NAME,
			windowHandle,
			message,
			wParameter,
			lParameter
		);
	}

	switch (message)
	{
		case WM_SIZE:
		{
			if (!appWindow)
			{
				break;
			}

			auto width = static_cast<uint16>(lParameter);
			auto height = static_cast<uint16>(lParameter >> 16);

			Log("WM_SIZE %u %u", width, height);

			UpdateGlobalWindowSize();
			UpdateGlobalClientSize();
			UpdateMousePositionMultiplier();

			break;
		}
		case WM_STYLECHANGED:
		{
			if (!appWindow)
			{
				break;
			}

			auto style = GetWindowLongA
			(
				appWindow,
				GWL_STYLE
			);

			Log("WM_STYLECHANGED %X", style);

			UpdateGlobalWindowSize();
			UpdateGlobalClientSize();
			UpdateMousePositionMultiplier();

			break;
		}
		// case WM_SHOWWINDOW:
		// {
		// 	Log("WM_SHOWWINDOW");





		// 	break;
		// }
		case WM_SETCURSOR:
		{
			ImGui::UpdateMouseCursor(windowHandle);

			break;
		}
		case WM_CHAR:
		{
			auto character = static_cast<uint16>(wParameter);

			auto & io = ImGui::GetIO();

			io.AddInputCharacter(character);

			break;
		}
	}

	// return ::Base::Windows::WindowProc
	// (
	// 	windowHandle,
	// 	message,
	// 	wParameter,
	// 	lParameter
	// );


	SetLastError(error);

	return result;



}

ATOM RegisterClassExW(const WNDCLASSEXW * windowClassAddr)
{
	Log
	(
		"%s "
		"%llX",
		FUNC_NAME,
		windowClassAddr
	);

	// if (!windowClassAddr)
	// {
	// 	return 0;
	// }

	auto & windowClass = *const_cast<WNDCLASSEXW *>(windowClassAddr);

	static bool run = false;
	if (!run)
	{
		run = true;

		ImGui::CreateContext();

		auto & io = ImGui::GetIO();

		io.IniFilename = 0;

		ImGui::DI8::Init();

		GUI_Init();

		::Base::Windows::WindowProc = windowClass.lpfnWndProc;

		windowClass.lpfnWndProc = ::Hook::Windows::WindowProc;
	}

	return ::Base::Windows::RegisterClassExW(windowClassAddr);
}

HWND CreateWindowExW
(
	DWORD dwExStyle,
	LPCWSTR lpClassName,
	LPCWSTR lpWindowName,
	DWORD dwStyle,
	int X,
	int Y,
	int nWidth,
	int nHeight,
	HWND hWndParent,
	HMENU hMenu,
	HINSTANCE hInstance,
	LPVOID lpParam
)
{
	if constexpr (debug)
	{
		X = 0;
		Y = 0;
	}

	Log
	(
		"%s "
		"%X "
		"%llX "
		"%llX "
		"%X "
		"%d "
		"%d "
		"%d "
		"%d "
		"%llX "
		"%llX "
		"%llX "
		"%llX",
		FUNC_NAME,
		dwExStyle,
		lpClassName,
		lpWindowName,
		dwStyle,
		X,
		Y,
		nWidth,
		nHeight,
		hWndParent,
		hMenu,
		hInstance,
		lpParam
	);

	ToggleCursor();

	return ::Base::Windows::CreateWindowExW
	(
		dwExStyle,
		lpClassName,
		lpWindowName,
		dwStyle,
		X,
		Y,
		nWidth,
		nHeight,
		hWndParent,
		hMenu,
		hInstance,
		lpParam
	);
}

namespaceEnd();

#pragma endregion





void UpdateShow()
{
	if (g_lastShow != g_show)
	{
		g_lastShow = g_show;

		ToggleCursor();
	}
}







void CreateRenderTarget()
{
	LogFunction();
	ID3D11Texture2D * backBuffer = 0;
	::DXGI::swapChain->GetBuffer
	(
		0,
		D3D11::IID_ID3D11Texture2D,
		reinterpret_cast<void **>(&backBuffer)
	);
	::D3D11::device->CreateRenderTargetView(backBuffer, 0, &::D3D11::renderTargetView);
	backBuffer->Release();
}

void RemoveRenderTarget()
{
	LogFunction();
	if (!::D3D11::renderTargetView)
	{
		return;
	}
	float32 clearColor[4] = {};
	::D3D11::deviceContext->ClearRenderTargetView(::D3D11::renderTargetView, clearColor);
	::D3D11::renderTargetView->Release();
	::D3D11::renderTargetView = 0;
}

void Timestep()
{
	static uint64 freq           = 0;
	static uint64 mainCounter    = 0;
	uint64        currentCounter = 0;
	static bool run = false;
	if (!run)
	{
		run = true;
		QueryPerformanceFrequency((LARGE_INTEGER *)&freq);
		QueryPerformanceCounter((LARGE_INTEGER *)&mainCounter);
	}
	QueryPerformanceCounter((LARGE_INTEGER *)&currentCounter);
	ImGui::GetIO().DeltaTime = (float32)(currentCounter - mainCounter) / (float32)freq;
	mainCounter = currentCounter;
}





#pragma region DXGI

namespaceStart(DXGI);

typedef HRESULT(__fastcall * Present_t)
(
	IDXGISwapChain * SwapChain,
	UINT SyncInterval,
	UINT Flags
);
typedef HRESULT (__fastcall * ResizeBuffers_t)
(
	IDXGISwapChain * SwapChain,
	UINT BufferCount,
	UINT Width,
	UINT Height,
	DXGI_FORMAT NewFormat,
	UINT SwapChainFlags
);

namespaceEnd();



namespaceStart(Base::DXGI);

::DXGI::Present_t Present = 0;
::DXGI::ResizeBuffers_t ResizeBuffers = 0;

namespaceEnd();











namespaceStart(Hook::DXGI);

HRESULT Present
(
	IDXGISwapChain * SwapChain,
	UINT SyncInterval,
	UINT Flags
)
{
	static bool run = false;
	if (!run)
	{
		run = true;

		Log
		(
			"%s "
			"%llX "
			"%u "
			"%X",
			FUNC_NAME,
			SwapChain,
			SyncInterval,
			Flags
		);
	}

	if (activeConfig.vSync != 0)
	{
		SyncInterval = (activeConfig.vSync - 1);
	}


	UpdateShow();


	ImGui::D3D11::NewFrame();

	Timestep();

	ImGui::NewFrame();

	GUI_Render();

	ImGui::Render();

	::D3D11::deviceContext->OMSetRenderTargets
	(
		1,
		&::D3D11::renderTargetView,
		0
	);

	ImGui::D3D11::RenderDrawData(ImGui::GetDrawData());

	return ::Base::DXGI::Present
	(
		SwapChain,
		SyncInterval,
		Flags
	);
}

HRESULT ResizeBuffers
(
	IDXGISwapChain * SwapChain,
	UINT BufferCount,
	UINT Width,
	UINT Height,
	DXGI_FORMAT NewFormat,
	UINT SwapChainFlags
)
{
	Log
	(
		"%s "
		"%llX "
		"%u "
		"%u "
		"%u "
		"%d "
		"%X",
		FUNC_NAME,
		SwapChain,
		BufferCount,
		Width,
		Height,
		NewFormat,
		SwapChainFlags
	);

	RemoveRenderTarget();

	auto result = ::Base::DXGI::ResizeBuffers
	(
		SwapChain,
		BufferCount,
		Width,
		Height,
		NewFormat,
		SwapChainFlags
	);

	auto error = GetLastError();

	CreateRenderTarget();

	// UpdateRenderSize
	// (
	// 	Width,
	// 	Height
	// );

	SetLastError(error);

	return result;
}

namespaceEnd();

#pragma endregion

#pragma region D3D11

namespaceStart(D3D11);

typedef decltype(D3D11CreateDeviceAndSwapChain) * D3D11CreateDeviceAndSwapChain_t;

namespaceEnd();



namespaceStart(Base::D3D11);

::D3D11::D3D11CreateDeviceAndSwapChain_t D3D11CreateDeviceAndSwapChain = 0;

namespaceEnd();



namespaceStart(Hook::D3D11);

HRESULT D3D11CreateDeviceAndSwapChain
(
	IDXGIAdapter* pAdapter,
	D3D_DRIVER_TYPE DriverType,
	HMODULE Software,
	UINT Flags,
	const D3D_FEATURE_LEVEL* pFeatureLevels,
	UINT FeatureLevels,
	UINT SDKVersion,
	const DXGI_SWAP_CHAIN_DESC* pSwapChainDesc,
	IDXGISwapChain** ppSwapChain,
	ID3D11Device** ppDevice,
	D3D_FEATURE_LEVEL* pFeatureLevel,
	ID3D11DeviceContext** ppImmediateContext
)
{
	Log
	(
		"%s "
		"%llX "
		"%X "
		"%llX "
		"%X "
		"%llX "
		"%X "
		"%X "
		"%llX "
		"%llX "
		"%llX "
		"%llX "
		"%llX",
		FUNC_NAME,
		pAdapter,
		DriverType,
		Software,
		Flags,
		pFeatureLevels,
		FeatureLevels,
		SDKVersion,
		pSwapChainDesc,
		ppSwapChain,
		ppDevice,
		pFeatureLevel,
		ppImmediateContext
	);

	auto result = ::Base::D3D11::D3D11CreateDeviceAndSwapChain
	(
		pAdapter,
		DriverType,
		Software,
		Flags,
		pFeatureLevels,
		FeatureLevels,
		SDKVersion,
		pSwapChainDesc,
		ppSwapChain,
		ppDevice,
		pFeatureLevel,
		ppImmediateContext
	);

	auto error = GetLastError();

	::D3D11::device = *ppDevice;
	::D3D11::deviceContext = *ppImmediateContext;
	::DXGI::swapChain = *ppSwapChain;

	appWindow = pSwapChainDesc->OutputWindow;

	UpdateGlobalWindowSize();
	UpdateGlobalClientSize();
	UpdateGlobalRenderSize
	(
		pSwapChainDesc->BufferDesc.Width,
		pSwapChainDesc->BufferDesc.Height
	);

	ImGui::UpdateDisplaySize
	(
		pSwapChainDesc->BufferDesc.Width,
		pSwapChainDesc->BufferDesc.Height
	);

	UpdateMousePositionMultiplier();

	ImGui::D3D11::Init
	(
		::D3D11::device,
		::D3D11::deviceContext
	);

	CreateRenderTarget();


	Graphics::Toggle(false);
	Graphics::Toggle(true);

	UpdateFrameRate();




	[&]()
	{
		if ((result != 0) || !ppSwapChain || !*ppSwapChain)
		{
			return;
		}

		// @Research: Quadruple pointer and dereference twice or use global swap chain.
		auto funcAddrs = *reinterpret_cast<byte8 ***>(*ppSwapChain);
		if (!funcAddrs)
		{
			return;
		}

		Install
		(
			&funcAddrs[8],
			::Base::DXGI::Present,
			::Hook::DXGI::Present
		);

		Install
		(
			&funcAddrs[13],
			::Base::DXGI::ResizeBuffers,
			::Hook::DXGI::ResizeBuffers
		);
	}();

	SetLastError(error);

	return result;
}

namespaceEnd();

#pragma endregion




// void ToggleShow(byte8 * state)
// {
// 	static bool execute = true;

// 	constexpr byte8 keys[] =
// 	{
// 		DIK_LCONTROL,
// 		DIK_D,
// 	};

// 	uint8 keysDown = 0;

// 	old_for_all(uint8, index, countof(keys))
// 	{
// 		auto & key = keys[index];
// 		if (state[key] & 0x80)
// 		{
// 			keysDown++;
// 		}
// 	}

// 	if (keysDown == countof(keys))
// 	{
// 		if (execute)
// 		{
// 			g_show = !g_show;

// 			execute = false;
// 		}
// 	}
// 	else
// 	{
// 		execute = true;
// 	}
// }

void WindowSize1(byte8 * state)
{
	static bool execute = true;
	constexpr byte8 keys[] =
	{
		DIK_LCONTROL,
		DIK_1,
	};
	uint8 keysDown = 0;
	old_for_all(uint8, index, countof(keys))
	{
		auto & key = keys[index];
		if (state[key] & 0x80)
		{
			keysDown++;
		}
	}
	if (keysDown == countof(keys))
	{
		if (execute)
		{
			execute = false;
			SetWindowPos
			(
				appWindow,
				0,
				0,
				0,
				640,
				360,
				0
			);
		}
	}
	else
	{
		execute = true;
	}
}

void WindowSize2(byte8 * state)
{
	static bool execute = true;
	constexpr byte8 keys[] =
	{
		DIK_LCONTROL,
		DIK_2,
	};
	uint8 keysDown = 0;
	old_for_all(uint8, index, countof(keys))
	{
		auto & key = keys[index];
		if (state[key] & 0x80)
		{
			keysDown++;
		}
	}
	if (keysDown == countof(keys))
	{
		if (execute)
		{
			execute = false;
			SetWindowPos
			(
				appWindow,
				0,
				0,
				0,
				1920,
				1080,
				0
			);
		}
	}
	else
	{
		execute = true;
	}
}

void WindowSize3(byte8 * state)
{
	static bool execute = true;
	constexpr byte8 keys[] =
	{
		DIK_LCONTROL,
		DIK_3,
	};
	uint8 keysDown = 0;
	old_for_all(uint8, index, countof(keys))
	{
		auto & key = keys[index];
		if (state[key] & 0x80)
		{
			keysDown++;
		}
	}
	if (keysDown == countof(keys))
	{
		if (execute)
		{
			execute = false;
			SetWindowPos
			(
				appWindow,
				0,
				1920,
				0,
				1920,
				1080,
				0
			);
		}
	}
	else
	{
		execute = true;
	}
}

#pragma region DI8

namespaceStart(DI8);

typedef HRESULT(__fastcall * GetDeviceStateA_t)
(
	IDirectInputDevice8A * pDevice,
	DWORD BufferSize,
	LPVOID Buffer
);

namespaceEnd();



namespaceStart(Base::DI8);

::DI8::GetDeviceStateA_t GetDeviceStateA = 0;

namespaceEnd();



namespaceStart(Hook::DI8);

HRESULT GetDeviceStateA
(
	IDirectInputDevice8A * pDevice,
	DWORD BufferSize,
	LPVOID Buffer
)
{
	auto state = reinterpret_cast<byte8 *>(Buffer);




	for_all(index, countof(keyBindings))
	{
		auto & keyBinding = keyBindings[index];

		keyBinding.UpdateKeyData(state);
		keyBinding.Check(state);
	}




	ImGui::DI8::UpdateKeyboard(state);

	//ToggleShow(state);






	if (g_show)
	{
		SetMemory
		(
			Buffer,
			0,
			BufferSize
		);
	}


	if constexpr (debug)
	{
		WindowSize1(state);
		WindowSize2(state);
		WindowSize3(state);
	}



	return 0;
}

namespaceEnd();



namespaceStart(DI8);

byte32 UpdateMouseThread(LPVOID parameter)
{
	LogFunction();

	while (true)
	{
		if
		(
			appWindow &&
			(
				g_show ||
				g_showItemWindow
			)
		)
		{
			::DI8::mouse->GetDeviceState
			(
				sizeof(DIMOUSESTATE2),
				&::DI8::mouseState
			);

			ImGui::DI8::UpdateMouse
			(
				appWindow,
				&::DI8::mouseState
			);
		}

		Sleep(10);
	}

	return 1;
}

byte32 AcquireMouseThread(LPVOID parameter)
{
	while (true)
	{
		[&]()
		{
			if (GetForegroundWindow() != appWindow)
			{
				return;
			}

			if (!::DI8::mouse)
			{
				return;
			}

			::DI8::mouse->Acquire();
		}();

		Sleep(100);
	}

	return 1;
}

byte32 CreateMouseThread(LPVOID parameter)
{
	while (true)
	{
		if (appWindow)
		{
			break;
		}

		Sleep(100);
	}

	LogFunction();

	HRESULT result = 0;
	byte32 error = 0;

	result = ::DI8::DirectInput8Create
	(
		reinterpret_cast<HINSTANCE>(appBaseAddr),
		0x800,
		IID_IDirectInput8W,
		reinterpret_cast<void **>(&::DI8::deviceInterface),
		0
	);
	if (result != DI_OK)
	{
		error = GetLastError();

		Log("Create %X %X", result, error);

		goto Return;
	}

	result = ::DI8::deviceInterface->CreateDevice
	(
		GUID_SysMouse,
		&::DI8::mouse,
		0
	);
	if (result != DI_OK)
	{
		error = GetLastError();

		Log("CreateDevice %X %X", result, error);

		goto Return;
	}

	result = ::DI8::mouse->SetCooperativeLevel
	(
		appWindow,
		DISCL_NONEXCLUSIVE |
		DISCL_FOREGROUND
	);
	if (result != DI_OK)
	{
		error = GetLastError();

		Log("SetCooperativeLevel %X %X", result, error);

		goto Return;
	}

	result = ::DI8::mouse->SetDataFormat(&c_dfDIMouse2);
	if (result != DI_OK)
	{
		error = GetLastError();

		Log("SetDataFormat %X %X", result, error);

		goto Return;
	}

	result = ::DI8::mouse->Acquire();

	CreateThread
	(
		0,
		4096,
		::DI8::UpdateMouseThread,
		0,
		0,
		0
	);

	CreateThread
	(
		0,
		4096,
		::DI8::AcquireMouseThread,
		0,
		0,
		0
	);

	Return:

	return 1;
}

namespaceEnd();

#pragma endregion

#pragma region XI

namespaceStart(XI);

typedef decltype(XInputGetState) * XInputGetState_t;

namespaceEnd();



namespaceStart(Base::XI);

::XI::XInputGetState_t XInputGetState = 0;

namespaceEnd();



namespaceStart(Hook::XI);

DWORD XInputGetState
(
	DWORD dwUserIndex,
	XINPUT_STATE* pState
)
{
	if (g_show)
	{
		SetMemory(pState, 0, sizeof(XINPUT_STATE));
	}

	return 0;
}

namespaceEnd();

#pragma endregion



namespaceStart(Hooks);



export void Init()
{
	LogFunction();



	Install
	(
		(appBaseAddr + 0x34F308),
		::Base::Windows::RegisterClassExW,
		::Hook::Windows::RegisterClassExW
	);

	Install
	(
		(appBaseAddr + 0x34F300),
		::Base::Windows::CreateWindowExW,
		::Hook::Windows::CreateWindowExW
	);

	Install
	(
		(appBaseAddr + 0x34F650),
		::Base::D3D11::D3D11CreateDeviceAndSwapChain,
		::Hook::D3D11::D3D11CreateDeviceAndSwapChain
	);



	constexpr bool enable = true;
	static bool run = false;



	{
		auto addr     = (appBaseAddr + 0x41DA0);
		auto jumpAddr = (appBaseAddr + 0x41DA6);
		constexpr uint32 size = 6;
		constexpr uint32 size2 = 3;
		/*
		dmc3.exe+41DA0 - 48 8B 01 - mov rax,[rcx]
		dmc3.exe+41DA3 - FF 50 48 - call qword ptr [rax+48]
		dmc3.exe+41DA6 - 85 C0    - test eax,eax
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x50,                   // push rax
			0x51,                   // push rcx
			0x52,                   // push rdx
			0x41, 0x50,             // push r8
			0x55,                   // push rbp
			0x48, 0x8B, 0xEC,       // mov rbp,rsp
			0x40, 0x80, 0xE4, 0xF0, // and spl,F0
			0x48, 0x83, 0xEC, 0x20, // sub rsp,20
			0xFF, 0x50, 0x48,       // call qword ptr [rax+48]
			0x48, 0x89, 0x45, 0x20, // mov [rbp+20],rax
			0x48, 0x8B, 0x4D, 0x18, // mov rcx,[rbp+18]
			0x48, 0x8B, 0x55, 0x10, // mov rdx,[rbp+10]
			0x4C, 0x8B, 0x45, 0x08, // mov r8,[rbp+08]
		};
		constexpr byte8 sect2[] =
		{
			0x48, 0x8B, 0xE5, // mov rsp,rbp
			0x5D,             // pop rbp
			0x41, 0x58,       // pop r8
			0x5A,             // pop rdx
			0x59,             // pop rcx
			0x58,             // pop rax
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(::Hook::DI8::GetDeviceStateA, jumpAddr, false, true, (size2 + sizeof(sect0)), 0, sizeof(sect2));
			CopyMemory(func.sect0, addr, size2, MemoryFlags_VirtualProtectSource);
			CopyMemory((func.sect0 + size2), sect0, sizeof(sect0));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	{
		auto addr     = (appBaseAddr + 0x482AD);
		auto jumpAddr = (appBaseAddr + 0x482B5);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+482AD - BA 00010000 - mov edx,00000100
		dmc3.exe+482B2 - FF 50 48    - call qword ptr [rax+48]
		dmc3.exe+482B5 - 85 C0       - test eax,eax
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x50,                   // push rax
			0x51,                   // push rcx
			0x52,                   // push rdx
			0x41, 0x50,             // push r8
			0x55,                   // push rbp
			0x48, 0x8B, 0xEC,       // mov rbp,rsp
			0x40, 0x80, 0xE4, 0xF0, // and spl,F0
			0x48, 0x83, 0xEC, 0x20, // sub rsp,20
			0xFF, 0x50, 0x48,       // call qword ptr [rax+48]
			0x48, 0x89, 0x45, 0x20, // mov [rbp+20],rax
			0x48, 0x8B, 0x4D, 0x18, // mov rcx,[rbp+18]
			0x48, 0x8B, 0x55, 0x10, // mov rdx,[rbp+10]
			0x4C, 0x8B, 0x45, 0x08, // mov r8,[rbp+08]
		};
		constexpr byte8 sect2[] =
		{
			0x48, 0x8B, 0xE5, // mov rsp,rbp
			0x5D,             // pop rbp
			0x41, 0x58,       // pop r8
			0x5A,             // pop rdx
			0x59,             // pop rcx
			0x58,             // pop rax
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(::Hook::DI8::GetDeviceStateA, jumpAddr, false, true, (size + sizeof(sect0)), 0, sizeof(sect2));
			CopyMemory(func.sect0, addr, size, MemoryFlags_VirtualProtectSource);
			CopyMemory((func.sect0 + size), sect0, sizeof(sect0));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}



	CreateThread(0, 4096, ::DI8::CreateMouseThread, 0, 0, 0);



	// SetCooperativeLevelKeyboard
	{
		auto addr = (appBaseAddr + 0x47F56);
		constexpr uint32 size = 6;
		/*
		dmc3.exe+47F56 - 41 B8 05000000    - mov r8d,00000005
		dmc3.exe+47F5C - 48 8B 15 6D0BBD00 - mov rdx,[dmc3.exe+C18AD0]
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			Write<byte32>((addr + 2), DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}



	{
		auto addr     = (appBaseAddr + 0x41A83);
		auto jumpAddr = (appBaseAddr + 0x41A88);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+41A83 - E8 6E393000 - call dmc3.exe+3453F6
		dmc3.exe+41A88 - 85 C0       - test eax,eax
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x50,                         // push rax
			0x51,                         // push rcx
			0x52,                         // push rdx
			0x55,                         // push rbp
			0x48, 0x8B, 0xEC,             // mov rbp,rsp
			0x40, 0x80, 0xE4, 0xF0,       // and spl,F0
			0x48, 0x83, 0xEC, 0x20,       // sub rsp,20
			0xE8, 0x00, 0x00, 0x00, 0x00, // call dmc3.exe+3453F6
			0x48, 0x89, 0x45, 0x18,       // mov [rbp+18],rax
			0x48, 0x8B, 0x4D, 0x10,       // mov rcx,[rbp+10]
			0x48, 0x8B, 0x55, 0x08,       // mov rdx,[rbp+08]
		};
		constexpr byte8 sect2[] =
		{
			0x48, 0x8B, 0xE5, // mov rsp,rbp
			0x5D,             // pop rbp
			0x5A,             // pop rdx
			0x59,             // pop rcx
			0x58,             // pop rax
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(::Hook::XI::XInputGetState, jumpAddr, false, true, sizeof(sect0), 0, sizeof(sect2));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
			WriteCall((func.sect0 + 0xF), (appBaseAddr + 0x3453F6));
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	{
		auto addr     = (appBaseAddr + 0x41AFA);
		auto jumpAddr = (appBaseAddr + 0x41AFF);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+41AFA - E8 F7383000 - call dmc3.exe+3453F6
		dmc3.exe+41AFF - 85 C0       - test eax,eax
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x50,                         // push rax
			0x51,                         // push rcx
			0x52,                         // push rdx
			0x55,                         // push rbp
			0x48, 0x8B, 0xEC,             // mov rbp,rsp
			0x40, 0x80, 0xE4, 0xF0,       // and spl,F0
			0x48, 0x83, 0xEC, 0x20,       // sub rsp,20
			0xE8, 0x00, 0x00, 0x00, 0x00, // call dmc3.exe+3453F6
			0x48, 0x89, 0x45, 0x18,       // mov [rbp+18],rax
			0x48, 0x8B, 0x4D, 0x10,       // mov rcx,[rbp+10]
			0x48, 0x8B, 0x55, 0x08,       // mov rdx,[rbp+08]
		};
		constexpr byte8 sect2[] =
		{
			0x48, 0x8B, 0xE5, // mov rsp,rbp
			0x5D,             // pop rbp
			0x5A,             // pop rdx
			0x59,             // pop rcx
			0x58,             // pop rax
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(::Hook::XI::XInputGetState, jumpAddr, false, true, sizeof(sect0), 0, sizeof(sect2));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
			WriteCall((func.sect0 + 0xF), (appBaseAddr + 0x3453F6));
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	{
		auto addr     = (appBaseAddr + 0x41C40);
		auto jumpAddr = (appBaseAddr + 0x41C45);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+41C40 - E8 B1373000 - call dmc3.exe+3453F6
		dmc3.exe+41C45 - 85 C0       - test eax,eax
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x50,                         // push rax
			0x51,                         // push rcx
			0x52,                         // push rdx
			0x55,                         // push rbp
			0x48, 0x8B, 0xEC,             // mov rbp,rsp
			0x40, 0x80, 0xE4, 0xF0,       // and spl,F0
			0x48, 0x83, 0xEC, 0x20,       // sub rsp,20
			0xE8, 0x00, 0x00, 0x00, 0x00, // call dmc3.exe+3453F6
			0x48, 0x89, 0x45, 0x18,       // mov [rbp+18],rax
			0x48, 0x8B, 0x4D, 0x10,       // mov rcx,[rbp+10]
			0x48, 0x8B, 0x55, 0x08,       // mov rdx,[rbp+08]
		};
		constexpr byte8 sect2[] =
		{
			0x48, 0x8B, 0xE5, // mov rsp,rbp
			0x5D,             // pop rbp
			0x5A,             // pop rdx
			0x59,             // pop rcx
			0x58,             // pop rax
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(::Hook::XI::XInputGetState, jumpAddr, false, true, sizeof(sect0), 0, sizeof(sect2));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
			WriteCall((func.sect0 + 0xF), (appBaseAddr + 0x3453F6));
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}



	run = true;
}



namespaceEnd();



#ifdef __GARBAGE__
#endif
