#include "Update.h"

uint64 ticksPerSecond      = 0;
uint64 ticksPerMillisecond = 0;
uint64 savedTickCount      = 0;

uint64 g_mainLoopCounter = 0;
uint64 g_actorLoopCounter = 0;

template <typename T>
bool IsBusy(T & actorData)
{
	if (actorData.state & STATE_BUSY)
	{
		return true;
	}
	return false;
}




template <typename T>
void ResetMotionData(T & actorData)
{
	memset(actorData.motionData, 0, 4);
}




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
void CopyPosition(T1 & dest, T2 & addr)
{
	dest.position = addr.position;
	dest.direction = addr.direction;
}





template <typename T>
void ResetMotionState(T & actorData)
{
	auto & modelData = actorData.modelData[actorData.activeModelIndex];
	modelData.motion.duration1[BODY_PART_LOWER] = 0;
	modelData.motion.duration1[BODY_PART_UPPER] = 0;
	modelData.motion.duration2[BODY_PART_LOWER] = 0;
	modelData.motion.duration2[BODY_PART_UPPER] = 0;
	modelData.motion.timer[BODY_PART_LOWER] = 0;
	modelData.motion.timer[BODY_PART_UPPER] = 0;

	memset(actorData.motionData, 0, 104);
	memset(actorData.var_3E00, 0, 48);


	// air only
	//actorData.var_3E00[0] = 1; // Update
	//actorData.var_3E00[2] = 1; // Play

	// 1 update
	// 2 end

	actorData.var_3E00[0] = 2; // End
	//actorData.var_3E00[2] = 1; // Play




	
	
	//actorData.move = 0;
	//actorData.lastMove = 0;
	//actorData.bufferedMove = 0;
	//func_1F01F0(actorData, 1);
	//return;
	//actorData.var_3E00[1] = 2;
	//actorData.var_3E00[2] = 2;
	//actorData.var_3E00[3] = 2;
}

template <typename T>
void TriggerAttack(T & actorData, uint8 index)
{
	actorData.move = index;
	actorData.lastMove = 0;
	func_1E0800(actorData, 17, 0, 0xFFFFFFFF);
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
bool WantsYamato(T & actorData)
{
	if (actorData.newMeleeWeaponMap[actorData.newMeleeWeaponIndex] == WEAPON_VERGIL_YAMATO)
	{
		return true;
	}
	return false;
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



//enum TILT_DIRECTION
//{
//	TILT_DIRECTION_VOID,
//	TILT_DIRECTION_UP,
//	TILT_DIRECTION_RIGHT,
//	TILT_DIRECTION_DOWN,
//	TILT_DIRECTION_LEFT,
//};
//
//
//
//
//
//template <typename T>
//uint8 GetRelativeTiltDirection(T & actorData)
//{
//	return 0;
//}
//







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



	if (parentActorData.newIsLeader)
	{
		childActorData.position = parentActorData.position;
		childActorData.direction = parentActorData.direction;
	}

	if (childActorData.newIsLeader)
	{
		parentActorData.position = childActorData.position;
		parentActorData.direction = childActorData.direction;
	}






	//if (IsWeaponActive(childActorData))




	// Disable always immediately.
	// Enable only when conditions are met.

	// Parent

	if (IsYamatoSelected(parentActorData))
	{
		parentActorData.newButtonMask = 0;
		parentActorData.newEnableLeftStick = false;
	}

	if (!IsYamatoSelected(parentActorData))
	{
		if (!IsWeaponActive(childActorData))
		{
			parentActorData.newButtonMask = 0xFFFF;
			parentActorData.newEnableLeftStick = true;
		}
	}

	if (!IsYamatoSelected(parentActorData))
	{
		if (IsWeaponActive(childActorData))
		{
			if (childActorData.nextActionRequestPolicy[4] == NEXT_ACTION_REQUEST_POLICY_EXECUTE)
			{
				if
				(
					(gamepad.buttons[2] & GAMEPAD_RIGHT_SHOULDER) &&
					(GetRelativeTiltDirection(parentActorData) == TILT_DIRECTION_UP) &&
					(gamepad.buttons[2] & GAMEPAD_Y)
				)
				{
					EndMotion(childActorData);

					EnableControl(parentActorData);

					//Camera_followBaseAddr = parentActorData;


					childActorData.newIsLeader = false;
					parentActorData.newIsLeader = true;



					if (parentActorData.state & STATE_ON_FLOOR)
					{
						TriggerAttack(parentActorData, 8); // Stinger
					}
				}
				else if
				(
					(gamepad.buttons[2] & GAMEPAD_RIGHT_SHOULDER) &&
					(GetRelativeTiltDirection(parentActorData) == TILT_DIRECTION_DOWN) &&
					(gamepad.buttons[2] & GAMEPAD_Y)
				)
				{
					EndMotion(childActorData);

					EnableControl(parentActorData);

					//Camera_followBaseAddr = parentActorData;

					childActorData.newIsLeader = false;
					parentActorData.newIsLeader = true;

					if (parentActorData.state & STATE_ON_FLOOR)
					{
						TriggerAttack(parentActorData, 10); // High Time
					}
				}
				else if (gamepad.buttons[2] & GAMEPAD_Y)
				{
					EndMotion(childActorData);

					EnableControl(parentActorData);

					//Camera_followBaseAddr = parentActorData;

					childActorData.newIsLeader = false;
					parentActorData.newIsLeader = true;

					if (parentActorData.state & STATE_ON_FLOOR)
					{
						TriggerAttack(parentActorData, 1); // Combo 1 Part 1
					}
					else
					{
						TriggerAttack(parentActorData, 6); // Helm Breaker
					}
				}
			}
		}
	}

	// Child

	if (!IsYamatoSelected(parentActorData))
	{
		childActorData.newButtonMask = 0;
		childActorData.newEnableLeftStick = false;
	}

	if (IsYamatoSelected(parentActorData))
	{
		if (!IsWeaponActive(parentActorData))
		{
			childActorData.newButtonMask = 0xFFFF;
			childActorData.newEnableLeftStick = true;
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
					(gamepad.buttons[2] & GAMEPAD_RIGHT_SHOULDER) &&
					(GetRelativeTiltDirection(childActorData) == TILT_DIRECTION_UP) &&
					(gamepad.buttons[2] & GAMEPAD_Y)
				)
				{
					EndMotion(parentActorData);

					EnableControl(childActorData);

					//Camera_followBaseAddr = childActorData;

					parentActorData.newIsLeader = false;
					childActorData.newIsLeader = true;
					


					if (childActorData.state & STATE_ON_FLOOR)
					{
						TriggerAttack(childActorData, 5); // Rapid Slash
					}
				}
				else if
				(
					(gamepad.buttons[2] & GAMEPAD_RIGHT_SHOULDER) &&
					(GetRelativeTiltDirection(childActorData) == TILT_DIRECTION_DOWN) &&
					(gamepad.buttons[2] & GAMEPAD_Y)
				)
				{
					EndMotion(parentActorData);

					EnableControl(childActorData);

					//Camera_followBaseAddr = childActorData;

					parentActorData.newIsLeader = false;
					childActorData.newIsLeader = true;

					if (childActorData.state & STATE_ON_FLOOR)
					{
						TriggerAttack(childActorData, 7); // High Time
					}
				}
				else if (gamepad.buttons[2] & GAMEPAD_Y)
				{
					EndMotion(parentActorData);

					EnableControl(childActorData);

					//Camera_followBaseAddr = childActorData;

					parentActorData.newIsLeader = false;
					childActorData.newIsLeader = true;

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

		//vergilActorData.newDisableLeftStick = true;

		danteActorData.position = mainActorData.position;
		vergilActorData.position = mainActorData.position;

		auto pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);

		pool[3] = danteActorData;

		danteActorData.newButtonMask = 0xFFFF;
		danteActorData.newEnableLeftStick = true;
		danteActorData.newEnableMotion = true;
		danteActorData.newEnablePermissionUpdate = true;

		vergilActorData.newButtonMask = GAMEPAD_Y | GAMEPAD_RIGHT_SHOULDER;
		vergilActorData.newEnableLeftStick = true;
		vergilActorData.newEnableMotion = true;
		vergilActorData.newEnablePermissionUpdate = true;
		//vergilActorData.newButtonMask = 0;
		//vergilActorData.newEnableLeftStick = false;
		

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
