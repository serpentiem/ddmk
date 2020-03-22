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


































// // var items =
// // [
	// // [ "characterlogic"           , "uint8"       , 1 , 0x78   ],
	// // [ "position"                 , "vec4"        , 1 , 0x80   ],
	// // [ "direction"                , "uint16"      , 1 , 0xc0   ],
	// // [ "actorid"                  , "uint8"       , 1 , 0x118  ],
	// // [ "isdoppelganger"           , "bool"        , 1 , 0x11c  ],
	// // [ "visible"                  , "uint8"       , 1 , 0x120  ],
	// // [ "motionfile"               , "byte8 *"     , 32, 0x38a0 ],
	// // [ "motiondata"               , "motion_data" , 5 , 0x39b0 ],
	// // [ "shadow"                   , "uint8"       , 1 , 0x3a18 ],
	// // [ "color"                    , "byte32"      , 1 , 0x3a28 ],
	// // [ "motionstate1"             , "byte32"      , 4 , 0x3e00 ],
	// // [ "chargedshotair"           , "uint16"      , 1 , 0x3e1a ],
	// // [ "chargedshot"              , "uint16"      , 1 , 0x3e22 ],
	// // [ "idletimer"                , "float32"     , 1 , 0x3e38 ],
	// // [ "motionstate2"             , "byte32"      , 3 , 0x3e60 ],
	// // [ "activemodel"              , "uint8"       , 1 , 0x3e6c ],
	// // [ "queuedmodel"              , "uint8"       , 1 , 0x3e70 ],
	// // [ "modelindex"               , "uint8"       , 3 , 0x3e74 ],
	// // [ "modelstate"               , "uint8"       , 1 , 0x3e80 ],
	// // [ "lockon"                   , "bool"        , 1 , 0x3e84 ],
	// // [ "modelindexmirror"         , "uint8"       , 1 , 0x3e88 ],
	// // [ "devilstate"               , "uint8"       , 1 , 0x3e94 ],
	// // [ "devil"                    , "bool"        , 1 , 0x3e9b ],
	// // [ "costume"                  , "uint8"       , 1 , 0x3e9e ],
	// // [ "specialcostume"           , "bool"        , 1 , 0x3e9f ],
	// // [ "magicpoints"              , "float32"     , 1 , 0x3eb8 ],
	// // [ "maxmagicpoints"           , "float32"     , 1 , 0x3ebc ],
	// // [ "move"                     , "uint8"       , 1 , 0x3fa4 ],
	// // [ "lastmove"                 , "uint8"       , 1 , 0x3fa5 ],
	// // [ "chaincount"               , "uint8"       , 1 , 0x3fac ],
	// // [ "expertise"                , "byte32"      , 16, 0x3fec ],
	// // [ "maxhitpoints"             , "float32"     , 1 , 0x40ec ],
	// // [ "hitpoints"                , "float32"     , 1 , 0x411c ],
	// // [ "targetbaseaddr"           , "byte8 *"     , 1 , 0x6328 ],
	// // [ "style"                    , "uint8"       , 1 , 0x6338 ],
	// // [ "stylelevel"               , "uint8"       , 1 , 0x6358 ],
	// // [ "dashcount"                , "uint8"       , 1 , 0x635c ],
	// // [ "skystarcount"             , "uint8"       , 1 , 0x635d ],
	// // [ "airtrickcount"            , "uint8"       , 1 , 0x635e ],
	// // [ "trickupcount"             , "uint8"       , 1 , 0x635f ],
	// // [ "trickdowncount"           , "uint8"       , 1 , 0x6360 ],
	// // [ "quicksilver"              , "bool"        , 1 , 0x6361 ],
	// // [ "doppelganger"             , "bool"        , 1 , 0x6362 ],
	// // [ "styleexperience"          , "float32"     , 1 , 0x6364 ],
	// // [ "controllinkedactor"       , "bool"        , 1 , 0x6454 ],
	// // [ "linkedactorbaseaddr"      , "byte8 *"     , 1 , 0x6478 ],
	// // [ "selectedmeleeweaponvergil", "uint8"       , 1 , 0x6488 ],
	// // [ "activeweapon"             , "uint8"       , 1 , 0x648d ],
	// // [ "selectedmeleeweapon"      , "uint8"       , 1 , 0x6490 ],
	// // [ "selectedrangedweapon"     , "uint8"       , 1 , 0x6494 ],
	// // [ "equipment"                , "uint8"       , 4 , 0x6498 ],
	// // [ "weaponmetadata"           , "byte8 *"     , 4 , 0x64a0 ],
	// // [ "weaponflags"              , "byte32"      , 4 , 0x64c8 ],
	// // [ "activemeleeweapon"        , "uint8"       , 1 , 0x64f0 ],
	// // [ "activerangedweapon"       , "uint8"       , 1 , 0x64f1 ],
	// // [ "weapontimer"              , "float32"     , 4 , 0x64f4 ],
	// // [ "stylerank"                , "uint8"       , 1 , 0x6510 ],
	// // [ "stylemeter"               , "float32"     , 1 , 0x6514 ],
	// // [ "inputdata"                , "input_data"  , 58, 0x6674 ],
	// // [ "interactiondata"          , "vec4"        , 8 , 0x7460 ],
	// // [ "buttoninput"              , "byte16"      , 4 , 0x74e0 ],
	// // [ "modeldata"                , "model_data"  , 6 , 0xb630 ],
	// // [ "artemischargevalue"       , "float32"     , 2 , 0xb868 ],
	// // [ "artemischargeflags"       , "byte32"      , 2 , 0xb87c ],
	// // [ "isdefault"                , "bool"        , 1 , 0xb8c0 ],
	// // [ "character"                , "uint8"       , 1 , 0xb8c1 ],
	// // [ "nocollision"              , "bool"        , 1 , 0xb8c2 ],
	// // [ "hide"                     , "bool"        , 1 , 0xb8c3 ],
// // ];









var script = document.createElement("script");
script.type = "text/javascript";
script.src = "file:///C:/Users/serpentiem/source/repos/ddmk/Scripts/dmc3_actor_data_items.js";


script.onload = function()
{
	console.log("stuff");
}

document.head.appendChild(script);




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
	
	
	var items = ACTOR_DATA_ITEMS;
	
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

// var diff = (0xB8C0 - pos);

// if (diff)
// {
	// c += "\t_(" + diff.toString() + ");\n";
// }

c += "};\n";
c += "\n";
c += "#pragma pack(pop)\n";
c += "\n";
c += "#undef _\n";

document.body.innerHTML = "<plaintext>" + c + "\n" + c_assert;
