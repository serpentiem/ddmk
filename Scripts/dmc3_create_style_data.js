var fs = require("fs");

eval(fs.readFileSync("dmc3_core.js", "utf8"));

const STYLE_DATA_SIZE = 352;

var items =
[
	[ "rank"    , "uint32", 0     ],
	[ "meter"   , "float" , 4     ],
	[ "quotient", "float" , 0x150 ],
	[ "dividend", "float" , 0x154 ],
	[ "divisor" , "float" , 0x158 ],
];

var c_assert = "";

var filename = "../Mary/Vars.h"

var file = fs.readFileSync(filename, "utf8");

var startTag = /\/\/ \$StyleDataStart$/;
var endTag   = /\/\/ \$StyleDataEnd$/;

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



c += "struct StyleData" + NEW_LINE;
c += "{" + NEW_LINE;

pos = 0;

for (var itemIndex = 0; itemIndex < items.length; itemIndex++)
{
	var name = items[itemIndex][0];
	var type = items[itemIndex][1];
	var off  = items[itemIndex][2];

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
			c += "\t_(" + diff.toString() + ");" + NEW_LINE;
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
			c += "\t_(" + diff.toString() + ");" + NEW_LINE;
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
	c_assert += "static_assert(offsetof(StyleData, " + name.split("[")[0] + ") == " + posString + ");" + NEW_LINE;

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

var off = STYLE_DATA_SIZE;

if (pos < off)
{
	var diff = (off - pos);
	if (diff)
	{
		c += "\t_(" + diff.toString() + ");" + NEW_LINE;
	}
	pos = off;
}

c += "};" + NEW_LINE;

c += NEW_LINE;

c_assert += "static_assert(sizeof(StyleData) == " + STYLE_DATA_SIZE + ");" + NEW_LINE;

c += c_assert;

c += NEW_LINE;



for (var index = endTagLine; index < obj.length; index++)
{
	var str = obj[index].substring(0, (obj[index].length - 2));
	c += str + NEW_LINE;
}



fs.writeFileSync(filename, c);
