#pragma once

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

struct vec4
{
	float32 x;
	float32 y;
	float32 z;
	float32 a;
};

template <typename T, uint32 n>
struct vector
{
	uint32 count;
	T data[n];
	void Push(T var)
	{
		data[count] = var;
		count++;
	}
	void Clear()
	{
		memset(this, 0, sizeof(*this));
	}
	void operator+=(T var)
	{
		Push(var);
	}
	T & operator[](uint32 index)
	{
		return data[index];
	}
	vector()
	{
		Clear();
	}
};
