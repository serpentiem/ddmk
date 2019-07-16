#include "File.h"

#pragma warning(disable: 4102) // Unreferenced label.

LoadFile_t LoadFile = 0;

BYTE * LoadAssetsProxy = 0;

// @Research: Disabled actor's costume is being applied to previous actor. Error either here or in Actor.cpp.

const char * path[MAX_CHAR][4] =
{
	{
		"rom\\player\\uPlayerDante",
		"rom\\player\\costume\\plmod_pl006",
		"rom\\player\\costume\\plmod_pl006_ex00",
		"rom\\player\\costume\\plmod_pl006_ex01",
	},
	{
		"rom\\player\\uPlayerNero",
		"rom\\player\\costume\\plmod_pl000",
		"rom\\player\\costume\\plmod_pl000_ex00",
		"rom\\player\\costume\\plmod_pl000_ex01",
	},
	{
		"rom\\player\\uPlayerVergil",
		"rom\\player\\costume\\plmod_pl030",
		"rom\\player\\costume\\plmod_pl030_ex00",
		"rom\\player\\costume\\plmod_pl030_ex01",
	},
	{
		"rom\\player\\uPlayerTrish",
		"rom\\player\\costume\\plmod_pl007",
		"rom\\player\\costume\\plmod_pl007_ex00",
		"rom\\player\\costume\\plmod_pl007_ex01",
	},
	{
		"rom\\player\\uPlayerLady",
		"rom\\player\\costume\\plmod_pl008",
		"rom\\player\\costume\\plmod_pl008_ex00",
		"rom\\player\\costume\\plmod_pl008_ex01",
	},
};

static void LoadAssets()
{
	LogFunction();
	MultiplayerStart:
	if (!Config.Game.Multiplayer.enable)
	{
		goto MultiplayerEnd;
	}
	for (uint8 actor = 0; actor < Config.Game.Multiplayer.actorCount; actor++)
	{
		uint8 character = Config.Game.Multiplayer.character[actor];
		if (character >= MAX_CHAR)
		{
			character = 0;
		}
		uint8 costume = Config.Game.Multiplayer.costume[actor];
		if (costume >= MAX_COSTUME)
		{
			costume = 0;
		}
		if (((character == CHAR_TRISH) || (character == CHAR_LADY)) && (costume == 1) && (IsDLCInstalled(DLC_TRISH_LADY_COSTUMES) == false))
		{
			costume = 0;
			Log("Required DLC not installed. %u %u", character, DLC_TRISH_LADY_COSTUMES);
		}
		BYTE * addr = (appBaseAddr + 0xF23F18);
		LoadFile(addr, path[character][1], LOAD_FILE_QUEUE);
		LoadFile(addr, path[character][(1 + costume)], LOAD_FILE_QUEUE);
		LoadFile(addr, path[character][0], LOAD_FILE_QUEUE);
	}
	MultiplayerEnd:
	return;
}

void System_File_Init()
{
	LogFunction();
	{
		BYTE sect1[] =
		{
			0x83, 0xEC, 0x0C,                   //sub esp,0C
			0x51,                               //push ecx
			0x56,                               //push esi
			0x57,                               //push edi
			0xB9, 0x03, 0x00, 0x00, 0x00,       //mov ecx,00000003
			0x8D, 0x74, 0x24, 0x3C,             //lea esi,[esp+3C]
			0x8D, 0x7C, 0x24, 0x0C,             //lea edi,[esp+0C]
			0xF3, 0xA5,                         //repe movsd
			0x5F,                               //pop edi
			0x5E,                               //pop esi
			0x59,                               //pop ecx
			0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, //mov ecx,[dmc4.exe+F23E44]
			0x8B, 0x01,                         //mov eax,[ecx]
			0x8B, 0x40, 0x30,                   //mov eax,[eax+30]
			0xFF, 0xD0,                         //call eax
		};
		FUNC func = CreateFunction(0, 3, true, false, 0, sizeof(sect1));
		memcpy(func.sect1, sect1, sizeof(sect1));
		*(BYTE **)(func.sect1 + 0x1A) = (appBaseAddr + 0xF23E44);
		LoadFile = (LoadFile_t)func.addr;
	}
	{
		BYTE sect0[] =
		{
			0x68, 0x00, 0x00, 0x00, 0x00, //push dmc4.exe+F23F18
			0xFF, 0xD2,                   //call edx
		};
		FUNC func = CreateFunction(LoadAssets, (appBaseAddr + 0x10C894), true, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*(BYTE **)(func.sect0 + 1) = (appBaseAddr + 0xF23F18);
		LoadAssetsProxy = func.addr;
	}
	Log("LoadFile   %X", LoadFile);
	Log("LoadAssets %X", LoadAssets);
}

void System_File_Toggle(bool enable)
{
	LogFunctionBool(enable);
	if (enable)
	{
		WriteJump((appBaseAddr + 0x10C88D), LoadAssetsProxy);
	}
	else
	{
		Write<BYTE>((appBaseAddr + 0x10C88D), 0x68);
		Write<BYTE *>((appBaseAddr + 0x10C88D + 1), (appBaseAddr + 0xF23F18));
	}
}
