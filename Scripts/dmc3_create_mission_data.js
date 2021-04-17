// @Todo: Merge.


var fs = require("fs");

eval(fs.readFileSync("dmc3_core.js", "utf8"));

var items =
[
	[ "orbs"         , "uint32", 0x38 ],
	[ "frameCount"   , "uint32", 0xA8 ],
	[ "damage"       , "uint32", 0xAC ],
	[ "orbsCollected", "uint32", 0xB0 ],
	[ "itemsUsed"    , "uint32", 0xB4 ],
	[ "killCount"    , "uint32", 0xB8 ],
];

var filename = "../Mary/Vars.h"

var file = fs.readFileSync(filename, "utf8");

var lines = file.match(/[\S\s]*?\r\n/g);

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

CreateStruct
(
	"MissionData",
	192,
	items
);

Tag_CopyAfter(lines);

fs.writeFileSync(filename, c);
