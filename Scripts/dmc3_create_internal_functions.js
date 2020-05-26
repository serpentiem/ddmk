var c_typedef = "";
var c_extern = "";
var c_vars = "";
var c_init = "";
var fs = require("fs");

var items =
[
	[ 0x897B0 , "void"   , "byte8 * dest"                                                                 , ""                            , ""                                    ],
	[ 0x89450 , "void"   , "byte8 * dest"                                                                 , ""                            , ""                                    ],
	[ 0x89270 , "void"   , "byte8 * dest"                                                                 , ""                            , ""                                    ],
	[ 0x8B470 , "void"   , "byte8 * dest, uint32 flag"                                                    , ""                            , ""                                    ],
	[ 0x89960 , "void"   , "byte8 * dest, byte8 * modelFile, byte8 * textureFile"                         , ""                            , ""                                    ],
	[ 0x89DE0 , "byte8 *", "byte8 * dest"                                                                 , "0, true, false"              , ""                                    ],
	[ 0x8BC60 , "void"   , "byte8 * dest, byte8 * addr, byte8 * shadowFile"                               , ""                            , ""                                    ],
	[ 0x305D80, "void"   , "byte8 * dest"                                                                 , ""                            , ""                                    ],
	[ 0x8A000 , "void"   , "byte8 * dest, byte8 * motionFile, byte8 * addr"                               , ""                            , ""                                    ],
	[ 0x2C9F40, "uint32 ", "byte8 * physicsFile"                                                          , "0, true, false"              , ""                                    ],
	[ 0x2CA1D0, "void"   , "byte8 * dest, byte8 * addr, byte8 * physicsFile, uint32 index"                , ""                            , ""                                    ],
	[ 0x2CA2F0, "void"   , "byte8 * dest, byte8 * addr, byte8 *, MODEL_METADATA * modelData, uint32 count", "0, true, true, 0, 0, 0, 0, 1", ""                                    ],
	[ 0x1EF040, "void"   , "byte8 * baseAddr, uint32 index"                                               , ""                            , ""                                    ],
	[ 0x2EE3D0, "void"   , "byte8 * dest"                                                                 , ""                            , ""                                    ],
	[ 0x1FAF40, "void"   , "byte8 * baseAddr"                                                             , ""                            , ""                                    ],
	[ 0x1EEF80, "void"   , "byte8 * baseAddr"                                                             , ""                            , ""                                    ],
	[ 0x2EE060, "bool"   , "byte8 * dest, uint32 size"                                                    , ""                            , ""                                    ],
	[ 0x1DE820, "byte8 *", "uint32 character, uint32 id, bool isClone"                                    , "0, true, false"              , "Create Actor"                        ],
	[ 0x217B90, "void"   , "byte8 * actorData, byte8 * sessionData"                                       , ""                            , "Init Actor Dante"                    ],
	[ 0x226F10, "void"   , "byte8 * actorData, byte8 * sessionData"                                       , ""                            , "Init Actor Bob"                      ],
	[ 0x219660, "void"   , "byte8 * actorData, byte8 * sessionData"                                       , ""                            , "Init Actor Lady"                     ],
	[ 0x223CB0, "void"   , "byte8 * actorData, byte8 * sessionData"                                       , ""                            , "Init Actor Vergil"                   ],
	[ 0x212BE0, "void"   , "byte8 * actorData"                                                            , ""                            , "Update Actor Dante"                  ],
	[ 0x225D70, "void"   , "byte8 * actorData"                                                            , ""                            , "Update Actor Bob"                    ],
	[ 0x219260, "void"   , "byte8 * actorData"                                                            , ""                            , "Update Actor Lady"                   ],
	[ 0x220970, "void"   , "byte8 * actorData"                                                            , ""                            , "Update Actor Vergil"                 ],
	[ 0x1DFC20, "void"   , "byte8 * actorData"                                                            , ""                            , ""                                    ],
	[ 0x2310B0, "byte8 *", "byte8 * actorData, uint32 id"                                                 , "0, true, false"              , "Dante Rebellion"                     ],
	[ 0x22EC90, "byte8 *", "byte8 * actorData, uint32 id"                                                 , "0, true, false"              , "Dante Cerberus"                      ],
	[ 0x227870, "byte8 *", "byte8 * actorData, uint32 id"                                                 , "0, true, false"              , "Dante Agni & Rudra"                  ],
	[ 0x22A1E0, "byte8 *", "byte8 * actorData, uint32 id"                                                 , "0, true, false"              , "Dante Nevan"                         ],
	[ 0x228CF0, "byte8 *", "byte8 * actorData, uint32 id"                                                 , "0, true, false"              , "Dante Vergil Beowulf"                ],
	[ 0x22B0C0, "byte8 *", "byte8 * actorData, uint32 id"                                                 , "0, true, false"              , "Dante Ebony & Ivory"                 ],
	[ 0x2306B0, "byte8 *", "byte8 * actorData, uint32 id"                                                 , "0, true, false"              , "Dante Shotgun"                       ],
	[ 0x22C4A0, "byte8 *", "byte8 * actorData, uint32 id"                                                 , "0, true, false"              , "Dante Artemis"                       ],
	[ 0x2300A0, "byte8 *", "byte8 * actorData, uint32 id"                                                 , "0, true, false"              , "Dante Spiral"                        ],
	[ 0x22BA30, "byte8 *", "byte8 * actorData, uint32 id"                                                 , "0, true, false"              , "Dante Lady Kalina Ann"               ],
	[ 0x231A30, "byte8 *", "byte8 * actorData, uint32 id"                                                 , "0, true, false"              , "Bob Yamato"                          ],
	[ 0x22D960, "byte8 *", "byte8 * actorData, uint32 id"                                                 , "0, true, false"              , "Vergil Yamato"                       ],
	[ 0x2298E0, "byte8 *", "byte8 * actorData, uint32 id"                                                 , "0, true, false"              , "Vergil Force Edge"                   ],
	[ 0x22CF00, "byte8 *", "byte8 * actorData, uint32 id"                                                 , "0, true, false"              , "Vergil Nero Angelo Sword"            ],
	[ 0x280120, "void"   , "byte8 * dest, uint32 side, uint32 index"                                      , ""                            , "Weapon Switch Animation Dante"       ],
	[ 0x280160, "void"   , "byte8 * dest, uint32 group, uint32 index, uint32 motion"                      , ""                            , "Weapon Switch Animation Vergil"      ],
	[ 0x1EB0E0, "void"   , "byte8 * actorData, uint32 index"                                              , ""                            , "Call after Weapon Switch Animation." ],
	[ 0x1F92C0, "void"   , "byte8 * actorData, uint32 phase"                                              , ""                            , "Queue devil model update."           ], // @Research: Works like bool, but has size of uint32.
	[ 0x1F97F0, "void"   , "byte8 * actorData, bool playMotion"                                           , ""                            , "Update devil model and play motion." ],
	[ 0x23E560, "void"   , "byte8 * eventData, uint32 position"                                           , ""                            , ""                                    ],
	[ 0x8AC80 , "void"   , "MODEL_DATA & modelData, uint32 bodyPart, byte8 * motionFile, uint32, bool"    , "0, true, true, 0, 0, 0, 0, 1", "Play Motion"                         ],
	[ 0x89E30 , "void"   , "byte8 * baseAddr, uint32 index"                                               , ""                            , "Call after icon update."             ],
	[ 0x1B9FA0, "void"   , "byte8 * addr"                                                                 , ""                            , "Adjust file pointers."               ],
	[ 0x223AC0, "void"   , "byte8 * actorData"                                                            , ""                            , "Create Spiral Swords."               ],
	[ 0x223F50, "void"   , "byte8 * actorData, uint32 index"                                              , ""                            , "Specific Summoned Swords."           ],
	[ 0x223BE0, "void"   , "byte8 * actorData, uint32 index"                                              , ""                            , "Shoot Summoned Sword. Use index 52." ],





	[ 0x1EFB90, "void"   , "byte8 * actorData, uint32 group, uint32 index, float32, uint8, uint8, uint8"                                              , ""                            , "Play motion and update state." ],





	[ 0x1E0800, "void", "byte8 * actorData, uint32 index, uint32, uint32", "", "Trigger Attack" ],




	[ 0x211100, "void", "byte8 * actorData", "", "Rebellion Combo 1 Part 3" ],



	[ 0x1F01F0, "void", "byte8 * actorData, uint32 index", "", "Reset State" ],



/*
dmc3.exe+1EFC36 - E8 55A6E6FF           - call dmc3.exe+5A290 { __ONLY_THIS_ONE_REALLY_MATTERS__
 }

*/

[ 0x5A290 , "void"   , "byte8 * body, uint32 group, uint32 index, uint16, uint8, uint8"    , "0, true, true, 0, 0, 0, 0, 2", "Play Motion"                         ],



[ 0x2F74E0 , "void"   , "byte8 * dest, uint32 index"    , "", "Show Model Partition"                         ],
[ 0x2F7350 , "void"   , "byte8 * dest, uint32 index"    , "", "Hide Model Partition"                         ],











];

for (var index = 0; index < items.length; index++)
{
	var off                = items[index][0];
	var returnType         = items[index][1];
	var args               = items[index][2];
	var createFunctionArgs = items[index][3];
	var hint               = items[index][4];
	
	var offStr = off.toString(16).toUpperCase();
	
	c_typedef += "typedef " + returnType + "(__fastcall * func_" + offStr + "_t)(" + args + ");";
	if (hint != "")
	{
		c_typedef += " // " + hint;
	}
	c_typedef += "\r\n";
	
	c_extern += "extern func_" + offStr + "_t func_" + offStr + ";\r\n";
	
	c_vars += "func_" + offStr + "_t func_" + offStr + " = 0;\r\n";
	
	c_init += "\t{\r\n";
	c_init += "\t\tauto func = CreateFunction((appBaseAddr + 0x" + offStr + ")";
	if (createFunctionArgs != "")
	{
		c_init += ", " + createFunctionArgs;
	}
	c_init += ");\r\n";
	c_init += "\t\tfunc_" + offStr + " = (func_" + offStr + "_t)func.addr;\r\n";
	c_init += "\t}\r\n";
}

var h = "";
h += "#pragma once\r\n";
h += "#include \"../Core/Core.h\"\r\n";
h += "\r\n";
h += "#include \"Vars.h\"\r\n";
h += "\r\n";
h += c_typedef;
h += "\r\n";
h += c_extern;
h += "\r\n";
h += "void Internal_Init();\r\n";

var cpp = "";
cpp += "#include \"Internal.h\"\r\n";
cpp += "\r\n";
cpp += c_vars;
cpp += "\r\n";
cpp += "void Internal_Init()\r\n";
cpp += "{\r\n";
cpp += "\tLogFunction();\r\n";
cpp += c_init;
cpp += "}\r\n";

fs.writeFileSync("../Mary/Internal.h", h);
fs.writeFileSync("../Mary/Internal.cpp", cpp);
