
// @Todo: More auto.
// @Research: Move sword model logic to Cosmetics and add Yamato.



// constexpr stringItemOff[] =
// {
// 0x4EB278, // font\lei20_4c.bin
// };




#include "Weapon.h"









bool System_Weapon_enableUpdateWeapon      = false;
bool System_Weapon_enableDoppelgangerFixes = false;
bool System_Weapon_enableModelFixes        = false;

//byte8 * System_Weapon_weaponMetadata[MAX_ACTOR][MAX_WEAPON] = {};

System_Weapon_Dante_UpdateExpertise_t System_Weapon_Dante_UpdateExpertise = 0;

extern uint8 Game_WeaponSwitcher_Melee_index;
extern uint8 Game_WeaponSwitcher_Ranged_index;

PrivateStart;

//struct FileItemHelper
//{
//	uint16 fileItemId;
//	uint16 stringItemId;
//	uint16 cacheFileId;
//	void Update()
//	{
//		FILE_ITEM   * fileItemAddr   = (FILE_ITEM   *)(appBaseAddr + 0xC99D30); // dmc3.exe+1DF696 - 48 8D 0D 93A6AB00 - lea rcx,[dmc3.exe+C99D30]
//
//
//
//
//		STRING_ITEM * stringItemAddr = (STRING_ITEM *)(appBaseAddr + 0x5B0F50); // dmc3.exe+1B922E - 48 8D 05 5B7E3F00 - lea rax,[dmc3.exe+5B1090]
//
//		FILE_ITEM   & fileItem   = fileItemAddr[fileItemId];
//		STRING_ITEM & stringItem = stringItemAddr[stringItemId];
//
//		memset(&fileItem, 0, sizeof(FILE_ITEM));
//
//		fileItem.status     = FILE_ITEM_READY;
//		fileItem.stringItem = &stringItem;
//		fileItem.file       = System_Cache_file[cacheFileId];
//	};
//};
//
//FileItemHelper fileItemHelperDante[] =
//{
//	{ 140, 0, plwp_sword    },
//	{ 141, 1, plwp_nunchaku },
//	{ 142, 2, plwp_2sword   },
//	{ 143, 3, plwp_guitar   },
//	{ 144, 4, plwp_fight    },
//	{ 145, 5, plwp_gun      },
//	{ 146, 6, plwp_shotgun  },
//	{ 147, 7, plwp_laser    },
//	{ 148, 8, plwp_rifle    },
//	{ 149, 9, plwp_ladygun  },
//};
//
//FileItemHelper fileItemHelperBob[] =
//{
//	{ 169, 14, plwp_vergilsword },
//};
//
//FileItemHelper fileItemHelperLady[] =
//{
//	{ 179, 9 , plwp_ladygun  },
//	{ 180, 10, plwp_ladygun1 },
//};
//
//FileItemHelper fileItemHelperVergil[] =
//{
//	{ 196, 11, plwp_newvergilsword },
//	{ 189, 17, plwp_newvergilfight },
//	{ 198, 13, plwp_forceedge      },
//	{ 187, 18, plwp_nerosword      },
//};
//
//FileItemHelper * fileItemHelper[] =
//{
//	fileItemHelperDante,
//	fileItemHelperBob,
//	fileItemHelperLady,
//	fileItemHelperVergil,
//};
//
//uint8 fileItemHelperCount[] =
//{
//	countof(fileItemHelperDante),
//	countof(fileItemHelperBob),
//	countof(fileItemHelperLady),
//	countof(fileItemHelperVergil),
//};
//
//struct SwordHelper
//{
//	uint16 stringItemId;
//	uint16 cacheFileId;
//};
//
//SwordHelper swordHelper[] =
//{
//	{ 0 , plwp_sword  },
//	{ 15, plwp_sword2 },
//	{ 16, plwp_sword3 },
//};

// @Todo: Array, sheesh.

//typedef byte8 *(* RegisterWeapon_t)(byte8 *);
//
//RegisterWeapon_t RegisterWeaponRebellion       = 0;
//RegisterWeapon_t RegisterWeaponCerberus        = 0;
//RegisterWeapon_t RegisterWeaponAgniRudra       = 0;
//RegisterWeapon_t RegisterWeaponNevan           = 0;
//RegisterWeapon_t RegisterWeaponBeowulf         = 0;
//RegisterWeapon_t RegisterWeaponYamato          = 0;
//RegisterWeapon_t RegisterWeaponYamatoBob       = 0;
//RegisterWeapon_t RegisterWeaponEbonyIvory      = 0;
//RegisterWeapon_t RegisterWeaponShotgun         = 0;
//RegisterWeapon_t RegisterWeaponArtemis         = 0;
//RegisterWeapon_t RegisterWeaponSpiral          = 0;
//RegisterWeapon_t RegisterWeaponKalinaAnn       = 0;
//RegisterWeapon_t RegisterWeaponKalinaAnnLady   = 0;
//RegisterWeapon_t RegisterWeaponForceEdge       = 0;
//RegisterWeapon_t RegisterWeaponNeroAngeloSword = 0;
//
//struct RegisterWeaponHelper
//{
//	RegisterWeapon_t * func;
//	uint8 id;
//};
//
//RegisterWeaponHelper registerWeaponHelperDante[] =
//{
//	{ &RegisterWeaponRebellion , WEAPON_REBELLION   },
//	{ &RegisterWeaponCerberus  , WEAPON_CERBERUS    },
//	{ &RegisterWeaponAgniRudra , WEAPON_AGNI_RUDRA  },
//	{ &RegisterWeaponNevan     , WEAPON_NEVAN       },
//	{ &RegisterWeaponBeowulf   , WEAPON_BEOWULF     },
//	{ &RegisterWeaponEbonyIvory, WEAPON_EBONY_IVORY },
//	{ &RegisterWeaponShotgun   , WEAPON_SHOTGUN     },
//	{ &RegisterWeaponArtemis   , WEAPON_ARTEMIS     },
//	{ &RegisterWeaponSpiral    , WEAPON_SPIRAL      },
//	{ &RegisterWeaponKalinaAnn , WEAPON_KALINA_ANN  },
//};
//
//RegisterWeaponHelper registerWeaponHelperBob[] =
//{
//	{ &RegisterWeaponYamatoBob, WEAPON_YAMATO_BOB },
//};
//
//RegisterWeaponHelper registerWeaponHelperLady[] =
//{
//	{ &RegisterWeaponKalinaAnn    , WEAPON_KALINA_ANN      },
//	{ &RegisterWeaponKalinaAnnLady, WEAPON_KALINA_ANN_LADY },
//};
//
//RegisterWeaponHelper registerWeaponHelperVergil[] =
//{
//	{ &RegisterWeaponYamato   , WEAPON_YAMATO         },
//	{ &RegisterWeaponBeowulf  , WEAPON_BEOWULF_VERGIL },
//	{ &RegisterWeaponForceEdge, WEAPON_FORCE_EDGE     },
//};
//
//RegisterWeaponHelper * registerWeaponHelper[] =
//{
//	registerWeaponHelperDante,
//	registerWeaponHelperBob,
//	registerWeaponHelperLady,
//	registerWeaponHelperVergil,
//};
//
//uint8 registerWeaponHelperCount[] =
//{
//	countof(registerWeaponHelperDante),
//	countof(registerWeaponHelperBob),
//	countof(registerWeaponHelperLady),
//	countof(registerWeaponHelperVergil),
//};

byte8 * UpdateWeaponProxy = 0;

byte8 * CycleDante  = 0;
byte8 * CycleVergil = 0;

//uint8 Dante_Melee_lastWeaponId[MAX_ACTOR] = {};

byte8 * IsWeaponReadyProxy     = 0;
byte8 * IsWeaponReadyRebellion = 0;
byte8 * IsWeaponReadyCerberus  = 0;
byte8 * IsWeaponReadyAgniRudra = 0;
byte8 * IsWeaponReadyNevan     = 0;
byte8 * IsWeaponReadyBeowulf   = 0;
byte8 * IsWeaponReadyArtemis   = 0;

byte8 * Dante_Melee_SetWeaponProxy  = 0;
byte8 * Dante_Ranged_SetWeaponProxy = 0;

//void Dante_UpdateSword(byte8 * baseAddr)
//{
//	//auto data = fileItemHelperDante;
//	uint8 sword = 0;
//
//	bool unlockDevilTrigger = *(bool *)(appBaseAddr + 0xC8F250 + 0xD1);
//	uint8 costume = *(uint8 *)(baseAddr + 0x3E9E);
//
//	// @Todo: Should be in Cosmetics.
//
//	if (Config.Game.WeaponSwitcher.enable && (Config.Game.WeaponSwitcher.sword != 0))
//	{
//		sword = (Config.Game.WeaponSwitcher.sword - 1);
//	}
//	else
//	{
//		if (unlockDevilTrigger)
//		{
//			sword = 1;
//		}
//		switch (costume)
//		{
//		case LOGIC_COSTUME_DANTE_DMC1:
//		case LOGIC_COSTUME_DANTE_DMC1_COATLESS:
//		case LOGIC_COSTUME_DANTE_SPARDA:
//		case LOGIC_COSTUME_DANTE_SPARDA_INFINITE_MP:
//			sword = 2;
//			break;
//		}
//	}
//
//	fileItemHelperDante[0].stringItemId = swordHelper[sword].stringItemId;
//	fileItemHelperDante[0].cacheFileId  = swordHelper[sword].cacheFileId;
//}

PrivateEnd;

void System_Weapon_Dante_Ranged_UpdateLevels(byte8 * baseAddr)
{
	uint8  * weapon = (uint8  *)(baseAddr + 0x649A);
	uint32 * level  = (uint32 *)(baseAddr + 0x64E4);

	byte * addr = *(byte **)(appBaseAddr + 0xC90E30);
	if (!addr)
	{
		return;
	}
	uint32 * sessionLevel = (uint32 *)(addr + 0xDC);

	for (uint8 slot = 0; slot < 2; slot++)
	{
		uint8 weaponId = weapon[slot];
		if (weaponId == 0xFF)
		{
			level[slot] = 0;
			continue;
		}
		weaponId -= 5;
		level[slot] = sessionLevel[weaponId];
	}
}

PrivateStart;

//__declspec(deprecated) void UpdateWeapon(byte8 * baseAddr)
//{
//	Log("%s Start %llX", FUNC_NAME, baseAddr);
//
//	//auto actor = System_Actor_GetActorId(baseAddr);
//
//
//	auto & actorData = *(ACTOR_DATA *)baseAddr;
//
//	//auto actor = actorData.actorId;
//
//
//
//
//
//	auto   character            = *(uint8 * )(baseAddr + 0x78  );
//	auto & specialCostume       = *(bool  * )(baseAddr + 0x3E9F);
//	auto & selectedMeleeWeapon  = *(uint8 * )(baseAddr + 0x6490);
//	auto & selectedRangedWeapon = *(uint8 * )(baseAddr + 0x6494);
//	auto   equipment            =  (uint8 * )(baseAddr + 0x6498);
//	auto   metadata             =  (byte8 **)(baseAddr + 0x64A0);
//
//	//if (character >= MAX_CHAR_LOGIC)
//	//{
//	//	character = 0;
//	//}
//
//	//// Update File Items
//	//{
//	//	if (character == CHAR_DANTE)
//	//	{
//	//		Dante_UpdateSword(baseAddr);
//	//	}
//	//	auto & count = fileItemHelperCount[character];
//	//	for (uint8 index = 0; index < count; index++)
//	//	{
//	//		fileItemHelper[character][index].Update();
//	//	}
//	//}
//
//	// Register Weapons
//	//{
//	//	auto & count = registerWeaponHelperCount[character];
//	//	for (uint8 index = 0; index < count; index++)
//	//	{
//	//		auto & RegisterWeapon = *registerWeaponHelper[character][index].func;
//	//		auto & id = registerWeaponHelper[character][index].id;
//	//		System_Weapon_weaponMetadata[actor][id] = RegisterWeapon(baseAddr);
//	//	}
//	//	if ((character == CHAR_VERGIL) && specialCostume)
//	//	{
//	//		RegisterWeaponNeroAngeloSword(baseAddr);
//	//	}
//	//}
//
//	// Update Live Variables
//	{
//		if ((character == CHAR_DANTE) && Config.Game.WeaponSwitcher.enable)
//		{
//
//			// @Todo: Should be 8 due to padding.
//			// @Research: Extension.
//
//			memset(equipment, 0xFF, 4);
//			memset((equipment + 4), 0, 4);
//			equipment[selectedMeleeWeapon ] = Config.Game.WeaponSwitcher.Melee.weapon [Game_WeaponSwitcher_Melee_index ];
//			equipment[selectedRangedWeapon] = Config.Game.WeaponSwitcher.Ranged.weapon[Game_WeaponSwitcher_Ranged_index];
//		}
//
//		memset(metadata, 0, 100);
//		for (uint8 index = 0; index < 4; index++)
//		{
//			uint8 & weaponId = equipment[index];
//			if (weaponId == 0xFF)
//			{
//				continue;
//			}
//			metadata[index] = System_Weapon_weaponMetadata[actor][weaponId];
//		}
//
//		// @Research: Different for Vergil!
//
//		*(uint32 *)(baseAddr + 0x64D8) = 4;
//
//		if (character == CHAR_DANTE)
//		{
//			System_Weapon_Dante_Ranged_UpdateLevels(baseAddr);
//			System_Weapon_Dante_UpdateExpertise(baseAddr);
//			auto & weaponId = equipment[selectedMeleeWeapon];
//			auto & lastWeaponId = Dante_Melee_lastWeaponId[actor];
//			lastWeaponId = weaponId;
//			if ((weaponId == WEAPON_DANTE_BEOWULF) && !Config.Cosmetics.Dante.Beowulf.hideModel)
//			{
//				Cosmetics_Dante_ApplyBeowulfModelAttributes(baseAddr);
//			}
//			else
//			{
//				Cosmetics_Dante_ApplyDefaultModelAttributes(baseAddr);
//			}
//		}
//	}
//	LogFunctionEnd();
//}

//void Dante_Melee_UpdateModelAttributes(byte8 * baseAddr, uint8 weaponId)
//{
//	auto & actorData = *(ACTOR_DATA *)baseAddr;
//	auto actor = actorData.actorId;
//
//	auto & lastWeaponId = Dante_Melee_lastWeaponId[actor];
//	if (lastWeaponId != weaponId)
//	{
//		lastWeaponId = weaponId;
//		if ((weaponId == WEAPON_DANTE_BEOWULF) && !Config.Cosmetics.Dante.Beowulf.hideModel)
//		{
//			Cosmetics_Dante_ApplyBeowulfModelAttributes(baseAddr);
//		}
//		else
//		{
//			Cosmetics_Dante_ApplyDefaultModelAttributes(baseAddr);
//		}
//	}
//}

// @Todo: Remove weaponId. It's not required, the weaponBaseAddr should have it at 0x18.

// @Research: IsReady is ambiguous.
// IsActive
// ShouldShow
// Show
// CondShow
// IsActive
// IsBusy
// ShowModel
// GetDisplayState






__declspec(deprecated) bool Dante_Melee_IsWeaponReady(byte8 * baseAddr, uint8 weaponId)
{
	auto actorBaseAddr = *(byte8 **)(baseAddr + 0x120);
	if (!actorBaseAddr)
	{
		return false;
	}

	auto & character      = *(uint8  *)(actorBaseAddr + 0x78  );
	auto & motionGroup    = *(uint8  *)(actorBaseAddr + 0x39B3);
	auto & actorModel     = *(uint32 *)(actorBaseAddr + 0x3E6C);
	auto & selectedWeapon = *(uint8  *)(actorBaseAddr + 0x6490);
	auto   equipment      =  (uint8  *)(actorBaseAddr + 0x6498);

	if (weaponId == WEAPON_DANTE_BEOWULF)
	{
		if (character == CHAR_VERGIL)
		{
			return true;
		}
		if (actorModel)
		{
			if (Config.Game.WeaponSwitcher.enable && (Config.Game.WeaponSwitcher.devil == DEVIL_DANTE_BEOWULF))
			{
				return true;
			}
			// @Todo: Ignore equipment check. Rather change to devil model check.
			uint8 index = (uint8)(actorModel - 1);
			if (equipment[index] == WEAPON_DANTE_BEOWULF)
			{
				return true;
			}
		}
	}

	uint8 motionGroupId[] =
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
	uint8 off = MOT_DANTE_REBELLION;
	for (uint8 index = 0; index < countof(motionGroupId); index++)
	{
		if (index == 5)
		{
			off = MOT_DANTE_SWORDMASTER_REBELLION;
		}
		if (motionGroup == (weaponId + off))
		{
			//Dante_Melee_UpdateModelAttributes(actorBaseAddr, weaponId);
			return true;
		}
		else if (motionGroup == motionGroupId[index])
		{
			return false;
		}
	}

	if (equipment[selectedWeapon] == weaponId)
	{
		//Dante_Melee_UpdateModelAttributes(actorBaseAddr, weaponId);
		return true;
	}

	return false;
}

bool IsWeaponActive(byte8 * baseAddr, uint8 weapon)
{
	auto & actorData = *(ACTOR_DATA *)baseAddr;
	if (actorData.motionData[1].group == (MOT_DANTE_REBELLION + weapon))
	{
		return true;
	}
	if (actorData.motionData[1].group == (MOT_DANTE_SWORDMASTER_REBELLION + weapon))
	{
		return true;
	}
	return false;
}

//void func(uint8 weapon)
//{
//
//
//
//
//	for (uint8 index = 0; index < MAX_WEAPON_DANTE; index++)
//	{
//		if (index == weapon)
//		{
//			continue;
//		}
//
//		IsWeaponActive(0, weapon);
//
//
//
//
//
//	}
//}




























// @Todo: Update!

__declspec(deprecated) bool Dante_Ranged_IsWeaponReady(byte8 * baseAddr, uint8 weaponId)
{
	auto actorBaseAddr = *(byte8 **)(baseAddr + 0x120);
	if (!actorBaseAddr)
	{
		return false;
	}

	auto & motionGroup    = *(uint8  *)(actorBaseAddr + 0x39B3);
	auto & selectedWeapon = *(uint8  *)(actorBaseAddr + 0x6494);
	auto   equipment      =  (uint8  *)(actorBaseAddr + 0x6498);

	uint8 motionGroupId[] =
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
	uint8 off = MOT_DANTE_REBELLION;
	for (uint8 index = 0; index < countof(motionGroupId); index++)
	{
		if (index == 5)
		{
			off = MOT_DANTE_SWORDMASTER_REBELLION;
		}
		if (motionGroup == (weaponId + off))
		{
			return true;
		}
		else if (motionGroup == motionGroupId[index])
		{
			return false;
		}
	}

	if (equipment[selectedWeapon] == weaponId)
	{
		return true;
	}

	return false;
}

void Dante_Melee_SetWeapon(byte8 * baseAddr)
{
	auto & selectedWeapon = *(uint8 *)(baseAddr + 0x6490);
	auto   equipment      =  (uint8 *)(baseAddr + 0x6498);
	auto & model          = *(uint8 *)(baseAddr + 0x64F0);
	model = equipment[selectedWeapon];

	//auto & active = *(uint8 *)(baseAddr + 0x3E6C);
	//auto & queue  = *(uint8 *)(baseAddr + 0x3E70);

	//uint32 slot = 0;

	//if (active == 1)
	//{
	//	slot = 2;
	//	DanteLady(baseAddr, slot);
	//	//queue = 2;
	//}
	//if (active == 2)
	//{
	//	slot = 1;
	//	DanteLady(baseAddr, slot);	
	//	//queue = 1;
	//}
	
}

void Dante_Ranged_SetWeapon(byte8 * baseAddr)
{
	auto & selectedWeapon = *(uint8 *)(baseAddr + 0x6494);
	auto   equipment      =  (uint8 *)(baseAddr + 0x6498);
	auto & model          = *(uint8 *)(baseAddr + 0x64F1);
	model = equipment[selectedWeapon];
}

PrivateEnd;

void System_Weapon_Init()
{
	LogFunction();
	//{
	//	RegisterWeapon_t * addr[] =
	//	{
	//		&RegisterWeaponRebellion,
	//		&RegisterWeaponCerberus,
	//		&RegisterWeaponAgniRudra,
	//		&RegisterWeaponNevan,
	//		&RegisterWeaponBeowulf,
	//		&RegisterWeaponYamato,
	//		&RegisterWeaponYamatoBob,
	//		&RegisterWeaponEbonyIvory,
	//		&RegisterWeaponShotgun,
	//		&RegisterWeaponArtemis,
	//		&RegisterWeaponSpiral,
	//		&RegisterWeaponForceEdge,
	//		&RegisterWeaponNeroAngeloSword,
	//	};
	//	byte8 * funcAddr[] =
	//	{
	//		(appBaseAddr + 0x2310B0), // Rebellion
	//		(appBaseAddr + 0x22EC90), // Cerberus
	//		(appBaseAddr + 0x227870), // Agni & Rudra
	//		(appBaseAddr + 0x22A1E0), // Nevan
	//		(appBaseAddr + 0x228CF0), // Beowulf
	//		(appBaseAddr + 0x22B0C0), // Ebony & Ivory
	//		(appBaseAddr + 0x2306B0), // Shotgun
	//		(appBaseAddr + 0x22C4A0), // Artemis
	//		(appBaseAddr + 0x2300A0), // Spiral

	//		(appBaseAddr + 0x231A30), // Yamato Bob

	//		(appBaseAddr + 0x22D960), // Yamato
	//		(appBaseAddr + 0x2298E0), // Force Edge
	//		(appBaseAddr + 0x22CF00), // Nero Angelo Sword
	//	};
	//	byte8 sect1[] =
	//	{
	//		0x33, 0xD2, //xor edx,edx
	//	};
	//	for (uint8 index = 0; index < countof(addr); index++)
	//	{
	//		FUNC func = CreateFunction(funcAddr[index], 0, true, false, 0, sizeof(sect1));
	//		memcpy(func.sect1, sect1, sizeof(sect1));
	//		*addr[index] = (RegisterWeapon_t)func.addr;
	//	}
	//	{
	//		byte8 sect1[] =
	//		{
	//			0x33, 0xD2, //xor edx,edx
	//			0xB2, 0x09, //mov dl,09
	//		};
	//		FUNC func = CreateFunction((appBaseAddr + 0x22BA30), 0, true, false, 0, sizeof(sect1));
	//		memcpy(func.sect1, sect1, sizeof(sect1));
	//		RegisterWeaponKalinaAnn = (RegisterWeapon_t)func.addr;
	//	}
	//	{
	//		byte8 sect1[] =
	//		{
	//			0x33, 0xD2, //xor edx,edx
	//			0xB2, 0x0A, //mov dl,0A
	//		};
	//		FUNC func = CreateFunction((appBaseAddr + 0x22BA30), 0, true, false, 0, sizeof(sect1));
	//		memcpy(func.sect1, sect1, sizeof(sect1));
	//		RegisterWeaponKalinaAnnLady = (RegisterWeapon_t)func.addr;
	//	}
	//}
	//{
	//	FUNC func = CreateFunction((appBaseAddr + 0x212A90));
	//	System_Weapon_Dante_UpdateExpertise = (System_Weapon_Dante_UpdateExpertise_t)func.addr;
	//}
	//{
	//	FUNC func = CreateFunction(UpdateWeapon, (appBaseAddr + 0x1DF2D2));
	//	UpdateWeaponProxy = func.addr;
	//}
	//{
	//	byte8 sect0[] =
	//	{
	//		0x8A, 0x87, 0x18, 0x01, 0x00, 0x00, //mov al,[rdi+00000118]
	//		0x84, 0xC0,                         //test al,al
	//		0x75, 0x05,                         //jne short
	//		0xE9, 0x00, 0x00, 0x00, 0x00,       //jmp dmc3.exe+280120
	//	};
	//	FUNC func = CreateFunction(0, 0, false, true, sizeof(sect0));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	WriteJump((func.sect0 + 0xA), (appBaseAddr + 0x280120));
	//	CycleDante = func.addr;
	//}
	//{
	//	byte8 sect0[] =
	//	{
	//		0x8A, 0x83, 0x18, 0x01, 0x00, 0x00, //mov al,[rbx+00000118]
	//		0x84, 0xC0,                         //test al,al
	//		0x75, 0x05,                         //jne short
	//		0xE9, 0x00, 0x00, 0x00, 0x00,       //jmp dmc3.exe+280160
	//	};
	//	FUNC func = CreateFunction(0, 0, false, true, sizeof(sect0));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	WriteJump((func.sect0 + 0xA), (appBaseAddr + 0x280160));
	//	CycleVergil = func.addr;
	//}
	//{
	//	byte8 ** addr[] =
	//	{
	//		&IsWeaponReadyRebellion,
	//		&IsWeaponReadyCerberus,
	//		&IsWeaponReadyAgniRudra,
	//		&IsWeaponReadyNevan,
	//	};
	//	byte8 * jumpAddr[] =
	//	{
	//		(appBaseAddr + 0x231633),
	//		(appBaseAddr + 0x22FAD9),
	//		(appBaseAddr + 0x2288A9),
	//		(appBaseAddr + 0x22AD32),
	//	};
	//	byte8 sect1[] =
	//	{
	//		0xB2, 0x00, //mov dl
	//	};
	//	for (uint8 index = 0; index < countof(addr); index++)
	//	{
	//		FUNC func = CreateFunction(Dante_Melee_IsWeaponReady, jumpAddr[index], true, false, 0, sizeof(sect1));
	//		memcpy(func.sect1, sect1, sizeof(sect1));
	//		*(uint8 *)(func.sect1 + 1) = index;
	//		*addr[index] = func.addr;
	//	}
	//}
	//{
	//	byte8 sect1[] =
	//	{
	//		0xB2, 0x00, //mov dl
	//	};
	//	byte8 sect2[] =
	//	{
	//		0x84, 0xC0,                   //test al,al
	//		0x74, 0x05,                   //je short
	//		0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc3.exe+1FDE10
	//	};
	//	FUNC func = CreateFunction(Dante_Melee_IsWeaponReady, (appBaseAddr + 0x2295BC), true, false, 0, sizeof(sect1), sizeof(sect2));
	//	memcpy(func.sect1, sect1, sizeof(sect1));
	//	memcpy(func.sect2, sect2, sizeof(sect2));
	//	*(uint8 *)(func.sect1 + 1) = WEAPON_BEOWULF;
	//	WriteCall((func.sect2 + 4), (appBaseAddr + 0x1FDE10));
	//	IsWeaponReadyBeowulf = func.addr;
	//}
	//{
	//	byte8 sect1[] =
	//	{
	//		0xB2, 0x00, //mov dl
	//	};
	//	byte8 sect2[] =
	//	{
	//		0x84, 0xC0,                   //test al,al
	//		0x74, 0x05,                   //je short
	//		0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc3.exe+1FDE10
	//	};
	//	FUNC func = CreateFunction(Dante_Ranged_IsWeaponReady, (appBaseAddr + 0x22CBCD), true, false, 0, sizeof(sect1), sizeof(sect2));
	//	memcpy(func.sect1, sect1, sizeof(sect1));
	//	memcpy(func.sect2, sect2, sizeof(sect2));
	//	*(uint8 *)(func.sect1 + 1) = WEAPON_ARTEMIS;
	//	WriteCall((func.sect2 + 4), (appBaseAddr + 0x1FDE10));
	//	IsWeaponReadyArtemis = func.addr;
	//}
	//{
	//	byte8 sect0[] =
	//	{
	//		0x89, 0x9F, 0x90, 0x64, 0x00, 0x00, //mov [rdi+00006490],ebx

	//	};
	//	byte8 sect1[] =
	//	{
	//		0x48, 0x8B, 0xCF, //mov rcx,rdi
	//	};
	//	FUNC func = CreateFunction(Dante_Melee_SetWeapon, (appBaseAddr + 0x1EA9E4), true, true, sizeof(sect0), sizeof(sect1));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	memcpy(func.sect1, sect1, sizeof(sect1));
	//	Dante_Melee_SetWeaponProxy = func.addr;
	//}
	//{
	//	byte8 sect0[] =
	//	{
	//		0x89, 0x9F, 0x94, 0x64, 0x00, 0x00, //mov [rdi+00006494],ebx
	//	};
	//	byte8 sect1[] =
	//	{
	//		0x48, 0x8B, 0xCF, //mov rcx,rdi
	//	};
	//	FUNC func = CreateFunction(Dante_Ranged_SetWeapon, (appBaseAddr + 0x1EAAD1), true, true, sizeof(sect0), sizeof(sect1));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	memcpy(func.sect1, sect1, sizeof(sect1));
	//	Dante_Ranged_SetWeaponProxy = func.addr;
	//}
}

void System_Weapon_ToggleUpdateWeapon(bool enable)
{
	LogFunction(enable);
	System_Weapon_enableUpdateWeapon = enable;
	if (enable)
	{
		WriteJump((appBaseAddr + 0x1DF2CD), UpdateWeaponProxy);
	}
	else
	{
		WriteCall((appBaseAddr + 0x1DF2CD), (appBaseAddr + 0x1DED20));
	}
}

void System_Weapon_ToggleDoppelgangerFixes(bool enable)
{
	LogFunction(enable);
	System_Weapon_enableDoppelgangerFixes = enable;
	if (enable)
	{
		// Add actor id check to weapon cycle functions.
		WriteCall((appBaseAddr + 0x1EA9D4), CycleDante ); // Melee
		WriteCall((appBaseAddr + 0x1EAAC1), CycleDante ); // Ranged
		WriteCall((appBaseAddr + 0x1E6EF3), CycleVergil); // Forward
		WriteCall((appBaseAddr + 0x1E6FE5), CycleVergil); // Backward
	}
	else
	{
		WriteCall((appBaseAddr + 0x1EA9D4), (appBaseAddr + 0x280120));
		WriteCall((appBaseAddr + 0x1EAAC1), (appBaseAddr + 0x280120));
		WriteCall((appBaseAddr + 0x1E6EF3), (appBaseAddr + 0x280160));
		WriteCall((appBaseAddr + 0x1E6FE5), (appBaseAddr + 0x280160));
	}
}

void System_Weapon_ToggleModelFixes(bool enable)
{
	LogFunction(enable);
	System_Weapon_enableModelFixes = enable;
	if (enable)
	{
		WriteJump((appBaseAddr + 0x23162E), IsWeaponReadyRebellion);
		WriteJump((appBaseAddr + 0x22FAD4), IsWeaponReadyCerberus);
		WriteJump((appBaseAddr + 0x2288A4), IsWeaponReadyAgniRudra);
		WriteJump((appBaseAddr + 0x22AD2D), IsWeaponReadyNevan);
		WriteJump((appBaseAddr + 0x2295B7), IsWeaponReadyBeowulf);
		WriteJump((appBaseAddr + 0x22CBC8), IsWeaponReadyArtemis);
		WriteJump((appBaseAddr + 0x1EA9DE), Dante_Melee_SetWeaponProxy, 1);
		WriteJump((appBaseAddr + 0x1EAACB), Dante_Ranged_SetWeaponProxy, 1);
		WriteAddress((appBaseAddr + 0x2292E0), (appBaseAddr + 0x2292E6), 6); // Disable equipment check.
	}
	else
	{
		WriteCall((appBaseAddr + 0x23162E), (appBaseAddr + 0x1FD3E0));
		WriteCall((appBaseAddr + 0x22FAD4), (appBaseAddr + 0x1FD3E0));
		WriteCall((appBaseAddr + 0x2288A4), (appBaseAddr + 0x1FD3E0));
		WriteCall((appBaseAddr + 0x22AD2D), (appBaseAddr + 0x1FD3E0));

		WriteCall((appBaseAddr + 0x2295B7), (appBaseAddr + 0x1FDE10));
		WriteCall((appBaseAddr + 0x22CBC8), (appBaseAddr + 0x1FDE10));
		{
			byte8 buffer[] =
			{
				0x89, 0x9F, 0x90, 0x64, 0x00, 0x00, //mov [rdi+00006490],ebx
			};
			vp_memcpy((appBaseAddr + 0x1EA9DE), buffer, sizeof(buffer));
		}
		{
			byte8 buffer[] =
			{
				0x89, 0x9F, 0x94, 0x64, 0x00, 0x00, //mov [rdi+00006494],ebx
			};
			vp_memcpy((appBaseAddr + 0x1EAACB), buffer, sizeof(buffer));
		}
		WriteAddress((appBaseAddr + 0x2292E0), (appBaseAddr + 0x2295C1), 6);
	}
}
