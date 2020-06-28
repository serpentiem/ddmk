#ifndef __MODULE_GUI__
#define __MODULE_GUI__

module;
#include "../Core/Core.h"

#include "../ImGui/imgui.h"
#include "../ImGui/imgui_internal.h"

#include "ActorData.h"
#include "Internal.h"
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
			ImGui::Text(Locale.Tools.Overlay.focus);
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






// @Todo: Add namespaces.

const char * characterName[] =
{
	"Dante",
	"Bob",
	"Lady",
	"Vergil",
};

inline void CharacterCostumeSelect
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
	GUI_Combo("Character", characterName, character);
	GUI_Input("Costume", costume);
	ImGui::PopItemWidth();
}








const char * meleeWeaponSelectNamesDante[] =
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

const char * meleeWeaponSelectNamesVergil[] =
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

uint8 meleeWeaponSelectMapDante[] =
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

uint8 meleeWeaponSelectMapVergil[] =
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






const char * rangedWeaponSelectNamesDante[] =
{
	"Ebony & Ivory",
	"Shotgun",
	"Artemis",
	"Spiral",
	"Kalina Ann",
};


uint8 rangedWeaponSelectMapDante[] =
{
	WEAPON_DANTE_EBONY_IVORY,
	WEAPON_DANTE_SHOTGUN,
	WEAPON_DANTE_ARTEMIS,
	WEAPON_DANTE_SPIRAL,
	WEAPON_DANTE_KALINA_ANN,
};



















uint8 meleeWeaponSelectIndex [MAX_PLAYER][MAX_ENTITY][MAX_CHAR][MAX_MELEE_WEAPON ] = {};
uint8 rangedWeaponSelectIndex[MAX_PLAYER][MAX_ENTITY][MAX_CHAR][MAX_RANGED_WEAPON] = {};



































template
<
	uint64 configMapItemCount,
	uint64 selectMapItemCount
>
void WeaponSelectFunction
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

template <uint64 character>
void WeaponSelect
(
	uint8 player,
	uint8 entity
)
{
	WeaponSelectFunction
	(
		"Melee Weapons",
		Config.Actor.meleeWeapon     [player][entity][character],
		Config.Actor.meleeWeaponCount[player][entity][character],
		(character == CHAR_DANTE) ? meleeWeaponSelectNamesDante : meleeWeaponSelectNamesVergil,
		(character == CHAR_DANTE) ? meleeWeaponSelectMapDante   : meleeWeaponSelectMapVergil,
		meleeWeaponSelectIndex[player][entity][character]
	);

	if constexpr (character == CHAR_DANTE)
	{
		ImGui::Text("");
		WeaponSelectFunction
		(
			"Ranged Weapons",
			Config.Actor.rangedWeapon     [player][entity][character],
			Config.Actor.rangedWeaponCount[player][entity][character],
			rangedWeaponSelectNamesDante,
			rangedWeaponSelectMapDante,
			rangedWeaponSelectIndex[player][entity][character]
		);
	}
}

















template
<
	uint64 configMapItemCount,
	uint64 selectMapItemCount
>
void UpdateWeaponSelectIndicesFunction
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

		GUI_UpdateComboMapIndex(selectMap, selectIndexItem, configMapItem);
	}
}

void UpdateWeaponSelectIndices()
{
	for_all(uint8, player   , MAX_PLAYER) {
	for_all(uint8, entity   , MAX_ENTITY) {
	for_all(uint8, character, MAX_CHAR  )
	{
		UpdateWeaponSelectIndicesFunction
		(
			(character == CHAR_DANTE) ? meleeWeaponSelectMapDante : meleeWeaponSelectMapVergil,
			meleeWeaponSelectIndex  [player][entity][character],
			Config.Actor.meleeWeapon[player][entity][character]
		);

		if (character == CHAR_DANTE)
		{

			


			UpdateWeaponSelectIndicesFunction
			(
				rangedWeaponSelectMapDante,
				rangedWeaponSelectIndex  [player][entity][character],
				Config.Actor.rangedWeapon[player][entity][character]
			);
		}
	}}}
}
































inline void ResetActorConfig
(
	uint8 player,
	uint8 entity
)
{
	Config.Actor.character[player][entity] = DefaultConfig.Actor.character[player][entity];

	memcpy(Config.Actor.costume[player][entity], DefaultConfig.Actor.costume[player][entity], sizeof(Config.Actor.costume[player][entity]));

	memcpy(Config.Actor.meleeWeapon [player][entity], DefaultConfig.Actor.meleeWeapon [player][entity], sizeof(Config.Actor.meleeWeapon [player][entity]));
	memcpy(Config.Actor.rangedWeapon[player][entity], DefaultConfig.Actor.rangedWeapon[player][entity], sizeof(Config.Actor.rangedWeapon[player][entity]));

	memcpy(Config.Actor.meleeWeaponCount [player][entity], DefaultConfig.Actor.meleeWeaponCount [player][entity], sizeof(Config.Actor.meleeWeaponCount [player][entity]));
	memcpy(Config.Actor.rangedWeaponCount[player][entity], DefaultConfig.Actor.rangedWeaponCount[player][entity], sizeof(Config.Actor.rangedWeaponCount[player][entity]));


	UpdateWeaponSelectIndices();




	//for_all(uint8, character, MAX_CHAR)
	//{
	//	UpdateMeleeWeaponSelectIndex (player, entity, character);
	//	UpdateRangedWeaponSelectIndex(player, entity, character);
	//}
}

inline void ActorTabContent
(
	uint8 player,
	uint8 entity
)
{
	ImGui::Text("");
	CharacterCostumeSelect(player, entity);
	ImGui::Text("");

	auto & character = Config.Actor.character[player][entity];

	switch (character)
	{
	case CHAR_DANTE:
	{
		WeaponSelect<CHAR_DANTE>(player, entity);
		break;
	}
	case CHAR_VERGIL:
	{
		WeaponSelect<CHAR_VERGIL>(player, entity);
		break;
	}
	}




	//if (character >= MAX_CHAR)
	//{
	//	character = CHAR_DANTE;
	//}

	//MeleeWeaponSelect (player, entity, character);
	//RangedWeaponSelect(player, entity, character);

	if (GUI_Button("Reset"))
	{
		ResetActorConfig(player, entity);
	}
}

inline void ActorTab
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
				ActorTabContent(player, ENTITY_MAIN);
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Clone"))
			{
				ActorTabContent(player, ENTITY_CLONE);
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}
		ImGui::EndTabItem();
	}
	GUI_PopDisable(condition);
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

























void Actor()
{
	if (ImGui::CollapsingHeader("Actor"))
	{
		ImGui::Text("");
		if (GUI_Checkbox("Enable", Config.Actor.enable))
		{
			//ToggleUpdateWeapon(Config.Actor.enable);
		}
		ImGui::Text("");
		if (GUI_Button("Reset"))
		{
			memcpy(&Config.Actor, &DefaultConfig.Actor, sizeof(Config.Actor));
		}
		ImGui::Text("");




		ImGui::PushItemWidth(200);
		GUI_Slider<uint8>("Player Count", Config.Actor.playerCount, 1, MAX_ACTOR);
		ImGui::PopItemWidth();
		ImGui::Text("");




		if (ImGui::BeginTabBar("PlayerTabs"))
		{
			ActorTab("Player 1", 0);
			ActorTab("Player 2", 1);
			ActorTab("Player 3", 2);
			ActorTab("Player 4", 3);
			ImGui::EndTabBar();
		}
		ImGui::Text("");
	}
}

























const char * missionNames[] =
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

const char * modeNames[] =
{
	"Easy",
	"Normal",
	"Hard",
	"Very Hard",
	"Dante Must Die",
	"Heaven or Hell",
};

uint32 modeMap[] =
{
	MODE_EASY,
	MODE_NORMAL,
	MODE_HARD,
	MODE_VERY_HARD,
	MODE_DANTE_MUST_DIE,
	MODE_HARD,
};

uint8 modeIndex = 0;

const char * characterNames[] =
{
	"Dante",
	"Bob",
	"Lady",
	"Vergil",
};

const char * styleNames[] =
{
	"Swordmaster",
	"Gunslinger",
	"Trickster",
	"Royalguard",
	"Quicksilver",
	"Doppelganger",
};

const char * meleeWeaponNames[] =
{
	"Rebellion",
	"Cerberus",
	"Agni & Rudra",
	"Nevan",
	"Beowulf",
};

uint8 meleeWeaponMap[] =
{
	WEAPON_DANTE_REBELLION,
	WEAPON_DANTE_CERBERUS,
	WEAPON_DANTE_AGNI_RUDRA,
	WEAPON_DANTE_NEVAN,
	WEAPON_DANTE_BEOWULF,
};

uint8 meleeWeaponIndex[2] = {};

const char * rangedWeaponNames[] =
{
	"Ebony & Ivory",
	"Shotgun",
	"Artemis",
	"Spiral",
	"Kalina Ann",
};

uint8 rangedWeaponMap[] =
{
	WEAPON_DANTE_EBONY_IVORY,
	WEAPON_DANTE_SHOTGUN,
	WEAPON_DANTE_ARTEMIS,
	WEAPON_DANTE_SPIRAL,
	WEAPON_DANTE_KALINA_ANN,
};

uint8 rangedWeaponIndex[2] = {};

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

		GUI_Combo("Mission", missionNames, Config.Arcade.mission, ImGuiComboFlags_HeightLargest);

		if ((Config.Arcade.mission >= 1) && (Config.Arcade.mission <= 20))
		{
			GUI_ComboMap("Mode", modeNames, modeMap, modeIndex, Config.Arcade.mode);
			if constexpr (debug)
			{
				ImGui::Text("value %u", Config.Arcade.mode);
				ImGui::Text("index %u", modeIndex);
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
			GUI_InputDefault("Floor", Config.Arcade.floor, DefaultConfig.Arcade.floor);
		}


		
		if (Config.Arcade.mission > 0)
		{
			GUI_InputDefault<float32>("Hit Points"  , Config.Arcade.hitPoints  , DefaultConfig.Arcade.hitPoints  , 1000, "%.0f");
			GUI_InputDefault<float32>("Magic Points", Config.Arcade.magicPoints, DefaultConfig.Arcade.magicPoints, 1000, "%.0f");
		}
		





		GUI_Combo("Character", characterNames, Config.Arcade.character);
		GUI_InputDefault("Costume", Config.Arcade.costume, DefaultConfig.Arcade.costume);





		if ((Config.Arcade.mission > 0) && (Config.Arcade.character == CHAR_DANTE))
		{
			GUI_Combo("Style", styleNames, Config.Arcade.style);
			GUI_ComboMap("Melee Weapon 1", meleeWeaponNames, meleeWeaponMap, meleeWeaponIndex[0], Config.Arcade.meleeWeapons[0]);
			GUI_ComboMap("Melee Weapon 2", meleeWeaponNames, meleeWeaponMap, meleeWeaponIndex[1], Config.Arcade.meleeWeapons[1]);
			GUI_ComboMap("Ranged Weapon 1", rangedWeaponNames, rangedWeaponMap, rangedWeaponIndex[0], Config.Arcade.rangedWeapons[0]);
			GUI_ComboMap("Ranged Weapon 2", rangedWeaponNames, rangedWeaponMap, rangedWeaponIndex[1], Config.Arcade.rangedWeapons[1]);
		}







		ImGui::Text("");

		ImGui::PopItemWidth();



		//GUI_ComboMap("Melee Weapon 1", meleeWeaponNames, meleeWeapon, Config.Arcade.meleeWeapons[0]);
		//GUI_Combo("Melee Weapon 2", meleeWeaponNames, Config.Arcade.meleeWeapons[1]);
		//GUI_Combo("Ranged Weapon 1", rangedWeaponNames, Config.Arcade.rangedWeapons[0]);
		//GUI_Combo("Ranged Weapon 2", rangedWeaponNames, Config.Arcade.rangedWeapons[1]);






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
		GUI_Checkbox("Skip Geryon Bridge Battle", Config.BossRush.Mission12.skipGeryonBridgeBattle);
		GUI_SectionEnd();

		GUI_SectionStart("Mission 17");
		GUI_Checkbox("Skip Jester", Config.BossRush.Mission17.skipJester);
		GUI_SectionEnd();

		GUI_SectionStart("Mission 19");
		GUI_Checkbox("Skip Arkham Battle Part 1", Config.BossRush.Mission19.skipArkhamBattlePart1);
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


// ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview


bool GUI_ColorEdit4
(
	const char * label,
	float32(&var)[4],
	ImGuiColorEditFlags flags = 0,
	bool save = true
)
{
	bool update = false;

	GUI_PushId();
	if (ImGui::ColorEdit4(label, var, flags))
	{
		update = true;
	}
	GUI_PopId();

	if (update && save)
	{
		SaveConfig();
	}

	return update;
}

template <uint8 count>
bool GUI_ColorPalette
(
	const char * label,
	float32(&vars)[count][4]
)
{
	bool update = false;
	auto & style = ImGui::GetStyle();

	for_all(uint8, index, count)
	{
		if (GUI_ColorEdit4("", vars[index], ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview))
		{
			update = true;
		}
		ImGui::SameLine(0, style.ItemInnerSpacing.x);
	}

	ImGui::Text(label);

	return update;
}

bool GUI_Color
(
	const char * label,
	float32(&var)[4]
)
{
	return GUI_ColorEdit4(label, var, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview);
}



void Section(const char * label)
{

	ImGui::Text(label);

	auto & style = ImGui::GetStyle();

	ImGui::SameLine(0, style.ItemInnerSpacing.x);



	auto size = ImGui::CalcTextSize(label);

	auto window = ImGui::GetCurrentWindow();

	float32 x1 = window->Pos.x + size.x + 16;
	float32 x2 = window->Pos.x + window->Size.x;

	//float thickness_draw = 1.0f;
	//float thickness_layout = 0.0f;
	const ImRect bb(ImVec2(x1, window->DC.CursorPos.y + 7), ImVec2(x2, window->DC.CursorPos.y + 7));
	ImGui::ItemSize(ImVec2(0.0f, 0.0f));
	window->DrawList->AddLine(bb.Min, ImVec2(bb.Max.x, bb.Min.y), ImGui::GetColorU32(ImGuiCol_Separator));


	ImGui::Text("");

}




void Cosmetics()
{
	if (ImGui::CollapsingHeader("Cosmetics"))
	{
		ImGui::Text("");


		GUI_Button("Reset");
		//ImGui::Text("");

		GUI_SectionEnd();




		//ColorPalette("Aura", Config.Cosmetics.Color.Aura.dante);

		//ImGui::Text("Color");




		float32 off = 123;

		
		//GUI_SectionStart("Color Dante");


		

		//ImGui::Text("Color Dante");

		//ImGui::SameLine(0, style.ItemInnerSpacing.x);

		//ImGui::SeparatorEx()

		//ImGui::Line

		




		//Section("Color Dante");


		ImGui::Text("Color Dante");
		ImGui::Text("");


		


		//ImGui::Text("");




		GUI_ColorPalette("Air Hike", Config.Color.Dante.airHike);

		ImGui::Text("");

		ImGui::Text("Trickster");

		//ImGui::SetCursorPosX(100);
		GUI_Color("Sky Star", Config.Color.Dante.Trickster.skyStar);
		//GUI_Color("", Config.Color.Dante.Trickster.skyStar);
		//ImGui::SameLine(off);
		//ImGui::Text("Sky Star");

		ImGui::Text("");


		ImGui::Text("Royalguard");
		//ImGui::SetCursorPosX(100);
		GUI_Color("Ultimate", Config.Color.Dante.Royalguard.ultimate);
		//GUI_Color("", Config.Color.Dante.Royalguard.ultimate);
		//ImGui::SameLine(off);
		//ImGui::Text("Ultimate");

		ImGui::Text("");

		ImGui::Text("Doppelganger");
		//ImGui::SetCursorPosX(100);
		GUI_Color("Clone", Config.Color.Dante.Doppelganger.clone);



		//GUI_Color("", Config.Color.Dante.Doppelganger.clone);
		//ImGui::SameLine(off);
		//ImGui::Text("Clone");
		

		ImGui::Text("");
		GUI_ColorPalette("Aura", Config.Color.Dante.aura);
		//ImGui::SetCursorPosX(100);

		//ImGui::Text("");

		GUI_Color("Sparda", Config.Color.Dante.sparda);
		//GUI_Color("", Config.Color.Dante.sparda);
		//ImGui::SameLine(off);
		//ImGui::Text("Hentai");



		//GUI_SectionEnd();


		//ImGui::Text("");


		//Section("Color Vergil");

		ImGui::Text("");
		GUI_Button("Reset");

		GUI_SectionEnd();

		ImGui::Text("Color Vergil");
		ImGui::Text("");

		GUI_ColorPalette("Aura", Config.Color.Vergil.aura);
		GUI_Color("Nero Angelo", Config.Color.Vergil.neroAngelo);



		ImGui::Text("");
		GUI_Button("Reset");





		ImGui::Text("");
	}
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


		//GUI_SectionStart();
		GUI_InputDefault<float32>("Weapon Switch Timeout", Config.Dante.weaponSwitchTimeout, DefaultConfig.Dante.weaponSwitchTimeout, 1, "%.0f");
		GUI_InputDefault<uint8>("Crazy Combo Level Multiplier", Config.Dante.crazyComboLevelMultiplier, DefaultConfig.Dante.crazyComboLevelMultiplier);
		GUI_Checkbox("Summoned Swords", Config.Dante.summonedSwords);

		ImGui::PopItemWidth();


		//GUI_SectionEnd();

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







const char * vSyncNames[] =
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
		GUI_Checkbox("Skip Cutscenes", Config.Event.skipCutscenes);
		GUI_SectionEnd();

		GUI_SectionStart("File");
		GUI_Checkbox("Prefer Local Files", Config.File.preferLocalFiles);
		GUI_SectionEnd();

		GUI_SectionStart("Graphics");

		ImGui::PushItemWidth(150);

		GUI_InputDefault("Frame Rate", Config.Graphics.frameRate, DefaultConfig.Graphics.frameRate);
		GUI_Combo("V-Sync", vSyncNames, Config.Graphics.vSync);

		ImGui::PopItemWidth();

		GUI_SectionEnd();

		GUI_SectionStart("Input");
		GUI_Checkbox("Hide Mouse Cursor", Config.Input.hideMouseCursor);
		GUI_SectionEnd();

		GUI_SectionStart("Window");
		GUI_Checkbox("Force Focus", Config.Window.forceFocus);
		//GUI_SectionEnd();

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
		//ImGui::Text("");
		ImGui::Text("Vergil");
		GUI_InputDefault("Yamato"    , Config.Speed.Devil.vergil[0], DefaultConfig.Speed.Devil.vergil[0], 0.1f, "%.2f");
		GUI_InputDefault("Beowulf"   , Config.Speed.Devil.vergil[1], DefaultConfig.Speed.Devil.vergil[1], 0.1f, "%.2f");
		GUI_InputDefault("Force Edge", Config.Speed.Devil.vergil[2], DefaultConfig.Speed.Devil.vergil[2], 0.1f, "%.2f");
		//ImGui::Text("");
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
			auto pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E10);
			if (!pool)
			{
				return false;
			}
			if (!pool[8])
			{
				return false;
			}
			if (!pool[12])
			{
				return false;
			}
			auto & eventData = *reinterpret_cast<EVENT_DATA *>(pool[8]);
			auto & nextEventData = *reinterpret_cast<NEXT_EVENT_DATA *>(pool[12]);
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
				eventData.index = EVENT_TELEPORT;
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






void Main()
{
	static bool run = false;
	if (!run)
	{
		run = true;
		ImGui::SetNextWindowSize(ImVec2(600, 650));
		ImGui::SetNextWindowPos(ImVec2(650, 50));

		//ImGuiIO & io = ImGui::GetIO();
		//io.FontDefault = io.Fonts->Fonts[FONT_MAIN];
		//ImGui::PushFont(io.Fonts->Fonts[FONT_OVERLAY_8 + Config.Tools.Overlay.fontSizeIndex]);

		//ImGui::SetCurrentFont(io.Fonts->Fonts[FONT_OVERLAY_8]);
	}

	if (ImGui::Begin("DDMK 2.7", &pause))
	{
		Actor();
		Arcade();
		BossRush();
		Camera();
		Cosmetics();
		Dante();
		Repair();
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
	UpdateWeaponSelectIndices();


	GUI_UpdateComboMapIndex(modeMap, modeIndex, Config.Arcade.mode);


	GUI_UpdateComboMapIndex(meleeWeaponMap, meleeWeaponIndex[0], Config.Arcade.meleeWeapons[0]);
	GUI_UpdateComboMapIndex(meleeWeaponMap, meleeWeaponIndex[1], Config.Arcade.meleeWeapons[1]);
	GUI_UpdateComboMapIndex(rangedWeaponMap, rangedWeaponIndex[0], Config.Arcade.rangedWeapons[0]);
	GUI_UpdateComboMapIndex(rangedWeaponMap, rangedWeaponIndex[1], Config.Arcade.rangedWeapons[1]);
	




	//GUI_UpdateComboMapIndex()



}

#ifdef __GARBAGE__











//
//inline void UpdateMeleeWeaponSelectIndex
//(
//	uint8 player,
//	uint8 entity,
//	uint8 character
//)
//{
//	UpdateWeaponSelectIndex
//	(
//		Config.Actor.meleeWeapon[player][entity][character],
//		MAX_MELEE_WEAPON,
//		meleeWeaponSelectMap     [character],
//		meleeWeaponSelectMapCount[character],
//		meleeWeaponSelectIndex[player][entity][character]
//	);
//}
//
//inline void UpdateRangedWeaponSelectIndex
//(
//	uint8 player,
//	uint8 entity,
//	uint8 character
//)
//{
//	UpdateWeaponSelectIndex
//	(
//		Config.Actor.rangedWeapon[player][entity][character],
//		MAX_RANGED_WEAPON,
//		rangedWeaponSelectMap     [character],
//		rangedWeaponSelectMapCount[character],
//		rangedWeaponSelectIndex[player][entity][character]
//	);
//}
//
//inline void UpdateWeaponSelectIndices()
//{
//	for_all(uint8, player   , MAX_PLAYER){
//	for_all(uint8, entity   , MAX_ENTITY){
//	for_all(uint8, character, MAX_CHAR  )
//	{
//		UpdateMeleeWeaponSelectIndex (player, entity, character);
//		UpdateRangedWeaponSelectIndex(player, entity, character);
//	}}}
//}
//

































//inline void WeaponSelect
//(
//	const char *  label,
//	uint8      *  configMap,
//	uint8         configMapCount,
//	uint8      *  selectMap,
//	uint8         selectMapCount,
//	const char ** selectName,
//	uint8      *  selectIndex,
//	uint8      &  weaponCount
//)
//{
//	if (!selectMap)
//	{
//		return;
//	}
//
//	ImGui::Text(label);
//	ImGui::Text("");
//
//	ImGui::PushItemWidth(250);
//
//	GUI_Slider<uint8>("", weaponCount, 1, configMapCount);
//
//	for_all(uint8, configMapIndex, configMapCount)
//	{
//		bool skip = (configMapIndex >= weaponCount) ? true : false;
//		GUI_PushDisable(skip);
//		auto & configMapItem   = configMap  [configMapIndex];
//		auto & selectIndexItem = selectIndex[configMapIndex];
//
//		GUI_ComboMap("", selectName)
//
//
//
//		GUI_ComboMap
//		(
//			"",
//			selectName,
//			selectMapCount,
//			selectMap,
//			selectIndexItem,
//			configMapItem
//		);
//		GUI_PopDisable(skip);
//	}
//
//	ImGui::PopItemWidth();
//
//	ImGui::Text("");
//}
//
//inline void MeleeWeaponSelect
//(
//	uint8 player,
//	uint8 entity,
//	uint8 character
//)
//{
//	WeaponSelect
//	(
//		"Melee Weapons",
//		Config.Actor.meleeWeapon[player][entity][character],
//		MAX_MELEE_WEAPON,
//		meleeWeaponSelectMap     [character],
//		meleeWeaponSelectMapCount[character],
//		meleeWeaponSelectName    [character],
//		meleeWeaponSelectIndex[player][entity][character],
//		Config.Actor.meleeWeaponCount[player][entity][character]
//	);
//}

//inline void RangedWeaponSelect
//(
//	uint8 player,
//	uint8 entity,
//	uint8 character
//)
//{
//	WeaponSelect
//	(
//		"Ranged Weapons",
//		Config.Actor.rangedWeapon[player][entity][character],
//		MAX_RANGED_WEAPON,
//		rangedWeaponSelectMap     [character],
//		rangedWeaponSelectMapCount[character],
//		rangedWeaponSelectName    [character],
//		rangedWeaponSelectIndex[player][entity][character],
//		Config.Actor.rangedWeaponCount[player][entity][character]
//	);
//}






















//inline void UpdateWeaponSelectIndex
//(
//	uint8 * configMap,
//	uint8   configMapCount,
//	uint8 * selectMap,
//	uint8   selectMapCount,
//	uint8 * selectIndex
//)
//{
//	if (!selectMap)
//	{
//		return;
//	}
//	for_all(uint8, configMapIndex, configMapCount)
//	{
//		auto & configMapItem   = configMap  [configMapIndex];
//		auto & selectIndexItem = selectIndex[configMapIndex];
//		for_all(uint8, selectMapIndex, selectMapCount)
//		{
//			auto & selectMapItem = selectMap[selectMapIndex];
//			if (selectMapItem == configMapItem)
//			{
//				selectIndexItem = selectMapIndex;
//				break;
//			}
//		}
//	}
//}



//
//
//void UpdateMeleeWeaponSelectIndex
//(
//	uint8 player,
//	uint8 entity,
//	uint8 character
//)
//{
//	GUI_UpdateComboMapIndex
//	(
//		meleeWeaponSelectMapDante,
//		meleeWeaponSelectIndex[player][entity][character][0],
//		Config.Actor.meleeWeapon[player][entity][character][0]
//	);
//}
//
//


//
//
//inline void WeaponSelect
//(
//	const char *  label,
//	uint8      *  configMap,
//	uint8         configMapCount,
//	uint8      *  selectMap,
//	uint8         selectMapCount,
//	const char ** selectName,
//	uint8      *  selectIndex,
//	uint8      &  weaponCount
//)
//{
//	if (!selectMap)
//	{
//		return;
//	}
//
//	ImGui::Text(label);
//	ImGui::Text("");
//
//	ImGui::PushItemWidth(250);
//
//	GUI_Slider<uint8>("", weaponCount, 1, configMapCount);
//
//	for_all(uint8, configMapIndex, configMapCount)
//	{
//		bool skip = (configMapIndex >= weaponCount) ? true : false;
//		GUI_PushDisable(skip);
//		auto & configMapItem   = configMap  [configMapIndex];
//		auto & selectIndexItem = selectIndex[configMapIndex];
//
//		GUI_ComboMap("", selectName)
//
//
//
//			GUI_ComboMap
//			(
//				"",
//				selectName,
//				selectMapCount,
//				selectMap,
//				selectIndexItem,
//				configMapItem
//			);
//		GUI_PopDisable(skip);
//	}
//
//	ImGui::PopItemWidth();
//
//	ImGui::Text("");
//}
//
//inline void MeleeWeaponSelect
//(
//	uint8 player,
//	uint8 entity,
//	uint8 character
//)
//{
//	WeaponSelect
//	(
//		"Melee Weapons",
//		Config.Actor.meleeWeapon[player][entity][character],
//		MAX_MELEE_WEAPON,
//		meleeWeaponSelectMap     [character],
//		meleeWeaponSelectMapCount[character],
//		meleeWeaponSelectName    [character],
//		meleeWeaponSelectIndex[player][entity][character],
//		Config.Actor.meleeWeaponCount[player][entity][character]
//	);
//}












//uint8 * meleeWeaponSelectMap[MAX_CHAR] =
//{
//	meleeWeaponSelectMapDante,
//	0,
//	0,
//	meleeWeaponSelectMapVergil
//};
//
//uint8 meleeWeaponSelectMapCount[MAX_CHAR] =
//{
//	countof(meleeWeaponSelectMapDante),
//	0,
//	0,
//	countof(meleeWeaponSelectMapVergil),
//};

// $MeleeWeaponSelectMapEnd

// $MeleeWeaponSelectNameStart

//const char * meleeWeaponSelectNameDante[] =
//{
//	"Rebellion",
//	"Cerberus",
//	"Agni & Rudra",
//	"Nevan",
//	"Beowulf",
//	"Vergil Yamato",
//	"Vergil Beowulf",
//	"Vergil Force Edge",
//};
//
//const char * meleeWeaponSelectNameVergil[] =
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

//const char ** meleeWeaponSelectName[MAX_CHAR] =
//{
//	meleeWeaponSelectNameDante,
//	0,
//	0,
//	meleeWeaponSelectNameVergil,
//};
//
//uint8 meleeWeaponSelectNameCount[MAX_CHAR] =
//{
//	countof(meleeWeaponSelectNameDante),
//	0,
//	0,
//	countof(meleeWeaponSelectNameVergil),
//};

// $MeleeWeaponSelectNameEnd

// $RangedWeaponSelectMapStart


//
//uint8 * rangedWeaponSelectMap[MAX_CHAR] =
//{
//	rangedWeaponSelectMapDante,
//	0,
//	0,
//	0,
//};
//
//uint8 rangedWeaponSelectMapCount[MAX_CHAR] =
//{
//	countof(rangedWeaponSelectMapDante),
//	0,
//	0,
//	0,
//};

// $RangedWeaponSelectMapEnd

// $RangedWeaponSelectNameStart


//
//const char ** rangedWeaponSelectName[MAX_CHAR] =
//{
//	rangedWeaponSelectNameDante,
//	0,
//	0,
//	0,
//};
//
//uint8 rangedWeaponSelectNameCount[MAX_CHAR] =
//{
//	countof(rangedWeaponSelectNameDante),
//	0,
//	0,
//	0,
//};

// $RangedWeaponSelectNameEnd

//uint8 meleeWeaponSelectIndex [MAX_PLAYER][MAX_ENTITY][MAX_CHAR][MAX_MELEE_WEAPON ] = {};




#endif

#endif
