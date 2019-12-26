
// @Todo: Supply pl000_00_3.pac patch.

#include "Cache.h"


constexpr bool debug = false;




bool System_Cache_enableExtendVectors = false;

byte8 * cacheAddr = 0;
uint32 cachePos = (CACHE_SIZE / 2);
byte8 * cacheFile[MAX_CACHE_FILES] = {};
byte8 * demo_pl000_00_3 = 0;

byte8 * vectorEffectManager = 0;
byte8 * vectorValueManager  = 0;
constexpr uint16 vectorItemCount = 4096;

byte8 * PushGameFile(const char * fileName)
{

	if constexpr (debug)
	{
		LogFunction();

	}

	

	byte8 * addr = (cacheAddr + cachePos);
	byte8 * file = 0;
	uint32 fileSize = 0;

	file = LoadGameFile(fileName, &fileSize, addr);
	if (!file)
	{
		return 0;
	}

	cachePos += fileSize;


	if constexpr (debug)
	{
		Log("cachePos %X", cachePos);
	}
	

	Align<uint32>(cachePos, 0x800);

	if constexpr (debug)
	{
		Log("file     %.16llX %s", file, fileName);
		Log("fileSize %X", fileSize);
		Log("cachePos %X", cachePos);
	}



	return addr;
}

const char * cacheFileName[] =
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

static void CreateCache()
{
	LogFunction();
	for (uint8 id = 0; id < MAX_CACHE_FILES; id++)
	{
		byte8 * file = PushGameFile(cacheFileName[id]);
		if (!file)
		{
			Log("PushGameFile failed.");
			return;
		}
		AdjustPointers(file);
		cacheFile[id] = file;
	}
	{
		byte8 * file = PushGameFile("demo_pl000_00_3.pac");
		if (file)
		{
			AdjustPointers(file);
			demo_pl000_00_3 = file;
		}
	}
}

// @Todo: Recheck.

void System_Cache_Init()
{
	LogFunction();
	CreateDirectoryA("data\\dmc3\\GData.afs", 0);
	byte8 * pos = (byte8 *)0x10000;
	byte8 * end = (byte8 *)0x7FFFFFFF;
	cacheAddr = (byte8 *)Alloc(CACHE_SIZE, pos, end);
	if (!cacheAddr)
	{
		Log("Alloc failed.");
		return;
	}
	byte8 sect0[] =
	{
		0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rax,addr
	};
	*(byte8 **)(sect0 + 2) = cacheAddr;
	vp_memcpy((appBaseAddr + 0x30194), sect0, sizeof(sect0));
	CreateCache();
	{
		constexpr uint64 size = ((vectorItemCount * 0x10) + 8);
		vectorEffectManager = (byte8 *)HighAlloc(size);
		vectorValueManager = (byte8 *)HighAlloc(size);
		if (!vectorEffectManager || !vectorValueManager)
		{
			Log("HighAlloc failed.");
			return;
		}
	}
}

void System_Cache_ToggleExtendVectors(bool enable)
{
	LogFunction(enable);
	System_Cache_enableExtendVectors = enable;
	byte8 * addr = 0;
	uint16 count = 0;
	{
		if (enable)
		{
			addr = vectorEffectManager;
			count = vectorItemCount;
		}
		else
		{
			addr = (appBaseAddr + 0xCAB230);
			count = 304;
		}
		WriteAddress((appBaseAddr + 0x2C0387), addr, 7);
		WriteAddress((appBaseAddr + 0x2C0460), addr, 7);
		WriteAddress((appBaseAddr + 0x2C0639), addr, 7);
		WriteAddress((appBaseAddr + 0x2E3B2E), addr, 7);
		WriteAddress((appBaseAddr + 0x2E3BAE), addr, 7);
		WriteAddress((appBaseAddr + 0x2E826E), addr, 7);
		Write<uint32>((appBaseAddr + 0x2E86D2), count);
		Write<uint32>((appBaseAddr + 0x2E8712), count);
		Write<uint32>((appBaseAddr + 0x2E876E), count);
		Write<uint32>((appBaseAddr + 0x2E87AC), count);
	}
	{
		if (enable)
		{
			addr = vectorValueManager;
			count = vectorItemCount;
		}
		else
		{
			addr = (appBaseAddr + 0xCF1270);
			count = 256;
		}
		WriteAddress((appBaseAddr + 0x2C0376), addr, 7);
		WriteAddress((appBaseAddr + 0x2C043E), addr, 7);
		WriteAddress((appBaseAddr + 0x2C0663), addr, 7);
		WriteAddress((appBaseAddr + 0x2E824A), addr, 7);
		WriteAddress((appBaseAddr + 0x32447E), addr, 7);
		WriteAddress((appBaseAddr + 0x3244FE), addr, 7);
		WriteAddress((appBaseAddr + 0x324804), addr, 7);
		Write<uint32>((appBaseAddr + 0x324F42), count);
		Write<uint32>((appBaseAddr + 0x324F83), count);
		Write<uint32>((appBaseAddr + 0x324FFE), count);
		Write<uint32>((appBaseAddr + 0x32503C), count);
	}
}
