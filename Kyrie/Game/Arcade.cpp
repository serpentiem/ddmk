#include "Arcade.h"

uint32 Game_Arcade_missionMap[21] =
{
	1,
	2,
	3,
	4,
	5,
	6,
	7,
	8,
	9,
	10,
	11,
	12,
	13,
	14,
	15,
	16,
	17,
	18,
	19,
	20,
	50,
};
uint8 Game_Arcade_missionIndex = 0;

uint32 Game_Arcade_modeMap[7] =
{
	MODE_HUMAN,
	MODE_DEVIL_HUNTER,
	MODE_SON_OF_SPARDA,
	MODE_DANTE_MUST_DIE,
	MODE_LEGENDARY_DARK_KNIGHT,
	MODE_SON_OF_SPARDA,
	MODE_SON_OF_SPARDA,
};
uint8 Game_Arcade_modeIndex = 0;

BYTE * InitMainMenu = 0;

void Game_Arcade_Init()
{
	LogFunction();
	{
		BYTE sect0[] =
		{
			0x83, 0xEC, 0x08,                   //sub esp,08
			0x56,                               //push esi
			0x57,                               //push edi
			0x53,                               //push ebx
			0x55,                               //push ebp
			0x8B, 0x35, 0x00, 0x00, 0x00, 0x00, //mov esi,[dmc4.exe+F59F00]
			0x31, 0xFF,                         //xor edi,edi
			0xBB, 0x01, 0x00, 0x00, 0x00,       //mov ebx,00000001
			0x8B, 0x2D, 0x00, 0x00, 0x00, 0x00, //mov ebp,[dmc4.exe+F59F10]
		};
		FUNC func = CreateFunction(0, (appBaseAddr + 0x7B2C9), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*(BYTE **)(func.sect0 +    9) = (appBaseAddr + 0xF59F00);
		*(BYTE **)(func.sect0 + 0x16) = (appBaseAddr + 0xF59F10);
		InitMainMenu = func.addr;
	}
}

void Game_Arcade_Toggle(bool enable)
{
	LogFunctionBool(enable);
	if (enable)
	{
		Write<BYTE *>((appBaseAddr + 0xC10570), InitMainMenu);
		// Mission Start Menu Auto Confirm
		WriteAddress((appBaseAddr + 0x77DED), (appBaseAddr + 0x77DF3), 6);
		// Bloody Palace Menu Auto Confirm
		WriteAddress((appBaseAddr + 0x46C32), (appBaseAddr + 0x46C38), 6);
	}
	else
	{
		Write<BYTE *>((appBaseAddr + 0xC10570), (appBaseAddr + 0x7B1A0));
		WriteAddress((appBaseAddr + 0x77DED), (appBaseAddr + 0x77EE4), 6);
		WriteAddress((appBaseAddr + 0x46C32), (appBaseAddr + 0x46CEC), 6);
	}
}
