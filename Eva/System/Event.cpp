#include "Event.h"

static inline void BossRush()
{
	if (!Config.Game.BossRush.enable)
	{
		return;
	}
	BYTE * session = *(BYTE **)(appBaseAddr + 0x5EAB88);
	if (!session)
	{
		return;
	}
	uint8 mission = *(uint8 *)(session + 0x1E64);
	BYTE * addr = *(BYTE **)(appBaseAddr + 0x60B148);
	if (!addr)
	{
		return;
	}
	uint16 & room = *(uint16 *)(addr + 0x274);
	if (mission == 22)
	{
		room = 11;
		if (Config.Game.BossRush.Mission22.skipAerialBattle)
		{
			room = 9;
		}
	}
}

static inline void MissionSelect()
{
	if (!Config.Game.MissionSelect.enable)
	{
		return;
	}
	BYTE * addr = *(BYTE **)(appBaseAddr + 0x5EAB88);
	if (!addr)
	{
		return;
	}
	uint8 & mission = *(uint8 *)(addr + 0x1E64);
	uint8 & mode    = *(uint8 *)(addr + 0x1E66);
	mission = Config.Game.MissionSelect.mission;
	mode    = Config.Game.MissionSelect.mode;
}


static void Arcade_InitSession()
{
	if (!Config.Game.Arcade.enable)
	{
		return;
	}
	BYTE * addr = *(BYTE **)(appBaseAddr + 0x5EAB88);
	if (!addr)
	{
		return;
	}
	uint8 & mission = *(uint8 *)(addr + 0x1E64);
	mission = Config.Game.Arcade.mission;
	uint8 & mode = *(uint8 *)(addr + 0x1E66);
	mode = Config.Game.Arcade.mode;


	uint8 & character = *(uint8 *)(addr + 0x1E67);
	character = Config.Game.Arcade.character;




	uint8 & hitPointsUnitCount = *(uint8 *)(addr + 0x2464);
	hitPointsUnitCount = Config.Game.Arcade.hitPointsUnitCount;
	uint8 & magicPointsUnitCount = *(uint8 *)(addr + 0x2465);
	magicPointsUnitCount = Config.Game.Arcade.magicPointsUnitCount;
	DWORD & expertise = *(DWORD *)(addr + 0x2468);
	expertise = 0xFFFFFFFF;
	DWORD & orbFlags = *(DWORD *)(addr + 0x247C);
	orbFlags += OrbFlags_GreenOrbTaken | OrbFlags_RedOrbTaken;







	/*
	dmc1.exe+60ACD0
	*/











}



void Arcade_SetRoom()
{

	/*
	dmc1.exe+60B148
	*/


	if (Config.Game.Arcade.ignoreRoom)
	{
		return;
	}

	BYTE * addr = *(BYTE **)(appBaseAddr + 0x60B148);
	if (!addr)
	{
		return;
	}

	uint16 & room = *(uint16 *)(addr + 0x274);
	room = Config.Game.Arcade.room;






}






static void InitSession()
{
	LogFunction();
	MissionSelect();
	Arcade_InitSession();
}

static void LoadSavegame()
{
	LogFunction();
	MissionSelect();
}






static void Arcade_SetEquipment()
{
	BYTE * addr = *(BYTE **)(appBaseAddr + 0x60ACD0);
	if (!addr)
	{
		return;
	}
	uint8 & meleeWeapon     = *(uint8 *)(addr + 0x1BCC);
	uint8 & rangedWeapon    = *(uint8 *)(addr + 0x1C48);
	uint8 & meleeWeaponForm = *(uint8 *)(addr + 0x1C4C);

	meleeWeapon     = Config.Game.Arcade.meleeWeapon;
	rangedWeapon    = Config.Game.Arcade.rangedWeapon;
	meleeWeaponForm = WEAPON_FORM_DEFAULT;
	switch (meleeWeapon)
	{
	case WEAPON_FORCE_EDGE:
		if (Config.Game.Arcade.meleeWeaponSparda)
		{
			meleeWeaponForm = WEAPON_FORM_SPARDA;
		}
		break;
	case WEAPON_ALASTOR:
		if (Config.Game.Arcade.meleeWeaponYamato)
		{
			meleeWeaponForm = WEAPON_FORM_YAMATO;
		}
		break;
	case WEAPON_SPARDA:
		meleeWeaponForm = WEAPON_FORM_SPARDA;
		break;
	}










	//if (meleeWeapon == WEAPON_FORCE_EDGE && Config.Game.Arcade.meleeWeaponSparda)
	//{
	//	meleeWeaponForm = WEAPON_FORM_SPARDA;
	//}
	//else if (meleeWeapon == WEAPON_ALASTOR && Config.Game.Arcade.meleeWeaponYamato)
	//{
	//	meleeWeaponForm = WEAPON_FORM_YAMATO;
	//}
	//else if (meleeWeapon == WEAPON_SPARDA)
	//{
	//	meleeWeaponForm = WEAPON_FORM_SPARDA;
	//}
}

static void SetEquipment()
{
	LogFunction();
	Arcade_SetEquipment();
}

static void SetRoom()
{
	LogFunction();


	Arcade_SetRoom();


	BossRush();
}

static void SetNextRoom()
{
	LogFunction();
}

void System_Event_Init()
{
	LogFunction();
	{
		BYTE payload[] =
		{
			0x41, 0x0F, 0xB6, 0x4E, 0x0D, //movzx ecx,byte ptr [r14+0D]
		};
		FUNC func = CreateFunction(InitSession, (appBaseAddr + 0x3F9D27), true, true, sizeof(payload));
		memcpy(func.sect0, payload, sizeof(payload));
		WriteJump((appBaseAddr + 0x3F9D22), func.addr);
	}
	{
		BYTE payload[] =
		{
			0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc1.exe+255A10
		};
		FUNC func = CreateFunction(LoadSavegame, (appBaseAddr + 0x44826), true, true, sizeof(payload));
		memcpy(func.sect0, payload, sizeof(payload));
		WriteCall(func.sect0, (appBaseAddr + 0x255A10));
		WriteJump((appBaseAddr + 0x44821), func.addr);
	}
	{
		BYTE sect0[] =
		{
			0x41, 0x89, 0xB8, 0x68, 0x24, 0x00, 0x00, //mov [r8+00002468],edi
		};
		FUNC func = CreateFunction(SetEquipment, (appBaseAddr + 0x2C3CB3), true, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteJump((appBaseAddr + 0x2C3CAC), func.addr, 2);
	}
	{
		BYTE payload[] =
		{
			0x89, 0x81, 0x74, 0x02, 0x00, 0x00, //mov [rcx+00000274],eax
		};
		FUNC func = CreateFunction(SetRoom, (appBaseAddr + 0x255D7B), true, true, sizeof(payload));
		memcpy(func.sect0, payload, sizeof(payload));
		WriteJump((appBaseAddr + 0x255D75), func.addr, 1);
	}
	{
		BYTE payload[] =
		{
			0x89, 0x8B, 0x8C, 0x02, 0x00, 0x00, //mov [rbx+0000028C],ecx
		};
		FUNC func = CreateFunction(SetNextRoom, (appBaseAddr + 0x3BD2D6), true, true, sizeof(payload));
		memcpy(func.sect0, payload, sizeof(payload));
		WriteJump((appBaseAddr + 0x3BD2D0), func.addr, 1);
	}
}
