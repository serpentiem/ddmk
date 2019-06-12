//#include "Weapon.h"
//
//BYTE * Melee_Timeout  = 0;
//BYTE * Ranged_Timeout = 0;
//
//
//
//
//
//void Game_Weapon_Init()
//{
//	LogFunction();
//
//
//
//
//	{
//		BYTE sect0[] =
//		{
//			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rcx
//			0x8B, 0x09,                                                 //mov ecx,[rcx]
//		};
//		FUNC func = CreateFunction(0, (appBaseAddr + 0x1EA97A), false, true, sizeof(sect0));
//		memcpy(func.sect0, sect0, sizeof(sect0));
//		*(float32 **)(func.sect0 + 2) = &Config.Game.Weapon.Timeout.melee;
//		Melee_Timeout = func.addr;
//	}
//	{
//		BYTE sect0[] =
//		{
//			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rcx
//			0x8B, 0x09,                                                 //mov ecx,[rcx]
//		};
//		FUNC func = CreateFunction(0, (appBaseAddr + 0x1EAA67), false, true, sizeof(sect0));
//		memcpy(func.sect0, sect0, sizeof(sect0));
//		*(float32 **)(func.sect0 + 2) = &Config.Game.Weapon.Timeout.ranged;
//		Ranged_Timeout = func.addr;
//	}
//}
//
//void Game_Weapon_ToggleTimeout(bool enable)
//{
//	Log("%s %u", FUNC_NAME, enable);
//	if (enable)
//	{
//		WriteJump((appBaseAddr + 0x1EA974), Melee_Timeout, 1);
//		WriteJump((appBaseAddr + 0x1EAA61), Ranged_Timeout, 1);
//	}
//	else
//	{
//		{
//			BYTE buffer[] =
//			{
//				0x8B, 0x88, 0xF4, 0x02, 0x00, 0x00, //mov ecx,[rax+000002F4]
//			};
//			vp_memcpy((appBaseAddr + 0x1EA974), buffer, sizeof(buffer));
//		}
//		{
//			BYTE buffer[] =
//			{
//				0x8B, 0x88, 0xF4, 0x02, 0x00, 0x00, //mov ecx,[rax+000002F4]
//			};
//			vp_memcpy((appBaseAddr + 0x1EAA61), buffer, sizeof(buffer));
//		}
//	}
//}
