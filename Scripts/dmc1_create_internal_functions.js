// #region

ClearAll();

let location = "Eva/Internal.ixx";

file = fs.readFileSync(location, "utf8");

let tagName = "Data";

// #endregion



FeedStart(tagName);



let items =
[
	[ 0x2C99C0, "void", "uint32 meleeWeapon, uint32 playAuraEffect", "", "Update Melee Weapon"      ],
	[ 0x2C4A00, "void", "uint32 meleeWeaponForm"                   , "", "Update Melee Weapon Form" ],
	[ 0x2C4C50, "void", "uint32 rangedWeapon"                      , "", "Update Ranged Weapon"     ],
	[ 0x3C8DC0, "void", ""                                         , "", "Update Weapons"           ],
	[ 0x2F0610, "void", "PlayerActorData & actorData", "", "Charge Update"           ],
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
		(StringFlags_Hex | StringFlags_NoPrefix)
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
		(StringFlags_Hex | StringFlags_NoPrefix)
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
		(StringFlags_Hex | StringFlags_NoPrefix)
	);



	ScopeStart();

	c += Tabs() + "auto func = old_CreateFunction((appBaseAddr + 0x" + offName + ")";

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

FeedEnd();



fs.writeFileSync(location, file);
