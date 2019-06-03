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
