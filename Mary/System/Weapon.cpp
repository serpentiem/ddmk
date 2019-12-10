#include "Weapon.h"

bool System_Weapon_enableUpdateWeapon      = false;
bool System_Weapon_enableDoppelgangerFixes = false;

byte * weaponMetadata[MAX_ACTOR][MAX_WEAPON] = {};

extern uint8 Game_WeaponSwitcher_Melee_index;
extern uint8 Game_WeaponSwitcher_Ranged_index;

typedef byte *(* RegisterWeapon_t)(byte *);

byte * UpdateWeaponProxy = 0;

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

byte8 * CycleDante  = 0;
byte8 * CycleVergil = 0;

void System_Weapon_Ranged_UpdateLevels(byte * baseAddr)
{
	uint8 * weapon = (uint8 *)(baseAddr + 0x649A);
	uint32 * level = (uint32 *)(baseAddr + 0x64E4);
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

struct FileItemHelper
{
	uint16 fileItemId;
	uint16 stringItemId;
	uint16 cacheFileId;
	void Update()
	{
		FILE_ITEM   * fileItemAddr   = (FILE_ITEM   *)(appBaseAddr + 0xC99D30); // dmc3.exe+1DF696 - 48 8D 0D 93A6AB00 - lea rcx,[dmc3.exe+C99D30]
		STRING_ITEM * stringItemAddr = (STRING_ITEM *)(appBaseAddr + 0x5B0F50); // dmc3.exe+1B922E - 48 8D 05 5B7E3F00 - lea rax,[dmc3.exe+5B1090]

		FILE_ITEM   & fileItem   = fileItemAddr[fileItemId];
		STRING_ITEM & stringItem = stringItemAddr[stringItemId];

		memset(&fileItem, 0, sizeof(FILE_ITEM));

		fileItem.status     = FILE_ITEM_READY;
		fileItem.stringItem = &stringItem;
		fileItem.file       = cacheFile[cacheFileId];
	};
};

static FileItemHelper fileItemHelperDante[] =
{
	{ 140, 0, plwp_sword    },
	{ 141, 1, plwp_nunchaku },
	{ 142, 2, plwp_2sword   },
	{ 143, 3, plwp_guitar   },
	{ 144, 4, plwp_fight    },
	{ 145, 5, plwp_gun      },
	{ 146, 6, plwp_shotgun  },
	{ 147, 7, plwp_laser    },
	{ 148, 8, plwp_rifle    },
	{ 149, 9, plwp_ladygun  },
};

static FileItemHelper fileItemHelperBob[] =
{
	{ 169, 14, plwp_vergilsword },
};

static FileItemHelper fileItemHelperLady[] =
{
	{ 179, 9 , plwp_ladygun  },
	{ 180, 10, plwp_ladygun1 },
};

static FileItemHelper fileItemHelperVergil[] =
{
	{ 196, 11, plwp_newvergilsword },
	{ 189, 17, plwp_newvergilfight },
	{ 198, 13, plwp_forceedge      },
	{ 187, 18, plwp_nerosword      },
};

static FileItemHelper * fileItemHelper[] =
{
	fileItemHelperDante,
	fileItemHelperBob,
	fileItemHelperLady,
	fileItemHelperVergil,
};

static uint8 fileItemHelperCount[] =
{
	countof(fileItemHelperDante),
	countof(fileItemHelperBob),
	countof(fileItemHelperLady),
	countof(fileItemHelperVergil),
};

struct SwordHelper
{
	uint16 stringItemId;
	uint16 cacheFileId;
};

static SwordHelper swordHelper[] =
{
	{ 0 , plwp_sword  },
	{ 15, plwp_sword2 },
	{ 16, plwp_sword3 },
};

static void UpdateSword(byte8 * baseAddr)
{
	auto data = fileItemHelperDante;
	uint8 sword = 0;

	bool unlockDevilTrigger = *(bool *)(appBaseAddr + 0xC8F250 + 0xD1);
	uint8 costume = *(uint8 *)(baseAddr + 0x3E9E);

	if (Config.Game.WeaponSwitcher.enable && (Config.Game.WeaponSwitcher.sword != 0))
	{
		sword = (Config.Game.WeaponSwitcher.sword - 1);
	}
	else
	{
		if (unlockDevilTrigger)
		{
			sword = 1;
		}
		switch (costume)
		{
		case COSTUME_DANTE_DMC1:
		case COSTUME_DANTE_DMC1_COATLESS:
		case COSTUME_DANTE_SPARDA:
		case COSTUME_DANTE_SPARDA_INFINITE_MP:
			sword = 2;
			break;
		}
	}

	fileItemHelperDante[0].stringItemId = swordHelper[sword].stringItemId;
	fileItemHelperDante[0].cacheFileId  = swordHelper[sword].cacheFileId;
}

struct RegisterWeaponHelper
{
	RegisterWeapon_t * func;
	uint8 id;
};

static RegisterWeaponHelper registerWeaponHelperDante[] =
{
	{ &RegisterRebellion , WEAPON_REBELLION   },
	{ &RegisterCerberus  , WEAPON_CERBERUS    },
	{ &RegisterAgniRudra , WEAPON_AGNI_RUDRA  },
	{ &RegisterNevan     , WEAPON_NEVAN       },
	{ &RegisterBeowulf   , WEAPON_BEOWULF     },
	{ &RegisterEbonyIvory, WEAPON_EBONY_IVORY },
	{ &RegisterShotgun   , WEAPON_SHOTGUN     },
	{ &RegisterArtemis   , WEAPON_ARTEMIS     },
	{ &RegisterSpiral    , WEAPON_SPIRAL      },
	{ &RegisterKalinaAnn , WEAPON_KALINA_ANN  },
};

static RegisterWeaponHelper registerWeaponHelperBob[] =
{
	{ &RegisterYamatoBob, WEAPON_YAMATO_BOB },
};

static RegisterWeaponHelper registerWeaponHelperLady[] =
{
	{ &RegisterKalinaAnn    , WEAPON_KALINA_ANN      },
	{ &RegisterKalinaAnnLady, WEAPON_KALINA_ANN_LADY },
};

static RegisterWeaponHelper registerWeaponHelperVergil[] =
{
	{ &RegisterYamato   , WEAPON_YAMATO         },
	{ &RegisterBeowulf  , WEAPON_BEOWULF_VERGIL },
	{ &RegisterForceEdge, WEAPON_FORCE_EDGE     },
};

static RegisterWeaponHelper * registerWeaponHelper[] =
{
	registerWeaponHelperDante,
	registerWeaponHelperBob,
	registerWeaponHelperLady,
	registerWeaponHelperVergil,
};

static uint8 registerWeaponHelperCount[] =
{
	countof(registerWeaponHelperDante),
	countof(registerWeaponHelperBob),
	countof(registerWeaponHelperLady),
	countof(registerWeaponHelperVergil),
};

static void UpdateWeapon(byte8 * baseAddr)
{
	Log("%s %llX", FUNC_NAME, baseAddr);

	uint8 actor = GetActorId(baseAddr);

	uint8 character = *(uint8 *)(baseAddr + 0x78);
	if (character >= MAX_CHAR)
	{
		character = 0;
	}
	bool specialCostume = *(bool *)(baseAddr + 0x3E9F);

	// Update File Items
	{
		if (character == CHAR_DANTE)
		{
			UpdateSword(baseAddr);
		}
		auto & count = fileItemHelperCount[character];
		for (uint8 index = 0; index < count; index++)
		{
			fileItemHelper[character][index].Update();
		}
	}

	// Register Weapons
	{
		auto & count = registerWeaponHelperCount[character];
		for (uint8 index = 0; index < count; index++)
		{
			auto & RegisterWeapon = *registerWeaponHelper[character][index].func;
			auto & id = registerWeaponHelper[character][index].id;
			weaponMetadata[actor][id] = RegisterWeapon(baseAddr);
		}
		if ((character == CHAR_VERGIL) && specialCostume)
		{
			RegisterNeroAngeloSword(baseAddr);
		}
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
		byte ** metaData = (byte **)(baseAddr + 0x64A0);
		for (uint8 i = 0; i < 4; i++)
		{
			if (equipment[i] == 0xFF)
			{
				continue;
			}
			metaData[i] = weaponMetadata[actor][equipment[i]];
		}
		*(uint32 *)(baseAddr + 0x64D8) = 4;

		System_Weapon_Ranged_UpdateLevels(baseAddr);
	}

	if (character == CHAR_DANTE)
	{
		UpdateExpertise(baseAddr);
	}
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
		byte * funcAddr[] =
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
		byte sect1[] =
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
			byte sect1[] =
			{
				0x33, 0xD2, //xor edx,edx
				0xB2, 0x09, //mov dl,09
			};
			FUNC func = CreateFunction((appBaseAddr + 0x22BA30), 0, true, false, 0, sizeof(sect1));
			memcpy(func.sect1, sect1, sizeof(sect1));
			RegisterKalinaAnn = (RegisterWeapon_t)func.addr;
		}
		{
			byte sect1[] =
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
	{
		byte sect0[] =
		{
			0x8B, 0x87, 0x1C, 0x01, 0x00, 0x00, //mov eax,[rdi+0000011C]
			0x85, 0xC0,                         //test eax,eax
			0x75, 0x05,                         //jne short
			0xE9, 0x00, 0x00, 0x00, 0x00,       //jmp dmc3.exe+280120
		};
		FUNC func = CreateFunction(0, 0, false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteJump((func.sect0 + 0xA), (appBaseAddr + 0x280120));
		CycleDante = func.addr;
	}
	{
		byte sect0[] =
		{
			0x8B, 0x83, 0x1C, 0x01, 0x00, 0x00, //mov eax,[rbx+0000011C]
			0x85, 0xC0,                         //test eax,eax
			0x75, 0x05,                         //jne short
			0xE9, 0x00, 0x00, 0x00, 0x00,       //jmp dmc3.exe+280160
		};
		FUNC func = CreateFunction(0, 0, false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteJump((func.sect0 + 0xA), (appBaseAddr + 0x280160));
		CycleVergil = func.addr;
	}
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
		// Add Doppelganger check to weapon cycle functions.
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
