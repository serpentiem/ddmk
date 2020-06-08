#include "Update.h"

uint64 ticksPerSecond      = 0;
uint64 ticksPerMillisecond = 0;
uint64 savedTickCount      = 0;

uint64 g_mainLoopCounter = 0;
uint64 g_actorLoopCounter = 0;


uint8 g_relativeTiltDirection = 0;













uint8 g_style[MAX_PLAYER][MAX_ENTITY][MAX_CHAR] =
{
	// Player 0
	{
		// Entity 0
		{
			STYLE_DANTE_TRICKSTER,
			0,
			0,
			STYLE_VERGIL_DARK_SLAYER,
		},
		// Entity 1
		{
			STYLE_DANTE_TRICKSTER,
			0,
			0,
			STYLE_VERGIL_DARK_SLAYER,
		},
	},
	// Player 1
	{
		// Entity 0
		{
			STYLE_DANTE_TRICKSTER,
			0,
			0,
			STYLE_VERGIL_DARK_SLAYER,
		},
		// Entity 1
		{
			STYLE_DANTE_TRICKSTER,
			0,
			0,
			STYLE_VERGIL_DARK_SLAYER,
		},
	},
	// Player 2
	{
		// Entity 0
		{
			STYLE_DANTE_TRICKSTER,
			0,
			0,
			STYLE_VERGIL_DARK_SLAYER,
		},
		// Entity 1
		{
			STYLE_DANTE_TRICKSTER,
			0,
			0,
			STYLE_VERGIL_DARK_SLAYER,
		},
	},
	// Player 3
	{
		// Entity 0
		{
			STYLE_DANTE_TRICKSTER,
			0,
			0,
			STYLE_VERGIL_DARK_SLAYER,
		},
		// Entity 1
		{
			STYLE_DANTE_TRICKSTER,
			0,
			0,
			STYLE_VERGIL_DARK_SLAYER,
		},
	},
};

















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





















//inline void EnableYamato(ACTOR_DATA_VERGIL & actorData)
//{
//	if (actorData.newMeleeWeapon[0] != WEAPON_VERGIL_YAMATO)
//	{
//		actorData.newMeleeWeapon[0] = WEAPON_VERGIL_YAMATO;
//		actorData.newMeleeWeaponCount = 1;
//	}
//}
//
//inline void DisableYamato(ACTOR_DATA_VERGIL & actorData)
//{
//	if (actorData.newMeleeWeapon[0] == WEAPON_VERGIL_YAMATO)
//	{
//		actorData.newMeleeWeapon[0] = WEAPON_VOID;
//		actorData.newMeleeWeaponCount = 0;
//	}
//}



//template <typename T>
//bool IsYamatoSelected(T & actorData)
//{
//	if (actorData.newMeleeWeapon[actorData.newMeleeWeaponIndex] == WEAPON_VERGIL_YAMATO)
//	{
//		return true;
//	}
//	return false;
//}



template <typename T>
bool IsVergilMeleeWeaponSelected(T & actorData)
{
	auto & meleeWeapon = actorData.newMeleeWeapon[actorData.newMeleeWeaponIndex];
	if ((meleeWeapon >= WEAPON_VERGIL_YAMATO) && (meleeWeapon <= WEAPON_VERGIL_FORCE_EDGE))
	{
		return true;
	}
	return false;
}

template <typename T>
bool IsDanteMeleeWeaponSelected(T & actorData)
{
	auto & meleeWeapon = actorData.newMeleeWeapon[actorData.newMeleeWeaponIndex];
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
for_each(uint8, tiltDirection, TILT_DIRECTION_UP, MAX_TILT_DIRECTION)\
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

// @Research: Maybe templates are better suited for this after all.
// @Todo: Check for input charge.

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
			auto style = parentActorData.style;
			if (style > STYLE_DANTE_DOPPELGANGER)
			{
				style = STYLE_DANTE_SWORDMASTER;
			}

			auto meleeWeapon = parentActorData.meleeWeapon[parentActorData.meleeWeaponIndex];
			if (meleeWeapon > WEAPON_DANTE_BEOWULF)
			{
				meleeWeapon = WEAPON_DANTE_REBELLION;
			}



			auto rangedWeapon = parentActorData.rangedWeapon[parentActorData.rangedWeaponIndex];
			if (rangedWeapon > WEAPON_DANTE_KALINA_ANN)
			{
				rangedWeapon = WEAPON_DANTE_EBONY_IVORY;
			}
			if (rangedWeapon >= WEAPON_DANTE_EBONY_IVORY)
			{
				rangedWeapon -= WEAPON_DANTE_EBONY_IVORY;
			}

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
			auto meleeWeapon = childActorData.meleeWeapon[childActorData.queuedMeleeWeaponIndex];
			if (meleeWeapon > WEAPON_VERGIL_FORCE_EDGE)
			{
				meleeWeapon = WEAPON_VERGIL_YAMATO;
			}
			if (meleeWeapon >= WEAPON_VERGIL_YAMATO)
			{
				meleeWeapon -= WEAPON_VERGIL_YAMATO;
			}

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




#define return_if(condition) if (condition) { return; }




// @Todo: Add jump cancel event to reset Air Stinger.

//void AerialState(byte8 * baseAddr)
//{
//	auto & actorData = *reinterpret_cast<ACTOR_DATA *>(baseAddr);
//
//	if (actorData.state & STATE_ON_FLOOR)
//	{
//		if ((actorData.state & STATE_ON_FLOOR) != (actorData.lastState & STATE_ON_FLOOR))
//		{
//			if (actorData.airStinger)
//			{
//				actorData.airStinger = false;
//			}
//		}
//	}
//}








//
//
//
//void DanteAirStinger(byte8 * baseAddr)
//{
//	auto & actorData = *reinterpret_cast<ACTOR_DATA_DANTE *>(baseAddr);
//	if (!actorData.character == CHAR_DANTE)
//	{
//		return;
//	}
//	auto & gamepad = GetGamepad(actorData.newGamepad);
//	if (!(actorData.state & STATE_IN_AIR))
//	{
//		return;
//	}
//
//	if
//	(
//		(gamepad.buttons[0] & GetBinding(BINDING_LOCK_ON)) &&
//		(GetRelativeTiltDirection(actorData) == TILT_DIRECTION_UP) &&
//		(gamepad.buttons[0] & GetBinding(BINDING_MELEE_ATTACK))
//	)
//	{
//		auto & meleeWeapon = actorData.meleeWeapon[actorData.meleeWeaponIndex];
//		switch (meleeWeapon)
//		{
//		case WEAPON_DANTE_REBELLION:
//		{
//
//
//
//			if (!actorData.airStinger)
//			{
//				actorData.airStinger = true;
//			}
//
//
//			//func_1E0800(actorData, ACTION_DANTE_REBELLION_STINGER_LEVEL_2, 0, 0xFFFFFFFF);
//			//actorData.permissions = 0xC08;
//
//
//
//
//			//if (!(actorData.state & STATE_BUSY))
//			//{
//			//	
//			//	
//			//}
//
//
//			
//
//
//
//
//
//
//			//actorData.bufferedAction = ACTION_DANTE_REBELLION_STINGER_LEVEL_2;
//
//
//
//
//
//
//
//
//
//			//	func_1E0800(actorData, 17, 0, 0xFFFFFFFF);
//
//
//
//
//			break;
//		}
//		//case WEAPON_DANTE_BEOWULF:
//		//{
//		//	actorData.bufferedAction = ACTION_DANTE_BEOWULF_STRAIGHT_LEVEL_2;
//		//	break;
//		//}
//		}
//		return;
//	}
//
//	//if
//	//(
//	//	(gamepad.buttons[0] & GetBinding(BINDING_LOCK_ON)) &&
//	//	(GetRelativeTiltDirection(actorData) == TILT_DIRECTION_UP) &&
//	//	(gamepad.buttons[0] & GetBinding(BINDING_STYLE_ACTION))
//	//)
//	//{
//	//	auto & rangedWeapon = actorData.rangedWeapon[actorData.rangedWeaponIndex];
//	//	if ((actorData.style == STYLE_DANTE_GUNSLINGER) && (rangedWeapon == WEAPON_DANTE_SHOTGUN))
//	//	{
//	//		actorData.bufferedAction = ACTION_DANTE_SHOTGUN_GUN_STINGER;
//	//	}
//	//	return;
//	//}
//}








void ActorLoop(byte8 * baseAddr)
{
	g_actorLoopCounter++;
	DanteVergil(baseAddr);



	//AerialState(baseAddr);

	//DanteAirStinger(baseAddr);
	











}

















template <typename T>
byte8 * SpawnActorFunction
(
	uint8 player,
	uint8 entity
)
{
	auto mainBaseAddr = Actor_actorBaseAddr[0];
	if (!mainBaseAddr)
	{
		return 0;
	}
	auto & mainActorData = *reinterpret_cast<ACTOR_DATA *>(mainBaseAddr);

	auto parentBaseAddr = CreateActor<T>(player, entity);
	if (!parentBaseAddr)
	{
		return 0;
	}
	auto & parentActorData = *parentBaseAddr;
	Actor_actorBaseAddr.Push(parentActorData);

	parentActorData.position = mainActorData.position;
	parentActorData.style = g_style[player][entity][GetCharacterId<T>::value]; // @Todo: Change to Actor_style for now.

	if (entity == ENTITY_MAIN)
	{
		parentActorData.newGamepad = player;
		parentActorData.newButtonMask = 0xFFFF;
		parentActorData.newEnableRightStick = true;
		parentActorData.newEnableLeftStick = true;
	}
	else
	{
		parentActorData.newGamepad = MAX_PLAYER;
		return parentActorData;
	}

	if constexpr (typematch(T, ACTOR_DATA_DANTE) || typematch(T, ACTOR_DATA_VERGIL))
	{
		auto childBaseAddr = CreateActor<GetChildActorDataType<T>::value>(player, entity);
		if (!childBaseAddr)
		{
			return 0;
		}
		auto & childActorData = *reinterpret_cast<typename GetChildActorDataType<T>::value *>(childBaseAddr);

		parentActorData.newChildBaseAddr[GetCharacterId<GetChildActorDataType<T>::value>::value] = childActorData;

		childActorData.newParentBaseAddr = parentActorData;
		childActorData.position = parentActorData.position;

		if constexpr (typematch(T, ACTOR_DATA_DANTE))
		{
			auto & newMeleeWeapon = parentActorData.newMeleeWeapon[parentActorData.newMeleeWeaponIndex];
			if ((newMeleeWeapon >= WEAPON_VERGIL_YAMATO) && (newMeleeWeapon <= WEAPON_VERGIL_FORCE_EDGE))
			{
				childActorData.activeMeleeWeaponIndex = (newMeleeWeapon - WEAPON_VERGIL_YAMATO);
				childActorData.queuedMeleeWeaponIndex = (newMeleeWeapon - WEAPON_VERGIL_YAMATO);
			}
		}
		else if constexpr (typematch(T, ACTOR_DATA_VERGIL))
		{
			for_all(uint8, index, MAX_MELEE_WEAPON)
			{
				childActorData.newMeleeWeapon[index] = (WEAPON_DANTE_REBELLION + index);
			}
			childActorData.newMeleeWeaponCount = MAX_MELEE_WEAPON_DANTE;
			childActorData.newMeleeWeaponIndex = 0;

			auto & newMeleeWeapon = parentActorData.newMeleeWeapon[parentActorData.newMeleeWeaponIndex];
			if ((newMeleeWeapon >= WEAPON_DANTE_REBELLION) && (newMeleeWeapon <= WEAPON_DANTE_BEOWULF))
			{
				childActorData.meleeWeapon[0] = newMeleeWeapon;
				childActorData.meleeWeapon[1] = WEAPON_VOID;
				childActorData.meleeWeaponIndex = 0;
			}
		}
	}

	return parentActorData;
}










byte8 * SpawnActor
(
	uint8 player,
	uint8 entity
)
{
	auto & character = Config.Actor.character[player][entity];

	if (character == CHAR_DANTE)
	{
		return SpawnActorFunction<ACTOR_DATA_DANTE>(player, entity);
	}
	else if (character == CHAR_BOB)
	{
		return SpawnActorFunction<ACTOR_DATA_BOB>(player, entity);
	}
	else if (character == CHAR_LADY)
	{
		return SpawnActorFunction<ACTOR_DATA_LADY>(player, entity);
	}
	else if (character == CHAR_VERGIL)
	{
		return SpawnActorFunction<ACTOR_DATA_VERGIL>(player, entity);
	}

	return 0;
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







		for_all(uint8, player, Config.Actor.playerCount)
		{
			auto mainBaseAddr = SpawnActor(player, ENTITY_MAIN);
			if (!mainBaseAddr)
			{
				continue;
			}
			auto & mainActorData = *reinterpret_cast<ACTOR_DATA *>(mainBaseAddr);

			auto cloneBaseAddr = SpawnActor(player, ENTITY_CLONE);
			if (!cloneBaseAddr)
			{
				continue;
			}
			auto & cloneActorData = *reinterpret_cast<ACTOR_DATA *>(cloneBaseAddr);

			mainActorData.cloneBaseAddr = cloneActorData;
		}

		auto baseAddr = Actor_actorBaseAddr[2];
		if (baseAddr)
		{
			auto pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);
			pool[3] = baseAddr;
		}
	}
}





void AttackDataDante(byte8 * baseAddr)
{
	auto & actorData = *reinterpret_cast<ACTOR_DATA_DANTE *>(baseAddr);
	auto & gamepad = GetGamepad(actorData.newGamepad);

	if (actorData.action == ACTION_DANTE_REBELLION_HELM_BREAKER)
	{
		actorData.airStinger = false;







		if
		(
			(gamepad.buttons[0] & GetBinding(BINDING_LOCK_ON)) &&
			(GetRelativeTiltDirection(actorData) == TILT_DIRECTION_UP) &&
			(gamepad.buttons[0] & GetBinding(BINDING_MELEE_ATTACK))
		)
		{
			actorData.airStinger = true;
		}

		if (actorData.airStinger)
		{
			actorData.action = ACTION_DANTE_REBELLION_STINGER_LEVEL_2;
		}
	}
}




void UpdatePermissions(byte8 * baseAddr)
{


	auto & actorData = *reinterpret_cast<ACTOR_DATA *>(baseAddr);

	if (actorData.permissions == 0x1C1B)
	{
		if (actorData.airStinger)
		{
			actorData.airStinger = false;



			actorData.permissions = PERMISSION_INTERACTION_STYLE_ATTACK;


			actorData.state = STATE_IN_AIR;
			actorData.lastState = actorData.state;




			//actorData.var_3E00[0]

			memset(actorData.var_3E00, 0, 16);
			actorData.var_3E00[2] = 6;


		}
	}



	if (actorData.permissions == 0x401)
	{
		if (actorData.action == ACTION_DANTE_REBELLION_STINGER_LEVEL_2)
		{
			if (actorData.state & STATE_IN_AIR)
			{
				actorData.permissions = 0x400;
			}
		}
	}

	



}


/*
dmc3.exe+1FF63A - 80 BB C6390000 01     - cmp byte ptr [rbx+000039C6],01 { 1 }
dmc3.exe+1FF641 - 75 0A                 - jne dmc3.exe+1FF64D
dmc3.exe+1FF643 - C7 83 A4000000 0000C0BF - mov [rbx+000000A4],BFC00000 { -1.50 }
dmc3.exe+1FF64D - F3 0F10 15 17DF1500   - movss xmm2,[dmc3.exe+35D56C] { (1.00) }
dmc3.exe+1FF655 - 48 8B CB              - mov rcx,rbx
dmc3.exe+1FF658 - 0FB7 93 D23E0000      - movzx edx,word ptr [rbx+00003ED2]
dmc3.exe+1FF65F - E8 9CBCFFFF           - call dmc3.exe+1FB300
*/


void DanteStinger(byte8 * baseAddr)
{
	//return;

	return;

	auto & actorData = *reinterpret_cast<ACTOR_DATA_DANTE *>(baseAddr);


	if (actorData.state & STATE_IN_AIR)
	{
		func_1FB300(actorData, actorData.direction, 1);


		////actorData.pull =

		//if (actorData.pull <= -10.0f)
		//{
		//	actorData.pull = -10.0f;
		//}



		//actorData.pullMultiplier = -1.5f;

	}










}



void DanteStingerImpact(byte8 * baseAddr)
{


	auto & actorData = *reinterpret_cast<ACTOR_DATA_DANTE *>(baseAddr);



	//func_1DFDA0(actorData, 8, 14, actorData.pull, actorData.pullMultiplier, 0);


	if (actorData.state & STATE_IN_AIR)
	{
		func_1DFDA0(actorData, 7, 0, actorData.pull, actorData.pullMultiplier, 0);

	}

	




	//static uint32  arg2           = 8;
	//static uint8   arg3           = 14;
	//static float32 pull           = -70.0f;
	//static float32 pullMultiplier = -1.5f;
	//static uint8   arg6           = 0;
	//NEW_GUI_Input<uint32 >("arg2"          , arg2          );
	//NEW_GUI_Input<uint8  >("arg3"          , arg3          );
	//NEW_GUI_Input<float32>("pull"          , pull          );
	//NEW_GUI_Input<float32>("pullMultiplier", pullMultiplier);
	//NEW_GUI_Input<uint8  >("arg6"          , arg6          );
	//if (NEW_GUI_Button("Drop1"))
	//{
	//	func_1DFDA0(actorData, arg2, arg3, pull, pullMultiplier, arg6);
	//}






}


void Update_Init()
{
	LogFunction();
	Windows_GetTicksPerSecond(&ticksPerSecond);
	ticksPerMillisecond = (ticksPerSecond / 1000);
	Windows_GetTickCount(&savedTickCount);


	//vp_memset((appBaseAddr + 0x204D6E), 0x90, 1032);
	vp_memset((appBaseAddr + 0x1F9189), 0x90, 8);
	vp_memset((appBaseAddr + 0x1E7BF2), 0x90, 5);



	{
		constexpr byte8 sect0[] =
		{
			0xC6, 0x87, 0x2A, 0x3E, 0x00, 0x00, 0x00, //mov byte ptr [rdi+00003E2A],00
			0x48, 0x8B, 0xCF,                         //mov rcx,rdi
		};
		constexpr byte8 sect1[] =
		{
			0x48, 0x8B, 0xCF, //mov rcx,rdi
		};
		auto func = CreateFunction(DanteStingerImpact, (appBaseAddr + 0x2091A0), true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteJump((appBaseAddr + 0x209199), func.addr, 2);
		/*
		dmc3.exe+209199 - C6 87 2A3E0000 00 - mov byte ptr [rdi+00003E2A],00
		dmc3.exe+2091A0 - 48 8B CF          - mov rcx,rdi
		*/
	}






	{
		constexpr byte8 sect0[] =
		{
			0x40, 0x57,             //push rdi
			0x48, 0x83, 0xEC, 0x60, //sub rsp,60
		};
		auto func = CreateFunction(DanteStinger, (appBaseAddr + 0x2090F6), true, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteJump((appBaseAddr + 0x2090F0), func.addr, 1);
		/*
		dmc3.exe+2090F0 - 40 57             - push rdi
		dmc3.exe+2090F2 - 48 83 EC 60       - sub rsp,60
		dmc3.exe+2090F6 - 80 B9 29620000 01 - cmp byte ptr [rcx+00006229],01
		*/
	}









	{
		constexpr byte8 sect0[] =
		{
			0xBA, 0x01, 0x00, 0x00, 0x00,                               //mov edx,00000001
			0xF7, 0x87, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //test [rdi+0000B8C0],00000002
			0x0F, 0x85, 0x00, 0x00, 0x00, 0x00,                         //jne dmc3.exe+2093F2
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x2093EA), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*reinterpret_cast<uint32 *>(func.sect0 + 7) = offsetof(ACTOR_DATA, state);
		*reinterpret_cast<uint32 *>(func.sect0 + 0xB) = STATE_IN_AIR;
		WriteAddress((func.sect0 + 0xF), (appBaseAddr + 0x2093F2), 6);
		WriteJump((appBaseAddr + 0x2093E5), func.addr);
		/*
		dmc3.exe+2093E5 - BA 01000000      - mov edx,00000001
		dmc3.exe+2093EA - 48 8B CF         - mov rcx,rdi
		dmc3.exe+2093ED - E8 6E77FDFF      - call dmc3.exe+1E0B60
		dmc3.exe+2093F2 - 0FB7 87 C0000000 - movzx eax,word ptr [rdi+000000C0]
		*/
	}








	//{
	//	constexpr byte8 sect0[] =
	//	{
	//		0x89, 0x83, 0x60, 0x3E, 0x00, 0x00, //mov [rbx+00003E60],eax
	//	};
	//	constexpr byte8 sect1[] =
	//	{
	//		0x48, 0x8B, 0xCB, //mov rcx,rbx
	//	};
	//	auto func = CreateFunction(UpdatePermissions, (appBaseAddr + 0x1E0AC5), true, true, sizeof(sect0), sizeof(sect1));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	memcpy(func.sect1, sect1, sizeof(sect1));
	//	WriteJump((appBaseAddr + 0x1E0ABF), func.addr, 1);
	//	/*
	//	dmc3.exe+1E0ABF - 89 83 603E0000 - mov [rbx+00003E60],eax
	//	dmc3.exe+1E0AC5 - 75 25          - jne dmc3.exe+1E0AEC
	//	*/
	//}




	{
		constexpr byte8 sect2[] =
		{
			0x0F, 0xB6, 0x81, 0xA4, 0x3F, 0x00, 0x00, //movzx eax,byte ptr [rcx+00003FA4]
		};
		auto func = CreateFunction(AttackDataDante, (appBaseAddr + 0x1FDF17), true, true, 0, 0, sizeof(sect2));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteJump((appBaseAddr + 0x1FDF10), func.addr, 2);
		/*
		dmc3.exe+1FDF10 - 0FB6 81 A43F0000 - movzx eax,byte ptr [rcx+00003FA4]
		dmc3.exe+1FDF17 - FF C8            - dec eax
		*/
	}














	{
		constexpr byte8 sect0[] =
		{
			0x80, 0xBF, 0x00, 0x00, 0x00, 0x00, 0x01, //cmp byte ptr [rdi+0000B8C0],01
			0x0F, 0x84, 0x00, 0x00, 0x00, 0x00,       //je dmc3.exe+2094A7
			0x80, 0xBF, 0x2A, 0x3E, 0x00, 0x00, 0x01, //cmp byte ptr [rdi+00003E2A],01
			0x0F, 0x85, 0x00, 0x00, 0x00, 0x00,       //jne dmc3.exe+2094A7
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x209462), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*reinterpret_cast<uint32 *>(func.sect0 + 2) = offsetof(ACTOR_DATA, airStinger);
		WriteAddress((func.sect0 + 7), (appBaseAddr + 0x2094A7), 6);
		WriteAddress((func.sect0 + 0x14), (appBaseAddr + 0x2094A7), 6);
		WriteJump((appBaseAddr + 0x209459), func.addr, 2);
		/*
		dmc3.exe+209459 - 80 BF 2A3E0000 01 - cmp byte ptr [rdi+00003E2A],01
		dmc3.exe+209460 - 75 45             - jne dmc3.exe+2094A7
		dmc3.exe+209462 - 0FB7 97 C0000000  - movzx edx,word ptr [rdi+000000C0]
		*/
	}












	//Write<byte8>((appBaseAddr + 0x209460), 0xEB); // Air Stinger



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
