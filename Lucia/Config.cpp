#include "Config.h"

CONFIG Config;
CONFIG DefaultConfig;

const char * Config_directory = "configs";
const char * Config_file      = "Lucia.bin";

byte * Config_addr = (byte *)&Config;
uint32 Config_size = (uint32)sizeof(CONFIG);
