// #region

"use strict";

let fs = require("fs");
let process = require("process");
let vm = require("vm");

vm.runInThisContext
(
	fs.readFileSync("../core.js"  , "utf8") +
	fs.readFileSync("dmc3_core.js", "utf8")
);

ClearAll();

// #endregion



let location = "../Mary/Vars.ixx";

let file = fs.readFileSync(location, "utf8");



// #region Feed

function FeedStruct
(
	name,
	items,
	size    = 0,
	tagName = name
)
{
	ClearAll();



	let c_until = "";
	let c_after = "";
	let c_new   = "";

	let lines = GetLines(file);

	let startName = new RegExp("\\/\\/ \\$" + tagName + "Start$");
	let endName   = new RegExp("\\/\\/ \\$" + tagName + "End$"  );

	console.log(startName);
	console.log(endName);

	if
	(
		!Tag_Init
		(
			lines,
			startName,
			endName
		)
	)
	{
		console.log("Tag_Init failed.");

		process.exit(1);

		return;
	}



	Tag_CopyUntil(lines);

	c_until = c;

	ClearAll();



	Tag_CopyAfter(lines);

	c_after = c;

	ClearAll();



	CreateStruct
	(
		name,
		items,
		size,
		0,
		StructFlags_Export
	);

	CreateStructAsserts
	(
		name,
		items,
		size,
		0,
		StructFlags_NoTypeAssert
	);

	MergeAsserts();
	FeedAsserts();

	CleanStream();

	c_new = c;

	ClearAll();



	file = c_until + c_new + c_after;
}

function FeedEnum
(
	name,
	items,
	tagName = name
)
{
	ClearAll();



	let c_until = "";
	let c_after = "";
	let c_new   = "";

	let lines = GetLines(file);

	let startName = new RegExp("\\/\\/ \\$" + tagName + "Start$");
	let endName   = new RegExp("\\/\\/ \\$" + tagName + "End$"  );

	console.log(startName);
	console.log(endName);

	if
	(
		!Tag_Init
		(
			lines,
			startName,
			endName
		)
	)
	{
		console.log("Tag_Init failed.");

		process.exit(1);

		return;
	}



	Tag_CopyUntil(lines);

	c_until = c;

	ClearAll();



	Tag_CopyAfter(lines);

	c_after = c;

	ClearAll();



	c += "export namespaceStart(" + name + ");" + NEW_LINE;

	CreateEnum
	(
		"",
		items,
		"",
		EnumFlags_UpperCase
	);

	c += "namespaceEnd();" + NEW_LINE;
	c += NEW_LINE;

	CleanStream();

	c_new = c;

	ClearAll();



	file = c_until + c_new + c_after;
}

// #endregion



// #region MissionData
{

let items =
[
	[ "redOrbs"       , "uint32", [], 0x38 ],
	[ "itemCounts[62]", "uint8" , [], 0x3C ],
	[ "buyCounts[8]"  , "uint8" , [], 0x7A ],
	[ "frameCount"    , "uint32", [], 0xA8 ],
	[ "damage"        , "uint32", [], 0xAC ],
	[ "orbsCollected" , "uint32", [], 0xB0 ],
	[ "itemsUsed"     , "uint32", [], 0xB4 ],
	[ "killCount"     , "uint32", [], 0xB8 ],
];

FeedStruct
(
	"MissionData",
	items,
	192
);

}
// #endregion

// #region SessionData
{

let items =
[
	[ "mission"              , "uint32", [], 0     ],
	[ "mode"                 , "uint32", [], 0xC   ],
	[ "oneHitKill"           , "bool"  , [], 0x10  ],
	[ "enableTutorial"       , "bool"  , [], 0x12  ],
	[ "useGoldOrb"           , "bool"  , [], 0x13  ],
	[ "character"            , "uint8" , [], 0x14  ],
	[ "bloodyPalace"         , "bool"  , [], 0x1C  ],
	[ "redOrbs"              , "uint32", [], 0x2C  ],
	[ "itemCounts[20]"       , "uint8" , [], 0x30  ],
	[ "unlocks[14]"          , "bool"  , [], 0x46  ],
	[ "weapons[8]"           , "uint8" , [], 0x84  ],
	[ "rangedWeaponLevels[5]", "uint32", [], 0xA0  ],
	[ "meleeWeaponIndex"     , "uint32", [], 0xC8  ],
	[ "rangedWeaponIndex"    , "uint32", [], 0xCC  ],
	[ "costume"              , "uint8" , [], 0xD0  ],
	[ "unlockDevilTrigger"   , "bool"  , [], 0xD1  ],
	[ "hitPoints"            , "float" , [], 0xD4  ],
	[ "magicPoints"          , "float" , [], 0xD8  ],
	[ "style"                , "uint32", [], 0xDC  ],
	[ "styleLevel[6]"        , "uint32", [], 0xE0  ],
	[ "styleExperience[6]"   , "float" , [], 0xF8  ],
	[ "expertise[8]"         , "byte32", [], 0x110 ],
];

FeedStruct
(
	"SessionData",
	items
);

}
// #endregion

// #region EventData
{

let items =
[
	[ "room"      , "uint32", [], 0x18 ],
	[ "position"  , "uint32", [], 0x1C ],
	[ "event"     , "uint32", [], 0x20 ],
	[ "subevent"  , "uint32", [], 0x24 ],
	[ "screen"    , "uint32", [], 0x28 ],
	[ "nextScreen", "uint32", [], 0x2C ],
];

FeedStruct
(
	"EventData",
	items
);

}
// #endregion

// #region NextEventData
{

let items =
[
	[ "room"      , "uint16", [], 0x164 ],
	[ "position"  , "uint16", [], 0x166 ],
];

FeedStruct
(
	"NextEventData",
	items
);

}
// #endregion

// #region ActorData
{

const SIZE_BASE          = 200;
const SIZE_PLAYER_BASE   = 0x7540;
const SIZE_PLAYER_DANTE  = 0xB8C0;
const SIZE_PLAYER_BOB    = 0xB680;
const SIZE_PLAYER_LADY   = 0x8280;
const SIZE_PLAYER_VERGIL = 0xB8C0;

let itemsBase =
[
	[ "status"         , "uint8"  , [], 8    ],
	[ "speed"          , "float"  , [], 0x14 ],
	[ "speedMultiplier", "float"  , [], 0x18 ],
	[ "lastBaseAddr"   , "byte8 *", [], 0x28 ],
	[ "nextBaseAddr"   , "byte8 *", [], 0x30 ],
	[ "baseAddr"       , "byte8 *", [], 0x48 ],
	[ "visible"        , "bool"   , [], 0x5D ],
	[ ""               , "union"  ,
		[
			[ "character", "uint32" ],
			[ "enemy"    , "uint32" ],
		],
		0x78
	],
	[ "position"              , "vec4"  , [], 0x80 ],
	[ "verticalPull"          , "float" , [], 0x94 ],
	[ "verticalPullMultiplier", "float" , [], 0xA4 ],
	[ "rotation"              , "uint16", [], 0xC0 ],
];

let itemsPlayerBase =
[
	[ "id"                             , "uint8"            , [], 0x118  ],
	[ "isClone"                        , "bool32"           , [], 0x11C  ],
	[ "visibility"                     , "uint32"           , [], 0x120  ],
	[ "horizontalPull"                 , "float"            , [], 0x1C0  ],
	[ "horizontalPullMultiplier"       , "float"            , [], 0x1C4  ],
	[ "modelData[3]"                   , "ModelData"        , [], 0x200  ],
	[ "modelPhysicsMetadataPool[4][24]", "PhysicsMetadata *", [], 0x1880 ],
	[ "modelAllocationDataCount"       , "uint32"           , [], 0x1B80 ],
	[ "modelAllocationData[209]"       , "Size_32"          , [], 0x1B88 ],
	[ "motionSpeed"                    , "float"            , [], 0x3894 ],
	[ "motionSpeedMultiplier"          , "float"            , [], 0x3898 ],
	[ "motionArchives[34]"             , "byte8 *"          , [], 0x38A0 ],
	[ "motionData[2]"                  , "MotionData"       , [], 0x39B0 ],
	[ "motionDataMirror[3]"            , "MotionData"       , [], 0x39B4 ],
	[ ""                               , "uint32"           , [], 0x39BC ],
	[ "[16]"                           , "uint8"            , [], 0x39C0 ],
	[ "nextActionRequestPolicy[16]"    , "uint32"           , [], 0x39D0 ],
	[ "[8]"                            , "uint8"            , [], 0x3A10 ],
	[ "shadow"                         , "uint32"           , [], 0x3A18 ],
	[ "lastShadow"                     , "uint32"           , [], 0x3A1C ],
	[ "color"                          , "byte32"           , [], 0x3A28 ],
	[ "recoveryData[3]"                , "RecoveryData"     , [], 0x3B00 ],
	[ "[2]"                            , "byte8"            , [], 0x3C50 ],
	[ "actionData[6]"                  , "byte8 *"          , [], 0x3DD0 ],
	[ "eventData[2]"                   , "ActorEventData"   , [], 0x3E00 ],
	[ "[32]"                           , "uint8"            , [], 0x3E10 ],
	[ "motionTimer"                    , "float"            , [], 0x3E34 ],
	[ "idleTimer"                      , "float"            , [], 0x3E38 ],
	[ "permissions"                    , "byte32"           , [], 0x3E60 ],
	[ "state"                          , "byte32"           , [], 0x3E64 ],
	[ "lastState"                      , "byte32"           , [], 0x3E68 ],
	[ "activeModelIndex"               , "uint32"           , [], 0x3E6C ],
	[ "queuedModelIndex"               , "uint32"           , [], 0x3E70 ],
	[ "devilModels[3]"                 , "uint32"           , [], 0x3E74 ],
	[ "modelState"                     , "uint8"            , [], 0x3E80 ],
	[ "lockOn"                         , "bool32"           , [], 0x3E84 ],
	[ "activeModelIndexMirror"         , "uint32"           , [], 0x3E88 ],
	[ "activeDevil"                    , "uint32"           , [], 0x3E8C ],
	[ "airRaid"                        , "uint32"           , [], 0x3E90 ],
	[ "mode"                           , "uint32"           , [], 0x3E94 ],
	[ "dead"                           , "bool"             , [], 0x3E99 ],
	[ "devil"                          , "bool"             , [], 0x3E9B ],
	[ "costume"                        , "uint8"            , [], 0x3E9E ],
	[ ""                               , "union",
		[
			[ "sparda"    , "bool" ],
			[ "neroAngelo", "bool" ],
		],
		0x3E9F
	],
	[ "useHolyWater"                , "bool"         , [], 0x3EA4 ],
	[ "magicPoints"                 , "float"        , [], 0x3EB8 ],
	[ "maxMagicPoints"              , "float"        , [], 0x3EBC ],
	[ ""                            , "float"        , [], 0x3EC4 ],
	[ ""                            , "float"        , [], 0x3EC8 ],
	[ ""                            , "uint16"       , [], 0x3ED2 ],
	[ "cameraDirection"             , "uint16"       , [], 0x3ED8 ],
	[ ""                            , "float"        , [], 0x3EDC ],
	[ "airHikeCount"                , "uint8"        , [], 0x3F11 ],
	[ "kickJumpCount"               , "uint8"        , [], 0x3F12 ],
	[ "wallHikeCount"               , "uint8"        , [], 0x3F13 ],
	[ "enableAirRaid"               , "bool"         , [], 0x3F14 ],
	[ ""                            , "bool"         , [], 0x3F19 ],
	[ "action"                      , "uint8"        , [], 0x3FA4 ],
	[ "lastAction"                  , "uint8"        , [], 0x3FA5 ],
	[ "bufferedAction"              , "uint8"        , [], 0x3FA8 ],
	[ "chainCount"                  , "uint8"        , [], 0x3FAC ],
	[ "expertise[16]"               , "byte32"       , [], 0x3FEC ],
	[ "maxHitPoints"                , "float"        , [], 0x40EC ],
	[ "hitPoints"                   , "float"        , [], 0x411C ],
	[ "lockOnData"                  , "LockOnData"   , [], 0x41C0 ],
	// [ "targetPosition"              , "vec4"         , [], 0x6300 ],
	// [ "targetBaseAddrPlus0x60"      , "byte8 *"      , [], 0x6328 ],
	[ "style"                       , "uint32"       , [], 0x6338 ],
	[ "wallHikeDirection"           , "uint32"       , [], 0x633C ],
	[ ""                            , "uint32"       , [], 0x6340 ],
	[ "styleLevel"                  , "uint32"       , [], 0x6358 ],
	[ "dashCount"                   , "uint8"        , [], 0x635C ],
	[ "skyStarCount"                , "uint8"        , [], 0x635D ],
	[ "airTrickCount"               , "uint8"        , [], 0x635E ],
	[ "trickUpCount"                , "uint8"        , [], 0x635F ],
	[ "trickDownCount"              , "uint8"        , [], 0x6360 ],
	[ "quicksilver"                 , "bool"         , [], 0x6361 ],
	[ "doppelganger"                , "bool"         , [], 0x6362 ],
	[ "styleExperience"             , "float"        , [], 0x6364 ],
	[ "royalguardBlockType"         , "uint32"       , [], 0x6370 ],
	[ "royalguardReleaseLevel"      , "uint8"        , [], 0x6380 ],
	[ "royalguardReleaseEffectIndex", "uint8"        , [], 0x6381 ],
	[ "royalguardReleaseDamage"     , "float"        , [], 0x6384 ],
	[ ""                            , "float"        , [], 0x6388 ],
	[ ""                            , "float"        , [], 0x638C ],
	[ ""                            , "uint32"       , [], 0x63D0 ],
	[ "quicksilverStage"            , "uint32"       , [], 0x63D4 ],
	[ "[40]"                        , "byte8"        , [], 0x6410 ],
	[ ""                            , "byte8 *"      , [], 0x6438 ],
	[ ""                            , "uint32"       , [], 0x6440 ],
	[ "cloneRate"                   , "uint32"       , [], 0x6450 ],
	[ "cloneStatus"                 , "uint32"       , [], 0x6454 ],
	[ "[32]"                        , "byte8"        , [], 0x6458 ],
	[ "cloneActorBaseAddr"          , "byte8 *"      , [], 0x6478 ],
	[ "cloneIsControlledByPlayer"   , "bool"         , [], 0x6480 ],
	[ "activeMeleeWeaponIndex"      , "uint32"       , [], 0x6484 ],
	[ "queuedMeleeWeaponIndex"      , "uint32"       , [], 0x6488 ],
	[ "activeWeapon"                , "uint8"        , [], 0x648D ],
	[ "meleeWeaponIndex"            , "uint32"       , [], 0x6490 ],
	[ "rangedWeaponIndex"           , "uint32"       , [], 0x6494 ],
	[ "weapons[5]"                  , "uint8"        , [], 0x6498 ],
	[ "weaponDataAddr[5]"           , "WeaponData *" , [], 0x64A0 ],
	[ "weaponStatus[5]"             , "uint32"       , [], 0x64C8 ],
	[ "weaponLevels[5]"             , "uint32"       , [], 0x64DC ],
	[ "activeMeleeWeapon"           , "uint8"        , [], 0x64F0 ],
	[ "activeRangedWeapon"          , "uint8"        , [], 0x64F1 ],
	[ "weaponTimers[5]"             , "float"        , [], 0x64F4 ],
	[ "meleeWeaponSwitchTimeout"    , "float"        , [], 0x6508 ],
	[ "rangedWeaponSwitchTimeout"   , "float"        , [], 0x650C ],
	[ "styleData"                   , "StyleData"    , [], 0x6510 ],
	[ ""                            , "float"        , [], 0x6670 ],
	[ "inputData[58]"               , "InputData"    , [], 0x6674 ],
	[ "bodyPartData[3][2]"          , "BodyPartData" , [], 0x6950 ],
	[ "collisionData"               , "CollisionData", [], 0x7250 ],
	[ "buttons[4]"                  , "byte16"       , [], 0x74E0 ],
	[ "rightStickPosition"          , "uint16"       , [], 0x74F8 ],
	[ "rightStickRadius"            , "uint16"       , [], 0x74FA ],
	[ "leftStickPosition"           , "uint16"       , [], 0x7508 ],
	[ "leftStickRadius"             , "uint16"       , [], 0x750A ],
	[ "actorCameraDirection"        , "uint16"       , [], 0x750C ],
	[ "leftStickDirection[2]"       , "uint32"       , [], 0x751C ],
];

let itemsPlayerDante =
[
	[ "submodelData[5]"                     , "ModelData"              , [], 0x7540 ],
	[ "submodelInit[5]"                     , "bool"                   , [], 0x9AC0 ],
	[ "modelShadowData[3]"                  , "ShadowData"             , [], 0x9AD0 ],
	[ "submodelShadowData[5]"               , "ShadowData"             , [], 0x9D10 ],
	[ "submodelPhysicsMetadataPool[39]"     , "PhysicsMetadata *"      , [], 0xA0D0 ],
	[ "submodelPhysicsData"                 , "PhysicsData"            , [], 0xA210 ],
	[ "devilModelPhysicsMetadataPool[2][36]", "PhysicsMetadata *"      , [], 0xA300 ],
	[ "devilSubmodelPhysicsData[4]"         , "PhysicsData"            , [], 0xA540 ],
	[ "devilSubmodelPhysicsLinkData[4][4]"  , "PhysicsLinkData"        , [], 0xAA00 ],
	[ "devilModelMetadata"                  , "DevilModelMetadataDante", [], 0xB600 ],
	[ "modelMetadata[6]"                    , "ModelMetadata"          , [], 0xB630 ],
	[ "artemisChargeValues[2]"              , "float"                  , [], 0xB868 ],
	[ "artemisStatus"                       , "uint8"                  , [], 0xB87E ],
	[ "artemisMultiLock"                    , "bool"                   , [], 0xB880 ],
	[ "artemisMultiLockCharged"             , "bool"                   , [], 0xB881 ],
];

let itemsPlayerBob = [];
let itemsPlayerLady = [];

let itemsPlayerVergil =
[
	[ "submodelData[5]"                , "ModelData"        , [], 0x7540 ],
	[ "submodelInit[5]"                , "bool"             , [], 0x9AC0 ],
	[ "modelShadowData[3]"             , "ShadowData"       , [], 0x9AF0 ],
	[ "submodelShadowData[5]"          , "ShadowData"       , [], 0x9D30 ],
	[ "submodelPhysicsMetadataPool[39]", "PhysicsMetadata *", [], 0xA0F0 ],
	[ "submodelPhysicsData"            , "PhysicsData"      , [], 0xA230 ],
	[ "modelMetadata[6]"               , "ModelMetadata"    , [], 0xB640 ],
];

let itemsPlayerNew =
[
	[ "newFirstVar"                            , "uint32"           , [], ],
	[ "_(12)"                                  , ""                 , [], ],
	[ "newModelData[6]"                        , "ModelData"        , [], ],
	[ "newModelPhysicsMetadataPool[7][24]"     , "PhysicsMetadata *", [], ],
	[ "newModelAllocationData[512]"            , "Size_32"          , [], ],
	[ "newRecoveryData[6]"                     , "RecoveryData"     , [], ],
	[ "newDevilModels[6]"                      , "uint32"           , [], ],
	[ "_(8)"                                   , ""                 , [], ],
	[ "newBodyPartData[7][2]"                  , "BodyPartData"     , [], ],
	[ "newSubmodelData[11]"                    , "ModelData"        , [], ],
	[ "newSubmodelInit[11]"                    , "bool"             , [], ],
	[ "_(5)"                                   , ""                 , [], ],
	[ "newModelShadowData[6]"                  , "ShadowData"       , [], ],
	[ "newSubmodelShadowData[11]"              , "ShadowData"       , [], ],
	[ "newDevilModelPhysicsMetadataPool[5][36]", "PhysicsMetadata *", [], ],
	[ "newDevilSubmodelPhysicsData[10]"        , "PhysicsData"      , [], ],
	[ "newDevilSubmodelPhysicsLinkData[10][4]" , "PhysicsLinkData"  , [], ],
	[ "newWeapons[10]"                         , "uint8"            , [], ],
	[ "_(6)"                                   , ""                 , [], ],
	[ "newWeaponDataAddr[10]"                  , "WeaponData *"     , [], ],
	[ "newWeaponStatus[10]"                    , "uint32"           , [], ],
	[ "_(8)"                                   , ""                 , [], ],
	[ "newWeaponLevels[10]"                    , "uint32"           , [], ],
	[ "_(8)"                                   , ""                 , [], ],
	[ "newWeaponTimers[10]"                    , "float"            , [], ],
	[ "newIsClone"                             , "bool32"           , [], ],
	[ "newPlayerIndex"                         , "uint8"            , [], ],
	[ "newCharacterIndex"                      , "uint8"            , [], ],
	[ "newEntityIndex"                         , "uint8"            , [], ],
	[ "newForceFiles"                          , "bool"             , [], ],
	[ "newForceFilesCharacter"                 , "uint8"            , [], ],
	[ "newForceFilesCostume"                   , "uint8"            , [], ],
	[ "newEnableVisibility"                    , "bool"             , [], ],
	[ "newGamepad"                             , "uint8"            , [], ],
	[ "newButtonMask"                          , "byte16"           , [], ],
	[ "newEnableRightStick"                    , "bool"             , [], ],
	[ "newEnableLeftStick"                     , "bool"             , [], ],
	[ "newQuickDrive"                          , "bool"             , [], ],
	[ "newEnableCollision"                     , "bool"             , [], ],
	[ "newActorLoopRun"                        , "bool"             , [], ],
	[ "newAirHikeCount"                        , "uint8"            , [], ],
	[ "newKickJumpCount"                       , "uint8"            , [], ],
	[ "newWallHikeCount"                       , "uint8"            , [], ],
	[ "newDashCount"                           , "uint8"            , [], ],
	[ "newSkyStarCount"                        , "uint8"            , [], ],
	[ "newAirTrickCount"                       , "uint8"            , [], ],
	[ "newTrickUpCount"                        , "uint8"            , [], ],
	[ "newTrickDownCount"                      , "uint8"            , [], ],
	[ "newAirStingerCount"                     , "uint8"            , [], ],
	[ "newAirRisingSunCount"                   , "uint8"            , [], ],
	[ "_(11)"                                  , ""                 , [], ],
	[ "newEffectIndices[12]"                   , "uint32"           , [], ],
	[ "newLastVar"                             , "uint32"           , [], ],
];

let itemsEnemyPride =
[
	[ "maxHitPoints", "float" , [], 0x2E2C ],
	[ "hitPoints"   , "float" , [], 0x2E5C ],
	[ "event"       , "uint32", [], 0x3A34 ],
	[ "state"       , "uint8" , [], 0x3A38 ],
];

let itemsEnemyLady =
[
	[ "collisionData", "CollisionData", [], 0x5460 ],
	[ "hitPoints"    , "float"        , [], 0x5758 ],
	[ "event"        , "uint32"       , [], 0x5988 ],
	[ "state"        , "uint8"        , [], 0x5994 ],
	[ "pistolBullets", "uint32"       , [], 0x59A0 ],
	[ "grenades"     , "uint32"       , [], 0x59B0 ],
	[ "smgBullets"   , "uint32"       , [], 0x59B8 ],
	[ "nextPosition" , "vec4"         , [], 0x59C0 ],
	[ "phase"        , "uint32"       , [], 0x5A1C ],
	[ "rotation2"    , "uint16"       , [], 0x5A20 ],
	[ "friendly"     , "bool"         , [], 0x5A2E ],
	[ "pistolRounds" , "uint32"       , [], 0x5A90 ],
];

let itemsEnemyVergil =
[
	[ "nextEventTimer", "float"        , [], 0x1D8  ],
	[ "collisionData" , "CollisionData", [], 0xE830 ],
	[ "hitPoints"     , "float"        , [], 0xEB28 ],
	[ "event"         , "uint32"       , [], 0xED74 ],
	[ ""              , "uint32"       , [], 0xED80 ],
	[ "state"         , "uint8"        , [], 0xED84 ],
	[ "variant"       , "uint32"       , [], 0xEF0C ],
	[ "toggleDevil"   , "bool"         , [], 0xEF19 ],
	[ "devil"         , "bool"         , [], 0xEF1B ],
];

let tagName = "ActorData";



ClearAll();



let c_until = "";
let c_after = "";
let c_new   = "";

let lines = GetLines(file);

let startName = new RegExp("\\/\\/ \\$" + tagName + "Start$");
let endName   = new RegExp("\\/\\/ \\$" + tagName + "End$"  );

console.log(startName);
console.log(endName);

if
(
	!Tag_Init
	(
		lines,
		startName,
		endName
	)
)
{
	console.log("Tag_Init failed.");

	process.exit(1);

	return;
}



Tag_CopyUntil(lines);

c_until = c;

ClearAll();



Tag_CopyAfter(lines);

c_after = c;

ClearAll();



// Base
{

CreateStruct
(
	"ActorDataBase",
	itemsBase,
	SIZE_BASE,
	0,
	StructFlags_Export
);

ClearAsserts();

CreateStructAsserts
(
	"ActorDataBase",
	itemsBase,
	SIZE_BASE,
	0,
	StructFlags_NoTypeAssert
);

MergeAsserts();
FeedAsserts();

}



// Player Base
{

CreateStruct
(
	"PlayerActorDataBase : ActorDataBase",
	itemsPlayerBase,
	SIZE_PLAYER_BASE,
	SIZE_BASE,
	StructFlags_Export |
	StructFlags_NoScopeEnd
);

c += NEW_LINE;
c += Tabs() + "operator byte8 *()" + NEW_LINE;

ScopeStart();

c += Tabs() + "return reinterpret_cast<byte8 *>(this);" + NEW_LINE;

ScopeEnd();

ScopeEnd
(
	"}",
	ScopeFlags_Semicolon
);

c += NEW_LINE;

ClearAsserts();

CreateStructAsserts
(
	"PlayerActorDataBase",
	itemsPlayerBase,
	SIZE_PLAYER_BASE,
	SIZE_BASE,
	StructFlags_NoTypeAssert,
	StringFlags_Hex
);

MergeAsserts();
FeedAsserts();

}



c += NEW_LINE;



// Player Derived
{

let helpers =
[
	[ ""      , []                ],
	[ "Dante" , itemsPlayerDante  ],
	[ "Bob"   , itemsPlayerBob    ],
	[ "Lady"  , itemsPlayerLady   ],
	[ "Vergil", itemsPlayerVergil ],
];

for (let index = 0; index < helpers.length; index++)
{
	let helper = helpers[index];

	let name  = helper[0];
	let items = helper[1];

	let structName = "PlayerActorData" + name;

	CreateStruct
	(
		structName + " : PlayerActorDataBase",
		items,
		SIZE_PLAYER_DANTE,
		SIZE_PLAYER_BASE,
		StructFlags_Export |
		StructFlags_NoScopeEnd
	);

	CreateStructContent
	(
		itemsPlayerNew,
		SIZE_PLAYER_DANTE
	);

	ScopeEnd
	(
		"}",
		ScopeFlags_Semicolon
	);



	ClearAsserts();

	CreateStructAsserts
	(
		structName,
		items,
		SIZE_PLAYER_DANTE,
		SIZE_PLAYER_BASE,
		StructFlags_NoTypeAssert |
		StructFlags_NoSizeAssert,
		StringFlags_Hex
	);

	CreateStructAsserts
	(
		structName,
		itemsPlayerNew,
		0,
		SIZE_PLAYER_DANTE,
		StructFlags_NoTypeAssert |
		StructFlags_NoSizeAssert,
		StringFlags_Hex
	);

	MergeAsserts();
	FeedAsserts();
}

}



c += NEW_LINE;



// Enemy Derived
{

let helpers =
[
	[ ""      , []               ],
	[ "Pride" , itemsEnemyPride  ],
	[ "Lady"  , itemsEnemyLady   ],
	[ "Vergil", itemsEnemyVergil ],
];

for (let index = 0; index < helpers.length; index++)
{
	let helper = helpers[index];

	let name  = helper[0];
	let items = helper[1];


	let structName = "EnemyActorData" + name;

	CreateStruct
	(
		structName + " : ActorDataBase",
		items,
		0,
		SIZE_BASE,
		StructFlags_Export
	);



	ClearAsserts();

	CreateStructAsserts
	(
		structName,
		items,
		0,
		SIZE_BASE,
		StructFlags_NoTypeAssert |
		StructFlags_NoSizeAssert
	);

	MergeAsserts();
	FeedAsserts();
}

}



CleanStream();

c_new = c;

ClearAll();



file = c_until + c_new + c_after;



// Cheat Engine
{

ClearAll();



CE_CheatTableStart();

let actorCount = 4;

for (let actorIndex = 0; actorIndex < actorCount; actorIndex++)
{
	let posName = PositionName
	(
		(g_pointerSize * actorIndex),
		StringFlags_Hex |
		StringFlags_NoPrefix
	);

	CE_GroupStart
	(
		"__" + lz(actorIndex) + "__",
		true
	);

	CE_CreateCheatEntries
	(
		itemsBase,
		"Mary.Global::g_playerActorBaseAddrs",
		[ posName ]
	);

	CE_CreateCheatEntries
	(
		itemsPlayerBase,
		"Mary.Global::g_playerActorBaseAddrs",
		[ posName ],
		SIZE_BASE
	);

	CE_CreateCheatEntries
	(
		itemsPlayerNew,
		"Mary.Global::g_playerActorBaseAddrs",
		[ posName ],
		SIZE_PLAYER_DANTE
	);

	CE_GroupEnd();
}

CE_CheatTableEnd();

fs.writeFileSync("dmc3_actor_data.txt", c);

}

}
// #endregion

// #region CollisionDataMetadata
{

let items =
[
	[ "data[8]"          , "vec4"   , [], 0x30  ],
	[ "collisionDataAddr", "void *" , [], 0xD0  ],
	[ "data2[3]"         , "vec4"   , [], 0xE0  ],
	[ "files[2]"         , "byte8 *", [], 0x110 ],
	[ "mode"             , "uint32" , [], 0x120 ],
	[ "data3"            , "vec4"   , [], 0x130 ],
	[ "heightAdjustment" , "float"  , [], 0x140 ],
];

FeedStruct
(
	"CollisionDataMetadata",
	items
);

}
// #endregion

// #region CollisionData
{

let items =
[
	[ "group"       , "uint32"                 , [], 4     ],
	[ "metadataAddr", "CollisionDataMetadata *", [], 0x88  ],
	[ "baseAddr"    , "byte8 *"                , [], 0x130 ],
	[ "flags"       , "byte32"                 , [], 0x140 ],
	[ "data[8]"     , "vec4"                   , [], 0x210 ],
];

FeedStruct
(
	"CollisionData",
	items,
	656
);
/*
dmc3.exe+5C310 - 0F29 81 80020000 - movaps [rcx+00000280],xmm0
dmc3.exe+5C317 - C3               - ret
*/

}
// #endregion

// #region ActorEvent
{

let items =
[
	[ ""                          , "" ],
	[ ""                          , "" ],
	[ ""                          , "" ],
	[ ""                          , "" ],
	[ ""                          , "" ],
	[ "Jump"                      , "" ],
	[ ""                          , "" ],
	[ "Air Hike"                  , "" ],
	[ ""                          , "" ],
	[ ""                          , "" ],
	[ "Lock-On"                   , "" ],
	[ ""                          , "" ],
	[ ""                          , "" ],
	[ ""                          , "" ],
	[ ""                          , "" ],
	[ ""                          , "" ],
	[ ""                          , "" ],
	[ "Attack"                    , "" ],
	[ "Taunt"                     , "" ],
	[ "Royalguard Block"          , "" ],
	[ "Royalguard Block Connect"  , "" ],
	[ "Royalguard Release Blocked", "" ],
	[ "Trickster Dash"            , "" ],
	[ "Trickster Sky Star"        , "" ],
	[ "Trickster Air Trick"       , "" ],
	[ "Quicksilver Time Lag"      , "" ],
	[ ""                          , "" ],
	[ "Dark Slayer Air Trick"     , "" ],
	[ "Dark Slayer Trick Up"      , "" ],
	[ "Dark Slayer Trick Down"    , "" ],
	[ "Melee Attack Blocked"      , "" ],
	[ ""                          , "" ],
	[ ""                          , "" ],
	[ ""                          , "" ],
	[ ""                          , "" ],
	[ ""                          , "" ],
	[ ""                          , "" ],
	[ ""                          , "" ],
	[ ""                          , "" ],
	[ ""                          , "" ],
	[ "Nevan Air Raid"            , "" ],
	[ "Super Jump"                , "" ],
	[ ""                          , "" ],
	[ "Holy Water"                , "" ],
	[ ""                          , "" ],
	[ "Death"                     , "" ],
	[ "Count"                     , "" ],
];

FeedEnum
(
	"ACTOR_EVENT",
	items,
	"ActorEvent"
);

}
// #endregion

// #region CameraData
{

let items =
[
	[ "fov"           , "float"  , [], 0x20 ],
	[ "data[2]"       , "vec4"   , [], 0x70 ],
	[ "targetBaseAddr", "byte8 *", [], 0xB0 ],
	[ "height"        , "float"  , [], 0xD0 ],
	[ "tilt"          , "float"  , [], 0xD4 ],
	[ "distance"      , "float"  , [], 0xD8 ],
	[ "distanceLockOn", "float"  , [], 0xE0 ],
];

FeedStruct
(
	"CameraData",
	items,
	512
);

}
// #endregion

// #region EnemyVectorData
{

let items =
[
	[ "count"           , "uint32"               , [], 0x28   ],
	[ "metadata[50]"    , "EnemyVectorDataMetadata"  , [], 0x48   ],
	[ "lastMetadataAddr", "EnemyVectorDataMetadata *", [], 0x1048 ],
	[ "nextMetadataAddr", "EnemyVectorDataMetadata *", [], 0x1050 ],
];

FeedStruct
(
	"EnemyVectorData",
	items
);

}
// #endregion

// #region Enemy
{

let items =
[
	[ "Pride 1"               , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Pride 2"               , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Pride 3"               , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Pride 4"               , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Gluttony 1"            , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Gluttony 2"            , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Gluttony 3"            , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Gluttony 4"            , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Lust 1"                , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Lust 2"                , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Lust 3"                , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Lust 4"                , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Sloth 1"               , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Sloth 2"               , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Sloth 3"               , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Sloth 4"               , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Wrath 1"               , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Wrath 2"               , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Wrath 3"               , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Wrath 4"               , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Greed 1"               , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Greed 2"               , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Greed 3"               , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Greed 4"               , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Abyss"                 , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Envy"                  , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Hell Vanguard"         , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ ""                      , "0"                           ],
	[ "Arachne"               , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "The Fallen"            , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Dullahan"              , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Enigma"                , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Blood-Goyle"           , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ ""                      , "0"                           ],
	[ "Soul Eater"            , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Damned Chessmen Pawn"  , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Damned Chessmen Knight", "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Damned Chessmen Bishop", "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Damned Chessmen Rook"  , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Damned Chessmen Queen" , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Damned Chessmen King"  , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Gigapede"              , "HELPER_ENEMY_GIGAPEDE"       ],
	[ ""                      , "0"                           ],
	[ "Cerberus"              , "HELPER_ENEMY_CERBERUS"       ],
	[ "Agni & Rudra All"      , "HELPER_ENEMY_AGNI_RUDRA"     ],
	[ "Agni & Rudra"          , "HELPER_ENEMY_AGNI_RUDRA"     ],
	[ "Agni & Rudra Black"    , "HELPER_ENEMY_AGNI_RUDRA"     ],
	[ "Agni & Rudra Red"      , "HELPER_ENEMY_AGNI_RUDRA"     ],
	[ "Agni & Rudra Blue"     , "HELPER_ENEMY_AGNI_RUDRA"     ],
	[ "Nevan"                 , "HELPER_ENEMY_NEVAN"          ],
	[ "Geryon"                , "HELPER_ENEMY_GERYON"         ],
	[ "Beowulf"               , "HELPER_ENEMY_BEOWULF"        ],
	[ "Doppelganger"          , "HELPER_ENEMY_DOPPELGANGER"   ],
	[ "Arkham"                , "HELPER_ENEMY_ARKHAM"         ],
	[ ""                      , "0"                           ],
	[ "Lady"                  , "HELPER_ENEMY_LADY"           ],
	[ ""                      , "0"                           ],
	[ ""                      , "0"                           ],
	[ "Vergil"                , "HELPER_ENEMY_VERGIL"         ],
	[ ""                      , "0"                           ],
	[ "Leviathan Heart"       , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Leviathan Other"       , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Jester"                , "HELPER_ENEMY_JESTER"         ],
	[ ""                      , "0"                           ],
];

let tagName = "Enemy";



ClearAll();



let c_until = "";
let c_after = "";
let c_new   = "";

let lines = GetLines(file);

let startName = new RegExp("\\/\\/ \\$" + tagName + "Start$");
let endName   = new RegExp("\\/\\/ \\$" + tagName + "End$"  );

console.log(startName);
console.log(endName);

if
(
	!Tag_Init
	(
		lines,
		startName,
		endName
	)
)
{
	console.log("Tag_Init failed.");

	process.exit(1);

	return;
}



Tag_CopyUntil(lines);

c_until = c;

ClearAll();



Tag_CopyAfter(lines);

c_after = c;

ClearAll();



// Enum
{

let items2 = [];

for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
{
	let item = items[itemIndex];

	let name        = item[0];
	let helperIndex = item[1];

	items2.push([ name, "" ]);
}

items2.push([ "COUNT", "" ]);



c += "export namespaceStart(ENEMY);" + NEW_LINE;

CreateEnum
(
	"",
	items2,
	"",
	EnumFlags_UpperCase
);

c += "namespaceEnd();" + NEW_LINE;
c += NEW_LINE;

}



// Names
{

c += "export const char * enemyNames[] =" + NEW_LINE;

ScopeStart();

for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
{
	let item = items[itemIndex];

	let name        = item[0];
	let helperIndex = item[1];

	c += Tabs() + "\"" + name + "\"," + NEW_LINE;
}

ScopeEnd
(
	"}",
	ScopeFlags_Semicolon
);

c += NEW_LINE;

}



// Helper Indices
{

c += "export constexpr uint8 enemyHelperIndices[] =" + NEW_LINE;

ScopeStart();

for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
{
	let item = items[itemIndex];

	let name        = item[0];
	let helperIndex = item[1];

	c += Tabs() + helperIndex + "," + NEW_LINE;
}

ScopeEnd
(
	"}",
	ScopeFlags_Semicolon
);

c += NEW_LINE;

}



CleanStream();

c_new = c;

ClearAll();



file = c_until + c_new + c_after;

}
// #endregion

// #region StyleData
{

let items =
[
	[ "rank"    , "uint32", [], 0     ],
	[ "meter"   , "float" , [], 4     ],
	[ "quotient", "float" , [], 0x150 ],
	[ "dividend", "float" , [], 0x154 ],
	[ "divisor" , "float" , [], 0x158 ],
];

FeedStruct
(
	"StyleData",
	items,
	352
);

}
// #endregion

// #region FileDataStatus
{

let names =
[
	[ "Free"  , "" ],
	[ ""      , "" ],
	[ ""      , "" ],
	[ "In Use", "" ],
];

FeedEnum
(
	"FILE_DATA_STATUS",
	names,
	"FileDataStatus"
);

}
// #endregion

// #region FileDataTypeData
{

let items =
[
	[ "_(8)"    , ""            , [] ],
	[ "typeName", "const char *", [] ],
];

FeedStruct
(
	"FileDataTypeData",
	items
);

}
// #endregion

// #region FileData
{

let items =
[
	[ "group"       , "uint32"            , [] ],
	[ "status"      , "uint32"            , [] ],
	[ "_(16)"       , ""                  , [] ],
	[ "typeDataAddr", "FileDataTypeData *", [] ],
	[ "file"        , "byte8 *"           , [] ],
	[ "_(32)"       , ""                  , [] ],
];

FeedStruct
(
	"FileData",
	items,
	72
);

}
// #endregion

// #region FileDataMetadata
{

let items =
[
	[ "funcAddrs"   , "void *"    , [] ],
	[ "lastAddr"    , "void *"    , [] ],
	[ "nextAddr"    , "void *"    , [] ],
	[ "fileDataAddr", "FileData *", [] ],
	[ "_(4)"        , ""          , [] ],
	[ "category"    , "uint32"    , [] ],
	[ "fileSetIndex", "uint32"    , [] ],
	[ "_(4)"        , ""          , [] ],
];

FeedStruct
(
	"FileDataMetadata",
	items,
	48
);

}
// #endregion

// #region WeaponData
{

let items =
[
	[ "speed"          , "float"  , [], 0x14  ],
	[ "speedMultiplier", "float"  , [], 0x18  ],
	[ "baseAddr"       , "byte8 *", [], 0x48  ],
	[ "weapon"         , "uint8"  , [], 0x112 ],
	[ "value"          , "uint8"  , [], 0x118 ],
	[ "actorBaseAddr"  , "byte8 *", [], 0x120 ],
];

FeedStruct
(
	"WeaponData",
	items
);

}
// #endregion

// #region BodyPartData
{

let items =
[
	[ "motionArchives", "byte8 **"   , [], 0x68 ],
	[ "modelDataAddr" , "ModelData *", [], 0x70 ],
	[ "busy"          , "bool"       , [], 0xBA ],
];

FeedStruct
(
	"BodyPartData",
	items,
	288
);

}
// #endregion

// #region LockOnData
{

let items =
[
	[ ""                , "byte8 *", [], 0      ], // 41C0-41C0=0
	[ ""                , "byte8 *", [], 0x1008 ], // 51C8-41C0=1008
	[ ""                , "byte8 *", [], 0x1010 ], // 51D0-41C0=1010
	[ ""                , "byte8 *", [], 0x1018 ], // 51D8-41C0=1018
	[ "targetCount"     , "uint32" , [], 0x2048 ], // 6208-41C0=2048
	[ "targetPosition"  , "vec4"   , [], 0x2140 ], // 6300-41C0=2140
	[ "targetBaseAddr60", "byte8 *", [], 0x2168 ], // 6328-41C0=2168
	[ ""                , "byte8 *", [], 0x2170 ], // 6330-41C0=2170
];

FeedStruct
(
	"LockOnData",
	items,
	8568
);

}
// #endregion

// #region CreateEnemyActorData
{

let items =
[
	[ "enemy"      , "uint32", [], 0    ], // dmc3.exe+97B6D - 8B 03               - mov eax,[rbx]
	[ "position"   , "vec4"  , [], 0x10 ], // dmc3.exe+98005 - 41 0F28 87 20060000 - movaps xmm0,[r15+00000620]
	[ "rotation"   , "uint16", [], 0x20 ], // dmc3.exe+9803C - 41 0FB7 87 30060000 - movzx eax,word ptr [r15+00000630]
	[ "spawnMethod", "uint16", [], 0x22 ], // dmc3.exe+6843B - 0FB7 41 22          - movzx eax,word ptr [rcx+22]
	[ "variant"    , "uint32", [], 0x28 ], // dmc3.exe+9836D - 41 39 B7 38060000   - cmp [r15+00000638],esi
];

FeedStruct
(
	"CreateEnemyActorData",
	items,
	128
);

}
// #endregion

// #region CacheFile
{

let items =
[
	// Dante
	[ "pl000"              , "obj"    ],
	[ "pl011"              , "obj"    ],
	[ "pl013"              , "obj"    ],
	[ "pl015"              , "obj"    ],
	[ "pl016"              , "obj"    ],
	[ "pl018"              , "obj"    ],
	[ "pl005"              , "obj"    ],
	[ "pl006"              , "obj"    ],
	[ "pl007"              , "obj"    ],
	[ "pl008"              , "obj"    ],
	[ "pl009"              , "obj"    ],
	[ "pl017"              , "obj"    ],
	[ "pl000_00_0"         , "motion" ],
	[ "pl000_00_1"         , "motion" ],
	[ "pl000_00_2"         , "motion" ],
	[ "pl000_00_3"         , "motion" ],
	[ "pl000_00_4"         , "motion" ],
	[ "pl000_00_5"         , "motion" ],
	[ "pl000_00_6"         , "motion" ],
	[ "pl000_00_7"         , "motion" ],
	[ "pl000_00_8"         , "motion" ],
	[ "pl000_00_9"         , "motion" ],
	[ "pl000_00_10"        , "motion" ],
	[ "pl000_00_11"        , "motion" ],
	[ "pl000_00_12"        , "motion" ],
	[ "pl000_00_13"        , "motion" ],
	[ "pl000_00_14"        , "motion" ],
	[ "pl000_00_15"        , "motion" ],
	[ "pl000_00_16"        , "motion" ],
	[ "pl000_00_17"        , "motion" ],
	[ "pl000_00_18"        , "motion" ],
	[ "pl000_00_19"        , "motion" ],
	[ "pl000_00_20"        , "motion" ],
	[ "pl000_00_21"        , "motion" ],
	[ "pl000_00_22"        , "motion" ],
	[ "pl000_00_23"        , "motion" ],
	[ "pl000_00_24"        , "motion" ],
	[ "pl000_00_25"        , "motion" ],
	[ "pl000_00_26"        , "motion" ],
	[ "plwp_sword"         , "obj"    ],
	[ "plwp_sword2"        , "obj"    ],
	[ "plwp_sword3"        , "obj"    ],
	[ "plwp_nunchaku"      , "obj"    ],
	[ "plwp_2sword"        , "obj"    ],
	[ "plwp_guitar"        , "obj"    ],
	[ "plwp_fight"         , "obj"    ],
	[ "plwp_gun"           , "obj"    ],
	[ "plwp_shotgun"       , "obj"    ],
	[ "plwp_laser"         , "obj"    ],
	[ "plwp_rifle"         , "obj"    ],
	[ "plwp_ladygun"       , "obj"    ],
	[ "snd_com0"           , "se"     ],
	[ "snd_com0a"          , "se"     ],
	[ "snd_sty02"          , "se"     ],
	[ "snd_sty03"          , "se"     ],
	[ "snd_sty04"          , "se"     ],
	[ "snd_sty05"          , "se"     ],
	[ "snd_sty06"          , "se"     ],
	[ "snd_wp00b"          , "se"     ],
	[ "snd_wp01b"          , "se"     ],
	[ "snd_wp02b"          , "se"     ],
	[ "snd_wp03b"          , "se"     ],
	[ "snd_wp04b"          , "se"     ],
	[ "snd_wp05b"          , "se"     ],
	[ "snd_wp06b"          , "se"     ],
	[ "snd_wp07b"          , "se"     ],
	[ "snd_wp08b"          , "se"     ],
	[ "snd_wp09b"          , "se"     ],
	// Bob
	[ "pl001"              , "obj"    ],
	[ "pl001_00_0"         , "motion" ],
	[ "pl001_00_1"         , "motion" ],
	[ "pl001_00_2"         , "motion" ],
	[ "pl001_00_31"        , "motion" ],
	[ "plwp_vergilsword"   , "obj"    ],
	// Lady
	[ "pl002"              , "obj"    ],
	[ "pl002_00_0"         , "motion" ],
	[ "pl002_00_1"         , "motion" ],
	[ "pl002_00_2"         , "motion" ],
	// Vergil
	[ "pl021"              , "obj"    ],
	[ "pl023"              , "obj"    ],
	[ "pl026"              , "obj"    ],
	[ "pl010"              , "obj"    ],
	[ "pl014"              , "obj"    ],
	[ "pl025"              , "obj"    ],
	[ "pl021_00_0"         , "motion" ],
	[ "pl021_00_1"         , "motion" ],
	[ "pl021_00_2"         , "motion" ],
	[ "pl021_00_3"         , "motion" ],
	[ "pl021_00_4"         , "motion" ],
	[ "pl021_00_5"         , "motion" ],
	[ "pl021_00_6"         , "motion" ],
	[ "pl021_00_7"         , "motion" ],
	[ "pl021_00_8"         , "motion" ],
	[ "pl021_00_9"         , "motion" ],
	[ "plwp_newvergilsword", "obj"    ],
	[ "plwp_newvergilfight", "obj"    ],
	[ "plwp_forceedge"     , "obj"    ],
	[ "plwp_nerosword"     , "obj"    ],
	[ "snd_com3"           , "se"     ],
	[ "snd_com3a"          , "se"     ],
	[ "snd_sty07"          , "se"     ],
	[ "snd_sty08"          , "se"     ],
	[ "snd_wp11a"          , "se"     ],
	[ "snd_wp11b"          , "se"     ],
	[ "snd_wp12a"          , "se"     ],
	[ "snd_wp12b"          , "se"     ],
	[ "snd_wp13a"          , "se"     ],
	[ "snd_wp13b"          , "se"     ],
	// Enemy
	[ "em000"              , "obj"    ],
	[ "em006"              , "obj"    ],
	[ "em007"              , "obj"    ],
	[ "em008"              , "obj"    ],
	[ "em010"              , "obj"    ],
	[ "em011"              , "obj"    ],
	[ "em012"              , "obj"    ],
	[ "em013"              , "obj"    ],
	[ "em014"              , "obj"    ],
	[ "em016"              , "obj"    ],
	[ "em017"              , "obj"    ],
	[ "em021"              , "obj"    ],
	[ "em023"              , "obj"    ],
	[ "em025"              , "obj"    ],
	[ "em026"              , "obj"    ],
	[ "em027"              , "obj"    ],
	[ "em028"              , "obj"    ],
	[ "em029"              , "obj"    ],
	[ "em030"              , "obj"    ],
	[ "em031"              , "obj"    ],
	[ "em032"              , "obj"    ],
	[ "em034"              , "obj"    ],
	[ "em035"              , "obj"    ],
	[ "em037"              , "obj"    ],
	[ "snd_em00a"          , "se"     ],
	[ "snd_em00b"          , "se"     ],
	[ "snd_em06"           , "se"     ],
	[ "snd_em07"           , "se"     ],
	[ "snd_em08"           , "se"     ],
	[ "snd_em10"           , "se"     ],
	[ "snd_em11"           , "se"     ],
	[ "snd_em12"           , "se"     ],
	[ "snd_em13"           , "se"     ],
	[ "snd_em14"           , "se"     ],
	[ "snd_em16"           , "se"     ],
	[ "snd_em17"           , "se"     ],
	[ "snd_em21"           , "se"     ],
	[ "snd_em23"           , "se"     ],
	[ "snd_em25"           , "se"     ],
	[ "snd_em26"           , "se"     ],
	[ "snd_em27"           , "se"     ],
	[ "snd_em28"           , "se"     ],
	[ "snd_em29"           , "se"     ],
	[ "snd_em30"           , "se"     ],
	[ "snd_em31"           , "se"     ],
	[ "snd_em32"           , "se"     ],
	[ "snd_em34"           , "se"     ],
	[ "snd_em35"           , "se"     ],
	[ "snd_em37"           , "se"     ],
	[ "snd_emsr"           , "se"     ],
	[ "snd_stay"           , "se"     ],
	// Other
	[ "id100"              , "id"     ],
	[ "id100V"             , "id"     ],
];

let tagName = "CacheFile";



ClearAll();



let c_until = "";
let c_after = "";
let c_new   = "";

let lines = GetLines(file);

let startName = new RegExp("\\/\\/ \\$" + tagName + "Start$");
let endName   = new RegExp("\\/\\/ \\$" + tagName + "End$"  );

console.log(startName);
console.log(endName);

if
(
	!Tag_Init
	(
		lines,
		startName,
		endName
	)
)
{
	console.log("Tag_Init failed.");

	process.exit(1);

	return;
}



Tag_CopyUntil(lines);

c_until = c;

ClearAll();



Tag_CopyAfter(lines);

c_after = c;

ClearAll();



// Enum
{

let names = [];

for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
{
	let item = items[itemIndex];

	let name        = item[0];
	let helperIndex = item[1];

	names.push([ name, "" ]);
}

names.push([ "CACHE_FILE_COUNT", "" ]);



CreateEnum
(
	"",
	names,
	"",
	EnumFlags_Export
);

c += NEW_LINE;

}



// Helper
{

c += "export struct CacheFileHelper" + NEW_LINE;

ScopeStart();

c += "\tconst char * filename;" + NEW_LINE;
c += "\tconst char * typeName;" + NEW_LINE;

ScopeEnd
(
	"}",
	ScopeFlags_Semicolon
);

c += NEW_LINE;

c += "export constexpr CacheFileHelper cacheFileHelpers[CACHE_FILE_COUNT] =" + NEW_LINE;

ScopeStart();

// @Research: Consider forward slash.

for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
{
	let item = items[itemIndex];

	let name = item[0];
	let type = item[1];



	c += Tabs() + "{ \"" + name + ".pac\", \"";

	if (type == "obj")
	{
		c += "obj\\\\" + name + ".pac";
	}
	else if (type == "motion")
	{
		let parent = name.match(/([\S\s]+?)_/);
		if (parent)
		{
			c += "motion\\\\" + parent[1] + "\\\\" + name + ".pac";
		}
	}
	else if (type == "id")
	{
		let id = name.match(/id([0-9]+?)[A-Z]*?$/);
		if (id)
		{
			let str = id[1];
			if (str.length >= 3)
			{
				str = str.substring(0, (str.length - 2)) + "00";
			}
			c += "id\\\\id" + str + "\\\\" + name + ".pac";
		}
	}
	else if (type == "se")
	{
		c += "se\\\\" + name + ".pac";
	}
	c += "\" }," + NEW_LINE;
}

ScopeEnd
(
	"}",
	ScopeFlags_Semicolon
);

c += NEW_LINE;

c += "static_assert(countof(cacheFileHelpers) == CACHE_FILE_COUNT);" + NEW_LINE;
c += NEW_LINE;

}



CleanStream();

c_new = c;

ClearAll();



file = c_until + c_new + c_after;

}
// #endregion

// #region Item
{

let tagName = "Item";



ClearAll();



let c_until = "";
let c_after = "";
let c_new   = "";

let lines = GetLines(file);

let startName = new RegExp("\\/\\/ \\$" + tagName + "Start$");
let endName   = new RegExp("\\/\\/ \\$" + tagName + "End$"  );

console.log(startName);
console.log(endName);

if
(
	!Tag_Init
	(
		lines,
		startName,
		endName
	)
)
{
	console.log("Tag_Init failed.");

	process.exit(1);

	return;
}



Tag_CopyUntil(lines);

c_until = c;

ClearAll();



Tag_CopyAfter(lines);

c_after = c;

ClearAll();



// Default
{

let items =
[
	[ ""                         , "" ],
	[ ""                         , "" ],
	[ ""                         , "" ],
	[ ""                         , "" ],
	[ ""                         , "" ],
	[ "Gold Orb"                 , "" ],
	[ "Yellow Orb"               , "" ],
	[ "Blue Orb"                 , "" ],
	[ "Purple Orb"               , "" ],
	[ "Blue Orb Fragment"        , "" ],
	[ ""                         , "" ],
	[ ""                         , "" ],
	[ ""                         , "" ],
	[ ""                         , "" ],
	[ ""                         , "" ],
	[ ""                         , "" ],
	[ "Vital Star Large"         , "" ],
	[ "Vital Star Small"         , "" ],
	[ "Devil Star"               , "" ],
	[ "Holy Water"               , "" ],
	[ ""                         , "" ],
	[ ""                         , "" ],
	[ ""                         , "" ],
	[ ""                         , "" ],
	[ ""                         , "" ],
	[ ""                         , "" ],
	[ ""                         , "" ],
	[ ""                         , "" ],
	[ ""                         , "" ],
	[ ""                         , "" ],
	[ ""                         , "" ],
	[ ""                         , "" ],
	[ ""                         , "" ],
	[ ""                         , "" ],
	[ ""                         , "" ],
	[ ""                         , "" ],
	[ "Astronomical Board"       , "" ],
	[ "Vajura"                   , "" ],
	[ ""                         , "" ],
	[ "Soul of Steel"            , "" ],
	[ "Essence of Fighting"      , "" ],
	[ "Essence of Technique"     , "" ],
	[ "Essence of Intelligence"  , "" ],
	[ "Orihalcon Fragment"       , "" ],
	[ "Siren's Shriek"           , "" ],
	[ "Crystal Skull"            , "" ],
	[ "Ignis Fatuus"             , "" ],
	[ "Ambrosia"                 , "" ],
	[ "Stone Mask"               , "" ],
	[ "Neo-Generator"            , "" ],
	[ "Haywire Neo-Generator"    , "" ],
	[ "Orihalcon"                , "" ],
	[ "Orihalcon Fragment Right" , "" ],
	[ "Orihalcon Fragment Bottom", "" ],
	[ "Orihalcon Fragment Left"  , "" ],
	[ "Golden Sun"               , "" ],
	[ "Onyx Moonshard"           , "" ],
	[ "Samsara"                  , "" ],
	[ ""                         , "" ],
	[ ""                         , "" ],
	[ ""                         , "" ],
	[ ""                         , "" ],
];

let names = [];



for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
{
	let item = items[itemIndex];

	let name  = item[0];
	let value = item[1];

	names.push(name);
}

items.push([ "COUNT", "" ]);



c += "export namespaceStart(ITEM);" + NEW_LINE;

CreateEnum
(
	"",
	items,
	"",
	EnumFlags_UpperCase
);

c += "namespaceEnd();" + NEW_LINE;
c += NEW_LINE;



c += "export const char * itemNames[] =" + NEW_LINE;

ScopeStart();

for (let nameIndex = 0; nameIndex < names.length; nameIndex++)
{
	let name = names[nameIndex];

	c += Tabs() + "\"" + name + "\"," + NEW_LINE;
}

ScopeEnd
(
	"}",
	ScopeFlags_Semicolon
);

c += NEW_LINE;

}



// Buy
{

let items =
[
	[ "Vital Star Small", "" ],
	[ "Vital Star Large", "" ],
	[ "Devil Star"      , "" ],
	[ "Holy Water"      , "" ],
	[ "Blue Orb"        , "" ],
	[ "Purple Orb"      , "" ],
	[ "Gold Orb"        , "" ],
	[ "Yellow Orb"      , "" ],
];

let names = [];



for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
{
	let item = items[itemIndex];

	let name  = item[0];
	let value = item[1];

	names.push(name);
}

items.push([ "COUNT", "" ]);



c += "export namespaceStart(BUY);" + NEW_LINE;

CreateEnum
(
	"",
	items,
	"",
	EnumFlags_UpperCase
);

c += "namespaceEnd();" + NEW_LINE;
c += NEW_LINE;



c += "export const char * buyNames[] =" + NEW_LINE;

ScopeStart();

for (let nameIndex = 0; nameIndex < names.length; nameIndex++)
{
	let name = names[nameIndex];

	c += Tabs() + "\"" + name + "\"," + NEW_LINE;
}

ScopeEnd
(
	"}",
	ScopeFlags_Semicolon
);

c += NEW_LINE;

}



CleanStream();

c_new = c;

ClearAll();



file = c_until + c_new + c_after;

}
// #endregion

// #region QueuedMissionActorData
{

let items =
[
	[ "weapons[5]"        , "uint8" , [], 0    ],
	[ "hitPoints"         , "float" , [], 0x50 ],
	[ "magicPoints"       , "float" , [], 0x54 ],
	[ "style"             , "uint32", [], 0x58 ],
	[ "styleLevel[6]"     , "uint32", [], 0x5C ],
	[ "styleExperience[6]", "float" , [], 0x74 ],
	[ "expertise[8]"      , "byte32", [], 0x8C ],
];

FeedStruct
(
	"QueuedMissionActorData",
	items
);

}
// #endregion

// #region ActiveMissionActorData
{

let items =
[
	[ "weapons[5]"     , "uint8" , [], 0    ],
	[ "style"          , "uint32", [], 0x38 ],
	[ "styleLevel"     , "uint32", [], 0x3C ],
	[ "expertise[8]"   , "byte32", [], 0x40 ],
	[ "styleExperience", "float" , [], 0x60 ],
	[ "hitPoints"      , "float" , [], 0x64 ],
	[ "maxHitPoints"   , "float" , [], 0x68 ],
	[ "magicPoints"    , "float" , [], 0x6C ],
	[ "maxMagicPoints" , "float" , [], 0x70 ],
];

FeedStruct
(
	"ActiveMissionActorData",
	items
);

}
// #endregion



fs.writeFileSync(location, file);
