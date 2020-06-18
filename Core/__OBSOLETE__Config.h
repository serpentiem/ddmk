#pragma once
#include "DataTypes.h"
#include "File.h"
#include "Log.h"
#include "Utility.h"
#include "Windows.h"

void SaveConfig();
void LoadConfig();

void Core_Config_Init
(
	const char * directoryName,
	const char * filename,
	void       * addr,
	uint32       size
);
