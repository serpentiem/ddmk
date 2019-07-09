#include "Actor.h"

BYTE * actorBaseAddr[MAX_ACTOR] = {};

CreateActor_t CreateActor[MAX_CHAR] = {};
InitActor_t   InitActor  [MAX_CHAR] = {};
SpawnActor_t  SpawnActor            = 0;

static DWORD SpawnActorsThread(LPVOID parameter)
{
	LogFunction();
	Sleep(Config.Game.Multiplayer.spawnDelay);

	if (!Config.Game.Multiplayer.enable)
	{
		return 1;
	}


	for (uint8 actor = 0; actor < Config.Game.Multiplayer.actorCount; actor++)
	{
		uint8 character = Config.Game.Multiplayer.character[actor];
		if (character >= MAX_CHAR)
		{
			character = 0;
		}
		BYTE * addr = CreateActor[character]();
		if (!addr)
		{
			Log("CreateActor failed. %u %u", actor, character);
			continue;
		}
		addr = InitActor[character](addr);
		if (!addr)
		{
			Log("InitActor failed. %u %u", actor, character);
			continue;
		}
		actorBaseAddr[(ACTOR_TWO + actor)] = addr;
		if (!SpawnActor(13, addr, 0, 0))
		{
			Log("SpawnActor failed. %u %u %X", actor, character, addr);
			continue;
		}
	}
	return 1;
}

static void CreateSpawnActorsThread()
{
	LogFunction();
	CreateThread(0, 4096, SpawnActorsThread, 0, 0, 0);
}

void System_Actor_Init()
{
	LogFunction();
	{
		uint32 offset[MAX_CHAR][2] =
		{
			{ 0x4D27D0, 0x4D2800 },
			{ 0x50EE10, 0x50EEF0 },
			{  0xCB400,  0xCB430 },
			{  0xC69C0,  0xC69F0 },
			{  0xC5140,  0xC5170 },
		};
		for (uint8 character = 0; character < MAX_CHAR; character++)
		{
			{
				BYTE sect1[] =
				{
					0xE8, 0x00, 0x00, 0x00, 0x00, //call
				};
				FUNC func = CreateFunction(0, 0, true, false, 0, sizeof(sect1));
				memcpy(func.sect1, sect1, sizeof(sect1));
				WriteCall(func.sect1, (appBaseAddr + offset[character][0]));
				CreateActor[character] = (CreateActor_t)func.addr;
			}
			{
				BYTE sect1[] =
				{
					0x8B, 0x44, 0x24, 0x24,       //mov eax,[esp+24]
					0x8B, 0xF0,                   //mov esi,eax
					0xE8, 0x00, 0x00, 0x00, 0x00, //call
				};
				FUNC func = CreateFunction(0, 1, true, false, 0, sizeof(sect1));
				memcpy(func.sect1, sect1, sizeof(sect1));
				if (character == CHAR_VERGIL)
				{
					Write<BYTE>((func.sect1 + 5), 0xF8); // mov edi,eax
				}
				WriteCall((func.sect1 + 6), (appBaseAddr + offset[character][1]));
				InitActor[character] = (InitActor_t)func.addr;
			}
		}
	}
	{
		BYTE sect1[] =
		{
			0x83, 0xEC, 0x10,                   //sub esp,10
			0x51,                               //push ecx
			0x56,                               //push esi
			0x57,                               //push edi
			0xB9, 0x04, 0x00, 0x00, 0x00,       //mov ecx,00000004
			0x8D, 0x74, 0x24, 0x40,             //lea esi,[esp+40]
			0x8D, 0x7C, 0x24, 0x0C,             //lea edi,[esp+0C]
			0xF3, 0xA5,                         //repe movsd
			0x5F,                               //pop edi
			0x5E,                               //pop esi
			0x59,                               //pop ecx
			0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, //mov ecx,[dmc4.exe+F240A4]
			0xE8, 0x00, 0x00, 0x00, 0x00,       //call dmc4.exe+6C32E0
		};
		FUNC func = CreateFunction(0, 4, true, false, 0, sizeof(sect1));
		memcpy(func.sect1, sect1, sizeof(sect1));
		*(BYTE **)(func.sect1 + 0x1A) = (appBaseAddr + 0xF240A4);
		WriteCall((func.sect1 + 0x1E), (appBaseAddr + 0x6C32E0));
		SpawnActor = (SpawnActor_t)func.addr;
	}
	{
		BYTE sect2[] =
		{
			0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc4.exe+5F1C50
		};
		FUNC func = CreateFunction(CreateSpawnActorsThread, (appBaseAddr + 0x11660F), true, true, 0, 0, sizeof(sect2));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteCall(func.sect2, (appBaseAddr + 0x5F1C50));
		WriteJump((appBaseAddr + 0x11660A), func.addr);
	}



















	Log("CreateActor %X", CreateActor[CHAR_DANTE]);
	Log("InitActor   %X", InitActor[CHAR_DANTE]);
	Log("SpawnActor  %X", SpawnActor);
}
