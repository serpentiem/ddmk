#include "Other.h"

byte * DanteAuraFix = 0;

void Cosmetics_Other_Init()
{
	LogFunction();
	{
		byte sect0[] =
		{
			0x49, 0x63, 0x86, 0x6C, 0x3E, 0x00, 0x00,       //movsxd rax,dword ptr [r14+00003E6C]
			0x48, 0x31, 0xC9,                               //xor rcx,rcx
			0x41, 0x8A, 0x8E, 0x90, 0x64, 0x00, 0x00,       //mov cl,[r14+00006490]
			0x42, 0x8A, 0x8C, 0x31, 0x98, 0x64, 0x00, 0x00, //mov cl,[rcx+r14+00006498]
		};
		FUNC func = CreateFunction(0, (appBaseAddr + 0x90B6F), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		DanteAuraFix = func.addr;
	}
}

void Cosmetics_Other_ToggleNoDevilForm(bool enable)
{
	Log("%s %u", FUNC_NAME, enable);
	if (enable)
	{
		Write<word>((appBaseAddr + 0x1F733C), 0xE990);       // Model
		Write<byte>((appBaseAddr + 0x1F539A), 0x88);         // Motion
		WriteJump((appBaseAddr + 0x90B60), DanteAuraFix, 2);
	}
	else
	{
		Write<word>((appBaseAddr + 0x1F733C), 0x840F);
		Write<byte>((appBaseAddr + 0x1F539A), 0x6C);
		{
			byte buffer[] =
			{
				0x49, 0x63, 0x86, 0x6C, 0x3E, 0x00, 0x00, //movsxd rax,dword ptr [r14+00003E6C]
			};
			vp_memcpy((appBaseAddr + 0x90B60), buffer, sizeof(buffer));
		}
	}
}
