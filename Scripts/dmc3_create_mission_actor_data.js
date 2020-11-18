var fs = require("fs");

eval(fs.readFileSync("dmc3_core.js", "utf8"));

var queuedItems =
[
	[ "weapons[5]"        , "uint8" , 0    ],
	[ "hitPoints"         , "float" , 0x50 ],
	[ "magicPoints"       , "float" , 0x54 ],
	[ "style"             , "uint32", 0x58 ],
	[ "styleLevel[6]"     , "uint32", 0x5C ],
	[ "styleExperience[6]", "float" , 0x74 ],
	[ "expertise[8]"      , "byte32", 0x8C ],
];

var activeItems =
[
	[ "weapons[5]"     , "uint8" , 0    ],
	[ "style"          , "uint32", 0x38 ],
	[ "styleLevel"     , "uint32", 0x3C ],
	[ "expertise[8]"   , "byte32", 0x40 ],
	[ "styleExperience", "float" , 0x60 ],
	[ "hitPoints"      , "float" , 0x64 ],
	[ "maxHitPoints"   , "float" , 0x68 ],
	[ "magicPoints"    , "float" , 0x6C ],
	[ "maxMagicPoints" , "float" , 0x70 ],
];

var filename = "../Mary/Vars.h"

var file = fs.readFileSync(filename, "utf8");

var lines = file.match(/[\S\s]*?\r\n/g);

if
(
	!Tag_Init
	(
		lines,
		/\/\/ \$MissionActorDataStart$/,
		/\/\/ \$MissionActorDataEnd$/
	)
)
{
	console.log("Tag_Init failed.");

	return;
}

Tag_CopyUntil(lines);

CreateStruct
(
	"QueuedMissionActorData",
	0,
	queuedItems
);

CreateStruct
(
	"ActiveMissionActorData",
	0,
	activeItems
);

Tag_CopyAfter(lines);

fs.writeFileSync(filename, c);
