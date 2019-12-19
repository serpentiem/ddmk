#include "Weapon.h"

//byte * ApplyModelAttributesProxy    = 0;
//byte * Melee_IsWeaponReadyProxy     = 0;
//byte * Melee_IsWeaponReadyRebellion = 0;
//byte * Melee_IsWeaponReadyCerberus  = 0;
//byte * Melee_IsWeaponReadyAgniRudra = 0;
//byte * Melee_IsWeaponReadyNevan     = 0;
//byte * Melee_IsWeaponReadyBeowulf   = 0;
//byte * Melee_DefaultSetWeaponProxy  = 0;
//byte * Ranged_IsWeaponReadyProxy    = 0;
//byte * Ranged_IsWeaponReadyArtemis  = 0;
//byte * Ranged_DefaultSetWeaponProxy = 0;

// @Todo: Seems redundant.

//static void ApplyModelAttributes(byte * baseAddr)
//{
//	LogFunction();
//	if (!Config.Cosmetics.Weapon.instantModelUpdate)
//	{
//		return;
//	}
//	uint8 character = *(uint8 *)(baseAddr + 0x78);
//	if (character != CHAR_DANTE)
//	{
//		return;
//	}
//	uint8 * equipment = (uint8 *)(baseAddr + 0x6498);
//	uint8 selectedWeapon = *(uint8 *)(baseAddr + 0x6490);
//	if ((equipment[selectedWeapon] == WEAPON_BEOWULF) && !Config.Cosmetics.Dante.hideBeowulf)
//	{
//		ApplyBeowulfModelAttributes(baseAddr);
//	}
//	else
//	{
//		ApplyDefaultModelAttributes(baseAddr);
//	}
//}

//static bool Melee_IsWeaponReady(byte * baseAddr, uint8 weaponId)
//{
//	byte * actorBaseAddr = *(byte **)(baseAddr + 0x120);
//	if (!actorBaseAddr)
//	{
//		return false;
//	}
//	uint8 actor = GetActorId(actorBaseAddr);
//	uint8 character = *(uint8 *)(actorBaseAddr + 0x78);
//	if ((weaponId == WEAPON_BEOWULF) && (character == CHAR_VERGIL))
//	{
//		return true;
//	}
//	bool devil = *(bool *)(actorBaseAddr + 0x3E9B);
//	if ((weaponId == WEAPON_BEOWULF) && devil && Config.Game.WeaponSwitcher.enable && (Config.Game.WeaponSwitcher.devil == DEVIL_DANTE_BEOWULF))
//	{
//		return true;
//	}
//	uint8   motion         = *(uint8 *)(actorBaseAddr + 0x39B3); // actually group.
//	uint8   selectedWeapon = *(uint8 *)(actorBaseAddr + 0x6490);
//	uint8 * equipment      =  (uint8 *)(actorBaseAddr + 0x6498);
//
//	// Check if a motion group associated with the weapon is active.
//
//	// Check if the weapon's motion group is active.
//
//
//
//
//	if ((motion == (weaponId + 3)) || (motion == (weaponId + 13))) // @Todo: Create enums for this.
//	{
//
//		// @Todo: Swap around.
//
//		// error lel
//
//		if (updateModelAttributes && (weaponId == equipment[selectedWeapon]))
//		{
//
//			// System_Actor_Dante_updateModelAttributes;
//			// Cosmetics_Dante_UpdateModelAttributes(byte8 * baseAddr, uint8 weaponId);
//
//			//System::Actor::GetActorCount();
//
//			//System_Actor_GetCount();
//
//			// System_Actor_GetActorCount();
//
//			// auto & GetActorCount = System_Actor_GetActorCount();
//
//
//			// auto & count = System::Actor::GetActorCount();
//
//			// auto count = System_Actor_GetActorCount();
//
//
//
//
//
//
//
//
//
//
//			// @Todo: Merge into one function.
//			// e. g. UpdateModelAttributes
//			// include update flag
//
//			if (weaponId == WEAPON_BEOWULF && !Config.Cosmetics.Dante.hideBeowulf)
//			{
//				ApplyBeowulfModelAttributes(actorBaseAddr);
//			}
//			else
//			{
//				ApplyDefaultModelAttributes(actorBaseAddr);
//			}
//
//
//
//
//			updateModelAttributes[actor] = false;
//		}
//		return true;
//	}
//
//	// Only one weapon is active at a time.
//	// So, if we're here it means our weapon is not active, but it might be idle: So check if another weapon of the same type is active.
//
//	// i. e. actor might just stand there, you still have to show the weapon though.
//
//
//
//
//
//	uint8 motionId[] =
//	{
//		MOT_DANTE_REBELLION,
//		MOT_DANTE_CERBERUS,
//		MOT_DANTE_AGNI_RUDRA,
//		MOT_DANTE_NEVAN,
//		MOT_DANTE_BEOWULF,
//		MOT_DANTE_SWORDMASTER_REBELLION,
//		MOT_DANTE_SWORDMASTER_CERBERUS,
//		MOT_DANTE_SWORDMASTER_AGNI_RUDRA,
//		MOT_DANTE_SWORDMASTER_NEVAN,
//		MOT_DANTE_SWORDMASTER_BEOWULF,
//	};
//	uint8 off = 3;
//	for (uint8 i = 0; i < countof(motionId); i++)
//	{
//		if (i == 5)
//		{
//			off = 13;
//		}
//		if ((motion == motionId[i]) && (motion != (weaponId + off)))
//		{
//			return false;
//		}
//	}
//
//	// If we reach this point neither our weapon nor other weapons of the same type are active.
//	// So now just check if the weapon is equipped and selected.
//
//	if (equipment[selectedWeapon] == weaponId)
//	{
//		if (updateModelAttributes)
//		{
//			if (weaponId == WEAPON_BEOWULF && !Config.Cosmetics.Dante.hideBeowulf)
//			{
//				ApplyBeowulfModelAttributes(actorBaseAddr);
//			}
//			else
//			{
//				ApplyDefaultModelAttributes(actorBaseAddr);
//			}
//			updateModelAttributes[actor] = false;
//		}
//		return true;
//	}
//
//
//
//
//
//
//
//
//
//	return false;
//}




//static void Melee_DefaultSetWeapon(byte * baseAddr)
//{
//	uint8 selectedWeapon = *(uint8 *)(baseAddr + 0x6490);
//	uint8 * equipment = (uint8 *)(baseAddr + 0x6498);
//	uint8 & model = *(uint8 *)(baseAddr + 0x64F0);
//	model = equipment[selectedWeapon];
//	uint8 actor = GetActorId(baseAddr);
//	updateModelAttributes[actor] = true;
//}
//
//static bool Ranged_IsWeaponReady(byte * baseAddr, uint8 weaponId)
//{
//	byte * actorBaseAddr = *(byte **)(baseAddr + 0x120);
//	if (!actorBaseAddr)
//	{
//		return false;
//	}
//	uint8 motion = *(uint8 *)(actorBaseAddr + 0x39B3);
//	if ((motion == (weaponId + 3)) || (motion == (weaponId + 13)))
//	{
//		return true;
//	}
//	uint8 motionId[] =
//	{
//		MOT_DANTE_EBONY_IVORY,
//		MOT_DANTE_SHOTGUN,
//		MOT_DANTE_ARTEMIS,
//		MOT_DANTE_SPIRAL,
//		MOT_DANTE_KALINA_ANN,
//		MOT_DANTE_GUNSLINGER_EBONY_IVORY,
//		MOT_DANTE_GUNSLINGER_SHOTGUN,
//		MOT_DANTE_GUNSLINGER_ARTEMIS,
//		MOT_DANTE_GUNSLINGER_SPIRAL,
//		MOT_DANTE_GUNSLINGER_KALINA_ANN,
//	};
//	uint8 off = 3;
//	for (uint8 i = 0; i < countof(motionId); i++)
//	{
//		if (i == 5)
//		{
//			off = 13;
//		}
//		if ((motion == motionId[i]) && (motion != (weaponId + off)))
//		{
//			return false;
//		}
//	}
//	uint8 selectedWeapon = *(uint8 *)(actorBaseAddr + 0x6494);
//	selectedWeapon -= 2;
//	uint8 * equipment = (uint8 *)(actorBaseAddr + 0x649A);
//	if (equipment[selectedWeapon] == weaponId)
//	{
//		return true;
//	}
//	return false;
//}
//
//static void Ranged_DefaultSetWeapon(byte * baseAddr)
//{
//	uint8 selectedWeapon = *(uint8 *)(baseAddr + 0x6494);
//	selectedWeapon -= 2;
//	uint8 * equipment = (uint8 *)(baseAddr + 0x649A);
//	uint8 & model = *(uint8 *)(baseAddr + 0x64F1);
//	model = equipment[selectedWeapon];
//}

void Cosmetics_Weapon_Init()
{
	LogFunction();
	//{
	//	byte sect2[] =
	//	{
	//		0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc3.exe+1DFC20
	//	};
	//	FUNC func = CreateFunction(ApplyModelAttributes, (appBaseAddr + 0x1DF2DA), true, true, 0, 0, sizeof(sect2));
	//	memcpy(func.sect2, sect2, sizeof(sect2));
	//	WriteCall(func.sect2, (appBaseAddr + 0x1DFC20));
	//	ApplyModelAttributesProxy = func.addr;
	//}
















}

//void Cosmetics_Weapon_ToggleInstantModelUpdate(bool enable)
//{
//	Log("%s %u", FUNC_NAME, enable);
//	if (enable)
//	{
//		WriteJump((appBaseAddr + 0x1DF2D5), ApplyModelAttributesProxy);
//		WriteJump((appBaseAddr + 0x23162E), Melee_IsWeaponReadyRebellion);
//		WriteJump((appBaseAddr + 0x22FAD4), Melee_IsWeaponReadyCerberus);
//		WriteJump((appBaseAddr + 0x2288A4), Melee_IsWeaponReadyAgniRudra);
//		WriteJump((appBaseAddr + 0x22AD2D), Melee_IsWeaponReadyNevan);
//		WriteJump((appBaseAddr + 0x2295B7), Melee_IsWeaponReadyBeowulf);
//		WriteJump((appBaseAddr + 0x1EA9DE), Melee_DefaultSetWeaponProxy, 1);
//		WriteAddress((appBaseAddr + 0x2292E0), (appBaseAddr + 0x2292E6), 6);
//		WriteJump((appBaseAddr + 0x22CBC8), Ranged_IsWeaponReadyArtemis);
//		WriteJump((appBaseAddr + 0x1EAACB), Ranged_DefaultSetWeaponProxy, 1);
//	}
//	else
//	{
//		WriteCall((appBaseAddr + 0x1DF2D5), (appBaseAddr + 0x1DFC20));
//		WriteCall((appBaseAddr + 0x23162E), (appBaseAddr + 0x1FD3E0));
//		WriteCall((appBaseAddr + 0x22FAD4), (appBaseAddr + 0x1FD3E0));
//		WriteCall((appBaseAddr + 0x2288A4), (appBaseAddr + 0x1FD3E0));
//		WriteCall((appBaseAddr + 0x22AD2D), (appBaseAddr + 0x1FD3E0));
//		WriteCall((appBaseAddr + 0x2295B7), (appBaseAddr + 0x1FDE10));
//		{
//			byte buffer[] =
//			{
//				0x89, 0x9F, 0x90, 0x64, 0x00, 0x00, //mov [rdi+00006490],ebx
//			};
//			vp_memcpy((appBaseAddr + 0x1EA9DE), buffer, sizeof(buffer));
//		}
//		WriteAddress((appBaseAddr + 0x2292E0), (appBaseAddr + 0x2295C1), 6);
//		WriteCall((appBaseAddr + 0x22CBC8), (appBaseAddr + 0x1FDE10));
//		{
//			byte buffer[] =
//			{
//				0x89, 0x9F, 0x94, 0x64, 0x00, 0x00, //mov [rdi+00006494],ebx
//			};
//			vp_memcpy((appBaseAddr + 0x1EAACB), buffer, sizeof(buffer));
//		}
//	}
//	Cosmetics_Dante_Beowulf_LiveUpdate();
//}
