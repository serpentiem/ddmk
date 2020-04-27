#include "Update.h"

uint64 ticksPerSecond      = 0;
uint64 ticksPerMillisecond = 0;
uint64 savedTickCount      = 0;

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

template <typename T>
void SetBusyFlag(T & actorData)
{
	auto & motionState = actorData.motionState3[1];
	if (!(motionState & MOTION_STATE_BUSY))
	{
		motionState += MOTION_STATE_BUSY;
	}
}

template <typename T>
void ClearBusyFlag(T & actorData)
{
	auto & motionState = actorData.motionState3[1];
	if (motionState & MOTION_STATE_BUSY)
	{
		motionState -= MOTION_STATE_BUSY;
	}
}

template <typename T>
bool IsBusy(T & actorData)
{
	auto & motionState = actorData.motionState3[1];
	if (motionState & MOTION_STATE_BUSY)
	{
		return true;
	}
	return false;
}

template <typename T>
void ResetState(T & actorData)
{
	const_for_all(index, 16)
	{
		actorData.motionState1[index] = 0;
	}

	actorData.motionState2[0] = 1;
	actorData.motionState2[1] = 0;
	actorData.motionState2[2] = 4;
	actorData.motionState2[3] = 0;
	actorData.motionState2[4] = 0;
	actorData.motionState2[5] = 0;

	actorData.motionState3[0] = 0x1C1B;
	actorData.motionState3[1] = 1;
	actorData.motionState3[2] = 0;
}

template <typename T>
void SetAttackState(T & actorData)
{
	const_for_all(index, 16)
	{
		actorData.motionState1[index] = 0;
	}

	actorData.motionState2[0] = 0x11;
	actorData.motionState2[1] = 1;
	actorData.motionState2[2] = 0x11;
	actorData.motionState2[3] = 0x11;
	actorData.motionState2[4] = 1;
	actorData.motionState2[5] = 0;

	actorData.motionState3[0] = 0x401;
	actorData.motionState3[1] = 0x10001;
	actorData.motionState3[2] = 0;
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



























void DanteYamatoDaemonStart()
{
	for_each(index, 2, Actor_actorBaseAddr.count)
	{
		auto baseAddr = Actor_actorBaseAddr[index];
		if (!baseAddr)
		{
			continue;
		}

		{
			auto & actorData = *reinterpret_cast<ACTOR_DATA_DANTE *>(baseAddr);
			if (actorData.character != CHAR_DANTE)
			{
				goto ParentEnd;
			}
			if (actorData.newParentBaseAddr)
			{
				goto ParentEnd;
			}
			if (!actorData.newChildBaseAddr[CHAR_VERGIL])
			{
				goto ParentEnd;
			}
			auto & childActorData = *reinterpret_cast<ACTOR_DATA_VERGIL *>(actorData.newChildBaseAddr[CHAR_VERGIL]);
			if (childActorData.character != CHAR_VERGIL)
			{
				goto ParentEnd;
			}

			// If parent wants Yamato, check if child has Yamato equipped.
			// if not, set vars.



			//auto & newMeleeWeapon = actorData.newMeleeWeaponMap[actorData.newMeleeWeaponIndex];


			if (WantsYamato(actorData))
			{
				DisableButton(actorData, GAMEPAD_Y);

				if (actorData.style == STYLE_DANTE_SWORDMASTER)
				{
					DisableButton(actorData, GAMEPAD_B);
				}

				EnableButton(childActorData, GAMEPAD_Y);

				if (!IsBusy(actorData))
				{
					SetYamato(childActorData);
				}
			}







			continue;
		}
		ParentEnd:;
	}
}








void DanteYamatoDaemonEnd()
{
	for_each(index, 2, Actor_actorBaseAddr.count)
	{
		auto baseAddr = Actor_actorBaseAddr[index];
		if (!baseAddr)
		{
			continue;
		}

		{
			auto & actorData = *reinterpret_cast<ACTOR_DATA_DANTE *>(baseAddr);
			if (actorData.character != CHAR_DANTE)
			{
				goto ParentEnd;
			}
			if (actorData.newParentBaseAddr)
			{
				goto ParentEnd;
			}
			if (!actorData.newChildBaseAddr[CHAR_VERGIL])
			{
				goto ParentEnd;
			}
			auto & childActorData = *reinterpret_cast<ACTOR_DATA_VERGIL *>(actorData.newChildBaseAddr[CHAR_VERGIL]);
			if (childActorData.character != CHAR_VERGIL)
			{
				goto ParentEnd;
			}

			// If parent no longer wants Yamato, check if child has Yamato equipped.
			// if not, set vars.



			//auto & newMeleeWeapon = actorData.newMeleeWeaponMap[actorData.newMeleeWeaponIndex];


			if (!WantsYamato(actorData))
			{
				EnableButton(actorData, GAMEPAD_Y);

				if (actorData.style == STYLE_DANTE_SWORDMASTER)
				{
					EnableButton(actorData, GAMEPAD_B);
				}

				DisableButton(childActorData, GAMEPAD_Y);



				





				if (!IsBusy(childActorData))
				{

					// Can't clear it beforehand, because some function that accesses the weaponData has no range check.

					//ClearYamato(childActorData);
					ClearYamato(childActorData);
				}
			}







			continue;
		}
		ParentEnd:;
	}
}




















void DanteYamatoDaemonUpdate()
{
	for_each(index, 2, Actor_actorBaseAddr.count)
	{
		auto baseAddr = Actor_actorBaseAddr[index];
		if (!baseAddr)
		{
			continue;
		}







		{
			auto & actorData = *reinterpret_cast<ACTOR_DATA_DANTE *>(baseAddr);
			if (actorData.character != CHAR_DANTE)
			{
				goto ParentEnd;
			}
			if (actorData.newParentBaseAddr)
			{
				goto ParentEnd;
			}
			if (!actorData.newChildBaseAddr[CHAR_VERGIL])
			{
				goto ParentEnd;
			}
			auto & childActorData = *reinterpret_cast<ACTOR_DATA_VERGIL *>(actorData.newChildBaseAddr[CHAR_VERGIL]);
			if (childActorData.character != CHAR_VERGIL)
			{
				goto ParentEnd;
			}



			




			auto & motionData = actorData.motionData[BODY_PART_UPPER];
			//auto & modelData = actorData.modelData[actorData.activeModelIndex];
			//auto & duration = modelData.motionDuration1[BODY_PART_UPPER];
			//auto & timer = modelData.motionTimer[BODY_PART_UPPER];



			//auto & childMotionData = childActorData.motionData[BODY_PART_UPPER];

			// We need this so Vergil can't immediately use Yamato once it's equipped.
			// the weapon map is updated
			// because normally he could use this as soon as the weapon map is updated, this could conflict with an ongoing attack
			// If the parent uses a weapon, check at what point the attack is.
			// If we're not at the point where we can execute a new action, set the busy flag.
			// Otherwise, clear the busy flag.

			// Takes care of lock-on issues.






			
			// We need the busy flag so Vergil can't use Yamato instantly.
			// Because we update the melee weapon map immediately to be able to use yamato as soon as possible.

			// we also need to set the busy flag otherwise Vergil could use Yamato during our attack.

			//auto IsBusy = [&]()
			//{
			//	if (actorData.motionState3[1] & MOTION_STATE_BUSY)
			//	{
			//		return true;
			//	}
			//	return false;
			//};









			if (IsBusy(actorData))
			{
				if ((motionData.group >= MOTION_GROUP_DANTE_REBELLION) && (motionData.group <= MOTION_GROUP_DANTE_GUNSLINGER_KALINA_ANN))
				{
					if (actorData.motionState1[4] != MOTION_STATE_EXECUTE)
					{
						SetBusyFlag(childActorData);
					}
					else
					{
						ClearBusyFlag(childActorData);

						// At this point the weapon is still active, but we can perform a new action.

						if (childActorData.buttons[2] & GAMEPAD_Y) // @Todo: Check charge switch.
						{
							ResetState(actorData);
							SetAttackState(childActorData);
							SetYamato(childActorData);
						}
					}
				}
			}












			// @Research: Perfect for lab conditions, but what happens when we get hit during an attack?
			// Check busy flag.
			// Shouldn't matter, because parent and child always share the same position and as such will both receive the hit.


			//else
			//{
			//	if (childMotionData.group != MOTION_GROUP_VERGIL_YAMATO)
			//	{
			//		ClearBusyFlag(childActorData);
			//	}
			//}

			continue;
		}
		ParentEnd:;

		// Base condition: Parent wants Yamato and child doesn't have Yamato.





		{
			auto & actorData = *reinterpret_cast<ACTOR_DATA_VERGIL*>(baseAddr);
			if (actorData.character != CHAR_VERGIL)
			{
				goto ChildEnd;
			}
			if (!actorData.newParentBaseAddr)
			{
				goto ChildEnd;
			}
			auto & parentActorData = *reinterpret_cast<ACTOR_DATA_DANTE *>(actorData.newParentBaseAddr);
			if (parentActorData.character != CHAR_DANTE)
			{
				goto ChildEnd;
			}




			//auto & modelData = actorData.modelData[actorData.activeModelIndex];
			//auto & duration = modelData.motionDuration1[BODY_PART_UPPER];
			//auto & timer = modelData.motionTimer[BODY_PART_UPPER];



			// Set and clear busy flag.

			auto & motionData = actorData.motionData[BODY_PART_UPPER];
			//auto & parentMotionData = parentActorData.motionData[BODY_PART_UPPER];

			if (motionData.group == MOTION_GROUP_VERGIL_YAMATO)
			{
				if (actorData.motionState1[4] != MOTION_STATE_EXECUTE)
				{
					SetBusyFlag(parentActorData);
				}
				else
				{
					ClearBusyFlag(parentActorData);

					if (parentActorData.buttons[2] & GAMEPAD_Y)
					{
						ResetState(actorData);
						SetAttackState(parentActorData);
						ClearYamato(actorData);
					}

















				}
			}
			//else
			//{
			//	if (!((parentMotionData.group >= MOTION_GROUP_DANTE_REBELLION) && (parentMotionData.group <= MOTION_GROUP_DANTE_GUNSLINGER_KALINA_ANN)))
			//	{
			//		ClearBusyFlag(parentActorData);
			//	}
			//}

			continue;
		}
		ChildEnd:;






	}
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
	if (actorData.leftStickRadius < 52)
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



void MainLoop()
{














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



	//DanteSummonedSwords();



	DanteYamatoDaemonStart();
	DanteYamatoDaemonUpdate();
	DanteYamatoDaemonEnd();







	auto baseAddr = Actor_actorBaseAddr[2];
	if (!baseAddr)
	{
		return;
	}
	auto & actorData = *reinterpret_cast<ACTOR_DATA_DANTE *>(baseAddr);
	g_relativeTilt = (actorData.actorCameraDirection - actorData.leftStickPosition);

	g_relativeTiltDirection = GetRelativeTiltDirection(actorData);





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












// Wow, same crap.

void Update_Init()
{
	LogFunction();
	Windows_GetTicksPerSecond(&ticksPerSecond);
	ticksPerMillisecond = (ticksPerSecond / 1000);
	Windows_GetTickCount(&savedTickCount);
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
