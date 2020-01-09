#pragma once

enum EVENT_
{
	EVENT_GAME     = 1,
	EVENT_TELEPORT = 2,
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
	// Direction ids are the same for dpad, left stick and right stick.
	GAMEPAD_UP             = 0x1000,
	GAMEPAD_RIGHT          = 0x2000,
	GAMEPAD_DOWN           = 0x4000,
	GAMEPAD_LEFT           = 0x8000,
};

// @Todo: Rename to Binding.

enum CMD_
{
	CMD_VOID,
	CMD_ITEM_SCREEN,
	CMD_EQUIP_SCREEN,
	CMD_MAP_SCREEN,
	CMD_FILE_SCREEN,
	CMD_MELEE_ATTACK,
	CMD_JUMP,
	CMD_STYLE_ACTION,
	CMD_SHOOT,
	CMD_DEVIL_TRIGGER,
	CMD_CHANGE_GUN,
	CMD_CHANGE_TARGET,
	CMD_LOCK_ON,
	CMD_CHANGE_DEVIL_ARMS,
	CMD_DEFAULT_CAMERA,
	CMD_TAUNT,
	MAX_CMD,
};

struct PS2_GAMEPAD
{
	uint32 ready;
	uint32 reserved[3];
	uint8  vibration[4];
	word   buttons[6];
	uint8  rightStickX;
	uint8  rightStickY;
	uint8  leftStickX;
	uint8  leftStickY;
	uint32 unknown[3];
	uint16 rightStickDirection[4];
	uint16 leftStickDirection[4];
	uint16 rightStickDirectionFast[2];
	uint16 leftStickDirectionFast[2];
	uint16 rightStickPosition;
	uint16 leftStickPosition;
	uint16 rightStickDifference;
	uint16 leftStickDifference;
};

struct CAPCOM_GAMEPAD
{
	word   buttons[4];
	uint16 buttonsTimer[2];
	uint16 rightStickDirection[4];
	uint16 rightStickTimer[2];
	uint16 rightStickPosition[2];
	uint16 leftStickDirection[4];
	uint16 leftStickTimer[2];
	uint16 leftStickPosition[2];
};






enum ROOM_
{
	ROOM_START_3             = 2,
	ROOM_START_4             = 100,
	ROOM_START_5             = 111,
	ROOM_START_7             = 127,
	ROOM_START_8             = 300,
	ROOM_START_9             = 201,
	ROOM_START_11            = 212,
	ROOM_START_12            = 217,
	ROOM_START_13            = 229,
	ROOM_START_16            = 106,
	ROOM_START_17            = 133,
	ROOM_START_18            = 400,
	ROOM_START_19            = 406,
	ROOM_CERBERUS            = 6,
	ROOM_GIGAPEDE            = 111,
	ROOM_JESTER_1            = 422,
	ROOM_AGNI_RUDRA          = 121,
	ROOM_VERGIL_1            = 144,
	ROOM_LEVIATHAN           = 302,
	ROOM_NEVAN               = 210,
	ROOM_BEOWULF             = 217,
	ROOM_JESTER_2            = 448,
	ROOM_GERYON              = 228,
	ROOM_VERGIL_2            = 234,
	ROOM_LADY                = 115,
	ROOM_JESTER_3            = 449,
	ROOM_DOPPELGANGER        = 139,
	ROOM_TAIZAI_REBORN       = 420,
	ROOM_CERBERUS_REBORN     = 412,
	ROOM_GIGAPEDE_REBORN     = 413,
	ROOM_AGNI_RUDRA_REBORN   = 414,
	ROOM_LEVIATHAN_REBORN    = 419,
	ROOM_NEVAN_REBORN        = 415,
	ROOM_BEOWULF_REBORN      = 416,
	ROOM_GERYON_REBORN       = 417,
	ROOM_DOPPELGANGER_REBORN = 418,
	ROOM_ARKHAM              = 421,
	ROOM_VERGIL_3            = 411,
};

enum POSITION_
{
	POSITION_CERBERUS            = 2,
	POSITION_GIGAPEDE            = 0,
	POSITION_JESTER_1            = 0,
	POSITION_AGNI_RUDRA          = 3,
	POSITION_VERGIL_1            = 0,
	POSITION_LEVIATHAN           = 0,
	POSITION_NEVAN               = 2,
	POSITION_BEOWULF             = 2,
	POSITION_JESTER_2            = 0,
	POSITION_GERYON_BRIDGE       = 0,
	POSITION_GERYON_GROUND       = 2,
	POSITION_VERGIL_2            = 0,
	POSITION_LADY                = 2,
	POSITION_JESTER_3            = 0,
	POSITION_DOPPELGANGER        = 0,
	POSITION_TAIZAI_REBORN       = 0,
	POSITION_CERBERUS_REBORN     = 0,
	POSITION_GIGAPEDE_REBORN     = 0,
	POSITION_AGNI_RUDRA_REBORN   = 0,
	POSITION_LEVIATHAN_REBORN    = 0,
	POSITION_NEVAN_REBORN        = 0,
	POSITION_BEOWULF_REBORN      = 0,
	POSITION_GERYON_REBORN       = 0,
	POSITION_DOPPELGANGER_REBORN = 0,
	POSITION_ARKHAM              = 0,
	POSITION_VERGIL_3            = 0,
};

#define TRACK_CERBERUS            "afs/sound/Boss_01.adx"
#define TRACK_GIGAPEDE            "afs/sound/T_Boss.adx"
#define TRACK_JESTER_1            "afs/sound/Jester.adx"
#define TRACK_AGNI_RUDRA          "afs/sound/Boss_02.adx"
#define TRACK_VERGIL_1            "afs/sound/Versil_01.adx"
#define TRACK_LEVIATHAN           "afs/sound/Boss_08.adx"
#define TRACK_NEVAN               "afs/sound/Boss_03.adx"
#define TRACK_BEOWULF             "afs/sound/Boss_04.adx"
#define TRACK_JESTER_2            "afs/sound/Jester.adx"
#define TRACK_GERYON              "afs/sound/Boss_05.adx"
#define TRACK_VERGIL_2            "afs/sound/Versil_02.adx"
#define TRACK_LADY                "afs/sound/Lady.adx"
#define TRACK_JESTER_3            "afs/sound/Jester.adx"
#define TRACK_DOPPELGANGER        "afs/sound/Boss_06.adx"
#define TRACK_TAIZAI_REBORN       "afs/sound/Battle_01B.adx"
#define TRACK_CERBERUS_REBORN     "afs/sound/Boss_01B.adx"
#define TRACK_GIGAPEDE_REBORN     "afs/sound/T_BossB.adx"
#define TRACK_AGNI_RUDRA_REBORN   "afs/sound/Boss_02B.adx"
#define TRACK_LEVIATHAN_REBORN    "afs/sound/Boss_08B.adx"
#define TRACK_NEVAN_REBORN        "afs/sound/Boss_03B.adx"
#define TRACK_BEOWULF_REBORN      "afs/sound/Boss_04B.adx"
#define TRACK_GERYON_REBORN       "afs/sound/Boss_05B.adx"
#define TRACK_DOPPELGANGER_REBORN "afs/sound/Boss_06B.adx"
#define TRACK_ARKHAM_1            "afs/sound/Hine_01.adx"
#define TRACK_ARKHAM_2            "afs/sound/Hine_02.adx"
#define TRACK_VERGIL_3            "afs/sound/Versil_03.adx"



























// MaxActor
// ActorOne
// ActorTwo
// ActorThree
// ActorFour



enum MISSION_
{
	MAX_MISSION = 22,
};



enum ACTOR_
{
	ACTOR_ONE,
	ACTOR_TWO,
	ACTOR_THREE,
	ACTOR_FOUR,
	MAX_ACTOR,
};


enum DEVIL_FLUX_
{
	DEVIL_FLUX_START = 1,
	DEVIL_FLUX_END   = 2,
};






enum BODY_COUNT_
{
	BODY_COUNT_DANTE  = 7,
	BODY_COUNT_BOB    = 2,
	BODY_COUNT_LADY   = 1,
	BODY_COUNT_VERGIL = 4,
	MAX_BODY_COUNT    = 7,
};














enum COSTUME_DANTE_
{
	COSTUME_DANTE_DEFAULT,
	COSTUME_DANTE_DEFAULT_COATLESS,
	COSTUME_DANTE_DEFAULT_TORN,
	COSTUME_DANTE_DMC1,
	COSTUME_DANTE_DMC1_COATLESS,
	COSTUME_DANTE_SPARDA,
	COSTUME_DANTE_DEFAULT_TORN_INFINITE_MP,
	COSTUME_DANTE_SPARDA_INFINITE_MP,
	MAX_COSTUME_DANTE,
};
enum COSTUME_BOB_
{
	COSTUME_BOB_DEFAULT,
	MAX_COSTUME_BOB,
};
enum COSTUME_LADY_
{
	COSTUME_LADY_DEFAULT,
	MAX_COSTUME_LADY,
};
enum COSTUME_VERGIL_
{
	COSTUME_VERGIL_DEFAULT,
	COSTUME_VERGIL_DEFAULT_COATLESS,
	COSTUME_VERGIL_DEFAULT_INFINITE_MP,
	COSTUME_VERGIL_SPARDA,
	COSTUME_VERGIL_SPARDA_INFINITE_MP,
	MAX_COSTUME_VERGIL,
};
enum COSTUME_COUNT_
{
	COSTUME_COUNT_DANTE  = MAX_COSTUME_DANTE,
	COSTUME_COUNT_BOB    = MAX_COSTUME_BOB,
	COSTUME_COUNT_LADY   = MAX_COSTUME_LADY,
	COSTUME_COUNT_VERGIL = MAX_COSTUME_VERGIL,
	MAX_COSTUME_COUNT    = MAX_COSTUME_DANTE,
};















enum MOT_DANTE_
{
	MOT_DANTE_BASE,
	MOT_DANTE_DAMAGE,
	MOT_DANTE_TAUNTS,
	MOT_DANTE_REBELLION,
	MOT_DANTE_CERBERUS,
	MOT_DANTE_AGNI_RUDRA,
	MOT_DANTE_NEVAN,
	MOT_DANTE_BEOWULF,
	MOT_DANTE_EBONY_IVORY,
	MOT_DANTE_SHOTGUN,
	MOT_DANTE_ARTEMIS,
	MOT_DANTE_SPIRAL,
	MOT_DANTE_KALINA_ANN,
	MOT_DANTE_SWORDMASTER_REBELLION,
	MOT_DANTE_SWORDMASTER_CERBERUS,
	MOT_DANTE_SWORDMASTER_AGNI_RUDRA,
	MOT_DANTE_SWORDMASTER_NEVAN,
	MOT_DANTE_SWORDMASTER_BEOWULF,
	MOT_DANTE_GUNSLINGER_EBONY_IVORY,
	MOT_DANTE_GUNSLINGER_SHOTGUN,
	MOT_DANTE_GUNSLINGER_ARTEMIS,
	MOT_DANTE_GUNSLINGER_SPIRAL,
	MOT_DANTE_GUNSLINGER_KALINA_ANN,
	MOT_DANTE_TRICKSTER,
	MOT_DANTE_ROYALGUARD,
	MOT_DANTE_QUICKSILVER,
	MOT_DANTE_DOPPELGANGER,
	MAX_MOT_DANTE,
};
enum MOT_BOB_
{
	MOT_BOB_BASE,
	MOT_BOB_DAMAGE,
	MOT_BOB_TAUNTS,
	MOT_BOB_MELEE_STYLE = 31,
	MAX_MOT_BOB         = 4,
};
enum MOT_LADY_
{
	MOT_LADY_BASE,
	MOT_LADY_DAMAGE,
	MOT_LADY_TAUNTS,
	MOT_LADY_KALINA_ANN = 12,
	MAX_MOT_LADY        = 4,
};
enum MOT_VERGIL_
{
	MOT_VERGIL_BASE,
	MOT_VERGIL_DAMAGE,
	MOT_VERGIL_TAUNTS,
	MOT_VERGIL_YAMATO,
	MOT_VERGIL_BEOWULF,
	MOT_VERGIL_FORCE_EDGE,
	MOT_VERGIL_DARK_SLAYER,
	MOT_VERGIL_NERO_ANGELO_YAMATO,
	MOT_VERGIL_NERO_ANGELO_BEOWULF,
	MOT_VERGIL_NERO_ANGELO_FORCE_EDGE,
	MAX_MOT_VERGIL,
};
enum MOT_
{
	MOT_DANTE  = MAX_MOT_DANTE,
	MOT_BOB    = MAX_MOT_BOB,
	MOT_LADY   = MAX_MOT_LADY,
	MOT_VERGIL = MAX_MOT_VERGIL,
	MAX_MOT    = 32,
};











//
//
//enum BUTTON_
//{
//	BUTTON_LEFT_TRIGGER_L2   = 0x0001,
//	BUTTON_RIGHT_TRIGGER_R2  = 0x0002,
//	BUTTON_LEFT_SHOULDER_L1  = 0x0004,
//	BUTTON_RIGHT_SHOULDER_R1 = 0x0008,
//	BUTTON_Y_TRIANGLE        = 0x0010,
//	BUTTON_B_CIRCLE          = 0x0020,
//	BUTTON_A_CROSS           = 0x0040,
//	BUTTON_X_SQUARE          = 0x0080,
//	BUTTON_BACK_SELECT       = 0x0100,
//	BUTTON_LEFT_THUMB_L3     = 0x0200,
//	BUTTON_RIGHT_THUMB_R3    = 0x0400,
//	BUTTON_START             = 0x0800,
//	BUTTON_DPAD_UP           = 0x1000,
//	BUTTON_DPAD_RIGHT        = 0x2000,
//	BUTTON_DPAD_DOWN         = 0x4000,
//	BUTTON_DPAD_LEFT         = 0x8000,
//};
//
//









enum MODE_
{
	MODE_EASY,
	MODE_NORMAL,
	MODE_HARD,
	MODE_VERY_HARD,
	MODE_DANTE_MUST_DIE,
	MAX_MODE,
};











enum CHAR_
{
	CHAR_DANTE,
	CHAR_BOB,
	CHAR_LADY,
	CHAR_VERGIL,
	MAX_CHAR,
};

enum DEVIL_DANTE_
{
	DEVIL_DANTE_REBELLION,
	DEVIL_DANTE_CERBERUS,
	DEVIL_DANTE_AGNI_RUDRA,
	DEVIL_DANTE_NEVAN,
	DEVIL_DANTE_BEOWULF,
	DEVIL_DANTE_SPARDA,
};


enum DEVIL_BOB_
{
	DEVIL_BOB_YAMATO = 1,
};


enum DEVIL_VERGIL_
{
	DEVIL_VERGIL_YAMATO     = 1,
	DEVIL_VERGIL_BEOWULF    = 2,
	DEVIL_VERGIL_FORCE_EDGE = 1,
};












enum STYLE_
{
	STYLE_SWORDMASTER,
	STYLE_GUNSLINGER,
	STYLE_TRICKSTER,
	STYLE_ROYALGUARD,
	STYLE_QUICKSILVER,
	STYLE_DOPPELGANGER,
	MAX_STYLE,
	STYLE_DARK_SLAYER = 2,
};
enum WEAPON_
{
	WEAPON_REBELLION,
	WEAPON_CERBERUS,
	WEAPON_AGNI_RUDRA,
	WEAPON_NEVAN,
	WEAPON_BEOWULF,
	WEAPON_EBONY_IVORY,
	WEAPON_SHOTGUN,
	WEAPON_ARTEMIS,
	WEAPON_SPIRAL,
	WEAPON_KALINA_ANN,
	WEAPON_KALINA_ANN_LADY,
	WEAPON_YAMATO,
	WEAPON_BEOWULF_VERGIL,
	WEAPON_FORCE_EDGE,
	WEAPON_YAMATO_BOB,
	MAX_WEAPON,
};
enum WEAPON_ICON_SIDE_
{
	WEAPON_ICON_SIDE_LEFT,
	WEAPON_ICON_SIDE_RIGHT,
};


enum WEAPON_COUNT_
{
	WEAPON_COUNT_DANTE  = 10,
	WEAPON_COUNT_BOB    = 1,
	WEAPON_COUNT_LADY   = 2,
	WEAPON_COUNT_VERGIL = 3,
};









struct STRING_ITEM
{
	byte8 unknown[8];
	const char * string;
};

struct FILE_ITEM
{
	uint32        category;
	uint32        status;
	uint16        id;
	byte8         padding[6];
	void        * callback;
	STRING_ITEM * stringItem;
	byte8       * file;
	byte8         unknown[32];
};

enum FILE_ITEM_STATUS_
{
	FILE_ITEM_READY = 3,
};



// CFileItem

// EFileItem

// COMBO_1_PART_1










enum MotionRebellion
{
	Combo1Part1 = 3,
	Combo1Part2,
	Combo1Part3,
	Combo2Part2,
	StingerLevel2 = 14,
};


enum SpeedDevil
{
	DanteRebellion,
	DanteCerberus,
	DanteAgniRudra,
	DanteNevan,
	DanteBeowulf,
	DanteSparda,
	VergilYamato,
	VergilBeowulf,
	VergilForceEdge,
	NeroAngeloYamato,
	NeroAngeloBeowulf,
	NeroAngeloForceEdge,
};


// SpeedDevil::DanteRebellion


// SpeedDevilDanteRebellion
// SpeedDevilVergilYamato
// SpeedDevilNeroAngeloYamato




enum SPEED_DEVIL_
{
	SPEED_DEVIL_DANTE_REBELLION,
	SPEED_DEVIL_DANTE_CERBERUS,
	SPEED_DEVIL_DANTE_AGNI_RUDRA,
	SPEED_DEVIL_DANTE_NEVAN,
	SPEED_DEVIL_DANTE_BEOWULF,
	SPEED_DEVIL_DANTE_SPARDA,
	SPEED_DEVIL_VERGIL_YAMATO = 8,
	SPEED_DEVIL_VERGIL_BEOWULF,
	SPEED_DEVIL_VERGIL_FORCE_EDGE,
	SPEED_DEVIL_NERO_ANGELO_YAMATO,
	SPEED_DEVIL_NERO_ANGELO_BEOWULF,
	SPEED_DEVIL_NERO_ANGELO_FORCE_EDGE,
};




//extern byte8 * appBaseAddr;


struct VARS
{
	bool     init;
	uint32 * room;
	uint32 * position;
	uint32 * event;
	uint16 * nextRoom;
	uint16 * nextPosition;
	byte32 * flags;
	uint32 * mission;
	VARS()
	{
		memset(this, 0, sizeof(*this));
		{
			byte8 ** addr = *(byte8 ***)(appBaseAddr + 0xCA8918);
			if (!addr)
			{
				return;
			}
			if (!addr[8])
			{
				return;
			}
			room     = (uint32 *)(addr[8] + 0x18);
			position = (uint32 *)(addr[8] + 0x1C);
			event    = (uint32 *)(addr[8] + 0x20);
			if (!addr[12])
			{
				return;
			}
			nextRoom     = (uint16 *)(addr[12] + 0x164);
			nextPosition = (uint16 *)(addr[12] + 0x166);
		}
		{
			byte8 ** addr = *(byte8 ***)(appBaseAddr + 0xC90E30);
			if (!addr)
			{
				return;
			}
			if (!addr[1])
			{
				return;
			}
			flags = (byte32 *)addr[1];
		}
		mission = (uint32 *)(appBaseAddr + 0xC8F250);
		init = true;
	}
};






enum FILE_MODE_
{
	FILE_MODE_MEMORY,
	FILE_MODE_ARCHIVE,
	FILE_MODE_LOCAL,
};

// FileMode::Memory
// FILE_MODE_MEMORY
// FileMode::Archive
// FileMode::Local


// FileModeLocal

// MotionDanteRebellionCombo1Part1

// MOTION_DANTE_REBELLION_COMBO_1_PART_1 3
// MOTION_DANTE_REBELLION_COMBO_1_PART_2 4
// MOTION_DANTE_REBELLION_COMBO_1_PART_3 5
// MOTION_DANTE_REBELLION_COMBO_2_PART_2 6


// using enum MotionDanteRebellion;
// Combo1Part1

// if (move == Combo1Part1)



enum Object_
{
	Object_Dante,
	Object_Lady,
	Object_Rebellion,
	Object_Rebellion2,
	Object_ForceEdgeDante,
	Object_Yamato,
	Object_ForceEdge,
	Object_NeroAngeloSword,
	Object_Count,
};








