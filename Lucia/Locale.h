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
	struct
	{
		struct
		{
			const char * header = "Graphics";
			const char * frameRate = "Frame Rate";
			const char * frameRateHint = "Requires restart.";
			struct
			{
				const char * label = "V-Sync";
				const char * items[3] =
				{
					"Auto",
					"Force Off",
					"Force On",
				};
			}
			VSync;
		}
		Graphics;
		struct
		{
			const char * header = "Input";
			const char * hideMouseCursor = "Hide Mouse Cursor";
		}
		Input;
		struct
		{
			const char * header = "Window";
			const char * forceFocus = "Force Focus";
		}
		Window;
	}
	System;
};

extern LOCALE Locale;
