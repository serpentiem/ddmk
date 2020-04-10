struct ACTOR_DATA_DANTE;
struct ACTOR_DATA_VERGIL;

struct ACTOR_DATA_DANTE
{
	_(8);
	bool init; // 0x8
	_(111);
	uint32 character; // 0x78
	_(4);
	vec4 position; // 0x80
	_(48);
	uint16 direction; // 0xC0
	_(86);
	uint8 id; // 0x118
	_(3);
	bool isClone; // 0x11C
	_(3);
	uint32 visible; // 0x120
	_(220);
	MODEL_DATA modelData[3]; // 0x200
	_(8224);
	byte8 * motionArchive[32]; // 0x38A0
	_(16);
	MOTION_DATA motionData[5]; // 0x39B0
	_(94);
	uint32 shadow; // 0x3A18
	_(12);
	byte32 color; // 0x3A28
	_(932);
	byte8 * actionData[6]; // 0x3DD0
	byte32 motionState1[6]; // 0x3E00
	_(2);
	uint16 chargedShotAir; // 0x3E1A
	_(6);
	uint16 chargedShot; // 0x3E22
	_(16);
	float32 motionTimer; // 0x3E34
	float32 idleTimer; // 0x3E38
	_(36);
	byte32 motionState2[3]; // 0x3E60
	uint32 activeModel; // 0x3E6C
	uint32 queuedModel; // 0x3E70
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
	bool spardaCostume; // 0x3E9F
	_(24);
	float32 magicPoints; // 0x3EB8
	float32 maxMagicPoints; // 0x3EBC
	_(24);
	uint16 cameraDirection; // 0x3ED8
	_(202);
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
	uint32 weaponIndex[2]; // 0x6490
	uint8 weaponMap[5]; // 0x6498
	_(3);
	byte8 * weaponData[5]; // 0x64A0
	byte32 weaponFlags[5]; // 0x64C8
	_(24);
	float32 weaponTimer[5]; // 0x64F4
	float32 weaponTimeout[2]; // 0x6508
	uint8 styleRank; // 0x6510
	_(3);
	float32 styleMeter; // 0x6514
	_(348);
	INPUT_DATA inputData[58]; // 0x6674
	_(2344);
	uint32 collisionIndex; // 0x7254
	_(520);
	vec4 interactionData[8]; // 0x7460
	byte16 buttons[4]; // 0x74E0
	_(16);
	byte16 rightStick[2]; // 0x74F8
	_(12);
	byte16 leftStick[2]; // 0x7508
	uint16 actorCameraDirection; // 0x750C
	_(14);
	uint32 leftStickDirection[2]; // 0x751C
	_(16604);
	DEVIL_MODEL_METADATA_DANTE devilModelMetadata; // 0xB600
	_(15);
	MODEL_METADATA modelMetadata[6]; // 0xB630
	_(88);
	float32 artemisChargeValue[2]; // 0xB868
	_(12);
	byte32 artemisChargeFlags[2]; // 0xB87C
	_(60);
	uint8 characterModel; // 0xB8C0
	_(7);
	byte8 * parentBaseAddr; // 0xB8C8
	byte8 * childBaseAddr[4]; // 0xB8D0
	uint8 gamepad; // 0xB8F0
	byte16 buttonMask; // 0xB8F1
	bool copyPosition; // 0xB8F3
	uint8 newStyle; // 0xB8F4
	_(3);
	uint8 styleMap[5][2]; // 0xB8F8
	_(6);
	byte8 * newWeaponData[16]; // 0xB908
	uint8 meleeWeaponMap[5]; // 0xB988
	uint8 meleeWeaponCount; // 0xB98D
	uint8 meleeWeaponIndex; // 0xB98E
	_(1);
	uint8 rangedWeaponMap[5]; // 0xB990
	uint8 rangedWeaponCount; // 0xB995
	uint8 rangedWeaponIndex; // 0xB996

	operator ACTOR_DATA_VERGIL &()
	{
		return *reinterpret_cast<ACTOR_DATA_VERGIL *>(this);
	}
};

struct ACTOR_DATA_VERGIL
{
	_(8);
	bool init; // 0x8
	_(111);
	uint32 character; // 0x78
	_(4);
	vec4 position; // 0x80
	_(48);
	uint16 direction; // 0xC0
	_(86);
	uint8 id; // 0x118
	_(3);
	bool isClone; // 0x11C
	_(3);
	uint32 visible; // 0x120
	_(220);
	MODEL_DATA modelData[3]; // 0x200
	_(8224);
	byte8 * motionArchive[32]; // 0x38A0
	_(16);
	MOTION_DATA motionData[5]; // 0x39B0
	_(94);
	uint32 shadow; // 0x3A18
	_(12);
	byte32 color; // 0x3A28
	_(932);
	byte8 * actionData[6]; // 0x3DD0
	byte32 motionState1[6]; // 0x3E00
	_(28);
	float32 motionTimer; // 0x3E34
	float32 idleTimer; // 0x3E38
	_(36);
	byte32 motionState2[3]; // 0x3E60
	uint32 activeModel; // 0x3E6C
	uint32 queuedModel; // 0x3E70
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
	bool spardaCostume; // 0x3E9F
	_(24);
	float32 magicPoints; // 0x3EB8
	float32 maxMagicPoints; // 0x3EBC
	_(24);
	uint16 cameraDirection; // 0x3ED8
	_(202);
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
	uint32 style; // 0x6338
	_(28);
	uint32 styleLevel; // 0x6358
	_(2);
	uint8 airTrickCount; // 0x635E
	uint8 trickUpCount; // 0x635F
	uint8 trickDownCount; // 0x6360
	_(3);
	float32 styleExperience; // 0x6364
	_(284);
	uint32 weaponIndex[2]; // 0x6484
	_(12);
	uint8 weaponMap[5]; // 0x6498
	_(3);
	byte8 * weaponData[5]; // 0x64A0
	byte32 weaponFlags[5]; // 0x64C8
	_(24);
	float32 weaponTimer[5]; // 0x64F4
	float32 weaponTimeout[2]; // 0x6508
	uint8 styleRank; // 0x6510
	_(3);
	float32 styleMeter; // 0x6514
	_(348);
	INPUT_DATA inputData[58]; // 0x6674
	_(2344);
	uint32 collisionIndex; // 0x7254
	_(520);
	vec4 interactionData[8]; // 0x7460
	byte16 buttons[4]; // 0x74E0
	_(16);
	byte16 rightStick[2]; // 0x74F8
	_(12);
	byte16 leftStick[2]; // 0x7508
	uint16 actorCameraDirection; // 0x750C
	_(14);
	uint32 leftStickDirection[2]; // 0x751C
	_(16668);
	MODEL_METADATA modelMetadata[6]; // 0xB640
	_(160);
	uint8 characterModel; // 0xB8C0
	_(7);
	byte8 * parentBaseAddr; // 0xB8C8
	byte8 * childBaseAddr[4]; // 0xB8D0
	uint8 gamepad; // 0xB8F0
	byte16 buttonMask; // 0xB8F1
	bool copyPosition; // 0xB8F3
	uint8 newStyle; // 0xB8F4
	_(3);
	uint8 styleMap[5][2]; // 0xB8F8
	_(6);
	byte8 * newWeaponData[16]; // 0xB908
	uint8 meleeWeaponMap[5]; // 0xB988
	uint8 meleeWeaponCount; // 0xB98D
	uint8 meleeWeaponIndex; // 0xB98E
	_(1);
	uint8 rangedWeaponMap[5]; // 0xB990
	uint8 rangedWeaponCount; // 0xB995
	uint8 rangedWeaponIndex; // 0xB996

	operator ACTOR_DATA_DANTE &()
	{
		return *reinterpret_cast<ACTOR_DATA_DANTE *>(this);
	}
};

typedef ACTOR_DATA_DANTE ACTOR_DATA;

static_assert(offsetof(ACTOR_DATA_DANTE, init) == 0x8);
static_assert(offsetof(ACTOR_DATA_DANTE, character) == 0x78);
static_assert(offsetof(ACTOR_DATA_DANTE, position) == 0x80);
static_assert(offsetof(ACTOR_DATA_DANTE, direction) == 0xC0);
static_assert(offsetof(ACTOR_DATA_DANTE, id) == 0x118);
static_assert(offsetof(ACTOR_DATA_DANTE, isClone) == 0x11C);
static_assert(offsetof(ACTOR_DATA_DANTE, visible) == 0x120);
static_assert(offsetof(ACTOR_DATA_DANTE, modelData) == 0x200);
static_assert(offsetof(ACTOR_DATA_DANTE, motionArchive) == 0x38A0);
static_assert(offsetof(ACTOR_DATA_DANTE, motionData) == 0x39B0);
static_assert(offsetof(ACTOR_DATA_DANTE, shadow) == 0x3A18);
static_assert(offsetof(ACTOR_DATA_DANTE, color) == 0x3A28);
static_assert(offsetof(ACTOR_DATA_DANTE, actionData) == 0x3DD0);
static_assert(offsetof(ACTOR_DATA_DANTE, motionState1) == 0x3E00);
static_assert(offsetof(ACTOR_DATA_DANTE, chargedShotAir) == 0x3E1A);
static_assert(offsetof(ACTOR_DATA_DANTE, chargedShot) == 0x3E22);
static_assert(offsetof(ACTOR_DATA_DANTE, motionTimer) == 0x3E34);
static_assert(offsetof(ACTOR_DATA_DANTE, idleTimer) == 0x3E38);
static_assert(offsetof(ACTOR_DATA_DANTE, motionState2) == 0x3E60);
static_assert(offsetof(ACTOR_DATA_DANTE, activeModel) == 0x3E6C);
static_assert(offsetof(ACTOR_DATA_DANTE, queuedModel) == 0x3E70);
static_assert(offsetof(ACTOR_DATA_DANTE, modelIndex) == 0x3E74);
static_assert(offsetof(ACTOR_DATA_DANTE, modelState) == 0x3E80);
static_assert(offsetof(ACTOR_DATA_DANTE, lockOn) == 0x3E84);
static_assert(offsetof(ACTOR_DATA_DANTE, modelIndexMirror) == 0x3E88);
static_assert(offsetof(ACTOR_DATA_DANTE, devilState) == 0x3E94);
static_assert(offsetof(ACTOR_DATA_DANTE, devil) == 0x3E9B);
static_assert(offsetof(ACTOR_DATA_DANTE, costume) == 0x3E9E);
static_assert(offsetof(ACTOR_DATA_DANTE, spardaCostume) == 0x3E9F);
static_assert(offsetof(ACTOR_DATA_DANTE, magicPoints) == 0x3EB8);
static_assert(offsetof(ACTOR_DATA_DANTE, maxMagicPoints) == 0x3EBC);
static_assert(offsetof(ACTOR_DATA_DANTE, cameraDirection) == 0x3ED8);
static_assert(offsetof(ACTOR_DATA_DANTE, move) == 0x3FA4);
static_assert(offsetof(ACTOR_DATA_DANTE, lastMove) == 0x3FA5);
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
static_assert(offsetof(ACTOR_DATA_DANTE, weaponIndex) == 0x6490);
static_assert(offsetof(ACTOR_DATA_DANTE, weaponMap) == 0x6498);
static_assert(offsetof(ACTOR_DATA_DANTE, weaponData) == 0x64A0);
static_assert(offsetof(ACTOR_DATA_DANTE, weaponFlags) == 0x64C8);
static_assert(offsetof(ACTOR_DATA_DANTE, weaponTimer) == 0x64F4);
static_assert(offsetof(ACTOR_DATA_DANTE, weaponTimeout) == 0x6508);
static_assert(offsetof(ACTOR_DATA_DANTE, styleRank) == 0x6510);
static_assert(offsetof(ACTOR_DATA_DANTE, styleMeter) == 0x6514);
static_assert(offsetof(ACTOR_DATA_DANTE, inputData) == 0x6674);
static_assert(offsetof(ACTOR_DATA_DANTE, collisionIndex) == 0x7254);
static_assert(offsetof(ACTOR_DATA_DANTE, interactionData) == 0x7460);
static_assert(offsetof(ACTOR_DATA_DANTE, buttons) == 0x74E0);
static_assert(offsetof(ACTOR_DATA_DANTE, rightStick) == 0x74F8);
static_assert(offsetof(ACTOR_DATA_DANTE, leftStick) == 0x7508);
static_assert(offsetof(ACTOR_DATA_DANTE, actorCameraDirection) == 0x750C);
static_assert(offsetof(ACTOR_DATA_DANTE, leftStickDirection) == 0x751C);
static_assert(offsetof(ACTOR_DATA_DANTE, devilModelMetadata) == 0xB600);
static_assert(offsetof(ACTOR_DATA_DANTE, modelMetadata) == 0xB630);
static_assert(offsetof(ACTOR_DATA_DANTE, artemisChargeValue) == 0xB868);
static_assert(offsetof(ACTOR_DATA_DANTE, artemisChargeFlags) == 0xB87C);
static_assert(offsetof(ACTOR_DATA_DANTE, characterModel) == 0xB8C0);
static_assert(offsetof(ACTOR_DATA_DANTE, parentBaseAddr) == 0xB8C8);
static_assert(offsetof(ACTOR_DATA_DANTE, childBaseAddr) == 0xB8D0);
static_assert(offsetof(ACTOR_DATA_DANTE, gamepad) == 0xB8F0);
static_assert(offsetof(ACTOR_DATA_DANTE, buttonMask) == 0xB8F1);
static_assert(offsetof(ACTOR_DATA_DANTE, copyPosition) == 0xB8F3);
static_assert(offsetof(ACTOR_DATA_DANTE, newStyle) == 0xB8F4);
static_assert(offsetof(ACTOR_DATA_DANTE, styleMap) == 0xB8F8);
static_assert(offsetof(ACTOR_DATA_DANTE, newWeaponData) == 0xB908);
static_assert(offsetof(ACTOR_DATA_DANTE, meleeWeaponMap) == 0xB988);
static_assert(offsetof(ACTOR_DATA_DANTE, meleeWeaponCount) == 0xB98D);
static_assert(offsetof(ACTOR_DATA_DANTE, meleeWeaponIndex) == 0xB98E);
static_assert(offsetof(ACTOR_DATA_DANTE, rangedWeaponMap) == 0xB990);
static_assert(offsetof(ACTOR_DATA_DANTE, rangedWeaponCount) == 0xB995);
static_assert(offsetof(ACTOR_DATA_DANTE, rangedWeaponIndex) == 0xB996);

static_assert(offsetof(ACTOR_DATA_VERGIL, init) == 0x8);
static_assert(offsetof(ACTOR_DATA_VERGIL, character) == 0x78);
static_assert(offsetof(ACTOR_DATA_VERGIL, position) == 0x80);
static_assert(offsetof(ACTOR_DATA_VERGIL, direction) == 0xC0);
static_assert(offsetof(ACTOR_DATA_VERGIL, id) == 0x118);
static_assert(offsetof(ACTOR_DATA_VERGIL, isClone) == 0x11C);
static_assert(offsetof(ACTOR_DATA_VERGIL, visible) == 0x120);
static_assert(offsetof(ACTOR_DATA_VERGIL, modelData) == 0x200);
static_assert(offsetof(ACTOR_DATA_VERGIL, motionArchive) == 0x38A0);
static_assert(offsetof(ACTOR_DATA_VERGIL, motionData) == 0x39B0);
static_assert(offsetof(ACTOR_DATA_VERGIL, shadow) == 0x3A18);
static_assert(offsetof(ACTOR_DATA_VERGIL, color) == 0x3A28);
static_assert(offsetof(ACTOR_DATA_VERGIL, actionData) == 0x3DD0);
static_assert(offsetof(ACTOR_DATA_VERGIL, motionState1) == 0x3E00);
static_assert(offsetof(ACTOR_DATA_VERGIL, motionTimer) == 0x3E34);
static_assert(offsetof(ACTOR_DATA_VERGIL, idleTimer) == 0x3E38);
static_assert(offsetof(ACTOR_DATA_VERGIL, motionState2) == 0x3E60);
static_assert(offsetof(ACTOR_DATA_VERGIL, activeModel) == 0x3E6C);
static_assert(offsetof(ACTOR_DATA_VERGIL, queuedModel) == 0x3E70);
static_assert(offsetof(ACTOR_DATA_VERGIL, modelIndex) == 0x3E74);
static_assert(offsetof(ACTOR_DATA_VERGIL, modelState) == 0x3E80);
static_assert(offsetof(ACTOR_DATA_VERGIL, lockOn) == 0x3E84);
static_assert(offsetof(ACTOR_DATA_VERGIL, modelIndexMirror) == 0x3E88);
static_assert(offsetof(ACTOR_DATA_VERGIL, devilState) == 0x3E94);
static_assert(offsetof(ACTOR_DATA_VERGIL, devil) == 0x3E9B);
static_assert(offsetof(ACTOR_DATA_VERGIL, costume) == 0x3E9E);
static_assert(offsetof(ACTOR_DATA_VERGIL, spardaCostume) == 0x3E9F);
static_assert(offsetof(ACTOR_DATA_VERGIL, magicPoints) == 0x3EB8);
static_assert(offsetof(ACTOR_DATA_VERGIL, maxMagicPoints) == 0x3EBC);
static_assert(offsetof(ACTOR_DATA_VERGIL, cameraDirection) == 0x3ED8);
static_assert(offsetof(ACTOR_DATA_VERGIL, move) == 0x3FA4);
static_assert(offsetof(ACTOR_DATA_VERGIL, lastMove) == 0x3FA5);
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
static_assert(offsetof(ACTOR_DATA_VERGIL, weaponIndex) == 0x6484);
static_assert(offsetof(ACTOR_DATA_VERGIL, weaponMap) == 0x6498);
static_assert(offsetof(ACTOR_DATA_VERGIL, weaponData) == 0x64A0);
static_assert(offsetof(ACTOR_DATA_VERGIL, weaponFlags) == 0x64C8);
static_assert(offsetof(ACTOR_DATA_VERGIL, weaponTimer) == 0x64F4);
static_assert(offsetof(ACTOR_DATA_VERGIL, weaponTimeout) == 0x6508);
static_assert(offsetof(ACTOR_DATA_VERGIL, styleRank) == 0x6510);
static_assert(offsetof(ACTOR_DATA_VERGIL, styleMeter) == 0x6514);
static_assert(offsetof(ACTOR_DATA_VERGIL, inputData) == 0x6674);
static_assert(offsetof(ACTOR_DATA_VERGIL, collisionIndex) == 0x7254);
static_assert(offsetof(ACTOR_DATA_VERGIL, interactionData) == 0x7460);
static_assert(offsetof(ACTOR_DATA_VERGIL, buttons) == 0x74E0);
static_assert(offsetof(ACTOR_DATA_VERGIL, rightStick) == 0x74F8);
static_assert(offsetof(ACTOR_DATA_VERGIL, leftStick) == 0x7508);
static_assert(offsetof(ACTOR_DATA_VERGIL, actorCameraDirection) == 0x750C);
static_assert(offsetof(ACTOR_DATA_VERGIL, leftStickDirection) == 0x751C);
static_assert(offsetof(ACTOR_DATA_VERGIL, modelMetadata) == 0xB640);
static_assert(offsetof(ACTOR_DATA_VERGIL, characterModel) == 0xB8C0);
static_assert(offsetof(ACTOR_DATA_VERGIL, parentBaseAddr) == 0xB8C8);
static_assert(offsetof(ACTOR_DATA_VERGIL, childBaseAddr) == 0xB8D0);
static_assert(offsetof(ACTOR_DATA_VERGIL, gamepad) == 0xB8F0);
static_assert(offsetof(ACTOR_DATA_VERGIL, buttonMask) == 0xB8F1);
static_assert(offsetof(ACTOR_DATA_VERGIL, copyPosition) == 0xB8F3);
static_assert(offsetof(ACTOR_DATA_VERGIL, newStyle) == 0xB8F4);
static_assert(offsetof(ACTOR_DATA_VERGIL, styleMap) == 0xB8F8);
static_assert(offsetof(ACTOR_DATA_VERGIL, newWeaponData) == 0xB908);
static_assert(offsetof(ACTOR_DATA_VERGIL, meleeWeaponMap) == 0xB988);
static_assert(offsetof(ACTOR_DATA_VERGIL, meleeWeaponCount) == 0xB98D);
static_assert(offsetof(ACTOR_DATA_VERGIL, meleeWeaponIndex) == 0xB98E);
static_assert(offsetof(ACTOR_DATA_VERGIL, rangedWeaponMap) == 0xB990);
static_assert(offsetof(ACTOR_DATA_VERGIL, rangedWeaponCount) == 0xB995);
static_assert(offsetof(ACTOR_DATA_VERGIL, rangedWeaponIndex) == 0xB996);
