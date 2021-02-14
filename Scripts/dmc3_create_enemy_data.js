var fs = require("fs");

eval(fs.readFileSync("dmc3_core.js", "utf8"));

var items =
[
	[ "lastBaseAddr", "byte8 *", 0x28 ],
	[ "nextBaseAddr", "byte8 *", 0x30 ],
	[ "baseAddr"    , "byte8 *", 0x48 ],
	[ "enemy"       , "uint32" , 0x78 ],
	[ "position"    , "vec4"   , 0x80 ],
];

var filename = "../Mary/Vars.h"

var file = fs.readFileSync(filename, "utf8");

var lines = file.match(/[\S\s]*?\r\n/g);

if
(
	!Tag_Init
	(
		lines,
		/\/\/ \$EnemyDataStart$/,
		/\/\/ \$EnemyDataEnd$/
	)
)
{
	console.log("Tag_Init failed.");

	return;
}

Tag_CopyUntil(lines);

CreateStruct
(
	"EnemyData",
	0,
	items
);

Tag_CopyAfter(lines);

fs.writeFileSync(filename, c);
