#include "HUD.h"

HUDIconHelper HUD_styleIconDante [MAX_STYLE ] = {};
HUDIconHelper HUD_styleIconVergil[MAX_STYLE ] = {};
HUDIconHelper HUD_weaponIcon     [MAX_WEAPON] = {};

// @Research: Make map local.

constexpr uint8 styleIconMapDante[MAX_STYLE] =
{
	20,
	22,
	18,
	24,
	26,
	28,
};

constexpr uint8 weaponIconMapDante[] =
{
	42,
	44,
	46,
	48,
	50,
	30,
	32,
	34,
	36,
	38,
};

constexpr uint8 weaponIconMapVergil[] =
{
	42,
	44,
	30,
};

// @Todo: Either create helper for this or access actor data.

bool HUD_updateStyleIcon = false;

void HUD_Update()
{
	if (!HUD_updateStyleIcon)
	{
		return;
	}
	if (!HUD_IsVisible())
	{
		return;
	}
	HUD_updateStyleIcon = false;
	//HUD_UpdateStyleIcon();
}

void HUD_UpdateStyleIcon
(
	uint8 style,
	byte8 * model,
	byte8 * texture
)
{
	auto addr = *reinterpret_cast<byte8 **>(appBaseAddr + 0xC90E28);
	if (!addr)
	{
		return;
	}
	addr -= 0x180;
	auto top    = *reinterpret_cast<byte8 **>(addr + 0x1B070);
	auto bottom = *reinterpret_cast<byte8 **>(addr + 0x1B078);

	auto styleIcon = (top + 0x3B80);

	func_897B0(styleIcon);
	func_89450(styleIcon);
	memset(styleIcon, 0, 0x780);
	func_89270(styleIcon);

	auto map = reinterpret_cast<uint8 *>(appBaseAddr + 0x4E9070);
	auto & effect = *reinterpret_cast<uint8 *>(top + 0x690E) = map[style];

	func_89960(styleIcon, model, texture);
	func_89E30(styleIcon, 1);
}

void HUD_UpdateWeaponIcon
(
	uint8 index,
	byte8 * model,
	byte8 * texture
)
{
	auto addr = *reinterpret_cast<byte8 **>(appBaseAddr + 0xC90E28);
	if (!addr)
	{
		return;
	}
	addr -= 0x180;
	auto top    = *reinterpret_cast<byte8 **>(addr + 0x1B070);
	auto bottom = *reinterpret_cast<byte8 **>(addr + 0x1B078);

	auto dest = (bottom + HUD_bottomOff[index]);

	func_897B0(dest);
	func_89450(dest);
	memset(dest, 0, 0x780);
	func_89270(dest);

	func_89960(dest, model, texture);
	func_89E30(dest, 1);
}


void HUD_Init()
{
	LogFunction();




	// Init Icons
	{
		for_all(uint8, index, countof(styleIconMapDante))
		{
			auto & fileIndex = styleIconMapDante[index];
			HUD_styleIconDante[index].model   = File_cacheFile[id100][(fileIndex + 1)];
			HUD_styleIconDante[index].texture = File_cacheFile[id100][(fileIndex + 0)];
		}

		HUD_styleIconVergil[STYLE_VERGIL_DARK_SLAYER].model   = File_cacheFile[id100V][(18 + 1)];
		HUD_styleIconVergil[STYLE_VERGIL_DARK_SLAYER].texture = File_cacheFile[id100V][(18 + 0)];

		for_all(uint8, index, countof(weaponIconMapDante))
		{
			auto & fileIndex = weaponIconMapDante[index];
			HUD_weaponIcon[(WEAPON_DANTE_REBELLION + index)].model   = File_cacheFile[id100][(fileIndex + 1)];
			HUD_weaponIcon[(WEAPON_DANTE_REBELLION + index)].texture = File_cacheFile[id100][(fileIndex + 0)];
		}

		for_all(uint8, index, countof(weaponIconMapVergil))
		{
			auto & fileIndex = weaponIconMapVergil[index];
			HUD_weaponIcon[(WEAPON_VERGIL_YAMATO + index)].model   = File_cacheFile[id100V][(fileIndex + 1)];
			HUD_weaponIcon[(WEAPON_VERGIL_YAMATO + index)].texture = File_cacheFile[id100V][(fileIndex + 0)];
		}
	}


	for_all(uint8, index, countof(HUD_weaponIcon))
	{
		Log("%u %llX", index, HUD_weaponIcon[index].model);
	}











}











