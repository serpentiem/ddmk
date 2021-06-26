

module;

#include "Macros.h"

// #include "Datatypes.h"
// #include "Macros.h"
export module DataTypes;











export
{


typedef unsigned char      bool8;
typedef unsigned short     bool16;
typedef unsigned long      bool32;
typedef unsigned long long bool64;

typedef char      int8;
typedef short     int16;
typedef long      int32;
typedef long long int64;

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

template <typename ...>
struct Tuple;

template <typename T>
struct Tuple<T>
{
	T x;
};

template
<
	typename T,
	typename T2
>
struct Tuple<T, T2>
{
	T x;
	T2 y;
};

template
<
	typename T,
	typename T2,
	typename T3
>
struct Tuple<T, T2, T3>
{
	T x;
	T2 y;
	T3 z;
};

template
<
	typename T,
	typename T2,
	typename T3,
	typename T4
>
struct Tuple<T, T2, T3, T4>
{
	T x;
	T2 y;
	T3 z;
	T4 a;
};

using vec2 = Tuple<float, float>;
using vec3 = Tuple<float, float, float>;
using vec4 = Tuple<float, float, float, float>;





}













