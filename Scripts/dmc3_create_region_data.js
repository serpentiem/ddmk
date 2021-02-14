var fs = require("fs");

eval(fs.readFileSync("dmc3_core.js", "utf8"));

var regionData =
[
	[ "addr"    , "byte8 *" ],
	[ "end"     , "byte8 *" ],
	[ "last"    , "uint32"  ],
	[ "boundary", "uint32"  ],
	[ "size"    , "uint32"  ],
	[ "pipe"    , "uint32"  ],
	[ "count"   , "uint32"  ],
];

const REGION_DATA_SIZE = 40;

CheatTableStart();

GroupStart("__REGION_DATA__", true);

pos = 0;

for (var index = 0; index < 8; index++)
{
	GroupStart(lz(index));

	var itemPos = 0;

	for (var itemIndex = 0; itemIndex < regionData.length; itemIndex++)
	{
		var item = regionData[itemIndex];

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
			"dmc3.exe+CA8910+" + pos.toString(16).toUpperCase() + "+" + itemPos.toString(16).toUpperCase()
		);

		itemPos += (count * size);
	}

	GroupEnd();

	pos += REGION_DATA_SIZE;
}

GroupEnd()

CheatTableEnd();

fs.writeFileSync("region_data.txt", c);
