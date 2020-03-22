#include "Animation.h"


// @Todo: Update.


// @Todo: Should really be motion.


extern bool Game_Dante_Rebellion_quickDrive;

static uint32 PlayAnimation(byte * baseAddr, uint8 file, uint8 index)
{
	if (!Config.Game.Dante.Rebellion.unlockQuickDrive)
	{
		return 0;
	}
	uint8 character = *(uint8 *)(baseAddr + 0x78);
	if (character != CHAR_LOGIC_DANTE)
	{
		return 0;
	}
	if (file != 3)
	{
		return 0;
	}
	byte ** motionAddr = (byte **)(baseAddr + 0x38A0);
	//motionAddr[MOT_DANTE_REBELLION] = System_Cache_file[pl000_00_3];
	motionAddr[MOT_DANTE_REBELLION] = System_File_cacheFile[pl000_00_3];
	if (!Game_Dante_Rebellion_quickDrive)
	{
		return 0;
	}
	Game_Dante_Rebellion_quickDrive = false;
	motionAddr[MOT_DANTE_REBELLION] = demo_pl000_00_3;
	return 30;
}

void System_Animation_Init()
{
	LogFunction();
	{
		byte sect0[] =
		{
			0x48, 0x89, 0x5C, 0x24, 0x08, //mov [rsp+08],rbx
		};
		byte sect2[] =
		{
			0x85, 0xC0,       //test eax,eax
			0x74, 0x03,       //je short
			0x44, 0x8B, 0xC0, //mov r8d,eax
		};
		FUNC func = CreateFunction(PlayAnimation, (appBaseAddr + 0x1EFB95), true, false, sizeof(sect0), 0, sizeof(sect2));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect2, sect2, sizeof(sect2));
		//WriteJump((appBaseAddr + 0x1EFB90), func.addr);
	}
}
