#include "Includes.h"

Export Module(Core_Utility);

#include "DataTypes.h"

// @Todo: Update.
Export float32 hexstrtof(const char * str)
{
	if (strlen(str) != 8)
	{
		return 0;
	}
	float32 value = 0;
	char buffer[3];
	for (uint8 i = 0; i < 4; i++)
	{
		buffer[0] = str[(0 + (i * 2))];
		buffer[1] = str[(1 + (i * 2))];
		buffer[2] = 0;
		*(byte8 *)((byte8 *)&value + (3 - i)) = (byte8)strtoul(buffer, 0, 16);
	}
	return value;
}

// @Todo: Update.
Export template <class T, class U>
struct is_same
{
	static constexpr const bool value = false;
};

Export template <class T>
struct is_same<T, T>
{
	static constexpr const bool value = true;
};

// @Todo: Update.
Export template <typename T>
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

Export template
<
	typename T,
	uint64 count
>
constexpr auto countof(T(&array)[count])
{
	return count;
}

Export template
<
	typename T1,
	typename T2,
	uint64 count
>
constexpr auto countof(T2(&array)[count])
{
	return static_cast<T1>(count);
}

#ifdef __GARBAGE__

//template <uint8 count> struct GetDataTypeByValueHelper {};
//
//template <> struct GetDataTypeByValueHelper<8 > { typedef uint8  type; };
//template <> struct GetDataTypeByValueHelper<16> { typedef uint16 type; };
//template <> struct GetDataTypeByValueHelper<32> { typedef uint32 type; };
//template <> struct GetDataTypeByValueHelper<64> { typedef uint64 type; };
//
//template <uint64 value>
//struct GetBitCount
//{
//	enum : uint8
//	{
//		COUNT =
//		(value < (1ull << 8 )) ? 8  :
//		(value < (1ull << 16)) ? 16 :
//		(value < (1ull << 32)) ? 32 :
//		64
//	};
//};
//
//template <uint64 value> struct GetDataTypeByValue : GetDataTypeByValueHelper<GetBitCount<value>::COUNT> {};

//template <typename T>
//constexpr auto countof(T & var)
//{
//	return (sizeof(var) / sizeof(var[0]));
//}


//#define const_for_each(name, start, end) for (GetDataTypeByValue<end>::type name = start; name < end; name++)
//
//#define for_each(name, start, end) for (decltype(end) name = start; name < end; name++)
//
//#define const_for_all(name, end) for (typename GetDataTypeByValue<end>::type name = 0; name < end; name++)
//
//// ugh, fails for const.
//#define for_all(name, end) for (decltype(end) name = 0; name < end; name++)


//#define for_each(type, name, start, end) for (type name = start; name < end; name++)
//#define for_all (type, name,        end) for (type name = 0    ; name < end; name++)

#endif
