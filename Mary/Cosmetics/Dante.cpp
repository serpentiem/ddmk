#include "Dante.h"

ApplyDefaultModelAttributes_t ApplyDefaultModelAttributes = 0;
ApplyBeowulfModelAttributes_t ApplyBeowulfModelAttributes = 0;

void Cosmetics_Dante_Init()
{
	LogFunction();
	{
		byte sect1[] =
		{
			0x48, 0x8B, 0xF1,                         //mov rsi,rcx
			0x48, 0x8D, 0x8E, 0x00, 0x02, 0x00, 0x00, //lea rcx,[rsi+00000200]
			0xE8, 0x00, 0x00, 0x00, 0x00,             //call dmc3.exe+89DE0
			0x48, 0x8B, 0xC8,                         //mov rcx,rax
			0xBA, 0x03, 0x00, 0x00, 0x00,             //mov edx,00000003
			0xE8, 0x00, 0x00, 0x00, 0x00,             //call dmc3.exe+2F74E0
			0x48, 0x8D, 0x8E, 0x00, 0x02, 0x00, 0x00, //lea rcx,[rsi+00000200]
			0xE8, 0x00, 0x00, 0x00, 0x00,             //call dmc3.exe+89DE0
			0x48, 0x8B, 0xC8,                         //mov rcx,rax
			0xBA, 0x04, 0x00, 0x00, 0x00,             //mov edx,00000004
			0xE8, 0x00, 0x00, 0x00, 0x00,             //call dmc3.exe+2F7350
			0x48, 0x8D, 0x8E, 0x00, 0x02, 0x00, 0x00, //lea rcx,[rsi+00000200]
			0xE8, 0x00, 0x00, 0x00, 0x00,             //call dmc3.exe+89DE0
			0x48, 0x8B, 0xC8,                         //mov rcx,rax
			0xBA, 0x05, 0x00, 0x00, 0x00,             //mov edx,00000005
			0xE8, 0x00, 0x00, 0x00, 0x00,             //call dmc3.exe+2F7350
			0x48, 0x8D, 0x8E, 0x00, 0x02, 0x00, 0x00, //lea rcx,[rsi+00000200]
			0xE8, 0x00, 0x00, 0x00, 0x00,             //call dmc3.exe+89DE0
			0x48, 0x8B, 0xC8,                         //mov rcx,rax
			0xBA, 0x06, 0x00, 0x00, 0x00,             //mov edx,00000006
			0xE8, 0x00, 0x00, 0x00, 0x00,             //call dmc3.exe+2F74E0
		};
		FUNC func = CreateFunction(0, 0, true, true, 0, sizeof(sect1));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteCall((func.sect1 + 0xA), (appBaseAddr + 0x89DE0));
		WriteCall((func.sect1 + 0x17), (appBaseAddr + 0x2F74E0));
		WriteCall((func.sect1 + 0x23), (appBaseAddr + 0x89DE0));
		WriteCall((func.sect1 + 0x30), (appBaseAddr + 0x2F7350));
		WriteCall((func.sect1 + 0x3C), (appBaseAddr + 0x89DE0));
		WriteCall((func.sect1 + 0x49), (appBaseAddr + 0x2F7350));
		WriteCall((func.sect1 + 0x55), (appBaseAddr + 0x89DE0));
		WriteCall((func.sect1 + 0x62), (appBaseAddr + 0x2F74E0));
		ApplyDefaultModelAttributes = (ApplyDefaultModelAttributes_t)func.addr;
	}
	{
		byte sect1[] =
		{
			0x48, 0x8B, 0xF1,                         //mov rsi,rcx
			0x48, 0x8D, 0x8E, 0x00, 0x02, 0x00, 0x00, //lea rcx,[rsi+00000200]
			0xE8, 0x00, 0x00, 0x00, 0x00,             //call dmc3.exe+89DE0
			0x48, 0x8B, 0xC8,                         //mov rcx,rax
			0xBA, 0x03, 0x00, 0x00, 0x00,             //mov edx,00000003
			0xE8, 0x00, 0x00, 0x00, 0x00,             //call dmc3.exe+2F7350
			0x48, 0x8D, 0x8E, 0x00, 0x02, 0x00, 0x00, //lea rcx,[rsi+00000200]
			0xE8, 0x00, 0x00, 0x00, 0x00,             //call dmc3.exe+89DE0
			0x48, 0x8B, 0xC8,                         //mov rcx,rax
			0xBA, 0x04, 0x00, 0x00, 0x00,             //mov edx,00000004
			0xE8, 0x00, 0x00, 0x00, 0x00,             //call dmc3.exe+2F74E0
			0x48, 0x8D, 0x8E, 0x00, 0x02, 0x00, 0x00, //lea rcx,[rsi+00000200]
			0xE8, 0x00, 0x00, 0x00, 0x00,             //call dmc3.exe+89DE0
			0x48, 0x8B, 0xC8,                         //mov rcx,rax
			0xBA, 0x05, 0x00, 0x00, 0x00,             //mov edx,00000005
			0xE8, 0x00, 0x00, 0x00, 0x00,             //call dmc3.exe+2F74E0
			0x48, 0x8D, 0x8E, 0x00, 0x02, 0x00, 0x00, //lea rcx,[rsi+00000200]
			0xE8, 0x00, 0x00, 0x00, 0x00,             //call dmc3.exe+89DE0
			0x48, 0x8B, 0xC8,                         //mov rcx,rax
			0xBA, 0x06, 0x00, 0x00, 0x00,             //mov edx,00000006
			0xE8, 0x00, 0x00, 0x00, 0x00,             //call dmc3.exe+2F7350
		};
		FUNC func = CreateFunction(0, 0, true, true, 0, sizeof(sect1));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteCall((func.sect1 + 0xA), (appBaseAddr + 0x89DE0));
		WriteCall((func.sect1 + 0x17), (appBaseAddr + 0x2F7350));
		WriteCall((func.sect1 + 0x23), (appBaseAddr + 0x89DE0));
		WriteCall((func.sect1 + 0x30), (appBaseAddr + 0x2F74E0));
		WriteCall((func.sect1 + 0x3C), (appBaseAddr + 0x89DE0));
		WriteCall((func.sect1 + 0x49), (appBaseAddr + 0x2F74E0));
		WriteCall((func.sect1 + 0x55), (appBaseAddr + 0x89DE0));
		WriteCall((func.sect1 + 0x62), (appBaseAddr + 0x2F7350));
		ApplyBeowulfModelAttributes = (ApplyBeowulfModelAttributes_t)func.addr;
	}
}

void Cosmetics_Dante_Beowulf_LiveUpdate()
{
	LogFunction();
	if (Config.Cosmetics.Dante.hideBeowulf)
	{
		if (ActorAvailable())
		{
			if (!System_Actor_enableArrayExtension)
			{
				byte * baseAddr = *(byte **)(appBaseAddr + 0xC90E28);
				baseAddr = *(byte **)(baseAddr + 0x18);
				uint8 character = *(uint8 *)(baseAddr + 0x78);
				if (character == CHAR_DANTE)
				{
					ApplyDefaultModelAttributes(baseAddr);
				}
			}
			else
			{
				for (uint8 actor = 0; actor < GetActorCount(); actor++)
				{
					uint8 character = *(uint8 *)(actorBaseAddr[actor] + 0x78);
					if (character == CHAR_DANTE)
					{
						ApplyDefaultModelAttributes(actorBaseAddr[actor]);
					}
				}
			}
		}
	}
	else
	{
		if (ActorAvailable())
		{
			if (!System_Actor_enableArrayExtension)
			{
				byte * baseAddr = *(byte **)(appBaseAddr + 0xC90E28);
				baseAddr = *(byte **)(baseAddr + 0x18);
				uint8 character = *(uint8 *)(baseAddr + 0x78);
				if (character == CHAR_DANTE)
				{
					uint8 * equipment = (uint8 *)(baseAddr + 0x6498);
					for (uint8 slot = 0; slot < 2; slot++)
					{
						if (equipment[slot] == WEAPON_BEOWULF)
						{
							ApplyBeowulfModelAttributes(baseAddr);
						}
					}
				}
			}
			else
			{
				for (uint8 actor = 0; actor < GetActorCount(); actor++)
				{
					uint8 character = *(uint8 *)(actorBaseAddr[actor] + 0x78);
					if (character == CHAR_DANTE)
					{
						if (!Config.Game.WeaponSwitcher.enable)
						{
							uint8 * equipment = (uint8 *)(actorBaseAddr[actor] + 0x6498);
							for (uint8 slot = 0; slot < 2; slot++)
							{
								if (equipment[slot] == WEAPON_BEOWULF)
								{
									ApplyBeowulfModelAttributes(actorBaseAddr[actor]);
								}
							}
						}
						else
						{
							uint8 selectedWeapon = *(uint8 *)(actorBaseAddr[actor] + 0x6490);
							uint8 * equipment = (uint8 *)(actorBaseAddr[actor] + 0x6498);
							if (equipment[selectedWeapon] == WEAPON_BEOWULF)
							{
								ApplyBeowulfModelAttributes(actorBaseAddr[actor]);
							}
						}
					}
				}
			}
		}
	}
}

void Cosmetics_Dante_ToggleHideBeowulf(bool enable)
{
	Log("%s %u", FUNC_NAME, enable);
	if (enable)
	{
		WriteAddress((appBaseAddr + 0x22968A), (appBaseAddr + 0x22968C), 2); // Model
		WriteAddress((appBaseAddr + 0x214BDA), (appBaseAddr + 0x214BE0), 6); // Attributes
	}
	else
	{
		WriteAddress((appBaseAddr + 0x22968A), (appBaseAddr + 0x2296BD), 2);
		WriteAddress((appBaseAddr + 0x214BDA), (appBaseAddr + 0x214CB9), 6);
	}
	Cosmetics_Dante_Beowulf_LiveUpdate();
}
