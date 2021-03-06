#pragma once

enum ACTOR_
{
	ACTOR_ONE,
	ACTOR_TWO,
	ACTOR_THREE,
	ACTOR_FOUR,
	MAX_ACTOR,
};

enum CHAR_
{
	CHAR_DANTE,
	CHAR_NERO,
	CHAR_VERGIL,
	CHAR_TRISH,
	CHAR_LADY,
	MAX_CHAR,
};


//enum CHAR_DATA_
//{
//	CHAR_DATA_DANTE_OFF    = 0x00000168,
//	CHAR_DATA_DANTE_COUNT  = 0x00000042,
//	CHAR_DATA_NERO_OFF     = 0x00000270,
//	CHAR_DATA_NERO_COUNT   = 0x0000003C,
//	CHAR_DATA_VERGIL_OFF   = 0x00000360,
//	CHAR_DATA_VERGIL_COUNT = 0x0000003F,
//	CHAR_DATA_TRISH_OFF    = 0x0000045C,
//	CHAR_DATA_TRISH_COUNT  = 0x00000042,
//	CHAR_DATA_LADY_OFF     = 0x00000564,
//	CHAR_DATA_LADY_COUNT   = 0x0000003E,
//};
//




enum EVENT_
{
	EVENT_GAME,
	EVENT_PAUSE,
	EVENT_TELEPORT
};





enum GAME_SELECT_
{
	GAME_SELECT_DANTE_NERO,
	GAME_SELECT_VERGIL,
	GAME_SELECT_LADY_TRISH,
};



enum MODE_
{
	MODE_HUMAN,
	MODE_DEVIL_HUNTER,
	MODE_SON_OF_SPARDA,
	MODE_DANTE_MUST_DIE,
	MODE_LEGENDARY_DARK_KNIGHT,
};


// heaven or hell is hard mode with one hit kill flag

// hell and hell is the same













enum LOAD_FILE_
{
	LOAD_FILE_UNKNOWN,
	LOAD_FILE_FORCE_LOAD,
	LOAD_FILE_QUEUE,
};






enum SPAWN_TYPE_
{
	SPAWN_TYPE_ACTOR = 13,
};


enum DLC_
{
	DLC_TRISH_LADY_COSTUMES = 359496,
};




enum COSTUME_
{
	MAX_COSTUME = 4,
};


enum COSTUME_DANTE_
{
	COSTUME_DANTE_DEFAULT,
	COSTUME_DANTE_SPARDA,
	COSTUME_DANTE_SUPER,
	COSTUME_DANTE_DONTE,
};

enum COSTUME_NERO_
{
	COSTUME_NERO_DEFAULT,
	COSTUME_NERO_SCARF,
	COSTUME_NERO_SUPER,
	COSTUME_NERO_VERGIL,
};

enum COSTUME_VERGIL_
{
	COSTUME_VERGIL_DEFAULT,
	COSTUME_VERGIL_SPARDA,
	COSTUME_VERGIL_SUPER,
	COSTUME_VERGIL_RED,
};

enum COSTUME_TRISH_
{
	COSTUME_TRISH_DEFAULT,
	COSTUME_TRISH_GLORIA,
	COSTUME_TRISH_SUPER,
	COSTUME_TRISH_MEGANE,
};

enum COSTUME_LADY_
{
	COSTUME_LADY_DEFAULT,
	COSTUME_LADY_DMC3,
	COSTUME_LADY_SUPER,
	COSTUME_LADY_GYARU,
};










// Main Vector Object

struct MVO
{
	BYTE   ** funcAddr;
	void   *  unknown0;
	uint32    unknown1;
	BYTE   *  addr;
	void   *  unknown2;
	float     unknown3;
};

// Main Vector Data Index

enum MVDI_
{
	MVDI_MISSION_SELECT = 1,
	MVDI_MISSION_START  = 25,
};




//
//
//enum MAIN_GAMEPAD_
//{
//	MAIN_GAMEPAD_OFF  = 0xBC0,
//	MAIN_GAMEPAD_SIZE = 0x200
//};
//
//enum MAIN_KEYBOARD_
//{
//	MAIN_KEYBOARD_SIZE = 0xA40
//};
//
//
//
//
//
//// Main Gamepad Object
//
//struct MGO
//{
//	BYTE data[MAIN_GAMEPAD_SIZE];
//};







enum GAMEPAD_
{
	GAMEPAD_VOID              = 0x00000000,
	GAMEPAD_BACK              = 0x00000001,
	GAMEPAD_LEFT_THUMB        = 0x00000002,
	GAMEPAD_RIGHT_THUMB       = 0x00000004,
	GAMEPAD_START             = 0x00000008,
	GAMEPAD_DPAD_UP           = 0x00000010,
	GAMEPAD_DPAD_RIGHT        = 0x00000020,
	GAMEPAD_DPAD_DOWN         = 0x00000040,
	GAMEPAD_DPAD_LEFT         = 0x00000080,
	GAMEPAD_LEFT_SHOULDER     = 0x00000100,
	GAMEPAD_RIGHT_SHOULDER    = 0x00000200,
	GAMEPAD_LEFT_TRIGGER      = 0x00000400,
	GAMEPAD_RIGHT_TRIGGER     = 0x00000800,
	GAMEPAD_Y                 = 0x00001000,
	GAMEPAD_B                 = 0x00002000,
	GAMEPAD_A                 = 0x00004000,
	GAMEPAD_X                 = 0x00008000,
	GAMEPAD_LEFT_STICK_UP     = 0x00010000,
	GAMEPAD_LEFT_STICK_RIGHT  = 0x00020000,
	GAMEPAD_LEFT_STICK_DOWN   = 0x00040000,
	GAMEPAD_LEFT_STICK_LEFT   = 0x00080000,
	GAMEPAD_RIGHT_STICK_UP    = 0x00100000,
	GAMEPAD_RIGHT_STICK_RIGHT = 0x00200000,
	GAMEPAD_RIGHT_STICK_DOWN  = 0x00400000,
	GAMEPAD_RIGHT_STICK_LEFT  = 0x00800000,
	TIER1_GAMEPAD_SIZE = 0x2CC,
	TIER2_GAMEPAD_SIZE = 0x200,
	//ACTOR_INPUT_OFF    = 0x1884,
	//TIER2_GAMEPAD1_OFF = 0xBC0,
};

enum KEYBOARD_
{
	KEYBOARD_SIZE = 0xA40,
};















//MTF_GAMEPAD_SIZE              = 0x2CC,

//
//
//// Character Base Data
//
//struct CBD
//{
//	bool   enable[8];
//	uint32 meleeWeapon;
//	uint32 rangedWeapon;
//	uint32 boughtSkillsCount;
//	uint32 proudSouls;
//	DWORD  expertise[8];
//	uint32 costume;
//	bool   unlockCostume[4];
//};
//
//// Character Base Data Enable Index
//
//enum CBDEI_
//{
//	CBDEI_DEVIL_TRIGGER = 0,
//	CBDEI_AIR_HIKE      = 1,
//	CBDEI_ENEMY_STEP    = 2,
//	CBDEI_SPEED         = 3,
//	CBDEI_GET_MORE_ORBS = 4,
//	CBDEI_TRIGGER_HEART = 5,
//	CBDEI_BURST_ATTACK  = 0,
//	CBDEI_BLASTER       = 1,
//};
//
//
//
//
//
//
//
//
//
//
//
//
//




enum STYLE_
{
	STYLE_SWORDMASTER,
	STYLE_GUNSLINGER,
	STYLE_TRICKSTER,
	STYLE_ROYALGUARD,
	STYLE_DARK_SLAYER,
};







