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

//#define __DDMK_OBSOLETE__
#ifndef __DDMK_OBSOLETE__

typedef unsigned char      byte;
typedef unsigned short     word;
typedef unsigned long      dword;
typedef unsigned long long qword;

#endif
