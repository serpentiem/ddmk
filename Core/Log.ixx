// @Todo: Merge File, Log and Memory when doing the Windows module.

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
void LogFunctionHelper
(
	const char * funcName,
	T var
)
{
	const char * format =
	(TypeMatch<T, byte8 *>::value) ? "%s %llX" :
	"%s %u";

	Log(format, funcName, var);
}

export template
<
typename T,
typename T2
>
void LogFunctionHelper
(
	const char * funcName,
	T var,
	T2 var2
)
{
	char format[128] = {};
	uint32 pos = 0;

	auto Feed = [&](const char * name)
	{
		auto size = static_cast<uint32>(strlen(name));

		memcpy
		(
			(format + pos),
			name,
			size
		);

		pos += size;
	};

	Feed("%s ");

	if constexpr (TypeMatch<T, byte8 *>::value)
	{
		Feed("%llX ");
	}
	else if constexpr (TypeMatch<T, float>::value)
	{
		Feed("%g ");
	}
	else
	{
		Feed("%u ");
	}

	if constexpr (TypeMatch<T2, byte8 *>::value)
	{
		Feed("%llX");
	}
	else if constexpr (TypeMatch<T2, float>::value)
	{
		Feed("%g");
	}
	else
	{
		Feed("%u");
	}

	Log(format, funcName, var, var2);
}




// export template
// <
// 	typename T,
// 	typename T2
// >
// void LogFunctionHelper
// (
// 	const char * funcName,
// 	T var,
// 	T2 var2
// )
// {
// 	if constexpr
// 	(
// 		TypeMatch<T, byte8 *>::value &&
// 		TypeMatch<T2, uint32>::value
// 	)
// 	{
// 		Log
// 		(
// 			"%s %llX %u",
// 			funcName,
// 			var,
// 			var2
// 		);
// 	}
// 	else
// 	{
// 		Log("%s %u %u", funcName, var, var2);
// 	}
// }

// export template
// <
// 	typename T1,
// 	typename T2,
// 	typename T3
// >
// void LogFunctionHelper
// (
// 	const char * funcName,
// 	T1 var,
// 	T2 var2,
// 	T3 var3
// )
// {
// 	Log("%s %u %u %u", funcName, var, var2, var3);
// }

export template <typename ... Args>
void Print(const char * format, Args ... args)
{
	char buffer[512];

	snprintf(buffer, sizeof(buffer), format, args ...);

	printf("%s\n", buffer);
}

export inline void PrintFunctionHelper(const char * funcName)
{
	Print(funcName);
}

export template <typename T>
void PrintFunctionHelper
(
	const char * funcName,
	T var
)
{
	const char * format =
	(TypeMatch<T, byte8 *>::value) ? "%s %llX" :
	"%s %u";

	Print(format, funcName, var);
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
