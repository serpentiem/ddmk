#include "Sound.h"

// @Todo: Update / merge with System's LoadFile.

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

SPS g_progSectOff = {}; // @Todo: Rename.
SPS g_prog = {};
SPS g_smpl = {};
SPS g_vagi = {};
SPS g_wave = {};

static void Decompile(byte * archive)
{
	uint32 fileCount = *(uint32 *)(archive + 4);
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
				PROG & prog = *(PROG *)(file + head.progOff);
				printf("sectCount %u\n", prog.sectCount);
				printf("\n");

				constexpr uint64 sectSize = sizeof(PROG_SECTION);
				constexpr uint64 itemSize = sizeof(PROG_ITEM);

				auto Process = [&](uint32 off)
				{
					*(uint32 *)(g_progSectOff.addr + g_progSectOff.pos) = (uint32)g_prog.pos;
					g_progSectOff.pos += 4;
					g_progSectOff.count++;

					PROG_SECTION & sect = *(PROG_SECTION *)(file + head.progOff + off);
					memcpy((g_prog.addr + g_prog.pos), &sect, sectSize);
					g_prog.pos += sectSize;

					printf("itemCount %u\n", sect.itemCount);

					for (uint8 itemIndex = 0; itemIndex < sect.itemCount; itemIndex++)
					{
						PROG_ITEM & item = ((PROG_ITEM *)(file + head.progOff + off + sectSize))[itemIndex];
						memcpy((g_prog.addr + g_prog.pos), &item, itemSize);

						//PROG_ITEM & newItem = *(PROG_ITEM *)(g_prog.addr + g_prog.pos);
						//newItem.id += smpl_count;

						g_prog.pos += itemSize;
					}

					g_prog.count++; // @Review: Not needed.
				};

				bool special = false;

				for (uint32 sectIndex = 0; sectIndex < (prog.sectCount + 1); sectIndex++)
				{
					uint32 off = ((uint32 *)(file + head.progOff + 0x10))[sectIndex];
					if (off == 0xFFFFFFFF)
					{
						special = true;
						break;
					}
					printf("off %X\n", off);
					Process(off);
				}
				if (special)
				{
					printf("Special\n");
					uint32 off = *(uint32 *)(file + head.progOff + 0x10 + (prog.sectCount * 4));
					printf("off %X\n", off);
					Process(off);
				}
				printf("\n");
				printf("g_prog addr  %llX\n", g_prog.addr);
				printf("g_prog pos   %llX\n", g_prog.pos);
				printf("g_prog count %llu\n", g_prog.count);
				printf("\n");
				printf("g_progSectOff addr  %llX\n", g_progSectOff.addr);
				printf("g_progSectOff pos   %llX\n", g_progSectOff.pos);
				printf("g_progSectOff count %llu\n", g_progSectOff.count);
				printf("\n");
			}

			printf("Smpl\n");
			{
				SMPL & smpl = *(SMPL *)(file + head.smplOff);

				constexpr uint64 itemSize = sizeof(SMPL_ITEM);

				printf("itemCount %u\n", smpl.itemCount);

				for (uint32 itemIndex = 0; itemIndex < (smpl.itemCount + 1); itemIndex++)
				{
					SMPL_ITEM & item = ((SMPL_ITEM *)(file + head.smplOff + 0x10))[itemIndex];
					memcpy((g_smpl.addr + g_smpl.pos), &item, itemSize);

					//SMPL_ITEM & newItem = *(SMPL_ITEM *)(g_smpl.addr + g_smpl.pos);
					//newItem.id += vagi_count;

					g_smpl.pos += itemSize;
					g_smpl.count++;
				}

				printf("\n");
				printf("g_smpl addr  %llX\n", g_smpl.addr);
				printf("g_smpl pos   %llX\n", g_smpl.pos);
				printf("g_smpl count %llu\n", g_smpl.count);
				printf("\n");
			}

			printf("Vagi\n");
			{
				VAGI & vagi = *(VAGI *)(file + head.vagiOff);

				constexpr uint64 itemSize = sizeof(VAGI_ITEM);

				printf("itemCount %u\n", vagi.itemCount);

				for (uint32 itemIndex = 0; itemIndex < (vagi.itemCount + 1); itemIndex++)
				{
					VAGI_ITEM & item = ((VAGI_ITEM *)(file + head.vagiOff + 0x10))[itemIndex];
					memcpy((g_vagi.addr + g_vagi.pos), &item, itemSize);

					g_vagi.pos += itemSize;
					g_vagi.count++;
				}

				printf("\n");
				printf("g_vagi addr  %llX\n", g_vagi.addr);
				printf("g_vagi pos   %llX\n", g_vagi.pos);
				printf("g_vagi count %llu\n", g_vagi.count);
				printf("\n");

				waveItemCount = (vagi.itemCount + 1);
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
			//printf("match found! %u\n", fileIndex);


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
		End:;
	}
}

void Compile()
{
}
