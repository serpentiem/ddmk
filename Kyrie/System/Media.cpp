#include "Media.h"

BYTE * GameSelect = 0;

void System_Media_Init()
{
	LogFunction();
	{
		BYTE sect0[] =
		{
			0xBA, 0x00, 0x00, 0x00, 0x00, //mov edx
			0x0F, 0xB6, 0x12,             //movzx edx,byte ptr [edx]
		};
		FUNC func = CreateFunction(0, (appBaseAddr + 0x1FE83), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*(uint8 **)(func.sect0 + 1) = &Config.System.Media.skipIntroGameSelect;
		GameSelect = func.addr;
	}
}

void System_Media_ToggleSkipIntro(bool enable)
{
	LogFunctionBool(enable);
	if (enable)
	{
		WriteJump((appBaseAddr + 0x1FE7D), GameSelect, 1);
	}
	else
	{
		BYTE buffer[] =
		{
			0x8B, 0x91, 0xBC, 0x01, 0x00, 0x00, //mov edx,[ecx+000001BC]
		};
		vp_memcpy((appBaseAddr + 0x1FE7D), buffer, sizeof(buffer));
	}
}
