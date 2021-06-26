let fs = require("fs");
let vm = require("vm");

vm.runInThisContext(fs.readFileSync("core.js", "utf8"));

ClearAll();



function CreateData(actorIndex)
{
	GroupStart(lz(actorIndex));

	for (let index = 0; index < 8; index++)
	{
		let off = 0x30 + (16 * index);

		let offName = PositionName
		(
			(off + 0),
			PositionFlags_Hex |
			PositionFlags_NoPrefix
		);

		CreateCheatEntry
		(
			"data[" + index + "] x",
			false,
			"Float",
			"Mary.Global::g_playerActorBaseAddrs",
			[
				offName + "+0",
				"7250+88",
				"8*" + actorIndex,
			]
		);

		CreateCheatEntry
		(
			"data[" + index + "] y",
			false,
			"Float",
			"Mary.Global::g_playerActorBaseAddrs",
			[
				offName + "+4",
				"7250+88",
				"8*" + actorIndex,
			]
		);

		CreateCheatEntry
		(
			"data[" + index + "] z",
			false,
			"Float",
			"Mary.Global::g_playerActorBaseAddrs",
			[
				offName + "+8",
				"7250+88",
				"8*" + actorIndex,
			]
		);

		CreateCheatEntry
		(
			"data[" + index + "] a",
			false,
			"Float",
			"Mary.Global::g_playerActorBaseAddrs",
			[
				offName + "+C",
				"7250+88",
				"8*" + actorIndex,
			]
		);
	}



	for (let index = 0; index < 3; index++)
	{
		let off = 0xE0 + (16 * index);

		let offName = PositionName
		(
			(off + 0),
			PositionFlags_Hex |
			PositionFlags_NoPrefix
		);

		CreateCheatEntry
		(
			"data2[" + index + "] x",
			false,
			"Float",
			"Mary.Global::g_playerActorBaseAddrs",
			[
				offName + "+0",
				"7250+88",
				"8*" + actorIndex,
			]
		);

		CreateCheatEntry
		(
			"data2[" + index + "] y",
			false,
			"Float",
			"Mary.Global::g_playerActorBaseAddrs",
			[
				offName + "+4",
				"7250+88",
				"8*" + actorIndex,
			]
		);

		CreateCheatEntry
		(
			"data2[" + index + "] z",
			false,
			"Float",
			"Mary.Global::g_playerActorBaseAddrs",
			[
				offName + "+8",
				"7250+88",
				"8*" + actorIndex,
			]
		);

		CreateCheatEntry
		(
			"data2[" + index + "] a",
			false,
			"Float",
			"Mary.Global::g_playerActorBaseAddrs",
			[
				offName + "+C",
				"7250+88",
				"8*" + actorIndex,
			]
		);
	}

	GroupEnd();
}



CheatTableStart();

CreateData(2);
CreateData(4);

CheatTableEnd();

fs.writeFileSync("collision_data.txt", c);
