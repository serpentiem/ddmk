const debug = true;

const TypeFlags_NoTypeAssert = 1 << 0;
const TypeFlags_NoSizeAssert = 1 << 1;
const TypeFlags_NoAsserts    = 1 << 2;
const TypeFlags_NoDefault    = 1 << 3;
const TypeFlags_NoP          = 1 << 4;
const TypeFlags_NoLP         = 1 << 5;
const TypeFlags_NoLPC        = 1 << 6;
const TypeFlags_NoPointers   = 1 << 7;

const ScopeFlags_Semicolon = 1 << 0;
const ScopeFlags_NoNewLine = 1 << 1;

const TupleFlags_GreatestSize   = 1 << 0;
const TupleFlags_NoIncPos       = 1 << 1;
const TupleFlags_NoPositionName = 1 << 2;
const TupleFlags_NoScopeStart   = 1 << 3;
const TupleFlags_NoScopeEnd     = 1 << 4;
const TupleFlags_NoTypeAssert   = 1 << 5;
const TupleFlags_NoOffsetAssert = 1 << 6;
const TupleFlags_NoSizeAssert   = 1 << 7;
const TupleFlags_Union          = 1 << 8;
const TupleFlags_Export         = 1 << 9;

const EnumFlags_NoSizeAssert = 1 << 0;

const PositionFlags_Hex      = 1 << 0;
const PositionFlags_NoPrefix = 1 << 1;

const FunctionFlags_Virtual     = 1 << 0;
const FunctionFlags_PureVirtual = 1 << 1;
const FunctionFlags_ExternC     = 1 << 2;
const FunctionFlags_NoSemicolon = 1 << 3;

NEW_LINE = "\r\n";

let c              = "";
let c_assert       = "";
let c_assertType   = "";
let c_assertOff    = "";
let c_assertSize   = "";
let c_verify       = "";
let c_assertVerify = "";

function Clear()
{
	c        = "";
	c_verify = "";
}

function ClearAsserts()
{
	c_assert       = "";
	c_assertType   = "";
	c_assertOff    = "";
	c_assertSize   = "";
	c_assertVerify = "";
}

function ClearAll()
{
	Clear();
	ClearAsserts();
}

function MergeAsserts()
{
	c_assert += c_assertType;
	c_assert += NEW_LINE;

	c_assert += c_assertOff;
	c_assert += NEW_LINE;

	c_assert += c_assertSize;
	c_assert += NEW_LINE;

	c_assertVerify += c_assertType;
	c_assertVerify += NEW_LINE;

	c_assertVerify += c_assertOff;
	c_assertVerify += NEW_LINE;

	c_assertVerify += c_assertSize;
	c_assertVerify += NEW_LINE;
}

function FeedAsserts()
{
	c += c_assert;
	c += NEW_LINE;

	c_verify += c_assertVerify;
	c_verify += NEW_LINE;
}

function GetLines(buffer)
{
	return buffer.match(/[\S\s]*?\r\n/g);
}

function GetLine
(
	lines,
	lineIndex
)
{
	if
	(
		(lineIndex < 0) ||
		(lineIndex >= lines.length)
	)
	{
		return "";
	}

	return lines[lineIndex].substring(0, (lines[lineIndex].length - 2));
}

function CleanStream()
{
	let c_new = "";

	let lines = GetLines(c);

	for (let lineIndex = 0; lineIndex < lines.length; lineIndex++)
	{
		let lastLineIndex = (lineIndex - 1);
		let nextLineIndex = (lineIndex + 1);

		let line     = GetLine(lines, lineIndex    );
		let lastLine = GetLine(lines, lastLineIndex);
		let nextLine = GetLine(lines, nextLineIndex);

		if
		(
			(line == "") &&
			(lastLine == "")
		)
		{
			continue;
		}
		// else if
		// (
		// 	(line == "") &&
		// 	(nextLine.match(/^\t*\};?$/))
		// )
		// {
		// 	continue;
		// }

		c_new += line + NEW_LINE;
	}

	c = c_new;
}




































//let c_assert2 = "";
//let g_pos = 0;

function lz(n)
{
	let str = "";
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






let tabCount = 0;

function Tabs()
{
	let tabs = "";

	for (let tabIndex = 0; tabIndex < tabCount; tabIndex++)
	{
		tabs += "\t";
	}

	return tabs;
}














function ScopeStart(name = "{")
{
	c += Tabs() + name + NEW_LINE;

	tabCount++;
}

function ScopeEnd
(
	name = "}",
	flags = 0
)
{
	tabCount--;

	c += Tabs() + name;

	if (flags & ScopeFlags_Semicolon)
	{
		c += ";";
	}

	if (!(flags & ScopeFlags_NoNewLine))
	{
		c += NEW_LINE;
	}
}






function PositionName
(
	pos,
	flags = 0
)
{
	let name = "";

	if (flags & PositionFlags_Hex)
	{
		if (pos >= 10)
		{
			if (!(flags & PositionFlags_NoPrefix))
			{
				name += "0x";
			}

			name += pos.toString(16).toUpperCase();
		}
		else
		{
			name += pos.toString();
		}
	}
	else
	{
		name = pos.toString();
	}

	return name;
}

















let typeSizes =
[
	[ "void"                   , 0    ],
	[ "bool"                   , 1    ],
	[ "int"                    , 4    ],
	[ "char"                   , 1    ],
	[ "short"                  , 2    ],
	[ "long"                   , 4    ],
	[ "long long"              , 8    ],
	[ "bool8"                  , 1    ],
	[ "bool16"                 , 2    ],
	[ "bool32"                 , 4    ],
	[ "bool64"                 , 8    ],
	[ "int8"                   , 1    ],
	[ "int16"                  , 2    ],
	[ "int32"                  , 4    ],
	[ "int64"                  , 8    ],
	[ "uint8"                  , 1    ],
	[ "uint16"                 , 2    ],
	[ "uint32"                 , 4    ],
	[ "uint64"                 , 8    ],
	[ "byte8"                  , 1    ],
	[ "byte16"                 , 2    ],
	[ "byte32"                 , 4    ],
	[ "byte64"                 , 8    ],
	[ "float"                  , 4    ],
	[ "vec4"                   , 16   ],
	// @Todo: Move.
	[ "InputData"              , 12   ],
	[ "MotionData"             , 2    ],
	[ "ActorEventData"         , 8    ],
	[ "ModelMetadata"          , 80   ],
	[ "ModelData"              , 1920 ],
	[ "DevilModelMetadataDante", 33   ],
	[ "ShadowData"             , 192  ],
	[ "PhysicsData"            , 240  ],
	[ "PhysicsMetadata"        , 320  ],
	[ "PhysicsLinkData"        , 192  ],
	[ "PhysicsLinkMetadata"    , 264  ],
	[ "BodyPartData"           , 288  ],
	[ "RecoveryData"           , 112  ],
	[ "WeaponData"             , 296  ],
	[ "PlayerData"             , 18   ],
	[ "CameraData"             , 512  ],
	[ "CollisionData"          , 656  ],
	[ "StyleData"              , 352  ],
];

function GetTypeSize(typename)
{
	if (typename == "")
	{
		console.log("No Type");

		return 0;
	}

	typename = typename.replace(/(const|signed|unsigned) /g, "");

	if (typename.match(/\*/))
	{
		return 8;
	}

	{
		let match = typename.match(/^Size_(\d+?)$/);
		if (match)
		{
			let size = parseInt(match[1]);

			return size;
		}
	}

	let items = typeSizes;

	for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
	{
		let item = items[itemIndex];

		let name = item[0];
		let size = item[1];

		if (name == typename)
		{
			if (name == "")
			{

				console.log(itemIndex);


				console.log(name + " " + size);
			}

			return size;
		}
	}

	console.log("Unknown Type " + typename);

	return 0;
}

function GetTypeCount(name)
{
	let count = 1;

	let items = name.match(/\[\d+?\]/g);
	if (!items)
	{
		return count;
	}

	for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
	{
		let item = items[itemIndex];

		count *= parseInt(item.match(/\[(\d+?)\]/)[1]);
	}

	return count;
}



let Tag_start = -1;
let Tag_end   = -1;

function Tag_GetLineIndex
(
	lines,
	tag
)
{
	for (let lineIndex = 0; lineIndex < lines.length; lineIndex++)
	{
		let line = lines[lineIndex].substring(0, (lines[lineIndex].length - 2));

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
	for (let lineIndex = 0; lineIndex <= Tag_start; lineIndex++)
	{
		let line = lines[lineIndex].substring(0, (lines[lineIndex].length - 2));

		c += line + NEW_LINE;
	}

	c += NEW_LINE;
}

function Tag_CopyAfter(lines)
{
	for (let lineIndex = Tag_end; lineIndex < lines.length; lineIndex++)
	{
		let line = lines[lineIndex].substring(0, (lines[lineIndex].length - 2));

		c += line + NEW_LINE;
	}
}



function Min
(
	a,
	b
)
{
	return (a < b) ? a : b;
}

function Max
(
	a,
	b
)
{
	return (a > b) ? a : b;
}

function Align
(
	pos,
	boundary
)
{
	let remainder = (pos % boundary);
	if (remainder)
	{
		let size = (boundary - remainder);

		pos += size;
	}

	return pos;
}

function DefaultAlignFunction
(
	pos,
	name,
	type
)
{
	return pos;
}



function GetTupleSize
(
	tupleItems,
	flags     = 0,
	alignFunc = DefaultAlignFunction
)
{
	let pos = 0;

	let greatestTypeSize = 0;

	for (let itemIndex = 0; itemIndex < tupleItems.length; itemIndex++)
	{
		let item = tupleItems[itemIndex];

		let name  = item[0];
		let type  = item[1];
		let items = item[2];
		let off   = item[3];

		let size = 0;

		if (off != undefined)
		{
			pos = off;
		}

		{
			let match = name.match(/_\((\d+?)\)/);
			if (match)
			{
				size = parseInt(match[1]);

				pos += size;

				continue;
			}
		}

		if (off == undefined)
		{
			pos = alignFunc
			(
				pos,
				name,
				type
			);
		}



		if (type == "union")
		{
			size = GetTupleSize
			(
				items,
				TupleFlags_GreatestSize,
				alignFunc
			);
		}
		else if (type == "struct")
		{
			size = GetTupleSize
			(
				items,
				0,
				alignFunc
			);
		}
		else
		{
			let typeSize = GetTypeSize(type);

			if (typeSize > greatestTypeSize)
			{
				greatestTypeSize = typeSize;
			}

			let typeCount = GetTypeCount(name);

			size = (typeSize * typeCount);
		}



		pos += size;
	}



	if (flags & TupleFlags_GreatestSize)
	{
		return greatestTypeSize;
	}



	return pos;
}



function CreateTypeAssert
(
	tuplename,
	name,
	type
)
{
	let newName = name.split("[")[0];

	let count = GetTypeCount(name);

	c_assertType += Tabs() + "static_assert(TypeMatch<decltype(" +
	tuplename + "::" + newName + "), " + type;

	if (count > 1)
	{
		c_assertType += "[" + count + "]";
	}

	c_assertType += ">::value);" + NEW_LINE;
}

function CreateOffsetAssert
(
	tuplename,
	name,
	off
)
{
	let newName = name.split("[")[0];

	c_assertOff += Tabs() + "static_assert(offsetof(" +
	tuplename + ", " + newName + ") == " +
	PositionName
	(
		off,
		PositionFlags_Hex
	) +
	");" + NEW_LINE;
}

function CreateSizeAssert
(
	name,
	size,
	flags
)
{
	c_assertSize += Tabs() + "static_assert(sizeof(" + name + ") == " +
	PositionName
	(
		size,
		flags
	) +
	");" + NEW_LINE;
}



function GetFlagIf
(
	flags,
	flag
)
{
	if (flags & flag)
	{
		return flag;
	}

	return 0;
}



function CreateTupleAssertsFunction
(
	tuplename,
	tupleItems,
	pos       = 0,
	flags     = 0,
	alignFunc = DefaultAlignFunction
)
{
	for (let itemIndex = 0; itemIndex < tupleItems.length; itemIndex++)
	{
		let item = tupleItems[itemIndex];

		let name  = item[0];
		let type  = item[1];
		let items = item[2];
		let off   = item[3];

		let size = 0;

		if (off != undefined)
		{
			pos = off;
		}

		{
			let match = name.match(/_\((\d+?)\)/);
			if (match)
			{
				size = parseInt(match[1]);

				pos += size;

				continue;
			}
		}

		if (off == undefined)
		{
			pos = alignFunc
			(
				pos,
				name,
				type
			);
		}



		if (type == "union")
		{
			let newFlags = TupleFlags_NoIncPos;

			newFlags |= GetFlagIf
			(
				flags,
				TupleFlags_NoTypeAssert
			);

			newFlags |= GetFlagIf
			(
				flags,
				TupleFlags_NoOffsetAssert
			);

			CreateTupleAssertsFunction
			(
				tuplename,
				items,
				pos,
				newFlags,
				alignFunc
			);

			size = GetTupleSize
			(
				items,
				TupleFlags_GreatestSize,
				alignFunc
			);
		}
		else if (type == "struct")
		{
			let newFlags = 0;

			newFlags |= GetFlagIf
			(
				flags,
				TupleFlags_NoTypeAssert
			);

			newFlags |= GetFlagIf
			(
				flags,
				TupleFlags_NoOffsetAssert
			);

			CreateTupleAssertsFunction
			(
				tuplename,
				items,
				pos,
				newFlags,
				alignFunc
			);

			size = GetTupleSize
			(
				items,
				0,
				alignFunc
			);
		}
		else
		{
			if
			(
				(name == "") ||
				(name.substring(0, 1) == "[")
			)
			{
				name = "var_" +
				PositionName
				(
					pos,
					PositionFlags_Hex |
					PositionFlags_NoPrefix
				) +
				name;
			}

			if (!(flags & TupleFlags_NoTypeAssert))
			{
				CreateTypeAssert
				(
					tuplename,
					name,
					type
				);
			}

			if (!(flags & TupleFlags_NoOffsetAssert))
			{
				CreateOffsetAssert
				(
					tuplename,
					name,
					pos
				);
			}

			let typeSize = GetTypeSize(type);

			let typeCount = GetTypeCount(name);

			size = (typeSize * typeCount);
		}



		if (!(flags & TupleFlags_NoIncPos))
		{
			pos += size;
		}
	}
}

function CreateTupleAsserts
(
	tuplename,
	tupleItems,
	tupleSize     = 0,
	pos           = 0,
	tupleFlags    = 0,
	positionFlags = 0,
	alignFunc     = DefaultAlignFunction
)
{
	CreateTupleAssertsFunction
	(
		tuplename,
		tupleItems,
		pos,
		tupleFlags,
		alignFunc
	);

	if (!(tupleFlags & TupleFlags_NoSizeAssert))
	{
		let size = 0;

		if (tupleSize > 0)
		{
			size = tupleSize;
		}
		else
		{
			size = GetTupleSize
			(
				tupleItems,
				tupleFlags,
				alignFunc
			);
		}

		CreateSizeAssert
		(
			tuplename,
			size,
			positionFlags
		);
	}
}



function CreateTupleFunction
(
	tupleItems,
	pos       = 0,
	flags     = 0,
	alignFunc = DefaultAlignFunction
)
{
	let lastPos = pos;

	for (let itemIndex = 0; itemIndex < tupleItems.length; itemIndex++)
	{
		let item = tupleItems[itemIndex];

		let name  = item[0];
		let type  = item[1];
		let items = item[2];
		let off   = item[3];

		let size = 0;

		if (off != undefined)
		{
			pos = off;
		}

		{
			let match = name.match(/_\((\d+?)\)/);
			if (match)
			{
				size = parseInt(match[1]);

				c += Tabs() + "_(" + size + ");" + NEW_LINE;

				pos += size;

				lastPos = pos;

				continue;
			}
		}

		if (off == undefined)
		{
			pos = alignFunc
			(
				pos,
				name,
				type
			);
		}

		let diff = (pos - lastPos);
		if (diff)
		{
			c += Tabs() + "_(" + diff + ");" + NEW_LINE;
		}



		if (type == "union")
		{
			if (name == "")
			{
				c += Tabs() + type + NEW_LINE;
			}
			else
			{
				c += Tabs() + type + " " + name + NEW_LINE;
			}

			ScopeStart();

			CreateTupleFunction
			(
				items,
				pos,
				TupleFlags_NoIncPos,
				alignFunc
			);

			ScopeEnd
			(
				"}",
				ScopeFlags_Semicolon |
				ScopeFlags_NoNewLine
			);

			c += " // " +
			PositionName
			(
				pos,
				PositionFlags_Hex
			);

			c += NEW_LINE;



			size = GetTupleSize
			(
				items,
				TupleFlags_GreatestSize,
				alignFunc
			);
		}
		else if (type == "struct")
		{
			if (name == "")
			{
				c += Tabs() + type + NEW_LINE;
			}
			else
			{
				c += Tabs() + type + " " + name + NEW_LINE;
			}

			ScopeStart();

			CreateTupleFunction
			(
				items,
				pos,
				0,
				alignFunc
			);

			ScopeEnd
			(
				"}",
				ScopeFlags_Semicolon |
				ScopeFlags_NoNewLine
			);

			c += " // " +
			PositionName
			(
				pos,
				PositionFlags_Hex
			);

			c += NEW_LINE;



			size = GetTupleSize
			(
				items,
				0,
				alignFunc
			);
		}
		else
		{
			if
			(
				(name == "") ||
				(name.substring(0, 1) == "[")
			)
			{
				name = "var_" +
				PositionName
				(
					pos,
					PositionFlags_Hex |
					PositionFlags_NoPrefix
				) +
				name;
			}

			c += Tabs() + type + " " + name + ";";

			if (!(flags & TupleFlags_NoPositionName))
			{
				c += " // " +
				PositionName
				(
					pos,
					PositionFlags_Hex
				);
			}

			c += NEW_LINE;



			let typeSize = GetTypeSize(type);

			let typeCount = GetTypeCount(name);

			size = (typeSize * typeCount);
		}



		if (!(flags & TupleFlags_NoIncPos))
		{
			pos += size;

			lastPos = pos;
		}
	}

	return pos;
}

function CreateTuple
(
	tuplename,
	tupleItems,
	tupleSize = 0,
	pos       = 0,
	flags     = 0,
	alignFunc = DefaultAlignFunction
)
{
	c += Tabs();

	if (flags & TupleFlags_Export)
	{
		c += "export ";
	}

	let type = "struct";

	if (flags & TupleFlags_Union)
	{
		type = "union";
	}

	c += type + " " + tuplename + NEW_LINE;

	ScopeStart();

	CreateTupleFunction
	(
		tupleItems,
		pos,
		flags,
		alignFunc
	);

	if (!(flags & TupleFlags_Union))
	{
		let size = 0;

		if (tupleItems.length < 1)
		{
			size = pos;
		}
		else
		{
			size = GetTupleSize
			(
				tupleItems,
				flags,
				alignFunc
			);
		}

		if (size < tupleSize)
		{
			let diff = (tupleSize - size);
			if (diff)
			{
				c += Tabs() + "_(" + diff + ");" + NEW_LINE;
			}
		}
		else if
		(
			(tupleSize > 0) &&
			(size > tupleSize)
		)
		{
			console.log("size > tupleSize");
		}
	}

	if (!(flags & TupleFlags_NoScopeEnd))
	{
		ScopeEnd
		(
			"}",
			ScopeFlags_Semicolon
		);
	}
}




function GetVariableType(type)
{
	if (type == "float")
	{
		return "Float";
	}
	else if (type == "double")
	{
		return "Double";
	}

	let typename = "Unknown";

	let size = GetTypeSize(type);

	if (size == 1)
	{
		typename = "Byte";
	}
	else if
	(
		(size >= 2) &&
		(size <= 8)
	)
	{
		typename = size + " Bytes";
	}

	return typename;
}

function CreateCheatEntry
(
	description,
	hex,
	type,
	addr,
	offs = []
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

	if (offs.length < 1)
	{
		c += "</CheatEntry>" + NEW_LINE;

		return;
	}

	c += "<Offsets>" + NEW_LINE;

	for (let index = 0; index < offs.length; index++)
	{
		let off = offs[index];

		c += "<Offset>" + off + "</Offset>" + NEW_LINE;
	}

	c += "</Offsets>" + NEW_LINE;

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
	hideChildren = false
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

function CreateCheatEntries
(
	items,
	addr,
	offs      = [],
	pos       = 0,
	flags     = 0,
	alignFunc = DefaultAlignFunction
)
{
	for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
	{
		let item = items[itemIndex];

		let name   = item[0];
		let type   = item[1];
		let items2 = item[2];
		let off    = item[3];

		if (off != undefined)
		{
			pos = off;
		}

		if (off == undefined)
		{
			pos = alignFunc
			(
				pos,
				name,
				type
			);
		}

		if
		(
			(type.match(/^Size_\d+?$/)) ||
			(type == "ModelData") ||
			(type == "RecoveryData") ||
			(type == "StyleData") ||
			(type == "InputData") ||
			(type == "BodyPartData") ||
			(type == "CollisionData") ||
			(type == "ShadowData") ||
			(type == "PhysicsData") ||
			(type == "PhysicsLinkData") ||
			(type == "PhysicsMetadata *") ||
			(type == "struct")
		)
		{
			let size = GetTypeSize(type);
			let count = GetTypeCount(name);

			size *= count;

			if (!(flags & TupleFlags_NoIncPos))
			{
				pos += size;
			}

			continue;
		}
		else if (type == "vec4")
		{
			let size = GetTypeSize(type);
			let count = GetTypeCount(name);

			let pos2 = 0;

			let names =
			[
				"x",
				"y",
				"z",
				"a",
			];

			for (let index = 0; index < names.length; index++)
			{
				let description = name + " " + names[index];

				offs.unshift("");

				offs[0] = PositionName
				(
					pos,
					PositionFlags_Hex |
					PositionFlags_NoPrefix
				) + "+" +
				PositionName
				(
					pos2,
					PositionFlags_Hex |
					PositionFlags_NoPrefix
				);

				CreateCheatEntry
				(
					description,
					false,
					"Float",
					addr,
					offs
				);

				offs.shift();

				pos2 += GetTypeSize("float");
			}



			size *= count;

			if (!(flags & TupleFlags_NoIncPos))
			{
				pos += size;
			}

			continue;
		}
		else if (type == "union")
		{
			CreateCheatEntries
			(
				items2,
				addr,
				offs,
				pos,
				TupleFlags_NoIncPos,
				alignFunc
			);

			let size = GetTupleSize
			(
				items2,
				TupleFlags_GreatestSize,
				alignFunc
			);

			pos += size;

			continue;
		}
		else
		{
			if
			(
				(name == "") ||
				(name.substring(0, 1) == "[")
			)
			{
				name = "var_" +
				PositionName
				(
					pos,
					PositionFlags_Hex |
					PositionFlags_NoPrefix
				) + name;
			}

			let size = GetTypeSize(type);
			let count = GetTypeCount(name);



			let description = name;

			let hex = (type.match(/\*/)) ? true : false;

			let variableType = GetVariableType(type);
			if (variableType == "Unknown")
			{
				console.log("Unknown " + type);

				return;
			}

			if (count > 1)
			{
				let pos2 = 0;

				for (let index = 0; index < count; index++)
				{
					description = name.split("[")[0] + " " + lz(index);

					offs.unshift("");

					offs[0] = PositionName
					(
						pos,
						PositionFlags_Hex |
						PositionFlags_NoPrefix
					) + "+" +
					PositionName
					(
						pos2,
						PositionFlags_Hex |
						PositionFlags_NoPrefix
					);

					CreateCheatEntry
					(
						description,
						hex,
						variableType,
						addr,
						offs
					);

					offs.shift();

					pos2 += size;
				}
			}
			else
			{
				offs.unshift("");

				offs[0] = PositionName
				(
					pos,
					PositionFlags_Hex |
					PositionFlags_NoPrefix
				);

				CreateCheatEntry
				(
					description,
					hex,
					variableType,
					addr,
					offs
				);

				offs.shift();
			}



			size *= count;

			if (!(flags & TupleFlags_NoIncPos))
			{
				pos += size;
			}

			continue;
		}
	}

	return pos;
}



function CreateTypedef
(
	name,
	type,
	size,
	flags = 0
)
{
	c += Tabs() + "typedef " + type + " " + name + ";" + NEW_LINE;

	typeSizes.push([ name, size ]);

	if (flags & TypeFlags_NoAsserts)
	{
		return;
	}

	if (!(flags & TypeFlags_NoTypeAssert))
	{
		c_assertType += Tabs() + "static_assert(TypeMatch<" + name + ", " + type + ">::value);" + NEW_LINE;
	}

	if
	(
		!(flags & TypeFlags_NoSizeAssert) &&
		(size > 0)
	)
	{
		c_assertSize += Tabs() + "static_assert(sizeof(" + name + ") == " + size + ");" + NEW_LINE;
	}
}



function CreateWindowsPointerTypedefs
(
	name,
	flags = 0
)
{
	let items =
	[
		[ "P"   + name,            name + " *", TypeFlags_NoP   ],
		[ "LP"  + name,            name + " *", TypeFlags_NoLP  ],
		[ "LPC" + name, "const " + name + " *", TypeFlags_NoLPC ],
	];

	for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
	{
		let item = items[itemIndex];

		let newName = item[0];
		let newType = item[1];
		let newFlag = item[2];

		if (flags & newFlag)
		{
			continue;
		}

		CreateTypedef
		(
			newName,
			newType,
			8
		);
	}
}

function CreateWindowsTypedef
(
	name,
	type,
	size,
	flags = 0
)
{
	if (!(flags & TypeFlags_NoDefault))
	{
		CreateTypedef
		(
			name,
			type,
			size,
			flags
		);
	}

	if (!(flags & TypeFlags_NoPointers))
	{
		CreateWindowsPointerTypedefs
		(
			name,
			flags
		);
	}
	else
	{
		console.log("Skipping pointers.");
	}

	c += NEW_LINE;

	MergeAsserts();

	FeedAsserts();

	ClearAsserts();
}

function CreateWindowsTypedefs(items)
{
	for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
	{
		let item = items[itemIndex];

		let name  = item[0];
		let type  = item[1];
		let size  = item[2];
		let flags = item[3];

		CreateWindowsTypedef
		(
			name,
			type,
			size,
			flags
		);
	}
}



function CreateSpecs(declspec)
{
	for (let index = 0; index < declspec.length; index++)
	{
		let name = declspec[index];

		c += "__declspec(" + name + ") ";
	}
}

function CreateFunctionArguments
(
	items,
	flags = 0
)
{
	if
	(
		(items == undefined) ||
		(items.length == 0)
	)
	{
		c += "()";
	}
	else if (items.length == 1)
	{
		let item = items[0];

		let name = item[0];
		let type = item[1];

		c += "(" + type;

		if (name != "")
		{
			c += " " + name;
		}

		c += ")";
	}
	else
	{
		c += NEW_LINE;

		ScopeStart("(");

		for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
		{
			let item = items[itemIndex];

			let name = item[0];
			let type = item[1];

			c += Tabs() + type;

			if (name != "")
			{
				c += " " + name;
			}

			if (itemIndex < (items.length - 1))
			{
				c += ",";
			}

			c += NEW_LINE;
		}

		ScopeEnd
		(
			")",
			ScopeFlags_NoNewLine
		);
	}

	if (!(flags & FunctionFlags_NoSemicolon))
	{
		c += ";" + NEW_LINE;
	}
}

function CreateFunction
(
	name,
	type,
	items,
	flags = 0,
	declspec = []
)
{
	c += Tabs();

	if (flags & FunctionFlags_ExternC)
	{
		c += "extern \"C\" ";
	}

	if
	(
		(flags & FunctionFlags_Virtual) ||
		(flags & FunctionFlags_PureVirtual)
	)
	{
		c += "virtual ";
	}

	CreateSpecs(declspec);

	c += type + " " + name;

	CreateFunctionArguments
	(
		items,
		FunctionFlags_NoSemicolon
	);

	if (flags & FunctionFlags_PureVirtual)
	{
		c += " = 0";
	}

	c += ";" + NEW_LINE;
}

function CreateFunctions(items)
{
	for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
	{
		let item = items[itemIndex];

		let name     = item[0];
		let type     = item[1];
		let items2   = item[2];
		let flags    = item[3];
		let declspec = item[4];

		CreateFunction
		(
			name,
			type,
			items2,
			flags,
			declspec
		);
	}
}

function CreateFunctionTuple
(
	name,
	items,
	declspec = []
)
{
	c += Tabs() + "struct ";

	CreateSpecs(declspec);

	c += name + NEW_LINE;

	ScopeStart();

	CreateFunctions(items);

	ScopeEnd
	(
		"}",
		ScopeFlags_Semicolon
	);
}

function CreateFunctionTypedef
(
	name,
	type,
	items
)
{
	c += Tabs() + "typedef " + type + "(__stdcall * " + name + ")";

	CreateFunctionArguments(items);

	let size = 8;

	typeSizes.push([ name, size ]);

	CreateSizeAssert
	(
		name,
		size
	);
}

function CreateFunctionTypedefs(items)
{
	for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
	{
		let item = items[itemIndex];

		let name   = item[0];
		let type   = item[1];
		let items2 = item[2];

		CreateFunctionTypedef
		(
			name,
			type,
			items2
		);

		c += NEW_LINE;
	}
}

function CreateEnumItems(items)
{
	let newConst = "";
	let newAssert = "";

	for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
	{
		let item = items[itemIndex];

		let name  = item[0];
		let value = item[1];
		let type  = item[2];

		c += Tabs() + name + "=" + value + "," + NEW_LINE;

		if (type != "")
		{
			let newName = "__NEW_" + name + "__";

			newConst += "const auto " + newName + " = reinterpret_cast<" + type + ">(" + value + ");" + NEW_LINE;

			newAssert += "static_assert(" + newName + " == " + name + ");" + NEW_LINE;

			continue;
		}

		newAssert += "static_assert(" + name + " == " + value + ");" + NEW_LINE;
	}

	c_verify += newConst;
	c_verify += NEW_LINE;

	c_assertVerify += newAssert;
}

function CreateEnum
(
	name,
	items,
	flags = 0
)
{
	if (items.length < 1)
	{
		console.log("Empty Enum");

		return;
	}

	c += Tabs() + "enum";

	if (name != "")
	{
		c += " " + name;
	}

	c += NEW_LINE;

	ScopeStart();

	CreateEnumItems(items);

	ScopeEnd
	(
		"}",
		ScopeFlags_Semicolon
	);

	if (name != "")
	{
		let size = 4;

		typeSizes.push([ name, size ]);

		if (!(flags & EnumFlags_NoSizeAssert))
		{
			CreateSizeAssert
			(
				name,
				size
			);
		}
	}
}

function CreateWindowsFunctionTypedefs(items)
{
	CreateFunctionTypedefs(items);

	MergeAsserts();

	FeedAsserts();

	ClearAsserts();
}

function CreateWindowsEnum
(
	name,
	items,
	flags = 0
)
{
	CreateEnum
	(
		name,
		items,
		flags
	);

	MergeAsserts();

	FeedAsserts();

	ClearAsserts();
}

function CreateWindowsTuple
(
	name,
	items,
	tupleFlags = 0,
	typeFlags  = 0
)
{
	if (tupleFlags & TupleFlags_Union)
	{
		tupleFlags |= TupleFlags_GreatestSize;
		tupleFlags |= TupleFlags_NoIncPos;
	}

	CreateTuple
	(
		name,
		items,
		0,
		0,
		tupleFlags
	);

	c += NEW_LINE;

	CreateTupleAsserts
	(
		name,
		items,
		0,
		0,
		tupleFlags,
		0
	);

	let size = GetTupleSize
	(
		items,
		tupleFlags
	);

	typeSizes.push([ name, size ]);

	MergeAsserts();

	FeedAsserts();

	ClearAsserts();

	if (!(typeFlags & TypeFlags_NoPointers))
	{
		CreateWindowsPointerTypedefs
		(
			name,
			typeFlags
		);
	}

	MergeAsserts();

	FeedAsserts();

	ClearAsserts();
}

function CreateWindowsFunctionTuple
(
	name,
	items,
	declspec = []
)
{
	CreateFunctionTuple
	(
		name,
		items,
		declspec
	);

	c += NEW_LINE;

	let size = 8;

	let newName = name.replace(/ /g, "").split(":")[0];

	CreateSizeAssert
	(
		newName,
		size
	);

	MergeAsserts();

	FeedAsserts();

	ClearAsserts();
}



function LogTypeSizes()
{
	let items = typeSizes;


	for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
	{
		let item = items[itemIndex];

		let name = item[0];
		let size = item[1];

		console.log(lz(itemIndex) + " " + name + " " + size);
	}
}



function ModuleStart
(
	name,
	importNames    = [],
	namespaceNames = []
)
{
	c += "module;" + NEW_LINE;
	c += NEW_LINE;

	c += "#pragma warning(disable: 5202)" + NEW_LINE;
	c += NEW_LINE;

	c += "typedef unsigned char byte8;" + NEW_LINE;
	c += NEW_LINE;

	c += "template" + NEW_LINE;
	c += "<" + NEW_LINE;
	c += "\ttypename T1," + NEW_LINE;
	c += "\ttypename T2" + NEW_LINE;
	c += ">" + NEW_LINE;
	c += "struct TypeMatch" + NEW_LINE;
	c += "{" + NEW_LINE;
	c += "\tstatic constexpr bool value = false;" + NEW_LINE;
	c += "};" + NEW_LINE;
	c += NEW_LINE;

	c += "template <typename T>" + NEW_LINE;
	c += "struct TypeMatch<T, T>" + NEW_LINE;
	c += "{" + NEW_LINE;
	c += "\tstatic constexpr bool value = true;" + NEW_LINE;
	c += "};" + NEW_LINE;
	c += NEW_LINE;

	c += "#define offsetof(s, m) __builtin_offsetof(s, m)" + NEW_LINE;
	c += NEW_LINE;

	c += "#define _Prep_Merge(a, b) a##b" + NEW_LINE;
	c += "#define Prep_Merge(a, b) _Prep_Merge(a, b)" + NEW_LINE;
	c += NEW_LINE;

	c += "#define _(size) struct { byte8 Prep_Merge(padding_, __LINE__)[size]; }" + NEW_LINE;
	c += NEW_LINE;

	c += "#define namespaceStart(name) namespace name {" + NEW_LINE;
	c += "#define namespaceEnd() }" + NEW_LINE;
	c += NEW_LINE;

	c += "export module " + name + ";" + NEW_LINE;
	c += NEW_LINE;

	for (let importNameIndex = 0; importNameIndex < importNames.length; importNameIndex++)
	{
		let importName = importNames[importNameIndex];

		c += "import " + importName + ";" + NEW_LINE;
	}
	c += NEW_LINE;

	for (let namespaceNameIndex = 0; namespaceNameIndex < namespaceNames.length; namespaceNameIndex++)
	{
		let namespaceName = namespaceNames[namespaceNameIndex];

		c += "using namespace " + namespaceName + ";" + NEW_LINE;
	}
	c += NEW_LINE;

	c += "export namespaceStart(" + name + ");" + NEW_LINE;
	c += NEW_LINE;
}

function ModuleEnd()
{
	c += NEW_LINE;
	c += "namespaceEnd();" + NEW_LINE;
}

function ModuleVerify()
{
	c = "";

	c += "#include <Windows.h>" + NEW_LINE;
	c += "#include <TlHelp32.h>" + NEW_LINE;
	c += "#include <shellapi.h>" + NEW_LINE;
	c += "#include <dxgi.h>" + NEW_LINE;
	c += "#include <d3d11.h>" + NEW_LINE;
	c += "#include <d3dcompiler.h>" + NEW_LINE;
	c += "#define DIRECTINPUT_VERSION 0x800" + NEW_LINE;
	c += "#include <dinput.h>" + NEW_LINE;
	c += "#include <Xinput.h>" + NEW_LINE;

	c += NEW_LINE;

	c += "template" + NEW_LINE;
	c += "<" + NEW_LINE;
	c += "\ttypename T1," + NEW_LINE;
	c += "\ttypename T2" + NEW_LINE;
	c += ">" + NEW_LINE;
	c += "struct TypeMatch" + NEW_LINE;
	c += "{" + NEW_LINE;
	c += "\tstatic constexpr bool value = false;" + NEW_LINE;
	c += "};" + NEW_LINE;

	c += NEW_LINE;

	c += "template <typename T>" + NEW_LINE;
	c += "struct TypeMatch<T, T>" + NEW_LINE;
	c += "{" + NEW_LINE;
	c += "\tstatic constexpr bool value = true;" + NEW_LINE;
	c += "};" + NEW_LINE;

	c += NEW_LINE;

	c += c_verify;
}



function CreateForwardDeclaration
(
	name,
	type,
	prefix = "",
	namePrefix = ""
)
{
	c += Tabs() + prefix + type + " " + namePrefix + name + ";" + NEW_LINE;
}

function CreateForwardDeclarations
(
	names,
	type,
	prefix = "",
	namePrefix = ""
)
{
	for (let nameIndex = 0; nameIndex < names.length; nameIndex++)
	{
		let name = names[nameIndex];

		CreateForwardDeclaration
		(
			name,
			type,
			prefix,
			namePrefix
		);
	}

	c += NEW_LINE;
}
