NEW_LINE = "\r\n";

var c = "";
var c_assert = "";
var pos = 0;

function lz(n)
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

function Align(boundary)
{
	var remainder = (pos % boundary);
	if (remainder)
	{
		var size = (boundary - remainder);
		pos += size;
	}
}

var typeHelper =
[
	// Built-in Primitives
	[ "bool"                    , "Byte"   , 1   , false ],
	[ "int"                     , "4 Bytes", 4   , false ],
	[ "void"                    , ""       , 0   , false ],
	// Primitives
	[ "bool8"                   , "Byte"   , 1   , false ],
	[ "bool16"                  , "2 Bytes", 2   , false ],
	[ "bool32"                  , "4 Bytes", 4   , false ],
	[ "bool64"                  , "8 Bytes", 8   , false ],
	[ "int8"                    , "Byte"   , 1   , false ],
	[ "int16"                   , "2 Bytes", 2   , false ],
	[ "int32"                   , "4 Bytes", 4   , false ],
	[ "int64"                   , "8 Bytes", 8   , false ],
	[ "uint8"                   , "Byte"   , 1   , false ],
	[ "uint16"                  , "2 Bytes", 2   , false ],
	[ "uint32"                  , "4 Bytes", 4   , false ],
	[ "uint64"                  , "8 Bytes", 8   , false ],
	[ "byte8"                   , "Byte"   , 1   , true  ],
	[ "byte16"                  , "2 Bytes", 2   , true  ],
	[ "byte32"                  , "4 Bytes", 4   , true  ],
	[ "byte64"                  , "8 Bytes", 8   , true  ],
	[ "float"                   , "Float"  , 4   , false ],
	// Structures
	[ "vec4"                    , ""       , 16  , false ],

	[ "InputData"               , ""       , 12  , false ],
	[ "MotionData"              , ""       , 2   , false ],
	[ "ActorEventData"          , ""       , 8   , false ],


	[ "ModelMetadata"           , ""       , 80  , false ],
	[ "ModelData"               , ""       , 1920, false ],
	[ "DevilModelMetadataDante" , ""       , 33  , false ],

	[ "ShadowData"              , ""       , 192 , false ],
	[ "PhysicsData"             , ""       , 240 , false ],
	[ "PhysicsMetadata"         , ""       , 320 , false ],
	[ "PhysicsLinkData"         , ""       , 192 , false ],
	[ "PhysicsLinkMetadata"     , ""       , 264 , false ],

	[ "BodyPartData"            , ""       , 288 , false ],
	[ "RecoveryData"            , ""       , 112 , false ],
	[ "WeaponData"              , ""       , 296 , false ],
	[ "PlayerData"              , ""       , 18  , false ],
	[ "CameraData"              , ""       , 512 , false ],
	[ "CollisionData"           , ""       , 656 , false ],
	[ "StyleData"           , ""       , 352 , false ],
];

function GetItemCount(name)
{
	var count = 1;

	var items = name.match(/\[\d+?\]/g);
	if (!items)
	{
		return count;
	}

	for (var itemIndex = 0; itemIndex < items.length; itemIndex++)
	{
		var item = items[itemIndex];

		count *= parseInt(item.match(/\[(\d+?)\]/)[1]);
	}

	return count;
}

function IsKnownType(type)
{
	type = type.replace(/ /g, "");
	type = type.replace(/\*/g, "");

	if (type.match(/Size_/))
	{
		return true;
	}

	var items = typeHelper;

	for (var itemIndex = 0; itemIndex < items.length; itemIndex++)
	{
		var item = items[itemIndex];
		var cppName = item[0];
		var ceName  = item[1];
		var size    = item[2];
		var hex     = item[3];

		if (cppName == type)
		{
			return true;
		}
	}

	return false;
}

function GetTypeSize(type)
{
	if (type.match(/\*/))
	{
		return 8;
	}

	{
		var match = type.match(/Size_([\d]+?)$/);
		if (match)
		{
			return parseInt(match[1]);
		}
	}

	var items = typeHelper;

	for (var itemIndex = 0; itemIndex < items.length; itemIndex++)
	{
		var item = items[itemIndex];
		var cppName = item[0];
		var ceName  = item[1];
		var size    = item[2];
		var hex     = item[3];

		if (cppName == type)
		{
			return size;
		}
	}

	console.log("Size 0");

	return 0;
}

function IsUnion
(
	name,
	type
)
{
	var names = name.split(",");
	var types = type.split(",");

	if (names.length != types.length)
	{
		console.log("Count Mismatch");
		console.log(name, type);

		return false;
	}

	return (names.length > 1);
}

function GetUnionSize
(
	name,
	type
)
{
	if (!IsUnion(name, type))
	{
		return 0;
	}

	var names = name.split(",");
	var types = type.split(",");

	var unionSize = 1;

	for (var index = 0; index < names.length; index++)
	{
		var count = GetItemCount(names[index]);
		var size = GetTypeSize(types[index]);

		size *= count;

		if (size > unionSize)
		{
			unionSize = size;
		}
	}

	return unionSize;
}



function GetVariableType(typeString)
{
	if (typeString.match(/\*/))
	{
		return "8 Bytes";
	}
	var items = typeHelper;
	for (var itemIndex = 0; itemIndex < items.length; itemIndex++)
	{
		var item = items[itemIndex];
		var cppName = item[0];
		var ceName  = item[1];
		var size    = item[2];
		var hex     = item[3];
		if (cppName == typeString)
		{
			return ceName;
		}
	}
	return "";
}

function GetShowAsHex(typeString)
{
	if (typeString.match(/\*/))
	{
		return true;
	}
	var items = typeHelper;
	for (var itemIndex = 0; itemIndex < items.length; itemIndex++)
	{
		var item = items[itemIndex];
		var cppName = item[0];
		var ceName  = item[1];
		var size    = item[2];
		var hex     = item[3];
		if ((cppName == typeString) && hex)
		{
			return true;
		}
	}
	return false;
}

function CreateCheatEntry
(
	description,
	hex,
	type,
	addr,
	off0,
	off1,
	off2,
	off3,
	off4,
	off5,
	off6,
	off7,
	off8,
	off9,
)
{
	c += "<CheatEntry>" + NEW_LINE;
	c += "<Description>" + description + "</Description>" + NEW_LINE;
	if (hex)
	{
		c += "<ShowAsHex>1</ShowAsHex>" + NEW_LINE;
	}
	c += "<VariableType>" + type + "</VariableType>" + NEW_LINE;
	c += "<Address>" + addr + "</Address>" + NEW_LINE;
	if (off0 != undefined)
	{
		c += "<Offsets>" + NEW_LINE;
		c += "<Offset>" + off0 + "</Offset>" + NEW_LINE;
	}
	if (off1 != undefined)
	{
		c += "<Offset>" + off1 + "</Offset>" + NEW_LINE;
	}
	if (off2 != undefined)
	{
		c += "<Offset>" + off2 + "</Offset>" + NEW_LINE;
	}
	if (off3 != undefined)
	{
		c += "<Offset>" + off3 + "</Offset>" + NEW_LINE;
	}
	if (off4 != undefined)
	{
		c += "<Offset>" + off4 + "</Offset>" + NEW_LINE;
	}
	if (off5 != undefined)
	{
		c += "<Offset>" + off5 + "</Offset>" + NEW_LINE;
	}
	if (off6 != undefined)
	{
		c += "<Offset>" + off6 + "</Offset>" + NEW_LINE;
	}
	if (off7 != undefined)
	{
		c += "<Offset>" + off7 + "</Offset>" + NEW_LINE;
	}
	if (off8 != undefined)
	{
		c += "<Offset>" + off8 + "</Offset>" + NEW_LINE;
	}
	if (off9 != undefined)
	{
		c += "<Offset>" + off9 + "</Offset>" + NEW_LINE;
	}
	if (off0 != undefined)
	{
		c += "</Offsets>" + NEW_LINE;
	}
	c += "</CheatEntry>" + NEW_LINE;
}

function CheatTableStart()
{
	c += "<?xml version=\"1.0\" encoding=\"utf-8\"?>" + NEW_LINE;
	c += "<CheatTable>" + NEW_LINE;
	c += "<CheatEntries>" + NEW_LINE;
}

function CheatTableEnd()
{
	c += "</CheatEntries>" + NEW_LINE;
	c += "</CheatTable>" + NEW_LINE;
}

function GroupStart
(
	description,
	hideChildren
)
{
	c += "<CheatEntry>" + NEW_LINE;
	c += "<Description>" + description + "</Description>" + NEW_LINE;
	if (hideChildren)
	{
		c += "<Options moHideChildren=\"1\"/>" + NEW_LINE;
	}
	c += "<GroupHeader>1</GroupHeader>" + NEW_LINE;
	c += "<CheatEntries>" + NEW_LINE;
}

function GroupEnd()
{
	c += "</CheatEntries>" + NEW_LINE;
	c += "</CheatEntry>" + NEW_LINE;
}



var Tag_start = -1;
var Tag_end   = -1;

function Tag_GetLineIndex
(
	lines,
	tag
)
{
	for (var lineIndex = 0; lineIndex < lines.length; lineIndex++)
	{
		var line = lines[lineIndex].substring(0, (lines[lineIndex].length - 2));

		if (line.match(tag))
		{
			return lineIndex;
		}
	}

	return -1;
}

function Tag_Init
(
	lines,
	startTag,
	endTag
)
{
	Tag_start = Tag_GetLineIndex(lines, startTag);
	Tag_end   = Tag_GetLineIndex(lines, endTag  );

	if (Tag_start < 0)
	{
		console.log("Start tag not found.");

		return false;
	}
	else if (Tag_end < 0)
	{
		console.log("End tag not found.");

		return false;
	}
	else if (Tag_end < Tag_start)
	{
		console.log("End tag appears before start tag.");

		return false;
	}

	console.log("Tag_start " + (Tag_start + 1));
	console.log("Tag_end   " + (Tag_end   + 1));

	return true;
}

function Tag_CopyUntil(lines)
{
	for (var lineIndex = 0; lineIndex <= Tag_start; lineIndex++)
	{
		var line = lines[lineIndex].substring(0, (lines[lineIndex].length - 2));

		c += line + NEW_LINE;
	}

	c += NEW_LINE;
}

function Tag_CopyAfter(lines)
{
	for (var lineIndex = Tag_end; lineIndex < lines.length; lineIndex++)
	{
		var line = lines[lineIndex].substring(0, (lines[lineIndex].length - 2));

		c += line + NEW_LINE;
	}
}

function CreateStruct
(
	structName,
	structSize,
	items
)
{
	c += "struct " + structName + NEW_LINE;
	c += "{" + NEW_LINE;

	pos = 0;

	for (var itemIndex = 0; itemIndex < items.length; itemIndex++)
	{
		var item = items[itemIndex];

		var name = item[0];
		var type = item[1];
		var off  = item[2];

		if
		(
			(name == "") ||
			(name.substring(0, 1) == "[")
		)
		{
			name = "var_" + off.toString(16).toUpperCase();
		}

		var diff = (off - pos);
		if (diff)
		{
			c += "\t_(" + diff.toString() + ");" + NEW_LINE;
		}
		pos = off;

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
		c_assert += "static_assert(offsetof(" + structName + ", " + name.split("[")[0] + ") == " + posString + ");" + NEW_LINE;

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

	if (pos < structSize)
	{
		var diff = (structSize - pos);
		if (diff)
		{
			c += "\t_(" + diff.toString() + ");" + NEW_LINE;
		}
		pos = structSize;
	}

	c += "};" + NEW_LINE;

	c += NEW_LINE;

	c_assert += "static_assert(sizeof(" + structName + ") == " + pos.toString() + ");" + NEW_LINE;

	c += c_assert;

	c_assert = "";

	c += NEW_LINE;
}
