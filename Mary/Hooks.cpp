#include "Hooks.h"

constexpr bool debug = false;

typedef ATOM(* User_RegisterClassExW_t)
(
	WNDCLASSEXW *
);
typedef HWND(* User_CreateWindowExW_t)
(
	dword    ,
	LPCWSTR  ,
	LPCWSTR  ,
	dword    ,
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

ATOM User_Hook_RegisterClassExW
(
	WNDCLASSEXW * windowClass
);
HWND User_Hook_CreateWindowExW
(
	dword     exStyle,
	LPCWSTR   className,
	LPCWSTR   windowName,
	dword     style,
	int       x,
	int       y,
	int       width,
	int       height,
	HWND      parentWindow,
	HMENU     menu,
	HINSTANCE instance,
	LPVOID    parameter
);
LRESULT User_Hook_WindowProc
(
	HWND   window,
	UINT   message,
	WPARAM wParameter,
	LPARAM lParameter
);

ID3D11Device           * D3D11_device           = 0;
ID3D11DeviceContext    * D3D11_deviceContext    = 0;
ID3D11RenderTargetView * D3D11_renderTargetView = 0;

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
);

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

HRESULT DXGI_Hook_Present
(
	IDXGISwapChain * swapChain,
	UINT             syncInterval,
	UINT             flags
);
HRESULT DXGI_Hook_ResizeBuffers
(
	IDXGISwapChain * swapChain,
	UINT             bufferCount,
	UINT             width,
	UINT             height,
	DXGI_FORMAT      newFormat,
	UINT             swapChainFlags
);

IDirectInput8W       * DirectInput8_deviceInterface = 0;
IDirectInputDevice8W * DirectInput8_mouse           = 0;
DIMOUSESTATE2          DirectInput8_mouseState      = {};

static dword DirectInput8_CreateMouseThread(LPVOID parameter);
static dword DirectInput8_UpdateMouseThread(LPVOID parameter);
static dword DirectInput8_AcquireMouseThread(LPVOID parameter);

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
	dword     exStyle,
	LPCWSTR   className,
	LPCWSTR   windowName,
	dword     style,
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
	x = 0;
	y = 0;
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
	if (Config.System.Input.hideMouseCursor)
	{
		ToggleCursor(false);
	}
	else
	{
		ToggleCursor(true);
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
		ImGui_User_UpdateMouseCursor(window);
		break;
	case WM_CHAR:
		ImGui::GetIO().AddInputCharacter((uint16)wParameter);
		return 0;
	case DM_PAUSE:
		Pause(pause);
		return 1;
	}
	return User_WindowProc
	(
		window,
		message,
		wParameter,
		lParameter
	);
}

static void CreateRenderTarget()
{
	LogFunction();
	ID3D11Texture2D * backBuffer = 0;
	DXGI_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void **)&backBuffer);
	D3D11_device->CreateRenderTargetView(backBuffer, 0, &D3D11_renderTargetView);
	backBuffer->Release();
}

static void RemoveRenderTarget()
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

static void Timestep()
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
	dword error = GetLastError();
	D3D11_device = *device;
	D3D11_deviceContext = *deviceContext;
	DXGI_swapChain = *swapChain;
	appWindow = swapChainDescription->OutputWindow;
	// @Audit: Remove cast?
	System_Window_UpdateSize((uint32)swapChainDescription->BufferDesc.Width, (uint32)swapChainDescription->BufferDesc.Height);
	ImGui_D3D11_Init(D3D11_device, D3D11_deviceContext);
	CreateRenderTarget();
	InstallStart:
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


	if (Config.System.Graphics.vSync != 0)
	{
		syncInterval = (Config.System.Graphics.vSync - 1);
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
	dword error = GetLastError();
	CreateRenderTarget();
	System_Window_UpdateSize((uint32)width, (uint32)height);
	SetLastError(error);
	return result;
}

HRESULT DirectInput8_Hook_GetDeviceStateKeyboard
(
	IDirectInputDevice8A * device,
	dword                  bufferSize,
	LPVOID                 buffer
)
{
	byte * state = (byte *)buffer;
	ImGui_DirectInput8_UpdateKeyboard(state);
	Hotkeys_TogglePause(state);
	if (pause)
	{
		memset(buffer, 0, bufferSize);
	}
	return 0;
}

static dword DirectInput8_CreateMouseThread(LPVOID parameter)
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

static dword DirectInput8_UpdateMouseThread(LPVOID parameter)
{
	LogFunction();
	do
	{
		if (appWindow && pause)
		{
			DirectInput8_mouse->GetDeviceState(sizeof(DIMOUSESTATE2), &DirectInput8_mouseState);
			ImGui_DirectInput8_UpdateMouse(appWindow, &DirectInput8_mouseState);
		}
		Sleep(10);
	}
	while (true);
	return 1;
}

static dword DirectInput8_AcquireMouseThread(LPVOID parameter)
{
	do
	{
		LoopStart:
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

dword XInput_Hook_GetState
(
	dword          userIndex,
	XINPUT_STATE * state
)
{
	if (pause)
	{
		memset(state, 0, sizeof(XINPUT_STATE));
	}
	return 0;
}

void Hooks_Init()
{
	LogFunction();
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
	Write<dword>((appBaseAddr + 0x47F58), DISCL_NONEXCLUSIVE | DISCL_FOREGROUND); // SetCooperativeLevelKeyboard
	{
		byte sect0[] =
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
		byte sect2[] =
		{
			0x48, 0x8B, 0xE5, //mov rsp,rbp
			0x5D,             //pop rbp
			0x41, 0x58,       //pop r8
			0x5A,             //pop rdx
			0x59,             //pop rcx
			0x58,             //pop rax
		};
		FUNC func = CreateFunction(DirectInput8_Hook_GetDeviceStateKeyboard, (appBaseAddr + 0x41DA6), false, true, sizeof(sect0), 0, sizeof(sect2));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteJump((appBaseAddr + 0x41DA0), func.addr, 1);
	}
	{
		byte sect0[] =
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
		byte sect2[] =
		{
			0x48, 0x8B, 0xE5, //mov rsp,rbp
			0x5D,             //pop rbp
			0x41, 0x58,       //pop r8
			0x5A,             //pop rdx
			0x59,             //pop rcx
			0x58,             //pop rax
		};
		FUNC func = CreateFunction(DirectInput8_Hook_GetDeviceStateKeyboard, (appBaseAddr + 0x482B5), false, true, sizeof(sect0), 0, sizeof(sect2));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteJump((appBaseAddr + 0x482AD), func.addr);
	}
	CreateThread(0, 4096, DirectInput8_CreateMouseThread, 0, 0, 0);
	{
		byte sect0[] =
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
		byte sect2[] =
		{
			0x48, 0x8B, 0xE5,             //mov rsp,rbp
			0x5D,                         //pop rbp
			0x5A,                         //pop rdx
			0x59,                         //pop rcx
			0x58,                         //pop rax
		};
		FUNC func = CreateFunction(XInput_Hook_GetState, (appBaseAddr + 0x41A88), false, true, sizeof(sect0), 0, sizeof(sect2));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteCall((func.sect0 + 0xF), (appBaseAddr + 0x3453F6));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteJump((appBaseAddr + 0x41A83), func.addr);
	}
	{
		byte sect0[] =
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
		byte sect2[] =
		{
			0x48, 0x8B, 0xE5,             //mov rsp,rbp
			0x5D,                         //pop rbp
			0x5A,                         //pop rdx
			0x59,                         //pop rcx
			0x58,                         //pop rax
		};
		FUNC func = CreateFunction(XInput_Hook_GetState, (appBaseAddr + 0x41AFF), false, true, sizeof(sect0), 0, sizeof(sect2));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteCall((func.sect0 + 0xF), (appBaseAddr + 0x3453F6));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteJump((appBaseAddr + 0x41AFA), func.addr);
	}
	{
		byte sect0[] =
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
		byte sect2[] =
		{
			0x48, 0x8B, 0xE5,             //mov rsp,rbp
			0x5D,                         //pop rbp
			0x5A,                         //pop rdx
			0x59,                         //pop rcx
			0x58,                         //pop rax
		};
		FUNC func = CreateFunction(XInput_Hook_GetState, (appBaseAddr + 0x41C45), false, true, sizeof(sect0), 0, sizeof(sect2));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteCall((func.sect0 + 0xF), (appBaseAddr + 0x3453F6));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteJump((appBaseAddr + 0x41C40), func.addr);
	}
}
