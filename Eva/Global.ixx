export module Global;

import Core;

#include "../Core/Macros.h"

import DXGI;
import D3D11;
import DI8;

import Vars;

using namespace DXGI;
using namespace D3D11;
using namespace DI8;

#define debug false

#include "Macros.h"



export namespace DXGI
{
	IDXGISwapChain * swapChain = 0;
}

export namespace D3D11
{
	ID3D11Device           * device           = 0;
	ID3D11DeviceContext    * deviceContext    = 0;
	ID3D11RenderTargetView * renderTargetView = 0;
}

export namespace DI8
{
	IDirectInput8W       * deviceInterface = 0;
	IDirectInputDevice8W * mouse           = 0;
	DIMOUSESTATE2          mouseState      = {};
}

export vec2 g_windowSize = {};
export vec2 g_clientSize = {};
export vec2 g_renderSize = {};


export bool g_show               = false;
export bool g_lastShow           = false;
// export bool g_showItemWindow     = false;
// export bool g_lastShowItemWindow = false;

// export bool g_setRoom = false;


//export bool g_skipBlackout = false;









export bool InGame()
{
	IntroduceSessionData(return false);

	return (sessionData.event & EVENT::IN_GAME);
}







export void ToggleSkipText(bool enable)
{
	LogFunction(enable);



	static bool run = false;



	// Fast Forward
	{
		auto addr = (appBaseAddr + 0x265D0B);
		auto dest = (appBaseAddr + 0x265D0D);
		constexpr uint32 size = 2;
		/*
		dmc1.exe+265D0B - 74 21             - je dmc1.exe+265D2E
		dmc1.exe+265D0D - 80 B9 647C0000 01 - cmp byte ptr [rcx+00007C64],01
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

	{
		auto addr = (appBaseAddr + 0x265D14);
		auto dest = (appBaseAddr + 0x265D16);
		constexpr uint32 size = 2;
		/*
		dmc1.exe+265D14 - 75 34          - jne dmc1.exe+265D4A
		dmc1.exe+265D16 - 8B 81 5C7C0000 - mov eax,[rcx+00007C5C]
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



	// Next
	{
		auto addr = (appBaseAddr + 0x2669D7);
		constexpr uint32 size = 2;
		/*
		dmc1.exe+2669D7 - 75 08          - jne dmc1.exe+2669E1
		dmc1.exe+2669D9 - 85 90 2C1D0000 - test [rax+00001D2C],edx
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			Write<byte8>(addr, 0xEB);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}



	run = true;
}










export void ToggleAutoExamine(bool enable)
{
	LogFunction(enable);

	static bool run = false;

	{
		auto addr = (appBaseAddr + 0x3BD0EE);
		constexpr uint32 size = 2;
		/*
		dmc1.exe+3BD0EE - 75 14       - jne dmc1.exe+3BD104
		dmc1.exe+3BD0F0 - 41 F6 C3 40 - test r11l,40
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			Write<byte8>(addr, 0xEB);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	run = true;
}







export void AddUniqueItem(ItemData & newItem)
{
	LogFunction();

	IntroduceSessionData(return);



	for_all(itemIndex, sessionData.itemCount)
	{
		auto & item = sessionData.items[itemIndex];

		if
		(
			(item.category == newItem.category) &&
			(item.id       == newItem.id      ) &&
			(item.count >= 1)
		)
		{
			Log("Match");

			item.count = newItem.count;

			return;
		}
	}



	Log("No Match");

	auto & itemIndex = sessionData.itemCount;

	auto & item = sessionData.items[itemIndex];

	item.category = newItem.category;
	item.id       = newItem.id;
	item.count    = newItem.count;

	itemIndex++;
}




export void ToggleSkipIntro(bool enable)
{
	LogFunction(enable);

	static bool run = false;



	// Play Video
	{
		auto addr = (appBaseAddr + 0x3F8D9A);
		constexpr uint32 size = 5;
		/*
		dmc1.exe+3F8D9A - E8 C1E0E7FF - call dmc1.exe+276E60
		dmc1.exe+3F8D9F - 8D 5E 01    - lea ebx,[rsi+01]
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			SetMemory(addr, 0x90, size, MemoryFlags_VirtualProtectDestination);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}



	// Disable Main Menu Video Timer
	{
		auto addr = (appBaseAddr + 0x3F8D18);
		constexpr uint32 size = 2;
		/*
		dmc1.exe+3F8D18 - FF C8    - dec eax
		dmc1.exe+3F8D1A - 89 43 34 - mov [rbx+34],eax
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			SetMemory(addr, 0x90, size, MemoryFlags_VirtualProtectDestination);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	{
		auto addr = (appBaseAddr + 0x3F8B7D);
		constexpr uint32 size = 3;
		/*
		dmc1.exe+3F8B7D - FF 4B 34    - dec [rbx+34]
		dmc1.exe+3F8B80 - C6 43 01 02 - mov byte ptr [rbx+01],02
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			SetMemory(addr, 0x90, size, MemoryFlags_VirtualProtectDestination);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}



	run = true;
}











