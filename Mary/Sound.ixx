// @Todo: Move sound files to static files.

module;
#include "../Core/Core.h"

#include "Vars.h"
export module Sound;

import File;
import FMOD;
import Global;

#define debug true

enum
{
	ARCHIVE_METADATA_SIZE   = 8,
	HEAD_METADATA_SIZE      = 32,
	PROG_SECT_ITEM_SIZE     = 14,
	PROG_SECT_METADATA_SIZE = 8,
	PROG_METADATA_SIZE      = 16,
	SMPL_ITEM_SIZE          = 12,
	SMPL_METADATA_SIZE      = 16,
	VAGI_ITEM_SIZE          = 16,
	VAGI_METADATA_SIZE      = 16,
	WAVE_METADATA_SIZE      = 64,
	SOUND_DATA_SIZE         = 24,
	DBST_METADATA_SIZE      = 16,
	DBST_ITEM_SIZE          = 32,
};

enum
{
	CHANNEL_SYSTEM,
	CHANNEL_COMMON,
	CHANNEL_STYLE_WEAPON,
	CHANNEL_WEAPON1,
	CHANNEL_WEAPON2,
	CHANNEL_WEAPON3,
	CHANNEL_WEAPON4,
	CHANNEL_ENEMY,
	CHANNEL_ROOM,
	CHANNEL_MUSIC,
	CHANNEL_DEMO,
	MAX_CHANNEL = 16,
};

enum
{
	PROG_SECT_REBELLION,
	PROG_SECT_CERBERUS,
	PROG_SECT_AGNI_RUDRA,
	PROG_SECT_NEVAN,
	PROG_SECT_BEOWULF_DANTE,
	PROG_SECT_EBONY_IVORY,
	PROG_SECT_SHOTGUN,
	PROG_SECT_ARTEMIS,
	PROG_SECT_SPIRAL,
	PROG_SECT_KALINA_ANN,
	PROG_SECT_YAMATO = 11,
	PROG_SECT_BEOWULF_VERGIL,
	PROG_SECT_YAMATO_FORCE_EDGE,
	PROG_SECT_SWORDMASTER = 100,
	PROG_SECT_GUNSLINGER,
	PROG_SECT_TRICKSTER,
	PROG_SECT_ROYALGUARD,
	PROG_SECT_QUICKSILVER,
	PROG_SECT_DOPPELGANGER,
	PROG_SECT_BATTLE_OF_BROTHERS,
	PROG_SECT_DARK_SLAYER,
	MAX_PROG_SECT,
};

enum
{
	HELPER_COMMON_DANTE,
	HELPER_COMMON_VERGIL,
	HELPER_STYLE_WEAPON_DANTE,
	HELPER_STYLE_WEAPON_VERGIL,
	HELPER_COUNT,
};

constexpr uint32 g_sectCount[HELPER_COUNT] =
{
	3,
	3,
	108,
	108,
};

#define _(size) struct { byte8 Prep_Merge(padding_, __LINE__)[size]; }

#pragma pack(push, 1)

export struct ArchiveMetadata
{
	byte8 signature[4];
	uint32 fileCount;
	uint32 fileOffs[1];
};

export struct HeadMetadata
{
	byte8 signature[4];
	_(8);
	uint32 size;
	uint32 waveSize;
	uint32 progMetadataOff;
	uint32 smplMetadataOff;
	uint32 vagiMetadataOff;
};

export struct ProgSectItem
{
	_(12);
	uint16 smplItemIndex;
};

export struct ProgSectMetadata
{
	uint8 itemCount;
	_(7);
	ProgSectItem items[1];
};

export struct ProgMetadata
{
	byte8 signature[4];
	uint32 size;
	uint32 last;
	_(4);
	uint32 sectOffs[1];
};

export struct SmplItem
{
	_(10);
	uint16 vagiItemIndex;
};

export struct SmplMetadata
{
	byte8 signature[4];
	uint32 size;
	uint32 last;
	_(4);
	SmplItem items[1];
};

export struct VagiItem
{
	uint32 off;
	uint32 size;
	_(4);
	uint32 sampleRate;
};

export struct VagiMetadata
{
	byte8 signature[4];
	uint32 size;
	uint32 last;
	_(4);
	VagiItem items[1];
};

export struct WaveMetadata
{
	byte8 signature[4];
	_(8);
	uint32 reverseSize;
	_(16);
	char name[32];
};

export struct SoundData
{
	uint64 off;
	uint64 size;
	FMOD_SOUND * fmodSoundAddr;
};

export struct DbstMetadata
{
	byte8 signature[4];
	_(4);
	uint32 size;
	_(4);
};

#pragma pack(pop)

#undef _



bool IsArchive(byte8 * addr)
{
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

bool IsHead(byte8 * addr)
{
	constexpr byte8 signature[] = { 'H', 'e', 'a', 'd', };

	return SignatureMatch(addr, signature);
}

bool IsProg(byte8 * addr)
{
	constexpr byte8 signature[] = { 'P', 'r', 'o', 'g', };

	return SignatureMatch(addr, signature);
}

bool IsSmpl(byte8 * addr)
{
	constexpr byte8 signature[] = { 'S', 'm', 'p', 'l', };

	return SignatureMatch(addr, signature);
}

bool IsVagi(byte8 * addr)
{
	constexpr byte8 signature[] = { 'V', 'a', 'g', 'i', };

	return SignatureMatch(addr, signature);
}

bool IsWave(byte8 * addr)
{
	constexpr byte8 signature[] = { 'V', 'A', 'G', 'p', };

	return SignatureMatch(addr, signature);
}

bool IsDbst(byte8 * addr)
{
	constexpr byte8 signature[] = { 'd', 'b', 's', 'T', };

	return SignatureMatch(addr, signature);
}






struct HeadHelper
{
	byte8 * dataAddr;
	uint32 pos;
	uint32 count;

	bool Init(uint32 dataSize);

	void Push
	(
		void * addr,
		uint32 size
	);
};

bool HeadHelper::Init(uint32 dataSize)
{
	LogFunction();

	dataAddr = Alloc(dataSize);
	if (!dataAddr)
	{
		Log("Alloc failed.");

		return false;
	}

	auto & headMetadata = *reinterpret_cast<HeadMetadata *>(dataAddr);

	headMetadata.signature[0] = 'H';
	headMetadata.signature[1] = 'e';
	headMetadata.signature[2] = 'a';
	headMetadata.signature[3] = 'd';

	pos = HEAD_METADATA_SIZE;

	return true;
}

void HeadHelper::Push
(
	void * addr,
	uint32 size
)
{
	LogFunction();

	CopyMemory
	(
		(dataAddr + pos),
		addr,
		size
	);

	pos += size;

	Log("pos %X", pos);

	Align<uint32>
	(
		pos,
		0x10,
		dataAddr,
		0xFF
	);

	Log("pos %X", pos);
}

struct ProgHelper
{
	byte8 * dataAddr;
	uint32 pos;
	uint32 count;

	bool Init
	(
		uint32 dataSize,
		uint32 sectCount
	);

	void Push
	(
		ProgSectMetadata & progSectMetadata,
		uint16 smplItemCount,
		uint8 sectIndex
	);

	ProgSectMetadata & operator[](uint8 sectIndex);
};

bool ProgHelper::Init
(
	uint32 dataSize,
	uint32 sectCount
)
{
	LogFunction();

	dataAddr = Alloc(dataSize);
	if (!dataAddr)
	{
		Log("Alloc failed.");

		return false;
	}

	auto & progMetadata = *reinterpret_cast<ProgMetadata *>(dataAddr);

	progMetadata.signature[0] = 'P';
	progMetadata.signature[1] = 'r';
	progMetadata.signature[2] = 'o';
	progMetadata.signature[3] = 'g';

	pos = PROG_METADATA_SIZE;

	if (sectCount > 0)
	{
		progMetadata.last = (sectCount - 1);

		uint32 size = (sectCount * 4);

		SetMemory
		(
			progMetadata.sectOffs,
			0xFF,
			size
		);

		pos += size;
	}

	return true;
}

void ProgHelper::Push
(
	ProgSectMetadata & progSectMetadata,
	uint16 smplItemCount,
	uint8 sectIndex
)
{
	LogFunction();

	auto & progMetadata = *reinterpret_cast<ProgMetadata *>(dataAddr);

	auto & progSectMetadata2 = *reinterpret_cast<ProgSectMetadata *>(dataAddr + pos);

	uint32 size = (PROG_SECT_METADATA_SIZE + (PROG_SECT_ITEM_SIZE * progSectMetadata.itemCount));

	CopyMemory
	(
		&progSectMetadata2,
		&progSectMetadata,
		size
	);

	for_all(uint8, itemIndex, progSectMetadata2.itemCount)
	{
		auto & item = progSectMetadata2.items[itemIndex];

		item.smplItemIndex += smplItemCount;
	}

	progMetadata.sectOffs[sectIndex] = pos;

	pos += size;
	count++;

	progMetadata.size = pos;
}

ProgSectMetadata & ProgHelper::operator[](uint8 sectIndex)
{
	auto & progMetadata = *reinterpret_cast<ProgMetadata *>(dataAddr);

	return *reinterpret_cast<ProgSectMetadata *>(dataAddr + progMetadata.sectOffs[sectIndex]);
}

struct SmplHelper
{
	byte8 * dataAddr;
	uint32 pos;
	uint32 count;

	bool Init(uint32 dataSize);

	void Push
	(
		SmplItem & smplItem,
		uint16 vagiItemCount
	);

	SmplItem & operator[](uint8 itemIndex);
};

bool SmplHelper::Init(uint32 dataSize)
{
	LogFunction();

	dataAddr = Alloc(dataSize);
	if (!dataAddr)
	{
		Log("Alloc failed.");

		return false;
	}

	auto & smplMetadata = *reinterpret_cast<SmplMetadata *>(dataAddr);

	smplMetadata.signature[0] = 'S';
	smplMetadata.signature[1] = 'm';
	smplMetadata.signature[2] = 'p';
	smplMetadata.signature[3] = 'l';

	pos = SMPL_METADATA_SIZE;

	return true;
}

void SmplHelper::Push
(
	SmplItem & smplItem,
	uint16 vagiItemCount
)
{
	LogFunction();

	auto & smplMetadata = *reinterpret_cast<SmplMetadata *>(dataAddr);

	auto & smplItem2 = *reinterpret_cast<SmplItem *>(dataAddr + pos);

	constexpr uint32 size = SMPL_ITEM_SIZE;

	CopyMemory
	(
		&smplItem2,
		&smplItem,
		size
	);

	smplItem2.vagiItemIndex += vagiItemCount;

	smplMetadata.last = count;

	pos += size;
	count++;

	smplMetadata.size = pos;
}

SmplItem & SmplHelper::operator[](uint8 itemIndex)
{
	return reinterpret_cast<SmplItem *>(dataAddr + SMPL_METADATA_SIZE)[itemIndex];
}

struct VagiHelper
{
	byte8 * dataAddr;
	uint32 pos;
	uint32 count;

	bool Init(uint32 dataSize);

	void Push(VagiItem & vagiItem);

	VagiItem & operator[](uint32 itemIndex);

	void UpdateOffsets();
};

bool VagiHelper::Init(uint32 dataSize)
{
	LogFunction();

	dataAddr = Alloc(dataSize);
	if (!dataAddr)
	{
		Log("Alloc failed.");

		return false;
	}

	auto & vagiMetadata = *reinterpret_cast<VagiMetadata *>(dataAddr);

	vagiMetadata.signature[0] = 'V';
	vagiMetadata.signature[1] = 'a';
	vagiMetadata.signature[2] = 'g';
	vagiMetadata.signature[3] = 'i';

	pos = VAGI_METADATA_SIZE;

	return true;
}

void VagiHelper::Push(VagiItem & vagiItem)
{
	LogFunction();

	auto & vagiMetadata = *reinterpret_cast<VagiMetadata *>(dataAddr);

	auto & vagiItem2 = *reinterpret_cast<VagiItem *>(dataAddr + pos);

	constexpr uint32 size = VAGI_ITEM_SIZE;

	CopyMemory
	(
		&vagiItem2,
		&vagiItem,
		size
	);

	vagiItem2.off = 0;

	vagiMetadata.last = count;

	pos += size;
	count++;

	vagiMetadata.size = pos;
}

VagiItem & VagiHelper::operator[](uint32 itemIndex)
{
	return reinterpret_cast<VagiItem *>(dataAddr + VAGI_METADATA_SIZE)[itemIndex];
}

void VagiHelper::UpdateOffsets()
{
	LogFunction();

	uint32 off = 0;

	for_all(uint32, itemIndex, count)
	{
		auto & item = (*this)[itemIndex];

		item.off = off;

		off += item.size;

		Log("off %X", item.off);
	}
}

struct WaveHelper
{
	struct Metadata
	{
		uint32 off;
	};

	byte8 * dataAddr;
	uint32 pos;
	uint32 count;
	Metadata * metadataAddr;

	bool Init
	(
		uint32 dataSize,
		uint32 metadataSize
	);

	void Push
	(
		byte8 * wave,
		uint32 size
	);

	WaveMetadata & operator[](uint32 index);
};

bool WaveHelper::Init
(
	uint32 dataSize,
	uint32 metadataSize
)
{
	LogFunction();

	dataAddr = Alloc(dataSize);
	if (!dataAddr)
	{
		Log("Alloc failed.");

		return false;
	}

	metadataAddr = reinterpret_cast<Metadata *>(Alloc(metadataSize));
	if (!metadataAddr)
	{
		Log("Alloc failed.");

		return false;
	}

	return true;
}

void WaveHelper::Push
(
	byte8 * wave,
	uint32 size
)
{
	LogFunction();

	CopyMemory
	(
		(dataAddr + pos),
		wave,
		size
	);

	auto & metadata = metadataAddr[count];

	metadata.off = pos;

	pos += size;
	count++;
}

WaveMetadata & WaveHelper::operator[](uint32 index)
{
	auto & metadata = metadataAddr[index];

	return *reinterpret_cast<WaveMetadata *>(dataAddr + metadata.off);
}

struct SoundHelper
{
	byte8 * dataAddr;
	uint32 pos;
	uint32 count;

	bool Init(uint32 dataSize);

	void Push(SoundData & soundData);

	SoundData & operator[](uint32 index);
};

bool SoundHelper::Init(uint32 dataSize)
{
	LogFunction();

	dataAddr = Alloc(dataSize);
	if (!dataAddr)
	{
		Log("Alloc failed.");

		return false;
	}

	return true;
}

void SoundHelper::Push(SoundData & soundData)
{
	LogFunction();

	constexpr uint32 size = SOUND_DATA_SIZE;

	CopyMemory
	(
		(dataAddr + pos),
		&soundData,
		size
	);

	pos += size;
	count++;
}

SoundData & SoundHelper::operator[](uint32 index)
{
	return reinterpret_cast<SoundData *>(dataAddr)[index];
}

struct DbstHelper
{
	byte8 * dataAddr;
	uint32 pos;
	uint32 count;

	bool Init(uint32 dataSize);

	void Push(DbstMetadata & soundData);

	DbstMetadata & operator[](uint32 index);
};

bool DbstHelper::Init(uint32 dataSize)
{
	LogFunction();

	dataAddr = Alloc(dataSize);
	if (!dataAddr)
	{
		Log("Alloc failed.");

		return false;
	}

	return true;
}

void DbstHelper::Push(DbstMetadata & dbstMetadata)
{
	LogFunction();

	auto size = (dbstMetadata.size + DBST_METADATA_SIZE);

	CopyMemory
	(
		(dataAddr + pos),
		&dbstMetadata,
		size
	);

	pos += size;
	count++;
}

DbstMetadata & DbstHelper::operator[](uint32 index)
{
	return reinterpret_cast<DbstMetadata *>(dataAddr)[index];
}

HeadHelper  g_headHelper [HELPER_COUNT] = {};
ProgHelper  g_progHelper [HELPER_COUNT] = {};
SmplHelper  g_smplHelper [HELPER_COUNT] = {};
VagiHelper  g_vagiHelper [HELPER_COUNT] = {};
WaveHelper  g_waveHelper [HELPER_COUNT] = {};
SoundHelper g_soundHelper[HELPER_COUNT] = {};
DbstHelper  g_dbstHelper [HELPER_COUNT] = {};

void Decompile
(
	byte8 * archive,
	uint8 helperIndex
)
{
	LogFunction();

	auto & headHelper  = g_headHelper [helperIndex];
	auto & progHelper  = g_progHelper [helperIndex];
	auto & smplHelper  = g_smplHelper [helperIndex];
	auto & vagiHelper  = g_vagiHelper [helperIndex];
	auto & waveHelper  = g_waveHelper [helperIndex];
	auto & soundHelper = g_soundHelper[helperIndex];
	auto & dbstHelper  = g_dbstHelper [helperIndex];

	Log("archive %llX", archive);

	if (!IsArchive(archive))
	{
		Log("IsArchive failed.");

		return;
	}

	auto & archiveMetadata = *reinterpret_cast<ArchiveMetadata *>(archive);

	uint32 waveCount = 0;

	for_all(uint32, fileIndex, archiveMetadata.fileCount)
	{
		auto & fileOff = archiveMetadata.fileOffs[fileIndex];
		auto file = reinterpret_cast<byte8 *>(archive + fileOff);

		Log("fileIndex %u", fileIndex);
		Log("fileOff %X", fileOff);
		Log("file %llX", file);

		if (IsHead(file))
		{
			auto headMetadataAddr = file;
			auto & headMetadata = *reinterpret_cast<HeadMetadata *>(headMetadataAddr);

			Log("Head");
			Log("headMetadataAddr %llX", headMetadataAddr);

			auto progMetadataAddr = (file + headMetadata.progMetadataOff);

			if (IsProg(progMetadataAddr))
			{
				auto & progMetadata = *reinterpret_cast<ProgMetadata *>(progMetadataAddr);

				Log("Prog");
				Log("progMetadataAddr %llX", progMetadataAddr);
				Log("size %X", progMetadata.size);
				Log("last %u", progMetadata.last);

				auto sectCount = static_cast<uint8>(progMetadata.last + 1);

				Log("sectCount %u", sectCount);

				for_all(uint8, sectIndex, sectCount)
				{
					auto & sectOff = progMetadata.sectOffs[sectIndex];
					if (sectOff == 0xFFFFFFFF)
					{
						continue;
					}

					Log("sectOff %X", sectOff);

					auto progSectMetadataAddr = (progMetadataAddr + sectOff);
					auto & progSectMetadata = *reinterpret_cast<ProgSectMetadata *>(progSectMetadataAddr);

					Log("ProgSectMetadata");
					Log("progSectMetadataAddr %llX", progSectMetadataAddr);
					Log("itemCount %u", progSectMetadata.itemCount);

					progHelper.Push
					(
						progSectMetadata,
						static_cast<uint16>(smplHelper.count),
						sectIndex
					);
				}
			}

			auto smplMetadataAddr = (file + headMetadata.smplMetadataOff);

			if (IsSmpl(smplMetadataAddr))
			{
				auto & smplMetadata = *reinterpret_cast<SmplMetadata *>(smplMetadataAddr);

				Log("Smpl");
				Log("smplMetadataAddr %llX", smplMetadataAddr);
				Log("size %X", smplMetadata.size);
				Log("last %u", smplMetadata.last);

				auto itemCount = (smplMetadata.last + 1);

				Log("itemCount %u", itemCount);

				for_all(uint32, itemIndex, itemCount)
				{
					auto & item = smplMetadata.items[itemIndex];

					smplHelper.Push
					(
						item,
						static_cast<uint16>(vagiHelper.count)
					);
				}
			}

			auto vagiMetadataAddr = (file + headMetadata.vagiMetadataOff);

			if (IsVagi(vagiMetadataAddr))
			{
				auto & vagiMetadata = *reinterpret_cast<VagiMetadata *>(vagiMetadataAddr);

				Log("Vagi");
				Log("vagiMetadataAddr %llX", vagiMetadataAddr);
				Log("size %X", vagiMetadata.size);
				Log("last %u", vagiMetadata.last);

				auto itemCount = (vagiMetadata.last + 1);

				waveCount = itemCount;

				Log("itemCount %u", itemCount);

				for_all(uint32, itemIndex, itemCount)
				{
					auto & item = vagiMetadata.items[itemIndex];

					vagiHelper.Push(item);
				}
			}
		}
		else if (IsWave(file))
		{
			Log("Wave");
			Log("waveCount %u", waveCount);

			uint32 pos = 0;

			for_all(uint32, waveIndex, waveCount)
			{
				auto wave = (file + pos);

				if (!IsWave(wave))
				{
					continue;
				}

				auto & waveMetadata = *reinterpret_cast<WaveMetadata *>(wave);

				auto size = (Reverse(&waveMetadata.reverseSize) + 0x30);

				Log("size %X", size);

				waveHelper.Push
				(
					wave,
					size
				);

				pos += size;
			}
		}
		else if (IsDbst(file))
		{
			Log("Dbst");

			auto dbstMetadataAddr = file;
			auto & dbstMetadata = *reinterpret_cast<DbstMetadata *>(dbstMetadataAddr);

			dbstHelper.Push(dbstMetadata);
		}
	}
}



void Compile(uint8 helperIndex)
{
	LogFunction();

	auto & headHelper  = g_headHelper [helperIndex];
	auto & progHelper  = g_progHelper [helperIndex];
	auto & smplHelper  = g_smplHelper [helperIndex];
	auto & vagiHelper  = g_vagiHelper [helperIndex];
	auto & waveHelper  = g_waveHelper [helperIndex];
	auto & soundHelper = g_soundHelper[helperIndex];
	auto & dbstHelper  = g_dbstHelper [helperIndex];

	auto & headMetadata = *reinterpret_cast<HeadMetadata *>(headHelper.dataAddr);

	headMetadata.progMetadataOff = headHelper.pos;

	headHelper.Push
	(
		progHelper.dataAddr,
		progHelper.pos
	);

	headMetadata.smplMetadataOff = headHelper.pos;

	headHelper.Push
	(
		smplHelper.dataAddr,
		smplHelper.pos
	);

	headMetadata.vagiMetadataOff = headHelper.pos;

	headHelper.Push
	(
		vagiHelper.dataAddr,
		vagiHelper.pos
	);

	headMetadata.size = headHelper.pos;

	if (vagiHelper.count != waveHelper.count)
	{
		Log("Count mismatch.");

		return;
	}

	uint32 off = 0;

	for_all(uint32, index, waveHelper.count)
	{
		auto & vagiItem = vagiHelper[index];
		auto & waveMetadata = waveHelper[index];

		auto waveSize = (Reverse(&waveMetadata.reverseSize) + 0x30);

		auto fmodSystem = *reinterpret_cast<FMOD_SYSTEM **>(appBaseAddr + 0x5DE3D0);
		/*
		dmc3.exe+32255 - 48 8B 0D 74C15A00 - mov rcx,[dmc3.exe+5DE3D0]
		*/

		FMOD_CREATESOUNDEXINFO fmodCreateSoundExInfo = {};
		fmodCreateSoundExInfo.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
		fmodCreateSoundExInfo.length = waveSize;

		SoundData soundData = {};
		soundData.off = off;
		soundData.size = vagiItem.size;

		auto result = FMOD_System_CreateSound
		(
			fmodSystem,
			&waveMetadata,
			FMOD_CREATECOMPRESSEDSAMPLE |
			FMOD_OPENMEMORY |
			FMOD_LOWMEM,
			&fmodCreateSoundExInfo,
			&soundData.fmodSoundAddr
		);

		if (result != FMOD_OK)
		{
			Log("FMOD_System_CreateSound failed. %X", result);

			return;
		}

		soundHelper.Push(soundData);

		off += vagiItem.size;
	}
}



void ProcessSoundFiles()
{
	LogFunction();

	// Common Dante
	{
		Log("Common Dante");

		constexpr uint8 helperIndex = HELPER_COMMON_DANTE;

		auto & headHelper  = g_headHelper [helperIndex];
		auto & progHelper  = g_progHelper [helperIndex];
		auto & smplHelper  = g_smplHelper [helperIndex];
		auto & vagiHelper  = g_vagiHelper [helperIndex];
		auto & waveHelper  = g_waveHelper [helperIndex];
		auto & soundHelper = g_soundHelper[helperIndex];
		auto & dbstHelper  = g_dbstHelper [helperIndex];

		auto filename = "snd_com0.pac";

		byte8 * file = 0;
		uint32 fileSize = 0;

		file = File_LoadFile(filename, &fileSize);
		if (!file)
		{
			Log("File_LoadFile failed. %s", filename);

			return;
		}

		Log(filename);

		Decompile(file, helperIndex);

		vagiHelper.UpdateOffsets();

		Log("progHelper");
		Log("dataAddr %llX", progHelper.dataAddr);
		Log("pos      %X", progHelper.pos);
		Log("count    %u", progHelper.count);

		Log("smplHelper");
		Log("dataAddr %llX", smplHelper.dataAddr);
		Log("pos      %X", smplHelper.pos);
		Log("count    %u", smplHelper.count);

		Log("vagiHelper");
		Log("dataAddr %llX", vagiHelper.dataAddr);
		Log("pos      %X", vagiHelper.pos);
		Log("count    %u", vagiHelper.count);

		Log("waveHelper");
		Log("dataAddr %llX", waveHelper.dataAddr);
		Log("pos      %X", waveHelper.pos);
		Log("count    %u", waveHelper.count);

		Log("dbstHelper");
		Log("dataAddr %llX", dbstHelper.dataAddr);
		Log("pos      %X", dbstHelper.pos);
		Log("count    %u", dbstHelper.count);

		Compile(helperIndex);

		Log("headHelper");
		Log("dataAddr %llX", headHelper.dataAddr);
		Log("pos      %X", headHelper.pos);
		Log("count    %u", headHelper.count);

		Log("soundHelper");
		Log("dataAddr %llX", soundHelper.dataAddr);
		Log("pos      %X", soundHelper.pos);
		Log("count    %u", soundHelper.count);
	}

	// Common Vergil
	{
		Log("Common Vergil");

		constexpr uint8 helperIndex = HELPER_COMMON_VERGIL;

		auto & headHelper  = g_headHelper [helperIndex];
		auto & progHelper  = g_progHelper [helperIndex];
		auto & smplHelper  = g_smplHelper [helperIndex];
		auto & vagiHelper  = g_vagiHelper [helperIndex];
		auto & waveHelper  = g_waveHelper [helperIndex];
		auto & soundHelper = g_soundHelper[helperIndex];
		auto & dbstHelper  = g_dbstHelper [helperIndex];

		auto filename = "snd_com3.pac";

		byte8 * file = 0;
		uint32 fileSize = 0;

		file = File_LoadFile(filename, &fileSize);
		if (!file)
		{
			Log("File_LoadFile failed. %s", filename);

			return;
		}

		Log(filename);

		Decompile(file, helperIndex);

		vagiHelper.UpdateOffsets();

		Log("progHelper");
		Log("dataAddr %llX", progHelper.dataAddr);
		Log("pos      %X", progHelper.pos);
		Log("count    %u", progHelper.count);

		Log("smplHelper");
		Log("dataAddr %llX", smplHelper.dataAddr);
		Log("pos      %X", smplHelper.pos);
		Log("count    %u", smplHelper.count);

		Log("vagiHelper");
		Log("dataAddr %llX", vagiHelper.dataAddr);
		Log("pos      %X", vagiHelper.pos);
		Log("count    %u", vagiHelper.count);

		Log("waveHelper");
		Log("dataAddr %llX", waveHelper.dataAddr);
		Log("pos      %X", waveHelper.pos);
		Log("count    %u", waveHelper.count);

		Log("dbstHelper");
		Log("dataAddr %llX", dbstHelper.dataAddr);
		Log("pos      %X", dbstHelper.pos);
		Log("count    %u", dbstHelper.count);

		Compile(helperIndex);

		Log("headHelper");
		Log("dataAddr %llX", headHelper.dataAddr);
		Log("pos      %X", headHelper.pos);
		Log("count    %u", headHelper.count);

		Log("soundHelper");
		Log("dataAddr %llX", soundHelper.dataAddr);
		Log("pos      %X", soundHelper.pos);
		Log("count    %u", soundHelper.count);
	}

	// Style Weapon Dante
	{
		Log("Style Weapon Dante");

		constexpr uint8 helperIndex = HELPER_STYLE_WEAPON_DANTE;

		auto & headHelper  = g_headHelper [helperIndex];
		auto & progHelper  = g_progHelper [helperIndex];
		auto & smplHelper  = g_smplHelper [helperIndex];
		auto & vagiHelper  = g_vagiHelper [helperIndex];
		auto & waveHelper  = g_waveHelper [helperIndex];
		auto & soundHelper = g_soundHelper[helperIndex];
		auto & dbstHelper  = g_dbstHelper [helperIndex];

		const char * filenames[] =
		{
			"snd_sty02.pac",
			"snd_sty03.pac",
			"snd_sty04.pac",
			"snd_sty05.pac",
			//"snd_sty06.pac",
			"snd_wp00b.pac",
			"snd_wp01b.pac",
			"snd_wp02b.pac",
			"snd_wp03b.pac",
			"snd_wp04b.pac",
			"snd_wp05b.pac",
			"snd_wp06b.pac",
			"snd_wp07b.pac",
			"snd_wp08b.pac",
			"snd_wp09b.pac",
		};

		for_all(uint8, fileIndex, countof(filenames))
		{
			auto filename = filenames[fileIndex];

			byte8 * file = 0;
			uint32 fileSize = 0;

			file = File_LoadFile(filename, &fileSize);
			if (!file)
			{
				Log("File_LoadFile failed. %s", filename);

				return;
			}

			Log(filename);

			Decompile(file, helperIndex);
		}

		vagiHelper.UpdateOffsets();

		Log("progHelper");
		Log("dataAddr %llX", progHelper.dataAddr);
		Log("pos      %X", progHelper.pos);
		Log("count    %u", progHelper.count);

		Log("smplHelper");
		Log("dataAddr %llX", smplHelper.dataAddr);
		Log("pos      %X", smplHelper.pos);
		Log("count    %u", smplHelper.count);

		Log("vagiHelper");
		Log("dataAddr %llX", vagiHelper.dataAddr);
		Log("pos      %X", vagiHelper.pos);
		Log("count    %u", vagiHelper.count);

		Log("waveHelper");
		Log("dataAddr %llX", waveHelper.dataAddr);
		Log("pos      %X", waveHelper.pos);
		Log("count    %u", waveHelper.count);

		Log("dbstHelper");
		Log("dataAddr %llX", dbstHelper.dataAddr);
		Log("pos      %X", dbstHelper.pos);
		Log("count    %u", dbstHelper.count);

		Compile(helperIndex);

		Log("headHelper");
		Log("dataAddr %llX", headHelper.dataAddr);
		Log("pos      %X", headHelper.pos);
		Log("count    %u", headHelper.count);

		Log("soundHelper");
		Log("dataAddr %llX", soundHelper.dataAddr);
		Log("pos      %X", soundHelper.pos);
		Log("count    %u", soundHelper.count);
	}

	// Style Weapon Vergil
	{
		Log("Style Weapon Vergil");

		constexpr uint8 helperIndex = HELPER_STYLE_WEAPON_VERGIL;

		auto & headHelper  = g_headHelper [helperIndex];
		auto & progHelper  = g_progHelper [helperIndex];
		auto & smplHelper  = g_smplHelper [helperIndex];
		auto & vagiHelper  = g_vagiHelper [helperIndex];
		auto & waveHelper  = g_waveHelper [helperIndex];
		auto & soundHelper = g_soundHelper[helperIndex];
		auto & dbstHelper  = g_dbstHelper [helperIndex];

		const char * filenames[] =
		{
			// "snd_sty04.pac",
			// "snd_sty05.pac",
			// "snd_sty06.pac",
			"snd_sty07.pac",
			"snd_wp11a.pac",
			"snd_wp12a.pac",
			"snd_wp13a.pac",
		};

		for_all(uint8, fileIndex, countof(filenames))
		{
			auto filename = filenames[fileIndex];

			byte8 * file = 0;
			uint32 fileSize = 0;

			file = File_LoadFile(filename, &fileSize);
			if (!file)
			{
				Log("File_LoadFile failed. %s", filename);

				return;
			}

			Log(filename);

			Decompile(file, helperIndex);
		}

		vagiHelper.UpdateOffsets();

		Log("progHelper");
		Log("dataAddr %llX", progHelper.dataAddr);
		Log("pos      %X", progHelper.pos);
		Log("count    %u", progHelper.count);

		Log("smplHelper");
		Log("dataAddr %llX", smplHelper.dataAddr);
		Log("pos      %X", smplHelper.pos);
		Log("count    %u", smplHelper.count);

		Log("vagiHelper");
		Log("dataAddr %llX", vagiHelper.dataAddr);
		Log("pos      %X", vagiHelper.pos);
		Log("count    %u", vagiHelper.count);

		Log("waveHelper");
		Log("dataAddr %llX", waveHelper.dataAddr);
		Log("pos      %X", waveHelper.pos);
		Log("count    %u", waveHelper.count);

		Log("dbstHelper");
		Log("dataAddr %llX", dbstHelper.dataAddr);
		Log("pos      %X", dbstHelper.pos);
		Log("count    %u", dbstHelper.count);

		Compile(helperIndex);

		Log("headHelper");
		Log("dataAddr %llX", headHelper.dataAddr);
		Log("pos      %X", headHelper.pos);
		Log("count    %u", headHelper.count);

		Log("soundHelper");
		Log("dataAddr %llX", soundHelper.dataAddr);
		Log("pos      %X", soundHelper.pos);
		Log("count    %u", soundHelper.count);
	}
}






byte8 * GetHeadMetadataAddress
(
	uint32 channelIndex,
	byte8 * addr
)
{
	LogFunction();

	switch (channelIndex)
	{
		case CHANNEL_COMMON:
		{
			switch (g_character)
			{
				case CHAR_DANTE:
				{
					return g_headHelper[HELPER_COMMON_DANTE].dataAddr;
				}
				case CHAR_VERGIL:
				{
					return g_headHelper[HELPER_COMMON_VERGIL].dataAddr;
				}
			}

			break;
		}
		case CHANNEL_STYLE_WEAPON:
		{
			switch (g_character)
			{
				case CHAR_DANTE:
				{
					return g_headHelper[HELPER_STYLE_WEAPON_DANTE].dataAddr;
				}
				case CHAR_VERGIL:
				{
					return g_headHelper[HELPER_STYLE_WEAPON_VERGIL].dataAddr;
				}
			}

			break;
		}
	}

	return addr;
}

uint64 GetChannelOffset
(
	uint32 channelIndex,
	uint64 off
)
{
	switch (channelIndex)
	{
		case CHANNEL_COMMON:
		case CHANNEL_STYLE_WEAPON:
		{
			return 0;
		}
	}

	return off;
}

uint32 GetSoundDataCount
(
	byte8 * addr,
	uint32 count
)
{
	auto & channelIndex = *reinterpret_cast<uint8 *>(addr + 0xC);

	switch (channelIndex)
	{
		case CHANNEL_COMMON:
		{
			switch (g_character)
			{
				case CHAR_DANTE:
				{
					return g_soundHelper[HELPER_COMMON_DANTE].count;
				}
				case CHAR_VERGIL:
				{
					return g_soundHelper[HELPER_COMMON_VERGIL].count;
				}
			}

			break;
		}
		case CHANNEL_STYLE_WEAPON:
		{
			switch (g_character)
			{
				case CHAR_DANTE:
				{
					return g_soundHelper[HELPER_STYLE_WEAPON_DANTE].count;
				}
				case CHAR_VERGIL:
				{
					return g_soundHelper[HELPER_STYLE_WEAPON_VERGIL].count;
				}
			}

			break;
		}
	}

	return count;
}

byte8 * GetSoundDataAddress
(
	byte8 * addr,
	byte8 * dataAddr
)
{
	auto & channelIndex = *reinterpret_cast<uint8 *>(addr + 0xC);

	switch (channelIndex)
	{
		case CHANNEL_COMMON:
		{
			switch (g_character)
			{
				case CHAR_DANTE:
				{
					return g_soundHelper[HELPER_COMMON_DANTE].dataAddr;
				}
				case CHAR_VERGIL:
				{
					return g_soundHelper[HELPER_COMMON_VERGIL].dataAddr;
				}
			}

			break;
		}
		case CHANNEL_STYLE_WEAPON:
		{
			switch (g_character)
			{
				case CHAR_DANTE:
				{
					return g_soundHelper[HELPER_STYLE_WEAPON_DANTE].dataAddr;
				}
				case CHAR_VERGIL:
				{
					return g_soundHelper[HELPER_STYLE_WEAPON_VERGIL].dataAddr;
				}
			}

			break;
		}
	}

	return dataAddr;
}





// @Todo: Rename to Item.
byte8 * GetDbstMetadataAddress
(
	uint32 channelIndex,
	uint32 itemIndex,
	byte8 * addr // @Research: defaultAddr.
)
{
	LogFunction();

	byte8 * dest = 0;

	uint32 off = (DBST_METADATA_SIZE + (itemIndex * DBST_ITEM_SIZE));

	switch (channelIndex)
	{
		case CHANNEL_COMMON:
		{
			switch (g_character)
			{
				case CHAR_DANTE:
				{
					dest = g_dbstHelper[HELPER_COMMON_DANTE].dataAddr;

					break;
				}
				case CHAR_VERGIL:
				{
					dest = g_dbstHelper[HELPER_COMMON_VERGIL].dataAddr;

					break;
				}
			}

			break;
		}
		case CHANNEL_STYLE_WEAPON:
		{
			switch (g_character)
			{
				case CHAR_DANTE:
				{
					dest = reinterpret_cast<byte8 *>(&g_dbstHelper[HELPER_STYLE_WEAPON_DANTE][0]);

					break;
				}
				case CHAR_VERGIL:
				{
					dest = reinterpret_cast<byte8 *>(&g_dbstHelper[HELPER_STYLE_WEAPON_VERGIL][0]);

					break;
				}
			}

			break;
		}
	}

	if (!dest)
	{
		return addr;
	}

	return (dest + off);
}







export void Sound_Toggle(bool enable)
{
	LogFunction(enable);

	static bool run = false;

	if (!run)
	{
		for_all(uint8, helperIndex, HELPER_COUNT)
		{
			Log("helperIndex %u", helperIndex);

			auto & headHelper  = g_headHelper [helperIndex];
			auto & progHelper  = g_progHelper [helperIndex];
			auto & smplHelper  = g_smplHelper [helperIndex];
			auto & vagiHelper  = g_vagiHelper [helperIndex];
			auto & waveHelper  = g_waveHelper [helperIndex];
			auto & soundHelper = g_soundHelper[helperIndex];
			auto & dbstHelper  = g_dbstHelper [helperIndex];

			if (!headHelper.Init(1 * 1024 * 1024))
			{
				Log("headHelper.Init failed.");

				return;
			}
			else if
			(
				!progHelper.Init
				(
					(1 * 1024 * 1024),
					g_sectCount[helperIndex]
				)
			)
			{
				Log("progHelper.Init failed.");

				return;
			}
			else if (!smplHelper.Init(1 * 1024 * 1024))
			{
				Log("smplHelper.Init failed.");

				return;
			}
			else if (!vagiHelper.Init(1 * 1024 * 1024))
			{
				Log("vagiHelper.Init failed.");

				return;
			}
			else if
			(
				!waveHelper.Init
				(
					(8 * 1024 * 1024),
					8192
				)
			)
			{
				Log("waveHelper.Init failed.");

				return;
			}
			else if (!soundHelper.Init(1 * 1024 * 1024))
			{
				Log("soundHelper.Init failed.");

				return;
			}
			else if (!dbstHelper.Init(1 * 1024 * 1024))
			{
				Log("dbstHelper.Init failed.");

				return;
			}
		}
	}

	// FMOD Init Complete
	{
		auto addr = (appBaseAddr + 0x32901);
		/*
		dmc3.exe+32901 - C3 - ret
		dmc3.exe+32902 - CC - int 3
		dmc3.exe+32903 - CC - int 3
		dmc3.exe+32904 - CC - int 3
		dmc3.exe+32905 - CC - int 3
		*/

		static Function func = {};

		constexpr uint32 size0 = 5;

		if (!run)
		{
			func = CreateFunction(ProcessSoundFiles);
			backupHelper.Save(addr, size0);
		}

		if (enable)
		{
			WriteJump(addr, func.addr);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Get Head Metadata Address
	{
		auto addr     = (appBaseAddr + 0x33A35B);
		auto jumpAddr = (appBaseAddr + 0x33A360);
		/*
		dmc3.exe+33A35B - E8 40FBFFFF - call dmc3.exe+339EA0
		dmc3.exe+33A360 - 40 0FB6 D5  - movzx edx,bpl
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_ecx_r15d,
			mov_rdx_rax,
		};
		constexpr uint32 size0 = 5;
		constexpr uint32 size1 = sizeof(sect1);

		if (!run)
		{
			func = CreateFunction(GetHeadMetadataAddress, jumpAddr, true, false, size0, size1);
			CopyMemory(func.sect0, addr, size0, MemoryFlags_VirtualProtectSource);
			CopyMemory(func.sect1, sect1, size1);
			WriteCall(func.sect0, (appBaseAddr + 0x339EA0));
			backupHelper.Save(addr, size0);
		}

		if (enable)
		{
			WriteJump(addr, func.addr);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Get Channel Offset
	{
		auto addr     = (appBaseAddr + 0x33A3A1);
		auto jumpAddr = (appBaseAddr + 0x33A3A6);
		/*
		dmc3.exe+33A3A1 - E8 EAFAFFFF   - call dmc3.exe+339E90
		dmc3.exe+33A3A6 - 44 0FB6 47 05 - movzx r8d,byte ptr [rdi+05]
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_ecx_r15d,
			mov_rdx_rax,
		};
		constexpr uint32 size0 = 5;
		constexpr uint32 size1 = sizeof(sect1);

		if (!run)
		{
			func = CreateFunction(GetChannelOffset, jumpAddr, true, false, size0, size1);
			CopyMemory(func.sect0, addr, size0, MemoryFlags_VirtualProtectSource);
			CopyMemory(func.sect1, sect1, size1);
			WriteCall(func.sect0, (appBaseAddr + 0x339E90));
			backupHelper.Save(addr, size0);
		}

		if (enable)
		{
			WriteJump(addr, func.addr);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Get Sound Data Count
	{
		auto addr     = (appBaseAddr + 0x321C7);
		auto jumpAddr = (appBaseAddr + 0x321CD);
		/*
		dmc3.exe+321C7 - 8B 15 27C35A00 - mov edx,[dmc3.exe+5DE4F4]
		dmc3.exe+321CD - 33 F6          - xor esi,esi
		*/

		static Function func = {};

		constexpr byte8 sect2[] =
		{
			mov_edx_eax,
		};
		constexpr uint32 size0 = 6;
		constexpr uint32 size2 = sizeof(sect2);

		if (!run)
		{
			func = CreateFunction(GetSoundDataCount, jumpAddr, true, false, size0, 0, size2);
			CopyMemory(func.sect0, addr, size0, MemoryFlags_VirtualProtectSource);
			CopyMemory(func.sect2, sect2, size2);
			WriteAddress(func.sect0, (appBaseAddr + 0x5DE4F4), size0);
			backupHelper.Save(addr, size0);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size0 - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Get Sound Data Address
	{
		auto addr     = (appBaseAddr + 0x321E0);
		auto jumpAddr = (appBaseAddr + 0x321E7);
		/*
		dmc3.exe+321E0 - 48 8D 3D C9C35A00 - lea rdi,[dmc3.exe+5DE5B0]
		dmc3.exe+321E7 - 48 8B CF          - mov rcx,rdi
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_rcx_rbx,
			mov_rdx_rdi,
		};
		constexpr byte8 sect2[] =
		{
			0x48, 0x8B, 0xF8, // mov rdi,rax
			0x8B, 0xC6,       // mov eax,esi
		};
		constexpr uint32 size0 = 7;
		constexpr uint32 size1 = sizeof(sect1);
		constexpr uint32 size2 = sizeof(sect2);

		if (!run)
		{
			func = CreateFunction(GetSoundDataAddress, jumpAddr, true, false, size0, size1, size2);
			CopyMemory(func.sect0, addr, size0, MemoryFlags_VirtualProtectSource);
			CopyMemory(func.sect1, sect1, size1);
			CopyMemory(func.sect2, sect2, size2);
			WriteAddress(func.sect0, (appBaseAddr + 0x5DE5B0), size0);
			backupHelper.Save(addr, size0);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size0 - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Disable Equipment Check
	Write<byte8>((appBaseAddr + 0x33995C), (enable) ? 0xEB : 0x74);
	/*
	dmc3.exe+33995C - 74 12    - je dmc3.exe+339970
	dmc3.exe+33995E - 41 FF C2 - inc r10d
	*/

	// Get Dbst Metadata Address
	{
		auto addr     = (appBaseAddr + 0x33947B);
		auto jumpAddr = (appBaseAddr + 0x339480);
		/*
		dmc3.exe+33947B - E8 20F1FFFF - call dmc3.exe+3385A0
		dmc3.exe+339480 - 4C 8B E0    - mov r12,rax
		*/

		static Function func = {};

		constexpr byte8 sect1[] =
		{
			mov_ecx_edi,
			mov_edx_ebx,
			0x4C, 0x8B, 0xC0, // mov r8,rax
		};
		constexpr uint32 size0 = 5;
		constexpr uint32 size1 = sizeof(sect1);

		if (!run)
		{
			func = CreateFunction(GetDbstMetadataAddress, jumpAddr, true, false, size0, size1);
			CopyMemory(func.sect0, addr, size0, MemoryFlags_VirtualProtectSource);
			CopyMemory(func.sect1, sect1, size1);
			WriteCall(func.sect0, (appBaseAddr + 0x3385A0));
			backupHelper.Save(addr, size0);
		}

		if (enable)
		{
			WriteJump(addr, func.addr);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}









	run = true;
}

#ifdef __GARBAGE__
#endif
