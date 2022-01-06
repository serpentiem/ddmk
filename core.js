// #region

"use strict";

let child_process = require("child_process");
let fs            = require("fs"           );
let process       = require("process"      );



let g_platform    = "x86_64";
let g_pointerSize = 8;



const NEW_LINE = "\r\n";
const NEW_LINE_SIZE = 2;



let c            = "";
let c_assert     = "";
let c_assertType = "";
let c_assertOff  = "";
let c_assertSize = "";
let c_until      = "";
let c_after      = "";
let c_new        = "";

let file = "";



const StringFlags_Hex      = 1 << 0;
const StringFlags_NoPrefix = 1 << 1;

const ScopeFlags_Semicolon = 1 << 0;
const ScopeFlags_Comma     = 1 << 1;
const ScopeFlags_NoNewLine = 1 << 2;

const FunctionFlags_Virtual     = 1 << 0;
const FunctionFlags_PureVirtual = 1 << 1;
const FunctionFlags_ExternC     = 1 << 2;
const FunctionFlags_stdcall     = 1 << 3;

const StructFlags_GreatestSize   = 1 << 0;
const StructFlags_NoIncPos       = 1 << 1;
const StructFlags_Export         = 1 << 2;
const StructFlags_Union          = 1 << 3;
const StructFlags_NoScopeEnd     = 1 << 4;
const StructFlags_NoTypeAssert   = 1 << 5;
const StructFlags_NoOffsetAssert = 1 << 6;
const StructFlags_NoSizeAssert   = 1 << 7;
const StructFlags_NoVTable       = 1 << 8;

const DeclarationFlags_ExternC = 1 << 0;

const EnumFlags_Export           = 1 << 0;
const EnumFlags_Namespace        = 1 << 1;
const EnumFlags_UnknownItemIndex = 1 << 2;
const EnumFlags_UpperCase        = 1 << 3;
const EnumFlags_NoUnknown        = 1 << 4;

// #endregion



// #region String

function Clear()
{
	c = "";
}

function ClearAsserts()
{
	c_assert     = "";
	c_assertType = "";
	c_assertOff  = "";
	c_assertSize = "";
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
}

function FeedAsserts()
{
	c += c_assert;
	c += NEW_LINE;
}



function GetLines(buffer)
{
	let pattern = new RegExp(("[\\S\\s]*?" + NEW_LINE), "g");

	return buffer.match(pattern);
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

	return lines[lineIndex].substring(0, (lines[lineIndex].length - NEW_LINE_SIZE));
}



function Substring
(
	name,
	pos,
	size
)
{
	return name.substring(pos, (pos + size));
}



// @Busted
function ReplaceAll
(
	name,
	pattern,
	replace
)
{
	if (name == undefined)
	{
		console.log("name undefined");

		return "";
	}
	else if (name == "")
	{
		console.log("no name");

		return "";
	}
	else if (pattern == undefined)
	{
		console.log("pattern undefined");

		return "";
	}
	else if (pattern == "")
	{
		console.log("no pattern");

		return "";
	}



	let newPattern = new RegExp(pattern);

	while (true)
	{
		let match = name.match(newPattern);
		if (!match)
		{
			break;
		}

		name = name.replace(newPattern, replace);
	}



	return name;
}



function IsWhitespace(name)
{
	if (name.match(/ |\t|\r|\n/))
	{
		return true;
	}

	return false;
}

function IsAlphanumerical(name)
{
	if (name.match(/[A-Za-z0-9]/))
	{
		return true;
	}

	return false;
}

function IsFunctionGlyph(name)
{
	if (name.match(/[A-Za-z0-9_]/))
	{
		return true;
	}

	return false;
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

	if (flags & ScopeFlags_Comma)
	{
		c += ",";
	}

	if (!(flags & ScopeFlags_NoNewLine))
	{
		c += NEW_LINE;
	}
}



function RegionStart(name)
{
	c += "#pragma region " + name + NEW_LINE;
}

function RegionEnd()
{
	c += "#pragma endregion" + NEW_LINE;
}



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

function LeadingZero
(
	value,
	width = 4,
	flags = 0
)
{
	let name = "";
	let newName = "";



	if (flags & StringFlags_Hex)
	{
		name = value.toString(16).toUpperCase();
	}
	else
	{
		name = value.toString();
	}



	let count = (width - name.length);

	for (let index = 0; index < count; index++)
	{
		newName += "0";
	}



	newName = (newName + name);



	if
	(
		(flags & StringFlags_Hex) &&
		!(flags & StringFlags_NoPrefix)
	)
	{
		newName = ("0x" + newName);
	}



	return newName;
}



// @Todo: Integrate LeadingZero.
function PositionName
(
	pos,
	flags = 0
)
{
	let name = "";



	if (flags & StringFlags_Hex)
	{
		if (pos < 10)
		{
			name += pos.toString();
		}
		else
		{
			if (!(flags & StringFlags_NoPrefix))
			{
				name += "0x";
			}

			name += pos.toString(16).toUpperCase();
		}
	}
	else
	{
		name += pos.toString();
	}



	return name;
}



function MergeNames
(
	names,
	separator = ","
)
{
	let newName = "";

	for (let nameIndex = 0; nameIndex < names.length; nameIndex++)
	{
		let name = names[nameIndex];

		if
		(
			(name == undefined) ||
			(name == "")
		)
		{
			continue;
		}

		newName += name + separator;
	}

	if (newName == "")
	{
		return;
	}

	// At this point we know newName length will be at least (1 + separator length).

	return newName.substring(0, (newName.length - separator.length));
}



function ToPascalCase(name)
{
	let start = name.substring(0, 1          );
	let end   = name.substring(1, name.length);

	return (start.toUpperCase() + end);
}

function ToCamelCase(name)
{
	let start = name.substring(0, 1          );
	let end   = name.substring(1, name.length);

	return (start.toLowerCase() + end);
}



function NumericName(name)
{
	let items =
	[
		[ "zero" , "0" ],
		[ "one"  , "1" ],
		[ "two"  , "2" ],
		[ "three", "3" ],
		[ "four" , "4" ],
		[ "five" , "5" ],
		[ "six"  , "6" ],
		[ "seven", "7" ],
		[ "eight", "8" ],
		[ "nine" , "9" ],
	];

	for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
	{
		let item = items[itemIndex];

		let alphaName = item[0];
		let numName   = item[1];

		let pattern = new RegExp(alphaName, "i");

		if (name.match(pattern))
		{
			name = numName;

			break;
		}
	}

	return name;
}



function EnumItemName(name)
{
	name = ReplaceAll(name, "-", " ");

	name = ReplaceAll(name, "&", "");

	name = ReplaceAll(name, "  ", " ");

	name = ReplaceAll(name, " ", "_");

	name = ReplaceAll(name, "'", "");

	return name;
}



function CleanScopeGlyph
(
	name,
	glyph
)
{
	let escapedGlyph = "\\" + glyph;

	name = ReplaceAll
	(
		name,
		(" " + escapedGlyph),
		glyph
	);

	name = ReplaceAll
	(
		name,
		(escapedGlyph + " "),
		glyph
	);

	return name;
}

function CleanString(name)
{
	name = ReplaceAll(name, "\r", "");
	name = ReplaceAll(name, "\t", "");

	name = ReplaceAll(name, "\n", " ");

	name = ReplaceAll(name, "  ", " ");

	name = name.replace(/^ /, "");
	name = name.replace(/ $/, "");

	name = CleanScopeGlyph(name, "(");
	name = CleanScopeGlyph(name, ")");

	name = CleanScopeGlyph(name, "{");
	name = CleanScopeGlyph(name, "}");

	name = CleanScopeGlyph(name, "[");
	name = CleanScopeGlyph(name, "]");

	name = ReplaceAll(name, ",\\(", ", (");
	name = ReplaceAll(name, ",\\{", ", {");
	name = ReplaceAll(name, ",\\[", ", [");

	return name;
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

		c_new += line + NEW_LINE;
	}

	c = c_new;
}

// #endregion



// #region File System

function GetPath(location)
{
	if (location.length < 1)
	{
		return "";
	}

	let pos = location.lastIndexOf("/");

	if (pos < 1)
	{
		return "";
	}

	return location.substring(0, pos);
}

function GetFileName(location)
{
	if (location.length < 1)
	{
		return "";
	}

	let pos = (location.lastIndexOf("/") + 1);

	if (pos >= location.length)
	{
		return "";
	}

	return location.substring(pos, location.length);
}

function FilterByExtension
(
	fileNames,
	extension
)
{
	if (extension.length < 1)
	{
		return;
	}



	for (let index = 0; index < fileNames.length; index++)
	{
		let fileName = fileNames[index];

		function Remove()
		{
			fileNames.splice(index, 1);

			index--;
		}

		if
		(
			(fileName.length < (1 + extension.length)) ||
			!fileName.match(/\./)
		)
		{
			Remove();

			continue;
		}

		let newExtension = fileName.substring((fileName.lastIndexOf(".") + 1), fileName.length);

		if (newExtension != extension)
		{
			Remove();

			continue;
		}
	}
}

function DeleteByExtension
(
	location,
	extension
)
{
	let fileNames = fs.readdirSync(location);

	FilterByExtension(fileNames, extension);

	if (fileNames.length < 1)
	{
		console.log("No Files *." + extension);

		return true;
	}

	for (let index = 0; index < fileNames.length; index++)
	{
		let fileName = fileNames[index];

		let newLocation = location + "/" + fileName;

		fs.rmSync
		(
			newLocation,
			{
				recursive: true
			}
		);
	}

	console.log("Delete *." + extension);

	return false;
}

// #endregion



// #region Other

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



function GetFunctionName()
{
	let stack = new Error().stack;



	let matches = stack.match(/at [\S\s]+? \(/g);
	if (matches)
	{
		let name = matches[1].match(/at ([\S\s]+?) \(/)[1];

		return name;
	}



	return "";
}



function AddFront
(
	data,
	newData
)
{
	let old = [];

	for (let index = 0; index < data.length; index++)
	{
		old.push(data[index]);
	}

	data = [];

	for (let index = 0; index < newData.length; index++)
	{
		data.push(newData[index]);
	}

	for (let index = 0; index < old.length; index++)
	{
		data.push(old[index]);
	}

	return data;
}

// #endregion



// #region Tag

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
		let lastLineIndex = (lineIndex - 1);
		let nextLineIndex = (lineIndex + 1);

		let line     = GetLine(lines, lineIndex    );
		let lastLine = GetLine(lines, lastLineIndex);
		let nextLine = GetLine(lines, nextLineIndex);

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
		let lastLineIndex = (lineIndex - 1);
		let nextLineIndex = (lineIndex + 1);

		let line     = GetLine(lines, lineIndex    );
		let lastLine = GetLine(lines, lastLineIndex);
		let nextLine = GetLine(lines, nextLineIndex);

		c += line + NEW_LINE;
	}

	c += NEW_LINE;
}

function Tag_CopyAfter(lines)
{
	for (let lineIndex = Tag_end; lineIndex < lines.length; lineIndex++)
	{
		let lastLineIndex = (lineIndex - 1);
		let nextLineIndex = (lineIndex + 1);

		let line     = GetLine(lines, lineIndex    );
		let lastLine = GetLine(lines, lastLineIndex);
		let nextLine = GetLine(lines, nextLineIndex);

		c += line + NEW_LINE;
	}
}

// #endregion



// #region Feed

function FeedStart(tagName)
{
	let lines = GetLines(file);

	let startName = new RegExp("\\/\\/ \\$" + tagName + "Start$");
	let endName   = new RegExp("\\/\\/ \\$" + tagName + "End$"  );

	console.log(startName);
	console.log(endName);

	if
	(
		!Tag_Init
		(
			lines,
			startName,
			endName
		)
	)
	{
		console.log("Tag_Init failed.");

		process.exit(1);

		return;
	}



	Tag_CopyUntil(lines);

	c_until = c;

	ClearAll();



	Tag_CopyAfter(lines);

	c_after = c;

	ClearAll();
}

function FeedEnd()
{
	c_new = c;

	ClearAll();

	file = c_until + c_new + c_after;
}


// @Move
function FeedStruct
(
	name,
	items,
	size    = 0,
	tagName = name
)
{
	ClearAll();

	FeedStart(tagName);

	CreateStruct
	(
		name,
		items,
		size,
		0,
		StructFlags_Export
	);

	CreateStructAsserts
	(
		name,
		items,
		size,
		0,
		StructFlags_NoTypeAssert
	);

	MergeAsserts();
	FeedAsserts();

	CleanStream();

	FeedEnd();
}

function FeedEnum
(
	name,
	items,
	tagName = name
)
{
	ClearAll();

	FeedStart(tagName);

	CreateEnum
	(
		name,
		items,
		"",
		EnumFlags_Export    |
		EnumFlags_Namespace |
		EnumFlags_UpperCase
	);

	c += NEW_LINE;

	CleanStream();

	FeedEnd();
}

// #endregion



// #region Type

let typeSizes =
[
	[ "void"     , 0  ],
	[ "bool"     , 1  ],
	[ "int"      , 4  ],
	[ "char"     , 1  ],
	[ "short"    , 2  ],
	[ "long"     , 4  ],
	[ "long long", 8  ],
	[ "bool8"    , 1  ],
	[ "bool16"   , 2  ],
	[ "bool32"   , 4  ],
	[ "bool64"   , 8  ],
	[ "int8"     , 1  ],
	[ "int16"    , 2  ],
	[ "int32"    , 4  ],
	[ "int64"    , 8  ],
	[ "uint8"    , 1  ],
	[ "uint16"   , 2  ],
	[ "uint32"   , 4  ],
	[ "uint64"   , 8  ],
	[ "byte8"    , 1  ],
	[ "byte16"   , 2  ],
	[ "byte32"   , 4  ],
	[ "byte64"   , 8  ],
	[ "float"    , 4  ],
	[ "vec4"     , 16 ],
];

function typeSizes_Copy()
{
	let dest = [];

	let items = typeSizes;

	for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
	{
		let item = items[itemIndex];

		let name = item[0];
		let size = item[1];

		dest.push([ name, size ]);
	}

	return dest;
}

function typeSizes_Add(items)
{
	for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
	{
		let item = items[itemIndex];

		let name = item[0];
		let size = item[1];

		typeSizes.push([ name, size ]);
	}
}

function typeSizes_Set(data)
{
	typeSizes = [];

	typeSizes_Add(data);
}

let defaultTypeSizes = typeSizes_Copy();

function typeSizes_Reset()
{
	typeSizes_Set(defaultTypeSizes);
}

function typeSizes_List(items)
{
	for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
	{
		let item = items[itemIndex];

		let name = item[0];
		let size = item[1];

		console.log(name + " " + size);
	}
}



function GetTypeSize(name)
{
	if (name == "")
	{
		console.log(GetFunctionName() + " No Name");

		return 0;
	}

	name = name.replace(/(const|signed|unsigned) /g, "");

	if (name.match(/\*/))
	{
		return g_pointerSize;
	}

	{
		let match = name.match(/^Size_(\d+?)$/);
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

		let name2 = item[0];
		let size  = item[1];

		if (name2 == name)
		{
			return size;
		}
	}

	console.log(GetFunctionName() + " Unknown " + name);

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

// #endregion



// #region Function

function CreateFunctionArguments(items)
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
}

function CreateFunction(item)
{
	let name  = item[0];
	let type  = item[1];
	let items = item[2];
	let flags = item[3];

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

	//c += type + " " + name;




	c += type;

	if (g_platform == "x86_32")
	{
		if (flags & FunctionFlags_stdcall)
		{
			c += " __stdcall";
		}
	}

	c += " " + name;













	CreateFunctionArguments(items);

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

		CreateFunction(item);
	}
}

// #endregion



// #region Struct

/*
pos can be set manually for inheritance.

Sometimes a struct will contain data from other structs and that data also
contributes to the total size of it.
*/

function GetStructSize
(
	items,
	pos   = 0,
	flags = 0
)
{
	let greatestTypeSize = 0;



	for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
	{
		let item = items[itemIndex];

		let name   = item[0];
		let type   = item[1];
		let items2 = item[2];
		let off    = item[3];



		let size = 0;

		if (off != undefined)
		{
			pos = off;
		}



		{
			let match = name.match(/_\((\d+?)\)/);
			if (match)
			{
				if
				(
					(type != "") &&
					(type != g_platform)
				)
				{
					continue;
				}

				size = parseInt(match[1]);

				pos += size;

				continue;
			}
		}



		if (type == "struct")
		{
			size = GetStructSize(items2);

			if (size > greatestTypeSize)
			{
				greatestTypeSize = size;
			}
		}
		else if (type == "union")
		{
			size = GetStructSize
			(
				items2,
				0,
				StructFlags_GreatestSize
			);
		}
		else if (type == "func")
		{
			continue;
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



	if (flags & StructFlags_GreatestSize)
	{
		return greatestTypeSize;
	}



	return pos;
}



function CreateStructContent
(
	items,
	pos   = 0,
	flags = 0
)
{
	let lastPos = pos;



	for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
	{
		let item = items[itemIndex];

		let name   = item[0];
		let type   = item[1];
		let items2 = item[2];
		let off    = item[3];

		let size = 0;



		if (off != undefined)
		{
			pos = off;
		}



		{
			let match = name.match(/_\((\d+?)\)/);
			if (match)
			{
				if
				(
					(type != "") &&
					(type != g_platform)
				)
				{
					continue;
				}

				size = parseInt(match[1]);

				c += Tabs() + "_(" + size + ");" + NEW_LINE;

				pos += size;

				lastPos = pos;

				continue;
			}
		}



		let diff = (pos - lastPos);
		if (diff)
		{
			c += Tabs() + "_(" + diff + ");" + NEW_LINE;
		}



		if (type == "struct")
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

			CreateStructContent
			(
				items2,
				pos
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
				StringFlags_Hex
			);

			c += NEW_LINE;



			size = GetStructSize(items2);
		}
		else if (type == "union")
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

			CreateStructContent
			(
				items2,
				pos,
				StructFlags_NoIncPos
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
				StringFlags_Hex
			);

			c += NEW_LINE;



			size = GetStructSize
			(
				items2,
				0,
				StructFlags_GreatestSize
			);
		}
		else if (type == "func")
		{
			CreateFunctions(items2);

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
					StringFlags_Hex |
					StringFlags_NoPrefix
				) +
				name;
			}

			c += Tabs() + type + " " + name + ";";



			c += " // " +
			PositionName
			(
				pos,
				StringFlags_Hex
			);

			c += NEW_LINE;



			let typeSize = GetTypeSize(type);

			let typeCount = GetTypeCount(name);

			size = (typeSize * typeCount);
		}



		if (!(flags & StructFlags_NoIncPos))
		{
			pos += size;

			lastPos = pos;
		}
	}
}



function CreateStruct
(
	name,
	items,
	size  = 0,
	pos   = 0,
	flags = 0
)
{
	c += Tabs();

	if (flags & StructFlags_Export)
	{
		c += "export ";
	}

	if (flags & StructFlags_Union)
	{
		c += "union";
	}
	else
	{
		c += "struct";
	}

	if (flags & StructFlags_NoVTable)
	{
		c += " __declspec(novtable)";
	}

	c += " " + name + NEW_LINE;

	ScopeStart();



	CreateStructContent
	(
		items,
		pos,
		flags
	);



	if
	(
		(size != 0) &&
		!(flags & StructFlags_Union)
	)
	{
		let size2 = GetStructSize
		(
			items,
			pos
		);




		// console.log("size  " + PositionName(size , StringFlags_Hex));
		// console.log("pos   " + PositionName(pos  , StringFlags_Hex));
		// console.log("size2 " + PositionName(size2, StringFlags_Hex));
		// console.log();







		if (size2 < size)
		{
			let diff = (size - size2);
			if (diff)
			{
				c += Tabs() + "_(" + diff + ");" + NEW_LINE;
			}
		}
	}



	if (!(flags & StructFlags_NoScopeEnd))
	{
		ScopeEnd
		(
			"}",
			ScopeFlags_Semicolon
		);
	}
}

// #endregion



// #region Asserts

function CreateTypeAssert
(
	name,
	type
)
{





	let count = "";

	{
		let matches = name.match(/(?:\[\d+?\])+?(?!(?:\[\d+?\]))/);
		if (matches)
		{


			// console.log("$" + name + "$");
			// console.log("$" + type + "$");


			name = name.replace(matches[0], "");
			count = matches[0];

			// console.log("new $" + name + "$");
			// console.log("new $" + count + "$");
		}
	}

	c_assertType += Tabs() + "static_assert(TypeMatch<" + name + ", ";

	c_assertType += type + count + ">::value);" + NEW_LINE;
}



function CreateOffsetAssert
(
	structName,
	name,
	off
)
{
	let newName = name.split("[")[0];

	c_assertOff += Tabs() + "static_assert(offsetof(" + structName + ", " + newName + ") == ";

	c_assertOff += PositionName
	(
		off,
		StringFlags_Hex
	);

	c_assertOff += ");" + NEW_LINE;
}

function CreateSizeAssert
(
	name,
	size,
	flags = 0
)
{
	c_assertSize += Tabs() + "static_assert(sizeof(" + name + ") == ";

	c_assertSize += PositionName
	(
		size,
		flags
	);

	c_assertSize += ");" + NEW_LINE;
}



function CreateStructContentAsserts
(
	name,
	items,
	pos   = 0,
	flags = 0
)
{
	for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
	{
		let item = items[itemIndex];

		let name2  = item[0];
		let type   = item[1];
		let items2 = item[2];
		let off    = item[3];

		let size = 0;



		if (off != undefined)
		{
			pos = off;
		}



		{
			let match = name2.match(/_\((\d+?)\)/);
			if (match)
			{
				if
				(
					(type != "") &&
					(type != g_platform)
				)
				{
					// console.log("assert ignore padding " + type + " " + g_platform);

					// for (let index = 0; index < typeSizes.length; index++)
					// {
					// 	let typeSize = typeSizes[index];

					// 	let name = typeSize[0];
					// 	let size = typeSize[1];

					// 	if (name == "LPVOID")
					// 	{
					// 		console.log(name + " " + size);

					// 		break;
					// 	}
					// }

					continue;
				}

				size = parseInt(match[1]);

				pos += size;

				continue;
			}
		}



		if (type == "struct")
		{
			let newFlags = 0;

			newFlags |= GetFlagIf
			(
				flags,
				StructFlags_NoTypeAssert
			);

			newFlags |= GetFlagIf
			(
				flags,
				StructFlags_NoOffsetAssert
			);

			CreateStructContentAsserts
			(
				name,
				items2,
				pos,
				newFlags
			);

			size = GetStructSize(items2);
		}
		else if (type == "union")
		{
			let newFlags = StructFlags_NoIncPos;

			newFlags |= GetFlagIf
			(
				flags,
				StructFlags_NoTypeAssert
			);

			newFlags |= GetFlagIf
			(
				flags,
				StructFlags_NoOffsetAssert
			);

			CreateStructContentAsserts
			(
				name,
				items2,
				pos,
				newFlags
			);

			size = GetStructSize
			(
				items2,
				0,
				StructFlags_GreatestSize
			);
		}
		else if (type == "func")
		{
			continue;
		}
		else
		{
			if
			(
				(name2 == "") ||
				(name2.substring(0, 1) == "[")
			)
			{
				name2 = "var_" +
				PositionName
				(
					pos,
					StringFlags_Hex |
					StringFlags_NoPrefix
				) +
				name2;
			}

			if (!(flags & StructFlags_NoTypeAssert))
			{
				CreateTypeAssert
				(
					("decltype(" + name + "::" + name2 + ")"),
					type
				);
			}

			if (!(flags & StructFlags_NoOffsetAssert))
			{
				CreateOffsetAssert
				(
					name,
					name2,
					pos
				);
			}



			let typeSize = GetTypeSize(type);

			let typeCount = GetTypeCount(name2);

			size = (typeSize * typeCount);
		}



		if (!(flags & StructFlags_NoIncPos))
		{
			pos += size;
		}
	}
}

function CreateStructAsserts
(
	name,
	items,
	size          = 0,
	pos           = 0,
	flags         = 0,
	positionFlags = 0
)
{
	CreateStructContentAsserts
	(
		name,
		items,
		pos,
		flags
	);



	if (!(flags & StructFlags_NoSizeAssert))
	{
		if (size == 0)
		{
			size = GetStructSize(items); // @Research: Shouldn't this take pos and flags as well?
		}

		CreateSizeAssert
		(
			name,
			size,
			positionFlags
		);
	}
}

// #endregion



// #region Typedef

function CreateTypedef
(
	name,
	type,
	size
)
{
	c += Tabs() + "typedef " + type + " " + name + ";" + NEW_LINE;

	typeSizes.push([ name, size ]);
}

function CreateFunctionTypedef
(
	name,
	type,
	items,
	flags = 0
)
{
	c += Tabs() + "typedef " + type + "(";

	if (g_platform == "x86_32")
	{
		if (flags & FunctionFlags_stdcall)
		{
			c += "__stdcall ";
		}
	}

	c += "* " + name + ")";

	CreateFunctionArguments(items);

	c += ";" + NEW_LINE;

	typeSizes.push([ name, g_pointerSize ]);
}

// #endregion



// #region Declaration

function CreateDeclaration
(
	name,
	type,
	flags = 0
)
{
	c += Tabs();

	if (flags & DeclarationFlags_ExternC)
	{
		c += "extern \"C\" ";
	}

	c += type + " " + name + ";" + NEW_LINE;
}

function CreateDeclarations
(
	names,
	type,
	prefix = "",
	flags = 0
)
{
	for (let nameIndex = 0; nameIndex < names.length; nameIndex++)
	{
		let name = names[nameIndex];

		CreateDeclaration
		(
			(prefix + name),
			type,
			flags
		);
	}

	c += NEW_LINE;
}

// #endregion



// #region Enum

function CreateEnum
(
	name,
	items,
	prefix = "",
	flags  = 0
)
{
	let exportName = "";

	if (flags & EnumFlags_Export)
	{
		exportName = "export ";
	}



	if (flags & EnumFlags_Namespace)
	{
		c += Tabs() + exportName + "namespaceStart(" + name + ");" + NEW_LINE;
		c += Tabs() + "enum" + NEW_LINE;
	}
	else
	{
		c += Tabs() + exportName + "enum";

		if (name != "")
		{
			c += " " + name;
		}

		c += NEW_LINE;
	}



	ScopeStart();

	let unknownIndex = 0;

	for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
	{
		let item = items[itemIndex];

		let name2 = item[0];
		let value = item[1];



		if (!(flags & EnumFlags_NoUnknown))
		{
			if
			(
				(name2 == "") ||
				name2.match(/unknown/i)
			)
			{
				if (flags & EnumFlags_UnknownItemIndex)
				{
					name2 = "unknown_" + itemIndex;
				}
				else
				{
					name2 = "unknown_" + unknownIndex;

					unknownIndex++;
				}
			}
		}



		name2 = EnumItemName(name2);


		name2 = prefix + name2;



		if (flags & EnumFlags_UpperCase)
		{
			name2 = name2.toUpperCase();
		}



		c += Tabs() + name2;

		if (value != "")
		{
			// @Restore
			// c += " = " + value;
			c += "=" + value;
		}

		c += "," + NEW_LINE;
	}

	ScopeEnd
	(
		"}",
		ScopeFlags_Semicolon
	);



	if (flags & EnumFlags_Namespace)
	{
		c += "namespaceEnd();" + NEW_LINE;
	}
}









// #endregion



// #region Cheat Engine

function CE_GetVariableType(name)
{
	if (name == "")
	{
		console.log(GetFunctionName() + " No Name");

		return "";
	}
	else if (name == "float")
	{
		return "Float";
	}
	else if (name == "double")
	{
		return "Double";
	}



	let size = GetTypeSize(name);

	let name2 = "Void";

	if (size == 1)
	{
		name2 = "Byte";
	}
	else if
	(
		(size >= 2) &&
		(size <= 8)
	)
	{
		name2 = size + " Bytes";
	}

	return name2;
}





function CE_CheatTableStart()
{
	c += "<?xml version=\"1.0\" encoding=\"utf-8\"?>" + NEW_LINE;
	c += "<CheatTable>" + NEW_LINE;
	c += "<CheatEntries>" + NEW_LINE;
}

function CE_CheatTableEnd()
{
	c += "</CheatEntries>" + NEW_LINE;
	c += "</CheatTable>" + NEW_LINE;
}

function CE_GroupStart
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

function CE_GroupEnd()
{
	c += "</CheatEntries>" + NEW_LINE;
	c += "</CheatEntry>" + NEW_LINE;
}

function CE_CreateCheatEntry
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

function CE_CreateCheatEntries
(
	items,
	addr,
	offs  = [],
	pos   = 0,
	flags = 0
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



		{
			let match = name.match(/_\((\d+?)\)/);
			if (match)
			{
				if
				(
					(type != "") &&
					(type != g_platform)
				)
				{
					continue;
				}

				let size = parseInt(match[1]);

				pos += size;

				continue;
			}
		}



		if
		(
			(type.match(/^Size_\d+?$/)) ||
			(type == "ModelData"        ) ||
			(type == "RecoveryData"     ) ||
			(type == "StyleData"        ) ||
			(type == "InputData"        ) ||
			(type == "BodyPartData"     ) ||
			(type == "CollisionData"    ) ||
			(type == "ShadowData"       ) ||
			(type == "PhysicsData"      ) ||
			(type == "PhysicsLinkData"  ) ||
			(type == "PhysicsMetadata *") ||
			(type == "LockOnData"       ) ||
			(type == "struct"           )
		)
		{
			let size = GetTypeSize(type);
			let count = GetTypeCount(name);

			size *= count;

			if (!(flags & StructFlags_NoIncPos))
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
					StringFlags_Hex |
					StringFlags_NoPrefix
				) + "+" +
				PositionName
				(
					pos2,
					StringFlags_Hex |
					StringFlags_NoPrefix
				);

				CE_CreateCheatEntry
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

			if (!(flags & StructFlags_NoIncPos))
			{
				pos += size;
			}

			continue;
		}
		else if (type == "union")
		{
			CE_CreateCheatEntries
			(
				items2,
				addr,
				offs,
				pos,
				StructFlags_NoIncPos
			);

			let size = GetStructSize
			(
				items2,
				StructFlags_GreatestSize
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
					StringFlags_Hex |
					StringFlags_NoPrefix
				) + name;
			}

			let size = GetTypeSize(type);
			let count = GetTypeCount(name);



			let description = name;

			let hex = (type.match(/\*/)) ? true : false;

			let variableType = CE_GetVariableType(type);
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
						StringFlags_Hex |
						StringFlags_NoPrefix
					) + "+" +
					PositionName
					(
						pos2,
						StringFlags_Hex |
						StringFlags_NoPrefix
					);

					CE_CreateCheatEntry
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
					StringFlags_Hex |
					StringFlags_NoPrefix
				);

				CE_CreateCheatEntry
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

			if (!(flags & StructFlags_NoIncPos))
			{
				pos += size;
			}

			continue;
		}
	}

	return pos;
}

// #endregion
