// @Todo: Move.


var fs = require("fs");

eval(fs.readFileSync("dmc3_core.js", "utf8"));

c += "<?xml version=\"1.0\" encoding=\"utf-8\"?>" + NEW_LINE;
c += "<CheatTable>" + NEW_LINE;
c += "<CheatEntries>" + NEW_LINE;

c += "<CheatEntry>" + NEW_LINE;
c += "<Description>__MODEL_PARTITION_DATA__</Description>" + NEW_LINE;
c += "<Options moHideChildren=\"1\"/>" + NEW_LINE;
c += "<GroupHeader>1</GroupHeader>" + NEW_LINE;
c += "<CheatEntries>" + NEW_LINE;

for (var actor = 0; actor < 4; actor++)
{
	c += "<CheatEntry>" + NEW_LINE;
	c += "<Description>" + lz(actor) + "</Description>" + NEW_LINE;
	c += "<Options moHideChildren=\"1\"/>" + NEW_LINE;
	c += "<GroupHeader>1</GroupHeader>" + NEW_LINE;
	c += "<CheatEntries>" + NEW_LINE;

	for (var index = 0; index < 20; index++)
	{
		CreateCheatEntry
		(
			lz(index),
			true,
			"Byte",
			"Mary.Actor_actorBaseAddr",
			(index * 0x380).toString(16).toUpperCase(),
			"B8D0+80+100",
			(actor * 8).toString(16).toUpperCase()
		);
	}

	c += "</CheatEntries>" + NEW_LINE;
	c += "</CheatEntry>" + NEW_LINE;
}

c += "</CheatEntries>" + NEW_LINE;
c += "</CheatEntry>" + NEW_LINE;

c += "</CheatEntries>" + NEW_LINE;
c += "</CheatTable>" + NEW_LINE;

fs.writeFileSync("modelPartitionData.txt", c);
