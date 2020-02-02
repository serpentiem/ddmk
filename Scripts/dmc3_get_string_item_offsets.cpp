
constexpr bool debug = false;

#pragma region Global

typedef signed char      int8;
typedef signed short     int16;
typedef signed long      int32;
typedef signed long long int64;

typedef unsigned char      uint8;
typedef unsigned short     uint16;
typedef unsigned long      uint32;
typedef unsigned long long uint64;

typedef unsigned char      byte8;
typedef unsigned short     byte16;
typedef unsigned long      byte32;
typedef unsigned long long byte64;

typedef float  float32;
typedef double float64;

#include <stdio.h>
#include <Windows.h>

byte8 * LoadFile
(
	const char * fileName,
	uint32     * size,
	byte8      * dest = 0
)
{
	byte8 * addr = dest;
	HANDLE file = 0;
	BY_HANDLE_FILE_INFORMATION fi = {};
	uint32 bytesRead = 0;
	byte32 error = 0;

	SetLastError(0);
	file = CreateFileA(fileName, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	error = GetLastError();
	if (file == INVALID_HANDLE_VALUE)
	{
		printf("CreateFile failed. %s %X\n", fileName, error);
		return 0;
	}
	GetFileInformationByHandle(file, &fi);
	SetLastError(0);
	if (!addr)
	{
		addr = (byte8 *)VirtualAlloc(0, fi.nFileSizeLow, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		error = GetLastError();
		if (!addr)
		{
			printf("VirtualAlloc failed. %X", error);
			return 0;
		}
	}
	ReadFile(file, addr, fi.nFileSizeLow, &bytesRead, 0);
	CloseHandle(file);
	if (size)
	{
		*size = fi.nFileSizeLow;
	}
	return addr;
}

bool AppendFile
(
	const char * fileName,
	byte8      * addr,
	uint32       size
)
{
	HANDLE file = 0;
	uint32 bytesWritten = 0;
	byte32 error = 0;

	SetLastError(0);
	file = CreateFileA(fileName, FILE_APPEND_DATA, 0, 0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	error = GetLastError();
	if (file == INVALID_HANDLE_VALUE)
	{
		printf("CreateFile failed. %X\n", error);
		return false;
	}

	WriteFile(file, addr, size, &bytesWritten, 0);
	CloseHandle(file);
	return true;
}

template <typename T>
bool Align(T & pos, T boundary, byte8 * addr = 0, uint8 pad = 0)
{
	T remainder = (pos % boundary);
	if (remainder)
	{
		T size = (boundary - remainder);
		if (addr)
		{
			memset((addr + pos), pad, size);
		}
		pos += size;
		return true;
	}
	return false;
}

#pragma endregion

bool GetCharacter(byte8 * file, uint32 pos)
{
	if ((file[pos] >= 'a') && (file[pos] <= 'z'))
	{
		return true;
	}
	if ((file[pos] >= 'A') && (file[pos] <= 'Z'))
	{
		return true;
	}
	if ((file[pos] >= '0') && (file[pos] <= '9'))
	{
		return true;
	}
	if (file[pos] == '_')
	{
		return true;
	}
	if (file[pos] == '.')
	{
		return true;
	}
	if (file[pos] == '\\')
	{
		return true;
	}
	if (file[pos] == '/')
	{
		return true;
	}
	return false;
}

int main()
{
	byte8 * file = 0;
	uint32 fileSize = 0;
	uint32 pos = 0x4EA570; // 0x4EA478 full range
	uint32 end = 0x4EB3C8; // 0x5058E0 full range
	char buffer[512];

	file = LoadFile("dmc3.exe", &fileSize);
	if (!file)
	{
		printf("LoadFile failed.\n");
		return 0;
	}

	do
	{
		uint32 size = 0;
		do
		{
			size++;
		}
		while (GetCharacter(file, (pos + size)) == true);

		if constexpr (debug)
		{
			printf("pos  %X\n", pos);
			printf("size %u\n", size);
		}

		if (size >= 3)
		{
			snprintf(buffer, sizeof(buffer), "0x%X, // %s\n", pos, (file + pos));
			AppendFile("strings.txt", (byte8 *)buffer, (uint32)strlen(buffer));
			pos += size;
		}

		pos++;
		Align<uint32>(pos, 8);
	}
	while (pos < end);

	return 1;
}
