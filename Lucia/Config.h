#pragma once
#include "../Core/Core.h"
#include "Vars.h"

#pragma pack(push, 1)
struct CONFIG
{
	struct
	{
		struct
		{
			struct
			{
				bool hideCursor = true;
			}
			Mouse;
		}
		Input;
	}
	System;
};
#pragma pack(pop)

extern CONFIG Config;
extern CONFIG DefaultConfig;
