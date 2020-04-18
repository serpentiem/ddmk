#pragma once
#include "DataTypes.h"
#include "File.h"
#include "Log.h"
#include "Windows.h"

extern const char   * Config_directory;
extern const char   * Config_file;
extern       char     Config_path[64];
extern       byte8   * Config_addr;
extern       uint32   Config_size;

void SaveConfig();
void LoadConfig();

void Config_Init();
