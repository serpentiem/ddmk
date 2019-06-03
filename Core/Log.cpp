#include "Log.h"

char Log_path[64];

char * GetFuncName(const char * prettyFunc)
{
	static char buffer[256] = {};
	static char unknown[] = "Unknown";
	uint64 pos = 0;
	do
	{
		if (prettyFunc[pos] == 0)
		{
			return unknown;
		}
		if (prettyFunc[pos] == ' ')
		{
			break;
		}
		pos++;
	}
	while (true);
	pos++;
	uint64 start = pos;
	do
	{
		if (prettyFunc[pos] == 0)
		{
			return unknown;
		}
		if (prettyFunc[pos] == '(')
		{
			break;
		}
		pos++;
	}
	while (true);
	uint64 end = pos;
	uint64 size = (end - start);
	if ((size + 1) >= sizeof(buffer))
	{
		return unknown;
	}
	memcpy(buffer, (prettyFunc + start), size);
	buffer[size] = 0;
	return buffer;
}

void Log_Init()
{
	CreateDirectoryA(Log_directory, 0);
	snprintf(Log_path, sizeof(Log_path), "%s\\%s", Log_directory, Log_file);
	DeleteFileA(Log_path);
}
