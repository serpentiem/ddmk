// @Todo: Unify functions so we only have to provide items.

let fs = require("fs");
let vm = require("vm");

vm.runInThisContext(fs.readFileSync("dmc3_core.js", "utf8"));

ClearAll();



// #region Mission Data
{

let items =
[
	[ "redOrbs"       , "uint32", [], 0x38 ],
	[ "itemCounts[62]", "uint8" , [], 0x3C ],
	[ "buyCounts[8]"  , "uint8" , [], 0x7A ],
	[ "frameCount"    , "uint32", [], 0xA8 ],
	[ "damage"        , "uint32", [], 0xAC ],
	[ "orbsCollected" , "uint32", [], 0xB0 ],
	[ "itemsUsed"     , "uint32", [], 0xB4 ],
	[ "killCount"     , "uint32", [], 0xB8 ],
];

const SIZE = 192;



CreateTuple
(
	"MissionData",
	items,
	SIZE,
	0,
	TupleFlags_Export
);



ClearAsserts();

CreateTupleAsserts
(
	"MissionData",
	items,
	SIZE,
	0,
	TupleFlags_NoTypeAssert
);

MergeAsserts();
FeedAsserts();

CleanStream();



let c_new = c;

c = "";

let filename = "../Mary/Vars.ixx";

let file = fs.readFileSync(filename, "utf8");

let lines = GetLines(file);

if
(
	!Tag_Init
	(
		lines,
		/\/\/ \$MissionDataStart$/,
		/\/\/ \$MissionDataEnd$/
	)
)
{
	console.log("Tag_Init failed.");

	return;
}

Tag_CopyUntil(lines);

c += c_new;

Tag_CopyAfter(lines);

fs.writeFileSync(filename, c);



ClearAll();

}
// #endregion

// #region Session Data
{

let items =
[
	[ "mission"              , "uint32", [], 0     ],
	[ "mode"                 , "uint32", [], 0xC   ],
	[ "oneHitKill"           , "bool"  , [], 0x10  ],
	[ "enableTutorial"       , "bool"  , [], 0x12  ],
	[ "useGoldOrb"           , "bool"  , [], 0x13  ],
	[ "character"            , "uint8" , [], 0x14  ],
	[ "bloodyPalace"         , "bool"  , [], 0x1C  ],
	[ "redOrbs"              , "uint32", [], 0x2C  ],
	[ "itemCounts[20]"       , "uint8" , [], 0x30  ],
	[ "unlock[14]"           , "bool"  , [], 0x46  ],
	[ "weapons[8]"           , "uint8" , [], 0x84  ],
	[ "rangedWeaponLevels[5]", "uint32", [], 0xA0  ],
	[ "meleeWeaponIndex"     , "uint32", [], 0xC8  ],
	[ "rangedWeaponIndex"    , "uint32", [], 0xCC  ],
	[ "costume"              , "uint8" , [], 0xD0  ],
	[ "unlockDevilTrigger"   , "bool"  , [], 0xD1  ],
	[ "hitPoints"            , "float" , [], 0xD4  ],
	[ "magicPoints"          , "float" , [], 0xD8  ],
	[ "style"                , "uint32", [], 0xDC  ],
	[ "styleLevel[6]"        , "uint32", [], 0xE0  ],
	[ "styleExperience[6]"   , "float" , [], 0xF8  ],
	[ "expertise[8]"         , "byte32", [], 0x110 ],
];



CreateTuple
(
	"SessionData",
	items,
	0,
	0,
	TupleFlags_Export
);



ClearAsserts();

CreateTupleAsserts
(
	"SessionData",
	items,
	0,
	0,
	TupleFlags_NoTypeAssert
);

MergeAsserts();
FeedAsserts();

CleanStream();



let c_new = c;

c = "";

let filename = "../Mary/Vars.ixx";

let file = fs.readFileSync(filename, "utf8");

let lines = GetLines(file);

if
(
	!Tag_Init
	(
		lines,
		/\/\/ \$SessionDataStart$/,
		/\/\/ \$SessionDataEnd$/
	)
)
{
	console.log("Tag_Init failed.");

	return;
}

Tag_CopyUntil(lines);

c += c_new;

Tag_CopyAfter(lines);

fs.writeFileSync(filename, c);



ClearAll();

}
// #endregion









