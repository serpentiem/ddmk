#include "Dante.h"

byte8 * RainStorm      = 0;
byte8 * Melee_Timeout  = 0;
byte8 * Ranged_Timeout = 0;

bool Game_Dante_Rebellion_quickDrive = false;

void Game_Dante_Init()
{
	LogFunction();
	{
		byte8 sect0[] =
		{
			0x66, 0x8B, 0x05, 0x00, 0x00, 0x00, 0x00, //mov ax,[dmc3.exe+D6CE88+E]
			0x66, 0x85, 0x83, 0xE0, 0x74, 0x00, 0x00, //test [rbx+000074E0],ax
			0x0F, 0x85, 0x00, 0x00, 0x00, 0x00,       //jne dmc3.exe+20CC20
		};
		FUNC func = CreateFunction(0, (appBaseAddr + 0x20CC14), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteAddress(func.sect0, (appBaseAddr + 0xD6CE88 + 0xE), 7);
		WriteAddress((func.sect0 + 0xE), (appBaseAddr + 0x20CC20), 6);
		RainStorm = func.addr;
	}
	//{
	//	byte8 sect0[] =
	//	{
	//		0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rcx
	//		0x8B, 0x09,                                                 //mov ecx,[rcx]
	//	};
	//	FUNC func = CreateFunction(0, (appBaseAddr + 0x1EA97A), false, true, sizeof(sect0));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	*(float32 **)(func.sect0 + 2) = &Config.Game.Dante.WeaponSwitchTimeout.melee;
	//	Melee_Timeout = func.addr;
	//}
	//{
	//	byte8 sect0[] =
	//	{
	//		0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rcx
	//		0x8B, 0x09,                                                 //mov ecx,[rcx]
	//	};
	//	FUNC func = CreateFunction(0, (appBaseAddr + 0x1EAA67), false, true, sizeof(sect0));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	*(float32 **)(func.sect0 + 2) = &Config.Game.Dante.WeaponSwitchTimeout.ranged;
	//	Ranged_Timeout = func.addr;
	//}
}




// @Todo: Move to Init.

//void Game_Dante_WeaponSwitchTimeout_Melee_Toggle(float32 var)
//{
//	Log("%s %.0f", FUNC_NAME, var);
//	if (var != 12)
//	{
//		WriteJump((appBaseAddr + 0x1EA974), Melee_Timeout, 1);
//	}
//	else
//	{
//		byte8 buffer[] =
//		{
//			0x8B, 0x88, 0xF4, 0x02, 0x00, 0x00, //mov ecx,[rax+000002F4]
//		};
//		vp_memcpy((appBaseAddr + 0x1EA974), buffer, sizeof(buffer));
//	}
//}
//
//void Game_Dante_WeaponSwitchTimeout_Ranged_Toggle(float32 var)
//{
//	Log("%s %.0f", FUNC_NAME, var);
//	if (var != 12)
//	{
//		WriteJump((appBaseAddr + 0x1EAA61), Ranged_Timeout, 1);
//	}
//	else
//	{
//		byte8 buffer[] =
//		{
//			0x8B, 0x88, 0xF4, 0x02, 0x00, 0x00, //mov ecx,[rax+000002F4]
//		};
//		vp_memcpy((appBaseAddr + 0x1EAA61), buffer, sizeof(buffer));
//	}
//}
