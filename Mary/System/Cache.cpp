
// @Todo: Proper documentation for why 32 bits.

#include "Cache.h"

bool System_Cache_enable = false;



byte * cacheAddr = 0;



uint32 cachePos = (CACHE_SIZE / 2);


byte * cacheFile[MAX_CACHE_FILES] = {};



byte * demo_pl000_00_3 = 0; // @Todo: Supply patch.




byte * PushGameFile(const char * fileName)
{
	LogFunction();

	byte * addr = (cacheAddr + cachePos);
	byte * file = 0;
	uint32 fileSize = 0;

	file = LoadGameFile(fileName, &fileSize, addr);
	if (!file)
	{
		return 0;
	}

	cachePos += fileSize;

	Log("cachePos %X", cachePos);

	Align<uint32>(cachePos, 0x800);

	Log("file     %.16llX %s", file, fileName);
	Log("fileSize %X", fileSize);
	Log("cachePos %X", cachePos);

	return addr;
}







static void CreateCache()
{
	LogFunction();

	Log("cacheAddr %llX", cacheAddr);

	Log("cachePos %X", cachePos);








	//memset((cacheAddr + cachePos), 0, (CACHE_SIZE / 2));


	//memset(cacheAddr, 0, CACHE_SIZE);





	





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
			byte * addr = PushGameFile(str[i]);
			dword error = GetLastError();
			if (!addr && error)
			{
				Log("Critical error: Failed to load all required files!");
				return;
			}

			//HoboBreak();

			AdjustPointers(addr);
			cacheFile[i] = addr;

			//return;

		}
	}
	{
		byte * addr = PushGameFile("demo_pl000_00_3.pac");
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
	//System_Cache_enable = MAGIC_6 ? true : false;
	//if (!System_Cache_enable)
	//{
	//	return;
	//}
	CreateDirectoryA("data\\dmc3\\GData.afs", 0);


	byte * addr = 0;


	{

		byte * pos = (byte *)4096;
		byte * end = (byte *)0x7FFFFFFF;





		addr = (byte *)Alloc(CACHE_SIZE, pos, end);

	}


	{
		byte * pos = (byte *)(addr + CACHE_SIZE);
		byte * end = (byte *)0x7FFFFFFF;
		byte * heapAddr = (byte *)Alloc((8 * 1024 * 1024), pos, end);
		Log("heapAddr %llX", heapAddr);
	}




	//byte * addr = (byte *)Alloc(CACHE_SIZE,)




	//byte * addr = (byte *)VirtualAlloc(0, CACHE_SIZE, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	if (!addr)
	{
		Log("greedy cunt");
		return;
	}




	Log("greedy addr %llX", addr);


	{
		byte sect0[] =
		{
			0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rax,addr
		};
		*(byte **)(sect0 + 2) = addr;
		vp_memcpy((appBaseAddr + 0x30194), sect0, sizeof(sect0));
	}

	cacheAddr = addr;


	//return;


	//HoboBreak();


	//return;

	
	
	CreateCache();






	//Write<uint32>((appBaseAddr + 0x301AB), (CACHE_SIZE / 2));
	//Write<uint32>((appBaseAddr + 0x301AB), CACHE_SIZE);



	//// Set Cache Size
	//{
	//	Write<dword>((appBaseAddr + 0x30195), (DEFAULT_CACHE_SIZE + CACHE_SIZE));
	//	Write<dword>((appBaseAddr + 0x301AB), (DEFAULT_CACHE_SIZE + CACHE_SIZE));
	//}



	// Get Cache Address
	//{
	//	byte sect0[] =
	//	{
	//		0xE8, 0x00, 0x00, 0x00, 0x00,                               //call dmc3.exe+490D0
	//		0x51,                                                       //push rcx
	//		0x48, 0xB9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rcx,&cacheAddr
	//		0x48, 0x89, 0x01,                                           //mov [rcx],rax
	//		0x59,                                                       //pop rcx
	//	};
	//	FUNC func = CreateFunction(0, (appBaseAddr + 0x3019E), false, true, sizeof(sect0));
	//	memcpy(func.sect0, sect0, sizeof(sect0));
	//	WriteCall(func.sect0, (appBaseAddr + 0x490D0));
	//	*(byte ***)(func.sect0 + 8) = &cacheAddr;
	//	WriteJump((appBaseAddr + 0x30199), func.addr);
	//}




	//CreateCache();


	//// Hook Create Cache
	//{
	//	FUNC func = CreateFunction(CreateCache, (appBaseAddr + 0x2C5E6E));
	//	WriteJump((appBaseAddr + 0x2C5E69), func.addr);
	//}


	// @Todo: Create standalone function.


	// Extend Vectors
	// 130 Effect Manager
	{
		uint16 count = 0x7FFF;
		byte * addr = (byte *)HighAlloc((count * 0x10) + 8);
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
		byte * addr = (byte *)HighAlloc((count * 0x10) + 8);
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

	//Log("System_Cache_Init reached end!");

}
