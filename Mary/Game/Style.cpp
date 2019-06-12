#include "Style.h"

typedef void(* Relax_t)(BYTE *);

Relax_t Relax = 0;

BYTE * ActivateDoppelgangerProxy       = 0;
BYTE * DeactivateDoppelgangerProxy     = 0;
BYTE * DoppelgangerRateControllerProxy = 0;
BYTE * AdjustDevilSound                = 0;

static void ActivateDoppelganger(BYTE * baseAddr)
{
	uint8 actor = GetActorId(baseAddr);
	if (actor != ACTOR_ONE)
	{
		return;
	}


	/*
	dmc3.exe+1F83D0 - 75 56                 - jne dmc3.exe+1F8428

	
	*/


	Write<BYTE>((appBaseAddr + 0x1F83D0), 0xEB); // Force Actor Update







	if (!Config.Game.Style.Doppelganger.useEXVersion)
	{
		UpdateFlux(baseAddr, DEVIL_FLUX_END);
		return;
	}
	bool devil = *(bool *)(baseAddr + 0x3E9B);
	if (devil)
	{
		UpdateFlux(baseAddr, DEVIL_FLUX_END);
	}
	*(uint32 *)(actorBaseAddr[ACTOR_TWO] + 0x3E6C) = *(uint32 *)(baseAddr + 0x3E6C);
	*(uint32 *)(actorBaseAddr[ACTOR_TWO] + 0x3E70) = *(uint32 *)(baseAddr + 0x3E70);
	*(uint32 *)(actorBaseAddr[ACTOR_TWO] + 0x3E88) = *(uint32 *)(baseAddr + 0x3E88);
	*(bool   *)(actorBaseAddr[ACTOR_TWO] + 0x3E9B) = *(bool   *)(baseAddr + 0x3E9B);
	uint8 character = *(uint8 *)(actorBaseAddr[ACTOR_TWO] + 0x78);
	if (character == CHAR_BOB)
	{
		if (devil)
		{
			*(uint32 *)(actorBaseAddr[ACTOR_TWO] + 0x3E6C) = DEVIL_BOB_YAMATO;
			*(uint32 *)(actorBaseAddr[ACTOR_TWO] + 0x3E70) = DEVIL_BOB_YAMATO;
			*(uint32 *)(actorBaseAddr[ACTOR_TWO] + 0x3E88) = DEVIL_BOB_YAMATO;
		}
		else
		{
			*(uint32 *)(actorBaseAddr[ACTOR_TWO] + 0x3E6C) = 0;
			*(uint32 *)(actorBaseAddr[ACTOR_TWO] + 0x3E70) = 0;
			*(uint32 *)(actorBaseAddr[ACTOR_TWO] + 0x3E88) = 0;
		}
	}
	else if (character == CHAR_LADY)
	{
		*(uint32 *)(actorBaseAddr[ACTOR_TWO] + 0x3E6C) = 0;
		*(uint32 *)(actorBaseAddr[ACTOR_TWO] + 0x3E70) = 0;
		*(uint32 *)(actorBaseAddr[ACTOR_TWO] + 0x3E88) = 0;
		*(bool   *)(actorBaseAddr[ACTOR_TWO] + 0x3E9B) = false;
	}
	else if (character == CHAR_VERGIL)
	{
		uint8 devilForm[] =
		{
			DEVIL_VERGIL_YAMATO,
			DEVIL_VERGIL_BEOWULF,
			DEVIL_VERGIL_FORCE_EDGE,
		};
		uint8 selectedWeapon = *(uint8 *)(actorBaseAddr[ACTOR_TWO] + 0x6488);
		if (selectedWeapon > 2)
		{
			selectedWeapon = 0;
		}
		if (devil)
		{
			*(uint32 *)(actorBaseAddr[ACTOR_TWO] + 0x3E6C) = devilForm[selectedWeapon];
			*(uint32 *)(actorBaseAddr[ACTOR_TWO] + 0x3E70) = devilForm[selectedWeapon];
			*(uint32 *)(actorBaseAddr[ACTOR_TWO] + 0x3E88) = devilForm[selectedWeapon];
		}
		else
		{
			*(uint32 *)(actorBaseAddr[ACTOR_TWO] + 0x3E6C) = 0;
			*(uint32 *)(actorBaseAddr[ACTOR_TWO] + 0x3E70) = 0;
			*(uint32 *)(actorBaseAddr[ACTOR_TWO] + 0x3E88) = 0;
		}
	}
	if (character != CHAR_LADY)
	{
		UpdateDevilForm(actorBaseAddr[ACTOR_TWO]);
	}
}

static void DeactivateDoppelganger(BYTE * baseAddr)
{
	uint8 actor = GetActorId(baseAddr);
	if (actor != ACTOR_ONE)
	{
		return;
	}

	Write<BYTE>((appBaseAddr + 0x1F83D0), 0x75);


	if (!Config.Game.Style.Doppelganger.useEXVersion)
	{
		*(uint32 *)(baseAddr + 0x3E6C) = 0;
		*(uint32 *)(baseAddr + 0x3E70) = 0;
		*(uint32 *)(baseAddr + 0x3E88) = 0;
		UpdateDevilForm(baseAddr);
		UpdateFlux(baseAddr, DEVIL_FLUX_END);
		Relax(baseAddr);
		return;
	}
	bool devil = *(bool *)(baseAddr + 0x3E9B);
	if (devil)
	{
		UpdateFlux(baseAddr, DEVIL_FLUX_START);
	}
	*(uint32 *)(actorBaseAddr[ACTOR_TWO] + 0x3E6C) = 0;
	*(uint32 *)(actorBaseAddr[ACTOR_TWO] + 0x3E70) = 0;
	*(uint32 *)(actorBaseAddr[ACTOR_TWO] + 0x3E88) = 0;
	*(bool   *)(actorBaseAddr[ACTOR_TWO] + 0x3E9B) = false;
}

static void DoppelgangerRateController(BYTE * baseAddr)
{
	static bool execute = false;
	if ((GetButtonState(ACTOR_ONE) & GetBinding(CMD_LOCK_ON)) && (GetButtonState(ACTOR_ONE) & GetBinding(CMD_TAUNT)))
	{
		if (execute)
		{
			uint32 & rate = *(uint32 *)(baseAddr + 0x6450);
			rate++;
			if (rate > 2)
			{
				rate = 0;
			}
			execute = false;
		}
	}
	else
	{
		execute = true;
	}
}

void Game_Style_Init()
{
	LogFunction();
	{
		BYTE sect1[] =
		{
			0x48, 0x8B, 0xD9,                         //mov rbx,rcx
			0x31, 0xD2,                               //xor edx,edx
			0xE8, 0x00, 0x00, 0x00, 0x00,             //call dmc3.exe+1F92C0
			0x48, 0x8B, 0x83, 0xE8, 0x3D, 0x00, 0x00, //mov rax,[rbx+00003DE8]
			0x8B, 0x80, 0xF0, 0x01, 0x00, 0x00,       //mov eax,[rax+000001F0]
			0x89, 0x83, 0xC4, 0x3E, 0x00, 0x00,       //mov [rbx+00003EC4],eax
			0x31, 0xD2,                               //xor edx,edx
			0x48, 0x8B, 0xCB,                         //mov rcx,rbx
			0xE8, 0x00, 0x00, 0x00, 0x00,             //call dmc3.exe+1F97F0
		};
		FUNC func = CreateFunction(0, 0, true, true, 0, sizeof(sect1));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteCall((func.sect1 + 5), (appBaseAddr + 0x1F92C0));
		WriteCall((func.sect1 + 0x22), (appBaseAddr + 0x1F97F0));
		Relax = (Relax_t)func.addr;
	}
	{
		BYTE sect1[] =
		{
			0x48, 0x8B, 0xCF, //mov rcx,rdi
		};
		FUNC func = CreateFunction(ActivateDoppelganger, (appBaseAddr + 0x1E930E), true, true, 0, sizeof(sect1));
		memcpy(func.sect1, sect1, sizeof(sect1));
		ActivateDoppelgangerProxy = func.addr;
	}
	{
		BYTE sect1[] =
		{
			0x48, 0x8B, 0xCB, //mov rcx,rbx
		};
		FUNC func = CreateFunction(DeactivateDoppelganger, (appBaseAddr + 0x1E2B63), true, true, 0, sizeof(sect1));
		memcpy(func.sect1, sect1, sizeof(sect1));
		DeactivateDoppelgangerProxy = func.addr;
	}
	{
		FUNC func = CreateFunction(DoppelgangerRateController);
		DoppelgangerRateControllerProxy = func.addr;
	}
	{
		BYTE sect0[] =
		{
			0x80, 0xBF, 0x62, 0x63, 0x00, 0x00, 0x01, //cmp byte ptr [rdi+00006362],01
			0x0F, 0x84, 0x00, 0x00, 0x00, 0x00,       //je dmcLauncher.exe+1F8FA1
			0x80, 0xBF, 0x9B, 0x3E, 0x00, 0x00, 0x01, //cmp byte ptr [rdi+00003E9B],01
			0x0F, 0x85, 0x00, 0x00, 0x00, 0x00,       //jne dmcLauncher.exe+1F8FA1
		};
		FUNC func = CreateFunction(0, (appBaseAddr + 0x1F8F35), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteAddress((func.sect0 + 7), (appBaseAddr + 0x1F8FA1), 6);
		WriteAddress((func.sect0 + 0x14), (appBaseAddr + 0x1F8FA1), 6);
		WriteJump((func.sect0 + 0x1A), (appBaseAddr + 0x1F8F35));
		AdjustDevilSound = func.addr;
	}
}

void Game_Style_Doppelganger_ToggleUseEXVersion(bool enable)
{
	Log("%s %u", FUNC_NAME, enable);
	if (enable)
	{
		WriteJump((appBaseAddr + 0x1E92E1), ActivateDoppelgangerProxy, 2);
		WriteJump((appBaseAddr + 0x1E2B24), DeactivateDoppelgangerProxy, 2);
		WriteCall((appBaseAddr + 0x1E25CD), DoppelgangerRateControllerProxy);
		WriteJump((appBaseAddr + 0x1F8F2C), AdjustDevilSound, 2);
		// Fixes
		Write<uint32>((appBaseAddr + 0x1E92BB), 0);                          // Disable Doppelganger Activation Devil Form
		Write<BYTE>((appBaseAddr + 0x1EAA07), 0xEB);                         // Disable Doppelganger Melee Weapon Change Devil Form Update
		Write<BYTE>((appBaseAddr + 0x1E7775), 0xEB);                         // Enable Devil Trigger Activation
		Write<BYTE>((appBaseAddr + 0x1F94A1), 0xEB);                         // Enable Devil Trigger Deactivation
		WriteAddress((appBaseAddr + 0x1E752B), (appBaseAddr + 0x1E752D), 2); // Enable Actor Two Devil Trigger
		Write<uint32>((appBaseAddr + 0x1F7D3F), 0);                          // Bob Set Visible Flag
	}
	else
	{
		{
			BYTE buffer[] =
			{
				0x80, 0xBF, 0x9B, 0x3E, 0x00, 0x00, 0x01, //cmp byte ptr [rdi+00003E9B],01
			};
			vp_memcpy((appBaseAddr + 0x1E92E1), buffer, sizeof(buffer));
		}
		{
			BYTE buffer[] =
			{
				0x80, 0xBB, 0x9B, 0x3E, 0x00, 0x00, 0x00, //cmp byte ptr [rbx+00003E9B],00
			};
			vp_memcpy((appBaseAddr + 0x1E2B24), buffer, sizeof(buffer));
		}
		WriteCall((appBaseAddr + 0x1E25CD), (appBaseAddr + 0x1E8F00));
		{
			BYTE buffer[] =
			{
				0x80, 0xBF, 0x9B, 0x3E, 0x00, 0x00, 0x01, //cmp byte ptr [rdi+00003E9B],01
			};
			vp_memcpy((appBaseAddr + 0x1F8F2C), buffer, sizeof(buffer));
		}
		Write<uint32>((appBaseAddr + 0x1E92BB), 1);
		Write<BYTE>((appBaseAddr + 0x1EAA07), 0x75);
		Write<BYTE>((appBaseAddr + 0x1E7775), 0x75);
		Write<BYTE>((appBaseAddr + 0x1F94A1), 0x74);
		WriteAddress((appBaseAddr + 0x1E752B), (appBaseAddr + 0x1E7516), 2);
		Write<uint32>((appBaseAddr + 0x1F7D3F), 1);
	}
}
