var fs = require("fs");

eval(fs.readFileSync("dmc3_core.js", "utf8"));

var items =
[
	[ "rank"    , "uint32", 0     ],
	[ "meter"   , "float" , 4     ],
	[ "quotient", "float" , 0x150 ],
	[ "dividend", "float" , 0x154 ],
	[ "divisor" , "float" , 0x158 ],
];

var filename = "../Mary/Vars.h"

var file = fs.readFileSync(filename, "utf8");

var lines = file.match(/[\S\s]*?\r\n/g);

if
(
	!Tag_Init
	(
		lines,
		/\/\/ \$StyleDataStart$/,
		/\/\/ \$StyleDataEnd$/
	)
)
{
	console.log("Tag_Init failed.");

	return;
}

Tag_CopyUntil(lines);

CreateStruct
(
	"StyleData",
	352,
	items
);

Tag_CopyAfter(lines);

fs.writeFileSync(filename, c);
