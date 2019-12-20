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
c += "<Description>\"__FILE_ITEMS__\"</Description>\n";
c += "<Options moHideChildren=\"1\"/>\n";
c += "<GroupHeader>1</GroupHeader>\n";
c += "<CheatEntries>\n";
var fileItem =
[
	[ "category"   ,  4, false ],
	[ "status"     ,  4, false ],
	[ "id"         ,  2, false ],
	[ "padding"    ,  6, true  ],
	[ "callback"   ,  8, true  ],
	[ "string item",  8, true  ],
	[ "file"       ,  8, true  ],
	[ "unknown"    , 32, true  ],
];

var itemName =
[
	[ 140, "rebellion"          ],
	[ 141, "cerberus"           ],
	[ 142, "agni rudra"       ],
	[ 143, "nevan"              ],
	[ 144, "beowulf"            ],
	[ 145, "ebony ivory"      ],
	[ 146, "shotgun"            ],
	[ 147, "artemis"            ],
	[ 148, "spiral"             ],
	[ 149, "kalina ann"         ],
	[ 169, "yamato bob"         ],
	[ 179, "lady gun 1"         ],
	[ 180, "lady gun 2"         ],
	[ 196, "yamato"             ],
	[ 189, "beowulf vergil"     ],
	[ 198, "force edge"         ],
	[ 187, "nero angelo sword"  ],
	[   0, "human dante"        ],
	[ 200, "devil rebellion"    ],
	[ 201, "devil cerberus"     ],
	[ 202, "devil agni rudra" ],
	[ 203, "devil nevan"        ],
	[ 204, "devil beowulf"      ],
	[ 205, "devil sparda"       ],
	[   1, "human bob"          ],
	[ 207, "devil yamato bob"   ],
	[   2, "human lady"         ],
	[   3, "human vergil"       ],
	[ 221, "devil yamato"       ],
	[ 222, "devil beowulf"      ],
	[ 223, "devil nero angelo"  ],
];

var pos = 0;
for (var index = 0; index < 250; index++)
{
	c += "<CheatEntry>\n";
	c += "<Description>\"" + lz(index);
	for (var itemNameIndex = 0; itemNameIndex < itemName.length; itemNameIndex++)
	{
		var id  = itemName[itemNameIndex][0];
		var str = itemName[itemNameIndex][1];
		if (index == id)
		{
			c += " " + str;
			break;
		}
	}
	c += "\"</Description>\n";
	c += "<Options moHideChildren=\"1\"/>\n";
	c += "<GroupHeader>1</GroupHeader>\n";
	c += "<CheatEntries>\n";
	var itemPos = 0;
	for (var fileItemIndex = 0; fileItemIndex < fileItem.length; fileItemIndex++)
	{
		var description = fileItem[fileItemIndex][0];
		var size        = fileItem[fileItemIndex][1];
		var hex         = fileItem[fileItemIndex][2];
		var isArray     = false;
		var addr        = "<Address>dmc3.exe+C99D30+" + pos.toString(16).toUpperCase() + "+" + itemPos.toString(16).toUpperCase() + "</Address>";
		c += "<CheatEntry>\n";
		c += "<Description>\"" + lz(fileItemIndex) + " " + description + "\"</Description>\n";
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
		else
		{
			c += "Array of byte";
			isArray = true;
		}
		c += "</VariableType>\n";
		if (isArray)
		{
			c += "<ByteLength>" + size + "</ByteLength>\n";
		}
		c += "<Address>" + addr + "</Address>\n"
		c += "</CheatEntry>\n";
		if (fileItemIndex == 5)
		{
			c += "<CheatEntry>\n";
			c += "<Description>\"string\"</Description>\n";
			c += "<VariableType>String</VariableType>\n";
			c += "<Length>128</Length>\n";
			c += "<Unicode>0</Unicode>\n";
			c += "<CodePage>0</CodePage>\n";
			c += "<ZeroTerminate>1</ZeroTerminate>\n";
			c += "<Address>" + addr + "</Address>\n"
			c += "<Offsets>\n";
			c += "<Offset>0</Offset>\n";
			c += "<Offset>8</Offset>\n";
			c += "</Offsets>\n";
			c += "</CheatEntry>\n";
		}
		itemPos += size;
	}
	c += "</CheatEntries>\n";
	c += "</CheatEntry>\n";
	pos += 72;
}
c += "</CheatEntries>\n";
c += "</CheatEntry>\n";

c += "</CheatEntries>\n";
c += "</CheatTable>\n";

document.body.innerHTML = "<plaintext>" + c;
