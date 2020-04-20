#pragma once
#include "DataTypes.h"
#include "String.h"

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>

float32 hexstrtof(const char * str);

template <class T, class U>
struct is_same
{
	static constexpr const bool value = false;
};

template <class T>
struct is_same<T, T>
{
	static constexpr const bool value = true;
};

#define typematch(a, b) is_same<a, b>::value

template <typename T>
T Reverse(T * var)
{
	constexpr uint8 size = (uint8)sizeof(T);
	T value = 0;
	for (uint8 index = 0; index < size; index++)
	{
		((byte8 *)&value)[index] = ((byte8 *)var)[(size - 1 - index)];
	}
	return value;
}

#define PrivateStart namespace {
#define PrivateEnd }

#ifdef offsetof
#undef offsetof
#endif
#ifdef _CRT_USE_BUILTIN_OFFSETOF
#define offsetof(s, m) __builtin_offsetof(s, m)
#else
#define offsetof(s, m) reinterpret_cast<uint64>(&(*reinterpret_cast<s *>(0)).m)
#endif

template <uint8 count> struct GetDataTypeByValueHelper {};

template <> struct GetDataTypeByValueHelper<8 > { typedef uint8  type; };
template <> struct GetDataTypeByValueHelper<16> { typedef uint16 type; };
template <> struct GetDataTypeByValueHelper<32> { typedef uint32 type; };
template <> struct GetDataTypeByValueHelper<64> { typedef uint64 type; };

template <uint64 value>
struct GetBitCount
{
	enum : uint8
	{
		COUNT =
		(value < (1ull << 8 )) ? 8  :
		(value < (1ull << 16)) ? 16 :
		(value < (1ull << 32)) ? 32 :
		64
	};
};

template <uint64 value> struct GetDataTypeByValue : GetDataTypeByValueHelper<GetBitCount<value>::COUNT> {};

template <typename T>
constexpr auto countof(T & var)
{
	return (sizeof(var) / sizeof(var[0]));
}

#define const_for_each(name, start, end) for (GetDataTypeByValue<end>::type name = start; name < end; name++)

#define for_each(name, start, end) for (decltype(end) name = start; name < end; name++)

#define const_for_all(name, end) for (GetDataTypeByValue<end>::type name = 0; name < end; name++)

#define for_all(name, end) for (decltype(end) name = 0; name < end; name++)

#define HoboBreak MessageBoxA(0, "break1", 0, 0); MessageBoxA(0, "break2", 0, 0);
