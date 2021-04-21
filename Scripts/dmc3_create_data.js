let fs = require("fs");
let vm = require("vm");

vm.runInThisContext(fs.readFileSync("dmc3_core.js", "utf8"));

ClearAll();



// #region Mission data
{

var items =
[
	[ "orbs"         , "uint32", [], 0x38 ],
	[ "itemCount[62]", "uint8" , [], 0x3C ],
	[ "buyCount[8]"  , "uint8" , [], 0x7A ],
	[ "frameCount"   , "uint32", [], 0xA8 ],
	[ "damage"       , "uint32", [], 0xAC ],
	[ "orbsCollected", "uint32", [], 0xB0 ],
	[ "itemsUsed"    , "uint32", [], 0xB4 ],
	[ "killCount"    , "uint32", [], 0xB8 ],
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















