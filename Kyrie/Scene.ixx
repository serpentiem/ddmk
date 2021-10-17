export module Scene;

import Core;

#include "../Core/Macros.h"

import Actor;
import Config;
import Global;
import Vars;



struct SceneHelper
{
	const char * name;
	uint8 scene;
};

SceneHelper sceneHelpers[] =
{
	{ "nativeDX10\\sa\\DX10\\Title"        , SCENE::MAIN            },
	{ "nativeDX10\\sa\\DX10\\MissionSelect", SCENE::MISSION_SELECT  },
	{ "nativeDX10\\sa\\DX10\\DemoDigest"   , SCENE::CUTSCENE_SELECT },
	{ "nativeDX10\\sa\\DX10\\MissionTitle" , SCENE::MISSION_START   },
	{ "nativeDX10\\rom\\demo\\player"      , SCENE::CUTSCENE        },
	{ "nativeDX10\\sa\\DX10\\Room"         , SCENE::GAME            },
	{ "nativeDX10\\sa\\DX10\\GameOver"     , SCENE::GAME_OVER       },
	{ "nativeDX10\\sa\\DX10\\MissionResult", SCENE::MISSION_RESULT  },
};



void SceneMain()
{
	LogFunction();

	Actor::SceneMain();
}

void SceneMissionSelect()
{
	LogFunction();

	Actor::SceneMissionSelect();
}

void SceneCutsceneSelect()
{
	LogFunction();
}

void SceneMissionStart()
{
	LogFunction();
}

void SceneCutscene()
{
	LogFunction();
}

void SceneGame()
{
	LogFunction();
}

void SceneGameOver()
{
	LogFunction();
}

void SceneMissionResult()
{
	LogFunction();
}



export void SetScene(const char * location)
{
	for_all(index, countof(sceneHelpers))
	{
		auto & helper = sceneHelpers[index];

		if
		(
			IndexOf
			(
				location,
				helper.name
			) != -1
		)
		{
			g_scene = helper.scene;



			switch (g_scene)
			{
				case SCENE::MAIN:
				case SCENE::MISSION_SELECT:
				{
					CopyMemory
					(
						&activeConfig,
						&queuedConfig,
						sizeof(activeConfig)
					);

					break;
				}
			}

			switch (g_scene)
			{
				case SCENE::MAIN:
				{
					SceneMain();

					break;
				}
				case SCENE::MISSION_SELECT:
				{
					SceneMissionSelect();

					break;
				}
				case SCENE::CUTSCENE_SELECT:
				{
					SceneCutsceneSelect();

					break;
				}
				case SCENE::MISSION_START:
				{
					SceneMissionStart();

					break;
				}
				case SCENE::CUTSCENE:
				{
					SceneCutscene();

					break;
				}
				case SCENE::GAME:
				{
					SceneGame();

					break;
				}
				case SCENE::GAME_OVER:
				{
					SceneGameOver();

					break;
				}
				case SCENE::MISSION_RESULT:
				{
					SceneMissionResult();

					break;
				}
			}



			return;
		}
	}
}
