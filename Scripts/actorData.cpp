#define _(size) struct { byte8 padding[size]; }

#pragma pack(push, 1)

struct ACTOR_DATA
{
	_(120);
	uint8 characterLogic; // 0x78
	_(7);
	vec4 position; // 0x80
	_(48);
	uint16 direction; // 0xC0
	_(86);
	uint8 actorId; // 0x118
	_(3);
	bool isDoppelganger; // 0x11C
	_(3);
	uint8 visible; // 0x120
	_(14207);
	byte8 * motionFile[32]; // 0x38A0
	_(16);
	MOTION_DATA motionData[5]; // 0x39B0
	_(94);
	uint8 shadow; // 0x3A18
	_(15);
	byte32 color; // 0x3A28
	_(980);
	byte32 motionState1[4]; // 0x3E00
	_(10);
	uint16 chargedShotAir; // 0x3E1A
	_(6);
	uint16 chargedShot; // 0x3E22
	_(20);
	float32 idleTimer; // 0x3E38
	_(36);
	byte32 motionState2[3]; // 0x3E60
	uint8 activeModel; // 0x3E6C
	_(3);
	uint8 queuedModel; // 0x3E70
	_(3);
	uint32 modelIndex[3]; // 0x3E74
	uint8 modelState; // 0x3E80
	_(3);
	bool lockOn; // 0x3E84
	_(3);
	uint8 modelIndexMirror; // 0x3E88
	_(11);
	uint8 devilState; // 0x3E94
	_(6);
	bool devil; // 0x3E9B
	_(2);
	uint8 costume; // 0x3E9E
	bool specialCostume; // 0x3E9F
	_(24);
	float32 magicPoints; // 0x3EB8
	float32 maxMagicPoints; // 0x3EBC
	_(228);
	uint8 move; // 0x3FA4
	uint8 lastMove; // 0x3FA5
	_(6);
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
	uint8 style; // 0x6338
	_(31);
	uint8 styleLevel; // 0x6358
	_(3);
	uint8 dashCount; // 0x635C
	uint8 skyStarCount; // 0x635D
	uint8 airTrickCount; // 0x635E
	uint8 trickUpCount; // 0x635F
	uint8 trickDownCount; // 0x6360
	bool quicksilver; // 0x6361
	bool doppelganger; // 0x6362
	_(1);
	float32 styleExperience; // 0x6364
	_(236);
	bool controlLinkedActor; // 0x6454
	_(35);
	byte8 * linkedActorBaseAddr; // 0x6478
	_(8);
	uint8 selectedMeleeWeaponVergil; // 0x6488
	_(4);
	uint8 activeWeapon; // 0x648D
	_(2);
	uint8 selectedMeleeWeapon; // 0x6490
	_(3);
	uint8 selectedRangedWeapon; // 0x6494
	_(3);
	uint8 equipment[4]; // 0x6498
	_(4);
	byte8 * weaponMetadata[4]; // 0x64A0
	_(8);
	byte32 weaponFlags[4]; // 0x64C8
	_(24);
	uint8 activeMeleeWeapon; // 0x64F0
	uint8 activeRangedWeapon; // 0x64F1
	_(2);
	float32 weaponTimer[4]; // 0x64F4
	_(12);
	uint8 styleRank; // 0x6510
	_(3);
	float32 styleMeter; // 0x6514
	_(348);
	INPUT_DATA inputData[58]; // 0x6674
	_(2868);
	vec4 interactionData[8]; // 0x7460
	byte16 buttonInput[4]; // 0x74E0
	_(16712);
	MODEL_DATA modelData[6]; // 0xB630
	_(88);
	float32 artemisChargeValue[2]; // 0xB868
	_(12);
	byte32 artemisChargeFlags[2]; // 0xB87C
	_(60);
	uint8 character; // 0xB8C0
	bool noActorCollision; // 0xB8C1
	bool noEnemyCollision; // 0xB8C2
	_(5);
	byte8 * parentBaseAddr; // 0xB8C8
	byte8 * childBaseAddr[4]; // 0xB8D0
	bool hide; // 0xB8F0
	uint8 gamepad; // 0xB8F1
	byte16 buttonMask; // 0xB8F2
	byte16 leftStickMask; // 0xB8F4
	_(2);
	uint8 styleMap[6][2]; // 0xB8F8
	uint8 meleeWeaponCount; // 0xB904
	_(3);
	uint8 meleeWeaponMap[5]; // 0xB908
	uint8 rangedWeaponCount; // 0xB90D
	_(2);
	uint8 rangedWeaponMap[5]; // 0xB910
};

#pragma pack(pop)

#undef _

static_assert(offsetof(ACTOR_DATA, characterLogic) == 0x78);
static_assert(offsetof(ACTOR_DATA, position) == 0x80);
static_assert(offsetof(ACTOR_DATA, direction) == 0xC0);
static_assert(offsetof(ACTOR_DATA, actorId) == 0x118);
static_assert(offsetof(ACTOR_DATA, isDoppelganger) == 0x11C);
static_assert(offsetof(ACTOR_DATA, visible) == 0x120);
static_assert(offsetof(ACTOR_DATA, motionFile) == 0x38A0);
static_assert(offsetof(ACTOR_DATA, motionData) == 0x39B0);
static_assert(offsetof(ACTOR_DATA, shadow) == 0x3A18);
static_assert(offsetof(ACTOR_DATA, color) == 0x3A28);
static_assert(offsetof(ACTOR_DATA, motionState1) == 0x3E00);
static_assert(offsetof(ACTOR_DATA, chargedShotAir) == 0x3E1A);
static_assert(offsetof(ACTOR_DATA, chargedShot) == 0x3E22);
static_assert(offsetof(ACTOR_DATA, idleTimer) == 0x3E38);
static_assert(offsetof(ACTOR_DATA, motionState2) == 0x3E60);
static_assert(offsetof(ACTOR_DATA, activeModel) == 0x3E6C);
static_assert(offsetof(ACTOR_DATA, queuedModel) == 0x3E70);
static_assert(offsetof(ACTOR_DATA, modelIndex) == 0x3E74);
static_assert(offsetof(ACTOR_DATA, modelState) == 0x3E80);
static_assert(offsetof(ACTOR_DATA, lockOn) == 0x3E84);
static_assert(offsetof(ACTOR_DATA, modelIndexMirror) == 0x3E88);
static_assert(offsetof(ACTOR_DATA, devilState) == 0x3E94);
static_assert(offsetof(ACTOR_DATA, devil) == 0x3E9B);
static_assert(offsetof(ACTOR_DATA, costume) == 0x3E9E);
static_assert(offsetof(ACTOR_DATA, specialCostume) == 0x3E9F);
static_assert(offsetof(ACTOR_DATA, magicPoints) == 0x3EB8);
static_assert(offsetof(ACTOR_DATA, maxMagicPoints) == 0x3EBC);
static_assert(offsetof(ACTOR_DATA, move) == 0x3FA4);
static_assert(offsetof(ACTOR_DATA, lastMove) == 0x3FA5);
static_assert(offsetof(ACTOR_DATA, chainCount) == 0x3FAC);
static_assert(offsetof(ACTOR_DATA, expertise) == 0x3FEC);
static_assert(offsetof(ACTOR_DATA, maxHitPoints) == 0x40EC);
static_assert(offsetof(ACTOR_DATA, hitPoints) == 0x411C);
static_assert(offsetof(ACTOR_DATA, targetBaseAddr) == 0x6328);
static_assert(offsetof(ACTOR_DATA, style) == 0x6338);
static_assert(offsetof(ACTOR_DATA, styleLevel) == 0x6358);
static_assert(offsetof(ACTOR_DATA, dashCount) == 0x635C);
static_assert(offsetof(ACTOR_DATA, skyStarCount) == 0x635D);
static_assert(offsetof(ACTOR_DATA, airTrickCount) == 0x635E);
static_assert(offsetof(ACTOR_DATA, trickUpCount) == 0x635F);
static_assert(offsetof(ACTOR_DATA, trickDownCount) == 0x6360);
static_assert(offsetof(ACTOR_DATA, quicksilver) == 0x6361);
static_assert(offsetof(ACTOR_DATA, doppelganger) == 0x6362);
static_assert(offsetof(ACTOR_DATA, styleExperience) == 0x6364);
static_assert(offsetof(ACTOR_DATA, controlLinkedActor) == 0x6454);
static_assert(offsetof(ACTOR_DATA, linkedActorBaseAddr) == 0x6478);
static_assert(offsetof(ACTOR_DATA, selectedMeleeWeaponVergil) == 0x6488);
static_assert(offsetof(ACTOR_DATA, activeWeapon) == 0x648D);
static_assert(offsetof(ACTOR_DATA, selectedMeleeWeapon) == 0x6490);
static_assert(offsetof(ACTOR_DATA, selectedRangedWeapon) == 0x6494);
static_assert(offsetof(ACTOR_DATA, equipment) == 0x6498);
static_assert(offsetof(ACTOR_DATA, weaponMetadata) == 0x64A0);
static_assert(offsetof(ACTOR_DATA, weaponFlags) == 0x64C8);
static_assert(offsetof(ACTOR_DATA, activeMeleeWeapon) == 0x64F0);
static_assert(offsetof(ACTOR_DATA, activeRangedWeapon) == 0x64F1);
static_assert(offsetof(ACTOR_DATA, weaponTimer) == 0x64F4);
static_assert(offsetof(ACTOR_DATA, styleRank) == 0x6510);
static_assert(offsetof(ACTOR_DATA, styleMeter) == 0x6514);
static_assert(offsetof(ACTOR_DATA, inputData) == 0x6674);
static_assert(offsetof(ACTOR_DATA, interactionData) == 0x7460);
static_assert(offsetof(ACTOR_DATA, buttonInput) == 0x74E0);
static_assert(offsetof(ACTOR_DATA, modelData) == 0xB630);
static_assert(offsetof(ACTOR_DATA, artemisChargeValue) == 0xB868);
static_assert(offsetof(ACTOR_DATA, artemisChargeFlags) == 0xB87C);
static_assert(offsetof(ACTOR_DATA, character) == 0xB8C0);
static_assert(offsetof(ACTOR_DATA, noActorCollision) == 0xB8C1);
static_assert(offsetof(ACTOR_DATA, noEnemyCollision) == 0xB8C2);
static_assert(offsetof(ACTOR_DATA, parentBaseAddr) == 0xB8C8);
static_assert(offsetof(ACTOR_DATA, childBaseAddr) == 0xB8D0);
static_assert(offsetof(ACTOR_DATA, hide) == 0xB8F0);
static_assert(offsetof(ACTOR_DATA, gamepad) == 0xB8F1);
static_assert(offsetof(ACTOR_DATA, buttonMask) == 0xB8F2);
static_assert(offsetof(ACTOR_DATA, leftStickMask) == 0xB8F4);
static_assert(offsetof(ACTOR_DATA, styleMap) == 0xB8F8);
static_assert(offsetof(ACTOR_DATA, meleeWeaponCount) == 0xB904);
static_assert(offsetof(ACTOR_DATA, meleeWeaponMap) == 0xB908);
static_assert(offsetof(ACTOR_DATA, rangedWeaponCount) == 0xB90D);
static_assert(offsetof(ACTOR_DATA, rangedWeaponMap) == 0xB910);
