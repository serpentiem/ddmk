let fs = require("fs");
let process = require("process");
let vm = require("vm");

let code = "";

code += fs.readFileSync("core.js", "utf8");
code += fs.readFileSync("prep.js", "utf8");
code += fs.readFileSync("prepMaryFunctions.js", "utf8");

vm.runInThisContext(code);

ClearAll();



let filename = "";
let newFilename = "";

{
	let argv = process.argv;
	let argc = argv.length;

	// @Todo: Update.
	if (argc < 4)
	{
		console.log("No Filenames");

		return;
	}

	filename    = argv[2];
	newFilename = argv[3];
}

let file = fs.readFileSync(filename, "utf8");

buffer = file;
bufferSize = file.length;

if (Prep())
{
	process.exit(1);

	return;
}

fs.writeFileSync(newFilename, c);
