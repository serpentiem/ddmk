#include "File.h"

constexpr bool debug = false;

CacheFile File_cacheFile[MAX_CACHE_FILE];

byte8 * demo_pl000_00_3 = 0;

PrivateStart;

uint32 cachePos = 0;

STRING_ITEM stringItem[countof(stringItemOff)] = {};

// @Research: Make local.
constexpr uint16 costumeMapDante[] =
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

constexpr uint16 costumeMapVergil[] =
{
	pl021,
	pl023,
	pl021,
	pl026,
	pl026,
};

constexpr uint16 swordMap[] =
{
	plwp_sword,
	plwp_sword2,
	plwp_sword3,
};

PrivateEnd;

bool File_ExtractFile(const char * filename)
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

byte8 * File_LoadFile
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
		if (!File_ExtractFile(filename))
		{
			Log("File_ExtractFile failed.");
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

void File_AdjustPointers(byte8 * archive)
{
	if constexpr (debug)
	{
		LogFunction();
	}
	{
		constexpr byte8 signature[] = { 'P','A','C' };
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
			func_1B9FA0((archive + fileOff));
			if constexpr (debug)
			{
				Log("%.16llX", (archive + fileOff));
			}
		}
		return;
	}
	sect0:
	func_1B9FA0(archive);
}

byte8 * File_PushFile(const char * filename)
{
	if constexpr (debug)
	{
		LogFunction();
	}

	auto addr = (Memory_addr + (512 * 1024 * 1024) + cachePos);
	byte8 * file = 0;
	uint32 fileSize = 0;

	file = File_LoadFile(filename, &fileSize, addr);
	if (!file)
	{
		Log("File_LoadFile failed.");
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

void File_UpdateFileItem
(
	uint16 fileItemId,
	uint16 cacheFileId
)
{
	auto & fileItem = (reinterpret_cast<FILE_ITEM *>(appBaseAddr + 0xC99D30))[fileItemId];

	memset(&fileItem, 0, sizeof(FILE_ITEM));

	fileItem.status     = FILE_ITEM_READY;
	fileItem.stringItem = &stringItem[cacheFileId];
	fileItem.file       = File_cacheFile[cacheFileId];
}

void File_UpdateFileItems()
{
	LogFunction();
	const_for_all(index, countof(fileItemHelper))
	{
		File_UpdateFileItem
		(
			fileItemHelper[index].fileItemId,
			fileItemHelper[index].cacheFileId
		);
	}
}

//void UpdateCostume(ACTOR_DATA * actorData)
//{
//	auto fileItem = (FILE_ITEM *)(appBaseAddr + 0xC99D30);
//
//	if (Config.Game.Multiplayer.enable && (actorData->id != 0))
//	{
//		actorData->costume = Config.Game.Multiplayer.costume[(actorData->id - 1)];
//	}
//
//	switch (actorData->character)
//	{
//	case CHAR_DANTE:
//	{
//		if (actorData->costume >= countof(costumeMapDante))
//		{
//			actorData->costume = 0;
//		}
//		auto cacheFileId = costumeMapDante[actorData->costume];
//		fileItem[0].file = System_File_cacheFile[cacheFileId];
//		fileItem[0].stringItem = &stringItem[cacheFileId];
//		break;
//	}
//	case CHAR_VERGIL:
//	{
//		if (actorData->costume >= countof(costumeMapVergil))
//		{
//			actorData->costume = 0;
//		}
//		auto cacheFileId = costumeMapVergil[actorData->costume];
//		fileItem[3].file = System_File_cacheFile[cacheFileId];
//		fileItem[3].stringItem = &stringItem[cacheFileId];
//		break;
//	}
//	}
//}
//
//void UpdateSword(ACTOR_DATA * actorData)
//{
//	auto & unlockDevilTrigger = *(bool *)(appBaseAddr + 0xC8F250 + 0xD1);
//	auto fileItem = (FILE_ITEM *)(appBaseAddr + 0xC99D30);
//	uint8 sword = 0;
//
//	if (actorData->character != CHAR_DANTE)
//	{
//		return;
//	}
//
//	if (Config.Game.WeaponSwitcher.enable && (Config.Game.WeaponSwitcher.sword != 0))
//	{
//		sword = (Config.Game.WeaponSwitcher.sword - 1);
//	}
//	else
//	{
//		if (unlockDevilTrigger)
//		{
//			sword = 1;
//		}
//		switch (actorData->costume)
//		{
//		case COSTUME_DANTE_DMC1:
//		case COSTUME_DANTE_DMC1_NO_COAT:
//		case COSTUME_DANTE_SPARDA:
//		case COSTUME_DANTE_SPARDA_INFINITE_MAGIC_POINTS:
//			sword = 2;
//			break;
//		}
//	}
//
//	sword = 2;
//
//	auto cacheFileId = swordMap[sword];
//	fileItem[140].file = System_File_cacheFile[cacheFileId];
//}

bool File_Init()
{
	LogFunction();

	CreateDirectoryA("data\\dmc3\\GData.afs", 0);

	const_for_all(cacheFileId, MAX_CACHE_FILE)
	{
		if constexpr (debug)
		{
			Log("%u", cacheFileId);
		}
		auto file = File_PushFile(cacheFilename[cacheFileId]);
		if (!file)
		{
			Log("File_PushFile failed. %s", cacheFilename[cacheFileId]);
			return false;
		}
		File_AdjustPointers(file);
		File_cacheFile[cacheFileId] = file;
	}

	return true;

	const_for_all(index, countof(stringItemOff))
	{
		stringItem[index].string = reinterpret_cast<const char *>(appBaseAddr + 0xE00 + stringItemOff[index]);
	}

	// @Todo: Update!
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

	return true;
}
