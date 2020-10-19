var c = "";

c += "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
c += "<CheatTable>\n";
c += "<CheatEntries>\n";

c += "<CheatEntry>\n";
c += "<Description>\"B600\"</Description>\n";
c += "<GroupHeader>1</GroupHeader>\n";
c += "<CheatEntries>\n";

for (var index = 0; index < 48; index++)
{
	var off = (0xB600 + index);
	
	c += "<CheatEntry>\n";
	c += "<Description>\"" + off.toString(16).toUpperCase() + "\"</Description>\n";
	c += "<ShowAsHex>1</ShowAsHex>\n";
	c += "<VariableType>Byte</VariableType>\n";
	c += "<Address>dmc3.exe+C90E28</Address>\n";
	c += "<Offsets>\n";
	c += "<Offset>" + off.toString(16).toUpperCase() + "</Offset>\n";
	c += "<Offset>18</Offset>\n";
	c += "</Offsets>\n";
	c += "</CheatEntry>\n";
}

c += "</CheatEntries>\n";
c += "</CheatEntry>\n";

c += "</CheatEntries>\n";
c += "</CheatTable>\n";

document.body.innerHTML = "<plaintext>" + c;
