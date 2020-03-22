#include "Update.h"

uint64 ticksPerSecond      = 0;
uint64 ticksPerMillisecond = 0;
uint64 savedTickCount      = 0;

bool millionStab = false;

// As soon as millionStab is true, start daemon and check for state.

// Consider all actors for millionStab.

void VergilMillionStab()
{
	auto g_pool = *(byte8 ***)(appBaseAddr + 0xC90E28);

	auto mainBaseAddr = System_Actor_mainActorBaseAddr;
	auto & mainActorData = *(ACTOR_DATA *)mainBaseAddr;

	auto baseAddr = System_Actor_actorBaseAddr[ACTOR_TWO];
	auto & actorData = *(ACTOR_DATA *)baseAddr;

	if (mainActorData.move != 39)
	{
		return;
	}
	if (mainActorData.motionData[1].group != 5)
	{
		return;
	}
	if (mainActorData.motionData[1].index != 11)
	{
		return;
	}
	//if (mainActorData.inputData[16].level < 6)
	if (mainActorData.inputData[16].flags[4] < 6)
	{
		return;
	}


	

	//auto position = mainActorData.position;
	//auto direction = mainActorData.direction;

	//mainActorData.position  = actorData.position;
	//mainActorData.direction = actorData.direction;
	mainActorData.actorId   = ACTOR_TWO;

	//actorData.position  = position;
	//actorData.direction = direction;
	actorData.actorId   = ACTOR_ONE;

	actorData.motionState1[0] = 0x11;
	actorData.motionState1[1] = 0x11;
	actorData.motionState1[2] = 0x11;
	actorData.motionState1[3] = 0x11;

	actorData.motionState2[0] = 0x401;
	actorData.motionState2[1] = 0xB0001;
	actorData.motionState2[2] = 0xB0001;

	actorData.move = 14;

	g_pool[3] = baseAddr;
}



void MainLoop()
{
	//uint64 tickCount           = 0;
	//uint32 elapsedMilliseconds = 0;

	//Windows_GetTickCount(&tickCount);
	//elapsedMilliseconds = (uint32)((tickCount - savedTickCount) / ticksPerMillisecond);

	//if (elapsedMilliseconds >= 1000)
	//{
	//	savedTickCount = tickCount;
	//}


	if (spawnActors)
	{
		spawnActors = false;

		Log("Spawn Actors.");

		System_Actor_actorBaseAddr[ACTOR_TWO] = CreateActor(CHAR_LOGIC_DANTE, ACTOR_TWO);

		//Log("System_Actor_actorBaseAddr %llX", System_Actor_actorBaseAddr[ACTOR_TWO]);



		//auto g_pool = *(byte8 ***)(appBaseAddr + 0xC90E28);

		//g_pool[3] = System_Actor_actorBaseAddr[ACTOR_ONE];


		
		auto & actorData     = *(ACTOR_DATA *)System_Actor_actorBaseAddr[ACTOR_TWO];
		auto & mainActorData = *(ACTOR_DATA *)System_Actor_mainActorBaseAddr;


		
		//actorData.x = mainActorData.x;
		//actorData.y = mainActorData.y;
		//actorData.z = mainActorData.z;


		actorData.position  = mainActorData.position;
		actorData.direction = mainActorData.direction;




		actorData.character = CHAR_VERGIL;
		actorData.equipment[0] = WEAPON_DANTE_REBELLION;
		actorData.equipment[1] = WEAPON_VOID;
		actorData.equipment[2] = WEAPON_VOID;
		actorData.equipment[3] = WEAPON_VOID;





		
		{
			//auto g_pool = *(byte8 ***)(appBaseAddr + 0xC90E10);

			//auto eventData = g_pool[8];
			//auto & position = *(uint32 *)(eventData + 0x1C);

			//func_23E560(eventData, position);







		}



		/*
dmc3.exe+C90E10
		*/


	}


	VergilMillionStab();


	return;














	










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
