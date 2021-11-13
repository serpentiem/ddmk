// @Todo: Update logging.
// @Todo: Create IsInvalidHandle function.
// @Todo: Update Inits.
// @Todo: Update LogFunctionHelpers.

module;
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <xmmintrin.h>
export module Core;

export import DataTypes;

#include "Macros.h"

import Windows;

using namespace Windows;

#define debug false

export template <typename ... Args>
void Log(const char * format, Args ... args);

export void LogFunctionHelper(const char * funcName);

export template <typename T>
void LogFunctionHelper
(
	const char * funcName,
	T var
);

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
);

#pragma region Utility

export template
<
	typename T1,
	typename T2
>
struct TypeMatch
{
	static constexpr bool value = false;
};

export template <typename T>
struct TypeMatch<T, T>
{
	static constexpr bool value = true;
};

export template <size_t T>
struct TypeValue
{
	static constexpr auto value = T;
};

export template
<
	typename T,
	size_t count
>
constexpr auto countof(T (&)[count])
{
	return count;
}

// export struct SizeData
// {
// 	uint32 width;
// 	uint32 height;
// 	vec2 size;

// 	void Update
// 	(
// 		uint32 newWidth,
// 		uint32 newHeight
// 	)
// 	{
// 		width = newWidth;
// 		height = newHeight;
// 		size =
// 		{
// 			static_cast<float>(width),
// 			static_cast<float>(height)
// 		};
// 	}
// };

export struct TimeData
{
	uint32 milliseconds;
	uint32 seconds;
	uint32 minutes;
	uint32 hours;

	TimeData
	(
		float frameCount,
		float frameRate
	)
	{
		constexpr uint32 oneSecond = 1000;
		constexpr uint32 oneMinute = (60 * oneSecond);
		constexpr uint32 oneHour = (60 * oneMinute);

		auto time = static_cast<uint32>((frameCount / frameRate) * 1000.0f);

		hours = (time / oneHour);
		time -= (hours * oneHour);

		minutes = (time / oneMinute);
		time -= (minutes * oneMinute);

		seconds = (time / oneSecond);
		time -= (seconds * oneSecond);

		milliseconds = time;
	}
};

export template
<
	typename T,
	uint8 count
>
bool SignatureMatch
(
	byte8 * signature,
	T(&array)[count]
)
{
	uint8 signatureIndex = 0;

	while (signatureIndex < count)
	{
		if (signature[signatureIndex] != array[signatureIndex])
		{
			break;
		}

		signatureIndex++;
	}

	return (signatureIndex == count);
}


export bool Match
(
	const void * addr,
	const void * addr2,
	uint32 count
)
{
	old_for_all(uint32, index, count)
	{
		if
		(
			reinterpret_cast<byte8 *>(const_cast<void *>(addr ))[index] !=
			reinterpret_cast<byte8 *>(const_cast<void *>(addr2))[index]
		)
		{
			return false;
		}
	}

	return true;
}


export template <uint32 count>
constexpr uint32 ctstrlen(const char (&name)[count])
{
	return (count - 1);
}













// @Research: Consider reference.
export template <typename T>
T Reverse(T * varAddr)
{
	constexpr uint8 size = static_cast<uint8>(sizeof(T));

	T var = 0;

	old_for_all(uint8, index, size)
	{
		reinterpret_cast<byte8 *>(&var)[index] = reinterpret_cast<byte8 *>(varAddr)[(size - 1 - index)];
	}

	return var;
}



export template
<
	typename varType,
	uint8 mapItemCount
>
void UpdateMapIndex
(
	const varType(&map)[mapItemCount],
	uint8 & index,
	varType & var
)
{
	//LogFunction();

	old_for_all(uint8, mapIndex, mapItemCount)
	{
		auto & mapItem = map[mapIndex];
		if (mapItem == var)
		{
			index = mapIndex;
			return;
		}
	}

	Log("No match.");
}




















#pragma endregion

#pragma region Memory

export enum
{
	RAX,
	RCX,
	RDX,
	RBX,
	RSP,
	RBP,
	RSI,
	RDI,
	R8,
	R9,
	R10,
	R11,
	R12,
	R13,
	R14,
	R15,
	MAX_REGISTER,
};

export byte8  * appBaseAddr = 0;
export uint32   appSize     = 0;
export HWND     appWindow   = 0;

SYSTEM_INFO systemInfo = {};



export void SetMemory
(
	void * addr,
	byte8 value,
	size_t size
)
{
	memset
	(
		addr,
		value,
		size
	);
}

export void CopyMemory
(
	void * destination,
	const void * source,
	size_t size
)
{
	memcpy
	(
		destination,
		source,
		size
	);
}

export template <typename T>
T Align
(
	T & pos,
	T boundary,
	byte8 * addr = 0,
	byte8 padValue = 0
)
{
	T remainder = (pos % boundary);

	if (remainder)
	{
		T size = (boundary - remainder);

		if (addr)
		{
			SetMemory
			(
				(addr + pos),
				padValue,
				size
			);
		}

		pos += size;
	}

	return remainder;
}

export byte8 * Alloc
(
	size_t size,
	byte8 * dest = 0
)
{
	byte8 * addr = 0;
	byte32 error = 0;

	SetLastError(0);

	addr = reinterpret_cast<byte8 *>
	(
		VirtualAlloc
		(
			dest,
			size,
			MEM_COMMIT | MEM_RESERVE,
			PAGE_EXECUTE_READWRITE
		)
	);

	error = GetLastError();

	if (!addr)
	{
		Log("VirtualAlloc failed. %X", error);
	}

	return addr;
}

export byte8 * AllocEx
(
	size_t size,
	off_t start,
	off_t end
)
{
	if constexpr (debug)
	{
		LogFunction();

		Log("size  %llX", size);
		Log("start %llX", start);
		Log("end   %llX", end);
	}

	byte8 * addr = 0;

	auto pos = start;

	MEMORY_BASIC_INFORMATION mbi = {};
	bool match = false;
	byte32 error = 0;

	do
	{
		SetLastError(0);

		if
		(
			VirtualQuery
			(
				reinterpret_cast<void *>(pos),
				&mbi,
				sizeof(mbi)
			) == 0
		)
		{
			error = GetLastError();

			Log("VirtualQuery failed. %X", error);
		}

		if
		(
			(mbi.RegionSize >= size) &&
			(mbi.State == MEM_FREE)
		)
		{
			if constexpr (debug)
			{
				Log("pos        %llX", pos);
				Log("regionSize %llX", mbi.RegionSize);
				Log("state      %X", mbi.State);
			}

			auto remainder = Align<off_t>(pos, systemInfo.dwAllocationGranularity);
			if (!remainder)
			{
				match = true;

				break;
			}

			continue;
		}

		pos += mbi.RegionSize;
	}
	while (pos < end);

	if (!match)
	{
		return 0;
	}

	addr = reinterpret_cast<byte8 *>(mbi.BaseAddress);

	addr = Alloc(size, addr);

	SetLastError(0);

	if
	(
		VirtualQuery
		(
			addr,
			&mbi,
			sizeof(mbi)
		) == 0
	)
	{
		error = GetLastError();

		Log("VirtualQuery failed. %X", error);
	}

	if constexpr (debug)
	{
		Log("addr  %llX", addr);
		Log("state %X", mbi.State);
	}

	return addr;
}

export auto LowAlloc(size_t size)
{
	return AllocEx
	(
		size,
		0x10000,
		0x7FFFFFFF
	);
}

export auto HighAlloc(size_t size)
{
	return AllocEx
	(
		size,
		reinterpret_cast<off_t>(appBaseAddr + appSize),
		reinterpret_cast<off_t>(appBaseAddr + 0x7FFFFFFF)
	);
}

export bool Free(byte8 * addr)
{
	if (!addr)
	{
		return false;
	}

	byte32 error = 0;

	SetLastError(0);

	if
	(
		!VirtualFree
		(
			addr,
			0,
			MEM_RELEASE
		)
	)
	{
		error = GetLastError();

		Log("VirtualFree failed. %X", error);

		return false;
	}

	return true;
}

#pragma endregion

#pragma region File

// @Todo: Remove logging.

export enum
{
	FileFlags_Read   = 1 << 0,
	FileFlags_Write  = 1 << 1,
	FileFlags_Append = 1 << 2,
};

export HANDLE OpenFile
(
	const char * name,
	byte32 flags
)
{
	if constexpr (debug)
	{
		// LogFunction();
		// Log("name  %s", name);
		// Log("flags %X", flags);
	}

	byte32 error = 0;
	HANDLE file = 0;

	SetLastError(0);

	if (flags & FileFlags_Read)
	{
		file = CreateFileA
		(
			name,
			GENERIC_READ,
			0,
			0,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			0
		);
	}
	else if (flags & FileFlags_Write)
	{
		file = CreateFileA
		(
			name,
			GENERIC_WRITE,
			0,
			0,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			0
		);
	}
	else if (flags & FileFlags_Append)
	{
		file = CreateFileA
		(
			name,
			FILE_APPEND_DATA,
			0,
			0,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			0
		);
	}

	if (file == reinterpret_cast<HANDLE>(INVALID_HANDLE_VALUE))
	{
		error = GetLastError();

		// Log
		// (
		// 	"CreateFile failed. %X %s %X",
		// 	error,
		// 	name,
		// 	flags
		// );

		return reinterpret_cast<HANDLE>(INVALID_HANDLE_VALUE);
	}

	return file;
}

export bool CloseFile(HANDLE file)
{
	if constexpr (debug)
	{
		// LogFunction();
		// Log("file %llX", file);
	}

	if (file == reinterpret_cast<HANDLE>(INVALID_HANDLE_VALUE))
	{
		return 0;
	}

	byte32 error = 0;

	SetLastError(0);

	if (!CloseHandle(file))
	{
		error = GetLastError();

		//Log("CloseHandle failed. %X", error);

		return false;
	}

	return true;
}


#ifdef _WIN64


export size_t GetFileSize(HANDLE file)
{
	if constexpr (debug)
	{
		// LogFunction();
		// Log("file %llX", file);
	}

	if (file == reinterpret_cast<HANDLE>(INVALID_HANDLE_VALUE))
	{
		return 0;
	}

	byte32 error = 0;
	BY_HANDLE_FILE_INFORMATION fileInformation = {};

	SetLastError(0);

	if
	(
		!GetFileInformationByHandle
		(
			file,
			&fileInformation
		)
	)
	{
		error = GetLastError();

		//Log("GetFileInformationByHandle failed. %X", error);

		return 0;
	}

	size_t size = 0;

	auto sizeAddr = reinterpret_cast<byte8 *>(&size);

	CopyMemory
	(
		sizeAddr,
		&fileInformation.nFileSizeLow,
		4
	);

	CopyMemory
	(
		(sizeAddr + 4),
		&fileInformation.nFileSizeHigh,
		4
	);

	return size;
}




#else


export size_t GetFileSize(HANDLE file)
{
	if constexpr (debug)
	{
		// LogFunction();
		// Log("file %llX", file);
	}

	if (file == reinterpret_cast<HANDLE>(INVALID_HANDLE_VALUE))
	{
		return 0;
	}

	byte32 error = 0;
	BY_HANDLE_FILE_INFORMATION fileInformation = {};

	SetLastError(0);

	if
	(
		!GetFileInformationByHandle
		(
			file,
			&fileInformation
		)
	)
	{
		error = GetLastError();

		char buffer[64];

		snprintf
		(
			buffer,
			sizeof(buffer),
			"bruh %X",
			error
		);

		MessageBoxA(0, buffer, 0, 0);

		//Log("GetFileInformationByHandle failed. %X", error);

		return 0;
	}



	return fileInformation.nFileSizeLow;


	// size_t size = 0;

	// auto sizeAddr = reinterpret_cast<byte8 *>(&size);

	// CopyMemory
	// (
	// 	sizeAddr,
	// 	&fileInformation.nFileSizeLow,
	// 	4
	// );

	// CopyMemory
	// (
	// 	(sizeAddr + 4),
	// 	&fileInformation.nFileSizeHigh,
	// 	4
	// );

	// return size;
}























#endif


















export bool LoadFile
(
	HANDLE file,
	size_t size,
	void * dest,
	off_t start = 0
)
{
	if constexpr (debug)
	{
		// LogFunction();
		// Log("file  %llX", file);
		// Log("size  %llu", size);
		// Log("dest  %llX", dest);
		// Log("start %llX", start);
	}

	if
	(
		(file == reinterpret_cast<HANDLE>(INVALID_HANDLE_VALUE)) ||
		(size == 0) ||
		!dest
	)
	{
		return false;
	}

	byte32 error = 0;
	constexpr size_t bufferSize = (1 * 1024 * 1024);
	auto pos = start;
	uint32 bytesRead = 0;
	LARGE_INTEGER filePointer = {};

	auto Function = [&](size_t size2) -> bool
	{



		SetLastError(0);

		if
		(
			!SetFilePointerEx
			(
				file,
				*reinterpret_cast<LARGE_INTEGER *>(&pos),
				&filePointer,
				FILE_BEGIN
			)
		)
		{
			error = GetLastError();

			//Log("SetFilePointerEx failed. %X", error);

			return false;
		}







		SetLastError(0);

		if
		(
			!ReadFile
			(
				file,
				(reinterpret_cast<byte8 *>(dest) + pos),
				static_cast<uint32>(size2),
				&bytesRead,
				0
			)
		)
		{
			error = GetLastError();

			//Log("ReadFile failed. %X", error);

			return false;
		}

		pos += size2;
		size -= size2;



		return true;
	};

	while (size > bufferSize)
	{
		if (!Function(bufferSize))
		{
			return false;
		}
	}

	if (size > 0)
	{
		if (!Function(size))
		{
			return false;
		}
	}

	return true;
}

export byte8 * LoadFile
(
	HANDLE file,
	size_t size,
	off_t start = 0
)
{
	if constexpr (debug)
	{
		// LogFunction();
		// Log("file  %llX", file);
		// Log("size  %llu", size);
		// Log("start %llX", start);
	}

	auto dest = Alloc(size);
	if (!dest)
	{
		return 0;
	}

	if
	(
		!LoadFile
		(
			file,
			size,
			dest,
			start
		)
	)
	{
		//Log("LoadFile failed.");

		Free(dest);

		return 0;
	}

	return dest;
}

export byte8 * LoadFile(const char * name)
{
	if constexpr (debug)
	{
		// LogFunction();
		// Log("name %s", name);
	}

	if (!name)
	{
		return 0;
	}

	byte32 error = 0;
	HANDLE file = 0;
	size_t size = 0;
	byte8 * dest = 0;

	file = OpenFile
	(
		name,
		FileFlags_Read
	);
	if (file == reinterpret_cast<HANDLE>(INVALID_HANDLE_VALUE))
	{
		//Log("OpenFile failed. %s", name);

		return 0;
	}

	size = GetFileSize(file);
	if (size == 0)
	{
		return 0;
	}

	dest = LoadFile
	(
		file,
		size
	);
	if (!dest)
	{
		return 0;
	}

	if (!CloseFile(file))
	{
		//Log("CloseFile failed. %s", name);
	}

	return dest;
}





export bool SaveFile
(
	HANDLE file,
	void * addr,
	size_t size
)
{
	if
	(
		(file == reinterpret_cast<HANDLE>(INVALID_HANDLE_VALUE)) ||
		!addr ||
		(size == 0)
	)
	{
		return false;
	}

	constexpr size_t bufferSize = (1 * 1024 * 1024);
	off_t pos = 0;
	uint32 bytesWritten = 0;
	LARGE_INTEGER filePointer = {};

	auto Function = [&](size_t size2) -> bool
	{
		if
		(
			!WriteFile
			(
				file,
				(reinterpret_cast<byte8 *>(addr) + pos),
				static_cast<uint32>(size2),
				&bytesWritten,
				0
			)
		)
		{
			return false;
		}

		pos += size2;
		size -= size2;

		return true;
	};

	while (size > bufferSize)
	{
		if (!Function(bufferSize))
		{
			return false;
		}
	}

	if (size > 0)
	{
		if (!Function(size))
		{
			return false;
		}
	}

	return true;
}

export bool SaveFile
(
	const char * name,
	void * addr,
	size_t size,
	byte32 flags = FileFlags_Write
)
{
	if
	(
		!name ||
		!addr ||
		(size == 0)
	)
	{
		return false;
	}

	HANDLE file = 0;

	file = OpenFile
	(
		name,
		flags
	);
	if (file == reinterpret_cast<HANDLE>(INVALID_HANDLE_VALUE))
	{
		return false;
	}

	SaveFile
	(
		file,
		addr,
		size
	);

	return CloseFile(file);
}

#pragma endregion

#pragma region Log

bool logInit = false;

char logPath[64] = {};

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

	if
	(
		!SaveFile
		(
			logPath,
			buffer,
			strlen(buffer),
			FileFlags_Append
		)
	)
	{
		OutputDebugStringA("Append failed.");

		if
		(
			!SaveFile
			(
				logPath,
				buffer,
				strlen(buffer),
				FileFlags_Write
			)
		)
		{
			OutputDebugStringA("Write failed.");

			return;
		}
	}
}

void LogFunctionHelper(const char * funcName)
{
	Log(funcName);
}

template <typename T>
void LogFunctionHelper
(
	const char * funcName,
	T var
)
{
	#ifdef _WIN64

	const char * format =
	(TypeMatch<T, byte8 *>::value) ? "%s %llX" :
	"%s %u";

	#else

	const char * format =
	(TypeMatch<T, byte8 *>::value) ? "%s %X" :
	"%s %u";

	#endif

	Log(format, funcName, var);
}

template
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

export void Core_Log_Init
(
	const char * directoryName,
	const char * filename
)
{
	CreateDirectoryA(directoryName, 0);
	snprintf(logPath, sizeof(logPath), "%s\\%s", directoryName, filename);
	DeleteFileA(logPath);

	logInit = true;
}

#pragma endregion

#pragma region Containers

// @Todo: virtual Push & Pop.

export template <typename ...>
struct Container;

export template <>
struct Container<>
{
	struct Metadata
	{
		off_t off;
		size_t size;
	};

	byte8 * dataAddr;
	size_t dataSize;

	byte8 * metadataAddr;
	size_t metadataSize;

	off_t pos;
	size_t count;

	// @Todo: Add alloc func arg.
	bool InitData(size_t size);
	bool InitMetadata(size_t size);
	bool Init
	(
		size_t dataSize2,
		size_t metadataSize2
	);
	void Clear();
	byte8 * Next(size_t size = 0);


	


	void Push
	(
		void * addr,
		size_t size
	);
	void Pop();
	byte8 * operator[](size_t index);



byte8 * Last();



};

bool Container<>::InitData(size_t size)
{
	if (size == 0)
	{
		return false;
	}

	dataAddr = HighAlloc(size);
	if (!dataAddr)
	{
		return false;
	}

	dataSize = size;

	return true;
}

bool Container<>::InitMetadata(size_t size)
{
	if (size == 0)
	{
		return false;
	}

	metadataAddr = HighAlloc(size);
	if (!metadataAddr)
	{
		return false;
	}

	metadataSize = size;

	return true;
}

bool Container<>::Init
(
	size_t dataSize2,
	size_t metadataSize2
)
{
	if
	(
		(dataSize2 == 0) ||
		!InitData(dataSize2) ||
		(metadataSize2 == 0) ||
		!InitMetadata(metadataSize2)
	)
	{
		return false;
	}

	return true;
}

void Container<>::Clear()
{
	if (dataAddr)
	{
		SetMemory
		(
			dataAddr,
			0,
			dataSize
		);
	}

	if (metadataAddr)
	{
		SetMemory
		(
			metadataAddr,
			0,
			metadataSize
		);
	}

	pos = 0;
	count = 0;
}

byte8 * Container<>::Next(size_t size)
{
	if
	(
		!dataAddr ||
		(dataSize == 0) ||
		(size > dataSize) ||
		(pos > (dataSize - size))
	)
	{
		return 0;
	}

	return (dataAddr + pos);
}









void Container<>::Push
(
	void * addr,
	size_t size
)
{
	if
	(
		!dataAddr ||
		(dataSize == 0) ||
		!metadataAddr ||
		(metadataSize == 0) ||
		!addr ||
		(size == 0) ||
		(pos > (dataSize - size))
	)
	{
		return;
	}

	CopyMemory
	(
		(dataAddr + pos),
		addr,
		size
	);

	auto & metadata = reinterpret_cast<Metadata *>(metadataAddr)[count];

	metadata.off = pos;
	metadata.size = size;

	pos += size;

	count++;
}

void Container<>::Pop()
{
	if
	(
		!dataAddr ||
		!metadataAddr ||
		(count < 1)
	)
	{
		return;
	}

	auto & metadata = reinterpret_cast<Metadata *>(metadataAddr)[(count - 1)];

	SetMemory
	(
		(dataAddr + metadata.off),
		0,
		metadata.size
	);

	pos -= metadata.size;

	SetMemory
	(
		&metadata,
		0,
		sizeof(metadata)
	);

	count--;
}

byte8 * Container<>::operator[](size_t index)
{
	if
	(
		!dataAddr ||
		!metadataAddr ||
		(index >= count)
	)
	{
		return 0;
	}

	auto & metadata = reinterpret_cast<Metadata *>(metadataAddr)[index];

	return (dataAddr + metadata.off);
}



byte8 * Container<>::Last()
{
	if
	(
		!dataAddr ||
		(dataSize == 0) ||
		!metadataAddr ||
		(metadataSize == 0) ||
		(count < 1)
	)
	{
		return 0;
	}

	return (*this)[(count - 1)];
}
























// @Todo: Add Extend.
// @Todo: Add += and -- operator I guess.
export template <typename T>
struct Container<T>
{
	T * dataAddr;
	size_t dataSize;
	size_t count;
	size_t capacity;

	bool Init(size_t size);
	void Push(const T & var);
	void Pop();


	void Remove(size_t index)
	{
		if
		(
			(count == 0) ||
			(index >= count)
		)
		{
			return;
		}

		auto remainingCount = (count - index - 1);

		if (remainingCount == 0)
		{
			SetMemory
			(
				&dataAddr[index],
				0,
				sizeof(T)
			);

			count--;

			return;
		}

		auto remainingSize = (sizeof(T) * remainingCount);

		CopyMemory
		(
			&dataAddr[index],
			&dataAddr[(index + 1)],
			remainingSize
		);

		SetMemory
		(
			&dataAddr[(count - 1)],
			0,
			sizeof(T)
		);

		count--;
	}


	void Clear();
	T & operator[](size_t index);
};

template <typename T>
bool Container<T>::Init(size_t size)
{
	if (size == 0)
	{
		return false;
	}

	dataAddr = reinterpret_cast<T *>(HighAlloc(size));
	if (!dataAddr)
	{
		return false;
	}

	dataSize = size;

	capacity = (dataSize / sizeof(T));

	return true;
}

template <typename T>
void Container<T>::Push(const T & var)
{
	if
	(
		!dataAddr ||
		(count >= capacity)
	)
	{
		return;
	}

	dataAddr[count] = var;

	count++;
}

template <typename T>
void Container<T>::Pop()
{
	if
	(
		!dataAddr ||
		(count < 1)
	)
	{
		return;
	}

	dataAddr[(count - 1)] = 0;

	count--;
}

template <typename T>
void Container<T>::Clear()
{
	if (dataAddr)
	{
		SetMemory
		(
			dataAddr,
			0,
			dataSize
		);
	}

	count = 0;
}

template <typename T>
T & Container<T>::operator[](size_t index)
{
	return dataAddr[index];
}

export template <typename T>
using Vector = Container<T>;



export template
<
	typename T,
	typename T2
>
struct Container<T, T2>
{
	T dataAddr[T2::value];
	size_t dataSize;
	size_t count;
	size_t capacity;

	Container();

	void Push(const T & var);
	void Pop();
	void Clear();
	T & operator[](size_t index);
	// @Remove
	template <typename U>
	void ForEach
	(
		size_t start,
		size_t end,
		U & func
	);
	template <typename U>
	void ForAll(U & func);
};

template
<
	typename T,
	typename T2
>
Container<T, T2>::Container()
{
	dataSize = (sizeof(T) * T2::value);
	capacity = T2::value;
}

template
<
	typename T,
	typename T2
>
void Container<T, T2>::Push(const T & var)
{
	if (count >= capacity)
	{
		return;
	}

	dataAddr[count] = var;

	count++;
}

template
<
	typename T,
	typename T2
>
void Container<T, T2>::Pop()
{
	if (count < 1)
	{
		return;
	}

	dataAddr[(count - 1)] = 0;

	count--;
}

template
<
	typename T,
	typename T2
>
void Container<T, T2>::Clear()
{
	SetMemory
	(
		dataAddr,
		0,
		dataSize
	);

	count = 0;
}

template
<
	typename T,
	typename T2
>
T & Container<T, T2>::operator[](size_t index)
{
	return dataAddr[index];
}

template
<
	typename T,
	typename T2
>
template <typename U>
void Container<T, T2>::ForEach
(
	size_t start,
	size_t end,
	U & func
)
{
	for_each(index, start, end)
	{
		auto & data = dataAddr[index];

		func(data);
	}
}

template
<
	typename T,
	typename T2
>
template <typename U>
void Container<T, T2>::ForAll(U & func)
{
	return ForEach
	(
		0,
		count,
		func
	);
}

export template
<
	typename T,
	size_t T2
>
using Array = Container<T, TypeValue<T2>>;

#pragma endregion

#pragma region Memory 2

export Container memoryData = {};



struct ProtectionHelperData
{
	void * addr;
	size_t size;
	byte32 protection;
};

struct ProtectionHelper : Container<ProtectionHelperData>
{
	void Push
	(
		void * addr,
		size_t size
	);
	void Pop();
};

void ProtectionHelper::Push
(
	void * addr,
	size_t size
)
{
	if
	(
		!dataAddr ||
		!addr ||
		(size == 0) ||
		(count >= capacity)
	)
	{
		return;
	}

	auto & data = dataAddr[count];

	byte32 error = 0;
	byte32 protection = 0;

	SetLastError(0);

	if
	(
		VirtualProtect
		(
			addr,
			size,
			PAGE_EXECUTE_READWRITE,
			&protection
		) == 0
	)
	{
		error = GetLastError();

		Log("VirtualProtect failed. %X", error);
	}

	data.addr = addr;
	data.size = size;
	data.protection = protection;

	count++;
}

void ProtectionHelper::Pop()
{
	if
	(
		!dataAddr ||
		(count < 1)
	)
	{
		return;
	}

	auto & data = dataAddr[(count - 1)];

	byte32 error = 0;
	byte32 protection = 0;

	SetLastError(0);

	if
	(
		VirtualProtect
		(
			data.addr,
			data.size,
			data.protection,
			&protection
		) == 0
	)
	{
		error = GetLastError();

		Log("VirtualProtect failed. %X", error);
	}

	SetMemory
	(
		&data,
		0,
		sizeof(data)
	);

	count--;
}

export ProtectionHelper protectionHelper = {};



export enum
{
	MemoryFlags_VirtualProtectDestination = 1 << 0,
	MemoryFlags_VirtualProtectSource      = 1 << 1,
};

export void SetMemory
(
	void * addr,
	byte8 value,
	size_t size,
	byte32 flags
)
{
	if (flags & MemoryFlags_VirtualProtectDestination)
	{
		protectionHelper.Push(addr, size);
	}

	SetMemory
	(
		addr,
		value,
		size
	);

	if (flags & MemoryFlags_VirtualProtectDestination)
	{
		protectionHelper.Pop();
	}
}

export void CopyMemory
(
	void * destination,
	const void * source,
	size_t size,
	byte32 flags
)
{
	if (flags & MemoryFlags_VirtualProtectDestination)
	{
		protectionHelper.Push(destination, size);
	}

	if (flags & MemoryFlags_VirtualProtectSource)
	{
		protectionHelper.Push(const_cast<void *>(source), size);
	}

	CopyMemory
	(
		destination,
		source,
		size
	);

	if (flags & MemoryFlags_VirtualProtectSource)
	{
		protectionHelper.Pop();
	}

	if (flags & MemoryFlags_VirtualProtectDestination)
	{
		protectionHelper.Pop();
	}
}



struct BackupHelper : Container<>
{
	struct Metadata : Container<>::Metadata
	{
		void * addr;
	};

	void Save
	(
		void * addr,
		size_t size
	);
	void Restore(void * addr);
};

void BackupHelper::Save
(
	void * addr,
	size_t size
)
{
	if
	(
		!dataAddr ||
		!metadataAddr ||
		!addr ||
		(size == 0) ||
		(pos > (dataSize - size))
	)
	{
		return;
	}

	CopyMemory
	(
		(dataAddr + pos),
		addr,
		size,
		MemoryFlags_VirtualProtectSource
	);

	auto & metadata = reinterpret_cast<Metadata *>(metadataAddr)[count];

	metadata.off = pos;
	metadata.size = size;
	metadata.addr = addr;

	pos += size;

	count++;
}

void BackupHelper::Restore(void * addr)
{
	for_all(index, count)
	{
		auto & metadata = reinterpret_cast<Metadata *>(metadataAddr)[index];

		if (metadata.addr != addr)
		{
			continue;
		}

		CopyMemory
		(
			metadata.addr,
			(dataAddr + metadata.off),
			metadata.size,
			MemoryFlags_VirtualProtectDestination
		);

		return;
	}

	auto off = static_cast<off_t>(reinterpret_cast<byte8 *>(addr) - appBaseAddr);

	Log("%s failed.", FUNC_NAME);

	Log("No Match dmc3.exe+%llX", off);
}

export BackupHelper backupHelper = {};

export template <typename T>
void Write
(
	void   * addr,
	T        value,
	uint32   padSize  = 0,
	byte8    padValue = 0x90
)
{
	constexpr uint32 size = sizeof(T);

	protectionHelper.Push(addr, size);

	*reinterpret_cast<T *>(addr) = value;

	if (padSize)
	{
		SetMemory
		(
			(reinterpret_cast<byte8 *>(addr) + size),
			padValue,
			padSize
		);
	}

	protectionHelper.Pop();
}

export void WriteAddress
(
	byte8  * addr,
	void   * dest,
	uint32   size,
	byte8    value    = 0,
	uint32   padSize  = 0,
	byte8    padValue = 0x90,
	uint32   off      = 0
)
{
	protectionHelper.Push(addr, (size + padSize));

	if (value)
	{
		addr[0] = value;
	}

	if (size == 2)
	{
		*reinterpret_cast<int8 *>(addr + (size - 1 - off)) = static_cast<int8>(reinterpret_cast<byte8 *>(dest) - addr - size);
	}
	else
	{
		*reinterpret_cast<int32 *>(addr + (size - 4 - off)) = static_cast<int32>(reinterpret_cast<byte8 *>(dest) - addr - size);
	}

	if (padSize)
	{
		SetMemory
		(
			(addr + size),
			padValue,
			padSize
		);
	}

	protectionHelper.Pop();
}

export auto WriteCall
(
	byte8  * addr,
	void   * dest,
	uint32   padSize  = 0,
	byte8    padValue = 0x90
)
{
	return WriteAddress(addr, dest, 5, 0xE8, padSize, padValue);
}

export auto WriteJump
(
	byte8  * addr,
	void   * dest,
	uint32   padSize  = 0,
	byte8    padValue = 0x90
)
{
	return WriteAddress(addr, dest, 5, 0xE9, padSize, padValue);
}

export auto WriteShortJump
(
	byte8  * addr,
	void   * dest,
	uint32   padSize  = 0,
	byte8    padValue = 0x90
)
{
	return WriteAddress(addr, dest, 2, 0xEB, padSize, padValue);
}

export void WriteNop
(
	void * addr,
	size_t size
)
{
	SetMemory
	(
		addr,
		0x90,
		size,
		MemoryFlags_VirtualProtectDestination
	);
}



#pragma region CreateFunction

#ifdef _WIN64

export struct Function
{
	byte8 *  addr;
	byte8 *  sect0;
	byte8 *  sect1;
	byte8 *  sect2;
	byte8 ** cache;
};

// @Todo: Increase Memory Data count.





export enum
{
	FunctionFlags_SaveRegisters    = 1 << 0,
	FunctionFlags_NoResult         = 1 << 1,
	FunctionFlags_NoReturn         = 1 << 2,
	FunctionFlags_Jump             = 1 << 3,
	FunctionFlags_SaveXMMRegisters = 1 << 4,
	FunctionFlags_NoXMMResult      = 1 << 5,
};





export Function CreateFunction
(
	void   * funcAddr  = 0,
	byte8  * jumpAddr  = 0,
	byte64   flags     = 0,
	size_t   size0     = 0,
	size_t   size1     = 0,
	size_t   size2     = 0,
	size_t   cacheSize = 0,
	size_t   count     = 0
)
{



	// @Remove
	const bool saveRegisters    = (flags & FunctionFlags_SaveRegisters   );
	const bool noResult         = (flags & FunctionFlags_NoResult        );
	const bool noReturn         = (flags & FunctionFlags_NoReturn        );
	const bool saveXMMRegisters = (flags & FunctionFlags_SaveXMMRegisters);
	const bool noXMMResult      = (flags & FunctionFlags_NoXMMResult     );







	Function func = {};
	off_t   pos  = 0;

	auto Feed = [&]
	(
		const byte8 * buffer,
		size_t bufferSize,
		bool adjustPosition = true
	)
	{
		// @Todo: Use CopyMemory.
		memcpy
		(
			(func.addr + pos),
			buffer,
			bufferSize
		);

		if (!adjustPosition)
		{
			return;
		}

		pos += bufferSize;
	};

	Align<off_t>(memoryData.pos, 0x10);

	func.addr = (memoryData.dataAddr + memoryData.pos);

	func.sect0 = (func.addr + pos);
	pos += size0;

	if (saveRegisters)
	{
		if (noResult)
		{
			constexpr byte8 buffer[] =
			{
				push_rax,
			};
			Feed(buffer, sizeof(buffer));
		}

		if (count)
		{
			if (noResult)
			{
				constexpr byte8 buffer[] =
				{
					0x48, 0x8D, 0x44, 0x24, 0x08, // lea rax,[rsp+08]
				};
				Feed(buffer, sizeof(buffer));
			}
			else
			{
				constexpr byte8 buffer[] =
				{
					0x48, 0x8B, 0xC4, // mov rax,rsp
				};
				Feed(buffer, sizeof(buffer));
			}
		}

		{
			// @Todo: Replace with macros.
			constexpr byte8 buffer[] =
			{
				0x51,                   // push rcx
				0x52,                   // push rdx
				0x53,                   // push rbx
				0x54,                   // push rsp
				0x55,                   // push rbp
				0x56,                   // push rsi
				0x57,                   // push rdi
				0x41, 0x50,             // push r8
				0x41, 0x51,             // push r9
				0x41, 0x52,             // push r10
				0x41, 0x53,             // push r11
				0x41, 0x54,             // push r12
				0x41, 0x55,             // push r13
				0x41, 0x56,             // push r14
				0x41, 0x57,             // push r15
				0x9C,                   // pushfq
			};
			Feed(buffer, sizeof(buffer));
		}

		if (saveXMMRegisters)
		{
			{
				constexpr byte8 buffer[] =
				{
					0x48, 0x81, 0xEC, 0x00, 0x01, 0x00, 0x00, // sub rsp,00000100
				};
				Feed(buffer, sizeof(buffer));
			}
			if (noXMMResult)
			{
				constexpr byte8 buffer[] =
				{
					0x0F, 0x11, 0x84, 0x24, 0xF0, 0x00, 0x00, 0x00,       // movups [rsp+000000F0],xmm0
				};
				Feed(buffer, sizeof(buffer));
			}
			{
				constexpr byte8 buffer[] =
				{
					0x0F, 0x11, 0x8C, 0x24, 0xE0, 0x00, 0x00, 0x00,       // movups [rsp+000000E0],xmm1
					0x0F, 0x11, 0x94, 0x24, 0xD0, 0x00, 0x00, 0x00,       // movups [rsp+000000D0],xmm2
					0x0F, 0x11, 0x9C, 0x24, 0xC0, 0x00, 0x00, 0x00,       // movups [rsp+000000C0],xmm3
					0x0F, 0x11, 0xA4, 0x24, 0xB0, 0x00, 0x00, 0x00,       // movups [rsp+000000B0],xmm4
					0x0F, 0x11, 0xAC, 0x24, 0xA0, 0x00, 0x00, 0x00,       // movups [rsp+000000A0],xmm5
					0x0F, 0x11, 0xB4, 0x24, 0x90, 0x00, 0x00, 0x00,       // movups [rsp+00000090],xmm6
					0x0F, 0x11, 0xBC, 0x24, 0x80, 0x00, 0x00, 0x00,       // movups [rsp+00000080],xmm7
					0x44, 0x0F, 0x11, 0x84, 0x24, 0x70, 0x00, 0x00, 0x00, // movups [rsp+00000070],xmm8
					0x44, 0x0F, 0x11, 0x8C, 0x24, 0x60, 0x00, 0x00, 0x00, // movups [rsp+00000060],xmm9
					0x44, 0x0F, 0x11, 0x94, 0x24, 0x50, 0x00, 0x00, 0x00, // movups [rsp+00000050],xmm10
					0x44, 0x0F, 0x11, 0x9C, 0x24, 0x40, 0x00, 0x00, 0x00, // movups [rsp+00000040],xmm11
					0x44, 0x0F, 0x11, 0xA4, 0x24, 0x30, 0x00, 0x00, 0x00, // movups [rsp+00000030],xmm12
					0x44, 0x0F, 0x11, 0xAC, 0x24, 0x20, 0x00, 0x00, 0x00, // movups [rsp+00000020],xmm13
					0x44, 0x0F, 0x11, 0xB4, 0x24, 0x10, 0x00, 0x00, 0x00, // movups [rsp+00000010],xmm14
					0x44, 0x0F, 0x11, 0xBC, 0x24, 0x00, 0x00, 0x00, 0x00, // movups [rsp+00000000],xmm15
				};
				Feed(buffer, sizeof(buffer));
			}
		}

		{
			constexpr byte8 buffer[] =
			{
				mov_rbp_rsp,
			};
			Feed(buffer, sizeof(buffer));
		}

		if (count)
		{
			constexpr byte8 buffer[] =
			{
				0x48, 0x81, 0xEC, 0x20, 0x00, 0x00, 0x00, // sub rsp,00000020
			};
			Feed(buffer, sizeof(buffer), false);
			*reinterpret_cast<uint32 *>(func.addr + pos + 3) += (static_cast<uint32>(count) * 8);
			pos += sizeof(buffer);
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0x48, 0x83, 0xEC, 0x20, // sub rsp,20
			};
			Feed(buffer, sizeof(buffer));
		}

		{
			constexpr byte8 buffer[] =
			{
				0x40, 0x80, 0xE4, 0xF0, // and spl,F0
			};
			Feed(buffer, sizeof(buffer));
		}

		if (count)
		{
			constexpr byte8 buffer[] =
			{
				0x51,                         // push rcx
				0x56,                         // push rsi
				0x57,                         // push rdi
				0xB9, 0x00, 0x00, 0x00, 0x00, // mov ecx
				0x48, 0x8D, 0x70, 0x28,       // lea rsi,[rax+28] return addr + shadow space
				0x48, 0x8D, 0x7C, 0x24, 0x38, // lea rdi,[rsp+38] rdi + rsi + rcx + shadow space
				0xF3, 0x48, 0xA5,             // repe movsq
				0x5F,                         // pop rdi
				0x5E,                         // pop rsi
				0x59,                         // pop rcx
			};
			Feed(buffer, sizeof(buffer), false);
			*reinterpret_cast<uint32 *>(func.addr + pos + 4) = static_cast<uint32>(count);
			pos += sizeof(buffer);
		}
	}

	func.sect1 = (func.addr + pos);
	pos += size1;

	if (funcAddr)
	{
		constexpr byte8 buffer[] =
		{
			0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // mov rax
		};
		Feed(buffer, sizeof(buffer), false);
		*reinterpret_cast<void **>(func.addr + pos + 2) = funcAddr;
		pos += sizeof(buffer);



		if (flags & FunctionFlags_Jump)
		{
			constexpr byte8 buffer[] =
			{
				0xFF, 0xE0, // jmp rax
			};
			Feed(buffer, sizeof(buffer));
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0xFF, 0xD0, // call rax
			};
			Feed(buffer, sizeof(buffer));
		}
	}

	if (saveRegisters)
	{
		{
			constexpr byte8 buffer[] =
			{
				mov_rsp_rbp,
			};
			Feed(buffer, sizeof(buffer));
		}

		if (saveXMMRegisters)
		{
			{
				constexpr byte8 buffer[] =
				{
					0x44, 0x0F, 0x10, 0xBC, 0x24, 0x00, 0x00, 0x00, 0x00, // movups xmm15,[rsp+00000000]
					0x44, 0x0F, 0x10, 0xB4, 0x24, 0x10, 0x00, 0x00, 0x00, // movups xmm14,[rsp+00000010]
					0x44, 0x0F, 0x10, 0xAC, 0x24, 0x20, 0x00, 0x00, 0x00, // movups xmm13,[rsp+00000020]
					0x44, 0x0F, 0x10, 0xA4, 0x24, 0x30, 0x00, 0x00, 0x00, // movups xmm12,[rsp+00000030]
					0x44, 0x0F, 0x10, 0x9C, 0x24, 0x40, 0x00, 0x00, 0x00, // movups xmm11,[rsp+00000040]
					0x44, 0x0F, 0x10, 0x94, 0x24, 0x50, 0x00, 0x00, 0x00, // movups xmm10,[rsp+00000050]
					0x44, 0x0F, 0x10, 0x8C, 0x24, 0x60, 0x00, 0x00, 0x00, // movups xmm9,[rsp+00000060]
					0x44, 0x0F, 0x10, 0x84, 0x24, 0x70, 0x00, 0x00, 0x00, // movups xmm8,[rsp+00000070]
					0x0F, 0x10, 0xBC, 0x24, 0x80, 0x00, 0x00, 0x00,       // movups xmm7,[rsp+00000080]
					0x0F, 0x10, 0xB4, 0x24, 0x90, 0x00, 0x00, 0x00,       // movups xmm6,[rsp+00000090]
					0x0F, 0x10, 0xAC, 0x24, 0xA0, 0x00, 0x00, 0x00,       // movups xmm5,[rsp+000000A0]
					0x0F, 0x10, 0xA4, 0x24, 0xB0, 0x00, 0x00, 0x00,       // movups xmm4,[rsp+000000B0]
					0x0F, 0x10, 0x9C, 0x24, 0xC0, 0x00, 0x00, 0x00,       // movups xmm3,[rsp+000000C0]
					0x0F, 0x10, 0x94, 0x24, 0xD0, 0x00, 0x00, 0x00,       // movups xmm2,[rsp+000000D0]
					0x0F, 0x10, 0x8C, 0x24, 0xE0, 0x00, 0x00, 0x00,       // movups xmm1,[rsp+000000E0]
				};
				Feed(buffer, sizeof(buffer));
			}
			if (noXMMResult)
			{
				constexpr byte8 buffer[] =
				{
					0x0F, 0x10, 0x84, 0x24, 0xF0, 0x00, 0x00, 0x00,       // movups xmm0,[rsp+000000F0]
				};
				Feed(buffer, sizeof(buffer));
			}
			{
				constexpr byte8 buffer[] =
				{
					0x48, 0x81, 0xC4, 0x00, 0x01, 0x00, 0x00, // add rsp,00000100
				};
				Feed(buffer, sizeof(buffer));
			}
		}

		{
			// @Todo: Replace with macros.
			constexpr byte8 buffer[] =
			{
				0x9D,             // popfq
				0x41, 0x5F,       // pop r15
				0x41, 0x5E,       // pop r14
				0x41, 0x5D,       // pop r13
				0x41, 0x5C,       // pop r12
				0x41, 0x5B,       // pop r11
				0x41, 0x5A,       // pop r10
				0x41, 0x59,       // pop r9
				0x41, 0x58,       // pop r8
				0x5F,             // pop rdi
				0x5E,             // pop rsi
				0x5D,             // pop rbp
				0x5C,             // pop rsp
				0x5B,             // pop rbx
				0x5A,             // pop rdx
				0x59,             // pop rcx
			};
			Feed(buffer, sizeof(buffer));
		}

		if (noResult)
		{
			constexpr byte8 buffer[] =
			{
				0x58, // pop rax
			};
			Feed(buffer, sizeof(buffer));
		}
	}

	func.sect2 = (func.addr + pos);
	pos += size2;

	if (jumpAddr)
	{
		WriteJump((func.addr + pos), jumpAddr);

		pos += 5;
	}
	else
	{
		if (!noReturn)
		{
			constexpr byte8 buffer[] =
			{
				0xC3, // ret
			};
			Feed(buffer, sizeof(buffer));
		}
	}

	memoryData.pos += pos;

	if (cacheSize)
	{
		Align<off_t>(memoryData.pos, 0x10);

		func.cache = reinterpret_cast<byte8 **>(memoryData.dataAddr + memoryData.pos);

		memoryData.pos += cacheSize;
	}

	return func;
}




export __declspec(deprecated) Function old_CreateFunction
(
	void   * funcAddr         = 0,
	byte8  * jumpAddr         = 0,
	bool     saveRegisters    = true,
	bool     noResult         = true,
	size_t   size0            = 0,
	size_t   size1            = 0,
	size_t   size2            = 0,
	size_t   cacheSize        = 0,
	size_t   count            = 0,
	bool     noReturn         = false,
	bool     saveXMMRegisters = false,
	bool     noXMMResult      = true
)
{
	byte64 flags = 0;

	if (saveRegisters)
	{
		flags |= FunctionFlags_SaveRegisters;
	}

	if (noResult)
	{
		flags |= FunctionFlags_NoResult;
	}

	if (noReturn)
	{
		flags |= FunctionFlags_NoReturn;
	}

	if (saveXMMRegisters)
	{
		flags |= FunctionFlags_SaveXMMRegisters;
	}

	if (noXMMResult)
	{
		flags |= FunctionFlags_NoXMMResult;
	}

	return CreateFunction
	(
		funcAddr,
		jumpAddr,
		flags,
		size0,
		size1,
		size2,
		cacheSize,
		count
	);
}


















#else








export enum
{
	FunctionFlags_SaveRegisters = 1 << 0,
	FunctionFlags_NoResult      = 1 << 1,
	FunctionFlags_NoReturn      = 1 << 2,
	FunctionFlags_Jump          = 1 << 3,
};






export struct Function
{
	byte8 *  addr;
	byte8 *  sect0;
	byte8 *  sect1;
	byte8 *  sect2;
	byte8 ** cache;
};





// @Update
export Function CreateFunction
(
	void   * funcAddr  = 0,
	byte8  * jumpAddr  = 0,
	byte32   flags     = 0,
	size_t   size0     = 0,
	size_t   size1     = 0,
	size_t   size2     = 0,
	size_t   cacheSize = 0
)
{




	// @Remove
	const bool saveRegisters = (flags & FunctionFlags_SaveRegisters);
	const bool noResult      = (flags & FunctionFlags_NoResult     );
	const bool noReturn      = (flags & FunctionFlags_NoReturn     );








	Function func = {};
	off_t    pos  = 0;

	auto Feed = [&]
	(
		const byte8 * buffer,
		size_t        bufferSize,
		bool          adjustPosition = true
	)
	{
		CopyMemory
		(
			(func.addr + pos),
			buffer,
			bufferSize
		);

		if (!adjustPosition)
		{
			return;
		}

		pos += bufferSize;
	};

	Align<off_t>(memoryData.pos, 0x10);

	func.addr = (memoryData.dataAddr + memoryData.pos);

	func.sect0 = (func.addr + pos);
	pos += size0;

	if (saveRegisters)
	{
		if (noResult)
		{
			constexpr byte8 buffer[] =
			{
				0x50, // push eax
			};
			Feed(buffer, sizeof(buffer));
		}

		{
			constexpr byte8 buffer[] =
			{
				0x51, // push ecx
				0x52, // push edx
				0x53, // push ebx
				0x54, // push esp
				0x55, // push ebp
				0x56, // push esi
				0x57, // push edi
				0x9C, // pushfd
			};
			Feed(buffer, sizeof(buffer));
		}

		{
			constexpr byte8 buffer[] =
			{
				0x8B, 0xEC, // mov ebp,esp
			};
			Feed(buffer, sizeof(buffer));
		}

		{


constexpr byte8 buffer[] =
{
	0x81, 0xE4, 0xF0, 0xFF, 0xFF, 0xFF, // and esp,FFFFFFF0
};




			// constexpr byte8 buffer[] =
			// {
			// 	0x81, 0xE4, 0xF0, 0x00, 0x00, 0x00, // and esp,000000F0
			// };
			Feed(buffer, sizeof(buffer));
		}
	}

	func.sect1 = (func.addr + pos);
	pos += size1;

	if (funcAddr)
	{
		constexpr byte8 buffer[] =
		{
			0xB8, 0x00, 0x00, 0x00, 0x00, // mov eax
		};
		Feed(buffer, sizeof(buffer), false);
		*reinterpret_cast<void **>(func.addr + pos + 1) = funcAddr;
		pos += sizeof(buffer);



		if (flags & FunctionFlags_Jump)
		{
			constexpr byte8 buffer[] =
			{
				0xFF, 0xE0, // jmp eax
			};
			Feed(buffer, sizeof(buffer));
		}
		else
		{
			constexpr byte8 buffer[] =
			{
				0xFF, 0xD0, // call eax
			};
			Feed(buffer, sizeof(buffer));
		}







		// // Not required!

		// if (argCount)
		// {
		// 	constexpr byte8 buffer[] =
		// 	{
		// 		0x83, 0xC4, 0x00, // add esp
		// 	};
		// 	Feed(buffer, sizeof(buffer), false);
		// 	*reinterpret_cast<uint8 *>(func.addr + pos + 2) = (argCount * 4);
		// 	pos += sizeof(buffer);
		// }
	}

	if (saveRegisters)
	{
		{
			constexpr byte8 buffer[] =
			{
				0x8B, 0xE5, // mov esp,ebp
			};
			Feed(buffer, sizeof(buffer));
		}

		{
			constexpr byte8 buffer[] =
			{
				0x9D, // popfd
				0x5F, // pop edi
				0x5E, // pop esi
				0x5D, // pop ebp
				0x5C, // pop esp
				0x5B, // pop ebx
				0x5A, // pop edx
				0x59, // pop ecx
			};
			Feed(buffer, sizeof(buffer));
		}

		if (noResult)
		{
			constexpr byte8 buffer[] =
			{
				0x58, // pop eax
			};
			Feed(buffer, sizeof(buffer));
		}
	}

	func.sect2 = (func.addr + pos);
	pos += size2;

	if (jumpAddr)
	{
		WriteJump((func.addr + pos), jumpAddr);

		pos += 5;
	}
	else
	{
		if (!noReturn)
		{
			constexpr byte8 buffer[] =
			{
				0xC3, // ret
			};
			Feed(buffer, sizeof(buffer));
		}
	}

	memoryData.pos += pos;

	if (cacheSize)
	{
		Align<off_t>(memoryData.pos, 0x10);

		func.cache = reinterpret_cast<byte8 **>(memoryData.dataAddr + memoryData.pos);

		memoryData.pos += cacheSize;
	}

	return func;
}




// @Remove
export __declspec(deprecated) Function old_CreateFunction
(
	void   * funcAddr      = 0,
	byte8  * jumpAddr      = 0,
	bool     saveRegisters = true,
	bool     noResult      = true,
	size_t   size0         = 0,
	size_t   size1         = 0,
	size_t   size2         = 0,
	size_t   cacheSize     = 0,
	bool     noReturn      = true
)
{
	byte32 flags = 0;

	if (saveRegisters)
	{
		flags |= FunctionFlags_SaveRegisters;
	}

	if (noResult)
	{
		flags |= FunctionFlags_NoResult;
	}

	if (noReturn)
	{
		flags |= FunctionFlags_NoReturn;
	}

	return CreateFunction
	(
		funcAddr,
		jumpAddr,
		flags,
		size0,
		size1,
		size2,
		cacheSize
	);
}
























#endif

#pragma endregion

























export bool Core_Memory_Init()
{
	LogFunction();

	MODULEENTRY32 moduleEntry = {};
	HANDLE snapshot = 0;

	moduleEntry.dwSize = sizeof(moduleEntry);
	snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, 0);
	Module32First(snapshot, &moduleEntry);

	appBaseAddr = moduleEntry.modBaseAddr;
	appSize = moduleEntry.modBaseSize;

	Log("%u %s", moduleEntry.th32ProcessID, moduleEntry.szModule);



	#ifdef _WIN64
	Log("appStart %llX", appBaseAddr);
	Log("appEnd   %llX", (appBaseAddr + appSize));
	#else
	Log("appStart %X", appBaseAddr);
	Log("appEnd   %X", (appBaseAddr + appSize));
	#endif



	Log("appSize %X", appSize);

	GetSystemInfo(&systemInfo);

	return true;
}



#pragma endregion


#pragma region String Stuff







export int32 IndexOf
(
	const char * name,
	const char * name2
)
{
	auto count  = static_cast<int32>(strlen(name ));
	auto count2 = static_cast<int32>(strlen(name2));

	if
	(
		(count  < 1     ) ||
		(count2 < 1     ) ||
		(count  < count2)
	)
	{
		return -1;
	}



	int32 pos = 0;

	while (pos < count)
	{
		if ((count - pos) < count2)
		{
			break;
		}

		auto dest = (reinterpret_cast<byte8 *>(const_cast<char *>(name)) + pos);

		if
		(
			memcmp
			(
				dest,
				name2,
				count2
			) == 0
		)
		{
			return pos;
		}

		pos++;
	}



	return -1;
}




#pragma endregion






#pragma region Windows





export inline bool Windows_GetTicksPerSecond(uint64 * var)
{
	return QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER *>(var));
}

export inline bool Windows_GetTickCount(uint64 * var)
{
	return QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER *>(var));
}

export void Windows_ToggleCursor(bool enable)
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

// export bool Windows_GetWindowPos(HWND window, POINT * point)
// {
// 	if (!window)
// 	{
// 		return false;
// 	}
// 	RECT rect = {};
// 	if (!GetWindowRect(window, &rect))
// 	{
// 		return false;
// 	}
// 	point->x = rect.left;
// 	point->y = rect.top;
// 	return true;
// }

// POINT Windows_GetWindowSize(HWND windowHandle)
// {
// 	RECT rect = {};

// 	GetWindowRect
// 	(
// 		windowHandle,
// 		&rect
// 	);

// 	POINT point = {};

// 	point.x = (rect.right - rect.left);
// 	point.y = (rect.bottom - rect.top);

// 	return point;
// }

// POINT Windows_GetClientSize(HWND windowHandle)
// {
// 	RECT rect = {};

// 	GetClientRect
// 	(
// 		windowHandle,
// 		&rect
// 	);

// 	POINT point = {};

// 	point.x = rect.right;
// 	point.y = rect.bottom;

// 	return point;
// }












// POINT Windows_GetWindowSize(HWND windowHandle)
// {
// 	POINT size = {};

// 	RECT rect = {};

// 	GetWindowRect
// 	(
// 		windowHandle,
// 		&rect
// 	);





// }








// export bool IsBorderless(HWND windowHandle)
// {
// 	auto style = GetWindowLongA
// 	(
// 		windowHandle,
// 		GWL_STYLE
// 	);

// 	if (style & WS_BORDER)
// 	{
// 		return false;
// 	}

// 	return true;
// }






// @Todo: Update for RVO.
export void GetWindowPos
(
	HWND window,
	POINT & point
)
{
	if (!window)
	{
		return;
	}

	RECT rect = {};

	GetWindowRect
	(
		window,
		&rect
	);

	point.x = rect.left;
	point.y = rect.top;
}








#pragma endregion






export enum
{
	KeyFlags_AtLeastOneKey = 1 << 0,
};



export struct KeyData
{
	byte8 keys[4];
	size_t keyCount;
	bool execute;
	//void * func;


	typedef void(* func_t)();

	func_t func;





	void Clear()
	{
		SetMemory
		(
			keys,
			0,
			sizeof(keys)
		);

		keyCount = 0;
	}

	void AddKey(byte8 newKey)
	{
		if (keyCount >= countof(keys))
		{
			return;
		}

		for_all(keyIndex, keyCount)
		{
			if (keys[keyIndex] == newKey)
			{
				return;
			}
		}

		keys[keyCount] = newKey;

		keyCount++;
	}





	void Check(byte8 * state)
	{
		// if (showPopup)
		// {
		// 	return;
		// }

		// auto & execute  = executes3[0];
		// auto & keys     = activeKeyData.keys;
		// auto & keyCount = activeKeyData.keyCount;

		size_t keysDown = 0;

		if (keyCount < 1)
		{
			return;
		}

		for_all(keyIndex, keyCount)
		{
			auto & key = keys[keyIndex];

			if (state[key] & 0x80)
			{
				keysDown++;
			}
		}

		if (keysDown == keyCount)
		{
			if (execute)
			{
				execute = false;

				[&]()
				{
					if (!func)
					{
						return;
					}

					func();
				}();
			}
		}
		else
		{
			execute = true;
		}
	}
};
















namespaceStart(DI8);









// $KeyStart

export namespaceStart(KEY);
enum
{
	UNKNOWN_0,
	ESCAPE,
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	ZERO,
	MINUS,
	EQUALS,
	BACKSPACE,
	TAB,
	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,
	LEFT_BRACKET,
	RIGHT_BRACKET,
	ENTER,
	LEFT_CONTROL,
	A,
	S,
	D,
	F,
	G,
	H,
	J,
	K,
	L,
	SEMICOLON,
	APOSTROPHE,
	TILDE,
	LEFT_SHIFT,
	BACKSLASH,
	Z,
	X,
	C,
	V,
	B,
	N,
	M,
	COMMA,
	PERIOD,
	SLASH,
	RIGHT_SHIFT,
	NUMPAD_MULTIPLY,
	LEFT_ALT,
	SPACE,
	CAPSLOCK,
	F1,
	F2,
	F3,
	F4,
	F5,
	F6,
	F7,
	F8,
	F9,
	F10,
	NUMLOCK,
	SCROLLLOCK,
	NUMPAD_7,
	NUMPAD_8,
	NUMPAD_9,
	NUMPAD_SUB,
	NUMPAD_4,
	NUMPAD_5,
	NUMPAD_6,
	NUMPAD_ADD,
	NUMPAD_1,
	NUMPAD_2,
	NUMPAD_3,
	NUMPAD_0,
	NUMPAD_DECIMAL,
	UNKNOWN_84,
	UNKNOWN_85,
	UNKNOWN_86,
	F11,
	F12,
	UNKNOWN_89,
	UNKNOWN_90,
	UNKNOWN_91,
	UNKNOWN_92,
	UNKNOWN_93,
	UNKNOWN_94,
	UNKNOWN_95,
	UNKNOWN_96,
	UNKNOWN_97,
	UNKNOWN_98,
	UNKNOWN_99,
	UNKNOWN_100,
	UNKNOWN_101,
	UNKNOWN_102,
	UNKNOWN_103,
	UNKNOWN_104,
	UNKNOWN_105,
	UNKNOWN_106,
	UNKNOWN_107,
	UNKNOWN_108,
	UNKNOWN_109,
	UNKNOWN_110,
	UNKNOWN_111,
	UNKNOWN_112,
	UNKNOWN_113,
	UNKNOWN_114,
	UNKNOWN_115,
	UNKNOWN_116,
	UNKNOWN_117,
	UNKNOWN_118,
	UNKNOWN_119,
	UNKNOWN_120,
	UNKNOWN_121,
	UNKNOWN_122,
	UNKNOWN_123,
	UNKNOWN_124,
	UNKNOWN_125,
	UNKNOWN_126,
	UNKNOWN_127,
	UNKNOWN_128,
	UNKNOWN_129,
	UNKNOWN_130,
	UNKNOWN_131,
	UNKNOWN_132,
	UNKNOWN_133,
	UNKNOWN_134,
	UNKNOWN_135,
	UNKNOWN_136,
	UNKNOWN_137,
	UNKNOWN_138,
	UNKNOWN_139,
	UNKNOWN_140,
	UNKNOWN_141,
	UNKNOWN_142,
	UNKNOWN_143,
	UNKNOWN_144,
	UNKNOWN_145,
	UNKNOWN_146,
	UNKNOWN_147,
	UNKNOWN_148,
	UNKNOWN_149,
	UNKNOWN_150,
	UNKNOWN_151,
	UNKNOWN_152,
	UNKNOWN_153,
	UNKNOWN_154,
	UNKNOWN_155,
	UNKNOWN_156,
	RIGHT_CONTROL,
	UNKNOWN_158,
	UNKNOWN_159,
	UNKNOWN_160,
	UNKNOWN_161,
	UNKNOWN_162,
	UNKNOWN_163,
	UNKNOWN_164,
	UNKNOWN_165,
	UNKNOWN_166,
	UNKNOWN_167,
	UNKNOWN_168,
	UNKNOWN_169,
	UNKNOWN_170,
	UNKNOWN_171,
	UNKNOWN_172,
	UNKNOWN_173,
	UNKNOWN_174,
	UNKNOWN_175,
	UNKNOWN_176,
	UNKNOWN_177,
	UNKNOWN_178,
	UNKNOWN_179,
	UNKNOWN_180,
	NUMPAD_DIVIDE,
	UNKNOWN_182,
	PRINT,
	RIGHT_ALT,
	UNKNOWN_185,
	UNKNOWN_186,
	UNKNOWN_187,
	UNKNOWN_188,
	UNKNOWN_189,
	UNKNOWN_190,
	UNKNOWN_191,
	UNKNOWN_192,
	UNKNOWN_193,
	UNKNOWN_194,
	UNKNOWN_195,
	UNKNOWN_196,
	PAUSE,
	UNKNOWN_198,
	HOME,
	UP,
	PAGE_UP,
	UNKNOWN_202,
	LEFT,
	UNKNOWN_204,
	RIGHT,
	UNKNOWN_206,
	END,
	DOWN,
	PAGE_DOWN,
	INSERT,
	DELETE,
	UNKNOWN_212,
	UNKNOWN_213,
	UNKNOWN_214,
	UNKNOWN_215,
	UNKNOWN_216,
	UNKNOWN_217,
	UNKNOWN_218,
	WIN,
	UNKNOWN_220,
	UNKNOWN_221,
	UNKNOWN_222,
	UNKNOWN_223,
	UNKNOWN_224,
	UNKNOWN_225,
	UNKNOWN_226,
	UNKNOWN_227,
	UNKNOWN_228,
	UNKNOWN_229,
	UNKNOWN_230,
	UNKNOWN_231,
	UNKNOWN_232,
	UNKNOWN_233,
	UNKNOWN_234,
	UNKNOWN_235,
	UNKNOWN_236,
	UNKNOWN_237,
	UNKNOWN_238,
	UNKNOWN_239,
	UNKNOWN_240,
	UNKNOWN_241,
	UNKNOWN_242,
	UNKNOWN_243,
	UNKNOWN_244,
	UNKNOWN_245,
	UNKNOWN_246,
	UNKNOWN_247,
	UNKNOWN_248,
	UNKNOWN_249,
	UNKNOWN_250,
	UNKNOWN_251,
	UNKNOWN_252,
	UNKNOWN_253,
	UNKNOWN_254,
	UNKNOWN_255,
	COUNT,
};
namespaceEnd();

export const char * keyNames[] =
{
	"UNKNOWN_0",
	"ESCAPE",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"0",
	"MINUS",
	"EQUALS",
	"BACKSPACE",
	"TAB",
	"Q",
	"W",
	"E",
	"R",
	"T",
	"Y",
	"U",
	"I",
	"O",
	"P",
	"LEFT_BRACKET",
	"RIGHT_BRACKET",
	"ENTER",
	"LEFT_CONTROL",
	"A",
	"S",
	"D",
	"F",
	"G",
	"H",
	"J",
	"K",
	"L",
	"SEMICOLON",
	"APOSTROPHE",
	"TILDE",
	"LEFT_SHIFT",
	"BACKSLASH",
	"Z",
	"X",
	"C",
	"V",
	"B",
	"N",
	"M",
	"COMMA",
	"PERIOD",
	"SLASH",
	"RIGHT_SHIFT",
	"NUMPAD_MULTIPLY",
	"LEFT_ALT",
	"SPACE",
	"CAPSLOCK",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"NUMLOCK",
	"SCROLLLOCK",
	"NUMPAD_7",
	"NUMPAD_8",
	"NUMPAD_9",
	"NUMPAD_SUB",
	"NUMPAD_4",
	"NUMPAD_5",
	"NUMPAD_6",
	"NUMPAD_ADD",
	"NUMPAD_1",
	"NUMPAD_2",
	"NUMPAD_3",
	"NUMPAD_0",
	"NUMPAD_DECIMAL",
	"UNKNOWN_84",
	"UNKNOWN_85",
	"UNKNOWN_86",
	"F11",
	"F12",
	"UNKNOWN_89",
	"UNKNOWN_90",
	"UNKNOWN_91",
	"UNKNOWN_92",
	"UNKNOWN_93",
	"UNKNOWN_94",
	"UNKNOWN_95",
	"UNKNOWN_96",
	"UNKNOWN_97",
	"UNKNOWN_98",
	"UNKNOWN_99",
	"UNKNOWN_100",
	"UNKNOWN_101",
	"UNKNOWN_102",
	"UNKNOWN_103",
	"UNKNOWN_104",
	"UNKNOWN_105",
	"UNKNOWN_106",
	"UNKNOWN_107",
	"UNKNOWN_108",
	"UNKNOWN_109",
	"UNKNOWN_110",
	"UNKNOWN_111",
	"UNKNOWN_112",
	"UNKNOWN_113",
	"UNKNOWN_114",
	"UNKNOWN_115",
	"UNKNOWN_116",
	"UNKNOWN_117",
	"UNKNOWN_118",
	"UNKNOWN_119",
	"UNKNOWN_120",
	"UNKNOWN_121",
	"UNKNOWN_122",
	"UNKNOWN_123",
	"UNKNOWN_124",
	"UNKNOWN_125",
	"UNKNOWN_126",
	"UNKNOWN_127",
	"UNKNOWN_128",
	"UNKNOWN_129",
	"UNKNOWN_130",
	"UNKNOWN_131",
	"UNKNOWN_132",
	"UNKNOWN_133",
	"UNKNOWN_134",
	"UNKNOWN_135",
	"UNKNOWN_136",
	"UNKNOWN_137",
	"UNKNOWN_138",
	"UNKNOWN_139",
	"UNKNOWN_140",
	"UNKNOWN_141",
	"UNKNOWN_142",
	"UNKNOWN_143",
	"UNKNOWN_144",
	"UNKNOWN_145",
	"UNKNOWN_146",
	"UNKNOWN_147",
	"UNKNOWN_148",
	"UNKNOWN_149",
	"UNKNOWN_150",
	"UNKNOWN_151",
	"UNKNOWN_152",
	"UNKNOWN_153",
	"UNKNOWN_154",
	"UNKNOWN_155",
	"UNKNOWN_156",
	"RIGHT_CONTROL",
	"UNKNOWN_158",
	"UNKNOWN_159",
	"UNKNOWN_160",
	"UNKNOWN_161",
	"UNKNOWN_162",
	"UNKNOWN_163",
	"UNKNOWN_164",
	"UNKNOWN_165",
	"UNKNOWN_166",
	"UNKNOWN_167",
	"UNKNOWN_168",
	"UNKNOWN_169",
	"UNKNOWN_170",
	"UNKNOWN_171",
	"UNKNOWN_172",
	"UNKNOWN_173",
	"UNKNOWN_174",
	"UNKNOWN_175",
	"UNKNOWN_176",
	"UNKNOWN_177",
	"UNKNOWN_178",
	"UNKNOWN_179",
	"UNKNOWN_180",
	"NUMPAD_DIVIDE",
	"UNKNOWN_182",
	"PRINT",
	"RIGHT_ALT",
	"UNKNOWN_185",
	"UNKNOWN_186",
	"UNKNOWN_187",
	"UNKNOWN_188",
	"UNKNOWN_189",
	"UNKNOWN_190",
	"UNKNOWN_191",
	"UNKNOWN_192",
	"UNKNOWN_193",
	"UNKNOWN_194",
	"UNKNOWN_195",
	"UNKNOWN_196",
	"PAUSE",
	"UNKNOWN_198",
	"HOME",
	"UP",
	"PAGE_UP",
	"UNKNOWN_202",
	"LEFT",
	"UNKNOWN_204",
	"RIGHT",
	"UNKNOWN_206",
	"END",
	"DOWN",
	"PAGE_DOWN",
	"INSERT",
	"DELETE",
	"UNKNOWN_212",
	"UNKNOWN_213",
	"UNKNOWN_214",
	"UNKNOWN_215",
	"UNKNOWN_216",
	"UNKNOWN_217",
	"UNKNOWN_218",
	"WIN",
	"UNKNOWN_220",
	"UNKNOWN_221",
	"UNKNOWN_222",
	"UNKNOWN_223",
	"UNKNOWN_224",
	"UNKNOWN_225",
	"UNKNOWN_226",
	"UNKNOWN_227",
	"UNKNOWN_228",
	"UNKNOWN_229",
	"UNKNOWN_230",
	"UNKNOWN_231",
	"UNKNOWN_232",
	"UNKNOWN_233",
	"UNKNOWN_234",
	"UNKNOWN_235",
	"UNKNOWN_236",
	"UNKNOWN_237",
	"UNKNOWN_238",
	"UNKNOWN_239",
	"UNKNOWN_240",
	"UNKNOWN_241",
	"UNKNOWN_242",
	"UNKNOWN_243",
	"UNKNOWN_244",
	"UNKNOWN_245",
	"UNKNOWN_246",
	"UNKNOWN_247",
	"UNKNOWN_248",
	"UNKNOWN_249",
	"UNKNOWN_250",
	"UNKNOWN_251",
	"UNKNOWN_252",
	"UNKNOWN_253",
	"UNKNOWN_254",
	"UNKNOWN_255",
};

// $KeyEnd

static_assert(KEY::COUNT == 256);









export namespaceStart(BUFFER_SIZE);
enum
{
	KEYBOARD = 256,
};
namespaceEnd();

namespaceEnd();





#pragma region Global

export vec2 g_windowSize = {};
export vec2 g_clientSize = {};
export vec2 g_renderSize = {};

export float g_frameRateMultiplier = 1.0f;



export POINT GetWindowSize(HWND windowHandle)
{
	POINT point = {};
	RECT  rect  = {};

	if (!windowHandle)
	{
		return point;
	}

	GetWindowRect
	(
		windowHandle,
		&rect
	);

	point.x = (rect.right  - rect.left);
	point.y = (rect.bottom - rect.top );

	return point;
}

export POINT GetClientSize(HWND windowHandle)
{
	POINT point = {};
	RECT  rect  = {};
	RECT  rect2 = {};

	if (!windowHandle)
	{
		return point;
	}

	GetWindowRect
	(
		appWindow,
		&rect
	);

	auto style = GetWindowLongA
	(
		appWindow,
		GWL_STYLE
	);

	AdjustWindowRect
	(
		&rect2,
		style,
		0
	);

	rect.left   -= rect2.left;
	rect.top    -= rect2.top;
	rect.right  -= rect2.right;
	rect.bottom -= rect2.bottom;

	point.x = (rect.right  - rect.left);
	point.y = (rect.bottom - rect.top );

	return point;
}



export void UpdateGlobalWindowSize()
{
	if (!appWindow)
	{
		return;
	}

	auto size = GetWindowSize(appWindow);

	g_windowSize =
	{
		static_cast<float>(size.x),
		static_cast<float>(size.y)
	};

	Log
	(
		"%s %g %g",
		FUNC_NAME,
		g_windowSize.x,
		g_windowSize.y
	);
}

export void UpdateGlobalClientSize()
{
	if (!appWindow)
	{
		return;
	}

	auto size = GetClientSize(appWindow);

	g_clientSize =
	{
		static_cast<float>(size.x),
		static_cast<float>(size.y)
	};

	Log
	(
		"%s %g %g",
		FUNC_NAME,
		g_clientSize.x,
		g_clientSize.y
	);
}

export void UpdateGlobalRenderSize
(
	uint32 width,
	uint32 height
)
{
	g_renderSize =
	{
		static_cast<float>(width),
		static_cast<float>(height)
	};

	Log
	(
		"%s %g %g",
		FUNC_NAME,
		g_renderSize.x,
		g_renderSize.y
	);
}

#pragma endregion






// @Research: Check triggers.

namespaceStart(XI);

// $GamepadStart

export namespaceStart(GAMEPAD);
enum
{
	UP             = 0x0001,
	DOWN           = 0x0002,
	LEFT           = 0x0004,
	RIGHT          = 0x0008,
	START          = 0x0010,
	BACK           = 0x0020,
	LEFT_THUMB     = 0x0040,
	RIGHT_THUMB    = 0x0080,
	LEFT_SHOULDER  = 0x0100,
	RIGHT_SHOULDER = 0x0200,
	A              = 0x1000,
	B              = 0x2000,
	X              = 0x4000,
	Y              = 0x8000,
};
namespaceEnd();

export const char * buttonNames[] =
{
	"Up",
	"Down",
	"Left",
	"Right",
	"Start",
	"Back",
	"Left Thumb",
	"Right Thumb",
	"Left Shoulder",
	"Right Shoulder",
	"A",
	"B",
	"X",
	"Y",
};

// $GamepadEnd

namespaceEnd();


















