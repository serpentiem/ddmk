#include "Hooks.h"

//#pragma warning(disable: 4102) // Unreferenced label.

typedef ATOM(* User_RegisterClassExW_t)
(
	WNDCLASSEXW *
);
typedef HWND(* User_CreateWindowExW_t)
(
	DWORD    ,
	LPCWSTR  ,
	LPCWSTR  ,
	DWORD    ,
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
	DWORD     exStyle,
	LPCWSTR   className,
	LPCWSTR   windowName,
	DWORD     style,
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

ID3D10Device           * D3D10_device           = 0;
ID3D10RenderTargetView * D3D10_renderTargetView = 0;

typedef HRESULT(* D3D10_CreateDeviceAndSwapChain_t)
(
	IDXGIAdapter         * ,
	D3D10_DRIVER_TYPE      ,
	HMODULE                ,
	UINT                   ,
	UINT                   ,
	DXGI_SWAP_CHAIN_DESC * ,
	IDXGISwapChain       **,
	ID3D10Device         **
);

D3D10_CreateDeviceAndSwapChain_t D3D10_CreateDeviceAndSwapChain = 0;

HRESULT D3D10_Hook_CreateDeviceAndSwapChain
(
	IDXGIAdapter         *  adapter,
	D3D10_DRIVER_TYPE       driverType,
	HMODULE                 software,
	UINT                    flags,
	UINT                    SDKVersion,
	DXGI_SWAP_CHAIN_DESC *  swapChainDescription,
	IDXGISwapChain       ** swapChain,
	ID3D10Device         ** device
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
	DWORD     exStyle,
	LPCWSTR   className,
	LPCWSTR   windowName,
	DWORD     style,
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
	//x = 0;
	//y = 0;
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
	ID3D10Texture2D * backBuffer = 0;
	DXGI_swapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (void **)&backBuffer);
	D3D10_device->CreateRenderTargetView(backBuffer, 0, &D3D10_renderTargetView);
	backBuffer->Release();
}

static void RemoveRenderTarget()
{
	LogFunction();
	if (!D3D10_renderTargetView)
	{
		return;
	}
	float32 clearColor[4] = {};
	D3D10_device->ClearRenderTargetView(D3D10_renderTargetView, clearColor);
	D3D10_renderTargetView->Release();
	D3D10_renderTargetView = 0;
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

HRESULT D3D10_Hook_CreateDeviceAndSwapChain
(
	IDXGIAdapter         *  adapter,
	D3D10_DRIVER_TYPE       driverType,
	HMODULE                 software,
	UINT                    flags,
	UINT                    SDKVersion,
	DXGI_SWAP_CHAIN_DESC *  swapChainDescription,
	IDXGISwapChain       ** swapChain,
	ID3D10Device         ** device
)
{
	Log
	(
		"%s "
		"%X "
		"%X "
		"%X "
		"%X "
		"%u "
		"%X "
		"%X "
		"%X",
		FUNC_NAME,
		adapter,
		driverType,
		software,
		flags,
		SDKVersion,
		swapChainDescription,
		swapChain,
		device
	);
	HRESULT result = D3D10_CreateDeviceAndSwapChain
	(
		adapter,
		driverType,
		software,
		flags,
		SDKVersion,
		swapChainDescription,
		swapChain,
		device
	);
	DWORD error = GetLastError();
	D3D10_device = *device;
	DXGI_swapChain = *swapChain;
	mainWindow = swapChainDescription->OutputWindow;
	// @Audit: Remove cast?
	System_Window_UpdateSize((uint32)swapChainDescription->BufferDesc.Width, (uint32)swapChainDescription->BufferDesc.Height);
	ImGui_D3D10_Init(D3D10_device);
	InstallStart:
	{
		if ((result != 0) || !swapChain || !*swapChain)
		{
			goto InstallEnd;
		}
		BYTE ** funcAddr = *(BYTE ***)*swapChain;
		if (!funcAddr)
		{
			goto InstallEnd;
		}
		DXGI_Present = (DXGI_Present_t)funcAddr[8];
		Write<void *>((BYTE *)&funcAddr[8], DXGI_Hook_Present);

		DXGI_ResizeBuffers = (DXGI_ResizeBuffers_t)funcAddr[13];
		Write<void *>((BYTE *)&funcAddr[13], DXGI_Hook_ResizeBuffers);
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
	ImGui_D3D10_NewFrame();
	Timestep();
	ImGui::NewFrame();
	GUI_Render();
	ImGui::Render();
	D3D10_device->OMSetRenderTargets(1, &D3D10_renderTargetView, 0);
	ImGui_D3D10_RenderDrawData(ImGui::GetDrawData());
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
	DWORD error = GetLastError();
	CreateRenderTarget();
	System_Window_UpdateSize((uint32)width, (uint32)height);
	SetLastError(error);
	return result;
}

HRESULT DirectInput8_Hook_GetDeviceStateKeyboard
(
	IDirectInputDevice8A * device,
	DWORD                  bufferSize,
	LPVOID                 buffer
)
{
	BYTE * state = (BYTE *)buffer;
	ImGui_DirectInput8_UpdateKeyboard(state);
	Hotkeys_TogglePause(state);
	if (pause)
	{
		memset(buffer, 0, bufferSize);
	}
	return 0;
}

HRESULT DirectInput8_Hook_GetDeviceStateMouse
(
	IDirectInputDevice8A * device,
	DWORD                  bufferSize,
	LPVOID                 buffer
)
{
	DIMOUSESTATE2 * state = (DIMOUSESTATE2 *)buffer;
	ImGui_DirectInput8_UpdateMouse(mainWindow, state);
	if (pause)
	{
		memset(buffer, 0, bufferSize);
	}
	return 0;
}

HRESULT DirectInput8_Hook_GetDeviceStateGamepad
(
	IDirectInputDevice8A * device,
	DWORD                  bufferSize,
	LPVOID                 buffer
)
{
	if (pause)
	{
		memset(buffer, 0, bufferSize);
	}
	return 0;
}

DWORD XInput_Hook_GetState
(
	DWORD          userIndex,
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
		BYTE * addr = (appBaseAddr + 0xB732F0);
		User_RegisterClassExW = *(User_RegisterClassExW_t *)addr;
		Write<void *>(addr, User_Hook_RegisterClassExW);
	}
	{
		BYTE * addr = (appBaseAddr + 0xB73328);
		User_CreateWindowExW = *(User_CreateWindowExW_t *)addr;
		Write<void *>(addr, User_Hook_CreateWindowExW);
	}
	{
		BYTE * addr = (appBaseAddr + 0xB733CC);
		D3D10_CreateDeviceAndSwapChain = *(D3D10_CreateDeviceAndSwapChain_t *)addr;
		Write<void *>(addr, D3D10_Hook_CreateDeviceAndSwapChain);
	}
	Write<BYTE>((appBaseAddr + 0x6E9BE1), DISCL_NONEXCLUSIVE | DISCL_FOREGROUND); // SetCooperativeLevelKeyboard
	Write<BYTE>((appBaseAddr + 0x6EA8B0), DISCL_NONEXCLUSIVE | DISCL_FOREGROUND); // SetCooperativeLevelMouse
	Write<BYTE>((appBaseAddr + 0x6ED9E6), DISCL_NONEXCLUSIVE | DISCL_FOREGROUND); // SetCooperativeLevelGamepad
	{
		BYTE sect0[] =
		{
			0x83, 0xEC, 0x10,             //sub esp,10
			0x51,                         //push ecx
			0x56,                         //push esi
			0x57,                         //push edi
			0xB9, 0x03, 0x00, 0x00, 0x00, //mov ecx,00000003
			0x8D, 0x74, 0x24, 0x1C,       //lea esi,[esp+1C]
			0x8D, 0x7C, 0x24, 0x0C,       //lea edi,[esp+0C]
			0xF3, 0xA5,                   //repe movsd
			0xB9, 0x03, 0x00, 0x00, 0x00, //mov ecx,00000003
			0x8D, 0x74, 0x24, 0x0C,       //lea esi,[esp+0C]
			0x8D, 0x7C, 0x24, 0x18,       //lea edi,[esp+18]
			0xF3, 0xA5,                   //repe movsd
			0x5F,                         //pop edi
			0x5E,                         //pop esi
			0x59,                         //pop ecx
			0x8B, 0x41, 0x24,             //mov eax,[ecx+24]
			0xFF, 0xD0,                   //call eax
			0x89, 0x44, 0x24, 0x0C,       //mov [esp+0C],eax
		};
		BYTE sect2[] =
		{
			0x58, //pop eax
		};
		FUNC func = CreateFunction(DirectInput8_Hook_GetDeviceStateKeyboard, (appBaseAddr + 0x6E9E55), false, true, sizeof(sect0), 0, sizeof(sect2));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteJump((appBaseAddr + 0x6E9E50), func.addr);
	}
	{
		BYTE sect0[] =
		{
			0x83, 0xEC, 0x10,             //sub esp,10
			0x51,                         //push ecx
			0x56,                         //push esi
			0x57,                         //push edi
			0xB9, 0x03, 0x00, 0x00, 0x00, //mov ecx,00000003
			0x8D, 0x74, 0x24, 0x1C,       //lea esi,[esp+1C]
			0x8D, 0x7C, 0x24, 0x0C,       //lea edi,[esp+0C]
			0xF3, 0xA5,                   //repe movsd
			0xB9, 0x03, 0x00, 0x00, 0x00, //mov ecx,00000003
			0x8D, 0x74, 0x24, 0x0C,       //lea esi,[esp+0C]
			0x8D, 0x7C, 0x24, 0x18,       //lea edi,[esp+18]
			0xF3, 0xA5,                   //repe movsd
			0x5F,                         //pop edi
			0x5E,                         //pop esi
			0x59,                         //pop ecx
			0x8B, 0x41, 0x24,             //mov eax,[ecx+24]
			0xFF, 0xD0,                   //call eax
			0x89, 0x44, 0x24, 0x0C,       //mov [esp+0C],eax
		};
		BYTE sect2[] =
		{
			0x58, //pop eax
		};
		FUNC func = CreateFunction(DirectInput8_Hook_GetDeviceStateMouse, (appBaseAddr + 0x6EA70E), false, true, sizeof(sect0), 0, sizeof(sect2));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteJump((appBaseAddr + 0x6EA709), func.addr);
	}
	{
		BYTE sect0[] =
		{
			0x68, 0x10, 0x01, 0x00, 0x00, //push 00000110
			0x57,                         //push edi
			0x83, 0xEC, 0x10,             //sub esp,10
			0x51,                         //push ecx
			0x56,                         //push esi
			0x57,                         //push edi
			0xB9, 0x03, 0x00, 0x00, 0x00, //mov ecx,00000003
			0x8D, 0x74, 0x24, 0x1C,       //lea esi,[esp+1C]
			0x8D, 0x7C, 0x24, 0x0C,       //lea edi,[esp+0C]
			0xF3, 0xA5,                   //repe movsd
			0xB9, 0x03, 0x00, 0x00, 0x00, //mov ecx,00000003
			0x8D, 0x74, 0x24, 0x0C,       //lea esi,[esp+0C]
			0x8D, 0x7C, 0x24, 0x18,       //lea edi,[esp+18]
			0xF3, 0xA5,                   //repe movsd
			0x5F,                         //pop edi
			0x5E,                         //pop esi
			0x59,                         //pop ecx
			0xFF, 0xD1,                   //call ecx
			0x89, 0x44, 0x24, 0x0C,       //mov [esp+0C],eax
		};
		BYTE sect2[] =
		{
			0x58, //pop eax
		};
		FUNC func = CreateFunction(DirectInput8_Hook_GetDeviceStateGamepad, (appBaseAddr + 0x6EE14E), false, true, sizeof(sect0), 0, sizeof(sect2));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteJump((appBaseAddr + 0x6EE146), func.addr);
	}
	{
		BYTE sect0[] =
		{
			0x83, 0xEC, 0x0C,             //sub esp,0C
			0x51,                         //push ecx
			0x56,                         //push esi
			0x57,                         //push edi
			0xB9, 0x02, 0x00, 0x00, 0x00, //mov ecx,00000002
			0x8D, 0x74, 0x24, 0x18,       //lea esi,[esp+18]
			0x8D, 0x7C, 0x24, 0x0C,       //lea edi,[esp+0C]
			0xF3, 0xA5,                   //repe movsd
			0xB9, 0x02, 0x00, 0x00, 0x00, //mov ecx,00000002
			0x8D, 0x74, 0x24, 0x0C,       //lea esi,[esp+0C]
			0x8D, 0x7C, 0x24, 0x14,       //lea edi,[esp+14]
			0xF3, 0xA5,                   //repe movsd
			0x5F,                         //pop edi
			0x5E,                         //pop esi
			0x59,                         //pop ecx
			0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc4.exe+AC2298
			0x89, 0x44, 0x24, 0x08,       //mov [esp+08],eax
		};
		BYTE sect2[] =
		{
			0x58, //pop eax
		};
		FUNC func = CreateFunction(XInput_Hook_GetState, (appBaseAddr + 0x6EB4E4), false, true, sizeof(sect0), 0, sizeof(sect2));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteCall((func.sect0 + 0x27), (appBaseAddr + 0xAC2298));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteJump((appBaseAddr + 0x6EB4DF), func.addr);
	}
	{
		BYTE sect0[] =
		{
			0x83, 0xEC, 0x0C,             //sub esp,0C
			0x51,                         //push ecx
			0x56,                         //push esi
			0x57,                         //push edi
			0xB9, 0x02, 0x00, 0x00, 0x00, //mov ecx,00000002
			0x8D, 0x74, 0x24, 0x18,       //lea esi,[esp+18]
			0x8D, 0x7C, 0x24, 0x0C,       //lea edi,[esp+0C]
			0xF3, 0xA5,                   //repe movsd
			0xB9, 0x02, 0x00, 0x00, 0x00, //mov ecx,00000002
			0x8D, 0x74, 0x24, 0x0C,       //lea esi,[esp+0C]
			0x8D, 0x7C, 0x24, 0x14,       //lea edi,[esp+14]
			0xF3, 0xA5,                   //repe movsd
			0x5F,                         //pop edi
			0x5E,                         //pop esi
			0x59,                         //pop ecx
			0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc4.exe+AC2298
			0x89, 0x44, 0x24, 0x08,       //mov [esp+08],eax
		};
		BYTE sect2[] =
		{
			0x58, //pop eax
		};
		FUNC func = CreateFunction(XInput_Hook_GetState, (appBaseAddr + 0x6EC99B), false, true, sizeof(sect0), 0, sizeof(sect2));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteCall((func.sect0 + 0x27), (appBaseAddr + 0xAC2298));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteJump((appBaseAddr + 0x6EC996), func.addr);
	}
	{
		BYTE sect0[] =
		{
			0x83, 0xEC, 0x0C,             //sub esp,0C
			0x51,                         //push ecx
			0x56,                         //push esi
			0x57,                         //push edi
			0xB9, 0x02, 0x00, 0x00, 0x00, //mov ecx,00000002
			0x8D, 0x74, 0x24, 0x18,       //lea esi,[esp+18]
			0x8D, 0x7C, 0x24, 0x0C,       //lea edi,[esp+0C]
			0xF3, 0xA5,                   //repe movsd
			0xB9, 0x02, 0x00, 0x00, 0x00, //mov ecx,00000002
			0x8D, 0x74, 0x24, 0x0C,       //lea esi,[esp+0C]
			0x8D, 0x7C, 0x24, 0x14,       //lea edi,[esp+14]
			0xF3, 0xA5,                   //repe movsd
			0x5F,                         //pop edi
			0x5E,                         //pop esi
			0x59,                         //pop ecx
			0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc4.exe+AC2298
			0x89, 0x44, 0x24, 0x08,       //mov [esp+08],eax
		};
		BYTE sect2[] =
		{
			0x58, //pop eax
		};
		FUNC func = CreateFunction(XInput_Hook_GetState, (appBaseAddr + 0x6EDE38), false, true, sizeof(sect0), 0, sizeof(sect2));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteCall((func.sect0 + 0x27), (appBaseAddr + 0xAC2298));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteJump((appBaseAddr + 0x6EDE33), func.addr);
	}
	{
		BYTE sect0[] =
		{
			0x83, 0xEC, 0x0C,             //sub esp,0C
			0x51,                         //push ecx
			0x56,                         //push esi
			0x57,                         //push edi
			0xB9, 0x02, 0x00, 0x00, 0x00, //mov ecx,00000002
			0x8D, 0x74, 0x24, 0x18,       //lea esi,[esp+18]
			0x8D, 0x7C, 0x24, 0x0C,       //lea edi,[esp+0C]
			0xF3, 0xA5,                   //repe movsd
			0xB9, 0x02, 0x00, 0x00, 0x00, //mov ecx,00000002
			0x8D, 0x74, 0x24, 0x0C,       //lea esi,[esp+0C]
			0x8D, 0x7C, 0x24, 0x14,       //lea edi,[esp+14]
			0xF3, 0xA5,                   //repe movsd
			0x5F,                         //pop edi
			0x5E,                         //pop esi
			0x59,                         //pop ecx
			0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc4.exe+AC2298
			0x89, 0x44, 0x24, 0x08,       //mov [esp+08],eax
		};
		BYTE sect2[] =
		{
			0x58, //pop eax
		};
		FUNC func = CreateFunction(XInput_Hook_GetState, (appBaseAddr + 0x6EDF69), false, true, sizeof(sect0), 0, sizeof(sect2));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteCall((func.sect0 + 0x27), (appBaseAddr + 0xAC2298));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteJump((appBaseAddr + 0x6EDF64), func.addr);
	}
	{
		BYTE sect0[] =
		{
			0x83, 0xEC, 0x0C,             //sub esp,0C
			0x51,                         //push ecx
			0x56,                         //push esi
			0x57,                         //push edi
			0xB9, 0x02, 0x00, 0x00, 0x00, //mov ecx,00000002
			0x8D, 0x74, 0x24, 0x18,       //lea esi,[esp+18]
			0x8D, 0x7C, 0x24, 0x0C,       //lea edi,[esp+0C]
			0xF3, 0xA5,                   //repe movsd
			0xB9, 0x02, 0x00, 0x00, 0x00, //mov ecx,00000002
			0x8D, 0x74, 0x24, 0x0C,       //lea esi,[esp+0C]
			0x8D, 0x7C, 0x24, 0x14,       //lea edi,[esp+14]
			0xF3, 0xA5,                   //repe movsd
			0x5F,                         //pop edi
			0x5E,                         //pop esi
			0x59,                         //pop ecx
			0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc4.exe+AC2298
			0x89, 0x44, 0x24, 0x08,       //mov [esp+08],eax
		};
		BYTE sect2[] =
		{
			0x58, //pop eax
		};
		FUNC func = CreateFunction(XInput_Hook_GetState, (appBaseAddr + 0x6EE0A7), false, true, sizeof(sect0), 0, sizeof(sect2));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteCall((func.sect0 + 0x27), (appBaseAddr + 0xAC2298));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteJump((appBaseAddr + 0x6EE0A2), func.addr);
	}
}
