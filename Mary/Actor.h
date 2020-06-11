#pragma once
#include "../Core/Core.h"

#include "ActorData.h"
#include "File.h"
#include "HUD.h"
#include "Internal.h"
#include "Input.h"
#include "Vars.h"

extern Vector<byte8 *> Actor_actorBaseAddr;

// @Todo: Modules.

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

extern RegisterWeapon_t RegisterWeapon[MAX_WEAPON];

inline void UpdateModelPartitionConfigFunction
(
	ACTOR_DATA_DANTE & actorData,
	uint8 weapon
)
{
	actorData.newLastMeleeWeapon = weapon;

	auto & modelData = actorData.modelData[0];
	auto dest = func_89DE0(modelData);

	if (weapon == WEAPON_DANTE_BEOWULF)
	{
		func_2F7350(dest, 3);
		func_2F74E0(dest, 4);
		func_2F74E0(dest, 5);
		func_2F7350(dest, 6);
	}
	else
	{
		func_2F74E0(dest, 3);
		func_2F7350(dest, 4);
		func_2F7350(dest, 5);
		func_2F74E0(dest, 6);
	}
}

inline void UpdateModelPartitionConfig
(
	ACTOR_DATA_DANTE & actorData,
	uint8 weapon
)
{
	if (actorData.newLastMeleeWeapon == weapon)
	{
		return;
	}
	UpdateModelPartitionConfigFunction(actorData, weapon);
}

template <typename T>
struct GetCharacterId
{
	enum
	{
		value =
		(typematch(T, ACTOR_DATA_DANTE )) ? CHAR_DANTE  :
		(typematch(T, ACTOR_DATA_BOB   )) ? CHAR_BOB    :
		(typematch(T, ACTOR_DATA_LADY  )) ? CHAR_LADY   :
		(typematch(T, ACTOR_DATA_VERGIL)) ? CHAR_VERGIL :
		0
	};
};

template <uint8 character> struct GetActorDataType {};
template <> struct GetActorDataType<CHAR_DANTE > { typedef ACTOR_DATA_DANTE  value; };
template <> struct GetActorDataType<CHAR_BOB   > { typedef ACTOR_DATA_BOB    value; };
template <> struct GetActorDataType<CHAR_LADY  > { typedef ACTOR_DATA_LADY   value; };
template <> struct GetActorDataType<CHAR_VERGIL> { typedef ACTOR_DATA_VERGIL value; };

template <typename T> struct GetChildActorDataType {};
template <> struct GetChildActorDataType<ACTOR_DATA_DANTE > { typedef ACTOR_DATA_VERGIL value; };
template <> struct GetChildActorDataType<ACTOR_DATA_VERGIL> { typedef ACTOR_DATA_DANTE  value; };

template <typename T>
bool IsWeaponActive
(
	T & actorData,
	uint8 weapon
)
{
	auto & motionData = actorData.motionData[BODY_PART_UPPER];
	if (weapon == WEAPON_VOID)
	{
		return false;
	}
	if constexpr (typematch(T, ACTOR_DATA_DANTE))
	{
		if (motionData.group == (MOTION_GROUP_DANTE_REBELLION + weapon))
		{
			return true;
		}
		if (motionData.group == (MOTION_GROUP_DANTE_SWORDMASTER_REBELLION + weapon))
		{
			return true;
		}
	}
	else if constexpr (typematch(T, ACTOR_DATA_VERGIL))
	{
		if (motionData.group == (MOTION_GROUP_VERGIL_YAMATO + (weapon - WEAPON_VERGIL_YAMATO)))
		{
			return true;
		}
	}
	return false;
}

template <typename T>
bool IsWeaponActive(T & actorData)
{
	auto & motionData = actorData.motionData[BODY_PART_UPPER];
	if constexpr (typematch(T, ACTOR_DATA_DANTE))
	{
		if ((motionData.group >= MOTION_GROUP_DANTE_REBELLION) && (motionData.group <= MOTION_GROUP_DANTE_GUNSLINGER_KALINA_ANN))
		{
			return true;
		}
	}
	else if constexpr (typematch(T, ACTOR_DATA_VERGIL))
	{
		if ((motionData.group >= MOTION_GROUP_VERGIL_YAMATO) && (motionData.group <= MOTION_GROUP_VERGIL_FORCE_EDGE))
		{
			return true;
		}
	}
	return false;
}

template <typename T>
bool IsActive(T & actorData)
{
	auto & motionData = actorData.motionData[BODY_PART_UPPER];
	if constexpr (typematch(T, ACTOR_DATA_DANTE))
	{
		if ((motionData.group == MOTION_GROUP_DANTE_BASE) && (motionData.index == 14))
		{
			return true;
		}
		if ((motionData.group == MOTION_GROUP_DANTE_TAUNTS))
		{
			return true;
		}
	}
	else if constexpr (typematch(T, ACTOR_DATA_VERGIL))
	{
		if ((motionData.group == MOTION_GROUP_VERGIL_BASE) && (motionData.index == 14))
		{
			return true;
		}
		if ((motionData.group == MOTION_GROUP_VERGIL_TAUNTS))
		{
			return true;
		}
	}
	return IsWeaponActive(actorData);
}

void ToggleUpdateWeapon(bool enable);

template <typename T>
void InitActor
(
	T & actorData,
	byte8 * sessionData
)
{
	if constexpr      (typematch(T, ACTOR_DATA_DANTE )) { func_217B90(actorData, sessionData); }
	else if constexpr (typematch(T, ACTOR_DATA_BOB   )) { func_226F10(actorData, sessionData); }
	else if constexpr (typematch(T, ACTOR_DATA_LADY  )) { func_219660(actorData, sessionData); }
	else if constexpr (typematch(T, ACTOR_DATA_VERGIL)) { func_223CB0(actorData, sessionData); }
}

template <typename T>
void UpdateActor(T & actorData)
{
	if constexpr      (typematch(T, ACTOR_DATA_DANTE )) { func_212BE0(actorData); }
	else if constexpr (typematch(T, ACTOR_DATA_BOB   )) { func_225D70(actorData); }
	else if constexpr (typematch(T, ACTOR_DATA_LADY  )) { func_219260(actorData); }
	else if constexpr (typematch(T, ACTOR_DATA_VERGIL)) { func_220970(actorData); }
}

struct MotionArchiveHelper
{
	uint8 group;
	uint16 cacheFileId;
};

constexpr MotionArchiveHelper motionArchiveHelperDante[] =
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

constexpr MotionArchiveHelper motionArchiveHelperBob[] =
{
	{ MOTION_GROUP_BOB_BASE       , pl001_00_0  },
	{ MOTION_GROUP_BOB_DAMAGE     , pl001_00_1  },
	{ MOTION_GROUP_BOB_TAUNTS     , pl001_00_2  },
	{ MOTION_GROUP_BOB_MELEE_STYLE, pl001_00_31 },
};

constexpr MotionArchiveHelper motionArchiveHelperLady[] =
{
	{ MOTION_GROUP_LADY_BASE      , pl002_00_0  },
	{ MOTION_GROUP_LADY_DAMAGE    , pl002_00_1  },
	{ MOTION_GROUP_LADY_TAUNTS    , pl002_00_2  },
	{ MOTION_GROUP_LADY_KALINA_ANN, pl000_00_12 },
};

constexpr MotionArchiveHelper motionArchiveHelperVergil[] =
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

template <typename T>
void UpdateMotionArchives(T & actorData)
{
	constexpr uint8 count =
	(typematch(T, ACTOR_DATA_DANTE )) ? countof<uint8>(motionArchiveHelperDante ) :
	(typematch(T, ACTOR_DATA_BOB   )) ? countof<uint8>(motionArchiveHelperBob   ) :
	(typematch(T, ACTOR_DATA_LADY  )) ? countof<uint8>(motionArchiveHelperLady  ) :
	(typematch(T, ACTOR_DATA_VERGIL)) ? countof<uint8>(motionArchiveHelperVergil) :
	0;

	const MotionArchiveHelper * motionArchiveHelper =
	(typematch(T, ACTOR_DATA_DANTE )) ? motionArchiveHelperDante  :
	(typematch(T, ACTOR_DATA_BOB   )) ? motionArchiveHelperBob    :
	(typematch(T, ACTOR_DATA_LADY  )) ? motionArchiveHelperLady   :
	(typematch(T, ACTOR_DATA_VERGIL)) ? motionArchiveHelperVergil :
	0;

	for_all(uint8, index, count)
	{
		auto & group = motionArchiveHelper[index].group;
		auto & cacheFileId = motionArchiveHelper[index].cacheFileId;

		auto & metadata = File_staticFiles[cacheFileId];

		actorData.motionArchive[group] = File_dynamicFiles.Push(metadata.addr, metadata.size);
	}
}

template <typename T>
void UpdateMeleeWeapons
(
	T & actorData,
	uint8 player,
	uint8 entity
)
{
	if constexpr (typematch(T, ACTOR_DATA_DANTE))
	{
		memcpy(actorData.newMeleeWeapon, Config.Actor.meleeWeapon[player][entity][CHAR_DANTE], MAX_MELEE_WEAPON);

		actorData.newMeleeWeaponCount = Config.Actor.meleeWeaponCount[player][entity][CHAR_DANTE];

		if (actorData.newMeleeWeaponIndex >= actorData.newMeleeWeaponCount)
		{
			actorData.newMeleeWeaponIndex = 0;
		}

		for_all(uint8, index, MAX_MELEE_WEAPON_DANTE)
		{
			uint32 weapon = (WEAPON_DANTE_REBELLION + index);
			actorData.newMeleeWeaponData[index] = RegisterWeapon[weapon](actorData, weapon);
		}

		auto & newMeleeWeapon = actorData.newMeleeWeapon[actorData.newMeleeWeaponIndex];
		if ((newMeleeWeapon >= WEAPON_DANTE_REBELLION) && (newMeleeWeapon <= WEAPON_DANTE_BEOWULF))
		{
			actorData.meleeWeapon[0] = newMeleeWeapon;
			actorData.meleeWeaponData[0] = actorData.newMeleeWeaponData[(newMeleeWeapon - WEAPON_DANTE_REBELLION)];
		}
		else
		{
			actorData.meleeWeapon[0] = WEAPON_VOID;
		}
		actorData.meleeWeapon[1] = WEAPON_VOID;

		actorData.meleeWeaponIndex = 0;

		UpdateModelPartitionConfigFunction(actorData, newMeleeWeapon);
	}
	else if constexpr (typematch(T, ACTOR_DATA_VERGIL))
	{
		memcpy(actorData.newMeleeWeapon, Config.Actor.meleeWeapon[player][entity][CHAR_VERGIL], MAX_MELEE_WEAPON);

		actorData.newMeleeWeaponCount = Config.Actor.meleeWeaponCount[player][entity][CHAR_VERGIL];

		if (actorData.newMeleeWeaponIndex >= actorData.newMeleeWeaponCount)
		{
			actorData.newMeleeWeaponIndex = 0;
		}

		for_all(uint8, index, MAX_MELEE_WEAPON_VERGIL)
		{
			uint32 weapon = (WEAPON_VERGIL_YAMATO + index);
			actorData.newMeleeWeaponData[index] = RegisterWeapon[weapon](actorData, weapon);
		}

		actorData.meleeWeapon[0] = WEAPON_VERGIL_YAMATO;
		actorData.meleeWeapon[1] = WEAPON_VERGIL_BEOWULF;
		actorData.meleeWeapon[2] = WEAPON_VERGIL_FORCE_EDGE;
		actorData.meleeWeapon[3] = WEAPON_VOID;
		actorData.meleeWeapon[4] = WEAPON_VOID;

		actorData.meleeWeaponData[0] = actorData.newMeleeWeaponData[0];
		actorData.meleeWeaponData[1] = actorData.newMeleeWeaponData[1];
		actorData.meleeWeaponData[2] = actorData.newMeleeWeaponData[2];

		actorData.meleeWeaponStatus[4] = WEAPON_STATUS_DISABLED;
	}
}

template <typename T>
void UpdateRangedWeapons
(
	T & actorData,
	uint8 player,
	uint8 entity
)
{
	if constexpr (typematch(T, ACTOR_DATA_DANTE))
	{
		memcpy(actorData.newRangedWeapon, Config.Actor.rangedWeapon[player][entity][CHAR_DANTE], MAX_RANGED_WEAPON);

		actorData.newRangedWeaponCount = Config.Actor.rangedWeaponCount[player][entity][CHAR_DANTE];

		if (actorData.newRangedWeaponIndex >= actorData.newRangedWeaponCount)
		{
			actorData.newRangedWeaponIndex = 0;
		}

		for_all(uint8, index, MAX_RANGED_WEAPON_DANTE)
		{
			uint32 weapon = (WEAPON_DANTE_EBONY_IVORY + index);
			actorData.newRangedWeaponData[index] = RegisterWeapon[weapon](actorData, weapon);
		}

		auto & newRangedWeapon = actorData.newRangedWeapon[actorData.newRangedWeaponIndex];
		if ((newRangedWeapon >= WEAPON_DANTE_EBONY_IVORY) && (newRangedWeapon <= WEAPON_DANTE_KALINA_ANN))
		{
			actorData.rangedWeapon[0] = newRangedWeapon;
			actorData.rangedWeaponData[0] = actorData.newRangedWeaponData[(newRangedWeapon - WEAPON_DANTE_EBONY_IVORY)];
		}
		else
		{
			actorData.rangedWeapon[0] = WEAPON_VOID;
		}
		actorData.rangedWeapon[1] = WEAPON_VOID;
		actorData.rangedWeapon[2] = WEAPON_VOID;

		actorData.rangedWeaponIndex = 2;

		actorData.rangedWeaponStatus[2] = WEAPON_STATUS_DISABLED;

		actorData.rangedWeaponLevel[0] = 2;
		actorData.rangedWeaponLevel[1] = 2;
	}
}

template <typename T>
void UpdateWeapons
(
	T & actorData,
	uint8 player,
	uint8 entity
)
{
	memset((reinterpret_cast<byte8 *>(&actorData) + 0x648C), 0, (0x6510 - 0x648C));
	UpdateMeleeWeapons(actorData, player, entity);
	UpdateRangedWeapons(actorData, player, entity);
}

template <typename T>
T * CreateActor
(
	uint8 player,
	uint8 entity
)
{
	constexpr uint8 character = GetCharacterId<T>::value;

	auto g_pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);
	auto sessionData = (g_pool[1] + 0x16C);

	auto baseAddr = func_1DE820(character, 0, false);
	if (!baseAddr)
	{
		return 0;
	}

	auto & actorData = *reinterpret_cast<T *>(baseAddr);

	InitActor(actorData, sessionData);

	actorData.costume = Config.Actor.costume[player][entity][character];
	File_UpdateCostumeFileItems(actorData);

	UpdateActor(actorData);

	UpdateMotionArchives(actorData);

	UpdateWeapons(actorData, player, entity);

	func_1DFC20(actorData);


	//auto pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);


	//
	//func_23E560(pool[9], 0);



	return &actorData;
}

void Actor_Init();
