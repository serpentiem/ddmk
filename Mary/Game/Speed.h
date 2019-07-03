#pragma once
#include "../../Core/Core.h"

#include "../Config.h"

#include "../System/State.h"

enum SPEED_
{
	SPEED_DANTE_REBELLION,
	SPEED_DANTE_CERBERUS,
	SPEED_DANTE_AGNI_RUDRA,
	SPEED_DANTE_NEVAN,
	SPEED_DANTE_BEOWULF,
	SPEED_DANTE_SPARDA,
	SPEED_VERGIL_YAMATO = 8,
	SPEED_VERGIL_BEOWULF,
	SPEED_VERGIL_FORCE_EDGE,
	SPEED_NERO_ANGELO_YAMATO,
	SPEED_NERO_ANGELO_BEOWULF,
	SPEED_NERO_ANGELO_FORCE_EDGE,
};

void Game_Speed_Update();
void Game_Speed_Reset();
void Game_Speed_Init();
void Game_Speed_Toggle(bool enable);
