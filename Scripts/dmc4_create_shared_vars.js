var lz = function(n)
{
	var str = "";
	if (n < 1000)
	{
		str = "0";
	}
	if (n < 100)
	{
		str = "00";
	}
	if (n < 10)
	{
		str = "000";
	}
	return str + n;
}

var root = []; // pos, size, description

function FeedMissionData()
{
	var games =
	[
		"Dante Nero",
		"Vergil",
		"Trish Lady",
	];
	var modes =
	[
		"Human",
		"Devil Hunter",
		"Son of Sparda",
		"Dante Must Die",
		"Legendary Dark Knight",
		"Heaven or Hell",
		"Hell and Hell",
	];
	var pos  = 0xB4;
	var size = 4;
	for (var game = 0; game < games.length; game++)
	{
	for (var mode = 0; mode < modes.length; mode++)
	{
		var description = games[game] + " Selected Mission " + modes[mode];
		root.push([pos, size, description]);
		pos += size;
	}
	{
		var description = games[game] + " Selected Mode";
		root.push([pos, size, description]);
		pos += size;
	}
	for (var mode = 0; mode < modes.length; mode++)
	{
		var description = games[game] + " Highest Unlocked Mission " + modes[mode];
		root.push([pos, size, description]);
		pos += size;
	}
	}
}

// @Todo: Add hex boolean.

function FeedDanteData()
{
	var items =
	[
		[ "Enable Devil Trigger"         , 1 ],
		[ "Enable Air Hike"              , 1 ],
		[ "Enable Enemy Step"            , 1 ],
		[ "Enable Speed"                 , 1 ],
		[ "Enable Get More Orbs"         , 1 ],
		[ "Enable Trigger Heart"         , 1 ],
		[ "Unknown / Padding"            , 1 ],
		[ "Unknown / Padding"            , 1 ],
		[ "Melee Weapon"                 , 4 ],
		[ "Ranged Weapon"                , 4 ],
		[ "Bought Skills Count"          , 4 ],
		[ "Proud Souls"                  , 4 ],
		[ "Expertise 1"                  , 4 ],
		[ "Expertise 2"                  , 4 ],
		[ "Expertise 3"                  , 4 ],
		[ "Expertise 4"                  , 4 ],
		[ "Unknown / Padding"            , 4 ],
		[ "Unknown / Padding"            , 4 ],
		[ "Unknown / Padding"            , 4 ],
		[ "Unknown / Padding"            , 4 ],
		[ "Costume"                      , 4 ],
		[ "Unlock Costume 1"             , 1 ],
		[ "Unlock Costume 2"             , 1 ],
		[ "Unlock Costume 3"             , 1 ],
		[ "Unlock Costume 4"             , 1 ],
		[ "Enable Flush"                 , 1 ],
		[ "Enable Enemy Dash"            , 1 ],
		[ "Enable Flipper"               , 1 ],
		[ "Enable Trickster"             , 1 ],
		[ "Enable Royalguard"            , 1 ],
		[ "Enable Gunslinger"            , 1 ],
		[ "Enable Swordmaster"           , 1 ],
		[ "Enable Dark Slayer"           , 1 ],
		[ "Enable Gilgamesh"             , 1 ],
		[ "Enable Pandora"               , 1 ],
		[ "Enable Lucifer"               , 1 ],
		[ "Unknown / Padding"            , 1 ],
		[ "Trickster Level"              , 4 ],
		[ "Royalguard Level"             , 4 ],
		[ "Gunslinger Level"             , 4 ],
		[ "Swordmaster Level"            , 4 ],
		[ "Active Style"                 , 4 ],
		[ "Gamepad Taunt"                , 4 ],
		[ "Gamepad Melee Attack"         , 4 ],
		[ "Gamepad Ranged Attack"        , 4 ],
		[ "Gamepad Jump"                 , 4 ],
		[ "Gamepad Lock-On"              , 4 ],
		[ "Gamepad Not Used"             , 4 ],
		[ "Gamepad Not Used"             , 4 ],
		[ "Gamepad Style"                , 4 ],
		[ "Gamepad Up"                   , 4 ],
		[ "Gamepad Left"                 , 4 ],
		[ "Gamepad Right"                , 4 ],
		[ "Gamepad Down"                 , 4 ],
		[ "Gamepad Devil Trigger"        , 4 ],
		[ "Gamepad Change Ranged Weapon" , 4 ],
		[ "Gamepad Change Melee Weapon"  , 4 ],
		[ "Gamepad Change Target"        , 4 ],
		[ "Gamepad Reset Camera"         , 4 ],
		[ "Keyboard Taunt"               , 4 ],
		[ "Keyboard Melee Attack"        , 4 ],
		[ "Keyboard Ranged Attack"       , 4 ],
		[ "Keyboard Jump"                , 4 ],
		[ "Keyboard Lock-On"             , 4 ],
		[ "Keyboard Not Used"            , 4 ],
		[ "Keyboard Not Used"            , 4 ],
		[ "Keyboard Style"               , 4 ],
		[ "Keyboard Up"                  , 4 ],
		[ "Keyboard Left"                , 4 ],
		[ "Keyboard Right"               , 4 ],
		[ "Keyboard Down"                , 4 ],
		[ "Keyboard Devil Trigger"       , 4 ],
		[ "Keyboard Change Ranged Weapon", 4 ],
		[ "Keyboard Change Melee Weapon" , 4 ],
		[ "Keyboard Move Up"             , 4 ],
		[ "Keyboard Move Down"           , 4 ],
		[ "Keyboard Move Left"           , 4 ],
		[ "Keyboard Move Right"          , 4 ],
		[ "Keyboard Up"                  , 4 ],
		[ "Keyboard Down"                , 4 ],
		[ "Keyboard Left"                , 4 ],
		[ "Keyboard Right"               , 4 ],
		[ "Keyboard Change Target"       , 4 ],
		[ "Keyboard Reset Camera"        , 4 ],
	];
	var pos = 0x168;
	for (var item = 0; item < items.length; item++)
	{
		var description = "Dante " + items[item][0];
		var size        = items[item][1];
		root.push([pos, size, description]);
		pos += size;
	}
}

function FeedNeroData()
{
	var items =
	[
		[ "Enable Devil Trigger"          , 1 ],
		[ "Enable Air Hike"               , 1 ],
		[ "Enable Enemy Step"             , 1 ],
		[ "Enable Speed"                  , 1 ],
		[ "Enable Get More Orbs"          , 1 ],
		[ "Enable Trigger Heart"          , 1 ],
		[ "Unknown / Padding"             , 1 ],
		[ "Unknown / Padding"             , 1 ],
		[ "Melee Weapon"                  , 4 ],
		[ "Ranged Weapon"                 , 4 ],
		[ "Bought Skills Count"           , 4 ],
		[ "Proud Souls"                   , 4 ],
		[ "Expertise 1"                   , 4 ],
		[ "Expertise 2"                   , 4 ],
		[ "Expertise 3"                   , 4 ],
		[ "Expertise 4"                   , 4 ],
		[ "Unknown / Padding"             , 4 ],
		[ "Unknown / Padding"             , 4 ],
		[ "Unknown / Padding"             , 4 ],
		[ "Unknown / Padding"             , 4 ],
		[ "Costume"                       , 4 ],
		[ "Unlock Costume 1"              , 1 ],
		[ "Unlock Costume 2"              , 1 ],
		[ "Unlock Costume 3"              , 1 ],
		[ "Unlock Costume 4"              , 1 ],
		[ "Enable Table Hopper"           , 1 ],
		[ "Not Used"                      , 1 ],
		[ "Not Used"                      , 1 ],
		[ "Enable Max-Act"                , 1 ],
		[ "Snatch Level"                  , 1 ],
		[ "Additional Exceeds Count"      , 1 ],
		[ "Additional Table Hoppers Count", 1 ],
		[ "Not Used / Padding"            , 1 ],
		[ "Gamepad Taunt"                 , 4 ],
		[ "Gamepad Melee Attack"          , 4 ],
		[ "Gamepad Ranged Attack"         , 4 ],
		[ "Gamepad Jump"                  , 4 ],
		[ "Gamepad Lock-On"               , 4 ],
		[ "Gamepad Devil Bringer"         , 4 ],
		[ "Gamepad Exceed"                , 4 ],
		[ "Gamepad Not Used"              , 4 ],
		[ "Gamepad Not Used"              , 4 ],
		[ "Gamepad Not Used"              , 4 ],
		[ "Gamepad Not Used"              , 4 ],
		[ "Gamepad Not Used"              , 4 ],
		[ "Gamepad Devil Trigger"         , 4 ],
		[ "Gamepad Not Used"              , 4 ],
		[ "Gamepad Not Used"              , 4 ],
		[ "Gamepad Change Target"         , 4 ],
		[ "Gamepad Reset Camera"          , 4 ],
		[ "Keyboard Taunt"                , 4 ],
		[ "Keyboard Melee Attack"         , 4 ],
		[ "Keyboard Ranged Attack"        , 4 ],
		[ "Keyboard Jump"                 , 4 ],
		[ "Keyboard Lock-On"              , 4 ],
		[ "Keyboard Devil Bringer"        , 4 ],
		[ "Keyboard Exceed"               , 4 ],
		[ "Keyboard Not Used"             , 4 ],
		[ "Keyboard Not Used"             , 4 ],
		[ "Keyboard Not Used"             , 4 ],
		[ "Keyboard Not Used"             , 4 ],
		[ "Keyboard Not Used"             , 4 ],
		[ "Keyboard Devil Trigger"        , 4 ],
		[ "Keyboard Not Used"             , 4 ],
		[ "Keyboard Not Used"             , 4 ],
		[ "Keyboard Move Up"              , 4 ],
		[ "Keyboard Move Down"            , 4 ],
		[ "Keyboard Move Left"            , 4 ],
		[ "Keyboard Move Right"           , 4 ],
		[ "Keyboard Up"                   , 4 ],
		[ "Keyboard Down"                 , 4 ],
		[ "Keyboard Left"                 , 4 ],
		[ "Keyboard Right"                , 4 ],
		[ "Keyboard Change Target"        , 4 ],
		[ "Keyboard Reset Camera"         , 4 ],
	];
	var pos = 0x270;
	for (var item = 0; item < items.length; item++)
	{
		var description = "Nero " + items[item][0];
		var size        = items[item][1];
		root.push([pos, size, description]);
		pos += size;
	}
}

function FeedVergilData()
{
	var items =
	[
		[ "Enable Devil Trigger"                , 1 ],
		[ "Not Used"                            , 1 ],
		[ "Enable Enemy Step"                   , 1 ],
		[ "Enable Speed"                        , 1 ],
		[ "Enable Get More Orbs"                , 1 ],
		[ "Enable Trigger Heart"                , 1 ],
		[ "Unknown / Padding"                   , 1 ],
		[ "Unknown / Padding"                   , 1 ],
		[ "Melee Weapon"                        , 4 ],
		[ "Ranged Weapon"                       , 4 ],
		[ "Bought Skills Count"                 , 4 ],
		[ "Proud Souls"                         , 4 ],
		[ "Expertise 1"                         , 4 ],
		[ "Expertise 2"                         , 4 ],
		[ "Expertise 3"                         , 4 ],
		[ "Expertise 4"                         , 4 ],
		[ "Unknown / Padding"                   , 4 ],
		[ "Unknown / Padding"                   , 4 ],
		[ "Unknown / Padding"                   , 4 ],
		[ "Unknown / Padding"                   , 4 ],
		[ "Costume"                             , 4 ],
		[ "Unlock Costume 1"                    , 1 ],
		[ "Unlock Costume 2"                    , 1 ],
		[ "Unlock Costume 3"                    , 1 ],
		[ "Unlock Costume 4"                    , 1 ],
		[ "Enable Flush"                        , 1 ],
		[ "Enable Million Stab"                 , 1 ],
		[ "Summoned Swords Level"               , 1 ],
		[ "Unknown / Padding"                   , 1 ],
		[ "Unknown / Padding"                   , 4 ],
		[ "Unknown / Padding"                   , 4 ],
		[ "Unknown / Padding"                   , 4 ],
		[ "Unknown / Padding"                   , 4 ],
		[ "Gamepad Taunt"                       , 4 ],
		[ "Gamepad Melee Attack"                , 4 ],
		[ "Gamepad Ranged Attack"               , 4 ],
		[ "Gamepad Jump"                        , 4 ],
		[ "Gamepad Lock-On"                     , 4 ],
		[ "Gamepad Not Used"                    , 4 ],
		[ "Gamepad Not Used"                    , 4 ],
		[ "Gamepad Style"                       , 4 ],
		[ "Gamepad Not Used"                    , 4 ],
		[ "Gamepad Not Used"                    , 4 ],
		[ "Gamepad Not Used"                    , 4 ],
		[ "Gamepad Not Used"                    , 4 ],
		[ "Gamepad Devil Trigger"               , 4 ],
		[ "Gamepad Change Melee Weapon Back"    , 4 ],
		[ "Gamepad Change Melee Weapon Forward" , 4 ],
		[ "Gamepad Change Target"               , 4 ],
		[ "Gamepad Reset Camera"                , 4 ],
		[ "Keyboard Taunt"                      , 4 ],
		[ "Keyboard Melee Attack"               , 4 ],
		[ "Keyboard Ranged Attack"              , 4 ],
		[ "Keyboard Jump"                       , 4 ],
		[ "Keyboard Lock-On"                    , 4 ],
		[ "Keyboard Not Used"                   , 4 ],
		[ "Keyboard Not Used"                   , 4 ],
		[ "Keyboard Style"                      , 4 ],
		[ "Keyboard Not Used"                   , 4 ],
		[ "Keyboard Not Used"                   , 4 ],
		[ "Keyboard Not Used"                   , 4 ],
		[ "Keyboard Not Used"                   , 4 ],
		[ "Keyboard Devil Trigger"              , 4 ],
		[ "Keyboard Change Melee Weapon Back"   , 4 ],
		[ "Keyboard Change Melee Weapon Forward", 4 ],
		[ "Keyboard Move Up"                    , 4 ],
		[ "Keyboard Move Down"                  , 4 ],
		[ "Keyboard Move Left"                  , 4 ],
		[ "Keyboard Move Right"                 , 4 ],
		[ "Keyboard Up"                         , 4 ],
		[ "Keyboard Down"                       , 4 ],
		[ "Keyboard Left"                       , 4 ],
		[ "Keyboard Right"                      , 4 ],
		[ "Keyboard Change Target"              , 4 ],
		[ "Keyboard Reset Camera"               , 4 ],
	];
	var pos = 0x360;
	for (var item = 0; item < items.length; item++)
	{
		var description = "Vergil " + items[item][0];
		var size        = items[item][1];
		root.push([pos, size, description]);
		pos += size;
	}
}

function FeedTrishData()
{
	var items =
	[
		[ "Enable Devil Trigger"  , 1 ],
		[ "Enable Air Hike"       , 1 ],
		[ "Enable Enemy Step"     , 1 ],
		[ "Enable Speed"          , 1 ],
		[ "Enable Get More Orbs"  , 1 ],
		[ "Enable Trigger Heart"  , 1 ],
		[ "Unknown / Padding"     , 1 ],
		[ "Unknown / Padding"     , 1 ],
		[ "Melee Weapon"          , 4 ],
		[ "Ranged Weapon"         , 4 ],
		[ "Bought Skills Count"   , 4 ],
		[ "Proud Souls"           , 4 ],
		[ "Expertise 1"           , 4 ],
		[ "Expertise 2"           , 4 ],
		[ "Expertise 3"           , 4 ],
		[ "Expertise 4"           , 4 ],
		[ "Unknown / Padding"     , 4 ],
		[ "Unknown / Padding"     , 4 ],
		[ "Unknown / Padding"     , 4 ],
		[ "Unknown / Padding"     , 4 ],
		[ "Costume"               , 4 ],
		[ "Unlock Costume 1"      , 1 ],
		[ "Unlock Costume 2"      , 1 ],
		[ "Unlock Costume 3"      , 1 ],
		[ "Unlock Costume 4"      , 1 ],
		[ "Enable Spark"          , 1 ],
		[ "Unknown / Padding"     , 1 ],
		[ "Unknown / Padding"     , 1 ],
		[ "Unknown / Padding"     , 1 ],
		[ "Unknown / Padding"     , 1 ],
		[ "Unknown / Padding"     , 1 ],
		[ "Unknown / Padding"     , 1 ],
		[ "Unknown / Padding"     , 1 ],
		[ "Unknown / Padding"     , 1 ],
		[ "Unknown / Padding"     , 1 ],
		[ "Unknown / Padding"     , 1 ],
		[ "Gamepad Taunt"         , 4 ],
		[ "Gamepad Melee Attack"  , 4 ],
		[ "Gamepad Ranged Attack" , 4 ],
		[ "Gamepad Jump"          , 4 ],
		[ "Gamepad Lock-On"       , 4 ],
		[ "Gamepad Not Used"      , 4 ],
		[ "Gamepad Not Used"      , 4 ],
		[ "Gamepad Sparda"        , 4 ],
		[ "Gamepad Not Used"      , 4 ],
		[ "Gamepad Not Used"      , 4 ],
		[ "Gamepad Not Used"      , 4 ],
		[ "Gamepad Not Used"      , 4 ],
		[ "Gamepad Devil Trigger" , 4 ],
		[ "Gamepad Not Used"      , 4 ],
		[ "Gamepad Not Used"      , 4 ],
		[ "Gamepad Change Target" , 4 ],
		[ "Gamepad Reset Camera"  , 4 ],
		[ "Keyboard Taunt"        , 4 ],
		[ "Keyboard Melee Attack" , 4 ],
		[ "Keyboard Ranged Attack", 4 ],
		[ "Keyboard Jump"         , 4 ],
		[ "Keyboard Lock-On"      , 4 ],
		[ "Keyboard Sparda"       , 4 ],
		[ "Keyboard Not Used"     , 4 ],
		[ "Keyboard Not Used"     , 4 ],
		[ "Keyboard Not Used"     , 4 ],
		[ "Keyboard Not Used"     , 4 ],
		[ "Keyboard Not Used"     , 4 ],
		[ "Keyboard Not Used"     , 4 ],
		[ "Keyboard Devil Trigger", 4 ],
		[ "Keyboard Not Used"     , 4 ],
		[ "Keyboard Not Used"     , 4 ],
		[ "Keyboard Move Up"      , 4 ],
		[ "Keyboard Move Down"    , 4 ],
		[ "Keyboard Move Left"    , 4 ],
		[ "Keyboard Move Right"   , 4 ],
		[ "Keyboard Up"           , 4 ],
		[ "Keyboard Down"         , 4 ],
		[ "Keyboard Left"         , 4 ],
		[ "Keyboard Right"        , 4 ],
		[ "Keyboard Change Target", 4 ],
		[ "Keyboard Reset Camera" , 4 ],
	];
	var pos = 0x45C;
	for (var item = 0; item < items.length; item++)
	{
		var description = "Trish " + items[item][0];
		var size        = items[item][1];
		root.push([pos, size, description]);
		pos += size;
	}
}

function FeedLadyData()
{
	var items =
	[
		[ "Enable Burst Attack"                  , 1 ],
		[ "Enable Blaster"                       , 1 ],
		[ "Enable Enemy Step"                    , 1 ],
		[ "Enable Speed"                         , 1 ],
		[ "Enable Get More Orbs"                 , 1 ],
		[ "Unknown / Padding"                    , 1 ],
		[ "Unknown / Padding"                    , 1 ],
		[ "Unknown / Padding"                    , 1 ],
		[ "Melee Weapon"                         , 4 ],
		[ "Ranged Weapon"                        , 4 ],
		[ "Bought Skills Count"                  , 4 ],
		[ "Proud Souls"                          , 4 ],
		[ "Expertise 1"                          , 4 ],
		[ "Expertise 2"                          , 4 ],
		[ "Expertise 3"                          , 4 ],
		[ "Expertise 4"                          , 4 ],
		[ "Unknown / Padding"                    , 4 ],
		[ "Unknown / Padding"                    , 4 ],
		[ "Unknown / Padding"                    , 4 ],
		[ "Unknown / Padding"                    , 4 ],
		[ "Costume"                              , 4 ],
		[ "Unlock Costume 1"                     , 1 ],
		[ "Unlock Costume 2"                     , 1 ],
		[ "Unlock Costume 3"                     , 1 ],
		[ "Unlock Costume 4"                     , 1 ],
		[ "Unknown / Padding"                    , 4 ],
		[ "Unknown / Padding"                    , 4 ],
		[ "Unknown / Padding"                    , 4 ],
		[ "Unknown / Padding"                    , 4 ],
		[ "Gamepad Taunt"                        , 4 ],
		[ "Gamepad Melee Attack"                 , 4 ],
		[ "Gamepad Ranged Attack"                , 4 ],
		[ "Gamepad Jump"                         , 4 ],
		[ "Gamepad Lock-On"                      , 4 ],
		[ "Gamepad Grapple"                      , 4 ],
		[ "Gamepad Not Used"                     , 4 ],
		[ "Gamepad Not Used"                     , 4 ],
		[ "Gamepad Not Used"                     , 4 ],
		[ "Gamepad Not Used"                     , 4 ],
		[ "Gamepad Not Used"                     , 4 ],
		[ "Gamepad Not Used"                     , 4 ],
		[ "Gamepad Burst Attack"                 , 4 ],
		[ "Gamepad Change Ranged Weapon Back"    , 4 ],
		[ "Gamepad Change Ranged Weapon Forward" , 4 ],
		[ "Gamepad Change Target"                , 4 ],
		[ "Gamepad Reset Camera"                 , 4 ],
		[ "Keyboard Taunt"                       , 4 ],
		[ "Keyboard Kalina Ann Bayonet"          , 4 ],
		[ "Keyboard Ranged Attack"               , 4 ],
		[ "Keyboard Jump"                        , 4 ],
		[ "Keyboard Lock-On"                     , 4 ],
		[ "Keyboard Not Used"                    , 4 ],
		[ "Keyboard Not Used"                    , 4 ],
		[ "Keyboard Grapple"                     , 4 ],
		[ "Keyboard Not Used"                    , 4 ],
		[ "Keyboard Not Used"                    , 4 ],
		[ "Keyboard Not Used"                    , 4 ],
		[ "Keyboard Not Used"                    , 4 ],
		[ "Keyboard Burst Attack"                , 4 ],
		[ "Keyboard Change Ranged Weapon Back"   , 4 ],
		[ "Keyboard Change Ranged Weapon Forward", 4 ],
		[ "Keyboard Move Up"                     , 4 ],
		[ "Keyboard Move Down"                   , 4 ],
		[ "Keyboard Move Left"                   , 4 ],
		[ "Keyboard Right"                       , 4 ],
		[ "Keyboard Up"                          , 4 ],
		[ "Keyboard Down"                        , 4 ],
		[ "Keyboard Left"                        , 4 ],
		[ "Keyboard Right"                       , 4 ],
		[ "Keyboard Change Target"               , 4 ],
		[ "Keyboard Reset Camera"                , 4 ],
	];
	var pos = 0x564;
	for (var item = 0; item < items.length; item++)
	{
		var description = "Lady " + items[item][0];
		var size        = items[item][1];
		root.push([pos, size, description]);
		pos += size;
	}
}

FeedMissionData();
FeedDanteData();
FeedNeroData();
FeedVergilData();
FeedTrishData();
FeedLadyData();

var c = "";

c += "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
c += "<CheatTable>\n";
c += "<CheatEntries>\n";

var pos = 0;
var id  = 0;

for (var index = 0; index < 500; index++)
{
	var skip = false;
	for (var rootIndex = 0; rootIndex < root.length; rootIndex++)
	{
		var offset      = root[rootIndex][0];
		var size        = root[rootIndex][1];
		var description = root[rootIndex][2];
		if (pos == offset)
		{
			c += "<CheatEntry>\n";
			c += "<Description>\"" + lz(id) + " " + description + "\"</Description>\n";
			c += "<VariableType>";
			if (size == 1)
			{
				c += "Byte";
			}
			else if (size == 2)
			{
				c += "4 Bytes";
			}
			else if (size == 4)
			{
				c += "4 Bytes";
			}
			else if (size == 5)
			{
				c += "Float";
			}
			c += "</VariableType>\n";
			c += "<Address>dmc4.exe+F59F10</Address>\n";
			c += "<Offsets>\n";
			c += "<Offset>" + offset.toString(16).toUpperCase() + "</Offset>\n";
			c += "</Offsets>\n";
			c += "</CheatEntry>\n";
			pos += size;
			id++;
			skip = true;
			break;
		}
	}
	if (skip)
	{
		continue;
	}
	if (pos % 4)
	{
		pos++;
		index--;
		continue;
	}
	c += "<CheatEntry>\n";
	c += "<Description>\"" + lz(id) + "\"</Description>\n";
	c += "<VariableType>4 Bytes</VariableType>\n";
	c += "<Address>dmc4.exe+F59F10</Address>\n";
	c += "<Offsets>\n";
	c += "<Offset>" + pos.toString(16).toUpperCase() + "</Offset>\n";
	c += "</Offsets>\n";
	c += "</CheatEntry>\n";
	pos++;
	id++;
}

c += "</CheatEntries>\n";
c += "</CheatTable>\n";

document.body.innerHTML = "<plaintext>" + c;
