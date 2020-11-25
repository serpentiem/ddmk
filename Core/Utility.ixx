module;
#include "Includes.h"
export module Core_Utility;

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

export template
<
	typename T,
	uint64 count
>
constexpr auto countof(T(&array)[count])
{
	return count;
}

export struct TimeData
{
	uint32 milliseconds;
	uint32 seconds;
	uint32 minutes;
	uint32 hours;

	TimeData
	(
		float frameCount,
		float frameRate
	)
	{
		constexpr uint32 oneSecond = 1000;
		constexpr uint32 oneMinute = (60 * oneSecond);
		constexpr uint32 oneHour = (60 * oneMinute);

		auto time = static_cast<uint32>((frameCount / frameRate) * 1000.0f);

		hours = (time / oneHour);
		time -= (hours * oneHour);

		minutes = (time / oneMinute);
		time -= (minutes * oneMinute);

		seconds = (time / oneSecond);
		time -= (seconds * oneSecond);

		milliseconds = time;
	}
};

export template
<
	typename T,
	uint8 count
>
bool SignatureMatch
(
	byte8 * signature,
	T(&array)[count]
)
{
	uint8 signatureIndex = 0;

	while (signatureIndex < count)
	{
		if (signature[signatureIndex] != array[signatureIndex])
		{
			break;
		}

		signatureIndex++;
	}

	return (signatureIndex == count);
}

// @Research: Consider reference.
export template <typename T>
T Reverse(T * varAddr)
{
	constexpr uint8 size = static_cast<uint8>(sizeof(T));

	T var = 0;

	for_all(uint8, index, size)
	{
		reinterpret_cast<byte8 *>(&var)[index] = reinterpret_cast<byte8 *>(varAddr)[(size - 1 - index)];
	}

	return var;
}
