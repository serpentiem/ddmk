var fs = require("fs");

eval(fs.readFileSync("dmc3_core.js", "utf8"));

var filename = "../Mary/Config.ixx"

var file = fs.readFileSync(filename, "utf8");

var startTag = /\/\/ \$GetDataStart$/;
var endTag   = /\/\/ \$GetDataEnd$/;

var startTagLine = -1;
var endTagLine   = -1;

var obj = file.match(/[\S\s]*?\r\n/g);

for (var index = 0; index < obj.length; index++)
{
	var str = obj[index].substring(0, (obj[index].length - 2));
	if (str.match(startTag))
	{
		startTagLine = index;
		break;
	}
}

if (startTagLine == -1)
{
	console.log("Start tag not found.");
	return;
}

for (var index = 0; index < obj.length; index++)
{
	var str = obj[index].substring(0, (obj[index].length - 2));
	if (str.match(endTag))
	{
		endTagLine = index;
		break;
	}
}

if (endTagLine == -1)
{
	console.log("End tag not found.");
	return;
}

if (endTagLine < startTagLine)
{
	console.log("End tag appears before start tag.");
	return;
}

console.log("startTagLine " + (startTagLine + 1));
console.log("endTagLine   " + (endTagLine   + 1));

for (var index = 0; index <= startTagLine; index++)
{
	var str = obj[index].substring(0, (obj[index].length - 2));
	c += str + NEW_LINE;
}

c += NEW_LINE;



// Player Data

var items =
[
	"Default",
	"Active",
	"Queued",
	"",
];

for (var itemIndex = 0; itemIndex < items.length; itemIndex++)
{
	var item = items[itemIndex];

	c += "export PlayerData & Get" + item + "PlayerData(uint8 playerIndex)" + NEW_LINE;
	c += "{" + NEW_LINE;

	if (item == "")
	{
		c += "\treturn GetActivePlayerData(playerIndex);" + NEW_LINE;
	}
	else
	{
		c += "\treturn " + item.toLowerCase() + "Config.Actor.playerData[playerIndex];" + NEW_LINE;
	}
	
	c += "}" + NEW_LINE;

	if (itemIndex < (items.length - 1))
	{
		c += NEW_LINE;
	}
}

c += NEW_LINE;

for (var itemIndex = 0; itemIndex < items.length; itemIndex++)
{
	var item = items[itemIndex];

	c += "export template <typename T>" + NEW_LINE;
	c += "PlayerData & Get" + item + "PlayerData(T & actorData)" + NEW_LINE;
	c += "{" + NEW_LINE;

	if (item == "")
	{
		c += "\treturn GetPlayerData(actorData.newPlayerIndex);" + NEW_LINE;
	}
	else
	{
		c += "\treturn Get" + item + "PlayerData(actorData.newPlayerIndex);" + NEW_LINE;
	}

	c += "}" + NEW_LINE;

	if (itemIndex < (items.length - 1))
	{
		c += NEW_LINE;
	}
}

c += NEW_LINE;

// Character Data

for (var itemIndex = 0; itemIndex < items.length; itemIndex++)
{
	var item = items[itemIndex];

	c += "export CharacterData & Get" + item + "CharacterData" + NEW_LINE;
	c += "(" + NEW_LINE;
	c += "\tuint8 playerIndex," + NEW_LINE;
	c += "\tuint8 characterIndex," + NEW_LINE;
	c += "\tuint8 entityIndex" + NEW_LINE;
	c += ")" + NEW_LINE;
	c += "{" + NEW_LINE;
	c += "\tauto & playerData = Get" + item + "PlayerData(playerIndex);" + NEW_LINE;
	c += NEW_LINE;
	c += "\treturn playerData.characterData[characterIndex][entityIndex];" + NEW_LINE;
	c += "}" + NEW_LINE;

	if (itemIndex < (items.length - 1))
	{
		c += NEW_LINE;
	}
}

c += NEW_LINE;

for (var itemIndex = 0; itemIndex < items.length; itemIndex++)
{
	var item = items[itemIndex];

	c += "export template <typename T>" + NEW_LINE;
	c += "CharacterData & Get" + item + "CharacterData(T & actorData)" + NEW_LINE;
	c += "{" + NEW_LINE;
	c += "\treturn Get" + item + "CharacterData" + NEW_LINE;
	c += "\t(" + NEW_LINE;
	c += "\t\tactorData.newPlayerIndex," + NEW_LINE;
	c += "\t\tactorData.newCharacterIndex," + NEW_LINE;
	c += "\t\tactorData.newEntityIndex" + NEW_LINE;
	c += "\t);" + NEW_LINE;
	c += "}" + NEW_LINE;

	if (itemIndex < (items.length - 1))
	{
		c += NEW_LINE;
	}
}



c += NEW_LINE;

for (var index = endTagLine; index < obj.length; index++)
{
	var str = obj[index].substring(0, (obj[index].length - 2));
	c += str + NEW_LINE;
}

fs.writeFileSync(filename, c);
