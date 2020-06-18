#include "Input.h"

//bool Input_enableRangeExtension   = false;
//bool Input_enableMultiplayerFixes = false;

////PrivateStart;
//
//struct FunctionHelper
//{
//	uint32 off;
//	uint32 funcOff;
//};
//
//constexpr FunctionHelper functionHelper[] =
//{
//	{ 0x1EBD2D, 0x32CC70 },
//	{ 0x1EBD42, 0x32CC80 },
//	{ 0x1EBD7E, 0x32CC10 },
//	{ 0x1EBD97, 0x32CC10 },
//	{ 0x1EBDAF, 0x32CC50 },
//	{ 0x1EBE98, 0x32CC50 },
//};
//
//byte8 * funcAddr[countof(functionHelper)] = {};
//
//byte8 backup[28] = {};
//
////PrivateEnd;

//void Input_Init()
//{
//	LogFunction();
//	{
//		byte8 sect0[] =
//		{
//			0x0F, 0xB6, 0x93, 0x18, 0x01, 0x00, 0x00, //movzx edx,byte ptr [rbx+00000118]
//		};
//		for (uint8 index = 0; index < countof(functionHelper); index++)
//		{
//			FUNC func = CreateFunction(0, (appBaseAddr + functionHelper[index].funcOff), false, true, sizeof(sect0));
//			memcpy(func.sect0, sect0, sizeof(sect0));
//			funcAddr[index] = func.addr;
//		}
//	}
//	memcpy(backup, (appBaseAddr + 0x2AFAA), 28);
//}
//
//void Input_ToggleRangeExtension(bool enable)
//{
//	LogFunction(enable);
//	Input_enableRangeExtension = enable;
//	WriteAddress((appBaseAddr + 0x32D0AA), (enable) ? (appBaseAddr + 0x32D0B0) : (appBaseAddr + 0x32D346), 6);
//	Write<uint8>((appBaseAddr + 0x2AF91), (enable) ? 3 : 1);
//	{
//		auto addr = (appBaseAddr + 0x2AFAA);
//		vp_memset(addr, 0x90, 28);
//		if (enable)
//		{
//			byte8 buffer[] =
//			{
//				0x44, 0x8B, 0xC7, //mov r8d,edi
//				0xEB, 0x17,       //jmp dmc3.exe+2AFC6
//			};
//			vp_memcpy(addr, buffer, sizeof(buffer));
//		}
//		else
//		{
//			vp_memcpy(addr, backup, sizeof(backup));
//		}
//	}
//	Write<byte32>((appBaseAddr + 0x32CFB9), (enable) ? 0x63C : 0x624);
//}
//
//void Input_ToggleMultiplayerFixes(bool enable)
//{
//	LogFunction(enable);
//	Input_enableMultiplayerFixes = enable;
//
//	// Disable actor id check.
//	WriteAddress((appBaseAddr + 0x1EBD1E), (enable) ? (appBaseAddr + 0x1EBD24) : (appBaseAddr + 0x1EBDBF), 6);
//
//	// Add actor id to function calls.
//	for (uint8 index = 0; index < countof(functionHelper); index++)
//	{
//		auto addr = (appBaseAddr + functionHelper[index].off);
//		auto dest = (enable) ? funcAddr[index] : (appBaseAddr + functionHelper[index].funcOff);
//		WriteCall(addr, dest);
//	}
//}
