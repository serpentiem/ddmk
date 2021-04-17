

// @Todo: Merge.



var fs = require("fs");

eval(fs.readFileSync("dmc3_core.js", "utf8"));

var items =
[
	[ "enemy", "uint32", 0 ],
	/*
	dmc3.exe+97B6D - 8B 03    - mov eax,[rbx]
	dmc3.exe+97B6F - 45 33 E4 - xor r12d,r12d
	*/

	[ "position", "vec4", 0x10 ],
	/*
	dmc3.exe+98005 - 41 0F28 87 20060000 - movaps xmm0,[r15+00000620]
	dmc3.exe+9800D - 33 F6               - xor esi,esi
	*/

	[ "rotation", "uint16", 0x20 ],
	/*
	dmc3.exe+9803C - 41 0FB7 87 30060000 - movzx eax,word ptr [r15+00000630]
	dmc3.exe+98044 - 8B 0B               - mov ecx,[rbx]
	*/

	[ "spawnMethod", "uint16", 0x22 ],
	/*
	dmc3.exe+6843B - 0FB7 41 22 - movzx eax,word ptr [rcx+22]
	dmc3.exe+6843F - 83 F8 63   - cmp eax,63
	*/

	[ "variant", "uint32", 0x28 ],
	/*
	dmc3.exe+9836D - 41 39 B7 38060000 - cmp [r15+00000638],esi
	dmc3.exe+98374 - 74 64             - je dmc3.exe+983DA
	*/
];

var filename = "../Mary/Vars.h"

var file = fs.readFileSync(filename, "utf8");

var lines = file.match(/[\S\s]*?\r\n/g);

if
(
	!Tag_Init
	(
		lines,
		/\/\/ \$CreateEnemyDataStart$/,
		/\/\/ \$CreateEnemyDataEnd$/
	)
)
{
	console.log("Tag_Init failed.");

	return;
}

Tag_CopyUntil(lines);

CreateStruct
(
	"CreateEnemyData",
	128,
	items
);

Tag_CopyAfter(lines);

fs.writeFileSync(filename, c);
