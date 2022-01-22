module;
#include <string.h> // snprintf

#include "../Core/RapidJSON.h"

#include <initializer_list>
export module Exp;

import Core;

#include "../Core/Macros.h"

import Windows; // CreateDirectoryA

using namespace Windows;

import Config;
import Global;
import Vars;

#define debug false



const char * directoryName = "configs";
const char * fileName      = "Mary_Exp.json";

char location[64] = {};



export struct ExpData
{
	uint32 styleLevels[STYLE::MAX];
	float styleExpPoints[STYLE::MAX];
	bool unlocks[64];

	ExpData & operator=(ExpData & expData)
	{
		CopyMemory
		(
			this,
			&expData,
			sizeof(*this)
		);

		return *this;
	}

	ExpData & operator=(const std::initializer_list<int> &)
	{
		Log("Reset");

		SetMemory
		(
			this,
			0,
			sizeof(*this)
		);

		return *this;
	}
};

export ExpData missionExpDataDante           = {};
export ExpData sessionExpDataDante           = {};
export ExpData savedExpDataDante[SAVE_COUNT] = {};

export ExpData missionExpDataVergil           = {};
export ExpData sessionExpDataVergil           = {};
export ExpData savedExpDataVergil[SAVE_COUNT] = {};






bool Enable()
{
	return activeConfig.Actor.enable;
}

bool Max()
{
	return
	(
		activeConfig.absoluteUnit ||
		activeConfig.Arcade.enable
	);
}

















#pragma region JSON

namespaceStart(JSON);

#include "../Core/JSON.h"



#pragma region CreateMembers

void CreateMembers_ExpData
(
	rapidjson::Value & member,
	ExpData (&expData)[SAVE_COUNT]
)
{
	for_all(index, SAVE_COUNT)
	{
		auto & member2  = member [index];
		auto & expData2 = expData[index];

		CreateArray<uint32, STYLE::MAX>(member2, "styleLevels"   , expData2.styleLevels   );
		CreateArray<float , STYLE::MAX>(member2, "styleExpPoints", expData2.styleExpPoints);
		CreateArray<bool  , 64        >(member2, "unlocks"       , expData2.unlocks       );
	}
}

void CreateMembers()
{
	LogFunctionStart();

	CreateArray<struct_t, SAVE_COUNT>(root, "Dante");
	CreateMembers_ExpData(root["Dante"], savedExpDataDante);

	CreateArray<struct_t, SAVE_COUNT>(root, "Vergil");
	CreateMembers_ExpData(root["Vergil"], savedExpDataVergil);

	LogFunctionEnd();
}

#pragma endregion



#pragma region ToJSON

void ToJSON_ExpData
(
	rapidjson::Value & member,
	ExpData (&expData)[SAVE_COUNT]
)
{
	for_all(index, SAVE_COUNT)
	{
		auto & member2  = member [index];
		auto & expData2 = expData[index];

		SetArray<uint32, STYLE::MAX>(member2["styleLevels"   ], expData2.styleLevels   );
		SetArray<float , STYLE::MAX>(member2["styleExpPoints"], expData2.styleExpPoints);
		SetArray<bool  , 64        >(member2["unlocks"       ], expData2.unlocks       );
	}
}

void ToJSON()
{
	LogFunction();

	ToJSON_ExpData(root["Dante" ], savedExpDataDante );
	ToJSON_ExpData(root["Vergil"], savedExpDataVergil);
}

#pragma endregion



#pragma region ToExpData

void ToExp_ExpData
(
	ExpData (&expData)[SAVE_COUNT],
	rapidjson::Value & member
)
{
	for_all(index, SAVE_COUNT)
	{
		auto & member2  = member [index];
		auto & expData2 = expData[index];

		GetArray<uint32, STYLE::MAX>(expData2.styleLevels   , member2["styleLevels"   ]);
		GetArray<float , STYLE::MAX>(expData2.styleExpPoints, member2["styleExpPoints"]);
		GetArray<bool  , 64        >(expData2.unlocks       , member2["unlocks"       ]);
	}
}

void ToExp()
{
	LogFunction();

	ToExp_ExpData(savedExpDataDante , root["Dante" ]);
	ToExp_ExpData(savedExpDataVergil, root["Vergil"]);
}

#pragma endregion



namespaceEnd();

#pragma endregion






export void SaveExp()
{
	if
	(
		!Enable() ||
		Max()
	)
	{
		return;
	}

	LogFunction();



	auto saveIndex = g_saveIndex;
	if (saveIndex >= SAVE_COUNT)
	{
		return;
	}

	if (g_scene == SCENE::GAME)
	{
		sessionExpDataDante  = missionExpDataDante;
		sessionExpDataVergil = missionExpDataVergil;
	}

	savedExpDataDante [saveIndex] = sessionExpDataDante;
	savedExpDataVergil[saveIndex] = sessionExpDataVergil;



	using namespace rapidjson;
	using namespace JSON;



	ToJSON();



	StringBuffer stringBuffer;
	PrettyWriter<StringBuffer> prettyWriter(stringBuffer);

	root.Accept(prettyWriter);



	auto name = stringBuffer.GetString();
	auto size = strlen(name);

	if
	(
		!SaveFile
		(
			location,
			name,
			size
		)
	)
	{
		Log("SaveFile failed.");
	}
}



export void LoadExp()
{
	LogFunction();

	using namespace rapidjson;
	using namespace JSON;



	auto file = LoadFile(location);
	if (!file)
	{
		Log("LoadFile failed.");

		CreateMembers();

		SaveExp();

		return;
	}



	auto name = const_cast<const char *>(reinterpret_cast<char *>(file));

	if (root.Parse(name).HasParseError())
	{
		Log("Parse failed.");

		return;
	}



	CreateMembers();

	// At this point all file members have been applied. Extra or obsolete file members can exist.
	// If members were missing in the file they were created and have their default values.



	// The actual configs are still untouched though.
	// Let's update them!

	ToExp();



	auto saveIndex = g_saveIndex;
	if (saveIndex >= SAVE_COUNT)
	{
		return;
	}

	sessionExpDataDante  = savedExpDataDante [saveIndex];
	sessionExpDataVergil = savedExpDataVergil[saveIndex];
}



export void InitExp()
{
	LogFunction();

	using namespace rapidjson;
	using namespace JSON;

	CreateDirectoryA(directoryName, 0);

	snprintf
	(
		location,
		sizeof(location),
		"%s/%s",
		directoryName,
		fileName
	);

	root.SetObject();

	g_allocator = &root.GetAllocator();
}



struct ExpertiseHelper
{
	new_size_t index;
	byte32 flags;
};

ExpertiseHelper expertiseHelpersDanteSwordmasterLevel2[] =
{
	{ 0, 0x8000     },
	{ 1, 0x1000     },
	{ 2, 0x10000004 },
	{ 3, 0x30000000 },
};

ExpertiseHelper expertiseHelpersDanteSwordmasterLevel3[] =
{
	{ 0, 0x8000     },
	{ 1, 0x5000     },
	{ 2, 0x5000000C },
	{ 3, 0x30000000 },
	{ 4, 1          },
	{ 6, 0x100      },
};

ExpertiseHelper expertiseHelpersDanteGunslingerLevel2[] =
{
	{ 4, 0x4000000 },
	{ 5, 0x1000    },
};

ExpertiseHelper expertiseHelpersDanteGunslingerLevel3[] =
{
	{ 4, 0x4040000 },
	{ 5, 0x1002    },
};



ExpertiseHelper expertiseHelpersDante[] =
{
	{ 0, 0x80       },
	{ 0, 0x100      },
	{ 0, 0x2000     },
	{ 6, 0x40000    },

	{ 1, 0x40       },
	{ 1, 0x20       },

	{ 1, 0x4000000  },
	{ 1, 0x8000000  },
	{ 1, 0x40000000 },
	{ 6, 0x80000    },

	{ 2, 0x400000   },
	{ 2, 0x800000   },
	{ 2, 0x200000   },
	{ 3, 4          },
	{ 3, 2          },

	{ 3, 0x2000000  },
	{ 3, 0x200000   },
	{ 3, 0x400000   },
	{ 6, 0x100000   },
};



ExpertiseHelper expertiseHelpersVergil[] =
{
	{ 0, 0x10      },
	{ 0, 0x20      },
	{ 0, 0x200     },
	{ 0, 0x400     },

	{ 0, 0x800000  },
	{ 0, 0x2000000 },
	{ 0, 0x4000000 },

	{ 1, 4         },
	{ 1, 0x40      },
	{ 1, 0x80      },
	{ 1, 0x100     },

	{ 1, 0x40000   },
	{ 1, 0xC0000   },
	{ 1, 0x200000  },
};



struct LevelHelper
{
	new_size_t index;
	uint32 level;
};

LevelHelper levelHelpers[] =
{
	{ WEAPON::EBONY_IVORY, 1 },
	{ WEAPON::EBONY_IVORY, 2 },
	{ WEAPON::SHOTGUN    , 1 },
	{ WEAPON::SHOTGUN    , 2 },
	{ WEAPON::ARTEMIS    , 1 },
	{ WEAPON::ARTEMIS    , 2 },
	{ WEAPON::SPIRAL     , 1 },
	{ WEAPON::SPIRAL     , 2 },
	{ WEAPON::KALINA_ANN , 1 },
	{ WEAPON::KALINA_ANN , 2 },
};



export void SavePlayerActorExp()
{
	if
	(
		!Enable() ||
		Max()
	)
	{
		return;
	}



	// Only player 1's active actor can accumulate exp.
	// Default actors are not updated.

	IntroducePlayerCharacterNewActorData();

	IntroduceData(activeNewActorData.baseAddr, activeActorData, PlayerActorData, return);

	IntroducePlayerActorExpData(activeActorData, return);

	DebugLogFunction();

	expData.styleLevels   [style] = activeActorData.styleLevel;
	expData.styleExpPoints[style] = activeActorData.styleExpPoints;
}



export void UpdatePlayerActorExp(byte8 * actorBaseAddr)
{
	if (!Enable())
	{
		return;
	}



	IntroduceData(actorBaseAddr, actorData, PlayerActorData, return);

	IntroducePlayerActorExpData(actorData, return);

	auto & styleLevel     = actorData.styleLevel;
	auto & styleExpPoints = actorData.styleExpPoints;

	DebugLogFunction(actorBaseAddr);



	// Reset
	{
		actorData.styleLevel     = 0;
		actorData.styleExpPoints = 0;

		if (character == CHARACTER::DANTE)
		{
			actorData.activeExpertise[0] = 0xFFFF5E7F;
			actorData.activeExpertise[1] = 0xA7FFAF5F;
			actorData.activeExpertise[2] = 0xAF1FFFF3;
			actorData.activeExpertise[3] = 0xCB9FFFF9;
			actorData.activeExpertise[4] = 0xFBFBFFFE;
			actorData.activeExpertise[5] = 0xFFFFEFFD;
			actorData.activeExpertise[6] = 0xFFE3FEFF;
			actorData.activeExpertise[7] = 0xFFFFFFFF;
		}
		else if (character == CHARACTER::VERGIL)
		{
			actorData.activeExpertise[0] = 0xF4FFF9CF;
			actorData.activeExpertise[1] = 0xFFC7FE37;
			actorData.activeExpertise[2] = 0xFFFFFFFF;
			actorData.activeExpertise[3] = 0xFFFFFFFF;
			actorData.activeExpertise[4] = 0xFFFFFFFF;
			actorData.activeExpertise[5] = 0xFFFFFFFF;
			actorData.activeExpertise[6] = 0xFFFFFFFF;
			actorData.activeExpertise[7] = 0xFFFFFFFF;
		}

		SetMemory
		(
			actorData.newWeaponLevels,
			0,
			sizeof(actorData.newWeaponLevels)
		);
	}



	if (Max())
	{
		if
		(
			(actorData.style >= STYLE::SWORDMASTER) &&
			(actorData.style <= STYLE::ROYALGUARD )
		)
		{
			actorData.styleLevel = 2;
		}

		SetMemory
		(
			actorData.activeExpertise,
			0xFF,
			sizeof(actorData.activeExpertise)
		);

		if (actorData.character == CHARACTER::DANTE)
		{
			for_each(index, WEAPON::EBONY_IVORY, WEAPON_COUNT)
			{
				actorData.newWeaponLevels[index] = 2;
			}
		}

		return;
	}



	auto UpdateOnce = [&](ExpertiseHelper & helper)
	{
		actorData.activeExpertise[helper.index] += helper.flags; // Plus instead of or, because a custom bit size is used.
	};

	auto UpdateLoop = [&]
	(
		ExpertiseHelper * helpers,
		new_size_t helperCount
	)
	{
		for_all(helperIndex, helperCount)
		{
			auto & helper = helpers[helperIndex];

			UpdateOnce(helper);
		}
	};



	styleLevel     = expData.styleLevels   [style];
	styleExpPoints = expData.styleExpPoints[style];



	if (character == CHARACTER::DANTE)
	{
		switch (style)
		{
			case STYLE::SWORDMASTER:
			{
				if (styleLevel == 1)
				{
					UpdateLoop
					(
						expertiseHelpersDanteSwordmasterLevel2,
						countof(expertiseHelpersDanteSwordmasterLevel2)
					);
				}
				else if (styleLevel == 2)
				{
					UpdateLoop
					(
						expertiseHelpersDanteSwordmasterLevel3,
						countof(expertiseHelpersDanteSwordmasterLevel3)
					);
				}

				break;
			}
			case STYLE::GUNSLINGER:
			{
				if (styleLevel == 1)
				{
					UpdateLoop
					(
						expertiseHelpersDanteGunslingerLevel2,
						countof(expertiseHelpersDanteGunslingerLevel2)
					);
				}
				else if (styleLevel == 2)
				{
					UpdateLoop
					(
						expertiseHelpersDanteGunslingerLevel3,
						countof(expertiseHelpersDanteGunslingerLevel3)
					);
				}

				break;
			}
		}



		using namespace UNLOCK_DANTE;

		for_each(index, REBELLION_STINGER_LEVEL_1, EBONY_IVORY_LEVEL_2)
		{
			auto & unlock = expData.unlocks[index];
			if (!unlock)
			{
				continue;
			}

			auto & helper = expertiseHelpersDante[index];

			UpdateOnce(helper);
		}



		for_each(index, EBONY_IVORY_LEVEL_2, COUNT)
		{
			auto & unlock = expData.unlocks[index];
			if (!unlock)
			{
				continue;
			}

			auto & helper = levelHelpers[(index - EBONY_IVORY_LEVEL_2)];

			actorData.newWeaponLevels[helper.index] = helper.level;
		}
	}
	else if (character == CHARACTER::VERGIL)
	{
		using namespace UNLOCK_VERGIL;

		for_all(index, COUNT)
		{
			auto & unlock = expData.unlocks[index];
			if (!unlock)
			{
				continue;
			}

			auto & helper = expertiseHelpersVergil[index];

			UpdateOnce(helper);
		}
	}
}



export void UpdatePlayerActorExps()
{
	if (!Enable())
	{
		return;
	}



	DebugLogFunction();

	old_for_all(uint8, playerIndex   , PLAYER_COUNT   ){
	old_for_all(uint8, characterIndex, CHARACTER_COUNT){
	old_for_all(uint8, entityIndex   , ENTITY_COUNT   )
	{
		IntroducePlayerCharacterNewActorData(playerIndex, characterIndex, entityIndex);

		IntroduceData(newActorData.baseAddr, actorData, PlayerActorData, continue);

		UpdatePlayerActorExp(actorData);
	}}}
}








namespaceStart(Exp);

export void InitSession()
{
	if (!Enable())
	{
		return;
	}

	LogFunction();

	sessionExpDataDante  = {};
	sessionExpDataVergil = {};
}

export void SceneMissionStart()
{
	if (!Enable())
	{
		return;
	}

	LogFunction();

	missionExpDataDante  = sessionExpDataDante;
	missionExpDataVergil = sessionExpDataVergil;
}

export void SceneMissionResult()
{
	if (!Enable())
	{
		return;
	}

	LogFunction();

	sessionExpDataDante  = missionExpDataDante;
	sessionExpDataVergil = missionExpDataVergil;
}

export void IncStyleExpPoints(byte8 * actorBaseAddr)
{
	if (!Enable())
	{
		return;
	}

	DebugLogFunction(actorBaseAddr);

	SavePlayerActorExp();
}

namespaceEnd();























