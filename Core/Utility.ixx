#ifndef __MODULE_CORE_UTILITY__
#define __MODULE_CORE_UTILITY__

module;
#include "Includes.h"
export module ModuleName(Core_Utility);

// @Todo: Update.
export float32 hexstrtof(const char * str)
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
//export template <class T, class U>
//struct is_same
//{
//	static constexpr const bool value = false;
//};
//
//export template <class T>
//struct is_same<T, T>
//{
//	static constexpr const bool value = true;
//};

export template
<
	typename T1,
	typename T2
>
struct TypeMatch
{
	static constexpr bool value = false;
};

export template <typename T>
struct TypeMatch<T, T>
{
	static constexpr bool value = true;
};





// @Todo: Update.
export template <typename T>
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

export template
<
	typename T,
	uint64 count
>
constexpr auto countof(T(&array)[count])
{
	return count;
}

//export template
//<
//	typename T1,
//	typename T2,
//	uint64 count
//>
//constexpr auto countof(T2(&array)[count])
//{
//	return static_cast<T1>(count);
//}





export template
<
	typename varType,
	uint8 mapItemCount
>
void UpdateMapIndex
(
	varType(&map)[mapItemCount],
	uint8 & index,
	varType & var
)
{

	//LogFunction();

	for_all(uint8, mapIndex, mapItemCount)
	{
		auto & mapItem = map[mapIndex];
		if (mapItem == var)
		{
			index = mapIndex;
			break;
		}
	}


	//MessageBoxA(0, "No Match", 0, 0);


	//Log("No Match");

}
















#endif
