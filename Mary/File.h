#pragma once
#include "../Core/Core.h"

#define ZIP_STATIC
#include "../Zip/zip.h"

#include "Config.h"
#include "Internal.h"
#include "Memory.h"
#include "Vars.h"



















//
//
//
//
//
//template <typename T, uint32 itemCount>
//struct vector
//{
//	uint32 count;
//	T data[itemCount];
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
//	T & operator[](uint32 index)
//	{
//		return data[index];
//	}
//	vector()
//	{
//		Clear();
//	}
//};
//
//




//
//struct CacheFile
//{
//	byte8 * file;
//
//	CacheFile()
//	{
//		memset(this, 0, sizeof(*this));
//	}
//
//	CacheFile(byte8 * addr)
//	{
//		file = addr;
//	}
//
//	operator byte8 *()
//	{
//		return file;
//	}
//
//	byte8 * operator[](uint32 index)
//	{
//		auto & archiveData = *reinterpret_cast<ARCHIVE_DATA *>(file);
//		if (index >= archiveData.fileCount)
//		{
//			Log("Outside file range. %u %u", archiveData.fileCount, index);
//			return 0;
//		}
//		if (!archiveData.fileOff[index])
//		{
//			return 0;
//		}
//		return (file + archiveData.fileOff[index]);
//	}
//};
//
//




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
		memset(this, 0, sizeof(*this));
	}
};




extern FileVector File_staticFiles;
extern FileVector File_dynamicFiles;























//extern CacheFile File_staticFiles[MAX_CACHE_FILE];























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



//byte8 * File_PushFile(const char * filename);




void File_UpdateFileItem
(
	uint16 fileItemId,
	uint16 cacheFileId
);



void File_UpdateFileItems();




bool File_Init();
