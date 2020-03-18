#include "Vergil.h"





byte * Levitate = 0;
static byte * Melee_Timeout = 0; // And here I thought variables were static by default. :/

void Game_Vergil_Init()
{
	LogFunction();
	{
		byte sect0[] =
		{
			0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rax,&System_Actor_actorBaseAddr[ACTOR_ONE]
			0x48, 0x8B, 0x00,                                           //mov rax,[rax]
			0x48, 0x85, 0xC0,                                           //test rax,rax
			0x74, 0x0E,                                                 //je short
			0x8A, 0x80, 0x61, 0x63, 0x00, 0x00,                         //mov al,[rax+00006361]
			0x84, 0xC0,                                                 //test al,al
			0x0F, 0x85, 0x00, 0x00, 0x00, 0x00,                         //jne dmc3.exe+1DB8FD
			0xF3, 0x0F, 0x5C, 0x43, 0x14,                               //subss xmm0,[rbx+14]
		};
		FUNC func = CreateFunction(0, (appBaseAddr + 0x1DB8FD), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		//Write<byte **>((func.sect0 + 2), &System_Actor_actorBaseAddr[ACTOR_ONE]);
		WriteAddress((func.sect0 + 0x1A), (appBaseAddr + 0x1DB8FD), 6);
		Levitate = func.addr;
	}
	{
		byte sect0[] =
		{
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rcx
			0x8B, 0x09,                                                 //mov ecx,[rcx]
		};
		FUNC func = CreateFunction(0, 0, false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*(float32 **)(func.sect0 + 2) = &Config.Game.Vergil.WeaponSwitchTimeout.melee;
		Melee_Timeout = func.addr;
	}
}

void Game_Vergil_ForceEdge_ToggleInfiniteRoundTrip(bool enable)
{
	Log("%s %u", FUNC_NAME, enable);
	if (enable)
	{
		vp_memset((appBaseAddr + 0x1D86DD), 0x90, 5);
		vp_memset((appBaseAddr + 0x222921), 0x90, 5);
	}
	else
	{
		{
			byte buffer[] =
			{
				0xF3, 0x0F, 0x5C, 0x47, 0x14, //subss xmm0,[rdi+14]
			};
			vp_memcpy((appBaseAddr + 0x1D86DD), buffer, sizeof(buffer));
		}
		{
			byte buffer[] =
			{
				0xF3, 0x0F, 0x5C, 0x47, 0x14, //subss xmm0,[rdi+14]
			};
			vp_memcpy((appBaseAddr + 0x222921), buffer, sizeof(buffer));
		}
	}
}

void Game_Vergil_SummonedSwords_ToggleChronoSwords(bool enable)
{
	Log("%s %u", FUNC_NAME, enable);
	if (enable)
	{
		WriteJump((appBaseAddr + 0x1DB8F8), Levitate);
	}
	else
	{
		byte buffer[] =
		{
			0xF3, 0x0F, 0x5C, 0x43, 0x14, //subss xmm0,[rbx+14]
		};
		vp_memcpy((appBaseAddr + 0x1DB8F8), buffer, sizeof(buffer));
	}
}

void Game_Vergil_WeaponSwitchTimeout_MeleeToggle(float32 var)
{
	Log("%s %.0f", FUNC_NAME, var);
	if (var != 8)
	{
		WriteCall((appBaseAddr + 0x1E6E4D), Melee_Timeout, 1);
		WriteCall((appBaseAddr + 0x1E6E60), Melee_Timeout, 1);
		WriteCall((appBaseAddr + 0x1E6F4A), Melee_Timeout, 1);
		WriteCall((appBaseAddr + 0x1E6F5D), Melee_Timeout, 1);
	}
	else
	{
		byte buffer[] =
		{
			0x8B, 0x88, 0x48, 0x03, 0x00, 0x00, //mov ecx,[rax+00000348]
		};
		vp_memcpy((appBaseAddr + 0x1E6E4D), buffer, sizeof(buffer));
		vp_memcpy((appBaseAddr + 0x1E6E60), buffer, sizeof(buffer));
		vp_memcpy((appBaseAddr + 0x1E6F4A), buffer, sizeof(buffer));
		vp_memcpy((appBaseAddr + 0x1E6F5D), buffer, sizeof(buffer));
	}
}
