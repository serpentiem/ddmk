#include "Actor.h"

vector<byte8 *, 128> Actor_actorBaseAddr;

typedef byte8 *(__fastcall * RegisterWeapon_t)
(
	byte8 * actorData,
	uint32 id
);

typedef bool(__fastcall * IsWeaponReady_t)
(
	byte8 * actorData,
	uint8 weapon
);

struct IsWeaponReadyProxyHelper_t
{
	uint32 off[2];
	uint8 weaponType;
};

RegisterWeapon_t RegisterWeapon[MAX_WEAPON] = {};

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

byte8 * IsWeaponReadyProxyFuncAddr[countof(IsWeaponReadyProxyHelper)] = {};















// @Todo: Update.

//template
//<
//	typename T,
//	uint8 weaponType = WEAPON_TYPE_MELEE
//>
//bool IsWeaponReady
//(
//	T & actorData,
//	uint8 weapon
//)
//{
//	uint8 * weaponMap = 0;
//	uint8 weaponCount = 0;
//	uint8 weaponIndex = 0;
//
//	if constexpr (typematch(T, ACTOR_DATA_DANTE))
//	{
//		if constexpr (weaponType == WEAPON_TYPE_MELEE)
//		{
//			weaponMap = actorData.meleeWeaponMap;
//			weaponCount = 2;
//			weaponIndex = actorData.meleeWeaponIndex;
//		}
//		else
//		{
//			weaponMap = actorData.rangedWeaponMap;
//			weaponCount = 2;
//			weaponIndex = (actorData.rangedWeaponIndex - 2);
//		}
//	}
//	else if constexpr (typematch(T, ACTOR_DATA_VERGIL))
//	{
//		weaponMap = actorData.meleeWeaponMap;
//		weaponCount = 3;
//		weaponIndex = actorData.queuedMeleeWeaponIndex;
//	}
//
//	if (IsWeaponActive<T>(actorData, weapon))
//	{
//		return true;
//	}
//
//	for (uint8 index = 0; index < weaponCount; index++)
//	{
//		if (weaponMap[index] == weapon)
//		{
//			continue;
//		}
//		if (IsWeaponActive<T>(actorData, weaponMap[index]))
//		{
//			return false;
//		}
//	}
//
//	if constexpr (typematch(T, ACTOR_DATA_VERGIL))
//	{
//		if (actorData.activeMeleeWeaponIndex != actorData.queuedMeleeWeaponIndex)
//		{
//			actorData.activeMeleeWeaponIndex = actorData.queuedMeleeWeaponIndex;
//		}
//	}
//
//	if (weaponMap[weaponIndex] == weapon)
//	{
//		return true;
//	}
//
//	if constexpr (typematch(T, ACTOR_DATA_VERGIL))
//	{
//		if ((weapon == WEAPON_VERGIL_YAMATO) && (weaponMap[weaponIndex] == WEAPON_VERGIL_FORCE_EDGE))
//		{
//			return true;
//		}
//	}
//
//	return false;
//}





// @Todo: If actor has no parent, has child, child's weapon yamato is still active, keep hiding weapon.


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


	// auto &

	uint8 * weaponMap = 0;
	uint8 weaponCount = 0;
	uint8 weaponIndex = 0;

	//if constexpr (typematch(T, ACTOR_DATA_DANTE))
	//{
	//	if constexpr (weaponType == WEAPON_TYPE_MELEE)
	//	{
	//		weaponMap = actorData.meleeWeaponMap;
	//		weaponCount = 2;
	//		weaponIndex = actorData.meleeWeaponIndex;
	//	}
	//	else
	//	{
	//		weaponMap = actorData.rangedWeaponMap;
	//		weaponCount = 2;
	//		weaponIndex = (actorData.rangedWeaponIndex - 2);
	//	}
	//}
	//else if constexpr (typematch(T, ACTOR_DATA_VERGIL))
	//{
	//	weaponMap = actorData.meleeWeaponMap;
	//	weaponCount = 3;
	//	weaponIndex = actorData.queuedMeleeWeaponIndex;
	//}


	if constexpr (weaponType == WEAPON_TYPE_MELEE)
	{
		weaponMap = actorData.newMeleeWeaponMap;
		weaponCount = actorData.newMeleeWeaponCount;
		weaponIndex = actorData.newMeleeWeaponIndex;
	}
	else
	{
		weaponMap = actorData.newRangedWeaponMap;
		weaponCount = actorData.newRangedWeaponCount;
		weaponIndex = actorData.newRangedWeaponIndex;
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

	//if constexpr (typematch(T, ACTOR_DATA_VERGIL))
	//{
	//	if (actorData.activeMeleeWeaponIndex != actorData.queuedMeleeWeaponIndex)
	//	{
	//		actorData.activeMeleeWeaponIndex = actorData.queuedMeleeWeaponIndex;
	//	}
	//}

	if (weaponMap[weaponIndex] == weapon)
	{
		return true;
	}

	//if constexpr (typematch(T, ACTOR_DATA_VERGIL))
	//{
	//	if ((weapon == WEAPON_VERGIL_YAMATO) && (weaponMap[weaponIndex] == WEAPON_VERGIL_FORCE_EDGE))
	//	{
	//		return true;
	//	}
	//}

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

	IsWeaponReady_t func = 0;

	auto character = actorData.character;
	if (character >= MAX_CHAR)
	{
		character = 0;
	}

	if constexpr (weaponType == WEAPON_TYPE_MELEE)
	{
		func = reinterpret_cast<IsWeaponReady_t>(IsMeleeWeaponReady[character]);
	}
	else
	{
		func = reinterpret_cast<IsWeaponReady_t>(IsRangedWeaponReady[character]);
	}

	if (func == 0)
	{
		return true;
	}

	return func(actorData, weapon);
}

auto IsMeleeWeaponReadyProxy = IsWeaponReadyProxy<>;
auto IsRangedWeaponReadyProxy = IsWeaponReadyProxy<WEAPON_TYPE_RANGED>;

void ToggleUpdateWeapon(bool enable)
{
	LogFunction(enable);

	const_for_all(index, countof(IsWeaponReadyProxyHelper))
	{
		auto & item = IsWeaponReadyProxyHelper[index];

		byte8 * addr = 0;
		byte8 * jumpAddr = 0;

		addr = (appBaseAddr + item.off[0]);
		jumpAddr = (item.off[1]) ? (appBaseAddr + item.off[1]) : 0;

		if (enable)
		{
			WriteJump(addr, IsWeaponReadyProxyFuncAddr[index]);
		}
		else
		{
			if (jumpAddr)
			{
				WriteCall(addr, (appBaseAddr + 0x1FDE10));
			}
			else
			{
				WriteJump(addr, (appBaseAddr + 0x1FDE10));
			}
		}
	}

	auto WriteHelper = [&]
	(
		uint32 callOff,
		uint32 jumpOff,
		uint32 jumpDestOff
		)
	{
		if (enable)
		{
			WriteJump((appBaseAddr + callOff), (appBaseAddr + callOff + 5));
			WriteAddress((appBaseAddr + jumpOff), (appBaseAddr + jumpOff + 2), 2);
		}
		else
		{
			WriteCall((appBaseAddr + callOff), (appBaseAddr + 0x1FD3E0));
			WriteAddress((appBaseAddr + jumpOff), (appBaseAddr + jumpDestOff), 2);
		}
	};

	WriteHelper(0x2288A4, 0x2288CE, 0x2288D8); // Dante Agni & Rudra
	/*
	dmc3.exe+2288A4 - E8 374BFDFF - call dmc3.exe+1FD3E0
	dmc3.exe+2288CE - 74 08       - je dmc3.exe+2288D8
	*/
	WriteHelper(0x229E8C, 0x229E93, 0x229EA2); // Vergil Force Edge
	/*
	dmc3.exe+229E8C - E8 4F35FDFF - call dmc3.exe+1FD3E0
	dmc3.exe+229E93 - 74 0D       - je dmc3.exe+229EA2
	*/
	WriteHelper(0x22AD2D, 0x22AD39, 0x22AD8B); // Dante Nevan
	/*
	dmc3.exe+22AD2D - E8 AE26FDFF - call dmc3.exe+1FD3E0
	dmc3.exe+22AD39 - 74 50       - je dmc3.exe+22AD8B
	*/
	WriteHelper(0x22FAD4, 0x22FADB, 0x22FB21); // Dante Cerberus
	/*
	dmc3.exe+22FAD4 - E8 07D9FCFF - call dmc3.exe+1FD3E0
	dmc3.exe+22FADB - 74 44       - je dmc3.exe+22FB21
	*/
	WriteHelper(0x23162E, 0x231635, 0x231644); // Dante Rebellion
	/*
	dmc3.exe+23162E - E8 ADBDFCFF - call dmc3.exe+1FD3E0
	dmc3.exe+231635 - 74 0D       - je dmc3.exe+231644
	*/
}

//void UpdateActorDante(byte8 * baseAddr)
//{
//	auto & actorData = *reinterpret_cast<ACTOR_DATA *>(baseAddr);
//
//
//
//
//	actorData.devilModelMetadata.rebellion.submodelMetadata[0].submodelIndex = 255;
//	actorData.devilModelMetadata.rebellion.submodelMetadata[1].submodelIndex = 255;
//	actorData.devilModelMetadata.cerberus.submodelMetadata[0].submodelIndex = 255;
//	actorData.devilModelMetadata.nevan.submodelMetadata[0].submodelIndex = 255;
//	actorData.devilModelMetadata.nevan.submodelMetadata[1].submodelIndex = 255;
//	actorData.devilModelMetadata.beowulf.submodelMetadata[0].submodelIndex = 255;
//	actorData.devilModelMetadata.sparda.submodelMetadata[0].submodelIndex = 255;
//
//
//
//
//
//	File_UpdateFileItems(&actorData);
//
//	Cosmetics_Model_UpdateModelDante[COSTUME_DANTE_DEFAULT](baseAddr);
//	
//
//
//
//	Cosmetics_Model_UpdateDevilModelDante[DEVIL_DANTE_REBELLION](baseAddr, 1);
//	Cosmetics_Model_UpdateDevilModelDante[DEVIL_DANTE_CERBERUS](baseAddr, 2);
//
//
//
//
//
//	//for (uint8 index = 0; index < countof(motionHelperDante); index++)
//	for_all(index, countof(motionHelperDante))
//	{
//		auto & motionId    = motionHelperDante[index].motionId;
//		auto & cacheFileId = motionHelperDante[index].cacheFileId;
//
//		actorData.motionArchive[motionId] = File_cacheFile[cacheFileId];
//	}
//
//
//
//
//
//	func_1EF040(baseAddr, 0);
//	func_1EEF80(baseAddr);
//	func_1EF040(baseAddr, 3);
//
//
//
//
//
//	actorData.actionData[0] = *(byte8 **)(appBaseAddr + 0x590598);
//	actorData.actionData[1] = *(byte8 **)(appBaseAddr + 0x58A2A0);
//	actorData.actionData[2] = (appBaseAddr + 0x5905B0);
//	actorData.actionData[3] = File_cacheFile[pl000][9];
//	actorData.actionData[4] = File_cacheFile[pl000][10];
//	actorData.actionData[5] = File_cacheFile[pl000][11];
//
//	func_2EE3D0((baseAddr + 0x3C50));
//	func_1FAF40(baseAddr);
//}

// @Todo: Create map and add missing entries.
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

//void UpdateWeaponDante(byte8 * baseAddr)
//{
//	auto & actorData = *reinterpret_cast<ACTOR_DATA *>(baseAddr);
//
//	constexpr uint32 size = (offsetof(ACTOR_DATA, styleRank) - offsetof(ACTOR_DATA, weaponData));
//	memset(actorData.weaponData, 0, size);
//
//	actorData.weaponData[0] = RegisterWeapon[WEAPON_DANTE_REBELLION  ](baseAddr, 0);
//	actorData.weaponData[1] = RegisterWeapon[WEAPON_DANTE_CERBERUS   ](baseAddr, 0);
//	actorData.weaponData[2] = RegisterWeapon[WEAPON_DANTE_EBONY_IVORY](baseAddr, 0);
//	actorData.weaponData[3] = RegisterWeapon[WEAPON_DANTE_SHOTGUN    ](baseAddr, 0);
//
//	//static_assert(offsetof(ACTOR_DATA, weaponFlags[4]) == 0x64D8);
//	actorData.weaponFlags[4] = 4;
//}

//byte8 * CreateActor
//(
//	uint8 character,
//	uint8 actor
//)
//{
//	auto g_pool = *(byte8 ***)(appBaseAddr + 0xC90E28);
//
//	byte8 * sessionData = 0;
//
//	byte8 * baseAddr = 0;
//
//	sessionData = (g_pool[1] + 0x16C);
//
//	//func_2EE060((mainActorBaseAddr + 0x6410), 0x3C);
//
//	baseAddr = func_1DE820(character, actor, false);
//
//	//func_1BB390(g_pool, actor);
//
//	func_217B90(baseAddr, sessionData); // InitActorDante
//	UpdateActorDante(baseAddr);
//	UpdateWeaponDante(baseAddr);
//
//	func_1DFC20(baseAddr);
//
//	return baseAddr;
//}







// @Research: Very treacherous.

struct
{
	uint8 newMeleeWeaponMap[5] =
	{
		WEAPON_DANTE_REBELLION,
		WEAPON_DANTE_CERBERUS,
		WEAPON_VERGIL_YAMATO,
		//WEAPON_DANTE_AGNI_RUDRA,
		WEAPON_DANTE_NEVAN,
		WEAPON_DANTE_BEOWULF,
	};
	uint8 newMeleeWeaponCount = 3;
	uint8 newRangedWeaponMap[5] =
	{
		WEAPON_DANTE_EBONY_IVORY,
		WEAPON_DANTE_SHOTGUN,
		WEAPON_DANTE_ARTEMIS,
		WEAPON_DANTE_SPIRAL,
		WEAPON_DANTE_KALINA_ANN,
	};
	uint8 newRangedWeaponCount = 5;
}
Dante;









// @Todo: Add IsWeaponIndexActive.

void UpdateWeaponDante(ACTOR_DATA_DANTE & actorData)
{
	constexpr uint32 size = (offsetof(ACTOR_DATA_DANTE, styleRank) - offsetof(ACTOR_DATA_DANTE, meleeWeaponData));
	memset(actorData.meleeWeaponData, 0, size);

	memcpy(actorData.newMeleeWeaponMap , Dante.newMeleeWeaponMap , sizeof(Dante.newMeleeWeaponMap ));
	memcpy(actorData.newRangedWeaponMap, Dante.newRangedWeaponMap, sizeof(Dante.newRangedWeaponMap));

	actorData.newMeleeWeaponCount  = Dante.newMeleeWeaponCount;
	actorData.newRangedWeaponCount = Dante.newRangedWeaponCount;

	const_for_all(index, 5)
	{
		uint32 id = (WEAPON_DANTE_REBELLION + index);
		actorData.newMeleeWeaponData[index] = RegisterWeapon[id](actorData, id);
	}
	const_for_all(index, 5)
	{
		uint32 id = (WEAPON_DANTE_EBONY_IVORY + index);
		actorData.newRangedWeaponData[index] = RegisterWeapon[id](actorData, id);
	}

	actorData.meleeWeaponMap[0] = actorData.newMeleeWeaponMap[actorData.newMeleeWeaponIndex];
	actorData.meleeWeaponMap[1] = WEAPON_VOID;

	//actorData.rangedWeaponMap[0] = actorData.newRangedWeaponMap[actorData.newRangedWeaponIndex];
	actorData.rangedWeaponMap[0] = WEAPON_DANTE_KALINA_ANN;
	actorData.rangedWeaponMap[1] = WEAPON_VOID;
	actorData.rangedWeaponMap[2] = WEAPON_VOID;

	actorData.meleeWeaponData [0] = actorData.newMeleeWeaponData [actorData.newMeleeWeaponIndex ];
	//actorData.rangedWeaponData[0] = actorData.newRangedWeaponData[actorData.newRangedWeaponIndex];
	actorData.rangedWeaponData[0] = actorData.newRangedWeaponData[4];

	actorData.rangedWeaponFlags[2] = 4;
}

ACTOR_DATA_DANTE * CreateActorDante()
{
	auto g_pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);
	auto sessionData = (g_pool[1] + 0x16C);

	auto baseAddr = func_1DE820(CHAR_DANTE, 0, false);
	if (!baseAddr)
	{
		return 0;
	}

	auto & actorData = *reinterpret_cast<ACTOR_DATA_DANTE *>(baseAddr);

	func_217B90(actorData, sessionData);
	func_212BE0(actorData);

	const_for_all(index, countof(motionHelperDante))
	{
		auto & motionId    = motionHelperDante[index].motionId;
		auto & cacheFileId = motionHelperDante[index].cacheFileId;

		actorData.motionArchive[motionId] = File_cacheFile[cacheFileId];
	}

	UpdateWeaponDante(actorData);

	func_1DFC20(actorData);

	return &actorData;
}

void UpdateWeaponVergil(ACTOR_DATA_VERGIL & actorData)
{
	constexpr uint32 size = (offsetof(ACTOR_DATA_VERGIL, styleRank) - offsetof(ACTOR_DATA_VERGIL, meleeWeaponData));
	memset(actorData.meleeWeaponData, 0, size);

	const_for_all(index, 3)
	{
		uint8 id = (WEAPON_VERGIL_YAMATO + index);
		actorData.newMeleeWeaponData[index] = RegisterWeapon[id](actorData, id);
	}

	actorData.meleeWeaponMap[0] = WEAPON_VERGIL_YAMATO;
	actorData.meleeWeaponMap[1] = WEAPON_VERGIL_BEOWULF;
	actorData.meleeWeaponMap[2] = WEAPON_VERGIL_FORCE_EDGE;
	actorData.meleeWeaponMap[3] = WEAPON_VOID;
	actorData.meleeWeaponMap[4] = WEAPON_VOID;

	actorData.meleeWeaponData[0] = actorData.newMeleeWeaponData[0];
	actorData.meleeWeaponData[1] = actorData.newMeleeWeaponData[1];
	actorData.meleeWeaponData[2] = actorData.newMeleeWeaponData[2];

	actorData.meleeWeaponFlags[4] = 4;
}

ACTOR_DATA_VERGIL * CreateActorVergil()
{
	auto g_pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);
	auto sessionData = (g_pool[1] + 0x16C);

	auto baseAddr = func_1DE820(CHAR_VERGIL, 0, false);
	if (!baseAddr)
	{
		return 0;
	}

	auto & actorData = *reinterpret_cast<ACTOR_DATA_VERGIL *>(baseAddr);

	func_223CB0(actorData, sessionData);
	func_220970(actorData);

	const_for_all(index, countof(motionHelperVergil))
	{
		auto & motionId    = motionHelperVergil[index].motionId;
		auto & cacheFileId = motionHelperVergil[index].cacheFileId;

		actorData.motionArchive[motionId] = File_cacheFile[cacheFileId];
	}

	UpdateWeaponVergil(actorData);

	func_1DFC20(actorData);

	return &actorData;
}

// @Todo: Add devil support and Nero Angelo exceptions.
// @Todo: Check for WEAPON_VOID and same weapon.
// @Todo: Create templates.

//bool WeaponSwitchVergil(ACTOR_DATA_VERGIL & actorData)
//{
//	if (actorData.devilState == 2)
//	{
//		return true;
//	}
//	if (actorData.moveOnly)
//	{
//		return false;
//	}
//
//
//	{
//		if (!(actorData.buttons[2] & GetBinding(ACTION_CHANGE_DEVIL_ARMS)))
//		{
//			goto sect0;
//		}
//		if (0 < actorData.weaponSwitchTimeout[0])
//		{
//			goto sect0;
//		}
//		auto addr = actorData.actionData[3];
//		auto & timeout = *reinterpret_cast<float32 *>(addr + 0x348);
//		actorData.weaponSwitchTimeout[0] = timeout;
//		actorData.weaponSwitchTimeout[1] = timeout;
//
//		auto & queuedWeaponIndex = actorData.weaponIndex[1];
//		queuedWeaponIndex++;
//		if (queuedWeaponIndex >= 3)
//		{
//			queuedWeaponIndex = 0;
//		}
//
//		auto g_pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);
//		auto hud = *reinterpret_cast<byte8 **>(g_pool[11]);
//
//		// @Todo: In the future just update the weapon icon and use 0.
//		func_280160
//		(
//			hud,
//			(queuedWeaponIndex < 2) ? 1 : 0,
//			(queuedWeaponIndex < 2) ? queuedWeaponIndex : 0,
//			1
//		);
//		*reinterpret_cast<bool *>(reinterpret_cast<byte8 *>(&actorData) + 0x648C) = true;
//		func_1EB0E0(actorData, 4);
//
//		if (actorData.devil || (actorData.devilState == 1))
//		{
//			func_1F92C0(actorData, 1);
//			func_1F97F0(actorData, true);
//		}
//	}
//	sect0:;
//
//
//
//
//
//	{
//		if (!(actorData.buttons[2] & GetBinding(ACTION_CHANGE_GUN)))
//		{
//			goto sect1;
//		}
//		if (0 < actorData.weaponSwitchTimeout[1])
//		{
//			goto sect1;
//		}
//		auto addr = actorData.actionData[3];
//		auto & timeout = *reinterpret_cast<float32 *>(addr + 0x348);
//		actorData.weaponSwitchTimeout[0] = timeout;
//		actorData.weaponSwitchTimeout[1] = timeout;
//
//		auto & queuedWeaponIndex = actorData.weaponIndex[1];
//
//
//		if (queuedWeaponIndex > 0)
//		{
//			queuedWeaponIndex--;
//		}
//		else
//		{
//			queuedWeaponIndex = 2;
//		}
//
//
//
//
//		auto g_pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);
//		auto hud = *reinterpret_cast<byte8 **>(g_pool[11]);
//
//		// @Todo: In the future just update the weapon icon and use 0.
//		func_280160
//		(
//			hud,
//			(queuedWeaponIndex < 2) ? 1 : 0,
//			(queuedWeaponIndex < 2) ? queuedWeaponIndex : 0,
//			0
//		);
//		*reinterpret_cast<bool *>(reinterpret_cast<byte8 *>(&actorData) + 0x648C) = true;
//		func_1EB0E0(actorData, 4);
//
//		if (actorData.devil || (actorData.devilState == 1))
//		{
//			func_1F92C0(actorData, 1);
//			func_1F97F0(actorData, true);
//		}
//
//
//
//	}
//	sect1:;
//
//	return true;
//}



// @Todo: Controller.

bool WeaponSwitchDante(ACTOR_DATA_DANTE & actorData)
{
	if (actorData.devilState == 2)
	{
		return true;
	}
	if (actorData.moveOnly)
	{
		return false;
	}

	//{
	//	auto & meleeWeaponIndex = actorData.weaponIndex[0];
	//	auto & meleeWeaponSwitchTimeout = actorData.weaponSwitchTimeout[0];

	//	if (!(actorData.buttons[2] & GetBinding(ACTION_CHANGE_DEVIL_ARMS)))
	//	{
	//		goto sect0;
	//	}
	//	if (0 < meleeWeaponSwitchTimeout)
	//	{
	//		goto sect0;
	//	}

	//	auto & timeout = *reinterpret_cast<float32 *>(actorData.actionData[3] + 0x2F4);
	//	meleeWeaponSwitchTimeout = timeout;

	//	if (meleeWeaponIndex < 1)
	//	{
	//		meleeWeaponIndex++;
	//	}
	//	else
	//	{
	//		meleeWeaponIndex = 0;
	//	}

	//	auto g_pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);
	//	auto hud = *reinterpret_cast<byte8 **>(g_pool[11]);

	//	func_280120(hud, 1, meleeWeaponIndex);

	//	func_1EB0E0(actorData, 4);

	//	if (actorData.devil || (actorData.devilState == 1))
	//	{
	//		func_1F92C0(actorData, 1);
	//		func_1F97F0(actorData, true);
	//	}
	//}
	//sect0:;


	auto & gamepad = GetGamepad(0);


	{
		if (!(gamepad.buttons[2] & GetBinding(BINDING_CHANGE_DEVIL_ARMS)))
		{
			goto sect0;
		}
		if (0 < actorData.meleeWeaponSwitchTimeout)
		{
			goto sect0;
		}

		//auto & timeout = *reinterpret_cast<float32 *>(actorData.actionData[3] + 0x2F4);
		float32 timeout = 1;
		actorData.meleeWeaponSwitchTimeout = timeout;




		//actorData.meleeWeaponIndex++;

		//if (actorData.meleeWeaponIndex >= 2)
		//{
		//	actorData.meleeWeaponIndex = 0;
		//}


		//actorData.meleeWeaponIndex = (IsWeaponActive(actorData, actorData.meleeWeaponMap[0])) ? 1 : 0;

		
		if (!IsWeaponActive(actorData, actorData.meleeWeaponMap[0]))
		{
			actorData.meleeWeaponIndex = 0;
		}
		else
		{
			actorData.meleeWeaponIndex = 1;
		}












		actorData.newMeleeWeaponIndex++;

		if (actorData.newMeleeWeaponIndex >= actorData.newMeleeWeaponCount)
		{
			actorData.newMeleeWeaponIndex = 0;
		}


		if (actorData.newMeleeWeaponMap[actorData.newMeleeWeaponIndex] != WEAPON_VERGIL_YAMATO)
		{
			actorData.meleeWeaponMap[actorData.meleeWeaponIndex] = actorData.newMeleeWeaponMap[actorData.newMeleeWeaponIndex];
			actorData.meleeWeaponData[actorData.meleeWeaponIndex] = actorData.newMeleeWeaponData[actorData.newMeleeWeaponIndex];
		}















		{
			auto & id = actorData.newMeleeWeaponMap[actorData.newMeleeWeaponIndex];
			HUD_UpdateWeaponIcon(2, HUD_weaponIcon[id].model, HUD_weaponIcon[id].texture);
		}


		//HUD_UpdateWeaponIcon(0, HUD_weaponIcon[actorData.newMeleeWeaponMap[actorData]])


		auto pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);
		auto hud = *reinterpret_cast<byte8 **>(pool[11]);
		func_280120(hud, 1, 0);

		func_1EB0E0(actorData, 4);

		//if (actorData.devil || (actorData.devilState == 1))
		//{
		//	func_1F92C0(actorData, 1);
		//	func_1F97F0(actorData, true);
		//}
	}
	sect0:;




	return true;










	//{
	//	auto & rangedWeaponIndex = actorData.weaponIndex[1];
	//	auto & rangedWeaponSwitchTimeout = actorData.weaponSwitchTimeout[1];

	//	if (!(actorData.buttons[2] & GetBinding(ACTION_CHANGE_GUN)))
	//	{
	//		goto sect1;
	//	}
	//	if (0 < rangedWeaponSwitchTimeout)
	//	{
	//		goto sect1;
	//	}

	//	auto & timeout = *reinterpret_cast<float32 *>(actorData.actionData[3] + 0x2F4);
	//	rangedWeaponSwitchTimeout = timeout;

	//	if (rangedWeaponIndex < 3)
	//	{
	//		rangedWeaponIndex++;
	//	}
	//	else
	//	{
	//		rangedWeaponIndex = 2;
	//	}

	//	auto g_pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);
	//	auto hud = *reinterpret_cast<byte8 **>(g_pool[11]);

	//	func_280120(hud, 0, (rangedWeaponIndex - 2));

	//	func_1EB0E0(actorData, 7);
	//	func_1EB0E0(actorData, 9);

	//	if (!(actorData.motionState2[1] & MOTION_STATE_BUSY))
	//	{
	//		if (actorData.buttons[0] & GetBinding(ACTION_LOCK_ON))
	//		{
	//			auto & modelData = actorData.modelData[actorData.activeModelIndex];

	//			uint8 id = 0;
	//			uint8 index = 0;
	//			byte8 * motionFile = 0;

	//			actorData.activeWeapon = actorData.weaponMap[rangedWeaponIndex];

	//			id = (pl000_00_3 + actorData.activeWeapon);
	//			index = actorData.motionData[1].index;
	//			motionFile = File_cacheFile[id][index];

	//			func_8AC80(modelData, BODY_PART_LOWER, motionFile, 0, false);
	//		}
	//	}
	//}
	//sect1:;

	return true;
}






void Actor_Init()
{













	//{
	//	// Walk, Run
	//	// Swordmaster, Trickster Dash, Royalguard Release
	//	// Melee Attack
	//	constexpr byte8 sect0[] =
	//	{
	//		0xF3, 0x0F, 0x11, 0x8B, 0x80, 0x00, 0x00, 0x00, //movss [rbx+00000080],xmm1
	//	};
	//	constexpr byte8 sect1[] =
	//	{
	//		0x48, 0x8B, 0xCB, //mov rcx,rbx
	//	};
	//	auto func = CreateFunction(UpdatePosition, (appBaseAddr + 0x1FC027), true, true, sizeof(sect0), sizeof(sect1));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	memcpy(func.sect1, sect1, sizeof(sect1));
	//	WriteJump((appBaseAddr + 0x1FC01F), func.addr, 3);
	//	/*
	//	dmc3.exe+1FC01F - F3 0F11 8B 80000000 - movss [rbx+00000080],xmm1
	//	dmc3.exe+1FC027 - E9 4E030000         - jmp dmc3.exe+1FC37A
	//	*/
	//}







	//{
	//	constexpr byte8 sect2[] =
	//	{
	//		0x84, 0xC0,                   //test al,al
	//		0x74, 0x05,                   //je short
	//		0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc3.exe+1F5450
	//	};
	//	auto func = CreateFunction(FreeWalk, (appBaseAddr + 0x1F6FD1), true, false, 0, 0, sizeof(sect2));
	//	memcpy(func.sect2, sect2, sizeof(sect2));
	//	WriteCall((func.sect2 + 4), (appBaseAddr + 0x1F5450));
	//	//WriteJump((appBaseAddr + 0x1F6FCC), func.addr);
	//	/*
	//	dmc3.exe+1F6FCC - E8 7FE4FFFF - call dmc3.exe+1F5450
	//	dmc3.exe+1F6FD1 - E9 02020000 - jmp dmc3.exe+1F71D8
	//	*/
	//}






	//{
	//	constexpr byte8 sect1[] =
	//	{
	//		0x4C, 0x8B, 0xC3, //mov r8,rbx
	//	};
	//	auto func = CreateFunction(WritePosition_1FC017, (appBaseAddr + 0x1FC027), true, true, 0, sizeof(sect1));
	//	memcpy(func.sect1, sect1, sizeof(sect1));
	//	//WriteJump((appBaseAddr + 0x1FC017), func.addr, 3);
	//	/*
	//	dmc3.exe+1FC017 - F3 0F11 83 88000000 - movss [rbx+00000088],xmm0
	//	dmc3.exe+1FC01F - F3 0F11 8B 80000000 - movss [rbx+00000080],xmm1
	//	dmc3.exe+1FC027 - E9 4E030000         - jmp dmc3.exe+1FC37A
	//	*/
	//}






	//{
	//	constexpr byte8 sect0[] =
	//	{
	//		0x66, 0x89, 0xAE, 0xB0, 0x39, 0x00, 0x00, //mov [rsi+000039B0],bp
	//	};
	//	constexpr byte8 sect1[] =
	//	{
	//		0x48, 0x8B, 0xCE, //mov rcx,rsi
	//	};
	//	auto func = CreateFunction(WriteLowerBodyMotionData, (appBaseAddr + 0x1EFC97), true, true, sizeof(sect0), sizeof(sect1));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	memcpy(func.sect1, sect1, sizeof(sect1));
	//	WriteJump((appBaseAddr + 0x1EFC90), func.addr, 2);
	//	/*
	//	dmc3.exe+1EFC90 - 66 89 AE B0390000       - mov [rsi+000039B0],bp
	//	dmc3.exe+1EFC97 - C7 86 C2390000 00000000 - mov [rsi+000039C2],00000000
	//	*/
	//}
	//{
	//	constexpr byte8 sect0[] =
	//	{
	//		0x66, 0x89, 0xAE, 0xB2, 0x39, 0x00, 0x00, //mov [rsi+000039B2],bp
	//	};
	//	constexpr byte8 sect1[] =
	//	{
	//		0x48, 0x8B, 0xCE, //mov rcx,rsi
	//	};
	//	auto func = CreateFunction(WriteUpperBodyMotionData, (appBaseAddr + 0x1EFC8D), true, true, sizeof(sect0), sizeof(sect1));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	memcpy(func.sect1, sect1, sizeof(sect1));
	//	WriteJump((appBaseAddr + 0x1EFC86), func.addr, 2);
	//	/*
	//	dmc3.exe+1EFC86 - 66 89 AE B2390000 - mov [rsi+000039B2],bp
	//	dmc3.exe+1EFC8D - 8D 51 01          - lea edx,[rcx+01]
	//	*/
	//}










	LogFunction();

	// Adjust actor data size.
	{
		constexpr uint32 size = (0xB8C0 + 512);
		Write<uint32>((appBaseAddr + 0x1DE8B4), size); // Vergil
		Write<uint32>((appBaseAddr + 0x1DE9CD), size); // Lady
		Write<uint32>((appBaseAddr + 0x1DEAC9), size); // Bob
		Write<uint32>((appBaseAddr + 0x1DEBE2), size); // Dante
	}





	//{
	//	constexpr byte8 sect0[] =
	//	{
	//		0x48, 0x8B, 0x5C, 0x24, 0x20,       //mov rbx,[rsp+20]
	//		0x84, 0xC0,                         //test al,al
	//		0x0F, 0x84, 0x00, 0x00, 0x00, 0x00, //je dmc3.exe+1E5F57
	//	};
	//	auto func = CreateFunction(LogMotionData, (appBaseAddr + 0x1E5F57), true, true, sizeof(sect0));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	WriteAddress((func.sect0 + 7), (appBaseAddr + 0x1E5F57), 6);
	//	//WriteJump((appBaseAddr + 0x1E5F52), func.addr);
	//	/*
	//	dmc3.exe+1E5F52 - 48 8B 5C 24 20 - mov rbx,[rsp+20]
	//	dmc3.exe+1E5F57 - 48 8B 6C 24 28 - mov rbp,[rsp+28]
	//	*/
	//}



	//{
	//	constexpr byte8 sect0[] =
	//	{
	//		0x89, 0x83, 0x64, 0x3E, 0x00, 0x00, //mov [rbx+00003E64],eax
	//	};
	//	constexpr byte8 sect1[] =
	//	{
	//		0x48, 0x8B, 0xCB, //mov rcx,rbx
	//	};
	//	auto func = CreateFunction(WriteMotionState, (appBaseAddr + 0x1E0510), true, true, sizeof(sect0), sizeof(sect1));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	memcpy(func.sect1, sect1, sizeof(sect1));
	//	WriteJump((appBaseAddr + 0x1E050A), func.addr, 1);
	//	/*
	//	dmc3.exe+1E050A - 89 83 643E0000 - mov [rbx+00003E64],eax
	//	dmc3.exe+1E0510 - 48 83 C4 40    - add rsp,40
	//	*/
	//}

	//{
	//	constexpr byte8 sect0[] =
	//	{
	//		0x89, 0x83, 0x64, 0x3E, 0x00, 0x00, //mov [rbx+00003E64],eax
	//	};
	//	constexpr byte8 sect1[] =
	//	{
	//		0x48, 0x8B, 0xCB, //mov rcx,rbx
	//	};
	//	auto func = CreateFunction(WriteMotionState, (appBaseAddr + 0x1E0952), true, true, sizeof(sect0), sizeof(sect1));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	memcpy(func.sect1, sect1, sizeof(sect1));
	//	WriteJump((appBaseAddr + 0x1E094C), func.addr, 1);
	//	/*
	//	dmc3.exe+1E094C - 89 83 643E0000 - mov [rbx+00003E64],eax
	//	dmc3.exe+1E0952 - 85 F6          - test esi,esi
	//	*/
	//}


	//{
	//	constexpr byte8 sect0[] =
	//	{
	//		0x89, 0x8B, 0x64, 0x3E, 0x00, 0x00, //mov [rbx+00003E64],ecx
	//	};
	//	constexpr byte8 sect1[] =
	//	{
	//		0x48, 0x8B, 0xCB, //mov rcx,rbx
	//	};
	//	auto func = CreateFunction(WriteMotionState, (appBaseAddr + 0x1E0AA8), true, true, sizeof(sect0), sizeof(sect1));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	memcpy(func.sect1, sect1, sizeof(sect1));
	//	WriteJump((appBaseAddr + 0x1E0AA2), func.addr, 1);
	//	/*
	//	dmc3.exe+1E0AA2 - 89 8B 643E0000        - mov [rbx+00003E64],ecx
	//	dmc3.exe+1E0AA8 - EB 0A                 - jmp dmc3.exe+1E0AB4
	//	*/
	//}

	//{
	//	constexpr byte8 sect0[] =
	//	{
	//		0x89, 0x83, 0x64, 0x3E, 0x00, 0x00, //mov [rbx+00003E64],eax
	//	};
	//	constexpr byte8 sect1[] =
	//	{
	//		0x48, 0x8B, 0xCB, //mov rcx,rbx
	//	};
	//	auto func = CreateFunction(WriteMotionState, (appBaseAddr + 0x1E0AB4), true, true, sizeof(sect0), sizeof(sect1));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	memcpy(func.sect1, sect1, sizeof(sect1));
	//	WriteJump((appBaseAddr + 0x1E0AAE), func.addr, 1);
	//	/*
	//	dmc3.exe+1E0AAE - 89 83 643E0000    - mov [rbx+00003E64],eax
	//	dmc3.exe+1E0AB4 - 83 BB 043E0000 12 - cmp dword ptr [rbx+00003E04],12
	//	*/
	//}



	//{
	//	constexpr byte8 sect0[] =
	//	{
	//		0x89, 0x91, 0x64, 0x3E, 0x00, 0x00, //mov [rcx+00003E64],edx
	//	};
	//	auto func = CreateFunction(WriteMotionState, (appBaseAddr + 0x1E0B7C), true, true, sizeof(sect0));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	WriteJump((appBaseAddr + 0x1E0B76), func.addr, 1);
	//	/*
	//	dmc3.exe+1E0B76 - 89 91 643E0000 - mov [rcx+00003E64],edx
	//	dmc3.exe+1E0B7C - 8B C2          - mov eax,edx
	//	*/
	//}

	//{
	//	constexpr byte8 sect0[] =
	//	{
	//		0x89, 0x83, 0x64, 0x3E, 0x00, 0x00, //mov [rbx+00003E64],eax
	//	};
	//	constexpr byte8 sect1[] =
	//	{
	//		0x48, 0x8B, 0xCB, //mov rcx,rbx
	//	};
	//	auto func = CreateFunction(WriteMotionState, (appBaseAddr + 0x1E146F), true, true, sizeof(sect0), sizeof(sect1));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	memcpy(func.sect1, sect1, sizeof(sect1));
	//	WriteJump((appBaseAddr + 0x1E1469), func.addr, 1);
	//	/*
	//	dmc3.exe+1E1469 - 89 83 643E0000    - mov [rbx+00003E64],eax
	//	dmc3.exe+1E146F - 40 88 B3 103E0000 - mov [rbx+00003E10],sil
	//	*/
	//}


	//{
	//	constexpr byte8 sect0[] =
	//	{
	//		0x89, 0x91, 0x64, 0x3E, 0x00, 0x00, //mov [rcx+00003E64],edx
	//	};
	//	auto func = CreateFunction(WriteMotionState, (appBaseAddr + 0x1E175E), true, true, sizeof(sect0));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	WriteJump((appBaseAddr + 0x1E1758), func.addr, 1);
	//	/*
	//	dmc3.exe+1E1758 - 89 91 643E0000 - mov [rcx+00003E64],edx
	//	dmc3.exe+1E175E - 8B C2          - mov eax,edx
	//	*/
	//}




















	//{
	//	constexpr byte8 sect2[] =
	//	{
	//		0x84, 0xC0,                   //test al,al
	//		0x74, 0x01,                   //je short
	//		0xC3,                         //ret
	//		0x48, 0x89, 0x5C, 0x24, 0x08, //mov [rsp+08],rbx
	//	};
	//	auto func = CreateFunction(PlayMotion, (appBaseAddr + 0x1EFB95), true, false, 0, 0, sizeof(sect2));
	//	memcpy(func.sect2, sect2, sizeof(sect2));
	//	//WriteJump((appBaseAddr + 0x1EFB90), func.addr);
	//	/*
	//	dmc3.exe+1EFB90 - 48 89 5C 24 08 - mov [rsp+08],rbx
	//	dmc3.exe+1EFB95 - 48 89 6C 24 10 - mov [rsp+10],rbp
	//	*/
	//}



	//{
	//	constexpr byte8 sect0[] =
	//	{
	//		0x89, 0x83, 0x64, 0x3E, 0x00, 0x00, //mov [rbx+00003E64],eax
	//	};
	//	constexpr byte8 sect1[] =
	//	{
	//		0x48, 0x8B, 0xCB, //mov rcx,rbx
	//	};
	//	auto func = CreateFunction(WriteMotionState, (appBaseAddr + 0x1E0952), true, true, sizeof(sect0), sizeof(sect1));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	memcpy(func.sect1, sect1, sizeof(sect1));
	//	//WriteJump((appBaseAddr + 0x1E094C), func.addr, 1);
	//	/*
	//	dmc3.exe+1E094C - 89 83 643E0000 - mov [rbx+00003E64],eax
	//	dmc3.exe+1E0952 - 85 F6          - test esi,esi
	//	*/
	//}












	// Disable Vergil Weapon Switch Controller
	{
		byte8 sect0[] =
		{
			0xB0, 0x01, //mov al,01
			0xC3,       //ret
			0x90,       //nop
			0x90,       //nop
		};
		vp_memcpy((appBaseAddr + 0x1E6DD0), sect0, sizeof(sect0));
	}




	


	Write<uint32>((appBaseAddr + 0x1EBD19), offsetof(ACTOR_DATA, newGamepad));









	{
		Write<byte8>((appBaseAddr + 0x27E800), 0xEB);
		Write<byte8>((appBaseAddr + 0x27DF3E), 0xEB);
		Write<byte16>((appBaseAddr + 0x280DB9), 0xE990);
	}









	// Add missing lower body update when switching ranged weapons with Dante.

	//{
	//	byte8 sect0[] =
	//	{
	//		0xE8, 0x00, 0x00, 0x00, 0x00,                   //call dmc3.exe+1F99F0
	//		0x48, 0x8B, 0xCB,                               //mov rcx,rbx
	//		0x31, 0xD2,                                     //xor edx,edx
	//		0x45, 0x31, 0xC9,                               //xor r9d,r9d
	//		0xF3, 0x0F, 0x10, 0x15, 0x00, 0x00, 0x00, 0x00, //movss xmm2,[dmc3.exe+4C6068]
	//		0xE8, 0x00, 0x00, 0x00, 0x00,                   //call dmc3.exe+1F99F0
	//	};
	//	auto func = CreateFunction(0, (appBaseAddr + 0x1F4F98), false, true, sizeof(sect0));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	WriteAddress(func.sect0, (appBaseAddr + 0x1F99F0), 5);
	//	WriteAddress((func.sect0 + 0xD), (appBaseAddr + 0x4C6068), 8);
	//	WriteAddress((func.sect0 + 0x15), (appBaseAddr + 0x1F99F0), 5);
	//	//WriteJump((appBaseAddr + 0x1F4F93), func.addr);
	//	/*
	//	dmc3.exe+1F4F93 - E8 584A0000       - call dmc3.exe+1F99F0
	//	dmc3.exe+1F4F98 - 80 BB AE3E0000 01 - cmp byte ptr [rbx+00003EAE],01
	//	*/
	//}













	//{
	//	auto func = CreateFunction(WeaponSwitchVergil, 0, true, false);
	//	WriteCall((appBaseAddr + 0x1E25E1), func.addr);
	//}
	{
		auto func = CreateFunction(WeaponSwitchDante, 0, true, false);
		WriteCall((appBaseAddr + 0x1E25EB), func.addr);
	}









	RegisterWeapon_Init();

	{
		byte8 sect2[] =
		{
			0x84, 0xC0,                   //test al,al
			0x74, 0x05,                   //je short
			0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc3.exe+1FDE10
		};
		//for (uint8 index = 0; index < countof(IsWeaponReadyProxyHelper); index++)

		//for_each(index, 0, countof(IsWeaponReadyProxyHelper))
		const_for_all(index, countof(IsWeaponReadyProxyHelper))
		{
			auto & item = IsWeaponReadyProxyHelper[index];

			byte8 * jumpAddr = 0;
			FUNC func = {};

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
			IsWeaponReadyProxyFuncAddr[index] = func.addr;
		}
	}











	//// @Research: Lady has different actor_data size. Geez, quite the turn.

	//// Increase ACTOR_DATA size.
	//{
	//	constexpr uint32 size = (0xB8C0 + 512);
	//	Write<uint32>((appBaseAddr + 0x1DE5FA), size);
	//	Write<uint32>((appBaseAddr + 0x1DE67A), size);
	//	Write<uint32>((appBaseAddr + 0x1DE8B4), size);
	//	Write<uint32>((appBaseAddr + 0x1DEBE2), size);
	//}

	{
		constexpr byte8 sect0[] =
		{
			0x66, 0x23, 0x83, 0x00, 0x00, 0x00, 0x00, //and ax,[rbx+0000B8C0]
			0x66, 0x89, 0x83, 0xE0, 0x74, 0x00, 0x00, //mov [rbx+000074E0],ax
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x1EBD3B), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*(byte32 *)(func.sect0 + 3) = offsetof(ACTOR_DATA_DANTE, newButtonMask);
		WriteJump((appBaseAddr + 0x1EBD34), func.addr, 2);
		/*
		dmc3.exe+1EBD34 - 66 89 83 E0740000 - mov [rbx+000074E0],ax
		dmc3.exe+1EBD3B - 48 8D 0D CE8CB600 - lea rcx,[dmc3.exe+D54A10]
		*/
	}


	{
		constexpr byte8 sect0[] =
		{
			0x66, 0x23, 0x83, 0x00, 0x00, 0x00, 0x00, //and ax,[rbx+0000B8C0]
			0x66, 0x89, 0x83, 0xE2, 0x74, 0x00, 0x00, //mov [rbx+000074E2],ax
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x1EBD5B), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*(byte32 *)(func.sect0 + 3) = offsetof(ACTOR_DATA_DANTE, newButtonMask);
		WriteJump((appBaseAddr + 0x1EBD54), func.addr, 2);
		/*
		dmc3.exe+1EBD54 - 66 89 83 E2740000 - mov [rbx+000074E2],ax
		dmc3.exe+1EBD5B - 66 23 CA          - and cx,dx
		*/
	}

	{
		constexpr byte8 sect0[] =
		{
			0x66, 0x23, 0x8B, 0x00, 0x00, 0x00, 0x00, //and cx,[rbx+0000B8C0]
			0x66, 0x89, 0x8B, 0xE4, 0x74, 0x00, 0x00, //mov [rbx+000074E4],cx
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x1EBD6B), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*(byte32 *)(func.sect0 + 3) = offsetof(ACTOR_DATA_DANTE, newButtonMask);
		WriteJump((appBaseAddr + 0x1EBD64), func.addr, 2);
		/*
		dmc3.exe+1EBD64 - 66 89 8B E4740000 - mov [rbx+000074E4],cx
		dmc3.exe+1EBD6B - 66 23 D0          - and dx,ax
		*/
	}


	{
		constexpr byte8 sect0[] =
		{
			0x66, 0x23, 0x93, 0x00, 0x00, 0x00, 0x00, //and dx,[rbx+0000B8C0]
			0x66, 0x89, 0x93, 0xE6, 0x74, 0x00, 0x00, //mov [rbx+000074E6],dx
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x1EBD7C), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*(byte32 *)(func.sect0 + 3) = offsetof(ACTOR_DATA_DANTE, newButtonMask);
		WriteJump((appBaseAddr + 0x1EBD75), func.addr, 2);
		/*
		dmc3.exe+1EBD75 - 66 89 93 E6740000 - mov [rbx+000074E6],dx
		dmc3.exe+1EBD7C - 33 D2             - xor edx,edx
		*/
	}

	{
		constexpr byte8 sect0[] =
		{
			0x80, 0xBB, 0x00, 0x00, 0x00, 0x00, 0x01, //cmp byte ptr [rbx+0000B8C0],01
			0x74, 0x03,                               //je short
			0x66, 0x31, 0xC0,                         //xor ax,ax
			0x66, 0x89, 0x83, 0x0A, 0x75, 0x00, 0x00, //mov [rbx+0000750A],ax
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x1EBEA4), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*reinterpret_cast<uint32 *>(func.sect0 + 2) = offsetof(ACTOR_DATA, newEnableLeftStick);
		WriteJump((appBaseAddr + 0x1EBE9D), func.addr, 2);
		/*
		dmc3.exe+1EBE9D - 66 89 83 0A750000   - mov [rbx+0000750A],ax
		dmc3.exe+1EBEA4 - F3 0F10 8B DC3E0000 - movss xmm1,[rbx+00003EDC]
		*/
	}

























	//Write<byte32>((appBaseAddr + 0x1EBD19), offsetof(ACTOR_DATA, gamepad));
}
