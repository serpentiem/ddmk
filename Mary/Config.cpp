#include "Config.h"

CONFIG Config;
CONFIG DefaultConfig;

const char * Config_directory = "configs";
const char * Config_file = "Mary.bin";

void * Config_addr = &Config;
uint64 Config_size = sizeof(CONFIG);
