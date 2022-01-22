export module DataTypes;

#include "Macros.h"



export typedef char      int8;
export typedef short     int16;
export typedef long      int32;
export typedef long long int64;

export typedef unsigned char      uint8;
export typedef unsigned short     uint16;
export typedef unsigned long      uint32;
export typedef unsigned long long uint64;

export typedef uint8  bool8;
export typedef uint16 bool16;
export typedef uint32 bool32;
export typedef uint64 bool64;

export typedef uint8  byte8;
export typedef uint16 byte16;
export typedef uint32 byte32;
export typedef uint64 byte64;

export typedef float  float32;
export typedef double float64;



// @Research: Signed and unsigned versions of these should be useful.
// For example for string functions like LastIndexOf to return -1.

#ifdef _WIN64

export typedef uint64 off_t;
export typedef uint64 new_size_t;

#else

export typedef uint32 off_t;
export typedef uint32 new_size_t;

#endif



export struct vec2
{
	float x;
	float y;
};

export struct vec3
{
	float x;
	float y;
	float z;
};

export struct vec4
{
	float x;
	float y;
	float z;
	float a;
};



export struct struct_t {};
export struct array_t  {};
