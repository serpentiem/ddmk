#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma region Windows

#define SetMemory Windows_SetMemory
#define CopyMemory Windows_CopyMemory
#define GetFileSize Windows_GetFileSize

#pragma warning(push)
#pragma warning(disable:4005)

#define WINVER 0x0601
#define _WIN32_WINNT 0x0601
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#pragma warning(pop)

#undef SetMemory
#undef CopyMemory
#undef GetFileSize

#pragma endregion

#include <TlHelp32.h>

#include "Datatypes.h"
#include "Macros.h"
