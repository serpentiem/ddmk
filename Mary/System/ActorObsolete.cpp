

//bool System_Actor_enableArrayExtension    = false;
//bool System_Actor_enableCreateActor       = false;
//bool System_Actor_enableUpdateActor       = false;
//bool System_Actor_enableDoppelgangerFixes = false;
//bool System_Actor_enableModelFixes        = false;









//vector<byte8 *, 128> Actor_actorBaseAddr;










//byte8 * System_Actor_mainActorBaseAddr = 0;
//byte8 * System_Actor_mainCloneBaseAddr = 0;
//
////byte8 ** System_Actor_actorBaseAddr = 0;
////byte8 ** System_Actor_cloneBaseAddr = 0;
//
//
//byte8 * System_Actor_actorBaseAddr[MAX_ACTOR] = {};
//byte8 * System_Actor_cloneBaseAddr[MAX_ACTOR] = {};



//byte8 *(addr[4]) = 0;










// redirect_1BA560
// Redirect_1BA560
// 
// 




//byte8 * redirect_1BA560 = 0;
//byte8 * redirect_1BC0A0 = 0;
//
//void System_Actor_ToggleArrayExtension(bool enable)
//{
//	LogFunction(enable);
//
//	// Redirect arrays.
//
//	if (enable)
//	{
//		WriteJump((appBaseAddr + 0x1BA569), redirect_1BA560);
//		WriteJump((appBaseAddr + 0x1BC0C5), redirect_1BC0A0);
//	}
//	else
//	{
//		{
//			byte8 buffer[] =
//			{
//				0x4C, 0x8B, 0x44, 0xC1, 0x18, //mov r8,[rcx+rax*8+18]
//			};
//			vp_memcpy((appBaseAddr + 0x1BA569), buffer, sizeof(buffer));
//		}
//		{
//			byte8 buffer[] =
//			{
//				0x4A, 0x8B, 0x6C, 0xC0, 0x18, //mov rbp,[rax+r8*8+18]
//			};
//			vp_memcpy((appBaseAddr + 0x1BC0C5), buffer, sizeof(buffer));
//		}
//	}
//	Write<byte16>((appBaseAddr + 0x1BA5C7), (enable) ? 0x9002 : 0x1842);
//}




//vector<byte8 *> actorBaseAddr;










//vector<byte8 *, 128> Actor_actorBaseAddr;













//constexpr uint32 v_off = offsetof(vector<byte8 * __COMMA__ 128>, data);


//
//
//
//
//
//vector<byte8 *, 128> System_Actor_actorBaseAddr;
//
//


/*
dmc3.exe+5B460 - 4D 85 C0              - test r8,r8

*/


//constexpr uint32 s = sizeof(void);








//uint8 hook_5B460
//(
//	void *,
//	byte8 * destination,
//	byte8 * source,
//	uint32,
//	uint32
//)
//{
//	{
//		if (!destination)
//		{
//			goto sect0;
//		}
//		auto addr = *(byte8 **)(destination + 0xD0);
//		if (!addr)
//		{
//			goto sect0;
//		}
//		addr -= 0x7250;
//
//		for (uint32 index = 0; index < System_Actor_actorBaseAddr.count; index++)
//		{
//			auto baseAddr = System_Actor_actorBaseAddr[index];
//			auto & actorData = *(ACTOR_DATA *)baseAddr;
//			if (!baseAddr)
//			{
//				continue;
//			}
//			if (addr == baseAddr)
//			{
//				if (actorData.noCollision)
//				{
//					return 0;
//				}
//			}
//		}
//	}
//	sect0:;
//
//
//
//	//{
//	//	if (!source)
//	//	{
//	//		goto sect1;
//	//	}
//	//	auto addr = *(byte8 **)(source + 0xD0);
//	//	if (!addr)
//	//	{
//	//		goto sect1;
//	//	}
//	//	addr -= 0x7250;
//
//	//	for (uint32 index = 0; index < System_Actor_actorBaseAddr.count; index++)
//	//	{
//	//		auto baseAddr = System_Actor_actorBaseAddr[index];
//	//		auto & actorData = *(ACTOR_DATA *)baseAddr;
//	//		if (!baseAddr)
//	//		{
//	//			continue;
//	//		}
//	//		if (addr == baseAddr)
//	//		{
//	//			if (actorData.noCollision)
//	//			{
//	//				return 0;
//	//			}
//	//		}
//	//	}
//	//}
//	//sect1:;
//
//	
//	return 1;
//
//
//
//
//
//
//
//
//
//
//
//
//
//	//for (uint32 index = 0; index < System_Actor_actorBaseAddr.count; index++)
//	//{
//	//	auto baseAddr = System_Actor_actorBaseAddr[index];
//	//	auto & actorData = *(ACTOR_DATA *)baseAddr;
//	//	if (!baseAddr)
//	//	{
//	//		continue;
//	//	}
//	//	if (destination == actorData.collisionData)
//	//	{
//	//		if (actorData.noCollision)
//	//		{
//	//			return 0;
//	//		}
//	//	}
//	//}
//
//	//for (uint32 index = 0; index < System_Actor_actorBaseAddr.count; index++)
//	//{
//	//	auto baseAddr = System_Actor_actorBaseAddr[index];
//	//	auto & actorData = *(ACTOR_DATA *)baseAddr;
//	//	if (!baseAddr)
//	//	{
//	//		continue;
//	//	}
//	//	if (source == actorData.collisionData)
//	//	{
//	//		if (actorData.noCollision)
//	//		{
//	//			return 0;
//	//		}
//	//	}
//	//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//	//return 10;
//}







	// if destination is one of us, check collision flag

	// if source is one of us, check collision flag





/*
dmc3.exe+2CC090 - 4C 8B 89 D0000000     - mov r9,[rcx+000000D0] { rbx addr
 }

*/


//bool hook_2CC090(byte8 * collisionData)
//{
//	byte8 * baseAddr = 0;
//
//
//
//
//
//
//	baseAddr = *(byte8 **)(collisionData + 0xD0);
//	baseAddr -= 0x7250;
//
//	for (uint32 index = 0; index < System_Actor_actorBaseAddr.count; index++)
//	{
//		auto actorBaseAddr = System_Actor_actorBaseAddr[index];
//		auto & actorData = *(ACTOR_DATA *)actorBaseAddr;
//		if (!actorBaseAddr)
//		{
//			continue;
//		}
//		if (baseAddr == actorBaseAddr)
//		{
//			if (actorData.noCollision)
//			{
//				return false;
//			}
//		}
//	}
//	return true;
//}
//
//
//bool hook_5C320(byte8 * collisionData)
//{
//
//
//
//	byte8 * baseAddr = 0;
//
//	//baseAddr = *(byte8 **)(collisionData + 0xD0);
//	//baseAddr -= 0x7250;
//
//	baseAddr = (collisionData - 0x7250);
//
//
//	for (uint32 index = 0; index < System_Actor_actorBaseAddr.count; index++)
//	{
//		auto actorBaseAddr = System_Actor_actorBaseAddr[index];
//		auto & actorData = *(ACTOR_DATA *)actorBaseAddr;
//		if (!actorBaseAddr)
//		{
//			continue;
//		}
//		if (baseAddr == actorBaseAddr)
//		{
//			if (actorData.noCollision)
//			{
//				return false;
//			}
//		}
//	}
//	return true;
//
//
//
//
//
//
//
//
//
//
//
//
//
//	return true;
//}



/*
dmc3.exe+5C320 - 48 89 5C 24 08        - mov [rsp+08],rbx { __NOT_IT_EITHER__
 }

*/







//extern uint32 devilCounter;
//extern bool System_Actor_enableArrayExtension;
//extern bool System_Actor_enableCreateActor;
//extern bool System_Actor_enableUpdateActor;
//extern bool System_Actor_enableDoppelgangerFixes;
//extern bool System_Actor_enableModelFixes;
//extern byte8 * System_Actor_actorBaseAddr[MAX_ACTOR];
// @Todo: Move to Internal.
//typedef void(__fastcall * UpdateModel_t)(byte8 * baseAddr);
//extern byte8 * System_Actor_mainActorBaseAddr;
//extern byte8 * System_Actor_mainCloneBaseAddr;
//
////extern byte8 ** System_Actor_actorBaseAddr;
////extern byte8 ** System_Actor_cloneBaseAddr;
//
//
//extern byte8 * System_Actor_actorBaseAddr[MAX_ACTOR];
//extern byte8 * System_Actor_cloneBaseAddr[MAX_ACTOR];



// @Todo: Add operator[].

//template <typename T, uint32 n>
//struct vector
//{
//	uint32 count;
//	T data[n];
//	void Push(T var)
//	{
//		data[count] = var;
//		count++;
//	}
//	void Clear()
//	{
//		memset(this, 0, sizeof(*this));
//	}
//	void operator+=(T var)
//	{
//		Push(var);
//	}
//	vector()
//	{
//		Clear();
//	}
//};


//extern vector<byte8 *, 128> Actor_actorBaseAddr;




//void System_Actor_ToggleArrayExtension(bool enable);
//void System_Actor_ToggleCreateActorOne(bool enable);
//void System_Actor_ToggleUpdateActor(bool enable);
//void System_Actor_ToggleDoppelgangerFixes(bool enable);
//void System_Actor_ToggleModelFixes(bool enable);
//void System_Actor_ToggleDisableIdleTimer(bool enable);



//typedef void(* System_Actor_UpdateDevilForm_t)(byte8 *       );
//typedef void(* System_Actor_UpdateFlux_t     )(byte8 *, uint8);
//typedef void(* System_Actor_Relax_t          )(byte8 *       );
//
//extern System_Actor_UpdateDevilForm_t System_Actor_UpdateDevilForm;
//extern System_Actor_UpdateFlux_t      System_Actor_UpdateFlux;
//extern System_Actor_Relax_t           System_Actor_Relax;







//void System_Actor_AdjustConfig(CONFIG & config);





//uint8 System_Actor_GetActorId(byte8 * baseAddr);
//uint8 System_Actor_GetActorCount();
//void System_Actor_ResetDevilModel();
//void System_Actor_UpdateDevilModel(uint8 model);


//MotionHelper * motionHelper[] =
//{
//	motionHelperDante,
//	motionHelperBob,
//	motionHelperLady,
//	motionHelperVergil,
//};
//
//uint8 motionHelperCount[] =
//{
//	countof(motionHelperDante),
//	countof(motionHelperBob),
//	countof(motionHelperLady),
//	countof(motionHelperVergil),
//};

// @Todo: Obsolete.

__declspec(deprecated("Use ACTOR_DATA instead.")) uint8 System_Actor_GetActorId(byte8 * baseAddr)
{
	//for (uint8 actor = 0; actor < MAX_ACTOR; actor++)
	//{
	//	if (System_Actor_actorBaseAddr[actor] == baseAddr)
	//	{
	//		return actor;
	//	}
	//}
	return 0;
}

__declspec(deprecated("Use ACTOR_DATA instead.")) uint8 System_Actor_GetActorCount()
{
	uint8 count = 0;
	//for (uint8 actor = 0; actor < MAX_ACTOR; actor++)
	//{
	//	if (!System_Actor_actorBaseAddr[actor])
	//	{
	//		break;
	//	}
	//	count++;
	//}
	return count;
}




//void CreateActors()
//{
//	LogFunction();
//
//
//
//
//
//
//	if (Config.Game.Multiplayer.enable)
//	{
//		for (uint8 index = 0; index < Config.Game.Multiplayer.actorCount; index++)
//		{
//			uint8 actor = (ACTOR_TWO + index);
//			auto & character = Config.Game.Multiplayer.character[index];
//			InternalCreateActor(character, actor, false);
//		}
//	}
//	else
//	{
//		uint8 & characterActorOne = *(uint8 *)(System_Actor_actorBaseAddr[ACTOR_ONE] + 0x78);
//		uint8 character = (Config.Game.Doppelganger.enable) ? Config.Game.Doppelganger.character : characterActorOne;
//		InternalCreateActor(character, ACTOR_TWO, false);
//	}
//}
//
//void CreateActorOne(byte8 * baseAddr)
//{
//	LogFunction(baseAddr);
//	memset(System_Actor_actorBaseAddr, 0, sizeof(System_Actor_actorBaseAddr));
//	System_Actor_actorBaseAddr[ACTOR_ONE] = baseAddr;
//
//
//	//CreateClone();
//
//
//
//	if (Config.System.Actor.forceSingleActor)
//	{
//		return;
//	}
//	CreateActors();
//
//
//	
//
//	
//
//
//
//
//
//
//}
//
//
//
//void UpdateBaseAddress(byte8 * baseAddr)
//{
//	uint8 actor = System_Actor_GetActorId(baseAddr);
//	byte8 ** data = *(byte8 ***)(appBaseAddr + 0xC90E28);
//	if (!data)
//	{
//		return;
//	}
//	switch (actor)
//	{
//	case ACTOR_ONE:
//		data[3] = baseAddr;
//		break;
//	case ACTOR_TWO:
//		data[4] = baseAddr;
//		break;
//	}
//}

//void UpdateActor(byte8 * baseAddr)
//{
//	Log("%s %llX", FUNC_NAME, baseAddr);
//
//	uint8 character = *(uint8 *)(baseAddr + 0x78);
//	if (character >= MAX_CHAR)
//	{
//		character = 0;
//	}
//
//	//// Update File Items
//	//{
//	//	UpdateCostume(baseAddr);
//	//	auto & count = fileItemHelperCount[character];
//	//	for (uint8 index = 0; index < count; index++)
//	//	{
//	//		fileItemHelper[character][index].Update();
//	//	}
//	//}
//
//	//UpdateBaseAddress(baseAddr);
//
//
//	System_File_UpdateFileItems((ACTOR_DATA *)baseAddr);
//
//
//
//
//
//
//
//
//
//
//
//	LogFunctionEnd();
//}
//
//void UpdateMotion(byte8 * baseAddr)
//{
//	LogFunction(baseAddr);
//	uint8 character = *(uint8 *)(baseAddr + 0x78);
//	if (character >= MAX_CHAR)
//	{
//		character = 0;
//	}
//	byte ** motion = (byte **)(baseAddr + 0x38A0);
//	memset(motion, 0, (MAX_MOT * 8));
//	auto & count = motionHelperCount[character];
//	for (uint8 index = 0; index < count; index++)
//	{
//		auto & motionId    = motionHelper[character][index].motionId;
//		auto & cacheFileId = motionHelper[character][index].cacheFileId;
//
//		//motion[motionId] = System_Cache_file[cacheFileId];
//
//		motion[motionId] = System_File_cacheFile[cacheFileId];
//
//
//	}
//}

PrivateEnd;

// @Todo: Review.

//void System_Actor_ResetDevilModel()
//{
//
//	return;
//
//
//	LogFunction();
//	// Loop Count
//	{
//		byte buffer[] =
//		{
//			0x0F, 0x45, 0xC1, //cmovne eax,ecx
//		};
//		vp_memcpy((appBaseAddr + 0x2130E5), buffer, sizeof(buffer));
//	}
//	// Sparda
//	{
//		byte buffer[] =
//		{
//			0x0F, 0x85, 0xCB, 0x03, 0x00, 0x00, //jne dmc3.exe+21353F
//		};
//		vp_memcpy((appBaseAddr + 0x21316E), buffer, sizeof(buffer));
//	}
//	// Other Models
//	{
//		byte buffer[] =
//		{
//			0x41, 0x0F, 0xBE, 0x0C, 0x0C, //movsx ecx,byte ptr [r12+rcx]
//		};
//		vp_memcpy((appBaseAddr + 0x21353F), buffer, sizeof(buffer));
//	}
//	// Aura
//	WriteAddress((appBaseAddr + 0x1F9393), (appBaseAddr + 0x1F93AB), 2);
//	WriteAddress((appBaseAddr + 0x1F9433), (appBaseAddr + 0x1F9440), 2);
//	Write<uint8>((appBaseAddr + 0x1F943B), DEVIL_DANTE_SPARDA);
//}
//
//void System_Actor_UpdateDevilModel(uint8 model)
//{
//
//	return;
//
//	LogFunction();
//	System_Actor_ResetDevilModel();
//	vp_memset((appBaseAddr + 0x2130E5), 0x90, 3);
//	if (model == DEVIL_DANTE_SPARDA)
//	{
//		WriteAddress((appBaseAddr + 0x21316E), (appBaseAddr + 0x213174), 6);
//	}
//	else
//	{
//		Write<word>((appBaseAddr + 0x21316E), 0xE990);
//		{
//			byte buffer[] =
//			{
//				0x31, 0xC9, //xor ecx,ecx
//				0xB1, 0x00, //mov cl,model
//				0x90,       //nop
//			};
//			vp_memcpy((appBaseAddr + 0x21353F), buffer, sizeof(buffer));
//			Write<uint8>((appBaseAddr + 0x213542), model);
//		}
//	}
//	WriteAddress((appBaseAddr + 0x1F9393), (appBaseAddr + 0x1F9395), 2);
//	WriteAddress((appBaseAddr + 0x1F9433), (appBaseAddr + 0x1F9435), 2);
//	Write<uint8>((appBaseAddr + 0x1F943B), model);
//}

PrivateStart;


//void UpdateActorAttributes(byte8 * baseAddr)
//{
//	LogFunction(baseAddr);
//
//
//
//	//auto & ad = (*(ACTOR_DATA *)baseAddr);
//	//auto & ad = *(ACTOR_DATA *)baseAddr;
//
//
//	//auto & ad = *((ACTOR_DATA *)baseAddr);
//
//	//auto & ad = *(ACTOR_DATA *)baseAddr;
//
//	//ad.isDoppelganger = true;
//
//
//
//	
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//	auto & character      = *(uint8  *)(baseAddr + 0x78  );
//	auto & isDoppelganger = *(uint32 *)(baseAddr + 0x11C );
//	auto & visible        = *(uint32 *)(baseAddr + 0x120 );
//	auto & shadow         = *(uint32 *)(baseAddr + 0x3A18);
//
//
//
//	if (Config.Game.Multiplayer.enable)
//	{
//		return;
//	}
//	if (baseAddr != System_Actor_actorBaseAddr[ACTOR_TWO])
//	{
//		return;
//	}
//	isDoppelganger = 1;
//	if (Config.Cosmetics.Doppelganger.noColor)
//	{
//		return;
//	}
//	Cosmetics_Color_ApplyColor(baseAddr, 6, 0);
//}

#pragma region __OBSOLETE__

void old_System_Actor_Init()
{
	LogFunction();

	// Increase ACTOR_DATA size.
	{
		constexpr uint32 size = (0xB8C0 + 512);
		Write<uint32>((appBaseAddr + 0x1DE5FA), size);
		Write<uint32>((appBaseAddr + 0x1DE67A), size);
		Write<uint32>((appBaseAddr + 0x1DE8B4), size);
		Write<uint32>((appBaseAddr + 0x1DEBE2), size);
	}





	//{
	//	byte8 sect0[] =
	//	{
	//		0x48, 0x8B, 0xD9,                         //mov rbx,rcx
	//		0x80, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x01, //cmp byte ptr [rcx+0000B8C0],01
	//		0x0F, 0x84, 0x00, 0x00, 0x00, 0x00,       //je dmc3.exe+1DFD56
	//		0x83, 0xB9, 0x20, 0x01, 0x00, 0x00, 0x00, //cmp dword ptr [rcx+00000120],00
	//		0x0F, 0x84, 0x00, 0x00, 0x00, 0x00,       //je dmc3.exe+1DFD56
	//	};
	//	auto func = CreateFunction(0, (appBaseAddr + 0x1DFD22), false, true, sizeof(sect0));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	*(byte32 *)(func.sect0 + 5) = offsetof(ACTOR_DATA, hide);
	//	WriteAddress((func.sect0 + 0xA), (appBaseAddr + 0x1DFD56), 6);
	//	WriteAddress((func.sect0 + 0x17), (appBaseAddr + 0x1DFD56), 6);
	//	WriteJump((appBaseAddr + 0x1DFD16), func.addr, 2);
	//	/*
	//	dmc3.exe+1DFD16 - 83 B9 20010000 00 - cmp dword ptr [rcx+00000120],00
	//	dmc3.exe+1DFD1D - 48 8B D9          - mov rbx,rcx
	//	dmc3.exe+1DFD20 - 74 34             - je dmc3.exe+1DFD56
	//	dmc3.exe+1DFD22 - 48 63 81 6C3E0000 - movsxd  rax,dword ptr [rcx+00003E6C]
	//	*/
	//}













	//{
	//	byte8 sect0[] =
	//	{
	//		0x80, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x01, //cmp byte ptr [rax+0000B8C0],01
	//		0x0F, 0x84, 0x00, 0x00, 0x00, 0x00,       //je dmc3.exe+1FDE7F
	//		0x83, 0xB8, 0x20, 0x01, 0x00, 0x00, 0x00, //cmp dword ptr [rax+00000120],00
	//		0x0F, 0x84, 0x00, 0x00, 0x00, 0x00,       //je dmc3.exe+1FDE7F
	//	};
	//	auto func = CreateFunction(0, (appBaseAddr + 0x1FDE29), false, true, sizeof(sect0));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	*(byte32 *)(func.sect0 + 2) = offsetof(ACTOR_DATA, hideWeapons);
	//	WriteAddress((func.sect0 + 7), (appBaseAddr + 0x1FDE7F), 6);
	//	WriteAddress((func.sect0 + 0x14), (appBaseAddr + 0x1FDE7F), 6);
	//	WriteJump((appBaseAddr + 0x1FDE20), func.addr, 2);
	//	/*
	//	dmc3.exe+1FDE20 - 83 B8 20010000 00 - cmp dword ptr [rax+00000120],00
	//	dmc3.exe+1FDE27 - 74 56             - je dmc3.exe+1FDE7F
	//	dmc3.exe+1FDE29 - 48 89 5C 24 30    - mov [rsp+30],rbx
	//	*/
	//}




	//{
	//	byte8 sect0[] =
	//	{
	//		0x80, 0xBA, 0x00, 0x00, 0x00, 0x00, 0x01, //cmp byte ptr [rdx+0000B8C0],01
	//		0x0F, 0x84, 0x00, 0x00, 0x00, 0x00,       //je dmc3.exe+1DB099
	//		0x83, 0xBA, 0x20, 0x01, 0x00, 0x00, 0x00, //cmp dword ptr [rdx+00000120],00
	//		0x0F, 0x84, 0x00, 0x00, 0x00, 0x00,       //je dmc3.exe+1DB099
	//	};
	//	auto func = CreateFunction(0, (appBaseAddr + 0x1DAF36), false, true, sizeof(sect0));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	*(byte32 *)(func.sect0 + 2) = offsetof(ACTOR_DATA, hideSummonedSwords);
	//	WriteAddress((func.sect0 + 7), (appBaseAddr + 0x1DB099), 6);
	//	WriteAddress((func.sect0 + 0x14), (appBaseAddr + 0x1DB099), 6);
	//	WriteJump((appBaseAddr + 0x1DAF29), func.addr, 2);
	//	/*
	//	dmc3.exe+1DAF29 - 83 BA 20010000 00 - cmp dword ptr [rdx+00000120],00
	//	dmc3.exe+1DAF30 - 0F84 63010000     - je dmc3.exe+1DB099
	//	dmc3.exe+1DAF36 - C6 81 E80D0000 00 - mov byte ptr [rcx+00000DE8],00
	//	*/
	//}


	//{
	//	byte8 * baseAddr = 0;
	//	auto & actorDataBase = *(ACTOR_DATA *)baseAddr;




	//}






	{
		byte8 sect0[] =
		{
			0x66, 0x23, 0x83, 0x00, 0x00, 0x00, 0x00, //and ax,[rbx+0000B8C0]
			0x66, 0x89, 0x83, 0xE0, 0x74, 0x00, 0x00, //mov [rbx+000074E0],ax
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x1EBD3B), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*(byte32 *)(func.sect0 + 3) = offsetof(ACTOR_DATA, buttonMask);
		WriteJump((appBaseAddr + 0x1EBD34), func.addr, 2);
		/*
		dmc3.exe+1EBD34 - 66 89 83 E0740000 - mov [rbx+000074E0],ax
		dmc3.exe+1EBD3B - 48 8D 0D CE8CB600 - lea rcx,[dmc3.exe+D54A10]
		*/
	}


	{
		byte8 sect0[] =
		{
			0x66, 0x23, 0x83, 0x00, 0x00, 0x00, 0x00, //and ax,[rbx+0000B8C0]
			0x66, 0x89, 0x83, 0xE2, 0x74, 0x00, 0x00, //mov [rbx+000074E2],ax
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x1EBD5B), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*(byte32 *)(func.sect0 + 3) = offsetof(ACTOR_DATA, buttonMask);
		WriteJump((appBaseAddr + 0x1EBD54), func.addr, 2);
		/*
		dmc3.exe+1EBD54 - 66 89 83 E2740000 - mov [rbx+000074E2],ax
		dmc3.exe+1EBD5B - 66 23 CA          - and cx,dx
		*/
	}

	{
		byte8 sect0[] =
		{
			0x66, 0x23, 0x8B, 0x00, 0x00, 0x00, 0x00, //and cx,[rbx+0000B8C0]
			0x66, 0x89, 0x8B, 0xE4, 0x74, 0x00, 0x00, //mov [rbx+000074E4],cx
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x1EBD6B), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*(byte32 *)(func.sect0 + 3) = offsetof(ACTOR_DATA, buttonMask);
		WriteJump((appBaseAddr + 0x1EBD64), func.addr, 2);
		/*
		dmc3.exe+1EBD64 - 66 89 8B E4740000 - mov [rbx+000074E4],cx
		dmc3.exe+1EBD6B - 66 23 D0          - and dx,ax
		*/
	}


	{
		byte8 sect0[] =
		{
			0x66, 0x23, 0x93, 0x00, 0x00, 0x00, 0x00, //and dx,[rbx+0000B8C0]
			0x66, 0x89, 0x93, 0xE6, 0x74, 0x00, 0x00, //mov [rbx+000074E6],dx
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x1EBD7C), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*(byte32 *)(func.sect0 + 3) = offsetof(ACTOR_DATA, buttonMask);
		WriteJump((appBaseAddr + 0x1EBD75), func.addr, 2);
		/*
		dmc3.exe+1EBD75 - 66 89 93 E6740000 - mov [rbx+000074E6],dx
		dmc3.exe+1EBD7C - 33 D2             - xor edx,edx
		*/
	}




















	//{
	//	byte8 sect2[] =
	//	{
	//		0x84, 0xC0,                   //test al,al
	//		0x75, 0x01,                   //jne short
	//		0xC3,                         //ret
	//		0x48, 0x89, 0x5C, 0x24, 0x08, //mov [rsp+08],rbx
	//		0xE9, 0x00, 0x00, 0x00, 0x00, //jmp dmc3.exe+5C325
	//	};
	//	auto func = CreateFunction(hook_5C320, 0, true, false, 0, 0, sizeof(sect2));
	//	memcpy(func.sect2, sect2, sizeof(sect2));
	//	WriteAddress((func.sect2 + 0xA), (appBaseAddr + 0x5C325), 5);
	//	//WriteJump((appBaseAddr + 0x5C320), func.addr);
	//}





	//{
	//	byte8 sect0[] =
	//	{
	//		0x0F, 0x29, 0x81, 0x80, 0x02, 0x00, 0x00, //movaps [rcx+00000280],xmm0
	//	};
	//	byte8 sect2[] =
	//	{
	//		0x84, 0xC0,                         //test al,al
	//		0x0F, 0x85, 0x88, 0xC3, 0x06, 0x00, //jne dmc3.exe+5C390
	//		0xE9, 0xCA, 0xC3, 0x06, 0x00,       //jmp dmc3.exe+5C3D7
	//	};










	//}












//	{
//		byte8 sect2[] =
//		{
//			0x84, 0xC0,                               //test al,al
//			0x75, 0x01,                               //jne short
//			0xC3,                                     //ret
//			0x4C, 0x8B, 0x89, 0xD0, 0x00, 0x00, 0x00, //mov r9,[rcx+000000D0]
//			0xE9, 0x00, 0x00, 0x00, 0x00,             //jmp dmc3.exe+2CC097
//		};
//		auto func = CreateFunction(hook_2CC090, 0, true, false, 0, 0, sizeof(sect2));
//		memcpy(func.sect2, sect2, sizeof(sect2));
//		WriteAddress((func.sect2 + 0xC), (appBaseAddr + 0x2CC097), 5);
//		//WriteJump((appBaseAddr + 0x2CC090), func.addr, 2);
//
//
//
//
//
//		/*
//dmc3.exe+2CC090 - 4C 8B 89 D0000000     - mov r9,[rcx+000000D0] { rbx addr
// }
//
//		*/
//
//
//		//WriteAddress((func.sect2 + 2), (appBaseAddr + 0x2CC090), 6);
//		//WriteCall((appBaseAddr + 0x5B5BC), func.addr);
//		//WriteCall((appBaseAddr + 0x5B5CB), func.addr);
//		//WriteCall((appBaseAddr + 0x5B5EA), func.addr);
//		//WriteCall((appBaseAddr + 0x5B609), func.addr);
//		//WriteCall((appBaseAddr + 0x5BA21), func.addr);
//		//WriteCall((appBaseAddr + 0x5BA34), func.addr);
//	}





	





	/*
dmc3.exe+1EBD19
	*/








	//{
	//	byte8 sect2[] =
	//	{
	//		0x84, 0xC0,                         //test al,al
	//		0x0F, 0x85, 0x00, 0x00, 0x00, 0x00, //jne dmc3.exe+5B460
	//		0xC3,                               //ret
	//	};
	//	auto func = CreateFunction(hook_5B460, 0, true, false, 0, 0, sizeof(sect2), 0, 1);
	//	memcpy(func.sect2, sect2, sizeof(sect2));
	//	WriteAddress((func.sect2 + 2), (appBaseAddr + 0x5B460), 6);
	//	//WriteCall((appBaseAddr + 0x5B7F9), func.addr);
	//	//WriteCall((appBaseAddr + 0x5B81C), func.addr);
	//	//WriteCall((appBaseAddr + 0x5B83F), func.addr);
	//	//WriteCall((appBaseAddr + 0x5B862), func.addr);
	//	//WriteCall((appBaseAddr + 0x5B885), func.addr);
	//	//WriteCall((appBaseAddr + 0x5B8AB), func.addr);
	//}























	//{
	//	byte8 sect0[] =
	//	{
	//		0x51,                                                       //push rcx
	//		0x52,                                                       //push rdx
	//		0x56,                                                       //push rsi
	//		0x48, 0xBE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rsi,System_Actor_actorBaseAddr
	//		0x48, 0x85, 0xD2,                                           //test rdx,rdx
	//		0x74, 0x2A,                                                 //je short
	//		0x48, 0x8B, 0x8A, 0xD0, 0x00, 0x00, 0x00,                   //mov rcx,[rdx+000000D0]
	//		0x48, 0x85, 0xC9,                                           //test rcx,rcx
	//		0x74, 0x1E,                                                 //je short
	//		0x48, 0x81, 0xE9, 0x50, 0x72, 0x00, 0x00,                   //sub rcx,00007250
	//		0x31, 0xD2,                                                 //xor edx,edx
	//		0x48, 0x8B, 0x44, 0xD6, 0x00,                               //mov rax,[rsi+rdx*8+08]
	//		0x48, 0x85, 0xC0,                                           //test rax,rax
	//		0x74, 0x05,                                                 //je short
	//		0x48, 0x39, 0xC1,                                           //cmp rcx,rax
	//		0x74, 0x3D,                                                 //je short
	//		0xFF, 0xC2,                                                 //inc edx
	//		0x3B, 0x16,                                                 //cmp edx,[rsi]
	//		0x72, 0xEB,                                                 //jb short
	//		0x4D, 0x85, 0xC0,                                           //test r8,r8
	//		0x74, 0x2A,                                                 //je short
	//		0x49, 0x8B, 0x88, 0xD0, 0x00, 0x00, 0x00,                   //mov rcx,[r8+000000D0]
	//		0x48, 0x85, 0xC9,                                           //test rcx,rcx
	//		0x74, 0x1E,                                                 //je short
	//		0x48, 0x81, 0xE9, 0x50, 0x72, 0x00, 0x00,                   //sub rcx,00007250
	//		0x31, 0xD2,                                                 //xor edx,edx
	//		0x48, 0x8B, 0x44, 0xD6, 0x00,                               //mov rax,[rsi+rdx*8+08]
	//		0x48, 0x85, 0xC0,                                           //test rax,rax
	//		0x74, 0x05,                                                 //je short
	//		0x48, 0x39, 0xC1,                                           //cmp rcx,rax
	//		0x74, 0x0E,                                                 //je short
	//		0xFF, 0xC2,                                                 //inc edx
	//		0x3B, 0x16,                                                 //cmp edx,[rsi]
	//		0x72, 0xEB,                                                 //jb short
	//		0x5E,                                                       //pop rsi
	//		0x5A,                                                       //pop rdx
	//		0x59,                                                       //pop rcx
	//		0xE9, 0x00, 0x00, 0x00, 0x00,                               //jmp dmc3.exe+5B460
	//		0x5E,                                                       //pop rsi
	//		0x5A,                                                       //pop rdx
	//		0x59,                                                       //pop rcx
	//		0x80, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x01,                   //cmp byte ptr [rax+0000B8C0],01
	//		0x0F, 0x85, 0x00, 0x00, 0x00, 0x00,                         //jne dmc3.exe+5B460
	//		0xC3,                                                       //ret
	//	};
	//	auto func = CreateFunction(0, 0, false, true, sizeof(sect0));
	//	memcpy(func.sect0, sect0, sizeof(sect0));



	//	//*(void **)(func.sect0 + 5) = System_Actor_actorBaseAddr;


	//	//*(vector<byte8 *, 128> **)(func.sect0 + 5) = &System_Actor_actorBaseAddr;
	//	



	//	

	//	*(void **)(func.sect0 + 5) = &System_Actor_actorBaseAddr;






	//	*(byte8 *)(func.sect0 + 0x2B) = (byte8)offsetof(vector<byte8 * __COMMA__ 128>, data);
	//	*(byte8 *)(func.sect0 + 0x5A) = (byte8)offsetof(vector<byte8 * __COMMA__ 128>, data);
	//	WriteAddress((func.sect0 + 0x6E), (appBaseAddr + 0x5B460), 5);
	//	*(byte32 *)(func.sect0 + 0x78) = offsetof(ACTOR_DATA, noCollision);
	//	WriteAddress((func.sect0 + 0x7D), (appBaseAddr + 0x5B460), 6);
	//	WriteCall((appBaseAddr + 0x5B7F9), func.addr);
	//	WriteCall((appBaseAddr + 0x5B81C), func.addr);
	//	WriteCall((appBaseAddr + 0x5B83F), func.addr);
	//	WriteCall((appBaseAddr + 0x5B862), func.addr);
	//	WriteCall((appBaseAddr + 0x5B885), func.addr);
	//	WriteCall((appBaseAddr + 0x5B8AB), func.addr);
	//}





























	////// Fix func_1BA560.
	////{
	////	auto addr = (appBaseAddr + 0x1BA560);
	////	{
	////		byte8 buffer[55];
	////		memcpy(buffer, addr, sizeof(buffer));
	////		vp_memset(addr, 0x90, 64);
	////		vp_memcpy((addr + 7), buffer, sizeof(buffer));
	////	}
	////	byte8 buffer[] =
	////	{
	////		0x48, 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, //mov rcx,[dmc3.exe+C90E28]
	////	};
	////	vp_memcpy(addr, buffer, sizeof(buffer));
	////	WriteAddress(addr, (appBaseAddr + 0xC90E28), 7);
	////}






	//// Add isDefault check to func_1BA560 and func_1BC0A0 calls.
	////{
	////	byte8 sect0[] =
	////	{
	////		0x80, 0xBF, 0x00, 0x00, 0x00, 0x00, 0x01, //cmp byte ptr [rdi+0000B8C0],01
	////		0x0F, 0x85, 0x00, 0x00, 0x00, 0x00,       //jne dmc3.exe+1BA560
	////		0xC3,                                     //ret
	////	};
	////	auto func = CreateFunction(0, 0, false, true, sizeof(sect0));
	////	memcpy(func.sect0, sect0, sizeof(sect0));
	////	*(byte32 *)(func.sect0 + 2) = offsetof(ACTOR_DATA, isDefault);
	////	WriteAddress((func.sect0 + 7), (appBaseAddr + 0x1BA560), 6);
	////	WriteCall((appBaseAddr + 0x1F8408), func.addr);
	////	WriteCall((appBaseAddr + 0x1F90CB), func.addr);
	////}
	////{
	////	byte8 sect0[] =
	////	{
	////		0x80, 0xBB, 0x00, 0x00, 0x00, 0x00, 0x01, //cmp byte ptr [rbx+0000B8C0],01
	////		0x0F, 0x85, 0x00, 0x00, 0x00, 0x00,       //jne dmc3.exe+1BC0A0
	////		0xC3,                                     //ret
	////	};
	////	auto func = CreateFunction(0, 0, false, true, sizeof(sect0));
	////	memcpy(func.sect0, sect0, sizeof(sect0));
	////	*(byte32 *)(func.sect0 + 2) = offsetof(ACTOR_DATA, isDefault);
	////	WriteAddress((func.sect0 + 7), (appBaseAddr + 0x1BC0A0), 6);
	////	WriteCall((appBaseAddr + 0x1E24A6), func.addr);
	////	WriteCall((appBaseAddr + 0x1E889E), func.addr);
	////	WriteCall((appBaseAddr + 0x1E8965), func.addr);
	////}
	////{
	////	byte8 sect0[] =
	////	{
	////		0x80, 0xBF, 0x00, 0x00, 0x00, 0x00, 0x01, //cmp byte ptr [rdi+0000B8C0],01
	////		0x0F, 0x85, 0x00, 0x00, 0x00, 0x00,       //jne dmc3.exe+1BC0A0
	////		0xC3,                                     //ret
	////	};
	////	auto func = CreateFunction(0, 0, false, true, sizeof(sect0));
	////	memcpy(func.sect0, sect0, sizeof(sect0));
	////	*(byte32 *)(func.sect0 + 2) = offsetof(ACTOR_DATA, isDefault);
	////	WriteAddress((func.sect0 + 7), (appBaseAddr + 0x1BC0A0), 6);
	////	WriteCall((appBaseAddr + 0x1EACE2), func.addr);
	////	WriteCall((appBaseAddr + 0x1EAD30), func.addr);
	////	WriteCall((appBaseAddr + 0x1F841E), func.addr);
	////}
	////// Redirect arrays.
	////{
	////	byte8 sect0[] =
	////	{
	////		0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rcx,System_Actor_actorBaseAddr
	////		0x4C, 0x8B, 0x04, 0xC1,                                     //mov r8,[rcx+rax*8]
	////	};
	////	auto func = CreateFunction(0, (appBaseAddr + 0x1BA56E), false, true, sizeof(sect0));
	////	memcpy(func.sect0, sect0, sizeof(sect0));
	////	*(byte8 ***)(func.sect0 + 2) = System_Actor_actorBaseAddr;
	////	redirect_1BA560 = func.addr;
	////}
	////{
	////	byte8 sect0[] =
	////	{
	////		0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rax,System_Actor_actorBaseAddr
	////		0x4A, 0x8B, 0x2C, 0xC0,                                     //mov rbp,[rax+r8*8]
	////	};
	////	auto func = CreateFunction(0, (appBaseAddr + 0x1BC0CA), false, true, sizeof(sect0));
	////	memcpy(func.sect0, sect0, sizeof(sect0));
	////	*(byte8 ***)(func.sect0 + 2) = System_Actor_actorBaseAddr;
	////	redirect_1BC0A0 = func.addr;
	////}





	//




	//// Add noCollision check to actor collision function.
	//{
	//	byte8 sect0[] =
	//	{
	//		0x51,                                                       //push rcx
	//		0x52,                                                       //push rdx
	//		0x56,                                                       //push rsi
	//		0x48, 0x8B, 0x8A, 0xD0, 0x00, 0x00, 0x00,                   //mov rcx,[rdx+000000D0]
	//		0x48, 0x85, 0xC9,                                           //test rcx,rcx
	//		0x74, 0x65,                                                 //je short
	//		0x48, 0x81, 0xE9, 0x50, 0x72, 0x00, 0x00,                   //sub rcx,00007250
	//		0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rax,System_Actor_mainActorBaseAddr
	//		0x48, 0x8B, 0x00,                                           //mov rax,[rax]
	//		0x48, 0x39, 0xC1,                                           //cmp rcx,rax
	//		0x74, 0x54,                                                 //je short
	//		0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rax,System_Actor_mainCloneBaseAddr
	//		0x48, 0x8B, 0x00,                                           //mov rax,[rax]
	//		0x48, 0x39, 0xC1,                                           //cmp rcx,rax
	//		0x74, 0x42,                                                 //je short
	//		0x48, 0x31, 0xD2,                                           //xor rdx,rdx
	//		0x48, 0xBE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rsi,System_Actor_actorBaseAddr
	//		0x48, 0x8B, 0x04, 0xD6,                                     //mov rax,[rsi+rdx*8]
	//		0x48, 0x39, 0xC1,                                           //cmp rcx,rax
	//		0x74, 0x2C,                                                 //je short
	//		0xFE, 0xC2,                                                 //inc dl
	//		0x80, 0xFA, 0x00,                                           //cmp dl,MAX_ACTOR
	//		0x72, 0xF0,                                                 //jb short
	//		0x48, 0x31, 0xD2,                                           //xor rdx,rdx
	//		0x48, 0xBE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rsi,System_Actor_cloneBaseAddr
	//		0x48, 0x8B, 0x04, 0xD6,                                     //mov rax,[rsi+rdx*8]
	//		0x48, 0x39, 0xC1,                                           //cmp rcx,rax
	//		0x74, 0x0F,                                                 //je short
	//		0xFE, 0xC2,                                                 //inc dl
	//		0x80, 0xFA, 0x00,                                           //cmp dl,MAX_ACTOR
	//		0x72, 0xF0,                                                 //jb short
	//		0x5E,                                                       //pop rsi
	//		0x5A,                                                       //pop rdx
	//		0x59,                                                       //pop rcx
	//		0xE9, 0x00, 0x00, 0x00, 0x00,                               //jmp dmc3.exe+5B460
	//		0x5E,                                                       //pop rsi
	//		0x5A,                                                       //pop rdx
	//		0x59,                                                       //pop rcx
	//		0x80, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x01,                   //cmp byte ptr [rax+0000B8C2],01
	//		0x0F, 0x85, 0x00, 0x00, 0x00, 0x00,                         //jne dmc3.exe+5B460
	//		0xC3,                                                       //ret
	//	};
	//	auto func = CreateFunction(0, 0, false, true, sizeof(sect0));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	*(byte8 ***)(func.sect0 + 0x18) = &System_Actor_mainActorBaseAddr;
	//	*(byte8 ***)(func.sect0 + 0x2A) = &System_Actor_mainCloneBaseAddr;
	//	*(byte8 ***)(func.sect0 + 0x3F) = System_Actor_actorBaseAddr;
	//	*(uint8 *)(func.sect0 + 0x54) = MAX_ACTOR;
	//	*(byte8 ***)(func.sect0 + 0x5C) = System_Actor_cloneBaseAddr;
	//	*(uint8 *)(func.sect0 + 0x71) = MAX_ACTOR;
	//	WriteAddress((func.sect0 + 0x77), (appBaseAddr + 0x5B460), 5);
	//	*(byte32 *)(func.sect0 + 0x81) = offsetof(ACTOR_DATA, noCollision);
	//	WriteAddress((func.sect0 + 0x86), (appBaseAddr + 0x5B460), 6);
	//	WriteCall((appBaseAddr + 0x5B7F9), func.addr);
	//	WriteCall((appBaseAddr + 0x5B81C), func.addr);
	//	WriteCall((appBaseAddr + 0x5B83F), func.addr);
	//	WriteCall((appBaseAddr + 0x5B862), func.addr);
	//	WriteCall((appBaseAddr + 0x5B885), func.addr);
	//	WriteCall((appBaseAddr + 0x5B8AB), func.addr);
	//}



	//{
	//	byte8 * mugen[MAX_ACTOR][(MAX_CHAR - 1)] =
	//	{
	//		{0,1},
	//		{},
	//		{},
	//		{},
	//	};
	//}

	






	

	// Add noCollision check to attack collision function.




	//{
	//	byte8 sect0[] =
	//	{
	//		0x51,                                                       //push rcx
	//		0x52,                                                       //push rdx
	//		0x56,                                                       //push rsi
	//		0x49, 0x8B, 0xC9,                                           //mov rcx,r9
	//		0x48, 0x85, 0xC9,                                           //test rcx,rcx
	//		0x74, 0x65,                                                 //je short
	//		0x48, 0x81, 0xE9, 0xC0, 0x40, 0x00, 0x00,                   //sub rcx,000040C0
	//		0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rax,System_Actor_mainActorBaseAddr
	//		0x48, 0x8B, 0x00,                                           //mov rax,[rax]
	//		0x48, 0x39, 0xC1,                                           //cmp rcx,rax
	//		0x74, 0x54,                                                 //je short
	//		0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rax,System_Actor_mainCloneBaseAddr
	//		0x48, 0x8B, 0x00,                                           //mov rax,[rax]
	//		0x48, 0x39, 0xC1,                                           //cmp rcx,rax
	//		0x74, 0x42,                                                 //je short
	//		0x48, 0x31, 0xD2,                                           //xor rdx,rdx
	//		0x48, 0xBE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rsi,System_Actor_actorBaseAddr
	//		0x48, 0x8B, 0x04, 0xD6,                                     //mov rax,[rsi+rdx*8]
	//		0x48, 0x39, 0xC1,                                           //cmp rcx,rax
	//		0x74, 0x2C,                                                 //je short
	//		0xFE, 0xC2,                                                 //inc dl
	//		0x80, 0xFA, 0x00,                                           //cmp dl,MAX_ACTOR
	//		0x72, 0xF0,                                                 //jb short
	//		0x48, 0x31, 0xD2,                                           //xor rdx,rdx
	//		0x48, 0xBE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rsi,System_Actor_cloneBaseAddr
	//		0x48, 0x8B, 0x04, 0xD6,                                     //mov rax,[rsi+rdx*8]
	//		0x48, 0x39, 0xC1,                                           //cmp rcx,rax
	//		0x74, 0x0F,                                                 //je short
	//		0xFE, 0xC2,                                                 //inc dl
	//		0x80, 0xFA, 0x00,                                           //cmp dl,MAX_ACTOR
	//		0x72, 0xF0,                                                 //jb short
	//		0x5E,                                                       //pop rsi
	//		0x5A,                                                       //pop rdx
	//		0x59,                                                       //pop rcx
	//		0xE9, 0x00, 0x00, 0x00, 0x00,                               //jmp dmc3.exe+88190
	//		0x5E,                                                       //pop rsi
	//		0x5A,                                                       //pop rdx
	//		0x59,                                                       //pop rcx
	//		0x80, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x01,                   //cmp byte ptr [rax+0000B8C2],01
	//		0x0F, 0x85, 0x00, 0x00, 0x00, 0x00,                         //jne dmc3.exe+88190
	//		0xC3,                                                       //ret
	//	};
	//	auto func = CreateFunction(0, 0, false, true, sizeof(sect0));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	*(byte8 ***)(func.sect0 + 0x14) = &System_Actor_mainActorBaseAddr;
	//	*(byte8 ***)(func.sect0 + 0x26) = &System_Actor_mainCloneBaseAddr;
	//	*(byte8 ***)(func.sect0 + 0x3B) = System_Actor_actorBaseAddr;
	//	*(uint8 *)(func.sect0 + 0x50) = MAX_ACTOR;
	//	*(byte8 ***)(func.sect0 + 0x58) = System_Actor_cloneBaseAddr;
	//	*(uint8 *)(func.sect0 + 0x6D) = MAX_ACTOR;
	//	WriteAddress((func.sect0 + 0x73), (appBaseAddr + 0x88190), 5);
	//	*(byte32 *)(func.sect0 + 0x7D) = offsetof(ACTOR_DATA, noCollision);
	//	WriteAddress((func.sect0 + 0x82), (appBaseAddr + 0x88190), 6);
	//	Write<byte8 *>((appBaseAddr + 0x4C89F8), func.addr);
	//}








	/*
	System_Actor_actionActorBaseAddr
	System_Actor_phaseActorBaseAddr
	System_Actor_shiftActorBaseAddr
	System_Actor_phaseShiftActorBaseAddr
	System_Actor_actorBaseAddrCharacter
	System_Actor_swapActorBaseAddr
	System_Actor_switchActorBaseAddr
	System_Actor_tagActorBaseAddr
	*/


	/*
	System_Actor_extraActorBaseAddr
	System_Actor_auxActorBaseAddr
	*/

	// System_Actor_phaseShiftBaseAddr











	RegisterWeapon_Init();


	////System_Actor_actorBaseAddr = (byte8 **)HighAlloc((MAX_ACTOR * 8));
	////System_Actor_cloneBaseAddr = (byte8 **)HighAlloc((MAX_ACTOR * 8));

	//System_Actor_actorBaseAddr[ACTOR_ONE] = (byte8 *)0x12345678;
	//System_Actor_cloneBaseAddr[ACTOR_ONE] = (byte8 *)0xDEADBEEF;

	//Log("actorBaseAddr %llX", System_Actor_actorBaseAddr);
	//Log("cloneBaseAddr %llX", System_Actor_cloneBaseAddr);











	
	//auto func = CreateFunction(CreateActor);
	//Log("CreateActor %llX", func.addr);

	//Log("CreateActor %llX", CreateActor);




	//{
	//	constexpr uint32 size = 374;
	//	auto func = CreateFunction(0, 0, false, true, size);
	//	memcpy(func.sect0, (appBaseAddr + 0x1BC0A0), size);

	//	



	//	WriteAddress((func.sect0 + 0x14), (byte8 *)System_Actor_actorBaseAddr, 7);
	//	*(byte8 *)(func.sect0 + 0x15) = 0x8D;



	//	//System_Actor_actorBaseAddr[ACTOR_TWO] = 0;



	//	*(byte8 *)(func.sect0 + 0x29) = 0;










	//	WriteCall((func.sect0 + 0x2D), (appBaseAddr + 0x1EBB40));
	//	WriteCall((func.sect0 + 0x41), (appBaseAddr + 0x1F78B0));
	//	WriteCall((func.sect0 + 0x5C), (appBaseAddr + 0x1BBCD0));
	//	WriteCall((func.sect0 + 0x72), (appBaseAddr + 0x1F78B0));
	//	WriteCall((func.sect0 + 0x7E), (appBaseAddr + 0x1BA120));
	//	WriteAddress((func.sect0 + 0x9C), (appBaseAddr + 0x4C6094), 8);
	//	WriteCall((func.sect0 + 0xB0), (appBaseAddr + 0x1BA120));
	//	WriteCall((func.sect0 + 0xB7), (appBaseAddr + 0x1BB880));
	//	WriteAddress((func.sect0 + 0xC8), (appBaseAddr + 0xCF2D90), 7);
	//	WriteCall((func.sect0 + 0xCF), (appBaseAddr + 0x326960));
	//	WriteCall((func.sect0 + 0x150), (appBaseAddr + 0x1BBCD0));
	//	WriteCall((func.sect0 + 0x158), (appBaseAddr + 0x1BB7A0));









	//	Log("func_1BCA0 whatever %llX", func.addr);




	//}



















	
	/*
	dmc3.exe+4DFA10
	*/

	{
		//auto func = CreateFunction(UpdateActorDante);
		//Write<void *>((appBaseAddr + 0x4DFA10), func.addr);
	}
	
	//return;






	//for (uint8 index = 0; index < countof(modelHelperDante); index++)
	//{
	//	Log("modelHelperDante[%u] %llX", index, (byte8 *)modelHelperDante[index]->Update);
	//}

	//for (uint8 index = 0; index < countof(devilModelHelperDante); index++)
	//{
	//	Log("devilModelHelperDante[%u] %llX", index, &devilModelHelperDante[index]->Update);
	//}



	//for (uint8 index = 0; index < countof(UpdateModelDante); index++)
	//{
	//	Log("UpdateModelDante[%u] %llX", index, UpdateModelDante[index]);
	//}


	//{
	//	auto func = CreateFunction(UpdateModelDante[0]);
	//	Log("UpdateModelDanteDefaultHook %llX", func.addr);
	//}









	//#pragma region Later

	//{
	//	byte sect1[] =
	//	{
	//		0x48, 0x31, 0xC0,                                           //xor rax,rax
	//		0x84, 0xD2,                                                 //test dl,dl
	//		0x74, 0x77,                                                 //je short
	//		0x48, 0xBB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rbx,System_Actor_actorBaseAddr
	//		0x48, 0x0F, 0xB6, 0xF1,                                     //movzx rsi,cl
	//		0x48, 0x0F, 0xB6, 0xFA,                                     //movzx rdi,dl
	//		0x4D, 0x0F, 0xB6, 0xE0,                                     //movzx r12,r8l

	//		0x48, 0x8B, 0x4C, 0xFB, 0xF8,                               //mov rcx,[rbx+rdi*8-08]
	//		0x48, 0x85, 0xC9,                                           //test rcx,rcx
	//		0x74, 0x57,                                                 //je short

	//		0x48, 0x8D, 0x89, 0x10, 0x64, 0x00, 0x00,                   //lea rcx,[rcx+00006410]
	//		0xBA, 0x3C, 0x00, 0x00, 0x00,                               //mov edx,0000003C
	//		0xE8, 0x00, 0x00, 0x00, 0x00,                               //call dmc3.exe+2EE060 // __NOPE__

	//		0x8B, 0xCE,                                                 //mov ecx,esi
	//		0x8B, 0xD7,                                                 //mov edx,edi
	//		0x45, 0x8B, 0xC4,                                           //mov r8d,r12d
	//		0xE8, 0x00, 0x00, 0x00, 0x00,                               //call dmc3.exe+1DE820 // __TRUE__ create actor object
	//		0x4C, 0x8B, 0xE8,                                           //mov r13,rax
	//		0x48, 0x89, 0x04, 0xFB,                                     //mov [rbx+rdi*8],rax

	//		0x48, 0x8B, 0xCB,                                           //mov rcx,rbx
	//		0x8B, 0xD7,                                                 //mov edx,edi
	//		0xE8, 0x00, 0x00, 0x00, 0x00,                               //call dmc3.exe+1BB390 // __NOPE__

	//		0x49, 0x8B, 0xCD,                                           //mov rcx,r13
	//		0x48, 0x8B, 0x15, 0x00, 0x00, 0x00, 0x00,                   //mov rdx,[dmc3.exe+C90E28]
	//		0x48, 0x8B, 0x52, 0x08,                                     //mov rdx,[rdx+08]
	//		0x48, 0x81, 0xC2, 0x6C, 0x01, 0x00, 0x00,                   //add rdx,0000016C
	//		0xE8, 0x00, 0x00, 0x00, 0x00,                               //call dmc3.exe+1DF240 // __TRUE__ register actor files

	//		0x48, 0x8B, 0x4C, 0xFB, 0xF8,                               //mov rcx,[rbx+rdi*8-08]
	//		0x4C, 0x89, 0xA9, 0x78, 0x64, 0x00, 0x00,                   //mov [rcx+00006478],r13
	//		0x49, 0x8B, 0xC5,                                           //mov rax,r13
	//	};
	//	FUNC func = CreateFunction(0, 0, true, false, 0, sizeof(sect1));
	//	memcpy(func.sect1, sect1, sizeof(sect1));
	//	*(byte8 ***)(func.sect1 + 9) = System_Actor_actorBaseAddr;
	//	WriteCall((func.sect1 + 0x33), (appBaseAddr + 0x2EE060));
	//	WriteCall((func.sect1 + 0x3F), (appBaseAddr + 0x1DE820));
	//	WriteCall((func.sect1 + 0x50), (appBaseAddr + 0x1BB390));
	//	WriteAddress((func.sect1 + 0x58), (appBaseAddr + 0xC90E28), 7);
	//	WriteCall((func.sect1 + 0x6A), (appBaseAddr + 0x1DF240));

	//	// More like queue an additional actor.

	//	InternalCreateActor = (InternalCreateActor_t)func.addr;

	//	Log("internalCraeteActor %llX", InternalCreateActor);

	//}
	//{
	//	FUNC func = CreateFunction((appBaseAddr + 0x1FB020), 0);
	//	System_Actor_UpdateDevilForm = (System_Actor_UpdateDevilForm_t)func.addr;
	//}
	//{
	//	FUNC func = CreateFunction((appBaseAddr + 0x1F94D0), 0);
	//	System_Actor_UpdateFlux = (System_Actor_UpdateFlux_t)func.addr;
	//}
	//{
	//	byte sect1[] =
	//	{
	//		0x48, 0x8B, 0xD9,                         //mov rbx,rcx
	//		0x31, 0xD2,                               //xor edx,edx
	//		0xE8, 0x00, 0x00, 0x00, 0x00,             //call dmc3.exe+1F92C0
	//		0x48, 0x8B, 0x83, 0xE8, 0x3D, 0x00, 0x00, //mov rax,[rbx+00003DE8]
	//		0x8B, 0x80, 0xF0, 0x01, 0x00, 0x00,       //mov eax,[rax+000001F0]
	//		0x89, 0x83, 0xC4, 0x3E, 0x00, 0x00,       //mov [rbx+00003EC4],eax
	//		0x31, 0xD2,                               //xor edx,edx
	//		0x48, 0x8B, 0xCB,                         //mov rcx,rbx
	//		0xE8, 0x00, 0x00, 0x00, 0x00,             //call dmc3.exe+1F97F0
	//	};
	//	FUNC func = CreateFunction(0, 0, true, true, 0, sizeof(sect1));
	//	memcpy(func.sect1, sect1, sizeof(sect1));
	//	WriteCall((func.sect1 + 5), (appBaseAddr + 0x1F92C0));
	//	WriteCall((func.sect1 + 0x22), (appBaseAddr + 0x1F97F0));
	//	System_Actor_Relax = (System_Actor_Relax_t)func.addr;
	//}












	//{
	//	byte sect0[] =
	//	{
	//		0x49, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov r8,actorBaseAddr
	//		0x4D, 0x8B, 0x04, 0xC0,                                     //mov r8,[r8+rax*8]
	//		0x4D, 0x8B, 0xD0,                                           //mov r10,r8
	//	};
	//	FUNC func = CreateFunction(0, (appBaseAddr + 0x1BA572), false, true, sizeof(sect0));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	*(byte ***)(func.sect0 + 2) = System_Actor_actorBaseAddr;
	//	OnUpdate[0] = func.addr;
	//}
	//{
	//	byte sect0[] =
	//	{
	//		0x48, 0xBD, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rbp,actorBaseAddr
	//		0x4A, 0x8B, 0x6C, 0xC5, 0x00,                               //mov rbp,[rbp+r8*8+00]
	//	};
	//	FUNC func = CreateFunction(0, (appBaseAddr + 0x1BC0CA), false, true, sizeof(sect0));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	*(byte ***)(func.sect0 + 2) = System_Actor_actorBaseAddr;
	//	OnUpdate[1] = func.addr;
	//}
	//{
	//	byte8 sect1[] =
	//	{
	//		0x48, 0x8B, 0xC8, //mov rcx,rax
	//	};
	//	byte sect2[] =
	//	{
	//		0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc3.exe+1BB470
	//	};
	//	FUNC func = CreateFunction(CreateActorOne, (appBaseAddr + 0x23C79F), true, true, 0, sizeof(sect1), sizeof(sect2));
	//	memcpy(func.sect1, sect1, sizeof(sect1));
	//	memcpy(func.sect2, sect2, sizeof(sect2));
	//	WriteCall(func.sect2, (appBaseAddr + 0x1BB470));
	//	CreateActorOneProxy = func.addr;
	//}



	//{
	//	byte sect2[] =
	//	{
	//		0xFF, 0x90, 0x80, 0x00, 0x00, 0x00, //call qword ptr [rax+00000080]
	//	};
	//	FUNC func = CreateFunction(UpdateActor, (appBaseAddr + 0x1DF2CA), true, true, 0, 0, sizeof(sect2));
	//	memcpy(func.sect2, sect2, sizeof(sect2));
	//	UpdateActorProxy = func.addr;
	//}
	//{
	//	byte sect1[] =
	//	{
	//		0x48, 0x8B, 0xCB, //mov rcx,rbx
	//	};
	//	FUNC func = CreateFunction(UpdateMotion, (appBaseAddr + 0x1DF2CA), true, true, 0, sizeof(sect1));
	//	memcpy(func.sect1, sect1, sizeof(sect1));
	//	WriteJump((UpdateActorProxy + 0x52), func.addr);
	//}



	//{
	//	byte8 sect1[] =
	//	{
	//		0x48, 0x8B, 0xCB, //mov rcx,rbx
	//	};
	//	byte8 sect2[] =
	//	{
	//		0x48, 0x8B, 0x5C, 0x24, 0x58, //mov rbx,[rsp+58]
	//	};
	//	FUNC func = CreateFunction(UpdateActorAttributes, (appBaseAddr + 0x1F7D8C), true, true, 0, sizeof(sect1), sizeof(sect2));
	//	memcpy(func.sect1, sect1, sizeof(sect1));
	//	memcpy(func.sect2, sect2, sizeof(sect2));
	//	WriteJump((appBaseAddr + 0x1F7D87), func.addr);
	//}


	//#pragma endregion

	//{
	//	auto func = CreateFunction(HumanDante);
	//	Log("HumanDante %llX", func.addr);
	//	//WriteCall((appBaseAddr + 0x212CB3), func.addr);
	//}
	//{
	//	auto func = CreateFunction(HumanVergil);
	//	Log("HumanVergil %llX", func.addr);
	//	//WriteCall((appBaseAddr + 0x220A30), func.addr); // Vergil Human Model Texture Update
	//}
	//{
	//	auto func = CreateFunction(DevilCerberusSlot1);
	//	Log("DevilCerberus1 %llX", func.addr);
	//}
	//{
	//	auto func = CreateFunction(DevilCerberusSlot2);
	//	Log("DevilCerberus2 %llX", func.addr);
	//}


	//{
	//	auto func = CreateFunction(ApplyModel);
	//	Log("ApplyModel  %llX", func.addr);


	//	g_modelAddr = HighAlloc(16 * 1024 * 1024);



	//	Log("g_modelAddr %llX", g_modelAddr);
	//}


	//{
	//	auto func = CreateFunction(CopyActorData);
	//	Log("CopyActorData %llX", func.addr);
	//	Log("g_actorData %llX", &g_actorData);


	//	cerberusAddr = HighAlloc((8 * 1024 * 1024));

	//	Log("cerberusAddr %llX", cerberusAddr);
	//}






	//{
	//	auto func = CreateFunction(DanteLady);
	//	DanteLadyProxy = func.addr;
	//	Log("DanteLadyProxy %llX", DanteLadyProxy);
	//}

	//{
	//	auto func = CreateFunction(DevilRebellion);
	//	DevilRebellionProxy = func.addr;
	//	Log("DevilRebellionProxy %llX", DevilRebellionProxy);
	//}

	//{
	//	auto func = CreateFunction(DevilBeowulf);
	//	DevilBeowulfProxy = func.addr;
	//	Log("DevilBeowulfProxy %llX", DevilBeowulfProxy);
	//}



	//{
	//	auto func = CreateFunction(DevilCerberus);
	//	DevilCerberusProxy = func.addr;
	//	Log("DevilCerberusProxy %llX", DevilCerberusProxy);
	//}
	//{
	//	auto func = CreateFunction(DevilAgniRudra);
	//	DevilAgniRudraProxy = func.addr;
	//	Log("DevilAgniRudraProxy %llX", DevilAgniRudraProxy);
	//}


	//g_slotAddr = LowAlloc(1 * 1024 * 1024);
	//Log("g_slotAddr %llX", g_slotAddr);
	//g_upperBodyAddr = HighAlloc(1 * 1024 * 1024);
	//g_lowerBodyAddr = HighAlloc(1 * 1024 * 1024);
	
	//Log("g_upperBodyAddr %llX", g_upperBodyAddr);
	//Log("g_lowerBodyAddr %llX", g_lowerBodyAddr);
	
	









	//{
	//	byte8 sect0[] =
	//	{
	//		0xC7, 0x81, 0x70, 0x3E, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, //mov [rcx+00003E70],00000001
	//	};
	//	auto func = CreateFunction(QueueSlot1, (appBaseAddr + 0x1F93C9), true, true, sizeof(sect0));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	//WriteJump((appBaseAddr + 0x1F93BF), func.addr, 5);
	//	/*
	//	dmc3.exe+1F93BF - C7 81 703E0000 01000000 - mov [rcx+00003E70],00000001
	//	dmc3.exe+1F93C9 - EB 14                   - jmp dmc3.exe+1F93DF
	//	*/
	//}

	//{
	//	byte8 sect0[] =
	//	{
	//		0xC7, 0x81, 0x70, 0x3E, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, //mov [rcx+00003E70],00000002
	//	};
	//	auto func = CreateFunction(QueueSlot2, (appBaseAddr + 0x1F93DF), true, true, sizeof(sect0));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	//WriteJump((appBaseAddr + 0x1F93D5), func.addr, 5);
	//	/*
	//	dmc3.exe+1F93D5 - C7 81 703E0000 02000000 - mov [rcx+00003E70],00000002
	//	dmc3.exe+1F93DF - 89 44 24 10             - mov [rsp+10],eax
	//	*/
	//}



	//{
	//	byte8 sect0[] =
	//	{
	//		0x89, 0x83, 0x6C, 0x3E, 0x00, 0x00, //mov [rbx+00003E6C],eax
	//	};
	//	auto func = CreateFunction(UpdateSlot, (appBaseAddr + 0x1F7348), true, true, sizeof(sect0));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	//WriteJump((appBaseAddr + 0x1F7342), func.addr, 1);
	//	/*
	//	dmc3.exe+1F7342 - 89 83 6C3E0000    - mov [rbx+00003E6C],eax
	//	dmc3.exe+1F7348 - C6 83 AE3E0000 01 - mov byte ptr [rbx+00003EAE],01
	//	*/
	//}



}
















// @Todo: Create Archive module.
// @Todo: Create Edit and Restore functions.
// @Todo: Merge with Weapon module.
// @Todo: Create session data struct.
// @Todo: Auto vars.
// @Todo: Compile offset list and function range.
//        Because we also have to clear those objects.
//        Increase counter by 2 for objects with only
//        1 asset as well to be able to replace them on demand.
//        Slot 2 will always come after slot 1.
//        Don't use a counter at all. Just use the slot + internal offset.

//byte8 * System_Actor_actorBaseAddr[MAX_ACTOR] = {};

//System_Actor_UpdateDevilForm_t     System_Actor_UpdateDevilForm     = 0;
//System_Actor_UpdateFlux_t          System_Actor_UpdateFlux          = 0;
//System_Actor_Relax_t               System_Actor_Relax               = 0;
//
//byte8 * OnUpdate[2] = {};
//
//byte8 * CreateActorOneProxy = 0;
//byte8 * UpdateActorProxy    = 0;
//
//uint32 devilCounter = 0;


//typedef byte8 *(* InternalCreateActor_t)(uint8 character, uint8 actor, bool isDoppelganger);
//
//InternalCreateActor_t InternalCreateActor = 0;





















//#pragma region Ignore
//

//byte8 * actorBaseAddr[MAX_ACTOR];











//void System_Actor_ToggleArrayExtension(bool enable)
//{
	//LogFunction(enable);












































//	LogFunction(enable);
//	System_Actor_enableArrayExtension = enable;
//	if (enable)
//	{
//		// OnUpdate
//		WriteJump((appBaseAddr + 0x1BA569), OnUpdate[0]);
//		vp_memset((appBaseAddr + 0x1BA5C5), 0x90, 4);
//		Write<byte8>((appBaseAddr + 0x1BA5C9), 0x45);
//		Write<byte8>((appBaseAddr + 0x1BA5CB), 0x9A);



//		WriteJump((appBaseAddr + 0x1BC0C5), OnUpdate[1]);
//		// OnEvent
//
//
//		// What event? Sheesh.
//
//		// @Todo: Put into on demand edits.
//
//
//		// Actor Heap Stuff
//
//		Write<byte8>((appBaseAddr + 0x1BB397), 0x1C);
//		Write<byte8>((appBaseAddr + 0x1BB399), 0x90);
//
//
//
//		Write<byte16>((appBaseAddr + 0x1BB408), 0x9003);
//
//
//
//		Write<byte16>((appBaseAddr + 0x1BB457), 0x9003);
//
//
//
//
//
//	}
//	else
//	{
//		{
//			byte buffer[] =
//			{
//				0x4C, 0x8B, 0x44, 0xC1, 0x18, //mov r8,[rcx+rax*8+18]
//			};
//			vp_memcpy((appBaseAddr + 0x1BA569), buffer, sizeof(buffer));
//		}
//		{
//			byte buffer[] =
//			{
//				0x49, 0x8B, 0x42, 0x18, //mov rax,[r10+18]
//			};
//			vp_memcpy((appBaseAddr + 0x1BA5C5), buffer, sizeof(buffer));
//		}
//		Write<byte8>((appBaseAddr + 0x1BA5C9), 0x44);
//		Write<byte8>((appBaseAddr + 0x1BA5CB), 0x98);
//		{
//			byte buffer[] =
//			{
//				0x4A, 0x8B, 0x6C, 0xC0, 0x18, //mov rbp,[rax+r8*8+18]
//			};
//			vp_memcpy((appBaseAddr + 0x1BC0C5), buffer, sizeof(buffer));
//		}
//		Write<byte8>((appBaseAddr + 0x1BB397), 0x5C);
//		Write<byte8>((appBaseAddr + 0x1BB399), 0x18);
//		Write<byte16>((appBaseAddr + 0x1BB408), 0x1843);
//		Write<byte16>((appBaseAddr + 0x1BB457), 0x1843);
//	}
//}
//
//void System_Actor_ToggleCreateActorOne(bool enable)
//{
//	LogFunction(enable);
//	System_Actor_enableCreateActor = enable;
//	if (enable)
//	{
//		WriteJump((appBaseAddr + 0x23C79A), CreateActorOneProxy);
//	}
//	else
//	{
//		WriteCall((appBaseAddr + 0x23C79A), (appBaseAddr + 0x1BB470));
//	}
//}
//
//void System_Actor_ToggleUpdateActor(bool enable)
//{
//	LogFunction(enable);
//	System_Actor_enableUpdateActor = enable;
//	if (enable)
//	{
//		WriteJump((appBaseAddr + 0x1DF2C4), UpdateActorProxy, 1);
//	}
//	else
//	{
//		byte buffer[] =
//		{
//			0xFF, 0x90, 0x80, 0x00, 0x00, 0x00, //call qword ptr [rax+00000080]
//		};
//		vp_memcpy((appBaseAddr + 0x1DF2C4), buffer, sizeof(buffer));
//	}
//}
//
//void System_Actor_ToggleDoppelgangerFixes(bool enable)
//{
//	LogFunction(enable);
//	System_Actor_enableDoppelgangerFixes = enable;
//
//	// Disable Bob visibility exception.
//	WriteAddress((appBaseAddr + 0x1F83D5), (enable) ? (appBaseAddr + 0x1F83D7) : (appBaseAddr + 0x1F8428), 2);
//
//
//	/*
//	dmc3.exe+1F83D5 - 74 51                 - je dmc3.exe+1F8428
//	dmc3.exe+1F83D7 - 48 8B 0D 4A8AA900     - mov rcx,[dmc3.exe+C90E28] { (01A44800) }
//	*/
//
//
//	if (enable)
//	{
//		vp_memset((appBaseAddr + 0x1DF291), 0x90, 7); // Disable linked actor base address reset.
//		// Make IsDoppelganger check always return false.
//		{
//			byte * addr = (appBaseAddr + 0x1F78B0);
//			vp_memset(addr, 0x90, 7);
//			byte buffer[] =
//			{
//				0x30, 0xC0, //xor al,al
//				0xC3,       //ret
//			};
//			vp_memcpy(addr, buffer, sizeof(buffer));
//		}
//		Write<byte16>((appBaseAddr + 0x2134A3), 0xE990); // Skip clone creation.
//		// @Todo: Clarify.
//		Write<byte8>((appBaseAddr + 0x1F92E0), 0x00); // Devil Form: Disable Doppelganger check.
//		Write<byte8>((appBaseAddr + 0x1F92F8), 0xEB); // Devil Form: Disable isDoppelganger check.
//	}
//	else
//	{
//		{
//			byte buffer[] =
//			{
//				0x48, 0x89, 0x81, 0x78, 0x64, 0x00, 0x00, //mov [rcx+00006478],rax
//			};
//			vp_memcpy((appBaseAddr + 0x1DF291), buffer, sizeof(buffer));
//		}
//		{
//			byte buffer[] =
//			{
//				0x83, 0xB9, 0x1C, 0x01, 0x00, 0x00, 0x01, //cmp dword ptr [rcx+0000011C],01
//			};
//			vp_memcpy((appBaseAddr + 0x1F78B0), buffer, sizeof(buffer));
//		}
//		Write<byte16>((appBaseAddr + 0x2134A3), 0x840F);
//		Write<byte8>((appBaseAddr + 0x1F92E0), 0x0D);
//		Write<byte8>((appBaseAddr + 0x1F92F8), 0x75);
//	}
//}
//
//void System_Actor_ToggleModelFixes(bool enable)
//{
//	LogFunction(enable);
//	if (enable)
//	{
//		vp_memset((appBaseAddr + 0x215577), 0x90, 5); // Disable Object Partition Update Dante
//	}
//	else
//	{
//		WriteCall((appBaseAddr + 0x215577), (appBaseAddr + 0x2169F0));
//	}
//}
//
//void System_Actor_ToggleDisableIdleTimer(bool enable)
//{
//	LogFunction(enable);
//	if (enable)
//	{
//		vp_memset((appBaseAddr + 0x1F2A38), 0x90, 5); // Dante
//		vp_memset((appBaseAddr + 0x1F29AE), 0x90, 5); // Vergil
//	}
//	else
//	{
//		byte8 buffer[] =
//		{
//			0xF3, 0x0F, 0x5C, 0x4B, 0x14, //subss xmm1,[rbx+14]
//		};
//		vp_memcpy((appBaseAddr + 0x1F2A38), buffer, sizeof(buffer));
//		vp_memcpy((appBaseAddr + 0x1F29AE), buffer, sizeof(buffer));
//	}
//}
//
//#pragma endregion



//void HumanVergil(byte8 * baseAddr)
//{
//	byte8 * textureFile = 0;
//	byte8 * modelFile   = 0;
//	byte8 * shadowFile  = 0;
//	byte8 * clothFile   = 0;
//	byte8 * addr = 0;
//	uint32 count = 0;
//
//	vec4 * g_vertex     = 0;
//
//	byte8 * dest = 0;
//	byte8 * addr2 = 0;
//
//
//
//	textureFile = System_File_GetFile(System_File_cacheFile[em034], 31);
//	modelFile   = System_File_GetFile(System_File_cacheFile[em034], 32);
//	func_8B470((baseAddr + 0x200), 1);
//	func_89960((baseAddr + 0x200), modelFile, textureFile);
//
//	shadowFile = System_File_GetFile(System_File_cacheFile[pl021], 8);
//	addr = func_89DE0((baseAddr + 0x200));
//	func_8BC60((baseAddr + 0x9AF0), addr, shadowFile);
//	addr = func_89DE0((baseAddr + 0x200));
//	func_305D80(addr);
//
//	g_vertex = (vec4 *)(appBaseAddr + 0x58B260);
//	auto md = (MODEL_DATA *)(baseAddr + 0xB640);
//
//	//md[0].count = 4;
//	//md[0].vertex[0] = g_vertex[0];
//	//md[0].vertex[1] = g_vertex[1];
//	//md[0].vertex[2] = g_vertex[2];
//
//	//md[1].count = 4;
//	//md[1].vertex[0] = g_vertex[3];
//	//md[1].vertex[1] = g_vertex[4];
//	//md[1].vertex[2] = g_vertex[5];
//
//	//md[2].count = 4;
//	//md[2].vertex[0] = g_vertex[6];
//	//md[2].vertex[1] = g_vertex[7];
//	//md[2].vertex[2] = g_vertex[8];
//
//	//md[3].count = 4;
//	//md[3].vertex[0] = g_vertex[9];
//	//md[3].vertex[1] = g_vertex[10];
//	//md[3].vertex[2] = g_vertex[11];
//
//	//md[4].count = 4;
//	//md[4].vertex[0] = g_vertex[12];
//	//md[4].vertex[1] = g_vertex[13];
//	//md[4].vertex[2] = g_vertex[14];
//
//	//md[5].count = 4;
//	//md[5].vertex[0] = g_vertex[15];
//	//md[5].vertex[1] = g_vertex[16];
//	//md[5].vertex[2] = g_vertex[17];
//
//
//
//
//
//	// No Coat
//
//	//textureFile = System_File_GetFile(System_File_cacheFile[pl023], 0 );
//	//modelFile   = System_File_GetFile(System_File_cacheFile[pl023], 12);
//	//func_8B470((baseAddr + 0x7540), 1);
//	//func_89960((baseAddr + 0x7540), modelFile, textureFile);
//	//*(uint8 *)(baseAddr + 0x9AC0) = 1;
//	//func_8A000((baseAddr + 0x7540), 0, (baseAddr + 0xA0F0));
//
//	//md[0].count = 4;
//	//md[0].vertex[0] = g_vertex[23];
//	//md[0].vertex[1] = g_vertex[24];
//	//md[0].vertex[2] = g_vertex[25];
//
//
//
//
//	//clothFile = System_File_GetFile(System_File_cacheFile[pl023], 13);
//	//count = func_2C9F40(clothFile);
//
//	//byte8 * dest = (baseAddr + 0xA230);
//	//for (uint32 index = 0; index < count; index++)
//	//{
//	//	func_2CA1D0(dest, (baseAddr + 0xA0F0), clothFile, index);
//	//	dest += 0xF0;
//	//}
//
//	//func_2CA2F0
//	//(
//	//	(baseAddr + 0xA230),
//	//	(baseAddr + 0x1880),
//	//	(appBaseAddr + 0x58B054),
//	//	(baseAddr + 0xB640),
//	//	1
//	//);
//
//
//
//
//	textureFile = System_File_GetFile(System_File_cacheFile[pl021], 0 );
//	// rax 00000000213B9080
//	// nrax 00000000213B9080
//
//	modelFile   = System_File_GetFile(System_File_cacheFile[pl021], 12);
//	// rax 00000000214E6E70
//	// nrax 00000000214E6E70
//
//	// rcx 00000000045F43B0
//	// rdx 0000000000000001
//	// nrcx 00000000045F43B0
//	// nrdx 0000000000000001
//	func_8B470((baseAddr + 0x7540), 1);
//
//
//
//	// rcx 00000000045F43B0
//	// rdx 00000000214E6E70
//	// r8  00000000213B9080
//	// nrcx 00000000045F43B0
//	// nrdx 00000000214E6E70
//	// nr8  00000000213B9080
//	func_89960((baseAddr + 0x7540), modelFile, textureFile);
//
//	*(uint8 *)(baseAddr + 0x9AC0) = 1;
//
//	// rcx 00000000045F43B0
//	// rdx 0000000000000000
//	// r8  00000000045F6F60
//	// nrcx 00000000045F43B0
//	// nrdx 0000000000000000
//	// nr8  00000000045F6F60
//	func_8A000((baseAddr + 0x7540), 0, (baseAddr + 0xA0F0));
//
//
//
//
//	addr2 = *(byte8 **)(baseAddr + 0xA0F0);
//	// rax 0000000004623270
//	// nrax 0000000004623270
//
//	addr2 = *(byte8 **)(addr2 + 0x108);
//	// rcx 00000000046232B0
//	// nrcx 00000000046232B0
//
//
//	auto g_coatVertex = (vec4 *)(appBaseAddr + 0x35D580);
//
//
//	auto coatVertex = (vec4 *)addr2;
//
//	coatVertex[0] = g_coatVertex[0];
//	coatVertex[1] = g_coatVertex[1];
//	coatVertex[2] = g_coatVertex[2];
//	coatVertex[3] = g_coatVertex[3];
//
//
//
//	//md[0].count = 4;
//	//md[0].vertex[0] = g_vertex[0];
//	//md[0].vertex[1] = g_vertex[1];
//	//md[0].vertex[2] = g_vertex[2];
//
//	//md[1].count = 4;
//	//md[1].vertex[0] = g_vertex[3];
//	//md[1].vertex[1] = g_vertex[4];
//	//md[1].vertex[2] = g_vertex[5];
//
//	//md[2].count = 4;
//	//md[2].vertex[0] = g_vertex[6];
//	//md[2].vertex[1] = g_vertex[7];
//	//md[2].vertex[2] = g_vertex[8];
//
//	//md[3].count = 4;
//	//md[3].vertex[0] = g_vertex[9];
//	//md[3].vertex[1] = g_vertex[10];
//	//md[3].vertex[2] = g_vertex[11];
//
//	//md[4].count = 4;
//	//md[4].vertex[0] = g_vertex[12];
//	//md[4].vertex[1] = g_vertex[13];
//	//md[4].vertex[2] = g_vertex[14];
//
//	//md[5].count = 4;
//	//md[5].vertex[0] = g_vertex[15];
//	//md[5].vertex[1] = g_vertex[16];
//	//md[5].vertex[2] = g_vertex[17];
//
//
//
//
//
//
//
//
//	clothFile = System_File_GetFile(System_File_cacheFile[pl021], 13);
//	// rax 00000000214ED330
//	// nrax 00000000214ED330
//
//
//	// rcx 00000000214ED330
//	// nrcx 00000000214ED330
//	count = func_2C9F40(clothFile);
//	// rax 0000000000000001
//	// nrax 0000000000000001
//
//
//
//	dest = (baseAddr + 0xA230);
//	for (uint32 index = 0; index < count; index++)
//	{
//
//		// rcx 00000000045F70A0
//		// rdx 00000000045F6F60
//		// r8  00000000214ED330
//		// r9  0000000000000000
//		// nrcx 00000000045F70A0
//		// nrdx 00000000045F6F60
//		// nr8  00000000214ED330
//		// nr9  0000000000000000
//		func_2CA1D0(dest, (baseAddr + 0xA0F0), clothFile, index);
//		dest += 0xF0;
//	}
//
//
//
//	// rcx    00000000045F70A0
//	// rdx    00000000045EE6F0
//	// r8     00007FF6817FB380
//	// r9     00000000045F84B0
//	// rsp+20 0000000000000006
//	// nrcx    00000000045F70A0
//	// nrdx    00000000045EE6F0
//	// nr8     00007FF6817FB380
//	// nr9     00000000045F84B0
//	// nrsp+20 0000000000000006
//	func_2CA2F0
//	(
//		(baseAddr + 0xA230),
//		(baseAddr + 0x1880),
//		(appBaseAddr + 0x58B380),
//		//(baseAddr + 0xB640),
//		0,
//		6
//	);
//
//
//
//	auto coatShadowFile = System_File_GetFile(System_File_cacheFile[pl021], 14);
//	// rax 00000000214ED6A0
//	// nrax 00000000214ED6A0
//
//
//	// rcx 00000000045F43B0
//	// nrcx 00000000045F43B0
//	addr = func_89DE0((baseAddr + 0x7540));
//	// rax 00000000045F4430
//	// nrax 00000000045F4430
//
//
//	// rcx 00000000045F6BA0
//	// rdx 00000000045F4430
//	// r8  00000000214ED6A0
//	// nrcx 00000000045F6BA0
//	// nrdx 00000000045F4430
//	// nr8  00000000214ED6A0
//	func_8BC60((baseAddr + 0x9D30), addr, coatShadowFile);
//
//
//	// rcx 00000000045F43B0
//	// nrcx 00000000045F43B0
//	addr = func_89DE0((baseAddr + 0x7540));
//	// rax 00000000045F4430
//	// nrax 00000000045F4430
//
//
//	// rcx 00000000045F4430
//	// nrcx 00000000045F4430
//	func_305D80(addr);
//
//
//
//
//
//
//}

#pragma endregion




















