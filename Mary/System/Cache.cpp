#include "Cache.h"

bool System_Cache_enable = false;
BYTE * cacheAddr = 0;
BYTE * cacheFile[MAX_CACHE_FILES] = {};
BYTE * demo_pl000_00_3 = 0;

BYTE * PushFile(const char * str)
{
	Log("%s %s", FUNC_NAME, str);
	char buffer[64];
	sprintf(buffer, "data\\dmc3\\GData.afs\\%s", str);
	HANDLE file = CreateFileA(buffer, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (file == INVALID_HANDLE_VALUE)
	{
		Log("Unable to retrieve valid handle. error %X", GetLastError());
		if (!ExtractFile(str))
		{
			Log("Unable to extract file. %s", str);
			return 0;
		}
		file = CreateFileA(buffer, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
		if (file == INVALID_HANDLE_VALUE)
		{
			Log("Unable to retrieve valid handle. error %X", GetLastError());
			return 0;
		}
	}
	BY_HANDLE_FILE_INFORMATION fi = {};
	GetFileInformationByHandle(file, &fi);
	static uint64 pos = 0;
	BYTE * addr = (cacheAddr + DEFAULT_CACHE_SIZE + pos);
	DWORD bytesRead = 0;
	OVERLAPPED overlap = {};
	ReadFile(file, addr, fi.nFileSizeLow, &bytesRead, &overlap);
	pos += fi.nFileSizeLow;
	if (pos % 0x800)
	{
		pos += (0x800 - (pos % 0x800));
	}
	CloseHandle(file);

	Log("file      %s",      str             );
	Log("addr      %.16llX", addr            );
	Log("bytesRead %u",      bytesRead       );
	Log("size      %u",      fi.nFileSizeLow );
	Log("pos       %llX",    pos             );

	SetLastError(0);
	return addr;
}

static void CreateCache()
{
	LogFunction();

	Log("cacheAddr %llX", cacheAddr);



	memset((cacheAddr + DEFAULT_CACHE_SIZE), 0, CACHE_SIZE); // Purge Cache
	// Push Files
	{
		const char * str[] =
		{
			"pl000.pac",
			"pl001.pac",
			"pl002.pac",
			"pl005.pac",
			"pl006.pac",
			"pl007.pac",
			"pl008.pac",
			"pl009.pac",
			"pl010.pac",
			"pl011.pac",
			"pl013.pac",
			"pl014.pac",
			"pl015.pac",
			"pl016.pac",
			"pl017.pac",
			"pl018.pac",
			"pl021.pac",
			"pl023.pac",
			"pl025.pac",
			"pl026.pac",
			"pl000_00_0.pac",
			"pl000_00_1.pac",
			"pl000_00_2.pac",
			"pl000_00_3.pac",
			"pl000_00_4.pac",
			"pl000_00_5.pac",
			"pl000_00_6.pac",
			"pl000_00_7.pac",
			"pl000_00_8.pac",
			"pl000_00_9.pac",
			"pl000_00_10.pac",
			"pl000_00_11.pac",
			"pl000_00_12.pac",
			"pl000_00_13.pac",
			"pl000_00_14.pac",
			"pl000_00_15.pac",
			"pl000_00_16.pac",
			"pl000_00_17.pac",
			"pl000_00_18.pac",
			"pl000_00_19.pac",
			"pl000_00_20.pac",
			"pl000_00_21.pac",
			"pl000_00_22.pac",
			"pl000_00_23.pac",
			"pl000_00_24.pac",
			"pl000_00_25.pac",
			"pl000_00_26.pac",
			"pl001_00_0.pac",
			"pl001_00_1.pac",
			"pl001_00_2.pac",
			"pl001_00_31.pac",
			"pl002_00_0.pac",
			"pl002_00_1.pac",
			"pl002_00_2.pac",
			"pl021_00_0.pac",
			"pl021_00_1.pac",
			"pl021_00_2.pac",
			"pl021_00_3.pac",
			"pl021_00_4.pac",
			"pl021_00_5.pac",
			"pl021_00_6.pac",
			"pl021_00_7.pac",
			"pl021_00_8.pac",
			"pl021_00_9.pac",
			"plwp_2sword.pac",
			"plwp_fight.pac",
			"plwp_forceedge.pac",
			"plwp_grenade.pac",
			"plwp_guitar.pac",
			"plwp_gun.pac",
			"plwp_ladygun.pac",
			"plwp_ladygun1.pac",
			"plwp_ladygun3.pac",
			"plwp_laser.pac",
			"plwp_nerosword.pac",
			"plwp_newvergilfight.pac",
			"plwp_newvergilsword.pac",
			"plwp_nunchaku.pac",
			"plwp_rifle.pac",
			"plwp_shotgun.pac",
			"plwp_sword.pac",
			"plwp_sword2.pac",
			"plwp_sword3.pac",
			"plwp_vergilsword.pac",
		};
		for (uint8 i = 0; i < MAX_CACHE_FILES; i++)
		{
			BYTE * addr = PushFile(str[i]);
			DWORD error = GetLastError();
			if (!addr && error)
			{
				Log("Critical error: Failed to load all required files!");
				return;
			}
			AdjustPointers(addr);
			cacheFile[i] = addr;
		}
	}
	{
		BYTE * addr = PushFile("demo_pl000_00_3.pac");
		if (addr)
		{
			AdjustPointers(addr);
			demo_pl000_00_3 = addr;
		}
	}
}

void System_Cache_Init()
{
	LogFunction();
	System_Cache_enable = MAGIC_6 ? true : false;
	if (!System_Cache_enable)
	{
		return;
	}
	CreateDirectoryA("data\\dmc3\\GData.afs", 0);
	// Set Cache Size
	{
		Write<DWORD>((appBaseAddr + 0x30195), (DEFAULT_CACHE_SIZE + CACHE_SIZE));
		Write<DWORD>((appBaseAddr + 0x301AB), (DEFAULT_CACHE_SIZE + CACHE_SIZE));
	}
	// Set FMOD Cache Size
	{
		Write<DWORD>((appBaseAddr + 0x32636), FMOD_CACHE_SIZE);
		Write<DWORD>((appBaseAddr + 0x32659), FMOD_CACHE_SIZE);
	}
	// Get Cache Address
	{
		BYTE sect0[] =
		{
			0xE8, 0x00, 0x00, 0x00, 0x00,                               //call dmcLauncher.exe+490D0
			0x51,                                                       //push rcx
			0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rcx,&cacheAddr
			0x48, 0x89, 0x01,                                           //mov [rcx],rax
			0x59,                                                       //pop rcx
		};
		FUNC func = CreateFunction(0, (appBaseAddr + 0x3019E), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteCall(func.sect0, (appBaseAddr + 0x490D0));
		*(BYTE ***)(func.sect0 + 8) = &cacheAddr;
		WriteJump((appBaseAddr + 0x30199), func.addr);
	}
	// Hook Create Cache
	{
		FUNC func = CreateFunction(CreateCache, (appBaseAddr + 0x2C5E6E));
		WriteJump((appBaseAddr + 0x2C5E69), func.addr);
	}
	// Extend Vectors
	// 130 Effect Manager
	{
		uint16 count = 0x7FFF;
		BYTE * addr = (BYTE *)HighAlloc((count * 0x10) + 8);
		WriteAddress((appBaseAddr + 0x2C0387), addr, 7);
		WriteAddress((appBaseAddr + 0x2C0460), addr, 7);
		WriteAddress((appBaseAddr + 0x2C0639), addr, 7);
		WriteAddress((appBaseAddr + 0x2E3B2E), addr, 7);
		WriteAddress((appBaseAddr + 0x2E3BAE), addr, 7);
		WriteAddress((appBaseAddr + 0x2E826E), addr, 7);
		Write<uint16>((appBaseAddr + 0x2E86D2), count);
		Write<uint16>((appBaseAddr + 0x2E8712), count);
		Write<uint16>((appBaseAddr + 0x2E876E), count);
		Write<uint16>((appBaseAddr + 0x2E87AC), count);
	}
	// 100 Value Manager
	{
		uint16 count = 0x7FFF;
		BYTE * addr = (BYTE *)HighAlloc((count * 0x10) + 8);
		WriteAddress((appBaseAddr + 0x2C0376), addr, 7);
		WriteAddress((appBaseAddr + 0x2C043E), addr, 7);
		WriteAddress((appBaseAddr + 0x2C0663), addr, 7);
		WriteAddress((appBaseAddr + 0x2E824A), addr, 7);
		WriteAddress((appBaseAddr + 0x32447E), addr, 7);
		WriteAddress((appBaseAddr + 0x3244FE), addr, 7);
		WriteAddress((appBaseAddr + 0x324804), addr, 7);
		Write<uint16>((appBaseAddr + 0x324F42), count);
		Write<uint16>((appBaseAddr + 0x324F83), count);
		Write<uint16>((appBaseAddr + 0x324FFE), count);
		Write<uint16>((appBaseAddr + 0x32503C), count);
	}

	Log("System_Cache_Init reached end!");

}
