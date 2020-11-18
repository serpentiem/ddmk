var fs = require("fs");

eval(fs.readFileSync("dmc3_core.js", "utf8"));

var items =
[
	[ "targetBaseAddr", "byte8 *", 0xB0 ],
	[ "height"        , "float"  , 0xD0 ],
	[ "tilt"          , "float"  , 0xD4 ],
	[ "zoom"          , "float"  , 0xD8 ],
	[ "zoomLockOn"    , "float"  , 0xE0 ],
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
	0,
	items
);

Tag_CopyAfter(lines);

fs.writeFileSync(filename, c);
