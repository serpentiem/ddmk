let fs = require("fs");
let vm = require("vm");

vm.runInThisContext(fs.readFileSync("core.js", "utf8"));

ClearAll();



CheatTableStart();

GroupStart("__SPEEDS__");

for (let index = 0; index < 8; index++)
{
	CreateCheatEntry
	(
		lz(index),
		false,
		"Float",
		"dmc3.exe+CF2D90+" + (4 * index).toString(16).toUpperCase()
	);
}

for (let index = 0; index < 8; index++)
{
	CreateCheatEntry
	(
		lz(index),
		false,
		"Float",
		"dmc3.exe+CF2D90+98+" + (8 * index).toString(16).toUpperCase()
	);
}

GroupEnd();

CheatTableEnd();

fs.writeFileSync("speeds.txt", c);
