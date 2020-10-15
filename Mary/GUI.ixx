module;
#include "../Core/Core.h"

#include "../ImGui/imgui.h"

#include "Locale.h"
#include "Vars.h"
export module GUI;

import Core_GUI;

import Actor;
import Arcade;
import Camera;
import Config;
import Event;
import File;
import Internal;
import Model;
import Pause;
import Scene;
import Speed;
import State;
import Training;
import Window;

#define debug true

// @Todo: Update.
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





void TooltipHelper
(
	const char * name,
	const char * description
)
{
	ImGui::TextDisabled(name);
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::Text(description);
		ImGui::EndTooltip();
	}
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






const char * Actor_meleeWeaponNamesDante[] =
{
	"Rebellion",
	"Cerberus",
	"Agni & Rudra",
	"Nevan",
	"Beowulf",
};

uint8 Actor_meleeWeaponsDante[] =
{
	WEAPON_REBELLION,
	WEAPON_CERBERUS,
	WEAPON_AGNI_RUDRA,
	WEAPON_NEVAN,
	WEAPON_BEOWULF_DANTE,
};

uint8 Actor_meleeWeaponIndexDante[MAX_PLAYER][MAX_ENTITY] = {};

const char * Actor_meleeWeaponNamesVergil[] =
{
	"Yamato",
	"Beowulf",
	"Yamato & Force Edge",
};

uint8 Actor_meleeWeaponsVergil[] =
{
	WEAPON_YAMATO_VERGIL,
	WEAPON_BEOWULF_VERGIL,
	WEAPON_YAMATO_FORCE_EDGE,
};

uint8 Actor_meleeWeaponIndexVergil[MAX_PLAYER][MAX_ENTITY] = {};



















const char * Actor_meleeWeaponNames[] =
{
	"Rebellion",
	"Cerberus",
	"Agni & Rudra",
	"Nevan",
	"Beowulf Dante",
	"Yamato",
	"Beowulf Vergil",
	"Yamato & Force Edge",
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
	WEAPON_YAMATO_FORCE_EDGE,
};

uint8 Actor_meleeWeaponIndices[MAX_PLAYER][MAX_ENTITY][MELEE_WEAPON_COUNT] = {};

















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

uint8 Actor_rangedWeaponIndices[MAX_PLAYER][MAX_ENTITY][RANGED_WEAPON_COUNT] = {};

void Actor_UpdateIndices()
{
	for_all(uint8, player, MAX_PLAYER){
	for_all(uint8, entity, MAX_ENTITY)
	{
		auto & playerData = queuedConfig.Actor.playerData[player][entity];

		switch (playerData.character)
		{
			case CHAR_DANTE:
			{
				UpdateMapIndex
				(
					Actor_meleeWeaponsDante,
					Actor_meleeWeaponIndexDante[player][entity],
					playerData.meleeWeapons[0]
				);

				break;
			}
			case CHAR_VERGIL:
			{
				UpdateMapIndex
				(
					Actor_meleeWeaponsVergil,
					Actor_meleeWeaponIndexVergil[player][entity],
					playerData.meleeWeapons[0]
				);

				break;
			}
		}

		for_each(uint8, index, 1, MELEE_WEAPON_COUNT)
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

		for_each(uint8, index, 1, RANGED_WEAPON_COUNT)
		{
			UpdateMapIndex
			(
				Actor_rangedWeapons,
				Actor_rangedWeaponIndices[player][entity][index],
				playerData.rangedWeapons[index]
			);
		}
	}}
}

void Actor_PlayerTab
(
	uint8 player,
	uint8 entity
)
{
	auto & playerData = queuedConfig.Actor.playerData[player][entity];

	ImGui::PushItemWidth(150);
	if (GUI_Combo("Character", Actor_characterNames, playerData.character))
	{
		ApplyDefaultPlayerData(playerData, playerData.character);

		Actor_UpdateIndices();
	}
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

	GUI_Slider<uint8>("", playerData.meleeWeaponCount, 1, MELEE_WEAPON_COUNT);

	switch (playerData.character)
	{
		case CHAR_DANTE:
		{
			GUI_ComboMap
			(
				"",
				Actor_meleeWeaponNamesDante,
				Actor_meleeWeaponsDante,
				Actor_meleeWeaponIndexDante[player][entity],
				playerData.meleeWeapons[0]
			);

			break;
		}
		case CHAR_VERGIL:
		{
			GUI_ComboMap
			(
				"",
				Actor_meleeWeaponNamesVergil,
				Actor_meleeWeaponsVergil,
				Actor_meleeWeaponIndexVergil[player][entity],
				playerData.meleeWeapons[0]
			);

			break;
		}
	}

	for_each(uint8, index, 1, MELEE_WEAPON_COUNT)
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

	GUI_Slider<uint8>("", playerData.rangedWeaponCount, 1, RANGED_WEAPON_COUNT);

	for_all(uint8, index, RANGED_WEAPON_COUNT)
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

		if (GUI_ResetButton())
		{
			memcpy
			(
				&queuedConfig.Actor,
				&defaultConfig.Actor,
				sizeof(Config::Actor)
			);

			Actor_UpdateIndices();

			if
			(
				(g_scene == SCENE_MAIN          ) ||
				(g_scene == SCENE_MISSION_SELECT)
			)
			{
				memcpy
				(
					&activeConfig.Actor,
					&queuedConfig.Actor,
					sizeof(Config::Actor)
				);

				Actor_Toggle(activeConfig.Actor.enable);
			}
		}
		ImGui::Text("");

		GUI_Checkbox2
		(
			"Show Idle Actors",
			activeConfig.Actor.showIdleActors,
			queuedConfig.Actor.showIdleActors
		);
		ImGui::Text("");

		ImGui::PushItemWidth(200);
		GUI_Slider<uint8>("Player Count", queuedConfig.Actor.playerCount, 1, MAX_PLAYER);
		ImGui::PopItemWidth();
		ImGui::Text("");

		if (ImGui::BeginTabBar("PlayerTabs"))
		{
			for_all(uint8, player, MAX_PLAYER)
			{
				auto condition = (player >= queuedConfig.Actor.playerCount);

				GUI_PushDisable(condition);

				if (ImGui::BeginTabItem(Actor_playerNames[player]))
				{
					ImGui::Text("");

					if (player == 0)
					{
						GUI_Checkbox("Enable Quicksilver", queuedConfig.Actor.enableQuicksilver);
					}

					if (GUI_Checkbox("Enable Doppelganger", queuedConfig.Actor.enableDoppelganger[player]))
					{
						for_all(uint8, entity, MAX_ENTITY)
						{
							auto & playerData = queuedConfig.Actor.playerData[player][entity];

							ApplyDefaultPlayerData(playerData, playerData.character);

							Actor_UpdateIndices();
						}
					}
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

void Arcade_UpdateIndices()
{
	UpdateMapIndex
	(
		Arcade_modeMap,
		Arcade_modeIndex,
		activeConfig.Arcade.mode
	);
	UpdateMapIndex
	(
		Arcade_meleeWeaponMap,
		Arcade_meleeWeaponIndex[0],
		activeConfig.Arcade.weapons[0]
	);
	UpdateMapIndex
	(
		Arcade_meleeWeaponMap,
		Arcade_meleeWeaponIndex[1],
		activeConfig.Arcade.weapons[1]
	);
	UpdateMapIndex
	(
		Arcade_rangedWeaponMap,
		Arcade_rangedWeaponIndex[0],
		activeConfig.Arcade.weapons[2]
	);
	UpdateMapIndex
	(
		Arcade_rangedWeaponMap,
		Arcade_rangedWeaponIndex[1],
		activeConfig.Arcade.weapons[3]
	);
}

void Arcade()
{
	if (ImGui::CollapsingHeader("Arcade"))
	{
		ImGui::Text("");

		if
		(
			GUI_Checkbox2
			(
				"Enable",
				activeConfig.Arcade.enable,
				queuedConfig.Arcade.enable
			)
		)
		{
			Arcade_Toggle(activeConfig.Arcade.enable);
		}
		ImGui::Text("");

		if (GUI_ResetButton())
		{
			memcpy
			(
				&queuedConfig.Arcade,
				&defaultConfig.Arcade,
				sizeof(Config::Arcade)
			);
			memcpy
			(
				&activeConfig.Arcade,
				&queuedConfig.Arcade,
				sizeof(Config::Arcade)
			);

			Arcade_UpdateIndices();

			Arcade_Toggle(activeConfig.Arcade.enable);
		}
		ImGui::Text("");

		ImGui::PushItemWidth(200);
		GUI_Combo2
		(
			"Mission",
			Arcade_missionNames,
			activeConfig.Arcade.mission,
			queuedConfig.Arcade.mission,
			ImGuiComboFlags_HeightLargest
		);

		if
		(
			(activeConfig.Arcade.mission >= 1 ) &&
			(activeConfig.Arcade.mission <= 20)
		)
		{
			GUI_ComboMap2
			(
				"Mode",
				Arcade_modeNames,
				Arcade_modeMap,
				Arcade_modeIndex,
				activeConfig.Arcade.mode,
				queuedConfig.Arcade.mode
			);
			GUI_InputDefault2
			(
				"Room",
				activeConfig.Arcade.room,
				queuedConfig.Arcade.room,
				defaultConfig.Arcade.room
			);
			ImGui::SameLine();
			GUI_Checkbox2
			(
				"Ignore",
				activeConfig.Arcade.ignoreRoom,
				queuedConfig.Arcade.ignoreRoom
			);
			GUI_InputDefault2
			(
				"Position",
				activeConfig.Arcade.position,
				queuedConfig.Arcade.position,
				defaultConfig.Arcade.position
			);
			ImGui::SameLine();
			GUI_Checkbox2
			(
				"Ignore",
				activeConfig.Arcade.ignorePosition,
				queuedConfig.Arcade.ignorePosition
			);
		}

		if (activeConfig.Arcade.mission == 21)
		{
			GUI_Combo2
			(
				"Floor",
				Arcade_floorNames,
				activeConfig.Arcade.floor,
				queuedConfig.Arcade.floor,
				ImGuiComboFlags_HeightLargest
			);
		}

		if (activeConfig.Arcade.mission > 0)
		{
			GUI_InputDefault2
			(
				"Hit Points",
				activeConfig.Arcade.hitPoints,
				queuedConfig.Arcade.hitPoints,
				defaultConfig.Arcade.hitPoints,
				1000.0f,
				"%.0f"
			);
			GUI_InputDefault2
			(
				"Magic Points",
				activeConfig.Arcade.magicPoints,
				queuedConfig.Arcade.magicPoints,
				defaultConfig.Arcade.magicPoints,
				1000.0f,
				"%.0f"
			);
		}

		GUI_Combo2
		(
			"Character",
			Arcade_characterNames,
			activeConfig.Arcade.character,
			queuedConfig.Arcade.character
		);
		GUI_InputDefault2
		(
			"Costume",
			activeConfig.Arcade.costume,
			queuedConfig.Arcade.costume,
			defaultConfig.Arcade.costume
		);

		if
		(
			(activeConfig.Arcade.mission > 0) &&
			(activeConfig.Arcade.character == CHAR_DANTE)
		)
		{
			GUI_Combo2
			(
				"Style",
				Arcade_styleNames,
				activeConfig.Arcade.style,
				queuedConfig.Arcade.style
			);
			GUI_ComboMap2
			(
				"Melee Weapon 1",
				Arcade_meleeWeaponNames,
				Arcade_meleeWeaponMap,
				Arcade_meleeWeaponIndex[0],
				activeConfig.Arcade.weapons[0],
				queuedConfig.Arcade.weapons[0]
			);
			GUI_ComboMap2
			(
				"Melee Weapon 2",
				Arcade_meleeWeaponNames,
				Arcade_meleeWeaponMap,
				Arcade_meleeWeaponIndex[1],
				activeConfig.Arcade.weapons[1],
				queuedConfig.Arcade.weapons[1]
			);
			GUI_ComboMap2
			(
				"Ranged Weapon 1",
				Arcade_rangedWeaponNames,
				Arcade_rangedWeaponMap,
				Arcade_rangedWeaponIndex[0],
				activeConfig.Arcade.weapons[2],
				queuedConfig.Arcade.weapons[2]
			);
			GUI_ComboMap2
			(
				"Ranged Weapon 2",
				Arcade_rangedWeaponNames,
				Arcade_rangedWeaponMap,
				Arcade_rangedWeaponIndex[1],
				activeConfig.Arcade.weapons[3],
				queuedConfig.Arcade.weapons[3]
			);
		}
		ImGui::PopItemWidth();

		ImGui::Text("");
	}
}

void BossRush()
{
	if (ImGui::CollapsingHeader("Boss Rush"))
	{
		ImGui::Text("");

		GUI_Checkbox2
		(
			"Enable",
			activeConfig.BossRush.enable,
			queuedConfig.BossRush.enable
		);
		ImGui::Text("");

		if (GUI_ResetButton())
		{
			memcpy
			(
				&queuedConfig.BossRush,
				&defaultConfig.BossRush,
				sizeof(Config::BossRush)
			);
			memcpy
			(
				&activeConfig.BossRush,
				&queuedConfig.BossRush,
				sizeof(Config::BossRush)
			);
		}
		GUI_SectionEnd();
		ImGui::Text("");

		GUI_SectionStart("Mission 5");
		GUI_Checkbox2
		(
			"Skip Jester",
			activeConfig.BossRush.Mission5.skipJester,
			queuedConfig.BossRush.Mission5.skipJester
		);
		GUI_SectionEnd();
		ImGui::Text("");

		GUI_SectionStart("Mission 12");
		GUI_Checkbox2
		(
			"Skip Jester",
			activeConfig.BossRush.Mission12.skipJester,
			queuedConfig.BossRush.Mission12.skipJester
		);
		GUI_Checkbox2
		(
			"Skip Geryon Part 1",
			activeConfig.BossRush.Mission12.skipGeryonPart1,
			queuedConfig.BossRush.Mission12.skipGeryonPart1
		);
		GUI_SectionEnd();
		ImGui::Text("");

		GUI_SectionStart("Mission 17");
		GUI_Checkbox2
		(
			"Skip Jester",
			activeConfig.BossRush.Mission17.skipJester,
			queuedConfig.BossRush.Mission17.skipJester
		);
		GUI_SectionEnd();
		ImGui::Text("");

		GUI_SectionStart("Mission 19");
		GUI_Checkbox2
		(
			"Skip Arkham Part 1",
			activeConfig.BossRush.Mission19.skipArkhamPart1,
			queuedConfig.BossRush.Mission19.skipArkhamPart1
		);

		ImGui::Text("");
	}
}

void Camera()
{
	if (ImGui::CollapsingHeader("Camera"))
	{
		ImGui::Text("");

		if
		(
			GUI_Checkbox2
			(
				"Invert X",
				activeConfig.Camera.invertX,
				queuedConfig.Camera.invertX
			)
		)
		{
			Camera_ToggleInvertX(activeConfig.Camera.invertX);
		}

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

void Color_UpdateValues()
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

		if (GUI_ResetButton())
		{
			memcpy
			(
				&queuedConfig.Color,
				&defaultConfig.Color,
				sizeof(Config::Color)
			);
			memcpy
			(
				&activeConfig.Color,
				&queuedConfig.Color,
				sizeof(Config::Color)
			);

			Color_UpdateValues();

			activeConfig.BeowulfDante.hide  = queuedConfig.BeowulfDante.hide  = defaultConfig.BeowulfDante.hide;
			activeConfig.BeowulfVergil.hide = queuedConfig.BeowulfVergil.hide = defaultConfig.BeowulfVergil.hide;
			activeConfig.noDevilForm        = queuedConfig.noDevilForm        = defaultConfig.noDevilForm;
		}
		GUI_SectionEnd();
		ImGui::Text("");

		ImGui::Text("Color");
		ImGui::SameLine();
		TooltipHelper
		(
			"(?)",
			"Requires Actor module."
		);
		ImGui::Text("");

		if (GUI_ResetButton())
		{
			memcpy
			(
				&queuedConfig.Color,
				&defaultConfig.Color,
				sizeof(Config::Color)
			);
			memcpy
			(
				&activeConfig.Color,
				&queuedConfig.Color,
				sizeof(Config::Color)
			);

			Color_UpdateValues();
		}
		ImGui::Text("");

		GUI_ColorPalette2
		(
			"Air Hike",
			activeConfig.Color.airHike,
			queuedConfig.Color.airHike,
			Color.airHike
		);
		ImGui::Text("");

		ImGui::Text("Trickster");
		GUI_Color2
		(
			"Sky Star",
			activeConfig.Color.Trickster.skyStar,
			queuedConfig.Color.Trickster.skyStar,
			Color.Trickster.skyStar
		);
		ImGui::Text("");

		ImGui::Text("Royalguard");
		GUI_Color2
		(
			"Ultimate",
			activeConfig.Color.Royalguard.ultimate,
			queuedConfig.Color.Royalguard.ultimate,
			Color.Royalguard.ultimate
		);
		ImGui::Text("");

		ImGui::Text("Doppelganger");
		GUI_Color2
		(
			"Clone",
			activeConfig.Color.Doppelganger.clone,
			queuedConfig.Color.Doppelganger.clone,
			Color.Doppelganger.clone
		);
		ImGui::Text("");

		ImGui::Text("Aura");
		GUI_ColorPalette2
		(
			"Dante",
			activeConfig.Color.Aura.dante,
			queuedConfig.Color.Aura.dante,
			Color.Aura.dante
		);
		GUI_Color2
		(
			"Sparda",
			activeConfig.Color.Aura.sparda,
			queuedConfig.Color.Aura.sparda,
			Color.Aura.sparda
		);
		GUI_ColorPalette2
		(
			"Vergil",
			activeConfig.Color.Aura.vergil,
			queuedConfig.Color.Aura.vergil,
			Color.Aura.vergil
		);
		GUI_Color2
		(
			"Nero Angelo",
			activeConfig.Color.Aura.neroAngelo,
			queuedConfig.Color.Aura.neroAngelo,
			Color.Aura.neroAngelo
		);
		GUI_SectionEnd();
		ImGui::Text("");

		ImGui::Text("Other");
		ImGui::SameLine();
		TooltipHelper
		(
			"(?)",
			"Requires Actor module."
		);
		ImGui::Text("");

		GUI_Checkbox2
		(
			"Hide Beowulf Dante",
			activeConfig.BeowulfDante.hide,
			queuedConfig.BeowulfDante.hide
		);
		GUI_Checkbox2
		(
			"Hide Beowulf Vergil",
			activeConfig.BeowulfVergil.hide,
			queuedConfig.BeowulfVergil.hide
		);
		GUI_Checkbox2
		(
			"No Devil Form",
			activeConfig.noDevilForm,
			queuedConfig.noDevilForm
		);

		ImGui::Text("");
	}
}

template <typename T>
void ActionData
(
	const char * label,
	T(&vars)[2],
	T(&vars2)[2],
	T(&defaultVars)[2],
	T step = 1,
	const char * format = 0,
	ImGuiInputTextFlags flags = 0,
	float32 width = 150
)
{
	auto & style = ImGui::GetStyle();

	ImGui::PushItemWidth(width);
	GUI_InputDefault2
	(
		"",
		vars[0],
		vars2[0],
		defaultVars[0],
		step,
		format,
		flags
	);
	ImGui::SameLine(0, style.ItemInnerSpacing.x);
	GUI_InputDefault2
	(
		label,
		vars[1],
		vars2[1],
		defaultVars[1],
		step,
		format,
		flags
	);
	ImGui::PopItemWidth();
}

void Dante()
{
	if (ImGui::CollapsingHeader("Dante"))
	{
		ImGui::Text("");
		if (GUI_ResetButton())
		{
		}
		GUI_SectionEnd();
		ImGui::Text("");

		ImGui::Text("Air Hike");
		ImGui::SameLine();
		TooltipHelper
		(
			"(?)",
			"Requires Actor module."
		);
		ImGui::Text("");

		if
		(
			GUI_Checkbox2
			(
				"Core Ability",
				activeConfig.AirHike.coreAbility,
				queuedConfig.AirHike.coreAbility
			)
		)
		{
			//Dante_AirHike_ToggleCoreAbility(activeConfig.AirHike.coreAbility);



		}




		ImGui::Text("");
		ActionData<uint8>
		(
			"Count",
			activeConfig.AirHike.count,
			queuedConfig.AirHike.count,
			defaultConfig.AirHike.count
		);
		GUI_SectionEnd();
		ImGui::Text("");

		//GUI_SectionStart("Trickster");


		ImGui::Text("Trickster");
		ImGui::SameLine();
		TooltipHelper
		(
			"(?)",
			"Requires Actor module."
		);
		ImGui::Text("");



		ActionData<uint8>
		(
			"Dash Count",
			activeConfig.Trickster.dashCount,
			queuedConfig.Trickster.dashCount,
			defaultConfig.Trickster.dashCount
		);
		ActionData<uint8>
		(
			"Sky Star Count",
			activeConfig.Trickster.skyStarCount,
			queuedConfig.Trickster.skyStarCount,
			defaultConfig.Trickster.skyStarCount
		);
		ActionData<uint8>
		(
			"Air Trick Count",
			activeConfig.Trickster.airTrickCount,
			queuedConfig.Trickster.airTrickCount,
			defaultConfig.Trickster.airTrickCount
		);
		GUI_SectionEnd();
		ImGui::Text("");

		GUI_SectionStart("Rebellion");
		GUI_Checkbox2
		(
			"Infinite Sword Pierce",
			activeConfig.Rebellion.infiniteSwordPierce,
			queuedConfig.Rebellion.infiniteSwordPierce
		);
		// ImGui::Text("");
		// ActionData<float32>("Stinger Duration"    , activeConfig.Rebellion.stingerDuration   , defaultConfig.Rebellion.stingerDuration   , 1 , "%.0f");
		// ActionData<float32>("Stinger Range"       , activeConfig.Rebellion.stingerRange      , defaultConfig.Rebellion.stingerRange      , 10, "%.0f");
		// ActionData<float32>("Air Stinger Duration", activeConfig.Rebellion.airStingerDuration, defaultConfig.Rebellion.airStingerDuration, 1 , "%.0f");
		// ActionData<float32>("Air Stinger Range"   , activeConfig.Rebellion.airStingerRange   , defaultConfig.Rebellion.airStingerRange   , 10, "%.0f");
		GUI_SectionEnd();
		ImGui::Text("");

		// GUI_SectionStart("Agni & Rudra");
		// ActionData<float32>("Jet-Stream Duration", activeConfig.AgniRudra.jetStreamDuration, defaultConfig.AgniRudra.jetStreamDuration, 1 , "%.0f");
		// ActionData<float32>("Jet-Stream Range"   , activeConfig.AgniRudra.jetStreamRange   , defaultConfig.AgniRudra.jetStreamRange   , 10, "%.0f");
		// GUI_SectionEnd();

		// GUI_SectionStart("Nevan");
		// ActionData<float32>("Reverb Shock Duration", activeConfig.Nevan.reverbShockDuration, defaultConfig.Nevan.reverbShockDuration, 1 , "%.0f");
		// ActionData<float32>("Reverb Shock Range"   , activeConfig.Nevan.reverbShockRange   , defaultConfig.Nevan.reverbShockRange   , 10, "%.0f");
		// GUI_SectionEnd();

		// GUI_SectionStart("Beowulf");
		// ActionData<float32>("Straight Duration"    , activeConfig.BeowulfDante.straightDuration   , defaultConfig.BeowulfDante.straightDuration   , 1 , "%.0f");
		// ActionData<float32>("Straight Range"       , activeConfig.BeowulfDante.straightRange      , defaultConfig.BeowulfDante.straightRange      , 10, "%.0f");
		// ActionData<float32>("Air Straight Duration", activeConfig.BeowulfDante.airStraightDuration, defaultConfig.BeowulfDante.airStraightDuration, 1 , "%.0f");
		// ActionData<float32>("Air Straight Range"   , activeConfig.BeowulfDante.airStraightRange   , defaultConfig.BeowulfDante.airStraightRange   , 10, "%.0f");
		// GUI_SectionEnd();

		GUI_SectionStart("Ebony & Ivory");
		GUI_Checkbox("Foursome Time", activeConfig.EbonyIvory.foursomeTime);
		GUI_Checkbox("Infinite Rain Storm", activeConfig.EbonyIvory.infiniteRainStorm);
		GUI_SectionEnd();
		ImGui::Text("");

		// GUI_SectionStart("Shotgun");
		// ActionData<float32>("Gun Stinger Duration"    , activeConfig.Shotgun.gunStingerDuration   , defaultConfig.Shotgun.gunStingerDuration   , 1 , "%.0f");
		// ActionData<float32>("Gun Stinger Range"       , activeConfig.Shotgun.gunStingerRange      , defaultConfig.Shotgun.gunStingerRange      , 10, "%.0f");
		// ActionData<float32>("Air Gun Stinger Duration", activeConfig.Shotgun.airGunStingerDuration, defaultConfig.Shotgun.airGunStingerDuration, 1 , "%.0f");
		// ActionData<float32>("Air Gun Stinger Range"   , activeConfig.Shotgun.airGunStingerRange   , defaultConfig.Shotgun.airGunStingerRange   , 10, "%.0f");
		// GUI_SectionEnd();

		GUI_SectionStart("Artemis");
		GUI_Checkbox("Swap Normal Shot and Multi Lock", activeConfig.Artemis.swapNormalShotAndMultiLock);
		GUI_Checkbox("Instant Full Charge", activeConfig.Artemis.instantFullCharge);
		ImGui::Text("");
	}
}

void Debug()
{
	if (ImGui::CollapsingHeader("Debug"))
	{
		ImGui::Text("");
		IntroduceSessionData();
		GUI_Checkbox("One Hit Kill", sessionData.oneHitKill);
		ImGui::Text("");

		auto PlayTrack = [](const char * filename)
		{
			func_32BE20((appBaseAddr + 0xCF3700));
			func_32BA90((appBaseAddr + 0xCF3708), filename, 0, 0);
		};

		static char buffer[512] = { "afs/sound/Battle_00.ogg" };
		static char filename[256] = { "Battle_00.ogg" };

		ImGui::PushItemWidth(200);
		if (ImGui::InputText("Filename", filename, sizeof(filename)))
		{
			snprintf(buffer, sizeof(buffer), "afs/sound/%s", filename);
		}
		ImGui::PopItemWidth();

		if (GUI_Button("Play Track"))
		{
			PlayTrack(buffer);
		}
		ImGui::Text("");
	}
}

void Other()
{
	if (ImGui::CollapsingHeader("Other"))
	{
		ImGui::Text("");
		if (GUI_ResetButton())
		{
			activeConfig.MagicPointsDepletionValues.quicksilver  = queuedConfig.MagicPointsDepletionValues.quicksilver  = defaultConfig.MagicPointsDepletionValues.quicksilver;
			activeConfig.MagicPointsDepletionValues.doppelganger = queuedConfig.MagicPointsDepletionValues.doppelganger = defaultConfig.MagicPointsDepletionValues.doppelganger;
			activeConfig.MagicPointsDepletionValues.devil        = queuedConfig.MagicPointsDepletionValues.devil        = defaultConfig.MagicPointsDepletionValues.devil;
			activeConfig.crazyComboLevelMultiplier               = queuedConfig.crazyComboLevelMultiplier               = defaultConfig.crazyComboLevelMultiplier;
			activeConfig.weaponSwitchTimeout                     = queuedConfig.weaponSwitchTimeout                     = defaultConfig.weaponSwitchTimeout;
			activeConfig.orbReach                                = queuedConfig.orbReach                                = defaultConfig.orbReach;

			UpdateMagicPointsDepletionValues();
			UpdateOrbReach();
		}
		GUI_SectionEnd();
		ImGui::Text("");

		GUI_SectionStart("Magic Points Depletion Rate");
		ImGui::PushItemWidth(150);
		if
		(
			GUI_InputDefault2
			(
				"Quicksilver",
				activeConfig.MagicPointsDepletionValues.quicksilver,
				queuedConfig.MagicPointsDepletionValues.quicksilver,
				defaultConfig.MagicPointsDepletionValues.quicksilver,
				1.0f,
				"%.1f"
			)
		)
		{
			UpdateMagicPointsDepletionValues();
		}
		if
		(
			GUI_InputDefault2
			(
				"Doppelganger",
				activeConfig.MagicPointsDepletionValues.doppelganger,
				queuedConfig.MagicPointsDepletionValues.doppelganger,
				defaultConfig.MagicPointsDepletionValues.doppelganger,
				1.0f,
				"%.1f"
			)
		)
		{
			UpdateMagicPointsDepletionValues();
		}
		if
		(
			GUI_InputDefault2
			(
				"Devil",
				activeConfig.MagicPointsDepletionValues.devil,
				queuedConfig.MagicPointsDepletionValues.devil,
				defaultConfig.MagicPointsDepletionValues.devil,
				1.0f,
				"%.1f"
			)
		)
		{
			UpdateMagicPointsDepletionValues();
		}
		ImGui::PopItemWidth();
		GUI_SectionEnd();
		ImGui::Text("");

		ImGui::PushItemWidth(150);
		GUI_InputDefault2
		(
			"Crazy Combo Level Multiplier",
			activeConfig.crazyComboLevelMultiplier,
			queuedConfig.crazyComboLevelMultiplier,
			defaultConfig.crazyComboLevelMultiplier
		);
		GUI_InputDefault2
		(
			"Weapon Switch Timeout",
			activeConfig.weaponSwitchTimeout,
			queuedConfig.weaponSwitchTimeout,
			defaultConfig.weaponSwitchTimeout,
			1.0f,
			"%.0f"
		);
		if
		(
			GUI_InputDefault2
			(
				"Orb Reach",
				activeConfig.orbReach,
				queuedConfig.orbReach,
				defaultConfig.orbReach,
				100.0f,
				"%.0f"
			)
		)
		{
			UpdateOrbReach();
		}
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

const char * RemoveBusyFlag_buttonNames[] =
{
	"Left Trigger",
	"Right Trigger",
	"Left Shoulder",
	"Right Shoulder",
	"Y",
	"B",
	"A",
	"X",
	"Back",
	"Left Thumb",
	"Right Thumb",
	"Start",
	"Up",
	"Right",
	"Down",
	"Left",
};

byte16 RemoveBusyFlag_buttonMap[] =
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

uint8 RemoveBusyFlag_buttonIndex = 0;

void RemoveBusyFlag_UpdateIndices()
{
	UpdateMapIndex
	(
		RemoveBusyFlag_buttonMap,
		RemoveBusyFlag_buttonIndex,
		activeConfig.RemoveBusyFlag.button
	);
}

void RemoveBusyFlag()
{
	if (ImGui::CollapsingHeader("Remove Busy Flag"))
	{
		ImGui::Text("");

		GUI_Checkbox2
		(
			"Enable",
			activeConfig.RemoveBusyFlag.enable,
			queuedConfig.RemoveBusyFlag.enable
		);
		ImGui::Text("");

		if (GUI_ResetButton())
		{
			memcpy
			(
				&queuedConfig.RemoveBusyFlag,
				&defaultConfig.RemoveBusyFlag,
				sizeof(Config::RemoveBusyFlag)
			);
			memcpy
			(
				&activeConfig.RemoveBusyFlag,
				&queuedConfig.RemoveBusyFlag,
				sizeof(Config::RemoveBusyFlag)
			);

			RemoveBusyFlag_UpdateIndices();
		}
		ImGui::Text("");

		ImGui::PushItemWidth(150);
		GUI_ComboMap2
		(
			"Button",
			RemoveBusyFlag_buttonNames,
			RemoveBusyFlag_buttonMap,
			RemoveBusyFlag_buttonIndex,
			activeConfig.RemoveBusyFlag.button,
			queuedConfig.RemoveBusyFlag.button,
			ImGuiComboFlags_HeightLargest
		);
		ImGui::PopItemWidth();

		ImGui::Text("");
	}
}

const char * ResetPermissions_buttonNames[] =
{
	"Left Trigger",
	"Right Trigger",
	"Left Shoulder",
	"Right Shoulder",
	"Y",
	"B",
	"A",
	"X",
	"Back",
	"Left Thumb",
	"Right Thumb",
	"Start",
	"Up",
	"Right",
	"Down",
	"Left",
};

byte16 ResetPermissions_buttonMap[] =
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

uint8 ResetPermissions_buttonIndex = 0;

void ResetPermissions_UpdateIndices()
{
	UpdateMapIndex
	(
		ResetPermissions_buttonMap,
		ResetPermissions_buttonIndex,
		activeConfig.ResetPermissions.button
	);
}

void ResetPermissions()
{
	if (ImGui::CollapsingHeader("Reset Permissions"))
	{
		ImGui::Text("");

		GUI_Checkbox2
		(
			"Enable",
			activeConfig.ResetPermissions.enable,
			queuedConfig.ResetPermissions.enable
		);
		ImGui::Text("");

		if (GUI_ResetButton())
		{
			memcpy
			(
				&queuedConfig.ResetPermissions,
				&defaultConfig.ResetPermissions,
				sizeof(Config::ResetPermissions)
			);
			memcpy
			(
				&activeConfig.ResetPermissions,
				&queuedConfig.ResetPermissions,
				sizeof(Config::ResetPermissions)
			);

			ResetPermissions_UpdateIndices();
		}
		ImGui::Text("");

		ImGui::PushItemWidth(150);
		GUI_ComboMap2
		(
			"Button",
			ResetPermissions_buttonNames,
			ResetPermissions_buttonMap,
			ResetPermissions_buttonIndex,
			activeConfig.ResetPermissions.button,
			queuedConfig.ResetPermissions.button,
			ImGuiComboFlags_HeightLargest
		);
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
		GUI_ResetButton();
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

// void StyleSwitchController()
// {
// 	if (ImGui::CollapsingHeader("Style Switch Controller"))
// 	{
// 		ImGui::Text("");

// 		GUI_Checkbox("No Double Tap", activeConfig.StyleSwitchController.noDoubleTap);

// 		ImGui::Text("");
// 	}
// }

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
		//GUI_ResetButton();
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

		if (GUI_ResetButton())
		{
			memcpy
			(
				&queuedConfig.DarkSlayer,
				&defaultConfig.DarkSlayer,
				sizeof(Config::DarkSlayer)
			);
			memcpy
			(
				&activeConfig.DarkSlayer,
				&queuedConfig.DarkSlayer,
				sizeof(Config::DarkSlayer)
			);

			activeConfig.YamatoForceEdge.infiniteRoundTrip = queuedConfig.YamatoForceEdge.infiniteRoundTrip = defaultConfig.YamatoForceEdge.infiniteRoundTrip;

			ToggleYamatoForceEdgeInfiniteRoundTrip(activeConfig.YamatoForceEdge.infiniteRoundTrip);

			activeConfig.SummonedSwords.chronoSwords = queuedConfig.SummonedSwords.chronoSwords = defaultConfig.SummonedSwords.chronoSwords;

			ToggleChronoSwords(activeConfig.SummonedSwords.chronoSwords);
		}
		ImGui::Text("");

		ImGui::Text("Dark Slayer");
		ImGui::SameLine();
		TooltipHelper
		(
			"(?)",
			"Requires Actor module."
		);
		ImGui::Text("");


		ActionData<uint8>
		(
			"Air Trick Count",
			activeConfig.DarkSlayer.airTrickCount,
			queuedConfig.DarkSlayer.airTrickCount,
			defaultConfig.DarkSlayer.airTrickCount
		);
		ActionData<uint8>
		(
			"Trick Up Count",
			activeConfig.DarkSlayer.trickUpCount,
			queuedConfig.DarkSlayer.trickUpCount,
			defaultConfig.DarkSlayer.trickUpCount
		);
		ActionData<uint8>
		(
			"Trick Down Count",
			activeConfig.DarkSlayer.trickDownCount,
			queuedConfig.DarkSlayer.trickDownCount,
			defaultConfig.DarkSlayer.trickDownCount
		);
		GUI_SectionEnd();
		ImGui::Text("");

		// GUI_SectionStart("Yamato");
		// ActionData<float32>("Rapid Slash Duration", activeConfig.Yamato.rapidSlashDuration, defaultConfig.Yamato.rapidSlashDuration, 1 , "%.0f");
		// ActionData<float32>("Rapid Slash Range"   , activeConfig.Yamato.rapidSlashRange   , defaultConfig.Yamato.rapidSlashRange   , 10, "%.0f");
		// ActionData<float32>("Judgement Cut Count" , activeConfig.Yamato.judgementCutCount , defaultConfig.Yamato.judgementCutCount , 1 , "%.0f");
		// ActionData<float32>("Judgement Cut Range" , activeConfig.Yamato.judgementCutRange , defaultConfig.Yamato.judgementCutRange , 10, "%.0f");
		// GUI_SectionEnd();

		//GUI_SectionStart("Beowulf");
		////GUI_Checkbox("Hide", activeConfig.Beowulf.hide);
		////ImGui::Text("");
		//ActionData<float32>("Rising Sun Height", activeConfig.Beowulf.risingSunHeight, defaultConfig.Beowulf.risingSunHeight, 1 , "%.0f");
		//GUI_SectionEnd();

		GUI_SectionStart("Yamato & Force Edge");
		if
		(
			GUI_Checkbox2
			(
				"Infinite Round Trip",
				activeConfig.YamatoForceEdge.infiniteRoundTrip,
				queuedConfig.YamatoForceEdge.infiniteRoundTrip
			)
		)
		{
			ToggleYamatoForceEdgeInfiniteRoundTrip(activeConfig.YamatoForceEdge.infiniteRoundTrip);
		}
		// ImGui::Text("");
		// ActionData<float32>("Stinger Duration"    , activeConfig.YamatoForceEdge.stingerDuration   , defaultConfig.YamatoForceEdge.stingerDuration   , 1 , "%.0f");
		// ActionData<float32>("Stinger Range"       , activeConfig.YamatoForceEdge.stingerRange      , defaultConfig.YamatoForceEdge.stingerRange      , 10, "%.0f");
		// ActionData<float32>("Air Stinger Duration", activeConfig.YamatoForceEdge.airStingerDuration, defaultConfig.YamatoForceEdge.airStingerDuration, 1 , "%.0f");
		// ActionData<float32>("Air Stinger Range"   , activeConfig.YamatoForceEdge.airStingerRange   , defaultConfig.YamatoForceEdge.airStingerRange   , 10, "%.0f");
		GUI_SectionEnd();
		ImGui::Text("");

		GUI_SectionStart("Summoned Swords");
		if
		(
			GUI_Checkbox2
			(
				"Chrono Swords",
				activeConfig.SummonedSwords.chronoSwords,
				queuedConfig.SummonedSwords.chronoSwords
			)
		)
		{
			ToggleChronoSwords(activeConfig.SummonedSwords.chronoSwords);
		}

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

		Actor();
		Arcade();
		BossRush();
		Camera();
		Cosmetics();
		Dante();

		if constexpr (debug)
		{
			Debug();
		}

		Other();
		Repair();
		RemoveBusyFlag();
		ResetPermissions();
		Speed();
		System();
		Teleporter();
		Training();
		Vergil();

		ImGui::Text("");
	}
	ImGui::End();
}

export void GUI_Render()
{
	GUI_id = 0;

	if constexpr (debug)
	{
		Overlay();
	}

	if (pause)
	{
		Main();
	}

	auto TimeoutFunction = [&]()
	{
		auto & save        = GUI_save;
		auto & saveTimeout = GUI_saveTimeout;

		if (saveTimeout > 0)
		{
			saveTimeout -= 1.0f;
		}
		else if (saveTimeout < 0)
		{
			saveTimeout = 0;
		}

		if (save)
		{
			if (saveTimeout > 0)
			{
				return;
			}

			save = false;

			saveTimeout = 6;

			SaveConfig();
		}
	};

	TimeoutFunction();
}

export void GUI_Init()
{
	BuildFonts();

	Actor_UpdateIndices();
	Arcade_UpdateIndices();
	Color_UpdateValues();
	RemoveBusyFlag_UpdateIndices();
	ResetPermissions_UpdateIndices();
}

#ifdef __GARBAGE__
#endif
