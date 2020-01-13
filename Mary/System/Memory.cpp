

// @Todo: Vector relations.




#include "Memory.h"

bool System_Memory_enableExtendVectors = false;

byte8 * System_Memory_addr = 0;

PrivateStart;

byte8 * vectorEffectManager = 0;
byte8 * vectorValueManager  = 0;

constexpr uint16 vectorItemCount = 4096;

PrivateEnd;

void System_Memory_Init()
{
	LogFunction();

	// @Todo: Scope and constexpr.



	uint64 pos = 0x10000;
	uint64 end = 0x7FFFFFFF;
	// @Todo: Allocator!
	//System_Memory_addr = (byte8 *)Alloc((1 * 1024 * 1024 * 1024), (void *)pos, (void *)end);


	System_Memory_addr = Alloc((1 * 1024 * 1024 * 1024), pos, end);


	if (!System_Memory_addr)
	{
		Log("Alloc failed.");
		return;
	}









	{
		byte8 sect0[] =
		{
			0x48, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //mov rax,&System_Memory_addr
			0x48, 0x8B, 0x00,                                           //mov rax,[rax]
		};
		auto func = CreateFunction(0, (appBaseAddr + 0x3019E), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*(byte8 ***)(func.sect0 + 2) = &System_Memory_addr;
		WriteJump((appBaseAddr + 0x30199), func.addr);
		// dmc3.exe+30199 - E8 328F0100 - call dmc3.exe+490D0
		// dmc3.exe+3019E - 48 8B D0    - mov rdx,rax
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









	// @Todo: 32 bit.

	{
		constexpr uint64 size = ((vectorItemCount * 0x10) + 8);

		// @Todo: Proper allocators! >_>

		vectorEffectManager = (byte8 *)HighAlloc(size);
		vectorValueManager = (byte8 *)HighAlloc(size);
		if (!vectorEffectManager || !vectorValueManager)
		{
			Log("HighAlloc failed.");
			return;
		}
	}
}





void System_Memory_ToggleExtendVectors(bool enable)
{
	LogFunction(enable);
	System_Memory_enableExtendVectors = enable;
	byte8 * addr = 0;
	uint16 count = 0;
	{
		if (enable)
		{
			addr = vectorEffectManager;
			count = vectorItemCount;
		}
		else
		{
			addr = (appBaseAddr + 0xCAB230);
			count = 304;
		}
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
	{
		if (enable)
		{
			addr = vectorValueManager;
			count = vectorItemCount;
		}
		else
		{
			addr = (appBaseAddr + 0xCF1270);
			count = 256;
		}
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
