#include "Memory.h"

constexpr uint32 vectorItemCount = 4096;

byte8 * Memory_addr = 0;

PrivateStart;

byte8 * effectManagerData = 0;
byte8 * valueManagerData  = 0;

auto GetMemoryAddress()
{
	return Memory_addr;
}

PrivateEnd;

bool Memory_Init()
{
	LogFunction();

	Memory_addr = LowAlloc((1 * 1024 * 1024 * 1024));
	if (!Memory_addr)
	{
		Log("LowAlloc failed.");
		return false;
	}
	Log("Memory_addr %llX", Memory_addr);

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

void Memory_ToggleExtendVectors(bool enable)
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
