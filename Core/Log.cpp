#include "Log.h"

char Core_Log_path[64];

// @Todo: Add proper check for directory.
void Core_Log_Init
(
	const char * directoryName,
	const char * filename
)
{
	CreateDirectoryA(directoryName, 0);
	snprintf(Core_Log_path, sizeof(Core_Log_path), "%s\\%s", directoryName, filename);
	DeleteFileA(Core_Log_path);
}
