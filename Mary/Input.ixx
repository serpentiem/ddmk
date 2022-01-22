export module Input;

import Core;

#include "../Core/Macros.h"

import Config;
import Global;
import Vars;

// export enum TILT_DIRECTION
// {
// 	TILT_DIRECTION::NEUTRAL,
// 	TILT_DIRECTION::UP,
// 	TILT_DIRECTION::RIGHT,
// 	TILT_DIRECTION::DOWN,
// 	TILT_DIRECTION::LEFT,
// 	MAX_TILT_DIRECTION,
// };

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

// export void ToggleDisableGetInput(bool enable)
// {
// 	LogFunction(enable);

// 	static bool run = false;



// 	{
// 		auto addr = (appBaseAddr + 0x32CC20);
// 		constexpr uint32 size = 9;
// 		/*
// 		dmc3.exe+32CC20 - 42 0FB7 84 C0 68050000 - movzx eax,word ptr [rax+r8*8+00000568]
// 		dmc3.exe+32CC29 - C3                     - ret
// 		*/

// 		constexpr byte8 sect0[] =
// 		{
// 			0x31, 0xC0, // xor eax,eax
// 		};

// 		if (!run)
// 		{
// 			backupHelper.Save(addr, size);
// 		}

// 		if (enable)
// 		{
// 			SetMemory(addr, 0x90, size, MemoryFlags_VirtualProtectDestination);
// 			CopyMemory(addr, sect0, sizeof(sect0), MemoryFlags_VirtualProtectDestination);
// 		}
// 		else
// 		{
// 			backupHelper.Restore(addr);
// 		}
// 	}

// 	{
// 		auto addr = (appBaseAddr + 0x32CC40);
// 		constexpr uint32 size = 9;
// 		/*
// 		dmc3.exe+32CC40 - 42 0FB7 84 C0 5C050000 - movzx eax,word ptr [rax+r8*8+0000055C]
// 		dmc3.exe+32CC49 - C3                     - ret
// 		*/

// 		constexpr byte8 sect0[] =
// 		{
// 			0x31, 0xC0, // xor eax,eax
// 		};

// 		if (!run)
// 		{
// 			backupHelper.Save(addr, size);
// 		}

// 		if (enable)
// 		{
// 			SetMemory(addr, 0x90, size, MemoryFlags_VirtualProtectDestination);
// 			CopyMemory(addr, sect0, sizeof(sect0), MemoryFlags_VirtualProtectDestination);
// 		}
// 		else
// 		{
// 			backupHelper.Restore(addr);
// 		}
// 	}

// 	{
// 		auto addr = (appBaseAddr + 0x32CC60);
// 		constexpr uint32 size = 9;
// 		/*
// 		dmc3.exe+32CC60 - 42 0FB7 84 C0 6A050000 - movzx eax,word ptr [rax+r8*8+0000056A]
// 		dmc3.exe+32CC69 - C3                     - ret
// 		*/

// 		constexpr byte8 sect0[] =
// 		{
// 			0x31, 0xC0, // xor eax,eax
// 		};

// 		if (!run)
// 		{
// 			backupHelper.Save(addr, size);
// 		}

// 		if (enable)
// 		{
// 			SetMemory(addr, 0x90, size, MemoryFlags_VirtualProtectDestination);
// 			CopyMemory(addr, sect0, sizeof(sect0), MemoryFlags_VirtualProtectDestination);
// 		}
// 		else
// 		{
// 			backupHelper.Restore(addr);
// 		}
// 	}

// 	{
// 		auto addr = (appBaseAddr + 0x32CC77);
// 		constexpr uint32 size = 8;
// 		/*
// 		dmc3.exe+32CC77 - 0FB7 84 0A 50050000 - movzx eax,word ptr [rdx+rcx+00000550]
// 		dmc3.exe+32CC7F - C3                  - ret
// 		*/

// 		constexpr byte8 sect0[] =
// 		{
// 			0x31, 0xC0, // xor eax,eax
// 		};

// 		if (!run)
// 		{
// 			backupHelper.Save(addr, size);
// 		}

// 		if (enable)
// 		{
// 			SetMemory(addr, 0x90, size, MemoryFlags_VirtualProtectDestination);
// 			CopyMemory(addr, sect0, sizeof(sect0), MemoryFlags_VirtualProtectDestination);
// 		}
// 		else
// 		{
// 			backupHelper.Restore(addr);
// 		}
// 	}

// 	{
// 		auto addr = (appBaseAddr + 0x32CC87);
// 		constexpr uint32 size = 8;
// 		/*
// 		dmc3.exe+32CC87 - 0FB7 84 0A 52050000 - movzx eax,word ptr [rdx+rcx+00000552]
// 		dmc3.exe+32CC8F - C3                  - ret
// 		*/

// 		constexpr byte8 sect0[] =
// 		{
// 			0x31, 0xC0, // xor eax,eax
// 		};

// 		if (!run)
// 		{
// 			backupHelper.Save(addr, size);
// 		}

// 		if (enable)
// 		{
// 			SetMemory(addr, 0x90, size, MemoryFlags_VirtualProtectDestination);
// 			CopyMemory(addr, sect0, sizeof(sect0), MemoryFlags_VirtualProtectDestination);
// 		}
// 		else
// 		{
// 			backupHelper.Restore(addr);
// 		}
// 	}

// 	{
// 		auto addr = (appBaseAddr + 0x32CC9B);
// 		constexpr uint32 size = 4;
// 		/*
// 		dmc3.exe+32CC9B - 0FB7 04 08 - movzx eax,word ptr [rax+rcx]
// 		dmc3.exe+32CC9F - C3         - ret
// 		*/

// 		constexpr byte8 sect0[] =
// 		{
// 			0x31, 0xC0, // xor eax,eax
// 		};

// 		if (!run)
// 		{
// 			backupHelper.Save(addr, size);
// 		}

// 		if (enable)
// 		{
// 			SetMemory(addr, 0x90, size, MemoryFlags_VirtualProtectDestination);
// 			CopyMemory(addr, sect0, sizeof(sect0), MemoryFlags_VirtualProtectDestination);
// 		}
// 		else
// 		{
// 			backupHelper.Restore(addr);
// 		}
// 	}

// 	{
// 		auto addr = (appBaseAddr + 0x32CCA7);
// 		constexpr uint32 size = 8;
// 		/*
// 		dmc3.exe+32CCA7 - 0FB7 84 0A 58050000 - movzx eax,word ptr [rdx+rcx+00000558]
// 		dmc3.exe+32CCAF - C3                  - ret
// 		*/

// 		constexpr byte8 sect0[] =
// 		{
// 			0x31, 0xC0, // xor eax,eax
// 		};

// 		if (!run)
// 		{
// 			backupHelper.Save(addr, size);
// 		}

// 		if (enable)
// 		{
// 			SetMemory(addr, 0x90, size, MemoryFlags_VirtualProtectDestination);
// 			CopyMemory(addr, sect0, sizeof(sect0), MemoryFlags_VirtualProtectDestination);
// 		}
// 		else
// 		{
// 			backupHelper.Restore(addr);
// 		}
// 	}

// 	{
// 		auto addr = (appBaseAddr + 0x32CCC7);
// 		constexpr uint32 size = 2;
// 		/*
// 		dmc3.exe+32CCC7 - 0B C1 - or eax,ecx
// 		dmc3.exe+32CCC9 - C3    - ret
// 		*/

// 		constexpr byte8 sect0[] =
// 		{
// 			0x31, 0xC0, // xor eax,eax
// 		};

// 		if (!run)
// 		{
// 			backupHelper.Save(addr, size);
// 		}

// 		if (enable)
// 		{
// 			SetMemory(addr, 0x90, size, MemoryFlags_VirtualProtectDestination);
// 			CopyMemory(addr, sect0, sizeof(sect0), MemoryFlags_VirtualProtectDestination);
// 		}
// 		else
// 		{
// 			backupHelper.Restore(addr);
// 		}
// 	}

// 	{
// 		auto addr = (appBaseAddr + 0x32CCEB);
// 		constexpr uint32 size = 2;
// 		/*
// 		dmc3.exe+32CCEB - 0B C1 - or eax,ecx
// 		dmc3.exe+32CCED - C3    - ret
// 		*/

// 		constexpr byte8 sect0[] =
// 		{
// 			0x31, 0xC0, // xor eax,eax
// 		};

// 		if (!run)
// 		{
// 			backupHelper.Save(addr, size);
// 		}

// 		if (enable)
// 		{
// 			SetMemory(addr, 0x90, size, MemoryFlags_VirtualProtectDestination);
// 			CopyMemory(addr, sect0, sizeof(sect0), MemoryFlags_VirtualProtectDestination);
// 		}
// 		else
// 		{
// 			backupHelper.Restore(addr);
// 		}
// 	}

// 	{
// 		auto addr = (appBaseAddr + 0x32CD22);
// 		constexpr uint32 size = 2;
// 		/*
// 		dmc3.exe+32CD22 - 0B C1 - or eax,ecx
// 		dmc3.exe+32CD24 - C3    - ret
// 		*/

// 		constexpr byte8 sect0[] =
// 		{
// 			0x31, 0xC0, // xor eax,eax
// 		};

// 		if (!run)
// 		{
// 			backupHelper.Save(addr, size);
// 		}

// 		if (enable)
// 		{
// 			SetMemory(addr, 0x90, size, MemoryFlags_VirtualProtectDestination);
// 			CopyMemory(addr, sect0, sizeof(sect0), MemoryFlags_VirtualProtectDestination);
// 		}
// 		else
// 		{
// 			backupHelper.Restore(addr);
// 		}
// 	}



// 	run = true;
// }
