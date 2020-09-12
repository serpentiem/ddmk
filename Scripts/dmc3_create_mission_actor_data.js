var fs = require("fs");

eval(fs.readFileSync("dmc3_core.js", "utf8"));

var queuedItems =
[
	[ "weapons[5]"        , "uint8"  , 0    ],
	[ "hitPoints"         , "float32", 0x50 ],
	[ "magicPoints"       , "float32", 0x54 ],
	[ "style"             , "uint32" , 0x58 ],
	[ "styleLevel[6]"     , "uint32" , 0x5C ],
	[ "styleExperience[6]", "float32", 0x74 ],
	[ "expertise[8]"      , "byte32" , 0x8C ],
];

var activeItems =
[
	[ "weapons[5]"        , "uint8"  , 0    ],
	[ "style"             , "uint32" , 0x38 ],
	[ "styleLevel"        , "uint32" , 0x3C ],
	[ "expertise[8]"      , "byte32" , 0x40 ],
	
	[ "styleExperience", "float32", 0x60 ],
	
	[ "hitPoints"         , "float32", 0x64 ],
	[ "maxHitPoints"         , "float32", 0x68 ],
	[ "magicPoints"       , "float32", 0x6C ],
	[ "maxMagicPoints"       , "float32", 0x70 ],




	
	




	
	


];

var c_assert = "";

var filename = "../Mary/Vars.h"

var file = fs.readFileSync(filename, "utf8");

var startTag = /\/\/ \$MissionActorDataStart$/;
var endTag   = /\/\/ \$MissionActorDataEnd$/;

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


pos = 0;


c += "struct QueuedMissionActorData" + NEW_LINE;
c += "{" + NEW_LINE;

for (var index = 0; index < queuedItems.length; index++)
{
	var name = queuedItems[index][0];
	var type = queuedItems[index][1];
	var off  = queuedItems[index][2];

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
	c_assert += "static_assert(offsetof(QueuedMissionActorData, " + name.split("[")[0] + ") == " + posString + ");" + NEW_LINE;

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



pos = 0;

c_assert = "";

c += "struct ActiveMissionActorData" + NEW_LINE;
c += "{" + NEW_LINE;

for (var index = 0; index < activeItems.length; index++)
{
	var name = activeItems[index][0];
	var type = activeItems[index][1];
	var off  = activeItems[index][2];

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
	c_assert += "static_assert(offsetof(ActiveMissionActorData, " + name.split("[")[0] + ") == " + posString + ");" + NEW_LINE;

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

fs.writeFileSync(filename, c);
