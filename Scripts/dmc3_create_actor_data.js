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

var GetByteSize = function(str)
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
		[ "INPUT_BUFFER", 12 ],
		[ "MOTION_DATA" , 2  ],
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

var items =
[
	[ "character"                , "uint8"       , 1 , 0x78   ],
	[ "x"                        , "float32"     , 1 , 0x80   ],
	[ "y"                        , "float32"     , 1 , 0x84   ],
	[ "z"                        , "float32"     , 1 , 0x88   ],
	[ "direction"                , "uint16"      , 1 , 0xC0   ],
	[ "actor"                    , "uint8"       , 1 , 0x118  ],
	[ "isDoppelganger"           , "bool"        , 1 , 0x11C  ],
	[ "visible"                  , "uint8"       , 1 , 0x120  ],
	[ "motionArchive"            , "byte8 *"     , 32, 0x38A0 ],
	[ "motionData"               , "MOTION_DATA" , 5 , 0x39B0 ],
	[ "shadow"                   , "uint8"       , 1 , 0x3A18 ],
	[ "color"                    , "byte32"      , 1 , 0x3A28 ],
	[ "motionState1"             , "byte32"      , 4 , 0x3E00 ],
	[ "motionState2"             , "byte32"      , 3 , 0x3E60 ],
	[ "baseModel"                , "uint8"       , 1 , 0x3E6C ],
	[ "baseModelMirror1"         , "uint8"       , 1 , 0x3E70 ],
	[ "baseModelMirror2"         , "uint8"       , 1 , 0x3E88 ],
	[ "devil"                    , "bool"        , 1 , 0x3E9B ],
	[ "costume"                  , "uint8"       , 1 , 0x3E9E ],
	[ "specialCostume"           , "bool"        , 1 , 0x3E9F ],
	[ "magicPoints"              , "float32"     , 1 , 0x3EB8 ],
	[ "maxMagicPoints"           , "float32"     , 1 , 0x3EBC ],
	[ "move"                     , "uint8"       , 1 , 0x3FA4 ],
	[ "lastMove"                 , "uint8"       , 1 , 0x3FA5 ],
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
	[ "inputBuffer"              , "INPUT_BUFFER", 58, 0x6674 ],
	[ "buttonInput"              , "byte16"      , 4 , 0x74E0 ],
];

var c = "";
var c_assert = "";
var pos = 0;

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
	
	var size = (GetByteSize(type) * count);
	
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

c += "};\n";
c += "\n";
c += "#pragma pack(pop)\n";
c += "\n";
c += "#undef _\n";

document.body.innerHTML = "<plaintext>" + c + "\n" + c_assert;
