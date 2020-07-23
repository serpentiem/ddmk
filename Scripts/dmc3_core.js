NEW_LINE = "\r\n";

var c = "";
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
	[ "bool"                      , "Byte"   , 1   , false ],
	[ "int"                       , "4 Bytes", 4   , false ],
	// Primitives
	[ "bool8"                     , "Byte"   , 1   , false ],
	[ "bool16"                    , "2 Bytes", 2   , false ],
	[ "bool32"                    , "4 Bytes", 4   , false ],
	[ "bool64"                    , "8 Bytes", 8   , false ],
	[ "int8"                      , "Byte"   , 1   , false ],
	[ "int16"                     , "2 Bytes", 2   , false ],
	[ "int32"                     , "4 Bytes", 4   , false ],
	[ "int64"                     , "8 Bytes", 8   , false ],
	[ "uint8"                     , "Byte"   , 1   , false ],
	[ "uint16"                    , "2 Bytes", 2   , false ],
	[ "uint32"                    , "4 Bytes", 4   , false ],
	[ "uint64"                    , "8 Bytes", 8   , false ],
	[ "byte8"                     , "Byte"   , 1   , true  ],
	[ "byte16"                    , "2 Bytes", 2   , true  ],
	[ "byte32"                    , "4 Bytes", 4   , true  ],
	[ "byte64"                    , "8 Bytes", 8   , true  ],
	[ "float32"                   , "4 Bytes", 4   , false ],
	// Structures
	[ "vec4"                      , ""       , 16  , false ],
	[ "INPUT_DATA"                , ""       , 12  , false ],
	[ "MOTION_DATA"               , ""       , 2   , false ],
	[ "ModelMetadata"            , ""       , 80  , false ],
	[ "ModelData"                , ""       , 1920, false ],
	[ "DevilModelMetadataDante"   , ""       , 33  , false ],
	[ "ACTOR_EVENT_DATA"          , ""       , 8   , false ],
	// [ "SHADOW_DATA"               , ""       , 192 , false ],
	// [ "PHYSICS_DATA"              , ""       , 240 , false ],
	


	[ "ShadowData"           , "" , 192 , false ],
	[ "PhysicsData"          , "" , 240 , false ],
	[ "PhysicsMetadata"      , "" , 320 , false ],
	[ "PhysicsLinkData"     , "" , 192 , false ],
	[ "PhysicsLinkMetadata" , "" , 264 , false ],

	[ "BodyPartData" , "" , 288 , false ],
];

// function Template(typeString)
// {
// 	var items = typeHelper;
// 	for (var itemIndex = 0; itemIndex < items.length; itemIndex++)
// 	{
// 		var item = items[itemIndex];
// 		var cppName = item[0];
// 		var ceName  = item[1];
// 		var size    = item[2];
// 		var hex     = item[3];
// 		if (cppName == typeString)
// 		{
// 			return;
// 		}
// 	}
// 	return;
// }

function IsKnownType(typeString)
{
	typeString = typeString.replace(/ /g, "");
	typeString = typeString.replace(/\*/g, "");
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
			return true;
		}
	}
	if (typeString.match(/Size_/))
	{
		return true;
	}
	return false;
}

function GetTypeSize(typeString)
{
	if (typeString.match(/\*/))
	{
		return 8;
	}
	{
		var match = typeString.match(/Size_([\d]+?)$/);
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
		if (cppName == typeString)
		{
			return size;
		}
	}
	return 0;
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
