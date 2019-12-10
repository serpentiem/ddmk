#include "Log.h"

char Log_path[64];

void Log_Init()
{
	CreateDirectoryA(Log_directory, 0);
	snprintf(Log_path, sizeof(Log_path), "%s\\%s", Log_directory, Log_file);
	DeleteFileA(Log_path);
}
