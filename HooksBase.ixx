module;
#include "ThirdParty/ImGui/imgui.h"
export module HooksBase;

import Core;
import Core_ImGui;
import Core_Input;

#include "Core/Macros.h"

import Windows;
import DXGI;
import D3D10;
import D3D11;
import DI8;
import XI;

using namespace Windows;

import GUIBase;

import Config;
import Global;
import GUI;   // Init, Render
import Input; // ToggleCursor
import Vars;

#define debug false



export namespaceStart(API);
enum
{
	D3D10,
	D3D11,
};
namespaceEnd();



export void UpdateMousePositionMultiplier()
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













//namespaceStart(DI8);

void CreateKeyboard()
{
	LogFunction();

	if (!keyboard.Create())
	{
		Log("keyboard.Create failed.");

		return;
	}
}



export typedef void(* UpdateKeyboard_func_t)(DI8::DIKEYBOARDSTATE * stateAddr);

export UpdateKeyboard_func_t UpdateKeyboard_func = 0;



export typedef void(* UpdateGamepad_func_t)(DI8::DIJOYSTATE * stateAddr);

export UpdateGamepad_func_t UpdateGamepad_func = 0;










#if debug

void WindowSize1()
{
	LogFunction();

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

void WindowSize2()
{
	LogFunction();

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

void WindowSize3()
{
	LogFunction();

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

#endif









// @Update

void UpdateKeyboard()
{
	keyboard.Update();

	ImGui::DI8::UpdateKeyboard(&keyboard.state);



	auto & state = keyboard.state;





	for_all(index, countof(keyBindings))
	{
		auto & keyBinding = keyBindings[index];

		keyBinding.UpdateKeyData(state.keys);
		keyBinding.Check(state.keys);
	}



	// @Move

	[&]()
	{
		auto func = UpdateKeyboard_func;
		if (!func)
		{
			return;
		}

		func(&keyboard.state);
	}();













	#if debug

	static KeyData keyData[] =
	{
		{
			{
				::DI8::KEY::LEFT_CONTROL,
				::DI8::KEY::ONE,
			},
			2,
			false,
			WindowSize1
		},
		{
			{
				::DI8::KEY::LEFT_CONTROL,
				::DI8::KEY::TWO,
			},
			2,
			false,
			WindowSize2
		},
		{
			{
				::DI8::KEY::LEFT_CONTROL,
				::DI8::KEY::THREE,
			},
			2,
			false,
			WindowSize3
		},
	};

	for_all(index, countof(keyData))
	{
		keyData[index].Check(keyboard.state.keys);
	}

	#endif


















}



void CreateMouse()
{
	LogFunction();

	if (!mouse.Create())
	{
		Log("mouse.Create failed.");

		return;
	}
}

void UpdateMouse()
{
	mouse.Update();

	ImGui::DI8::UpdateMouse
	(
		appWindow,
		&mouse.state
	);
}











BOOL CreateGamepad_EnumFunction
(
	DI8::LPCDIDEVICEINSTANCEA deviceInstanceAddr,
	LPVOID pvRef
)
{
	DebugLogFunction();



	if (!deviceInstanceAddr)
	{
		Log("!deviceInstanceAddr");

		return DI8::DIENUM_CONTINUE;
	}

	auto & deviceInstance = *deviceInstanceAddr;




	// Log    ("dwSize          %X", deviceInstance.dwSize                  );
	// LogGUID("guidInstance    "  , deviceInstance.guidInstance            );
	// LogGUID("guidProduct     "  , deviceInstance.guidProduct             );
	// Log    ("dwDevType       %X", deviceInstance.dwDevType               );
	// Log    ("dwDevType[0]    %X", (deviceInstance.dwDevType & 0xFF));
	// Log    ("dwDevType[1]    %X", ((deviceInstance.dwDevType >> 8) & 0xFF));



	// Log    ("tszInstanceName %s", deviceInstance.tszInstanceName         );
	// Log    ("tszProductName  %s", deviceInstance.tszProductName          );
	// LogGUID("guidFFDriver    "  , deviceInstance.guidFFDriver            );
	// Log    ("wUsagePage      %X", deviceInstance.wUsagePage              );
	// Log    ("wUsage          %X", deviceInstance.wUsage                  );


	// Log<false>("");





	if
	(
		strcmp
		(
			deviceInstance.tszInstanceName,
			activeConfig.gamepadName
		) != 0
	)
	{
		// Log("No Match $%s$ $%s$", deviceInstance.tszInstanceName, activeConfig.gamepadName);
		// Log<false>("");

		return DI8::DIENUM_CONTINUE;
	}












	CopyMemory
	(
		&gamepad.deviceInstance,
		&deviceInstance,
		sizeof(gamepad.deviceInstance)
	);



	gamepad.match = true;


	return DI8::DIENUM_STOP;
}

void CreateGamepad()
{
	LogFunction();

	gamepad.enumFunc = CreateGamepad_EnumFunction;

	if (!gamepad.Create())
	{
		Log("gamepad.Create failed.");

		return;
	}
}

void UpdateGamepad()
{





	if
	(
		(GetForegroundWindow() != appWindow) &&
		!activeConfig.forceWindowFocus
	)
	{
		return;
	}






	gamepad.Update();




	auto & state = gamepad.state;




	auto button = activeConfig.gamepadButton;
	if (button > countof(state.rgbButtons))
	{
		button = 0;
	}

	static bool execute = false;

	if (state.rgbButtons[button])
	{
		if (execute)
		{
			execute = false;

			ToggleShowMain();
		}
	}
	else
	{
		execute = true;
	}








	[&]()
	{
		auto func = UpdateGamepad_func;
		if (!func)
		{
			return;
		}

		func(&gamepad.state);
	}();



}

//namespaceEnd();






namespaceStart(XI);

export void UpdateGamepad()
{


	// @Merge
	if
	(
		(GetForegroundWindow() != appWindow) &&
		!activeConfig.forceWindowFocus
	)
	{
		return;
	}

	if (!g_show)
	{
		return;
	}



	new_XInputGetState
	(
		0,
		&state
	);



	::ImGui::XI::UpdateGamepad(&state);




}



namespaceEnd();
















// @Research: template- and reference-less solution. Use void **.
export template
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

export typedef WNDPROC WindowProc_t;
export typedef decltype(RegisterClassExW) * RegisterClassExW_t;
export typedef decltype(CreateWindowExW) * CreateWindowExW_t;
export typedef decltype(CreateFileA) * CreateFileA_t;
export typedef decltype(CreateFileW) * CreateFileW_t;

namespaceEnd();



namespaceStart(Base::Windows);

export ::Windows::WindowProc_t WindowProc = 0;
export ::Windows::RegisterClassExW_t RegisterClassExW = 0;
export ::Windows::CreateWindowExW_t CreateWindowExW = 0;
export ::Windows::CreateFileA_t CreateFileA = 0;
export ::Windows::CreateFileW_t CreateFileW = 0;

namespaceEnd();



namespaceStart(Hook::Windows);

export LRESULT WindowProc
(
	HWND windowHandle,
	UINT message,
	WPARAM wParameter,
	LPARAM lParameter
)
{
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
			#ifdef _WIN64
			"%s "
			"%llX "
			"%X "
			"%llX "
			"%llX",
			#else
			"%s "
			"%X "
			"%X "
			"%X "
			"%X",
			#endif
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



	SetLastError(error);

	return result;
}
























export ATOM RegisterClassExW(const WNDCLASSEXW * windowClassAddr)
{
	Log
	(
		#ifdef _WIN64
		"%s "
		"%llX",
		#else
		"%s "
		"%X",
		#endif
		FUNC_NAME,
		windowClassAddr
	);



	if (!windowClassAddr)
	{
		goto Return;
	}



	{
		auto & windowClass = *const_cast<WNDCLASSEXW *>(windowClassAddr);

		static bool run = false;
		if (!run)
		{
			run = true;

			ImGui::CreateContext();

			auto & io = ImGui::GetIO();

			io.IniFilename = 0;


			io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

			io.BackendFlags |= ImGuiBackendFlags_HasGamepad;



			ImGui::DI8::Init();

			GUI_Init();












			::Base::Windows::WindowProc = windowClass.lpfnWndProc;

			windowClass.lpfnWndProc = ::Hook::Windows::WindowProc;
		}
	}



	Return:;
	{
		return ::Base::Windows::RegisterClassExW(windowClassAddr);
	}
}

export HWND CreateWindowExW
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



	Log
	(
		#ifdef _WIN64
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
		#else
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
		#endif
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

	ToggleCursor(); // CreateWindowExW

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



export typedef void(* CreateFileA_func_t)(LPCSTR lpFileName);

export CreateFileA_func_t CreateFileA_func = 0;

export HANDLE CreateFileA
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
	[&]()
	{
		auto func = CreateFileA_func;
		if (!func)
		{
			return;
		}

		func(lpFileName);
	}();



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

export HANDLE CreateFileW
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
	g_show =
	(
		// activeConfig.welcome ||
		g_showMain ||
		g_showShop
	);

	if (g_lastShow != g_show)
	{
		g_lastShow = g_show;

		ToggleCursor(); // g_show
	}
}







export template <new_size_t api>
void CreateRenderTarget()
{
	LogFunction();

	if constexpr (api == API::D3D10)
	{
		using namespace D3D10;

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
	else if constexpr (api == API::D3D11)
	{
		using namespace D3D11;

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
}

export template <new_size_t api>
void RemoveRenderTarget()
{
	LogFunction();

	if constexpr (api == API::D3D10)
	{
		if (!::D3D10::renderTargetView)
		{
			return;
		}
		float clearColor[4] = {};
		::D3D10::device->ClearRenderTargetView(::D3D10::renderTargetView, clearColor);
		::D3D10::renderTargetView->Release();
		::D3D10::renderTargetView = 0;

	}
	else if constexpr (api == API::D3D11)
	{
		if (!::D3D11::renderTargetView)
		{
			return;
		}
		float clearColor[4] = {};
		::D3D11::deviceContext->ClearRenderTargetView(::D3D11::renderTargetView, clearColor);
		::D3D11::renderTargetView->Release();
		::D3D11::renderTargetView = 0;
	}
}

export void Timestep()
{
	static uint64 frequency   = 0;
	static uint64 mainCounter = 0;
	static bool   run         = false;

	uint64 currentCounter = 0;

	if (!run)
	{
		run = true;

		QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER *>(&frequency));
		QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER *>(&mainCounter));
	}

	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER *>(&currentCounter));

	ImGui::GetIO().DeltaTime = (static_cast<float>(currentCounter - mainCounter) / static_cast<float>(frequency));

	mainCounter = currentCounter;
}



#pragma region DXGI

namespaceStart(DXGI);

export typedef HRESULT(* Present_t)
(
	IDXGISwapChain * SwapChain,
	UINT SyncInterval,
	UINT Flags
);
export typedef HRESULT (* ResizeBuffers_t)
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

export ::DXGI::Present_t Present = 0;
export ::DXGI::ResizeBuffers_t ResizeBuffers = 0;

namespaceEnd();



namespaceStart(Hook::DXGI);

export typedef void(* Present_func_t)();

export Present_func_t Present_func = 0;

export template <new_size_t api>
HRESULT Present
(
	::DXGI::IDXGISwapChain * SwapChain,
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
			#ifdef _WIN64
			"%s "
			"%llX "
			"%u "
			"%X",
			#else
			"%s "
			"%X "
			"%u "
			"%X",
			#endif
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





	UpdateKeyboard();
	UpdateMouse();
	UpdateGamepad();

	XI::UpdateGamepad();














	if constexpr (api == API::D3D10)
	{
		ImGui::D3D10::NewFrame();
	}
	else if constexpr (api == API::D3D11)
	{
		ImGui::D3D11::NewFrame();
	}



	Timestep();

	ImGui::NewFrame();

	GUI_Render();

	ImGui::Render();



	if constexpr (api == API::D3D10)
	{
		::D3D10::device->OMSetRenderTargets
		(
			1,
			&::D3D10::renderTargetView,
			0
		);

		ImGui::D3D10::RenderDrawData(ImGui::GetDrawData());
	}
	else if constexpr (api == API::D3D11)
	{
		::D3D11::deviceContext->OMSetRenderTargets
		(
			1,
			&::D3D11::renderTargetView,
			0
		);

		ImGui::D3D11::RenderDrawData(ImGui::GetDrawData());
	}



	[&]()
	{
		auto func = Present_func;
		if (!func)
		{
			return;
		}

		func();
	}();



	return ::Base::DXGI::Present
	(
		SwapChain,
		SyncInterval,
		Flags
	);
}

export template <new_size_t api>
HRESULT ResizeBuffers
(
	::DXGI::IDXGISwapChain * SwapChain,
	UINT BufferCount,
	UINT Width,
	UINT Height,
	::DXGI::DXGI_FORMAT NewFormat,
	UINT SwapChainFlags
)
{
	Log
	(
		#ifdef _WIN64
		"%s "
		"%llX "
		"%u "
		"%u "
		"%u "
		"%d "
		"%X",
		#else
		"%s "
		"%X "
		"%u "
		"%u "
		"%u "
		"%d "
		"%X",
		#endif
		FUNC_NAME,
		SwapChain,
		BufferCount,
		Width,
		Height,
		NewFormat,
		SwapChainFlags
	);

	RemoveRenderTarget<api>();



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

	CreateRenderTarget<api>();



	UpdateGlobalWindowSize();
	UpdateGlobalClientSize();
	UpdateGlobalRenderSize
	(
		Width,
		Height
	);



	SetLastError(error);

	return result;
}

namespaceEnd();

#pragma endregion



#pragma region D3D10

namespaceStart(D3D10);

export typedef decltype(D3D10CreateDeviceAndSwapChain) * D3D10CreateDeviceAndSwapChain_t;

namespaceEnd();



namespaceStart(Base::D3D10);

export ::D3D10::D3D10CreateDeviceAndSwapChain_t D3D10CreateDeviceAndSwapChain = 0;

namespaceEnd();



namespaceStart(Hook::D3D10);

export typedef void(* D3D10CreateDeviceAndSwapChain_func_t)();

export D3D10CreateDeviceAndSwapChain_func_t D3D10CreateDeviceAndSwapChain_func = 0;

export HRESULT D3D10CreateDeviceAndSwapChain
(
	::DXGI::IDXGIAdapter* pAdapter,
	::D3D10::D3D10_DRIVER_TYPE DriverType,
	HMODULE Software,
	UINT Flags,
	UINT SDKVersion,
	::DXGI::DXGI_SWAP_CHAIN_DESC* pSwapChainDesc,
	::DXGI::IDXGISwapChain** ppSwapChain,
	::D3D10::ID3D10Device** ppDevice
)
{
	Log
	(
		#ifdef _WIN64
		"%s "
		"%llX "
		"%X "
		"%llX "
		"%X "
		"%X "
		"%llX "
		"%llX "
		"%llX",
		#else
		"%s "
		"%X "
		"%X "
		"%X "
		"%X "
		"%X "
		"%X "
		"%X "
		"%X",
		#endif
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

	CreateRenderTarget<API::D3D10>();



	[&]()
	{
		auto func = D3D10CreateDeviceAndSwapChain_func;
		if (!func)
		{
			return;
		}

		func();
	}();



	[&]()
	{
		if
		(
			(result != 0) ||
			!ppSwapChain  ||
			!*ppSwapChain
		)
		{
			return;
		}

		auto funcAddrs = *reinterpret_cast<byte8 ***>(*ppSwapChain);
		if (!funcAddrs)
		{
			return;
		}

		Install
		(
			&funcAddrs[8],
			::Base::DXGI::Present,
			::Hook::DXGI::Present<API::D3D10>
		);

		Install
		(
			&funcAddrs[13],
			::Base::DXGI::ResizeBuffers,
			::Hook::DXGI::ResizeBuffers<API::D3D10>
		);
	}();


CreateKeyboard();
CreateMouse();
CreateGamepad();



	SetLastError(error);

	return result;
}

namespaceEnd();

#pragma endregion



#pragma region D3D11

namespaceStart(D3D11);

export typedef decltype(D3D11CreateDeviceAndSwapChain) * D3D11CreateDeviceAndSwapChain_t;

namespaceEnd();



namespaceStart(Base::D3D11);

export ::D3D11::D3D11CreateDeviceAndSwapChain_t D3D11CreateDeviceAndSwapChain = 0;

namespaceEnd();



namespaceStart(Hook::D3D11);

export typedef void(* D3D11CreateDeviceAndSwapChain_func_t)();

export D3D11CreateDeviceAndSwapChain_func_t D3D11CreateDeviceAndSwapChain_func = 0;

export HRESULT D3D11CreateDeviceAndSwapChain
(
	::DXGI::IDXGIAdapter* pAdapter,
	::D3D11::D3D_DRIVER_TYPE DriverType,
	HMODULE Software,
	UINT Flags,
	const ::D3D11::D3D_FEATURE_LEVEL* pFeatureLevels,
	UINT FeatureLevels,
	UINT SDKVersion,
	const ::DXGI::DXGI_SWAP_CHAIN_DESC* pSwapChainDesc,
	::DXGI::IDXGISwapChain** ppSwapChain,
	::D3D11::ID3D11Device** ppDevice,
	::D3D11::D3D_FEATURE_LEVEL* pFeatureLevel,
	::D3D11::ID3D11DeviceContext** ppImmediateContext
)
{
	Log
	(
		#ifdef _WIN64
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
		#else
		"%s "
		"%X "
		"%X "
		"%X "
		"%X "
		"%X "
		"%X "
		"%X "
		"%X "
		"%X "
		"%X "
		"%X "
		"%X",
		#endif
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

	CreateRenderTarget<API::D3D11>();



	[&]()
	{
		auto func = D3D11CreateDeviceAndSwapChain_func;
		if (!func)
		{
			return;
		}

		func();
	}();



	[&]()
	{
		if
		(
			(result != 0) ||
			!ppSwapChain  ||
			!*ppSwapChain
		)
		{
			return;
		}

		auto funcAddrs = *reinterpret_cast<byte8 ***>(*ppSwapChain);
		if (!funcAddrs)
		{
			return;
		}

		Install
		(
			&funcAddrs[8],
			::Base::DXGI::Present,
			::Hook::DXGI::Present<API::D3D11>
		);

		Install
		(
			&funcAddrs[13],
			::Base::DXGI::ResizeBuffers,
			::Hook::DXGI::ResizeBuffers<API::D3D11>
		);
	}();






CreateKeyboard();
CreateMouse();
CreateGamepad();





	SetLastError(error);

	return result;
}

namespaceEnd();

#pragma endregion




#pragma region DI8

namespaceStart(DI8);

export typedef HRESULT(* GetDeviceStateA_t)
(
	IDirectInputDevice8A * pDevice,
	DWORD BufferSize,
	LPVOID Buffer
);

namespaceEnd();



namespaceStart(Base::DI8);

export ::DI8::GetDeviceStateA_t GetDeviceStateA = 0;

namespaceEnd();



namespaceStart(Hook::DI8);

export HRESULT GetDeviceStateA
(
	::DI8::IDirectInputDevice8A * pDevice,
	DWORD BufferSize,
	LPVOID Buffer
)
{
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



#pragma endregion



#pragma region XI

namespaceStart(XI);

export typedef decltype(XInputGetState) * XInputGetState_t;

namespaceEnd();



namespaceStart(Base::XI);

export ::XI::XInputGetState_t XInputGetState = 0;

namespaceEnd();



namespaceStart(Hook::XI);

export DWORD XInputGetState
(
	DWORD dwUserIndex,
	::XI::XINPUT_STATE* pState
)
{
	if (g_show)
	{
		SetMemory
		(
			pState,
			0,
			sizeof(::XI::XINPUT_STATE)
		);
	}

	return 0;
}

namespaceEnd();

#pragma endregion
