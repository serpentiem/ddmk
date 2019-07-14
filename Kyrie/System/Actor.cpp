#include "Actor.h"

#pragma warning(disable: 4102) // Unreferenced label.

// @Research: Costume Session Data Access.

BYTE * actorBaseAddr[MAX_ACTOR] = {};

CreateActor_t CreateActor[MAX_CHAR] = {};
InitActor_t   InitActor  [MAX_CHAR] = {};
SpawnActor_t  SpawnActor            = 0;

BYTE * SpawnActorOneProxy   = 0;
BYTE * SpawnActorsProxy     = 0;
BYTE * GetLiveDataToSession = 0;

static void SpawnActorOne(BYTE * baseAddr)
{
	Log("%s %X", FUNC_NAME, baseAddr);
	memset(actorBaseAddr, 0, sizeof(actorBaseAddr));
	actorBaseAddr[ACTOR_ONE] = baseAddr;
}

static DWORD SpawnActorsThread(LPVOID parameter)
{
	LogFunction();
	MultiplayerStart:
	Log("MultiplayerStart");
	if (!Config.Game.Multiplayer.enable)
	{
		goto MultiplayerEnd;
	}
	Sleep(Config.Game.Multiplayer.spawnDelay);
	for (uint8 actor = 0; actor < Config.Game.Multiplayer.actorCount; actor++)
	{
		uint8 character = Config.Game.Multiplayer.character[actor];
		if (character >= MAX_CHAR)
		{
			character = 0;
		}
		Log("CreateActor %u %u", actor, character);
		BYTE * addr = CreateActor[character]();
		if (!addr)
		{
			Log("CreateActor failed. %u %u", actor, character);
			continue;
		}
		Log("InitActor %u %u", actor, character);
		addr = InitActor[character](addr);
		if (!addr)
		{
			Log("InitActor failed. %u %u", actor, character);
			continue;
		}
		actorBaseAddr[(ACTOR_TWO + actor)] = addr;
		Log("SpawnActor %u %u", actor, character);
		if (!SpawnActor(SPAWN_TYPE_ACTOR, addr, 0, 0))
		{
			Log("SpawnActor failed. %u %u %X", actor, character, addr);
			continue;
		}
	}
	Log("MultiplayerEnd");
	MultiplayerEnd:
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
		BYTE sect1[] =
		{
			0x50, //push eax
		};
		BYTE sect2[] =
		{
			0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc4.exe+6C32E0
		};
		FUNC func = CreateFunction(SpawnActorOne, (appBaseAddr + 0x116605), true, true, 0, sizeof(sect1), sizeof(sect2));
		memcpy(func.sect1, sect1, sizeof(sect1));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteCall(func.sect2, (appBaseAddr + 0x6C32E0));
		SpawnActorOneProxy = func.addr;
	}
	{
		BYTE sect2[] =
		{
			0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc4.exe+5F1C50
		};
		FUNC func = CreateFunction(CreateSpawnActorsThread, (appBaseAddr + 0x11660F), true, true, 0, 0, sizeof(sect2));
		memcpy(func.sect2, sect2, sizeof(sect2));
		WriteCall(func.sect2, (appBaseAddr + 0x5F1C50));
		SpawnActorsProxy = func.addr;
	}
	{
		BYTE sect0[] =
		{
			0x85, 0xC9,                               //test ecx,ecx
			0x74, 0x17,                               //je short
			0x50,                                     //push eax
			0x52,                                     //push edx
			0x31, 0xD2,                               //xor edx,edx
			0x8B, 0x04, 0x95, 0x00, 0x00, 0x00, 0x00, //mov eax,[edx*4+actorBaseAddr]
			0x39, 0xC1,                               //cmp ecx,eax
			0x74, 0x0E,                               //je short
			0x42,                                     //inc edx
			0x83, 0xFA, 0x00,                         //cmp edx,MAX_ACTOR
			0x72, 0xEF,                               //jb short
			0x5A,                                     //pop edx
			0x58,                                     //pop eax
			0xB9, 0x42, 0x00, 0x00, 0x00,             //mov ecx,00000042
			0xC3,                                     //ret
			0x5A,                                     //pop edx
			0x58,                                     //pop eax
			0x8B, 0x89, 0xAC, 0x19, 0x00, 0x00,       //mov ecx,[ecx+000019AC]
			0x83, 0xF9, 0x00,                         //cmp ecx,MAX_CHAR
			0x72, 0x02,                               //jb short
			0x31, 0xC9,                               //xor ecx,ecx
			0x8B, 0x35, 0x00, 0x00, 0x00, 0x00,       //mov esi,[dmc4.exe+F59F10]
			0xFF, 0x24, 0x8D, 0x00, 0x00, 0x00, 0x00, //jmp dword ptr [ecx*4+Cache]
			0x81, 0xC6, 0x68, 0x01, 0x00, 0x00,       //add esi,00000168
			0xB9, 0x42, 0x00, 0x00, 0x00,             //mov ecx,00000042
			0xC3,                                     //ret
			0x81, 0xC6, 0x70, 0x02, 0x00, 0x00,       //add esi,00000270
			0xB9, 0x3C, 0x00, 0x00, 0x00,             //mov ecx,0000003C
			0xC3,                                     //ret
			0x81, 0xC6, 0x60, 0x03, 0x00, 0x00,       //add esi,00000360
			0xB9, 0x3F, 0x00, 0x00, 0x00,             //mov ecx,0000003F
			0xC3,                                     //ret
			0x81, 0xC6, 0x5C, 0x04, 0x00, 0x00,       //add esi,0000045C
			0xB9, 0x42, 0x00, 0x00, 0x00,             //mov ecx,00000042
			0xC3,                                     //ret
			0x81, 0xC6, 0x64, 0x05, 0x00, 0x00,       //add esi,00000564
			0xB9, 0x3E, 0x00, 0x00, 0x00,             //mov ecx,0000003E
			0xC3,                                     //ret
		};
		FUNC func = CreateFunction(0, 0, false, true, sizeof(sect0), 0, 0, (MAX_CHAR * 4), true);
		memcpy(func.sect0, sect0, sizeof(sect0));
		*(BYTE ***)(func.sect0 + 0xB) = actorBaseAddr;
		*(uint8 *)(func.sect0 + 0x16) = MAX_ACTOR;
		*(uint8 *)(func.sect0 + 0x2B) = MAX_CHAR;
		*(BYTE **)(func.sect0 + 0x32) = (appBaseAddr + 0xF59F10);
		*(BYTE ***)(func.sect0 + 0x39) = func.cache;
		func.cache[CHAR_DANTE]  = (func.sect0 + 0x3D);
		func.cache[CHAR_NERO]   = (func.sect0 + 0x49);
		func.cache[CHAR_VERGIL] = (func.sect0 + 0x55);
		func.cache[CHAR_TRISH]  = (func.sect0 + 0x61);
		func.cache[CHAR_LADY]   = (func.sect0 + 0x6D);
		GetLiveDataToSession = func.addr;
	}
	Log("CreateActor %X", CreateActor[CHAR_DANTE]);
	Log("InitActor   %X", InitActor[CHAR_DANTE]);
	Log("SpawnActor  %X", SpawnActor);
	Log("GetLiveDataToSession %X", GetLiveDataToSession);
}

void System_Actor_Toggle(bool enable)
{
	LogFunctionBool(enable);
	if (enable)
	{
		WriteJump((appBaseAddr + 0x116600), SpawnActorOneProxy);
		WriteJump((appBaseAddr + 0x11660A), SpawnActorsProxy);
		WriteCall((appBaseAddr + 0x9E05D ), GetLiveDataToSession); // OnUpdate Lady Kalina Ann
		WriteCall((appBaseAddr + 0xB40AD ), GetLiveDataToSession); // OnUpdate Dante Nero Vergil Trish Lady
		WriteCall((appBaseAddr + 0xB40ED ), GetLiveDataToSession); // OnUpdate Dante OnEvent Trish Jump Spark
		WriteCall((appBaseAddr + 0x50FD4D), GetLiveDataToSession); // OnUpdate Nero
	}
	else
	{
		WriteCall((appBaseAddr + 0x116600), (appBaseAddr + 0x6C32E0));
		WriteCall((appBaseAddr + 0x11660A), (appBaseAddr + 0x5F1C50));
		{
			BYTE buffer[] =
			{
				0xB9, 0x42, 0x00, 0x00, 0x00, //mov ecx,00000042
			};
			vp_memcpy((appBaseAddr + 0x9E05D ), buffer, sizeof(buffer));
			vp_memcpy((appBaseAddr + 0xB40AD ), buffer, sizeof(buffer));
			vp_memcpy((appBaseAddr + 0xB40ED ), buffer, sizeof(buffer));
			vp_memcpy((appBaseAddr + 0x50FD4D), buffer, sizeof(buffer));
		}
	}
}
