#include "Actor.h"

bool System_Actor_enableArrayExtension    = false;
bool System_Actor_enableCreateActor       = false;
bool System_Actor_enableUpdateActor       = false;
bool System_Actor_enableDoppelgangerFixes = false;

byte8 * actorBaseAddr[MAX_ACTOR] = {};

typedef byte8 *(* InternalCreateActor_t)(uint8 character, uint8 actor, bool isDoppelganger);

InternalCreateActor_t InternalCreateActor = 0;
UpdateDevilForm_t     UpdateDevilForm     = 0;
UpdateFlux_t          UpdateFlux          = 0;
Relax_t               Relax               = 0;

byte * OnUpdate[2] = {};

byte8 * CreateActorOneProxy = 0;
byte8 * UpdateActorProxy    = 0;

ApplyColor_t ApplyColor = 0;

uint8 GetActorId(byte * baseAddr)
{
	for (uint8 actor = 0; actor < MAX_ACTOR; actor++)
	{
		if (actorBaseAddr[actor] == baseAddr)
		{
			return actor;
		}
	}
	return 0;
}

uint8 GetActorCount()
{
	uint8 count = 0;
	for (uint8 actor = 0; actor < MAX_ACTOR; actor++)
	{
		if (!actorBaseAddr[actor])
		{
			break;
		}
		count++;
	}
	return count;
}

static void CreateActors()
{
	LogFunction();
	if (Config.Game.Multiplayer.enable)
	{
		for (uint8 index = 0; index < Config.Game.Multiplayer.actorCount; index++)
		{
			uint8 actor = (ACTOR_TWO + index);
			auto & character = Config.Game.Multiplayer.character[index];
			InternalCreateActor(character, actor, false);
		}
	}
	else
	{
		uint8 & characterActorOne = *(uint8 *)(actorBaseAddr[ACTOR_ONE] + 0x78);
		uint8 character = (Config.Game.Doppelganger.enable) ? Config.Game.Doppelganger.character : characterActorOne;
		InternalCreateActor(character, ACTOR_TWO, false);
	}
}

static void CreateActorOne(byte8 * baseAddr)
{
	LogFunction(baseAddr);
	memset(actorBaseAddr, 0, sizeof(actorBaseAddr));
	actorBaseAddr[ACTOR_ONE] = baseAddr;
	CreateActors();
}

struct FileItemHelper
{
	uint16 fileItemId;
	uint16 stringItemId;
	uint16 cacheFileId;
	void Update()
	{
		FILE_ITEM   * fileItemAddr   = (FILE_ITEM   *)(appBaseAddr + 0xC99D30); // dmc3.exe+1DF64B - 48 8D 0D DEA6AB00 - lea rcx,[dmc3.exe+C99D30]
		STRING_ITEM * stringItemAddr = (STRING_ITEM *)(appBaseAddr + 0x5B08C0); // dmc3.exe+1B8F9A - 48 8D 05 CF793F00 - lea rax,[dmc3.exe+5B0970]

		FILE_ITEM   & fileItem   = fileItemAddr[fileItemId];
		STRING_ITEM & stringItem = stringItemAddr[stringItemId];

		memset(&fileItem, 0, sizeof(FILE_ITEM));

		fileItem.status     = FILE_ITEM_READY;
		fileItem.stringItem = &stringItem;
		fileItem.file       = cacheFile[cacheFileId];
	};
};

FileItemHelper fileItemHelperDante[] =
{
	{ 0  , 0 , pl000 },
	{ 200, 13, pl005 },
	{ 201, 14, pl006 },
	{ 202, 15, pl007 },
	{ 203, 16, pl008 },
	{ 204, 17, pl009 },
	{ 205, 18, pl017 },
};

FileItemHelper fileItemHelperBob[] =
{
	{ 1  , 6 , pl001 },
	{ 207, 19, pl010 },
};

FileItemHelper fileItemHelperLady[] =
{
	{ 2, 7, pl002 },
};

FileItemHelper fileItemHelperVergil[] =
{
	{ 3  , 8 , pl021 },
	{ 221, 21, pl010 },
	{ 222, 22, pl014 },
	{ 223, 23, pl025 },
};

FileItemHelper * fileItemHelper[] =
{
	fileItemHelperDante,
	fileItemHelperBob,
	fileItemHelperLady,
	fileItemHelperVergil,
};

uint8 fileItemHelperCount[] =
{
	countof(fileItemHelperDante),
	countof(fileItemHelperBob),
	countof(fileItemHelperLady),
	countof(fileItemHelperVergil),
};

struct CostumeHelper
{
	uint16 stringItemId;
	uint16 cacheFileId;
};

static CostumeHelper costumeHelperDante[] =
{
	{ 0, pl000 },
	{ 1, pl011 },
	{ 2, pl013 },
	{ 3, pl015 },
	{ 4, pl016 },
	{ 5, pl018 },
	{ 2, pl013 },
	{ 5, pl018 },
};

static CostumeHelper costumeHelperBob[] =
{
	{ 6, pl001 },
};

static CostumeHelper costumeHelperLady[] =
{
	{ 7, pl002 },
};

static CostumeHelper costumeHelperVergil[] =
{
	{ 8 , pl021 },
	{ 9 , pl023 },
	{ 8 , pl021 },
	{ 10, pl026 },
	{ 10, pl026 },
};

static CostumeHelper * costumeHelper[] =
{
	costumeHelperDante,
	costumeHelperBob,
	costumeHelperLady,
	costumeHelperVergil,
};

static uint8 costumeHelperCount[] =
{
	countof(costumeHelperDante),
	countof(costumeHelperBob),
	countof(costumeHelperLady),
	countof(costumeHelperVergil),
};

static void UpdateCostume(byte8 * baseAddr)
{
	uint8 actor = GetActorId(baseAddr);
	uint8 character = *(uint8 *)(baseAddr + 0x78);
	if (character >= MAX_CHAR)
	{
		character = 0;
	}
	uint8 & costume = *(uint8 *)(baseAddr + 0x3E9E);
	if (Config.Game.Multiplayer.enable && (actor != ACTOR_ONE))
	{
		costume = Config.Game.Multiplayer.costume[(actor - 1)];
	}
	if (costume >= costumeHelperCount[character])
	{
		costume = 0;
	}
	fileItemHelper[character][0].stringItemId = costumeHelper[character][costume].stringItemId;
	fileItemHelper[character][0].cacheFileId  = costumeHelper[character][costume].cacheFileId;
}

static void UpdateBaseAddress(byte8 * baseAddr)
{
	uint8 actor = GetActorId(baseAddr);
	byte8 ** data = *(byte8 ***)(appBaseAddr + 0xC90E28);
	if (!data)
	{
		return;
	}
	switch (actor)
	{
	case ACTOR_ONE:
		data[3] = baseAddr;
		break;
	case ACTOR_TWO:
		data[4] = baseAddr;
		break;
	}
}

static void UpdateActor(byte8 * baseAddr)
{
	Log("%s %llX", FUNC_NAME, baseAddr);

	uint8 character = *(uint8 *)(baseAddr + 0x78);
	if (character >= MAX_CHAR)
	{
		character = 0;
	}

	// Update File Items
	{
		UpdateCostume(baseAddr);
		auto & count = fileItemHelperCount[character];
		for (uint8 index = 0; index < count; index++)
		{
			fileItemHelper[character][index].Update();
		}
	}

	UpdateBaseAddress(baseAddr);














	LogFunctionEnd();
}

struct MotionHelper
{
	uint8 motionId;
	uint16 cacheFileId;
};

static MotionHelper motionHelperDante[] =
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

static MotionHelper motionHelperBob[] =
{
	{ MOT_BOB_BASE       , pl001_00_0  },
	{ MOT_BOB_DAMAGE     , pl001_00_1  },
	{ MOT_BOB_TAUNTS     , pl001_00_2  },
	{ MOT_BOB_MELEE_STYLE, pl001_00_31 },
};

static MotionHelper motionHelperLady[] =
{
	{ MOT_LADY_BASE      , pl002_00_0  },
	{ MOT_LADY_DAMAGE    , pl002_00_1  },
	{ MOT_LADY_TAUNTS    , pl002_00_2  },
	{ MOT_LADY_KALINA_ANN, pl000_00_12 },
};

static MotionHelper motionHelperVergil[] =
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

static MotionHelper * motionHelper[] =
{
	motionHelperDante,
	motionHelperBob,
	motionHelperLady,
	motionHelperVergil,
};

static uint8 motionHelperCount[] =
{
	countof(motionHelperDante),
	countof(motionHelperBob),
	countof(motionHelperLady),
	countof(motionHelperVergil),
};

static void UpdateMotion(byte8 * baseAddr)
{
	LogFunction(baseAddr);
	uint8 character = *(uint8 *)(baseAddr + 0x78);
	if (character >= MAX_CHAR)
	{
		character = 0;
	}
	byte ** motion = (byte **)(baseAddr + 0x38A0);
	memset(motion, 0, (MAX_MOT * 8));
	auto & count = motionHelperCount[character];
	for (uint8 index = 0; index < count; index++)
	{
		auto & motionId    = motionHelper[character][index].motionId;
		auto & cacheFileId = motionHelper[character][index].cacheFileId;

		motion[motionId] = cacheFile[cacheFileId];
	}
}

void ResetDevilModel()
{
	LogFunction();
	// Loop Count
	{
		byte buffer[] =
		{
			0x0F, 0x45, 0xC1, //cmovne eax,ecx
		};
		vp_memcpy((appBaseAddr + 0x2130E5), buffer, sizeof(buffer));
	}
	// Sparda
	{
		byte buffer[] =
		{
			0x0F, 0x85, 0xCB, 0x03, 0x00, 0x00, //jne dmc3.exe+21353F
		};
		vp_memcpy((appBaseAddr + 0x21316E), buffer, sizeof(buffer));
	}
	// Other Models
	{
		byte buffer[] =
		{
			0x41, 0x0F, 0xBE, 0x0C, 0x0C, //movsx ecx,byte ptr [r12+rcx]
		};
		vp_memcpy((appBaseAddr + 0x21353F), buffer, sizeof(buffer));
	}
	// Aura
	WriteAddress((appBaseAddr + 0x1F9393), (appBaseAddr + 0x1F93AB), 2);
	WriteAddress((appBaseAddr + 0x1F9433), (appBaseAddr + 0x1F9440), 2);
	Write<uint8>((appBaseAddr + 0x1F943B), DEVIL_DANTE_SPARDA);
}

void UpdateDevilModel(uint8 model)
{
	LogFunction();
	ResetDevilModel();
	vp_memset((appBaseAddr + 0x2130E5), 0x90, 3);
	if (model == DEVIL_DANTE_SPARDA)
	{
		WriteAddress((appBaseAddr + 0x21316E), (appBaseAddr + 0x213174), 6);
	}
	else
	{
		Write<word>((appBaseAddr + 0x21316E), 0xE990);
		{
			byte buffer[] =
			{
				0x31, 0xC9, //xor ecx,ecx
				0xB1, 0x00, //mov cl,model
				0x90,       //nop
			};
			vp_memcpy((appBaseAddr + 0x21353F), buffer, sizeof(buffer));
			Write<uint8>((appBaseAddr + 0x213542), model);
		}
	}
	WriteAddress((appBaseAddr + 0x1F9393), (appBaseAddr + 0x1F9395), 2);
	WriteAddress((appBaseAddr + 0x1F9433), (appBaseAddr + 0x1F9435), 2);
	Write<uint8>((appBaseAddr + 0x1F943B), model);
}

//bool ApplyShading(byte8 * baseAddr, uint8 shade)
//{
//
//	return false;
//
//	uint8 & character = *(uint8 *)(baseAddr + 0x78);
//	if (Config.Game.Multiplayer.enable)
//	{
//		return false;
//	}
//	if (baseAddr == actorBaseAddr[ACTOR_ONE])
//	{
//		return false;
//	}
//	if (character == CHAR_BOB)
//	{
//		return false;
//	}
//	return true;
//}



void UpdateActorAttributes(byte8 * baseAddr)
{
	LogFunction(baseAddr);
	auto & character      = *(uint8  *)(baseAddr + 0x78  );
	auto & isDoppelganger = *(uint32 *)(baseAddr + 0x11C );
	auto & visible        = *(uint32 *)(baseAddr + 0x120 );
	auto & shadow         = *(uint32 *)(baseAddr + 0x3A18);
	if (Config.Game.Multiplayer.enable)
	{
		return;
	}
	if (baseAddr == actorBaseAddr[ACTOR_ONE])
	{
		return;
	}
	if (character == CHAR_BOB)
	{
		return;
	}

	ApplyColor(baseAddr, 6, 0);

	



	isDoppelganger = 1;
	visible = 0;
	shadow = 0;
}













void System_Actor_Init()
{
	LogFunction();
	{
		byte sect1[] =
		{
			0x48, 0x31, 0xC0,                                           //xor rax,rax
			0x84, 0xD2,                                                 //test dl,dl
			0x74, 0x77,                                                 //je short
			0x48, 0xBB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rbx,actorBaseAddr
			0x48, 0x0F, 0xB6, 0xF1,                                     //movzx rsi,cl
			0x48, 0x0F, 0xB6, 0xFA,                                     //movzx rdi,dl
			0x4D, 0x0F, 0xB6, 0xE0,                                     //movzx r12,r8l
			0x48, 0x8B, 0x4C, 0xFB, 0xF8,                               //mov rcx,[rbx+rdi*8-08]
			0x48, 0x85, 0xC9,                                           //test rcx,rcx
			0x74, 0x57,                                                 //je short
			0x48, 0x8D, 0x89, 0x10, 0x64, 0x00, 0x00,                   //lea rcx,[rcx+00006410]
			0xBA, 0x3C, 0x00, 0x00, 0x00,                               //mov edx,0000003C
			0xE8, 0x00, 0x00, 0x00, 0x00,                               //call dmc3.exe+2EE060
			0x8B, 0xCE,                                                 //mov ecx,esi
			0x8B, 0xD7,                                                 //mov edx,edi
			0x45, 0x8B, 0xC4,                                           //mov r8d,r12d
			0xE8, 0x00, 0x00, 0x00, 0x00,                               //call dmc3.exe+1DE820
			0x4C, 0x8B, 0xE8,                                           //mov r13,rax
			0x48, 0x89, 0x04, 0xFB,                                     //mov [rbx+rdi*8],rax
			0x48, 0x8B, 0xCB,                                           //mov rcx,rbx
			0x8B, 0xD7,                                                 //mov edx,edi
			0xE8, 0x00, 0x00, 0x00, 0x00,                               //call dmc3.exe+1BB390
			0x49, 0x8B, 0xCD,                                           //mov rcx,r13
			0x48, 0x8B, 0x15, 0x00, 0x00, 0x00, 0x00,                   //mov rdx,[dmc3.exe+C90E28]
			0x48, 0x8B, 0x52, 0x08,                                     //mov rdx,[rdx+08]
			0x48, 0x81, 0xC2, 0x6C, 0x01, 0x00, 0x00,                   //add rdx,0000016C
			0xE8, 0x00, 0x00, 0x00, 0x00,                               //call dmc3.exe+1DF240
			0x48, 0x8B, 0x4C, 0xFB, 0xF8,                               //mov rcx,[rbx+rdi*8-08]
			0x4C, 0x89, 0xA9, 0x78, 0x64, 0x00, 0x00,                   //mov [rcx+00006478],r13
			0x49, 0x8B, 0xC5,                                           //mov rax,r13
		};
		FUNC func = CreateFunction(0, 0, true, false, 0, sizeof(sect1));
		memcpy(func.sect1, sect1, sizeof(sect1));
		*(byte8 ***)(func.sect1 + 9) = actorBaseAddr;
		WriteCall((func.sect1 + 0x33), (appBaseAddr + 0x2EE060));
		WriteCall((func.sect1 + 0x3F), (appBaseAddr + 0x1DE820));
		WriteCall((func.sect1 + 0x50), (appBaseAddr + 0x1BB390));
		WriteAddress((func.sect1 + 0x58), (appBaseAddr + 0xC90E28), 7);
		WriteCall((func.sect1 + 0x6A), (appBaseAddr + 0x1DF240));
		InternalCreateActor = (InternalCreateActor_t)func.addr;
	}
	{
		FUNC func = CreateFunction((appBaseAddr + 0x1FB020), 0);
		UpdateDevilForm = (UpdateDevilForm_t)func.addr;
	}
	{
		FUNC func = CreateFunction((appBaseAddr + 0x1F94D0), 0);
		UpdateFlux = (UpdateFlux_t)func.addr;
	}
	{
		byte sect1[] =
		{
			0x48, 0x8B, 0xD9,                         //mov rbx,rcx
			0x31, 0xD2,                               //xor edx,edx
			0xE8, 0x00, 0x00, 0x00, 0x00,             //call dmc3.exe+1F92C0
			0x48, 0x8B, 0x83, 0xE8, 0x3D, 0x00, 0x00, //mov rax,[rbx+00003DE8]
			0x8B, 0x80, 0xF0, 0x01, 0x00, 0x00,       //mov eax,[rax+000001F0]
			0x89, 0x83, 0xC4, 0x3E, 0x00, 0x00,       //mov [rbx+00003EC4],eax
			0x31, 0xD2,                               //xor edx,edx
			0x48, 0x8B, 0xCB,                         //mov rcx,rbx
			0xE8, 0x00, 0x00, 0x00, 0x00,             //call dmc3.exe+1F97F0
		};
		FUNC func = CreateFunction(0, 0, true, true, 0, sizeof(sect1));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteCall((func.sect1 + 5), (appBaseAddr + 0x1F92C0));
		WriteCall((func.sect1 + 0x22), (appBaseAddr + 0x1F97F0));
		Relax = (Relax_t)func.addr;
	}
	{
		byte sect0[] =
		{
			0x49, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov r8,actorBaseAddr
			0x4D, 0x8B, 0x04, 0xC0,                                     //mov r8,[r8+rax*8]
			0x4D, 0x8B, 0xD0,                                           //mov r10,r8
		};
		FUNC func = CreateFunction(0, (appBaseAddr + 0x1BA572), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*(byte ***)(func.sect0 + 2) = actorBaseAddr;
		OnUpdate[0] = func.addr;
	}
	{
		byte sect0[] =
		{
			0x48, 0xBD, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rbp,actorBaseAddr
			0x4A, 0x8B, 0x6C, 0xC5, 0x00,                               //mov rbp,[rbp+r8*8+00]
		};
		FUNC func = CreateFunction(0, (appBaseAddr + 0x1BC0CA), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*(byte ***)(func.sect0 + 2) = actorBaseAddr;
		OnUpdate[1] = func.addr;
	}
	{
		byte8 sect1[] =
		{
			0x48, 0x8B, 0xC8, //mov rcx,rax
		};
		byte sect2[] =
		{
			0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc3.exe+1BB470
		};
		FUNC func = CreateFunction(CreateActorOne, (appBaseAddr + 0x23C79F), true, true, 0, sizeof(sect1), sizeof(sect2));
		memcpy(func.sect1, sect1, sizeof(sect1));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteCall(func.sect2, (appBaseAddr + 0x1BB470));
		CreateActorOneProxy = func.addr;
	}
	{
		byte sect2[] =
		{
			0xFF, 0x90, 0x80, 0x00, 0x00, 0x00, //call qword ptr [rax+00000080]
		};
		FUNC func = CreateFunction(UpdateActor, (appBaseAddr + 0x1DF2CA), true, true, 0, 0, sizeof(sect2));
		memcpy(func.sect2, sect2, sizeof(sect2));
		UpdateActorProxy = func.addr;
	}
	{
		byte sect1[] =
		{
			0x48, 0x8B, 0xCB, //mov rcx,rbx
		};
		FUNC func = CreateFunction(UpdateMotion, (appBaseAddr + 0x1DF2CA), true, true, 0, sizeof(sect1));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteJump((UpdateActorProxy + 0x52), func.addr);
	}






	{
		FUNC func = CreateFunction((appBaseAddr + 0x1FCB10));
		ApplyColor = (ApplyColor_t)func.addr;
	}


	{
		byte8 sect1[] =
		{
			0x48, 0x8B, 0xCB, //mov rcx,rbx
		};
		byte8 sect2[] =
		{
			0x48, 0x8B, 0x5C, 0x24, 0x58, //mov rbx,[rsp+58]
		};
		FUNC func = CreateFunction(UpdateActorAttributes, (appBaseAddr + 0x1F7D8C), true, true, 0, sizeof(sect1), sizeof(sect2));
		memcpy(func.sect1, sect1, sizeof(sect1));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteJump((appBaseAddr + 0x1F7D87), func.addr);
		//dmc3.exe+1F7D87 - 48 8B 5C 24 58        - mov rbx,[rsp+58]
		//dmc3.exe+1F7D8C - 48 83 C4 40           - add rsp,40
	}





	//{
		//byte8 sect0[] =
		//{
		//	0x50, //push rax
		//};
		//byte8 sect2[] =
		//{
		//	0x84, 0xC0,                   //test al,al
		//	0x74, 0x05,                   //je short
		//	0xBA, 0x06, 0x00, 0x00, 0x00, //mov edx,00000006
		//	0x58,                         //pop rax
		//	0x48, 0x89, 0x5C, 0x24, 0x18, //mov [rsp+18],rbx
		//};
		//FUNC func = CreateFunction(ApplyShading, (appBaseAddr + 0x1FCB15), true, false, sizeof(sect0), 0, sizeof(sect2));
		//memcpy(func.sect0, sect0, sizeof(sect0));
		//memcpy(func.sect2, sect2, sizeof(sect2));
		//WriteJump((appBaseAddr + 0x1FCB10), func.addr);
	//}
}

void System_Actor_ToggleArrayExtension(bool enable)
{
	LogFunction(enable);
	System_Actor_enableArrayExtension = enable;
	if (enable)
	{
		// OnUpdate
		WriteJump((appBaseAddr + 0x1BA569), OnUpdate[0]);
		vp_memset((appBaseAddr + 0x1BA5C5), 0x90, 4);
		Write<byte8>((appBaseAddr + 0x1BA5C9), 0x45);
		Write<byte8>((appBaseAddr + 0x1BA5CB), 0x9A);
		WriteJump((appBaseAddr + 0x1BC0C5), OnUpdate[1]);
		// OnEvent
		Write<byte8>((appBaseAddr + 0x1BB397), 0x1C);
		Write<byte8>((appBaseAddr + 0x1BB399), 0x90);
		Write<byte16>((appBaseAddr + 0x1BB408), 0x9003);
		Write<byte16>((appBaseAddr + 0x1BB457), 0x9003);
	}
	else
	{
		{
			byte buffer[] =
			{
				0x4C, 0x8B, 0x44, 0xC1, 0x18, //mov r8,[rcx+rax*8+18]
			};
			vp_memcpy((appBaseAddr + 0x1BA569), buffer, sizeof(buffer));
		}
		{
			byte buffer[] =
			{
				0x49, 0x8B, 0x42, 0x18, //mov rax,[r10+18]
			};
			vp_memcpy((appBaseAddr + 0x1BA5C5), buffer, sizeof(buffer));
		}
		Write<byte8>((appBaseAddr + 0x1BA5C9), 0x44);
		Write<byte8>((appBaseAddr + 0x1BA5CB), 0x98);
		{
			byte buffer[] =
			{
				0x4A, 0x8B, 0x6C, 0xC0, 0x18, //mov rbp,[rax+r8*8+18]
			};
			vp_memcpy((appBaseAddr + 0x1BC0C5), buffer, sizeof(buffer));
		}
		Write<byte8>((appBaseAddr + 0x1BB397), 0x5C);
		Write<byte8>((appBaseAddr + 0x1BB399), 0x18);
		Write<byte16>((appBaseAddr + 0x1BB408), 0x1843);
		Write<byte16>((appBaseAddr + 0x1BB457), 0x1843);
	}
}

void System_Actor_ToggleCreateActorOne(bool enable)
{
	LogFunction(enable);
	System_Actor_enableCreateActor = enable;
	if (enable)
	{
		WriteJump((appBaseAddr + 0x23C79A), CreateActorOneProxy);
	}
	else
	{
		WriteCall((appBaseAddr + 0x23C79A), (appBaseAddr + 0x1BB470));
	}
}

void System_Actor_ToggleUpdateActor(bool enable)
{
	LogFunction(enable);
	System_Actor_enableUpdateActor = enable;
	if (enable)
	{
		WriteJump((appBaseAddr + 0x1DF2C4), UpdateActorProxy, 1);
	}
	else
	{
		byte buffer[] =
		{
			0xFF, 0x90, 0x80, 0x00, 0x00, 0x00, //call qword ptr [rax+00000080]
		};
		vp_memcpy((appBaseAddr + 0x1DF2C4), buffer, sizeof(buffer));
	}
}

void System_Actor_ToggleDoppelgangerFixes(bool enable)
{
	LogFunction(enable);
	System_Actor_enableDoppelgangerFixes = enable;
	if (enable)
	{
		vp_memset((appBaseAddr + 0x1DF291), 0x90, 7); // Disable linked actor base address reset.
		// Make IsDoppelganger check always return false.
		{
			byte * addr = (appBaseAddr + 0x1F78B0);
			vp_memset(addr, 0x90, 7);
			byte buffer[] =
			{
				0x30, 0xC0, //xor al,al
				0xC3,       //ret
			};
			vp_memcpy(addr, buffer, sizeof(buffer));
		}
		Write<byte16>((appBaseAddr + 0x2134A3), 0xE990); // Skip clone creation.
		Write<byte8>((appBaseAddr + 0x1F92E0), 0x00); // Devil Form: Disable Doppelganger check.
		Write<byte8>((appBaseAddr + 0x1F92F8), 0xEB); // Devil Form: Disable isDoppelganger check.
	}
	else
	{
		{
			byte buffer[] =
			{
				0x48, 0x89, 0x81, 0x78, 0x64, 0x00, 0x00, //mov [rcx+00006478],rax
			};
			vp_memcpy((appBaseAddr + 0x1DF291), buffer, sizeof(buffer));
		}
		{
			byte buffer[] =
			{
				0x83, 0xB9, 0x1C, 0x01, 0x00, 0x00, 0x01, //cmp dword ptr [rcx+0000011C],01
			};
			vp_memcpy((appBaseAddr + 0x1F78B0), buffer, sizeof(buffer));
		}
		Write<byte16>((appBaseAddr + 0x2134A3), 0x840F);
		Write<byte8>((appBaseAddr + 0x1F92E0), 0x0D);
		Write<byte8>((appBaseAddr + 0x1F92F8), 0x75);
	}
}
