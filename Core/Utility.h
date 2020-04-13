#pragma once
#include "DataTypes.h"
#include "String.h"

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>

float32 hexstrtof(const char * str);

//#define countof(var) (sizeof(var) / sizeof(var[0]))

// @Todo: Update.

template <class T, T _value>
struct integral_constant
{
	static constexpr const T value = _value;
};
template <class T, class U> struct is_same       : integral_constant<bool, false> {};
template <class T>          struct is_same<T, T> : integral_constant<bool, true>  {};
#define typematch(a, b) is_same<a, b>::value

template <typename T>
T Reverse(T * var)
{
	constexpr uint8 size = (uint8)sizeof(T);
	T value = 0;
	for (uint8 index = 0; index < size; index++)
	{
		((byte *)&value)[index] = ((byte *)var)[(size - 1 - index)];
	}
	return value;
}

#define PrivateStart namespace {
#define PrivateEnd }

#ifdef offsetof
#undef offsetof
#endif
#define offsetof(s, m) (uint32)(&(*(s *)0).m)

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
	constexpr auto count = (sizeof(var) / sizeof(var[0]));
	constexpr GetDataTypeByValue<count>::type value = count;
	return value;
}

#define for_each(name, start, end) for (decltype(end) name = start; name < end; name++)

#define for_all(name, end) for (decltype(end) name = 0; name < end; name++)
