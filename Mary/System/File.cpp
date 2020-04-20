#include "File.h"












//typedef void(* InternalAdjustPointers_t)(byte8 *);
//
//InternalAdjustPointers_t InternalAdjustPointers = 0;

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











void System_File_UpdateFileItemsLite()
{
	for (uint8 helperIndex = 0; helperIndex < countof(fileItemHelper); helperIndex++)
	{
		fileItemHelper[helperIndex].Update();
	}
	//UpdateCostume(actorData);
	//UpdateSword(actorData);
}





//void System_File_UpdateFileItems(ACTOR_DATA * actorData)
//{
//	for (uint8 helperIndex = 0; helperIndex < countof(fileItemHelper); helperIndex++)
//	{
//		fileItemHelper[helperIndex].Update();
//	}
//	UpdateCostume(actorData);
//	UpdateSword(actorData);
//}

//void System_File_UpdateMotion(ACTOR_DATA * actorData)
//{
//	//memset(&actorData->motionFile, 0, (MAX_MOT * 8));
//	//auto character = actorData->character;
//	//if (character >= MAX_CHAR_LOGIC)
//	//{
//	//	character = 0;
//	//}
//	//auto & count = motionHelperCount[character];
//	//for (uint8 index = 0; index < count; index++)
//	//{
//	//	auto & motionId    = motionHelper[character][index].motionId;
//	//	auto & cacheFileId = motionHelper[character][index].cacheFileId;
//	//	actorData->motionFile[motionId] = System_File_cacheFile[cacheFileId];
//	//}
//}

void System_File_Init()
{
	LogFunction();

	// @Todo: Internal!

	//{
	//	FUNC func = CreateFunction((appBaseAddr + 0x1B9FA0));
	//	InternalAdjustPointers = (InternalAdjustPointers_t)func.addr;
	//}

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
