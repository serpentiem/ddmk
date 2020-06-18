#include "Utility.h"

float32 hexstrtof(const char * str)
{
	if (strlen(str) != 8)
	{
		return 0;
	}
	float32 value = 0;
	char buffer[3];
	for (uint8 i = 0; i < 4; i++)
	{
		buffer[0] = str[(0 + (i * 2))];
		buffer[1] = str[(1 + (i * 2))];
		buffer[2] = 0;
		*(byte8 *)((byte8 *)&value + (3 - i)) = (byte8)strtoul(buffer, 0, 16);
	}
	return value;
}
