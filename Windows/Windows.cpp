#include "Windows.h"

void ToggleCursor(bool enable)
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

bool GetWindowPos(HWND window, POINT * point)
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
