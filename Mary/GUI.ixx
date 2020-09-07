#ifndef __MODULE_GUI__
#define __MODULE_GUI__

module;
#include "../Core/Core.h"

#include "../ImGui/imgui.h"

#include "Locale.h"
#include "Vars.h"
export module ModuleName(GUI);

import ModuleName(Core_GUI);

import ModuleName(Actor);
import ModuleName(Arcade);
import ModuleName(Camera);
import ModuleName(Config);
import ModuleName(Event);
import ModuleName(File);
import ModuleName(Internal);
import ModuleName(Model);
import ModuleName(Pause);
import ModuleName(Scene);
import ModuleName(Speed);
import ModuleName(State);
import ModuleName(Training);
import ModuleName(Window);

#ifdef __INTELLISENSE__
#include "../Core/GUI.ixx"

#include "Actor.ixx"
#include "Arcade.ixx"
#include "Camera.ixx"
#include "Config.ixx"
#include "Event.ixx"
#include "File.ixx"
#include "Internal.ixx"
#include "Model.ixx"
#include "Pause.ixx"
#include "Scene.ixx"
#include "Speed.ixx"
#include "State.ixx"
#include "Training.ixx"
#include "Window.ixx"
#endif

#define debug true

enum FONT_
{
	FONT_DEFAULT,
	FONT_MAIN,
	FONT_OVERLAY_8,
	FONT_OVERLAY_16,
	FONT_OVERLAY_32,
	FONT_OVERLAY_64,
	FONT_OVERLAY_128,
};

void BuildFonts()
{
	ImGuiIO & io = ImGui::GetIO();
	io.Fonts->AddFontDefault();
	char overlayFont[512];
	{
		char buffer[64];
		GetWindowsDirectoryA(buffer, sizeof(buffer));
		snprintf(overlayFont, sizeof(overlayFont), "%s\\Fonts\\consola.ttf", buffer);
	}
	io.Fonts->AddFontFromFileTTF(overlayFont, 17);
	io.Fonts->AddFontFromFileTTF(overlayFont, 8);
	io.Fonts->AddFontFromFileTTF(overlayFont, 16);
	io.Fonts->AddFontFromFileTTF(overlayFont, 32);
	io.Fonts->AddFontFromFileTTF(overlayFont, 64);
	io.Fonts->AddFontFromFileTTF(overlayFont, 128);
	io.Fonts->Build();
}

bool Overlay_enable = true;
bool Overlay_run = false;
ImVec2 Overlay_size = ImVec2(300, 300);

void Overlay()
{
	if (!Overlay_run)
	{
		Overlay_run = true;
		ImGui::SetNextWindowSize(ImVec2(Overlay_size.x + 16, Overlay_size.y + 16));
		ImGui::SetNextWindowPos(ImVec2(0, 0));
	}
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(1, 1));
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));
	if (ImGui::Begin("GUI_Overlay", &Overlay_enable, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize))
	{
		auto & io = ImGui::GetIO();
		ImGui::PushFont(io.Fonts->Fonts[FONT_OVERLAY_16]);
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 0, 0, 1));

		{
			ImVec4 color = ImVec4(0, 1, 0, 1);
			if (GetForegroundWindow() != appWindow)
			{
				color = ImVec4(1, 0, 0, 1);
			}
			ImGui::PushStyleColor(ImGuiCol_Text, color);
			ImGui::Text("Focus");
			ImGui::PopStyleColor();
		}

		ImGui::Text("%.3f FPS", (ImGui::GetIO().Framerate));

		ImGui::Text("g_scene %u", g_scene);

		constexpr uint32 off[] =
		{
			0xCA8910,
			0xCA8938,
			0xCA8960,
		};
		for_all(uint8, index, countof(off))
		{
			auto & memoryObject = *reinterpret_cast<MEMORY_OBJECT *>(appBaseAddr + off[index]);
			ImGui::Text("__%.4u__", index);
			ImGui::Text("addr     %llX", memoryObject.addr    );
			ImGui::Text("end      %llX", memoryObject.end     );
			ImGui::Text("last     %X"  , memoryObject.last    );
			ImGui::Text("boundary %X"  , memoryObject.boundary);
			ImGui::Text("size     %X"  , memoryObject.size    );
			ImGui::Text("pipe     %u"  , memoryObject.pipe    );
			ImGui::Text("count    %u"  , memoryObject.count   );
		}

		ImGui::PopStyleColor();
		ImGui::PopFont();
	}
	ImGui::End();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar(3);
}






const char * Actor_playerNames[MAX_PLAYER] =
{
	"Player 1",
	"Player 2",
	"Player 3",
	"Player 4",
};

const char * Actor_characterNames[] =
{
	"Dante",
	"Bob",
	"Lady",
	"Vergil",
};

const char * Actor_meleeWeaponNames[] =
{
	"Rebellion",
	"Cerberus",
	"Agni & Rudra",
	"Nevan",
	"Beowulf Dante",
	"Yamato",
	"Beowulf Vergil",
	"Force Edge",
};

uint8 Actor_meleeWeapons[] =
{
	WEAPON_REBELLION,
	WEAPON_CERBERUS,
	WEAPON_AGNI_RUDRA,
	WEAPON_NEVAN,
	WEAPON_BEOWULF_DANTE,
	WEAPON_YAMATO_VERGIL,
	WEAPON_BEOWULF_VERGIL,
	WEAPON_FORCE_EDGE,
};

uint8 Actor_meleeWeaponIndices[MAX_PLAYER][MAX_ENTITY][MAX_MELEE_WEAPON] = {};

const char * Actor_rangedWeaponNames[] =
{
	"Ebony & Ivory",
	"Shotgun",
	"Artemis",
	"Spiral",
	"Kalina Ann",
};

uint8 Actor_rangedWeapons[] =
{
	WEAPON_EBONY_IVORY,
	WEAPON_SHOTGUN,
	WEAPON_ARTEMIS,
	WEAPON_SPIRAL,
	WEAPON_KALINA_ANN,
};

uint8 Actor_rangedWeaponIndices[MAX_PLAYER][MAX_ENTITY][MAX_RANGED_WEAPON] = {};

void Actor_UpdateWeaponIndices
(
	uint8 player,
	uint8 entity
)
{
	auto & playerData = activeConfig.Actor.playerData[player][entity];

	for_all(uint8, index, MAX_MELEE_WEAPON)
	{
		UpdateMapIndex
		(
			Actor_meleeWeapons,
			Actor_meleeWeaponIndices[player][entity][index],
			playerData.meleeWeapons[index]
		);
	}

	if (playerData.character != CHAR_DANTE)
	{
		return;
	}

	for_all(uint8, index, MAX_RANGED_WEAPON)
	{
		UpdateMapIndex
		(
			Actor_rangedWeapons,
			Actor_rangedWeaponIndices[player][entity][index],
			playerData.rangedWeapons[index]
		);
	}
}

void Actor_UpdateWeaponIndices()
{
	for_all(uint8, player, MAX_PLAYER){
	for_all(uint8, entity, MAX_ENTITY)
	{
		Actor_UpdateWeaponIndices(player, entity);
	}}
}

void Actor_PlayerTab
(
	uint8 player,
	uint8 entity
)
{
	auto & playerData = activeConfig.Actor.playerData[player][entity];

	for_all(uint8, character, MAX_CHAR)
	{
		if (GUI_Button(Actor_characterNames[character]))
		{
			ApplyPlayerData(playerData, character);
			Actor_UpdateWeaponIndices(player, entity);
		}
		ImGui::SameLine();
	}
	ImGui::Text("Template");
	ImGui::Text("");

	ImGui::PushItemWidth(150);
	GUI_Combo("Character", Actor_characterNames, playerData.character);
	ImGui::PopItemWidth();

	if
	(
		(playerData.character == CHAR_BOB ) ||
		(playerData.character == CHAR_LADY)
	)
	{
		return;
	}

	ImGui::PushItemWidth(150);
	GUI_Input("Costume", playerData.costume);
	GUI_Checkbox("Force Files", playerData.forceFiles);

	bool condition = !playerData.forceFiles;
	GUI_PushDisable(condition);
	GUI_Combo("Character", Actor_characterNames, playerData.forceFilesCharacter);
	GUI_PopDisable(condition);

	ImGui::PopItemWidth();
	ImGui::Text("");

	ImGui::Text("Melee Weapons");
	ImGui::PushItemWidth(200);

	GUI_Slider<uint8>("", playerData.meleeWeaponCount, 1, MAX_MELEE_WEAPON);

	for_all(uint8, index, MAX_MELEE_WEAPON)
	{
		bool condition = (index >= playerData.meleeWeaponCount);
		GUI_PushDisable(condition);
		GUI_ComboMap
		(
			"",
			Actor_meleeWeaponNames,
			Actor_meleeWeapons,
			Actor_meleeWeaponIndices[player][entity][index],
			playerData.meleeWeapons[index]
		);
		if constexpr (debug)
		{
			ImGui::Text("value %u", playerData.meleeWeapons[index]);
			ImGui::Text("index %u", Actor_meleeWeaponIndices[player][entity][index]);
		}
		GUI_PopDisable(condition);
	}
	ImGui::PopItemWidth();

	if (playerData.character != CHAR_DANTE)
	{
		return;
	}
	ImGui::Text("");

	ImGui::Text("Ranged Weapons");
	ImGui::PushItemWidth(200);

	GUI_Slider<uint8>("", playerData.rangedWeaponCount, 1, MAX_RANGED_WEAPON);

	for_all(uint8, index, MAX_RANGED_WEAPON)
	{
		bool condition = (index >= playerData.rangedWeaponCount);
		GUI_PushDisable(condition);
		GUI_ComboMap
		(
			"",
			Actor_rangedWeaponNames,
			Actor_rangedWeapons,
			Actor_rangedWeaponIndices[player][entity][index],
			playerData.rangedWeapons[index]
		);
		if constexpr (debug)
		{
			ImGui::Text("value %u", playerData.rangedWeapons[index]);
			ImGui::Text("index %u", Actor_rangedWeaponIndices[player][entity][index]);
		}
		GUI_PopDisable(condition);
	}
	ImGui::PopItemWidth();
}

void Actor()
{
	if (ImGui::CollapsingHeader("Actor"))
	{
		ImGui::Text("");

		if (GUI_Checkbox("Enable", queuedConfig.Actor.enable))
		{
			if
			(
				(g_scene == SCENE_MAIN          ) ||
				(g_scene == SCENE_MISSION_SELECT)
			)
			{
				activeConfig.Actor.enable = queuedConfig.Actor.enable;
				Actor_Toggle(activeConfig.Actor.enable);
			}
		}
		ImGui::Text("");

		if (GUI_Button("Reset"))
		{
			memcpy(&activeConfig.Actor, &defaultConfig.Actor, sizeof(Config::Actor));
			memcpy(&queuedConfig.Actor, &defaultConfig.Actor, sizeof(Config::Actor));
			Actor_UpdateWeaponIndices();
		}
		ImGui::Text("");

		ImGui::PushItemWidth(200);
		GUI_Slider<uint8>("Player Count", activeConfig.Actor.playerCount, 1, MAX_PLAYER);
		ImGui::PopItemWidth();
		ImGui::Text("");

		if (ImGui::BeginTabBar("PlayerTabs"))
		{
			for_all(uint8, player, MAX_PLAYER)
			{
				auto condition = (player >= activeConfig.Actor.playerCount);

				GUI_PushDisable(condition);

				if (ImGui::BeginTabItem(Actor_playerNames[player]))
				{
					ImGui::Text("");

					GUI_SectionStart("Main");
					Actor_PlayerTab(player, ENTITY_MAIN);
					GUI_SectionEnd();
					ImGui::Text("");

					GUI_SectionStart("Clone");
					Actor_PlayerTab(player, ENTITY_CLONE);

					ImGui::EndTabItem();
				}

				GUI_PopDisable(condition);
			}

			ImGui::EndTabBar();
		}

		ImGui::Text("");
	}
}















const char * Arcade_missionNames[] =
{
	"Movie",
	"Mission 1",
	"Mission 2",
	"Mission 3",
	"Mission 4",
	"Mission 5",
	"Mission 6",
	"Mission 7",
	"Mission 8",
	"Mission 9",
	"Mission 10",
	"Mission 11",
	"Mission 12",
	"Mission 13",
	"Mission 14",
	"Mission 15",
	"Mission 16",
	"Mission 17",
	"Mission 18",
	"Mission 19",
	"Mission 20",
	"Bloody Palace",
};

const char * Arcade_modeNames[] =
{
	"Easy",
	"Normal",
	"Hard",
	"Very Hard",
	"Dante Must Die",
	"Heaven or Hell",
};

uint32 Arcade_modeMap[] =
{
	MODE_EASY,
	MODE_NORMAL,
	MODE_HARD,
	MODE_VERY_HARD,
	MODE_DANTE_MUST_DIE,
	MODE_HARD,
};

uint8 Arcade_modeIndex = 0;

const char * Arcade_floorNames[] =
{
	"Floor 1",
	"Floor 2",
	"Floor 3",
	"Floor 4",
	"Floor 5",
	"Floor 6",
	"Floor 7",
	"Floor 8",
	"Floor 9",
	"Floor 10",
	"Cerberus",
	"Gigapede",
	"Agni & Rudra",
	"Nevan",
	"Beowulf",
	"Geryon",
	"Doppelganger",
	"Leviathan",
	"Damned Chessmen",
	"Vergil 1",
	"Vergil 2",
	"Vergil 3",
	"Lady",
	"Arkham",
	"Jester 1",
	"Jester 2",
	"Jester 3",
};

const char * Arcade_characterNames[] =
{
	"Dante",
	"Bob",
	"Lady",
	"Vergil",
};

const char * Arcade_styleNames[] =
{
	"Swordmaster",
	"Gunslinger",
	"Trickster",
	"Royalguard",
	"Quicksilver",
	"Doppelganger",
};

const char * Arcade_meleeWeaponNames[] =
{
	"Rebellion",
	"Cerberus",
	"Agni & Rudra",
	"Nevan",
	"Beowulf",
};

uint8 Arcade_meleeWeaponMap[] =
{
	WEAPON_REBELLION,
	WEAPON_CERBERUS,
	WEAPON_AGNI_RUDRA,
	WEAPON_NEVAN,
	WEAPON_BEOWULF_DANTE,
};

uint8 Arcade_meleeWeaponIndex[2] = {};

const char * Arcade_rangedWeaponNames[] =
{
	"Ebony & Ivory",
	"Shotgun",
	"Artemis",
	"Spiral",
	"Kalina Ann",
};

uint8 Arcade_rangedWeaponMap[] =
{
	WEAPON_EBONY_IVORY,
	WEAPON_SHOTGUN,
	WEAPON_ARTEMIS,
	WEAPON_SPIRAL,
	WEAPON_KALINA_ANN,
};

uint8 Arcade_rangedWeaponIndex[2] = {};

void Arcade_Init()
{
	UpdateMapIndex(Arcade_modeMap, Arcade_modeIndex, activeConfig.Arcade.mode);
	UpdateMapIndex(Arcade_meleeWeaponMap , Arcade_meleeWeaponIndex [0], activeConfig.Arcade.meleeWeapons[0] );
	UpdateMapIndex(Arcade_meleeWeaponMap , Arcade_meleeWeaponIndex [1], activeConfig.Arcade.meleeWeapons[1] );
	UpdateMapIndex(Arcade_rangedWeaponMap, Arcade_rangedWeaponIndex[0], activeConfig.Arcade.rangedWeapons[0]);
	UpdateMapIndex(Arcade_rangedWeaponMap, Arcade_rangedWeaponIndex[1], activeConfig.Arcade.rangedWeapons[1]);
}

void Arcade()
{
	if (ImGui::CollapsingHeader("Arcade"))
	{
		ImGui::Text("");
		GUI_Checkbox("Enable", activeConfig.Arcade.enable);
		ImGui::Text("");
		GUI_Button("Reset");
		ImGui::Text("");

		ImGui::PushItemWidth(200);

		GUI_Combo("Mission", Arcade_missionNames, activeConfig.Arcade.mission, ImGuiComboFlags_HeightLargest);

		if ((activeConfig.Arcade.mission >= 1) && (activeConfig.Arcade.mission <= 20))
		{
			GUI_ComboMap("Mode", Arcade_modeNames, Arcade_modeMap, Arcade_modeIndex, activeConfig.Arcade.mode);
			if constexpr (debug)
			{
				ImGui::Text("value %u", activeConfig.Arcade.mode);
				ImGui::Text("index %u", Arcade_modeIndex);
			}
			GUI_InputDefault("Room", activeConfig.Arcade.room, defaultConfig.Arcade.room);
			ImGui::SameLine();
			GUI_Checkbox("Ignore", activeConfig.Arcade.ignoreRoom);
			GUI_InputDefault("Position", activeConfig.Arcade.position, defaultConfig.Arcade.position);
			ImGui::SameLine();
			GUI_Checkbox("Ignore", activeConfig.Arcade.ignorePosition);
		}

		if (activeConfig.Arcade.mission == 21)
		{
			GUI_Combo("Floor", Arcade_floorNames, activeConfig.Arcade.floor, ImGuiComboFlags_HeightLargest);
		}

		if (activeConfig.Arcade.mission > 0)
		{
			GUI_InputDefault<float32>("Hit Points"  , activeConfig.Arcade.hitPoints  , defaultConfig.Arcade.hitPoints  , 1000, "%.0f");
			GUI_InputDefault<float32>("Magic Points", activeConfig.Arcade.magicPoints, defaultConfig.Arcade.magicPoints, 1000, "%.0f");
		}

		GUI_Combo("Character", Arcade_characterNames, activeConfig.Arcade.character);
		GUI_InputDefault("Costume", activeConfig.Arcade.costume, defaultConfig.Arcade.costume);

		if ((activeConfig.Arcade.mission > 0) && (activeConfig.Arcade.character == CHAR_DANTE))
		{
			GUI_Combo("Style", Arcade_styleNames, activeConfig.Arcade.style);
			GUI_ComboMap("Melee Weapon 1" , Arcade_meleeWeaponNames , Arcade_meleeWeaponMap , Arcade_meleeWeaponIndex [0], activeConfig.Arcade.meleeWeapons [0]);
			GUI_ComboMap("Melee Weapon 2" , Arcade_meleeWeaponNames , Arcade_meleeWeaponMap , Arcade_meleeWeaponIndex [1], activeConfig.Arcade.meleeWeapons [1]);
			GUI_ComboMap("Ranged Weapon 1", Arcade_rangedWeaponNames, Arcade_rangedWeaponMap, Arcade_rangedWeaponIndex[0], activeConfig.Arcade.rangedWeapons[0]);
			GUI_ComboMap("Ranged Weapon 2", Arcade_rangedWeaponNames, Arcade_rangedWeaponMap, Arcade_rangedWeaponIndex[1], activeConfig.Arcade.rangedWeapons[1]);
		}

		ImGui::Text("");

		ImGui::PopItemWidth();
	}
}

void BossRush()
{
	if (ImGui::CollapsingHeader("Boss Rush"))
	{
		ImGui::Text("");
		GUI_Checkbox("Enable", activeConfig.BossRush.enable);
		ImGui::Text("");
		GUI_Button("Reset");
		GUI_SectionEnd();

		GUI_SectionStart("Mission 5");
		GUI_Checkbox("Skip Jester", activeConfig.BossRush.Mission5.skipJester);
		GUI_SectionEnd();

		GUI_SectionStart("Mission 12");
		GUI_Checkbox("Skip Jester", activeConfig.BossRush.Mission12.skipJester);
		GUI_Checkbox("Skip Geryon Part 1", activeConfig.BossRush.Mission12.skipGeryonPart1);
		GUI_SectionEnd();

		GUI_SectionStart("Mission 17");
		GUI_Checkbox("Skip Jester", activeConfig.BossRush.Mission17.skipJester);
		GUI_SectionEnd();

		GUI_SectionStart("Mission 19");
		GUI_Checkbox("Skip Arkham Part 1", activeConfig.BossRush.Mission19.skipArkhamPart1);
		ImGui::Text("");
	}
}

void Camera()
{
	if (ImGui::CollapsingHeader("Camera"))
	{
		ImGui::Text("");
		GUI_Checkbox("Invert X", activeConfig.Camera.invertX);
		ImGui::Text("");
	}
}





struct
{
	float32 airHike[5][4] =
	{
		{ 128,   0,   0, 200 },
		{  96, 128, 144, 200 },
		{ 160,  64,  16, 200 },
		{ 112,  64, 160, 200 },
		{ 128, 128, 128, 200 },
	};
	struct
	{
		float32 skyStar[4] = { 255, 0, 0, 200 };
	}
	Trickster;
	struct
	{
		float32 ultimate[4] = { 143, 112, 48, 200 };
	}
	Royalguard;
	struct
	{
		float32 clone[4] = { 16, 16, 16, 48 };
	}
	Doppelganger;
	struct
	{
		float32 dante[5][4] =
		{
			{ 128,   0,   0, 200 },
			{  96, 128, 144, 200 },
			{ 160,  64,  16, 200 },
			{ 112,  64, 160, 200 },
			{ 128, 128, 128, 200 },
		};
		float32 sparda[4] = { 128, 0, 0, 200 };
		float32 vergil[3][4] =
		{
			{ 32, 64, 128, 200 },
			{ 32, 64, 128, 200 },
			{ 32, 64, 128, 200 },
		};
		float32 neroAngelo[4] = { 64, 0, 255, 200 };
	}
	Aura;
}
Color;

void Cosmetics_Init()
{
	constexpr uint8 itemCount = (sizeof(Color) / 4);

	auto items = reinterpret_cast<uint8 *>(activeConfig.Color.airHike);
	auto items2 = reinterpret_cast<float32 *>(Color.airHike);

	for_all(uint8, index, itemCount)
	{
		items2[index] = (static_cast<float32>(items[index]) / 255);
	}
}

void Cosmetics()
{
	if (ImGui::CollapsingHeader("Cosmetics"))
	{
		ImGui::Text("");
		GUI_Button("Reset");
		GUI_SectionEnd();

		GUI_SectionStart("Color");


		//ImGui::Text("airHike[0][0] %u", activeConfig.Color.airHike[0][0]);
		//ImGui::Text("airHike[0][1] %u", activeConfig.Color.airHike[0][1]);
		//ImGui::Text("airHike[0][2] %u", activeConfig.Color.airHike[0][2]);
		//ImGui::Text("airHike[0][3] %u", activeConfig.Color.airHike[0][3]);


		GUI_ColorPalette("Air Hike", activeConfig.Color.airHike, Color.airHike);






		ImGui::Text("");
		ImGui::Text("Trickster");
		GUI_Color("Sky Star", activeConfig.Color.Trickster.skyStar, Color.Trickster.skyStar);
		ImGui::Text("");
		ImGui::Text("Royalguard");
		GUI_Color("Ultimate", activeConfig.Color.Royalguard.ultimate, Color.Royalguard.ultimate);
		ImGui::Text("");
		ImGui::Text("Doppelganger");
		GUI_Color("Clone", activeConfig.Color.Doppelganger.clone, Color.Doppelganger.clone);
		ImGui::Text("");
		ImGui::Text("Aura");
		GUI_ColorPalette("Dante", activeConfig.Color.Aura.dante, Color.Aura.dante);
		GUI_Color("Sparda", activeConfig.Color.Aura.sparda, Color.Aura.sparda);
		GUI_ColorPalette("Vergil", activeConfig.Color.Aura.vergil, Color.Aura.vergil);
		GUI_Color("Nero Angelo", activeConfig.Color.Aura.neroAngelo, Color.Aura.neroAngelo);
		ImGui::Text("");
		GUI_Button("Reset");
		GUI_SectionEnd();






		GUI_SectionStart("Other");
		GUI_Checkbox("No Devil Form", activeConfig.noDevilForm);

		GUI_Checkbox("Hide Beowulf Dante", activeConfig.BeowulfDante.hide);
		GUI_Checkbox("Hide Beowulf Vergil", activeConfig.BeowulfVergil.hide);






		ImGui::Text("");
	}
}

template <typename T>
void ActionData
(
	const char * label,
	T(&vars)[2],
	T(&defaultVars)[2],
	T step = 1,
	const char * format = 0,
	ImGuiInputTextFlags flags = 0,
	float32 width = 150
)
{
	auto & style = ImGui::GetStyle();

	ImGui::PushItemWidth(width);
	GUI_InputDefault(""   , vars[0], defaultVars[0], step, format, flags);
	ImGui::SameLine(0, style.ItemInnerSpacing.x);
	GUI_InputDefault(label, vars[1], defaultVars[1], step, format, flags);
	ImGui::PopItemWidth();
}

void Dante()
{
	if (ImGui::CollapsingHeader("Dante"))
	{
		ImGui::Text("");
		if (GUI_Button("Reset"))
		{
		}
		GUI_SectionEnd();

		GUI_SectionStart("Air Hike");
		GUI_Checkbox("Core Ability", activeConfig.AirHike.coreAbility);
		ImGui::Text("");
		ActionData<uint8>("Count", activeConfig.AirHike.count, defaultConfig.AirHike.count);
		GUI_SectionEnd();

		GUI_SectionStart("Trickster");
		ActionData<uint8>("Dash Count"     , activeConfig.Trickster.dashCount    , defaultConfig.Trickster.dashCount    );
		ActionData<uint8>("Sky Star Count" , activeConfig.Trickster.skyStarCount , defaultConfig.Trickster.skyStarCount );
		ActionData<uint8>("Air Trick Count", activeConfig.Trickster.airTrickCount, defaultConfig.Trickster.airTrickCount);
		GUI_SectionEnd();

		GUI_SectionStart("Rebellion");
		GUI_Checkbox("Infinite Sword Pierce", activeConfig.Rebellion.infiniteSwordPierce);
		ImGui::Text("");
		ActionData<float32>("Stinger Duration"    , activeConfig.Rebellion.stingerDuration   , defaultConfig.Rebellion.stingerDuration   , 1 , "%.0f");
		ActionData<float32>("Stinger Range"       , activeConfig.Rebellion.stingerRange      , defaultConfig.Rebellion.stingerRange      , 10, "%.0f");
		ActionData<float32>("Air Stinger Duration", activeConfig.Rebellion.airStingerDuration, defaultConfig.Rebellion.airStingerDuration, 1 , "%.0f");
		ActionData<float32>("Air Stinger Range"   , activeConfig.Rebellion.airStingerRange   , defaultConfig.Rebellion.airStingerRange   , 10, "%.0f");
		GUI_SectionEnd();

		//GUI_SectionStart("Cerberus");
		//ActionData<float32>("Revolver Height", activeConfig.Cerberus.revolverHeight, defaultConfig.Cerberus.revolverHeight, 0.5f, "%.1f");
		//GUI_SectionEnd();

		GUI_SectionStart("Agni & Rudra");
		ActionData<float32>("Jet-Stream Duration", activeConfig.AgniRudra.jetStreamDuration, defaultConfig.AgniRudra.jetStreamDuration, 1 , "%.0f");
		ActionData<float32>("Jet-Stream Range"   , activeConfig.AgniRudra.jetStreamRange   , defaultConfig.AgniRudra.jetStreamRange   , 10, "%.0f");
		GUI_SectionEnd();

		GUI_SectionStart("Nevan");
		ActionData<float32>("Reverb Shock Duration", activeConfig.Nevan.reverbShockDuration, defaultConfig.Nevan.reverbShockDuration, 1 , "%.0f");
		ActionData<float32>("Reverb Shock Range"   , activeConfig.Nevan.reverbShockRange   , defaultConfig.Nevan.reverbShockRange   , 10, "%.0f");
		GUI_SectionEnd();

		GUI_SectionStart("Beowulf");
		//GUI_Checkbox("Hide", activeConfig.Beowulf.hide);
		//ImGui::Text("");
		ActionData<float32>("Straight Duration"    , activeConfig.BeowulfDante.straightDuration   , defaultConfig.BeowulfDante.straightDuration   , 1 , "%.0f");
		ActionData<float32>("Straight Range"       , activeConfig.BeowulfDante.straightRange      , defaultConfig.BeowulfDante.straightRange      , 10, "%.0f");
		ActionData<float32>("Air Straight Duration", activeConfig.BeowulfDante.airStraightDuration, defaultConfig.BeowulfDante.airStraightDuration, 1 , "%.0f");
		ActionData<float32>("Air Straight Range"   , activeConfig.BeowulfDante.airStraightRange   , defaultConfig.BeowulfDante.airStraightRange   , 10, "%.0f");
		//ActionData<float32>("Rising Dragon Height" , activeConfig.BeowulfDante.risingDragonHeight , defaultConfig.BeowulfDante.risingDragonHeight , 10, "%.1f");
		GUI_SectionEnd();

		GUI_SectionStart("Ebony & Ivory");
		GUI_Checkbox("Foursome Time", activeConfig.EbonyIvory.foursomeTime);
		GUI_Checkbox("Infinite Rain Storm", activeConfig.EbonyIvory.infiniteRainStorm);
		GUI_SectionEnd();

		GUI_SectionStart("Shotgun");
		ActionData<float32>("Gun Stinger Duration"    , activeConfig.Shotgun.gunStingerDuration   , defaultConfig.Shotgun.gunStingerDuration   , 1 , "%.0f");
		ActionData<float32>("Gun Stinger Range"       , activeConfig.Shotgun.gunStingerRange      , defaultConfig.Shotgun.gunStingerRange      , 10, "%.0f");
		ActionData<float32>("Air Gun Stinger Duration", activeConfig.Shotgun.airGunStingerDuration, defaultConfig.Shotgun.airGunStingerDuration, 1 , "%.0f");
		ActionData<float32>("Air Gun Stinger Range"   , activeConfig.Shotgun.airGunStingerRange   , defaultConfig.Shotgun.airGunStingerRange   , 10, "%.0f");
		GUI_SectionEnd();

		GUI_SectionStart("Artemis");
		GUI_Checkbox("Swap Normal Shot and Multi Lock", activeConfig.Artemis.swapNormalShotAndMultiLock);
		GUI_Checkbox("Instant Full Charge", activeConfig.Artemis.instantFullCharge);
		GUI_SectionEnd();

		GUI_SectionStart("Summoned Swords");
		GUI_Checkbox("Enable", activeConfig.SummonedSwords.dante);
		ImGui::Text("");


		//GUI_SectionEnd();



		//ImGui::PushItemWidth(150);

		//GUI_Checkbox("Summoned Swords", activeConfig.summonedSwords);
		//ImGui::PopItemWidth();
		//ImGui::Text("");
	}
}

void Other()
{
	if (ImGui::CollapsingHeader("Other"))
	{
		ImGui::Text("");
		if (GUI_Button("Reset"))
		{
		}
		GUI_SectionEnd();
		GUI_SectionStart("Magic Points Depletion Rate");
		ImGui::PushItemWidth(150);
		GUI_InputDefault<float32>("Quicksilver" , activeConfig.MagicPointsDepletionRate.quicksilver , defaultConfig.MagicPointsDepletionRate.quicksilver , 1, "%.1f");
		GUI_InputDefault<float32>("Doppelganger", activeConfig.MagicPointsDepletionRate.doppelganger, defaultConfig.MagicPointsDepletionRate.doppelganger, 1, "%.1f");
		GUI_InputDefault<float32>("Devil"       , activeConfig.MagicPointsDepletionRate.devil       , defaultConfig.MagicPointsDepletionRate.devil       , 1, "%.1f");
		ImGui::PopItemWidth();
		GUI_SectionEnd();
		ImGui::PushItemWidth(150);
		GUI_InputDefault<uint8  >("Crazy Combo Level Multiplier", activeConfig.crazyComboLevelMultiplier, defaultConfig.crazyComboLevelMultiplier             );
		GUI_InputDefault<float32>("Orb Reach"                   , activeConfig.orbReach                 , defaultConfig.orbReach                 , 100, "%.0f");
		GUI_InputDefault<float32>("Weapon Switch Timeout"       , activeConfig.weaponSwitchTimeout      , defaultConfig.weaponSwitchTimeout      , 1  , "%.0f");
		ImGui::PopItemWidth();
		ImGui::Text("");
	}
}

void Repair()
{
	if (ImGui::CollapsingHeader("Repair"))
	{
		ImGui::Text("");
		GUI_Button("Reset Weapons");
		GUI_Button("Reset Ranged Weapon Levels");
		ImGui::Text("");
	}
}

const char * ResetMotionState_buttonNames[] =
{
	"GAMEPAD_LEFT_TRIGGER",
	"GAMEPAD_RIGHT_TRIGGER",
	"GAMEPAD_LEFT_SHOULDER",
	"GAMEPAD_RIGHT_SHOULDER",
	"GAMEPAD_Y",
	"GAMEPAD_B",
	"GAMEPAD_A",
	"GAMEPAD_X",
	"GAMEPAD_BACK",
	"GAMEPAD_LEFT_THUMB",
	"GAMEPAD_RIGHT_THUMB",
	"GAMEPAD_START",
	"GAMEPAD_UP",
	"GAMEPAD_RIGHT",
	"GAMEPAD_DOWN",
	"GAMEPAD_LEFT",
};

byte16 ResetMotionState_buttonMap[] =
{
	GAMEPAD_LEFT_TRIGGER,
	GAMEPAD_RIGHT_TRIGGER,
	GAMEPAD_LEFT_SHOULDER,
	GAMEPAD_RIGHT_SHOULDER,
	GAMEPAD_Y,
	GAMEPAD_B,
	GAMEPAD_A,
	GAMEPAD_X,
	GAMEPAD_BACK,
	GAMEPAD_LEFT_THUMB,
	GAMEPAD_RIGHT_THUMB,
	GAMEPAD_START,
	GAMEPAD_UP,
	GAMEPAD_RIGHT,
	GAMEPAD_DOWN,
	GAMEPAD_LEFT,
};

uint8 ResetMotionState_buttonIndex = 0;

void ResetMotionState_Init()
{
	UpdateMapIndex(ResetMotionState_buttonMap, ResetMotionState_buttonIndex, activeConfig.ResetMotionState.button);
}

void ResetMotionState()
{
	if (ImGui::CollapsingHeader("Reset Motion State"))
	{
		ImGui::Text("");
		GUI_Checkbox("Enable", activeConfig.ResetMotionState.enable);
		ImGui::Text("");
		GUI_Button("Reset");
		ImGui::Text("");
		ImGui::PushItemWidth(200);
		GUI_ComboMap("Button", ResetMotionState_buttonNames, ResetMotionState_buttonMap, ResetMotionState_buttonIndex, activeConfig.ResetMotionState.button, ImGuiComboFlags_HeightLargest);
		ImGui::PopItemWidth();
		ImGui::Text("");
	}
}

void Speed()
{
	if (ImGui::CollapsingHeader("Speed"))
	{
		ImGui::Text("");

		GUI_Checkbox("Enable", activeConfig.Speed.enable);
		ImGui::Text("");
		GUI_Button("Reset");
		GUI_SectionEnd();
		ImGui::PushItemWidth(200);
		GUI_SectionStart("Main");
		GUI_InputDefault("Base" , activeConfig.Speed.Main.base , defaultConfig.Speed.Main.base , 0.1f, "%.2f");
		GUI_InputDefault("Turbo", activeConfig.Speed.Main.turbo, defaultConfig.Speed.Main.turbo, 0.1f, "%.2f");
		GUI_InputDefault("Actor", activeConfig.Speed.Main.actor, defaultConfig.Speed.Main.actor, 0.1f, "%.2f");
		GUI_InputDefault("Enemy", activeConfig.Speed.Main.enemy, defaultConfig.Speed.Main.enemy, 0.1f, "%.2f");
		GUI_SectionEnd();
		GUI_SectionStart("Quicksilver");
		GUI_InputDefault("Actor", activeConfig.Speed.Quicksilver.actor, defaultConfig.Speed.Quicksilver.actor, 0.1f, "%.2f");
		GUI_InputDefault("Enemy", activeConfig.Speed.Quicksilver.enemy, defaultConfig.Speed.Quicksilver.enemy, 0.1f, "%.2f");
		GUI_SectionEnd();
		GUI_SectionStart("Devil");
		ImGui::Text("Dante");
		GUI_InputDefault("Rebellion"   , activeConfig.Speed.Devil.dante[0], defaultConfig.Speed.Devil.dante[0], 0.1f, "%.2f");
		GUI_InputDefault("Cerberus"    , activeConfig.Speed.Devil.dante[1], defaultConfig.Speed.Devil.dante[1], 0.1f, "%.2f");
		GUI_InputDefault("Agni & Rudra", activeConfig.Speed.Devil.dante[2], defaultConfig.Speed.Devil.dante[2], 0.1f, "%.2f");
		GUI_InputDefault("Nevan"       , activeConfig.Speed.Devil.dante[3], defaultConfig.Speed.Devil.dante[3], 0.1f, "%.2f");
		GUI_InputDefault("Beowulf"     , activeConfig.Speed.Devil.dante[4], defaultConfig.Speed.Devil.dante[4], 0.1f, "%.2f");
		GUI_InputDefault("Sparda"      , activeConfig.Speed.Devil.dante[5], defaultConfig.Speed.Devil.dante[5], 0.1f, "%.2f");
		ImGui::Text("");
		ImGui::Text("Vergil");
		GUI_InputDefault("Yamato"    , activeConfig.Speed.Devil.vergil[0], defaultConfig.Speed.Devil.vergil[0], 0.1f, "%.2f");
		GUI_InputDefault("Beowulf"   , activeConfig.Speed.Devil.vergil[1], defaultConfig.Speed.Devil.vergil[1], 0.1f, "%.2f");
		GUI_InputDefault("Force Edge", activeConfig.Speed.Devil.vergil[2], defaultConfig.Speed.Devil.vergil[2], 0.1f, "%.2f");
		ImGui::Text("");
		ImGui::Text("Nero Angelo");
		GUI_InputDefault("Yamato"    , activeConfig.Speed.Devil.neroAngelo[0], defaultConfig.Speed.Devil.neroAngelo[0], 0.1f, "%.2f");
		GUI_InputDefault("Beowulf"   , activeConfig.Speed.Devil.neroAngelo[1], defaultConfig.Speed.Devil.neroAngelo[1], 0.1f, "%.2f");
		GUI_InputDefault("Force Edge", activeConfig.Speed.Devil.neroAngelo[2], defaultConfig.Speed.Devil.neroAngelo[2], 0.1f, "%.2f");
		ImGui::PopItemWidth();

		ImGui::Text("");
	}
}

void StyleSwitchController()
{
	if (ImGui::CollapsingHeader("Style Switch Controller"))
	{
		ImGui::Text("");

		GUI_Checkbox("No Double Tap", activeConfig.StyleSwitchController.noDoubleTap);

		ImGui::Text("");
	}
}

const char * Graphics_vSyncNames[] =
{
	"Auto",
	"Force Off",
	"Force On",
};

void System()
{
	if (ImGui::CollapsingHeader("System"))
	{
		ImGui::Text("");
		GUI_SectionStart("Event");
		GUI_Checkbox("Skip Intro"    , activeConfig.Event.skipIntro    );
		if (GUI_Checkbox("Skip Cutscenes", activeConfig.Event.skipCutscenes))
		{
			Event_ToggleSkipCutscenes(activeConfig.Event.skipCutscenes);
		}
		GUI_SectionEnd();

		GUI_SectionStart("File");
		GUI_Checkbox("Prefer Local Files", activeConfig.File.preferLocalFiles);
		GUI_SectionEnd();

		GUI_SectionStart("Graphics");
		ImGui::PushItemWidth(150);
		GUI_InputDefault("Frame Rate", activeConfig.Graphics.frameRate, defaultConfig.Graphics.frameRate);
		GUI_Combo("V-Sync", Graphics_vSyncNames, activeConfig.Graphics.vSync);
		ImGui::PopItemWidth();
		GUI_SectionEnd();

		GUI_SectionStart("Input");
		GUI_Checkbox("Hide Mouse Cursor", activeConfig.Input.hideMouseCursor);
		GUI_SectionEnd();

		GUI_SectionStart("Window");
		GUI_Checkbox("Force Focus", activeConfig.Window.forceFocus);
		ImGui::Text("");
	}
}

void Teleporter()
{
	if (ImGui::CollapsingHeader("Teleporter"))
	{
		auto Draw = []()
		{
			if (!InGame())
			{
				return false;
			}
			IntroduceEventData(return false);
			IntroduceNextEventData(return false);
			float32 width = 150;

			ImGui::PushItemWidth(width);
			ImGui::Text("Current");
			GUI_Input<uint32>("", eventData.room    , 0, "%u", ImGuiInputTextFlags_ReadOnly);
			GUI_Input<uint32>("", eventData.position, 0, "%u", ImGuiInputTextFlags_ReadOnly);
			ImGui::Text("Next");
			GUI_Input<uint16>("", nextEventData.room    , 1, "%u", 0);
			GUI_Input<uint16>("", nextEventData.position, 1, "%u", 0);
			if (GUI_Button("Teleport", ImVec2(width, ImGui::GetFrameHeight())))
			{
				eventData.event = EVENT_TELEPORT;

				//Actor_Teleport();
			}
			ImGui::PopItemWidth();

			return true;
		};

		ImGui::Text("");
		if (!Draw())
		{
			ImGui::Text("Invalid Pointer");
		}
		ImGui::Text("");
	}
}

void Training()
{
	if (ImGui::CollapsingHeader("Training"))
	{
		//ImGui::Text("");
		//GUI_Checkbox("Enable", activeConfig.Training.enable);
		//ImGui::Text("");
		//GUI_Button("Reset");
		ImGui::Text("");
		if (GUI_Checkbox("Infinite Hit Points", activeConfig.Training.infiniteHitPoints))
		{
			Training_ToggleInfiniteHitPoints(activeConfig.Training.infiniteHitPoints);
		}
		if (GUI_Checkbox("Infinite Magic Points", activeConfig.Training.infiniteMagicPoints))
		{
		}
		if (GUI_Checkbox("Disable Timer", activeConfig.Training.disableTimer))
		{
		}
		ImGui::Text("");
	}
}

void Vergil()
{
	if (ImGui::CollapsingHeader("Vergil"))
	{
		ImGui::Text("");
		//GUI_Checkbox("Enable", activeConfig.enable);
		//ImGui::Text("");
		//GUI_Button("Reset");
		//GUI_SectionEnd();

		GUI_SectionStart("Dark Slayer");
		ActionData<uint8>("Air Trick Count" , activeConfig.DarkSlayer.airTrickCount , defaultConfig.DarkSlayer.airTrickCount );
		ActionData<uint8>("Trick Up Count"  , activeConfig.DarkSlayer.trickUpCount  , defaultConfig.DarkSlayer.trickUpCount  );
		ActionData<uint8>("Trick Down Count", activeConfig.DarkSlayer.trickDownCount, defaultConfig.DarkSlayer.trickDownCount);
		GUI_SectionEnd();

		GUI_SectionStart("Yamato");
		ActionData<float32>("Rapid Slash Duration", activeConfig.Yamato.rapidSlashDuration, defaultConfig.Yamato.rapidSlashDuration, 1 , "%.0f");
		ActionData<float32>("Rapid Slash Range"   , activeConfig.Yamato.rapidSlashRange   , defaultConfig.Yamato.rapidSlashRange   , 10, "%.0f");
		ActionData<float32>("Judgement Cut Count" , activeConfig.Yamato.judgementCutCount , defaultConfig.Yamato.judgementCutCount , 1 , "%.0f");
		ActionData<float32>("Judgement Cut Range" , activeConfig.Yamato.judgementCutRange , defaultConfig.Yamato.judgementCutRange , 10, "%.0f");
		GUI_SectionEnd();

		//GUI_SectionStart("Beowulf");
		////GUI_Checkbox("Hide", activeConfig.Beowulf.hide);
		////ImGui::Text("");
		//ActionData<float32>("Rising Sun Height", activeConfig.Beowulf.risingSunHeight, defaultConfig.Beowulf.risingSunHeight, 1 , "%.0f");
		//GUI_SectionEnd();

		GUI_SectionStart("Force Edge");
		GUI_Checkbox("Infinite Round Trip", activeConfig.ForceEdge.infiniteRoundTrip);
		ImGui::Text("");
		ActionData<float32>("Stinger Duration"    , activeConfig.ForceEdge.stingerDuration   , defaultConfig.ForceEdge.stingerDuration   , 1 , "%.0f");
		ActionData<float32>("Stinger Range"       , activeConfig.ForceEdge.stingerRange      , defaultConfig.ForceEdge.stingerRange      , 10, "%.0f");
		ActionData<float32>("Air Stinger Duration", activeConfig.ForceEdge.airStingerDuration, defaultConfig.ForceEdge.airStingerDuration, 1 , "%.0f");
		ActionData<float32>("Air Stinger Range"   , activeConfig.ForceEdge.airStingerRange   , defaultConfig.ForceEdge.airStingerRange   , 10, "%.0f");
		GUI_SectionEnd();

		GUI_SectionStart("Summoned Swords");
		GUI_Checkbox("Chrono Swords", activeConfig.SummonedSwords.chronoSwords);
		ImGui::Text("");
	}
}

bool Main_run = false;

void Main()
{
	if (!Main_run)
	{
		Main_run = true;
		ImGui::SetNextWindowSize(ImVec2(600, 650));
		ImGui::SetNextWindowPos(ImVec2(650, 50));

		//ImGuiIO & io = ImGui::GetIO();
		//io.FontDefault = io.Fonts->Fonts[FONT_MAIN];
		//ImGui::PushFont(io.Fonts->Fonts[FONT_OVERLAY_8 + activeConfig.Tools.Overlay.fontSizeIndex]);

		//ImGui::SetCurrentFont(io.Fonts->Fonts[FONT_OVERLAY_8]);
	}

	if (ImGui::Begin("DDMK 2.7", &pause))
	{
		ImGui::Text("");





		//static uint8 actor = 0;
		//static uint8 devil = 0;
		//static uint8 devilModelIndex = 0;
		//GUI_Input("Actor"            , actor          );
		//GUI_Input("Devil"            , devil          );
		//GUI_Input("Devil Model Index", devilModelIndex);
		////if (GUI_Button("Update Devil"))
		////{
		////	auto & actorData = *reinterpret_cast<ActorDataDante *>(Actor_actorBaseAddr[actor]);



		////	//ResetModel(actorData.modelData   [(devilModelIndex == 0) ? 1 : 2]);
		////	//ResetModel(actorData.submodelData[(devilModelIndex == 0) ? 1 : 3]);
		////	//ResetModel(actorData.submodelData[(devilModelIndex == 0) ? 2 : 4]);




		////	UpdateDevilModelFunctionDante(actorData, devil, devilModelIndex);
		////}




		////if (GUI_Button("Vector"))
		////{
		////	for_all(uint32, index, devilAuras.count)
		////	{
		////		Log("devilAura[%u] %llX", index, devilAuras[index]);
		////	}
		////}




		//
		//static uint8 index = 0;
		//GUI_Input("Actor", actor);
		//GUI_Input("Index", index);
		//if (GUI_Button("Flux"))
		//{
		//	func_1F94D0(Actor_actorBaseAddr[actor], index);
		//}



		////if (GUI_Button("Pop Dante"))
		////{
		////	ResetModel(Actor_actorBaseAddr[0] + 0xB8C0);
		////	UpdateModelDante(Actor_actorBaseAddr[0]);
		////}


		//if (GUI_Button("SpawnActors"))
		//{
		//	SpawnActors();
		//	//HoboBreak();
		//}





		ImGui::Text("");
		auto & sessionData = *reinterpret_cast<SESSION_DATA *>(appBaseAddr + 0xC8F250);
		GUI_Checkbox("One Hit Kill", sessionData.oneHitKill);
		ImGui::Text("");



		//auto PlayTrack = [](const char * filename)
		//{
		//	func_32BE20((appBaseAddr + 0xCF3700));
		//	func_32BA90((appBaseAddr + 0xCF3708), filename, 0, 0);
		//};


		//ImGui::Text("");
		//static char buffer[256] = {};
		//ImGui::InputText("Filename", buffer, sizeof(buffer));

		//if (GUI_Button("Play Track"))
		//{
		//	PlayTrack(buffer);
		//}



		//ImGui::Text("");








		Actor();
		Arcade();
		BossRush();
		Camera();
		Cosmetics();
		Dante();
		Other();
		Repair();
		ResetMotionState();
		Speed();
		StyleSwitchController();
		System();
		Teleporter();
		Training();
		Vergil();
	}
	ImGui::End();
}

export void GUI_Render()
{
	GUI_id = 0;

	Overlay();

	if (pause)
	{
		Main();
	}

	if (GUI_save)
	{
		GUI_save = false;

		Log("SaveConfig");
		SaveConfig();
	}
}

export void GUI_Init()
{
	BuildFonts();
	Actor_UpdateWeaponIndices();
	Arcade_Init();
	Cosmetics_Init();
	ResetMotionState_Init();
}

#ifdef __GARBAGE__



void Actor_WeaponSelectFunction
(
	const char * label,
	uint8(&configMap)[configMapItemCount],
	uint8 & weaponCount,
	const char *(&selectNames)[selectMapItemCount],
	uint8(&selectMap)[selectMapItemCount],
	uint8(&selectIndex)[configMapItemCount]
)
{

}































//const char * Actor_rangedWeaponNamesDante[] =
//{
//	"Ebony & Ivory",
//	"Shotgun",
//	"Artemis",
//	"Spiral",
//	"Kalina Ann",
//};
//
//uint8 Actor_rangedWeaponMapDante[] =
//{
//	WEAPON_EBONY_IVORY,
//	WEAPON_SHOTGUN,
//	WEAPON_ARTEMIS,
//	WEAPON_SPIRAL,
//	WEAPON_KALINA_ANN,
//};
//
//uint8 Actor_rangedWeaponIndex[MAX_PLAYER][MAX_ENTITY][MAX_CHAR][MAX_RANGED_WEAPON] = {};

//template
//<
//	uint8 configMapItemCount,
//	uint8 selectMapItemCount
//>
//void Actor_WeaponSelectFunction
//(
//	const char * label,
//	uint8(&configMap)[configMapItemCount],
//	uint8 & weaponCount,
//	const char *(&selectNames)[selectMapItemCount],
//	uint8(&selectMap)[selectMapItemCount],
//	uint8(&selectIndex)[configMapItemCount]
//)
//{
//	ImGui::Text(label);
//	ImGui::Text("");
//
//	ImGui::PushItemWidth(250);
//
//	GUI_Slider<uint8>("", weaponCount, 1, configMapItemCount);
//
//	for_all(uint8, configMapIndex, configMapItemCount)
//	{
//		auto & configMapItem   = configMap  [configMapIndex];
//		auto & selectIndexItem = selectIndex[configMapIndex];
//
//		bool skip = (configMapIndex >= weaponCount) ? true : false;
//		GUI_PushDisable(skip);
//
//		GUI_ComboMap
//		(
//			"",
//			selectNames,
//			selectMap,
//			selectIndexItem,
//			configMapItem
//		);
//
//		if constexpr (debug)
//		{
//			ImGui::Text("value %u", configMapItem  );
//			ImGui::Text("index %u", selectIndexItem);
//		}
//
//		GUI_PopDisable(skip);
//	}
//
//	ImGui::PopItemWidth();
//}
//
//template <uint8 character>
//void Actor_WeaponSelect
//(
//	uint8 player,
//	uint8 entity
//)
//{
//	Actor_WeaponSelectFunction
//	(
//		"Melee Weapons",
//		(character == CHAR_DANTE) ? activeConfig.Actor.meleeWeaponsDante[player][entity] : activeConfig.Actor.meleeWeaponsVergil[player][entity],
//		(character == CHAR_DANTE) ? activeConfig.Actor.meleeWeaponCountDante[player][entity] : activeConfig.Actor.meleeWeaponCountVergil[player][entity],
//		(character == CHAR_DANTE) ? Actor_meleeWeaponNamesDante : Actor_meleeWeaponNamesVergil,
//		(character == CHAR_DANTE) ? Actor_meleeWeaponMapDante   : Actor_meleeWeaponMapVergil,
//		Actor_meleeWeaponIndex[player][entity][character]
//	);
//
//	if constexpr (character == CHAR_DANTE)
//	{
//		ImGui::Text("");
//		Actor_WeaponSelectFunction
//		(
//			"Ranged Weapons",
//			activeConfig.Actor.rangedWeaponsDante     [player][entity],
//			activeConfig.Actor.rangedWeaponCountDante[player][entity],
//			Actor_rangedWeaponNamesDante,
//			Actor_rangedWeaponMapDante,
//			Actor_rangedWeaponIndex[player][entity][character]
//		);
//	}
//}
//
//template
//<
//	uint8 configMapItemCount,
//	uint8 selectMapItemCount
//>
//void Actor_UpdateWeaponSelectIndicesFunction
//(
//	uint8(&selectMap)[selectMapItemCount],
//	uint8(&selectIndex)[configMapItemCount],
//	uint8(&configMap)[configMapItemCount]
//)
//{
//	for_all(uint8, configMapIndex, configMapItemCount)
//	{
//		auto & configMapItem   = configMap  [configMapIndex];
//		auto & selectIndexItem = selectIndex[configMapIndex];
//
//		UpdateMapIndex(selectMap, selectIndexItem, configMapItem);
//	}
//}
//
//
//// @Todo: Update.
//void Actor_UpdateWeaponSelectIndices()
//{
//	for_all(uint8, player   , MAX_PLAYER) {
//	for_all(uint8, entity   , MAX_ENTITY) {
//	for_all(uint8, character, MAX_CHAR  )
//	{
//		Actor_UpdateWeaponSelectIndicesFunction
//		(
//			(character == CHAR_DANTE) ? Actor_meleeWeaponMapDante : Actor_meleeWeaponMapVergil,
//			Actor_meleeWeaponIndex  [player][entity][character],
//			(character == CHAR_DANTE) ? activeConfig.Actor.meleeWeaponsDante[player][entity] : activeConfig.Actor.meleeWeaponsVergil[player][entity]
//		);
//
//		if (character == CHAR_DANTE)
//		{
//			Actor_UpdateWeaponSelectIndicesFunction
//			(
//				Actor_rangedWeaponMapDante,
//				Actor_rangedWeaponIndex  [player][entity][character],
//				activeConfig.Actor.rangedWeaponsDante[player][entity]
//			);
//		}
//	}}}
//}


// @Todo: Move to tab content ffs.
//void Actor_CharacterCostumeSelect
//(
//	uint8 player,
//	uint8 entity
//)
//{
//	auto & character = activeConfig.Actor.character[player][entity];
//	if (character >= MAX_CHAR)
//	{
//		character = CHAR_DANTE;
//	}
//	auto & costume = activeConfig.Actor.costume[player][entity][character];
//	ImGui::PushItemWidth(150);
//	GUI_Combo("Character", Actor_characterNames, character);
//	GUI_Input("Costume", costume);
//	GUI_Checkbox("Force Files", activeConfig.Actor.forceFiles[player][entity][character]);
//	
//
//	
//	bool condition = !activeConfig.Actor.forceFiles[player][entity][character];
//	GUI_PushDisable(condition);
//	GUI_Combo("Character", Actor_characterNames, activeConfig.Actor.forceFilesCharacter[player][entity][character]);
//	GUI_PopDisable(condition);
//
//
//
//
//	//GUI_Checkbox("Force Dante Files" , activeConfig.Actor.forceDanteFiles [player][entity][character]);
//	//GUI_Checkbox("Force Bob Files"   , activeConfig.Actor.forceBobFiles   [player][entity][character]);
//	//GUI_Checkbox("Force Lady Files"  , activeConfig.Actor.forceLadyFiles  [player][entity][character]);
//	//GUI_Checkbox("Force Vergil Files", activeConfig.Actor.forceVergilFiles[player][entity][character]);
//
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
//}



//const char * Actor_meleeWeaponNamesVergil[] =
//{
//	"Yamato",
//	"Beowulf",
//	"Force Edge",
//	"Dante Rebellion",
//	"Dante Cerberus",
//	"Dante Agni & Rudra",
//	"Dante Nevan",
//	"Dante Beowulf",
//};
//
//uint8 Actor_meleeWeaponMapDante[] =
//{
//	WEAPON_REBELLION,
//	WEAPON_CERBERUS,
//	WEAPON_AGNI_RUDRA,
//	WEAPON_NEVAN,
//	WEAPON_BEOWULF_DANTE,
//	WEAPON_YAMATO_VERGIL,
//	WEAPON_BEOWULF_VERGIL,
//	WEAPON_FORCE_EDGE,
//};
//
//uint8 Actor_meleeWeaponMapVergil[] =
//{
//	WEAPON_YAMATO_VERGIL,
//	WEAPON_BEOWULF_VERGIL,
//	WEAPON_FORCE_EDGE,
//	WEAPON_REBELLION,
//	WEAPON_CERBERUS,
//	WEAPON_AGNI_RUDRA,
//	WEAPON_NEVAN,
//	WEAPON_BEOWULF_DANTE,
//};
//
//uint8 Actor_meleeWeaponIndex[MAX_PLAYER][MAX_ENTITY][MAX_CHAR][MAX_MELEE_WEAPON] = {};




#endif

#endif
