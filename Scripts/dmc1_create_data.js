// #region Core



let fs = require("fs");
let process = require("process");
let vm = require("vm");

vm.runInThisContext(fs.readFileSync("core.js", "utf8"));

ClearAll();



const Flags_NoSave  = 1 << 0;
const Flags_NoClear = 1 << 1;



function SaveStream(name)
{
	let c_new = c;

	c = "";

	let filename = "../Eva/Vars.ixx";

	let file = fs.readFileSync(filename, "utf8");

	let lines = GetLines(file);



	let startName = new RegExp("\\/\\/ \\$" + name + "Start$");
	let endName   = new RegExp("\\/\\/ \\$" + name + "End$"  );

	console.log(startName);
	console.log(endName);

	if
	(
		!Tag_Init
		(
			lines,
			startName,
			endName
		)
	)
	{
		console.log("Tag_Init failed.");

		process.exit(1);

		return;
	}

	Tag_CopyUntil(lines);

	c += c_new;

	Tag_CopyAfter(lines);

	fs.writeFileSync(filename, c);



	ClearAll();
}

function FeedTuple
(
	name,
	items,
	size = 0,
	tagName = name,
	flags = 0
)
{
	CreateTuple
	(
		name,
		items,
		size,
		0,
		TupleFlags_Export
	);



	ClearAsserts();

	CreateTupleAsserts
	(
		name,
		items,
		size,
		0,
		TupleFlags_NoTypeAssert
	);

	MergeAsserts();
	FeedAsserts();

	CleanStream();

	if (!(flags & Flags_NoSave))
	{
		SaveStream(tagName);
	}
}

function FeedEnum
(
	name,
	items,
	tagName = name,
	flags = 0
)
{
	c += "export namespaceStart(" + name + ");" + NEW_LINE;
	c += "enum" + NEW_LINE;

	ScopeStart();

	let unknownIndex = 0;

	for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
	{
		let item = items[itemIndex];

		let name = item[0];
		let value = item[1];

		if
		(
			(name == "") ||
			name.match(/unknown/i)
		)
		{
			name = "UNKNOWN_" + unknownIndex;

			unknownIndex++;
		}

		name = ReplaceAll(name, "-", " ");

		name = ReplaceAll(name, "&", "");

		name = ReplaceAll(name, "  ", " ");

		name = ReplaceAll(name, " ", "_");

		name = ReplaceAll(name, "'", "");

		name = name.toUpperCase();

		c += Tabs() + name;

		if (value != "")
		{
			c += " = " + value;
		}

		c += "," + NEW_LINE;
	}

	ScopeEnd
	(
		"}",
		ScopeFlags_Semicolon
	);

	c += "namespaceEnd();" + NEW_LINE;
	c += NEW_LINE;


	if (!(flags & Flags_NoSave))
	{
		SaveStream(tagName);
	}
}

// #endregion



// #region SessionData
{

let items =
[
	[ "buttons[4]" , "byte16"  , [], 0      ],
	[ "rightStickX", "uint8"   , [], 0x36   ],
	[ "rightStickY", "uint8"   , [], 0x37   ],
	[ "leftStickX" , "uint8"   , [], 0x38   ],
	[ "leftStickY" , "uint8"   , [], 0x39   ],
	[ "[5]"        , "byte32"  , [], 0x90   ],
	[ "event"      , "byte32"  , [], 0x1CA4 ],
	[ "mission"    , "uint8"   , [], 0x1E64 ],
	[ "mode"       , "uint8"   , [], 0x1E66 ],
	[ "character"  , "uint8"   , [], 0x1E67 ],
	[ ""           , "byte32"  , [], 0x1F88 ],
	[ ""           , "byte32"  , [], 0x1F94 ],
	[ ""           , "bool"    , [], 0x1F98 ],
	[ ""           , "byte32"  , [], 0x1F9C ],
	[ ""           , "byte32"  , [], 0x1FD4 ],
	[ "state"  , "byte32"      , [], 0x2040 ],
	[ "itemCount"  , "uint8"   , [], 0x207B ],
	[ "items[1]"   , "ItemData", [], 0x2090 ],
	[ "hitPoints"  , "uint8"   , [], 0x2464 ],
	[ "magicPoints", "uint8"   , [], 0x2465 ],
	[ "expertise"  , "byte32"  , [], 0x2468 ],
	[ "redOrbs"    , "uint32"  , [], 0x2474 ],
	[ "orbFlags"   , "byte32"  , [], 0x247C ],
];

FeedTuple
(
	"SessionData",
	items
);

}
// #endregion



// #region EventData
{

let items =
[
	[ "track"    , "uint32", [], 0x270 ],
	[ "room"     , "uint32", [], 0x274 ],
	[ "nextTrack", "uint32", [], 0x288 ],
	[ "nextRoom" , "uint32", [], 0x28C ],
];

FeedTuple
(
	"EventData",
	items
);

}
// #endregion



// #region PlayerActorData
{

let items =
[
	[ "state[8]"           , "byte8" , [], 0      ],
	[ "rotation"           , "float" , [], 0x124  ],
	[ "position"           , "vec4"  , [], 0x170  ],
	[ "hitPoints"          , "uint16", [], 0x17A2 ],
	[ "idleTimer"          , "uint16", [], 0x1A10 ],
	[ "maxHitPoints"       , "uint16", [], 0x1BC8 ],
	[ "meleeWeapon"        , "uint8" , [], 0x1BCC ],
	[ "magicPointsHuman"   , "uint16", [], 0x1BCE ],
	[ "maxMagicPointsHuman", "uint16", [], 0x1BD0 ],
	[ "magicPointsDevil"   , "uint16", [], 0x1BD2 ],
	[ "maxMagicPointsDevil", "uint16", [], 0x1BD4 ],
	[ "rangedWeapon"       , "uint8" , [], 0x1C48 ],
	[ "meleeWeaponForm"    , "uint8" , [], 0x1C4C ],
	[ "chargeTimers[2]"    , "int16" , [], 0x1C66 ],
];

FeedTuple
(
	"PlayerActorData",
	items
);

}
// #endregion




// #region WeaponData
{

let items =
[
	[ "updateRangedWeapon", "bool", [], 0xA9E9 ],
	[ "updateMeleeWeapon" , "bool", [], 0xACA1 ],
];

FeedTuple
(
	"WeaponData",
	items
);

}
// #endregion


















// #region Event
{

let items =
[
	[ "in-game", "0x2000" ],
	[ "teleport", "0x10000000" ],
];

FeedEnum
(
	"EVENT",
	items,
	"Event"
);

}
// #endregion




// #region Mode
{

let items =
[
	[ "easy"          , "2" ],
	[ "normal"        , "3" ],
	[ "hard"          , "5" ],
	[ "dante must die", "6" ],
];

FeedEnum
(
	"MODE",
	items,
	"Mode"
);

}
// #endregion



// #region Character
{

let items =
[
	[ "dante", "" ],
	[ "ldk", "" ],
	[ "super dante", "" ],
];

FeedEnum
(
	"CHARACTER",
	items,
	"Character"
);

}
// #endregion



// #region Weapon
{

let items =
[
	[ "alastor", "" ],
	[ "ifrit", "" ],
	[ "sparda air", "" ],
	[ "sparda", "" ],
	[ "force edge", "" ],
	[ "handgun", "1" ],
	[ "shotgun", "" ],
	[ "grenadegun", "" ],
	[ "nightmare beta", "" ],
	[ "melee weapon count", "5" ],
	[ "ranged weapon count", "4" ],
];

FeedEnum
(
	"WEAPON",
	items,
	"Weapon"
);

}
// #endregion


// #region MeleeWeaponForm
{

let items =
[
	[ "default", "" ],
	[ "sparda", "" ],
	[ "yamato", "" ],
];

FeedEnum
(
	"MELEE_WEAPON_FORM",
	items,
	"MeleeWeaponForm"
);

}
// #endregion





// #region Item0
{

let items =
[
	[ "handgun"       , "" ],
	[ "shotgun"       , "" ],
	[ "needlegun"     , "" ],
	[ "grenadegun"    , "" ],
	[ "nightmare beta", "" ],
	[ "force edge"    , "" ],
	[ "alastor"       , "" ],
	[ "ifrit"         , "" ],
	[ "sparda"        , "" ],
	[ "yamato"        , "" ],
];

FeedEnum
(
	"ITEM_0",
	items,
	"Item0"
);

}
// #endregion







// #region Item1
{

let items =
[
	[ "bangle of time", "" ],
	[ "luminite", "" ],
	[ "unknown", "" ],
	[ "unknown", "" ],
	[ "yellow orb", "" ],
	[ "unknown", "" ],
	[ "blue orb bottom right", "" ],
	[ "blue orb top right", "" ],
	[ "blue orb bottom left", "" ],
	[ "blue orb top left", "" ],
	[ "unknown", "" ],
	[ "unknown", "" ],
	[ "vital star", "" ],
	[ "devil star", "" ],
	[ "untouchable", "" ],
	[ "holy water", "" ],
	[ "rusty key", "" ],
	[ "staff of hermes", "" ],
	[ "amulet", "" ],
	[ "emblem shield", "" ],
];

FeedEnum
(
	"ITEM_1",
	items,
	"Item1"
);

}
// #endregion





// #region Item2
{

let items =
[
	[ "unknown", "" ],
	[ "unknown", "" ],
	[ "yellow orb", "" ],
	[ "unknown", "" ],
	[ "blue orb bottom right", "" ],
	[ "blue orb top right", "" ],
	[ "blue orb bottom left", "" ],
	[ "blue orb top left", "" ],
	[ "unknown", "" ],
	[ "unknown", "" ],
	[ "vital star", "" ],
	[ "devil star", "" ],
	[ "untouchable", "" ],
	[ "holy water", "" ],
	[ "rusty key", "" ],
	[ "staff of hermes", "" ],
	[ "amulet", "" ],
	[ "emblem shield", "" ],
];

FeedEnum
(
	"ITEM_2",
	items,
	"Item2"
);

}
// #endregion




// // #region Item3
// {

// let items =
// [
// 	[ "", "" ],
// ];

// FeedEnum
// (
// 	"ITEM_3",
// 	items,
// 	"Item3"
// );

// }
// // #endregion

















// #region Item4
{

let items =
[
	[ "staff of judgement", "" ],
	[ "death sentence"    , "" ],
	[ "death sentence 2"  , "" ],
	[ "melancholy soul"   , "" ],
	[ "trident"           , "" ],
	[ "guiding light"     , "" ],
	[ "pride of lion"     , "" ],
];

FeedEnum
(
	"ITEM_4",
	items,
	"Item4"
);

}
// #endregion



// #region Item5
{

let items =
[
	[ "emblem shield", "" ],
	[ "knight's portrait", "" ],
	[ "sign of chastity", "" ],
	[ "sign of humbleness", "" ],
	[ "sign of perseverance", "" ],
	[ "chalice", "" ],
	[ "pair of lances", "" ],
	[ "wheel of destiny", "" ],
];

FeedEnum
(
	"ITEM_5",
	items,
	"Item5"
);

}
// #endregion



// #region Item6
{

let items =
[
	[ "token of philosophy", "" ],
	[ "philosopher's egg", "" ],
	[ "elixir", "" ],
	[ "quicksilver", "" ],
	[ "philosopher's stone", "" ],
	[ "unknown", "" ],
	[ "perfect amulet", "" ],
];

FeedEnum
(
	"ITEM_6",
	items,
	"Item6"
);

}
// #endregion



/*
mission 1

vital star
2
10
1

amulet
2
16
1

mission 2

vital star
2
10
1

amulet
2
16
1

mission 3

vital star
2
10
1

amulet
2
16
1



mission 4

vital star
2
10
1

amulet
2
16
1

pride of lion
4
6
1






mission 5

vital star
2
10
1

amulet
2
16
1

melancholy soul
4
3
1




mission 6

vital star
2
10
1

amulet
2
16
1



mission 7

vital star
2
10
1

amulet
2
16
1

guiding light
4
5
1





mission 8

vital star
2
10
1

amulet
2
16
1



mission 9

vital star
2
10
1

amulet
2
16
1




mission 10

vital star
2
10
1

amulet
2
16
1



mission 11

vital star
2
10
1

amulet
2
16
1


mission 12

vital star
2
10
1

amulet
2
16
1






mission 13

vital star
2
10
1

amulet
2
16
1





mission 14

vital star
2
10
1

amulet
2
16
1




mission 15

vital star
2
10
1

amulet
2
16
1


emblem shield
2
17
1




mission 16

vital star
2
10
1

staff of hermes
2
15
1

amulet
2
16
1

wheel of destiny
5
7
1





mission 17

vital star
2
10
1

amulet
2
16
1





mission 18

vital star
2
10
1

amulet
2
16
1






mission 19

vital star
2
10
1

perfect amulet
6
6
1

elixir
6
2
1



mission 20

vital star
2
10
1

perfect amulet
6
6
1



mission 21

vital star
2
10
1

perfect amulet
6
6
1



mission 22

vital star
2
10
1

perfect amulet
6
6
1


mission 23

vital star
2
10
1

perfect amulet
6
6
1


mission 24

vital star
2
10
1

perfect amulet
6
6
1














































































































*/













// #region ScreenEffectData
{

let items =
[
	[ "r"     , "uint8" , [], 8    ],
	[ "g"     , "uint8" , [], 9    ],
	[ "b"     , "uint8" , [], 0xA  ],
	[ "a"     , "uint8" , [], 0xB  ],
	[ "timer" , "uint16", [], 0x62 ],
	[ "status", "uint8" , [], 0x64 ],
];

FeedTuple
(
	"ScreenEffectData",
	items,
	104
);

/*
dmc1.exe+26261F - 48 83 C3 68 - add rbx,68
dmc1.exe+262623 - 48 3B DD    - cmp rbx,rbp
*/

}
// #endregion














