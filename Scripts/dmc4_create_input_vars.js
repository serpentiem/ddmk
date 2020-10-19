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

function FeedInternalData()
{
	var items =
	[
		[ "Enable", 4, false, 0x20 ],
	];
	for (var item = 0; item < items.length; item++)
	{
		var description = items[item][0];
		var size        = items[item][1];
		var hex         = items[item][2];
		var off         = items[item][3];
		root.push([off, size, description, hex]);
	}
}

function FeedDeviceData()
{
	var items =
	[
		[ "Start"                  , 4, true,     0 ],
		[ "Timer Void"             , 2, true,  0x1C ],
		[ "Timer Back"             , 2, true,  0x1E ],
		[ "Timer Left Thumb"       , 2, true,  0x20 ],
		[ "Timer Right Thumb"      , 2, true,  0x22 ],
		[ "Timer Start"            , 2, true,  0x24 ],
		[ "Timer DPad Up"          , 2, true,  0x26 ],
		[ "Timer DPad Right"       , 2, true,  0x28 ],
		[ "Timer DPad Down"        , 2, true,  0x2A ],
		[ "Timer DPad Left"        , 2, true,  0x2C ],
		[ "Timer Left Shoulder"    , 2, true,  0x2E ],
		[ "Timer Right Shoulder"   , 2, true,  0x30 ],
		[ "Timer Left Trigger"     , 2, true,  0x32 ],
		[ "Timer Right Trigger"    , 2, true,  0x34 ],
		[ "Timer Y"                , 2, true,  0x36 ],
		[ "Timer B"                , 2, true,  0x38 ],
		[ "Timer A"                , 2, true,  0x3A ],
		[ "Timer X"                , 2, true,  0x3C ],
		[ "Timer Left Stick Up"    , 2, true,  0x3E ],
		[ "Timer Left Stick Right" , 2, true,  0x40 ],
		[ "Timer Left Stick Down"  , 2, true,  0x42 ],
		[ "Timer Left Stick Left"  , 2, true,  0x44 ],
		[ "Timer Right Stick Up"   , 2, true,  0x46 ],
		[ "Timer Right Stick Right", 2, true,  0x48 ],
		[ "Timer Right Stick Down" , 2, true,  0x4A ],
		[ "Timer Right Stick Left" , 2, true,  0x4C ],
		[ "Timer Padding"          , 2, true,  0x4E ],
		[ "Buttons Sticks"         , 4, true, 0x15C ],
		[ "Buttons Sticks"         , 4, true, 0x160 ],
		[ "Buttons Sticks"         , 4, true, 0x164 ],
		[ "Buttons Sticks"         , 4, true, 0x168 ],
		[ "Buttons Sticks"         , 4, true, 0x16C ],
		[ "Buttons Sticks"         , 4, true, 0x170 ],
		[ "Right Stick X"          , 4, true, 0x174 ],
		[ "Right Stick Y"          , 4, true, 0x178 ],
		[ "Left Stick X"           , 4, true, 0x17C ],
		[ "Left Stick Y"           , 4, true, 0x180 ],
	];
	var pos = 0x3C;
	for (var device = 0; device < 4; device++)
	{
	for (var item = 0; item < items.length; item++)
	{
		var description = "Device " + (device + 1).toString() + " " + items[item][0];
		var size        = items[item][1];
		var hex         = items[item][2];
		var off         = items[item][3];
		root.push([(pos + off), size, description, hex]);
	}
		pos += 0x2CC;
	}
}

function FeedGamepadData()
{
	var items =
	[
		[ "Start"                  , 4, true,    0 ],
		[ "Linked Device Address"  , 4, true,    4 ],
		[ "Buttons Sticks"         , 4, true, 0x14 ],
		[ "Buttons Sticks"         , 4, true, 0x18 ],
		[ "Buttons Sticks"         , 4, true, 0x1C ],
		[ "Buttons Sticks"         , 4, true, 0x20 ],
		[ "Left Stick X"           , 4, true, 0x24 ],
		[ "Left Stick Y"           , 4, true, 0x28 ],
		[ "Right Stick X"          , 4, true, 0x2C ],
		[ "Right Stick Y"          , 4, true, 0x30 ],
		[ "Pressure Y"             , 4, true, 0x44 ],
		[ "Pressure B"             , 4, true, 0x48 ],
		[ "Pressure A"             , 4, true, 0x4C ],
		[ "Pressure X"             , 4, true, 0x50 ],
		[ "Pressure Left Shoulder" , 4, true, 0x54 ],
		[ "Pressure Left Trigger"  , 4, true, 0x58 ],
		[ "Pressure Right Shoulder", 4, true, 0x5C ],
		[ "Pressure Right Trigger" , 4, true, 0x60 ],
		[ "Pressure Back"          , 4, true, 0x64 ],
		[ "Pressure Left Thumb"    , 4, true, 0x68 ],
		[ "Pressure Right Thumb"   , 4, true, 0x6C ],
	];
	var pos = 0xBC0;
	for (var device = 0; device < 2; device++)
	{
	for (var item = 0; item < items.length; item++)
	{
		var description = "Gamepad " + (device + 1).toString() + " " + items[item][0];
		var size        = items[item][1];
		var hex         = items[item][2];
		var off         = items[item][3];
		root.push([(pos + off), size, description, hex]);
	}
		pos += 0x200;
	}
}

FeedInternalData();
FeedDeviceData();
FeedGamepadData();

var c = "";

c += "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
c += "<CheatTable>\n";
c += "<CheatEntries>\n";

c += "<CheatEntry>\n";
c += "<Description>\"__INPUT__\"</Description>\n";
c += "<GroupHeader>1</GroupHeader>\n";
c += "<CheatEntries>\n";

var pos = 0;
var id  = 0;

for (var index = 0; index < 1000; index++)
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
				c += "2 Bytes";
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
			c += "<Address>dmc4.exe+F2432C</Address>\n";
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
	c += "<Address>dmc4.exe+F2432C</Address>\n";
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
