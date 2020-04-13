const CHAR_DANTE  = 0;
const CHAR_VERGIL = 3;

const ACTOR_DATA_SIZE = 0xB8C0;

var items =
[
	[ "init"                     , "bool"                      , 8                   ],
	[ "character"                , "uint32"                    , 0x78                ],
	[ "position"                 , "vec4"                      , 0x80                ],
	[ "direction"                , "uint16"                    , 0xC0                ],
	[ "id"                       , "uint8"                     , 0x118               ],
	[ "isClone"                  , "bool"                      , 0x11C               ], // @Research: Pretty much just a bool, but has size of uint32.
	[ "visible"                  , "uint32"                    , 0x120               ],
	[ "modelData[3]"             , "MODEL_DATA"                , 0x200               ],
	[ "motionArchive[32]"        , "byte8 *"                   , 0x38A0              ],
	[ "motionData[5]"            , "MOTION_DATA"               , 0x39B0              ],
	[ "shadow"                   , "uint32"                    , 0x3A18              ],
	[ "color"                    , "byte32"                    , 0x3A28              ],
	[ "actionData[6]"            , "byte8 *"                   , 0x3DD0              ],
	[ "motionState1[6]"          , "byte32"                    , 0x3E00              ],
	[ "chargedShotAir"           , "uint16"                    , 0x3E1A, CHAR_DANTE  ],
	[ "chargedShot"              , "uint16"                    , 0x3E22, CHAR_DANTE  ],
	[ "motionTimer"              , "float32"                   , 0x3E34              ],
	[ "idleTimer"                , "float32"                   , 0x3E38              ],
	[ "motionState2[3]"          , "byte32"                    , 0x3E60              ],
	[ "activeModelIndex"         , "uint32"                    , 0x3E6C              ],
	[ "queuedModelIndex"         , "uint32"                    , 0x3E70              ],
	[ "modelMap[3]"              , "uint32"                    , 0x3E74              ],
	[ "modelState"               , "uint8"                     , 0x3E80              ],
	[ "lockOn"                   , "bool"                      , 0x3E84              ],
	[ "activeModelIndexMirror"   , "uint32"                    , 0x3E88              ],
	[ "activeDevilModel"         , "uint32"                    , 0x3E8C              ],
	[ "devilState"               , "uint8"                     , 0x3E94              ],
	[ "devil"                    , "bool"                      , 0x3E9B              ],
	[ "costume"                  , "uint8"                     , 0x3E9E              ],
	[ "sparda"                   , "bool"                      , 0x3E9F              ], // @Research: Nero Angelo for Vergil.
	[ "magicPoints"              , "float32"                   , 0x3EB8              ],
	[ "maxMagicPoints"           , "float32"                   , 0x3EBC              ],
	[ "cameraDirection"          , "uint16"                    , 0x3ED8              ],
	[ "move"                     , "uint8"                     , 0x3FA4              ],
	[ "lastMove"                 , "uint8"                     , 0x3FA5              ],
	[ "chainCount"               , "uint8"                     , 0x3FAC              ],
	[ "expertise[16]"            , "byte32"                    , 0x3FEC              ],
	[ "maxHitPoints"             , "float32"                   , 0x40EC              ],
	[ "hitPoints"                , "float32"                   , 0x411C              ],
	[ "targetBaseAddr"           , "byte8 *"                   , 0x6328              ],
	[ "style"                    , "uint32"                    , 0x6338              ],
	[ "styleLevel"               , "uint32"                    , 0x6358              ],
	[ "dashCount"                , "uint8"                     , 0x635C, CHAR_DANTE  ],
	[ "skyStarCount"             , "uint8"                     , 0x635D, CHAR_DANTE  ],
	[ "airTrickCount"            , "uint8"                     , 0x635E              ],
	[ "trickUpCount"             , "uint8"                     , 0x635F, CHAR_VERGIL ],
	[ "trickDownCount"           , "uint8"                     , 0x6360, CHAR_VERGIL ],
	[ "quicksilver"              , "bool"                      , 0x6361, CHAR_DANTE  ],
	[ "doppelganger"             , "bool"                      , 0x6362, CHAR_DANTE  ],
	[ "styleExperience"          , "float32"                   , 0x6364              ],
	[ "cloneIsActive"            , "bool"                      , 0x6454, CHAR_DANTE  ],
	[ "cloneBaseAddr"            , "byte8 *"                   , 0x6478, CHAR_DANTE  ],
	[ "cloneIsControlledByPlayer", "bool"                      , 0x6480, CHAR_DANTE  ],
	[ "weaponIndex[2]"           , "uint32"                    , 0x6484, CHAR_VERGIL ],
	[ "activeWeapon"             , "uint8"                     , 0x648D, CHAR_DANTE  ],
	[ "weaponIndex[2]"           , "uint32"                    , 0x6490, CHAR_DANTE  ],
	[ "weaponMap[5]"             , "uint8"                     , 0x6498              ],
	[ "weaponData[5]"            , "byte8 *"                   , 0x64A0              ],
	[ "weaponFlags[5]"           , "byte32"                    , 0x64C8              ],
	[ "weaponTimer[5]"           , "float32"                   , 0x64F4              ],
	[ "weaponSwitchTimeout[2]"   , "float32"                   , 0x6508              ],
	[ "styleRank"                , "uint8"                     , 0x6510              ],
	[ "styleMeter"               , "float32"                   , 0x6514              ],
	[ "inputData[58]"            , "INPUT_DATA"                , 0x6674              ],
	[ "collisionIndex"           , "uint32"                    , 0x7254              ],
	[ "interactionData[8]"       , "vec4"                      , 0x7460              ],
	[ "buttons[4]"               , "byte16"                    , 0x74E0              ],
	[ "rightStick[2]"            , "byte16"                    , 0x74F8              ],
	[ "leftStick[2]"             , "byte16"                    , 0x7508              ],
	[ "actorCameraDirection"     , "uint16"                    , 0x750C              ],
	[ "leftStickDirection[2]"    , "uint32"                    , 0x751C              ],
	[ "devilModelMetadata"       , "DEVIL_MODEL_METADATA_DANTE", 0xB600, CHAR_DANTE  ],
	[ "modelMetadata[6]"         , "MODEL_METADATA"            , 0xB630, CHAR_DANTE  ],
	[ "modelMetadata[6]"         , "MODEL_METADATA"            , 0xB640, CHAR_VERGIL ],
	[ "artemisChargeValue[2]"    , "float32"                   , 0xB868, CHAR_DANTE  ],
	[ "artemisChargeFlags[2]"    , "byte32"                    , 0xB87C, CHAR_DANTE  ],
];

var extra =
[
	[ "characterModel"        , "uint8"   ],
	[ "parentBaseAddr"        , "byte8 *" ],
	[ "childBaseAddr[4]"      , "byte8 *" ],
	[ "gamepad"               , "uint8"   ],
	[ "buttonMask"            , "byte16"  ],
	[ "copyPosition"          , "bool"    ],
	[ "newStyle"              , "uint8"   ],
	[ "newStyleMap[5][2]"     , "uint8"   ],
	[ "newMeleeWeaponMap[5]"  , "uint8"   ],
	[ "newMeleeWeaponData[5]" , "byte8 *" ],
	[ "newMeleeWeaponCount"   , "uint8"   ],
	[ "newMeleeWeaponIndex"   , "uint8"   ],
	[ "newRangedWeaponMap[5]" , "uint8"   ],
	[ "newRangedWeaponData[5]", "byte8 *" ],
	[ "newRangedWeaponCount"  , "uint8"   ],
	[ "newRangedWeaponIndex"  , "uint8"   ],
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

// c += "struct ACTOR_DATA_BASE;\r\n";
// c += "struct ACTOR_DATA_CHAR_VOID;\r\n";
// c += "struct ACTOR_DATA_CHAR_DANTE;\r\n";
// c += "struct ACTOR_DATA_CHAR_VERGIL;\r\n";
// c += "struct ACTOR_DATA_EXTRA;\r\n";

//c += "struct ACTOR_DATA;\r\n";
c += "struct ACTOR_DATA_DANTE;\r\n";
c += "struct ACTOR_DATA_VERGIL;\r\n";
c += "\r\n";

// c += "#define _(size) struct { byte8 padding[size]; }\n";
// c += "\n";
// c += "#pragma pack(push, 1)\n";
// c += "\n";
// c += "struct ACTOR_DATA_BASE\r\n";
// c += "{\r\n";

// pos = 0;

// for (var index = 0; index < base.length; index++)
// {
// 	var name = base[index][0];
// 	var type = base[index][1];
// 	var off  = base[index][2];
	
// 	{
// 		var diff = (off - pos);
// 		if (diff)
// 		{
// 			c += "\t_(" + diff.toString() + ");\r\n";
// 			pos += diff;
// 		}
// 	}
	
// 	c += "\t" + type + " " + name + "; // 0x" + off.toString(16).toUpperCase() + "\r\n";
	
// 	//c_assert += "static_assert(offsetof(ACTOR_DATA_BASE, " + name + ") == 0x" + off + ");\r\n";
// 	c_assert += "static_assert(offsetof(ACTOR_DATA_BASE, " + name.split("[")[0] + ") == 0x" + pos.toString(16).toUpperCase() + ");\r\n";
	
	
	
// 	var size = GetTypeSize(type);
	
// 	{
// 		var match = name.match(/\[\d+?\]/g);
// 		if (match)
// 		{
// 			for (var matchIndex = 0; matchIndex < match.length; matchIndex++)
// 			{
// 				var count = parseInt(match[matchIndex].match(/\[(\d+?)\]/)[1]);
// 				size *= count;
// 			}
// 		}
// 	}
	
// 	pos += size;
// }

// {
// 	var diff = (512 - pos);
// 	if (diff)
// 	{
// 		c += "\t_(" + diff.toString() + ");\r\n";
// 	}
// }

// c += "};\r\n";

// c += "\r\n";
// c_assert += "\r\n";

// c += "struct ACTOR_DATA_CHAR_VOID\r\n";
// c += "{\r\n";

// pos = 512;

// {
// 	var diff = (ACTOR_DATA_SIZE - pos);
// 	if (diff)
// 	{
// 		c += "\t_(" + diff.toString() + ");\r\n";
// 	}
// }

// c += "};\r\n";

// c += "\r\n";









function AddActorData
(
	structName,
	data,
	id
)
{
	for (var index = 0; index < data.length; index++)
	{
		var name      = data[index][0];
		var type      = data[index][1];
		var off       = data[index][2];
		var character = data[index][3];
		
		if ((character != undefined) && (character != id))
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
	id
)
{
	c += "struct " + structName + "\r\n";
	c += "{\r\n";
	
	pos = 0;
	
	AddActorData(structName, items, id);
	
	{
		var diff = (ACTOR_DATA_SIZE - pos);
		if (diff)
		{
			c += "\t_(" + diff.toString() + ");\r\n";
		}
	}
	
	pos = ACTOR_DATA_SIZE;
	
	AddActorData(structName, extra, id);
	
	c += "};\r\n";
}

CreateActorData("ACTOR_DATA_DANTE", CHAR_DANTE);

c = c.substring(0, (c.length - 4));



//c += "\r\n";
//c += "struct ACTOR_DATA : ACTOR_DATA_BASE, ACTOR_DATA_CHAR_VOID, ACTOR_DATA_EXTRA\r\n";
//c += "struct ACTOR_DATA\r\n";
//c += "{\r\n";


c += "\r\n";
c += "\toperator ACTOR_DATA_VERGIL &()\r\n";
c += "\t{\r\n";
c += "\t\treturn *reinterpret_cast<ACTOR_DATA_VERGIL *>(this);\r\n";
c += "\t}\r\n";

c += "};\r\n";




c_assert += "\r\n";
c += "\r\n";











CreateActorData("ACTOR_DATA_VERGIL", CHAR_VERGIL);


c = c.substring(0, (c.length - 4));


c += "\r\n";
c += "\toperator ACTOR_DATA_DANTE &()\r\n";
c += "\t{\r\n";
c += "\t\treturn *reinterpret_cast<ACTOR_DATA_DANTE *>(this);\r\n";
c += "\t}\r\n";

c += "};\r\n";

c += "\r\n";

c += "typedef ACTOR_DATA_DANTE ACTOR_DATA;\r\n";

//c += "\r\n";




















// c += "};\r\n";

// c += "\r\n";
// c_assert += "\r\n";

// c += "struct ACTOR_DATA_CHAR_VERGIL\r\n";
// c += "{\r\n";

// pos = 0;

// for (var index = 0; index < char.length; index++)
// {
// 	var name      = char[index][0];
// 	var type      = char[index][1];
// 	var off       = char[index][2];
// 	var character = char[index][3];
	
// 	if ((character != undefined) && (character != CHAR_VERGIL))
// 	{
// 		continue;
// 	}
	
// 	{
// 		var diff = (off - pos);
// 		if (diff)
// 		{
// 			c += "\t_(" + diff.toString() + ");\r\n";
// 			pos += diff;
// 		}
// 	}
	
// 	c += "\t" + type + " " + name + "; // 0x" + off.toString(16).toUpperCase() + "\r\n";
	
// 	//c_assert += "static_assert(offsetof(ACTOR_DATA_CHAR_VERGIL, " + name + ") == 0x" + off + ");\r\n";
// 	c_assert += "static_assert(offsetof(ACTOR_DATA_VERGIL, " + name.split("[")[0] + ") == 0x" + pos.toString(16).toUpperCase() + ");\r\n";
	
// 	var size = GetTypeSize(type);
	
// 	{
// 		var match = name.match(/\[\d+?\]/g);
// 		if (match)
// 		{
// 			for (var matchIndex = 0; matchIndex < match.length; matchIndex++)
// 			{
// 				var count = parseInt(match[matchIndex].match(/\[(\d+?)\]/)[1]);
// 				size *= count;
// 			}
// 		}
// 	}
	
// 	pos += size;
// }

// {
// 	var diff = (ACTOR_DATA_SIZE - pos);
// 	if (diff)
// 	{
// 		c += "\t_(" + diff.toString() + ");\r\n";
// 	}
// }

// c += "};\r\n";
// c_assert += "\r\n";





// c += "struct ACTOR_DATA_EXTRA\r\n";
// c += "{\r\n";

// pos = 0;

// for (var index = 0; index < extra.length; index++)
// {
// 	var name = extra[index][0];
// 	var type = extra[index][1];

// 	var size = GetTypeSize(type);

// 	{
// 		var match = name.match(/\[\d+?\]/g);
// 		if (match)
// 		{
// 			for (var matchIndex = 0; matchIndex < match.length; matchIndex++)
// 			{
// 				var count = parseInt(match[matchIndex].match(/\[(\d+?)\]/)[1]);
// 				size *= count;
// 			}
// 		}
// 	}

// 	{
// 		var lastPos = pos;

// 		if (name.match(/\[/))
// 		{
// 			Align(4);
// 		}
// 		if (type.match(/\*/))
// 		{
// 			Align(8);
// 		}

// 		var diff = (pos - lastPos);
// 		if (diff)
// 		{
// 			c += "\t_(" + diff.toString() + ");\r\n";
// 		}
// 	}

// 	c += "\t" + type + " " + name + "; // 0x" + pos.toString(16).toUpperCase() + "\r\n";

// 	//c_assert += "static_assert(offsetof(ACTOR_DATA_EXTRA, " + name.split("[")[0] + ") == 0x" + pos.toString(16).toUpperCase() + ");\r\n";
// 	c_assert += "static_assert(offsetof(ACTOR_DATA_EXTRA, " + name.split("[")[0] + ") == 0x" + pos.toString(16).toUpperCase() + ");\r\n";

// 	pos += size;
// }

// c += "};\r\n";

// c += "\r\n";
// c_assert += "\r\n";












//c += "#pragma pack(pop)\r\n";
//c += "\r\n";
//c += "#undef _\r\n";

// c += "\r\n";
// //c += "struct ACTOR_DATA : ACTOR_DATA_BASE, ACTOR_DATA_CHAR_VOID, ACTOR_DATA_EXTRA\r\n";
// c += "struct ACTOR_DATA\r\n";
// c += "{\r\n";
// c += "\toperator ACTOR_DATA_DANTE &()\r\n";
// c += "\t{\r\n";
// c += "\t\treturn *reinterpret_cast<ACTOR_DATA_DANTE *>(this);\r\n";
// c += "\t}\r\n";
// c += "\r\n";
// c += "\toperator ACTOR_DATA_VERGIL &()\r\n";
// c += "\t{\r\n";
// c += "\t\treturn *reinterpret_cast<ACTOR_DATA_VERGIL *>(this);\r\n";
// c += "\t}\r\n";
// c += "};\r\n";

// c += "\r\n";

// //c += "struct ACTOR_DATA_DANTE : ACTOR_DATA_BASE, ACTOR_DATA_CHAR_DANTE, ACTOR_DATA_EXTRA\r\n";
// c += "struct ACTOR_DATA_DANTE\r\n";
// c += "{\r\n";
// c += "\toperator ACTOR_DATA &()\r\n";
// c += "\t{\r\n";
// c += "\t\treturn *reinterpret_cast<ACTOR_DATA *>(this);\r\n";
// c += "\t}\r\n";
// c += "};\r\n";

// c += "\r\n";

// //c += "struct ACTOR_DATA_VERGIL : ACTOR_DATA_BASE, ACTOR_DATA_CHAR_VERGIL, ACTOR_DATA_EXTRA\r\n";
// c += "struct ACTOR_DATA_VERGIL\r\n";
// c += "{\r\n";
// c += "\toperator ACTOR_DATA &()\r\n";
// c += "\t{\r\n";
// c += "\t\treturn *reinterpret_cast<ACTOR_DATA *>(this);\r\n";
// c += "\t}\r\n";
// c += "};\r\n";

//c += "\r\n";

//c_assert += "static_assert((sizeof(ACTOR_DATA_BASE) + sizeof(ACTOR_DATA_CHAR_VOID)) == 0xB8C0);\r\n";
//c_assert += "static_assert((sizeof(ACTOR_DATA_BASE) + sizeof(ACTOR_DATA_CHAR_DANTE)) == 0xB8C0);\r\n";
//c_assert += "static_assert((sizeof(ACTOR_DATA_BASE) + sizeof(ACTOR_DATA_CHAR_VERGIL)) == 0xB8C0);\r\n";

fs.writeFileSync("actorData.cpp", c + "\r\n" + c_assert);





















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
	c += "<Address>Mary.System_Actor_actorBaseAddr+8+" + (actor * 8).toString(16).toUpperCase() + "</Address>\r\n";
	c += "<Offsets>\r\n";
	c += "<Offset>" + off.toString(16).toUpperCase() + "</Offset>\r\n";
	c += "</Offsets>\r\n";
	c += "</CheatEntry>\r\n";
}

function AddActorDataCE
(
	data,
	id,
	actor
)
{
	for (var index = 0; index < data.length; index++)
	{
		var name      = data[index][0];
		var type      = data[index][1];
		var off       = data[index][2];
		var character = data[index][3];
		
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
				continue;
			}
			else if (type == "MODEL_METADATA")
			{
				continue;
			}
			else if (type == "MODEL_DATA")
			{
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
	id
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
		
		AddActorDataCE(items, id, actor);
		
		pos = ACTOR_DATA_SIZE;
		
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

CreateActorDataCE("__DANTE__", CHAR_DANTE);
CreateActorDataCE("__VERGIL__", CHAR_VERGIL);

c += "</CheatEntries>\r\n";
c += "</CheatTable>\r\n";

fs.writeFileSync("actorData.txt", c);
