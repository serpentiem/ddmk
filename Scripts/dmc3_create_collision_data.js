
// @Todo: Merge.


var fs = require("fs");

eval(fs.readFileSync("dmc3_core.js", "utf8"));

var items =
[
	[ "index", "uint32", 4     ],
	[ "data" , "vec4"  , 0x210 ],
];

var filename = "../Mary/Vars.h"

var file = fs.readFileSync(filename, "utf8");

var lines = file.match(/[\S\s]*?\r\n/g);

if
(
	!Tag_Init
	(
		lines,
		/\/\/ \$CollisionDataStart$/,
		/\/\/ \$CollisionDataEnd$/
	)
)
{
	console.log("Tag_Init failed.");

	return;
}

Tag_CopyUntil(lines);

CreateStruct
(
	"CollisionData",
	656,
	items
);

Tag_CopyAfter(lines);

fs.writeFileSync(filename, c);
