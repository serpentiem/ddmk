#pragma once
#include "../Core/Core.h"

#include "Vars.h"

#define _Merge(a, b) a##b
#define Merge(a, b) _Merge(a, b)

#define _(size) struct { byte8 Merge(padding, __LINE__)[size]; }

#pragma pack(push, 1)

struct ACTOR_DATA
{
	_(8);
	bool init; // 0x8
	_(111);
	uint32 character; // 0x78
	_(4);
	vec4 position; // 0x80
	_(4);
	float32 pull; // 0x94
	_(12);
	float32 pullMultiplier; // 0xA4
	_(24);
	uint16 direction; // 0xC0
	_(86);
	uint8 id; // 0x118
	_(3);
	bool isClone; // 0x11C
	_(3);
	uint32 visible; // 0x120
	_(156);
	float32 var_1C0; // 0x1C0
	float32 var_1C4; // 0x1C4
	_(56);
	MODEL_DATA modelData[3]; // 0x200
	_(8224);
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
	uint32 var_3E00[4]; // 0x3E00
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
	uint32 modelMap[3]; // 0x3E74
	uint8 modelState; // 0x3E80
	_(3);
	bool lockOn; // 0x3E84
	_(3);
	uint32 activeModelIndexMirror; // 0x3E88
	uint32 activeDevilModel; // 0x3E8C
	uint32 airRaid; // 0x3E90
	uint32 devilState; // 0x3E94
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
	_(24);
	uint16 cameraDirection; // 0x3ED8
	_(63);
	bool moveOnly; // 0x3F19
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
	_(424);
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
	uint16 rightStickPosition; // 0x74F8
	uint16 rightStickRadius; // 0x74FA
	_(12);
	uint16 leftStickPosition; // 0x7508
	uint16 leftStickRadius; // 0x750A
	uint16 actorCameraDirection; // 0x750C
	_(14);
	uint32 leftStickDirection[2]; // 0x751C
	_(17308);
	uint8 newCharacterModel; // 0xB8C0
	_(7);
	byte8 * newParentBaseAddr; // 0xB8C8
	byte8 * newChildBaseAddr[4]; // 0xB8D0
	uint8 newGamepad; // 0xB8F0
	byte16 newButtonMask; // 0xB8F1
	bool newEnableRightStick; // 0xB8F3
	bool newEnableLeftStick; // 0xB8F4
	_(3);
	uint8 newMeleeWeapon[5]; // 0xB8F8
	_(3);
	byte8 * newMeleeWeaponData[5]; // 0xB900
	uint8 newMeleeWeaponCount; // 0xB928
	uint8 newMeleeWeaponIndex; // 0xB929
	_(2);
	uint8 newRangedWeapon[5]; // 0xB92C
	_(7);
	byte8 * newRangedWeaponData[5]; // 0xB938
	uint8 newRangedWeaponCount; // 0xB960
	uint8 newRangedWeaponIndex; // 0xB961
	_(2);
	bool newSect[8]; // 0xB964
	uint8 newBufferedActionPolicy; // 0xB96C

	operator byte8 *()
	{
		return reinterpret_cast<byte8 *>(this);
	}
};

struct ACTOR_DATA_DANTE
{
	_(8);
	bool init; // 0x8
	_(111);
	uint32 character; // 0x78
	_(4);
	vec4 position; // 0x80
	_(4);
	float32 pull; // 0x94
	_(12);
	float32 pullMultiplier; // 0xA4
	_(24);
	uint16 direction; // 0xC0
	_(86);
	uint8 id; // 0x118
	_(3);
	bool isClone; // 0x11C
	_(3);
	uint32 visible; // 0x120
	_(156);
	float32 var_1C0; // 0x1C0
	float32 var_1C4; // 0x1C4
	_(56);
	MODEL_DATA modelData[3]; // 0x200
	_(8224);
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
	uint32 var_3E00[4]; // 0x3E00
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
	uint32 modelMap[3]; // 0x3E74
	uint8 modelState; // 0x3E80
	_(3);
	bool lockOn; // 0x3E84
	_(3);
	uint32 activeModelIndexMirror; // 0x3E88
	uint32 activeDevilModel; // 0x3E8C
	uint32 airRaid; // 0x3E90
	uint32 devilState; // 0x3E94
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
	_(24);
	uint16 cameraDirection; // 0x3ED8
	_(63);
	bool moveOnly; // 0x3F19
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
	uint8 meleeWeapon[2]; // 0x6498
	uint8 rangedWeapon[3]; // 0x649A
	_(3);
	byte8 * meleeWeaponData[2]; // 0x64A0
	byte8 * rangedWeaponData[3]; // 0x64B0
	uint32 meleeWeaponStatus[2]; // 0x64C8
	uint32 rangedWeaponStatus[3]; // 0x64D0
	uint32 meleeWeaponLevel[2]; // 0x64DC
	uint32 rangedWeaponLevel[3]; // 0x64E4
	uint8 activeMeleeWeapon; // 0x64F0
	uint8 activeRangedWeapon; // 0x64F1
	_(2);
	float32 meleeWeaponTimer[2]; // 0x64F4
	float32 rangedWeaponTimer[3]; // 0x64FC
	float32 meleeWeaponSwitchTimeout; // 0x6508
	float32 rangedWeaponSwitchTimeout; // 0x650C
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
	uint16 rightStickPosition; // 0x74F8
	uint16 rightStickRadius; // 0x74FA
	_(12);
	uint16 leftStickPosition; // 0x7508
	uint16 leftStickRadius; // 0x750A
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
	uint8 newCharacterModel; // 0xB8C0
	_(7);
	byte8 * newParentBaseAddr; // 0xB8C8
	byte8 * newChildBaseAddr[4]; // 0xB8D0
	uint8 newGamepad; // 0xB8F0
	byte16 newButtonMask; // 0xB8F1
	bool newEnableRightStick; // 0xB8F3
	bool newEnableLeftStick; // 0xB8F4
	_(3);
	uint8 newMeleeWeapon[5]; // 0xB8F8
	_(3);
	byte8 * newMeleeWeaponData[5]; // 0xB900
	uint8 newMeleeWeaponCount; // 0xB928
	uint8 newMeleeWeaponIndex; // 0xB929
	_(2);
	uint8 newRangedWeapon[5]; // 0xB92C
	_(7);
	byte8 * newRangedWeaponData[5]; // 0xB938
	uint8 newRangedWeaponCount; // 0xB960
	uint8 newRangedWeaponIndex; // 0xB961
	_(2);
	bool newSect[8]; // 0xB964
	uint8 newBufferedActionPolicy; // 0xB96C

	operator byte8 *()
	{
		return reinterpret_cast<byte8 *>(this);
	}
};

struct ACTOR_DATA_BOB
{
	_(8);
	bool init; // 0x8
	_(111);
	uint32 character; // 0x78
	_(4);
	vec4 position; // 0x80
	_(4);
	float32 pull; // 0x94
	_(12);
	float32 pullMultiplier; // 0xA4
	_(24);
	uint16 direction; // 0xC0
	_(86);
	uint8 id; // 0x118
	_(3);
	bool isClone; // 0x11C
	_(3);
	uint32 visible; // 0x120
	_(156);
	float32 var_1C0; // 0x1C0
	float32 var_1C4; // 0x1C4
	_(56);
	MODEL_DATA modelData[3]; // 0x200
	_(8224);
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
	uint32 var_3E00[4]; // 0x3E00
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
	uint32 modelMap[3]; // 0x3E74
	uint8 modelState; // 0x3E80
	_(3);
	bool lockOn; // 0x3E84
	_(3);
	uint32 activeModelIndexMirror; // 0x3E88
	uint32 activeDevilModel; // 0x3E8C
	uint32 airRaid; // 0x3E90
	uint32 devilState; // 0x3E94
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
	_(24);
	uint16 cameraDirection; // 0x3ED8
	_(63);
	bool moveOnly; // 0x3F19
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
	_(424);
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
	uint16 rightStickPosition; // 0x74F8
	uint16 rightStickRadius; // 0x74FA
	_(12);
	uint16 leftStickPosition; // 0x7508
	uint16 leftStickRadius; // 0x750A
	uint16 actorCameraDirection; // 0x750C
	_(14);
	uint32 leftStickDirection[2]; // 0x751C
	_(17308);
	uint8 newCharacterModel; // 0xB8C0
	_(7);
	byte8 * newParentBaseAddr; // 0xB8C8
	byte8 * newChildBaseAddr[4]; // 0xB8D0
	uint8 newGamepad; // 0xB8F0
	byte16 newButtonMask; // 0xB8F1
	bool newEnableRightStick; // 0xB8F3
	bool newEnableLeftStick; // 0xB8F4
	_(3);
	uint8 newMeleeWeapon[5]; // 0xB8F8
	_(3);
	byte8 * newMeleeWeaponData[5]; // 0xB900
	uint8 newMeleeWeaponCount; // 0xB928
	uint8 newMeleeWeaponIndex; // 0xB929
	_(2);
	uint8 newRangedWeapon[5]; // 0xB92C
	_(7);
	byte8 * newRangedWeaponData[5]; // 0xB938
	uint8 newRangedWeaponCount; // 0xB960
	uint8 newRangedWeaponIndex; // 0xB961
	_(2);
	bool newSect[8]; // 0xB964
	uint8 newBufferedActionPolicy; // 0xB96C

	operator byte8 *()
	{
		return reinterpret_cast<byte8 *>(this);
	}
};

struct ACTOR_DATA_LADY
{
	_(8);
	bool init; // 0x8
	_(111);
	uint32 character; // 0x78
	_(4);
	vec4 position; // 0x80
	_(4);
	float32 pull; // 0x94
	_(12);
	float32 pullMultiplier; // 0xA4
	_(24);
	uint16 direction; // 0xC0
	_(86);
	uint8 id; // 0x118
	_(3);
	bool isClone; // 0x11C
	_(3);
	uint32 visible; // 0x120
	_(156);
	float32 var_1C0; // 0x1C0
	float32 var_1C4; // 0x1C4
	_(56);
	MODEL_DATA modelData[3]; // 0x200
	_(8224);
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
	uint32 var_3E00[4]; // 0x3E00
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
	uint32 modelMap[3]; // 0x3E74
	uint8 modelState; // 0x3E80
	_(3);
	bool lockOn; // 0x3E84
	_(3);
	uint32 activeModelIndexMirror; // 0x3E88
	uint32 activeDevilModel; // 0x3E8C
	uint32 airRaid; // 0x3E90
	uint32 devilState; // 0x3E94
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
	_(24);
	uint16 cameraDirection; // 0x3ED8
	_(63);
	bool moveOnly; // 0x3F19
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
	_(424);
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
	uint16 rightStickPosition; // 0x74F8
	uint16 rightStickRadius; // 0x74FA
	_(12);
	uint16 leftStickPosition; // 0x7508
	uint16 leftStickRadius; // 0x750A
	uint16 actorCameraDirection; // 0x750C
	_(14);
	uint32 leftStickDirection[2]; // 0x751C
	_(17308);
	uint8 newCharacterModel; // 0xB8C0
	_(7);
	byte8 * newParentBaseAddr; // 0xB8C8
	byte8 * newChildBaseAddr[4]; // 0xB8D0
	uint8 newGamepad; // 0xB8F0
	byte16 newButtonMask; // 0xB8F1
	bool newEnableRightStick; // 0xB8F3
	bool newEnableLeftStick; // 0xB8F4
	_(3);
	uint8 newMeleeWeapon[5]; // 0xB8F8
	_(3);
	byte8 * newMeleeWeaponData[5]; // 0xB900
	uint8 newMeleeWeaponCount; // 0xB928
	uint8 newMeleeWeaponIndex; // 0xB929
	_(2);
	uint8 newRangedWeapon[5]; // 0xB92C
	_(7);
	byte8 * newRangedWeaponData[5]; // 0xB938
	uint8 newRangedWeaponCount; // 0xB960
	uint8 newRangedWeaponIndex; // 0xB961
	_(2);
	bool newSect[8]; // 0xB964
	uint8 newBufferedActionPolicy; // 0xB96C

	operator byte8 *()
	{
		return reinterpret_cast<byte8 *>(this);
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
	_(4);
	float32 pull; // 0x94
	_(12);
	float32 pullMultiplier; // 0xA4
	_(24);
	uint16 direction; // 0xC0
	_(86);
	uint8 id; // 0x118
	_(3);
	bool isClone; // 0x11C
	_(3);
	uint32 visible; // 0x120
	_(156);
	float32 var_1C0; // 0x1C0
	float32 var_1C4; // 0x1C4
	_(56);
	MODEL_DATA modelData[3]; // 0x200
	_(8224);
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
	uint32 var_3E00[4]; // 0x3E00
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
	uint32 modelMap[3]; // 0x3E74
	uint8 modelState; // 0x3E80
	_(3);
	bool lockOn; // 0x3E84
	_(3);
	uint32 activeModelIndexMirror; // 0x3E88
	uint32 activeDevilModel; // 0x3E8C
	uint32 airRaid; // 0x3E90
	uint32 devilState; // 0x3E94
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
	_(24);
	uint16 cameraDirection; // 0x3ED8
	_(63);
	bool moveOnly; // 0x3F19
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
	_(284);
	uint32 activeMeleeWeaponIndex; // 0x6484
	uint32 queuedMeleeWeaponIndex; // 0x6488
	_(12);
	uint8 meleeWeapon[5]; // 0x6498
	_(3);
	byte8 * meleeWeaponData[5]; // 0x64A0
	uint32 meleeWeaponStatus[5]; // 0x64C8
	uint32 meleeWeaponLevel[5]; // 0x64DC
	_(4);
	float32 meleeWeaponTimer[5]; // 0x64F4
	float32 meleeWeaponSwitchForwardTimeout; // 0x6508
	float32 meleeWeaponSwitchBackTimeout; // 0x650C
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
	uint16 rightStickPosition; // 0x74F8
	uint16 rightStickRadius; // 0x74FA
	_(12);
	uint16 leftStickPosition; // 0x7508
	uint16 leftStickRadius; // 0x750A
	uint16 actorCameraDirection; // 0x750C
	_(14);
	uint32 leftStickDirection[2]; // 0x751C
	_(16668);
	MODEL_METADATA modelMetadata[6]; // 0xB640
	_(160);
	uint8 newCharacterModel; // 0xB8C0
	_(7);
	byte8 * newParentBaseAddr; // 0xB8C8
	byte8 * newChildBaseAddr[4]; // 0xB8D0
	uint8 newGamepad; // 0xB8F0
	byte16 newButtonMask; // 0xB8F1
	bool newEnableRightStick; // 0xB8F3
	bool newEnableLeftStick; // 0xB8F4
	_(3);
	uint8 newMeleeWeapon[5]; // 0xB8F8
	_(3);
	byte8 * newMeleeWeaponData[5]; // 0xB900
	uint8 newMeleeWeaponCount; // 0xB928
	uint8 newMeleeWeaponIndex; // 0xB929
	_(2);
	uint8 newRangedWeapon[5]; // 0xB92C
	_(7);
	byte8 * newRangedWeaponData[5]; // 0xB938
	uint8 newRangedWeaponCount; // 0xB960
	uint8 newRangedWeaponIndex; // 0xB961
	_(2);
	bool newSect[8]; // 0xB964
	uint8 newBufferedActionPolicy; // 0xB96C

	operator byte8 *()
	{
		return reinterpret_cast<byte8 *>(this);
	}
};

#pragma pack(pop)

#undef _
#undef Merge
#undef _Merge
