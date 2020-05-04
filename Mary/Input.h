#pragma once
#include "../Core/Core.h"

#include "Vars.h"






//extern bool Input_enableRangeExtension;
//extern bool Input_enableMultiplayerFixes;






// @Todo: Change to controller and add actor input one as well.
//inline byte16 Input_GetButtonState(uint8 actor)
//{
//	auto & gamepad = ((CAPCOM_GAMEPAD *)(appBaseAddr + 0xD54A10 + 0x550))[actor];
//	return gamepad.buttons[0];
//}

//inline byte16 Input_GetBinding(uint8 index)
//{
//	auto bindings = (byte16 *)(appBaseAddr + 0xD6CE88);
//	return bindings[index];
//}





inline ENGINE_GAMEPAD & GetGamepad(uint8 index)
{
	return (reinterpret_cast<ENGINE_GAMEPAD *>(appBaseAddr + 0xD54A10 + 0x550))[index];
}










inline byte16 GetBinding(uint8 index)
{
	return (reinterpret_cast<byte16 *>(appBaseAddr + 0xD6CE80 + 0xA))[index];
}







//void Input_Init();
//void Input_ToggleRangeExtension(bool enable);
//void Input_ToggleMultiplayerFixes(bool enable);




