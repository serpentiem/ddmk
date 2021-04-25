module;
#include "../Core/Macros.h" //

// #include "../Core/Core.h"

// #include "Vars.h"
export module Speed;

import Core;



import Vars;

// #define memset SetMemory
// #define memcpy CopyMemory

import Config;
import Global;

float * turboAddr            = 0;
float * quicksilverActorAddr = 0;
float * quicksilverEnemyAddr = 0;

export void UpdateSpeedValues()
{
	LogFunction();

	Write((appBaseAddr + 0x32694E + 2), activeConfig.Speed.main);
	/*
	dmc3.exe+32694E - C7 01 0000803F - mov [rcx],3F800000
	dmc3.exe+326954 - C3             - ret 
	*/

	// Cutscene
	Write((appBaseAddr + 0x2D4D12 + 6), activeConfig.Speed.main);
	/*
	dmc3.exe+2D4D12 - C7 05 74E0A100 0000803F - mov [dmc3.exe+CF2D90],3F800000
	dmc3.exe+2D4D1C - 48 8B F2                - mov rsi,rdx
	*/

	*turboAddr = activeConfig.Speed.turbo;
	WriteAddress((appBaseAddr + 0x23E639), turboAddr, 8);
	/*
	dmc3.exe+23E639 - F3 0F10 05 FFDF2800 - movss xmm0,[dmc3.exe+4CC640]
	dmc3.exe+23E641 - F3 0F11 05 4747AB00 - movss [dmc3.exe+CF2D90],xmm0
	*/

	Write((appBaseAddr + 0x326ADA + 3), activeConfig.Speed.enemy);
	/*
	dmc3.exe+326ADA - C7 41 10 0000803F - mov [rcx+10],3F800000
	dmc3.exe+326AE1 - 80 B9 AC000000 01 - cmp byte ptr [rcx+000000AC],01
	*/

	*quicksilverActorAddr = activeConfig.Speed.quicksilverActor;
	*quicksilverEnemyAddr = activeConfig.Speed.quicksilverEnemy;
	WriteAddress((appBaseAddr + 0x27A982), quicksilverActorAddr, 8);
	WriteAddress((appBaseAddr + 0x27A98A), quicksilverEnemyAddr, 8);
	/*
	dmc3.exe+27A982 - F3 0F10 05 6E432500 - movss xmm0,[dmc3.exe+4CECF8]
	dmc3.exe+27A98A - F3 0F10 0D 5ADB2500 - movss xmm1,[dmc3.exe+4D84EC]
	*/

	if (g_scene == SCENE_GAME)
	{
		auto & value = *reinterpret_cast<float *>(appBaseAddr + 0xCF2D90);
		auto & turbo = GetTurbo();

		value = (turbo) ? activeConfig.Speed.turbo : activeConfig.Speed.main;
	}
}

export void Speed_Init()
{
	LogFunction();

	auto dest = reinterpret_cast<float *>(HighAlloc(12));
	if (!dest)
	{
		Log("HighAlloc failed.");

		return;
	}

	turboAddr            = &dest[0];
	quicksilverActorAddr = &dest[1];
	quicksilverEnemyAddr = &dest[2];
}
