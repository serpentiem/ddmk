#include "GUI.h"

#pragma warning(disable: 4102) // Unreferenced Label



bool debug = false;

enum TAB_
{
	TAB_GAME,
	TAB_SYSTEM,
	TAB_TOOLS,
	MAX_TAB,
	TAB_VOID,
};

uint8 activeTab = TAB_VOID;

ImVec2 GUI_Game_size       = ImVec2(500, 500);
ImVec2 GUI_System_size     = ImVec2(300, 300);
ImVec2 GUI_Tools_size      = ImVec2(300, 300);
ImVec2 GUI_Teleporter_size = ImVec2(300, 300);

bool GUI_Teleporter_show = false;

void GUI_Game_Arcade()
{
	static uint8 modeIndex         = 0;
	static uint8 meleeWeaponIndex  = 0;
	static uint8 rangedWeaponIndex = 0;
	static bool  run               = false;
	if (!run)
	{
		run = true;
		for (uint8 i = 0; i < countof(Game_Arcade_modeMask); i++)
		{
			if (Config.Game.Arcade.mode == Game_Arcade_modeMask[i])
			{
				modeIndex = i;
				break;
			}
		}
		for (uint8 i = 0; i < countof(Game_Arcade_meleeWeaponMask); i++)
		{
			if (Config.Game.Arcade.meleeWeapon == Game_Arcade_meleeWeaponMask[i])
			{
				meleeWeaponIndex = i;
				break;
			}
		}
		for (uint8 i = 0; i < countof(Game_Arcade_rangedWeaponMask); i++)
		{
			if (Config.Game.Arcade.rangedWeapon == Game_Arcade_rangedWeaponMask[i])
			{
				rangedWeaponIndex = i;
				break;
			}
		}
	}
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
	ImGui::PushItemWidth(150);
	GUI_Combo<uint8>
	(
		Locale.Game.Arcade.Mission.label,
		Locale.Game.Arcade.Mission.items,
		countof(Locale.Game.Arcade.Mission.items),
		Config.Game.Arcade.mission
	);
	if (GUI_Combo<uint8>
	(
		Locale.Game.Arcade.Mode.label,
		Locale.Game.Arcade.Mode.items,
		countof(Locale.Game.Arcade.Mode.items),
		modeIndex,
		0,
		false
	))
	{
		Config.Game.Arcade.mode = Game_Arcade_modeMask[modeIndex];
		SaveConfig();
	}
	if (debug)
	{
		ImGui::Text("index   %u", modeIndex);
		ImGui::Text("true id %u", Config.Game.Arcade.mode);
	}
	GUI_InputEx<uint16>(Locale.Game.Arcade.room, Config.Game.Arcade.room);
	ImGui::SameLine();
	GUI_Checkbox(Locale.Game.Arcade.ignoreRoom, Config.Game.Arcade.ignoreRoom);
	GUI_Combo<uint8>
	(
		Locale.Game.Arcade.Character.label,
		Locale.Game.Arcade.Character.items,
		countof(Locale.Game.Arcade.Character.items),
		Config.Game.Arcade.character
	);
	if (GUI_Combo<uint8>
	(
		Locale.Game.Arcade.MeleeWeapon.label,
		Locale.Game.Arcade.MeleeWeapon.items,
		countof(Locale.Game.Arcade.MeleeWeapon.items),
		meleeWeaponIndex,
		0,
		false
	))
	{
		Config.Game.Arcade.meleeWeapon = Game_Arcade_meleeWeaponMask[meleeWeaponIndex];
		SaveConfig();
	}
	uint8 & weapon = Config.Game.Arcade.meleeWeapon;
	if (weapon == WEAPON_FORCE_EDGE)
	{
		ImGui::SameLine();
		GUI_Checkbox(Locale.Game.Arcade.MeleeWeapon.sparda, Config.Game.Arcade.meleeWeaponSparda);
	}
	else if (weapon == WEAPON_ALASTOR)
	{
		ImGui::SameLine();
		GUI_Checkbox(Locale.Game.Arcade.MeleeWeapon.yamato, Config.Game.Arcade.meleeWeaponYamato);
	}
	if (debug)
	{
		ImGui::Text("index   %u", meleeWeaponIndex);
		ImGui::Text("true id %u", Config.Game.Arcade.meleeWeapon);
	}
	if (GUI_Combo<uint8>
	(
		Locale.Game.Arcade.RangedWeapon.label,
		Locale.Game.Arcade.RangedWeapon.items,
		countof(Locale.Game.Arcade.RangedWeapon.items),
		rangedWeaponIndex,
		0,
		false
	))
	{
		Config.Game.Arcade.rangedWeapon = Game_Arcade_rangedWeaponMask[rangedWeaponIndex];
		SaveConfig();
	}
	if (debug)
	{
		ImGui::Text("index   %u", rangedWeaponIndex);
		ImGui::Text("true id %u", Config.Game.Arcade.rangedWeapon);
	}
	GUI_InputEx<uint8>(Locale.Game.Arcade.hitPointsUnitCount, Config.Game.Arcade.hitPointsUnitCount);
	GUI_InputEx<uint8>(Locale.Game.Arcade.magicPointsUnitCount, Config.Game.Arcade.magicPointsUnitCount);
	ImGui::PopItemWidth();
	GUI_SECTION_FOOTER_START(Game.Arcade);
	run = false;
	Game_Arcade_Toggle(DefaultConfig.Game.Arcade.enable);
	GUI_SECTION_FOOTER_END;
}

void GUI_Game_BossRush()
{
	GUI_SECTION_HEADER_START(Game.BossRush);
	if (Config.Game.BossRush.enable)
	{
		Game_BossRush_Toggle(Config.Game.BossRush.enable);
	}
	else
	{
		Game_BossRush_Toggle(DefaultConfig.Game.BossRush.enable);
	}
	GUI_SECTION_HEADER_END(Game.BossRush);
	ImGui::Text(Locale.Game.BossRush.Mission22.header);
	GUI_Checkbox(Locale.Game.BossRush.Mission22.skipAerialBattle, Config.Game.BossRush.Mission22.skipAerialBattle);
	GUI_SECTION_FOOTER_START(Game.BossRush);
	Game_BossRush_Toggle(DefaultConfig.Game.BossRush.enable);
	GUI_SECTION_FOOTER_END;
}

void GUI_Game_Dante()
{
	GUI_SECTION_HEADER_START(Game.Dante);
	if (Config.Game.Dante.enable)
	{
		Game_Dante_ForceEdge_ToggleUnlockStinger(Config.Game.Dante.ForceEdge.unlockStinger);
		Game_Dante_ForceEdge_ToggleUnlockRoundTrip(Config.Game.Dante.ForceEdge.unlockRoundTrip);
		Game_Dante_Sparda_ToggleUnlockDevilTrigger(Config.Game.Dante.Sparda.unlockDevilTrigger);
		Game_Dante_Sparda_ToggleForceLoadAssets(Config.Game.Dante.Sparda.forceLoadAssets);
		Game_Dante_Yamato_ToggleUnlock(Config.Game.Dante.Yamato.unlock);
		Game_Dante_AirHike_ToggleCoreAbility(Config.Game.Dante.AirHike.coreAbility);
	}
	else
	{
		Game_Dante_ForceEdge_ToggleUnlockStinger(DefaultConfig.Game.Dante.ForceEdge.unlockStinger);
		Game_Dante_ForceEdge_ToggleUnlockRoundTrip(DefaultConfig.Game.Dante.ForceEdge.unlockRoundTrip);
		Game_Dante_Sparda_ToggleUnlockDevilTrigger(DefaultConfig.Game.Dante.Sparda.unlockDevilTrigger);
		Game_Dante_Sparda_ToggleForceLoadAssets(DefaultConfig.Game.Dante.Sparda.forceLoadAssets);
		Game_Dante_Yamato_ToggleUnlock(DefaultConfig.Game.Dante.Yamato.unlock);
		Game_Dante_AirHike_ToggleCoreAbility(DefaultConfig.Game.Dante.AirHike.coreAbility);
	}
	GUI_SECTION_HEADER_END(Game.Dante);
	ImGui::Text(Locale.Game.Dante.ForceEdge.header);
	if (GUI_Checkbox(Locale.Game.Dante.ForceEdge.unlockStinger, Config.Game.Dante.ForceEdge.unlockStinger))
	{
		Game_Dante_ForceEdge_ToggleUnlockStinger(Config.Game.Dante.ForceEdge.unlockStinger);
	}
	if (GUI_Checkbox(Locale.Game.Dante.ForceEdge.unlockRoundTrip, Config.Game.Dante.ForceEdge.unlockRoundTrip))
	{
		Game_Dante_ForceEdge_ToggleUnlockRoundTrip(Config.Game.Dante.ForceEdge.unlockRoundTrip);
	}
	ImGui::Text(Locale.Game.Dante.Sparda.header);
	if (GUI_Checkbox(Locale.Game.Dante.Sparda.unlockDevilTrigger, Config.Game.Dante.Sparda.unlockDevilTrigger))
	{
		Game_Dante_Sparda_ToggleUnlockDevilTrigger(Config.Game.Dante.Sparda.unlockDevilTrigger);
	}
	if (GUI_Checkbox(Locale.Game.Dante.Sparda.forceLoadAssets, Config.Game.Dante.Sparda.forceLoadAssets))
	{
		Game_Dante_Sparda_ToggleForceLoadAssets(Config.Game.Dante.Sparda.forceLoadAssets);
	}
	ImGui::Text(Locale.Game.Dante.Yamato.header);
	if (GUI_Checkbox(Locale.Game.Dante.Yamato.unlock, Config.Game.Dante.Yamato.unlock))
	{
		Game_Dante_Yamato_ToggleUnlock(Config.Game.Dante.Yamato.unlock);
	}
	GUI_PUSH_DISABLE(!InGame());
	ImGui::SameLine();
	if (GUI_Button(Locale.Game.Dante.Yamato.acquire))
	{
		Game_Dante_Yamato_Acquire();
	}
	GUI_POP_DISABLE(!InGame());
	ImGui::Text(Locale.Game.Dante.AirHike.header);
	if (GUI_Checkbox(Locale.Game.Dante.AirHike.coreAbility, Config.Game.Dante.AirHike.coreAbility))
	{
		Game_Dante_AirHike_ToggleCoreAbility(Config.Game.Dante.AirHike.coreAbility);
	}
	GUI_SECTION_FOOTER_START(Game.Dante);
	Game_Dante_ForceEdge_ToggleUnlockStinger(DefaultConfig.Game.Dante.ForceEdge.unlockStinger);
	Game_Dante_ForceEdge_ToggleUnlockRoundTrip(DefaultConfig.Game.Dante.ForceEdge.unlockRoundTrip);
	Game_Dante_Sparda_ToggleUnlockDevilTrigger(DefaultConfig.Game.Dante.Sparda.unlockDevilTrigger);
	Game_Dante_Sparda_ToggleForceLoadAssets(DefaultConfig.Game.Dante.Sparda.forceLoadAssets);
	Game_Dante_Yamato_ToggleUnlock(DefaultConfig.Game.Dante.Yamato.unlock);
	Game_Dante_AirHike_ToggleCoreAbility(DefaultConfig.Game.Dante.AirHike.coreAbility);
	GUI_SECTION_FOOTER_END;
}

void GUI_Game_LockOn()
{
	static uint8 buttonIndex = 0;
	static bool  run         = false;
	if (!run)
	{
		run = true;
		for (uint8 i = 0; i < countof(Game_LockOn_buttonMap); i++)
		{
			if (Config.Game.LockOn.button == Game_LockOn_buttonMap[i])
			{
				buttonIndex = i;
				break;
			}
		}
	}
	GUI_SECTION_HEADER_START(Game.LockOn);
	if (Config.Game.LockOn.enable)
	{
		Game_LockOn_Toggle(Config.Game.LockOn.enable);
	}
	else
	{
		Game_LockOn_Toggle(DefaultConfig.Game.LockOn.enable);
	}
	GUI_SECTION_HEADER_END(Game.LockOn);
	ImGui::PushItemWidth(150);
	if (GUI_Combo<uint8>
	(
		Locale.Game.LockOn.Button.label,
		Locale.Game.LockOn.Button.items,
		countof(Locale.Game.LockOn.Button.items),
		buttonIndex,
		0,
		false
	))
	{
		Config.Game.LockOn.button = Game_LockOn_buttonMap[buttonIndex];
		SaveConfig();
	}
	if (debug)
	{
		ImGui::Text("index   %u", buttonIndex);
		ImGui::Text("true id %X", Config.Game.LockOn.button);
	}
	ImGui::PopItemWidth();
	GUI_SECTION_FOOTER_START(Game.LockOn);
	run = false;
	Game_LockOn_Toggle(DefaultConfig.Game.LockOn.enable);
	GUI_SECTION_FOOTER_END;
}

void GUI_Game_MissionSelect()
{
	static uint8 modeIndex = 0;
	static bool  run       = false;
	if (!run)
	{
		run = true;
		for (uint8 i = 0; i < countof(Game_MissionSelect_modeMask); i++)
		{
			if (Config.Game.MissionSelect.mode == Game_MissionSelect_modeMask[i])
			{
				modeIndex = i;
				break;
			}
		}
	}
	GUI_SECTION_HEADER(Game.MissionSelect);
	ImGui::PushItemWidth(130);
	GUI_Combo<uint8>
	(
		Locale.Game.MissionSelect.Mission.label,
		Locale.Game.MissionSelect.Mission.items,
		countof(Locale.Game.MissionSelect.Mission.items),
		Config.Game.MissionSelect.mission
	);
	if (GUI_Combo<uint8>
	(
		Locale.Game.MissionSelect.Mode.label,
		Locale.Game.MissionSelect.Mode.items,
		countof(Locale.Game.MissionSelect.Mode.items),
		modeIndex,
		0,
		false
	))
	{
		Config.Game.MissionSelect.mode = Game_MissionSelect_modeMask[modeIndex];
		SaveConfig();
	}
	if (debug)
	{
		ImGui::Text("index   %u", modeIndex);
		ImGui::Text("true id %u", Config.Game.MissionSelect.mode);
	}
	ImGui::PopItemWidth();
	GUI_SECTION_FOOTER_START(Game.MissionSelect);
	run = false;
	GUI_SECTION_FOOTER_END;
}

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
	GUI_SECTION_HEADER(Game.ResetMotionState);
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
	GUI_SECTION_FOOTER_START(Game.ResetMotionState);
	run = false;
	GUI_SECTION_FOOTER_END;
}

void GUI_Game_Training()
{
	GUI_SECTION_HEADER_START(Game.Training);
	if (Config.Game.Training.enable)
	{
		Game_Training_ToggleInfiniteHitPoints(Config.Game.Training.infiniteHitPoints);
		Game_Training_ToggleInfiniteMagicPoints(Config.Game.Training.infiniteMagicPoints);
		Game_Training_ToggleDisableTimer(Config.Game.Training.disableTimer);
	}
	else
	{
		Game_Training_ToggleInfiniteHitPoints(DefaultConfig.Game.Training.infiniteHitPoints);
		Game_Training_ToggleInfiniteMagicPoints(DefaultConfig.Game.Training.infiniteMagicPoints);
		Game_Training_ToggleDisableTimer(DefaultConfig.Game.Training.disableTimer);
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
	Game_Training_ToggleInfiniteHitPoints(DefaultConfig.Game.Training.infiniteHitPoints);
	Game_Training_ToggleInfiniteMagicPoints(DefaultConfig.Game.Training.infiniteMagicPoints);
	Game_Training_ToggleDisableTimer(DefaultConfig.Game.Training.disableTimer);
	GUI_SECTION_FOOTER_END;
}

void GUI_Game_WeaponSwitcher()
{
	static uint8 Melee_weaponIndex [4] = {};
	static uint8 Ranged_weaponIndex[4] = {};
	static bool  run                   = false;
	if (!run)
	{
		run = true;
		for (uint8 slot = 0; slot < 4; slot++)
		{
			for (uint8 i = 0; i < countof(Game_WeaponSwitcher_Melee_weaponMask); i++)
			{
				if (Config.Game.WeaponSwitcher.Melee.weapon[slot] == Game_WeaponSwitcher_Melee_weaponMask[i])
				{
					Melee_weaponIndex[slot] = i;
					break;
				}
			}
		}
		for (uint8 slot = 0; slot < 4; slot++)
		{
			for (uint8 i = 0; i < countof(Game_WeaponSwitcher_Ranged_weaponMask); i++)
			{
				if (Config.Game.WeaponSwitcher.Ranged.weapon[slot] == Game_WeaponSwitcher_Ranged_weaponMask[i])
				{
					Ranged_weaponIndex[slot] = i;
					break;
				}
			}
		}
	}
	GUI_SECTION_HEADER_START(Game.WeaponSwitcher);
	if (Config.Game.WeaponSwitcher.enable)
	{
		Game_WeaponSwitcher_Toggle(Config.Game.WeaponSwitcher.enable);
	}
	else
	{
		Game_WeaponSwitcher_Toggle(DefaultConfig.Game.WeaponSwitcher.enable);
	}
	GUI_SECTION_HEADER_END(Game.WeaponSwitcher);
	ImGui::PushItemWidth(150);
	ImGui::Text(Locale.Game.WeaponSwitcher.Melee.header);
	GUI_Slider("", Config.Game.WeaponSwitcher.Melee.count, 1, 4);
	for (uint8 slot = 0; slot < 4; slot++)
	{
		bool skip = (slot >= Config.Game.WeaponSwitcher.Melee.count) ? true : false;
		GUI_PUSH_DISABLE(skip);
		if (GUI_Combo<uint8>
		(
			"",
			Locale.Game.WeaponSwitcher.Melee.weapon,
			countof(Locale.Game.WeaponSwitcher.Melee.weapon),
			Melee_weaponIndex[slot]
		))
		{
			Config.Game.WeaponSwitcher.Melee.weapon[slot] = Game_WeaponSwitcher_Melee_weaponMask[Melee_weaponIndex[slot]];
			SaveConfig();
		}
		uint8 & weapon = Config.Game.WeaponSwitcher.Melee.weapon[slot];
		if (weapon == WEAPON_FORCE_EDGE)
		{
			ImGui::SameLine();
			GUI_Checkbox(Locale.Game.WeaponSwitcher.Melee.sparda, Config.Game.WeaponSwitcher.Melee.sparda[slot]);
		}
		else if (weapon == WEAPON_ALASTOR)
		{
			ImGui::SameLine();
			GUI_Checkbox(Locale.Game.WeaponSwitcher.Melee.yamato, Config.Game.WeaponSwitcher.Melee.yamato[slot]);
		}
		GUI_POP_DISABLE(skip);
		if (debug)
		{
			ImGui::Text("index   %u", Melee_weaponIndex[slot]);
			ImGui::Text("true id %u", Config.Game.WeaponSwitcher.Melee.weapon[slot]);
		}
	}
	GUI_InputEx<float32>(Locale.Game.WeaponSwitcher.Melee.timeout, Config.Game.WeaponSwitcher.Melee.timeout);
	ImGui::PopItemWidth();
	GUI_SECTION_FOOTER_START(Game.WeaponSwitcher);
	run = false;
	Game_WeaponSwitcher_Toggle(DefaultConfig.Game.WeaponSwitcher.enable);
	GUI_SECTION_FOOTER_END;
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
		GUI_Game_LockOn();
		ImGui::Text("");
		GUI_Game_MissionSelect();
		ImGui::Text("");
		GUI_Game_ResetMotionState();
		ImGui::Text("");
		GUI_Game_Training();
		ImGui::Text("");
		GUI_Game_WeaponSwitcher();
	}
	ImGui::End();
	ImGui::PopStyleVar(3);
}

void GUI_System_Input()
{
	GUI_Hyperlink(Locale.System.Input.header);
	ImGui::Text("");
	ImGui::Text(Locale.System.Input.Mouse.header);
	ImGui::PushItemWidth(120);
	GUI_Checkbox(Locale.System.Input.Mouse.hideCursor, Config.System.Input.Mouse.hideCursor);
	GUI_InputEx(Locale.System.Input.Mouse.updateRate, Config.System.Input.Mouse.updateRate);
	ImGui::PopItemWidth();
}

void GUI_System_Window()
{
	GUI_Hyperlink(Locale.System.Window.header);
	ImGui::Text("");
	GUI_Checkbox(Locale.System.Window.forceFocus, Config.System.Window.forceFocus);
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
	TeleporterStart:
	if (ImGui::Begin("Teleporter", &GUI_Teleporter_show, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize))
	{
		if (!InGame())
		{
			ImGui::Text("Invalid pointer!");
			goto TeleporterEnd;
		}
		ImGui::Text("yar!");
	}
	TeleporterEnd:
	ImGui::End();
	ImGui::PopStyleVar(3);
}

void GUI_Main_Tab(const char * label, uint8 index)
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
	ImVec2 len = ImGui::CalcTextSize(label);
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
	ImGui::RenderText(ImGui::GetCurrentWindow()->DC.CursorPos, label);
	ImGui::SetCursorPos(ImVec2(pos.x + size.x + 8.0f, pos.y));
}

void GUI_Main_Draw()
{
	static bool run = false;
	if (!run)
	{
		run = true;
		ImGui::SetNextWindowSize(ImVec2((float32)::System::Window::width, 25));
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
	case TAB_SYSTEM:
		GUI_System_Draw();
		break;
	case TAB_TOOLS:
		GUI_Tools_Draw();
		break;
	}
}

void GUI_Render()
{
	GUI_id = 0;
	if (pause)
	{
		GUI_Main_Draw();
		if (GUI_Teleporter_show)
		{
			GUI_Teleporter_Draw();
		}
	}
}
