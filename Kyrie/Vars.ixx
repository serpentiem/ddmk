export module Vars;

import Core;

#include "../Core/Macros.h"




export namespaceStart(MISSION);
enum
{
	BLOODY_PALACE = 50,
};
namespaceEnd();


export namespaceStart(FLOOR);
enum
{
	COUNT = 11,
};
namespaceEnd();


export namespaceStart(PLAYER);
enum
{
	COUNT = 4,
};
namespaceEnd();



// export enum
// {
// 	LoadFileFlags_Unknown,
// 	LoadFileFlags_Force,
// 	LoadFileFlags_Queue,
// };



export namespaceStart(LOAD_TYPE);
enum
{
	FORCE = 1,
	QUEUE,
};
namespaceEnd();








export namespaceStart(ENTITY_TYPE);
enum
{
	PLAYER_ACTOR = 13,
};
namespaceEnd();



export namespaceStart(DLC);
enum
{


LADY_TRISH_COSTUMES = 359496,


/*
https://steamdb.info/app/359496/
*/




};
namespaceEnd();



export namespaceStart(MODE);
enum
{
	HUMAN,
	DEVIL_HUNTER,
	SON_OF_SPARDA,
	DANTE_MUST_DIE,
	LEGENDARY_DARK_KNIGHT,
	COUNT,
};
namespaceEnd();





export namespaceStart(COSTUME);
enum
{
	COUNT = 4,
};
namespaceEnd();





export namespaceStart(CHARACTER);
enum
{
	DANTE,
	NERO,
	VERGIL,
	TRISH,
	LADY,
	COUNT,
};
namespaceEnd();


export namespaceStart(GAME);
enum
{
	NERO_DANTE,
	VERGIL,
	LADY_TRISH,
	COUNT,
};
namespaceEnd();



export namespaceStart(SCENE);
enum
{
	MAIN,
	MISSION_SELECT,
	CUTSCENE_SELECT,
	MISSION_START,
	CUTSCENE,
	GAME,
	GAME_OVER,
	MISSION_RESULT,
	COUNT,
};
namespaceEnd();



export namespaceStart(EVENT);
enum
{
	MAIN,
	PAUSE,
	TELEPORT,
	ITEM,
	CUTSCENE,
	COUNT,
};
namespaceEnd();






#define _(size) struct { byte8 Prep_Merge(padding_, __LINE__)[size]; }

#pragma pack(push, 1)








// export struct KeyData
// {
// 	bool enable;
// 	size_t keys[4];
// 	size_t keyCount;
// };





















// $CameraDataStart

export struct CameraData
{
	_(208);
	float height; // 0xD0
	float tilt; // 0xD4
	float distance; // 0xD8
	float distanceLockOn; // 0xDC
	_(4);
	float fov; // 0xE4
};

static_assert(offsetof(CameraData, height) == 0xD0);
static_assert(offsetof(CameraData, tilt) == 0xD4);
static_assert(offsetof(CameraData, distance) == 0xD8);
static_assert(offsetof(CameraData, distanceLockOn) == 0xDC);
static_assert(offsetof(CameraData, fov) == 0xE4);

static_assert(sizeof(CameraData) == 232);

// $CameraDataEnd



// export struct Gamepad
// {
// 	_(4);
// 	void * addr;
// };

export struct Gamepad
{
	_(4);
	byte8 * addr;
	_(504);
};

static_assert(sizeof(Gamepad) == 0x200);

enum
{
	KEYBOARD_SIZE = 2624,
};

static_assert(KEYBOARD_SIZE == 0xA40);

export struct Keyboard
{
	_(2624);
};








export struct PlayerData
{
	uint32 character;
	uint32 costume;
};

export struct NewActorData
{
	byte8 * baseAddr;
};








// $CharacterDataStart

// CharacterDataBase

export struct CharacterDataBase
{
	bool unlocks[8]; // 0
	_(16);
	byte32 expertise[8]; // 0x18
	uint32 costume; // 0x38
	_(4);
};

static_assert(offsetof(CharacterDataBase, unlocks) == 0);
static_assert(offsetof(CharacterDataBase, expertise) == 0x18);
static_assert(offsetof(CharacterDataBase, costume) == 0x38);

static_assert(sizeof(CharacterDataBase) == 64);

// CharacterDataDante

export struct CharacterDataDante : CharacterDataBase
{
	bool unlocks2[11]; // 0x40
	_(1);
	uint32 styleLevels[4]; // 0x4C
};

static_assert(offsetof(CharacterDataDante, unlocks2) == 0x40);
static_assert(offsetof(CharacterDataDante, styleLevels) == 0x4C);

// CharacterDataNero

export struct CharacterDataNero : CharacterDataBase
{
	bool unlocks2[4]; // 0x40
	uint8 snatchLevel; // 0x44
	uint8 extraExceedCount; // 0x45
	uint8 extraTableHopperCount; // 0x46
};

static_assert(offsetof(CharacterDataNero, unlocks2) == 0x40);
static_assert(offsetof(CharacterDataNero, snatchLevel) == 0x44);
static_assert(offsetof(CharacterDataNero, extraExceedCount) == 0x45);
static_assert(offsetof(CharacterDataNero, extraTableHopperCount) == 0x46);

// CharacterDataVergil

export struct CharacterDataVergil : CharacterDataBase
{
	bool unlocks2[2]; // 0x40
	uint8 summonedSwordsLevel; // 0x42
};

static_assert(offsetof(CharacterDataVergil, unlocks2) == 0x40);
static_assert(offsetof(CharacterDataVergil, summonedSwordsLevel) == 0x42);

// CharacterDataTrish

export struct CharacterDataTrish : CharacterDataBase
{
	bool unlocks2[1]; // 0x40
};

static_assert(offsetof(CharacterDataTrish, unlocks2) == 0x40);

// CharacterDataLady

export struct CharacterDataLady : CharacterDataBase
{
	uint8 kalinaAnnChargeCount; // 0x40
};

static_assert(offsetof(CharacterDataLady, kalinaAnnChargeCount) == 0x40);

// CharacterData

export struct CharacterData
{
	_(120);
	float hitPoints; // 0x78
	float magicPoints; // 0x7C
	_(232);
	CharacterDataDante Dante; // 0x168
	_(172);
	CharacterDataNero Nero; // 0x270
	_(169);
	CharacterDataVergil Vergil; // 0x360
	_(185);
	CharacterDataTrish Trish; // 0x45C
	_(199);
	CharacterDataLady Lady; // 0x564
};

static_assert(offsetof(CharacterData, hitPoints) == 0x78);
static_assert(offsetof(CharacterData, magicPoints) == 0x7C);
static_assert(offsetof(CharacterData, Dante) == 0x168);
static_assert(offsetof(CharacterData, Nero) == 0x270);
static_assert(offsetof(CharacterData, Vergil) == 0x360);
static_assert(offsetof(CharacterData, Trish) == 0x45C);
static_assert(offsetof(CharacterData, Lady) == 0x564);

static_assert(sizeof(CharacterData) == 1445);

// $CharacterDataEnd



// $SessionDataStart

export struct SessionData
{
	_(36);
	byte8 * mainActorBaseAddr; // 0x24
	_(296);
	uint32 mission; // 0x150
	_(104);
	uint32 game; // 0x1BC
	_(128);
	uint32 mode; // 0x240
	_(628);
	CharacterDataBase characterData; // 0x4B8
};

static_assert(offsetof(SessionData, mainActorBaseAddr) == 0x24);
static_assert(offsetof(SessionData, mission) == 0x150);
static_assert(offsetof(SessionData, game) == 0x1BC);
static_assert(offsetof(SessionData, mode) == 0x240);
static_assert(offsetof(SessionData, characterData) == 0x4B8);

static_assert(sizeof(SessionData) == 1272);

// $SessionDataEnd


// $PlayerActorDataStart

export struct PlayerActorData
{
	_(64);
	vec4 position; // 0x40
	_(6488);
	uint32 costume; // 0x19A8
	uint32 character; // 0x19AC
	_(109);
	bool enable; // 0x1A1D
	_(226);
	float hitPoints; // 0x1B00
	float maxHitPoints; // 0x1B04
	_(2556);
	float magicPoints; // 0x2504
	float maxMagicPoints; // 0x2508
};

static_assert(offsetof(PlayerActorData, position) == 0x40);
static_assert(offsetof(PlayerActorData, costume) == 0x19A8);
static_assert(offsetof(PlayerActorData, character) == 0x19AC);
static_assert(offsetof(PlayerActorData, enable) == 0x1A1D);
static_assert(offsetof(PlayerActorData, hitPoints) == 0x1B00);
static_assert(offsetof(PlayerActorData, maxHitPoints) == 0x1B04);
static_assert(offsetof(PlayerActorData, magicPoints) == 0x2504);
static_assert(offsetof(PlayerActorData, maxMagicPoints) == 0x2508);

static_assert(sizeof(PlayerActorData) == 9484);

// $PlayerActorDataEnd






// $EventDataStart

export struct EventData
{
	_(4);
	uint8 event; // 4
	_(43);
	uint32 room; // 0x30
};

static_assert(offsetof(EventData, event) == 4);
static_assert(offsetof(EventData, room) == 0x30);

static_assert(sizeof(EventData) == 52);

// $EventDataEnd



// $NextEventDataStart

export struct NextEventData
{
	_(132);
	uint32 useDoor; // 0x84
	uint32 room; // 0x88
	uint32 position; // 0x8C
	uint32 level; // 0x90
	_(12);
	bool usePosition; // 0xA0
};

static_assert(offsetof(NextEventData, useDoor) == 0x84);
static_assert(offsetof(NextEventData, room) == 0x88);
static_assert(offsetof(NextEventData, position) == 0x8C);
static_assert(offsetof(NextEventData, level) == 0x90);
static_assert(offsetof(NextEventData, usePosition) == 0xA0);

static_assert(sizeof(NextEventData) == 161);

// $NextEventDataEnd



// $SessionEventDataStart

export struct SessionEventData
{
	_(48);
	uint8 character; // 0x30
};

static_assert(offsetof(SessionEventData, character) == 0x30);

static_assert(sizeof(SessionEventData) == 49);

// $SessionEventDataEnd





#pragma pack(pop)

#undef _



export struct FilterHelper
{
	const char * name;
	uint64 off;
};

export constexpr FilterHelper filterHelpers[] =
{
	// { "SystemFilter"                , 0xB9E564 },
	// { "mFootAdjustFilter"           , 0xBA1608 },
	// { "Sunny Cross Filter"          , 0xBA1918 },
	// { "Snow Cross Filter"           , 0xBA1940 },
	// { "Cross Screen Filter"         , 0xBA196C },
	// { "Cross Screen Filter"         , 0xBA196C },
	// { "mConeFilter"                 , 0xBA2D80 },
	// { "uFilter"                     , 0xBA3A84 },
	{ "uDOFFilter"                  , 0xBA3A8C },
	// { "uTVNoiseFilter"              , 0xBA3A98 },
	// { "uCrossFadeFilter"            , 0xBA3ABC },
	// { "uVolumeNoiseFilter"          , 0xBA3AD0 },
	// { "uNoiseFogFilter"             , 0xBA3AE4 },
	// { "uRadialBlurFilter"           , 0xBA3AF4 },
	// { "uHazeFilter"                 , 0xBA3B08 },
	// { "uFishEyeFilter"              , 0xBA3B14 },
	// { "uColorFogFilter"             , 0xBA3B24 },
	{ "uBlurFilter"                 , 0xBA3B34 },
	// { "uColorCorrectFilter"         , 0xBA3B60 },
	// { "uLightScatteringFilter"      , 0xBA3B74 },
	{ "uBloomFilter"                , 0xBA3B8C },
	{ "uAmbientOcclusionFilter"     , 0xBA3BAC },
	// { "uOutlineFilter"              , 0xBA3BE0 },
	// { "uBokehFilter"                , 0xBA3BF0 },
	// { "uEdgeAntiAliasingFilter"     , 0xBA3C00 },
	{ "uGodRaysFilter"              , 0xBA3C18 },
	// { "uChromaticAberrationFilter"  , 0xBA3C28 },
	// { "uTangentBlurFilter"          , 0xBA3C44 },
	// { "uToneMapFilter"              , 0xBA3C58 },
	// { "uLevelCorrectFilter"         , 0xBA3C68 },
	// { "uHSVFilter"                  , 0xBA3C7C },
	// { "UseIconFontFilter"           , 0xBA81A4 },
	// { "mColliderFilter"             , 0xBAC004 },
	// { "mSbcFilter"                  , 0xBAC04C },
	// { "cParticleGeneratorFilter"    , 0xBB0480 },
	//{ "uMultiBlurFilter"            , 0xBB0E88 },
	//{ "uMultiGodRaysFilter"         , 0xBB0E9C },
	// { "uMultiColorCorrectFilter"    , 0xBB0EB0 },
	//{ "uMultiBloomFilter"           , 0xBB0ECC },
	// { "nCollision::cScrCommonFilter", 0xBB2044 },
	// { "uMultiFilter"                , 0xC1C908 },
	// { "cGUIFontFilter"              , 0xC1CA14 },
	{ "uMotionBlurFilter"           , 0xC57810 },
	// { "mpFilter"                    , 0xC6F960 },
	// { "TextureFilter"               , 0xC761EC },
	// { "UnhandledExceptionFilter"    , 0xC9AA46 },
	// { "SetUnhandledExceptionFilter" , 0xC9AA62 },
};

































