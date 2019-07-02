#pragma once
#include "DataTypes.h"

#define WINVER       0x0601
#define _WIN32_WINNT 0x0601
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <TlHelp32.h>

void ToggleCursor(bool enable);
bool GetWindowPos(HWND window, POINT * point);
