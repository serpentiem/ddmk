#pragma once
#include "../Core/Core.h"

#define DIRECTINPUT_VERSION 0x800
#include <dinput.h>

#include "Pause.h"

#include "System/Message.h"

void Hotkeys_TogglePause(BYTE * state);
