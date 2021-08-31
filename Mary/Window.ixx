export module Window;

import Core;

#include "../Core/Macros.h"

import Core_ImGui;

import Config;
import Global;
import Vars;


// @Todo: Rename to ToggleForceWindowFocus.
export namespace Window
{


	// @Update
	void ToggleForceFocus(bool enable)
	{
		LogFunction(enable);

		Write<byte16>((appBaseAddr + 0x487F6), (enable) ? 0xE990 : 0x850F);

		// Enable Background Gamepad Input
		WriteAddress((appBaseAddr + 0x41C0A), (enable) ? (appBaseAddr + 0x41C10) : (appBaseAddr + 0x42016), 6);
	}
}





// export void UpdateWindowSize
// (
// 	uint32 width,
// 	uint32 height
// )
// {
// 	Log
// 	(
// 		"%s "
// 		"%u "
// 		"%u",
// 		FUNC_NAME,
// 		width,
// 		height
// 	);

// 	windowWidth = width;
// 	windowHeight = height;
// 	windowSize =
// 	{
// 		static_cast<float>(width),
// 		static_cast<float>(height)
// 	};

// 	ImGui::DI8::UpdateMouseMultiplier
// 	(
// 		windowSize,
// 		renderSize
// 	);
// }
