module;
#include "Includes.h"
export module Core_Log;

import Core_Utility;

#ifdef __INTELLISENSE__
#include "Utility.ixx"
#endif

export char Core_Log_path[64];

export template <typename ... Args>
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

export inline void LogFunctionHelper(const char * funcName)
{
	Log(funcName);
}

export template <typename T>
void LogFunctionHelper(const char * funcName, T var)
{
	if constexpr (TypeMatch<T, byte8 *>::value)
	{
		Log("%s %llX", funcName, var);
	}
	else if constexpr (TypeMatch<T, const char *>::value)
	{
		Log("%s %s", funcName, var);
	}
	else
	{
		Log("%s %u", funcName, var);
	}
}

export template
<
	typename T1,
	typename T2
>
void LogFunctionHelper
(
	const char * funcName,
	T1 var,
	T2 var2
)
{
	if constexpr
	(
		TypeMatch<T1, byte8 *>::value &&
		TypeMatch<T2, uint32>::value
	)
	{
		Log
		(
			"%s %llX %u",
			funcName,
			var,
			var2
		);
	}
	else
	{
		Log("%s %u %u", funcName, var, var2);
	}
}

export template
<
	typename T1,
	typename T2,
	typename T3
>
void LogFunctionHelper
(
	const char * funcName,
	T1 var,
	T2 var2,
	T3 var3
)
{
	Log("%s %u %u %u", funcName, var, var2, var3);
}

export void Core_Log_Init
(
	const char * directoryName,
	const char * filename
)
{
	CreateDirectoryA(directoryName, 0);
	snprintf(Core_Log_path, sizeof(Core_Log_path), "%s\\%s", directoryName, filename);
	DeleteFileA(Core_Log_path);
}
