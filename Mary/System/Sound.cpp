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

struct HEAD
{
	byte signature[4];
	byte unknown[8];
	uint32 size;
	uint32 waveSize;
	dword progOff;
	dword smplOff;
	dword vagiOff;
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
	dword off;
	uint32 size;
	byte unknown[4];
	uint32 sampleRate;
};

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

template <typename T>
struct SPS
{
	T * addr;
	#ifdef _WIN64
	uint64 pos;
	uint64 count;
	uint64 size;
	#else
	uint32 pos;
	uint32 count;
	uint32 size;
	#endif
};

SPS<uint32   > g_progOff = {};
SPS<byte     > g_prog    = {};
SPS<SMPL_ITEM> g_smpl    = {};
SPS<VAGI_ITEM> g_vagi    = {};
SPS<byte     > g_wave    = {};

static void Decompile(byte * archive)
{
	uint32 & fileCount = *(uint32 *)(archive + 4);
	printf("fileCount %u\n", fileCount);
	printf("\n");

	uint16 smpl_count = (uint16)g_smpl.count;
	uint16 vagi_count = (uint16)g_vagi.count;
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

					g_progOff.addr[g_progOff.count] = (uint32)g_prog.pos;
					g_progOff.count++;

					PROG_SECT_METADATA & sect = *(PROG_SECT_METADATA *)(file + head.progOff + off);
					PROG_SECT_METADATA & newSect = *(PROG_SECT_METADATA *)(g_prog.addr + g_prog.pos);
					newSect = sect;
					g_prog.pos += sizeof(PROG_SECT_METADATA);

					printf("itemCount %u\n", sect.itemCount);

					for (uint8 itemIndex = 0; itemIndex < sect.itemCount; itemIndex++)
					{
						PROG_SECT_ITEM & item = ((PROG_SECT_ITEM *)(file + head.progOff + off + sizeof(PROG_SECT_METADATA)))[itemIndex];
						PROG_SECT_ITEM & newItem = *(PROG_SECT_ITEM *)(g_prog.addr + g_prog.pos);
						newItem = item;
						//newItem.id += smpl_count;
						g_prog.pos += sizeof(PROG_SECT_ITEM);
					}
				}

				printf("\n");
				printf("g_progOff addr  %llX\n", g_progOff.addr);
				printf("g_progOff count %llu\n", g_progOff.count);
				printf("\n");
				printf("g_prog addr  %llX\n", g_prog.addr);
				printf("g_prog pos   %llX\n", g_prog.pos);
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
					SMPL_ITEM & newItem = g_smpl.addr[g_smpl.count];
					newItem = item;
					//newItem.id += vagi_count;
					g_smpl.count++;
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

					// new item addr 0

					g_vagi.addr[g_vagi.count] = item;
					g_vagi.count++;
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
				uint32 itemSize = (Reverse((uint32 *)(file + pos + 0xC)) + 0x30);
				printf("itemSize  %X\n", itemSize);

				memcpy((g_wave.addr + g_wave.pos), item, itemSize);
				g_wave.pos += itemSize;
				g_wave.count++;

				pos += itemSize;
			}
			printf("\n");
			printf("g_wave addr  %llX\n", g_wave.addr);
			printf("g_wave pos   %llX\n", g_wave.pos);
			printf("g_wave count %llu\n", g_wave.count);
			printf("\n");
		}
		End:

		system("pause");


	}
}

static void Compile()
{
	LogFunction();
}

static void Process()
{
	LogFunction();
}

void System_Sound_Init()
{
	LogFunction();

	printf("g_progOff addr %llX\n", g_progOff.addr);
	printf("g_prog    addr %llX\n", g_prog.addr);
	printf("g_smpl    addr %llX\n", g_smpl.addr);
	printf("g_vagi    addr %llX\n", g_vagi.addr);
	printf("g_wave    addr %llX\n", g_wave.addr);

	dword error = 0;
	{
		void * varAddr[] =
		{
			&g_progOff.addr,
			&g_prog.addr,
			&g_smpl.addr,
			&g_vagi.addr,
			&g_wave.addr,
		};
		uint64 size[] =
		{
			( 1 * 1024 * 1024),
			( 8 * 1024 * 1024),
			( 8 * 1024 * 1024),
			( 8 * 1024 * 1024),
			(64 * 1024 * 1024),
		};
		for (uint8 index = 0; index < countof(varAddr); index++)
		{
			void * & addr = *(void **)varAddr[index];
			addr = VirtualAlloc(0, size[index], MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
			error = GetLastError();
			if (!addr)
			{
				printf("VirtualAlloc failed. error %X\n", error);
				return;
			}
		}
	}

	printf("g_progOff addr %llX\n", g_progOff.addr);
	printf("g_prog    addr %llX\n", g_prog.addr);
	printf("g_smpl    addr %llX\n", g_smpl.addr);
	printf("g_vagi    addr %llX\n", g_vagi.addr);
	printf("g_wave    addr %llX\n", g_wave.addr);
	printf("\n");

	const char * archiveName[] =
	{
		//"snd_com0.pac",
		"snd_sty02.pac",
		"snd_sty03.pac",
		//"snd_sty04.pac",
		//"snd_sty05.pac",
	};
	for (uint8 archiveIndex = 0; archiveIndex < countof(archiveName); archiveIndex++)
	{
		byte   * archive = 0;
		uint64   size    = 0;
		archive = LoadFile(archiveName[archiveIndex], &size);
		if (!archive)
		{
			return;
		}
		Decompile(archive);
	}
	{
		FUNC func = CreateFunction(Process);
		WriteJump((appBaseAddr + 0x32901), func.addr);
	}
}
