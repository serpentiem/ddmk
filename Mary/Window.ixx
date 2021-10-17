export module Window;

import Core;

#include "../Core/Macros.h"

import Config;
import Global;
import Vars;



export void ToggleForceWindowFocus(bool enable)
{
	LogFunction(enable);

	static bool run = false;



	{
		auto addr = (appBaseAddr + 0x487F6);
		constexpr uint64 size = 6;
		/*
		dmc3.exe+487F6 - 0F85 8D000000     - jne dmc3.exe+48889
		dmc3.exe+487FC - 48 8B 0D CD5B5900 - mov rcx,[dmc3.exe+5DE3D0]
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			Write<byte16>(addr, 0xE990);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Force gamepad focus.
	{
		auto addr = (appBaseAddr + 0x41C0A);
		auto dest = (appBaseAddr + 0x41C10);
		constexpr uint64 size = 6;
		/*
		dmc3.exe+41C0A - 0F84 06040000 - je dmc3.exe+42016
		dmc3.exe+41C10 - 8B 4B 04      - mov ecx,[rbx+04]
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			WriteAddress(addr, dest, size);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}



	run = true;
}


// @Remove


// // @Todo: Rename to ToggleForceWindowFocus.
// export namespace Window
// {


// 	// @Update
// 	void ToggleForceFocus(bool enable)
// 	{
// 		LogFunction(enable);

// 		Write<byte16>((appBaseAddr + 0x487F6), (enable) ? 0xE990 : 0x850F);

// 		// Enable Background Gamepad Input
// 		WriteAddress((appBaseAddr + 0x41C0A), (enable) ? (appBaseAddr + 0x41C10) : (appBaseAddr + 0x42016), 6);
// 	}
// }





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
