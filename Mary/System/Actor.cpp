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













//bool IsWeaponActive(byte8 * baseAddr, uint8 weapon)
//{
//	auto & actorData = *(ACTOR_DATA *)baseAddr;
//	if (actorData.motionData[1].group == (MOTION_GROUP_DANTE_REBELLION + weapon))
//	{
//		return true;
//	}
//	if (actorData.motionData[1].group == (MOTION_GROUP_DANTE_SWORDMASTER_REBELLION + weapon))
//	{
//		return true;
//	}
//	return false;
//}






//bool IsWeaponActiveDante
//(
//	ACTOR_DATA_DANTE & actorData,
//	uint8 weapon
//)
//{
//	if (actorData.motionData[1].group == (MOTION_GROUP_DANTE_REBELLION + weapon))
//	{
//		return true;
//	}
//	if (actorData.motionData[1].group == (MOTION_GROUP_DANTE_SWORDMASTER_REBELLION + weapon))
//	{
//		return true;
//	}
//	return false;
//}
//
//bool IsWeaponActiveVergil
//(
//	ACTOR_DATA_VERGIL & actorData,
//	uint8 weapon
//)
//{
//	if (actorData.motionData[1].group == (MOTION_GROUP_VERGIL_YAMATO + weapon - WEAPON_VERGIL_YAMATO))
//	{
//		return true;
//	}
//	return false;
//}




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

auto IsMeleeWeaponReadyDante = IsWeaponReady<ACTOR_DATA_DANTE>;
auto IsRangedWeaponReadyDante = IsWeaponReady<ACTOR_DATA_DANTE, WEAPON_TYPE_RANGED>;
auto IsMeleeWeaponReadyVergil = IsWeaponReady<ACTOR_DATA_VERGIL>;







//bool IsMeleeWeaponReadyDante
//(
//	ACTOR_DATA_DANTE & actorData,
//	uint8 weapon
//)
//{
//	auto meleeWeaponMap = actorData.weaponMap;
//	auto & meleeWeaponIndex = actorData.weaponIndex[0];
//
//	if (IsWeaponActiveDante(actorData, weapon))
//	{
//		return true;
//	}
//
//	for (uint8 index = 0; index < 2; index++)
//	{
//		if (meleeWeaponMap[index] == weapon)
//		{
//			continue;
//		}
//		if (IsWeaponActiveDante(actorData, meleeWeaponMap[index]))
//		{
//			return false;
//		}
//	}
//
//	if (meleeWeaponMap[meleeWeaponIndex] == weapon)
//	{
//		return true;
//	}
//
//	return false;
//}
//
//bool IsRangedWeaponReadyDante
//(
//	ACTOR_DATA_DANTE & actorData,
//	uint8 weapon
//)
//{
//	auto rangedWeaponMap = reinterpret_cast<uint8 *>(&actorData.weaponMap[2]);
//	auto rangedWeaponIndex = (actorData.weaponIndex[1] - 2);
//
//	if (IsWeaponActiveDante(actorData, weapon))
//	{
//		return true;
//	}
//
//	for (uint8 index = 0; index < 2; index++)
//	{
//		if (rangedWeaponMap[index] == weapon)
//		{
//			continue;
//		}
//		if (IsWeaponActiveDante(actorData, rangedWeaponMap[index]))
//		{
//			return false;
//		}
//	}
//
//	if (rangedWeaponMap[rangedWeaponIndex] == weapon)
//	{
//		return true;
//	}
//
//	return false;
//}
//
//bool IsMeleeWeaponReadyVergil
//(
//	ACTOR_DATA_VERGIL & actorData,
//	uint8 weapon
//)
//{
//	auto meleeWeaponMap = actorData.weaponMap;
//	auto & meleeWeaponIndex = actorData.weaponIndex[0];
//
//	if (IsWeaponActiveVergil(actorData, weapon))
//	{
//		return true;
//	}
//
//	for (uint8 index = 0; index < 3; index++)
//	{
//		if (meleeWeaponMap[index] == weapon)
//		{
//			continue;
//		}
//		if (IsWeaponActiveVergil(actorData, meleeWeaponMap[index]))
//		{
//			return false;
//		}
//	}
//
//	if (meleeWeaponMap[meleeWeaponIndex] == weapon)
//	{
//		return true;
//	}
//
//	return false;
//}






template
<
	typename T,
	uint8 weaponType = WEAPON_TYPE_MELEE
>
bool IsWeaponReadyProxy(byte8 * baseAddr)
{
	auto & weapon = *reinterpret_cast<uint8 *>(baseAddr + 0x112);
	auto actorBaseAddr = *reinterpret_cast<byte8 **>(baseAddr + 0x120);
	if (!actorBaseAddr)
	{
		return false;
	}
	auto & actorData = *reinterpret_cast<T *>(actorBaseAddr);
	return IsWeaponReady<T, weaponType>(actorData, weapon);
}

auto IsMeleeWeaponReadyProxyDante = IsWeaponReadyProxy<ACTOR_DATA_DANTE>;
auto IsRangedWeaponReadyProxyDante = IsWeaponReadyProxy<ACTOR_DATA_DANTE, WEAPON_TYPE_RANGED>;
auto IsMeleeWeaponReadyProxyVergil = IsWeaponReadyProxy<ACTOR_DATA_VERGIL>;






//bool IsMeleeWeaponReadyProxyDante(byte8 * baseAddr)
//{
//	auto actorBaseAddr = reinterpret_cast<byte8 *>(baseAddr + 0x120);
//	if (!actorBaseAddr)
//	{
//		return false;
//	}
//	auto & actorData = *reinterpret_cast<ACTOR_DATA_DANTE *>(actorBaseAddr);
//	auto & weapon = *reinterpret_cast<uint8 *>(baseAddr + 0x112);
//	return IsMeleeWeaponReadyDante(actorData, weapon);
//}
//
//bool IsMeleeWeaponReadyProxyDante(byte8 * baseAddr)
//{
//	auto actorBaseAddr = reinterpret_cast<byte8 *>(baseAddr + 0x120);
//	if (!actorBaseAddr)
//	{
//		return false;
//	}
//	auto & actorData = *reinterpret_cast<ACTOR_DATA_DANTE *>(actorBaseAddr);
//	auto & weapon = *reinterpret_cast<uint8 *>(baseAddr + 0x112);
//	return IsMeleeWeaponReadyDante(actorData, weapon);
//}

















//auto lol = IsMeleeWeaponReadyTemplate<ACTOR_DATA_DANTE, CHAR_DANTE>;

//using IsMeleeWeaponReadyTemplate<ACTOR_DATA_DANTE, CHAR_DANTE> = lol;





























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

void System_Actor_Init()
{
	LogFunction();

	RegisterWeapon_Init();



	Log("IsMeleeWeaponReadyDante  %llX", IsMeleeWeaponReadyDante);
	Log("IsRangedWeaponReadyDante %llX", IsRangedWeaponReadyDante);
	Log("IsMeleeWeaponReadyVergil %llX", IsMeleeWeaponReadyVergil);


	/*
	dmc3.exe+2288D3 Dante Agni & Rudra
	dmc3.exe+2295B7 Dante Vergil Beowulf
	dmc3.exe+229E9D Vergil Force Edge
	dmc3.exe+22AD86 Dante Nevan
	dmc3.exe+22B723 Dante Ebony & Ivory Air
	dmc3.exe+22B753 Dante Ebony & Ivory
	dmc3.exe+22C186 Dante Lady Kalina Ann
	dmc3.exe+22C1A5 Dante Kalina Ann Grapple
	dmc3.exe+22CBC8 Dante Artemis
	dmc3.exe+22D432 Vergil Nero Angelo Sword
	dmc3.exe+22E09A Vergil Yamato
	dmc3.exe+22FB1C Dante Cerberus
	dmc3.exe+2304BF Dante Spiral
	dmc3.exe+230DD3 Dante Shotgun Shot
	dmc3.exe+230E16 Dante Shotgun
	dmc3.exe+23163F Dante Rebellion
	dmc3.exe+232005 Bob Yamato Combo 1 Part 3
	dmc3.exe+232056 Bob Yamato
	*/

	{
		byte8 sect2[] =
		{
			0x84, 0xC0,                   //test al,al
			0x74, 0x05,                   //je short
			0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc3.exe+1FDE10
			0xC3,                         //ret
		};


		{
			auto func = CreateFunction(IsMeleeWeaponReadyProxyDante, 0, true, false, 0, 0, sizeof(sect2));
			memcpy(func.sect2, sect2, sizeof(sect2));
			WriteJump((func.sect2 + 4), (appBaseAddr + 0x1FDE10));
			WriteJump((appBaseAddr + 0x23163F), func.addr);
		}


		//auto func = CreateFunction(IsMeleeWeaponReadyProxyDante, 0, true, false, 0, 0, sizeof(sect2));
		//memcpy(func.sect2, sect2, sizeof(sect2));
		//WriteCall((func.sect2 + 4), (appBaseAddr + 0x1FDE10));
		//WriteJump((appBaseAddr + 0x23163F), func.addr);






	}


	//{

	//	byte8 sect2[] =
	//	{
	//		0x84, 0xC0,                   //test al,al
	//		0x74, 0x05,                   //je short
	//		0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc3.exe+1FDE10
	//		0xC3,                         //ret
	//	};

	//	auto func = CreateFunction()





	//}

















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
