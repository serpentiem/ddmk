#include "Sound.h"

#pragma region __PRELIMINARY_STUFF__

#define HoboBreak() \
MessageBoxA(0, "break", 0, 0); \
MessageBoxA(0, "break", 0, 0);

byte * LoadFile(const char * fileName, uint64 * p_size = 0)
{
	byte * addr = 0;
	dword error = 0;
	SetLastError(0);
	HANDLE file = CreateFileA(fileName, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	error = GetLastError();
	if (file == INVALID_HANDLE_VALUE)
	{
		Log("CreateFileA failed. error %s %X", fileName, error);
		return 0;
	}
	BY_HANDLE_FILE_INFORMATION fi = {};
	GetFileInformationByHandle(file, &fi);
	SetLastError(0);
	addr = (byte *)VirtualAlloc(0, fi.nFileSizeLow, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	error = GetLastError();
	if (!addr)
	{
		Log("VirtualAlloc failed. error %X", error);
		return 0;
	}
	dword bytesRead = 0;
	OVERLAPPED overlap = {};
	ReadFile(file, addr, fi.nFileSizeLow, &bytesRead, &overlap);
	CloseHandle(file);
	if (p_size)
	{
		*p_size = (uint64)fi.nFileSizeLow;
	}
	return addr;
}

bool SaveFile(byte * addr, uint64 size, const char * fileName)
{
	dword error = 0;
	SetLastError(0);
	HANDLE file = CreateFileA(fileName, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	error = GetLastError();
	if (file == INVALID_HANDLE_VALUE)
	{
		Log("CreateFile failed. error %X", error);
		return false;
	}
	dword bytesWritten = 0;
	OVERLAPPED overlap = {};
	WriteFile(file, addr, (uint32)size, &bytesWritten, &overlap);
	CloseHandle(file);
	return true;
}

template <typename T>
T Reverse(T * var)
{
	constexpr uint8 size = (uint8)sizeof(T);
	T value = 0;
	for (uint8 index = 0; index < size; index++)
	{
		((byte *)&value)[index] = ((byte *)var)[(size - 1 - index)];
	}
	return value;
}

#pragma endregion

#pragma region Global Definitions

enum SOUND_
{
	MAX_SOUND = 10000,
	MAX_SOUND_PER_CHANNEL = 625,
};

enum CHANNEL_
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

enum PROG_SECT_
{
	PROG_SECT_REBELLION,
	PROG_SECT_CERBERUS,
	PROG_SECT_AGNI_RUDRA,
	PROG_SECT_NEVAN,
	PROG_SECT_BEOWULF,
	PROG_SECT_EBONY_IVORY,
	PROG_SECT_SHOTGUN,
	PROG_SECT_ARTEMIS,
	PROG_SECT_SPIRAL,
	PROG_SECT_KALINA_ANN,
	PROG_SECT_SWORDMASTER = 100,
	PROG_SECT_GUNSLINGER,
	PROG_SECT_TRICKSTER,
	PROG_SECT_ROYALGUARD,
	PROG_SECT_QUICKSILVER,
	PROG_SECT_DOPPELGANGER,
	MAX_PROG_SECT = 108,
};




struct HEAD
{
	byte signature[4];
	byte unknown[8];
	uint32 size;
	uint32 waveSize;
	uint32 progOff;
	uint32 smplOff;
	uint32 vagiOff;
};

struct PROG_METADATA
{
	byte signature[4];
	uint32 size;
	uint32 last;
};

struct PROG_SECT_METADATA
{
	uint8 itemCount;
	byte unknown[7];
};

struct PROG_SECT_ITEM
{
	byte unknown[12];
	uint16 id;
};

struct SMPL_METADATA
{
	byte signature[4];
	uint32 size;
	uint32 last;
};

struct SMPL_ITEM
{
	byte unknown[10];
	uint16 id;
};

struct VAGI_METADATA
{
	byte signature[4];
	uint32 size;
	uint32 last;
};

struct VAGI_ITEM
{
	uint32 off;
	uint32 size;
	byte unknown[4];
	uint32 sampleRate;
};

struct G_PROG
{
	byte * addr;
	uint64 pos;
	uint64 count;
	uint32 * off;
	uint8 id[MAX_PROG_SECT];

	PROG_SECT_METADATA & Push(PROG_SECT_METADATA & sect, uint8 index) // @Research: Convention for identical names.
	{
		off[count] = (uint32)pos;


		id[count] = index;






		PROG_SECT_METADATA & newSect = *(PROG_SECT_METADATA *)(addr + pos) = sect;
		pos += sizeof(PROG_SECT_METADATA);
		count++;
		return newSect;
	}
	PROG_SECT_ITEM & Push(PROG_SECT_ITEM & item)
	{
		PROG_SECT_ITEM & newItem = *(PROG_SECT_ITEM *)(addr + pos) = item;
		pos += sizeof(PROG_SECT_ITEM);
		return newItem;
	}
};

struct G_SMPL
{
	SMPL_ITEM * addr;
	uint64 count;
	SMPL_ITEM & Push(SMPL_ITEM & item)
	{
		SMPL_ITEM & newItem = addr[count] = item;
		count++;
		return newItem;
	}
};

struct G_VAGI
{
	VAGI_ITEM * addr;
	uint64 count;
	VAGI_ITEM & Push(VAGI_ITEM & item)
	{
		VAGI_ITEM & newItem = addr[count] = item;
		count++;
		return newItem;
	}
};

struct WAVE_ITEM
{
	byte * addr;
	uint32 size;
};

struct G_WAVE
{
	byte * addr;
	uint32 pos;
	uint32 count;
	uint32 * off;
	uint32 * size;
	byte * Push(byte * item, uint32 itemSize)
	{
		off[count] = pos;
		size[count] = itemSize;
		byte * newItem = (addr + pos);
		memcpy(newItem, item, itemSize);
		pos += itemSize;
		count++;
		return newItem;
	}
	WAVE_ITEM operator[](uint32 index)
	{
		WAVE_ITEM item = {};
		item.addr = (addr + off[index]);
		item.size = size[index];
		return item;
	}
};

struct SOUND_ITEM
{
	uint64 pos;
	uint64 size;
	FMOD_SOUND * sound;
};

G_PROG g_prog[MAX_CHANNEL] = {};
G_SMPL g_smpl[MAX_CHANNEL] = {};
G_VAGI g_vagi[MAX_CHANNEL] = {};
G_WAVE g_wave[MAX_CHANNEL] = {};

uint64       posMap   [MAX_CHANNEL] = {};
byte       * soundMap [MAX_CHANNEL] = {};
SOUND_ITEM * soundItem[MAX_CHANNEL] = {};

#pragma endregion

static void Decompile(byte * archive, uint8 channel, uint8 progId) // = 0xFF
{
	Log("Decompile Start");
	LogNewLine();
	Log("archive %llX", archive);
	Log("channel %u"  , channel);

	uint32 & fileCount = *(uint32 *)(archive + 4);

	Log("fileCount %u", fileCount);
	LogNewLine();

	uint16 smplCount = (uint16)g_smpl[channel].count;
	uint16 vagiCount = (uint16)g_vagi[channel].count;
	uint32 waveItemCount = 0;

	for (uint8 fileIndex = 0; fileIndex < fileCount; fileIndex++)
	{
		uint32 fileOff = ((uint32 *)(archive + 8))[fileIndex];
		byte * file = (archive + fileOff);

		Log("file %u %llX", fileIndex, file);
		LogNewLine();

		Head:
		{
			byte signature[] = { 'H','e','a','d' };
			for (uint8 index = 0; index < countof(signature); index++)
			{
				if (file[index] != signature[index])
				{
					goto Wave;
				}
			}
			Log("Head");
			LogNewLine();

			HEAD & head = *(HEAD *)file;

			Log("Prog");
			{
				PROG_METADATA & prog = *(PROG_METADATA *)(file + head.progOff);
				Log("last %u", prog.last);
				uint32 sectCount = (prog.last + 1);
				for (uint32 sectIndex = 0; sectIndex < sectCount; sectIndex++)
				{
					uint32 off = ((uint32 *)(file + head.progOff + 0x10))[sectIndex];
					if (off == 0xFFFFFFFF)
					{
						continue;
					}
					Log("off %X", off);

					PROG_SECT_METADATA & sect = *(PROG_SECT_METADATA *)(file + head.progOff + off);
					g_prog[channel].Push(sect, progId);

					for (uint8 itemIndex = 0; itemIndex < sect.itemCount; itemIndex++)
					{
						PROG_SECT_ITEM & item = ((PROG_SECT_ITEM *)(file + head.progOff + off + sizeof(PROG_SECT_METADATA)))[itemIndex];
						PROG_SECT_ITEM & newItem = g_prog[channel].Push(item);
						newItem.id += smplCount;
					}
				}
				Log("g_prog[%u] addr  %llX", channel, g_prog[channel].addr );
				Log("g_prog[%u] pos   %llX", channel, g_prog[channel].pos  );
				Log("g_prog[%u] count %u"  , channel, g_prog[channel].count);
			}
			LogNewLine();

			Log("Smpl");
			{
				SMPL_METADATA & smpl = *(SMPL_METADATA *)(file + head.smplOff);
				Log("last %u", smpl.last);
				uint32 itemCount = (smpl.last + 1);
				for (uint32 itemIndex = 0; itemIndex < itemCount; itemIndex++)
				{
					SMPL_ITEM & item = ((SMPL_ITEM *)(file + head.smplOff + 0x10))[itemIndex];
					SMPL_ITEM & newItem = g_smpl[channel].Push(item);
					newItem.id += vagiCount;
				}
				Log("g_smpl[%u] addr  %llX", channel, g_smpl[channel].addr );
				Log("g_smpl[%u] count %llu", channel, g_smpl[channel].count);
			}
			LogNewLine();

			Log("Vagi");
			{
				VAGI_METADATA & vagi = *(VAGI_METADATA *)(file + head.vagiOff);
				Log("last %u", vagi.last);
				uint32 itemCount = (vagi.last + 1);
				for (uint32 itemIndex = 0; itemIndex < itemCount; itemIndex++)
				{
					VAGI_ITEM & item = ((VAGI_ITEM *)(file + head.vagiOff + 0x10))[itemIndex];
					VAGI_ITEM & newItem = g_vagi[channel].Push(item);
					newItem.off = 0;
				}
				Log("g_vagi[%u] addr  %llX", channel, g_vagi[channel].addr );
				Log("g_vagi[%u] count %llu", channel, g_vagi[channel].count);

				waveItemCount = itemCount;
			}
			LogNewLine();
		}
		Wave:
		{
			byte signature[] = { 'V','A','G','p' };
			for (uint8 index = 0; index < countof(signature); index++)
			{
				if (file[index] != signature[index])
				{
					goto End;
				}
			}
			Log("Wave");
			Log("waveItemCount %u", waveItemCount);

			uint32 filePos = 0;
			for (uint32 itemIndex = 0; itemIndex < waveItemCount; itemIndex++)
			{
				byte * item = (file + filePos);
				uint32 itemSize = (Reverse((uint32 *)(item + 0xC)) + 0x30);

				Log("item     %llX", item);
				Log("itemSize %X", itemSize);

				g_wave[channel].Push(item, itemSize);
				filePos += itemSize;
			}
			Log("g_wave[%u] addr  %llX", channel, g_wave[channel].addr );
			Log("g_wave[%u] pos   %X"  , channel, g_wave[channel].pos  );
			Log("g_wave[%u] count %u"  , channel, g_wave[channel].count);
		}
		End:;
	}
	LogNewLine();
	Log("Decompile End");
	LogNewLine();
}

static void Compile(uint8 channel, uint8 maxProgSect)
{
	Log("Compile Start");
	LogNewLine();

	dword error = 0;

	Head:
	{
		byte * & addr = soundMap[channel];
		uint64 pos = 0;

		auto Align = [&]()
		{
			constexpr uint64 boundary = 0x10;
			uint64 remainder = (pos % boundary);
			if (remainder)
			{
				uint64 size = (boundary - remainder);
				memset((addr + pos), 0xFF, size);
				pos += size;
			}
		};

		HEAD & head = *(HEAD *)(addr + pos);
		pos += sizeof(HEAD);
		Align();

		Prog:
		{
			head.progOff = (uint32)pos;

			PROG_METADATA & prog = *(PROG_METADATA *)(addr + pos);
			pos += sizeof(PROG_METADATA);
			Align();

			uint32 * off = (uint32 *)(addr + pos);

			// @Optimize: Adjust datatypes with regards to MAX_PROG_SECT.

			for (uint8 sect = 0; sect < maxProgSect; sect++)
			{
				//Log("Def not accessing this. %u", sect);
				off[sect] = 0xFFFFFFFF;
				pos += sizeof(uint32);
			}

			for (uint64 sect = 0; sect < g_prog[channel].count; sect++)
			{
				uint8 & id = g_prog[channel].id[sect];
				off[id] = g_prog[channel].off[sect];
				off[id] += 0x10;
				off[id] += (maxProgSect * sizeof(uint32));
			}

			memcpy((addr + pos), g_prog[channel].addr, g_prog[channel].pos);
			pos += g_prog[channel].pos;

			Align();

			prog.signature[0] = 'P';
			prog.signature[1] = 'r';
			prog.signature[2] = 'o';
			prog.signature[3] = 'g';
			prog.size = (uint32)(pos - head.progOff);
			prog.last = (maxProgSect == 0) ? 0 : (maxProgSect - 1);
		}

		Smpl:
		{
			head.smplOff = (uint32)pos;

			SMPL_METADATA & smpl = *(SMPL_METADATA *)(addr + pos);
			pos += sizeof(SMPL_METADATA);
			Align();

			uint64 size = (g_smpl[channel].count * sizeof(SMPL_ITEM));
			memcpy((addr + pos), g_smpl[channel].addr, size);
			pos += size;
			Align();

			smpl.signature[0] = 'S';
			smpl.signature[1] = 'm';
			smpl.signature[2] = 'p';
			smpl.signature[3] = 'l';
			smpl.size = (uint32)(pos - head.smplOff);
			smpl.last = (uint32)(g_smpl[channel].count - 1);
		}

		Vagi:
		{
			head.vagiOff = (uint32)pos;

			VAGI_METADATA & vagi = *(VAGI_METADATA *)(addr + pos);
			pos += sizeof(VAGI_METADATA);
			Align();

			// @Optimize: Just go with itemCount.

			uint64 size = (g_vagi[channel].count * sizeof(VAGI_ITEM));
			memcpy((addr + pos), g_vagi[channel].addr, size);

			// @Optimize: Change datatypes for count.
			//Log("__UFF__ loop start addr %llX", addr);
			//Log("__UFF__ loop start pos  %llX", pos);

			for (uint64 itemIndex = 0; itemIndex < g_vagi[channel].count; itemIndex++)
			{
				static uint32 off = 0;
				VAGI_ITEM & item = ((VAGI_ITEM *)(addr + pos))[itemIndex];
				//Log("__UFF__ off   %X", off);
				//LogNewLine();
				
				//Log("item      %llX", item);
				//Log("item size %u", item.size);
				//Log("item rate %u", item.sampleRate);

				item.off = off;
				off += item.size;
			}

			pos += size;
			Align();

			vagi.signature[0] = 'V';
			vagi.signature[1] = 'a';
			vagi.signature[2] = 'g';
			vagi.signature[3] = 'i';
			vagi.size = (uint32)(pos - head.vagiOff);
			vagi.last = (uint32)(g_vagi[channel].count - 1);
		}

		head.signature[0] = 'H';
		head.signature[1] = 'e';
		head.signature[2] = 'a';
		head.signature[3] = 'd';
	}

	Wave:
	{


		// @Optimize: Adjust datatype for pos.

		uint64 pos = posMap[CHANNEL_STYLE_WEAPON];

		for (uint32 index = 0; index < g_wave[channel].count; index++)
		{
			// @Optimize: Create wave item reference.

			Log("g_wave[%u][%u] addr %llX", channel, index, g_wave[channel][index].addr);
			Log("g_wave[%u][%u] size %X"  , channel, index, g_wave[channel][index].size);

			FMOD_SYSTEM * FMOD_system = *(FMOD_SYSTEM **)(appBaseAddr + 0x5DE3D0);

			FMOD_CREATESOUNDEXINFO info = {};
			info.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
			info.length = g_wave[channel][index].size;

			SOUND_ITEM & item = soundItem[channel][index];
			item.pos = pos;

			// true size : size from metadata + 0x30
			// vagi size : size from metadata + 0x10

			// In this case vagi size is used, so true size - 0x20.

			item.size = (uint64)(g_wave[channel][index].size - 0x20);

			// true size when registering them

			FMOD_RESULT result = FMOD_System_CreateSound
			(
				FMOD_system,
				g_wave[channel][index].addr,
				FMOD_CREATECOMPRESSEDSAMPLE | FMOD_OPENMEMORY | FMOD_LOWMEM,
				&info,
				&item.sound
			);
			if (result != FMOD_OK)
			{
				Log("FMOD_System_CreateSound failed. result %X", result);
				return;
			}

			pos += item.size;
		}
	}

	Log("soundMap [%u] %llX", channel, soundMap [channel]);
	Log("soundItem[%u] %llX", channel, soundItem[channel]);







	Log("Compile End");
	LogNewLine();

}






static bool InitPosMap()
{
	byte * file = 0;
	uint64 fileSize = 0;
	file = LoadFile("data\\dmc3\\GData.afs\\SpuMap.bin", &fileSize);
	if (!file)
	{
		Log("LoadFile failed.");
		return false;
	}
	uint64 pos = 0x5020;
	for (uint8 channel = 0; channel < MAX_CHANNEL; channel++)
	{
		posMap[channel] = pos;
		pos += ((uint32 *)(file + 0x10))[channel];
		Log("posMap[%u] %llX", channel, posMap[channel]);
	}
	return true;
}




static void Process()
{

	Compile(CHANNEL_STYLE_WEAPON, MAX_PROG_SECT);


}












bool System_Sound_Init()
{
	LogFunction();
	dword error = 0;
	for (uint8 channel = 0; channel < MAX_CHANNEL; channel++)
	{
		struct VAR_PROC
		{
			void * addr;
			uint64 size;
		};
		VAR_PROC var[] =
		{
			{ &g_prog[channel].addr, (1 * 1024 * 1024                          ) },
			{ &g_prog[channel].off , (MAX_SOUND_PER_CHANNEL * sizeof(uint32)   ) },
			{ &g_smpl[channel].addr, (MAX_SOUND_PER_CHANNEL * sizeof(SMPL_ITEM)) },
			{ &g_vagi[channel].addr, (MAX_SOUND_PER_CHANNEL * sizeof(VAGI_ITEM)) },
			{ &g_wave[channel].addr, (8 * 1024 * 1024                          ) },
			{ &g_wave[channel].off , (MAX_SOUND_PER_CHANNEL * sizeof(uint32)   ) },
			{ &g_wave[channel].size, (MAX_SOUND_PER_CHANNEL * sizeof(uint32)   ) },
			{ &soundMap[channel]   , (1 * 1024 * 1024                          ) },
			{ &soundItem[channel]  , (1 * 1024 * 1024                          ) }, // @Research: Use game's array.
		};
		for (uint8 index = 0; index < countof(var); index++)
		{
			void * & addr = *(void **)var[index].addr;
			SetLastError(0);
			addr = VirtualAllocEx(appProcess, 0, var[index].size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
			error = GetLastError();
			if (!addr)
			{
				Log("VirtualAllocEx failed. %u %u %X", channel, index, error);
				return false;
			}
		}
		Log("g_prog   [%u] addr %llX", channel, g_prog[channel].addr);
		Log("g_prog   [%u] off  %llX", channel, g_prog[channel].off);
		Log("g_smpl   [%u] addr %llX", channel, g_smpl[channel].addr);
		Log("g_vagi   [%u] addr %llX", channel, g_vagi[channel].addr);
		Log("g_wave   [%u] addr %llX", channel, g_wave[channel].addr);
		Log("g_wave   [%u] off  %llX", channel, g_wave[channel].off);
		Log("g_wave   [%u] size %llX", channel, g_wave[channel].size);
		Log("soundMap [%u]      %llX", channel, soundMap[channel]);
		Log("soundItem[%u]      %llX", channel, soundItem[channel]);
	}






	/*
	C:\Program Files (x86)\Steam\steamapps\common\Devil May Cry HD Collection\data\dmc3\GData.afs
	*/




	// Style Weapon

	const char * archiveName[] =
	{
		"data\\dmc3\\GData.afs\\snd_sty02.pac",
		"data\\dmc3\\GData.afs\\snd_sty03.pac",
		"data\\dmc3\\GData.afs\\snd_sty04.pac",
		"data\\dmc3\\GData.afs\\snd_sty05.pac",
	};


	uint8 id[64] =
	{
		PROG_SECT_TRICKSTER,
		PROG_SECT_ROYALGUARD,
		PROG_SECT_QUICKSILVER,
		PROG_SECT_DOPPELGANGER,
	};




	for (uint8 archiveIndex = 0; archiveIndex < countof(archiveName); archiveIndex++)
	{
		byte   * archive = 0;
		uint64   size    = 0;
		archive = LoadFile(archiveName[archiveIndex], &size);
		if (!archive)
		{
			return false;
		}
		Decompile(archive, CHANNEL_STYLE_WEAPON, id[archiveIndex]);
	}












	if (!InitPosMap())
	{
		return false;
	}

	


	// @Todo: Def free memory!


	{
		FUNC func = CreateFunction(Process);
		WriteJump((appBaseAddr + 0x32901), func.addr);
	}





	{

		// @Todo: edx also has to be adjusted.

		byte sect0[] =
		{
			0x48, 0x8D, 0x3D, 0x00, 0x00, 0x00, 0x00,                   //lea rdi,[dmc3.exe+5DE5B0]
			0x80, 0x79, 0x0C, 0x00,                                     //cmp byte ptr [rcx+0C],CHANNEL_STYLE_WEAPON
			0x75, 0x0A,                                                 //jne short
			0x48, 0xBF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rdi,soundItem[CHANNEL_STYLE_WEAPON] // @Todo: Make dynamic!
		};
		FUNC func = CreateFunction(0, (appBaseAddr + 0x321E7), false, true, sizeof(sect0));

		memcpy(func.sect0, sect0, sizeof(sect0));






		WriteAddress(func.addr, (appBaseAddr + 0x5DE5B0), 7);


		*(uint8 *)(func.addr + 0xA) = CHANNEL_STYLE_WEAPON;

		*(SOUND_ITEM **)(func.addr + 0xF) = soundItem[CHANNEL_STYLE_WEAPON];

		//WriteJump((func.addr + 0x17), (appBaseAddr + 0x321E7));

		WriteJump((appBaseAddr + 0x321E0), func.addr, 2); // @Todo: Not always required, add toggle.
	}

















	return true;
}
