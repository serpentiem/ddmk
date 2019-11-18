#include "Sound.h"

#pragma warning(disable: 4477) // string format type mismatch

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
		printf("CreateFileA failed. error %X\n", error);
		return 0;
	}
	BY_HANDLE_FILE_INFORMATION fi = {};
	GetFileInformationByHandle(file, &fi);
	SetLastError(0);
	addr = (byte *)VirtualAlloc(0, fi.nFileSizeLow, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	error = GetLastError();
	if (!addr)
	{
		printf("VirtualAlloc failed. error %X\n", error);
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
		printf("CreateFile failed. error %X\n", error);
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
	uint32 * off;
	byte * addr;
	uint64 pos;
	uint64 count;
	PROG_SECT_METADATA & Push(PROG_SECT_METADATA & sect)
	{
		off[count] = (uint32)pos;
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

struct G_WAVE
{
	byte * addr;
	uint64 pos;
	uint64 count;
	byte * Push(byte * item, uint32 itemSize)
	{
		byte * newItem = (addr + pos);
		memcpy(newItem, item, itemSize);
		pos += itemSize;
		count++;
		return newItem;
	}
};

uint64 posMap[MAX_CHANNEL] = {};

G_PROG g_prog = {};
G_SMPL g_smpl = {};
G_VAGI g_vagi = {};
G_WAVE g_wave = {};

bool InitPosMap()
{
	byte * file = 0;
	uint64 fileSize = 0;
	file = LoadFile("SpuMap.bin", &fileSize);
	if (!file)
	{
		printf("LoadFile failed.\n");
		return false;
	}
	uint64 pos = 0x5020;
	for (uint8 channel = 0; channel < MAX_CHANNEL; channel++)
	{
		posMap[channel] = pos;
		pos += ((uint32 *)(file + 0x10))[channel];
		printf("posMap[%u] %llX\n", channel, posMap[channel]);
	}
	return true;
}

static void Decompile(byte * archive)
{
	uint32 & fileCount = *(uint32 *)(archive + 4);
	printf("fileCount %u\n", fileCount);
	printf("\n");

	uint16 smplCount = (uint16)g_smpl.count;
	uint16 vagiCount = (uint16)g_vagi.count;

	uint32 waveItemCount = 0;

	for (uint8 fileIndex = 0; fileIndex < fileCount; fileIndex++)
	{
		dword off = ((dword *)(archive + 8))[fileIndex];
		byte * file = (archive + off);

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
			HEAD & head = *(HEAD *)file;

			printf("Prog\n");
			{
				PROG_METADATA & prog = *(PROG_METADATA *)(file + head.progOff);
				printf("last %u\n", prog.last);
				uint32 sectCount = (prog.last + 1);
				for (uint32 sectIndex = 0; sectIndex < sectCount; sectIndex++)
				{
					uint32 off = ((uint32 *)(file + head.progOff + 0x10))[sectIndex];
					if (off == 0xFFFFFFFF)
					{
						continue;
					}
					printf("off %X\n", off);

					PROG_SECT_METADATA & sect = *(PROG_SECT_METADATA *)(file + head.progOff + off);
					g_prog.Push(sect);

					for (uint8 itemIndex = 0; itemIndex < sect.itemCount; itemIndex++)
					{
						PROG_SECT_ITEM & item = ((PROG_SECT_ITEM *)(file + head.progOff + off + sizeof(PROG_SECT_METADATA)))[itemIndex];
						PROG_SECT_ITEM & newItem = g_prog.Push(item);
						//newItem.id += smplCount;
					}
				}
				printf("\n");
				printf("g_prog addr  %llX\n", g_prog.addr);
				printf("g_prog pos   %llX\n", g_prog.pos);
				printf("g_prog count %u\n", g_prog.count);
				printf("\n");
			}

			printf("Smpl\n");
			{
				SMPL_METADATA & smpl = *(SMPL_METADATA *)(file + head.smplOff);
				printf("last %u\n", smpl.last);
				uint32 itemCount = (smpl.last + 1);
				for (uint32 itemIndex = 0; itemIndex < itemCount; itemIndex++)
				{
					SMPL_ITEM & item = ((SMPL_ITEM *)(file + head.smplOff + 0x10))[itemIndex];
					SMPL_ITEM & newItem = g_smpl.Push(item);
					//newItem.id += vagiCount;
				}
				printf("\n");
				printf("g_smpl addr  %llX\n", g_smpl.addr);
				printf("g_smpl count %llu\n", g_smpl.count);
				printf("\n");
			}

			printf("Vagi\n");
			{
				VAGI_METADATA & vagi = *(VAGI_METADATA *)(file + head.vagiOff);
				printf("last %u\n", vagi.last);
				uint32 itemCount = (vagi.last + 1);
				for (uint32 itemIndex = 0; itemIndex < itemCount; itemIndex++)
				{
					VAGI_ITEM & item = ((VAGI_ITEM *)(file + head.vagiOff + 0x10))[itemIndex];
					VAGI_ITEM & newItem = g_vagi.Push(item);
					//newItem.off = 0;
				}
				printf("\n");
				printf("g_vagi addr  %llX\n", g_vagi.addr);
				printf("g_vagi count %llu\n", g_vagi.count);
				printf("\n");

				waveItemCount = itemCount;
			}
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
			printf("waveItemCount %u\n", waveItemCount);
			uint32 pos = 0;
			for (uint32 itemIndex = 0; itemIndex < waveItemCount; itemIndex++)
			{
				byte * item = (file + pos);
				uint32 itemSize = (Reverse((uint32 *)(item + 0xC)) + 0x30);

				printf("item     %llX\n", item);
				printf("itemSize %X\n", itemSize);

				g_wave.Push(item, itemSize);
				pos += itemSize;
			}
			printf("\n");
			printf("g_wave addr  %llX\n", g_wave.addr);
			printf("g_wave pos   %llX\n", g_wave.pos);
			printf("g_wave count %llu\n", g_wave.count);
			printf("\n");
		}
		End:;
	}
}

void Compile()
{
	printf("Compile\n");
	printf("\n");
	dword error = 0;

	printf("Vagi\n");
	printf("\n");
	{
		SetLastError(0);
		byte * addr = (byte *)VirtualAlloc(0, (1 * 1024 * 1024), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		error = GetLastError();
		if (!addr)
		{
			printf("VirtualAlloc failed. error %X\n", error);
			return;
		}
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

		{
			head.progOff = (uint32)pos;

			PROG_METADATA & prog = *(PROG_METADATA *)(addr + pos);
			pos += sizeof(PROG_METADATA);
			Align();

			uint32 * off = (uint32 *)(addr + pos);
			for (uint64 sect = 0; sect < g_prog.count; sect++)
			{
				off[sect] = (g_prog.off[sect] + (uint32)(0x10 + (g_prog.count * sizeof(uint32))));
				pos += sizeof(uint32);
			}
			memcpy((addr + pos), g_prog.addr, g_prog.pos);
			pos += g_prog.pos;
			Align();

			prog.signature[0] = 'P';
			prog.signature[1] = 'r';
			prog.signature[2] = 'o';
			prog.signature[3] = 'g';
			prog.size = (uint32)(pos - head.progOff);
			prog.last = (uint32)(g_prog.count - 1);
		}

		{
			head.smplOff = (uint32)pos;

			SMPL_METADATA & smpl = *(SMPL_METADATA *)(addr + pos);
			pos += sizeof(SMPL_METADATA);
			Align();

			uint64 size = (g_smpl.count * sizeof(SMPL_ITEM));
			memcpy((addr + pos), g_smpl.addr, size);
			pos += size;
			Align();

			smpl.signature[0] = 'S';
			smpl.signature[1] = 'm';
			smpl.signature[2] = 'p';
			smpl.signature[3] = 'l';
			smpl.size = (uint32)(pos - head.smplOff);
			smpl.last = (uint32)(g_smpl.count - 1);
		}

		{
			head.vagiOff = (uint32)pos;

			VAGI_METADATA & vagi = *(VAGI_METADATA *)(addr + pos);
			pos += sizeof(VAGI_METADATA);
			Align();

			uint64 size = (g_vagi.count * sizeof(VAGI_ITEM));
			memcpy((addr + pos), g_vagi.addr, size);
			pos += size;
			Align();

			vagi.signature[0] = 'V';
			vagi.signature[1] = 'a';
			vagi.signature[2] = 'g';
			vagi.signature[3] = 'i';
			vagi.size = (uint32)(pos - head.vagiOff);
			vagi.last = (uint32)(g_vagi.count - 1);
		}


		head.signature[0] = 'H';
		head.signature[1] = 'e';
		head.signature[2] = 'a';
		head.signature[3] = 'd';



		printf("addr %llX\n", addr);
		printf("pos %llX\n", pos);
	}

	system("pause");
}
