export module Input;

import Core;

#include "../Core/Macros.h"

import Config;
import Global;
import Vars;



export namespaceStart(TILT_DIRECTION);
enum
{
	NEUTRAL,
	UP,
	RIGHT,
	DOWN,
	LEFT,
	MAX,
};
namespaceEnd();



export void ToggleCursor()
{
	if
	(
		g_showMain ||
		g_showShop
	)
	{
		Windows_ToggleCursor(true);
	}
	else
	{
		Windows_ToggleCursor(!activeConfig.hideMouseCursor);
	}
}



export inline ENGINE_GAMEPAD & GetGamepad(uint8 index)
{
	return (reinterpret_cast<ENGINE_GAMEPAD *>(appBaseAddr + 0xD54A10 + 0x550))[index];
}



export inline byte16 GetBinding(uint8 index)
{
	return (reinterpret_cast<byte16 *>(appBaseAddr + 0xD6CE80 + 0xA))[index];
}



export inline uint8 GetRelativeTiltDirection(PlayerActorData & actorData)
{
	auto & gamepad = GetGamepad(0);
	uint16 relativeTilt = 0;

	if (gamepad.leftStickRadius < LEFT_STICK_DEADZONE)
	{
		return TILT_DIRECTION::NEUTRAL;
	}

	relativeTilt = (actorData.actorCameraDirection - gamepad.leftStickPosition);

	{
		uint16 value = (relativeTilt - 0x6000);
		if (value <= 0x4000)
		{
			return TILT_DIRECTION::UP;
		}
	}
	{
		uint16 value = (relativeTilt + 0x6000);
		if (value <= 0x4000)
		{
			return TILT_DIRECTION::RIGHT;
		}
	}
	{
		uint16 value = (relativeTilt + 0x2000);
		if (value <= 0x4000)
		{
			return TILT_DIRECTION::DOWN;
		}
	}
	{
		uint16 value = (relativeTilt - 0x2000);
		if (value <= 0x4000)
		{
			return TILT_DIRECTION::LEFT;
		}
	}

	return TILT_DIRECTION::NEUTRAL;
}
