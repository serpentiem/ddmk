let fs = require("fs");
let process = require("process");
let vm = require("vm");

vm.runInThisContext(fs.readFileSync("core.js", "utf8"));

ClearAll();



const Flags_NoSave  = 1 << 0;
const Flags_NoClear = 1 << 1;



function SaveStream(name)
{
	let c_new = c;

	c = "";

	let filename = "../Mary/Vars.ixx";

	let file = fs.readFileSync(filename, "utf8");

	let lines = GetLines(file);



	let startName = new RegExp("\\/\\/ \\$" + name + "Start$");
	let endName   = new RegExp("\\/\\/ \\$" + name + "End$"  );

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

	c += c_new;

	Tag_CopyAfter(lines);

	fs.writeFileSync(filename, c);



	ClearAll();
}

function FeedTuple
(
	name,
	items,
	size = 0,
	tagName = name,
	flags = 0
)
{
	CreateTuple
	(
		name,
		items,
		size,
		0,
		TupleFlags_Export
	);



	ClearAsserts();

	CreateTupleAsserts
	(
		name,
		items,
		size,
		0,
		TupleFlags_NoTypeAssert
	);

	MergeAsserts();
	FeedAsserts();

	CleanStream();

	if (!(flags & Flags_NoSave))
	{
		SaveStream(tagName);
	}
}

function FeedEnum
(
	name,
	names,
	tagName = name,
	flags = 0
)
{
	c += "export namespaceStart(" + name + ");" + NEW_LINE;
	c += "enum" + NEW_LINE;

	ScopeStart();

	let unknownIndex = 0;

	for (let nameIndex = 0; nameIndex < names.length; nameIndex++)
	{
		let name = names[nameIndex];

		if (name == "")
		{
			name = name + "UNKNOWN_" + unknownIndex;

			unknownIndex++;
		}

		name = ReplaceAll(name, "-", " ");

		name = ReplaceAll(name, "&", "");

		name = ReplaceAll(name, "  ", " ");

		name = ReplaceAll(name, " ", "_");

		name = name.toUpperCase();

		c += Tabs() + name + "," + NEW_LINE;
	}

	ScopeEnd
	(
		"}",
		ScopeFlags_Semicolon
	);

	c += "namespaceEnd();" + NEW_LINE;
	c += NEW_LINE;


	if (!(flags & Flags_NoSave))
	{
		SaveStream(tagName);
	}
}



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

FeedTuple
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
	[ "unlock[14]"           , "bool"  , [], 0x46  ],
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

FeedTuple
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

FeedTuple
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

FeedTuple
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
	[ "id"                             , "uint8"             , [], 0x118  ],
	[ "isClone"                        , "bool32"            , [], 0x11C  ],
	[ "visibility"                     , "uint32"            , [], 0x120  ],
	[ "horizontalPull"                 , "float"             , [], 0x1C0  ],
	[ "horizontalPullMultiplier"       , "float"             , [], 0x1C4  ],
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



/*

41C0 lock on data start
51D0 last lock on data addr
51D8 last lock on data addr
6208 lock on data count
6300 vec4 target position




Update Lock-On Data Boss Vergil

dmc3.exe+185724 - 48 8B 0D FDB6B000 - mov rcx,[dmc3.exe+C90E28]
dmc3.exe+18572B - 48 8D 97 C0EA0000 - lea rdx,[rdi+0000EAC0]
dmc3.exe+185732 - E8 095F0300       - call dmc3.exe+1BB640



Update Lock-On Data Boss Lady

dmc3.exe+171379 - 48 8B 0D A8FAB100     - mov rcx,[dmc3.exe+C90E28]
dmc3.exe+171380 - 48 8D 96 F0560000     - lea rdx,[rsi+000056F0]
dmc3.exe+171387 - E8 B4A20400           - call dmc3.exe+1BB640











enemies update lock-on data

rdx GUILockOnData



disable boss vergil lock-on update





*/



	[ "targetPosition"                 , "vec4"           , [], 0x6300 ],



	// base addr + 60
	[ "targetBaseAddr"                 , "byte8 *"           , [], 0x6328 ],


/*

lock on gui data


*/


/*

lock on data

16 bytes of trash

target gui lock on data addr

apparently 255 entries

addr
nextAddr



gui lock on data

82 bytes

judging by

dmc3.exe+1BBE2E - 66 44 89 77 50        - mov [rdi+50],r14w




if newPlayerIndex == 0
use 1

if 1 use 0

if player is 0

update gui lock on data as well

2 functions

fill position stuff










*/





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
	[ "royalguardBlockType"         , "uint32"             , [], 0x6370 ],
	[ "royalguardReleaseLevel"         , "uint8"             , [], 0x6380 ],
	[ "royalguardReleaseEffectIndex"   , "uint8"             , [], 0x6381 ],
	[ "royalguardReleaseDamage"        , "float"             , [], 0x6384 ],
	[ ""                               , "float"             , [], 0x6388 ],
	[ ""                               , "float"             , [], 0x638C ],
	[ ""                      , "uint32"            , [], 0x63D0 ],
	[ "quicksilverStage"                      , "uint32"            , [], 0x63D4 ],
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


/*


player is target dmc3.exe+173B5D - C7 86 D0020000 43040300 - mov [rsi+000002D0],00030443
enemy  is target dmc3.exe+173B76 - C7 86 D0020000 0C050300 - mov [rsi+000002D0],0003050C


dmc3.exe+188825 - C7 83 C0020000 40040000 - mov [rbx+000002C0],00000440 { sjc follow collision flags
 }
dmc3.exe+18882F - BA 11000000           - mov edx,00000011 { 17 }




dmc3.exe+5C964 - 8B 81 40010000        - mov eax,[rcx+00000140] { collision group
 }



*/




	[ "buttons[4]"                     , "byte16"            , [], 0x74E0 ],
	[ "rightStickPosition"             , "uint16"            , [], 0x74F8 ],
	[ "rightStickRadius"               , "uint16"            , [], 0x74FA ],
	[ "leftStickPosition"              , "uint16"            , [], 0x7508 ],
	[ "leftStickRadius"                , "uint16"            , [], 0x750A ],
	[ "actorCameraDirection"           , "uint16"            , [], 0x750C ],
	[ "leftStickDirection[2]"          , "uint32"            , [], 0x751C ],
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
	[ "artemisChargeValue[2]"               , "float"                  , [], 0xB868 ],
	[ "artemisChargeFlags[2]"               , "byte32"                 , [], 0xB87C ],
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
	// [ "newContainerIndex"                      , "uint8"            , [], ],

	[ "newForceFiles"                          , "bool"             , [], ],
	[ "newForceFilesCharacter"                 , "uint8"            , [], ],
	[ "newForceFilesCostume"                   , "uint8"            , [], ],

	[ "newEnableVisibility"                    , "bool"             , [], ],

	// @Todo: Should be index.
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



	[ "newEffectIndices[12]"                   , "uint32"           , [], ],

	[ "newLastVar"                             , "uint32"           , [], ],
];

let itemsEnemyPride =
[
	[ "maxHitPoints" , "float", [], 0x2E2C ],
	[ "hitPoints" , "float", [], 0x2E5C ],
	[ "event" , "uint32", [], 0x3A34 ],
	[ "state" , "uint8" , [], 0x3A38 ],
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






/*

dmc3.exe+2C72E0 - 44 0FB7 0A            - movzx r9d,word ptr [rdx]

rotation update

*/























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
	TupleFlags_Export
);

ClearAsserts();

CreateTupleAsserts
(
	"ActorDataBase",
	itemsBase,
	SIZE_BASE,
	0,
	TupleFlags_NoTypeAssert
);

MergeAsserts();
FeedAsserts();



// Player Base

CreateTuple
(
	"PlayerActorDataBase : ActorDataBase",
	itemsPlayerBase,
	SIZE_PLAYER_BASE,
	SIZE_BASE,
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
	"PlayerActorDataBase",
	itemsPlayerBase,
	SIZE_PLAYER_BASE,
	SIZE_BASE,
	TupleFlags_NoTypeAssert,
	PositionFlags_Hex
);

MergeAsserts();
FeedAsserts();

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

	let tuplename = "PlayerActorData" + name;

	CreateTuple
	(
		tuplename + " : PlayerActorDataBase",
		items,
		SIZE_PLAYER_DANTE,
		SIZE_PLAYER_BASE,
		TupleFlags_Export |
		TupleFlags_NoScopeEnd
	);

	CreateTupleFunction
	(
		itemsPlayerNew,
		SIZE_PLAYER_DANTE,
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
		SIZE_PLAYER_DANTE,
		SIZE_PLAYER_BASE,
		TupleFlags_NoTypeAssert |
		TupleFlags_NoSizeAssert,
		PositionFlags_Hex,
		AlignFunction
	);

	CreateTupleAsserts
	(
		tuplename,
		itemsPlayerNew,
		0,
		SIZE_PLAYER_DANTE,
		TupleFlags_NoTypeAssert |
		TupleFlags_NoSizeAssert,
		PositionFlags_Hex,
		AlignFunction
	);

	MergeAsserts();
	FeedAsserts();

	c += NEW_LINE;
}

}








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


	let tuplename = "EnemyActorData" + name;

	CreateTuple
	(
		tuplename + " : ActorDataBase",
		items,
		0,
		SIZE_BASE,
		TupleFlags_Export
	);



	ClearAsserts();

	CreateTupleAsserts
	(
		tuplename,
		items,
		0,
		SIZE_BASE,
		TupleFlags_NoTypeAssert |
		TupleFlags_NoSizeAssert
	);

	MergeAsserts();
	FeedAsserts();
}




CleanStream();



































// const SIZE_BASE = 200;



SaveStream("ActorData");


// let c_new = c;

// c = "";

// let filename = "../Mary/Vars.ixx";

// let file = fs.readFileSync(filename, "utf8");

// let lines = GetLines(file);

// if
// (
// 	!Tag_Init
// 	(
// 		lines,
// 		/\/\/ \$ActorDataStart$/,
// 		/\/\/ \$ActorDataEnd$/
// 	)
// )
// {
// 	console.log("Tag_Init failed.");

// 	return;
// }

// Tag_CopyUntil(lines);

// c += c_new;

// Tag_CopyAfter(lines);

// fs.writeFileSync(filename, c);

// ClearAll();














// Cheat Engine

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
		"Mary.Global::g_playerActorBaseAddrs",
		[ posName ]
	);

	CreateCheatEntries
	(
		itemsPlayerBase,
		"Mary.Global::g_playerActorBaseAddrs",
		[ posName ],
		SIZE_BASE
	);

	CreateCheatEntries
	(
		itemsPlayerNew,
		"Mary.Global::g_playerActorBaseAddrs",
		[ posName ],
		SIZE_PLAYER_DANTE,
		0,
		AlignFunction
	);

	GroupEnd();
}

CheatTableEnd();

fs.writeFileSync("actor_data.txt", c);

ClearAll();































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

FeedTuple
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

FeedTuple
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

let names =
[
	"",
	"",
	"",
	"",
	"",
	"Jump",
	"",
	"Air Hike",
	"",
	"",
	"Lock-On",
	"",
	"",
	"",
	"",
	"",
	"",
	"Attack",
	"Taunt",
	"Royalguard Block",
	"Royalguard Block Connect",
	"Royalguard Release Blocked",
	"Trickster Dash",
	"Trickster Sky Star",
	"Trickster Air Trick",
	"Quicksilver Time Lag",
	"",
	"Dark Slayer Air Trick",
	"Dark Slayer Trick Up",
	"Dark Slayer Trick Down",
	"Melee Attack Blocked",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"Nevan Air Raid",
	"Super Jump",
	"",
	"Holy Water",
	"",
	"Death",
	"Count",
];

FeedEnum
(
	"ACTOR_EVENT",
	names,
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

FeedTuple
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

FeedTuple
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



// Enum

let names = [];

for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
{
	let item = items[itemIndex];

	let name = item[0];

	names.push(name);
}

names.push("COUNT");

FeedEnum
(
	"ENEMY",
	names,
	"",
	Flags_NoSave
);






// c += "export enum" + NEW_LINE;

// ScopeStart();

// let unknownIndex = 0;

// for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
// {
// 	let item = items[itemIndex];

// 	let name = item[0];
// 	let helperIndex = item[1];

// 	let enumName = name;

// 	if (enumName == "Unknown")
// 	{
// 		enumName = enumName + "_" + unknownIndex;

// 		unknownIndex++;
// 	}

// 	enumName = ReplaceAll(enumName, "-", " ");

// 	enumName = ReplaceAll(enumName, "&", "");

// 	enumName = ReplaceAll(enumName, "  ", " ");

// 	enumName = ReplaceAll(enumName, " ", "_");

// 	enumName = "ENEMY_" + enumName.toUpperCase();

// 	c += Tabs() + enumName + "," + NEW_LINE;
// }

// c += Tabs() + "ENEMY_COUNT," + NEW_LINE;
// c += Tabs() + "CREATE_ENEMY_COUNT = 30," + NEW_LINE;

// ScopeEnd
// (
// 	"}",
// 	ScopeFlags_Semicolon
// );

// c += NEW_LINE;



// Names

c += "export const char * enemyNames[] =" + NEW_LINE;

ScopeStart();

for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
{
	let item = items[itemIndex];

	let name = item[0];
	let helperIndex = item[1];

	c += Tabs() + "\"" + name + "\"," + NEW_LINE;
}

ScopeEnd
(
	"}",
	ScopeFlags_Semicolon
);

c += NEW_LINE;



// Helper Indices

c += "export constexpr uint8 enemyHelperIndices[] =" + NEW_LINE;

ScopeStart();

for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
{
	let item = items[itemIndex];

	let name = item[0];
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


SaveStream("Enemy");


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


FeedTuple
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
	"Free",
	"",
	"",
	"In Use",
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

FeedTuple
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

FeedTuple
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

FeedTuple
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

FeedTuple
(
	"WeaponData",
	items
);

}
// #endregion








