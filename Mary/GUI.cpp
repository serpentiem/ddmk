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
	TAB_SYSTEM,
	TAB_GAME,
	TAB_COSMETICS,
	TAB_TOOLS,
	MAX_TAB,
	TAB_VOID,
};

constexpr bool debug = false;

uint8 activeTab = TAB_VOID;

bool GUI_Overlay_run = false;

ImVec2 GUI_System_size     = ImVec2(300, 500);
ImVec2 GUI_Game_size       = ImVec2(500, 500);
ImVec2 GUI_Cosmetics_size  = ImVec2(400, 500);
ImVec2 GUI_Tools_size      = ImVec2(300, 500);

ImVec2 GUI_Camera_size     = ImVec2(400, 400);
ImVec2 GUI_Speed_size      = ImVec2(400, 400);
ImVec2 GUI_Teleporter_size = ImVec2(120, 180);
ImVec2 GUI_Overlay_size    = ImVec2(300, 300);

bool GUI_Camera_show     = false;
bool GUI_Speed_show      = false;
bool GUI_Teleporter_show = false;

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

#pragma region System

void GUI_System_Actor()
{
	GUI_Hyperlink(Locale.System.Actor.header);
	ImGui::Text("");
	GUI_Checkbox
	(
		Locale.System.Actor.forceSingleActor,
		Config.System.Actor.forceSingleActor
	);
	if (GUI_Checkbox
	(
		Locale.System.Actor.disableIdleTimer,
		Config.System.Actor.disableIdleTimer
	))
	{
		//System_Actor_ToggleDisableIdleTimer(Config.System.Actor.disableIdleTimer);
	}
}

void GUI_System_Camera()
{
	GUI_Hyperlink(Locale.System.Camera.header);
	ImGui::Text("");
	if (GUI_Checkbox
	(
		Locale.System.Camera.invertX,
		Config.System.Camera.invertX
	))
	{
		//System_Camera_ToggleInvertX(Config.System.Camera.invertX);
	}
}

void GUI_System_Event()
{
	GUI_Hyperlink(Locale.System.Event.header);
	ImGui::Text("");
	if (GUI_Checkbox
	(
		Locale.System.Event.skipIntro,
		Config.System.Event.skipIntro
	))
	{
		Event_ToggleSkipIntro(Config.System.Event.skipIntro);
	}
	if (GUI_Checkbox
	(
		Locale.System.Event.skipCutscenes,
		Config.System.Event.skipCutscenes
	))
	{
		Event_ToggleSkipCutscenes(Config.System.Event.skipCutscenes);
	}
}

void GUI_System_File()
{
	GUI_Hyperlink(Locale.System.File.header);
	ImGui::Text("");
	GUI_Checkbox
	(
		Locale.System.File.preferLocalFiles,
		Config.System.File.preferLocalFiles
	);
}

void GUI_System_Graphics()
{
	GUI_Hyperlink(Locale.System.Graphics.header);
	ImGui::Text("");
	ImGui::PushItemWidth(150);
	GUI_InputEx<uint32>
	(
		Locale.System.Graphics.frameRate,
		Config.System.Graphics.frameRate
	);
	ImGui::SameLine();
	GUI_Tooltip(Locale.System.Graphics.frameRateHint);
	GUI_Combo<uint8>
	(
		Locale.System.Graphics.VSync.label,
		Locale.System.Graphics.VSync.items,
		countof(Locale.System.Graphics.VSync.items),
		Config.System.Graphics.vSync
	);
	ImGui::PopItemWidth();
}

void GUI_System_Input()
{
	GUI_Hyperlink(Locale.System.Input.header);
	ImGui::Text("");
	GUI_Checkbox
	(
		Locale.System.Input.hideMouseCursor,
		Config.System.Input.hideMouseCursor
	);
}

void GUI_System_Window()
{
	GUI_Hyperlink(Locale.System.Window.header);
	ImGui::Text("");
	if (GUI_Checkbox(
		Locale.System.Window.forceFocus,
		Config.System.Window.forceFocus
	))
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
		GUI_System_Actor();
		ImGui::Text("");
		GUI_System_Camera();
		ImGui::Text("");
		GUI_System_Event();
		ImGui::Text("");
		GUI_System_File();
		ImGui::Text("");
		GUI_System_Graphics();
		ImGui::Text("");
		GUI_System_Input();
		ImGui::Text("");
		GUI_System_Window();
	}
	ImGui::End();
	ImGui::PopStyleVar(3);
}

#pragma endregion

#pragma region Game

void GUI_Game_Arcade()
{


	//static uint8 character = CHAR_DANTE;

	//if (GUI_Button("CreateActor"))
	//{
	//	auto baseAddr = CreateActor(CHAR_DANTE, ACTOR_TWO);
	//	Log("baseAddr %llX", baseAddr);
	//}



	{
		static uint32 arg[3] = {};
		GUI_InputEx<uint32>("arg1", arg[0]);
		GUI_InputEx<uint32>("arg2", arg[1]);
		GUI_InputEx<uint32>("arg3", arg[2]);
		if (GUI_Button("Switch"))
		{
			auto g_pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);
			auto hud = *reinterpret_cast<byte8 **>(g_pool[11]);
			func_280160(hud, arg[0], arg[1], arg[2]);
		}
	}














	{
		static bool enable = false;
		if (GUI_Checkbox("Toggle Update Weapon", enable))
		{
			//ToggleUpdateWeapon(enable);
		}
	}













	ImGui::Text(Locale.Game.Arcade.header);
	ImGui::SameLine();
	GUI_Tooltip(Locale.Game.Arcade.description);
	ImGui::Text("");
	if (GUI_Checkbox
	(
		Locale.Game.Arcade.enable,
		Config.Game.Arcade.enable
	))
	{
		if (Config.Game.Arcade.enable)
		{
			Game_Arcade_Toggle(Config.Game.Arcade.enable);
		}
		else
		{
			Game_Arcade_Toggle(DefaultConfig.Game.Arcade.enable);
		}
	}
	ImGui::Text("");
	GUI_PUSH_DISABLE(!Config.Game.Arcade.enable);
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
		if (GUI_Combo<uint8>
		(
			Locale.Game.Arcade.Mode.label,
			Locale.Game.Arcade.Mode.items,
			countof(Locale.Game.Arcade.Mode.items),
			Game_Arcade_modeIndex,
			0,
			false
		))
		{
			auto & modeIndex = Game_Arcade_modeIndex;
			auto & modeMap   = Game_Arcade_modeMap;
			Config.Game.Arcade.mode = modeMap[modeIndex];
			SaveConfig();
		}
		if constexpr (debug)
		{
			ImGui::Text("index %u", Game_Arcade_modeIndex);
			ImGui::Text("true  %X", Config.Game.Arcade.mode);
		}
		GUI_InputEx<uint16>
		(
			Locale.Game.Arcade.room,
			Config.Game.Arcade.room
		);
		ImGui::SameLine();
		GUI_Checkbox
		(
			Locale.Game.Arcade.ignoreRoom,
			Config.Game.Arcade.ignoreRoom
		);
		GUI_InputEx<uint16>
		(
			Locale.Game.Arcade.position,
			Config.Game.Arcade.position
		);
		ImGui::SameLine();
		GUI_Checkbox
		(
			Locale.Game.Arcade.ignorePosition,
			Config.Game.Arcade.ignorePosition
		);
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
		GUI_InputEx<uint8>
		(
			Locale.Game.Arcade.costume,
			Config.Game.Arcade.costume
		);
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
		for (uint8 index = 0; index < countof(Config.Game.Arcade.equipment); index++)
		{
			if (index < 2)
			{
				GUI_Combo<uint8>
				(
					Locale.Game.Arcade.Equipment.label[index],
					Locale.Game.Arcade.Equipment.items,
					5,
					Config.Game.Arcade.equipment[index]
				);
			}
			else
			{
				GUI_Combo<uint8>
				(
					Locale.Game.Arcade.Equipment.label[index],
					Locale.Game.Arcade.Equipment.items,
					10,
					Config.Game.Arcade.equipment[index],
					5
				);
			}
		}
	}
	if (Config.Game.Arcade.mission != 0)
	{
		GUI_InputEx<float32>
		(
			Locale.Game.Arcade.hitPoints,
			Config.Game.Arcade.hitPoints,
			1000
		);
		GUI_InputEx<float32>
		(
			Locale.Game.Arcade.magicPoints,
			Config.Game.Arcade.magicPoints,
			1000
		);
	}
	ImGui::PopItemWidth();
	GUI_SECTION_FOOTER_START(Game.Arcade);
	Game_Arcade_UpdateModeIndex();
	Game_Arcade_Toggle(DefaultConfig.Game.Arcade.enable);
	GUI_SECTION_FOOTER_END;
}

void GUI_Game_BossRush()
{
	ImGui::Text(Locale.Game.BossRush.header);
	ImGui::SameLine();
	GUI_Tooltip(Locale.Game.BossRush.description);
	ImGui::Text("");
	GUI_Checkbox
	(
		Locale.Game.BossRush.enable,
		Config.Game.BossRush.enable
	);
	ImGui::Text("");
	GUI_PUSH_DISABLE(!Config.Game.BossRush.enable);
	ImGui::Text(Locale.Game.BossRush.Mission5.header);
	GUI_Checkbox
	(
		Locale.Game.BossRush.Mission5.skipJester,
		Config.Game.BossRush.Mission5.skipJester
	);
	ImGui::Text(Locale.Game.BossRush.Mission12.header);
	GUI_Checkbox
	(
		Locale.Game.BossRush.Mission12.skipJester,
		Config.Game.BossRush.Mission12.skipJester
	);
	GUI_Checkbox
	(
		Locale.Game.BossRush.Mission12.skipGeryonBridgeBattle,
		Config.Game.BossRush.Mission12.skipGeryonBridgeBattle
	);
	ImGui::Text(Locale.Game.BossRush.Mission17.header);
	GUI_Checkbox
	(
		Locale.Game.BossRush.Mission17.skipJester,
		Config.Game.BossRush.Mission17.skipJester
	);
	ImGui::Text(Locale.Game.BossRush.Mission19.header);
	GUI_Checkbox
	(
		Locale.Game.BossRush.Mission19.skipFirstPart,
		Config.Game.BossRush.Mission19.skipFirstPart
	);
	GUI_SECTION_FOOTER(Game.BossRush);
}

void GUI_Game_Dante()
{
	auto Toggle = [](CONFIG & config)
	{
		//Game_Dante_Rebellion_ToggleInfiniteSwordPierce(config.Game.Dante.Rebellion.infiniteSwordPierce);
		//Game_Dante_EbonyIvory_ToggleFoursomeTime      (config.Game.Dante.EbonyIvory.foursomeTime      );
		//Game_Dante_EbonyIvory_ToggleInfiniteRainStorm (config.Game.Dante.EbonyIvory.infiniteRainStorm );
		//Game_Dante_Artemis_ToggleSwap                 (config.Game.Dante.Artemis.swap                 );
		//Game_Dante_Artemis_ToggleInstant              (config.Game.Dante.Artemis.instant              );
		//Game_Dante_AirHike_ToggleCoreAbility          (config.Game.Dante.AirHike.coreAbility          );
		//Game_Dante_CrazyCombo_SetLevelMultiplier      (config.Game.Dante.CrazyCombo.levelMultiplier   );
		//Game_Dante_WeaponSwitchTimeout_Melee_Toggle   (config.Game.Dante.WeaponSwitchTimeout.melee    );
		//Game_Dante_WeaponSwitchTimeout_Ranged_Toggle  (config.Game.Dante.WeaponSwitchTimeout.ranged   );
	};
	GUI_SECTION_HEADER_START(Game.Dante);
	if (Config.Game.Dante.enable)
	{
		Toggle(Config);
	}
	else
	{
		Toggle(DefaultConfig);
	}
	GUI_SECTION_HEADER_END(Game.Dante);
	ImGui::Text(Locale.Game.Dante.Rebellion.header);
	if (GUI_Checkbox
	(
		Locale.Game.Dante.Rebellion.infiniteSwordPierce,
		Config.Game.Dante.Rebellion.infiniteSwordPierce
	))
	{
		//Game_Dante_Rebellion_ToggleInfiniteSwordPierce(Config.Game.Dante.Rebellion.infiniteSwordPierce);
	}
	GUI_Checkbox
	(
		Locale.Game.Dante.Rebellion.unlockQuickDrive,
		Config.Game.Dante.Rebellion.unlockQuickDrive
	);
	ImGui::SameLine();
	GUI_Tooltip(Locale.Game.Dante.Rebellion.unlockQuickDriveDescription);
	{
		ImGui::SameLine();
		auto color = ImVec4(0, 1, 0, 1);
		if (!demo_pl000_00_3)
		{
			color = ImVec4(1, 0, 0, 1);
		}
		ImGui::PushStyleColor(ImGuiCol_Text, color);
		ImGui::Text("demo_pl000_00_3.pac");
		ImGui::PopStyleColor();
	}
	ImGui::Text(Locale.Game.Dante.EbonyIvory.header);
	if (GUI_Checkbox
	(
		Locale.Game.Dante.EbonyIvory.foursomeTime,
		Config.Game.Dante.EbonyIvory.foursomeTime
	))
	{
		//Game_Dante_EbonyIvory_ToggleFoursomeTime(Config.Game.Dante.EbonyIvory.foursomeTime);
	}
	ImGui::SameLine();
	GUI_Tooltip(Locale.Game.Dante.EbonyIvory.foursomeTimeDescription);
	if (GUI_Checkbox
	(
		Locale.Game.Dante.EbonyIvory.infiniteRainStorm,
		Config.Game.Dante.EbonyIvory.infiniteRainStorm
	))
	{
		//Game_Dante_EbonyIvory_ToggleInfiniteRainStorm(Config.Game.Dante.EbonyIvory.infiniteRainStorm);
	}
	ImGui::Text(Locale.Game.Dante.Artemis.header);
	if (GUI_Checkbox
	(
		Locale.Game.Dante.Artemis.swap,
		Config.Game.Dante.Artemis.swap
	))
	{
		//Game_Dante_Artemis_ToggleSwap(Config.Game.Dante.Artemis.swap);
	}
	if (GUI_Checkbox
	(
		Locale.Game.Dante.Artemis.instant,
		Config.Game.Dante.Artemis.instant
	))
	{
		//Game_Dante_Artemis_ToggleInstant(Config.Game.Dante.Artemis.instant);
	}
	ImGui::Text(Locale.Game.Dante.AirHike.header);
	if (GUI_Checkbox
	(
		Locale.Game.Dante.AirHike.coreAbility,
		Config.Game.Dante.AirHike.coreAbility
	))
	{
		//Game_Dante_AirHike_ToggleCoreAbility(Config.Game.Dante.AirHike.coreAbility);
	}
	ImGui::SameLine();
	GUI_Tooltip(Locale.Game.Dante.AirHike.coreAbilityDescription);
	ImGui::PushItemWidth(100);
	ImGui::Text(Locale.Game.Dante.CrazyCombo.header);
	if (GUI_InputEx
	(
		Locale.Game.Dante.CrazyCombo.levelMultiplier,
		Config.Game.Dante.CrazyCombo.levelMultiplier
	))
	{
		//Game_Dante_CrazyCombo_SetLevelMultiplier(Config.Game.Dante.CrazyCombo.levelMultiplier);
	}
	ImGui::PopItemWidth();
	ImGui::PushItemWidth(150);
	ImGui::Text(Locale.Game.Dante.WeaponSwitchTimeout.header);
	if (GUI_InputEx<float32>
	(
		Locale.Game.Dante.WeaponSwitchTimeout.melee,
		Config.Game.Dante.WeaponSwitchTimeout.melee
	))
	{
		//Game_Dante_WeaponSwitchTimeout_Melee_Toggle(Config.Game.Dante.WeaponSwitchTimeout.melee);
	}
	if constexpr (debug)
	{
		ImGui::Text("%f", Config.Game.Dante.WeaponSwitchTimeout.melee);
	}
	if (GUI_InputEx<float32>
	(
		Locale.Game.Dante.WeaponSwitchTimeout.ranged,
		Config.Game.Dante.WeaponSwitchTimeout.ranged
	))
	{
		//Game_Dante_WeaponSwitchTimeout_Ranged_Toggle(Config.Game.Dante.WeaponSwitchTimeout.ranged);
	}
	if constexpr (debug)
	{
		ImGui::Text("%f", Config.Game.Dante.WeaponSwitchTimeout.ranged);
	}
	ImGui::PopItemWidth();
	GUI_SECTION_FOOTER_START(Game.Dante);
	Toggle(DefaultConfig);
	GUI_SECTION_FOOTER_END;
}

void GUI_Game_Doppelganger()
{
	GUI_SECTION_HEADER_START(Game.Doppelganger);
	if (Config.Game.Doppelganger.enable)
	{
		//Game_Doppelganger_ToggleEnableDevilTrigger(Config.Game.Doppelganger.enableDevilTrigger);
	}
	else
	{
		//Game_Doppelganger_ToggleEnableDevilTrigger(DefaultConfig.Game.Doppelganger.enableDevilTrigger);
	}
	GUI_SECTION_HEADER_END(Game.Doppelganger);
	ImGui::PushItemWidth(100);
	GUI_Combo<uint8>
	(
		Locale.Game.Doppelganger.Character.label,
		Locale.Game.Doppelganger.Character.items,
		countof(Locale.Game.Doppelganger.Character.items),
		Config.Game.Doppelganger.character
	);
	ImGui::PopItemWidth();
	if (GUI_Checkbox
	(
		Locale.Game.Doppelganger.enableDevilTrigger,
		Config.Game.Doppelganger.enableDevilTrigger
	))
	{
		//Game_Doppelganger_ToggleEnableDevilTrigger(Config.Game.Doppelganger.enableDevilTrigger);
	}
	GUI_SECTION_FOOTER_START(Game.Doppelganger);
	//Game_Doppelganger_ToggleEnableDevilTrigger(DefaultConfig.Game.Doppelganger.enableDevilTrigger);
	GUI_SECTION_FOOTER_END;
}

void GUI_Game_Mobility()
{
	auto InputExMobility = []
	(
		const char * label,
		uint8 & human,
		uint8 & devil
	)
	{
		ImGui::PushItemWidth(29);
		GUI_InputEx<uint8>("", human, 0);
		ImGui::SameLine(0, ImGui::GetStyle().ItemInnerSpacing.x);
		GUI_InputEx<uint8>(label, devil, 0);
		ImGui::PopItemWidth();
	};
	ImGui::Text(Locale.Game.Mobility.header);
	ImGui::SameLine();
	GUI_Tooltip(Locale.Game.Mobility.description);
	ImGui::Text("");
	if (GUI_Checkbox
	(
		Locale.Game.Mobility.enable,
		Config.Game.Mobility.enable
	))
	{
		if (Config.Game.Mobility.enable)
		{
			//Game_Mobility_Toggle(Config.Game.Mobility.enable);
		}
		else
		{
			//Game_Mobility_Toggle(DefaultConfig.Game.Mobility.enable);
		}
	}
	ImGui::Text("");
	GUI_PUSH_DISABLE(!Config.Game.Mobility.enable);
	ImGui::Text(Locale.Game.Mobility.Dante.header);
	InputExMobility
	(
		Locale.Game.Mobility.Dante.airHike,
		Config.Game.Mobility.Human.Dante.airHike,
		Config.Game.Mobility.Devil.Dante.airHike
	);
	for (uint8 index = 0; index < countof(Config.Game.Mobility.Human.Dante.dash); index++)
	{
		InputExMobility
		(
			Locale.Game.Mobility.Dante.dash[index],
			Config.Game.Mobility.Human.Dante.dash[index],
			Config.Game.Mobility.Devil.Dante.dash[index]
		);
	}
	InputExMobility
	(
		Locale.Game.Mobility.Dante.skyStar,
		Config.Game.Mobility.Human.Dante.skyStar,
		Config.Game.Mobility.Devil.Dante.skyStar
	);
	InputExMobility
	(
		Locale.Game.Mobility.Dante.airTrick,
		Config.Game.Mobility.Human.Dante.airTrick,
		Config.Game.Mobility.Devil.Dante.airTrick
	);
	ImGui::Text(Locale.Game.Mobility.Vergil.header);
	InputExMobility
	(
		Locale.Game.Mobility.Vergil.airTrick,
		Config.Game.Mobility.Human.Vergil.airTrick,
		Config.Game.Mobility.Devil.Vergil.airTrick
	);
	InputExMobility
	(
		Locale.Game.Mobility.Vergil.trickUp,
		Config.Game.Mobility.Human.Vergil.trickUp,
		Config.Game.Mobility.Devil.Vergil.trickUp
	);
	InputExMobility
	(
		Locale.Game.Mobility.Vergil.trickDown,
		Config.Game.Mobility.Human.Vergil.trickDown,
		Config.Game.Mobility.Devil.Vergil.trickDown
	);
	GUI_SECTION_FOOTER_START(Game.Mobility);
	//Game_Mobility_Toggle(DefaultConfig.Game.Mobility.enable);
	GUI_SECTION_FOOTER_END;
}

void GUI_Game_Multiplayer()
{
	auto Toggle = [](bool enable)
	{
		//System_Input_ToggleRangeExtension  (enable);
		//System_Input_ToggleMultiplayerFixes(enable);
	};
	GUI_PUSH_DISABLE(ActorAvailable());
	ImGui::Text(Locale.Game.Multiplayer.header);
	ImGui::SameLine();
	GUI_Tooltip(Locale.Game.Multiplayer.description);
	ImGui::Text("");
	if (GUI_Checkbox
	(
		Locale.Game.Multiplayer.enable,
		Config.Game.Multiplayer.enable
	))
	{
		Toggle(Config.Game.Multiplayer.enable);
	}
	ImGui::Text("");
	GUI_PUSH_DISABLE(!Config.Game.Multiplayer.enable);
	//constexpr uint8 count = (MAX_ACTOR - 1);
	constexpr uint8 count = 3;
	ImGui::PushItemWidth(100);
	GUI_Slider("", Config.Game.Multiplayer.actorCount, 1, count);
	for (uint8 index = 0; index < count; index++)
	{
		bool skip = (index >= Config.Game.Multiplayer.actorCount) ? true : false;
		GUI_PUSH_DISABLE(skip);
		GUI_Combo<uint8>
		(
			"",
			Locale.Game.Multiplayer.Character.items,
			countof(Locale.Game.Multiplayer.Character.items),
			Config.Game.Multiplayer.character[index]
		);
		ImGui::SameLine();
		GUI_InputEx("", Config.Game.Multiplayer.costume[index]);
		GUI_POP_DISABLE(skip);
	}
	ImGui::PopItemWidth();
	GUI_SECTION_FOOTER_START(Game.Multiplayer);
	Toggle(DefaultConfig.Game.Multiplayer.enable);
	GUI_SECTION_FOOTER_END;
	GUI_POP_DISABLE(ActorAvailable());
}

void GUI_Game_Other()
{
	GUI_SECTION_HEADER_START(Game.Other);
	if (Config.Game.Other.enable)
	{
		//Game_Other_Toggle(Config.Game.Other.enable);
	}
	else
	{
		//Game_Other_Toggle(DefaultConfig.Game.Other.enable);
	}
	GUI_SECTION_HEADER_END(Game.Other);
	ImGui::PushItemWidth(150);
	GUI_InputEx<float32>
	(
		Locale.Game.Other.orbReach,
		Config.Game.Other.orbReach,
		100
	);
	ImGui::Text(Locale.Game.Other.MagicPointsDepletionRate.header);
	GUI_InputEx<float32>
	(
		Locale.Game.Other.MagicPointsDepletionRate.devil,
		Config.Game.Other.MagicPointsDepletionRate.devil,
		1
	);
	GUI_InputEx<float32>
	(
		Locale.Game.Other.MagicPointsDepletionRate.quicksilver,
		Config.Game.Other.MagicPointsDepletionRate.quicksilver,
		1
	);
	GUI_InputEx<float32>
	(
		Locale.Game.Other.MagicPointsDepletionRate.doppelganger,
		Config.Game.Other.MagicPointsDepletionRate.doppelganger,
		1
	);
	ImGui::PopItemWidth();
	GUI_SECTION_FOOTER_START(Game.Other);
	//Game_Other_Toggle(DefaultConfig.Game.Other.enable);
	GUI_SECTION_FOOTER_END;
}

void GUI_Game_ResetMotionState()
{
	//GUI_SECTION_HEADER(Game.ResetMotionState);
	//ImGui::PushItemWidth(150);
	//if (GUI_Combo<uint8>
	//(
	//	Locale.Game.ResetMotionState.Button.label,
	//	Locale.Game.ResetMotionState.Button.items,
	//	countof(Locale.Game.ResetMotionState.Button.items),
	//	Game_ResetMotionState_buttonIndex,
	//	0,
	//	false
	//))
	//{
	//	auto & buttonIndex = Game_ResetMotionState_buttonIndex;
	//	auto & buttonMap   = Game_ResetMotionState_buttonMap;
	//	Config.Game.ResetMotionState.button = buttonMap[buttonIndex];
	//	SaveConfig();
	//}
	//ImGui::PopItemWidth();
	//if constexpr (debug)
	//{
	//	ImGui::Text("index %u", Game_ResetMotionState_buttonIndex);
	//	ImGui::Text("true  %X", Config.Game.ResetMotionState.button);
	//}
	//GUI_SECTION_FOOTER_START(Game.ResetMotionState);
	//Game_ResetMotionState_UpdateButtonIndex();
	//GUI_SECTION_FOOTER_END;
}

void GUI_Game_StyleSwitcher()
{
	//GUI_SECTION_HEADER_START(Game.StyleSwitcher);
	//if (Config.Game.StyleSwitcher.enable)
	//{
	//	Game_StyleSwitcher_Toggle(Config.Game.StyleSwitcher.enable);
	//}
	//else
	//{
	//	Game_StyleSwitcher_Toggle(DefaultConfig.Game.StyleSwitcher.enable);
	//}
	//GUI_SECTION_HEADER_END(Game.StyleSwitcher);
	//GUI_Checkbox
	//(
	//	Locale.Game.StyleSwitcher.noDoubleTap,
	//	Config.Game.StyleSwitcher.noDoubleTap
	//);
	//GUI_SECTION_FOOTER_START(Game.StyleSwitcher);
	//Game_StyleSwitcher_Toggle(DefaultConfig.Game.StyleSwitcher.enable);
	//GUI_SECTION_FOOTER_END;
}

void GUI_Game_Training()
{
	auto Toggle = [](CONFIG & config)
	{
		Training_ToggleInfiniteHitPoints  (config.Game.Training.infiniteHitPoints  );
		Training_ToggleInfiniteMagicPoints(config.Game.Training.infiniteMagicPoints);
		Training_ToggleDisableTimer       (config.Game.Training.disableTimer       );
	};
	GUI_SECTION_HEADER_START(Game.Training);
	if (Config.Game.Training.enable)
	{
		Toggle(Config);
	}
	else
	{
		Toggle(DefaultConfig);
	}
	GUI_SECTION_HEADER_END(Game.Training);
	if (GUI_Checkbox
	(
		Locale.Game.Training.infiniteHitPoints,
		Config.Game.Training.infiniteHitPoints
	))
	{
		Training_ToggleInfiniteHitPoints(Config.Game.Training.infiniteHitPoints);
	}
	if (GUI_Checkbox
	(
		Locale.Game.Training.infiniteMagicPoints,
		Config.Game.Training.infiniteMagicPoints
	))
	{
		Training_ToggleInfiniteMagicPoints(Config.Game.Training.infiniteMagicPoints);
	}
	if (GUI_Checkbox
	(
		Locale.Game.Training.disableTimer,
		Config.Game.Training.disableTimer
	))
	{
		Training_ToggleDisableTimer(Config.Game.Training.disableTimer);
	}
	GUI_SECTION_FOOTER_START(Game.Training);
	Toggle(DefaultConfig);
	GUI_SECTION_FOOTER_END;
}

void GUI_Game_Vergil()
{
	auto Toggle = [](CONFIG & config)
	{
		//Game_Vergil_ForceEdge_ToggleInfiniteRoundTrip(config.Game.Vergil.ForceEdge.infiniteRoundTrip);
		//Game_Vergil_SummonedSwords_ToggleChronoSwords(config.Game.Vergil.SummonedSwords.chronoSwords);
		//Game_Vergil_WeaponSwitchTimeout_MeleeToggle  (config.Game.Vergil.WeaponSwitchTimeout.melee  );
	};
	GUI_SECTION_HEADER_START(Game.Vergil);
	if (Config.Game.Vergil.enable)
	{
		Toggle(Config);
	}
	else
	{
		Toggle(DefaultConfig);
	}
	GUI_SECTION_HEADER_END(Game.Vergil);
	ImGui::Text(Locale.Game.Vergil.ForceEdge.header);
	if (GUI_Checkbox
	(
		Locale.Game.Vergil.ForceEdge.infiniteRoundTrip,
		Config.Game.Vergil.ForceEdge.infiniteRoundTrip
	))
	{
		//Game_Vergil_ForceEdge_ToggleInfiniteRoundTrip(Config.Game.Vergil.ForceEdge.infiniteRoundTrip);
	}
	ImGui::Text(Locale.Game.Vergil.SummonedSwords.header);
	if (GUI_Checkbox
	(
		Locale.Game.Vergil.SummonedSwords.chronoSwords,
		Config.Game.Vergil.SummonedSwords.chronoSwords
	))
	{
		//Game_Vergil_SummonedSwords_ToggleChronoSwords(Config.Game.Vergil.SummonedSwords.chronoSwords);
	}
	ImGui::SameLine();
	GUI_Tooltip(Locale.Game.Vergil.SummonedSwords.chronoSwordsDescription);
	ImGui::Text(Locale.Game.Vergil.WeaponSwitchTimeout.header);
	ImGui::PushItemWidth(150);
	if (GUI_InputEx<float32>
	(
		Locale.Game.Vergil.WeaponSwitchTimeout.melee,
		Config.Game.Vergil.WeaponSwitchTimeout.melee
	))
	{
		//Game_Vergil_WeaponSwitchTimeout_MeleeToggle(Config.Game.Vergil.WeaponSwitchTimeout.melee);
	}
	ImGui::PopItemWidth();
	GUI_SECTION_FOOTER_START(Game.Vergil);
	Toggle(DefaultConfig);
	GUI_SECTION_FOOTER_END;
}

void GUI_Game_WeaponSwitcher()
{
	GUI_PUSH_DISABLE(ActorAvailable());
	GUI_SECTION_HEADER_START(Game.WeaponSwitcher);
	if (Config.Game.WeaponSwitcher.enable)
	{
		//Game_WeaponSwitcher_Toggle(Config.Game.WeaponSwitcher.enable);
	}
	else
	{
		//Game_WeaponSwitcher_Toggle(DefaultConfig.Game.WeaponSwitcher.enable);
	}
	GUI_SECTION_HEADER_END(Game.WeaponSwitcher);
	ImGui::PushItemWidth(200);
	if (GUI_Combo<uint8>
	(
		Locale.Game.WeaponSwitcher.Devil.label,
		Locale.Game.WeaponSwitcher.Devil.items,
		countof(Locale.Game.WeaponSwitcher.Devil.items),
		Config.Game.WeaponSwitcher.devil
	))
	{
		//System_Actor_UpdateDevilModel(Config.Game.WeaponSwitcher.devil);
	}
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
	GUI_SECTION_FOOTER_START(Game.WeaponSwitcher);
	//Game_WeaponSwitcher_Toggle(DefaultConfig.Game.WeaponSwitcher.enable);
	GUI_SECTION_FOOTER_END;
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
		GUI_Game_StyleSwitcher();
		ImGui::Text("");
		GUI_Game_Training();
		ImGui::Text("");
		GUI_Game_Vergil();
		ImGui::Text("");
		GUI_Game_WeaponSwitcher();
	}
	ImGui::End();
	ImGui::PopStyleVar(3);
}

#pragma endregion



















void GUI_Cosmetics_Color()
{
	auto ColorPalette = []
	(
		const char * label,
		const char ** items,
		float32(*var)[4],
		uint8 count
	)
	{
		bool update = false;
		for (uint8 index = 0; index < count; index++)
		{
			if (GUI_ColorEdit4(items[index], var[index]))
			{
				update = true;
				//Cosmetics_Color_UpdateColors(Config);
			}
			ImGui::SameLine(0, ImGui::GetStyle().ItemInnerSpacing.x);
		}
		ImGui::Text(label);
		return update;
	};
	auto UpdateDoppelgangerColor = []()
	{
		if (Config.Game.Multiplayer.enable)
		{
			return;
		}
		if (Config.Cosmetics.Doppelganger.noColor)
		{
			return;
		}
		if (!InGame())
		{
			return;
		}
		//auto & baseAddr = System_Actor_actorBaseAddr[ACTOR_TWO];
		//if (!baseAddr)
		//{
		//	return;
		//}
		//Cosmetics_Color_ApplyColor(baseAddr, 6, 0);
	};




	
	//static uint8 slot[6] = {};
	//if (GUI_Button("DevilRebellion"))
	//{
	//	ApplyDevilRebellion(slot[0]);
	//}
	//if (GUI_Button("DevilCerberus"))
	//{
	//	ApplyDevilCerberus(slot[1]);
	//}
	//if (GUI_Button("DevilAgniRudra"))
	//{
	//	ApplyDevilAgniRudra(slot[2]);
	//}
	//if (GUI_Button("DevilNevan"))
	//{
	//	ApplyDevilNevan(slot[3]);
	//}
	//if (GUI_Button("DevilBeowulf"))
	//{
	//	ApplyDevilBeowulf(slot[4]);
	//}
	//if (GUI_Button("DevilSparda"))
	//{
	//	ApplyDevilSparda(slot[5]);
	//}
	//for (uint8 index = 0; index < countof(slot); index++)
	//{
	//	GUI_InputEx<uint8>("Slot", slot[index]);
	//}



















	ImGui::Text("");














	GUI_Hyperlink(Locale.Cosmetics.Color.header);
	ImGui::Text("");
	ImGui::Text(Locale.Cosmetics.Color.Aura.header);
	ColorPalette
	(
		Locale.Cosmetics.Color.Aura.Dante.label,
		Locale.Cosmetics.Color.Aura.Dante.items,
		Config.Cosmetics.Color.Aura.dante,
		countof(Config.Cosmetics.Color.Aura.dante)
	);
	ColorPalette
	(
		Locale.Cosmetics.Color.Aura.Vergil.label,
		Locale.Cosmetics.Color.Aura.Vergil.items,
		Config.Cosmetics.Color.Aura.vergil,
		countof(Config.Cosmetics.Color.Aura.vergil)
	);
	ColorPalette
	(
		Locale.Cosmetics.Color.Aura.NeroAngelo.label,
		Locale.Cosmetics.Color.Aura.NeroAngelo.items,
		Config.Cosmetics.Color.Aura.neroAngelo,
		countof(Config.Cosmetics.Color.Aura.neroAngelo)
	);
	ImGui::Text(Locale.Cosmetics.Color.Style.header);
	ColorPalette
	(
		Locale.Cosmetics.Color.Style.Trickster.label,
		Locale.Cosmetics.Color.Style.Trickster.items,
		Config.Cosmetics.Color.Style.trickster,
		countof(Config.Cosmetics.Color.Style.trickster)
	);
	ColorPalette
	(
		Locale.Cosmetics.Color.Style.Royalguard.label,
		Locale.Cosmetics.Color.Style.Royalguard.items,
		Config.Cosmetics.Color.Style.royalguard,
		countof(Config.Cosmetics.Color.Style.royalguard)
	);
	if (ColorPalette
	(
		Locale.Cosmetics.Color.Style.Doppelganger.label,
		Locale.Cosmetics.Color.Style.Doppelganger.items,
		Config.Cosmetics.Color.Style.doppelganger,
		countof(Config.Cosmetics.Color.Style.doppelganger)
	))
	{
		UpdateDoppelgangerColor();
	}
	ImGui::Text(Locale.Cosmetics.Color.AirHike.header);
	ColorPalette
	(
		Locale.Cosmetics.Color.AirHike.Dante.label,
		Locale.Cosmetics.Color.AirHike.Dante.items,
		Config.Cosmetics.Color.AirHike.dante,
		countof(Config.Cosmetics.Color.AirHike.dante)
	);
	ImGui::Text("");
	if (GUI_Button(Locale.Cosmetics.Color.reset))
	{
		memcpy(&Config.Cosmetics.Color, &DefaultConfig.Cosmetics.Color, sizeof(Config.Cosmetics.Color));
		SaveConfig();
		//Cosmetics_Color_UpdateColors(DefaultConfig);
		UpdateDoppelgangerColor();
	}
}

void GUI_Cosmetics_Dante()
{
	//auto UpdateModelAttributes = []()
	//{
	//	auto count = System_Actor_GetActorCount();
	//	for (uint8 actor = 0; actor < count; actor++)
	//	{
	//		//auto & baseAddr = System_Actor_actorBaseAddr[actor];
	//		//if (!baseAddr)
	//		//{
	//		//	continue;
	//		//}
	//		//auto & character      = *(uint8 *)(baseAddr + 0x78  );
	//		//auto & selectedWeapon = *(uint8 *)(baseAddr + 0x6490);
	//		//auto   equipment      =  (uint8 *)(baseAddr + 0x6498);
	//		//auto & weapon = equipment[selectedWeapon];
	//		//if (character != CHAR_DANTE)
	//		//{
	//		//	continue;
	//		//}
	//		//if ((weapon == WEAPON_DANTE_BEOWULF) && !Config.Cosmetics.Dante.Beowulf.hideModel)
	//		//{
	//		//	Cosmetics_Dante_ApplyBeowulfModelAttributes(baseAddr);
	//		//}
	//		//else
	//		//{
	//		//	Cosmetics_Dante_ApplyDefaultModelAttributes(baseAddr);
	//		//}
	//	}
	//};
	//GUI_Hyperlink(Locale.Cosmetics.Dante.header);
	//ImGui::Text("");
	//ImGui::Text(Locale.Cosmetics.Dante.Beowulf.header);
	//if (GUI_Checkbox
	//(
	//	Locale.Cosmetics.Dante.Beowulf.hideModel,
	//	Config.Cosmetics.Dante.Beowulf.hideModel
	//))
	//{
	//	Cosmetics_Dante_ToggleHideBeowulf(Config.Cosmetics.Dante.Beowulf.hideModel);
	//	UpdateModelAttributes();
	//}
}

void GUI_Cosmetics_Doppelganger()
{
	GUI_Hyperlink(Locale.Cosmetics.Doppelganger.header);
	ImGui::Text("");
	if (GUI_Checkbox
	(
		Locale.Cosmetics.Doppelganger.noColor,
		Config.Cosmetics.Doppelganger.noColor
	))
	{
		//// @Todo: Creater helper function.
		//{
		//	if (Config.Game.Multiplayer.enable)
		//	{
		//		goto sect0;
		//	}
		//	if (!InGame())
		//	{
		//		goto sect0;
		//	}
		//	auto & noColor = Config.Cosmetics.Doppelganger.noColor;
		//	auto & baseAddr1 = System_Actor_actorBaseAddr[ACTOR_ONE];
		//	auto & baseAddr2 = System_Actor_actorBaseAddr[ACTOR_TWO];
		//	if (!baseAddr1 || !baseAddr2)
		//	{
		//		goto sect0;
		//	}
		//	auto & shadow1 = *(uint32 *)(baseAddr1 + 0x3A18) = (noColor) ? 1 : 0;
		//	auto & shadow2 = *(uint32 *)(baseAddr2 + 0x3A18) = (noColor) ? 1 : 0;
		//	Cosmetics_Color_ApplyColor(baseAddr2, (Config.Cosmetics.Doppelganger.noColor) ? 7 : 6, 0);
		//}
		sect0:;
	}
}

void GUI_Cosmetics_Object()
{
	GUI_Hyperlink(Locale.Cosmetics.Object.header);
	ImGui::Text("");
	//ImGui::PushItemWidth(200);
	//for (uint8 object = 0; object < Object_Count; object++)
	//{
	//	GUI_Combo<uint8>
	//	(
	//		Locale.Cosmetics.Object.label[object],
	//		Locale.Cosmetics.Object.items,
	//		countof(Locale.Cosmetics.Object.items),
	//		Config.Cosmetics.Object.index[object]
	//	);
	//}
	//ImGui::PopItemWidth();
	//ImGui::Text("");
	//if (GUI_Button(Locale.Cosmetics.Object.reset))
	//{
	//	memcpy(&Config.Cosmetics.Object, &DefaultConfig.Cosmetics.Object, sizeof(Config.Cosmetics.Object));
	//	SaveConfig();
	//}
}

void GUI_Cosmetics_Other()
{
	GUI_Hyperlink(Locale.Cosmetics.Other.header);
	ImGui::Text("");
	if (GUI_Checkbox(Locale.Cosmetics.Other.noDevilForm, Config.Cosmetics.Other.noDevilForm))
	{
		//Cosmetics_Other_ToggleNoDevilForm(Config.Cosmetics.Other.noDevilForm);
	}
}

void GUI_Cosmetics_Vergil()
{
	GUI_Hyperlink(Locale.Cosmetics.Vergil.header);
	ImGui::Text("");
	ImGui::Text(Locale.Cosmetics.Vergil.Beowulf.header);
	if (GUI_Checkbox
	(
		Locale.Cosmetics.Vergil.Beowulf.hideModel,
		Config.Cosmetics.Vergil.Beowulf.hideModel
	))
	{
		//Cosmetics_Vergil_ToggleHideBeowulf(Config.Cosmetics.Vergil.Beowulf.hideModel);
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
		GUI_Cosmetics_Doppelganger();
		ImGui::Text("");
		GUI_Cosmetics_Object();
		ImGui::Text("");
		GUI_Cosmetics_Other();
		ImGui::Text("");
		GUI_Cosmetics_Vergil();
	}
	ImGui::End();
	ImGui::PopStyleVar(3);
}

void GUI_Tools_Overlay()
{
	GUI_SECTION_HEADER(Tools.Overlay);
	ImGui::PushItemWidth(100);
	GUI_Combo<uint8>
	(
		"",
		Locale.Tools.Overlay.FontSize.items,
		countof(Locale.Tools.Overlay.FontSize.items),
		Config.Tools.Overlay.fontSizeIndex
	);
	ImGui::PopItemWidth();
	ImGui::SameLine();
	GUI_ColorEdit4("", Config.Tools.Overlay.color);
	GUI_Checkbox
	(
		Locale.Tools.Overlay.focus,
		Config.Tools.Overlay.focus
	);
	GUI_Checkbox
	(
		Locale.Tools.Overlay.memory,
		Config.Tools.Overlay.memory
	);
	GUI_SECTION_FOOTER_START(Tools.Overlay);
	GUI_Overlay_run = false;
	GUI_SECTION_FOOTER_END;
}

void GUI_Tools_Repair()
{
	GUI_Hyperlink(Locale.Tools.Repair.header);
	ImGui::Text("");
	auto ResetEquipment = []()
	{
		//if (!InGame())
		//{
		//	return;
		//}
		//auto count = System_Actor_GetActorCount();
		////for (uint8 actor = 0; actor < count; actor++)
		////{
		////	auto & baseAddr = System_Actor_actorBaseAddr[actor];
		////	if (!baseAddr)
		////	{
		////		continue;
		////	}
		////	auto & character = *(uint8 *)(baseAddr + 0x78);
		////	auto equipment = (uint8 *)(baseAddr + 0x6498);
		////	vp_memset(equipment, 0, 8);
		////	switch (character)
		////	{
		////	case CHAR_DANTE:
		////		equipment[0] = WEAPON_DANTE_REBELLION;
		////		equipment[1] = WEAPON_DANTE_CERBERUS;
		////		equipment[2] = WEAPON_EBONY_IVORY;
		////		equipment[3] = WEAPON_SHOTGUN;
		////		break;
		////	case CHAR_BOB:
		////		equipment[0] = WEAPON_YAMATO_BOB;
		////		break;
		////	case CHAR_LADY:
		////		equipment[2] = WEAPON_KALINA_ANN;
		////		equipment[4] = 11;
		////		break;
		////	case CHAR_VERGIL:
		////		equipment[0] = WEAPON_YAMATO;
		////		equipment[1] = WEAPON_BEOWULF_VERGIL;
		////		equipment[2] = WEAPON_FORCE_EDGE;
		////		break;
		////	}
		////}
	};
	auto ResetRangedWeaponLevels = []()
	{
		if (!InGame())
		{
			return;
		}
		//auto count = System_Actor_GetActorCount();
		//for (uint8 actor = 0; actor < count; actor++)
		//{
		//	auto & baseAddr = System_Actor_actorBaseAddr[actor];
		//	if (!baseAddr)
		//	{
		//		continue;
		//	}
		//	auto level = (uint32 *)(baseAddr + 0x64E4);
		//	level[0] = 0;
		//	level[1] = 0;
		//}
	};
	if (GUI_Button(Locale.Tools.Repair.resetEquipment))
	{
		ResetEquipment();
	}
	if (GUI_Button(Locale.Tools.Repair.resetRangedWeaponLevels))
	{
		ResetRangedWeaponLevels();
	}
}










void GUI_Tools_Camera()
{
	if (GUI_Hyperlink("Camera"))
	{
		GUI_Camera_show = true;
	}
}






void GUI_Tools_Speed()
{
	if (GUI_Hyperlink(Locale.Tools.Speed.header))
	{
		GUI_Speed_show = true;
	}
}

void GUI_Tools_Teleporter()
{
	if (GUI_Hyperlink(Locale.Tools.Teleporter.header))
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
		GUI_Tools_Camera();
		ImGui::Text("");
		GUI_Tools_Overlay();
		ImGui::Text("");
		GUI_Tools_Repair();
		ImGui::Text("");
		GUI_Tools_Speed();
		ImGui::Text("");
		GUI_Tools_Teleporter();
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
	case TAB_SYSTEM:
		GUI_System_Draw();
		break;
	case TAB_GAME:
		GUI_Game_Draw();
		break;
	case TAB_COSMETICS:
		GUI_Cosmetics_Draw();
		break;
	case TAB_TOOLS:
		GUI_Tools_Draw();
		break;
	}
}






void GUI_Camera_Draw()
{
	static bool run = false;
	if (!run)
	{
		run = true;
		ImGui::SetNextWindowPos(ImVec2(900, 100));
	}
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(1, 1));
	if (ImGui::Begin("Camera", &GUI_Camera_show, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize))
	{
		{
			if (!InGame())
			{
				goto InvalidPointer;
			}
			// @Todo: Add to vars.
			auto addr = *(byte8 **)(appBaseAddr + 0xC8FBD0);
			if (!addr)
			{
				goto InvalidPointer;
			}
			addr = *(byte8 **)(addr + 0x498);
			if (!addr)
			{
				goto InvalidPointer;
			}
			auto & height     = *(float32 *)(addr + 0xD0 );
			auto & tilt       = *(float32 *)(addr + 0xD4 );
			auto & zoom       = *(float32 *)(addr + 0xD8 );
			auto & zoomLockOn = *(float32 *)(addr + 0xE0 );
			ImGui::Text(Locale.Camera.live);
			ImGui::PushItemWidth(200);
			GUI_InputEx<float32>(Locale.Camera.height    , height    , 10  );
			GUI_InputEx<float32>(Locale.Camera.tilt      , tilt      , 0.1f);
			GUI_InputEx<float32>(Locale.Camera.zoom      , zoom      , 50  );
			GUI_InputEx<float32>(Locale.Camera.zoomLockOn, zoomLockOn, 50  );
			ImGui::Text("");
			ImGui::Text(Locale.Camera.config);
			GUI_InputEx<float32>(Locale.Camera.height    , Config.Camera.height    , 10  );
			GUI_InputEx<float32>(Locale.Camera.tilt      , Config.Camera.tilt      , 0.1f);
			GUI_InputEx<float32>(Locale.Camera.zoom      , Config.Camera.zoom      , 50  );
			GUI_InputEx<float32>(Locale.Camera.zoomLockOn, Config.Camera.zoomLockOn, 50  );
			ImGui::PopItemWidth();
			ImGui::Text("");
			GUI_Checkbox
			(
				Locale.Camera.applyConfig,
				Config.Camera.applyConfig
			);
			GUI_PUSH_DISABLE(!Config.Camera.applyConfig);
			{
				ImGui::PushItemWidth(100);
				GUI_InputEx<uint32>
				(
					Locale.Camera.rate,
					Config.Camera.rate,
					100
				);
				ImGui::PopItemWidth();
			}
			GUI_POP_DISABLE(!Config.Camera.applyConfig);
			ImGui::Text("");
			if (GUI_Button(Locale.Camera.reset))
			{
				memcpy(&Config.Camera, &DefaultConfig.Camera, sizeof(Config.Camera));
				SaveConfig();
				Camera_Update(DefaultConfig);
			}
			goto End;
		}
		InvalidPointer:
		ImGui::Text("Invalid Pointer!");
	}
	End:
	ImGui::End();
	ImGui::PopStyleVar(3);
}







void GUI_Speed_Draw()
{
	static bool run = false;
	if (!run)
	{
		run = true;
		ImGui::SetNextWindowSize(ImVec2((GUI_Speed_size.x + 16), (GUI_Speed_size.y + 16)));
		ImGui::SetNextWindowPos(ImVec2(530, 40));
	}
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(1, 1));
	if (ImGui::Begin("Speed", &GUI_Speed_show, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse))
	{
		if constexpr (debug)
		{
			auto pos = ImGui::GetWindowPos();
			ImGui::Text("%f %f", pos.x, pos.y);
		}
		auto InputExSpeed = []
		(
			const char * label,
			float32    & var
		)
		{
			if (GUI_InputEx<float32>(label, var, 0.1f))
			{
				var = (ceilf(var * 10000) / 10000);
				//Speed_Update(Config);
			}
		};
		auto InputExSpeedMulti = [&]
		(
			const char ** label,
			float32    *  var,
			uint8         count
		)
		{
			for (uint8 index = 0; index < count; index++)
			{
				InputExSpeed(label[index], var[index]);
			}
		};
		ImGui::PushItemWidth(200);
		//ImGui::Text(Locale.Speed.FrameRate.header);
		//if (GUI_InputEx<uint32>
		//(
		//	Locale.Speed.FrameRate.target,
		//	Config.Speed.FrameRate.target
		//))
		//{
		//	Speed_Update(Config);
		//}
		//ImGui::SameLine();
		//GUI_Tooltip(Locale.Speed.FrameRate.hint, 300);
		//if constexpr (debug)
		//{
		//	ImGui::Text("Multiplier %.3f", Speed_FrameRate_multiplier);
		//}
		ImGui::Text(Locale.Speed.Main.header);
		InputExSpeed
		(
			Locale.Speed.Main.base,
			Config.Speed.Main.base
		);
		ImGui::SameLine(300);
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 1, 0, 1));
		//ImGui::Text("%.3f", (DefaultConfig.Speed.Main.base * System_Graphics_frameRateMultiplier));
		ImGui::PopStyleColor();
		InputExSpeed
		(
			Locale.Speed.Main.turbo,
			Config.Speed.Main.turbo
		);
		ImGui::SameLine(300);
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 1, 0, 1));
		//ImGui::Text("%.3f", (DefaultConfig.Speed.Main.turbo * System_Graphics_frameRateMultiplier));
		ImGui::PopStyleColor();
		InputExSpeed
		(
			Locale.Speed.Main.actor,
			Config.Speed.Main.actor
		);
		InputExSpeed
		(
			Locale.Speed.Main.enemy,
			Config.Speed.Main.enemy
		);
		ImGui::Text(Locale.Speed.Devil.header);
		ImGui::Text(Locale.Speed.Devil.Dante.header);
		InputExSpeedMulti
		(
			Locale.Speed.Devil.Dante.label,
			Config.Speed.Devil.dante,
			countof(Config.Speed.Devil.dante)
		);
		ImGui::Text(Locale.Speed.Devil.Vergil.header);
		InputExSpeedMulti
		(
			Locale.Speed.Devil.Vergil.label,
			Config.Speed.Devil.vergil,
			countof(Config.Speed.Devil.vergil)
		);
		ImGui::Text(Locale.Speed.Devil.NeroAngelo.header);
		InputExSpeedMulti
		(
			Locale.Speed.Devil.NeroAngelo.label,
			Config.Speed.Devil.neroAngelo,
			countof(Config.Speed.Devil.neroAngelo)
		);
		ImGui::Text(Locale.Speed.Quicksilver.header);
		InputExSpeed
		(
			Locale.Speed.Quicksilver.actor,
			Config.Speed.Quicksilver.actor
		);
		InputExSpeed
		(
			Locale.Speed.Quicksilver.enemy,
			Config.Speed.Quicksilver.enemy
		);
		ImGui::PopItemWidth();
		ImGui::Text("");
		if (GUI_Button(Locale.Speed.reset))
		{
			memcpy(&Config.Speed, &DefaultConfig.Speed, sizeof(Config.Speed));
			SaveConfig();
			//Speed_Update(DefaultConfig);
		}
	}
	ImGui::End();
	ImGui::PopStyleVar(3);
}



























void GUI_Teleporter_Draw()
{
	static bool run = false;
	if (!run)
	{
		run = true;
		ImGui::SetNextWindowSize(ImVec2(GUI_Teleporter_size.x + 16, GUI_Teleporter_size.y + 16));
		ImGui::SetNextWindowPos(ImVec2(10, 530));
	}
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(1, 1));
	if (ImGui::Begin(Locale.Tools.Teleporter.header, &GUI_Teleporter_show, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize))
	{



		//DrawRelativeTilt();


		{
			
			GUI_InputEx("group", g_motionGroup);
			GUI_InputEx("index", g_motionIndex);
			GUI_Checkbox("Log", g_logMotionData);
			ImGui::Text("");
		}




		{
			static uint32 index = 0;
			GUI_InputEx<uint32>("Index", index);
			if (GUI_Button("Summon Swords"))
			{
				func_223F50(Actor_actorBaseAddr[0], index);
			}
			if (GUI_Button("Create Swords"))
			{
				func_223AC0(Actor_actorBaseAddr[0]);
			}
			if (GUI_Button("Shoot Sword"))
			{
				func_223BE0(Actor_actorBaseAddr[0], index);
			}
		}











		{
			static uint8 style = 0;
			GUI_InputEx<uint8>("Style", style);
			if (GUI_Button("Update Style Icon"))
			{
				//UpdateStyleIcon(style, styleIconDante[style].model, styleIconDante[style].texture);
			}
		}


		{
			static uint8 index = 0;
			static uint8 weapon = 0;
			GUI_InputEx<uint8>("Index", index);
			GUI_InputEx<uint8>("Weapon", weapon);
			if (GUI_Button("Update Weapon Icon"))
			{
				//UpdateWeaponIcon(index, weaponIcon[weapon].model, weaponIcon[weapon].texture);
			}
		}












		{
			static uint32 off = 0;
			if (GUI_Button("Hide"))
			{
				auto g_pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);
				auto hud = *reinterpret_cast<byte8 **>(g_pool[11]);
				auto dest = (hud + off);
				auto & visible = *reinterpret_cast<bool *>(dest + 0x18) = false;
			}
			ImGui::SameLine();
			if (GUI_Button("Show"))
			{
				auto g_pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);
				auto hud = *reinterpret_cast<byte8 **>(g_pool[11]);
				auto dest = (hud + off);
				auto & visible = *reinterpret_cast<bool *>(dest + 0x18) = true;
			}
			ImGui::SameLine();
			GUI_InputEx<uint32>("Offset", off, 1, true, false);
		}









		if constexpr (debug)
		{
			auto pos = ImGui::GetWindowPos();
			ImGui::Text("%f %f", pos.x, pos.y);
		}
		{
			if (!InGame())
			{
				goto InvalidPointer;
			}
			VARS vars;
			if (!vars.init)
			{
				goto InvalidPointer;
			}
			uint32 & room         = *vars.room;
			uint32 & position     = *vars.position;
			uint32 & event        = *vars.event;
			uint16 & nextRoom     = *vars.nextRoom;
			uint16 & nextPosition = *vars.nextPosition;
			ImGui::PushItemWidth(100);
			ImGui::Text(Locale.Teleporter.current);
			GUI_Input("", room, false, ImGuiInputTextFlags_ReadOnly);
			GUI_Input("", position, false, ImGuiInputTextFlags_ReadOnly);
			ImGui::Text(Locale.Teleporter.next);
			GUI_InputEx<uint16>("", nextRoom);
			GUI_InputEx<uint16>("", nextPosition);
			if (GUI_Button(Locale.Teleporter.teleport))
			{
				event = EVENT_TELEPORT;
			}
			ImGui::PopItemWidth();
			goto TeleporterEnd;
		}
		InvalidPointer:
		ImGui::Text(Locale.Teleporter.invalidPointer);
		TeleporterEnd:;
	}
	ImGui::End();
	ImGui::PopStyleVar(3);
}







void GUI_Overlay_Draw()
{
	if (!GUI_Overlay_run)
	{
		GUI_Overlay_run = true;
		ImGui::SetNextWindowSize(ImVec2(GUI_Overlay_size.x + 16, GUI_Overlay_size.y + 16));
		ImGui::SetNextWindowPos(ImVec2(Config.Tools.Overlay.x, Config.Tools.Overlay.y));
	}
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(1, 1));
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));
	if (ImGui::Begin("GUI_Overlay", &Config.Tools.Overlay.enable, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize))
	{
		{
			ImVec2 pos = ImGui::GetWindowPos();
			if ((Config.Tools.Overlay.x != pos.x) || (Config.Tools.Overlay.y != pos.y))
			{
				Config.Tools.Overlay.x = pos.x;
				Config.Tools.Overlay.y = pos.y;
				SaveConfig();
			}
		}
		ImGuiIO & io = ImGui::GetIO();
		ImGui::PushFont(io.Fonts->Fonts[FONT_OVERLAY_8 + Config.Tools.Overlay.fontSizeIndex]);
		ImGui::PushStyleColor(ImGuiCol_Text, *(ImVec4 *)Config.Tools.Overlay.color);
		//if (Config.Tools.Overlay.heapFrame)
		//{
		//	auto & value = *(uint32 *)(appBaseAddr + 0xCA8958);
		//	ImGui::Text("%s %u", Locale.Tools.Overlay.heapFrame, value);
		//}
		if (Config.Tools.Overlay.focus)
		{
			ImVec4 color = ImVec4(0, 1, 0, 1);
			if (GetForegroundWindow() != appWindow)
			{
				color = ImVec4(1, 0, 0, 1);
			}
			ImGui::PushStyleColor(ImGuiCol_Text, color);
			ImGui::Text(Locale.Tools.Overlay.focus);
			ImGui::PopStyleColor();
		}
		//ImGui::Text("%llu", Game_StyleSwitcher_counter);


		ImGui::Text("%.3f FPS", (ImGui::GetIO().Framerate));


		if (Config.Tools.Overlay.memory)
		{
			uint32 off[] =
			{
				0xCA8910,
				0xCA8938,
				0xCA8960,
			};
			for (uint8 index = 0; index < countof(off); index++)
			{
				MEMORY_OBJECT & object = *(MEMORY_OBJECT *)(appBaseAddr + off[index]);
				ImGui::Text("__%.4u__", index);
				ImGui::Text("addr     %llX", object.addr);
				ImGui::Text("end      %llX", object.end);
				ImGui::Text("last     %X", object.last);
				ImGui::Text("boundary %X", object.boundary);
				ImGui::Text("size     %X", object.size);
				ImGui::Text("pipe     %u", object.pipe);
				ImGui::Text("count    %u", object.count);
			}
		}


		//ImGui::Text("devilCounter %u", devilCounter);


		//ImGui::Text("Delta %f", Update_delta);




		

		//ImGui::Text("%f value", GUI_value);
		//ImGui::Text("%f valueRounded", GUI_valueRounded);





		/*
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		*/


		ImGui::PopStyleColor();
		ImGui::PopFont();
	}
	ImGui::End();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar(3);
}

void DrawRestartOverlay()
{
	//static ImVec2 size = {};
	//ImVec2 position = {};
	//position.x = (ImGui::GetIO().DisplaySize.x - size.x) / 2;
	//position.y = (ImGui::GetIO().DisplaySize.y - size.y) / 2;
	//ImGui::SetNextWindowPos(position);
	//ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	//ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	//ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(1, 1));
	//ImGui::PushStyleColor(ImGuiCol_WindowBg, ImGui::GetStyle().Colors[ImGuiCol_WindowBg]);
	//if (ImGui::Begin("RestartOverlay", &restart, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_AlwaysAutoResize))
	//{
	//	size = ImGui::GetWindowSize();
	//	ImGuiIO & io = ImGui::GetIO();
	//	ImGui::PushFont(io.Fonts->Fonts[1]);
	//	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 0, 0, 1));
	//	//ImGui::Text(Locale.restartRequired);
	//	ImGui::PopStyleColor();
	//	ImGui::PopFont();
	//}
	//ImGui::End();
	//ImGui::PopStyleColor();
	//ImGui::PopStyleVar(3);
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
	if (Config.Tools.Overlay.enable)
	{
		GUI_Overlay_Draw();
	}
	if (GUI_Camera_show)
	{
		GUI_Camera_Draw();
	}
	if (GUI_Speed_show)
	{
		GUI_Speed_Draw();
	}
	if (GUI_Teleporter_show)
	{
		GUI_Teleporter_Draw();
	}
	//if (restart)
	//{
	//	DrawRestartOverlay();
	//}
}

void GUI_Init()
{
	BuildFonts();
}
