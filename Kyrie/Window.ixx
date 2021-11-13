export module Window;

import Core;

#include "../Core/Macros.h"


import Windows;

using namespace Windows;



import Config;
import Global;
import Vars;






export void ToggleForceWindowFocus(bool enable)
{
	LogFunction(enable);

	static bool run = false;



	{
		auto addr = (appBaseAddr + 0x6E322B);
		constexpr size_t size = 7;
		/*
		dmc4.exe+6E322B - C6 81 51250000 00 - mov byte ptr [ecx+00002551],00
		dmc4.exe+6E3232 - 8B 0D 2C433201    - mov ecx,[dmc4.exe+F2432C]
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			Write<byte8>((addr + 6), 1);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}



	run = true;
}













export void ToggleBorderless(bool enable)
{
	LogFunction(enable);





	static LONG defaultStyle = 0;

	constexpr LONG borderlessStyle = (WS_OVERLAPPED | WS_MINIMIZEBOX | WS_CLIPSIBLINGS | WS_VISIBLE);

	static bool run = false;

	if (!run)
	{
		defaultStyle = GetWindowLongA
		(
			appWindow,
			GWL_STYLE
		);
	}


	LONG style = (enable) ? borderlessStyle : defaultStyle;
















	SetWindowLongA
	(
		appWindow,
		GWL_STYLE,
		style
	);




	RECT rect = {};

	rect.right  = static_cast<LONG>(g_renderSize.x);
	rect.bottom = static_cast<LONG>(g_renderSize.y);

	AdjustWindowRect
	(
		&rect,
		style,
		0
	);








	MoveWindow
	(
		appWindow,
		activeConfig.windowPosX,
		activeConfig.windowPosY,
		(rect.right - rect.left),
		(rect.bottom - rect.top),
		0
	);






	run = true;
}






void GunkOver()
{
	LogFunction();

	g_update3D = true;
}



namespaceStart(Window);

export void Toggle(bool enable)
{
	LogFunction(enable);

	static bool run = false;



	// GunkOver
	{
		auto addr     = (appBaseAddr + 0x69C50C);
		auto jumpAddr = (appBaseAddr + 0x69C512);
		constexpr size_t size = 6;
		/*
		dmc4.exe+69C50C - 89 96 B8000000 - mov [esi+000000B8],edx
		dmc4.exe+69C512 - 5F             - pop edi
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(GunkOver, jumpAddr, true, true, size);
			CopyMemory(func.sect0, addr, size, MemoryFlags_VirtualProtectSource);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}



	run = true;
}

namespaceEnd();




























