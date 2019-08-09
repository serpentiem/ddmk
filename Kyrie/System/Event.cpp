#include "Event.h"

static void Session_Init()
{
	LogFunction();
	ArcadeStart:
	{
		if (!Config.Game.Arcade.enable)
		{
			goto ArcadeEnd;
		}
		BYTE * live = *(BYTE **)(appBaseAddr + 0xF59F00);
		if (!live)
		{
			goto ArcadeEnd;
		}
		uint32 & mission = *(uint32 *)(live + 0x150);
		uint32 & game    = *(uint32 *)(live + 0x1BC);
		uint32 & mode    = *(uint32 *)(live + 0x240);
		game    = Config.Game.Arcade.game;
		mission = Config.Game.Arcade.mission;
		mode    = Config.Game.Arcade.mode;

		BYTE * session = *(BYTE **)(appBaseAddr + 0xF59F10);
		if (!session)
		{
			goto ArcadeEnd;
		}
		float32 & hitPoints   = *(float32 *)(session + 0x78);
		float32 & magicPoints = *(float32 *)(session + 0x7C);

		uint8 & character = Config.Game.Arcade.character;
		if (character >= MAX_CHAR)
		{
			character = 0;
		}
		uint32 off[MAX_CHAR] =
		{
			0x168,
			0x270,
			0x360,
			0x45C,
			0x564,
		};
		BYTE * addr = (session + off[character]);
		{
			bool   * enable    =  (bool   *)(addr + 0   );
			DWORD  * expertise =  (DWORD  *)(addr + 0x18);
			uint32 & costume   = *(uint32 *)(addr + 0x38);
			memset(enable, 0, 8);
			memset(enable, 1, (character != CHAR_LADY) ? 6 : 5);
			memset(expertise, 0, 32);
			memset(expertise, 0xFF, 16);
			costume = Config.Game.Arcade.costume;
			if (costume >= MAX_COSTUME)
			{
				costume = 0;
			}
			if (((character == CHAR_TRISH) || (character == CHAR_LADY)) && (costume == 1) && (IsDLCInstalled(DLC_TRISH_LADY_COSTUMES) == false))
			{
				costume = 0;
				Log("Required DLC not installed. %u %u", character, DLC_TRISH_LADY_COSTUMES);
			}
		}
		switch (character)
		{
		case CHAR_DANTE:
		{
			bool   & enableFlush       = *(bool   *)(addr + 0x40);
			bool   & enableEnemyDash   = *(bool   *)(addr + 0x41);
			bool   & enableFlipper     = *(bool   *)(addr + 0x42);
			bool   & enableTrickster   = *(bool   *)(addr + 0x43);
			bool   & enableRoyalguard  = *(bool   *)(addr + 0x44);
			bool   & enableGunslinger  = *(bool   *)(addr + 0x45);
			bool   & enableSwordmaster = *(bool   *)(addr + 0x46);
			bool   & enableDarkSlayer  = *(bool   *)(addr + 0x47);
			bool   & enableGilgamesh   = *(bool   *)(addr + 0x48);
			bool   & enablePandora     = *(bool   *)(addr + 0x49);
			bool   & enableLucifer     = *(bool   *)(addr + 0x4A);
			uint32 * styleLevel        =  (uint32 *)(addr + 0x4C);
			memset((addr + 0x40), 0, 32);
			enableFlush                   = true;
			enableEnemyDash               = true;
			enableFlipper                 = true;
			enableTrickster               = true;
			enableRoyalguard              = true;
			enableGunslinger              = true;
			enableSwordmaster             = true;
			enableDarkSlayer              = true;
			enableGilgamesh               = true;
			enablePandora                 = true;
			enableLucifer                 = true;
			styleLevel[STYLE_SWORDMASTER] = 3;
			styleLevel[STYLE_GUNSLINGER ] = 3;
			styleLevel[STYLE_TRICKSTER  ] = 3;
			styleLevel[STYLE_ROYALGUARD ] = 3;
			break;
		}
		case CHAR_NERO:
		{
			bool  & enableTableHopper           = *(bool  *)(addr + 0x40);
			bool  & enableMaxAct                = *(bool  *)(addr + 0x43);
			uint8 & snatchLevel                 = *(uint8 *)(addr + 0x44);
			uint8 & additionalExceedCount       = *(uint8 *)(addr + 0x45);
			uint8 & additionalTableHopperCount  = *(uint8 *)(addr + 0x46);
			memset((addr + 0x40), 0, 8);
			enableTableHopper          = true;
			enableMaxAct               = true;
			snatchLevel                = 2;
			additionalExceedCount      = 2;
			additionalTableHopperCount = 2;
			break;
		}
		case CHAR_VERGIL:
		{
			bool  & enableFlush         = *(bool  *)(addr + 0x40);
			bool  & enableMillionStab   = *(bool  *)(addr + 0x41);
			uint8 & summonedSwordsLevel = *(uint8 *)(addr + 0x42);
			memset((addr + 0x40), 0, 20);
			enableFlush         = true;
			enableMillionStab   = true;
			summonedSwordsLevel = 2;
			break;
		}
		case CHAR_TRISH:
		{
			bool & enableSpark = *(bool *)(addr + 0x40);
			memset((addr + 0x40), 0, 32);
			enableSpark = true;
			break;
		}
		case CHAR_LADY:
		{
			uint8 & kalinaAnnChargeCount = *(uint8 *)(addr + 0x40);
			memset((addr + 0x40), 0, 16);
			kalinaAnnChargeCount = 3;
			break;
		}
		}
		hitPoints   = Config.Game.Arcade.hitPoints;
		magicPoints = Config.Game.Arcade.magicPoints;
	}
	ArcadeEnd:;
}

static void SetCharacter(BYTE * baseAddr)
{
	LogFunction();


	ArcadeStart:
	{
		if (!Config.Game.Arcade.enable)
		{
			goto ArcadeEnd;
		}


		uint8 & character = *(uint8 *)(baseAddr + 0x30);

		character = Config.Game.Arcade.character;






	}
	ArcadeEnd:;



}





__declspec(noinline) static void PseudoLog(const char * message, BYTE * origin)
//__declspec(noinline) static void PseudoLog()
{
	//LogFunction();


	//if (_stricmp(message, "rSoundRequest") == 0)
	//{
	//	Log("sound request found mon.");
	//}



	if (_stricmp(message, "aRoom400") == 0)
	{

		Log("room request mon");


	}






}






//BYTE * GetMapTableProxy = 0;



GetMapTable_t GetMapTable = 0;








void System_Event_Init()
{
	{
		BYTE sect0[] =
		{
			0x80, 0xBE, 0x83, 0x06, 0x00, 0x00, 0x00, //cmp byte ptr [esi+00000683],00
		};
		FUNC func = CreateFunction(Session_Init, (appBaseAddr + 0x7B42C), true, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteJump((appBaseAddr + 0x7B425), func.addr, 2);
	}
	{
		BYTE sect0[] =
		{
			0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, //mov ecx,[dmc4.exe+F2424C]
		};
		BYTE sect1[] =
		{
			0x56, //push esi
		};
		FUNC func = CreateFunction(SetCharacter, (appBaseAddr + 0x10C1F9), true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		*(BYTE **)(func.sect0 + 2)= (appBaseAddr + 0xF2424C);
		WriteJump((appBaseAddr + 0x10C1F3), func.addr, 1);
	}



	{
		BYTE sect0[] =
		{
			0x57,                   //push edi
			0x8B, 0x7C, 0x24, 0x08, //mov edi,[esp+08]
		};
		BYTE sect1[] =
		{
			0x8B, 0x44, 0x24, 0x28, //mov eax,[esp+28]
			0x8B, 0x4C, 0x24, 0x2C, //mov ecx,[esp+2C]
			0x50,                   //push eax
			0x51,                   //push ecx
		};
		FUNC func = CreateFunction(PseudoLog, (appBaseAddr + 0x5F1545), true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteJump((appBaseAddr + 0x5F1540), func.addr);

		//Log("PseudoProxy %X", func.addr);





		/*
		dmc4.exe+5F1540 - 57                    - push edi
		dmc4.exe+5F1541 - 8B 7C 24 08           - mov edi,[esp+08]
		dmc4.exe+5F1545 - 85 FF                 - test edi,edi
		dmc4.exe+5F1547 - 75 04                 - jne dmc4.exe+5F154D

		*/

	}




	{






		/*
		dmc4.exe+10C1F3 - 8B 0D 4C423201        - mov ecx,[dmc4.exe+F2424C] { (0019D858) }
		dmc4.exe+10C1F9 - 68 FFFF0000           - push 0000FFFF { 65535 }

		*/



	}



	{
		BYTE sect1[] =
		{
			0x83, 0xEC, 0x08,             //sub esp,08
			0x51,                         //push ecx
			0x56,                         //push esi
			0x57,                         //push edi
			0xB9, 0x02, 0x00, 0x00, 0x00, //mov ecx,00000002
			0x8D, 0x74, 0x24, 0x38,       //lea esi,[esp+38]
			0x8D, 0x7C, 0x24, 0x0C,       //lea edi,[esp+0C]
			0xF3, 0xA5,                   //repe movsd
			0x5F,                         //pop edi
			0x5E,                         //pop esi
			0x59,                         //pop ecx
			0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc4.exe+5F1540
			0x83, 0xC4, 0x08,             //add esp,08
		};
		FUNC func = CreateFunction(0, 2, true, false, 0, sizeof(sect1));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteCall((func.sect1 + 0x18), (appBaseAddr + 0x5F1540));
		GetMapTable = (GetMapTable_t)func.addr;
	}


	Log("GetMapTable %X", GetMapTable);







}

void System_Event_ToggleSkipIntro(bool enable)
{
	LogFunctionBool(enable);
	if (enable)
	{
		// Replace autosave menu funcAddr with start menu funcAddr.
		Write<BYTE *>((appBaseAddr + 0x10B1E2), (appBaseAddr + 0xC27DC0));
		Write<BYTE *>((appBaseAddr + 0x10B248), (appBaseAddr + 0xC27DC0));
	}
	else
	{
		Write<BYTE *>((appBaseAddr + 0x10B1E2), (appBaseAddr + 0xC1FF20));
		Write<BYTE *>((appBaseAddr + 0x10B248), (appBaseAddr + 0xC1FF20));
	}
}
