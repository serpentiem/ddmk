#include "StyleSwitcher.h"

uint64 Game_StyleSwitcher_counter = 0;

PrivateStart;

byte8 * StyleControllerProxy    = 0;
byte8 * GunslingerGetStyleLevel = 0;
byte8 * VergilDynamicStyle      = 0;

void UpdateStyle(byte8 * baseAddr, uint32 index)
{
	//auto actor = System_Actor_GetActorId(baseAddr);

	//auto & character  = *(uint8   *)(baseAddr + 0x78);
	//auto & style      = *(uint32  *)(baseAddr + 0x6338);
	//auto & level      = *(uint32  *)(baseAddr + 0x6358);
	//auto & experience = *(float32 *)(baseAddr + 0x6364);

	//auto session = *(byte **)(appBaseAddr + 0xC90E30);
	//if (!session)
	//{
	//	return;
	//}
	//auto sessionLevel      = (uint32  *)(session + 0x11C);
	//auto sessionExperience = (float32 *)(session + 0x134);

	//if (!((character == CHAR_DANTE) || (character == CHAR_VERGIL)))
	//{
	//	return;
	//}

	//if (character == CHAR_VERGIL)
	//{
	//	switch (index)
	//	{
	//	case STYLE_DANTE_SWORDMASTER:
	//	case STYLE_DANTE_GUNSLINGER:
	//	case STYLE_DANTE_ROYALGUARD:
	//		index = STYLE_VERGIL_DARK_SLAYER;
	//		break;
	//	}
	//}

	//if (style == index)
	//{
	//	if (Config.Game.StyleSwitcher.noDoubleTap)
	//	{
	//		return;
	//	}
	//	index = STYLE_DANTE_QUICKSILVER;
	//}

	//if ((index == STYLE_DANTE_QUICKSILVER) && (actor != ACTOR_ONE))
	//{
	//	return;
	//}

	//if ((index == STYLE_DANTE_DOPPELGANGER) && Config.System.Actor.forceSingleActor)
	//{
	//	return;
	//}

	//// @Todo: Check if array for unlocked styles.

	//if (character == CHAR_DANTE)
	//{
	//	if (index == STYLE_DANTE_QUICKSILVER)
	//	{
	//		auto & unlock = *(bool *)(session + 0x5E);
	//		if (!unlock)
	//		{
	//			return;
	//		}
	//	}
	//	else if (index == STYLE_DANTE_DOPPELGANGER)
	//	{
	//		auto & unlock = *(bool *)(session + 0x5F);
	//		if (!unlock)
	//		{
	//			return;
	//		}
	//	}
	//}

	//if (actor == ACTOR_ONE)
	//{
	//	sessionLevel     [style] = level;
	//	sessionExperience[style] = experience;
	//}

	//level      = sessionLevel     [index];
	//experience = sessionExperience[index];
	//style      = index;

	//if ((index == STYLE_DANTE_SWORDMASTER) || (index == STYLE_DANTE_GUNSLINGER))
	//{
	//	System_Weapon_Dante_UpdateExpertise(baseAddr);
	//}

	////UpdateActor2Start:
	////{
	////	auto & baseAddr2 = System_Actor_actorBaseAddr[ACTOR_TWO];
	////	if (!baseAddr2)
	////	{
	////		goto UpdateActor2End;
	////	}
	////	auto & character2            = *(uint8  *)(baseAddr2 + 0x78  );
	////	auto & style2                = *(uint32 *)(baseAddr2 + 0x6338);
	////	auto & isControlledByPlayer2 = *(bool   *)(baseAddr2 + 0x6480);

	////	if (Config.System.Actor.forceSingleActor)
	////	{
	////		goto UpdateActor2End;
	////	}
	////	if (actor != ACTOR_ONE)
	////	{
	////		goto UpdateActor2End;
	////	}
	////	if (character != character2)
	////	{
	////		goto UpdateActor2End;
	////	}
	////	if ((index == STYLE_DANTE_QUICKSILVER) /*|| (index == STYLE_DANTE_DOPPELGANGER)*/)
	////	{
	////		goto UpdateActor2End;
	////	}
	////	if (!isControlledByPlayer2)
	////	{
	////		style2 = index;
	////		if ((index == STYLE_DANTE_SWORDMASTER) || (index == STYLE_DANTE_GUNSLINGER))
	////		{
	////			System_Weapon_Dante_UpdateExpertise(baseAddr2);
	////		}
	////	}
	////}
	////UpdateActor2End:

	//if (actor == ACTOR_ONE)
	//{
	//	System_HUD_updateStyleIcon = true;
	//}
	//Game_StyleSwitcher_counter++;
}

PrivateEnd;

void Game_StyleSwitcher_Controller()
{
	////uint8 actorCount = System_Actor_GetActorCount();
	////if (actorCount < 1)
	////{
	////	return;
	////}

	//// @Todo: Change to bindings.

	//uint8 commandId[] =
	//{
	//	CMD_MAP_SCREEN,
	//	CMD_FILE_SCREEN,
	//	CMD_ITEM_SCREEN,
	//	CMD_EQUIP_SCREEN,
	//};
	//static bool execute[MAX_ACTOR][5] = {};


	//// @Fix: GetButtonState or loop is broken. Style is updated for other actors as well even if only actor one initiates the switch.

	//// @Todo: Create helper;

	//auto count = System_Actor_GetActorCount();


	//for (uint8 actor = 0; actor < count; actor++)
	//{
	//	for (uint8 style = 0; style < 4; style++)
	//	{
	//		if (System_Input_GetButtonState(actor) & System_Input_GetBinding(commandId[style]))
	//		{
	//			if (execute[actor][style])
	//			{
	//				//UpdateStyle(System_Actor_actorBaseAddr[actor], style);
	//				execute[actor][style] = false;
	//			}
	//		}
	//		else
	//		{
	//			execute[actor][style] = true;
	//		}
	//	}










	//	if (Config.Game.Multiplayer.enable)
	//	{
	//		continue;
	//	}
	//	if ((System_Input_GetButtonState(actor) & System_Input_GetBinding(CMD_CHANGE_TARGET)) && (System_Input_GetButtonState(actor) & System_Input_GetBinding(CMD_DEFAULT_CAMERA)))
	//	{
	//		if (execute[actor][4])
	//		{
	//			//UpdateStyle(System_Actor_actorBaseAddr[actor], STYLE_DANTE_DOPPELGANGER);
	//			execute[actor][4] = false;
	//		}
	//	}
	//	else
	//	{
	//		execute[actor][4] = true;
	//	}
	//}
}





void Game_StyleSwitcher_Init()
{
	LogFunction();
	{
		byte8 sect0[] =
		{
			0x48, 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, //mov rcx,[dmc3.exe+C90E30]
			0x48, 0x85, 0xC9,                         //test rcx,rcx
			0x74, 0x07,                               //je short
			0x8B, 0x8B, 0x58, 0x63, 0x00, 0x00,       //mov ecx,[rbx+00006358]
			0xC3,                                     //ret
			0x8B, 0x89, 0x00, 0x00, 0x00, 0x00,       //mov ecx,[rcx+00000000]
			0xC3,                                     //ret
		};
		FUNC func = CreateFunction(0, 0, false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteAddress(func.sect0, (appBaseAddr + 0xC90E30), 7);
		*(dword *)(func.sect0 + 0x15) = (0x11C + (STYLE_DANTE_GUNSLINGER * 4));
		GunslingerGetStyleLevel = func.addr;
	}
	{
		byte8 sect0[] =
		{
			0x50,                                     //push rax
			0x56,                                     //push rsi
			0x48, 0x8B, 0x35, 0x00, 0x00, 0x00, 0x00, //mov rsi,[dmc3.exe+C90E30]
			0x48, 0x85, 0xF6,                         //test rsi,rsi
			0x74, 0x0C,                               //je short
			0x8B, 0x86, 0xA4, 0x01, 0x00, 0x00,       //mov eax,[rsi+000001A4]
			0x89, 0x81, 0x38, 0x63, 0x00, 0x00,       //mov [rcx+00006338],eax
			0x5E,                                     //pop rsi
			0x58,                                     //pop rax
		};
		FUNC func = CreateFunction(0, (appBaseAddr + 0x223D81), false, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteAddress((func.sect0 + 2), (appBaseAddr + 0xC90E30), 7);
		VergilDynamicStyle = func.addr;
	}
}

// @Todo: Update.

void Game_StyleSwitcher_Toggle(bool enable)
{
	Log("%s %u", FUNC_NAME, enable);
	if (enable)
	{
		Write<byte>((appBaseAddr + 0x1E8F98), 0xEB); // Bypass Character Check
		//WriteJump((appBaseAddr + 0x23D4B2), StyleControllerProxy);
		Write<byte>((appBaseAddr + 0x23B111), 0);
		Write<byte>((appBaseAddr + 0x23B15E), 0);
		Write<byte>((appBaseAddr + 0x23B1A2), 0);
		Write<byte>((appBaseAddr + 0x23B1E6), 0);
		// Gunslinger Fixes
		WriteCall((appBaseAddr + 0x204E38), GunslingerGetStyleLevel, 1);
		WriteCall((appBaseAddr + 0x205586), GunslingerGetStyleLevel, 1);
		WriteCall((appBaseAddr + 0x208A90), GunslingerGetStyleLevel, 1);
		WriteCall((appBaseAddr + 0x208F13), GunslingerGetStyleLevel, 1);
		WriteAddress((appBaseAddr + 0x1E6AAD), (appBaseAddr + 0x1E6AB3), 6 ); // Allow Charged Shot
		Write<byte>((appBaseAddr + 0x1E7F5F), 0xEB);                          // Allow Wild Stomp
		WriteAddress((appBaseAddr + 0x21607C), (appBaseAddr + 0x216082), 6 ); // Allow Charging
		// Force Style Updates
		WriteAddress((appBaseAddr + 0x1F87BB), (appBaseAddr + 0x1F87DC), 6);
		WriteAddress((appBaseAddr + 0x1F87C4), (appBaseAddr + 0x1F87DC), 6);
		WriteAddress((appBaseAddr + 0x1F87CD), (appBaseAddr + 0x1F87DC), 6);
		WriteAddress((appBaseAddr + 0x1F87D6), (appBaseAddr + 0x1F87DC), 6);
		WriteAddress((appBaseAddr + 0x1F880B), (appBaseAddr + 0x1F8A00), 6);
		WriteAddress((appBaseAddr + 0x1F8852), (appBaseAddr + 0x1F8A00), 6);
		WriteAddress((appBaseAddr + 0x1F8862), (appBaseAddr + 0x1F8A00), 5);
		WriteAddress((appBaseAddr + 0x1F886E), (appBaseAddr + 0x1F8A00), 6);
		WriteAddress((appBaseAddr + 0x1F89E1), (appBaseAddr + 0x1F8A00), 6);
		WriteAddress((appBaseAddr + 0x1F89FB), (appBaseAddr + 0x1F8A00), 5);
		WriteAddress((appBaseAddr + 0x1F8A07), (appBaseAddr + 0x1F8AAC), 6);
		WriteAddress((appBaseAddr + 0x1F8A7D), (appBaseAddr + 0x1F8AAC), 2);
		WriteAddress((appBaseAddr + 0x1F8AAA), (appBaseAddr + 0x1F8AAC), 2);
		WriteAddress((appBaseAddr + 0x1F8AC4), (appBaseAddr + 0x1F8AC6), 2);
		// Vergil Fixes
		WriteJump((appBaseAddr + 0x223D77), VergilDynamicStyle, 5); // Force dynamic style
		// @Audit: Should this go to Actor.cpp? Yup, Doppelganger fix.
		vp_memset((appBaseAddr + 0x221E50), 0x90, 8); // Update Actor Vergil; Disable linked actor base address reset.
	}
	else
	{
		Write<byte>((appBaseAddr + 0x1E8F98), 0x74);
		//WriteCall((appBaseAddr + 0x23D4B2), (appBaseAddr + 0x23B060));
		Write<byte>((appBaseAddr + 0x23B111), 1);
		Write<byte>((appBaseAddr + 0x23B15E), 1);
		Write<byte>((appBaseAddr + 0x23B1A2), 1);
		Write<byte>((appBaseAddr + 0x23B1E6), 1);
		{
			byte buffer[] =
			{
				0x8B, 0x8B, 0x58, 0x63, 0x00, 0x00, //mov ecx,[rbx+00006358]
			};
			vp_memcpy((appBaseAddr + 0x204E38), buffer, sizeof(buffer));
			vp_memcpy((appBaseAddr + 0x205586), buffer, sizeof(buffer));
			vp_memcpy((appBaseAddr + 0x208A90), buffer, sizeof(buffer));
			vp_memcpy((appBaseAddr + 0x208F13), buffer, sizeof(buffer));
		}
		WriteAddress((appBaseAddr + 0x1E6AAD), (appBaseAddr + 0x1E64A9), 6);
		Write<byte>((appBaseAddr + 0x1E7F5F), 0x74);
		WriteAddress((appBaseAddr + 0x21607C), (appBaseAddr + 0x216572), 6);
		WriteAddress((appBaseAddr + 0x1F87BB), (appBaseAddr + 0x1F8AC6), 6);
		WriteAddress((appBaseAddr + 0x1F87C4), (appBaseAddr + 0x1F8AAC), 6);
		WriteAddress((appBaseAddr + 0x1F87CD), (appBaseAddr + 0x1F8A00), 6);
		WriteAddress((appBaseAddr + 0x1F87D6), (appBaseAddr + 0x1F8AF8), 6);
		WriteAddress((appBaseAddr + 0x1F880B), (appBaseAddr + 0x1F8AF8), 6);
		WriteAddress((appBaseAddr + 0x1F8852), (appBaseAddr + 0x1F8AF8), 6);
		WriteAddress((appBaseAddr + 0x1F8862), (appBaseAddr + 0x1F8AF8), 5);
		WriteAddress((appBaseAddr + 0x1F886E), (appBaseAddr + 0x1F8AF8), 6);
		WriteAddress((appBaseAddr + 0x1F89E1), (appBaseAddr + 0x1F8AF8), 6);
		WriteAddress((appBaseAddr + 0x1F89FB), (appBaseAddr + 0x1F8AF8), 5);
		WriteAddress((appBaseAddr + 0x1F8A07), (appBaseAddr + 0x1F8AF8), 6);
		WriteAddress((appBaseAddr + 0x1F8A7D), (appBaseAddr + 0x1F8AF8), 2);
		WriteAddress((appBaseAddr + 0x1F8AAA), (appBaseAddr + 0x1F8AF8), 2);
		WriteAddress((appBaseAddr + 0x1F8AC4), (appBaseAddr + 0x1F8AF8), 2);
		{
			byte buffer[] =
			{
				0xC7, 0x81, 0x38, 0x63, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, //mov [rcx+00006338],00000002
			};
			vp_memcpy((appBaseAddr + 0x223D77), buffer, sizeof(buffer));
		}
		{
			byte buffer[] =
			{
				0x4D, 0x89, 0xB4, 0x24, 0x78, 0x64, 0x00, 0x00, //mov [r12+00006478],r14
			};
			vp_memcpy((appBaseAddr + 0x221E50), buffer, sizeof(buffer));
		}
	}
}
