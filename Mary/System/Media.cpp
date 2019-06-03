#include "Media.h"

PlayTrack_t PlayTrack = 0;

DWORD mediaError     = MEDIA_NO_ERROR;
bool  mediaSkipTrack = false;

void System_Media_Init()
{
	LogFunction();
	{
		BYTE sect1[] =
		{
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00, //lea rcx,[dmc3.exe+CF3700]
			0xE8, 0x00, 0x00, 0x00, 0x00,             //call dmc3.exe+32BE20
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00, //lea rcx,[dmc3.exe+CF3708]
			0x48, 0x8B, 0x55, 0x78,                   //mov rdx,[rbp+78]
			0x45, 0x31, 0xC0,                         //xor r8d,r8d
			0x45, 0x31, 0xC9,                         //xor r9d,r9d
			0xE8, 0x00, 0x00, 0x00, 0x00,             //call dmc3.exe+32BA90
		};
		FUNC func = CreateFunction(0, 0, true, true, 0, sizeof(sect1));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteAddress(func.sect1, (appBaseAddr + 0xCF3700), 7);
		WriteCall((func.sect1 + 7), (appBaseAddr + 0x32BE20));
		WriteAddress((func.sect1 + 0xC), (appBaseAddr + 0xCF3708), 7);
		WriteCall((func.sect1 + 0x1D), (appBaseAddr + 0x32BA90));
		PlayTrack = (PlayTrack_t)func.addr;
	}
}

void System_Media_ToggleSkipIntro(bool enable)
{
	Log("%s %u", FUNC_NAME, enable);
	if (enable)
	{
		WriteAddress((appBaseAddr + 0x2383F2), (appBaseAddr + 0x2383F8), 6); // Skip Message
		WriteAddress((appBaseAddr + 0x241789), (appBaseAddr + 0x24178B), 2); // Skip Video
		vp_memset((appBaseAddr + 0x243531), 0x90, 2);                        // Disable Video Timer
		Write<BYTE>((appBaseAddr + 0x238704), 0x00);                         // Hide Rebellion
	}
	else
	{
		WriteAddress((appBaseAddr + 0x2383F2), (appBaseAddr + 0x238527), 6);
		WriteAddress((appBaseAddr + 0x241789), (appBaseAddr + 0x2417A6), 2);
		{
			BYTE payload[] =
			{
				0xFF, 0xC8, //dec eax
			};
			vp_memcpy((appBaseAddr + 0x243531), payload, sizeof(payload));
		}
		Write<BYTE>((appBaseAddr + 0x238704), 0x01);
	}
}

void System_Media_ToggleSkipCutscenes(bool enable)
{
	Log("%s %u", FUNC_NAME, enable);
	if (enable)
	{
		WriteAddress((appBaseAddr + 0x238CCA), (appBaseAddr + 0x238CD0), 6);
		WriteAddress((appBaseAddr + 0x238CD8), (appBaseAddr + 0x238CDE), 6);
		WriteAddress((appBaseAddr + 0x238CE3), (appBaseAddr + 0x238CE9), 6);
	}
	else
	{
		WriteAddress((appBaseAddr + 0x238CCA), (appBaseAddr + 0x238E62), 6);
		WriteAddress((appBaseAddr + 0x238CD8), (appBaseAddr + 0x238E62), 6);
		WriteAddress((appBaseAddr + 0x238CE3), (appBaseAddr + 0x238E62), 6);
	}
}
