// #region

ClearAll();

let dmc1_typeSizes =
[
	[ "ItemData", 4 ],
];

typeSizes_Reset();
typeSizes_Add(dmc1_typeSizes);

let location = "Eva/Vars.ixx";

file = fs.readFileSync(location, "utf8");

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

FeedStruct
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

FeedStruct
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

FeedStruct
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

FeedStruct
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

FeedStruct
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



fs.writeFileSync(location, file);
