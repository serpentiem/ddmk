var fs = require("fs");

eval(fs.readFileSync("dmc3_core.js", "utf8"));

var fileData =
[
	[ "group"     , "uint32"  ],
	[ "status"    , "uint32"  ],
	[ "id"        , "uint16"  ],
	[ "[6]"       , "byte8"   ],
	[ "callback"  , "void *"  ],
	[ "stringData", "void *"  ],
	[ "file"      , "byte8 *" ],
	[ "[32]"      , "byte8"   ],
];

const FILE_DATA_SIZE = 72;

var items =
[
	[ 0  , "human dante"       ],
	[ 1  , "human bob"         ],
	[ 2  , "human lady"        ],
	[ 3  , "human vergil"      ],
	[ 140, "rebellion"         ],
	[ 141, "cerberus"          ],
	[ 142, "agni rudra"        ],
	[ 143, "nevan"             ],
	[ 144, "beowulf dante"     ],
	[ 145, "ebony ivory"       ],
	[ 146, "shotgun"           ],
	[ 147, "artemis"           ],
	[ 148, "spiral"            ],
	[ 149, "kalina ann"        ],
	[ 169, "yamato bob"        ],
	[ 179, "lady gun 1"        ],
	[ 180, "lady gun 2"        ],
	[ 187, "nero angelo sword" ],
	[ 189, "beowulf vergil"    ],
	[ 196, "yamato"            ],
	[ 198, "force edge"        ],
	[ 200, "devil rebellion"   ],
	[ 201, "devil cerberus"    ],
	[ 202, "devil agni rudra"  ],
	[ 203, "devil nevan"       ],
	[ 204, "devil beowulf"     ],
	[ 205, "devil sparda"      ],
	[ 207, "devil yamato bob"  ],
	[ 221, "devil yamato"      ],
	[ 222, "devil beowulf"     ],
	[ 223, "devil nero angelo" ],
	[ 231, "pride" ],
];

CheatTableStart();

GroupStart("__FILE_DATA_ITEMS__", true);




var groupItemCounts =
[
	4,
	136,
	60,
	28,
	1,
	128,
	6
];



var g_itemIndex = 0;

pos = 0;

for (var groupIndex = 0; groupIndex < groupItemCounts.length; groupIndex++)
{
	GroupStart(lz(groupIndex), true);



	var groupItemCount = groupItemCounts[groupIndex];

	for (var groupItemIndex = 0; groupItemIndex < groupItemCount; groupItemIndex++, g_itemIndex++)
	{
		var groupName = lz(groupItemIndex) + " " + lz(g_itemIndex);

		for (var itemIndex = 0; itemIndex < items.length; itemIndex++)
		{
			var item = items[itemIndex];

			var id   = item[0];
			var name = item[1];

			if (g_itemIndex == id)
			{
				groupName += " " + name;

				break;
			}
		}

		GroupStart(groupName, true);



		var itemPos = 0;

		for (var itemIndex = 0; itemIndex < fileData.length; itemIndex++)
		{
			var item = fileData[itemIndex];

			var name = item[0];
			var type = item[1];

			var count        = 1;
			var size         = GetTypeSize    (type);
			var variableType = GetVariableType(type);
			var hex          = GetShowAsHex   (type);

			{
				var matches = name.match(/\[\d+?\]/g);
				if (matches)
				{
					for (var matchIndex = 0; matchIndex < matches.length; matchIndex++)
					{
						count *= parseInt(matches[matchIndex].match(/\[(\d+?)\]/)[1]);
					}
				}
			}

			CreateCheatEntry
			(
				name,
				hex,
				variableType,
				"dmc3.exe+C99D30+" + pos.toString(16).toUpperCase() + "+" + itemPos.toString(16).toUpperCase()
			);

			if (name == "stringData")
			{
				c += "<CheatEntry>" + NEW_LINE;
				c += "<Description>\"" + name + "\"</Description>" + NEW_LINE;
				c += "<VariableType>String</VariableType>" + NEW_LINE;
				c += "<Length>64</Length>" + NEW_LINE;
				c += "<Unicode>0</Unicode>" + NEW_LINE;
				c += "<CodePage>0</CodePage>" + NEW_LINE;
				c += "<ZeroTerminate>1</ZeroTerminate>" + NEW_LINE;
				c += "<Address>" + "dmc3.exe+C99D30+" + pos.toString(16).toUpperCase() + "+" + itemPos.toString(16).toUpperCase() + "</Address>" + NEW_LINE;
				c += "<Offsets>" + NEW_LINE;
				c += "<Offset>0</Offset>" + NEW_LINE;
				c += "<Offset>8</Offset>" + NEW_LINE;
				c += "</Offsets>" + NEW_LINE;
				c += "</CheatEntry>" + NEW_LINE;
			}

			itemPos += (count * size);
		}



		GroupEnd();

		pos += FILE_DATA_SIZE;
	}



	GroupEnd();
}









// for (var fileDataIndex = 0; fileDataIndex < 363; fileDataIndex++)
// {
// 	var groupName = lz(fileDataIndex);

// 	for (var itemIndex = 0; itemIndex < items.length; itemIndex++)
// 	{
// 		var item = items[itemIndex];

// 		var id   = item[0];
// 		var name = item[1];

// 		if (fileDataIndex == id)
// 		{
// 			groupName += " " + name;

// 			break;
// 		}
// 	}

// 	GroupStart(groupName, true);






// 	var itemPos = 0;

// 	for (var itemIndex = 0; itemIndex < fileData.length; itemIndex++)
// 	{
// 		var item = fileData[itemIndex];

// 		var name = item[0];
// 		var type = item[1];

// 		var count        = 1;
// 		var size         = GetTypeSize    (type);
// 		var variableType = GetVariableType(type);
// 		var hex          = GetShowAsHex   (type);

// 		{
// 			var matches = name.match(/\[\d+?\]/g);
// 			if (matches)
// 			{
// 				for (var matchIndex = 0; matchIndex < matches.length; matchIndex++)
// 				{
// 					count *= parseInt(matches[matchIndex].match(/\[(\d+?)\]/)[1]);
// 				}
// 			}
// 		}

// 		CreateCheatEntry
// 		(
// 			name,
// 			hex,
// 			variableType,
// 			"dmc3.exe+C99D30+" + pos.toString(16).toUpperCase() + "+" + itemPos.toString(16).toUpperCase()
// 		);

// 		if (name == "stringData")
// 		{
// 			c += "<CheatEntry>" + NEW_LINE;
// 			c += "<Description>\"" + name + "\"</Description>" + NEW_LINE;
// 			c += "<VariableType>String</VariableType>" + NEW_LINE;
// 			c += "<Length>64</Length>" + NEW_LINE;
// 			c += "<Unicode>0</Unicode>" + NEW_LINE;
// 			c += "<CodePage>0</CodePage>" + NEW_LINE;
// 			c += "<ZeroTerminate>1</ZeroTerminate>" + NEW_LINE;
// 			c += "<Address>" + "dmc3.exe+C99D30+" + pos.toString(16).toUpperCase() + "+" + itemPos.toString(16).toUpperCase() + "</Address>" + NEW_LINE;
// 			c += "<Offsets>" + NEW_LINE;
// 			c += "<Offset>0</Offset>" + NEW_LINE;
// 			c += "<Offset>8</Offset>" + NEW_LINE;
// 			c += "</Offsets>" + NEW_LINE;
// 			c += "</CheatEntry>" + NEW_LINE;
// 		}

// 		itemPos += (count * size);
// 	}

// 	GroupEnd();

// 	pos += FILE_DATA_SIZE;
// }

GroupEnd()

CheatTableEnd();

fs.writeFileSync("file_data_items.txt", c);
