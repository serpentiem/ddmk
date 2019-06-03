#pragma once
#include "DataTypes.h"
#include "String.h"
#include "../Windows/Windows.h"

extern const char * Log_directory;
extern const char * Log_file;
extern       char   Log_path[64];

template <typename ... Args>
void Log(const char * format, Args ... args)
{
	char timestamp[64];
	SYSTEMTIME st = {};
	GetLocalTime(&st);
	snprintf(timestamp, sizeof(timestamp), "%.2u:%.2u:%.2u.%.3u", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);

	char message[512];
	snprintf(message, sizeof(message), format, args ...);

	char buffer[2048];
	snprintf(buffer, sizeof(buffer), "%s %s\n", timestamp, message);

	HANDLE file = CreateFileA(Log_path, FILE_APPEND_DATA, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (file == INVALID_HANDLE_VALUE)
	{
		file = CreateFileA(Log_path, GENERIC_WRITE, 0, 0, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, 0);
		if (file == INVALID_HANDLE_VALUE)
		{
			return;
		}
	}
	DWORD bytesWritten = 0;
	OVERLAPPED overlap = {};
	WriteFile(file, buffer, (uint32)strlen(buffer), &bytesWritten, &overlap);
	CloseHandle(file);
}

#ifdef __clang__
char * GetFuncName(const char * prettyFunc);
#define FUNC_NAME GetFuncName(__PRETTY_FUNCTION__)
#else
#define FUNC_NAME __FUNCTION__
#endif

#define LogFunction() Log(FUNC_NAME)
#define LogFunctionBool(var) Log("%s %u", FUNC_NAME, var)

void Log_Init();
