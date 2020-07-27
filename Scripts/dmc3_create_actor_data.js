var fs = require("fs");

eval(fs.readFileSync("dmc3_core.js", "utf8"));

const CHAR_DANTE  = 1;
const CHAR_BOB    = 2;
const CHAR_LADY   = 4;
const CHAR_VERGIL = 8;

const ACTOR_DATA_SIZE_DANTE  = 0xB8C0;
const ACTOR_DATA_SIZE_BOB    = 0xB680;
const ACTOR_DATA_SIZE_LADY   = 0x8280;
const ACTOR_DATA_SIZE_VERGIL = 0xB8C0;

//const NEW_ACTOR_DATA_START = (64 * 1024);
const NEW_ACTOR_DATA_START = 0xB8C0;

var items =
[
	[ "status"                              , "uint8"                   , 8                                ],
	[ "character"                           , "uint32"                  , 0x78                             ],
	[ "position"                            , "vec4"                    , 0x80                             ],
	[ "pull"                                , "float32"                 , 0x94                             ],
	[ "pullMultiplier"                      , "float32"                 , 0xA4                             ],
	[ "rotation"                            , "uint16"                  , 0xC0                             ],
	[ "id"                                  , "uint8"                   , 0x118                            ],
	[ "isClone"                             , "bool32"                  , 0x11C                            ],
	[ "visible"                             , "uint32"                  , 0x120                            ],
	[ ""                                    , "float32"                 , 0x1C0                            ],
	[ ""                                    , "float32"                 , 0x1C4                            ],

	[ "modelData[3]"                        , "ModelData"               , 0x200                            ],








	[ "modelPhysicsMetadataPool[4][24]"     , "PhysicsMetadata *"       , 0x1880                           ],




	[ "modelAllocationDataCount", "uint32"       , 0x1B80                           ],
	[ "modelAllocationData[209]", "Size_32"      , 0x1B88                           ],













	//[ "[4][24]"     , "Size_32"       , 0x1B88                           ],








	[ "motionSpeed"                   , "float32"                 , 0x3894                           ],
	[ "motionSpeedMultiplier"                   , "float32"                 , 0x3898                           ],



	[ "motionArchive[32]"                   , "byte8 *"                 , 0x38A0                           ],
	[ "motionData[2]"                       , "MOTION_DATA"             , 0x39B0                           ],
	[ "motionDataMirror[3]"                 , "MOTION_DATA"             , 0x39B4                           ],
	[ ""                                    , "uint32"                  , 0x39BC                           ],
	[ "[16]"                                , "uint8"                   , 0x39C0                           ],
	[ "nextActionRequestPolicy[16]"         , "uint32"                  , 0x39D0                           ],
	[ "[8]"                                 , "uint8"                   , 0x3A10                           ],
	[ "shadow"                              , "uint32"                  , 0x3A18                           ],
	[ "color"                               , "byte32"                  , 0x3A28                           ],
















	[ "actionData[6]"                       , "byte8 *"                 , 0x3DD0                           ],
	[ "eventData[2]"                        , "ACTOR_EVENT_DATA"        , 0x3E00                           ],
	[ "[32]"                                , "uint8"                   , 0x3E10                           ],
	[ "motionTimer"                         , "float32"                 , 0x3E34                           ],
	[ "idleTimer"                           , "float32"                 , 0x3E38                           ],
	[ "permissions"                         , "byte32"                  , 0x3E60                           ],
	[ "state"                               , "byte32"                  , 0x3E64                           ],
	[ "lastState"                           , "byte32"                  , 0x3E68                           ],

	[ "activeModelIndex"                    , "uint32"                  , 0x3E6C                           ],
	[ "queuedModelIndex"                    , "uint32"                  , 0x3E70                           ],
	[ "devilModels[3]"                      , "uint32"                  , 0x3E74                           ],

	[ "modelState"                          , "uint8"                   , 0x3E80                           ],
	[ "lockOn"                              , "bool32"                  , 0x3E84                           ],

	[ "activeModelIndexMirror"              , "uint32"                  , 0x3E88                           ],
	[ "activeDevil"                         , "uint32"                  , 0x3E8C                           ],

	[ "airRaid"                             , "uint32"                  , 0x3E90                           ],
	[ "mode"                                , "uint32"                  , 0x3E94                           ],
	[ "devil"                               , "bool"                    , 0x3E9B                           ],
	[ "costume"                             , "uint8"                   , 0x3E9E                           ],
	[ "sparda"                              , "bool"                    , 0x3E9F, CHAR_DANTE               ],
	[ "neroAngelo"                          , "bool"                    , 0x3E9F, CHAR_VERGIL              ],
	[ "useHolyWater"                        , "bool"                    , 0x3EA4                           ],
	[ "magicPoints"                         , "float32"                 , 0x3EB8                           ],
	[ "maxMagicPoints"                      , "float32"                 , 0x3EBC                           ],
	[ ""                                    , "uint16"                  , 0x3ED2                           ],
	[ "cameraDirection"                     , "uint16"                  , 0x3ED8                           ],
	[ "airHikeCount"                        , "uint8"                   , 0x3F11                           ],
	[ "kickJumpCount"                       , "uint8"                   , 0x3F12                           ],
	[ "wallHikeCount"                       , "uint8"                   , 0x3F13                           ],
	[ ""                                    , "bool"                    , 0x3F19                           ],
	[ "action"                              , "uint8"                   , 0x3FA4                           ],
	[ "lastAction"                          , "uint8"                   , 0x3FA5                           ],
	[ "bufferedAction"                      , "uint8"                   , 0x3FA8                           ],
	[ "chainCount"                          , "uint8"                   , 0x3FAC                           ],
	[ "expertise[16]"                       , "byte32"                  , 0x3FEC                           ],
	[ "maxHitPoints"                        , "float32"                 , 0x40EC                           ],
	[ "hitPoints"                           , "float32"                 , 0x411C                           ],
	[ "targetBaseAddr"                      , "byte8 *"                 , 0x6328                           ],
	[ "style"                               , "uint32"                  , 0x6338                           ],
	[ "styleLevel"                          , "uint32"                  , 0x6358                           ],
	[ "dashCount"                           , "uint8"                   , 0x635C, CHAR_DANTE               ],
	[ "skyStarCount"                        , "uint8"                   , 0x635D, CHAR_DANTE               ],
	[ "airTrickCount"                       , "uint8"                   , 0x635E, CHAR_DANTE | CHAR_VERGIL ],
	[ "trickUpCount"                        , "uint8"                   , 0x635F, CHAR_VERGIL              ],
	[ "trickDownCount"                      , "uint8"                   , 0x6360, CHAR_VERGIL              ],
	[ "quicksilver"                         , "bool"                    , 0x6361, CHAR_DANTE               ],
	[ "doppelganger"                        , "bool"                    , 0x6362, CHAR_DANTE               ],
	[ "styleExperience"                     , "float32"                 , 0x6364                           ],
	[ "cloneIsActive"                       , "bool"                    , 0x6454                           ],
	[ "cloneBaseAddr"                       , "byte8 *"                 , 0x6478                           ],
	[ "cloneIsControlledByPlayer"           , "bool"                    , 0x6480                           ],
	[ "activeMeleeWeaponIndex"              , "uint32"                  , 0x6484, CHAR_VERGIL              ],
	[ "queuedMeleeWeaponIndex"              , "uint32"                  , 0x6488, CHAR_VERGIL              ],
	[ "activeWeapon"                        , "uint8"                   , 0x648D, CHAR_DANTE               ],
	[ "meleeWeaponIndex"                    , "uint32"                  , 0x6490, CHAR_DANTE               ],
	[ "rangedWeaponIndex"                   , "uint32"                  , 0x6494, CHAR_DANTE               ],
	[ "weapons[5]"                          , "uint8"                   , 0x6498                           ],
	[ "weaponData[5]"                       , "byte8 *"                 , 0x64A0                           ],
	[ "weaponStatus[5]"                     , "uint32"                  , 0x64C8                           ],
	[ "weaponLevels[5]"                     , "uint32"                  , 0x64DC                           ],
	[ "activeMeleeWeapon"                   , "uint8"                   , 0x64F0, CHAR_DANTE               ],
	[ "activeRangedWeapon"                  , "uint8"                   , 0x64F1, CHAR_DANTE               ],
	[ "weaponTimers[5]"                     , "float32"                 , 0x64F4                           ],
	[ "meleeWeaponSwitchTimeout"            , "float32"                 , 0x6508, CHAR_DANTE               ],
	[ "rangedWeaponSwitchTimeout"           , "float32"                 , 0x650C, CHAR_DANTE               ],
	[ "meleeWeaponSwitchForwardTimeout"     , "float32"                 , 0x6508, CHAR_VERGIL              ],
	[ "meleeWeaponSwitchBackTimeout"        , "float32"                 , 0x650C, CHAR_VERGIL              ],
	[ "styleRank"                           , "uint32"                  , 0x6510                           ],
	[ "styleMeter"                          , "float32"                 , 0x6514                           ],
	[ "inputData[58]"                       , "INPUT_DATA"              , 0x6674                           ],





	[ "bodyPartData[4][2]"                      , "BodyPartData"                  , 0x6950                           ], // Relocated.

















	[ ""                      , "uint32"                  , 0x7250                           ],



	[ "collisionIndex"                      , "uint32"                  , 0x7254                           ],
	[ "interactionData[8]"                  , "vec4"                    , 0x7460                           ],
	[ "buttons[4]"                          , "byte16"                  , 0x74E0                           ],
	[ "rightStickPosition"                  , "uint16"                  , 0x74F8                           ],
	[ "rightStickRadius"                    , "uint16"                  , 0x74FA                           ],
	[ "leftStickPosition"                   , "uint16"                  , 0x7508                           ],
	[ "leftStickRadius"                     , "uint16"                  , 0x750A                           ],
	[ "actorCameraDirection"                , "uint16"                  , 0x750C                           ],
	[ "leftStickDirection[2]"               , "uint32"                  , 0x751C                           ],




	[ "submodelData[5]"                     , "ModelData"               , 0x7540                           ], // Relocated.







	[ "[5]"                                 , "bool"                    , 0x9AC0                           ],

	[ "modelShadowData[3]"                  , "ShadowData"              , 0x9AD0                           ], // Relocated.
	[ "submodelShadowData[5]"               , "ShadowData"              , 0x9D10                           ], // Relocated.









	[ "submodelPhysicsMetadataPool[39]"             , "byte8 *"         , 0xA0D0                           ], // Relocated.



	[ "submodelPhysicsData"                 , "PhysicsData"             , 0xA210                           ], // Relocated.













	[ "devilModelPhysicsLinkMetadataPool[2][36]", "PhysicsLinkMetadata *"  , 0xA300                           ], // Relocated.













	[ "devilSubmodelPhysicsData[4]"         , "PhysicsData"             , 0xA540                           ], // Relocated.
	[ "devilSubmodelPhysicsLinkData[4][4]"         , "PhysicsLinkData"        , 0xAA00                           ], // Relocated.











	[ "devilModelMetadata"                  , "DevilModelMetadataDante" , 0xB600, CHAR_DANTE               ],
	[ "modelMetadata[6]"                    , "ModelMetadata"           , 0xB630, CHAR_DANTE               ],

	[ "artemisChargeValue[2]"               , "float32"                 , 0xB868, CHAR_DANTE               ],
	[ "artemisChargeFlags[2]"               , "byte32"                  , 0xB87C, CHAR_DANTE               ],
];










var extra =
[




	[ "newModelPhysicsMetadataPool[7][24]", "PhysicsMetadata *" ],



	[ "newModelAllocationData[512]", "Size_32" ],










	[ "newParentBaseAddr"      , "byte8 *" ],
	[ "newChildBaseAddr"       , "byte8 *" ],
	[ "newGamepad"             , "uint8"   ],
	[ "newButtonMask"          , "byte16"  ],
	[ "newEnableRightStick"    , "bool"    ],
	[ "newEnableLeftStick"     , "bool"    ],
	[ "newMeleeWeapon[5]"      , "uint8"   ],
	[ "newMeleeWeaponData[5]"  , "byte8 *" ],
	[ "newMeleeWeaponCount"    , "uint8"   ],
	[ "newMeleeWeaponIndex"    , "uint8"   ],
	[ "newLastMeleeWeapon"     , "uint8"   ],
	[ "newRangedWeapon[5]"     , "uint8"   ],
	[ "newRangedWeaponData[5]" , "byte8 *" ],
	[ "newRangedWeaponCount"   , "uint8"   ],
	[ "newRangedWeaponIndex"   , "uint8"   ],
	[ "newLastRangedWeapon"    , "uint8"   ],
	[ "newSect[8]"             , "bool"    ],
	[ "newBufferedActionPolicy", "uint8"   ],
	[ "newAirStingerCount"     , "uint8"   ],
	[ "newForceFiles"          , "bool"    ],
	[ "newForceFilesCharacter" , "uint8"   ],
	[ "newDevilAura"           , "byte8 *" ],
	[ "newEffectIndices[8]"    , "byte32"  ],

	// [ "newBodyPartData[7][2]", "BodyPartData" ],

	// [ "newSubmodelData[11]", "ModelData" ],

	// [ "newModelShadowData[6]", "ShadowData" ],
	// [ "newSubmodelShadowData[11]", "ShadowData" ],





	// [ "newSubmodelPhysicsMetadata[2]", "PhysicsMetadata" ],






	// [ "newSubmodelPhysicsData[2]", "PhysicsData" ],



	// [ "newDevilSubmodelPhysicsData[10]", "PhysicsData" ],




	// [ "newDevilSubmodelPhysicsLinkData[10][4]", "PhysicsLinkData" ],



	// [ "newDevilModelPhysicsLinkMetadataPool[5][36]", "PhysicsLinkMetadata *" ],




	//[ "newModelPhysicsMetadataPool[10][24]"     , "PhysicsMetadata *" ],




	
	


	
	//[ "newModelPhysicsMetadataAllocationCount"      , "uint32"            ],
	//[ "newModelPhysicsMetadataAllocationData[4][24]", "Size_32"           ],





	[ "newLastVar", "uint32" ],




];

// Cpp

console.log("Cpp");
console.log("");

var c_assert = "";

var filename = "../Mary/Vars.h"

var file = fs.readFileSync(filename, "utf8");

var startTag = /\/\/ \$ActorDataStart$/;
var endTag   = /\/\/ \$ActorDataEnd$/;

var startTagLine = -1;
var endTagLine   = -1;

var obj = file.match(/[\S\s]*?\r\n/g);

for (var index = 0; index < obj.length; index++)
{
	var str = obj[index].substring(0, (obj[index].length - 2));
	if (str.match(startTag))
	{
		startTagLine = index;
		break;
	}
}

if (startTagLine == -1)
{
	console.log("Start tag not found.");
	return;
}

for (var index = 0; index < obj.length; index++)
{
	var str = obj[index].substring(0, (obj[index].length - 2));
	if (str.match(endTag))
	{
		endTagLine = index;
		break;
	}
}

if (endTagLine == -1)
{
	console.log("End tag not found.");
	return;
}

if (endTagLine < startTagLine)
{
	console.log("End tag appears before start tag.");
	return;
}

console.log("startTagLine " + (startTagLine + 1));
console.log("endTagLine   " + (endTagLine   + 1));

for (var index = 0; index <= startTagLine; index++)
{
	var str = obj[index].substring(0, (obj[index].length - 2));
	c += str + NEW_LINE;
}

c += NEW_LINE;



function CreateActorDataFunction
(
	structName,
	name,
	type
)
{
	if (!IsKnownType(type))
	{
		console.log("Unknown " + type);
		return;
	}

	var count = 1;
	var size = GetTypeSize(type);

	if (name == "")
	{
		name = "var_" + pos.toString(16).toUpperCase();
	}
	else if (name.substring(0, 1) == "[")
	{
		name = "var_" + pos.toString(16).toUpperCase() + name;
	}

	{
		var matches = name.match(/\[\d+?\]/g);
		if (matches)
		{
			for (var matchIndex = 0; matchIndex < matches.length; matchIndex++)
			{
				count *= parseInt(matches[matchIndex].match(/\[(\d+?)\]/)[1]);
			}
		}
	}

	size *= count;

	var posString = "";
	if (pos >= 10)
	{
		posString = "0x" + pos.toString(16).toUpperCase();
	}
	else
	{
		posString = pos.toString();
	}

	c += "\t" + type + " " + name + "; // " + posString + NEW_LINE;

	c_assert += "static_assert(offsetof(" + structName + ", " + name.split("[")[0] + ") == " + posString + ");" + NEW_LINE;

	pos += size;
}

function CreateActorData
(
	structName,
	id
)
{
	c += "struct " + structName + NEW_LINE;
	c += "{" + NEW_LINE;
	
	pos = 0;

	for (var itemIndex = 0; itemIndex < items.length; itemIndex++)
	{
		var item = items[itemIndex];

		var name      = item[0];
		var type      = item[1];
		var off       = item[2];
		var character = item[3];

		if ((character != undefined) && !(character & id))
		{
			continue;
		}

		var diff = (off - pos);
		if (diff)
		{
			c += "\t_(" + diff.toString() + ");" + NEW_LINE;
		}

		pos = off;

		CreateActorDataFunction(structName, name, type);
	}

	var diff = (NEW_ACTOR_DATA_START - pos);
	if (diff)
	{
		c += "\t_(" + diff.toString() + ");" + NEW_LINE;
	}

	pos = NEW_ACTOR_DATA_START;

	for (var itemIndex = 0; itemIndex < extra.length; itemIndex++)
	{
		var item = extra[itemIndex];

		var name = item[0];
		var type = item[1];

		var lastPos = pos;

		if (type.match(/\*/))
		{
			Align(16);
		}
		else if (name.match(/\[/))
		{
			Align(16);
		}

		var diff = (pos - lastPos);
		if (diff)
		{
			c += "\t_(" + diff.toString() + ");" + NEW_LINE;
		}

		CreateActorDataFunction(structName, name, type);
	}

	c += "" + NEW_LINE;
	c += "\toperator byte8 *()" + NEW_LINE;
	c += "\t{" + NEW_LINE;
	c += "\t\treturn reinterpret_cast<byte8 *>(this);" + NEW_LINE;
	c += "\t}" + NEW_LINE;

	c += "};" + NEW_LINE;
}

CreateActorData("ACTOR_DATA", 0);
c_assert += "" + NEW_LINE;
c += "" + NEW_LINE;

CreateActorData("ACTOR_DATA_DANTE", CHAR_DANTE);
c_assert += "" + NEW_LINE;
c += "" + NEW_LINE;

CreateActorData("ACTOR_DATA_BOB", CHAR_BOB);
c_assert += "" + NEW_LINE;
c += "" + NEW_LINE;

CreateActorData("ACTOR_DATA_LADY", CHAR_LADY);
c_assert += "" + NEW_LINE;
c += "" + NEW_LINE;

CreateActorData("ACTOR_DATA_VERGIL", CHAR_VERGIL);

c += NEW_LINE;
c += c_assert;



c += NEW_LINE;

for (var index = endTagLine; index < obj.length; index++)
{
	var str = obj[index].substring(0, (obj[index].length - 2));
	c += str + NEW_LINE;
}

fs.writeFileSync(filename, c);

console.log("");

// Cheat Engine

console.log("Cheat Engine");
console.log("");

function CreateActorCheatEntryFunction
(
	name,
	type,
	off,
	hex,
	actor
)
{
	CreateCheatEntry
	(
		name,
		hex,
		type,
		"Mary.Actor_actorBaseAddr",
		off.toString(16).toUpperCase(),
		(actor * 8).toString(16).toUpperCase()
	);
}

function CreateActorCheatEntry
(
	name,
	type,
	actor
)
{
	if (!IsKnownType(type))
	{
		console.log("Unknown " + type);
		return;
	}

	var count = 1;
	var size = GetTypeSize(type);
	var variableType = GetVariableType(type);
	var hex = GetShowAsHex(type);

	if (name == "")
	{
		name = "var_" + pos.toString(16).toUpperCase();
	}
	else if (name.substring(0, 1) == "[")
	{
		name = "var_" + pos.toString(16).toUpperCase() + name;
	}

	{
		var matches = name.match(/\[\d+?\]/g);
		if (matches)
		{
			for (var matchIndex = 0; matchIndex < matches.length; matchIndex++)
			{
				count *= parseInt(matches[matchIndex].match(/\[(\d+?)\]/)[1]);
			}
		}
	}

	for (var index = 0; index < count; index++, pos += size)
	{
		var description = name.split("[")[0];

		if (count > 1)
		{
			description += " " + lz(index);
		}

		if (variableType != "")
		{
			CreateActorCheatEntryFunction(description, variableType, pos, hex, actor);
			continue;
		}

		if (type.match(/Size_/))
		{
			continue;
		}
		else if (type == "vec4")
		{
			CreateActorCheatEntryFunction(description + " x", "Float", (pos + 0  ), false, actor);
			CreateActorCheatEntryFunction(description + " y", "Float", (pos + 4  ), false, actor);
			CreateActorCheatEntryFunction(description + " z", "Float", (pos + 8  ), false, actor);
			CreateActorCheatEntryFunction(description + " a", "Float", (pos + 0xC), false, actor);
			continue;
		}
		else if (type == "MOTION_DATA")
		{
			CreateActorCheatEntryFunction(description + " index", "Byte", (pos + 0), false, actor);
			CreateActorCheatEntryFunction(description + " group", "Byte", (pos + 1), false, actor);
			continue;
		}
		else if (type == "INPUT_DATA")
		{
			continue;
		}
		else if (type == "MODEL_METADATA")
		{
			continue;
		}
		else if (type == "ModelData")
		{
			continue;
		}
		else if (type == "DevilModelMetadataDante")
		{
			continue;
		}
		else if (type == "ACTOR_EVENT_DATA")
		{
			continue;
		}
		else if (type == "BodyPartData")
		{
			continue;
		}
		else if (type == "ModelMetadata")
		{
			continue;
		}
		else if (type == "PhysicsLinkData")
		{
			continue;
		}
		else if (type == "ShadowData")
		{
			continue;
		}
		else if (type == "PhysicsData")
		{
			continue;
		}
		else if (type == "PhysicsMetadata")
		{
			continue;
		}
		else
		{
			console.log("Ignore " + type);
		}
	}
}

function CreateCheatEntries
(
	groupName,
	id
)
{
	GroupStart(groupName, true);

	for (var actor = 0; actor < 4; actor++)
	{
		GroupStart(lz(actor), true);

		// Main

		for (var itemIndex = 0; itemIndex < items.length; itemIndex++)
		{
			var item = items[itemIndex];

			var name      = item[0];
			var type      = item[1];
			var off       = item[2];
			var character = item[3];

			if ((character != undefined) && !(character & id))
			{
				continue;
			}

			pos = off;

			CreateActorCheatEntry(name, type, actor);
		}

		pos = NEW_ACTOR_DATA_START;

		// Ex

		for (var itemIndex = 0; itemIndex < extra.length; itemIndex++)
		{
			var item = extra[itemIndex];

			var name = item[0];
			var type = item[1];

			if (type.match(/\*/))
			{
				Align(16);
			}
			else if (name.match(/\[/))
			{
				Align(16);
			}

			CreateActorCheatEntry(name, type, actor);
		}

		GroupEnd();
	}
	
	GroupEnd();
}

c = "";

CheatTableStart();

// CreateCheatEntries("ACTOR_DATA"       , 0          );
CreateCheatEntries("ACTOR_DATA_DANTE" , CHAR_DANTE );
// CreateCheatEntries("ACTOR_DATA_BOB"   , CHAR_BOB   );
// CreateCheatEntries("ACTOR_DATA_LADY"  , CHAR_LADY  );
// CreateCheatEntries("ACTOR_DATA_VERGIL", CHAR_VERGIL);

CheatTableEnd();

fs.writeFileSync("actorData.txt", c);
