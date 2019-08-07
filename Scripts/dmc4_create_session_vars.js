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

var root = []; // pos, size, description, hex

function FeedGenericData()
{
	var items =
	[
		[ "Hit Points"                        , 5, false, 0x78 ],
		[ "Magic Points"                      , 5, false, 0x7C ],
		[ "Last Mission Human"                , 4, false, 0x84 ],
		[ "Last Mission Devil Hunter"         , 4, false, 0x88 ],
		[ "Last Mission Son of Sparda"        , 4, false, 0x8C ],
		[ "Last Mission Dante Must Die"       , 4, false, 0x90 ],
		[ "Last Mission Legendary Dark Knight", 4, false, 0x94 ],
		[ "Last Mission Heaven or Hell"       , 4, false, 0x98 ],
		[ "Last Mission Hell and Hell"        , 4, false, 0x9C ],
		[ "Last Mode"                         , 4, false, 0xA0 ],
		[ "Last Character"                    , 4, false, 0xA4 ],
	];
	for (var item = 0; item < items.length; item++)
	{
		var description = items[item][0];
		var size        = items[item][1];
		var hex         = items[item][2];
		var pos         = items[item][3];
		root.push([pos, size, description, hex]);
	}
}

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
		root.push([pos, size, description, false]);
		pos += size;
	}
	{
		var description = games[game] + " Selected Mode";
		root.push([pos, size, description, false]);
		pos += size;
	}
	for (var mode = 0; mode < modes.length; mode++)
	{
		var description = games[game] + " Highest Unlocked Mission " + modes[mode];
		root.push([pos, size, description, false]);
		pos += size;
	}
	}
}

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
	var pos = 0x168;
	for (var item = 0; item < items.length; item++)
	{
		var description = "Dante " + items[item][0];
		var size        = items[item][1];
		var hex         = items[item][2];
		root.push([pos, size, description, hex]);
		pos += size;
	}
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
		[ "Unlock Costume 2 Also Used For Dante"              , 1, true  ],
		[ "Unlock Costume 3"              , 1, true  ],
		[ "Unlock Costume 4"              , 1, true  ],
		[ "Enable Table Hopper"           , 1, true  ],
		[ "Not Used"                      , 1, true  ],
		[ "Not Used"                      , 1, true  ],
		[ "Enable Max-Act"                , 1, true  ],
		[ "Snatch Level"                  , 1, false ],
		[ "Additional Exceed Count"      , 1, false ],
		[ "Additional Table Hopper Count", 1, false ],
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
	var pos = 0x270;
	for (var item = 0; item < items.length; item++)
	{
		var description = "Nero " + items[item][0];
		var size        = items[item][1];
		var hex         = items[item][2];
		root.push([pos, size, description, hex]);
		pos += size;
	}
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
	var pos = 0x360;
	for (var item = 0; item < items.length; item++)
	{
		var description = "Vergil " + items[item][0];
		var size        = items[item][1];
		var hex         = items[item][2];
		root.push([pos, size, description, hex]);
		pos += size;
	}
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
		[ "Unknown / Padding"     , 1, true  ],
		[ "Unknown / Padding"     , 1, true  ],
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
	var pos = 0x45C;
	for (var item = 0; item < items.length; item++)
	{
		var description = "Trish " + items[item][0];
		var size        = items[item][1];
		var hex         = items[item][2];
		root.push([pos, size, description, hex]);
		pos += size;
	}
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
		[ "Unknown / Padding"                    , 1, true  ],
		[ "Unknown / Padding"                    , 1, true  ],
		[ "Kalina Ann Charge Count"              , 1, true  ],
		[ "Unknown / Padding"                    , 1, true  ],
		[ "Unknown / Padding"                    , 1, true  ],
		[ "Unknown / Padding"                    , 1, true  ],
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
	var pos = 0x564;
	for (var item = 0; item < items.length; item++)
	{
		var description = "Lady " + items[item][0];
		var size        = items[item][1];
		var hex         = items[item][2];
		root.push([pos, size, description, hex]);
		pos += size;
	}
}

FeedGenericData();
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

c += "<CheatEntry>\n";
c += "<Description>\"__SESSION__\"</Description>\n";
c += "<GroupHeader>1</GroupHeader>\n";
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
		var hex         = root[rootIndex][3];
		if (pos == offset)
		{
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
	c += "<ShowAsHex>1</ShowAsHex>\n";
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
c += "</CheatEntry>\n";

c += "</CheatEntries>\n";
c += "</CheatTable>\n";

document.body.innerHTML = "<plaintext>" + c;
