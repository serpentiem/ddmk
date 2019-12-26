#include "Config.h"

CONFIG Config;
CONFIG DefaultConfig;

const char * Config_directory = "configs";
const char * Config_file      = "Mary.bin";

byte8 * Config_addr = (byte8 *)&Config;
uint32 Config_size = (uint32)sizeof(CONFIG);
