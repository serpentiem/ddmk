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
c += "<Options moHideChildren=\"1\"/>\n";
c += "<GroupHeader>1</GroupHeader>\n";
c += "<CheatEntries>\n";

var items =
[
	[ "character"                   , 1, false, 0x78                    ],
	[ "x"                           , 4, false, 0x80  , "Float"         ],
	[ "y"                           , 4, false, 0x84  , "Float"         ],
	[ "z"                           , 4, false, 0x88  , "Float"         ],
	[ "actor id"                    , 1, false, 0x118                   ],
	[ "is doppelganger"             , 1, false, 0x11C                   ],
	[ "visible"                     , 1, false, 0x120                   ],
	[ "motion 0000"                 , 8, true , 0x38A0                  ],
	[ "motion 0001"                 , 8, true , 0x38A8                  ],
	[ "motion 0002"                 , 8, true , 0x38B0                  ],
	[ "motion 0003"                 , 8, true , 0x38B8                  ],
	[ "motion 0004"                 , 8, true , 0x38C0                  ],
	[ "motion 0005"                 , 8, true , 0x38C8                  ],
	[ "motion 0006"                 , 8, true , 0x38D0                  ],
	[ "motion 0007"                 , 8, true , 0x38D8                  ],
	[ "motion 0008"                 , 8, true , 0x38E0                  ],
	[ "motion 0009"                 , 8, true , 0x38E8                  ],
	[ "motion 0010"                 , 8, true , 0x38F0                  ],
	[ "motion 0011"                 , 8, true , 0x38F8                  ],
	[ "motion 0012"                 , 8, true , 0x3900                  ],
	[ "motion 0013"                 , 8, true , 0x3908                  ],
	[ "motion 0014"                 , 8, true , 0x3910                  ],
	[ "motion 0015"                 , 8, true , 0x3918                  ],
	[ "motion 0016"                 , 8, true , 0x3920                  ],
	[ "motion 0017"                 , 8, true , 0x3928                  ],
	[ "motion 0018"                 , 8, true , 0x3930                  ],
	[ "motion 0019"                 , 8, true , 0x3938                  ],
	[ "motion 0020"                 , 8, true , 0x3940                  ],
	[ "motion 0021"                 , 8, true , 0x3948                  ],
	[ "motion 0022"                 , 8, true , 0x3950                  ],
	[ "motion 0023"                 , 8, true , 0x3958                  ],
	[ "motion 0024"                 , 8, true , 0x3960                  ],
	[ "motion 0025"                 , 8, true , 0x3968                  ],
	[ "motion 0026"                 , 8, true , 0x3970                  ],
	[ "motion 0027"                 , 8, true , 0x3978                  ],
	[ "motion 0028"                 , 8, true , 0x3980                  ],
	[ "motion 0029"                 , 8, true , 0x3988                  ],
	[ "motion 0030"                 , 8, true , 0x3990                  ],
	[ "motion 0031"                 , 8, true , 0x3998                  ],
	[ "motion flags 1"              , 2, false, 0x39B0                  ],
	[ "motion flags 2"              , 2, false, 0x39B2                  ],
	[ "motion flags 3"              , 2, false, 0x39B4                  ],
	[ "motion flags 4"              , 2, false, 0x39B6                  ],
	[ "motion flags 5"              , 2, false, 0x39B8                  ],
	[ "shadow"                      , 4, false, 0x3A18                  ],
	[ "color"                       , 4, true , 0x3A28                  ],
	[ "charged shot air"            , 2, false, 0x3E1A                  ],
	[ "charged shot"                , 2, false, 0x3E22                  ],
	[ "idle timer"                  , 4, false, 0x3E38, "Float"         ],
	[ "motion state 1"              , 4, true , 0x3E60                  ],
	[ "motion state 2"              , 4, true , 0x3E64                  ],
	[ "motion state 3"              , 4, true , 0x3E68                  ],
	[ "actor model"                 , 4, false, 0x3E6C                  ],
	[ "actor model mirror"          , 4, false, 0x3E70                  ],
	[ "actor model mirror"          , 4, false, 0x3E88                  ],
	[ "devil"                       , 1, false, 0x3E9B                  ],
	[ "costume"                     , 1, false, 0x3E9E                  ],
	[ "special costume"             , 1, false, 0x3E9F                  ],
	[ "magic points"                , 4, false, 0x3EB8, "Float"         ],
	[ "max magic points"            , 4, false, 0x3EBC, "Float"         ],
	[ "move"                        , 1, false, 0x3FA4                  ],
	[ "last move"                   , 1, false, 0x3FA5                  ],
	[ "chain count infinite"        , 1, false, 0x3FAC                  ],
	[ "expertise 0000"              , 4, true , 0x3FEC                  ],
	[ "expertise 0001"              , 4, true , 0x3FF0                  ],
	[ "expertise 0002"              , 4, true , 0x3FF4                  ],
	[ "expertise 0003"              , 4, true , 0x3FF8                  ],
	[ "expertise 0004"              , 4, true , 0x3FFC                  ],
	[ "expertise 0005"              , 4, true , 0x4000                  ],
	[ "expertise 0006"              , 4, true , 0x4004                  ],
	[ "expertise 0007"              , 4, true , 0x4008                  ],
	[ "expertise 0008"              , 4, true , 0x400C                  ],
	[ "expertise 0009"              , 4, true , 0x4010                  ],
	[ "expertise 0010"              , 4, true , 0x4014                  ],
	[ "expertise 0011"              , 4, true , 0x4018                  ],
	[ "expertise 0012"              , 4, true , 0x401C                  ],
	[ "expertise 0013"              , 4, true , 0x4020                  ],
	[ "expertise 0014"              , 4, true , 0x4024                  ],
	[ "expertise 0015"              , 4, true , 0x4028                  ],
	[ "max hit points"              , 4, false, 0x40EC, "Float"         ],
	[ "hit points"                  , 4, false, 0x411C, "Float"         ],
	[ "target base addr"            , 8, true , 0x6328                  ],
	[ "style"                       , 4, false, 0x6338                  ],
	[ "style level"                 , 4, false, 0x6358                  ],
	[ "dash"                        , 1, false, 0x635C                  ],
	[ "sky star"                    , 1, false, 0x635D                  ],
	[ "air trick"                   , 1, false, 0x635E                  ],
	[ "trick up"                    , 1, false, 0x635F                  ],
	[ "trick down"                  , 1, false, 0x6360                  ],
	[ "quicksilver"                 , 1, false, 0x6361                  ],
	[ "doppelganger"                , 1, false, 0x6362                  ],
	[ "style experience"            , 4, false, 0x6364, "Float"         ],
	[ "control linked actor"        , 4, false, 0x6454                  ],
	[ "linked actor base addr"      , 8, true , 0x6478                  ],
	[ "selected melee weapon vergil", 4, false, 0x6488                  ],
	[ "active weapon"               , 1, false, 0x648D                  ],
	[ "selected melee weapon"       , 4, false, 0x6490                  ],
	[ "selected ranged weapon"      , 4, false, 0x6494                  ],
	[ "equipment"                   , 8, true , 0x6498, "Array of byte" ],
	[ "weapon metadata 0000"        , 8, true , 0x64A0                  ],
	[ "weapon metadata 0001"        , 8, true , 0x64A8                  ],
	[ "weapon metadata 0002"        , 8, true , 0x64B0                  ],
	[ "weapon metadata 0003"        , 8, true , 0x64B8                  ],
	[ "weapon flags 0000"           , 4, true , 0x64C8                  ],
	[ "weapon flags 0001"           , 4, true , 0x64CC                  ],
	[ "weapon flags 0002"           , 4, true , 0x64D0                  ],
	[ "weapon flags 0003"           , 4, true , 0x64D4                  ],
	[ "melee weapon model"          , 1, false, 0x64F0                  ],
	[ "ranged weapon model"         , 1, false, 0x64F1                  ],
	[ "weapon timer 0000"           , 4, false, 0x64F4, "Float"         ],
	[ "weapon timer 0001"           , 4, false, 0x64F8, "Float"         ],
	[ "weapon timer 0002"           , 4, false, 0x64FC, "Float"         ],
	[ "weapon timer 0003"           , 4, false, 0x6500, "Float"         ],
	[ "style rank"                  , 4, false, 0x6510                  ],
	[ "style meter"                 , 4, false, 0x6514, "Float"         ],
	[ "charge 0000 flags 1"         , 4, true , 0x66A4                  ],
	[ "charge 0000 flags 2"         , 4, true , 0x66A8                  ],
	[ "charge 0000 value"           , 4, false, 0x66AC, "Float"         ],
	[ "charge 0001 flags 1"         , 4, true , 0x66B0                  ],
	[ "charge 0001 flags 2"         , 4, true , 0x66B4                  ],
	[ "charge 0001 value"           , 4, false, 0x66B8, "Float"         ],
	[ "charge 0002 flags 1"         , 4, true , 0x66BC                  ],
	[ "charge 0002 flags 2"         , 4, true , 0x66C0                  ],
	[ "charge 0002 value"           , 4, false, 0x66C4, "Float"         ],
	[ "charge 0003 flags 1"         , 4, true , 0x66C8                  ],
	[ "charge 0003 flags 2"         , 4, true , 0x66CC                  ],
	[ "charge 0003 value"           , 4, false, 0x66D0, "Float"         ],
	[ "charge 0004 flags 1"         , 4, true , 0x66D4                  ],
	[ "charge 0004 flags 2"         , 4, true , 0x66D8                  ],
	[ "charge 0004 value"           , 4, false, 0x66DC, "Float"         ],
	[ "charge 0005 flags 1"         , 4, true , 0x66E0                  ],
	[ "charge 0005 flags 2"         , 4, true , 0x66E4                  ],
	[ "charge 0005 value"           , 4, false, 0x66E8, "Float"         ],
	[ "charge 0006 flags 1"         , 4, true , 0x66EC                  ],
	[ "charge 0006 flags 2"         , 4, true , 0x66F0                  ],
	[ "charge 0006 value"           , 4, false, 0x66F4, "Float"         ],
	[ "charge 0007 flags 1"         , 4, true , 0x66F8                  ],
	[ "charge 0007 flags 2"         , 4, true , 0x66FC                  ],
	[ "charge 0007 value"           , 4, false, 0x6700, "Float"         ],
	[ "lower body motion index"     , 4, false, 0x6950+0x5C             ],
	[ "lower body move interval"    , 2, false, 0x6950+0xB2             ],
	[ "lower body motion index"     , 1, false, 0x6950+0xBD             ],
	[ "upper body motion index"     , 4, false, 0x6A70+0x5C             ],
	[ "upper body move interval"    , 2, false, 0x6A70+0xB2             ],
	[ "upper body motion index"     , 1, false, 0x6A70+0xBD             ],
	[ "artemis all charges"         , 4, false, 0xB868, "Float"         ],
	[ "artemis single charge"       , 4, false, 0xB86C, "Float"         ],
	[ "artemis charge flags 1"      , 4, true , 0xB87C                  ],
	[ "artemis charge flags 2"      , 4, true , 0xB880                  ],
];

for (var actor = 0; actor < 4; actor++)
{
	c += "<CheatEntry>\n";
	c += "<Description>\"" + lz(actor) + "\"</Description>\n";
	c += "<Options moHideChildren=\"1\"/>\n";
	c += "<GroupHeader>1</GroupHeader>\n";
	c += "<CheatEntries>\n";
	for (var itemIndex = 0; itemIndex < items.length; itemIndex++)
	{
		var description = items[itemIndex][0];
		var size        = items[itemIndex][1];
		var hex         = items[itemIndex][2];
		var off         = items[itemIndex][3];
		var type        = items[itemIndex][4];
		c += "<CheatEntry>\n";
		c += "<Description>\"" + description + "\"</Description>\n";
		if (hex)
		{
			c += "<ShowAsHex>1</ShowAsHex>\n";
		}
		c += "<VariableType>";
		if (type)
		{
			c += type;
		}
		else
		{
			if (size == 1)
			{
				c += "Byte";
			}
			else if (size == 2)
			{
				c += "2 Bytes";
			}
			else if (size == 4)
			{
				c += "4 Bytes";
			}
			else if (size == 8)
			{
				c += "8 Bytes";
			}
		}
		c += "</VariableType>\n";
		if (type && (type == "Array of byte"))
		{
			c += "<ByteLength>" + size + "</ByteLength>\n";
		}
		c += "<Address>System_Actor_actorBaseAddr+" + (actor * 8).toString(16).toUpperCase() + "</Address>\n"
		c += "<Offsets>\n";
		c += "<Offset>" + off.toString(16).toUpperCase() + "</Offset>\n";
		c += "</Offsets>\n";
		c += "</CheatEntry>\n";
	}
	c += "</CheatEntries>\n";
	c += "</CheatEntry>\n";
}

c += "</CheatEntries>\n";
c += "</CheatEntry>\n";

c += "</CheatEntries>\n";
c += "</CheatTable>\n";

document.body.innerHTML = "<plaintext>" + c;
