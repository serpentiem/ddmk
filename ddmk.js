
// @Todo: default libs.




// #region

ClearAll();



const PrepFlags_IgnoreSemicolon = 1 << 0;


const LinkFlags_Static = 1 << 0;



const PATH_ZLIB   = "ThirdParty/zlib";
const PATH_LIBZIP = "ThirdParty/libzip";
const PATH_IMGUI  = "ThirdParty/ImGui";
const PATH_STB    = "ThirdParty/stb";

const LOCATION_ZLIB          = "zlib.lib";
const LOCATION_LIBZIP        = "libzip.lib";
const LOCATION_HDC           = "D:/__STEAM__/steamapps/common/Devil May Cry HD Collection";
const LOCATION_4             = "D:/__STEAM__/steamapps/common/Devil May Cry 4";
const LOCATION_LOADER_X86_64 = LOCATION_HDC + "/dinput8.dll";
const LOCATION_LOADER_X86_32 = LOCATION_4   + "/dinput8.dll";
const LOCATION_EVA           = LOCATION_HDC + "/Eva.dll";
const LOCATION_LUCIA         = LOCATION_HDC + "/Lucia.dll";
const LOCATION_MARY          = LOCATION_HDC + "/Mary.dll";
const LOCATION_KYRIE         = LOCATION_4   + "/Kyrie.dll";

const LOCATION_EVA_PDB   = LOCATION_HDC + "/Eva.pdb";
const LOCATION_LUCIA_PDB = LOCATION_HDC + "/Lucia.pdb";
const LOCATION_MARY_PDB  = LOCATION_HDC + "/Mary.pdb";
const LOCATION_KYRIE_PDB = LOCATION_4   + "/Kyrie.pdb";








const debug = false;

function Log(name)
{
	console.log(name);
}

function DebugLog(name)
{
	if (!debug)
	{
		return;
	}

	Log(name);
}

// #endregion



// #region Config

let config =
{
	platform: "x86_64",
};

let configLocation = "config.json";



function SaveConfig()
{
	console.log(GetFunctionName());

	let name = JSON.stringify(config);

	fs.writeFileSync(configLocation, name);
}

function LoadConfig()
{
	console.log(GetFunctionName());

	try
	{
		let name = fs.readFileSync(configLocation, "utf8");

		config = JSON.parse(name);
	}
	catch(error)
	{
		console.log("fs.readFileSync failed. " + error.code + " $" + error.path + "$");

		SaveConfig();

		return;
	}
}

// #endregion



// #region Env

const VISUAL_STUDIO_YEAR    = "2019";
const VISUAL_STUDIO_EDITION = "Community";
const VISUAL_STUDIO_PATH    = "C:/Program Files (x86)/Microsoft Visual Studio/" + VISUAL_STUDIO_YEAR + "/" + VISUAL_STUDIO_EDITION;



/*
14.26.28801
14.27.29110
14.28.29333
14.29.29917
14.29.30037
14.29.30133
*/

const MSVC_VERSION      = "14.29.30133";
const MSVC_PATH         = VISUAL_STUDIO_PATH + "/VC/Tools/MSVC";
const MSVC_INCLUDE_PATH = MSVC_PATH + "/" + MSVC_VERSION + "/include";
const MSVC_LIB_PATH     = MSVC_PATH + "/" + MSVC_VERSION + "/lib";



/*
10.0.17763.0
10.0.18362.0
10.0.19041.0
*/

const WSDK_VERSION      = "10.0.18362.0";
const WSDK_PATH         = "C:/Program Files (x86)/Windows Kits/10";
const WSDK_INCLUDE_PATH = WSDK_PATH + "/Include/" + WSDK_VERSION;
const WSDK_LIB_PATH     = WSDK_PATH + "/Lib/"     + WSDK_VERSION;



let pathLocations_x86_64 =
[
	"C:/Windows",
	"C:/Windows/System32",
	MSVC_PATH + "/" + MSVC_VERSION + "/bin/Hostx64/x64",
];

let includeLocations_x86_64 =
[
	MSVC_INCLUDE_PATH,
	WSDK_INCLUDE_PATH + "/shared",
	WSDK_INCLUDE_PATH + "/ucrt",
	WSDK_INCLUDE_PATH + "/um",
	WSDK_INCLUDE_PATH + "/winrt",
];

let libLocations_x86_64 =
[
	MSVC_LIB_PATH + "/x64",
	WSDK_LIB_PATH + "/ucrt/x64",
	WSDK_LIB_PATH + "/um/x64",
];



let pathLocations_x86_32 =
[
	"C:/Windows",
	"C:/Windows/System32",
	MSVC_PATH + "/" + MSVC_VERSION + "/bin/Hostx64/x86",
];

let includeLocations_x86_32 =
[
	MSVC_INCLUDE_PATH,
	WSDK_INCLUDE_PATH + "/shared",
	WSDK_INCLUDE_PATH + "/ucrt",
	WSDK_INCLUDE_PATH + "/um",
	WSDK_INCLUDE_PATH + "/winrt",
];

let libLocations_x86_32 =
[
	MSVC_LIB_PATH + "/x86",
	WSDK_LIB_PATH + "/ucrt/x86",
	WSDK_LIB_PATH + "/um/x86",
];



function SetEnv_Feed(names)
{
	let newName = "";

	for (let nameIndex = 0; nameIndex < names.length; nameIndex++)
	{
		let name = names[nameIndex];

		newName += name + ";";
	}

	newName = newName.substring(0, (newName.length - 1));

	newName = newName.replace(/\//g, "\\");

	return newName;
}

function SetEnv(name)
{
	let path    = "";
	let include = "";
	let lib     = "";



	if (name == "x86_64")
	{
		path    = SetEnv_Feed(pathLocations_x86_64   );
		include = SetEnv_Feed(includeLocations_x86_64);
		lib     = SetEnv_Feed(libLocations_x86_64    );
	}
	else if (name == "x86_32")
	{
		path    = SetEnv_Feed(pathLocations_x86_32   );
		include = SetEnv_Feed(includeLocations_x86_32);
		lib     = SetEnv_Feed(libLocations_x86_32    );
	}



	process.env.PATH    = path;
	process.env.INCLUDE = include;
	process.env.LIB     = lib;
}

// #endregion



LoadConfig();

SetEnv(config.platform);

console.log(config.platform);



console.log("set PATH="    + process.env.PATH   );
console.log("set INCLUDE=" + process.env.INCLUDE);
console.log("set LIB="     + process.env.LIB    );



// #region PrepHelper

let PrepHelper_funcName  = "";
let PrepHelper_lineIndex = 0;
let PrepHelper_argCount  = 0;



function PrepHelper_Check
(
	argMin = 0,
	argMax = 0
)
{
	if
	(
		(argMin < 1) &&
		(argMax < 1)
	)
	{
		return false;
	}

	let funcName  = PrepHelper_funcName;
	let lineIndex = PrepHelper_lineIndex;
	let argCount  = PrepHelper_argCount;



	if (argCount < argMin)
	{
		console.log(funcName);
		console.log(lineIndex + ": Too few arguments.");

		console.log("argCount " + argCount);
		console.log("argMin   " + argMin);

		return true;
	}
	else if (argCount > argMax)
	{
		console.log(funcName);
		console.log(lineIndex + ": Too many arguments.");

		console.log("argCount " + argCount);
		console.log("argMax   " + argMax);

		return true;
	}
}

// #endregion

// #region All

function ResetConfigHelper
(
	dest,
	source,
	name
)
{
	c += Tabs() + "CopyMemory" + NEW_LINE;

	ScopeStart("(");

	c += Tabs() + "&" + dest + "Config." + name + "," + NEW_LINE;
	c += Tabs() + "&" + source + "Config." + name + "," + NEW_LINE;
	c += Tabs() + "sizeof(" + dest + "Config." + name + ")" + NEW_LINE;

	ScopeEnd
	(
		")",
		ScopeFlags_Semicolon
	);
}



let helpersAll =
[

["IntroduceData", (args) =>
{
	// IntroduceData(baseAddrName, dataName, dataType, return);
	// IntroduceData(baseAddrName, baseAddrSource, dataName, dataType, return);

	if (PrepHelper_Check(4, 5))
	{
		return true;
	}

	let argCount  = PrepHelper_argCount;

	let baseAddrName   = "";
	let baseAddrSource = "";
	let dataName       = "";
	let dataType       = "";
	let returnal       = "";

	if (argCount == 4)
	{
		baseAddrName = args[0];
		dataName     = args[1];
		dataType     = args[2];
		returnal     = args[3];
	}
	else if (argCount == 5)
	{
		baseAddrName   = args[0];
		baseAddrSource = args[1];
		dataName       = args[2];
		dataType       = args[3];
		returnal       = args[4];

		c += Tabs() + "auto " + baseAddrName + " = " + baseAddrSource + ";" + NEW_LINE;
	}

	c += Tabs() + "if (!" + baseAddrName + ")" + NEW_LINE;

	ScopeStart();

	c += Tabs() + returnal + ";" + NEW_LINE;

	ScopeEnd();

	c += Tabs() + "auto & " + dataName + " = *reinterpret_cast<" + dataType + " *>(" + baseAddrName + ");";

	return false;
}],

[ "ResetConfig", (args) =>
{
	// ResetConfig(name);

	if (PrepHelper_Check(1, 1))
	{
		return true;
	}

	let name = args[0];

	ResetConfigHelper
	(
		"queued",
		"default",
		name
	);

	ResetConfigHelper
	(
		"active",
		"queued",
		name
	);

	return false;
}],

[ "ResetActiveConfig", (args) =>
{
	// ResetActiveConfig(name);

	if (PrepHelper_Check(1, 1))
	{
		return true;
	}

	let name = args[0];

	ResetConfigHelper
	(
		"active",
		"queued",
		name
	);

	return false;
}],

[ "ResetQueuedConfig", (args) =>
{
	// ResetQueuedConfig(name);

	if (PrepHelper_Check(1, 1))
	{
		return true;
	}

	let name = args[0];

	ResetConfigHelper
	(
		"queued",
		"default",
		name
	);

	return false;
}],


["Prep_arg", (args) =>
{
	// Prep_arg(name);

	if (PrepHelper_Check(1, 1))
	{
		return true;
	}

	let argCount = PrepHelper_argCount;

	let name = args[0];

	c += name + "_";

	return false;
},
PrepFlags_IgnoreSemicolon
],














];

// #endregion

// #region Prep

let Prep = new function()
{

let buffer = "";
let bufferSize = 0;

let pos = 0;
let lastPos = pos;

let start = -1;
let end   = -1;

let startArgs = -1;
let endArgs   = -1;

let args = [];
let arg = "";



function Feed(size = 1)
{
	c += Substring(buffer, pos, size);
}

function InRange()
{
	if (pos < bufferSize)
	{
		return true;
	}

	return false;
}

function GetTabCount()
{
	let count = 0;

	lastPos = pos;

	pos--;

	while (pos >= 0)
	{
		let name = Substring(buffer, pos, 1);

		if (name.match(/\t/))
		{
			count++;
		}
		else
		{
			break;
		}

		pos--;
	}

	pos = lastPos;

	return count;
}



// Single-line comment does not include terminating glyphs.

// Returns true if a comment is found. Position will then be behind the comment.

function FeedComment(feed = true)
{
	if (pos >= bufferSize)
	{
		return false;
	}

	let start = 0;
	let end   = bufferSize;



	let nextPos = (pos + 1);

	let name = Substring(buffer, pos, 1);
	let nextName = "";

	if (nextPos < bufferSize)
	{
		nextName = Substring(buffer, nextPos, 1);
	}



	if
	(
		(name == "/") &&
		(nextName == "/")
	)
	{
		start = pos;

		pos += 2;

		while (pos < bufferSize)
		{
			let nextPos = (pos + 1);

			let name = Substring(buffer, pos, 1);
			let nextName = "";

			if (nextPos < bufferSize)
			{
				nextName = Substring(buffer, nextPos, 1);
			}

			if
			(
				name.match(/\r/) &&
				nextName.match(/\n/)
			)
			{
				end = pos;

				break;
			}
			else if (name.match(/\n/))
			{
				end = pos;

				break;
			}

			pos++;
		}

		let size = (end - start);

		let comment = Substring(buffer, start, size);

		if (feed)
		{
			c += comment;
		}

		return true;
	}
	else if
	(
		(name == "/") &&
		(nextName == "*")
	)
	{
		start = pos;

		pos += 2;

		while (pos < bufferSize)
		{
			let nextPos = (pos + 1);

			let name = Substring(buffer, pos, 1);
			let nextName = "";

			if (nextPos < bufferSize)
			{
				nextName = Substring(buffer, nextPos, 1);
			}

			if
			(
				(name == "*") &&
				(nextName == "/")
			)
			{
				end = pos;

				break;
			}

			pos++;
		}

		let size = (end - start);

		let comment = Substring(buffer, start, size);

		if (feed)
		{
			c += comment;
		}

		return true;
	}

	return false;
}

function SkipComment()
{
	return FeedComment(false);
}



this.GetLineIndex = function()
{
	let lineIndex = 1;

	for (let index = 0; index < pos; index++)
	{
		let name = Substring(buffer, index, 1);
		if (name.match(/\n/))
		{
			lineIndex++;
		}
	}

	return lineIndex;
}



// All ReplaceFunction functions return true on error.

function ReplaceFunctionOnce
(
	tag,
	func,
	flags = 0
)
{
	DebugLog(GetFunctionName() + " Start");

	let tagSize = tag.length;

	start = -1;
	end   = -1;

	startArgs = -1;
	endArgs   = -1;

	let scopeLevel = 1;

	args = [];
	arg = "";



	// Find tag.

	while (pos < bufferSize)
	{
		if (FeedComment())
		{
			continue;
		}

		// At this point we know it's not a comment and we are still within bounds.



		// If there is not enough room, feed the remaining buffer and return.

		if ((pos + tagSize) >= bufferSize)
		{
			DebugLog("Not enough room.");

			let size = (bufferSize - pos);

			Feed(size);

			pos += size;

			DebugLog("pos        " + pos);
			DebugLog("bufferSize " + bufferSize);

			return false;
		}



		let name = Substring(buffer, pos, tagSize);
		if (name == tag)
		{
			start = pos;

			break;
		}



		Feed();

		pos++;
	}

	if (start < 0)
	{
		DebugLog("Tag not found. " + tag);

		return false;
	}

	DebugLog("Found tag. " + pos);



	// Verify tag.

	// Back
	if (pos > 0)
	{
		let lastPos = (pos - 1);
		let lastName = buffer.substring(lastPos, (lastPos + 1));

		if (IsFunctionGlyph(lastName))
		{
			DebugLog("Back failed.");

			Feed(tagSize);

			pos += tagSize;

			return false;
		}
	}

	pos += tagSize;



	// Make sure we have at least one character left.

	if (!InRange())
	{
		DebugLog("Out of range.");

		return false;
	}



	// Front
	{
		let name = Substring(buffer, pos, 1);

		if (IsFunctionGlyph(name))
		{
			DebugLog("Front failed.");

			pos = start;

			let size = (tagSize + 1);

			Feed(size);

			pos += size;

			return false;
		}
	}

	// At this point we have a valid tag.



	// Find opening scope.

	while (pos < bufferSize)
	{
		if (SkipComment())
		{
			continue;
		}



		let name = Substring(buffer, pos, 1);
		if (name == "(")
		{
			pos++;

			startArgs = pos;

			break;
		}



		pos++;
	}

	if (startArgs < 0)
	{
		pos = start;

		let lineIndex = GetLineIndex();

		Log(lineIndex + ": Opening scope not found.");

		return true;
	}



	// Find closing scope.

	while (pos < bufferSize)
	{
		if (SkipComment())
		{
			continue;
		}



		let nextPos = (pos + 1);

		let name = Substring(buffer, pos, 1);
		let nextName = "";

		if (nextPos < bufferSize)
		{
			nextName = Substring(buffer, nextPos, 1);
		}

		if (name == "(")
		{
			scopeLevel++;
		}
		else if (name == ")")
		{
			scopeLevel--;
		}

		if (scopeLevel == 0)
		{
			endArgs = pos;

			if
			(
				!(flags & PrepFlags_IgnoreSemicolon) &&
				nextName == ";"
			)
			{
				pos += 2;
			}
			else
			{
				pos++;
			}

			end = pos;

			break;
		}



		pos++;
	}

	if (endArgs < 0)
	{
		pos = start;

		let lineIndex = GetLineIndex();

		Log(lineIndex + ": Closing scope not found.");

		return true;
	}

	DebugLog("start " + start);
	DebugLog("end " + end);

	DebugLog("startArgs " + startArgs);
	DebugLog("endArgs " + endArgs);



	// Get args.

	pos = startArgs;

	while (pos < endArgs)
	{
		if (SkipComment())
		{
			continue;
		}



		let name = Substring(buffer, pos, 1);

		if (name == "(")
		{
			scopeLevel++;
		}
		else if (name == ")")
		{
			scopeLevel--;
		}

		if
		(
			(name == ",") &&
			(scopeLevel == 0)
		)
		{
			args.push(arg);

			arg = "";

			pos++;

			continue;
		}

		arg += name;



		pos++;
	}

	if (arg != "")
	{
		args.push(arg);

		arg = "";
	}



	// Clean args.

	for (let argIndex = 0; argIndex < args.length; argIndex++)
	{
		args[argIndex] = CleanString(args[argIndex]);
	}



	// Get tab count.

	pos = start;

	tabCount = GetTabCount();

	DebugLog("tabCount " + tabCount);

	// At this point the stream could already differ from the original buffer.
	// So use the stream's size instead of the buffer's position.

	c = Substring(c, 0, (c.length - tabCount));



	PrepHelper_funcName = tag;

	PrepHelper_lineIndex = Prep.GetLineIndex();

	PrepHelper_argCount = args.length;





	// console.log("Prep funcName  " + PrepHelper_funcName );
	// console.log("Prep lineIndex " + PrepHelper_lineIndex);
	// console.log("Prep argCount  " + PrepHelper_argCount );



	// Do stuff.

	if (func(args))
	{
		return true;
	}



	pos = end;

	tabCount = 0; // @Research: Consider lastTabCount.



	DebugLog(GetFunctionName() + " End");

	return false;
}

function ReplaceFunctionLoop
(
	tag,
	func,
	flags = 0
)
{
	while (pos < bufferSize)
	{
		if
		(
			ReplaceFunctionOnce
			(
				tag,
				func,
				flags
			)
		)
		{
			return true;
		}
	}

	return false;
}

function ReplaceFunction
(
	tag,
	func,
	flags = 0
)
{
	ClearAll();

	pos = 0;

	if
	(
		ReplaceFunctionLoop
		(
			tag,
			func,
			flags
		)
	)
	{
		return true;
	}

	buffer = c;
	bufferSize = c.length;

	return false;
}



this.Main = function
(
	location,
	newLocation,
	helpers
)
{
	let file = fs.readFileSync(location, "utf8");

	buffer     = file;
	bufferSize = file.length;



	for (let helperIndex = 0; helperIndex < helpersAll.length; helperIndex++)
	{
		let helper = helpersAll[helperIndex];

		let tag   = helper[0];
		let func  = helper[1];
		let flags = helper[2];

		if
		(
			ReplaceFunction
			(
				tag,
				func,
				flags
			)
		)
		{
			return true;
		}
	}



	for (let helperIndex = 0; helperIndex < helpers.length; helperIndex++)
	{
		let helper = helpers[helperIndex];

		let tag   = helper[0];
		let func  = helper[1];
		let flags = helper[2];

		if
		(
			ReplaceFunction
			(
				tag,
				func,
				flags
			)
		)
		{
			return true;
		}
	}



	fs.writeFileSync(newLocation, buffer);



	return false;
}

}

// #endregion



// #region Main

function CompileOnce
(
	args,
	helpers,
	item
)
{
	let sourceLocation = item[0];
	let objectLocation = item[1];
	let prep           = item[2];
	let newArgs        = item[3];



	if (prep)
	{
		let location = sourceLocation;
		let path     = GetPath(location);
		let fileName = GetFileName(location);

		let newFilename = "prep_" + fileName;
		let newLocation = path + "/" + newFilename;

		// console.log("location    $" + location    + "$");
		// console.log("path        $" + path        + "$");
		// console.log("fileName    $" + fileName    + "$");
		// console.log("newFilename $" + newFilename + "$");
		// console.log("newLocation $" + newLocation + "$");

		if
		(
			Prep.Main
			(
				location,
				newLocation,
				helpers
			)
		)
		{
			return true;
		}

		sourceLocation = newLocation;
	}



	ClearAll();

	c = "cl.exe";

	if (newArgs.length > 0)
	{
		args = newArgs;
	}

	for (let index = 0; index < args.length; index++)
	{
		let arg = args[index];

		c += " " + arg;
	}

	if (objectLocation != "")
	{
		c += " /Fo\"" + objectLocation + "\"";
	}

	c += " \"" + sourceLocation + "\"";



	try
	{
		child_process.execSync
		(
			c,
			{
				stdio: "inherit",
				encoding: "utf8"
			}
		);
	}
	catch(error)
	{
		return true;
	}

	return false;
}

function CompileLoop
(
	args,
	helpers,
	items
)
{
	for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
	{
		let item = items[itemIndex];

		if
		(
			CompileOnce
			(
				args,
				helpers,
				item
			)
		)
		{
			return true;
		}
	}

	return false;
}



function Link
(
	args,
	libs,
	location,
	flags = 0
)
{
	ClearAll();



	let appName = "link.exe";

	if (flags & LinkFlags_Static)
	{
		appName = "lib.exe";
	}

	c += appName;



	for (let index = 0; index < args.length; index++)
	{
		let arg = args[index];

		c += " " + arg;
	}



	for (let index = 0; index < libs.length; index++)
	{
		let lib = libs[index];

		c += " \"" + lib + "\"";
	}



	// @Research: Add flag to use specific items only. Requires dynamic array of items.
	let fileNames = fs.readdirSync(".");

	FilterByExtension(fileNames, "obj");

	if (fileNames.length < 1)
	{
		console.log("No Objects");

		return true;
	}

	for (let index = 0; index < fileNames.length; index++)
	{
		let fileName = fileNames[index];

		c += " \"" + fileName + "\"";
	}

	c += " /OUT:\"" + location + "\"";



	try
	{
		child_process.execSync
		(
			c,
			{
				stdio: "inherit",
				encoding: "utf8"
			}
		);
	}
	catch(error)
	{
		return true;
	}

	return false;
}



function Clean()
{
	DeleteByExtension(".", "ifc");
	DeleteByExtension(".", "obj");
	DeleteByExtension(".", "pdb");
}

// #endregion



let compilerArgs_x86_64 =
[
	"/nologo",
	"/c",
	"/std:c++latest",
	"/permissive-",
	"/experimental:module",
	"/Zc:forScope",
	"/Zc:inline",
	"/Zc:preprocessor",
	"/Zc:wchar_t",
	"/Zc:externC-",
	"/W3",
	"/wd4005", // macro redefinition
	"/wd4996", // was declared deprecated
	"/wd5105", // macro expansion producing 'defined' has undefined behavior
	// "/wd5202", // a global module fragment can only contain preprocessor directives
	"/O2",
	"/Oi",
	"/Gy",
	"/Zi",
	"/EHsc",
];

let compilerArgs_x86_32 =
[
	"/nologo",
	"/c",
	"/std:c++latest",
	"/permissive-",
	"/experimental:module",
	"/Zc:forScope",
	"/Zc:inline",
	"/Zc:preprocessor",
	"/Zc:wchar_t",
	"/Zc:externC-",
	"/W3",
	"/wd4005", // macro redefinition
	"/wd4996", // was declared deprecated
	"/wd5105", // macro expansion producing 'defined' has undefined behavior
	// "/wd5202", // a global module fragment can only contain preprocessor directives
	"/O2",
	"/Oi",
	"/Gy",
	"/Zi",
	"/EHsc",
	"/Gz", // __stdcall
];



let libs_x86_64 =
[
	"msvcrt.lib",
	"vcruntime.lib",
	"ucrt.lib",
	"libcpmt.lib",
	"kernel32.lib",
	"user32.lib",
	"shell32.lib",
	"imm32.lib",
	"advapi32.lib",
	"d3d11.lib",
	"d3dcompiler.lib",
	"dinput8.lib",
	"dxguid.lib",
	//"xinput.lib",
	"Xinput9_1_0.lib",
];

let libs_x86_32 =
[
	"msvcrt.lib",
	// "msvcprt.lib",
	// "msvcprtd.lib",
	"vcruntime.lib",
	"ucrt.lib",
	"libcpmt.lib",
	// "mmc.lib",
	// "libcpmt1.lib",
	// "libcpmtd.lib",
	// "libcpmtd0.lib",
	// "libcpmtd1.lib",
	// "libconcrt.lib",
	// "libconcrt1.lib",
	// "libconcrtd.lib",
	// "libconcrtd0.lib",
	// "libconcrtd1.lib",
	"kernel32.lib",
	"user32.lib",
	"shell32.lib",
	"imm32.lib",
	"advapi32.lib",
	"d3d10.lib",
	"d3dcompiler.lib",
	"dinput8.lib",
	"dxguid.lib",
	"xinput.lib",
	//"Xinput9_1_0.lib",




];

























// #region Core

let compilerArgsCore_x86_64 = [];

compilerArgsCore_x86_64 = AddFront
(
	compilerArgsCore_x86_64,
	compilerArgs_x86_64
);

let itemsCore_x86_64 =
[
	[ "Core/DataTypes.ixx", ""              , false, [] ],
	[ "Core/Windows.ixx"  , ""              , false, [] ],
	[ "Core/DXGI.ixx"     , ""              , false, [] ],
	[ "Core/D3D10.ixx"    , ""              , false, [] ],
	[ "Core/D3D11.ixx"    , ""              , false, [] ],
	[ "Core/DI8.ixx"      , ""              , false, [] ],
	[ "Core/XI.ixx"       , ""              , false, [] ],
	[ "Core/Core.ixx"     , ""              , false, [] ],
	[ "Core/GUI.ixx"      , "Core_GUI.obj"  , false, [] ],
	[ "Core/Input.ixx"    , "Core_Input.obj", false, [] ],
	[ "Core/ImGui.ixx"    , "Core_ImGui.obj", false, [] ],
];

let itemsCoreNoGUI_x86_64 =
[
	[ "Core/DataTypes.ixx", "", false, [] ],
	[ "Core/Windows.ixx"  , "", false, [] ],
	[ "Core/DXGI.ixx"     , "", false, [] ],
	[ "Core/D3D10.ixx"    , "", false, [] ],
	[ "Core/D3D11.ixx"    , "", false, [] ],
	[ "Core/DI8.ixx"      , "", false, [] ],
	[ "Core/XI.ixx"       , "", false, [] ],
	[ "Core/Core.ixx"     , "", false, [] ],
];



let compilerArgsCore_x86_32 = [];

compilerArgsCore_x86_32 = AddFront
(
	compilerArgsCore_x86_32,
	compilerArgs_x86_32
);

let itemsCore_x86_32 =
[
	[ "Core/DataTypes.ixx", ""              , false, [] ],
	[ "Core/Windows.ixx"  , ""              , false, [] ],
	[ "Core/DXGI.ixx"     , ""              , false, [] ],
	[ "Core/D3D10.ixx"    , ""              , false, [] ],
	[ "Core/D3D11.ixx"    , ""              , false, [] ],
	[ "Core/DI8.ixx"      , ""              , false, [] ],
	[ "Core/XI.ixx"       , ""              , false, [] ],
	[ "Core/Core.ixx"     , ""              , false, [] ],
	[ "Core/GUI.ixx"      , "Core_GUI.obj"  , false, [] ],
	[ "Core/Input.ixx"    , "Core_Input.obj", false, [] ],
	[ "Core/ImGui.ixx"    , "Core_ImGui.obj", false, [] ],
];

let itemsCoreNoGUI_x86_32 =
[
	[ "Core/DataTypes.ixx", ""              , false, [] ],
	[ "Core/Windows.ixx"  , ""              , false, [] ],
	[ "Core/DXGI.ixx"     , ""              , false, [] ],
	[ "Core/D3D10.ixx"    , ""              , false, [] ],
	[ "Core/D3D11.ixx"    , ""              , false, [] ],
	[ "Core/DI8.ixx"      , ""              , false, [] ],
	[ "Core/XI.ixx"       , ""              , false, [] ],
	[ "Core/Core.ixx"     , ""              , false, [] ],
];

// #endregion



// #region ImGui

let compilerArgsImGui_x86_64 = [];

compilerArgsImGui_x86_64 = AddFront
(
	compilerArgsImGui_x86_64,
	compilerArgs_x86_64
);

let itemsImGui_x86_64 =
[
	[ PATH_IMGUI + "/imgui.cpp"        , "", false, [] ],
	// [ PATH_IMGUI + "/imgui_demo.cpp"   , "", false, [] ],
	[ PATH_IMGUI + "/imgui_draw.cpp"   , "", false, [] ],
	[ PATH_IMGUI + "/imgui_tables.cpp" , "", false, [] ],
	[ PATH_IMGUI + "/imgui_widgets.cpp", "", false, [] ],
];



let compilerArgsImGui_x86_32 = [];

compilerArgsImGui_x86_32 = AddFront
(
	compilerArgsImGui_x86_32,
	compilerArgs_x86_32
);

let itemsImGui_x86_32 =
[
	[ PATH_IMGUI + "/imgui.cpp"        , "", false, [] ],
	// [ PATH_IMGUI + "/imgui_demo.cpp"   , "", false, [] ],
	[ PATH_IMGUI + "/imgui_draw.cpp"   , "", false, [] ],
	[ PATH_IMGUI + "/imgui_tables.cpp" , "", false, [] ],
	[ PATH_IMGUI + "/imgui_widgets.cpp", "", false, [] ],
];

// #endregion



// #region ZLib

let compilerArgsZLib =
[
	"/nologo",
	"/c",
	"/std:c++latest",
	"/permissive-",
	"/experimental:module",
	"/Zc:forScope",
	"/Zc:inline",
	"/Zc:preprocessor",
	"/Zc:wchar_t",
	"/Zc:externC-",
	"/W3",
	"/wd4267", // conversion from 'a' to 'b', possible loss of data
	"/O2",
	"/Oi",
	"/DHAVE_SYS_TYPES_H",
	"/DHAVE_STDINT_H",
	"/DHAVE_STDDEF_H",
	"/DNO_FSEEKO",
	"/D_CRT_SECURE_NO_DEPRECATE",
	"/D_CRT_NONSTDC_NO_DEPRECATE",
];

let itemsZLib =
[
	[ PATH_ZLIB + "/adler32.c" , "", false, [] ],
	[ PATH_ZLIB + "/compress.c", "", false, [] ],
	[ PATH_ZLIB + "/crc32.c"   , "", false, [] ],
	[ PATH_ZLIB + "/deflate.c" , "", false, [] ],
	[ PATH_ZLIB + "/gzclose.c" , "", false, [] ],
	[ PATH_ZLIB + "/gzlib.c"   , "", false, [] ],
	[ PATH_ZLIB + "/gzread.c"  , "", false, [] ],
	[ PATH_ZLIB + "/gzwrite.c" , "", false, [] ],
	[ PATH_ZLIB + "/infback.c" , "", false, [] ],
	[ PATH_ZLIB + "/inffast.c" , "", false, [] ],
	[ PATH_ZLIB + "/inflate.c" , "", false, [] ],
	[ PATH_ZLIB + "/inftrees.c", "", false, [] ],
	[ PATH_ZLIB + "/trees.c"   , "", false, [] ],
	[ PATH_ZLIB + "/uncompr.c" , "", false, [] ],
	[ PATH_ZLIB + "/zutil.c"   , "", false, [] ],
];

let linkerArgsZLib =
[
	"/NOLOGO",
	"/MACHINE:X64",
];

// #endregion



// #region LibZip

let compilerArgsLibZip =
[
	"/nologo",
	"/c",
	"/std:c++latest",
	"/permissive-",
	"/experimental:module",
	"/Zc:forScope",
	"/Zc:inline",
	"/Zc:preprocessor",
	"/Zc:wchar_t",
	"/Zc:externC-",
	"/W3",
	"/wd5105", // macro expansion producing 'defined' has undefined behavior
	"/O2",
	"/Oi",
	"/DHAVE_INTTYPES_H_LIBZIP",
	"/DHAVE_STDINT_H_LIBZIP",
	"/DHAVE_SYS_TYPES_H_LIBZIP",
	"/D_CRT_SECURE_NO_WARNINGS",
	"/D_CRT_NONSTDC_NO_DEPRECATE",
	"/IThirdParty/zlib",
	"/IThirdParty/libzip",
];

let itemsLibZip =
[
	[ PATH_LIBZIP + "/zip_add.c"                          , "", false, [] ],
	[ PATH_LIBZIP + "/zip_add_dir.c"                      , "", false, [] ],
	[ PATH_LIBZIP + "/zip_add_entry.c"                    , "", false, [] ],
	// [ PATH_LIBZIP + "/zip_algorithm_bzip2.c"              , "", false, [] ],
	[ PATH_LIBZIP + "/zip_algorithm_deflate.c"            , "", false, [] ],
	// [ PATH_LIBZIP + "/zip_algorithm_xz.c"                 , "", false, [] ],
	// [ PATH_LIBZIP + "/zip_algorithm_zstd.c"               , "", false, [] ],
	[ PATH_LIBZIP + "/zip_buffer.c"                       , "", false, [] ],
	[ PATH_LIBZIP + "/zip_close.c"                        , "", false, [] ],
	// [ PATH_LIBZIP + "/zip_crypto_commoncrypto.c"          , "", false, [] ],
	// [ PATH_LIBZIP + "/zip_crypto_gnutls.c"                , "", false, [] ],
	// [ PATH_LIBZIP + "/zip_crypto_mbedtls.c"               , "", false, [] ],
	// [ PATH_LIBZIP + "/zip_crypto_openssl.c"               , "", false, [] ],
	// [ PATH_LIBZIP + "/zip_crypto_win.c"                   , "", false, [] ],
	[ PATH_LIBZIP + "/zip_delete.c"                       , "", false, [] ],
	[ PATH_LIBZIP + "/zip_dir_add.c"                      , "", false, [] ],
	[ PATH_LIBZIP + "/zip_dirent.c"                       , "", false, [] ],
	[ PATH_LIBZIP + "/zip_discard.c"                      , "", false, [] ],
	[ PATH_LIBZIP + "/zip_entry.c"                        , "", false, [] ],
	[ PATH_LIBZIP + "/zip_err_str.c"                      , "", false, [] ],
	[ PATH_LIBZIP + "/zip_error.c"                        , "", false, [] ],
	[ PATH_LIBZIP + "/zip_error_clear.c"                  , "", false, [] ],
	[ PATH_LIBZIP + "/zip_error_get.c"                    , "", false, [] ],
	[ PATH_LIBZIP + "/zip_error_get_sys_type.c"           , "", false, [] ],
	[ PATH_LIBZIP + "/zip_error_strerror.c"               , "", false, [] ],
	[ PATH_LIBZIP + "/zip_error_to_str.c"                 , "", false, [] ],
	[ PATH_LIBZIP + "/zip_extra_field.c"                  , "", false, [] ],
	[ PATH_LIBZIP + "/zip_extra_field_api.c"              , "", false, [] ],
	[ PATH_LIBZIP + "/zip_fclose.c"                       , "", false, [] ],
	[ PATH_LIBZIP + "/zip_fdopen.c"                       , "", false, [] ],
	[ PATH_LIBZIP + "/zip_file_add.c"                     , "", false, [] ],
	[ PATH_LIBZIP + "/zip_file_error_clear.c"             , "", false, [] ],
	[ PATH_LIBZIP + "/zip_file_error_get.c"               , "", false, [] ],
	[ PATH_LIBZIP + "/zip_file_get_comment.c"             , "", false, [] ],
	[ PATH_LIBZIP + "/zip_file_get_external_attributes.c" , "", false, [] ],
	[ PATH_LIBZIP + "/zip_file_get_offset.c"              , "", false, [] ],
	[ PATH_LIBZIP + "/zip_file_rename.c"                  , "", false, [] ],
	[ PATH_LIBZIP + "/zip_file_replace.c"                 , "", false, [] ],
	[ PATH_LIBZIP + "/zip_file_set_comment.c"             , "", false, [] ],
	[ PATH_LIBZIP + "/zip_file_set_encryption.c"          , "", false, [] ],
	[ PATH_LIBZIP + "/zip_file_set_external_attributes.c" , "", false, [] ],
	[ PATH_LIBZIP + "/zip_file_set_mtime.c"               , "", false, [] ],
	[ PATH_LIBZIP + "/zip_file_strerror.c"                , "", false, [] ],
	[ PATH_LIBZIP + "/zip_fopen.c"                        , "", false, [] ],
	[ PATH_LIBZIP + "/zip_fopen_encrypted.c"              , "", false, [] ],
	[ PATH_LIBZIP + "/zip_fopen_index.c"                  , "", false, [] ],
	[ PATH_LIBZIP + "/zip_fopen_index_encrypted.c"        , "", false, [] ],
	[ PATH_LIBZIP + "/zip_fread.c"                        , "", false, [] ],
	[ PATH_LIBZIP + "/zip_fseek.c"                        , "", false, [] ],
	[ PATH_LIBZIP + "/zip_ftell.c"                        , "", false, [] ],
	[ PATH_LIBZIP + "/zip_get_archive_comment.c"          , "", false, [] ],
	[ PATH_LIBZIP + "/zip_get_archive_flag.c"             , "", false, [] ],
	[ PATH_LIBZIP + "/zip_get_encryption_implementation.c", "", false, [] ],
	[ PATH_LIBZIP + "/zip_get_file_comment.c"             , "", false, [] ],
	[ PATH_LIBZIP + "/zip_get_name.c"                     , "", false, [] ],
	[ PATH_LIBZIP + "/zip_get_num_entries.c"              , "", false, [] ],
	[ PATH_LIBZIP + "/zip_get_num_files.c"                , "", false, [] ],
	[ PATH_LIBZIP + "/zip_hash.c"                         , "", false, [] ],
	[ PATH_LIBZIP + "/zip_io_util.c"                      , "", false, [] ],
	[ PATH_LIBZIP + "/zip_libzip_version.c"               , "", false, [] ],
	[ PATH_LIBZIP + "/zip_memdup.c"                       , "", false, [] ],
	// [ PATH_LIBZIP + "/zip_mkstempm.c"                     , "", false, [] ],
	[ PATH_LIBZIP + "/zip_name_locate.c"                  , "", false, [] ],
	[ PATH_LIBZIP + "/zip_new.c"                          , "", false, [] ],
	[ PATH_LIBZIP + "/zip_open.c"                         , "", false, [] ],
	[ PATH_LIBZIP + "/zip_pkware.c"                       , "", false, [] ],
	[ PATH_LIBZIP + "/zip_progress.c"                     , "", false, [] ],
	// [ PATH_LIBZIP + "/zip_random_unix.c"                  , "", false, [] ],
	// [ PATH_LIBZIP + "/zip_random_uwp.c"                   , "", false, [] ],
	[ PATH_LIBZIP + "/zip_random_win32.c"                 , "", false, [] ],
	[ PATH_LIBZIP + "/zip_rename.c"                       , "", false, [] ],
	[ PATH_LIBZIP + "/zip_replace.c"                      , "", false, [] ],
	[ PATH_LIBZIP + "/zip_set_archive_comment.c"          , "", false, [] ],
	[ PATH_LIBZIP + "/zip_set_archive_flag.c"             , "", false, [] ],
	[ PATH_LIBZIP + "/zip_set_default_password.c"         , "", false, [] ],
	[ PATH_LIBZIP + "/zip_set_file_comment.c"             , "", false, [] ],
	[ PATH_LIBZIP + "/zip_set_file_compression.c"         , "", false, [] ],
	[ PATH_LIBZIP + "/zip_set_name.c"                     , "", false, [] ],
	[ PATH_LIBZIP + "/zip_source_accept_empty.c"          , "", false, [] ],
	[ PATH_LIBZIP + "/zip_source_begin_write.c"           , "", false, [] ],
	[ PATH_LIBZIP + "/zip_source_begin_write_cloning.c"   , "", false, [] ],
	[ PATH_LIBZIP + "/zip_source_buffer.c"                , "", false, [] ],
	[ PATH_LIBZIP + "/zip_source_call.c"                  , "", false, [] ],
	[ PATH_LIBZIP + "/zip_source_close.c"                 , "", false, [] ],
	[ PATH_LIBZIP + "/zip_source_commit_write.c"          , "", false, [] ],
	[ PATH_LIBZIP + "/zip_source_compress.c"              , "", false, [] ],
	[ PATH_LIBZIP + "/zip_source_crc.c"                   , "", false, [] ],
	[ PATH_LIBZIP + "/zip_source_error.c"                 , "", false, [] ],
	[ PATH_LIBZIP + "/zip_source_file_common.c"           , "", false, [] ],
	[ PATH_LIBZIP + "/zip_source_file_stdio.c"            , "", false, [] ],
	// [ PATH_LIBZIP + "/zip_source_file_stdio_named.c"      , "", false, [] ],
	[ PATH_LIBZIP + "/zip_source_file_win32.c"            , "", false, [] ],
	[ PATH_LIBZIP + "/zip_source_file_win32_ansi.c"       , "", false, [] ],
	[ PATH_LIBZIP + "/zip_source_file_win32_named.c"      , "", false, [] ],
	[ PATH_LIBZIP + "/zip_source_file_win32_utf16.c"      , "", false, [] ],
	[ PATH_LIBZIP + "/zip_source_file_win32_utf8.c"       , "", false, [] ],
	[ PATH_LIBZIP + "/zip_source_free.c"                  , "", false, [] ],
	[ PATH_LIBZIP + "/zip_source_function.c"              , "", false, [] ],
	[ PATH_LIBZIP + "/zip_source_get_file_attributes.c"   , "", false, [] ],
	[ PATH_LIBZIP + "/zip_source_is_deleted.c"            , "", false, [] ],
	[ PATH_LIBZIP + "/zip_source_layered.c"               , "", false, [] ],
	[ PATH_LIBZIP + "/zip_source_open.c"                  , "", false, [] ],
	[ PATH_LIBZIP + "/zip_source_pkware_decode.c"         , "", false, [] ],
	[ PATH_LIBZIP + "/zip_source_pkware_encode.c"         , "", false, [] ],
	[ PATH_LIBZIP + "/zip_source_read.c"                  , "", false, [] ],
	[ PATH_LIBZIP + "/zip_source_remove.c"                , "", false, [] ],
	[ PATH_LIBZIP + "/zip_source_rollback_write.c"        , "", false, [] ],
	[ PATH_LIBZIP + "/zip_source_seek.c"                  , "", false, [] ],
	[ PATH_LIBZIP + "/zip_source_seek_write.c"            , "", false, [] ],
	[ PATH_LIBZIP + "/zip_source_stat.c"                  , "", false, [] ],
	[ PATH_LIBZIP + "/zip_source_supports.c"              , "", false, [] ],
	[ PATH_LIBZIP + "/zip_source_tell.c"                  , "", false, [] ],
	[ PATH_LIBZIP + "/zip_source_tell_write.c"            , "", false, [] ],
	[ PATH_LIBZIP + "/zip_source_window.c"                , "", false, [] ],
	[ PATH_LIBZIP + "/zip_source_winzip_aes_decode.c"     , "", false, [] ],
	[ PATH_LIBZIP + "/zip_source_winzip_aes_encode.c"     , "", false, [] ],
	[ PATH_LIBZIP + "/zip_source_write.c"                 , "", false, [] ],
	[ PATH_LIBZIP + "/zip_source_zip.c"                   , "", false, [] ],
	[ PATH_LIBZIP + "/zip_source_zip_new.c"               , "", false, [] ],
	[ PATH_LIBZIP + "/zip_stat.c"                         , "", false, [] ],
	[ PATH_LIBZIP + "/zip_stat_index.c"                   , "", false, [] ],
	[ PATH_LIBZIP + "/zip_stat_init.c"                    , "", false, [] ],
	[ PATH_LIBZIP + "/zip_strerror.c"                     , "", false, [] ],
	[ PATH_LIBZIP + "/zip_string.c"                       , "", false, [] ],
	[ PATH_LIBZIP + "/zip_unchange.c"                     , "", false, [] ],
	[ PATH_LIBZIP + "/zip_unchange_all.c"                 , "", false, [] ],
	[ PATH_LIBZIP + "/zip_unchange_archive.c"             , "", false, [] ],
	[ PATH_LIBZIP + "/zip_unchange_data.c"                , "", false, [] ],
	[ PATH_LIBZIP + "/zip_utf-8.c"                        , "", false, [] ],
	// [ PATH_LIBZIP + "/zip_winzip_aes.c"                   , "", false, [] ],
];

let linkerArgsLibZip =
[
	"/NOLOGO",
	"/MACHINE:X64",
];

// #endregion



// #region Loader

let compilerArgsLoader_x86_64 = [];

compilerArgsLoader_x86_64 = AddFront
(
	compilerArgsLoader_x86_64,
	compilerArgs_x86_64
);

let itemsLoader_x86_64 =
[
	[ "dinput8.cpp", "", false, [] ],
];

let linkerArgsLoader_x86_64 =
[
	"/NOLOGO",
	"/DLL",
	"/MACHINE:X64",
	"/DYNAMICBASE",
	"/DEBUG:FULL",
	"/OPT:REF",
	"/OPT:ICF",
	"/NODEFAULTLIB",
];

let libsLoader_x86_64 =
[
	"msvcrt.lib",
	"vcruntime.lib",
	"ucrt.lib",
	"kernel32.lib",
	"user32.lib",
	"shell32.lib",
	"imm32.lib",
	"advapi32.lib",
	"d3d10.lib",
	"d3dcompiler.lib",
	"dinput8.lib",
	"dxguid.lib",
	"xinput.lib",
];



let compilerArgsLoader_x86_32 = [];

compilerArgsLoader_x86_32 = AddFront
(
	compilerArgsLoader_x86_32,
	compilerArgs_x86_32
);

let itemsLoader_x86_32 =
[
	[ "dinput8.cpp", "", false, [] ],
];

let linkerArgsLoader_x86_32 =
[
	"/NOLOGO",
	"/DLL",
	"/MACHINE:X86",
	"/DYNAMICBASE",
	"/DEBUG:FULL",
	"/OPT:REF",
	"/OPT:ICF",
	"/NODEFAULTLIB",
];

let libsLoader_x86_32 =
[
	"msvcrt.lib",
	"vcruntime.lib",
	"ucrt.lib",
	"kernel32.lib",
	"user32.lib",
	"shell32.lib",
	"imm32.lib",
	"advapi32.lib",
	"d3d10.lib",
	"d3dcompiler.lib",
	"dinput8.lib",
	"dxguid.lib",
	"xinput.lib",
];

// #endregion



// #region Eva

let compilerArgsEva = [];

compilerArgsEva = AddFront
(
	compilerArgsEva,
	compilerArgs_x86_64
);

let helpersEva =
[

["IntroduceMainActorData", (args) =>
{
	// IntroduceMainActorData(actorDataName, return);
	// IntroduceMainActorData(actorBaseAddrName, actorDataName, return);

	if (PrepHelper_Check(2, 3))
	{
		return true;
	}

	let funcName  = PrepHelper_funcName;
	let lineIndex = PrepHelper_lineIndex;
	let argCount  = PrepHelper_argCount;



	let poolName = "pool_" + lineIndex;

	let actorBaseAddrName = "";
	let actorDataName     = "";
	let returnName        = "";

	if (argCount == 2)
	{
		actorBaseAddrName = poolName;
		actorDataName     = args[0];
		returnName        = args[1];
	}
	else if (argCount == 3)
	{
		actorBaseAddrName = args[0];
		actorDataName     = args[1];
		returnName        = args[2];
	}



	c += Tabs() + "auto " + actorBaseAddrName + " = *reinterpret_cast<byte8 **>(appBaseAddr + 0x60ACD0);" + NEW_LINE;

	c += Tabs() + "if (!" + actorBaseAddrName + ")" + NEW_LINE;

	ScopeStart();

	c += Tabs() + returnName + ";" + NEW_LINE;

	ScopeEnd();



	c += Tabs() + "auto & " + actorDataName + " = *reinterpret_cast<PlayerActorData *>(" + actorBaseAddrName + ");";



	return false;
}],



["IntroduceSessionData", (args) =>
{
	// IntroduceSessionData(return);

	if (PrepHelper_Check(1, 1))
	{
		return true;
	}

	let funcName  = PrepHelper_funcName;
	let lineIndex = PrepHelper_lineIndex;
	let argCount  = PrepHelper_argCount;



	let returnal = args[0];

	let name = "name_" + lineIndex;



	c += Tabs() + "auto " + name + " = *reinterpret_cast<byte8 **>(appBaseAddr + 0x5EAB88);" + NEW_LINE;
	c += Tabs() + "if (!" + name + ")"+ NEW_LINE;

	ScopeStart();

	c += Tabs() + returnal + ";" + NEW_LINE;

	ScopeEnd();

	c += Tabs() + "auto & sessionData = *reinterpret_cast<SessionData *>(" + name + ");" + NEW_LINE;



	return false;
}],



["IntroduceEventData", (args) =>
{
	// IntroduceEventData(return);

	if (PrepHelper_Check(1, 1))
	{
		return true;
	}

	let funcName  = PrepHelper_funcName;
	let lineIndex = PrepHelper_lineIndex;
	let argCount  = PrepHelper_argCount;



	let returnal = args[0];

	let name = "name_" + lineIndex;



	c += Tabs() + "auto " + name + " = *reinterpret_cast<byte8 **>(appBaseAddr + 0x60B148);" + NEW_LINE;
	c += Tabs() + "if (!" + name + ")"+ NEW_LINE;

	ScopeStart();

	c += Tabs() + returnal + ";" + NEW_LINE;

	ScopeEnd();

	c += Tabs() + "auto & eventData = *reinterpret_cast<EventData *>(" + name + ");" + NEW_LINE;



	return false;
}],



["IntroduceWeaponData", (args) =>
{
	// IntroduceWeaponData(return);

	if (PrepHelper_Check(1, 1))
	{
		return true;
	}

	let funcName  = PrepHelper_funcName;
	let lineIndex = PrepHelper_lineIndex;
	let argCount  = PrepHelper_argCount;



	let returnal = args[0];

	let name = "name_" + lineIndex;



	c += Tabs() + "auto " + name + " = *reinterpret_cast<byte8 **>(appBaseAddr + 0x60AD10);" + NEW_LINE;
	c += Tabs() + "if (!" + name + ")"+ NEW_LINE;

	ScopeStart();

	c += Tabs() + returnal + ";" + NEW_LINE;

	ScopeEnd();

	c += Tabs() + "auto & weaponData = *reinterpret_cast<WeaponData *>(" + name + ");" + NEW_LINE;



	return false;
}],

];

let itemsEva =
[
	[ "Eva/Vars.ixx"    , "", false , [] ],
	[ "Eva/Config.ixx"  , "", true , [] ],
	[ "Eva/Global.ixx"  , "", true  , [] ],
	[ "Eva/Internal.ixx", "", false , [] ],
	[ "Eva/Arcade.ixx"  , "", true  , [] ],
	[ "Eva/BossRush.ixx", "", true  , [] ],
	[ "Eva/HUD.ixx"     , "", false , [] ],
	[ "Eva/Input.ixx"   , "", false , [] ],
	[ "Eva/Window.ixx"  , "", false , [] ],
	[ "Eva/Actor.ixx"   , "", true  , [] ],
	[ "Eva/Event.ixx"   , "", true  , [] ],
	[ "Eva/Graphics.ixx", "", false , [] ],
	[ "Eva/Training.ixx", "", false , [] ],
	[ "GlobalBase.ixx"  , "", false , [] ],
	[ "GUIBase.ixx"     , "", false , [] ],
	[ "Eva/GUI.ixx"     , "", true  , [] ],
	[ "HooksBase.ixx"   , "", false , [] ],
	[ "Eva/Hooks.ixx"   , "", false , [] ],
	[ "Eva/Eva.cpp"     , "", false , [] ],
];

let itemsEvaActor =
[
	[ "Eva/Actor.ixx", "", true, [] ],
];

let itemsEvaGUI =
[
	[ "GlobalBase.ixx"  , "", false , [] ],
	[ "GUIBase.ixx"     , "", false , [] ],
	[ "Eva/GUI.ixx"     , "", true  , [] ],
	[ "HooksBase.ixx"   , "", false , [] ],
	[ "Eva/Hooks.ixx"   , "", false , [] ],
];

let linkerArgsEva =
[
	"/NOLOGO",
	"/DLL",
	"/MACHINE:X64",
	"/DYNAMICBASE",
	"/DEBUG:FULL",
	"/OPT:REF",
	"/OPT:ICF",
	"/NODEFAULTLIB",
];

let libsEva = [];

libsEva = AddFront
(
	libsEva,
	libs_x86_64
);

// #endregion



// #region Lucia

let compilerArgsLucia = [];

compilerArgsLucia = AddFront
(
	compilerArgsLucia,
	compilerArgs_x86_64
);

let helpersLucia = [];

let itemsLucia =
[
	[ "Lucia/Vars.ixx"    , "", false, [] ],
	[ "Lucia/Config.ixx"  , "", true, [] ],
	[ "Lucia/Global.ixx"  , "", false, [] ],
	[ "Lucia/Input.ixx"   , "", false, [] ],
	[ "Lucia/Window.ixx"  , "", false, [] ],
	[ "Lucia/Graphics.ixx", "", false, [] ],
	[ "GlobalBase.ixx"    , "", false, [] ],
	[ "GUIBase.ixx"       , "", false, [] ],
	[ "Lucia/GUI.ixx"     , "", true , [] ],
	[ "HooksBase.ixx"     , "", false, [] ],
	[ "Lucia/Hooks.ixx"   , "", false, [] ],
	[ "Lucia/Lucia.cpp"   , "", false, [] ],
];

let linkerArgsLucia =
[
	"/NOLOGO",
	"/DLL",
	"/MACHINE:X64",
	"/DYNAMICBASE",
	"/DEBUG:FULL",
	"/OPT:REF",
	"/OPT:ICF",
	"/NODEFAULTLIB",
];

let libsLucia = [];

libsLucia = AddFront
(
	libsLucia,
	libs_x86_64
);

// #endregion



// #region Mary

let compilerArgsMary =
[
	"/IThirdParty/zlib",
	"/IThirdParty/libzip",
];

compilerArgsMary = AddFront
(
	compilerArgsMary,
	compilerArgs_x86_64
);

let helpersMary =
[

["IntroducePlayerActorData", (args) =>
{
	// IntroducePlayerActorData(actorBaseAddrName, actorDataName, return);
	// IntroducePlayerActorData(actorBaseAddrName, actorBaseAddrSource, actorDataName, return);

	if (PrepHelper_Check(3, 4))
	{
		return true;
	}

	let funcName  = PrepHelper_funcName;
	let lineIndex = PrepHelper_lineIndex;
	let argCount  = PrepHelper_argCount;



	let actorBaseAddrName   = "";
	let actorBaseAddrSource = "";
	let actorDataName       = "";
	let returnal            = "";

	if (argCount == 3)
	{
		actorBaseAddrName = args[0];
		actorDataName     = args[1];
		returnal          = args[2];
	}
	else if (argCount == 4)
	{
		actorBaseAddrName   = args[0];
		actorBaseAddrSource = args[1];
		actorDataName       = args[2];
		returnal            = args[3];

		c += Tabs() + "auto " + actorBaseAddrName + " = " + actorBaseAddrSource + ";" + NEW_LINE;
	}

	c += Tabs() + "if (!" + actorBaseAddrName + ")" + NEW_LINE;

	ScopeStart();

	c += Tabs() + returnal + ";" + NEW_LINE;

	ScopeEnd();

	c += Tabs() + "auto & " + actorDataName + " = *reinterpret_cast<PlayerActorData *>(" + actorBaseAddrName + ");";

	return false;
}],

["IntroduceMainActorData", (args) =>
{
	// IntroduceMainActorData(actorDataName, return);
	// IntroduceMainActorData(actorBaseAddrName, actorDataName, return);

	if (PrepHelper_Check(2, 3))
	{
		return true;
	}

	let funcName  = PrepHelper_funcName;
	let lineIndex = PrepHelper_lineIndex;
	let argCount  = PrepHelper_argCount;



	let poolName = "pool_" + lineIndex;

	let actorBaseAddrName = "";
	let actorDataName     = "";
	let returnal          = "";

	if (argCount == 2)
	{
		actorBaseAddrName = poolName + "[3]";
		actorDataName     = args[0];
		returnal          = args[1];
	}
	else if (argCount == 3)
	{
		actorBaseAddrName = args[0];
		actorDataName     = args[1];
		returnal          = args[2];
	}



	c += Tabs() + "auto " + poolName + " = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);" + NEW_LINE;



	c += Tabs() + "if" + NEW_LINE;

	ScopeStart("(");

	c += Tabs() + "!" + poolName + " ||" + NEW_LINE;
	c += Tabs() + "!" + poolName + "[3]" + NEW_LINE;

	ScopeEnd(")");

	ScopeStart();

	c += Tabs() + returnal + ";" + NEW_LINE;

	ScopeEnd();



	if (argCount == 3)
	{
		c += Tabs() + "auto " + actorBaseAddrName + " = " + poolName + "[3];" + NEW_LINE;
	}



	c += Tabs() + "auto & " + actorDataName + " = *reinterpret_cast<PlayerActorData *>(" + actorBaseAddrName + ");";



	return false;
}],



["IntroducePlayerCharacterNewActorData", (args) =>
{
	// IntroducePlayerCharacterNewActorData();
	// IntroducePlayerCharacterNewActorData(playerIndex);
	// IntroducePlayerCharacterNewActorData(playerIndex, characterIndex);
	// IntroducePlayerCharacterNewActorData(playerIndex, characterIndex, entityIndex);

	if (PrepHelper_Check(0, 3))
	{
		return true;
	}

	let funcName  = PrepHelper_funcName;
	let lineIndex = PrepHelper_lineIndex;
	let argCount  = PrepHelper_argCount;



	let playerIndex    = "0";
	let characterIndex = "playerData.characterIndex";
	let entityIndex    = "ENTITY::MAIN";

	if (argCount >= 1)
	{
		playerIndex = args[0];
	}

	if (argCount >= 2)
	{
		characterIndex = args[1];
	}

	if (argCount >= 3)
	{
		entityIndex = args[2];
	}

	c += Tabs() + "auto & playerData = GetPlayerData(" + playerIndex + ");" + NEW_LINE;
	c += NEW_LINE;

	c += Tabs() + "auto & characterData = GetCharacterData(" + playerIndex + ", " + characterIndex + ", " + entityIndex + ");" + NEW_LINE;
	c += Tabs() + "auto & newActorData  = GetNewActorData (" + playerIndex + ", " + characterIndex + ", " + entityIndex + ");" + NEW_LINE;
	c += NEW_LINE;

	c += Tabs() + "auto & activeCharacterData = GetCharacterData(" + playerIndex + ", playerData.activeCharacterIndex, ENTITY::MAIN);" + NEW_LINE;
	c += Tabs() + "auto & activeNewActorData  = GetNewActorData (" + playerIndex + ", playerData.activeCharacterIndex, ENTITY::MAIN);" + NEW_LINE;
	c += NEW_LINE;

	c += Tabs() + "auto & leadCharacterData = GetCharacterData(" + playerIndex + ", 0, ENTITY::MAIN);" + NEW_LINE;
	c += Tabs() + "auto & leadNewActorData  = GetNewActorData (" + playerIndex + ", 0, ENTITY::MAIN);" + NEW_LINE;
	c += NEW_LINE;

	c += Tabs() + "auto & mainCharacterData = GetCharacterData(" + playerIndex + ", " + characterIndex + ", ENTITY::MAIN);" + NEW_LINE;
	c += Tabs() + "auto & mainNewActorData  = GetNewActorData (" + playerIndex + ", " + characterIndex + ", ENTITY::MAIN);" + NEW_LINE;
	c += NEW_LINE;



	return false;
}],



["IntroduceEnemyCount", (args) =>
{
	// IntroduceEnemyCount(return);

	if (PrepHelper_Check(1, 1))
	{
		return true;
	}

	let funcName  = PrepHelper_funcName;
	let lineIndex = PrepHelper_lineIndex;
	let argCount  = PrepHelper_argCount;



	let returnal = args[0];

	let poolName = "pool_" + lineIndex;



	c += Tabs() + "auto " + poolName + " = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);" + NEW_LINE;
	c += Tabs() + "if" + NEW_LINE;

	ScopeStart("(");

	c += Tabs() + "!" + poolName + " ||" + NEW_LINE;
	c += Tabs() + "!" + poolName + "[8]" + NEW_LINE;

	ScopeEnd(")");

	ScopeStart();

	c += Tabs() + returnal + ";" + NEW_LINE;

	ScopeEnd();

	c += Tabs() + "auto & enemyCount = *reinterpret_cast<uint32 *>(" + poolName + "[8] + 0x28);" + NEW_LINE;



	return false;
}],



["IntroduceEnemyVectorData", (args) =>
{
	// IntroduceEnemyVectorData(return);

	if (PrepHelper_Check(1, 1))
	{
		return true;
	}

	let funcName  = PrepHelper_funcName;
	let lineIndex = PrepHelper_lineIndex;
	let argCount  = PrepHelper_argCount;



	let returnal = args[0];

	let poolName = "pool_" + lineIndex;



	c += Tabs() + "auto " + poolName + " = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);" + NEW_LINE;
	c += Tabs() + "if" + NEW_LINE;

	ScopeStart("(");

	c += Tabs() + "!" + poolName + " ||" + NEW_LINE;
	c += Tabs() + "!" + poolName + "[8]" + NEW_LINE;

	ScopeEnd(")");

	ScopeStart();

	c += Tabs() + returnal + ";" + NEW_LINE;

	ScopeEnd();

	c += Tabs() + "auto & enemyVectorData = *reinterpret_cast<EnemyVectorData *>(" + poolName + "[8]);" + NEW_LINE;



	return false;
}],



["IntroduceBloodyPalaceData", (args) =>
{
	// IntroduceBloodyPalaceData(return);

	if (PrepHelper_Check(1, 1))
	{
		return true;
	}

	let funcName  = PrepHelper_funcName;
	let lineIndex = PrepHelper_lineIndex;
	let argCount  = PrepHelper_argCount;



	let returnal = args[0];

	let poolName = "pool_" + lineIndex;
	let name = "name_" + lineIndex;



	c += Tabs() + "auto " + poolName + " = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E10);" + NEW_LINE;
	c += Tabs() + "if" + NEW_LINE;

	ScopeStart("(");

	c += Tabs() + "!" + poolName + " ||" + NEW_LINE;
	c += Tabs() + "!" + poolName + "[5]" + NEW_LINE;

	ScopeEnd(")");

	ScopeStart();

	c += Tabs() + returnal + ";" + NEW_LINE;

	ScopeEnd();



	c += Tabs() + "auto " + name + " = *reinterpret_cast<byte8 **>(" + poolName + "[5] + 0x10);" + NEW_LINE;
	c += Tabs() + "if (!" + name + ")" + NEW_LINE;

	ScopeStart();

	c += Tabs() + returnal + ";" + NEW_LINE;

	ScopeEnd();



	c += Tabs() + name + " = *reinterpret_cast<byte8 **>(" + name + " + 8);" + NEW_LINE;
	c += Tabs() + "if (!" + name + ")" + NEW_LINE;

	ScopeStart();

	c += Tabs() + returnal + ";" + NEW_LINE;

	ScopeEnd();



	c += Tabs() + "auto & bloodyPalaceData = *reinterpret_cast<BloodyPalaceData *>(" + name + ");" + NEW_LINE;



	return false;
}],



["IntroduceSessionData", (args) =>
{
	// IntroduceSessionData(return);

	if (PrepHelper_Check(0, 0))
	{
		return true;
	}

	c += Tabs() + "auto & sessionData = *reinterpret_cast<SessionData *>(appBaseAddr + 0xC8F250);" + NEW_LINE;



	return false;
}],



["IntroduceMissionData", (args) =>
{
	// IntroduceMissionData(return);

	if (PrepHelper_Check(1, 1))
	{
		return true;
	}

	let funcName  = PrepHelper_funcName;
	let lineIndex = PrepHelper_lineIndex;
	let argCount  = PrepHelper_argCount;



	let returnal = args[0];

	let name = "name_" + lineIndex;



	c += Tabs() + "auto " + name + " = *reinterpret_cast<byte8 **>(appBaseAddr + 0xC90E30);" + NEW_LINE;
	c += Tabs() + "if (!" + name + ")"+ NEW_LINE;

	ScopeStart();

	c += Tabs() + returnal + ";" + NEW_LINE;

	ScopeEnd();

	c += Tabs() + "auto & missionData = *reinterpret_cast<MissionData *>(" + name + ");" + NEW_LINE;



	return false;
}],



["IntroduceMissionActorData", (args) =>
{
	// IntroduceMissionActorData(return);

	if (PrepHelper_Check(1, 1))
	{
		return true;
	}

	let funcName  = PrepHelper_funcName;
	let lineIndex = PrepHelper_lineIndex;
	let argCount  = PrepHelper_argCount;



	let returnal = args[0];

	let name = "name_" + lineIndex;



	c += Tabs() + "auto " + name + " = *reinterpret_cast<byte8 **>(appBaseAddr + 0xC90E30);" + NEW_LINE;
	c += Tabs() + "if (!" + name + ")"+ NEW_LINE;

	ScopeStart();

	c += Tabs() + returnal + ";" + NEW_LINE;

	ScopeEnd();

	c += Tabs() + "auto & queuedMissionActorData = *reinterpret_cast<QueuedMissionActorData *>(" + name + " + 0xC0 );" + NEW_LINE;
	c += Tabs() + "auto & activeMissionActorData = *reinterpret_cast<ActiveMissionActorData *>(" + name + " + 0x16C);" + NEW_LINE;



	return false;
}],



["IntroduceEventData", (args) =>
{
	// IntroduceEventData(return);

	if (PrepHelper_Check(1, 1))
	{
		return true;
	}

	let funcName  = PrepHelper_funcName;
	let lineIndex = PrepHelper_lineIndex;
	let argCount  = PrepHelper_argCount;



	let returnal = args[0];

	let poolName = "pool_" + lineIndex;



	c += Tabs() + "auto " + poolName + " = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E10);" + NEW_LINE;
	c += Tabs() + "if" + NEW_LINE;

	ScopeStart("(");

	c += Tabs() + "!" + poolName + " ||" + NEW_LINE;
	c += Tabs() + "!" + poolName + "[8]" + NEW_LINE;

	ScopeEnd(")");

	ScopeStart();

	c += Tabs() + returnal + ";" + NEW_LINE;

	ScopeEnd();



	c += Tabs() + "auto & eventData = *reinterpret_cast<EventData *>(" + poolName + "[8]);" + NEW_LINE;



	return false;
}],



["IntroduceNextEventData", (args) =>
{
	// IntroduceNextEventData(return);

	if (PrepHelper_Check(1, 1))
	{
		return true;
	}

	let funcName  = PrepHelper_funcName;
	let lineIndex = PrepHelper_lineIndex;
	let argCount  = PrepHelper_argCount;



	let returnal = args[0];

	let poolName = "pool_" + lineIndex;



	c += Tabs() + "auto " + poolName + " = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E10);" + NEW_LINE;
	c += Tabs() + "if" + NEW_LINE;

	ScopeStart("(");

	c += Tabs() + "!" + poolName + " ||" + NEW_LINE;
	c += Tabs() + "!" + poolName + "[12]" + NEW_LINE;

	ScopeEnd(")");

	ScopeStart();

	c += Tabs() + returnal + ";" + NEW_LINE;

	ScopeEnd();



	c += Tabs() + "auto & nextEventData = *reinterpret_cast<NextEventData *>(" + poolName + "[12]);" + NEW_LINE;



	return false;
}],



["IntroduceEventFlags", (args) =>
{
	// IntroduceEventFlags(return);

	if (PrepHelper_Check(1, 1))
	{
		return true;
	}

	let funcName  = PrepHelper_funcName;
	let lineIndex = PrepHelper_lineIndex;
	let argCount  = PrepHelper_argCount;



	let returnal = args[0];

	let poolName = "pool_" + lineIndex;



	c += Tabs() + "auto " + poolName + " = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E30);" + NEW_LINE;
	c += Tabs() + "if" + NEW_LINE;

	ScopeStart("(");

	c += Tabs() + "!" + poolName + " ||" + NEW_LINE;
	c += Tabs() + "!" + poolName + "[1]" + NEW_LINE;

	ScopeEnd(")");

	ScopeStart();

	c += Tabs() + returnal + ";" + NEW_LINE;

	ScopeEnd();



	c += Tabs() + "auto eventFlags = reinterpret_cast<byte32 *>(" + poolName + "[1]);" + NEW_LINE;



	return false;
}],



["IntroduceCameraData", (args) =>
{
	// IntroduceCameraData(return);

	if (PrepHelper_Check(1, 1))
	{
		return true;
	}

	let funcName  = PrepHelper_funcName;
	let lineIndex = PrepHelper_lineIndex;
	let argCount  = PrepHelper_argCount;



	let returnal = args[0];

	let poolName = "pool_" + lineIndex;



	c += Tabs() + "auto " + poolName + " = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC8FBD0);" + NEW_LINE;
	c += Tabs() + "if" + NEW_LINE;

	ScopeStart("(");

	c += Tabs() + "!" + poolName + " ||" + NEW_LINE;
	c += Tabs() + "!" + poolName + "[147]" + NEW_LINE;

	ScopeEnd(")");

	ScopeStart();

	c += Tabs() + returnal + ";" + NEW_LINE;

	ScopeEnd();



	c += Tabs() + "auto & cameraData = *reinterpret_cast<CameraData *>(" + poolName + "[147]);" + NEW_LINE;



	return false;
}],



["IntroduceHUDPointers", (args) =>
{
	// IntroduceHUDPointers(return);

	if (PrepHelper_Check(1, 1))
	{
		return true;
	}

	let funcName  = PrepHelper_funcName;
	let lineIndex = PrepHelper_lineIndex;
	let argCount  = PrepHelper_argCount;



	let returnal = args[0];

	let name = "name_" + lineIndex;



	c += Tabs() + "auto " + name + " = *reinterpret_cast<byte8 **>(appBaseAddr + 0xC90E28);" + NEW_LINE;
	c += Tabs() + "if (!" + name + ")" + NEW_LINE;

	ScopeStart();

	c += Tabs() + returnal + ";" + NEW_LINE;

	ScopeEnd();

	c += Tabs() + name + " -= 0x180;" + NEW_LINE;
	c += Tabs() + "auto hudTop    = *reinterpret_cast<byte8 **>(" + name + " + 0x1B070);" + NEW_LINE;
	c += Tabs() + "auto hudBottom = *reinterpret_cast<byte8 **>(" + name + " + 0x1B078);" + NEW_LINE;

	/*
	dmc3.exe+23E691 - 48 8D 93 80010000 - lea rdx,[rbx+00000180]
	*/



	return false;
}],





["IntroducePlayerActorExpData", (args) =>
{
	// IntroducePlayerActorExpData(actorData, return);

	if (PrepHelper_Check(2, 2))
	{
		return true;
	}

	let funcName  = PrepHelper_funcName;
	let lineIndex = PrepHelper_lineIndex;
	let argCount  = PrepHelper_argCount;



	let actorData = args[0];
	let returnal  = args[1];



	c += Tabs() + "auto character = " + actorData + ".character;" + NEW_LINE;
	c += Tabs() + "if (character >= CHARACTER::MAX)" + NEW_LINE;
	ScopeStart();
	c += Tabs() + returnal + ";" + NEW_LINE;
	ScopeEnd();
	c += NEW_LINE;

	c += Tabs() + "auto style = " + actorData + ".style;" + NEW_LINE;
	c += Tabs() + "if (style >= STYLE::MAX)" + NEW_LINE;
	ScopeStart();
	c += Tabs() + returnal + ";" + NEW_LINE;
	ScopeEnd();
	c += NEW_LINE;

	c += Tabs() + "ExpData * expDataAddr =" + NEW_LINE;
	c += Tabs() + "(character == CHARACTER::DANTE ) ? &missionExpDataDante  :" + NEW_LINE;
	c += Tabs() + "(character == CHARACTER::VERGIL) ? &missionExpDataVergil :" + NEW_LINE;
	c += Tabs() + "0;" + NEW_LINE;
	c += NEW_LINE;

	c += Tabs() + "if (!expDataAddr)" + NEW_LINE;
	ScopeStart();
	c += Tabs() + returnal + ";" + NEW_LINE;
	ScopeEnd();
	c += NEW_LINE;

	c += Tabs() + "auto & expData = *expDataAddr;";



	return false;
}],



];

let itemsMary =
[
	[ "Mary/Vars.ixx"            , "", true , [] ],
	[ "Mary/Internal.ixx"        , "", false, [] ],
	[ "Mary/Global.ixx"          , "", true , [] ],
	[ "Mary/Config.ixx"          , "", true , [] ],
	[ "Mary/Memory.ixx"          , "", false, [] ],
	[ "Mary/File.ixx"            , "", false, [] ],
	[ "Mary/FMOD.ixx"            , "", false, [] ],
	[ "Mary/Graphics.ixx"        , "", false, [] ],
	[ "Mary/Input.ixx"           , "", false, [] ],
	[ "Mary/Model.ixx"           , "", false, [] ],
	[ "Mary/HUD.ixx"             , "", true , [] ],
	[ "Mary/SoundRelocations.ixx", "", true , [] ],
	[ "Mary/Sound.ixx"           , "", true , [] ],
	[ "Mary/Exp.ixx"             , "", true , [] ],
	[ "Mary/ActorBase.ixx"       , "", true , [] ],
	[ "Mary/ActorRelocations.ixx", "", true , [] ],
	[ "Mary/Actor.ixx"           , "", true , [] ],
	[ "Mary/Arcade.ixx"          , "", true , [] ],
	[ "Mary/BossRush.ixx"        , "", true , [] ],
	[ "Mary/Camera.ixx"          , "", false, [] ],
	[ "Mary/Speed.ixx"           , "", false, [] ],
	[ "Mary/Training.ixx"        , "", false, [] ],
	[ "Mary/Window.ixx"          , "", false, [] ],
	// [ "Mary/Item.ixx"            , "", true , [] ],
	[ "Mary/Event.ixx"           , "", true , [] ],
	[ "Mary/Scene.ixx"           , "", true, [] ],
	[ "GlobalBase.ixx"           , "", false, [] ],
	[ "GUIBase.ixx"              , "", false, [] ],
	[ "Mary/GUI.ixx"             , "", true , [] ],
	[ "HooksBase.ixx"            , "", false, [] ],
	[ "Mary/Hooks.ixx"           , "", false, [] ],
	[ "Mary/Mary.cpp"            , "", false, [] ],
];

let itemsMaryActor =
[
	[ "Mary/Exp.ixx", "", true, [] ],
	[ "Mary/Mary.cpp", "", false, [] ],
];

let itemsMaryGUI =
[
	[ "GlobalBase.ixx", "", false, [] ],
	[ "GUIBase.ixx"   , "", false, [] ],
	[ "Mary/GUI.ixx"  , "", true , [] ],
	[ "HooksBase.ixx" , "", false, [] ],
	[ "Mary/Hooks.ixx", "", false, [] ],
];

let linkerArgsMary =
[
	"/NOLOGO",
	"/DLL",
	"/MACHINE:X64",
	"/DYNAMICBASE",
	"/DEBUG:FULL",
	"/OPT:REF",
	"/OPT:ICF",
	"/NODEFAULTLIB",
];

let libsMary =
[
	LOCATION_ZLIB,
	LOCATION_LIBZIP,
];

libsMary = AddFront
(
	libsMary,
	libs_x86_64
);





// #endregion



// #region Kyrie

let compilerArgsKyrie = [];

compilerArgsKyrie = AddFront
(
	compilerArgsKyrie,
	compilerArgs_x86_32
);

let helpersKyrie =
[

["IntroduceEventData", (args) =>
{
	// IntroduceEventData(return);

	if (PrepHelper_Check(1, 1))
	{
		console.log("IntroduceEventData");
		return true;
	}

	let funcName  = PrepHelper_funcName;
	let lineIndex = PrepHelper_lineIndex;
	let argCount  = PrepHelper_argCount;



	let returnal = args[0];

	let name = "name_" + lineIndex;
	let name2 = "name2_" + lineIndex;



	c += Tabs() + "auto " + name + " = *reinterpret_cast<byte8 **>(appBaseAddr + 0xF23F38);" + NEW_LINE;
	c += Tabs() + "if (!" + name + ")" + NEW_LINE;

	ScopeStart();

	c += Tabs() + returnal + ";" + NEW_LINE;

	ScopeEnd();

	c += Tabs() + "auto " + name2 + " = reinterpret_cast<byte8 **>(" + name + " + 0x382C);" + NEW_LINE;
	c += Tabs() + "if (!" + name2 + "[3])" + NEW_LINE;

	ScopeStart();

	c += Tabs() + returnal + ";" + NEW_LINE;

	ScopeEnd();

	c += Tabs() + "auto & eventData = *reinterpret_cast<EventData *>(" + name2 + "[3]);" + NEW_LINE;



	return false;
}],

["IntroduceNextEventData", (args) =>
{
	// IntroduceNextEventData(return);

	if (PrepHelper_Check(1, 1))
	{
	console.log("IntroduceNextEventData");
		return true;
	}

	let funcName  = PrepHelper_funcName;
	let lineIndex = PrepHelper_lineIndex;
	let argCount  = PrepHelper_argCount;



	let returnal = args[0];

	let name = "name_" + lineIndex;
	let name2 = "name2_" + lineIndex;



	c += Tabs() + "auto " + name + " = *reinterpret_cast<byte8 **>(appBaseAddr + 0xF23F38);" + NEW_LINE;
	c += Tabs() + "if (!" + name + ")" + NEW_LINE;

	ScopeStart();

	c += Tabs() + returnal + ";" + NEW_LINE;

	ScopeEnd();

	c += Tabs() + "auto " + name2 + " = reinterpret_cast<byte8 **>(" + name + " + 0x382C);" + NEW_LINE;
	c += Tabs() + "if (!" + name2 + "[1])" + NEW_LINE;

	ScopeStart();

	c += Tabs() + returnal + ";" + NEW_LINE;

	ScopeEnd();

	c += Tabs() + "auto & nextEventData = *reinterpret_cast<NextEventData *>(" + name2 + "[1]);" + NEW_LINE;



	return false;
}],



["IntroduceSessionEventData", (args) =>
{
	// IntroduceSessionEventData(return);

	if (PrepHelper_Check(1, 1))
	{
	console.log("IntroduceSessionEventData");
		return true;
	}

	let funcName  = PrepHelper_funcName;
	let lineIndex = PrepHelper_lineIndex;
	let argCount  = PrepHelper_argCount;



	let returnal = args[0];

	let name = "name_" + lineIndex;
	let name2 = "name2_" + lineIndex;



	c += Tabs() + "auto " + name + " = *reinterpret_cast<byte8 **>(appBaseAddr + 0xF23F38);" + NEW_LINE;
	c += Tabs() + "if (!" + name + ")" + NEW_LINE;

	ScopeStart();

	c += Tabs() + returnal + ";" + NEW_LINE;

	ScopeEnd();

	c += Tabs() + "auto " + name2 + " = reinterpret_cast<byte8 **>(" + name + " + 0x382C);" + NEW_LINE;
	c += Tabs() + "if (!" + name2 + "[2])" + NEW_LINE;

	ScopeStart();

	c += Tabs() + returnal + ";" + NEW_LINE;

	ScopeEnd();

	c += Tabs() + "auto & sessionEventData = *reinterpret_cast<SessionEventData *>(" + name2 + "[2]);" + NEW_LINE;



	return false;
}],



["IntroduceSessionData", (args) =>
{
	// IntroduceSessionData(return);



	if (PrepHelper_Check(1, 1))
	{
	console.log("IntroduceSessionData");
		return true;
	}

	let funcName  = PrepHelper_funcName;
	let lineIndex = PrepHelper_lineIndex;
	let argCount  = PrepHelper_argCount;



	let returnal = args[0];

	let name = "name_" + lineIndex;

	c += Tabs() + "auto " + name + " = *reinterpret_cast<byte8 **>(appBaseAddr + 0xF59F00);" + NEW_LINE;
	c += Tabs() + "if (!" + name + ")" + NEW_LINE;

	ScopeStart();

	c += Tabs() + returnal + ";" + NEW_LINE;

	ScopeEnd();

	c += Tabs() + "auto & sessionData = *reinterpret_cast<SessionData *>(" + name + ");" + NEW_LINE;



	return false;
}],



["IntroduceCharacterData", (args) =>
{
	// IntroduceCharacterData(return);



	if (PrepHelper_Check(1, 1))
	{
	console.log("IntroduceCharacterData");
		return true;
	}

	let funcName  = PrepHelper_funcName;
	let lineIndex = PrepHelper_lineIndex;
	let argCount  = PrepHelper_argCount;



	let returnal = args[0];

	let name = "name_" + lineIndex;

	c += Tabs() + "auto " + name + " = *reinterpret_cast<byte8 **>(appBaseAddr + 0xF59F10);" + NEW_LINE;
	c += Tabs() + "if (!" + name + ")" + NEW_LINE;

	ScopeStart();

	c += Tabs() + returnal + ";" + NEW_LINE;

	ScopeEnd();

	c += Tabs() + "auto & characterData = *reinterpret_cast<CharacterData *>(" + name + ");" + NEW_LINE;



	return false;
}],



["IntroduceCameraData", (args) =>
{
	// IntroduceCameraData(return);



	if (PrepHelper_Check(1, 1))
	{
	console.log("IntroduceCameraData");
		return true;
	}

	let funcName  = PrepHelper_funcName;
	let lineIndex = PrepHelper_lineIndex;
	let argCount  = PrepHelper_argCount;



	let returnal = args[0];

	let name = "name_" + lineIndex;



	c += Tabs() + "auto " + name + " = *reinterpret_cast<byte8 **>(appBaseAddr + 0xF59F00);" + NEW_LINE;
	c += Tabs() + "if (!" + name + ")" + NEW_LINE;

	ScopeStart();

	c += Tabs() + returnal + ";" + NEW_LINE;

	ScopeEnd();



	c += Tabs() + name + " = *reinterpret_cast<byte8 **>(" + name + " + 0x140);" + NEW_LINE;
	c += Tabs() + "if (!" + name + ")" + NEW_LINE;

	ScopeStart();

	c += Tabs() + returnal + ";" + NEW_LINE;

	ScopeEnd();



	c += Tabs() + name + " = *reinterpret_cast<byte8 **>(" + name + " + 0x468);" + NEW_LINE;
	c += Tabs() + "if (!" + name + ")" + NEW_LINE;

	ScopeStart();

	c += Tabs() + returnal + ";" + NEW_LINE;

	ScopeEnd();



	c += Tabs() + "auto & cameraData = *reinterpret_cast<CameraData *>(" + name + ");" + NEW_LINE;



	return false;
}],

];

let itemsKyrie =
[
	[ "Kyrie/Vars.ixx"    , "", false, [] ],
	[ "Kyrie/Internal.ixx", "", false, [] ],
	[ "Kyrie/Steam.ixx"   , "", false, [] ],
	[ "Kyrie/Global.ixx"  , "", true , [] ],
	[ "Kyrie/Config.ixx"  , "", true, [] ],
	[ "Kyrie/File.ixx"    , "", false, [] ],
	[ "Kyrie/Graphics.ixx", "", false, [] ],
	[ "Kyrie/Input.ixx"   , "", false, [] ],
	[ "Kyrie/Actor.ixx"   , "", true , [] ],
	[ "Kyrie/Arcade.ixx"  , "", true , [] ],
	[ "Kyrie/Camera.ixx"  , "", false, [] ],
	[ "Kyrie/Speed.ixx"   , "", true , [] ],
	[ "Kyrie/Training.ixx", "", false, [] ],
	[ "Kyrie/Window.ixx"  , "", false, [] ],
	[ "Kyrie/Event.ixx"   , "", true , [] ],
	[ "Kyrie/Scene.ixx"   , "", false, [] ],
	[ "GlobalBase.ixx"    , "", false, [] ],
	[ "GUIBase.ixx"       , "", false, [] ],
	[ "Kyrie/GUI.ixx"     , "", true , [] ],
	[ "HooksBase.ixx"     , "", false, [] ],
	[ "Kyrie/Hooks.ixx"   , "", false, [] ],
	[ "Kyrie/Kyrie.cpp"   , "", false, [] ],
];

let itemsKyrieActor =
[
	[ "Kyrie/Actor.ixx", "", true, [] ],
];

let itemsKyrieGUI =
[
	[ "GlobalBase.ixx" , "", false, [] ],
	[ "GUIBase.ixx"    , "", false, [] ],
	[ "Kyrie/GUI.ixx"  , "", true , [] ],
	[ "HooksBase.ixx"  , "", false, [] ],
	[ "Kyrie/Hooks.ixx", "", false, [] ],
];

let linkerArgsKyrie =
[
	"/NOLOGO",
	"/DLL",
	"/MACHINE:X86",
	"/DYNAMICBASE",
	"/DEBUG:FULL",
	"/OPT:REF",
	"/OPT:ICF",
	"/NODEFAULTLIB",
];

let libsKyrie = [];

libsKyrie = AddFront
(
	libsKyrie,
	libs_x86_32
);

// #endregion



// #region Verify

let compilerArgsVerify = [];

compilerArgsVerify = AddFront
(
	compilerArgsVerify,
	compilerArgs_x86_64
);

let itemsVerify =
[
	[ "verifyWindows.cpp", "", false, [] ],
	[ "verifyDXGI.cpp"   , "", false, [] ],
	[ "verifyD3D10.cpp"  , "", false, [] ],
	[ "verifyD3D11.cpp"  , "", false, [] ],
	[ "verifyDI8.cpp"    , "", false, [] ],
	[ "verifyXI.cpp"     , "", false, [] ],
];

// #endregion






// #region CleanPDB

let compilerArgsCleanPDB = [];

compilerArgsCleanPDB = AddFront
(
	compilerArgsCleanPDB,
	compilerArgs_x86_64
);



let itemsCleanPDB =
[
	[ "CleanPDB.cpp", "", false, [] ],
];

let linkerArgsCleanPDB =
[
	"/NOLOGO",
	"/MACHINE:X64",
	"/SUBSYSTEM:CONSOLE",
	"/DYNAMICBASE",
	"/DEBUG:FULL",
	"/OPT:REF",
	"/OPT:ICF",
	"/NODEFAULTLIB",
];

let libsCleanPDB = [];

libsCleanPDB = AddFront
(
	libsCleanPDB,
	libs_x86_64
);



// #endregion





function CleanPDB(location)
{
	ClearAll();

	c += "CleanPDB.exe \"" + location + "\"";

	try
	{
		child_process.execSync
		(
			c,
			{
				stdio: "inherit",
				encoding: "utf8"
			}
		);
	}
	catch(error)
	{
		return true;
	}

	return false;
}


















































// $FunctionDataStart

function CompileCore_x86_64()
{
	return CompileLoop
	(
		compilerArgsCore_x86_64,
		[],
		itemsCore_x86_64
	);
}

function CompileCoreNoGUI_x86_64()
{
	return CompileLoop
	(
		compilerArgsCore_x86_64,
		[],
		itemsCoreNoGUI_x86_64
	);
}

function CompileCore_x86_32()
{
	return CompileLoop
	(
		compilerArgsCore_x86_32,
		[],
		itemsCore_x86_32
	);
}

function CompileCoreNoGUI_x86_32()
{
	return CompileLoop
	(
		compilerArgsCore_x86_32,
		[],
		itemsCoreNoGUI_x86_32
	);
}

function CompileImGui_x86_64()
{
	return CompileLoop
	(
		compilerArgsImGui_x86_64,
		[],
		itemsImGui_x86_64
	);
}

function CompileImGui_x86_32()
{
	return CompileLoop
	(
		compilerArgsImGui_x86_32,
		[],
		itemsImGui_x86_32
	);
}

function CompileZLib()
{
	return CompileLoop
	(
		compilerArgsZLib,
		[],
		itemsZLib
	);
}

function LinkZLib()
{
	return Link
	(
		linkerArgsZLib,
		[],
		LOCATION_ZLIB,
		LinkFlags_Static
	);
}

function BuildZLib()
{
	if (CompileZLib())
	{
		return true;
	}

	return LinkZLib();
}

function CompileLibZip()
{
	return CompileLoop
	(
		compilerArgsLibZip,
		[],
		itemsLibZip
	);
}

function LinkLibZip()
{
	return Link
	(
		linkerArgsLibZip,
		[],
		LOCATION_LIBZIP,
		LinkFlags_Static
	);
}

function BuildLibZip()
{
	if (CompileLibZip())
	{
		return true;
	}

	return LinkLibZip();
}

function CompileLoader_x86_64()
{
	return CompileLoop
	(
		compilerArgsLoader_x86_64,
		[],
		itemsLoader_x86_64
	);
}

function CompileLoaderFull_x86_64()
{
	if (CompileCoreNoGUI_x86_64())
	{
		return true;
	}

	return CompileLoader_x86_64();
}

function LinkLoader_x86_64()
{
	return Link
	(
		linkerArgsLoader_x86_64,
		libsLoader_x86_64,
		LOCATION_LOADER_X86_64
	);
}

function BuildLoader_x86_64()
{
	if (CompileLoader_x86_64())
	{
		return true;
	}

	return LinkLoader_x86_64();
}

function BuildLoaderFull_x86_64()
{
	if (CompileLoaderFull_x86_64())
	{
		return true;
	}

	return LinkLoader_x86_64();
}

function CompileLoader_x86_32()
{
	return CompileLoop
	(
		compilerArgsLoader_x86_32,
		[],
		itemsLoader_x86_32
	);
}

function CompileLoaderFull_x86_32()
{
	if (CompileCoreNoGUI_x86_32())
	{
		return true;
	}

	return CompileLoader_x86_32();
}

function LinkLoader_x86_32()
{
	return Link
	(
		linkerArgsLoader_x86_32,
		libsLoader_x86_32,
		LOCATION_LOADER_X86_32
	);
}

function BuildLoader_x86_32()
{
	if (CompileLoader_x86_32())
	{
		return true;
	}

	return LinkLoader_x86_32();
}

function BuildLoaderFull_x86_32()
{
	if (CompileLoaderFull_x86_32())
	{
		return true;
	}

	return LinkLoader_x86_32();
}

function CompileEva()
{
	return CompileLoop
	(
		compilerArgsEva,
		helpersEva,
		itemsEva
	);
}

function CompileEvaActor()
{
	return CompileLoop
	(
		compilerArgsEva,
		helpersEva,
		itemsEvaActor
	);
}

function CompileEvaGUI()
{
	return CompileLoop
	(
		compilerArgsEva,
		helpersEva,
		itemsEvaGUI
	);
}

function CompileEvaActorGUI()
{
	if (CompileEvaActor())
	{
		return true;
	}

	return CompileEvaGUI();
}

function CompileEvaFull()
{
	if (CompileCore_x86_64())
	{
		return true;
	}

	if (CompileImGui_x86_64())
	{
		return true;
	}

	return CompileEva();
}

function LinkEva()
{
	return Link
	(
		linkerArgsEva,
		libsEva,
		LOCATION_EVA
	);
}

function BuildEva()
{
	if (CompileEva())
	{
		return true;
	}

	return LinkEva();
}

function BuildEvaActor()
{
	if (CompileEvaActor())
	{
		return true;
	}

	return LinkEva();
}

function BuildEvaGUI()
{
	if (CompileEvaGUI())
	{
		return true;
	}

	return LinkEva();
}

function BuildEvaActorGUI()
{
	if (CompileEvaActorGUI())
	{
		return true;
	}

	return LinkEva();
}

function BuildEvaFull()
{
	if (CompileEvaFull())
	{
		return true;
	}

	return LinkEva();
}

function CleanPDBEva()
{
	return CleanPDB(LOCATION_EVA_PDB);
}

function CompileLucia()
{
	return CompileLoop
	(
		compilerArgsLucia,
		helpersLucia,
		itemsLucia
	);
}

function CompileLuciaFull()
{
	if (CompileCore_x86_64())
	{
		return true;
	}

	if (CompileImGui_x86_64())
	{
		return true;
	}

	return CompileLucia();
}

function LinkLucia()
{
	return Link
	(
		linkerArgsLucia,
		libsLucia,
		LOCATION_LUCIA
	);
}

function BuildLucia()
{
	if (CompileLucia())
	{
		return true;
	}

	return LinkLucia();
}

function BuildLuciaFull()
{
	if (CompileLuciaFull())
	{
		return true;
	}

	return LinkLucia();
}

function CleanPDBLucia()
{
	return CleanPDB(LOCATION_LUCIA_PDB);
}

function CompileMary()
{
	return CompileLoop
	(
		compilerArgsMary,
		helpersMary,
		itemsMary
	);
}

function CompileMaryActor()
{
	return CompileLoop
	(
		compilerArgsMary,
		helpersMary,
		itemsMaryActor
	);
}

function CompileMaryGUI()
{
	return CompileLoop
	(
		compilerArgsMary,
		helpersMary,
		itemsMaryGUI
	);
}

function CompileMaryActorGUI()
{
	if (CompileMaryActor())
	{
		return true;
	}

	return CompileMaryGUI();
}

function CompileMaryFull()
{
	if (CompileCore_x86_64())
	{
		return true;
	}

	if (CompileImGui_x86_64())
	{
		return true;
	}

	return CompileMary();
}

function LinkMary()
{
	return Link
	(
		linkerArgsMary,
		libsMary,
		LOCATION_MARY
	);
}

function BuildMary()
{
	if (CompileMary())
	{
		return true;
	}

	return LinkMary();
}

function BuildMaryActor()
{
	if (CompileMaryActor())
	{
		return true;
	}

	return LinkMary();
}

function BuildMaryGUI()
{
	if (CompileMaryGUI())
	{
		return true;
	}

	return LinkMary();
}

function BuildMaryActorGUI()
{
	if (CompileMaryActorGUI())
	{
		return true;
	}

	return LinkMary();
}

function BuildMaryFull()
{
	if (CompileMaryFull())
	{
		return true;
	}

	return LinkMary();
}

function CleanPDBMary()
{
	return CleanPDB(LOCATION_MARY_PDB);
}

function CompileKyrie()
{
	return CompileLoop
	(
		compilerArgsKyrie,
		helpersKyrie,
		itemsKyrie
	);
}

function CompileKyrieActor()
{
	return CompileLoop
	(
		compilerArgsKyrie,
		helpersKyrie,
		itemsKyrieActor
	);
}

function CompileKyrieGUI()
{
	return CompileLoop
	(
		compilerArgsKyrie,
		helpersKyrie,
		itemsKyrieGUI
	);
}

function CompileKyrieActorGUI()
{
	if (CompileKyrieActor())
	{
		return true;
	}

	return CompileKyrieGUI();
}

function CompileKyrieFull()
{
	if (CompileCore_x86_32())
	{
		return true;
	}

	if (CompileImGui_x86_32())
	{
		return true;
	}

	return CompileKyrie();
}

function LinkKyrie()
{
	return Link
	(
		linkerArgsKyrie,
		libsKyrie,
		LOCATION_KYRIE
	);
}

function BuildKyrie()
{
	if (CompileKyrie())
	{
		return true;
	}

	return LinkKyrie();
}

function BuildKyrieActor()
{
	if (CompileKyrieActor())
	{
		return true;
	}

	return LinkKyrie();
}

function BuildKyrieGUI()
{
	if (CompileKyrieGUI())
	{
		return true;
	}

	return LinkKyrie();
}

function BuildKyrieActorGUI()
{
	if (CompileKyrieActorGUI())
	{
		return true;
	}

	return LinkKyrie();
}

function BuildKyrieFull()
{
	if (CompileKyrieFull())
	{
		return true;
	}

	return LinkKyrie();
}

function CleanPDBKyrie()
{
	return CleanPDB(LOCATION_KYRIE_PDB);
}

function CompileVerify()
{
	return CompileLoop
	(
		compilerArgsVerify,
		[],
		itemsVerify
	);
}

function CompileCleanPDB()
{
	return CompileLoop
	(
		compilerArgsCleanPDB,
		[],
		itemsCleanPDB
	);
}

function CompileCleanPDBFull()
{
	if (CompileCoreNoGUI_x86_64())
	{
		return true;
	}

	return CompileCleanPDB();
}

function LinkCleanPDB()
{
	return Link
	(
		linkerArgsCleanPDB,
		libsCleanPDB,
		"CleanPDB.exe"
	);
}

function BuildCleanPDB()
{
	if (CompileCleanPDB())
	{
		return true;
	}

	return LinkCleanPDB();
}

function BuildCleanPDBFull()
{
	if (CompileCleanPDBFull())
	{
		return true;
	}

	return LinkCleanPDB();
}

// $FunctionDataEnd



let args = process.argv;

if (args.length < 3)
{
	console.log("g_Too few arguments.");

	console.log(args);

	return;
}



{
	let argCount = args.length;

	if
	(
		(argCount == 4) &&
		(args[2] == "platform")
	)
	{
		let name = args[3];

		config.platform = name;

		SaveConfig();

		//console.log(config);

		return;
	}
}



let items =
[
	// $ActionDataStart

	[
		"compileCore_x86_64",
		CompileCore_x86_64
	],
	[
		"compileCoreNoGUI_x86_64",
		CompileCoreNoGUI_x86_64
	],
	[
		"compileCore_x86_32",
		CompileCore_x86_32
	],
	[
		"compileCoreNoGUI_x86_32",
		CompileCoreNoGUI_x86_32
	],
	[
		"compileImGui_x86_64",
		CompileImGui_x86_64
	],
	[
		"compileImGui_x86_32",
		CompileImGui_x86_32
	],
	[
		"compileZLib",
		CompileZLib
	],
	[
		"linkZLib",
		LinkZLib
	],
	[
		"buildZLib",
		BuildZLib
	],
	[
		"compileLibZip",
		CompileLibZip
	],
	[
		"linkLibZip",
		LinkLibZip
	],
	[
		"buildLibZip",
		BuildLibZip
	],
	[
		"compileLoader_x86_64",
		CompileLoader_x86_64
	],
	[
		"compileLoaderFull_x86_64",
		CompileLoaderFull_x86_64
	],
	[
		"linkLoader_x86_64",
		LinkLoader_x86_64
	],
	[
		"buildLoader_x86_64",
		BuildLoader_x86_64
	],
	[
		"buildLoaderFull_x86_64",
		BuildLoaderFull_x86_64
	],
	[
		"compileLoader_x86_32",
		CompileLoader_x86_32
	],
	[
		"compileLoaderFull_x86_32",
		CompileLoaderFull_x86_32
	],
	[
		"linkLoader_x86_32",
		LinkLoader_x86_32
	],
	[
		"buildLoader_x86_32",
		BuildLoader_x86_32
	],
	[
		"buildLoaderFull_x86_32",
		BuildLoaderFull_x86_32
	],
	[
		"compileEva",
		CompileEva
	],
	[
		"compileEvaActor",
		CompileEvaActor
	],
	[
		"compileEvaGUI",
		CompileEvaGUI
	],
	[
		"compileEvaActorGUI",
		CompileEvaActorGUI
	],
	[
		"compileEvaFull",
		CompileEvaFull
	],
	[
		"linkEva",
		LinkEva
	],
	[
		"buildEva",
		BuildEva
	],
	[
		"buildEvaActor",
		BuildEvaActor
	],
	[
		"buildEvaGUI",
		BuildEvaGUI
	],
	[
		"buildEvaActorGUI",
		BuildEvaActorGUI
	],
	[
		"buildEvaFull",
		BuildEvaFull
	],
	[
		"cleanPDBEva",
		CleanPDBEva
	],
	[
		"compileLucia",
		CompileLucia
	],
	[
		"compileLuciaFull",
		CompileLuciaFull
	],
	[
		"linkLucia",
		LinkLucia
	],
	[
		"buildLucia",
		BuildLucia
	],
	[
		"buildLuciaFull",
		BuildLuciaFull
	],
	[
		"cleanPDBLucia",
		CleanPDBLucia
	],
	[
		"compileMary",
		CompileMary
	],
	[
		"compileMaryActor",
		CompileMaryActor
	],
	[
		"compileMaryGUI",
		CompileMaryGUI
	],
	[
		"compileMaryActorGUI",
		CompileMaryActorGUI
	],
	[
		"compileMaryFull",
		CompileMaryFull
	],
	[
		"linkMary",
		LinkMary
	],
	[
		"buildMary",
		BuildMary
	],
	[
		"buildMaryActor",
		BuildMaryActor
	],
	[
		"buildMaryGUI",
		BuildMaryGUI
	],
	[
		"buildMaryActorGUI",
		BuildMaryActorGUI
	],
	[
		"buildMaryFull",
		BuildMaryFull
	],
	[
		"cleanPDBMary",
		CleanPDBMary
	],
	[
		"compileKyrie",
		CompileKyrie
	],
	[
		"compileKyrieActor",
		CompileKyrieActor
	],
	[
		"compileKyrieGUI",
		CompileKyrieGUI
	],
	[
		"compileKyrieActorGUI",
		CompileKyrieActorGUI
	],
	[
		"compileKyrieFull",
		CompileKyrieFull
	],
	[
		"linkKyrie",
		LinkKyrie
	],
	[
		"buildKyrie",
		BuildKyrie
	],
	[
		"buildKyrieActor",
		BuildKyrieActor
	],
	[
		"buildKyrieGUI",
		BuildKyrieGUI
	],
	[
		"buildKyrieActorGUI",
		BuildKyrieActorGUI
	],
	[
		"buildKyrieFull",
		BuildKyrieFull
	],
	[
		"cleanPDBKyrie",
		CleanPDBKyrie
	],
	[
		"compileVerify",
		CompileVerify
	],
	[
		"compileCleanPDB",
		CompileCleanPDB
	],
	[
		"compileCleanPDBFull",
		CompileCleanPDBFull
	],
	[
		"linkCleanPDB",
		LinkCleanPDB
	],
	[
		"buildCleanPDB",
		BuildCleanPDB
	],
	[
		"buildCleanPDBFull",
		BuildCleanPDBFull
	],

	// $ActionDataEnd



	[
		"clean", function()
		{
			Clean();

			return false;
		}
	],



	[
		"compile", function()
		{
			if (args.length < 4)
			{
				console.log("c_Too few arguments.");

				return true;
			}
			else if (args.length > 5)
			{
				console.log("Too many arguments.");

				return true;
			}

			return CompileOnce
			(
				[
					"/nologo",
					"/c",
					"/std:c++latest",
					"/permissive-",
					"/experimental:module",
					"/Zc:forScope",
					"/Zc:inline",
					"/Zc:preprocessor",
					"/Zc:wchar_t",
					"/Zc:externC-",
					"/W3",
					// "/wd4005",
					// "/wd5105",
					"/O2",
					"/Oi",
					"/Gy",
					"/Zi",
					"/EHsc",
				],
				[],
				[ args[3], args[4], false, [] ]
			);
		}
	],



	[
		"preprocess", function()
		{
			if (args.length < 4)
			{
				console.log("Too few arguments.");

				return true;
			}
			else if (args.length > 4)
			{
				console.log("Too many arguments.");

				return true;
			}

			return CompileOnce
			(
				[
					"/nologo",
					"/c",
					"/std:c++latest",
					"/permissive-",
					"/experimental:module",
					"/Zc:forScope",
					"/Zc:inline",
					"/Zc:preprocessor",
					"/Zc:wchar_t",
					"/Zc:externC-",
					"/W3",
					"/O2",
					"/Oi",
					"/Gy",
					"/Zi",
					"/EHsc",
					"/P",
					"/C",
				],
				[],
				[ args[3], "", false, [] ]
			);
		}
	],



	[
		"link", function()
		{
			if (args.length < 4)
			{
				console.log("Too few arguments.");

				return true;
			}
			else if (args.length > 4)
			{
				console.log("Too many arguments.");

				return true;
			}

			return Link
			(
				[
					"/NOLOGO",
					//"/MACHINE:X64",
					"/MACHINE:X86",
					"/SUBSYSTEM:CONSOLE",
					"/DYNAMICBASE",
					"/DEBUG:FULL",
					"/OPT:REF",
					"/OPT:ICF",
					"/NODEFAULTLIB",
				],
				[
					"msvcrt.lib",
					"vcruntime.lib",
					"ucrt.lib",
					"kernel32.lib",
					"user32.lib",
					"shell32.lib",
					"advapi32.lib",
					"libcpmt.lib",
					"gdi32.lib",
					"winspool.lib",
					"comdlg32.lib",
					"ole32.lib",
					"oleaut32.lib",
					"uuid.lib",
					"odbc32.lib",
					"odbccp32.lib",
					"imm32.lib",
					"d3d11.lib",
					"d3dcompiler.lib",
					"dinput8.lib",
					"dxguid.lib",
					"xinput.lib",
				],
				args[3]
			);
		}
	],



	[
		"buildAll", function()
		{
			let items =
			[
				[ "ZLib"  , "x86_64", BuildZLib              ],
				[ "LibZip", "x86_64", BuildLibZip            ],
				[ "Loader", "x86_64", BuildLoaderFull_x86_64 ],
				[ "Eva"   , "x86_64", BuildEvaFull           ],
				[ "Lucia" , "x86_64", BuildLuciaFull         ],
				[ "Mary"  , "x86_64", BuildMaryFull          ],
				[ "Loader", "x86_32", BuildLoaderFull_x86_32 ],
				[ "Kyrie" , "x86_32", BuildKyrieFull         ],
			];

			for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
			{
				let item = items[itemIndex];

				let name     = item[0];
				let platform = item[1];
				let func     = item[2];



				console.log(name + " " + platform);
				console.log("");

				SetEnv(platform);

				Clean();
				console.log("");

				if (func())
				{
					return true;
				}

				if (itemIndex < (items.length - 1))
				{
					console.log("");
				}
			}



			return false;
		}
	],
];



for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
{
	let item = items[itemIndex];

	let name = item[0];
	let func = item[1];

	if (args[2] == name)
	{
		func();

		return;
	}
}



console.log("No Match");
