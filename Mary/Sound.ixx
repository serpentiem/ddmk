module;
#include "../Core/Core.h"

#include "Vars.h"
export module Sound;

import File;
import FMOD;

#define debug true

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

#pragma pack(pop)

#undef _



bool IsArchive(ArchiveMetadata & archiveMetadata)
{
	constexpr byte8 signature1[] = { 'P', 'A', 'C' };
	constexpr byte8 signature2[] = { 'P', 'N', 'S', 'T' };

	if
	(
		SignatureMatch(archiveMetadata.signature, signature1) ||
		SignatureMatch(archiveMetadata.signature, signature2)
	)
	{
		return true;
	}

	return false;
}

bool IsHead(HeadMetadata & headMetadata)
{
	constexpr byte8 signature[] = { 'H', 'e', 'a', 'd', };

	return SignatureMatch(headMetadata.signature, signature);
}

bool IsProg(ProgMetadata & progMetadata)
{
	constexpr byte8 signature[] = { 'P', 'r', 'o', 'g', };

	return SignatureMatch(progMetadata.signature, signature);
}

bool IsSmpl(SmplMetadata & smplMetadata)
{
	constexpr byte8 signature[] = { 'S', 'm', 'p', 'l', };

	return SignatureMatch(smplMetadata.signature, signature);
}

bool IsVagi(VagiMetadata & vagiMetadata)
{
	constexpr byte8 signature[] = { 'V', 'a', 'g', 'i', };

	return SignatureMatch(vagiMetadata.signature, signature);
}

bool IsWave(byte8 * addr)
{
	constexpr byte8 signature[] = { 'V', 'A', 'G', 'p', };

	return SignatureMatch(addr, signature);
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

	uint32 size = VAGI_ITEM_SIZE;

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

	uint32 size = SMPL_ITEM_SIZE;

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

struct ProgHelper
{
	byte8 * dataAddr;
	uint32 pos;
	uint32 count;

	bool Init(uint32 dataSize);

	void Push
	(
		ProgSectMetadata & progSectMetadata,
		uint16 smplItemCount,
		uint8 sectIndex
	);

	ProgSectMetadata & operator[](uint8 sectIndex);
};

bool ProgHelper::Init(uint32 dataSize)
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

	progMetadata.last = (MAX_PROG_SECT - 1);

	constexpr uint32 size = (MAX_PROG_SECT * 4);

	SetMemory
	(
		progMetadata.sectOffs,
		0xFF,
		size
	);

	pos = (PROG_METADATA_SIZE + size);

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



WaveHelper waveHelper = {};
VagiHelper vagiHelper = {};
SmplHelper smplHelper = {};
ProgHelper progHelper = {};
HeadHelper headHelper = {};



void Decompile(byte8 * archive)
{
	LogFunction();

	Log("archive %llX", archive);

	auto & archiveMetadata = *reinterpret_cast<ArchiveMetadata *>(archive);

	if (!IsArchive(archiveMetadata))
	{
		Log("IsArchive failed.");

		return;
	}

	uint32 waveCount = 0;

	for_all(uint32, fileIndex, archiveMetadata.fileCount)
	{
		auto & fileOff = archiveMetadata.fileOffs[fileIndex];
		auto file = reinterpret_cast<byte8 *>(archive + fileOff);

		Log("fileIndex %u", fileIndex);
		Log("fileOff %X", fileOff);
		Log("file %llX", file);

		// @Todo: Check for byte8 * signature and do not assume metadata.

		auto & headMetadata = *reinterpret_cast<HeadMetadata *>(file);
		auto headMetadataAddr = reinterpret_cast<byte8 *>(&headMetadata);

		if (IsHead(headMetadata))
		{
			Log("Head");
			Log("headMetadataAddr %llX", headMetadataAddr);

			auto & progMetadata = *reinterpret_cast<ProgMetadata *>(file + headMetadata.progMetadataOff);
			auto progMetadataAddr = reinterpret_cast<byte8 *>(&progMetadata);

			if (IsProg(progMetadata))
			{
				Log("Prog");
				Log("progMetadataAddr %llX", progMetadataAddr);
				Log("size %X", progMetadata.size);
				Log("last %u", progMetadata.last);

				auto sectCount = static_cast<uint8>(progMetadata.last + 1);

				for_all(uint8, sectIndex, sectCount)
				{
					auto & sectOff = progMetadata.sectOffs[sectIndex];
					if (sectOff == 0xFFFFFFFF)
					{
						continue;
					}

					Log("sectOff %X", sectOff);

					auto & progSectMetadata = *reinterpret_cast<ProgSectMetadata *>(progMetadataAddr + sectOff);
					auto progSectMetadataAddr = reinterpret_cast<byte8 *>(&progSectMetadata);

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

			auto & smplMetadata = *reinterpret_cast<SmplMetadata *>(file + headMetadata.smplMetadataOff);
			auto smplMetadataAddr = reinterpret_cast<byte8 *>(&smplMetadata);

			if (IsSmpl(smplMetadata))
			{
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

			auto & vagiMetadata = *reinterpret_cast<VagiMetadata *>(file + headMetadata.vagiMetadataOff);
			auto vagiMetadataAddr = reinterpret_cast<byte8 *>(&vagiMetadata);

			if (IsVagi(vagiMetadata))
			{
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

				vagiHelper.UpdateOffsets();
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
	}
}



void Compile()
{
	LogFunction();

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
}




void ProcessSoundFiles()
{
	LogFunction();

	const char * filenames[] =
	{
		"snd_sty02.pac",
		"snd_sty03.pac",
		"snd_sty04.pac",
		"snd_sty05.pac",
		"snd_sty06.pac",
		"snd_sty07.pac",
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
		"snd_wp11b.pac",
		"snd_wp12b.pac",
		"snd_wp13b.pac",
	};

	for_all(uint8, fileIndex, countof(filenames))
	{
		auto filename = filenames[fileIndex];

		byte8 * file = 0;
		uint32 fileSize = 0;

		file = File_LoadFile(filename, &fileSize);
		if (!file)
		{
			Log("File_LoadFile failed.");

			return;
		}

		Decompile(file);
	}

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

	Compile();

	Log("headHelper");
	Log("dataAddr %llX", headHelper.dataAddr);
	Log("pos      %X", headHelper.pos);
	Log("count    %u", headHelper.count);
}

export void Sound_Toggle(bool enable)
{
	LogFunction(enable);

	static bool run = false;

	if (!run)
	{
		if
		(
			!waveHelper.Init
			(
				(32 * 1024 * 1024),
				4096
			)
		)
		{
			Log("waveHelper.Init failed.");

			return;
		}
		else if (!vagiHelper.Init(1 * 1024 * 1024))
		{
			Log("vagiHelper.Init failed.");

			return;
		}
		else if (!smplHelper.Init(1 * 1024 * 1024))
		{
			Log("smplHelper.Init failed.");

			return;
		}
		else if (!progHelper.Init(1 * 1024 * 1024))
		{
			Log("progHelper.Init failed.");

			return;
		}
		else if (!headHelper.Init(1 * 1024 * 1024))
		{
			Log("headHelper.Init failed.");

			return;
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

	run = true;
}

#ifdef __GARBAGE__
#endif
