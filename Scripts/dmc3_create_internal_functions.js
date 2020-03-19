var c = "";

var items =
[
	[ 0x897B0 , "void"   , "byte8 * dest"                                                             , ""                             ],
	[ 0x89450 , "void"   , "byte8 * dest"                                                             , ""                             ],
	[ 0x89270 , "void"   , "byte8 * dest"                                                             , ""                             ],
	[ 0x8B470 , "void"   , "byte8 * dest, uint32 flag"                                                , ""                             ],
	[ 0x89960 , "void"   , "byte8 * dest, byte8 * modelFile, byte8 * textureFile"                     , ""                             ],
	[ 0x89DE0 , "byte8 *", "byte8 * dest"                                                             , "0, true, false"               ],
	[ 0x8BC60 , "void"   , "byte8 * dest, byte8 * addr, byte8 * shadowFile"                           , ""                             ],
	[ 0x305D80, "void"   , "byte8 * dest"                                                             , ""                             ],
	[ 0x8A000 , "void"   , "byte8 * dest, byte8 * motionFile, byte8 * addr"                           , ""                             ],
	[ 0x2C9F40, "uint32" , "byte8 * physicsFile"                                                      , "0, true, false"               ],
	[ 0x2CA1D0, "void"   , "byte8 * dest, byte8 * addr, byte8 * physicsFile, uint32 index"            , ""                             ],
	[ 0x2CA2F0, "void"   , "byte8 * dest, byte8 * addr, byte8 *, MODEL_DATA * modelData, uint32 count", "0, true, true, 0, 0, 0, 0, 1" ],
	[ 0x1EF040, "void"   , "byte8 * baseAddr, uint32 index"                                           , ""                             ],
	[ 0x1F92C0, "void"   , "byte8 * dest, byte32 flag"                                                , ""                             ],
	[ 0x1F97F0, "void"   , "byte8 * dest, byte32 flag"                                                , ""                             ],
	[ 0x2EE3D0, "void"   , "byte8 * dest"                                                             , ""                             ],
	[ 0x1FAF40, "void"   , "byte8 * baseAddr"                                                         , ""                             ],
	[ 0x1EEF80, "void"   , "byte8 * baseAddr"                                                         , ""                             ],
	[ 0x2EE060, "bool"   , "byte8 * dest, uint32 size"                                                , ""                             ],
	[ 0x1DE820, "byte8 *", "uint32 character, uint32 actor, bool isClone"                             , "0, true, false"               ],
	[ 0x1BB390, "void"   , "byte8 ** pool, uint32 actor"                                              , ""                             ],
	[ 0x217B90, "void"   , "byte8 * baseAddr, byte8 * sessionData"                                    , ""                             ],
	[ 0x223CB0, "void"   , "byte8 * baseAddr, byte8 * sessionData"                                    , ""                             ],
	[ 0x1DFC20, "void"   , "byte8 * baseAddr"                                                         , ""                             ],
	[ 0x2310B0, "byte8 *", "byte8 * baseAddr, uint32 id"                                              , "0, true, false"               ],
	[ 0x22EC90, "byte8 *", "byte8 * baseAddr, uint32 id"                                              , "0, true, false"               ],
	[ 0x227870, "byte8 *", "byte8 * baseAddr, uint32 id"                                              , "0, true, false"               ],
	[ 0x22A1E0, "byte8 *", "byte8 * baseAddr, uint32 id"                                              , "0, true, false"               ],
	[ 0x228CF0, "byte8 *", "byte8 * baseAddr, uint32 id"                                              , "0, true, false"               ],
	[ 0x22B0C0, "byte8 *", "byte8 * baseAddr, uint32 id"                                              , "0, true, false"               ],
	[ 0x2306B0, "byte8 *", "byte8 * baseAddr, uint32 id"                                              , "0, true, false"               ],
	[ 0x22C4A0, "byte8 *", "byte8 * baseAddr, uint32 id"                                              , "0, true, false"               ],
	[ 0x2300A0, "byte8 *", "byte8 * baseAddr, uint32 id"                                              , "0, true, false"               ],
	[ 0x22BA30, "byte8 *", "byte8 * baseAddr, uint32 id"                                              , "0, true, false"               ],
	[ 0x22D960, "byte8 *", "byte8 * baseAddr, uint32 id"                                              , "0, true, false"               ],
	[ 0x2298E0, "byte8 *", "byte8 * baseAddr, uint32 id"                                              , "0, true, false"               ],
	[ 0x22CF00, "byte8 *", "byte8 * baseAddr, uint32 id"                                              , "0, true, false"               ],
	[ 0x23E560, "void"   , "byte8 * eventData, uint32 position"                                       , ""                             ],
];

for (var index = 0; index < items.length; index++)
{
	var off                = items[index][0];
	var returnType         = items[index][1];
	var args               = items[index][2];
	var createFunctionArgs = items[index][3];
	
	var offStr = off.toString(16).toUpperCase();
	
	c += "typedef " + returnType + "(__fastcall * func_" + offStr + "_t)(" + args + ");\n";
}

c += "\n";

for (var index = 0; index < items.length; index++)
{
	var off                = items[index][0];
	var returnType         = items[index][1];
	var args               = items[index][2];
	var createFunctionArgs = items[index][3];
	
	var offStr = off.toString(16).toUpperCase();
	
	c += "extern func_" + offStr + "_t func_" + offStr + ";\n";
}

c += "\n";

for (var index = 0; index < items.length; index++)
{
	var off                = items[index][0];
	var returnType         = items[index][1];
	var args               = items[index][2];
	var createFunctionArgs = items[index][3];
	
	var offStr = off.toString(16).toUpperCase();
	
	c += "func_" + offStr + "_t func_" + offStr + " = 0;\n";
}

c += "\n";

for (var index = 0; index < items.length; index++)
{
	var off                = items[index][0];
	var returnType         = items[index][1];
	var args               = items[index][2];
	var createFunctionArgs = items[index][3];
	
	var offStr = off.toString(16).toUpperCase();
	
	c += "{\n";
	c += "\tauto func = CreateFunction((appBaseAddr + 0x" + offStr + ")";
	if (createFunctionArgs != "")
	{
		c += ", " + createFunctionArgs;
	}
	c += ");\n";
	c += "\tfunc_" + offStr + " = (func_" + offStr + "_t)func.addr;\n";
	c += "}\n";
}

document.body.innerHTML = "<plaintext>" + c;
