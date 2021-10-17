// @Update

export module Graphics;

import Core;

#include "../Core/Macros.h"

// import Core_ImGui;

import Config;
import Global;
import Vars;







/*
dmc3.exe+4F22E  - 0FBE 83 8D020000    - MOVSX EAX,BYTE PTR [RBX+0000028D]
dmc3.exe+23D39E - 0FBE 05 5828A500    - MOVSX EAX,BYTE PTR [00C8EFFD]

dmc3.exe+2A284D - 0FBE 0D A9D39E00    - MOVSX ECX,BYTE PTR [00C8EFFD]
dmc3.exe+2A5504 - 0FBE 0D F2A69E00    - MOVSX ECX,BYTE PTR [00C8EFFD]
dmc3.exe+32B23D - 0FBE 0D B9499600    - MOVSX ECX,BYTE PTR [00C8EFFD]

dmc3.exe+3297EB - 0FBE 15 0B649600    - MOVSX EDX,BYTE PTR [00C8EFFD]

dmc3.exe+27EF97 - 44 0FBE 15 5E0CA100 - MOVSX R10D,BYTE PTR [00C8EFFD]

dmc3.exe+2384FD - 80 3D F976A500 3C   - CMP BYTE PTR [00C8EFFD],3C
dmc3.exe+32693E - 80 3D B8929600 32   - CMP BYTE PTR [00C8EFFD],32
*/


// constexpr byte8 sect0[] =
// {
// 	0x8B, 0x05, 0x00, 0x00, 0x00, 0x00,       // mov eax,[]
// 	0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00,       // mov ecx,[]
// 	0x8B, 0x15, 0x00, 0x00, 0x00, 0x00,       // mov edx,[]
// 	0x44, 0x8B, 0x15, 0x00, 0x00, 0x00, 0x00, // mov r10d,[]
// };

/*
dmc3.exe+4F22E - 8B 05 CC0D6E05        - mov eax,[7FF7BC990000] { (60) }
dmc3.exe+4F234 - 90                    - nop 
dmc3.exe+4F235 - FF 83 90020000        - inc [rbx+00000290]

dmc3.exe+23D39E - 8B 05 5C2C4F05        - mov eax,[7FF7BC990000] { (60) }
dmc3.exe+23D3A4 - 90                    - nop 
dmc3.exe+23D3A5 - 48 8B 57 10           - mov rdx,[rdi+10]

dmc3.exe+2A284D - 8B 0D ADD74805        - mov ecx,[7FF7BC990000] { (60) }
dmc3.exe+2A2853 - 90                    - nop 
dmc3.exe+2A2854 - 4C 89 A4 24 A0000000  - mov [rsp+000000A0],r12

dmc3.exe+2A5504 - 8B 0D F6AA4805        - mov ecx,[7FF7BC990000] { (60) }
dmc3.exe+2A550A - 90                    - nop 
dmc3.exe+2A550B - 33 D2                 - xor edx,edx

dmc3.exe+32B23D - 8B 0D BD4D4005        - mov ecx,[7FF7BC990000] { (60) }
dmc3.exe+32B243 - 90                    - nop 
dmc3.exe+32B244 - 8B 05 46932300        - mov eax,[dmc3.exe+564590] { (39) }

dmc3.exe+3297EB - 8B 15 0F684005        - mov edx,[7FF7BC990000] { (60) }
dmc3.exe+3297F1 - 90                    - nop 
dmc3.exe+3297F2 - 4C 8B C0              - mov r8,rax

dmc3.exe+27EF97 - 44 8B 15 62104B05     - mov r10d,[7FF7BC990000] { (60) }
dmc3.exe+27EF9E - 90                    - nop 
dmc3.exe+27EF9F - 33 D2                 - xor edx,edx
*/































double g_defaultFrequency = 0;

double * g_frequencyAddr = 0;

int32 * g_frameRateAddr = 0;



void ToggleFrameRateFixes(bool enable)
{
	LogFunction(enable);

	static bool run = false;



	#pragma region movsx eax

	{
		auto addr = (appBaseAddr + 0x4F22E);
		constexpr uint64 size = 7;
		/*
		dmc3.exe+4F22E - 0FBE 83 8D020000 - movsx eax,byte ptr [rbx+0000028D]
		dmc3.exe+4F235 - FF 83 90020000   - inc [rbx+00000290]
		*/

		constexpr byte8 sect0[] =
		{
			0x8B, 0x05, 0x00, 0x00, 0x00, 0x00, // mov eax,[]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			SetMemory(addr, 0x90, size, MemoryFlags_VirtualProtectDestination);
			CopyMemory(addr, sect0, sizeof(sect0), MemoryFlags_VirtualProtectDestination);
			WriteAddress(addr, g_frameRateAddr, 6);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	{
		auto addr = (appBaseAddr + 0x23D39E);
		constexpr uint64 size = 7;
		/*
		dmc3.exe+23D39E - 0FBE 05 5828A500 - movsx eax,byte ptr [dmc3.exe+C8FBFD]
		dmc3.exe+23D3A5 - 48 8B 57 10      - mov rdx,[rdi+10]
		*/

		constexpr byte8 sect0[] =
		{
			0x8B, 0x05, 0x00, 0x00, 0x00, 0x00, // mov eax,[]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			SetMemory(addr, 0x90, size, MemoryFlags_VirtualProtectDestination);
			CopyMemory(addr, sect0, sizeof(sect0), MemoryFlags_VirtualProtectDestination);
			WriteAddress(addr, g_frameRateAddr, 6);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	#pragma endregion

	#pragma region movsx ecx

	{
		auto addr = (appBaseAddr + 0x2A284D);
		constexpr uint64 size = 7;
		/*
		dmc3.exe+2A284D - 0FBE 0D A9D39E00     - movsx ecx,byte ptr [dmc3.exe+C8FBFD]
		dmc3.exe+2A2854 - 4C 89 A4 24 A0000000 - mov [rsp+000000A0],r12
		*/

		constexpr byte8 sect0[] =
		{
			0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, // mov ecx,[]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			SetMemory(addr, 0x90, size, MemoryFlags_VirtualProtectDestination);
			CopyMemory(addr, sect0, sizeof(sect0), MemoryFlags_VirtualProtectDestination);
			WriteAddress(addr, g_frameRateAddr, 6);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	{
		auto addr = (appBaseAddr + 0x2A5504);
		constexpr uint64 size = 7;
		/*
		dmc3.exe+2A5504 - 0FBE 0D F2A69E00 - movsx ecx,byte ptr [dmc3.exe+C8FBFD]
		dmc3.exe+2A550B - 33 D2            - xor edx,edx
		*/

		constexpr byte8 sect0[] =
		{
			0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, // mov ecx,[]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			SetMemory(addr, 0x90, size, MemoryFlags_VirtualProtectDestination);
			CopyMemory(addr, sect0, sizeof(sect0), MemoryFlags_VirtualProtectDestination);
			WriteAddress(addr, g_frameRateAddr, 6);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	{
		auto addr = (appBaseAddr + 0x32B23D);
		constexpr uint64 size = 7;
		/*
		dmc3.exe+32B23D - 0FBE 0D B9499600 - movsx ecx,byte ptr [dmc3.exe+C8FBFD]
		dmc3.exe+32B244 - 8B 05 46932300   - mov eax,[dmc3.exe+564590]
		*/

		constexpr byte8 sect0[] =
		{
			0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, // mov ecx,[]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			SetMemory(addr, 0x90, size, MemoryFlags_VirtualProtectDestination);
			CopyMemory(addr, sect0, sizeof(sect0), MemoryFlags_VirtualProtectDestination);
			WriteAddress(addr, g_frameRateAddr, 6);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	#pragma endregion

	#pragma region movsx edx

	{
		auto addr = (appBaseAddr + 0x3297EB);
		constexpr uint64 size = 7;
		/*
		dmc3.exe+3297EB - 0FBE 15 0B649600 - movsx edx,byte ptr [dmc3.exe+C8FBFD]
		dmc3.exe+3297F2 - 4C 8B C0         - mov r8,rax
		*/

		constexpr byte8 sect0[] =
		{
			0x8B, 0x15, 0x00, 0x00, 0x00, 0x00, // mov edx,[]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			SetMemory(addr, 0x90, size, MemoryFlags_VirtualProtectDestination);
			CopyMemory(addr, sect0, sizeof(sect0), MemoryFlags_VirtualProtectDestination);
			WriteAddress(addr, g_frameRateAddr, 6);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	#pragma endregion

	#pragma region movsx r10d

	{
		auto addr = (appBaseAddr + 0x27EF97);
		constexpr uint64 size = 8;
		/*
		dmc3.exe+27EF97 - 44 0FBE 15 5E0CA100 - movsx r10d,byte ptr [dmc3.exe+C8FBFD]
		dmc3.exe+27EF9F - 33 D2               - xor edx,edx
		*/

		constexpr byte8 sect0[] =
		{
			0x44, 0x8B, 0x15, 0x00, 0x00, 0x00, 0x00, // mov r10d,[]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
		}

		if (enable)
		{
			SetMemory(addr, 0x90, size, MemoryFlags_VirtualProtectDestination);
			CopyMemory(addr, sect0, sizeof(sect0), MemoryFlags_VirtualProtectDestination);
			WriteAddress(addr, g_frameRateAddr, 7);
		}
		else
		{
			backupHelper.Restore(addr);
		}
	}

	#pragma endregion



	run = true;
}


// @Todo: Call in D3D11.
namespaceStart(Graphics);

export void Toggle(bool enable)
{
	LogFunction(enable);

	static bool run = false;



	if (!run)
	{
		g_defaultFrequency = *reinterpret_cast<double *>(appBaseAddr + 0x505E38);
		/*
		dmc3.exe+2C5E97 - F2 0F10 3D 99FF2300 - movsd xmm7,[dmc3.exe+505E38]
		dmc3.exe+2C5E9F - 48 89 05 4A2A9E00   - mov [dmc3.exe+CA88F0],rax
		*/

		g_frequencyAddr = reinterpret_cast<double *>(HighAlloc(8));
		if (!g_frequencyAddr)
		{
			Log("HighAlloc failed.");

			return;
		}

		*g_frequencyAddr = g_defaultFrequency;



		g_frameRateAddr = reinterpret_cast<int32 *>(HighAlloc(4));
		if (!g_frameRateAddr)
		{
			Log("HighAlloc failed.");

			return;
		}

		*g_frameRateAddr = 60;
	}



	{
		auto addr     = (appBaseAddr + 0x2C5EB0);
		auto jumpAddr = (appBaseAddr + 0x2C5EB5);
		constexpr uint64 size = 5;
		/*
		dmc3.exe+2C5EB0 - 48 8D 4C 24 20 - lea rcx,[rsp+20]
		dmc3.exe+2C5EB5 - FF 15 1D930800 - call qword ptr [dmc3.exe+34F1D8]
		*/

		static Function func = {};

		constexpr byte8 sect0[] =
		{
			0xF2, 0x0F, 0x10, 0x3D, 0x00, 0x00, 0x00, 0x00, // movsd xmm7,[]
		};

		if (!run)
		{
			backupHelper.Save(addr, size);
			func = CreateFunction(0, jumpAddr, false, true, (sizeof(sect0) + size));
			CopyMemory(func.sect0, sect0, sizeof(sect0));
			CopyMemory((func.sect0 + sizeof(sect0)), addr, size, MemoryFlags_VirtualProtectSource);
			WriteAddress(func.sect0, g_frequencyAddr, 8);
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



	ToggleFrameRateFixes(enable);



	run = true;
}

namespaceEnd();



export void UpdateFrameRate()
{
	LogFunction();

	*g_frequencyAddr = (g_defaultFrequency * (60.0 / static_cast<double>(activeConfig.frameRate)));

	*g_frameRateAddr = static_cast<int32>(activeConfig.frameRate);

	g_frameRateMultiplier = (60.0f / activeConfig.frameRate);
}














// export void Init()
// {
// 	LogFunction();








// 	// {
// 	// 	constexpr byte8 sect0[] =
// 	// 	{
// 	// 		0xF2, 0x0F, 0x10, 0x3D, 0x00, 0x00, 0x00, 0x00, // movsd xmm7,[]
// 	// 		0x48, 0x8D, 0x4C, 0x24, 0x20,                   // lea rcx,[rsp+20]
// 	// 	};
// 	// 	auto func = CreateFunction(0, (appBaseAddr + 0x2C5EB5), false, true, sizeof(sect0));
// 	// 	CopyMemory(func.sect0, sect0, sizeof(sect0));
// 	// 	WriteAddress(func.sect0, g_frequencyAddr, 8);
// 	// 	WriteJump((appBaseAddr + 0x2C5EB0), func.addr);
// 	// 	/*
// 	// 	dmc3.exe+2C5EB0 - 48 8D 4C 24 20 - lea rcx,[rsp+20]
// 	// 	dmc3.exe+2C5EB5 - FF 15 1D930800 - call qword ptr [dmc3.exe+34F1D8]
// 	// 	*/
// 	// }
// }

// @Todo: Since double is kinda the exception, deal with it and prefer float.
// export void UpdateRenderSize
// (
// 	uint32 width,
// 	uint32 height
// )
// {
// 	Log
// 	(
// 		"%s "
// 		"%u "
// 		"%u",
// 		FUNC_NAME,
// 		width,
// 		height
// 	);

// 	renderWidth = width;
// 	renderHeight = height;
// 	renderSize =
// 	{
// 		static_cast<float>(width),
// 		static_cast<float>(height)
// 	};

// 	ImGui::UpdateDisplaySize
// 	(
// 		width,
// 		height
// 	);

// 	ImGui::DI8::UpdateMouseMultiplier
// 	(
// 		windowSize,
// 		renderSize
// 	);
// }
