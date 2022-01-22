


// @Research: To avoid logging create error level or func enum to indicate point of failure.
// @Research: Add device name for Acquire log.



export module Core_Input;

import Core;

#include "../Core/Macros.h"

import Windows;
import DI8;
import XI;

using namespace Windows;
using namespace DI8;
using namespace XI;

#define debug false











#define LogFail(name, value) Log(name " failed. %X", value)





export struct InputDevice
{
	IDirectInput8A * deviceInterface;
	IDirectInputDevice8A * device;
	bool init;



	bool CreateInterface()
	{
		HRESULT result = 0;



		result = DirectInput8Create
		(
			appBaseAddr,
			0x800,
			IID_IDirectInput8A,
			reinterpret_cast<void **>(&deviceInterface),
			0
		);

		if (result != DI_OK)
		{
			LogFail("DirectInput8Create", result);

			return false;
		}



		return true;
	};

	bool Create
	(
		const GUID & guid,
		const DIDATAFORMAT * dataFormat,
		DWORD setCooperativeLevelFlags
	)
	{
		HRESULT result = 0;



		result = deviceInterface->CreateDevice
		(
			guid,
			&device,
			0
		);

		if (result != DI_OK)
		{
			LogFail("deviceInterface->CreateDevice", result);

			return false;
		}



		result = device->SetCooperativeLevel
		(
			appWindow,
			setCooperativeLevelFlags
		);

		if (result != DI_OK)
		{
			LogFail("device->SetCooperativeLevel", result);

			return false;
		}



		result = device->SetDataFormat(dataFormat);

		if (result != DI_OK)
		{
			LogFail("device->SetDataFormat", result);

			return false;
		}



		result = device->Acquire();

		if (result != DI_OK)
		{
			LogFail("device->Acquire", result);
		}



		init = true;



		return true;
	};

	void Update
	(
		DWORD size,
		void * addr
	)
	{
		if (!init)
		{
			return;
		}



		HRESULT result = 0;

		result = device->GetDeviceState
		(
			size,
			addr
		);



		if
		(
			(GetForegroundWindow() == appWindow) &&
			(
				(result == DIERR_INPUTLOST  ) ||
				(result == DIERR_NOTACQUIRED)
			)
		)
		{
			result = device->Acquire();

			Log("device->Acquire");
		}
	};
};



export struct Keyboard : InputDevice
{
	DIKEYBOARDSTATE state;

	bool Create()
	{
		if (!CreateInterface())
		{
			Log("CreateInterface failed.");

			return false;
		}

		if
		(
			!InputDevice::Create
			(
				GUID_SysKeyboard,
				&c_dfDIKeyboard,
				DISCL_NONEXCLUSIVE |
				DISCL_FOREGROUND
			)
		)
		{
			Log("InputDevice::Create failed.");

			return false;
		}

		return true;
	};

	void Update()
	{
		InputDevice::Update
		(
			sizeof(state),
			&state
		);
	};
};



export struct Mouse : InputDevice
{
	DIMOUSESTATE2 state;

	bool Create()
	{
		if (!CreateInterface())
		{
			Log("CreateInterface failed.");

			return false;
		}

		if
		(
			!InputDevice::Create
			(
				GUID_SysMouse,
				&c_dfDIMouse2,
				DISCL_NONEXCLUSIVE |
				DISCL_FOREGROUND
			)
		)
		{
			Log("InputDevice::Create failed.");

			return false;
		}

		return true;
	};

	void Update()
	{
		InputDevice::Update
		(
			sizeof(state),
			&state
		);
	};
};



export struct Gamepad : InputDevice
{
	LPDIENUMDEVICESCALLBACKA enumFunc;
	DIDEVICEINSTANCEA deviceInstance;
	bool match;
	DIJOYSTATE state;



	bool Create()
	{
		if (!CreateInterface())
		{
			Log("CreateInterface failed.");

			return false;
		}



		HRESULT result = 0;

		result = deviceInterface->EnumDevices
		(
			0,
			enumFunc,
			0,
			DIEDFL_ALLDEVICES
		);

		if (result != DI_OK)
		{
			Log("EnumDevices failed.");

			return false;
		}

		if (!match)
		{
			Log("Gamepad: No Match");

			return false;
		}

		// LogGUID("gamepad guid ", deviceInstance.guidInstance);



		if
		(
			!InputDevice::Create
			(
				deviceInstance.guidInstance,
				&c_dfDIJoystick,
				DISCL_NONEXCLUSIVE |
				DISCL_BACKGROUND
			)
		)
		{
			Log("InputDevice::Create failed.");

			return false;
		}

		return true;
	};

	void Update()
	{
		InputDevice::Update
		(
			sizeof(state),
			&state
		);
	};
};















namespaceStart(XI);


export namespaceStart(GAMEPAD);
enum
{
	UP             = 0x1,
	DOWN           = 0x2,
	LEFT           = 0x4,
	RIGHT          = 0x8,
	START          = 0x10,
	BACK           = 0x20,
	LEFT_THUMB     = 0x40,
	RIGHT_THUMB    = 0x80,
	LEFT_SHOULDER  = 0x100,
	RIGHT_SHOULDER = 0x200,
	A              = 0x1000,
	B              = 0x2000,
	X              = 0x4000,
	Y              = 0x8000,
};
namespaceEnd();









export typedef DWORD(* new_XInputGetState_t)
(
	DWORD,
	XINPUT_STATE *
);

export new_XInputGetState_t new_XInputGetState = 0;



export void new_Init(const char * libName)
{
	LogFunction();



	byte32 error = 0;



	SetLastError(0);

	auto lib = LoadLibraryA(libName);
	if (!lib)
	{
		error = GetLastError();

		Log("LoadLibraryA failed. %s %X", libName, error);

		return;
	}



	// XInputGetState
	{
		const char * funcName = "XInputGetState";

		SetLastError(0);

		auto funcAddr = GetProcAddress(lib, funcName);
		if (!funcAddr)
		{
			error = GetLastError();

			Log("GetProcAddress failed. %s %X", funcName, error);

			return;
		}

		new_XInputGetState = reinterpret_cast<new_XInputGetState_t>(funcAddr);
	}
}










namespaceEnd();


































