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
				bool   hideCursor = true;
				uint32 updateRate = 10;
			}
			Mouse;
		}
		Input;
		struct
		{
			bool borderless = true;
		}
		Window;
	}
	System;
};
#pragma pack(pop)

extern CONFIG Config;
extern CONFIG DefaultConfig;
