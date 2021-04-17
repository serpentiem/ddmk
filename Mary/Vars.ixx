export module Vars;

import Core;

#include "../Core/Macros.h"









export enum PLAYER
{
	MAX_PLAYER = 4,
};

export enum ENTITY
{
	ENTITY_MAIN,
	ENTITY_CLONE,
	MAX_ENTITY,
};

export enum CLONE_STATUS
{
	CLONE_STATUS_IDLE,
	CLONE_STATUS_ACTIVE,
	CLONE_STATUS_DECOMMISSION,
};

export enum WALL_HIKE_DIRECTION
{
	WALL_HIKE_DIRECTION_RIGHT,
	WALL_HIKE_DIRECTION_LEFT,
	WALL_HIKE_DIRECTION_FORWARD,
};

export enum CopyStateFlags
{
	CopyStateFlags_EventData = 1 << 0,
	CopyStateFlags_Mode      = 1 << 1,
};

export enum
{
	DEVIL_FLUX_START = 1,
	DEVIL_FLUX_END   = 2,
};

export enum
{
	STYLE_RANK_NONE,
	STYLE_RANK_DOPE,
	STYLE_RANK_CRAZY,
	STYLE_RANK_BLAST,
	STYLE_RANK_ALRIGHT,
	STYLE_RANK_SWEET,
	STYLE_RANK_SHOWTIME,
	STYLE_RANK_STYLISH,
	STYLE_RANK_COUNT,
};



export enum WEAPON_SWITCH_TYPE
{
	WEAPON_SWITCH_TYPE_LINEAR,
	WEAPON_SWITCH_TYPE_ARBITRARY,
	WEAPON_SWITCH_TYPE_COUNT,
};

export enum ACTOR_DATA_SIZE
{
	ACTOR_DATA_SIZE_DANTE  = 47296,
	ACTOR_DATA_SIZE_BOB    = 46720,
	ACTOR_DATA_SIZE_LADY   = 33408,
	ACTOR_DATA_SIZE_VERGIL = 47296,
};

export enum DOT_SHADOW
{
	DOT_SHADOW_ENABLE,
	DOT_SHADOW_DISABLE,
	DOT_SHADOW_DISABLE_ACTOR_ONLY,
};

export enum
{
	PLAYER_COUNT = 4,
	ENTITY_COUNT = 2,
	CHARACTER_COUNT = 3,
	STYLE_COUNT = 4,
	WEAPON_COUNT = 10,
};

export enum FILE_MODE
{
	FILE_MODE_MEMORY,
	FILE_MODE_ARCHIVE,
	FILE_MODE_LOCAL,
};

export enum
{
	CHANNEL_SYSTEM,
	CHANNEL_COMMON,
	CHANNEL_STYLE_WEAPON,
	CHANNEL_WEAPON1,
	CHANNEL_WEAPON2,
	CHANNEL_WEAPON3,
	CHANNEL_WEAPON4,
	CHANNEL_ENEMY,
	CHANNEL_ROOM,
	CHANNEL_MUSIC,
	CHANNEL_DEMO,
	MAX_CHANNEL,
};

export enum WEAPON_STATUS
{
	WEAPON_STATUS_READY,
	WEAPON_STATUS_ACTIVE,
	WEAPON_STATUS_RETURN,
	WEAPON_STATUS_END,
	WEAPON_STATUS_DISABLED,
};

export enum MODE_
{
	MODE_EASY,
	MODE_NORMAL,
	MODE_HARD,
	MODE_VERY_HARD,
	MODE_DANTE_MUST_DIE,
	MAX_MODE,
};

export enum CHAR_
{
	CHAR_DANTE,
	CHAR_BOB,
	CHAR_LADY,
	CHAR_VERGIL,
	CHAR_VOID = 255,
	MAX_CHAR = 4,
};

export enum COSTUME_
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
	COSTUME_VERGIL_NERO_ANGELO,
	COSTUME_VERGIL_NERO_ANGELO_INFINITE_MAGIC_POINTS,
	MAX_COSTUME = 8,
	MAX_COSTUME_DANTE = 8,
	MAX_COSTUME_BOB = 1,
	MAX_COSTUME_LADY = 2,
	MAX_COSTUME_VERGIL = 5,
};

export enum DEVIL
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

export enum STYLE
{
	STYLE_SWORDMASTER,
	STYLE_GUNSLINGER,
	STYLE_TRICKSTER,
	STYLE_ROYALGUARD,
	STYLE_QUICKSILVER,
	STYLE_DOPPELGANGER,
	STYLE_DARK_SLAYER = 2,
	MAX_STYLE = 6,
};

export enum WEAPON
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
	WEAPON_YAMATO_FORCE_EDGE,
	WEAPON_YAMATO_BOB,
	MAX_WEAPON,
	WEAPON_VOID = 255,
};

export enum
{
	WEAPON_COUNT_DANTE = 10,
	WEAPON_COUNT_BOB = 1,
	WEAPON_COUNT_VERGIL = 3,
	MELEE_WEAPON_COUNT = 5,
	MELEE_WEAPON_COUNT_DANTE = 5,
	MELEE_WEAPON_COUNT_BOB = 1,
	MELEE_WEAPON_COUNT_VERGIL = 3,
	RANGED_WEAPON_COUNT = 5,
	RANGED_WEAPON_COUNT_DANTE = 5,
};

// @Todo: Update.
export enum MOTION_GROUP_
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
	MOTION_GROUP_BOB_YAMATO = 31,
	MOTION_GROUP_LADY_BASE = 0,
	MOTION_GROUP_LADY_DAMAGE,
	MOTION_GROUP_LADY_TAUNTS,
	MOTION_GROUP_VERGIL_BASE = 0,
	MOTION_GROUP_VERGIL_DAMAGE,
	MOTION_GROUP_VERGIL_TAUNTS,
	MOTION_GROUP_VERGIL_YAMATO,
	MOTION_GROUP_VERGIL_BEOWULF,
	MOTION_GROUP_VERGIL_YAMATO_FORCE_EDGE,
	MOTION_GROUP_VERGIL_DARK_SLAYER,
	MOTION_GROUP_VERGIL_NERO_ANGELO_YAMATO,
	MOTION_GROUP_VERGIL_NERO_ANGELO_BEOWULF,
	MOTION_GROUP_VERGIL_NERO_ANGELO_FORCE_EDGE,
	MOTION_GROUP_IN_GAME_CUTSCENE = 33,
	MAX_MOTION_GROUP = 34,
};

export enum NEXT_ACTION_REQUEST_POLICY
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

export enum ACTION
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
	ACTION_VERGIL_YAMATO_FORCE_EDGE_COMBO_PART_1 = 30,
	ACTION_VERGIL_YAMATO_FORCE_EDGE_COMBO_PART_2,
	ACTION_VERGIL_YAMATO_FORCE_EDGE_COMBO_PART_3,
	ACTION_VERGIL_YAMATO_FORCE_EDGE_COMBO_PART_4,
	ACTION_VERGIL_YAMATO_FORCE_EDGE_HELM_BREAKER_LEVEL_1,
	ACTION_VERGIL_YAMATO_FORCE_EDGE_HELM_BREAKER_LEVEL_2,
	ACTION_VERGIL_YAMATO_FORCE_EDGE_HIGH_TIME,
	ACTION_VERGIL_YAMATO_FORCE_EDGE_HIGH_TIME_LAUNCH,
	ACTION_VERGIL_YAMATO_FORCE_EDGE_STINGER_LEVEL_1,
	ACTION_VERGIL_YAMATO_FORCE_EDGE_STINGER_LEVEL_2,
	ACTION_VERGIL_YAMATO_FORCE_EDGE_ROUND_TRIP,
	ACTION_VERGIL_YAMATO_FORCE_EDGE_KICK,
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

export enum PERMISSION
{
	PERMISSION_UPDATE = 1,
	PERMISSION_WALK_RUN = 2,
	PERMISSION_JUMP_ROLL = 8,
	PERMISSION_TARGET = 0x10,
	PERMISSION_RELEASE = 0x20,
	PERMISSION_INTERACTION_STYLE_ATTACK = 0x400,
	PERMISSION_TRICKSTER_DARK_SLAYER = 0x1000000,
};

export enum STATE
{
	STATE_ON_FLOOR = 1,
	STATE_IN_AIR = 2,
	STATE_BUSY = 0x10000,
};

export enum BODY_PART
{
	LOWER_BODY,
	UPPER_BODY,
	MAX_BODY_PART,
};

export enum HUD_TOP
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

export enum HUD_BOTTOM
{
	HUD_BOTTOM_RANGED_WEAPON_1,
	HUD_BOTTOM_RANGED_WEAPON_2,
	HUD_BOTTOM_MELEE_WEAPON_1,
	HUD_BOTTOM_MELEE_WEAPON_2,
};

// $CacheFileStart

export enum
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
	snd_com0,
	snd_com0a,
	snd_sty02,
	snd_sty03,
	snd_sty04,
	snd_sty05,
	snd_sty06,
	snd_wp00b,
	snd_wp01b,
	snd_wp02b,
	snd_wp03b,
	snd_wp04b,
	snd_wp05b,
	snd_wp06b,
	snd_wp07b,
	snd_wp08b,
	snd_wp09b,
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
	snd_com3,
	snd_com3a,
	snd_sty07,
	snd_sty08,
	snd_wp11a,
	snd_wp11b,
	snd_wp12a,
	snd_wp12b,
	snd_wp13a,
	snd_wp13b,
	em000,
	em006,
	em007,
	em008,
	em010,
	em011,
	em012,
	em013,
	em014,
	em016,
	em017,
	em021,
	em023,
	em025,
	em026,
	em027,
	em028,
	em029,
	em030,
	em031,
	em032,
	em034,
	em035,
	em037,
	snd_em00a,
	snd_em00b,
	snd_em06,
	snd_em07,
	snd_em08,
	snd_em10,
	snd_em11,
	snd_em12,
	snd_em13,
	snd_em14,
	snd_em16,
	snd_em17,
	snd_em21,
	snd_em23,
	snd_em25,
	snd_em26,
	snd_em27,
	snd_em28,
	snd_em29,
	snd_em30,
	snd_em31,
	snd_em32,
	snd_em34,
	snd_em35,
	snd_em37,
	snd_emsr,
	snd_stay,
	id100,
	id100V,
	CACHE_FILE_COUNT,
};

export struct CacheFileHelper
{
	const char * filename;
	const char * typeName;
};

export constexpr CacheFileHelper cacheFileHelpers[CACHE_FILE_COUNT] =
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
	{ "snd_com0.pac", "se\\snd_com0.pac" },
	{ "snd_com0a.pac", "se\\snd_com0a.pac" },
	{ "snd_sty02.pac", "se\\snd_sty02.pac" },
	{ "snd_sty03.pac", "se\\snd_sty03.pac" },
	{ "snd_sty04.pac", "se\\snd_sty04.pac" },
	{ "snd_sty05.pac", "se\\snd_sty05.pac" },
	{ "snd_sty06.pac", "se\\snd_sty06.pac" },
	{ "snd_wp00b.pac", "se\\snd_wp00b.pac" },
	{ "snd_wp01b.pac", "se\\snd_wp01b.pac" },
	{ "snd_wp02b.pac", "se\\snd_wp02b.pac" },
	{ "snd_wp03b.pac", "se\\snd_wp03b.pac" },
	{ "snd_wp04b.pac", "se\\snd_wp04b.pac" },
	{ "snd_wp05b.pac", "se\\snd_wp05b.pac" },
	{ "snd_wp06b.pac", "se\\snd_wp06b.pac" },
	{ "snd_wp07b.pac", "se\\snd_wp07b.pac" },
	{ "snd_wp08b.pac", "se\\snd_wp08b.pac" },
	{ "snd_wp09b.pac", "se\\snd_wp09b.pac" },
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
	{ "snd_com3.pac", "se\\snd_com3.pac" },
	{ "snd_com3a.pac", "se\\snd_com3a.pac" },
	{ "snd_sty07.pac", "se\\snd_sty07.pac" },
	{ "snd_sty08.pac", "se\\snd_sty08.pac" },
	{ "snd_wp11a.pac", "se\\snd_wp11a.pac" },
	{ "snd_wp11b.pac", "se\\snd_wp11b.pac" },
	{ "snd_wp12a.pac", "se\\snd_wp12a.pac" },
	{ "snd_wp12b.pac", "se\\snd_wp12b.pac" },
	{ "snd_wp13a.pac", "se\\snd_wp13a.pac" },
	{ "snd_wp13b.pac", "se\\snd_wp13b.pac" },
	{ "em000.pac", "obj\\em000.pac" },
	{ "em006.pac", "obj\\em006.pac" },
	{ "em007.pac", "obj\\em007.pac" },
	{ "em008.pac", "obj\\em008.pac" },
	{ "em010.pac", "obj\\em010.pac" },
	{ "em011.pac", "obj\\em011.pac" },
	{ "em012.pac", "obj\\em012.pac" },
	{ "em013.pac", "obj\\em013.pac" },
	{ "em014.pac", "obj\\em014.pac" },
	{ "em016.pac", "obj\\em016.pac" },
	{ "em017.pac", "obj\\em017.pac" },
	{ "em021.pac", "obj\\em021.pac" },
	{ "em023.pac", "obj\\em023.pac" },
	{ "em025.pac", "obj\\em025.pac" },
	{ "em026.pac", "obj\\em026.pac" },
	{ "em027.pac", "obj\\em027.pac" },
	{ "em028.pac", "obj\\em028.pac" },
	{ "em029.pac", "obj\\em029.pac" },
	{ "em030.pac", "obj\\em030.pac" },
	{ "em031.pac", "obj\\em031.pac" },
	{ "em032.pac", "obj\\em032.pac" },
	{ "em034.pac", "obj\\em034.pac" },
	{ "em035.pac", "obj\\em035.pac" },
	{ "em037.pac", "obj\\em037.pac" },
	{ "snd_em00a.pac", "se\\snd_em00a.pac" },
	{ "snd_em00b.pac", "se\\snd_em00b.pac" },
	{ "snd_em06.pac", "se\\snd_em06.pac" },
	{ "snd_em07.pac", "se\\snd_em07.pac" },
	{ "snd_em08.pac", "se\\snd_em08.pac" },
	{ "snd_em10.pac", "se\\snd_em10.pac" },
	{ "snd_em11.pac", "se\\snd_em11.pac" },
	{ "snd_em12.pac", "se\\snd_em12.pac" },
	{ "snd_em13.pac", "se\\snd_em13.pac" },
	{ "snd_em14.pac", "se\\snd_em14.pac" },
	{ "snd_em16.pac", "se\\snd_em16.pac" },
	{ "snd_em17.pac", "se\\snd_em17.pac" },
	{ "snd_em21.pac", "se\\snd_em21.pac" },
	{ "snd_em23.pac", "se\\snd_em23.pac" },
	{ "snd_em25.pac", "se\\snd_em25.pac" },
	{ "snd_em26.pac", "se\\snd_em26.pac" },
	{ "snd_em27.pac", "se\\snd_em27.pac" },
	{ "snd_em28.pac", "se\\snd_em28.pac" },
	{ "snd_em29.pac", "se\\snd_em29.pac" },
	{ "snd_em30.pac", "se\\snd_em30.pac" },
	{ "snd_em31.pac", "se\\snd_em31.pac" },
	{ "snd_em32.pac", "se\\snd_em32.pac" },
	{ "snd_em34.pac", "se\\snd_em34.pac" },
	{ "snd_em35.pac", "se\\snd_em35.pac" },
	{ "snd_em37.pac", "se\\snd_em37.pac" },
	{ "snd_emsr.pac", "se\\snd_emsr.pac" },
	{ "snd_stay.pac", "se\\snd_stay.pac" },
	{ "id100.pac", "id\\id100\\id100.pac" },
	{ "id100V.pac", "id\\id100\\id100V.pac" },
};

static_assert(countof(cacheFileHelpers) == CACHE_FILE_COUNT);

// $CacheFileEnd

export enum SCENE
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

export enum EVENT
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

export enum SUBEVENT
{
	SUBEVENT_MISSION_START  = 7,
	SUBEVENT_MISSION_SELECT = 8,
};

export enum GAMEPAD
{
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

export enum DIRECTION
{
	DIRECTION_UP,
	DIRECTION_RIGHT,
	DIRECTION_DOWN,
	DIRECTION_LEFT,
	MAX_DIRECTION,
};

export enum LEFT_STICK
{
	LEFT_STICK_DEADZONE = 52,
};

export enum RIGHT_STICK
{
	RIGHT_STICK_DEADZONE = 70,
};

export enum BINDING
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

export enum DEVIL_SPEED
{
	DEVIL_SPEED_DANTE_REBELLION,
	DEVIL_SPEED_DANTE_CERBERUS,
	DEVIL_SPEED_DANTE_AGNI_RUDRA,
	DEVIL_SPEED_DANTE_NEVAN,
	DEVIL_SPEED_DANTE_BEOWULF,
	DEVIL_SPEED_DANTE_SPARDA,
	DEVIL_SPEED_VERGIL_YAMATO = 0,
	DEVIL_SPEED_VERGIL_BEOWULF,
	DEVIL_SPEED_VERGIL_YAMATO_FORCE_EDGE,
	DEVIL_SPEED_VERGIL_NERO_ANGELO_YAMATO,
	DEVIL_SPEED_VERGIL_NERO_ANGELO_BEOWULF,
};

export enum ACTOR_EVENT
{
	ACTOR_EVENT_DANTE_AIR_HIKE = 7,
	ACTOR_EVENT_DANTE_DASH = 22,
	ACTOR_EVENT_DANTE_SKY_STAR,
	ACTOR_EVENT_DANTE_AIR_TRICK,
	ACTOR_EVENT_VERGIL_AIR_TRICK = 27,
	ACTOR_EVENT_VERGIL_TRICK_UP,
	ACTOR_EVENT_VERGIL_TRICK_DOWN,
};

export enum ACTOR_MODE
{
	ACTOR_MODE_DEFAULT,
	ACTOR_MODE_MISSION_12,
	ACTOR_MODE_MISSION_18,
	ACTOR_MODE_MISSION_19,
};

// @Todo: Change to count.

export constexpr uint16 costumeFileIdsDante[MAX_COSTUME_DANTE] =
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

export constexpr uint16 costumeFileIdsBob[MAX_COSTUME_BOB] =
{
	pl001,
};

export constexpr uint16 costumeFileIdsLady[MAX_COSTUME_LADY] =
{
	pl002,
	em034,
};

export constexpr uint16 costumeFileIdsVergil[MAX_COSTUME_VERGIL] =
{
	pl021,
	pl023,
	pl021,
	pl026,
	pl026,
};

export constexpr uint8 costumeCounts[MAX_CHAR] =
{
	MAX_COSTUME_DANTE,
	MAX_COSTUME_BOB,
	MAX_COSTUME_LADY,
	MAX_COSTUME_VERGIL,
};

export constexpr uint16 devilFileIdsDante[6] =
{
	pl005,
	pl006,
	pl007,
	pl008,
	pl009,
	pl017,
};

export constexpr uint8 weaponDevilIds[MAX_WEAPON] =
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

export constexpr uint32 hudTopOffs[] =
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

export constexpr uint32 hudBottomOffs[] =
{
	0x880,
	0x1000,
	0x1780,
	0x1F00,
};

#define _(size) struct { byte8 Prep_Merge(padding_, __LINE__)[size]; }

#pragma pack(push, 1)

IntroduceSizeStruct(32);
IntroduceSizeStruct(112);
IntroduceSizeStruct(192);
IntroduceSizeStruct(240);
IntroduceSizeStruct(288);
IntroduceSizeStruct(768);

// $SessionDataStart

export struct SessionData
{
	uint32 mission; // 0
	_(8);
	uint32 mode; // 0xC
	bool oneHitKill; // 0x10
	_(1);
	bool enableTutorial; // 0x12
	bool useGoldOrb; // 0x13
	uint8 character; // 0x14
	_(7);
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
	float hitPoints; // 0xD4
	float magicPoints; // 0xD8
	uint32 style; // 0xDC
	uint32 styleLevel[6]; // 0xE0
	float styleExperience[6]; // 0xF8
	byte32 expertise[8]; // 0x110
};

static_assert(offsetof(SessionData, mission) == 0);
static_assert(offsetof(SessionData, mode) == 0xC);
static_assert(offsetof(SessionData, oneHitKill) == 0x10);
static_assert(offsetof(SessionData, enableTutorial) == 0x12);
static_assert(offsetof(SessionData, useGoldOrb) == 0x13);
static_assert(offsetof(SessionData, character) == 0x14);
static_assert(offsetof(SessionData, bloodyPalace) == 0x1C);
static_assert(offsetof(SessionData, goldOrbCount) == 0x35);
static_assert(offsetof(SessionData, unlock) == 0x46);
static_assert(offsetof(SessionData, weapons) == 0x84);
static_assert(offsetof(SessionData, costume) == 0xD0);
static_assert(offsetof(SessionData, unlockDevilTrigger) == 0xD1);
static_assert(offsetof(SessionData, hitPoints) == 0xD4);
static_assert(offsetof(SessionData, magicPoints) == 0xD8);
static_assert(offsetof(SessionData, style) == 0xDC);
static_assert(offsetof(SessionData, styleLevel) == 0xE0);
static_assert(offsetof(SessionData, styleExperience) == 0xF8);
static_assert(offsetof(SessionData, expertise) == 0x110);
static_assert(sizeof(SessionData) == 304);

// $SessionDataEnd

// $MissionDataStart

export struct MissionData
{
	_(56);
	uint32 orbs; // 0x38
	_(108);
	uint32 frameCount; // 0xA8
	uint32 damage; // 0xAC
	uint32 orbsCollected; // 0xB0
	uint32 itemsUsed; // 0xB4
	uint32 killCount; // 0xB8
	_(4);
};

static_assert(offsetof(MissionData, orbs) == 0x38);
static_assert(offsetof(MissionData, frameCount) == 0xA8);
static_assert(offsetof(MissionData, damage) == 0xAC);
static_assert(offsetof(MissionData, orbsCollected) == 0xB0);
static_assert(offsetof(MissionData, itemsUsed) == 0xB4);
static_assert(offsetof(MissionData, killCount) == 0xB8);
static_assert(sizeof(MissionData) == 192);

// $MissionDataEnd

// $MissionActorDataStart

export struct QueuedMissionActorData
{
	uint8 weapons[5]; // 0
	_(75);
	float hitPoints; // 0x50
	float magicPoints; // 0x54
	uint32 style; // 0x58
	uint32 styleLevel[6]; // 0x5C
	float styleExperience[6]; // 0x74
	byte32 expertise[8]; // 0x8C
};

static_assert(offsetof(QueuedMissionActorData, weapons) == 0);
static_assert(offsetof(QueuedMissionActorData, hitPoints) == 0x50);
static_assert(offsetof(QueuedMissionActorData, magicPoints) == 0x54);
static_assert(offsetof(QueuedMissionActorData, style) == 0x58);
static_assert(offsetof(QueuedMissionActorData, styleLevel) == 0x5C);
static_assert(offsetof(QueuedMissionActorData, styleExperience) == 0x74);
static_assert(offsetof(QueuedMissionActorData, expertise) == 0x8C);
static_assert(sizeof(QueuedMissionActorData) == 172);

export struct ActiveMissionActorData
{
	uint8 weapons[5]; // 0
	_(51);
	uint32 style; // 0x38
	uint32 styleLevel; // 0x3C
	byte32 expertise[8]; // 0x40
	float styleExperience; // 0x60
	float hitPoints; // 0x64
	float maxHitPoints; // 0x68
	float magicPoints; // 0x6C
	float maxMagicPoints; // 0x70
};

static_assert(offsetof(ActiveMissionActorData, weapons) == 0);
static_assert(offsetof(ActiveMissionActorData, style) == 0x38);
static_assert(offsetof(ActiveMissionActorData, styleLevel) == 0x3C);
static_assert(offsetof(ActiveMissionActorData, expertise) == 0x40);
static_assert(offsetof(ActiveMissionActorData, styleExperience) == 0x60);
static_assert(offsetof(ActiveMissionActorData, hitPoints) == 0x64);
static_assert(offsetof(ActiveMissionActorData, maxHitPoints) == 0x68);
static_assert(offsetof(ActiveMissionActorData, magicPoints) == 0x6C);
static_assert(offsetof(ActiveMissionActorData, maxMagicPoints) == 0x70);
static_assert(sizeof(ActiveMissionActorData) == 116);

// $MissionActorDataEnd

// $StyleDataStart

export struct StyleData
{
	uint32 rank; // 0
	float meter; // 4
	_(328);
	float quotient; // 0x150
	float dividend; // 0x154
	float divisor; // 0x158
	_(4);
};

static_assert(offsetof(StyleData, rank) == 0);
static_assert(offsetof(StyleData, meter) == 4);
static_assert(offsetof(StyleData, quotient) == 0x150);
static_assert(offsetof(StyleData, dividend) == 0x154);
static_assert(offsetof(StyleData, divisor) == 0x158);
static_assert(sizeof(StyleData) == 352);

// $StyleDataEnd

// @Todo: Create scripts.
export struct EventData
{
	_(24);
	uint32 room;
	uint32 position;
	uint32 event;
	_(8);
	uint32 subevent;
};

export struct NextEventData
{
	_(356);
	uint16 room;
	uint16 position;
};

// $CollisionDataStart

export struct CollisionData
{
	_(4);
	uint32 index; // 4
	_(520);
	vec4 data; // 0x210
	_(112);
};

static_assert(offsetof(CollisionData, index) == 4);
static_assert(offsetof(CollisionData, data) == 0x210);
static_assert(sizeof(CollisionData) == 656);

// $CollisionDataEnd

// $CameraDataStart

export struct CameraData
{
	_(176);
	byte8 * targetBaseAddr; // 0xB0
	_(24);
	float height; // 0xD0
	float tilt; // 0xD4
	float distance; // 0xD8
	_(4);
	float distanceLockOn; // 0xE0
	_(284);
};

static_assert(offsetof(CameraData, targetBaseAddr) == 0xB0);
static_assert(offsetof(CameraData, height) == 0xD0);
static_assert(offsetof(CameraData, tilt) == 0xD4);
static_assert(offsetof(CameraData, distance) == 0xD8);
static_assert(offsetof(CameraData, distanceLockOn) == 0xE0);
static_assert(sizeof(CameraData) == 512);

// $CameraDataEnd

// @Todo: Update if statements.
// @Todo: Create preprocess script.

// @Todo: Update.

// struct ArchiveData
// {
// 	byte8 signature[4];
// 	uint32 fileCount;
// 	uint32 fileOff[128];
// };

export struct ArchiveMetadata
{
	byte8 signature[4];
	uint32 fileCount;
	uint32 fileOffs[1];
};

// @Todo: FILE_DATA_STATUS

export enum
{
	FILE_DATA_STATUS_FREE,
	FILE_DATA_STATUS_IN_USE = 3,
};

export struct FileDataTypeData
{
	_(8);
	const char * typeName;
};

export struct FileData
{
	uint32 group;
	uint32 status;
	_(16);
	FileDataTypeData * typeDataAddr;
	byte8 * file;
	_(32);
};

static_assert(sizeof(FileData) == 72);

export struct FileDataMetadata
{
	void * funcAddrs;
	void * lastAddr;
	void * nextAddr;
	FileData * fileDataAddr;
	_(4);
	uint32 category;
	uint32 fileSetIndex;
	_(4);
};

static_assert(sizeof(FileDataMetadata) == 48);









export enum
{
	ARCHIVE_METADATA_SIZE   = 8,
	HEAD_METADATA_SIZE      = 32,
	PROG_SECT_ITEM_SIZE     = 14,
	PROG_SECT_METADATA_SIZE = 8,
	PROG_METADATA_SIZE      = 16,
	SMPL_ITEM_SIZE          = 12,
	SMPL_METADATA_SIZE      = 16,
	VAGI_ITEM_SIZE          = 16,
	VAGI_METADATA_SIZE      = 16,
	WAVE_METADATA_SIZE      = 64,
	SOUND_DATA_SIZE         = 24,
	DBST_METADATA_SIZE      = 16,
	DBST_ITEM_SIZE          = 32,
};

export enum
{
	PROG_SECT_REBELLION,
	PROG_SECT_CERBERUS,
	PROG_SECT_AGNI_RUDRA,
	PROG_SECT_NEVAN,
	PROG_SECT_BEOWULF_DANTE,
	PROG_SECT_EBONY_IVORY,
	PROG_SECT_SHOTGUN,
	PROG_SECT_ARTEMIS,
	PROG_SECT_SPIRAL,
	PROG_SECT_KALINA_ANN,
	PROG_SECT_YAMATO = 11,
	PROG_SECT_BEOWULF_VERGIL,
	PROG_SECT_YAMATO_FORCE_EDGE,
	PROG_SECT_SWORDMASTER = 100,
	PROG_SECT_GUNSLINGER,
	PROG_SECT_TRICKSTER,
	PROG_SECT_ROYALGUARD,
	PROG_SECT_QUICKSILVER,
	PROG_SECT_DOPPELGANGER,
	PROG_SECT_BATTLE_OF_BROTHERS,
	PROG_SECT_DARK_SLAYER,
	MAX_PROG_SECT,
};

export enum
{
	HELPER_COMMON_DANTE_DEFAULT,
	HELPER_COMMON_DANTE_NO_COAT,
	HELPER_COMMON_VERGIL_DEFAULT,
	HELPER_COMMON_VERGIL_NERO_ANGELO,
	HELPER_STYLE_WEAPON_DANTE,
	HELPER_STYLE_WEAPON_VERGIL_DEFAULT,
	HELPER_STYLE_WEAPON_VERGIL_NERO_ANGELO,
	HELPER_ENEMY_LESSER_ENEMIES,
	HELPER_ENEMY_GIGAPEDE,
	HELPER_ENEMY_CERBERUS,
	HELPER_ENEMY_AGNI_RUDRA,
	HELPER_ENEMY_NEVAN,
	HELPER_ENEMY_GERYON,
	HELPER_ENEMY_BEOWULF,
	HELPER_ENEMY_DOPPELGANGER,
	HELPER_ENEMY_ARKHAM,
	HELPER_ENEMY_LADY,
	HELPER_ENEMY_VERGIL,
	HELPER_ENEMY_JESTER,
	HELPER_COUNT,
};














// $EnemyStart

export enum
{
	ENEMY_PRIDE_1,
	ENEMY_PRIDE_2,
	ENEMY_PRIDE_3,
	ENEMY_PRIDE_4,
	ENEMY_GLUTTONY_1,
	ENEMY_GLUTTONY_2,
	ENEMY_GLUTTONY_3,
	ENEMY_GLUTTONY_4,
	ENEMY_LUST_1,
	ENEMY_LUST_2,
	ENEMY_LUST_3,
	ENEMY_LUST_4,
	ENEMY_SLOTH_1,
	ENEMY_SLOTH_2,
	ENEMY_SLOTH_3,
	ENEMY_SLOTH_4,
	ENEMY_WRATH_1,
	ENEMY_WRATH_2,
	ENEMY_WRATH_3,
	ENEMY_WRATH_4,
	ENEMY_GREED_1,
	ENEMY_GREED_2,
	ENEMY_GREED_3,
	ENEMY_GREED_4,
	ENEMY_ABYSS,
	ENEMY_ENVY,
	ENEMY_HELL_VANGUARD,
	ENEMY_UNKNOWN_0,
	ENEMY_ARACHNE,
	ENEMY_THE_FALLEN,
	ENEMY_DULLAHAN,
	ENEMY_ENIGMA,
	ENEMY_BLOOD_GOYLE,
	ENEMY_UNKNOWN_1,
	ENEMY_SOUL_EATER,
	ENEMY_DAMNED_CHESSMEN_PAWN,
	ENEMY_DAMNED_CHESSMEN_KNIGHT,
	ENEMY_DAMNED_CHESSMEN_BISHOP,
	ENEMY_DAMNED_CHESSMEN_ROOK,
	ENEMY_DAMNED_CHESSMEN_QUEEN,
	ENEMY_DAMNED_CHESSMEN_KING,
	ENEMY_GIGAPEDE,
	ENEMY_UNKNOWN_2,
	ENEMY_CERBERUS,
	ENEMY_AGNI_RUDRA_ALL,
	ENEMY_AGNI_RUDRA,
	ENEMY_AGNI_RUDRA_BLACK,
	ENEMY_AGNI_RUDRA_RED,
	ENEMY_AGNI_RUDRA_BLUE,
	ENEMY_NEVAN,
	ENEMY_GERYON,
	ENEMY_BEOWULF,
	ENEMY_DOPPELGANGER,
	ENEMY_ARKHAM,
	ENEMY_UNKNOWN_3,
	ENEMY_LADY,
	ENEMY_UNKNOWN_4,
	ENEMY_UNKNOWN_5,
	ENEMY_VERGIL,
	ENEMY_UNKNOWN_6,
	ENEMY_LEVIATHAN_HEART,
	ENEMY_LEVIATHAN_OTHER,
	ENEMY_JESTER,
	ENEMY_UNKNOWN_7,
	ENEMY_COUNT,
	CREATE_ENEMY_COUNT = 30,
};

export const char * enemyNames[] =
{
	"Pride 1",
	"Pride 2",
	"Pride 3",
	"Pride 4",
	"Gluttony 1",
	"Gluttony 2",
	"Gluttony 3",
	"Gluttony 4",
	"Lust 1",
	"Lust 2",
	"Lust 3",
	"Lust 4",
	"Sloth 1",
	"Sloth 2",
	"Sloth 3",
	"Sloth 4",
	"Wrath 1",
	"Wrath 2",
	"Wrath 3",
	"Wrath 4",
	"Greed 1",
	"Greed 2",
	"Greed 3",
	"Greed 4",
	"Abyss",
	"Envy",
	"Hell Vanguard",
	"Unknown",
	"Arachne",
	"The Fallen",
	"Dullahan",
	"Enigma",
	"Blood-Goyle",
	"Unknown",
	"Soul Eater",
	"Damned Chessmen Pawn",
	"Damned Chessmen Knight",
	"Damned Chessmen Bishop",
	"Damned Chessmen Rook",
	"Damned Chessmen Queen",
	"Damned Chessmen King",
	"Gigapede",
	"Unknown",
	"Cerberus",
	"Agni & Rudra All",
	"Agni & Rudra",
	"Agni & Rudra Black",
	"Agni & Rudra Red",
	"Agni & Rudra Blue",
	"Nevan",
	"Geryon",
	"Beowulf",
	"Doppelganger",
	"Arkham",
	"Unknown",
	"Lady",
	"Unknown",
	"Unknown",
	"Vergil",
	"Unknown",
	"Leviathan Heart",
	"Leviathan Other",
	"Jester",
	"Unknown",
};

export constexpr uint8 enemyHelperIndices[] =
{
	HELPER_ENEMY_LESSER_ENEMIES,
	HELPER_ENEMY_LESSER_ENEMIES,
	HELPER_ENEMY_LESSER_ENEMIES,
	HELPER_ENEMY_LESSER_ENEMIES,
	HELPER_ENEMY_LESSER_ENEMIES,
	HELPER_ENEMY_LESSER_ENEMIES,
	HELPER_ENEMY_LESSER_ENEMIES,
	HELPER_ENEMY_LESSER_ENEMIES,
	HELPER_ENEMY_LESSER_ENEMIES,
	HELPER_ENEMY_LESSER_ENEMIES,
	HELPER_ENEMY_LESSER_ENEMIES,
	HELPER_ENEMY_LESSER_ENEMIES,
	HELPER_ENEMY_LESSER_ENEMIES,
	HELPER_ENEMY_LESSER_ENEMIES,
	HELPER_ENEMY_LESSER_ENEMIES,
	HELPER_ENEMY_LESSER_ENEMIES,
	HELPER_ENEMY_LESSER_ENEMIES,
	HELPER_ENEMY_LESSER_ENEMIES,
	HELPER_ENEMY_LESSER_ENEMIES,
	HELPER_ENEMY_LESSER_ENEMIES,
	HELPER_ENEMY_LESSER_ENEMIES,
	HELPER_ENEMY_LESSER_ENEMIES,
	HELPER_ENEMY_LESSER_ENEMIES,
	HELPER_ENEMY_LESSER_ENEMIES,
	HELPER_ENEMY_LESSER_ENEMIES,
	HELPER_ENEMY_LESSER_ENEMIES,
	HELPER_ENEMY_LESSER_ENEMIES,
	0,
	HELPER_ENEMY_LESSER_ENEMIES,
	HELPER_ENEMY_LESSER_ENEMIES,
	HELPER_ENEMY_LESSER_ENEMIES,
	HELPER_ENEMY_LESSER_ENEMIES,
	HELPER_ENEMY_LESSER_ENEMIES,
	0,
	HELPER_ENEMY_LESSER_ENEMIES,
	HELPER_ENEMY_LESSER_ENEMIES,
	HELPER_ENEMY_LESSER_ENEMIES,
	HELPER_ENEMY_LESSER_ENEMIES,
	HELPER_ENEMY_LESSER_ENEMIES,
	HELPER_ENEMY_LESSER_ENEMIES,
	HELPER_ENEMY_LESSER_ENEMIES,
	HELPER_ENEMY_GIGAPEDE,
	0,
	HELPER_ENEMY_CERBERUS,
	HELPER_ENEMY_AGNI_RUDRA,
	HELPER_ENEMY_AGNI_RUDRA,
	HELPER_ENEMY_AGNI_RUDRA,
	HELPER_ENEMY_AGNI_RUDRA,
	HELPER_ENEMY_AGNI_RUDRA,
	HELPER_ENEMY_NEVAN,
	HELPER_ENEMY_GERYON,
	HELPER_ENEMY_BEOWULF,
	HELPER_ENEMY_DOPPELGANGER,
	HELPER_ENEMY_ARKHAM,
	0,
	HELPER_ENEMY_LADY,
	0,
	0,
	HELPER_ENEMY_VERGIL,
	0,
	HELPER_ENEMY_LESSER_ENEMIES,
	HELPER_ENEMY_LESSER_ENEMIES,
	HELPER_ENEMY_JESTER,
	0,
};

// $EnemyEnd




// @Todo: Remove.
static_assert(ENEMY_LADY == 55);
static_assert(ENEMY_VERGIL == 58);
static_assert(ENEMY_COUNT == 64);



















export enum
{
	ENEMY_FILE_DATA_EM000,
	ENEMY_FILE_DATA_EM006,
	ENEMY_FILE_DATA_EM007,
	ENEMY_FILE_DATA_EM008,
	ENEMY_FILE_DATA_EM010,
	ENEMY_FILE_DATA_EM011,
	ENEMY_FILE_DATA_EM012,
	ENEMY_FILE_DATA_EM013,
	ENEMY_FILE_DATA_EM014,
	ENEMY_FILE_DATA_EM016,
	ENEMY_FILE_DATA_EM017,
	ENEMY_FILE_DATA_EM021,
	ENEMY_FILE_DATA_EM023,
	ENEMY_FILE_DATA_EM025,
	ENEMY_FILE_DATA_EM026,
	ENEMY_FILE_DATA_EM027,
	ENEMY_FILE_DATA_EM028,
	ENEMY_FILE_DATA_EM029,
	ENEMY_FILE_DATA_EM030,
	ENEMY_FILE_DATA_EM031,
	ENEMY_FILE_DATA_EM032,
	ENEMY_FILE_DATA_EM034,
	ENEMY_FILE_DATA_EM035,
	ENEMY_FILE_DATA_EM037,
	ENEMY_FILE_DATA_COUNT,
};




// #define HelperAccess(type, name, var, newName)\
// struct Prep_Merge(type, var)\
// {\
// 	operator[](uint64 index)\
// 	{\
// 		return name[index].var;\
// 	}\
// };\
// Prep_Merge(type, var) newName = {};

// HelperAccess(EnemyHelper, enemyHelpers, name, enemyNames);






export enum
{
	ENEMY_FILE_SET_EM000,
	ENEMY_FILE_SET_EM006,
	ENEMY_FILE_SET_EM007,
	ENEMY_FILE_SET_EM008,
	ENEMY_FILE_SET_EM000_2,
	ENEMY_FILE_SET_EM010,
	ENEMY_FILE_SET_EM011,
	ENEMY_FILE_SET_EM012,
	ENEMY_FILE_SET_EM013,
	ENEMY_FILE_SET_EM014,
	ENEMY_FILE_SET_EM000_3,
	ENEMY_FILE_SET_EM016,
	ENEMY_FILE_SET_EM017,
	ENEMY_FILE_SET_EM021,
	ENEMY_FILE_SET_EM023,
	ENEMY_FILE_SET_EM000_4,
	ENEMY_FILE_SET_EM025,
	ENEMY_FILE_SET_EM026,
	ENEMY_FILE_SET_EM026_2,
	ENEMY_FILE_SET_EM028,
	ENEMY_FILE_SET_EM029,
	ENEMY_FILE_SET_EM030,
	ENEMY_FILE_SET_EM031,
	ENEMY_FILE_SET_EM032,
	ENEMY_FILE_SET_EM032_2,
	ENEMY_FILE_SET_EM034,
	ENEMY_FILE_SET_EM035,
	ENEMY_FILE_SET_EM037,
	ENEMY_FILE_SET_EM000_5,
	ENEMY_FILE_SET_EM000_6,
	ENEMY_FILE_SET_COUNT,
};

/*
Config::CreateEnemyData

Config_CreateEnemyData

ConfigCreateEnemyData
*/

// @Todo: Create script.

// struct CreateEnemyData
// {
// 	uint32 enemy;
// 	_(12);
// 	vec4 position;
// 	uint16 rotation,
// 	uint16 spawnMethod;
// 	_(4);
// 	uint32 variant;
// 	_(128);
// };

// static_assert(offsetof(CreateEnemyData, variant) == 0x28);

// $CreateEnemyDataStart

export struct CreateEnemyData
{
	uint32 enemy; // 0
	_(12);
	vec4 position; // 0x10
	uint16 rotation; // 0x20
	uint16 spawnMethod; // 0x22
	_(4);
	uint32 variant; // 0x28
	_(84);
};

static_assert(offsetof(CreateEnemyData, enemy) == 0);
static_assert(offsetof(CreateEnemyData, position) == 0x10);
static_assert(offsetof(CreateEnemyData, rotation) == 0x20);
static_assert(offsetof(CreateEnemyData, spawnMethod) == 0x22);
static_assert(offsetof(CreateEnemyData, variant) == 0x28);
static_assert(sizeof(CreateEnemyData) == 128);

// $CreateEnemyDataEnd

export struct EnemyVectorData
{
	byte8 * baseAddr;
	byte8 * nextAddr;
};

export struct RegionData
{
	byte8 * metadataAddr;
	byte8 * dataAddr;
	uint32 capacity;
	uint32 boundary;
	uint32 size;
	uint32 pipe;
	uint32 count;
	_(4);
};

// #define _(size) struct { byte8 Prep_Merge(padding_, __LINE__)[size]; }

// #pragma pack(push, 1)

// #pragma pack(pop)

// #undef _

// @Todo: Update names.

// struct MEMORY_OBJECT
// {
// 	byte8 * addr;
// 	byte8 * end;
// 	uint32 last;
// 	uint32 boundary;
// 	uint32 size;
// 	uint32 pipe;
// 	uint32 count;
// 	byte8 padding[4];
// };

export struct PS2_GAMEPAD
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

export struct ENGINE_GAMEPAD
{
	byte16 buttons[4];
	uint16 buttonsTimer[2];
	uint16 rightStickDirection[4];
	uint16 rightStickTimer[2];
	int16 rightStickPosition;
	int16 rightStickRadius;
	uint16 leftStickDirection[4];
	uint16 leftStickTimer[2];
	int16 leftStickPosition;
	int16 leftStickRadius;
};

// @Todo: Order.

export struct ActorEventData
{
	uint32 event;
	uint32 lastEvent;
};

export struct MotionData
{
	uint8 index;
	uint8 group;
};

export struct InputData
{
	byte8 flags[8];
	float32 value;
};

export struct ShadowData
{
	_(192);
};

static_assert(sizeof(ShadowData) == 0xC0);

export struct PhysicsData
{
	_(240);
};

static_assert(sizeof(PhysicsData) == 0xF0);

export struct PhysicsLinkData
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

export struct PhysicsMetadata
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

export struct BodyPartData
{
	_(104);
	byte8 ** motionArchives;
	_(176);
	//_(288);
};

static_assert(sizeof(BodyPartData) == 0x120);

export struct ModelMetadata
{
	uint8 count;
	_(15);
	vec4 vertices[3];
	_(16);
};

static_assert(sizeof(ModelMetadata) == 80);

export struct DevilModelMetadata
{
	uint8 modelIndex;
	uint8 modelPhysicsMetadataIndex;
};

export struct DevilSubmodelMetadata
{
	uint8 submodelIndex;
	uint8 devilModelPhysicsMetadataIndex;
	uint8 devilSubmodelIndex;
};

export struct DevilModelMetadata1 : DevilModelMetadata
{
	DevilSubmodelMetadata devilSubmodelMetadata;
};

export struct DevilModelMetadata2 : DevilModelMetadata
{
	DevilSubmodelMetadata devilSubmodelMetadata[2];
};

// @Todo: Cleanup.

export struct DevilModelMetadataDante
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

export struct ModelPartitionData
{
	uint8 value;
	_(895);
};

static_assert(sizeof(ModelPartitionData) == 0x380);

export struct ModelData
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

export struct RecoveryData
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

export struct WeaponData
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

export struct SummonedSwordsData
{
	_(1376);
	byte8 * actorBaseAddr;
};

static_assert(offsetof(SummonedSwordsData, actorBaseAddr) == 0x560);

export struct LockOnData
{
	struct Item
	{
		byte8 * addr;
		byte8 * nextAddr;
	};

	_(8);
	Item items[255];
	_(8);
	byte8 * var_1000;
	byte8 * var_1008;
	Item * var_1010;
	_(4136);
	uint32 var_2040;
};

static_assert(offsetof(LockOnData, items) == 8);
static_assert(offsetof(LockOnData, var_1000) == 0x1000);
static_assert(offsetof(LockOnData, var_1008) == 0x1008);
static_assert(offsetof(LockOnData, var_1010) == 0x1010);
static_assert(offsetof(LockOnData, var_2040) == 0x2040);
static_assert(sizeof(LockOnData) == 8260);

export struct CharacterData
{
	uint8 character;
	uint8 costume;
	bool ignoreCostume;
	bool forceFiles;
	uint8 forceFilesCharacter;
	uint8 forceFilesCostume;

	uint8 styles[STYLE_COUNT][2];
	uint8 styleIndices[STYLE_COUNT];
	byte16 styleButtons[STYLE_COUNT];
	uint8 styleButtonIndex;

	uint8 meleeWeaponCount;
	uint8 meleeWeapons[MELEE_WEAPON_COUNT];
	uint8 meleeWeaponIndex;
	uint8 lastMeleeWeaponIndex;
	uint8 meleeWeaponSwitchType;

	uint8 rangedWeaponCount;
	uint8 rangedWeapons[RANGED_WEAPON_COUNT];
	uint8 rangedWeaponIndex;
	uint8 lastRangedWeaponIndex;
	uint8 rangedWeaponSwitchType;
};

export struct PlayerData
{
	byte16 button;

	uint8 characterCount;
	uint8 characterIndex;
	uint8 lastCharacterIndex;
	uint8 activeCharacterIndex;

	CharacterData characterData[CHARACTER_COUNT][ENTITY_COUNT];
};

// $ActorDataStart

export struct ActorDataBase
{
	_(8);
	uint8 status; // 8
	_(11);
	float speed; // 0x14
	float speedMultiplier; // 0x18
	_(92);
	uint32 character; // 0x78
	_(4);
	vec4 position; // 0x80
	_(4);
	float pull; // 0x94
	_(12);
	float pullMultiplier; // 0xA4
	_(24);
	uint16 rotation; // 0xC0
	_(86);
	uint8 id; // 0x118
	_(3);
	bool32 isClone; // 0x11C
	uint32 visibility; // 0x120
	_(156);
	float var_1C0; // 0x1C0
	float var_1C4; // 0x1C4
	_(56);
	ModelData modelData[3]; // 0x200
	PhysicsMetadata * modelPhysicsMetadataPool[4][24]; // 0x1880
	uint32 modelAllocationDataCount; // 0x1B80
	_(4);
	Size_32 modelAllocationData[209]; // 0x1B88
	_(748);
	float motionSpeed; // 0x3894
	float motionSpeedMultiplier; // 0x3898
	_(4);
	byte8 * motionArchives[34]; // 0x38A0
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
	float motionTimer; // 0x3E34
	float idleTimer; // 0x3E38
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
	_(1);
	bool dead; // 0x3E99
	_(1);
	bool devil; // 0x3E9B
	_(2);
	uint8 costume; // 0x3E9E
	union
	{
		bool sparda; // 0x3E9F
		bool neroAngelo; // 0x3E9F
	}; // 0x3E9F
	_(4);
	bool useHolyWater; // 0x3EA4
	_(19);
	float magicPoints; // 0x3EB8
	float maxMagicPoints; // 0x3EBC
	_(4);
	float var_3EC4; // 0x3EC4
	float var_3EC8; // 0x3EC8
	_(6);
	uint16 var_3ED2; // 0x3ED2
	_(4);
	uint16 cameraDirection; // 0x3ED8
	_(2);
	float var_3EDC; // 0x3EDC
	_(49);
	uint8 airHikeCount; // 0x3F11
	uint8 kickJumpCount; // 0x3F12
	uint8 wallHikeCount; // 0x3F13
	bool enableAirRaid; // 0x3F14
	_(4);
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
	float maxHitPoints; // 0x40EC
	_(44);
	float hitPoints; // 0x411C
	_(8712);
	byte8 * targetBaseAddr; // 0x6328
	_(8);
	uint32 style; // 0x6338
	uint32 wallHikeDirection; // 0x633C
	uint32 var_6340; // 0x6340
	_(20);
	uint32 styleLevel; // 0x6358
	uint8 dashCount; // 0x635C
	uint8 skyStarCount; // 0x635D
	uint8 airTrickCount; // 0x635E
	uint8 trickUpCount; // 0x635F
	uint8 trickDownCount; // 0x6360
	bool quicksilver; // 0x6361
	bool doppelganger; // 0x6362
	_(1);
	float styleExperience; // 0x6364
	_(24);
	uint8 royalguardReleaseLevel; // 0x6380
	uint8 royalguardReleaseEffectIndex; // 0x6381
	_(2);
	float royalguardReleaseDamage; // 0x6384
	float var_6388; // 0x6388
	float var_638C; // 0x638C
	_(68);
	uint32 speedMode; // 0x63D4
	_(56);
	byte8 var_6410[40]; // 0x6410
	byte8 * var_6438; // 0x6438
	uint32 var_6440; // 0x6440
	_(12);
	uint32 cloneRate; // 0x6450
	uint32 cloneStatus; // 0x6454
	byte8 var_6458[32]; // 0x6458
	byte8 * cloneActorBaseAddr; // 0x6478
	bool cloneIsControlledByPlayer; // 0x6480
	_(3);
	uint32 activeMeleeWeaponIndex; // 0x6484
	uint32 queuedMeleeWeaponIndex; // 0x6488
	_(1);
	uint8 activeWeapon; // 0x648D
	_(2);
	uint32 meleeWeaponIndex; // 0x6490
	uint32 rangedWeaponIndex; // 0x6494
	uint8 weapons[5]; // 0x6498
	_(3);
	WeaponData * weaponDataAddr[5]; // 0x64A0
	uint32 weaponStatus[5]; // 0x64C8
	uint32 weaponLevels[5]; // 0x64DC
	uint8 activeMeleeWeapon; // 0x64F0
	uint8 activeRangedWeapon; // 0x64F1
	_(2);
	float weaponTimers[5]; // 0x64F4
	float meleeWeaponSwitchTimeout; // 0x6508
	float rangedWeaponSwitchTimeout; // 0x650C
	StyleData styleData; // 0x6510
	float var_6670; // 0x6670
	InputData inputData[58]; // 0x6674
	_(36);
	BodyPartData bodyPartData[3][2]; // 0x6950
	_(576);
	CollisionData collisionData; // 0x7250
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

	operator byte8 *()
	{
		return reinterpret_cast<byte8 *>(this);
	}
};

static_assert(offsetof(ActorDataBase, status) == 8);
static_assert(offsetof(ActorDataBase, speed) == 0x14);
static_assert(offsetof(ActorDataBase, speedMultiplier) == 0x18);
static_assert(offsetof(ActorDataBase, character) == 0x78);
static_assert(offsetof(ActorDataBase, position) == 0x80);
static_assert(offsetof(ActorDataBase, pull) == 0x94);
static_assert(offsetof(ActorDataBase, pullMultiplier) == 0xA4);
static_assert(offsetof(ActorDataBase, rotation) == 0xC0);
static_assert(offsetof(ActorDataBase, id) == 0x118);
static_assert(offsetof(ActorDataBase, isClone) == 0x11C);
static_assert(offsetof(ActorDataBase, visibility) == 0x120);
static_assert(offsetof(ActorDataBase, var_1C0) == 0x1C0);
static_assert(offsetof(ActorDataBase, var_1C4) == 0x1C4);
static_assert(offsetof(ActorDataBase, modelData) == 0x200);
static_assert(offsetof(ActorDataBase, modelPhysicsMetadataPool) == 0x1880);
static_assert(offsetof(ActorDataBase, modelAllocationDataCount) == 0x1B80);
static_assert(offsetof(ActorDataBase, modelAllocationData) == 0x1B88);
static_assert(offsetof(ActorDataBase, motionSpeed) == 0x3894);
static_assert(offsetof(ActorDataBase, motionSpeedMultiplier) == 0x3898);
static_assert(offsetof(ActorDataBase, motionArchives) == 0x38A0);
static_assert(offsetof(ActorDataBase, motionData) == 0x39B0);
static_assert(offsetof(ActorDataBase, motionDataMirror) == 0x39B4);
static_assert(offsetof(ActorDataBase, var_39BC) == 0x39BC);
static_assert(offsetof(ActorDataBase, var_39C0) == 0x39C0);
static_assert(offsetof(ActorDataBase, nextActionRequestPolicy) == 0x39D0);
static_assert(offsetof(ActorDataBase, var_3A10) == 0x3A10);
static_assert(offsetof(ActorDataBase, shadow) == 0x3A18);
static_assert(offsetof(ActorDataBase, lastShadow) == 0x3A1C);
static_assert(offsetof(ActorDataBase, color) == 0x3A28);
static_assert(offsetof(ActorDataBase, recoveryData) == 0x3B00);
static_assert(offsetof(ActorDataBase, var_3C50) == 0x3C50);
static_assert(offsetof(ActorDataBase, actionData) == 0x3DD0);
static_assert(offsetof(ActorDataBase, eventData) == 0x3E00);
static_assert(offsetof(ActorDataBase, var_3E10) == 0x3E10);
static_assert(offsetof(ActorDataBase, motionTimer) == 0x3E34);
static_assert(offsetof(ActorDataBase, idleTimer) == 0x3E38);
static_assert(offsetof(ActorDataBase, permissions) == 0x3E60);
static_assert(offsetof(ActorDataBase, state) == 0x3E64);
static_assert(offsetof(ActorDataBase, lastState) == 0x3E68);
static_assert(offsetof(ActorDataBase, activeModelIndex) == 0x3E6C);
static_assert(offsetof(ActorDataBase, queuedModelIndex) == 0x3E70);
static_assert(offsetof(ActorDataBase, devilModels) == 0x3E74);
static_assert(offsetof(ActorDataBase, modelState) == 0x3E80);
static_assert(offsetof(ActorDataBase, lockOn) == 0x3E84);
static_assert(offsetof(ActorDataBase, activeModelIndexMirror) == 0x3E88);
static_assert(offsetof(ActorDataBase, activeDevil) == 0x3E8C);
static_assert(offsetof(ActorDataBase, airRaid) == 0x3E90);
static_assert(offsetof(ActorDataBase, mode) == 0x3E94);
static_assert(offsetof(ActorDataBase, dead) == 0x3E99);
static_assert(offsetof(ActorDataBase, devil) == 0x3E9B);
static_assert(offsetof(ActorDataBase, costume) == 0x3E9E);
static_assert(offsetof(ActorDataBase, sparda) == 0x3E9F);
static_assert(offsetof(ActorDataBase, neroAngelo) == 0x3E9F);
static_assert(offsetof(ActorDataBase, useHolyWater) == 0x3EA4);
static_assert(offsetof(ActorDataBase, magicPoints) == 0x3EB8);
static_assert(offsetof(ActorDataBase, maxMagicPoints) == 0x3EBC);
static_assert(offsetof(ActorDataBase, var_3EC4) == 0x3EC4);
static_assert(offsetof(ActorDataBase, var_3EC8) == 0x3EC8);
static_assert(offsetof(ActorDataBase, var_3ED2) == 0x3ED2);
static_assert(offsetof(ActorDataBase, cameraDirection) == 0x3ED8);
static_assert(offsetof(ActorDataBase, var_3EDC) == 0x3EDC);
static_assert(offsetof(ActorDataBase, airHikeCount) == 0x3F11);
static_assert(offsetof(ActorDataBase, kickJumpCount) == 0x3F12);
static_assert(offsetof(ActorDataBase, wallHikeCount) == 0x3F13);
static_assert(offsetof(ActorDataBase, enableAirRaid) == 0x3F14);
static_assert(offsetof(ActorDataBase, var_3F19) == 0x3F19);
static_assert(offsetof(ActorDataBase, action) == 0x3FA4);
static_assert(offsetof(ActorDataBase, lastAction) == 0x3FA5);
static_assert(offsetof(ActorDataBase, bufferedAction) == 0x3FA8);
static_assert(offsetof(ActorDataBase, chainCount) == 0x3FAC);
static_assert(offsetof(ActorDataBase, expertise) == 0x3FEC);
static_assert(offsetof(ActorDataBase, maxHitPoints) == 0x40EC);
static_assert(offsetof(ActorDataBase, hitPoints) == 0x411C);
static_assert(offsetof(ActorDataBase, targetBaseAddr) == 0x6328);
static_assert(offsetof(ActorDataBase, style) == 0x6338);
static_assert(offsetof(ActorDataBase, wallHikeDirection) == 0x633C);
static_assert(offsetof(ActorDataBase, var_6340) == 0x6340);
static_assert(offsetof(ActorDataBase, styleLevel) == 0x6358);
static_assert(offsetof(ActorDataBase, dashCount) == 0x635C);
static_assert(offsetof(ActorDataBase, skyStarCount) == 0x635D);
static_assert(offsetof(ActorDataBase, airTrickCount) == 0x635E);
static_assert(offsetof(ActorDataBase, trickUpCount) == 0x635F);
static_assert(offsetof(ActorDataBase, trickDownCount) == 0x6360);
static_assert(offsetof(ActorDataBase, quicksilver) == 0x6361);
static_assert(offsetof(ActorDataBase, doppelganger) == 0x6362);
static_assert(offsetof(ActorDataBase, styleExperience) == 0x6364);
static_assert(offsetof(ActorDataBase, royalguardReleaseLevel) == 0x6380);
static_assert(offsetof(ActorDataBase, royalguardReleaseEffectIndex) == 0x6381);
static_assert(offsetof(ActorDataBase, royalguardReleaseDamage) == 0x6384);
static_assert(offsetof(ActorDataBase, var_6388) == 0x6388);
static_assert(offsetof(ActorDataBase, var_638C) == 0x638C);
static_assert(offsetof(ActorDataBase, speedMode) == 0x63D4);
static_assert(offsetof(ActorDataBase, var_6410) == 0x6410);
static_assert(offsetof(ActorDataBase, var_6438) == 0x6438);
static_assert(offsetof(ActorDataBase, var_6440) == 0x6440);
static_assert(offsetof(ActorDataBase, cloneRate) == 0x6450);
static_assert(offsetof(ActorDataBase, cloneStatus) == 0x6454);
static_assert(offsetof(ActorDataBase, var_6458) == 0x6458);
static_assert(offsetof(ActorDataBase, cloneActorBaseAddr) == 0x6478);
static_assert(offsetof(ActorDataBase, cloneIsControlledByPlayer) == 0x6480);
static_assert(offsetof(ActorDataBase, activeMeleeWeaponIndex) == 0x6484);
static_assert(offsetof(ActorDataBase, queuedMeleeWeaponIndex) == 0x6488);
static_assert(offsetof(ActorDataBase, activeWeapon) == 0x648D);
static_assert(offsetof(ActorDataBase, meleeWeaponIndex) == 0x6490);
static_assert(offsetof(ActorDataBase, rangedWeaponIndex) == 0x6494);
static_assert(offsetof(ActorDataBase, weapons) == 0x6498);
static_assert(offsetof(ActorDataBase, weaponDataAddr) == 0x64A0);
static_assert(offsetof(ActorDataBase, weaponStatus) == 0x64C8);
static_assert(offsetof(ActorDataBase, weaponLevels) == 0x64DC);
static_assert(offsetof(ActorDataBase, activeMeleeWeapon) == 0x64F0);
static_assert(offsetof(ActorDataBase, activeRangedWeapon) == 0x64F1);
static_assert(offsetof(ActorDataBase, weaponTimers) == 0x64F4);
static_assert(offsetof(ActorDataBase, meleeWeaponSwitchTimeout) == 0x6508);
static_assert(offsetof(ActorDataBase, rangedWeaponSwitchTimeout) == 0x650C);
static_assert(offsetof(ActorDataBase, styleData) == 0x6510);
static_assert(offsetof(ActorDataBase, var_6670) == 0x6670);
static_assert(offsetof(ActorDataBase, inputData) == 0x6674);
static_assert(offsetof(ActorDataBase, bodyPartData) == 0x6950);
static_assert(offsetof(ActorDataBase, collisionData) == 0x7250);
static_assert(offsetof(ActorDataBase, buttons) == 0x74E0);
static_assert(offsetof(ActorDataBase, rightStickPosition) == 0x74F8);
static_assert(offsetof(ActorDataBase, rightStickRadius) == 0x74FA);
static_assert(offsetof(ActorDataBase, leftStickPosition) == 0x7508);
static_assert(offsetof(ActorDataBase, leftStickRadius) == 0x750A);
static_assert(offsetof(ActorDataBase, actorCameraDirection) == 0x750C);
static_assert(offsetof(ActorDataBase, leftStickDirection) == 0x751C);

static_assert(sizeof(ActorDataBase) == 0x7540);

export struct ActorData : ActorDataBase
{
	_(17280);
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
	WeaponData * newWeaponDataAddr[10]; // 0x1C9F0
	uint32 newWeaponStatus[10]; // 0x1CA40
	_(8);
	uint32 newWeaponLevels[10]; // 0x1CA70
	_(8);
	float newWeaponTimers[10]; // 0x1CAA0
	bool32 newIsClone; // 0x1CAC8
	uint8 newPlayerIndex; // 0x1CACC
	uint8 newCharacterIndex; // 0x1CACD
	uint8 newEntityIndex; // 0x1CACE
	bool newForceFiles; // 0x1CACF
	uint8 newForceFilesCharacter; // 0x1CAD0
	uint8 newForceFilesCostume; // 0x1CAD1
	bool newEnableVisibility; // 0x1CAD2
	uint8 newGamepad; // 0x1CAD3
	byte16 newButtonMask; // 0x1CAD4
	bool newEnableRightStick; // 0x1CAD6
	bool newEnableLeftStick; // 0x1CAD7
	bool newAirStinger; // 0x1CAD8
	uint8 newAirStingerCount; // 0x1CAD9
	bool newEnableCollision; // 0x1CADA
	bool newActorLoopRun; // 0x1CADB
	uint8 newAirHikeCount; // 0x1CADC
	uint8 newKickJumpCount; // 0x1CADD
	uint8 newWallHikeCount; // 0x1CADE
	uint8 newDashCount; // 0x1CADF
	uint8 newSkyStarCount; // 0x1CAE0
	uint8 newAirTrickCount; // 0x1CAE1
	uint8 newTrickUpCount; // 0x1CAE2
	uint8 newTrickDownCount; // 0x1CAE3
	_(12);
	uint32 newEffectIndices[12]; // 0x1CAF0
	uint32 newLastVar; // 0x1CB20
};

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
static_assert(offsetof(ActorData, newWeaponDataAddr) == 0x1C9F0);
static_assert(offsetof(ActorData, newWeaponStatus) == 0x1CA40);
static_assert(offsetof(ActorData, newWeaponLevels) == 0x1CA70);
static_assert(offsetof(ActorData, newWeaponTimers) == 0x1CAA0);
static_assert(offsetof(ActorData, newIsClone) == 0x1CAC8);
static_assert(offsetof(ActorData, newPlayerIndex) == 0x1CACC);
static_assert(offsetof(ActorData, newCharacterIndex) == 0x1CACD);
static_assert(offsetof(ActorData, newEntityIndex) == 0x1CACE);
static_assert(offsetof(ActorData, newForceFiles) == 0x1CACF);
static_assert(offsetof(ActorData, newForceFilesCharacter) == 0x1CAD0);
static_assert(offsetof(ActorData, newForceFilesCostume) == 0x1CAD1);
static_assert(offsetof(ActorData, newEnableVisibility) == 0x1CAD2);
static_assert(offsetof(ActorData, newGamepad) == 0x1CAD3);
static_assert(offsetof(ActorData, newButtonMask) == 0x1CAD4);
static_assert(offsetof(ActorData, newEnableRightStick) == 0x1CAD6);
static_assert(offsetof(ActorData, newEnableLeftStick) == 0x1CAD7);
static_assert(offsetof(ActorData, newAirStinger) == 0x1CAD8);
static_assert(offsetof(ActorData, newAirStingerCount) == 0x1CAD9);
static_assert(offsetof(ActorData, newEnableCollision) == 0x1CADA);
static_assert(offsetof(ActorData, newActorLoopRun) == 0x1CADB);
static_assert(offsetof(ActorData, newAirHikeCount) == 0x1CADC);
static_assert(offsetof(ActorData, newKickJumpCount) == 0x1CADD);
static_assert(offsetof(ActorData, newWallHikeCount) == 0x1CADE);
static_assert(offsetof(ActorData, newDashCount) == 0x1CADF);
static_assert(offsetof(ActorData, newSkyStarCount) == 0x1CAE0);
static_assert(offsetof(ActorData, newAirTrickCount) == 0x1CAE1);
static_assert(offsetof(ActorData, newTrickUpCount) == 0x1CAE2);
static_assert(offsetof(ActorData, newTrickDownCount) == 0x1CAE3);
static_assert(offsetof(ActorData, newEffectIndices) == 0x1CAF0);
static_assert(offsetof(ActorData, newLastVar) == 0x1CB20);

export struct ActorDataDante : ActorDataBase
{
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
	float artemisChargeValue[2]; // 0xB868
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
	WeaponData * newWeaponDataAddr[10]; // 0x1C9F0
	uint32 newWeaponStatus[10]; // 0x1CA40
	_(8);
	uint32 newWeaponLevels[10]; // 0x1CA70
	_(8);
	float newWeaponTimers[10]; // 0x1CAA0
	bool32 newIsClone; // 0x1CAC8
	uint8 newPlayerIndex; // 0x1CACC
	uint8 newCharacterIndex; // 0x1CACD
	uint8 newEntityIndex; // 0x1CACE
	bool newForceFiles; // 0x1CACF
	uint8 newForceFilesCharacter; // 0x1CAD0
	uint8 newForceFilesCostume; // 0x1CAD1
	bool newEnableVisibility; // 0x1CAD2
	uint8 newGamepad; // 0x1CAD3
	byte16 newButtonMask; // 0x1CAD4
	bool newEnableRightStick; // 0x1CAD6
	bool newEnableLeftStick; // 0x1CAD7
	bool newAirStinger; // 0x1CAD8
	uint8 newAirStingerCount; // 0x1CAD9
	bool newEnableCollision; // 0x1CADA
	bool newActorLoopRun; // 0x1CADB
	uint8 newAirHikeCount; // 0x1CADC
	uint8 newKickJumpCount; // 0x1CADD
	uint8 newWallHikeCount; // 0x1CADE
	uint8 newDashCount; // 0x1CADF
	uint8 newSkyStarCount; // 0x1CAE0
	uint8 newAirTrickCount; // 0x1CAE1
	uint8 newTrickUpCount; // 0x1CAE2
	uint8 newTrickDownCount; // 0x1CAE3
	_(12);
	uint32 newEffectIndices[12]; // 0x1CAF0
	uint32 newLastVar; // 0x1CB20
};

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
static_assert(offsetof(ActorDataDante, newWeaponDataAddr) == 0x1C9F0);
static_assert(offsetof(ActorDataDante, newWeaponStatus) == 0x1CA40);
static_assert(offsetof(ActorDataDante, newWeaponLevels) == 0x1CA70);
static_assert(offsetof(ActorDataDante, newWeaponTimers) == 0x1CAA0);
static_assert(offsetof(ActorDataDante, newIsClone) == 0x1CAC8);
static_assert(offsetof(ActorDataDante, newPlayerIndex) == 0x1CACC);
static_assert(offsetof(ActorDataDante, newCharacterIndex) == 0x1CACD);
static_assert(offsetof(ActorDataDante, newEntityIndex) == 0x1CACE);
static_assert(offsetof(ActorDataDante, newForceFiles) == 0x1CACF);
static_assert(offsetof(ActorDataDante, newForceFilesCharacter) == 0x1CAD0);
static_assert(offsetof(ActorDataDante, newForceFilesCostume) == 0x1CAD1);
static_assert(offsetof(ActorDataDante, newEnableVisibility) == 0x1CAD2);
static_assert(offsetof(ActorDataDante, newGamepad) == 0x1CAD3);
static_assert(offsetof(ActorDataDante, newButtonMask) == 0x1CAD4);
static_assert(offsetof(ActorDataDante, newEnableRightStick) == 0x1CAD6);
static_assert(offsetof(ActorDataDante, newEnableLeftStick) == 0x1CAD7);
static_assert(offsetof(ActorDataDante, newAirStinger) == 0x1CAD8);
static_assert(offsetof(ActorDataDante, newAirStingerCount) == 0x1CAD9);
static_assert(offsetof(ActorDataDante, newEnableCollision) == 0x1CADA);
static_assert(offsetof(ActorDataDante, newActorLoopRun) == 0x1CADB);
static_assert(offsetof(ActorDataDante, newAirHikeCount) == 0x1CADC);
static_assert(offsetof(ActorDataDante, newKickJumpCount) == 0x1CADD);
static_assert(offsetof(ActorDataDante, newWallHikeCount) == 0x1CADE);
static_assert(offsetof(ActorDataDante, newDashCount) == 0x1CADF);
static_assert(offsetof(ActorDataDante, newSkyStarCount) == 0x1CAE0);
static_assert(offsetof(ActorDataDante, newAirTrickCount) == 0x1CAE1);
static_assert(offsetof(ActorDataDante, newTrickUpCount) == 0x1CAE2);
static_assert(offsetof(ActorDataDante, newTrickDownCount) == 0x1CAE3);
static_assert(offsetof(ActorDataDante, newEffectIndices) == 0x1CAF0);
static_assert(offsetof(ActorDataDante, newLastVar) == 0x1CB20);

export struct ActorDataBob : ActorDataBase
{
	_(17280);
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
	WeaponData * newWeaponDataAddr[10]; // 0x1C9F0
	uint32 newWeaponStatus[10]; // 0x1CA40
	_(8);
	uint32 newWeaponLevels[10]; // 0x1CA70
	_(8);
	float newWeaponTimers[10]; // 0x1CAA0
	bool32 newIsClone; // 0x1CAC8
	uint8 newPlayerIndex; // 0x1CACC
	uint8 newCharacterIndex; // 0x1CACD
	uint8 newEntityIndex; // 0x1CACE
	bool newForceFiles; // 0x1CACF
	uint8 newForceFilesCharacter; // 0x1CAD0
	uint8 newForceFilesCostume; // 0x1CAD1
	bool newEnableVisibility; // 0x1CAD2
	uint8 newGamepad; // 0x1CAD3
	byte16 newButtonMask; // 0x1CAD4
	bool newEnableRightStick; // 0x1CAD6
	bool newEnableLeftStick; // 0x1CAD7
	bool newAirStinger; // 0x1CAD8
	uint8 newAirStingerCount; // 0x1CAD9
	bool newEnableCollision; // 0x1CADA
	bool newActorLoopRun; // 0x1CADB
	uint8 newAirHikeCount; // 0x1CADC
	uint8 newKickJumpCount; // 0x1CADD
	uint8 newWallHikeCount; // 0x1CADE
	uint8 newDashCount; // 0x1CADF
	uint8 newSkyStarCount; // 0x1CAE0
	uint8 newAirTrickCount; // 0x1CAE1
	uint8 newTrickUpCount; // 0x1CAE2
	uint8 newTrickDownCount; // 0x1CAE3
	_(12);
	uint32 newEffectIndices[12]; // 0x1CAF0
	uint32 newLastVar; // 0x1CB20
};

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
static_assert(offsetof(ActorDataBob, newWeaponDataAddr) == 0x1C9F0);
static_assert(offsetof(ActorDataBob, newWeaponStatus) == 0x1CA40);
static_assert(offsetof(ActorDataBob, newWeaponLevels) == 0x1CA70);
static_assert(offsetof(ActorDataBob, newWeaponTimers) == 0x1CAA0);
static_assert(offsetof(ActorDataBob, newIsClone) == 0x1CAC8);
static_assert(offsetof(ActorDataBob, newPlayerIndex) == 0x1CACC);
static_assert(offsetof(ActorDataBob, newCharacterIndex) == 0x1CACD);
static_assert(offsetof(ActorDataBob, newEntityIndex) == 0x1CACE);
static_assert(offsetof(ActorDataBob, newForceFiles) == 0x1CACF);
static_assert(offsetof(ActorDataBob, newForceFilesCharacter) == 0x1CAD0);
static_assert(offsetof(ActorDataBob, newForceFilesCostume) == 0x1CAD1);
static_assert(offsetof(ActorDataBob, newEnableVisibility) == 0x1CAD2);
static_assert(offsetof(ActorDataBob, newGamepad) == 0x1CAD3);
static_assert(offsetof(ActorDataBob, newButtonMask) == 0x1CAD4);
static_assert(offsetof(ActorDataBob, newEnableRightStick) == 0x1CAD6);
static_assert(offsetof(ActorDataBob, newEnableLeftStick) == 0x1CAD7);
static_assert(offsetof(ActorDataBob, newAirStinger) == 0x1CAD8);
static_assert(offsetof(ActorDataBob, newAirStingerCount) == 0x1CAD9);
static_assert(offsetof(ActorDataBob, newEnableCollision) == 0x1CADA);
static_assert(offsetof(ActorDataBob, newActorLoopRun) == 0x1CADB);
static_assert(offsetof(ActorDataBob, newAirHikeCount) == 0x1CADC);
static_assert(offsetof(ActorDataBob, newKickJumpCount) == 0x1CADD);
static_assert(offsetof(ActorDataBob, newWallHikeCount) == 0x1CADE);
static_assert(offsetof(ActorDataBob, newDashCount) == 0x1CADF);
static_assert(offsetof(ActorDataBob, newSkyStarCount) == 0x1CAE0);
static_assert(offsetof(ActorDataBob, newAirTrickCount) == 0x1CAE1);
static_assert(offsetof(ActorDataBob, newTrickUpCount) == 0x1CAE2);
static_assert(offsetof(ActorDataBob, newTrickDownCount) == 0x1CAE3);
static_assert(offsetof(ActorDataBob, newEffectIndices) == 0x1CAF0);
static_assert(offsetof(ActorDataBob, newLastVar) == 0x1CB20);

export struct ActorDataLady : ActorDataBase
{
	_(17280);
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
	WeaponData * newWeaponDataAddr[10]; // 0x1C9F0
	uint32 newWeaponStatus[10]; // 0x1CA40
	_(8);
	uint32 newWeaponLevels[10]; // 0x1CA70
	_(8);
	float newWeaponTimers[10]; // 0x1CAA0
	bool32 newIsClone; // 0x1CAC8
	uint8 newPlayerIndex; // 0x1CACC
	uint8 newCharacterIndex; // 0x1CACD
	uint8 newEntityIndex; // 0x1CACE
	bool newForceFiles; // 0x1CACF
	uint8 newForceFilesCharacter; // 0x1CAD0
	uint8 newForceFilesCostume; // 0x1CAD1
	bool newEnableVisibility; // 0x1CAD2
	uint8 newGamepad; // 0x1CAD3
	byte16 newButtonMask; // 0x1CAD4
	bool newEnableRightStick; // 0x1CAD6
	bool newEnableLeftStick; // 0x1CAD7
	bool newAirStinger; // 0x1CAD8
	uint8 newAirStingerCount; // 0x1CAD9
	bool newEnableCollision; // 0x1CADA
	bool newActorLoopRun; // 0x1CADB
	uint8 newAirHikeCount; // 0x1CADC
	uint8 newKickJumpCount; // 0x1CADD
	uint8 newWallHikeCount; // 0x1CADE
	uint8 newDashCount; // 0x1CADF
	uint8 newSkyStarCount; // 0x1CAE0
	uint8 newAirTrickCount; // 0x1CAE1
	uint8 newTrickUpCount; // 0x1CAE2
	uint8 newTrickDownCount; // 0x1CAE3
	_(12);
	uint32 newEffectIndices[12]; // 0x1CAF0
	uint32 newLastVar; // 0x1CB20
};

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
static_assert(offsetof(ActorDataLady, newWeaponDataAddr) == 0x1C9F0);
static_assert(offsetof(ActorDataLady, newWeaponStatus) == 0x1CA40);
static_assert(offsetof(ActorDataLady, newWeaponLevels) == 0x1CA70);
static_assert(offsetof(ActorDataLady, newWeaponTimers) == 0x1CAA0);
static_assert(offsetof(ActorDataLady, newIsClone) == 0x1CAC8);
static_assert(offsetof(ActorDataLady, newPlayerIndex) == 0x1CACC);
static_assert(offsetof(ActorDataLady, newCharacterIndex) == 0x1CACD);
static_assert(offsetof(ActorDataLady, newEntityIndex) == 0x1CACE);
static_assert(offsetof(ActorDataLady, newForceFiles) == 0x1CACF);
static_assert(offsetof(ActorDataLady, newForceFilesCharacter) == 0x1CAD0);
static_assert(offsetof(ActorDataLady, newForceFilesCostume) == 0x1CAD1);
static_assert(offsetof(ActorDataLady, newEnableVisibility) == 0x1CAD2);
static_assert(offsetof(ActorDataLady, newGamepad) == 0x1CAD3);
static_assert(offsetof(ActorDataLady, newButtonMask) == 0x1CAD4);
static_assert(offsetof(ActorDataLady, newEnableRightStick) == 0x1CAD6);
static_assert(offsetof(ActorDataLady, newEnableLeftStick) == 0x1CAD7);
static_assert(offsetof(ActorDataLady, newAirStinger) == 0x1CAD8);
static_assert(offsetof(ActorDataLady, newAirStingerCount) == 0x1CAD9);
static_assert(offsetof(ActorDataLady, newEnableCollision) == 0x1CADA);
static_assert(offsetof(ActorDataLady, newActorLoopRun) == 0x1CADB);
static_assert(offsetof(ActorDataLady, newAirHikeCount) == 0x1CADC);
static_assert(offsetof(ActorDataLady, newKickJumpCount) == 0x1CADD);
static_assert(offsetof(ActorDataLady, newWallHikeCount) == 0x1CADE);
static_assert(offsetof(ActorDataLady, newDashCount) == 0x1CADF);
static_assert(offsetof(ActorDataLady, newSkyStarCount) == 0x1CAE0);
static_assert(offsetof(ActorDataLady, newAirTrickCount) == 0x1CAE1);
static_assert(offsetof(ActorDataLady, newTrickUpCount) == 0x1CAE2);
static_assert(offsetof(ActorDataLady, newTrickDownCount) == 0x1CAE3);
static_assert(offsetof(ActorDataLady, newEffectIndices) == 0x1CAF0);
static_assert(offsetof(ActorDataLady, newLastVar) == 0x1CB20);

export struct ActorDataVergil : ActorDataBase
{
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
	WeaponData * newWeaponDataAddr[10]; // 0x1C9F0
	uint32 newWeaponStatus[10]; // 0x1CA40
	_(8);
	uint32 newWeaponLevels[10]; // 0x1CA70
	_(8);
	float newWeaponTimers[10]; // 0x1CAA0
	bool32 newIsClone; // 0x1CAC8
	uint8 newPlayerIndex; // 0x1CACC
	uint8 newCharacterIndex; // 0x1CACD
	uint8 newEntityIndex; // 0x1CACE
	bool newForceFiles; // 0x1CACF
	uint8 newForceFilesCharacter; // 0x1CAD0
	uint8 newForceFilesCostume; // 0x1CAD1
	bool newEnableVisibility; // 0x1CAD2
	uint8 newGamepad; // 0x1CAD3
	byte16 newButtonMask; // 0x1CAD4
	bool newEnableRightStick; // 0x1CAD6
	bool newEnableLeftStick; // 0x1CAD7
	bool newAirStinger; // 0x1CAD8
	uint8 newAirStingerCount; // 0x1CAD9
	bool newEnableCollision; // 0x1CADA
	bool newActorLoopRun; // 0x1CADB
	uint8 newAirHikeCount; // 0x1CADC
	uint8 newKickJumpCount; // 0x1CADD
	uint8 newWallHikeCount; // 0x1CADE
	uint8 newDashCount; // 0x1CADF
	uint8 newSkyStarCount; // 0x1CAE0
	uint8 newAirTrickCount; // 0x1CAE1
	uint8 newTrickUpCount; // 0x1CAE2
	uint8 newTrickDownCount; // 0x1CAE3
	_(12);
	uint32 newEffectIndices[12]; // 0x1CAF0
	uint32 newLastVar; // 0x1CB20
};

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
static_assert(offsetof(ActorDataVergil, newWeaponDataAddr) == 0x1C9F0);
static_assert(offsetof(ActorDataVergil, newWeaponStatus) == 0x1CA40);
static_assert(offsetof(ActorDataVergil, newWeaponLevels) == 0x1CA70);
static_assert(offsetof(ActorDataVergil, newWeaponTimers) == 0x1CAA0);
static_assert(offsetof(ActorDataVergil, newIsClone) == 0x1CAC8);
static_assert(offsetof(ActorDataVergil, newPlayerIndex) == 0x1CACC);
static_assert(offsetof(ActorDataVergil, newCharacterIndex) == 0x1CACD);
static_assert(offsetof(ActorDataVergil, newEntityIndex) == 0x1CACE);
static_assert(offsetof(ActorDataVergil, newForceFiles) == 0x1CACF);
static_assert(offsetof(ActorDataVergil, newForceFilesCharacter) == 0x1CAD0);
static_assert(offsetof(ActorDataVergil, newForceFilesCostume) == 0x1CAD1);
static_assert(offsetof(ActorDataVergil, newEnableVisibility) == 0x1CAD2);
static_assert(offsetof(ActorDataVergil, newGamepad) == 0x1CAD3);
static_assert(offsetof(ActorDataVergil, newButtonMask) == 0x1CAD4);
static_assert(offsetof(ActorDataVergil, newEnableRightStick) == 0x1CAD6);
static_assert(offsetof(ActorDataVergil, newEnableLeftStick) == 0x1CAD7);
static_assert(offsetof(ActorDataVergil, newAirStinger) == 0x1CAD8);
static_assert(offsetof(ActorDataVergil, newAirStingerCount) == 0x1CAD9);
static_assert(offsetof(ActorDataVergil, newEnableCollision) == 0x1CADA);
static_assert(offsetof(ActorDataVergil, newActorLoopRun) == 0x1CADB);
static_assert(offsetof(ActorDataVergil, newAirHikeCount) == 0x1CADC);
static_assert(offsetof(ActorDataVergil, newKickJumpCount) == 0x1CADD);
static_assert(offsetof(ActorDataVergil, newWallHikeCount) == 0x1CADE);
static_assert(offsetof(ActorDataVergil, newDashCount) == 0x1CADF);
static_assert(offsetof(ActorDataVergil, newSkyStarCount) == 0x1CAE0);
static_assert(offsetof(ActorDataVergil, newAirTrickCount) == 0x1CAE1);
static_assert(offsetof(ActorDataVergil, newTrickUpCount) == 0x1CAE2);
static_assert(offsetof(ActorDataVergil, newTrickDownCount) == 0x1CAE3);
static_assert(offsetof(ActorDataVergil, newEffectIndices) == 0x1CAF0);
static_assert(offsetof(ActorDataVergil, newLastVar) == 0x1CB20);

// $ActorDataEnd

// $EnemyDataStart

export struct EnemyData
{
	_(40);
	byte8 * lastBaseAddr; // 0x28
	byte8 * nextBaseAddr; // 0x30
	_(16);
	byte8 * baseAddr; // 0x48
	_(40);
	uint32 enemy; // 0x78
	_(4);
	vec4 position; // 0x80
};

static_assert(offsetof(EnemyData, lastBaseAddr) == 0x28);
static_assert(offsetof(EnemyData, nextBaseAddr) == 0x30);
static_assert(offsetof(EnemyData, baseAddr) == 0x48);
static_assert(offsetof(EnemyData, enemy) == 0x78);
static_assert(offsetof(EnemyData, position) == 0x80);
static_assert(sizeof(EnemyData) == 144);

// $EnemyDataEnd

// @Todo: Update.

#pragma pack(pop)

#undef _

// @Todo: Update.

export struct MotionArchiveHelper
{
	uint8 group;
	uint16 cacheFileId;
};

export constexpr MotionArchiveHelper motionArchiveHelperDante[] =
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

export constexpr MotionArchiveHelper motionArchiveHelperBob[] =
{
	{ MOTION_GROUP_BOB_BASE   , pl001_00_0  },
	{ MOTION_GROUP_BOB_DAMAGE , pl001_00_1  },
	{ MOTION_GROUP_BOB_TAUNTS , pl001_00_2  },
	{ MOTION_GROUP_BOB_YAMATO , pl001_00_31 },
};

export constexpr MotionArchiveHelper motionArchiveHelperLady[] =
{
	{ MOTION_GROUP_LADY_BASE      , pl002_00_0  },
	{ MOTION_GROUP_LADY_DAMAGE    , pl002_00_1  },
	{ MOTION_GROUP_LADY_TAUNTS    , pl002_00_2  },
};

export constexpr MotionArchiveHelper motionArchiveHelperVergil[] =
{
	{ MOTION_GROUP_VERGIL_BASE                  , pl021_00_0 },
	{ MOTION_GROUP_VERGIL_DAMAGE                , pl021_00_1 },
	{ MOTION_GROUP_VERGIL_TAUNTS                , pl021_00_2 },
	{ MOTION_GROUP_VERGIL_YAMATO                , pl021_00_3 },
	{ MOTION_GROUP_VERGIL_BEOWULF               , pl021_00_4 },
	{ MOTION_GROUP_VERGIL_YAMATO_FORCE_EDGE            , pl021_00_5 },
	{ MOTION_GROUP_VERGIL_DARK_SLAYER           , pl021_00_6 },
	{ MOTION_GROUP_VERGIL_NERO_ANGELO_YAMATO    , pl021_00_7 },
	{ MOTION_GROUP_VERGIL_NERO_ANGELO_BEOWULF   , pl021_00_8 },
	{ MOTION_GROUP_VERGIL_NERO_ANGELO_FORCE_EDGE, pl021_00_9 }, // @Todo: Review.
};

export struct MissionStartHelper
{
	uint16 room;
	uint16 position;
};

export constexpr MissionStartHelper missionStartHelper[] =
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

export struct FloorHelper
{
	uint16 room;
	uint16 position;
};

export constexpr FloorHelper Arcade_floorHelper[] =
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

export enum BOSS
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

export struct BossHelper
{
	uint16 room;
	uint16 position;
	const char * track;
};

export constexpr BossHelper bossHelper[] =
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














