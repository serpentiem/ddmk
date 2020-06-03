#pragma once
#include "../Core/Core.h"






enum MEMORY_SIZE
{
	MEMORY_SIZE_ALL                    = (1 * 1024 * 1024 * 1024),
	MEMORY_SIZE_MAIN                   = (    512  * 1024 * 1024),
	MEMORY_SIZE_STATIC_FILES           = (    128  * 1024 * 1024),
	MEMORY_SIZE_STATIC_FILES_METADATA  = (    1    * 1024 * 1024),
	MEMORY_SIZE_DYNAMIC_FILES          = (    64   * 1024 * 1024),
	MEMORY_SIZE_DYNAMIC_FILES_METADATA = (    1    * 1024 * 1024),
};











extern byte8 * Memory_main;














bool Memory_Init();
void Memory_ToggleExtendVectors(bool enable);
