#pragma once
#include "DataTypes.h"

#define WINVER       0x0601
#define _WIN32_WINNT 0x0601
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <TlHelp32.h>

void ToggleCursor(bool enable);
bool GetWindowPos(HWND window, POINT * point);

inline bool Windows_GetTicksPerSecond(uint64 * var)
{
	return QueryPerformanceFrequency((LARGE_INTEGER *)var);
}

inline bool Windows_GetTickCount(uint64 * var)
{
	return QueryPerformanceCounter((LARGE_INTEGER *)var);
}
