#include "Attack.h"

extern bool Game_Dante_Rebellion_quickDrive;

static void SetMove(BYTE * baseAddr)
{
	if (!Config.Game.Dante.Rebellion.unlockQuickDrive)
	{
		return;
	}
	uint8 character = *(uint8 *)(baseAddr + 0x78);
	uint32 style = *(uint32 *)(baseAddr + 0x6338);
	uint8 & move = *(uint8 *)(baseAddr + 0x3FA4);


	//loop

	uint8 actor = GetActorId(baseAddr);





	if ((character == CHAR_DANTE) && (style == STYLE_SWORDMASTER) && (GetButtonState(actor) & GetBinding(CMD_STYLE_ACTION)) && (move == 2))
	{
		move = 13;
		Game_Dante_Rebellion_quickDrive = true;
	}
}

void Game_Attack_Init()
{
	LogFunction();
	{
		BYTE sect2[] =
		{
			0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc3.exe+1E0800
		};
		FUNC func = CreateFunction(SetMove, (appBaseAddr + 0x1E6DB4), true, true, 0, 0, sizeof(sect2));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteCall(func.sect2, (appBaseAddr + 0x1E0800));
		WriteJump((appBaseAddr + 0x1E6DAF), func.addr);
	}
}
