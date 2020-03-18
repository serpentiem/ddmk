





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

#include "Actor.h"

bool System_Actor_enableArrayExtension    = false;
bool System_Actor_enableCreateActor       = false;
bool System_Actor_enableUpdateActor       = false;
bool System_Actor_enableDoppelgangerFixes = false;
bool System_Actor_enableModelFixes        = false;

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





PrivateStart;

//typedef byte8 *(* InternalCreateActor_t)(uint8 character, uint8 actor, bool isDoppelganger);
//
//InternalCreateActor_t InternalCreateActor = 0;





struct MotionHelper
{
	uint8 motionId;
	uint16 cacheFileId;
};

MotionHelper motionHelperDante[] =
{
	{ MOT_DANTE_BASE                  , pl000_00_0  },
	{ MOT_DANTE_DAMAGE                , pl000_00_1  },
	{ MOT_DANTE_TAUNTS                , pl000_00_2  },
	{ MOT_DANTE_REBELLION             , pl000_00_3  },
	{ MOT_DANTE_CERBERUS              , pl000_00_4  },
	{ MOT_DANTE_AGNI_RUDRA            , pl000_00_5  },
	{ MOT_DANTE_NEVAN                 , pl000_00_6  },
	{ MOT_DANTE_BEOWULF               , pl000_00_7  },
	{ MOT_DANTE_EBONY_IVORY           , pl000_00_8  },
	{ MOT_DANTE_SHOTGUN               , pl000_00_9  },
	{ MOT_DANTE_ARTEMIS               , pl000_00_10 },
	{ MOT_DANTE_SPIRAL                , pl000_00_11 },
	{ MOT_DANTE_KALINA_ANN            , pl000_00_12 },
	{ MOT_DANTE_SWORDMASTER_REBELLION , pl000_00_13 },
	{ MOT_DANTE_SWORDMASTER_CERBERUS  , pl000_00_14 },
	{ MOT_DANTE_SWORDMASTER_AGNI_RUDRA, pl000_00_15 },
	{ MOT_DANTE_SWORDMASTER_NEVAN     , pl000_00_16 },
	{ MOT_DANTE_SWORDMASTER_BEOWULF   , pl000_00_17 },
	{ MOT_DANTE_GUNSLINGER_EBONY_IVORY, pl000_00_18 },
	{ MOT_DANTE_GUNSLINGER_SHOTGUN    , pl000_00_19 },
	{ MOT_DANTE_GUNSLINGER_ARTEMIS    , pl000_00_20 },
	{ MOT_DANTE_GUNSLINGER_SPIRAL     , pl000_00_21 },
	{ MOT_DANTE_GUNSLINGER_KALINA_ANN , pl000_00_22 },
	{ MOT_DANTE_TRICKSTER             , pl000_00_23 },
	{ MOT_DANTE_ROYALGUARD            , pl000_00_24 },
	{ MOT_DANTE_QUICKSILVER           , pl000_00_25 },
	{ MOT_DANTE_DOPPELGANGER          , pl000_00_26 },
};

MotionHelper motionHelperBob[] =
{
	{ MOT_BOB_BASE       , pl001_00_0  },
	{ MOT_BOB_DAMAGE     , pl001_00_1  },
	{ MOT_BOB_TAUNTS     , pl001_00_2  },
	{ MOT_BOB_MELEE_STYLE, pl001_00_31 },
};

MotionHelper motionHelperLady[] =
{
	{ MOT_LADY_BASE      , pl002_00_0  },
	{ MOT_LADY_DAMAGE    , pl002_00_1  },
	{ MOT_LADY_TAUNTS    , pl002_00_2  },
	{ MOT_LADY_KALINA_ANN, pl000_00_12 },
};

MotionHelper motionHelperVergil[] =
{
	{ MOT_VERGIL_BASE                  , pl021_00_0 },
	{ MOT_VERGIL_DAMAGE                , pl021_00_1 },
	{ MOT_VERGIL_TAUNTS                , pl021_00_2 },
	{ MOT_VERGIL_YAMATO                , pl021_00_3 },
	{ MOT_VERGIL_BEOWULF               , pl021_00_4 },
	{ MOT_VERGIL_FORCE_EDGE            , pl021_00_5 },
	{ MOT_VERGIL_DARK_SLAYER           , pl021_00_6 },
	{ MOT_VERGIL_NERO_ANGELO_YAMATO    , pl021_00_7 },
	{ MOT_VERGIL_NERO_ANGELO_BEOWULF   , pl021_00_8 },
	{ MOT_VERGIL_NERO_ANGELO_FORCE_EDGE, pl021_00_9 },
};

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

PrivateEnd;

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

uint8 System_Actor_GetActorCount()
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

PrivateStart;























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

PrivateEnd;









void UpdateActorDante(byte8 * baseAddr)
{
	//LogFunction(baseAddr);
	//auto actorData = (ACTOR_DATA *)baseAddr;
	//*(uint32 *)(baseAddr + 0x9AC0) = 0x01010101;
	//*(uint8  *)(baseAddr + 0x9AC4) = 0x01;
	//memset((baseAddr + 0xB600), 0, 0x30);
	//memset((baseAddr + 0x38A0), 0, (32 * 8));


	
	/*
	dmc3.exe+212C20 - C6 81 02B60000 FF     - mov byte ptr [rcx+0000],-01 { 255 }
	dmc3.exe+212C2B - C6 81 05B60000 FF     - mov byte ptr [rcx+0000],-01 { 255 }
	dmc3.exe+212C32 - C6 81 0AB60000 FF     - mov byte ptr [rcx+0000],-01 { 255 }
	dmc3.exe+212C39 - C6 81 11B60000 FF     - mov byte ptr [rcx+0000],-01 { 255 }
	dmc3.exe+212C40 - C6 81 14B60000 FF     - mov byte ptr [rcx+0000],-01 { 255 }
	dmc3.exe+212C47 - C6 81 19B60000 FF     - mov byte ptr [rcx+0000],-01 { 255 }
	dmc3.exe+212C4E - C6 81 1EB60000 FF     - mov byte ptr [rcx+0000],-01 { 255 }
	*/



	*(byte8 *)(baseAddr + 0xB602) = 0xFF;
	*(byte8 *)(baseAddr + 0xB605) = 0xFF;
	*(byte8 *)(baseAddr + 0xB60A) = 0xFF;
	*(byte8 *)(baseAddr + 0xB611) = 0xFF;
	*(byte8 *)(baseAddr + 0xB614) = 0xFF;
	*(byte8 *)(baseAddr + 0xB619) = 0xFF;
	*(byte8 *)(baseAddr + 0xB61E) = 0xFF;







	System_File_UpdateFileItems((ACTOR_DATA *)baseAddr);









	Cosmetics_Model_UpdateModelDanteVergil[0](baseAddr);
	//Cosmetics_Model_UpdateDevilModelDante[0](baseAddr, 1);

	Cosmetics_Model_UpdateDevilModelDante[0](baseAddr, 1);
	Cosmetics_Model_UpdateDevilModelDante[1](baseAddr, 2);

	










	auto motionFile = (byte8 **)(baseAddr + 0x38A0);

	for (uint8 index = 0; index < countof(motionHelperDante); index++)
	{
		auto & motionId    = motionHelperDante[index].motionId;
		auto & cacheFileId = motionHelperDante[index].cacheFileId;

		motionFile[motionId] = System_File_cacheFile[cacheFileId];
	}

	func_1EF040(baseAddr, 0);

	func_1EEF80(baseAddr);

	func_1EF040(baseAddr, 3);

	*(byte8 **)(baseAddr + 0x3DD0) = *(byte8 **)(appBaseAddr + 0x590598);
	*(byte8 **)(baseAddr + 0x3DD8) = *(byte8 **)(appBaseAddr + 0x58A2A0);
	*(byte8 **)(baseAddr + 0x3DE0) = (appBaseAddr + 0x5905B0);
	*(byte8 **)(baseAddr + 0x3DE8) = System_File_cacheFile[pl000][9];
	*(byte8 **)(baseAddr + 0x3DF0) = System_File_cacheFile[pl000][10];
	*(byte8 **)(baseAddr + 0x3DF8) = System_File_cacheFile[pl000][11];
	





	func_2EE3D0((baseAddr + 0x3C50));
	func_1FAF40(baseAddr);



	//memset((baseAddr + 0xB850), 0, 0x40);
}



typedef byte8 *(__fastcall * RegisterWeapon_t)(byte8 * baseAddr, uint32 id);

RegisterWeapon_t RegisterWeapon[MAX_WEAPON] = {};

inline void RegisterWeapon_Init()
{
	RegisterWeapon[WEAPON_DANTE_REBELLION  ] = func_2310B0;
	RegisterWeapon[WEAPON_DANTE_CERBERUS   ] = func_22EC90;
	RegisterWeapon[WEAPON_DANTE_AGNI_RUDRA ] = func_227870;
	RegisterWeapon[WEAPON_DANTE_NEVAN      ] = func_22A1E0;
	RegisterWeapon[WEAPON_DANTE_BEOWULF    ] = func_228CF0;
	RegisterWeapon[WEAPON_DANTE_EBONY_IVORY] = func_22B0C0;
	RegisterWeapon[WEAPON_DANTE_SHOTGUN    ] = func_2306B0;
	RegisterWeapon[WEAPON_DANTE_ARTEMIS    ] = func_22C4A0;
	RegisterWeapon[WEAPON_DANTE_SPIRAL     ] = func_2300A0;
	RegisterWeapon[WEAPON_DANTE_KALINA_ANN ] = func_22BA30;

	RegisterWeapon[WEAPON_VERGIL_YAMATO    ] = func_22D960;
	RegisterWeapon[WEAPON_VERGIL_BEOWULF   ] = func_228CF0;
	RegisterWeapon[WEAPON_VERGIL_FORCE_EDGE] = func_2298E0;
}

void UpdateWeaponDante(byte8 * baseAddr)
{
	auto & actorData = *(ACTOR_DATA *)baseAddr;

	//for (uint8 index = 0; index < MAX_WEAPON_DANTE; index++)
	//{
	//	RegisterWeapon[index](baseAddr, index);
	//}

	memset(actorData.weaponMetadata, 0, 100);

	actorData.weaponMetadata[0] = RegisterWeapon[WEAPON_DANTE_REBELLION  ](baseAddr, 0);
	actorData.weaponMetadata[1] = RegisterWeapon[WEAPON_DANTE_CERBERUS   ](baseAddr, 0);
	actorData.weaponMetadata[2] = RegisterWeapon[WEAPON_DANTE_EBONY_IVORY](baseAddr, 0);
	actorData.weaponMetadata[3] = RegisterWeapon[WEAPON_DANTE_SHOTGUN    ](baseAddr, 0);

	*(uint32 *)(baseAddr + 0x64D8) = 4;







}

byte8 * CreateActor
(
	uint8 character,
	uint8 actor
)
{
	auto g_pool = *(byte8 ***)(appBaseAddr + 0xC90E28);

	byte8 * sessionData = 0;

	byte8 * baseAddr = 0;

	sessionData = (g_pool[1] + 0x16C);

	//func_2EE060((mainActorBaseAddr + 0x6410), 0x3C);

	baseAddr = func_1DE820(character, actor, false);

	//func_1BB390(g_pool, actor);

	func_217B90(baseAddr, sessionData); // InitActorDante
	UpdateActorDante(baseAddr);
	UpdateWeaponDante(baseAddr);

	func_1DFC20(baseAddr);

	return baseAddr;
}

void HumanVergil(byte8 * baseAddr)
{
	byte8 * textureFile = 0;
	byte8 * modelFile   = 0;
	byte8 * shadowFile  = 0;
	byte8 * clothFile   = 0;
	byte8 * addr = 0;
	uint32 count = 0;

	vec4 * g_vertex     = 0;

	byte8 * dest = 0;
	byte8 * addr2 = 0;



	textureFile = System_File_GetFile(System_File_cacheFile[em034], 31);
	modelFile   = System_File_GetFile(System_File_cacheFile[em034], 32);
	func_8B470((baseAddr + 0x200), 1);
	func_89960((baseAddr + 0x200), modelFile, textureFile);

	shadowFile = System_File_GetFile(System_File_cacheFile[pl021], 8);
	addr = func_89DE0((baseAddr + 0x200));
	func_8BC60((baseAddr + 0x9AF0), addr, shadowFile);
	addr = func_89DE0((baseAddr + 0x200));
	func_305D80(addr);

	g_vertex = (vec4 *)(appBaseAddr + 0x58B260);
	auto md = (MODEL_DATA *)(baseAddr + 0xB640);

	//md[0].count = 4;
	//md[0].vertex[0] = g_vertex[0];
	//md[0].vertex[1] = g_vertex[1];
	//md[0].vertex[2] = g_vertex[2];

	//md[1].count = 4;
	//md[1].vertex[0] = g_vertex[3];
	//md[1].vertex[1] = g_vertex[4];
	//md[1].vertex[2] = g_vertex[5];

	//md[2].count = 4;
	//md[2].vertex[0] = g_vertex[6];
	//md[2].vertex[1] = g_vertex[7];
	//md[2].vertex[2] = g_vertex[8];

	//md[3].count = 4;
	//md[3].vertex[0] = g_vertex[9];
	//md[3].vertex[1] = g_vertex[10];
	//md[3].vertex[2] = g_vertex[11];

	//md[4].count = 4;
	//md[4].vertex[0] = g_vertex[12];
	//md[4].vertex[1] = g_vertex[13];
	//md[4].vertex[2] = g_vertex[14];

	//md[5].count = 4;
	//md[5].vertex[0] = g_vertex[15];
	//md[5].vertex[1] = g_vertex[16];
	//md[5].vertex[2] = g_vertex[17];





	// No Coat

	//textureFile = System_File_GetFile(System_File_cacheFile[pl023], 0 );
	//modelFile   = System_File_GetFile(System_File_cacheFile[pl023], 12);
	//func_8B470((baseAddr + 0x7540), 1);
	//func_89960((baseAddr + 0x7540), modelFile, textureFile);
	//*(uint8 *)(baseAddr + 0x9AC0) = 1;
	//func_8A000((baseAddr + 0x7540), 0, (baseAddr + 0xA0F0));

	//md[0].count = 4;
	//md[0].vertex[0] = g_vertex[23];
	//md[0].vertex[1] = g_vertex[24];
	//md[0].vertex[2] = g_vertex[25];




	//clothFile = System_File_GetFile(System_File_cacheFile[pl023], 13);
	//count = func_2C9F40(clothFile);

	//byte8 * dest = (baseAddr + 0xA230);
	//for (uint32 index = 0; index < count; index++)
	//{
	//	func_2CA1D0(dest, (baseAddr + 0xA0F0), clothFile, index);
	//	dest += 0xF0;
	//}

	//func_2CA2F0
	//(
	//	(baseAddr + 0xA230),
	//	(baseAddr + 0x1880),
	//	(appBaseAddr + 0x58B054),
	//	(baseAddr + 0xB640),
	//	1
	//);




	textureFile = System_File_GetFile(System_File_cacheFile[pl021], 0 );
	// rax 00000000213B9080
	// nrax 00000000213B9080

	modelFile   = System_File_GetFile(System_File_cacheFile[pl021], 12);
	// rax 00000000214E6E70
	// nrax 00000000214E6E70

	// rcx 00000000045F43B0
	// rdx 0000000000000001
	// nrcx 00000000045F43B0
	// nrdx 0000000000000001
	func_8B470((baseAddr + 0x7540), 1);



	// rcx 00000000045F43B0
	// rdx 00000000214E6E70
	// r8  00000000213B9080
	// nrcx 00000000045F43B0
	// nrdx 00000000214E6E70
	// nr8  00000000213B9080
	func_89960((baseAddr + 0x7540), modelFile, textureFile);

	*(uint8 *)(baseAddr + 0x9AC0) = 1;

	// rcx 00000000045F43B0
	// rdx 0000000000000000
	// r8  00000000045F6F60
	// nrcx 00000000045F43B0
	// nrdx 0000000000000000
	// nr8  00000000045F6F60
	func_8A000((baseAddr + 0x7540), 0, (baseAddr + 0xA0F0));




	addr2 = *(byte8 **)(baseAddr + 0xA0F0);
	// rax 0000000004623270
	// nrax 0000000004623270

	addr2 = *(byte8 **)(addr2 + 0x108);
	// rcx 00000000046232B0
	// nrcx 00000000046232B0


	auto g_coatVertex = (vec4 *)(appBaseAddr + 0x35D580);


	auto coatVertex = (vec4 *)addr2;

	coatVertex[0] = g_coatVertex[0];
	coatVertex[1] = g_coatVertex[1];
	coatVertex[2] = g_coatVertex[2];
	coatVertex[3] = g_coatVertex[3];



	//md[0].count = 4;
	//md[0].vertex[0] = g_vertex[0];
	//md[0].vertex[1] = g_vertex[1];
	//md[0].vertex[2] = g_vertex[2];

	//md[1].count = 4;
	//md[1].vertex[0] = g_vertex[3];
	//md[1].vertex[1] = g_vertex[4];
	//md[1].vertex[2] = g_vertex[5];

	//md[2].count = 4;
	//md[2].vertex[0] = g_vertex[6];
	//md[2].vertex[1] = g_vertex[7];
	//md[2].vertex[2] = g_vertex[8];

	//md[3].count = 4;
	//md[3].vertex[0] = g_vertex[9];
	//md[3].vertex[1] = g_vertex[10];
	//md[3].vertex[2] = g_vertex[11];

	//md[4].count = 4;
	//md[4].vertex[0] = g_vertex[12];
	//md[4].vertex[1] = g_vertex[13];
	//md[4].vertex[2] = g_vertex[14];

	//md[5].count = 4;
	//md[5].vertex[0] = g_vertex[15];
	//md[5].vertex[1] = g_vertex[16];
	//md[5].vertex[2] = g_vertex[17];








	clothFile = System_File_GetFile(System_File_cacheFile[pl021], 13);
	// rax 00000000214ED330
	// nrax 00000000214ED330


	// rcx 00000000214ED330
	// nrcx 00000000214ED330
	count = func_2C9F40(clothFile);
	// rax 0000000000000001
	// nrax 0000000000000001



	dest = (baseAddr + 0xA230);
	for (uint32 index = 0; index < count; index++)
	{

		// rcx 00000000045F70A0
		// rdx 00000000045F6F60
		// r8  00000000214ED330
		// r9  0000000000000000
		// nrcx 00000000045F70A0
		// nrdx 00000000045F6F60
		// nr8  00000000214ED330
		// nr9  0000000000000000
		func_2CA1D0(dest, (baseAddr + 0xA0F0), clothFile, index);
		dest += 0xF0;
	}



	// rcx    00000000045F70A0
	// rdx    00000000045EE6F0
	// r8     00007FF6817FB380
	// r9     00000000045F84B0
	// rsp+20 0000000000000006
	// nrcx    00000000045F70A0
	// nrdx    00000000045EE6F0
	// nr8     00007FF6817FB380
	// nr9     00000000045F84B0
	// nrsp+20 0000000000000006
	func_2CA2F0
	(
		(baseAddr + 0xA230),
		(baseAddr + 0x1880),
		(appBaseAddr + 0x58B380),
		//(baseAddr + 0xB640),
		0,
		6
	);



	auto coatShadowFile = System_File_GetFile(System_File_cacheFile[pl021], 14);
	// rax 00000000214ED6A0
	// nrax 00000000214ED6A0


	// rcx 00000000045F43B0
	// nrcx 00000000045F43B0
	addr = func_89DE0((baseAddr + 0x7540));
	// rax 00000000045F4430
	// nrax 00000000045F4430


	// rcx 00000000045F6BA0
	// rdx 00000000045F4430
	// r8  00000000214ED6A0
	// nrcx 00000000045F6BA0
	// nrdx 00000000045F4430
	// nr8  00000000214ED6A0
	func_8BC60((baseAddr + 0x9D30), addr, coatShadowFile);


	// rcx 00000000045F43B0
	// nrcx 00000000045F43B0
	addr = func_89DE0((baseAddr + 0x7540));
	// rax 00000000045F4430
	// nrax 00000000045F4430


	// rcx 00000000045F4430
	// nrcx 00000000045F4430
	func_305D80(addr);






}










byte8 * System_Actor_mainActorBaseAddr = 0;
byte8 * System_Actor_mainCloneBaseAddr = 0;

byte8 ** System_Actor_actorBaseAddr = 0;
byte8 ** System_Actor_cloneBaseAddr = 0;



//byte8 *(addr[4]) = 0;








void System_Actor_ToggleArrayExtension(bool enable)
{
	LogFunction(enable);

	// Increase ACTOR_DATA size.

	{
		constexpr uint32 defaultSize = 0xB8C0;
		constexpr uint32 size        = (defaultSize + 0x10);

		Write<uint32>((appBaseAddr + 0x1DE5FA), (enable) ? size : defaultSize);
		Write<uint32>((appBaseAddr + 0x1DE67A), (enable) ? size : defaultSize);
		Write<uint32>((appBaseAddr + 0x1DE8B4), (enable) ? size : defaultSize);
		Write<uint32>((appBaseAddr + 0x1DEBE2), (enable) ? size : defaultSize);
	}

	// Redirect pool and remove offset.

	{
		Write<byte8>((appBaseAddr + 0x1BC0B5), (enable) ? 0x8D : 0x8B);
		WriteAddress((appBaseAddr + 0x1BC0B4), (enable) ? (byte8 *)System_Actor_actorBaseAddr : (appBaseAddr + 0xC90E28), 7);
		Write<byte8>((appBaseAddr + 0x1BC0C9), (enable) ? 0 : 0x18);

		Write<byte8>((appBaseAddr + 0x1F90C5), (enable) ? 0x8D : 0x8B);
		WriteAddress((appBaseAddr + 0x1F90C4), (enable) ? (byte8 *)System_Actor_actorBaseAddr : (appBaseAddr + 0xC90E28), 7);
		Write<byte8>((appBaseAddr + 0x1BA56D), (enable) ? 0 : 0x18);
		Write<byte8>((appBaseAddr + 0x1BA5C8), (enable) ? 0 : 0x18);
	}



	{
		byte8 sect0[] =
		{
			0x80, 0xBB, 0xC0, 0xB8, 0x00, 0x00, 0x01, //cmp byte ptr [rbx+0000B8C0],01
			0x0F, 0x85, 0x00, 0x00, 0x00, 0x00,       //jne dmc3.exe+1BC0A0
			0xC3,                                     //ret
		};
		auto func = CreateFunction(0, 0, false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteAddress((func.sect0 + 7), (appBaseAddr + 0x1BC0A0), 6);
		WriteCall((appBaseAddr + 0x1E889E), func.addr);
		WriteCall((appBaseAddr + 0x1E8965), func.addr);
	}
	{
		byte8 sect0[] =
		{
			0x80, 0xBF, 0xC0, 0xB8, 0x00, 0x00, 0x01, //cmp byte ptr [rdi+0000B8C0],01
			0x0F, 0x85, 0x00, 0x00, 0x00, 0x00,       //jne dmc3.exe+1BA560
			0xC3,                                     //ret
		};
		auto func = CreateFunction(0, 0, false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteAddress((func.sect0 + 7), (appBaseAddr + 0x1BA560), 6);
		WriteCall((appBaseAddr + 0x1F90CB), func.addr);
	}






}










void System_Actor_Init()
{
	LogFunction();


	RegisterWeapon_Init();


	System_Actor_actorBaseAddr = (byte8 **)HighAlloc((MAX_ACTOR * 8));
	System_Actor_cloneBaseAddr = (byte8 **)HighAlloc((MAX_ACTOR * 8));

	System_Actor_actorBaseAddr[ACTOR_ONE] = (byte8 *)0x12345678;
	System_Actor_cloneBaseAddr[ACTOR_ONE] = (byte8 *)0xDEADBEEF;

	Log("actorBaseAddr %llX", System_Actor_actorBaseAddr);
	Log("cloneBaseAddr %llX", System_Actor_cloneBaseAddr);











	
	//auto func = CreateFunction(CreateActor);
	//Log("CreateActor %llX", func.addr);

	Log("CreateActor %llX", CreateActor);




	{
		constexpr uint32 size = 374;
		auto func = CreateFunction(0, 0, false, true, size);
		memcpy(func.sect0, (appBaseAddr + 0x1BC0A0), size);

		



		WriteAddress((func.sect0 + 0x14), (byte8 *)System_Actor_actorBaseAddr, 7);
		*(byte8 *)(func.sect0 + 0x15) = 0x8D;



		//System_Actor_actorBaseAddr[ACTOR_TWO] = 0;



		*(byte8 *)(func.sect0 + 0x29) = 0;










		WriteCall((func.sect0 + 0x2D), (appBaseAddr + 0x1EBB40));
		WriteCall((func.sect0 + 0x41), (appBaseAddr + 0x1F78B0));
		WriteCall((func.sect0 + 0x5C), (appBaseAddr + 0x1BBCD0));
		WriteCall((func.sect0 + 0x72), (appBaseAddr + 0x1F78B0));
		WriteCall((func.sect0 + 0x7E), (appBaseAddr + 0x1BA120));
		WriteAddress((func.sect0 + 0x9C), (appBaseAddr + 0x4C6094), 8);
		WriteCall((func.sect0 + 0xB0), (appBaseAddr + 0x1BA120));
		WriteCall((func.sect0 + 0xB7), (appBaseAddr + 0x1BB880));
		WriteAddress((func.sect0 + 0xC8), (appBaseAddr + 0xCF2D90), 7);
		WriteCall((func.sect0 + 0xCF), (appBaseAddr + 0x326960));
		WriteCall((func.sect0 + 0x150), (appBaseAddr + 0x1BBCD0));
		WriteCall((func.sect0 + 0x158), (appBaseAddr + 0x1BB7A0));









		Log("func_1BCA0 whatever %llX", func.addr);




	}



















	
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
void System_Actor_ToggleModelFixes(bool enable)
{
	LogFunction(enable);
	if (enable)
	{
		vp_memset((appBaseAddr + 0x215577), 0x90, 5); // Disable Object Partition Update Dante
	}
	else
	{
		WriteCall((appBaseAddr + 0x215577), (appBaseAddr + 0x2169F0));
	}
}
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
