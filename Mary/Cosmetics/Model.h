#pragma once
#include "../../Core/Core.h"

#include "../Config.h"
#include "../Internal.h"
#include "../Vars.h"

#include "../System/File.h"

typedef void(__fastcall * Cosmetics_Model_UpdateModel_t)(byte8 * baseAddr);
typedef void(__fastcall * Cosmetics_Model_UpdateDevilModel_t)
(
	byte8 * baseAddr,
	uint8   slot
);

extern Cosmetics_Model_UpdateModel_t Cosmetics_Model_UpdateModelDante      [MAX_COSTUME];
extern Cosmetics_Model_UpdateModel_t Cosmetics_Model_UpdateModelDanteVergil[MAX_COSTUME];

extern Cosmetics_Model_UpdateDevilModel_t Cosmetics_Model_UpdateDevilModelDante      [MAX_DEVIL];
extern Cosmetics_Model_UpdateDevilModel_t Cosmetics_Model_UpdateDevilModelDanteVergil[MAX_DEVIL];

void Cosmetics_Model_Init();
