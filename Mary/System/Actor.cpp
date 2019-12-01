#include "Actor.h"

#pragma region Global Stuff

bool System_Actor_enableArrayExtension    = false;
bool System_Actor_enableCreateActor       = false;
bool System_Actor_enableUpdateActor       = false;
bool System_Actor_enableDoppelgangerFixes = false;

byte * actorBaseAddr[MAX_ACTOR] = {};
bool updateModelAttributes[MAX_ACTOR] = {};

typedef void(* InternalCreateActor_t)(uint8, uint8);

InternalCreateActor_t InternalCreateActor = 0;
UpdateDevilForm_t     UpdateDevilForm     = 0;
UpdateFlux_t          UpdateFlux          = 0;
Relax_t               Relax               = 0;

byte * OnUpdate[2] = {};
byte * CreateActorProxy = 0;
byte * UpdateActorProxy = 0;

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

// @Check: Run directly after ACTOR_ONE has been created.

static void CreateActor()
{
	LogFunction();










	// Update base addresses.

	memset(actorBaseAddr, 0, sizeof(actorBaseAddr));
	{
		byte * addr = *(byte **)(appBaseAddr + 0xC90E28);
		if (!addr)
		{
			goto sect0;
		}

		//byte * nativeActorBaseAddr 

		//byte * & baseAddr

		
		byte ** baseAddr = (byte **)(addr + 0x18);

		actorBaseAddr[ACTOR_ONE] = baseAddr[ACTOR_ONE];








		actorBaseAddr[ACTOR_ONE] = *(byte **)(addr + 0x18);
	}
	sect0:





























	if (Config.Game.Multiplayer.enable)
	{
		for (uint8 actor = 0; actor < Config.Game.Multiplayer.actorCount; actor++)
		{
			InternalCreateActor((ACTOR_TWO + actor), Config.Game.Multiplayer.character[actor]);
		}
	}
	else
	{

		// @Todo: Check dependency chain.

		// @Todo: Make reference.
		uint8 character = *(uint8 *)(actorBaseAddr[ACTOR_ONE] + 0x78);
		if (Config.Game.StyleSwitcher.enable || (character == CHAR_DANTE))
		{
			InternalCreateActor(ACTOR_TWO, (Config.Game.Doppelganger.enable) ? Config.Game.Doppelganger.character : character);
		}
	}






}











// @Todo: Jesus, simplify!


static void UpdateActor(byte * baseAddr)
{
	//LogFunction();



	Log("%s %llX", FUNC_NAME, baseAddr);


	for (uint8 actor = 0; actor < MAX_ACTOR; actor++)
	{
		Log("actorBaseAddr[%u] %llX", actor, actorBaseAddr[actor]);
	}










	uint8 actorId = GetActorId(baseAddr);
	uint8 character = *(uint8 *)(baseAddr + 0x78);
	if (character >= MAX_CHAR)
	{
		character = 0;
	}
	uint8 & costume = *(uint8 *)(baseAddr + 0x3E9E);
	// Update File Structs
	byte * structAddr[MAX_CHAR][MAX_BODY_COUNT] =
	{
		{                                        // Dante
			( appBaseAddr + 0xC99D30          ), // Base
			( appBaseAddr + 0xC99D30 + 0x3840 ), // Devil Rebellion
			( appBaseAddr + 0xC99D30 + 0x3888 ), // Devil Cerberus
			( appBaseAddr + 0xC99D30 + 0x38D0 ), // Devil Agni & Rudra
			( appBaseAddr + 0xC99D30 + 0x3918 ), // Devil Nevan
			( appBaseAddr + 0xC99D30 + 0x3960 ), // Devil Beowulf
			( appBaseAddr + 0xC99D30 + 0x39A8 ), // Devil Sparda
		},
		{                                        // Bob
			( appBaseAddr + 0xC99D30 + 0x48   ), // Base
			( appBaseAddr + 0xC99D30 + 0x3A38 ), // Devil Yamato
		},
		{                                        // Lady
			( appBaseAddr + 0xC99D30 + 0x90   ), // Base
		},
		{                                        // Vergil
			( appBaseAddr + 0xC99D30 + 0xD8   ), // Base
			( appBaseAddr + 0xC99D30 + 0x3E28 ), // Devil Yamato
			( appBaseAddr + 0xC99D30 + 0x3E70 ), // Devil Beowulf
			( appBaseAddr + 0xC99D30 + 0x3EB8 ), // Nero Angelo
		},
	};
	byte * stringAddr[MAX_CHAR][MAX_BODY_COUNT] =
	{
		{
			(appBaseAddr + 0x5B08C0), // obj\pl000.pac
			(appBaseAddr + 0x5B0990), // obj\pl005.pac
			(appBaseAddr + 0x5B09A0), // obj\pl006.pac
			(appBaseAddr + 0x5B09B0), // obj\pl007.pac
			(appBaseAddr + 0x5B09C0), // obj\pl008.pac
			(appBaseAddr + 0x5B09D0), // obj\pl009.pac
			(appBaseAddr + 0x5B09E0), // obj\pl017.pac
		},
		{
			(appBaseAddr + 0x5B0920), // obj\pl001.pac
			(appBaseAddr + 0x5B09F0), // obj\pl010.pac
		},
		{
			(appBaseAddr + 0x5B0930), // obj\pl002.pac
		},
		{
			(appBaseAddr + 0x5B0940), // obj\pl021.pac
			(appBaseAddr + 0x5B0A10), // obj\pl010.pac
			(appBaseAddr + 0x5B0A20), // obj\pl014.pac
			(appBaseAddr + 0x5B0A30), // obj\pl025.pac
		},
	};
	byte * fileAddr[MAX_CHAR][MAX_BODY_COUNT] =
	{
		{
			cacheFile[pl000],
			cacheFile[pl005],
			cacheFile[pl006],
			cacheFile[pl007],
			cacheFile[pl008],
			cacheFile[pl009],
			cacheFile[pl017],
		},
		{
			cacheFile[pl001],
			cacheFile[pl010],
		},
		{
			cacheFile[pl002],
		},
		{
			cacheFile[pl021],
			cacheFile[pl010],
			cacheFile[pl014],
			cacheFile[pl025],
		},
	};
	// Set Costume
	{
		if (Config.Game.Multiplayer.enable && (actorId != ACTOR_ONE))
		{
			costume = Config.Game.Multiplayer.costume[(actorId - 1)];
		}
		uint8 count[] =
		{
			COSTUME_COUNT_DANTE,
			COSTUME_COUNT_BOB,
			COSTUME_COUNT_LADY,
			COSTUME_COUNT_VERGIL,
		};
		if (costume >= count[character])
		{
			costume = 0;
		}
		byte * costumeStringAddr[MAX_CHAR][MAX_COSTUME_COUNT] =
		{
			{
				(appBaseAddr + 0x5B08C0), // obj\pl000.pac
				(appBaseAddr + 0x5B08D0), // obj\pl011.pac
				(appBaseAddr + 0x5B08E0), // obj\pl013.pac
				(appBaseAddr + 0x5B08F0), // obj\pl015.pac
				(appBaseAddr + 0x5B0900), // obj\pl016.pac
				(appBaseAddr + 0x5B0910), // obj\pl018.pac
				(appBaseAddr + 0x5B08E0), // obj\pl013.pac
				(appBaseAddr + 0x5B0910), // obj\pl018.pac
			},
			{
				(appBaseAddr + 0x5B0920), // obj\pl001.pac
			},
			{
				(appBaseAddr + 0x5B0930), // obj\pl002.pac
			},
			{
				(appBaseAddr + 0x5B0940), // obj\pl021.pac
				(appBaseAddr + 0x5B0950), // obj\pl023.pac
				(appBaseAddr + 0x5B0940), // obj\pl021.pac
				(appBaseAddr + 0x5B0960), // obj\pl026.pac
				(appBaseAddr + 0x5B0960), // obj\pl026.pac
			},
		};
		byte * costumeFileAddr[MAX_CHAR][MAX_COSTUME_COUNT] =
		{
			{
				cacheFile[pl000],
				cacheFile[pl011],
				cacheFile[pl013],
				cacheFile[pl015],
				cacheFile[pl016],
				cacheFile[pl018],
				cacheFile[pl013],
				cacheFile[pl018],
			},
			{
				cacheFile[pl001],
			},
			{
				cacheFile[pl002],
			},
			{
				cacheFile[pl021],
				cacheFile[pl023],
				cacheFile[pl021],
				cacheFile[pl026],
				cacheFile[pl026],
			},
		};
		stringAddr[character][0] = costumeStringAddr[character][costume];
		fileAddr  [character][0] = costumeFileAddr  [character][costume];
	}
	uint8 count[] =
	{
		BODY_COUNT_DANTE,
		BODY_COUNT_BOB,
		BODY_COUNT_LADY,
		BODY_COUNT_VERGIL,
	};
	for (uint8 i = 0; i < count[character]; i++)
	{
		memset(structAddr[character][i], 0, 0x48);
		uint32   & state  = *( uint32 *  )( structAddr[character][i] + 4    );
		byte   * & string = *( byte   ** )( structAddr[character][i] + 0x18 );
		byte   * & file   = *( byte   ** )( structAddr[character][i] + 0x20 );
		state  = 3;
		string = stringAddr[character][i];
		file   = fileAddr  [character][i];
	}










	





	UpdateHardBaseAddrStart:
	{
		byte * addr = *(byte **)(appBaseAddr + 0xC90E28);
		if (!addr)
		{
			goto UpdateHardBaseAddrEnd;
		}
		if (actorId == ACTOR_ONE)
		{
			*(byte **)(addr + 0x18) = baseAddr;
		}
		else if (actorId == ACTOR_TWO)
		{
			*(byte **)(addr + 0x20) = baseAddr;
		}
	}
	UpdateHardBaseAddrEnd:












	Log("%s reached end!", FUNC_NAME);
}

static void UpdateMotion(byte * baseAddr)
{
	LogFunction();
	uint8 character = *(uint8 *)(baseAddr + 0x78);
	if (character >= MAX_CHAR)
	{
		character = 0;
	}
	byte ** motionAddr = (byte **)(baseAddr + 0x38A0);
	memset(motionAddr, 0, (MAX_MOT * 8));
	byte * fileAddr[MAX_CHAR][MAX_MOT] =
	{
		{
			cacheFile[pl000_00_0],
			cacheFile[pl000_00_1],
			cacheFile[pl000_00_2],
			cacheFile[pl000_00_3],
			cacheFile[pl000_00_4],
			cacheFile[pl000_00_5],
			cacheFile[pl000_00_6],
			cacheFile[pl000_00_7],
			cacheFile[pl000_00_8],
			cacheFile[pl000_00_9],
			cacheFile[pl000_00_10],
			cacheFile[pl000_00_11],
			cacheFile[pl000_00_12],
			cacheFile[pl000_00_13],
			cacheFile[pl000_00_14],
			cacheFile[pl000_00_15],
			cacheFile[pl000_00_16],
			cacheFile[pl000_00_17],
			cacheFile[pl000_00_18],
			cacheFile[pl000_00_19],
			cacheFile[pl000_00_20],
			cacheFile[pl000_00_21],
			cacheFile[pl000_00_22],
			cacheFile[pl000_00_23],
			cacheFile[pl000_00_24],
			cacheFile[pl000_00_25],
			cacheFile[pl000_00_26],
		},
		{
			cacheFile[pl001_00_0],
			cacheFile[pl001_00_1],
			cacheFile[pl001_00_2],
			cacheFile[pl001_00_31],
		},
		{
			cacheFile[pl002_00_0],
			cacheFile[pl002_00_1],
			cacheFile[pl002_00_2],
			cacheFile[pl000_00_12],
		},
		{
			cacheFile[pl021_00_0],
			cacheFile[pl021_00_1],
			cacheFile[pl021_00_2],
			cacheFile[pl021_00_3],
			cacheFile[pl021_00_4],
			cacheFile[pl021_00_5],
			cacheFile[pl021_00_6],
			cacheFile[pl021_00_7],
			cacheFile[pl021_00_8],
			cacheFile[pl021_00_9],
		},
	};
	uint8 id[MAX_CHAR][MAX_MOT] =
	{
		{
			MOT_DANTE_BASE,
			MOT_DANTE_DAMAGE,
			MOT_DANTE_TAUNTS,
			MOT_DANTE_REBELLION,
			MOT_DANTE_CERBERUS,
			MOT_DANTE_AGNI_RUDRA,
			MOT_DANTE_NEVAN,
			MOT_DANTE_BEOWULF,
			MOT_DANTE_EBONY_IVORY,
			MOT_DANTE_SHOTGUN,
			MOT_DANTE_ARTEMIS,
			MOT_DANTE_SPIRAL,
			MOT_DANTE_KALINA_ANN,
			MOT_DANTE_SWORDMASTER_REBELLION,
			MOT_DANTE_SWORDMASTER_CERBERUS,
			MOT_DANTE_SWORDMASTER_AGNI_RUDRA,
			MOT_DANTE_SWORDMASTER_NEVAN,
			MOT_DANTE_SWORDMASTER_BEOWULF,
			MOT_DANTE_GUNSLINGER_EBONY_IVORY,
			MOT_DANTE_GUNSLINGER_SHOTGUN,
			MOT_DANTE_GUNSLINGER_ARTEMIS,
			MOT_DANTE_GUNSLINGER_SPIRAL,
			MOT_DANTE_GUNSLINGER_KALINA_ANN,
			MOT_DANTE_TRICKSTER,
			MOT_DANTE_ROYALGUARD,
			MOT_DANTE_QUICKSILVER,
			MOT_DANTE_DOPPELGANGER,
		},
		{
			MOT_BOB_BASE,
			MOT_BOB_DAMAGE,
			MOT_BOB_TAUNTS,
			MOT_BOB_MELEE_STYLE,
		},
		{
			MOT_LADY_BASE,
			MOT_LADY_DAMAGE,
			MOT_LADY_TAUNTS,
			MOT_LADY_KALINA_ANN,
		},
		{
			MOT_VERGIL_BASE,
			MOT_VERGIL_DAMAGE,
			MOT_VERGIL_TAUNTS,
			MOT_VERGIL_YAMATO,
			MOT_VERGIL_BEOWULF,
			MOT_VERGIL_FORCE_EDGE,
			MOT_VERGIL_DARK_SLAYER,
			MOT_VERGIL_NERO_ANGELO_YAMATO,
			MOT_VERGIL_NERO_ANGELO_BEOWULF,
			MOT_VERGIL_NERO_ANGELO_FORCE_EDGE,
		},
	};
	uint8 count[] =
	{
		MOT_DANTE,
		MOT_BOB,
		MOT_LADY,
		MOT_VERGIL,
	};
	for (uint8 i = 0; i < count[character]; i++)
	{
		motionAddr[id[character][i]] = fileAddr[character][i];
	}
	Log("%s reached end!", FUNC_NAME);














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

void System_Actor_Init()
{
	LogFunction();
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
		byte sect1[] =
		{
			0x48, 0x0F, 0xB6, 0xF1,                                     //movzx rsi,cl
			0x48, 0x0F, 0xB6, 0xFA,                                     //movzx rdi,dl
			0x49, 0xBC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov r12,actorBaseAddr
			0x49, 0x8B, 0x4C, 0xF4, 0xF8,                               //mov rcx,[r12+rsi*8-08]
			0x48, 0x8D, 0x89, 0x10, 0x64, 0x00, 0x00,                   //lea rcx,[rcx+00006410]
			0xBA, 0x3C, 0x00, 0x00, 0x00,                               //mov edx,0000003C
			0xE8, 0x00, 0x00, 0x00, 0x00,                               //call dmc3.exe+2EE060
			0x8B, 0xCF,                                                 //mov ecx,edi
			0xBA, 0x01, 0x00, 0x00, 0x00,                               //mov edx,00000001
			0x41, 0xB8, 0x01, 0x00, 0x00, 0x00,                         //mov r8d,00000001
			0xE8, 0x00, 0x00, 0x00, 0x00,                               //call dmc3.exe+1DE820
			0x49, 0x89, 0x04, 0xF4,                                     //mov [r12+rsi*8],rax
			0x49, 0x8B, 0xCC,                                           //mov rcx,r12
			0x8B, 0xD6,                                                 //mov edx,esi
			0xE8, 0x00, 0x00, 0x00, 0x00,                               //call dmc3.exe+1BB390
			0x49, 0x8B, 0x0C, 0xF4,                                     //mov rcx,[r12+rsi*8]
			0x48, 0x8B, 0x15, 0x00, 0x00, 0x00, 0x00,                   //mov rdx,[dmc3.exe+C90E28]
			0x48, 0x8B, 0x52, 0x08,                                     //mov rdx,[rdx+08]
			0x48, 0x81, 0xC2, 0x6C, 0x01, 0x00, 0x00,                   //add rdx,0000016C
			0xE8, 0x00, 0x00, 0x00, 0x00,                               //call dmc3.exe+1DF240
			0x49, 0x8B, 0x4C, 0xF4, 0xF8,                               //mov rcx,[r12+rsi*8-08]
			0x49, 0x8B, 0x04, 0xF4,                                     //mov rax,[r12+rsi*8]
			0x48, 0x89, 0x81, 0x78, 0x64, 0x00, 0x00,                   //mov [rcx+00006478],rax
		};
		FUNC func = CreateFunction(0, 0, true, true, 0, sizeof(sect1));
		memcpy(func.sect1, sect1, sizeof(sect1));
		*(byte ***)(func.sect1 + 0xA) = actorBaseAddr;
		WriteCall((func.sect1 + 0x23), (appBaseAddr + 0x2EE060));
		WriteCall((func.sect1 + 0x35), (appBaseAddr + 0x1DE820));
		WriteCall((func.sect1 + 0x43), (appBaseAddr + 0x1BB390));
		WriteAddress((func.sect1 + 0x4C), (appBaseAddr + 0xC90E28), 7);
		WriteCall((func.sect1 + 0x5E), (appBaseAddr + 0x1DF240));
		InternalCreateActor = (InternalCreateActor_t)func.addr;
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
		byte sect2[] =
		{
			0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc3.exe+1BB470
		};
		FUNC func = CreateFunction(CreateActor, (appBaseAddr + 0x23C79F), true, true, 0, 0, sizeof(sect2));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteCall(func.sect2, (appBaseAddr + 0x1BB470));
		CreateActorProxy = func.addr;
	}


	// @Todo: Write UpdateMotion first so we can use the proxy addr.



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

}


#pragma endregion










void System_Actor_ToggleArrayExtension(bool enable)
{
	LogFunctionBool(enable);
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

void System_Actor_ToggleCreateActor(bool enable)
{
	LogFunctionBool(enable);
	System_Actor_enableCreateActor = enable;
	if (enable)
	{
		WriteJump((appBaseAddr + 0x23C79A), CreateActorProxy);
	}
	else
	{
		WriteCall((appBaseAddr + 0x23C79A), (appBaseAddr + 0x1BB470));
	}
}

void System_Actor_ToggleUpdateActor(bool enable)
{
	LogFunctionBool(enable);
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
	LogFunctionBool(enable);
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
	}
}
