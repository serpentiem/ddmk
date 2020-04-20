#pragma once
#include "../Core/Core.h"

#include "File.h"
#include "Internal.h"
#include "State.h"
#include "Vars.h"

// @Todo: Move to vars.
// @Todo: Solve unknown enums.
enum HUD_TOP
{
	TOP_HIT_POINTS_FRAME,
	TOP_HIT_POINTS_BAR,
	TOP_HIT_POINTS_BACKGROUND,
	BOTTOM_HIT_POINTS_FRAME,
	BOTTOM_HIT_POINTS_BAR,
	BOTTOM_HIT_POINTS_BACKGROUND,
	MAGIC_ORBS,
	STYLE_ICON,
	RED_ORB_COUNTER,
	UNKNOWN_1,
	UNKNOWN_2,
	FLUX,
	UNKNOWN_3,
};

enum HUD_BOTTOM
{
	RANGED_WEAPON_1,
	RANGED_WEAPON_2,
	MELEE_WEAPON_1,
	MELEE_WEAPON_2,
};

constexpr uint32 HUD_topOff[] =
{
	0x700,
	0xE80,
	0x1600,
	0x1D80,
	0x2500,
	0x2C80,
	0x3400,
	0x3B80,
	0x4300,
	0x4A80,
	0x5200,
	0x5980,
	0x6100,
};

constexpr uint32 HUD_bottomOff[] =
{
	0x880,
	0x1000,
	0x1780,
	0x1F00,
};

struct HUDIconHelper
{
	byte8 * model;
	byte8 * texture;
};

extern HUDIconHelper HUD_styleIconDante [MAX_STYLE ];
extern HUDIconHelper HUD_styleIconVergil[MAX_STYLE ];
extern HUDIconHelper HUD_weaponIcon     [MAX_WEAPON];

inline bool HUD_IsVisible()
{
	if (!InGame())
	{
		return false;
	}
	// @Todo: Update pointer!
	byte8 ** addr = (byte8 **)(appBaseAddr + 0xCF2520);
	byte8 * item = addr[44];
	if (!item)
	{
		return false;
	}
	uint8 & alpha = *(uint8 *)(item + 0x6920);
	return (alpha > 0) ? true : false;
}

void HUD_UpdateStyleIcon
(
	uint8 style,
	byte8 * model,
	byte8 * texture
);

void HUD_UpdateWeaponIcon
(
	uint8 index,
	byte8 * model,
	byte8 * texture
);

void HUD_Init();
