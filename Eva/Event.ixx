
// @Cleanup




export module Event;

import Core;

#include "../Core/Macros.h"

import Windows;

using namespace Windows;

import Actor;
import Arcade;
import BossRush;
import Config;
import Global;
import Vars;

#define debug false

#include "Macros.h"



namespaceStart(MissionSelect);

void LoadSaveFile()
{
	if (!activeConfig.MissionSelect.enable)
	{
		return;
	}

	LogFunction();

	IntroduceSessionData(return);



	sessionData.mission = activeConfig.MissionSelect.mission;
	sessionData.mode    = activeConfig.MissionSelect.mode;
}

namespaceEnd();





void InitSession()
{
	LogFunction();

	Arcade::InitSession();
}


void LoadSaveFile()
{
	LogFunction();

	MissionSelect::LoadSaveFile();
}





void MissionStartSetIndex()
{
	LogFunction();


	// @Research: Prefer InitSession.
	ToggleSkipText   (false);
	ToggleAutoExamine(false);



	Arcade::MissionStartSetIndex();
	BossRush::MissionStartSetIndex();
	Actor::MissionStartSetIndex();
}


void SetRoomNewGame()
{
	LogFunction();
}

void SetRoomMissionStart()
{
	LogFunction();

	Arcade::SetRoom();
	BossRush::SetRoom();
}

void SetRoomGeneric()
{
	LogFunction();
}


void SetPositionMissionStart()
{
	LogFunction();

	Arcade::SetPosition();
	BossRush::SetPosition();
}




void MainLoop()
{
	Actor::MainLoop();
}











// void Mission3CutsceneStart()
// {
// 	LogFunction();

// 	BossRush::Mission3CutsceneStart();
// }



// void SetRoom()
// {
// 	if (!g_setRoom)
// 	{
// 		return;
// 	}

// 	g_setRoom = false;

// 	LogFunction();

// 	Arcade::SetRoom();
// }


// void SetHitPoints()
// {
// 	LogFunction();

// 	Arcade::SetHitPoints();
// }

void SetExpertise()
{
	LogFunction();

	Arcade::SetExpertise();
}





void TextEnd()
{
	LogFunction();

	BossRush::TextEnd();
}










namespaceStart(Event);


export void Toggle(bool enable)
{
	LogFunction(enable);

	static bool run = false;




// MainLoop
{
	auto addr     = (appBaseAddr + 0x251839);
	auto jumpAddr = (appBaseAddr + 0x251840);
	constexpr uint32 size = 7;
	/*
	dmc1.exe+251839 - 41 8B 93 9C000000 - mov edx,[r11+0000009C]
	dmc1.exe+251840 - F7 C2 000000C0    - test edx,C0000000
	*/

	static Function func = {};

	if (!run)
	{
		backupHelper.Save(addr, size);
		func = CreateFunction(MainLoop, jumpAddr, true, true, 0, 0, size);
		CopyMemory(func.sect2, addr, size, MemoryFlags_VirtualProtectSource);
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














	// // Mission3CutsceneStart
	// {
	// 	auto addr     = (appBaseAddr + 0x318F8C);
	// 	auto jumpAddr = (appBaseAddr + 0x318F96);
	// 	constexpr uint32 size = 10;
	// 	/*
	// 	dmc1.exe+318F8C - 81 89 B41C0000 80808000 - or [rcx+00001CB4],00808080
	// 	dmc1.exe+318F96 - 66 89 35 47A39904       - mov [dmc1.exe+4CB32E4],si
	// 	*/

	// 	static Function func = {};

	// 	if (!run)
	// 	{
	// 		backupHelper.Save(addr, size);
	// 		func = CreateFunction(Mission3CutsceneStart, jumpAddr, true, true, size);
	// 		CopyMemory(func.sect0, addr, size, MemoryFlags_VirtualProtectSource);
	// 	}

	// 	if (enable)
	// 	{
	// 		WriteJump(addr, func.addr, (size - 5));
	// 	}
	// 	else
	// 	{
	// 		backupHelper.Restore(addr);
	// 	}
	// }











	// TextEnd
	{
		auto addr     = (appBaseAddr + 0x26731A);
		auto jumpAddr = (appBaseAddr + 0x267321);
		constexpr uint32 size = 7;
		/*
		dmc1.exe+26731A - 41 89 80 B41C0000 - mov [r8+00001CB4],eax
		dmc1.exe+267321 - 44 89 1D 58C7A404 - mov [dmc1.exe+4CB3A80],r11d
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(TextEnd, jumpAddr, true, true, size);
			CopyMemory(func.sect0, addr, size, MemoryFlags_VirtualProtectSource);
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

















	// InitSession
	{
		auto addr     = (appBaseAddr + 0x3F9D22);
		auto jumpAddr = (appBaseAddr + 0x3F9D27);
		constexpr uint32 size = 5;
		/*
		dmc1.exe+3F9D22 - 41 0FB6 4E 0D - movzx ecx,byte ptr [r14+0D]
		dmc1.exe+3F9D27 - 85 C9         - test ecx,ecx
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(InitSession, jumpAddr, true, true, size);
			CopyMemory(func.sect0, addr, size, MemoryFlags_VirtualProtectSource);
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

	// MissionStartSetIndex
	{
		auto addr     = (appBaseAddr + 0x3DC0E2);
		auto jumpAddr = (appBaseAddr + 0x3DC0E9);
		constexpr uint32 size = 7;
		/*
		dmc1.exe+3DC0E2 - 48 89 AB 60A50000 - mov [rbx+0000A560],rbp
		dmc1.exe+3DC0E9 - 48 89 AB 68A50000 - mov [rbx+0000A568],rbp
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(MissionStartSetIndex, jumpAddr, true, true, size);
			CopyMemory(func.sect0, addr, size, MemoryFlags_VirtualProtectSource);
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

	// SetRoomNewGame
	{
		auto addr     = (appBaseAddr + 0x24F719);
		auto jumpAddr = (appBaseAddr + 0x24F721);
		constexpr uint32 size = 8;
		/*
		dmc1.exe+24F719 - F3 0F11 0D 8B8B5902 - movss [dmc1.exe+27E82AC],xmm1
		dmc1.exe+24F721 - 33 FF               - xor edi,edi
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(SetRoomNewGame, jumpAddr, true, true, size);
			CopyMemory(func.sect0, addr, size, MemoryFlags_VirtualProtectSource);
			WriteAddress(func.sect0, (appBaseAddr + 0x27E82AC), 8);
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

	// SetRoomMissionStart
	{
		auto addr     = (appBaseAddr + 0x255D75);
		auto jumpAddr = (appBaseAddr + 0x255D7B);
		constexpr uint32 size = 6;
		/*
		dmc1.exe+255D75 - 89 81 74020000 - mov [rcx+00000274],eax
		dmc1.exe+255D7B - 0FB6 07        - movzx eax,byte ptr [rdi]
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(SetRoomMissionStart, jumpAddr, true, true, size);
			CopyMemory(func.sect0, addr, size, MemoryFlags_VirtualProtectSource);
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

	// SetRoomGeneric
	{
		auto addr     = (appBaseAddr + 0x252680);
		auto jumpAddr = (appBaseAddr + 0x252686);
		constexpr uint32 size = 6;
		/*
		dmc1.exe+252680 - 89 83 74020000             - mov [rbx+00000274],eax
		dmc1.exe+252686 - 41 81 A3 A41C0000 FFFFFFBF - and [r11+00001CA4],BFFFFFFF
		*/

		static Function func = {};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(SetRoomGeneric, jumpAddr, true, true, size);
			CopyMemory(func.sect0, addr, size, MemoryFlags_VirtualProtectSource);
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



// SetPositionMissionStart
{
	auto addr     = (appBaseAddr + 0x255D88);
	auto jumpAddr = (appBaseAddr + 0x255D8F);
	constexpr uint32 size = 7;
	/*
	dmc1.exe+255D88 - 0F29 05 11255902 - movaps [dmc1.exe+27E82A0],xmm0
	dmc1.exe+255D8F - 8B 82 A41C0000   - mov eax,[rdx+00001CA4]
	*/

	static Function func = {};

	if (!run)
	{
		backupHelper.Save(addr, size);
		func = CreateFunction(SetPositionMissionStart, jumpAddr, true, true, size);
		CopyMemory(func.sect0, addr, size, MemoryFlags_VirtualProtectSource);
		WriteAddress(func.sect0, (appBaseAddr + 0x27E82A0), 7);
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




















// // SetEquipmentNewGame
// {
// 	auto addr     = (appBaseAddr + 0x2C3CAC);
// 	auto jumpAddr = (appBaseAddr + 0x2C3CB3);
// 	constexpr uint32 size = 7;
// 	/*
// 	dmc1.exe+2C3CAC - 41 89 B8 68240000 - mov [r8+00002468],edi
// 	dmc1.exe+2C3CB3 - 0F28 05 66092200  - movaps xmm0,[dmc1.exe+4E4620]
// 	*/

// 	static Function func = {};

// 	if (!run)
// 	{
// 		backupHelper.Save(addr, size);
// 		func = CreateFunction(SetEquipmentNewGame, jumpAddr, true, true, size);
// 		CopyMemory(func.sect0, addr, size, MemoryFlags_VirtualProtectSource);
// 	}

// 	if (enable)
// 	{
// 		WriteJump(addr, func.addr, (size - 5));
// 	}
// 	else
// 	{
// 		backupHelper.Restore(addr);
// 	}
// }


// // SetEquipmentLoadGame
// {
// 	auto addr     = (appBaseAddr + 0x255BAE);
// 	auto jumpAddr = (appBaseAddr + 0x255BB5);
// 	constexpr uint32 size = 7;
// 	/*
// 	dmc1.exe+255BAE - 66 89 81 CE1B0000 - mov [rcx+00001BCE],ax
// 	dmc1.exe+255BB5 - 48 83 C4 20       - add rsp,20
// 	*/

// 	static Function func = {};

// 	if (!run)
// 	{
// 		backupHelper.Save(addr, size);
// 		func = CreateFunction(SetEquipmentLoadGame, jumpAddr, true, true, size);
// 		CopyMemory(func.sect0, addr, size, MemoryFlags_VirtualProtectSource);
// 	}

// 	if (enable)
// 	{
// 		WriteJump(addr, func.addr, (size - 5));
// 	}
// 	else
// 	{
// 		backupHelper.Restore(addr);
// 	}
// }



// // SetHitPoints
// {
// 	auto addr     = (appBaseAddr + 0x2C3C07);
// 	auto jumpAddr = (appBaseAddr + 0x2C3C0F);
// 	constexpr uint32 size = 8;
// 	/*
// 	dmc1.exe+2C3C07 - 41 0FB6 80 64240000 - movzx eax,byte ptr [r8+00002464]
// 	dmc1.exe+2C3C0F - 33 FF               - xor edi,edi
// 	*/

// 	static Function func = {};

// 	if (!run)
// 	{
// 		backupHelper.Save(addr, size);
// 		func = CreateFunction(SetHitPoints, jumpAddr, true, true, 0, 0, size);
// 		CopyMemory(func.sect2, addr, size, MemoryFlags_VirtualProtectSource);
// 	}

// 	if (enable)
// 	{
// 		WriteJump(addr, func.addr, (size - 5));
// 	}
// 	else
// 	{
// 		backupHelper.Restore(addr);
// 	}
// }


// SetExpertise
{
	auto addr     = (appBaseAddr + 0x2C3CAC);
	auto jumpAddr = (appBaseAddr + 0x2C3CB3);
	constexpr uint32 size = 7;
	/*
	dmc1.exe+2C3CAC - 41 89 B8 68240000 - mov [r8+00002468],edi
	dmc1.exe+2C3CB3 - 0F28 05 66092200  - movaps xmm0,[dmc1.exe+4E4620]
	*/

	static Function func = {};

	if (!run)
	{
		backupHelper.Save(addr, size);
		func = CreateFunction(SetExpertise, jumpAddr, true, true, size);
		CopyMemory(func.sect0, addr, size, MemoryFlags_VirtualProtectSource);
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






// LoadSaveFile
{
	auto addr     = (appBaseAddr + 0x255BAE);
	auto jumpAddr = (appBaseAddr + 0x255BB5);
	constexpr uint32 size = 7;
	/*
	dmc1.exe+255BAE - 66 89 81 CE1B0000 - mov [rcx+00001BCE],ax
	dmc1.exe+255BB5 - 48 83 C4 20       - add rsp,20
	*/

	static Function func = {};

	if (!run)
	{
		backupHelper.Save(addr, size);
		func = CreateFunction(LoadSaveFile, jumpAddr, true, true, size);
		CopyMemory(func.sect0, addr, size, MemoryFlags_VirtualProtectSource);
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











namespaceEnd();







export void ToggleDisablePauseRestrictions(bool enable)
{
	LogFunction(enable);



	static bool run = false;



	// Default
	{
		auto addr = (appBaseAddr + 0x2518D4);
		constexpr uint32 size = 2;
		/*
		dmc1.exe+2518D4 - 76 49       - jna dmc1.exe+25191F
		dmc1.exe+2518D6 - 41 8D 40 EA - lea eax,[r8-16]
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			Write<byte8>(addr, 0xEB);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Red
	{
		auto addr = (appBaseAddr + 0x2B8EC9);
		constexpr uint32 size = 2;
		/*
		dmc1.exe+2B8EC9 - 76 46       - jna dmc1.exe+2B8F11
		dmc1.exe+2B8ECB - 41 8D 40 EA - lea eax,[r8-16]
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			Write<byte8>(addr, 0xEB);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	// Red Ignore Screen Effect
	{
		auto addr = (appBaseAddr + 0x2B8DF3);
		auto dest = (appBaseAddr + 0x2B8DF5);
		constexpr uint32 size = 2;
		/*
		dmc1.exe+2B8DF3 - 75 13    - jne dmc1.exe+2B8E08
		dmc1.exe+2B8DF5 - 48 FF C1 - inc rcx
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			WriteAddress(addr, dest, size);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}



	// Default Plane
	{
		auto addr = (appBaseAddr + 0x251883);
		auto dest = (appBaseAddr + 0x251889);
		constexpr uint32 size = 6;
		/*
		dmc1.exe+251883 - 0F85 C4030000 - jne dmc1.exe+251C4D
		dmc1.exe+251889 - 41 0FBA E1 0B - bt r9d,0B
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			WriteAddress(addr, dest, size);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	{
		auto addr = (appBaseAddr + 0x2518B5);
		auto dest = (appBaseAddr + 0x2518BB);
		constexpr uint32 size = 6;
		/*
		dmc1.exe+2518B5 - 0F88 92030000     - js dmc1.exe+251C4D
		dmc1.exe+2518BB - 48 8B 0D 0E943B00 - mov rcx,[dmc1.exe+60ACD0]
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			WriteAddress(addr, dest, size);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}



	// Red Plane
	{
		auto addr = (appBaseAddr + 0x2B8E76);
		auto dest = (appBaseAddr + 0x2B8E7C);
		constexpr uint32 size = 6;
		/*
		dmc1.exe+2B8E76 - 0F85 CD000000 - jne dmc1.exe+2B8F49
		dmc1.exe+2B8E7C - 41 0FBA E1 0B - bt r9d,0B
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			WriteAddress(addr, dest, size);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	{
		auto addr = (appBaseAddr + 0x2B8EA4);
		auto dest = (appBaseAddr + 0x2B8EAA);
		constexpr uint32 size = 6;
		/*
		dmc1.exe+2B8EA4 - 0F88 9F000000     - js dmc1.exe+2B8F49
		dmc1.exe+2B8EAA - 80 3D C2F35202 00 - cmp byte ptr [dmc1.exe+27E8273],00
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			WriteAddress(addr, dest, size);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	{
		auto addr = (appBaseAddr + 0x2B8F81);
		auto dest = (appBaseAddr + 0x2B8F87);
		constexpr uint32 size = 6;
		/*
		dmc1.exe+2B8F81 - 0F85 1F010000 - jne dmc1.exe+2B90A6
		dmc1.exe+2B8F87 - 41 0FBA E0 0B - bt r8d,0B
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			WriteAddress(addr, dest, size);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	{
		auto addr = (appBaseAddr + 0x2B8FB8);
		auto dest = (appBaseAddr + 0x2B8FBE);
		constexpr uint32 size = 6;
		/*
		dmc1.exe+2B8FB8 - 0F8C E8000000 - jl dmc1.exe+2B90A6
		dmc1.exe+2B8FBE - 41 80 3B 02   - cmp byte ptr [r11],02
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			WriteAddress(addr, dest, size);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}



	run = true;
}



export void ToggleScreenEffectForceMaxTimer(bool enable)
{
	LogFunction(enable);



	static bool run = false;



	{
		auto addr = (appBaseAddr + 0x262427);
		auto dest = (appBaseAddr + 0x262429);
		constexpr uint32 size = 2;
		/*
		dmc1.exe+262427 - 75 23 - jne dmc1.exe+26244C
		dmc1.exe+262429 - A8 02 - test al,02
		*/

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			WriteAddress(addr, dest, size);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}



	run = true;
}










#ifdef __GARBAGE__
#endif
