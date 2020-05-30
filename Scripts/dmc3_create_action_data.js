var fs = require("fs");

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

// var items =
// [
// 	[ 7, "Rapid Slash Duration" ],
// 	[ 8, "Rapid Slash Range" ],
// 	[ 39, "Stinger Duration" ],
// 	[ 40, "Stinger Range" ],
// 	[ 81, "Judgement Cut Range" ],
// 	[ 98, "Judgement Cut Extra Count" ],
// ];

var items =
[
	[ 10 , "Rebellion Stinger Duration"   ],
	[ 11 , "Rebellion Stinger Range"      ],
	[ 159, "Beowulf Rising Dragon No Charge Height"      ],
	[ 333, "Beowulf Rising Dragon Medium Charge Height"      ],
	[ 337, "Beowulf Rising Dragon Full Charge Height"      ],
	[ 283, "Shotgun Gun Stinger Duration" ],
	[ 284, "Shotgun Gun Stinger Range"    ],
	[ 301, "Nevan Reverb Shock Duration"  ],
	[ 302, "Nevan Reverb Shock Range"     ],
	[ 328, "Beowulf Straight Duration"    ],
	[ 329, "Beowulf Straight Range"       ],
	[ 339, "Cerberus Revolver Height"     ],
	[ 340, "Cerberus Revolver Pull"       ],
];

// var items =
// [
// 	[ 75 , "Trickster Sky Star Count"   ],
// 	[ 164 , "Trickster Air Trick Duration"   ],
// 	[ 168 , "Trickster Air Trick Leap"   ],
// ];



var c = "";

c += "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
c += "<CheatTable>\n";
c += "<CheatEntries>\n";

c += "<CheatEntry>\n";
c += "<Description>\"__ACTION_DATA__\"</Description>\n";
c += "<GroupHeader>1</GroupHeader>\n";
c += "<CheatEntries>\n";

for (var index = 0; index < 500; index++)
{
	c += "<CheatEntry>\n";
	c += "<Description>\"" + lz(index);
	for (var itemIndex = 0; itemIndex < items.length; itemIndex++)
	{
		var id   = items[itemIndex][0];
		var name = items[itemIndex][1];
		if (index == id)
		{
			if (name == "")
			{
				c += " Unknown";
			}
			else
			{
				c += " " + name;
			}
			break;
		}
	}
	c += "\"</Description>\n";
	c += "<VariableType>Float</VariableType>\n";
	c += "<Address>Mary.Actor_actorBaseAddr+8+10</Address>\n";
	c += "<Offsets>\n";
	c += "<Offset>" + (index * 4).toString(16).toUpperCase() + "</Offset>\n";
	c += "<Offset>3DF8</Offset>\n";
	c += "</Offsets>\n";
	c += "</CheatEntry>\n";
}

c += "</CheatEntries>\n";
c += "</CheatEntry>\n";

c += "</CheatEntries>\n";
c += "</CheatTable>\n";

fs.writeFileSync("actionData.txt", c);
