#include "Vergil.h"

void Cosmetics_Vergil_ToggleHideBeowulf(bool enable)
{
	Log("%s %u", FUNC_NAME, enable);
	if (enable)
	{
		WriteAddress((appBaseAddr + 0x2296AA), (appBaseAddr + 0x2296AC), 2); // Model
		Write<byte16>((appBaseAddr + 0x22357C), 0xE990);                       // Attributes
	}
	else
	{
		WriteAddress((appBaseAddr + 0x2296AA), (appBaseAddr + 0x2296BD), 2);
		Write<byte16>((appBaseAddr + 0x22357C), 0x850F);
	}
}
