#pragma once
#include "../../Core/Core.h"

#include "../Vars.h"

extern bool System_Input_enableRangeExtension;
extern bool System_Input_enableMultiplayerFixes;

inline byte16 System_Input_GetButtonState(uint8 actor)
{
	auto & gamepad = ((CAPCOM_GAMEPAD *)(appBaseAddr + 0xD54A10 + 0x550))[actor];
	return gamepad.buttons[0];
}

inline byte16 System_Input_GetBinding(uint8 index)
{
	auto bindings = (byte16 *)(appBaseAddr + 0xD6CE88);
	return bindings[index];
}

void System_Input_Init();
void System_Input_ToggleRangeExtension(bool enable);
void System_Input_ToggleMultiplayerFixes(bool enable);
