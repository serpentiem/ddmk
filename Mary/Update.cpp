#include "Update.h"

uint64 ticksPerSecond      = 0;
uint64 ticksPerMillisecond = 0;
uint64 savedTickCount      = 0;

uint64 g_mainLoopCounter = 0;
uint64 g_actorLoopCounter = 0;


uint8 g_relativeTiltDirection = 0;





constexpr uint8 meleeAttackDante [MAX_MELEE_WEAPON_DANTE ][MAX_TILT_DIRECTION][2] =
{
	// Rebellion
	{
		// Neutral
		{
			ACTION_DANTE_REBELLION_COMBO_1_PART_1,
			ACTION_DANTE_REBELLION_HELM_BREAKER,
		},
		// Up
		{
			ACTION_DANTE_REBELLION_STINGER_LEVEL_2,
			0,
		},
		// Right
		{
			0,
			0,
		},
		// Down
		{
			ACTION_DANTE_REBELLION_HIGH_TIME,
			0,
		},
		// Left
		{
			0,
			0,
		},
	},
	// Cerberus
	{
		// Neutral
		{
			ACTION_DANTE_CERBERUS_COMBO_1_PART_1,
			ACTION_DANTE_CERBERUS_SWING,
		},
		// Up
		{
			ACTION_DANTE_CERBERUS_REVOLVER_LEVEL_2,
			0,
		},
		// Right
		{
			0,
			0,
		},
		// Down
		{
			ACTION_DANTE_CERBERUS_WINDMILL,
			0,
		},
		// Left
		{
			0,
			0,
		},
	},
	// Agni & Rudra
	{
		// Neutral
		{
			ACTION_DANTE_AGNI_RUDRA_COMBO_1_PART_1,
			ACTION_DANTE_AGNI_RUDRA_AERIAL_CROSS,
		},
		// Up
		{
			ACTION_DANTE_AGNI_RUDRA_JET_STREAM_LEVEL_3,
			0,
		},
		// Right
		{
			0,
			0,
		},
		// Down
		{
			ACTION_DANTE_AGNI_RUDRA_WHIRLWIND,
			0,
		},
		// Left
		{
			0,
			0,
		},
	},
	// Nevan
	{
		// Neutral
		{
			ACTION_DANTE_NEVAN_TUNE_UP,
			ACTION_DANTE_NEVAN_AIR_PLAY,
		},
		// Up
		{
			ACTION_DANTE_NEVAN_REVERB_SHOCK_LEVEL_2,
			0,
		},
		// Right
		{
			0,
			0,
		},
		// Down
		{
			ACTION_DANTE_NEVAN_BAT_RIFT_LEVEL_2,
			0,
		},
		// Left
		{
			0,
			0,
		},
	},
	// Beowulf
	{
		// Neutral
		{
			ACTION_DANTE_BEOWULF_COMBO_1_PART_1,
			ACTION_DANTE_BEOWULF_KILLER_BEE,
		},
		// Up
		{
			ACTION_DANTE_BEOWULF_STRAIGHT_LEVEL_2,
			0,
		},
		// Right
		{
			0,
			0,
		},
		// Down
		{
			ACTION_DANTE_BEOWULF_BEAST_UPPERCUT,
			0,
		},
		// Left
		{
			0,
			0,
		},
	},
};
constexpr uint8 swordmasterDante [MAX_MELEE_WEAPON_DANTE ][MAX_TILT_DIRECTION][2] =
{
	// Rebellion
	{
		// Neutral
		{
			ACTION_DANTE_REBELLION_PROP_SHREDDER_1,
			ACTION_DANTE_REBELLION_AERIAL_RAVE_PART_1,
		},
		// Up
		{
			ACTION_DANTE_REBELLION_SWORD_PIERCE,
			0,
		},
		// Right
		{
			0,
			0,
		},
		// Down
		{
			ACTION_DANTE_REBELLION_DANCE_MACABRE_PART_1,
			0,
		},
		// Left
		{
			0,
			0,
		},
	},
	// Cerberus
	{
		// Neutral
		{
			ACTION_DANTE_CERBERUS_FLICKER,
			ACTION_DANTE_CERBERUS_AIR_FLICKER,
		},
		// Up
		{
			ACTION_DANTE_CERBERUS_CRYSTAL,
			0,
		},
		// Right
		{
			0,
			0,
		},
		// Down
		{
			ACTION_DANTE_CERBERUS_ICE_AGE,
			0,
		},
		// Left
		{
			0,
			0,
		},
	},
	// Agni & Rudra
	{
		// Neutral
		{
			ACTION_DANTE_AGNI_RUDRA_CROSSED_SWORDS,
			ACTION_DANTE_AGNI_RUDRA_SKY_DANCE_PART_1,
		},
		// Up
		{
			ACTION_DANTE_AGNI_RUDRA_CRAWLER,
			0,
		},
		// Right
		{
			0,
			0,
		},
		// Down
		{
			ACTION_DANTE_AGNI_RUDRA_TWISTER,
			0,
		},
		// Left
		{
			0,
			0,
		},
	},
	// Nevan
	{
		// Neutral
		{
			ACTION_DANTE_NEVAN_SLASH,
			ACTION_DANTE_NEVAN_AIR_SLASH_PART_1,
		},
		// Up
		{
			ACTION_DANTE_NEVAN_FEEDBACK,
			0,
		},
		// Right
		{
			0,
			0,
		},
		// Down
		{
			ACTION_DANTE_NEVAN_DISTORTION,
			0,
		},
		// Left
		{
			0,
			0,
		},
	},
	// Beowulf
	{
		// Neutral
		{
			ACTION_DANTE_BEOWULF_ZODIAC,
			ACTION_DANTE_BEOWULF_THE_HAMMER,
		},
		// Up
		{
			ACTION_DANTE_BEOWULF_VOLCANO,
			ACTION_DANTE_BEOWULF_AIR_VOLCANO,
		},
		// Right
		{
			0,
			0,
		},
		// Down
		{
			ACTION_DANTE_BEOWULF_REAL_IMPACT,
			0,
		},
		// Left
		{
			0,
			0,
		},
	},
};
constexpr uint8 gunslingerDante  [MAX_RANGED_WEAPON_DANTE][MAX_TILT_DIRECTION][2] =
{
	// Ebony & Ivory
	{
		// Neutral
		{
			ACTION_DANTE_EBONY_IVORY_TWOSOME_TIME,
			ACTION_DANTE_EBONY_IVORY_RAIN_STORM,
		},
		// Up
		{
			0,
			0,
		},
		// Right
		{
			0,
			0,
		},
		// Down
		{
			0,
			0,
		},
		// Left
		{
			0,
			0,
		},
	},
	// Shotgun
	{
		// Neutral
		{
			ACTION_DANTE_SHOTGUN_FIREWORKS,
			ACTION_DANTE_SHOTGUN_AIR_FIREWORKS,
		},
		// Up
		{
			ACTION_DANTE_SHOTGUN_GUN_STINGER,
			0,
		},
		// Right
		{
			0,
			0,
		},
		// Down
		{
			0,
			0,
		},
		// Left
		{
			0,
			0,
		},
	},
	// Artemis
	{
		// Neutral
		{
			ACTION_DANTE_ARTEMIS_MULTI_LOCK_SHOT,
			ACTION_DANTE_ARTEMIS_AIR_MULTI_LOCK_SHOT,
		},
		// Up
		{
			ACTION_DANTE_ARTEMIS_SPHERE,
			0,
		},
		// Right
		{
			0,
			0,
		},
		// Down
		{
			0,
			0,
		},
		// Left
		{
			0,
			0,
		},
	},
	// Spiral
	{
		// Neutral
		{
			ACTION_DANTE_SPIRAL_TRICK_SHOT,
			0,
		},
		// Up
		{
			ACTION_DANTE_SPIRAL_SNIPER,
			0,
		},
		// Right
		{
			0,
			0,
		},
		// Down
		{
			0,
			0,
		},
		// Left
		{
			0,
			0,
		},
	},
	// Kalina Ann
	{
		// Neutral
		{
			ACTION_DANTE_KALINA_ANN_HYSTERIC,
			0,
		},
		// Up
		{
			ACTION_DANTE_KALINA_ANN_GRAPPLE,
			0,
		},
		// Right
		{
			0,
			0,
		},
		// Down
		{
			0,
			0,
		},
		// Left
		{
			0,
			0,
		},
	},
};
constexpr uint8 royalguardDante                           [MAX_TILT_DIRECTION][2] =
{
	// Neutral
	{
		0,
		0,
	},
	// Up
	{
		ACTION_DANTE_ROYALGUARD_RELEASE_1,
		ACTION_DANTE_ROYALGUARD_AIR_RELEASE_1,
	},
	// Right
	{
		0,
		0,
	},
	// Down
	{
		0,
		0,
	},
	// Left
	{
		0,
		0,
	},
};
constexpr uint8 tricksterDante                            [MAX_TILT_DIRECTION][2] =
{
	// Neutral
	{
		ACTION_DANTE_TRICKSTER_DASH,
		ACTION_DANTE_TRICKSTER_SKY_STAR,
	},
	// Up
	{
		ACTION_DANTE_TRICKSTER_AIR_TRICK,
		ACTION_DANTE_TRICKSTER_AIR_TRICK,
	},
	// Right
	{
		0,
		0,
	},
	// Down
	{
		0,
		0,
	},
	// Left
	{
		0,
		0,
	},
};
constexpr uint8 rangedAttackDante[MAX_RANGED_WEAPON_DANTE][MAX_TILT_DIRECTION][2] =
{
	// Ebony & Ivory
	{
		// Neutral
		{
			ACTION_DANTE_EBONY_IVORY_NORMAL_SHOT,
			ACTION_DANTE_EBONY_IVORY_AIR_NORMAL_SHOT,
		},
		// Up
		{
			0,
			0,
		},
		// Right
		{
			0,
			0,
		},
		// Down
		{
			0,
			0,
		},
		// Left
		{
			0,
			0,
		},
	},
	// Shotgun
	{
		// Neutral
		{
			ACTION_DANTE_SHOTGUN_NORMAL_SHOT,
			ACTION_DANTE_SHOTGUN_AIR_NORMAL_SHOT,
		},
		// Up
		{
			0,
			0,
		},
		// Right
		{
			0,
			0,
		},
		// Down
		{
			0,
			0,
		},
		// Left
		{
			0,
			0,
		},
	},
	// Artemis
	{
		// Neutral
		{
			ACTION_DANTE_ARTEMIS_NORMAL_SHOT,
			ACTION_DANTE_ARTEMIS_AIR_NORMAL_SHOT,
		},
		// Up
		{
			0,
			0,
		},
		// Right
		{
			0,
			0,
		},
		// Down
		{
			0,
			0,
		},
		// Left
		{
			0,
			0,
		},
	},
	// Spiral
	{
		// Neutral
		{
			ACTION_DANTE_SPIRAL_NORMAL_SHOT,
			0,
		},
		// Up
		{
			0,
			0,
		},
		// Right
		{
			0,
			0,
		},
		// Down
		{
			0,
			0,
		},
		// Left
		{
			0,
			0,
		},
	},
	// Kalina Ann
	{
		// Neutral
		{
			ACTION_DANTE_KALINA_ANN_NORMAL_SHOT,
			0,
		},
		// Up
		{
			0,
			0,
		},
		// Right
		{
			0,
			0,
		},
		// Down
		{
			0,
			0,
		},
		// Left
		{
			0,
			0,
		},
	},
};

constexpr uint8 meleeAttackVergil[MAX_MELEE_WEAPON_VERGIL][MAX_TILT_DIRECTION][2] =
{
	// Yamato
	{
		// Neutral
		{
			ACTION_VERGIL_YAMATO_COMBO_PART_1,
			ACTION_VERGIL_YAMATO_AERIAL_RAVE_PART_1,
		},
		// Up
		{
			ACTION_VERGIL_YAMATO_RAPID_SLASH_LEVEL_2,
			0,
		},
		// Right
		{
			0,
			0,
		},
		// Down
		{
			ACTION_VERGIL_YAMATO_UPPER_SLASH_PART_1,
			0,
		},
		// Left
		{
			0,
			0,
		},
	},
	// Beowulf
	{
		// Neutral
		{
			ACTION_VERGIL_BEOWULF_COMBO_PART_1,
			ACTION_VERGIL_BEOWULF_STARFALL_LEVEL_2,
		},
		// Up
		{
			ACTION_VERGIL_BEOWULF_LUNAR_PHASE_LEVEL_2,
			0,
		},
		// Right
		{
			0,
			0,
		},
		// Down
		{
			ACTION_VERGIL_BEOWULF_RISING_SUN,
			0,
		},
		// Left
		{
			0,
			0,
		},
	},
	// Force Edge
	{
		// Neutral
		{
			ACTION_VERGIL_FORCE_EDGE_COMBO_PART_1,
			ACTION_VERGIL_FORCE_EDGE_HELM_BREAKER_LEVEL_2,
		},
		// Up
		{
			ACTION_VERGIL_FORCE_EDGE_STINGER_LEVEL_2,
			0,
		},
		// Right
		{
			0,
			0,
		},
		// Down
		{
			ACTION_VERGIL_FORCE_EDGE_HIGH_TIME,
			0,
		},
		// Left
		{
			0,
			0,
		},
	},
};
constexpr uint8 darkSlayerVergil                          [MAX_TILT_DIRECTION][2] =
{
	// Neutral
	{
		ACTION_VERGIL_DARK_SLAYER_AIR_TRICK,
		ACTION_VERGIL_DARK_SLAYER_AIR_TRICK,
	},
	// Up
	{
		ACTION_VERGIL_DARK_SLAYER_TRICK_UP,
		ACTION_VERGIL_DARK_SLAYER_TRICK_UP,
	},
	// Right
	{
		0,
		0,
	},
	// Down
	{
		ACTION_VERGIL_DARK_SLAYER_TRICK_DOWN,
		ACTION_VERGIL_DARK_SLAYER_TRICK_DOWN,
	},
	// Left
	{
		0,
		0,
	},
};

























template <typename T>
void EndMotion(T & actorData)
{
	actorData.var_3E00[0] = 2;
}

template <typename T>
void EnableControl(T & actorData)
{
	actorData.newButtonMask = 0xFFFF;
	actorData.newEnableLeftStick = true;
}

template <typename T>
void DisableControl(T & actorData)
{
	actorData.newButtonMask = 0;
	actorData.newEnableLeftStick = false;
}

//template <typename T1, typename T2>
//void CopyPosition(T1 & target, T2 & source)
//{
//	target.position = source.position;
//	target.direction = source.direction;
//}


template
<
	typename T1,
	typename T2
>
void CopyPosition
(
	T1 & activeActorData,
	T2 & idleActorData
)
{
	idleActorData.position       = activeActorData.position;
	idleActorData.pull           = activeActorData.pull;
	idleActorData.pullMultiplier = activeActorData.pullMultiplier;
	idleActorData.direction      = activeActorData.direction;

	//idleActorData.state &= ~STATE_ON_FLOOR;
	//idleActorData.state &= ~STATE_IN_AIR;
	//if (activeActorData.state & STATE_ON_FLOOR)
	//{
	//	idleActorData.state |= STATE_ON_FLOOR;
	//}
	//else
	//{
	//	idleActorData.state |= STATE_IN_AIR;
	//}
}

template <typename T>
void FixPull(T & actorData)
{
	if (actorData.state & STATE_ON_FLOOR)
	{
		actorData.pull = 0;
		actorData.pullMultiplier = 0;
	}
	else
	{
		actorData.pull = 0;
		actorData.pullMultiplier = -1.5;
	}
}












//template <typename T>
//void SetLeader(T & actorData)
//{
//
//
//	MessageBoxA(0, "SetLeader", 0, 0);
//
//	actorData.newIsLeader = true;
//	{
//		auto parentBaseAddr = actorData.newParentBaseAddr;
//		if (!parentBaseAddr)
//		{
//			goto sect0;
//		}
//		auto & parentActorData = *reinterpret_cast<ACTOR_DATA *>(parentBaseAddr);
//		parentActorData.newIsLeader = false;
//	}
//	sect0:;
//	const_for_all(index, 4)
//	{
//		auto childBaseAddr = actorData.newChildBaseAddr[index];
//		if (!childBaseAddr)
//		{
//			continue;
//		}
//		auto & childActorData = *reinterpret_cast<ACTOR_DATA *>(childBaseAddr);
//		childActorData.newIsLeader = false;
//	}
//}
//
//
//
//
//template <typename T>
//__declspec(deprecated("Use bufferedAction instead.")) void TriggerAttack(T & actorData, uint8 index)
//{
//	actorData.action = index;
//	actorData.lastAction = 0;
//	func_1E0800(actorData, 17, 0, 0xFFFFFFFF);
//}





















inline void EnableYamato(ACTOR_DATA_VERGIL & actorData)
{
	if (actorData.newMeleeWeaponMap[0] != WEAPON_VERGIL_YAMATO)
	{
		actorData.newMeleeWeaponMap[0] = WEAPON_VERGIL_YAMATO;
		actorData.newMeleeWeaponCount = 1;
	}
}

inline void DisableYamato(ACTOR_DATA_VERGIL & actorData)
{
	if (actorData.newMeleeWeaponMap[0] == WEAPON_VERGIL_YAMATO)
	{
		actorData.newMeleeWeaponMap[0] = WEAPON_VOID;
		actorData.newMeleeWeaponCount = 0;
	}
}



//template <typename T>
//bool IsYamatoSelected(T & actorData)
//{
//	if (actorData.newMeleeWeaponMap[actorData.newMeleeWeaponIndex] == WEAPON_VERGIL_YAMATO)
//	{
//		return true;
//	}
//	return false;
//}



template <typename T>
bool IsVergilMeleeWeaponSelected(T & actorData)
{
	auto & meleeWeapon = actorData.newMeleeWeaponMap[actorData.newMeleeWeaponIndex];
	if ((meleeWeapon >= WEAPON_VERGIL_YAMATO) && (meleeWeapon <= WEAPON_VERGIL_FORCE_EDGE))
	{
		return true;
	}
	return false;
}

template <typename T>
bool IsDanteMeleeWeaponSelected(T & actorData)
{
	auto & meleeWeapon = actorData.newMeleeWeaponMap[actorData.newMeleeWeaponIndex];
	if ((meleeWeapon >= WEAPON_DANTE_REBELLION) && (meleeWeapon <= WEAPON_DANTE_BEOWULF))
	{
		return true;
	}
	return false;
}



































#define OnceEnable(actorData, index) actorData.newSect[index] = true
#define OnceDisable(actorData, index) actorData.newSect[index] = false
#define OnceStart(actorData, index) if (actorData.newSect[index]) { OnceDisable(actorData, index)
#define OnceEnd }

#define GetAction(actorData, binding, __DEST__)\
uint8 action = 0;\
const_for_each(tiltDirection, TILT_DIRECTION_UP, MAX_TILT_DIRECTION)\
{\
	if\
	(\
		(gamepad.buttons[0] & GetBinding(BINDING_LOCK_ON)) &&\
		(GetRelativeTiltDirection(actorData) == tiltDirection) &&\
		(gamepad.buttons[0] & GetBinding(binding))\
	)\
	{\
		action = __DEST__[tiltDirection][state];\
		break;\
	}\
}\
if (!action)\
{\
	if (gamepad.buttons[0] & GetBinding(binding))\
	{\
		action = __DEST__[TILT_DIRECTION_NEUTRAL][state];\
	}\
}\

#define _Merge(a, b) a##b
#define Merge(a, b) _Merge(a, b)

#define _ToString(a) #a
#define ToString(a) _ToString(a)

#define BufferExecute(activeActorData, idleActorData, policy, binding, __DEST__, sect)\
if (activeActorData.nextActionRequestPolicy[policy] == NEXT_ACTION_REQUEST_POLICY_BUFFER)\
{\
	GetAction(activeActorData, binding, __DEST__);\
	if (action)\
	{\
		idleActorData.bufferedAction = action;\
		idleActorData.newBufferedActionPolicy = policy;\
		idleActorData.state |= STATE_BUSY;\
		MessageBoxA(0, Merge("BUFFER\n", ToString(policy)), 0, 0);\
	}\
}\
else if (activeActorData.nextActionRequestPolicy[policy] == NEXT_ACTION_REQUEST_POLICY_EXECUTE)\
{\
	if (idleActorData.bufferedAction && (idleActorData.newBufferedActionPolicy == policy))\
	{\
		idleActorData.newBufferedActionPolicy = 0;\
		idleActorData.state &= ~STATE_BUSY;\
		EndMotion(activeActorData);\
		MessageBoxA(0, Merge("BUFFER TRIGGERED FROM EXECUTE\n", ToString(policy)), 0, 0);\
		goto sect;\
	}\
	GetAction(activeActorData, binding, __DEST__);\
	if (action)\
	{\
		idleActorData.bufferedAction = action;\
		EndMotion(activeActorData);\
		MessageBoxA(0, Merge("EXECUTE\n", ToString(policy)), 0, 0);\
	}\
}\

void DanteVergil(byte8 * baseAddr)
{
	auto & parentActorData = *reinterpret_cast<ACTOR_DATA_DANTE *>(baseAddr);
	if (parentActorData.character != CHAR_DANTE)
	{
		return;
	}
	if (parentActorData.newParentBaseAddr)
	{
		return;
	}
	if (!parentActorData.newChildBaseAddr[CHAR_VERGIL])
	{
		return;
	}
	auto & childActorData = *reinterpret_cast<ACTOR_DATA_VERGIL *>(parentActorData.newChildBaseAddr[CHAR_VERGIL]);
	if (childActorData.character != CHAR_VERGIL)
	{
		return;
	}
	auto & gamepad = GetGamepad(0);


	



	// Only one actor can be active at any given time.

	// Active

	if (IsActive(parentActorData))
	{
		CopyPosition(parentActorData, childActorData);
	}

	if (IsActive(childActorData))
	{
		CopyPosition(childActorData, parentActorData);
	}

	// Idle

	if (!IsVergilMeleeWeaponSelected(parentActorData) && !IsActive(childActorData))
	{
		CopyPosition(parentActorData, childActorData);
		OnceStart(parentActorData, 1);
		{
			FixPull(parentActorData);
		}
		OnceEnd;
	}
	else
	{
		OnceEnable(parentActorData, 1);
	}

	if (IsVergilMeleeWeaponSelected(parentActorData) && !IsActive(parentActorData))
	{
		CopyPosition(childActorData, parentActorData);
		OnceStart(parentActorData, 0);
		{
			FixPull(childActorData);
		}
		OnceEnd;
	}
	else
	{
		OnceEnable(parentActorData, 0);
	}































	// Parent

	if (IsVergilMeleeWeaponSelected(parentActorData))
	{
		DisableControl(parentActorData);
	}

	if (!IsVergilMeleeWeaponSelected(parentActorData))
	{
		if (!IsActive(childActorData))
		{
			EnableControl(parentActorData);
		}
	}









	if (!IsVergilMeleeWeaponSelected(parentActorData))
	{
		if (IsActive(childActorData))
		{
			auto style = parentActorData.newStyle;
			if (style > STYLE_DANTE_DOPPELGANGER)
			{
				style = STYLE_DANTE_SWORDMASTER;
			}

			auto meleeWeapon = parentActorData.newMeleeWeaponMap[parentActorData.newMeleeWeaponIndex];
			if (meleeWeapon > WEAPON_DANTE_BEOWULF)
			{
				meleeWeapon = WEAPON_DANTE_REBELLION;
			}



			auto rangedWeapon = parentActorData.newRangedWeaponMap[parentActorData.newRangedWeaponIndex];
			if (rangedWeapon > WEAPON_DANTE_KALINA_ANN)
			{
				rangedWeapon = WEAPON_DANTE_EBONY_IVORY;
			}
			rangedWeapon -= WEAPON_DANTE_EBONY_IVORY;


			uint8 state = (childActorData.state & STATE_ON_FLOOR) ? 0 : 1;









			BufferExecute(childActorData, parentActorData, NEXT_ACTION_REQUEST_POLICY_MELEE_ATTACK, BINDING_MELEE_ATTACK, meleeAttackDante[meleeWeapon], BufferExecuteEndDante);
			switch (style)
			{
			case STYLE_DANTE_SWORDMASTER:
			{
				BufferExecute(childActorData, parentActorData, NEXT_ACTION_REQUEST_POLICY_SWORDMASTER_GUNSLINGER, BINDING_STYLE_ACTION, swordmasterDante[meleeWeapon], BufferExecuteEndDante);
				break;
			}
			case STYLE_DANTE_GUNSLINGER:
			{
				BufferExecute(childActorData, parentActorData, NEXT_ACTION_REQUEST_POLICY_SWORDMASTER_GUNSLINGER, BINDING_STYLE_ACTION, gunslingerDante[rangedWeapon], BufferExecuteEndDante);
				break;
			}
			case STYLE_DANTE_TRICKSTER:
			{
				BufferExecute(childActorData, parentActorData, NEXT_ACTION_REQUEST_POLICY_TRICKSTER_DARK_SLAYER, BINDING_STYLE_ACTION, tricksterDante, BufferExecuteEndDante);
				break;
			}
			case STYLE_DANTE_ROYALGUARD:
			{
				BufferExecute(childActorData, parentActorData, NEXT_ACTION_REQUEST_POLICY_ROYALGUARD, BINDING_STYLE_ACTION, royalguardDante, BufferExecuteEndDante);
				break;
			}
			}
			BufferExecute(childActorData, parentActorData, NEXT_ACTION_REQUEST_POLICY_RANGED_ATTACK, BINDING_SHOOT, rangedAttackDante[rangedWeapon], BufferExecuteEndDante);
			// Special case. Never has buffer state. Is run at the very end.
			if (childActorData.nextActionRequestPolicy[NEXT_ACTION_REQUEST_POLICY_END] == NEXT_ACTION_REQUEST_POLICY_EXECUTE)
			{
				EndMotion(childActorData);
			}
			BufferExecuteEndDante:;
		}
	}



























	// Child

	if (!IsVergilMeleeWeaponSelected(parentActorData))
	{
		DisableControl(childActorData);
	}

	if (IsVergilMeleeWeaponSelected(parentActorData))
	{
		if (!IsActive(parentActorData))
		{
			EnableControl(childActorData);
		}
	}

	if (IsVergilMeleeWeaponSelected(parentActorData))
	{
		if (IsActive(parentActorData))
		{
			auto meleeWeapon = childActorData.newMeleeWeaponMap[childActorData.newMeleeWeaponIndex];
			if (meleeWeapon > WEAPON_VERGIL_FORCE_EDGE)
			{
				meleeWeapon = WEAPON_VERGIL_YAMATO;
			}
			meleeWeapon -= WEAPON_VERGIL_YAMATO;

			uint8 state = (parentActorData.state & STATE_ON_FLOOR) ? 0 : 1;

			BufferExecute(parentActorData, childActorData, NEXT_ACTION_REQUEST_POLICY_MELEE_ATTACK         , BINDING_MELEE_ATTACK, meleeAttackVergil[meleeWeapon], BufferExecuteEndVergil);
			BufferExecute(parentActorData, childActorData, NEXT_ACTION_REQUEST_POLICY_TRICKSTER_DARK_SLAYER, BINDING_STYLE_ACTION, darkSlayerVergil              , BufferExecuteEndVergil);
			if (parentActorData.nextActionRequestPolicy[NEXT_ACTION_REQUEST_POLICY_END] == NEXT_ACTION_REQUEST_POLICY_EXECUTE)
			{
				EndMotion(parentActorData);
			}
			BufferExecuteEndVergil:;
		}
	}















}

#undef BufferExecute
#undef ToString
#undef _ToString
#undef Merge
#undef _Merge
#undef GetAction
#undef OnceEnd
#undef OnceStart
#undef OnceDisable
#undef OnceEnable






void ActorLoop(byte8 * baseAddr)
{
	g_actorLoopCounter++;
	DanteVergil(baseAddr);


	//DanteAirStinger(baseAddr);













}

void MainLoop()
{
	g_mainLoopCounter++;

	{
		auto baseAddr = Actor_actorBaseAddr[2];
		if (!baseAddr)
		{
			goto sect0;
		}
		auto & actorData = *reinterpret_cast<ACTOR_DATA *>(baseAddr);
		g_relativeTiltDirection = GetRelativeTiltDirection(actorData);
	}
	sect0:;

	






	if (spawnActors)
	{
		spawnActors = false;
		Log("Spawn Actors.");

		auto & mainActorData = *reinterpret_cast<ACTOR_DATA *>(Actor_actorBaseAddr[0]);

		auto danteBaseAddr = CreateActorDante();
		if (!danteBaseAddr)
		{
			return;
		}
		auto & danteActorData = *danteBaseAddr;
		Actor_actorBaseAddr.Push(danteActorData);

		danteActorData.position = mainActorData.position;
		danteActorData.newButtonMask = 0xFFFF;
		danteActorData.newEnableLeftStick = true;

		auto pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);
		pool[3] = danteActorData;





		//const_for_all(index, 5)
		//{
		//	danteActorData.newMeleeWeaponMap [index] = (WEAPON_DANTE_REBELLION   + index);
		//	danteActorData.newRangedWeaponMap[index] = (WEAPON_DANTE_EBONY_IVORY + index);
		//}
		//danteActorData.newMeleeWeaponCount = 5;
		//danteActorData.newMeleeWeaponIndex = 0;
		//danteActorData.newRangedWeaponCount = 3;
		//danteActorData.newRangedWeaponIndex = 0;

		////danteActorData.newMeleeWeaponMap[1] = WEAPON_DANTE_BEOWULF;
		////danteActorData.newMeleeWeaponMap[2] = WEAPON_VERGIL_YAMATO;
		//danteActorData.rangedWeaponMap[0] = WEAPON_DANTE_KALINA_ANN;
		//
		//danteActorData.rangedWeaponData[0] = danteActorData.newRangedWeaponData[0];

		//danteActorData.newRangedWeaponMap[0] = WEAPON_DANTE_KALINA_ANN;


		


		auto vergilBaseAddr = CreateActorVergil();
		if (!vergilBaseAddr)
		{
			return;
		}
		auto & vergilActorData = *vergilBaseAddr;
		Actor_actorBaseAddr.Push(vergilActorData);

		danteActorData.newChildBaseAddr[CHAR_VERGIL] = vergilActorData;

		vergilActorData.newParentBaseAddr = danteActorData;

		const_for_all(index, 5)
		{
			vergilActorData.meleeWeaponMap[index] = WEAPON_VOID;
		}
		vergilActorData.meleeWeaponMap[0] = WEAPON_VERGIL_YAMATO;
		vergilActorData.position = mainActorData.position;


		vergilActorData.newMeleeWeaponMap[0] = WEAPON_VERGIL_YAMATO;

		//vergilActorData.newDisableLeftStick = true;
		//vergilActorData.position = mainActorData.position;
		//danteActorData.newIsLeader = true;
		//danteActorData.newSect[0] = true;
		//danteActorData.newSect[1] = true;
		// danteActorData.newEnableMotion = true;
		// danteActorData.newEnablePermissionUpdate = true;
		// vergilActorData.newButtonMask = GAMEPAD_Y | GAMEPAD_RIGHT_SHOULDER;
		// vergilActorData.newEnableLeftStick = true;
		// vergilActorData.newEnableMotion = true;
		// vergilActorData.newEnablePermissionUpdate = true;
		//vergilActorData.newButtonMask = 0;
		//vergilActorData.newEnableLeftStick = false;
		//Log("count %u", Actor_actorBaseAddr.count);
		//for (uint32 index = 0; index < Actor_actorBaseAddr.count; index++)
		//{
		//	Log("%llX", Actor_actorBaseAddr[index]);
		//}
	}
}











void Update_Init()
{
	LogFunction();
	Windows_GetTicksPerSecond(&ticksPerSecond);
	ticksPerMillisecond = (ticksPerSecond / 1000);
	Windows_GetTickCount(&savedTickCount);


	Write<byte8>((appBaseAddr + 0x209460), 0xEB); // Air Stinger



	// {
	// 	constexpr byte8 sect0[] =
	// 	{
	// 		0x80, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x01, //cmp byte ptr [rcx+0000B8C0],01
	// 		0x74, 0x01,                               //je short
	// 		0xC3,                                     //ret
	// 		0x48, 0x89, 0x5C, 0x24, 0x08,             //mov [rsp+08],rbx
	// 	};
	// 	auto func = CreateFunction(0, (appBaseAddr + 0x1FB305), false, true, sizeof(sect0));
	// 	memcpy(func.sect0, sect0, sizeof(sect0));
	// 	*reinterpret_cast<uint32 *>(func.sect0 + 2) = offsetof(ACTOR_DATA, newEnablePositionUpdate);
	// 	WriteJump((appBaseAddr + 0x1FB300), func.addr);
	// 	/*
	// 	dmc3.exe+1FB300 - 48 89 5C 24 08 - mov [rsp+08],rbx
	// 	dmc3.exe+1FB305 - 57             - push rdi
	// 	*/
	// }















	/*
	dmc3.exe+209460 - EB 45                 - jmp dmc3.exe+2094A7

	*/


	//EventEnableYamato.Push(EventEnableYamatoDefault);
	//EventDisableYamato.Push(EventDisableYamatoDefault);
	//EventNextActionRequestPolicyUpdate.Push(EventNextActionRequestPolicyUpdate_DanteYamato);



	//#pragma region Permissions
	//{
	//	constexpr byte8 sect0[] =
	//	{
	//		0x80, 0xBB, 0x00, 0x00, 0x00, 0x00, 0x00, //cmp byte ptr [rbx+0000B8C0],00
	//		0x74, 0x06,                               //je short
	//		0x89, 0x83, 0x60, 0x3E, 0x00, 0x00,       //mov [rbx+00003E60],eax
	//	};
	//	auto func = CreateFunction(0, (appBaseAddr + 0x1E0AC5), false, true, sizeof(sect0));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	*reinterpret_cast<uint32 *>(func.sect0 + 2) = offsetof(ACTOR_DATA, newEnablePermissionUpdate);
	//	WriteJump((appBaseAddr + 0x1E0ABF), func.addr, 1);
	//	/*
	//	dmc3.exe+1E0ABF - 89 83 603E0000 - mov [rbx+00003E60],eax
	//	dmc3.exe+1E0AC5 - 75 25          - jne dmc3.exe+1E0AEC
	//	*/
	//}
	//{
	//	constexpr byte8 sect0[] =
	//	{
	//		0x80, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, //cmp byte ptr [rcx+0000B8C0],00
	//		0x74, 0x06,                               //je short
	//		0x89, 0x91, 0x60, 0x3E, 0x00, 0x00,       //mov [rcx+00003E60],edx
	//	};
	//	auto func = CreateFunction(0, (appBaseAddr + 0x1E0B6C), false, true, sizeof(sect0));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	*reinterpret_cast<uint32 *>(func.sect0 + 2) = offsetof(ACTOR_DATA, newEnablePermissionUpdate);
	//	WriteJump((appBaseAddr + 0x1E0B66), func.addr, 1);
	//	/*
	//	dmc3.exe+1E0B66 - 89 91 603E0000 - mov [rcx+00003E60],edx
	//	dmc3.exe+1E0B6C - 8B C2          - mov eax,edx
	//	*/
	//}
	//{
	//	constexpr byte8 sect0[] =
	//	{
	//		0x80, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, //cmp byte ptr [rcx+0000B8C0],00
	//		0x74, 0x06,                               //je short
	//		0x89, 0x91, 0x60, 0x3E, 0x00, 0x00,       //mov [rcx+00003E60],edx
	//	};
	//	auto func = CreateFunction(0, (appBaseAddr + 0x1E173E), false, true, sizeof(sect0));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	*reinterpret_cast<uint32 *>(func.sect0 + 2) = offsetof(ACTOR_DATA, newEnablePermissionUpdate);
	//	WriteJump((appBaseAddr + 0x1E1738), func.addr, 1);
	//	/*
	//	dmc3.exe+1E1738 - 89 91 603E0000 - mov [rcx+00003E60],edx
	//	dmc3.exe+1E173E - 8B C2          - mov eax,edx
	//	*/
	//}
	//{
	//	constexpr byte8 sect0[] =
	//	{
	//		0x80, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00,                   //cmp byte ptr [rcx+0000B8C0],00
	//		0x74, 0x0A,                                                 //je short
	//		0xC7, 0x81, 0x60, 0x3E, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, //mov [rcx+00003E60],00000002
	//	};
	//	auto func = CreateFunction(0, (appBaseAddr + 0x1E248C), false, true, sizeof(sect0));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	*reinterpret_cast<uint32 *>(func.sect0 + 2) = offsetof(ACTOR_DATA, newEnablePermissionUpdate);
	//	WriteJump((appBaseAddr + 0x1E2482), func.addr, 5);
	//	/*
	//	dmc3.exe+1E2482 - C7 81 603E0000 02000000 - mov [rcx+00003E60],00000002
	//	dmc3.exe+1E248C - E8 8F800100             - call dmc3.exe+1FA520
	//	*/
	//}
	//#pragma endregion





































	//{
	//	constexpr byte8 sect0[] =
	//	{
	//		0x80, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x01, //cmp byte ptr [rcx+0000B8C0],01
	//		0x74, 0x01,                               //je short
	//		0xC3,                                     //ret
	//		0x48, 0x89, 0x5C, 0x24, 0x08,             //mov [rsp+08],rbx
	//	};
	//	auto func = CreateFunction(0, (appBaseAddr + 0x1EFB95), false, true, sizeof(sect0));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	*reinterpret_cast<uint32 *>(func.sect0 + 2) = offsetof(ACTOR_DATA, newEnableMotion);
	//	WriteJump((appBaseAddr + 0x1EFB90), func.addr);
	//	/*
	//	dmc3.exe+1EFB90 - 48 89 5C 24 08 - mov [rsp+08],rbx
	//	dmc3.exe+1EFB95 - 48 89 6C 24 10 - mov [rsp+10],rbp
	//	*/
	//}













	//// Skip Position Update
	//{
	//	constexpr byte8 sect0[] =
	//	{
	//		0x80, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, //cmp byte ptr [rcx+0000B8C0],00
	//		0x74, 0x01,                               //je short
	//		0xC3,                                     //ret
	//		0x48, 0x89, 0x5C, 0x24, 0x08,             //mov [rsp+08],rbx
	//	};
	//	auto func = CreateFunction(0, (appBaseAddr + 0x1FB305), false, true, sizeof(sect0));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	*reinterpret_cast<uint32 *>(func.sect0 + 2) = offsetof(ACTOR_DATA, newSkipPositionUpdate);
	//	WriteJump((appBaseAddr + 0x1FB300), func.addr);
	//	/*
	//	dmc3.exe+1FB300 - 48 89 5C 24 08 - mov [rsp+08],rbx
	//	dmc3.exe+1FB305 - 57             - push rdi
	//	*/
	//}

	//{
	//	constexpr byte8 sect0[] =
	//	{
	//		0x80, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, //cmp byte ptr [rcx+0000B8C0],00
	//		0x74, 0x01,                               //je short
	//		0xC3,                                     //ret
	//		0x0F, 0xB6, 0x81, 0x09, 0x3F, 0x00, 0x00, //movzx eax,byte ptr [rcx+00003F09]
	//	};
	//	auto func = CreateFunction(0, (appBaseAddr + 0x1FCF37), false, true, sizeof(sect0));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	*reinterpret_cast<uint32 *>(func.sect0 + 2) = offsetof(ACTOR_DATA, newSkipPositionUpdate);
	//	WriteJump((appBaseAddr + 0x1FCF30), func.addr, 2);
	//	/*
	//	dmc3.exe+1FCF30 - 0FB6 81 093F0000 - movzx eax,byte ptr [rcx+00003F09]
	//	dmc3.exe+1FCF37 - 4C 8B C9         - mov r9,rcx
	//	*/
	//}









	// @Research: Where did I get this from?
	// Maybe prefer root update.


	{
		constexpr byte8 sect1[] =
		{
			0x48, 0x8B, 0xCB, //mov rcx,rbx
		};
		constexpr byte8 sect2[] =
		{
			0x48, 0x83, 0xC4, 0x20, //add rsp,20
			0x5B,                   //pop rbx
		};
		auto func = CreateFunction(ActorLoop, (appBaseAddr + 0x1DFAB4), true, true, 0, sizeof(sect1), sizeof(sect2));
		memcpy(func.sect1, sect1, sizeof(sect1));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteJump((appBaseAddr + 0x1DFAAF), func.addr);
		/*
		dmc3.exe+1DFAAF - 48 83 C4 20 - add rsp,20
		dmc3.exe+1DFAB3 - 5B          - pop rbx
		dmc3.exe+1DFAB4 - E9 C7711400 - jmp dmc3.exe+326C80
		*/
	}
	{
		byte8 sect0[] =
		{
			0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc3.exe+23B060
		};
		FUNC func = CreateFunction(MainLoop, (appBaseAddr + 0x23D4B7), true, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteCall(func.sect0, (appBaseAddr + 0x23B060));
		WriteJump((appBaseAddr + 0x23D4B2), func.addr);
		/*
		dmc3.exe+23D4B2 - E8 A9DBFFFF - call dmc3.exe+23B060
		dmc3.exe+23D4B7 - 84 C0       - test al,al
		*/
	}
}
