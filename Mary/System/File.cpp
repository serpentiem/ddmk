#include "File.h"

constexpr bool debug = false;

//byte8 * System_File_cacheFile[MAX_CACHE_FILE] = {};


CacheFile System_File_cacheFile[MAX_CACHE_FILE];





byte8 * demo_pl000_00_3 = 0;

PrivateStart;

uint32 cachePos = 0;

STRING_ITEM stringItem[countof(stringItemOff)] = {};

struct FileItemHelper
{
	uint16 fileItemId;
	uint16 cacheFileId;
	void Update()
	{
		auto & fileItem = ((FILE_ITEM *)(appBaseAddr + 0xC99D30))[fileItemId];
		memset(&fileItem, 0, sizeof(FILE_ITEM));
		fileItem.status     = FILE_ITEM_READY;
		fileItem.stringItem = &stringItem[cacheFileId];
		fileItem.file       = System_File_cacheFile[cacheFileId];
	}
};

struct MotionHelper
{
	uint8 motionId;
	uint16 cacheFileId;
};

FileItemHelper fileItemHelper[] =
{
	// Dante
	{ 0  , pl000               },
	{ 200, pl005               },
	{ 201, pl006               },
	{ 202, pl007               },
	{ 203, pl008               },
	{ 204, pl009               },
	{ 205, pl017               },
	{ 140, plwp_sword          },
	{ 141, plwp_nunchaku       },
	{ 142, plwp_2sword         },
	{ 143, plwp_guitar         },
	{ 144, plwp_fight          },
	{ 145, plwp_gun            },
	{ 146, plwp_shotgun        },
	{ 147, plwp_laser          },
	{ 148, plwp_rifle          },
	{ 149, plwp_ladygun        },
	// Bob
	{ 1  , pl001               },
	{ 207, pl010               },
	{ 169, plwp_vergilsword    },
	// Lady
	{ 2  , pl002               },
	// Vergil
	{ 3  , pl021               },
	{ 221, pl010               },
	{ 222, pl014               },
	{ 223, pl025               },
	{ 196, plwp_newvergilsword },
	{ 189, plwp_newvergilfight },
	{ 198, plwp_forceedge      },
	{ 187, plwp_nerosword      },
};

uint16 costumeMapDante[] =
{
	pl000,
	pl011,
	pl013,
	pl015,
	pl016,
	pl018,
	pl013,
	pl018,
};

uint16 costumeMapVergil[] =
{
	pl021,
	pl023,
	pl021,
	pl026,
	pl026,
};

uint16 swordMap[] =
{
	plwp_sword,
	plwp_sword2,
	plwp_sword3,
};

MotionHelper motionHelperDante[] =
{
	{ MOTION_GROUP_DANTE_BASE                  , pl000_00_0  },
	{ MOTION_GROUP_DANTE_DAMAGE                , pl000_00_1  },
	{ MOTION_GROUP_DANTE_TAUNTS                , pl000_00_2  },
	{ MOTION_GROUP_DANTE_REBELLION             , pl000_00_3  },
	{ MOTION_GROUP_DANTE_CERBERUS              , pl000_00_4  },
	{ MOTION_GROUP_DANTE_AGNI_RUDRA            , pl000_00_5  },
	{ MOTION_GROUP_DANTE_NEVAN                 , pl000_00_6  },
	{ MOTION_GROUP_DANTE_BEOWULF               , pl000_00_7  },
	{ MOTION_GROUP_DANTE_EBONY_IVORY           , pl000_00_8  },
	{ MOTION_GROUP_DANTE_SHOTGUN               , pl000_00_9  },
	{ MOTION_GROUP_DANTE_ARTEMIS               , pl000_00_10 },
	{ MOTION_GROUP_DANTE_SPIRAL                , pl000_00_11 },
	{ MOTION_GROUP_DANTE_KALINA_ANN            , pl000_00_12 },
	{ MOTION_GROUP_DANTE_SWORDMASTER_REBELLION , pl000_00_13 },
	{ MOTION_GROUP_DANTE_SWORDMASTER_CERBERUS  , pl000_00_14 },
	{ MOTION_GROUP_DANTE_SWORDMASTER_AGNI_RUDRA, pl000_00_15 },
	{ MOTION_GROUP_DANTE_SWORDMASTER_NEVAN     , pl000_00_16 },
	{ MOTION_GROUP_DANTE_SWORDMASTER_BEOWULF   , pl000_00_17 },
	{ MOTION_GROUP_DANTE_GUNSLINGER_EBONY_IVORY, pl000_00_18 },
	{ MOTION_GROUP_DANTE_GUNSLINGER_SHOTGUN    , pl000_00_19 },
	{ MOTION_GROUP_DANTE_GUNSLINGER_ARTEMIS    , pl000_00_20 },
	{ MOTION_GROUP_DANTE_GUNSLINGER_SPIRAL     , pl000_00_21 },
	{ MOTION_GROUP_DANTE_GUNSLINGER_KALINA_ANN , pl000_00_22 },
	{ MOTION_GROUP_DANTE_TRICKSTER             , pl000_00_23 },
	{ MOTION_GROUP_DANTE_ROYALGUARD            , pl000_00_24 },
	{ MOTION_GROUP_DANTE_QUICKSILVER           , pl000_00_25 },
	{ MOTION_GROUP_DANTE_DOPPELGANGER          , pl000_00_26 },
};

MotionHelper motionHelperBob[] =
{
	{ MOTION_GROUP_BOB_BASE       , pl001_00_0  },
	{ MOTION_GROUP_BOB_DAMAGE     , pl001_00_1  },
	{ MOTION_GROUP_BOB_TAUNTS     , pl001_00_2  },
	{ MOTION_GROUP_BOB_MELEE_STYLE, pl001_00_31 },
};

MotionHelper motionHelperLady[] =
{
	{ MOTION_GROUP_LADY_BASE      , pl002_00_0  },
	{ MOTION_GROUP_LADY_DAMAGE    , pl002_00_1  },
	{ MOTION_GROUP_LADY_TAUNTS    , pl002_00_2  },
	{ MOTION_GROUP_LADY_KALINA_ANN, pl000_00_12 },
};

MotionHelper motionHelperVergil[] =
{
	{ MOTION_GROUP_VERGIL_BASE                  , pl021_00_0 },
	{ MOTION_GROUP_VERGIL_DAMAGE                , pl021_00_1 },
	{ MOTION_GROUP_VERGIL_TAUNTS                , pl021_00_2 },
	{ MOTION_GROUP_VERGIL_YAMATO                , pl021_00_3 },
	{ MOTION_GROUP_VERGIL_BEOWULF               , pl021_00_4 },
	{ MOTION_GROUP_VERGIL_FORCE_EDGE            , pl021_00_5 },
	{ MOTION_GROUP_VERGIL_DARK_SLAYER           , pl021_00_6 },
	{ MOTION_GROUP_VERGIL_NERO_ANGELO_YAMATO    , pl021_00_7 },
	{ MOTION_GROUP_VERGIL_NERO_ANGELO_BEOWULF   , pl021_00_8 },
	{ MOTION_GROUP_VERGIL_NERO_ANGELO_FORCE_EDGE, pl021_00_9 },
};

MotionHelper * motionHelper[] =
{
	motionHelperDante,
	motionHelperBob,
	motionHelperLady,
	motionHelperVergil,
};

uint8 motionHelperCount[] =
{
	countof(motionHelperDante),
	countof(motionHelperBob),
	countof(motionHelperLady),
	countof(motionHelperVergil),
};

typedef void(* InternalAdjustPointers_t)(byte8 *);

InternalAdjustPointers_t InternalAdjustPointers = 0;

void UpdateCostume(ACTOR_DATA * actorData)
{
	auto fileItem = (FILE_ITEM *)(appBaseAddr + 0xC99D30);

	if (Config.Game.Multiplayer.enable && (actorData->id != 0))
	{
		actorData->costume = Config.Game.Multiplayer.costume[(actorData->id - 1)];
	}

	switch (actorData->character)
	{
	case CHAR_DANTE:
	{
		if (actorData->costume >= countof(costumeMapDante))
		{
			actorData->costume = 0;
		}
		auto cacheFileId = costumeMapDante[actorData->costume];
		fileItem[0].file = System_File_cacheFile[cacheFileId];
		fileItem[0].stringItem = &stringItem[cacheFileId];
		break;
	}
	case CHAR_VERGIL:
	{
		if (actorData->costume >= countof(costumeMapVergil))
		{
			actorData->costume = 0;
		}
		auto cacheFileId = costumeMapVergil[actorData->costume];
		fileItem[3].file = System_File_cacheFile[cacheFileId];
		fileItem[3].stringItem = &stringItem[cacheFileId];
		break;
	}
	}
}

void UpdateSword(ACTOR_DATA * actorData)
{
	auto & unlockDevilTrigger = *(bool *)(appBaseAddr + 0xC8F250 + 0xD1);
	auto fileItem = (FILE_ITEM *)(appBaseAddr + 0xC99D30);
	uint8 sword = 0;

	if (actorData->character != CHAR_DANTE)
	{
		return;
	}

	if (Config.Game.WeaponSwitcher.enable && (Config.Game.WeaponSwitcher.sword != 0))
	{
		sword = (Config.Game.WeaponSwitcher.sword - 1);
	}
	else
	{
		if (unlockDevilTrigger)
		{
			sword = 1;
		}
		switch (actorData->costume)
		{
		case COSTUME_DANTE_DMC1:
		case COSTUME_DANTE_DMC1_NO_COAT:
		case COSTUME_DANTE_SPARDA:
		case COSTUME_DANTE_SPARDA_INFINITE_MAGIC_POINTS:
			sword = 2;
			break;
		}
	}

	sword = 2;

	auto cacheFileId = swordMap[sword];
	fileItem[140].file = System_File_cacheFile[cacheFileId];
}

PrivateEnd;

bool System_File_ExtractFile(const char * filename)
{
	char buffer[128];
	zip * archive = 0;
	zip_error result = {};
	zip_file * file = 0;
	zip_stat_t stats = {};
	byte8 * addr = 0;

	snprintf(buffer, sizeof(buffer), "data\\dmc3\\dmc3-0.nbz");

	archive = zip_open(buffer, 0, &result.zip_err);
	if (!archive)
	{
		Log("zip_open failed. %d %s", result.zip_err, filename);
		return false;
	}

	snprintf(buffer, sizeof(buffer), "GData.afs/%s", filename);

	file = zip_fopen(archive, buffer, 0);
	if (!file)
	{
		Log("zip_fopen failed. %d %s", result.zip_err, filename);
		zip_close(archive);
		return false;
	}

	zip_stat_init(&stats);
	zip_stat(archive, buffer, 0, &stats);

	addr = Alloc((uint32)stats.size);
	if (!addr)
	{
		Log("Alloc failed.");
		zip_fclose(file);
		zip_close(archive);
		return false;
	}

	zip_fread(file, addr, stats.size);
	zip_fclose(file);
	zip_close(archive);

	snprintf(buffer, sizeof(buffer), "data\\dmc3\\GData.afs\\%s", filename);

	if (!SaveFile(buffer, addr, (uint32)stats.size))
	{
		Log("SaveFile failed.");
		return false;
	}

	return true;
}

byte8 * System_File_LoadFile
(
	const char * filename,
	uint32     * size,
	byte8      * dest,
	bool         skipArchive
)
{
	byte8 * file = 0;

	char buffer[128];
	snprintf(buffer, sizeof(buffer), "data\\dmc3\\GData.afs\\%s", filename);

	file = LoadFile(buffer, size, dest);
	if (!file)
	{
		Log("LoadFile failed.");
		if (skipArchive)
		{
			return 0;
		}
		if (!System_File_ExtractFile(filename))
		{
			Log("System_File_ExtractFile failed.");
			return 0;
		}
		file = LoadFile(buffer, size, dest);
		if (!file)
		{
			Log("LoadFile failed.");
			return 0;
		}
	}

	return file;
}

void System_File_AdjustPointers(byte8 * archive)
{
	if constexpr (debug)
	{
		LogFunction();
	}
	{
		byte8 signature[] = { 'P','A','C' };
		for (uint8 index = 0; index < countof(signature); index++)
		{
			if (archive[index] != signature[index])
			{
				if constexpr (debug)
				{
					Log("Not a PAC.");
					Log("archive %.16llX", archive);
				}
				goto sect0;
			}
		}
		uint32 & fileCount = *(uint32 *)(archive + 4);
		for (uint32 fileIndex = 0; fileIndex < fileCount; fileIndex++)
		{
			uint32 & fileOff = ((uint32 *)(archive + 8))[fileIndex];
			InternalAdjustPointers((archive + fileOff));
			if constexpr (debug)
			{
				Log("%.16llX", (archive + fileOff));
			}
		}
		return;
	}
	sect0:
	InternalAdjustPointers(archive);
}

byte8 * System_File_PushFile(const char * filename)
{
	if constexpr (debug)
	{
		LogFunction();
	}

	auto addr = (System_Memory_addr + (512 * 1024 * 1024) + cachePos);
	byte8 * file = 0;
	uint32 fileSize = 0;

	file = System_File_LoadFile(filename, &fileSize, addr);
	if (!file)
	{
		Log("System_File_LoadFile failed.");
		return 0;
	}

	cachePos += fileSize;

	if constexpr (debug)
	{
		Log("cachePos %X", cachePos);
	}

	Align<uint32>(cachePos, 0x800);

	if constexpr (debug)
	{
		Log("file     %.16llX %s", file, filename);
		Log("fileSize %X", fileSize);
		Log("cachePos %X", cachePos);
	}

	return addr;
}







void System_File_UpdateFileItemsLite()
{
	for (uint8 helperIndex = 0; helperIndex < countof(fileItemHelper); helperIndex++)
	{
		fileItemHelper[helperIndex].Update();
	}
	//UpdateCostume(actorData);
	//UpdateSword(actorData);
}





void System_File_UpdateFileItems(ACTOR_DATA * actorData)
{
	for (uint8 helperIndex = 0; helperIndex < countof(fileItemHelper); helperIndex++)
	{
		fileItemHelper[helperIndex].Update();
	}
	UpdateCostume(actorData);
	UpdateSword(actorData);
}

void System_File_UpdateMotion(ACTOR_DATA * actorData)
{
	//memset(&actorData->motionFile, 0, (MAX_MOT * 8));
	//auto character = actorData->character;
	//if (character >= MAX_CHAR_LOGIC)
	//{
	//	character = 0;
	//}
	//auto & count = motionHelperCount[character];
	//for (uint8 index = 0; index < count; index++)
	//{
	//	auto & motionId    = motionHelper[character][index].motionId;
	//	auto & cacheFileId = motionHelper[character][index].cacheFileId;
	//	actorData->motionFile[motionId] = System_File_cacheFile[cacheFileId];
	//}
}

void System_File_Init()
{
	LogFunction();

	// @Todo: Internal!

	{
		FUNC func = CreateFunction((appBaseAddr + 0x1B9FA0));
		InternalAdjustPointers = (InternalAdjustPointers_t)func.addr;
	}

	CreateDirectoryA("data\\dmc3\\GData.afs", 0);


	
	// @Todo: External bool function. Terminate if fail.

	for (uint16 cacheFileId = 0; cacheFileId < MAX_CACHE_FILE; cacheFileId++)
	{
		auto file = System_File_PushFile(cacheFilename[cacheFileId]);
		if (!file)
		{
			Log("System_File_PushFile failed. %s", cacheFilename[cacheFileId]);
			return;
		}
		System_File_AdjustPointers(file);
		System_File_cacheFile[cacheFileId] = file;
	}


	return;


	for (uint32 index = 0; index < countof(stringItemOff); index++)
	{
		stringItem[index].string = (const char *)(appBaseAddr + 0xE00 + stringItemOff[index]);
	}

	{
		byte8 sect0[] =
		{
			0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rax,&Config.System.File.preferLocalFiles
			0x8A, 0x00,                                                 //mov al,[rax]
			0x84, 0xC0,                                                 //test al,al
			0x74, 0x0F,                                                 //je short
			0xBA, 0x00, 0x00, 0x00, 0x00,                               //mov edx,FILE_MODE_LOCAL
			0xE8, 0x00, 0x00, 0x00, 0x00,                               //call dmc3.exe+327430
			0x48, 0x85, 0xC0,                                           //test rax,rax
			0x75, 0x10,                                                 //jne short
			0x8D, 0x56, 0x01,                                           //lea edx,[rsi+01]
			0x48, 0x8D, 0x8C, 0x24, 0x60, 0x01, 0x00, 0x00,             //lea rcx,[rsp+00000160]
			0xE8, 0x00, 0x00, 0x00, 0x00,                               //call dmc3.exe+327430
		};
		FUNC func = CreateFunction(0, (appBaseAddr + 0x2FDB1), false, false, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*(bool **)(func.sect0 + 2) = &Config.System.File.preferLocalFiles;
		*(uint32 *)(func.sect0 + 0x11) = FILE_MODE_LOCAL;
		WriteCall((func.sect0 + 0x15), (appBaseAddr + 0x327430));
		WriteCall((func.sect0 + 0x2A), (appBaseAddr + 0x327430));
		WriteJump((appBaseAddr + 0x2FDAC), func.addr);
	}
}
