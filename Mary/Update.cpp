#include "Update.h"

void InGameMenuAccess()
{
	Game_StyleSwitcher_Controller();
	Game_ResetMotionState_Controller();
}

void Update_Init()
{
	LogFunction();
	{
		byte8 sect0[] =
		{
			0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc3.exe+23B060
		};
		FUNC func = CreateFunction(InGameMenuAccess, (appBaseAddr + 0x23D4B7), true, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteCall(func.sect0, (appBaseAddr + 0x23B060));
		WriteJump((appBaseAddr + 0x23D4B2), func.addr);
		/*
		dmc3.exe+23D4B2 - E8 A9DBFFFF           - call dmc3.exe+23B060
		dmc3.exe+23D4B7 - 84 C0                 - test al,al
		*/
	}
}
