#include "../Core/Core.h"

#include "Vars.h"

#pragma warning(push)
#pragma warning(disable: 4302)
#pragma warning(disable: 4311)

static_assert(offsetof(ACTOR_DATA, characterLogic) == 0x78);
static_assert(offsetof(ACTOR_DATA, position) == 0x80);
static_assert(offsetof(ACTOR_DATA, direction) == 0xC0);
static_assert(offsetof(ACTOR_DATA, index) == 0x118);
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
static_assert(offsetof(ACTOR_DATA, costumeLogic) == 0x3E9E);
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
static_assert(offsetof(ACTOR_DATA, controlClone) == 0x6454);
static_assert(offsetof(ACTOR_DATA, cloneBaseAddr) == 0x6478);
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
static_assert(offsetof(ACTOR_DATA, noActorCollision) == 0xB8D0);
static_assert(offsetof(ACTOR_DATA, noEnemyCollision) == 0xB8D1);
static_assert(offsetof(ACTOR_DATA, noEnemyAttackCollision) == 0xB8D2);
static_assert(offsetof(ACTOR_DATA, parentBaseAddr) == 0xB8D8);
static_assert(offsetof(ACTOR_DATA, childBaseAddr) == 0xB8E0);

#pragma warning(pop)
