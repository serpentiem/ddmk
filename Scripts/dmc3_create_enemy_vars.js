let fs = require("fs");
let vm = require("vm");

vm.runInThisContext(fs.readFileSync("dmc3_core.js", "utf8"));

ClearAll();

// @Todo: Move to core.
function ReplaceAll
(
	name,
	pattern,
	replace
)
{
	let newPattern = new RegExp(pattern);

	let count = 0;

	while (true)
	{
		let match = name.match(newPattern);
		if (!match)
		{
			break;
		}

		name = name.replace(newPattern, replace);

		count++;
	}

	// console.log("count " + count);

	return name;
}




let items =
[
	[ "Pride 1"               , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Pride 2"               , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Pride 3"               , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Pride 4"               , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Gluttony 1"            , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Gluttony 2"            , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Gluttony 3"            , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Gluttony 4"            , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Lust 1"                , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Lust 2"                , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Lust 3"                , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Lust 4"                , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Sloth 1"               , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Sloth 2"               , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Sloth 3"               , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Sloth 4"               , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Wrath 1"               , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Wrath 2"               , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Wrath 3"               , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Wrath 4"               , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Greed 1"               , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Greed 2"               , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Greed 3"               , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Greed 4"               , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Abyss"                 , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Envy"                  , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Hell Vanguard"         , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Unknown"               , "0"                           ],
	[ "Arachne"               , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "The Fallen"            , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Dullahan"              , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Enigma"                , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Blood-Goyle"           , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Unknown"               , "0"                           ],
	[ "Soul Eater"            , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Damned Chessmen Pawn"  , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Damned Chessmen Knight", "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Damned Chessmen Bishop", "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Damned Chessmen Rook"  , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Damned Chessmen Queen" , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Damned Chessmen King"  , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Gigapede"              , "HELPER_ENEMY_GIGAPEDE"       ],
	[ "Unknown"               , "0"                           ],
	[ "Cerberus"              , "HELPER_ENEMY_CERBERUS"       ],
	[ "Agni & Rudra All"      , "HELPER_ENEMY_AGNI_RUDRA"     ],
	[ "Agni & Rudra"          , "HELPER_ENEMY_AGNI_RUDRA"     ],
	[ "Agni & Rudra Black"    , "HELPER_ENEMY_AGNI_RUDRA"     ],
	[ "Agni & Rudra Red"      , "HELPER_ENEMY_AGNI_RUDRA"     ],
	[ "Agni & Rudra Blue"     , "HELPER_ENEMY_AGNI_RUDRA"     ],
	[ "Nevan"                 , "HELPER_ENEMY_NEVAN"          ],
	[ "Geryon"                , "HELPER_ENEMY_GERYON"         ],
	[ "Beowulf"               , "HELPER_ENEMY_BEOWULF"        ],
	[ "Doppelganger"          , "HELPER_ENEMY_DOPPELGANGER"   ],
	[ "Arkham"                , "HELPER_ENEMY_ARKHAM"         ],
	[ "Unknown"               , "0"                           ],
	[ "Lady"                  , "HELPER_ENEMY_LADY"           ],
	[ "Unknown"               , "0"                           ],
	[ "Unknown"               , "0"                           ],
	[ "Vergil"                , "HELPER_ENEMY_VERGIL"         ],
	[ "Unknown"               , "0"                           ],
	[ "Leviathan Heart"       , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Leviathan Other"       , "HELPER_ENEMY_LESSER_ENEMIES" ],
	[ "Jester"                , "HELPER_ENEMY_JESTER"         ],
	[ "Unknown"               , "0"                           ],
];



// Enum

c += "export enum" + NEW_LINE;

ScopeStart();

let unknownIndex = 0;

for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
{
	let item = items[itemIndex];

	let name = item[0];
	let helperIndex = item[1];

	let enumName = name;

	if (enumName == "Unknown")
	{
		enumName = enumName + "_" + unknownIndex;

		unknownIndex++;
	}

	enumName = ReplaceAll(enumName, "-", " ");

	enumName = ReplaceAll(enumName, "&", "");

	enumName = ReplaceAll(enumName, "  ", " ");

	enumName = ReplaceAll(enumName, " ", "_");

	enumName = "ENEMY_" + enumName.toUpperCase();

	c += Tabs() + enumName + "," + NEW_LINE;
}

c += Tabs() + "ENEMY_COUNT," + NEW_LINE;
c += Tabs() + "CREATE_ENEMY_COUNT = 30," + NEW_LINE;

ScopeEnd
(
	"}",
	ScopeFlags_Semicolon
);

c += NEW_LINE;



// Names

c += "export const char * enemyNames[] =" + NEW_LINE;

ScopeStart();

for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
{
	let item = items[itemIndex];

	let name = item[0];
	let helperIndex = item[1];

	c += Tabs() + "\"" + name + "\"," + NEW_LINE;
}

ScopeEnd
(
	"}",
	ScopeFlags_Semicolon
);

c += NEW_LINE;



// Helper Indices

c += "export constexpr uint8 enemyHelperIndices[] =" + NEW_LINE;

ScopeStart();

for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
{
	let item = items[itemIndex];

	let name = item[0];
	let helperIndex = item[1];

	c += Tabs() + helperIndex + "," + NEW_LINE;
}

ScopeEnd
(
	"}",
	ScopeFlags_Semicolon
);

c += NEW_LINE;



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
		/\/\/ \$EnemyStart$/,
		/\/\/ \$EnemyEnd$/
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
