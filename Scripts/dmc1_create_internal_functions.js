

// @Todo: Use reinterpret_cast please.



let fs = require("fs");
let vm = require("vm");

vm.runInThisContext(fs.readFileSync("core.js", "utf8"));

ClearAll();



let c_typedefs = "";
let c_vars = "";
let c_init = "";

let items =
[
	[ 0x2C99C0, "void", "uint32 meleeWeapon, uint32 playAuraEffect", "", "Update Melee Weapon"      ],
	[ 0x2C4A00, "void", "uint32 meleeWeaponForm"                   , "", "Update Melee Weapon Form" ],
	[ 0x2C4C50, "void", "uint32 rangedWeapon"                      , "", "Update Ranged Weapon"     ],
	[ 0x3C8DC0, "void", ""                                         , "", "Update Weapons"           ],


	[ 0x2F0610, "void", "PlayerActorData & actorData", "", "Charge Update"           ],





];

let filename = "../Eva/Internal.ixx"

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
