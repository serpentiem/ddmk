#pragma once
#include "../../Core/Core.h"

#include "../Config.h"

#include "File.h"

enum CACHE_
{
	CACHE_SIZE         = (128 * 1024 * 1024),
	DEFAULT_CACHE_SIZE = (260 * 1024 * 1024),
	FMOD_CACHE_SIZE    = (128 * 1024 * 1024),
};

enum CACHE_FILES
{
	pl000,
	pl001,
	pl002,
	pl005,
	pl006,
	pl007,
	pl008,
	pl009,
	pl010,
	pl011,
	pl013,
	pl014,
	pl015,
	pl016,
	pl017,
	pl018,
	pl021,
	pl023,
	pl025,
	pl026,
	pl000_00_0,
	pl000_00_1,
	pl000_00_2,
	pl000_00_3,
	pl000_00_4,
	pl000_00_5,
	pl000_00_6,
	pl000_00_7,
	pl000_00_8,
	pl000_00_9,
	pl000_00_10,
	pl000_00_11,
	pl000_00_12,
	pl000_00_13,
	pl000_00_14,
	pl000_00_15,
	pl000_00_16,
	pl000_00_17,
	pl000_00_18,
	pl000_00_19,
	pl000_00_20,
	pl000_00_21,
	pl000_00_22,
	pl000_00_23,
	pl000_00_24,
	pl000_00_25,
	pl000_00_26,
	pl001_00_0,
	pl001_00_1,
	pl001_00_2,
	pl001_00_31,
	pl002_00_0,
	pl002_00_1,
	pl002_00_2,
	pl021_00_0,
	pl021_00_1,
	pl021_00_2,
	pl021_00_3,
	pl021_00_4,
	pl021_00_5,
	pl021_00_6,
	pl021_00_7,
	pl021_00_8,
	pl021_00_9,
	plwp_2sword,
	plwp_fight,
	plwp_forceedge,
	plwp_grenade,
	plwp_guitar,
	plwp_gun,
	plwp_ladygun,
	plwp_ladygun1,
	plwp_ladygun3,
	plwp_laser,
	plwp_nerosword,
	plwp_newvergilfight,
	plwp_newvergilsword,
	plwp_nunchaku,
	plwp_rifle,
	plwp_shotgun,
	plwp_sword,
	plwp_sword2,
	plwp_sword3,
	plwp_vergilsword,
	MAX_CACHE_FILES,
};

extern bool System_Cache_enable;
extern BYTE * cacheFile[MAX_CACHE_FILES];
extern BYTE * demo_pl000_00_3;

BYTE * PushFile(const char * str);
void System_Cache_Init();
