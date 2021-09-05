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



#define _IntroduceSessionData(name, ...)\
auto name = *reinterpret_cast<byte8 **>(appBaseAddr + 0x5EAB88);\
if (!name)\
{\
	__VA_ARGS__;\
}\
auto & sessionData = *reinterpret_cast<SessionData *>(name)
#define IntroduceSessionData(...) _IntroduceSessionData(Prep_Merge(pool_, __LINE__), __VA_ARGS__)



#define _IntroduceEventData(name, ...)\
auto name = *reinterpret_cast<byte8 **>(appBaseAddr + 0x60B148);\
if (!name)\
{\
	__VA_ARGS__;\
}\
auto & eventData = *reinterpret_cast<EventData *>(name)
#define IntroduceEventData(...) _IntroduceEventData(Prep_Merge(pool_, __LINE__), __VA_ARGS__)



#define _IntroduceWeaponData(name, ...)\
auto name = *reinterpret_cast<byte8 **>(appBaseAddr + 0x60AD10);\
if (!name)\
{\
	__VA_ARGS__;\
}\
auto & weaponData = *reinterpret_cast<WeaponData *>(name)
#define IntroduceWeaponData(...) _IntroduceWeaponData(Prep_Merge(pool_, __LINE__), __VA_ARGS__)





