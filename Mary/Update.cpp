#include "Update.h"

uint64 ticksPerSecond      = 0;
uint64 ticksPerMillisecond = 0;
uint64 savedTickCount      = 0;



uint64 g_mainLoopCounter = 0;
uint64 g_actorLoopCounter = 0;







//bool millionStab = false;

// As soon as millionStab is true, start daemon and check for state.

// Consider all actors for millionStab.

//__declspec(noinline) void VergilMillionStab(byte8 * baseAddr)
//{
//	auto & actorData = *(ACTOR_DATA *)baseAddr;
//	if (actorData.character != CHAR_VERGIL)
//	{
//		return;
//	}
//	if (actorData.move != 39)
//	{
//		return;
//	}
//	if (actorData.motionData[1].group != 5)
//	{
//		return;
//	}
//	if (actorData.motionData[1].index != 11)
//	{
//		return;
//	}
//	if (actorData.inputData[16].flags[4] < 6)
//	{
//		return;
//	}
//	if (!actorData.childBaseAddr[0])
//	{
//		return;
//	}
//	auto & childActorData = *(ACTOR_DATA *)actorData.childBaseAddr[0];
//
//
//
//	//actorData.collisionIndex = 1;
//	//actorData.hide = true;
//	//actorData.hideWeapons = true;
//	//actorData.hideSummonedSwords = false;
//	actorData.buttonMask = 0;
//
//
//
//
//
//
//
//	childActorData.motionState1[0] = 0x11;
//	childActorData.motionState1[1] = 0xD;
//	childActorData.motionState1[2] = 0x11;
//	childActorData.motionState1[3] = 0x11;
//
//	childActorData.motionState2[0] = 0x401;
//	childActorData.motionState2[1] = 0xB0001;
//	childActorData.motionState2[2] = 0xA0001;
//
//	childActorData.move = 14;
//
//
//	childActorData.inputData[16].flags[4] = 6;
//
//
//	//if (actorData.inputData[16].flags[4] < 6)
//	//{
//	//	return;
//	//}
//
//
//	childActorData.buttonMask = GAMEPAD_RIGHT_SHOULDER | GAMEPAD_Y;
//
//
//	//childActorData.lastMove = 8;
//	//childActorData.chainCount = 2;
//
//
//	//childActorData.collisionIndex = 1;
//	//childActorData.hide = false;
//	//childActorData.hideWeapons = false;
//	//childActorData.hideSummonedSwords = false;
//
//	
//
//
//}










template <typename T>
void EnableButton(T & actorData, byte16 button)
{
	if (!(actorData.newButtonMask & button))
	{
		actorData.newButtonMask += button;
	}
}

template <typename T>
void DisableButton(T & actorData, byte16 button)
{
	if (actorData.newButtonMask & button)
	{
		actorData.newButtonMask -= button;
	}
}

//template <typename T>
//void SetBusyFlag(T & actorData)
//{
//	auto & motionState = actorData.motionState3[1];
//	if (!(motionState & MOTION_STATE_BUSY))
//	{
//		motionState += MOTION_STATE_BUSY;
//	}
//}
//
//template <typename T>
//void ClearBusyFlag(T & actorData)
//{
//	auto & motionState = actorData.motionState3[1];
//	if (motionState & MOTION_STATE_BUSY)
//	{
//		motionState -= MOTION_STATE_BUSY;
//	}
//}

template <typename T>
bool IsBusy(T & actorData)
{
	if (actorData.state & 0x10000)
	{
		return true;
	}
	return false;
}

//template <typename T>
//void ResetState(T & actorData)
//{
//	const_for_all(index, 16)
//	{
//		actorData.motionState1[index] = 0;
//	}
//
//	actorData.motionState2[0] = 1;
//	actorData.motionState2[1] = 0;
//	actorData.motionState2[2] = 4;
//	actorData.motionState2[3] = 0;
//	actorData.motionState2[4] = 0;
//	actorData.motionState2[5] = 0;
//
//	actorData.motionState3[0] = 0x1C1B;
//	actorData.motionState3[1] = 1;
//	actorData.motionState3[2] = 0;
//}
//
//template <typename T>
//void SetAttackState2(T & actorData)
//{
//	const_for_all(index, 16)
//	{
//		actorData.motionState1[index] = 0;
//	}
//
//	actorData.motionState2[0] = 0x11;
//	actorData.motionState2[1] = 1;
//	actorData.motionState2[2] = 0x11;
//	actorData.motionState2[3] = 0x11;
//	actorData.motionState2[4] = 1;
//	actorData.motionState2[5] = 0;
//
//	actorData.motionState3[0] = 0x401;
//	actorData.motionState3[1] = 0x10001;
//	actorData.motionState3[2] = 0;
//}



//template <typename T>
//void ClearMotionData(T & actorData)
//{
//	const_for_all(index, 2)
//	{
//		actorData.motionData[index].group = 0;
//		actorData.motionData[index].index = 0;
//	}
//}
//
//
//
//
//template <typename T>
//void ClearExecutionState(T & actorData)
//{
//	const_for_all(index, 16)
//	{
//		actorData.motionState1[index] = 0;
//	}
//}


















//template <typename T>
//void SetAttackState(T & actorData)
//{
//	actorData.motionState2[0] = 0x11;
//	actorData.motionState2[1] = 1;
//	actorData.motionState2[2] = 0x11;
//	actorData.motionState2[3] = 0x11;
//	actorData.motionState2[4] = 1;
//	actorData.motionState2[5] = 0;
//}
//
//template <typename T>
//void ClearAttackState(T & actorData)
//{
//	actorData.motionState2[0] = 1;
//	actorData.motionState2[1] = 0;
//	actorData.motionState2[2] = 4;
//	actorData.motionState2[3] = 0;
//	actorData.motionState2[4] = 0;
//	actorData.motionState2[5] = 0;
//}
//
//template <typename T>
//void SetBusyState(T & actorData)
//{
//	actorData.motionState3[0] = 0x401;
//	actorData.motionState3[1] = 0x10001;
//	actorData.motionState3[2] = 0;
//}
//
//template <typename T>
//void ClearBusyState(T & actorData)
//{
//	actorData.motionState3[0] = 0x1C1B;
//	actorData.motionState3[1] = 1;
//	actorData.motionState3[2] = 0;
//}






//
//template <typename T1, typename T2>
//void CopyState(T1 & source, T2 & target)
//{
//	//memcpy(target.motionData             , source.motionData             , 4 );
//	//memcpy(target.nextActionRequestPolicy, source.nextActionRequestPolicy, 64);
//	//memcpy(target.var_3E00               , source.var_3E00               , 16);
//
//	target.permissions = source.permissions;
//	target.state       = source.state;
//	target.lastState   = source.lastState;
//}








// @Todo: Set different permissions according to state.
// Floor, air.




template <typename T>
void ResetState1(T & actorData)
{

	
	Log("ResetState1");


	const_for_all(index, 2)
	{
		actorData.motionData[index].group = 0;
		actorData.motionData[index].index = 0;
	}
	const_for_all(index, 16)
	{
		actorData.nextActionRequestPolicy[index] = NEXT_ACTION_REQUEST_POLICY_IGNORE;
	}
	actorData.var_3E00[0] = 1;
	actorData.var_3E00[1] = 0;
	actorData.var_3E00[2] = 4;
	actorData.var_3E00[3] = 0;

	memset(actorData.var_3E10, 0, 32);

	actorData.permissions = 0x1C1B;
	actorData.state = 1;
	actorData.lastState = 0;
}




template <typename T>
void ResetState2(T & actorData)
{
	Log("ResetState2");

	const_for_all(index, 2)
	{
		actorData.motionData[index].group = 0;
		actorData.motionData[index].index = 0;
	}
	const_for_all(index, 16)
	{
		actorData.nextActionRequestPolicy[index] = NEXT_ACTION_REQUEST_POLICY_IGNORE;
	}
	actorData.var_3E00[0] = 1;
	actorData.var_3E00[1] = 0;
	actorData.var_3E00[2] = 4;
	actorData.var_3E00[3] = 0;

	memset(actorData.var_3E10, 0, 32);

	actorData.permissions = 0x1C1B;
	actorData.state = 1;
	actorData.lastState = 0;
}

template <typename T>
void ResetState3(T & actorData)
{

	Log("ResetState3");



	const_for_all(index, 2)
	{
		actorData.motionData[index].group = 0;
		actorData.motionData[index].index = 0;
	}
	const_for_all(index, 16)
	{
		actorData.nextActionRequestPolicy[index] = NEXT_ACTION_REQUEST_POLICY_IGNORE;
	}
	actorData.var_3E00[0] = 1;
	actorData.var_3E00[1] = 0;
	actorData.var_3E00[2] = 4;
	actorData.var_3E00[3] = 0;

	memset(actorData.var_3E10, 0, 32);

	actorData.permissions = 0x1C1B;
	actorData.state = 1;
	actorData.lastState = 0;
}


template <typename T>
void ResetState4(T & actorData)
{

	Log("ResetState4");

	const_for_all(index, 2)
	{
		actorData.motionData[index].group = 0;
		actorData.motionData[index].index = 0;
	}
	const_for_all(index, 16)
	{
		actorData.nextActionRequestPolicy[index] = NEXT_ACTION_REQUEST_POLICY_IGNORE;
	}
	actorData.var_3E00[0] = 1;
	actorData.var_3E00[1] = 0;
	actorData.var_3E00[2] = 4;
	actorData.var_3E00[3] = 0;

	memset(actorData.var_3E10, 0, 32);

	actorData.permissions = 0x1C1B;
	actorData.state = 1;
	actorData.lastState = 0;
}

template <typename T>
void ResetState5(T & actorData)
{

	Log("ResetState5");

	const_for_all(index, 2)
	{
		actorData.motionData[index].group = 0;
		actorData.motionData[index].index = 0;
	}
	const_for_all(index, 16)
	{
		actorData.nextActionRequestPolicy[index] = NEXT_ACTION_REQUEST_POLICY_IGNORE;
	}
	actorData.var_3E00[0] = 1;
	actorData.var_3E00[1] = 0;
	actorData.var_3E00[2] = 4;
	actorData.var_3E00[3] = 0;

	memset(actorData.var_3E10, 0, 32);

	actorData.permissions = 0x1C1B;
	actorData.state = 1;
	actorData.lastState = 0;
}
template <typename T>
void ResetState6(T & actorData)
{

	Log("ResetState6");

	const_for_all(index, 2)
	{
		actorData.motionData[index].group = 0;
		actorData.motionData[index].index = 0;
	}
	const_for_all(index, 16)
	{
		actorData.nextActionRequestPolicy[index] = NEXT_ACTION_REQUEST_POLICY_IGNORE;
	}
	actorData.var_3E00[0] = 1;
	actorData.var_3E00[1] = 0;
	actorData.var_3E00[2] = 4;
	actorData.var_3E00[3] = 0;

	memset(actorData.var_3E10, 0, 32);

	actorData.permissions = 0x1C1B;
	actorData.state = 1;
	actorData.lastState = 0;
}


template <typename T>
void ResetState7(T & actorData)
{

	Log("ResetState7");

	const_for_all(index, 2)
	{
		actorData.motionData[index].group = 0;
		actorData.motionData[index].index = 0;
	}
	const_for_all(index, 16)
	{
		actorData.nextActionRequestPolicy[index] = NEXT_ACTION_REQUEST_POLICY_IGNORE;
	}
	actorData.var_3E00[0] = 1;
	actorData.var_3E00[1] = 0;
	actorData.var_3E00[2] = 4;
	actorData.var_3E00[3] = 0;

	memset(actorData.var_3E10, 0, 32);

	actorData.permissions = 0x1C1B;
	actorData.state = 1;
	actorData.lastState = 0;
}


template <typename T>
void ResetState8(T & actorData)
{

	Log("ResetState8");

	const_for_all(index, 2)
	{
		actorData.motionData[index].group = 0;
		actorData.motionData[index].index = 0;
	}
	const_for_all(index, 16)
	{
		actorData.nextActionRequestPolicy[index] = NEXT_ACTION_REQUEST_POLICY_IGNORE;
	}
	actorData.var_3E00[0] = 1;
	actorData.var_3E00[1] = 0;
	actorData.var_3E00[2] = 4;
	actorData.var_3E00[3] = 0;

	memset(actorData.var_3E10, 0, 32);

	actorData.permissions = 0x1C1B;
	actorData.state = 1;
	actorData.lastState = 0;
}





















template <typename T>
void SetAttackState(T & actorData)
{
	actorData.var_3E00[0] = 0x11;
	actorData.var_3E00[1] = 1;
	actorData.var_3E00[2] = 0x11;
	actorData.var_3E00[3] = 0x11;

	actorData.var_3E10[0] = 1;

	actorData.permissions = 0x401;
	actorData.state = 0x10001;
	actorData.lastState = 1;
}












inline void SetYamato(ACTOR_DATA_VERGIL & actorData)
{
	if (actorData.newMeleeWeaponMap[0] != WEAPON_VERGIL_YAMATO)
	{
		actorData.newMeleeWeaponMap[0] = WEAPON_VERGIL_YAMATO;
		actorData.newMeleeWeaponCount = 1;
	}
}

inline void ClearYamato(ACTOR_DATA_VERGIL & actorData)
{
	if (actorData.newMeleeWeaponMap[0] == WEAPON_VERGIL_YAMATO)
	{
		actorData.newMeleeWeaponMap[0] = WEAPON_VOID;
		actorData.newMeleeWeaponCount = 0;
	}
}

template <typename T>
bool WantsYamato(T & actorData)
{
	if (actorData.newMeleeWeaponMap[actorData.newMeleeWeaponIndex] == WEAPON_VERGIL_YAMATO)
	{
		return true;
	}
	return false;
}

// @Todo: Add Nero Angelo.


























void old_DanteYamato()
{
	for_each(index, 2, Actor_actorBaseAddr.count)
	{
		auto baseAddr = Actor_actorBaseAddr[index];
		if (!baseAddr)
		{
			continue;
		}
		auto & parentActorData = *reinterpret_cast<ACTOR_DATA_DANTE *>(baseAddr);
		if (parentActorData.character != CHAR_DANTE)
		{
			continue;
		}
		if (parentActorData.newParentBaseAddr)
		{
			continue;
		}
		if (!parentActorData.newChildBaseAddr[CHAR_VERGIL])
		{
			continue;
		}
		auto & childActorData = *reinterpret_cast<ACTOR_DATA_VERGIL *>(parentActorData.newChildBaseAddr[CHAR_VERGIL]);
		if (childActorData.character != CHAR_VERGIL)
		{
			continue;
		}

		// Start End

		if (WantsYamato(parentActorData))
		{
			DisableButton(parentActorData, GAMEPAD_Y);

			if (parentActorData.style == STYLE_DANTE_SWORDMASTER)
			{
				DisableButton(parentActorData, GAMEPAD_B);
			}

			EnableButton(childActorData, GAMEPAD_Y);

			if (!IsWeaponActive(parentActorData))
			{
				SetYamato(childActorData);
			}
		}
		else
		{
			EnableButton(parentActorData, GAMEPAD_Y);

			if (parentActorData.style == STYLE_DANTE_SWORDMASTER)
			{
				EnableButton(parentActorData, GAMEPAD_B);
			}

			DisableButton(childActorData, GAMEPAD_Y);

			if (!IsWeaponActive(childActorData))
			{
				ClearYamato(childActorData);
			}
		}

		// Update


		//if (IsWeaponActive(parentActorData))
		//{
		//	CopyState(parentActorData, childActorData);
		//}

		//if (IsWeaponActive(childActorData))
		//{
		//	CopyState(childActorData, parentActorData);
		//}






		#define OnceStart(dest, index) if (dest.newSect[index]) { dest.newSect[index] = false;
		#define OnceEnd }
		// @Research: Maybe enable and disable are better.
		#define OnceEnable(dest, index) dest.newSect[index] = true;
		#define OnceDisable(dest, index) dest.newSect[index] = false;













		





		if (IsWeaponActive(parentActorData))
		{
			childActorData.position = parentActorData.position;
			childActorData.direction = parentActorData.direction;
			childActorData.permissions = 0;
			childActorData.state = parentActorData.state;

			OnceEnable(childActorData, 0);

			if (parentActorData.nextActionRequestPolicy[4] == NEXT_ACTION_REQUEST_POLICY_EXECUTE)
			{
				childActorData.permissions += PERMISSION_INTERACTION_STYLE_ATTACK;

				if (childActorData.buttons[2] & GAMEPAD_Y)
				{
					ResetState1(parentActorData);
					parentActorData.permissions = 0;

					SetYamato(childActorData);

					OnceDisable(childActorData, 0);

					goto ParentEnd;
				}
			}
		}
		else
		{
			OnceStart(childActorData, 0);
			{
				ResetState3(childActorData);
			}
			OnceEnd;
		}
		ParentEnd:;








		if (IsWeaponActive(childActorData))
		{
			parentActorData.position = childActorData.position;
			parentActorData.direction = childActorData.direction;
			parentActorData.permissions = 0;
			parentActorData.state = childActorData.state;

			OnceEnable(parentActorData, 0);

			if (childActorData.nextActionRequestPolicy[4] == NEXT_ACTION_REQUEST_POLICY_EXECUTE)
			{
				parentActorData.permissions += PERMISSION_INTERACTION_STYLE_ATTACK;

				if
				(
					(parentActorData.buttons[2] & GAMEPAD_Y) ||
					(parentActorData.buttons[2] & GAMEPAD_X) ||
					(parentActorData.buttons[2] & GAMEPAD_B)
				)
				{
					ResetState4(childActorData);
					childActorData.permissions = 0;
					ClearYamato(childActorData);

					OnceDisable(parentActorData, 0);

					goto ChildEnd;
				}
			}

			if (childActorData.nextActionRequestPolicy[5] == NEXT_ACTION_REQUEST_POLICY_EXECUTE)
			{
				parentActorData.permissions += PERMISSION_JUMP_ROLL;

				if (parentActorData.buttons[2] & GAMEPAD_A)
				{
					ResetState4(childActorData);
					childActorData.permissions = 0;
					ClearYamato(childActorData);

					OnceDisable(parentActorData, 0);

					goto ChildEnd;
				}
			}

			if (childActorData.nextActionRequestPolicy[15] == NEXT_ACTION_REQUEST_POLICY_EXECUTE)
			{
				parentActorData.permissions += PERMISSION_WALK_RUN;

				if (parentActorData.leftStickRadius >= LEFT_STICK_DEADZONE)
				{
					ResetState4(childActorData);
					childActorData.permissions = 0;
					ClearYamato(childActorData);

					OnceDisable(parentActorData, 0);

					goto ChildEnd;
				}
			}
		}
		else
		{
			OnceStart(parentActorData, 0);
			{
				ResetState5(parentActorData);
			}
			OnceEnd;

			//childActorData.position = parentActorData.position;
			//childActorData.direction = parentActorData.direction;
			//childActorData.state = parentActorData.state;
		}
		ChildEnd:;















		#undef OnceReset
		#undef OnceEnd
		#undef OnceStart
		


		













	}
}










void DanteYamato(byte8 * baseAddr)
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

	// Start End

	if (WantsYamato(parentActorData))
	{
		DisableButton(parentActorData, GAMEPAD_Y);

		if (parentActorData.style == STYLE_DANTE_SWORDMASTER)
		{
			DisableButton(parentActorData, GAMEPAD_B);
		}

		EnableButton(childActorData, GAMEPAD_Y);

		if (!IsWeaponActive(parentActorData))
		{
			SetYamato(childActorData);
		}
	}
	else
	{
		EnableButton(parentActorData, GAMEPAD_Y);

		if (parentActorData.style == STYLE_DANTE_SWORDMASTER)
		{
			EnableButton(parentActorData, GAMEPAD_B);
		}

		DisableButton(childActorData, GAMEPAD_Y);

		if (!IsWeaponActive(childActorData))
		{
			ClearYamato(childActorData);
		}
	}

	// Update

	#define OnceStart(dest, index) if (dest.newSect[index]) { dest.newSect[index] = false;
	#define OnceEnd }
	#define OnceEnable(dest, index) dest.newSect[index] = true;
	#define OnceDisable(dest, index) dest.newSect[index] = false;

	if (IsWeaponActive(parentActorData))
	{
		childActorData.position = parentActorData.position;
		childActorData.direction = parentActorData.direction;
		childActorData.permissions = 0;
		childActorData.state = parentActorData.state;

		OnceEnable(childActorData, 0);

		if (parentActorData.nextActionRequestPolicy[4] == NEXT_ACTION_REQUEST_POLICY_EXECUTE)
		{
			childActorData.permissions += PERMISSION_INTERACTION_STYLE_ATTACK;

			if (childActorData.buttons[2] & GAMEPAD_Y)
			{
				ResetState1(parentActorData);
				parentActorData.permissions = 0;

				SetYamato(childActorData);

				OnceDisable(childActorData, 0);

				goto ParentEnd;
			}
		}
	}
	else
	{
		OnceStart(childActorData, 0);
		{
			ResetState3(childActorData);
		}
		OnceEnd;
	}
	ParentEnd:;

	if (IsWeaponActive(childActorData))
	{
		parentActorData.position = childActorData.position;
		parentActorData.direction = childActorData.direction;
		parentActorData.permissions = 0;
		parentActorData.state = childActorData.state;

		OnceEnable(parentActorData, 0);

		if (childActorData.nextActionRequestPolicy[4] == NEXT_ACTION_REQUEST_POLICY_EXECUTE)
		{
			parentActorData.permissions += PERMISSION_INTERACTION_STYLE_ATTACK;

			if
			(
				(parentActorData.buttons[2] & GAMEPAD_Y) ||
				(parentActorData.buttons[2] & GAMEPAD_X) ||
				(parentActorData.buttons[2] & GAMEPAD_B)
			)
			{
				ResetState4(childActorData);
				childActorData.permissions = 0;
				ClearYamato(childActorData);

				OnceDisable(parentActorData, 0);

				goto ChildEnd;
			}
		}

		if (childActorData.nextActionRequestPolicy[5] == NEXT_ACTION_REQUEST_POLICY_EXECUTE)
		{
			parentActorData.permissions += PERMISSION_JUMP_ROLL;

			if (parentActorData.buttons[2] & GAMEPAD_A)
			{
				ResetState4(childActorData);
				childActorData.permissions = 0;
				ClearYamato(childActorData);

				OnceDisable(parentActorData, 0);

				goto ChildEnd;
			}
		}

		if (childActorData.nextActionRequestPolicy[15] == NEXT_ACTION_REQUEST_POLICY_EXECUTE)
		{
			parentActorData.permissions += PERMISSION_WALK_RUN;

			if (parentActorData.leftStickRadius >= LEFT_STICK_DEADZONE)
			{
				ResetState4(childActorData);
				childActorData.permissions = 0;
				ClearYamato(childActorData);

				OnceDisable(parentActorData, 0);

				goto ChildEnd;
			}
		}
	}
	else
	{
		OnceStart(parentActorData, 0);
		{
			ResetState5(parentActorData);
		}
		OnceEnd;

		childActorData.position = parentActorData.position;
		childActorData.direction = parentActorData.direction;
		childActorData.state = parentActorData.state;
	}
	ChildEnd:;

	#undef OnceReset
	#undef OnceEnd
	#undef OnceStart
}
































int16 g_relativeTilt = 0;

/*
GAMEPAD_UP             = 0x1000,
GAMEPAD_RIGHT          = 0x2000,
GAMEPAD_DOWN           = 0x4000,
GAMEPAD_LEFT           = 0x8000,
*/













enum TILT_DIRECTION
{
	TILT_DIRECTION_UP,
	TILT_DIRECTION_RIGHT,
	TILT_DIRECTION_DOWN,
	TILT_DIRECTION_LEFT,
	TILT_DIRECTION_VOID = 255,
};

uint8 GetRelativeTiltDirection(byte8 * baseAddr)
{
	auto & actorData = *reinterpret_cast<ACTOR_DATA *>(baseAddr);
	if (actorData.leftStickRadius < 52) // 66 for camera.
	{
		return TILT_DIRECTION_VOID;
	}

	uint16 relativeTilt = (actorData.actorCameraDirection - actorData.leftStickPosition);

	{
		uint16 value = (relativeTilt - 0x6000);
		if (value <= 0x4000)
		{
			return TILT_DIRECTION_UP;
		}
	}

	{
		uint16 value = (relativeTilt + 0x6000);
		if (value <= 0x4000)
		{
			return TILT_DIRECTION_RIGHT;
		}
	}

	{
		uint16 value = (relativeTilt + 0x2000);
		if (value <= 0x4000)
		{
			return TILT_DIRECTION_DOWN;
		}
	}

	{
		uint16 value = (relativeTilt - 0x2000);
		if (value <= 0x4000)
		{
			return TILT_DIRECTION_LEFT;
		}
	}

	return TILT_DIRECTION_VOID;
}



void DanteSummonedSwords()
{
	for_each(index, 2, Actor_actorBaseAddr.count)
	{
		auto baseAddr = Actor_actorBaseAddr[index];
		if (!baseAddr)
		{
			continue;
		}
		auto & actorData = *reinterpret_cast<ACTOR_DATA_DANTE *>(baseAddr);
		if (actorData.character != CHAR_DANTE)
		{
			continue;
		}
		if (actorData.newParentBaseAddr)
		{
			continue;
		}
		if (!actorData.newChildBaseAddr[CHAR_VERGIL])
		{
			continue;
		}
		auto & childActorData = *reinterpret_cast<ACTOR_DATA_VERGIL *>(actorData.newChildBaseAddr[CHAR_VERGIL]);
		if (childActorData.character != CHAR_VERGIL)
		{
			continue;
		}
		if (actorData.buttons[2] & GAMEPAD_X)
		{
			func_223BE0(childActorData, 52);
		}
	}
}


















uint8 g_relativeTiltDirection = TILT_DIRECTION_VOID;


//uint64 g_mainCounter = 0;
//uint64 g_newCounter = 0;






void MainLoop()
{


	g_mainLoopCounter++;


	//g_mainCounter++;











	//return;

	//uint64 tickCount           = 0;
	//uint32 elapsedMilliseconds = 0;

	//Windows_GetTickCount(&tickCount);
	//elapsedMilliseconds = (uint32)((tickCount - savedTickCount) / ticksPerMillisecond);

	//if (elapsedMilliseconds >= 1000)
	//{
	//	savedTickCount = tickCount;
	//}


	//return;

	if (spawnActors)
	{
		spawnActors = false;

		Log("Spawn Actors.");


		Log("g_relativeTilt %llX", &g_relativeTilt);
		Log("g_relativeTiltDirection %llX", &g_relativeTiltDirection);













		auto danteBaseAddr = CreateActorDante();
		if (!danteBaseAddr)
		{
			return;
		}
		auto & danteActorData = *danteBaseAddr;
		Actor_actorBaseAddr.Push(danteActorData);




		const_for_all(index, 5)
		{
			danteActorData.newMeleeWeaponMap [index] = (WEAPON_DANTE_REBELLION   + index);
			danteActorData.newRangedWeaponMap[index] = (WEAPON_DANTE_EBONY_IVORY + index);
		}
		danteActorData.newMeleeWeaponCount = 3;
		danteActorData.newMeleeWeaponIndex = 0;
		danteActorData.newRangedWeaponCount = 3;
		danteActorData.newRangedWeaponIndex = 0;

		danteActorData.newMeleeWeaponMap[1] = WEAPON_DANTE_BEOWULF;
		danteActorData.newMeleeWeaponMap[2] = WEAPON_VERGIL_YAMATO;







		auto & mainActorData = *reinterpret_cast<ACTOR_DATA *>(Actor_actorBaseAddr[0]);

		//danteActorData.position = mainActorData.position;


		//return;


		





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


		vergilActorData.newDisableLeftStick = true;


		//auto & mainActorData = *reinterpret_cast<ACTOR_DATA *>(Actor_actorBaseAddr[0]);

		danteActorData.position = mainActorData.position;
		vergilActorData.position = mainActorData.position;


		auto pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);

		pool[3] = danteActorData;

		danteActorData.newButtonMask = 0xFFFF;
		//vergilActorData.newButtonMask = 0xFFFF;
		vergilActorData.newButtonMask = 0;




		Log("count %u", Actor_actorBaseAddr.count);
		for (uint32 index = 0; index < Actor_actorBaseAddr.count; index++)
		{
			Log("%llX", Actor_actorBaseAddr[index]);
		}
	}



	//DanteYamato();



	//DanteSummonedSwords();
	//DanteYamatoDaemonStart();
	//DanteYamatoDaemonUpdate();
	//DanteYamatoDaemonEnd();







	//auto baseAddr = Actor_actorBaseAddr[2];
	//if (!baseAddr)
	//{
	//	return;
	//}
	//auto & actorData = *reinterpret_cast<ACTOR_DATA_DANTE *>(baseAddr);
	//g_relativeTilt = (actorData.actorCameraDirection - actorData.leftStickPosition);

	//g_relativeTiltDirection = GetRelativeTiltDirection(actorData);





	return;





//
//

	//VergilMillionStab();


	//for (uint32 index = 0; index < System_Actor_actorBaseAddr.count; index++)
	//{
	//	auto baseAddr = System_Actor_actorBaseAddr[index];


	//	if (!baseAddr)
	//	{
	//		continue;
	//	}

	//	VergilMillionStab(baseAddr);




	//	auto & actorData = *(ACTOR_DATA *)baseAddr;
	//	

	//	if (!actorData.parentBaseAddr)
	//	{
	//		continue;
	//	}

	//	auto & parentActorData = *(ACTOR_DATA *)actorData.parentBaseAddr;



	//	actorData.position = parentActorData.position;
	//	actorData.direction = parentActorData.direction;


	//	


	//}








	//return;














	










	//InGameStart:
	//{
	//	//if (!InGame())
	//	//{
	//	//	goto InGameEnd;
	//	//}
	//	if (Config.Game.StyleSwitcher.enable)
	//	{
	//		Game_StyleSwitcher_Controller();
	//	}
	//	if (Config.Game.ResetMotionState.enable)
	//	{
	//		Game_ResetMotionState_Controller();
	//	}
	//	System_HUD_Update();

	//	CameraStart:
	//	{
	//		if (!Config.Camera.applyConfig)
	//		{
	//			goto CameraEnd;
	//		}
	//		uint32 remainder = (elapsedMilliseconds % Config.Camera.rate);
	//		if (!remainder)
	//		{
	//			Camera_Update(Config);
	//		}
	//	}
	//	CameraEnd:;
	//}
	//InGameEnd:;
}




void ActorLoop(byte8 * baseAddr)
{
	g_actorLoopCounter++;



	DanteYamato(baseAddr);





















}


























/*
dmc3.exe+1E2495 - movzx r8d,byte ptr [rbx+00000118]
dmc3.exe+1E8866 - movzx r8d,byte ptr [rcx+00000118]
dmc3.exe+1E9869 - movzx eax,byte ptr [rdi+00000118]
dmc3.exe+1EACB6 - movzx r8d,byte ptr [rcx+00000118]
dmc3.exe+1F8401 - movzx edx,byte ptr [rdi+00000118]
dmc3.exe+1F840D - movzx r8d,byte ptr [rdi+00000118]
dmc3.exe+1F90BD - movzx edx,byte ptr [rdi+00000118]
dmc3.exe+21295A - movzx eax,byte ptr [rdi+00000118]
dmc3.exe+2129B2 - movzx eax,byte ptr [rdi+00000118]
dmc3.exe+215457 - movzx eax,byte ptr [rdi+00000118]
dmc3.exe+21547C - movzx eax,byte ptr [rdi+00000118]
dmc3.exe+2154EE - movzx eax,byte ptr [rdi+00000118]
dmc3.exe+215B7A - movzx eax,byte ptr [rdi+00000118]
dmc3.exe+22821B - movzx eax,byte ptr [rdi+00000118]
dmc3.exe+22847C - movzx eax,byte ptr [rdi+00000118]
dmc3.exe+22889D - movzx edx,byte ptr [rdi+00000118]
dmc3.exe+229E82 - movzx edx,byte ptr [rbx+00000118]
dmc3.exe+229F38 - movzx r8d,byte ptr [rbx+00000118]
dmc3.exe+22AA2F - movzx r8d,byte ptr [rbx+00000118]
dmc3.exe+22AAF8 - movzx eax,byte ptr [rbx+00000118]
dmc3.exe+22AD26 - movzx edx,byte ptr [rbx+00000118]
dmc3.exe+22BFA1 - movzx eax,byte ptr [rdi+00000118]
dmc3.exe+22BFDC - movzx r8d,byte ptr [rdi+00000118]
dmc3.exe+22F6E3 - movzx r8d,byte ptr [rbx+00000118]
dmc3.exe+22F93B - movzx eax,byte ptr [rbx+00000118]
dmc3.exe+22FA95 - movzx edx,byte ptr [rbx+00000118]
dmc3.exe+230439 - movzx eax,byte ptr [rbx+00000118]
dmc3.exe+23046F - movzx r8d,byte ptr [rbx+00000118]
dmc3.exe+230C00 - movzx eax,byte ptr [rbx+00000118]
dmc3.exe+230C51 - movzx r8d,byte ptr [rbx+00000118]
dmc3.exe+231624 - movzx edx,byte ptr [rbx+00000118]
dmc3.exe+2316DA - movzx r8d,byte ptr [rbx+00000118]
*/



/*
dmc3.exe+1BE7A9 - 48 8B 0D 7826AD00 - mov rcx,[dmc3.exe+C90E28]
dmc3.exe+1BE7B3 - E8 C810FFFF       - call dmc3.exe+1AF880
*/







//void DanteLoop(byte8 * baseAddr)
//{
//	g_newCounter++;
//}





void UpdateAirPosition(byte8 * baseAddr)
{


	{
		auto & parentActorData = *reinterpret_cast<ACTOR_DATA *>(baseAddr);
		if (parentActorData.newParentBaseAddr)
		{
			goto ParentEnd;
		}
		const_for_all(index, 4)
		{
			auto childBaseAddr = parentActorData.newChildBaseAddr[index];
			if (!childBaseAddr)
			{
				continue;
			}
			auto & childActorData = *reinterpret_cast<ACTOR_DATA *>(childBaseAddr);

			if (!IsWeaponActive(childActorData))
			{
				childActorData.position = parentActorData.position;
				childActorData.direction = parentActorData.direction;
			}



		}
		return;
	}
	ParentEnd:;
	{
		auto & childActorData = *reinterpret_cast<ACTOR_DATA *>(baseAddr);
		auto parentBaseAddr = childActorData.newParentBaseAddr;
		if (!parentBaseAddr)
		{
			goto ChildEnd;
		}
		auto & parentActorData = *reinterpret_cast<ACTOR_DATA *>(parentBaseAddr);

		if (!IsWeaponActive(parentActorData))
		{
			parentActorData.position = childActorData.position;
			parentActorData.direction = childActorData.direction;

		}


		return;
	}
	ChildEnd:;





}


// Wow, same crap.

void Update_Init()
{
	LogFunction();
	Windows_GetTicksPerSecond(&ticksPerSecond);
	ticksPerMillisecond = (ticksPerSecond / 1000);
	Windows_GetTickCount(&savedTickCount);


	{
		constexpr byte8 sect1[] =
		{
			0x48, 0x8B, 0xCF, //mov rcx,rdi
		};
		constexpr byte8 sect2[] =
		{
			0x48, 0x83, 0xC4, 0x30, //add rsp,30
			0x5F,                   //pop rdi
		};
		auto func = CreateFunction(UpdateAirPosition, (appBaseAddr + 0x1FB3E8), true, true, 0, sizeof(sect1), sizeof(sect2));
		memcpy(func.sect1, sect1, sizeof(sect1));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteJump((appBaseAddr + 0x1FB3E3), func.addr);
		/*
		dmc3.exe+1FB3E3 - 48 83 C4 30 - add rsp,30
		dmc3.exe+1FB3E7 - 5F          - pop rdi
		dmc3.exe+1FB3E8 - C3          - ret
		*/
	}




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









	//{
	//	auto func = CreateFunction(DanteLoop, (appBaseAddr + 0x1DFA30));
	//	Write<byte8 *>((appBaseAddr + 0x4DF998), func.addr);





	//	/*
	//	dmc3.exe+4DF998
	//	*/




	//	/*
	//	dmc3.exe+1DFA30 - 40 53                 - push rbx
	//	*/
	//}














	//{
	//	byte8 sect0[] =
	//	{
	//		0x48, 0x8D, 0x4C, 0x24, 0x20, //lea rcx,[rsp+20]
	//	};
	//	auto func = CreateFunction(MainLoop, (appBaseAddr + 0x2C5EB5), true, true, sizeof(sect0));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	WriteJump((appBaseAddr + 0x2C5EB0), func.addr);
	//	/*
	//	dmc3.exe+2C5EB0 - 48 8D 4C 24 20 - lea rcx,[rsp+20]
	//	dmc3.exe+2C5EB5 - FF 15 1D930800 - call qword ptr [dmc3.exe+34F1D8]
	//	*/
	//}
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
