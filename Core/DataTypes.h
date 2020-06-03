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

struct vec4
{
	float32 x;
	float32 y;
	float32 z;
	float32 a;
};

template <typename T>
struct Vector
{
	T * data;
	uint32 count;
	uint32 dataSize;

	void Push(const T & var)
	{
		data[count] = var;
		count++;
	}
	void Pop()
	{
		if (count == 0)
		{
			return;
		}
		count--;
	}
	T & operator[](uint32 index)
	{
		return data[index];
	}
	void Clear()
	{
		memset(this, 0, sizeof(*this));
	}
	bool Init(uint32 _dataSize)
	{
		Clear();

		data = reinterpret_cast<T *>(Alloc(_dataSize));
		if (!data)
		{
			return false;
		}
		dataSize = _dataSize;

		return true;
	}
};

struct MixedVectorMetadata
{
	byte8 * addr;
	uint32 size;
	uint32 alignedSize;
};

struct MixedVector
{
	byte8 * data;
	uint32 pos;
	uint32 count;
	MixedVectorMetadata * metadata;
	uint32 dataSize;
	uint32 metadataSize;

	template <typename T>
	void Push(const T & var)
	{
		auto & dest = *reinterpret_cast<T *>(data + pos) = var;

		metadata[count].addr = reinterpret_cast<byte8 *>(&dest);
		metadata[count].size = sizeof(T);

		uint32 lastPos = pos;
		pos += sizeof(T);
		Align<uint32>(pos, 16);
		metadata[count].alignedSize = (pos - lastPos);
	}
	void Pop()
	{
		if (count == 0)
		{
			return;
		}
		pos -= metadata[count].alignedSize;
		count--;
	}
	byte8 * Next()
	{
		return (data + pos);
	}
	byte8 * operator[](uint32 index)
	{
		return metadata[index].addr;
	}
	void Clear()
	{
		memset(this, 0, sizeof(*this));
	}
	bool Init(uint32 _dataSize, uint32 _metadataSize)
	{
		Clear();

		data = Alloc(_dataSize);
		if (!data)
		{
			return false;
		}
		dataSize = _dataSize;

		metadata = reinterpret_cast<MixedVectorMetadata *>(Alloc(_metadataSize));
		if (!metadata)
		{
			return false;
		}
		metadataSize = _metadataSize;

		return true;
	}
};
