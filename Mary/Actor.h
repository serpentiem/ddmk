#pragma once
#include "../Core/Core.h"

#include "ActorData.h"
#include "File.h"
#include "Internal.h"
#include "Input.h"
#include "Vars.h"

extern vector<byte8 *, 128> Actor_actorBaseAddr;




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









void ToggleUpdateWeapon(bool enable);
ACTOR_DATA_DANTE * CreateActorDante();
ACTOR_DATA_VERGIL * CreateActorVergil();

void Actor_Init();
