export module Vars;

import Core;

#include "../Core/Macros.h"



namespaceStart(GAMEPAD);
enum
{
	LEFT_TRIGGER   = 0x0001,
	RIGHT_TRIGGER  = 0x0002,
	LEFT_SHOULDER  = 0x0004,
	RIGHT_SHOULDER = 0x0008,
	Y              = 0x0010,
	B              = 0x0020,
	A              = 0x0040,
	X              = 0x0080,
	BACK           = 0x0100,
	LEFT_THUMB     = 0x0200,
	RIGHT_THUMB    = 0x0400,
	START          = 0x0800,
	// Direction ids are the same for dpad, left stick and right stick.
	UP             = 0x1000,
	RIGHT          = 0x2000,
	DOWN           = 0x4000,
	LEFT           = 0x8000,
};
namespaceEnd();




export enum
{
	RESET_STATE_BUTTON_COUNT = 4,
};









// $EventStart

export namespaceStart(EVENT);
enum
{
	IN_GAME = 0x2000,
	TELEPORT = 0x10000000,
};
namespaceEnd();

// $EventEnd


// $ModeStart

export namespaceStart(MODE);
enum
{
	EASY = 2,
	NORMAL = 3,
	HARD = 5,
	DANTE_MUST_DIE = 6,
};
namespaceEnd();

// $ModeEnd



// $CharacterStart

export namespaceStart(CHARACTER);
enum
{
	DANTE,
	LDK,
	SUPER_DANTE,
};
namespaceEnd();

// $CharacterEnd






export enum
{
	MELEE_WEAPON_COUNT = 4,
	RANGED_WEAPON_COUNT = 4,
};





// $WeaponStart

export namespaceStart(WEAPON);
enum
{
	ALASTOR,
	IFRIT,
	SPARDA_AIR,
	SPARDA,
	FORCE_EDGE,
	HANDGUN = 1,
	SHOTGUN,
	GRENADEGUN,
	NIGHTMARE_BETA,
	MELEE_WEAPON_COUNT = 5,
	RANGED_WEAPON_COUNT = 4,
};
namespaceEnd();

// $WeaponEnd

// $MeleeWeaponFormStart

export namespaceStart(MELEE_WEAPON_FORM);
enum
{
	DEFAULT,
	SPARDA,
	YAMATO,
};
namespaceEnd();

// $MeleeWeaponFormEnd



// $Item0Start

export namespaceStart(ITEM_0);
enum
{
	HANDGUN,
	SHOTGUN,
	NEEDLEGUN,
	GRENADEGUN,
	NIGHTMARE_BETA,
	FORCE_EDGE,
	ALASTOR,
	IFRIT,
	SPARDA,
	YAMATO,
};
namespaceEnd();

// $Item0End






// $Item1Start

export namespaceStart(ITEM_1);
enum
{
	BANGLE_OF_TIME,
	LUMINITE,
	UNKNOWN_0,
	UNKNOWN_1,
	YELLOW_ORB,
	UNKNOWN_2,
	BLUE_ORB_BOTTOM_RIGHT,
	BLUE_ORB_TOP_RIGHT,
	BLUE_ORB_BOTTOM_LEFT,
	BLUE_ORB_TOP_LEFT,
	UNKNOWN_3,
	UNKNOWN_4,
	VITAL_STAR,
	DEVIL_STAR,
	UNTOUCHABLE,
	HOLY_WATER,
	RUSTY_KEY,
	STAFF_OF_HERMES,
	AMULET,
	EMBLEM_SHIELD,
};
namespaceEnd();

// $Item1End




// $Item2Start

export namespaceStart(ITEM_2);
enum
{
	UNKNOWN_0,
	UNKNOWN_1,
	YELLOW_ORB,
	UNKNOWN_2,
	BLUE_ORB_BOTTOM_RIGHT,
	BLUE_ORB_TOP_RIGHT,
	BLUE_ORB_BOTTOM_LEFT,
	BLUE_ORB_TOP_LEFT,
	UNKNOWN_3,
	UNKNOWN_4,
	VITAL_STAR,
	DEVIL_STAR,
	UNTOUCHABLE,
	HOLY_WATER,
	RUSTY_KEY,
	STAFF_OF_HERMES,
	AMULET,
	EMBLEM_SHIELD,
};
namespaceEnd();

// $Item2End

static_assert(ITEM_2::VITAL_STAR == 10);
static_assert(ITEM_2::AMULET == 16);









// $Item4Start

export namespaceStart(ITEM_4);
enum
{
	STAFF_OF_JUDGEMENT,
	DEATH_SENTENCE,
	DEATH_SENTENCE_2,
	MELANCHOLY_SOUL,
	TRIDENT,
	GUIDING_LIGHT,
	PRIDE_OF_LION,
};
namespaceEnd();

// $Item4End





// $Item5Start

export namespaceStart(ITEM_5);
enum
{
	EMBLEM_SHIELD,
	KNIGHTS_PORTRAIT,
	SIGN_OF_CHASTITY,
	SIGN_OF_HUMBLENESS,
	SIGN_OF_PERSEVERANCE,
	CHALICE,
	PAIR_OF_LANCES,
	WHEEL_OF_DESTINY,
};
namespaceEnd();

// $Item5End

// $Item6Start

export namespaceStart(ITEM_6);
enum
{
	TOKEN_OF_PHILOSOPHY,
	PHILOSOPHERS_EGG,
	ELIXIR,
	QUICKSILVER,
	PHILOSOPHERS_STONE,
	UNKNOWN_0,
	PERFECT_AMULET,
};
namespaceEnd();

// $Item6End






/*

mission 1

vital star
2
10
1

amulet
2
16
1













*/




















#define _(size) struct { byte8 Prep_Merge(padding_, __LINE__)[size]; }

#pragma pack(push, 1)


export struct ItemData
{
	uint8 category;
	uint8 id;
	uint16 count;
};


// $SessionDataStart

export struct SessionData
{
	byte16 buttons[4]; // 0
	_(46);
	uint8 rightStickX; // 0x36
	uint8 rightStickY; // 0x37
	uint8 leftStickX; // 0x38
	uint8 leftStickY; // 0x39
	_(86);
	byte32 var_90[5]; // 0x90
	_(7168);
	byte32 event; // 0x1CA4
	_(444);
	uint8 mission; // 0x1E64
	_(1);
	uint8 mode; // 0x1E66
	uint8 character; // 0x1E67
	_(288);
	byte32 var_1F88; // 0x1F88
	_(8);
	byte32 var_1F94; // 0x1F94
	bool var_1F98; // 0x1F98
	_(3);
	byte32 var_1F9C; // 0x1F9C
	_(52);
	byte32 var_1FD4; // 0x1FD4
	_(104);
	byte32 state; // 0x2040
	_(55);
	uint8 itemCount; // 0x207B
	_(20);
	ItemData items[1]; // 0x2090
	_(976);
	uint8 hitPoints; // 0x2464
	uint8 magicPoints; // 0x2465
	_(2);
	byte32 expertise; // 0x2468
	_(8);
	uint32 redOrbs; // 0x2474
	_(4);
	byte32 orbFlags; // 0x247C
};

static_assert(offsetof(SessionData, buttons) == 0);
static_assert(offsetof(SessionData, rightStickX) == 0x36);
static_assert(offsetof(SessionData, rightStickY) == 0x37);
static_assert(offsetof(SessionData, leftStickX) == 0x38);
static_assert(offsetof(SessionData, leftStickY) == 0x39);
static_assert(offsetof(SessionData, var_90) == 0x90);
static_assert(offsetof(SessionData, event) == 0x1CA4);
static_assert(offsetof(SessionData, mission) == 0x1E64);
static_assert(offsetof(SessionData, mode) == 0x1E66);
static_assert(offsetof(SessionData, character) == 0x1E67);
static_assert(offsetof(SessionData, var_1F88) == 0x1F88);
static_assert(offsetof(SessionData, var_1F94) == 0x1F94);
static_assert(offsetof(SessionData, var_1F98) == 0x1F98);
static_assert(offsetof(SessionData, var_1F9C) == 0x1F9C);
static_assert(offsetof(SessionData, var_1FD4) == 0x1FD4);
static_assert(offsetof(SessionData, state) == 0x2040);
static_assert(offsetof(SessionData, itemCount) == 0x207B);
static_assert(offsetof(SessionData, items) == 0x2090);
static_assert(offsetof(SessionData, hitPoints) == 0x2464);
static_assert(offsetof(SessionData, magicPoints) == 0x2465);
static_assert(offsetof(SessionData, expertise) == 0x2468);
static_assert(offsetof(SessionData, redOrbs) == 0x2474);
static_assert(offsetof(SessionData, orbFlags) == 0x247C);

static_assert(sizeof(SessionData) == 9344);

// $SessionDataEnd

// $EventDataStart

export struct EventData
{
	_(624);
	uint32 track; // 0x270
	uint32 room; // 0x274
	_(16);
	uint32 nextTrack; // 0x288
	uint32 nextRoom; // 0x28C
};

static_assert(offsetof(EventData, track) == 0x270);
static_assert(offsetof(EventData, room) == 0x274);
static_assert(offsetof(EventData, nextTrack) == 0x288);
static_assert(offsetof(EventData, nextRoom) == 0x28C);

static_assert(sizeof(EventData) == 656);

// $EventDataEnd


// $PlayerActorDataStart

export struct PlayerActorData
{
	byte8 state[8]; // 0
	_(284);
	float rotation; // 0x124
	_(72);
	vec4 position; // 0x170
	_(5666);
	uint16 hitPoints; // 0x17A2
	_(620);
	uint16 idleTimer; // 0x1A10
	_(438);
	uint16 maxHitPoints; // 0x1BC8
	_(2);
	uint8 meleeWeapon; // 0x1BCC
	_(1);
	uint16 magicPointsHuman; // 0x1BCE
	uint16 maxMagicPointsHuman; // 0x1BD0
	uint16 magicPointsDevil; // 0x1BD2
	uint16 maxMagicPointsDevil; // 0x1BD4
	_(114);
	uint8 rangedWeapon; // 0x1C48
	_(3);
	uint8 meleeWeaponForm; // 0x1C4C
	_(25);
	int16 chargeTimers[2]; // 0x1C66
};

static_assert(offsetof(PlayerActorData, state) == 0);
static_assert(offsetof(PlayerActorData, rotation) == 0x124);
static_assert(offsetof(PlayerActorData, position) == 0x170);
static_assert(offsetof(PlayerActorData, hitPoints) == 0x17A2);
static_assert(offsetof(PlayerActorData, idleTimer) == 0x1A10);
static_assert(offsetof(PlayerActorData, maxHitPoints) == 0x1BC8);
static_assert(offsetof(PlayerActorData, meleeWeapon) == 0x1BCC);
static_assert(offsetof(PlayerActorData, magicPointsHuman) == 0x1BCE);
static_assert(offsetof(PlayerActorData, maxMagicPointsHuman) == 0x1BD0);
static_assert(offsetof(PlayerActorData, magicPointsDevil) == 0x1BD2);
static_assert(offsetof(PlayerActorData, maxMagicPointsDevil) == 0x1BD4);
static_assert(offsetof(PlayerActorData, rangedWeapon) == 0x1C48);
static_assert(offsetof(PlayerActorData, meleeWeaponForm) == 0x1C4C);
static_assert(offsetof(PlayerActorData, chargeTimers) == 0x1C66);

static_assert(sizeof(PlayerActorData) == 7274);

// $PlayerActorDataEnd



// $WeaponDataStart

export struct WeaponData
{
	_(43497);
	bool updateRangedWeapon; // 0xA9E9
	_(695);
	bool updateMeleeWeapon; // 0xACA1
};

static_assert(offsetof(WeaponData, updateRangedWeapon) == 0xA9E9);
static_assert(offsetof(WeaponData, updateMeleeWeapon) == 0xACA1);

static_assert(sizeof(WeaponData) == 44194);

// $WeaponDataEnd









// $ScreenEffectDataStart

export struct ScreenEffectData
{
	_(8);
	uint8 r; // 8
	uint8 g; // 9
	uint8 b; // 0xA
	uint8 a; // 0xB
	_(86);
	uint16 timer; // 0x62
	uint8 status; // 0x64
	_(3);
};

static_assert(offsetof(ScreenEffectData, r) == 8);
static_assert(offsetof(ScreenEffectData, g) == 9);
static_assert(offsetof(ScreenEffectData, b) == 0xA);
static_assert(offsetof(ScreenEffectData, a) == 0xB);
static_assert(offsetof(ScreenEffectData, timer) == 0x62);
static_assert(offsetof(ScreenEffectData, status) == 0x64);

static_assert(sizeof(ScreenEffectData) == 104);

// $ScreenEffectDataEnd







#pragma pack(pop)

#undef _







