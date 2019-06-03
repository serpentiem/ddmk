#pragma once
#include "../Core/Core.h"
#define DIRECTINPUT_VERSION 0x800
#include <dinput.h>
#include "Pause.h"
#include "System/Message.h"

namespace Hotkeys
{
	void TogglePause(BYTE * buffer);
}
