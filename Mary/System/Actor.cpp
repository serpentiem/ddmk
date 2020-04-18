#include "Actor.h"

vector<byte8 *, 128> System_Actor_actorBaseAddr;

PrivateStart;

// @Todo: Create functions instead and add stringItemOff.


// @Todo: Constexpr and add to vars.

struct MotionHelper
{
	uint8 motionId;
	uint16 cacheFileId;
};

constexpr MotionHelper motionHelperDante[] =
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

constexpr MotionHelper motionHelperBob[] =
{
	{ MOTION_GROUP_BOB_BASE       , pl001_00_0  },
	{ MOTION_GROUP_BOB_DAMAGE     , pl001_00_1  },
	{ MOTION_GROUP_BOB_TAUNTS     , pl001_00_2  },
	{ MOTION_GROUP_BOB_MELEE_STYLE, pl001_00_31 },
};

constexpr MotionHelper motionHelperLady[] =
{
	{ MOTION_GROUP_LADY_BASE      , pl002_00_0  },
	{ MOTION_GROUP_LADY_DAMAGE    , pl002_00_1  },
	{ MOTION_GROUP_LADY_TAUNTS    , pl002_00_2  },
	{ MOTION_GROUP_LADY_KALINA_ANN, pl000_00_12 },
};

constexpr MotionHelper motionHelperVergil[] =
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
	if (!(actorData.motionState2[1] & MOTION_STATE_BUSY))
	{
		return false;
	}
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
		if ((weapon == WEAPON_VERGIL_YAMATO) && (actorData.motionData[1].group == MOTION_GROUP_VERGIL_FORCE_EDGE))
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
		weaponIndex = actorData.weaponIndex[1];
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

	if constexpr (typematch(T, ACTOR_DATA_VERGIL))
	{
		if (actorData.weaponIndex[0] != actorData.weaponIndex[1])
		{
			actorData.weaponIndex[0] = actorData.weaponIndex[1];
		}
	}

	if (weaponMap[weaponIndex] == weapon)
	{
		return true;
	}

	if constexpr (typematch(T, ACTOR_DATA_VERGIL))
	{
		if ((weapon == WEAPON_VERGIL_YAMATO) && (weaponMap[weaponIndex] == WEAPON_VERGIL_FORCE_EDGE))
		{
			return true;
		}
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

byte8 * IsWeaponReadyProxyFuncAddr[countof(IsWeaponReadyProxyHelper)] = {};

void ToggleUpdateWeapon(bool enable)
{
	LogFunction(enable);

	for_all(index, countof(IsWeaponReadyProxyHelper))
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


















void UpdateActorDante(byte8 * baseAddr)
{
	auto & actorData = *reinterpret_cast<ACTOR_DATA *>(baseAddr);




	actorData.devilModelMetadata.rebellion.submodelMetadata[0].submodelIndex = 255;
	actorData.devilModelMetadata.rebellion.submodelMetadata[1].submodelIndex = 255;
	actorData.devilModelMetadata.cerberus.submodelMetadata[0].submodelIndex = 255;
	actorData.devilModelMetadata.nevan.submodelMetadata[0].submodelIndex = 255;
	actorData.devilModelMetadata.nevan.submodelMetadata[1].submodelIndex = 255;
	actorData.devilModelMetadata.beowulf.submodelMetadata[0].submodelIndex = 255;
	actorData.devilModelMetadata.sparda.submodelMetadata[0].submodelIndex = 255;





	System_File_UpdateFileItems(&actorData);

	Cosmetics_Model_UpdateModelDante[COSTUME_DANTE_DEFAULT](baseAddr);
	



	Cosmetics_Model_UpdateDevilModelDante[DEVIL_DANTE_REBELLION](baseAddr, 1);
	Cosmetics_Model_UpdateDevilModelDante[DEVIL_DANTE_CERBERUS](baseAddr, 2);





	//for (uint8 index = 0; index < countof(motionHelperDante); index++)
	for_all(index, countof(motionHelperDante))
	{
		auto & motionId    = motionHelperDante[index].motionId;
		auto & cacheFileId = motionHelperDante[index].cacheFileId;

		actorData.motionArchive[motionId] = System_File_cacheFile[cacheFileId];
	}





	func_1EF040(baseAddr, 0);
	func_1EEF80(baseAddr);
	func_1EF040(baseAddr, 3);





	actorData.actionData[0] = *(byte8 **)(appBaseAddr + 0x590598);
	actorData.actionData[1] = *(byte8 **)(appBaseAddr + 0x58A2A0);
	actorData.actionData[2] = (appBaseAddr + 0x5905B0);
	actorData.actionData[3] = System_File_cacheFile[pl000][9];
	actorData.actionData[4] = System_File_cacheFile[pl000][10];
	actorData.actionData[5] = System_File_cacheFile[pl000][11];

	func_2EE3D0((baseAddr + 0x3C50));
	func_1FAF40(baseAddr);
}

typedef byte8 *(__fastcall * RegisterWeapon_t)(ACTOR_DATA & actorData, uint32 id);

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




void UpdateWeaponDante(ACTOR_DATA_DANTE & actorData)
{
	constexpr uint32 size = (offsetof(ACTOR_DATA, styleRank) - offsetof(ACTOR_DATA, weaponData));
	memset(actorData.weaponData, 0, size);

	actorData.weaponData[0] = RegisterWeapon[WEAPON_DANTE_REBELLION  ](actorData, 0);
	actorData.weaponData[0] = RegisterWeapon[WEAPON_DANTE_CERBERUS   ](actorData, 0);
	actorData.weaponData[0] = RegisterWeapon[WEAPON_DANTE_EBONY_IVORY](actorData, 0);
	actorData.weaponData[0] = RegisterWeapon[WEAPON_DANTE_KALINA_ANN ](actorData, 9);

	actorData.weaponFlags[4] = 4;
}

ACTOR_DATA_DANTE & CreateActorDante()
{
	auto g_pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);
	auto sessionData = (g_pool[1] + 0x16C);

	auto & actorData = func_1DE820(CHAR_DANTE, 0, false);

	System_File_UpdateFileItemsLite();



	func_217B90(actorData, sessionData);
	func_212BE0(actorData);


	for_all(index, countof(motionHelperDante))
	{
		auto & motionId    = motionHelperDante[index].motionId;
		auto & cacheFileId = motionHelperDante[index].cacheFileId;

		actorData.motionArchive[motionId] = System_File_cacheFile[cacheFileId];
	}

	UpdateWeaponDante(actorData);




	func_1DFC20(actorData);

	return actorData;
}





void UpdateWeaponVergil(ACTOR_DATA_VERGIL & actorData)
{
	//auto & actorData = *reinterpret_cast<ACTOR_DATA *>(baseAddr);

	//auto baseAddr = reinterpret_cast<by>


	constexpr uint32 size = (offsetof(ACTOR_DATA, styleRank) - offsetof(ACTOR_DATA, weaponData));
	memset(actorData.weaponData, 0, size);

	actorData.weaponData[0] = RegisterWeapon[WEAPON_VERGIL_YAMATO](actorData, 0);
	actorData.weaponData[1] = RegisterWeapon[WEAPON_VERGIL_BEOWULF](actorData, 0);
	actorData.weaponData[2] = RegisterWeapon[WEAPON_VERGIL_FORCE_EDGE](actorData, 0);




	//actorData.weaponData[1] = RegisterWeapon[WEAPON_DANTE_CERBERUS   ](actorData, 0);
	//actorData.weaponData[2] = RegisterWeapon[WEAPON_DANTE_EBONY_IVORY](actorData, 0);
	//actorData.weaponData[3] = RegisterWeapon[WEAPON_DANTE_SHOTGUN    ](actorData, 0);

	//static_assert(offsetof(ACTOR_DATA, weaponFlags[4]) == 0x64D8);
	actorData.weaponFlags[4] = 4;
}


ACTOR_DATA_VERGIL & CreateActorVergil()
{
	auto g_pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);
	auto sessionData = (g_pool[1] + 0x16C);
	//auto baseAddr = func_1DE820(CHAR_VERGIL, 0, false);
	//auto & actorData = *reinterpret_cast<ACTOR_DATA_VERGIL *>(baseAddr);


	auto & actorData = func_1DE820(CHAR_VERGIL, 0, false);


	System_File_UpdateFileItemsLite();



	//actorData.collisionIndex = 1;


	//System_File_UpdateFileItems(actorData);
	



	func_223CB0(actorData, sessionData);
	func_220970(actorData);




	for_all(index, countof(motionHelperVergil))
	{
		auto & motionId    = motionHelperVergil[index].motionId;
		auto & cacheFileId = motionHelperVergil[index].cacheFileId;

		actorData.motionArchive[motionId] = System_File_cacheFile[cacheFileId];
	}



	UpdateWeaponVergil(actorData);







	func_1DFC20(actorData);
	//return *reinterpret_cast<ACTOR_DATA_VERGIL *>(baseAddr);

	return actorData;

}




















inline byte16 GetBinding(uint8 action)
{
	return (reinterpret_cast<byte16 *>(appBaseAddr + 0xD6CE8A))[action];
}




// @Todo: Add devil support and Nero Angelo exceptions.
// @Todo: Check for WEAPON_VOID and same weapon.
// @Todo: Create templates.

bool WeaponSwitchVergil(ACTOR_DATA_VERGIL & actorData)
{
	if (actorData.devilState == 2)
	{
		return true;
	}
	if (actorData.moveOnly)
	{
		return false;
	}

	
	{
		if (!(actorData.buttons[2] & GetBinding(ACTION_CHANGE_DEVIL_ARMS)))
		{
			goto sect0;
		}
		if (0 < actorData.weaponSwitchTimeout[0])
		{
			goto sect0;
		}
		auto addr = actorData.actionData[3];
		auto & timeout = *reinterpret_cast<float32 *>(addr + 0x348);
		actorData.weaponSwitchTimeout[0] = timeout;
		actorData.weaponSwitchTimeout[1] = timeout;

		auto & queuedWeaponIndex = actorData.weaponIndex[1];
		queuedWeaponIndex++;
		if (queuedWeaponIndex >= 3)
		{
			queuedWeaponIndex = 0;
		}

		auto g_pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);
		auto hud = *reinterpret_cast<byte8 **>(g_pool[11]);

		// @Todo: In the future just update the weapon icon and use 0.
		func_280160
		(
			hud,
			(queuedWeaponIndex < 2) ? 1 : 0,
			(queuedWeaponIndex < 2) ? queuedWeaponIndex : 0,
			1
		);
		*reinterpret_cast<bool *>(reinterpret_cast<byte8 *>(&actorData) + 0x648C) = true;
		func_1EB0E0(actorData, 4);

		if (actorData.devil || (actorData.devilState == 1))
		{
			func_1F92C0(actorData, 1);
			func_1F97F0(actorData, true);
		}
	}
	sect0:;





	{
		if (!(actorData.buttons[2] & GetBinding(ACTION_CHANGE_GUN)))
		{
			goto sect1;
		}
		if (0 < actorData.weaponSwitchTimeout[1])
		{
			goto sect1;
		}
		auto addr = actorData.actionData[3];
		auto & timeout = *reinterpret_cast<float32 *>(addr + 0x348);
		actorData.weaponSwitchTimeout[0] = timeout;
		actorData.weaponSwitchTimeout[1] = timeout;

		auto & queuedWeaponIndex = actorData.weaponIndex[1];


		if (queuedWeaponIndex > 0)
		{
			queuedWeaponIndex--;
		}
		else
		{
			queuedWeaponIndex = 2;
		}




		auto g_pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);
		auto hud = *reinterpret_cast<byte8 **>(g_pool[11]);

		// @Todo: In the future just update the weapon icon and use 0.
		func_280160
		(
			hud,
			(queuedWeaponIndex < 2) ? 1 : 0,
			(queuedWeaponIndex < 2) ? queuedWeaponIndex : 0,
			0
		);
		*reinterpret_cast<bool *>(reinterpret_cast<byte8 *>(&actorData) + 0x648C) = true;
		func_1EB0E0(actorData, 4);

		if (actorData.devil || (actorData.devilState == 1))
		{
			func_1F92C0(actorData, 1);
			func_1F97F0(actorData, true);
		}



	}
	sect1:;

	return true;
}



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

	{
		auto & meleeWeaponIndex = actorData.weaponIndex[0];
		auto & meleeWeaponSwitchTimeout = actorData.weaponSwitchTimeout[0];

		if (!(actorData.buttons[2] & GetBinding(ACTION_CHANGE_DEVIL_ARMS)))
		{
			goto sect0;
		}
		if (0 < meleeWeaponSwitchTimeout)
		{
			goto sect0;
		}

		auto & timeout = *reinterpret_cast<float32 *>(actorData.actionData[3] + 0x2F4);
		meleeWeaponSwitchTimeout = timeout;

		if (meleeWeaponIndex < 1)
		{
			meleeWeaponIndex++;
		}
		else
		{
			meleeWeaponIndex = 0;
		}

		auto g_pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);
		auto hud = *reinterpret_cast<byte8 **>(g_pool[11]);

		func_280120(hud, 1, meleeWeaponIndex);

		func_1EB0E0(actorData, 4);

		if (actorData.devil || (actorData.devilState == 1))
		{
			func_1F92C0(actorData, 1);
			func_1F97F0(actorData, true);
		}
	}
	sect0:;

	{
		auto & rangedWeaponIndex = actorData.weaponIndex[1];
		auto & rangedWeaponSwitchTimeout = actorData.weaponSwitchTimeout[1];

		if (!(actorData.buttons[2] & GetBinding(ACTION_CHANGE_GUN)))
		{
			goto sect1;
		}
		if (0 < rangedWeaponSwitchTimeout)
		{
			goto sect1;
		}

		auto & timeout = *reinterpret_cast<float32 *>(actorData.actionData[3] + 0x2F4);
		rangedWeaponSwitchTimeout = timeout;

		if (rangedWeaponIndex < 3)
		{
			rangedWeaponIndex++;
		}
		else
		{
			rangedWeaponIndex = 2;
		}

		auto g_pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);
		auto hud = *reinterpret_cast<byte8 **>(g_pool[11]);

		func_280120(hud, 0, (rangedWeaponIndex - 2));

		func_1EB0E0(actorData, 7);
		func_1EB0E0(actorData, 9);

		if (!(actorData.motionState2[1] & MOTION_STATE_BUSY))
		{
			if (actorData.buttons[0] & GetBinding(ACTION_LOCK_ON))
			{
				auto & modelData = actorData.modelData[actorData.activeModelIndex];

				uint8 id = 0;
				uint8 index = 0;
				byte8 * motionFile = 0;

				actorData.activeWeapon = actorData.weaponMap[rangedWeaponIndex];

				id = (pl000_00_3 + actorData.activeWeapon);
				index = actorData.motionData[1].index;
				motionFile = System_File_cacheFile[id][index];

				func_8AC80(modelData, BODY_PART_LOWER, motionFile, 0, false);
			}
		}
	}
	sect1:;

	return true;
}



// HUDIconHelper


// texture
// model

//constexpr uint8 HUDIconMap



//struct HUDIconHelper
//{
//	byte8 * model;
//	byte8 * texture;
//};

//HUDIconHelper hudIconHelper


HUDIconHelper styleIconDante[MAX_STYLE] = {};
HUDIconHelper styleIconVergil[MAX_STYLE] = {};
HUDIconHelper weaponIcon[MAX_WEAPON] = {};

constexpr uint8 styleIconMapDante[MAX_STYLE] =
{
	20,
	22,
	18,
	24,
	26,
	28,
};

constexpr uint8 weaponIconMapDante[] =
{
	42,
	44,
	46,
	48,
	50,
	30,
	32,
	34,
	36,
	38,
};

constexpr uint8 weaponIconMapVergil[] =
{
	42,
	44,
	30,
};





void UpdateStyleIcon
(
	uint8 style,
	byte8 * model,
	byte8 * texture
)
{
	auto addr = *reinterpret_cast<byte8 **>(appBaseAddr + 0xC90E28);
	if (!addr)
	{
		return;
	}
	addr -= 0x180;
	auto top    = *reinterpret_cast<byte8 **>(addr + 0x1B070);
	auto bottom = *reinterpret_cast<byte8 **>(addr + 0x1B078);

	auto styleIcon = (top + 0x3B80);

	func_897B0(styleIcon);
	func_89450(styleIcon);
	memset(styleIcon, 0, 0x780);
	func_89270(styleIcon);

	auto map = reinterpret_cast<uint8 *>(appBaseAddr + 0x4E9070);

	auto & effect = *reinterpret_cast<uint8 *>(top + 0x690E) = map[style];

	





	func_89960(styleIcon, model, texture);
	func_89E30(styleIcon, 1);
}






// @Todo: Move to vars.

enum HUD_TOP
{
	TOP_HIT_POINTS_FRAME,
	TOP_HIT_POINTS_BAR,
	TOP_HIT_POINTS_BACKGROUND,
	BOTTOM_HIT_POINTS_FRAME,
	BOTTOM_HIT_POINTS_BAR,
	BOTTOM_HIT_POINTS_BACKGROUND,
	MAGIC_ORBS,
	STYLE_ICON,
	RED_ORB_COUNTER,
	UNKNOWN_1,
	UNKNOWN_2,
	FLUX,
	UNKNOWN_3,
};

enum HUD_BOTTOM
{
	RANGED_WEAPON_1,
	RANGED_WEAPON_2,
	MELEE_WEAPON_1,
	MELEE_WEAPON_2,
};

constexpr uint32 hudTopOff[] =
{
	0x700,
	0xE80,
	0x1600,
	0x1D80,
	0x2500,
	0x2C80,
	0x3400,
	0x3B80,
	0x4300,
	0x4A80,
	0x5200,
	0x5980,
	0x6100,
};

constexpr uint32 hudBottomOff[] =
{
	0x880,
	0x1000,
	0x1780,
	0x1F00,
};



void UpdateWeaponIcon(uint8 index, byte8 * model, byte8 * texture)
{
	auto addr = *reinterpret_cast<byte8 **>(appBaseAddr + 0xC90E28);
	if (!addr)
	{
		return;
	}
	addr -= 0x180;
	auto top    = *reinterpret_cast<byte8 **>(addr + 0x1B070);
	auto bottom = *reinterpret_cast<byte8 **>(addr + 0x1B078);

	auto dest = (bottom + hudBottomOff[index]);

	func_897B0(dest);
	func_89450(dest);
	memset(dest, 0, 0x780);
	func_89270(dest);

	func_89960(dest, model, texture);
	func_89E30(dest, 1);
}



























void Reset(uint32 off)
{


	auto g_pool = reinterpret_cast<byte8 **>(appBaseAddr + 0xCF2520);

	auto dest = (g_pool[44] + off);

	//func_897B0(dest);
	//func_89450(dest);
	//memset(dest, 0, 0x780);
	//func_89270(dest);


	auto & visible = *reinterpret_cast<bool *>(dest + 0x18) = false;



}















void System_Actor_Init()
{
	LogFunction();


	Log("UpdateStyleIcon %llX", UpdateStyleIcon);
	Log("UpdateWeaponIcon %llX", UpdateWeaponIcon);



	{
		Write<byte8>((appBaseAddr + 0x27E800), 0xEB);
		Write<byte8>((appBaseAddr + 0x27DF3E), 0xEB);
		Write<byte16>((appBaseAddr + 0x280DB9), 0xE990);
	}


	
	// Init Icons
	{
		for_all(index, countof(styleIconMapDante))
		{
			auto & fileIndex = styleIconMapDante[index];
			styleIconDante[index].model   = System_File_cacheFile[id100][(fileIndex + 1)];
			styleIconDante[index].texture = System_File_cacheFile[id100][(fileIndex + 0)];
		}

		styleIconVergil[STYLE_VERGIL_DARK_SLAYER].model   = System_File_cacheFile[id100V][(18 + 1)];
		styleIconVergil[STYLE_VERGIL_DARK_SLAYER].texture = System_File_cacheFile[id100V][(18 + 0)];

		for_all(index, countof(weaponIconMapDante))
		{
			auto & fileIndex = weaponIconMapDante[index];
			weaponIcon[(WEAPON_DANTE_REBELLION + index)].model   = System_File_cacheFile[id100][(fileIndex + 1)];
			weaponIcon[(WEAPON_DANTE_REBELLION + index)].texture = System_File_cacheFile[id100][(fileIndex + 0)];
		}

		for_all(index, countof(weaponIconMapVergil))
		{
			auto & fileIndex = weaponIconMapVergil[index];
			weaponIcon[(WEAPON_VERGIL_YAMATO + index)].model   = System_File_cacheFile[id100V][(fileIndex + 1)];
			weaponIcon[(WEAPON_VERGIL_YAMATO + index)].texture = System_File_cacheFile[id100V][(fileIndex + 0)];
		}
	}


	for_all(index, countof(weaponIcon))
	{
		Log("%u %llX", index, weaponIcon[index].model);
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













	{
		auto func = CreateFunction(WeaponSwitchVergil, 0, true, false);
		WriteCall((appBaseAddr + 0x1E25E1), func.addr);
	}
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
		for_all(index, countof(IsWeaponReadyProxyHelper))
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
