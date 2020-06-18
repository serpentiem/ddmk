#include "Includes.h"

Export Module(Core_Windows);

#include "DataTypes.h"

Export inline bool Windows_GetTicksPerSecond(uint64 * var)
{
	return QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER *>(var));
}

Export inline bool Windows_GetTickCount(uint64 * var)
{
	return QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER *>(var));
}

Export void Windows_ToggleCursor(bool enable)
{
	int32 counter = ShowCursor(false);
	if (counter < 0)
	{
		do
		{
			continue;
		}
		while (ShowCursor(true) < 0);
	}
	else
	{
		do
		{
			continue;
		}
		while (ShowCursor(false) > 0);
	}
	if (enable)
	{
		ShowCursor(true);
	}
	else
	{
		ShowCursor(false);
	}
}

Export bool Windows_GetWindowPos(HWND window, POINT * point)
{
	if (!window)
	{
		return false;
	}
	RECT rect = {};
	if (!GetWindowRect(window, &rect))
	{
		return false;
	}
	point->x = rect.left;
	point->y = rect.top;
	return true;
}
