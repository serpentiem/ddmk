NEW_LINE = "\r\n";

var fs = require("fs");

var c = "";
var c_typedefs = "";
var c_vars = "";
var c_init = "";

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
	[ 0x217B90, "void"   , "byte8 * actorData, byte8 * missionActorData"                                       , ""                            , "Init Actor Dante"                    ],
	[ 0x226F10, "void"   , "byte8 * actorData, byte8 * missionActorData"                                       , ""                            , "Init Actor Bob"                      ],
	[ 0x219660, "void"   , "byte8 * actorData, byte8 * missionActorData"                                       , ""                            , "Init Actor Lady"                     ],
	[ 0x223CB0, "void"   , "byte8 * actorData, byte8 * missionActorData"                                       , ""                            , "Init Actor Vergil"                   ],
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
	//[ 0x23E560, "void"   , "byte8 * eventData, uint32 position"                                           , ""                            , ""                                    ],
	
	[ 0x89E30 , "void"   , "byte8 * baseAddr, uint32 index"                                               , ""                            , "Call after icon update."             ],
	[ 0x1B9FA0, "void"   , "byte8 * addr"                                                                 , ""                            , "Adjust file pointers."               ],
	[ 0x223AC0, "void"   , "byte8 * actorData"                                                            , ""                            , "Create Spiral Swords."               ],
	[ 0x223F50, "void"   , "byte8 * actorData, uint32 index"                                              , ""                            , "Specific Summoned Swords."           ],
	[ 0x223BE0, "void"   , "byte8 * actorData, uint32 index"                                              , ""                            , "Shoot Summoned Sword. Use index 52." ],



	[ 0x5A290 , "void"   , "byte8 * body, uint32 group, uint32 index, uint16, uint8, uint8"    , "0, true, true, 0, 0, 0, 0, 2", "Play Motion"                         ],
	[ 0x8AC80 , "void"   , "MODEL_DATA & modelData, uint32 bodyPart, byte8 * motionFile, uint32, bool"    , "0, true, true, 0, 0, 0, 0, 1", "Play Motion"                         ],






	[ 0x1EFB90, "void", "byte8 * actorData, uint32 group, uint32 index, float32, int8, uint8, uint8", "0, true, true, 0, 0, 0, 0, 3", "Play motion and update state." ],
	
	
	
	
	/*dmc3.exe+204C76 - E8 25B1FDFF           - call dmc3.exe+1DFDA0 { drop func
 }
*/
	
	
	
	
	[ 0x1DFDA0, "void", "byte8 *, uint32, uint8, float32, float32, uint8", "0, true, true, 0, 0, 0, 0, 2", "Drop1" ],

	[ 0x1FB300, "void", "byte8 * actorData, uint32 direction, float32 value", "", "Adjust Position" ],



/*
dmc3.exe+1FF64D - F3 0F10 15 17DF1500   - movss xmm2,[dmc3.exe+35D56C] { (1.00) }
dmc3.exe+1FF655 - 48 8B CB              - mov rcx,rbx
dmc3.exe+1FF658 - 0FB7 93 D23E0000      - movzx edx,word ptr [rbx+00003ED2]
dmc3.exe+1FF65F - E8 9CBCFFFF           - call dmc3.exe+1FB300

*/






	[ 0x1E0800, "void", "byte8 * actorData, uint32 index, uint32, uint32", "", "Trigger Attack" ],




	[ 0x211100, "void", "byte8 * actorData", "", "Rebellion Combo 1 Part 3" ],



	[ 0x1F01F0, "void", "byte8 * actorData, uint32 index", "", "Reset State" ],



/*
dmc3.exe+1EFC36 - E8 55A6E6FF           - call dmc3.exe+5A290 { __ONLY_THIS_ONE_REALLY_MATTERS__
 }

*/





[ 0x2F74E0 , "void"   , "byte8 * dest, uint32 index"    , "", "Show Model Partition"                         ],
[ 0x2F7350 , "void"   , "byte8 * dest, uint32 index"    , "", "Hide Model Partition"                         ],




//[ 0x23E560, "void"   , "byte8 *, uint32"    , "", "Set Start Position"],

/*
dmc3.exe+23CC23 - E8 38190000           - call dmc3.exe+23E560
*/



[ 0x32BE20, "void", "byte8 * dest"                                       , "", "Init Track" ],
[ 0x32BA90, "void", "byte8 * dest, const char * filename, uint32, uint32", "", "Set Track"  ],


/*







dmc3.exe+243325 - 45 33 C9              - xor r9d,r9d { __SET_TRACK__
 }
dmc3.exe+243328 - 48 8D 15 D9002A00     - lea rdx,[dmc3.exe+4E3408] { ("afs/sound/Kaze_01.adx") }
dmc3.exe+24332F - 45 33 C0              - xor r8d,r8d
dmc3.exe+243332 - 48 8D 0D CF03AB00     - lea rcx,[dmc3.exe+CF3708] { (0) }
dmc3.exe+243339 - E8 52870E00           - call dmc3.exe+32BA90

*/




];

for (var index = 0; index < items.length; index++)
{
	var off                = items[index][0];
	var returnType         = items[index][1];
	var args               = items[index][2];
	var createFunctionArgs = items[index][3];
	var hint               = items[index][4];
	
	var offStr = off.toString(16).toUpperCase();
	
	c_typedefs += "export typedef " + returnType + "(__fastcall * func_" + offStr + "_t)(" + args + ");";
	if (hint != "")
	{
		c_typedefs += " // " + hint;
	}
	c_typedefs += "" + NEW_LINE;

	c_vars += "export func_" + offStr + "_t func_" + offStr + " = 0;" + NEW_LINE;
	
	c_init += "\t{" + NEW_LINE;
	c_init += "\t\tauto func = CreateFunction((appBaseAddr + 0x" + offStr + ")";
	if (createFunctionArgs != "")
	{
		c_init += ", " + createFunctionArgs;
	}
	c_init += ");" + NEW_LINE;
	c_init += "\t\tfunc_" + offStr + " = (func_" + offStr + "_t)func.addr;" + NEW_LINE;
	c_init += "\t}" + NEW_LINE;
}

c += "#ifndef __MODULE_INTERNAL__" + NEW_LINE;
c += "#define __MODULE_INTERNAL__" + NEW_LINE;
c += NEW_LINE;
c += "module;" + NEW_LINE;
c += "#include \"../Core/Core.h\"" + NEW_LINE;
c += NEW_LINE;
c += "#include \"Vars.h\"" + NEW_LINE;
c += "export module ModuleName(Internal);" + NEW_LINE;
c += NEW_LINE;

c += c_typedefs;
c += NEW_LINE;

c += c_vars;
c += NEW_LINE;

c += "export void Internal_Init()" + NEW_LINE;
c += "{" + NEW_LINE;
c += "\tLogFunction();" + NEW_LINE;
c += c_init;
c += "}" + NEW_LINE;

c += NEW_LINE;
c += "#endif" + NEW_LINE;

fs.writeFileSync("../Mary/Internal.ixx", c);
