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

const char * Actor_characterNames[] =
{
	"Dante",
	"Bob",
	"Lady",
	"Vergil",
};


// @Todo: Move to tab content ffs.
void Actor_CharacterCostumeSelect
(
	uint8 player,
	uint8 entity
)
{
	auto & character = Config.Actor.character[player][entity];
	if (character >= MAX_CHAR)
	{
		character = CHAR_DANTE;
	}
	auto & costume = Config.Actor.costume[player][entity][character];
	ImGui::PushItemWidth(150);
	GUI_Combo("Character", Actor_characterNames, character);
	GUI_Input("Costume", costume);
	GUI_Checkbox("Force Files", Config.Actor.forceFiles[player][entity][character]);
	

	
	bool condition = !Config.Actor.forceFiles[player][entity][character];
	GUI_PushDisable(condition);
	GUI_Combo("Character", Actor_characterNames, Config.Actor.forceFilesCharacter[player][entity][character]);
	GUI_PopDisable(condition);




	//GUI_Checkbox("Force Dante Files" , Config.Actor.forceDanteFiles [player][entity][character]);
	//GUI_Checkbox("Force Bob Files"   , Config.Actor.forceBobFiles   [player][entity][character]);
	//GUI_Checkbox("Force Lady Files"  , Config.Actor.forceLadyFiles  [player][entity][character]);
	//GUI_Checkbox("Force Vergil Files", Config.Actor.forceVergilFiles[player][entity][character]);










	ImGui::PopItemWidth();
}

const char * Actor_meleeWeaponNamesDante[] =
{
	"Rebellion",
	"Cerberus",
	"Agni & Rudra",
	"Nevan",
	"Beowulf",
	"Vergil Yamato",
	"Vergil Beowulf",
	"Vergil Force Edge",
};

const char * Actor_meleeWeaponNamesVergil[] =
{
	"Yamato",
	"Beowulf",
	"Force Edge",
	"Dante Rebellion",
	"Dante Cerberus",
	"Dante Agni & Rudra",
	"Dante Nevan",
	"Dante Beowulf",
};

uint8 Actor_meleeWeaponMapDante[] =
{
	WEAPON_DANTE_REBELLION,
	WEAPON_DANTE_CERBERUS,
	WEAPON_DANTE_AGNI_RUDRA,
	WEAPON_DANTE_NEVAN,
	WEAPON_DANTE_BEOWULF,
	WEAPON_VERGIL_YAMATO,
	WEAPON_VERGIL_BEOWULF,
	WEAPON_VERGIL_FORCE_EDGE,
};

uint8 Actor_meleeWeaponMapVergil[] =
{
	WEAPON_VERGIL_YAMATO,
	WEAPON_VERGIL_BEOWULF,
	WEAPON_VERGIL_FORCE_EDGE,
	WEAPON_DANTE_REBELLION,
	WEAPON_DANTE_CERBERUS,
	WEAPON_DANTE_AGNI_RUDRA,
	WEAPON_DANTE_NEVAN,
	WEAPON_DANTE_BEOWULF,
};

uint8 Actor_meleeWeaponIndex[MAX_PLAYER][MAX_ENTITY][MAX_CHAR][MAX_MELEE_WEAPON] = {};

const char * Actor_rangedWeaponNamesDante[] =
{
	"Ebony & Ivory",
	"Shotgun",
	"Artemis",
	"Spiral",
	"Kalina Ann",
};

uint8 Actor_rangedWeaponMapDante[] =
{
	WEAPON_DANTE_EBONY_IVORY,
	WEAPON_DANTE_SHOTGUN,
	WEAPON_DANTE_ARTEMIS,
	WEAPON_DANTE_SPIRAL,
	WEAPON_DANTE_KALINA_ANN,
};

uint8 Actor_rangedWeaponIndex[MAX_PLAYER][MAX_ENTITY][MAX_CHAR][MAX_RANGED_WEAPON] = {};

template
<
	uint8 configMapItemCount,
	uint8 selectMapItemCount
>
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
	ImGui::Text(label);
	ImGui::Text("");

	ImGui::PushItemWidth(250);

	GUI_Slider<uint8>("", weaponCount, 1, configMapItemCount);

	for_all(uint8, configMapIndex, configMapItemCount)
	{
		auto & configMapItem   = configMap  [configMapIndex];
		auto & selectIndexItem = selectIndex[configMapIndex];

		bool skip = (configMapIndex >= weaponCount) ? true : false;
		GUI_PushDisable(skip);

		GUI_ComboMap
		(
			"",
			selectNames,
			selectMap,
			selectIndexItem,
			configMapItem
		);

		if constexpr (debug)
		{
			ImGui::Text("value %u", configMapItem  );
			ImGui::Text("index %u", selectIndexItem);
		}

		GUI_PopDisable(skip);
	}

	ImGui::PopItemWidth();
}

template <uint8 character>
void Actor_WeaponSelect
(
	uint8 player,
	uint8 entity
)
{
	Actor_WeaponSelectFunction
	(
		"Melee Weapons",
		(character == CHAR_DANTE) ? Config.Actor.meleeWeaponsDante[player][entity] : Config.Actor.meleeWeaponsVergil[player][entity],
		(character == CHAR_DANTE) ? Config.Actor.meleeWeaponCountDante[player][entity] : Config.Actor.meleeWeaponCountVergil[player][entity],
		(character == CHAR_DANTE) ? Actor_meleeWeaponNamesDante : Actor_meleeWeaponNamesVergil,
		(character == CHAR_DANTE) ? Actor_meleeWeaponMapDante   : Actor_meleeWeaponMapVergil,
		Actor_meleeWeaponIndex[player][entity][character]
	);

	if constexpr (character == CHAR_DANTE)
	{
		ImGui::Text("");
		Actor_WeaponSelectFunction
		(
			"Ranged Weapons",
			Config.Actor.rangedWeaponsDante     [player][entity],
			Config.Actor.rangedWeaponCountDante[player][entity],
			Actor_rangedWeaponNamesDante,
			Actor_rangedWeaponMapDante,
			Actor_rangedWeaponIndex[player][entity][character]
		);
	}
}

template
<
	uint8 configMapItemCount,
	uint8 selectMapItemCount
>
void Actor_UpdateWeaponSelectIndicesFunction
(
	uint8(&selectMap)[selectMapItemCount],
	uint8(&selectIndex)[configMapItemCount],
	uint8(&configMap)[configMapItemCount]
)
{
	for_all(uint8, configMapIndex, configMapItemCount)
	{
		auto & configMapItem   = configMap  [configMapIndex];
		auto & selectIndexItem = selectIndex[configMapIndex];

		UpdateMapIndex(selectMap, selectIndexItem, configMapItem);
	}
}


// @Todo: Update.
void Actor_UpdateWeaponSelectIndices()
{
	for_all(uint8, player   , MAX_PLAYER) {
	for_all(uint8, entity   , MAX_ENTITY) {
	for_all(uint8, character, MAX_CHAR  )
	{
		Actor_UpdateWeaponSelectIndicesFunction
		(
			(character == CHAR_DANTE) ? Actor_meleeWeaponMapDante : Actor_meleeWeaponMapVergil,
			Actor_meleeWeaponIndex  [player][entity][character],
			(character == CHAR_DANTE) ? Config.Actor.meleeWeaponsDante[player][entity] : Config.Actor.meleeWeaponsVergil[player][entity]
		);

		if (character == CHAR_DANTE)
		{
			Actor_UpdateWeaponSelectIndicesFunction
			(
				Actor_rangedWeaponMapDante,
				Actor_rangedWeaponIndex  [player][entity][character],
				Config.Actor.rangedWeaponsDante[player][entity]
			);
		}
	}}}
}

void Actor_ActorTabContent
(
	uint8 player,
	uint8 entity
)
{
	ImGui::Text("");

	if (entity == ENTITY_MAIN)
	{
		GUI_Checkbox("Enable Quicksilver" , Config.Actor.enableQuicksilver [player]);
		GUI_Checkbox("Enable Doppelganger", Config.Actor.enableDoppelganger[player]);
	}
	ImGui::Text("");




	Actor_CharacterCostumeSelect(player, entity);
	ImGui::Text("");

	auto & character = Config.Actor.character[player][entity];

	switch (character)
	{
	case CHAR_DANTE:
	{
		Actor_WeaponSelect<CHAR_DANTE>(player, entity);
		break;
	}
	case CHAR_VERGIL:
	{
		Actor_WeaponSelect<CHAR_VERGIL>(player, entity);
		break;
	}
	}

	if (GUI_Button("Reset"))
	{
		Config.Actor.character[player][entity] = DefaultConfig.Actor.character[player][entity];

		memcpy(Config.Actor.costume[player][entity], DefaultConfig.Actor.costume[player][entity], sizeof(Config.Actor.costume[player][entity]));

		//memcpy(Config.Actor.meleeWeapon [player][entity], DefaultConfig.Actor.meleeWeapon [player][entity], sizeof(Config.Actor.meleeWeapon [player][entity]));
		//memcpy(Config.Actor.rangedWeapon[player][entity], DefaultConfig.Actor.rangedWeapon[player][entity], sizeof(Config.Actor.rangedWeapon[player][entity]));

		//memcpy(Config.Actor.meleeWeaponCount [player][entity], DefaultConfig.Actor.meleeWeaponCount [player][entity], sizeof(Config.Actor.meleeWeaponCount [player][entity]));
		//memcpy(Config.Actor.rangedWeaponCount[player][entity], DefaultConfig.Actor.rangedWeaponCount[player][entity], sizeof(Config.Actor.rangedWeaponCount[player][entity]));

		Actor_UpdateWeaponSelectIndices();
	}
}

void Actor_ActorTab
(
	const char * label,
	uint8 player
)
{
	auto condition = (Config.Actor.playerCount < (player + 1));

	GUI_PushDisable(condition);
	if (ImGui::BeginTabItem(label))
	{
		if (ImGui::BeginTabBar("EntityTabs"))
		{
			if (ImGui::BeginTabItem("Main"))
			{
				Actor_ActorTabContent(player, ENTITY_MAIN);
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Clone"))
			{
				Actor_ActorTabContent(player, ENTITY_CLONE);
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}
		ImGui::EndTabItem();
	}
	GUI_PopDisable(condition);
}

void Actor_Init()
{
	Actor_UpdateWeaponSelectIndices();
}

void Actor()
{
	if (ImGui::CollapsingHeader("Actor"))
	{
		ImGui::Text("");
		GUI_Checkbox("Enable", Config.Actor.enable);
		ImGui::Text("");
		if (GUI_Button("Reset"))
		{
			memcpy(&Config.Actor, &DefaultConfig.Actor, sizeof(Config.Actor));
		}
		ImGui::Text("");

		ImGui::PushItemWidth(200);
		GUI_Slider<uint8>("Player Count", Config.Actor.playerCount, 1, MAX_PLAYER);
		ImGui::PopItemWidth();
		ImGui::Text("");

		if (ImGui::BeginTabBar("PlayerTabs"))
		{
			Actor_ActorTab("Player 1", 0);
			Actor_ActorTab("Player 2", 1);
			Actor_ActorTab("Player 3", 2);
			Actor_ActorTab("Player 4", 3);
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
	WEAPON_DANTE_REBELLION,
	WEAPON_DANTE_CERBERUS,
	WEAPON_DANTE_AGNI_RUDRA,
	WEAPON_DANTE_NEVAN,
	WEAPON_DANTE_BEOWULF,
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
	WEAPON_DANTE_EBONY_IVORY,
	WEAPON_DANTE_SHOTGUN,
	WEAPON_DANTE_ARTEMIS,
	WEAPON_DANTE_SPIRAL,
	WEAPON_DANTE_KALINA_ANN,
};

uint8 Arcade_rangedWeaponIndex[2] = {};

void Arcade_Init()
{
	UpdateMapIndex(Arcade_modeMap, Arcade_modeIndex, Config.Arcade.mode);
	UpdateMapIndex(Arcade_meleeWeaponMap , Arcade_meleeWeaponIndex [0], Config.Arcade.meleeWeapons[0] );
	UpdateMapIndex(Arcade_meleeWeaponMap , Arcade_meleeWeaponIndex [1], Config.Arcade.meleeWeapons[1] );
	UpdateMapIndex(Arcade_rangedWeaponMap, Arcade_rangedWeaponIndex[0], Config.Arcade.rangedWeapons[0]);
	UpdateMapIndex(Arcade_rangedWeaponMap, Arcade_rangedWeaponIndex[1], Config.Arcade.rangedWeapons[1]);
}

void Arcade()
{
	if (ImGui::CollapsingHeader("Arcade"))
	{
		ImGui::Text("");
		GUI_Checkbox("Enable", Config.Arcade.enable);
		ImGui::Text("");
		GUI_Button("Reset");
		ImGui::Text("");

		ImGui::PushItemWidth(200);

		GUI_Combo("Mission", Arcade_missionNames, Config.Arcade.mission, ImGuiComboFlags_HeightLargest);

		if ((Config.Arcade.mission >= 1) && (Config.Arcade.mission <= 20))
		{
			GUI_ComboMap("Mode", Arcade_modeNames, Arcade_modeMap, Arcade_modeIndex, Config.Arcade.mode);
			if constexpr (debug)
			{
				ImGui::Text("value %u", Config.Arcade.mode);
				ImGui::Text("index %u", Arcade_modeIndex);
			}
			GUI_InputDefault("Room", Config.Arcade.room, DefaultConfig.Arcade.room);
			ImGui::SameLine();
			GUI_Checkbox("Ignore", Config.Arcade.ignoreRoom);
			GUI_InputDefault("Position", Config.Arcade.position, DefaultConfig.Arcade.position);
			ImGui::SameLine();
			GUI_Checkbox("Ignore", Config.Arcade.ignorePosition);
		}

		if (Config.Arcade.mission == 21)
		{
			GUI_Combo("Floor", Arcade_floorNames, Config.Arcade.floor, ImGuiComboFlags_HeightLargest);
		}

		if (Config.Arcade.mission > 0)
		{
			GUI_InputDefault<float32>("Hit Points"  , Config.Arcade.hitPoints  , DefaultConfig.Arcade.hitPoints  , 1000, "%.0f");
			GUI_InputDefault<float32>("Magic Points", Config.Arcade.magicPoints, DefaultConfig.Arcade.magicPoints, 1000, "%.0f");
		}

		GUI_Combo("Character", Arcade_characterNames, Config.Arcade.character);
		GUI_InputDefault("Costume", Config.Arcade.costume, DefaultConfig.Arcade.costume);

		if ((Config.Arcade.mission > 0) && (Config.Arcade.character == CHAR_DANTE))
		{
			GUI_Combo("Style", Arcade_styleNames, Config.Arcade.style);
			GUI_ComboMap("Melee Weapon 1" , Arcade_meleeWeaponNames , Arcade_meleeWeaponMap , Arcade_meleeWeaponIndex [0], Config.Arcade.meleeWeapons [0]);
			GUI_ComboMap("Melee Weapon 2" , Arcade_meleeWeaponNames , Arcade_meleeWeaponMap , Arcade_meleeWeaponIndex [1], Config.Arcade.meleeWeapons [1]);
			GUI_ComboMap("Ranged Weapon 1", Arcade_rangedWeaponNames, Arcade_rangedWeaponMap, Arcade_rangedWeaponIndex[0], Config.Arcade.rangedWeapons[0]);
			GUI_ComboMap("Ranged Weapon 2", Arcade_rangedWeaponNames, Arcade_rangedWeaponMap, Arcade_rangedWeaponIndex[1], Config.Arcade.rangedWeapons[1]);
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
		GUI_Checkbox("Enable", Config.BossRush.enable);
		ImGui::Text("");
		GUI_Button("Reset");
		GUI_SectionEnd();

		GUI_SectionStart("Mission 5");
		GUI_Checkbox("Skip Jester", Config.BossRush.Mission5.skipJester);
		GUI_SectionEnd();

		GUI_SectionStart("Mission 12");
		GUI_Checkbox("Skip Jester", Config.BossRush.Mission12.skipJester);
		GUI_Checkbox("Skip Geryon Part 1", Config.BossRush.Mission12.skipGeryonPart1);
		GUI_SectionEnd();

		GUI_SectionStart("Mission 17");
		GUI_Checkbox("Skip Jester", Config.BossRush.Mission17.skipJester);
		GUI_SectionEnd();

		GUI_SectionStart("Mission 19");
		GUI_Checkbox("Skip Arkham Part 1", Config.BossRush.Mission19.skipArkhamPart1);
		ImGui::Text("");
	}
}

void Camera()
{
	if (ImGui::CollapsingHeader("Camera"))
	{
		ImGui::Text("");
		GUI_Checkbox("Invert X", Config.Camera.invertX);
		ImGui::Text("");
	}
}

void Cosmetics()
{
	if (ImGui::CollapsingHeader("Cosmetics"))
	{
		ImGui::Text("");
		GUI_Button("Reset");
		GUI_SectionEnd();

		GUI_SectionStart("Color Dante");
		GUI_ColorPalette("Air Hike", Config.Color.Dante.airHike);
		ImGui::Text("");
		ImGui::Text("Trickster");
		GUI_Color("Sky Star", Config.Color.Dante.Trickster.skyStar);
		ImGui::Text("");
		ImGui::Text("Royalguard");
		GUI_Color("Ultimate", Config.Color.Dante.Royalguard.ultimate);
		ImGui::Text("");
		ImGui::Text("Doppelganger");
		GUI_Color("Clone", Config.Color.Dante.Doppelganger.clone);
		ImGui::Text("");
		GUI_ColorPalette("Aura", Config.Color.Dante.aura);
		GUI_Color("Sparda", Config.Color.Dante.sparda);
		ImGui::Text("");
		GUI_Button("Reset");
		GUI_SectionEnd();

		GUI_SectionStart("Color Vergil");
		GUI_ColorPalette("Aura", Config.Color.Vergil.aura);
		GUI_Color("Nero Angelo", Config.Color.Vergil.neroAngelo);
		ImGui::Text("");
		GUI_Button("Reset");
		GUI_SectionEnd();

		GUI_SectionStart("Other");
		GUI_Checkbox("No Devil Form", Config.Other.noDevilForm);
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
	float32 width = 150,
	bool save = true
)
{
	auto & style = ImGui::GetStyle();

	ImGui::PushItemWidth(width);
	GUI_InputDefault(""   , vars[0], defaultVars[0], step, format, flags, save);
	ImGui::SameLine(0, style.ItemInnerSpacing.x);
	GUI_InputDefault(label, vars[1], defaultVars[1], step, format, flags, save);
	ImGui::PopItemWidth();
}

void Dante()
{
	if (ImGui::CollapsingHeader("Dante"))
	{
		ImGui::Text("");
		GUI_Checkbox("Enable", Config.Dante.enable);
		ImGui::Text("");
		if (GUI_Button("Reset"))
		{
			memcpy(&Config.Dante, &DefaultConfig.Dante, sizeof(Config.Dante));
		}
		GUI_SectionEnd();

		GUI_SectionStart("Air Hike");
		GUI_Checkbox("Core Ability", Config.Dante.AirHike.coreAbility);
		ImGui::Text("");
		ActionData<uint8>("Count", Config.Dante.AirHike.count, DefaultConfig.Dante.AirHike.count);
		GUI_SectionEnd();

		GUI_SectionStart("Trickster");
		ActionData<uint8>("Dash Count"     , Config.Dante.Trickster.dashCount    , DefaultConfig.Dante.Trickster.dashCount    );
		ActionData<uint8>("Sky Star Count" , Config.Dante.Trickster.skyStarCount , DefaultConfig.Dante.Trickster.skyStarCount );
		ActionData<uint8>("Air Trick Count", Config.Dante.Trickster.airTrickCount, DefaultConfig.Dante.Trickster.airTrickCount);
		GUI_SectionEnd();

		GUI_SectionStart("Rebellion");
		GUI_Checkbox("Infinite Sword Pierce", Config.Dante.Rebellion.infiniteSwordPierce);
		ImGui::Text("");
		ActionData<float32>("Stinger Duration"    , Config.Dante.Rebellion.stingerDuration   , DefaultConfig.Dante.Rebellion.stingerDuration   , 1 , "%.0f");
		ActionData<float32>("Stinger Range"       , Config.Dante.Rebellion.stingerRange      , DefaultConfig.Dante.Rebellion.stingerRange      , 10, "%.0f");
		ActionData<float32>("Air Stinger Duration", Config.Dante.Rebellion.airStingerDuration, DefaultConfig.Dante.Rebellion.airStingerDuration, 1 , "%.0f");
		ActionData<float32>("Air Stinger Range"   , Config.Dante.Rebellion.airStingerRange   , DefaultConfig.Dante.Rebellion.airStingerRange   , 10, "%.0f");
		GUI_SectionEnd();

		GUI_SectionStart("Cerberus");
		ActionData<float32>("Revolver Height", Config.Dante.Cerberus.revolverHeight, DefaultConfig.Dante.Cerberus.revolverHeight, 0.5f, "%.1f");
		GUI_SectionEnd();

		GUI_SectionStart("Agni & Rudra");
		ActionData<float32>("Jet-Stream Duration", Config.Dante.AgniAndRudra.jetStreamDuration, DefaultConfig.Dante.AgniAndRudra.jetStreamDuration, 1 , "%.0f");
		ActionData<float32>("Jet-Stream Range"   , Config.Dante.AgniAndRudra.jetStreamRange   , DefaultConfig.Dante.AgniAndRudra.jetStreamRange   , 10, "%.0f");
		GUI_SectionEnd();

		GUI_SectionStart("Nevan");
		ActionData<float32>("Reverb Shock Duration", Config.Dante.Nevan.reverbShockDuration, DefaultConfig.Dante.Nevan.reverbShockDuration, 1 , "%.0f");
		ActionData<float32>("Reverb Shock Range"   , Config.Dante.Nevan.reverbShockRange   , DefaultConfig.Dante.Nevan.reverbShockRange   , 10, "%.0f");
		GUI_SectionEnd();

		GUI_SectionStart("Beowulf");
		GUI_Checkbox("Hide", Config.Dante.Beowulf.hide);
		ImGui::Text("");
		ActionData<float32>("Straight Duration"    , Config.Dante.Beowulf.straightDuration   , DefaultConfig.Dante.Beowulf.straightDuration   , 1 , "%.0f");
		ActionData<float32>("Straight Range"       , Config.Dante.Beowulf.straightRange      , DefaultConfig.Dante.Beowulf.straightRange      , 10, "%.0f");
		ActionData<float32>("Air Straight Duration", Config.Dante.Beowulf.airStraightDuration, DefaultConfig.Dante.Beowulf.airStraightDuration, 1 , "%.0f");
		ActionData<float32>("Air Straight Range"   , Config.Dante.Beowulf.airStraightRange   , DefaultConfig.Dante.Beowulf.airStraightRange   , 10, "%.0f");
		ActionData<float32>("Rising Dragon Height" , Config.Dante.Beowulf.risingDragonHeight , DefaultConfig.Dante.Beowulf.risingDragonHeight , 10, "%.1f");
		GUI_SectionEnd();

		GUI_SectionStart("Ebony & Ivory");
		GUI_Checkbox("Foursome Time", Config.Dante.EbonyIvory.foursomeTime);
		GUI_Checkbox("Infinite Rain Storm", Config.Dante.EbonyIvory.infiniteRainStorm);
		GUI_SectionEnd();

		GUI_SectionStart("Shotgun");
		ActionData<float32>("Gun Stinger Duration"    , Config.Dante.Shotgun.gunStingerDuration   , DefaultConfig.Dante.Shotgun.gunStingerDuration   , 1 , "%.0f");
		ActionData<float32>("Gun Stinger Range"       , Config.Dante.Shotgun.gunStingerRange      , DefaultConfig.Dante.Shotgun.gunStingerRange      , 10, "%.0f");
		ActionData<float32>("Air Gun Stinger Duration", Config.Dante.Shotgun.airGunStingerDuration, DefaultConfig.Dante.Shotgun.airGunStingerDuration, 1 , "%.0f");
		ActionData<float32>("Air Gun Stinger Range"   , Config.Dante.Shotgun.airGunStingerRange   , DefaultConfig.Dante.Shotgun.airGunStingerRange   , 10, "%.0f");
		GUI_SectionEnd();

		GUI_SectionStart("Artemis");
		GUI_Checkbox("Swap Normal Shot and Multi Lock", Config.Dante.Artemis.swapNormalShotAndMultiLock);
		GUI_Checkbox("Instant Full Charge", Config.Dante.Artemis.instantFullCharge);
		GUI_SectionEnd();

		ImGui::PushItemWidth(150);
		GUI_InputDefault<float32>("Weapon Switch Timeout", Config.Dante.weaponSwitchTimeout, DefaultConfig.Dante.weaponSwitchTimeout, 1, "%.0f");
		GUI_InputDefault<uint8>("Crazy Combo Level Multiplier", Config.Dante.crazyComboLevelMultiplier, DefaultConfig.Dante.crazyComboLevelMultiplier);
		GUI_Checkbox("Summoned Swords", Config.Dante.summonedSwords);
		ImGui::PopItemWidth();
		ImGui::Text("");
	}
}

void Other()
{
	if (ImGui::CollapsingHeader("Other"))
	{
		ImGui::Text("");
		GUI_Button("Reset");
		ImGui::Text("");

		ImGui::PushItemWidth(150);
		GUI_InputDefault<float32>("Orb Reach", Config.Other.orbReach, DefaultConfig.Other.orbReach, 100, "%.0f");
		ImGui::PopItemWidth();
		GUI_SectionEnd();

		GUI_SectionStart("Magic Points Depletion Rate");
		ImGui::PushItemWidth(150);
		GUI_InputDefault<float32>("Devil"       , Config.Other.MagicPointsDepletionRate.devil       , DefaultConfig.Other.MagicPointsDepletionRate.devil       , 1, "%.1f");
		GUI_InputDefault<float32>("Quicksilver" , Config.Other.MagicPointsDepletionRate.quicksilver , DefaultConfig.Other.MagicPointsDepletionRate.quicksilver , 1, "%.1f");
		GUI_InputDefault<float32>("Doppelganger", Config.Other.MagicPointsDepletionRate.doppelganger, DefaultConfig.Other.MagicPointsDepletionRate.doppelganger, 1, "%.1f");
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
	UpdateMapIndex(ResetMotionState_buttonMap, ResetMotionState_buttonIndex, Config.ResetMotionState.button);
}

void ResetMotionState()
{
	if (ImGui::CollapsingHeader("Reset Motion State"))
	{
		ImGui::Text("");
		GUI_Checkbox("Enable", Config.ResetMotionState.enable);
		ImGui::Text("");
		GUI_Button("Reset");
		ImGui::Text("");
		ImGui::PushItemWidth(200);
		GUI_ComboMap("Button", ResetMotionState_buttonNames, ResetMotionState_buttonMap, ResetMotionState_buttonIndex, Config.ResetMotionState.button, ImGuiComboFlags_HeightLargest);
		ImGui::PopItemWidth();
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
		GUI_Checkbox("Skip Intro"    , Config.Event.skipIntro    );
		if (GUI_Checkbox("Skip Cutscenes", Config.Event.skipCutscenes))
		{
			Event_ToggleSkipCutscenes(Config.Event.skipCutscenes);
		}
		GUI_SectionEnd();

		GUI_SectionStart("File");
		GUI_Checkbox("Prefer Local Files", Config.File.preferLocalFiles);
		GUI_SectionEnd();

		GUI_SectionStart("Graphics");
		ImGui::PushItemWidth(150);
		GUI_InputDefault("Frame Rate", Config.Graphics.frameRate, DefaultConfig.Graphics.frameRate);
		GUI_Combo("V-Sync", Graphics_vSyncNames, Config.Graphics.vSync);
		ImGui::PopItemWidth();
		GUI_SectionEnd();

		GUI_SectionStart("Input");
		GUI_Checkbox("Hide Mouse Cursor", Config.Input.hideMouseCursor);
		GUI_SectionEnd();

		GUI_SectionStart("Window");
		GUI_Checkbox("Force Focus", Config.Window.forceFocus);
		ImGui::Text("");
	}
}

void Speed()
{
	if (ImGui::CollapsingHeader("Speed"))
	{
		ImGui::Text("");

		GUI_Checkbox("Enable", Config.Speed.enable);
		ImGui::Text("");
		GUI_Button("Reset");
		GUI_SectionEnd();

		ImGui::PushItemWidth(200);

		GUI_SectionStart("Main");
		GUI_InputDefault("Base" , Config.Speed.Main.base , DefaultConfig.Speed.Main.base , 0.1f, "%.2f");
		GUI_InputDefault("Turbo", Config.Speed.Main.turbo, DefaultConfig.Speed.Main.turbo, 0.1f, "%.2f");
		GUI_InputDefault("Actor", Config.Speed.Main.actor, DefaultConfig.Speed.Main.actor, 0.1f, "%.2f");
		GUI_InputDefault("Enemy", Config.Speed.Main.enemy, DefaultConfig.Speed.Main.enemy, 0.1f, "%.2f");
		GUI_SectionEnd();

		GUI_SectionStart("Devil");
		ImGui::Text("Dante");
		GUI_InputDefault("Rebellion"   , Config.Speed.Devil.dante[0], DefaultConfig.Speed.Devil.dante[0], 0.1f, "%.2f");
		GUI_InputDefault("Cerberus"    , Config.Speed.Devil.dante[1], DefaultConfig.Speed.Devil.dante[1], 0.1f, "%.2f");
		GUI_InputDefault("Agni & Rudra", Config.Speed.Devil.dante[2], DefaultConfig.Speed.Devil.dante[2], 0.1f, "%.2f");
		GUI_InputDefault("Nevan"       , Config.Speed.Devil.dante[3], DefaultConfig.Speed.Devil.dante[3], 0.1f, "%.2f");
		GUI_InputDefault("Beowulf"     , Config.Speed.Devil.dante[4], DefaultConfig.Speed.Devil.dante[4], 0.1f, "%.2f");
		GUI_InputDefault("Sparda"      , Config.Speed.Devil.dante[5], DefaultConfig.Speed.Devil.dante[5], 0.1f, "%.2f");
		ImGui::Text("");

		ImGui::Text("Vergil");
		GUI_InputDefault("Yamato"    , Config.Speed.Devil.vergil[0], DefaultConfig.Speed.Devil.vergil[0], 0.1f, "%.2f");
		GUI_InputDefault("Beowulf"   , Config.Speed.Devil.vergil[1], DefaultConfig.Speed.Devil.vergil[1], 0.1f, "%.2f");
		GUI_InputDefault("Force Edge", Config.Speed.Devil.vergil[2], DefaultConfig.Speed.Devil.vergil[2], 0.1f, "%.2f");
		ImGui::Text("");

		ImGui::Text("Nero Angelo");
		GUI_InputDefault("Yamato"    , Config.Speed.Devil.neroAngelo[0], DefaultConfig.Speed.Devil.neroAngelo[0], 0.1f, "%.2f");
		GUI_InputDefault("Beowulf"   , Config.Speed.Devil.neroAngelo[1], DefaultConfig.Speed.Devil.neroAngelo[1], 0.1f, "%.2f");
		GUI_InputDefault("Force Edge", Config.Speed.Devil.neroAngelo[2], DefaultConfig.Speed.Devil.neroAngelo[2], 0.1f, "%.2f");
		GUI_SectionEnd();

		GUI_SectionStart("Quicksilver");
		GUI_InputDefault("Actor", Config.Speed.Quicksilver.actor, DefaultConfig.Speed.Quicksilver.actor, 0.1f, "%.2f");
		GUI_InputDefault("Enemy", Config.Speed.Quicksilver.enemy, DefaultConfig.Speed.Quicksilver.enemy, 0.1f, "%.2f");
		ImGui::Text("");

		ImGui::PopItemWidth();
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
			GUI_Input<uint32>("", eventData.room    , 0, "%u", ImGuiInputTextFlags_ReadOnly, false);
			GUI_Input<uint32>("", eventData.position, 0, "%u", ImGuiInputTextFlags_ReadOnly, false);
			ImGui::Text("Next");
			GUI_Input<uint16>("", nextEventData.room    , 1, "%u", 0, false);
			GUI_Input<uint16>("", nextEventData.position, 1, "%u", 0, false);
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
		ImGui::Text("");
		GUI_Checkbox("Enable", Config.Training.enable);
		ImGui::Text("");
		GUI_Button("Reset");
		ImGui::Text("");
		if (GUI_Checkbox("Infinite Hit Points", Config.Training.infiniteHitPoints))
		{
			Training_ToggleInfiniteHitPoints(Config.Training.infiniteHitPoints);
		}
		if (GUI_Checkbox("Infinite Magic Points", Config.Training.infiniteMagicPoints))
		{
		}
		if (GUI_Checkbox("Disable Timer", Config.Training.disableTimer))
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
		GUI_Checkbox("Enable", Config.Vergil.enable);
		ImGui::Text("");
		GUI_Button("Reset");
		GUI_SectionEnd();

		GUI_SectionStart("Dark Slayer");
		ActionData<uint8>("Air Trick Count" , Config.Vergil.DarkSlayer.airTrickCount , DefaultConfig.Vergil.DarkSlayer.airTrickCount );
		ActionData<uint8>("Trick Up Count"  , Config.Vergil.DarkSlayer.trickUpCount  , DefaultConfig.Vergil.DarkSlayer.trickUpCount  );
		ActionData<uint8>("Trick Down Count", Config.Vergil.DarkSlayer.trickDownCount, DefaultConfig.Vergil.DarkSlayer.trickDownCount);
		GUI_SectionEnd();

		GUI_SectionStart("Yamato");
		ActionData<float32>("Rapid Slash Duration", Config.Vergil.Yamato.rapidSlashDuration, DefaultConfig.Vergil.Yamato.rapidSlashDuration, 1 , "%.0f");
		ActionData<float32>("Rapid Slash Range"   , Config.Vergil.Yamato.rapidSlashRange   , DefaultConfig.Vergil.Yamato.rapidSlashRange   , 10, "%.0f");
		ActionData<float32>("Judgement Cut Count" , Config.Vergil.Yamato.judgementCutCount , DefaultConfig.Vergil.Yamato.judgementCutCount , 1 , "%.0f");
		ActionData<float32>("Judgement Cut Range" , Config.Vergil.Yamato.judgementCutRange , DefaultConfig.Vergil.Yamato.judgementCutRange , 10, "%.0f");
		GUI_SectionEnd();

		GUI_SectionStart("Beowulf");
		GUI_Checkbox("Hide", Config.Vergil.Beowulf.hide);
		ImGui::Text("");
		ActionData<float32>("Rising Sun Height", Config.Vergil.Beowulf.risingSunHeight, DefaultConfig.Vergil.Beowulf.risingSunHeight, 1 , "%.0f");
		GUI_SectionEnd();

		GUI_SectionStart("Force Edge");
		GUI_Checkbox("Infinite Round Trip", Config.Vergil.ForceEdge.infiniteRoundTrip);
		ImGui::Text("");
		ActionData<float32>("Stinger Duration"    , Config.Vergil.ForceEdge.stingerDuration   , DefaultConfig.Vergil.ForceEdge.stingerDuration   , 1 , "%.0f");
		ActionData<float32>("Stinger Range"       , Config.Vergil.ForceEdge.stingerRange      , DefaultConfig.Vergil.ForceEdge.stingerRange      , 10, "%.0f");
		ActionData<float32>("Air Stinger Duration", Config.Vergil.ForceEdge.airStingerDuration, DefaultConfig.Vergil.ForceEdge.airStingerDuration, 1 , "%.0f");
		ActionData<float32>("Air Stinger Range"   , Config.Vergil.ForceEdge.airStingerRange   , DefaultConfig.Vergil.ForceEdge.airStingerRange   , 10, "%.0f");
		GUI_SectionEnd();

		GUI_SectionStart("Summoned Swords");
		GUI_Checkbox("Chrono Swords", Config.Vergil.SummonedSwords.chronoSwords);
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
		//ImGui::PushFont(io.Fonts->Fonts[FONT_OVERLAY_8 + Config.Tools.Overlay.fontSizeIndex]);

		//ImGui::SetCurrentFont(io.Fonts->Fonts[FONT_OVERLAY_8]);
	}

	if (ImGui::Begin("DDMK 2.7", &pause))
	{
		ImGui::Text("");





		static uint8 actor = 0;
		static uint8 devil = 0;
		static uint8 devilModelIndex = 0;
		GUI_Input("Actor"            , actor          );
		GUI_Input("Devil"            , devil          );
		GUI_Input("Devil Model Index", devilModelIndex);
		//if (GUI_Button("Update Devil"))
		//{
		//	auto & actorData = *reinterpret_cast<ActorDataDante *>(Actor_actorBaseAddr[actor]);



		//	//ResetModel(actorData.modelData   [(devilModelIndex == 0) ? 1 : 2]);
		//	//ResetModel(actorData.submodelData[(devilModelIndex == 0) ? 1 : 3]);
		//	//ResetModel(actorData.submodelData[(devilModelIndex == 0) ? 2 : 4]);




		//	UpdateDevilModelFunctionDante(actorData, devil, devilModelIndex);
		//}




		//if (GUI_Button("Vector"))
		//{
		//	for_all(uint32, index, devilAuras.count)
		//	{
		//		Log("devilAura[%u] %llX", index, devilAuras[index]);
		//	}
		//}




		
		static uint8 index = 0;
		GUI_Input("Actor", actor);
		GUI_Input("Index", index);
		if (GUI_Button("Flux"))
		{
			func_1F94D0(Actor_actorBaseAddr[actor], index);
		}



		//if (GUI_Button("Pop Dante"))
		//{
		//	ResetModel(Actor_actorBaseAddr[0] + 0xB8C0);
		//	UpdateModelDante(Actor_actorBaseAddr[0]);
		//}


		if (GUI_Button("SpawnActors"))
		{
			SpawnActors();
			//HoboBreak();
		}





		ImGui::Text("");

		auto & sessionData = *reinterpret_cast<SESSION_DATA *>(appBaseAddr + 0xC8F250);

		GUI_Checkbox("One Hit Kill", sessionData.oneHitKill, false);

		ImGui::Text("");



		auto PlayTrack = [](const char * filename)
		{
			func_32BE20((appBaseAddr + 0xCF3700));
			func_32BA90((appBaseAddr + 0xCF3708), filename, 0, 0);
		};


		ImGui::Text("");
		static char buffer[256] = {};
		ImGui::InputText("Filename", buffer, sizeof(buffer));

		if (GUI_Button("Play Track"))
		{
			PlayTrack(buffer);
		}



		ImGui::Text("");








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
}

export void GUI_Init()
{
	BuildFonts();
	Actor_Init();
	Arcade_Init();
	ResetMotionState_Init();
}

#ifdef __GARBAGE__
#endif

#endif
