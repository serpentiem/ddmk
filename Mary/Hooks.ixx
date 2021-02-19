// @Todo: Update.

module;
#include "../Core/Core.h"

#include <d3d11.h>
#define DIRECTINPUT_VERSION 0x800
#include <dinput.h>
#include <dxgi.h>
#include <Xinput.h>

#include "../ImGui/imgui.h"
export module Hooks;

import ImGui_D3D11;
import ImGui_DirectInput8;
import ImGui_User;
import Config;
import Global;
import GUI;
import Window;

#define debug false

enum DM_
{
	DM_PAUSE = WM_USER,
};

typedef ATOM(* User_RegisterClassExW_t)
(
	WNDCLASSEXW *
);
typedef HWND(* User_CreateWindowExW_t)
(
	byte32    ,
	LPCWSTR  ,
	LPCWSTR  ,
	byte32    ,
	int      ,
	int      ,
	int      ,
	int      ,
	HWND     ,
	HMENU    ,
	HINSTANCE,
	LPVOID
);
typedef LRESULT(* User_WindowProc_t)
(
	HWND,
	UINT,
	WPARAM,
	LPARAM
);

User_RegisterClassExW_t User_RegisterClassExW = 0;
User_CreateWindowExW_t  User_CreateWindowExW  = 0;
User_WindowProc_t       User_WindowProc       = 0;











//ATOM User_Hook_RegisterClassExW
//(
//	WNDCLASSEXW * windowClass
//);
//HWND User_Hook_CreateWindowExW
//(
//	byte32     exStyle,
//	LPCWSTR   className,
//	LPCWSTR   windowName,
//	byte32     style,
//	int       x,
//	int       y,
//	int       width,
//	int       height,
//	HWND      parentWindow,
//	HMENU     menu,
//	HINSTANCE instance,
//	LPVOID    parameter
//);
//LRESULT User_Hook_WindowProc
//(
//	HWND   window,
//	UINT   message,
//	WPARAM wParameter,
//	LPARAM lParameter
//);

// ID3D11Device           * D3D11_device           = 0;
// ID3D11DeviceContext    * D3D11_deviceContext    = 0;
// ID3D11RenderTargetView * D3D11_renderTargetView = 0;







typedef HRESULT(* D3D11_CreateDeviceAndSwapChain_t)
(
	IDXGIAdapter         * ,
	D3D_DRIVER_TYPE        ,
	HMODULE                ,
	UINT                   ,
	D3D_FEATURE_LEVEL    * ,
	UINT                   ,
	UINT                   ,
	DXGI_SWAP_CHAIN_DESC * ,
	IDXGISwapChain       **,
	ID3D11Device         **,
	D3D_FEATURE_LEVEL    * ,
	ID3D11DeviceContext  **
);

D3D11_CreateDeviceAndSwapChain_t D3D11_CreateDeviceAndSwapChain = 0;

//HRESULT D3D11_Hook_CreateDeviceAndSwapChain
//(
//	IDXGIAdapter         *  adapter,
//	D3D_DRIVER_TYPE         driverType,
//	HMODULE                 software,
//	UINT                    flags,
//	D3D_FEATURE_LEVEL    *  featureLevels,
//	UINT                    featureLevelCount,
//	UINT                    SDKVersion,
//	DXGI_SWAP_CHAIN_DESC *  swapChainDescription,
//	IDXGISwapChain       ** swapChain,
//	ID3D11Device         ** device,
//	D3D_FEATURE_LEVEL    *  featureLevel,
//	ID3D11DeviceContext  ** deviceContext
//);






IDXGISwapChain * DXGI_swapChain = 0;

typedef HRESULT(* DXGI_Present_t)
(
	IDXGISwapChain *,
	UINT            ,
	UINT
);
typedef HRESULT(* DXGI_ResizeBuffers_t)
(
	IDXGISwapChain *,
	UINT            ,
	UINT            ,
	UINT            ,
	DXGI_FORMAT     ,
	UINT
);

DXGI_Present_t       DXGI_Present       = 0;
DXGI_ResizeBuffers_t DXGI_ResizeBuffers = 0;

//HRESULT DXGI_Hook_Present
//(
//	IDXGISwapChain * swapChain,
//	UINT             syncInterval,
//	UINT             flags
//);
//HRESULT DXGI_Hook_ResizeBuffers
//(
//	IDXGISwapChain * swapChain,
//	UINT             bufferCount,
//	UINT             width,
//	UINT             height,
//	DXGI_FORMAT      newFormat,
//	UINT             swapChainFlags
//);

IDirectInput8W       * DirectInput8_deviceInterface = 0;
IDirectInputDevice8W * DirectInput8_mouse           = 0;
DIMOUSESTATE2          DirectInput8_mouseState      = {};

//static byte32 DirectInput8_CreateMouseThread(LPVOID parameter);
//static byte32 DirectInput8_UpdateMouseThread(LPVOID parameter);
//static byte32 DirectInput8_AcquireMouseThread(LPVOID parameter);





LRESULT User_Hook_WindowProc
(
	HWND   window,
	UINT   message,
	WPARAM wParameter,
	LPARAM lParameter
)
{
	static bool run = false;
	if (!run)
	{
		run = true;
		LogFunction();
	}
	switch (message)
	{
		case WM_SETCURSOR:
		{
			ImGui_User_UpdateMouseCursor(window);

			break;
		}
		case WM_CHAR:
		{
			ImGui::GetIO().AddInputCharacter((uint16)wParameter);

			return 0;
		}
		case DM_PAUSE:
		{
			ImGuiIO& io = ImGui::GetIO();
			if (g_pause)
			{
				// FIXME: workaround for unaligned cursor in windowed mode
				// hide hardware cursor and show software one
				io.MouseDrawCursor = true;
				//Windows_ToggleCursor(true);
			}
			else
			{
				io.MouseDrawCursor = false;
				if (activeConfig.hideMouseCursor)
				{
					Windows_ToggleCursor(false);
				}
			}

			return 1;
		}
	}
	return User_WindowProc
	(
		window,
		message,
		wParameter,
		lParameter
	);
}







ATOM User_Hook_RegisterClassExW
(
	WNDCLASSEXW * windowClass
)
{
	static bool run = false;
	if (!run)
	{
		run = true;
		ImGui::CreateContext();
		ImGui::GetIO().IniFilename = 0;
		ImGui_User_Init();
		ImGui_DirectInput8_Init();
		GUI_Init();
		User_WindowProc = windowClass->lpfnWndProc;
		windowClass->lpfnWndProc = User_Hook_WindowProc;
	}
	return User_RegisterClassExW
	(
		windowClass
	);
}

HWND User_Hook_CreateWindowExW
(
	byte32     exStyle,
	LPCWSTR   className,
	LPCWSTR   windowName,
	byte32     style,
	int       x,
	int       y,
	int       width,
	int       height,
	HWND      parentWindow,
	HMENU     menu,
	HINSTANCE instance,
	LPVOID    parameter
)
{
	if constexpr (debug)
	{
		x = 0;
		y = 0;
	}
	Log
	(
		"%s "
		"%X "
		"%X "
		"%X "
		"%X "
		"%u "
		"%u "
		"%u "
		"%u "
		"%X "
		"%X "
		"%X "
		"%X",
		FUNC_NAME,
		exStyle,
		className,
		windowName,
		style,
		x,
		y,
		width,
		height,
		parentWindow,
		menu,
		instance,
		parameter
	);
	if (activeConfig.hideMouseCursor)
	{
		Windows_ToggleCursor(false);
	}
	else
	{
		Windows_ToggleCursor(true);
	}
	return User_CreateWindowExW
	(
		exStyle,
		className,
		windowName,
		style,
		x,
		y,
		width,
		height,
		parentWindow,
		menu,
		instance,
		parameter
	);
}



void CreateRenderTarget()
{
	LogFunction();
	ID3D11Texture2D * backBuffer = 0;
	DXGI_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void **)&backBuffer);
	D3D11_device->CreateRenderTargetView(backBuffer, 0, &D3D11_renderTargetView);
	backBuffer->Release();
}

void RemoveRenderTarget()
{
	LogFunction();
	if (!D3D11_renderTargetView)
	{
		return;
	}
	float32 clearColor[4] = {};
	D3D11_deviceContext->ClearRenderTargetView(D3D11_renderTargetView, clearColor);
	D3D11_renderTargetView->Release();
	D3D11_renderTargetView = 0;
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







HRESULT DXGI_Hook_Present
(
	IDXGISwapChain * swapChain,
	UINT             syncInterval,
	UINT             flags
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
			swapChain,
			syncInterval,
			flags
		);
	}

	//if constexpr (debug)
	//{
	//	syncInterval = 0;
	//}


	if (activeConfig.vSync != 0)
	{
		syncInterval = (activeConfig.vSync - 1);
	}








	ImGui_D3D11_NewFrame();
	Timestep();
	ImGui::NewFrame();
	GUI_Render();
	ImGui::Render();
	D3D11_deviceContext->OMSetRenderTargets(1, &D3D11_renderTargetView, 0);
	ImGui_D3D11_RenderDrawData(ImGui::GetDrawData());
	return DXGI_Present
	(
		swapChain,
		syncInterval,
		flags
	);
}







HRESULT DXGI_Hook_ResizeBuffers
(
	IDXGISwapChain * swapChain,
	UINT             bufferCount,
	UINT             width,
	UINT             height,
	DXGI_FORMAT      newFormat,
	UINT             swapChainFlags
)
{
	Log
	(
		"%s "
		"%llX "
		"%u "
		"%u "
		"%u "
		"%X "
		"%X",
		FUNC_NAME,
		swapChain,
		bufferCount,
		width,
		height,
		newFormat,
		swapChainFlags
	);
	RemoveRenderTarget();
	HRESULT result = DXGI_ResizeBuffers
	(
		swapChain,
		bufferCount,
		width,
		height,
		newFormat,
		swapChainFlags
	);
	byte32 error = GetLastError();
	CreateRenderTarget();
	Window_UpdateSize((uint32)width, (uint32)height);
	SetLastError(error);
	return result;
}

















HRESULT D3D11_Hook_CreateDeviceAndSwapChain
(
	IDXGIAdapter         *  adapter,
	D3D_DRIVER_TYPE         driverType,
	HMODULE                 software,
	UINT                    flags,
	D3D_FEATURE_LEVEL    *  featureLevels,
	UINT                    featureLevelCount,
	UINT                    SDKVersion,
	DXGI_SWAP_CHAIN_DESC *  swapChainDescription,
	IDXGISwapChain       ** swapChain,
	ID3D11Device         ** device,
	D3D_FEATURE_LEVEL    *  featureLevel,
	ID3D11DeviceContext  ** deviceContext
)
{
	Log
	(
		"%s "
		"%llX "
		"%u "
		"%llX "
		"%X "
		"%llX "
		"%u "
		"%u "
		"%llX "
		"%llX "
		"%llX "
		"%llX "
		"%llX",
		FUNC_NAME,
		adapter,
		driverType,
		software,
		flags,
		featureLevels,
		featureLevelCount,
		SDKVersion,
		swapChainDescription,
		swapChain,
		device,
		featureLevel,
		deviceContext
	);
	HRESULT result = D3D11_CreateDeviceAndSwapChain
	(
		adapter,
		driverType,
		software,
		flags,
		featureLevels,
		featureLevelCount,
		SDKVersion,
		swapChainDescription,
		swapChain,
		device,
		featureLevel,
		deviceContext
	);
	byte32 error = GetLastError();
	D3D11_device = *device;
	D3D11_deviceContext = *deviceContext;
	DXGI_swapChain = *swapChain;
	appWindow = swapChainDescription->OutputWindow;
	// @Audit: Remove cast?
	Window_UpdateSize((uint32)swapChainDescription->BufferDesc.Width, (uint32)swapChainDescription->BufferDesc.Height);
	ImGui_D3D11_Init(D3D11_device, D3D11_deviceContext);
	CreateRenderTarget();
	//InstallStart:
	{
		if ((result != 0) || !swapChain || !*swapChain)
		{
			goto InstallEnd;
		}
		byte ** funcAddr = *(byte ***)*swapChain;
		if (!funcAddr)
		{
			goto InstallEnd;
		}
		DXGI_Present = (DXGI_Present_t)funcAddr[8];

		if constexpr (debug)
		{
			Log("DXGI_Present %llX", DXGI_Present);
		}

		Write<void *>((byte *)&funcAddr[8], DXGI_Hook_Present);

		DXGI_ResizeBuffers = (DXGI_ResizeBuffers_t)funcAddr[13];
		Write<void *>((byte *)&funcAddr[13], DXGI_Hook_ResizeBuffers);
	}
	InstallEnd:
	SetLastError(error);
	return result;
}

void TogglePause(byte8 * state)
{
	static bool execute = true;
	constexpr byte8 keys[] =
	{
		DIK_LCONTROL,
		DIK_D,
	};
	uint8 keysDown = 0;
	for_all(uint8, index, countof(keys))
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
			g_pause = !g_pause;
			PostMessageA(appWindow, DM_PAUSE, 0, 0);
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
	for_all(uint8, index, countof(keys))
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
	for_all(uint8, index, countof(keys))
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
				1280,
				720,
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
	for_all(uint8, index, countof(keys))
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

HRESULT DirectInput8_Hook_GetDeviceStateKeyboard
(
	IDirectInputDevice8A * device,
	byte32                  bufferSize,
	LPVOID                 buffer
)
{
	byte * state = (byte *)buffer;
	ImGui_DirectInput8_UpdateKeyboard(state);
	TogglePause(state);
	if (g_pause)
	{
		memset(buffer, 0, bufferSize);
	}
	if constexpr (debug)
	{
		WindowSize1(state);
		WindowSize2(state);
		WindowSize3(state);
	}
	return 0;
}




byte32 DirectInput8_UpdateMouseThread(LPVOID parameter)
{
	LogFunction();
	do
	{
		if (appWindow && g_pause)
		{
			DirectInput8_mouse->GetDeviceState(sizeof(DIMOUSESTATE2), &DirectInput8_mouseState);
			ImGui_DirectInput8_UpdateMouse(appWindow, &DirectInput8_mouseState);
		}
		Sleep(10);
	}
	while (true);
	return 1;
}

byte32 DirectInput8_AcquireMouseThread(LPVOID parameter)
{



	do
	{
		//LoopStart:
		{
			if (GetForegroundWindow() != appWindow)
			{
				goto LoopEnd;
			}
			if (!DirectInput8_mouse)
			{
				goto LoopEnd;
			}
			DirectInput8_mouse->Acquire();
		}
		LoopEnd:
		Sleep(100);
	}
	while (true);
	return 1;
}














byte32 DirectInput8_CreateMouseThread(LPVOID parameter)
{

	



	do
	{
		if (appWindow)
		{
			break;
		}
		Sleep(100);
	}
	while (true);
	LogFunction();
	HRESULT result = 0;
	result = DirectInput8Create((HINSTANCE)appBaseAddr, 0x800, IID_IDirectInput8W, (void **)&DirectInput8_deviceInterface, 0);
	if (result != DI_OK)
	{
		Log("Create %X %X", result, GetLastError());
		goto Return;
	}
	result = DirectInput8_deviceInterface->CreateDevice(GUID_SysMouse, &DirectInput8_mouse, 0);
	if (result != DI_OK)
	{
		Log("CreateDevice %X %X", result, GetLastError());
		goto Return;
	}
	result = DirectInput8_mouse->SetCooperativeLevel(appWindow, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (result != DI_OK)
	{
		Log("SetCooperativeLevel %X %X", result, GetLastError());
		goto Return;
	}
	result = DirectInput8_mouse->SetDataFormat(&c_dfDIMouse2);
	if (result != DI_OK)
	{
		Log("SetDataFormat %X %X", result, GetLastError());
		goto Return;
	}
	result = DirectInput8_mouse->Acquire();
	CreateThread(0, 4096, DirectInput8_UpdateMouseThread, 0, 0, 0);
	CreateThread(0, 4096, DirectInput8_AcquireMouseThread, 0, 0, 0);
	Return:
	return 1;
}

// @Todo: Update.
byte32 XInput_Hook_GetState
(
	byte32          userIndex,
	XINPUT_STATE * state
)
{
	//if (pause)
	//{
	//	memset(state, 0, sizeof(XINPUT_STATE));
	//}
	return 0;
}

export void Hooks_Init()
{
	LogFunction();
	// @Todo: byte8 *
	{
		byte * addr = (appBaseAddr + 0x34F308);
		User_RegisterClassExW = *(User_RegisterClassExW_t *)addr;
		Write<void *>(addr, User_Hook_RegisterClassExW);
	}
	{
		byte * addr = (appBaseAddr + 0x34F300);
		User_CreateWindowExW = *(User_CreateWindowExW_t *)addr;
		Write<void *>(addr, User_Hook_CreateWindowExW);
	}
	{
		byte * addr = (appBaseAddr + 0x34F650);
		D3D11_CreateDeviceAndSwapChain = *(D3D11_CreateDeviceAndSwapChain_t *)addr;

		if constexpr (debug)
		{
			Log("D3D11_CreateDeviceAndSwapChain %llX", D3D11_CreateDeviceAndSwapChain);
		}

		Write<void *>(addr, D3D11_Hook_CreateDeviceAndSwapChain);
	}

	Write<byte32>((appBaseAddr + 0x47F58), DISCL_NONEXCLUSIVE | DISCL_FOREGROUND); // SetCooperativeLevelKeyboard



	





	{
		byte8 sect0[] =
		{
			0x48, 0x8B, 0x01,       //mov rax,[rcx]
			0x50,                   //push rax
			0x51,                   //push rcx
			0x52,                   //push rdx
			0x41, 0x50,             //push r8
			0x55,                   //push rbp
			0x48, 0x8B, 0xEC,       //mov rbp,rsp
			0x40, 0x80, 0xE4, 0xF0, //and spl,F0
			0x48, 0x83, 0xEC, 0x20, //sub rsp,20
			0xFF, 0x50, 0x48,       //call qword ptr [rax+48]
			0x48, 0x89, 0x45, 0x20, //mov [rbp+20],rax
			0x48, 0x8B, 0x4D, 0x18, //mov rcx,[rbp+18]
			0x48, 0x8B, 0x55, 0x10, //mov rdx,[rbp+10]
			0x4C, 0x8B, 0x45, 0x08, //mov r8,[rbp+08]
		};
		byte8 sect2[] =
		{
			0x48, 0x8B, 0xE5, //mov rsp,rbp
			0x5D,             //pop rbp
			0x41, 0x58,       //pop r8
			0x5A,             //pop rdx
			0x59,             //pop rcx
			0x58,             //pop rax
		};

		//HoboBreak();


		auto func = ::CreateFunction(DirectInput8_Hook_GetDeviceStateKeyboard, (appBaseAddr + 0x41DA6), false, true, sizeof(sect0), 0, sizeof(sect2));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteJump((appBaseAddr + 0x41DA0), func.addr, 1);
	}


	























	{
		byte8 sect0[] =
		{
			0xBA, 0x00, 0x01, 0x00, 0x00, //mov edx,00000100
			0x50,                         //push rax
			0x51,                         //push rcx
			0x52,                         //push rdx
			0x41, 0x50,                   //push r8
			0x55,                         //push rbp
			0x48, 0x8B, 0xEC,             //mov rbp,rsp
			0x40, 0x80, 0xE4, 0xF0,       //and spl,F0
			0x48, 0x83, 0xEC, 0x20,       //sub rsp,20
			0xFF, 0x50, 0x48,             //call qword ptr [rax+48]
			0x48, 0x89, 0x45, 0x20,       //mov [rbp+20],rax
			0x48, 0x8B, 0x4D, 0x18,       //mov rcx,[rbp+18]
			0x48, 0x8B, 0x55, 0x10,       //mov rdx,[rbp+10]
			0x4C, 0x8B, 0x45, 0x08,       //mov r8,[rbp+08]
		};
		byte8 sect2[] =
		{
			0x48, 0x8B, 0xE5, //mov rsp,rbp
			0x5D,             //pop rbp
			0x41, 0x58,       //pop r8
			0x5A,             //pop rdx
			0x59,             //pop rcx
			0x58,             //pop rax
		};
		auto func = CreateFunction(DirectInput8_Hook_GetDeviceStateKeyboard, (appBaseAddr + 0x482B5), false, true, sizeof(sect0), 0, sizeof(sect2));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteJump((appBaseAddr + 0x482AD), func.addr);
	}


	





	CreateThread(0, 4096, DirectInput8_CreateMouseThread, 0, 0, 0);



	{
		byte8 sect0[] =
		{
			0x50,                         //push rax
			0x51,                         //push rcx
			0x52,                         //push rdx
			0x55,                         //push rbp
			0x48, 0x8B, 0xEC,             //mov rbp,rsp
			0x40, 0x80, 0xE4, 0xF0,       //and spl,F0
			0x48, 0x83, 0xEC, 0x20,       //sub rsp,20
			0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc3.exe+3453F6
			0x48, 0x89, 0x45, 0x18,       //mov [rbp+18],rax
			0x48, 0x8B, 0x4D, 0x10,       //mov rcx,[rbp+10]
			0x48, 0x8B, 0x55, 0x08,       //mov rdx,[rbp+08]
		};
		byte8 sect2[] =
		{
			0x48, 0x8B, 0xE5,             //mov rsp,rbp
			0x5D,                         //pop rbp
			0x5A,                         //pop rdx
			0x59,                         //pop rcx
			0x58,                         //pop rax
		};
		auto func = CreateFunction(XInput_Hook_GetState, (appBaseAddr + 0x41A88), false, true, sizeof(sect0), 0, sizeof(sect2));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteCall((func.sect0 + 0xF), (appBaseAddr + 0x3453F6));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteJump((appBaseAddr + 0x41A83), func.addr);
	}
	{
		byte8 sect0[] =
		{
			0x50,                         //push rax
			0x51,                         //push rcx
			0x52,                         //push rdx
			0x55,                         //push rbp
			0x48, 0x8B, 0xEC,             //mov rbp,rsp
			0x40, 0x80, 0xE4, 0xF0,       //and spl,F0
			0x48, 0x83, 0xEC, 0x20,       //sub rsp,20
			0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc3.exe+3453F6
			0x48, 0x89, 0x45, 0x18,       //mov [rbp+18],rax
			0x48, 0x8B, 0x4D, 0x10,       //mov rcx,[rbp+10]
			0x48, 0x8B, 0x55, 0x08,       //mov rdx,[rbp+08]
		};
		byte8 sect2[] =
		{
			0x48, 0x8B, 0xE5,             //mov rsp,rbp
			0x5D,                         //pop rbp
			0x5A,                         //pop rdx
			0x59,                         //pop rcx
			0x58,                         //pop rax
		};
		auto func = CreateFunction(XInput_Hook_GetState, (appBaseAddr + 0x41AFF), false, true, sizeof(sect0), 0, sizeof(sect2));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteCall((func.sect0 + 0xF), (appBaseAddr + 0x3453F6));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteJump((appBaseAddr + 0x41AFA), func.addr);
	}
	{
		byte8 sect0[] =
		{
			0x50,                         //push rax
			0x51,                         //push rcx
			0x52,                         //push rdx
			0x55,                         //push rbp
			0x48, 0x8B, 0xEC,             //mov rbp,rsp
			0x40, 0x80, 0xE4, 0xF0,       //and spl,F0
			0x48, 0x83, 0xEC, 0x20,       //sub rsp,20
			0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc3.exe+3453F6
			0x48, 0x89, 0x45, 0x18,       //mov [rbp+18],rax
			0x48, 0x8B, 0x4D, 0x10,       //mov rcx,[rbp+10]
			0x48, 0x8B, 0x55, 0x08,       //mov rdx,[rbp+08]
		};
		byte8 sect2[] =
		{
			0x48, 0x8B, 0xE5,             //mov rsp,rbp
			0x5D,                         //pop rbp
			0x5A,                         //pop rdx
			0x59,                         //pop rcx
			0x58,                         //pop rax
		};
		auto func = CreateFunction(XInput_Hook_GetState, (appBaseAddr + 0x41C45), false, true, sizeof(sect0), 0, sizeof(sect2));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteCall((func.sect0 + 0xF), (appBaseAddr + 0x3453F6));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteJump((appBaseAddr + 0x41C40), func.addr);
	}
}
