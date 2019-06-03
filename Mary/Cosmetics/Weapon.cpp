#include "Weapon.h"

BYTE * ApplyModelAttributesProxy    = 0;
BYTE * Melee_IsWeaponReadyProxy     = 0;
BYTE * Melee_IsWeaponReadyRebellion = 0;
BYTE * Melee_IsWeaponReadyCerberus  = 0;
BYTE * Melee_IsWeaponReadyAgniRudra = 0;
BYTE * Melee_IsWeaponReadyNevan     = 0;
BYTE * Melee_IsWeaponReadyBeowulf   = 0;
BYTE * Melee_DefaultSetWeaponProxy  = 0;
BYTE * Ranged_IsWeaponReadyProxy    = 0;
BYTE * Ranged_IsWeaponReadyArtemis  = 0;
BYTE * Ranged_DefaultSetWeaponProxy = 0;

static void ApplyModelAttributes(BYTE * baseAddr)
{
	LogFunction();
	if (!Config.Cosmetics.Weapon.instantModelUpdate)
	{
		return;
	}
	uint8 character = *(uint8 *)(baseAddr + 0x78);
	if (character != CHAR_DANTE)
	{
		return;
	}
	uint8 * equipment = (uint8 *)(baseAddr + 0x6498);
	uint8 selectedWeapon = *(uint8 *)(baseAddr + 0x6490);
	if ((equipment[selectedWeapon] == WEAPON_BEOWULF) && !Config.Cosmetics.Dante.hideBeowulf)
	{
		ApplyBeowulfModelAttributes(baseAddr);
	}
	else
	{
		ApplyDefaultModelAttributes(baseAddr);
	}
}

static bool Melee_IsWeaponReady(BYTE * baseAddr, uint8 weaponId)
{
	BYTE * actorBaseAddr = *(BYTE **)(baseAddr + 0x120);
	if (!actorBaseAddr)
	{
		return false;
	}
	uint8 actor = GetActorId(actorBaseAddr);
	uint8 character = *(uint8 *)(actorBaseAddr + 0x78);
	if ((weaponId == WEAPON_BEOWULF) && (character == CHAR_VERGIL))
	{
		return true;
	}
	bool devil = *(bool *)(actorBaseAddr + 0x3E9B);
	if ((weaponId == WEAPON_BEOWULF) && devil && Config.Game.WeaponSwitcher.enable && (Config.Game.WeaponSwitcher.devil == DEVIL_DANTE_BEOWULF))
	{
		return true;
	}
	uint8   motion         = *(uint8 *)(actorBaseAddr + 0x39B3);
	uint8   selectedWeapon = *(uint8 *)(actorBaseAddr + 0x6490);
	uint8 * equipment      =  (uint8 *)(actorBaseAddr + 0x6498);

	// Check if a motion associated with the weapon is active.

	if ((motion == (weaponId + 3)) || (motion == (weaponId + 13)))
	{
		if (updateModelAttributes && (weaponId == equipment[selectedWeapon]))
		{
			if (weaponId == WEAPON_BEOWULF && !Config.Cosmetics.Dante.hideBeowulf)
			{
				ApplyBeowulfModelAttributes(actorBaseAddr);
			}
			else
			{
				ApplyDefaultModelAttributes(actorBaseAddr);
			}
			updateModelAttributes[actor] = false;
		}
		return true;
	}

	// Only one weapon is active at a time.
	// So, if we're here it means our weapon is not active, but it might be idle: So check if another weapon of the same type is active.

	uint8 motionId[] =
	{
		MOT_DANTE_REBELLION,
		MOT_DANTE_CERBERUS,
		MOT_DANTE_AGNI_RUDRA,
		MOT_DANTE_NEVAN,
		MOT_DANTE_BEOWULF,
		MOT_DANTE_SWORDMASTER_REBELLION,
		MOT_DANTE_SWORDMASTER_CERBERUS,
		MOT_DANTE_SWORDMASTER_AGNI_RUDRA,
		MOT_DANTE_SWORDMASTER_NEVAN,
		MOT_DANTE_SWORDMASTER_BEOWULF,
	};
	uint8 off = 3;
	for (uint8 i = 0; i < countof(motionId); i++)
	{
		if (i == 5)
		{
			off = 13;
		}
		if ((motion == motionId[i]) && (motion != (weaponId + off)))
		{
			return false;
		}
	}

	// If we reach this point neither our weapon nor other weapons of the same type are active.
	// So now just check if the weapon is equipped and selected.

	if (equipment[selectedWeapon] == weaponId)
	{
		if (updateModelAttributes)
		{
			if (weaponId == WEAPON_BEOWULF && !Config.Cosmetics.Dante.hideBeowulf)
			{
				ApplyBeowulfModelAttributes(actorBaseAddr);
			}
			else
			{
				ApplyDefaultModelAttributes(actorBaseAddr);
			}
			updateModelAttributes[actor] = false;
		}
		return true;
	}

	return false;
}

static void Melee_DefaultSetWeapon(BYTE * baseAddr)
{
	uint8 selectedWeapon = *(uint8 *)(baseAddr + 0x6490);
	uint8 * equipment = (uint8 *)(baseAddr + 0x6498);
	uint8 & model = *(uint8 *)(baseAddr + 0x64F0);
	model = equipment[selectedWeapon];
	uint8 actor = GetActorId(baseAddr);
	updateModelAttributes[actor] = true;
}

static bool Ranged_IsWeaponReady(BYTE * baseAddr, uint8 weaponId)
{
	BYTE * actorBaseAddr = *(BYTE **)(baseAddr + 0x120);
	if (!actorBaseAddr)
	{
		return false;
	}
	uint8 motion = *(uint8 *)(actorBaseAddr + 0x39B3);
	if ((motion == (weaponId + 3)) || (motion == (weaponId + 13)))
	{
		return true;
	}
	uint8 motionId[] =
	{
		MOT_DANTE_EBONY_IVORY,
		MOT_DANTE_SHOTGUN,
		MOT_DANTE_ARTEMIS,
		MOT_DANTE_SPIRAL,
		MOT_DANTE_KALINA_ANN,
		MOT_DANTE_GUNSLINGER_EBONY_IVORY,
		MOT_DANTE_GUNSLINGER_SHOTGUN,
		MOT_DANTE_GUNSLINGER_ARTEMIS,
		MOT_DANTE_GUNSLINGER_SPIRAL,
		MOT_DANTE_GUNSLINGER_KALINA_ANN,
	};
	uint8 off = 3;
	for (uint8 i = 0; i < countof(motionId); i++)
	{
		if (i == 5)
		{
			off = 13;
		}
		if ((motion == motionId[i]) && (motion != (weaponId + off)))
		{
			return false;
		}
	}
	uint8 selectedWeapon = *(uint8 *)(actorBaseAddr + 0x6494);
	selectedWeapon -= 2;
	uint8 * equipment = (uint8 *)(actorBaseAddr + 0x649A);
	if (equipment[selectedWeapon] == weaponId)
	{
		return true;
	}
	return false;
}

static void Ranged_DefaultSetWeapon(BYTE * baseAddr)
{
	uint8 selectedWeapon = *(uint8 *)(baseAddr + 0x6494);
	selectedWeapon -= 2;
	uint8 * equipment = (uint8 *)(baseAddr + 0x649A);
	uint8 & model = *(uint8 *)(baseAddr + 0x64F1);
	model = equipment[selectedWeapon];
}

void Cosmetics_Weapon_Init()
{
	LogFunction();
	{
		BYTE sect2[] =
		{
			0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc3.exe+1DFC20
		};
		FUNC func = CreateFunction(ApplyModelAttributes, (appBaseAddr + 0x1DF2DA), true, true, 0, 0, sizeof(sect2));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteCall(func.sect2, (appBaseAddr + 0x1DFC20));
		ApplyModelAttributesProxy = func.addr;
	}
	// Melee
	{
		FUNC func = CreateFunction(Melee_IsWeaponReady, 0, true, false);
		Melee_IsWeaponReadyProxy = func.addr;
	}
	{
		BYTE sect0[] =
		{
			0xBA, 0x00, 0x00, 0x00, 0x00, //mov edx
			0xE8, 0x00, 0x00, 0x00, 0x00, //call
		};
		BYTE ** addr[] =
		{
			&Melee_IsWeaponReadyRebellion,
			&Melee_IsWeaponReadyCerberus,
			&Melee_IsWeaponReadyAgniRudra,
			&Melee_IsWeaponReadyNevan,
		};
		BYTE * jumpAddr[] =
		{
			(appBaseAddr + 0x231633),
			(appBaseAddr + 0x22FAD9),
			(appBaseAddr + 0x2288A9),
			(appBaseAddr + 0x22AD32),
		};
		for (uint8 weapon = 0; weapon < 4; weapon++)
		{
			FUNC func = CreateFunction(0, jumpAddr[weapon], false, true, sizeof(sect0));
			memcpy(func.sect0, sect0, sizeof(sect0));
			*(uint8 *)((func.sect0 + 1)) = weapon;
			WriteCall((func.sect0 + 5), Melee_IsWeaponReadyProxy);
			*addr[weapon] = func.addr;
		}
		{
			BYTE sect0[] =
			{
				0xBA, 0x04, 0x00, 0x00, 0x00,       //mov edx,WEAPON_BEOWULF
				0xE8, 0x00, 0x00, 0x00, 0x00,       //call IsWeaponReadyProxy
				0x84, 0xC0,                         //test al,al
				0x0F, 0x84, 0x00, 0x00, 0x00, 0x00, //je dmcLauncher.exe+2295BC
				0xE8, 0x00, 0x00, 0x00, 0x00,       //call dmcLauncher.exe+1FDE10
			};
			FUNC func = CreateFunction(0, (appBaseAddr + 0x2295BC), false, true, sizeof(sect0));
			memcpy(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 5), Melee_IsWeaponReadyProxy);
			WriteAddress((func.sect0 + 0xC), (appBaseAddr + 0x2295BC), 6);
			WriteCall((func.sect0 + 0x12), (appBaseAddr + 0x1FDE10));
			Melee_IsWeaponReadyBeowulf = func.addr;
		}
	}
	{
		BYTE sect0[] =
		{
			0x89, 0x9F, 0x90, 0x64, 0x00, 0x00, //mov [rdi+00006490],ebx

		};
		BYTE sect1[] =
		{
			0x48, 0x8B, 0xCF, //mov rcx,rdi
		};
		FUNC func = CreateFunction(Melee_DefaultSetWeapon, (appBaseAddr + 0x1EA9E4), true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		Melee_DefaultSetWeaponProxy = func.addr;
	}
	// Ranged
	{
		FUNC func = CreateFunction(Ranged_IsWeaponReady, 0, true, false);
		Ranged_IsWeaponReadyProxy = func.addr;
	}
	{
		BYTE sect0[] =
		{
			0xBA, 0x07, 0x00, 0x00, 0x00,       //mov edx,WEAPON_ARTEMIS
			0xE8, 0x00, 0x00, 0x00, 0x00,       //call IsWeaponReady
			0x84, 0xC0,                         //test al,al
			0x0F, 0x84, 0x00, 0x00, 0x00, 0x00, //je dmcLauncher.exe+22CBCD
			0xE8, 0x00, 0x00, 0x00, 0x00,       //call dmcLauncher.exe+1FDE10
		};
		FUNC func = CreateFunction(0, (appBaseAddr + 0x22CBCD), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteCall((func.sect0 + 5), Ranged_IsWeaponReadyProxy);
		WriteAddress((func.sect0 + 0xC), (appBaseAddr + 0x22CBCD), 6);
		WriteCall((func.sect0 + 0x12), (appBaseAddr + 0x1FDE10));
		Ranged_IsWeaponReadyArtemis = func.addr;
	}
	{
		BYTE sect0[] =
		{
			0x89, 0x9F, 0x94, 0x64, 0x00, 0x00, //mov [rdi+00006494],ebx
		};
		BYTE sect1[] =
		{
			0x48, 0x8B, 0xCF, //mov rcx,rdi
		};
		FUNC func = CreateFunction(Ranged_DefaultSetWeapon, (appBaseAddr + 0x1EAAD1), true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		Ranged_DefaultSetWeaponProxy = func.addr;
	}
}

void Cosmetics_Weapon_ToggleInstantModelUpdate(bool enable)
{
	Log("%s %u", FUNC_NAME, enable);
	if (enable)
	{
		WriteJump((appBaseAddr + 0x1DF2D5), ApplyModelAttributesProxy);
		WriteJump((appBaseAddr + 0x23162E), Melee_IsWeaponReadyRebellion);
		WriteJump((appBaseAddr + 0x22FAD4), Melee_IsWeaponReadyCerberus);
		WriteJump((appBaseAddr + 0x2288A4), Melee_IsWeaponReadyAgniRudra);
		WriteJump((appBaseAddr + 0x22AD2D), Melee_IsWeaponReadyNevan);
		WriteJump((appBaseAddr + 0x2295B7), Melee_IsWeaponReadyBeowulf);
		WriteJump((appBaseAddr + 0x1EA9DE), Melee_DefaultSetWeaponProxy, 1);
		WriteAddress((appBaseAddr + 0x2292E0), (appBaseAddr + 0x2292E6), 6);
		WriteJump((appBaseAddr + 0x22CBC8), Ranged_IsWeaponReadyArtemis);
		WriteJump((appBaseAddr + 0x1EAACB), Ranged_DefaultSetWeaponProxy, 1);
	}
	else
	{
		WriteCall((appBaseAddr + 0x1DF2D5), (appBaseAddr + 0x1DFC20));
		WriteCall((appBaseAddr + 0x23162E), (appBaseAddr + 0x1FD3E0));
		WriteCall((appBaseAddr + 0x22FAD4), (appBaseAddr + 0x1FD3E0));
		WriteCall((appBaseAddr + 0x2288A4), (appBaseAddr + 0x1FD3E0));
		WriteCall((appBaseAddr + 0x22AD2D), (appBaseAddr + 0x1FD3E0));
		WriteCall((appBaseAddr + 0x2295B7), (appBaseAddr + 0x1FDE10));
		{
			BYTE buffer[] =
			{
				0x89, 0x9F, 0x90, 0x64, 0x00, 0x00, //mov [rdi+00006490],ebx
			};
			vp_memcpy((appBaseAddr + 0x1EA9DE), buffer, sizeof(buffer));
		}
		WriteAddress((appBaseAddr + 0x2292E0), (appBaseAddr + 0x2295C1), 6);
		WriteCall((appBaseAddr + 0x22CBC8), (appBaseAddr + 0x1FDE10));
		{
			BYTE buffer[] =
			{
				0x89, 0x9F, 0x94, 0x64, 0x00, 0x00, //mov [rdi+00006494],ebx
			};
			vp_memcpy((appBaseAddr + 0x1EAACB), buffer, sizeof(buffer));
		}
	}
	Cosmetics_Dante_Beowulf_LiveUpdate();
}
