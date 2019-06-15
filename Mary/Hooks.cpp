#include "Hooks.h"

namespace User
{
	typedef ATOM(* _RegisterClassExW)
	(
		WNDCLASSEXW *
	);
	typedef HWND(* _CreateWindowExW)
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
	typedef LRESULT(* _WindowProc)
	(
		HWND,
		UINT,
		WPARAM,
		LPARAM
	);

	_RegisterClassExW RegisterClassExW = 0;
	_CreateWindowExW  CreateWindowExW  = 0;
	_WindowProc       WindowProc       = 0;

	namespace Hook
	{
		ATOM RegisterClassExW
		(
			WNDCLASSEXW * windowClass
		);

		HWND CreateWindowExW
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

		LRESULT WindowProc
		(
			HWND   window,
			UINT   message,
			WPARAM wParameter,
			LPARAM lParameter
		);
	}
}

namespace D3D11
{
	ID3D11Device           * device           = 0;
	ID3D11DeviceContext    * deviceContext    = 0;
	ID3D11RenderTargetView * renderTargetView = 0;

	typedef HRESULT(* _CreateDeviceAndSwapChain)
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

	_CreateDeviceAndSwapChain CreateDeviceAndSwapChain = 0;

	namespace Hook
	{
		HRESULT CreateDeviceAndSwapChain
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
	}
}

namespace DXGI
{
	IDXGISwapChain * swapChain = 0;

	typedef HRESULT(* _Present)
	(
		IDXGISwapChain *,
		UINT            ,
		UINT
	);
	typedef HRESULT(* _ResizeBuffers)
	(
		IDXGISwapChain *,
		UINT            ,
		UINT            ,
		UINT            ,
		DXGI_FORMAT     ,
		UINT
	);

	_Present       Present       = 0;
	_ResizeBuffers ResizeBuffers = 0;

	namespace Hook
	{
		HRESULT Present
		(
			IDXGISwapChain * swapChain,
			UINT             syncInterval,
			UINT             flags
		);

		HRESULT ResizeBuffers
		(
			IDXGISwapChain * swapChain,
			UINT             bufferCount,
			UINT             width,
			UINT             height,
			DXGI_FORMAT      newFormat,
			UINT             swapChainFlags
		);
	}
}

namespace DirectInput8
{
	IDirectInput8W       * deviceInterface = 0;
	IDirectInputDevice8W * mainMouse       = 0;
	DIMOUSESTATE2          mainMouseState  = {};

	DWORD CreateMouse
	(
		LPVOID parameter
	);
	DWORD MouseOnUpdate
	(
		LPVOID paramter
	);

	namespace Hook
	{
		HRESULT GetDeviceStateKeyboard
		(
			IDirectInputDevice8W * device,
			DWORD                  bufferSize,
			LPVOID                 buffer
		);
	}
}

namespace XInput
{
	namespace Hook
	{
		DWORD GetState
		(
			DWORD          userIndex,
			XINPUT_STATE * state
		);
	}
}

#pragma region User

ATOM User::Hook::RegisterClassExW
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
		ImGui::User::Init();
		ImGui::DirectInput8::Init();
		GUI_Init();
		User::WindowProc = windowClass->lpfnWndProc;
		windowClass->lpfnWndProc = WindowProc;
	}
	return User::RegisterClassExW
	(
		windowClass
	);
}

HWND User::Hook::CreateWindowExW
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
	if (Config.System.Input.Mouse.hideCursor)
	{
		ToggleCursor(false);
	}
	else
	{
		ToggleCursor(true);
	}
	return User::CreateWindowExW
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

LRESULT User::Hook::WindowProc
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
	case WM_SETFOCUS:
		if (DirectInput8::mainMouse)
		{
			DirectInput8::mainMouse->Acquire();
		}
	case WM_SETCURSOR:
		ImGui::User::UpdateMouseCursor(window);
		break;
	case WM_CHAR:
		ImGui::GetIO().AddInputCharacter((uint16)wParameter);
		return 0;
	case DM_PAUSE:
		Pause(pause);
		return 1;
	}
	return User::WindowProc
	(
		window,
		message,
		wParameter,
		lParameter
	);
}

#pragma endregion

static void CreateRenderTarget()
{
	LogFunction();
	ID3D11Texture2D * backBuffer = 0;
	DXGI::swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void **)&backBuffer);
	D3D11::device->CreateRenderTargetView(backBuffer, 0, &D3D11::renderTargetView);
	backBuffer->Release();
}

static void RemoveRenderTarget()
{
	LogFunction();
	if (!D3D11::renderTargetView)
	{
		return;
	}
	float32 clearColor[4] = {};
	D3D11::deviceContext->ClearRenderTargetView(D3D11::renderTargetView, clearColor);
	D3D11::renderTargetView->Release();
	D3D11::renderTargetView = 0;
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

#pragma region D3D11

HRESULT D3D11::Hook::CreateDeviceAndSwapChain
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
	HRESULT result = D3D11::CreateDeviceAndSwapChain
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
	DWORD error = GetLastError();
	D3D11::device        = *device;
	D3D11::deviceContext = *deviceContext;
	DXGI::swapChain      = *swapChain;
	mainWindow           = swapChainDescription->OutputWindow;
	System::Window::UpdateWindowSize((uint32)swapChainDescription->BufferDesc.Width, (uint32)swapChainDescription->BufferDesc.Height);
	ImGui::D3D11::Init(D3D11::device, D3D11::deviceContext);

	CreateRenderTarget();

	BYTE * table = *(BYTE **)*swapChain;
	if (!table)
	{
		SetLastError(error);
		return result;
	}
	BYTE ** funcAddr = (BYTE **)table;

	DXGI::Present = (DXGI::_Present)funcAddr[8];
	Write<void *>((BYTE *)&funcAddr[8], DXGI::Hook::Present);

	DXGI::ResizeBuffers = (DXGI::_ResizeBuffers)funcAddr[13];
	Write<void *>((BYTE *)&funcAddr[13], DXGI::Hook::ResizeBuffers);

	SetLastError(error);
	return result;
}

#pragma endregion

#pragma region DXGI

HRESULT DXGI::Hook::Present
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
	ImGui::D3D11::NewFrame();
	Timestep();
	ImGui::NewFrame();
	GUI_Render();
	ImGui::Render();
	D3D11::deviceContext->OMSetRenderTargets(1, &D3D11::renderTargetView, 0);
	ImGui::D3D11::RenderDrawData(ImGui::GetDrawData());
	return DXGI::Present
	(
		swapChain,
		syncInterval,
		flags
	);
}

HRESULT DXGI::Hook::ResizeBuffers
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
	HRESULT result = DXGI::ResizeBuffers
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
	System::Window::UpdateWindowSize((uint32)width, (uint32)height);
	SetLastError(error);
	return result;
}

#pragma endregion

#pragma region DirectInput8

DWORD DirectInput8::CreateMouse(LPVOID parameter)
{
	do
	{
		if (mainWindow)
		{
			break;
		}
		Sleep(100);
	}
	while (true);

	LogFunction();
	HRESULT result = 0;

	result = DirectInput8Create((HINSTANCE)appBaseAddr, 0x800, IID_IDirectInput8W, (void **)&deviceInterface, 0);
	if (result != DI_OK)
	{
		Log("%s failed. Create %X %X", FUNC_NAME, result, GetLastError());
		goto Return;
	}

	result = deviceInterface->CreateDevice(GUID_SysMouse, &mainMouse, 0);
	if (result != DI_OK)
	{
		Log("%s failed. CreateDevice %X %X", FUNC_NAME, result, GetLastError());
		goto Return;
	}

	result = mainMouse->SetCooperativeLevel(mainWindow, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (result != DI_OK)
	{
		Log("%s failed. SetCooperativeLevel %X %X", FUNC_NAME, result, GetLastError());
		goto Return;
	}

	result = mainMouse->SetDataFormat(&c_dfDIMouse2);
	if (result != DI_OK)
	{
		Log("%s failed. SetDataFormat %X %X", FUNC_NAME, result, GetLastError());
		goto Return;
	}

	result = mainMouse->Acquire();

	CreateThread(0, 4096, MouseOnUpdate, 0, 0, 0);

Return:
	return 1;
}

DWORD DirectInput8::MouseOnUpdate(LPVOID paramter)
{
	LogFunction();
	do
	{
		if (mainWindow && pause)
		{
			mainMouse->GetDeviceState(sizeof(DIMOUSESTATE2), &mainMouseState);
			ImGui::DirectInput8::UpdateMouse(mainWindow, &mainMouseState);
		}
		Sleep(Config.System.Input.Mouse.updateRate);
	}
	while (true);
	return 1;
}

HRESULT DirectInput8::Hook::GetDeviceStateKeyboard
(
	IDirectInputDevice8W * device,
	DWORD                  bufferSize,
	LPVOID                 buffer
)
{
	BYTE * state = (BYTE *)buffer;
	ImGui::DirectInput8::UpdateKeyboard(state);
	Hotkeys::TogglePause(state);
	if (pause)
	{
		memset(buffer, 0, bufferSize);
	}
	return 0;
}

#pragma endregion

#pragma region XInput

DWORD XInput::Hook::GetState
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

#pragma endregion

void Hooks::Init()
{
	LogFunction();
	{
		BYTE * addr = (appBaseAddr + 0x34F308);
		User::RegisterClassExW = *(User::_RegisterClassExW *)addr;
		Write<void *>(addr, User::Hook::RegisterClassExW);
	}
	{
		BYTE * addr = (appBaseAddr + 0x34F300);
		User::CreateWindowExW = *(User::_CreateWindowExW *)addr;
		Write<void *>(addr, User::Hook::CreateWindowExW);
	}
	{
		BYTE * addr = (appBaseAddr + 0x34F650);
		D3D11::CreateDeviceAndSwapChain = *(D3D11::_CreateDeviceAndSwapChain *)addr;
		Write<void *>(addr, D3D11::Hook::CreateDeviceAndSwapChain);
	}
	Write<DWORD>((appBaseAddr + 0x47F58), DISCL_NONEXCLUSIVE | DISCL_FOREGROUND); // Keyboard Cooperative Level
	{
		BYTE payload[] =
		{
			0x48, 0x8B, 0x01,                                           //mov rax,[rcx]
			0x50,                                                       //push rax
			0x51,                                                       //push rcx
			0x52,                                                       //push rdx
			0x41, 0x50,                                                 //push r8
			0x55,                                                       //push rbp
			0x48, 0x8B, 0xEC,                                           //mov rbp,rsp
			0x40, 0x80, 0xE4, 0xF0,                                     //and spl,F0
			0x48, 0x83, 0xEC, 0x20,                                     //sub rsp,20
			0xFF, 0x50, 0x48,                                           //call qword ptr [rax+48]
			0x48, 0x89, 0x45, 0x20,                                     //mov [rbp+20],rax
			0x48, 0x8B, 0x4D, 0x18,                                     //mov rcx,[rbp+18]
			0x48, 0x8B, 0x55, 0x10,                                     //mov rdx,[rbp+10]
			0x4C, 0x8B, 0x45, 0x08,                                     //mov r8,[rbp+08]
			0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rax,GetDeviceStateKeyboard
			0xFF, 0xD0,                                                 //call rax
			0x48, 0x8B, 0xE5,                                           //mov rsp,rbp
			0x5D,                                                       //pop rbp
			0x41, 0x58,                                                 //pop r8
			0x5A,                                                       //pop rdx
			0x59,                                                       //pop rcx
			0x58,                                                       //pop rax
			0xE9, 0x00, 0x00, 0x00, 0x00,                               //jmp dmc3.exe+41DA6
		};
		FUNC func = CreateFunction(0, 0, false, false, sizeof(payload));
		memcpy(func.addr, payload, sizeof(payload));
		*(void **)(func.addr + 0x29) = DirectInput8::Hook::GetDeviceStateKeyboard;
		WriteJump((func.addr + 0x3C), (appBaseAddr + 0x41DA6));
		WriteJump((appBaseAddr + 0x41DA0), func.addr, 1);
	}
	{
		BYTE payload[] =
		{
			0xBA, 0x00, 0x01, 0x00, 0x00,                               //mov edx,00000100
			0x50,                                                       //push rax
			0x51,                                                       //push rcx
			0x52,                                                       //push rdx
			0x41, 0x50,                                                 //push r8
			0x55,                                                       //push rbp
			0x48, 0x8B, 0xEC,                                           //mov rbp,rsp
			0x40, 0x80, 0xE4, 0xF0,                                     //and spl,F0
			0x48, 0x83, 0xEC, 0x20,                                     //sub rsp,20
			0xFF, 0x50, 0x48,                                           //call qword ptr [rax+48]
			0x48, 0x89, 0x45, 0x20,                                     //mov [rbp+20],rax
			0x48, 0x8B, 0x4D, 0x18,                                     //mov rcx,[rbp+18]
			0x48, 0x8B, 0x55, 0x10,                                     //mov rdx,[rbp+10]
			0x4C, 0x8B, 0x45, 0x08,                                     //mov r8,[rbp+08]
			0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rax,GetDeviceStateKeyboard
			0xFF, 0xD0,                                                 //call rax
			0x48, 0x8B, 0xE5,                                           //mov rsp,rbp
			0x5D,                                                       //pop rbp
			0x41, 0x58,                                                 //pop r8
			0x5A,                                                       //pop rdx
			0x59,                                                       //pop rcx
			0x58,                                                       //pop rax
			0xE9, 0x00, 0x00, 0x00, 0x00,                               //jmp dmc3.exe+482B5
		};
		FUNC func = CreateFunction(0, 0, false, false, sizeof(payload));
		memcpy(func.addr, payload, sizeof(payload));
		*(void **)(func.addr + 0x2B) = DirectInput8::Hook::GetDeviceStateKeyboard;
		WriteJump((func.addr + 0x3E), (appBaseAddr + 0x482B5));
		WriteJump((appBaseAddr + 0x482AD), func.addr);
	}
	{
		BYTE payload[] =
		{
			0x50,                                                       //push rax
			0x51,                                                       //push rcx
			0x52,                                                       //push rdx
			0x55,                                                       //push rbp
			0x48, 0x8B, 0xEC,                                           //mov rbp,rsp
			0x40, 0x80, 0xE4, 0xF0,                                     //and spl,F0
			0x48, 0x83, 0xEC, 0x20,                                     //sub rsp,20
			0xFF, 0x15, 0x00, 0x00, 0x00, 0x00,                         //call qword ptr [dmc3.exe+34F410]
			0x48, 0x89, 0x45, 0x18,                                     //mov [rbp+18],rax
			0x48, 0x8B, 0x4D, 0x10,                                     //mov rcx,[rbp+10]
			0x48, 0x8B, 0x55, 0x08,                                     //mov rdx,[rbp+08]
			0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rax,GetState
			0xFF, 0xD0,                                                 //call rax
			0x48, 0x8B, 0xE5,                                           //mov rsp,rbp
			0x5D,                                                       //pop rbp
			0x5A,                                                       //pop rdx
			0x59,                                                       //pop rcx
			0x58,                                                       //pop rax
			0xE9, 0x00, 0x00, 0x00, 0x00,                               //jmp dmc3.exe+41A88
		};
		FUNC func = CreateFunction(0, 0, false, false, sizeof(payload));
		memcpy(func.addr, payload, sizeof(payload));
		WriteAddress((func.addr + 0xF), (appBaseAddr + 0x34F410), 6);
		*(void **)(func.addr + 0x23) = XInput::Hook::GetState;
		WriteJump((func.addr + 0x34), (appBaseAddr + 0x41A88));
		WriteJump((appBaseAddr + 0x41A83), func.addr);
	}
	{
		BYTE payload[] =
		{
			0x50,                                                       //push rax
			0x51,                                                       //push rcx
			0x52,                                                       //push rdx
			0x55,                                                       //push rbp
			0x48, 0x8B, 0xEC,                                           //mov rbp,rsp
			0x40, 0x80, 0xE4, 0xF0,                                     //and spl,F0
			0x48, 0x83, 0xEC, 0x20,                                     //sub rsp,20
			0xFF, 0x15, 0x00, 0x00, 0x00, 0x00,                         //call qword ptr [dmc3.exe+34F410]
			0x48, 0x89, 0x45, 0x18,                                     //mov [rbp+18],rax
			0x48, 0x8B, 0x4D, 0x10,                                     //mov rcx,[rbp+10]
			0x48, 0x8B, 0x55, 0x08,                                     //mov rdx,[rbp+08]
			0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rax,GetState
			0xFF, 0xD0,                                                 //call rax
			0x48, 0x8B, 0xE5,                                           //mov rsp,rbp
			0x5D,                                                       //pop rbp
			0x5A,                                                       //pop rdx
			0x59,                                                       //pop rcx
			0x58,                                                       //pop rax
			0xE9, 0x00, 0x00, 0x00, 0x00,                               //jmp dmc3.exe+41AFF
		};
		FUNC func = CreateFunction(0, 0, false, false, sizeof(payload));
		memcpy(func.addr, payload, sizeof(payload));
		WriteAddress((func.addr + 0xF), (appBaseAddr + 0x34F410), 6);
		*(void **)(func.addr + 0x23) = XInput::Hook::GetState;
		WriteJump((func.addr + 0x34), (appBaseAddr + 0x41AFF));
		WriteJump((appBaseAddr + 0x41AFA), func.addr);
	}
	{
		BYTE payload[] =
		{
			0x50,                                                       //push rax
			0x51,                                                       //push rcx
			0x52,                                                       //push rdx
			0x55,                                                       //push rbp
			0x48, 0x8B, 0xEC,                                           //mov rbp,rsp
			0x40, 0x80, 0xE4, 0xF0,                                     //and spl,F0
			0x48, 0x83, 0xEC, 0x20,                                     //sub rsp,20
			0xFF, 0x15, 0x00, 0x00, 0x00, 0x00,                         //call qword ptr [dmc3.exe+34F410]
			0x48, 0x89, 0x45, 0x18,                                     //mov [rbp+18],rax
			0x48, 0x8B, 0x4D, 0x10,                                     //mov rcx,[rbp+10]
			0x48, 0x8B, 0x55, 0x08,                                     //mov rdx,[rbp+08]
			0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rax,GetState
			0xFF, 0xD0,                                                 //call rax
			0x48, 0x8B, 0xE5,                                           //mov rsp,rbp
			0x5D,                                                       //pop rbp
			0x5A,                                                       //pop rdx
			0x59,                                                       //pop rcx
			0x58,                                                       //pop rax
			0xE9, 0x00, 0x00, 0x00, 0x00,                               //jmp dmc3.exe+41C45
		};
		FUNC func = CreateFunction(0, 0, false, false, sizeof(payload));
		memcpy(func.addr, payload, sizeof(payload));
		WriteAddress((func.addr + 0xF), (appBaseAddr + 0x34F410), 6);
		*(void **)(func.addr + 0x23) = XInput::Hook::GetState;
		WriteJump((func.addr + 0x34), (appBaseAddr + 0x41C45));
		WriteJump((appBaseAddr + 0x41C40), func.addr);
	}
	CreateThread(0, 4096, DirectInput8::CreateMouse, 0, 0, 0);
}
