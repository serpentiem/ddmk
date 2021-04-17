

// @Todo: Merge.



var fs = require("fs");

eval(fs.readFileSync("dmc3_core.js", "utf8"));

var items =
[
	// [ "fovMultiplier"  , "float"  , 0x20 ],
	// [ "rotation"       , "float"  , 0x70 ],
	[ "targetBaseAddr" , "byte8 *", 0xB0 ],
	[ "height"         , "float"  , 0xD0 ],
	[ "tilt"           , "float"  , 0xD4 ],
	[ "distance"       , "float"  , 0xD8 ],
	[ "distanceLockOn" , "float"  , 0xE0 ],
];

var filename = "../Mary/Vars.h"

var file = fs.readFileSync(filename, "utf8");

var lines = file.match(/[\S\s]*?\r\n/g);

if
(
	!Tag_Init
	(
		lines,
		/\/\/ \$CameraDataStart$/,
		/\/\/ \$CameraDataEnd$/
	)
)
{
	console.log("Tag_Init failed.");

	return;
}

Tag_CopyUntil(lines);

CreateStruct
(
	"CameraData",
	512,
	items
);

Tag_CopyAfter(lines);

fs.writeFileSync(filename, c);
