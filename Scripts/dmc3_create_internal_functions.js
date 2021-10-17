// #region

"use strict";

let fs = require("fs");
let process = require("process");
let vm = require("vm");

vm.runInThisContext
(
	fs.readFileSync("../core.js"  , "utf8") +
	fs.readFileSync("dmc3_core.js", "utf8")
);

ClearAll();

// #endregion



let location = "../Mary/Internal.ixx";

let file = fs.readFileSync(location, "utf8");



let tagName = "Data";



ClearAll();



let c_until = "";
let c_after = "";
let c_new   = "";

let lines = GetLines(file);

let startName = new RegExp("\\/\\/ \\$" + tagName + "Start$");
let endName   = new RegExp("\\/\\/ \\$" + tagName + "End$"  );

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

c_until = c;

ClearAll();



Tag_CopyAfter(lines);

c_after = c;

ClearAll();



let items =
[
	[ 0x897B0  , "void"        , "ModelData & modelData"                                                                                                                                                                                , ""                                          , ""                                    ],
	[ 0x89450  , "void"        , "ModelData & modelData"                                                                                                                                                                                , ""                                          , ""                                    ],
	[ 0x89270  , "void"        , "ModelData & modelData"                                                                                                                                                                                , ""                                          , ""                                    ],
	[ 0x8B470  , "void"        , "ModelData & modelData, bool32 enable"                                                                                                                                                                 , ""                                          , ""                                    ],
	[ 0x89960  , "void"        , "ModelData & modelData, byte8 * modelFile, byte8 * textureFile"                                                                                                                                        , ""                                          , ""                                    ],
	[ 0x1EF040 , "void"        , "byte8 * actorData, uint32 index"                                                                                                                                                                      , ""                                          , ""                                    ],
	[ 0x89DE0  , "byte8 *"     , "ModelData & modelData"                                                                                                                                                                                , "0, true, false"                            , ""                                    ],
	[ 0x8BC60  , "void"        , "ShadowData & shadowData, byte8 * dest, byte8 * file"                                                                                                                                                  , ""                                          , ""                                    ],
	[ 0x305D80 , "void"        , "byte8 * dest"                                                                                                                                                                                         , ""                                          , ""                                    ],
	[ 0x8A000  , "void"        , "ModelData & modelData, byte8 * motionFile, PhysicsMetadata ** modelPhysicsMetadataPool"                                                                                                               , ""                                          , ""                                    ],
	[ 0x2C9F40 , "uint32"      , "byte8 * physicsFile"                                                                                                                                                                                  , "0, true, false"                            , ""                                    ],
	[ 0x2CA1D0 , "void"        , "PhysicsData & physicsData, PhysicsMetadata ** physicsMetadata, byte8 * physicsFile, uint32 index"                                                                                                     , ""                                          , ""                                    ],
	[ 0x2CA2F0 , "void"        , "PhysicsData & physicsData, void * dest, byte8 * addr, ModelMetadata * modelMetadata, uint32 count"                                                                                                    , "0, true, true, 0, 0, 0, 0, 1"              , ""                                    ],
	[ 0x2C6150 , "void *"      , "void * dest, uint32 size, int32 mode"                                                                                                                                                                 , ""                                          , "Alloc"                               ],
	[ 0x1FD3E0 , "bool"        , "WeaponData & weaponData, uint8"                                                                                                                                                                       , ""                                          , "IsWeaponReady"                       ],
	[ 0x1FDE10 , "void"        , "WeaponData & weaponData"                                                                                                                                                                              , ""                                          , "Show Weapon"                         ],
	[ 0x8BF30  , "void"        , "uint32 index, void * dest, byte8 * baseAddr"                                                                                                                                                          , ""                                          , ""                                    ],
	[ 0x2EDFC0 , "void"        , "byte8 *"                                                                                                                                                                                              , ""                                          , ""                                    ],
	[ 0x337710 , "void"        , "byte8 *"                                                                                                                                                                                              , ""                                          , ""                                    ],
	[ 0x27AA90 , "bool"        , "void *, uint32, void *, float"                                                                                                                                                                        , ""                                          , ""                                    ],
	[ 0x1A4680 , "byte8 *"     , "byte8 *, const CreateEnemyActorData &"                                                                                                                                                                , "0, true, false"                            , "Create Enemy Actor"                  ],
	[ 0x3391C0 , "void"        , "void *, int32, int32, int32, int32"                                                                                                                                                                   , "0, true, true, 0, 0, 0, 0, 1"              , "Play Sound"                          ],
	[ 0x2EE3D0 , "void"        , "byte8 * dest"                                                                                                                                                                                         , ""                                          , ""                                    ],
	[ 0x1FAF40 , "void"        , "byte8 * baseAddr"                                                                                                                                                                                     , ""                                          , ""                                    ],
	[ 0x1EEF80 , "void"        , "byte8 * baseAddr"                                                                                                                                                                                     , ""                                          , ""                                    ],
	[ 0x2EE060 , "bool"        , "byte8 * dest, uint32 size"                                                                                                                                                                            , ""                                          , ""                                    ],
	[ 0x1DE820 , "byte8 *"     , "uint32 character, uint32 id, bool isClone"                                                                                                                                                            , "0, true, false"                            , "Create Actor"                        ],
	[ 0x217B90 , "void"        , "byte8 * actorData, ActiveMissionActorData & activeMissionActorData"                                                                                                                                   , ""                                          , "Init Actor Dante"                    ],
	[ 0x226F10 , "void"        , "byte8 * actorData, ActiveMissionActorData & activeMissionActorData"                                                                                                                                   , ""                                          , "Init Actor Bob"                      ],
	[ 0x219660 , "void"        , "byte8 * actorData, ActiveMissionActorData & activeMissionActorData"                                                                                                                                   , ""                                          , "Init Actor Lady"                     ],
	[ 0x223CB0 , "void"        , "byte8 * actorData, ActiveMissionActorData & activeMissionActorData"                                                                                                                                   , ""                                          , "Init Actor Vergil"                   ],
	[ 0x212BE0 , "void"        , "byte8 * actorData"                                                                                                                                                                                    , ""                                          , "Update Actor Dante"                  ],
	[ 0x225D70 , "void"        , "byte8 * actorData"                                                                                                                                                                                    , ""                                          , "Update Actor Bob"                    ],
	[ 0x219260 , "void"        , "byte8 * actorData"                                                                                                                                                                                    , ""                                          , "Update Actor Lady"                   ],
	[ 0x220970 , "void"        , "byte8 * actorData"                                                                                                                                                                                    , ""                                          , "Update Actor Vergil"                 ],
	[ 0x1DFC20 , "void"        , "byte8 * actorData"                                                                                                                                                                                    , ""                                          , ""                                    ],
	[ 0x2310B0 , "WeaponData *", "byte8 * actorData, uint32 id"                                                                                                                                                                         , "0, true, false"                            , "Dante Rebellion"                     ],
	[ 0x22EC90 , "WeaponData *", "byte8 * actorData, uint32 id"                                                                                                                                                                         , "0, true, false"                            , "Dante Cerberus"                      ],
	[ 0x227870 , "WeaponData *", "byte8 * actorData, uint32 id"                                                                                                                                                                         , "0, true, false"                            , "Dante Agni & Rudra"                  ],
	[ 0x22A1E0 , "WeaponData *", "byte8 * actorData, uint32 id"                                                                                                                                                                         , "0, true, false"                            , "Dante Nevan"                         ],
	[ 0x228CF0 , "WeaponData *", "byte8 * actorData, uint32 id"                                                                                                                                                                         , "0, true, false"                            , "Dante Vergil Beowulf"                ],
	[ 0x22B0C0 , "WeaponData *", "byte8 * actorData, uint32 id"                                                                                                                                                                         , "0, true, false"                            , "Dante Ebony & Ivory"                 ],
	[ 0x2306B0 , "WeaponData *", "byte8 * actorData, uint32 id"                                                                                                                                                                         , "0, true, false"                            , "Dante Shotgun"                       ],
	[ 0x22C4A0 , "WeaponData *", "byte8 * actorData, uint32 id"                                                                                                                                                                         , "0, true, false"                            , "Dante Artemis"                       ],
	[ 0x2300A0 , "WeaponData *", "byte8 * actorData, uint32 id"                                                                                                                                                                         , "0, true, false"                            , "Dante Spiral"                        ],
	[ 0x22BA30 , "WeaponData *", "byte8 * actorData, uint32 id"                                                                                                                                                                         , "0, true, false"                            , "Dante Lady Kalina Ann"               ],
	[ 0x231A30 , "WeaponData *", "byte8 * actorData, uint32 id"                                                                                                                                                                         , "0, true, false"                            , "Bob Yamato"                          ],
	[ 0x22D960 , "WeaponData *", "byte8 * actorData, uint32 id"                                                                                                                                                                         , "0, true, false"                            , "Vergil Yamato"                       ],
	[ 0x2298E0 , "WeaponData *", "byte8 * actorData, uint32 id"                                                                                                                                                                         , "0, true, false"                            , "Vergil Force Edge"                   ],
	[ 0x22CF00 , "WeaponData *", "byte8 * actorData, uint32 id"                                                                                                                                                                         , "0, true, false"                            , "Vergil Nero Angelo Sword"            ],
	[ 0x280120 , "void"        , "byte8 * dest, uint32 side, uint32 index"                                                                                                                                                              , ""                                          , "Weapon Switch Animation Dante"       ],
	[ 0x280160 , "void"        , "byte8 * dest, uint32 group, uint32 index, uint32 motion"                                                                                                                                              , ""                                          , "Weapon Switch Animation Vergil"      ],
	[ 0x1EB0E0 , "void"        , "byte8 * actorData, uint32 index"                                                                                                                                                                      , ""                                          , "Call after Weapon Switch Animation." ],
	[ 0x1F92C0 , "void"        , "byte8 * actorData, uint32 phase"                                                                                                                                                                      , ""                                          , "Queue devil model update."           ],
	[ 0x1F97F0 , "void"        , "byte8 * actorData, bool noMotion"                                                                                                                                                                     , ""                                          , "Update devil model and play motion." ],
	[ 0x1F94D0 , "void"        , "byte8 * actorData, uint8 index"                                                                                                                                                                       , ""                                          , "Devil Flux"                          ],
	[ 0x1EAE60 , "void"        , "byte8 * actorData, uint8 index"                                                                                                                                                                       , ""                                          , "Play Doppelganger Effect"            ],
	[ 0x1FCA20 , "void"        , "byte8 * actorBaseAddr, uint32 visibility"                                                                                                                                                             , ""                                          , "Update Color Matrices"               ],
	[ 0x32E5F0 , "float32"     , "vec4 & position"                                                                                                                                                                                      , "0, true, false"                            , ""                                    ],
	[ 0x89E30  , "void"        , "ModelData & modelData, uint32 index"                                                                                                                                                                  , ""                                          , "Call after icon update."             ],
	[ 0x1B9FA0 , "void"        , "byte8 * addr"                                                                                                                                                                                         , ""                                          , "Adjust file pointers."               ],
	[ 0x223AC0 , "void"        , "byte8 * actorData"                                                                                                                                                                                    , ""                                          , "Create Spiral Swords."               ],
	[ 0x223F50 , "void"        , "byte8 * actorData, uint32 index"                                                                                                                                                                      , ""                                          , "Specific Summoned Swords."           ],
	[ 0x223BE0 , "void"        , "byte8 * actorData, uint32 index"                                                                                                                                                                      , ""                                          , "Shoot Summoned Sword. Use index 52." ],
	[ 0x594B0  , "void"        , "BodyPartData & bodyPartData, byte8 * file, uint32 bodyPart, uint32, byte8 ** motionArchives, byte8 *** modelDataFunctions, PhysicsMetadata ** modelPhysicsMetadataPool, float32 * motionSpeed, void *", "0, true, true, 0, 0, 0, 0, 5"              , ""                                    ],
	[ 0x5A290  , "void"        , "byte8 * body, uint32 group, uint32 index, uint16, uint8, uint8"                                                                                                                                       , "0, true, true, 0, 0, 0, 0, 2"              , "Play Motion"                         ],
	[ 0x8AC80  , "void"        , "ModelData & modelData, uint32 bodyPart, byte8 * motionFile, uint32, bool"                                                                                                                             , "0, true, true, 0, 0, 0, 0, 1"              , "Play Motion"                         ],
	[ 0x1EFB90 , "void"        , "byte8 * actorData, uint32 group, uint32 index, float32, int8, uint8, uint8"                                                                                                                           , "0, true, true, 0, 0, 0, 0, 3"              , "Play motion and update state."       ],
	[ 0x1DFDA0 , "void"        , "byte8 *, uint32, uint8, float32, float32, uint8"                                                                                                                                                      , "0, true, true, 0, 0, 0, 0, 2"              , "Drop1"                               ],
	[ 0x1FB300 , "void"        , "byte8 * actorData, uint32 direction, float32 value"                                                                                                                                                   , ""                                          , "Adjust Position"                     ],
	[ 0x1E09D0 , "void"        , "byte8 * actorBaseAddr, uint32 event"                                                                                                                                                                  , ""                                          , ""                                    ],
	[ 0x175210 , "byte8 *"     , "vec4 *, vec4 *, __m128"                                                                                                                                                                               , "0, true, false, 0, 0, 0, 0, 0, false, true", "Boss Lady Grenade"                   ],
	[ 0x1E0800 , "void"        , "byte8 * actorData, uint32 index, uint32, uint32"                                                                                                                                                      , ""                                          , "Trigger Attack"                      ],
	[ 0x211100 , "void"        , "byte8 * actorData"                                                                                                                                                                                    , ""                                          , "Rebellion Combo 1 Part 3"            ],
	[ 0x1F01F0 , "void"        , "byte8 * actorData, uint32 index"                                                                                                                                                                      , ""                                          , "Reset State"                         ],
	[ 0x2F74E0 , "void"        , "byte8 * dest, uint32 index"                                                                                                                                                                           , ""                                          , "Show Model Partition"                ],
	[ 0x2F7350 , "void"        , "byte8 * dest, uint32 index"                                                                                                                                                                           , ""                                          , "Hide Model Partition"                ],
	[ 0x32BE20 , "void"        , "byte8 * dest"                                                                                                                                                                                         , ""                                          , "Init Track"                          ],
	[ 0x32BA90 , "void"        , "byte8 * dest, const char * location, uint32, uint32"                                                                                                                                                  , ""                                          , "Set Track"                           ],
	[ 0x8A520  , "byte8 *"     , "ModelData & modelData"                                                                                                                                                                                , "0, true, false"                            , ""                                    ],
	[ 0x30E630 , "void"        , "byte8 * dest, uint32 index"                                                                                                                                                                           , ""                                          , ""                                    ],
];



// Typedefs
{

for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
{
	let item = items[itemIndex];

	let off                = item[0];
	let returnType         = item[1];
	let args               = item[2];
	let createFunctionArgs = item[3];
	let hint               = item[4];



	let offName = PositionName
	(
		off,
		(PositionFlags_Hex | PositionFlags_NoPrefix)
	);



	c += Tabs() + "export typedef " + returnType + "(__fastcall * func_" + offName + "_t)(" + args + ");";

	if (hint != "")
	{
		c += Tabs() + " // " + hint;
	}

	c += NEW_LINE;
}

c += NEW_LINE;

}



// Vars
{

for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
{
	let item = items[itemIndex];

	let off                = item[0];
	let returnType         = item[1];
	let args               = item[2];
	let createFunctionArgs = item[3];
	let hint               = item[4];



	let offName = PositionName
	(
		off,
		(PositionFlags_Hex | PositionFlags_NoPrefix)
	);



	c += Tabs() + "export func_" + offName + "_t func_" + offName + " = 0; // (" + args + ")" + NEW_LINE;
}

c += NEW_LINE;

}



// Init
{

c += Tabs() + "export void Internal_Init()" + NEW_LINE;

ScopeStart();

c += Tabs() + "LogFunction();" + NEW_LINE;
c += NEW_LINE;



for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
{
	let item = items[itemIndex];

	let off                = item[0];
	let returnType         = item[1];
	let args               = item[2];
	let createFunctionArgs = item[3];
	let hint               = item[4];



	let offName = PositionName
	(
		off,
		(PositionFlags_Hex | PositionFlags_NoPrefix)
	);



	ScopeStart();

	c += Tabs() + "auto func = CreateFunction((appBaseAddr + 0x" + offName + ")";

	if (createFunctionArgs != "")
	{
		c += ", " + createFunctionArgs;
	}

	c += ");" + NEW_LINE;

	c += Tabs() + "func_" + offName + " = (func_" + offName + "_t)func.addr;" + NEW_LINE;

	ScopeEnd();
}

ScopeEnd();

c += NEW_LINE;

}



CleanStream();

c_new = c;

ClearAll();



file = c_until + c_new + c_after;



fs.writeFileSync(location, file);
