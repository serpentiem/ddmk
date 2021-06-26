let fs = require("fs");
let vm = require("vm");

vm.runInThisContext(fs.readFileSync("core.js", "utf8"));

ClearAll();

CheatTableStart();

GroupStart("__CAMERA__");

for (let index = 0; index < 128; index++)
{
	CreateCheatEntry
	(
		"No description",
		false,
		"Float",
		"dmc3.exe+C90E10",
		[
			PositionName
			(
				(index * 4),
				PositionFlags_Hex |
				PositionFlags_NoPrefix
			),
			"2CD0+498",
			"40",
		]
	);
}

GroupEnd();

CheatTableEnd();

fs.writeFileSync("camera.txt", c);
