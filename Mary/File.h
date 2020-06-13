#pragma once
#include "../Core/Core.h"

#define ZIP_STATIC
#include "../Zip/zip.h"

#include "ActorData.h"
#include "Config.h"
#include "Internal.h"
#include "Memory.h"
#include "Vars.h"

struct FileVectorMetadata
{
	byte8 * addr;
	uint32 size;
	uint32 alignedSize;
	operator byte8 *()
	{
		return addr;
	}
	byte8 * operator[](uint32 index)
	{
		auto & archiveData = *reinterpret_cast<ARCHIVE_DATA *>(addr);
		if (index >= archiveData.fileCount)
		{
			Log("Outside file range. %u %u", archiveData.fileCount, index);
			return 0;
		}
		if (!archiveData.fileOff[index])
		{
			return 0;
		}
		return (addr + archiveData.fileOff[index]);
	}
};

struct FileVector
{
	byte8 * data;
	uint32 pos;
	uint32 count;
	FileVectorMetadata * metadata;
	uint32 dataSize;
	uint32 metadataSize;

	byte8 * Push(const char * filename); // @Todo: Modules.
	byte8 * Push(byte8 * file, uint32 fileSize);
	void Pop()
	{
		if (count == 0)
		{
			return;
		}

		pos -= metadata[count].alignedSize;
		count--;
	}
	FileVectorMetadata & operator[](uint32 index)
	{
		return metadata[index];
	}
	void Clear()
	{
		if (count == 0)
		{
			return;
		}
		memset(metadata, 0, (count * sizeof(FileVectorMetadata)));
		count = 0;
	}
	void Reset()
	{
		memset(this, 0, sizeof(*this));
	}
};

extern FileVector File_staticFiles;
extern FileVector File_dynamicFiles;
extern byte8 * demo_pl000_00_3;

bool File_ExtractFile(const char * filename);

byte8 * File_LoadFile
(
	const char * filename,
	uint32     * size        = 0,
	byte8      * dest        = 0,
	bool         skipArchive = false
);

void File_AdjustPointers(byte8 * archive);

void File_UpdateFileItem
(
	uint16 fileItemId,
	uint16 cacheFileId
);

// @Todo: Modules.

constexpr uint16 File_costumeMapDante[MAX_COSTUME_DANTE] =
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

constexpr uint16 File_costumeMapVergil[MAX_COSTUME_VERGIL] =
{
	pl021,
	pl023,
	pl021,
	pl026,
	pl026,
};

template <typename T>
void File_UpdateCostumeFileItems(T & actorData)
{
	auto & unlockDevilTrigger = *reinterpret_cast<bool *>(appBaseAddr + 0xC8F250 + 0xD1); // @Todo: Use SESSION_DATA.
	auto costume = actorData.costume;
	uint16 cacheFileId = 0;

	if constexpr (typematch(T, ACTOR_DATA_DANTE))
	{
		if (costume >= MAX_COSTUME_DANTE)
		{
			costume = COSTUME_DANTE_DEFAULT;
		}
		cacheFileId = File_costumeMapDante[costume];
		File_UpdateFileItem(0, cacheFileId);
		// Update Sword
		cacheFileId = (unlockDevilTrigger) ? plwp_sword2 : plwp_sword;
		switch (costume)
		{
		case COSTUME_DANTE_DMC1:
		case COSTUME_DANTE_DMC1_NO_COAT:
		case COSTUME_DANTE_SPARDA:
		case COSTUME_DANTE_SPARDA_INFINITE_MAGIC_POINTS:
		{
			cacheFileId = plwp_sword3;
			break;
		}
		}
		File_UpdateFileItem(140, cacheFileId);
	}
	else if constexpr (typematch(T, ACTOR_DATA_VERGIL))
	{
		if (costume >= MAX_COSTUME_VERGIL)
		{
			costume = COSTUME_VERGIL_DEFAULT;
		}
		cacheFileId = File_costumeMapVergil[costume];
		File_UpdateFileItem(3, cacheFileId);
	}
}

void File_UpdateMainFileItems();

bool File_Init();
