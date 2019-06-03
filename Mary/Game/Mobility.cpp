#include "Mobility.h"

BYTE * AirHikeProxy        = 0;
BYTE * AirHikeFix          = 0;
BYTE * DashProxy           = 0;
BYTE * SkyStarProxy        = 0;
BYTE * AirTrickProxy       = 0;
BYTE * AirTrickReset       = 0;
BYTE * AirTrickProxyVergil = 0;
BYTE * AirTrickResetVergil = 0;
BYTE * TrickUpProxy        = 0;
BYTE * TrickUpReset        = 0;
BYTE * TrickDownProxy      = 0;
BYTE * TrickDownReset      = 0;

static bool AirHike(BYTE * baseAddr)
{
	uint8 character = *(uint8 *)(baseAddr + 0x78);
	if (character != CHAR_DANTE)
	{
		return false;
	}
	bool devil = *(bool *)(baseAddr + 0x3E9B);
	uint8 max = devil ? Config.Game.Mobility.Devil.Dante.airHike : Config.Game.Mobility.Human.Dante.airHike;
	uint8 count = *(uint8 *)(baseAddr + 0x3F11);
	if (count)
	{
		count--;
	}
	if (count >= max)
	{
		return false;
	}
	return true;
}

static bool Dash(BYTE * baseAddr)
{
	uint8 level = *(uint8 *)(baseAddr + 0x6358);
	if (level > 2)
	{
		level = 2;
	}
	bool devil = *(bool *)(baseAddr + 0x3E9B);
	uint8 max = devil ? Config.Game.Mobility.Devil.Dante.dash[level] : Config.Game.Mobility.Human.Dante.dash[level];
	uint8 count = *(uint8 *)(baseAddr + 0x635C);
	if (count >= max)
	{
		return false;
	}
	return true;
}

static bool SkyStar(BYTE * baseAddr)
{
	bool devil = *(bool *)(baseAddr + 0x3E9B);
	uint8 max = devil ? Config.Game.Mobility.Devil.Dante.skyStar : Config.Game.Mobility.Human.Dante.skyStar;
	uint8 count = *(uint8 *)(baseAddr + 0x635D);
	if (count)
	{
		count--;
	}
	if (count >= max)
	{
		return false;
	}
	return true;
}

static bool AirTrick(BYTE * baseAddr)
{
	bool devil = *(bool *)(baseAddr + 0x3E9B);
	uint8 max = devil ? Config.Game.Mobility.Devil.Dante.airTrick : Config.Game.Mobility.Human.Dante.airTrick;
	uint8 count = *(uint8 *)(baseAddr + 0x635E);
	if (count)
	{
		count--;
	}
	if (count >= max)
	{
		return false;
	}
	return true;
}

static bool AirTrickVergil(BYTE * baseAddr)
{
	bool devil = *(bool *)(baseAddr + 0x3E9B);
	uint8 max = devil ? Config.Game.Mobility.Devil.Vergil.airTrick : Config.Game.Mobility.Human.Vergil.airTrick;
	uint8 count = *(uint8 *)(baseAddr + 0x635E);
	if (count)
	{
		count--;
	}
	if (count >= max)
	{
		return false;
	}
	return true;
}

static bool TrickUp(BYTE * baseAddr)
{
	bool devil = *(bool *)(baseAddr + 0x3E9B);
	uint8 max = devil ? Config.Game.Mobility.Devil.Vergil.trickUp : Config.Game.Mobility.Human.Vergil.trickUp;
	uint8 count = *(uint8 *)(baseAddr + 0x635F);
	if (count)
	{
		count--;
	}
	if (count >= max)
	{
		return false;
	}
	return true;
}

static bool TrickDown(BYTE * baseAddr)
{
	bool devil = *(bool *)(baseAddr + 0x3E9B);
	uint8 max = devil ? Config.Game.Mobility.Devil.Vergil.trickDown : Config.Game.Mobility.Human.Vergil.trickDown;
	uint8 count = *(uint8 *)(baseAddr + 0x6360);
	if (count)
	{
		count--;
	}
	if (count >= max)
	{
		return false;
	}
	return true;
}

void Game_Mobility_Init()
{
	LogFunction();
	{
		BYTE sect1[] =
		{
			0x48, 0x8B, 0xCB, //mov rcx,rbx
		};
		BYTE sect2[] =
		{
			0x84, 0xC0,                         //test al,al
			0x0F, 0x84, 0x00, 0x00, 0x00, 0x00, //je dmc3.exe+1E9B3A
		};
		FUNC func = CreateFunction(AirHike, (appBaseAddr + 0x1E9AB6), true, false, 0, sizeof(sect1), sizeof(sect2));
		memcpy(func.sect1, sect1, sizeof(sect1));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteAddress((func.sect2 + 2), (appBaseAddr + 0x1E9B3A), 6);
		AirHikeProxy = func.addr;
	}
	{
		BYTE sect0[] =
		{
			0x41, 0x80, 0x78, 0x78, 0x00,                   //cmp byte ptr [r8+78],CHAR_DANTE
			0x74, 0x0A,                                     //je short
			0x41, 0xC6, 0x80, 0x11, 0x3F, 0x00, 0x00, 0x00, //mov byte ptr [r8+00003F11],00
			0xEB, 0x07,                                     //jmp short
			0x41, 0xFE, 0x80, 0x11, 0x3F, 0x00, 0x00,       //inc byte ptr [r8+00003F11]
		};
		FUNC func = CreateFunction(0, (appBaseAddr + 0x1E1016), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		AirHikeFix = func.addr;
	}
	{
		BYTE sect1[] =
		{
			0x48, 0x8B, 0xCB, //mov rcx,rbx
		};
		BYTE sect2[] =
		{
			0x84, 0xC0,                               //test al,al
			0x0F, 0x84, 0x00, 0x00, 0x00, 0x00,       //je dmc3.exe+1E64A9
			0x0F, 0xB6, 0x83, 0x5C, 0x63, 0x00, 0x00, //movzx eax,byte ptr [rbx+0000635C]
		};
		FUNC func = CreateFunction(Dash,(appBaseAddr + 0x1E6708), true, false, 0, sizeof(sect1), sizeof(sect2));
		memcpy(func.sect1, sect1, sizeof(sect1));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteAddress((func.sect2 + 2), (appBaseAddr + 0x1E64A9), 6);
		DashProxy = func.addr;
	}
	{
		BYTE sect1[] =
		{
			0x48, 0x8B, 0xCB, //mov rcx,rbx
		};
		BYTE sect2[] =
		{
			0x84, 0xC0,                               //test al,al
			0x0F, 0x84, 0x00, 0x00, 0x00, 0x00,       //je dmc3.exe+1E64A9
			0x0F, 0xB6, 0x83, 0x5D, 0x63, 0x00, 0x00, //movzx eax,byte ptr [rbx+0000635D]
		};
		FUNC func = CreateFunction(SkyStar, (appBaseAddr + 0x1E66A5), true, false, 0, sizeof(sect1), sizeof(sect2));
		memcpy(func.sect1, sect1, sizeof(sect1));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteAddress((func.sect2 + 2), (appBaseAddr + 0x1E64A9), 6);
		SkyStarProxy = func.addr;
	}
	{
		BYTE sect1[] =
		{
			0x48, 0x8B, 0xCB, //mov rcx,rbx
		};
		BYTE sect2[] =
		{
			0x84, 0xC0,                         //test al,al
			0x0F, 0x84, 0x00, 0x00, 0x00, 0x00, //je dmc3.exe+1E64A9
		};
		FUNC func = CreateFunction(AirTrick, (appBaseAddr + 0x1E6640), true, false, 0, sizeof(sect1), sizeof(sect2));
		memcpy(func.sect1, sect1, sizeof(sect1));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteAddress((func.sect2 + 2), (appBaseAddr + 0x1E64A9), 6);
		AirTrickProxy = func.addr;
	}
	{
		BYTE sect0[] =
		{
			0x80, 0xBF, 0x64, 0x3E, 0x00, 0x00, 0x01, //cmp byte ptr [rdi+00003E64],01
			0x75, 0x06,                               //jne short
			0xFE, 0x87, 0x5E, 0x63, 0x00, 0x00,       //inc byte ptr [rdi+0000635E]
		};
		FUNC func = CreateFunction(0, (appBaseAddr + 0x1F222F), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		AirTrickReset = func.addr;
	}
	{
		BYTE sect1[] =
		{
			0x48, 0x8B, 0xCB, //mov rcx,rbx
		};
		BYTE sect2[] =
		{
			0x84, 0xC0,                         //test al,al
			0x0F, 0x84, 0x00, 0x00, 0x00, 0x00, //je dmc3.exe+1E64A9
		};
		FUNC func = CreateFunction(AirTrickVergil, (appBaseAddr + 0x1E6861), true, false, 0, sizeof(sect1), sizeof(sect2));
		memcpy(func.sect1, sect1, sizeof(sect1));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteAddress((func.sect2 + 2), (appBaseAddr + 0x1E64A9), 6);
		AirTrickProxyVergil = func.addr;
	}
	{
		BYTE sect0[] =
		{
			0x80, 0xBB, 0x64, 0x3E, 0x00, 0x00, 0x01, //cmp byte ptr [rbx+00003E64],01
			0x75, 0x06,                               //jne short
			0xFE, 0x83, 0x5E, 0x63, 0x00, 0x00,       //inc byte ptr [rbx+0000635E]
		};
		FUNC func = CreateFunction(0, (appBaseAddr + 0x1F0C99), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		AirTrickResetVergil = func.addr;
	}
	{
		BYTE sect1[] =
		{
			0x48, 0x8B, 0xCB, //mov rcx,rbx
		};
		BYTE sect2[] =
		{
			0x84, 0xC0,                         //test al,al
			0x0F, 0x84, 0x00, 0x00, 0x00, 0x00, //je dmc3.exe+1E64A9
		};
		FUNC func = CreateFunction(TrickUp, (appBaseAddr + 0x1E6801), true, false, 0, sizeof(sect1), sizeof(sect2));
		memcpy(func.sect1, sect1, sizeof(sect1));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteAddress((func.sect2 + 2), (appBaseAddr + 0x1E64A9), 6);
		TrickUpProxy = func.addr;
	}
	{
		BYTE sect0[] =
		{
			0x80, 0xBB, 0x64, 0x3E, 0x00, 0x00, 0x01, //cmp byte ptr [rbx+00003E64],01
			0x75, 0x06,                               //jne short
			0xFE, 0x83, 0x5F, 0x63, 0x00, 0x00,       //inc byte ptr [rbx+0000635F]
		};
		FUNC func = CreateFunction(0, (appBaseAddr + 0x1F0B31), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		TrickUpReset = func.addr;
	}
	{
		BYTE sect1[] =
		{
			0x48, 0x8B, 0xCB, //mov rcx,rbx
		};
		BYTE sect2[] =
		{
			0x84, 0xC0,                         //test al,al
			0x0F, 0x84, 0x00, 0x00, 0x00, 0x00, //je dmc3.exe+1E64A9
		};
		FUNC func = CreateFunction(TrickDown, (appBaseAddr + 0x1E6794), true, false, 0, sizeof(sect1), sizeof(sect2));
		memcpy(func.sect1, sect1, sizeof(sect1));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteAddress((func.sect2 + 2), (appBaseAddr + 0x1E64A9), 6);
		TrickDownProxy = func.addr;
	}
	{
		BYTE sect0[] =
		{
			0x80, 0xBB, 0x64, 0x3E, 0x00, 0x00, 0x01, //cmp byte ptr [rbx+00003E64],01
			0x75, 0x06,                               //jne short
			0xFE, 0x83, 0x60, 0x63, 0x00, 0x00,       //inc byte ptr [rbx+00006360]
		};
		FUNC func = CreateFunction(0, (appBaseAddr + 0x1F0A3A), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		TrickDownReset = func.addr;
	}
}

void Game_Mobility_Toggle(bool enable)
{
	Log("%s %u", FUNC_NAME, enable);
	if (enable)
	{
		WriteJump((appBaseAddr + 0x1E9AA9), AirHikeProxy, 2);
		Write<BYTE>((appBaseAddr + 0x1E0FF8), 0x80);
		WriteJump((appBaseAddr + 0x1E100E), AirHikeFix, 3);
		WriteJump((appBaseAddr + 0x1E66CB), DashProxy, 1);
		WriteJump((appBaseAddr + 0x1E6696), SkyStarProxy, 2);
		Write<BYTE>((appBaseAddr + 0x1E66A6), 0xC0);
		WriteJump((appBaseAddr + 0x1E6634), AirTrickProxy, 1);
		Write<BYTE>((appBaseAddr + 0x1E664D), 0x83);
		WriteJump((appBaseAddr + 0x1F2228), AirTrickReset, 2);
		WriteJump((appBaseAddr + 0x1E6854), AirTrickProxyVergil, 2);
		Write<BYTE>((appBaseAddr + 0x1E686E), 0x83);
		WriteJump((appBaseAddr + 0x1F0C92), AirTrickResetVergil, 2);
		WriteJump((appBaseAddr + 0x1E67F4), TrickUpProxy, 2);
		Write<BYTE>((appBaseAddr + 0x1E680E), 0x83);
		WriteJump((appBaseAddr + 0x1F0B2A), TrickUpReset, 2);
		WriteJump((appBaseAddr + 0x1E6787), TrickDownProxy, 2);
		Write<BYTE>((appBaseAddr + 0x1E67A1), 0x83);
		WriteJump((appBaseAddr + 0x1F0A33), TrickDownReset, 2);
	}
	else
	{
		{
			BYTE buffer[] =
			{
				0x80, 0xBB, 0x11, 0x3F, 0x00, 0x00, 0x00, //cmp byte ptr [rbx+00003F11],00
			};
			vp_memcpy((appBaseAddr + 0x1E9AA9), buffer, sizeof(buffer));
		}
		Write<BYTE>((appBaseAddr + 0x1E0FF8), 0x88);
		{
			BYTE buffer[] =
			{
				0x41, 0xC6, 0x80, 0x11, 0x3F, 0x00, 0x00, 0x00, //mov byte ptr [r8+00003F11],00
			};
			vp_memcpy((appBaseAddr + 0x1E100E), buffer, sizeof(buffer));
		}
		{
			BYTE buffer[] =
			{
				0x8B, 0x8B, 0x58, 0x63, 0x00, 0x00, //mov ecx,[rbx+00006358]
			};
			vp_memcpy((appBaseAddr + 0x1E66CB), buffer, sizeof(buffer));
		}
		{
			BYTE buffer[] =
			{
				0x0F, 0xB6, 0x83, 0x5D, 0x63, 0x00, 0x00, //movzx eax,byte ptr [rbx+0000635D]
			};
			vp_memcpy((appBaseAddr + 0x1E6696), buffer, sizeof(buffer));
		}
		Write<BYTE>((appBaseAddr + 0x1E66A6), 0xC8);
		{
			BYTE buffer[] =
			{
				0x38, 0x8B, 0x5E, 0x63, 0x00, 0x00, //cmp [rbx+0000635E],cl
			};
			vp_memcpy((appBaseAddr + 0x1E6634), buffer, sizeof(buffer));
		}
		Write<BYTE>((appBaseAddr + 0x1E664D), 0x8B);
		{
			BYTE buffer[] =
			{
				0xC6, 0x87, 0x5E, 0x63, 0x00, 0x00, 0x00, //mov byte ptr [rdi+0000635E],00
			};
			vp_memcpy((appBaseAddr + 0x1F2228), buffer, sizeof(buffer));
		}
		{
			BYTE buffer[] =
			{
				0x80, 0xBB, 0x5E, 0x63, 0x00, 0x00, 0x00, //cmp byte ptr [rbx+0000635E],00
			};
			vp_memcpy((appBaseAddr + 0x1E6854), buffer, sizeof(buffer));
			
		}
		Write<BYTE>((appBaseAddr + 0x1E686E), 0x8B);
		{
			BYTE buffer[] =
			{
				0x40, 0x88, 0xBB, 0x5E, 0x63, 0x00, 0x00, //mov [rbx+0000635E],dil
			};
			vp_memcpy((appBaseAddr + 0x1F0C92), buffer, sizeof(buffer));
		}
		{
			BYTE buffer[] =
			{
				0x80, 0xBB, 0x5F, 0x63, 0x00, 0x00, 0x00, //cmp byte ptr [rbx+0000635F],00
			};
			vp_memcpy((appBaseAddr + 0x1E67F4), buffer, sizeof(buffer));
			
		}
		Write<BYTE>((appBaseAddr + 0x1E680E), 0x8B);
		{
			BYTE buffer[] =
			{
				0x40, 0x88, 0xBB, 0x5F, 0x63, 0x00, 0x00, //mov [rbx+0000635F],dil
			};
			vp_memcpy((appBaseAddr + 0x1F0B2A), buffer, sizeof(buffer));
		}
		{
			BYTE buffer[] =
			{
				0x80, 0xBB, 0x60, 0x63, 0x00, 0x00, 0x00, //cmp byte ptr [rbx+00006360],00
			};
			vp_memcpy((appBaseAddr + 0x1E6787), buffer, sizeof(buffer));
		}
		Write<BYTE>((appBaseAddr + 0x1E67A1), 0x8B);
		{
			BYTE buffer[] =
			{
				0x40, 0x88, 0xBB, 0x60, 0x63, 0x00, 0x00, //mov [rbx+00006360],dil
			};
			vp_memcpy((appBaseAddr + 0x1F0A33), buffer, sizeof(buffer));
		}
	}
}
