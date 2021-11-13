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



const char * sceneFuncNames[] =
{
	"SceneMain",
	"SceneMissionSelect",
	"SceneCutsceneSelect",
	"SceneMissionStart",
	"SceneCutscene",
	"SceneGame",
	"SceneGameOver",
	"SceneMissionResult",
};

static_assert(countof(sceneFuncNames) == SCENE::COUNT);



void SceneHandler()
{
	using namespace SCENE;

	auto scene = g_scene;
	if (scene >= COUNT)
	{
		Log("__UNKNOWN_SCENE__ %u", scene);

		return;
	}

	auto funcName = sceneFuncNames[scene];



	switch (scene)
	{
		case MAIN:
		case MISSION_SELECT:
		case MISSION_START:
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



	switch (scene)
	{
		case MAIN:
		{
			Log(funcName);

			Actor::SceneMain();

			break;
		}
		case MISSION_SELECT:
		{
			Log(funcName);

			Actor::SceneMissionSelect();

			break;
		}
		case CUTSCENE_SELECT:
		{
			Log(funcName);

			break;
		}
		case MISSION_START:
		{
			Log(funcName);

			Actor::SceneMissionStart();

			break;
		}
		case CUTSCENE:
		{
			Log(funcName);

			break;
		}
		case SCENE::GAME:
		{
			Log(funcName);

			break;
		}
		case GAME_OVER:
		{
			Log(funcName);

			break;
		}
		case MISSION_RESULT:
		{
			Log(funcName);

			break;
		}
	}
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

			SceneHandler();

			return;
		}
	}
}
