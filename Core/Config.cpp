#include "Config.h"

char Config_path[64];

void SaveConfig()
{
	LogFunction();
	HANDLE file = CreateFileA(Config_path, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	if (file == INVALID_HANDLE_VALUE)
	{
		Log("CreateFile failed. %s %X", Config_path, GetLastError());
		return;
	}
	DWORD bytesWritten = 0;
	OVERLAPPED overlap = {};
	WriteFile(file, Config_addr, (uint32)Config_size, &bytesWritten, &overlap);
	CloseHandle(file);
}

void LoadConfig()
{
	LogFunction();
	HANDLE file = CreateFileA(Config_path, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (file == INVALID_HANDLE_VALUE)
	{
		Log("Unable to open %s.", Config_path);
		SaveConfig();
		return;
	}
	BY_HANDLE_FILE_INFORMATION fi = {};
	GetFileInformationByHandle(file, &fi);
	if (fi.nFileSizeLow != Config_size)
	{
		Log("Size mismatch.");
		CloseHandle(file);
		SaveConfig();
		return;
	}
	DWORD bytesRead = 0;
	OVERLAPPED overlap = {};
	ReadFile(file, Config_addr, fi.nFileSizeLow, &bytesRead, &overlap);
	CloseHandle(file);
}

void Config_Init()
{
	LogFunction();
	CreateDirectoryA(Config_directory, 0);
	snprintf(Config_path, sizeof(Config_path), "%s\\%s", Config_directory, Config_file);
}
