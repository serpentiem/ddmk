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







// @Todo: Replace old_for_all with old_old_for_all and use the new version from now on.



// @Todo: Put in prep Mary.

#define IntroduceSessionData() auto & sessionData = *reinterpret_cast<SessionData *>(appBaseAddr + 0xC8F250)


// @Research: Consider C90E10 + 58.

#define _IntroduceMissionData(name, ...)\
auto name = *reinterpret_cast<byte8 **>(appBaseAddr + 0xC90E30);\
if (!name)\
{\
	__VA_ARGS__;\
}\
auto & missionData = *reinterpret_cast<MissionData *>(name)
#define IntroduceMissionData(...) _IntroduceMissionData(Prep_Merge(pool_, __LINE__), __VA_ARGS__)




#define _IntroduceMissionActorData(name, ...)\
auto name = *reinterpret_cast<byte8 **>(appBaseAddr + 0xC90E30);\
if (!name)\
{\
	__VA_ARGS__;\
}\
auto & queuedMissionActorData = *reinterpret_cast<QueuedMissionActorData *>(name + 0xC0 );\
auto & activeMissionActorData = *reinterpret_cast<ActiveMissionActorData *>(name + 0x16C)
#define IntroduceMissionActorData(...) _IntroduceMissionActorData(Prep_Merge(pool_, __LINE__), __VA_ARGS__)


#define _IntroduceEventData(name, ...)\
auto name = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E10);\
if (!name)\
{\
	__VA_ARGS__;\
}\
if (!name[8])\
{\
	__VA_ARGS__;\
}\
auto & eventData = *reinterpret_cast<EventData *>(name[8])
#define IntroduceEventData(...) _IntroduceEventData(Prep_Merge(pool_, __LINE__), __VA_ARGS__)

#define _IntroduceNextEventData(name, ...)\
auto name = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E10);\
if (!name)\
{\
	__VA_ARGS__;\
}\
if (!name[12])\
{\
	__VA_ARGS__;\
}\
auto & nextEventData = *reinterpret_cast<NextEventData *>(name[12])
#define IntroduceNextEventData(...) _IntroduceNextEventData(Prep_Merge(pool_, __LINE__), __VA_ARGS__)









#define _IntroduceEventFlags(name, ...)\
auto name = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E30);\
if (!name)\
{\
	__VA_ARGS__;\
}\
if (!name[1])\
{\
	__VA_ARGS__;\
}\
auto eventFlags = reinterpret_cast<byte32 *>(name[1])
#define IntroduceEventFlags(...) _IntroduceEventFlags(Prep_Merge(pool_, __LINE__), __VA_ARGS__)


#define _IntroduceCameraData(name, ...)\
auto name = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC8FBD0);\
if (!name)\
{\
	__VA_ARGS__;\
}\
if (!name[147])\
{\
	__VA_ARGS__;\
}\
auto & cameraData = *reinterpret_cast<CameraData *>(name[147])
#define IntroduceCameraData(...) _IntroduceCameraData(Prep_Merge(pool_, __LINE__), __VA_ARGS__)



#define _IntroduceHUDPointers(name, ...)\
auto name = *reinterpret_cast<byte8 **>(appBaseAddr + 0xC90E28);\
if (!name)\
{\
	__VA_ARGS__;\
}\
name -= 0x180;\
auto hudTop    = *reinterpret_cast<byte8 **>(name + 0x1B070);\
auto hudBottom = *reinterpret_cast<byte8 **>(name + 0x1B078)
#define IntroduceHUDPointers(...) _IntroduceHUDPointers(Prep_Merge(pool_, __LINE__), __VA_ARGS__)
/*
dmc3.exe+23E691 - 48 8D 93 80010000 - lea rdx,[rbx+00000180]
*/



#ifdef __GARBAGE__
#endif
