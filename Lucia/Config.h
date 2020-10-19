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
			uint32 frameRate = 60;
			uint8  vSync     = 0;
		}
		Graphics;
		struct
		{
			bool hideMouseCursor = true;
		}
		Input;
		struct
		{
			bool forceFocus = true;
		}
		Window;
	}
	System;
};
#pragma pack(pop)

extern CONFIG Config;
extern CONFIG DefaultConfig;
