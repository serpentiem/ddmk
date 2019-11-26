#include "Dante.h"

UpdateExpertise_t UpdateExpertise = 0;

byte * RainStorm      = 0;
byte * Melee_Timeout  = 0;
byte * Ranged_Timeout = 0;

bool Game_Dante_Rebellion_quickDrive = false;

void Game_Dante_Init()
{
	LogFunction();

	//g_proc.pos = 64;

	//Log("g_proc addr %llX", &g_proc);




	{
		FUNC func = CreateFunction((appBaseAddr + 0x212A90), 0);
		UpdateExpertise = (UpdateExpertise_t)func.addr;
	}
	{
		byte sect0[] =
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
	{
		byte sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rcx
			0x8B, 0x09,                                                 //mov ecx,[rcx]
		};
		FUNC func = CreateFunction(0, (appBaseAddr + 0x1EA97A), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*(float32 **)(func.sect0 + 2) = &Config.Game.Dante.WeaponSwitchTimeout.melee;
		Melee_Timeout = func.addr;
	}
	{
		byte sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rcx
			0x8B, 0x09,                                                 //mov ecx,[rcx]
		};
		FUNC func = CreateFunction(0, (appBaseAddr + 0x1EAA67), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*(float32 **)(func.sect0 + 2) = &Config.Game.Dante.WeaponSwitchTimeout.ranged;
		Ranged_Timeout = func.addr;
	}
}

void Game_Dante_Rebellion_ToggleInfiniteSwordPierce(bool enable)
{
	Log("%s %u", FUNC_NAME, enable);
	if (enable)
	{
		vp_memset((appBaseAddr + 0x1CC9A4), 0x90, 5);
		vp_memset((appBaseAddr + 0x1CDA1B), 0x90, 4);
		vp_memset((appBaseAddr + 0x1CDD64), 0x90, 5);
		vp_memset((appBaseAddr + 0x1CDDCE), 0x90, 4);
		vp_memset((appBaseAddr + 0x21562E), 0x90, 5);
	}
	else
	{
		{
			byte buffer[] =
			{
				0xF3, 0x0F, 0x5C, 0x4B, 0x14, //subss xmm1,[rbx+14]
			};
			vp_memcpy((appBaseAddr + 0x1CC9A4), buffer, sizeof(buffer));
		}
		{
			byte buffer[] =
			{
				0xF3, 0x0F, 0x5C, 0xC1, //subss xmm0,xmm1
			};
			vp_memcpy((appBaseAddr + 0x1CDA1B), buffer, sizeof(buffer));
		}
		{
			byte buffer[] =
			{
				0xF3, 0x0F, 0x5C, 0x4B, 0x14, //subss xmm1,[rbx+14]
			};
			vp_memcpy((appBaseAddr + 0x1CDD64), buffer, sizeof(buffer));
		}
		{
			byte buffer[] =
			{
				0xF3, 0x0F, 0x5C, 0xCA, //subss xmm1,xmm2
			};
			vp_memcpy((appBaseAddr + 0x1CDDCE), buffer, sizeof(buffer));
		}
		{
			byte buffer[] =
			{
				0xF3, 0x0F, 0x5C, 0x47, 0x14, //subss xmm0,[rdi+14]
			};
			vp_memcpy((appBaseAddr + 0x21562E), buffer, sizeof(buffer));
		}
	}
}

void Game_Dante_EbonyIvory_ToggleFoursomeTime(bool enable)
{
	Log("%s %u", FUNC_NAME, enable);
	if (enable)
	{
		WriteAddress((appBaseAddr + 0x1E24F6), (appBaseAddr + 0x1E24FC), 6);
		WriteAddress((appBaseAddr + 0x20D188), (appBaseAddr + 0x20D18A), 2);
	}
	else
	{
		WriteAddress((appBaseAddr + 0x1E24F6), (appBaseAddr + 0x1E259C), 6);
		WriteAddress((appBaseAddr + 0x20D188), (appBaseAddr + 0x20D1AB), 2);
	}
}

void Game_Dante_EbonyIvory_ToggleInfiniteRainStorm(bool enable)
{
	Log("%s %u", FUNC_NAME, enable);
	if (enable)
	{
		WriteJump((appBaseAddr + 0x20CC0F), RainStorm);
	}
	else
	{
		byte buffer[] =
		{
			0x0F, 0xA3, 0xC1, //bt ecx,eax
			0x72, 0x0C,       //jb dmc3.exe+20CC20
		};
		vp_memcpy((appBaseAddr + 0x20CC0F), buffer, sizeof(buffer));
	}
}

void Game_Dante_Artemis_ToggleSwap(bool enable)
{
	Log("%s %u", FUNC_NAME, enable);
	if (enable)
	{
		byte buffer[] =
		{
			0xC6, 0x87, 0x80, 0xB8, 0x00, 0x00, 0x01, //mov byte ptr [rdi+0000B880],01
		};
		vp_memcpy((appBaseAddr + 0x215C78), buffer, sizeof(buffer));
		Write<byte>((appBaseAddr + 0x215CDA), 0x00);
	}
	else
	{
		byte buffer[] =
		{
			0x44, 0x88, 0xB7, 0x80, 0xB8, 0x00, 0x00, //mov [rdi+0000B880],r14l
		};
		vp_memcpy((appBaseAddr + 0x215C78), buffer, sizeof(buffer));
		Write<byte>((appBaseAddr + 0x215CDA), 0x01);
	}
}

void Game_Dante_Artemis_ToggleInstant(bool enable)
{
	Log("%s %u", FUNC_NAME, enable);
	if (enable)
	{
		WriteAddress((appBaseAddr + 0x215E42), (appBaseAddr + 0x215E48), 6);
	}
	else
	{
		WriteAddress((appBaseAddr + 0x215E42), (appBaseAddr + 0x215F78), 6);
	}
}

void Game_Dante_AirHike_ToggleCoreAbility(bool enable)
{
	Log("%s %u", FUNC_NAME, enable);
	if (enable)
	{
		Write<byte>((appBaseAddr + 0x1E9B0E), 0xEB);
	}
	else
	{
		Write<byte>((appBaseAddr + 0x1E9B0E), 0x74);
	}
}

void Game_Dante_CrazyCombo_SetLevelMultiplier(uint8 multiplier)
{
	LogFunction();
	Write<uint8>((appBaseAddr + 0x5898DE), multiplier);
	Write<uint8>((appBaseAddr + 0x58999E), multiplier);
	Write<uint8>((appBaseAddr + 0x589A5E), multiplier);
}

void Game_Dante_WeaponSwitchTimeout_MeleeToggle(float32 var)
{
	Log("%s %.0f", FUNC_NAME, var);
	if (var != 12)
	{
		WriteJump((appBaseAddr + 0x1EA974), Melee_Timeout, 1);
	}
	else
	{
		byte buffer[] =
		{
			0x8B, 0x88, 0xF4, 0x02, 0x00, 0x00, //mov ecx,[rax+000002F4]
		};
		vp_memcpy((appBaseAddr + 0x1EA974), buffer, sizeof(buffer));
	}
}

void Game_Dante_WeaponSwitchTimeout_RangedToggle(float32 var)
{
	Log("%s %.0f", FUNC_NAME, var);
	if (var != 12)
	{
		WriteJump((appBaseAddr + 0x1EAA61), Ranged_Timeout, 1);
	}
	else
	{
		byte buffer[] =
		{
			0x8B, 0x88, 0xF4, 0x02, 0x00, 0x00, //mov ecx,[rax+000002F4]
		};
		vp_memcpy((appBaseAddr + 0x1EAA61), buffer, sizeof(buffer));
	}
}
