







module;
#include "../ImGui/imgui.h"
export module Hooks;

import Core;

#include "../Core/Macros.h"

import Windows;
import DXGI;
import D3D10;
import DI8;
import XI;

import Core_ImGui;

import Config;
import Global;
import Graphics;
import GUI;
import Input;
import Scene;
import Window;
import Vars;

using namespace Windows;
using namespace DXGI;
using namespace D3D10;
using namespace DI8;
using namespace XI;

#define debug false

// #include "Macros.h"

































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
typedef decltype(CreateFileA) * CreateFileA_t;
typedef decltype(CreateFileW) * CreateFileW_t;

namespaceEnd();



namespaceStart(Base::Windows);

::Windows::WindowProc_t WindowProc = 0;
::Windows::RegisterClassExW_t RegisterClassExW = 0;
::Windows::CreateWindowExW_t CreateWindowExW = 0;
::Windows::CreateFileA_t CreateFileA = 0;
::Windows::CreateFileW_t CreateFileW = 0;

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



	X = activeConfig.windowPosX;
	Y = activeConfig.windowPosY;




	// X = 0;
	// Y = 0;

	// nWidth = 1920;
	// nHeight = 1080;


	// constexpr DWORD style = (WS_OVERLAPPED | WS_MINIMIZEBOX | WS_CLIPSIBLINGS | WS_VISIBLE);

	// dwStyle = style;







	Log
	(
		"%s "
		"%X "
		"%X "
		"%X "
		"%X "
		"%d "
		"%d "
		"%d "
		"%d "
		"%X "
		"%X "
		"%X "
		"%X",
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

HANDLE CreateFileA
(
	LPCSTR lpFileName,
	DWORD dwDesiredAccess,
	DWORD dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD dwCreationDisposition,
	DWORD dwFlagsAndAttributes,
	HANDLE hTemplateFile
)
{
	// Log
	// (
	// 	"%s "
	// 	"%s "
	// 	"%X "
	// 	"%X "
	// 	"%X "
	// 	"%X "
	// 	"%X "
	// 	"%X",
	// 	FUNC_NAME,
	// 	lpFileName,
	// 	dwDesiredAccess,
	// 	dwShareMode,
	// 	lpSecurityAttributes,
	// 	dwCreationDisposition,
	// 	dwFlagsAndAttributes,
	// 	hTemplateFile
	// );


	SetScene(lpFileName);

	// if
	// (
	// 	(IndexOf(lpFileName, "SavedGame") == -1)
	// )
	// {
	// 	Log("$%s$", lpFileName);
	// }


	// if (IndexOf(lpFileName, "player") != -1)
	// {
	// 	Log("$%s$", lpFileName);
	// }


	//Log("$%s$", lpFileName);


	// if (IndexOf(lpFileName, "demo") != -1)
	// {
	// 	Log("$%s$", lpFileName);
	// }



	// if (IndexOf(lpFileName, "Room") != -1)
	// {
	// 	Log("$%s$", lpFileName);
	// }


	



	return ::Base::Windows::CreateFileA
	(
		lpFileName,
		dwDesiredAccess,
		dwShareMode,
		lpSecurityAttributes,
		dwCreationDisposition,
		dwFlagsAndAttributes,
		hTemplateFile
	);
}

HANDLE CreateFileW
(
	LPCWSTR lpFileName,
	DWORD dwDesiredAccess,
	DWORD dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD dwCreationDisposition,
	DWORD dwFlagsAndAttributes,
	HANDLE hTemplateFile
)
{
	// Log
	// (
	// 	"%s "
	// 	"%s "
	// 	"%X "
	// 	"%X "
	// 	"%X "
	// 	"%X "
	// 	"%X "
	// 	"%X",
	// 	FUNC_NAME,
	// 	lpFileName,
	// 	dwDesiredAccess,
	// 	dwShareMode,
	// 	lpSecurityAttributes,
	// 	dwCreationDisposition,
	// 	dwFlagsAndAttributes,
	// 	hTemplateFile
	// );

	return ::Base::Windows::CreateFileW
	(
		lpFileName,
		dwDesiredAccess,
		dwShareMode,
		lpSecurityAttributes,
		dwCreationDisposition,
		dwFlagsAndAttributes,
		hTemplateFile
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
	ID3D10Texture2D * backBuffer = 0;
	::DXGI::swapChain->GetBuffer
	(
		0,
		D3D10::IID_ID3D10Texture2D,
		reinterpret_cast<void **>(&backBuffer)
	);
	::D3D10::device->CreateRenderTargetView(backBuffer, 0, &::D3D10::renderTargetView);
	backBuffer->Release();
}

void RemoveRenderTarget()
{
	LogFunction();
	if (!::D3D10::renderTargetView)
	{
		return;
	}
	float32 clearColor[4] = {};
	::D3D10::device->ClearRenderTargetView(::D3D10::renderTargetView, clearColor);
	::D3D10::renderTargetView->Release();
	::D3D10::renderTargetView = 0;
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

typedef HRESULT(* Present_t)
(
	IDXGISwapChain * SwapChain,
	UINT SyncInterval,
	UINT Flags
);
typedef HRESULT (* ResizeBuffers_t)
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


	ImGui::D3D10::NewFrame();

	Timestep();

	ImGui::NewFrame();

	GUI_Render();

	ImGui::Render();

	::D3D10::device->OMSetRenderTargets
	(
		1,
		&::D3D10::renderTargetView,
		0
	);

	ImGui::D3D10::RenderDrawData(ImGui::GetDrawData());



	if (g_update3D)
	{
		g_update3D = false;

		ToggleBorderless(activeConfig.borderless);
	}



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

	// Width = 1280;
	// Height = 720;



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




	UpdateGlobalWindowSize();
	UpdateGlobalClientSize();
	UpdateGlobalRenderSize
	(
		Width,
		Height
	);






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

#pragma region D3D10

namespaceStart(D3D10);

typedef decltype(D3D10CreateDeviceAndSwapChain) * D3D10CreateDeviceAndSwapChain_t;

namespaceEnd();



namespaceStart(Base::D3D10);

::D3D10::D3D10CreateDeviceAndSwapChain_t D3D10CreateDeviceAndSwapChain = 0;

namespaceEnd();



namespaceStart(Hook::D3D10);

HRESULT D3D10CreateDeviceAndSwapChain
(
	IDXGIAdapter* pAdapter,
	D3D10_DRIVER_TYPE DriverType,
	HMODULE Software,
	UINT Flags,
	UINT SDKVersion,
	DXGI_SWAP_CHAIN_DESC* pSwapChainDesc,
	IDXGISwapChain** ppSwapChain,
	ID3D10Device** ppDevice
)
{
	Log
	(
		"%s "
		"%llX "
		"%X "
		"%llX "
		"%X "
		"%X "
		"%llX "
		"%llX "
		"%llX",
		FUNC_NAME,
		pAdapter,
		DriverType,
		Software,
		Flags,
		SDKVersion,
		pSwapChainDesc,
		ppSwapChain,
		ppDevice
	);








	// pSwapChainDesc->BufferDesc.Width = 1280;
	// pSwapChainDesc->BufferDesc.Height = 720;



	// ID3D10DeviceContext * newContext = 0;



	// if (!ppImmediateContext)
	// {
	// 	ppImmediateContext = &newContext;
	// }



	auto result = ::Base::D3D10::D3D10CreateDeviceAndSwapChain
	(
		pAdapter,
		DriverType,
		Software,
		Flags,
		SDKVersion,
		pSwapChainDesc,
		ppSwapChain,
		ppDevice
	);







	auto error = GetLastError();

	::D3D10::device = *ppDevice;
	//::D3D10::deviceContext = *ppImmediateContext;
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

	ImGui::D3D10::Init(::D3D10::device);

	CreateRenderTarget();



	//Graphics::Init();


	Graphics::Toggle(false);
	Graphics::Toggle(true);

	UpdateFrameRate();




	[&]()
	{
		// @Todo: Proper indentation.
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

void ToggleShow(byte8 * state)
{
	static bool execute = true;

	constexpr byte8 keys[] =
	{
		DIK_LCONTROL,
		DIK_D,
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
			g_show = !g_show;

			execute = false;
		}
	}
	else
	{
		execute = true;
	}
}

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

typedef HRESULT(* GetDeviceStateA_t)
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

HRESULT GetDeviceStateAKeyboard
(
	IDirectInputDevice8A * pDevice,
	DWORD BufferSize,
	LPVOID Buffer
)
{


	if (GetForegroundWindow() != appWindow)
	{
		SetMemory
		(
			Buffer,
			0,
			BufferSize
		);

		return 0;
	}




	auto state = reinterpret_cast<byte8 *>(Buffer);



	ImGui::DI8::UpdateKeyboard(state);

	ToggleShow(state);

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

HRESULT GetDeviceStateAMouse
(
	IDirectInputDevice8A * pDevice,
	DWORD BufferSize,
	LPVOID Buffer
)
{


	if (GetForegroundWindow() != appWindow)
	{
		SetMemory
		(
			Buffer,
			0,
			BufferSize
		);

		return 0;
	}





	if (g_show)
	{
		SetMemory
		(
			Buffer,
			0,
			BufferSize
		);
	}

	return 0;
}

HRESULT GetDeviceStateAGamepad
(
	IDirectInputDevice8A * pDevice,
	DWORD BufferSize,
	LPVOID Buffer
)
{


	if (GetForegroundWindow() != appWindow)
	{
		SetMemory
		(
			Buffer,
			0,
			BufferSize
		);

		return 0;
	}






	if (g_show)
	{
		SetMemory
		(
			Buffer,
			0,
			BufferSize
		);
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


//::DI8::IDirectInputDevice8W newMouse = {};



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
		(appBaseAddr + 0xB732F0),
		::Base::Windows::RegisterClassExW,
		::Hook::Windows::RegisterClassExW
	);

	Install
	(
		(appBaseAddr + 0xB73328),
		::Base::Windows::CreateWindowExW,
		::Hook::Windows::CreateWindowExW
	);

	Install
	(
		(appBaseAddr + 0xB733CC),
		::Base::D3D10::D3D10CreateDeviceAndSwapChain,
		::Hook::D3D10::D3D10CreateDeviceAndSwapChain
	);

	Install
	(
		(appBaseAddr + 0xB73128),
		::Base::Windows::CreateFileA,
		::Hook::Windows::CreateFileA
	);

	Install
	(
		(appBaseAddr + 0xB73090),
		::Base::Windows::CreateFileW,
		::Hook::Windows::CreateFileW
	);









	constexpr bool enable = true;
	static bool run = false;



	// GetDeviceStateAKeyboard
	{
		auto addr     = (appBaseAddr + 0x6E9E50);
		auto jumpAddr = (appBaseAddr + 0x6E9E55);
		constexpr size_t size = 5;
		/*
		dmc4.exe+6E9E50 - 8B 41 24 - mov eax,[ecx+24]
		dmc4.exe+6E9E53 - FF D0    - call eax
		dmc4.exe+6E9E55 - 85 C0    - test eax,eax
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x83, 0xEC, 0x10,             // sub esp,10
			0x51,                         // push ecx
			0x56,                         // push esi
			0x57,                         // push edi
			0xB9, 0x03, 0x00, 0x00, 0x00, // mov ecx,00000003
			0x8D, 0x74, 0x24, 0x1C,       // lea esi,[esp+1C]
			0x8D, 0x7C, 0x24, 0x0C,       // lea edi,[esp+0C]
			0xF3, 0xA5,                   // repe movsd
			0xB9, 0x03, 0x00, 0x00, 0x00, // mov ecx,00000003
			0x8D, 0x74, 0x24, 0x0C,       // lea esi,[esp+0C]
			0x8D, 0x7C, 0x24, 0x18,       // lea edi,[esp+18]
			0xF3, 0xA5,                   // repe movsd
			0x5F,                         // pop edi
			0x5E,                         // pop esi
			0x59,                         // pop ecx
			0x8B, 0x41, 0x24,             // mov eax,[ecx+24]
			0xFF, 0xD0,                   // call eax
			0x89, 0x44, 0x24, 0x0C,       // mov [esp+0C],eax
		};

		constexpr byte8 sect2[] =
		{
			0x58, // pop eax
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = OldCreateFunction(::Hook::DI8::GetDeviceStateAKeyboard, jumpAddr, false, true, sizeof(sect0), 0, sizeof(sect2));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
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

	// GetDeviceStateAMouse
	{
		auto addr     = (appBaseAddr + 0x6EA709);
		auto jumpAddr = (appBaseAddr + 0x6EA70E);
		constexpr size_t size = 5;
		/*
		dmc4.exe+6EA709 - 8B 41 24 - mov eax,[ecx+24]
		dmc4.exe+6EA70C - FF D0    - call eax
		dmc4.exe+6EA70E - 85 C0    - test eax,eax
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x83, 0xEC, 0x10,             // sub esp,10
			0x51,                         // push ecx
			0x56,                         // push esi
			0x57,                         // push edi
			0xB9, 0x03, 0x00, 0x00, 0x00, // mov ecx,00000003
			0x8D, 0x74, 0x24, 0x1C,       // lea esi,[esp+1C]
			0x8D, 0x7C, 0x24, 0x0C,       // lea edi,[esp+0C]
			0xF3, 0xA5,                   // repe movsd
			0xB9, 0x03, 0x00, 0x00, 0x00, // mov ecx,00000003
			0x8D, 0x74, 0x24, 0x0C,       // lea esi,[esp+0C]
			0x8D, 0x7C, 0x24, 0x18,       // lea edi,[esp+18]
			0xF3, 0xA5,                   // repe movsd
			0x5F,                         // pop edi
			0x5E,                         // pop esi
			0x59,                         // pop ecx
			0x8B, 0x41, 0x24,             // mov eax,[ecx+24]
			0xFF, 0xD0,                   // call eax
			0x89, 0x44, 0x24, 0x0C,       // mov [esp+0C],eax
		};

		constexpr byte8 sect2[] =
		{
			0x58, // pop eax
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = OldCreateFunction(::Hook::DI8::GetDeviceStateAMouse, jumpAddr, false, true, sizeof(sect0), 0, sizeof(sect2));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
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

	// GetDeviceStateAGamepad
	{
		auto addr     = (appBaseAddr + 0x6EE146);
		auto jumpAddr = (appBaseAddr + 0x6EE14E);
		constexpr size_t size = 6;
		/*
		dmc4.exe+6EE146 - 68 10010000 - push 00000110
		dmc4.exe+6EE14B - 57          - push edi
		dmc4.exe+6EE14C - FF D1       - call ecx
		dmc4.exe+6EE14E - 85 C0       - test eax,eax
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x83, 0xEC, 0x10,             // sub esp,10
			0x51,                         // push ecx
			0x56,                         // push esi
			0x57,                         // push edi
			0xB9, 0x03, 0x00, 0x00, 0x00, // mov ecx,00000003
			0x8D, 0x74, 0x24, 0x1C,       // lea esi,[esp+1C]
			0x8D, 0x7C, 0x24, 0x0C,       // lea edi,[esp+0C]
			0xF3, 0xA5,                   // repe movsd
			0xB9, 0x03, 0x00, 0x00, 0x00, // mov ecx,00000003
			0x8D, 0x74, 0x24, 0x0C,       // lea esi,[esp+0C]
			0x8D, 0x7C, 0x24, 0x18,       // lea edi,[esp+18]
			0xF3, 0xA5,                   // repe movsd
			0x5F,                         // pop edi
			0x5E,                         // pop esi
			0x59,                         // pop ecx
			0xFF, 0xD1,                   // call ecx
			0x89, 0x44, 0x24, 0x0C,       // mov [esp+0C],eax
		};

		constexpr byte8 sect2[] =
		{
			0x58, // pop eax
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = OldCreateFunction(::Hook::DI8::GetDeviceStateAGamepad, jumpAddr, false, true, (size + sizeof(sect0)), 0, sizeof(sect2));
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
		auto addr = (appBaseAddr + 0x6E9BE0);
		constexpr uint32 size = 2;
		/*
		dmc4.exe+6E9BE0 - 6A 15 - push 15
		dmc4.exe+6E9BE2 - 52    - push edx
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			Write<byte8>((addr + 1), (DISCL_NONEXCLUSIVE | DISCL_FOREGROUND));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// SetCooperativeLevelMouse
	{
		auto addr = (appBaseAddr + 0x6EA8AF);
		constexpr uint32 size = 2;
		/*
		dmc4.exe+6EA8AF - 6A 0A - push 0A
		dmc4.exe+6EA8B1 - 52    - push edx
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			Write<byte8>((addr + 1), (DISCL_NONEXCLUSIVE | DISCL_FOREGROUND));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// SetCooperativeLevelGamepad
	{
		auto addr = (appBaseAddr + 0x6ED9E5);
		constexpr uint32 size = 2;
		/*
		dmc4.exe+6ED9E5 - 6A 09 - push 09
		dmc4.exe+6ED9E7 - 51    - push ecx
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			Write<byte8>((addr + 1), (DISCL_NONEXCLUSIVE | DISCL_FOREGROUND));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}



	// GetState
	{
		auto addr     = (appBaseAddr + 0x6EB4DF);
		auto jumpAddr = (appBaseAddr + 0x6EB4E4);
		constexpr size_t size = 5;
		/*
		dmc4.exe+6EB4DF - E8 B46D3D00 - call dmc4.exe+AC2298
		dmc4.exe+6EB4E4 - 85 C0       - test eax,eax
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x83, 0xEC, 0x0C,             // sub esp,0C
			0x51,                         // push ecx
			0x56,                         // push esi
			0x57,                         // push edi
			0xB9, 0x02, 0x00, 0x00, 0x00, // mov ecx,00000002
			0x8D, 0x74, 0x24, 0x18,       // lea esi,[esp+18]
			0x8D, 0x7C, 0x24, 0x0C,       // lea edi,[esp+0C]
			0xF3, 0xA5,                   // repe movsd
			0xB9, 0x02, 0x00, 0x00, 0x00, // mov ecx,00000002
			0x8D, 0x74, 0x24, 0x0C,       // lea esi,[esp+0C]
			0x8D, 0x7C, 0x24, 0x14,       // lea edi,[esp+14]
			0xF3, 0xA5,                   // repe movsd
			0x5F,                         // pop edi
			0x5E,                         // pop esi
			0x59,                         // pop ecx
			0xE8, 0x00, 0x00, 0x00, 0x00, // call dmc4.exe+AC2298
			0x89, 0x44, 0x24, 0x08,       // mov [esp+08],eax
		};

		constexpr byte8 sect2[] =
		{
			0x58, // pop eax
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = OldCreateFunction(::Hook::XI::XInputGetState, jumpAddr, false, true, sizeof(sect0), 0, sizeof(sect2));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
			WriteCall((func.sect0 + 0x27), (appBaseAddr + 0xAC2298));
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
		auto addr     = (appBaseAddr + 0x6EC996);
		auto jumpAddr = (appBaseAddr + 0x6EC99B);
		constexpr size_t size = 5;
		/*
		dmc4.exe+6EC996 - E8 FD583D00 - call dmc4.exe+AC2298
		dmc4.exe+6EC99B - 85 C0       - test eax,eax
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x83, 0xEC, 0x0C,             // sub esp,0C
			0x51,                         // push ecx
			0x56,                         // push esi
			0x57,                         // push edi
			0xB9, 0x02, 0x00, 0x00, 0x00, // mov ecx,00000002
			0x8D, 0x74, 0x24, 0x18,       // lea esi,[esp+18]
			0x8D, 0x7C, 0x24, 0x0C,       // lea edi,[esp+0C]
			0xF3, 0xA5,                   // repe movsd
			0xB9, 0x02, 0x00, 0x00, 0x00, // mov ecx,00000002
			0x8D, 0x74, 0x24, 0x0C,       // lea esi,[esp+0C]
			0x8D, 0x7C, 0x24, 0x14,       // lea edi,[esp+14]
			0xF3, 0xA5,                   // repe movsd
			0x5F,                         // pop edi
			0x5E,                         // pop esi
			0x59,                         // pop ecx
			0xE8, 0x00, 0x00, 0x00, 0x00, // call dmc4.exe+AC2298
			0x89, 0x44, 0x24, 0x08,       // mov [esp+08],eax
		};

		constexpr byte8 sect2[] =
		{
			0x58, // pop eax
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = OldCreateFunction(::Hook::XI::XInputGetState, jumpAddr, false, true, sizeof(sect0), 0, sizeof(sect2));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
			WriteCall((func.sect0 + 0x27), (appBaseAddr + 0xAC2298));
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
		auto addr     = (appBaseAddr + 0x6EDE33);
		auto jumpAddr = (appBaseAddr + 0x6EDE38);
		constexpr size_t size = 5;
		/*
		dmc4.exe+6EDE33 - E8 60443D00 - call dmc4.exe+AC2298
		dmc4.exe+6EDE38 - 85 C0       - test eax,eax
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x83, 0xEC, 0x0C,             // sub esp,0C
			0x51,                         // push ecx
			0x56,                         // push esi
			0x57,                         // push edi
			0xB9, 0x02, 0x00, 0x00, 0x00, // mov ecx,00000002
			0x8D, 0x74, 0x24, 0x18,       // lea esi,[esp+18]
			0x8D, 0x7C, 0x24, 0x0C,       // lea edi,[esp+0C]
			0xF3, 0xA5,                   // repe movsd
			0xB9, 0x02, 0x00, 0x00, 0x00, // mov ecx,00000002
			0x8D, 0x74, 0x24, 0x0C,       // lea esi,[esp+0C]
			0x8D, 0x7C, 0x24, 0x14,       // lea edi,[esp+14]
			0xF3, 0xA5,                   // repe movsd
			0x5F,                         // pop edi
			0x5E,                         // pop esi
			0x59,                         // pop ecx
			0xE8, 0x00, 0x00, 0x00, 0x00, // call dmc4.exe+AC2298
			0x89, 0x44, 0x24, 0x08,       // mov [esp+08],eax
		};

		constexpr byte8 sect2[] =
		{
			0x58, // pop eax
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = OldCreateFunction(::Hook::XI::XInputGetState, jumpAddr, false, true, sizeof(sect0), 0, sizeof(sect2));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
			WriteCall((func.sect0 + 0x27), (appBaseAddr + 0xAC2298));
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
		auto addr     = (appBaseAddr + 0x6EDF64);
		auto jumpAddr = (appBaseAddr + 0x6EDF69);
		constexpr size_t size = 5;
		/*
		dmc4.exe+6EDF64 - E8 2F433D00 - call dmc4.exe+AC2298
		dmc4.exe+6EDF69 - 85 C0       - test eax,eax
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x83, 0xEC, 0x0C,             // sub esp,0C
			0x51,                         // push ecx
			0x56,                         // push esi
			0x57,                         // push edi
			0xB9, 0x02, 0x00, 0x00, 0x00, // mov ecx,00000002
			0x8D, 0x74, 0x24, 0x18,       // lea esi,[esp+18]
			0x8D, 0x7C, 0x24, 0x0C,       // lea edi,[esp+0C]
			0xF3, 0xA5,                   // repe movsd
			0xB9, 0x02, 0x00, 0x00, 0x00, // mov ecx,00000002
			0x8D, 0x74, 0x24, 0x0C,       // lea esi,[esp+0C]
			0x8D, 0x7C, 0x24, 0x14,       // lea edi,[esp+14]
			0xF3, 0xA5,                   // repe movsd
			0x5F,                         // pop edi
			0x5E,                         // pop esi
			0x59,                         // pop ecx
			0xE8, 0x00, 0x00, 0x00, 0x00, // call dmc4.exe+AC2298
			0x89, 0x44, 0x24, 0x08,       // mov [esp+08],eax
		};

		constexpr byte8 sect2[] =
		{
			0x58, // pop eax
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = OldCreateFunction(::Hook::XI::XInputGetState, jumpAddr, false, true, sizeof(sect0), 0, sizeof(sect2));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
			WriteCall((func.sect0 + 0x27), (appBaseAddr + 0xAC2298));
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
		auto addr     = (appBaseAddr + 0x6EE0A2);
		auto jumpAddr = (appBaseAddr + 0x6EE0A7);
		constexpr size_t size = 5;
		/*
		dmc4.exe+6EE0A2 - E8 F1413D00 - call dmc4.exe+AC2298
		dmc4.exe+6EE0A7 - 85 C0       - test eax,eax
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x83, 0xEC, 0x0C,             // sub esp,0C
			0x51,                         // push ecx
			0x56,                         // push esi
			0x57,                         // push edi
			0xB9, 0x02, 0x00, 0x00, 0x00, // mov ecx,00000002
			0x8D, 0x74, 0x24, 0x18,       // lea esi,[esp+18]
			0x8D, 0x7C, 0x24, 0x0C,       // lea edi,[esp+0C]
			0xF3, 0xA5,                   // repe movsd
			0xB9, 0x02, 0x00, 0x00, 0x00, // mov ecx,00000002
			0x8D, 0x74, 0x24, 0x0C,       // lea esi,[esp+0C]
			0x8D, 0x7C, 0x24, 0x14,       // lea edi,[esp+14]
			0xF3, 0xA5,                   // repe movsd
			0x5F,                         // pop edi
			0x5E,                         // pop esi
			0x59,                         // pop ecx
			0xE8, 0x00, 0x00, 0x00, 0x00, // call dmc4.exe+AC2298
			0x89, 0x44, 0x24, 0x08,       // mov [esp+08],eax
		};

		constexpr byte8 sect2[] =
		{
			0x58, // pop eax
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = OldCreateFunction(::Hook::XI::XInputGetState, jumpAddr, false, true, sizeof(sect0), 0, sizeof(sect2));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
			WriteCall((func.sect0 + 0x27), (appBaseAddr + 0xAC2298));
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



