#pragma once

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

// template <typename T>
// struct vec2Base
// {
// 	T x;
// 	T y;
// };

// template <typename T>
// struct vec2 : vec2Base<T>
// {
// };

// template <>
// struct vec2<uint32> : vec2Base<uint32>
// {
// 	vec2<uint32> & operator=(const vec2 & var)
// 	{
// 		x = static_cast<uint32>(var.x);
// 		y = static_cast<uint32>(var.y);

// 		return *this;
// 	}
// 	bool operator==(const vec2 & var)
// 	{
// 		return
// 		(
// 			(x == static_cast<uint32>(var.x)) &&
// 			(y == static_cast<uint32>(var.y))
// 		);
// 	}
// };

struct vec2
{
	float32 x;
	float32 y;
};

struct vec3
{
	float32 x;
	float32 y;
	float32 z;
};

struct vec4
{
	float32 x;
	float32 y;
	float32 z;
	float32 a;
};
