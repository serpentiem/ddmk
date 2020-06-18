#pragma once
#include "DataTypes.h"

template <typename T>
struct old_vector
{
	T data[256];
	uint64 count = 0;
	void push(T value)
	{
		data[count] = value;
		count++;
	}
};
