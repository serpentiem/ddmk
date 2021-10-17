// #region

"use strict";

let fs = require("fs");
let process = require("process");
let vm = require("vm");

vm.runInThisContext
(
	fs.readFileSync("../core.js"  , "utf8") +
	fs.readFileSync("dmc4_core.js", "utf8")
);

ClearAll();



let location = "../Kyrie/Internal.ixx";

let file = fs.readFileSync(location, "utf8");

let tagName = "Data";



ClearAll();



let c_until = "";
let c_after = "";
let c_new   = "";

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

// #endregion









let items =
[
	[ 0x5F1540, "byte8 *", "__stdcall" , "const char *, byte8 *"                          , "Get Map Table"     ],







	// [ 0x4D27D0, "byte8 *", "__stdcall" , ""                                               , "CreateActorDante"  ],
	// [ 0x50EE10, "byte8 *", "__stdcall" , ""                                               , "CreateActorNero"   ],
	// [ 0xCB400 , "byte8 *", "__stdcall" , ""                                               , "CreateActorVergil" ],
	// [ 0xC69C0 , "byte8 *", "__stdcall" , ""                                               , "CreateActorTrish"  ],
	// [ 0xC5140 , "byte8 *", "__stdcall" , ""                                               , "CreateActorLady"   ],
	// [ 0x4D2800, "byte8 *", "__stdcall" , "byte8 * actorData"                              , "UpdateActorDante"  ],
	// [ 0x50EEF0, "byte8 *", "__stdcall" , "byte8 * actorData"                              , "UpdateActorNero"   ],
	// [ 0xCB430 , "byte8 *", "__stdcall" , "byte8 * actorData"                              , "UpdateActorVergil" ],
	// [ 0xC69F0 , "byte8 *", "__stdcall" , "byte8 * actorData"                              , "UpdateActorTrish"  ],
	// [ 0xC5170 , "byte8 *", "__stdcall" , "byte8 * actorData"                              , "UpdateActorLady"   ],





	[ 0x6C32E0, "bool"   , "__fastcall", "byte8 *, void *, uint8, byte8 *, uint32, uint32", "Spawn"             ],
];

// @Research: FunctionFlags_SaveRegisters may not be required.






// Typedefs
{

for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
{
	let item = items[itemIndex];

	let off               = item[0];
	let returnType        = item[1];
	let callingConvention = item[2];
	let args              = item[3];
	let hint              = item[4];

	let offName = LeadingZero
	(
		off,
		0,
		(StringFlags_Hex | StringFlags_NoPrefix)
	);

	c += Tabs() + "export typedef " + returnType + "(" + callingConvention + " * func_" + offName + "_t)(" + args + ");";

	if (hint != "")
	{
		c += Tabs() + " // " + hint;
	}

	c += NEW_LINE;
}

c += NEW_LINE;

}



// Vars
{

for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
{
	let item = items[itemIndex];

	let off               = item[0];
	let returnType        = item[1];
	let callingConvention = item[2];
	let args              = item[3];
	let hint              = item[4];

	let offName = LeadingZero
	(
		off,
		0,
		(StringFlags_Hex | StringFlags_NoPrefix)
	);

	c += Tabs() + "export func_" + offName + "_t func_" + offName + " = 0;" + NEW_LINE;
}

c += NEW_LINE;

}



// Init
{

c += Tabs() + "export void Internal_Init()" + NEW_LINE;

ScopeStart();

c += Tabs() + "LogFunction();" + NEW_LINE;
c += NEW_LINE;

for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
{
	let item = items[itemIndex];

	let off               = item[0];
	let returnType        = item[1];
	let callingConvention = item[2];
	let args              = item[3];
	let hint              = item[4];



	let offName = LeadingZero
	(
		off,
		0,
		(StringFlags_Hex | StringFlags_NoPrefix)
	);



	let argCount = 0;

	if (args != "")
	{
		argCount = 1;

		let matches = args.match(/,/g);
		if (matches)
		{
			argCount = (matches.length + 1);
		}
	}



	if (callingConvention == "__fastcall")
	{
		if (argCount >= 2)
		{
			argCount -= 2;
		}
		else if (argCount >= 1)
		{
			argCount--;
		}
	}



	let noResult = (returnType == "void");

	let registerCount = (noResult) ? 9 : 8;



	ScopeStart();



	if (argCount > 0)
	{
		// sect1
		{
			c += Tabs() + "constexpr byte8 sect1[] =" + NEW_LINE;

			ScopeStart();

			{
				let size = (argCount * 4);

				c += Tabs() + "0x83, 0xEC, ";

				c += LeadingZero
				(
					size,
					2,
					StringFlags_Hex
				);

				c += ",             // sub esp,";

				c += LeadingZero
				(
					size,
					2,
					(StringFlags_Hex | StringFlags_NoPrefix)
				);

				c += NEW_LINE;
			}

			c += Tabs() + "0x51,                         // push ecx" + NEW_LINE;
			c += Tabs() + "0x56,                         // push esi" + NEW_LINE;
			c += Tabs() + "0x57,                         // push edi" + NEW_LINE;

			{
				c += Tabs() + "0xB9, ";

				c += LeadingZero
				(
					argCount,
					2,
					StringFlags_Hex
				);

				c += ", 0x00, 0x00, 0x00, // mov ecx,";

				c += LeadingZero
				(
					argCount,
					8,
					(StringFlags_Hex | StringFlags_NoPrefix)
				);

				c += NEW_LINE;
			}

			{
				let size = ((registerCount + 1) * 4); // Registers + return address!

				c += Tabs() + "0x8D, 0x75, ";

				c += LeadingZero
				(
					size,
					2,
					StringFlags_Hex
				);

				c += ",             // lea esi,[ebp+";

				c += LeadingZero
				(
					size,
					2,
					(StringFlags_Hex | StringFlags_NoPrefix)
				);

				c += "]" + NEW_LINE;
			}

			c += Tabs() + "0x8D, 0x7C, 0x24, 0x0C,       // lea edi,[esp+0C]" + NEW_LINE;
			c += Tabs() + "0xF3, 0xA5,                   // repe movsd" + NEW_LINE;
			c += Tabs() + "0x5F,                         // pop edi" + NEW_LINE;
			c += Tabs() + "0x5E,                         // pop esi" + NEW_LINE;
			c += Tabs() + "0x59,                         // pop ecx" + NEW_LINE;

			ScopeEnd
			(
				"}",
				ScopeFlags_Semicolon
			);
		}



		// sect2
		{
			c += Tabs() + "constexpr byte8 sect2[] =" + NEW_LINE;

			ScopeStart();

			if (argCount == 0)
			{
				c += Tabs() + "0xC3, // ret";
			}
			else
			{
				let size = (argCount * 4);

				c += Tabs() + "0xC2, "

				c += LeadingZero
				(
					size,
					2,
					StringFlags_Hex
				);

				c += ", 0x00, // ret "

				c += LeadingZero
				(
					size,
					4,
					(StringFlags_Hex | StringFlags_NoPrefix)
				);

				c += NEW_LINE;
			}

			ScopeEnd
			(
				"}",
				ScopeFlags_Semicolon
			);
		}

		c += NEW_LINE;
	}



	c += Tabs() + "auto func = CreateFunction((appBaseAddr + 0x" + offName + "), 0, ";

	if
	(
		noResult ||
		(argCount > 0)
	)
	{
		c += "(";
	}

	c += "FunctionFlags_SaveRegisters";



	if (noResult)
	{
		c += " | FunctionFlags_NoResult";
	}

	if (argCount > 0)
	{
		c += " | FunctionFlags_NoReturn";
	}



	if
	(
		noResult ||
		(argCount > 0)
	)
	{
		c += ")";
	}



	if (argCount > 0)
	{
		c += ", 0, sizeof(sect1), sizeof(sect2)";
	}





	c += ");" + NEW_LINE;



	if (argCount > 0)
	{
		c += Tabs() + "CopyMemory(func.sect1, sect1, sizeof(sect1));" + NEW_LINE;
		c += Tabs() + "CopyMemory(func.sect2, sect2, sizeof(sect2));" + NEW_LINE;
	}



	c += Tabs() + "func_" + offName + " = reinterpret_cast<func_" + offName + "_t>(func.addr);" + NEW_LINE;



	ScopeEnd();
}



ScopeEnd();

c += NEW_LINE;

}



CleanStream();

c_new = c;

ClearAll();



file = c_until + c_new + c_after;



fs.writeFileSync(location, file);
