const CHAR_DANTE  = 1;
const CHAR_BOB    = 2;
const CHAR_LADY   = 4;
const CHAR_VERGIL = 8;

const ACTOR_DATA_SIZE_DANTE  = 0xB8C0
const ACTOR_DATA_SIZE_BOB    = 0xB680
const ACTOR_DATA_SIZE_LADY   = 0x8280
const ACTOR_DATA_SIZE_VERGIL = 0xB8C0

var items =
[
	[ "init"                            , "bool"                      , 8                                ],
	[ "character"                       , "uint32"                    , 0x78                             ],
	[ "position"                        , "vec4"                      , 0x80                             ],
	[ "pull"                        , "float32"                      , 0x94                             ],
	[ "pullMultiplier"                        , "float32"                      , 0xA4                             ],
	[ "direction"                       , "uint16"                    , 0xC0                             ],
	[ "id"                              , "uint8"                     , 0x118                            ],
	[ "isClone"                         , "bool"                      , 0x11C                            ], //but has size of uint32.
	[ "visible"                         , "uint32"                    , 0x120                            ],
	[ ""                         , "float32"                    , 0x1C0                            ],
	[ ""                         , "float32"                    , 0x1C4                            ],













	[ "modelData[3]"                    , "MODEL_DATA"                , 0x200                            ],
	[ "motionArchive[32]"               , "byte8 *"                   , 0x38A0                           ],
	[ "motionData[2]"                   , "MOTION_DATA"               , 0x39B0                           ],
	[ "motionDataMirror[3]"             , "MOTION_DATA"               , 0x39B4                           ],
	//[ "[6]"             , "uint8"               , 0x39BA                           ],
	[ ""             , "uint32"               , 0x39BC                           ],
	[ "[16]"             , "uint8"               , 0x39C0                           ],



	


	[ "nextActionRequestPolicy[16]" , "uint32"  , 0x39D0 ],
	[ "[8]"                         , "uint8"   , 0x3A10 ],
	[ "shadow"                      , "uint32"  , 0x3A18 ],
	[ "color"                       , "byte32"  , 0x3A28 ],
	[ "actionData[6]"               , "byte8 *" , 0x3DD0 ],
	[ "[4]"                         , "uint32"  , 0x3E00 ],
	[ "[32]"                        , "uint8"   , 0x3E10 ],
	[ "motionTimer"                 , "float32" , 0x3E34 ],
	[ "idleTimer"                   , "float32" , 0x3E38 ],
	[ "permissions"                 , "byte32"  , 0x3E60 ],
	[ "state"                       , "byte32"  , 0x3E64 ],
	[ "lastState"                   , "byte32"  , 0x3E68 ],





	[ "activeModelIndex"                , "uint32"                    , 0x3E6C                           ],
	[ "queuedModelIndex"                , "uint32"                    , 0x3E70                           ],
	[ "modelMap[3]"                     , "uint32"                    , 0x3E74                           ],
	[ "modelState"                      , "uint8"                     , 0x3E80                           ],
	[ "lockOn"                          , "bool"                      , 0x3E84                           ],
	[ "activeModelIndexMirror"          , "uint32"                    , 0x3E88                           ],
	[ "activeDevilModel"                , "uint32"                    , 0x3E8C                           ],
	[ "airRaid"                         , "uint32"                    , 0x3E90                           ], //but has size of uint32.
	[ "devilState"                      , "uint32"                    , 0x3E94                           ],
	[ "devil"                           , "bool"                      , 0x3E9B                           ],
	[ "costume"                         , "uint8"                     , 0x3E9E                           ],
	[ "sparda"                          , "bool"                      , 0x3E9F                           ], // @Research: Nero Angelo for Vergil.
	[ "useHolyWater"                    , "bool"                      , 0x3EA4                           ],
	[ "magicPoints"                     , "float32"                   , 0x3EB8                           ],
	[ "maxMagicPoints"                  , "float32"                   , 0x3EBC                           ],
	[ "cameraDirection"                 , "uint16"                    , 0x3ED8                           ],
	[ "moveOnly"                        , "bool"                      , 0x3F19                           ],


	[ "action"                            , "uint8"                     , 0x3FA4                           ],
	[ "lastAction"                        , "uint8"                     , 0x3FA5                           ],
	[ "bufferedAction"                    , "uint8"                     , 0x3FA8                           ],

	[ "chainCount"                      , "uint8"                     , 0x3FAC                           ],
	[ "expertise[16]"                   , "byte32"                    , 0x3FEC                           ],
	[ "maxHitPoints"                    , "float32"                   , 0x40EC                           ],
	[ "hitPoints"                       , "float32"                   , 0x411C                           ],
	[ "targetBaseAddr"                  , "byte8 *"                   , 0x6328                           ],
	[ "style"                           , "uint32"                    , 0x6338                           ],
	[ "styleLevel"                      , "uint32"                    , 0x6358                           ],
	[ "dashCount"                       , "uint8"                     , 0x635C, CHAR_DANTE               ],
	[ "skyStarCount"                    , "uint8"                     , 0x635D, CHAR_DANTE               ],
	[ "airTrickCount"                   , "uint8"                     , 0x635E, CHAR_DANTE | CHAR_VERGIL ],
	[ "trickUpCount"                    , "uint8"                     , 0x635F, CHAR_VERGIL              ],
	[ "trickDownCount"                  , "uint8"                     , 0x6360, CHAR_VERGIL              ],
	[ "quicksilver"                     , "bool"                      , 0x6361, CHAR_DANTE               ],
	[ "doppelganger"                    , "bool"                      , 0x6362, CHAR_DANTE               ],
	[ "styleExperience"                 , "float32"                   , 0x6364                           ],
	[ "cloneIsActive"                   , "bool"                      , 0x6454, CHAR_DANTE               ],
	[ "cloneBaseAddr"                   , "byte8 *"                   , 0x6478, CHAR_DANTE               ],
	[ "cloneIsControlledByPlayer"       , "bool"                      , 0x6480, CHAR_DANTE               ],
	[ "activeMeleeWeaponIndex"          , "uint32"                    , 0x6484, CHAR_VERGIL              ],
	[ "queuedMeleeWeaponIndex"          , "uint32"                    , 0x6488, CHAR_VERGIL              ],
	[ "activeWeapon"                    , "uint8"                     , 0x648D, CHAR_DANTE               ],
	[ "meleeWeaponIndex"                , "uint32"                    , 0x6490, CHAR_DANTE               ],
	[ "rangedWeaponIndex"               , "uint32"                    , 0x6494, CHAR_DANTE               ],

	[ "meleeWeaponMap[2]"               , "uint8"                     , 0x6498, CHAR_DANTE               ],
	[ "meleeWeaponMap[5]"               , "uint8"                     , 0x6498, CHAR_VERGIL              ],
	[ "rangedWeaponMap[3]"              , "uint8"                     , 0x649A, CHAR_DANTE               ],

	[ "meleeWeaponData[2]"              , "byte8 *"                   , 0x64A0, CHAR_DANTE               ],
	[ "meleeWeaponData[5]"              , "byte8 *"                   , 0x64A0, CHAR_VERGIL              ],
	[ "rangedWeaponData[3]"             , "byte8 *"                   , 0x64B0, CHAR_DANTE               ],

	[ "meleeWeaponFlags[2]"             , "byte32"                    , 0x64C8, CHAR_DANTE               ],
	[ "meleeWeaponFlags[5]"             , "byte32"                    , 0x64C8, CHAR_VERGIL              ],
	[ "rangedWeaponFlags[3]"            , "byte32"                    , 0x64D0, CHAR_DANTE               ],

	[ "meleeWeaponLevel[2]"             , "uint32"                    , 0x64DC, CHAR_DANTE               ],
	[ "meleeWeaponLevel[5]"             , "uint32"                    , 0x64DC, CHAR_VERGIL              ],
	[ "rangedWeaponLevel[3]"            , "uint32"                    , 0x64E4, CHAR_DANTE               ],




	[ "activeMeleeWeapon"               , "uint8"                     , 0x64F0, CHAR_DANTE               ],
	[ "activeRangedWeapon"              , "uint8"                     , 0x64F1, CHAR_DANTE               ],


	[ "meleeWeaponTimer[2]"             , "float32"                   , 0x64F4, CHAR_DANTE               ],
	[ "meleeWeaponTimer[5]"             , "float32"                   , 0x64F4, CHAR_VERGIL              ],
	[ "rangedWeaponTimer[3]"            , "float32"                   , 0x64FC, CHAR_DANTE               ],



	[ "meleeWeaponSwitchTimeout"        , "float32"                   , 0x6508, CHAR_DANTE               ],
	[ "rangedWeaponSwitchTimeout"       , "float32"                   , 0x650C, CHAR_DANTE               ],
	[ "meleeWeaponSwitchForwardTimeout" , "float32"                   , 0x6508, CHAR_VERGIL              ],
	[ "meleeWeaponSwitchBackwardTimeout", "float32"                   , 0x650C, CHAR_VERGIL              ],




	[ "styleRank"                       , "uint8"                     , 0x6510                           ],
	[ "styleMeter"                      , "float32"                   , 0x6514                           ],
	[ "inputData[58]"                   , "INPUT_DATA"                , 0x6674                           ],
	[ "collisionIndex"                  , "uint32"                    , 0x7254                           ],
	[ "interactionData[8]"              , "vec4"                      , 0x7460                           ],
	[ "buttons[4]"                      , "byte16"                    , 0x74E0                           ],
	[ "rightStickPosition"              , "uint16"                    , 0x74F8                           ],
	[ "rightStickRadius"                , "uint16"                    , 0x74FA                           ],
	[ "leftStickPosition"               , "uint16"                    , 0x7508                           ],
	[ "leftStickRadius"                 , "uint16"                    , 0x750A                           ],
	[ "actorCameraDirection"            , "uint16"                    , 0x750C                           ],
	[ "leftStickDirection[2]"           , "uint32"                    , 0x751C                           ],
	[ "devilModelMetadata"              , "DEVIL_MODEL_METADATA_DANTE", 0xB600, CHAR_DANTE               ],
	[ "modelMetadata[6]"                , "MODEL_METADATA"            , 0xB630, CHAR_DANTE               ],
	[ "modelMetadata[6]"                , "MODEL_METADATA"            , 0xB640, CHAR_VERGIL              ],
	[ "artemisChargeValue[2]"           , "float32"                   , 0xB868, CHAR_DANTE               ],
	[ "artemisChargeFlags[2]"           , "byte32"                    , 0xB87C, CHAR_DANTE               ],
];

var extra =
[
	[ "newCharacterModel"     , "uint8"   ],
	[ "newParentBaseAddr"     , "byte8 *" ],
	[ "newChildBaseAddr[4]"   , "byte8 *" ],
	[ "newGamepad"            , "uint8"   ],
	[ "newButtonMask"         , "byte16"  ],
	[ "newEnableLeftStick"    , "bool"    ],
	//[ "newStyle"              , "uint8"   ],
	[ "newStyleMap[5][2]"     , "uint8"   ],

	[ "newMeleeWeaponMap[5]"  , "uint8"   ],
	[ "newMeleeWeaponData[5]" , "byte8 *" ],
	//[ "newMeleeWeaponCount"   , "uint8"   ],
	[ "newMeleeWeaponIndex"   , "uint8"   ],

	[ "newRangedWeaponMap[5]" , "uint8"   ],
	[ "newRangedWeaponData[5]", "byte8 *" ],
	//[ "newRangedWeaponCount"  , "uint8"   ],
	[ "newRangedWeaponIndex"  , "uint8"   ],



	
	[ "newSect[8]"            , "bool"    ],
	// [ "newSkipPositionUpdate" , "bool"    ],
	// [ "newEnableMotion"       , "bool"    ],
	// [ "newEnablePermissionUpdate"       , "bool"    ],
	// [ "newIsLeader"       , "bool"    ],
	[ "newBufferedActionPolicy"       , "uint8"    ],
	//[ "newEnablePositionUpdate"       , "bool"    ],

];

var c = "";
var c_assert = "";
var pos = 0;

var fs = require("fs");

var lz = function(n)
{
	var str = "";
	if (n < 1000)
	{
		str = "0";
	}
	if (n < 100)
	{
		str = "00";
	}
	if (n < 10)
	{
		str = "000";
	}
	return str + n;
}

var GetTypeSize = function(str)
{
	var sizes =
	[
		[ "int8"                      , 1    ],
		[ "int16"                     , 2    ],
		[ "int32"                     , 4    ],
		[ "int64"                     , 8    ],
		[ "uint8"                     , 1    ],
		[ "uint16"                    , 2    ],
		[ "uint32"                    , 4    ],
		[ "uint64"                    , 8    ],
		[ "byte8"                     , 1    ],
		[ "byte16"                    , 2    ],
		[ "byte32"                    , 4    ],
		[ "byte64"                    , 8    ],
		[ "byte8 *"                   , 8    ],
		[ "bool"                      , 1    ],
		[ "float32"                   , 4    ],
		[ "vec4"                      , 16   ],
		[ "INPUT_DATA"                , 12   ],
		[ "MOTION_DATA"               , 2    ],
		[ "MODEL_METADATA"            , 80   ],
		[ "MODEL_DATA"                , 1920 ],
		[ "DEVIL_MODEL_METADATA_DANTE", 33   ],
	];
	for (var index = 0; index < sizes.length; index++)
	{
		var name = sizes[index][0];
		var size = sizes[index][1];
		if (name == str)
		{
			return size;
		}
	}
	return 0;
}

var Align = function(boundary)
{
	var remainder = (pos % boundary);
	if (remainder)
	{
		var size = (boundary - remainder);
		pos += size;
	}
}

// Cpp

c += "#pragma once\r\n";
c += "#include \"../Core/Core.h\"\r\n";
c += "\r\n";
c += "#include \"Vars.h\"\r\n";
c += "\r\n";
c += "#define _Merge(a, b) a##b\r\n";
c += "#define Merge(a, b) _Merge(a, b)\r\n";
c += "\r\n";
c += "#define _(size) struct { byte8 Merge(padding, __LINE__)[size]; }\r\n";
c += "\r\n";
c += "#pragma pack(push, 1)\r\n";
c += "\r\n";

c_assert += "#include \"ActorData.h\"\r\n";
c_assert += "\r\n";

function AddActorData
(
	structName,
	data,
	id,
	max
)
{
	for (var index = 0; index < data.length; index++)
	{
		var name      = data[index][0];
		var type      = data[index][1];
		var off       = data[index][2];
		var character = data[index][3];

		if (name == "")
		{
			name = "var_" + off.toString(16).toUpperCase();
		}
		else if (name.substring(0, 1) == "[")
		{
			name = "var_" + off.toString(16).toUpperCase() + name;
		}

		if ((max != undefined) && (pos >= max))
		{
			return;
		}

		if ((character != undefined) && !(character & id))
		{
			continue;
		}
		
		var lastPos = pos;
		
		if (off != undefined)
		{
			var diff = (off - pos);
			if (diff)
			{
				c += "\t_(" + diff.toString() + ");\r\n";
			}
			pos = off;
		}
		else
		{
			if (type.match(/\*/))
			{
				Align(8);
			}
			else if (name.match(/\[/))
			{
				Align(4);
			}
			var diff = (pos - lastPos);
			if (diff)
			{
				c += "\t_(" + diff.toString() + ");\r\n";
			}
		}
		
		c += "\t" + type + " " + name + "; // 0x" + pos.toString(16).toUpperCase() + "\r\n";
		
		c_assert += "static_assert(offsetof(" + structName + ", " + name.split("[")[0] + ") == 0x" + pos.toString(16).toUpperCase() + ");\r\n";
		
		var size = GetTypeSize(type);
		
		{
			var match = name.match(/\[\d+?\]/g);
			if (match)
			{
				for (var matchIndex = 0; matchIndex < match.length; matchIndex++)
				{
					var count = parseInt(match[matchIndex].match(/\[(\d+?)\]/)[1]);
					size *= count;
				}
			}
		}
		
		pos += size;
	}
}

function CreateActorData
(
	structName,
	id,
	max
)
{
	c += "struct " + structName + "\r\n";
	c += "{\r\n";
	
	pos = 0;
	
	AddActorData(structName, items, id, max);
	
	{
		var diff = (max - pos);
		if (diff)
		{
			c += "\t_(" + diff.toString() + ");\r\n";
		}
	}
	
	pos = max;
	
	AddActorData(structName, extra, id);

	c += "\r\n";
	c += "\toperator byte8 *()\r\n";
	c += "\t{\r\n";
	c += "\t\treturn reinterpret_cast<byte8 *>(this);\r\n";
	c += "\t}\r\n";

	c += "};\r\n";
}

CreateActorData("ACTOR_DATA", 0, ACTOR_DATA_SIZE_DANTE);

c_assert += "\r\n";
c += "\r\n";

CreateActorData("ACTOR_DATA_DANTE", CHAR_DANTE, ACTOR_DATA_SIZE_DANTE);

c_assert += "\r\n";
c += "\r\n";

CreateActorData("ACTOR_DATA_BOB", CHAR_BOB, ACTOR_DATA_SIZE_DANTE);

c_assert += "\r\n";
c += "\r\n";

CreateActorData("ACTOR_DATA_LADY", CHAR_LADY, ACTOR_DATA_SIZE_DANTE);

c_assert += "\r\n";
c += "\r\n";

CreateActorData("ACTOR_DATA_VERGIL", CHAR_VERGIL, ACTOR_DATA_SIZE_DANTE);

//c_assert += "\r\n";
c += "\r\n";

c += "#pragma pack(pop)\r\n";
c += "\r\n";
c += "#undef _\r\n";
c += "#undef Merge\r\n";
c += "#undef _Merge\r\n";

fs.writeFileSync("../Mary/ActorData.h", c);
fs.writeFileSync("../Mary/ActorData.cpp", c_assert);














// Cheat Engine

var GetShowAsHex = function(str)
{
	var dataTypes =
	[
		"byte8",
		"byte16",
		"byte32",
		"byte64",
		"byte8 *",
	];
	for (var index = 0; index < dataTypes.length; index++)
	{
		var type = dataTypes[index];
		if (str == type)
		{
			return true;
		}
	}
	return false;
}

var GetVariableType = function(str)
{
	var dataTypes =
	[
		[ "int8"   , "Byte"    ],
		[ "int16"  , "2 Bytes" ],
		[ "int32"  , "4 Bytes" ],
		[ "int64"  , "8 Bytes" ],
		[ "uint8"  , "Byte"    ],
		[ "uint16" , "2 Bytes" ],
		[ "uint32" , "4 Bytes" ],
		[ "uint64" , "8 Bytes" ],
		[ "byte8"  , "Byte"    ],
		[ "byte16" , "2 Bytes" ],
		[ "byte32" , "4 Bytes" ],
		[ "byte64" , "8 Bytes" ],
		[ "byte8 *", "8 Bytes" ],
		[ "bool"   , "Byte"    ],
		[ "float32", "Float"   ],
	];
	for (var index = 0; index < dataTypes.length; index++)
	{
		var cppType = dataTypes[index][0];
		var ceType  = dataTypes[index][1];
		if (str == cppType)
		{
			return ceType;
		}
	}
	return "";
}

// @Todo: Create general CreateCheatEntry function.

var AddCheatEntry = function
(
	description,
	hex,
	type,
	size,
	off,
	actor
)
{
	c += "<CheatEntry>\r\n";
	c += "<Description>\"" + description + "\"</Description>\r\n";
	if (hex)
	{
		c += "<ShowAsHex>1</ShowAsHex>\r\n";
	}
	c += "<VariableType>" + type + "</VariableType>\r\n";
	if (type == "Array of byte")
	{
		c += "<ByteLength>" + size + "</ByteLength>\r\n";
	}
	c += "<Address>Mary.Actor_actorBaseAddr+8+" + (actor * 8).toString(16).toUpperCase() + "</Address>\r\n";
	c += "<Offsets>\r\n";
	c += "<Offset>" + off.toString(16).toUpperCase() + "</Offset>\r\n";
	c += "</Offsets>\r\n";
	c += "</CheatEntry>\r\n";
}

function AddActorDataCE
(
	data,
	id,
	actor,
	max
)
{
	for (var index = 0; index < data.length; index++)
	{
		var name      = data[index][0];
		var type      = data[index][1];
		var off       = data[index][2];
		var character = data[index][3];

		if (name == "")
		{
			name = "var_" + off.toString(16).toUpperCase();
		}
		else if (name.substring(0, 1) == "[")
		{
			name = "var_" + off.toString(16).toUpperCase() + name;
		}

		if ((max != undefined) && (pos >= max))
		{
			return;
		}

		if ((character != undefined) && (character != id))
		{
			continue;
		}
		
		if (off != undefined)
		{
			pos = off;
		}
		else
		{
			if (type.match(/\*/))
			{
				Align(8);
			}
			else if (name.match(/\[/))
			{
				Align(4);
			}
		}
		
		var count = 1;
		
		{
			var match = name.match(/\[\d+?\]/g);
			if (match)
			{
				for (var matchIndex = 0; matchIndex < match.length; matchIndex++)
				{
					count *= parseInt(match[matchIndex].match(/\[(\d+?)\]/)[1]);
				}
			}
		}
		
		var size = GetTypeSize(type);
		
		for (var entryIndex = 0; entryIndex < count; entryIndex++)
		{
			var description = name.split("[")[0];
			if (count > 1)
			{
				description += " " + lz(entryIndex);
			}
			
			if (type == "vec4")
			{
				AddCheatEntry(description + " x", false, "Float", 0, (pos + 0  ), actor);
				AddCheatEntry(description + " y", false, "Float", 0, (pos + 4  ), actor);
				AddCheatEntry(description + " z", false, "Float", 0, (pos + 8  ), actor);
				AddCheatEntry(description + " a", false, "Float", 0, (pos + 0xC), actor);
				continue;
			}
			else if (type == "INPUT_DATA")
			{
				continue;
			}
			else if (type == "MOTION_DATA")
			{
				AddCheatEntry(description + " index", false, "Byte", 0, (pos + 0), actor);
				AddCheatEntry(description + " group", false, "Byte", 0, (pos + 1), actor);
				pos += size;
				continue;
			}
			else if (type == "MODEL_METADATA")
			{
				continue;
			}
			else if (type == "MODEL_DATA")
			{
				AddCheatEntry(description + " duration1 lower body", false, "Float", 0, (pos + 0x554 + 0), actor);
				AddCheatEntry(description + " duration1 upper body", false, "Float", 0, (pos + 0x554 + 4), actor);
				AddCheatEntry(description + " duration2 lower body", false, "Float", 0, (pos + 0x594 + 0), actor);
				AddCheatEntry(description + " duration2 upper body", false, "Float", 0, (pos + 0x594 + 4), actor);
				AddCheatEntry(description + " timer lower body"    , false, "Float", 0, (pos + 0x6B4 + 0), actor);
				AddCheatEntry(description + " timer upper body"    , false, "Float", 0, (pos + 0x6B4 + 4), actor);
				pos += size;
				continue;
			}
			else if (type == "DEVIL_MODEL_METADATA_DANTE")
			{
				continue;
			}
			
			AddCheatEntry(description, GetShowAsHex(type), GetVariableType(type), 0, pos, actor);
			
			pos += size;
		}
	}
}

function CreateActorDataCE
(
	groupName,
	id,
	max
)
{
	c += "<CheatEntry>\r\n";
	c += "<Description>\"" + groupName + "\"</Description>\r\n";
	c += "<Options moHideChildren=\"1\"/>\r\n";
	c += "<GroupHeader>1</GroupHeader>\r\n";
	c += "<CheatEntries>\r\n";
	
	for (var actor = 0; actor < 4; actor++)
	{
		c += "<CheatEntry>\r\n";
		c += "<Description>\"" + lz(actor) + "\"</Description>\r\n";
		c += "<Options moHideChildren=\"1\"/>\r\n";
		c += "<GroupHeader>1</GroupHeader>\r\n";
		c += "<CheatEntries>\r\n";
		
		pos = 0;
		
		AddActorDataCE(items, id, actor, max);
		
		pos = max;
		
		AddActorDataCE(extra, id, actor);
		
		c += "</CheatEntries>\r\n";
		c += "</CheatEntry>\r\n";
	}
	
	c += "</CheatEntries>\r\n";
	c += "</CheatEntry>\r\n";
}

c = "";

c += "<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n";
c += "<CheatTable>\r\n";
c += "<CheatEntries>\r\n";

CreateActorDataCE("__DANTE__" , CHAR_DANTE , ACTOR_DATA_SIZE_DANTE );
CreateActorDataCE("__BOB__"   , CHAR_BOB   , ACTOR_DATA_SIZE_BOB   );
CreateActorDataCE("__LADY__"  , CHAR_LADY  , ACTOR_DATA_SIZE_LADY  );
CreateActorDataCE("__VERGIL__", CHAR_VERGIL, ACTOR_DATA_SIZE_VERGIL);

c += "</CheatEntries>\r\n";
c += "</CheatTable>\r\n";

fs.writeFileSync("actorData.txt", c);
