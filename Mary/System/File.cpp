#include "File.h"





bool ExtractGameFile(const char * fileName)
{
	char buffer[128];
	snprintf(buffer, sizeof(buffer), "data\\dmc3\\dmc3-0.nbz");

	zip_error result = {};
	zip * archive = zip_open(buffer, 0, &result.zip_err);
	if (!archive)
	{
		Log("zip_open failed. error %d", result.zip_err);
		return false;
	}

	snprintf(buffer, sizeof(buffer), "GData.afs/%s", fileName);

	zip_file * file = zip_fopen(archive, buffer, 0);
	if (!file)
	{
		zip_close(archive);
		Log("zip_fopen failed. error %d", result.zip_err);
		return false;
	}

	zip_stat_t stats = {};
	zip_stat_init(&stats);
	zip_stat(archive, buffer, 0, &stats);

	dword error = 0;

	SetLastError(0);
	byte * addr = (byte *)VirtualAllocEx(appProcess, 0, stats.size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	error = GetLastError();
	if (!addr)
	{
		zip_fclose(file);
		zip_close(archive);
		Log("VirtualAllocEx failed. error %X", error);
		return false;
	}

	zip_fread(file, addr, stats.size);
	zip_fclose(file);
	zip_close(archive);

	snprintf(buffer, sizeof(buffer), "data\\dmc3\\GData.afs\\%s", fileName);

	SaveFile(addr, (uint32)stats.size, buffer);

	return true;
}











byte * LoadFile(const char * str)
{
	Log("%s %s", FUNC_NAME, str);

	char buffer[64];
	sprintf(buffer, "data\\dmc3\\GData.afs\\%s", str);

	HANDLE file = CreateFileA(buffer, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (file == INVALID_HANDLE_VALUE)
	{
		Log("Unable to retrieve valid handle. error %X", GetLastError());
		return 0;
	}

	BY_HANDLE_FILE_INFORMATION fi = {};
	GetFileInformationByHandle(file, &fi);
	SetLastError(0);
	byte * addr = (byte *)VirtualAllocEx(appProcess, 0, fi.nFileSizeLow, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	dword error = GetLastError();
	if (!addr && error)
	{
		CloseHandle(file);
		Log("VirtualAllocEx failed. error %X", GetLastError());
		return 0;
	}

	dword bytesRead = 0;
	OVERLAPPED overlap = {};
	ReadFile(file, addr, fi.nFileSizeLow, &bytesRead, &overlap);
	CloseHandle(file);

	Log("bytesRead %u", bytesRead);
	Log("size      %u", fi.nFileSizeLow);

	return addr;
}





















void * AdjustPointersProxy = 0;




// Ugh.

void AdjustPointers(byte * addr)
{
	LogFunction();
	if (addr[0] == 'P' && addr[1] == 'A' && addr[2] == 'C')
	{
		uint32 count = *(uint32 *)(addr + 4);
		for (uint32 i = 0; i < count; i++)
		{
			uint32 off = *(uint32 *)(addr + 8 + (i * 4));
			((void(*)(byte *))AdjustPointersProxy)((addr + off));
			Log("%.16llX", (addr + off));
		}
		return;
	}
	((void(*)(byte *))AdjustPointersProxy)(addr);
}

void System_File_Init()
{
	LogFunction();

	// Modes
	// 0 Memory
	// 1 Archive
	// 2 Local

	{
		byte payload[] =
		{
			0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rax,&Config.System.File.preferLocalFiles
			0x8A, 0x00,                                                 //mov al,[rax]
			0x84, 0xC0,                                                 //test al,al
			0x74, 0x0F,                                                 //je short
			0xBA, 0x02, 0x00, 0x00, 0x00,                               //mov edx,00000002
			0xE8, 0x00, 0x00, 0x00, 0x00,                               //call dmcLauncher.exe+327430
			0x48, 0x85, 0xC0,                                           //test rax,rax
			0x75, 0x10,                                                 //jne short
			0x8D, 0x56, 0x01,                                           //lea edx,[rsi+01]
			0x48, 0x8D, 0x8C, 0x24, 0x60, 0x01, 0x00, 0x00,             //lea rcx,[rsp+00000160]
			0xE8, 0x00, 0x00, 0x00, 0x00,                               //call dmcLauncher.exe+327430
		};
		FUNC func = CreateFunction(0, (appBaseAddr + 0x2FDB1), false, true, sizeof(payload));
		memcpy(func.sect0, payload, sizeof(payload));
		*(bool **)(func.sect0 + 2) = &Config.System.File.preferLocalFiles;
		WriteCall((func.sect0 + 0x15), (appBaseAddr + 0x327430));
		WriteCall((func.sect0 + 0x2A), (appBaseAddr + 0x327430));
		WriteJump((appBaseAddr + 0x2FDAC), func.addr);
	}
	{
		FUNC func = CreateFunction((appBaseAddr + 0x1B9FA0));
		AdjustPointersProxy = func.addr;
	}
}
