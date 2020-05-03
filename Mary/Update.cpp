#include "Update.h"

uint64 ticksPerSecond      = 0;
uint64 ticksPerMillisecond = 0;
uint64 savedTickCount      = 0;

uint64 g_mainLoopCounter = 0;
uint64 g_actorLoopCounter = 0;

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

template <typename T>
bool IsBusy(T & actorData)
{
	if (actorData.state & STATE_BUSY)
	{
		return true;
	}
	return false;
}

#pragma region Reset State 1 to 8

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

#pragma endregion

template <typename T>
void ResetMotionState(T & actorData)
{
	const_for_all(index, 2)
	{
		actorData.motionData[index].group = 0;
		actorData.motionData[index].index = 0;
	}
	const_for_all(index, 16)
	{
		actorData.nextActionRequestPolicy[index] = NEXT_ACTION_REQUEST_POLICY_IGNORE;
	}

	//if (actorData.state & STATE_ON_FLOOR)
	{
		actorData.var_3E00[0] = 1;
		actorData.var_3E00[1] = 0;
		actorData.var_3E00[2] = 1;
		actorData.var_3E00[3] = 0;
	}
	//else
	//{
	//	actorData.var_3E00[0] = 6;
	//	actorData.var_3E00[1] = 5;
	//	actorData.var_3E00[2] = 6;
	//	actorData.var_3E00[3] = 0;
	//}




	memset(actorData.var_3E10, 0, 32);
}

template <typename T>
void ResetPermissions(T & actorData)
{
	if (actorData.state & STATE_ON_FLOOR)
	{
		actorData.permissions = 0x1C1B;
	}
	else
	{
		actorData.permissions = 0xC08;
	}
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
		//childActorData.state = parentActorData.state;

		OnceEnable(childActorData, 0);

		if (parentActorData.nextActionRequestPolicy[4] == NEXT_ACTION_REQUEST_POLICY_EXECUTE)
		{
			childActorData.permissions += PERMISSION_INTERACTION_STYLE_ATTACK;

			if (childActorData.buttons[2] & GAMEPAD_Y)
			{
				ResetMotionState(parentActorData);
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


	// @Research: Permissions and state mods are wonky. Try toggling buttons instead.

	//if (!IsBusy(parentActorData))
	{
		if (IsWeaponActive(childActorData))
		{
			parentActorData.position = childActorData.position;
			parentActorData.direction = childActorData.direction;
			parentActorData.permissions = 0;

			//OnceEnable(parentActorData, 0);

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
					ResetMotionState(childActorData);
					childActorData.permissions = 0;

					ClearYamato(childActorData);

					//OnceDisable(parentActorData, 0);

					//goto ChildEnd;
				}
			}

			//if (childActorData.nextActionRequestPolicy[5] == NEXT_ACTION_REQUEST_POLICY_EXECUTE)
			//{
			//	parentActorData.permissions += PERMISSION_JUMP_ROLL;

			//	if (parentActorData.buttons[2] & GAMEPAD_A)
			//	{
			//		ResetState4(childActorData);
			//		childActorData.permissions = 0;
			//		ClearYamato(childActorData);

			//		OnceDisable(parentActorData, 0);

			//		goto ChildEnd;
			//	}
			//}

			//if (childActorData.nextActionRequestPolicy[15] == NEXT_ACTION_REQUEST_POLICY_EXECUTE)
			//{
			//	parentActorData.permissions += PERMISSION_WALK_RUN;

			//	if (parentActorData.leftStickRadius >= LEFT_STICK_DEADZONE)
			//	{
			//		ResetState4(childActorData);
			//		childActorData.permissions = 0;
			//		ClearYamato(childActorData);

			//		OnceDisable(parentActorData, 0);

			//		goto ChildEnd;
			//	}
			//}
		}
		else
		{



			if (parentActorData.newSect[3])
			{
				parentActorData.state ^= STATE_BUSY;
			}









			OnceStart(parentActorData, 0);
			{
				//ResetMotionState(parentActorData);
				ResetPermissions(parentActorData);
				//parentActorData.state ^= STATE_BUSY;
			}
			OnceEnd;

			childActorData.position = parentActorData.position;
			childActorData.direction = parentActorData.direction;
			childActorData.state = parentActorData.state;
		}







	//ChildEnd:;

	}


















	#undef OnceReset
	#undef OnceEnd
	#undef OnceStart
}

void ActorLoop(byte8 * baseAddr)
{
	g_actorLoopCounter++;
	DanteYamato(baseAddr);
}

void MainLoop()
{
	g_mainLoopCounter++;

	if (spawnActors)
	{
		spawnActors = false;
		Log("Spawn Actors.");

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

		danteActorData.position = mainActorData.position;
		vergilActorData.position = mainActorData.position;

		auto pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);

		pool[3] = danteActorData;

		danteActorData.newButtonMask = 0xFFFF;
		vergilActorData.newButtonMask = 0;

		Log("count %u", Actor_actorBaseAddr.count);
		for (uint32 index = 0; index < Actor_actorBaseAddr.count; index++)
		{
			Log("%llX", Actor_actorBaseAddr[index]);
		}
	}
}

void Update_Init()
{
	LogFunction();
	Windows_GetTicksPerSecond(&ticksPerSecond);
	ticksPerMillisecond = (ticksPerSecond / 1000);
	Windows_GetTickCount(&savedTickCount);


	// Skip Position Update
	{
		constexpr byte8 sect0[] =
		{
			0x80, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, //cmp byte ptr [rcx+0000B8C0],00
			0x74, 0x01,                               //je short
			0xC3,                                     //ret
			0x48, 0x89, 0x5C, 0x24, 0x08,             //mov [rsp+08],rbx
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x1FB305), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*reinterpret_cast<uint32 *>(func.sect0 + 2) = offsetof(ACTOR_DATA, newSkipPositionUpdate);
		WriteJump((appBaseAddr + 0x1FB300), func.addr);
		/*
		dmc3.exe+1FB300 - 48 89 5C 24 08 - mov [rsp+08],rbx
		dmc3.exe+1FB305 - 57             - push rdi
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
