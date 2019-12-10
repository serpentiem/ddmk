#include "Dante.h"

BYTE * SpardaIdFix     = 0;
BYTE * SpardaEffectFix = 0;

void Game_Dante_Init()
{
	LogFunction();
	{
		BYTE sect0[] =
		{
			0x0F, 0xB6, 0x87, 0xCC, 0x1B, 0x00, 0x00, //movzx eax,byte ptr [rdi+00001BCC]
			0x83, 0xF8, 0x03,                         //cmp eax,WEAPON_SPARDA
			0x74, 0x02,                               //je short
			0x31, 0xC0,                               //xor eax,eax
			0x41, 0x8D, 0x4C, 0x24, 0x03,             //lea ecx,[r12+03]
		};
		FUNC func = CreateFunction(0, (appBaseAddr + 0x2C565B), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		SpardaIdFix = func.addr;
	}
	{
		BYTE sect0[] =
		{
			0x48, 0x8B, 0x05, 0x00, 0x00, 0x00, 0x00,       //mov rax,[dmc1.exe+60B148]
			0x48, 0x85, 0xC0,                               //test rax,rax
			0x0F, 0x84, 0x00, 0x00, 0x00, 0x00,             //je dmc1.exe+748C0
			0x66, 0x83, 0xB8, 0x74, 0x02, 0x00, 0x00, 0x09, //cmp word ptr [rax+00000274],09
			0x0F, 0x84, 0x00, 0x00, 0x00, 0x00,             //je dmc1.exe+748C0
			0xC3,                                           //ret
		};
		FUNC func = CreateFunction(0, 0, false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteAddress(func.sect0, (appBaseAddr + 0x60B148), 7);
		WriteAddress((func.sect0 + 0xA), (appBaseAddr + 0x748C0), 6);
		WriteAddress((func.sect0 + 0x18), (appBaseAddr + 0x748C0), 6);
		SpardaEffectFix = func.addr;
	}
}

void Game_Dante_ForceEdge_ToggleUnlockStinger(bool enable)
{
	LogFunction(enable);
	if (enable)
	{
		WriteAddress((appBaseAddr + 0x2EAF0B), (appBaseAddr + 0x2EAF11), 6);
	}
	else
	{
		WriteAddress((appBaseAddr + 0x2EAF0B), (appBaseAddr + 0x2EB290), 6);
	}
}

void Game_Dante_ForceEdge_ToggleUnlockRoundTrip(bool enable)
{
	LogFunction(enable);
	if (enable)
	{
		WriteAddress((appBaseAddr + 0x2EB29C), (appBaseAddr + 0x2EB29E), 2); // Initiator
		WriteAddress((appBaseAddr + 0x2D6911), (appBaseAddr + 0x2D6913), 2); // First Hit
		WriteAddress((appBaseAddr + 0x2D6C7C), (appBaseAddr + 0x2D6C7E), 2); // Second Hit
		WriteAddress((appBaseAddr + 0x2D787C), (appBaseAddr + 0x2D787E), 2); // Double Blows
		WriteAddress((appBaseAddr + 0x2DF82D), (appBaseAddr + 0x2DF82F), 2); // Million Stab
	}
	else
	{
		WriteAddress((appBaseAddr + 0x2EB29C), (appBaseAddr + 0x2EB2CE), 2);
		WriteAddress((appBaseAddr + 0x2D6911), (appBaseAddr + 0x2D693B), 2);
		WriteAddress((appBaseAddr + 0x2D6C7C), (appBaseAddr + 0x2D6CAC), 2);
		WriteAddress((appBaseAddr + 0x2D787C), (appBaseAddr + 0x2D7890), 2);
		WriteAddress((appBaseAddr + 0x2DF82D), (appBaseAddr + 0x2DF841), 2);
	}
}

void Game_Dante_Sparda_ToggleUnlockDevilTrigger(bool enable)
{
	LogFunction(enable);
	if (enable)
	{
		WriteJump((appBaseAddr + 0x2C5656), SpardaIdFix);
		Write<BYTE>((appBaseAddr + 0x3F2581), WEAPON_SPARDA);
		Write<BYTE *>((appBaseAddr + 0x482958), SpardaEffectFix);
	}
	else
	{
		{
			BYTE buffer[] =
			{
				0x41, 0x8D, 0x4C, 0x24, 0x03, //lea ecx,[r12+03]
			};
			vp_memcpy((appBaseAddr + 0x2C5656), buffer, sizeof(buffer));
		}
		Write<BYTE>((appBaseAddr + 0x3F2581), WEAPON_FORCE_EDGE);
		Write<BYTE *>((appBaseAddr + 0x482958), (appBaseAddr + 0x748C0));
	}
}

void Game_Dante_Sparda_ToggleForceLoadAssets(bool enable)
{
	LogFunction(enable);
	if (enable)
	{
		{
			vp_memset((appBaseAddr + 0x2C57AD), 0x90, 12);
			BYTE buffer[] =
			{
				0xB9, 0x03, 0x00, 0x00, 0x00, //mov ecx,WEAPON_SPARDA
			};
			vp_memcpy((appBaseAddr + 0x2C57AD), buffer, sizeof(buffer));
		}
	}
	else
	{
		{
			BYTE buffer[] =
			{
				0x44, 0x3A, 0xC0,                   //cmp r8l,al
				0x0F, 0x84, 0x00, 0x00, 0x00, 0x00, //je dmc1.exe+2C584F
				0x0F, 0xB6, 0xC8,                   //movzx ecx,al
			};
			vp_memcpy((appBaseAddr + 0x2C57AD), buffer, sizeof(buffer));
			WriteAddress((appBaseAddr + 0x2C57B0), (appBaseAddr + 0x2C584F), 6);
		}
	}
}

void Game_Dante_Yamato_ToggleUnlock(bool enable)
{
	LogFunction(enable);
	if (enable)
	{
		WriteAddress((appBaseAddr + 0x2CDE98), (appBaseAddr + 0x2CDE9A), 2); // Fix Model
		WriteAddress((appBaseAddr + 0x3EBAE3), (appBaseAddr + 0x3EBAE5), 2); // OnEnter
		WriteAddress((appBaseAddr + 0x3F1793), (appBaseAddr + 0x3F1795), 2); // OnEquip
	}
	else
	{
		WriteAddress((appBaseAddr + 0x2CDE98), (appBaseAddr + 0x2CDF06), 2);
		WriteAddress((appBaseAddr + 0x3EBAE3), (appBaseAddr + 0x3EBAEC), 2);
		WriteAddress((appBaseAddr + 0x3F1793), (appBaseAddr + 0x3F179D), 2);
	}
}

void Game_Dante_Yamato_Acquire()
{
	LogFunction();
	BYTE * addr = *(BYTE **)(appBaseAddr + 0x5EAB88);
	if (!addr)
	{
		return;
	}
	uint8 & count = *(uint8 *)(addr + 0x207B);
	ITEM_STRUCT * item = (ITEM_STRUCT *)(addr + 0x2090);
	item[count].category = 0;
	item[count].id       = ITEM_YAMATO;
	item[count].count    = 1;
	count++;
}

void Game_Dante_AirHike_ToggleCoreAbility(bool enable)
{
	LogFunction(enable);
	if (enable)
	{
		Write<BYTE>((appBaseAddr + 0x2EC755), 0xEB);
	}
	else
	{
		Write<BYTE>((appBaseAddr + 0x2EC755), 0x74);
	}
}
