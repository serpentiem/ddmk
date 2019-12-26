#include "Config.h"

char Config_path[64];

void SaveConfig()
{
	LogFunction();
	SaveFile(Config_addr, Config_size, Config_path);
}

void LoadConfig()
{
	LogFunction();
	byte8 * file = 0;
	uint32 size = 0;
	file = LoadFile(Config_path, &size);
	if (!file)
	{
		SaveConfig();
		return;
	}
	if (size != Config_size)
	{
		Log("Size mismatch.");
		SaveConfig();
		return;
	}
	memcpy(Config_addr, file, size);
}

void Config_Init()
{
	LogFunction();
	CreateDirectoryA(Config_directory, 0);
	snprintf(Config_path, sizeof(Config_path), "%s\\%s", Config_directory, Config_file);
}
