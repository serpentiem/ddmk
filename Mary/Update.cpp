#include "Update.h"

uint64 ticksPerSecond      = 0;
uint64 ticksPerMillisecond = 0;
uint64 savedTickCount      = 0;

uint64 g_mainLoopCounter = 0;
uint64 g_actorLoopCounter = 0;


uint8 g_relativeTiltDirection = 0;



uint8 lockOnForwardMeleeAttackDante[5][2] = {};
uint8 lockOnBackMeleeAttackDante   [5][2] = {};
uint8 meleeAttackDante             [5][2] =
{
	{ ACTION_DANTE_REBELLION_COMBO_1_PART_1, ACTION_DANTE_REBELLION_HELM_BREAKER },
};

uint8 lockOnForwardSwordmasterDante[5][2] = {};
uint8 lockOnBackSwordmasterDante   [5][2] = {};
uint8 swordmasterDante             [5][2] = {};

uint8 lockOnForwardGunslingerDante[5][2] = {};
uint8 lockOnBackGunslingerDante   [5][2] = {};
uint8 gunslingerDante             [5][2] = {};

uint8 lockOnForwardRoyalguardDante[2] = {};
uint8 lockOnBackRoyalguardDante   [2] = {};
uint8 royalguardDante             [2] = {};

uint8 lockOnForwardTricksterDante[2] = {};
uint8 lockOnBackTricksterDante   [2] = {};
uint8 tricksterDante             [2] = {};

uint8 lockOnForwardRangedAttackDante[5][2] = {};
uint8 lockOnBackRangedAttackDante   [5][2] = {};
uint8 rangedAttackDante             [5][2] = {};





uint8 lockOnForwardMeleeAttackVergil[3][2] = {};
uint8 lockOnBackMeleeAttackVergil   [3][2] = {};
uint8 meleeAttackVergil             [3][2] = {};

uint8 lockOnForwardDarkSlayerVergil[2] = {};
uint8 lockOnBackDarkSlayerVergil   [2] = {};
uint8 darkSlayerVergil             [2] = {};

























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

template <typename T1, typename T2>
void CopyPosition(T1 & target, T2 & source)
{
	target.position = source.position;
	target.direction = source.direction;
}

template <typename T>
void SetLeader(T & actorData)
{


	MessageBoxA(0, "SetLeader", 0, 0);

	actorData.newIsLeader = true;
	{
		auto parentBaseAddr = actorData.newParentBaseAddr;
		if (!parentBaseAddr)
		{
			goto sect0;
		}
		auto & parentActorData = *reinterpret_cast<ACTOR_DATA *>(parentBaseAddr);
		parentActorData.newIsLeader = false;
	}
	sect0:;
	const_for_all(index, 4)
	{
		auto childBaseAddr = actorData.newChildBaseAddr[index];
		if (!childBaseAddr)
		{
			continue;
		}
		auto & childActorData = *reinterpret_cast<ACTOR_DATA *>(childBaseAddr);
		childActorData.newIsLeader = false;
	}
}




template <typename T>
__declspec(deprecated("Use bufferedAction instead.")) void TriggerAttack(T & actorData, uint8 index)
{
	actorData.action = index;
	actorData.lastAction = 0;
	func_1E0800(actorData, 17, 0, 0xFFFFFFFF);
}





















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



template <typename T>
bool IsYamatoSelected(T & actorData)
{
	if (actorData.newMeleeWeaponMap[actorData.newMeleeWeaponIndex] == WEAPON_VERGIL_YAMATO)
	{
		return true;
	}
	return false;
}




void DanteAirStinger(byte8 * baseAddr)
{
	if (!baseAddr)
	{
		return;
	}
	auto & actorData = *reinterpret_cast<ACTOR_DATA_DANTE *>(baseAddr);
	if (actorData.character != CHAR_DANTE)
	{
		return;
	}
	auto & gamepad = GetGamepad(0);
	auto BufferStinger = [&]()
	{
		if
		(
			(gamepad.buttons[0] & GAMEPAD_RIGHT_SHOULDER) &&
			(GetRelativeTiltDirection(actorData) == TILT_DIRECTION_DOWN) &&
			(gamepad.buttons[0] & GAMEPAD_Y)
		)
		{
			actorData.bufferedAction = ACTION_DANTE_REBELLION_STINGER_LEVEL_2;
		}
	};
	if (actorData.state & STATE_IN_AIR)
	{
		//if (IsWeaponActive(actorData))
		//{
		//	if (actorData.nextActionRequestPolicy[NEXT_ACTION_REQUEST_POLICY_MELEE_ATTACK] == NEXT_ACTION_REQUEST_POLICY_BUFFER)
		//	{
		//		BufferStinger();
		//	}
		//	if (actorData.nextActionRequestPolicy[NEXT_ACTION_REQUEST_POLICY_MELEE_ATTACK] == NEXT_ACTION_REQUEST_POLICY_EXECUTE)
		//	{
		//		if (actorData.bufferedAction)
		//		{
		//			return;
		//		}
		//		BufferStinger();
		//	}
		//}
		//else
		{
			if
			(
				(gamepad.buttons[0] & GAMEPAD_RIGHT_SHOULDER) &&
				(GetRelativeTiltDirection(actorData) == TILT_DIRECTION_UP) &&
				(gamepad.buttons[0] & GAMEPAD_Y)
			)
			{
				TriggerAttack(actorData, ACTION_DANTE_REBELLION_STINGER_LEVEL_2);
			}
		}
	}
}

















//enum EVENT
//{
//	EVENT_ENABLE_YAMATO,
//};
//
//
//typedef void(__fastcall * ParentChildFunc_t)(byte8 *, byte8 *);
//
//
//
//template <typename T1, typename T2, typename T3 = void>
//struct Pair
//{
//	typedef T3(__fastcall * type)(T1, T2);
//};






//typedef void(__fastcall * EventEnableYamato_t)(byte8 *, byte8 *);
//vector<EventEnableYamato_t, 64> EventEnableYamato;
//
//inline void TriggerEventEnableYamato
//(
//	byte8 * parentBaseAddr,
//	byte8 * childBaseAddr
//)
//{
//	for_all(index, EventEnableYamato.count)
//	{
//		EventEnableYamato[index](parentBaseAddr, childBaseAddr);
//	}
//}
//
//typedef void(__fastcall * EventDisableYamato_t)(byte8 *, byte8 *);
//vector<EventDisableYamato_t, 64> EventDisableYamato;
//
//inline void TriggerEventDisableYamato
//(
//	byte8 * parentBaseAddr,
//	byte8 * childBaseAddr
//)
//{
//	for_all(index, EventDisableYamato.count)
//	{
//		EventDisableYamato[index](parentBaseAddr, childBaseAddr);
//	}
//}



//typedef void(__fastcall * EventVergilYamatoMeleeAttackBuffer_t)(byte8 *);


template <typename T1, typename T2 = void>
struct Signature1
{
	typedef T2(__fastcall * type)(T1);
};

template <typename T1, typename T2, typename T3 = void>
struct Signature2
{
	typedef T3(__fastcall * type)(T1, T2);
};


//vector<Signature1<byte8 *>::type, 8> EventVergilYamatoMeleeAttackBuffer;
//
//
//void EventVergilYamatoMeleeAttackBuffer_Default(byte8 *)
//{
//	MessageBoxA(0, "EVENT_VERGIL_MELEE_ATTACK_BUFFER", 0, 0);
//}
//
//
//
//void func()
//{
//	EventVergilYamatoMeleeAttackBuffer.Push(EventVergilYamatoMeleeAttackBuffer_Default);
//}
//
//
//
//vector<Signature1<byte8 *>::type, 8> EventMeleeAttackBuffer;
//vector<Signature1<byte8 *>::type, 8> EventMeleeAttackExecute;
//vector<Signature1<byte8 *>::type, 8> EventSwordmasterGunslingerBuffer;
//vector<Signature1<byte8 *>::type, 8> EventSwordmasterGunslingerExecute;
//vector<Signature1<byte8 *>::type, 8> EventRoyalguardBuffer;
//vector<Signature1<byte8 *>::type, 8> EventRoyalguardExecute;
//vector<Signature1<byte8 *>::type, 8> EventTricksterBuffer;
//vector<Signature1<byte8 *>::type, 8> EventTricksterExecute;
//vector<Signature1<byte8 *>::type, 8> EventRangedAttackBuffer;
//vector<Signature1<byte8 *>::type, 8> EventRangedAttackExecute;
//
//
//
//
//vector<Signature1<byte8 *>::type, 8> EventNextActionRequestPolicyUpdate;
//
//void TriggerEventNextActionRequestPolicyUpdate(byte8 * baseAddr)
//{
//	for_all(index, EventNextActionRequestPolicyUpdate.count)
//	{
//		EventNextActionRequestPolicyUpdate[index](baseAddr);
//	}
//}
//
//
//
//
//
//
//bool IsParent(byte8 * baseAddr)
//{
//	auto & parentActorData = *reinterpret_cast<ACTOR_DATA_DANTE *>(baseAddr);
//	if (parentActorData.character != CHAR_DANTE)
//	{
//		return false;
//	}
//	if (parentActorData.newParentBaseAddr)
//	{
//		return false;
//	}
//	if (!parentActorData.newChildBaseAddr[CHAR_VERGIL])
//	{
//		return false;
//	}
//	auto & childActorData = *reinterpret_cast<ACTOR_DATA_VERGIL *>(parentActorData.newChildBaseAddr[CHAR_VERGIL]);
//	if (childActorData.character != CHAR_VERGIL)
//	{
//		return false;
//	}
//	return true;
//}
//
//


































template
<
	uint8 id,
	byte16 button,
	typename T
>
bool Buffer(T & actorData)
{
	auto & gamepad = GetGamepad(0);

	uint8 style = 0;
	uint8 meleeWeapon = 0;
	uint8 rangedWeapon = 0;

	if constexpr (typematch(T, ACTOR_DATA_DANTE))
	{
		if constexpr (id == NEXT_ACTION_REQUEST_POLICY_MELEE_ATTACK)
		{
			meleeWeapon = actorData.newMeleeWeaponMap[actorData.newMeleeWeaponIndex];
			if (meleeWeapon > WEAPON_DANTE_BEOWULF)
			{
				meleeWeapon = WEAPON_DANTE_REBELLION;
			}
		}
		else if constexpr (id == NEXT_ACTION_REQUEST_POLICY_SWORDMASTER_GUNSLINGER)
		{
			style = actorData.newStyle;
			meleeWeapon = actorData.newMeleeWeaponMap[actorData.newMeleeWeaponIndex];
			if (meleeWeapon > WEAPON_DANTE_BEOWULF)
			{
				meleeWeapon = WEAPON_DANTE_REBELLION;
			}
			rangedWeapon = actorData.newRangedWeaponMap[actorData.newRangedWeaponIndex];
			if (rangedWeapon > WEAPON_DANTE_KALINA_ANN)
			{
				rangedWeapon = WEAPON_DANTE_EBONY_IVORY;
			}
			rangedWeapon -= WEAPON_DANTE_EBONY_IVORY;
		}
		else if constexpr (id == NEXT_ACTION_REQUEST_POLICY_RANGED_ATTACK)
		{
			rangedWeapon = actorData.newRangedWeaponMap[actorData.newRangedWeaponIndex];
			if (rangedWeapon > WEAPON_DANTE_KALINA_ANN)
			{
				rangedWeapon = WEAPON_DANTE_EBONY_IVORY;
			}
			rangedWeapon -= WEAPON_DANTE_EBONY_IVORY;
		}
	}
	else if constexpr (typematch(T, ACTOR_DATA_VERGIL))
	{
		if constexpr (id == NEXT_ACTION_REQUEST_POLICY_MELEE_ATTACK)
		{
			meleeWeapon = actorData.newMeleeWeaponMap[actorData.newMeleeWeaponIndex];
			if (meleeWeapon > WEAPON_VERGIL_FORCE_EDGE)
			{
				meleeWeapon = WEAPON_VERGIL_YAMATO;
			}
			meleeWeapon -= WEAPON_VERGIL_YAMATO;
		}
	}

	if
	(
		(gamepad.buttons[0] & GAMEPAD_RIGHT_SHOULDER) &&
		(GetRelativeTiltDirection(actorData) == TILT_DIRECTION_UP) &&
		(gamepad.buttons[0] & button)
	)
	{
		if (actorData.state & STATE_ON_FLOOR)
		{
			if constexpr (typematch(T, ACTOR_DATA_DANTE))
			{
				if constexpr (id == NEXT_ACTION_REQUEST_POLICY_MELEE_ATTACK)
				{
					actorData.bufferedAction = lockOnForwardMeleeAttackDante[meleeWeapon][0];
				}
				else if constexpr (id == NEXT_ACTION_REQUEST_POLICY_SWORDMASTER_GUNSLINGER)
				{
					actorData.bufferedAction = (style == STYLE_DANTE_SWORDMASTER) ? lockOnForwardSwordmasterDante[meleeWeapon][0] : lockOnForwardGunslingerDante[rangedWeapon][0];
				}
				else if constexpr (id == NEXT_ACTION_REQUEST_POLICY_ROYALGUARD)
				{
					actorData.bufferedAction = lockOnForwardRoyalguardDante[0];
				}
				else if constexpr (id == NEXT_ACTION_REQUEST_POLICY_TRICKSTER_DARK_SLAYER)
				{
					actorData.bufferedAction = lockOnForwardTricksterDante[0];
				}
				else if constexpr (id == NEXT_ACTION_REQUEST_POLICY_RANGED_ATTACK)
				{
					actorData.bufferedAction = lockOnForwardRangedAttackDante[rangedWeapon][0];
				}
			}
			else if constexpr (typematch(T, ACTOR_DATA_VERGIL))
			{
				// dark slayer
				// melee attack
			}
		}
		else
		{
			if constexpr (typematch(T, ACTOR_DATA_DANTE))
			{
				if constexpr (id == NEXT_ACTION_REQUEST_POLICY_ROYALGUARD)
				{
					actorData.bufferedAction = lockOnForwardRoyalguardDante[1];
				}
				else if constexpr (id == NEXT_ACTION_REQUEST_POLICY_TRICKSTER_DARK_SLAYER)
				{
					actorData.bufferedAction = lockOnForwardTricksterDante[1];
				}
			}
			else if constexpr (typematch(T, ACTOR_DATA_VERGIL))
			{
				// dark slayer
			}
		}
		return true;
	}

	if
	(
		(gamepad.buttons[0] & GAMEPAD_RIGHT_SHOULDER) &&
		(GetRelativeTiltDirection(actorData) == TILT_DIRECTION_DOWN) &&
		(gamepad.buttons[0] & button)
	)
	{
		if (actorData.state & STATE_ON_FLOOR)
		{
			if constexpr (typematch(T, ACTOR_DATA_DANTE))
			{
				if constexpr (id == NEXT_ACTION_REQUEST_POLICY_MELEE_ATTACK)
				{
					actorData.bufferedAction = lockOnBackMeleeAttackDante[meleeWeapon][0];
				}
				else if constexpr (id == NEXT_ACTION_REQUEST_POLICY_SWORDMASTER_GUNSLINGER)
				{
					if (style == STYLE_DANTE_SWORDMASTER)
					{
						actorData.bufferedAction = lockOnBackSwordmasterDante[meleeWeapon][0];
					}
				}
				else if constexpr (id == NEXT_ACTION_REQUEST_POLICY_ROYALGUARD)
				{
					actorData.bufferedAction = lockOnBackRoyalguardDante[0];
				}
			}
			else if constexpr (typematch(T, ACTOR_DATA_VERGIL))
			{
			}
		}
		else
		{
			// trick down
			if constexpr (typematch(T, ACTOR_DATA_VERGIL))
			{
			}
		}
		return true;
	}

	if (gamepad.buttons[0] & button)
	{
		if (actorData.state & STATE_ON_FLOOR)
		{
			if constexpr (typematch(T, ACTOR_DATA_DANTE))
			{
				if constexpr (id == NEXT_ACTION_REQUEST_POLICY_MELEE_ATTACK)
				{
					actorData.bufferedAction = meleeAttackDante[meleeWeapon][0];
				}
				else if constexpr (id == NEXT_ACTION_REQUEST_POLICY_SWORDMASTER_GUNSLINGER)
				{
					actorData.bufferedAction = (style == STYLE_DANTE_SWORDMASTER) ? swordmasterDante[meleeWeapon][0] : gunslingerDante[rangedWeapon][0];
				}
				else if constexpr (id == NEXT_ACTION_REQUEST_POLICY_ROYALGUARD)
				{
					actorData.bufferedAction = royalguardDante[0];
				}
				else if constexpr (id == NEXT_ACTION_REQUEST_POLICY_TRICKSTER_DARK_SLAYER)
				{
					actorData.bufferedAction = tricksterDante[0];
				}
				else if constexpr (id == NEXT_ACTION_REQUEST_POLICY_RANGED_ATTACK)
				{
					actorData.bufferedAction = rangedAttackDante[rangedWeapon][0];
				}
			}
			else if constexpr (typematch(T, ACTOR_DATA_VERGIL))
			{
			}
		}
		else
		{
			if constexpr (typematch(T, ACTOR_DATA_DANTE))
			{
				if constexpr (id == NEXT_ACTION_REQUEST_POLICY_MELEE_ATTACK)
				{
					actorData.bufferedAction = meleeAttackDante[meleeWeapon][1];
				}
				else if constexpr (id == NEXT_ACTION_REQUEST_POLICY_SWORDMASTER_GUNSLINGER)
				{
					actorData.bufferedAction = (style == STYLE_DANTE_SWORDMASTER) ? swordmasterDante[meleeWeapon][1] : gunslingerDante[rangedWeapon][1];
				}
				else if constexpr (id == NEXT_ACTION_REQUEST_POLICY_ROYALGUARD)
				{
					actorData.bufferedAction = royalguardDante[1];
				}
				else if constexpr (id == NEXT_ACTION_REQUEST_POLICY_TRICKSTER_DARK_SLAYER)
				{
					actorData.bufferedAction = tricksterDante[1];
				}
				else if constexpr (id == NEXT_ACTION_REQUEST_POLICY_RANGED_ATTACK)
				{
					actorData.bufferedAction = rangedAttackDante[rangedWeapon][1];
				}
			}
			else if constexpr (typematch(T, ACTOR_DATA_VERGIL))
			{
			}
		}
		return true;
	}

	return false;
}



template
<
	uint8 id,
	byte16 button,
	typename T1,
	typename T2
>
bool BufferHelper
(
	T1 & parentActorData,
	T2 & childActorData
)
{
	if (parentActorData.nextActionRequestPolicy[id] == NEXT_ACTION_REQUEST_POLICY_BUFFER)
	{
		if (Buffer<id, button>(childActorData))
		{
			MessageBoxA(0, "BUFFER", 0, 0);
		}
	}
	else if (parentActorData.nextActionRequestPolicy[id] == NEXT_ACTION_REQUEST_POLICY_EXECUTE)
	{
		if (childActorData.bufferedAction)
		{
			return true;
		}
		if (Buffer<id, button>(childActorData))
		{
			MessageBoxA(0, "EXECUTE", 0, 0);
			return true;
		}
	}
	return false;
}














void DanteYamato(byte8 * baseAddr)
{
	#define OnceEnable(dest, index) dest.newSect[index] = true
	#define OnceDisable(dest, index) dest.newSect[index] = false
	#define OnceStart(dest, index) if (dest.newSect[index]) { OnceDisable(dest, index)
	#define OnceEnd }

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








	if (IsYamatoSelected(parentActorData) && !IsWeaponActive(parentActorData))
	{
		OnceStart(parentActorData, 0);
		{
			//TriggerEventEnableYamato(parentActorData, childActorData);
		}
		OnceEnd;
	}
	else
	{
		OnceEnable(parentActorData, 0);
	}





	if (!IsYamatoSelected(parentActorData) && !IsWeaponActive(childActorData))
	{
		OnceStart(parentActorData, 1);
		{
			//TriggerEventDisableYamato(parentActorData, childActorData);
		}
		OnceEnd;
	}
	else
	{
		OnceEnable(parentActorData, 1);
	}

	// Parent

	if (IsYamatoSelected(parentActorData))
	{
		DisableControl(parentActorData);
	}

	if (!IsYamatoSelected(parentActorData))
	{
		if (!IsWeaponActive(childActorData))
		{
			EnableControl(parentActorData);
			//SetLeader(parentActorData);
		}
	}




	if (!IsYamatoSelected(parentActorData))
	{
		if (IsWeaponActive(childActorData))
		{
			if (BufferHelper<NEXT_ACTION_REQUEST_POLICY_MELEE_ATTACK          , GAMEPAD_Y>(parentActorData, childActorData)) { return; }
			if (BufferHelper<NEXT_ACTION_REQUEST_POLICY_SWORDMASTER_GUNSLINGER, GAMEPAD_B>(parentActorData, childActorData)) { return; }
			if (BufferHelper<NEXT_ACTION_REQUEST_POLICY_ROYALGUARD            , GAMEPAD_B>(parentActorData, childActorData)) { return; }
			if (BufferHelper<NEXT_ACTION_REQUEST_POLICY_TRICKSTER_DARK_SLAYER             , GAMEPAD_B>(parentActorData, childActorData)) { return; }
			if (BufferHelper<NEXT_ACTION_REQUEST_POLICY_RANGED_ATTACK         , GAMEPAD_X>(parentActorData, childActorData)) { return; }
		}
	}






















	// Child

	if (!IsYamatoSelected(parentActorData))
	{


		DisableControl(childActorData);
		// childActorData.newButtonMask = 0;
		// childActorData.newEnableLeftStick = false;
	}

	if (IsYamatoSelected(parentActorData))
	{
		if (!IsWeaponActive(parentActorData))
		{
			EnableControl(childActorData);
			//SetLeader(childActorData);
			// childActorData.newButtonMask = 0xFFFF;
			// childActorData.newEnableLeftStick = true;
		}
	}

	if (IsYamatoSelected(parentActorData))
	{
		if (IsWeaponActive(parentActorData))
		{
			if (parentActorData.nextActionRequestPolicy[4] == NEXT_ACTION_REQUEST_POLICY_EXECUTE)
			{
				if
				(
					(gamepad.buttons[0] & GAMEPAD_RIGHT_SHOULDER) &&
					(GetRelativeTiltDirection(childActorData) == TILT_DIRECTION_UP) &&
					(gamepad.buttons[0] & GAMEPAD_Y)
				)
				{
					EndMotion(parentActorData);

					EnableControl(childActorData);

					//Camera_followBaseAddr = childActorData;

					// parentActorData.newIsLeader = false;
					// childActorData.newIsLeader = true;
					SetLeader(childActorData);
					CopyPosition(parentActorData, childActorData);
					


					if (childActorData.state & STATE_ON_FLOOR)
					{
						TriggerAttack(childActorData, 5); // Rapid Slash
					}
				}
				else if
				(
					(gamepad.buttons[0] & GAMEPAD_RIGHT_SHOULDER) &&
					(GetRelativeTiltDirection(childActorData) == TILT_DIRECTION_DOWN) &&
					(gamepad.buttons[0] & GAMEPAD_Y)
				)
				{
					EndMotion(parentActorData);

					EnableControl(childActorData);

					//Camera_followBaseAddr = childActorData;

					// parentActorData.newIsLeader = false;
					// childActorData.newIsLeader = true;
					SetLeader(childActorData);
					CopyPosition(parentActorData, childActorData);

					if (childActorData.state & STATE_ON_FLOOR)
					{
						TriggerAttack(childActorData, 7); // High Time
					}
				}
				else if (gamepad.buttons[0] & GAMEPAD_Y)
				{
					EndMotion(parentActorData);

					EnableControl(childActorData);

					//Camera_followBaseAddr = childActorData;

					// parentActorData.newIsLeader = false;
					// childActorData.newIsLeader = true;
					SetLeader(childActorData);
					CopyPosition(parentActorData, childActorData);

					if (childActorData.state & STATE_ON_FLOOR)
					{
						TriggerAttack(childActorData, 1); // Combo 1 Part 1
					}
					else
					{
						TriggerAttack(childActorData, 11); // Aerial Rave
					}
				}
			}
		}
	}














	#undef OnceReset
	#undef OnceEnd
	#undef OnceStart
}

void ActorLoop(byte8 * baseAddr)
{
	g_actorLoopCounter++;
	DanteYamato(baseAddr);


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
