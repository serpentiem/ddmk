#pragma once
#include "DataTypes.h"
#include "String.h"

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>

float32 hexstrtof(const char * str);

#define countof(var) (sizeof(var) / sizeof(var[0]))

//template <typename T>
//constexpr uint32 countof(T & var)
//{
//	return (uint32)(sizeof(var) / sizeof(var[0]));
//}

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

//#define __COMMA__ ,
