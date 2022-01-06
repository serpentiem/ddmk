


// @Research: To avoid logging create error level or func enum to indicate point of failure.
// @Research: Add device name for Acquire log.



export module Core_Input;

import Core;

#include "../Core/Macros.h"

import Windows;
import DI8;

using namespace Windows;
using namespace DI8;

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
