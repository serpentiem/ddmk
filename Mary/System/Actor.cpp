#include "Actor.h"

vector<byte8 *, 128> System_Actor_actorBaseAddr;

PrivateStart;

// @Todo: Create functions instead and add stringItemOff.

struct MotionHelper
{
	uint8 motionId;
	uint16 cacheFileId;
};

MotionHelper motionHelperDante[] =
{
	{ MOTION_GROUP_DANTE_BASE                  , pl000_00_0  },
	{ MOTION_GROUP_DANTE_DAMAGE                , pl000_00_1  },
	{ MOTION_GROUP_DANTE_TAUNTS                , pl000_00_2  },
	{ MOTION_GROUP_DANTE_REBELLION             , pl000_00_3  },
	{ MOTION_GROUP_DANTE_CERBERUS              , pl000_00_4  },
	{ MOTION_GROUP_DANTE_AGNI_RUDRA            , pl000_00_5  },
	{ MOTION_GROUP_DANTE_NEVAN                 , pl000_00_6  },
	{ MOTION_GROUP_DANTE_BEOWULF               , pl000_00_7  },
	{ MOTION_GROUP_DANTE_EBONY_IVORY           , pl000_00_8  },
	{ MOTION_GROUP_DANTE_SHOTGUN               , pl000_00_9  },
	{ MOTION_GROUP_DANTE_ARTEMIS               , pl000_00_10 },
	{ MOTION_GROUP_DANTE_SPIRAL                , pl000_00_11 },
	{ MOTION_GROUP_DANTE_KALINA_ANN            , pl000_00_12 },
	{ MOTION_GROUP_DANTE_SWORDMASTER_REBELLION , pl000_00_13 },
	{ MOTION_GROUP_DANTE_SWORDMASTER_CERBERUS  , pl000_00_14 },
	{ MOTION_GROUP_DANTE_SWORDMASTER_AGNI_RUDRA, pl000_00_15 },
	{ MOTION_GROUP_DANTE_SWORDMASTER_NEVAN     , pl000_00_16 },
	{ MOTION_GROUP_DANTE_SWORDMASTER_BEOWULF   , pl000_00_17 },
	{ MOTION_GROUP_DANTE_GUNSLINGER_EBONY_IVORY, pl000_00_18 },
	{ MOTION_GROUP_DANTE_GUNSLINGER_SHOTGUN    , pl000_00_19 },
	{ MOTION_GROUP_DANTE_GUNSLINGER_ARTEMIS    , pl000_00_20 },
	{ MOTION_GROUP_DANTE_GUNSLINGER_SPIRAL     , pl000_00_21 },
	{ MOTION_GROUP_DANTE_GUNSLINGER_KALINA_ANN , pl000_00_22 },
	{ MOTION_GROUP_DANTE_TRICKSTER             , pl000_00_23 },
	{ MOTION_GROUP_DANTE_ROYALGUARD            , pl000_00_24 },
	{ MOTION_GROUP_DANTE_QUICKSILVER           , pl000_00_25 },
	{ MOTION_GROUP_DANTE_DOPPELGANGER          , pl000_00_26 },
};

MotionHelper motionHelperBob[] =
{
	{ MOTION_GROUP_BOB_BASE       , pl001_00_0  },
	{ MOTION_GROUP_BOB_DAMAGE     , pl001_00_1  },
	{ MOTION_GROUP_BOB_TAUNTS     , pl001_00_2  },
	{ MOTION_GROUP_BOB_MELEE_STYLE, pl001_00_31 },
};

MotionHelper motionHelperLady[] =
{
	{ MOTION_GROUP_LADY_BASE      , pl002_00_0  },
	{ MOTION_GROUP_LADY_DAMAGE    , pl002_00_1  },
	{ MOTION_GROUP_LADY_TAUNTS    , pl002_00_2  },
	{ MOTION_GROUP_LADY_KALINA_ANN, pl000_00_12 },
};

MotionHelper motionHelperVergil[] =
{
	{ MOTION_GROUP_VERGIL_BASE                  , pl021_00_0 },
	{ MOTION_GROUP_VERGIL_DAMAGE                , pl021_00_1 },
	{ MOTION_GROUP_VERGIL_TAUNTS                , pl021_00_2 },
	{ MOTION_GROUP_VERGIL_YAMATO                , pl021_00_3 },
	{ MOTION_GROUP_VERGIL_BEOWULF               , pl021_00_4 },
	{ MOTION_GROUP_VERGIL_FORCE_EDGE            , pl021_00_5 },
	{ MOTION_GROUP_VERGIL_DARK_SLAYER           , pl021_00_6 },
	{ MOTION_GROUP_VERGIL_NERO_ANGELO_YAMATO    , pl021_00_7 },
	{ MOTION_GROUP_VERGIL_NERO_ANGELO_BEOWULF   , pl021_00_8 },
	{ MOTION_GROUP_VERGIL_NERO_ANGELO_FORCE_EDGE, pl021_00_9 },
};

PrivateEnd;







template <typename T>
bool IsWeaponActive
(
	T & actorData,
	uint8 weapon
)
{
	if constexpr (typematch(T, ACTOR_DATA_DANTE))
	{
		if (actorData.motionData[1].group == (MOTION_GROUP_DANTE_REBELLION + weapon))
		{
			return true;
		}
		if (actorData.motionData[1].group == (MOTION_GROUP_DANTE_SWORDMASTER_REBELLION + weapon))
		{
			return true;
		}
	}
	else if constexpr (typematch(T, ACTOR_DATA_VERGIL))
	{
		if (actorData.motionData[1].group == (MOTION_GROUP_VERGIL_YAMATO + weapon - WEAPON_VERGIL_YAMATO))
		{
			return true;
		}
	}
	return false;
}

template
<
	typename T,
	uint8 weaponType = WEAPON_TYPE_MELEE
>
bool IsWeaponReady
(
	T & actorData,
	uint8 weapon
)
{
	uint8 * weaponMap = 0;
	uint8 weaponCount = 0;
	uint8 weaponIndex = 0;

	if constexpr (typematch(T, ACTOR_DATA_DANTE))
	{
		if constexpr (weaponType == WEAPON_TYPE_MELEE)
		{
			weaponMap = actorData.weaponMap;
			weaponCount = 2;
			weaponIndex = actorData.weaponIndex[0];
		}
		else
		{
			weaponMap = reinterpret_cast<uint8 *>(&actorData.weaponMap[2]);
			weaponCount = 2;
			weaponIndex = (actorData.weaponIndex[1] - 2);
		}
	}
	else if constexpr (typematch(T, ACTOR_DATA_VERGIL))
	{
		weaponMap = actorData.weaponMap;
		weaponCount = 3;
		weaponIndex = actorData.weaponIndex[0];
	}

	if (IsWeaponActive<T>(actorData, weapon))
	{
		return true;
	}

	for (uint8 index = 0; index < weaponCount; index++)
	{
		if (weaponMap[index] == weapon)
		{
			continue;
		}
		if (IsWeaponActive<T>(actorData, weaponMap[index]))
		{
			return false;
		}
	}

	if (weaponMap[weaponIndex] == weapon)
	{
		return true;
	}

	return false;
}

void * IsMeleeWeaponReady[MAX_CHAR] =
{
	IsWeaponReady<ACTOR_DATA_DANTE>,
	0,
	0,
	IsWeaponReady<ACTOR_DATA_VERGIL>,
};

void * IsRangedWeaponReady[MAX_CHAR] =
{
	IsWeaponReady<ACTOR_DATA_DANTE, WEAPON_TYPE_RANGED>,
	0,
	0,
	0,
};

typedef bool(__fastcall * IsWeaponReady_t)
(
	ACTOR_DATA & actorData,
	uint8 weapon
);

template <uint8 weaponType = WEAPON_TYPE_MELEE>
bool IsWeaponReadyProxy(byte8 * baseAddr)
{
	auto & weapon = *reinterpret_cast<uint8 *>(baseAddr + 0x112);
	auto actorBaseAddr = *reinterpret_cast<byte8 **>(baseAddr + 0x120);
	if (!actorBaseAddr)
	{
		return true;
	}
	auto & actorData = *reinterpret_cast<ACTOR_DATA *>(actorBaseAddr);


	//auto character = actorData.character;
	//if (character >= MAX_CHAR)
	//{
	//	character = 0;
	//}


	IsWeaponReady_t func = 0;

	if constexpr (weaponType == WEAPON_TYPE_MELEE)
	{
		func = reinterpret_cast<IsWeaponReady_t>(IsMeleeWeaponReady[actorData.character]);
	}
	else
	{
		func = reinterpret_cast<IsWeaponReady_t>(IsRangedWeaponReady[actorData.character]);
	}


	if (func == 0)
	{
		return true;
	}




	return func(actorData, weapon);
}

auto IsMeleeWeaponReadyProxy = IsWeaponReadyProxy<>;
auto IsRangedWeaponReadyProxy = IsWeaponReadyProxy<WEAPON_TYPE_RANGED>;











struct IsWeaponReadyProxyHelper_t
{
	uint32 off[2];
	uint8 weaponType;
};

constexpr IsWeaponReadyProxyHelper_t IsWeaponReadyProxyHelper[] =
{
	{ 0x2288D3, 0x2288D8, WEAPON_TYPE_MELEE  }, // Dante Agni & Rudra
	{ 0x2295B7, 0x2295BC, WEAPON_TYPE_MELEE  }, // Dante Vergil Beowulf
	{ 0x229E9D, 0       , WEAPON_TYPE_MELEE  }, // Vergil Force Edge
	{ 0x22AD86, 0x22AD8B, WEAPON_TYPE_MELEE  }, // Dante Nevan
	{ 0x22B723, 0       , WEAPON_TYPE_RANGED }, // Dante Ebony & Ivory Air
	{ 0x22B753, 0       , WEAPON_TYPE_RANGED }, // Dante Ebony & Ivory
	{ 0x22C186, 0       , WEAPON_TYPE_RANGED }, // Dante Lady Kalina Ann
	{ 0x22C1A5, 0       , WEAPON_TYPE_RANGED }, // Dante Kalina Ann Grapple
	{ 0x22CBC8, 0x22CBCD, WEAPON_TYPE_RANGED }, // Dante Artemis
	{ 0x22D432, 0x22D437, WEAPON_TYPE_MELEE  }, // Vergil Nero Angelo Sword
	{ 0x22E09A, 0x22E09F, WEAPON_TYPE_MELEE  }, // Vergil Yamato
	{ 0x22FB1C, 0x22FB21, WEAPON_TYPE_MELEE  }, // Dante Cerberus
	{ 0x2304BF, 0       , WEAPON_TYPE_RANGED }, // Dante Spiral
	{ 0x230DD3, 0       , WEAPON_TYPE_RANGED }, // Dante Shotgun Shot
	{ 0x230E16, 0       , WEAPON_TYPE_RANGED }, // Dante Shotgun
	{ 0x23163F, 0       , WEAPON_TYPE_MELEE  }, // Dante Rebellion
	{ 0x232005, 0       , WEAPON_TYPE_MELEE  }, // Bob Yamato Combo 1 Part 3
	{ 0x232056, 0       , WEAPON_TYPE_MELEE  }, // Bob Yamato
};







void UpdateActorDante(byte8 * baseAddr)
{
	auto & actorData = *reinterpret_cast<ACTOR_DATA *>(baseAddr);

	//static_assert(offsetof(ACTOR_DATA, devilModelMetadata.rebellion.submodelMetadata[0].submodelIndex) == 0xB602);
	//static_assert(offsetof(ACTOR_DATA, devilModelMetadata.rebellion.submodelMetadata[1].submodelIndex) == 0xB605);
	//static_assert(offsetof(ACTOR_DATA, devilModelMetadata.cerberus.submodelMetadata[0].submodelIndex) == 0xB60A);
	//static_assert(offsetof(ACTOR_DATA, devilModelMetadata.nevan.submodelMetadata[0].submodelIndex) == 0xB611);
	//static_assert(offsetof(ACTOR_DATA, devilModelMetadata.nevan.submodelMetadata[1].submodelIndex) == 0xB614);
	//static_assert(offsetof(ACTOR_DATA, devilModelMetadata.beowulf.submodelMetadata[0].submodelIndex) == 0xB619);
	//static_assert(offsetof(ACTOR_DATA, devilModelMetadata.sparda.submodelMetadata[0].submodelIndex) == 0xB61E);

	actorData.devilModelMetadata.rebellion.submodelMetadata[0].submodelIndex = 255;
	actorData.devilModelMetadata.rebellion.submodelMetadata[1].submodelIndex = 255;
	actorData.devilModelMetadata.cerberus.submodelMetadata[0].submodelIndex = 255;
	actorData.devilModelMetadata.nevan.submodelMetadata[0].submodelIndex = 255;
	actorData.devilModelMetadata.nevan.submodelMetadata[1].submodelIndex = 255;
	actorData.devilModelMetadata.beowulf.submodelMetadata[0].submodelIndex = 255;
	actorData.devilModelMetadata.sparda.submodelMetadata[0].submodelIndex = 255;

	//*(byte8 *)(baseAddr + 0xB602) = 0xFF;
	//*(byte8 *)(baseAddr + 0xB605) = 0xFF;
	//*(byte8 *)(baseAddr + 0xB60A) = 0xFF;
	//*(byte8 *)(baseAddr + 0xB611) = 0xFF;
	//*(byte8 *)(baseAddr + 0xB614) = 0xFF;
	//*(byte8 *)(baseAddr + 0xB619) = 0xFF;
	//*(byte8 *)(baseAddr + 0xB61E) = 0xFF;

	System_File_UpdateFileItems(&actorData);

	Cosmetics_Model_UpdateModelDante[COSTUME_DANTE_DEFAULT](baseAddr);
	//Cosmetics_Model_UpdateDevilModelDante[0](baseAddr, 1);

	Cosmetics_Model_UpdateDevilModelDante[DEVIL_DANTE_REBELLION](baseAddr, 1);
	Cosmetics_Model_UpdateDevilModelDante[DEVIL_DANTE_CERBERUS](baseAddr, 2);





	for (uint8 index = 0; index < countof(motionHelperDante); index++)
	{
		auto & motionId    = motionHelperDante[index].motionId;
		auto & cacheFileId = motionHelperDante[index].cacheFileId;

		actorData.motionArchive[motionId] = System_File_cacheFile[cacheFileId];
	}





	func_1EF040(baseAddr, 0);

	func_1EEF80(baseAddr);

	func_1EF040(baseAddr, 3);

	//*(byte8 **)(baseAddr + 0x3DD0) = *(byte8 **)(appBaseAddr + 0x590598);
	//*(byte8 **)(baseAddr + 0x3DD8) = *(byte8 **)(appBaseAddr + 0x58A2A0);
	//*(byte8 **)(baseAddr + 0x3DE0) = (appBaseAddr + 0x5905B0);
	//*(byte8 **)(baseAddr + 0x3DE8) = System_File_cacheFile[pl000][9];
	//*(byte8 **)(baseAddr + 0x3DF0) = System_File_cacheFile[pl000][10];
	//*(byte8 **)(baseAddr + 0x3DF8) = System_File_cacheFile[pl000][11];

	actorData.actionData[0] = *(byte8 **)(appBaseAddr + 0x590598);
	actorData.actionData[1] = *(byte8 **)(appBaseAddr + 0x58A2A0);
	actorData.actionData[2] = (appBaseAddr + 0x5905B0);
	actorData.actionData[3] = System_File_cacheFile[pl000][9];
	actorData.actionData[4] = System_File_cacheFile[pl000][10];
	actorData.actionData[5] = System_File_cacheFile[pl000][11];

	func_2EE3D0((baseAddr + 0x3C50));
	func_1FAF40(baseAddr);
}

typedef byte8 *(__fastcall * RegisterWeapon_t)(byte8 * baseAddr, uint32 id);

RegisterWeapon_t RegisterWeapon[MAX_WEAPON] = {};

inline void RegisterWeapon_Init()
{
	RegisterWeapon[WEAPON_DANTE_REBELLION  ] = func_2310B0;
	RegisterWeapon[WEAPON_DANTE_CERBERUS   ] = func_22EC90;
	RegisterWeapon[WEAPON_DANTE_AGNI_RUDRA ] = func_227870;
	RegisterWeapon[WEAPON_DANTE_NEVAN      ] = func_22A1E0;
	RegisterWeapon[WEAPON_DANTE_BEOWULF    ] = func_228CF0;
	RegisterWeapon[WEAPON_DANTE_EBONY_IVORY] = func_22B0C0;
	RegisterWeapon[WEAPON_DANTE_SHOTGUN    ] = func_2306B0;
	RegisterWeapon[WEAPON_DANTE_ARTEMIS    ] = func_22C4A0;
	RegisterWeapon[WEAPON_DANTE_SPIRAL     ] = func_2300A0;
	RegisterWeapon[WEAPON_DANTE_KALINA_ANN ] = func_22BA30;

	RegisterWeapon[WEAPON_VERGIL_YAMATO    ] = func_22D960;
	RegisterWeapon[WEAPON_VERGIL_BEOWULF   ] = func_228CF0;
	RegisterWeapon[WEAPON_VERGIL_FORCE_EDGE] = func_2298E0;
}

void UpdateWeaponDante(byte8 * baseAddr)
{
	auto & actorData = *reinterpret_cast<ACTOR_DATA *>(baseAddr);

	constexpr uint32 size = (offsetof(ACTOR_DATA, styleRank) - offsetof(ACTOR_DATA, weaponData));
	memset(actorData.weaponData, 0, size);

	actorData.weaponData[0] = RegisterWeapon[WEAPON_DANTE_REBELLION  ](baseAddr, 0);
	actorData.weaponData[1] = RegisterWeapon[WEAPON_DANTE_CERBERUS   ](baseAddr, 0);
	actorData.weaponData[2] = RegisterWeapon[WEAPON_DANTE_EBONY_IVORY](baseAddr, 0);
	actorData.weaponData[3] = RegisterWeapon[WEAPON_DANTE_SHOTGUN    ](baseAddr, 0);

	//static_assert(offsetof(ACTOR_DATA, weaponFlags[4]) == 0x64D8);
	actorData.weaponFlags[4] = 4;
}

byte8 * CreateActor
(
	uint8 character,
	uint8 actor
)
{
	auto g_pool = *(byte8 ***)(appBaseAddr + 0xC90E28);

	byte8 * sessionData = 0;

	byte8 * baseAddr = 0;

	sessionData = (g_pool[1] + 0x16C);

	//func_2EE060((mainActorBaseAddr + 0x6410), 0x3C);

	baseAddr = func_1DE820(character, actor, false);

	//func_1BB390(g_pool, actor);

	func_217B90(baseAddr, sessionData); // InitActorDante
	UpdateActorDante(baseAddr);
	UpdateWeaponDante(baseAddr);

	func_1DFC20(baseAddr);

	return baseAddr;
}






















//#include <algorithm>



void System_Actor_Init()
{
	LogFunction();

	RegisterWeapon_Init();

	{
		byte8 sect2[] =
		{
			0x84, 0xC0,                   //test al,al
			0x74, 0x05,                   //je short
			0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc3.exe+1FDE10
		};
		for (uint8 index = 0; index < countof(IsWeaponReadyProxyHelper); index++)
		{
			auto & item = IsWeaponReadyProxyHelper[index];

			byte8 * addr = 0;
			byte8 * jumpAddr = 0;
			FUNC func = {};

			addr = (appBaseAddr + item.off[0]);
			jumpAddr = (item.off[1]) ? (appBaseAddr + item.off[1]) : 0;
			func = CreateFunction
			(
				(item.weaponType == WEAPON_TYPE_MELEE) ? IsMeleeWeaponReadyProxy : IsRangedWeaponReadyProxy,
				jumpAddr,
				true,
				false,
				0,
				0,
				sizeof(sect2)
			);
			memcpy(func.sect2, sect2, sizeof(sect2));
			if (jumpAddr)
			{
				WriteCall((func.sect2 + 4), (appBaseAddr + 0x1FDE10));
			}
			else
			{
				WriteJump((func.sect2 + 4), (appBaseAddr + 0x1FDE10));
			}
			WriteJump(addr, func.addr);
		}
	}











	// @Research: Lady has different actor_data size. Geez, quite the turn.

	// Increase ACTOR_DATA size.
	{
		constexpr uint32 size = (0xB8C0 + 512);
		Write<uint32>((appBaseAddr + 0x1DE5FA), size);
		Write<uint32>((appBaseAddr + 0x1DE67A), size);
		Write<uint32>((appBaseAddr + 0x1DE8B4), size);
		Write<uint32>((appBaseAddr + 0x1DEBE2), size);
	}

	{
		byte8 sect0[] =
		{
			0x66, 0x23, 0x83, 0x00, 0x00, 0x00, 0x00, //and ax,[rbx+0000B8C0]
			0x66, 0x89, 0x83, 0xE0, 0x74, 0x00, 0x00, //mov [rbx+000074E0],ax
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x1EBD3B), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*(byte32 *)(func.sect0 + 3) = offsetof(ACTOR_DATA, buttonMask);
		//WriteJump((appBaseAddr + 0x1EBD34), func.addr, 2);
		/*
		dmc3.exe+1EBD34 - 66 89 83 E0740000 - mov [rbx+000074E0],ax
		dmc3.exe+1EBD3B - 48 8D 0D CE8CB600 - lea rcx,[dmc3.exe+D54A10]
		*/
	}


	{
		byte8 sect0[] =
		{
			0x66, 0x23, 0x83, 0x00, 0x00, 0x00, 0x00, //and ax,[rbx+0000B8C0]
			0x66, 0x89, 0x83, 0xE2, 0x74, 0x00, 0x00, //mov [rbx+000074E2],ax
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x1EBD5B), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*(byte32 *)(func.sect0 + 3) = offsetof(ACTOR_DATA, buttonMask);
		//WriteJump((appBaseAddr + 0x1EBD54), func.addr, 2);
		/*
		dmc3.exe+1EBD54 - 66 89 83 E2740000 - mov [rbx+000074E2],ax
		dmc3.exe+1EBD5B - 66 23 CA          - and cx,dx
		*/
	}

	{
		byte8 sect0[] =
		{
			0x66, 0x23, 0x8B, 0x00, 0x00, 0x00, 0x00, //and cx,[rbx+0000B8C0]
			0x66, 0x89, 0x8B, 0xE4, 0x74, 0x00, 0x00, //mov [rbx+000074E4],cx
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x1EBD6B), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*(byte32 *)(func.sect0 + 3) = offsetof(ACTOR_DATA, buttonMask);
		//WriteJump((appBaseAddr + 0x1EBD64), func.addr, 2);
		/*
		dmc3.exe+1EBD64 - 66 89 8B E4740000 - mov [rbx+000074E4],cx
		dmc3.exe+1EBD6B - 66 23 D0          - and dx,ax
		*/
	}


	{
		byte8 sect0[] =
		{
			0x66, 0x23, 0x93, 0x00, 0x00, 0x00, 0x00, //and dx,[rbx+0000B8C0]
			0x66, 0x89, 0x93, 0xE6, 0x74, 0x00, 0x00, //mov [rbx+000074E6],dx
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x1EBD7C), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*(byte32 *)(func.sect0 + 3) = offsetof(ACTOR_DATA, buttonMask);
		//WriteJump((appBaseAddr + 0x1EBD75), func.addr, 2);
		/*
		dmc3.exe+1EBD75 - 66 89 93 E6740000 - mov [rbx+000074E6],dx
		dmc3.exe+1EBD7C - 33 D2             - xor edx,edx
		*/
	}

	//Write<byte32>((appBaseAddr + 0x1EBD19), offsetof(ACTOR_DATA, gamepad));
}
