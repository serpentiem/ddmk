// #region

ClearAll();

let location = "Mary/Config.ixx";

file = fs.readFileSync(location, "utf8");

let tagName = "GetData";

// #endregion



FeedStart(tagName);



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

FeedEnd();



fs.writeFileSync(location, file);
