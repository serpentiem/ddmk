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



let location = "../Mary/Config.ixx";

let file = fs.readFileSync(location, "utf8");



let tagName = "GetData";



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
	"Default",
	"Active",
	"Queued",
	"",
];



// PlayerData
{

for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
{
	let item = items[itemIndex];

	c += Tabs() + "export PlayerData & Get" + item + "PlayerData(uint8 playerIndex)" + NEW_LINE;

	ScopeStart();

	if (item == "")
	{
		c += Tabs() + "return GetActivePlayerData(playerIndex);" + NEW_LINE;
	}
	else
	{
		c += Tabs() + "return " + item.toLowerCase() + "Config.Actor.playerData[playerIndex];" + NEW_LINE;
	}

	ScopeEnd();

	c += NEW_LINE;
}

c += NEW_LINE;

for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
{
	let item = items[itemIndex];

	c += Tabs() + "export template <typename T>" + NEW_LINE;
	c += Tabs() + "PlayerData & Get" + item + "PlayerData(T & actorData)" + NEW_LINE;

	ScopeStart();

	if (item == "")
	{
		c += Tabs() + "return GetPlayerData(actorData.newPlayerIndex);" + NEW_LINE;
	}
	else
	{
		c += Tabs() + "return Get" + item + "PlayerData(actorData.newPlayerIndex);" + NEW_LINE;
	}

	ScopeEnd();

	c += NEW_LINE;
}

c += NEW_LINE;

}



// CharacterData
{

for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
{
	let item = items[itemIndex];

	c += Tabs() + "export CharacterData & Get" + item + "CharacterData" + NEW_LINE;

	ScopeStart("(");

	c += Tabs() + "uint8 playerIndex," + NEW_LINE;
	c += Tabs() + "uint8 characterIndex," + NEW_LINE;
	c += Tabs() + "uint8 entityIndex" + NEW_LINE;

	ScopeEnd(")");

	ScopeStart();

	c += Tabs() + "auto & playerData = Get" + item + "PlayerData(playerIndex);" + NEW_LINE;
	c += NEW_LINE;
	c += Tabs() + "return playerData.characterData[characterIndex][entityIndex];" + NEW_LINE;

	ScopeEnd();

	c += NEW_LINE;
}

c += NEW_LINE;

for (let itemIndex = 0; itemIndex < items.length; itemIndex++)
{
	let item = items[itemIndex];

	c += Tabs() + "export template <typename T>" + NEW_LINE;
	c += Tabs() + "CharacterData & Get" + item + "CharacterData(T & actorData)" + NEW_LINE;

	ScopeStart();

	c += Tabs() + "return Get" + item + "CharacterData" + NEW_LINE;

	ScopeStart("(");

	c += Tabs() + "actorData.newPlayerIndex," + NEW_LINE;
	c += Tabs() + "actorData.newCharacterIndex," + NEW_LINE;
	c += Tabs() + "actorData.newEntityIndex" + NEW_LINE;

	ScopeEnd
	(
		")",
		ScopeFlags_Semicolon
	);

	ScopeEnd();

	c += NEW_LINE;
}

}



CleanStream();

c_new = c;

ClearAll();



file = c_until + c_new + c_after;



fs.writeFileSync(location, file);
