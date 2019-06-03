#include "Weapon.h"

bool System_Weapon_enable = false;
BYTE * weaponMetadata[MAX_ACTOR][MAX_WEAPON] = {};
bool System_Weapon_Ranged_resetLevel = false;
extern uint8 Game_WeaponSwitcher_Melee_index;
extern uint8 Game_WeaponSwitcher_Ranged_index;

typedef BYTE *(* RegisterWeapon_t)(BYTE *);

BYTE * UpdateWeaponProxy = 0;
RegisterWeapon_t RegisterRebellion       = 0;
RegisterWeapon_t RegisterCerberus        = 0;
RegisterWeapon_t RegisterAgniRudra       = 0;
RegisterWeapon_t RegisterNevan           = 0;
RegisterWeapon_t RegisterBeowulf         = 0;
RegisterWeapon_t RegisterYamato          = 0;
RegisterWeapon_t RegisterYamatoBob       = 0;
RegisterWeapon_t RegisterEbonyIvory      = 0;
RegisterWeapon_t RegisterShotgun         = 0;
RegisterWeapon_t RegisterArtemis         = 0;
RegisterWeapon_t RegisterSpiral          = 0;
RegisterWeapon_t RegisterKalinaAnn       = 0;
RegisterWeapon_t RegisterKalinaAnnLady   = 0;
RegisterWeapon_t RegisterForceEdge       = 0;
RegisterWeapon_t RegisterNeroAngeloSword = 0;

void System_Weapon_Ranged_UpdateLevels(BYTE * baseAddr)
{
	uint8 * weapon = (uint8 *)(baseAddr + 0x649A);
	uint32 * level = (uint32 *)(baseAddr + 0x64E4);
	BYTE * addr = *(BYTE **)(appBaseAddr + 0xC90E30);
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

static void UpdateWeapon(BYTE * baseAddr)
{
	

	Log("%s %llX", FUNC_NAME, baseAddr);



	uint8 character = *(uint8 *)(baseAddr + 0x78);
	if (character >= MAX_CHAR)
	{
		character = 0;
	}
	uint8 actor = GetActorId(baseAddr);

	Log("actorId %u", actor);


	Log("reached here");




	// Update File Structs
	{
		BYTE * structAddr[MAX_CHAR][MAX_WEAPON] =
		{
			{                                      // Dante
				(appBaseAddr + 0xC99D30 + 0x2760), // Rebellion
				(appBaseAddr + 0xC99D30 + 0x27A8), // Cerberus
				(appBaseAddr + 0xC99D30 + 0x27F0), // Agni & Rudra
				(appBaseAddr + 0xC99D30 + 0x2838), // Nevan
				(appBaseAddr + 0xC99D30 + 0x2880), // Beowulf
				(appBaseAddr + 0xC99D30 + 0x28C8), // Ebony & Ivory
				(appBaseAddr + 0xC99D30 + 0x2910), // Shotgun
				(appBaseAddr + 0xC99D30 + 0x2958), // Artemis
				(appBaseAddr + 0xC99D30 + 0x29A0), // Spiral
				(appBaseAddr + 0xC99D30 + 0x29E8), // Kalina Ann
			},
			{                                      // Bob
				(appBaseAddr + 0xC99D30 + 0x2F88), // Yamato
			},
			{                                      // Lady
				(appBaseAddr + 0xC99D30 + 0x3258), // obj\plwp_ladygun.pac
				(appBaseAddr + 0xC99D30 + 0x32A0), // obj\plwp_ladygun1.pac
			},
			{                                      // Vergil
				(appBaseAddr + 0xC99D30 + 0x3720), // Yamato
				(appBaseAddr + 0xC99D30 + 0x3528), // Beowulf
				(appBaseAddr + 0xC99D30 + 0x37B0), // Force Edge
				(appBaseAddr + 0xC99D30 + 0x3498), // Nero Angelo Sword
			},
		};
		BYTE * stringAddr[MAX_CHAR][MAX_WEAPON] =
		{
			{
				(appBaseAddr + 0x5B0F50), // obj\plwp_sword.pac
				(appBaseAddr + 0x5B0F60), // obj\plwp_nunchaku.pac
				(appBaseAddr + 0x5B0F70), // obj\plwp_2sword.pac
				(appBaseAddr + 0x5B0F80), // obj\plwp_guitar.pac
				(appBaseAddr + 0x5B0F90), // obj\plwp_fight.pac
				(appBaseAddr + 0x5B0FA0), // obj\plwp_gun.pac
				(appBaseAddr + 0x5B0FB0), // obj\plwp_shotgun.pac
				(appBaseAddr + 0x5B0FC0), // obj\plwp_laser.pac
				(appBaseAddr + 0x5B0FD0), // obj\plwp_rifle.pac
				(appBaseAddr + 0x5B0FE0), // obj\plwp_ladygun.pac
			},
			{
				(appBaseAddr + 0x5B1030), // obj\plwp_vergilsword.pac
			},
			{
				(appBaseAddr + 0x5B0FE0), // obj\plwp_ladygun.pac
				(appBaseAddr + 0x5B0FF0), // obj\plwp_ladygun1.pac
				(appBaseAddr + 0x5B1010), // obj\plwp_ladygun3.pac
				(appBaseAddr + 0x5B1080), // obj\plwp_grenade.pac
			},
			{
				(appBaseAddr + 0x5B1000), // obj\plwp_newvergilsword.pac
				(appBaseAddr + 0x5B1060), // obj\plwp_newvergilfight.pac
				(appBaseAddr + 0x5B1020), // obj\plwp_forceedge.pac
				(appBaseAddr + 0x5B1070), // obj\plwp_nerosword.pac
			},
		};
		BYTE * fileAddr[MAX_CHAR][MAX_WEAPON] =
		{
			{
				cacheFile[plwp_sword],
				cacheFile[plwp_nunchaku],
				cacheFile[plwp_2sword],
				cacheFile[plwp_guitar],
				cacheFile[plwp_fight],
				cacheFile[plwp_gun],
				cacheFile[plwp_shotgun],
				cacheFile[plwp_laser],
				cacheFile[plwp_rifle],
				cacheFile[plwp_ladygun],
			},
			{
				cacheFile[plwp_vergilsword],
			},
			{
				cacheFile[plwp_ladygun],
				cacheFile[plwp_ladygun1],
				cacheFile[plwp_ladygun3],
				cacheFile[plwp_grenade],
			},
			{
				cacheFile[plwp_newvergilsword],
				cacheFile[plwp_newvergilfight],
				cacheFile[plwp_forceedge],
				cacheFile[plwp_nerosword],
			},
		};
		// Set Sword
		if (character == CHAR_DANTE)
		{
			BYTE * swordStringAddr[] =
			{
				(appBaseAddr + 0x5B0F50), // obj\plwp_sword.pac
				(appBaseAddr + 0x5B1040), // obj\plwp_sword2.pac
				(appBaseAddr + 0x5B1050), // obj\plwp_sword3.pac
			};
			BYTE * swordFileAddr[] =
			{
				cacheFile[plwp_sword],
				cacheFile[plwp_sword2],
				cacheFile[plwp_sword3],
			};
			if (Config.Game.WeaponSwitcher.enable && (Config.Game.WeaponSwitcher.sword != 0))
			{
				stringAddr[CHAR_DANTE][0] = swordStringAddr[(Config.Game.WeaponSwitcher.sword - 1)];
				fileAddr[CHAR_DANTE][0] = swordFileAddr[(Config.Game.WeaponSwitcher.sword - 1)];
			}
			else
			{
				bool unlockDevilTrigger = *(bool *)(appBaseAddr + 0xC8F250 + 0xD1);
				if (unlockDevilTrigger)
				{
					stringAddr[CHAR_DANTE][0] = swordStringAddr[1];
					fileAddr[CHAR_DANTE][0] = swordFileAddr[1];
				}
				uint8 costume = *(uint8 *)(baseAddr + 0x3E9E);
				switch (costume)
				{
				case COSTUME_DANTE_DMC1:
				case COSTUME_DANTE_DMC1_COATLESS:
				case COSTUME_DANTE_SPARDA:
				case COSTUME_DANTE_SPARDA_INFINITE_MP:
					stringAddr[CHAR_DANTE][0] = swordStringAddr[2];
					fileAddr[CHAR_DANTE][0] = swordFileAddr[2];
					break;
				}
			}
		}
		uint8 count[] =
		{
			WEAPON_COUNT_DANTE,
			WEAPON_COUNT_BOB,
			WEAPON_COUNT_LADY,
			4,
		};
		for (uint8 i = 0; i < count[character]; i++)
		{
			memset(structAddr[character][i], 0, 0x48);
			uint32   & state  = *( uint32 *  )( structAddr[character][i] + 4    );
			BYTE   * & string = *( BYTE   ** )( structAddr[character][i] + 0x18 );
			BYTE   * & file   = *( BYTE   ** )( structAddr[character][i] + 0x20 );
			state  = 3;
			string = stringAddr[character][i];
			file   = fileAddr  [character][i];
		}

		Log("reached here memset");

	}
	// Register Weapons
	{
		memset(weaponMetadata[actor], 0, (MAX_WEAPON * 8));
		RegisterWeapon_t RegisterWeapon[MAX_CHAR][MAX_WEAPON] =
		{
			{
				RegisterRebellion,
				RegisterCerberus,
				RegisterAgniRudra,
				RegisterNevan,
				RegisterBeowulf,
				RegisterEbonyIvory,
				RegisterShotgun,
				RegisterArtemis,
				RegisterSpiral,
				RegisterKalinaAnn,
			},
			{
				RegisterYamatoBob,
			},
			{
				RegisterKalinaAnn,
				RegisterKalinaAnnLady,
			},
			{
				RegisterYamato,
				RegisterBeowulf,
				RegisterForceEdge,
			},
		};
		uint8 id[MAX_CHAR][MAX_WEAPON] =
		{
			{
				WEAPON_REBELLION,
				WEAPON_CERBERUS,
				WEAPON_AGNI_RUDRA,
				WEAPON_NEVAN,
				WEAPON_BEOWULF,
				WEAPON_EBONY_IVORY,
				WEAPON_SHOTGUN,
				WEAPON_ARTEMIS,
				WEAPON_SPIRAL,
				WEAPON_KALINA_ANN,
			},
			{
				WEAPON_YAMATO_BOB,
			},
			{
				WEAPON_KALINA_ANN,
				WEAPON_KALINA_ANN_LADY,
			},
			{
				WEAPON_YAMATO,
				WEAPON_BEOWULF_VERGIL,
				WEAPON_FORCE_EDGE,
			},
		};
		uint8 count[] =
		{
			WEAPON_COUNT_DANTE,
			WEAPON_COUNT_BOB,
			WEAPON_COUNT_LADY,
			WEAPON_COUNT_VERGIL,
		};
		for (uint8 i = 0; i < count[character]; i++)
		{
			weaponMetadata[actor][id[character][i]] = RegisterWeapon[character][i](baseAddr);
		}


		Log("reached here register");




		bool specialCostume = *(bool *)(baseAddr + 0x3E9F);
		if ((character == CHAR_VERGIL) && specialCostume)
		{
			RegisterNeroAngeloSword(baseAddr);
		}

		Log("reached here nero");


	}
	// Update Live Variables
	{
		if (Config.Game.WeaponSwitcher.enable && character == CHAR_DANTE)
		{
			memset((baseAddr + 0x6498), 0, 8);
			{
				uint8 * equipment = (uint8 *)(baseAddr + 0x6498);
				equipment[0] = 0xFF;
				equipment[1] = 0xFF;
				uint8 selectedWeapon = *(uint8 *)(baseAddr + 0x6490);
				equipment[selectedWeapon] = Config.Game.WeaponSwitcher.Melee.weapon[Game_WeaponSwitcher_Melee_index];
			}
			{
				uint8 * equipment = (uint8 *)(baseAddr + 0x649A);
				equipment[0] = 0xFF;
				equipment[1] = 0xFF;
				uint8 selectedWeapon = *(uint8 *)(baseAddr + 0x6494);
				selectedWeapon -= 2;
				equipment[selectedWeapon] = Config.Game.WeaponSwitcher.Ranged.weapon[Game_WeaponSwitcher_Ranged_index];
			}
		}




		

		memset((baseAddr + 0x64A0), 0, 0x64);
		uint8 * equipment = (uint8 *)(baseAddr + 0x6498);
		BYTE ** metaData = (BYTE **)(baseAddr + 0x64A0);
		for (uint8 i = 0; i < 4; i++)
		{
			if (equipment[i] == 0xFF)
			{
				continue;
			}
			metaData[i] = weaponMetadata[actor][equipment[i]];
		}
		*(uint32 *)(baseAddr + 0x64D8) = 4;



		
		//LogFunctionBool(enable);








		System_Weapon_Ranged_UpdateLevels(baseAddr);

		if (System_Weapon_Ranged_resetLevel)
		{
			uint32 * level = (uint32 *)(baseAddr + 0x64E4);
			level[0] = 0;
			level[1] = 1;
		}





		



		Log("reached here live update");







	}
	if (character == CHAR_DANTE)
	{
		UpdateExpertise(baseAddr);
	}

	

	Log("%s reached end!", FUNC_NAME);



}

void System_Weapon_Init()
{
	LogFunction();
	{
		RegisterWeapon_t * addr[] =
		{
			&RegisterRebellion,
			&RegisterCerberus,
			&RegisterAgniRudra,
			&RegisterNevan,
			&RegisterBeowulf,
			&RegisterYamato,
			&RegisterYamatoBob,
			&RegisterEbonyIvory,
			&RegisterShotgun,
			&RegisterArtemis,
			&RegisterSpiral,
			&RegisterForceEdge,
			&RegisterNeroAngeloSword,
		};
		BYTE * funcAddr[] =
		{
			(appBaseAddr + 0x2310B0), // Rebellion
			(appBaseAddr + 0x22EC90), // Cerberus
			(appBaseAddr + 0x227870), // Agni & Rudra
			(appBaseAddr + 0x22A1E0), // Nevan
			(appBaseAddr + 0x228CF0), // Beowulf
			(appBaseAddr + 0x22D960), // Yamato
			(appBaseAddr + 0x231A30), // Yamato Bob
			(appBaseAddr + 0x22B0C0), // Ebony & Ivory
			(appBaseAddr + 0x2306B0), // Shotgun
			(appBaseAddr + 0x22C4A0), // Artemis
			(appBaseAddr + 0x2300A0), // Spiral
			(appBaseAddr + 0x2298E0), // Force Edge
			(appBaseAddr + 0x22CF00), // Nero Angelo Sword
		};
		BYTE sect1[] =
		{
			0x33, 0xD2, //xor edx,edx
		};
		for (uint8 weapon = 0; weapon < countof(addr); weapon++)
		{
			FUNC func = CreateFunction(funcAddr[weapon], 0, true, false, 0, sizeof(sect1));
			memcpy(func.sect1, sect1, sizeof(sect1));
			*addr[weapon] = (RegisterWeapon_t)func.addr;
		}
		{
			BYTE sect1[] =
			{
				0x33, 0xD2, //xor edx,edx
				0xB2, 0x09, //mov dl,09
			};
			FUNC func = CreateFunction((appBaseAddr + 0x22BA30), 0, true, false, 0, sizeof(sect1));
			memcpy(func.sect1, sect1, sizeof(sect1));
			RegisterKalinaAnn = (RegisterWeapon_t)func.addr;
		}
		{
			BYTE sect1[] =
			{
				0x33, 0xD2, //xor edx,edx
				0xB2, 0x0A, //mov dl,0A
			};
			FUNC func = CreateFunction((appBaseAddr + 0x22BA30), 0, true, false, 0, sizeof(sect1));
			memcpy(func.sect1, sect1, sizeof(sect1));
			RegisterKalinaAnnLady = (RegisterWeapon_t)func.addr;
		}
	}
	{
		FUNC func = CreateFunction(UpdateWeapon, (appBaseAddr + 0x1DF2D2));
		UpdateWeaponProxy = func.addr;
	}
}

void System_Weapon_Toggle()
{
	System_Weapon_enable = MAGIC_6 ? true : false;
	Log("%s %u", FUNC_NAME, System_Weapon_enable);
	if (System_Weapon_enable)
	{
		WriteJump((appBaseAddr + 0x1DF2CD), UpdateWeaponProxy);
	}
	else
	{
		WriteCall((appBaseAddr + 0x1DF2CD), (appBaseAddr + 0x1DED20));
	}
}
