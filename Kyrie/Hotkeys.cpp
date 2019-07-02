#include "Hotkeys.h"

void Hotkeys_TogglePause(BYTE * state)
{
	static bool execute = true;
	BYTE keys[] =
	{
		DIK_LCONTROL,
		DIK_D,
	};
	uint8 keysDown = 0;
	for (uint8 i = 0; i < countof(keys); i++)
	{
		if (state[keys[i]] & 0x80)
		{
			keysDown++;
		}
	}
	if (keysDown == countof(keys))
	{
		if (execute)
		{
			pause = !pause;
			PostMessageA(mainWindow, DM_PAUSE, 0, 0);
			execute = false;
		}
	}
	else
	{
		execute = true;
	}
}


//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//// add save check!
//
//void Hotkeys::Exit(BYTE * buffer)
//{
//	static bool execute = true;
//	BYTE keys[] =
//	{
//		DIK_LALT,
//		DIK_F4,
//	};
//	uint8 keysDown = 0;
//	for (uint8 i = 0; i < countof(keys); i++)
//	{
//		if (buffer[keys[i]] & 0x80)
//		{
//			keysDown++;
//		}
//	}
//	if (keysDown == countof(keys))
//	{
//		if (execute)
//		{
//			PostMessageA(mainWindow, WM_QUIT, 0, 0);
//			execute = false;
//		}
//	}
//	else
//	{
//		execute = true;
//	}
//}
//
//
//
//
//
//
//
//
//
//
//
//void Hotkeys::MenuController(BYTE * state)
//{
//	using namespace System::Input;
//	using namespace Game::Actor;
//	BYTE * gamepadAddr = *(BYTE **)(me32.modBaseAddr + 0xF2432C);
//	if (!gamepadAddr)
//	{
//		return;
//	}
//	if (InControl())
//	{
//		return;
//	}
//	DWORD off[MAX_ACTOR] =
//	{
//		0x3C,
//		0x308,
//		0x5D4,
//		0x8A0
//	};
//	DWORD map[][2] =
//	{
//		{ MTF_GAMEPAD_START,            DIK_ESCAPE },
//		{ MTF_GAMEPAD_DPAD_UP,          DIK_UP     },
//		{ MTF_GAMEPAD_DPAD_RIGHT,       DIK_RIGHT  },
//		{ MTF_GAMEPAD_DPAD_DOWN,        DIK_DOWN   },
//		{ MTF_GAMEPAD_DPAD_LEFT,        DIK_LEFT   },
//		{ MTF_GAMEPAD_LEFT_SHOULDER,    DIK_N      },
//		{ MTF_GAMEPAD_RIGHT_SHOULDER,   DIK_SPACE  },
//		{ MTF_GAMEPAD_Y,                DIK_Y      },
//		{ MTF_GAMEPAD_B,                DIK_B      },
//		{ MTF_GAMEPAD_A,                DIK_A      },
//		{ MTF_GAMEPAD_X,                DIK_X      },
//		{ MTF_GAMEPAD_LEFT_STICK_UP,    DIK_UP     },
//		{ MTF_GAMEPAD_LEFT_STICK_RIGHT, DIK_RIGHT  },
//		{ MTF_GAMEPAD_LEFT_STICK_DOWN,  DIK_DOWN   },
//		{ MTF_GAMEPAD_LEFT_STICK_LEFT,  DIK_LEFT   }
//	};
//	for (uint8 device = ACTOR_TWO; device < MAX_ACTOR; device++)
//	{
//		DWORD & buttons = *(DWORD *)(gamepadAddr + off[device] + 0x15C);
//		for (uint8 index = 0; index < countof(map); index++)
//		{
//			uint32 button = map[index][0];
//			uint32 key    = map[index][1];
//			if (buttons & button)
//			{
//				state[key] = 0x80;
//			}
//		}
//	}
//}
//
//void Hotkeys::StartCameraController(BYTE * state)
//{
//	using namespace System::Input;
//	using namespace Game::Actor;
//	BYTE * gamepadAddr = *(BYTE **)(me32.modBaseAddr + 0xF2432C);
//	if (!gamepadAddr)
//	{
//		return;
//	}
//	if (!InControl())
//	{
//		return;
//	}
//	DWORD off[MAX_ACTOR] =
//	{
//		0x3C,
//		0x308,
//		0x5D4,
//		0x8A0
//	};
//	DWORD map[][2] =
//	{
//		{ MTF_GAMEPAD_START,             DIK_ESCAPE },
//		{ MTF_GAMEPAD_RIGHT_STICK_UP,    DIK_UP     },
//		{ MTF_GAMEPAD_RIGHT_STICK_RIGHT, DIK_RIGHT  },
//		{ MTF_GAMEPAD_RIGHT_STICK_DOWN,  DIK_DOWN   },
//		{ MTF_GAMEPAD_RIGHT_STICK_LEFT,  DIK_LEFT   }
//	};
//	for (uint8 device = ACTOR_TWO; device < MAX_ACTOR; device++)
//	{
//		DWORD & buttons = *(DWORD *)(gamepadAddr + off[device] + 0x15C);
//		for (uint8 index = 0; index < countof(map); index++)
//		{
//			uint32 button = map[index][0];
//			uint32 key    = map[index][1];
//			if (buttons & button)
//			{
//				state[key] = 0x80;
//			}
//		}
//	}
//}
