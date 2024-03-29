// #region

g_platform = "x86_32";
g_pointerSize = 4;

ClearAll();

let dmc4_typeSizes =
[
	[ "InputData", 12 ],
];

typeSizes_Reset();
typeSizes_Add(dmc4_typeSizes);

let location = "Kyrie/Vars.ixx";

file = fs.readFileSync(location, "utf8");

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

FeedStart(tagName);



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

FeedEnd();

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
	[ "event"         , "uint32", [], 0x10   ],
	[ "position"      , "vec4"  , [], 0x40   ],
	[ "size"          , "vec4"  , [], 0x60   ],
	[ "buttons[4]"    , "byte32", [], 0x1920 ],
	[ "directions[3]" , "uint32", [], 0x1938 ],
	[ "costume"       , "uint32", [], 0x19A8 ],
	[ "character"     , "uint32", [], 0x19AC ],
	[ "enable"        , "bool"  , [], 0x1A1D ],
	[ "hitPoints"     , "float" , [], 0x1B00 ],
	[ "maxHitPoints"  , "float" , [], 0x1B04 ],
	[ "rotation"      , "float" , [], 0x1C48 ],
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









// #region KeyboardData
{

let items =
[
	[ "flags[4]", "byte32", [], 0x120  ],
];

FeedStruct
(
	"KeyboardData",
	items
);

}
// #endregion


















const GAMEPAD_METADATA_SIZE = 0x2CC;
const GAMEPAD_DATA_SIZE     = 0x200;



// #region GamepadMetadata
{

let name = "GamepadMetadata";
let size = GAMEPAD_METADATA_SIZE;

let items =
[
	[ "playerIndex", "uint32", [], 0x10 ],
	[ "flags[2]", "byte32", [], 0x15C ],
];

FeedStruct
(
	name,
	items,
	size
);

typeSizes.push([ name, size ]);

}
// #endregion

// #region GamepadData
{

let name = "GamepadData";
let size = GAMEPAD_DATA_SIZE;

let items =
[
	[ "gamepadMetadataAddr", "GamepadMetadata *", [], 4 ],
];

FeedStruct
(
	name,
	items,
	size
);

typeSizes.push([ name, size ]);

}
// #endregion



// #region GamepadManager
{

let items =
[
	[ "gamepadMetadata[4]", "GamepadMetadata", [], 0x3C  ],
	[ "gamepadData[2]"    , "GamepadData",     [], 0xBC0 ],
];

FeedStruct
(
	"GamepadManager",
	items
);

}
// #endregion







fs.writeFileSync(location, file);
