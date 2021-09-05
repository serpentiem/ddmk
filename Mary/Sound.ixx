// @Todo: Update order.
// @Todo: Use MAX_PROG_SECT regardless of common.

export module Sound;

import Core;

#include "../Core/Macros.h"

import Vars;

import Config;
import File;
import FMOD;
import Global;
import Internal;

#define debug false

#include "Macros.h"

constexpr uint32 g_sectCount[HELPER_COUNT] =
{
	3,
	3,
	3,
	3,
	108,
	108,
	108,
	50,
	50,
	50,
	50,
	50,
	50,
	50,
	50,
	50,
	50,
	50,
	50,
};

#define _(size) struct { byte8 Prep_Merge(padding_, __LINE__)[size]; }

#pragma pack(push, 1)

// export struct ArchiveMetadata
// {
// 	byte8 signature[4];
// 	uint32 fileCount;
// 	uint32 fileOffs[1];
// };

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

export struct DbstItem
{
	_(32);
};

export struct DbstMetadata
{
	byte8 signature[4];
	_(4);
	uint32 size;
	uint32 itemCount;
	DbstItem items[1];
};

#pragma pack(pop)

#undef _





export void PlaySound
(
	int32 group,
	int32 index
)
{
	func_3391C0
	(
		(appBaseAddr + 0xD6DC90),
		group,
		index,
		0,
		0
	);
}

export void PlayTrack(const char * filename)
{
	func_32BE20((appBaseAddr + 0xCF3700));
	func_32BA90((appBaseAddr + 0xCF3708), filename, 0, 0);
};

export void SetVolume
(
	uint8 channelIndex,
	float volume
)
{
	LogFunction(channelIndex, volume);

	if (!FMOD_init)
	{
		Log("!FMOD_init");

		return;
	}

	auto channelAddr = reinterpret_cast<FMOD_CHANNEL **>(appBaseAddr + 0x5DE3E0)[channelIndex];
	/*
	dmc3.exe+3271E - 48 8D 3D BBBC5A00 - lea rdi,[dmc3.exe+5DE3E0]
	*/

	auto result = FMOD_Channel_SetVolume
	(
		channelAddr,
		volume
	);

	if (result != FMOD_OK)
	{
		Log("FMOD_Channel_SetVolume failed. %u %X", channelIndex, result);

		return;
	}
}

export inline void UpdateVolumes()
{
	old_for_all(uint8, channelIndex, CHANNEL::MAX)
	{
		SetVolume
		(
			channelIndex,
			activeConfig.channelVolumes[channelIndex]
		);
	}
}














// bool IsArchive(byte8 * addr)
// {
// 	constexpr byte8 signature1[] = { 'P', 'A', 'C' };
// 	constexpr byte8 signature2[] = { 'P', 'N', 'S', 'T' };

// 	if
// 	(
// 		SignatureMatch(addr, signature1) ||
// 		SignatureMatch(addr, signature2)
// 	)
// 	{
// 		return true;
// 	}

// 	return false;
// }

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
	if constexpr (debug)
	{
		LogFunction();
	}

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
	if constexpr (debug)
	{
		LogFunction();
	}

	CopyMemory
	(
		(dataAddr + pos),
		addr,
		size
	);

	pos += size;

	if constexpr (debug)
	{
		Log("pos %X", pos);
	}

	Align<uint32>
	(
		pos,
		0x10,
		dataAddr,
		0xFF
	);

	if constexpr (debug)
	{
		Log("pos %X", pos);
	}
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
	if constexpr (debug)
	{
		LogFunction();
	}

	auto & progMetadata = *reinterpret_cast<ProgMetadata *>(dataAddr);

	auto & progSectMetadata2 = *reinterpret_cast<ProgSectMetadata *>(dataAddr + pos);

	uint32 size = (PROG_SECT_METADATA_SIZE + (PROG_SECT_ITEM_SIZE * progSectMetadata.itemCount));

	CopyMemory
	(
		&progSectMetadata2,
		&progSectMetadata,
		size
	);

	old_for_all(uint8, itemIndex, progSectMetadata2.itemCount)
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
	if constexpr (debug)
	{
		LogFunction();
	}

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
	if constexpr (debug)
	{
		LogFunction();
	}

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
	if constexpr (debug)
	{
		LogFunction();
	}

	uint32 off = 0;

	old_for_all(uint32, itemIndex, count)
	{
		auto & item = (*this)[itemIndex];

		item.off = off;

		off += item.size;

		if constexpr (debug)
		{
			Log("off %X", item.off);
		}
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
	if constexpr (debug)
	{
		LogFunction();
	}

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
	if constexpr (debug)
	{
		LogFunction();
	}

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

DbstHelper  g_dbstHelper [HELPER_COUNT] = {};
HeadHelper  g_headHelper [HELPER_COUNT] = {};
ProgHelper  g_progHelper [HELPER_COUNT] = {};
SmplHelper  g_smplHelper [HELPER_COUNT] = {};
VagiHelper  g_vagiHelper [HELPER_COUNT] = {};
WaveHelper  g_waveHelper [HELPER_COUNT] = {};
SoundHelper g_soundHelper[HELPER_COUNT] = {};

#define IntroduceHelpers(name)\
auto & dbstHelper  = g_dbstHelper [name];\
auto & headHelper  = g_headHelper [name];\
auto & progHelper  = g_progHelper [name];\
auto & smplHelper  = g_smplHelper [name];\
auto & vagiHelper  = g_vagiHelper [name];\
auto & waveHelper  = g_waveHelper [name];\
auto & soundHelper = g_soundHelper[name]

void Decompile
(
	byte8 * archive,
	uint8 helperIndex
)
{
	LogFunction();

	IntroduceHelpers(helperIndex);

	if constexpr (debug)
	{
		Log("archive %llX", archive);
	}

	if (!IsArchive(archive))
	{
		Log("IsArchive failed.");

		return;
	}

	auto & archiveMetadata = *reinterpret_cast<ArchiveMetadata *>(archive);

	uint32 waveCount = 0;

	old_for_all(uint32, fileIndex, archiveMetadata.fileCount)
	{
		auto & fileOff = archiveMetadata.fileOffs[fileIndex];
		auto file = reinterpret_cast<byte8 *>(archive + fileOff);

		if constexpr (debug)
		{
			Log("fileIndex %u", fileIndex);
			Log("fileOff %X", fileOff);
			Log("file %llX", file);
		}

		if (IsDbst(file))
		{
			if constexpr (debug)
			{
				Log("Dbst");
			}

			auto dbstMetadataAddr = file;
			auto & dbstMetadata = *reinterpret_cast<DbstMetadata *>(dbstMetadataAddr);

			dbstHelper.Push(dbstMetadata);
		}
		else if (IsHead(file))
		{
			auto headMetadataAddr = file;
			auto & headMetadata = *reinterpret_cast<HeadMetadata *>(headMetadataAddr);

			if constexpr (debug)
			{
				Log("Head");
				Log("headMetadataAddr %llX", headMetadataAddr);
			}

			auto progMetadataAddr = (file + headMetadata.progMetadataOff);

			if (IsProg(progMetadataAddr))
			{
				auto & progMetadata = *reinterpret_cast<ProgMetadata *>(progMetadataAddr);

				if constexpr (debug)
				{
					Log("Prog");
					Log("progMetadataAddr %llX", progMetadataAddr);
					Log("size %X", progMetadata.size);
					Log("last %u", progMetadata.last);
				}

				auto sectCount = static_cast<uint8>(progMetadata.last + 1);

				if constexpr (debug)
				{
					Log("sectCount %u", sectCount);
				}

				old_for_all(uint8, sectIndex, sectCount)
				{
					auto & sectOff = progMetadata.sectOffs[sectIndex];
					if (sectOff == 0xFFFFFFFF)
					{
						continue;
					}

					if constexpr (debug)
					{
						Log("sectOff %X", sectOff);
					}

					auto progSectMetadataAddr = (progMetadataAddr + sectOff);
					auto & progSectMetadata = *reinterpret_cast<ProgSectMetadata *>(progSectMetadataAddr);

					if constexpr (debug)
					{
						Log("ProgSectMetadata");
						Log("progSectMetadataAddr %llX", progSectMetadataAddr);
						Log("itemCount %u", progSectMetadata.itemCount);
					}

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

				if constexpr (debug)
				{
					Log("Smpl");
					Log("smplMetadataAddr %llX", smplMetadataAddr);
					Log("size %X", smplMetadata.size);
					Log("last %u", smplMetadata.last);
				}

				auto itemCount = (smplMetadata.last + 1);

				if constexpr (debug)
				{
					Log("itemCount %u", itemCount);
				}

				old_for_all(uint32, itemIndex, itemCount)
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

				if constexpr (debug)
				{
					Log("Vagi");
					Log("vagiMetadataAddr %llX", vagiMetadataAddr);
					Log("size %X", vagiMetadata.size);
					Log("last %u", vagiMetadata.last);
				}

				auto itemCount = (vagiMetadata.last + 1);

				waveCount = itemCount;

				if constexpr (debug)
				{
					Log("itemCount %u", itemCount);
				}

				old_for_all(uint32, itemIndex, itemCount)
				{
					auto & item = vagiMetadata.items[itemIndex];

					vagiHelper.Push(item);
				}
			}
		}
		else if (IsWave(file))
		{
			if constexpr (debug)
			{
				Log("Wave");
				Log("waveCount %u", waveCount);
			}

			uint32 pos = 0;

			old_for_all(uint32, waveIndex, waveCount)
			{
				auto wave = (file + pos);

				if (!IsWave(wave))
				{
					continue;
				}

				auto & waveMetadata = *reinterpret_cast<WaveMetadata *>(wave);

				auto size = (Reverse(&waveMetadata.reverseSize) + 0x30);

				if constexpr (debug)
				{
					Log("size %X", size);
				}

				waveHelper.Push
				(
					wave,
					size
				);

				pos += size;
			}
		}
	}

	if constexpr (debug)
	{
		Log("dbstHelper");
		Log("dataAddr %llX", dbstHelper.dataAddr);
		Log("pos      %X", dbstHelper.pos);
		Log("count    %u", dbstHelper.count);

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
	}
}

void Compile(uint8 helperIndex)
{
	LogFunction();

	IntroduceHelpers(helperIndex);

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

	old_for_all(uint32, index, waveHelper.count)
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

	if constexpr (debug)
	{
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

inline void Single
(
	const char * message,
	const uint8 helperIndex,
	const uint8 fileIndex
)
{
	Log(message);

	IntroduceHelpers(helperIndex);

	auto file = File_staticFiles[fileIndex];

	Decompile(file, helperIndex);

	vagiHelper.UpdateOffsets();

	Compile(helperIndex);
};

template <uint8 count>
void Multi
(
	const char * message,
	const uint8 helperIndex,
	const uint8(&fileIndices)[count]
)
{
	Log(message);

	IntroduceHelpers(helperIndex);

	old_for_all(uint8, index, count)
	{
		auto fileIndex = fileIndices[index];

		auto file = File_staticFiles[fileIndex];

		Decompile(file, helperIndex);
	}

	vagiHelper.UpdateOffsets();

	Compile(helperIndex);
}










// byte8 * dbstVergil = 0;
// byte8 * dbstLady = 0;


// namespaceStart(Sound);

// export uint8 id = 0;

// namespaceEnd();





void FMOD_InitComplete()
{
	LogFunction();

	FMOD_init = true;


	UpdateVolumes();











	Single
	(
		"Common Dante Default",
		HELPER_COMMON_DANTE_DEFAULT,
		snd_com0
	);
	Single
	(
		"Common Dante No Coat",
		HELPER_COMMON_DANTE_NO_COAT,
		snd_com0a
	);
	Single
	(
		"Common Vergil Default",
		HELPER_COMMON_VERGIL_DEFAULT,
		snd_com3
	);
	Single
	(
		"Common Vergil Nero Angelo",
		HELPER_COMMON_VERGIL_NERO_ANGELO,
		snd_com3a
	);

	{
		constexpr uint8 fileIndices[] =
		{
			snd_sty02,
			snd_sty03,
			snd_sty04,
			snd_sty05,
			snd_sty06,
			snd_wp00b,
			snd_wp01b,
			snd_wp02b,
			snd_wp03b,
			snd_wp04b,
			snd_wp05b,
			snd_wp06b,
			snd_wp07b,
			snd_wp08b,
			snd_wp09b,
		};

		Multi
		(
			"Style Weapon Dante",
			HELPER_STYLE_WEAPON_DANTE,
			fileIndices
		);
	}

	{
		constexpr uint8 fileIndices[] =
		{
			snd_sty07,
			snd_sty08,
			snd_wp11a,
			snd_wp12a,
			snd_wp13a,
		};

		Multi
		(
			"Style Weapon Vergil Default",
			HELPER_STYLE_WEAPON_VERGIL_DEFAULT,
			fileIndices
		);
	}

	{
		constexpr uint8 fileIndices[] =
		{
			snd_sty07,
			snd_sty08,
			snd_wp11b,
			snd_wp12b,
			snd_wp13b,
		};

		Multi
		(
			"Style Weapon Vergil Nero Angelo",
			HELPER_STYLE_WEAPON_VERGIL_NERO_ANGELO,
			fileIndices
		);
	}





	[&]()
	{
		auto file = File_staticFiles[snd_stay][1];

		if
		(
			!file ||
			!IsDbst(file)
		)
		{
			return;
		}

		auto dbstMetadataAddr = file;
		auto & dbstMetadata = *reinterpret_cast<DbstMetadata *>(dbstMetadataAddr);
		auto & dbstHelper = g_dbstHelper[HELPER_ENEMY_LESSER_ENEMIES];

		dbstHelper.Push(dbstMetadata);

		if constexpr (debug)
		{
			// @Todo: Create Print or Log func.
			Log("dbstHelper");
			Log("dataAddr %llX", dbstHelper.dataAddr);
			Log("pos      %X", dbstHelper.pos);
			Log("count    %u", dbstHelper.count);
		}
	}();

	{
		constexpr uint8 fileIndices[] =
		{
			snd_em00a,
			snd_em06,
			snd_em07,
			snd_em08,
			snd_em10,
			snd_em11,
			snd_em12,
			snd_em13,
			snd_em14,
			snd_em16,
			snd_em17,
			snd_em21,
		};

		Multi
		(
			"Lesser Enemies",
			HELPER_ENEMY_LESSER_ENEMIES,
			fileIndices
		);
	}


	// @Todo: Do for actor as well.
	struct SingleHelper
	{
		const char * name;
		uint8 helperIndex;
		uint8 fileIndex;
	};

	constexpr SingleHelper singleHelpers[] =
	{
		{ "Enemy Gigapede"    , HELPER_ENEMY_GIGAPEDE    , snd_em23 },
		{ "Enemy Cerberus"    , HELPER_ENEMY_CERBERUS    , snd_em25 },
		{ "Enemy Agni & Rudra", HELPER_ENEMY_AGNI_RUDRA  , snd_em26 },
		{ "Enemy Nevan"       , HELPER_ENEMY_NEVAN       , snd_em28 },
		{ "Enemy Geryon"      , HELPER_ENEMY_GERYON      , snd_em29 },
		{ "Enemy Beowulf"     , HELPER_ENEMY_BEOWULF     , snd_em30 },
		{ "Enemy Doppelganger", HELPER_ENEMY_DOPPELGANGER, snd_em31 },
		{ "Enemy Arkham"      , HELPER_ENEMY_ARKHAM      , snd_em32 },
		{ "Enemy Lady"        , HELPER_ENEMY_LADY        , snd_em34 },
		{ "Enemy Vergil"      , HELPER_ENEMY_VERGIL      , snd_em35 },
		{ "Enemy Jester"      , HELPER_ENEMY_JESTER      , snd_em37 },
	};

	old_for_all(uint8, index, countof(singleHelpers))
	{
		auto & singleHelper = singleHelpers[index];

		Single
		(
			singleHelper.name,
			singleHelper.helperIndex,
			singleHelper.fileIndex
		);
	}



	// {
	// 	// constexpr uint8 fileIndices[] =
	// 	// {
	// 	// 	snd_em34,
	// 	// 	//snd_em35,
	// 	// };

	// 	Single
	// 	(
	// 		"Lady",
	// 		HELPER_ENEMY_LADY,
	// 		snd_em34
	// 	);
	// }

	// {
	// 	// constexpr uint8 fileIndices[] =
	// 	// {
	// 	// 	snd_em35,
	// 	// };

	// 	Single
	// 	(
	// 		"Vergil",
	// 		HELPER_ENEMY_VERGIL,
	// 		snd_em35
	// 	);
	// }


}
















byte8 * GetDbstMetadataAddress(uint32 channelIndex)
{
	if constexpr (debug)
	{
		LogFunction();
	}

	auto pool = reinterpret_cast<byte8 **>(appBaseAddr + 0xD6E610);
	/*
	dmc3.exe+33AB12 - 48 8D 0D F73AA300 - lea rcx,[dmc3.exe+D6E610]
	*/

	auto dbstMetadataAddr = pool[channelIndex];

	//uint8 helperIndex = 0;

	switch (channelIndex)
	{
		case CHANNEL::COMMON:
		case CHANNEL::STYLE_WEAPON:
		case CHANNEL::ENEMY:
		{
			auto & helperIndex = g_helperIndices[channelIndex];

			dbstMetadataAddr = g_dbstHelper[helperIndex].dataAddr;

			break;
		}
	}

	if constexpr (debug)
	{
		Log("dbstMetadataAddr %llX", dbstMetadataAddr);
	}

	return dbstMetadataAddr;
}

















byte8 * GetDbstItemAddress
(
	uint32 channelIndex,
	uint32 itemIndex
)
{
	if constexpr (debug)
	{
		LogFunction();
		Log("channelIndex %u", channelIndex);
		Log("itemIndex %u", itemIndex);
	}

	auto dbstMetadataAddr = GetDbstMetadataAddress(channelIndex);
	if (!dbstMetadataAddr)
	{
		return 0;
	}
	auto & dbstMetadata = *reinterpret_cast<DbstMetadata *>(dbstMetadataAddr);

	if (itemIndex >= dbstMetadata.itemCount)
	{
		Log("Exceeding count.");

		return 0;
	}

	auto & item = dbstMetadata.items[itemIndex];

	return reinterpret_cast<byte8 *>(&item);
}

byte8 * GetHeadMetadataAddress(uint32 channelIndex)
{
	if constexpr (debug)
	{
		LogFunction();
	}

	auto pool = reinterpret_cast<byte8 **>(appBaseAddr + 0xD6E590);
	/*
	dmc3.exe+339EAA - 48 8D 0D DF46A300 - lea rcx,[dmc3.exe+D6E590]
	*/

	auto addr = pool[channelIndex];

	//uint8 helperIndex = 0;

	switch (channelIndex)
	{
		case CHANNEL::COMMON:
		case CHANNEL::STYLE_WEAPON:
		case CHANNEL::ENEMY:
		{
			auto & helperIndex = g_helperIndices[channelIndex];

			addr = g_headHelper[helperIndex].dataAddr;

			break;
		}
	}

	if constexpr (debug)
	{
		Log("addr %llX", addr);
	}

	return addr;
}

uint64 GetChannelOffset(uint32 channelIndex)
{
	auto offs = reinterpret_cast<uint64 *>(appBaseAddr + 0xD6E4C0);
	/*
	dmc3.exe+339D6A - 48 8D 0D 4F47A300 - lea rcx,[dmc3.exe+D6E4C0]
	*/

	switch (channelIndex)
	{
		case CHANNEL::COMMON:
		case CHANNEL::STYLE_WEAPON:
		case CHANNEL::ENEMY:
		{
			return 0;
		}
	}

	auto & off = offs[channelIndex];

	return off;
}



uint32 GetSoundDataCount(byte8 * addr)
{
	auto & channelIndex = *reinterpret_cast<uint8 *>(addr + 0xC);

	auto count = *reinterpret_cast<uint32 *>(appBaseAddr + 0x5DE4F4);
	/*
	dmc3.exe+321C7 - 8B 15 27C35A00 - mov edx,[dmc3.exe+5DE4F4]
	*/

	//uint8 helperIndex = 0;

	switch (channelIndex)
	{
		case CHANNEL::COMMON:
		case CHANNEL::STYLE_WEAPON:
		case CHANNEL::ENEMY:
		{
			auto & helperIndex = g_helperIndices[channelIndex];

			count = g_soundHelper[helperIndex].count;

			break;
		}
	}

	if constexpr (debug)
	{
		Log("count %u", count);
	}

	return count;
}

// @Todo: Update.
byte8 * GetSoundDataAddress(byte8 * addr)
{
	auto & channelIndex = *reinterpret_cast<uint8 *>(addr + 0xC);

	auto addr2 = reinterpret_cast<byte8 *>(appBaseAddr + 0x5DE5B0);
	/*
	dmc3.exe+321E0 - 48 8D 3D C9C35A00 - lea rdi,[dmc3.exe+5DE5B0]
	*/

	uint8 helperIndex = 0;

	switch (channelIndex)
	{
		case CHANNEL::COMMON:
		case CHANNEL::STYLE_WEAPON:
		case CHANNEL::ENEMY:
		{
			auto & helperIndex = g_helperIndices[channelIndex];

			addr2 = g_soundHelper[helperIndex].dataAddr;

			break;
		}
	}

	if constexpr (debug)
	{
		Log("addr2 %llX", addr2);
	}

	return addr2;
}











// @Todo: Update memory sizes.

export bool Sound_Init()
{
	LogFunction();

	old_for_all(uint8, helperIndex, HELPER_COUNT)
	{
		Log("helperIndex %u", helperIndex);

		// auto & headHelper  = g_headHelper [helperIndex];
		// auto & progHelper  = g_progHelper [helperIndex];
		// auto & smplHelper  = g_smplHelper [helperIndex];
		// auto & vagiHelper  = g_vagiHelper [helperIndex];
		// auto & waveHelper  = g_waveHelper [helperIndex];
		// auto & soundHelper = g_soundHelper[helperIndex];
		// auto & dbstHelper  = g_dbstHelper [helperIndex];

		IntroduceHelpers(helperIndex);

		if (!headHelper.Init(1 * 1024 * 1024))
		{
			Log("headHelper.Init failed.");

			return false;
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

			return false;
		}
		else if (!smplHelper.Init(1 * 1024 * 1024))
		{
			Log("smplHelper.Init failed.");

			return false;
		}
		else if (!vagiHelper.Init(1 * 1024 * 1024))
		{
			Log("vagiHelper.Init failed.");

			return false;
		}
		else if
		(
			!waveHelper.Init
			(
				(16 * 1024 * 1024),
				8192
			)
		)
		{
			Log("waveHelper.Init failed.");

			return false;
		}
		else if (!soundHelper.Init(1 * 1024 * 1024))
		{
			Log("soundHelper.Init failed.");

			return false;
		}
		else if (!dbstHelper.Init(8 * 1024 * 1024))
		{
			Log("dbstHelper.Init failed.");

			return false;
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

		auto func = CreateFunction(FMOD_InitComplete);

		WriteJump(addr, func.addr);
	}

	return true;
}



namespaceStart(Sound);

export void Toggle(bool enable)
{
	LogFunction(enable);

	static bool run = false;

	// Get Dbst Metadata Address
	{
		auto addr     = (appBaseAddr + 0x33AE40);
		auto jumpAddr = (appBaseAddr + 0x33AE47);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+33AE40 - 4C 8B 38   - mov r15,[rax]
		dmc3.exe+33AE43 - 45 0FB7 E5 - movzx r12d,r13w
		dmc3.exe+33AE47 - 4D 85 FF   - test r15,r15
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rax,
		};
		constexpr byte8 sect2[] =
		{
			mov_r15_rax,
			pop_rax,
			0x45, 0x0F, 0xB7, 0xE5, // movzx r12d,r13w
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(GetDbstMetadataAddress, jumpAddr, true, false, sizeof(sect0), 0, sizeof(sect2));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
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

	// Get Dbst Item Address
	{
		auto addr = (appBaseAddr + 0x33AB10);
		constexpr uint32 size = 9;
		/*
		dmc3.exe+33AB10 - 8B C1             - mov eax,ecx
		dmc3.exe+33AB12 - 48 8D 0D F73AA300 - lea rcx,[dmc3.exe+D6E610]
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(GetDbstItemAddress, 0, true, false);
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

	// Get Head Metadata Address
	{
		auto addr = (appBaseAddr + 0x339EA0);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+339EA0 - 83 F9 10 - cmp ecx,10
		dmc3.exe+339EA3 - 72 03    - jb dmc3.exe+339EA8
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(GetHeadMetadataAddress, 0, true, false);
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

	// Get Channel Offset
	{
		auto addr = (appBaseAddr + 0x339D60);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+339D60 - 83 F9 10 - cmp ecx,10
		dmc3.exe+339D63 - 72 03    - jb dmc3.exe+339D68
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(GetChannelOffset, 0, true, false);
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

	// Get Sound Data Count
	{
		auto addr     = (appBaseAddr + 0x321C7);
		auto jumpAddr = (appBaseAddr + 0x321CD);
		constexpr uint32 size = 6;
		/*
		dmc3.exe+321C7 - 8B 15 27C35A00 - mov edx,[dmc3.exe+5DE4F4]
		dmc3.exe+321CD - 33 F6          - xor esi,esi
		*/

		static Function func = {};

		constexpr byte8 sect2[] =
		{
			mov_edx_eax,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(GetSoundDataCount, jumpAddr, true, false, 0, 0, sizeof(sect2));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
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

	// Get Sound Data Address
	{
		auto addr     = (appBaseAddr + 0x321E0);
		auto jumpAddr = (appBaseAddr + 0x321E7);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+321E0 - 48 8D 3D C9C35A00 - lea rdi,[dmc3.exe+5DE5B0]
		dmc3.exe+321E7 - 48 8B CF          - mov rcx,rdi
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rax,
		};

		constexpr byte8 sect2[] =
		{
			mov_rdi_rax,
			pop_rax,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(GetSoundDataAddress, jumpAddr, true, false, sizeof(sect0), 0, sizeof(sect2));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			CopyMemory(func.sect2, sect2, sizeof(sect2));
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

	// Disable Equipment Check
	Write<byte8>((appBaseAddr + 0x33995C), (enable) ? 0xEB : 0x74);
	/*
	dmc3.exe+33995C - 74 12    - je dmc3.exe+339970
	dmc3.exe+33995E - 41 FF C2 - inc r10d
	*/

	run = true;
}



export void EventMain()
{
	if (!activeConfig.Actor.enable)
	{
		return;
	}

	LogFunction();

	Toggle(true);
}

export void EventDelete()
{
	if (!activeConfig.Actor.enable)
	{
		return;
	}

	LogFunction();

	Toggle(false);
}

export void UpdateEnemyCount()
{
	if
	(
		activeConfig.soundIgnoreEnemyData ||
		!activeConfig.Actor.enable
	)
	{
		return;
	}

	LogFunction();



	auto & helperIndex = g_helperIndices[CHANNEL::ENEMY];

	IntroduceEnemyVectorData(return);

	old_for_all(uint32, enemyIndex, countof(enemyVectorData.metadata))
	{
		auto & metadata = enemyVectorData.metadata[enemyIndex];

		// if (!metadata.baseAddr)
		// {
		// 	continue;
		// }

		IntroduceData(metadata.baseAddr, actorData, EnemyActorData, continue);

		// @Research: actorData.baseAddr could be 0.
		// @Todo: Check if metadata.baseAddr is properly set to zero.

		if (!actorData.baseAddr)
		{
			continue;
		}




		auto enemy = actorData.enemy;
		if (enemy >= ENEMY::COUNT)
		{
			enemy = 0;
		}

		helperIndex = enemyHelperIndices[enemy];

		return;
	}
}

namespaceEnd();

#ifdef __GARBAGE__
#endif
