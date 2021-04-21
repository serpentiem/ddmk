let fs = require("fs");
let vm = require("vm");

vm.runInThisContext(fs.readFileSync("dmc3_core.js", "utf8"));

ClearAll();

// Default
{

let names =
[
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Gold Orb",
	"Yellow Orb",
	"Blue Orb",
	"Purple Orb",
	"Blue Orb Fragment",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Vital Star Large",
	"Vital Star Small",
	"Devil Star",
	"Holy Water",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Astronomical Board",
	"Vajura",
	"Unknown",
	"Soul of Steel",
	"Essence of Fighting",
	"Essence of Technique",
	"Essence of Intelligence",
	"Orihalcon Fragment",
	"Siren's Shriek",
	"Crystal Skull",
	"Ignis Fatuus",
	"Ambrosia",
	"Stone Mask",
	"Neo-Generator",
	"Haywire Neo-Generator",
	"Orihalcon",
	"Orihalcon Fragment Right",
	"Orihalcon Fragment Bottom",
	"Orihalcon Fragment Left",
	"Golden Sun",
	"Onyx Moonshard",
	"Samsara",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
];










c += "export const char * itemNames[] =" + NEW_LINE;

ScopeStart();

for (let nameIndex = 0; nameIndex < names.length; nameIndex++)
{
	let name = names[nameIndex];

	c += Tabs() + "\"" + name + "\"," + NEW_LINE;
}

ScopeEnd
(
	"}",
	ScopeFlags_Semicolon
);

c += NEW_LINE;









c += "export enum" + NEW_LINE;

ScopeStart();

let unknownIndex = 0;

for (let nameIndex = 0; nameIndex < names.length; nameIndex++)
{
	let name = names[nameIndex];

	let enumName = name;

	if (enumName == "Unknown")
	{
		enumName = enumName + "_" + unknownIndex;

		unknownIndex++;
	}

	enumName = ReplaceAll(enumName, "-", " ");

	enumName = ReplaceAll(enumName, "&", "");

	enumName = ReplaceAll(enumName, "'", "");

	enumName = ReplaceAll(enumName, "  ", " ");

	enumName = ReplaceAll(enumName, " ", "_");

	enumName = "ITEM_" + enumName.toUpperCase();

	c += Tabs() + enumName + "," + NEW_LINE;
}

c += Tabs() + "ITEM_COUNT," + NEW_LINE;

ScopeEnd
(
	"}",
	ScopeFlags_Semicolon
);

c += NEW_LINE;

}



// Buy
{

let names =
[
	"Vital Star Small",
	"Vital Star Large",
	"Devil Star",
	"Holy Water",
	"Blue Orb",
	"Purple Orb",
	"Gold Orb",
	"Yellow Orb",
];



c += "export const char * buyNames[] =" + NEW_LINE;

ScopeStart();

for (let nameIndex = 0; nameIndex < names.length; nameIndex++)
{
	let name = names[nameIndex];

	c += Tabs() + "\"" + name + "\"," + NEW_LINE;
}

ScopeEnd
(
	"}",
	ScopeFlags_Semicolon
);

c += NEW_LINE;

















c += "export enum" + NEW_LINE;

ScopeStart();

let unknownIndex = 0;

for (let nameIndex = 0; nameIndex < names.length; nameIndex++)
{
	let name = names[nameIndex];

	let enumName = name;

	if (enumName == "Unknown")
	{
		enumName = enumName + "_" + unknownIndex;

		unknownIndex++;
	}

	enumName = ReplaceAll(enumName, "-", " ");

	enumName = ReplaceAll(enumName, "&", "");

	enumName = ReplaceAll(enumName, "'", "");

	enumName = ReplaceAll(enumName, "  ", " ");

	enumName = ReplaceAll(enumName, " ", "_");

	enumName = "BUY_" + enumName.toUpperCase();

	c += Tabs() + enumName + "," + NEW_LINE;
}

c += Tabs() + "BUY_COUNT," + NEW_LINE;

ScopeEnd
(
	"}",
	ScopeFlags_Semicolon
);

c += NEW_LINE;

}













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
		/\/\/ \$ItemStart$/,
		/\/\/ \$ItemEnd$/
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




















