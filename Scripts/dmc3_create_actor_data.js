let fs = require("fs");
let vm = require("vm");

vm.runInThisContext(fs.readFileSync("dmc3_core.js", "utf8"));

const SIZE_BASE   = 0x7540;
const SIZE_DANTE  = 0xB8C0;
const SIZE_BOB    = 0xB680;
const SIZE_LADY   = 0x8280;
const SIZE_VERGIL = 0xB8C0;

let itemsBase =
[
	[ "status"                         , "uint8"             , [], 8      ],
	[ "speed"                          , "float"             , [], 0x14   ],
	[ "speedMultiplier"                , "float"             , [], 0x18   ],
	[ "character"                      , "uint32"            , [], 0x78   ],
	[ "position"                       , "vec4"              , [], 0x80   ],
	[ "pull"                           , "float"             , [], 0x94   ],
	[ "pullMultiplier"                 , "float"             , [], 0xA4   ],
	[ "rotation"                       , "uint16"            , [], 0xC0   ],
	[ "id"                             , "uint8"             , [], 0x118  ],
	[ "isClone"                        , "bool32"            , [], 0x11C  ],
	[ "visibility"                     , "uint32"            , [], 0x120  ],
	[ ""                               , "float"             , [], 0x1C0  ],
	[ ""                               , "float"             , [], 0x1C4  ],
	[ "modelData[3]"                   , "ModelData"         , [], 0x200  ],
	[ "modelPhysicsMetadataPool[4][24]", "PhysicsMetadata *" , [], 0x1880 ],
	[ "modelAllocationDataCount"       , "uint32"            , [], 0x1B80 ],
	[ "modelAllocationData[209]"       , "Size_32"           , [], 0x1B88 ],
	[ "motionSpeed"                    , "float"             , [], 0x3894 ],
	[ "motionSpeedMultiplier"          , "float"             , [], 0x3898 ],
	[ "motionArchives[34]"             , "byte8 *"           , [], 0x38A0 ],
	[ "motionData[2]"                  , "MotionData"        , [], 0x39B0 ],
	[ "motionDataMirror[3]"            , "MotionData"        , [], 0x39B4 ],
	[ ""                               , "uint32"            , [], 0x39BC ],
	[ "[16]"                           , "uint8"             , [], 0x39C0 ],
	[ "nextActionRequestPolicy[16]"    , "uint32"            , [], 0x39D0 ],
	[ "[8]"                            , "uint8"             , [], 0x3A10 ],
	[ "shadow"                         , "uint32"            , [], 0x3A18 ],
	[ "lastShadow"                     , "uint32"            , [], 0x3A1C ],
	[ "color"                          , "byte32"            , [], 0x3A28 ],
	[ "recoveryData[3]"                , "RecoveryData"      , [], 0x3B00 ],
	[ "[2]"                            , "byte8"             , [], 0x3C50 ],
	[ "actionData[6]"                  , "byte8 *"           , [], 0x3DD0 ],
	[ "eventData[2]"                   , "ActorEventData"    , [], 0x3E00 ],
	[ "[32]"                           , "uint8"             , [], 0x3E10 ],
	[ "motionTimer"                    , "float"             , [], 0x3E34 ],
	[ "idleTimer"                      , "float"             , [], 0x3E38 ],
	[ "permissions"                    , "byte32"            , [], 0x3E60 ],
	[ "state"                          , "byte32"            , [], 0x3E64 ],
	[ "lastState"                      , "byte32"            , [], 0x3E68 ],
	[ "activeModelIndex"               , "uint32"            , [], 0x3E6C ],
	[ "queuedModelIndex"               , "uint32"            , [], 0x3E70 ],
	[ "devilModels[3]"                 , "uint32"            , [], 0x3E74 ],
	[ "modelState"                     , "uint8"             , [], 0x3E80 ],
	[ "lockOn"                         , "bool32"            , [], 0x3E84 ],
	[ "activeModelIndexMirror"         , "uint32"            , [], 0x3E88 ],
	[ "activeDevil"                    , "uint32"            , [], 0x3E8C ],
	[ "airRaid"                        , "uint32"            , [], 0x3E90 ],
	[ "mode"                           , "uint32"            , [], 0x3E94 ],
	[ "dead"                           , "bool"              , [], 0x3E99 ],
	[ "devil"                          , "bool"              , [], 0x3E9B ],
	[ "costume"                        , "uint8"             , [], 0x3E9E ],
	[ ""                               , "union",
		[
			[ "sparda"    , "bool" ],
			[ "neroAngelo", "bool" ],
		],
		0x3E9F
	],
	[ "useHolyWater"                   , "bool"              , [], 0x3EA4 ],
	[ "magicPoints"                    , "float"             , [], 0x3EB8 ],
	[ "maxMagicPoints"                 , "float"             , [], 0x3EBC ],
	[ ""                               , "float"             , [], 0x3EC4 ],
	[ ""                               , "float"             , [], 0x3EC8 ],
	[ ""                               , "uint16"            , [], 0x3ED2 ],
	[ "cameraDirection"                , "uint16"            , [], 0x3ED8 ],
	[ ""                               , "float"             , [], 0x3EDC ],
	[ "airHikeCount"                   , "uint8"             , [], 0x3F11 ],
	[ "kickJumpCount"                  , "uint8"             , [], 0x3F12 ],
	[ "wallHikeCount"                  , "uint8"             , [], 0x3F13 ],
	[ "enableAirRaid"                  , "bool"              , [], 0x3F14 ],
	[ ""                               , "bool"              , [], 0x3F19 ],
	[ "action"                         , "uint8"             , [], 0x3FA4 ],
	[ "lastAction"                     , "uint8"             , [], 0x3FA5 ],
	[ "bufferedAction"                 , "uint8"             , [], 0x3FA8 ],
	[ "chainCount"                     , "uint8"             , [], 0x3FAC ],
	[ "expertise[16]"                  , "byte32"            , [], 0x3FEC ],
	[ "maxHitPoints"                   , "float"             , [], 0x40EC ],
	[ "hitPoints"                      , "float"             , [], 0x411C ],
	[ "targetBaseAddr"                 , "byte8 *"           , [], 0x6328 ],
	[ "style"                          , "uint32"            , [], 0x6338 ],
	[ "wallHikeDirection"              , "uint32"            , [], 0x633C ],
	[ ""                               , "uint32"            , [], 0x6340 ],
	[ "styleLevel"                     , "uint32"            , [], 0x6358 ],
	[ "dashCount"                      , "uint8"             , [], 0x635C ],
	[ "skyStarCount"                   , "uint8"             , [], 0x635D ],
	[ "airTrickCount"                  , "uint8"             , [], 0x635E ],
	[ "trickUpCount"                   , "uint8"             , [], 0x635F ],
	[ "trickDownCount"                 , "uint8"             , [], 0x6360 ],
	[ "quicksilver"                    , "bool"              , [], 0x6361 ],
	[ "doppelganger"                   , "bool"              , [], 0x6362 ],
	[ "styleExperience"                , "float"             , [], 0x6364 ],
	[ "royalguardReleaseLevel"         , "uint8"             , [], 0x6380 ],
	[ "royalguardReleaseEffectIndex"   , "uint8"             , [], 0x6381 ],
	[ "royalguardReleaseDamage"        , "float"             , [], 0x6384 ],
	[ ""                               , "float"             , [], 0x6388 ],
	[ ""                               , "float"             , [], 0x638C ],
	[ "speedMode"                      , "uint32"            , [], 0x63D4 ],
	// @Research: Consider CloneData.
	[ "[40]"                           , "byte8"             , [], 0x6410 ],
	[ ""                               , "byte8 *"           , [], 0x6438 ],
	[ ""                               , "uint32"            , [], 0x6440 ],
	[ "cloneRate"                      , "uint32"            , [], 0x6450 ],
	[ "cloneStatus"                    , "uint32"            , [], 0x6454 ],
	[ "[32]"                           , "byte8"             , [], 0x6458 ],
	[ "cloneActorBaseAddr"             , "byte8 *"           , [], 0x6478 ],
	[ "cloneIsControlledByPlayer"      , "bool"              , [], 0x6480 ],
	[ "activeMeleeWeaponIndex"         , "uint32"            , [], 0x6484 ],
	[ "queuedMeleeWeaponIndex"         , "uint32"            , [], 0x6488 ],
	[ "activeWeapon"                   , "uint8"             , [], 0x648D ],
	[ "meleeWeaponIndex"               , "uint32"            , [], 0x6490 ],
	[ "rangedWeaponIndex"              , "uint32"            , [], 0x6494 ],
	[ "weapons[5]"                     , "uint8"             , [], 0x6498 ],
	[ "weaponDataAddr[5]"              , "WeaponData *"      , [], 0x64A0 ],
	[ "weaponStatus[5]"                , "uint32"            , [], 0x64C8 ],
	[ "weaponLevels[5]"                , "uint32"            , [], 0x64DC ],
	[ "activeMeleeWeapon"              , "uint8"             , [], 0x64F0 ],
	[ "activeRangedWeapon"             , "uint8"             , [], 0x64F1 ],
	[ "weaponTimers[5]"                , "float"             , [], 0x64F4 ],
	[ "meleeWeaponSwitchTimeout"       , "float"             , [], 0x6508 ],
	[ "rangedWeaponSwitchTimeout"      , "float"             , [], 0x650C ],
	[ "styleData"                      , "StyleData"         , [], 0x6510 ],
	[ ""                               , "float"             , [], 0x6670 ],
	[ "inputData[58]"                  , "InputData"         , [], 0x6674 ],
	[ "bodyPartData[3][2]"             , "BodyPartData"      , [], 0x6950 ],
	[ "collisionData"                  , "CollisionData"     , [], 0x7250 ],
	[ "buttons[4]"                     , "byte16"            , [], 0x74E0 ],
	[ "rightStickPosition"             , "uint16"            , [], 0x74F8 ],
	[ "rightStickRadius"               , "uint16"            , [], 0x74FA ],
	[ "leftStickPosition"              , "uint16"            , [], 0x7508 ],
	[ "leftStickRadius"                , "uint16"            , [], 0x750A ],
	[ "actorCameraDirection"           , "uint16"            , [], 0x750C ],
	[ "leftStickDirection[2]"          , "uint32"            , [], 0x751C ],
];

let itemsDante =
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
	[ "artemisChargeValue[2]"               , "float"                  , [], 0xB868 ],
	[ "artemisChargeFlags[2]"               , "byte32"                 , [], 0xB87C ],
];

let itemsBob = [];
let itemsLady = [];

let itemsVergil =
[
	[ "submodelData[5]"                , "ModelData"        , [], 0x7540 ],
	[ "submodelInit[5]"                , "bool"             , [], 0x9AC0 ],
	[ "modelShadowData[3]"             , "ShadowData"       , [], 0x9AF0 ],
	[ "submodelShadowData[5]"          , "ShadowData"       , [], 0x9D30 ],
	[ "submodelPhysicsMetadataPool[39]", "PhysicsMetadata *", [], 0xA0F0 ],
	[ "submodelPhysicsData"            , "PhysicsData"      , [], 0xA230 ],
	[ "modelMetadata[6]"               , "ModelMetadata"    , [], 0xB640 ],
];

let itemsNew =
[
	[ "newFirstVar"                            , "uint32"           , [], ],

	[ "newModelData[6]"                        , "ModelData"        , [], ],
	[ "newModelPhysicsMetadataPool[7][24]"     , "PhysicsMetadata *", [], ],
	[ "newModelAllocationData[512]"            , "Size_32"          , [], ],
	[ "newRecoveryData[6]"                     , "RecoveryData"     , [], ],
	[ "newDevilModels[6]"                      , "uint32"           , [], ],
	[ "newBodyPartData[7][2]"                  , "BodyPartData"     , [], ],
	[ "newSubmodelData[11]"                    , "ModelData"        , [], ],
	[ "newSubmodelInit[11]"                    , "bool"             , [], ],
	[ "newModelShadowData[6]"                  , "ShadowData"       , [], ],
	[ "newSubmodelShadowData[11]"              , "ShadowData"       , [], ],
	[ "newDevilModelPhysicsMetadataPool[5][36]", "PhysicsMetadata *", [], ],
	[ "newDevilSubmodelPhysicsData[10]"        , "PhysicsData"      , [], ],
	[ "newDevilSubmodelPhysicsLinkData[10][4]" , "PhysicsLinkData"  , [], ],

	[ "newWeapons[10]"                         , "uint8"            , [], ],
	[ "newWeaponDataAddr[10]"                  , "WeaponData *"     , [], ],
	[ "newWeaponStatus[10]"                    , "uint32"           , [], ],
	[ "newWeaponLevels[10]"                    , "uint32"           , [], ],
	[ "newWeaponTimers[10]"                    , "float"            , [], ],

	[ "newIsClone"                             , "bool32"           , [], ],

	[ "newPlayerIndex"                         , "uint8"            , [], ],
	[ "newCharacterIndex"                      , "uint8"            , [], ],
	[ "newEntityIndex"                         , "uint8"            , [], ],

	[ "newForceFiles"                          , "bool"             , [], ],
	[ "newForceFilesCharacter"                 , "uint8"            , [], ],
	[ "newForceFilesCostume"                   , "uint8"            , [], ],

	[ "newEnableVisibility"                    , "bool"             , [], ],

	// @Todo: Should be index.
	[ "newGamepad"                             , "uint8"            , [], ],
	[ "newButtonMask"                          , "byte16"           , [], ],
	[ "newEnableRightStick"                    , "bool"             , [], ],
	[ "newEnableLeftStick"                     , "bool"             , [], ],

	[ "newAirStinger"                          , "bool"             , [], ],
	[ "newAirStingerCount"                     , "uint8"            , [], ],

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

	[ "newEffectIndices[12]"                   , "uint32"           , [], ],

	[ "newLastVar"                             , "uint32"           , [], ],
];



// Cpp

function AlignFunction
(
	pos,
	name,
	type
)
{
	let size = GetTypeSize(type);

	if
	(
		(type.match(/\*/)) ||
		(name.match(/\[/)) ||
		(size >= 8)
	)
	{
		pos = Align
		(
			pos,
			16
		);
	}
	else if
	(
		(size >= 4) &&
		(size < 8)
	)
	{
		pos = Align
		(
			pos,
			8
		);
	}

	return pos;
}

// Base

CreateTuple
(
	"ActorDataBase",
	itemsBase,
	SIZE_BASE,
	0,
	TupleFlags_Export |
	TupleFlags_NoScopeEnd
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

CreateTupleAsserts
(
	"ActorDataBase",
	itemsBase,
	SIZE_BASE,
	0,
	TupleFlags_NoTypeAssert,
	PositionFlags_Hex
);

MergeAsserts();
FeedAsserts();

c += NEW_LINE;

// Derived

let helpers =
[
	[ ""      , []          ],
	[ "Dante" , itemsDante  ],
	[ "Bob"   , itemsBob    ],
	[ "Lady"  , itemsLady   ],
	[ "Vergil", itemsVergil ],
];

for (let index = 0; index < helpers.length; index++)
{
	let helper = helpers[index];

	let name  = helper[0];
	let items = helper[1];

	let tuplename = "ActorData" + name;

	CreateTuple
	(
		tuplename + " : ActorDataBase",
		items,
		SIZE_DANTE,
		SIZE_BASE,
		TupleFlags_Export |
		TupleFlags_NoScopeEnd
	);

	CreateTupleFunction
	(
		itemsNew,
		SIZE_DANTE,
		0,
		AlignFunction
	);

	ScopeEnd
	(
		"}",
		ScopeFlags_Semicolon
	);

	ClearAsserts();

	CreateTupleAsserts
	(
		tuplename,
		items,
		SIZE_DANTE,
		SIZE_BASE,
		TupleFlags_NoTypeAssert |
		TupleFlags_NoSizeAssert,
		PositionFlags_Hex,
		AlignFunction
	);

	CreateTupleAsserts
	(
		tuplename,
		itemsNew,
		0,
		SIZE_DANTE,
		TupleFlags_NoTypeAssert |
		TupleFlags_NoSizeAssert,
		PositionFlags_Hex,
		AlignFunction
	);

	MergeAsserts();
	FeedAsserts();

	c += NEW_LINE;
}



CleanStream();

let c_new = c;

ClearAll();



let filename = "../Mary/Vars.ixx"

let file = fs.readFileSync(filename, "utf8");

let lines = GetLines(file);

if
(
	!Tag_Init
	(
		lines,
		/\/\/ \$ActorDataStart$/,
		/\/\/ \$ActorDataEnd$/
	)
)
{
	console.log("Tag_Init failed.");

	return;
}

Tag_CopyUntil(lines);

c += c_new;

Tag_CopyAfter(lines);

fs.writeFileSync(filename, c);






// Cheat Engine

c = "";

CheatTableStart();

let actorCount = 4;

for (let actorIndex = 0; actorIndex < actorCount; actorIndex++)
{
	let posName = PositionName
	(
		(8 * actorIndex),
		PositionFlags_Hex |
		PositionFlags_NoPrefix
	);

	GroupStart
	(
		"__" + lz(actorIndex) + "__",
		true
	);

	CreateCheatEntries
	(
		itemsBase,
		"Mary.Actor::Actor_actorBaseAddr",
		[ posName ]
	);

	CreateCheatEntries
	(
		itemsNew,
		"Mary.Actor::Actor_actorBaseAddr",
		[ posName ],
		SIZE_DANTE,
		0,
		AlignFunction
	);

	GroupEnd();
}

CheatTableEnd();

fs.writeFileSync("actor_data.txt", c);













