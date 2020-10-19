// @Todo: Review.

module;
#include "../Core/Core.h"

#include "Vars.h"
export module State;

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
	IntroduceEventData(return false);
	if (eventData.event != EVENT_MAIN)
	{
		return false;
	}
	return true;
}
