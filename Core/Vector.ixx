#include "Includes.h"

Export Module(Core_Vector);

#include "Datatypes.h"

Import(Core_Memory);

Export template <typename T>
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
		memset(data, 0, (count * sizeof(T)));
		count = 0;
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

Export struct MixedVectorMetadata
{
	byte8 * addr;
	uint32 size;
	uint32 alignedSize;
};

Export struct MixedVector
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

		count++;
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
