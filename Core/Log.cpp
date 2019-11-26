#include "Log.h"

char Log_path[64];




void LogNewLine()
{
	HANDLE file = CreateFileA(Log_path, FILE_APPEND_DATA, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (file == INVALID_HANDLE_VALUE)
	{
		file = CreateFileA(Log_path, GENERIC_WRITE, 0, 0, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, 0);
		if (file == INVALID_HANDLE_VALUE)
		{
			return;
		}
	}
	char buffer[64] = {};
	snprintf(buffer, sizeof(buffer), "\n");
	dword bytesWritten = 0;
	OVERLAPPED overlap = {};
	WriteFile(file, buffer, (uint32)strlen(buffer), &bytesWritten, &overlap);
	CloseHandle(file);
}










void Log_Init()
{
	CreateDirectoryA(Log_directory, 0);
	snprintf(Log_path, sizeof(Log_path), "%s\\%s", Log_directory, Log_file);
	DeleteFileA(Log_path);
}
