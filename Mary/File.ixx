


module;
#include "../Zip/zip.h"
export module File;



import Core;

#include "../Core/Macros.h"

import Windows;

import Vars;


import Config;
import Internal;
import Memory;

using namespace Windows;

#define debug false





export bool IsArchive(byte8 * addr)
{
	if (!addr)
	{
		return false;
	}

	constexpr byte8 signature1[] = { 'P', 'A', 'C' };
	constexpr byte8 signature2[] = { 'P', 'N', 'S', 'T' };

	if
	(
		SignatureMatch(addr, signature1) ||
		SignatureMatch(addr, signature2)
	)
	{
		return true;
	}

	return false;
}

void AdjustPointers(byte8 * archive)
{
	if constexpr (debug)
	{
		LogFunction();

		Log("archive %.16llX", archive);
	}

	if (!archive)
	{
		return;
	}

	if (!IsArchive(archive))
	{
		Log("IsArchive failed.");

		func_1B9FA0(archive);

		return;
	}

	auto & archiveMetadata = *reinterpret_cast<ArchiveMetadata *>(archive);

	for_all(uint32, fileIndex, archiveMetadata.fileCount)
	{
		auto & fileOff = archiveMetadata.fileOffs[fileIndex];

		if constexpr (debug)
		{
			Log("fileOff %X", fileOff);
		}

		if (!fileOff)
		{
			continue;
		}

		auto file = (archive + fileOff);

		if constexpr (debug)
		{
			Log("%.4u %.16llX", fileIndex, file);
		}

		func_1B9FA0(file);
	}
}

// @Todo: Add LoadFileFromZip.
// filename, dest = 0

bool ExtractFile(const char * name)
{
	if constexpr (debug)
	{
		LogFunction();

		Log("name %s", name);
	}

	char path[128];
	zip * archive = 0;
	zip_error result = {};
	zip_file * file = 0;
	zip_stat_t stats = {};
	constexpr uint64 maxSize = (128 * 1024 * 1024);
	byte8 * addr = 0;

	snprintf
	(
		path,
		sizeof(path),
		"data\\dmc3\\dmc3-0.nbz"
	);

	archive = zip_open
	(
		path,
		0,
		&result.zip_err
	);
	if (!archive)
	{
		Log("zip_open failed. %d %s", result.zip_err, name);

		return false;
	}

	snprintf
	(
		path,
		sizeof(path),
		"GData.afs/%s",
		name
	);

	file = zip_fopen
	(
		archive,
		path,
		0
	);
	if (!file)
	{
		Log("zip_fopen failed. %d %s", result.zip_err, name);

		zip_close(archive);

		return false;
	}

	zip_stat_init(&stats);
	zip_stat
	(
		archive,
		path,
		0,
		&stats
	);

	if (stats.size > maxSize)
	{
		Log("File is too big.");

		zip_fclose(file);
		zip_close(archive);

		return false;
	}

	addr = Alloc(stats.size);
	if (!addr)
	{
		Log("Alloc failed.");

		zip_fclose(file);
		zip_close(archive);

		return false;
	}

	zip_fread
	(
		file,
		addr,
		stats.size
	);

	zip_fclose(file);
	zip_close(archive);

	snprintf
	(
		path,
		sizeof(path),
		"data\\dmc3\\GData.afs\\%s",
		name
	);

	if
	(
		!SaveFile
		(
			path,
			addr,
			stats.size
		)
	)
	{
		Log("SaveFile failed.");

		Free(addr);

		return false;
	}

	Free(addr);

	return true;
}

struct FileManager : Container<>
{
	struct Metadata
	{
		byte8 * addr;
		uint64 size;
		uint64 alignedSize;

		byte8 * operator[](uint32 fileIndex);
		operator byte8 *();
	};

	byte8 * Push
	(
		const char * name,
		bool skipArchive = false
	);
	byte8 * Push
	(
		byte8 * addr,
		uint64 size
	);
	Metadata & operator[](uint64 index);
};


// @Todo: Add GetFileSize(uint32 fileIndex).

byte8 * FileManager::Metadata::operator[](uint32 fileIndex)
{

	if constexpr (debug)
	{
		LogFunction();

		Log("fileIndex %u", fileIndex);
	}



	if
	(
		!addr ||
		(size == 0) ||
		(alignedSize == 0) ||
		!IsArchive(addr)
	)
	{
		if constexpr (debug)
		{
			Log("IsArchive failed.");

			HoboBreak();
		}

		return 0;
	}

	auto & archiveMetadata = *reinterpret_cast<ArchiveMetadata *>(addr);

	if (fileIndex >= archiveMetadata.fileCount)
	{
		Log("Out of range. %u %u", fileIndex, archiveMetadata.fileCount);

		return 0;
	}

	auto & fileOff = archiveMetadata.fileOffs[fileIndex];

	return (addr + fileOff);
}

FileManager::Metadata::operator byte8 *()
{
	if constexpr (debug)
	{
		LogFunction();

		Log("addr %.16llX", addr);
	}

	return addr;
}

byte8 * FileManager::Push
(
	const char * name,
	bool skipArchive
)
{
	if constexpr (debug)
	{
		LogFunction();

		Log("name %s", name);
		Log("skipArchive %u", skipArchive);
	}

	if
	(
		!dataAddr ||
		(dataSize == 0) ||
		!metadataAddr ||
		(metadataSize == 0) ||
		!name
	)
	{
		return 0;
	}

	char path[128];
	HANDLE file = 0;
	uint64 size = 0;
	byte8 * dest = 0;

	snprintf
	(
		path,
		sizeof(path),
		"data\\dmc3\\GData.afs\\%s",
		name
	);

	file = OpenFile
	(
		path,
		FileFlags_Read
	);
	if (file == reinterpret_cast<HANDLE>(INVALID_HANDLE_VALUE))
	{
		Log("OpenFile failed. %s", path);

		if (skipArchive)
		{
			return 0;
		}

		if (!ExtractFile(name))
		{
			Log("ExtractFile failed. %s", name);

			return 0;
		}

		file = OpenFile
		(
			path,
			FileFlags_Read
		);
		if (file == reinterpret_cast<HANDLE>(INVALID_HANDLE_VALUE))
		{
			Log("OpenFile failed. %s", path);

			return 0;
		}
	}

	size = GetFileSize(file);
	if (size == 0)
	{
		if (!CloseFile(file))
		{
			Log("CloseFile failed.");
		}

		return 0;
	}

	dest = Next(size);
	if (!dest)
	{
		return 0;
	}

	if
	(
		!LoadFile
		(
			file,
			size,
			dest
		)
	)
	{
		Log("LoadFile failed.");

		return 0;
	}

	if (!CloseFile(file))
	{
		Log("CloseFile failed.");
	}

	auto & metadata = reinterpret_cast<Metadata *>(metadataAddr)[count];

	metadata.addr = dest;
	metadata.size = size;

	auto lastPos = pos;

	pos += size;

	Align<uint64>(pos, 0x800);

	metadata.alignedSize = (pos - lastPos);

	if constexpr (debug)
	{
		Log("addr        %llX", metadata.addr);
		Log("size        %llX", metadata.size);
		Log("alignedSize %llX", metadata.alignedSize);
	}

	count++;

	return dest;
}

byte8 * FileManager::Push
(
	byte8 * addr,
	uint64 size
)
{
	if constexpr (debug)
	{
		LogFunction();

		Log("addr %llX", addr);
		Log("size %llu", size);
	}

	if
	(
		!dataAddr ||
		(dataSize == 0) ||
		!metadataAddr ||
		(metadataSize == 0) ||
		!addr ||
		(size == 0)
	)
	{
		return 0;
	}

	byte8 * dest = 0;

	dest = Next(size);
	if (!dest)
	{
		return 0;
	}

	CopyMemory
	(
		dest,
		addr,
		size
	);

	auto & metadata = reinterpret_cast<Metadata *>(metadataAddr)[count];

	metadata.addr = dest;
	metadata.size = size;

	auto lastPos = pos;

	pos += size;

	Align<uint64>(pos, 0x800);

	metadata.alignedSize = (pos - lastPos);

	if constexpr (debug)
	{
		Log("addr        %llX", metadata.addr);
		Log("size        %llX", metadata.size);
		Log("alignedSize %llX", metadata.alignedSize);
	}

	count++;

	return dest;
}

FileManager::Metadata & FileManager::operator[](uint64 index)
{
	return reinterpret_cast<Metadata *>(metadataAddr)[index];
}

export FileManager File_staticFiles;
export FileManager File_dynamicFiles;

FileDataTypeData fileDataTypeData[CACHE_FILE_COUNT] = {};

export byte8 * demo_pl000_00_3 = 0;

export void File_UpdateFileData
(
	FileData & fileData,
	uint16 cacheFileIndex
)
{
	SetMemory
	(
		&fileData,
		0,
		sizeof(fileData)
	);

	fileData.status       = FILE_DATA_STATUS::IN_USE;
	fileData.typeDataAddr = &fileDataTypeData[cacheFileIndex];
	fileData.file         = File_staticFiles[cacheFileIndex];
}

export void File_UpdateFileData
(
	uint16 fileDataIndex,
	uint16 cacheFileIndex
)
{
	auto & fileData = reinterpret_cast<FileData *>(appBaseAddr + 0xC99D30)[fileDataIndex];
	/*
	dmc3.exe+1AECAD - 48 8D 0D 7CB0AE00 - lea rcx,[dmc3.exe+C99D30]
	dmc3.exe+1AECBA - E8 31A10000       - call dmc3.exe+1B8DF0
	*/

	File_UpdateFileData
	(
		fileData,
		cacheFileIndex
	);
}

export FileData enemyFileData[ENEMY_FILE_DATA_COUNT] = {};
export FileDataMetadata enemyFileDataMetadata[ENEMY::COUNT] = {};

export bool File_Init()
{
	LogFunction();

	CreateDirectoryA("data\\dmc3\\GData.afs", 0);

	{
		auto dest = (Memory_main + MEMORY_SIZE_MAIN);

		auto Function = [&]
		(
			byte8 * & addr,
			uint64 & size,
			uint64 size2
		)
		{
			addr = dest;
			size = size2;

			dest += size2;
		};

		Function
		(
			File_staticFiles.dataAddr,
			File_staticFiles.dataSize,
			MEMORY_SIZE_STATIC_FILES
		);
		Function
		(
			File_staticFiles.metadataAddr,
			File_staticFiles.metadataSize,
			MEMORY_SIZE_STATIC_FILES_METADATA
		);
		Function
		(
			File_dynamicFiles.dataAddr,
			File_dynamicFiles.dataSize,
			MEMORY_SIZE_DYNAMIC_FILES
		);
		Function
		(
			File_dynamicFiles.metadataAddr,
			File_dynamicFiles.metadataSize,
			MEMORY_SIZE_DYNAMIC_FILES_METADATA
		);

		if constexpr (debug)
		{
			Log("File_staticFiles.dataAddr      %.16llX", File_staticFiles.dataAddr);
			Log("File_staticFiles.metadataAddr  %.16llX", File_staticFiles.metadataAddr);
			Log("File_dynamicFiles.dataAddr     %.16llX", File_dynamicFiles.dataAddr);
			Log("File_dynamicFiles.metadataAddr %.16llX", File_dynamicFiles.metadataAddr);
		}
	}

	for_all(uint16, cacheFileIndex, CACHE_FILE_COUNT)
	{
		auto & cacheFileHelper = cacheFileHelpers[cacheFileIndex];

		if constexpr (debug)
		{
			Log("%.4u %s", cacheFileIndex, cacheFileHelper.filename);
		}

		auto file = File_staticFiles.Push(cacheFileHelper.filename);
		if (!file)
		{
			Log("File_PushFile failed. %s", cacheFileHelper.filename);

			return false;
		}

		AdjustPointers(file);

		fileDataTypeData[cacheFileIndex].typeName = cacheFileHelper.typeName;
	}

	// Enemy File Data
	{
		constexpr uint16 cacheFileIndices[] =
		{
			em000,
			em006,
			em007,
			em008,
			em010,
			em011,
			em012,
			em013,
			em014,
			em016,
			em017,
			em021,
			em023,
			em025,
			em026,
			em027,
			em028,
			em029,
			em030,
			em031,
			em032,
			em034,
			em035,
			em037,
		};

		static_assert(countof(cacheFileIndices) == ENEMY_FILE_DATA_COUNT);

		for_all(uint8, fileDataIndex, ENEMY_FILE_DATA_COUNT)
		{
			auto & fileData = enemyFileData[fileDataIndex];

			auto & cacheFileIndex = cacheFileIndices[fileDataIndex];

			File_UpdateFileData
			(
				fileData,
				cacheFileIndex
			);
		}
	}

	// Enemy File Data Metadata
	{
		struct Helper
		{
			uint8 fileDataIndex;
			uint32 fileSetIndex;
		};

		constexpr Helper helpers[] =
		{
			{ ENEMY_FILE_DATA_EM000, ENEMY_FILE_SET_EM000 }, // Pride
			{ ENEMY_FILE_DATA_EM000, ENEMY_FILE_SET_EM000 }, // Pride
			{ ENEMY_FILE_DATA_EM000, ENEMY_FILE_SET_EM000 }, // Pride
			{ ENEMY_FILE_DATA_EM000, ENEMY_FILE_SET_EM000 }, // Pride
			{ ENEMY_FILE_DATA_EM000, ENEMY_FILE_SET_EM000 }, // Gluttony
			{ ENEMY_FILE_DATA_EM000, ENEMY_FILE_SET_EM000 }, // Gluttony
			{ ENEMY_FILE_DATA_EM000, ENEMY_FILE_SET_EM000 }, // Gluttony
			{ ENEMY_FILE_DATA_EM000, ENEMY_FILE_SET_EM000 }, // Gluttony
			{ ENEMY_FILE_DATA_EM000, ENEMY_FILE_SET_EM000 }, // Lust
			{ ENEMY_FILE_DATA_EM000, ENEMY_FILE_SET_EM000 }, // Lust
			{ ENEMY_FILE_DATA_EM000, ENEMY_FILE_SET_EM000 }, // Lust
			{ ENEMY_FILE_DATA_EM000, ENEMY_FILE_SET_EM000 }, // Lust
			{ ENEMY_FILE_DATA_EM000, ENEMY_FILE_SET_EM000 }, // Sloth
			{ ENEMY_FILE_DATA_EM000, ENEMY_FILE_SET_EM000 }, // Sloth
			{ ENEMY_FILE_DATA_EM000, ENEMY_FILE_SET_EM000 }, // Sloth
			{ ENEMY_FILE_DATA_EM000, ENEMY_FILE_SET_EM000 }, // Sloth
			{ ENEMY_FILE_DATA_EM000, ENEMY_FILE_SET_EM000 }, // Wrath
			{ ENEMY_FILE_DATA_EM000, ENEMY_FILE_SET_EM000 }, // Wrath
			{ ENEMY_FILE_DATA_EM000, ENEMY_FILE_SET_EM000 }, // Wrath
			{ ENEMY_FILE_DATA_EM000, ENEMY_FILE_SET_EM000 }, // Wrath
			{ ENEMY_FILE_DATA_EM000, ENEMY_FILE_SET_EM000 }, // Greed
			{ ENEMY_FILE_DATA_EM000, ENEMY_FILE_SET_EM000 }, // Greed
			{ ENEMY_FILE_DATA_EM000, ENEMY_FILE_SET_EM000 }, // Greed
			{ ENEMY_FILE_DATA_EM000, ENEMY_FILE_SET_EM000 }, // Greed
			{ ENEMY_FILE_DATA_EM006, ENEMY_FILE_SET_EM006 }, // Abyss
			{ ENEMY_FILE_DATA_EM007, ENEMY_FILE_SET_EM007 }, // Envy
			{ ENEMY_FILE_DATA_EM008, ENEMY_FILE_SET_EM008 }, // Hell Vanguard
			{ ENEMY_FILE_DATA_EM000, ENEMY_FILE_SET_EM000 }, // Unknown
			{ ENEMY_FILE_DATA_EM010, ENEMY_FILE_SET_EM010 }, // Arachne
			{ ENEMY_FILE_DATA_EM011, ENEMY_FILE_SET_EM011 }, // The Fallen
			{ ENEMY_FILE_DATA_EM012, ENEMY_FILE_SET_EM012 }, // Dullahan
			{ ENEMY_FILE_DATA_EM013, ENEMY_FILE_SET_EM013 }, // Enigma
			{ ENEMY_FILE_DATA_EM014, ENEMY_FILE_SET_EM014 }, // Blood-Goyle
			{ ENEMY_FILE_DATA_EM000, ENEMY_FILE_SET_EM000 }, // Unknown
			{ ENEMY_FILE_DATA_EM016, ENEMY_FILE_SET_EM016 }, // Soul Eater
			{ ENEMY_FILE_DATA_EM017, ENEMY_FILE_SET_EM017 }, // Damned Chessmen Pawn
			{ ENEMY_FILE_DATA_EM017, ENEMY_FILE_SET_EM017 }, // Damned Chessmen Knight
			{ ENEMY_FILE_DATA_EM017, ENEMY_FILE_SET_EM017 }, // Damned Chessmen Bishop
			{ ENEMY_FILE_DATA_EM017, ENEMY_FILE_SET_EM017 }, // Damned Chessmen Rook
			{ ENEMY_FILE_DATA_EM021, ENEMY_FILE_SET_EM021 }, // Damned Chessmen Queen
			{ ENEMY_FILE_DATA_EM021, ENEMY_FILE_SET_EM021 }, // Damned Chessmen King
			{ ENEMY_FILE_DATA_EM023, ENEMY_FILE_SET_EM023 }, // Gigapede
			{ ENEMY_FILE_DATA_EM000, ENEMY_FILE_SET_EM000 }, // Unknown
			{ ENEMY_FILE_DATA_EM025, ENEMY_FILE_SET_EM025 }, // Cerberus
			{ ENEMY_FILE_DATA_EM000, ENEMY_FILE_SET_EM000 }, // Unknown
			{ ENEMY_FILE_DATA_EM026, ENEMY_FILE_SET_EM026_2 }, // Agni & Rudra
			{ ENEMY_FILE_DATA_EM026, ENEMY_FILE_SET_EM026_2 }, // Agni & Rudra Black
			{ ENEMY_FILE_DATA_EM026, ENEMY_FILE_SET_EM026_2 }, // Agni & Rudra Red
			{ ENEMY_FILE_DATA_EM026, ENEMY_FILE_SET_EM026_2 }, // Agni & Rudra Blue
			{ ENEMY_FILE_DATA_EM028, ENEMY_FILE_SET_EM028 }, // Nevan
			{ ENEMY_FILE_DATA_EM029, ENEMY_FILE_SET_EM029 }, // Geryon
			{ ENEMY_FILE_DATA_EM030, ENEMY_FILE_SET_EM030 }, // Beowulf
			{ ENEMY_FILE_DATA_EM031, ENEMY_FILE_SET_EM031 }, // Doppelganger
			{ ENEMY_FILE_DATA_EM032, ENEMY_FILE_SET_EM032 }, // Arkham
			{ ENEMY_FILE_DATA_EM000, ENEMY_FILE_SET_EM000 }, // Unknown
			{ ENEMY_FILE_DATA_EM034, ENEMY_FILE_SET_EM034 }, // Lady
			{ ENEMY_FILE_DATA_EM000, ENEMY_FILE_SET_EM000 }, // Unknown
			{ ENEMY_FILE_DATA_EM000, ENEMY_FILE_SET_EM000 }, // Unknown
			{ ENEMY_FILE_DATA_EM035, ENEMY_FILE_SET_EM035 }, // Vergil
			{ ENEMY_FILE_DATA_EM000, ENEMY_FILE_SET_EM000 }, // Unknown
			{ ENEMY_FILE_DATA_EM000, ENEMY_FILE_SET_EM000 }, // Unknown
			{ ENEMY_FILE_DATA_EM000, ENEMY_FILE_SET_EM000 }, // Unknown
			{ ENEMY_FILE_DATA_EM037, ENEMY_FILE_SET_EM037 }, // Jester
			{ ENEMY_FILE_DATA_EM000, ENEMY_FILE_SET_EM000 }, // Unknown
		};

		static_assert(countof(helpers) == ENEMY::COUNT);

		for_all(uint8, index, ENEMY::COUNT)
		{
			bool lastCondition = (index > 0);
			bool nextCondition = (index < (ENEMY::COUNT - 1));

			uint8 lastIndex = (lastCondition) ? (index - 1) : 0;
			uint8 nextIndex = (nextCondition) ? (index + 1) : 0;

			auto & metadata     = enemyFileDataMetadata[index    ];
			auto & lastMetadata = enemyFileDataMetadata[lastIndex];
			auto & nextMetadata = enemyFileDataMetadata[nextIndex];

			auto & helper = helpers[index];
			auto & fileDataIndex = helper.fileDataIndex;
			auto & fileSetIndex = helper.fileSetIndex;

			metadata.funcAddrs = (appBaseAddr + 0x4E3218);
			/*
			dmc3.exe+23F522 - 48 8D 05 EF3C2A00 - lea rax,[dmc3.exe+4E3218]
			dmc3.exe+23F529 - 48 89 01          - mov [rcx],rax
			*/

			metadata.lastAddr     = (lastCondition) ? &lastMetadata : 0;
			metadata.nextAddr     = (nextCondition) ? &nextMetadata : 0;
			metadata.fileDataAddr = &enemyFileData[fileDataIndex];
			metadata.category     = 5;
			metadata.fileSetIndex = fileSetIndex;
		}
	}

	if constexpr (debug)
	{
		Log("enemyFileData         %.16llX", enemyFileData);
		Log("enemyFileDataMetadata %.16llX", enemyFileDataMetadata);
	}






	// Demo Rebellion Motion File
	[&]()
	{
		const char * filename = "demo_pl000_00_3.pac";

		auto & file = demo_pl000_00_3 = File_staticFiles.Push(filename);
		if (!file)
		{
			return;
		}

		AdjustPointers(file);
	}();



	constexpr bool enable = true;
	static bool run = false;

	{
		auto addr     = (appBaseAddr + 0x2FDAC);
		auto jumpAddr = (appBaseAddr + 0x2FDB1);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+2FDA1 - 8D 56 01             - lea edx,[rsi+01]
		dmc3.exe+2FDA4 - 48 8D 8C 24 60010000 - lea rcx,[rsp+00000160]
		dmc3.exe+2FDAC - E8 7F762F00          - call dmc3.exe+327430
		dmc3.exe+2FDB1 - 48 89 45 08          - mov [rbp+08],rax
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rax
			0x8A, 0x00,                                                 // mov al,[rax]
			0x84, 0xC0,                                                 // test al,al
			0x74, 0x17,                                                 // je short
			0x48, 0x8D, 0x8C, 0x24, 0x60, 0x01, 0x00, 0x00,             // lea rcx,[rsp+00000160]
			0xBA, 0x00, 0x00, 0x00, 0x00,                               // mov edx
			0xE8, 0x00, 0x00, 0x00, 0x00,                               // call dmc3.exe+327430
			0x48, 0x85, 0xC0,                                           // test rax,rax
			0x75, 0x10,                                                 // jne short
			0x48, 0x8D, 0x8C, 0x24, 0x60, 0x01, 0x00, 0x00,             // lea rcx,[rsp+00000160]
			0x8D, 0x56, 0x01,                                           // lea edx,[rsi+01]
			0xE8, 0x00, 0x00, 0x00, 0x00,                               // call dmc3.exe+327430
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(0, jumpAddr, false, true, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			*reinterpret_cast<bool **>(func.sect0 + 2) = &activeConfig.preferLocalFiles;
			*reinterpret_cast<uint32 *>(func.sect0 + 0x18 + 1) = FILE_MODE_LOCAL;
			WriteCall((func.sect0 + 0x1D), (appBaseAddr + 0x327430));
			WriteCall((func.sect0 + 0x32), (appBaseAddr + 0x327430));
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	run = true;

	return true;
}

#ifdef __GARBAGE__
#endif
