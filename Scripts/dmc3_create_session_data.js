NEW_LINE = "\r\n";

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

var c = "";
var c_assert = "";



var filename = "../Mary/Vars.h"

var file = fs.readFileSync(filename, "utf8");

var startTag = /\/\/ \$SessionDataStart$/;
var endTag   = /\/\/ \$SessionDataEnd$/;

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


c += "struct SESSION_DATA" + NEW_LINE;
c += "{" + NEW_LINE;
















var items =
[
	[ "mission"           , "uint32" , 0     ],
	[ "mode"              , "uint32" , 0xC   ],
	[ "oneHitKill"        , "bool"   , 0x10  ],
	[ "enableTutorial"    , "bool"   , 0x12  ],
	[ "useGoldOrb"        , "bool"   , 0x13  ],
	[ "character"         , "uint8"  , 0x14  ],
	[ "bloodyPalace"      , "bool"   , 0x1C  ],
	[ "goldOrbCount"      , "uint8"  , 0x35  ],
	[ "unlock[14]"        , "bool"   , 0x46  ],
	[ "weapons[4]"        , "uint8"  , 0x84  ],
	[ "costume"           , "uint8"  , 0xD0  ],
	[ "unlockDevilTrigger", "bool"   , 0xD1  ],
	[ "hitPoints"         , "float32", 0xD4  ],
	[ "magicPoints"       , "float32", 0xD8  ],
	[ "style"             , "uint32" , 0xDC  ],
	[ "styleLevel[6]"     , "uint32" , 0xE0  ],
	[ "styleExperience[6]", "float32", 0xF8  ],
	[ "expertise[8]"      , "byte32" , 0x110 ],
];

var pos = 0;

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

for (var index = 0; index < items.length; index++)
{
	var name = items[index][0];
	var type = items[index][1];
	var off  = items[index][2];

	if ((name == "") || (name.substring(0, 1) == "["))
	{
		name = "var_" + off.toString(16).toUpperCase();
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
	c_assert += "static_assert(offsetof(SESSION_DATA, " + name.split("[")[0] + ") == " + posString + ");" + NEW_LINE;

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


c += "};" + NEW_LINE;


c += NEW_LINE;

c += c_assert;



c += NEW_LINE;





for (var index = endTagLine; index < obj.length; index++)
{
	var str = obj[index].substring(0, (obj[index].length - 2));
	c += str + NEW_LINE;
}



//console.log(c_assert);


//var data = c + NEW_LINE + c_assert;


fs.writeFileSync(filename, c);





// console.log(c);
// console.log(c_assert);











