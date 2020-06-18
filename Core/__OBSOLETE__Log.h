#pragma once
#include "DataTypes.h"
#include "String.h"
#include "Utility.h"
#include "Windows.h"

template <typename ... Args>
void Log(const char * format, Args ... args)
{
	extern char Core_Log_path[64];

	char timestamp[64];
	SYSTEMTIME st = {};
	GetLocalTime(&st);
	snprintf(timestamp, sizeof(timestamp), "%.2u:%.2u:%.2u.%.3u", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);

	char message[512];
	snprintf(message, sizeof(message), format, args ...);

	char buffer[2048];
	snprintf(buffer, sizeof(buffer), "%s %s\n", timestamp, message);

	// @Todo: Replace with AppendFile.

	HANDLE file = CreateFileA(Core_Log_path, FILE_APPEND_DATA, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (file == INVALID_HANDLE_VALUE)
	{
		file = CreateFileA(Core_Log_path, GENERIC_WRITE, 0, 0, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, 0);
		if (file == INVALID_HANDLE_VALUE)
		{
			return;
		}
	}
	byte32 bytesWritten = 0;
	OVERLAPPED overlap = {};
	WriteFile(file, buffer, (uint32)strlen(buffer), &bytesWritten, &overlap);
	CloseHandle(file);
}

inline void LogFunctionHelper(const char * funcName)
{
	Log(funcName);
}

template <typename T>
void LogFunctionHelper(const char * funcName, T var)
{
	if constexpr (typematch(T, byte8 *))
	{
		Log("%s %llX", funcName, var);
	}
	else if constexpr (typematch(T, const char *))
	{
		Log("%s %s", funcName, var);
	}
	else
	{
		Log("%s %u", funcName, var);
	}
}

#define FUNC_NAME __FUNCTION__

#define LogFunction(...) LogFunctionHelper(FUNC_NAME, __VA_ARGS__)

#define LogFunctionStart() Log("%s Start", FUNC_NAME)
#define LogFunctionEnd() Log("%s End", FUNC_NAME)

void Core_Log_Init
(
	const char * directoryName,
	const char * filename
);
