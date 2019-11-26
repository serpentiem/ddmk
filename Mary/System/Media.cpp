#include "Media.h"

PlayTrack_t PlayTrack = 0;

dword mediaError     = MEDIA_NO_ERROR;
bool  mediaSkipTrack = false;

void System_Media_Init()
{
	LogFunction();
	{
		byte sect1[] =
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
