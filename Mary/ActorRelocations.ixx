export module ActorRelocations;

import Core;

#include "../Core/Macros.h"

import ActorBase;
import Vars;

namespaceStart(Actor);



export void ToggleRelocations(bool enable)
{
	LogFunction(enable);
	// 0x200
	{
		constexpr auto off = offsetof(PlayerActorData, modelData[0]);
		constexpr auto newOff = offsetof(PlayerActorData, newModelData[0]);
		static_assert(off == 0x200);
		// Update Actor Dante
		Write<uint32>((appBaseAddr + 0x2131D9 + 3), (enable) ? newOff : off); // dmc3.exe+2131D9 - 49 81 C4 00020000 - ADD R12,00000200
		Write<uint32>((appBaseAddr + 0x2135D4 + 3), (enable) ? newOff : off); // dmc3.exe+2135D4 - 49 81 C4 00020000 - ADD R12,00000200
		Write<uint32>((appBaseAddr + 0x2139E1 + 3), (enable) ? newOff : off); // dmc3.exe+2139E1 - 49 81 C4 00020000 - ADD R12,00000200
		Write<uint32>((appBaseAddr + 0x214037 + 3), (enable) ? newOff : off); // dmc3.exe+214037 - 49 81 C4 00020000 - ADD R12,00000200
		Write<uint32>((appBaseAddr + 0x214165 + 3), (enable) ? newOff : off); // dmc3.exe+214165 - 49 81 C4 00020000 - ADD R12,00000200
		Write<uint32>((appBaseAddr + 0x214558 + 3), (enable) ? newOff : off); // dmc3.exe+214558 - 49 81 C4 00020000 - ADD R12,00000200
		Write<uint32>((appBaseAddr + 0x214BE7 + 3), (enable) ? newOff : off); // dmc3.exe+214BE7 - 48 8D 8E 00020000 - LEA RCX,[RSI+00000200]
		Write<uint32>((appBaseAddr + 0x214C00 + 3), (enable) ? newOff : off); // dmc3.exe+214C00 - 48 8D 8E 00020000 - LEA RCX,[RSI+00000200]
		Write<uint32>((appBaseAddr + 0x214C19 + 3), (enable) ? newOff : off); // dmc3.exe+214C19 - 48 8D 8E 00020000 - LEA RCX,[RSI+00000200]
		Write<uint32>((appBaseAddr + 0x214C32 + 3), (enable) ? newOff : off); // dmc3.exe+214C32 - 48 8D 8E 00020000 - LEA RCX,[RSI+00000200]
		Write<uint32>((appBaseAddr + 0x214CC2 + 3), (enable) ? newOff : off); // dmc3.exe+214CC2 - 48 8D 8E 00020000 - LEA RCX,[RSI+00000200]
		Write<uint32>((appBaseAddr + 0x214CDB + 3), (enable) ? newOff : off); // dmc3.exe+214CDB - 48 8D 8E 00020000 - LEA RCX,[RSI+00000200]
		Write<uint32>((appBaseAddr + 0x214CF4 + 3), (enable) ? newOff : off); // dmc3.exe+214CF4 - 48 8D 8E 00020000 - LEA RCX,[RSI+00000200]
		Write<uint32>((appBaseAddr + 0x214D0D + 3), (enable) ? newOff : off); // dmc3.exe+214D0D - 48 8D 8E 00020000 - LEA RCX,[RSI+00000200]
		// Update Actor Bob
		Write<uint32>((appBaseAddr + 0x225E61 + 3), (enable) ? newOff : off); // dmc3.exe+225E61 - 49 8D B6 00020000 - LEA RSI,[R14+00000200]
		Write<uint32>((appBaseAddr + 0x226414 + 3), (enable) ? newOff : off); // dmc3.exe+226414 - 4C 8B 83 00020000 - MOV R8,[RBX+00000200]
		Write<uint32>((appBaseAddr + 0x22641B + 3), (enable) ? newOff : off); // dmc3.exe+22641B - 48 8D 8B 00020000 - LEA RCX,[RBX+00000200]
		Write<uint32>((appBaseAddr + 0x226426 + 3), (enable) ? newOff : off); // dmc3.exe+226426 - 4C 8B 8B 00020000 - MOV R9,[RBX+00000200]
		Write<uint32>((appBaseAddr + 0x22642D + 3), (enable) ? newOff : off); // dmc3.exe+22642D - 48 8D 8B 00020000 - LEA RCX,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x226988 + 3), (enable) ? newOff : off); // dmc3.exe+226988 - 4C 8B 83 00020000 - MOV R8,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x22698F + 3), (enable) ? newOff : off); // dmc3.exe+22698F - 48 8D 8B 00020000 - LEA RCX,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x22699A + 3), (enable) ? newOff : off); // dmc3.exe+22699A - 4C 8B 8B 00020000 - MOV R9,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x2269A1 + 3), (enable) ? newOff : off); // dmc3.exe+2269A1 - 48 8D 8B 00020000 - LEA RCX,[RBX+00000200]
		Write<uint32>((appBaseAddr + 0x226C65 + 3), (enable) ? newOff : off); // dmc3.exe+226C65 - 49 8D 8E 00020000 - LEA RCX,[R14+00000200]
		Write<uint32>((appBaseAddr + 0x226C7D + 3), (enable) ? newOff : off); // dmc3.exe+226C7D - 49 8D 8E 00020000 - LEA RCX,[R14+00000200]
		// Update Actor Lady
		Write<uint32>((appBaseAddr + 0x219318 + 3), (enable) ? newOff : off); // dmc3.exe+219318 - 4C 8D A5 00020000 - LEA R12,[RBP+00000200]
		// Update Actor Vergil
		Write<uint32>((appBaseAddr + 0x220E21 + 3), (enable) ? newOff : off); // dmc3.exe+220E21 - 49 81 C6 00020000 - ADD R14,00000200
		Write<uint32>((appBaseAddr + 0x2211EB + 3), (enable) ? newOff : off); // dmc3.exe+2211EB - 49 81 C6 00020000 - ADD R14,00000200
		Write<uint32>((appBaseAddr + 0x2215F0 + 3), (enable) ? newOff : off); // dmc3.exe+2215F0 - 49 81 C6 00020000 - ADD R14,00000200
		// Update Model Dante
		Write<uint32>((appBaseAddr + 0x214D95 + 3), (enable) ? newOff : off); // dmc3.exe+214D95 - 49 8D B6 00020000 - LEA RSI,[R14+00000200]
		// Update Model Vergil
		Write<uint32>((appBaseAddr + 0x22202B + 3), (enable) ? newOff : off); // dmc3.exe+22202B - 4C 8D B5 00020000 - LEA R14,[RBP+00000200]
		// func_1DDAF0
		Write<uint32>((appBaseAddr + 0x1DDB4B + 3), (enable) ? newOff : off); // dmc3.exe+1DDB4B - 48 8D 8E 00020000 - LEA RCX,[RSI+00000200]
		// func_1DE280
		Write<uint32>((appBaseAddr + 0x1DE41A + 3), (enable) ? newOff : off); // dmc3.exe+1DE41A - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		// func_1DE750
		Write<uint32>((appBaseAddr + 0x1DE764 + 3), (enable) ? newOff : off); // dmc3.exe+1DE764 - 48 8D 99 00020000 - LEA RBX,[RCX+00000200]
		// func_1EF040
		Write<uint32>((appBaseAddr + 0x1EF09A + 3), (enable) ? newOff : off); // dmc3.exe+1EF09A - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x1EF3E0 + 3), (enable) ? newOff : off); // dmc3.exe+1EF3E0 - 4D 8D BD 00020000 - LEA R15,[R13+00000200]
		// Other
		Write<uint32>((appBaseAddr + 0xC9F2B + 3), (enable) ? newOff : off); // dmc3.exe+C9F2B - 49 8D 8F 00020000 - LEA RCX,[R15+00000200]
		Write<uint32>((appBaseAddr + 0x1DFD29 + 3), (enable) ? newOff : off); // dmc3.exe+1DFD29 - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x1EEF16 + 3), (enable) ? newOff : off); // dmc3.exe+1EEF16 - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x1EEF4D + 3), (enable) ? newOff : off); // dmc3.exe+1EEF4D - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x1EF566 + 3), (enable) ? newOff : off); // dmc3.exe+1EF566 - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x1EF5CC + 3), (enable) ? newOff : off); // dmc3.exe+1EF5CC - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x1EF6DC + 3), (enable) ? newOff : off); // dmc3.exe+1EF6DC - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x1EF8B3 + 3), (enable) ? newOff : off); // dmc3.exe+1EF8B3 - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x1FB570 + 3), (enable) ? newOff : off); // dmc3.exe+1FB570 - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x1FB70B + 3), (enable) ? newOff : off); // dmc3.exe+1FB70B - 48 8D B3 00020000 - LEA RSI,[RBX+00000200]
		Write<uint32>((appBaseAddr + 0x1FB7C3 + 3), (enable) ? newOff : off); // dmc3.exe+1FB7C3 - 48 8D B3 00020000 - LEA RSI,[RBX+00000200]
		Write<uint32>((appBaseAddr + 0x1FB946 + 3), (enable) ? newOff : off); // dmc3.exe+1FB946 - 48 8D B3 00020000 - LEA RSI,[RBX+00000200]
		Write<uint32>((appBaseAddr + 0x1FB9D1 + 3), (enable) ? newOff : off); // dmc3.exe+1FB9D1 - 48 81 C3 00020000 - ADD RBX,00000200
		Write<uint32>((appBaseAddr + 0x1FC3CB + 3), (enable) ? newOff : off); // dmc3.exe+1FC3CB - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x1FC525 + 3), (enable) ? newOff : off); // dmc3.exe+1FC525 - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x1FCA34 + 3), (enable) ? newOff : off); // dmc3.exe+1FCA34 - 48 8D B1 00020000 - LEA RSI,[RCX+00000200]
		Write<uint32>((appBaseAddr + 0x1FCB5B + 3), (enable) ? newOff : off); // dmc3.exe+1FCB5B - 4C 8D B7 00020000 - LEA R14,[RDI+00000200]
		Write<uint32>((appBaseAddr + 0x1FCC97 + 3), (enable) ? newOff : off); // dmc3.exe+1FCC97 - 4C 8D B7 00020000 - LEA R14,[RDI+00000200]
		Write<uint32>((appBaseAddr + 0x1FCCFC + 3), (enable) ? newOff : off); // dmc3.exe+1FCCFC - 4C 8D B7 00020000 - LEA R14,[RDI+00000200]
		Write<uint32>((appBaseAddr + 0x1FCD6A + 3), (enable) ? newOff : off); // dmc3.exe+1FCD6A - 4C 8D B7 00020000 - LEA R14,[RDI+00000200]
		Write<uint32>((appBaseAddr + 0x1FCDEC + 3), (enable) ? newOff : off); // dmc3.exe+1FCDEC - 4C 8D B7 00020000 - LEA R14,[RDI+00000200]
		Write<uint32>((appBaseAddr + 0x1FCE63 + 3), (enable) ? newOff : off); // dmc3.exe+1FCE63 - 4C 8D B7 00020000 - LEA R14,[RDI+00000200]
		Write<uint32>((appBaseAddr + 0x2005C0 + 3), (enable) ? newOff : off); // dmc3.exe+2005C0 - 48 8D 83 00020000 - LEA RAX,[RBX+00000200]
		Write<uint32>((appBaseAddr + 0x216A1E + 3), (enable) ? newOff : off); // dmc3.exe+216A1E - 48 8D 99 00020000 - LEA RBX,[RCX+00000200]
		Write<uint32>((appBaseAddr + 0x216A55 + 3), (enable) ? newOff : off); // dmc3.exe+216A55 - 48 8D 99 00020000 - LEA RBX,[RCX+00000200]
		Write<uint32>((appBaseAddr + 0x218A2F + 3), (enable) ? newOff : off); // dmc3.exe+218A2F - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x219AA1 + 3), (enable) ? newOff : off); // dmc3.exe+219AA1 - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		Write<uint32>((appBaseAddr + 0x223455 + 3), (enable) ? newOff : off); // dmc3.exe+223455 - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x22347F + 3), (enable) ? newOff : off); // dmc3.exe+22347F - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x2234A7 + 3), (enable) ? newOff : off); // dmc3.exe+2234A7 - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x2234D1 + 3), (enable) ? newOff : off); // dmc3.exe+2234D1 - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x22350F + 3), (enable) ? newOff : off); // dmc3.exe+22350F - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x223528 + 3), (enable) ? newOff : off); // dmc3.exe+223528 - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		Write<uint32>((appBaseAddr + 0x223543 + 3), (enable) ? newOff : off); // dmc3.exe+223543 - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x22355C + 3), (enable) ? newOff : off); // dmc3.exe+22355C - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		Write<uint32>((appBaseAddr + 0x223590 + 3), (enable) ? newOff : off); // dmc3.exe+223590 - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x2235BA + 3), (enable) ? newOff : off); // dmc3.exe+2235BA - 48 81 C1 00020000 - ADD RCX,00000200
		Write<uint32>((appBaseAddr + 0x2235DF + 3), (enable) ? newOff : off); // dmc3.exe+2235DF - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		Write<uint32>((appBaseAddr + 0x2235F8 + 3), (enable) ? newOff : off); // dmc3.exe+2235F8 - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		Write<uint32>((appBaseAddr + 0x223611 + 3), (enable) ? newOff : off); // dmc3.exe+223611 - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		Write<uint32>((appBaseAddr + 0x22362A + 3), (enable) ? newOff : off); // dmc3.exe+22362A - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		Write<uint32>((appBaseAddr + 0x22364D + 3), (enable) ? newOff : off); // dmc3.exe+22364D - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		Write<uint32>((appBaseAddr + 0x223666 + 3), (enable) ? newOff : off); // dmc3.exe+223666 - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		Write<uint32>((appBaseAddr + 0x22367F + 3), (enable) ? newOff : off); // dmc3.exe+22367F - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		Write<uint32>((appBaseAddr + 0x223698 + 3), (enable) ? newOff : off); // dmc3.exe+223698 - 48 8D 8F 00020000 - LEA RCX,[RDI+00000200]
		// Unknown
		// Write<uint32>((appBaseAddr + 0x23470 + 3), (enable) ? newOff : off); // dmc3.exe+23470 - 48 89 8B 00020000 - MOV [RBX+00000200],RCX
		// Write<uint32>((appBaseAddr + 0xDB2A9 + 3), (enable) ? newOff : off); // dmc3.exe+DB2A9 - 48 8B 89 00020000 - MOV RCX,[RCX+00000200]
		// Write<uint32>((appBaseAddr + 0x101747 + 3), (enable) ? newOff : off); // dmc3.exe+101747 - 4C 8D 83 00020000 - LEA R8,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x102544 + 3), (enable) ? newOff : off); // dmc3.exe+102544 - 48 8D B1 00020000 - LEA RSI,[RCX+00000200]
		// Write<uint32>((appBaseAddr + 0x102E9F + 3), (enable) ? newOff : off); // dmc3.exe+102E9F - 4C 8D 83 00020000 - LEA R8,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x102EE2 + 3), (enable) ? newOff : off); // dmc3.exe+102EE2 - 48 8D 91 00020000 - LEA RDX,[RCX+00000200]
		// Write<uint32>((appBaseAddr + 0x104A5F + 3), (enable) ? newOff : off); // dmc3.exe+104A5F - 4C 8D 8B 00020000 - LEA R9,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x104A99 + 3), (enable) ? newOff : off); // dmc3.exe+104A99 - 4C 8D 8B 00020000 - LEA R9,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x104AFF + 3), (enable) ? newOff : off); // dmc3.exe+104AFF - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x104C6F + 3), (enable) ? newOff : off); // dmc3.exe+104C6F - 48 8D B7 00020000 - LEA RSI,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x105025 + 3), (enable) ? newOff : off); // dmc3.exe+105025 - 48 8D B7 00020000 - LEA RSI,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x105518 + 3), (enable) ? newOff : off); // dmc3.exe+105518 - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x105A02 + 3), (enable) ? newOff : off); // dmc3.exe+105A02 - 4C 8D 8F 00020000 - LEA R9,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x105B4B + 3), (enable) ? newOff : off); // dmc3.exe+105B4B - 4C 8D 87 00020000 - LEA R8,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x10630A + 3), (enable) ? newOff : off); // dmc3.exe+10630A - 48 8D B7 00020000 - LEA RSI,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x1EF762 + 3), (enable) ? newOff : off); // dmc3.exe+1EF762 - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x1EF7B3 + 3), (enable) ? newOff : off); // dmc3.exe+1EF7B3 - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x1EF7F3 + 3), (enable) ? newOff : off); // dmc3.exe+1EF7F3 - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x1EF82E + 3), (enable) ? newOff : off); // dmc3.exe+1EF82E - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x1EF867 + 3), (enable) ? newOff : off); // dmc3.exe+1EF867 - 48 81 C1 00020000 - ADD RCX,00000200
		// Write<uint32>((appBaseAddr + 0x1FB88C + 3), (enable) ? newOff : off); // dmc3.exe+1FB88C - 48 8D B3 00020000 - LEA RSI,[RBX+00000200]
		// Write<uint32>((appBaseAddr + 0x1FCBC7 + 3), (enable) ? newOff : off); // dmc3.exe+1FCBC7 - 4C 8D B7 00020000 - LEA R14,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x1FCC2D + 3), (enable) ? newOff : off); // dmc3.exe+1FCC2D - 4C 8D B7 00020000 - LEA R14,[RDI+00000200]
		// Write<uint32>((appBaseAddr + 0x2DC32D + 2), (enable) ? newOff : off); // dmc3.exe+2DC32D - 48 05 00020000 - ADD RAX,00000200
		// Write<uint32>((appBaseAddr + 0x2DE765 + 2), (enable) ? newOff : off); // dmc3.exe+2DE765 - 48 05 00020000 - ADD RAX,00000200
		// Write<uint32>((appBaseAddr + 0x2DE827 + 2), (enable) ? newOff : off); // dmc3.exe+2DE827 - 48 05 00020000 - ADD RAX,00000200
		// Write<uint32>((appBaseAddr + 0x2DEB27 + 2), (enable) ? newOff : off); // dmc3.exe+2DEB27 - 48 05 00020000 - ADD RAX,00000200
		// Write<uint32>((appBaseAddr + 0x2FB2DB + 4), (enable) ? newOff : off); // dmc3.exe+2FB2DB - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB30E + 4), (enable) ? newOff : off); // dmc3.exe+2FB30E - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB341 + 4), (enable) ? newOff : off); // dmc3.exe+2FB341 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB374 + 4), (enable) ? newOff : off); // dmc3.exe+2FB374 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB3AC + 4), (enable) ? newOff : off); // dmc3.exe+2FB3AC - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB3DF + 4), (enable) ? newOff : off); // dmc3.exe+2FB3DF - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB412 + 4), (enable) ? newOff : off); // dmc3.exe+2FB412 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB445 + 4), (enable) ? newOff : off); // dmc3.exe+2FB445 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB47D + 4), (enable) ? newOff : off); // dmc3.exe+2FB47D - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB4B0 + 4), (enable) ? newOff : off); // dmc3.exe+2FB4B0 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB4E3 + 4), (enable) ? newOff : off); // dmc3.exe+2FB4E3 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB516 + 4), (enable) ? newOff : off); // dmc3.exe+2FB516 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB54E + 4), (enable) ? newOff : off); // dmc3.exe+2FB54E - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB583 + 4), (enable) ? newOff : off); // dmc3.exe+2FB583 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB5B8 + 4), (enable) ? newOff : off); // dmc3.exe+2FB5B8 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB5ED + 4), (enable) ? newOff : off); // dmc3.exe+2FB5ED - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB622 + 4), (enable) ? newOff : off); // dmc3.exe+2FB622 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB657 + 4), (enable) ? newOff : off); // dmc3.exe+2FB657 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB68C + 4), (enable) ? newOff : off); // dmc3.exe+2FB68C - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB6C1 + 4), (enable) ? newOff : off); // dmc3.exe+2FB6C1 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB6F6 + 4), (enable) ? newOff : off); // dmc3.exe+2FB6F6 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB72B + 4), (enable) ? newOff : off); // dmc3.exe+2FB72B - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB760 + 4), (enable) ? newOff : off); // dmc3.exe+2FB760 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB795 + 4), (enable) ? newOff : off); // dmc3.exe+2FB795 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB7CA + 4), (enable) ? newOff : off); // dmc3.exe+2FB7CA - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB7FF + 4), (enable) ? newOff : off); // dmc3.exe+2FB7FF - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB834 + 4), (enable) ? newOff : off); // dmc3.exe+2FB834 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
		// Write<uint32>((appBaseAddr + 0x2FB869 + 4), (enable) ? newOff : off); // dmc3.exe+2FB869 - 48 8D 84 01 00020000 - LEA RAX,[RCX+RAX+00000200]
	}
	// 0x208
	{
		constexpr auto off = (offsetof(PlayerActorData, modelData[0]) + 8);
		constexpr auto newOff = (offsetof(PlayerActorData, newModelData[0]) + 8);
		static_assert(off == 0x208);
		// func_1EF040
		Write<uint32>((appBaseAddr + 0x1EF412 + 3), (enable) ? newOff : off); // dmc3.exe+1EF412 - 49 8D AD 08020000 - LEA RBP,[R13+00000208]
		// Other
		Write<uint32>((appBaseAddr + 0x2005B9 + 3), (enable) ? newOff : off); // dmc3.exe+2005B9 - 48 8D 8B 08020000 - LEA RCX,[RBX+00000208]
		// Unknown
		// Write<uint32>((appBaseAddr + 0x2A108 + 3), (enable) ? newOff : off); // dmc3.exe+2A108 - 48 81 C2 08020000 - ADD RDX,00000208
		// Write<uint32>((appBaseAddr + 0x2A83B + 3), (enable) ? newOff : off); // dmc3.exe+2A83B - 48 81 C3 08020000 - ADD RBX,00000208
		// Write<uint32>((appBaseAddr + 0x2DE34 + 3), (enable) ? newOff : off); // dmc3.exe+2DE34 - 41 B8 08020000 - MOV R8D,00000208
		// Write<uint32>((appBaseAddr + 0x10135F + 3), (enable) ? newOff : off); // dmc3.exe+10135F - 48 89 B9 08020000 - MOV [RCX+00000208],RDI
		// Write<uint32>((appBaseAddr + 0x10461F + 3), (enable) ? newOff : off); // dmc3.exe+10461F - 48 8B 81 08020000 - MOV RAX,[RCX+00000208]
		// Write<uint32>((appBaseAddr + 0x10463F + 3), (enable) ? newOff : off); // dmc3.exe+10463F - 48 89 B1 08020000 - MOV [RCX+00000208],RSI
		// Write<uint32>((appBaseAddr + 0x104646 + 3), (enable) ? newOff : off); // dmc3.exe+104646 - 48 39 B1 08020000 - CMP [RCX+00000208],RSI
		// Write<uint32>((appBaseAddr + 0x1046D3 + 3), (enable) ? newOff : off); // dmc3.exe+1046D3 - 48 8B 87 08020000 - MOV RAX,[RDI+00000208]
		// Write<uint32>((appBaseAddr + 0x104701 + 3), (enable) ? newOff : off); // dmc3.exe+104701 - 48 8B 87 08020000 - MOV RAX,[RDI+00000208]
		// Write<uint32>((appBaseAddr + 0x1050AB + 3), (enable) ? newOff : off); // dmc3.exe+1050AB - F3 0F59 97 08020000 - MULSS XMM2,[RDI+00000208]
		// Write<uint32>((appBaseAddr + 0x105EBF + 3), (enable) ? newOff : off); // dmc3.exe+105EBF - 48 8B 81 08020000 - MOV RAX,[RCX+00000208]
		// Write<uint32>((appBaseAddr + 0x105EDF + 3), (enable) ? newOff : off); // dmc3.exe+105EDF - 48 89 B1 08020000 - MOV [RCX+00000208],RSI
		// Write<uint32>((appBaseAddr + 0x105EE6 + 3), (enable) ? newOff : off); // dmc3.exe+105EE6 - 48 39 B1 08020000 - CMP [RCX+00000208],RSI
		// Write<uint32>((appBaseAddr + 0x105F4E + 3), (enable) ? newOff : off); // dmc3.exe+105F4E - 48 8B 83 08020000 - MOV RAX,[RBX+00000208]
		// Write<uint32>((appBaseAddr + 0x22EE29 + 3), (enable) ? newOff : off); // dmc3.exe+22EE29 - 48 8D 81 08020000 - LEA RAX,[RCX+00000208]
		// Write<uint32>((appBaseAddr + 0x22EF4F + 3), (enable) ? newOff : off); // dmc3.exe+22EF4F - 48 05 08020000 - ADD RAX,00000208
		// Write<uint32>((appBaseAddr + 0x24297E + 3), (enable) ? newOff : off); // dmc3.exe+24297E - 48 8D 8F 08020000 - LEA RCX,[RDI+00000208]
		// Write<uint32>((appBaseAddr + 0x2429A4 + 3), (enable) ? newOff : off); // dmc3.exe+2429A4 - 48 8D 8F 08020000 - LEA RCX,[RDI+00000208]
		// Write<uint32>((appBaseAddr + 0x2429B5 + 3), (enable) ? newOff : off); // dmc3.exe+2429B5 - 48 8D 8F 08020000 - LEA RCX,[RDI+00000208]
		// Write<uint32>((appBaseAddr + 0x242AC0 + 3), (enable) ? newOff : off); // dmc3.exe+242AC0 - 48 8D 8F 08020000 - LEA RCX,[RDI+00000208]
		// Write<uint32>((appBaseAddr + 0x242ADA + 3), (enable) ? newOff : off); // dmc3.exe+242ADA - 48 8D 8F 08020000 - LEA RCX,[RDI+00000208]
		// Write<uint32>((appBaseAddr + 0x242AEB + 3), (enable) ? newOff : off); // dmc3.exe+242AEB - 48 8D 8F 08020000 - LEA RCX,[RDI+00000208]
	}
	// 0x980
	{
		constexpr auto off = offsetof(PlayerActorData, modelData[1]);
		constexpr auto newOff = offsetof(PlayerActorData, newModelData[1]);
		static_assert(off == 0x980);
		// func_1EF040
		Write<uint32>((appBaseAddr + 0x1EF2B4 + 3), (enable) ? newOff : off); // dmc3.exe+1EF2B4 - 49 8B 85 80090000 - MOV RAX,[R13+00000980]
		Write<uint32>((appBaseAddr + 0x1EF2C8 + 3), (enable) ? newOff : off); // dmc3.exe+1EF2C8 - 49 8D 8D 80090000 - LEA RCX,[R13+00000980]
		Write<uint32>((appBaseAddr + 0x1EF2D5 + 3), (enable) ? newOff : off); // dmc3.exe+1EF2D5 - 49 8D 8D 80090000 - LEA RCX,[R13+00000980]
		Write<uint32>((appBaseAddr + 0x1EF2EB + 3), (enable) ? newOff : off); // dmc3.exe+1EF2EB - 4D 8D B5 80090000 - LEA R14,[R13+00000980]
	}
	// 0x988
	{
		constexpr auto off = (offsetof(PlayerActorData, modelData[1]) + 8);
		constexpr auto newOff = (offsetof(PlayerActorData, newModelData[1]) + 8);
		static_assert(off == 0x988);
		// func_1EF040
		Write<uint32>((appBaseAddr + 0x1EF2F2 + 3), (enable) ? newOff : off); // dmc3.exe+1EF2F2 - 49 8D AD 88090000 - lea rbp,[r13+00000988]
	}
	// 0x1100
	{
		constexpr auto off = offsetof(PlayerActorData, modelData[2]);
		constexpr auto newOff = offsetof(PlayerActorData, newModelData[2]);
		static_assert(off == 0x1100);
		// func_1EF040
		Write<uint32>((appBaseAddr + 0x1EF188 + 3), (enable) ? newOff : off); // dmc3.exe+1EF188 - 49 8B 85 00110000 - MOV RAX,[R13+00001100]
		Write<uint32>((appBaseAddr + 0x1EF19C + 3), (enable) ? newOff : off); // dmc3.exe+1EF19C - 49 8D 8D 00110000 - LEA RCX,[R13+00001100]
		Write<uint32>((appBaseAddr + 0x1EF1A9 + 3), (enable) ? newOff : off); // dmc3.exe+1EF1A9 - 49 8D 8D 00110000 - LEA RCX,[R13+00001100]
		Write<uint32>((appBaseAddr + 0x1EF1BF + 3), (enable) ? newOff : off); // dmc3.exe+1EF1BF - 4D 8D B5 00110000 - LEA R14,[R13+00001100]
		// Unknown
		// Write<uint32>((appBaseAddr + 0x1400C4 + 3), (enable) ? newOff : off); // dmc3.exe+1400C4 - 48 8B 96 00110000 - MOV RDX,[RSI+00001100]
		// Write<uint32>((appBaseAddr + 0x14051A + 3), (enable) ? newOff : off); // dmc3.exe+14051A - 48 8B 93 00110000 - MOV RDX,[RBX+00001100]
		// Write<uint32>((appBaseAddr + 0x1405E5 + 3), (enable) ? newOff : off); // dmc3.exe+1405E5 - 48 8B 93 00110000 - MOV RDX,[RBX+00001100]
		// Write<uint32>((appBaseAddr + 0x141E29 + 3), (enable) ? newOff : off); // dmc3.exe+141E29 - 48 8B 93 00110000 - MOV RDX,[RBX+00001100]
		// Write<uint32>((appBaseAddr + 0x165F5A + 3), (enable) ? newOff : off); // dmc3.exe+165F5A - 48 8B 81 00110000 - MOV RAX,[RCX+00001100]
		// Write<uint32>((appBaseAddr + 0x165F7A + 3), (enable) ? newOff : off); // dmc3.exe+165F7A - 48 89 B9 00110000 - MOV [RCX+00001100],RDI
		// Write<uint32>((appBaseAddr + 0x165F81 + 3), (enable) ? newOff : off); // dmc3.exe+165F81 - 48 8B 89 00110000 - MOV RCX,[RCX+00001100]
		// Write<uint32>((appBaseAddr + 0x165F92 + 3), (enable) ? newOff : off); // dmc3.exe+165F92 - 48 89 BB 00110000 - MOV [RBX+00001100],RDI
		// Write<uint32>((appBaseAddr + 0x16601A + 3), (enable) ? newOff : off); // dmc3.exe+16601A - 48 8B 81 00110000 - MOV RAX,[RCX+00001100]
		// Write<uint32>((appBaseAddr + 0x16603A + 3), (enable) ? newOff : off); // dmc3.exe+16603A - 48 89 B9 00110000 - MOV [RCX+00001100],RDI
		// Write<uint32>((appBaseAddr + 0x166041 + 3), (enable) ? newOff : off); // dmc3.exe+166041 - 48 39 B9 00110000 - CMP [RCX+00001100],RDI
		// Write<uint32>((appBaseAddr + 0x166061 + 3), (enable) ? newOff : off); // dmc3.exe+166061 - 48 89 83 00110000 - MOV [RBX+00001100],RAX
		// Write<uint32>((appBaseAddr + 0x16608C + 3), (enable) ? newOff : off); // dmc3.exe+16608C - 48 8B 83 00110000 - MOV RAX,[RBX+00001100]
	}
	// 0x1108
	{
		constexpr auto off = (offsetof(PlayerActorData, modelData[2]) + 8);
		constexpr auto newOff = (offsetof(PlayerActorData, newModelData[2]) + 8);
		static_assert(off == 0x1108);
		// func_1EF040
		Write<uint32>((appBaseAddr + 0x1EF1C6 + 3), (enable) ? newOff : off); // dmc3.exe+1EF1C6 - 49 8D AD 08110000 - lea rbp,[r13+00001108]
	}
	// 0x1880
	{
		constexpr auto off = offsetof(PlayerActorData, modelPhysicsMetadataPool[0][0]);
		constexpr auto newOff = offsetof(PlayerActorData, newModelPhysicsMetadataPool[0][0]);
		static_assert(off == 0x1880);
		// Create Actor Dante
		Write<uint32>((appBaseAddr + 0x1DEC5C + 3), (enable) ? newOff : off); // dmc3.exe+1DEC5C - 48 8D 90 80180000 - LEA RDX,[RAX+00001880]
		// Create Actor Bob
		Write<uint32>((appBaseAddr + 0x1DEB43 + 3), (enable) ? newOff : off); // dmc3.exe+1DEB43 - 48 8D 90 80180000 - LEA RDX,[RAX+00001880]
		// Create Actor Lady
		Write<uint32>((appBaseAddr + 0x1DEA47 + 3), (enable) ? newOff : off); // dmc3.exe+1DEA47 - 48 8D 90 80180000 - LEA RDX,[RAX+00001880]
		// Create Actor Vergil
		Write<uint32>((appBaseAddr + 0x1DE92E + 3), (enable) ? newOff : off); // dmc3.exe+1DE92E - 48 8D 90 80180000 - LEA RDX,[RAX+00001880]
		// Update Actor Dante
		Write<uint32>((appBaseAddr + 0x213814 + 4), (enable) ? newOff : off); // dmc3.exe+213814 - 48 8B 8C C6 80180000 - MOV RCX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x213873 + 4), (enable) ? newOff : off); // dmc3.exe+213873 - 48 8B 8C C6 80180000 - MOV RCX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2138D2 + 4), (enable) ? newOff : off); // dmc3.exe+2138D2 - 48 8B 8C C6 80180000 - MOV RCX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x213C18 + 4), (enable) ? newOff : off); // dmc3.exe+213C18 - 48 8B 8C C6 80180000 - MOV RCX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x213C79 + 4), (enable) ? newOff : off); // dmc3.exe+213C79 - 48 8B 8C C6 80180000 - MOV RCX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x213ECF + 4), (enable) ? newOff : off); // dmc3.exe+213ECF - 48 8B 8C C6 80180000 - MOV RCX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x213F30 + 4), (enable) ? newOff : off); // dmc3.exe+213F30 - 48 8B 8C C6 80180000 - MOV RCX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21440F + 4), (enable) ? newOff : off); // dmc3.exe+21440F - 48 8B 8C C6 80180000 - MOV RCX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21446B + 4), (enable) ? newOff : off); // dmc3.exe+21446B - 48 8B 8C C6 80180000 - MOV RCX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2144C7 + 4), (enable) ? newOff : off); // dmc3.exe+2144C7 - 48 8B 8C C6 80180000 - MOV RCX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2147EC + 4), (enable) ? newOff : off); // dmc3.exe+2147EC - 48 8B 8C C6 80180000 - MOV RCX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21484D + 4), (enable) ? newOff : off); // dmc3.exe+21484D - 48 8B 8C C6 80180000 - MOV RCX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x214A9A + 4), (enable) ? newOff : off); // dmc3.exe+214A9A - 48 8B 8C C6 80180000 - MOV RCX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x214AF8 + 4), (enable) ? newOff : off); // dmc3.exe+214AF8 - 48 8B 8C C6 80180000 - MOV RCX,[RSI+RAX*8+00001880]
		// Update Actor Bob
		Write<uint32>((appBaseAddr + 0x2261BE + 3), (enable) ? newOff : off); // dmc3.exe+2261BE - 49 8D 96 80180000 - LEA RDX,[R14+00001880]
		Write<uint32>((appBaseAddr + 0x2265C7 + 4), (enable) ? newOff : off); // dmc3.exe+2265C7 - 49 8B 8C C6 80180000 - MOV RCX,[R14+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x226638 + 4), (enable) ? newOff : off); // dmc3.exe+226638 - 49 8B 8C C6 80180000 - MOV RCX,[R14+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2267CD + 4), (enable) ? newOff : off); // dmc3.exe+2267CD - 49 8B 8C C6 80180000 - MOV RCX,[R14+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x22683E + 4), (enable) ? newOff : off); // dmc3.exe+22683E - 49 8B 8C C6 80180000 - MOV RCX,[R14+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x226B37 + 4), (enable) ? newOff : off); // dmc3.exe+226B37 - 49 8B 8C C6 80180000 - MOV RCX,[R14+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x226BA0 + 4), (enable) ? newOff : off); // dmc3.exe+226BA0 - 49 8B 8C C6 80180000 - MOV RCX,[R14+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x226BFD + 4), (enable) ? newOff : off); // dmc3.exe+226BFD - 49 8B 8C C6 80180000 - MOV RCX,[R14+RAX*8+00001880]
		// Update Actor Lady
		Write<uint32>((appBaseAddr + 0x2194B2 + 3), (enable) ? newOff : off); // dmc3.exe+2194B2 - 48 8D 95 80180000 - LEA RDX,[RBP+00001880]
		// Update Actor Vergil
		Write<uint32>((appBaseAddr + 0x22112F + 4), (enable) ? newOff : off); // dmc3.exe+22112F - 49 8B 8C C4 80180000 - MOV RCX,[R12+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x22148C + 4), (enable) ? newOff : off); // dmc3.exe+22148C - 49 8B 8C C4 80180000 - MOV RCX,[R12+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2214E5 + 4), (enable) ? newOff : off); // dmc3.exe+2214E5 - 49 8B 8C C4 80180000 - MOV RCX,[R12+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x221551 + 4), (enable) ? newOff : off); // dmc3.exe+221551 - 49 8B 8C C4 80180000 - MOV RCX,[R12+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x22188B + 4), (enable) ? newOff : off); // dmc3.exe+22188B - 49 8B 8C C4 80180000 - MOV RCX,[R12+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2218F9 + 4), (enable) ? newOff : off); // dmc3.exe+2218F9 - 49 8B 8C C4 80180000 - MOV RCX,[R12+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x221B09 + 4), (enable) ? newOff : off); // dmc3.exe+221B09 - 49 8B 8C C4 80180000 - MOV RCX,[R12+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x221B71 + 4), (enable) ? newOff : off); // dmc3.exe+221B71 - 49 8B 8C C4 80180000 - MOV RCX,[R12+RAX*8+00001880]
		// Update Model Dante
		Write<uint32>((appBaseAddr + 0x2151C3 + 3), (enable) ? newOff : off); // dmc3.exe+2151C3 - 49 8D 96 80180000 - LEA RDX,[R14+00001880]
		Write<uint32>((appBaseAddr + 0x215373 + 3), (enable) ? newOff : off); // dmc3.exe+215373 - 49 8D 96 80180000 - LEA RDX,[R14+00001880]
		// Update Model Vergil
		Write<uint32>((appBaseAddr + 0x222653 + 3), (enable) ? newOff : off); // dmc3.exe+222653 - 48 8D 95 80180000 - LEA RDX,[RBP+00001880]
		Write<uint32>((appBaseAddr + 0x2227D3 + 3), (enable) ? newOff : off); // dmc3.exe+2227D3 - 48 8D 95 80180000 - LEA RDX,[RBP+00001880]
		// func_1EF040
		Write<uint32>((appBaseAddr + 0x1EF3ED + 3), (enable) ? newOff : off); // dmc3.exe+1EF3ED - 4D 8D B5 80180000 - LEA R14,[R13+00001880]
		// func_1F7BE0
		Write<uint32>((appBaseAddr + 0x1F7CEE + 4), (enable) ? newOff : off); // dmc3.exe+1F7CEE - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F81DE + 4), (enable) ? newOff : off); // dmc3.exe+1F81DE - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		// Other
		Write<uint32>((appBaseAddr + 0x8C3B9 + 4), (enable) ? newOff : off); // dmc3.exe+8C3B9 - 49 8B 94 C4 80180000 - MOV RDX,[R12+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x8CB96 + 4), (enable) ? newOff : off); // dmc3.exe+8CB96 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x8FA6B + 4), (enable) ? newOff : off); // dmc3.exe+8FA6B - 49 8B 94 C6 80180000 - MOV RDX,[R14+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x8FC47 + 4), (enable) ? newOff : off); // dmc3.exe+8FC47 - 49 8B 94 C6 80180000 - MOV RDX,[R14+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x9176B + 4), (enable) ? newOff : off); // dmc3.exe+9176B - 49 8B 94 C6 80180000 - MOV RDX,[R14+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x91D6F + 4), (enable) ? newOff : off); // dmc3.exe+91D6F - 49 8B 94 C6 80180000 - MOV RDX,[R14+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x91E9D + 4), (enable) ? newOff : off); // dmc3.exe+91E9D - 49 8B 94 C6 80180000 - MOV RDX,[R14+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x92289 + 4), (enable) ? newOff : off); // dmc3.exe+92289 - 49 8B 94 C6 80180000 - MOV RDX,[R14+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0xB9F5A + 3), (enable) ? newOff : off); // dmc3.exe+B9F5A - 48 8B 87 80180000 - MOV RAX,[RDI+00001880]
		Write<uint32>((appBaseAddr + 0xDA8A9 + 4), (enable) ? newOff : off); // dmc3.exe+DA8A9 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0xDA8C5 + 4), (enable) ? newOff : off); // dmc3.exe+DA8C5 - 48 8B 8C C7 80180000 - MOV RCX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0xDA8E7 + 4), (enable) ? newOff : off); // dmc3.exe+DA8E7 - 48 8B 8C C7 80180000 - MOV RCX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x150370 + 4), (enable) ? newOff : off); // dmc3.exe+150370 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x150395 + 4), (enable) ? newOff : off); // dmc3.exe+150395 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x16FC58 + 4), (enable) ? newOff : off); // dmc3.exe+16FC58 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x173072 + 4), (enable) ? newOff : off); // dmc3.exe+173072 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x173D52 + 4), (enable) ? newOff : off); // dmc3.exe+173D52 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x17C39B + 4), (enable) ? newOff : off); // dmc3.exe+17C39B - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x17C784 + 4), (enable) ? newOff : off); // dmc3.exe+17C784 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x17D694 + 4), (enable) ? newOff : off); // dmc3.exe+17D694 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x17DA05 + 4), (enable) ? newOff : off); // dmc3.exe+17DA05 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x188FB0 + 4), (enable) ? newOff : off); // dmc3.exe+188FB0 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1892AF + 4), (enable) ? newOff : off); // dmc3.exe+1892AF - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1A35EB + 4), (enable) ? newOff : off); // dmc3.exe+1A35EB - 48 8B 8C C7 80180000 - MOV RCX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1A36FF + 4), (enable) ? newOff : off); // dmc3.exe+1A36FF - 48 8B 8C C7 80180000 - MOV RCX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1B2266 + 4), (enable) ? newOff : off); // dmc3.exe+1B2266 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1E946F + 4), (enable) ? newOff : off); // dmc3.exe+1E946F - 48 8B 8C C7 80180000 - MOV RCX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1EAE89 + 4), (enable) ? newOff : off); // dmc3.exe+1EAE89 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1EAEE9 + 4), (enable) ? newOff : off); // dmc3.exe+1EAEE9 - 4C 8D 0C C5 80180000 - LEA R9,[RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1EAF20 + 4), (enable) ? newOff : off); // dmc3.exe+1EAF20 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1EAF79 + 4), (enable) ? newOff : off); // dmc3.exe+1EAF79 - 48 8D 0C C5 80180000 - LEA RCX,[RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1ED840 + 4), (enable) ? newOff : off); // dmc3.exe+1ED840 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1ED8E2 + 4), (enable) ? newOff : off); // dmc3.exe+1ED8E2 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1ED920 + 4), (enable) ? newOff : off); // dmc3.exe+1ED920 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1ED9AA + 4), (enable) ? newOff : off); // dmc3.exe+1ED9AA - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1EDACF + 4), (enable) ? newOff : off); // dmc3.exe+1EDACF - 48 8B 94 CF 80180000 - MOV RDX,[RDI+RCX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1EDB5B + 4), (enable) ? newOff : off); // dmc3.exe+1EDB5B - 48 8B 8C C7 80180000 - MOV RCX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1EDCB4 + 4), (enable) ? newOff : off); // dmc3.exe+1EDCB4 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1EE62E + 4), (enable) ? newOff : off); // dmc3.exe+1EE62E - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1EE690 + 4), (enable) ? newOff : off); // dmc3.exe+1EE690 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1EE6ED + 4), (enable) ? newOff : off); // dmc3.exe+1EE6ED - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F0764 + 4), (enable) ? newOff : off); // dmc3.exe+1F0764 - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F08D5 + 4), (enable) ? newOff : off); // dmc3.exe+1F08D5 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F0D12 + 4), (enable) ? newOff : off); // dmc3.exe+1F0D12 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F0D94 + 4), (enable) ? newOff : off); // dmc3.exe+1F0D94 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F0DC6 + 4), (enable) ? newOff : off); // dmc3.exe+1F0DC6 - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F0FE6 + 4), (enable) ? newOff : off); // dmc3.exe+1F0FE6 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F15D5 + 4), (enable) ? newOff : off); // dmc3.exe+1F15D5 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F1B2B + 4), (enable) ? newOff : off); // dmc3.exe+1F1B2B - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F1EC0 + 4), (enable) ? newOff : off); // dmc3.exe+1F1EC0 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F22E4 + 4), (enable) ? newOff : off); // dmc3.exe+1F22E4 - 4C 8B 84 C7 80180000 - MOV R8,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F2ECB + 4), (enable) ? newOff : off); // dmc3.exe+1F2ECB - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F2FEC + 4), (enable) ? newOff : off); // dmc3.exe+1F2FEC - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F353C + 4), (enable) ? newOff : off); // dmc3.exe+1F353C - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F359E + 4), (enable) ? newOff : off); // dmc3.exe+1F359E - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F35EB + 4), (enable) ? newOff : off); // dmc3.exe+1F35EB - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F3669 + 4), (enable) ? newOff : off); // dmc3.exe+1F3669 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F3721 + 4), (enable) ? newOff : off); // dmc3.exe+1F3721 - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F39F4 + 4), (enable) ? newOff : off); // dmc3.exe+1F39F4 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F4118 + 4), (enable) ? newOff : off); // dmc3.exe+1F4118 - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F4218 + 4), (enable) ? newOff : off); // dmc3.exe+1F4218 - 4C 8B 84 D3 80180000 - MOV R8,[RBX+RDX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F425D + 4), (enable) ? newOff : off); // dmc3.exe+1F425D - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F5721 + 4), (enable) ? newOff : off); // dmc3.exe+1F5721 - 48 8B 94 C6 80180000 - MOV RDX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F62DD + 4), (enable) ? newOff : off); // dmc3.exe+1F62DD - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F6306 + 4), (enable) ? newOff : off); // dmc3.exe+1F6306 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F6350 + 4), (enable) ? newOff : off); // dmc3.exe+1F6350 - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F65BE + 4), (enable) ? newOff : off); // dmc3.exe+1F65BE - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F7846 + 4), (enable) ? newOff : off); // dmc3.exe+1F7846 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1F9791 + 4), (enable) ? newOff : off); // dmc3.exe+1F9791 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1FA61A + 4), (enable) ? newOff : off); // dmc3.exe+1FA61A - 48 8B 94 CB 80180000 - MOV RDX,[RBX+RCX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1FAA81 + 4), (enable) ? newOff : off); // dmc3.exe+1FAA81 - 48 8B 84 C1 80180000 - MOV RAX,[RCX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1FAAA5 + 4), (enable) ? newOff : off); // dmc3.exe+1FAAA5 - 4A 8B 84 C1 80180000 - MOV RAX,[RCX+R8*8+00001880]
		Write<uint32>((appBaseAddr + 0x1FB059 + 4), (enable) ? newOff : off); // dmc3.exe+1FB059 - 4E 8B 8C CB 80180000 - MOV R9,[RBX+R9*8+00001880]
		Write<uint32>((appBaseAddr + 0x1FB065 + 4), (enable) ? newOff : off); // dmc3.exe+1FB065 - 4E 8B 84 C3 80180000 - MOV R8,[RBX+R8*8+00001880]
		Write<uint32>((appBaseAddr + 0x1FB070 + 4), (enable) ? newOff : off); // dmc3.exe+1FB070 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1FB09B + 4), (enable) ? newOff : off); // dmc3.exe+1FB09B - 4E 8B 8C CB 80180000 - MOV R9,[RBX+R9*8+00001880]
		Write<uint32>((appBaseAddr + 0x1FB0A7 + 4), (enable) ? newOff : off); // dmc3.exe+1FB0A7 - 4E 8B 84 C3 80180000 - MOV R8,[RBX+R8*8+00001880]
		Write<uint32>((appBaseAddr + 0x1FB0B2 + 4), (enable) ? newOff : off); // dmc3.exe+1FB0B2 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1FBAE5 + 4), (enable) ? newOff : off); // dmc3.exe+1FBAE5 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1FBBE3 + 4), (enable) ? newOff : off); // dmc3.exe+1FBBE3 - 48 8B 8C CB 80180000 - MOV RCX,[RBX+RCX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1FEE63 + 4), (enable) ? newOff : off); // dmc3.exe+1FEE63 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1FEF97 + 4), (enable) ? newOff : off); // dmc3.exe+1FEF97 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1FFB74 + 4), (enable) ? newOff : off); // dmc3.exe+1FFB74 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1FFD5B + 4), (enable) ? newOff : off); // dmc3.exe+1FFD5B - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x1FFFCC + 4), (enable) ? newOff : off); // dmc3.exe+1FFFCC - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x200604 + 4), (enable) ? newOff : off); // dmc3.exe+200604 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20121A + 4), (enable) ? newOff : off); // dmc3.exe+20121A - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20136A + 4), (enable) ? newOff : off); // dmc3.exe+20136A - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x201471 + 4), (enable) ? newOff : off); // dmc3.exe+201471 - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x201659 + 4), (enable) ? newOff : off); // dmc3.exe+201659 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x201696 + 4), (enable) ? newOff : off); // dmc3.exe+201696 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x201B74 + 4), (enable) ? newOff : off); // dmc3.exe+201B74 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x201D2E + 4), (enable) ? newOff : off); // dmc3.exe+201D2E - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x202155 + 4), (enable) ? newOff : off); // dmc3.exe+202155 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2021F9 + 4), (enable) ? newOff : off); // dmc3.exe+2021F9 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2026ED + 4), (enable) ? newOff : off); // dmc3.exe+2026ED - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x202974 + 4), (enable) ? newOff : off); // dmc3.exe+202974 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x202A64 + 4), (enable) ? newOff : off); // dmc3.exe+202A64 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x203160 + 4), (enable) ? newOff : off); // dmc3.exe+203160 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2032F2 + 4), (enable) ? newOff : off); // dmc3.exe+2032F2 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20381D + 4), (enable) ? newOff : off); // dmc3.exe+20381D - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x203A34 + 4), (enable) ? newOff : off); // dmc3.exe+203A34 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x203AE7 + 4), (enable) ? newOff : off); // dmc3.exe+203AE7 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x204159 + 4), (enable) ? newOff : off); // dmc3.exe+204159 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2041CE + 4), (enable) ? newOff : off); // dmc3.exe+2041CE - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20445E + 4), (enable) ? newOff : off); // dmc3.exe+20445E - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20454F + 4), (enable) ? newOff : off); // dmc3.exe+20454F - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2049FF + 4), (enable) ? newOff : off); // dmc3.exe+2049FF - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x205A15 + 4), (enable) ? newOff : off); // dmc3.exe+205A15 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x205BF3 + 4), (enable) ? newOff : off); // dmc3.exe+205BF3 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x205D66 + 4), (enable) ? newOff : off); // dmc3.exe+205D66 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x207241 + 4), (enable) ? newOff : off); // dmc3.exe+207241 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x209391 + 4), (enable) ? newOff : off); // dmc3.exe+209391 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x209AD0 + 4), (enable) ? newOff : off); // dmc3.exe+209AD0 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x209E14 + 4), (enable) ? newOff : off); // dmc3.exe+209E14 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x209E67 + 4), (enable) ? newOff : off); // dmc3.exe+209E67 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x209FBA + 4), (enable) ? newOff : off); // dmc3.exe+209FBA - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20A0A0 + 4), (enable) ? newOff : off); // dmc3.exe+20A0A0 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20A127 + 4), (enable) ? newOff : off); // dmc3.exe+20A127 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20A230 + 4), (enable) ? newOff : off); // dmc3.exe+20A230 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20A301 + 4), (enable) ? newOff : off); // dmc3.exe+20A301 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20A7F4 + 4), (enable) ? newOff : off); // dmc3.exe+20A7F4 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20AA63 + 4), (enable) ? newOff : off); // dmc3.exe+20AA63 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20ABFC + 4), (enable) ? newOff : off); // dmc3.exe+20ABFC - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20AF79 + 4), (enable) ? newOff : off); // dmc3.exe+20AF79 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20B02B + 4), (enable) ? newOff : off); // dmc3.exe+20B02B - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20B230 + 4), (enable) ? newOff : off); // dmc3.exe+20B230 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20B283 + 4), (enable) ? newOff : off); // dmc3.exe+20B283 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20B7A4 + 4), (enable) ? newOff : off); // dmc3.exe+20B7A4 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20B7CA + 4), (enable) ? newOff : off); // dmc3.exe+20B7CA - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20BD9F + 4), (enable) ? newOff : off); // dmc3.exe+20BD9F - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20BDC5 + 4), (enable) ? newOff : off); // dmc3.exe+20BDC5 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20C322 + 4), (enable) ? newOff : off); // dmc3.exe+20C322 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20C359 + 4), (enable) ? newOff : off); // dmc3.exe+20C359 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20C411 + 4), (enable) ? newOff : off); // dmc3.exe+20C411 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20C51B + 4), (enable) ? newOff : off); // dmc3.exe+20C51B - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20C72B + 4), (enable) ? newOff : off); // dmc3.exe+20C72B - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20CAA2 + 4), (enable) ? newOff : off); // dmc3.exe+20CAA2 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20D75E + 4), (enable) ? newOff : off); // dmc3.exe+20D75E - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20DBFE + 4), (enable) ? newOff : off); // dmc3.exe+20DBFE - 48 8B 94 CB 80180000 - MOV RDX,[RBX+RCX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20DD00 + 4), (enable) ? newOff : off); // dmc3.exe+20DD00 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20DFED + 4), (enable) ? newOff : off); // dmc3.exe+20DFED - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20E1AB + 4), (enable) ? newOff : off); // dmc3.exe+20E1AB - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20E6C6 + 4), (enable) ? newOff : off); // dmc3.exe+20E6C6 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20EC4F + 4), (enable) ? newOff : off); // dmc3.exe+20EC4F - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20EE46 + 4), (enable) ? newOff : off); // dmc3.exe+20EE46 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20F166 + 4), (enable) ? newOff : off); // dmc3.exe+20F166 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20F3B2 + 4), (enable) ? newOff : off); // dmc3.exe+20F3B2 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20FCAA + 4), (enable) ? newOff : off); // dmc3.exe+20FCAA - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20FDFA + 4), (enable) ? newOff : off); // dmc3.exe+20FDFA - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x20FF43 + 4), (enable) ? newOff : off); // dmc3.exe+20FF43 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2101E2 + 4), (enable) ? newOff : off); // dmc3.exe+2101E2 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2106FE + 4), (enable) ? newOff : off); // dmc3.exe+2106FE - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x210829 + 4), (enable) ? newOff : off); // dmc3.exe+210829 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x210CA2 + 4), (enable) ? newOff : off); // dmc3.exe+210CA2 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2114AC + 4), (enable) ? newOff : off); // dmc3.exe+2114AC - 48 8B 94 C6 80180000 - MOV RDX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2119E6 + 4), (enable) ? newOff : off); // dmc3.exe+2119E6 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x211BAC + 4), (enable) ? newOff : off); // dmc3.exe+211BAC - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x212190 + 4), (enable) ? newOff : off); // dmc3.exe+212190 - 4C 8B 84 C6 80180000 - MOV R8,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2121F3 + 4), (enable) ? newOff : off); // dmc3.exe+2121F3 - 48 8B 94 C6 80180000 - MOV RDX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x212272 + 4), (enable) ? newOff : off); // dmc3.exe+212272 - 4C 8B 84 C6 80180000 - MOV R8,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2122D5 + 4), (enable) ? newOff : off); // dmc3.exe+2122D5 - 48 8B 94 C6 80180000 - MOV RDX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x212340 + 4), (enable) ? newOff : off); // dmc3.exe+212340 - 4C 8B 84 C1 80180000 - MOV R8,[RCX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2123A3 + 4), (enable) ? newOff : off); // dmc3.exe+2123A3 - 48 8B 94 C6 80180000 - MOV RDX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x212422 + 4), (enable) ? newOff : off); // dmc3.exe+212422 - 4C 8B 84 C6 80180000 - MOV R8,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x212485 + 4), (enable) ? newOff : off); // dmc3.exe+212485 - 48 8B 94 C6 80180000 - MOV RDX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x212504 + 4), (enable) ? newOff : off); // dmc3.exe+212504 - 4C 8B 84 C6 80180000 - MOV R8,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x212567 + 4), (enable) ? newOff : off); // dmc3.exe+212567 - 48 8B 94 C6 80180000 - MOV RDX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2125CF + 4), (enable) ? newOff : off); // dmc3.exe+2125CF - 4C 8B 84 C1 80180000 - MOV R8,[RCX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x212632 + 4), (enable) ? newOff : off); // dmc3.exe+212632 - 48 8B 94 C6 80180000 - MOV RDX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21266C + 4), (enable) ? newOff : off); // dmc3.exe+21266C - 48 8B 94 C6 80180000 - MOV RDX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2126D7 + 4), (enable) ? newOff : off); // dmc3.exe+2126D7 - 4C 8B 84 C6 80180000 - MOV R8,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21273A + 4), (enable) ? newOff : off); // dmc3.exe+21273A - 48 8B 94 C6 80180000 - MOV RDX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2129AA + 4), (enable) ? newOff : off); // dmc3.exe+2129AA - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21544F + 4), (enable) ? newOff : off); // dmc3.exe+21544F - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2160EF + 4), (enable) ? newOff : off); // dmc3.exe+2160EF - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x216157 + 4), (enable) ? newOff : off); // dmc3.exe+216157 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x216289 + 4), (enable) ? newOff : off); // dmc3.exe+216289 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2162F1 + 4), (enable) ? newOff : off); // dmc3.exe+2162F1 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21636C + 4), (enable) ? newOff : off); // dmc3.exe+21636C - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x216493 + 4), (enable) ? newOff : off); // dmc3.exe+216493 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2166C0 + 4), (enable) ? newOff : off); // dmc3.exe+2166C0 - 4C 8B 84 C7 80180000 - MOV R8,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21670F + 4), (enable) ? newOff : off); // dmc3.exe+21670F - 4C 8B 84 C7 80180000 - MOV R8,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21677F + 4), (enable) ? newOff : off); // dmc3.exe+21677F - 4C 8B 84 C7 80180000 - MOV R8,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2167EF + 4), (enable) ? newOff : off); // dmc3.exe+2167EF - 4C 8B 84 C7 80180000 - MOV R8,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21685F + 4), (enable) ? newOff : off); // dmc3.exe+21685F - 4C 8B 84 C7 80180000 - MOV R8,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2168CF + 4), (enable) ? newOff : off); // dmc3.exe+2168CF - 4C 8B 84 C7 80180000 - MOV R8,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21693F + 4), (enable) ? newOff : off); // dmc3.exe+21693F - 4C 8B 84 C7 80180000 - MOV R8,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2169AF + 4), (enable) ? newOff : off); // dmc3.exe+2169AF - 4C 8B 84 C7 80180000 - MOV R8,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x216BB5 + 4), (enable) ? newOff : off); // dmc3.exe+216BB5 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x216D3B + 4), (enable) ? newOff : off); // dmc3.exe+216D3B - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x216D8A + 4), (enable) ? newOff : off); // dmc3.exe+216D8A - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x216EF2 + 4), (enable) ? newOff : off); // dmc3.exe+216EF2 - 48 8B 8C C7 80180000 - MOV RCX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21709C + 4), (enable) ? newOff : off); // dmc3.exe+21709C - 48 8B 8C C7 80180000 - MOV RCX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21723B + 4), (enable) ? newOff : off); // dmc3.exe+21723B - 48 8B 8C C7 80180000 - MOV RCX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x217387 + 4), (enable) ? newOff : off); // dmc3.exe+217387 - 48 8B 8C C7 80180000 - MOV RCX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x218087 + 4), (enable) ? newOff : off); // dmc3.exe+218087 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x218278 + 4), (enable) ? newOff : off); // dmc3.exe+218278 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x218358 + 4), (enable) ? newOff : off); // dmc3.exe+218358 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x218A97 + 4), (enable) ? newOff : off); // dmc3.exe+218A97 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x218B2D + 4), (enable) ? newOff : off); // dmc3.exe+218B2D - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x218BE0 + 4), (enable) ? newOff : off); // dmc3.exe+218BE0 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x218C76 + 4), (enable) ? newOff : off); // dmc3.exe+218C76 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x218D0C + 4), (enable) ? newOff : off); // dmc3.exe+218D0C - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x218DBC + 4), (enable) ? newOff : off); // dmc3.exe+218DBC - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x218E52 + 4), (enable) ? newOff : off); // dmc3.exe+218E52 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21A3CA + 4), (enable) ? newOff : off); // dmc3.exe+21A3CA - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21B1EE + 4), (enable) ? newOff : off); // dmc3.exe+21B1EE - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21B9DD + 4), (enable) ? newOff : off); // dmc3.exe+21B9DD - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21BD4F + 4), (enable) ? newOff : off); // dmc3.exe+21BD4F - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21C0F6 + 4), (enable) ? newOff : off); // dmc3.exe+21C0F6 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21C4ED + 4), (enable) ? newOff : off); // dmc3.exe+21C4ED - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21C801 + 4), (enable) ? newOff : off); // dmc3.exe+21C801 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21C9A4 + 4), (enable) ? newOff : off); // dmc3.exe+21C9A4 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21CBC0 + 4), (enable) ? newOff : off); // dmc3.exe+21CBC0 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21CCF1 + 4), (enable) ? newOff : off); // dmc3.exe+21CCF1 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21CDE5 + 4), (enable) ? newOff : off); // dmc3.exe+21CDE5 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21CE48 + 4), (enable) ? newOff : off); // dmc3.exe+21CE48 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21D214 + 4), (enable) ? newOff : off); // dmc3.exe+21D214 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21D314 + 4), (enable) ? newOff : off); // dmc3.exe+21D314 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21DA7A + 4), (enable) ? newOff : off); // dmc3.exe+21DA7A - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21DAED + 4), (enable) ? newOff : off); // dmc3.exe+21DAED - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21DD32 + 4), (enable) ? newOff : off); // dmc3.exe+21DD32 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21DDF0 + 4), (enable) ? newOff : off); // dmc3.exe+21DDF0 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21DF4B + 4), (enable) ? newOff : off); // dmc3.exe+21DF4B - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21E0D3 + 4), (enable) ? newOff : off); // dmc3.exe+21E0D3 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21E3A2 + 4), (enable) ? newOff : off); // dmc3.exe+21E3A2 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21EB05 + 4), (enable) ? newOff : off); // dmc3.exe+21EB05 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21ED0A + 4), (enable) ? newOff : off); // dmc3.exe+21ED0A - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21EECA + 4), (enable) ? newOff : off); // dmc3.exe+21EECA - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21F014 + 4), (enable) ? newOff : off); // dmc3.exe+21F014 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21F6EC + 4), (enable) ? newOff : off); // dmc3.exe+21F6EC - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21F8FE + 4), (enable) ? newOff : off); // dmc3.exe+21F8FE - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21F9EF + 4), (enable) ? newOff : off); // dmc3.exe+21F9EF - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21FADF + 4), (enable) ? newOff : off); // dmc3.exe+21FADF - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21FC5B + 4), (enable) ? newOff : off); // dmc3.exe+21FC5B - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21FCD1 + 4), (enable) ? newOff : off); // dmc3.exe+21FCD1 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x21FF27 + 4), (enable) ? newOff : off); // dmc3.exe+21FF27 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x220032 + 4), (enable) ? newOff : off); // dmc3.exe+220032 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x220059 + 4), (enable) ? newOff : off); // dmc3.exe+220059 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x22019D + 4), (enable) ? newOff : off); // dmc3.exe+22019D - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2201D0 + 4), (enable) ? newOff : off); // dmc3.exe+2201D0 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2202A5 + 4), (enable) ? newOff : off); // dmc3.exe+2202A5 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x220595 + 4), (enable) ? newOff : off); // dmc3.exe+220595 - 4C 8B 84 C6 80180000 - MOV R8,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2205EA + 4), (enable) ? newOff : off); // dmc3.exe+2205EA - 48 8B 94 C6 80180000 - MOV RDX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x22060A + 4), (enable) ? newOff : off); // dmc3.exe+22060A - 48 8B 94 C6 80180000 - MOV RDX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x220644 + 4), (enable) ? newOff : off); // dmc3.exe+220644 - 4C 8B 84 C6 80180000 - MOV R8,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x22069D + 4), (enable) ? newOff : off); // dmc3.exe+22069D - 48 8B 94 C6 80180000 - MOV RDX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2206BD + 4), (enable) ? newOff : off); // dmc3.exe+2206BD - 48 8B 94 C6 80180000 - MOV RDX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x22071E + 4), (enable) ? newOff : off); // dmc3.exe+22071E - 4C 8B 84 C6 80180000 - MOV R8,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x220777 + 4), (enable) ? newOff : off); // dmc3.exe+220777 - 48 8B 94 C6 80180000 - MOV RDX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x220797 + 4), (enable) ? newOff : off); // dmc3.exe+220797 - 48 8B 94 C6 80180000 - MOV RDX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2207C3 + 4), (enable) ? newOff : off); // dmc3.exe+2207C3 - 4C 8B 84 C6 80180000 - MOV R8,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x22081C + 4), (enable) ? newOff : off); // dmc3.exe+22081C - 48 8B 94 C6 80180000 - MOV RDX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x22083C + 4), (enable) ? newOff : off); // dmc3.exe+22083C - 48 8B 94 C6 80180000 - MOV RDX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x220894 + 4), (enable) ? newOff : off); // dmc3.exe+220894 - 48 8B 94 C6 80180000 - MOV RDX,[RSI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x222C61 + 4), (enable) ? newOff : off); // dmc3.exe+222C61 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x22316A + 4), (enable) ? newOff : off); // dmc3.exe+22316A - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2231DB + 4), (enable) ? newOff : off); // dmc3.exe+2231DB - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x223223 + 4), (enable) ? newOff : off); // dmc3.exe+223223 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x223295 + 4), (enable) ? newOff : off); // dmc3.exe+223295 - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2232D9 + 4), (enable) ? newOff : off); // dmc3.exe+2232D9 - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x223335 + 4), (enable) ? newOff : off); // dmc3.exe+223335 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2233A8 + 4), (enable) ? newOff : off); // dmc3.exe+2233A8 - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2233EF + 4), (enable) ? newOff : off); // dmc3.exe+2233EF - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x22464B + 4), (enable) ? newOff : off); // dmc3.exe+22464B - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2246DD + 4), (enable) ? newOff : off); // dmc3.exe+2246DD - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x224D88 + 4), (enable) ? newOff : off); // dmc3.exe+224D88 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2251F2 + 4), (enable) ? newOff : off); // dmc3.exe+2251F2 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x22531D + 4), (enable) ? newOff : off); // dmc3.exe+22531D - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x22553B + 4), (enable) ? newOff : off); // dmc3.exe+22553B - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x225602 + 4), (enable) ? newOff : off); // dmc3.exe+225602 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x225846 + 4), (enable) ? newOff : off); // dmc3.exe+225846 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x2258AE + 4), (enable) ? newOff : off); // dmc3.exe+2258AE - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x225A40 + 3), (enable) ? newOff : off); // dmc3.exe+225A40 - 4C 8B 83 80180000 - MOV R8,[RBX+00001880]
		Write<uint32>((appBaseAddr + 0x225A93 + 3), (enable) ? newOff : off); // dmc3.exe+225A93 - 48 8B 93 80180000 - MOV RDX,[RBX+00001880]
		Write<uint32>((appBaseAddr + 0x225BDD + 4), (enable) ? newOff : off); // dmc3.exe+225BDD - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x225C36 + 4), (enable) ? newOff : off); // dmc3.exe+225C36 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x225C56 + 4), (enable) ? newOff : off); // dmc3.exe+225C56 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x225C82 + 4), (enable) ? newOff : off); // dmc3.exe+225C82 - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x225CDB + 4), (enable) ? newOff : off); // dmc3.exe+225CDB - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x225CFB + 4), (enable) ? newOff : off); // dmc3.exe+225CFB - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x225D47 + 4), (enable) ? newOff : off); // dmc3.exe+225D47 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x226E08 + 4), (enable) ? newOff : off); // dmc3.exe+226E08 - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x226E75 + 4), (enable) ? newOff : off); // dmc3.exe+226E75 - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x22737C + 4), (enable) ? newOff : off); // dmc3.exe+22737C - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		Write<uint32>((appBaseAddr + 0x27A7E8 + 4), (enable) ? newOff : off); // dmc3.exe+27A7E8 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		// Unknown
		// Write<uint32>((appBaseAddr + 0x8CBB3 + 4), (enable) ? newOff : off); // dmc3.exe+8CBB3 - 48 8B 8C C3 80180000 - MOV RCX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x1F61AF + 4), (enable) ? newOff : off); // dmc3.exe+1F61AF - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x216129 + 4), (enable) ? newOff : off); // dmc3.exe+216129 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x2162C3 + 4), (enable) ? newOff : off); // dmc3.exe+2162C3 - 48 8B 94 C7 80180000 - MOV RDX,[RDI+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x224ED8 + 4), (enable) ? newOff : off); // dmc3.exe+224ED8 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x225028 + 4), (enable) ? newOff : off); // dmc3.exe+225028 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x225B03 + 4), (enable) ? newOff : off); // dmc3.exe+225B03 - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x225B5C + 4), (enable) ? newOff : off); // dmc3.exe+225B5C - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x225B83 + 4), (enable) ? newOff : off); // dmc3.exe+225B83 - 48 8B 94 C3 80180000 - MOV RDX,[RBX+RAX*8+00001880]
		// Write<uint32>((appBaseAddr + 0x226EE2 + 4), (enable) ? newOff : off); // dmc3.exe+226EE2 - 4C 8B 84 C3 80180000 - MOV R8,[RBX+RAX*8+00001880]
		// 0x310
		{
			constexpr auto off = (offsetof(PlayerActorData, modelPhysicsMetadataPool[0][0]) / 8);
			constexpr auto newOff = (offsetof(PlayerActorData, newModelPhysicsMetadataPool[0][0]) / 8);
			static_assert(off == 0x310);
			// Update Actor Dante
			Write<uint32>((appBaseAddr + 0x213E42 + 2), (enable) ? newOff : off); // dmc3.exe+213E42 - 48 05 10030000 - ADD RAX,00000310
			Write<uint32>((appBaseAddr + 0x214A06 + 2), (enable) ? newOff : off); // dmc3.exe+214A06 - 48 05 10030000 - ADD RAX,00000310
			// Update Actor Vergil
			Write<uint32>((appBaseAddr + 0x221077 + 2), (enable) ? newOff : off); // dmc3.exe+221077 - 48 05 10030000 - ADD RAX,00000310
			// Other
			Write<uint32>((appBaseAddr + 0x1DF131 + 3), (enable) ? newOff : off); // dmc3.exe+1DF131 - 48 81 C3 10030000 - ADD RBX,00000310
			// Unknown
			// Write<uint32>((appBaseAddr + 0x271850 + 3), (enable) ? newOff : off); // dmc3.exe+271850 - 48 81 C1 10030000 - ADD RCX,00000310
		}
		// 0x1820
		{
			constexpr auto off = (offsetof(PlayerActorData, modelPhysicsMetadataPool[0][0]) - 0x60);
			constexpr auto newOff = (offsetof(PlayerActorData, newModelPhysicsMetadataPool[0][0]) - 0x60);
			static_assert(off == 0x1820);
			// Other
			Write<uint32>((appBaseAddr + 0x1ED65A + 4), (enable) ? newOff : off); // dmc3.exe+1ED65A - 48 8B 94 C3 20180000 - MOV RDX,[RBX+RAX*8+00001820]
			// Unknown
			// Write<uint32>((appBaseAddr + 0xFA7F2 + 3), (enable) ? newOff : off); // dmc3.exe+FA7F2 - 48 8D 8E 20180000 - LEA RCX,[RSI+00001820]
			// Write<uint32>((appBaseAddr + 0xFA8B2 + 3), (enable) ? newOff : off); // dmc3.exe+FA8B2 - 48 8D 8E 20180000 - LEA RCX,[RSI+00001820]
		}
	}
	// 0x1888
	{
		constexpr auto off = offsetof(PlayerActorData, modelPhysicsMetadataPool[0][1]);
		constexpr auto newOff = offsetof(PlayerActorData, newModelPhysicsMetadataPool[0][1]);
		static_assert(off == 0x1888);
		// func_1EF040
		Write<uint32>((appBaseAddr + 0x1EF434 + 3), (enable) ? newOff : off); // dmc3.exe+1EF434 - 49 8B 85 88180000 - MOV RAX,[R13+00001888]
		// Other
		Write<uint32>((appBaseAddr + 0xBA9DE + 3), (enable) ? newOff : off); // dmc3.exe+BA9DE - 48 8B 96 88180000 - MOV RDX,[RSI+00001888]
		Write<uint32>((appBaseAddr + 0xBAAE5 + 3), (enable) ? newOff : off); // dmc3.exe+BAAE5 - 48 8B 96 88180000 - MOV RDX,[RSI+00001888]
		Write<uint32>((appBaseAddr + 0x212096 + 3), (enable) ? newOff : off); // dmc3.exe+212096 - 4C 8B 86 88180000 - MOV R8,[RSI+00001888]
		Write<uint32>((appBaseAddr + 0x2120E6 + 3), (enable) ? newOff : off); // dmc3.exe+2120E6 - 48 8B 96 88180000 - MOV RDX,[RSI+00001888]
		Write<uint32>((appBaseAddr + 0x2191DF + 3), (enable) ? newOff : off); // dmc3.exe+2191DF - 4C 8B 81 88180000 - MOV R8,[RCX+00001888]
		Write<uint32>((appBaseAddr + 0x21922C + 3), (enable) ? newOff : off); // dmc3.exe+21922C - 48 8B 97 88180000 - MOV RDX,[RDI+00001888]
		Write<uint32>((appBaseAddr + 0x2204D4 + 3), (enable) ? newOff : off); // dmc3.exe+2204D4 - 4C 8B 81 88180000 - MOV R8,[RCX+00001888]
		Write<uint32>((appBaseAddr + 0x220528 + 3), (enable) ? newOff : off); // dmc3.exe+220528 - 48 8B 96 88180000 - MOV RDX,[RSI+00001888]
	}
	// 0x1890
	{
		constexpr auto off = offsetof(PlayerActorData, modelPhysicsMetadataPool[0][2]);
		constexpr auto newOff = offsetof(PlayerActorData, newModelPhysicsMetadataPool[0][2]);
		static_assert(off == 0x1890);
		// func_1EF040
		Write<uint32>((appBaseAddr + 0x1EF30A + 3), (enable) ? newOff : off); // dmc3.exe+1EF30A - 49 8B 85 90180000 - MOV RAX,[R13+00001890]
	}
	// 0x1898
	{
		constexpr auto off = offsetof(PlayerActorData, modelPhysicsMetadataPool[0][3]);
		constexpr auto newOff = offsetof(PlayerActorData, newModelPhysicsMetadataPool[0][3]);
		static_assert(off == 0x1898);
		// func_1EF040
		Write<uint32>((appBaseAddr + 0x1EF1DE + 3), (enable) ? newOff : off); // dmc3.exe+1EF1DE - 49 8B 85 98180000 - MOV RAX,[R13+00001898]
		// Other
		Write<uint32>((appBaseAddr + 0xB9DF1 + 3), (enable) ? newOff : off); // dmc3.exe+B9DF1 - 48 8B 87 98180000 - MOV RAX,[RDI+00001898]
		Write<uint32>((appBaseAddr + 0xBA06E + 3), (enable) ? newOff : off); // dmc3.exe+BA06E - 48 8B 8F 98180000 - MOV RCX,[RDI+00001898]
		Write<uint32>((appBaseAddr + 0xBA9F4 + 3), (enable) ? newOff : off); // dmc3.exe+BA9F4 - 48 8B 96 98180000 - MOV RDX,[RSI+00001898]
		Write<uint32>((appBaseAddr + 0xBAAFB + 3), (enable) ? newOff : off); // dmc3.exe+BAAFB - 48 8B 96 98180000 - MOV RDX,[RSI+00001898]
		Write<uint32>((appBaseAddr + 0xC75A7 + 3), (enable) ? newOff : off); // dmc3.exe+C75A7 - 48 8B 96 98180000 - MOV RDX,[RSI+00001898]
		Write<uint32>((appBaseAddr + 0xC7A1D + 3), (enable) ? newOff : off); // dmc3.exe+C7A1D - 48 8B 97 98180000 - MOV RDX,[RDI+00001898]
		Write<uint32>((appBaseAddr + 0xCB18E + 3), (enable) ? newOff : off); // dmc3.exe+CB18E - 48 8B 8E 98180000 - MOV RCX,[RSI+00001898]
		Write<uint32>((appBaseAddr + 0x2120C4 + 3), (enable) ? newOff : off); // dmc3.exe+2120C4 - 48 8B 96 98180000 - MOV RDX,[RSI+00001898]
		Write<uint32>((appBaseAddr + 0x218EFD + 3), (enable) ? newOff : off); // dmc3.exe+218EFD - 48 8B 97 98180000 - MOV RDX,[RDI+00001898]
		Write<uint32>((appBaseAddr + 0x218F67 + 3), (enable) ? newOff : off); // dmc3.exe+218F67 - 48 8B 97 98180000 - MOV RDX,[RDI+00001898]
		Write<uint32>((appBaseAddr + 0x220506 + 3), (enable) ? newOff : off); // dmc3.exe+220506 - 48 8B 96 98180000 - MOV RDX,[RSI+00001898]
		Write<uint32>((appBaseAddr + 0x223068 + 3), (enable) ? newOff : off); // dmc3.exe+223068 - 4C 8B 81 98180000 - MOV R8,[RCX+00001898]
		Write<uint32>((appBaseAddr + 0x2230AA + 3), (enable) ? newOff : off); // dmc3.exe+2230AA - 4C 8B 83 98180000 - MOV R8,[RBX+00001898]
		Write<uint32>((appBaseAddr + 0x2230E0 + 3), (enable) ? newOff : off); // dmc3.exe+2230E0 - 48 8B 93 98180000 - MOV RDX,[RBX+00001898]
		Write<uint32>((appBaseAddr + 0x2243FB + 3), (enable) ? newOff : off); // dmc3.exe+2243FB - 48 8B 93 98180000 - MOV RDX,[RBX+00001898]
		Write<uint32>((appBaseAddr + 0x22445B + 3), (enable) ? newOff : off); // dmc3.exe+22445B - 48 8B 93 98180000 - MOV RDX,[RBX+00001898]
		Write<uint32>((appBaseAddr + 0x225A71 + 3), (enable) ? newOff : off); // dmc3.exe+225A71 - 48 8B 93 98180000 - MOV RDX,[RBX+00001898]
		Write<uint32>((appBaseAddr + 0x226D86 + 3), (enable) ? newOff : off); // dmc3.exe+226D86 - 4C 8B 81 98180000 - MOV R8,[RCX+00001898]
		Write<uint32>((appBaseAddr + 0x2272D1 + 3), (enable) ? newOff : off); // dmc3.exe+2272D1 - 48 8B 93 98180000 - MOV RDX,[RBX+00001898]
		// Unknown
		// Write<uint32>((appBaseAddr + 0xC823B + 3), (enable) ? newOff : off); // dmc3.exe+C823B - 48 8B 85 98180000 - MOV RAX,[RBP+00001898]
	}
	// 0x18A8
	{
		constexpr auto off = offsetof(PlayerActorData, modelPhysicsMetadataPool[0][5]);
		constexpr auto newOff = offsetof(PlayerActorData, newModelPhysicsMetadataPool[0][5]);
		static_assert(off == 0x18A8);
		// Other
		Write<uint32>((appBaseAddr + 0x986CE + 3), (enable) ? newOff : off); // dmc3.exe+986CE - 48 8B 81 A8180000 - MOV RAX,[RCX+000018A8]
		Write<uint32>((appBaseAddr + 0x9DB24 + 3), (enable) ? newOff : off); // dmc3.exe+9DB24 - 48 8B 81 A8180000 - MOV RAX,[RCX+000018A8]
		Write<uint32>((appBaseAddr + 0xA2A55 + 3), (enable) ? newOff : off); // dmc3.exe+A2A55 - 48 8B 81 A8180000 - MOV RAX,[RCX+000018A8]
		Write<uint32>((appBaseAddr + 0xA78C7 + 3), (enable) ? newOff : off); // dmc3.exe+A78C7 - 48 8B 81 A8180000 - MOV RAX,[RCX+000018A8]
		Write<uint32>((appBaseAddr + 0xA8F8D + 3), (enable) ? newOff : off); // dmc3.exe+A8F8D - 48 8B 81 A8180000 - MOV RAX,[RCX+000018A8]
		Write<uint32>((appBaseAddr + 0xAB6DA + 3), (enable) ? newOff : off); // dmc3.exe+AB6DA - 48 8B 81 A8180000 - MOV RAX,[RCX+000018A8]
		Write<uint32>((appBaseAddr + 0xB04AF + 3), (enable) ? newOff : off); // dmc3.exe+B04AF - 48 8B 81 A8180000 - MOV RAX,[RCX+000018A8]
		Write<uint32>((appBaseAddr + 0xB2B09 + 3), (enable) ? newOff : off); // dmc3.exe+B2B09 - 48 8B 81 A8180000 - MOV RAX,[RCX+000018A8]
		Write<uint32>((appBaseAddr + 0xB685E + 3), (enable) ? newOff : off); // dmc3.exe+B685E - 48 8B 81 A8180000 - MOV RAX,[RCX+000018A8]
		Write<uint32>((appBaseAddr + 0x1FAF4F + 3), (enable) ? newOff : off); // dmc3.exe+1FAF4F - 48 8B 81 A8180000 - MOV RAX,[RCX+000018A8]
		Write<uint32>((appBaseAddr + 0x1FAF93 + 3), (enable) ? newOff : off); // dmc3.exe+1FAF93 - 48 8B 81 A8180000 - MOV RAX,[RCX+000018A8]
		Write<uint32>((appBaseAddr + 0x1FAFA4 + 3), (enable) ? newOff : off); // dmc3.exe+1FAFA4 - 48 8B 81 A8180000 - MOV RAX,[RCX+000018A8]
		Write<uint32>((appBaseAddr + 0x1FC8F3 + 3), (enable) ? newOff : off); // dmc3.exe+1FC8F3 - 48 8B 81 A8180000 - MOV RAX,[RCX+000018A8]
		Write<uint32>((appBaseAddr + 0x21920A + 3), (enable) ? newOff : off); // dmc3.exe+21920A - 48 8B 97 A8180000 - MOV RDX,[RDI+000018A8]
		Write<uint32>((appBaseAddr + 0x219ACB + 3), (enable) ? newOff : off); // dmc3.exe+219ACB - 48 8B 97 A8180000 - MOV RDX,[RDI+000018A8]
	}
	// 0x18F8
	{
		constexpr auto off = offsetof(PlayerActorData, modelPhysicsMetadataPool[0][15]);
		constexpr auto newOff = offsetof(PlayerActorData, newModelPhysicsMetadataPool[0][15]);
		static_assert(off == 0x18F8);
		// Other
		Write<uint32>((appBaseAddr + 0xBAA0B + 3), (enable) ? newOff : off); // dmc3.exe+BAA0B - 48 8B 96 F8180000 - MOV RDX,[RSI+000018F8]
		Write<uint32>((appBaseAddr + 0xBAB12 + 3), (enable) ? newOff : off); // dmc3.exe+BAB12 - 48 8B 96 F8180000 - MOV RDX,[RSI+000018F8]
		// Unknown
		// Write<uint32>((appBaseAddr + 0x25AD52 + 3), (enable) ? newOff : off); // dmc3.exe+25AD52 - 48 8D B3 F8180000 - LEA RSI,[RBX+000018F8]
		// Write<uint32>((appBaseAddr + 0x25C5EC + 3), (enable) ? newOff : off); // dmc3.exe+25C5EC - 48 8D B7 F8180000 - LEA RSI,[RDI+000018F8]
		// Write<uint32>((appBaseAddr + 0x25D0C2 + 4), (enable) ? newOff : off); // dmc3.exe+25D0C2 - 48 89 84 CF F8180000 - MOV [RDI+RCX*8+000018F8],RAX
		// Write<uint32>((appBaseAddr + 0x25D0D1 + 4), (enable) ? newOff : off); // dmc3.exe+25D0D1 - 48 8B 8C C7 F8180000 - MOV RCX,[RDI+RAX*8+000018F8]
		// Write<uint32>((appBaseAddr + 0x25D0FA + 4), (enable) ? newOff : off); // dmc3.exe+25D0FA - 48 8B 8C C7 F8180000 - MOV RCX,[RDI+RAX*8+000018F8]
		// Write<uint32>((appBaseAddr + 0x25D2E2 + 3), (enable) ? newOff : off); // dmc3.exe+25D2E2 - 48 8D 8F F8180000 - LEA RCX,[RDI+000018F8]
		// Write<uint32>((appBaseAddr + 0x25D55C + 3), (enable) ? newOff : off); // dmc3.exe+25D55C - 48 8D BB F8180000 - LEA RDI,[RBX+000018F8]
		// Write<uint32>((appBaseAddr + 0x25D5A3 + 3), (enable) ? newOff : off); // dmc3.exe+25D5A3 - 48 8D BB F8180000 - LEA RDI,[RBX+000018F8]
	}
	// 0x1900
	{
		constexpr auto off = offsetof(PlayerActorData, modelPhysicsMetadataPool[0][16]);
		constexpr auto newOff = offsetof(PlayerActorData, newModelPhysicsMetadataPool[0][16]);
		static_assert(off == 0x1900);
		// Other
		Write<uint32>((appBaseAddr + 0xBAA25 + 3), (enable) ? newOff : off); // dmc3.exe+BAA25 - 48 8B 96 00190000 - MOV RDX,[RSI+00001900]
		Write<uint32>((appBaseAddr + 0xBAB2C + 3), (enable) ? newOff : off); // dmc3.exe+BAB2C - 48 8B 96 00190000 - MOV RDX,[RSI+00001900]
		// Unknown
		// Write<uint32>((appBaseAddr + 0x292170 + 2), (enable) ? newOff : off); // dmc3.exe+292170 - C7 83 00190000 05000000 - MOV [RBX+00001900],00000005
		// Write<uint32>((appBaseAddr + 0x292189 + 2), (enable) ? newOff : off); // dmc3.exe+292189 - C7 83 00190000 06000000 - MOV [RBX+00001900],00000006
	}
	// 0x1918
	{
		constexpr auto off = offsetof(PlayerActorData, modelPhysicsMetadataPool[0][19]);
		constexpr auto newOff = offsetof(PlayerActorData, newModelPhysicsMetadataPool[0][19]);
		static_assert(off == 0x1918);
		// Other
		Write<uint32>((appBaseAddr + 0xBAA3F + 3), (enable) ? newOff : off); // dmc3.exe+BAA3F - 48 8B 96 18190000 - MOV RDX,[RSI+00001918]
		Write<uint32>((appBaseAddr + 0xBAB46 + 3), (enable) ? newOff : off); // dmc3.exe+BAB46 - 48 8B 96 18190000 - MOV RDX,[RSI+00001918]
	}
	// 0x1920
	{
		constexpr auto off = offsetof(PlayerActorData, modelPhysicsMetadataPool[0][20]);
		constexpr auto newOff = offsetof(PlayerActorData, newModelPhysicsMetadataPool[0][20]);
		static_assert(off == 0x1920);
		// Other
		Write<uint32>((appBaseAddr + 0xBAA59 + 3), (enable) ? newOff : off); // dmc3.exe+BAA59 - 48 8B 96 20190000 - MOV RDX,[RSI+00001920]
		Write<uint32>((appBaseAddr + 0xBAB60 + 3), (enable) ? newOff : off); // dmc3.exe+BAB60 - 48 8B 96 20190000 - MOV RDX,[RSI+00001920]
	}
	// 0x1940
	{
		constexpr auto off = offsetof(PlayerActorData, modelPhysicsMetadataPool[1][0]);
		constexpr auto newOff = offsetof(PlayerActorData, newModelPhysicsMetadataPool[1][0]);
		static_assert(off == 0x1940);
		// func_1EF040
		Write<uint32>((appBaseAddr + 0x1EF2BB + 3), (enable) ? newOff : off); // dmc3.exe+1EF2BB - 4D 8D BD 40190000 - LEA R15,[R13+00001940]
	}
	// 0x1A00
	{
		constexpr auto off = offsetof(PlayerActorData, modelPhysicsMetadataPool[2][0]);
		constexpr auto newOff = offsetof(PlayerActorData, newModelPhysicsMetadataPool[2][0]);
		static_assert(off == 0x1A00);
		// func_1EF040
		Write<uint32>((appBaseAddr + 0x1EF18F + 3), (enable) ? newOff : off); // dmc3.exe+1EF18F - 4D 8D BD 001A0000 - LEA R15,[R13+00001A00]
	}
	// 0x1AC0
	{
		constexpr auto off = offsetof(PlayerActorData, modelPhysicsMetadataPool[3][0]);
		constexpr auto newOff = offsetof(PlayerActorData, newModelPhysicsMetadataPool[6][0]); // [3] -> [6]
		static_assert(off == 0x1AC0);
		// func_1EF040
		Write<uint32>((appBaseAddr + 0x1EF0A9 + 3), (enable) ? newOff : off); // dmc3.exe+1EF0A9 - 49 8D AD C01A0000 - LEA RBP,[R13+00001AC0]
	}
	// 0x1B88
	{
		constexpr auto off = offsetof(PlayerActorData, modelAllocationData[0]);
		constexpr auto newOff = offsetof(PlayerActorData, newModelAllocationData[0]);
		static_assert(off == 0x1B88);
		// func_1DD140
		Write<uint32>((appBaseAddr + 0x1DD1AA + 3), (enable) ? newOff : off); // dmc3.exe+1DD1AA - 49 8D 8E 881B0000 - LEA RCX,[R14+00001B88]
		// func_1DD210
		Write<uint32>((appBaseAddr + 0x1DD27A + 3), (enable) ? newOff : off); // dmc3.exe+1DD27A - 49 8D 8E 881B0000 - LEA RCX,[R14+00001B88]
		// func_1DD2E0
		Write<uint32>((appBaseAddr + 0x1DD34A + 3), (enable) ? newOff : off); // dmc3.exe+1DD34A - 49 8D 8E 881B0000 - LEA RCX,[R14+00001B88]
		// func_1DD3B0
		Write<uint32>((appBaseAddr + 0x1DD41A + 3), (enable) ? newOff : off); // dmc3.exe+1DD41A - 49 8D 8E 881B0000 - LEA RCX,[R14+00001B88]
		// func_1DDAF0
		Write<uint32>((appBaseAddr + 0x1DDB76 + 3), (enable) ? newOff : off); // dmc3.exe+1DDB76 - 48 8D 8E 881B0000 - LEA RCX,[RSI+00001B88]
		// func_1DE280
		Write<uint32>((appBaseAddr + 0x1DE3FB + 3), (enable) ? newOff : off); // dmc3.exe+1DE3FB - 48 8D 8F 881B0000 - LEA RCX,[RDI+00001B88]
		// func_1DE750
		Write<uint32>((appBaseAddr + 0x1DE7B3 + 3), (enable) ? newOff : off); // dmc3.exe+1DE7B3 - 48 8D 8F 881B0000 - LEA RCX,[RDI+00001B88]
		// Other
		Write<uint32>((appBaseAddr + 0x1DFAEE + 3), (enable) ? newOff : off); // dmc3.exe+1DFAEE - 48 81 C1 881B0000 - ADD RCX,00001B88
	}
	// 0x1B98
	{
		constexpr auto off = (offsetof(PlayerActorData, modelAllocationData[0]) + 0x10);
		constexpr auto newOff = (offsetof(PlayerActorData, newModelAllocationData[0]) + 0x10);
		static_assert(off == 0x1B98);
		// func_1DD140
		Write<uint32>((appBaseAddr + 0x1DD1BB + 3), (enable) ? newOff : off); // dmc3.exe+1DD1BB - 49 8B 8E 981B0000 - MOV RCX,[R14+00001B98]
		// func_1DD210
		Write<uint32>((appBaseAddr + 0x1DD28B + 3), (enable) ? newOff : off); // dmc3.exe+1DD28B - 49 8B 8E 981B0000 - MOV RCX,[R14+00001B98]
		// func_1DD2E0
		Write<uint32>((appBaseAddr + 0x1DD35B + 3), (enable) ? newOff : off); // dmc3.exe+1DD35B - 49 8B 8E 981B0000 - MOV RCX,[R14+00001B98]
		// func_1DD3B0
		Write<uint32>((appBaseAddr + 0x1DD42B + 3), (enable) ? newOff : off); // dmc3.exe+1DD42B - 49 8B 8E 981B0000 - MOV RCX,[R14+00001B98]
	}
	// 0x3B00
	{
		constexpr auto off = offsetof(PlayerActorData, recoveryData[0]);
		constexpr auto newOff = offsetof(PlayerActorData, newRecoveryData[0]);
		static_assert(off == 0x3B00);
		// func_1DDAF0
		Write<uint32>((appBaseAddr + 0x1DDC09 + 3), (enable) ? newOff : off); // dmc3.exe+1DDC09 - 48 8D 8E 003B0000 - LEA RCX,[RSI+00003B00]
		// func_1DE280
		Write<uint32>((appBaseAddr + 0x1DE3AD + 3), (enable) ? newOff : off); // dmc3.exe+1DE3AD - 48 8D 8F 003B0000 - LEA RCX,[RDI+00003B00]
		// func_1EF040
		Write<uint32>((appBaseAddr + 0x1EF408 + 3), (enable) ? newOff : off); // dmc3.exe+1EF408 - 49 8D 8D 003B0000 - LEA RCX,[R13+00003B00]
	}
	// 0x3B70
	{
		constexpr auto off = offsetof(PlayerActorData, recoveryData[1]);
		constexpr auto newOff = offsetof(PlayerActorData, newRecoveryData[1]);
		static_assert(off == 0x3B70);
		// func_1EF040
		Write<uint32>((appBaseAddr + 0x1EF2E1 + 3), (enable) ? newOff : off); // dmc3.exe+1EF2E1 - 49 8D 8D 703B0000 - LEA RCX,[R13+00003B70]
	}
	// 0x3BE0
	{
		constexpr auto off = offsetof(PlayerActorData, recoveryData[2]);
		constexpr auto newOff = offsetof(PlayerActorData, newRecoveryData[2]);
		static_assert(off == 0x3BE0);
		// func_1EF040
		Write<uint32>((appBaseAddr + 0x1EF1B5 + 3), (enable) ? newOff : off); // dmc3.exe+1EF1B5 - 49 8D 8D E03B0000 - LEA RCX,[R13+00003BE0]
	}
	// 0x3E74
	{
		constexpr auto off = offsetof(PlayerActorData, devilModels[0]);
		constexpr auto newOff = offsetof(PlayerActorData, newDevilModels[0]);
		static_assert(off == 0x3E74);
		// Update Actor Dante
		Write<uint32>((appBaseAddr + 0x213181 + 3), (enable) ? newOff : off); // dmc3.exe+213181 - C7 84 BE 743E0000 05000000 - MOV [RSI+RDI*4+00003E74],00000005
		Write<uint32>((appBaseAddr + 0x213580 + 3), (enable) ? newOff : off); // dmc3.exe+213580 - C7 84 BE 743E0000 04000000 - MOV [RSI+RDI*4+00003E74],00000004
		Write<uint32>((appBaseAddr + 0x213989 + 3), (enable) ? newOff : off); // dmc3.exe+213989 - C7 84 BE 743E0000 03000000 - MOV [RSI+RDI*4+00003E74],00000003
		Write<uint32>((appBaseAddr + 0x213FE0 + 4), (enable) ? newOff : off); // dmc3.exe+213FE0 - 42 C7 84 AE 743E0000 02000000 - MOV [RSI+R13*4+00003E74],00000002
		Write<uint32>((appBaseAddr + 0x21410F + 3), (enable) ? newOff : off); // dmc3.exe+21410F - C7 84 BE 743E0000 01000000 - MOV [RSI+RDI*4+00003E74],00000001
		Write<uint32>((appBaseAddr + 0x21450A + 3), (enable) ? newOff : off); // dmc3.exe+21450A - C7 84 BE 743E0000 00000000 - MOV [RSI+RDI*4+00003E74],00000000
		// Update Actor Bob
		Write<uint32>((appBaseAddr + 0x2263C0 + 4), (enable) ? newOff : off); // dmc3.exe+2263C0 - 41 C7 84 9E 743E0000 00000000 - MOV [R14+RBX*4+00003E74],00000000
		// Write<uint32>((appBaseAddr + 0x22692E + 4), (enable) ? newOff : off); // dmc3.exe+22692E - 41 C7 84 9E 743E0000 04000000 - MOV [R14+RBX*4+00003E74],00000004
		// Update Actor Vergil
		Write<uint32>((appBaseAddr + 0x220D9E + 4), (enable) ? newOff : off); // dmc3.exe+220D9E - 41 C7 84 BC 743E0000 06000000 - MOV [R12+RDI*4+00003E74],00000006
		Write<uint32>((appBaseAddr + 0x221198 + 4), (enable) ? newOff : off); // dmc3.exe+221198 - 41 C7 84 BC 743E0000 04000000 - MOV [R12+RDI*4+00003E74],00000004
		Write<uint32>((appBaseAddr + 0x2215A0 + 4), (enable) ? newOff : off); // dmc3.exe+2215A0 - 45 89 B4 BC 743E0000 - MOV [R12+RDI*4+00003E74],R14D
		// func_1F7BE0
		Write<uint32>((appBaseAddr + 0x1F7E5A + 2), (enable) ? newOff : off); // dmc3.exe+1F7E5A - C7 83 743E0000 FFFFFFFF - MOV [RBX+00003E74],FFFFFFFF
		// Other
		Write<uint32>((appBaseAddr + 0x90B67 + 4), (enable) ? newOff : off); // dmc3.exe+90B67 - 41 8B 8C 86 743E0000 - MOV ECX,[R14+RAX*4+00003E74]
		Write<uint32>((appBaseAddr + 0x1FAB17 + 3), (enable) ? newOff : off); // dmc3.exe+1FAB17 - 8B 84 81 743E0000 - MOV EAX,[RCX+RAX*4+00003E74]
		Write<uint32>((appBaseAddr + 0x1FAB34 + 4), (enable) ? newOff : off); // dmc3.exe+1FAB34 - 48 63 94 81 743E0000 - MOVSXD RDX,DWORD PTR [RCX+RAX*4+00003E74]
		Write<uint32>((appBaseAddr + 0x212110 + 3), (enable) ? newOff : off); // dmc3.exe+212110 - 8B 94 81 743E0000 - MOV EDX,[RCX+RAX*4+00003E74]
		Write<uint32>((appBaseAddr + 0x2189B0 + 3), (enable) ? newOff : off); // dmc3.exe+2189B0 - 8B 94 8F 743E0000 - MOV EDX,[RDI+RCX*4+00003E74]
		Write<uint32>((appBaseAddr + 0x220552 + 3), (enable) ? newOff : off); // dmc3.exe+220552 - 8B 8C 81 743E0000 - MOV ECX,[RCX+RAX*4+00003E74]
		Write<uint32>((appBaseAddr + 0x2244A8 + 3), (enable) ? newOff : off); // dmc3.exe+2244A8 - 8B 8C 83 743E0000 - MOV ECX,[RBX+RAX*4+00003E74]
		Write<uint32>((appBaseAddr + 0x2296B3 + 3), (enable) ? newOff : off); // dmc3.exe+2296B3 - 83 BC 81 743E0000 04 - CMP DWORD PTR [RCX+RAX*4+00003E74],04
		// Unknown
		// Write<uint32>((appBaseAddr + 0x4B950 + 2), (enable) ? newOff : off); // dmc3.exe+4B950 - C7 83 743E0000 01000000 - MOV [RBX+00003E74],00000001
	}
	// 0x6498
	{
		constexpr auto off = offsetof(PlayerActorData, weapons[0]);
		constexpr auto newOff = offsetof(PlayerActorData, newWeapons[0]);
		static_assert(off == 0x6498);
		// Init Actor Dante
		Write<uint32>((appBaseAddr + 0x217BF4 + 2), (enable) ? newOff : off); // dmc3.exe+217BF4 - 88 81 98640000 - MOV [RCX+00006498],AL
		// Init Actor Bob
		Write<uint32>((appBaseAddr + 0x226F53 + 2), (enable) ? newOff : off); // dmc3.exe+226F53 - C7 81 98640000 0EFFFFFF - MOV [RCX+00006498],FFFFFF0E
		// Init Actor Lady
		Write<uint32>((appBaseAddr + 0x2196AA + 2), (enable) ? newOff : off); // dmc3.exe+2196AA - C7 81 98640000 FFFF090A - MOV [RCX+00006498],0A09FFFF
		// Init Actor Vergil
		Write<uint32>((appBaseAddr + 0x223D11 + 2), (enable) ? newOff : off); // dmc3.exe+223D11 - C7 81 98640000 0B0C0DFF - MOV [RCX+00006498],FF0D0C0B
		// Update Actor Dante
		Write<uint32>((appBaseAddr + 0x212D9A + 3), (enable) ? newOff : off); // dmc3.exe+212D9A - 4C 8D A6 98640000 - LEA R12,[RSI+00006498]
		Write<uint32>((appBaseAddr + 0x213423 + 3), (enable) ? newOff : off); // dmc3.exe+213423 - 4C 8D A6 98640000 - LEA R12,[RSI+00006498]
		Write<uint32>((appBaseAddr + 0x2143AC + 3), (enable) ? newOff : off); // dmc3.exe+2143AC - 4C 8D A6 98640000 - LEA R12,[RSI+00006498]
		Write<uint32>((appBaseAddr + 0x214A5F + 3), (enable) ? newOff : off); // dmc3.exe+214A5F - 4C 8D A6 98640000 - LEA R12,[RSI+00006498]
		Write<uint32>((appBaseAddr + 0x214BD2 + 3), (enable) ? newOff : off); // dmc3.exe+214BD2 - 80 BC 30 98640000 04 - CMP BYTE PTR [RAX+RSI+00006498],04
		// Update Actor Bob
		Write<uint32>((appBaseAddr + 0x22629D + 3), (enable) ? newOff : off); // dmc3.exe+22629D - 49 8D 86 98640000 - LEA RAX,[R14+00006498]
		Write<uint32>((appBaseAddr + 0x22639B + 5), (enable) ? newOff : off); // dmc3.exe+22639B - 42 0FB6 84 31 98640000 - MOVZX EAX,BYTE PTR [RCX+R14+00006498]
		// Update Actor Lady
		Write<uint32>((appBaseAddr + 0x21959D + 3), (enable) ? newOff : off); // dmc3.exe+21959D - 48 8D 9D 98640000 - LEA RBX,[RBP+00006498]
		// Register Weapons
		Write<uint32>((appBaseAddr + 0x1DED41 + 3), (enable) ? newOff : off); // dmc3.exe+1DED41 - 48 8D A9 98640000 - LEA RBP,[RCX+00006498]
		// Weapon Switch Controller Dante
		Write<uint32>((appBaseAddr + 0x1EA987 + 5), (enable) ? newOff : off); // dmc3.exe+1EA987 - 44 0FB6 84 3B 98640000 - MOVZX R8D,BYTE PTR [RBX+RDI+00006498]
		Write<uint32>((appBaseAddr + 0x1EA99D + 3), (enable) ? newOff : off); // dmc3.exe+1EA99D - 80 BC 38 98640000 FF - CMP BYTE PTR [RAX+RDI+00006498],-01
		Write<uint32>((appBaseAddr + 0x1EA9AF + 4), (enable) ? newOff : off); // dmc3.exe+1EA9AF - 44 3A 84 38 98640000 - CMP R8L,[RAX+RDI+00006498]
		Write<uint32>((appBaseAddr + 0x1EAA74 + 4), (enable) ? newOff : off); // dmc3.exe+1EAA74 - 0FB6 8C 3B 98640000 - MOVZX ECX,BYTE PTR [RBX+RDI+00006498]
		Write<uint32>((appBaseAddr + 0x1EAA8A + 3), (enable) ? newOff : off); // dmc3.exe+1EAA8A - 80 BC 3B 98640000 FF - CMP BYTE PTR [RBX+RDI+00006498],-01
		Write<uint32>((appBaseAddr + 0x1EAA9F + 3), (enable) ? newOff : off); // dmc3.exe+1EAA9F - 3A 8C 3B 98640000 - CMP CL,[RBX+RDI+00006498]
		// func_1F7BE0
		Write<uint32>((appBaseAddr + 0x1F80B1 + 4), (enable) ? newOff : off); // dmc3.exe+1F80B1 - 0FB6 84 19 98640000 - MOVZX EAX,BYTE PTR [RCX+RBX+00006498]
		Write<uint32>((appBaseAddr + 0x1F80BF + 4), (enable) ? newOff : off); // dmc3.exe+1F80BF - 0FB6 84 19 98640000 - MOVZX EAX,BYTE PTR [RCX+RBX+00006498]
		Write<uint32>((appBaseAddr + 0x1F80D4 + 4), (enable) ? newOff : off); // dmc3.exe+1F80D4 - 0FB6 8C 18 98640000 - MOVZX ECX,BYTE PTR [RAX+RBX+00006498]
		// func_2198D0
		Write<uint32>((appBaseAddr + 0x2198D0 + 3), (enable) ? newOff : off); // dmc3.exe+2198D0 - 0FB6 81 98640000 - MOVZX EAX,BYTE PTR [RCX+00006498]
		// func_2241F0
		Write<uint32>((appBaseAddr + 0x2241F0 + 3), (enable) ? newOff : off); // dmc3.exe+2241F0 - 0FB6 81 98640000 - MOVZX EAX,BYTE PTR [RCX+00006498]
		// Other
		Write<uint32>((appBaseAddr + 0x1D91E0 + 3), (enable) ? newOff : off); // dmc3.exe+1D91E0 - 80 BC 11 98640000 0D - CMP BYTE PTR [RCX+RDX+00006498],0D
		Write<uint32>((appBaseAddr + 0x1E02A2 + 4), (enable) ? newOff : off); // dmc3.exe+1E02A2 - 40 38 B4 18 98640000 - CMP [RAX+RBX+00006498],SIL
		Write<uint32>((appBaseAddr + 0x1E088D + 3), (enable) ? newOff : off); // dmc3.exe+1E088D - 80 BC 18 98640000 05 - CMP BYTE PTR [RAX+RBX+00006498],05
		Write<uint32>((appBaseAddr + 0x1E090C + 4), (enable) ? newOff : off); // dmc3.exe+1E090C - 0FB6 8C 18 98640000 - MOVZX ECX,BYTE PTR [RAX+RBX+00006498]
		Write<uint32>((appBaseAddr + 0x1E0923 + 4), (enable) ? newOff : off); // dmc3.exe+1E0923 - 0FB6 8C 18 98640000 - MOVZX ECX,BYTE PTR [RAX+RBX+00006498]
		Write<uint32>((appBaseAddr + 0x1E28E6 + 4), (enable) ? newOff : off); // dmc3.exe+1E28E6 - 0FB6 B4 08 98640000 - MOVZX ESI,BYTE PTR [RAX+RCX+00006498]
		Write<uint32>((appBaseAddr + 0x1E64DB + 4), (enable) ? newOff : off); // dmc3.exe+1E64DB - 0FB6 8C 18 98640000 - MOVZX ECX,BYTE PTR [RAX+RBX+00006498]
		Write<uint32>((appBaseAddr + 0x1E64FB + 4), (enable) ? newOff : off); // dmc3.exe+1E64FB - 0FB6 8C 18 98640000 - MOVZX ECX,BYTE PTR [RAX+RBX+00006498]
		Write<uint32>((appBaseAddr + 0x1E657D + 3), (enable) ? newOff : off); // dmc3.exe+1E657D - 80 BC 18 98640000 07 - CMP BYTE PTR [RAX+RBX+00006498],07
		Write<uint32>((appBaseAddr + 0x1E6BB8 + 4), (enable) ? newOff : off); // dmc3.exe+1E6BB8 - 0FB6 8C 1A 98640000 - MOVZX ECX,BYTE PTR [RDX+RBX+00006498]
		Write<uint32>((appBaseAddr + 0x1E6C03 + 4), (enable) ? newOff : off); // dmc3.exe+1E6C03 - 0FB6 8C 18 98640000 - MOVZX ECX,BYTE PTR [RAX+RBX+00006498]
		Write<uint32>((appBaseAddr + 0x1E6C35 + 4), (enable) ? newOff : off); // dmc3.exe+1E6C35 - 0FB6 84 1A 98640000 - MOVZX EAX,BYTE PTR [RDX+RBX+00006498]
		Write<uint32>((appBaseAddr + 0x1E6D9B + 4), (enable) ? newOff : off); // dmc3.exe+1E6D9B - 0FB6 8C 18 98640000 - MOVZX ECX,BYTE PTR [RAX+RBX+00006498]
		Write<uint32>((appBaseAddr + 0x1E70DD + 4), (enable) ? newOff : off); // dmc3.exe+1E70DD - 40 3A BC 18 98640000 - CMP DIL,[RAX+RBX+00006498]
		Write<uint32>((appBaseAddr + 0x1E70EE + 4), (enable) ? newOff : off); // dmc3.exe+1E70EE - 40 3A BC 18 98640000 - CMP DIL,[RAX+RBX+00006498]
		Write<uint32>((appBaseAddr + 0x1E711C + 4), (enable) ? newOff : off); // dmc3.exe+1E711C - 40 3A BC 18 98640000 - CMP DIL,[RAX+RBX+00006498]
		Write<uint32>((appBaseAddr + 0x1E714A + 4), (enable) ? newOff : off); // dmc3.exe+1E714A - 40 3A BC 18 98640000 - CMP DIL,[RAX+RBX+00006498]
		Write<uint32>((appBaseAddr + 0x1E7174 + 4), (enable) ? newOff : off); // dmc3.exe+1E7174 - 40 3A BC 18 98640000 - CMP DIL,[RAX+RBX+00006498]
		Write<uint32>((appBaseAddr + 0x1E7185 + 4), (enable) ? newOff : off); // dmc3.exe+1E7185 - 40 3A BC 18 98640000 - CMP DIL,[RAX+RBX+00006498]
		Write<uint32>((appBaseAddr + 0x1E7E93 + 3), (enable) ? newOff : off); // dmc3.exe+1E7E93 - 80 BC 18 98640000 03 - CMP BYTE PTR [RAX+RBX+00006498],03
		Write<uint32>((appBaseAddr + 0x1E927F + 5), (enable) ? newOff : off); // dmc3.exe+1E927F - 42 0FB6 8C 00 98640000 - MOVZX ECX,BYTE PTR [RAX+R8+00006498]
		Write<uint32>((appBaseAddr + 0x1E9B04 + 4), (enable) ? newOff : off); // dmc3.exe+1E9B04 - 0FB6 8C 18 98640000 - MOVZX ECX,BYTE PTR [RAX+RBX+00006498]
		Write<uint32>((appBaseAddr + 0x1EADEA + 4), (enable) ? newOff : off); // dmc3.exe+1EADEA - 0FBE 8C 08 98640000 - MOVSX ECX,BYTE PTR [RAX+RCX+00006498]
		Write<uint32>((appBaseAddr + 0x1EAE10 + 3), (enable) ? newOff : off); // dmc3.exe+1EAE10 - 80 BC 11 98640000 05 - CMP BYTE PTR [RCX+RDX+00006498],05
		Write<uint32>((appBaseAddr + 0x1EB1E5 + 3), (enable) ? newOff : off); // dmc3.exe+1EB1E5 - 80 BC 18 98640000 07 - CMP BYTE PTR [RAX+RBX+00006498],07
		Write<uint32>((appBaseAddr + 0x1F59B1 + 3), (enable) ? newOff : off); // dmc3.exe+1F59B1 - 80 BC 31 98640000 05 - CMP BYTE PTR [RCX+RSI+00006498],05
		Write<uint32>((appBaseAddr + 0x1F59D7 + 3), (enable) ? newOff : off); // dmc3.exe+1F59D7 - 80 BC 30 98640000 05 - CMP BYTE PTR [RAX+RSI+00006498],05
		Write<uint32>((appBaseAddr + 0x1F6674 + 4), (enable) ? newOff : off); // dmc3.exe+1F6674 - 40 38 BC 18 98640000 - CMP [RAX+RBX+00006498],DIL
		Write<uint32>((appBaseAddr + 0x1F66A9 + 4), (enable) ? newOff : off); // dmc3.exe+1F66A9 - 40 38 BC 18 98640000 - CMP [RAX+RBX+00006498],DIL
		Write<uint32>((appBaseAddr + 0x1F7607 + 3), (enable) ? newOff : off); // dmc3.exe+1F7607 - 80 BC 18 98640000 07 - CMP BYTE PTR [RAX+RBX+00006498],07
		Write<uint32>((appBaseAddr + 0x1F762A + 3), (enable) ? newOff : off); // dmc3.exe+1F762A - 80 BC 18 98640000 07 - CMP BYTE PTR [RAX+RBX+00006498],07
		Write<uint32>((appBaseAddr + 0x1F9445 + 4), (enable) ? newOff : off); // dmc3.exe+1F9445 - 0FBE 94 08 98640000 - MOVSX EDX,BYTE PTR [RAX+RCX+00006498]
		Write<uint32>((appBaseAddr + 0x1FACA0 + 3), (enable) ? newOff : off); // dmc3.exe+1FACA0 - 38 94 08 98640000 - CMP [RAX+RCX+00006498],DL
		Write<uint32>((appBaseAddr + 0x1FAD00 + 3), (enable) ? newOff : off); // dmc3.exe+1FAD00 - 38 94 08 98640000 - CMP [RAX+RCX+00006498],DL
		Write<uint32>((appBaseAddr + 0x1FAD40 + 3), (enable) ? newOff : off); // dmc3.exe+1FAD40 - 38 94 08 98640000 - CMP [RAX+RCX+00006498],DL
		Write<uint32>((appBaseAddr + 0x1FB13F + 3), (enable) ? newOff : off); // dmc3.exe+1FB13F - 80 BC 08 98640000 00 - CMP BYTE PTR [RAX+RCX+00006498],00
		Write<uint32>((appBaseAddr + 0x1FD143 + 3), (enable) ? newOff : off); // dmc3.exe+1FD143 - 38 94 08 98640000 - CMP [RAX+RCX+00006498],DL
		Write<uint32>((appBaseAddr + 0x1FD173 + 4), (enable) ? newOff : off); // dmc3.exe+1FD173 - 41 38 94 09 98640000 - CMP [R9+RCX+00006498],DL
		Write<uint32>((appBaseAddr + 0x1FD1A6 + 4), (enable) ? newOff : off); // dmc3.exe+1FD1A6 - 0FB6 8C 08 98640000 - MOVZX ECX,BYTE PTR [RAX+RCX+00006498]
		Write<uint32>((appBaseAddr + 0x1FD1D0 + 3), (enable) ? newOff : off); // dmc3.exe+1FD1D0 - 38 94 08 98640000 - CMP [RAX+RCX+00006498],DL
		Write<uint32>((appBaseAddr + 0x1FD651 + 4), (enable) ? newOff : off); // dmc3.exe+1FD651 - 44 38 84 10 98640000 - CMP [RAX+RDX+00006498],R8L
		Write<uint32>((appBaseAddr + 0x20477A + 4), (enable) ? newOff : off); // dmc3.exe+20477A - 0FB6 8C 18 98640000 - MOVZX ECX,BYTE PTR [RAX+RBX+00006498]
		Write<uint32>((appBaseAddr + 0x204A45 + 4), (enable) ? newOff : off); // dmc3.exe+204A45 - 0FB6 8C 18 98640000 - MOVZX ECX,BYTE PTR [RAX+RBX+00006498]
		Write<uint32>((appBaseAddr + 0x204AD4 + 3), (enable) ? newOff : off); // dmc3.exe+204AD4 - 80 BC 18 98640000 03 - CMP BYTE PTR [RAX+RBX+00006498],03
		Write<uint32>((appBaseAddr + 0x204B4A + 3), (enable) ? newOff : off); // dmc3.exe+204B4A - 80 BC 18 98640000 03 - CMP BYTE PTR [RAX+RBX+00006498],03
		Write<uint32>((appBaseAddr + 0x20511E + 3), (enable) ? newOff : off); // dmc3.exe+20511E - 80 BC 18 98640000 05 - CMP BYTE PTR [RAX+RBX+00006498],05
		Write<uint32>((appBaseAddr + 0x205273 + 3), (enable) ? newOff : off); // dmc3.exe+205273 - 80 BC 18 98640000 05 - CMP BYTE PTR [RAX+RBX+00006498],05
		Write<uint32>((appBaseAddr + 0x20530B + 3), (enable) ? newOff : off); // dmc3.exe+20530B - 80 BC 18 98640000 05 - CMP BYTE PTR [RAX+RBX+00006498],05
		Write<uint32>((appBaseAddr + 0x2054D1 + 3), (enable) ? newOff : off); // dmc3.exe+2054D1 - 80 BC 18 98640000 05 - CMP BYTE PTR [RAX+RBX+00006498],05
		Write<uint32>((appBaseAddr + 0x206172 + 3), (enable) ? newOff : off); // dmc3.exe+206172 - 80 BC 18 98640000 09 - CMP BYTE PTR [RAX+RBX+00006498],09
		Write<uint32>((appBaseAddr + 0x206192 + 3), (enable) ? newOff : off); // dmc3.exe+206192 - 80 BC 18 98640000 09 - CMP BYTE PTR [RAX+RBX+00006498],09
		Write<uint32>((appBaseAddr + 0x2063A0 + 3), (enable) ? newOff : off); // dmc3.exe+2063A0 - 80 BC 19 98640000 09 - CMP BYTE PTR [RCX+RBX+00006498],09
		Write<uint32>((appBaseAddr + 0x206510 + 3), (enable) ? newOff : off); // dmc3.exe+206510 - 80 BC 19 98640000 09 - CMP BYTE PTR [RCX+RBX+00006498],09
		Write<uint32>((appBaseAddr + 0x208220 + 3), (enable) ? newOff : off); // dmc3.exe+208220 - 80 BC 1F 98640000 00 - CMP BYTE PTR [RDI+RBX+00006498],00
		Write<uint32>((appBaseAddr + 0x208281 + 3), (enable) ? newOff : off); // dmc3.exe+208281 - 80 BC 18 98640000 00 - CMP BYTE PTR [RAX+RBX+00006498],00
		Write<uint32>((appBaseAddr + 0x2086E5 + 3), (enable) ? newOff : off); // dmc3.exe+2086E5 - 80 BC 18 98640000 08 - CMP BYTE PTR [RAX+RBX+00006498],08
		Write<uint32>((appBaseAddr + 0x208713 + 3), (enable) ? newOff : off); // dmc3.exe+208713 - 80 BC 18 98640000 08 - CMP BYTE PTR [RAX+RBX+00006498],08
		Write<uint32>((appBaseAddr + 0x208CF8 + 3), (enable) ? newOff : off); // dmc3.exe+208CF8 - 80 BC 18 98640000 06 - CMP BYTE PTR [RAX+RBX+00006498],06
		Write<uint32>((appBaseAddr + 0x208DFF + 3), (enable) ? newOff : off); // dmc3.exe+208DFF - 80 BC 18 98640000 06 - CMP BYTE PTR [RAX+RBX+00006498],06
		Write<uint32>((appBaseAddr + 0x20D1B2 + 3), (enable) ? newOff : off); // dmc3.exe+20D1B2 - 80 BC 18 98640000 05 - CMP BYTE PTR [RAX+RBX+00006498],05
		Write<uint32>((appBaseAddr + 0x20E302 + 3), (enable) ? newOff : off); // dmc3.exe+20E302 - 80 BC 18 98640000 08 - CMP BYTE PTR [RAX+RBX+00006498],08
		Write<uint32>((appBaseAddr + 0x20E332 + 3), (enable) ? newOff : off); // dmc3.exe+20E332 - 80 BC 18 98640000 08 - CMP BYTE PTR [RAX+RBX+00006498],08
		Write<uint32>((appBaseAddr + 0x20E363 + 3), (enable) ? newOff : off); // dmc3.exe+20E363 - 80 BC 18 98640000 08 - CMP BYTE PTR [RAX+RBX+00006498],08
		Write<uint32>((appBaseAddr + 0x20E662 + 3), (enable) ? newOff : off); // dmc3.exe+20E662 - 80 BC 18 98640000 08 - CMP BYTE PTR [RAX+RBX+00006498],08
		Write<uint32>((appBaseAddr + 0x20E713 + 3), (enable) ? newOff : off); // dmc3.exe+20E713 - 80 BC 18 98640000 08 - CMP BYTE PTR [RAX+RBX+00006498],08
		Write<uint32>((appBaseAddr + 0x210A22 + 4), (enable) ? newOff : off); // dmc3.exe+210A22 - 44 38 84 18 98640000 - CMP [RAX+RBX+00006498],R8L
		Write<uint32>((appBaseAddr + 0x210C00 + 3), (enable) ? newOff : off); // dmc3.exe+210C00 - 80 BC 1F 98640000 00 - CMP BYTE PTR [RDI+RBX+00006498],00
		Write<uint32>((appBaseAddr + 0x210C40 + 3), (enable) ? newOff : off); // dmc3.exe+210C40 - 80 BC 19 98640000 00 - CMP BYTE PTR [RCX+RBX+00006498],00
		Write<uint32>((appBaseAddr + 0x2113D1 + 3), (enable) ? newOff : off); // dmc3.exe+2113D1 - 80 BC 37 98640000 00 - CMP BYTE PTR [RDI+RSI+00006498],00
		Write<uint32>((appBaseAddr + 0x2114C0 + 3), (enable) ? newOff : off); // dmc3.exe+2114C0 - 80 BC 37 98640000 00 - CMP BYTE PTR [RDI+RSI+00006498],00
		Write<uint32>((appBaseAddr + 0x2115E0 + 3), (enable) ? newOff : off); // dmc3.exe+2115E0 - 80 BC 37 98640000 00 - CMP BYTE PTR [RDI+RSI+00006498],00
		Write<uint32>((appBaseAddr + 0x211682 + 4), (enable) ? newOff : off); // dmc3.exe+211682 - 40 38 BC 30 98640000 - CMP [RAX+RSI+00006498],DIL
		Write<uint32>((appBaseAddr + 0x211723 + 3), (enable) ? newOff : off); // dmc3.exe+211723 - 80 BC 37 98640000 00 - CMP BYTE PTR [RDI+RSI+00006498],00
		Write<uint32>((appBaseAddr + 0x211782 + 4), (enable) ? newOff : off); // dmc3.exe+211782 - 40 38 BC 30 98640000 - CMP [RAX+RSI+00006498],DIL
		Write<uint32>((appBaseAddr + 0x212A3C + 3), (enable) ? newOff : off); // dmc3.exe+212A3C - 0FB6 81 98640000 - MOVZX EAX,BYTE PTR [RCX+00006498]
		Write<uint32>((appBaseAddr + 0x2155F6 + 3), (enable) ? newOff : off); // dmc3.exe+2155F6 - 48 81 C1 98640000 - ADD RCX,00006498
		Write<uint32>((appBaseAddr + 0x215702 + 4), (enable) ? newOff : off); // dmc3.exe+215702 - 44 38 B4 38 98640000 - CMP [RAX+RDI+00006498],R14L
		Write<uint32>((appBaseAddr + 0x215899 + 4), (enable) ? newOff : off); // dmc3.exe+215899 - 44 38 B4 38 98640000 - CMP [RAX+RDI+00006498],R14L
		Write<uint32>((appBaseAddr + 0x2158B2 + 4), (enable) ? newOff : off); // dmc3.exe+2158B2 - 44 38 B4 38 98640000 - CMP [RAX+RDI+00006498],R14L
		Write<uint32>((appBaseAddr + 0x215948 + 4), (enable) ? newOff : off); // dmc3.exe+215948 - 44 38 B4 38 98640000 - CMP [RAX+RDI+00006498],R14L
		Write<uint32>((appBaseAddr + 0x215972 + 4), (enable) ? newOff : off); // dmc3.exe+215972 - 44 38 B4 38 98640000 - CMP [RAX+RDI+00006498],R14L
		Write<uint32>((appBaseAddr + 0x2159CE + 4), (enable) ? newOff : off); // dmc3.exe+2159CE - 44 38 B4 38 98640000 - CMP [RAX+RDI+00006498],R14L
		Write<uint32>((appBaseAddr + 0x2159E2 + 4), (enable) ? newOff : off); // dmc3.exe+2159E2 - 44 38 B4 38 98640000 - CMP [RAX+RDI+00006498],R14L
		Write<uint32>((appBaseAddr + 0x215BD2 + 3), (enable) ? newOff : off); // dmc3.exe+215BD2 - 80 BC 38 98640000 07 - CMP BYTE PTR [RAX+RDI+00006498],07
		Write<uint32>((appBaseAddr + 0x215C1D + 4), (enable) ? newOff : off); // dmc3.exe+215C1D - 0FB6 9C 38 98640000 - MOVZX EBX,BYTE PTR [RAX+RDI+00006498]
		Write<uint32>((appBaseAddr + 0x215E82 + 3), (enable) ? newOff : off); // dmc3.exe+215E82 - 80 BC 38 98640000 07 - CMP BYTE PTR [RAX+RDI+00006498],07
		Write<uint32>((appBaseAddr + 0x215EA2 + 3), (enable) ? newOff : off); // dmc3.exe+215EA2 - 80 BC 38 98640000 07 - CMP BYTE PTR [RAX+RDI+00006498],07
		Write<uint32>((appBaseAddr + 0x21609D + 4), (enable) ? newOff : off); // dmc3.exe+21609D - 0FB6 B4 38 98640000 - MOVZX ESI,BYTE PTR [RAX+RDI+00006498]
		Write<uint32>((appBaseAddr + 0x2161D2 + 5), (enable) ? newOff : off); // dmc3.exe+2161D2 - 44 0FBE 8C 38 98640000 - MOVSX R9D,BYTE PTR [RAX+RDI+00006498]
		Write<uint32>((appBaseAddr + 0x2163E7 + 5), (enable) ? newOff : off); // dmc3.exe+2163E7 - 44 0FBE 8C 38 98640000 - MOVSX R9D,BYTE PTR [RAX+RDI+00006498]
		Write<uint32>((appBaseAddr + 0x216E42 + 3), (enable) ? newOff : off); // dmc3.exe+216E42 - 80 BC 38 98640000 05 - CMP BYTE PTR [RAX+RDI+00006498],05
		Write<uint32>((appBaseAddr + 0x217012 + 3), (enable) ? newOff : off); // dmc3.exe+217012 - 80 BC 38 98640000 05 - CMP BYTE PTR [RAX+RDI+00006498],05
		Write<uint32>((appBaseAddr + 0x2171E2 + 3), (enable) ? newOff : off); // dmc3.exe+2171E2 - 80 BC 38 98640000 05 - CMP BYTE PTR [RAX+RDI+00006498],05
		Write<uint32>((appBaseAddr + 0x217362 + 3), (enable) ? newOff : off); // dmc3.exe+217362 - 80 BC 38 98640000 05 - CMP BYTE PTR [RAX+RDI+00006498],05
		Write<uint32>((appBaseAddr + 0x217473 + 3), (enable) ? newOff : off); // dmc3.exe+217473 - 80 BC 38 98640000 05 - CMP BYTE PTR [RAX+RDI+00006498],05
		Write<uint32>((appBaseAddr + 0x218192 + 3), (enable) ? newOff : off); // dmc3.exe+218192 - 80 BC 18 98640000 06 - CMP BYTE PTR [RAX+RBX+00006498],06
		Write<uint32>((appBaseAddr + 0x218312 + 3), (enable) ? newOff : off); // dmc3.exe+218312 - 80 BC 18 98640000 06 - CMP BYTE PTR [RAX+RBX+00006498],06
		Write<uint32>((appBaseAddr + 0x2183E5 + 3), (enable) ? newOff : off); // dmc3.exe+2183E5 - 80 BC 18 98640000 06 - CMP BYTE PTR [RAX+RBX+00006498],06
		Write<uint32>((appBaseAddr + 0x218422 + 3), (enable) ? newOff : off); // dmc3.exe+218422 - 80 BC 18 98640000 06 - CMP BYTE PTR [RAX+RBX+00006498],06
		Write<uint32>((appBaseAddr + 0x218456 + 3), (enable) ? newOff : off); // dmc3.exe+218456 - 80 BC 18 98640000 06 - CMP BYTE PTR [RAX+RBX+00006498],06
		Write<uint32>((appBaseAddr + 0x2184B2 + 3), (enable) ? newOff : off); // dmc3.exe+2184B2 - 80 BC 18 98640000 06 - CMP BYTE PTR [RAX+RBX+00006498],06
		Write<uint32>((appBaseAddr + 0x2184F2 + 3), (enable) ? newOff : off); // dmc3.exe+2184F2 - 80 BC 18 98640000 06 - CMP BYTE PTR [RAX+RBX+00006498],06
		Write<uint32>((appBaseAddr + 0x218532 + 3), (enable) ? newOff : off); // dmc3.exe+218532 - 80 BC 18 98640000 06 - CMP BYTE PTR [RAX+RBX+00006498],06
		Write<uint32>((appBaseAddr + 0x21A462 + 3), (enable) ? newOff : off); // dmc3.exe+21A462 - 80 BC 18 98640000 0B - CMP BYTE PTR [RAX+RBX+00006498],0B
		Write<uint32>((appBaseAddr + 0x21A4B2 + 3), (enable) ? newOff : off); // dmc3.exe+21A4B2 - 80 BC 18 98640000 0B - CMP BYTE PTR [RAX+RBX+00006498],0B
		Write<uint32>((appBaseAddr + 0x21B7F4 + 3), (enable) ? newOff : off); // dmc3.exe+21B7F4 - 80 BC 18 98640000 0B - CMP BYTE PTR [RAX+RBX+00006498],0B
		Write<uint32>((appBaseAddr + 0x21B8C2 + 3), (enable) ? newOff : off); // dmc3.exe+21B8C2 - 80 BC 18 98640000 0B - CMP BYTE PTR [RAX+RBX+00006498],0B
		Write<uint32>((appBaseAddr + 0x21B8F2 + 3), (enable) ? newOff : off); // dmc3.exe+21B8F2 - 80 BC 18 98640000 0B - CMP BYTE PTR [RAX+RBX+00006498],0B
		Write<uint32>((appBaseAddr + 0x21BBB0 + 3), (enable) ? newOff : off); // dmc3.exe+21BBB0 - 80 BC 19 98640000 0B - CMP BYTE PTR [RCX+RBX+00006498],0B
		Write<uint32>((appBaseAddr + 0x21BBE0 + 3), (enable) ? newOff : off); // dmc3.exe+21BBE0 - 80 BC 19 98640000 0B - CMP BYTE PTR [RCX+RBX+00006498],0B
		Write<uint32>((appBaseAddr + 0x21C0A2 + 3), (enable) ? newOff : off); // dmc3.exe+21C0A2 - 80 BC 18 98640000 0B - CMP BYTE PTR [RAX+RBX+00006498],0B
		Write<uint32>((appBaseAddr + 0x21C3D2 + 3), (enable) ? newOff : off); // dmc3.exe+21C3D2 - 80 BC 18 98640000 0B - CMP BYTE PTR [RAX+RBX+00006498],0B
		Write<uint32>((appBaseAddr + 0x21C402 + 3), (enable) ? newOff : off); // dmc3.exe+21C402 - 80 BC 18 98640000 0B - CMP BYTE PTR [RAX+RBX+00006498],0B
		Write<uint32>((appBaseAddr + 0x21C6A3 + 3), (enable) ? newOff : off); // dmc3.exe+21C6A3 - 80 BC 18 98640000 0B - CMP BYTE PTR [RAX+RBX+00006498],0B
		Write<uint32>((appBaseAddr + 0x21C745 + 3), (enable) ? newOff : off); // dmc3.exe+21C745 - 80 BC 18 98640000 0B - CMP BYTE PTR [RAX+RBX+00006498],0B
		Write<uint32>((appBaseAddr + 0x21C842 + 3), (enable) ? newOff : off); // dmc3.exe+21C842 - 80 BC 18 98640000 0B - CMP BYTE PTR [RAX+RBX+00006498],0B
		Write<uint32>((appBaseAddr + 0x21D0D4 + 3), (enable) ? newOff : off); // dmc3.exe+21D0D4 - 80 BC 38 98640000 0B - CMP BYTE PTR [RAX+RDI+00006498],0B
		Write<uint32>((appBaseAddr + 0x21D102 + 3), (enable) ? newOff : off); // dmc3.exe+21D102 - 80 BC 38 98640000 0B - CMP BYTE PTR [RAX+RDI+00006498],0B
		Write<uint32>((appBaseAddr + 0x21E904 + 3), (enable) ? newOff : off); // dmc3.exe+21E904 - 80 BC 18 98640000 0B - CMP BYTE PTR [RAX+RBX+00006498],0B
		Write<uint32>((appBaseAddr + 0x21E932 + 3), (enable) ? newOff : off); // dmc3.exe+21E932 - 80 BC 18 98640000 0B - CMP BYTE PTR [RAX+RBX+00006498],0B
		Write<uint32>((appBaseAddr + 0x21F226 + 3), (enable) ? newOff : off); // dmc3.exe+21F226 - 80 BC 1F 98640000 0D - CMP BYTE PTR [RDI+RBX+00006498],0D
		Write<uint32>((appBaseAddr + 0x21F250 + 3), (enable) ? newOff : off); // dmc3.exe+21F250 - 80 BC 19 98640000 0D - CMP BYTE PTR [RCX+RBX+00006498],0D
		Write<uint32>((appBaseAddr + 0x2228F3 + 3), (enable) ? newOff : off); // dmc3.exe+2228F3 - 48 81 C1 98640000 - ADD RCX,00006498
		Write<uint32>((appBaseAddr + 0x2229A2 + 3), (enable) ? newOff : off); // dmc3.exe+2229A2 - 80 BC 38 98640000 0D - CMP BYTE PTR [RAX+RDI+00006498],0D
		Write<uint32>((appBaseAddr + 0x222B46 + 3), (enable) ? newOff : off); // dmc3.exe+222B46 - 80 BC 38 98640000 0B - CMP BYTE PTR [RAX+RDI+00006498],0B
		Write<uint32>((appBaseAddr + 0x222E92 + 3), (enable) ? newOff : off); // dmc3.exe+222E92 - 80 BC 38 98640000 0D - CMP BYTE PTR [RAX+RDI+00006498],0D
		Write<uint32>((appBaseAddr + 0x222F34 + 3), (enable) ? newOff : off); // dmc3.exe+222F34 - 80 BC 38 98640000 0D - CMP BYTE PTR [RAX+RDI+00006498],0D
		// Unknown
		// Write<uint32>((appBaseAddr + 0x1E2C33 + 4), (enable) ? newOff : off); // dmc3.exe+1E2C33 - 41 3A 84 18 98640000 - CMP AL,[R8+RBX+00006498]
		// Write<uint32>((appBaseAddr + 0x1E2CEA + 5), (enable) ? newOff : off); // dmc3.exe+1E2CEA - 41 0FB6 84 18 98640000 - MOVZX EAX,BYTE PTR [R8+RBX+00006498]
		// Write<uint32>((appBaseAddr + 0x1E3F9D + 4), (enable) ? newOff : off); // dmc3.exe+1E3F9D - 0FB6 8C 18 98640000 - MOVZX ECX,BYTE PTR [RAX+RBX+00006498]
		// Write<uint32>((appBaseAddr + 0x1FAB48 + 4), (enable) ? newOff : off); // dmc3.exe+1FAB48 - 0FB6 84 08 98640000 - MOVZX EAX,BYTE PTR [RAX+RCX+00006498]
		// Write<uint32>((appBaseAddr + 0x1FCFD4 + 2), (enable) ? newOff : off); // dmc3.exe+1FCFD4 - 80 B9 98640000 FF - CMP BYTE PTR [RCX+00006498],-01
		// Write<uint32>((appBaseAddr + 0x1FCFDD + 2), (enable) ? newOff : off); // dmc3.exe+1FCFDD - 88 91 98640000 - MOV [RCX+00006498],DL
		// Write<uint32>((appBaseAddr + 0x1FD4D9 + 3), (enable) ? newOff : off); // dmc3.exe+1FD4D9 - 38 94 08 98640000 - CMP [RAX+RCX+00006498],DL
		// Write<uint32>((appBaseAddr + 0x20EF5F + 3), (enable) ? newOff : off); // dmc3.exe+20EF5F - 80 BC 38 98640000 06 - CMP BYTE PTR [RAX+RDI+00006498],06
	}
	// 0x6499
	{
		constexpr auto off = offsetof(PlayerActorData, weapons[1]);
		constexpr auto newOff = offsetof(PlayerActorData, newWeapons[1]);
		static_assert(off == 0x6499);
		// Init Actor Dante
		Write<uint32>((appBaseAddr + 0x217C07 + 2), (enable) ? newOff : off); // dmc3.exe+217C07 - 88 81 99640000 - MOV [RCX+00006499],AL
		// Update Actor
		Write<uint32>((appBaseAddr + 0x1DF2E9 + 2), (enable) ? newOff : off); // dmc3.exe+1DF2E9 - C6 83 99640000 FF - MOV BYTE PTR [RBX+00006499],-01
		// func_2198D0
		Write<uint32>((appBaseAddr + 0x2198E5 + 3), (enable) ? newOff : off); // dmc3.exe+2198E5 - 0FB6 81 99640000 - MOVZX EAX,BYTE PTR [RCX+00006499]
		// func_2241F0
		Write<uint32>((appBaseAddr + 0x224205 + 3), (enable) ? newOff : off); // dmc3.exe+224205 - 0FB6 81 99640000 - MOVZX EAX,BYTE PTR [RCX+00006499]
		// Unknown
		// Write<uint32>((appBaseAddr + 0x1FCFE6 + 2), (enable) ? newOff : off); // dmc3.exe+1FCFE6 - 80 B9 99640000 FF - CMP BYTE PTR [RCX+00006499],-01
		// Write<uint32>((appBaseAddr + 0x1FCFEF + 2), (enable) ? newOff : off); // dmc3.exe+1FCFEF - 88 91 99640000 - MOV [RCX+00006499],DL
	}
	// 0x649A
	{
		constexpr auto off = offsetof(PlayerActorData, weapons[2]);
		constexpr auto newOff = offsetof(PlayerActorData, newWeapons[2]);
		static_assert(off == 0x649A);
		// Init Actor Dante
		Write<uint32>((appBaseAddr + 0x217C1A + 2), (enable) ? newOff : off); // dmc3.exe+217C1A - 88 81 9A640000 - MOV [RCX+0000649A],AL
		// Update Actor Dante
		Write<uint32>((appBaseAddr + 0x212F12 + 3), (enable) ? newOff : off); // dmc3.exe+212F12 - 48 8D 9E 9A640000 - LEA RBX,[RSI+0000649A]
		// Register Weapons
		Write<uint32>((appBaseAddr + 0x1DEE2A + 3), (enable) ? newOff : off); // dmc3.exe+1DEE2A - 48 8D AB 9A640000 - LEA RBP,[RBX+0000649A]
		// func_2198D0
		Write<uint32>((appBaseAddr + 0x2198F8 + 3), (enable) ? newOff : off); // dmc3.exe+2198F8 - 0FB6 81 9A640000 - MOVZX EAX,BYTE PTR [RCX+0000649A]
		// func_2241F0
		Write<uint32>((appBaseAddr + 0x224218 + 3), (enable) ? newOff : off); // dmc3.exe+224218 - 0FB6 81 9A640000 - MOVZX EAX,BYTE PTR [RCX+0000649A]
		// Unknown
		// Write<uint32>((appBaseAddr + 0x1FCFB0 + 2), (enable) ? newOff : off); // dmc3.exe+1FCFB0 - 80 B9 9A640000 FF - CMP BYTE PTR [RCX+0000649A],-01
		// Write<uint32>((appBaseAddr + 0x1FCFB9 + 2), (enable) ? newOff : off); // dmc3.exe+1FCFB9 - 88 91 9A640000 - MOV [RCX+0000649A],DL
	}
	// 0x649B
	{
		constexpr auto off = offsetof(PlayerActorData, weapons[3]);
		constexpr auto newOff = offsetof(PlayerActorData, newWeapons[3]);
		static_assert(off == 0x649B);
		// Init Actor Dante
		Write<uint32>((appBaseAddr + 0x217C2D + 2), (enable) ? newOff : off); // dmc3.exe+217C2D - 88 81 9B640000 - MOV [RCX+0000649B],AL
		// Update Actor
		Write<uint32>((appBaseAddr + 0x1DF2F9 + 2), (enable) ? newOff : off); // dmc3.exe+1DF2F9 - C6 83 9B640000 FF - MOV BYTE PTR [RBX+0000649B],-01
		// func_2198D0
		Write<uint32>((appBaseAddr + 0x21990B + 3), (enable) ? newOff : off); // dmc3.exe+21990B - 0FB6 81 9B640000 - MOVZX EAX,BYTE PTR [RCX+0000649B]
		// func_2241F0
		Write<uint32>((appBaseAddr + 0x22422B + 3), (enable) ? newOff : off); // dmc3.exe+22422B - 0FB6 81 9B640000 - MOVZX EAX,BYTE PTR [RCX+0000649B]
		// Unknown
		// Write<uint32>((appBaseAddr + 0x1FCFC2 + 2), (enable) ? newOff : off); // dmc3.exe+1FCFC2 - 80 B9 9B640000 FF - CMP BYTE PTR [RCX+0000649B],-01
		// Write<uint32>((appBaseAddr + 0x1FCFCB + 2), (enable) ? newOff : off); // dmc3.exe+1FCFCB - 88 91 9B640000 - MOV [RCX+0000649B],DL
	}
	// 0x649C
	{
		constexpr auto off = offsetof(PlayerActorData, weapons[4]);
		constexpr auto newOff = offsetof(PlayerActorData, newWeapons[4]);
		static_assert(off == 0x649C);
		// Init Actor Dante
		Write<uint32>((appBaseAddr + 0x217C40 + 2), (enable) ? newOff : off); // dmc3.exe+217C40 - 88 81 9C640000 - MOV [RCX+0000649C],AL
		// Init Actor Bob
		Write<uint32>((appBaseAddr + 0x226F5D + 2), (enable) ? newOff : off); // dmc3.exe+226F5D - C6 81 9C640000 FF - MOV BYTE PTR [RCX+0000649C],-01
		// Init Actor Lady
		Write<uint32>((appBaseAddr + 0x2196B4 + 2), (enable) ? newOff : off); // dmc3.exe+2196B4 - C6 81 9C640000 0B - MOV BYTE PTR [RCX+0000649C],0B
		// Init Actor Vergil
		Write<uint32>((appBaseAddr + 0x223D1B + 2), (enable) ? newOff : off); // dmc3.exe+223D1B - C6 81 9C640000 FF - MOV BYTE PTR [RCX+0000649C],-01
		// func_2198D0
		Write<uint32>((appBaseAddr + 0x21991E + 3), (enable) ? newOff : off); // dmc3.exe+21991E - 0FB6 81 9C640000 - MOVZX EAX,BYTE PTR [RCX+0000649C]
		// func_2241F0
		Write<uint32>((appBaseAddr + 0x22423E + 3), (enable) ? newOff : off); // dmc3.exe+22423E - 0FB6 81 9C640000 - MOVZX EAX,BYTE PTR [RCX+0000649C]
	}
	// 0x64A0
	{
		constexpr auto off = offsetof(PlayerActorData, weaponDataAddr[0]);
		constexpr auto newOff = offsetof(PlayerActorData, newWeaponDataAddr[0]);
		static_assert(off == 0x64A0);
		// Register Weapons
		Write<uint32>((appBaseAddr + 0x1DED55 + 3), (enable) ? newOff : off); // dmc3.exe+1DED55 - 48 8D B1 A0640000 - LEA RSI,[RCX+000064A0]
		// Other
		Write<uint32>((appBaseAddr + 0x1DFB82 + 3), (enable) ? newOff : off); // dmc3.exe+1DFB82 - 48 8D 99 A0640000 - LEA RBX,[RCX+000064A0]
		Write<uint32>((appBaseAddr + 0x1FACBB + 4), (enable) ? newOff : off); // dmc3.exe+1FACBB - 49 8B 8C CA A0640000 - MOV RCX,[R10+RCX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x1FAD5B + 4), (enable) ? newOff : off); // dmc3.exe+1FAD5B - 49 8B 8C C9 A0640000 - MOV RCX,[R9+RCX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x1FB777 + 3), (enable) ? newOff : off); // dmc3.exe+1FB777 - 48 8D B3 A0640000 - LEA RSI,[RBX+000064A0]
		Write<uint32>((appBaseAddr + 0x1FB84C + 3), (enable) ? newOff : off); // dmc3.exe+1FB84C - 48 8D B3 A0640000 - LEA RSI,[RBX+000064A0]
		Write<uint32>((appBaseAddr + 0x1FB8F8 + 3), (enable) ? newOff : off); // dmc3.exe+1FB8F8 - 48 8D B3 A0640000 - LEA RSI,[RBX+000064A0]
		Write<uint32>((appBaseAddr + 0x1FB9A7 + 3), (enable) ? newOff : off); // dmc3.exe+1FB9A7 - 48 8D B3 A0640000 - LEA RSI,[RBX+000064A0]
		Write<uint32>((appBaseAddr + 0x1FCAD4 + 3), (enable) ? newOff : off); // dmc3.exe+1FCAD4 - 49 8D 9E A0640000 - LEA RBX,[R14+000064A0]
		Write<uint32>((appBaseAddr + 0x1FCEC8 + 3), (enable) ? newOff : off); // dmc3.exe+1FCEC8 - 48 81 C7 A0640000 - ADD RDI,000064A0
		Write<uint32>((appBaseAddr + 0x2061AE + 4), (enable) ? newOff : off); // dmc3.exe+2061AE - 4C 8B 94 C3 A0640000 - MOV R10,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x210A48 + 4), (enable) ? newOff : off); // dmc3.exe+210A48 - 48 8B 8C C3 A0640000 - MOV RCX,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x210D2B + 4), (enable) ? newOff : off); // dmc3.exe+210D2B - 48 8B 8C C3 A0640000 - MOV RCX,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x2113FC + 4), (enable) ? newOff : off); // dmc3.exe+2113FC - 48 8B 8C C6 A0640000 - MOV RCX,[RSI+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x2114DD + 4), (enable) ? newOff : off); // dmc3.exe+2114DD - 48 8B 8C C6 A0640000 - MOV RCX,[RSI+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x21160F + 4), (enable) ? newOff : off); // dmc3.exe+21160F - 48 8B 8C C6 A0640000 - MOV RCX,[RSI+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x21169E + 4), (enable) ? newOff : off); // dmc3.exe+21169E - 48 8B 8C C6 A0640000 - MOV RCX,[RSI+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x21174E + 4), (enable) ? newOff : off); // dmc3.exe+21174E - 48 8B 8C C6 A0640000 - MOV RCX,[RSI+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x2117B5 + 4), (enable) ? newOff : off); // dmc3.exe+2117B5 - 48 8B 8C C6 A0640000 - MOV RCX,[RSI+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x2158CE + 4), (enable) ? newOff : off); // dmc3.exe+2158CE - 48 8B 8C C7 A0640000 - MOV RCX,[RDI+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x2159FE + 4), (enable) ? newOff : off); // dmc3.exe+2159FE - 48 8B 8C C7 A0640000 - MOV RCX,[RDI+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x216EA9 + 4), (enable) ? newOff : off); // dmc3.exe+216EA9 - 48 8B 8C C7 A0640000 - MOV RCX,[RDI+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x218443 + 4), (enable) ? newOff : off); // dmc3.exe+218443 - 48 8B BC C3 A0640000 - MOV RDI,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x218472 + 4), (enable) ? newOff : off); // dmc3.exe+218472 - 48 8B BC C3 A0640000 - MOV RDI,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x2184D6 + 4), (enable) ? newOff : off); // dmc3.exe+2184D6 - 48 8B BC C3 A0640000 - MOV RDI,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x218516 + 4), (enable) ? newOff : off); // dmc3.exe+218516 - 48 8B BC C3 A0640000 - MOV RDI,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x21854E + 4), (enable) ? newOff : off); // dmc3.exe+21854E - 48 8B BC C3 A0640000 - MOV RDI,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x21A48F + 4), (enable) ? newOff : off); // dmc3.exe+21A48F - 4C 8B 8C C3 A0640000 - MOV R9,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x21A4DF + 4), (enable) ? newOff : off); // dmc3.exe+21A4DF - 4C 8B 8C C3 A0640000 - MOV R9,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x21B810 + 4), (enable) ? newOff : off); // dmc3.exe+21B810 - 4C 8B 8C C3 A0640000 - MOV R9,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x21B8E1 + 4), (enable) ? newOff : off); // dmc3.exe+21B8E1 - 4C 8B 8C C3 A0640000 - MOV R9,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x21B90E + 4), (enable) ? newOff : off); // dmc3.exe+21B90E - 4C 8B 8C C3 A0640000 - MOV R9,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x21BBD4 + 4), (enable) ? newOff : off); // dmc3.exe+21BBD4 - 48 8B 8C C3 A0640000 - MOV RCX,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x21BC78 + 4), (enable) ? newOff : off); // dmc3.exe+21BC78 - 48 8B 8C C3 A0640000 - MOV RCX,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x21C0BE + 4), (enable) ? newOff : off); // dmc3.exe+21C0BE - 48 8B BC C3 A0640000 - MOV RDI,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x21C3F1 + 4), (enable) ? newOff : off); // dmc3.exe+21C3F1 - 4C 8B 8C C3 A0640000 - MOV R9,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x21C41E + 4), (enable) ? newOff : off); // dmc3.exe+21C41E - 4C 8B 8C C3 A0640000 - MOV R9,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x21C6BF + 4), (enable) ? newOff : off); // dmc3.exe+21C6BF - 48 8B BC C3 A0640000 - MOV RDI,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x21C761 + 4), (enable) ? newOff : off); // dmc3.exe+21C761 - 48 8B BC C3 A0640000 - MOV RDI,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x21C85E + 4), (enable) ? newOff : off); // dmc3.exe+21C85E - 48 8B BC C3 A0640000 - MOV RDI,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x21D0F3 + 4), (enable) ? newOff : off); // dmc3.exe+21D0F3 - 4C 8B 8C C7 A0640000 - MOV R9,[RDI+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x21D11E + 4), (enable) ? newOff : off); // dmc3.exe+21D11E - 4C 8B 8C C7 A0640000 - MOV R9,[RDI+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x21E923 + 4), (enable) ? newOff : off); // dmc3.exe+21E923 - 4C 8B 8C C3 A0640000 - MOV R9,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x21E94E + 4), (enable) ? newOff : off); // dmc3.exe+21E94E - 4C 8B 8C C3 A0640000 - MOV R9,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x21F2F7 + 4), (enable) ? newOff : off); // dmc3.exe+21F2F7 - 48 8B 8C C3 A0640000 - MOV RCX,[RBX+RAX*8+000064A0]
		Write<uint32>((appBaseAddr + 0x222B62 + 4), (enable) ? newOff : off); // dmc3.exe+222B62 - 48 8B 8C C7 A0640000 - MOV RCX,[RDI+RAX*8+000064A0]
	}
	// 0x64B0
	{
		constexpr auto off = offsetof(PlayerActorData, weaponDataAddr[2]);
		constexpr auto newOff = offsetof(PlayerActorData, newWeaponDataAddr[2]);
		static_assert(off == 0x64B0);
		// Register Weapons
		Write<uint32>((appBaseAddr + 0x1DEE3E + 3), (enable) ? newOff : off); // dmc3.exe+1DEE3E - 48 8D B3 B0640000 - LEA RSI,[RBX+000064B0]
	}
	// 0x64B8
	{
		constexpr auto off = offsetof(PlayerActorData, weaponDataAddr[3]);
		constexpr auto newOff = offsetof(PlayerActorData, newWeaponDataAddr[3]);
		static_assert(off == 0x64B8);
		// Register Weapons
		Write<uint32>((appBaseAddr + 0x1DEF27 + 3), (enable) ? newOff : off); // dmc3.exe+1DEF27 - 48 89 83 B8640000 - MOV [RBX+000064B8],RAX
		// Other
		Write<uint32>((appBaseAddr + 0x21AF95 + 3), (enable) ? newOff : off); // dmc3.exe+21AF95 - 48 8B 8F B8640000 - MOV RCX,[RDI+000064B8]
	}
	// 0x64C8
	{
		constexpr auto off = offsetof(PlayerActorData, weaponStatus[0]);
		constexpr auto newOff = offsetof(PlayerActorData, newWeaponStatus[0]);
		static_assert(off == 0x64C8);
		// Register Weapons
		Write<uint32>((appBaseAddr + 0x1DED48 + 3), (enable) ? newOff : off); // dmc3.exe+1DED48 - 48 8D B9 C8640000 - LEA RDI,[RCX+000064C8]
		// Other
		Write<uint32>((appBaseAddr + 0x1D9203 + 3), (enable) ? newOff : off); // dmc3.exe+1D9203 - C7 84 82 C8640000 00000000 - MOV [RDX+RAX*4+000064C8],00000000
		Write<uint32>((appBaseAddr + 0x1FAD1E + 4), (enable) ? newOff : off); // dmc3.exe+1FAD1E - 41 8B 84 89 C8640000 - MOV EAX,[R9+RCX*4+000064C8]
		Write<uint32>((appBaseAddr + 0x1FD162 + 4), (enable) ? newOff : off); // dmc3.exe+1FD162 - 44 39 8C 81 C8640000 - CMP [RCX+RAX*4+000064C8],R9D
		Write<uint32>((appBaseAddr + 0x1FD1E9 + 4), (enable) ? newOff : off); // dmc3.exe+1FD1E9 - 41 83 BC 8A C8640000 04 - CMP DWORD PTR [R10+RCX*4+000064C8],04
		Write<uint32>((appBaseAddr + 0x1FD1F4 + 4), (enable) ? newOff : off); // dmc3.exe+1FD1F4 - 45 89 84 8A C8640000 - MOV [R10+RCX*4+000064C8],R8D
		Write<uint32>((appBaseAddr + 0x2063BA + 3), (enable) ? newOff : off); // dmc3.exe+2063BA - 83 BC BB C8640000 01 - CMP DWORD PTR [RBX+RDI*4+000064C8],01
		Write<uint32>((appBaseAddr + 0x206418 + 3), (enable) ? newOff : off); // dmc3.exe+206418 - C7 84 BB C8640000 02000000 - MOV [RBX+RDI*4+000064C8],00000002
		Write<uint32>((appBaseAddr + 0x20644C + 3), (enable) ? newOff : off); // dmc3.exe+20644C - 83 BC BB C8640000 03 - CMP DWORD PTR [RBX+RDI*4+000064C8],03
		Write<uint32>((appBaseAddr + 0x206532 + 3), (enable) ? newOff : off); // dmc3.exe+206532 - C7 84 83 C8640000 01000000 - MOV [RBX+RAX*4+000064C8],00000001
		Write<uint32>((appBaseAddr + 0x210CDF + 3), (enable) ? newOff : off); // dmc3.exe+210CDF - C7 84 93 C8640000 01000000 - MOV [RBX+RDX*4+000064C8],00000001
		Write<uint32>((appBaseAddr + 0x215650 + 3), (enable) ? newOff : off); // dmc3.exe+215650 - 48 8D 87 C8640000 - LEA RAX,[RDI+000064C8]
		Write<uint32>((appBaseAddr + 0x215725 + 3), (enable) ? newOff : off); // dmc3.exe+215725 - 83 BC 9F C8640000 01 - CMP DWORD PTR [RDI+RBX*4+000064C8],01
		Write<uint32>((appBaseAddr + 0x215770 + 3), (enable) ? newOff : off); // dmc3.exe+215770 - C7 84 9F C8640000 02000000 - MOV [RDI+RBX*4+000064C8],00000002
		Write<uint32>((appBaseAddr + 0x215995 + 4), (enable) ? newOff : off); // dmc3.exe+215995 - 44 39 B4 87 C8640000 - CMP [RDI+RAX*4+000064C8],R14D
		Write<uint32>((appBaseAddr + 0x21F29E + 3), (enable) ? newOff : off); // dmc3.exe+21F29E - C7 84 93 C8640000 01000000 - MOV [RBX+RDX*4+000064C8],00000001
		Write<uint32>((appBaseAddr + 0x222941 + 3), (enable) ? newOff : off); // dmc3.exe+222941 - 48 8D 87 C8640000 - LEA RAX,[RDI+000064C8]
		Write<uint32>((appBaseAddr + 0x2229BE + 3), (enable) ? newOff : off); // dmc3.exe+2229BE - 39 B4 87 C8640000 - CMP [RDI+RAX*4+000064C8],ESI
		Write<uint32>((appBaseAddr + 0x222EAF + 3), (enable) ? newOff : off); // dmc3.exe+222EAF - 83 BC 87 C8640000 00 - CMP DWORD PTR [RDI+RAX*4+000064C8],00
		Write<uint32>((appBaseAddr + 0x222F57 + 3), (enable) ? newOff : off); // dmc3.exe+222F57 - 39 B4 87 C8640000 - CMP [RDI+RAX*4+000064C8],ESI
	}
	// 0x64D0
	{
		constexpr auto off = offsetof(PlayerActorData, weaponStatus[2]);
		constexpr auto newOff = offsetof(PlayerActorData, newWeaponStatus[2]);
		static_assert(off == 0x64D0);
		// Register Weapons
		Write<uint32>((appBaseAddr + 0x1DEE37 + 3), (enable) ? newOff : off); // dmc3.exe+1DEE37 - 48 8D BB D0640000 - LEA RDI,[RBX+000064D0]
	}
	// 0x64DC
	{
		constexpr auto off = offsetof(PlayerActorData, weaponLevels[0]);
		constexpr auto newOff = offsetof(PlayerActorData, newWeaponLevels[0]);
		static_assert(off == 0x64DC);
		// Init Actor Dante
		Write<uint32>((appBaseAddr + 0x217BFD + 2), (enable) ? newOff : off); // dmc3.exe+217BFD - 89 81 DC640000 - MOV [RCX+000064DC],EAX
		// Init Actor Bob
		Write<uint32>((appBaseAddr + 0x226F64 + 3), (enable) ? newOff : off); // dmc3.exe+226F64 - 4C 89 A1 DC640000 - MOV [RCX+000064DC],R12
		// Init Actor Lady
		Write<uint32>((appBaseAddr + 0x2196BB + 3), (enable) ? newOff : off); // dmc3.exe+2196BB - 4C 89 A1 DC640000 - MOV [RCX+000064DC],R12
		// Init Actor Vergil
		Write<uint32>((appBaseAddr + 0x223D25 + 2), (enable) ? newOff : off); // dmc3.exe+223D25 - 89 81 DC640000 - MOV [RCX+000064DC],EAX
		// func_2198D0
		Write<uint32>((appBaseAddr + 0x2198DC + 2), (enable) ? newOff : off); // dmc3.exe+2198DC - 8B 81 DC640000 - MOV EAX,[RCX+000064DC]
		// func_2241F0
		Write<uint32>((appBaseAddr + 0x2241FC + 2), (enable) ? newOff : off); // dmc3.exe+2241FC - 8B 81 DC640000 - MOV EAX,[RCX+000064DC]
		// Other
		Write<uint32>((appBaseAddr + 0x2061C1 + 4), (enable) ? newOff : off); // dmc3.exe+2061C1 - 44 8B 84 83 DC640000 - MOV R8D,[RBX+RAX*4+000064DC]
		Write<uint32>((appBaseAddr + 0x208704 + 4), (enable) ? newOff : off); // dmc3.exe+208704 - 44 8B 84 83 DC640000 - MOV R8D,[RBX+RAX*4+000064DC]
		Write<uint32>((appBaseAddr + 0x20872F + 4), (enable) ? newOff : off); // dmc3.exe+20872F - 44 8B 84 83 DC640000 - MOV R8D,[RBX+RAX*4+000064DC]
		Write<uint32>((appBaseAddr + 0x20E321 + 4), (enable) ? newOff : off); // dmc3.exe+20E321 - 44 8B 84 83 DC640000 - MOV R8D,[RBX+RAX*4+000064DC]
		Write<uint32>((appBaseAddr + 0x20E351 + 4), (enable) ? newOff : off); // dmc3.exe+20E351 - 44 8B 84 83 DC640000 - MOV R8D,[RBX+RAX*4+000064DC]
		Write<uint32>((appBaseAddr + 0x20E37F + 4), (enable) ? newOff : off); // dmc3.exe+20E37F - 44 8B 84 83 DC640000 - MOV R8D,[RBX+RAX*4+000064DC]
		Write<uint32>((appBaseAddr + 0x20E684 + 3), (enable) ? newOff : off); // dmc3.exe+20E684 - 8B BC 83 DC640000 - MOV EDI,[RBX+RAX*4+000064DC]
		Write<uint32>((appBaseAddr + 0x20E72F + 3), (enable) ? newOff : off); // dmc3.exe+20E72F - 8B BC 83 DC640000 - MOV EDI,[RBX+RAX*4+000064DC]
		Write<uint32>((appBaseAddr + 0x215EBE + 3), (enable) ? newOff : off); // dmc3.exe+215EBE - 83 BC 87 DC640000 01 - CMP DWORD PTR [RDI+RAX*4+000064DC],01
		Write<uint32>((appBaseAddr + 0x215ED5 + 3), (enable) ? newOff : off); // dmc3.exe+215ED5 - 83 BC 87 DC640000 02 - CMP DWORD PTR [RDI+RAX*4+000064DC],02
		Write<uint32>((appBaseAddr + 0x217496 + 3), (enable) ? newOff : off); // dmc3.exe+217496 - 8B 8C 87 DC640000 - MOV ECX,[RDI+RAX*4+000064DC]
		Write<uint32>((appBaseAddr + 0x218408 + 3), (enable) ? newOff : off); // dmc3.exe+218408 - 8B 8C 83 DC640000 - MOV ECX,[RBX+RAX*4+000064DC]
	}
	// 0x64E0
	{
		constexpr auto off = offsetof(PlayerActorData, weaponLevels[1]);
		constexpr auto newOff = offsetof(PlayerActorData, newWeaponLevels[1]);
		static_assert(off == 0x64E0);
		// Init Actor Dante
		Write<uint32>((appBaseAddr + 0x217C10 + 2), (enable) ? newOff : off); // dmc3.exe+217C10 - 89 81 E0640000 - MOV [RCX+000064E0],EAX
		// Init Actor Vergil
		Write<uint32>((appBaseAddr + 0x223D2E + 2), (enable) ? newOff : off); // dmc3.exe+223D2E - 89 81 E0640000 - MOV [RCX+000064E0],EAX
		// func_2198D0
		Write<uint32>((appBaseAddr + 0x2198EF + 2), (enable) ? newOff : off); // dmc3.exe+2198EF - 8B 81 E0640000 - MOV EAX,[RCX+000064E0]
		// func_2241F0
		Write<uint32>((appBaseAddr + 0x22420F + 2), (enable) ? newOff : off); // dmc3.exe+22420F - 8B 81 E0640000 - MOV EAX,[RCX+000064E0]
	}
	// 0x64E4
	{
		constexpr auto off = offsetof(PlayerActorData, weaponLevels[2]);
		constexpr auto newOff = offsetof(PlayerActorData, newWeaponLevels[2]);
		static_assert(off == 0x64E4);
		// Init Actor Dante
		Write<uint32>((appBaseAddr + 0x217C23 + 2), (enable) ? newOff : off); // dmc3.exe+217C23 - 89 81 E4640000 - MOV [RCX+000064E4],EAX
		// Init Actor Bob
		Write<uint32>((appBaseAddr + 0x226F6B + 3), (enable) ? newOff : off); // dmc3.exe+226F6B - 4C 89 A1 E4640000 - MOV [RCX+000064E4],R12
		// Init Actor Lady
		Write<uint32>((appBaseAddr + 0x2196C2 + 3), (enable) ? newOff : off); // dmc3.exe+2196C2 - 4C 89 A1 E4640000 - MOV [RCX+000064E4],R12
		// Init Actor Vergil
		Write<uint32>((appBaseAddr + 0x223D37 + 2), (enable) ? newOff : off); // dmc3.exe+223D37 - 89 81 E4640000 - MOV [RCX+000064E4],EAX
		// func_2198D0
		Write<uint32>((appBaseAddr + 0x219902 + 2), (enable) ? newOff : off); // dmc3.exe+219902 - 8B 81 E4640000 - MOV EAX,[RCX+000064E4]
		// func_2241F0
		Write<uint32>((appBaseAddr + 0x224222 + 2), (enable) ? newOff : off); // dmc3.exe+224222 - 8B 81 E4640000 - MOV EAX,[RCX+000064E4]
	}
	// 0x64E8
	{
		constexpr auto off = offsetof(PlayerActorData, weaponLevels[3]);
		constexpr auto newOff = offsetof(PlayerActorData, newWeaponLevels[3]);
		static_assert(off == 0x64E8);
		// Init Actor Dante
		Write<uint32>((appBaseAddr + 0x217C36 + 2), (enable) ? newOff : off); // dmc3.exe+217C36 - 89 81 E8640000 - MOV [RCX+000064E8],EAX
		// Init Actor Vergil
		Write<uint32>((appBaseAddr + 0x223D40 + 2), (enable) ? newOff : off); // dmc3.exe+223D40 - 89 81 E8640000 - MOV [RCX+000064E8],EAX
		// func_2198D0
		Write<uint32>((appBaseAddr + 0x219915 + 2), (enable) ? newOff : off); // dmc3.exe+219915 - 8B 81 E8640000 - MOV EAX,[RCX+000064E8]
		// func_2241F0
		Write<uint32>((appBaseAddr + 0x224235 + 2), (enable) ? newOff : off); // dmc3.exe+224235 - 8B 81 E8640000 - MOV EAX,[RCX+000064E8]
	}
	// 0x64EC
	{
		constexpr auto off = offsetof(PlayerActorData, weaponLevels[4]);
		constexpr auto newOff = offsetof(PlayerActorData, newWeaponLevels[4]);
		static_assert(off == 0x64EC);
		// Init Actor Dante
		Write<uint32>((appBaseAddr + 0x217C49 + 2), (enable) ? newOff : off); // dmc3.exe+217C49 - 89 81 EC640000 - MOV [RCX+000064EC],EAX
		// Init Actor Bob
		Write<uint32>((appBaseAddr + 0x226F72 + 3), (enable) ? newOff : off); // dmc3.exe+226F72 - 44 89 A1 EC640000 - MOV [RCX+000064EC],R12D
		// Init Actor Lady
		Write<uint32>((appBaseAddr + 0x2196C9 + 3), (enable) ? newOff : off); // dmc3.exe+2196C9 - 44 89 A1 EC640000 - MOV [RCX+000064EC],R12D
		// Init Actor Vergil
		Write<uint32>((appBaseAddr + 0x223D49 + 2), (enable) ? newOff : off); // dmc3.exe+223D49 - 89 81 EC640000 - MOV [RCX+000064EC],EAX
		// func_2198D0
		Write<uint32>((appBaseAddr + 0x219928 + 2), (enable) ? newOff : off); // dmc3.exe+219928 - 8B 81 EC640000 - MOV EAX,[RCX+000064EC]
		// func_2241F0
		Write<uint32>((appBaseAddr + 0x224248 + 2), (enable) ? newOff : off); // dmc3.exe+224248 - 8B 81 EC640000 - MOV EAX,[RCX+000064EC]
	}
	// 0x64F4
	{
		constexpr auto off = offsetof(PlayerActorData, weaponTimers[0]);
		constexpr auto newOff = offsetof(PlayerActorData, newWeaponTimers[0]);
		static_assert(off == 0x64F4);
		// Register Weapons
		Write<uint32>((appBaseAddr + 0x1DEF3D + 3), (enable) ? newOff : off); // dmc3.exe+1DEF3D - 4C 89 BB F4640000 - MOV [RBX+000064F4],R15
		// Other
		Write<uint32>((appBaseAddr + 0x2063C2 + 3), (enable) ? newOff : off); // dmc3.exe+2063C2 - C7 84 BB F4640000 00002041 - MOV [RBX+RDI*4+000064F4],41200000
		Write<uint32>((appBaseAddr + 0x206527 + 3), (enable) ? newOff : off); // dmc3.exe+206527 - C7 84 83 F4640000 00002042 - MOV [RBX+RAX*4+000064F4],42200000
		Write<uint32>((appBaseAddr + 0x210CD8 + 3), (enable) ? newOff : off); // dmc3.exe+210CD8 - 89 8C 93 F4640000 - MOV [RBX+RDX*4+000064F4],ECX
		Write<uint32>((appBaseAddr + 0x21560F + 3), (enable) ? newOff : off); // dmc3.exe+21560F - 48 8D 87 F4640000 - LEA RAX,[RDI+000064F4]
		Write<uint32>((appBaseAddr + 0x21577B + 3), (enable) ? newOff : off); // dmc3.exe+21577B - C7 84 9F F4640000 00009644 - MOV [RDI+RBX*4+000064F4],44960000
		Write<uint32>((appBaseAddr + 0x21F297 + 3), (enable) ? newOff : off); // dmc3.exe+21F297 - 89 8C 93 F4640000 - MOV [RBX+RDX*4+000064F4],ECX
		Write<uint32>((appBaseAddr + 0x22290C + 3), (enable) ? newOff : off); // dmc3.exe+22290C - 48 8D 87 F4640000 - LEA RAX,[RDI+000064F4]
	}
	// 0x64FC
	{
		constexpr auto off = offsetof(PlayerActorData, weaponTimers[2]);
		constexpr auto newOff = offsetof(PlayerActorData, newWeaponTimers[2]);
		static_assert(off == 0x64FC);
		// Register Weapons
		Write<uint32>((appBaseAddr + 0x1DEF44 + 3), (enable) ? newOff : off); // dmc3.exe+1DEF44 - 4C 89 BB FC640000 - MOV [RBX+000064FC],R15
	}
	// 0x6504
	{
		constexpr auto off = offsetof(PlayerActorData, weaponTimers[4]);
		constexpr auto newOff = offsetof(PlayerActorData, newWeaponTimers[4]);
		static_assert(off == 0x6504);
		// Register Weapons
		Write<uint32>((appBaseAddr + 0x1DEF4B + 3), (enable) ? newOff : off); // dmc3.exe+1DEF4B - 44 89 BB 04650000 - MOV [RBX+00006504],R15D
	}
	// 0x6950
	{
		constexpr auto off = offsetof(PlayerActorData, bodyPartData[0][0]);
		constexpr auto newOff = offsetof(PlayerActorData, newBodyPartData[0][0]);
		static_assert(off == 0x6950);
		// func_1DDAF0
		Write<uint32>((appBaseAddr + 0x1DDD63 + 3), (enable) ? newOff : off); // dmc3.exe+1DDD63 - 48 8D 8E 50690000 - LEA RCX,[RSI+00006950]
		// func_1DE280
		Write<uint32>((appBaseAddr + 0x1DE2F4 + 3), (enable) ? newOff : off); // dmc3.exe+1DE2F4 - 48 8D 8F 50690000 - LEA RCX,[RDI+00006950]
		// func_1EF040
		Write<uint32>((appBaseAddr + 0x1EF4CE + 3), (enable) ? newOff : off); // dmc3.exe+1EF4CE - 49 8D 8D 50690000 - LEA RCX,[R13+00006950]
		// Other
		Write<uint32>((appBaseAddr + 0x1EF90E + 3), (enable) ? newOff : off); // dmc3.exe+1EF90E - 48 8D 8B 50690000 - LEA RCX,[RBX+00006950]
		Write<uint32>((appBaseAddr + 0x1EF947 + 3), (enable) ? newOff : off); // dmc3.exe+1EF947 - 48 81 C1 50690000 - ADD RCX,00006950
		Write<uint32>((appBaseAddr + 0x1EFAC0 + 3), (enable) ? newOff : off); // dmc3.exe+1EFAC0 - 48 81 C1 50690000 - ADD RCX,00006950
		Write<uint32>((appBaseAddr + 0x1EFADE + 3), (enable) ? newOff : off); // dmc3.exe+1EFADE - 48 8D 8B 50690000 - LEA RCX,[RBX+00006950]
		Write<uint32>((appBaseAddr + 0x1EFB0E + 3), (enable) ? newOff : off); // dmc3.exe+1EFB0E - 48 81 C3 50690000 - ADD RBX,00006950
		Write<uint32>((appBaseAddr + 0x1EFC62 + 3), (enable) ? newOff : off); // dmc3.exe+1EFC62 - 48 81 C1 50690000 - ADD RCX,00006950
		Write<uint32>((appBaseAddr + 0x1EFD36 + 3), (enable) ? newOff : off); // dmc3.exe+1EFD36 - 48 81 C1 50690000 - ADD RCX,00006950
		Write<uint32>((appBaseAddr + 0x1EFFFE + 3), (enable) ? newOff : off); // dmc3.exe+1EFFFE - 48 81 C1 50690000 - ADD RCX,00006950
		Write<uint32>((appBaseAddr + 0x1F0052 + 3), (enable) ? newOff : off); // dmc3.exe+1F0052 - 48 81 C1 50690000 - ADD RCX,00006950
		Write<uint32>((appBaseAddr + 0x1F906A + 3), (enable) ? newOff : off); // dmc3.exe+1F906A - 48 81 C1 50690000 - ADD RCX,00006950
		Write<uint32>((appBaseAddr + 0x1F9080 + 3), (enable) ? newOff : off); // dmc3.exe+1F9080 - 48 8D 97 50690000 - LEA RDX,[RDI+00006950]
		// Unknown
		// Write<uint32>((appBaseAddr + 0x1F0446 + 3), (enable) ? newOff : off); // dmc3.exe+1F0446 - 48 81 C1 50690000 - ADD RCX,00006950
	}
	// 0x6A70
	{
		constexpr auto off = offsetof(PlayerActorData, bodyPartData[0][1]);
		constexpr auto newOff = offsetof(PlayerActorData, newBodyPartData[0][1]);
		static_assert(off == 0x6A70);
		// func_1EF040
		Write<uint32>((appBaseAddr + 0x1EF477 + 3), (enable) ? newOff : off); // dmc3.exe+1EF477 - 49 8D 8D 706A0000 - LEA RCX,[R13+00006A70]
		// Other
		Write<uint32>((appBaseAddr + 0xB9C7C + 3), (enable) ? newOff : off); // dmc3.exe+B9C7C - 4C 8D B7 706A0000 - LEA R14,[RDI+00006A70]
		Write<uint32>((appBaseAddr + 0xCA512 + 3), (enable) ? newOff : off); // dmc3.exe+CA512 - 48 8D 8E 706A0000 - LEA RCX,[RSI+00006A70]
		Write<uint32>((appBaseAddr + 0xCA62B + 3), (enable) ? newOff : off); // dmc3.exe+CA62B - 48 8D 8E 706A0000 - LEA RCX,[RSI+00006A70]
		Write<uint32>((appBaseAddr + 0xCA97E + 3), (enable) ? newOff : off); // dmc3.exe+CA97E - 48 8D 8D 706A0000 - LEA RCX,[RBP+00006A70]
		Write<uint32>((appBaseAddr + 0x1EF8F0 + 3), (enable) ? newOff : off); // dmc3.exe+1EF8F0 - 48 81 C1 706A0000 - ADD RCX,00006A70
		Write<uint32>((appBaseAddr + 0x1EF969 + 3), (enable) ? newOff : off); // dmc3.exe+1EF969 - 48 81 C3 706A0000 - ADD RBX,00006A70
		Write<uint32>((appBaseAddr + 0x1EFB40 + 3), (enable) ? newOff : off); // dmc3.exe+1EFB40 - 48 81 C1 706A0000 - ADD RCX,00006A70
		Write<uint32>((appBaseAddr + 0x1EFB6B + 3), (enable) ? newOff : off); // dmc3.exe+1EFB6B - 48 8D 8B 706A0000 - LEA RCX,[RBX+00006A70]
		Write<uint32>((appBaseAddr + 0x1EFC24 + 3), (enable) ? newOff : off); // dmc3.exe+1EFC24 - 48 81 C1 706A0000 - ADD RCX,00006A70
		Write<uint32>((appBaseAddr + 0x1F0102 + 3), (enable) ? newOff : off); // dmc3.exe+1F0102 - 48 81 C1 706A0000 - ADD RCX,00006A70
		Write<uint32>((appBaseAddr + 0x1F0211 + 3), (enable) ? newOff : off); // dmc3.exe+1F0211 - 48 81 C1 706A0000 - ADD RCX,00006A70
		Write<uint32>((appBaseAddr + 0x1F025C + 3), (enable) ? newOff : off); // dmc3.exe+1F025C - 48 81 C1 706A0000 - ADD RCX,00006A70
		Write<uint32>((appBaseAddr + 0x1F02A5 + 3), (enable) ? newOff : off); // dmc3.exe+1F02A5 - 48 81 C1 706A0000 - ADD RCX,00006A70
		Write<uint32>((appBaseAddr + 0x1F030D + 3), (enable) ? newOff : off); // dmc3.exe+1F030D - 48 81 C1 706A0000 - ADD RCX,00006A70
		Write<uint32>((appBaseAddr + 0x1F0331 + 3), (enable) ? newOff : off); // dmc3.exe+1F0331 - 48 81 C1 706A0000 - ADD RCX,00006A70
		Write<uint32>((appBaseAddr + 0x1F035B + 3), (enable) ? newOff : off); // dmc3.exe+1F035B - 48 81 C1 706A0000 - ADD RCX,00006A70
		Write<uint32>((appBaseAddr + 0x1F0385 + 3), (enable) ? newOff : off); // dmc3.exe+1F0385 - 48 81 C1 706A0000 - ADD RCX,00006A70
		Write<uint32>((appBaseAddr + 0x1F03B7 + 3), (enable) ? newOff : off); // dmc3.exe+1F03B7 - 48 81 C1 706A0000 - ADD RCX,00006A70
		Write<uint32>((appBaseAddr + 0x1F903D + 3), (enable) ? newOff : off); // dmc3.exe+1F903D - 48 81 C1 706A0000 - ADD RCX,00006A70
	}
	// 0x6B90
	{
		constexpr auto off = offsetof(PlayerActorData, bodyPartData[1][0]);
		constexpr auto newOff = offsetof(PlayerActorData, newBodyPartData[1][0]);
		static_assert(off == 0x6B90);
		// func_1EF040
		Write<uint32>((appBaseAddr + 0x1EF3AE + 3), (enable) ? newOff : off); // dmc3.exe+1EF3AE - 49 8D 8D 906B0000 - LEA RCX,[R13+00006B90]
	}
	// 0x6CB0
	{
		constexpr auto off = offsetof(PlayerActorData, bodyPartData[1][1]);
		constexpr auto newOff = offsetof(PlayerActorData, newBodyPartData[1][1]);
		static_assert(off == 0x6CB0);
		// func_1EF040
		Write<uint32>((appBaseAddr + 0x1EF357 + 3), (enable) ? newOff : off); // dmc3.exe+1EF357 - 49 8D 8D B06C0000 - LEA RCX,[R13+00006CB0]
	}
	// 0x6DD0
	{
		constexpr auto off = offsetof(PlayerActorData, bodyPartData[2][0]);
		constexpr auto newOff = offsetof(PlayerActorData, newBodyPartData[2][0]);
		static_assert(off == 0x6DD0);
		// func_1EF040
		Write<uint32>((appBaseAddr + 0x1EF282 + 3), (enable) ? newOff : off); // dmc3.exe+1EF282 - 49 8D 8D D06D0000 - LEA RCX,[R13+00006DD0]
	}
	// 0x6EF0
	{
		constexpr auto off = offsetof(PlayerActorData, bodyPartData[2][1]);
		constexpr auto newOff = offsetof(PlayerActorData, newBodyPartData[2][1]);
		static_assert(off == 0x6EF0);
		// func_1EF040
		Write<uint32>((appBaseAddr + 0x1EF22B + 3), (enable) ? newOff : off); // dmc3.exe+1EF22B - 49 8D 8D F06E0000 - LEA RCX,[R13+00006EF0]
	}
	// 0x7540
	{
		constexpr auto off = offsetof(PlayerActorDataDante, submodelData[0]);
		constexpr auto newOff = offsetof(PlayerActorDataDante, newSubmodelData[0]);
		static_assert(off == 0x7540);
		// Update Actor Dante
		Write<uint32>((appBaseAddr + 0x2132C5 + 3), (enable) ? newOff : off); // dmc3.exe+2132C5 - 49 81 C4 40750000 - ADD R12,00007540
		Write<uint32>((appBaseAddr + 0x2136BF + 3), (enable) ? newOff : off); // dmc3.exe+2136BF - 49 81 C4 40750000 - ADD R12,00007540
		Write<uint32>((appBaseAddr + 0x213ACD + 3), (enable) ? newOff : off); // dmc3.exe+213ACD - 49 81 C4 40750000 - ADD R12,00007540
		Write<uint32>((appBaseAddr + 0x213D57 + 3), (enable) ? newOff : off); // dmc3.exe+213D57 - 49 81 C4 40750000 - ADD R12,00007540
		Write<uint32>((appBaseAddr + 0x21424F + 3), (enable) ? newOff : off); // dmc3.exe+21424F - 49 81 C4 40750000 - ADD R12,00007540
		Write<uint32>((appBaseAddr + 0x21463A + 3), (enable) ? newOff : off); // dmc3.exe+21463A - 49 81 C4 40750000 - ADD R12,00007540
		Write<uint32>((appBaseAddr + 0x2148B6 + 3), (enable) ? newOff : off); // dmc3.exe+2148B6 - 49 81 C4 40750000 - ADD R12,00007540
		// Update Actor Bob
		Write<uint32>((appBaseAddr + 0x2260CA + 3), (enable) ? newOff : off); // dmc3.exe+2260CA - 49 8D B6 40750000 - LEA RSI,[R14+00007540]
		Write<uint32>((appBaseAddr + 0x22648D + 3), (enable) ? newOff : off); // dmc3.exe+22648D - 48 81 C7 40750000 - ADD RDI,00007540
		Write<uint32>((appBaseAddr + 0x22669C + 3), (enable) ? newOff : off); // dmc3.exe+22669C - 48 81 C7 40750000 - ADD RDI,00007540
		Write<uint32>((appBaseAddr + 0x2268A2 + 3), (enable) ? newOff : off); // dmc3.exe+2268A2 - 48 81 C7 40750000 - ADD RDI,00007540
		// Write<uint32>((appBaseAddr + 0x226A03 + 3), (enable) ? newOff : off); // dmc3.exe+226A03 - 48 81 C7 40750000 - ADD RDI,00007540
		Write<uint32>((appBaseAddr + 0x226C92 + 3), (enable) ? newOff : off); // dmc3.exe+226C92 - 49 8D 8E 40750000 - LEA RCX,[R14+00007540]
		// Update Actor Lady
		Write<uint32>((appBaseAddr + 0x2193C2 + 3), (enable) ? newOff : off); // dmc3.exe+2193C2 - 48 8D B5 40750000 - LEA RSI,[RBP+00007540]
		// Update Actor Vergil
		Write<uint32>((appBaseAddr + 0x220F35 + 3), (enable) ? newOff : off); // dmc3.exe+220F35 - 49 81 C6 40750000 - ADD R14,00007540
		Write<uint32>((appBaseAddr + 0x2212C8 + 3), (enable) ? newOff : off); // dmc3.exe+2212C8 - 49 81 C6 40750000 - ADD R14,00007540
		Write<uint32>((appBaseAddr + 0x2216C3 + 3), (enable) ? newOff : off); // dmc3.exe+2216C3 - 49 81 C6 40750000 - ADD R14,00007540
		Write<uint32>((appBaseAddr + 0x22195B + 3), (enable) ? newOff : off); // dmc3.exe+22195B - 49 81 C6 40750000 - ADD R14,00007540
		Write<uint32>((appBaseAddr + 0x221BC4 + 4), (enable) ? newOff : off); // dmc3.exe+221BC4 - 4D 8D B4 24 40750000 - LEA R14,[R12+00007540]
		// Update Model Dante
		Write<uint32>((appBaseAddr + 0x214FAB + 3), (enable) ? newOff : off); // dmc3.exe+214FAB - 4D 8D AE 40750000 - LEA R13,[R14+00007540]
		Write<uint32>((appBaseAddr + 0x2152A1 + 3), (enable) ? newOff : off); // dmc3.exe+2152A1 - 49 8D B6 40750000 - LEA RSI,[R14+00007540]
		// Update Model Vergil
		Write<uint32>((appBaseAddr + 0x22221B + 3), (enable) ? newOff : off); // dmc3.exe+22221B - 4C 8D AD 40750000 - LEA R13,[RBP+00007540]
		Write<uint32>((appBaseAddr + 0x222449 + 3), (enable) ? newOff : off); // dmc3.exe+222449 - 4C 8D AD 40750000 - LEA R13,[RBP+00007540]
		Write<uint32>((appBaseAddr + 0x222702 + 3), (enable) ? newOff : off); // dmc3.exe+222702 - 48 8D B5 40750000 - LEA RSI,[RBP+00007540]
		// func_1DD480
		Write<uint32>((appBaseAddr + 0x1DD4D2 + 3), (enable) ? newOff : off); // dmc3.exe+1DD4D2 - 48 8D 8B 40750000 - LEA RCX,[RBX+00007540]
		// func_1DDE40
		Write<uint32>((appBaseAddr + 0x1DDF1E + 3), (enable) ? newOff : off); // dmc3.exe+1DDF1E - 48 8D 8B 40750000 - LEA RCX,[RBX+00007540]
		// func_1DE160
		Write<uint32>((appBaseAddr + 0x1DE24C + 3), (enable) ? newOff : off); // dmc3.exe+1DE24C - 48 8D 8B 40750000 - LEA RCX,[RBX+00007540]
		// func_211F20
		Write<uint32>((appBaseAddr + 0x211F4D + 3), (enable) ? newOff : off); // dmc3.exe+211F4D - 4C 8D B9 40750000 - LEA R15,[RCX+00007540]
		Write<uint32>((appBaseAddr + 0x211F68 + 3), (enable) ? newOff : off); // dmc3.exe+211F68 - 48 8D 8B 40750000 - LEA RCX,[RBX+00007540]
		// Other
		Write<uint32>((appBaseAddr + 0x1DD642 + 3), (enable) ? newOff : off); // dmc3.exe+1DD642 - 48 8D 8B 40750000 - LEA RCX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x1DD7F2 + 3), (enable) ? newOff : off); // dmc3.exe+1DD7F2 - 48 8D 8B 40750000 - LEA RCX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x1DD9A2 + 3), (enable) ? newOff : off); // dmc3.exe+1DD9A2 - 48 8D 8B 40750000 - LEA RCX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x1DDFF0 + 3), (enable) ? newOff : off); // dmc3.exe+1DDFF0 - 48 8D 8B 40750000 - LEA RCX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x1DE126 + 3), (enable) ? newOff : off); // dmc3.exe+1DE126 - 48 8D 8B 40750000 - LEA RCX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x21209D + 3), (enable) ? newOff : off); // dmc3.exe+21209D - 48 8D 96 40750000 - LEA RDX,[RSI+00007540]
		Write<uint32>((appBaseAddr + 0x2120CB + 3), (enable) ? newOff : off); // dmc3.exe+2120CB - 48 8D 8E 40750000 - LEA RCX,[RSI+00007540]
		Write<uint32>((appBaseAddr + 0x2120D2 + 3), (enable) ? newOff : off); // dmc3.exe+2120D2 - 48 8B 86 40750000 - MOV RAX,[RSI+00007540]
		Write<uint32>((appBaseAddr + 0x212176 + 3), (enable) ? newOff : off); // dmc3.exe+212176 - 48 8D 96 40750000 - LEA RDX,[RSI+00007540]
		Write<uint32>((appBaseAddr + 0x2121E7 + 3), (enable) ? newOff : off); // dmc3.exe+2121E7 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x212258 + 3), (enable) ? newOff : off); // dmc3.exe+212258 - 48 8D 96 40750000 - LEA RDX,[RSI+00007540]
		Write<uint32>((appBaseAddr + 0x2122C9 + 3), (enable) ? newOff : off); // dmc3.exe+2122C9 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x212326 + 3), (enable) ? newOff : off); // dmc3.exe+212326 - 48 8D 96 40750000 - LEA RDX,[RSI+00007540]
		Write<uint32>((appBaseAddr + 0x212397 + 3), (enable) ? newOff : off); // dmc3.exe+212397 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x212408 + 3), (enable) ? newOff : off); // dmc3.exe+212408 - 48 8D 96 40750000 - LEA RDX,[RSI+00007540]
		Write<uint32>((appBaseAddr + 0x212479 + 3), (enable) ? newOff : off); // dmc3.exe+212479 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x2124EA + 3), (enable) ? newOff : off); // dmc3.exe+2124EA - 48 8D 96 40750000 - LEA RDX,[RSI+00007540]
		Write<uint32>((appBaseAddr + 0x21255B + 3), (enable) ? newOff : off); // dmc3.exe+21255B - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x2125B5 + 3), (enable) ? newOff : off); // dmc3.exe+2125B5 - 48 8D 96 40750000 - LEA RDX,[RSI+00007540]
		Write<uint32>((appBaseAddr + 0x212626 + 3), (enable) ? newOff : off); // dmc3.exe+212626 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x2126BD + 3), (enable) ? newOff : off); // dmc3.exe+2126BD - 48 8D 96 40750000 - LEA RDX,[RSI+00007540]
		Write<uint32>((appBaseAddr + 0x21272E + 3), (enable) ? newOff : off); // dmc3.exe+21272E - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x21557C + 3), (enable) ? newOff : off); // dmc3.exe+21557C - 48 81 C7 40750000 - ADD RDI,00007540
		Write<uint32>((appBaseAddr + 0x2166B2 + 3), (enable) ? newOff : off); // dmc3.exe+2166B2 - 48 8D 97 40750000 - LEA RDX,[RDI+00007540]
		Write<uint32>((appBaseAddr + 0x2166EC + 3), (enable) ? newOff : off); // dmc3.exe+2166EC - 48 8D 97 40750000 - LEA RDX,[RDI+00007540]
		Write<uint32>((appBaseAddr + 0x21675C + 3), (enable) ? newOff : off); // dmc3.exe+21675C - 48 8D 97 40750000 - LEA RDX,[RDI+00007540]
		Write<uint32>((appBaseAddr + 0x2167CC + 3), (enable) ? newOff : off); // dmc3.exe+2167CC - 48 8D 97 40750000 - LEA RDX,[RDI+00007540]
		Write<uint32>((appBaseAddr + 0x21683C + 3), (enable) ? newOff : off); // dmc3.exe+21683C - 48 8D 97 40750000 - LEA RDX,[RDI+00007540]
		Write<uint32>((appBaseAddr + 0x2168AC + 3), (enable) ? newOff : off); // dmc3.exe+2168AC - 48 8D 97 40750000 - LEA RDX,[RDI+00007540]
		Write<uint32>((appBaseAddr + 0x21691C + 3), (enable) ? newOff : off); // dmc3.exe+21691C - 48 8D 97 40750000 - LEA RDX,[RDI+00007540]
		Write<uint32>((appBaseAddr + 0x21698C + 3), (enable) ? newOff : off); // dmc3.exe+21698C - 48 8D 97 40750000 - LEA RDX,[RDI+00007540]
		Write<uint32>((appBaseAddr + 0x2189F2 + 3), (enable) ? newOff : off); // dmc3.exe+2189F2 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x218A55 + 3), (enable) ? newOff : off); // dmc3.exe+218A55 - 48 8D 8F 40750000 - LEA RCX,[RDI+00007540]
		Write<uint32>((appBaseAddr + 0x218A8B + 3), (enable) ? newOff : off); // dmc3.exe+218A8B - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x218AD9 + 3), (enable) ? newOff : off); // dmc3.exe+218AD9 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x218B21 + 3), (enable) ? newOff : off); // dmc3.exe+218B21 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x218B8C + 3), (enable) ? newOff : off); // dmc3.exe+218B8C - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x218BD4 + 3), (enable) ? newOff : off); // dmc3.exe+218BD4 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x218C22 + 3), (enable) ? newOff : off); // dmc3.exe+218C22 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x218C6A + 3), (enable) ? newOff : off); // dmc3.exe+218C6A - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x218CB8 + 3), (enable) ? newOff : off); // dmc3.exe+218CB8 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x218D00 + 3), (enable) ? newOff : off); // dmc3.exe+218D00 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x218D68 + 3), (enable) ? newOff : off); // dmc3.exe+218D68 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x218DB0 + 3), (enable) ? newOff : off); // dmc3.exe+218DB0 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x218DFE + 3), (enable) ? newOff : off); // dmc3.exe+218DFE - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x218E46 + 3), (enable) ? newOff : off); // dmc3.exe+218E46 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x218ED5 + 3), (enable) ? newOff : off); // dmc3.exe+218ED5 - 48 8D 9F 40750000 - LEA RBX,[RDI+00007540]
		Write<uint32>((appBaseAddr + 0x218F3F + 3), (enable) ? newOff : off); // dmc3.exe+218F3F - 48 8D 9F 40750000 - LEA RBX,[RDI+00007540]
		Write<uint32>((appBaseAddr + 0x21914B + 3), (enable) ? newOff : off); // dmc3.exe+21914B - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x2191FE + 3), (enable) ? newOff : off); // dmc3.exe+2191FE - 48 8D 97 40750000 - LEA RDX,[RDI+00007540]
		Write<uint32>((appBaseAddr + 0x219211 + 3), (enable) ? newOff : off); // dmc3.exe+219211 - 48 8D 8F 40750000 - LEA RCX,[RDI+00007540]
		Write<uint32>((appBaseAddr + 0x219218 + 3), (enable) ? newOff : off); // dmc3.exe+219218 - 48 8B 87 40750000 - MOV RAX,[RDI+00007540]
		Write<uint32>((appBaseAddr + 0x219A76 + 3), (enable) ? newOff : off); // dmc3.exe+219A76 - 48 8D B1 40750000 - LEA RSI,[RCX+00007540]
		Write<uint32>((appBaseAddr + 0x219BFC + 3), (enable) ? newOff : off); // dmc3.exe+219BFC - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x2203D7 + 3), (enable) ? newOff : off); // dmc3.exe+2203D7 - 4C 8D B9 40750000 - LEA R15,[RCX+00007540]
		Write<uint32>((appBaseAddr + 0x2203F0 + 3), (enable) ? newOff : off); // dmc3.exe+2203F0 - 48 8D 8B 40750000 - LEA RCX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x2204E2 + 3), (enable) ? newOff : off); // dmc3.exe+2204E2 - 48 8D 91 40750000 - LEA RDX,[RCX+00007540]
		Write<uint32>((appBaseAddr + 0x22050D + 3), (enable) ? newOff : off); // dmc3.exe+22050D - 48 8D 8E 40750000 - LEA RCX,[RSI+00007540]
		Write<uint32>((appBaseAddr + 0x220514 + 3), (enable) ? newOff : off); // dmc3.exe+220514 - 48 8B 86 40750000 - MOV RAX,[RSI+00007540]
		Write<uint32>((appBaseAddr + 0x220580 + 3), (enable) ? newOff : off); // dmc3.exe+220580 - 48 8D 96 40750000 - LEA RDX,[RSI+00007540]
		Write<uint32>((appBaseAddr + 0x2205E0 + 3), (enable) ? newOff : off); // dmc3.exe+2205E0 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x22062F + 3), (enable) ? newOff : off); // dmc3.exe+22062F - 48 8D 96 40750000 - LEA RDX,[RSI+00007540]
		Write<uint32>((appBaseAddr + 0x220691 + 3), (enable) ? newOff : off); // dmc3.exe+220691 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x2206F9 + 3), (enable) ? newOff : off); // dmc3.exe+2206F9 - 48 8D 96 40750000 - LEA RDX,[RSI+00007540]
		Write<uint32>((appBaseAddr + 0x22076B + 3), (enable) ? newOff : off); // dmc3.exe+22076B - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x220810 + 3), (enable) ? newOff : off); // dmc3.exe+220810 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x220888 + 3), (enable) ? newOff : off); // dmc3.exe+220888 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x222861 + 3), (enable) ? newOff : off); // dmc3.exe+222861 - 48 8D B7 40750000 - LEA RSI,[RDI+00007540]
		Write<uint32>((appBaseAddr + 0x22306F + 3), (enable) ? newOff : off); // dmc3.exe+22306F - 48 8D 91 40750000 - LEA RDX,[RCX+00007540]
		Write<uint32>((appBaseAddr + 0x2230B8 + 3), (enable) ? newOff : off); // dmc3.exe+2230B8 - 48 8D 93 40750000 - LEA RDX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x2230E7 + 3), (enable) ? newOff : off); // dmc3.exe+2230E7 - 48 8D 8B 40750000 - LEA RCX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x2230EE + 3), (enable) ? newOff : off); // dmc3.exe+2230EE - 48 8B 83 40750000 - MOV RAX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x22314B + 3), (enable) ? newOff : off); // dmc3.exe+22314B - 48 8D 93 40750000 - LEA RDX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x2231BC + 3), (enable) ? newOff : off); // dmc3.exe+2231BC - 48 8D 93 40750000 - LEA RDX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x223217 + 3), (enable) ? newOff : off); // dmc3.exe+223217 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x223276 + 3), (enable) ? newOff : off); // dmc3.exe+223276 - 48 8D 93 40750000 - LEA RDX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x2232C4 + 3), (enable) ? newOff : off); // dmc3.exe+2232C4 - 48 8D 93 40750000 - LEA RDX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x223329 + 3), (enable) ? newOff : off); // dmc3.exe+223329 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x22338D + 3), (enable) ? newOff : off); // dmc3.exe+22338D - 48 8D 93 40750000 - LEA RDX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x2233E5 + 3), (enable) ? newOff : off); // dmc3.exe+2233E5 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x223780 + 3), (enable) ? newOff : off); // dmc3.exe+223780 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x2237DF + 3), (enable) ? newOff : off); // dmc3.exe+2237DF - 48 8D B1 40750000 - LEA RSI,[RCX+00007540]
		Write<uint32>((appBaseAddr + 0x2238C3 + 3), (enable) ? newOff : off); // dmc3.exe+2238C3 - 48 8D B5 40750000 - LEA RSI,[RBP+00007540]
		Write<uint32>((appBaseAddr + 0x223919 + 3), (enable) ? newOff : off); // dmc3.exe+223919 - 48 8D B5 40750000 - LEA RSI,[RBP+00007540]
		Write<uint32>((appBaseAddr + 0x22397A + 3), (enable) ? newOff : off); // dmc3.exe+22397A - 48 8D B5 40750000 - LEA RSI,[RBP+00007540]
		Write<uint32>((appBaseAddr + 0x2239DF + 3), (enable) ? newOff : off); // dmc3.exe+2239DF - 48 8D B5 40750000 - LEA RSI,[RBP+00007540]
		Write<uint32>((appBaseAddr + 0x223A46 + 3), (enable) ? newOff : off); // dmc3.exe+223A46 - 48 8D B5 40750000 - LEA RSI,[RBP+00007540]
		Write<uint32>((appBaseAddr + 0x2243CA + 3), (enable) ? newOff : off); // dmc3.exe+2243CA - 48 8D BB 40750000 - LEA RDI,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x2244D7 + 3), (enable) ? newOff : off); // dmc3.exe+2244D7 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x22451B + 3), (enable) ? newOff : off); // dmc3.exe+22451B - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x22456E + 3), (enable) ? newOff : off); // dmc3.exe+22456E - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x2245B2 + 3), (enable) ? newOff : off); // dmc3.exe+2245B2 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x2245F9 + 3), (enable) ? newOff : off); // dmc3.exe+2245F9 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x22463F + 3), (enable) ? newOff : off); // dmc3.exe+22463F - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x22468B + 3), (enable) ? newOff : off); // dmc3.exe+22468B - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x2246D1 + 3), (enable) ? newOff : off); // dmc3.exe+2246D1 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x22472C + 3), (enable) ? newOff : off); // dmc3.exe+22472C - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x224770 + 3), (enable) ? newOff : off); // dmc3.exe+224770 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x2259A0 + 3), (enable) ? newOff : off); // dmc3.exe+2259A0 - 48 8D B1 40750000 - LEA RSI,[RCX+00007540]
		Write<uint32>((appBaseAddr + 0x2259AF + 3), (enable) ? newOff : off); // dmc3.exe+2259AF - 48 8D 8D 40750000 - LEA RCX,[RBP+00007540]
		Write<uint32>((appBaseAddr + 0x225A4E + 3), (enable) ? newOff : off); // dmc3.exe+225A4E - 48 8D 93 40750000 - LEA RDX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x225A78 + 3), (enable) ? newOff : off); // dmc3.exe+225A78 - 48 8D 8B 40750000 - LEA RCX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x225A7F + 3), (enable) ? newOff : off); // dmc3.exe+225A7F - 48 8B 83 40750000 - MOV RAX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x225BB8 + 3), (enable) ? newOff : off); // dmc3.exe+225BB8 - 48 8D 93 40750000 - LEA RDX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x225C2A + 3), (enable) ? newOff : off); // dmc3.exe+225C2A - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x225CCF + 3), (enable) ? newOff : off); // dmc3.exe+225CCF - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x225D3B + 3), (enable) ? newOff : off); // dmc3.exe+225D3B - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x226D9F + 3), (enable) ? newOff : off); // dmc3.exe+226D9F - 48 8D 91 40750000 - LEA RDX,[RCX+00007540]
		Write<uint32>((appBaseAddr + 0x226DE9 + 3), (enable) ? newOff : off); // dmc3.exe+226DE9 - 48 8D 93 40750000 - LEA RDX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x226E56 + 3), (enable) ? newOff : off); // dmc3.exe+226E56 - 48 8D 93 40750000 - LEA RDX,[RBX+00007540]
		Write<uint32>((appBaseAddr + 0x2272D8 + 3), (enable) ? newOff : off); // dmc3.exe+2272D8 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x227370 + 3), (enable) ? newOff : off); // dmc3.exe+227370 - 48 81 C1 40750000 - ADD RCX,00007540
		Write<uint32>((appBaseAddr + 0x2273A8 + 3), (enable) ? newOff : off); // dmc3.exe+2273A8 - 48 81 C1 40750000 - ADD RCX,00007540
		// Unknown
		// Write<uint32>((appBaseAddr + 0x180ABD + 3), (enable) ? newOff : off); // dmc3.exe+180ABD - 48 8D 8F 40750000 - LEA RCX,[RDI+00007540]
		// Write<uint32>((appBaseAddr + 0x225AEE + 3), (enable) ? newOff : off); // dmc3.exe+225AEE - 48 8D 93 40750000 - LEA RDX,[RBX+00007540]
		// Write<uint32>((appBaseAddr + 0x225B50 + 3), (enable) ? newOff : off); // dmc3.exe+225B50 - 48 81 C1 40750000 - ADD RCX,00007540
		// Write<uint32>((appBaseAddr + 0x226EC3 + 3), (enable) ? newOff : off); // dmc3.exe+226EC3 - 48 8D 93 40750000 - LEA RDX,[RBX+00007540]
	}
	// 0x7548
	{
		constexpr auto off = (offsetof(PlayerActorDataDante, submodelData[0]) + 8);
		constexpr auto newOff = (offsetof(PlayerActorDataDante, newSubmodelData[0]) + 8);
		static_assert(off == 0x7548);
		// Update Actor Vergil
		Write<uint32>((appBaseAddr + 0x221D07 + 3), (enable) ? newOff : off); // dmc3.exe+221D07 - 48 81 C7 48750000 - add rdi,00007548
	}
	// 0x9AC0
	{
		constexpr auto off = offsetof(PlayerActorDataDante, submodelInit[0]);
		constexpr auto newOff = offsetof(PlayerActorDataDante, newSubmodelInit[0]);
		static_assert(off == 0x9AC0);
		// Update Actor Dante
		Write<uint32>((appBaseAddr + 0x212C0D + 3), (enable) ? newOff : off); // dmc3.exe+212C0D - 44 89 B9 C09A0000 - MOV [RCX+00009AC0],R15D
		Write<uint32>((appBaseAddr + 0x21338B + 4), (enable) ? newOff : off); // dmc3.exe+21338B - 42 C6 84 2E C09A0000 01 - MOV BYTE PTR [RSI+R13+00009AC0],01
		Write<uint32>((appBaseAddr + 0x213709 + 3), (enable) ? newOff : off); // dmc3.exe+213709 - C6 84 37 C09A0000 01 - MOV BYTE PTR [RDI+RSI+00009AC0],01
		Write<uint32>((appBaseAddr + 0x213B1D + 3), (enable) ? newOff : off); // dmc3.exe+213B1D - C6 84 37 C09A0000 01 - MOV BYTE PTR [RDI+RSI+00009AC0],01
		Write<uint32>((appBaseAddr + 0x213D9E + 4), (enable) ? newOff : off); // dmc3.exe+213D9E - 41 C6 84 36 C09A0000 01 - MOV BYTE PTR [R14+RSI+00009AC0],01
		Write<uint32>((appBaseAddr + 0x214315 + 4), (enable) ? newOff : off); // dmc3.exe+214315 - 42 C6 84 2E C09A0000 01 - MOV BYTE PTR [RSI+R13+00009AC0],01
		Write<uint32>((appBaseAddr + 0x2146FC + 4), (enable) ? newOff : off); // dmc3.exe+2146FC - 42 C6 84 2E C09A0000 01 - MOV BYTE PTR [RSI+R13+00009AC0],01
		Write<uint32>((appBaseAddr + 0x214978 + 4), (enable) ? newOff : off); // dmc3.exe+214978 - 42 C6 84 36 C09A0000 01 - MOV BYTE PTR [RSI+R14+00009AC0],01
		// Update Actor Bob
		Write<uint32>((appBaseAddr + 0x225D8A + 2), (enable) ? newOff : off); // dmc3.exe+225D8A - C7 81 C09A0000 00000000 - MOV [RCX+00009AC0],00000000
		Write<uint32>((appBaseAddr + 0x226107 + 3), (enable) ? newOff : off); // dmc3.exe+226107 - 41 C6 86 C09A0000 01 - MOV BYTE PTR [R14+00009AC0],01
		Write<uint32>((appBaseAddr + 0x2264D6 + 4), (enable) ? newOff : off); // dmc3.exe+2264D6 - 42 C6 84 36 C09A0000 01 - MOV BYTE PTR [RSI+R14+00009AC0],01
		Write<uint32>((appBaseAddr + 0x2266EB + 4), (enable) ? newOff : off); // dmc3.exe+2266EB - 43 C6 84 34 C09A0000 01 - MOV BYTE PTR [R12+R14+00009AC0],01
		Write<uint32>((appBaseAddr + 0x2268F7 + 4), (enable) ? newOff : off); // dmc3.exe+2268F7 - 43 C6 84 34 C09A0000 01 - MOV BYTE PTR [R12+R14+00009AC0],01
		// Write<uint32>((appBaseAddr + 0x226A43 + 4), (enable) ? newOff : off); // dmc3.exe+226A43 - 42 C6 84 36 C09A0000 01 - MOV BYTE PTR [RSI+R14+00009AC0],01
		// Update Actor Vergil
		Write<uint32>((appBaseAddr + 0x22098E + 3), (enable) ? newOff : off); // dmc3.exe+22098E - 44 89 B1 C09A0000 - MOV [RCX+00009AC0],R14D
		Write<uint32>((appBaseAddr + 0x22116B + 4), (enable) ? newOff : off); // dmc3.exe+22116B - 42 88 9C 20 C09A0000 - MOV [RAX+R12+00009AC0],BL
		Write<uint32>((appBaseAddr + 0x22136C + 4), (enable) ? newOff : off); // dmc3.exe+22136C - 43 C6 84 27 C09A0000 01 - MOV BYTE PTR [R15+R12+00009AC0],01
		Write<uint32>((appBaseAddr + 0x221770 + 4), (enable) ? newOff : off); // dmc3.exe+221770 - 43 C6 84 27 C09A0000 01 - MOV BYTE PTR [R15+R12+00009AC0],01
		Write<uint32>((appBaseAddr + 0x221A0A + 4), (enable) ? newOff : off); // dmc3.exe+221A0A - 42 C6 84 25 C09A0000 01 - MOV BYTE PTR [RBP+R12+00009AC0],01
		Write<uint32>((appBaseAddr + 0x221DF9 + 4), (enable) ? newOff : off); // dmc3.exe+221DF9 - 42 C6 84 25 C09A0000 01 - MOV BYTE PTR [RBP+R12+00009AC0],01
		// Update Model Dante
		Write<uint32>((appBaseAddr + 0x214FE3 + 3), (enable) ? newOff : off); // dmc3.exe+214FE3 - 41 C6 86 C09A0000 01 - MOV BYTE PTR [R14+00009AC0],01
		Write<uint32>((appBaseAddr + 0x2152D6 + 3), (enable) ? newOff : off); // dmc3.exe+2152D6 - 41 C6 86 C09A0000 01 - MOV BYTE PTR [R14+00009AC0],01
		// Update Model Vergil
		Write<uint32>((appBaseAddr + 0x222253 + 2), (enable) ? newOff : off); // dmc3.exe+222253 - C6 85 C09A0000 01 - MOV BYTE PTR [RBP+00009AC0],01
		Write<uint32>((appBaseAddr + 0x222481 + 2), (enable) ? newOff : off); // dmc3.exe+222481 - C6 85 C09A0000 01 - MOV BYTE PTR [RBP+00009AC0],01
		Write<uint32>((appBaseAddr + 0x222737 + 2), (enable) ? newOff : off); // dmc3.exe+222737 - C6 85 C09A0000 01 - MOV BYTE PTR [RBP+00009AC0],01
		// func_211F20
		Write<uint32>((appBaseAddr + 0x211F3A + 3), (enable) ? newOff : off); // dmc3.exe+211F3A - 48 8D B9 C09A0000 - LEA RDI,[RCX+00009AC0]
		// Other
		Write<uint32>((appBaseAddr + 0x2203BD + 3), (enable) ? newOff : off); // dmc3.exe+2203BD - 48 8D B1 C09A0000 - LEA RSI,[RCX+00009AC0]
		Write<uint32>((appBaseAddr + 0x225997 + 3), (enable) ? newOff : off); // dmc3.exe+225997 - 48 8D 99 C09A0000 - LEA RBX,[RCX+00009AC0]
	}
	// 0x9AC4
	{
		constexpr auto off = offsetof(PlayerActorDataDante, submodelInit[4]);
		constexpr auto newOff = offsetof(PlayerActorDataDante, newSubmodelInit[4]);
		static_assert(off == 0x9AC4);
		// Update Actor Dante
		Write<uint32>((appBaseAddr + 0x212C14 + 3), (enable) ? newOff : off); // dmc3.exe+212C14 - 44 88 B9 C49A0000 - MOV [RCX+00009AC4],R15L
		// Update Actor Bob
		Write<uint32>((appBaseAddr + 0x225D97 + 2), (enable) ? newOff : off); // dmc3.exe+225D97 - C6 81 C49A0000 00 - MOV BYTE PTR [RCX+00009AC4],00
		// Update Actor Vergil
		Write<uint32>((appBaseAddr + 0x220997 + 3), (enable) ? newOff : off); // dmc3.exe+220997 - 44 88 B1 C49A0000 - MOV [RCX+00009AC4],R14L
	}
	// 0x9AC8
	{
		constexpr auto off = offsetof(PlayerActorDataDante, submodelInit[8]);
		constexpr auto newOff = offsetof(PlayerActorDataDante, newSubmodelInit[8]);
		static_assert(off == 0x9AC8);
		// Update Actor Bob
		Write<uint32>((appBaseAddr + 0x226318 + 3), (enable) ? newOff : off); // dmc3.exe+226318 - 49 89 B6 C89A0000 - MOV [R14+00009AC8],RSI
		// Update Actor Vergil
		Write<uint32>((appBaseAddr + 0x220CC4 + 4), (enable) ? newOff : off); // dmc3.exe+220CC4 - 4D 89 B4 24 C89A0000 - MOV [R12+00009AC8],R14
	}
	// 0x9AD0
	{
		constexpr auto off = offsetof(PlayerActorDataDante, modelShadowData[0]);
		constexpr auto newOff = offsetof(PlayerActorDataDante, newModelShadowData[0]);
		static_assert(off == 0x9AD0);
		// Update Actor Dante
		Write<uint32>((appBaseAddr + 0x213262 + 4), (enable) ? newOff : off); // dmc3.exe+213262 - 48 8B BC 33 D09A0000 - MOV RDI,[RBX+RSI+00009AD0]
		Write<uint32>((appBaseAddr + 0x21326D + 3), (enable) ? newOff : off); // dmc3.exe+21326D - 48 8D 8E D09A0000 - LEA RCX,[RSI+00009AD0]
		Write<uint32>((appBaseAddr + 0x21365C + 4), (enable) ? newOff : off); // dmc3.exe+21365C - 48 8B BC 33 D09A0000 - MOV RDI,[RBX+RSI+00009AD0]
		Write<uint32>((appBaseAddr + 0x213667 + 3), (enable) ? newOff : off); // dmc3.exe+213667 - 48 8D 8E D09A0000 - LEA RCX,[RSI+00009AD0]
		Write<uint32>((appBaseAddr + 0x213A6A + 4), (enable) ? newOff : off); // dmc3.exe+213A6A - 48 8B BC 33 D09A0000 - MOV RDI,[RBX+RSI+00009AD0]
		Write<uint32>((appBaseAddr + 0x213A75 + 3), (enable) ? newOff : off); // dmc3.exe+213A75 - 48 8D 8E D09A0000 - LEA RCX,[RSI+00009AD0]
		Write<uint32>((appBaseAddr + 0x2140CD + 4), (enable) ? newOff : off); // dmc3.exe+2140CD - 48 8B BC 33 D09A0000 - MOV RDI,[RBX+RSI+00009AD0]
		Write<uint32>((appBaseAddr + 0x2140DD + 3), (enable) ? newOff : off); // dmc3.exe+2140DD - 48 8D 8E D09A0000 - LEA RCX,[RSI+00009AD0]
		Write<uint32>((appBaseAddr + 0x2141ED + 4), (enable) ? newOff : off); // dmc3.exe+2141ED - 48 8B BC 33 D09A0000 - MOV RDI,[RBX+RSI+00009AD0]
		Write<uint32>((appBaseAddr + 0x2141F8 + 3), (enable) ? newOff : off); // dmc3.exe+2141F8 - 48 8D 8E D09A0000 - LEA RCX,[RSI+00009AD0]
		Write<uint32>((appBaseAddr + 0x2145DC + 4), (enable) ? newOff : off); // dmc3.exe+2145DC - 48 8B BC 33 D09A0000 - MOV RDI,[RBX+RSI+00009AD0]
		Write<uint32>((appBaseAddr + 0x2145E7 + 3), (enable) ? newOff : off); // dmc3.exe+2145E7 - 48 8D 8E D09A0000 - LEA RCX,[RSI+00009AD0]
		// Update Actor Bob
		// Write<uint32>((appBaseAddr + 0x22631F + 3), (enable) ? newOff : off); // dmc3.exe+22631F - 49 89 B6 D09A0000 - MOV [R14+00009AD0],RSI - Ignore!
		// Update Actor Vergil
		// Write<uint32>((appBaseAddr + 0x220CCF + 4), (enable) ? newOff : off); // dmc3.exe+220CCF - 4D 89 B4 24 D09A0000 - MOV [R12+00009AD0],R14 - Ignore!
		// Update Model Dante
		Write<uint32>((appBaseAddr + 0x214DED + 3), (enable) ? newOff : off); // dmc3.exe+214DED - 49 8B BE D09A0000 - MOV RDI,[R14+00009AD0]
		Write<uint32>((appBaseAddr + 0x214DFA + 3), (enable) ? newOff : off); // dmc3.exe+214DFA - 49 8D 8E D09A0000 - LEA RCX,[R14+00009AD0]
		// func_1DD480
		Write<uint32>((appBaseAddr + 0x1DD4FD + 3), (enable) ? newOff : off); // dmc3.exe+1DD4FD - 48 8D 8B D09A0000 - LEA RCX,[RBX+00009AD0]
		// func_1DDE40
		Write<uint32>((appBaseAddr + 0x1DDEFF + 3), (enable) ? newOff : off); // dmc3.exe+1DDEFF - 48 8D 8B D09A0000 - LEA RCX,[RBX+00009AD0]
		// func_211F20
		Write<uint32>((appBaseAddr + 0x211FC7 + 3), (enable) ? newOff : off); // dmc3.exe+211FC7 - 48 8D B3 D09A0000 - LEA RSI,[RBX+00009AD0]
		Write<uint32>((appBaseAddr + 0x211FF8 + 3), (enable) ? newOff : off); // dmc3.exe+211FF8 - 48 81 C1 D09A0000 - ADD RCX,00009AD0
		// Other
		Write<uint32>((appBaseAddr + 0x218999 + 3), (enable) ? newOff : off); // dmc3.exe+218999 - 48 81 C1 D09A0000 - ADD RCX,00009AD0
		Write<uint32>((appBaseAddr + 0x218EAC + 3), (enable) ? newOff : off); // dmc3.exe+218EAC - 48 8D 8F D09A0000 - LEA RCX,[RDI+00009AD0]
	}
	// 0x9AF0
	{
		constexpr auto off = offsetof(PlayerActorDataVergil, modelShadowData[0]);
		constexpr auto newOff = offsetof(PlayerActorDataVergil, newModelShadowData[0]);
		static_assert(off == 0x9AF0);
		// Update Actor Vergil
		Write<uint32>((appBaseAddr + 0x220ED2 + 4), (enable) ? newOff : off); // dmc3.exe+220ED2 - 4A 8B BC 23 F09A0000 - MOV RDI,[RBX+R12+00009AF0]
		Write<uint32>((appBaseAddr + 0x220EDD + 3), (enable) ? newOff : off); // dmc3.exe+220EDD - 48 8D 8B F09A0000 - LEA RCX,[RBX+00009AF0]
		Write<uint32>((appBaseAddr + 0x221262 + 4), (enable) ? newOff : off); // dmc3.exe+221262 - 4A 8B BC 23 F09A0000 - MOV RDI,[RBX+R12+00009AF0]
		Write<uint32>((appBaseAddr + 0x22126D + 3), (enable) ? newOff : off); // dmc3.exe+22126D - 48 8D 8B F09A0000 - LEA RCX,[RBX+00009AF0]
		Write<uint32>((appBaseAddr + 0x221663 + 4), (enable) ? newOff : off); // dmc3.exe+221663 - 4A 8B BC 23 F09A0000 - MOV RDI,[RBX+R12+00009AF0]
		Write<uint32>((appBaseAddr + 0x22166E + 3), (enable) ? newOff : off); // dmc3.exe+22166E - 48 8D 8B F09A0000 - LEA RCX,[RBX+00009AF0]
		// Update Model Vergil
		Write<uint32>((appBaseAddr + 0x222073 + 3), (enable) ? newOff : off); // dmc3.exe+222073 - 48 8B B5 F09A0000 - MOV RSI,[RBP+00009AF0]
		Write<uint32>((appBaseAddr + 0x222083 + 3), (enable) ? newOff : off); // dmc3.exe+222083 - 48 8D 8D F09A0000 - LEA RCX,[RBP+00009AF0]
		// func_1DE160
		Write<uint32>((appBaseAddr + 0x1DE22D + 3), (enable) ? newOff : off); // dmc3.exe+1DE22D - 48 8D 8B F09A0000 - LEA RCX,[RBX+00009AF0]
		// Other
		Write<uint32>((appBaseAddr + 0x1DD81D + 3), (enable) ? newOff : off); // dmc3.exe+1DD81D - 48 8D 8B F09A0000 - LEA RCX,[RBX+00009AF0]
		Write<uint32>((appBaseAddr + 0x1DD9CD + 3), (enable) ? newOff : off); // dmc3.exe+1DD9CD - 48 8D 8B F09A0000 - LEA RCX,[RBX+00009AF0]
		Write<uint32>((appBaseAddr + 0x1DE107 + 3), (enable) ? newOff : off); // dmc3.exe+1DE107 - 48 8D 8B F09A0000 - LEA RCX,[RBX+00009AF0]
		Write<uint32>((appBaseAddr + 0x22045C + 3), (enable) ? newOff : off); // dmc3.exe+22045C - 48 8D B3 F09A0000 - LEA RSI,[RBX+00009AF0]
		Write<uint32>((appBaseAddr + 0x22048A + 3), (enable) ? newOff : off); // dmc3.exe+22048A - 48 81 C1 F09A0000 - ADD RCX,00009AF0
		Write<uint32>((appBaseAddr + 0x2243B1 + 3), (enable) ? newOff : off); // dmc3.exe+2243B1 - 48 81 C1 F09A0000 - ADD RCX,00009AF0
		Write<uint32>((appBaseAddr + 0x224491 + 3), (enable) ? newOff : off); // dmc3.exe+224491 - 48 81 C1 F09A0000 - ADD RCX,00009AF0
	}
	// 0x9D10
	{
		constexpr auto off = offsetof(PlayerActorDataDante, submodelShadowData[0]);
		constexpr auto newOff = offsetof(PlayerActorDataDante, newSubmodelShadowData[0]);
		static_assert(off == 0x9D10);
		// Update Actor Dante
		Write<uint32>((appBaseAddr + 0x21335B + 4), (enable) ? newOff : off); // dmc3.exe+21335B - 48 8B BC 33 109D0000 - MOV RDI,[RBX+RSI+00009D10]
		Write<uint32>((appBaseAddr + 0x21336B + 3), (enable) ? newOff : off); // dmc3.exe+21336B - 48 8D 8E 109D0000 - LEA RCX,[RSI+00009D10]
		Write<uint32>((appBaseAddr + 0x213931 + 4), (enable) ? newOff : off); // dmc3.exe+213931 - 48 8B BC 33 109D0000 - MOV RDI,[RBX+RSI+00009D10]
		Write<uint32>((appBaseAddr + 0x21393C + 3), (enable) ? newOff : off); // dmc3.exe+21393C - 48 8D 8E 109D0000 - LEA RCX,[RSI+00009D10]
		Write<uint32>((appBaseAddr + 0x213CD8 + 4), (enable) ? newOff : off); // dmc3.exe+213CD8 - 48 8B BC 33 109D0000 - MOV RDI,[RBX+RSI+00009D10]
		Write<uint32>((appBaseAddr + 0x213CE3 + 3), (enable) ? newOff : off); // dmc3.exe+213CE3 - 48 8D 8E 109D0000 - LEA RCX,[RSI+00009D10]
		Write<uint32>((appBaseAddr + 0x213F8F + 4), (enable) ? newOff : off); // dmc3.exe+213F8F - 48 8B BC 33 109D0000 - MOV RDI,[RBX+RSI+00009D10]
		Write<uint32>((appBaseAddr + 0x213F9A + 3), (enable) ? newOff : off); // dmc3.exe+213F9A - 48 8D 8E 109D0000 - LEA RCX,[RSI+00009D10]
		Write<uint32>((appBaseAddr + 0x2142E5 + 4), (enable) ? newOff : off); // dmc3.exe+2142E5 - 48 8B BC 33 109D0000 - MOV RDI,[RBX+RSI+00009D10]
		Write<uint32>((appBaseAddr + 0x2142F5 + 3), (enable) ? newOff : off); // dmc3.exe+2142F5 - 48 8D 8E 109D0000 - LEA RCX,[RSI+00009D10]
		Write<uint32>((appBaseAddr + 0x2146CC + 4), (enable) ? newOff : off); // dmc3.exe+2146CC - 48 8B BC 33 109D0000 - MOV RDI,[RBX+RSI+00009D10]
		Write<uint32>((appBaseAddr + 0x2146DC + 3), (enable) ? newOff : off); // dmc3.exe+2146DC - 48 8D 8E 109D0000 - LEA RCX,[RSI+00009D10]
		Write<uint32>((appBaseAddr + 0x214948 + 4), (enable) ? newOff : off); // dmc3.exe+214948 - 48 8B BC 33 109D0000 - MOV RDI,[RBX+RSI+00009D10]
		Write<uint32>((appBaseAddr + 0x214958 + 3), (enable) ? newOff : off); // dmc3.exe+214958 - 48 8D 8E 109D0000 - LEA RCX,[RSI+00009D10]
		// Update Model Dante
		Write<uint32>((appBaseAddr + 0x21522A + 3), (enable) ? newOff : off); // dmc3.exe+21522A - 49 8B BE 109D0000 - MOV RDI,[R14+00009D10]
		Write<uint32>((appBaseAddr + 0x215237 + 3), (enable) ? newOff : off); // dmc3.exe+215237 - 49 8D 8E 109D0000 - LEA RCX,[R14+00009D10]
		// func_1DD480
		Write<uint32>((appBaseAddr + 0x1DD528 + 3), (enable) ? newOff : off); // dmc3.exe+1DD528 - 48 8D 8B 109D0000 - LEA RCX,[RBX+00009D10]
		// func_1DDE40
		Write<uint32>((appBaseAddr + 0x1DDEE0 + 3), (enable) ? newOff : off); // dmc3.exe+1DDEE0 - 48 8D 8B 109D0000 - LEA RCX,[RBX+00009D10]
		// func_211F20
		Write<uint32>((appBaseAddr + 0x211F46 + 3), (enable) ? newOff : off); // dmc3.exe+211F46 - 4C 8D B1 109D0000 - LEA R14,[RCX+00009D10]
		Write<uint32>((appBaseAddr + 0x211F9D + 3), (enable) ? newOff : off); // dmc3.exe+211F9D - 48 8D 8B 109D0000 - LEA RCX,[RBX+00009D10]
		// Other
		Write<uint32>((appBaseAddr + 0x218E88 + 3), (enable) ? newOff : off); // dmc3.exe+218E88 - 48 81 C1 109D0000 - ADD RCX,00009D10
		Write<uint32>((appBaseAddr + 0x218F20 + 3), (enable) ? newOff : off); // dmc3.exe+218F20 - 48 8D 8F 109D0000 - LEA RCX,[RDI+00009D10]
	}
	// 0x9D30
	{
		constexpr auto off = offsetof(PlayerActorDataVergil, submodelShadowData[0]);
		constexpr auto newOff = offsetof(PlayerActorDataVergil, newSubmodelShadowData[0]);
		static_assert(off == 0x9D30);
		// Update Actor Vergil
		Write<uint32>((appBaseAddr + 0x220FB4 + 4), (enable) ? newOff : off); // dmc3.exe+220FB4 - 4A 8B BC 23 309D0000 - MOV RDI,[RBX+R12+00009D30]
		Write<uint32>((appBaseAddr + 0x220FBF + 4), (enable) ? newOff : off); // dmc3.exe+220FBF - 49 8D 8C 24 309D0000 - LEA RCX,[R12+00009D30]
		Write<uint32>((appBaseAddr + 0x22133E + 4), (enable) ? newOff : off); // dmc3.exe+22133E - 4A 8B BC 23 309D0000 - MOV RDI,[RBX+R12+00009D30]
		Write<uint32>((appBaseAddr + 0x221349 + 3), (enable) ? newOff : off); // dmc3.exe+221349 - 48 8D 8B 309D0000 - LEA RCX,[RBX+00009D30]
		Write<uint32>((appBaseAddr + 0x221741 + 4), (enable) ? newOff : off); // dmc3.exe+221741 - 4A 8B BC 23 309D0000 - MOV RDI,[RBX+R12+00009D30]
		Write<uint32>((appBaseAddr + 0x22174C + 4), (enable) ? newOff : off); // dmc3.exe+22174C - 49 8D 8C 24 309D0000 - LEA RCX,[R12+00009D30]
		Write<uint32>((appBaseAddr + 0x2219DB + 4), (enable) ? newOff : off); // dmc3.exe+2219DB - 4A 8B BC 23 309D0000 - MOV RDI,[RBX+R12+00009D30]
		Write<uint32>((appBaseAddr + 0x2219E6 + 4), (enable) ? newOff : off); // dmc3.exe+2219E6 - 49 8D 8C 24 309D0000 - LEA RCX,[R12+00009D30]
		Write<uint32>((appBaseAddr + 0x221DAD + 4), (enable) ? newOff : off); // dmc3.exe+221DAD - 4A 8B BC 23 309D0000 - MOV RDI,[RBX+R12+00009D30]
		Write<uint32>((appBaseAddr + 0x221DB8 + 4), (enable) ? newOff : off); // dmc3.exe+221DB8 - 49 8D 8C 24 309D0000 - LEA RCX,[R12+00009D30]
		// Update Model Vergil
		Write<uint32>((appBaseAddr + 0x222698 + 3), (enable) ? newOff : off); // dmc3.exe+222698 - 48 8B B5 309D0000 - MOV RSI,[RBP+00009D30]
		Write<uint32>((appBaseAddr + 0x2226A8 + 3), (enable) ? newOff : off); // dmc3.exe+2226A8 - 48 8D 8D 309D0000 - LEA RCX,[RBP+00009D30]
		// func_1DE160
		Write<uint32>((appBaseAddr + 0x1DE20E + 3), (enable) ? newOff : off); // dmc3.exe+1DE20E - 48 8D 8B 309D0000 - LEA RCX,[RBX+00009D30]
		// Other
		Write<uint32>((appBaseAddr + 0x1DD848 + 3), (enable) ? newOff : off); // dmc3.exe+1DD848 - 48 8D 8B 309D0000 - LEA RCX,[RBX+00009D30]
		Write<uint32>((appBaseAddr + 0x1DD9F8 + 3), (enable) ? newOff : off); // dmc3.exe+1DD9F8 - 48 8D 8B 309D0000 - LEA RCX,[RBX+00009D30]
		Write<uint32>((appBaseAddr + 0x1DE0E8 + 3), (enable) ? newOff : off); // dmc3.exe+1DE0E8 - 48 8D 8B 309D0000 - LEA RCX,[RBX+00009D30]
		Write<uint32>((appBaseAddr + 0x2203D0 + 3), (enable) ? newOff : off); // dmc3.exe+2203D0 - 4C 8D B1 309D0000 - LEA R14,[RCX+00009D30]
		Write<uint32>((appBaseAddr + 0x220425 + 3), (enable) ? newOff : off); // dmc3.exe+220425 - 48 8D 8B 309D0000 - LEA RCX,[RBX+00009D30]
		Write<uint32>((appBaseAddr + 0x22441E + 3), (enable) ? newOff : off); // dmc3.exe+22441E - 48 8D 8B 309D0000 - LEA RCX,[RBX+00009D30]
		Write<uint32>((appBaseAddr + 0x22454A + 3), (enable) ? newOff : off); // dmc3.exe+22454A - 48 81 C1 309D0000 - ADD RCX,00009D30
		Write<uint32>((appBaseAddr + 0x22470E + 3), (enable) ? newOff : off); // dmc3.exe+22470E - 48 81 C1 309D0000 - ADD RCX,00009D30
	}
	// 0xA300
	{
		constexpr auto off = offsetof(PlayerActorDataDante, devilModelPhysicsMetadataPool[0][0]);
		constexpr auto newOff = offsetof(PlayerActorDataDante, newDevilModelPhysicsMetadataPool[0][0]);
		static_assert(off == 0xA300);
		// Create Actor Dante
		Write<uint32>((appBaseAddr + 0x1DEC79 + 3), (enable) ? newOff : off); // dmc3.exe+1DEC79 - 48 81 C2 00A30000 - ADD RDX,0000A300
		// Update Actor Dante
		Write<uint32>((appBaseAddr + 0x2136FC + 3), (enable) ? newOff : off); // dmc3.exe+2136FC - 4D 8D 85 00A30000 - LEA R8,[R13+0000A300]
		Write<uint32>((appBaseAddr + 0x213773 + 3), (enable) ? newOff : off); // dmc3.exe+213773 - 49 8D 95 00A30000 - LEA RDX,[R13+0000A300]
		Write<uint32>((appBaseAddr + 0x2137DA + 4), (enable) ? newOff : off); // dmc3.exe+2137DA - 48 8B 84 C6 00A30000 - MOV RAX,[RSI+RAX*8+0000A300]
		Write<uint32>((appBaseAddr + 0x21383C + 4), (enable) ? newOff : off); // dmc3.exe+21383C - 48 8B 84 C6 00A30000 - MOV RAX,[RSI+RAX*8+0000A300]
		Write<uint32>((appBaseAddr + 0x21389B + 4), (enable) ? newOff : off); // dmc3.exe+21389B - 48 8B 84 C6 00A30000 - MOV RAX,[RSI+RAX*8+0000A300]
		Write<uint32>((appBaseAddr + 0x213B0A + 3), (enable) ? newOff : off); // dmc3.exe+213B0A - 4D 8D 85 00A30000 - LEA R8,[R13+0000A300]
		Write<uint32>((appBaseAddr + 0x213B73 + 3), (enable) ? newOff : off); // dmc3.exe+213B73 - 49 8D 95 00A30000 - LEA RDX,[R13+0000A300]
		Write<uint32>((appBaseAddr + 0x213BDC + 4), (enable) ? newOff : off); // dmc3.exe+213BDC - 48 8B 84 C6 00A30000 - MOV RAX,[RSI+RAX*8+0000A300]
		Write<uint32>((appBaseAddr + 0x213C40 + 4), (enable) ? newOff : off); // dmc3.exe+213C40 - 48 8B 84 C6 00A30000 - MOV RAX,[RSI+RAX*8+0000A300]
		Write<uint32>((appBaseAddr + 0x213D8C + 3), (enable) ? newOff : off); // dmc3.exe+213D8C - 4D 8D 85 00A30000 - LEA R8,[R13+0000A300]
		Write<uint32>((appBaseAddr + 0x213E03 + 3), (enable) ? newOff : off); // dmc3.exe+213E03 - 49 8D 95 00A30000 - LEA RDX,[R13+0000A300]
		Write<uint32>((appBaseAddr + 0x213E93 + 4), (enable) ? newOff : off); // dmc3.exe+213E93 - 48 8B 84 C6 00A30000 - MOV RAX,[RSI+RAX*8+0000A300]
		Write<uint32>((appBaseAddr + 0x213EF7 + 4), (enable) ? newOff : off); // dmc3.exe+213EF7 - 48 8B 84 C6 00A30000 - MOV RAX,[RSI+RAX*8+0000A300]
		Write<uint32>((appBaseAddr + 0x2143D5 + 4), (enable) ? newOff : off); // dmc3.exe+2143D5 - 48 8B 84 C6 00A30000 - MOV RAX,[RSI+RAX*8+0000A300]
		Write<uint32>((appBaseAddr + 0x214434 + 4), (enable) ? newOff : off); // dmc3.exe+214434 - 48 8B 84 C6 00A30000 - MOV RAX,[RSI+RAX*8+0000A300]
		Write<uint32>((appBaseAddr + 0x214490 + 4), (enable) ? newOff : off); // dmc3.exe+214490 - 48 8B 84 C6 00A30000 - MOV RAX,[RSI+RAX*8+0000A300]
		Write<uint32>((appBaseAddr + 0x2147B0 + 4), (enable) ? newOff : off); // dmc3.exe+2147B0 - 48 8B 84 C6 00A30000 - MOV RAX,[RSI+RAX*8+0000A300]
		Write<uint32>((appBaseAddr + 0x214814 + 4), (enable) ? newOff : off); // dmc3.exe+214814 - 48 8B 84 C6 00A30000 - MOV RAX,[RSI+RAX*8+0000A300]
		Write<uint32>((appBaseAddr + 0x214A57 + 4), (enable) ? newOff : off); // dmc3.exe+214A57 - 48 8B 84 C6 00A30000 - MOV RAX,[RSI+RAX*8+0000A300]
		Write<uint32>((appBaseAddr + 0x214ABF + 4), (enable) ? newOff : off); // dmc3.exe+214ABF - 48 8B 84 C6 00A30000 - MOV RAX,[RSI+RAX*8+0000A300]
		// 0x1460
		{
			constexpr auto off = (offsetof(PlayerActorDataDante, devilModelPhysicsMetadataPool[0][0]) / 8);
			constexpr auto newOff = (offsetof(PlayerActorDataDante, newDevilModelPhysicsMetadataPool[0][0]) / 8);
			static_assert(off == 0x1460);
			// Update Actor Dante
			Write<uint32>((appBaseAddr + 0x2132F2 + 2), (enable) ? newOff : off); // dmc3.exe+2132F2 - 48 05 60140000 - ADD RAX,00001460
			Write<uint32>((appBaseAddr + 0x21427C + 2), (enable) ? newOff : off); // dmc3.exe+21427C - 48 05 60140000 - ADD RAX,00001460
			Write<uint32>((appBaseAddr + 0x214667 + 2), (enable) ? newOff : off); // dmc3.exe+214667 - 48 05 60140000 - ADD RAX,00001460
			Write<uint32>((appBaseAddr + 0x2148E3 + 2), (enable) ? newOff : off); // dmc3.exe+2148E3 - 48 05 60140000 - ADD RAX,00001460
		}
	}
	// 0xA540
	{
		constexpr auto off = offsetof(PlayerActorDataDante, devilSubmodelPhysicsData[0]);
		constexpr auto newOff = offsetof(PlayerActorDataDante, newDevilSubmodelPhysicsData[0]);
		static_assert(off == 0xA540);
		// Update Actor Dante
		Write<uint32>((appBaseAddr + 0x2133CA + 3), (enable) ? newOff : off); // dmc3.exe+2133CA - 48 8D BE 40A50000 - LEA RDI,[RSI+0000A540]
		Write<uint32>((appBaseAddr + 0x213746 + 3), (enable) ? newOff : off); // dmc3.exe+213746 - 48 8D BE 40A50000 - LEA RDI,[RSI+0000A540]
		Write<uint32>((appBaseAddr + 0x213B53 + 3), (enable) ? newOff : off); // dmc3.exe+213B53 - 48 8D BE 40A50000 - LEA RDI,[RSI+0000A540]
		Write<uint32>((appBaseAddr + 0x213DDD + 3), (enable) ? newOff : off); // dmc3.exe+213DDD - 48 8D BE 40A50000 - LEA RDI,[RSI+0000A540]
		Write<uint32>((appBaseAddr + 0x213E60 + 3), (enable) ? newOff : off); // dmc3.exe+213E60 - 48 81 C1 40A50000 - ADD RCX,0000A540
		Write<uint32>((appBaseAddr + 0x214353 + 3), (enable) ? newOff : off); // dmc3.exe+214353 - 48 8D BE 40A50000 - LEA RDI,[RSI+0000A540]
		Write<uint32>((appBaseAddr + 0x214736 + 3), (enable) ? newOff : off); // dmc3.exe+214736 - 48 8D BE 40A50000 - LEA RDI,[RSI+0000A540]
		Write<uint32>((appBaseAddr + 0x2149B3 + 3), (enable) ? newOff : off); // dmc3.exe+2149B3 - 48 8D BE 40A50000 - LEA RDI,[RSI+0000A540]
		Write<uint32>((appBaseAddr + 0x214A24 + 3), (enable) ? newOff : off); // dmc3.exe+214A24 - 48 81 C1 40A50000 - ADD RCX,0000A540
		// func_1DD480
		Write<uint32>((appBaseAddr + 0x1DD577 + 3), (enable) ? newOff : off); // dmc3.exe+1DD577 - 48 8D 8B 40A50000 - LEA RCX,[RBX+0000A540]
		// func_1DDE40
		Write<uint32>((appBaseAddr + 0x1DDEA2 + 3), (enable) ? newOff : off); // dmc3.exe+1DDEA2 - 48 8D 8B 40A50000 - LEA RCX,[RBX+0000A540]
		// Other
		Write<uint32>((appBaseAddr + 0x2121BC + 3), (enable) ? newOff : off); // dmc3.exe+2121BC - 48 8D 8E 40A50000 - LEA RCX,[RSI+0000A540]
		Write<uint32>((appBaseAddr + 0x21229E + 3), (enable) ? newOff : off); // dmc3.exe+21229E - 48 8D 8E 40A50000 - LEA RCX,[RSI+0000A540]
		Write<uint32>((appBaseAddr + 0x21236C + 3), (enable) ? newOff : off); // dmc3.exe+21236C - 48 8D 8E 40A50000 - LEA RCX,[RSI+0000A540]
		Write<uint32>((appBaseAddr + 0x21244E + 3), (enable) ? newOff : off); // dmc3.exe+21244E - 48 8D 8E 40A50000 - LEA RCX,[RSI+0000A540]
		Write<uint32>((appBaseAddr + 0x212530 + 3), (enable) ? newOff : off); // dmc3.exe+212530 - 48 8D 8E 40A50000 - LEA RCX,[RSI+0000A540]
		Write<uint32>((appBaseAddr + 0x2125FB + 3), (enable) ? newOff : off); // dmc3.exe+2125FB - 48 8D 8E 40A50000 - LEA RCX,[RSI+0000A540]
		Write<uint32>((appBaseAddr + 0x212703 + 3), (enable) ? newOff : off); // dmc3.exe+212703 - 48 8D 8E 40A50000 - LEA RCX,[RSI+0000A540]
		Write<uint32>((appBaseAddr + 0x216737 + 3), (enable) ? newOff : off); // dmc3.exe+216737 - 48 8D 8F 40A50000 - LEA RCX,[RDI+0000A540]
		Write<uint32>((appBaseAddr + 0x2167A7 + 3), (enable) ? newOff : off); // dmc3.exe+2167A7 - 48 8D 8F 40A50000 - LEA RCX,[RDI+0000A540]
		Write<uint32>((appBaseAddr + 0x216817 + 3), (enable) ? newOff : off); // dmc3.exe+216817 - 48 8D 8F 40A50000 - LEA RCX,[RDI+0000A540]
		Write<uint32>((appBaseAddr + 0x216887 + 3), (enable) ? newOff : off); // dmc3.exe+216887 - 48 8D 8F 40A50000 - LEA RCX,[RDI+0000A540]
		Write<uint32>((appBaseAddr + 0x2168F7 + 3), (enable) ? newOff : off); // dmc3.exe+2168F7 - 48 8D 8F 40A50000 - LEA RCX,[RDI+0000A540]
		Write<uint32>((appBaseAddr + 0x216967 + 3), (enable) ? newOff : off); // dmc3.exe+216967 - 48 8D 8F 40A50000 - LEA RCX,[RDI+0000A540]
		Write<uint32>((appBaseAddr + 0x2169D7 + 3), (enable) ? newOff : off); // dmc3.exe+2169D7 - 48 8D 8F 40A50000 - LEA RCX,[RDI+0000A540]
	}
	// 0xAA00
	{
		constexpr auto off = offsetof(PlayerActorDataDante, devilSubmodelPhysicsLinkData[0][0]);
		constexpr auto newOff = offsetof(PlayerActorDataDante, newDevilSubmodelPhysicsLinkData[0][0]);
		static_assert(off == 0xAA00);
		// Update Actor Dante
		Write<uint32>((appBaseAddr + 0x2137AA + 3), (enable) ? newOff : off); // dmc3.exe+2137AA - 48 8D 96 00AA0000 - LEA RDX,[RSI+0000AA00]
		Write<uint32>((appBaseAddr + 0x213BAA + 3), (enable) ? newOff : off); // dmc3.exe+213BAA - 48 8D 96 00AA0000 - LEA RDX,[RSI+0000AA00]
		Write<uint32>((appBaseAddr + 0x213E8C + 3), (enable) ? newOff : off); // dmc3.exe+213E8C - 48 8D 96 00AA0000 - LEA RDX,[RSI+0000AA00]
		Write<uint32>((appBaseAddr + 0x21439E + 3), (enable) ? newOff : off); // dmc3.exe+21439E - 48 8D 96 00AA0000 - LEA RDX,[RSI+0000AA00]
		Write<uint32>((appBaseAddr + 0x21477E + 3), (enable) ? newOff : off); // dmc3.exe+21477E - 48 8D 96 00AA0000 - LEA RDX,[RSI+0000AA00]
		Write<uint32>((appBaseAddr + 0x214A50 + 3), (enable) ? newOff : off); // dmc3.exe+214A50 - 48 8D 96 00AA0000 - LEA RDX,[RSI+0000AA00]
		// func_1DD480
		Write<uint32>((appBaseAddr + 0x1DD59B + 3), (enable) ? newOff : off); // dmc3.exe+1DD59B - 48 8D 8B 00AA0000 - LEA RCX,[RBX+0000AA00]
		// func_1DDE40
		Write<uint32>((appBaseAddr + 0x1DDE83 + 3), (enable) ? newOff : off); // dmc3.exe+1DDE83 - 48 81 C1 00AA0000 - ADD RCX,0000AA00
	}
	// 0xAAC0
	{
		constexpr auto off = (offsetof(PlayerActorDataDante, devilSubmodelPhysicsLinkData[0][0]) + 0xC0);
		constexpr auto newOff = (offsetof(PlayerActorDataDante, newDevilSubmodelPhysicsLinkData[0][0]) + 0xC0);
		static_assert(off == 0xAAC0);
		// Update Actor Dante
		Write<uint32>((appBaseAddr + 0x213832 + 3), (enable) ? newOff : off); // dmc3.exe+213832 - 48 8D 96 C0AA0000 - LEA RDX,[RSI+0000AAC0]
		Write<uint32>((appBaseAddr + 0x213C36 + 3), (enable) ? newOff : off); // dmc3.exe+213C36 - 48 8D 96 C0AA0000 - LEA RDX,[RSI+0000AAC0]
		Write<uint32>((appBaseAddr + 0x213EED + 3), (enable) ? newOff : off); // dmc3.exe+213EED - 48 8D 96 C0AA0000 - LEA RDX,[RSI+0000AAC0]
		Write<uint32>((appBaseAddr + 0x21442A + 3), (enable) ? newOff : off); // dmc3.exe+21442A - 48 8D 96 C0AA0000 - LEA RDX,[RSI+0000AAC0]
		Write<uint32>((appBaseAddr + 0x21480A + 3), (enable) ? newOff : off); // dmc3.exe+21480A - 48 8D 96 C0AA0000 - LEA RDX,[RSI+0000AAC0]
		Write<uint32>((appBaseAddr + 0x214AB5 + 3), (enable) ? newOff : off); // dmc3.exe+214AB5 - 48 8D 96 C0AA0000 - LEA RDX,[RSI+0000AAC0]
	}
}



export void ToggleEffectRelocations(bool enable)
{
	LogFunction(enable);

	static bool run = false;

	{
		auto addr     = (appBaseAddr + 0x8DC1C);
		auto jumpAddr = (appBaseAddr + 0x8DC23);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+8DC1C - 8B 84 96 C02DC900 - MOV EAX,[RSI+RDX*4+00C92DC0]
		dmc3.exe+8DC23
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rbx,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x8DC41);
		auto jumpAddr = (appBaseAddr + 0x8DC48);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+8DC41 - 31 84 96 C02DC900 - XOR [RSI+RDX*4+00C92DC0],EAX
		dmc3.exe+8DC48
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			push_rax,
			mov_rcx_rbx,
			call,
			mov_rcx_rax,
			pop_rax,
			0x31, 0x84, 0x91, 0x00, 0x00, 0x00, 0x00, // xor [rcx+rdx*4+0000B8C0],eax
			pop_rcx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 5), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0x11) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x8F9C5);
		auto jumpAddr = (appBaseAddr + 0x8F9CD);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+8F9C5 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+8F9CD
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x8F9EE);
		auto jumpAddr = (appBaseAddr + 0x8F9F6);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+8F9EE - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+8F9F6
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x8FA18);
		auto jumpAddr = (appBaseAddr + 0x8FA20);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+8FA18 - 41 31 9C 94 C02DC900 - XOR [R12+RDX*4+00C92DC0],EBX
		dmc3.exe+8FA20
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			push_rax,
			mov_rcx_rdi,
			call,
			mov_rcx_rax,
			pop_rax,
			0x31, 0x9C, 0x91, 0x00, 0x00, 0x00, 0x00, // xor [rcx+rdx*4+0000B8C0],ebx
			pop_rcx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 5), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0x11) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x8FBA1);
		auto jumpAddr = (appBaseAddr + 0x8FBA9);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+8FBA1 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+8FBA9
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x8FBCA);
		auto jumpAddr = (appBaseAddr + 0x8FBD2);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+8FBCA - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+8FBD2
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x8FBF4);
		auto jumpAddr = (appBaseAddr + 0x8FBFC);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+8FBF4 - 41 31 9C 94 C02DC900 - XOR [R12+RDX*4+00C92DC0],EBX
		dmc3.exe+8FBFC
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			push_rax,
			mov_rcx_rdi,
			call,
			mov_rcx_rax,
			pop_rax,
			0x31, 0x9C, 0x91, 0x00, 0x00, 0x00, 0x00, // xor [rcx+rdx*4+0000B8C0],ebx
			pop_rcx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 5), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0x11) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x8FD14);
		auto jumpAddr = (appBaseAddr + 0x8FD1C);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+8FD14 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+8FD1C
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x8FDB6);
		auto jumpAddr = (appBaseAddr + 0x8FDBE);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+8FDB6 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+8FDBE
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x8FDDC);
		auto jumpAddr = (appBaseAddr + 0x8FDE4);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+8FDDC - 41 31 9C 94 C02DC900 - XOR [R12+RDX*4+00C92DC0],EBX
		dmc3.exe+8FDE4
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			push_rax,
			mov_rcx_rdi,
			call,
			mov_rcx_rax,
			pop_rax,
			0x31, 0x9C, 0x91, 0x00, 0x00, 0x00, 0x00, // xor [rcx+rdx*4+0000B8C0],ebx
			pop_rcx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 5), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0x11) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x8FEA9);
		auto jumpAddr = (appBaseAddr + 0x8FEB1);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+8FEA9 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+8FEB1
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x8FECF);
		auto jumpAddr = (appBaseAddr + 0x8FED7);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+8FECF - 41 31 9C 94 C02DC900 - XOR [R12+RDX*4+00C92DC0],EBX
		dmc3.exe+8FED7
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			push_rax,
			mov_rcx_rdi,
			call,
			mov_rcx_rax,
			pop_rax,
			0x31, 0x9C, 0x91, 0x00, 0x00, 0x00, 0x00, // xor [rcx+rdx*4+0000B8C0],ebx
			pop_rcx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 5), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0x11) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x8FFA0);
		auto jumpAddr = (appBaseAddr + 0x8FFA8);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+8FFA0 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+8FFA8
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x8FFCA);
		auto jumpAddr = (appBaseAddr + 0x8FFD2);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+8FFCA - 41 31 9C 94 C02DC900 - XOR [R12+RDX*4+00C92DC0],EBX
		dmc3.exe+8FFD2
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			push_rax,
			mov_rcx_rdi,
			call,
			mov_rcx_rax,
			pop_rax,
			0x31, 0x9C, 0x91, 0x00, 0x00, 0x00, 0x00, // xor [rcx+rdx*4+0000B8C0],ebx
			pop_rcx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 5), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0x11) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x9014C);
		auto jumpAddr = (appBaseAddr + 0x90154);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+9014C - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+90154
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x90172);
		auto jumpAddr = (appBaseAddr + 0x9017A);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+90172 - 41 31 9C 94 C02DC900 - XOR [R12+RDX*4+00C92DC0],EBX
		dmc3.exe+9017A
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			push_rax,
			mov_rcx_rdi,
			call,
			mov_rcx_rax,
			pop_rax,
			0x31, 0x9C, 0x91, 0x00, 0x00, 0x00, 0x00, // xor [rcx+rdx*4+0000B8C0],ebx
			pop_rcx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 5), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0x11) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x9021F);
		auto jumpAddr = (appBaseAddr + 0x90227);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+9021F - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+90227
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x90245);
		auto jumpAddr = (appBaseAddr + 0x9024D);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+90245 - 41 31 9C 94 C02DC900 - XOR [R12+RDX*4+00C92DC0],EBX
		dmc3.exe+9024D
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			push_rax,
			mov_rcx_rdi,
			call,
			mov_rcx_rax,
			pop_rax,
			0x31, 0x9C, 0x91, 0x00, 0x00, 0x00, 0x00, // xor [rcx+rdx*4+0000B8C0],ebx
			pop_rcx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 5), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0x11) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x902F2);
		auto jumpAddr = (appBaseAddr + 0x902FA);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+902F2 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+902FA
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x90318);
		auto jumpAddr = (appBaseAddr + 0x90320);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+90318 - 41 31 9C 94 C02DC900 - XOR [R12+RDX*4+00C92DC0],EBX
		dmc3.exe+90320
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			push_rax,
			mov_rcx_rdi,
			call,
			mov_rcx_rax,
			pop_rax,
			0x31, 0x9C, 0x91, 0x00, 0x00, 0x00, 0x00, // xor [rcx+rdx*4+0000B8C0],ebx
			pop_rcx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 5), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0x11) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x9044F);
		auto jumpAddr = (appBaseAddr + 0x90457);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+9044F - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+90457
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x9047F);
		auto jumpAddr = (appBaseAddr + 0x90487);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+9047F - 41 31 9C 94 C02DC900 - XOR [R12+RDX*4+00C92DC0],EBX
		dmc3.exe+90487
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			push_rax,
			mov_rcx_rdi,
			call,
			mov_rcx_rax,
			pop_rax,
			0x31, 0x9C, 0x91, 0x00, 0x00, 0x00, 0x00, // xor [rcx+rdx*4+0000B8C0],ebx
			pop_rcx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 5), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0x11) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x90504);
		auto jumpAddr = (appBaseAddr + 0x9050C);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+90504 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+9050C
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x90534);
		auto jumpAddr = (appBaseAddr + 0x9053C);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+90534 - 41 31 9C 94 C02DC900 - XOR [R12+RDX*4+00C92DC0],EBX
		dmc3.exe+9053C
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			push_rax,
			mov_rcx_rdi,
			call,
			mov_rcx_rax,
			pop_rax,
			0x31, 0x9C, 0x91, 0x00, 0x00, 0x00, 0x00, // xor [rcx+rdx*4+0000B8C0],ebx
			pop_rcx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 5), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0x11) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x9065D);
		auto jumpAddr = (appBaseAddr + 0x90665);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+9065D - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+90665
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x90846);
		auto jumpAddr = (appBaseAddr + 0x9084E);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+90846 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+9084E
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x9086C);
		auto jumpAddr = (appBaseAddr + 0x90874);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+9086C - 41 31 9C 94 C02DC900 - XOR [R12+RDX*4+00C92DC0],EBX
		dmc3.exe+90874
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			push_rax,
			mov_rcx_rdi,
			call,
			mov_rcx_rax,
			pop_rax,
			0x31, 0x9C, 0x91, 0x00, 0x00, 0x00, 0x00, // xor [rcx+rdx*4+0000B8C0],ebx
			pop_rcx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 5), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0x11) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x909F9);
		auto jumpAddr = (appBaseAddr + 0x90A01);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+909F9 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+90A01
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x90A29);
		auto jumpAddr = (appBaseAddr + 0x90A31);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+90A29 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+90A31
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x90A55);
		auto jumpAddr = (appBaseAddr + 0x90A5D);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+90A55 - 43 31 9C 84 C02DC900 - XOR [R12+R8*4+00C92DC0],EBX
		dmc3.exe+90A5D
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			push_rax,
			mov_rcx_rdi,
			call,
			mov_rcx_rax,
			pop_rax,
			0x42, 0x31, 0x9C, 0x81, 0x00, 0x00, 0x00, 0x00, // xor [rcx+r8*4+0000B8C0],ebx
			pop_rcx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 5), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0x12) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x90D21);
		auto jumpAddr = (appBaseAddr + 0x90D29);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+90D21 - 41 8B 84 91 C02DC900 - MOV EAX,[R9+RDX*4+00C92DC0]
		dmc3.exe+90D29
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x90D4F);
		auto jumpAddr = (appBaseAddr + 0x90D57);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+90D4F - 41 31 84 91 C02DC900 - XOR [R9+RDX*4+00C92DC0],EAX
		dmc3.exe+90D57
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			push_rax,
			mov_rcx_rdi,
			call,
			mov_rcx_rax,
			pop_rax,
			0x31, 0x84, 0x91, 0x00, 0x00, 0x00, 0x00, // xor [rcx+rdx*4+0000B8C0],eax
			pop_rcx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 5), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0x11) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x90E2D);
		auto jumpAddr = (appBaseAddr + 0x90E35);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+90E2D - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+90E35
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x90E5C);
		auto jumpAddr = (appBaseAddr + 0x90E64);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+90E5C - 41 31 9C 94 C02DC900 - XOR [R12+RDX*4+00C92DC0],EBX
		dmc3.exe+90E64
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			push_rax,
			mov_rcx_rdi,
			call,
			mov_rcx_rax,
			pop_rax,
			0x31, 0x9C, 0x91, 0x00, 0x00, 0x00, 0x00, // xor [rcx+rdx*4+0000B8C0],ebx
			pop_rcx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 5), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0x11) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x90F3A);
		auto jumpAddr = (appBaseAddr + 0x90F42);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+90F3A - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+90F42
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x90F70);
		auto jumpAddr = (appBaseAddr + 0x90F78);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+90F70 - 41 31 84 94 C02DC900 - XOR [R12+RDX*4+00C92DC0],EAX
		dmc3.exe+90F78
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			push_rax,
			mov_rcx_rdi,
			call,
			mov_rcx_rax,
			pop_rax,
			0x31, 0x84, 0x91, 0x00, 0x00, 0x00, 0x00, // xor [rcx+rdx*4+0000B8C0],eax
			pop_rcx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 5), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0x11) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x91021);
		auto jumpAddr = (appBaseAddr + 0x91029);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+91021 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+91029
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x91076);
		auto jumpAddr = (appBaseAddr + 0x9107E);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+91076 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+9107E
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x910F3);
		auto jumpAddr = (appBaseAddr + 0x910FB);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+910F3 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+910FB
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x91126);
		auto jumpAddr = (appBaseAddr + 0x9112E);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+91126 - 41 31 9C 94 C02DC900 - XOR [R12+RDX*4+00C92DC0],EBX
		dmc3.exe+9112E
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			push_rax,
			mov_rcx_rdi,
			call,
			mov_rcx_rax,
			pop_rax,
			0x31, 0x9C, 0x91, 0x00, 0x00, 0x00, 0x00, // xor [rcx+rdx*4+0000B8C0],ebx
			pop_rcx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 5), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0x11) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x911B2);
		auto jumpAddr = (appBaseAddr + 0x911BA);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+911B2 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+911BA
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x91217);
		auto jumpAddr = (appBaseAddr + 0x9121F);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+91217 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+9121F
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x91266);
		auto jumpAddr = (appBaseAddr + 0x9126E);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+91266 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+9126E
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x912D5);
		auto jumpAddr = (appBaseAddr + 0x912DD);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+912D5 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+912DD
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x912FB);
		auto jumpAddr = (appBaseAddr + 0x91303);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+912FB - 41 31 9C 94 C02DC900 - XOR [R12+RDX*4+00C92DC0],EBX
		dmc3.exe+91303
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			push_rax,
			mov_rcx_rdi,
			call,
			mov_rcx_rax,
			pop_rax,
			0x31, 0x9C, 0x91, 0x00, 0x00, 0x00, 0x00, // xor [rcx+rdx*4+0000B8C0],ebx
			pop_rcx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 5), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0x11) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x91351);
		auto jumpAddr = (appBaseAddr + 0x91359);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+91351 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+91359
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x913A0);
		auto jumpAddr = (appBaseAddr + 0x913A8);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+913A0 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+913A8
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x913EF);
		auto jumpAddr = (appBaseAddr + 0x913F7);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+913EF - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+913F7
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x91457);
		auto jumpAddr = (appBaseAddr + 0x9145F);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+91457 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+9145F
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x914A0);
		auto jumpAddr = (appBaseAddr + 0x914A8);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+914A0 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+914A8
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x9150F);
		auto jumpAddr = (appBaseAddr + 0x91517);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+9150F - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+91517
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x91535);
		auto jumpAddr = (appBaseAddr + 0x9153D);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+91535 - 41 31 9C 94 C02DC900 - XOR [R12+RDX*4+00C92DC0],EBX
		dmc3.exe+9153D
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			push_rax,
			mov_rcx_rdi,
			call,
			mov_rcx_rax,
			pop_rax,
			0x31, 0x9C, 0x91, 0x00, 0x00, 0x00, 0x00, // xor [rcx+rdx*4+0000B8C0],ebx
			pop_rcx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 5), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0x11) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x9159B);
		auto jumpAddr = (appBaseAddr + 0x915A3);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+9159B - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+915A3
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x915E7);
		auto jumpAddr = (appBaseAddr + 0x915EF);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+915E7 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+915EF
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x9161C);
		auto jumpAddr = (appBaseAddr + 0x91624);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+9161C - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+91624
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x916F6);
		auto jumpAddr = (appBaseAddr + 0x916FE);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+916F6 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+916FE
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x9171F);
		auto jumpAddr = (appBaseAddr + 0x91727);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+9171F - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+91727
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x9174B);
		auto jumpAddr = (appBaseAddr + 0x91753);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+9174B - 41 31 9C 94 C02DC900 - XOR [R12+RDX*4+00C92DC0],EBX
		dmc3.exe+91753
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			push_rax,
			mov_rcx_rdi,
			call,
			mov_rcx_rax,
			pop_rax,
			0x31, 0x9C, 0x91, 0x00, 0x00, 0x00, 0x00, // xor [rcx+rdx*4+0000B8C0],ebx
			pop_rcx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 5), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0x11) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x917CF);
		auto jumpAddr = (appBaseAddr + 0x917D7);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+917CF - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+917D7
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x917FB);
		auto jumpAddr = (appBaseAddr + 0x91803);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+917FB - 41 31 9C 94 C02DC900 - XOR [R12+RDX*4+00C92DC0],EBX
		dmc3.exe+91803
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			push_rax,
			mov_rcx_rdi,
			call,
			mov_rcx_rax,
			pop_rax,
			0x31, 0x9C, 0x91, 0x00, 0x00, 0x00, 0x00, // xor [rcx+rdx*4+0000B8C0],ebx
			pop_rcx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 5), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0x11) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x91848);
		auto jumpAddr = (appBaseAddr + 0x91850);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+91848 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+91850
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x91874);
		auto jumpAddr = (appBaseAddr + 0x9187C);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+91874 - 41 31 9C 94 C02DC900 - XOR [R12+RDX*4+00C92DC0],EBX
		dmc3.exe+9187C
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			push_rax,
			mov_rcx_rdi,
			call,
			mov_rcx_rax,
			pop_rax,
			0x31, 0x9C, 0x91, 0x00, 0x00, 0x00, 0x00, // xor [rcx+rdx*4+0000B8C0],ebx
			pop_rcx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 5), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0x11) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x918A7);
		auto jumpAddr = (appBaseAddr + 0x918AF);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+918A7 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+918AF
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x918D3);
		auto jumpAddr = (appBaseAddr + 0x918DB);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+918D3 - 41 31 9C 94 C02DC900 - XOR [R12+RDX*4+00C92DC0],EBX
		dmc3.exe+918DB
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			push_rax,
			mov_rcx_rdi,
			call,
			mov_rcx_rax,
			pop_rax,
			0x31, 0x9C, 0x91, 0x00, 0x00, 0x00, 0x00, // xor [rcx+rdx*4+0000B8C0],ebx
			pop_rcx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 5), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0x11) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x9190A);
		auto jumpAddr = (appBaseAddr + 0x91912);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+9190A - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+91912
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x9193C);
		auto jumpAddr = (appBaseAddr + 0x91944);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+9193C - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+91944
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x91995);
		auto jumpAddr = (appBaseAddr + 0x9199D);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+91995 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+9199D
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x919C5);
		auto jumpAddr = (appBaseAddr + 0x919CD);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+919C5 - 41 31 9C 94 C02DC900 - XOR [R12+RDX*4+00C92DC0],EBX
		dmc3.exe+919CD
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			push_rax,
			mov_rcx_rdi,
			call,
			mov_rcx_rax,
			pop_rax,
			0x31, 0x9C, 0x91, 0x00, 0x00, 0x00, 0x00, // xor [rcx+rdx*4+0000B8C0],ebx
			pop_rcx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 5), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0x11) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x91AB9);
		auto jumpAddr = (appBaseAddr + 0x91AC1);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+91AB9 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+91AC1
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x91B05);
		auto jumpAddr = (appBaseAddr + 0x91B0D);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+91B05 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+91B0D
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x91B50);
		auto jumpAddr = (appBaseAddr + 0x91B58);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+91B50 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+91B58
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x91B86);
		auto jumpAddr = (appBaseAddr + 0x91B8E);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+91B86 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+91B8E
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x91C75);
		auto jumpAddr = (appBaseAddr + 0x91C7D);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+91C75 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+91C7D
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x91D32);
		auto jumpAddr = (appBaseAddr + 0x91D3A);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+91D32 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+91D3A
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x91DD3);
		auto jumpAddr = (appBaseAddr + 0x91DDB);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+91DD3 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+91DDB
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x91DF8);
		auto jumpAddr = (appBaseAddr + 0x91E00);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+91DF8 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+91E00
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x91E24);
		auto jumpAddr = (appBaseAddr + 0x91E2C);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+91E24 - 41 31 9C 94 C02DC900 - XOR [R12+RDX*4+00C92DC0],EBX
		dmc3.exe+91E2C
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			push_rax,
			mov_rcx_rdi,
			call,
			mov_rcx_rax,
			pop_rax,
			0x31, 0x9C, 0x91, 0x00, 0x00, 0x00, 0x00, // xor [rcx+rdx*4+0000B8C0],ebx
			pop_rcx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 5), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0x11) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x91E73);
		auto jumpAddr = (appBaseAddr + 0x91E7B);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+91E73 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+91E7B
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x91ED4);
		auto jumpAddr = (appBaseAddr + 0x91EDC);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+91ED4 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+91EDC
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x91F0F);
		auto jumpAddr = (appBaseAddr + 0x91F17);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+91F0F - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+91F17
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x91F4F);
		auto jumpAddr = (appBaseAddr + 0x91F57);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+91F4F - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+91F57
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x91FA1);
		auto jumpAddr = (appBaseAddr + 0x91FA9);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+91FA1 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+91FA9
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x91FDF);
		auto jumpAddr = (appBaseAddr + 0x91FE7);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+91FDF - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+91FE7
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x92020);
		auto jumpAddr = (appBaseAddr + 0x92028);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+92020 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+92028
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x9207E);
		auto jumpAddr = (appBaseAddr + 0x92086);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+9207E - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+92086
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x920C9);
		auto jumpAddr = (appBaseAddr + 0x920D1);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+920C9 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+920D1
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x920FE);
		auto jumpAddr = (appBaseAddr + 0x92106);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+920FE - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+92106
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x9218A);
		auto jumpAddr = (appBaseAddr + 0x92192);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+9218A - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+92192
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x921EC);
		auto jumpAddr = (appBaseAddr + 0x921F4);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+921EC - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+921F4
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x92215);
		auto jumpAddr = (appBaseAddr + 0x9221D);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+92215 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+9221D
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x92245);
		auto jumpAddr = (appBaseAddr + 0x9224D);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+92245 - 41 31 9C 94 C02DC900 - XOR [R12+RDX*4+00C92DC0],EBX
		dmc3.exe+9224D
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			push_rax,
			mov_rcx_rdi,
			call,
			mov_rcx_rax,
			pop_rax,
			0x31, 0x9C, 0x91, 0x00, 0x00, 0x00, 0x00, // xor [rcx+rdx*4+0000B8C0],ebx
			pop_rcx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 5), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0x11) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x9232F);
		auto jumpAddr = (appBaseAddr + 0x92337);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+9232F - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+92337
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x92370);
		auto jumpAddr = (appBaseAddr + 0x92378);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+92370 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+92378
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x923B1);
		auto jumpAddr = (appBaseAddr + 0x923B9);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+923B1 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+923B9
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x923F2);
		auto jumpAddr = (appBaseAddr + 0x923FA);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+923F2 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+923FA
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x9244D);
		auto jumpAddr = (appBaseAddr + 0x92455);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+9244D - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+92455
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x9247D);
		auto jumpAddr = (appBaseAddr + 0x92485);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+9247D - 41 31 9C 94 C02DC900 - XOR [R12+RDX*4+00C92DC0],EBX
		dmc3.exe+92485
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			push_rax,
			mov_rcx_rdi,
			call,
			mov_rcx_rax,
			pop_rax,
			0x31, 0x9C, 0x91, 0x00, 0x00, 0x00, 0x00, // xor [rcx+rdx*4+0000B8C0],ebx
			pop_rcx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 5), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0x11) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x92598);
		auto jumpAddr = (appBaseAddr + 0x925A0);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+92598 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+925A0
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x925D9);
		auto jumpAddr = (appBaseAddr + 0x925E1);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+925D9 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+925E1
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x9261A);
		auto jumpAddr = (appBaseAddr + 0x92622);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+9261A - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+92622
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x92671);
		auto jumpAddr = (appBaseAddr + 0x92679);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+92671 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+92679
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x926B2);
		auto jumpAddr = (appBaseAddr + 0x926BA);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+926B2 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+926BA
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x9271F);
		auto jumpAddr = (appBaseAddr + 0x92727);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+9271F - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+92727
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x92760);
		auto jumpAddr = (appBaseAddr + 0x92768);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+92760 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+92768
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x9278C);
		auto jumpAddr = (appBaseAddr + 0x92794);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+9278C - 41 31 9C 94 C02DC900 - XOR [R12+RDX*4+00C92DC0],EBX
		dmc3.exe+92794
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			push_rax,
			mov_rcx_rdi,
			call,
			mov_rcx_rax,
			pop_rax,
			0x31, 0x9C, 0x91, 0x00, 0x00, 0x00, 0x00, // xor [rcx+rdx*4+0000B8C0],ebx
			pop_rcx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 5), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0x11) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x927CD);
		auto jumpAddr = (appBaseAddr + 0x927D5);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+927CD - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+927D5
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x92802);
		auto jumpAddr = (appBaseAddr + 0x9280A);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+92802 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+9280A
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x9286D);
		auto jumpAddr = (appBaseAddr + 0x92875);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+9286D - 41 31 9C 94 C02DC900 - XOR [R12+RDX*4+00C92DC0],EBX
		dmc3.exe+92875
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			push_rax,
			mov_rcx_rdi,
			call,
			mov_rcx_rax,
			pop_rax,
			0x31, 0x9C, 0x91, 0x00, 0x00, 0x00, 0x00, // xor [rcx+rdx*4+0000B8C0],ebx
			pop_rcx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 5), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0x11) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x9288F);
		auto jumpAddr = (appBaseAddr + 0x92897);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+9288F - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+92897
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x928D8);
		auto jumpAddr = (appBaseAddr + 0x928E0);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+928D8 - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+928E0
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x9290D);
		auto jumpAddr = (appBaseAddr + 0x92915);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+9290D - 41 8B 84 94 C02DC900 - MOV EAX,[R12+RDX*4+00C92DC0]
		dmc3.exe+92915
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x92933);
		auto jumpAddr = (appBaseAddr + 0x9293B);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+92933 - 41 31 9C 94 C02DC900 - XOR [R12+RDX*4+00C92DC0],EBX
		dmc3.exe+9293B
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			push_rax,
			mov_rcx_rdi,
			call,
			mov_rcx_rax,
			pop_rax,
			0x31, 0x9C, 0x91, 0x00, 0x00, 0x00, 0x00, // xor [rcx+rdx*4+0000B8C0],ebx
			pop_rcx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 5), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0x11) = offsetof(PlayerActorData, newEffectIndices[0]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x8DC62);
		auto jumpAddr = (appBaseAddr + 0x8DC69);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+8DC62 - 8B 84 96 D82DC900 - MOV EAX,[RSI+RDX*4+00C92DD8]
		dmc3.exe+8DC69
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rbx,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[6]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x8DC87);
		auto jumpAddr = (appBaseAddr + 0x8DC8E);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+8DC87 - 31 84 96 D82DC900 - XOR [RSI+RDX*4+00C92DD8],EAX
		dmc3.exe+8DC8E
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			push_rax,
			mov_rcx_rbx,
			call,
			mov_rcx_rax,
			pop_rax,
			0x31, 0x84, 0x91, 0x00, 0x00, 0x00, 0x00, // xor [rcx+rdx*4+0000B8C0],eax
			pop_rcx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 5), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0x11) = offsetof(PlayerActorData, newEffectIndices[6]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x8F7EF);
		auto jumpAddr = (appBaseAddr + 0x8F7F7);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+8F7EF - 41 8B 84 94 D82DC900 - MOV EAX,[R12+RDX*4+00C92DD8]
		dmc3.exe+8F7F7
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			mov_rcx_rdi,
			call,
			pop_rcx,
			0x8B, 0x84, 0x90, 0x00, 0x00, 0x00, 0x00, // mov eax,[rax+rdx*4+0000B8C0]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0xD) = offsetof(PlayerActorData, newEffectIndices[6]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr     = (appBaseAddr + 0x8F815);
		auto jumpAddr = (appBaseAddr + 0x8F81D);
		constexpr uint32 size = 8;
		/*
		dmc3.exe+8F815 - 41 31 9C 94 D82DC900 - XOR [R12+RDX*4+00C92DD8],EBX
		dmc3.exe+8F81D
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rcx,
			push_rax,
			mov_rcx_rdi,
			call,
			mov_rcx_rax,
			pop_rax,
			0x31, 0x9C, 0x91, 0x00, 0x00, 0x00, 0x00, // xor [rcx+rdx*4+0000B8C0],ebx
			pop_rcx,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, false, sizeof(sect0));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			WriteCall((func.sect0 + 5), GetPlayerActorBaseAddressByEffectData);
			*reinterpret_cast<uint32 *>(func.sect0 + 0x11) = offsetof(PlayerActorData, newEffectIndices[6]);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x1E0B1F);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+1E0B1F - 81 0D 9722AB00 00000080 - OR [7FF6784E2DC0],80000000
		dmc3.exe+1E0B29
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, // or [rbx+0000B8C0],80000000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[0]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x1EE0ED);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+1EE0ED - 81 0D C94CAA00 00000080 - OR [7FF6784E2DC0],80000000
		dmc3.exe+1EE0F7
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, // or [rbx+0000B8C0],80000000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[0]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x1F1712);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+1F1712 - 81 0D A416AA00 00000010 - OR [7FF6784E2DC0],10000000
		dmc3.exe+1F171C
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, // or [rbx+0000B8C0],10000000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[0]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x1F2C26);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+1F2C26 - 81 0D 9001AA00 00000080 - OR [7FF6784E2DC0],80000000
		dmc3.exe+1F2C30
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, // or [rbx+0000B8C0],80000000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[0]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x1F2D56);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+1F2D56 - 81 0D 6000AA00 00000080 - OR [7FF6784E2DC0],80000000
		dmc3.exe+1F2D60
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, // or [rbx+0000B8C0],80000000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[0]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x1F31CC);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+1F31CC - 81 0D EAFBA900 00000080 - OR [7FF6784E2DC0],80000000
		dmc3.exe+1F31D6
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, // or [rbx+0000B8C0],80000000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[0]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x1F57D0);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+1F57D0 - 81 0D E6D5A900 00000020 - OR [7FF6784E2DC0],20000000
		dmc3.exe+1F57DA
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, // or [rsi+0000B8C0],20000000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[0]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x1F5E47);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+1F5E47 - 81 0D 6FCFA900 00000020 - OR [7FF6784E2DC0],20000000
		dmc3.exe+1F5E51
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, // or [rsi+0000B8C0],20000000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[0]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x1F6C21);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+1F6C21 - 81 0D 95C1A900 00000010 - OR [7FF6784E2DC0],10000000
		dmc3.exe+1F6C2B
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, // or [rbx+0000B8C0],10000000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[0]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x20115E);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+20115E - 81 0D 581CA900 00400000 - OR [7FF6784E2DC0],00004000
		dmc3.exe+201168
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, // or [rbx+0000B8C0],00004000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[0]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x205846);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+205846 - 81 0D 70D5A800 00100000 - OR [7FF6784E2DC0],00001000
		dmc3.exe+205850
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, // or [rdi+0000B8C0],00001000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[0]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x2058FE);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+2058FE - 81 0D B8D4A800 00100000 - OR [7FF6784E2DC0],00001000
		dmc3.exe+205908
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, // or [rdi+0000B8C0],00001000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[0]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x205AC7);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+205AC7 - 81 0D EFD2A800 00200000 - OR [7FF6784E2DC0],00002000
		dmc3.exe+205AD1
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, // or [rdi+0000B8C0],00002000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[0]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x2091BD);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+2091BD - 81 0D F99BA800 00080000 - OR [7FF6784E2DC0],00000800
		dmc3.exe+2091C7
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, // or [rdi+0000B8C0],00000800
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[0]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x2092A7);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+2092A7 - 81 0D 0F9BA800 00080000 - OR [7FF6784E2DC0],00000800
		dmc3.exe+2092B1
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, // or [rdi+0000B8C0],00000800
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[0]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x20A29A);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+20A29A - 81 0D 1C8BA800 00000400 - OR [7FF6784E2DC0],00040000
		dmc3.exe+20A2A4
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, // or [rbx+0000B8C0],00040000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[0]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x20AA0E);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+20AA0E - 81 0D A883A800 00000400 - OR [7FF6784E2DC0],00040000
		dmc3.exe+20AA18
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, // or [rdi+0000B8C0],00040000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[0]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x20AC23);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+20AC23 - 81 0D 9381A800 00000400 - OR [7FF6784E2DC0],00040000
		dmc3.exe+20AC2D
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, // or [rdi+0000B8C0],00040000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[0]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x20ACAD);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+20ACAD - 81 0D 0981A800 00000400 - OR [7FF6784E2DC0],00040000
		dmc3.exe+20ACB7
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, // or [rdi+0000B8C0],00040000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[0]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x20B34B);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+20B34B - 81 0D 6B7AA800 00800000 - OR [7FF6784E2DC0],00008000
		dmc3.exe+20B355
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, // or [rbx+0000B8C0],00008000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[0]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x20B84C);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+20B84C - 81 0D 6A75A800 00800000 - OR [7FF6784E2DC0],00008000
		dmc3.exe+20B856
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, // or [rbx+0000B8C0],00008000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[0]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x20E921);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+20E921 - 81 0D 9544A800 00000008 - OR [7FF6784E2DC0],08000000
		dmc3.exe+20E92B
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, // or [rdi+0000B8C0],08000000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[0]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x20F09E);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+20F09E - 81 0D 183DA800 00000008 - OR [7FF6784E2DC0],08000000
		dmc3.exe+20F0A8
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, // or [rdi+0000B8C0],08000000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[0]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x20FBEE);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+20FBEE - 81 0D C831A800 00400000 - OR [7FF6784E2DC0],00004000
		dmc3.exe+20FBF8
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, // or [rbx+0000B8C0],00004000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[0]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x20FEAC);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+20FEAC - 81 0D 0A2FA800 00000200 - OR [7FF6784E2DC0],00020000
		dmc3.exe+20FEB6
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, // or [rbx+0000B8C0],00020000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[0]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x2107BE);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+2107BE - 81 0D F825A800 00040000 - OR [7FF6784E2DC0],00000400
		dmc3.exe+2107C8
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, // or [rbx+0000B8C0],00000400
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[0]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x210881);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+210881 - 81 0D 3525A800 00040000 - OR [7FF6784E2DC0],00000400
		dmc3.exe+21088B
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, // or [rbx+0000B8C0],00000400
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[0]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x211937);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+211937 - 81 0D 7F14A800 00040000 - OR [7FF6784E2DC0],00000400
		dmc3.exe+211941
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, // or [rbx+0000B8C0],00000400
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[0]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x211A99);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+211A99 - 81 0D 1D13A800 00040000 - OR [7FF6784E2DC0],00000400
		dmc3.exe+211AA3
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, // or [rbx+0000B8C0],00000400
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[0]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x215D50);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+215D50 - 81 0D 66D0A700 00000040 - OR [7FF6784E2DC0],40000000
		dmc3.exe+215D5A
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, // or [rdi+0000B8C0],40000000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[0]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x215F9C);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+215F9C - 81 0D 1ACEA700 00000040 - OR [7FF6784E2DC0],40000000
		dmc3.exe+215FA6
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, // or [rdi+0000B8C0],40000000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[0]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x21622B);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+21622B - 81 0D 8BCBA700 0000E001 - OR [7FF6784E2DC0],01E00000
		dmc3.exe+216235
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x01, // or [rdi+0000B8C0],01E00000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[0]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x216434);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+216434 - 81 0D 82C9A700 00000006 - OR [7FF6784E2DC0],06000000
		dmc3.exe+21643E
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, // or [rdi+0000B8C0],06000000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[0]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x1E14C4);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+1E14C4 - 81 0D F618AB00 00000008 - OR [7FF6784E2DC4],08000000
		dmc3.exe+1E14CE
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, // or [rbx+0000B8C0],08000000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[1]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x1F7CD2);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+1F7CD2 - 81 0D E8B0A900 00000008 - OR [7FF6784E2DC4],08000000
		dmc3.exe+1F7CDC
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, // or [rbx+0000B8C0],08000000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[1]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x1F950C);
		constexpr uint32 size = 6;
		/*
		dmc3.exe+1F950C - 8B 05 B298A900 - MOV EAX,[7FF6784E2DC4]
		dmc3.exe+1F9512
		*/

		constexpr byte8 sect0[] =
		{
			0x8B, 0x83, 0x00, 0x00, 0x00, 0x00, // mov eax,[rbx+0000B8C0]
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[1]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x1F9526);
		constexpr uint32 size = 6;
		/*
		dmc3.exe+1F9526 - 89 05 9898A900 - MOV [7FF6784E2DC4],EAX
		dmc3.exe+1F952C
		*/

		constexpr byte8 sect0[] =
		{
			0x89, 0x83, 0x00, 0x00, 0x00, 0x00, // mov [rbx+0000B8C0],eax
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[1]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x1F9542);
		constexpr uint32 size = 6;
		/*
		dmc3.exe+1F9542 - 8B 05 7C98A900 - MOV EAX,[7FF6784E2DC4]
		dmc3.exe+1F9548
		*/

		constexpr byte8 sect0[] =
		{
			0x8B, 0x83, 0x00, 0x00, 0x00, 0x00, // mov eax,[rbx+0000B8C0]
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[1]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x1F956C);
		constexpr uint32 size = 6;
		/*
		dmc3.exe+1F956C - 89 05 5298A900 - MOV [7FF6784E2DC4],EAX
		dmc3.exe+1F9572
		*/

		constexpr byte8 sect0[] =
		{
			0x89, 0x83, 0x00, 0x00, 0x00, 0x00, // mov [rbx+0000B8C0],eax
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[1]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x201513);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+201513 - 81 0D A718A900 00001000 - OR [7FF6784E2DC4],00100000
		dmc3.exe+20151D
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, // or [rbx+0000B8C0],00100000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[1]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x20222C);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+20222C - 81 0D 8E0BA900 00800000 - OR [7FF6784E2DC4],00008000
		dmc3.exe+202236
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, // or [rbx+0000B8C0],00008000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[1]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x2022EB);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+2022EB - 81 0D CF0AA900 00800000 - OR [7FF6784E2DC4],00008000
		dmc3.exe+2022F5
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, // or [rbx+0000B8C0],00008000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[1]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x2023AA);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+2023AA - 81 0D 100AA900 00800000 - OR [7FF6784E2DC4],00008000
		dmc3.exe+2023B4
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, // or [rbx+0000B8C0],00008000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[1]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x202517);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+202517 - 81 0D A308A900 00000100 - OR [7FF6784E2DC4],00010000
		dmc3.exe+202521
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, // or [rbx+0000B8C0],00010000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[1]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x2025DA);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+2025DA - 81 0D E007A900 00000100 - OR [7FF6784E2DC4],00010000
		dmc3.exe+2025E4
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, // or [rbx+0000B8C0],00010000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[1]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x2029E3);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+2029E3 - 81 0D D703A900 00000800 - OR [7FF6784E2DC4],00080000
		dmc3.exe+2029ED
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, // or [rbx+0000B8C0],00080000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[1]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x202AEC);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+202AEC - 81 0D CE02A900 00000800 - OR [7FF6784E2DC4],00080000
		dmc3.exe+202AF6
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, // or [rbx+0000B8C0],00080000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[1]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x20302B);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+20302B - 81 0D 8FFDA800 00000010 - OR [7FF6784E2DC4],10000000
		dmc3.exe+203035
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, // or [rbx+0000B8C0],10000000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[1]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x20364D);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+20364D - 81 0D 6DF7A800 00002000 - OR [7FF6784E2DC4],00200000
		dmc3.exe+203657
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, // or [rbx+0000B8C0],00200000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[1]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x204320);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+204320 - 81 0D 9AEAA800 00008000 - OR [7FF6784E2DC4],00800000
		dmc3.exe+20432A
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, // or [rbx+0000B8C0],00800000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[1]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x20436C);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+20436C - 81 0D 4EEAA800 00004000 - OR [7FF6784E2DC4],00400000
		dmc3.exe+204376
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, // or [rbx+0000B8C0],00400000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[1]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x20441E);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+20441E - 81 0D 9CE9A800 00004000 - OR [7FF6784E2DC4],00400000
		dmc3.exe+204428
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, // or [rbx+0000B8C0],00400000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[1]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x204840);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+204840 - 81 0D 7AE5A800 00000200 - OR [7FF6784E2DC4],00020000
		dmc3.exe+20484A
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, // or [rbx+0000B8C0],00020000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[1]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x209E7B);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+209E7B - 81 0D 3F8FA800 00040000 - OR [7FF6784E2DC4],00000400
		dmc3.exe+209E85
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, // or [rbx+0000B8C0],00000400
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[1]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x209F1D);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+209F1D - 81 0D 9D8EA800 00040000 - OR [7FF6784E2DC4],00000400
		dmc3.exe+209F27
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, // or [rbx+0000B8C0],00000400
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[1]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x20A195);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+20A195 - 81 0D 258CA800 00000080 - OR [7FF6784E2DC4],80000000
		dmc3.exe+20A19F
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, // or [rbx+0000B8C0],80000000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[1]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x20A2A4);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+20A2A4 - 81 0D 168BA800 00000001 - OR [7FF6784E2DC4],01000000
		dmc3.exe+20A2AE
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, // or [rbx+0000B8C0],01000000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[1]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x20A5B3);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+20A5B3 - 81 0D 0788A800 00100000 - OR [7FF6784E2DC4],00001000
		dmc3.exe+20A5BD
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, // or [rbx+0000B8C0],00001000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[1]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x20A601);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+20A601 - 81 0D B987A800 00080000 - OR [7FF6784E2DC4],00000800
		dmc3.exe+20A60B
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, // or [rbx+0000B8C0],00000800
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[1]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x20A740);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+20A740 - 81 0D 7A86A800 00080000 - OR [7FF6784E2DC4],00000800
		dmc3.exe+20A74A
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, // or [rbx+0000B8C0],00000800
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[1]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x20AED5);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+20AED5 - 81 0D E57EA800 00000400 - OR [7FF6784E2DC4],00040000
		dmc3.exe+20AEDF
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, // or [rbx+0000B8C0],00040000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[1]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x20AF98);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+20AF98 - 81 0D 227EA800 00000400 - OR [7FF6784E2DC4],00040000
		dmc3.exe+20AFA2
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, // or [rbx+0000B8C0],00040000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[1]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x20B0A2);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+20B0A2 - 81 0D 187DA800 00000002 - OR [7FF6784E2DC4],02000000
		dmc3.exe+20B0AC
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, // or [rbx+0000B8C0],02000000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[1]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x20B33F);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+20B33F - 81 0D 7B7AA800 00000020 - OR [7FF6784E2DC4],20000000
		dmc3.exe+20B349
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, // or [rbx+0000B8C0],20000000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[1]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x20B83F);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+20B83F - 81 0D 7B75A800 00000020 - OR [7FF6784E2DC4],20000000
		dmc3.exe+20B849
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, // or [rbx+0000B8C0],20000000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[1]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x20C73F);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+20C73F - 81 0D 7B66A800 00000004 - OR [7FF6784E2DC4],04000000
		dmc3.exe+20C749
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, // or [rdi+0000B8C0],04000000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[1]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x20E10D);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+20E10D - 81 0D AD4CA800 00020000 - OR [7FF6784E2DC4],00000200
		dmc3.exe+20E117
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, // or [rbx+0000B8C0],00000200
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[1]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x20F253);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+20F253 - 81 0D 673BA800 00000040 - OR [7FF6784E2DC4],40000000
		dmc3.exe+20F25D
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, // or [rdi+0000B8C0],40000000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[1]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x20F30A);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+20F30A - 81 0D B03AA800 00000040 - OR [7FF6784E2DC4],40000000
		dmc3.exe+20F314
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, // or [rdi+0000B8C0],40000000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[1]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x2100E0);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+2100E0 - 83 0D DD2CA800 20 - OR DWORD PTR [7FF6784E2DC4],20
		dmc3.exe+2100E7
		*/

		constexpr byte8 sect0[] =
		{
			0x83, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x20, // or dword ptr [rdi+0000B8C0],20
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[1]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x8CBF0);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+8CBF0 - 81 0D CE61C000 00004000 - OR [7FF6784E2DC8],00400000
		dmc3.exe+8CBFA
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, // or [rbx+0000B8C0],00400000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[2]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x8CC7B);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+8CC7B - 81 0D 4361C000 00008000 - OR [7FF6784E2DC8],00800000
		dmc3.exe+8CC85
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, // or [rbx+0000B8C0],00800000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[2]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x8CC8E);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+8CC8E - 81 0D 3061C000 00008000 - OR [7FF6784E2DC8],00800000
		dmc3.exe+8CC98
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, // or [rbx+0000B8C0],00800000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[2]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x1F9512);
		constexpr uint32 size = 6;
		/*
		dmc3.exe+1F9512 - 8B 0D B098A900 - MOV ECX,[7FF6784E2DC8]
		dmc3.exe+1F9518
		*/

		constexpr byte8 sect0[] =
		{
			0x8B, 0x8B, 0x00, 0x00, 0x00, 0x00, // mov ecx,[rbx+0000B8C0]
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[2]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x1F9536);
		constexpr uint32 size = 6;
		/*
		dmc3.exe+1F9536 - 89 0D 8C98A900 - MOV [7FF6784E2DC8],ECX
		dmc3.exe+1F953C
		*/

		constexpr byte8 sect0[] =
		{
			0x89, 0x8B, 0x00, 0x00, 0x00, 0x00, // mov [rbx+0000B8C0],ecx
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[2]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x1F9548);
		constexpr uint32 size = 6;
		/*
		dmc3.exe+1F9548 - 8B 0D 7A98A900 - MOV ECX,[7FF6784E2DC8]
		dmc3.exe+1F954E
		*/

		constexpr byte8 sect0[] =
		{
			0x8B, 0x8B, 0x00, 0x00, 0x00, 0x00, // mov ecx,[rbx+0000B8C0]
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[2]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x1F9572);
		constexpr uint32 size = 6;
		/*
		dmc3.exe+1F9572 - 89 0D 5098A900 - MOV [7FF6784E2DC8],ECX
		dmc3.exe+1F9578
		*/

		constexpr byte8 sect0[] =
		{
			0x89, 0x8B, 0x00, 0x00, 0x00, 0x00, // mov [rbx+0000B8C0],ecx
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[2]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x1FED7B);
		constexpr uint32 size = 6;
		/*
		dmc3.exe+1FED7B - 8B 15 4740A900 - MOV EDX,[7FF6784E2DC8]
		dmc3.exe+1FED81
		*/

		constexpr byte8 sect0[] =
		{
			0x8B, 0x93, 0x00, 0x00, 0x00, 0x00, // mov edx,[rbx+0000B8C0]
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[2]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x1FED93);
		constexpr uint32 size = 6;
		/*
		dmc3.exe+1FED93 - 89 15 2F40A900 - MOV [7FF6784E2DC8],EDX
		dmc3.exe+1FED99
		*/

		constexpr byte8 sect0[] =
		{
			0x89, 0x93, 0x00, 0x00, 0x00, 0x00, // mov [rbx+0000B8C0],edx
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[2]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x1FFE52);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+1FFE52 - 81 0D 6C2FA900 00020000 - OR [7FF6784E2DC8],00000200
		dmc3.exe+1FFE5C
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, // or [rbx+0000B8C0],00000200
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[2]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x20181D);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+20181D - 81 0D A115A900 00000001 - OR [7FF6784E2DC8],01000000
		dmc3.exe+201827
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, // or [rdi+0000B8C0],01000000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[2]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x2019DF);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+2019DF - 81 0D DF13A900 00000001 - OR [7FF6784E2DC8],01000000
		dmc3.exe+2019E9
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, // or [rdi+0000B8C0],01000000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[2]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x203F83);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+203F83 - 81 0D 3BEEA800 00002000 - OR [7FF6784E2DC8],00200000
		dmc3.exe+203F8D
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, // or [rbx+0000B8C0],00200000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[2]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x209A16);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+209A16 - 81 0D A893A800 00040000 - OR [7FF6784E2DC8],00000400
		dmc3.exe+209A20
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, // or [rbx+0000B8C0],00000400
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[2]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x209C11);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+209C11 - 81 0D AD91A800 00001000 - OR [7FF6784E2DC8],00100000
		dmc3.exe+209C1B
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, // or [rbx+0000B8C0],00100000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[2]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x20A019);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+20A019 - 81 0D A58DA800 00000002 - OR [7FF6784E2DC8],02000000
		dmc3.exe+20A023
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, // or [rbx+0000B8C0],02000000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[2]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x20D73D);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+20D73D - 81 0D 8156A800 00000800 - OR [7FF6784E2DC8],00080000
		dmc3.exe+20D747
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, // or [rdi+0000B8C0],00080000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[2]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x20D858);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+20D858 - 81 0D 6655A800 00000800 - OR [7FF6784E2DC8],00080000
		dmc3.exe+20D862
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, // or [rbx+0000B8C0],00080000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[2]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x224C96);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+224C96 - 81 0D 28E1A600 00080000 - OR [7FF6784E2DC8],00000800
		dmc3.exe+224CA0
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, // or [rbx+0000B8C0],00000800
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[2]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x224CE7);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+224CE7 - 81 0D D7E0A600 00400000 - OR [7FF6784E2DC8],00004000
		dmc3.exe+224CF1
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, // or [rbx+0000B8C0],00004000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[2]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x224DE6);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+224DE6 - 81 0D D8DFA600 00080000 - OR [7FF6784E2DC8],00000800
		dmc3.exe+224DF0
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, // or [rbx+0000B8C0],00000800
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[2]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x224E37);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+224E37 - 81 0D 87DFA600 00800000 - OR [7FF6784E2DC8],00008000
		dmc3.exe+224E41
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, // or [rbx+0000B8C0],00008000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[2]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x224F36);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+224F36 - 81 0D 88DEA600 00080000 - OR [7FF6784E2DC8],00000800
		dmc3.exe+224F40
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, // or [rbx+0000B8C0],00000800
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[2]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x224F87);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+224F87 - 81 0D 37DEA600 00000100 - OR [7FF6784E2DC8],00010000
		dmc3.exe+224F91
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, // or [rbx+0000B8C0],00010000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[2]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x225142);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+225142 - 81 0D 7CDCA600 00200000 - OR [7FF6784E2DC8],00002000
		dmc3.exe+22514C
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, // or [rbx+0000B8C0],00002000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[2]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x2253F3);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+2253F3 - 81 0D CBD9A600 00080000 - OR [7FF6784E2DC8],00000800
		dmc3.exe+2253FD
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, // or [rbx+0000B8C0],00000800
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[2]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x225440);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+225440 - 81 0D 7ED9A600 00000100 - OR [7FF6784E2DC8],00010000
		dmc3.exe+22544A
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, // or [rbx+0000B8C0],00010000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[2]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x2254AC);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+2254AC - 81 0D 12D9A600 00800000 - OR [7FF6784E2DC8],00008000
		dmc3.exe+2254B6
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, // or [rbx+0000B8C0],00008000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[2]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x2255A3);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+2255A3 - 81 0D 1BD8A600 00100200 - OR [7FF6784E2DC8],00021000
		dmc3.exe+2255AD
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x02, 0x00, // or [rbx+0000B8C0],00021000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[2]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x8CC05);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+8CC05 - 81 0D BD61C000 00000040 - OR [7FF6784E2DCC],40000000
		dmc3.exe+8CC0F
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, // or [rbx+0000B8C0],40000000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[3]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x1E0B2B);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+1E0B2B - 81 0D 9722AB00 00000200 - OR [7FF6784E2DCC],00020000
		dmc3.exe+1E0B35
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, // or [rbx+0000B8C0],00020000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[3]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x1EE0F9);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+1EE0F9 - 81 0D C94CAA00 00000200 - OR [7FF6784E2DCC],00020000
		dmc3.exe+1EE103
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, // or [rbx+0000B8C0],00020000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[3]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x1F1721);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+1F1721 - 81 0D A116AA00 00200000 - OR [7FF6784E2DCC],00002000
		dmc3.exe+1F172B
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, // or [rbx+0000B8C0],00002000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[3]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x1F2C44);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+1F2C44 - 81 0D 7E01AA00 00000200 - OR [7FF6784E2DCC],00020000
		dmc3.exe+1F2C4E
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, // or [rbx+0000B8C0],00020000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[3]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x1F2D6C);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+1F2D6C - 81 0D 5600AA00 00000200 - OR [7FF6784E2DCC],00020000
		dmc3.exe+1F2D76
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, // or [rbx+0000B8C0],00020000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[3]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x1F31D8);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+1F31D8 - 81 0D EAFBA900 00000200 - OR [7FF6784E2DCC],00020000
		dmc3.exe+1F31E2
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, // or [rbx+0000B8C0],00020000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[3]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x1F57DC);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+1F57DC - 81 0D E6D5A900 00800000 - OR [7FF6784E2DCC],00008000
		dmc3.exe+1F57E6
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, // or [rsi+0000B8C0],00008000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[3]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x1F5E53);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+1F5E53 - 81 0D 6FCFA900 00800000 - OR [7FF6784E2DCC],00008000
		dmc3.exe+1F5E5D
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, // or [rsi+0000B8C0],00008000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[3]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x1FFE6B);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+1FFE6B - 81 0D 572FA900 00000010 - OR [7FF6784E2DCC],10000000
		dmc3.exe+1FFE75
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, // or [rbx+0000B8C0],10000000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[3]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x20116D);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+20116D - 83 0D 581CA900 10 - OR DWORD PTR [7FF6784E2DCC],10
		dmc3.exe+201174
		*/

		constexpr byte8 sect0[] =
		{
			0x83, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x10, // or dword ptr [rbx+0000B8C0],10
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[3]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x20151F);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+20151F - 81 0D A318A900 00008000 - OR [7FF6784E2DCC],00800000
		dmc3.exe+201529
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, // or [rbx+0000B8C0],00800000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[3]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x201836);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+201836 - 81 0D 8C15A900 00000080 - OR [7FF6784E2DCC],80000000
		dmc3.exe+201840
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, // or [rdi+0000B8C0],80000000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[3]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x2019EE);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+2019EE - 81 0D D413A900 00000080 - OR [7FF6784E2DCC],80000000
		dmc3.exe+2019F8
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, // or [rdi+0000B8C0],80000000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[3]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x20224A);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+20224A - 81 0D 780BA900 00000800 - OR [7FF6784E2DCC],00080000
		dmc3.exe+202254
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, // or [rbx+0000B8C0],00080000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[3]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x2022F7);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+2022F7 - 81 0D CB0AA900 00000800 - OR [7FF6784E2DCC],00080000
		dmc3.exe+202301
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, // or [rbx+0000B8C0],00080000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[3]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x2023C6);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+2023C6 - 81 0D FC09A900 00000800 - OR [7FF6784E2DCC],00080000
		dmc3.exe+2023D0
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, // or [rbx+0000B8C0],00080000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[3]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x202523);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+202523 - 81 0D 9F08A900 00001000 - OR [7FF6784E2DCC],00100000
		dmc3.exe+20252D
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, // or [rbx+0000B8C0],00100000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[3]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x2025E6);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+2025E6 - 81 0D DC07A900 00001000 - OR [7FF6784E2DCC],00100000
		dmc3.exe+2025F0
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, // or [rbx+0000B8C0],00100000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[3]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x2029FF);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+2029FF - 81 0D C303A900 00004000 - OR [7FF6784E2DCC],00400000
		dmc3.exe+202A09
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, // or [rbx+0000B8C0],00400000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[3]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x202AF8);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+202AF8 - 81 0D CA02A900 00004000 - OR [7FF6784E2DCC],00400000
		dmc3.exe+202B02
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, // or [rbx+0000B8C0],00400000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[3]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x203041);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+203041 - 81 0D 81FDA800 00000008 - OR [7FF6784E2DCC],08000000
		dmc3.exe+20304B
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, // or [rbx+0000B8C0],08000000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[3]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x20366E);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+20366E - 81 0D 54F7A800 00000001 - OR [7FF6784E2DCC],01000000
		dmc3.exe+203678
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, // or [rbx+0000B8C0],01000000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[3]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x203F8F);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+203F8F - 81 0D 33EEA800 00000020 - OR [7FF6784E2DCC],20000000
		dmc3.exe+203F99
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, // or [rbx+0000B8C0],20000000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[3]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x204335);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+204335 - 81 0D 8DEAA800 00000004 - OR [7FF6784E2DCC],04000000
		dmc3.exe+20433F
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, // or [rbx+0000B8C0],04000000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[3]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x204388);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+204388 - 81 0D 3AEAA800 00000002 - OR [7FF6784E2DCC],02000000
		dmc3.exe+204392
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, // or [rbx+0000B8C0],02000000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[3]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x20442A);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+20442A - 81 0D 98E9A800 00000002 - OR [7FF6784E2DCC],02000000
		dmc3.exe+204434
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, // or [rbx+0000B8C0],02000000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[3]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x20484C);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+20484C - 81 0D 76E5A800 00002000 - OR [7FF6784E2DCC],00200000
		dmc3.exe+204856
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, // or [rbx+0000B8C0],00200000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[3]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x205864);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+205864 - 83 0D 61D5A800 04 - OR DWORD PTR [7FF6784E2DCC],04
		dmc3.exe+20586B
		*/

		constexpr byte8 sect0[] =
		{
			0x83, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x04, // or dword ptr [rdi+0000B8C0],04
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[3]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x205913);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+205913 - 83 0D B2D4A800 04 - OR DWORD PTR [7FF6784E2DCC],04
		dmc3.exe+20591A
		*/

		constexpr byte8 sect0[] =
		{
			0x83, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x04, // or dword ptr [rdi+0000B8C0],04
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[3]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x205AD3);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+205AD3 - 83 0D F2D2A800 08 - OR DWORD PTR [7FF6784E2DCC],08
		dmc3.exe+205ADA
		*/

		constexpr byte8 sect0[] =
		{
			0x83, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x08, // or dword ptr [rdi+0000B8C0],08
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[3]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x2091E0);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+2091E0 - 83 0D E59BA800 02 - OR DWORD PTR [7FF6784E2DCC],02
		dmc3.exe+2091E7
		*/

		constexpr byte8 sect0[] =
		{
			0x83, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x02, // or dword ptr [rdi+0000B8C0],02
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[3]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x2092B6);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+2092B6 - 83 0D 0F9BA800 02 - OR DWORD PTR [7FF6784E2DCC],02
		dmc3.exe+2092BD
		*/

		constexpr byte8 sect0[] =
		{
			0x83, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x02, // or dword ptr [rdi+0000B8C0],02
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[3]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x20FBFD);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+20FBFD - 83 0D C831A800 10 - OR DWORD PTR [7FF6784E2DCC],10
		dmc3.exe+20FC04
		*/

		constexpr byte8 sect0[] =
		{
			0x83, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x10, // or dword ptr [rbx+0000B8C0],10
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[3]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x211950);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+211950 - 83 0D 7514A800 01 - OR DWORD PTR [7FF6784E2DCC],01
		dmc3.exe+211957
		*/

		constexpr byte8 sect0[] =
		{
			0x83, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x01, // or dword ptr [rbx+0000B8C0],01
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[3]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x211AA5);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+211AA5 - 83 0D 2013A800 01 - OR DWORD PTR [7FF6784E2DCC],01
		dmc3.exe+211AAC
		*/

		constexpr byte8 sect0[] =
		{
			0x83, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x01, // or dword ptr [rbx+0000B8C0],01
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[3]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x215D66);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+215D66 - 81 0D 5CD0A700 00000100 - OR [7FF6784E2DCC],00010000
		dmc3.exe+215D70
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, // or [rdi+0000B8C0],00010000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[3]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x21605D);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+21605D - 81 0D 65CDA700 00000100 - OR [7FF6784E2DCC],00010000
		dmc3.exe+216067
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, // or [rdi+0000B8C0],00010000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[3]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x21630D);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+21630D - 81 0D B5CAA700 80070000 - OR [7FF6784E2DCC],00000780
		dmc3.exe+216317
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x80, 0x07, 0x00, 0x00, // or [rdi+0000B8C0],00000780
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[3]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x2164AF);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+2164AF - 81 0D 13C9A700 00180000 - OR [7FF6784E2DCC],00001800
		dmc3.exe+2164B9
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, // or [rdi+0000B8C0],00001800
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[3]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x21B696);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+21B696 - 81 0D 3077A700 00020000 - OR [7FF6784E2DD0],00000200
		dmc3.exe+21B6A0
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, // or [rbx+0000B8C0],00000200
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[4]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x21B85A);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+21B85A - 83 0D 6F75A700 40 - OR DWORD PTR [7FF6784E2DD0],40
		dmc3.exe+21B861
		*/

		constexpr byte8 sect0[] =
		{
			0x83, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x40, // or dword ptr [rbx+0000B8C0],40
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[4]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x21BB16);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+21BB16 - 81 0D B072A700 00000002 - OR [7FF6784E2DD0],02000000
		dmc3.exe+21BB20
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, // or [rbx+0000B8C0],02000000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[4]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x21BB40);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+21BB40 - 81 0D 8672A700 00000002 - OR [7FF6784E2DD0],02000000
		dmc3.exe+21BB4A
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, // or [rbx+0000B8C0],02000000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[4]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x21BEE2);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+21BEE2 - 81 0D E46EA700 00000001 - OR [7FF6784E2DD0],01000000
		dmc3.exe+21BEEC
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, // or [rbx+0000B8C0],01000000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[4]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x21BF11);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+21BF11 - 81 0D B56EA700 00000001 - OR [7FF6784E2DD0],01000000
		dmc3.exe+21BF1B
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, // or [rbx+0000B8C0],01000000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[4]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x21C1C6);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+21C1C6 - 81 0D 006CA700 00020000 - OR [7FF6784E2DD0],00000200
		dmc3.exe+21C1D0
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, // or [rbx+0000B8C0],00000200
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[4]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x21C34A);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+21C34A - 81 0D 7C6AA700 80000000 - OR [7FF6784E2DD0],00000080
		dmc3.exe+21C354
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, // or [rbx+0000B8C0],00000080
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[4]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x21C57A);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+21C57A - 81 0D 4C68A700 00020000 - OR [7FF6784E2DD0],00000200
		dmc3.exe+21C584
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, // or [rbx+0000B8C0],00000200
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[4]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x21C703);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+21C703 - 81 0D C366A700 00010000 - OR [7FF6784E2DD0],00000100
		dmc3.exe+21C70D
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, // or [rbx+0000B8C0],00000100
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[4]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x21D04D);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+21D04D - 81 0D 795DA700 000C0000 - OR [7FF6784E2DD0],00000C00
		dmc3.exe+21D057
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, // or [rdi+0000B8C0],00000C00
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[4]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x21D228);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+21D228 - 81 0D 9E5BA700 00000200 - OR [7FF6784E2DD0],00020000
		dmc3.exe+21D232
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, // or [rdi+0000B8C0],00020000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[4]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x21DA15);
		constexpr uint32 size = 6;
		/*
		dmc3.exe+21DA15 - 8B 0D B553A700 - MOV ECX,[7FF6784E2DD0]
		dmc3.exe+21DA1B
		*/

		constexpr byte8 sect0[] =
		{
			0x8B, 0x8B, 0x00, 0x00, 0x00, 0x00, // mov ecx,[rbx+0000B8C0]
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[4]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x21DA2F);
		constexpr uint32 size = 6;
		/*
		dmc3.exe+21DA2F - 89 0D 9B53A700 - MOV [7FF6784E2DD0],ECX
		dmc3.exe+21DA35
		*/

		constexpr byte8 sect0[] =
		{
			0x89, 0x8B, 0x00, 0x00, 0x00, 0x00, // mov [rbx+0000B8C0],ecx
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[4]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x21DEBE);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+21DEBE - 81 0D 084FA700 00000004 - OR [7FF6784E2DD0],04000000
		dmc3.exe+21DEC8
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, // or [rbx+0000B8C0],04000000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[4]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x21E885);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+21E885 - 81 0D 4145A700 00100000 - OR [7FF6784E2DD0],00001000
		dmc3.exe+21E88F
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, // or [rbx+0000B8C0],00001000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[4]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x21F56D);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+21F56D - 81 0D 5938A700 00000200 - OR [7FF6784E2DD0],00020000
		dmc3.exe+21F577
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, // or [rdi+0000B8C0],00020000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[4]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x21F61A);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+21F61A - 81 0D AC37A700 00000200 - OR [7FF6784E2DD0],00020000
		dmc3.exe+21F624
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, // or [rdi+0000B8C0],00020000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[4]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x21FBF2);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+21FBF2 - 81 0D D431A700 00000020 - OR [7FF6784E2DD0],20000000
		dmc3.exe+21FBFC
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, // or [rbx+0000B8C0],20000000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[4]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x1F952C);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+1F952C - 81 0D 9E98A900 00060000 - OR [7FF6784E2DD4],00000600
		dmc3.exe+1F9536
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, // or [rbx+0000B8C0],00000600
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[5]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x21AED9);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+21AED9 - 81 0D F17EA700 00400000 - OR [7FF6784E2DD4],00004000
		dmc3.exe+21AEE3
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, // or [rdi+0000B8C0],00004000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[5]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x21B13A);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+21B13A - 81 0D 907CA700 00010000 - OR [7FF6784E2DD4],00000100
		dmc3.exe+21B144
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, // or [rbx+0000B8C0],00000100
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[5]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x21EB8A);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+21EB8A - 81 0D 4042A700 00080000 - OR [7FF6784E2DD4],00000800
		dmc3.exe+21EB94
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, // or [rdi+0000B8C0],00000800
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[5]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x21EC17);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+21EC17 - 81 0D B341A700 00080000 - OR [7FF6784E2DD4],00000800
		dmc3.exe+21EC21
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, // or [rdi+0000B8C0],00000800
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[5]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x21EDBB);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+21EDBB - 81 0D 0F40A700 00100000 - OR [7FF6784E2DD4],00001000
		dmc3.exe+21EDC5
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, // or [rdi+0000B8C0],00001000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[5]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x21F865);
		constexpr uint32 size = 6;
		/*
		dmc3.exe+21F865 - 09 05 6935A700 - OR [7FF6784E2DD4],EAX
		dmc3.exe+21F86B
		*/

		constexpr byte8 sect0[] =
		{
			0x09, 0x83, 0x00, 0x00, 0x00, 0x00, // or [rbx+0000B8C0],eax
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[5]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x21F955);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+21F955 - 83 0D 7834A700 08 - OR DWORD PTR [7FF6784E2DD4],08
		dmc3.exe+21F95C
		*/

		constexpr byte8 sect0[] =
		{
			0x83, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x08, // or dword ptr [rbx+0000B8C0],08
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[5]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x21FA45);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+21FA45 - 83 0D 8833A700 10 - OR DWORD PTR [7FF6784E2DD4],10
		dmc3.exe+21FA4C
		*/

		constexpr byte8 sect0[] =
		{
			0x83, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x10, // or dword ptr [rbx+0000B8C0],10
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[5]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x21FF82);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+21FF82 - 83 0D 4B2EA700 02 - OR DWORD PTR [7FF6784E2DD4],02
		dmc3.exe+21FF89
		*/

		constexpr byte8 sect0[] =
		{
			0x83, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x02, // or dword ptr [rbx+0000B8C0],02
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[5]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x2201E4);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+2201E4 - 83 0D E92BA700 20 - OR DWORD PTR [7FF6784E2DD4],20
		dmc3.exe+2201EB
		*/

		constexpr byte8 sect0[] =
		{
			0x83, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x20, // or dword ptr [rbx+0000B8C0],20
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[5]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x1FDEE2);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+1FDEE2 - 81 0D EC4EA900 00001800 - OR [7FF6784E2DD8],00180000
		dmc3.exe+1FDEEC
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, // or [rbx+0000B8C0],00180000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[6]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x215854);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+215854 - 81 0D 7AD5A700 00001800 - OR [7FF6784E2DD8],00180000
		dmc3.exe+21585E
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, // or [rdi+0000B8C0],00180000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[6]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x215A73);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+215A73 - 81 0D 5BD3A700 00001800 - OR [7FF6784E2DD8],00180000
		dmc3.exe+215A7D
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, // or [rdi+0000B8C0],00180000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[6]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x1F9590);
		constexpr uint32 size = 6;
		/*
		dmc3.exe+1F9590 - 8B 05 4698A900 - MOV EAX,[7FF6784E2DDC]
		dmc3.exe+1F9596
		*/

		constexpr byte8 sect0[] =
		{
			0x8B, 0x83, 0x00, 0x00, 0x00, 0x00, // mov eax,[rbx+0000B8C0]
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[7]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x1F95AA);
		constexpr uint32 size = 6;
		/*
		dmc3.exe+1F95AA - 89 05 2C98A900 - MOV [7FF6784E2DDC],EAX
		dmc3.exe+1F95B0
		*/

		constexpr byte8 sect0[] =
		{
			0x89, 0x83, 0x00, 0x00, 0x00, 0x00, // mov [rbx+0000B8C0],eax
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[7]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x1F95C6);
		constexpr uint32 size = 6;
		/*
		dmc3.exe+1F95C6 - 8B 05 1098A900 - MOV EAX,[7FF6784E2DDC]
		dmc3.exe+1F95CC
		*/

		constexpr byte8 sect0[] =
		{
			0x8B, 0x83, 0x00, 0x00, 0x00, 0x00, // mov eax,[rbx+0000B8C0]
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[7]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x1F95F0);
		constexpr uint32 size = 6;
		/*
		dmc3.exe+1F95F0 - 89 05 E697A900 - MOV [7FF6784E2DDC],EAX
		dmc3.exe+1F95F6
		*/

		constexpr byte8 sect0[] =
		{
			0x89, 0x83, 0x00, 0x00, 0x00, 0x00, // mov [rbx+0000B8C0],eax
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[7]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x1F9596);
		constexpr uint32 size = 6;
		/*
		dmc3.exe+1F9596 - 8B 0D 4498A900 - MOV ECX,[7FF6784E2DE0]
		dmc3.exe+1F959C
		*/

		constexpr byte8 sect0[] =
		{
			0x8B, 0x8B, 0x00, 0x00, 0x00, 0x00, // mov ecx,[rbx+0000B8C0]
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[8]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x1F95BA);
		constexpr uint32 size = 6;
		/*
		dmc3.exe+1F95BA - 89 0D 2098A900 - MOV [7FF6784E2DE0],ECX
		dmc3.exe+1F95C0
		*/

		constexpr byte8 sect0[] =
		{
			0x89, 0x8B, 0x00, 0x00, 0x00, 0x00, // mov [rbx+0000B8C0],ecx
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[8]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x1F95CC);
		constexpr uint32 size = 6;
		/*
		dmc3.exe+1F95CC - 8B 0D 0E98A900 - MOV ECX,[7FF6784E2DE0]
		dmc3.exe+1F95D2
		*/

		constexpr byte8 sect0[] =
		{
			0x8B, 0x8B, 0x00, 0x00, 0x00, 0x00, // mov ecx,[rbx+0000B8C0]
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[8]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x1F95F6);
		constexpr uint32 size = 6;
		/*
		dmc3.exe+1F95F6 - 89 0D E497A900 - MOV [7FF6784E2DE0],ECX
		dmc3.exe+1F95FC
		*/

		constexpr byte8 sect0[] =
		{
			0x89, 0x8B, 0x00, 0x00, 0x00, 0x00, // mov [rbx+0000B8C0],ecx
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[8]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x1FDEF8);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+1FDEF8 - 83 0D E54EA900 60 - OR DWORD PTR [7FF6784E2DE4],60
		dmc3.exe+1FDEFF
		*/

		constexpr byte8 sect0[] =
		{
			0x83, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x60, // or dword ptr [rbx+0000B8C0],60
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[9]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x21586A);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+21586A - 83 0D 73D5A700 60 - OR DWORD PTR [7FF6784E2DE4],60
		dmc3.exe+215871
		*/

		constexpr byte8 sect0[] =
		{
			0x83, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x60, // or dword ptr [rdi+0000B8C0],60
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[9]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x215A7F);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+215A7F - 83 0D 5ED3A700 60 - OR DWORD PTR [7FF6784E2DE4],60
		dmc3.exe+215A86
		*/

		constexpr byte8 sect0[] =
		{
			0x83, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x60, // or dword ptr [rdi+0000B8C0],60
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[9]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x1F95B0);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+1F95B0 - 81 0D 3298A900 00060000 - OR [7FF6784E2DEC],00000600
		dmc3.exe+1F95BA
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, // or [rbx+0000B8C0],00000600
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[11]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x219B4E);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+219B4E - 81 0D 9492A700 00800000 - OR [7FF6784E2DEC],00008000
		dmc3.exe+219B58
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, // or [rbx+0000B8C0],00008000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[11]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x219B95);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+219B95 - 81 0D 4D92A700 00000100 - OR [7FF6784E2DEC],00010000
		dmc3.exe+219B9F
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, // or [rbx+0000B8C0],00010000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[11]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x219BD8);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+219BD8 - 81 0D 0A92A700 00000200 - OR [7FF6784E2DEC],00020000
		dmc3.exe+219BE2
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, // or [rbx+0000B8C0],00020000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[11]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x21CD33);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+21CD33 - 81 0D AF60A700 00000100 - OR [7FF6784E2DEC],00010000
		dmc3.exe+21CD3D
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, // or [rbx+0000B8C0],00010000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[11]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x21F3F1);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+21F3F1 - 81 0D F139A700 00000200 - OR [7FF6784E2DEC],00020000
		dmc3.exe+21F3FB
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, // or [rbx+0000B8C0],00020000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[11]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x21FFA1);
		constexpr uint32 size = 7;
		/*
		dmc3.exe+21FFA1 - 83 0D 442EA700 20 - OR DWORD PTR [7FF6784E2DEC],20
		dmc3.exe+21FFA8
		*/

		constexpr byte8 sect0[] =
		{
			0x83, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x20, // or dword ptr [rbx+0000B8C0],20
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[11]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x2201EB);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+2201EB - 81 0D F72BA700 00800000 - OR [7FF6784E2DEC],00008000
		dmc3.exe+2201F5
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, // or [rbx+0000B8C0],00008000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[11]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x222BEF);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+222BEF - 81 0D F301A700 00800000 - OR [7FF6784E2DEC],00008000
		dmc3.exe+222BF9
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, // or [rdi+0000B8C0],00008000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[11]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x222C8A);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+222C8A - 81 0D 5801A700 00800000 - OR [7FF6784E2DEC],00008000
		dmc3.exe+222C94
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, // or [rdi+0000B8C0],00008000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[11]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x222D66);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+222D66 - 81 0D 7C00A700 00000100 - OR [7FF6784E2DEC],00010000
		dmc3.exe+222D70
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, // or [rdi+0000B8C0],00010000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[11]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x222E0E);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+222E0E - 81 0D D4FFA600 00000100 - OR [7FF6784E2DEC],00010000
		dmc3.exe+222E18
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, // or [rdi+0000B8C0],00010000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[11]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x222EB9);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+222EB9 - 81 0D 29FFA600 00000200 - OR [7FF6784E2DEC],00020000
		dmc3.exe+222EC3
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, // or [rdi+0000B8C0],00020000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[11]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x222F1A);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+222F1A - 81 0D C8FEA600 00000200 - OR [7FF6784E2DEC],00020000
		dmc3.exe+222F24
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, // or [rdi+0000B8C0],00020000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[11]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x222FDC);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+222FDC - 81 0D 06FEA600 00000200 - OR [7FF6784E2DEC],00020000
		dmc3.exe+222FE6
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, // or [rdi+0000B8C0],00020000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[11]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x22D175);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+22D175 - 81 0D 6D5CA600 00000800 - OR [7FF6784E2DEC],00080000
		dmc3.exe+22D17F
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, // or [rdi+0000B8C0],00080000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[11]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x22D32B);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+22D32B - 81 0D B75AA600 00000800 - OR [7FF6784E2DEC],00080000
		dmc3.exe+22D335
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, // or [rbx+0000B8C0],00080000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[11]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}
	{
		auto addr = (appBaseAddr + 0x22D406);
		constexpr uint32 size = 10;
		/*
		dmc3.exe+22D406 - 81 0D DC59A600 00000800 - OR [7FF6784E2DEC],00080000
		dmc3.exe+22D410
		*/

		constexpr byte8 sect0[] =
		{
			0x81, 0x8B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, // or [rbx+0000B8C0],00080000
		};
		static_assert(sizeof(sect0) == size);

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			protectionHelper.Push(addr, size);
			CopyMemory(addr, sect0, sizeof(sect0));
			*reinterpret_cast<uint32 *>(addr + 2) = offsetof(PlayerActorData, newEffectIndices[11]);
			protectionHelper.Pop();
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	run = true;
}







export void ToggleFixDevilAura(bool enable)
{
	LogFunction(enable);

	static bool run = false;

	{
		auto addr     = (appBaseAddr + 0x8F898);
		auto jumpAddr = (appBaseAddr + 0x8F89E);
		constexpr uint32 size = 6;
		/*
		dmc3.exe+8F898 - 8B 91 A83E0000 - mov edx,[rcx+00003EA8]
		dmc3.exe+8F89E - 85 D2          - test edx,edx
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rax,
			mov_rcx_rdi,
			call,
			mov_rcx_rax,
			pop_rax,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, (sizeof(sect0) + size));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			CopyMemory((func.sect0 + sizeof(sect0)), addr, size, MemoryFlags_VirtualProtectSource);
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	{
		auto addr     = (appBaseAddr + 0x90B21);
		auto jumpAddr = (appBaseAddr + 0x90B26);
		constexpr uint32 size = 5;
		/*
		dmc3.exe+90B21 - BB 01000000 - mov ebx,00000001
		dmc3.exe+90B26 - 8B D3       - mov edx,ebx
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			push_rax,
			mov_rcx_rdi,
			call,
			mov_rcx_rax,
			pop_rax,
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = old_CreateFunction(0, jumpAddr, false, true, (sizeof(sect0) + size));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			CopyMemory((func.sect0 + sizeof(sect0)), addr, size, MemoryFlags_VirtualProtectSource);
			WriteCall((func.sect0 + 4), GetPlayerActorBaseAddressByEffectData);
		}

		if (enable)
		{
			WriteJump(addr, func.addr, (size - 5));
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	run = true;
}










export void ToggleModelCountAdjustments(bool enable)
{
	LogFunction(enable);

	// Model Data
	{
		constexpr uint32 count = 3;
		constexpr uint32 newCount = 6;
		// Create
		Write<uint32>((appBaseAddr + 0x1DDB6A + 2), (enable) ? newCount : count); // dmc3.exe+1DDB6A - 41 B8 03000000 - mov r8d,00000003
		// Free
		Write<uint32>((appBaseAddr + 0x1DE42D + 2), (enable) ? newCount : count); // dmc3.exe+1DE42D - 41 B8 03000000 - mov r8d,00000003
		Write<uint32>((appBaseAddr + 0x1DE771 + 1), (enable) ? newCount : count); // dmc3.exe+1DE771 - BD 03000000 - mov ebp,00000003
	}

	// Model Physics Metadata Pool
	{
		constexpr uint32 count = (4 * 24);
		constexpr uint32 newCount = (7 * 24);
		// Create Actor Dante
		Write<uint32>((appBaseAddr + 0x1DEC63 + 2), (enable) ? newCount : count); // dmc3.exe+1DEC63 - 41 B9 60000000 - mov r9d,00000060
		// Create Actor Bob
		Write<uint32>((appBaseAddr + 0x1DEB4A + 2), (enable) ? newCount : count); // dmc3.exe+1DEB4A - 41 B9 60000000 - MOV R9D,00000060
		// Create Actor Lady
		Write<uint32>((appBaseAddr + 0x1DEA4E + 2), (enable) ? newCount : count); // dmc3.exe+1DEA4E - 41 B9 60000000 - MOV R9D,00000060
		// Create Actor Vergil
		Write<uint32>((appBaseAddr + 0x1DE935 + 2), (enable) ? newCount : count); // dmc3.exe+1DE935 - 41 B9 60000000 - MOV R9D,00000060
		// Free
		// Handled together with Model Allocation Data.
	}

	// Model Allocation Data
	{
		constexpr uint32 count = 209;
		constexpr uint32 newCount = 512;
		// Create Actor
		Write<uint32>((appBaseAddr + 0x1DDB95 + 2), (enable) ? newCount : count); // dmc3.exe+1DDB95 - 41 B8 D1000000 - mov r8d,000000D1
		// Create Actor Dante
		Write<uint32>((appBaseAddr + 0x1DD172 + 1), (enable) ? newCount : count); // dmc3.exe+1DD172 - B8 D1000000 - mov eax,000000D1
		// Create Actor Bob
		Write<uint32>((appBaseAddr + 0x1DD3E2 + 1), (enable) ? newCount : count); // dmc3.exe+1DD3E2 - B8 D1000000 - MOV EAX,000000D1
		// Create Actor Lady
		Write<uint32>((appBaseAddr + 0x1DD242 + 1), (enable) ? newCount : count); // dmc3.exe+1DD242 - B8 D1000000 - MOV EAX,000000D1
		// Create Actor Vergil
		Write<uint32>((appBaseAddr + 0x1DD312 + 1), (enable) ? newCount : count); // dmc3.exe+1DD312 - B8 D1000000 - MOV EAX,000000D1
		// Free
		Write<uint32>((appBaseAddr + 0x1DE40E + 2), (enable) ? newCount : count); // dmc3.exe+1DE40E - 41 B8 D1000000 - mov r8d,000000D1
	}

	// Recovery Data
	{
		constexpr int8 count = -(static_cast<int8>(sizeof(RecoveryData) - 3));
		constexpr int8 newCount = -(static_cast<int8>(sizeof(RecoveryData) - 6));
		// Create
		Write<int8>((appBaseAddr + 0x1DDC28 + 3), (enable) ? newCount : count); // dmc3.exe+1DDC28 - 44 8D 42 93 - lea r8d,[rdx-6D]
		// Free
		Write<int8>((appBaseAddr + 0x1DE3C0 + 3), (enable) ? newCount : count); // dmc3.exe+1DE3C0 - 44 8D 42 93 - lea r8d,[rdx-6D]
	}

	// Body Part Data
	{
		constexpr uint32 count = (3 * 2);
		constexpr uint32 newCount = (6 * 2);
		// Create
		Write<uint8>((appBaseAddr + 0x1DDD82 + 3), (enable) ? static_cast<uint8>(newCount) : static_cast<uint8>(count)); // dmc3.exe+1DDD82 - 45 8D 47 06 - lea r8d,[r15+06]
		// Free
		Write<uint32>((appBaseAddr + 0x1DE307 + 2), (enable) ? newCount : count); // dmc3.exe+1DE307 - 41 B8 06000000 - mov r8d,00000006
	}

	// Submodel Data
	{
		constexpr uint32 count = (1 + (2 * 2));
		constexpr uint32 newCount = (1 + (5 * 2));
		// Create
		Write<uint32>((appBaseAddr + 0x1DD4F1 + 2), (enable) ? newCount : count); // dmc3.exe+1DD4F1 - 41 B8 05000000 - mov r8d,00000005
		// Free
		Write<uint32>((appBaseAddr + 0x1DDF31 + 2), (enable) ? newCount : count); // dmc3.exe+1DDF31 - 41 B8 05000000 - mov r8d,00000005
		Write<uint8>((appBaseAddr + 0x211FBD + 2), (enable) ? static_cast<uint8>(newCount) : static_cast<uint8>(count)); // dmc3.exe+211FBD - 83 FE 05 - cmp esi,05
	}

	// Model Shadow Data
	{
		constexpr uint32 count = 3;
		constexpr uint32 newCount = 6;
		// Create
		Write<uint32>((appBaseAddr + 0x1DD51C + 2), (enable) ? newCount : count); // dmc3.exe+1DD51C - 41 B8 03000000 - mov r8d,00000003
		// Free
		Write<uint32>((appBaseAddr + 0x1DDF12 + 2), (enable) ? newCount : count); // dmc3.exe+1DDF12 - 41 B8 03000000 - mov r8d,00000003
		Write<uint8>((appBaseAddr + 0x21200E + 2), (enable) ? static_cast<uint8>(newCount) : static_cast<uint8>(count)); // dmc3.exe+21200E - 83 FF 03 - cmp edi,03
	}

	// Submodel Shadow Data
	{
		constexpr uint32 count = (1 + (2 * 2));
		constexpr uint32 newCount = (1 + (5 * 2));
		// Create
		Write<uint32>((appBaseAddr + 0x1DD540 + 2), (enable) ? newCount : count); // dmc3.exe+1DD540 - 41 B8 05000000 - mov r8d,00000005
		// Free
		Write<uint32>((appBaseAddr + 0x1DDEF3 + 2), (enable) ? newCount : count); // dmc3.exe+1DDEF3 - 41 B8 05000000 - mov r8d,00000005
	}

	// Submodel Physics Metadata Pool
	{
		constexpr uint32 count = 39;
		constexpr uint32 newCount = 39;
		// Create
		Write<uint32>((appBaseAddr + 0x1DEC9D + 2), (enable) ? newCount : count); // dmc3.exe+1DEC9D - 41 B9 27000000 - mov r9d,00000027
		// Free
		// Handled together with Model Allocation Data.
	}

	// Submodel Physics Data
	{
		constexpr uint32 count = 1;
		constexpr uint32 newCount = 1;
		// Create
		Write<uint32>((appBaseAddr + 0x1DD56B + 2), (enable) ? newCount : count); // dmc3.exe+1DD56B - 41 B8 01000000 - mov r8d,00000001
		// Free
		Write<uint32>((appBaseAddr + 0x1DDED4 + 2), (enable) ? newCount : count); // dmc3.exe+1DDED4 - 41 B8 01000000 - mov r8d,00000001
	}

	// Devil Model Physics Metadata Pool
	{
		constexpr uint32 count = (2 * 36);
		constexpr uint32 newCount = (5 * 36);
		// Create
		Write<uint32>((appBaseAddr + 0x1DEC80 + 2), (enable) ? newCount : count); // dmc3.exe+1DEC80 - 41 B9 48000000 - mov r9d,00000048
		// Free
		// Handled together with Model Allocation Data.
	}

	// Devil Submodel Physics Data
	{
		constexpr uint32 count = (2 * 2);
		constexpr uint32 newCount = (5 * 2);
		// Create
		Write<uint32>((appBaseAddr + 0x1DD58F + 2), (enable) ? newCount : count); // dmc3.exe+1DD58F - 41 B8 04000000 - mov r8d,00000004
		// Free
		Write<uint32>((appBaseAddr + 0x1DDEB5 + 2), (enable) ? newCount : count); // dmc3.exe+1DDEB5 - 41 B8 04000000 - mov r8d,00000004
	}

	// Devil Submodel Physics Link Data
	{
		constexpr uint32 count = (2 * 2 * 4);
		constexpr uint32 newCount = (5 * 2 * 4);
		// Create
		Write<uint32>((appBaseAddr + 0x1DD5BA + 2), (enable) ? newCount : count); // dmc3.exe+1DD5BA - 41 B8 10000000 - mov r8d,00000010
		// Free
		Write<uint32>((appBaseAddr + 0x1DDE96 + 2), (enable) ? newCount : count); // dmc3.exe+1DDE96 - 41 B8 10000000 - mov r8d,00000010
	}
}

export void ToggleWeaponCountAdjustments(bool enable)
{
	LogFunction(enable);

	constexpr uint8 count = 5;
	constexpr uint8 newCount = 10;

	Write<uint8>((appBaseAddr + 0x1D91EC + 2), (enable) ? newCount : count); // dmc3.exe+1D91EC - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x1E02B2 + 2), (enable) ? newCount : count); // dmc3.exe+1E02B2 - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x1EAE1E + 2), (enable) ? newCount : count); // dmc3.exe+1EAE1E - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x1F59BD + 2), (enable) ? newCount : count); // dmc3.exe+1F59BD - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x1FACAB + 2), (enable) ? newCount : count); // dmc3.exe+1FACAB - 83 F8 05 - cmp eax,05
	Write<uint8>((appBaseAddr + 0x1FAD0B + 2), (enable) ? newCount : count); // dmc3.exe+1FAD0B - 83 F8 05 - cmp eax,05
	Write<uint8>((appBaseAddr + 0x1FAD4B + 2), (enable) ? newCount : count); // dmc3.exe+1FAD4B - 83 F8 05 - cmp eax,05
	Write<uint8>((appBaseAddr + 0x1FD14F + 3), (enable) ? newCount : count); // dmc3.exe+1FD14F - 41 83 FA 05 - cmp r10d,05
	Write<uint8>((appBaseAddr + 0x1FD180 + 3), (enable) ? newCount : count); // dmc3.exe+1FD180 - 41 83 F9 05 - cmp r9d,05
	Write<uint8>((appBaseAddr + 0x1FD1DB + 2), (enable) ? newCount : count); // dmc3.exe+1FD1DB - 83 F8 05 - cmp eax,05
	Write<uint8>((appBaseAddr + 0x1FD65D + 2), (enable) ? newCount : count); // dmc3.exe+1FD65D - 83 F8 05 - cmp eax,05
	Write<uint8>((appBaseAddr + 0x20617E + 2), (enable) ? newCount : count); // dmc3.exe+20617E - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x20619E + 2), (enable) ? newCount : count); // dmc3.exe+20619E - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x2063AC + 2), (enable) ? newCount : count); // dmc3.exe+2063AC - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x20651C + 2), (enable) ? newCount : count); // dmc3.exe+20651C - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x20822C + 2), (enable) ? newCount : count); // dmc3.exe+20822C - 83 FF 05 - cmp edi,05
	Write<uint8>((appBaseAddr + 0x2086F1 + 2), (enable) ? newCount : count); // dmc3.exe+2086F1 - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x20871F + 2), (enable) ? newCount : count); // dmc3.exe+20871F - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x20E30E + 2), (enable) ? newCount : count); // dmc3.exe+20E30E - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x20E33E + 2), (enable) ? newCount : count); // dmc3.exe+20E33E - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x20E36F + 2), (enable) ? newCount : count); // dmc3.exe+20E36F - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x20E66E + 2), (enable) ? newCount : count); // dmc3.exe+20E66E - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x20E71F + 2), (enable) ? newCount : count); // dmc3.exe+20E71F - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x210A2E + 2), (enable) ? newCount : count); // dmc3.exe+210A2E - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x210C0C + 2), (enable) ? newCount : count); // dmc3.exe+210C0C - 83 FF 05 - cmp edi,05
	Write<uint8>((appBaseAddr + 0x210C50 + 2), (enable) ? newCount : count); // dmc3.exe+210C50 - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x2113DD + 2), (enable) ? newCount : count); // dmc3.exe+2113DD - 83 FF 05 - cmp edi,05
	Write<uint8>((appBaseAddr + 0x2114CC + 2), (enable) ? newCount : count); // dmc3.exe+2114CC - 83 FF 05 - cmp edi,05
	Write<uint8>((appBaseAddr + 0x2115EC + 2), (enable) ? newCount : count); // dmc3.exe+2115EC - 83 FF 05 - cmp edi,05
	Write<uint8>((appBaseAddr + 0x21168E + 2), (enable) ? newCount : count); // dmc3.exe+21168E - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21172F + 2), (enable) ? newCount : count); // dmc3.exe+21172F - 83 FF 05 - cmp edi,05
	Write<uint8>((appBaseAddr + 0x21178E + 2), (enable) ? newCount : count); // dmc3.exe+21178E - 83 F9 05 - cmp ecx,05
	Write<uint32>((appBaseAddr + 0x215602 + 1), (enable) ? newCount : count); // dmc3.exe+215602 - BA 05000000 - mov edx,00000005
	Write<uint8>((appBaseAddr + 0x215657 + 2), (enable) ? newCount : count); // dmc3.exe+215657 - 8D 4A 05 - lea ecx,[rdx+05]
	Write<uint8>((appBaseAddr + 0x21570E + 2), (enable) ? newCount : count); // dmc3.exe+21570E - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x2158BE + 2), (enable) ? newCount : count); // dmc3.exe+2158BE - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21597E + 2), (enable) ? newCount : count); // dmc3.exe+21597E - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x2159EE + 2), (enable) ? newCount : count); // dmc3.exe+2159EE - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x215BDE + 2), (enable) ? newCount : count); // dmc3.exe+215BDE - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x215E8E + 2), (enable) ? newCount : count); // dmc3.exe+215E8E - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x215EAE + 2), (enable) ? newCount : count); // dmc3.exe+215EAE - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x216E4E + 2), (enable) ? newCount : count); // dmc3.exe+216E4E - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x217022 + 2), (enable) ? newCount : count); // dmc3.exe+217022 - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x2171F2 + 2), (enable) ? newCount : count); // dmc3.exe+2171F2 - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x217372 + 2), (enable) ? newCount : count); // dmc3.exe+217372 - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21747F + 2), (enable) ? newCount : count); // dmc3.exe+21747F - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x2181A2 + 2), (enable) ? newCount : count); // dmc3.exe+2181A2 - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x218322 + 2), (enable) ? newCount : count); // dmc3.exe+218322 - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x2183F1 + 2), (enable) ? newCount : count); // dmc3.exe+2183F1 - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21842E + 2), (enable) ? newCount : count); // dmc3.exe+21842E - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x218462 + 2), (enable) ? newCount : count); // dmc3.exe+218462 - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x2184BE + 2), (enable) ? newCount : count); // dmc3.exe+2184BE - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x2184FE + 2), (enable) ? newCount : count); // dmc3.exe+2184FE - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21853E + 2), (enable) ? newCount : count); // dmc3.exe+21853E - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21A46E + 2), (enable) ? newCount : count); // dmc3.exe+21A46E - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21A4BE + 2), (enable) ? newCount : count); // dmc3.exe+21A4BE - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21B800 + 2), (enable) ? newCount : count); // dmc3.exe+21B800 - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21B8CE + 2), (enable) ? newCount : count); // dmc3.exe+21B8CE - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21B8FE + 2), (enable) ? newCount : count); // dmc3.exe+21B8FE - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21BBBC + 2), (enable) ? newCount : count); // dmc3.exe+21BBBC - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21BBF0 + 2), (enable) ? newCount : count); // dmc3.exe+21BBF0 - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21C0AE + 2), (enable) ? newCount : count); // dmc3.exe+21C0AE - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21C3DE + 2), (enable) ? newCount : count); // dmc3.exe+21C3DE - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21C40E + 2), (enable) ? newCount : count); // dmc3.exe+21C40E - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21C6AF + 2), (enable) ? newCount : count); // dmc3.exe+21C6AF - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21C751 + 2), (enable) ? newCount : count); // dmc3.exe+21C751 - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21C84E + 2), (enable) ? newCount : count); // dmc3.exe+21C84E - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21D0E0 + 2), (enable) ? newCount : count); // dmc3.exe+21D0E0 - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21D10E + 2), (enable) ? newCount : count); // dmc3.exe+21D10E - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21E910 + 2), (enable) ? newCount : count); // dmc3.exe+21E910 - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21E93E + 2), (enable) ? newCount : count); // dmc3.exe+21E93E - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x21F232 + 2), (enable) ? newCount : count); // dmc3.exe+21F232 - 83 FF 05 - cmp edi,05
	Write<uint8>((appBaseAddr + 0x21F260 + 2), (enable) ? newCount : count); // dmc3.exe+21F260 - 83 F9 05 - cmp ecx,05
	Write<uint32>((appBaseAddr + 0x2228FF + 1), (enable) ? newCount : count); // dmc3.exe+2228FF - BA 05000000 - mov edx,00000005
	Write<uint8>((appBaseAddr + 0x2229AE + 2), (enable) ? newCount : count); // dmc3.exe+2229AE - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x222B52 + 2), (enable) ? newCount : count); // dmc3.exe+222B52 - 83 F9 05 - cmp ecx,05
	Write<uint8>((appBaseAddr + 0x222E9E + 2), (enable) ? newCount : count); // dmc3.exe+222E9E - 83 FE 05 - cmp esi,05
	Write<uint8>((appBaseAddr + 0x222F40 + 2), (enable) ? newCount : count); // dmc3.exe+222F40 - 83 F9 05 - cmp ecx,05
}
























namespaceEnd();
