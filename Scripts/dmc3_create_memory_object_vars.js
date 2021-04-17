
// @Todo: Move.


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

var memoryObject =
[
	[ "addr"    , 8, true  ],
	[ "end"     , 8, true  ],
	[ "last"    , 4, true  ],
	[ "boundary", 4, true  ],
	[ "size"    , 4, true  ],
	[ "pipe"    , 4, true  ],
	[ "count"   , 4, false ],
	[ "padding" , 4, false ],
];

var objectOff =
[
	0xCA8910,
	0xCA8938,
	0xCA8960,
];

for (var object = 0; object < objectOff.length; object++)
{
	c += "<CheatEntry>\n";
	c += "<Description>\"" + lz(object) + "\"</Description>\n";
	c += "<Options moHideChildren=\"0\"/>\n";
	c += "<GroupHeader>1</GroupHeader>\n";
	c += "<CheatEntries>\n";
	var pos = 0;
	for (var index = 0; index < memoryObject.length; index++)
	{
		var description = memoryObject[index][0];
		var size        = memoryObject[index][1];
		var hex         = memoryObject[index][2];
		c += "<CheatEntry>\n";
		c += "<Description>\"" + lz(index) + " " + description + "\"</Description>\n";
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
		c += "</VariableType>\n";
		c += "<Address>dmc3.exe+" + objectOff[object].toString(16).toUpperCase() + "+" + pos.toString(16).toUpperCase() + "</Address>\n"
		c += "</CheatEntry>\n";
		pos += size;
	}
	c += "</CheatEntries>\n";
	c += "</CheatEntry>\n";
}

c += "</CheatEntries>\n";
c += "</CheatTable>\n";

document.body.innerHTML = "<plaintext>" + c;
