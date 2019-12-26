
// @Todo: Check cache dependency.

#include "StyleSwitcher.h"





typedef void(* UpdateIcon_t)();

UpdateIcon_t UpdateIcon = 0;

byte * StyleControllerProxy    = 0;
byte * GunslingerGetStyleLevel = 0;
byte * VergilDynamicStyle      = 0;





bool updateIcon = false;










__declspec(noinline) static void UpdateStyle(byte * baseAddr, uint32 styleId)
{

	// @Research: Check references.

	uint8     character  = *(uint8   *)(baseAddr + 0x78);
	uint32  & style      = *(uint32  *)(baseAddr + 0x6338);
	uint32  & level      = *(uint32  *)(baseAddr + 0x6358);
	float32 & experience = *(float32 *)(baseAddr + 0x6364);

	byte * session = *(byte **)(appBaseAddr + 0xC90E30);
	if (!session)
	{
		return;
	}
	uint32  * sessionLevel      = (uint32  *)(session + 0x11C);
	float32 * sessionExperience = (float32 *)(session + 0x134);

	uint8 actorId    = System_Actor_GetActorId(baseAddr);



	//uint8 actorCount = GetActorCount();


	// @Todo: Add section.

	bool unleash = ((character == CHAR_DANTE) || (character == CHAR_VERGIL)) ? true : false;
	if (!unleash)
	{
		return;
	}















	if (character == CHAR_VERGIL)
	{
		switch (styleId)
		{
		case STYLE_SWORDMASTER:
		case STYLE_GUNSLINGER:
		case STYLE_ROYALGUARD:
			styleId = STYLE_DARK_SLAYER;
			break;
		}
	}


	if (style == styleId)
	{
		if (Config.Game.StyleSwitcher.noDoubleTap)
		{
			return;
		}
		styleId = STYLE_QUICKSILVER;
	}



	// @Research: If Quicksilver is used by anyone other than ACTOR_ONE, it freezes that actor.

	if ((actorId != ACTOR_ONE) && (styleId == STYLE_QUICKSILVER))
	{
		//styleId = STYLE_DOPPELGANGER;
		return;
	}




	





	// @Todo:
	// Fixing style id issue will also fix style level issue






	//if (character == CHAR_DANTE)
	//{
	//	if (styleId == STYLE_QUICKSILVER)
	//	{
	//		bool unlock = *(bool *)(session + 0x5E);
	//		if (!unlock)
	//		{
	//			return;
	//		}
	//	}
	//	else if (styleId == STYLE_DOPPELGANGER)
	//	{
	//		bool unlock = *(bool *)(session + 0x5F);
	//		if (!unlock)
	//		{
	//			return;
	//		}
	//	}
	//}

	//// @Todo: Merge!


	if ((styleId == STYLE_DOPPELGANGER) && Config.System.Actor.forceSingleActor)
	{
		return;
	}







	if (actorId == ACTOR_ONE)
	{
		sessionLevel[style] = level;
		sessionExperience[style] = experience;
	}






	level      = sessionLevel     [styleId];
	experience = sessionExperience[styleId];
	style      = styleId;




	// @Todo: Block Quicksilver and Doppelganger.
	
	UpdateStyle2Start:
	{
		if (actorId != ACTOR_ONE)
		{
			goto UpdateStyle2End;
		}
		if (!System_Actor_actorBaseAddr[ACTOR_TWO])
		{
			goto UpdateStyle2End;
		}
		uint32 & style2                = *(uint32 *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x6338);
		bool   & isControlledByPlayer2 = *(bool   *)(System_Actor_actorBaseAddr[ACTOR_TWO] + 0x6480);
		if (!isControlledByPlayer2)
		{
			style2 = styleId;
		}
	}
	UpdateStyle2End:
















	//if (character == CHAR_DANTE)
	//{
	//	if ((styleId == STYLE_SWORDMASTER) || (styleId == STYLE_GUNSLINGER))
	//	{
	//		UpdateExpertise(baseAddr);



	//		// @Todo: Actor two also requires dante check!

	//		if (actorId == ACTOR_ONE)
	//		{
	//			for (uint8 actor = ACTOR_TWO; actor < actorCount; actor++)
	//			{
	//				bool isControlledByPlayer = *(bool *)(actorBaseAddr[actor] + 0x6480);
	//				if (!isControlledByPlayer)
	//				{
	//					UpdateExpertise(actorBaseAddr[actor]);
	//				}
	//			}
	//		}
	//	}
	//}

	if (actorId == ACTOR_ONE)
	{
		updateIcon = true;
	}
}

dword UpdateIconThread(void * parameter)
{
	LogFunction();
	do
	{
		LoopStart:
		{
			if (!updateIcon)
			{
				goto LoopEnd;
			}
			if (!HUD_IsVisible())
			{
				goto LoopEnd;
			}
			updateIcon = false;
			UpdateIcon();
		}
		LoopEnd:
		Sleep(10);
	}
	while (true);
	return 1;
}

static void StyleController()
{
	uint8 actorCount = System_Actor_GetActorCount();
	if (actorCount < 1)
	{
		return;
	}
	uint8 commandId[] =
	{
		CMD_MAP_SCREEN,
		CMD_FILE_SCREEN,
		CMD_ITEM_SCREEN,
		CMD_EQUIP_SCREEN,
	};
	static bool execute[MAX_ACTOR][5] = {};


	// @Fix: GetButtonState or loop is broken. Style is updated for other actors as well even if only actor one initiates the switch.


	for (uint8 actor = 0; actor < actorCount; actor++)
	{
		for (uint8 style = 0; style < 4; style++)
		{
			if (System_Input_GetButtonState(actor) & System_Input_GetBinding(commandId[style]))
			{
				if (execute[actor][style])
				{
					UpdateStyle(System_Actor_actorBaseAddr[actor], style);
					execute[actor][style] = false;
				}
			}
			else
			{
				execute[actor][style] = true;
			}
		}
		if (Config.Game.Multiplayer.enable)
		{
			continue;
		}
		if ((System_Input_GetButtonState(actor) & System_Input_GetBinding(CMD_CHANGE_TARGET)) && (System_Input_GetButtonState(actor) & System_Input_GetBinding(CMD_DEFAULT_CAMERA)))
		{
			if (execute[actor][4])
			{
				UpdateStyle(System_Actor_actorBaseAddr[actor], STYLE_DOPPELGANGER);
				execute[actor][4] = false;
			}
		}
		else
		{
			execute[actor][4] = true;
		}
	}
}

void Game_StyleSwitcher_Init()
{
	LogFunction();
	{
		byte sect1[] =
		{
			0x4C, 0x8B, 0x25, 0x00, 0x00, 0x00, 0x00,       //mov r12,[dmc3.exe+CF2680]
			0x49, 0x8D, 0x8C, 0x24, 0x80, 0x3B, 0x00, 0x00, //lea rcx,[r12+00003B80]
			0xE8, 0x00, 0x00, 0x00, 0x00,                   //call dmc3.exe+897B0
			0x49, 0x8D, 0x8C, 0x24, 0x80, 0x3B, 0x00, 0x00, //lea rcx,[r12+00003B80]
			0xE8, 0x00, 0x00, 0x00, 0x00,                   //call dmc3.exe+89450
			0x48, 0x31, 0xC0,                               //xor rax,rax
			0xB9, 0x80, 0x07, 0x00, 0x00,                   //mov ecx,00000780
			0x49, 0x8D, 0xBC, 0x24, 0x80, 0x3B, 0x00, 0x00, //lea rdi,[r12+00003B80]
			0xF3, 0xAA,                                     //repe stosb
			0x49, 0x8D, 0x8C, 0x24, 0x80, 0x3B, 0x00, 0x00, //lea rcx,[r12+00003B80]
			0xE8, 0x00, 0x00, 0x00, 0x00,                   //call dmc3.exe+89270
			0x48, 0x8B, 0x05, 0x00, 0x00, 0x00, 0x00,       //mov rax,[dmc3.exe+C90E28]
			0x48, 0x8B, 0x40, 0x18,                         //mov rax,[rax+18]
			0x8B, 0x80, 0x38, 0x63, 0x00, 0x00,             //mov eax,[rax+00006338]
			0x48, 0x8D, 0x0D, 0x00, 0x00, 0x00, 0x00,       //lea rcx,[dmc3.exe+4E9070]
			0x0F, 0xB6, 0x04, 0x08,                         //movzx eax,byte ptr [rax+rcx]
			0x41, 0x88, 0x84, 0x24, 0x0E, 0x69, 0x00, 0x00, //mov [r12+0000690E],al
			0x00, 0xC0,                                     //add al,al
			0x49, 0x8B, 0x4C, 0x24, 0x60,                   //mov rcx,[r12+60]
			0x8D, 0x50, 0x12,                               //lea edx,[rax+12]
			0x48, 0x8B, 0xD8,                               //mov rbx,rax
			0xE8, 0x00, 0x00, 0x00, 0x00,                   //call dmc3.exe+16FBF0
			0x49, 0x8B, 0x4C, 0x24, 0x60,                   //mov rcx,[r12+60]
			0x8D, 0x53, 0x13,                               //lea edx,[rbx+13]
			0x48, 0x8B, 0xD8,                               //mov rbx,rax
			0xE8, 0x00, 0x00, 0x00, 0x00,                   //call dmc3.exe+16FBF0
			0x49, 0x8D, 0x8C, 0x24, 0x80, 0x3B, 0x00, 0x00, //lea rcx,[r12+00003B80]
			0x48, 0x8B, 0xD0,                               //mov rdx,rax
			0x4C, 0x8B, 0xC3,                               //mov r8,rbx
			0xE8, 0x00, 0x00, 0x00, 0x00,                   //call dmc3.exe+89960
			0x49, 0x8D, 0x8C, 0x24, 0x80, 0x3B, 0x00, 0x00, //lea rcx,[r12+00003B80]
			0xBA, 0x01, 0x00, 0x00, 0x00,                   //mov edx,00000001
			0xE8, 0x00, 0x00, 0x00, 0x00,                   //call dmc3.exe+89E30
		};
		FUNC func = CreateFunction(0, 0, true, true, 0, sizeof(sect1));
		memcpy(func.sect1, sect1, sizeof(sect1));
		WriteAddress (func.sect1, (appBaseAddr + 0xCF2680), 7);
		WriteCall    ((func.sect1 + 0xF), (appBaseAddr + 0x897B0));
		WriteCall    ((func.sect1 + 0x1C), (appBaseAddr + 0x89450));
		WriteCall    ((func.sect1 + 0x3B), (appBaseAddr + 0x89270));
		WriteAddress ((func.sect1 + 0x40), (appBaseAddr + 0xC90E28), 7);
		WriteAddress ((func.sect1 + 0x51), (appBaseAddr + 0x4E9070), 7);
		WriteCall    ((func.sect1 + 0x71), (appBaseAddr + 0x16FBF0));
		WriteCall    ((func.sect1 + 0x81), (appBaseAddr + 0x16FBF0));
		WriteCall    ((func.sect1 + 0x94), (appBaseAddr + 0x89960));
		WriteCall    ((func.sect1 + 0xA6), (appBaseAddr + 0x89E30));
		UpdateIcon = (UpdateIcon_t)func.addr;
	}
	{
		byte sect0[] =
		{
			0xE8, 0x00, 0x00, 0x00, 0x00, //call dmc3.exe+23B060
		};
		FUNC func = CreateFunction(StyleController, (appBaseAddr + 0x23D4B7), true, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		WriteCall(func.sect0, (appBaseAddr + 0x23B060));
		StyleControllerProxy = func.addr;
	}
	{
		byte sect0[] =
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
		*(dword *)(func.sect0 + 0x15) = (0x11C + (STYLE_GUNSLINGER * 4));
		GunslingerGetStyleLevel = func.addr;
	}
	{
		byte sect0[] =
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



	CreateThread(0, 4096, UpdateIconThread, 0, 0, 0);









}

void Game_StyleSwitcher_Toggle(bool enable)
{
	Log("%s %u", FUNC_NAME, enable);
	if (enable)
	{
		Write<byte>((appBaseAddr + 0x1E8F98), 0xEB); // Bypass Character Check
		WriteJump((appBaseAddr + 0x23D4B2), StyleControllerProxy);
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
		// @Audit: Should this go to Actor.cpp?
		vp_memset((appBaseAddr + 0x221E50), 0x90, 8);               // Disable Doppelganger base address reset
	}
	else
	{
		Write<byte>((appBaseAddr + 0x1E8F98), 0x74);
		WriteCall((appBaseAddr + 0x23D4B2), (appBaseAddr + 0x23B060));
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
