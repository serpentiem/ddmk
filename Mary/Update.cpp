#include "Update.h"

uint64 ticksPerSecond      = 0;
uint64 ticksPerMillisecond = 0;
uint64 savedTickCount      = 0;

bool millionStab = false;

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








void DanteYamatoDaemonStart()
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
		if (actorData.newMeleeWeaponMap[actorData.newMeleeWeaponIndex] != WEAPON_VERGIL_YAMATO)
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





		if (childActorData.meleeWeaponMap[0] == WEAPON_VERGIL_YAMATO)
		{
			continue;
		}







		if (actorData.newButtonMask & GAMEPAD_Y)
		{
			actorData.newButtonMask -= GAMEPAD_Y;
		}

		if (actorData.motionState2[1] & MOTION_STATE_BUSY)
		{
			float32 timeout = 0;

			const_for_all(weaponIndex, 4)
			{
				if (IsWeaponActive<ACTOR_DATA_DANTE>(actorData, actorData.meleeWeaponMap[weaponIndex]))
				{
					// @Todo: Get timeout.
					break;
				}
			}

			auto & length = actorData.modelData[actorData.activeModelIndex].motionLength1[BODY_PART_UPPER];
			auto & timer  = actorData.modelData[actorData.activeModelIndex].motionTimer  [BODY_PART_UPPER];

			if (timer < timeout)
			{
				continue;
			}

			if (childActorData.buttons[2] & GAMEPAD_Y)
			{
				goto sect0;
			}

			if (timer < length)
			{
				continue;
			}
		}
		sect0:;




		childActorData.meleeWeaponMap[0] = WEAPON_VERGIL_YAMATO;
		childActorData.activeMeleeWeaponIndex = 0;
		childActorData.queuedMeleeWeaponIndex = 0;







		

		// if dante and wants yamato
		// insta take away control
		// if no longer busy transfer control to the child
		// update buttons if necessary



		//if (!parentActorData.newChildBaseAddr[CHAR_VERGIL])
		//{
		//	continue;
		//}
		//// @Research: Maybe not required.
		//if (baseAddr != parentActorData.newChildBaseAddr[CHAR_VERGIL])
		//{
		//	continue;
		//}


		// No need to check the timer if we're not busy.







		// At this point we already switched the melee weapon, which means we WANT yamato.

		// There are two parts to this: Control and visibility.

		// Once the timer is above the timeout threshold, transfer control to the child.

		// Now check for GAMEPAD_Y and the timer.

		// If the timer runs out or GAMEPAD_Y is pressed, show the weapon model.

		// And set a flag I guess?

		// Basically, at this point Yamato is initiated properly.






	}









}












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









		auto vergilBaseAddr = CreateActorVergil();
		if (!vergilBaseAddr)
		{
			return;
		}
		auto & vergilActorData = *vergilBaseAddr;
		Actor_actorBaseAddr.Push(vergilActorData);

		danteActorData.newChildBaseAddr[CHAR_VERGIL] = vergilActorData;

		vergilActorData.newParentBaseAddr = danteActorData;


		auto & mainActorData = *reinterpret_cast<ACTOR_DATA *>(Actor_actorBaseAddr[0]);

		danteActorData.position = mainActorData.position;
		vergilActorData.position = mainActorData.position;


		auto pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);

		pool[3] = danteActorData;




		Log("count %u", Actor_actorBaseAddr.count);
		for (uint32 index = 0; index < Actor_actorBaseAddr.count; index++)
		{
			Log("%llX", Actor_actorBaseAddr[index]);
		}
	}





	DanteYamatoDaemonStart();









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
