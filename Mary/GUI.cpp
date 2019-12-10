#include "GUI.h"

enum FONT_
{
	FONT_DEFAULT,
	FONT_OVERLAY_8,
	FONT_OVERLAY_16,
	FONT_OVERLAY_32,
	FONT_OVERLAY_64,
	FONT_OVERLAY_128,
};

enum TAB_
{
	TAB_GAME,
	TAB_COSMETICS,
	TAB_SYSTEM,
	TAB_TOOLS,
	TAB_DEBUG,
	MAX_TAB,
	TAB_VOID,
};

bool debug = false;

uint8 activeTab = TAB_VOID;

ImVec2 GUI_Game_size          = ImVec2(500, 500);
ImVec2 GUI_Cosmetics_size     = ImVec2(300, 578);
ImVec2 GUI_System_size        = ImVec2(300, 418);
ImVec2 GUI_Tools_size         = ImVec2(300, 300);
ImVec2 GUI_Debug_size         = ImVec2(300, 300);
ImVec2 GUI_Teleporter_size    = ImVec2(300, 300);
ImVec2 GUI_CacheStats_size    = ImVec2(300, 300);
ImVec2 GUI_Documentation_size = ImVec2(700, 500);

bool GUI_Teleporter_show    = false;
bool GUI_Documentation_show = false;

uint32 GUI_Overlay_x = 0;
uint32 GUI_Overlay_y = 0;

static void BuildFonts()
{
	ImGuiIO & io = ImGui::GetIO();
	io.Fonts->AddFontDefault();
	char overlayFont[512];
	{
		char buffer[64];
		GetWindowsDirectoryA(buffer, sizeof(buffer));
		snprintf(overlayFont, sizeof(overlayFont), "%s\\Fonts\\consola.ttf", buffer);
	}
	io.Fonts->AddFontFromFileTTF(overlayFont, 8);
	io.Fonts->AddFontFromFileTTF(overlayFont, 16);
	io.Fonts->AddFontFromFileTTF(overlayFont, 32);
	io.Fonts->AddFontFromFileTTF(overlayFont, 64);
	io.Fonts->AddFontFromFileTTF(overlayFont, 128);
	io.Fonts->Build();
}

void GUI_Game_Arcade()
{
	GUI_SECTION_HEADER_START(Game.Arcade);
	if (Config.Game.Arcade.enable)
	{
		Game_Arcade_Toggle(Config.Game.Arcade.enable);
	}
	else
	{
		Game_Arcade_Toggle(DefaultConfig.Game.Arcade.enable);
	}
	GUI_SECTION_HEADER_END(Game.Arcade);
	ImGui::PushItemWidth(200);
	GUI_Combo<uint32>
	(
		Locale.Game.Arcade.Mission.label,
		Locale.Game.Arcade.Mission.items,
		countof(Locale.Game.Arcade.Mission.items),
		Config.Game.Arcade.mission
	);
	if ((Config.Game.Arcade.mission != 0) && (Config.Game.Arcade.mission != 21))
	{


		GUI_Combo<uint32>
		(
			Locale.Game.Arcade.Mode.label,
			Locale.Game.Arcade.Mode.items,
			countof(Locale.Game.Arcade.Mode.items),
			Config.Game.Arcade.mode
		);








		//if (GUI_Combo<uint32>
		//(
		//	Locale.Game.Arcade.Mode.label,
		//	Locale.Game.Arcade.Mode.items,
		//	countof(Locale.Game.Arcade.Mode.items),
		//	modeIndex,
		//	0,
		//	false
		//))
		//{
		//	Config.Game.Arcade.mode = Game_Arcade_modeMap[modeIndex];
		//	SaveConfig();
		//}

		//if (debug)
		//{
		//	ImGui::Text("index   %u", modeIndex);
		//	ImGui::Text("true id %u", Config.Game.Arcade.mode);
		//}


		GUI_InputEx(Locale.Game.Arcade.room,     Config.Game.Arcade.room    );
		ImGui::SameLine();
		GUI_Checkbox(Locale.Game.Arcade.ignoreRoom, Config.Game.Arcade.ignoreRoom);
		GUI_InputEx(Locale.Game.Arcade.position, Config.Game.Arcade.position);
		ImGui::SameLine();
		GUI_Checkbox(Locale.Game.Arcade.ignorePosition, Config.Game.Arcade.ignorePosition);
	}
	else if (Config.Game.Arcade.mission == 21)
	{
		GUI_Combo<uint8>
		(
			Locale.Game.Arcade.BloodyPalace.Floor.label,
			Locale.Game.Arcade.BloodyPalace.Floor.items,
			countof(Locale.Game.Arcade.BloodyPalace.Floor.items),
			Config.Game.Arcade.BloodyPalace.floor
		);
	}
	GUI_Combo<uint8>
	(
		Locale.Game.Arcade.Character.label,
		Locale.Game.Arcade.Character.items,
		countof(Locale.Game.Arcade.Character.items),
		Config.Game.Arcade.character
	);
	if (Config.Game.Arcade.mission != 0)
	{
		GUI_InputEx(Locale.Game.Arcade.costume, Config.Game.Arcade.costume);
	}
	if ((Config.Game.Arcade.mission != 0) && (Config.Game.Arcade.character == CHAR_DANTE))
	{
		GUI_Combo<uint32>
		(
			Locale.Game.Arcade.Style.label,
			Locale.Game.Arcade.Style.items,
			countof(Locale.Game.Arcade.Style.items),
			Config.Game.Arcade.style
		);
		for (uint8 i = 0; i < countof(Config.Game.Arcade.equipment); i++)
		{
			if (i < 2)
			{
				GUI_Combo<uint8>
				(
					Locale.Game.Arcade.Equipment.label[i],
					Locale.Game.Arcade.Equipment.items,
					5,
					Config.Game.Arcade.equipment[i]
				);
			}
			else
			{
				GUI_Combo<uint8>
				(
					Locale.Game.Arcade.Equipment.label[i],
					Locale.Game.Arcade.Equipment.items,
					10,
					Config.Game.Arcade.equipment[i],
					5
				);
			}
		}
	}
	if (Config.Game.Arcade.mission != 0)
	{
		GUI_InputEx<float32>(Locale.Game.Arcade.hitPoints,   Config.Game.Arcade.hitPoints,   1000);
		GUI_InputEx<float32>(Locale.Game.Arcade.magicPoints, Config.Game.Arcade.magicPoints, 1000);
	}
	ImGui::PopItemWidth();
	GUI_SECTION_FOOTER_START(Game.Arcade);
	//run = false;
	Game_Arcade_Toggle(DefaultConfig.Game.Arcade.enable);
	GUI_SECTION_FOOTER_END;
}

void GUI_Game_BossRush()
{
	GUI_SECTION_HEADER(Game.BossRush);
	ImGui::Text(Locale.Game.BossRush.Mission5.header);
	GUI_Checkbox(Locale.Game.BossRush.Mission5.skipJester, Config.Game.BossRush.Mission5.skipJester);
	ImGui::Text(Locale.Game.BossRush.Mission12.header);
	GUI_Checkbox(Locale.Game.BossRush.Mission12.skipJester, Config.Game.BossRush.Mission12.skipJester);
	GUI_Checkbox(Locale.Game.BossRush.Mission12.skipGeryonBridgeBattle, Config.Game.BossRush.Mission12.skipGeryonBridgeBattle);
	ImGui::Text(Locale.Game.BossRush.Mission17.header);
	GUI_Checkbox(Locale.Game.BossRush.Mission17.skipJester, Config.Game.BossRush.Mission17.skipJester);
	ImGui::Text(Locale.Game.BossRush.Mission19.header);
	GUI_Checkbox(Locale.Game.BossRush.Mission19.skipFirstPart, Config.Game.BossRush.Mission19.skipFirstPart);
	GUI_SECTION_FOOTER(Game.BossRush);
}

void GUI_Game_Dante()
{
	GUI_Hyperlink(Locale.Game.Dante.header);
	ImGui::Text("");
	GUI_PUSH_DISABLE(ActorAvailable());
	if (GUI_Checkbox(Locale.Game.Dante.enable, Config.Game.Dante.enable))
	{
		//if (!System_Cache_enable)
		//{
		//	restart = true;
		//}
		//else
		{
			//System_Actor_Toggle();
			if (Config.Game.Dante.enable)
			{
				Game_Dante_Rebellion_ToggleInfiniteSwordPierce(Config.Game.Dante.Rebellion.infiniteSwordPierce);
				Game_Dante_EbonyIvory_ToggleFoursomeTime(Config.Game.Dante.EbonyIvory.foursomeTime);
				Game_Dante_EbonyIvory_ToggleInfiniteRainStorm(Config.Game.Dante.EbonyIvory.infiniteRainStorm);
				Game_Dante_Artemis_ToggleSwap(Config.Game.Dante.Artemis.swap);
				Game_Dante_Artemis_ToggleInstant(Config.Game.Dante.Artemis.instant);
				Game_Dante_AirHike_ToggleCoreAbility(Config.Game.Dante.AirHike.coreAbility);
				Game_Dante_CrazyCombo_SetLevelMultiplier(Config.Game.Dante.CrazyCombo.levelMultiplier);
				Game_Dante_WeaponSwitchTimeout_MeleeToggle(Config.Game.Dante.WeaponSwitchTimeout.melee);
				Game_Dante_WeaponSwitchTimeout_RangedToggle(Config.Game.Dante.WeaponSwitchTimeout.ranged);
			}
			else
			{
				Game_Dante_Rebellion_ToggleInfiniteSwordPierce(DefaultConfig.Game.Dante.Rebellion.infiniteSwordPierce);
				Game_Dante_EbonyIvory_ToggleFoursomeTime(DefaultConfig.Game.Dante.EbonyIvory.foursomeTime);
				Game_Dante_EbonyIvory_ToggleInfiniteRainStorm(DefaultConfig.Game.Dante.EbonyIvory.infiniteRainStorm);
				Game_Dante_Artemis_ToggleSwap(DefaultConfig.Game.Dante.Artemis.swap);
				Game_Dante_Artemis_ToggleInstant(DefaultConfig.Game.Dante.Artemis.instant);
				Game_Dante_AirHike_ToggleCoreAbility(DefaultConfig.Game.Dante.AirHike.coreAbility);
				Game_Dante_CrazyCombo_SetLevelMultiplier(DefaultConfig.Game.Dante.CrazyCombo.levelMultiplier);
				Game_Dante_WeaponSwitchTimeout_MeleeToggle(DefaultConfig.Game.Dante.WeaponSwitchTimeout.melee);
				Game_Dante_WeaponSwitchTimeout_RangedToggle(DefaultConfig.Game.Dante.WeaponSwitchTimeout.ranged);
			}
		}
	}
	GUI_POP_DISABLE(ActorAvailable());
	ImGui::Text("");
	GUI_PUSH_DISABLE(!Config.Game.Dante.enable);
	ImGui::Text(Locale.Game.Dante.Rebellion.header);
	if (GUI_Checkbox(Locale.Game.Dante.Rebellion.infiniteSwordPierce, Config.Game.Dante.Rebellion.infiniteSwordPierce))
	{
		Game_Dante_Rebellion_ToggleInfiniteSwordPierce(Config.Game.Dante.Rebellion.infiniteSwordPierce);
	}
	GUI_PUSH_DISABLE(ActorAvailable());
	if (GUI_Checkbox(Locale.Game.Dante.Rebellion.unlockQuickDrive, Config.Game.Dante.Rebellion.unlockQuickDrive))
	{
		//if (!System_Cache_enable)
		//{
		//	restart = true;
		//}
		//else
		{
			//System_Actor_Toggle();
		}
	}
	if (!demo_pl000_00_3)
	{
		ImGui::SameLine();
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 0, 0, 1));
		ImGui::TextWrapped("demo_pl000_00_3.pac");
		ImGui::PopStyleColor();
	}
	GUI_POP_DISABLE(ActorAvailable());
	ImGui::Text(Locale.Game.Dante.EbonyIvory.header);
	if (GUI_Checkbox(Locale.Game.Dante.EbonyIvory.foursomeTime, Config.Game.Dante.EbonyIvory.foursomeTime))
	{
		Game_Dante_EbonyIvory_ToggleFoursomeTime(Config.Game.Dante.EbonyIvory.foursomeTime);
	}
	if (GUI_Checkbox(Locale.Game.Dante.EbonyIvory.infiniteRainStorm, Config.Game.Dante.EbonyIvory.infiniteRainStorm))
	{
		Game_Dante_EbonyIvory_ToggleInfiniteRainStorm(Config.Game.Dante.EbonyIvory.infiniteRainStorm);
	}
	ImGui::Text(Locale.Game.Dante.Artemis.header);
	if (GUI_Checkbox(Locale.Game.Dante.Artemis.swap, Config.Game.Dante.Artemis.swap))
	{
		Game_Dante_Artemis_ToggleSwap(Config.Game.Dante.Artemis.swap);
	}
	if (GUI_Checkbox(Locale.Game.Dante.Artemis.instant, Config.Game.Dante.Artemis.instant))
	{
		Game_Dante_Artemis_ToggleInstant(Config.Game.Dante.Artemis.instant);
	}
	ImGui::Text(Locale.Game.Dante.AirHike.header);
	if (GUI_Checkbox(Locale.Game.Dante.AirHike.coreAbility, Config.Game.Dante.AirHike.coreAbility))
	{
		Game_Dante_AirHike_ToggleCoreAbility(Config.Game.Dante.AirHike.coreAbility);
	}
	ImGui::PushItemWidth(100);
	ImGui::Text(Locale.Game.Dante.CrazyCombo.header);
	if (GUI_InputEx(Locale.Game.Dante.CrazyCombo.levelMultiplier, Config.Game.Dante.CrazyCombo.levelMultiplier))
	{
		Game_Dante_CrazyCombo_SetLevelMultiplier(Config.Game.Dante.CrazyCombo.levelMultiplier);
	}
	ImGui::PopItemWidth();
	ImGui::PushItemWidth(150);
	ImGui::Text(Locale.Game.Dante.WeaponSwitchTimeout.header);
	if (GUI_InputEx<float32>(Locale.Game.Dante.WeaponSwitchTimeout.melee, Config.Game.Dante.WeaponSwitchTimeout.melee))
	{
		Game_Dante_WeaponSwitchTimeout_MeleeToggle(Config.Game.Dante.WeaponSwitchTimeout.melee);
	}
	if (GUI_InputEx<float32>(Locale.Game.Dante.WeaponSwitchTimeout.ranged, Config.Game.Dante.WeaponSwitchTimeout.ranged))
	{
		Game_Dante_WeaponSwitchTimeout_RangedToggle(Config.Game.Dante.WeaponSwitchTimeout.ranged);
	}
	ImGui::PopItemWidth();
	GUI_POP_DISABLE(!Config.Game.Dante.enable);
	ImGui::Text("");
	GUI_PUSH_DISABLE(ActorAvailable());
	if (GUI_Button(Locale.Game.Dante.reset))
	{
		memcpy(&Config.Game.Dante, &DefaultConfig.Game.Dante, sizeof(Config.Game.Dante));
		SaveConfig();
		//System_Actor_Toggle();
		Game_Dante_Rebellion_ToggleInfiniteSwordPierce(DefaultConfig.Game.Dante.Rebellion.infiniteSwordPierce);
		Game_Dante_EbonyIvory_ToggleFoursomeTime(DefaultConfig.Game.Dante.EbonyIvory.foursomeTime);
		Game_Dante_EbonyIvory_ToggleInfiniteRainStorm(DefaultConfig.Game.Dante.EbonyIvory.infiniteRainStorm);
		Game_Dante_Artemis_ToggleSwap(DefaultConfig.Game.Dante.Artemis.swap);
		Game_Dante_Artemis_ToggleInstant(DefaultConfig.Game.Dante.Artemis.instant);
		Game_Dante_AirHike_ToggleCoreAbility(DefaultConfig.Game.Dante.AirHike.coreAbility);
		Game_Dante_CrazyCombo_SetLevelMultiplier(DefaultConfig.Game.Dante.CrazyCombo.levelMultiplier);
		Game_Dante_WeaponSwitchTimeout_MeleeToggle(DefaultConfig.Game.Dante.WeaponSwitchTimeout.melee);
		Game_Dante_WeaponSwitchTimeout_RangedToggle(DefaultConfig.Game.Dante.WeaponSwitchTimeout.ranged);
	}
	GUI_POP_DISABLE(ActorAvailable());
}

void GUI_Game_Doppelganger()
{
	GUI_Hyperlink(Locale.Game.Doppelganger.header);
	ImGui::Text("");
	GUI_PUSH_DISABLE(ActorAvailable());
	if (GUI_Checkbox(Locale.Game.Doppelganger.enable, Config.Game.Doppelganger.enable))
	{
		//if (!System_Cache_enable)
		//{
		//	restart = true;
		//}
		//else
		{
			//System_Actor_Toggle();
			if (Config.Game.Doppelganger.enable)
			{
				Game_Doppelganger_ToggleUseEXVersion(Config.Game.Doppelganger.useEXVersion);
			}
			else
			{
				Game_Doppelganger_ToggleUseEXVersion(DefaultConfig.Game.Doppelganger.useEXVersion);
			}
		}
	}
	GUI_POP_DISABLE(ActorAvailable());
	ImGui::Text("");

	GUI_PUSH_DISABLE(!Config.Game.Doppelganger.enable);
	{
		ImGui::PushItemWidth(100);
		if (GUI_Checkbox(Locale.Game.Doppelganger.useEXVersion, Config.Game.Doppelganger.useEXVersion))
		{
			Game_Doppelganger_ToggleUseEXVersion(Config.Game.Doppelganger.useEXVersion);
		}
		GUI_Combo<uint8>
		(
			Locale.Game.Doppelganger.Character.label,
			Locale.Game.Doppelganger.Character.items,
			countof(Locale.Game.Doppelganger.Character.items),
			Config.Game.Doppelganger.character
		);
		ImGui::PopItemWidth();
	}
	GUI_POP_DISABLE(!Config.Game.Doppelganger.enable);

	ImGui::Text("");

	GUI_PUSH_DISABLE(ActorAvailable());

	if (GUI_Button(Locale.Game.Doppelganger.reset))
	{
		memcpy(&Config.Game.Doppelganger, &DefaultConfig.Game.Doppelganger, sizeof(Config.Game.Doppelganger));
		SaveConfig();
		//System_Actor_Toggle();
		Game_Doppelganger_ToggleUseEXVersion(DefaultConfig.Game.Doppelganger.useEXVersion);
	}

	GUI_POP_DISABLE(ActorAvailable());
}























#define GUI_InputEx2(branch)                                                           \
ImGui::PushItemWidth(29);                                                          \
GUI_InputEx<uint8>("", Config.Game.Mobility.Human.branch, 0);                          \
ImGui::SameLine(0, ImGui::GetStyle().ItemInnerSpacing.x);                          \
GUI_InputEx<uint8>(Locale.Game.Mobility.branch, Config.Game.Mobility.Devil.branch, 0); \
ImGui::PopItemWidth();

void GUI_Game_Mobility()
{
	GUI_SECTION_HEADER_START(Game.Mobility);
	if (Config.Game.Mobility.enable)
	{
		Game_Mobility_Toggle(Config.Game.Mobility.enable);
	}
	else
	{
		Game_Mobility_Toggle(DefaultConfig.Game.Mobility.enable);
	}
	GUI_SECTION_HEADER_END(Game.Mobility);
	ImGui::Text(Locale.Game.Mobility.Dante.header);
	GUI_InputEx2(Dante.airHike);
	GUI_InputEx2(Dante.dash[0]);
	GUI_InputEx2(Dante.dash[1]);
	GUI_InputEx2(Dante.dash[2]);
	GUI_InputEx2(Dante.skyStar);
	GUI_InputEx2(Dante.airTrick);
	ImGui::Text(Locale.Game.Mobility.Vergil.header);
	GUI_InputEx2(Vergil.airTrick);
	GUI_InputEx2(Vergil.trickUp);
	GUI_InputEx2(Vergil.trickDown);
	GUI_SECTION_FOOTER_START(Game.Mobility);
	Game_Mobility_Toggle(DefaultConfig.Game.Mobility.enable);
	GUI_SECTION_FOOTER_END;
}

#undef GUI_InputEx2

void GUI_Game_Multiplayer()
{
	GUI_Hyperlink(Locale.Game.Multiplayer.header);
	ImGui::Text("");
	GUI_PUSH_DISABLE(ActorAvailable());
	if (GUI_Checkbox(Locale.Game.Multiplayer.enable, Config.Game.Multiplayer.enable))
	{
		//if (!System_Cache_enable || !System_Input_extend)
		//{
		//	restart = true;
		//}
		//else
		{
			//System_Actor_Toggle();
		}
	}
	GUI_POP_DISABLE(ActorAvailable());
	ImGui::Text("");
	GUI_PUSH_DISABLE(!Config.Game.Multiplayer.enable);
	ImGui::PushItemWidth(100);
	GUI_Slider("", Config.Game.Multiplayer.actorCount, 1, (MAX_ACTOR - 1));
	for (uint8 i = 0; i < (MAX_ACTOR - 1); i++)
	{
		bool skip = (i >= Config.Game.Multiplayer.actorCount) ? true : false;
		GUI_PUSH_DISABLE(skip);
		GUI_Combo<uint8>
		(
			"",
			Locale.Game.Multiplayer.Character.items,
			countof(Locale.Game.Multiplayer.Character.items),
			Config.Game.Multiplayer.character[i]
		);
		ImGui::SameLine();
		GUI_InputEx("", Config.Game.Multiplayer.costume[i]);
		GUI_POP_DISABLE(skip);
	}
	//GUI_InputEx<uint32>(Locale.Game.Multiplayer.spawnDelay, Config.Game.Multiplayer.spawnDelay, 100);
	ImGui::PopItemWidth();
	GUI_POP_DISABLE(!Config.Game.Multiplayer.enable);
	ImGui::Text("");
	GUI_PUSH_DISABLE(ActorAvailable());
	if (GUI_Button(Locale.Game.Multiplayer.reset))
	{
		memcpy(&Config.Game.Multiplayer, &DefaultConfig.Game.Multiplayer, sizeof(Config.Game.Multiplayer));
		SaveConfig();
		// Technically not needed, but sometimes I want to test how a function behaves
		// under specific conditions.
		//if (System_Cache_enable)
		//{
		//	//System_Actor_Toggle();
		//}
		if (System_Input_extend)
		{
			restart = true;
		}
	}
	GUI_POP_DISABLE(ActorAvailable());
}

#define GUI_InputExOther(branch, step)                                            \
if (GUI_InputEx<float32>(Locale.Game.Other.branch, Config.Game.Other.branch, step)) \
{                                                                             \
	Game_Other_Update();                                                      \
}

void GUI_Game_Other()
{
	GUI_SECTION_HEADER_START(Game.Other);
	if (Config.Game.Other.enable)
	{
		Game_Other_Toggle(Config.Game.Other.enable);
	}
	else
	{
		Game_Other_Toggle(DefaultConfig.Game.Other.enable);
	}
	GUI_SECTION_HEADER_END(Game.Other);
	ImGui::PushItemWidth(150);
	GUI_InputExOther(orbReach, 100);
	ImGui::Text(Locale.Game.Other.MagicPointsDepletionRate.header);
	GUI_InputExOther(MagicPointsDepletionRate.devil, 1);
	GUI_InputExOther(MagicPointsDepletionRate.quicksilver, 1);
	GUI_InputExOther(MagicPointsDepletionRate.doppelganger, 1);
	ImGui::PopItemWidth();
	GUI_SECTION_FOOTER_START(Game.Other);
	Game_Other_Toggle(DefaultConfig.Game.Other.enable);
	GUI_SECTION_FOOTER_END;
}

#undef GUI_InputExOther




void GUI_Game_ResetMotionState()
{
	static uint8 buttonIndex = 0;
	static bool  run         = false;
	if (!run)
	{
		run = true;
		for (uint8 i = 0; i < countof(Game_ResetMotionState_buttonMask); i++)
		{
			if (Config.Game.ResetMotionState.button == Game_ResetMotionState_buttonMask[i])
			{
				buttonIndex = i;
				break;
			}
		}
	}
	GUI_Hyperlink(Locale.Game.ResetMotionState.header);
	ImGui::Text("");
	GUI_PUSH_DISABLE(ActorAvailable());
	if (GUI_Checkbox(Locale.Game.ResetMotionState.enable, Config.Game.ResetMotionState.enable))
	{
		//if (!System_Cache_enable)
		//{
		//	restart = true;
		//}
		//else
		{
			//System_Actor_Toggle();
		}
	}
	GUI_POP_DISABLE(ActorAvailable());
	ImGui::Text("");




	GUI_PUSH_DISABLE(!Config.Game.ResetMotionState.enable);
	ImGui::PushItemWidth(150);
	if (GUI_Combo<uint8>
		(
		Locale.Game.ResetMotionState.Button.label,
		Locale.Game.ResetMotionState.Button.items,
		countof(Locale.Game.ResetMotionState.Button.items),
		buttonIndex,
		0,
		false
		))
	{
		Config.Game.ResetMotionState.button = Game_ResetMotionState_buttonMask[buttonIndex];
		SaveConfig();
	}
	if (debug)
	{
		ImGui::Text("index   %u", buttonIndex);
		ImGui::Text("true id %X", Config.Game.ResetMotionState.button);
	}
	GUI_InputEx<uint32>(Locale.Game.ResetMotionState.updateRate, Config.Game.ResetMotionState.updateRate);
	ImGui::PopItemWidth();
	GUI_POP_DISABLE(!Config.Game.ResetMotionState.enable);




	ImGui::Text("");
	GUI_PUSH_DISABLE(ActorAvailable());
	if (GUI_Button(Locale.Game.ResetMotionState.reset))
	{
		run = false;
		memcpy(&Config.Game.ResetMotionState, &DefaultConfig.Game.ResetMotionState, sizeof(Config.Game.ResetMotionState));
		SaveConfig();
		//if (System_Cache_enable)
		//{
		//	//System_Actor_Toggle();
		//}
	}
	GUI_POP_DISABLE(ActorAvailable());
}






//
//
//
//
//void GUI_Game::ResetMotionState()
//{
//	GUI_Hyperlink(Locale.Game.ResetMotionState.header);
//	ImGui::Text("");
//	GUI_PUSH_DISABLE(ActorAvailable());
//	if (GUI_Checkbox(Locale.Game.ResetMotionState.enable, Config.Game.ResetMotionState.enable))
//	{
//		if (!System_Cache_enable)
//		{
//			restart = true;
//		}
//		else
//		{
//			//System_Actor_Toggle();
//		}
//	}
//	GUI_POP_DISABLE(ActorAvailable());
//	ImGui::Text("");
//	GUI_PUSH_DISABLE(!Config.Game.ResetMotionState.enable);
//	static uint8 index = 0;
//	static bool run = false;
//	if (!run)
//	{
//		run = true;
//		for (uint8 i = 0; i < countof(buttonMask); i++)
//		{
//			if (buttonMask[i] == Config.Game.ResetMotionState.button)
//			{
//				index = i;
//				break;
//			}
//		}
//	}
//	ImGui::PushItemWidth(150);
//	if (GUI_Combo<uint8>
//	(
//		Locale.Game.ResetMotionState.GUI_Button.label,
//		Locale.Game.ResetMotionState.GUI_Button.items,
//		countof(Locale.Game.ResetMotionState.GUI_Button.items),
//		index,
//		0,
//		false
//	))
//	{
//		Config.Game.ResetMotionState.button = buttonMask[index];
//		SaveConfig();
//	}
//	GUI_InputEx(Locale.Game.ResetMotionState.updateRate, Config.Game.ResetMotionState.updateRate);
//	ImGui::PopItemWidth();
//	GUI_POP_DISABLE(!Config.Game.ResetMotionState.enable);
//	ImGui::Text("");
//	GUI_PUSH_DISABLE(ActorAvailable());
//	if (GUI_Button(Locale.Game.ResetMotionState.reset))
//	{
//		run = false;
//		memcpy(&Config.Game.ResetMotionState, &DefaultConfig.Game.ResetMotionState, sizeof(Config.Game.ResetMotionState));
//		SaveConfig();
//		if (System_Cache_enable)
//		{
//			//System_Actor_Toggle();
//		}
//	}
//	GUI_POP_DISABLE(ActorAvailable());
//}

#define GUI_InputExSpeed(branch)                                                  \
if (GUI_InputEx<float32>(Locale.Game.Speed.branch, Config.Game.Speed.branch, 0.1f)) \
{                                                                             \
	Game_Speed_Update();                                                      \
}

void GUI_Game_Speed()
{
	GUI_SECTION_HEADER_START(Game.Speed);
	if (Config.Game.Speed.enable)
	{
		Game_Speed_Toggle(Config.Game.Speed.enable);
	}
	else
	{
		Game_Speed_Toggle(DefaultConfig.Game.Speed.enable);
	}
	GUI_SECTION_HEADER_END(Game.Speed);
	ImGui::PushItemWidth(150);
	ImGui::Text(Locale.Game.Speed.Main.header);
	GUI_InputExSpeed(Main.base);
	GUI_InputExSpeed(Main.turbo);
	GUI_InputExSpeed(Main.actor);
	GUI_InputExSpeed(Main.enemy);
	ImGui::Text(Locale.Game.Speed.Dante.header);
	GUI_InputExSpeed(Dante.rebellion);
	GUI_InputExSpeed(Dante.cerberus);
	GUI_InputExSpeed(Dante.agniRudra);
	GUI_InputExSpeed(Dante.nevan);
	GUI_InputExSpeed(Dante.beowulf);
	GUI_InputExSpeed(Dante.sparda);
	ImGui::Text(Locale.Game.Speed.Vergil.header);
	GUI_InputExSpeed(Vergil.yamato);
	GUI_InputExSpeed(Vergil.beowulf);
	GUI_InputExSpeed(Vergil.forceEdge);
	ImGui::Text(Locale.Game.Speed.NeroAngelo.header);
	GUI_InputExSpeed(NeroAngelo.yamato);
	GUI_InputExSpeed(NeroAngelo.beowulf);
	GUI_InputExSpeed(NeroAngelo.forceEdge);
	ImGui::Text(Locale.Game.Speed.Quicksilver.header);
	GUI_InputExSpeed(Quicksilver.actor);
	GUI_InputExSpeed(Quicksilver.enemy);
	ImGui::PopItemWidth();
	GUI_SECTION_FOOTER_START(Game.Speed);
	Game_Speed_Toggle(DefaultConfig.Game.Speed.enable);
	GUI_SECTION_FOOTER_END;
}

#undef GUI_InputExSpeed




void GUI_Game_StyleSwitcher()
{
	GUI_Hyperlink(Locale.Game.StyleSwitcher.header);
	ImGui::Text("");
	GUI_PUSH_DISABLE(ActorAvailable());
	if (GUI_Checkbox(Locale.Game.StyleSwitcher.enable, Config.Game.StyleSwitcher.enable))
	{
		//if (!System_Cache_enable)
		//{
		//	restart = true;
		//}
		//else
		{
			//System_Actor_Toggle();
			if (Config.Game.StyleSwitcher.enable)
			{
				Game_StyleSwitcher_Toggle(Config.Game.StyleSwitcher.enable);
			}
			else
			{
				Game_StyleSwitcher_Toggle(DefaultConfig.Game.StyleSwitcher.enable);
			}
		}
	}
	GUI_POP_DISABLE(ActorAvailable());
	GUI_PUSH_DISABLE(!Config.Game.StyleSwitcher.enable);
	GUI_Checkbox(Locale.Game.StyleSwitcher.noDoubleTap, Config.Game.StyleSwitcher.noDoubleTap);
	GUI_POP_DISABLE(!Config.Game.StyleSwitcher.enable);
	ImGui::Text("");
	GUI_PUSH_DISABLE(ActorAvailable());
	if (GUI_Button(Locale.Game.StyleSwitcher.reset))
	{
		memcpy(&Config.Game.StyleSwitcher, &DefaultConfig.Game.StyleSwitcher, sizeof(Config.Game.StyleSwitcher));
		SaveConfig();
		//System_Actor_Toggle();
		Game_StyleSwitcher_Toggle(DefaultConfig.Game.StyleSwitcher.enable);
	}
	GUI_POP_DISABLE(ActorAvailable());
}

void GUI_Game_Training()
{
	GUI_SECTION_HEADER_START(Game.Training);
	if (Config.Game.Training.enable)
	{
		Game_Training_ToggleInfiniteHitPoints   ( Config.Game.Training.infiniteHitPoints   );
		Game_Training_ToggleInfiniteMagicPoints ( Config.Game.Training.infiniteMagicPoints );
		Game_Training_ToggleDisableTimer        ( Config.Game.Training.disableTimer        );
	}
	else
	{
		Game_Training_ToggleInfiniteHitPoints   ( DefaultConfig.Game.Training.infiniteHitPoints   );
		Game_Training_ToggleInfiniteMagicPoints ( DefaultConfig.Game.Training.infiniteMagicPoints );
		Game_Training_ToggleDisableTimer        ( DefaultConfig.Game.Training.disableTimer        );
	}
	GUI_SECTION_HEADER_END(Game.Training);
	if (GUI_Checkbox(Locale.Game.Training.infiniteHitPoints, Config.Game.Training.infiniteHitPoints))
	{
		Game_Training_ToggleInfiniteHitPoints(Config.Game.Training.infiniteHitPoints);
	}
	if (GUI_Checkbox(Locale.Game.Training.infiniteMagicPoints, Config.Game.Training.infiniteMagicPoints))
	{
		Game_Training_ToggleInfiniteMagicPoints(Config.Game.Training.infiniteMagicPoints);
	}
	if (GUI_Checkbox(Locale.Game.Training.disableTimer, Config.Game.Training.disableTimer))
	{
		Game_Training_ToggleDisableTimer(Config.Game.Training.disableTimer);
	}
	GUI_SECTION_FOOTER_START(Game.Training);
	Game_Training_ToggleInfiniteHitPoints   ( DefaultConfig.Game.Training.infiniteHitPoints   );
	Game_Training_ToggleInfiniteMagicPoints ( DefaultConfig.Game.Training.infiniteMagicPoints );
	Game_Training_ToggleDisableTimer        ( DefaultConfig.Game.Training.disableTimer        );
	GUI_SECTION_FOOTER_END;
}

void GUI_Game_Vergil()
{
	GUI_SECTION_HEADER_START(Game.Vergil);
	if (Config.Game.Vergil.enable)
	{
		Game_Vergil_ForceEdge_ToggleInfiniteRoundTrip(Config.Game.Vergil.ForceEdge.infiniteRoundTrip);
		Game_Vergil_SummonedSwords_ToggleChronoSwords(Config.Game.Vergil.SummonedSwords.chronoSwords);
		Game_Vergil_WeaponSwitchTimeout_MeleeToggle(Config.Game.Vergil.WeaponSwitchTimeout.melee);
	}
	else
	{
		Game_Vergil_ForceEdge_ToggleInfiniteRoundTrip(DefaultConfig.Game.Vergil.ForceEdge.infiniteRoundTrip);
		Game_Vergil_SummonedSwords_ToggleChronoSwords(DefaultConfig.Game.Vergil.SummonedSwords.chronoSwords);
		Game_Vergil_WeaponSwitchTimeout_MeleeToggle(DefaultConfig.Game.Vergil.WeaponSwitchTimeout.melee);
	}
	GUI_SECTION_HEADER_END(Game.Vergil);
	ImGui::Text(Locale.Game.Vergil.ForceEdge.header);
	if (GUI_Checkbox(Locale.Game.Vergil.ForceEdge.infiniteRoundTrip, Config.Game.Vergil.ForceEdge.infiniteRoundTrip))
	{
		Game_Vergil_ForceEdge_ToggleInfiniteRoundTrip(Config.Game.Vergil.ForceEdge.infiniteRoundTrip);
	}
	ImGui::Text(Locale.Game.Vergil.SummonedSwords.header);
	if (GUI_Checkbox(Locale.Game.Vergil.SummonedSwords.chronoSwords, Config.Game.Vergil.SummonedSwords.chronoSwords))
	{
		Game_Vergil_SummonedSwords_ToggleChronoSwords(Config.Game.Vergil.SummonedSwords.chronoSwords);
	}
	ImGui::PushItemWidth(150);
	ImGui::Text(Locale.Game.Vergil.WeaponSwitchTimeout.header);
	if (GUI_InputEx<float32>(Locale.Game.Vergil.WeaponSwitchTimeout.melee, Config.Game.Vergil.WeaponSwitchTimeout.melee))
	{
		Game_Vergil_WeaponSwitchTimeout_MeleeToggle(Config.Game.Vergil.WeaponSwitchTimeout.melee);
	}
	ImGui::PopItemWidth();
	GUI_SECTION_FOOTER_START(Game.Vergil);
	Game_Vergil_ForceEdge_ToggleInfiniteRoundTrip(DefaultConfig.Game.Vergil.ForceEdge.infiniteRoundTrip);
	Game_Vergil_SummonedSwords_ToggleChronoSwords(DefaultConfig.Game.Vergil.SummonedSwords.chronoSwords);
	Game_Vergil_WeaponSwitchTimeout_MeleeToggle(Config.Game.Vergil.WeaponSwitchTimeout.melee);
	GUI_SECTION_FOOTER_END;
}

//void GUI_Game_Weapon()
//{
//	GUI_SECTION_HEADER_START(Game.Weapon);
//	if (Config.Game.Weapon.enable)
//	{
//		Game_Weapon_ToggleTimeout(Config.Game.Weapon.enable);
//	}
//	else
//	{
//		Game_Weapon_ToggleTimeout(DefaultConfig.Game.Weapon.enable);
//	}
//	GUI_SECTION_HEADER_END(Game.Weapon);
//	
//	ImGui::PushItemWidth(150);
//
//	//ImGui::Text(Locale.Game.Weapon.TimeoutDante.header);
//
//	//bool level = false;
//
//	//GUI_Checkbox("Reset Level", level);
//
//
//	ImGui::Text("Timeout");
//	ImGui::Text("Dante");
//
//
//
//	GUI_InputEx(Locale.Game.Weapon.TimeoutDante.melee, Config.Game.Weapon.Timeout.melee);
//	GUI_InputEx(Locale.Game.Weapon.TimeoutDante.ranged, Config.Game.Weapon.Timeout.ranged);
//
//	//ImGui::Text(Locale.Game.Weapon.TimeoutVergil.header);
//
//	ImGui::Text("Vergil");
//
//	GUI_InputEx(Locale.Game.Weapon.TimeoutVergil.melee, Config.Game.Weapon.Timeout.melee);
//
//	
//
//	
//
//
//
//
//
//	ImGui::PopItemWidth();
//	GUI_SECTION_FOOTER_START(Game.Weapon);
//	Game_Weapon_ToggleTimeout(DefaultConfig.Game.Weapon.enable);
//	GUI_SECTION_FOOTER_END;
//}

void GUI_Game_WeaponSwitcher()
{
	GUI_Hyperlink(Locale.Game.WeaponSwitcher.header);
	ImGui::Text("");
	GUI_PUSH_DISABLE(ActorAvailable());
	if (GUI_Checkbox(Locale.Game.WeaponSwitcher.enable, Config.Game.WeaponSwitcher.enable))
	{
		if (Config.Game.WeaponSwitcher.enable)
		{
			Config.Cosmetics.Weapon.instantModelUpdate = true;
			SaveConfig();
		}
		//if (!System_Cache_enable)
		//{
		//	restart = true;
		//}
		//else
		{
			//System_Actor_Toggle();
			//System_Weapon_Toggle();
			if (Config.Game.WeaponSwitcher.enable)
			{
				Game_WeaponSwitcher_Toggle(Config.Game.WeaponSwitcher.enable);
			}
			else
			{
				Game_WeaponSwitcher_Toggle(DefaultConfig.Game.WeaponSwitcher.enable);
			}
			Cosmetics_Weapon_ToggleInstantModelUpdate(Config.Cosmetics.Weapon.instantModelUpdate);
		}
	}
	GUI_POP_DISABLE(ActorAvailable());
	ImGui::Text("");
	ImGui::PushItemWidth(200);

	GUI_PUSH_DISABLE(!Config.Game.WeaponSwitcher.enable);
	



	GUI_PUSH_DISABLE(ActorAvailable());
	if (GUI_Combo<uint8>
	(
		Locale.Game.WeaponSwitcher.Devil.label,
		Locale.Game.WeaponSwitcher.Devil.items,
		countof(Locale.Game.WeaponSwitcher.Devil.items),
		Config.Game.WeaponSwitcher.devil
	))
	{
		UpdateDevilModel(Config.Game.WeaponSwitcher.devil);
	}
	GUI_POP_DISABLE(ActorAvailable());
	GUI_Combo<uint8>
	(
		Locale.Game.WeaponSwitcher.Sword.label,
		Locale.Game.WeaponSwitcher.Sword.items,
		countof(Locale.Game.WeaponSwitcher.Sword.items),
		Config.Game.WeaponSwitcher.sword
	);
	ImGui::Text(Locale.Game.WeaponSwitcher.Melee.header);
	GUI_Slider("", Config.Game.WeaponSwitcher.Melee.count, 1, 5);
	for (uint8 i = 0; i < 5; i++)
	{
		bool skip = (i >= Config.Game.WeaponSwitcher.Melee.count) ? true : false;
		GUI_PUSH_DISABLE(skip);
		GUI_Combo<uint8>
		(
			"",
			Locale.Game.WeaponSwitcher.Weapon.items,
			5,
			Config.Game.WeaponSwitcher.Melee.weapon[i]
		);
		GUI_POP_DISABLE(skip);
	}
	ImGui::Text(Locale.Game.WeaponSwitcher.Ranged.header);
	GUI_Slider("", Config.Game.WeaponSwitcher.Ranged.count, 1, 5);
	for (uint8 i = 0; i < 5; i++)
	{
		bool skip = (i >= Config.Game.WeaponSwitcher.Ranged.count) ? true : false;
		GUI_PUSH_DISABLE(skip);
		GUI_Combo<uint8>
		(
			"",
			Locale.Game.WeaponSwitcher.Weapon.items,
			10,
			Config.Game.WeaponSwitcher.Ranged.weapon[i],
			5
		);
		GUI_POP_DISABLE(skip);
	}
	ImGui::PopItemWidth();
	GUI_POP_DISABLE(!Config.Game.WeaponSwitcher.enable);
	ImGui::Text("");
	GUI_PUSH_DISABLE(ActorAvailable());
	if (GUI_Button(Locale.Game.WeaponSwitcher.reset))
	{
		memcpy(&Config.Game.WeaponSwitcher, &DefaultConfig.Game.WeaponSwitcher, sizeof(Config.Game.WeaponSwitcher));
		SaveConfig();
		//System_Actor_Toggle();
		//System_Weapon_Toggle();
		Game_WeaponSwitcher_Toggle(DefaultConfig.Game.WeaponSwitcher.enable);
	}
	GUI_POP_DISABLE(ActorAvailable());
}

void GUI_Game_Draw()
{
	static bool run = false;
	if (!run)
	{
		run = true;
		ImGui::SetNextWindowSize(ImVec2(GUI_Game_size.x + 16, GUI_Game_size.y + 16));
		ImGui::SetNextWindowPos(ImVec2(0, 25));
	}
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(1, 1));
	if (ImGui::Begin("GUI_Game", &pause, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
	{
		GUI_Game_Arcade();
		ImGui::Text("");
		GUI_Game_BossRush();
		ImGui::Text("");
		GUI_Game_Dante();
		ImGui::Text("");
		GUI_Game_Doppelganger();
		ImGui::Text("");
		GUI_Game_Mobility();
		ImGui::Text("");
		GUI_Game_Multiplayer();
		ImGui::Text("");
		GUI_Game_Other();
		ImGui::Text("");
		GUI_Game_ResetMotionState();
		ImGui::Text("");
		GUI_Game_Speed();
		ImGui::Text("");
		//GUI_Game_Style();
		//ImGui::Text("");
		GUI_Game_StyleSwitcher();
		ImGui::Text("");
		GUI_Game_Training();
		ImGui::Text("");
		GUI_Game_Vergil();
		//ImGui::Text("");
		//GUI_Game_Weapon();
		ImGui::Text("");
		GUI_Game_WeaponSwitcher();
	}
	ImGui::End();
	ImGui::PopStyleVar(3);
}

#define ColorPalette(label, items, var)                       \
for (uint8 i = 0; i < countof(var); i++)                      \
{                                                             \
	if (GUI_ColorEdit4(items[i], var[i]))                     \
	{                                                         \
		Cosmetics_Color_UpdateRGB();                          \
	}                                                         \
	ImGui::SameLine(0, ImGui::GetStyle().ItemInnerSpacing.x); \
}                                                             \
ImGui::Text(label);

void GUI_Cosmetics_Color()
{
	GUI_Hyperlink(Locale.Cosmetics.Color.header);
	ImGui::Text("");
	if (GUI_Checkbox(Locale.Cosmetics.Color.enable, Config.Cosmetics.Color_enable))
	{
		if (Config.Cosmetics.Color_enable)
		{
			Cosmetics_Color_Toggle(Config.Cosmetics.Color_enable);
		}
		else
		{
			Cosmetics_Color_Toggle(DefaultConfig.Cosmetics.Color_enable);
		}
	}
	ImGui::Text("");
	GUI_PUSH_DISABLE(!Config.Cosmetics.Color_enable);
	ColorPalette
	(
		Locale.Cosmetics.Color.Dante.Aura.label,
		Locale.Cosmetics.Color.Dante.Aura.items,
		Config.Cosmetics.Color.Dante.aura
	);
	ColorPalette
	(
		Locale.Cosmetics.Color.Dante.AirHike.label,
		Locale.Cosmetics.Color.Dante.AirHike.items,
		Config.Cosmetics.Color.Dante.airHike
	);
	ColorPalette
	(
		Locale.Cosmetics.Color.Dante.Trickster.label,
		Locale.Cosmetics.Color.Dante.Trickster.items,
		Config.Cosmetics.Color.Dante.trickster
	);
	ColorPalette
	(
		Locale.Cosmetics.Color.Dante.Royalguard.label,
		Locale.Cosmetics.Color.Dante.Royalguard.items,
		Config.Cosmetics.Color.Dante.royalguard
	);
	ImGui::Text(Locale.Cosmetics.Color.Vergil.header);
	ColorPalette
	(
		Locale.Cosmetics.Color.Vergil.Aura.label,
		Locale.Cosmetics.Color.Vergil.Aura.items,
		Config.Cosmetics.Color.Vergil.aura
	);
	ImGui::Text(Locale.Cosmetics.Color.NeroAngelo.header);
	ColorPalette
	(
		Locale.Cosmetics.Color.NeroAngelo.Aura.label,
		Locale.Cosmetics.Color.NeroAngelo.Aura.items,
		Config.Cosmetics.Color.NeroAngelo.aura
	);
	GUI_POP_DISABLE(!Config.Cosmetics.Color_enable);
	ImGui::Text("");
	if (GUI_Button(Locale.Cosmetics.Color.reset))
	{
		memcpy(&Config.Cosmetics.Color, &DefaultConfig.Cosmetics.Color, sizeof(Config.Cosmetics.Color));
		Config.Cosmetics.Color_enable = DefaultConfig.Cosmetics.Color_enable;
		SaveConfig();
		Cosmetics_Color_Toggle(DefaultConfig.Cosmetics.Color_enable);
	}
}

#undef ColorPalette

void GUI_Cosmetics_Dante()
{
	GUI_Hyperlink(Locale.Cosmetics.Dante.header);
	ImGui::Text("");
	if (GUI_Checkbox(Locale.Cosmetics.Dante.hideBeowulf, Config.Cosmetics.Dante.hideBeowulf))
	{
		Cosmetics_Dante_ToggleHideBeowulf(Config.Cosmetics.Dante.hideBeowulf);
	}
}

void GUI_Cosmetics_Other()
{
	GUI_Hyperlink(Locale.Cosmetics.Other.header);
	ImGui::Text("");
	if (GUI_Checkbox(Locale.Cosmetics.Other.noDevilForm, Config.Cosmetics.Other.noDevilForm))
	{
		Cosmetics_Other_ToggleNoDevilForm(Config.Cosmetics.Other.noDevilForm);
	}
}

void GUI_Cosmetics_Vergil()
{
	GUI_Hyperlink(Locale.Cosmetics.Vergil.header);
	ImGui::Text("");
	if (GUI_Checkbox(Locale.Cosmetics.Vergil.hideBeowulf, Config.Cosmetics.Vergil.hideBeowulf))
	{
		Cosmetics_Vergil_ToggleHideBeowulf(Config.Cosmetics.Vergil.hideBeowulf);
	}
}

void GUI_Cosmetics_Weapon()
{
	GUI_Hyperlink(Locale.Cosmetics.Weapon.header);
	ImGui::Text("");
	if (GUI_Checkbox(Locale.Cosmetics.Weapon.instantModelUpdate, Config.Cosmetics.Weapon.instantModelUpdate))
	{
		Cosmetics_Weapon_ToggleInstantModelUpdate(Config.Cosmetics.Weapon.instantModelUpdate);
	}
}

void GUI_Cosmetics_Draw()
{
	static bool run = false;
	if (!run)
	{
		run = true;
		ImGui::SetNextWindowSize(ImVec2(GUI_Cosmetics_size.x + 16, GUI_Cosmetics_size.y + 16));
		ImGui::SetNextWindowPos(ImVec2(0, 25));
	}
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(1, 1));
	if (ImGui::Begin("GUI_Cosmetics", &pause, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
	{
		GUI_Cosmetics_Color();
		ImGui::Text("");
		GUI_Cosmetics_Dante();
		ImGui::Text("");
		GUI_Cosmetics_Other();
		ImGui::Text("");
		GUI_Cosmetics_Vergil();
		ImGui::Text("");
		GUI_Cosmetics_Weapon();
	}
	ImGui::End();
	ImGui::PopStyleVar(3);
}

void GUI_System_Camera()
{
	GUI_Hyperlink(Locale.System.Camera.header);
	ImGui::Text("");
	if (GUI_Checkbox(Locale.System.Camera.invertX, Config.System.Camera.invertX))
	{
		System_Camera_ToggleInvertX(Config.System.Camera.invertX);
	}
}

void GUI_System_Event()
{
	GUI_Hyperlink(Locale.System.Event.header);
	ImGui::Text("");
	if (GUI_Checkbox(Locale.System.Event.skipIntro, Config.System.Event.skipIntro))
	{
		Event_ToggleSkipIntro(Config.System.Event.skipIntro);
	}
	if (GUI_Checkbox(Locale.System.Event.skipCutscenes, Config.System.Event.skipCutscenes))
	{
		Event_ToggleSkipCutscenes(Config.System.Event.skipCutscenes);
	}
}

void GUI_System_File()
{
	GUI_Hyperlink(Locale.System.File.header);
	ImGui::Text("");
	GUI_Checkbox(Locale.System.File.preferLocalFiles, Config.System.File.preferLocalFiles);
}

void GUI_System_Input()
{
	GUI_Hyperlink(Locale.System.Input.header);
	ImGui::Text("");
	GUI_Checkbox("Hide Mouse Cursor", Config.System.Input.hideMouseCursor);
}

void GUI_System_Window()
{
	GUI_Hyperlink(Locale.System.Window.header);
	ImGui::Text("");
	if (GUI_Checkbox(Locale.System.Window.forceFocus, Config.System.Window.forceFocus))
	{
		System_Window_ToggleForceFocus(Config.System.Window.forceFocus);
	}
}

void GUI_System_Draw()
{
	static bool run = false;
	if (!run)
	{
		run = true;
		ImGui::SetNextWindowSize(ImVec2(GUI_System_size.x + 16, GUI_System_size.y + 16));
		ImGui::SetNextWindowPos(ImVec2(0, 25));
	}
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(1, 1));
	if (ImGui::Begin("GUI_System", &pause, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
	{
		GUI_System_Camera();
		ImGui::Text("");
		GUI_System_Event();
		ImGui::Text("");
		GUI_System_File();
		ImGui::Text("");
		GUI_System_Input();
		ImGui::Text("");
		GUI_System_Window();
	}
	ImGui::End();
	ImGui::PopStyleVar(3);
}

void GUI_Tools_Teleporter()
{
	if (GUI_Hyperlink("Teleporter"))
	{
		GUI_Teleporter_show = true;
	}
}

void GUI_Tools_Draw()
{
	static bool run = false;
	if (!run)
	{
		run = true;
		ImGui::SetNextWindowSize(ImVec2(GUI_Tools_size.x + 16, GUI_Tools_size.y + 16));
		ImGui::SetNextWindowPos(ImVec2(0, 25));
	}
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(1, 1));
	if (ImGui::Begin("GUI_Tools", &pause, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
	{
		GUI_Tools_Teleporter();
	}
	ImGui::End();
	ImGui::PopStyleVar(3);
}

void GUI_Debug_Action()
{
	GUI_Hyperlink("Action");
	ImGui::Text("");
	ResetRangedWeaponLevelStart:
	if (GUI_Button("Reset Ranged Weapon Level"))
	{
		byte * addr = *(byte **)(appBaseAddr + 0xC90E28);
		if (!addr)
		{
			goto ResetRangedWeaponLevelEnd;
		}
		addr = *(byte **)(addr + 0x18);
		if (!addr)
		{
			goto ResetRangedWeaponLevelEnd;
		}
		uint32 * level = (uint32 *)(addr + 0x64E4);
		level[0] = 0;
		level[1] = 0;
	}
	ResetRangedWeaponLevelEnd:
	ResetEquipmentStart:
	if (GUI_Button("Reset Equipment"))
	{
		byte * addr = *(byte **)(appBaseAddr + 0xC90E28);
		if (!addr)
		{
			goto ResetRangedWeaponLevelEnd;
		}
		addr = *(byte **)(addr + 0x18);
		if (!addr)
		{
			goto ResetRangedWeaponLevelEnd;
		}
		uint8 * equipment = (uint8 *)(addr + 0x6498);
		equipment[0] = WEAPON_REBELLION;
		equipment[1] = WEAPON_CERBERUS;
		equipment[2] = WEAPON_EBONY_IVORY;
		equipment[3] = WEAPON_SHOTGUN;
	}
	ResetEquipmentEnd:
	return;
}

void GUI_Debug_Overlay()
{
	GUI_Hyperlink(Locale.GUI.Overlay.header);
	ImGui::Text("");
	GUI_Checkbox(Locale.GUI.Overlay.show, Config.GUI.Overlay.show);
	ImGui::Text("");
	GUI_PUSH_DISABLE(!Config.GUI.Overlay.show);
	ImGui::PushItemWidth(100);
	GUI_Combo<uint8>
	(
		"",
		Locale.GUI.Overlay.FontSize.items,
		countof(Locale.GUI.Overlay.FontSize.items),
		Config.GUI.Overlay.fontSizeIndex
	);
	ImGui::PopItemWidth();
	ImGui::SameLine();
	GUI_ColorEdit4("", Config.GUI.Overlay.color);
	GUI_Checkbox(Locale.GUI.Overlay.cacheStats, Config.GUI.Overlay.cacheStats);
	if (GUI_Button(Locale.GUI.Overlay.resetPosition))
	{
		ImGui::SetWindowPos("GUI_Overlay", ImVec2(0, 0));
	}
	GUI_POP_DISABLE(!Config.GUI.Overlay.show);
}

void GUI_Debug_Draw()
{
	static bool run = false;
	if (!run)
	{
		run = true;
		ImGui::SetNextWindowSize(ImVec2(GUI_Tools_size.x + 16, GUI_Tools_size.y + 16));
		ImGui::SetNextWindowPos(ImVec2(0, 25));
	}
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(1, 1));
	if (ImGui::Begin("GUI_Debug", &pause, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
	{
		GUI_Debug_Action();
		ImGui::Text("");
		GUI_Debug_Overlay();
	}
	ImGui::End();
	ImGui::PopStyleVar(3);
}

void GUI_Main_Tab(const char * str, uint8 index)
{
	ImVec2 pos = ImGui::GetCursorPos();
	bool selected = activeTab == index ? true : false;
	ImVec2 size = ImVec2(100, 20);
	ImGui::PushID(GUI_id);
	GUI_id++;
	if (ImGui::Selectable("", &selected, 0, size))
	{
		activeTab = activeTab == index ? TAB_VOID : index;
	}
	ImGui::PopID();
	ImVec2 len = ImGui::CalcTextSize(str);
	if ((uint32)len.x % 2)
	{
		len.x += 1.0f;
	}
	if ((uint32)len.y % 2)
	{
		len.y += 1.0f;
	}
	float32 x = pos.x + ((size.x - len.x) / 2);
	float32 y = pos.y + ((size.y - len.y) / 2);
	ImGui::SetCursorPos(ImVec2(x, y));
	ImGui::RenderText(ImGui::GetCurrentWindow()->DC.CursorPos, str);
	ImGui::SetCursorPos(ImVec2(pos.x + size.x + 8.0f, pos.y));
}

void GUI_Main_Draw()
{
	static bool run = false;
	if (!run)
	{
		run = true;
		ImGui::SetNextWindowSize(ImVec2((float32)System_Window_width, 25));
		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::GetStyle().ScrollbarRounding = 0;
	}
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(1, 1));
	if (ImGui::Begin("GUI_Main", &pause, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
	{
		ImGui::SetCursorPos(ImVec2(4, 2));
		for (uint8 i = 0; i < MAX_TAB; i++)
		{
			GUI_Main_Tab(Locale.Main.label[i], i);
		}
		ImGui::SetCursorPos(ImVec2(0, 24));
		ImGui::Separator();
		ImGui::End();
	}
	ImGui::PopStyleVar(4);
	switch (activeTab)
	{
	case TAB_GAME:
		GUI_Game_Draw();
		break;
	case TAB_COSMETICS:
		GUI_Cosmetics_Draw();
		break;
	case TAB_SYSTEM:
		GUI_System_Draw();
		break;
	case TAB_TOOLS:
		GUI_Tools_Draw();
		break;
	case TAB_DEBUG:
		GUI_Debug_Draw();
		break;
	}
}

#define GUI_InputReadOnly(label, var)                                                                                  \
{                                                                                                                      \
	char buffer[64];                                                                                                   \
	snprintf(buffer, sizeof(buffer), "%u", var);                                                                       \
	ImGui::PushID(GUI_id);                                                                                             \
	GUI_id++;                                                                                                          \
	ImGui::InputText(label, buffer, sizeof(buffer), ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_ReadOnly); \
	ImGui::PopID();                                                                                                    \
}

void GUI_Teleporter_Draw()
{
	static bool run = false;
	if (!run)
	{
		run = true;
		ImGui::SetNextWindowSize(ImVec2(GUI_Teleporter_size.x + 16, GUI_Teleporter_size.y + 16));
		ImGui::SetNextWindowPos(ImVec2(500, 500));
	}
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(1, 1));
	if (ImGui::Begin("Teleporter", &GUI_Teleporter_show, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize))
	{
		{
			if (!InGame())
			{
				goto InvalidPointer;
			}

			byte * addr = *(byte **)(appBaseAddr + 0xCA8918);
			if (!addr)
			{
				goto InvalidPointer;
			}
			addr = *(byte **)(addr + 0x40);
			if (!addr)
			{
				goto InvalidPointer;

			}
			uint32 & currentRoom     = *(uint32 *)(addr + 0x18);
			uint32 & currentPosition = *(uint32 *)(addr + 0x1C);
			uint32 & event           = *(uint32 *)(addr + 0x20);

			addr = *(byte **)(appBaseAddr + 0xCA8918);
			if (!addr)
			{

				goto InvalidPointer;
			}
			addr = *(byte **)(addr + 0x60);
			if (!addr)
			{

				goto InvalidPointer;

			}
			uint16 & nextRoom     = *(uint16 *)(addr + 0x164);
			uint16 & nextPosition = *(uint16 *)(addr + 0x166);

			ImGui::PushItemWidth(100);
			ImGui::Text("Current");
			GUI_InputReadOnly("", currentRoom);
			GUI_InputReadOnly("", currentPosition);
			ImGui::Text("Next");
			GUI_InputEx<uint16>("", nextRoom);
			GUI_InputEx<uint16>("", nextPosition);
			if (GUI_Button("Teleport"))
			{
				event = EVENT_TELEPORT;
			}
			ImGui::PopItemWidth();
			goto TeleporterEnd;
		}
		InvalidPointer:
		ImGui::Text("Invalid Pointer!");
	}
	TeleporterEnd:
	ImGui::End();
	ImGui::PopStyleVar(3);
}

#undef GUI_InputReadOnly

void GUI_Overlay_Draw()
{
	static bool run = false;
	if (!run)
	{
		run = true;
		ImGui::SetNextWindowSize(ImVec2(GUI_CacheStats_size.x + 16, GUI_CacheStats_size.y + 16));
		ImGui::SetNextWindowPos(ImVec2(Config.GUI.Overlay.x, Config.GUI.Overlay.y));
	}
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(1, 1));
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));
	if (ImGui::Begin("GUI_Overlay", &Config.GUI.Overlay.show, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize))
	{
		{
			ImVec2 pos = ImGui::GetWindowPos();
			if ((Config.GUI.Overlay.x != pos.x) || (Config.GUI.Overlay.y != pos.y))
			{
				Config.GUI.Overlay.x = pos.x;
				Config.GUI.Overlay.y = pos.y;
				SaveConfig();
				Log("Saved Overlay position.");
			}
		}
		ImGuiIO & io = ImGui::GetIO();
		ImGui::PushFont(io.Fonts->Fonts[FONT_OVERLAY_8 + Config.GUI.Overlay.fontSizeIndex]);
		ImGui::PushStyleColor(ImGuiCol_Text, *(ImVec4 *)Config.GUI.Overlay.color);
		if (Config.GUI.Overlay.cacheStats)
		{
			ImGui::Text(Locale.GUI.Overlay.cacheStats);
			byte * cacheAddr[] =
			{
				(appBaseAddr + 0xCAE7D0),
				(appBaseAddr + 0xCF1270),
				(appBaseAddr + 0xCAB230),
				(appBaseAddr + 0xCB9ED0),
				(appBaseAddr + 0xCEFFD0),
				(appBaseAddr + 0xCAA840),
				(appBaseAddr + 0xCA8958),
				(appBaseAddr + 0xCAB150),
				(appBaseAddr + 0xCAAAE8),
				(appBaseAddr + 0xCF0AA0),
			};
			const char * cacheStr[] =
			{
				"Generator",
				"Value",
				"Effect",
				"Particle",
				"Effect System",
				"After Image, Effect System",
				"Heap Frame 1",
				"Heap Frame 2",
				"Texture Manager 1",
				"Texture Manager 2",
			};
			for (uint8 i = 0; i < countof(cacheAddr); i++)
			{
				ImGui::Text("%u", *(uint32 *)cacheAddr[i]);
				ImGui::SameLine(100);
				ImGui::Text(cacheStr[i]);
			}
		}
		ImGui::PopStyleColor();




		{
			ImVec4 color = ImVec4(0, 1, 0, 1);
			if (GetForegroundWindow() != mainWindow)
			{
				color = ImVec4(1, 0, 0, 1);
			}
			ImGui::PushStyleColor(ImGuiCol_Text, color);
			ImGui::Text("Focus");
			ImGui::PopStyleColor();
		}
		
		ImGui::PopFont();
	}
	ImGui::End();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar(3);
}

void GUI_Documentation_Draw()
{
	static bool run = false;
	if (!run)
	{
		run = true;
		ImGui::SetNextWindowSize(ImVec2(GUI_Documentation_size.x + 16, GUI_Documentation_size.y + 16));
		ImGui::SetNextWindowPos(ImVec2(516, 25));
	}
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(1, 1));
	if (ImGui::Begin("Documentation", &GUI_Documentation_show, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse))
	{
		ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + 200);
		ImGui::Text(Locale.Game.description);
		ImGui::PopTextWrapPos();
	}
	ImGui::End();
	ImGui::PopStyleVar(3);
}

void DrawRestartOverlay()
{
	static ImVec2 size = {};
	ImVec2 position = {};
	position.x = (ImGui::GetIO().DisplaySize.x - size.x) / 2;
	position.y = (ImGui::GetIO().DisplaySize.y - size.y) / 2;
	ImGui::SetNextWindowPos(position);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(1, 1));
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImGui::GetStyle().Colors[ImGuiCol_WindowBg]);
	if (ImGui::Begin("RestartOverlay", &restart, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_AlwaysAutoResize))
	{
		size = ImGui::GetWindowSize();
		ImGuiIO & io = ImGui::GetIO();
		ImGui::PushFont(io.Fonts->Fonts[1]);
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 0, 0, 1));
		ImGui::Text(Locale.restartRequired);
		ImGui::PopStyleColor();
		ImGui::PopFont();
	}
	ImGui::End();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar(3);
}

void GUI_Render()
{
	if (GUI_hide)
	{
		return;
	}
	GUI_id = 0;
	if (pause)
	{
		GUI_Main_Draw();
	}
	if (GUI_Teleporter_show)
	{
		GUI_Teleporter_Draw();
	}
	if (Config.GUI.Overlay.show)
	{
		GUI_Overlay_Draw();
	}
	if (GUI_Documentation_show)
	{
		GUI_Documentation_Draw();
	}
	if (restart)
	{
		DrawRestartOverlay();
	}
}

void GUI_Init()
{
	BuildFonts();
}
