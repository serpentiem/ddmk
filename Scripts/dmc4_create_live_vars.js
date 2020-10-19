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

var c = "";

c += "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
c += "<CheatTable>\n";
c += "<CheatEntries>\n";

c += "<CheatEntry>\n";
c += "<Description>\"__LIVE__\"</Description>\n";
c += "<GroupHeader>1</GroupHeader>\n";
c += "<CheatEntries>\n";

function FeedDanteData()
{
	var items =
	[
		[ "Enable Devil Trigger"         , 1, true  ],
		[ "Enable Air Hike"              , 1, true  ],
		[ "Enable Enemy Step"            , 1, true  ],
		[ "Enable Speed"                 , 1, true  ],
		[ "Enable Get More Orbs"         , 1, true  ],
		[ "Enable Trigger Heart"         , 1, true  ],
		[ "Unknown / Padding"            , 1, true  ],
		[ "Unknown / Padding"            , 1, true  ],
		[ "Melee Weapon"                 , 4, false ],
		[ "Ranged Weapon"                , 4, false ],
		[ "Bought Skills Count"          , 4, false ],
		[ "Proud Souls"                  , 4, false ],
		[ "Expertise 1"                  , 4, true  ],
		[ "Expertise 2"                  , 4, true  ],
		[ "Expertise 3"                  , 4, true  ],
		[ "Expertise 4"                  , 4, true  ],
		[ "Unknown / Padding"            , 4, true  ],
		[ "Unknown / Padding"            , 4, true  ],
		[ "Unknown / Padding"            , 4, true  ],
		[ "Unknown / Padding"            , 4, true  ],
		[ "Costume"                      , 4, false ],
		[ "Unlock Costume 1"             , 1, true  ],
		[ "Unlock Costume 2"             , 1, true  ],
		[ "Unlock Costume 3"             , 1, true  ],
		[ "Unlock Costume 4"             , 1, true  ],
		[ "Enable Flush"                 , 1, true  ],
		[ "Enable Enemy Dash"            , 1, true  ],
		[ "Enable Flipper"               , 1, true  ],
		[ "Enable Trickster"             , 1, true  ],
		[ "Enable Royalguard"            , 1, true  ],
		[ "Enable Gunslinger"            , 1, true  ],
		[ "Enable Swordmaster"           , 1, true  ],
		[ "Enable Dark Slayer"           , 1, true  ],
		[ "Enable Gilgamesh"             , 1, true  ],
		[ "Enable Pandora"               , 1, true  ],
		[ "Enable Lucifer"               , 1, true  ],
		[ "Unknown / Padding"            , 1, true  ],
		[ "Trickster Level"              , 4, false ],
		[ "Royalguard Level"             , 4, false ],
		[ "Gunslinger Level"             , 4, false ],
		[ "Swordmaster Level"            , 4, false ],
		[ "Active Style"                 , 4, false ],
		[ "Gamepad Taunt"                , 4, true  ],
		[ "Gamepad Melee Attack"         , 4, true  ],
		[ "Gamepad Ranged Attack"        , 4, true  ],
		[ "Gamepad Jump"                 , 4, true  ],
		[ "Gamepad Lock-On"              , 4, true  ],
		[ "Gamepad Not Used"             , 4, true  ],
		[ "Gamepad Not Used"             , 4, true  ],
		[ "Gamepad Style"                , 4, true  ],
		[ "Gamepad Up"                   , 4, true  ],
		[ "Gamepad Left"                 , 4, true  ],
		[ "Gamepad Right"                , 4, true  ],
		[ "Gamepad Down"                 , 4, true  ],
		[ "Gamepad Devil Trigger"        , 4, true  ],
		[ "Gamepad Change Ranged Weapon" , 4, true  ],
		[ "Gamepad Change Melee Weapon"  , 4, true  ],
		[ "Gamepad Change Target"        , 4, true  ],
		[ "Gamepad Reset Camera"         , 4, true  ],
		[ "Keyboard Taunt"               , 4, true  ],
		[ "Keyboard Melee Attack"        , 4, true  ],
		[ "Keyboard Ranged Attack"       , 4, true  ],
		[ "Keyboard Jump"                , 4, true  ],
		[ "Keyboard Lock-On"             , 4, true  ],
		[ "Keyboard Not Used"            , 4, true  ],
		[ "Keyboard Not Used"            , 4, true  ],
		[ "Keyboard Style"               , 4, true  ],
		[ "Keyboard Up"                  , 4, true  ],
		[ "Keyboard Left"                , 4, true  ],
		[ "Keyboard Right"               , 4, true  ],
		[ "Keyboard Down"                , 4, true  ],
		[ "Keyboard Devil Trigger"       , 4, true  ],
		[ "Keyboard Change Ranged Weapon", 4, true  ],
		[ "Keyboard Change Melee Weapon" , 4, true  ],
		[ "Keyboard Move Up"             , 4, true  ],
		[ "Keyboard Move Down"           , 4, true  ],
		[ "Keyboard Move Left"           , 4, true  ],
		[ "Keyboard Move Right"          , 4, true  ],
		[ "Keyboard Up"                  , 4, true  ],
		[ "Keyboard Down"                , 4, true  ],
		[ "Keyboard Left"                , 4, true  ],
		[ "Keyboard Right"               , 4, true  ],
		[ "Keyboard Change Target"       , 4, true  ],
		[ "Keyboard Reset Camera"        , 4, true  ],
	];
	c += "<CheatEntry>\n";
	c += "<Description>\"Dante\"</Description>\n";
	c += "<Options moHideChildren=\"1\"/>\n";
	c += "<GroupHeader>1</GroupHeader>\n";
	c += "<CheatEntries>\n";
	var id  = 0;
	var pos = 0x4B8;
	for (var item = 0; item < items.length; item++)
	{
		var description = items[item][0];
		var size        = items[item][1];
		var hex         = items[item][2];
		c += "<CheatEntry>\n";
		c += "<Description>\"" + lz(id) + " " + description + "\"</Description>\n";
		if (hex)
		{
			c += "<ShowAsHex>1</ShowAsHex>\n";
		}
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
			size = 4;
		}
		c += "</VariableType>\n";
		c += "<Address>dmc4.exe+F59F00</Address>\n";
		c += "<Offsets>\n";
		c += "<Offset>" + pos.toString(16).toUpperCase() + "</Offset>\n";
		c += "</Offsets>\n";
		c += "</CheatEntry>\n";
		id++;
		pos += size;
	}
	c += "</CheatEntries>\n";
	c += "</CheatEntry>\n";
}

function FeedNeroData()
{
	var items =
	[
		[ "Enable Devil Trigger"          , 1, true  ],
		[ "Enable Air Hike"               , 1, true  ],
		[ "Enable Enemy Step"             , 1, true  ],
		[ "Enable Speed"                  , 1, true  ],
		[ "Enable Get More Orbs"          , 1, true  ],
		[ "Enable Trigger Heart"          , 1, true  ],
		[ "Unknown / Padding"             , 1, true  ],
		[ "Unknown / Padding"             , 1, true  ],
		[ "Melee Weapon"                  , 4, false ],
		[ "Ranged Weapon"                 , 4, false ],
		[ "Bought Skills Count"           , 4, false ],
		[ "Proud Souls"                   , 4, false ],
		[ "Expertise 1"                   , 4, true  ],
		[ "Expertise 2"                   , 4, true  ],
		[ "Expertise 3"                   , 4, true  ],
		[ "Expertise 4"                   , 4, true  ],
		[ "Unknown / Padding"             , 4, true  ],
		[ "Unknown / Padding"             , 4, true  ],
		[ "Unknown / Padding"             , 4, true  ],
		[ "Unknown / Padding"             , 4, true  ],
		[ "Costume"                       , 4, false ],
		[ "Unlock Costume 1"              , 1, true  ],
		[ "Unlock Costume 2"              , 1, true  ],
		[ "Unlock Costume 3"              , 1, true  ],
		[ "Unlock Costume 4"              , 1, true  ],
		[ "Enable Table Hopper"           , 1, true  ],
		[ "Not Used"                      , 1, true  ],
		[ "Not Used"                      , 1, true  ],
		[ "Enable Max-Act"                , 1, true  ],
		[ "Snatch Level"                  , 1, false ],
		[ "Additional Exceeds Count"      , 1, false ],
		[ "Additional Table Hoppers Count", 1, false ],
		[ "Not Used / Padding"            , 1, true  ],
		[ "Gamepad Taunt"                 , 4, true  ],
		[ "Gamepad Melee Attack"          , 4, true  ],
		[ "Gamepad Ranged Attack"         , 4, true  ],
		[ "Gamepad Jump"                  , 4, true  ],
		[ "Gamepad Lock-On"               , 4, true  ],
		[ "Gamepad Devil Bringer"         , 4, true  ],
		[ "Gamepad Exceed"                , 4, true  ],
		[ "Gamepad Not Used"              , 4, true  ],
		[ "Gamepad Not Used"              , 4, true  ],
		[ "Gamepad Not Used"              , 4, true  ],
		[ "Gamepad Not Used"              , 4, true  ],
		[ "Gamepad Not Used"              , 4, true  ],
		[ "Gamepad Devil Trigger"         , 4, true  ],
		[ "Gamepad Not Used"              , 4, true  ],
		[ "Gamepad Not Used"              , 4, true  ],
		[ "Gamepad Change Target"         , 4, true  ],
		[ "Gamepad Reset Camera"          , 4, true  ],
		[ "Keyboard Taunt"                , 4, true  ],
		[ "Keyboard Melee Attack"         , 4, true  ],
		[ "Keyboard Ranged Attack"        , 4, true  ],
		[ "Keyboard Jump"                 , 4, true  ],
		[ "Keyboard Lock-On"              , 4, true  ],
		[ "Keyboard Devil Bringer"        , 4, true  ],
		[ "Keyboard Exceed"               , 4, true  ],
		[ "Keyboard Not Used"             , 4, true  ],
		[ "Keyboard Not Used"             , 4, true  ],
		[ "Keyboard Not Used"             , 4, true  ],
		[ "Keyboard Not Used"             , 4, true  ],
		[ "Keyboard Not Used"             , 4, true  ],
		[ "Keyboard Devil Trigger"        , 4, true  ],
		[ "Keyboard Not Used"             , 4, true  ],
		[ "Keyboard Not Used"             , 4, true  ],
		[ "Keyboard Move Up"              , 4, true  ],
		[ "Keyboard Move Down"            , 4, true  ],
		[ "Keyboard Move Left"            , 4, true  ],
		[ "Keyboard Move Right"           , 4, true  ],
		[ "Keyboard Up"                   , 4, true  ],
		[ "Keyboard Down"                 , 4, true  ],
		[ "Keyboard Left"                 , 4, true  ],
		[ "Keyboard Right"                , 4, true  ],
		[ "Keyboard Change Target"        , 4, true  ],
		[ "Keyboard Reset Camera"         , 4, true  ],
	];
	c += "<CheatEntry>\n";
	c += "<Description>\"Nero\"</Description>\n";
	c += "<Options moHideChildren=\"1\"/>\n";
	c += "<GroupHeader>1</GroupHeader>\n";
	c += "<CheatEntries>\n";
	var id  = 0;
	var pos = 0x4B8;
	for (var item = 0; item < items.length; item++)
	{
		var description = items[item][0];
		var size        = items[item][1];
		var hex         = items[item][2];
		c += "<CheatEntry>\n";
		c += "<Description>\"" + lz(id) + " " + description + "\"</Description>\n";
		if (hex)
		{
			c += "<ShowAsHex>1</ShowAsHex>\n";
		}
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
			size = 4;
		}
		c += "</VariableType>\n";
		c += "<Address>dmc4.exe+F59F00</Address>\n";
		c += "<Offsets>\n";
		c += "<Offset>" + pos.toString(16).toUpperCase() + "</Offset>\n";
		c += "</Offsets>\n";
		c += "</CheatEntry>\n";
		id++;
		pos += size;
	}
	c += "</CheatEntries>\n";
	c += "</CheatEntry>\n";
}

function FeedVergilData()
{
	var items =
	[
		[ "Enable Devil Trigger"                , 1, true  ],
		[ "Not Used"                            , 1, true  ],
		[ "Enable Enemy Step"                   , 1, true  ],
		[ "Enable Speed"                        , 1, true  ],
		[ "Enable Get More Orbs"                , 1, true  ],
		[ "Enable Trigger Heart"                , 1, true  ],
		[ "Unknown / Padding"                   , 1, true  ],
		[ "Unknown / Padding"                   , 1, true  ],
		[ "Melee Weapon"                        , 4, false ],
		[ "Ranged Weapon"                       , 4, false ],
		[ "Bought Skills Count"                 , 4, false ],
		[ "Proud Souls"                         , 4, false ],
		[ "Expertise 1"                         , 4, true  ],
		[ "Expertise 2"                         , 4, true  ],
		[ "Expertise 3"                         , 4, true  ],
		[ "Expertise 4"                         , 4, true  ],
		[ "Unknown / Padding"                   , 4, true  ],
		[ "Unknown / Padding"                   , 4, true  ],
		[ "Unknown / Padding"                   , 4, true  ],
		[ "Unknown / Padding"                   , 4, true  ],
		[ "Costume"                             , 4, false ],
		[ "Unlock Costume 1"                    , 1, true  ],
		[ "Unlock Costume 2"                    , 1, true  ],
		[ "Unlock Costume 3"                    , 1, true  ],
		[ "Unlock Costume 4"                    , 1, true  ],
		[ "Enable Flush"                        , 1, true  ],
		[ "Enable Million Stab"                 , 1, true  ],
		[ "Summoned Swords Level"               , 1, false ],
		[ "Unknown / Padding"                   , 1, true  ],
		[ "Unknown / Padding"                   , 4, true  ],
		[ "Unknown / Padding"                   , 4, true  ],
		[ "Unknown / Padding"                   , 4, true  ],
		[ "Unknown / Padding"                   , 4, true  ],
		[ "Gamepad Taunt"                       , 4, true  ],
		[ "Gamepad Melee Attack"                , 4, true  ],
		[ "Gamepad Ranged Attack"               , 4, true  ],
		[ "Gamepad Jump"                        , 4, true  ],
		[ "Gamepad Lock-On"                     , 4, true  ],
		[ "Gamepad Not Used"                    , 4, true  ],
		[ "Gamepad Not Used"                    , 4, true  ],
		[ "Gamepad Style"                       , 4, true  ],
		[ "Gamepad Not Used"                    , 4, true  ],
		[ "Gamepad Not Used"                    , 4, true  ],
		[ "Gamepad Not Used"                    , 4, true  ],
		[ "Gamepad Not Used"                    , 4, true  ],
		[ "Gamepad Devil Trigger"               , 4, true  ],
		[ "Gamepad Change Melee Weapon Back"    , 4, true  ],
		[ "Gamepad Change Melee Weapon Forward" , 4, true  ],
		[ "Gamepad Change Target"               , 4, true  ],
		[ "Gamepad Reset Camera"                , 4, true  ],
		[ "Keyboard Taunt"                      , 4, true  ],
		[ "Keyboard Melee Attack"               , 4, true  ],
		[ "Keyboard Ranged Attack"              , 4, true  ],
		[ "Keyboard Jump"                       , 4, true  ],
		[ "Keyboard Lock-On"                    , 4, true  ],
		[ "Keyboard Not Used"                   , 4, true  ],
		[ "Keyboard Not Used"                   , 4, true  ],
		[ "Keyboard Style"                      , 4, true  ],
		[ "Keyboard Not Used"                   , 4, true  ],
		[ "Keyboard Not Used"                   , 4, true  ],
		[ "Keyboard Not Used"                   , 4, true  ],
		[ "Keyboard Not Used"                   , 4, true  ],
		[ "Keyboard Devil Trigger"              , 4, true  ],
		[ "Keyboard Change Melee Weapon Back"   , 4, true  ],
		[ "Keyboard Change Melee Weapon Forward", 4, true  ],
		[ "Keyboard Move Up"                    , 4, true  ],
		[ "Keyboard Move Down"                  , 4, true  ],
		[ "Keyboard Move Left"                  , 4, true  ],
		[ "Keyboard Move Right"                 , 4, true  ],
		[ "Keyboard Up"                         , 4, true  ],
		[ "Keyboard Down"                       , 4, true  ],
		[ "Keyboard Left"                       , 4, true  ],
		[ "Keyboard Right"                      , 4, true  ],
		[ "Keyboard Change Target"              , 4, true  ],
		[ "Keyboard Reset Camera"               , 4, true  ],
	];
	c += "<CheatEntry>\n";
	c += "<Description>\"Vergil\"</Description>\n";
	c += "<Options moHideChildren=\"1\"/>\n";
	c += "<GroupHeader>1</GroupHeader>\n";
	c += "<CheatEntries>\n";
	var id  = 0;
	var pos = 0x4B8;
	for (var item = 0; item < items.length; item++)
	{
		var description = items[item][0];
		var size        = items[item][1];
		var hex         = items[item][2];
		c += "<CheatEntry>\n";
		c += "<Description>\"" + lz(id) + " " + description + "\"</Description>\n";
		if (hex)
		{
			c += "<ShowAsHex>1</ShowAsHex>\n";
		}
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
			size = 4;
		}
		c += "</VariableType>\n";
		c += "<Address>dmc4.exe+F59F00</Address>\n";
		c += "<Offsets>\n";
		c += "<Offset>" + pos.toString(16).toUpperCase() + "</Offset>\n";
		c += "</Offsets>\n";
		c += "</CheatEntry>\n";
		id++;
		pos += size;
	}
	c += "</CheatEntries>\n";
	c += "</CheatEntry>\n";
}

function FeedTrishData()
{
	var items =
	[
		[ "Enable Devil Trigger"  , 1, true  ],
		[ "Enable Air Hike"       , 1, true  ],
		[ "Enable Enemy Step"     , 1, true  ],
		[ "Enable Speed"          , 1, true  ],
		[ "Enable Get More Orbs"  , 1, true  ],
		[ "Enable Trigger Heart"  , 1, true  ],
		[ "Unknown / Padding"     , 1, true  ],
		[ "Unknown / Padding"     , 1, true  ],
		[ "Melee Weapon"          , 4, false ],
		[ "Ranged Weapon"         , 4, false ],
		[ "Bought Skills Count"   , 4, false ],
		[ "Proud Souls"           , 4, false ],
		[ "Expertise 1"           , 4, true  ],
		[ "Expertise 2"           , 4, true  ],
		[ "Expertise 3"           , 4, true  ],
		[ "Expertise 4"           , 4, true  ],
		[ "Unknown / Padding"     , 4, true  ],
		[ "Unknown / Padding"     , 4, true  ],
		[ "Unknown / Padding"     , 4, true  ],
		[ "Unknown / Padding"     , 4, true  ],
		[ "Costume"               , 4, false ],
		[ "Unlock Costume 1"      , 1, true  ],
		[ "Unlock Costume 2"      , 1, true  ],
		[ "Unlock Costume 3"      , 1, true  ],
		[ "Unlock Costume 4"      , 1, true  ],
		[ "Enable Spark"          , 1, true  ],
		[ "Unknown / Padding"     , 1, true  ],
		[ "Unknown / Padding"     , 1, true  ],
		[ "Unknown / Padding"     , 1, true  ],
		[ "Unknown / Padding"     , 1, true  ],
		[ "Unknown / Padding"     , 1, true  ],
		[ "Unknown / Padding"     , 1, true  ],
		[ "Unknown / Padding"     , 1, true  ],
		[ "Unknown / Padding"     , 4, true  ],
		[ "Unknown / Padding"     , 4, true  ],
		[ "Unknown / Padding"     , 4, true  ],
		[ "Unknown / Padding"     , 4, true  ],
		[ "Unknown / Padding"     , 4, true  ],
		[ "Unknown / Padding"     , 4, true  ],
		[ "Gamepad Taunt"         , 4, true  ],
		[ "Gamepad Melee Attack"  , 4, true  ],
		[ "Gamepad Ranged Attack" , 4, true  ],
		[ "Gamepad Jump"          , 4, true  ],
		[ "Gamepad Lock-On"       , 4, true  ],
		[ "Gamepad Not Used"      , 4, true  ],
		[ "Gamepad Not Used"      , 4, true  ],
		[ "Gamepad Sparda"        , 4, true  ],
		[ "Gamepad Not Used"      , 4, true  ],
		[ "Gamepad Not Used"      , 4, true  ],
		[ "Gamepad Not Used"      , 4, true  ],
		[ "Gamepad Not Used"      , 4, true  ],
		[ "Gamepad Devil Trigger" , 4, true  ],
		[ "Gamepad Not Used"      , 4, true  ],
		[ "Gamepad Not Used"      , 4, true  ],
		[ "Gamepad Change Target" , 4, true  ],
		[ "Gamepad Reset Camera"  , 4, true  ],
		[ "Keyboard Taunt"        , 4, true  ],
		[ "Keyboard Melee Attack" , 4, true  ],
		[ "Keyboard Ranged Attack", 4, true  ],
		[ "Keyboard Jump"         , 4, true  ],
		[ "Keyboard Lock-On"      , 4, true  ],
		[ "Keyboard Sparda"       , 4, true  ],
		[ "Keyboard Not Used"     , 4, true  ],
		[ "Keyboard Not Used"     , 4, true  ],
		[ "Keyboard Not Used"     , 4, true  ],
		[ "Keyboard Not Used"     , 4, true  ],
		[ "Keyboard Not Used"     , 4, true  ],
		[ "Keyboard Not Used"     , 4, true  ],
		[ "Keyboard Devil Trigger", 4, true  ],
		[ "Keyboard Not Used"     , 4, true  ],
		[ "Keyboard Not Used"     , 4, true  ],
		[ "Keyboard Move Up"      , 4, true  ],
		[ "Keyboard Move Down"    , 4, true  ],
		[ "Keyboard Move Left"    , 4, true  ],
		[ "Keyboard Move Right"   , 4, true  ],
		[ "Keyboard Up"           , 4, true  ],
		[ "Keyboard Down"         , 4, true  ],
		[ "Keyboard Left"         , 4, true  ],
		[ "Keyboard Right"        , 4, true  ],
		[ "Keyboard Change Target", 4, true  ],
		[ "Keyboard Reset Camera" , 4, true  ],
	];
	c += "<CheatEntry>\n";
	c += "<Description>\"Trish\"</Description>\n";
	c += "<Options moHideChildren=\"1\"/>\n";
	c += "<GroupHeader>1</GroupHeader>\n";
	c += "<CheatEntries>\n";
	var id  = 0;
	var pos = 0x4B8;
	for (var item = 0; item < items.length; item++)
	{
		var description = items[item][0];
		var size        = items[item][1];
		var hex         = items[item][2];
		c += "<CheatEntry>\n";
		c += "<Description>\"" + lz(id) + " " + description + "\"</Description>\n";
		if (hex)
		{
			c += "<ShowAsHex>1</ShowAsHex>\n";
		}
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
			size = 4;
		}
		c += "</VariableType>\n";
		c += "<Address>dmc4.exe+F59F00</Address>\n";
		c += "<Offsets>\n";
		c += "<Offset>" + pos.toString(16).toUpperCase() + "</Offset>\n";
		c += "</Offsets>\n";
		c += "</CheatEntry>\n";
		id++;
		pos += size;
	}
	c += "</CheatEntries>\n";
	c += "</CheatEntry>\n";
}

function FeedLadyData()
{
	var items =
	[
		[ "Enable Burst Attack"                  , 1, true  ],
		[ "Enable Blaster"                       , 1, true  ],
		[ "Enable Enemy Step"                    , 1, true  ],
		[ "Enable Speed"                         , 1, true  ],
		[ "Enable Get More Orbs"                 , 1, true  ],
		[ "Unknown / Padding"                    , 1, true  ],
		[ "Unknown / Padding"                    , 1, true  ],
		[ "Unknown / Padding"                    , 1, true  ],
		[ "Melee Weapon"                         , 4, false ],
		[ "Ranged Weapon"                        , 4, false ],
		[ "Bought Skills Count"                  , 4, false ],
		[ "Proud Souls"                          , 4, false ],
		[ "Expertise 1"                          , 4, true  ],
		[ "Expertise 2"                          , 4, true  ],
		[ "Expertise 3"                          , 4, true  ],
		[ "Expertise 4"                          , 4, true  ],
		[ "Unknown / Padding"                    , 4, true  ],
		[ "Unknown / Padding"                    , 4, true  ],
		[ "Unknown / Padding"                    , 4, true  ],
		[ "Unknown / Padding"                    , 4, true  ],
		[ "Costume"                              , 4, false ],
		[ "Unlock Costume 1"                     , 1, true  ],
		[ "Unlock Costume 2"                     , 1, true  ],
		[ "Unlock Costume 3"                     , 1, true  ],
		[ "Unlock Costume 4"                     , 1, true  ],
		[ "Unknown / Padding"                    , 4, true  ],
		[ "Unknown / Padding"                    , 4, true  ],
		[ "Unknown / Padding"                    , 4, true  ],
		[ "Unknown / Padding"                    , 4, true  ],
		[ "Gamepad Taunt"                        , 4, true  ],
		[ "Gamepad Melee Attack"                 , 4, true  ],
		[ "Gamepad Ranged Attack"                , 4, true  ],
		[ "Gamepad Jump"                         , 4, true  ],
		[ "Gamepad Lock-On"                      , 4, true  ],
		[ "Gamepad Grapple"                      , 4, true  ],
		[ "Gamepad Not Used"                     , 4, true  ],
		[ "Gamepad Not Used"                     , 4, true  ],
		[ "Gamepad Not Used"                     , 4, true  ],
		[ "Gamepad Not Used"                     , 4, true  ],
		[ "Gamepad Not Used"                     , 4, true  ],
		[ "Gamepad Not Used"                     , 4, true  ],
		[ "Gamepad Burst Attack"                 , 4, true  ],
		[ "Gamepad Change Ranged Weapon Back"    , 4, true  ],
		[ "Gamepad Change Ranged Weapon Forward" , 4, true  ],
		[ "Gamepad Change Target"                , 4, true  ],
		[ "Gamepad Reset Camera"                 , 4, true  ],
		[ "Keyboard Taunt"                       , 4, true  ],
		[ "Keyboard Kalina Ann Bayonet"          , 4, true  ],
		[ "Keyboard Ranged Attack"               , 4, true  ],
		[ "Keyboard Jump"                        , 4, true  ],
		[ "Keyboard Lock-On"                     , 4, true  ],
		[ "Keyboard Not Used"                    , 4, true  ],
		[ "Keyboard Not Used"                    , 4, true  ],
		[ "Keyboard Grapple"                     , 4, true  ],
		[ "Keyboard Not Used"                    , 4, true  ],
		[ "Keyboard Not Used"                    , 4, true  ],
		[ "Keyboard Not Used"                    , 4, true  ],
		[ "Keyboard Not Used"                    , 4, true  ],
		[ "Keyboard Burst Attack"                , 4, true  ],
		[ "Keyboard Change Ranged Weapon Back"   , 4, true  ],
		[ "Keyboard Change Ranged Weapon Forward", 4, true  ],
		[ "Keyboard Move Up"                     , 4, true  ],
		[ "Keyboard Move Down"                   , 4, true  ],
		[ "Keyboard Move Left"                   , 4, true  ],
		[ "Keyboard Right"                       , 4, true  ],
		[ "Keyboard Up"                          , 4, true  ],
		[ "Keyboard Down"                        , 4, true  ],
		[ "Keyboard Left"                        , 4, true  ],
		[ "Keyboard Right"                       , 4, true  ],
		[ "Keyboard Change Target"               , 4, true  ],
		[ "Keyboard Reset Camera"                , 4, true  ],
	];
	c += "<CheatEntry>\n";
	c += "<Description>\"Lady\"</Description>\n";
	c += "<Options moHideChildren=\"1\"/>\n";
	c += "<GroupHeader>1</GroupHeader>\n";
	c += "<CheatEntries>\n";
	var id  = 0;
	var pos = 0x4B8;
	for (var item = 0; item < items.length; item++)
	{
		var description = items[item][0];
		var size        = items[item][1];
		var hex         = items[item][2];
		c += "<CheatEntry>\n";
		c += "<Description>\"" + lz(id) + " " + description + "\"</Description>\n";
		if (hex)
		{
			c += "<ShowAsHex>1</ShowAsHex>\n";
		}
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
			size = 4;
		}
		c += "</VariableType>\n";
		c += "<Address>dmc4.exe+F59F00</Address>\n";
		c += "<Offsets>\n";
		c += "<Offset>" + pos.toString(16).toUpperCase() + "</Offset>\n";
		c += "</Offsets>\n";
		c += "</CheatEntry>\n";
		id++;
		pos += size;
	}
	c += "</CheatEntries>\n";
	c += "</CheatEntry>\n";
}

FeedDanteData();
FeedNeroData();
FeedVergilData();
FeedTrishData();
FeedLadyData();

c += "</CheatEntries>\n";
c += "</CheatEntry>\n";

c += "</CheatEntries>\n";
c += "</CheatTable>\n";

document.body.innerHTML = "<plaintext>" + c;
