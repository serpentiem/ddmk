

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

enum DEVIL
{
	DEVIL_REBELLION,
	DEVIL_CERBERUS,
	DEVIL_AGNI_RUDRA,
	DEVIL_NEVAN,
	DEVIL_BEOWULF,
	DEVIL_SPARDA,
	DEVIL_NERO_ANGELO,
	DEVIL_YAMATO = 0,
	MAX_DEVIL = 7,
};

enum STYLE_
{
	STYLE_SWORDMASTER,
	STYLE_GUNSLINGER,
	STYLE_TRICKSTER,
	STYLE_ROYALGUARD,
	STYLE_QUICKSILVER,
	STYLE_DOPPELGANGER,
	STYLE_DARK_SLAYER = 2,
	MAX_STYLE = 6,
	//STYLE_VOID = 255,
};

enum WEAPON
{
	WEAPON_REBELLION,
	WEAPON_CERBERUS,
	WEAPON_AGNI_RUDRA,
	WEAPON_NEVAN,
	WEAPON_BEOWULF_DANTE,
	WEAPON_EBONY_IVORY,
	WEAPON_SHOTGUN,
	WEAPON_ARTEMIS,
	WEAPON_SPIRAL,
	WEAPON_KALINA_ANN,
	WEAPON_YAMATO_VERGIL = 11,
	WEAPON_BEOWULF_VERGIL,
	WEAPON_FORCE_EDGE,
	WEAPON_YAMATO_BOB,
	MAX_WEAPON,
	WEAPON_VOID = 255,
};

enum WEAPON_COUNT
{
	WEAPON_COUNT_DANTE = 10,
	WEAPON_COUNT_VERGIL = 3,
	MELEE_WEAPON_COUNT = 5,
	MELEE_WEAPON_COUNT_DANTE = 5,
	MELEE_WEAPON_COUNT_VERGIL = 3,
	RANGED_WEAPON_COUNT = 5,
	RANGED_WEAPON_COUNT_DANTE = 5,
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




enum HUD_TOP
{
	HUD_TOP_UPPER_HIT_POINTS_FRAME,
	HUD_TOP_UPPER_HIT_POINTS_BAR,
	HUD_TOP_UPPER_HIT_POINTS_BACKGROUND,
	HUD_TOP_LOWER_HIT_POINTS_FRAME,
	HUD_TOP_LOWER_HIT_POINTS_BAR,
	HUD_TOP_LOWER_HIT_POINTS_BACKGROUND,
	HUD_TOP_MAGIC_ORBS,
	HUD_TOP_STYLE_ICON,
	HUD_TOP_RED_ORB_COUNTER,
	HUD_TOP_UNKNOWN_1,
	HUD_TOP_UNKNOWN_2,
	HUD_TOP_FLUX,
	HUD_TOP_UNKNOWN_3,
};

enum HUD_BOTTOM
{
	HUD_BOTTOM_RANGED_WEAPON_1,
	HUD_BOTTOM_RANGED_WEAPON_2,
	HUD_BOTTOM_MELEE_WEAPON_1,
	HUD_BOTTOM_MELEE_WEAPON_2,
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
	SCENE_BOOT,
	SCENE_INTRO,
	SCENE_MAIN,
	SCENE_MISSION_SELECT,
	SCENE_LOAD,
	SCENE_GAME,
	SCENE_CUTSCENE,
	SCENE_MISSION_START,
	SCENE_MISSION_RESULT,
	SCENE_GAME_OVER,
	MAX_SCENE,
};

enum EVENT
{
	EVENT_INIT,
	EVENT_MAIN,
	EVENT_TELEPORT,
	EVENT_PAUSE,
	EVENT_STATUS,
	EVENT_OPTIONS,
	EVENT_DEATH,
	EVENT_GET_ITEM,
	EVENT_MESSAGE,
	EVENT_CUSTOMIZE,
	EVENT_SAVE,
	EVENT_DELETE,
	EVENT_END,
	MAX_EVENT,
};

enum SUBEVENT
{
	SUBEVENT_MISSION_START  = 7,
	SUBEVENT_MISSION_SELECT = 8,
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








struct ActorEventData
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

struct EventData
{
	_(24);
	uint32 room;
	uint32 position;
	uint32 event;
	_(8);
	uint32 subevent;
};

struct NextEventData
{
	_(356);
	uint16 room;
	uint16 position;
};

struct StagePositionData
{
	uint8 event;
	_(3);
	float32 x;
	float32 y;
	float32 z;
	float32 rotation;
	_(28);
};











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
auto & cameraData = *reinterpret_cast<CAMERA_DATA *>(name[147])
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










// $MissionActorDataStart

struct QueuedMissionActorData
{
	uint8 weapons[5]; // 0
	_(75);
	float32 hitPoints; // 0x50
	float32 magicPoints; // 0x54
	uint32 style; // 0x58
	uint32 styleLevel[6]; // 0x5C
	float32 styleExperience[6]; // 0x74
	byte32 expertise[8]; // 0x8C
};

static_assert(offsetof(QueuedMissionActorData, weapons) == 0);
static_assert(offsetof(QueuedMissionActorData, hitPoints) == 0x50);
static_assert(offsetof(QueuedMissionActorData, magicPoints) == 0x54);
static_assert(offsetof(QueuedMissionActorData, style) == 0x58);
static_assert(offsetof(QueuedMissionActorData, styleLevel) == 0x5C);
static_assert(offsetof(QueuedMissionActorData, styleExperience) == 0x74);
static_assert(offsetof(QueuedMissionActorData, expertise) == 0x8C);

struct ActiveMissionActorData
{
	_(80);
	float32 hitPoints; // 0x50
	float32 magicPoints; // 0x54
	uint32 style; // 0x58
	uint32 styleLevel[6]; // 0x5C
	float32 styleExperience[6]; // 0x74
	byte32 expertise[8]; // 0x8C
};

static_assert(offsetof(ActiveMissionActorData, hitPoints) == 0x50);
static_assert(offsetof(ActiveMissionActorData, magicPoints) == 0x54);
static_assert(offsetof(ActiveMissionActorData, style) == 0x58);
static_assert(offsetof(ActiveMissionActorData, styleLevel) == 0x5C);
static_assert(offsetof(ActiveMissionActorData, styleExperience) == 0x74);
static_assert(offsetof(ActiveMissionActorData, expertise) == 0x8C);

// $MissionActorDataEnd

#define _IntroduceMissionActorData(name, ...)\
auto name = *reinterpret_cast<byte8 **>(appBaseAddr + 0xC90E30);\
if (!name)\
{\
	__VA_ARGS__;\
}\
auto & queuedMissionActorData = *reinterpret_cast<QueuedMissionActorData *>(name + 0xC0 );\
auto & activeMissionActorData = *reinterpret_cast<ActiveMissionActorData *>(name + 0x16C)
#define IntroduceMissionActorData(...) _IntroduceMissionActorData(Prep_Merge(pool_, __LINE__), __VA_ARGS__)












// #define _IntroduceMissionActorDataPointers(name, ...)\
// auto name = *reinterpret_cast<byte8 **>(appBaseAddr + 0xC90E30);\
// if (!name)\
// {\
// 	__VA_ARGS__;\
// }\
// auto missionActorData_C0  = reinterpret_cast<byte8 *>(name + 0xC0 );\
// auto missionActorData_16C = reinterpret_cast<byte8 *>(name + 0x16C)
// #define IntroduceMissionActorDataPointers(...) _IntroduceMissionActorDataPointers(Prep_Merge(pool_, __LINE__), __VA_ARGS__)







#define IntroduceSessionData() auto & sessionData = *reinterpret_cast<SESSION_DATA *>(appBaseAddr + 0xC8F250)

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
auto stagePositionData = *reinterpret_cast<StagePositionData **>(name[8] + 0x2CB0);\
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











enum FILE_STATUS
{
	FILE_STATUS_READY = 3,
};

enum FILE_MODE
{
	FILE_MODE_MEMORY,
	FILE_MODE_ARCHIVE,
	FILE_MODE_LOCAL,
};




struct ArchiveData
{
	byte8 signature[4];
	uint32 fileCount;
	uint32 fileOff[128];
};

struct StringData
{
	_(8);
	const char * string;
};

struct FileData
{
	uint32 category;
	uint32 status;
	uint16 id;
	_(6);
	void * callback;
	StringData * stringData;
	byte8 * file;
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
















struct MotionData
{
	uint8 index;
	uint8 group;
};









struct InputData
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








struct PhysicsMetadata
{
	_(256);
	PhysicsLinkData * physicsLinkData;
	vec4 * vertices;
	PhysicsData * physicsData;
	_(40);
};

static_assert(offsetof(PhysicsMetadata, physicsLinkData) == 0x100);
static_assert(offsetof(PhysicsMetadata, vertices) == 0x108);
static_assert(offsetof(PhysicsMetadata, physicsData) == 0x110);
static_assert(sizeof(PhysicsMetadata) == 0x140);































//struct PhysicsLinkMetadata
//{
//	_(256);
//	PhysicsLinkData * devilPhysicsData;
//};

//static_assert(offsetof(PhysicsLinkMetadata, devilPhysicsData) == 0x100);
















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
		case DEVIL_REBELLION:
		{
			return Rebellion;
		}
		case DEVIL_CERBERUS:
		{
			return *reinterpret_cast<DevilModelMetadata2 *>(&Cerberus);
		}
		case DEVIL_AGNI_RUDRA:
		{
			return *reinterpret_cast<DevilModelMetadata2 *>(&AgniRudra);
		}
		case DEVIL_NEVAN:
		{
			return Nevan;
		}
		case DEVIL_BEOWULF:
		{
			return *reinterpret_cast<DevilModelMetadata2 *>(&Beowulf);
		}
		case DEVIL_SPARDA:
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



constexpr uint16 devilFileIdsDante[6] =
{
	pl005,
	pl006,
	pl007,
	pl008,
	pl009,
	pl017,
};






constexpr uint8 weaponDevilIds[MAX_WEAPON] =
{
	DEVIL_REBELLION,
	DEVIL_CERBERUS,
	DEVIL_AGNI_RUDRA,
	DEVIL_NEVAN,
	DEVIL_BEOWULF,
	0,
	0,
	0,
	0,
	0,
	0,
	DEVIL_YAMATO,
	DEVIL_BEOWULF,
	DEVIL_YAMATO,
	DEVIL_YAMATO,
};







constexpr uint32 hudTopOffs[] =
{
	0x700,
	0xE80,
	0x1600,
	0x1D80,
	0x2500,
	0x2C80,
	0x3400,
	0x3B80,
	0x4300,
	0x4A80,
	0x5200,
	0x5980,
	0x6100,
};

constexpr uint32 hudBottomOffs[] =
{
	0x880,
	0x1000,
	0x1780,
	0x1F00,
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
	_(8);
	byte8 ** functions;
	_(8);
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
		_(244);
		bool init;
		_(35);
		float32 timer[2];
		_(196);
	}
	Motion;
};

static_assert(offsetof(ModelData, functions) == 8);
static_assert(offsetof(ModelData, visible) == 0x18);
static_assert(offsetof(ModelData, physics) == 0x19);
static_assert(offsetof(ModelData, Motion) == 0x500);
static_assert(offsetof(ModelData, Motion.duration1) == 0x554);
static_assert(offsetof(ModelData, Motion.duration2) == 0x594);
static_assert(offsetof(ModelData, Motion.init) == 0x690);
static_assert(offsetof(ModelData, Motion.timer) == 0x6B4);
static_assert(sizeof(ModelData) == 0x780);






struct RecoveryData
{
	byte8 ** functions;
	_(24);
	bool init;
	_(15);
	vec4 data[4];
};

static_assert(offsetof(RecoveryData, init) == 0x20);
static_assert(offsetof(RecoveryData, data) == 0x30);
static_assert(sizeof(RecoveryData) == 0x70);














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


IntroduceSizeStruct(32);
IntroduceSizeStruct(112);
IntroduceSizeStruct(192);
IntroduceSizeStruct(240);
IntroduceSizeStruct(288);
IntroduceSizeStruct(768);



struct WeaponData
{
	_(274);
	uint8 weapon;
	_(5);
	uint8 value;
	_(7);
	byte8 * actorBaseAddr;
};

static_assert(offsetof(WeaponData, weapon) == 0x112);
static_assert(offsetof(WeaponData, value) == 0x118);
static_assert(offsetof(WeaponData, actorBaseAddr) == 0x120);



enum ACTOR_DATA_SIZE
{
	ACTOR_DATA_SIZE_DANTE  = 47296,
	ACTOR_DATA_SIZE_BOB    = 46720,
	ACTOR_DATA_SIZE_LADY   = 33408,
	ACTOR_DATA_SIZE_VERGIL = 47296,
};




struct PlayerData
{
	uint8 character;
	uint8 costume;
	bool forceFiles;
	uint8 forceFilesCharacter;
	uint8 style;
	uint8 meleeWeapons[MELEE_WEAPON_COUNT];
	uint8 meleeWeaponCount;
	uint8 meleeWeaponIndex;
	uint8 rangedWeapons[RANGED_WEAPON_COUNT];
	uint8 rangedWeaponCount;
	uint8 rangedWeaponIndex;
};



//constexpr uint64 playerDataSize = sizeof(PlayerData);





// $ActorDataStart

struct ActorData
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
	PhysicsMetadata * modelPhysicsMetadataPool[4][24]; // 0x1880
	uint32 modelAllocationDataCount; // 0x1B80
	_(4);
	Size_32 modelAllocationData[209]; // 0x1B88
	_(748);
	float32 motionSpeed; // 0x3894
	float32 motionSpeedMultiplier; // 0x3898
	_(4);
	byte8 * motionArchives[32]; // 0x38A0
	_(16);
	MotionData motionData[2]; // 0x39B0
	MotionData motionDataMirror[3]; // 0x39B4
	_(2);
	uint32 var_39BC; // 0x39BC
	uint8 var_39C0[16]; // 0x39C0
	uint32 nextActionRequestPolicy[16]; // 0x39D0
	uint8 var_3A10[8]; // 0x3A10
	uint32 shadow; // 0x3A18
	uint32 lastShadow; // 0x3A1C
	_(8);
	byte32 color; // 0x3A28
	_(212);
	RecoveryData recoveryData[3]; // 0x3B00
	byte8 var_3C50[2]; // 0x3C50
	_(382);
	byte8 * actionData[6]; // 0x3DD0
	ActorEventData eventData[2]; // 0x3E00
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
	_(4);
	float32 var_3EC4; // 0x3EC4
	float32 var_3EC8; // 0x3EC8
	_(6);
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
	_(4);
	uint32 var_6340; // 0x6340
	_(20);
	uint32 styleLevel; // 0x6358
	_(5);
	bool quicksilver; // 0x6361
	bool doppelganger; // 0x6362
	_(1);
	float32 styleExperience; // 0x6364
	_(168);
	byte8 var_6410[40]; // 0x6410
	byte8 * var_6438; // 0x6438
	uint32 var_6440; // 0x6440
	_(12);
	uint32 cloneRate; // 0x6450
	uint32 var_6454; // 0x6454
	byte8 var_6458[32]; // 0x6458
	byte8 * cloneBaseAddr; // 0x6478
	bool cloneIsControlledByPlayer; // 0x6480
	_(23);
	uint8 weapons[5]; // 0x6498
	_(3);
	WeaponData * weaponData[5]; // 0x64A0
	uint32 weaponStatus[5]; // 0x64C8
	uint32 weaponLevels[5]; // 0x64DC
	_(4);
	float32 weaponTimers[5]; // 0x64F4
	float32 meleeWeaponSwitchTimeout; // 0x6508
	float32 rangedWeaponSwitchTimeout; // 0x650C
	uint32 styleRank; // 0x6510
	float32 styleMeter; // 0x6514
	_(348);
	InputData inputData[58]; // 0x6674
	_(36);
	BodyPartData bodyPartData[3][2]; // 0x6950
	_(576);
	byte8 var_7250[4]; // 0x7250
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
	bool submodelInit[5]; // 0x9AC0
	_(7675);
	uint32 newFirstVar; // 0xB8C0
	_(12);
	ModelData newModelData[6]; // 0xB8D0
	PhysicsMetadata * newModelPhysicsMetadataPool[7][24]; // 0xE5D0
	Size_32 newModelAllocationData[512]; // 0xEB10
	RecoveryData newRecoveryData[6]; // 0x12B10
	uint32 newDevilModels[6]; // 0x12DB0
	_(8);
	BodyPartData newBodyPartData[7][2]; // 0x12DD0
	ModelData newSubmodelData[11]; // 0x13D90
	bool newSubmodelInit[11]; // 0x19010
	_(5);
	ShadowData newModelShadowData[6]; // 0x19020
	ShadowData newSubmodelShadowData[11]; // 0x194A0
	PhysicsMetadata * newDevilModelPhysicsMetadataPool[5][36]; // 0x19CE0
	PhysicsData newDevilSubmodelPhysicsData[10]; // 0x1A280
	PhysicsLinkData newDevilSubmodelPhysicsLinkData[10][4]; // 0x1ABE0
	uint8 newWeapons[10]; // 0x1C9E0
	_(6);
	WeaponData * newWeaponData[10]; // 0x1C9F0
	uint32 newWeaponStatus[10]; // 0x1CA40
	_(8);
	uint32 newWeaponLevels[10]; // 0x1CA70
	_(8);
	float32 newWeaponTimers[10]; // 0x1CAA0
	bool32 newIsClone; // 0x1CAC8
	uint8 newPlayer; // 0x1CACC
	uint8 newEntity; // 0x1CACD
	bool newForceFiles; // 0x1CACE
	uint8 newForceFilesCharacter; // 0x1CACF
	uint8 newGamepad; // 0x1CAD0
	byte16 newButtonMask; // 0x1CAD1
	bool newEnableRightStick; // 0x1CAD3
	bool newEnableLeftStick; // 0x1CAD4
	bool newExecuteStyleSwitch; // 0x1CAD5
	bool newEnable; // 0x1CAD6
	uint8 newAirStingerCount; // 0x1CAD7
	_(8);
	byte32 newEffectIndices[8]; // 0x1CAE0
	uint32 newLastVar; // 0x1CB00

	operator byte8 *()
	{
		return reinterpret_cast<byte8 *>(this);
	}
};

struct ActorDataDante
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
	PhysicsMetadata * modelPhysicsMetadataPool[4][24]; // 0x1880
	uint32 modelAllocationDataCount; // 0x1B80
	_(4);
	Size_32 modelAllocationData[209]; // 0x1B88
	_(748);
	float32 motionSpeed; // 0x3894
	float32 motionSpeedMultiplier; // 0x3898
	_(4);
	byte8 * motionArchives[32]; // 0x38A0
	_(16);
	MotionData motionData[2]; // 0x39B0
	MotionData motionDataMirror[3]; // 0x39B4
	_(2);
	uint32 var_39BC; // 0x39BC
	uint8 var_39C0[16]; // 0x39C0
	uint32 nextActionRequestPolicy[16]; // 0x39D0
	uint8 var_3A10[8]; // 0x3A10
	uint32 shadow; // 0x3A18
	uint32 lastShadow; // 0x3A1C
	_(8);
	byte32 color; // 0x3A28
	_(212);
	RecoveryData recoveryData[3]; // 0x3B00
	byte8 var_3C50[2]; // 0x3C50
	_(382);
	byte8 * actionData[6]; // 0x3DD0
	ActorEventData eventData[2]; // 0x3E00
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
	_(4);
	float32 var_3EC4; // 0x3EC4
	float32 var_3EC8; // 0x3EC8
	_(6);
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
	_(4);
	uint32 var_6340; // 0x6340
	_(20);
	uint32 styleLevel; // 0x6358
	uint8 dashCount; // 0x635C
	uint8 skyStarCount; // 0x635D
	uint8 airTrickCount; // 0x635E
	_(2);
	bool quicksilver; // 0x6361
	bool doppelganger; // 0x6362
	_(1);
	float32 styleExperience; // 0x6364
	_(168);
	byte8 var_6410[40]; // 0x6410
	byte8 * var_6438; // 0x6438
	uint32 var_6440; // 0x6440
	_(12);
	uint32 cloneRate; // 0x6450
	uint32 var_6454; // 0x6454
	byte8 var_6458[32]; // 0x6458
	byte8 * cloneBaseAddr; // 0x6478
	bool cloneIsControlledByPlayer; // 0x6480
	_(12);
	uint8 activeWeapon; // 0x648D
	_(2);
	uint32 meleeWeaponIndex; // 0x6490
	uint32 rangedWeaponIndex; // 0x6494
	uint8 weapons[5]; // 0x6498
	_(3);
	WeaponData * weaponData[5]; // 0x64A0
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
	InputData inputData[58]; // 0x6674
	_(36);
	BodyPartData bodyPartData[3][2]; // 0x6950
	_(576);
	byte8 var_7250[4]; // 0x7250
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
	bool submodelInit[5]; // 0x9AC0
	_(11);
	ShadowData modelShadowData[3]; // 0x9AD0
	ShadowData submodelShadowData[5]; // 0x9D10
	PhysicsMetadata * submodelPhysicsMetadataPool[39]; // 0xA0D0
	_(8);
	PhysicsData submodelPhysicsData; // 0xA210
	PhysicsMetadata * devilModelPhysicsMetadataPool[2][36]; // 0xA300
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
	uint32 newFirstVar; // 0xB8C0
	_(12);
	ModelData newModelData[6]; // 0xB8D0
	PhysicsMetadata * newModelPhysicsMetadataPool[7][24]; // 0xE5D0
	Size_32 newModelAllocationData[512]; // 0xEB10
	RecoveryData newRecoveryData[6]; // 0x12B10
	uint32 newDevilModels[6]; // 0x12DB0
	_(8);
	BodyPartData newBodyPartData[7][2]; // 0x12DD0
	ModelData newSubmodelData[11]; // 0x13D90
	bool newSubmodelInit[11]; // 0x19010
	_(5);
	ShadowData newModelShadowData[6]; // 0x19020
	ShadowData newSubmodelShadowData[11]; // 0x194A0
	PhysicsMetadata * newDevilModelPhysicsMetadataPool[5][36]; // 0x19CE0
	PhysicsData newDevilSubmodelPhysicsData[10]; // 0x1A280
	PhysicsLinkData newDevilSubmodelPhysicsLinkData[10][4]; // 0x1ABE0
	uint8 newWeapons[10]; // 0x1C9E0
	_(6);
	WeaponData * newWeaponData[10]; // 0x1C9F0
	uint32 newWeaponStatus[10]; // 0x1CA40
	_(8);
	uint32 newWeaponLevels[10]; // 0x1CA70
	_(8);
	float32 newWeaponTimers[10]; // 0x1CAA0
	bool32 newIsClone; // 0x1CAC8
	uint8 newPlayer; // 0x1CACC
	uint8 newEntity; // 0x1CACD
	bool newForceFiles; // 0x1CACE
	uint8 newForceFilesCharacter; // 0x1CACF
	uint8 newGamepad; // 0x1CAD0
	byte16 newButtonMask; // 0x1CAD1
	bool newEnableRightStick; // 0x1CAD3
	bool newEnableLeftStick; // 0x1CAD4
	bool newExecuteStyleSwitch; // 0x1CAD5
	bool newEnable; // 0x1CAD6
	uint8 newAirStingerCount; // 0x1CAD7
	_(8);
	byte32 newEffectIndices[8]; // 0x1CAE0
	uint32 newLastVar; // 0x1CB00

	operator byte8 *()
	{
		return reinterpret_cast<byte8 *>(this);
	}
};

struct ActorDataBob
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
	PhysicsMetadata * modelPhysicsMetadataPool[4][24]; // 0x1880
	uint32 modelAllocationDataCount; // 0x1B80
	_(4);
	Size_32 modelAllocationData[209]; // 0x1B88
	_(748);
	float32 motionSpeed; // 0x3894
	float32 motionSpeedMultiplier; // 0x3898
	_(4);
	byte8 * motionArchives[32]; // 0x38A0
	_(16);
	MotionData motionData[2]; // 0x39B0
	MotionData motionDataMirror[3]; // 0x39B4
	_(2);
	uint32 var_39BC; // 0x39BC
	uint8 var_39C0[16]; // 0x39C0
	uint32 nextActionRequestPolicy[16]; // 0x39D0
	uint8 var_3A10[8]; // 0x3A10
	uint32 shadow; // 0x3A18
	uint32 lastShadow; // 0x3A1C
	_(8);
	byte32 color; // 0x3A28
	_(212);
	RecoveryData recoveryData[3]; // 0x3B00
	byte8 var_3C50[2]; // 0x3C50
	_(382);
	byte8 * actionData[6]; // 0x3DD0
	ActorEventData eventData[2]; // 0x3E00
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
	_(4);
	float32 var_3EC4; // 0x3EC4
	float32 var_3EC8; // 0x3EC8
	_(6);
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
	_(4);
	uint32 var_6340; // 0x6340
	_(20);
	uint32 styleLevel; // 0x6358
	_(5);
	bool quicksilver; // 0x6361
	bool doppelganger; // 0x6362
	_(1);
	float32 styleExperience; // 0x6364
	_(168);
	byte8 var_6410[40]; // 0x6410
	byte8 * var_6438; // 0x6438
	uint32 var_6440; // 0x6440
	_(12);
	uint32 cloneRate; // 0x6450
	uint32 var_6454; // 0x6454
	byte8 var_6458[32]; // 0x6458
	byte8 * cloneBaseAddr; // 0x6478
	bool cloneIsControlledByPlayer; // 0x6480
	_(23);
	uint8 weapons[5]; // 0x6498
	_(3);
	WeaponData * weaponData[5]; // 0x64A0
	uint32 weaponStatus[5]; // 0x64C8
	uint32 weaponLevels[5]; // 0x64DC
	_(4);
	float32 weaponTimers[5]; // 0x64F4
	float32 meleeWeaponSwitchTimeout; // 0x6508
	float32 rangedWeaponSwitchTimeout; // 0x650C
	uint32 styleRank; // 0x6510
	float32 styleMeter; // 0x6514
	_(348);
	InputData inputData[58]; // 0x6674
	_(36);
	BodyPartData bodyPartData[3][2]; // 0x6950
	_(576);
	byte8 var_7250[4]; // 0x7250
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
	bool submodelInit[5]; // 0x9AC0
	_(7675);
	uint32 newFirstVar; // 0xB8C0
	_(12);
	ModelData newModelData[6]; // 0xB8D0
	PhysicsMetadata * newModelPhysicsMetadataPool[7][24]; // 0xE5D0
	Size_32 newModelAllocationData[512]; // 0xEB10
	RecoveryData newRecoveryData[6]; // 0x12B10
	uint32 newDevilModels[6]; // 0x12DB0
	_(8);
	BodyPartData newBodyPartData[7][2]; // 0x12DD0
	ModelData newSubmodelData[11]; // 0x13D90
	bool newSubmodelInit[11]; // 0x19010
	_(5);
	ShadowData newModelShadowData[6]; // 0x19020
	ShadowData newSubmodelShadowData[11]; // 0x194A0
	PhysicsMetadata * newDevilModelPhysicsMetadataPool[5][36]; // 0x19CE0
	PhysicsData newDevilSubmodelPhysicsData[10]; // 0x1A280
	PhysicsLinkData newDevilSubmodelPhysicsLinkData[10][4]; // 0x1ABE0
	uint8 newWeapons[10]; // 0x1C9E0
	_(6);
	WeaponData * newWeaponData[10]; // 0x1C9F0
	uint32 newWeaponStatus[10]; // 0x1CA40
	_(8);
	uint32 newWeaponLevels[10]; // 0x1CA70
	_(8);
	float32 newWeaponTimers[10]; // 0x1CAA0
	bool32 newIsClone; // 0x1CAC8
	uint8 newPlayer; // 0x1CACC
	uint8 newEntity; // 0x1CACD
	bool newForceFiles; // 0x1CACE
	uint8 newForceFilesCharacter; // 0x1CACF
	uint8 newGamepad; // 0x1CAD0
	byte16 newButtonMask; // 0x1CAD1
	bool newEnableRightStick; // 0x1CAD3
	bool newEnableLeftStick; // 0x1CAD4
	bool newExecuteStyleSwitch; // 0x1CAD5
	bool newEnable; // 0x1CAD6
	uint8 newAirStingerCount; // 0x1CAD7
	_(8);
	byte32 newEffectIndices[8]; // 0x1CAE0
	uint32 newLastVar; // 0x1CB00

	operator byte8 *()
	{
		return reinterpret_cast<byte8 *>(this);
	}
};

struct ActorDataLady
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
	PhysicsMetadata * modelPhysicsMetadataPool[4][24]; // 0x1880
	uint32 modelAllocationDataCount; // 0x1B80
	_(4);
	Size_32 modelAllocationData[209]; // 0x1B88
	_(748);
	float32 motionSpeed; // 0x3894
	float32 motionSpeedMultiplier; // 0x3898
	_(4);
	byte8 * motionArchives[32]; // 0x38A0
	_(16);
	MotionData motionData[2]; // 0x39B0
	MotionData motionDataMirror[3]; // 0x39B4
	_(2);
	uint32 var_39BC; // 0x39BC
	uint8 var_39C0[16]; // 0x39C0
	uint32 nextActionRequestPolicy[16]; // 0x39D0
	uint8 var_3A10[8]; // 0x3A10
	uint32 shadow; // 0x3A18
	uint32 lastShadow; // 0x3A1C
	_(8);
	byte32 color; // 0x3A28
	_(212);
	RecoveryData recoveryData[3]; // 0x3B00
	byte8 var_3C50[2]; // 0x3C50
	_(382);
	byte8 * actionData[6]; // 0x3DD0
	ActorEventData eventData[2]; // 0x3E00
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
	_(4);
	float32 var_3EC4; // 0x3EC4
	float32 var_3EC8; // 0x3EC8
	_(6);
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
	_(4);
	uint32 var_6340; // 0x6340
	_(20);
	uint32 styleLevel; // 0x6358
	_(5);
	bool quicksilver; // 0x6361
	bool doppelganger; // 0x6362
	_(1);
	float32 styleExperience; // 0x6364
	_(168);
	byte8 var_6410[40]; // 0x6410
	byte8 * var_6438; // 0x6438
	uint32 var_6440; // 0x6440
	_(12);
	uint32 cloneRate; // 0x6450
	uint32 var_6454; // 0x6454
	byte8 var_6458[32]; // 0x6458
	byte8 * cloneBaseAddr; // 0x6478
	bool cloneIsControlledByPlayer; // 0x6480
	_(23);
	uint8 weapons[5]; // 0x6498
	_(3);
	WeaponData * weaponData[5]; // 0x64A0
	uint32 weaponStatus[5]; // 0x64C8
	uint32 weaponLevels[5]; // 0x64DC
	_(4);
	float32 weaponTimers[5]; // 0x64F4
	float32 meleeWeaponSwitchTimeout; // 0x6508
	float32 rangedWeaponSwitchTimeout; // 0x650C
	uint32 styleRank; // 0x6510
	float32 styleMeter; // 0x6514
	_(348);
	InputData inputData[58]; // 0x6674
	_(36);
	BodyPartData bodyPartData[3][2]; // 0x6950
	_(576);
	byte8 var_7250[4]; // 0x7250
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
	bool submodelInit[5]; // 0x9AC0
	_(7675);
	uint32 newFirstVar; // 0xB8C0
	_(12);
	ModelData newModelData[6]; // 0xB8D0
	PhysicsMetadata * newModelPhysicsMetadataPool[7][24]; // 0xE5D0
	Size_32 newModelAllocationData[512]; // 0xEB10
	RecoveryData newRecoveryData[6]; // 0x12B10
	uint32 newDevilModels[6]; // 0x12DB0
	_(8);
	BodyPartData newBodyPartData[7][2]; // 0x12DD0
	ModelData newSubmodelData[11]; // 0x13D90
	bool newSubmodelInit[11]; // 0x19010
	_(5);
	ShadowData newModelShadowData[6]; // 0x19020
	ShadowData newSubmodelShadowData[11]; // 0x194A0
	PhysicsMetadata * newDevilModelPhysicsMetadataPool[5][36]; // 0x19CE0
	PhysicsData newDevilSubmodelPhysicsData[10]; // 0x1A280
	PhysicsLinkData newDevilSubmodelPhysicsLinkData[10][4]; // 0x1ABE0
	uint8 newWeapons[10]; // 0x1C9E0
	_(6);
	WeaponData * newWeaponData[10]; // 0x1C9F0
	uint32 newWeaponStatus[10]; // 0x1CA40
	_(8);
	uint32 newWeaponLevels[10]; // 0x1CA70
	_(8);
	float32 newWeaponTimers[10]; // 0x1CAA0
	bool32 newIsClone; // 0x1CAC8
	uint8 newPlayer; // 0x1CACC
	uint8 newEntity; // 0x1CACD
	bool newForceFiles; // 0x1CACE
	uint8 newForceFilesCharacter; // 0x1CACF
	uint8 newGamepad; // 0x1CAD0
	byte16 newButtonMask; // 0x1CAD1
	bool newEnableRightStick; // 0x1CAD3
	bool newEnableLeftStick; // 0x1CAD4
	bool newExecuteStyleSwitch; // 0x1CAD5
	bool newEnable; // 0x1CAD6
	uint8 newAirStingerCount; // 0x1CAD7
	_(8);
	byte32 newEffectIndices[8]; // 0x1CAE0
	uint32 newLastVar; // 0x1CB00

	operator byte8 *()
	{
		return reinterpret_cast<byte8 *>(this);
	}
};

struct ActorDataVergil
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
	PhysicsMetadata * modelPhysicsMetadataPool[4][24]; // 0x1880
	uint32 modelAllocationDataCount; // 0x1B80
	_(4);
	Size_32 modelAllocationData[209]; // 0x1B88
	_(748);
	float32 motionSpeed; // 0x3894
	float32 motionSpeedMultiplier; // 0x3898
	_(4);
	byte8 * motionArchives[32]; // 0x38A0
	_(16);
	MotionData motionData[2]; // 0x39B0
	MotionData motionDataMirror[3]; // 0x39B4
	_(2);
	uint32 var_39BC; // 0x39BC
	uint8 var_39C0[16]; // 0x39C0
	uint32 nextActionRequestPolicy[16]; // 0x39D0
	uint8 var_3A10[8]; // 0x3A10
	uint32 shadow; // 0x3A18
	uint32 lastShadow; // 0x3A1C
	_(8);
	byte32 color; // 0x3A28
	_(212);
	RecoveryData recoveryData[3]; // 0x3B00
	byte8 var_3C50[2]; // 0x3C50
	_(382);
	byte8 * actionData[6]; // 0x3DD0
	ActorEventData eventData[2]; // 0x3E00
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
	_(4);
	float32 var_3EC4; // 0x3EC4
	float32 var_3EC8; // 0x3EC8
	_(6);
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
	_(4);
	uint32 var_6340; // 0x6340
	_(20);
	uint32 styleLevel; // 0x6358
	_(2);
	uint8 airTrickCount; // 0x635E
	uint8 trickUpCount; // 0x635F
	uint8 trickDownCount; // 0x6360
	bool quicksilver; // 0x6361
	bool doppelganger; // 0x6362
	_(1);
	float32 styleExperience; // 0x6364
	_(168);
	byte8 var_6410[40]; // 0x6410
	byte8 * var_6438; // 0x6438
	uint32 var_6440; // 0x6440
	_(12);
	uint32 cloneRate; // 0x6450
	uint32 var_6454; // 0x6454
	byte8 var_6458[32]; // 0x6458
	byte8 * cloneBaseAddr; // 0x6478
	bool cloneIsControlledByPlayer; // 0x6480
	_(3);
	uint32 activeMeleeWeaponIndex; // 0x6484
	uint32 queuedMeleeWeaponIndex; // 0x6488
	_(12);
	uint8 weapons[5]; // 0x6498
	_(3);
	WeaponData * weaponData[5]; // 0x64A0
	uint32 weaponStatus[5]; // 0x64C8
	uint32 weaponLevels[5]; // 0x64DC
	_(4);
	float32 weaponTimers[5]; // 0x64F4
	float32 meleeWeaponSwitchTimeout; // 0x6508
	float32 rangedWeaponSwitchTimeout; // 0x650C
	uint32 styleRank; // 0x6510
	float32 styleMeter; // 0x6514
	_(348);
	InputData inputData[58]; // 0x6674
	_(36);
	BodyPartData bodyPartData[3][2]; // 0x6950
	_(576);
	byte8 var_7250[4]; // 0x7250
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
	bool submodelInit[5]; // 0x9AC0
	_(43);
	ShadowData modelShadowData[3]; // 0x9AF0
	ShadowData submodelShadowData[5]; // 0x9D30
	PhysicsMetadata * submodelPhysicsMetadataPool[39]; // 0xA0F0
	_(8);
	PhysicsData submodelPhysicsData; // 0xA230
	_(4896);
	ModelMetadata modelMetadata[6]; // 0xB640
	_(160);
	uint32 newFirstVar; // 0xB8C0
	_(12);
	ModelData newModelData[6]; // 0xB8D0
	PhysicsMetadata * newModelPhysicsMetadataPool[7][24]; // 0xE5D0
	Size_32 newModelAllocationData[512]; // 0xEB10
	RecoveryData newRecoveryData[6]; // 0x12B10
	uint32 newDevilModels[6]; // 0x12DB0
	_(8);
	BodyPartData newBodyPartData[7][2]; // 0x12DD0
	ModelData newSubmodelData[11]; // 0x13D90
	bool newSubmodelInit[11]; // 0x19010
	_(5);
	ShadowData newModelShadowData[6]; // 0x19020
	ShadowData newSubmodelShadowData[11]; // 0x194A0
	PhysicsMetadata * newDevilModelPhysicsMetadataPool[5][36]; // 0x19CE0
	PhysicsData newDevilSubmodelPhysicsData[10]; // 0x1A280
	PhysicsLinkData newDevilSubmodelPhysicsLinkData[10][4]; // 0x1ABE0
	uint8 newWeapons[10]; // 0x1C9E0
	_(6);
	WeaponData * newWeaponData[10]; // 0x1C9F0
	uint32 newWeaponStatus[10]; // 0x1CA40
	_(8);
	uint32 newWeaponLevels[10]; // 0x1CA70
	_(8);
	float32 newWeaponTimers[10]; // 0x1CAA0
	bool32 newIsClone; // 0x1CAC8
	uint8 newPlayer; // 0x1CACC
	uint8 newEntity; // 0x1CACD
	bool newForceFiles; // 0x1CACE
	uint8 newForceFilesCharacter; // 0x1CACF
	uint8 newGamepad; // 0x1CAD0
	byte16 newButtonMask; // 0x1CAD1
	bool newEnableRightStick; // 0x1CAD3
	bool newEnableLeftStick; // 0x1CAD4
	bool newExecuteStyleSwitch; // 0x1CAD5
	bool newEnable; // 0x1CAD6
	uint8 newAirStingerCount; // 0x1CAD7
	_(8);
	byte32 newEffectIndices[8]; // 0x1CAE0
	uint32 newLastVar; // 0x1CB00

	operator byte8 *()
	{
		return reinterpret_cast<byte8 *>(this);
	}
};

static_assert(offsetof(ActorData, status) == 8);
static_assert(offsetof(ActorData, character) == 0x78);
static_assert(offsetof(ActorData, position) == 0x80);
static_assert(offsetof(ActorData, pull) == 0x94);
static_assert(offsetof(ActorData, pullMultiplier) == 0xA4);
static_assert(offsetof(ActorData, rotation) == 0xC0);
static_assert(offsetof(ActorData, id) == 0x118);
static_assert(offsetof(ActorData, isClone) == 0x11C);
static_assert(offsetof(ActorData, visible) == 0x120);
static_assert(offsetof(ActorData, var_1C0) == 0x1C0);
static_assert(offsetof(ActorData, var_1C4) == 0x1C4);
static_assert(offsetof(ActorData, modelData) == 0x200);
static_assert(offsetof(ActorData, modelPhysicsMetadataPool) == 0x1880);
static_assert(offsetof(ActorData, modelAllocationDataCount) == 0x1B80);
static_assert(offsetof(ActorData, modelAllocationData) == 0x1B88);
static_assert(offsetof(ActorData, motionSpeed) == 0x3894);
static_assert(offsetof(ActorData, motionSpeedMultiplier) == 0x3898);
static_assert(offsetof(ActorData, motionArchives) == 0x38A0);
static_assert(offsetof(ActorData, motionData) == 0x39B0);
static_assert(offsetof(ActorData, motionDataMirror) == 0x39B4);
static_assert(offsetof(ActorData, var_39BC) == 0x39BC);
static_assert(offsetof(ActorData, var_39C0) == 0x39C0);
static_assert(offsetof(ActorData, nextActionRequestPolicy) == 0x39D0);
static_assert(offsetof(ActorData, var_3A10) == 0x3A10);
static_assert(offsetof(ActorData, shadow) == 0x3A18);
static_assert(offsetof(ActorData, lastShadow) == 0x3A1C);
static_assert(offsetof(ActorData, color) == 0x3A28);
static_assert(offsetof(ActorData, recoveryData) == 0x3B00);
static_assert(offsetof(ActorData, var_3C50) == 0x3C50);
static_assert(offsetof(ActorData, actionData) == 0x3DD0);
static_assert(offsetof(ActorData, eventData) == 0x3E00);
static_assert(offsetof(ActorData, var_3E10) == 0x3E10);
static_assert(offsetof(ActorData, motionTimer) == 0x3E34);
static_assert(offsetof(ActorData, idleTimer) == 0x3E38);
static_assert(offsetof(ActorData, permissions) == 0x3E60);
static_assert(offsetof(ActorData, state) == 0x3E64);
static_assert(offsetof(ActorData, lastState) == 0x3E68);
static_assert(offsetof(ActorData, activeModelIndex) == 0x3E6C);
static_assert(offsetof(ActorData, queuedModelIndex) == 0x3E70);
static_assert(offsetof(ActorData, devilModels) == 0x3E74);
static_assert(offsetof(ActorData, modelState) == 0x3E80);
static_assert(offsetof(ActorData, lockOn) == 0x3E84);
static_assert(offsetof(ActorData, activeModelIndexMirror) == 0x3E88);
static_assert(offsetof(ActorData, activeDevil) == 0x3E8C);
static_assert(offsetof(ActorData, airRaid) == 0x3E90);
static_assert(offsetof(ActorData, mode) == 0x3E94);
static_assert(offsetof(ActorData, devil) == 0x3E9B);
static_assert(offsetof(ActorData, costume) == 0x3E9E);
static_assert(offsetof(ActorData, useHolyWater) == 0x3EA4);
static_assert(offsetof(ActorData, magicPoints) == 0x3EB8);
static_assert(offsetof(ActorData, maxMagicPoints) == 0x3EBC);
static_assert(offsetof(ActorData, var_3EC4) == 0x3EC4);
static_assert(offsetof(ActorData, var_3EC8) == 0x3EC8);
static_assert(offsetof(ActorData, var_3ED2) == 0x3ED2);
static_assert(offsetof(ActorData, cameraDirection) == 0x3ED8);
static_assert(offsetof(ActorData, airHikeCount) == 0x3F11);
static_assert(offsetof(ActorData, kickJumpCount) == 0x3F12);
static_assert(offsetof(ActorData, wallHikeCount) == 0x3F13);
static_assert(offsetof(ActorData, var_3F19) == 0x3F19);
static_assert(offsetof(ActorData, action) == 0x3FA4);
static_assert(offsetof(ActorData, lastAction) == 0x3FA5);
static_assert(offsetof(ActorData, bufferedAction) == 0x3FA8);
static_assert(offsetof(ActorData, chainCount) == 0x3FAC);
static_assert(offsetof(ActorData, expertise) == 0x3FEC);
static_assert(offsetof(ActorData, maxHitPoints) == 0x40EC);
static_assert(offsetof(ActorData, hitPoints) == 0x411C);
static_assert(offsetof(ActorData, targetBaseAddr) == 0x6328);
static_assert(offsetof(ActorData, style) == 0x6338);
static_assert(offsetof(ActorData, var_6340) == 0x6340);
static_assert(offsetof(ActorData, styleLevel) == 0x6358);
static_assert(offsetof(ActorData, quicksilver) == 0x6361);
static_assert(offsetof(ActorData, doppelganger) == 0x6362);
static_assert(offsetof(ActorData, styleExperience) == 0x6364);
static_assert(offsetof(ActorData, var_6410) == 0x6410);
static_assert(offsetof(ActorData, var_6438) == 0x6438);
static_assert(offsetof(ActorData, var_6440) == 0x6440);
static_assert(offsetof(ActorData, cloneRate) == 0x6450);
static_assert(offsetof(ActorData, var_6454) == 0x6454);
static_assert(offsetof(ActorData, var_6458) == 0x6458);
static_assert(offsetof(ActorData, cloneBaseAddr) == 0x6478);
static_assert(offsetof(ActorData, cloneIsControlledByPlayer) == 0x6480);
static_assert(offsetof(ActorData, weapons) == 0x6498);
static_assert(offsetof(ActorData, weaponData) == 0x64A0);
static_assert(offsetof(ActorData, weaponStatus) == 0x64C8);
static_assert(offsetof(ActorData, weaponLevels) == 0x64DC);
static_assert(offsetof(ActorData, weaponTimers) == 0x64F4);
static_assert(offsetof(ActorData, meleeWeaponSwitchTimeout) == 0x6508);
static_assert(offsetof(ActorData, rangedWeaponSwitchTimeout) == 0x650C);
static_assert(offsetof(ActorData, styleRank) == 0x6510);
static_assert(offsetof(ActorData, styleMeter) == 0x6514);
static_assert(offsetof(ActorData, inputData) == 0x6674);
static_assert(offsetof(ActorData, bodyPartData) == 0x6950);
static_assert(offsetof(ActorData, var_7250) == 0x7250);
static_assert(offsetof(ActorData, collisionIndex) == 0x7254);
static_assert(offsetof(ActorData, interactionData) == 0x7460);
static_assert(offsetof(ActorData, buttons) == 0x74E0);
static_assert(offsetof(ActorData, rightStickPosition) == 0x74F8);
static_assert(offsetof(ActorData, rightStickRadius) == 0x74FA);
static_assert(offsetof(ActorData, leftStickPosition) == 0x7508);
static_assert(offsetof(ActorData, leftStickRadius) == 0x750A);
static_assert(offsetof(ActorData, actorCameraDirection) == 0x750C);
static_assert(offsetof(ActorData, leftStickDirection) == 0x751C);
static_assert(offsetof(ActorData, submodelData) == 0x7540);
static_assert(offsetof(ActorData, submodelInit) == 0x9AC0);
static_assert(offsetof(ActorData, newFirstVar) == 0xB8C0);
static_assert(offsetof(ActorData, newModelData) == 0xB8D0);
static_assert(offsetof(ActorData, newModelPhysicsMetadataPool) == 0xE5D0);
static_assert(offsetof(ActorData, newModelAllocationData) == 0xEB10);
static_assert(offsetof(ActorData, newRecoveryData) == 0x12B10);
static_assert(offsetof(ActorData, newDevilModels) == 0x12DB0);
static_assert(offsetof(ActorData, newBodyPartData) == 0x12DD0);
static_assert(offsetof(ActorData, newSubmodelData) == 0x13D90);
static_assert(offsetof(ActorData, newSubmodelInit) == 0x19010);
static_assert(offsetof(ActorData, newModelShadowData) == 0x19020);
static_assert(offsetof(ActorData, newSubmodelShadowData) == 0x194A0);
static_assert(offsetof(ActorData, newDevilModelPhysicsMetadataPool) == 0x19CE0);
static_assert(offsetof(ActorData, newDevilSubmodelPhysicsData) == 0x1A280);
static_assert(offsetof(ActorData, newDevilSubmodelPhysicsLinkData) == 0x1ABE0);
static_assert(offsetof(ActorData, newWeapons) == 0x1C9E0);
static_assert(offsetof(ActorData, newWeaponData) == 0x1C9F0);
static_assert(offsetof(ActorData, newWeaponStatus) == 0x1CA40);
static_assert(offsetof(ActorData, newWeaponLevels) == 0x1CA70);
static_assert(offsetof(ActorData, newWeaponTimers) == 0x1CAA0);
static_assert(offsetof(ActorData, newIsClone) == 0x1CAC8);
static_assert(offsetof(ActorData, newPlayer) == 0x1CACC);
static_assert(offsetof(ActorData, newEntity) == 0x1CACD);
static_assert(offsetof(ActorData, newForceFiles) == 0x1CACE);
static_assert(offsetof(ActorData, newForceFilesCharacter) == 0x1CACF);
static_assert(offsetof(ActorData, newGamepad) == 0x1CAD0);
static_assert(offsetof(ActorData, newButtonMask) == 0x1CAD1);
static_assert(offsetof(ActorData, newEnableRightStick) == 0x1CAD3);
static_assert(offsetof(ActorData, newEnableLeftStick) == 0x1CAD4);
static_assert(offsetof(ActorData, newExecuteStyleSwitch) == 0x1CAD5);
static_assert(offsetof(ActorData, newEnable) == 0x1CAD6);
static_assert(offsetof(ActorData, newAirStingerCount) == 0x1CAD7);
static_assert(offsetof(ActorData, newEffectIndices) == 0x1CAE0);
static_assert(offsetof(ActorData, newLastVar) == 0x1CB00);

static_assert(offsetof(ActorDataDante, status) == 8);
static_assert(offsetof(ActorDataDante, character) == 0x78);
static_assert(offsetof(ActorDataDante, position) == 0x80);
static_assert(offsetof(ActorDataDante, pull) == 0x94);
static_assert(offsetof(ActorDataDante, pullMultiplier) == 0xA4);
static_assert(offsetof(ActorDataDante, rotation) == 0xC0);
static_assert(offsetof(ActorDataDante, id) == 0x118);
static_assert(offsetof(ActorDataDante, isClone) == 0x11C);
static_assert(offsetof(ActorDataDante, visible) == 0x120);
static_assert(offsetof(ActorDataDante, var_1C0) == 0x1C0);
static_assert(offsetof(ActorDataDante, var_1C4) == 0x1C4);
static_assert(offsetof(ActorDataDante, modelData) == 0x200);
static_assert(offsetof(ActorDataDante, modelPhysicsMetadataPool) == 0x1880);
static_assert(offsetof(ActorDataDante, modelAllocationDataCount) == 0x1B80);
static_assert(offsetof(ActorDataDante, modelAllocationData) == 0x1B88);
static_assert(offsetof(ActorDataDante, motionSpeed) == 0x3894);
static_assert(offsetof(ActorDataDante, motionSpeedMultiplier) == 0x3898);
static_assert(offsetof(ActorDataDante, motionArchives) == 0x38A0);
static_assert(offsetof(ActorDataDante, motionData) == 0x39B0);
static_assert(offsetof(ActorDataDante, motionDataMirror) == 0x39B4);
static_assert(offsetof(ActorDataDante, var_39BC) == 0x39BC);
static_assert(offsetof(ActorDataDante, var_39C0) == 0x39C0);
static_assert(offsetof(ActorDataDante, nextActionRequestPolicy) == 0x39D0);
static_assert(offsetof(ActorDataDante, var_3A10) == 0x3A10);
static_assert(offsetof(ActorDataDante, shadow) == 0x3A18);
static_assert(offsetof(ActorDataDante, lastShadow) == 0x3A1C);
static_assert(offsetof(ActorDataDante, color) == 0x3A28);
static_assert(offsetof(ActorDataDante, recoveryData) == 0x3B00);
static_assert(offsetof(ActorDataDante, var_3C50) == 0x3C50);
static_assert(offsetof(ActorDataDante, actionData) == 0x3DD0);
static_assert(offsetof(ActorDataDante, eventData) == 0x3E00);
static_assert(offsetof(ActorDataDante, var_3E10) == 0x3E10);
static_assert(offsetof(ActorDataDante, motionTimer) == 0x3E34);
static_assert(offsetof(ActorDataDante, idleTimer) == 0x3E38);
static_assert(offsetof(ActorDataDante, permissions) == 0x3E60);
static_assert(offsetof(ActorDataDante, state) == 0x3E64);
static_assert(offsetof(ActorDataDante, lastState) == 0x3E68);
static_assert(offsetof(ActorDataDante, activeModelIndex) == 0x3E6C);
static_assert(offsetof(ActorDataDante, queuedModelIndex) == 0x3E70);
static_assert(offsetof(ActorDataDante, devilModels) == 0x3E74);
static_assert(offsetof(ActorDataDante, modelState) == 0x3E80);
static_assert(offsetof(ActorDataDante, lockOn) == 0x3E84);
static_assert(offsetof(ActorDataDante, activeModelIndexMirror) == 0x3E88);
static_assert(offsetof(ActorDataDante, activeDevil) == 0x3E8C);
static_assert(offsetof(ActorDataDante, airRaid) == 0x3E90);
static_assert(offsetof(ActorDataDante, mode) == 0x3E94);
static_assert(offsetof(ActorDataDante, devil) == 0x3E9B);
static_assert(offsetof(ActorDataDante, costume) == 0x3E9E);
static_assert(offsetof(ActorDataDante, sparda) == 0x3E9F);
static_assert(offsetof(ActorDataDante, useHolyWater) == 0x3EA4);
static_assert(offsetof(ActorDataDante, magicPoints) == 0x3EB8);
static_assert(offsetof(ActorDataDante, maxMagicPoints) == 0x3EBC);
static_assert(offsetof(ActorDataDante, var_3EC4) == 0x3EC4);
static_assert(offsetof(ActorDataDante, var_3EC8) == 0x3EC8);
static_assert(offsetof(ActorDataDante, var_3ED2) == 0x3ED2);
static_assert(offsetof(ActorDataDante, cameraDirection) == 0x3ED8);
static_assert(offsetof(ActorDataDante, airHikeCount) == 0x3F11);
static_assert(offsetof(ActorDataDante, kickJumpCount) == 0x3F12);
static_assert(offsetof(ActorDataDante, wallHikeCount) == 0x3F13);
static_assert(offsetof(ActorDataDante, var_3F19) == 0x3F19);
static_assert(offsetof(ActorDataDante, action) == 0x3FA4);
static_assert(offsetof(ActorDataDante, lastAction) == 0x3FA5);
static_assert(offsetof(ActorDataDante, bufferedAction) == 0x3FA8);
static_assert(offsetof(ActorDataDante, chainCount) == 0x3FAC);
static_assert(offsetof(ActorDataDante, expertise) == 0x3FEC);
static_assert(offsetof(ActorDataDante, maxHitPoints) == 0x40EC);
static_assert(offsetof(ActorDataDante, hitPoints) == 0x411C);
static_assert(offsetof(ActorDataDante, targetBaseAddr) == 0x6328);
static_assert(offsetof(ActorDataDante, style) == 0x6338);
static_assert(offsetof(ActorDataDante, var_6340) == 0x6340);
static_assert(offsetof(ActorDataDante, styleLevel) == 0x6358);
static_assert(offsetof(ActorDataDante, dashCount) == 0x635C);
static_assert(offsetof(ActorDataDante, skyStarCount) == 0x635D);
static_assert(offsetof(ActorDataDante, airTrickCount) == 0x635E);
static_assert(offsetof(ActorDataDante, quicksilver) == 0x6361);
static_assert(offsetof(ActorDataDante, doppelganger) == 0x6362);
static_assert(offsetof(ActorDataDante, styleExperience) == 0x6364);
static_assert(offsetof(ActorDataDante, var_6410) == 0x6410);
static_assert(offsetof(ActorDataDante, var_6438) == 0x6438);
static_assert(offsetof(ActorDataDante, var_6440) == 0x6440);
static_assert(offsetof(ActorDataDante, cloneRate) == 0x6450);
static_assert(offsetof(ActorDataDante, var_6454) == 0x6454);
static_assert(offsetof(ActorDataDante, var_6458) == 0x6458);
static_assert(offsetof(ActorDataDante, cloneBaseAddr) == 0x6478);
static_assert(offsetof(ActorDataDante, cloneIsControlledByPlayer) == 0x6480);
static_assert(offsetof(ActorDataDante, activeWeapon) == 0x648D);
static_assert(offsetof(ActorDataDante, meleeWeaponIndex) == 0x6490);
static_assert(offsetof(ActorDataDante, rangedWeaponIndex) == 0x6494);
static_assert(offsetof(ActorDataDante, weapons) == 0x6498);
static_assert(offsetof(ActorDataDante, weaponData) == 0x64A0);
static_assert(offsetof(ActorDataDante, weaponStatus) == 0x64C8);
static_assert(offsetof(ActorDataDante, weaponLevels) == 0x64DC);
static_assert(offsetof(ActorDataDante, activeMeleeWeapon) == 0x64F0);
static_assert(offsetof(ActorDataDante, activeRangedWeapon) == 0x64F1);
static_assert(offsetof(ActorDataDante, weaponTimers) == 0x64F4);
static_assert(offsetof(ActorDataDante, meleeWeaponSwitchTimeout) == 0x6508);
static_assert(offsetof(ActorDataDante, rangedWeaponSwitchTimeout) == 0x650C);
static_assert(offsetof(ActorDataDante, styleRank) == 0x6510);
static_assert(offsetof(ActorDataDante, styleMeter) == 0x6514);
static_assert(offsetof(ActorDataDante, inputData) == 0x6674);
static_assert(offsetof(ActorDataDante, bodyPartData) == 0x6950);
static_assert(offsetof(ActorDataDante, var_7250) == 0x7250);
static_assert(offsetof(ActorDataDante, collisionIndex) == 0x7254);
static_assert(offsetof(ActorDataDante, interactionData) == 0x7460);
static_assert(offsetof(ActorDataDante, buttons) == 0x74E0);
static_assert(offsetof(ActorDataDante, rightStickPosition) == 0x74F8);
static_assert(offsetof(ActorDataDante, rightStickRadius) == 0x74FA);
static_assert(offsetof(ActorDataDante, leftStickPosition) == 0x7508);
static_assert(offsetof(ActorDataDante, leftStickRadius) == 0x750A);
static_assert(offsetof(ActorDataDante, actorCameraDirection) == 0x750C);
static_assert(offsetof(ActorDataDante, leftStickDirection) == 0x751C);
static_assert(offsetof(ActorDataDante, submodelData) == 0x7540);
static_assert(offsetof(ActorDataDante, submodelInit) == 0x9AC0);
static_assert(offsetof(ActorDataDante, modelShadowData) == 0x9AD0);
static_assert(offsetof(ActorDataDante, submodelShadowData) == 0x9D10);
static_assert(offsetof(ActorDataDante, submodelPhysicsMetadataPool) == 0xA0D0);
static_assert(offsetof(ActorDataDante, submodelPhysicsData) == 0xA210);
static_assert(offsetof(ActorDataDante, devilModelPhysicsMetadataPool) == 0xA300);
static_assert(offsetof(ActorDataDante, devilSubmodelPhysicsData) == 0xA540);
static_assert(offsetof(ActorDataDante, devilSubmodelPhysicsLinkData) == 0xAA00);
static_assert(offsetof(ActorDataDante, devilModelMetadata) == 0xB600);
static_assert(offsetof(ActorDataDante, modelMetadata) == 0xB630);
static_assert(offsetof(ActorDataDante, artemisChargeValue) == 0xB868);
static_assert(offsetof(ActorDataDante, artemisChargeFlags) == 0xB87C);
static_assert(offsetof(ActorDataDante, newFirstVar) == 0xB8C0);
static_assert(offsetof(ActorDataDante, newModelData) == 0xB8D0);
static_assert(offsetof(ActorDataDante, newModelPhysicsMetadataPool) == 0xE5D0);
static_assert(offsetof(ActorDataDante, newModelAllocationData) == 0xEB10);
static_assert(offsetof(ActorDataDante, newRecoveryData) == 0x12B10);
static_assert(offsetof(ActorDataDante, newDevilModels) == 0x12DB0);
static_assert(offsetof(ActorDataDante, newBodyPartData) == 0x12DD0);
static_assert(offsetof(ActorDataDante, newSubmodelData) == 0x13D90);
static_assert(offsetof(ActorDataDante, newSubmodelInit) == 0x19010);
static_assert(offsetof(ActorDataDante, newModelShadowData) == 0x19020);
static_assert(offsetof(ActorDataDante, newSubmodelShadowData) == 0x194A0);
static_assert(offsetof(ActorDataDante, newDevilModelPhysicsMetadataPool) == 0x19CE0);
static_assert(offsetof(ActorDataDante, newDevilSubmodelPhysicsData) == 0x1A280);
static_assert(offsetof(ActorDataDante, newDevilSubmodelPhysicsLinkData) == 0x1ABE0);
static_assert(offsetof(ActorDataDante, newWeapons) == 0x1C9E0);
static_assert(offsetof(ActorDataDante, newWeaponData) == 0x1C9F0);
static_assert(offsetof(ActorDataDante, newWeaponStatus) == 0x1CA40);
static_assert(offsetof(ActorDataDante, newWeaponLevels) == 0x1CA70);
static_assert(offsetof(ActorDataDante, newWeaponTimers) == 0x1CAA0);
static_assert(offsetof(ActorDataDante, newIsClone) == 0x1CAC8);
static_assert(offsetof(ActorDataDante, newPlayer) == 0x1CACC);
static_assert(offsetof(ActorDataDante, newEntity) == 0x1CACD);
static_assert(offsetof(ActorDataDante, newForceFiles) == 0x1CACE);
static_assert(offsetof(ActorDataDante, newForceFilesCharacter) == 0x1CACF);
static_assert(offsetof(ActorDataDante, newGamepad) == 0x1CAD0);
static_assert(offsetof(ActorDataDante, newButtonMask) == 0x1CAD1);
static_assert(offsetof(ActorDataDante, newEnableRightStick) == 0x1CAD3);
static_assert(offsetof(ActorDataDante, newEnableLeftStick) == 0x1CAD4);
static_assert(offsetof(ActorDataDante, newExecuteStyleSwitch) == 0x1CAD5);
static_assert(offsetof(ActorDataDante, newEnable) == 0x1CAD6);
static_assert(offsetof(ActorDataDante, newAirStingerCount) == 0x1CAD7);
static_assert(offsetof(ActorDataDante, newEffectIndices) == 0x1CAE0);
static_assert(offsetof(ActorDataDante, newLastVar) == 0x1CB00);

static_assert(offsetof(ActorDataBob, status) == 8);
static_assert(offsetof(ActorDataBob, character) == 0x78);
static_assert(offsetof(ActorDataBob, position) == 0x80);
static_assert(offsetof(ActorDataBob, pull) == 0x94);
static_assert(offsetof(ActorDataBob, pullMultiplier) == 0xA4);
static_assert(offsetof(ActorDataBob, rotation) == 0xC0);
static_assert(offsetof(ActorDataBob, id) == 0x118);
static_assert(offsetof(ActorDataBob, isClone) == 0x11C);
static_assert(offsetof(ActorDataBob, visible) == 0x120);
static_assert(offsetof(ActorDataBob, var_1C0) == 0x1C0);
static_assert(offsetof(ActorDataBob, var_1C4) == 0x1C4);
static_assert(offsetof(ActorDataBob, modelData) == 0x200);
static_assert(offsetof(ActorDataBob, modelPhysicsMetadataPool) == 0x1880);
static_assert(offsetof(ActorDataBob, modelAllocationDataCount) == 0x1B80);
static_assert(offsetof(ActorDataBob, modelAllocationData) == 0x1B88);
static_assert(offsetof(ActorDataBob, motionSpeed) == 0x3894);
static_assert(offsetof(ActorDataBob, motionSpeedMultiplier) == 0x3898);
static_assert(offsetof(ActorDataBob, motionArchives) == 0x38A0);
static_assert(offsetof(ActorDataBob, motionData) == 0x39B0);
static_assert(offsetof(ActorDataBob, motionDataMirror) == 0x39B4);
static_assert(offsetof(ActorDataBob, var_39BC) == 0x39BC);
static_assert(offsetof(ActorDataBob, var_39C0) == 0x39C0);
static_assert(offsetof(ActorDataBob, nextActionRequestPolicy) == 0x39D0);
static_assert(offsetof(ActorDataBob, var_3A10) == 0x3A10);
static_assert(offsetof(ActorDataBob, shadow) == 0x3A18);
static_assert(offsetof(ActorDataBob, lastShadow) == 0x3A1C);
static_assert(offsetof(ActorDataBob, color) == 0x3A28);
static_assert(offsetof(ActorDataBob, recoveryData) == 0x3B00);
static_assert(offsetof(ActorDataBob, var_3C50) == 0x3C50);
static_assert(offsetof(ActorDataBob, actionData) == 0x3DD0);
static_assert(offsetof(ActorDataBob, eventData) == 0x3E00);
static_assert(offsetof(ActorDataBob, var_3E10) == 0x3E10);
static_assert(offsetof(ActorDataBob, motionTimer) == 0x3E34);
static_assert(offsetof(ActorDataBob, idleTimer) == 0x3E38);
static_assert(offsetof(ActorDataBob, permissions) == 0x3E60);
static_assert(offsetof(ActorDataBob, state) == 0x3E64);
static_assert(offsetof(ActorDataBob, lastState) == 0x3E68);
static_assert(offsetof(ActorDataBob, activeModelIndex) == 0x3E6C);
static_assert(offsetof(ActorDataBob, queuedModelIndex) == 0x3E70);
static_assert(offsetof(ActorDataBob, devilModels) == 0x3E74);
static_assert(offsetof(ActorDataBob, modelState) == 0x3E80);
static_assert(offsetof(ActorDataBob, lockOn) == 0x3E84);
static_assert(offsetof(ActorDataBob, activeModelIndexMirror) == 0x3E88);
static_assert(offsetof(ActorDataBob, activeDevil) == 0x3E8C);
static_assert(offsetof(ActorDataBob, airRaid) == 0x3E90);
static_assert(offsetof(ActorDataBob, mode) == 0x3E94);
static_assert(offsetof(ActorDataBob, devil) == 0x3E9B);
static_assert(offsetof(ActorDataBob, costume) == 0x3E9E);
static_assert(offsetof(ActorDataBob, useHolyWater) == 0x3EA4);
static_assert(offsetof(ActorDataBob, magicPoints) == 0x3EB8);
static_assert(offsetof(ActorDataBob, maxMagicPoints) == 0x3EBC);
static_assert(offsetof(ActorDataBob, var_3EC4) == 0x3EC4);
static_assert(offsetof(ActorDataBob, var_3EC8) == 0x3EC8);
static_assert(offsetof(ActorDataBob, var_3ED2) == 0x3ED2);
static_assert(offsetof(ActorDataBob, cameraDirection) == 0x3ED8);
static_assert(offsetof(ActorDataBob, airHikeCount) == 0x3F11);
static_assert(offsetof(ActorDataBob, kickJumpCount) == 0x3F12);
static_assert(offsetof(ActorDataBob, wallHikeCount) == 0x3F13);
static_assert(offsetof(ActorDataBob, var_3F19) == 0x3F19);
static_assert(offsetof(ActorDataBob, action) == 0x3FA4);
static_assert(offsetof(ActorDataBob, lastAction) == 0x3FA5);
static_assert(offsetof(ActorDataBob, bufferedAction) == 0x3FA8);
static_assert(offsetof(ActorDataBob, chainCount) == 0x3FAC);
static_assert(offsetof(ActorDataBob, expertise) == 0x3FEC);
static_assert(offsetof(ActorDataBob, maxHitPoints) == 0x40EC);
static_assert(offsetof(ActorDataBob, hitPoints) == 0x411C);
static_assert(offsetof(ActorDataBob, targetBaseAddr) == 0x6328);
static_assert(offsetof(ActorDataBob, style) == 0x6338);
static_assert(offsetof(ActorDataBob, var_6340) == 0x6340);
static_assert(offsetof(ActorDataBob, styleLevel) == 0x6358);
static_assert(offsetof(ActorDataBob, quicksilver) == 0x6361);
static_assert(offsetof(ActorDataBob, doppelganger) == 0x6362);
static_assert(offsetof(ActorDataBob, styleExperience) == 0x6364);
static_assert(offsetof(ActorDataBob, var_6410) == 0x6410);
static_assert(offsetof(ActorDataBob, var_6438) == 0x6438);
static_assert(offsetof(ActorDataBob, var_6440) == 0x6440);
static_assert(offsetof(ActorDataBob, cloneRate) == 0x6450);
static_assert(offsetof(ActorDataBob, var_6454) == 0x6454);
static_assert(offsetof(ActorDataBob, var_6458) == 0x6458);
static_assert(offsetof(ActorDataBob, cloneBaseAddr) == 0x6478);
static_assert(offsetof(ActorDataBob, cloneIsControlledByPlayer) == 0x6480);
static_assert(offsetof(ActorDataBob, weapons) == 0x6498);
static_assert(offsetof(ActorDataBob, weaponData) == 0x64A0);
static_assert(offsetof(ActorDataBob, weaponStatus) == 0x64C8);
static_assert(offsetof(ActorDataBob, weaponLevels) == 0x64DC);
static_assert(offsetof(ActorDataBob, weaponTimers) == 0x64F4);
static_assert(offsetof(ActorDataBob, meleeWeaponSwitchTimeout) == 0x6508);
static_assert(offsetof(ActorDataBob, rangedWeaponSwitchTimeout) == 0x650C);
static_assert(offsetof(ActorDataBob, styleRank) == 0x6510);
static_assert(offsetof(ActorDataBob, styleMeter) == 0x6514);
static_assert(offsetof(ActorDataBob, inputData) == 0x6674);
static_assert(offsetof(ActorDataBob, bodyPartData) == 0x6950);
static_assert(offsetof(ActorDataBob, var_7250) == 0x7250);
static_assert(offsetof(ActorDataBob, collisionIndex) == 0x7254);
static_assert(offsetof(ActorDataBob, interactionData) == 0x7460);
static_assert(offsetof(ActorDataBob, buttons) == 0x74E0);
static_assert(offsetof(ActorDataBob, rightStickPosition) == 0x74F8);
static_assert(offsetof(ActorDataBob, rightStickRadius) == 0x74FA);
static_assert(offsetof(ActorDataBob, leftStickPosition) == 0x7508);
static_assert(offsetof(ActorDataBob, leftStickRadius) == 0x750A);
static_assert(offsetof(ActorDataBob, actorCameraDirection) == 0x750C);
static_assert(offsetof(ActorDataBob, leftStickDirection) == 0x751C);
static_assert(offsetof(ActorDataBob, submodelData) == 0x7540);
static_assert(offsetof(ActorDataBob, submodelInit) == 0x9AC0);
static_assert(offsetof(ActorDataBob, newFirstVar) == 0xB8C0);
static_assert(offsetof(ActorDataBob, newModelData) == 0xB8D0);
static_assert(offsetof(ActorDataBob, newModelPhysicsMetadataPool) == 0xE5D0);
static_assert(offsetof(ActorDataBob, newModelAllocationData) == 0xEB10);
static_assert(offsetof(ActorDataBob, newRecoveryData) == 0x12B10);
static_assert(offsetof(ActorDataBob, newDevilModels) == 0x12DB0);
static_assert(offsetof(ActorDataBob, newBodyPartData) == 0x12DD0);
static_assert(offsetof(ActorDataBob, newSubmodelData) == 0x13D90);
static_assert(offsetof(ActorDataBob, newSubmodelInit) == 0x19010);
static_assert(offsetof(ActorDataBob, newModelShadowData) == 0x19020);
static_assert(offsetof(ActorDataBob, newSubmodelShadowData) == 0x194A0);
static_assert(offsetof(ActorDataBob, newDevilModelPhysicsMetadataPool) == 0x19CE0);
static_assert(offsetof(ActorDataBob, newDevilSubmodelPhysicsData) == 0x1A280);
static_assert(offsetof(ActorDataBob, newDevilSubmodelPhysicsLinkData) == 0x1ABE0);
static_assert(offsetof(ActorDataBob, newWeapons) == 0x1C9E0);
static_assert(offsetof(ActorDataBob, newWeaponData) == 0x1C9F0);
static_assert(offsetof(ActorDataBob, newWeaponStatus) == 0x1CA40);
static_assert(offsetof(ActorDataBob, newWeaponLevels) == 0x1CA70);
static_assert(offsetof(ActorDataBob, newWeaponTimers) == 0x1CAA0);
static_assert(offsetof(ActorDataBob, newIsClone) == 0x1CAC8);
static_assert(offsetof(ActorDataBob, newPlayer) == 0x1CACC);
static_assert(offsetof(ActorDataBob, newEntity) == 0x1CACD);
static_assert(offsetof(ActorDataBob, newForceFiles) == 0x1CACE);
static_assert(offsetof(ActorDataBob, newForceFilesCharacter) == 0x1CACF);
static_assert(offsetof(ActorDataBob, newGamepad) == 0x1CAD0);
static_assert(offsetof(ActorDataBob, newButtonMask) == 0x1CAD1);
static_assert(offsetof(ActorDataBob, newEnableRightStick) == 0x1CAD3);
static_assert(offsetof(ActorDataBob, newEnableLeftStick) == 0x1CAD4);
static_assert(offsetof(ActorDataBob, newExecuteStyleSwitch) == 0x1CAD5);
static_assert(offsetof(ActorDataBob, newEnable) == 0x1CAD6);
static_assert(offsetof(ActorDataBob, newAirStingerCount) == 0x1CAD7);
static_assert(offsetof(ActorDataBob, newEffectIndices) == 0x1CAE0);
static_assert(offsetof(ActorDataBob, newLastVar) == 0x1CB00);

static_assert(offsetof(ActorDataLady, status) == 8);
static_assert(offsetof(ActorDataLady, character) == 0x78);
static_assert(offsetof(ActorDataLady, position) == 0x80);
static_assert(offsetof(ActorDataLady, pull) == 0x94);
static_assert(offsetof(ActorDataLady, pullMultiplier) == 0xA4);
static_assert(offsetof(ActorDataLady, rotation) == 0xC0);
static_assert(offsetof(ActorDataLady, id) == 0x118);
static_assert(offsetof(ActorDataLady, isClone) == 0x11C);
static_assert(offsetof(ActorDataLady, visible) == 0x120);
static_assert(offsetof(ActorDataLady, var_1C0) == 0x1C0);
static_assert(offsetof(ActorDataLady, var_1C4) == 0x1C4);
static_assert(offsetof(ActorDataLady, modelData) == 0x200);
static_assert(offsetof(ActorDataLady, modelPhysicsMetadataPool) == 0x1880);
static_assert(offsetof(ActorDataLady, modelAllocationDataCount) == 0x1B80);
static_assert(offsetof(ActorDataLady, modelAllocationData) == 0x1B88);
static_assert(offsetof(ActorDataLady, motionSpeed) == 0x3894);
static_assert(offsetof(ActorDataLady, motionSpeedMultiplier) == 0x3898);
static_assert(offsetof(ActorDataLady, motionArchives) == 0x38A0);
static_assert(offsetof(ActorDataLady, motionData) == 0x39B0);
static_assert(offsetof(ActorDataLady, motionDataMirror) == 0x39B4);
static_assert(offsetof(ActorDataLady, var_39BC) == 0x39BC);
static_assert(offsetof(ActorDataLady, var_39C0) == 0x39C0);
static_assert(offsetof(ActorDataLady, nextActionRequestPolicy) == 0x39D0);
static_assert(offsetof(ActorDataLady, var_3A10) == 0x3A10);
static_assert(offsetof(ActorDataLady, shadow) == 0x3A18);
static_assert(offsetof(ActorDataLady, lastShadow) == 0x3A1C);
static_assert(offsetof(ActorDataLady, color) == 0x3A28);
static_assert(offsetof(ActorDataLady, recoveryData) == 0x3B00);
static_assert(offsetof(ActorDataLady, var_3C50) == 0x3C50);
static_assert(offsetof(ActorDataLady, actionData) == 0x3DD0);
static_assert(offsetof(ActorDataLady, eventData) == 0x3E00);
static_assert(offsetof(ActorDataLady, var_3E10) == 0x3E10);
static_assert(offsetof(ActorDataLady, motionTimer) == 0x3E34);
static_assert(offsetof(ActorDataLady, idleTimer) == 0x3E38);
static_assert(offsetof(ActorDataLady, permissions) == 0x3E60);
static_assert(offsetof(ActorDataLady, state) == 0x3E64);
static_assert(offsetof(ActorDataLady, lastState) == 0x3E68);
static_assert(offsetof(ActorDataLady, activeModelIndex) == 0x3E6C);
static_assert(offsetof(ActorDataLady, queuedModelIndex) == 0x3E70);
static_assert(offsetof(ActorDataLady, devilModels) == 0x3E74);
static_assert(offsetof(ActorDataLady, modelState) == 0x3E80);
static_assert(offsetof(ActorDataLady, lockOn) == 0x3E84);
static_assert(offsetof(ActorDataLady, activeModelIndexMirror) == 0x3E88);
static_assert(offsetof(ActorDataLady, activeDevil) == 0x3E8C);
static_assert(offsetof(ActorDataLady, airRaid) == 0x3E90);
static_assert(offsetof(ActorDataLady, mode) == 0x3E94);
static_assert(offsetof(ActorDataLady, devil) == 0x3E9B);
static_assert(offsetof(ActorDataLady, costume) == 0x3E9E);
static_assert(offsetof(ActorDataLady, useHolyWater) == 0x3EA4);
static_assert(offsetof(ActorDataLady, magicPoints) == 0x3EB8);
static_assert(offsetof(ActorDataLady, maxMagicPoints) == 0x3EBC);
static_assert(offsetof(ActorDataLady, var_3EC4) == 0x3EC4);
static_assert(offsetof(ActorDataLady, var_3EC8) == 0x3EC8);
static_assert(offsetof(ActorDataLady, var_3ED2) == 0x3ED2);
static_assert(offsetof(ActorDataLady, cameraDirection) == 0x3ED8);
static_assert(offsetof(ActorDataLady, airHikeCount) == 0x3F11);
static_assert(offsetof(ActorDataLady, kickJumpCount) == 0x3F12);
static_assert(offsetof(ActorDataLady, wallHikeCount) == 0x3F13);
static_assert(offsetof(ActorDataLady, var_3F19) == 0x3F19);
static_assert(offsetof(ActorDataLady, action) == 0x3FA4);
static_assert(offsetof(ActorDataLady, lastAction) == 0x3FA5);
static_assert(offsetof(ActorDataLady, bufferedAction) == 0x3FA8);
static_assert(offsetof(ActorDataLady, chainCount) == 0x3FAC);
static_assert(offsetof(ActorDataLady, expertise) == 0x3FEC);
static_assert(offsetof(ActorDataLady, maxHitPoints) == 0x40EC);
static_assert(offsetof(ActorDataLady, hitPoints) == 0x411C);
static_assert(offsetof(ActorDataLady, targetBaseAddr) == 0x6328);
static_assert(offsetof(ActorDataLady, style) == 0x6338);
static_assert(offsetof(ActorDataLady, var_6340) == 0x6340);
static_assert(offsetof(ActorDataLady, styleLevel) == 0x6358);
static_assert(offsetof(ActorDataLady, quicksilver) == 0x6361);
static_assert(offsetof(ActorDataLady, doppelganger) == 0x6362);
static_assert(offsetof(ActorDataLady, styleExperience) == 0x6364);
static_assert(offsetof(ActorDataLady, var_6410) == 0x6410);
static_assert(offsetof(ActorDataLady, var_6438) == 0x6438);
static_assert(offsetof(ActorDataLady, var_6440) == 0x6440);
static_assert(offsetof(ActorDataLady, cloneRate) == 0x6450);
static_assert(offsetof(ActorDataLady, var_6454) == 0x6454);
static_assert(offsetof(ActorDataLady, var_6458) == 0x6458);
static_assert(offsetof(ActorDataLady, cloneBaseAddr) == 0x6478);
static_assert(offsetof(ActorDataLady, cloneIsControlledByPlayer) == 0x6480);
static_assert(offsetof(ActorDataLady, weapons) == 0x6498);
static_assert(offsetof(ActorDataLady, weaponData) == 0x64A0);
static_assert(offsetof(ActorDataLady, weaponStatus) == 0x64C8);
static_assert(offsetof(ActorDataLady, weaponLevels) == 0x64DC);
static_assert(offsetof(ActorDataLady, weaponTimers) == 0x64F4);
static_assert(offsetof(ActorDataLady, meleeWeaponSwitchTimeout) == 0x6508);
static_assert(offsetof(ActorDataLady, rangedWeaponSwitchTimeout) == 0x650C);
static_assert(offsetof(ActorDataLady, styleRank) == 0x6510);
static_assert(offsetof(ActorDataLady, styleMeter) == 0x6514);
static_assert(offsetof(ActorDataLady, inputData) == 0x6674);
static_assert(offsetof(ActorDataLady, bodyPartData) == 0x6950);
static_assert(offsetof(ActorDataLady, var_7250) == 0x7250);
static_assert(offsetof(ActorDataLady, collisionIndex) == 0x7254);
static_assert(offsetof(ActorDataLady, interactionData) == 0x7460);
static_assert(offsetof(ActorDataLady, buttons) == 0x74E0);
static_assert(offsetof(ActorDataLady, rightStickPosition) == 0x74F8);
static_assert(offsetof(ActorDataLady, rightStickRadius) == 0x74FA);
static_assert(offsetof(ActorDataLady, leftStickPosition) == 0x7508);
static_assert(offsetof(ActorDataLady, leftStickRadius) == 0x750A);
static_assert(offsetof(ActorDataLady, actorCameraDirection) == 0x750C);
static_assert(offsetof(ActorDataLady, leftStickDirection) == 0x751C);
static_assert(offsetof(ActorDataLady, submodelData) == 0x7540);
static_assert(offsetof(ActorDataLady, submodelInit) == 0x9AC0);
static_assert(offsetof(ActorDataLady, newFirstVar) == 0xB8C0);
static_assert(offsetof(ActorDataLady, newModelData) == 0xB8D0);
static_assert(offsetof(ActorDataLady, newModelPhysicsMetadataPool) == 0xE5D0);
static_assert(offsetof(ActorDataLady, newModelAllocationData) == 0xEB10);
static_assert(offsetof(ActorDataLady, newRecoveryData) == 0x12B10);
static_assert(offsetof(ActorDataLady, newDevilModels) == 0x12DB0);
static_assert(offsetof(ActorDataLady, newBodyPartData) == 0x12DD0);
static_assert(offsetof(ActorDataLady, newSubmodelData) == 0x13D90);
static_assert(offsetof(ActorDataLady, newSubmodelInit) == 0x19010);
static_assert(offsetof(ActorDataLady, newModelShadowData) == 0x19020);
static_assert(offsetof(ActorDataLady, newSubmodelShadowData) == 0x194A0);
static_assert(offsetof(ActorDataLady, newDevilModelPhysicsMetadataPool) == 0x19CE0);
static_assert(offsetof(ActorDataLady, newDevilSubmodelPhysicsData) == 0x1A280);
static_assert(offsetof(ActorDataLady, newDevilSubmodelPhysicsLinkData) == 0x1ABE0);
static_assert(offsetof(ActorDataLady, newWeapons) == 0x1C9E0);
static_assert(offsetof(ActorDataLady, newWeaponData) == 0x1C9F0);
static_assert(offsetof(ActorDataLady, newWeaponStatus) == 0x1CA40);
static_assert(offsetof(ActorDataLady, newWeaponLevels) == 0x1CA70);
static_assert(offsetof(ActorDataLady, newWeaponTimers) == 0x1CAA0);
static_assert(offsetof(ActorDataLady, newIsClone) == 0x1CAC8);
static_assert(offsetof(ActorDataLady, newPlayer) == 0x1CACC);
static_assert(offsetof(ActorDataLady, newEntity) == 0x1CACD);
static_assert(offsetof(ActorDataLady, newForceFiles) == 0x1CACE);
static_assert(offsetof(ActorDataLady, newForceFilesCharacter) == 0x1CACF);
static_assert(offsetof(ActorDataLady, newGamepad) == 0x1CAD0);
static_assert(offsetof(ActorDataLady, newButtonMask) == 0x1CAD1);
static_assert(offsetof(ActorDataLady, newEnableRightStick) == 0x1CAD3);
static_assert(offsetof(ActorDataLady, newEnableLeftStick) == 0x1CAD4);
static_assert(offsetof(ActorDataLady, newExecuteStyleSwitch) == 0x1CAD5);
static_assert(offsetof(ActorDataLady, newEnable) == 0x1CAD6);
static_assert(offsetof(ActorDataLady, newAirStingerCount) == 0x1CAD7);
static_assert(offsetof(ActorDataLady, newEffectIndices) == 0x1CAE0);
static_assert(offsetof(ActorDataLady, newLastVar) == 0x1CB00);

static_assert(offsetof(ActorDataVergil, status) == 8);
static_assert(offsetof(ActorDataVergil, character) == 0x78);
static_assert(offsetof(ActorDataVergil, position) == 0x80);
static_assert(offsetof(ActorDataVergil, pull) == 0x94);
static_assert(offsetof(ActorDataVergil, pullMultiplier) == 0xA4);
static_assert(offsetof(ActorDataVergil, rotation) == 0xC0);
static_assert(offsetof(ActorDataVergil, id) == 0x118);
static_assert(offsetof(ActorDataVergil, isClone) == 0x11C);
static_assert(offsetof(ActorDataVergil, visible) == 0x120);
static_assert(offsetof(ActorDataVergil, var_1C0) == 0x1C0);
static_assert(offsetof(ActorDataVergil, var_1C4) == 0x1C4);
static_assert(offsetof(ActorDataVergil, modelData) == 0x200);
static_assert(offsetof(ActorDataVergil, modelPhysicsMetadataPool) == 0x1880);
static_assert(offsetof(ActorDataVergil, modelAllocationDataCount) == 0x1B80);
static_assert(offsetof(ActorDataVergil, modelAllocationData) == 0x1B88);
static_assert(offsetof(ActorDataVergil, motionSpeed) == 0x3894);
static_assert(offsetof(ActorDataVergil, motionSpeedMultiplier) == 0x3898);
static_assert(offsetof(ActorDataVergil, motionArchives) == 0x38A0);
static_assert(offsetof(ActorDataVergil, motionData) == 0x39B0);
static_assert(offsetof(ActorDataVergil, motionDataMirror) == 0x39B4);
static_assert(offsetof(ActorDataVergil, var_39BC) == 0x39BC);
static_assert(offsetof(ActorDataVergil, var_39C0) == 0x39C0);
static_assert(offsetof(ActorDataVergil, nextActionRequestPolicy) == 0x39D0);
static_assert(offsetof(ActorDataVergil, var_3A10) == 0x3A10);
static_assert(offsetof(ActorDataVergil, shadow) == 0x3A18);
static_assert(offsetof(ActorDataVergil, lastShadow) == 0x3A1C);
static_assert(offsetof(ActorDataVergil, color) == 0x3A28);
static_assert(offsetof(ActorDataVergil, recoveryData) == 0x3B00);
static_assert(offsetof(ActorDataVergil, var_3C50) == 0x3C50);
static_assert(offsetof(ActorDataVergil, actionData) == 0x3DD0);
static_assert(offsetof(ActorDataVergil, eventData) == 0x3E00);
static_assert(offsetof(ActorDataVergil, var_3E10) == 0x3E10);
static_assert(offsetof(ActorDataVergil, motionTimer) == 0x3E34);
static_assert(offsetof(ActorDataVergil, idleTimer) == 0x3E38);
static_assert(offsetof(ActorDataVergil, permissions) == 0x3E60);
static_assert(offsetof(ActorDataVergil, state) == 0x3E64);
static_assert(offsetof(ActorDataVergil, lastState) == 0x3E68);
static_assert(offsetof(ActorDataVergil, activeModelIndex) == 0x3E6C);
static_assert(offsetof(ActorDataVergil, queuedModelIndex) == 0x3E70);
static_assert(offsetof(ActorDataVergil, devilModels) == 0x3E74);
static_assert(offsetof(ActorDataVergil, modelState) == 0x3E80);
static_assert(offsetof(ActorDataVergil, lockOn) == 0x3E84);
static_assert(offsetof(ActorDataVergil, activeModelIndexMirror) == 0x3E88);
static_assert(offsetof(ActorDataVergil, activeDevil) == 0x3E8C);
static_assert(offsetof(ActorDataVergil, airRaid) == 0x3E90);
static_assert(offsetof(ActorDataVergil, mode) == 0x3E94);
static_assert(offsetof(ActorDataVergil, devil) == 0x3E9B);
static_assert(offsetof(ActorDataVergil, costume) == 0x3E9E);
static_assert(offsetof(ActorDataVergil, neroAngelo) == 0x3E9F);
static_assert(offsetof(ActorDataVergil, useHolyWater) == 0x3EA4);
static_assert(offsetof(ActorDataVergil, magicPoints) == 0x3EB8);
static_assert(offsetof(ActorDataVergil, maxMagicPoints) == 0x3EBC);
static_assert(offsetof(ActorDataVergil, var_3EC4) == 0x3EC4);
static_assert(offsetof(ActorDataVergil, var_3EC8) == 0x3EC8);
static_assert(offsetof(ActorDataVergil, var_3ED2) == 0x3ED2);
static_assert(offsetof(ActorDataVergil, cameraDirection) == 0x3ED8);
static_assert(offsetof(ActorDataVergil, airHikeCount) == 0x3F11);
static_assert(offsetof(ActorDataVergil, kickJumpCount) == 0x3F12);
static_assert(offsetof(ActorDataVergil, wallHikeCount) == 0x3F13);
static_assert(offsetof(ActorDataVergil, var_3F19) == 0x3F19);
static_assert(offsetof(ActorDataVergil, action) == 0x3FA4);
static_assert(offsetof(ActorDataVergil, lastAction) == 0x3FA5);
static_assert(offsetof(ActorDataVergil, bufferedAction) == 0x3FA8);
static_assert(offsetof(ActorDataVergil, chainCount) == 0x3FAC);
static_assert(offsetof(ActorDataVergil, expertise) == 0x3FEC);
static_assert(offsetof(ActorDataVergil, maxHitPoints) == 0x40EC);
static_assert(offsetof(ActorDataVergil, hitPoints) == 0x411C);
static_assert(offsetof(ActorDataVergil, targetBaseAddr) == 0x6328);
static_assert(offsetof(ActorDataVergil, style) == 0x6338);
static_assert(offsetof(ActorDataVergil, var_6340) == 0x6340);
static_assert(offsetof(ActorDataVergil, styleLevel) == 0x6358);
static_assert(offsetof(ActorDataVergil, airTrickCount) == 0x635E);
static_assert(offsetof(ActorDataVergil, trickUpCount) == 0x635F);
static_assert(offsetof(ActorDataVergil, trickDownCount) == 0x6360);
static_assert(offsetof(ActorDataVergil, quicksilver) == 0x6361);
static_assert(offsetof(ActorDataVergil, doppelganger) == 0x6362);
static_assert(offsetof(ActorDataVergil, styleExperience) == 0x6364);
static_assert(offsetof(ActorDataVergil, var_6410) == 0x6410);
static_assert(offsetof(ActorDataVergil, var_6438) == 0x6438);
static_assert(offsetof(ActorDataVergil, var_6440) == 0x6440);
static_assert(offsetof(ActorDataVergil, cloneRate) == 0x6450);
static_assert(offsetof(ActorDataVergil, var_6454) == 0x6454);
static_assert(offsetof(ActorDataVergil, var_6458) == 0x6458);
static_assert(offsetof(ActorDataVergil, cloneBaseAddr) == 0x6478);
static_assert(offsetof(ActorDataVergil, cloneIsControlledByPlayer) == 0x6480);
static_assert(offsetof(ActorDataVergil, activeMeleeWeaponIndex) == 0x6484);
static_assert(offsetof(ActorDataVergil, queuedMeleeWeaponIndex) == 0x6488);
static_assert(offsetof(ActorDataVergil, weapons) == 0x6498);
static_assert(offsetof(ActorDataVergil, weaponData) == 0x64A0);
static_assert(offsetof(ActorDataVergil, weaponStatus) == 0x64C8);
static_assert(offsetof(ActorDataVergil, weaponLevels) == 0x64DC);
static_assert(offsetof(ActorDataVergil, weaponTimers) == 0x64F4);
static_assert(offsetof(ActorDataVergil, meleeWeaponSwitchTimeout) == 0x6508);
static_assert(offsetof(ActorDataVergil, rangedWeaponSwitchTimeout) == 0x650C);
static_assert(offsetof(ActorDataVergil, styleRank) == 0x6510);
static_assert(offsetof(ActorDataVergil, styleMeter) == 0x6514);
static_assert(offsetof(ActorDataVergil, inputData) == 0x6674);
static_assert(offsetof(ActorDataVergil, bodyPartData) == 0x6950);
static_assert(offsetof(ActorDataVergil, var_7250) == 0x7250);
static_assert(offsetof(ActorDataVergil, collisionIndex) == 0x7254);
static_assert(offsetof(ActorDataVergil, interactionData) == 0x7460);
static_assert(offsetof(ActorDataVergil, buttons) == 0x74E0);
static_assert(offsetof(ActorDataVergil, rightStickPosition) == 0x74F8);
static_assert(offsetof(ActorDataVergil, rightStickRadius) == 0x74FA);
static_assert(offsetof(ActorDataVergil, leftStickPosition) == 0x7508);
static_assert(offsetof(ActorDataVergil, leftStickRadius) == 0x750A);
static_assert(offsetof(ActorDataVergil, actorCameraDirection) == 0x750C);
static_assert(offsetof(ActorDataVergil, leftStickDirection) == 0x751C);
static_assert(offsetof(ActorDataVergil, submodelData) == 0x7540);
static_assert(offsetof(ActorDataVergil, submodelInit) == 0x9AC0);
static_assert(offsetof(ActorDataVergil, modelShadowData) == 0x9AF0);
static_assert(offsetof(ActorDataVergil, submodelShadowData) == 0x9D30);
static_assert(offsetof(ActorDataVergil, submodelPhysicsMetadataPool) == 0xA0F0);
static_assert(offsetof(ActorDataVergil, submodelPhysicsData) == 0xA230);
static_assert(offsetof(ActorDataVergil, modelMetadata) == 0xB640);
static_assert(offsetof(ActorDataVergil, newFirstVar) == 0xB8C0);
static_assert(offsetof(ActorDataVergil, newModelData) == 0xB8D0);
static_assert(offsetof(ActorDataVergil, newModelPhysicsMetadataPool) == 0xE5D0);
static_assert(offsetof(ActorDataVergil, newModelAllocationData) == 0xEB10);
static_assert(offsetof(ActorDataVergil, newRecoveryData) == 0x12B10);
static_assert(offsetof(ActorDataVergil, newDevilModels) == 0x12DB0);
static_assert(offsetof(ActorDataVergil, newBodyPartData) == 0x12DD0);
static_assert(offsetof(ActorDataVergil, newSubmodelData) == 0x13D90);
static_assert(offsetof(ActorDataVergil, newSubmodelInit) == 0x19010);
static_assert(offsetof(ActorDataVergil, newModelShadowData) == 0x19020);
static_assert(offsetof(ActorDataVergil, newSubmodelShadowData) == 0x194A0);
static_assert(offsetof(ActorDataVergil, newDevilModelPhysicsMetadataPool) == 0x19CE0);
static_assert(offsetof(ActorDataVergil, newDevilSubmodelPhysicsData) == 0x1A280);
static_assert(offsetof(ActorDataVergil, newDevilSubmodelPhysicsLinkData) == 0x1ABE0);
static_assert(offsetof(ActorDataVergil, newWeapons) == 0x1C9E0);
static_assert(offsetof(ActorDataVergil, newWeaponData) == 0x1C9F0);
static_assert(offsetof(ActorDataVergil, newWeaponStatus) == 0x1CA40);
static_assert(offsetof(ActorDataVergil, newWeaponLevels) == 0x1CA70);
static_assert(offsetof(ActorDataVergil, newWeaponTimers) == 0x1CAA0);
static_assert(offsetof(ActorDataVergil, newIsClone) == 0x1CAC8);
static_assert(offsetof(ActorDataVergil, newPlayer) == 0x1CACC);
static_assert(offsetof(ActorDataVergil, newEntity) == 0x1CACD);
static_assert(offsetof(ActorDataVergil, newForceFiles) == 0x1CACE);
static_assert(offsetof(ActorDataVergil, newForceFilesCharacter) == 0x1CACF);
static_assert(offsetof(ActorDataVergil, newGamepad) == 0x1CAD0);
static_assert(offsetof(ActorDataVergil, newButtonMask) == 0x1CAD1);
static_assert(offsetof(ActorDataVergil, newEnableRightStick) == 0x1CAD3);
static_assert(offsetof(ActorDataVergil, newEnableLeftStick) == 0x1CAD4);
static_assert(offsetof(ActorDataVergil, newExecuteStyleSwitch) == 0x1CAD5);
static_assert(offsetof(ActorDataVergil, newEnable) == 0x1CAD6);
static_assert(offsetof(ActorDataVergil, newAirStingerCount) == 0x1CAD7);
static_assert(offsetof(ActorDataVergil, newEffectIndices) == 0x1CAE0);
static_assert(offsetof(ActorDataVergil, newLastVar) == 0x1CB00);

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
