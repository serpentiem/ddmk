#include "File.h"

bool ExtractFile(const char * str)
{
	Log("%s %s", FUNC_NAME, str);

	zip_error result = {};
	zip * archive = zip_open("data\\dmc3\\dmc3-0.nbz", 0, &result.zip_err);
	if (!archive)
	{
		Log("Unable to open archive.");
		return false;
	}

	char buffer[64];
	sprintf(buffer, "GData.afs/%s", str);
	zip_file * file = zip_fopen(archive, buffer, 0);
	if (!file)
	{
		zip_close(archive);
		Log("Unable to open file. %s", buffer);
		return false;
	}

	zip_stat_t stats = {};
	zip_stat_init(&stats);
	zip_stat(archive, buffer, 0, &stats);

	SetLastError(0);
	BYTE * addr = (BYTE *)VirtualAllocEx(appProcess, 0, stats.size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	DWORD error = GetLastError();

	if (!addr && error)
	{
		zip_fclose(file);
		zip_close(archive);
		Log("VirtualAllocEx failed. error %X", GetLastError());
		return false;
	}

	zip_fread(file, addr, stats.size);
	zip_fclose(file);
	zip_close(archive);

	sprintf(buffer, "data\\dmc3\\GData.afs\\%s", str);
	HANDLE _file = CreateFileA(buffer, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	if (_file == INVALID_HANDLE_VALUE)
	{
		Log("Unable to retrieve valid handle. error %X", GetLastError());
		return false;
	}

	DWORD bytesWritten = 0;
	OVERLAPPED overlap = {};
	WriteFile(_file, addr, (DWORD)stats.size, &bytesWritten, &overlap);
	CloseHandle(_file);

	Log("bytesWritten %u", bytesWritten);
	Log("size         %u", (DWORD)stats.size);

	return true;
}

BYTE * LoadFile(const char * str)
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
	BYTE * addr = (BYTE *)VirtualAllocEx(appProcess, 0, fi.nFileSizeLow, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	DWORD error = GetLastError();
	if (!addr && error)
	{
		CloseHandle(file);
		Log("VirtualAllocEx failed. error %X", GetLastError());
		return 0;
	}

	DWORD bytesRead = 0;
	OVERLAPPED overlap = {};
	ReadFile(file, addr, fi.nFileSizeLow, &bytesRead, &overlap);
	CloseHandle(file);

	Log("bytesRead %u", bytesRead);
	Log("size      %u", fi.nFileSizeLow);

	return addr;
}

void * AdjustPointersProxy = 0;

void AdjustPointers(BYTE * addr)
{
	LogFunction();
	if (addr[0] == 'P' && addr[1] == 'A' && addr[2] == 'C')
	{
		uint32 count = *(uint32 *)(addr + 4);
		for (uint32 i = 0; i < count; i++)
		{
			uint32 off = *(uint32 *)(addr + 8 + (i * 4));
			((void(*)(BYTE *))AdjustPointersProxy)((addr + off));
			Log("%.16llX", (addr + off));
		}
		return;
	}
	((void(*)(BYTE *))AdjustPointersProxy)(addr);
}

void System_File_Init()
{
	LogFunction();

	// Modes
	// 0 Memory
	// 1 Archive
	// 2 Local

	{
		BYTE payload[] =
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
