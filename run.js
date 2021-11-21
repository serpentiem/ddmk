"use strict";

let child_process = require("child_process");
let fs            = require("fs");



function GetPath(location)
{
	if (location.length < 1)
	{
		return "";
	}

	let pos = location.lastIndexOf("/");

	if (pos < 1)
	{
		return "";
	}

	return location.substring(0, pos);
}

function GetFileName(location)
{
	if (location.length < 1)
	{
		return "";
	}

	let pos = (location.lastIndexOf("/") + 1);

	if (pos >= location.length)
	{
		return "";
	}

	return location.substring(pos, location.length);
}



let args     = process.argv;
let argCount = args.length;

if (argCount < 3)
{
	console.log("Too few args. " + argCount);

	console.log(args);

	return;
}



let location = args[2].replace(/\\/g, "/");

if (location.length < 1)
{
	console.log("Invalid Location");

	return;
}



let currentPath = process.cwd().replace(/\\/g, "/");



let path     = GetPath(location);
let fileName = GetFileName(location);

// console.log("path     $" + path     + "$");
// console.log("fileName $" + fileName + "$");

let match = path.match(/^[A-Z]:/);

if (!match)
{
	// At this point we have no drive letter in the beginning.

	if (path != "")
	{
		path = (currentPath + "/" + path);
	}
	else
	{
		path = currentPath;
	}
}

// console.log("path     $" + path     + "$");
// console.log("fileName $" + fileName + "$");

if
(
	(fileName.length < 3) ||
	(fileName.substring((fileName.length - 3), fileName.length) != ".js")
)
{
	fileName = fileName + ".js";
}

let prepFileName = "prep_" + fileName;



let newLocation     = (path + "/" + fileName    );
let newPrepLocation = (path + "/" + prepFileName);

console.log("path         $" + path         + "$");
console.log("fileName     $" + fileName     + "$");
console.log("prepFileName $" + prepFileName + "$");

console.log("newLocation     $" + newLocation     + "$");
console.log("newPrepLocation $" + newPrepLocation + "$");



let core = fs.readFileSync("core.js", "utf8");
let file = fs.readFileSync(newLocation, "utf8");

fs.writeFileSync(newPrepLocation, (core + file));



let newArgs =
[
	newPrepLocation,
];

for (let index = 3; index < argCount; index++)
{
	let arg = args[index];

	newArgs.push(arg);
}

console.log(newArgs.length);
console.log(newArgs);

child_process.execFileSync
(
	"node.exe",
	newArgs,
	{
		stdio: "inherit",
		encoding: "utf8"
	}
);
