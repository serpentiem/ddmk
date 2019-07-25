#include "Memory.h"

BYTE * AllocProxy = 0;
BYTE * FreeProxy  = 0;

void System_Memory_Init()
{
	LogFunction();
	{
		BYTE sect1[] =
		{
			0x68, 0x00, 0x00, 0x00, 0x00,       //push PAGE_EXECUTE_READWRITE
			0x68, 0x00, 0x00, 0x00, 0x00,       //push MEM_COMMIT | MEM_RESERVE
			0x57,                               //push edi
			0x6A, 0x00,                         //push 00
			0xFF, 0x15, 0x00, 0x00, 0x00, 0x00, //call dword ptr [dmc4.exe+B731A4]
		};
		FUNC func = CreateFunction(0, (appBaseAddr + 0x7B05C3), true, false, 0, sizeof(sect1));
		memcpy(func.sect1, sect1, sizeof(sect1));
		*(DWORD *)(func.sect1 + 1) = PAGE_EXECUTE_READWRITE;
		*(DWORD *)(func.sect1 + 6) = MEM_COMMIT | MEM_RESERVE;
		*(BYTE **)(func.sect1 + 0xF) = (appBaseAddr + 0xB731A4);
		AllocProxy = func.addr;
	}
	{
		BYTE sect1[] =
		{
			0x68, 0x00, 0x00, 0x00, 0x00,       //push MEM_RELEASE
			0x6A, 0x00,                         //push 00
			0x57,                               //push edi
			0xFF, 0x15, 0x00, 0x00, 0x00, 0x00, //call dword ptr [dmc4.exe+B731A8]
		};
		FUNC func = CreateFunction(0, (appBaseAddr + 0x7B07F9), true, false, 0, sizeof(sect1));
		memcpy(func.sect1, sect1, sizeof(sect1));
		*(DWORD *)(func.sect1 + 1) = MEM_RELEASE;
		*(BYTE **)(func.sect1 + 0xA) = (appBaseAddr + 0xB731A8);
		FreeProxy = func.addr;
	}
}

void System_Memory_ToggleReplaceAllocationFunctions(bool enable)
{
	LogFunctionBool(enable);
	if (enable)
	{
		WriteJump((appBaseAddr + 0x7B05AA), AllocProxy);
		WriteJump((appBaseAddr + 0x7B07B7), FreeProxy);
	}
	else
	{
		Write<BYTE>((appBaseAddr + 0x7B05AA), 0x68);
		Write<BYTE *>((appBaseAddr + 0x7B05AA + 1), (appBaseAddr + 0xF24C20));
		Write<BYTE>((appBaseAddr + 0x7B07B7), 0x68);
		Write<BYTE *>((appBaseAddr + 0x7B07B7 + 1), (appBaseAddr + 0xF24C20));
	}
}
