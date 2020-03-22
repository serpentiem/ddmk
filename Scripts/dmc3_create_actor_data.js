var items =
[
	[ "characterLogic"           , "uint8"       , 1 , 0x78   ],
	[ "position"                 , "vec4"        , 1 , 0x80   ],
	[ "direction"                , "uint16"      , 1 , 0xC0   ],
	[ "actorId"                  , "uint8"       , 1 , 0x118  ],
	[ "isDoppelganger"           , "bool"        , 1 , 0x11C  ],
	[ "visible"                  , "uint8"       , 1 , 0x120  ],
	[ "motionFile"               , "byte8 *"     , 32, 0x38A0 ],
	[ "motionData"               , "MOTION_DATA" , 5 , 0x39B0 ],
	[ "shadow"                   , "uint8"       , 1 , 0x3A18 ],
	[ "color"                    , "byte32"      , 1 , 0x3A28 ],
	[ "motionState1"             , "byte32"      , 4 , 0x3E00 ],
	[ "chargedShotAir"           , "uint16"      , 1 , 0x3E1A ],
	[ "chargedShot"              , "uint16"      , 1 , 0x3E22 ],
	[ "idleTimer"                , "float32"     , 1 , 0x3E38 ],
	[ "motionState2"             , "byte32"      , 3 , 0x3E60 ],
	[ "activeModel"              , "uint8"       , 1 , 0x3E6C ],
	[ "queuedModel"              , "uint8"       , 1 , 0x3E70 ],
	[ "modelIndex"               , "uint32"      , 3 , 0x3E74 ],
	[ "modelState"               , "uint8"       , 1 , 0x3E80 ],
	[ "lockOn"                   , "bool"        , 1 , 0x3E84 ],
	[ "modelIndexMirror"         , "uint8"       , 1 , 0x3E88 ],
	[ "devilState"               , "uint8"       , 1 , 0x3E94 ],
	[ "devil"                    , "bool"        , 1 , 0x3E9B ],
	[ "costume"                  , "uint8"       , 1 , 0x3E9E ],
	[ "specialCostume"           , "bool"        , 1 , 0x3E9F ],
	[ "magicPoints"              , "float32"     , 1 , 0x3EB8 ],
	[ "maxMagicPoints"           , "float32"     , 1 , 0x3EBC ],
	[ "move"                     , "uint8"       , 1 , 0x3FA4 ],
	[ "lastMove"                 , "uint8"       , 1 , 0x3FA5 ],
	[ "chainCount"               , "uint8"       , 1 , 0x3FAC ],
	[ "expertise"                , "byte32"      , 16, 0x3FEC ],
	[ "maxHitPoints"             , "float32"     , 1 , 0x40EC ],
	[ "hitPoints"                , "float32"     , 1 , 0x411C ],
	[ "targetBaseAddr"           , "byte8 *"     , 1 , 0x6328 ],
	[ "style"                    , "uint8"       , 1 , 0x6338 ],
	[ "styleLevel"               , "uint8"       , 1 , 0x6358 ],
	[ "dashCount"                , "uint8"       , 1 , 0x635C ],
	[ "skyStarCount"             , "uint8"       , 1 , 0x635D ],
	[ "airTrickCount"            , "uint8"       , 1 , 0x635E ],
	[ "trickUpCount"             , "uint8"       , 1 , 0x635F ],
	[ "trickDownCount"           , "uint8"       , 1 , 0x6360 ],
	[ "quicksilver"              , "bool"        , 1 , 0x6361 ],
	[ "doppelganger"             , "bool"        , 1 , 0x6362 ],
	[ "styleExperience"          , "float32"     , 1 , 0x6364 ],
	[ "controlLinkedActor"       , "bool"        , 1 , 0x6454 ],
	[ "linkedActorBaseAddr"      , "byte8 *"     , 1 , 0x6478 ],
	[ "selectedMeleeWeaponVergil", "uint8"       , 1 , 0x6488 ],
	[ "activeWeapon"             , "uint8"       , 1 , 0x648D ],
	[ "selectedMeleeWeapon"      , "uint8"       , 1 , 0x6490 ],
	[ "selectedRangedWeapon"     , "uint8"       , 1 , 0x6494 ],
	[ "equipment"                , "uint8"       , 4 , 0x6498 ],
	[ "weaponMetadata"           , "byte8 *"     , 4 , 0x64A0 ],
	[ "weaponFlags"              , "byte32"      , 4 , 0x64C8 ],
	[ "activeMeleeWeapon"        , "uint8"       , 1 , 0x64F0 ],
	[ "activeRangedWeapon"       , "uint8"       , 1 , 0x64F1 ],
	[ "weaponTimer"              , "float32"     , 4 , 0x64F4 ],
	[ "styleRank"                , "uint8"       , 1 , 0x6510 ],
	[ "styleMeter"               , "float32"     , 1 , 0x6514 ],
	[ "inputData"                , "INPUT_DATA"  , 58, 0x6674 ],
	[ "interactionData"          , "vec4"        , 8 , 0x7460 ],
	[ "buttonInput"              , "byte16"      , 4 , 0x74E0 ],
	[ "modelData"                , "MODEL_DATA"  , 6 , 0xB630 ],
	[ "artemisChargeValue"       , "float32"     , 2 , 0xB868 ],
	[ "artemisChargeFlags"       , "byte32"      , 2 , 0xB87C ],
	[ "isDefault"                , "bool"        , 1 , 0xB8C0 ],
	[ "character"                , "uint8"       , 1 , 0xB8C1 ],
	[ "noCollision"              , "bool"        , 1 , 0xB8C2 ],
	[ "hide"                     , "bool"        , 1 , 0xB8C3 ],
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
		[ "uint8"       , 1  ],
		[ "uint16"      , 2  ],
		[ "uint32"      , 4  ],
		[ "uint64"      , 8  ],
		[ "byte8"       , 1  ],
		[ "byte16"      , 2  ],
		[ "byte32"      , 4  ],
		[ "byte64"      , 8  ],
		[ "byte8 *"     , 8  ],
		[ "bool"        , 1  ],
		[ "float32"     , 4  ],
		[ "vec4"        , 16 ],
		[ "INPUT_DATA"  , 12 ],
		[ "MOTION_DATA" , 2  ],
		[ "MODEL_DATA"  , 80 ],
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

var AddCheatEntry = function
(
	description,
	hex,
	type,
	size,
	off,
	actor,
	systemActor
)
{
	c += "<CheatEntry>\n";
	c += "<Description>\"" + description + "\"</Description>\n";
	if (hex)
	{
		c += "<ShowAsHex>1</ShowAsHex>\n";
	}
	c += "<VariableType>" + type + "</VariableType>\n";
	if (type == "Array of byte")
	{
		c += "<ByteLength>" + size + "</ByteLength>\n";
	}
	if (systemActor)
	{
		c += "<Address>Mary.System_Actor_actorBaseAddr+" + (actor * 8).toString(16).toUpperCase() + "</Address>\n";
	}
	else
	{
		c += "<Address>dmc3.exe+C90E28</Address>\n"
	}
	c += "<Offsets>\n";
	c += "<Offset>" + off.toString(16).toUpperCase() + "</Offset>\n";
	if (!systemActor)
	{
		c += "<Offset>" + (0x18 + (actor * 8)).toString(16).toUpperCase() + "</Offset>\n";
	}
	c += "</Offsets>\n";
	c += "</CheatEntry>\n";
}

var CreateData = function
(
	groupName,
	actorCount,
	systemActor
)
{
	c += "<CheatEntry>\n";
	c += "<Description>\"" + groupName + "\"</Description>\n";
	c += "<Options moHideChildren=\"1\"/>\n";
	c += "<GroupHeader>1</GroupHeader>\n";
	c += "<CheatEntries>\n";

	for (var actor = 0; actor < actorCount; actor++)
	{
		c += "<CheatEntry>\n";
		c += "<Description>\"" + lz(actor) + "\"</Description>\n";
		c += "<Options moHideChildren=\"1\"/>\n";
		c += "<GroupHeader>1</GroupHeader>\n";
		c += "<CheatEntries>\n";
		
		for (var itemIndex = 0; itemIndex < items.length; itemIndex++)
		{
			var name   = items[itemIndex][0];
			var type   = items[itemIndex][1];
			var count  = items[itemIndex][2];
			var _off   = items[itemIndex][3];
			
			for (var index = 0; index < count; index++)
			{
				var description = name;
				if (count > 1)
				{
					description = name + " " + lz(index);
				}
				var off = (_off + (index * GetTypeSize(type)));
				
				if (type == "vec4")
				{
					AddCheatEntry(description + " x", false, "Float", 0, (off + 0  ), actor, systemActor);
					AddCheatEntry(description + " y", false, "Float", 0, (off + 4  ), actor, systemActor);
					AddCheatEntry(description + " z", false, "Float", 0, (off + 8  ), actor, systemActor);
					AddCheatEntry(description + " a", false, "Float", 0, (off + 0xC), actor, systemActor);
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
				else if (type == "MODEL_DATA")
				{
					continue;
				}
				
				AddCheatEntry(description, GetShowAsHex(type), GetVariableType(type), 0, off, actor, systemActor);
			}
		}
		c += "</CheatEntries>\n";
		c += "</CheatEntry>\n";
	}

	c += "</CheatEntries>\n";
	c += "</CheatEntry>\n";
}

// Cpp

c += "#define _(size) struct { byte8 padding[size]; }\n";
c += "\n";
c += "#pragma pack(push, 1)\n";
c += "\n";
c += "struct ACTOR_DATA\n";
c += "{\n";

for (var index = 0; index < items.length; index++)
{
	var name  = items[index][0];
	var type  = items[index][1];
	var count = items[index][2];
	var off   = items[index][3];
	
	var diff = (off - pos);
	
	var size = (GetTypeSize(type) * count);
	
	if (diff)
	{
		c += "\t_(" + diff.toString() + ");\n";
		pos += diff;
	}
	
	c += "\t" + type + " " + name;
	if (count > 1)
	{
		c += "[" + count.toString() + "]";
	}
	c += "; // 0x" + off.toString(16).toUpperCase() + "\n";
	
	c_assert += "static_assert(offsetof(ACTOR_DATA, " + name + ") == 0x" + off.toString(16).toUpperCase() + ");\n";
	
	pos += size;
}

console.log("pos 0x" + pos.toString(16).toUpperCase());

c += "};\n";
c += "\n";
c += "#pragma pack(pop)\n";
c += "\n";
c += "#undef _\n";

fs.writeFileSync("actorData.cpp", c + "\n" + c_assert);

// Cheat Engine

c = "";

c += "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
c += "<CheatTable>\n";
c += "<CheatEntries>\n";

CreateData("__LIVE__"                  , 2, false);
CreateData("System_Actor_actorBaseAddr", 4, true );

c += "</CheatEntries>\n";
c += "</CheatTable>\n";

fs.writeFileSync("actorData.txt", c);
