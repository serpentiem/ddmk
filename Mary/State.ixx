#ifndef __MODULE_STATE__
#define __MODULE_STATE__

module;
#include "../Core/Core.h"

#include "Vars.h"
export module ModuleName(State);

export inline bool ActorAvailable()
{
	auto pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);
	if (!pool)
	{
		return false;
	}
	if (!pool[3])
	{
		return false;
	}
	return true;
}

export inline bool InGame()
{
	if (!ActorAvailable())
	{
		return false;
	}
	IntroduceSceneData(return false);
	if (sceneData.scene != SCENE_MAIN)
	{
		return false;
	}
	return true;
}

#endif
