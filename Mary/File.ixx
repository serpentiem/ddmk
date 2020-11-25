// @Todo: Update!

module;
#include "../Core/Core.h"

#define ZIP_STATIC
#include "../Zip/zip.h"

#include "Vars.h"
export module File;

import Config;
import Internal;
import Memory;

#define debug false

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
		auto & archiveData = *reinterpret_cast<ArchiveData *>(addr);
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





export FileVector File_staticFiles;
export FileVector File_dynamicFiles;

StringData stringData[MAX_CACHE_FILE] = {};

byte8 * demo_pl000_00_3 = 0;



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

export byte8 * File_LoadFile
(
	const char * filename,
	uint32     * size = 0,
	byte8      * dest = 0,
	bool         skipArchive = false
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


// @Todo: Update.
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
				Log("%.4u %.16llX", fileIndex, (archive + fileOff));
			}
		}
		return;
	}
sect0:
	func_1B9FA0(archive);
}






byte8 * FileVector::Push(const char * filename)
{
	if constexpr (debug)
	{
		LogFunction(filename);
	}

	byte8 * file = 0;
	uint32 fileSize = 0;

	file = File_LoadFile(filename, &fileSize, (data + pos));
	if (!file)
	{
		Log("File_LoadFile failed.");
		return 0;
	}

	metadata[count].addr = file;
	metadata[count].size = fileSize;

	uint32 lastPos = pos;
	pos += fileSize;
	Align<uint32>(pos, 0x800, data);
	metadata[count].alignedSize = (pos - lastPos);

	if constexpr (debug)
	{
		Log("file        %.16llX", file);
		Log("fileSize    %X", fileSize);
		Log("data        %.16llX", data);
		Log("pos         %X", pos);
		Log("count       %u", count);
		Log("addr        %.16llX", metadata[count].addr);
		Log("size        %u", metadata[count].size);
		Log("alignedSize %u", metadata[count].alignedSize);
	}

	count++;

	return file;
}

byte8 * FileVector::Push(byte8 * file, uint32 fileSize)
{
	if constexpr (debug)
	{
		LogFunction();
		Log("file     %.16llX", file);
		Log("fileSize %u", fileSize);
	}

	auto dest = (data + pos);
	memcpy(dest, file, fileSize);

	metadata[count].addr = dest;
	metadata[count].size = fileSize;

	uint32 lastPos = pos;
	pos += fileSize;
	Align<uint32>(pos, 0x800, data);
	metadata[count].alignedSize = (pos - lastPos);

	if constexpr (debug)
	{
		Log("file        %.16llX", file);
		Log("fileSize    %X", fileSize);
		Log("data        %.16llX", data);
		Log("pos         %X", pos);
		Log("count       %u", count);
		Log("addr        %.16llX", metadata[count].addr);
		Log("size        %u", metadata[count].size);
		Log("alignedSize %u", metadata[count].alignedSize);
	}

	count++;

	return dest;
}

export void File_UpdateFileData
(
	uint16 fileDataId,
	uint16 fileId
)
{
	// @Todo: Add source.
	auto & fileData = (reinterpret_cast<FileData *>(appBaseAddr + 0xC99D30))[fileDataId];

	memset(&fileData, 0, sizeof(FileData));

	fileData.status = FILE_STATUS_READY;
	fileData.stringData = &stringData[fileId];
	fileData.file = File_staticFiles[fileId];
}

export bool File_Init()
{
	LogFunction();

	CreateDirectoryA("data\\dmc3\\GData.afs", 0);

	{
		auto dest = (Memory_main + MEMORY_SIZE_MAIN);

		File_staticFiles.data = dest;
		dest += MEMORY_SIZE_STATIC_FILES;

		File_staticFiles.metadata = reinterpret_cast<FileVectorMetadata *>(dest);
		dest += MEMORY_SIZE_STATIC_FILES_METADATA;

		File_dynamicFiles.data = dest;
		dest += MEMORY_SIZE_DYNAMIC_FILES;

		File_dynamicFiles.metadata = reinterpret_cast<FileVectorMetadata *>(dest);
		dest += MEMORY_SIZE_DYNAMIC_FILES_METADATA;
	}

	if constexpr (debug)
	{
		Log("File_staticFiles.data      %.16llX", File_staticFiles.data);
		Log("File_staticFiles.metadata  %.16llX", File_staticFiles.metadata);
		Log("File_dynamicFiles.data     %.16llX", File_dynamicFiles.data);
		Log("File_dynamicFiles.metadata %.16llX", File_dynamicFiles.metadata);
	}

	for_all(uint8, cacheFileId, MAX_CACHE_FILE)
	{
		if constexpr (debug)
		{
			Log("%u", cacheFileId);
		}
		auto & name = cacheFileHelper[cacheFileId].name;
		auto & type = cacheFileHelper[cacheFileId].type;
		auto file = File_staticFiles.Push(name);
		if (!file)
		{
			Log("File_PushFile failed. %s", name);
			return false;
		}
		File_AdjustPointers(file);
		stringData[cacheFileId].string = type;
	}

	{
		constexpr byte8 sect0[] =
		{
			0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rax,&activeConfig.System.File.preferLocalFiles
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
		auto func = CreateFunction(0, (appBaseAddr + 0x2FDB1), false, false, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*reinterpret_cast<bool **>(func.sect0 + 2) = &activeConfig.File.preferLocalFiles;
		*reinterpret_cast<uint32 *>(func.sect0 + 0x11) = FILE_MODE_LOCAL;
		WriteCall((func.sect0 + 0x15), (appBaseAddr + 0x327430));
		WriteCall((func.sect0 + 0x2A), (appBaseAddr + 0x327430));
		WriteJump((appBaseAddr + 0x2FDAC), func.addr);
	}

	return true;
}
