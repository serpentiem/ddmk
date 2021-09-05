#pragma once




#define ResetConfig(name)\
ResetConfigHelper\
(\
	activeConfig.name,\
	queuedConfig.name,\
	defaultConfig.name\
)

#define SetConfig(name)\
SetConfigHelper\
(\
	activeConfig.name,\
	queuedConfig.name,\
	defaultConfig.name\
)







#ifdef __GARBAGE__
#endif
