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


g_platformName = "x86_32";
g_pointerSize = 4;





ClearAll();

// #endregion



let location = "../Kyrie/Vars.ixx";

let file = fs.readFileSync(location, "utf8");



// #region Feed

function FeedStruct
(
	name,
	items,
	size    = 0,
	tagName = name
)
{
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

	c_new = c;

	ClearAll();



	file = c_until + c_new + c_after;
}

function FeedEnum
(
	name,
	items,
	tagName = name
)
{
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



	c += "export namespaceStart(" + name + ");" + NEW_LINE;

	CreateEnum
	(
		"",
		items,
		"",
		EnumFlags_UpperCase
	);

	c += "namespaceEnd();" + NEW_LINE;
	c += NEW_LINE;

	CleanStream();

	c_new = c;

	ClearAll();



	file = c_until + c_new + c_after;
}

// #endregion








// #region CharacterData
{

const SIZE_BASE = 64;

let itemsBase =
[
	[ "unlocks[8]"  , "bool"  , [], 0    ],
	[ "expertise[8]", "byte32", [], 0x18 ],
	[ "costume"     , "uint32", [], 0x38 ],
];

let itemsDante =
[
	[ "unlocks2[11]"  , "bool"  , [], 0x40 ],
	[ "styleLevels[4]", "uint32", [], 0x4C ],
];

let itemsNero =
[
	[ "unlocks2[4]"          , "bool" , [], 0x40 ],
	[ "snatchLevel"          , "uint8", [], 0x44 ],
	[ "extraExceedCount"     , "uint8", [], 0x45 ],
	[ "extraTableHopperCount", "uint8", [], 0x46 ],
];

let itemsVergil =
[
	[ "unlocks2[2]"        , "bool" , [], 0x40 ],
	[ "summonedSwordsLevel", "uint8", [], 0x42 ],
];

let itemsTrish =
[
	[ "unlocks2[1]", "bool", [], 0x40 ],
];

let itemsLady =
[
	[ "kalinaAnnChargeCount", "uint8", [], 0x40 ],
];

let tagName = "CharacterData";



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



// Base
{

let structName = "CharacterDataBase";

c += Tabs() + "// " + structName + NEW_LINE;
c += NEW_LINE;

CreateStruct
(
	structName,
	itemsBase,
	SIZE_BASE,
	0,
	StructFlags_Export
);



typeSizes.push([ structName, SIZE_BASE ]);



ClearAsserts();

CreateStructAsserts
(
	structName,
	itemsBase,
	SIZE_BASE,
	0,
	StructFlags_NoTypeAssert
);

MergeAsserts();
FeedAsserts();

}



// Derived
{

let helpers =
[
	[ "Dante" , itemsDante  ],
	[ "Nero"  , itemsNero   ],
	[ "Vergil", itemsVergil ],
	[ "Trish" , itemsTrish  ],
	[ "Lady"  , itemsLady   ],
];

for (let index = 0; index < helpers.length; index++)
{
	let helper = helpers[index];

	let name  = helper[0];
	let items = helper[1];

	let structName = "CharacterData" + name;



	c += Tabs() + "// " + structName + NEW_LINE;
	c += NEW_LINE;



	CreateStruct
	(
		structName + " : CharacterDataBase",
		items,
		0,
		SIZE_BASE,
		StructFlags_Export
	);



	let size = GetStructSize(items);

	typeSizes.push([ structName, size ]);



	ClearAsserts();

	CreateStructAsserts
	(
		structName,
		items,
		0,
		SIZE_BASE,
		(StructFlags_NoTypeAssert | StructFlags_NoSizeAssert)
	);

	MergeAsserts();
	FeedAsserts();
}

}



// Main
{

let items =
[
	[ "hitPoints"  , "float"            , [], 0x78  ],
	[ "magicPoints", "float"            , [], 0x7C  ],
	[ "Dante"      , "CharacterDataDante" , [], 0x168 ],
	[ "Nero"       , "CharacterDataNero"  , [], 0x270 ],
	[ "Vergil"     , "CharacterDataVergil", [], 0x360 ],
	[ "Trish"      , "CharacterDataTrish" , [], 0x45C ],
	[ "Lady"       , "CharacterDataLady"  , [], 0x564 ],
];

let structName = "CharacterData";



c += Tabs() + "// " + structName + NEW_LINE;
c += NEW_LINE;



CreateStruct
(
	structName,
	items,
	0,
	0,
	StructFlags_Export
);



ClearAsserts();

CreateStructAsserts
(
	structName,
	items,
	0,
	0,
	StructFlags_NoTypeAssert
);

MergeAsserts();
FeedAsserts();

}



CleanStream();

c_new = c;

ClearAll();



file = c_until + c_new + c_after;

}
// #endregion



// #region SessionData
{

let items =
[
	[ "mainActorBaseAddr", "byte8 *"          , [], 0x24  ],
	[ "mission"          , "uint32"           , [], 0x150 ],
	[ "game"             , "uint32"           , [], 0x1BC ],
	[ "mode"             , "uint32"           , [], 0x240 ],
	[ "characterData"    , "CharacterDataBase", [], 0x4B8 ],
];

FeedStruct
(
	"SessionData",
	items
);

}
// #endregion








// #region PlayerActorData
{

let items =
[
	[ "position"      , "vec4"  , [], 0x40   ],
	[ "costume"       , "uint32", [], 0x19A8 ],
	[ "character"     , "uint32", [], 0x19AC ],
	[ "enable"        , "bool"  , [], 0x1A1D ],
	[ "hitPoints"     , "float" , [], 0x1B00 ],
	[ "maxHitPoints"  , "float" , [], 0x1B04 ],
	[ "magicPoints"   , "float" , [], 0x2504 ],
	[ "maxMagicPoints", "float" , [], 0x2508 ],
];

FeedStruct
(
	"PlayerActorData",
	items
);

}
// #endregion






// #region EventData
{

let items =
[
	[ "event", "uint8" , [], 4    ],
	[ "room" , "uint32", [], 0x30 ],
];

FeedStruct
(
	"EventData",
	items
);

}
// #endregion



// #region NextEventData
{

let items =
[
	[ "useDoor"    , "uint32", [], 0x84 ],
	[ "room"       , "uint32", [], 0x88 ],
	[ "position"   , "uint32", [], 0x8C ],
	[ "level"   , "uint32", [], 0x90 ],
	[ "usePosition", "bool"  , [], 0xA0 ],
];

FeedStruct
(
	"NextEventData",
	items
);

}
// #endregion



// #region SessionEventData
{

let items =
[
	[ "character", "uint8", [], 0x30 ],
];

FeedStruct
(
	"SessionEventData",
	items
);

}
// #endregion







// #region CameraData
{

let items =
[
	[ "height"        , "float", [], 0xD0 ],
	[ "tilt"          , "float", [], 0xD4 ],
	[ "distance"      , "float", [], 0xD8 ],
	[ "distanceLockOn", "float", [], 0xDC ],
	[ "fov"           , "float", [], 0xE4 ],
];

FeedStruct
(
	"CameraData",
	items
);

}
// #endregion









fs.writeFileSync(location, file);
