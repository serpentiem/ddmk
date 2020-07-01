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
	auto pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E10);
	if (!pool)
	{
		return false;
	}
	if (!pool[8])
	{
		return false;
	}
	auto & eventData = *reinterpret_cast<EVENT_DATA *>(pool[8]);
	if (eventData.index != EVENT_MAIN)
	{
		return false;
	}
	return true;
}

#endif
