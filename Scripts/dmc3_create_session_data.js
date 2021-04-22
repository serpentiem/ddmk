
// @Todo: Merge.


var fs = require("fs");

eval(fs.readFileSync("dmc3_core.js", "utf8"));

var items =
[
	[ "mission"           , "uint32", 0     ],
	[ "mode"              , "uint32", 0xC   ],
	[ "oneHitKill"        , "bool"  , 0x10  ],
	[ "enableTutorial"    , "bool"  , 0x12  ],
	[ "useGoldOrb"        , "bool"  , 0x13  ],
	[ "character"         , "uint8" , 0x14  ],
	[ "bloodyPalace"      , "bool"  , 0x1C  ],
	[ "itemCounts[20]"      , "uint8" , 0x30  ],
	[ "unlock[14]"        , "bool"  , 0x46  ],
	[ "weapons[8]"        , "uint8" , 0x84  ],
	[ "rangedWeaponLevels[5]", "uint32" , 0xA0  ],
	[ "meleeWeaponIndex", "uint32" , 0xC8  ],
	[ "rangedWeaponIndex", "uint32" , 0xCC  ],
	[ "costume"           , "uint8" , 0xD0  ],
	[ "unlockDevilTrigger", "bool"  , 0xD1  ],
	[ "hitPoints"         , "float" , 0xD4  ],
	[ "magicPoints"       , "float" , 0xD8  ],
	[ "style"             , "uint32", 0xDC  ],
	[ "styleLevel[6]"     , "uint32", 0xE0  ],
	[ "styleExperience[6]", "float" , 0xF8  ],
	[ "expertise[8]"      , "byte32", 0x110 ],
];

var filename = "../Mary/Vars.h"

var file = fs.readFileSync(filename, "utf8");

var lines = file.match(/[\S\s]*?\r\n/g);

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

CreateStruct
(
	"SessionData",
	0,
	items
);

Tag_CopyAfter(lines);

fs.writeFileSync(filename, c);
