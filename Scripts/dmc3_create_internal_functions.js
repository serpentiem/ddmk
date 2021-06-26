



/*
dmc3.exe+1F7C85 - E8 36160000 - call dmc3.exe+1F92C0
dmc3.exe+1F7C8A - 45 33 C9    - xor r9d,r9d
dmc3.exe+1F7C8D - 45 33 C0    - xor r8d,r8d
dmc3.exe+1F7C90 - 33 D2       - xor edx,edx
dmc3.exe+1F7C92 - 48 8B CB    - mov rcx,rbx
dmc3.exe+1F7C95 - E8 56F6FFFF - call dmc3.exe+1F72F0
dmc3.exe+1F7C9A - 48 8B CB    - mov rcx,rbx
dmc3.exe+1F7C9D - 33 D2       - xor edx,edx
dmc3.exe+1F7C9F - E8 8C83FEFF - call dmc3.exe+1E0030
*/





let fs = require("fs");
let vm = require("vm");

vm.runInThisContext(fs.readFileSync("core.js", "utf8"));

ClearAll();






let c_typedefs = "";
let c_vars = "";
let c_init = "";

let items =
[
	[ 0x897B0 , "void"   , "ModelData & modelData"                                                                       , ""                            , "" ],
	[ 0x89450 , "void"   , "ModelData & modelData"                                                                       , ""                            , "" ],
	[ 0x89270 , "void"   , "ModelData & modelData"                                                                       , ""                            , "" ],

	[ 0x8B470 , "void"   , "ModelData & modelData, bool32 enable"                                                   , ""                            , "" ],
	[ 0x89960 , "void"   , "ModelData & modelData, byte8 * modelFile, byte8 * textureFile"                          , ""                            , "" ],
	// @Todo: void *.
	[ 0x1EF040, "void"   , "byte8 * actorData, uint32 index"                                                    , ""                            , "" ], // @Research: Check if modelIndex.





	[ 0x89DE0 , "byte8 *", "ModelData & modelData"                                                                  , "0, true, false"              , "" ],
	[ 0x8BC60 , "void"   , "ShadowData & shadowData, byte8 * dest, byte8 * file"                                     , ""                            , "" ],
	[ 0x305D80, "void"   , "byte8 * dest"                                                                       , ""                            , "" ],
	[ 0x8A000 , "void"   , "ModelData & modelData, byte8 * motionFile, PhysicsMetadata ** modelPhysicsMetadataPool"                                 , ""                            , "" ],



	[ 0x2C9F40, "uint32" , "byte8 * physicsFile"                                                                       , "0, true, false"              , "" ],



	[ 0x2CA1D0, "void"   , "PhysicsData & physicsData, PhysicsMetadata ** physicsMetadata, byte8 * physicsFile, uint32 index"                       , ""                            , "" ],



	[ 0x2CA2F0, "void"   , "PhysicsData & physicsData, void * dest, byte8 * addr, ModelMetadata * modelMetadata, uint32 count", "0, true, true, 0, 0, 0, 0, 1", "" ], // @Research: Check addr.




	[ 0x2C6150, "void *", "void * dest, uint32 size, int32 mode", "", "Alloc" ],
	




	[ 0x1FD3E0, "bool", "WeaponData & weaponData, uint8", "", "IsWeaponReady" ],
	[ 0x1FDE10, "void", "WeaponData & weaponData", "", "Show Weapon" ],






/*
dmc3.exe+1F7CD2 - 81 8B F4CA0100 00000008 - or [rbx+0001CAF4],08000000
dmc3.exe+1F7CDC - 48 8B CB                - mov rcx,rbx
dmc3.exe+1F7CDF - E8 6C2D0000             - call dmc3.exe+1FAA50
dmc3.exe+1F7CE4 - FF C0                   - inc eax
dmc3.exe+1F7CE6 - 4C 8B C3                - mov r8,rbx
dmc3.exe+1F7CE9 - B9 3B000000             - mov ecx,0000003B
dmc3.exe+1F7CEE - 48 8B 94 C3 D0E50000    - mov rdx,[rbx+rax*8+0000E5D0]
dmc3.exe+1F7CF6 - 48 8B 92 10010000       - mov rdx,[rdx+00000110]
dmc3.exe+1F7CFD - E8 2E42E9FF             - call dmc3.exe+8BF30
*/


[ 0x8BF30, "void", "uint32 index, void * dest, byte8 * baseAddr", "", "" ],
























/*
mov byte ptr [rsp],3A
mov byte ptr [rsp+4],00

mov rcx,[dmc3.exe+C90E10]
mov rcx,[rcx+28]
lea rcx,[rcx+CB0]

lea rdx,[rsp]

call dmc3.exe+1A4680
*/

/*
dmc3.exe+212013 - 48 8D 8B 10640000     - lea rcx,[rbx+00006410]
dmc3.exe+21201A - E8 A1BF0D00           - call dmc3.exe+2EDFC0
dmc3.exe+21201F - 48 8D 8B 58640000     - lea rcx,[rbx+00006458]
dmc3.exe+212026 - E8 E5561200           - call dmc3.exe+337710
*/

[ 0x2EDFC0, "void", "byte8 *", "", "" ],
[ 0x337710, "void", "byte8 *", "", "" ],



/*

dmc3.exe+1E9489 - E8 02160900           - call dmc3.exe+27AA90 { effect
 }




*/


	
	[ 0x27AA90, "bool", "void *, uint32, void *, float", "", "" ],








	[ 0x1A4680, "byte8 *", "byte8 *, const CreateEnemyActorData &", "0, true, false", "Create Enemy Actor" ],




	
	[ 0x3391C0, "void", "void *, int32, int32, int32, int32", "0, true, true, 0, 0, 0, 0, 1", "Play Sound" ],


/*
mov rcx,[dmc3.exe+C90E10]
mov rcx,[rcx+28]
lea rcx,[rcx+CB0]

lea rdx,[rsp]

call dmc3.exe+1A4680
*/



/*
dmc3.exe+2A02E3 - 48 8D 0D A6D9AC00     - lea rcx,[dmc3.exe+D6DC90] { (1) }
dmc3.exe+2A02E1 - 33 D2                 - xor edx,edx
dmc3.exe+2A02EA - 45 8D 41 02           - lea r8d,[r9+02]
dmc3.exe+2A02D9 - 45 33 C9              - xor r9d,r9d
dmc3.exe+2A02DC - 44 89 7C 24 20        - mov [rsp+20],r15d
dmc3.exe+2A02EE - E8 CD8E0900           - call dmc3.exe+3391C0
*/



/*
// @Todo: Add to CleanPDB.
dmc3.exe+280F3F - 41 B8 0C000000        - mov r8d,Mary.stbi__vertically_flip_on_load_local { 0000000C }
*/














	[ 0x2EE3D0, "void"   , "byte8 * dest"                                                                 , ""                            , ""                                    ],







	[ 0x1FAF40, "void"   , "byte8 * baseAddr"                                                             , ""                            , ""                                    ],
	[ 0x1EEF80, "void"   , "byte8 * baseAddr"                                                             , ""                            , ""                                    ],


	
	[ 0x2EE060, "bool"   , "byte8 * dest, uint32 size"                                                    , ""                            , ""                                    ],




	
	[ 0x1DE820, "byte8 *", "uint32 character, uint32 id, bool isClone"                                    , "0, true, false"              , "Create Actor"                        ],
	[ 0x217B90, "void"   , "byte8 * actorData, ActiveMissionActorData & activeMissionActorData"                                       , ""                            , "Init Actor Dante"                    ],
	[ 0x226F10, "void"   , "byte8 * actorData, ActiveMissionActorData & activeMissionActorData"                                       , ""                            , "Init Actor Bob"                      ],
	[ 0x219660, "void"   , "byte8 * actorData, ActiveMissionActorData & activeMissionActorData"                                       , ""                            , "Init Actor Lady"                     ],
	[ 0x223CB0, "void"   , "byte8 * actorData, ActiveMissionActorData & activeMissionActorData"                                       , ""                            , "Init Actor Vergil"                   ],
	[ 0x212BE0, "void"   , "byte8 * actorData"                                                            , ""                            , "Update Actor Dante"                  ],
	[ 0x225D70, "void"   , "byte8 * actorData"                                                            , ""                            , "Update Actor Bob"                    ],
	[ 0x219260, "void"   , "byte8 * actorData"                                                            , ""                            , "Update Actor Lady"                   ],
	[ 0x220970, "void"   , "byte8 * actorData"                                                            , ""                            , "Update Actor Vergil"                 ],
	[ 0x1DFC20, "void"   , "byte8 * actorData"                                                            , ""                            , ""                                    ],




	[ 0x2310B0, "WeaponData *", "byte8 * actorData, uint32 id"                                                 , "0, true, false"              , "Dante Rebellion"                     ],
	[ 0x22EC90, "WeaponData *", "byte8 * actorData, uint32 id"                                                 , "0, true, false"              , "Dante Cerberus"                      ],
	[ 0x227870, "WeaponData *", "byte8 * actorData, uint32 id"                                                 , "0, true, false"              , "Dante Agni & Rudra"                  ],
	[ 0x22A1E0, "WeaponData *", "byte8 * actorData, uint32 id"                                                 , "0, true, false"              , "Dante Nevan"                         ],
	[ 0x228CF0, "WeaponData *", "byte8 * actorData, uint32 id"                                                 , "0, true, false"              , "Dante Vergil Beowulf"                ],
	[ 0x22B0C0, "WeaponData *", "byte8 * actorData, uint32 id"                                                 , "0, true, false"              , "Dante Ebony & Ivory"                 ],
	[ 0x2306B0, "WeaponData *", "byte8 * actorData, uint32 id"                                                 , "0, true, false"              , "Dante Shotgun"                       ],
	[ 0x22C4A0, "WeaponData *", "byte8 * actorData, uint32 id"                                                 , "0, true, false"              , "Dante Artemis"                       ],
	[ 0x2300A0, "WeaponData *", "byte8 * actorData, uint32 id"                                                 , "0, true, false"              , "Dante Spiral"                        ],
	[ 0x22BA30, "WeaponData *", "byte8 * actorData, uint32 id"                                                 , "0, true, false"              , "Dante Lady Kalina Ann"               ],
	[ 0x231A30, "WeaponData *", "byte8 * actorData, uint32 id"                                                 , "0, true, false"              , "Bob Yamato"                          ],
	[ 0x22D960, "WeaponData *", "byte8 * actorData, uint32 id"                                                 , "0, true, false"              , "Vergil Yamato"                       ],
	[ 0x2298E0, "WeaponData *", "byte8 * actorData, uint32 id"                                                 , "0, true, false"              , "Vergil Force Edge"                   ],
	[ 0x22CF00, "WeaponData *", "byte8 * actorData, uint32 id"                                                 , "0, true, false"              , "Vergil Nero Angelo Sword"            ],







	[ 0x280120, "void" , "byte8 * dest, uint32 side, uint32 index" , "" , "Weapon Switch Animation Dante" ],
	[ 0x280160, "void" , "byte8 * dest, uint32 group, uint32 index, uint32 motion" , "" , "Weapon Switch Animation Vergil" ],
	[ 0x1EB0E0, "void" , "byte8 * actorData, uint32 index" , "" , "Call after Weapon Switch Animation." ],





	[ 0x1F92C0, "void" , "byte8 * actorData, uint32 phase" , "" , "Queue devil model update." ],
	[ 0x1F97F0, "void" , "byte8 * actorData, bool noMotion" , "" , "Update devil model and play motion." ],




	[ 0x1F94D0, "void"   , "byte8 * actorData, uint8 index", "", "Devil Flux"  ],
	[ 0x1EAE60, "void"   , "byte8 * actorData, uint8 index", "", "Play Doppelganger Effect" ],



	[ 0x1FCA20 , "void", "byte8 * actorBaseAddr, uint32 visibility", "", "Update Color Matrices" ],





	[ 0x32E5F0, "float32"   , "vec4 & position", "0, true, false", "" ],
	
	
/*
dmc3.exe+1BB69D - E8 4E2F1700           - call dmc3.exe+32E5F0 { actor position vector
 }

*/

	





	[ 0x89E30 , "void"   , "ModelData & modelData, uint32 index"                                               , ""                            , "Call after icon update."             ],




	[ 0x1B9FA0, "void"   , "byte8 * addr"                                                                 , ""                            , "Adjust file pointers."               ],
	[ 0x223AC0, "void"   , "byte8 * actorData"                                                            , ""                            , "Create Spiral Swords."               ],
	[ 0x223F50, "void"   , "byte8 * actorData, uint32 index"                                              , ""                            , "Specific Summoned Swords."           ],
	[ 0x223BE0, "void"   , "byte8 * actorData, uint32 index"                                              , ""                            , "Shoot Summoned Sword. Use index 52." ],




	[ 0x594B0, "void", "BodyPartData & bodyPartData, byte8 * file, uint32 bodyPart, uint32, byte8 ** motionArchives, byte8 *** modelDataFunctions, PhysicsMetadata ** modelPhysicsMetadataPool, float32 * motionSpeed, void *", "0, true, true, 0, 0, 0, 0, 5", "" ],
	[ 0x5A290 , "void"   , "byte8 * body, uint32 group, uint32 index, uint16, uint8, uint8"    , "0, true, true, 0, 0, 0, 0, 2", "Play Motion"                         ],

	[ 0x8AC80 , "void"   , "ModelData & modelData, uint32 bodyPart, byte8 * motionFile, uint32, bool"    , "0, true, true, 0, 0, 0, 0, 1", "Play Motion"                         ],
	[ 0x1EFB90, "void", "byte8 * actorData, uint32 group, uint32 index, float32, int8, uint8, uint8", "0, true, true, 0, 0, 0, 0, 3", "Play motion and update state." ],




/*
dmc3.exe+1E666D - 48 8B CB              - mov rcx,rbx
dmc3.exe+1E6670 - E8 5BA3FFFF           - call dmc3.exe+1E09D0

*/




	[ 0x1DFDA0, "void", "byte8 *, uint32, uint8, float32, float32, uint8", "0, true, true, 0, 0, 0, 0, 2", "Drop1" ],

	[ 0x1FB300, "void", "byte8 * actorData, uint32 direction, float32 value", "", "Adjust Position" ],






	[ 0x1E09D0, "void", "byte8 * actorBaseAddr, uint32 event", "", "" ],


/*
dmc3.exe+16CE66 - E8 A5830000           - call dmc3.exe+175210 { drop grenade
 }

*/


	[ 0x175210, "byte8 *", "vec4 *, vec4 *, __m128", "0, true, false, 0, 0, 0, 0, 0, false, true", "Boss Lady Grenade" ],













	[ 0x1E0800, "void", "byte8 * actorData, uint32 index, uint32, uint32", "", "Trigger Attack" ],




	[ 0x211100, "void", "byte8 * actorData", "", "Rebellion Combo 1 Part 3" ],



	[ 0x1F01F0, "void", "byte8 * actorData, uint32 index", "", "Reset State" ],




	




[ 0x2F74E0 , "void"   , "byte8 * dest, uint32 index"    , "", "Show Model Partition"                         ],
[ 0x2F7350 , "void"   , "byte8 * dest, uint32 index"    , "", "Hide Model Partition"                         ],






[ 0x32BE20, "void", "byte8 * dest"                                       , "", "Init Track" ],
[ 0x32BA90, "void", "byte8 * dest, const char * filename, uint32, uint32", "", "Set Track"  ],

















[ 0x8A520, "byte8 *", "ModelData & modelData", "0, true, false", "" ],



[ 0x30E630, "void", "byte8 * dest, uint32 index", "", "" ],









];

let filename = "../Mary/Internal.ixx"

let file = fs.readFileSync(filename, "utf8");

let lines = file.match(/[\S\s]*?\r\n/g);

if
(
	!Tag_Init
	(
		lines,
		/\/\/ \$DataStart$/,
		/\/\/ \$DataEnd$/
	)
)
{
	console.log("Tag_Init failed.");

	return;
}

Tag_CopyUntil(lines);



for (let index = 0; index < items.length; index++)
{
	let off                = items[index][0];
	let returnType         = items[index][1];
	let args               = items[index][2];
	let createFunctionArgs = items[index][3];
	let hint               = items[index][4];
	
	let offStr = off.toString(16).toUpperCase();
	
	c_typedefs += "export typedef " + returnType + "(__fastcall * func_" + offStr + "_t)(" + args + ");";
	if (hint != "")
	{
		c_typedefs += " // " + hint;
	}
	c_typedefs += "" + NEW_LINE;

	c_vars += "export func_" + offStr + "_t func_" + offStr + " = 0; // (" + args + ")" + NEW_LINE;
	
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



Tag_CopyAfter(lines);

fs.writeFileSync(filename, c);
