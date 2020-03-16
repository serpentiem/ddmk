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

var items =
[
	[ "equipment"                , "uint8"       , 8 , 0 ],
	[ "modelIndexMirror"         , "uint8"       , 1 , 0x28   ],
	[ "devil"         , "bool"       , 1 , 0x2C   ],
	[ "devilState"         , "uint8"       , 1 , 0x30   ],
	
	
	
	
	[ "character"                , "uint8"       , 1 , 0x78   ],
	[ "character"                , "uint8"       , 1 , 0x78   ],
	[ "character"                , "uint8"       , 1 , 0x78   ],
	[ "character"                , "uint8"       , 1 , 0x78   ],
	[ "character"                , "uint8"       , 1 , 0x78   ],
	
	
	
	
	[ "x"                        , "float32"     , 1 , 0x80   ],
	[ "y"                        , "float32"     , 1 , 0x84   ],
	[ "z"                        , "float32"     , 1 , 0x88   ],
	[ "direction"                , "uint16"      , 1 , 0xC0   ],
	[ "actorId"                  , "uint8"       , 1 , 0x118  ],
	[ "isDoppelganger"           , "bool"        , 1 , 0x11C  ],
	[ "visible"                  , "uint8"       , 1 , 0x120  ],
	[ "motionArchive"            , "byte8 *"     , 32, 0x38A0 ],
	[ "motionData"               , "MOTION_DATA" , 5 , 0x39B0 ],
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

console.log("pos 0x" + pos.toString(16).toUpperCase());

var diff = (0x3F800 - pos);

if (diff)
{
	c += "\t_(" + diff.toString() + ");\n";
}

c += "};\n";
c += "\n";
c += "#pragma pack(pop)\n";
c += "\n";
c += "#undef _\n";

document.body.innerHTML = "<plaintext>" + c + "\n" + c_assert;
