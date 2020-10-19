NEW_LINE = "\r\n";

var fs = require("fs");

var c = "";



var filename = "../Mary/Vars.h"



var file = fs.readFileSync(filename, "utf8");

var startTag = /\/\/ \$CacheFileStart$/;
var endTag   = /\/\/ \$CacheFileEnd$/;

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








var items =
[
	// Dante
	[ "pl000"              , "obj"    ],
	[ "pl011"              , "obj"    ],
	[ "pl013"              , "obj"    ],
	[ "pl015"              , "obj"    ],
	[ "pl016"              , "obj"    ],
	[ "pl018"              , "obj"    ],
	[ "pl005"              , "obj"    ],
	[ "pl006"              , "obj"    ],
	[ "pl007"              , "obj"    ],
	[ "pl008"              , "obj"    ],
	[ "pl009"              , "obj"    ],
	[ "pl017"              , "obj"    ],
	[ "pl000_00_0"         , "motion" ],
	[ "pl000_00_1"         , "motion" ],
	[ "pl000_00_2"         , "motion" ],
	[ "pl000_00_3"         , "motion" ],
	[ "pl000_00_4"         , "motion" ],
	[ "pl000_00_5"         , "motion" ],
	[ "pl000_00_6"         , "motion" ],
	[ "pl000_00_7"         , "motion" ],
	[ "pl000_00_8"         , "motion" ],
	[ "pl000_00_9"         , "motion" ],
	[ "pl000_00_10"        , "motion" ],
	[ "pl000_00_11"        , "motion" ],
	[ "pl000_00_12"        , "motion" ],
	[ "pl000_00_13"        , "motion" ],
	[ "pl000_00_14"        , "motion" ],
	[ "pl000_00_15"        , "motion" ],
	[ "pl000_00_16"        , "motion" ],
	[ "pl000_00_17"        , "motion" ],
	[ "pl000_00_18"        , "motion" ],
	[ "pl000_00_19"        , "motion" ],
	[ "pl000_00_20"        , "motion" ],
	[ "pl000_00_21"        , "motion" ],
	[ "pl000_00_22"        , "motion" ],
	[ "pl000_00_23"        , "motion" ],
	[ "pl000_00_24"        , "motion" ],
	[ "pl000_00_25"        , "motion" ],
	[ "pl000_00_26"        , "motion" ],
	[ "plwp_sword"         , "obj"    ],
	[ "plwp_sword2"        , "obj"    ],
	[ "plwp_sword3"        , "obj"    ],
	[ "plwp_nunchaku"      , "obj"    ],
	[ "plwp_2sword"        , "obj"    ],
	[ "plwp_guitar"        , "obj"    ],
	[ "plwp_fight"         , "obj"    ],
	[ "plwp_gun"           , "obj"    ],
	[ "plwp_shotgun"       , "obj"    ],
	[ "plwp_laser"         , "obj"    ],
	[ "plwp_rifle"         , "obj"    ],
	[ "plwp_ladygun"       , "obj"    ],
	// Bob
	[ "pl001"              , "obj"    ],
	[ "pl001_00_0"         , "motion" ],
	[ "pl001_00_1"         , "motion" ],
	[ "pl001_00_2"         , "motion" ],
	[ "pl001_00_31"        , "motion" ],
	[ "plwp_vergilsword"   , "obj"    ],
	// Lady
	[ "pl002"              , "obj"    ],
	[ "pl002_00_0"         , "motion" ],
	[ "pl002_00_1"         , "motion" ],
	[ "pl002_00_2"         , "motion" ],
	// Vergil
	[ "pl021"              , "obj"    ],
	[ "pl023"              , "obj"    ],
	[ "pl026"              , "obj"    ],
	[ "pl010"              , "obj"    ],
	[ "pl014"              , "obj"    ],
	[ "pl025"              , "obj"    ],
	[ "pl021_00_0"         , "motion" ],
	[ "pl021_00_1"         , "motion" ],
	[ "pl021_00_2"         , "motion" ],
	[ "pl021_00_3"         , "motion" ],
	[ "pl021_00_4"         , "motion" ],
	[ "pl021_00_5"         , "motion" ],
	[ "pl021_00_6"         , "motion" ],
	[ "pl021_00_7"         , "motion" ],
	[ "pl021_00_8"         , "motion" ],
	[ "pl021_00_9"         , "motion" ],
	[ "plwp_newvergilsword", "obj"    ],
	[ "plwp_newvergilfight", "obj"    ],
	[ "plwp_forceedge"     , "obj"    ],
	[ "plwp_nerosword"     , "obj"    ],
	// Other
	[ "em034"              , "obj"    ],
	[ "id100"              , "id"     ],
	[ "id100V"             , "id"     ],
];

c += "enum CACHE_FILE" + NEW_LINE;
c += "{" + NEW_LINE;

for (var index = 0; index < items.length; index++)
{
	var name = items[index][0];
	var type = items[index][1];
	c += "\t" + name + "," + NEW_LINE;
}

c += "\tMAX_CACHE_FILE," + NEW_LINE;
c += "};" + NEW_LINE;

c += NEW_LINE;

c += "struct CacheFileHelper" + NEW_LINE;
c += "{" + NEW_LINE;
c += "\tconst char * name;" + NEW_LINE;
c += "\tconst char * type;" + NEW_LINE;
c += "};" + NEW_LINE;

c += NEW_LINE;

c += "constexpr CacheFileHelper cacheFileHelper[MAX_CACHE_FILE] =" + NEW_LINE;
c += "{" + NEW_LINE;

for (var index = 0; index < items.length; index++)
{
	var name = items[index][0];
	var type = items[index][1];
	c += "\t{ \"" + name + ".pac\", \"";

	if (type == "obj")
	{
		c += "obj\\\\" + name + ".pac";
	}
	else if (type == "motion")
	{
		var parent = name.match(/([\S\s]+?)_/);
		if (parent)
		{
			c += "motion\\\\" + parent[1] + "\\\\" + name + ".pac";
		}
	}
	else if (type == "id")
	{
		var id = name.match(/id([0-9]+?)[A-Z]*?$/);
		if (id)
		{
			var str = id[1];
			if (str.length >= 3)
			{
				str = str.substring(0, (str.length - 2)) + "00";
			}
			c += "id\\\\id" + str + "\\\\" + name + ".pac";
		}
	}
	c += "\" }," + NEW_LINE;
}

c += "};" + NEW_LINE;


c += NEW_LINE;





for (var index = endTagLine; index < obj.length; index++)
{
	var str = obj[index].substring(0, (obj[index].length - 2));
	c += str + NEW_LINE;
}





//fs.writeFileSync("../Mary/ActorData.h", c);





//fs.writeFileSync("cacheFiles.txt", c);
fs.writeFileSync(filename, c);





