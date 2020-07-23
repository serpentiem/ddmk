

// @Research: To module or not to module.




#pragma once
#include "../Core/DataTypes.h"

enum PLAYER
{
	MAX_PLAYER = 4,
};

enum ENTITY
{
	ENTITY_MAIN,
	ENTITY_CLONE,
	MAX_ENTITY,
};

enum WEAPON_STATUS
{
	WEAPON_STATUS_READY,
	WEAPON_STATUS_ACTIVE,
	WEAPON_STATUS_RETURN,
	WEAPON_STATUS_END,
	WEAPON_STATUS_DISABLED,
};

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
	CHAR_VOID = 255,
	MAX_CHAR = 4,
};

enum COSTUME_
{
	COSTUME_DANTE_DEFAULT,
	COSTUME_DANTE_DEFAULT_NO_COAT,
	COSTUME_DANTE_DEFAULT_TORN,
	COSTUME_DANTE_DMC1,
	COSTUME_DANTE_DMC1_NO_COAT,
	COSTUME_DANTE_SPARDA,
	COSTUME_DANTE_DEFAULT_TORN_INFINITE_MAGIC_POINTS,
	COSTUME_DANTE_SPARDA_INFINITE_MAGIC_POINTS,
	COSTUME_BOB_DEFAULT = 0,
	COSTUME_LADY_DEFAULT = 0,
	COSTUME_LADY_LEATHER_JUMPSUIT,
	COSTUME_VERGIL_DEFAULT = 0,
	COSTUME_VERGIL_DEFAULT_NO_COAT,
	COSTUME_VERGIL_DEFAULT_INFINITE_MAGIC_POINTS,
	COSTUME_VERGIL_SPARDA,
	COSTUME_VERGIL_SPARDA_INFINITE_MAGIC_POINTS,
	MAX_COSTUME = 8,
	MAX_COSTUME_DANTE = 8,
	MAX_COSTUME_BOB = 1,
	MAX_COSTUME_LADY = 2,
	MAX_COSTUME_VERGIL = 5,
};

enum DEVIL_
{
	DEVIL_DANTE_REBELLION,
	DEVIL_DANTE_CERBERUS,
	DEVIL_DANTE_AGNI_RUDRA,
	DEVIL_DANTE_NEVAN,
	DEVIL_DANTE_BEOWULF,
	DEVIL_DANTE_SPARDA,
	MAX_DEVIL_DANTE = 6,
	//DEVIL_VERGIL_YAMATO,
	//DEVIL_VERGIL_BEOWULF = 4,
	//DEVIL_VERGIL_NERO_ANGELO = 6,
	//MAX_DEVIL = 7,
};

enum STYLE_
{
	STYLE_DANTE_SWORDMASTER,
	STYLE_DANTE_GUNSLINGER,
	STYLE_DANTE_TRICKSTER,
	STYLE_DANTE_ROYALGUARD,
	STYLE_DANTE_QUICKSILVER,
	STYLE_DANTE_DOPPELGANGER,
	STYLE_VERGIL_DARK_SLAYER = 2,
	MAX_STYLE = 6,
};

enum WEAPON_
{
	WEAPON_DANTE_REBELLION,
	WEAPON_DANTE_CERBERUS,
	WEAPON_DANTE_AGNI_RUDRA,
	WEAPON_DANTE_NEVAN,
	WEAPON_DANTE_BEOWULF,
	WEAPON_DANTE_EBONY_IVORY,
	WEAPON_DANTE_SHOTGUN,
	WEAPON_DANTE_ARTEMIS,
	WEAPON_DANTE_SPIRAL,
	WEAPON_DANTE_KALINA_ANN,
	WEAPON_BOB_YAMATO = 14,
	WEAPON_LADY_KALINA_ANN = 9,
	WEAPON_LADY_UNKNOWN = 11,
	WEAPON_VERGIL_YAMATO = 11,
	WEAPON_VERGIL_BEOWULF,
	WEAPON_VERGIL_FORCE_EDGE,
	WEAPON_VOID = 255,
	MAX_WEAPON = 16,
	MAX_MELEE_WEAPON = 5,
	MAX_RANGED_WEAPON = 5,
	MAX_MELEE_WEAPON_DANTE = 5,
	MAX_RANGED_WEAPON_DANTE = 5,
	MAX_MELEE_WEAPON_VERGIL = 3,
};

enum WEAPON_TYPE_
{
	WEAPON_TYPE_MELEE,
	WEAPON_TYPE_RANGED,
};

enum MOTION_GROUP_
{
	MOTION_GROUP_DANTE_BASE,
	MOTION_GROUP_DANTE_DAMAGE,
	MOTION_GROUP_DANTE_TAUNTS,
	MOTION_GROUP_DANTE_REBELLION,
	MOTION_GROUP_DANTE_CERBERUS,
	MOTION_GROUP_DANTE_AGNI_RUDRA,
	MOTION_GROUP_DANTE_NEVAN,
	MOTION_GROUP_DANTE_BEOWULF,
	MOTION_GROUP_DANTE_EBONY_IVORY,
	MOTION_GROUP_DANTE_SHOTGUN,
	MOTION_GROUP_DANTE_ARTEMIS,
	MOTION_GROUP_DANTE_SPIRAL,
	MOTION_GROUP_DANTE_KALINA_ANN,
	MOTION_GROUP_DANTE_SWORDMASTER_REBELLION,
	MOTION_GROUP_DANTE_SWORDMASTER_CERBERUS,
	MOTION_GROUP_DANTE_SWORDMASTER_AGNI_RUDRA,
	MOTION_GROUP_DANTE_SWORDMASTER_NEVAN,
	MOTION_GROUP_DANTE_SWORDMASTER_BEOWULF,
	MOTION_GROUP_DANTE_GUNSLINGER_EBONY_IVORY,
	MOTION_GROUP_DANTE_GUNSLINGER_SHOTGUN,
	MOTION_GROUP_DANTE_GUNSLINGER_ARTEMIS,
	MOTION_GROUP_DANTE_GUNSLINGER_SPIRAL,
	MOTION_GROUP_DANTE_GUNSLINGER_KALINA_ANN,
	MOTION_GROUP_DANTE_TRICKSTER,
	MOTION_GROUP_DANTE_ROYALGUARD,
	MOTION_GROUP_DANTE_QUICKSILVER,
	MOTION_GROUP_DANTE_DOPPELGANGER,
	MOTION_GROUP_BOB_BASE = 0,
	MOTION_GROUP_BOB_DAMAGE,
	MOTION_GROUP_BOB_TAUNTS,
	MOTION_GROUP_BOB_MELEE_STYLE = 31,
	MOTION_GROUP_LADY_BASE = 0,
	MOTION_GROUP_LADY_DAMAGE,
	MOTION_GROUP_LADY_TAUNTS,
	MOTION_GROUP_LADY_KALINA_ANN = 12,
	MOTION_GROUP_VERGIL_BASE = 0,
	MOTION_GROUP_VERGIL_DAMAGE,
	MOTION_GROUP_VERGIL_TAUNTS,
	MOTION_GROUP_VERGIL_YAMATO,
	MOTION_GROUP_VERGIL_BEOWULF,
	MOTION_GROUP_VERGIL_FORCE_EDGE,
	MOTION_GROUP_VERGIL_DARK_SLAYER,
	MOTION_GROUP_VERGIL_NERO_ANGELO_YAMATO,
	MOTION_GROUP_VERGIL_NERO_ANGELO_BEOWULF,
	MOTION_GROUP_VERGIL_NERO_ANGELO_FORCE_EDGE,
	MAX_MOTION_GROUP = 32,
};

// @Todo: Check Vergil.

enum NEXT_ACTION_REQUEST_POLICY
{
	NEXT_ACTION_REQUEST_POLICY_IGNORE,
	NEXT_ACTION_REQUEST_POLICY_BUFFER,
	NEXT_ACTION_REQUEST_POLICY_EXECUTE,
	// Indices
	NEXT_ACTION_REQUEST_POLICY_MELEE_ATTACK = 0,
	NEXT_ACTION_REQUEST_POLICY_SWORDMASTER_GUNSLINGER = 4,
	NEXT_ACTION_REQUEST_POLICY_JUMP_ROLL = 5,
	NEXT_ACTION_REQUEST_POLICY_ROYALGUARD = 6,
	NEXT_ACTION_REQUEST_POLICY_TRICKSTER_DARK_SLAYER = 8,
	NEXT_ACTION_REQUEST_POLICY_RANGED_ATTACK = 10,
	NEXT_ACTION_REQUEST_POLICY_END = 15,
};

enum ACTION
{
	ACTION_DANTE_REBELLION_COMBO_1_PART_1 = 1,
	ACTION_DANTE_REBELLION_COMBO_1_PART_2,
	ACTION_DANTE_REBELLION_COMBO_1_PART_3,
	ACTION_DANTE_REBELLION_COMBO_2_PART_2,
	ACTION_DANTE_REBELLION_COMBO_2_PART_3,
	ACTION_DANTE_REBELLION_HELM_BREAKER,
	ACTION_DANTE_REBELLION_STINGER_LEVEL_1,
	ACTION_DANTE_REBELLION_STINGER_LEVEL_2,
	ACTION_DANTE_REBELLION_LEAP,
	ACTION_DANTE_REBELLION_HIGH_TIME,
	ACTION_DANTE_REBELLION_HIGH_TIME_LAUNCH,
	ACTION_DANTE_REBELLION_KICK_1,
	ACTION_DANTE_REBELLION_DRIVE_1,
	ACTION_DANTE_REBELLION_MILLION_STAB,
	ACTION_DANTE_REBELLION_SWORD_PIERCE,
	ACTION_DANTE_REBELLION_PROP_SHREDDER_1,
	ACTION_DANTE_REBELLION_DIVEKICK,
	ACTION_DANTE_REBELLION_KICK_2,
	ACTION_DANTE_REBELLION_AERIAL_RAVE_PART_1,
	ACTION_DANTE_REBELLION_AERIAL_RAVE_PART_2,
	ACTION_DANTE_REBELLION_AERIAL_RAVE_PART_3,
	ACTION_DANTE_REBELLION_AERIAL_RAVE_PART_4,
	ACTION_DANTE_REBELLION_SWORD_PIERCE_RETURN,
	ACTION_DANTE_REBELLION_PROP_SHREDDER_2,
	ACTION_DANTE_REBELLION_DRIVE_2,
	ACTION_DANTE_CERBERUS_COMBO_1_PART_1 = 30,
	ACTION_DANTE_CERBERUS_COMBO_1_PART_2,
	ACTION_DANTE_CERBERUS_COMBO_1_PART_3,
	ACTION_DANTE_CERBERUS_COMBO_1_PART_4,
	ACTION_DANTE_CERBERUS_COMBO_1_PART_5,
	ACTION_DANTE_CERBERUS_COMBO_2_PART_3,
	ACTION_DANTE_CERBERUS_COMBO_2_PART_4,
	ACTION_DANTE_CERBERUS_WINDMILL,
	ACTION_DANTE_CERBERUS_REVOLVER_LEVEL_1,
	ACTION_DANTE_CERBERUS_REVOLVER_LEVEL_2,
	ACTION_DANTE_CERBERUS_SWING,
	ACTION_DANTE_CERBERUS_SATELLITE,
	ACTION_DANTE_CERBERUS_FLICKER,
	ACTION_DANTE_CERBERUS_AIR_FLICKER,
	ACTION_DANTE_CERBERUS_CRYSTAL,
	ACTION_DANTE_CERBERUS_MILLION_CARATS,
	ACTION_DANTE_CERBERUS_ICE_AGE,
	ACTION_DANTE_AGNI_RUDRA_COMBO_1_PART_1 = 50,
	ACTION_DANTE_AGNI_RUDRA_COMBO_1_PART_2,
	ACTION_DANTE_AGNI_RUDRA_COMBO_1_PART_3,
	ACTION_DANTE_AGNI_RUDRA_COMBO_1_PART_4,
	ACTION_DANTE_AGNI_RUDRA_COMBO_1_PART_5,
	ACTION_DANTE_AGNI_RUDRA_COMBO_2_PART_2,
	ACTION_DANTE_AGNI_RUDRA_COMBO_2_PART_3,
	ACTION_DANTE_AGNI_RUDRA_COMBO_3_PART_3,
	ACTION_DANTE_AGNI_RUDRA_JET_STREAM_LEVEL_1,
	ACTION_DANTE_AGNI_RUDRA_JET_STREAM_LEVEL_2,
	ACTION_DANTE_AGNI_RUDRA_JET_STREAM_LEVEL_3,
	ACTION_DANTE_AGNI_RUDRA_AERIAL_CROSS,
	ACTION_DANTE_AGNI_RUDRA_WHIRLWIND,
	ACTION_DANTE_AGNI_RUDRA_WHIRLWIND_LAUNCH,
	ACTION_DANTE_AGNI_RUDRA_MILLION_SLASH,
	ACTION_DANTE_AGNI_RUDRA_CROSSED_SWORDS,
	ACTION_DANTE_AGNI_RUDRA_CRAWLER,
	ACTION_DANTE_AGNI_RUDRA_TWISTER,
	ACTION_DANTE_AGNI_RUDRA_SKY_DANCE_PART_1,
	ACTION_DANTE_AGNI_RUDRA_SKY_DANCE_PART_2,
	ACTION_DANTE_AGNI_RUDRA_SKY_DANCE_PART_3,
	ACTION_DANTE_AGNI_RUDRA_TEMPEST,
	ACTION_DANTE_NEVAN_TUNE_UP = 80,
	ACTION_DANTE_NEVAN_COMBO_1,
	ACTION_DANTE_NEVAN_COMBO_2,
	ACTION_DANTE_NEVAN_JAM_SESSION,
	ACTION_DANTE_NEVAN_BAT_RIFT_LEVEL_1,
	ACTION_DANTE_NEVAN_BAT_RIFT_LEVEL_2,
	ACTION_DANTE_NEVAN_REVERB_SHOCK_LEVEL_1,
	ACTION_DANTE_NEVAN_REVERB_SHOCK_LEVEL_2,
	ACTION_DANTE_NEVAN_AIR_PLAY,
	ACTION_DANTE_NEVAN_SLASH,
	ACTION_DANTE_NEVAN_AIR_SLASH_PART_1,
	ACTION_DANTE_NEVAN_AIR_SLASH_PART_2,
	ACTION_DANTE_NEVAN_FEEDBACK,
	ACTION_DANTE_NEVAN_CRAZY_ROLL,
	ACTION_DANTE_NEVAN_DISTORTION,
	ACTION_DANTE_NEVAN_VORTEX,
	ACTION_DANTE_NEVAN_THUNDER_BOLT,
	ACTION_DANTE_BEOWULF_COMBO_1_PART_1 = 110,
	ACTION_DANTE_BEOWULF_COMBO_1_PART_2,
	ACTION_DANTE_BEOWULF_COMBO_1_PART_3,
	ACTION_DANTE_BEOWULF_COMBO_2_PART_3,
	ACTION_DANTE_BEOWULF_COMBO_2_PART_4,
	ACTION_DANTE_BEOWULF_HYPER_FIST,
	ACTION_DANTE_BEOWULF_KILLER_BEE,
	ACTION_DANTE_BEOWULF_BEAST_UPPERCUT,
	ACTION_DANTE_BEOWULF_RISING_DRAGON,
	ACTION_DANTE_BEOWULF_RISING_DRAGON_LAUNCH,
	ACTION_DANTE_BEOWULF_RISING_DRAGON_WHIRLWIND,
	ACTION_DANTE_BEOWULF_STRAIGHT_LEVEL_1,
	ACTION_DANTE_BEOWULF_STRAIGHT_LEVEL_2,
	ACTION_DANTE_BEOWULF_ZODIAC,
	ACTION_DANTE_BEOWULF_VOLCANO,
	ACTION_DANTE_BEOWULF_AIR_VOLCANO,
	ACTION_DANTE_BEOWULF_TORNADO,
	ACTION_DANTE_BEOWULF_THE_HAMMER,
	ACTION_DANTE_BEOWULF_REAL_IMPACT,
	ACTION_DANTE_EBONY_IVORY_NORMAL_SHOT = 130,
	ACTION_DANTE_EBONY_IVORY_CHARGED_SHOT,
	ACTION_DANTE_EBONY_IVORY_AIR_NORMAL_SHOT,
	ACTION_DANTE_EBONY_IVORY_AIR_CHARGED_SHOT,
	ACTION_DANTE_EBONY_IVORY_TWOSOME_TIME,
	ACTION_DANTE_EBONY_IVORY_RAIN_STORM,
	ACTION_DANTE_EBONY_IVORY_WILD_STOMP,
	ACTION_DANTE_SHOTGUN_NORMAL_SHOT = 140,
	ACTION_DANTE_SHOTGUN_CHARGED_SHOT,
	ACTION_DANTE_SHOTGUN_AIR_NORMAL_SHOT,
	ACTION_DANTE_SHOTGUN_AIR_CHARGED_SHOT,
	ACTION_DANTE_SHOTGUN_FIREWORKS,
	ACTION_DANTE_SHOTGUN_AIR_FIREWORKS,
	ACTION_DANTE_SHOTGUN_GUN_STINGER,
	ACTION_DANTE_SHOTGUN_POINT_BLANK,
	ACTION_DANTE_ARTEMIS_NORMAL_SHOT = 150,
	ACTION_DANTE_ARTEMIS_AIR_NORMAL_SHOT,
	ACTION_DANTE_ARTEMIS_MULTI_LOCK_SHOT,
	ACTION_DANTE_ARTEMIS_AIR_MULTI_LOCK_SHOT,
	ACTION_DANTE_ARTEMIS_SPHERE,
	ACTION_DANTE_ARTEMIS_ACID_RAIN,
	ACTION_DANTE_SPIRAL_NORMAL_SHOT = 160,
	ACTION_DANTE_SPIRAL_SNIPER,
	ACTION_DANTE_SPIRAL_TRICK_SHOT,
	ACTION_DANTE_KALINA_ANN_NORMAL_SHOT = 170,
	ACTION_DANTE_KALINA_ANN_HYSTERIC,
	ACTION_DANTE_KALINA_ANN_GRAPPLE,
	ACTION_DANTE_TRICKSTER_DASH = 180,
	ACTION_DANTE_TRICKSTER_SKY_STAR,
	ACTION_DANTE_TRICKSTER_AIR_TRICK,
	ACTION_DANTE_TRICKSTER_WALL_HIKE,
	ACTION_DANTE_ROYALGUARD_RELEASE_1 = 190,
	ACTION_DANTE_ROYALGUARD_RELEASE_2,
	ACTION_DANTE_ROYALGUARD_RELEASE_3,
	ACTION_DANTE_ROYALGUARD_RELEASE_4,
	ACTION_DANTE_ROYALGUARD_AIR_RELEASE_1,
	ACTION_DANTE_ROYALGUARD_AIR_RELEASE_2,
	ACTION_DANTE_ROYALGUARD_AIR_RELEASE_3,
	ACTION_DANTE_ROYALGUARD_AIR_RELEASE_4,
	ACTION_DANTE_REBELLION_DANCE_MACABRE_PART_1 = 200,
	ACTION_DANTE_REBELLION_DANCE_MACABRE_PART_2,
	ACTION_DANTE_REBELLION_DANCE_MACABRE_PART_3,
	ACTION_DANTE_REBELLION_DANCE_MACABRE_PART_4,
	ACTION_DANTE_REBELLION_DANCE_MACABRE_PART_5,
	ACTION_DANTE_REBELLION_DANCE_MACABRE_PART_6,
	ACTION_DANTE_REBELLION_DANCE_MACABRE_PART_7,
	ACTION_DANTE_REBELLION_DANCE_MACABRE_PART_8,
	ACTION_DANTE_REBELLION_CRAZY_DANCE,
	ACTION_DANTE_POLE_PLAY,
	ACTION_VERGIL_YAMATO_COMBO_PART_1 = 1,
	ACTION_VERGIL_YAMATO_COMBO_PART_2,
	ACTION_VERGIL_YAMATO_COMBO_PART_3,
	ACTION_VERGIL_YAMATO_RAPID_SLASH_LEVEL_1,
	ACTION_VERGIL_YAMATO_RAPID_SLASH_LEVEL_2,
	ACTION_VERGIL_YAMATO_LEAP,
	ACTION_VERGIL_YAMATO_UPPER_SLASH_PART_1,
	ACTION_VERGIL_YAMATO_UPPER_SLASH_PART_2,
	ACTION_VERGIL_YAMATO_JUDGEMENT_CUT_LEVEL_1,
	ACTION_VERGIL_YAMATO_JUDGEMENT_CUT_LEVEL_2,
	ACTION_VERGIL_YAMATO_AERIAL_RAVE_PART_1,
	ACTION_VERGIL_YAMATO_AERIAL_RAVE_PART_2,
	ACTION_VERGIL_BEOWULF_COMBO_PART_1 = 20,
	ACTION_VERGIL_BEOWULF_COMBO_PART_2,
	ACTION_VERGIL_BEOWULF_COMBO_PART_3,
	ACTION_VERGIL_BEOWULF_STARFALL_LEVEL_1,
	ACTION_VERGIL_BEOWULF_STARFALL_LEVEL_2,
	ACTION_VERGIL_BEOWULF_RISING_SUN,
	ACTION_VERGIL_BEOWULF_LUNAR_PHASE_LEVEL_1,
	ACTION_VERGIL_BEOWULF_LUNAR_PHASE_LEVEL_2,
	ACTION_VERGIL_FORCE_EDGE_COMBO_PART_1 = 30,
	ACTION_VERGIL_FORCE_EDGE_COMBO_PART_2,
	ACTION_VERGIL_FORCE_EDGE_COMBO_PART_3,
	ACTION_VERGIL_FORCE_EDGE_COMBO_PART_4,
	ACTION_VERGIL_FORCE_EDGE_HELM_BREAKER_LEVEL_1,
	ACTION_VERGIL_FORCE_EDGE_HELM_BREAKER_LEVEL_2,
	ACTION_VERGIL_FORCE_EDGE_HIGH_TIME,
	ACTION_VERGIL_FORCE_EDGE_HIGH_TIME_LAUNCH,
	ACTION_VERGIL_FORCE_EDGE_STINGER_LEVEL_1,
	ACTION_VERGIL_FORCE_EDGE_STINGER_LEVEL_2,
	ACTION_VERGIL_FORCE_EDGE_ROUND_TRIP,
	ACTION_VERGIL_FORCE_EDGE_KICK,
	ACTION_VERGIL_SUMMONED_SWORDS_SHOOT = 52,
	ACTION_VERGIL_SUMMONED_SWORDS_SPIRAL_SWORDS,
	ACTION_VERGIL_SUMMONED_SWORDS_BLISTERING_SWORDS,
	ACTION_VERGIL_SUMMONED_SWORDS_SWORD_STORM,
	ACTION_VERGIL_DARK_SLAYER_AIR_TRICK = 60,
	ACTION_VERGIL_DARK_SLAYER_TRICK_UP,
	ACTION_VERGIL_DARK_SLAYER_TRICK_DOWN,
	ACTION_VERGIL_NERO_ANGELO_COMBO_1_PART_1 = 70,
	ACTION_VERGIL_NERO_ANGELO_COMBO_1_PART_2,
	ACTION_VERGIL_NERO_ANGELO_COMBO_1_PART_3,
	ACTION_VERGIL_NERO_ANGELO_HELM_BREAKER,
	ACTION_VERGIL_NERO_ANGELO_HIGH_TIME,
	ACTION_VERGIL_NERO_ANGELO_HIGH_TIME_LAUNCH,
	ACTION_VERGIL_NERO_ANGELO_STINGER,
	ACTION_VERGIL_NERO_ANGELO_FIREBALL_1,
	ACTION_VERGIL_NERO_ANGELO_COMBO_2_PART_1 = 90,
	ACTION_VERGIL_NERO_ANGELO_COMBO_2_PART_2,
	ACTION_VERGIL_NERO_ANGELO_COMBO_2_PART_3,
	ACTION_VERGIL_NERO_ANGELO_DIVEKICK,
	ACTION_VERGIL_NERO_ANGELO_ROUNDHOUSE_KICK,
	ACTION_VERGIL_NERO_ANGELO_UPPERCUT,
	ACTION_VERGIL_NERO_ANGELO_FIREBALL_2,
};

enum PERMISSION
{
	PERMISSION_UPDATE = 1,
	PERMISSION_WALK_RUN = 2,
	PERMISSION_JUMP_ROLL = 8,
	PERMISSION_TARGET = 0x10,
	PERMISSION_RELEASE = 0x20,
	PERMISSION_INTERACTION_STYLE_ATTACK = 0x400,
};

enum STATE
{
	STATE_ON_FLOOR = 1,
	STATE_IN_AIR = 2,
	STATE_BUSY = 0x10000,
};

//enum BODY_PART_
//{
//	BODY_PART_LOWER,
//	BODY_PART_UPPER,
//};

//enum MODEL_PART_
//{
//	MODEL_PART_BASE,
//	MODEL_PART_AMULET,
//	MODEL_PART_COAT,
//	MAX_MODEL_PART,
//};
//
//enum DEVIL_MODEL_PART_
//{
//	DEVIL_MODEL_PART_BASE,
//	DEVIL_MODEL_PART_WINGS,
//	DEVIL_MODEL_PART_COAT,
//	MAX_DEVIL_MODEL_PART,
//};




enum BODY_PART
{
	LOWER_BODY,
	UPPER_BODY,
	MAX_BODY_PART,
};













// $CacheFileStart

enum CACHE_FILE
{
	pl000,
	pl011,
	pl013,
	pl015,
	pl016,
	pl018,
	pl005,
	pl006,
	pl007,
	pl008,
	pl009,
	pl017,
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
	plwp_sword,
	plwp_sword2,
	plwp_sword3,
	plwp_nunchaku,
	plwp_2sword,
	plwp_guitar,
	plwp_fight,
	plwp_gun,
	plwp_shotgun,
	plwp_laser,
	plwp_rifle,
	plwp_ladygun,
	pl001,
	pl001_00_0,
	pl001_00_1,
	pl001_00_2,
	pl001_00_31,
	plwp_vergilsword,
	pl002,
	pl002_00_0,
	pl002_00_1,
	pl002_00_2,
	pl021,
	pl023,
	pl026,
	pl010,
	pl014,
	pl025,
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
	plwp_newvergilsword,
	plwp_newvergilfight,
	plwp_forceedge,
	plwp_nerosword,
	em034,
	id100,
	id100V,
	MAX_CACHE_FILE,
};

struct CacheFileHelper
{
	const char * name;
	const char * type;
};

constexpr CacheFileHelper cacheFileHelper[MAX_CACHE_FILE] =
{
	{ "pl000.pac", "obj\\pl000.pac" },
	{ "pl011.pac", "obj\\pl011.pac" },
	{ "pl013.pac", "obj\\pl013.pac" },
	{ "pl015.pac", "obj\\pl015.pac" },
	{ "pl016.pac", "obj\\pl016.pac" },
	{ "pl018.pac", "obj\\pl018.pac" },
	{ "pl005.pac", "obj\\pl005.pac" },
	{ "pl006.pac", "obj\\pl006.pac" },
	{ "pl007.pac", "obj\\pl007.pac" },
	{ "pl008.pac", "obj\\pl008.pac" },
	{ "pl009.pac", "obj\\pl009.pac" },
	{ "pl017.pac", "obj\\pl017.pac" },
	{ "pl000_00_0.pac", "motion\\pl000\\pl000_00_0.pac" },
	{ "pl000_00_1.pac", "motion\\pl000\\pl000_00_1.pac" },
	{ "pl000_00_2.pac", "motion\\pl000\\pl000_00_2.pac" },
	{ "pl000_00_3.pac", "motion\\pl000\\pl000_00_3.pac" },
	{ "pl000_00_4.pac", "motion\\pl000\\pl000_00_4.pac" },
	{ "pl000_00_5.pac", "motion\\pl000\\pl000_00_5.pac" },
	{ "pl000_00_6.pac", "motion\\pl000\\pl000_00_6.pac" },
	{ "pl000_00_7.pac", "motion\\pl000\\pl000_00_7.pac" },
	{ "pl000_00_8.pac", "motion\\pl000\\pl000_00_8.pac" },
	{ "pl000_00_9.pac", "motion\\pl000\\pl000_00_9.pac" },
	{ "pl000_00_10.pac", "motion\\pl000\\pl000_00_10.pac" },
	{ "pl000_00_11.pac", "motion\\pl000\\pl000_00_11.pac" },
	{ "pl000_00_12.pac", "motion\\pl000\\pl000_00_12.pac" },
	{ "pl000_00_13.pac", "motion\\pl000\\pl000_00_13.pac" },
	{ "pl000_00_14.pac", "motion\\pl000\\pl000_00_14.pac" },
	{ "pl000_00_15.pac", "motion\\pl000\\pl000_00_15.pac" },
	{ "pl000_00_16.pac", "motion\\pl000\\pl000_00_16.pac" },
	{ "pl000_00_17.pac", "motion\\pl000\\pl000_00_17.pac" },
	{ "pl000_00_18.pac", "motion\\pl000\\pl000_00_18.pac" },
	{ "pl000_00_19.pac", "motion\\pl000\\pl000_00_19.pac" },
	{ "pl000_00_20.pac", "motion\\pl000\\pl000_00_20.pac" },
	{ "pl000_00_21.pac", "motion\\pl000\\pl000_00_21.pac" },
	{ "pl000_00_22.pac", "motion\\pl000\\pl000_00_22.pac" },
	{ "pl000_00_23.pac", "motion\\pl000\\pl000_00_23.pac" },
	{ "pl000_00_24.pac", "motion\\pl000\\pl000_00_24.pac" },
	{ "pl000_00_25.pac", "motion\\pl000\\pl000_00_25.pac" },
	{ "pl000_00_26.pac", "motion\\pl000\\pl000_00_26.pac" },
	{ "plwp_sword.pac", "obj\\plwp_sword.pac" },
	{ "plwp_sword2.pac", "obj\\plwp_sword2.pac" },
	{ "plwp_sword3.pac", "obj\\plwp_sword3.pac" },
	{ "plwp_nunchaku.pac", "obj\\plwp_nunchaku.pac" },
	{ "plwp_2sword.pac", "obj\\plwp_2sword.pac" },
	{ "plwp_guitar.pac", "obj\\plwp_guitar.pac" },
	{ "plwp_fight.pac", "obj\\plwp_fight.pac" },
	{ "plwp_gun.pac", "obj\\plwp_gun.pac" },
	{ "plwp_shotgun.pac", "obj\\plwp_shotgun.pac" },
	{ "plwp_laser.pac", "obj\\plwp_laser.pac" },
	{ "plwp_rifle.pac", "obj\\plwp_rifle.pac" },
	{ "plwp_ladygun.pac", "obj\\plwp_ladygun.pac" },
	{ "pl001.pac", "obj\\pl001.pac" },
	{ "pl001_00_0.pac", "motion\\pl001\\pl001_00_0.pac" },
	{ "pl001_00_1.pac", "motion\\pl001\\pl001_00_1.pac" },
	{ "pl001_00_2.pac", "motion\\pl001\\pl001_00_2.pac" },
	{ "pl001_00_31.pac", "motion\\pl001\\pl001_00_31.pac" },
	{ "plwp_vergilsword.pac", "obj\\plwp_vergilsword.pac" },
	{ "pl002.pac", "obj\\pl002.pac" },
	{ "pl002_00_0.pac", "motion\\pl002\\pl002_00_0.pac" },
	{ "pl002_00_1.pac", "motion\\pl002\\pl002_00_1.pac" },
	{ "pl002_00_2.pac", "motion\\pl002\\pl002_00_2.pac" },
	{ "pl021.pac", "obj\\pl021.pac" },
	{ "pl023.pac", "obj\\pl023.pac" },
	{ "pl026.pac", "obj\\pl026.pac" },
	{ "pl010.pac", "obj\\pl010.pac" },
	{ "pl014.pac", "obj\\pl014.pac" },
	{ "pl025.pac", "obj\\pl025.pac" },
	{ "pl021_00_0.pac", "motion\\pl021\\pl021_00_0.pac" },
	{ "pl021_00_1.pac", "motion\\pl021\\pl021_00_1.pac" },
	{ "pl021_00_2.pac", "motion\\pl021\\pl021_00_2.pac" },
	{ "pl021_00_3.pac", "motion\\pl021\\pl021_00_3.pac" },
	{ "pl021_00_4.pac", "motion\\pl021\\pl021_00_4.pac" },
	{ "pl021_00_5.pac", "motion\\pl021\\pl021_00_5.pac" },
	{ "pl021_00_6.pac", "motion\\pl021\\pl021_00_6.pac" },
	{ "pl021_00_7.pac", "motion\\pl021\\pl021_00_7.pac" },
	{ "pl021_00_8.pac", "motion\\pl021\\pl021_00_8.pac" },
	{ "pl021_00_9.pac", "motion\\pl021\\pl021_00_9.pac" },
	{ "plwp_newvergilsword.pac", "obj\\plwp_newvergilsword.pac" },
	{ "plwp_newvergilfight.pac", "obj\\plwp_newvergilfight.pac" },
	{ "plwp_forceedge.pac", "obj\\plwp_forceedge.pac" },
	{ "plwp_nerosword.pac", "obj\\plwp_nerosword.pac" },
	{ "em034.pac", "obj\\em034.pac" },
	{ "id100.pac", "id\\id100\\id100.pac" },
	{ "id100V.pac", "id\\id100\\id100V.pac" },
};

// $CacheFileEnd









enum SCENE
{
	SCENE_MAIN      = 1,
	SCENE_TELEPORT  = 2,
	SCENE_PAUSE     = 3,
	SCENE_STATUS    = 4,
	SCENE_OPTIONS   = 5,
	SCENE_CONTINUE  = 6,
	SCENE_CUSTOMIZE = 9,
	SCENE_SAVE      = 10,
	SCENE_SUB       = 11,
};

enum SUBSCENE
{
	SUBSCENE_MISSION_CLEAR  = 5,
	SUBSCENE_GAME_OVER      = 6,
	SUBSCENE_MISSION_START  = 7,
	SUBSCENE_MISSION_SELECT = 8,
};

enum GAMEPAD
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
	MAX_GAMEPAD = 4,
};

enum LEFT_STICK
{
	LEFT_STICK_DEADZONE = 52,
};

enum BINDING
{
	BINDING_ITEM_SCREEN,
	BINDING_EQUIP_SCREEN,
	BINDING_MAP_SCREEN,
	BINDING_FILE_SCREEN,
	BINDING_MELEE_ATTACK,
	BINDING_JUMP,
	BINDING_STYLE_ACTION,
	BINDING_SHOOT,
	BINDING_DEVIL_TRIGGER,
	BINDING_CHANGE_GUN,
	BINDING_CHANGE_TARGET,
	BINDING_LOCK_ON,
	BINDING_CHANGE_DEVIL_ARMS,
	BINDING_DEFAULT_CAMERA,
	BINDING_TAUNT,
};

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

enum FILE_ITEM_STATUS_
{
	FILE_ITEM_READY = 3,
};

enum FILE_MODE_
{
	FILE_MODE_MEMORY,
	FILE_MODE_ARCHIVE,
	FILE_MODE_LOCAL,
};

enum ACTOR_EVENT
{
	ACTOR_EVENT_DANTE_DASH = 22,
	ACTOR_EVENT_DANTE_SKY_STAR,
	ACTOR_EVENT_DANTE_AIR_TRICK,
	ACTOR_EVENT_VERGIL_AIR_TRICK = 27,
	ACTOR_EVENT_VERGIL_TRICK_UP,
	ACTOR_EVENT_VERGIL_TRICK_DOWN,
};

enum ACTOR_MODE
{
	ACTOR_MODE_DEFAULT,
	ACTOR_MODE_MISSION_12,
	ACTOR_MODE_MISSION_18,
	ACTOR_MODE_MISSION_19,
};










#define IntroduceSizeStruct(size)\
struct Size_##size\
{\
	byte8 data[size];\
	operator byte8 *()\
	{\
		return reinterpret_cast<byte8 *>(this);\
	}\
}

#define _(size) struct { byte8 Prep_Merge(padding_, __LINE__)[size]; }

#pragma pack(push, 1)








struct ACTOR_EVENT_DATA
{
	uint32 index;
	uint32 lastIndex;
};



// $SessionDataStart

struct SESSION_DATA
{
	uint32 mission; // 0
	_(8);
	uint32 mode; // 0xC
	bool oneHitKill; // 0x10
	_(1);
	bool enableTutorial; // 0x12
	bool useGoldOrb; // 0x13
	_(8);
	bool bloodyPalace; // 0x1C
	_(24);
	uint8 goldOrbCount; // 0x35
	_(16);
	bool unlock[14]; // 0x46
	_(48);
	uint8 weapons[4]; // 0x84
	_(72);
	uint8 costume; // 0xD0
	bool unlockDevilTrigger; // 0xD1
	_(2);
	float32 hitPoints; // 0xD4
	float32 magicPoints; // 0xD8
	uint32 style; // 0xDC
	uint32 styleLevel[6]; // 0xE0
	float32 styleExperience[6]; // 0xF8
	byte32 expertise[8]; // 0x110
};

static_assert(offsetof(SESSION_DATA, mission) == 0);
static_assert(offsetof(SESSION_DATA, mode) == 0xC);
static_assert(offsetof(SESSION_DATA, oneHitKill) == 0x10);
static_assert(offsetof(SESSION_DATA, enableTutorial) == 0x12);
static_assert(offsetof(SESSION_DATA, useGoldOrb) == 0x13);
static_assert(offsetof(SESSION_DATA, bloodyPalace) == 0x1C);
static_assert(offsetof(SESSION_DATA, goldOrbCount) == 0x35);
static_assert(offsetof(SESSION_DATA, unlock) == 0x46);
static_assert(offsetof(SESSION_DATA, weapons) == 0x84);
static_assert(offsetof(SESSION_DATA, costume) == 0xD0);
static_assert(offsetof(SESSION_DATA, unlockDevilTrigger) == 0xD1);
static_assert(offsetof(SESSION_DATA, hitPoints) == 0xD4);
static_assert(offsetof(SESSION_DATA, magicPoints) == 0xD8);
static_assert(offsetof(SESSION_DATA, style) == 0xDC);
static_assert(offsetof(SESSION_DATA, styleLevel) == 0xE0);
static_assert(offsetof(SESSION_DATA, styleExperience) == 0xF8);
static_assert(offsetof(SESSION_DATA, expertise) == 0x110);

// $SessionDataEnd

struct SCENE_DATA
{
	_(24);
	uint32 room;
	uint32 position;
	uint32 scene;
	_(8);
	uint32 subscene;
};

struct NEXT_SCENE_DATA
{
	_(356);
	uint16 room;
	uint16 position;
};

struct STAGE_POSITION_DATA
{
	uint8 event;
	_(3);
	float32 x;
	float32 y;
	float32 z;
	float32 rotation;
	_(28);
};








#define _IntroduceHUDPointers(name, ...)\
auto name = GetMasterPointer();\
if (!name)\
{\
	__VA_ARGS__;\
}\
auto hudTop    = *reinterpret_cast<byte8 **>(name + 0x1B070);\
auto hudBottom = *reinterpret_cast<byte8 **>(name + 0x1B078)
#define IntroduceHUDPointers(...) _IntroduceHUDPointers(Prep_Merge(dest_, __LINE__), __VA_ARGS__)








#define _IntroduceMissionActorDataPointers(name, ...)\
auto name = *reinterpret_cast<byte8 **>(appBaseAddr + 0xC90E30);\
if (!name)\
{\
	__VA_ARGS__;\
}\
auto missionActorData_C0  = reinterpret_cast<byte8 *>(name + 0xC0 );\
auto missionActorData_16C = reinterpret_cast<byte8 *>(name + 0x16C)
#define IntroduceMissionActorDataPointers(...) _IntroduceMissionActorDataPointers(Prep_Merge(pool_, __LINE__), __VA_ARGS__)














#define IntroduceSessionData() auto & sessionData = *reinterpret_cast<SESSION_DATA *>(appBaseAddr + 0xC8F250)

#define _IntroduceSceneData(name, ...)\
auto name = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E10);\
if (!name)\
{\
	__VA_ARGS__;\
}\
if (!name[8])\
{\
	__VA_ARGS__;\
}\
auto & sceneData = *reinterpret_cast<SCENE_DATA *>(name[8])
#define IntroduceSceneData(...) _IntroduceSceneData(Prep_Merge(pool_, __LINE__), __VA_ARGS__)

#define _IntroduceNextSceneData(name, ...)\
auto name = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E10);\
if (!name)\
{\
	__VA_ARGS__;\
}\
if (!name[12])\
{\
	__VA_ARGS__;\
}\
auto & nextSceneData = *reinterpret_cast<NEXT_SCENE_DATA *>(name[12])
#define IntroduceNextSceneData(...) _IntroduceNextSceneData(Prep_Merge(pool_, __LINE__), __VA_ARGS__)

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

#define _IntroduceStagePositionData(name, ...)\
auto name = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E10);\
if (!name)\
{\
	__VA_ARGS__;\
}\
if (!name[8])\
{\
	__VA_ARGS__;\
}\
auto stagePositionData = *reinterpret_cast<STAGE_POSITION_DATA **>(name[8] + 0x2CB0);\
if (!stagePositionData)\
{\
	__VA_ARGS__;\
}
#define IntroduceStagePositionData(...) _IntroduceStagePositionData(Prep_Merge(pool_, __LINE__), __VA_ARGS__)













































struct CAMERA_DATA
{
	_(176);
	byte8 * targetBaseAddr;
	_(24);
	float32 height;
	float32 tilt;
	float32 zoom;
};

static_assert(offsetof(CAMERA_DATA, targetBaseAddr) == 0xB0);
static_assert(offsetof(CAMERA_DATA, height) == 0xD0);
static_assert(offsetof(CAMERA_DATA, tilt) == 0xD4);
static_assert(offsetof(CAMERA_DATA, zoom) == 0xD8);
















struct ARCHIVE_DATA
{
	byte8 signature[4];
	uint32 fileCount;
	uint32 fileOff[128];
};





struct STRING_ITEM
{
	_(8);
	const char * string;
};

struct FILE_ITEM
{
	uint32        category;
	uint32        status;
	uint16        id;
	_(6);
	void        * callback;
	STRING_ITEM * stringItem;
	byte8       * file;
	_(32);
};

























struct PS2_GAMEPAD
{
	_(16);
	uint8  vibration[4];
	byte16 buttons[6];
	uint8  rightStickX;
	uint8  rightStickY;
	uint8  leftStickX;
	uint8  leftStickY;
	_(12);
	uint16 rightStickDirection[4];
	uint16 leftStickDirection[4];
	uint16 rightStickDirectionFast[2];
	uint16 leftStickDirectionFast[2];
	uint16 rightStickPosition;
	uint16 leftStickPosition;
	uint16 rightStickDifference;
	uint16 leftStickDifference;
};

struct ENGINE_GAMEPAD
{
	byte16 buttons[4];
	uint16 buttonsTimer[2];
	uint16 rightStickDirection[4];
	uint16 rightStickTimer[2];
	uint16 rightStickPosition;
	uint16 rightStickRadius;
	uint16 leftStickDirection[4];
	uint16 leftStickTimer[2];
	uint16 leftStickPosition;
	uint16 leftStickRadius;
};
















struct MEMORY_OBJECT
{
	byte8 * addr;
	byte8 * end;
	uint32 last;
	uint32 boundary;
	uint32 size;
	uint32 pipe;
	uint32 count;
	byte8 padding[4];
};
















struct MOTION_DATA
{
	uint8 index;
	uint8 group;
};









struct INPUT_DATA
{
	byte8 flags[8];
	float32 value;
};








struct ShadowData
{
	_(192);
};

static_assert(sizeof(ShadowData) == 0xC0);

struct PhysicsData
{
	_(240);
};

static_assert(sizeof(PhysicsData) == 0xF0);

struct PhysicsMetadata
{
	_(264);
	vec4 * vertices;
	PhysicsData * physicsData;
	_(40);
};

static_assert(offsetof(PhysicsMetadata, vertices) == 0x108);
static_assert(offsetof(PhysicsMetadata, physicsData) == 0x110);
static_assert(sizeof(PhysicsMetadata) == 0x140);





























struct PhysicsLinkData
{
	_(40);
	bool32 enable;
	_(4);
	PhysicsData * physicsData;
	_(72);
	vec4 data[4];
};

static_assert(offsetof(PhysicsLinkData, enable) == 0x28);
static_assert(offsetof(PhysicsLinkData, physicsData) == 0x30);
static_assert(offsetof(PhysicsLinkData, data) == 0x80);
static_assert(sizeof(PhysicsLinkData) == 0xC0);

struct PhysicsLinkMetadata
{
	_(256);
	PhysicsLinkData * devilPhysicsData;
};

static_assert(offsetof(PhysicsLinkMetadata, devilPhysicsData) == 0x100);
















struct BodyPartData
{
	_(288);
};

static_assert(sizeof(BodyPartData) == 0x120);

















//struct DevilPhysicsData
//{
//	DevilPhysicsMetadata metadata[2];
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
//};
//
//static_assert(sizeof(DevilPhysicsData) == 0x300);















struct ModelMetadata
{
	uint8 count;
	_(15);
	vec4 vertices[3];
	_(16);
};

static_assert(sizeof(ModelMetadata) == 80);






struct DevilModelMetadata
{
	uint8 modelIndex;
	uint8 modelPhysicsMetadataIndex;
};

struct DevilSubmodelMetadata
{
	uint8 submodelIndex;
	uint8 devilModelPhysicsMetadataIndex;
	uint8 devilSubmodelIndex;
};














struct DevilModelMetadata1 : DevilModelMetadata
{
	DevilSubmodelMetadata devilSubmodelMetadata;
};

struct DevilModelMetadata2 : DevilModelMetadata
{
	DevilSubmodelMetadata devilSubmodelMetadata[2];
};

struct DevilModelMetadataDante
{
	DevilModelMetadata2 Rebellion;
	DevilModelMetadata1 Cerberus;
	DevilModelMetadata  AgniRudra;
	DevilModelMetadata2 Nevan;
	DevilModelMetadata1 Beowulf;
	DevilModelMetadata1 Sparda;

	DevilModelMetadata2 & operator[](uint8 index)
	{
		switch (index)
		{
		case DEVIL_DANTE_REBELLION:
		{
			return Rebellion;
		}
		case DEVIL_DANTE_CERBERUS:
		{
			return *reinterpret_cast<DevilModelMetadata2 *>(&Cerberus);
		}
		case DEVIL_DANTE_AGNI_RUDRA:
		{
			return *reinterpret_cast<DevilModelMetadata2 *>(&AgniRudra);
		}
		case DEVIL_DANTE_NEVAN:
		{
			return Nevan;
		}
		case DEVIL_DANTE_BEOWULF:
		{
			return *reinterpret_cast<DevilModelMetadata2 *>(&Beowulf);
		}
		case DEVIL_DANTE_SPARDA:
		{
			return *reinterpret_cast<DevilModelMetadata2 *>(&Sparda);
		}
		}
		return Rebellion;
	}
};

static_assert(sizeof(DevilModelMetadataDante) == 33);





















enum DEVIL_FLUX_
{
	DEVIL_FLUX_START = 1,
	DEVIL_FLUX_END   = 2,
};









//constexpr uint16 File_costumeMapDante[MAX_COSTUME_DANTE] =
//{
//	pl000,
//	pl011,
//	pl013,
//	pl015,
//	pl016,
//	pl018,
//	pl013,
//	pl018,
//};




constexpr uint16 costumeFileIdsDante[MAX_COSTUME_DANTE] =
{
	pl000,
	pl011,
	pl013,
	pl015,
	pl016,
	pl018,
	pl013,
	pl018,
};

constexpr uint16 costumeFileIdsBob[MAX_COSTUME_BOB] =
{
	pl001,
};

constexpr uint16 costumeFileIdsLady[MAX_COSTUME_LADY] =
{
	pl002,
	em034,
};

constexpr uint16 costumeFileIdsVergil[MAX_COSTUME_VERGIL] =
{
	pl021,
	pl023,
	pl021,
	pl026,
	pl026,
};



constexpr uint16 devilFileIdsDante[MAX_DEVIL_DANTE] =
{
	pl005,
	pl006,
	pl007,
	pl008,
	pl009,
	pl017,
};


















//struct MODEL_FILE_HELPER
//{
//	struct Data
//	{
//		uint16 cacheFileId;
//		uint8  fileIndex;
//	};
//	Data model;
//	Data texture;
//	Data shadow;
//	Data physics;
//};
//
//typedef MODEL_FILE_HELPER DEVIL_MODEL_FILE_HELPER;





struct ModelPartitionData
{
	uint8 value;
	_(895);
};

static_assert(sizeof(ModelPartitionData) == 0x380);

struct ModelData
{
	_(24);
	bool visible;
	bool physics;
	_(358);
	ModelPartitionData * modelPartitionData;
	_(888);
	struct
	{
		_(84);
		float32 duration1[2];
		_(56);
		float32 duration2[2];
		_(280);
		float32 timer[2];
		_(196);
	}
	Motion;
	operator byte8 *()
	{
		return reinterpret_cast<byte8 *>(this);
	}
};

static_assert(offsetof(ModelData, Motion.duration1) == 0x554);
static_assert(offsetof(ModelData, Motion.duration2) == 0x594);
static_assert(offsetof(ModelData, Motion.timer) == 0x6B4);
static_assert(sizeof(ModelData) == 0x780);





















//struct SHADOW_DATA
//{
//	_(192);
//	operator byte8 *()
//	{
//		return reinterpret_cast<byte8 *>(this);
//	}
//};
//
//static_assert(sizeof(SHADOW_DATA) == 0xC0);
//
//struct PHYSICS_DATA
//{
//	_(240);
//	operator byte8 *()
//	{
//		return reinterpret_cast<byte8 *>(this);
//	}
//};
//
//static_assert(sizeof(PHYSICS_DATA) == 0xF0);


IntroduceSizeStruct(192);
IntroduceSizeStruct(240);
IntroduceSizeStruct(288);
IntroduceSizeStruct(768);
















// $ActorDataStart

struct ACTOR_DATA
{
	_(8);
	uint8 status; // 8
	_(111);
	uint32 character; // 0x78
	_(4);
	vec4 position; // 0x80
	_(4);
	float32 pull; // 0x94
	_(12);
	float32 pullMultiplier; // 0xA4
	_(24);
	uint16 rotation; // 0xC0
	_(86);
	uint8 id; // 0x118
	_(3);
	bool32 isClone; // 0x11C
	uint32 visible; // 0x120
	_(156);
	float32 var_1C0; // 0x1C0
	float32 var_1C4; // 0x1C4
	_(56);
	ModelData modelData[3]; // 0x200
	PhysicsMetadata * modelPhysicsMetadataPool[3][24]; // 0x1880
	_(7636);
	byte8 * var_3894; // 0x3894
	_(4);
	byte8 * motionArchive[32]; // 0x38A0
	_(16);
	MOTION_DATA motionData[2]; // 0x39B0
	MOTION_DATA motionDataMirror[3]; // 0x39B4
	_(2);
	uint32 var_39BC; // 0x39BC
	uint8 var_39C0[16]; // 0x39C0
	uint32 nextActionRequestPolicy[16]; // 0x39D0
	uint8 var_3A10[8]; // 0x3A10
	uint32 shadow; // 0x3A18
	_(12);
	byte32 color; // 0x3A28
	_(932);
	byte8 * actionData[6]; // 0x3DD0
	ACTOR_EVENT_DATA eventData[2]; // 0x3E00
	uint8 var_3E10[32]; // 0x3E10
	_(4);
	float32 motionTimer; // 0x3E34
	float32 idleTimer; // 0x3E38
	_(36);
	byte32 permissions; // 0x3E60
	byte32 state; // 0x3E64
	byte32 lastState; // 0x3E68
	uint32 activeModelIndex; // 0x3E6C
	uint32 queuedModelIndex; // 0x3E70
	uint32 devilModels[3]; // 0x3E74
	uint8 modelState; // 0x3E80
	_(3);
	bool32 lockOn; // 0x3E84
	uint32 activeModelIndexMirror; // 0x3E88
	uint32 activeDevil; // 0x3E8C
	uint32 airRaid; // 0x3E90
	uint32 mode; // 0x3E94
	_(3);
	bool devil; // 0x3E9B
	_(2);
	uint8 costume; // 0x3E9E
	_(5);
	bool useHolyWater; // 0x3EA4
	_(19);
	float32 magicPoints; // 0x3EB8
	float32 maxMagicPoints; // 0x3EBC
	_(18);
	uint16 var_3ED2; // 0x3ED2
	_(4);
	uint16 cameraDirection; // 0x3ED8
	_(55);
	uint8 airHikeCount; // 0x3F11
	uint8 kickJumpCount; // 0x3F12
	uint8 wallHikeCount; // 0x3F13
	_(5);
	bool var_3F19; // 0x3F19
	_(138);
	uint8 action; // 0x3FA4
	uint8 lastAction; // 0x3FA5
	_(2);
	uint8 bufferedAction; // 0x3FA8
	_(3);
	uint8 chainCount; // 0x3FAC
	_(63);
	byte32 expertise[16]; // 0x3FEC
	_(192);
	float32 maxHitPoints; // 0x40EC
	_(44);
	float32 hitPoints; // 0x411C
	_(8712);
	byte8 * targetBaseAddr; // 0x6328
	_(8);
	uint32 style; // 0x6338
	_(28);
	uint32 styleLevel; // 0x6358
	_(8);
	float32 styleExperience; // 0x6364
	_(236);
	bool cloneIsActive; // 0x6454
	_(35);
	byte8 * cloneBaseAddr; // 0x6478
	bool cloneIsControlledByPlayer; // 0x6480
	_(23);
	uint8 weapons[5]; // 0x6498
	_(3);
	byte8 * weaponData[5]; // 0x64A0
	uint32 weaponStatus[5]; // 0x64C8
	uint32 weaponLevels[5]; // 0x64DC
	_(4);
	float32 weaponTimers[5]; // 0x64F4
	_(8);
	uint32 styleRank; // 0x6510
	float32 styleMeter; // 0x6514
	_(348);
	INPUT_DATA inputData[58]; // 0x6674
	_(36);
	BodyPartData bodyPartData[4][2]; // 0x6950
	uint32 var_7250; // 0x7250
	uint32 collisionIndex; // 0x7254
	_(520);
	vec4 interactionData[8]; // 0x7460
	byte16 buttons[4]; // 0x74E0
	_(16);
	uint16 rightStickPosition; // 0x74F8
	uint16 rightStickRadius; // 0x74FA
	_(12);
	uint16 leftStickPosition; // 0x7508
	uint16 leftStickRadius; // 0x750A
	uint16 actorCameraDirection; // 0x750C
	_(14);
	uint32 leftStickDirection[2]; // 0x751C
	_(28);
	ModelData submodelData[5]; // 0x7540
	bool var_9AC0[5]; // 0x9AC0
	_(11);
	ShadowData modelShadowData[3]; // 0x9AD0
	ShadowData submodelShadowData[5]; // 0x9D10
	PhysicsMetadata submodelPhysicsMetadata; // 0xA0D0
	PhysicsData submodelPhysicsData; // 0xA210
	PhysicsLinkMetadata * devilModelPhysicsLinkMetadataPool[2][36]; // 0xA300
	PhysicsData devilSubmodelPhysicsData[4]; // 0xA540
	_(256);
	PhysicsLinkData devilSubmodelPhysicsLinkData[4][4]; // 0xAA00
	_(704);
	byte8 * newParentBaseAddr; // 0xB8C0
	_(8);
	byte8 * newChildBaseAddr; // 0xB8D0
	uint8 newGamepad; // 0xB8D8
	byte16 newButtonMask; // 0xB8D9
	bool newEnableRightStick; // 0xB8DB
	bool newEnableLeftStick; // 0xB8DC
	_(3);
	uint8 newMeleeWeapon[5]; // 0xB8E0
	_(11);
	byte8 * newMeleeWeaponData[5]; // 0xB8F0
	uint8 newMeleeWeaponCount; // 0xB918
	uint8 newMeleeWeaponIndex; // 0xB919
	uint8 newLastMeleeWeapon; // 0xB91A
	_(5);
	uint8 newRangedWeapon[5]; // 0xB920
	_(11);
	byte8 * newRangedWeaponData[5]; // 0xB930
	uint8 newRangedWeaponCount; // 0xB958
	uint8 newRangedWeaponIndex; // 0xB959
	uint8 newLastRangedWeapon; // 0xB95A
	_(5);
	bool newSect[8]; // 0xB960
	uint8 newBufferedActionPolicy; // 0xB968
	uint8 newAirStingerCount; // 0xB969
	bool newForceFiles; // 0xB96A
	uint8 newForceFilesCharacter; // 0xB96B
	_(4);
	byte8 * newDevilAura; // 0xB970
	_(8);
	byte32 newEffectIndices[8]; // 0xB980
	BodyPartData newBodyPartData[7][2]; // 0xB9A0
	ModelData newSubmodelData[11]; // 0xC960
	ShadowData newModelShadowData[6]; // 0x11BE0
	ShadowData newSubmodelShadowData[11]; // 0x12060
	PhysicsMetadata newSubmodelPhysicsMetadata[2]; // 0x128A0
	PhysicsData newSubmodelPhysicsData[2]; // 0x12B20
	PhysicsData newDevilSubmodelPhysicsData[10]; // 0x12D00
	uint32 newLastVar; // 0x13660

	operator byte8 *()
	{
		return reinterpret_cast<byte8 *>(this);
	}
};

struct ACTOR_DATA_DANTE
{
	_(8);
	uint8 status; // 8
	_(111);
	uint32 character; // 0x78
	_(4);
	vec4 position; // 0x80
	_(4);
	float32 pull; // 0x94
	_(12);
	float32 pullMultiplier; // 0xA4
	_(24);
	uint16 rotation; // 0xC0
	_(86);
	uint8 id; // 0x118
	_(3);
	bool32 isClone; // 0x11C
	uint32 visible; // 0x120
	_(156);
	float32 var_1C0; // 0x1C0
	float32 var_1C4; // 0x1C4
	_(56);
	ModelData modelData[3]; // 0x200
	PhysicsMetadata * modelPhysicsMetadataPool[3][24]; // 0x1880
	_(7636);
	byte8 * var_3894; // 0x3894
	_(4);
	byte8 * motionArchive[32]; // 0x38A0
	_(16);
	MOTION_DATA motionData[2]; // 0x39B0
	MOTION_DATA motionDataMirror[3]; // 0x39B4
	_(2);
	uint32 var_39BC; // 0x39BC
	uint8 var_39C0[16]; // 0x39C0
	uint32 nextActionRequestPolicy[16]; // 0x39D0
	uint8 var_3A10[8]; // 0x3A10
	uint32 shadow; // 0x3A18
	_(12);
	byte32 color; // 0x3A28
	_(932);
	byte8 * actionData[6]; // 0x3DD0
	ACTOR_EVENT_DATA eventData[2]; // 0x3E00
	uint8 var_3E10[32]; // 0x3E10
	_(4);
	float32 motionTimer; // 0x3E34
	float32 idleTimer; // 0x3E38
	_(36);
	byte32 permissions; // 0x3E60
	byte32 state; // 0x3E64
	byte32 lastState; // 0x3E68
	uint32 activeModelIndex; // 0x3E6C
	uint32 queuedModelIndex; // 0x3E70
	uint32 devilModels[3]; // 0x3E74
	uint8 modelState; // 0x3E80
	_(3);
	bool32 lockOn; // 0x3E84
	uint32 activeModelIndexMirror; // 0x3E88
	uint32 activeDevil; // 0x3E8C
	uint32 airRaid; // 0x3E90
	uint32 mode; // 0x3E94
	_(3);
	bool devil; // 0x3E9B
	_(2);
	uint8 costume; // 0x3E9E
	bool sparda; // 0x3E9F
	_(4);
	bool useHolyWater; // 0x3EA4
	_(19);
	float32 magicPoints; // 0x3EB8
	float32 maxMagicPoints; // 0x3EBC
	_(18);
	uint16 var_3ED2; // 0x3ED2
	_(4);
	uint16 cameraDirection; // 0x3ED8
	_(55);
	uint8 airHikeCount; // 0x3F11
	uint8 kickJumpCount; // 0x3F12
	uint8 wallHikeCount; // 0x3F13
	_(5);
	bool var_3F19; // 0x3F19
	_(138);
	uint8 action; // 0x3FA4
	uint8 lastAction; // 0x3FA5
	_(2);
	uint8 bufferedAction; // 0x3FA8
	_(3);
	uint8 chainCount; // 0x3FAC
	_(63);
	byte32 expertise[16]; // 0x3FEC
	_(192);
	float32 maxHitPoints; // 0x40EC
	_(44);
	float32 hitPoints; // 0x411C
	_(8712);
	byte8 * targetBaseAddr; // 0x6328
	_(8);
	uint32 style; // 0x6338
	_(28);
	uint32 styleLevel; // 0x6358
	uint8 dashCount; // 0x635C
	uint8 skyStarCount; // 0x635D
	uint8 airTrickCount; // 0x635E
	_(2);
	bool quicksilver; // 0x6361
	bool doppelganger; // 0x6362
	_(1);
	float32 styleExperience; // 0x6364
	_(236);
	bool cloneIsActive; // 0x6454
	_(35);
	byte8 * cloneBaseAddr; // 0x6478
	bool cloneIsControlledByPlayer; // 0x6480
	_(12);
	uint8 activeWeapon; // 0x648D
	_(2);
	uint32 meleeWeaponIndex; // 0x6490
	uint32 rangedWeaponIndex; // 0x6494
	uint8 weapons[5]; // 0x6498
	_(3);
	byte8 * weaponData[5]; // 0x64A0
	uint32 weaponStatus[5]; // 0x64C8
	uint32 weaponLevels[5]; // 0x64DC
	uint8 activeMeleeWeapon; // 0x64F0
	uint8 activeRangedWeapon; // 0x64F1
	_(2);
	float32 weaponTimers[5]; // 0x64F4
	float32 meleeWeaponSwitchTimeout; // 0x6508
	float32 rangedWeaponSwitchTimeout; // 0x650C
	uint32 styleRank; // 0x6510
	float32 styleMeter; // 0x6514
	_(348);
	INPUT_DATA inputData[58]; // 0x6674
	_(36);
	BodyPartData bodyPartData[4][2]; // 0x6950
	uint32 var_7250; // 0x7250
	uint32 collisionIndex; // 0x7254
	_(520);
	vec4 interactionData[8]; // 0x7460
	byte16 buttons[4]; // 0x74E0
	_(16);
	uint16 rightStickPosition; // 0x74F8
	uint16 rightStickRadius; // 0x74FA
	_(12);
	uint16 leftStickPosition; // 0x7508
	uint16 leftStickRadius; // 0x750A
	uint16 actorCameraDirection; // 0x750C
	_(14);
	uint32 leftStickDirection[2]; // 0x751C
	_(28);
	ModelData submodelData[5]; // 0x7540
	bool var_9AC0[5]; // 0x9AC0
	_(11);
	ShadowData modelShadowData[3]; // 0x9AD0
	ShadowData submodelShadowData[5]; // 0x9D10
	PhysicsMetadata submodelPhysicsMetadata; // 0xA0D0
	PhysicsData submodelPhysicsData; // 0xA210
	PhysicsLinkMetadata * devilModelPhysicsLinkMetadataPool[2][36]; // 0xA300
	PhysicsData devilSubmodelPhysicsData[4]; // 0xA540
	_(256);
	PhysicsLinkData devilSubmodelPhysicsLinkData[4][4]; // 0xAA00
	DevilModelMetadataDante devilModelMetadata; // 0xB600
	_(15);
	ModelMetadata modelMetadata[6]; // 0xB630
	_(88);
	float32 artemisChargeValue[2]; // 0xB868
	_(12);
	byte32 artemisChargeFlags[2]; // 0xB87C
	_(60);
	byte8 * newParentBaseAddr; // 0xB8C0
	_(8);
	byte8 * newChildBaseAddr; // 0xB8D0
	uint8 newGamepad; // 0xB8D8
	byte16 newButtonMask; // 0xB8D9
	bool newEnableRightStick; // 0xB8DB
	bool newEnableLeftStick; // 0xB8DC
	_(3);
	uint8 newMeleeWeapon[5]; // 0xB8E0
	_(11);
	byte8 * newMeleeWeaponData[5]; // 0xB8F0
	uint8 newMeleeWeaponCount; // 0xB918
	uint8 newMeleeWeaponIndex; // 0xB919
	uint8 newLastMeleeWeapon; // 0xB91A
	_(5);
	uint8 newRangedWeapon[5]; // 0xB920
	_(11);
	byte8 * newRangedWeaponData[5]; // 0xB930
	uint8 newRangedWeaponCount; // 0xB958
	uint8 newRangedWeaponIndex; // 0xB959
	uint8 newLastRangedWeapon; // 0xB95A
	_(5);
	bool newSect[8]; // 0xB960
	uint8 newBufferedActionPolicy; // 0xB968
	uint8 newAirStingerCount; // 0xB969
	bool newForceFiles; // 0xB96A
	uint8 newForceFilesCharacter; // 0xB96B
	_(4);
	byte8 * newDevilAura; // 0xB970
	_(8);
	byte32 newEffectIndices[8]; // 0xB980
	BodyPartData newBodyPartData[7][2]; // 0xB9A0
	ModelData newSubmodelData[11]; // 0xC960
	ShadowData newModelShadowData[6]; // 0x11BE0
	ShadowData newSubmodelShadowData[11]; // 0x12060
	PhysicsMetadata newSubmodelPhysicsMetadata[2]; // 0x128A0
	PhysicsData newSubmodelPhysicsData[2]; // 0x12B20
	PhysicsData newDevilSubmodelPhysicsData[10]; // 0x12D00
	uint32 newLastVar; // 0x13660

	operator byte8 *()
	{
		return reinterpret_cast<byte8 *>(this);
	}
};

struct ACTOR_DATA_BOB
{
	_(8);
	uint8 status; // 8
	_(111);
	uint32 character; // 0x78
	_(4);
	vec4 position; // 0x80
	_(4);
	float32 pull; // 0x94
	_(12);
	float32 pullMultiplier; // 0xA4
	_(24);
	uint16 rotation; // 0xC0
	_(86);
	uint8 id; // 0x118
	_(3);
	bool32 isClone; // 0x11C
	uint32 visible; // 0x120
	_(156);
	float32 var_1C0; // 0x1C0
	float32 var_1C4; // 0x1C4
	_(56);
	ModelData modelData[3]; // 0x200
	PhysicsMetadata * modelPhysicsMetadataPool[3][24]; // 0x1880
	_(7636);
	byte8 * var_3894; // 0x3894
	_(4);
	byte8 * motionArchive[32]; // 0x38A0
	_(16);
	MOTION_DATA motionData[2]; // 0x39B0
	MOTION_DATA motionDataMirror[3]; // 0x39B4
	_(2);
	uint32 var_39BC; // 0x39BC
	uint8 var_39C0[16]; // 0x39C0
	uint32 nextActionRequestPolicy[16]; // 0x39D0
	uint8 var_3A10[8]; // 0x3A10
	uint32 shadow; // 0x3A18
	_(12);
	byte32 color; // 0x3A28
	_(932);
	byte8 * actionData[6]; // 0x3DD0
	ACTOR_EVENT_DATA eventData[2]; // 0x3E00
	uint8 var_3E10[32]; // 0x3E10
	_(4);
	float32 motionTimer; // 0x3E34
	float32 idleTimer; // 0x3E38
	_(36);
	byte32 permissions; // 0x3E60
	byte32 state; // 0x3E64
	byte32 lastState; // 0x3E68
	uint32 activeModelIndex; // 0x3E6C
	uint32 queuedModelIndex; // 0x3E70
	uint32 devilModels[3]; // 0x3E74
	uint8 modelState; // 0x3E80
	_(3);
	bool32 lockOn; // 0x3E84
	uint32 activeModelIndexMirror; // 0x3E88
	uint32 activeDevil; // 0x3E8C
	uint32 airRaid; // 0x3E90
	uint32 mode; // 0x3E94
	_(3);
	bool devil; // 0x3E9B
	_(2);
	uint8 costume; // 0x3E9E
	_(5);
	bool useHolyWater; // 0x3EA4
	_(19);
	float32 magicPoints; // 0x3EB8
	float32 maxMagicPoints; // 0x3EBC
	_(18);
	uint16 var_3ED2; // 0x3ED2
	_(4);
	uint16 cameraDirection; // 0x3ED8
	_(55);
	uint8 airHikeCount; // 0x3F11
	uint8 kickJumpCount; // 0x3F12
	uint8 wallHikeCount; // 0x3F13
	_(5);
	bool var_3F19; // 0x3F19
	_(138);
	uint8 action; // 0x3FA4
	uint8 lastAction; // 0x3FA5
	_(2);
	uint8 bufferedAction; // 0x3FA8
	_(3);
	uint8 chainCount; // 0x3FAC
	_(63);
	byte32 expertise[16]; // 0x3FEC
	_(192);
	float32 maxHitPoints; // 0x40EC
	_(44);
	float32 hitPoints; // 0x411C
	_(8712);
	byte8 * targetBaseAddr; // 0x6328
	_(8);
	uint32 style; // 0x6338
	_(28);
	uint32 styleLevel; // 0x6358
	_(8);
	float32 styleExperience; // 0x6364
	_(236);
	bool cloneIsActive; // 0x6454
	_(35);
	byte8 * cloneBaseAddr; // 0x6478
	bool cloneIsControlledByPlayer; // 0x6480
	_(23);
	uint8 weapons[5]; // 0x6498
	_(3);
	byte8 * weaponData[5]; // 0x64A0
	uint32 weaponStatus[5]; // 0x64C8
	uint32 weaponLevels[5]; // 0x64DC
	_(4);
	float32 weaponTimers[5]; // 0x64F4
	_(8);
	uint32 styleRank; // 0x6510
	float32 styleMeter; // 0x6514
	_(348);
	INPUT_DATA inputData[58]; // 0x6674
	_(36);
	BodyPartData bodyPartData[4][2]; // 0x6950
	uint32 var_7250; // 0x7250
	uint32 collisionIndex; // 0x7254
	_(520);
	vec4 interactionData[8]; // 0x7460
	byte16 buttons[4]; // 0x74E0
	_(16);
	uint16 rightStickPosition; // 0x74F8
	uint16 rightStickRadius; // 0x74FA
	_(12);
	uint16 leftStickPosition; // 0x7508
	uint16 leftStickRadius; // 0x750A
	uint16 actorCameraDirection; // 0x750C
	_(14);
	uint32 leftStickDirection[2]; // 0x751C
	_(28);
	ModelData submodelData[5]; // 0x7540
	bool var_9AC0[5]; // 0x9AC0
	_(11);
	ShadowData modelShadowData[3]; // 0x9AD0
	ShadowData submodelShadowData[5]; // 0x9D10
	PhysicsMetadata submodelPhysicsMetadata; // 0xA0D0
	PhysicsData submodelPhysicsData; // 0xA210
	PhysicsLinkMetadata * devilModelPhysicsLinkMetadataPool[2][36]; // 0xA300
	PhysicsData devilSubmodelPhysicsData[4]; // 0xA540
	_(256);
	PhysicsLinkData devilSubmodelPhysicsLinkData[4][4]; // 0xAA00
	_(704);
	byte8 * newParentBaseAddr; // 0xB8C0
	_(8);
	byte8 * newChildBaseAddr; // 0xB8D0
	uint8 newGamepad; // 0xB8D8
	byte16 newButtonMask; // 0xB8D9
	bool newEnableRightStick; // 0xB8DB
	bool newEnableLeftStick; // 0xB8DC
	_(3);
	uint8 newMeleeWeapon[5]; // 0xB8E0
	_(11);
	byte8 * newMeleeWeaponData[5]; // 0xB8F0
	uint8 newMeleeWeaponCount; // 0xB918
	uint8 newMeleeWeaponIndex; // 0xB919
	uint8 newLastMeleeWeapon; // 0xB91A
	_(5);
	uint8 newRangedWeapon[5]; // 0xB920
	_(11);
	byte8 * newRangedWeaponData[5]; // 0xB930
	uint8 newRangedWeaponCount; // 0xB958
	uint8 newRangedWeaponIndex; // 0xB959
	uint8 newLastRangedWeapon; // 0xB95A
	_(5);
	bool newSect[8]; // 0xB960
	uint8 newBufferedActionPolicy; // 0xB968
	uint8 newAirStingerCount; // 0xB969
	bool newForceFiles; // 0xB96A
	uint8 newForceFilesCharacter; // 0xB96B
	_(4);
	byte8 * newDevilAura; // 0xB970
	_(8);
	byte32 newEffectIndices[8]; // 0xB980
	BodyPartData newBodyPartData[7][2]; // 0xB9A0
	ModelData newSubmodelData[11]; // 0xC960
	ShadowData newModelShadowData[6]; // 0x11BE0
	ShadowData newSubmodelShadowData[11]; // 0x12060
	PhysicsMetadata newSubmodelPhysicsMetadata[2]; // 0x128A0
	PhysicsData newSubmodelPhysicsData[2]; // 0x12B20
	PhysicsData newDevilSubmodelPhysicsData[10]; // 0x12D00
	uint32 newLastVar; // 0x13660

	operator byte8 *()
	{
		return reinterpret_cast<byte8 *>(this);
	}
};

struct ACTOR_DATA_LADY
{
	_(8);
	uint8 status; // 8
	_(111);
	uint32 character; // 0x78
	_(4);
	vec4 position; // 0x80
	_(4);
	float32 pull; // 0x94
	_(12);
	float32 pullMultiplier; // 0xA4
	_(24);
	uint16 rotation; // 0xC0
	_(86);
	uint8 id; // 0x118
	_(3);
	bool32 isClone; // 0x11C
	uint32 visible; // 0x120
	_(156);
	float32 var_1C0; // 0x1C0
	float32 var_1C4; // 0x1C4
	_(56);
	ModelData modelData[3]; // 0x200
	PhysicsMetadata * modelPhysicsMetadataPool[3][24]; // 0x1880
	_(7636);
	byte8 * var_3894; // 0x3894
	_(4);
	byte8 * motionArchive[32]; // 0x38A0
	_(16);
	MOTION_DATA motionData[2]; // 0x39B0
	MOTION_DATA motionDataMirror[3]; // 0x39B4
	_(2);
	uint32 var_39BC; // 0x39BC
	uint8 var_39C0[16]; // 0x39C0
	uint32 nextActionRequestPolicy[16]; // 0x39D0
	uint8 var_3A10[8]; // 0x3A10
	uint32 shadow; // 0x3A18
	_(12);
	byte32 color; // 0x3A28
	_(932);
	byte8 * actionData[6]; // 0x3DD0
	ACTOR_EVENT_DATA eventData[2]; // 0x3E00
	uint8 var_3E10[32]; // 0x3E10
	_(4);
	float32 motionTimer; // 0x3E34
	float32 idleTimer; // 0x3E38
	_(36);
	byte32 permissions; // 0x3E60
	byte32 state; // 0x3E64
	byte32 lastState; // 0x3E68
	uint32 activeModelIndex; // 0x3E6C
	uint32 queuedModelIndex; // 0x3E70
	uint32 devilModels[3]; // 0x3E74
	uint8 modelState; // 0x3E80
	_(3);
	bool32 lockOn; // 0x3E84
	uint32 activeModelIndexMirror; // 0x3E88
	uint32 activeDevil; // 0x3E8C
	uint32 airRaid; // 0x3E90
	uint32 mode; // 0x3E94
	_(3);
	bool devil; // 0x3E9B
	_(2);
	uint8 costume; // 0x3E9E
	_(5);
	bool useHolyWater; // 0x3EA4
	_(19);
	float32 magicPoints; // 0x3EB8
	float32 maxMagicPoints; // 0x3EBC
	_(18);
	uint16 var_3ED2; // 0x3ED2
	_(4);
	uint16 cameraDirection; // 0x3ED8
	_(55);
	uint8 airHikeCount; // 0x3F11
	uint8 kickJumpCount; // 0x3F12
	uint8 wallHikeCount; // 0x3F13
	_(5);
	bool var_3F19; // 0x3F19
	_(138);
	uint8 action; // 0x3FA4
	uint8 lastAction; // 0x3FA5
	_(2);
	uint8 bufferedAction; // 0x3FA8
	_(3);
	uint8 chainCount; // 0x3FAC
	_(63);
	byte32 expertise[16]; // 0x3FEC
	_(192);
	float32 maxHitPoints; // 0x40EC
	_(44);
	float32 hitPoints; // 0x411C
	_(8712);
	byte8 * targetBaseAddr; // 0x6328
	_(8);
	uint32 style; // 0x6338
	_(28);
	uint32 styleLevel; // 0x6358
	_(8);
	float32 styleExperience; // 0x6364
	_(236);
	bool cloneIsActive; // 0x6454
	_(35);
	byte8 * cloneBaseAddr; // 0x6478
	bool cloneIsControlledByPlayer; // 0x6480
	_(23);
	uint8 weapons[5]; // 0x6498
	_(3);
	byte8 * weaponData[5]; // 0x64A0
	uint32 weaponStatus[5]; // 0x64C8
	uint32 weaponLevels[5]; // 0x64DC
	_(4);
	float32 weaponTimers[5]; // 0x64F4
	_(8);
	uint32 styleRank; // 0x6510
	float32 styleMeter; // 0x6514
	_(348);
	INPUT_DATA inputData[58]; // 0x6674
	_(36);
	BodyPartData bodyPartData[4][2]; // 0x6950
	uint32 var_7250; // 0x7250
	uint32 collisionIndex; // 0x7254
	_(520);
	vec4 interactionData[8]; // 0x7460
	byte16 buttons[4]; // 0x74E0
	_(16);
	uint16 rightStickPosition; // 0x74F8
	uint16 rightStickRadius; // 0x74FA
	_(12);
	uint16 leftStickPosition; // 0x7508
	uint16 leftStickRadius; // 0x750A
	uint16 actorCameraDirection; // 0x750C
	_(14);
	uint32 leftStickDirection[2]; // 0x751C
	_(28);
	ModelData submodelData[5]; // 0x7540
	bool var_9AC0[5]; // 0x9AC0
	_(11);
	ShadowData modelShadowData[3]; // 0x9AD0
	ShadowData submodelShadowData[5]; // 0x9D10
	PhysicsMetadata submodelPhysicsMetadata; // 0xA0D0
	PhysicsData submodelPhysicsData; // 0xA210
	PhysicsLinkMetadata * devilModelPhysicsLinkMetadataPool[2][36]; // 0xA300
	PhysicsData devilSubmodelPhysicsData[4]; // 0xA540
	_(256);
	PhysicsLinkData devilSubmodelPhysicsLinkData[4][4]; // 0xAA00
	_(704);
	byte8 * newParentBaseAddr; // 0xB8C0
	_(8);
	byte8 * newChildBaseAddr; // 0xB8D0
	uint8 newGamepad; // 0xB8D8
	byte16 newButtonMask; // 0xB8D9
	bool newEnableRightStick; // 0xB8DB
	bool newEnableLeftStick; // 0xB8DC
	_(3);
	uint8 newMeleeWeapon[5]; // 0xB8E0
	_(11);
	byte8 * newMeleeWeaponData[5]; // 0xB8F0
	uint8 newMeleeWeaponCount; // 0xB918
	uint8 newMeleeWeaponIndex; // 0xB919
	uint8 newLastMeleeWeapon; // 0xB91A
	_(5);
	uint8 newRangedWeapon[5]; // 0xB920
	_(11);
	byte8 * newRangedWeaponData[5]; // 0xB930
	uint8 newRangedWeaponCount; // 0xB958
	uint8 newRangedWeaponIndex; // 0xB959
	uint8 newLastRangedWeapon; // 0xB95A
	_(5);
	bool newSect[8]; // 0xB960
	uint8 newBufferedActionPolicy; // 0xB968
	uint8 newAirStingerCount; // 0xB969
	bool newForceFiles; // 0xB96A
	uint8 newForceFilesCharacter; // 0xB96B
	_(4);
	byte8 * newDevilAura; // 0xB970
	_(8);
	byte32 newEffectIndices[8]; // 0xB980
	BodyPartData newBodyPartData[7][2]; // 0xB9A0
	ModelData newSubmodelData[11]; // 0xC960
	ShadowData newModelShadowData[6]; // 0x11BE0
	ShadowData newSubmodelShadowData[11]; // 0x12060
	PhysicsMetadata newSubmodelPhysicsMetadata[2]; // 0x128A0
	PhysicsData newSubmodelPhysicsData[2]; // 0x12B20
	PhysicsData newDevilSubmodelPhysicsData[10]; // 0x12D00
	uint32 newLastVar; // 0x13660

	operator byte8 *()
	{
		return reinterpret_cast<byte8 *>(this);
	}
};

struct ACTOR_DATA_VERGIL
{
	_(8);
	uint8 status; // 8
	_(111);
	uint32 character; // 0x78
	_(4);
	vec4 position; // 0x80
	_(4);
	float32 pull; // 0x94
	_(12);
	float32 pullMultiplier; // 0xA4
	_(24);
	uint16 rotation; // 0xC0
	_(86);
	uint8 id; // 0x118
	_(3);
	bool32 isClone; // 0x11C
	uint32 visible; // 0x120
	_(156);
	float32 var_1C0; // 0x1C0
	float32 var_1C4; // 0x1C4
	_(56);
	ModelData modelData[3]; // 0x200
	PhysicsMetadata * modelPhysicsMetadataPool[3][24]; // 0x1880
	_(7636);
	byte8 * var_3894; // 0x3894
	_(4);
	byte8 * motionArchive[32]; // 0x38A0
	_(16);
	MOTION_DATA motionData[2]; // 0x39B0
	MOTION_DATA motionDataMirror[3]; // 0x39B4
	_(2);
	uint32 var_39BC; // 0x39BC
	uint8 var_39C0[16]; // 0x39C0
	uint32 nextActionRequestPolicy[16]; // 0x39D0
	uint8 var_3A10[8]; // 0x3A10
	uint32 shadow; // 0x3A18
	_(12);
	byte32 color; // 0x3A28
	_(932);
	byte8 * actionData[6]; // 0x3DD0
	ACTOR_EVENT_DATA eventData[2]; // 0x3E00
	uint8 var_3E10[32]; // 0x3E10
	_(4);
	float32 motionTimer; // 0x3E34
	float32 idleTimer; // 0x3E38
	_(36);
	byte32 permissions; // 0x3E60
	byte32 state; // 0x3E64
	byte32 lastState; // 0x3E68
	uint32 activeModelIndex; // 0x3E6C
	uint32 queuedModelIndex; // 0x3E70
	uint32 devilModels[3]; // 0x3E74
	uint8 modelState; // 0x3E80
	_(3);
	bool32 lockOn; // 0x3E84
	uint32 activeModelIndexMirror; // 0x3E88
	uint32 activeDevil; // 0x3E8C
	uint32 airRaid; // 0x3E90
	uint32 mode; // 0x3E94
	_(3);
	bool devil; // 0x3E9B
	_(2);
	uint8 costume; // 0x3E9E
	bool neroAngelo; // 0x3E9F
	_(4);
	bool useHolyWater; // 0x3EA4
	_(19);
	float32 magicPoints; // 0x3EB8
	float32 maxMagicPoints; // 0x3EBC
	_(18);
	uint16 var_3ED2; // 0x3ED2
	_(4);
	uint16 cameraDirection; // 0x3ED8
	_(55);
	uint8 airHikeCount; // 0x3F11
	uint8 kickJumpCount; // 0x3F12
	uint8 wallHikeCount; // 0x3F13
	_(5);
	bool var_3F19; // 0x3F19
	_(138);
	uint8 action; // 0x3FA4
	uint8 lastAction; // 0x3FA5
	_(2);
	uint8 bufferedAction; // 0x3FA8
	_(3);
	uint8 chainCount; // 0x3FAC
	_(63);
	byte32 expertise[16]; // 0x3FEC
	_(192);
	float32 maxHitPoints; // 0x40EC
	_(44);
	float32 hitPoints; // 0x411C
	_(8712);
	byte8 * targetBaseAddr; // 0x6328
	_(8);
	uint32 style; // 0x6338
	_(28);
	uint32 styleLevel; // 0x6358
	_(2);
	uint8 airTrickCount; // 0x635E
	uint8 trickUpCount; // 0x635F
	uint8 trickDownCount; // 0x6360
	_(3);
	float32 styleExperience; // 0x6364
	_(236);
	bool cloneIsActive; // 0x6454
	_(35);
	byte8 * cloneBaseAddr; // 0x6478
	bool cloneIsControlledByPlayer; // 0x6480
	_(3);
	uint32 activeMeleeWeaponIndex; // 0x6484
	uint32 queuedMeleeWeaponIndex; // 0x6488
	_(12);
	uint8 weapons[5]; // 0x6498
	_(3);
	byte8 * weaponData[5]; // 0x64A0
	uint32 weaponStatus[5]; // 0x64C8
	uint32 weaponLevels[5]; // 0x64DC
	_(4);
	float32 weaponTimers[5]; // 0x64F4
	float32 meleeWeaponSwitchForwardTimeout; // 0x6508
	float32 meleeWeaponSwitchBackTimeout; // 0x650C
	uint32 styleRank; // 0x6510
	float32 styleMeter; // 0x6514
	_(348);
	INPUT_DATA inputData[58]; // 0x6674
	_(36);
	BodyPartData bodyPartData[4][2]; // 0x6950
	uint32 var_7250; // 0x7250
	uint32 collisionIndex; // 0x7254
	_(520);
	vec4 interactionData[8]; // 0x7460
	byte16 buttons[4]; // 0x74E0
	_(16);
	uint16 rightStickPosition; // 0x74F8
	uint16 rightStickRadius; // 0x74FA
	_(12);
	uint16 leftStickPosition; // 0x7508
	uint16 leftStickRadius; // 0x750A
	uint16 actorCameraDirection; // 0x750C
	_(14);
	uint32 leftStickDirection[2]; // 0x751C
	_(28);
	ModelData submodelData[5]; // 0x7540
	bool var_9AC0[5]; // 0x9AC0
	_(11);
	ShadowData modelShadowData[3]; // 0x9AD0
	ShadowData submodelShadowData[5]; // 0x9D10
	PhysicsMetadata submodelPhysicsMetadata; // 0xA0D0
	PhysicsData submodelPhysicsData; // 0xA210
	PhysicsLinkMetadata * devilModelPhysicsLinkMetadataPool[2][36]; // 0xA300
	PhysicsData devilSubmodelPhysicsData[4]; // 0xA540
	_(256);
	PhysicsLinkData devilSubmodelPhysicsLinkData[4][4]; // 0xAA00
	_(704);
	byte8 * newParentBaseAddr; // 0xB8C0
	_(8);
	byte8 * newChildBaseAddr; // 0xB8D0
	uint8 newGamepad; // 0xB8D8
	byte16 newButtonMask; // 0xB8D9
	bool newEnableRightStick; // 0xB8DB
	bool newEnableLeftStick; // 0xB8DC
	_(3);
	uint8 newMeleeWeapon[5]; // 0xB8E0
	_(11);
	byte8 * newMeleeWeaponData[5]; // 0xB8F0
	uint8 newMeleeWeaponCount; // 0xB918
	uint8 newMeleeWeaponIndex; // 0xB919
	uint8 newLastMeleeWeapon; // 0xB91A
	_(5);
	uint8 newRangedWeapon[5]; // 0xB920
	_(11);
	byte8 * newRangedWeaponData[5]; // 0xB930
	uint8 newRangedWeaponCount; // 0xB958
	uint8 newRangedWeaponIndex; // 0xB959
	uint8 newLastRangedWeapon; // 0xB95A
	_(5);
	bool newSect[8]; // 0xB960
	uint8 newBufferedActionPolicy; // 0xB968
	uint8 newAirStingerCount; // 0xB969
	bool newForceFiles; // 0xB96A
	uint8 newForceFilesCharacter; // 0xB96B
	_(4);
	byte8 * newDevilAura; // 0xB970
	_(8);
	byte32 newEffectIndices[8]; // 0xB980
	BodyPartData newBodyPartData[7][2]; // 0xB9A0
	ModelData newSubmodelData[11]; // 0xC960
	ShadowData newModelShadowData[6]; // 0x11BE0
	ShadowData newSubmodelShadowData[11]; // 0x12060
	PhysicsMetadata newSubmodelPhysicsMetadata[2]; // 0x128A0
	PhysicsData newSubmodelPhysicsData[2]; // 0x12B20
	PhysicsData newDevilSubmodelPhysicsData[10]; // 0x12D00
	uint32 newLastVar; // 0x13660

	operator byte8 *()
	{
		return reinterpret_cast<byte8 *>(this);
	}
};

static_assert(offsetof(ACTOR_DATA, status) == 8);
static_assert(offsetof(ACTOR_DATA, character) == 0x78);
static_assert(offsetof(ACTOR_DATA, position) == 0x80);
static_assert(offsetof(ACTOR_DATA, pull) == 0x94);
static_assert(offsetof(ACTOR_DATA, pullMultiplier) == 0xA4);
static_assert(offsetof(ACTOR_DATA, rotation) == 0xC0);
static_assert(offsetof(ACTOR_DATA, id) == 0x118);
static_assert(offsetof(ACTOR_DATA, isClone) == 0x11C);
static_assert(offsetof(ACTOR_DATA, visible) == 0x120);
static_assert(offsetof(ACTOR_DATA, var_1C0) == 0x1C0);
static_assert(offsetof(ACTOR_DATA, var_1C4) == 0x1C4);
static_assert(offsetof(ACTOR_DATA, modelData) == 0x200);
static_assert(offsetof(ACTOR_DATA, modelPhysicsMetadataPool) == 0x1880);
static_assert(offsetof(ACTOR_DATA, var_3894) == 0x3894);
static_assert(offsetof(ACTOR_DATA, motionArchive) == 0x38A0);
static_assert(offsetof(ACTOR_DATA, motionData) == 0x39B0);
static_assert(offsetof(ACTOR_DATA, motionDataMirror) == 0x39B4);
static_assert(offsetof(ACTOR_DATA, var_39BC) == 0x39BC);
static_assert(offsetof(ACTOR_DATA, var_39C0) == 0x39C0);
static_assert(offsetof(ACTOR_DATA, nextActionRequestPolicy) == 0x39D0);
static_assert(offsetof(ACTOR_DATA, var_3A10) == 0x3A10);
static_assert(offsetof(ACTOR_DATA, shadow) == 0x3A18);
static_assert(offsetof(ACTOR_DATA, color) == 0x3A28);
static_assert(offsetof(ACTOR_DATA, actionData) == 0x3DD0);
static_assert(offsetof(ACTOR_DATA, eventData) == 0x3E00);
static_assert(offsetof(ACTOR_DATA, var_3E10) == 0x3E10);
static_assert(offsetof(ACTOR_DATA, motionTimer) == 0x3E34);
static_assert(offsetof(ACTOR_DATA, idleTimer) == 0x3E38);
static_assert(offsetof(ACTOR_DATA, permissions) == 0x3E60);
static_assert(offsetof(ACTOR_DATA, state) == 0x3E64);
static_assert(offsetof(ACTOR_DATA, lastState) == 0x3E68);
static_assert(offsetof(ACTOR_DATA, activeModelIndex) == 0x3E6C);
static_assert(offsetof(ACTOR_DATA, queuedModelIndex) == 0x3E70);
static_assert(offsetof(ACTOR_DATA, devilModels) == 0x3E74);
static_assert(offsetof(ACTOR_DATA, modelState) == 0x3E80);
static_assert(offsetof(ACTOR_DATA, lockOn) == 0x3E84);
static_assert(offsetof(ACTOR_DATA, activeModelIndexMirror) == 0x3E88);
static_assert(offsetof(ACTOR_DATA, activeDevil) == 0x3E8C);
static_assert(offsetof(ACTOR_DATA, airRaid) == 0x3E90);
static_assert(offsetof(ACTOR_DATA, mode) == 0x3E94);
static_assert(offsetof(ACTOR_DATA, devil) == 0x3E9B);
static_assert(offsetof(ACTOR_DATA, costume) == 0x3E9E);
static_assert(offsetof(ACTOR_DATA, useHolyWater) == 0x3EA4);
static_assert(offsetof(ACTOR_DATA, magicPoints) == 0x3EB8);
static_assert(offsetof(ACTOR_DATA, maxMagicPoints) == 0x3EBC);
static_assert(offsetof(ACTOR_DATA, var_3ED2) == 0x3ED2);
static_assert(offsetof(ACTOR_DATA, cameraDirection) == 0x3ED8);
static_assert(offsetof(ACTOR_DATA, airHikeCount) == 0x3F11);
static_assert(offsetof(ACTOR_DATA, kickJumpCount) == 0x3F12);
static_assert(offsetof(ACTOR_DATA, wallHikeCount) == 0x3F13);
static_assert(offsetof(ACTOR_DATA, var_3F19) == 0x3F19);
static_assert(offsetof(ACTOR_DATA, action) == 0x3FA4);
static_assert(offsetof(ACTOR_DATA, lastAction) == 0x3FA5);
static_assert(offsetof(ACTOR_DATA, bufferedAction) == 0x3FA8);
static_assert(offsetof(ACTOR_DATA, chainCount) == 0x3FAC);
static_assert(offsetof(ACTOR_DATA, expertise) == 0x3FEC);
static_assert(offsetof(ACTOR_DATA, maxHitPoints) == 0x40EC);
static_assert(offsetof(ACTOR_DATA, hitPoints) == 0x411C);
static_assert(offsetof(ACTOR_DATA, targetBaseAddr) == 0x6328);
static_assert(offsetof(ACTOR_DATA, style) == 0x6338);
static_assert(offsetof(ACTOR_DATA, styleLevel) == 0x6358);
static_assert(offsetof(ACTOR_DATA, styleExperience) == 0x6364);
static_assert(offsetof(ACTOR_DATA, cloneIsActive) == 0x6454);
static_assert(offsetof(ACTOR_DATA, cloneBaseAddr) == 0x6478);
static_assert(offsetof(ACTOR_DATA, cloneIsControlledByPlayer) == 0x6480);
static_assert(offsetof(ACTOR_DATA, weapons) == 0x6498);
static_assert(offsetof(ACTOR_DATA, weaponData) == 0x64A0);
static_assert(offsetof(ACTOR_DATA, weaponStatus) == 0x64C8);
static_assert(offsetof(ACTOR_DATA, weaponLevels) == 0x64DC);
static_assert(offsetof(ACTOR_DATA, weaponTimers) == 0x64F4);
static_assert(offsetof(ACTOR_DATA, styleRank) == 0x6510);
static_assert(offsetof(ACTOR_DATA, styleMeter) == 0x6514);
static_assert(offsetof(ACTOR_DATA, inputData) == 0x6674);
static_assert(offsetof(ACTOR_DATA, bodyPartData) == 0x6950);
static_assert(offsetof(ACTOR_DATA, var_7250) == 0x7250);
static_assert(offsetof(ACTOR_DATA, collisionIndex) == 0x7254);
static_assert(offsetof(ACTOR_DATA, interactionData) == 0x7460);
static_assert(offsetof(ACTOR_DATA, buttons) == 0x74E0);
static_assert(offsetof(ACTOR_DATA, rightStickPosition) == 0x74F8);
static_assert(offsetof(ACTOR_DATA, rightStickRadius) == 0x74FA);
static_assert(offsetof(ACTOR_DATA, leftStickPosition) == 0x7508);
static_assert(offsetof(ACTOR_DATA, leftStickRadius) == 0x750A);
static_assert(offsetof(ACTOR_DATA, actorCameraDirection) == 0x750C);
static_assert(offsetof(ACTOR_DATA, leftStickDirection) == 0x751C);
static_assert(offsetof(ACTOR_DATA, submodelData) == 0x7540);
static_assert(offsetof(ACTOR_DATA, var_9AC0) == 0x9AC0);
static_assert(offsetof(ACTOR_DATA, modelShadowData) == 0x9AD0);
static_assert(offsetof(ACTOR_DATA, submodelShadowData) == 0x9D10);
static_assert(offsetof(ACTOR_DATA, submodelPhysicsMetadata) == 0xA0D0);
static_assert(offsetof(ACTOR_DATA, submodelPhysicsData) == 0xA210);
static_assert(offsetof(ACTOR_DATA, devilModelPhysicsLinkMetadataPool) == 0xA300);
static_assert(offsetof(ACTOR_DATA, devilSubmodelPhysicsData) == 0xA540);
static_assert(offsetof(ACTOR_DATA, devilSubmodelPhysicsLinkData) == 0xAA00);
static_assert(offsetof(ACTOR_DATA, newParentBaseAddr) == 0xB8C0);
static_assert(offsetof(ACTOR_DATA, newChildBaseAddr) == 0xB8D0);
static_assert(offsetof(ACTOR_DATA, newGamepad) == 0xB8D8);
static_assert(offsetof(ACTOR_DATA, newButtonMask) == 0xB8D9);
static_assert(offsetof(ACTOR_DATA, newEnableRightStick) == 0xB8DB);
static_assert(offsetof(ACTOR_DATA, newEnableLeftStick) == 0xB8DC);
static_assert(offsetof(ACTOR_DATA, newMeleeWeapon) == 0xB8E0);
static_assert(offsetof(ACTOR_DATA, newMeleeWeaponData) == 0xB8F0);
static_assert(offsetof(ACTOR_DATA, newMeleeWeaponCount) == 0xB918);
static_assert(offsetof(ACTOR_DATA, newMeleeWeaponIndex) == 0xB919);
static_assert(offsetof(ACTOR_DATA, newLastMeleeWeapon) == 0xB91A);
static_assert(offsetof(ACTOR_DATA, newRangedWeapon) == 0xB920);
static_assert(offsetof(ACTOR_DATA, newRangedWeaponData) == 0xB930);
static_assert(offsetof(ACTOR_DATA, newRangedWeaponCount) == 0xB958);
static_assert(offsetof(ACTOR_DATA, newRangedWeaponIndex) == 0xB959);
static_assert(offsetof(ACTOR_DATA, newLastRangedWeapon) == 0xB95A);
static_assert(offsetof(ACTOR_DATA, newSect) == 0xB960);
static_assert(offsetof(ACTOR_DATA, newBufferedActionPolicy) == 0xB968);
static_assert(offsetof(ACTOR_DATA, newAirStingerCount) == 0xB969);
static_assert(offsetof(ACTOR_DATA, newForceFiles) == 0xB96A);
static_assert(offsetof(ACTOR_DATA, newForceFilesCharacter) == 0xB96B);
static_assert(offsetof(ACTOR_DATA, newDevilAura) == 0xB970);
static_assert(offsetof(ACTOR_DATA, newEffectIndices) == 0xB980);
static_assert(offsetof(ACTOR_DATA, newBodyPartData) == 0xB9A0);
static_assert(offsetof(ACTOR_DATA, newSubmodelData) == 0xC960);
static_assert(offsetof(ACTOR_DATA, newModelShadowData) == 0x11BE0);
static_assert(offsetof(ACTOR_DATA, newSubmodelShadowData) == 0x12060);
static_assert(offsetof(ACTOR_DATA, newSubmodelPhysicsMetadata) == 0x128A0);
static_assert(offsetof(ACTOR_DATA, newSubmodelPhysicsData) == 0x12B20);
static_assert(offsetof(ACTOR_DATA, newDevilSubmodelPhysicsData) == 0x12D00);
static_assert(offsetof(ACTOR_DATA, newLastVar) == 0x13660);

static_assert(offsetof(ACTOR_DATA_DANTE, status) == 8);
static_assert(offsetof(ACTOR_DATA_DANTE, character) == 0x78);
static_assert(offsetof(ACTOR_DATA_DANTE, position) == 0x80);
static_assert(offsetof(ACTOR_DATA_DANTE, pull) == 0x94);
static_assert(offsetof(ACTOR_DATA_DANTE, pullMultiplier) == 0xA4);
static_assert(offsetof(ACTOR_DATA_DANTE, rotation) == 0xC0);
static_assert(offsetof(ACTOR_DATA_DANTE, id) == 0x118);
static_assert(offsetof(ACTOR_DATA_DANTE, isClone) == 0x11C);
static_assert(offsetof(ACTOR_DATA_DANTE, visible) == 0x120);
static_assert(offsetof(ACTOR_DATA_DANTE, var_1C0) == 0x1C0);
static_assert(offsetof(ACTOR_DATA_DANTE, var_1C4) == 0x1C4);
static_assert(offsetof(ACTOR_DATA_DANTE, modelData) == 0x200);
static_assert(offsetof(ACTOR_DATA_DANTE, modelPhysicsMetadataPool) == 0x1880);
static_assert(offsetof(ACTOR_DATA_DANTE, var_3894) == 0x3894);
static_assert(offsetof(ACTOR_DATA_DANTE, motionArchive) == 0x38A0);
static_assert(offsetof(ACTOR_DATA_DANTE, motionData) == 0x39B0);
static_assert(offsetof(ACTOR_DATA_DANTE, motionDataMirror) == 0x39B4);
static_assert(offsetof(ACTOR_DATA_DANTE, var_39BC) == 0x39BC);
static_assert(offsetof(ACTOR_DATA_DANTE, var_39C0) == 0x39C0);
static_assert(offsetof(ACTOR_DATA_DANTE, nextActionRequestPolicy) == 0x39D0);
static_assert(offsetof(ACTOR_DATA_DANTE, var_3A10) == 0x3A10);
static_assert(offsetof(ACTOR_DATA_DANTE, shadow) == 0x3A18);
static_assert(offsetof(ACTOR_DATA_DANTE, color) == 0x3A28);
static_assert(offsetof(ACTOR_DATA_DANTE, actionData) == 0x3DD0);
static_assert(offsetof(ACTOR_DATA_DANTE, eventData) == 0x3E00);
static_assert(offsetof(ACTOR_DATA_DANTE, var_3E10) == 0x3E10);
static_assert(offsetof(ACTOR_DATA_DANTE, motionTimer) == 0x3E34);
static_assert(offsetof(ACTOR_DATA_DANTE, idleTimer) == 0x3E38);
static_assert(offsetof(ACTOR_DATA_DANTE, permissions) == 0x3E60);
static_assert(offsetof(ACTOR_DATA_DANTE, state) == 0x3E64);
static_assert(offsetof(ACTOR_DATA_DANTE, lastState) == 0x3E68);
static_assert(offsetof(ACTOR_DATA_DANTE, activeModelIndex) == 0x3E6C);
static_assert(offsetof(ACTOR_DATA_DANTE, queuedModelIndex) == 0x3E70);
static_assert(offsetof(ACTOR_DATA_DANTE, devilModels) == 0x3E74);
static_assert(offsetof(ACTOR_DATA_DANTE, modelState) == 0x3E80);
static_assert(offsetof(ACTOR_DATA_DANTE, lockOn) == 0x3E84);
static_assert(offsetof(ACTOR_DATA_DANTE, activeModelIndexMirror) == 0x3E88);
static_assert(offsetof(ACTOR_DATA_DANTE, activeDevil) == 0x3E8C);
static_assert(offsetof(ACTOR_DATA_DANTE, airRaid) == 0x3E90);
static_assert(offsetof(ACTOR_DATA_DANTE, mode) == 0x3E94);
static_assert(offsetof(ACTOR_DATA_DANTE, devil) == 0x3E9B);
static_assert(offsetof(ACTOR_DATA_DANTE, costume) == 0x3E9E);
static_assert(offsetof(ACTOR_DATA_DANTE, sparda) == 0x3E9F);
static_assert(offsetof(ACTOR_DATA_DANTE, useHolyWater) == 0x3EA4);
static_assert(offsetof(ACTOR_DATA_DANTE, magicPoints) == 0x3EB8);
static_assert(offsetof(ACTOR_DATA_DANTE, maxMagicPoints) == 0x3EBC);
static_assert(offsetof(ACTOR_DATA_DANTE, var_3ED2) == 0x3ED2);
static_assert(offsetof(ACTOR_DATA_DANTE, cameraDirection) == 0x3ED8);
static_assert(offsetof(ACTOR_DATA_DANTE, airHikeCount) == 0x3F11);
static_assert(offsetof(ACTOR_DATA_DANTE, kickJumpCount) == 0x3F12);
static_assert(offsetof(ACTOR_DATA_DANTE, wallHikeCount) == 0x3F13);
static_assert(offsetof(ACTOR_DATA_DANTE, var_3F19) == 0x3F19);
static_assert(offsetof(ACTOR_DATA_DANTE, action) == 0x3FA4);
static_assert(offsetof(ACTOR_DATA_DANTE, lastAction) == 0x3FA5);
static_assert(offsetof(ACTOR_DATA_DANTE, bufferedAction) == 0x3FA8);
static_assert(offsetof(ACTOR_DATA_DANTE, chainCount) == 0x3FAC);
static_assert(offsetof(ACTOR_DATA_DANTE, expertise) == 0x3FEC);
static_assert(offsetof(ACTOR_DATA_DANTE, maxHitPoints) == 0x40EC);
static_assert(offsetof(ACTOR_DATA_DANTE, hitPoints) == 0x411C);
static_assert(offsetof(ACTOR_DATA_DANTE, targetBaseAddr) == 0x6328);
static_assert(offsetof(ACTOR_DATA_DANTE, style) == 0x6338);
static_assert(offsetof(ACTOR_DATA_DANTE, styleLevel) == 0x6358);
static_assert(offsetof(ACTOR_DATA_DANTE, dashCount) == 0x635C);
static_assert(offsetof(ACTOR_DATA_DANTE, skyStarCount) == 0x635D);
static_assert(offsetof(ACTOR_DATA_DANTE, airTrickCount) == 0x635E);
static_assert(offsetof(ACTOR_DATA_DANTE, quicksilver) == 0x6361);
static_assert(offsetof(ACTOR_DATA_DANTE, doppelganger) == 0x6362);
static_assert(offsetof(ACTOR_DATA_DANTE, styleExperience) == 0x6364);
static_assert(offsetof(ACTOR_DATA_DANTE, cloneIsActive) == 0x6454);
static_assert(offsetof(ACTOR_DATA_DANTE, cloneBaseAddr) == 0x6478);
static_assert(offsetof(ACTOR_DATA_DANTE, cloneIsControlledByPlayer) == 0x6480);
static_assert(offsetof(ACTOR_DATA_DANTE, activeWeapon) == 0x648D);
static_assert(offsetof(ACTOR_DATA_DANTE, meleeWeaponIndex) == 0x6490);
static_assert(offsetof(ACTOR_DATA_DANTE, rangedWeaponIndex) == 0x6494);
static_assert(offsetof(ACTOR_DATA_DANTE, weapons) == 0x6498);
static_assert(offsetof(ACTOR_DATA_DANTE, weaponData) == 0x64A0);
static_assert(offsetof(ACTOR_DATA_DANTE, weaponStatus) == 0x64C8);
static_assert(offsetof(ACTOR_DATA_DANTE, weaponLevels) == 0x64DC);
static_assert(offsetof(ACTOR_DATA_DANTE, activeMeleeWeapon) == 0x64F0);
static_assert(offsetof(ACTOR_DATA_DANTE, activeRangedWeapon) == 0x64F1);
static_assert(offsetof(ACTOR_DATA_DANTE, weaponTimers) == 0x64F4);
static_assert(offsetof(ACTOR_DATA_DANTE, meleeWeaponSwitchTimeout) == 0x6508);
static_assert(offsetof(ACTOR_DATA_DANTE, rangedWeaponSwitchTimeout) == 0x650C);
static_assert(offsetof(ACTOR_DATA_DANTE, styleRank) == 0x6510);
static_assert(offsetof(ACTOR_DATA_DANTE, styleMeter) == 0x6514);
static_assert(offsetof(ACTOR_DATA_DANTE, inputData) == 0x6674);
static_assert(offsetof(ACTOR_DATA_DANTE, bodyPartData) == 0x6950);
static_assert(offsetof(ACTOR_DATA_DANTE, var_7250) == 0x7250);
static_assert(offsetof(ACTOR_DATA_DANTE, collisionIndex) == 0x7254);
static_assert(offsetof(ACTOR_DATA_DANTE, interactionData) == 0x7460);
static_assert(offsetof(ACTOR_DATA_DANTE, buttons) == 0x74E0);
static_assert(offsetof(ACTOR_DATA_DANTE, rightStickPosition) == 0x74F8);
static_assert(offsetof(ACTOR_DATA_DANTE, rightStickRadius) == 0x74FA);
static_assert(offsetof(ACTOR_DATA_DANTE, leftStickPosition) == 0x7508);
static_assert(offsetof(ACTOR_DATA_DANTE, leftStickRadius) == 0x750A);
static_assert(offsetof(ACTOR_DATA_DANTE, actorCameraDirection) == 0x750C);
static_assert(offsetof(ACTOR_DATA_DANTE, leftStickDirection) == 0x751C);
static_assert(offsetof(ACTOR_DATA_DANTE, submodelData) == 0x7540);
static_assert(offsetof(ACTOR_DATA_DANTE, var_9AC0) == 0x9AC0);
static_assert(offsetof(ACTOR_DATA_DANTE, modelShadowData) == 0x9AD0);
static_assert(offsetof(ACTOR_DATA_DANTE, submodelShadowData) == 0x9D10);
static_assert(offsetof(ACTOR_DATA_DANTE, submodelPhysicsMetadata) == 0xA0D0);
static_assert(offsetof(ACTOR_DATA_DANTE, submodelPhysicsData) == 0xA210);
static_assert(offsetof(ACTOR_DATA_DANTE, devilModelPhysicsLinkMetadataPool) == 0xA300);
static_assert(offsetof(ACTOR_DATA_DANTE, devilSubmodelPhysicsData) == 0xA540);
static_assert(offsetof(ACTOR_DATA_DANTE, devilSubmodelPhysicsLinkData) == 0xAA00);
static_assert(offsetof(ACTOR_DATA_DANTE, devilModelMetadata) == 0xB600);
static_assert(offsetof(ACTOR_DATA_DANTE, modelMetadata) == 0xB630);
static_assert(offsetof(ACTOR_DATA_DANTE, artemisChargeValue) == 0xB868);
static_assert(offsetof(ACTOR_DATA_DANTE, artemisChargeFlags) == 0xB87C);
static_assert(offsetof(ACTOR_DATA_DANTE, newParentBaseAddr) == 0xB8C0);
static_assert(offsetof(ACTOR_DATA_DANTE, newChildBaseAddr) == 0xB8D0);
static_assert(offsetof(ACTOR_DATA_DANTE, newGamepad) == 0xB8D8);
static_assert(offsetof(ACTOR_DATA_DANTE, newButtonMask) == 0xB8D9);
static_assert(offsetof(ACTOR_DATA_DANTE, newEnableRightStick) == 0xB8DB);
static_assert(offsetof(ACTOR_DATA_DANTE, newEnableLeftStick) == 0xB8DC);
static_assert(offsetof(ACTOR_DATA_DANTE, newMeleeWeapon) == 0xB8E0);
static_assert(offsetof(ACTOR_DATA_DANTE, newMeleeWeaponData) == 0xB8F0);
static_assert(offsetof(ACTOR_DATA_DANTE, newMeleeWeaponCount) == 0xB918);
static_assert(offsetof(ACTOR_DATA_DANTE, newMeleeWeaponIndex) == 0xB919);
static_assert(offsetof(ACTOR_DATA_DANTE, newLastMeleeWeapon) == 0xB91A);
static_assert(offsetof(ACTOR_DATA_DANTE, newRangedWeapon) == 0xB920);
static_assert(offsetof(ACTOR_DATA_DANTE, newRangedWeaponData) == 0xB930);
static_assert(offsetof(ACTOR_DATA_DANTE, newRangedWeaponCount) == 0xB958);
static_assert(offsetof(ACTOR_DATA_DANTE, newRangedWeaponIndex) == 0xB959);
static_assert(offsetof(ACTOR_DATA_DANTE, newLastRangedWeapon) == 0xB95A);
static_assert(offsetof(ACTOR_DATA_DANTE, newSect) == 0xB960);
static_assert(offsetof(ACTOR_DATA_DANTE, newBufferedActionPolicy) == 0xB968);
static_assert(offsetof(ACTOR_DATA_DANTE, newAirStingerCount) == 0xB969);
static_assert(offsetof(ACTOR_DATA_DANTE, newForceFiles) == 0xB96A);
static_assert(offsetof(ACTOR_DATA_DANTE, newForceFilesCharacter) == 0xB96B);
static_assert(offsetof(ACTOR_DATA_DANTE, newDevilAura) == 0xB970);
static_assert(offsetof(ACTOR_DATA_DANTE, newEffectIndices) == 0xB980);
static_assert(offsetof(ACTOR_DATA_DANTE, newBodyPartData) == 0xB9A0);
static_assert(offsetof(ACTOR_DATA_DANTE, newSubmodelData) == 0xC960);
static_assert(offsetof(ACTOR_DATA_DANTE, newModelShadowData) == 0x11BE0);
static_assert(offsetof(ACTOR_DATA_DANTE, newSubmodelShadowData) == 0x12060);
static_assert(offsetof(ACTOR_DATA_DANTE, newSubmodelPhysicsMetadata) == 0x128A0);
static_assert(offsetof(ACTOR_DATA_DANTE, newSubmodelPhysicsData) == 0x12B20);
static_assert(offsetof(ACTOR_DATA_DANTE, newDevilSubmodelPhysicsData) == 0x12D00);
static_assert(offsetof(ACTOR_DATA_DANTE, newLastVar) == 0x13660);

static_assert(offsetof(ACTOR_DATA_BOB, status) == 8);
static_assert(offsetof(ACTOR_DATA_BOB, character) == 0x78);
static_assert(offsetof(ACTOR_DATA_BOB, position) == 0x80);
static_assert(offsetof(ACTOR_DATA_BOB, pull) == 0x94);
static_assert(offsetof(ACTOR_DATA_BOB, pullMultiplier) == 0xA4);
static_assert(offsetof(ACTOR_DATA_BOB, rotation) == 0xC0);
static_assert(offsetof(ACTOR_DATA_BOB, id) == 0x118);
static_assert(offsetof(ACTOR_DATA_BOB, isClone) == 0x11C);
static_assert(offsetof(ACTOR_DATA_BOB, visible) == 0x120);
static_assert(offsetof(ACTOR_DATA_BOB, var_1C0) == 0x1C0);
static_assert(offsetof(ACTOR_DATA_BOB, var_1C4) == 0x1C4);
static_assert(offsetof(ACTOR_DATA_BOB, modelData) == 0x200);
static_assert(offsetof(ACTOR_DATA_BOB, modelPhysicsMetadataPool) == 0x1880);
static_assert(offsetof(ACTOR_DATA_BOB, var_3894) == 0x3894);
static_assert(offsetof(ACTOR_DATA_BOB, motionArchive) == 0x38A0);
static_assert(offsetof(ACTOR_DATA_BOB, motionData) == 0x39B0);
static_assert(offsetof(ACTOR_DATA_BOB, motionDataMirror) == 0x39B4);
static_assert(offsetof(ACTOR_DATA_BOB, var_39BC) == 0x39BC);
static_assert(offsetof(ACTOR_DATA_BOB, var_39C0) == 0x39C0);
static_assert(offsetof(ACTOR_DATA_BOB, nextActionRequestPolicy) == 0x39D0);
static_assert(offsetof(ACTOR_DATA_BOB, var_3A10) == 0x3A10);
static_assert(offsetof(ACTOR_DATA_BOB, shadow) == 0x3A18);
static_assert(offsetof(ACTOR_DATA_BOB, color) == 0x3A28);
static_assert(offsetof(ACTOR_DATA_BOB, actionData) == 0x3DD0);
static_assert(offsetof(ACTOR_DATA_BOB, eventData) == 0x3E00);
static_assert(offsetof(ACTOR_DATA_BOB, var_3E10) == 0x3E10);
static_assert(offsetof(ACTOR_DATA_BOB, motionTimer) == 0x3E34);
static_assert(offsetof(ACTOR_DATA_BOB, idleTimer) == 0x3E38);
static_assert(offsetof(ACTOR_DATA_BOB, permissions) == 0x3E60);
static_assert(offsetof(ACTOR_DATA_BOB, state) == 0x3E64);
static_assert(offsetof(ACTOR_DATA_BOB, lastState) == 0x3E68);
static_assert(offsetof(ACTOR_DATA_BOB, activeModelIndex) == 0x3E6C);
static_assert(offsetof(ACTOR_DATA_BOB, queuedModelIndex) == 0x3E70);
static_assert(offsetof(ACTOR_DATA_BOB, devilModels) == 0x3E74);
static_assert(offsetof(ACTOR_DATA_BOB, modelState) == 0x3E80);
static_assert(offsetof(ACTOR_DATA_BOB, lockOn) == 0x3E84);
static_assert(offsetof(ACTOR_DATA_BOB, activeModelIndexMirror) == 0x3E88);
static_assert(offsetof(ACTOR_DATA_BOB, activeDevil) == 0x3E8C);
static_assert(offsetof(ACTOR_DATA_BOB, airRaid) == 0x3E90);
static_assert(offsetof(ACTOR_DATA_BOB, mode) == 0x3E94);
static_assert(offsetof(ACTOR_DATA_BOB, devil) == 0x3E9B);
static_assert(offsetof(ACTOR_DATA_BOB, costume) == 0x3E9E);
static_assert(offsetof(ACTOR_DATA_BOB, useHolyWater) == 0x3EA4);
static_assert(offsetof(ACTOR_DATA_BOB, magicPoints) == 0x3EB8);
static_assert(offsetof(ACTOR_DATA_BOB, maxMagicPoints) == 0x3EBC);
static_assert(offsetof(ACTOR_DATA_BOB, var_3ED2) == 0x3ED2);
static_assert(offsetof(ACTOR_DATA_BOB, cameraDirection) == 0x3ED8);
static_assert(offsetof(ACTOR_DATA_BOB, airHikeCount) == 0x3F11);
static_assert(offsetof(ACTOR_DATA_BOB, kickJumpCount) == 0x3F12);
static_assert(offsetof(ACTOR_DATA_BOB, wallHikeCount) == 0x3F13);
static_assert(offsetof(ACTOR_DATA_BOB, var_3F19) == 0x3F19);
static_assert(offsetof(ACTOR_DATA_BOB, action) == 0x3FA4);
static_assert(offsetof(ACTOR_DATA_BOB, lastAction) == 0x3FA5);
static_assert(offsetof(ACTOR_DATA_BOB, bufferedAction) == 0x3FA8);
static_assert(offsetof(ACTOR_DATA_BOB, chainCount) == 0x3FAC);
static_assert(offsetof(ACTOR_DATA_BOB, expertise) == 0x3FEC);
static_assert(offsetof(ACTOR_DATA_BOB, maxHitPoints) == 0x40EC);
static_assert(offsetof(ACTOR_DATA_BOB, hitPoints) == 0x411C);
static_assert(offsetof(ACTOR_DATA_BOB, targetBaseAddr) == 0x6328);
static_assert(offsetof(ACTOR_DATA_BOB, style) == 0x6338);
static_assert(offsetof(ACTOR_DATA_BOB, styleLevel) == 0x6358);
static_assert(offsetof(ACTOR_DATA_BOB, styleExperience) == 0x6364);
static_assert(offsetof(ACTOR_DATA_BOB, cloneIsActive) == 0x6454);
static_assert(offsetof(ACTOR_DATA_BOB, cloneBaseAddr) == 0x6478);
static_assert(offsetof(ACTOR_DATA_BOB, cloneIsControlledByPlayer) == 0x6480);
static_assert(offsetof(ACTOR_DATA_BOB, weapons) == 0x6498);
static_assert(offsetof(ACTOR_DATA_BOB, weaponData) == 0x64A0);
static_assert(offsetof(ACTOR_DATA_BOB, weaponStatus) == 0x64C8);
static_assert(offsetof(ACTOR_DATA_BOB, weaponLevels) == 0x64DC);
static_assert(offsetof(ACTOR_DATA_BOB, weaponTimers) == 0x64F4);
static_assert(offsetof(ACTOR_DATA_BOB, styleRank) == 0x6510);
static_assert(offsetof(ACTOR_DATA_BOB, styleMeter) == 0x6514);
static_assert(offsetof(ACTOR_DATA_BOB, inputData) == 0x6674);
static_assert(offsetof(ACTOR_DATA_BOB, bodyPartData) == 0x6950);
static_assert(offsetof(ACTOR_DATA_BOB, var_7250) == 0x7250);
static_assert(offsetof(ACTOR_DATA_BOB, collisionIndex) == 0x7254);
static_assert(offsetof(ACTOR_DATA_BOB, interactionData) == 0x7460);
static_assert(offsetof(ACTOR_DATA_BOB, buttons) == 0x74E0);
static_assert(offsetof(ACTOR_DATA_BOB, rightStickPosition) == 0x74F8);
static_assert(offsetof(ACTOR_DATA_BOB, rightStickRadius) == 0x74FA);
static_assert(offsetof(ACTOR_DATA_BOB, leftStickPosition) == 0x7508);
static_assert(offsetof(ACTOR_DATA_BOB, leftStickRadius) == 0x750A);
static_assert(offsetof(ACTOR_DATA_BOB, actorCameraDirection) == 0x750C);
static_assert(offsetof(ACTOR_DATA_BOB, leftStickDirection) == 0x751C);
static_assert(offsetof(ACTOR_DATA_BOB, submodelData) == 0x7540);
static_assert(offsetof(ACTOR_DATA_BOB, var_9AC0) == 0x9AC0);
static_assert(offsetof(ACTOR_DATA_BOB, modelShadowData) == 0x9AD0);
static_assert(offsetof(ACTOR_DATA_BOB, submodelShadowData) == 0x9D10);
static_assert(offsetof(ACTOR_DATA_BOB, submodelPhysicsMetadata) == 0xA0D0);
static_assert(offsetof(ACTOR_DATA_BOB, submodelPhysicsData) == 0xA210);
static_assert(offsetof(ACTOR_DATA_BOB, devilModelPhysicsLinkMetadataPool) == 0xA300);
static_assert(offsetof(ACTOR_DATA_BOB, devilSubmodelPhysicsData) == 0xA540);
static_assert(offsetof(ACTOR_DATA_BOB, devilSubmodelPhysicsLinkData) == 0xAA00);
static_assert(offsetof(ACTOR_DATA_BOB, newParentBaseAddr) == 0xB8C0);
static_assert(offsetof(ACTOR_DATA_BOB, newChildBaseAddr) == 0xB8D0);
static_assert(offsetof(ACTOR_DATA_BOB, newGamepad) == 0xB8D8);
static_assert(offsetof(ACTOR_DATA_BOB, newButtonMask) == 0xB8D9);
static_assert(offsetof(ACTOR_DATA_BOB, newEnableRightStick) == 0xB8DB);
static_assert(offsetof(ACTOR_DATA_BOB, newEnableLeftStick) == 0xB8DC);
static_assert(offsetof(ACTOR_DATA_BOB, newMeleeWeapon) == 0xB8E0);
static_assert(offsetof(ACTOR_DATA_BOB, newMeleeWeaponData) == 0xB8F0);
static_assert(offsetof(ACTOR_DATA_BOB, newMeleeWeaponCount) == 0xB918);
static_assert(offsetof(ACTOR_DATA_BOB, newMeleeWeaponIndex) == 0xB919);
static_assert(offsetof(ACTOR_DATA_BOB, newLastMeleeWeapon) == 0xB91A);
static_assert(offsetof(ACTOR_DATA_BOB, newRangedWeapon) == 0xB920);
static_assert(offsetof(ACTOR_DATA_BOB, newRangedWeaponData) == 0xB930);
static_assert(offsetof(ACTOR_DATA_BOB, newRangedWeaponCount) == 0xB958);
static_assert(offsetof(ACTOR_DATA_BOB, newRangedWeaponIndex) == 0xB959);
static_assert(offsetof(ACTOR_DATA_BOB, newLastRangedWeapon) == 0xB95A);
static_assert(offsetof(ACTOR_DATA_BOB, newSect) == 0xB960);
static_assert(offsetof(ACTOR_DATA_BOB, newBufferedActionPolicy) == 0xB968);
static_assert(offsetof(ACTOR_DATA_BOB, newAirStingerCount) == 0xB969);
static_assert(offsetof(ACTOR_DATA_BOB, newForceFiles) == 0xB96A);
static_assert(offsetof(ACTOR_DATA_BOB, newForceFilesCharacter) == 0xB96B);
static_assert(offsetof(ACTOR_DATA_BOB, newDevilAura) == 0xB970);
static_assert(offsetof(ACTOR_DATA_BOB, newEffectIndices) == 0xB980);
static_assert(offsetof(ACTOR_DATA_BOB, newBodyPartData) == 0xB9A0);
static_assert(offsetof(ACTOR_DATA_BOB, newSubmodelData) == 0xC960);
static_assert(offsetof(ACTOR_DATA_BOB, newModelShadowData) == 0x11BE0);
static_assert(offsetof(ACTOR_DATA_BOB, newSubmodelShadowData) == 0x12060);
static_assert(offsetof(ACTOR_DATA_BOB, newSubmodelPhysicsMetadata) == 0x128A0);
static_assert(offsetof(ACTOR_DATA_BOB, newSubmodelPhysicsData) == 0x12B20);
static_assert(offsetof(ACTOR_DATA_BOB, newDevilSubmodelPhysicsData) == 0x12D00);
static_assert(offsetof(ACTOR_DATA_BOB, newLastVar) == 0x13660);

static_assert(offsetof(ACTOR_DATA_LADY, status) == 8);
static_assert(offsetof(ACTOR_DATA_LADY, character) == 0x78);
static_assert(offsetof(ACTOR_DATA_LADY, position) == 0x80);
static_assert(offsetof(ACTOR_DATA_LADY, pull) == 0x94);
static_assert(offsetof(ACTOR_DATA_LADY, pullMultiplier) == 0xA4);
static_assert(offsetof(ACTOR_DATA_LADY, rotation) == 0xC0);
static_assert(offsetof(ACTOR_DATA_LADY, id) == 0x118);
static_assert(offsetof(ACTOR_DATA_LADY, isClone) == 0x11C);
static_assert(offsetof(ACTOR_DATA_LADY, visible) == 0x120);
static_assert(offsetof(ACTOR_DATA_LADY, var_1C0) == 0x1C0);
static_assert(offsetof(ACTOR_DATA_LADY, var_1C4) == 0x1C4);
static_assert(offsetof(ACTOR_DATA_LADY, modelData) == 0x200);
static_assert(offsetof(ACTOR_DATA_LADY, modelPhysicsMetadataPool) == 0x1880);
static_assert(offsetof(ACTOR_DATA_LADY, var_3894) == 0x3894);
static_assert(offsetof(ACTOR_DATA_LADY, motionArchive) == 0x38A0);
static_assert(offsetof(ACTOR_DATA_LADY, motionData) == 0x39B0);
static_assert(offsetof(ACTOR_DATA_LADY, motionDataMirror) == 0x39B4);
static_assert(offsetof(ACTOR_DATA_LADY, var_39BC) == 0x39BC);
static_assert(offsetof(ACTOR_DATA_LADY, var_39C0) == 0x39C0);
static_assert(offsetof(ACTOR_DATA_LADY, nextActionRequestPolicy) == 0x39D0);
static_assert(offsetof(ACTOR_DATA_LADY, var_3A10) == 0x3A10);
static_assert(offsetof(ACTOR_DATA_LADY, shadow) == 0x3A18);
static_assert(offsetof(ACTOR_DATA_LADY, color) == 0x3A28);
static_assert(offsetof(ACTOR_DATA_LADY, actionData) == 0x3DD0);
static_assert(offsetof(ACTOR_DATA_LADY, eventData) == 0x3E00);
static_assert(offsetof(ACTOR_DATA_LADY, var_3E10) == 0x3E10);
static_assert(offsetof(ACTOR_DATA_LADY, motionTimer) == 0x3E34);
static_assert(offsetof(ACTOR_DATA_LADY, idleTimer) == 0x3E38);
static_assert(offsetof(ACTOR_DATA_LADY, permissions) == 0x3E60);
static_assert(offsetof(ACTOR_DATA_LADY, state) == 0x3E64);
static_assert(offsetof(ACTOR_DATA_LADY, lastState) == 0x3E68);
static_assert(offsetof(ACTOR_DATA_LADY, activeModelIndex) == 0x3E6C);
static_assert(offsetof(ACTOR_DATA_LADY, queuedModelIndex) == 0x3E70);
static_assert(offsetof(ACTOR_DATA_LADY, devilModels) == 0x3E74);
static_assert(offsetof(ACTOR_DATA_LADY, modelState) == 0x3E80);
static_assert(offsetof(ACTOR_DATA_LADY, lockOn) == 0x3E84);
static_assert(offsetof(ACTOR_DATA_LADY, activeModelIndexMirror) == 0x3E88);
static_assert(offsetof(ACTOR_DATA_LADY, activeDevil) == 0x3E8C);
static_assert(offsetof(ACTOR_DATA_LADY, airRaid) == 0x3E90);
static_assert(offsetof(ACTOR_DATA_LADY, mode) == 0x3E94);
static_assert(offsetof(ACTOR_DATA_LADY, devil) == 0x3E9B);
static_assert(offsetof(ACTOR_DATA_LADY, costume) == 0x3E9E);
static_assert(offsetof(ACTOR_DATA_LADY, useHolyWater) == 0x3EA4);
static_assert(offsetof(ACTOR_DATA_LADY, magicPoints) == 0x3EB8);
static_assert(offsetof(ACTOR_DATA_LADY, maxMagicPoints) == 0x3EBC);
static_assert(offsetof(ACTOR_DATA_LADY, var_3ED2) == 0x3ED2);
static_assert(offsetof(ACTOR_DATA_LADY, cameraDirection) == 0x3ED8);
static_assert(offsetof(ACTOR_DATA_LADY, airHikeCount) == 0x3F11);
static_assert(offsetof(ACTOR_DATA_LADY, kickJumpCount) == 0x3F12);
static_assert(offsetof(ACTOR_DATA_LADY, wallHikeCount) == 0x3F13);
static_assert(offsetof(ACTOR_DATA_LADY, var_3F19) == 0x3F19);
static_assert(offsetof(ACTOR_DATA_LADY, action) == 0x3FA4);
static_assert(offsetof(ACTOR_DATA_LADY, lastAction) == 0x3FA5);
static_assert(offsetof(ACTOR_DATA_LADY, bufferedAction) == 0x3FA8);
static_assert(offsetof(ACTOR_DATA_LADY, chainCount) == 0x3FAC);
static_assert(offsetof(ACTOR_DATA_LADY, expertise) == 0x3FEC);
static_assert(offsetof(ACTOR_DATA_LADY, maxHitPoints) == 0x40EC);
static_assert(offsetof(ACTOR_DATA_LADY, hitPoints) == 0x411C);
static_assert(offsetof(ACTOR_DATA_LADY, targetBaseAddr) == 0x6328);
static_assert(offsetof(ACTOR_DATA_LADY, style) == 0x6338);
static_assert(offsetof(ACTOR_DATA_LADY, styleLevel) == 0x6358);
static_assert(offsetof(ACTOR_DATA_LADY, styleExperience) == 0x6364);
static_assert(offsetof(ACTOR_DATA_LADY, cloneIsActive) == 0x6454);
static_assert(offsetof(ACTOR_DATA_LADY, cloneBaseAddr) == 0x6478);
static_assert(offsetof(ACTOR_DATA_LADY, cloneIsControlledByPlayer) == 0x6480);
static_assert(offsetof(ACTOR_DATA_LADY, weapons) == 0x6498);
static_assert(offsetof(ACTOR_DATA_LADY, weaponData) == 0x64A0);
static_assert(offsetof(ACTOR_DATA_LADY, weaponStatus) == 0x64C8);
static_assert(offsetof(ACTOR_DATA_LADY, weaponLevels) == 0x64DC);
static_assert(offsetof(ACTOR_DATA_LADY, weaponTimers) == 0x64F4);
static_assert(offsetof(ACTOR_DATA_LADY, styleRank) == 0x6510);
static_assert(offsetof(ACTOR_DATA_LADY, styleMeter) == 0x6514);
static_assert(offsetof(ACTOR_DATA_LADY, inputData) == 0x6674);
static_assert(offsetof(ACTOR_DATA_LADY, bodyPartData) == 0x6950);
static_assert(offsetof(ACTOR_DATA_LADY, var_7250) == 0x7250);
static_assert(offsetof(ACTOR_DATA_LADY, collisionIndex) == 0x7254);
static_assert(offsetof(ACTOR_DATA_LADY, interactionData) == 0x7460);
static_assert(offsetof(ACTOR_DATA_LADY, buttons) == 0x74E0);
static_assert(offsetof(ACTOR_DATA_LADY, rightStickPosition) == 0x74F8);
static_assert(offsetof(ACTOR_DATA_LADY, rightStickRadius) == 0x74FA);
static_assert(offsetof(ACTOR_DATA_LADY, leftStickPosition) == 0x7508);
static_assert(offsetof(ACTOR_DATA_LADY, leftStickRadius) == 0x750A);
static_assert(offsetof(ACTOR_DATA_LADY, actorCameraDirection) == 0x750C);
static_assert(offsetof(ACTOR_DATA_LADY, leftStickDirection) == 0x751C);
static_assert(offsetof(ACTOR_DATA_LADY, submodelData) == 0x7540);
static_assert(offsetof(ACTOR_DATA_LADY, var_9AC0) == 0x9AC0);
static_assert(offsetof(ACTOR_DATA_LADY, modelShadowData) == 0x9AD0);
static_assert(offsetof(ACTOR_DATA_LADY, submodelShadowData) == 0x9D10);
static_assert(offsetof(ACTOR_DATA_LADY, submodelPhysicsMetadata) == 0xA0D0);
static_assert(offsetof(ACTOR_DATA_LADY, submodelPhysicsData) == 0xA210);
static_assert(offsetof(ACTOR_DATA_LADY, devilModelPhysicsLinkMetadataPool) == 0xA300);
static_assert(offsetof(ACTOR_DATA_LADY, devilSubmodelPhysicsData) == 0xA540);
static_assert(offsetof(ACTOR_DATA_LADY, devilSubmodelPhysicsLinkData) == 0xAA00);
static_assert(offsetof(ACTOR_DATA_LADY, newParentBaseAddr) == 0xB8C0);
static_assert(offsetof(ACTOR_DATA_LADY, newChildBaseAddr) == 0xB8D0);
static_assert(offsetof(ACTOR_DATA_LADY, newGamepad) == 0xB8D8);
static_assert(offsetof(ACTOR_DATA_LADY, newButtonMask) == 0xB8D9);
static_assert(offsetof(ACTOR_DATA_LADY, newEnableRightStick) == 0xB8DB);
static_assert(offsetof(ACTOR_DATA_LADY, newEnableLeftStick) == 0xB8DC);
static_assert(offsetof(ACTOR_DATA_LADY, newMeleeWeapon) == 0xB8E0);
static_assert(offsetof(ACTOR_DATA_LADY, newMeleeWeaponData) == 0xB8F0);
static_assert(offsetof(ACTOR_DATA_LADY, newMeleeWeaponCount) == 0xB918);
static_assert(offsetof(ACTOR_DATA_LADY, newMeleeWeaponIndex) == 0xB919);
static_assert(offsetof(ACTOR_DATA_LADY, newLastMeleeWeapon) == 0xB91A);
static_assert(offsetof(ACTOR_DATA_LADY, newRangedWeapon) == 0xB920);
static_assert(offsetof(ACTOR_DATA_LADY, newRangedWeaponData) == 0xB930);
static_assert(offsetof(ACTOR_DATA_LADY, newRangedWeaponCount) == 0xB958);
static_assert(offsetof(ACTOR_DATA_LADY, newRangedWeaponIndex) == 0xB959);
static_assert(offsetof(ACTOR_DATA_LADY, newLastRangedWeapon) == 0xB95A);
static_assert(offsetof(ACTOR_DATA_LADY, newSect) == 0xB960);
static_assert(offsetof(ACTOR_DATA_LADY, newBufferedActionPolicy) == 0xB968);
static_assert(offsetof(ACTOR_DATA_LADY, newAirStingerCount) == 0xB969);
static_assert(offsetof(ACTOR_DATA_LADY, newForceFiles) == 0xB96A);
static_assert(offsetof(ACTOR_DATA_LADY, newForceFilesCharacter) == 0xB96B);
static_assert(offsetof(ACTOR_DATA_LADY, newDevilAura) == 0xB970);
static_assert(offsetof(ACTOR_DATA_LADY, newEffectIndices) == 0xB980);
static_assert(offsetof(ACTOR_DATA_LADY, newBodyPartData) == 0xB9A0);
static_assert(offsetof(ACTOR_DATA_LADY, newSubmodelData) == 0xC960);
static_assert(offsetof(ACTOR_DATA_LADY, newModelShadowData) == 0x11BE0);
static_assert(offsetof(ACTOR_DATA_LADY, newSubmodelShadowData) == 0x12060);
static_assert(offsetof(ACTOR_DATA_LADY, newSubmodelPhysicsMetadata) == 0x128A0);
static_assert(offsetof(ACTOR_DATA_LADY, newSubmodelPhysicsData) == 0x12B20);
static_assert(offsetof(ACTOR_DATA_LADY, newDevilSubmodelPhysicsData) == 0x12D00);
static_assert(offsetof(ACTOR_DATA_LADY, newLastVar) == 0x13660);

static_assert(offsetof(ACTOR_DATA_VERGIL, status) == 8);
static_assert(offsetof(ACTOR_DATA_VERGIL, character) == 0x78);
static_assert(offsetof(ACTOR_DATA_VERGIL, position) == 0x80);
static_assert(offsetof(ACTOR_DATA_VERGIL, pull) == 0x94);
static_assert(offsetof(ACTOR_DATA_VERGIL, pullMultiplier) == 0xA4);
static_assert(offsetof(ACTOR_DATA_VERGIL, rotation) == 0xC0);
static_assert(offsetof(ACTOR_DATA_VERGIL, id) == 0x118);
static_assert(offsetof(ACTOR_DATA_VERGIL, isClone) == 0x11C);
static_assert(offsetof(ACTOR_DATA_VERGIL, visible) == 0x120);
static_assert(offsetof(ACTOR_DATA_VERGIL, var_1C0) == 0x1C0);
static_assert(offsetof(ACTOR_DATA_VERGIL, var_1C4) == 0x1C4);
static_assert(offsetof(ACTOR_DATA_VERGIL, modelData) == 0x200);
static_assert(offsetof(ACTOR_DATA_VERGIL, modelPhysicsMetadataPool) == 0x1880);
static_assert(offsetof(ACTOR_DATA_VERGIL, var_3894) == 0x3894);
static_assert(offsetof(ACTOR_DATA_VERGIL, motionArchive) == 0x38A0);
static_assert(offsetof(ACTOR_DATA_VERGIL, motionData) == 0x39B0);
static_assert(offsetof(ACTOR_DATA_VERGIL, motionDataMirror) == 0x39B4);
static_assert(offsetof(ACTOR_DATA_VERGIL, var_39BC) == 0x39BC);
static_assert(offsetof(ACTOR_DATA_VERGIL, var_39C0) == 0x39C0);
static_assert(offsetof(ACTOR_DATA_VERGIL, nextActionRequestPolicy) == 0x39D0);
static_assert(offsetof(ACTOR_DATA_VERGIL, var_3A10) == 0x3A10);
static_assert(offsetof(ACTOR_DATA_VERGIL, shadow) == 0x3A18);
static_assert(offsetof(ACTOR_DATA_VERGIL, color) == 0x3A28);
static_assert(offsetof(ACTOR_DATA_VERGIL, actionData) == 0x3DD0);
static_assert(offsetof(ACTOR_DATA_VERGIL, eventData) == 0x3E00);
static_assert(offsetof(ACTOR_DATA_VERGIL, var_3E10) == 0x3E10);
static_assert(offsetof(ACTOR_DATA_VERGIL, motionTimer) == 0x3E34);
static_assert(offsetof(ACTOR_DATA_VERGIL, idleTimer) == 0x3E38);
static_assert(offsetof(ACTOR_DATA_VERGIL, permissions) == 0x3E60);
static_assert(offsetof(ACTOR_DATA_VERGIL, state) == 0x3E64);
static_assert(offsetof(ACTOR_DATA_VERGIL, lastState) == 0x3E68);
static_assert(offsetof(ACTOR_DATA_VERGIL, activeModelIndex) == 0x3E6C);
static_assert(offsetof(ACTOR_DATA_VERGIL, queuedModelIndex) == 0x3E70);
static_assert(offsetof(ACTOR_DATA_VERGIL, devilModels) == 0x3E74);
static_assert(offsetof(ACTOR_DATA_VERGIL, modelState) == 0x3E80);
static_assert(offsetof(ACTOR_DATA_VERGIL, lockOn) == 0x3E84);
static_assert(offsetof(ACTOR_DATA_VERGIL, activeModelIndexMirror) == 0x3E88);
static_assert(offsetof(ACTOR_DATA_VERGIL, activeDevil) == 0x3E8C);
static_assert(offsetof(ACTOR_DATA_VERGIL, airRaid) == 0x3E90);
static_assert(offsetof(ACTOR_DATA_VERGIL, mode) == 0x3E94);
static_assert(offsetof(ACTOR_DATA_VERGIL, devil) == 0x3E9B);
static_assert(offsetof(ACTOR_DATA_VERGIL, costume) == 0x3E9E);
static_assert(offsetof(ACTOR_DATA_VERGIL, neroAngelo) == 0x3E9F);
static_assert(offsetof(ACTOR_DATA_VERGIL, useHolyWater) == 0x3EA4);
static_assert(offsetof(ACTOR_DATA_VERGIL, magicPoints) == 0x3EB8);
static_assert(offsetof(ACTOR_DATA_VERGIL, maxMagicPoints) == 0x3EBC);
static_assert(offsetof(ACTOR_DATA_VERGIL, var_3ED2) == 0x3ED2);
static_assert(offsetof(ACTOR_DATA_VERGIL, cameraDirection) == 0x3ED8);
static_assert(offsetof(ACTOR_DATA_VERGIL, airHikeCount) == 0x3F11);
static_assert(offsetof(ACTOR_DATA_VERGIL, kickJumpCount) == 0x3F12);
static_assert(offsetof(ACTOR_DATA_VERGIL, wallHikeCount) == 0x3F13);
static_assert(offsetof(ACTOR_DATA_VERGIL, var_3F19) == 0x3F19);
static_assert(offsetof(ACTOR_DATA_VERGIL, action) == 0x3FA4);
static_assert(offsetof(ACTOR_DATA_VERGIL, lastAction) == 0x3FA5);
static_assert(offsetof(ACTOR_DATA_VERGIL, bufferedAction) == 0x3FA8);
static_assert(offsetof(ACTOR_DATA_VERGIL, chainCount) == 0x3FAC);
static_assert(offsetof(ACTOR_DATA_VERGIL, expertise) == 0x3FEC);
static_assert(offsetof(ACTOR_DATA_VERGIL, maxHitPoints) == 0x40EC);
static_assert(offsetof(ACTOR_DATA_VERGIL, hitPoints) == 0x411C);
static_assert(offsetof(ACTOR_DATA_VERGIL, targetBaseAddr) == 0x6328);
static_assert(offsetof(ACTOR_DATA_VERGIL, style) == 0x6338);
static_assert(offsetof(ACTOR_DATA_VERGIL, styleLevel) == 0x6358);
static_assert(offsetof(ACTOR_DATA_VERGIL, airTrickCount) == 0x635E);
static_assert(offsetof(ACTOR_DATA_VERGIL, trickUpCount) == 0x635F);
static_assert(offsetof(ACTOR_DATA_VERGIL, trickDownCount) == 0x6360);
static_assert(offsetof(ACTOR_DATA_VERGIL, styleExperience) == 0x6364);
static_assert(offsetof(ACTOR_DATA_VERGIL, cloneIsActive) == 0x6454);
static_assert(offsetof(ACTOR_DATA_VERGIL, cloneBaseAddr) == 0x6478);
static_assert(offsetof(ACTOR_DATA_VERGIL, cloneIsControlledByPlayer) == 0x6480);
static_assert(offsetof(ACTOR_DATA_VERGIL, activeMeleeWeaponIndex) == 0x6484);
static_assert(offsetof(ACTOR_DATA_VERGIL, queuedMeleeWeaponIndex) == 0x6488);
static_assert(offsetof(ACTOR_DATA_VERGIL, weapons) == 0x6498);
static_assert(offsetof(ACTOR_DATA_VERGIL, weaponData) == 0x64A0);
static_assert(offsetof(ACTOR_DATA_VERGIL, weaponStatus) == 0x64C8);
static_assert(offsetof(ACTOR_DATA_VERGIL, weaponLevels) == 0x64DC);
static_assert(offsetof(ACTOR_DATA_VERGIL, weaponTimers) == 0x64F4);
static_assert(offsetof(ACTOR_DATA_VERGIL, meleeWeaponSwitchForwardTimeout) == 0x6508);
static_assert(offsetof(ACTOR_DATA_VERGIL, meleeWeaponSwitchBackTimeout) == 0x650C);
static_assert(offsetof(ACTOR_DATA_VERGIL, styleRank) == 0x6510);
static_assert(offsetof(ACTOR_DATA_VERGIL, styleMeter) == 0x6514);
static_assert(offsetof(ACTOR_DATA_VERGIL, inputData) == 0x6674);
static_assert(offsetof(ACTOR_DATA_VERGIL, bodyPartData) == 0x6950);
static_assert(offsetof(ACTOR_DATA_VERGIL, var_7250) == 0x7250);
static_assert(offsetof(ACTOR_DATA_VERGIL, collisionIndex) == 0x7254);
static_assert(offsetof(ACTOR_DATA_VERGIL, interactionData) == 0x7460);
static_assert(offsetof(ACTOR_DATA_VERGIL, buttons) == 0x74E0);
static_assert(offsetof(ACTOR_DATA_VERGIL, rightStickPosition) == 0x74F8);
static_assert(offsetof(ACTOR_DATA_VERGIL, rightStickRadius) == 0x74FA);
static_assert(offsetof(ACTOR_DATA_VERGIL, leftStickPosition) == 0x7508);
static_assert(offsetof(ACTOR_DATA_VERGIL, leftStickRadius) == 0x750A);
static_assert(offsetof(ACTOR_DATA_VERGIL, actorCameraDirection) == 0x750C);
static_assert(offsetof(ACTOR_DATA_VERGIL, leftStickDirection) == 0x751C);
static_assert(offsetof(ACTOR_DATA_VERGIL, submodelData) == 0x7540);
static_assert(offsetof(ACTOR_DATA_VERGIL, var_9AC0) == 0x9AC0);
static_assert(offsetof(ACTOR_DATA_VERGIL, modelShadowData) == 0x9AD0);
static_assert(offsetof(ACTOR_DATA_VERGIL, submodelShadowData) == 0x9D10);
static_assert(offsetof(ACTOR_DATA_VERGIL, submodelPhysicsMetadata) == 0xA0D0);
static_assert(offsetof(ACTOR_DATA_VERGIL, submodelPhysicsData) == 0xA210);
static_assert(offsetof(ACTOR_DATA_VERGIL, devilModelPhysicsLinkMetadataPool) == 0xA300);
static_assert(offsetof(ACTOR_DATA_VERGIL, devilSubmodelPhysicsData) == 0xA540);
static_assert(offsetof(ACTOR_DATA_VERGIL, devilSubmodelPhysicsLinkData) == 0xAA00);
static_assert(offsetof(ACTOR_DATA_VERGIL, newParentBaseAddr) == 0xB8C0);
static_assert(offsetof(ACTOR_DATA_VERGIL, newChildBaseAddr) == 0xB8D0);
static_assert(offsetof(ACTOR_DATA_VERGIL, newGamepad) == 0xB8D8);
static_assert(offsetof(ACTOR_DATA_VERGIL, newButtonMask) == 0xB8D9);
static_assert(offsetof(ACTOR_DATA_VERGIL, newEnableRightStick) == 0xB8DB);
static_assert(offsetof(ACTOR_DATA_VERGIL, newEnableLeftStick) == 0xB8DC);
static_assert(offsetof(ACTOR_DATA_VERGIL, newMeleeWeapon) == 0xB8E0);
static_assert(offsetof(ACTOR_DATA_VERGIL, newMeleeWeaponData) == 0xB8F0);
static_assert(offsetof(ACTOR_DATA_VERGIL, newMeleeWeaponCount) == 0xB918);
static_assert(offsetof(ACTOR_DATA_VERGIL, newMeleeWeaponIndex) == 0xB919);
static_assert(offsetof(ACTOR_DATA_VERGIL, newLastMeleeWeapon) == 0xB91A);
static_assert(offsetof(ACTOR_DATA_VERGIL, newRangedWeapon) == 0xB920);
static_assert(offsetof(ACTOR_DATA_VERGIL, newRangedWeaponData) == 0xB930);
static_assert(offsetof(ACTOR_DATA_VERGIL, newRangedWeaponCount) == 0xB958);
static_assert(offsetof(ACTOR_DATA_VERGIL, newRangedWeaponIndex) == 0xB959);
static_assert(offsetof(ACTOR_DATA_VERGIL, newLastRangedWeapon) == 0xB95A);
static_assert(offsetof(ACTOR_DATA_VERGIL, newSect) == 0xB960);
static_assert(offsetof(ACTOR_DATA_VERGIL, newBufferedActionPolicy) == 0xB968);
static_assert(offsetof(ACTOR_DATA_VERGIL, newAirStingerCount) == 0xB969);
static_assert(offsetof(ACTOR_DATA_VERGIL, newForceFiles) == 0xB96A);
static_assert(offsetof(ACTOR_DATA_VERGIL, newForceFilesCharacter) == 0xB96B);
static_assert(offsetof(ACTOR_DATA_VERGIL, newDevilAura) == 0xB970);
static_assert(offsetof(ACTOR_DATA_VERGIL, newEffectIndices) == 0xB980);
static_assert(offsetof(ACTOR_DATA_VERGIL, newBodyPartData) == 0xB9A0);
static_assert(offsetof(ACTOR_DATA_VERGIL, newSubmodelData) == 0xC960);
static_assert(offsetof(ACTOR_DATA_VERGIL, newModelShadowData) == 0x11BE0);
static_assert(offsetof(ACTOR_DATA_VERGIL, newSubmodelShadowData) == 0x12060);
static_assert(offsetof(ACTOR_DATA_VERGIL, newSubmodelPhysicsMetadata) == 0x128A0);
static_assert(offsetof(ACTOR_DATA_VERGIL, newSubmodelPhysicsData) == 0x12B20);
static_assert(offsetof(ACTOR_DATA_VERGIL, newDevilSubmodelPhysicsData) == 0x12D00);
static_assert(offsetof(ACTOR_DATA_VERGIL, newLastVar) == 0x13660);

// $ActorDataEnd

#pragma pack(pop)

#undef _




struct MotionArchiveHelper
{
	uint8 group;
	uint16 cacheFileId;
};

constexpr MotionArchiveHelper motionArchiveHelperDante[] =
{
	{ MOTION_GROUP_DANTE_BASE                  , pl000_00_0  },
	{ MOTION_GROUP_DANTE_DAMAGE                , pl000_00_1  },
	{ MOTION_GROUP_DANTE_TAUNTS                , pl000_00_2  },
	{ MOTION_GROUP_DANTE_REBELLION             , pl000_00_3  },
	{ MOTION_GROUP_DANTE_CERBERUS              , pl000_00_4  },
	{ MOTION_GROUP_DANTE_AGNI_RUDRA            , pl000_00_5  },
	{ MOTION_GROUP_DANTE_NEVAN                 , pl000_00_6  },
	{ MOTION_GROUP_DANTE_BEOWULF               , pl000_00_7  },
	{ MOTION_GROUP_DANTE_EBONY_IVORY           , pl000_00_8  },
	{ MOTION_GROUP_DANTE_SHOTGUN               , pl000_00_9  },
	{ MOTION_GROUP_DANTE_ARTEMIS               , pl000_00_10 },
	{ MOTION_GROUP_DANTE_SPIRAL                , pl000_00_11 },
	{ MOTION_GROUP_DANTE_KALINA_ANN            , pl000_00_12 },
	{ MOTION_GROUP_DANTE_SWORDMASTER_REBELLION , pl000_00_13 },
	{ MOTION_GROUP_DANTE_SWORDMASTER_CERBERUS  , pl000_00_14 },
	{ MOTION_GROUP_DANTE_SWORDMASTER_AGNI_RUDRA, pl000_00_15 },
	{ MOTION_GROUP_DANTE_SWORDMASTER_NEVAN     , pl000_00_16 },
	{ MOTION_GROUP_DANTE_SWORDMASTER_BEOWULF   , pl000_00_17 },
	{ MOTION_GROUP_DANTE_GUNSLINGER_EBONY_IVORY, pl000_00_18 },
	{ MOTION_GROUP_DANTE_GUNSLINGER_SHOTGUN    , pl000_00_19 },
	{ MOTION_GROUP_DANTE_GUNSLINGER_ARTEMIS    , pl000_00_20 },
	{ MOTION_GROUP_DANTE_GUNSLINGER_SPIRAL     , pl000_00_21 },
	{ MOTION_GROUP_DANTE_GUNSLINGER_KALINA_ANN , pl000_00_22 },
	{ MOTION_GROUP_DANTE_TRICKSTER             , pl000_00_23 },
	{ MOTION_GROUP_DANTE_ROYALGUARD            , pl000_00_24 },
	{ MOTION_GROUP_DANTE_QUICKSILVER           , pl000_00_25 },
	{ MOTION_GROUP_DANTE_DOPPELGANGER          , pl000_00_26 },
};

constexpr MotionArchiveHelper motionArchiveHelperBob[] =
{
	{ MOTION_GROUP_BOB_BASE       , pl001_00_0  },
	{ MOTION_GROUP_BOB_DAMAGE     , pl001_00_1  },
	{ MOTION_GROUP_BOB_TAUNTS     , pl001_00_2  },
	{ MOTION_GROUP_BOB_MELEE_STYLE, pl001_00_31 },
};

constexpr MotionArchiveHelper motionArchiveHelperLady[] =
{
	{ MOTION_GROUP_LADY_BASE      , pl002_00_0  },
	{ MOTION_GROUP_LADY_DAMAGE    , pl002_00_1  },
	{ MOTION_GROUP_LADY_TAUNTS    , pl002_00_2  },
	{ MOTION_GROUP_LADY_KALINA_ANN, pl000_00_12 },
};

constexpr MotionArchiveHelper motionArchiveHelperVergil[] =
{
	{ MOTION_GROUP_VERGIL_BASE                  , pl021_00_0 },
	{ MOTION_GROUP_VERGIL_DAMAGE                , pl021_00_1 },
	{ MOTION_GROUP_VERGIL_TAUNTS                , pl021_00_2 },
	{ MOTION_GROUP_VERGIL_YAMATO                , pl021_00_3 },
	{ MOTION_GROUP_VERGIL_BEOWULF               , pl021_00_4 },
	{ MOTION_GROUP_VERGIL_FORCE_EDGE            , pl021_00_5 },
	{ MOTION_GROUP_VERGIL_DARK_SLAYER           , pl021_00_6 },
	{ MOTION_GROUP_VERGIL_NERO_ANGELO_YAMATO    , pl021_00_7 },
	{ MOTION_GROUP_VERGIL_NERO_ANGELO_BEOWULF   , pl021_00_8 },
	{ MOTION_GROUP_VERGIL_NERO_ANGELO_FORCE_EDGE, pl021_00_9 },
};




struct MissionStartHelper
{
	uint16 room;
	uint16 position;
};

constexpr MissionStartHelper missionStartHelper[] =
{
	{ 0  , 0 }, // Movie
	{ 0  , 0 }, // Mission 1
	{ 1  , 0 }, // Mission 2
	{ 2  , 0 }, // Mission 3
	{ 100, 0 }, // Mission 4
	{ 111, 2 }, // Mission 5
	{ 122, 0 }, // Mission 6
	{ 127, 2 }, // Mission 7
	{ 300, 0 }, // Mission 8
	{ 201, 0 }, // Mission 9
	{ 209, 2 }, // Mission 10
	{ 212, 1 }, // Mission 11
	{ 217, 1 }, // Mission 12
	{ 229, 0 }, // Mission 13
	{ 237, 1 }, // Mission 14
	{ 222, 1 }, // Mission 15
	{ 106, 0 }, // Mission 16
	{ 133, 1 }, // Mission 17
	{ 400, 0 }, // Mission 18
	{ 406, 0 }, // Mission 19
	{ 411, 0 }, // Mission 20
	{ 423, 0 }, // Bloody Palace
};




















struct FloorHelper
{
	uint16 room;
	uint16 position;
};

constexpr FloorHelper Arcade_floorHelper[] =
{
	{ 423, 0 }, // Floor 1
	{ 424, 0 }, // Floor 2
	{ 425, 0 }, // Floor 3
	{ 426, 0 }, // Floor 4
	{ 427, 0 }, // Floor 5
	{ 428, 0 }, // Floor 6
	{ 429, 0 }, // Floor 7
	{ 430, 0 }, // Floor 8
	{ 431, 0 }, // Floor 9
	{ 432, 0 }, // Floor 10
	{ 433, 0 }, // Cerberus
	{ 434, 0 }, // Gigapede
	{ 435, 0 }, // Agni & Rudra
	{ 436, 0 }, // Nevan
	{ 437, 0 }, // Beowulf
	{ 438, 2 }, // Geryon
	{ 439, 0 }, // Doppelganger
	{ 440, 0 }, // Heart of Leviathan
	{ 441, 0 }, // Damned Chessmen
	{ 442, 0 }, // Vergil 1
	{ 443, 0 }, // Vergil 2
	{ 444, 0 }, // Vergil 3
	{ 445, 2 }, // Lady
	{ 446, 0 }, // Arkham
	{ 422, 0 }, // Jester 1
	{ 448, 0 }, // Jester 2
	{ 449, 0 }, // Jester 3
};










enum BOSS
{
	BOSS_CERBERUS,
	BOSS_GIGAPEDE,
	BOSS_JESTER_1,
	BOSS_AGNI_RUDRA,
	BOSS_VERGIL_1,
	BOSS_LEVIATHAN,
	BOSS_NEVAN,
	BOSS_BEOWULF,
	BOSS_JESTER_2,
	BOSS_GERYON_PART_1,
	BOSS_GERYON_PART_2,
	BOSS_VERGIL_2,
	BOSS_LADY,
	BOSS_JESTER_3,
	BOSS_DOPPELGANGER,
	BOSS_TAIZAI_REBORN,
	BOSS_CERBERUS_REBORN,
	BOSS_GIGAPEDE_REBORN,
	BOSS_AGNI_RUDRA_REBORN,
	BOSS_LEVIATHAN_REBORN,
	BOSS_NEVAN_REBORN,
	BOSS_BEOWULF_REBORN,
	BOSS_GERYON_REBORN,
	BOSS_DOPPELGANGER_REBORN,
	BOSS_ARKHAM_PART_1,
	BOSS_ARKHAM_PART_2,
	BOSS_VERGIL_3,
};

struct BossHelper
{
	uint16 room;
	uint16 position;
	const char * track;
};

constexpr BossHelper bossHelper[] =
{
	{ 6  , 2, "afs/sound/Boss_01.adx"    }, // Cerberus
	{ 111, 0, "afs/sound/T_Boss.adx"     }, // Gigapede
	{ 422, 0, "afs/sound/Jester.adx"     }, // Jester 1
	{ 121, 3, "afs/sound/Boss_02.adx"    }, // Agni & Rudra
	{ 144, 0, "afs/sound/Versil_01.adx"  }, // Vergil 1
	{ 302, 0, "afs/sound/Boss_08.adx"    }, // Leviathan
	{ 210, 2, "afs/sound/Boss_03.adx"    }, // Nevan
	{ 217, 2, "afs/sound/Boss_04.adx"    }, // Beowulf
	{ 448, 0, "afs/sound/Jester.adx"     }, // Jester 2
	{ 228, 0, "afs/sound/Boss_05.adx"    }, // Geryon Part 1
	{ 228, 2, "afs/sound/Boss_05.adx"    }, // Geryon Part 2
	{ 234, 0, "afs/sound/Versil_02.adx"  }, // Vergil 2
	{ 115, 2, "afs/sound/Lady.adx"       }, // Lady
	{ 449, 0, "afs/sound/Jester.adx"     }, // Jester 3
	{ 139, 0, "afs/sound/Boss_06.adx"    }, // Doppelganger
	{ 420, 0, "afs/sound/Battle_01B.adx" }, // Taizai Reborn
	{ 412, 0, "afs/sound/Boss_01B.adx"   }, // Cerberus Reborn
	{ 413, 0, "afs/sound/T_BossB.adx"    }, // Gigapede Reborn
	{ 414, 0, "afs/sound/Boss_02B.adx"   }, // Agni & Rudra Reborn
	{ 419, 0, "afs/sound/Boss_08B.adx"   }, // Leviathan Reborn
	{ 415, 0, "afs/sound/Boss_03B.adx"   }, // Nevan Reborn
	{ 416, 0, "afs/sound/Boss_04B.adx"   }, // Beowulf Reborn
	{ 417, 0, "afs/sound/Boss_05B.adx"   }, // Geryon Reborn
	{ 418, 0, "afs/sound/Boss_06B.adx"   }, // Doppelganger Reborn
	{ 421, 0, "afs/sound/Hine_01.adx"    }, // Arkham Part 1
	{ 421, 0, "afs/sound/Hine_02.adx"    }, // Arkham Part 2
	{ 411, 0, "afs/sound/Versil_03.adx"  }, // Vergil 3
};












#ifdef __GARBAGE__
#endif
