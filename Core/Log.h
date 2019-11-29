
// @Research: Need something better. So I'll periodically add requirements here.
//            Colors, channels and better formatting. I don't want to create a log viewer, so I'm thinking html.
//            Doesn't have to be super fast. It's fine if it loads within 1s in Chromium.

// @Todo: Add LogWarning LogError and LogCriticalError.





#pragma once
#include "DataTypes.h"
#include "String.h"
#include "Windows.h"

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

	// @Todo: Replace with AppendFile.

	HANDLE file = CreateFileA(Log_path, FILE_APPEND_DATA, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (file == INVALID_HANDLE_VALUE)
	{
		file = CreateFileA(Log_path, GENERIC_WRITE, 0, 0, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, 0);
		if (file == INVALID_HANDLE_VALUE)
		{
			return;
		}
	}
	dword bytesWritten = 0;
	OVERLAPPED overlap = {};
	WriteFile(file, buffer, (uint32)strlen(buffer), &bytesWritten, &overlap);
	CloseHandle(file);
}

void LogNewLine();

#define FUNC_NAME __FUNCTION__

#define LogFunction() Log(FUNC_NAME)




#define LogFunctionStart() Log("%s Start", FUNC_NAME)
#define LogFunctionEnd() Log("%s End", FUNC_NAME)






#define LogFunctionUInt32(a) Log("%s %u", FUNC_NAME, a)
#define LogFunctionBool(a) LogFunctionUInt32(a)

void Log_Init();
