let fs = require("fs");
let vm = require("vm");

vm.runInThisContext(fs.readFileSync("dmc3_core.js", "utf8"));

ClearAll();

CheatTableStart();

GroupStart("__SPEEDS__");

for (let index = 0; index < 32; index++)
{
	CreateCheatEntry
	(
		"No description",
		false,
		"Float",
		"dmc3.exe+CF2D90+" + (4 * index).toString(16).toUpperCase()
	);
}

GroupEnd();

CheatTableEnd();

fs.writeFileSync("speeds.txt", c);
