#pragma once
#include "../Core/Core.h"

struct LOCALE
{
	struct
	{
		const char * label[4] =
		{
			"Game",
			"System",
			"Tools",
			"Debug",
		};
	}
	Main;
};

extern LOCALE Locale;
