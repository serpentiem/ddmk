// @Todo: Review.

module;
#include "../Core/Core.h"
export module Memory;

export enum MEMORY_SIZE
{
	MEMORY_SIZE_ALL = (1 * 1024 * 1024 * 1024),
	MEMORY_SIZE_MAIN = (512 * 1024 * 1024),
	MEMORY_SIZE_STATIC_FILES = (128 * 1024 * 1024),
	MEMORY_SIZE_STATIC_FILES_METADATA = (1 * 1024 * 1024),
	MEMORY_SIZE_DYNAMIC_FILES = (64 * 1024 * 1024),
	MEMORY_SIZE_DYNAMIC_FILES_METADATA = (1 * 1024 * 1024),
};

constexpr uint32 vectorItemCount = 4096;

// @Todo: Rename.
export byte8 * Memory_main = 0;

byte8 * effectManagerData = 0;
byte8 * valueManagerData  = 0;

auto GetMemoryAddress()
{
	return Memory_main;
}

export bool Memory_Init()
{
	LogFunction();

	Memory_main = LowAlloc(MEMORY_SIZE_ALL);
	if (!Memory_main)
	{
		Log("LowAlloc failed.");
		return false;
	}

	Log("Memory_main %llX", Memory_main);

	{
		auto func = CreateFunction(GetMemoryAddress, (appBaseAddr + 0x3019E), true, false);
		WriteJump((appBaseAddr + 0x30199), func.addr);
		/*
		dmc3.exe+30199 - E8 328F0100 - call dmc3.exe+490D0
		dmc3.exe+3019E - 48 8B D0    - mov rdx,rax
		*/
	}

	// Increase main memory from 260 MB to 300 MB.
	{
		constexpr uint32 size = (300 * 1024 * 1024);
		Write<uint32>((appBaseAddr + 0x30195), size);
		Write<uint32>((appBaseAddr + 0x301AB), size);
	}

	// Increase section from 5 MB to 16 MB.
	{
		constexpr uint32 size = (16 * 1024 * 1024);
		Write<uint32>((appBaseAddr + 0x2C6065), size);
		Write<uint32>((appBaseAddr + 0x2C6082), size);
	}

	{
		constexpr uint32 size = ((vectorItemCount * 0x10) + 8);
		effectManagerData = HighAlloc(size);
		valueManagerData = HighAlloc(size);
		if (!effectManagerData || !valueManagerData)
		{
			Log("HighAlloc failed.");
			return false;
		}
	}

	return true;
}

export void Memory_ToggleExtendVectors(bool enable)
{
	LogFunction(enable);

	// Effect Manager
	{
		byte8 * addr = (enable) ? effectManagerData : (appBaseAddr + 0xCAB230);
		uint32 count = (enable) ? vectorItemCount : 304;

		WriteAddress((appBaseAddr + 0x2C0387), addr, 7);
		WriteAddress((appBaseAddr + 0x2C0460), addr, 7);
		WriteAddress((appBaseAddr + 0x2C0639), addr, 7);
		WriteAddress((appBaseAddr + 0x2E3B2E), addr, 7);
		WriteAddress((appBaseAddr + 0x2E3BAE), addr, 7);
		WriteAddress((appBaseAddr + 0x2E826E), addr, 7);

		Write<uint32>((appBaseAddr + 0x2E86D2), count);
		Write<uint32>((appBaseAddr + 0x2E8712), count);
		Write<uint32>((appBaseAddr + 0x2E876E), count);
		Write<uint32>((appBaseAddr + 0x2E87AC), count);
	}

	// Value Manager
	{
		byte8 * addr = (enable) ? valueManagerData : (appBaseAddr + 0xCF1270);
		uint32 count = (enable) ? vectorItemCount : 256;

		WriteAddress((appBaseAddr + 0x2C0376), addr, 7);
		WriteAddress((appBaseAddr + 0x2C043E), addr, 7);
		WriteAddress((appBaseAddr + 0x2C0663), addr, 7);
		WriteAddress((appBaseAddr + 0x2E824A), addr, 7);
		WriteAddress((appBaseAddr + 0x32447E), addr, 7);
		WriteAddress((appBaseAddr + 0x3244FE), addr, 7);
		WriteAddress((appBaseAddr + 0x324804), addr, 7);

		Write<uint32>((appBaseAddr + 0x324F42), count);
		Write<uint32>((appBaseAddr + 0x324F83), count);
		Write<uint32>((appBaseAddr + 0x324FFE), count);
		Write<uint32>((appBaseAddr + 0x32503C), count);
	}
}

// @Todo: Remove.
export byte8 * GetMasterPointer()
{
	auto dest = *reinterpret_cast<byte8 **>(appBaseAddr + 0xC8F970 + 0x1478 + 0x10);
	if (!dest)
	{
		return 0;
	}
	return *reinterpret_cast<byte8 **>(dest + 0x18 + 0x10);
}
