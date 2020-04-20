#pragma once
#include "../Core/Core.h"

#include "Vars.h"

inline bool ActorAvailable()
{
	auto pool = reinterpret_cast<byte8 **>(appBaseAddr + 0xC90E28);
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

inline bool InGame()
{
	if (!ActorAvailable())
	{
		return false;
	}
	// @Todo: Update pointer!
	auto pool = reinterpret_cast<byte8 **>(appBaseAddr + 0xCA8918);
	if (!pool)
	{
		return false;
	}
	if (!pool[8])
	{
		return false;
	}
	auto & event = *reinterpret_cast<byte32 *>(pool[8] + 0x20);
	if (event != EVENT_GAME)
	{
		return false;
	}
	return true;
}
