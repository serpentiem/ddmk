#pragma once
#include "../Core/Core.h"

#include "ActorData.h"
#include "File.h"
#include "HUD.h"
#include "Internal.h"
#include "Input.h"
#include "Vars.h"

extern vector<byte8 *, 128> Actor_actorBaseAddr;









//PrivateStart;

//template <typename T>
//bool ActorIsBusy(T & actorData)
//{
//	if (actorData.motionState3[1] & MOTION_STATE_BUSY)
//	{
//		return true;
//	}
//	return false;
//}

//PrivateEnd;



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































extern bool g_logMotionData;
extern uint8 g_motionGroup;
extern uint8 g_motionIndex;
extern void LogMotionData();



void ToggleUpdateWeapon(bool enable);
//ACTOR_DATA_DANTE * CreateActorDante();
//ACTOR_DATA_VERGIL * CreateActorVergil();

//
//ACTOR_DATA_DANTE * CreateActorDante
//(
//	uint8 entity,
//	uint8 actor
//);
//
//ACTOR_DATA_VERGIL * CreateActorVergil
//(
//	uint8 entity,
//	uint8 actor
//);


ACTOR_DATA_DANTE * CreateActorDante
(
	uint8 player,
	uint8 entity
);


ACTOR_DATA_VERGIL * CreateActorVergil
(
	uint8 player,
	uint8 entity
);



void Actor_Init();
