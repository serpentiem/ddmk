#pragma once
#include "../Core/Core.h"

enum ACTOR_
{
	ACTOR_ONE,
	MAX_ACTOR,
};


enum CHAR_
{
	CHAR_DANTE,
	CHAR_LDK,
	CHAR_SUPER_DANTE,
	MAX_CHAR,
};



enum OrbFlags_
{
	OrbFlags_GreenOrbTaken = 0x200000,
	OrbFlags_RedOrbTaken   = 0x400000,
};


enum EVENT_
{
	EVENT_TELEPORT = 0x10000000,
};


enum GAMEPAD_
{
	GAMEPAD_VOID           = 0x0000,
	GAMEPAD_LEFT_TRIGGER   = 0x0001,
	GAMEPAD_RIGHT_TRIGGER  = 0x0002,
	GAMEPAD_LEFT_SHOULDER  = 0x0004,
	GAMEPAD_RIGHT_SHOULDER = 0x0008,
	GAMEPAD_Y              = 0x0010,
	GAMEPAD_B              = 0x0020,
	GAMEPAD_A              = 0x0040,
	GAMEPAD_X              = 0x0080,
	GAMEPAD_BACK           = 0x0100,
	GAMEPAD_LEFT_THUMB     = 0x0200,
	GAMEPAD_RIGHT_THUMB    = 0x0400,
	GAMEPAD_START          = 0x0800,
	GAMEPAD_DPAD_UP        = 0x1000,
	GAMEPAD_DPAD_RIGHT     = 0x2000,
	GAMEPAD_DPAD_DOWN      = 0x4000,
	GAMEPAD_DPAD_LEFT      = 0x8000,
};




enum MODE_
{
	MODE_EASY           = 2,
	MODE_NORMAL         = 3,
	MODE_HARD           = 5,
	MODE_DANTE_MUST_DIE = 6,
};




enum WEAPON_
{
	WEAPON_ALASTOR        = 0,
	WEAPON_IFRIT          = 1,
	WEAPON_SPARDA_AERIAL  = 2,
	WEAPON_SPARDA         = 3,
	WEAPON_FORCE_EDGE     = 4,
	WEAPON_HANDGUN        = 1,
	WEAPON_SHOTGUN        = 2,
	WEAPON_GRENADEGUN     = 3,
	WEAPON_NIGHTMARE_BETA = 4,
	MELEE_WEAPON_COUNT    = 5,
	RANGED_WEAPON_COUNT   = 4,
	MAX_MELEE_WEAPON      = WEAPON_FORCE_EDGE,
	MAX_RANGED_WEAPON     = WEAPON_NIGHTMARE_BETA,
};



enum WEAPON_FORM_
{
	WEAPON_FORM_DEFAULT,
	WEAPON_FORM_SPARDA,
	WEAPON_FORM_YAMATO,
};





struct ITEM_STRUCT
{
	uint8  category;
	uint8  id;
	uint16 count;
};


enum ITEM_
{
	ITEM_FORCE_EDGE = 5,
	ITEM_ALASTOR    = 6,
	ITEM_IFRIT      = 7,
	ITEM_SPARDA     = 8,
	ITEM_YAMATO     = 9,
};









