module;
#include "../Core/Core.h"

#include "Vars.h"
export module Global;

export bool  g_pause       = false;
export uint8 g_scene       = 0;
export bool  g_quicksilver = false;

export bool InGame()
{
	if (g_scene != SCENE_GAME)
	{
		return false;
	}

	IntroduceEventData(return false);

	if (eventData.event != EVENT_MAIN)
	{
		return false;
	}

	return true;
}

export auto & GetTurbo()
{
	return *reinterpret_cast<bool *>(appBaseAddr + 0xD6CEA9);
}

export auto & InCutscene()
{
	return *reinterpret_cast<bool *>(appBaseAddr + 0x5D113D);
}
