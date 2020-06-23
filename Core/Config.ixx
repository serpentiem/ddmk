#ifndef __MODULE_CORE_CONFIG__
#define __MODULE_CORE_CONFIG__

module;
#include "Includes.h"
export module ModuleName(Core_Config);

import ModuleName(Core_File);
import ModuleName(Core_Log);

#ifdef __INTELLISENSE__
#include "File.ixx"
#include "Log.ixx"
#endif

char     g_path[64] = {};
byte8  * g_addr     = 0;
uint32   g_size     = 0;

export void SaveConfig()
{
	//LogFunction();
	SaveFile(g_path, g_addr, g_size);
}

export void LoadConfig()
{
	//LogFunction();
	byte8 * file = 0;
	uint32 size = 0;
	file = LoadFile(g_path, &size);
	if (!file)
	{
		SaveConfig();
		return;
	}
	if (size != g_size)
	{
		Log("Size mismatch.");
		SaveConfig();
		return;
	}
	memcpy(g_addr, file, size);
}

export void Core_Config_Init
(
	const char * directoryName,
	const char * filename,
	void       * addr,
	uint32       size
)
{
	LogFunction();
	CreateDirectoryA(directoryName, 0);
	snprintf(g_path, sizeof(g_path), "%s\\%s", directoryName, filename);
	g_addr = reinterpret_cast<byte8 *>(addr);
	g_size = size;
}

#endif
