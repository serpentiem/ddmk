#pragma once
#include "DataTypes.h"
#include "String.h"

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>

float32 hexstrtof(const char * str);

#define countof(var) (sizeof(var) / sizeof(var[0]))

template <class T, T _value>
struct integral_constant
{
	static constexpr const T value = _value;
};
template <class T, class U> struct is_same       : integral_constant<bool, false> {};
template <class T>          struct is_same<T, T> : integral_constant<bool, true>  {};
#define typematch(a, b) is_same<a, b>::value

struct SPS
{
	byte * addr;
	#ifdef _WIN64
	uint64 pos;
	uint64 count;
	uint64 size;
	#else
	uint32 pos;
	uint32 count;
	uint32 size;
	#endif
};

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
