module;
#include "../Core/Core.h"

#include "Vars.h"
export module Speed;

import Config;
import State;

float * turboAddr            = 0;
float * quicksilverActorAddr = 0;
float * quicksilverEnemyAddr = 0;

export void UpdateSpeedValues()
{
	LogFunction();

	Write<float>((appBaseAddr + 0x32694E + 2), activeConfig.Speed.main);
	/*
	dmc3.exe+32694E - C7 01 0000803F - mov [rcx],3F800000
	dmc3.exe+326954 - C3             - ret 
	*/

	*turboAddr = activeConfig.Speed.turbo;
	WriteAddress((appBaseAddr + 0x23E639), turboAddr, 8);
	/*
	dmc3.exe+23E639 - F3 0F10 05 FFDF2800 - movss xmm0,[dmc3.exe+4CC640]
	dmc3.exe+23E641 - F3 0F11 05 4747AB00 - movss [dmc3.exe+CF2D90],xmm0
	*/

	Write<float>((appBaseAddr + 0x326ADA + 3), activeConfig.Speed.enemy);
	/*
	dmc3.exe+326ADA - C7 41 10 0000803F - mov [rcx+10],3F800000
	dmc3.exe+326AE1 - 80 B9 AC000000 01 - cmp byte ptr [rcx+000000AC],01
	*/

	WriteAddress((appBaseAddr + 0x27A982), quicksilverActorAddr, 8);
	WriteAddress((appBaseAddr + 0x27A98A), quicksilverEnemyAddr, 8);
	/*
	dmc3.exe+27A982 - F3 0F10 05 6E432500 - movss xmm0,[dmc3.exe+4CECF8]
	dmc3.exe+27A98A - F3 0F10 0D 5ADB2500 - movss xmm1,[dmc3.exe+4D84EC]
	*/

	auto & speed = *reinterpret_cast<float *>(appBaseAddr + 0xCF2D90);
	auto & turbo = *reinterpret_cast<bool *>(appBaseAddr + 0xD6CEA9);

	if (!InGame())
	{
		return;
	}
	
	speed = (turbo) ? activeConfig.Speed.turbo : activeConfig.Speed.main;
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
