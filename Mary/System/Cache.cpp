#include "Cache.h"

constexpr bool debug = true;

byte8 * System_Cache_file[MAX_CACHE_FILE] = {};
byte8 * demo_pl000_00_3 = 0;

PrivateStart;

uint32 g_pos = 0;

const char * g_fileName[MAX_CACHE_FILE] =
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

PrivateEnd;

byte8 * System_Cache_PushFile(const char * fileName)
{
	if constexpr (debug)
	{
		LogFunction();
	}

	auto addr = (System_Memory_addr + (512 * 1024 * 1024));

	byte8 * file = 0;
	uint32 fileSize = 0;

	// @Todo: Rename to System_File_LoadFile.

	file = LoadGameFile(fileName, &fileSize, addr);
	if (!file)
	{
		Log("LoadGameFile failed.");
		return 0;
	}

	g_pos += fileSize;

	if constexpr (debug)
	{
		Log("g_pos %X", g_pos);
	}
	Align<uint32>(g_pos, 0x800);
	if constexpr (debug)
	{
		Log("file     %.16llX %s", file, fileName);
		Log("fileSize %X", fileSize);
		Log("g_pos %X", g_pos);
	}

	return addr;
}

void System_Cache_Init()
{
	LogFunction();

	CreateDirectoryA("data\\dmc3\\GData.afs", 0);

	for (uint8 index = 0; index < MAX_CACHE_FILE; index++)
	{
		auto file = System_Cache_PushFile(g_fileName[index]);
		if (!file)
		{
			Log("System_Cache_PushFile failed.");
			return;
		}
		AdjustPointers(file);
		System_Cache_file[index] = file;
	}
	{
		auto file = System_Cache_PushFile("demo_pl000_00_3.pac");
		if (file)
		{
			AdjustPointers(file);
			demo_pl000_00_3 = file;
		}
	}
}
