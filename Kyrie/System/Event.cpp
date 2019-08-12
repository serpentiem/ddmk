#include "Event.h"

GetMapTable_t GetMapTable = 0;

static void InitSession()
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

static void SetMissionTableAndPosition(BYTE ** table, uint32 * position)
{
	LogFunction();
	ArcadeStart:
	{
		if (!Config.Game.Arcade.enable)
		{
			goto ArcadeEnd;
		}
		if (!Config.Game.Arcade.ignoreRoom)
		{
			char room[64];
			snprintf(room, sizeof(room), "aRoom%03u", Config.Game.Arcade.room);
			*table = GetMapTable(room, (appBaseAddr + 0xC9C000));
		}
		if (!Config.Game.Arcade.ignorePosition)
		{
			*position = Config.Game.Arcade.position;
		}
	}
	ArcadeEnd:
	Log("&table    %X", table);
	Log("table     %X", *table);
	Log("&position %X", position);
	Log("position  %u", *position);
}

void System_Event_Init()
{
	LogFunction();
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
	{
		BYTE sect0[] =
		{
			0x80, 0xBE, 0x83, 0x06, 0x00, 0x00, 0x00, //cmp byte ptr [esi+00000683],00
		};
		FUNC func = CreateFunction(InitSession, (appBaseAddr + 0x7B42C), true, true, sizeof(sect0));
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
		DWORD off[21] =
		{
			0x5E5661, // done
			0x5E57F1, // done
			0x5E5AAE, // done
			0x5E5C21, // done
			0x5E5E01, // done
			0x5E5FC1, // done
			0x5E6161, // done
			0x5E62D1, // done
			0x5E64B1, // done
			0x5E6631, // done
			0x5E67B1, // done
			0x5E6921, // done
			0x5E6AF1, // done
			0x5E6CA1, // done
			0x5E6E51, // done
			0x5E7031, // done
			0x5E71CE, // done
			0x5E739E, // done
			0x5E751E, // done
			0x5E766E, // done
			0x5E5381, // done
		};
		DWORD funcAddrOff[21] =
		{
			0xF5D474, // done
			0xF5D5B4, // done
			0xF5D614, // done
			0xF5D3D4, // done
			0xF5D374, // done
			0xF5D7F4, // done
			0xF5D754, // done
			0xF5DC78, // done
			0xF5D1F4, // done
			0xF5DD38, // done
			0xF5D654, // done
			0xF5D1D4, // done
			0xF5DC78, // done
			0xF5DC78, // done
			0xF5D734, // done
			0xF5D7F4, // done
			0xF5DC98, // done
			0xF5D5F4, // done
			0xF5DDD8, // done
			0xF5D5F4, // done
			0xF5DA14, // done
		};
		BYTE sect0[] =
		{
			0x68, 0x00, 0x00, 0x00, 0x00, //push
		};
		BYTE sect1[] =
		{
			0x83, 0xEC, 0x08,       //sub esp,08
			0x8D, 0x44, 0x24, 0x2C, //lea eax,[esp+2C]
			0x89, 0x04, 0x24,       //mov [esp],eax
			0x8D, 0x44, 0x24, 0x30, //lea eax,[esp+30]
			0x89, 0x44, 0x24, 0x04, //mov [esp+04],eax
		};
		for (uint8 i = 0; i < countof(off); i++)
		{
			FUNC func = CreateFunction(SetMissionTableAndPosition, (appBaseAddr + off[i] + 5), true, true, sizeof(sect0), sizeof(sect1));
			memcpy(func.sect0, sect0, sizeof(sect0));
			*(BYTE **)(func.sect0 + 1) = (appBaseAddr + funcAddrOff[i]);
			memcpy(func.sect1, sect1, sizeof(sect1));
			WriteJump((appBaseAddr + off[i]), func.addr);
		}
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
