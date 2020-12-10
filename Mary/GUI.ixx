// @Todo: Update all sizeof(Config::X)!
// @Todo: Add Jukebox.
// @Todo: Add ResetButton to Graphics.
// @Todo: Actor reset doesn't trigger Actor_Toggle.

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
import FMOD;
import Global;
import Graphics;
import Internal;
import Model;
import Other;
import Scene;
import Sound;
import Speed;
import Training;
import Window;

#define debug false


















const char * buttonNames[] =
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

byte16 buttons[] =
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

const char * playerNames[MAX_PLAYER] =
{
	"Player 1",
	"Player 2",
	"Player 3",
	"Player 4",
};

const char * entityNames[MAX_ENTITY] =
{
	"Main",
	"Clone",
};

const char * directionNames[MAX_DIRECTION] =
{
	"Up",
	"Right",
	"Down",
	"Left",
};

const char * characterNames[] =
{
	"Dante",
	"Bob",
	"Lady",
	"Vergil",
};

const char * styleNamesDante[] =
{
	"Swordmaster",
	"Gunslinger",
	"Trickster",
	"Royalguard",
	"Quicksilver",
	"Doppelganger",
};

uint8 stylesDante[] =
{
	STYLE_SWORDMASTER,
	STYLE_GUNSLINGER,
	STYLE_TRICKSTER,
	STYLE_ROYALGUARD,
	STYLE_QUICKSILVER,
	STYLE_DOPPELGANGER,
};

const char * styleNamesVergil[] =
{
	"Dark Slayer",
	"Quicksilver",
	"Doppelganger",
};

uint8 stylesVergil[] =
{
	STYLE_DARK_SLAYER,
	STYLE_QUICKSILVER,
	STYLE_DOPPELGANGER,
};













const char * meleeWeaponNamesDante[] =
{
	"Rebellion",
	"Cerberus",
	"Agni & Rudra",
	"Nevan",
	"Beowulf",
};

uint8 meleeWeaponsDante[] =
{
	WEAPON_REBELLION,
	WEAPON_CERBERUS,
	WEAPON_AGNI_RUDRA,
	WEAPON_NEVAN,
	WEAPON_BEOWULF_DANTE,
};

const char * meleeWeaponNamesVergil[] =
{
	"Yamato",
	"Beowulf",
	"Yamato & Force Edge",
};

uint8 meleeWeaponsVergil[] =
{
	WEAPON_YAMATO_VERGIL,
	WEAPON_BEOWULF_VERGIL,
	WEAPON_YAMATO_FORCE_EDGE,
};

const char * rangedWeaponNamesDante[] =
{
	"Ebony & Ivory",
	"Shotgun",
	"Artemis",
	"Spiral",
	"Kalina Ann",
};

uint8 rangedWeaponsDante[] =
{
	WEAPON_EBONY_IVORY,
	WEAPON_SHOTGUN,
	WEAPON_ARTEMIS,
	WEAPON_SPIRAL,
	WEAPON_KALINA_ANN,
};

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

uint32 modes[] =
{
	MODE_EASY,
	MODE_NORMAL,
	MODE_HARD,
	MODE_VERY_HARD,
	MODE_DANTE_MUST_DIE,
	MODE_HARD,
};

const char * floorNames[] =
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












#pragma region Overlay

// @Todo: Update.
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

		ImGui::Text("%.2f FPS", (ImGui::GetIO().Framerate));

		ImGui::Text("g_scene %u", g_scene);

		[&]()
		{
			if (!InGame())
			{
				return;
			}

			IntroduceEventData(return);

			ImGui::Text("%u", eventData.room);
			ImGui::Text("%u", eventData.position);
		}();

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



// @Todo: Update.
// bool Overlay_enable = true;
// bool Overlay_run = false;
// ImVec2 Overlay_size = ImVec2(300, 300);

void Overlay2()
{
	static bool run = false;
	if (!run)
	{
		run = true;
		ImGui::SetNextWindowSize(ImVec2((300 + 16), (300 + 16)));
		ImGui::SetNextWindowPos(ImVec2(200, 0));
	}
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(1, 1));
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));
	if (ImGui::Begin("GUI_Overlay2", &Overlay_enable, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize))
	{
		auto & io = ImGui::GetIO();
		ImGui::PushFont(io.Fonts->Fonts[FONT_OVERLAY_16]);
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 0, 0, 1));


		ImGui::Text("Memory Data");
		ImGui::Text("pos   %u", memoryData.pos);
		ImGui::Text("end   %u", memoryData.end);
		ImGui::Text("count %u", memoryData.count);
		ImGui::Text("");

		ImGui::Text("Backup Helper");
		ImGui::Text("pos   %u", backupHelper.pos);
		ImGui::Text("end   %u", backupHelper.end);
		ImGui::Text("count %u", backupHelper.count);
		ImGui::Text("");








		ImGui::Text("Actor");

		for_all(uint32, index, Actor_actorBaseAddr.count)
		{
			ImGui::Text("%.4u %.16llX", index, Actor_actorBaseAddr[index]);
		}

		if (Actor_actorBaseAddr.count > 0)
		{
			ImGui::Text("");
		}

		// //for_all(uint8, player, MAX_PLAYER)
		// {
		// 	constexpr uint8 player = 0;

		// 	for_all(uint8, direction, MAX_DIRECTION)
		// 	{
		// 		ImGui::Text("%.4u %.16llX", direction, g_actorBaseAddr[player][direction]);
		// 	}

		// 	auto & character       = g_character      [player];
		// 	auto & lastCharacter   = g_lastCharacter  [player];
		// 	auto & activeCharacter = g_activeCharacter[player];
		// 	auto & executeFunction = g_executeFunction[player];

		// 	ImGui::Text("character        %u", character      );
		// 	ImGui::Text("lastCharacter    %u", lastCharacter  );
		// 	ImGui::Text("activeCharacter  %u", activeCharacter);

		// 	for_all(uint8, direction, MAX_DIRECTION)
		// 	{
		// 		auto & executeButton = g_executeButton[player][direction];

		// 		ImGui::Text("executeButton[%u] %u", direction, executeButton );
		// 	}

		// 	ImGui::Text("executeFunction  %u", executeFunction);
		// }




		ImGui::PopStyleColor();
		ImGui::PopFont();
	}
	ImGui::End();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar(3);
}




void MissionOverlay()
{
	if (!activeConfig.MissionOverlay.enable)
	{
		return;
	}

	static bool run = false;
	if (!run)
	{
		run = true;

		ImGui::SetNextWindowSize
		(
			ImVec2
			(
				(300.0f + 16.0f),
				(300.0f + 16.0f)
			)
		);
		ImGui::SetNextWindowPos
		(
			ImVec2
			(
				static_cast<float>(activeConfig.MissionOverlay.x),
				static_cast<float>(activeConfig.MissionOverlay.y)
			)
		);
	}
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(1, 1));
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));
	if
	(
		ImGui::Begin
		(
			"GUI_MissionOverlay",
			&activeConfig.MissionOverlay.enable,
			ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize
		)
	)
	{
		{
			auto pos = ImGui::GetWindowPos();

			auto x = static_cast<uint32>(pos.x);
			auto y = static_cast<uint32>(pos.y);

			if
			(
				(activeConfig.MissionOverlay.x != x) ||
				(activeConfig.MissionOverlay.y != y)
			)
			{
				activeConfig.MissionOverlay.x = queuedConfig.MissionOverlay.x = x;
				activeConfig.MissionOverlay.y = queuedConfig.MissionOverlay.y = y;

				GUI_save = true;
			}
		}

		auto & io = ImGui::GetIO();

		ImGui::PushFont(io.Fonts->Fonts[FONT_OVERLAY_16]);

		ImGui::PushStyleColor
		(
			ImGuiCol_Text,
			*reinterpret_cast<ImVec4 *>(&activeConfig.MissionOverlay.color)
		);

		ImGui::Text("Mission");

		[&]()
		{
			IntroduceMissionData(return);

			auto timeData = TimeData
			(
				static_cast<float>(missionData.frameCount),
				60.0f
			);






			ImGui::Text
			(
				"Time           %02u:%02u:%02u.%03u",
				timeData.hours,
				timeData.minutes,
				timeData.seconds,
				timeData.milliseconds
			);
			ImGui::Text("Damage         %u", missionData.damage);
			ImGui::Text("Orbs Collected %u", missionData.orbsCollected);
			ImGui::Text("Items Used     %u", missionData.itemsUsed);
			ImGui::Text("Kill Count     %u", missionData.killCount);

			auto pool = *reinterpret_cast<byte8 ***>(appBaseAddr + 0xC90E28);
			if (!pool)
			{
				return;
			}

			IntroduceActorData(actorBaseAddr, actorData, pool[3], return);

			auto stylePoints = (actorData.styleData.quotient * 100.0f);

			ImGui::Text("Style Points   %.2f", stylePoints);
		}();

		ImGui::PopStyleColor();
		ImGui::PopFont();
	}
	ImGui::End();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar(3);
}

































#pragma endregion

#pragma region Actor

const char * Actor_playerTabNames[PLAYER_COUNT] =
{
	"Player 1",
	"Player 2",
	"Player 3",
	"Player 4",
};

#define Actor_buttonNames buttonNames
#define Actor_buttons buttons

uint8 Actor_buttonIndices[PLAYER_COUNT] = {};

const char * Actor_characterTabNames[CHARACTER_COUNT] =
{
	"Character 1",
	"Character 2",
	"Character 3",
};

#define Actor_entityNames entityNames

#define Actor_characterNames characterNames

#define Actor_styleButtonNames buttonNames
#define Actor_styleButtons buttons

uint8 Actor_styleButtonIndices[PLAYER_COUNT][CHARACTER_COUNT][ENTITY_COUNT][STYLE_COUNT] = {};

#define Actor_styleNamesDante styleNamesDante
#define Actor_stylesDante stylesDante

#define Actor_styleNamesVergil styleNamesVergil
#define Actor_stylesVergil stylesVergil

uint8 Actor_styleIndices[PLAYER_COUNT][CHARACTER_COUNT][ENTITY_COUNT][STYLE_COUNT][2] = {};

#define Actor_meleeWeaponNamesDante meleeWeaponNamesDante
#define Actor_meleeWeaponsDante meleeWeaponsDante
#define Actor_meleeWeaponNamesVergil meleeWeaponNamesVergil
#define Actor_meleeWeaponsVergil meleeWeaponsVergil

uint8 Actor_meleeWeaponIndices[PLAYER_COUNT][CHARACTER_COUNT][ENTITY_COUNT][MELEE_WEAPON_COUNT] = {};

#define Actor_rangedWeaponNamesDante rangedWeaponNamesDante
#define Actor_rangedWeaponsDante rangedWeaponsDante

uint8 Actor_rangedWeaponIndices[PLAYER_COUNT][CHARACTER_COUNT][ENTITY_COUNT][RANGED_WEAPON_COUNT] = {};

void Actor_UpdateIndices()
{
	LogFunction();

	for_all(uint8, playerIndex, PLAYER_COUNT)
	{
		auto & playerData = GetPlayerData(playerIndex);

		UpdateMapIndex
		(
			Actor_buttons,
			Actor_buttonIndices[playerIndex],
			playerData.button
		);

		for_all(uint8, characterIndex, CHARACTER_COUNT){
		for_all(uint8, entityIndex   , ENTITY_COUNT   )
		{
			auto & characterData = GetCharacterData
			(
				playerIndex,
				characterIndex,
				entityIndex
			);

			for_all(uint8, styleIndex, STYLE_COUNT)
			{
				UpdateMapIndex
				(
					Actor_styleButtons,
					Actor_styleButtonIndices[playerIndex][characterIndex][entityIndex][styleIndex],
					characterData.styleButtons[styleIndex]
				);

				switch (characterData.character)
				{
					case CHAR_DANTE:
					{
						UpdateMapIndex
						(
							Actor_stylesDante,
							Actor_styleIndices[playerIndex][characterIndex][entityIndex][styleIndex][0],
							characterData.styles[styleIndex][0]
						);
						UpdateMapIndex
						(
							Actor_stylesDante,
							Actor_styleIndices[playerIndex][characterIndex][entityIndex][styleIndex][1],
							characterData.styles[styleIndex][1]
						);

						break;
					}
					case CHAR_VERGIL:
					{
						UpdateMapIndex
						(
							Actor_stylesVergil,
							Actor_styleIndices[playerIndex][characterIndex][entityIndex][styleIndex][0],
							characterData.styles[styleIndex][0]
						);
						UpdateMapIndex
						(
							Actor_stylesVergil,
							Actor_styleIndices[playerIndex][characterIndex][entityIndex][styleIndex][1],
							characterData.styles[styleIndex][1]
						);

						break;
					}
				}
			}

			if (characterData.character != CHAR_DANTE)
			{
				continue;
			}

			for_all(uint8, meleeWeaponIndex, MELEE_WEAPON_COUNT_DANTE)
			{
				UpdateMapIndex
				(
					Actor_meleeWeaponsDante,
					Actor_meleeWeaponIndices[playerIndex][characterIndex][entityIndex][meleeWeaponIndex],
					characterData.meleeWeapons[meleeWeaponIndex]
				);
			}

			for_all(uint8, rangedWeaponIndex, RANGED_WEAPON_COUNT_DANTE)
			{
				UpdateMapIndex
				(
					Actor_rangedWeaponsDante,
					Actor_rangedWeaponIndices[playerIndex][characterIndex][entityIndex][rangedWeaponIndex],
					characterData.rangedWeapons[rangedWeaponIndex]
				);
			}
		}}
	}
}

void Actor_CharacterTab
(
	uint8 playerIndex,
	uint8 characterIndex,
	uint8 entityIndex
)
{
	ImGui::Text(Actor_entityNames[entityIndex]);
	ImGui::Text("");

	auto & activeCharacterData = GetActiveCharacterData
	(
		playerIndex,
		characterIndex,
		entityIndex
	);
	auto & queuedCharacterData = GetQueuedCharacterData
	(
		playerIndex,
		characterIndex,
		entityIndex
	);

	ImGui::PushItemWidth(150);
	if
	(
		GUI_Combo2
		(
			"Character",
			Actor_characterNames,
			activeCharacterData.character,
			queuedCharacterData.character
		)
	)
	{
		ApplyDefaultCharacterData(activeCharacterData, activeCharacterData.character);
		ApplyDefaultCharacterData(queuedCharacterData, queuedCharacterData.character);

		Actor_UpdateIndices();
	}
	ImGui::PopItemWidth();

	if
	(
		(activeCharacterData.character == CHAR_BOB ) ||
		(activeCharacterData.character == CHAR_LADY)
	)
	{
		return;
	}

	ImGui::PushItemWidth(150);
	GUI_Input2
	(
		"Costume",
		activeCharacterData.costume,
		queuedCharacterData.costume
	);
	GUI_Checkbox2
	(
		"Force Files",
		activeCharacterData.forceFiles,
		queuedCharacterData.forceFiles
	);
	{
		bool condition = !activeCharacterData.forceFiles;
		GUI_PushDisable(condition);
		GUI_Combo2
		(
			"Character",
			Actor_characterNames,
			activeCharacterData.forceFilesCharacter,
			queuedCharacterData.forceFilesCharacter
		);
		GUI_PopDisable(condition);
	}
	ImGui::PopItemWidth();
	ImGui::Text("");

	ImGui::Text("Styles");
	ImGui::PushItemWidth(150);
	for_all(uint8, styleIndex, STYLE_COUNT)
	{
		if constexpr (debug)
		{
			ImGui::Text("");
			ImGui::Text("%u", styleIndex);
		}

		GUI_ComboMap2
		(
			"",
			Actor_styleButtonNames,
			Actor_styleButtons,
			Actor_styleButtonIndices[playerIndex][characterIndex][entityIndex][styleIndex],
			activeCharacterData.styleButtons[styleIndex],
			queuedCharacterData.styleButtons[styleIndex],
			ImGuiComboFlags_HeightLargest
		);

		if constexpr (!debug)
		{
			ImGui::SameLine();
		}

		switch (queuedCharacterData.character)
		{
			case CHAR_DANTE:
			{
				GUI_ComboMap2
				(
					"",
					styleNamesDante,
					stylesDante,
					Actor_styleIndices[playerIndex][characterIndex][entityIndex][styleIndex][0],
					activeCharacterData.styles[styleIndex][0],
					queuedCharacterData.styles[styleIndex][0]
				);
				if constexpr (!debug)
				{
					ImGui::SameLine();
				}
				GUI_ComboMap2
				(
					"",
					styleNamesDante,
					stylesDante,
					Actor_styleIndices[playerIndex][characterIndex][entityIndex][styleIndex][1],
					activeCharacterData.styles[styleIndex][1],
					queuedCharacterData.styles[styleIndex][1]
				);

				break;
			}
			case CHAR_VERGIL:
			{
				GUI_ComboMap2
				(
					"",
					styleNamesVergil,
					stylesVergil,
					Actor_styleIndices[playerIndex][characterIndex][entityIndex][styleIndex][0],
					activeCharacterData.styles[styleIndex][0],
					queuedCharacterData.styles[styleIndex][0]
				);
				if constexpr (!debug)
				{
					ImGui::SameLine();
				}
				GUI_ComboMap2
				(
					"",
					styleNamesVergil,
					stylesVergil,
					Actor_styleIndices[playerIndex][characterIndex][entityIndex][styleIndex][1],
					activeCharacterData.styles[styleIndex][1],
					queuedCharacterData.styles[styleIndex][1]
				);

				break;
			}
		}
	}
	ImGui::PopItemWidth();

	if (queuedCharacterData.character != CHAR_DANTE)
	{
		return;
	}
	ImGui::Text("");

	ImGui::Text("Melee Weapons");
	ImGui::PushItemWidth(200);
	GUI_Slider2<uint8>
	(
		"",
		activeCharacterData.meleeWeaponCount,
		queuedCharacterData.meleeWeaponCount,
		1,
		MELEE_WEAPON_COUNT_DANTE
	);
	for_all(uint8, meleeWeaponIndex, MELEE_WEAPON_COUNT_DANTE)
	{
		bool condition = (meleeWeaponIndex >= queuedCharacterData.meleeWeaponCount);
		GUI_PushDisable(condition);
		GUI_ComboMap2
		(
			"",
			Actor_meleeWeaponNamesDante,
			Actor_meleeWeaponsDante,
			Actor_meleeWeaponIndices[playerIndex][characterIndex][entityIndex][meleeWeaponIndex],
			activeCharacterData.meleeWeapons[meleeWeaponIndex],
			queuedCharacterData.meleeWeapons[meleeWeaponIndex]
		);
		GUI_PopDisable(condition);
	}
	ImGui::Text("");

	ImGui::Text("Ranged Weapons");
	GUI_Slider2<uint8>
	(
		"",
		activeCharacterData.rangedWeaponCount,
		queuedCharacterData.rangedWeaponCount,
		1,
		RANGED_WEAPON_COUNT_DANTE
	);
	for_all(uint8, rangedWeaponIndex, RANGED_WEAPON_COUNT_DANTE)
	{
		bool condition = (rangedWeaponIndex >= queuedCharacterData.rangedWeaponCount);
		GUI_PushDisable(condition);
		GUI_ComboMap2
		(
			"",
			Actor_rangedWeaponNamesDante,
			Actor_rangedWeaponsDante,
			Actor_rangedWeaponIndices[playerIndex][characterIndex][entityIndex][rangedWeaponIndex],
			activeCharacterData.rangedWeapons[rangedWeaponIndex],
			queuedCharacterData.rangedWeapons[rangedWeaponIndex]
		);
		GUI_PopDisable(condition);
	}
	ImGui::PopItemWidth();
}

void Actor_PlayerTab(uint8 playerIndex)
{
	auto & activePlayerData = GetActivePlayerData(playerIndex);
	auto & queuedPlayerData = GetQueuedPlayerData(playerIndex);

	ImGui::PushItemWidth(200);
	GUI_ComboMap2
	(
		"Button",
		Actor_buttonNames,
		Actor_buttons,
		Actor_buttonIndices[playerIndex],
		activePlayerData.button,
		queuedPlayerData.button,
		ImGuiComboFlags_HeightLargest
	);
	ImGui::PopItemWidth();
	ImGui::Text("");

	ImGui::PushItemWidth(200);
	GUI_Slider2<uint8>
	(
		"Character Count",
		activePlayerData.characterCount,
		queuedPlayerData.characterCount,
		1,
		CHARACTER_COUNT
	);
	ImGui::PopItemWidth();
	ImGui::Text("");

	if (ImGui::BeginTabBar("CharacterTabs"))
	{
		for_all(uint8, characterIndex, CHARACTER_COUNT)
		{
			auto condition = (characterIndex >= activePlayerData.characterCount);

			GUI_PushDisable(condition);

			if (ImGui::BeginTabItem(Actor_characterTabNames[characterIndex]))
			{
				ImGui::Text("");

				for_all(uint8, entityIndex, ENTITY_COUNT)
				{
					Actor_CharacterTab
					(
						playerIndex,
						characterIndex,
						entityIndex
					);

					if (entityIndex < (ENTITY_COUNT - 1))
					{
						ImGui::Text("");
					}
				}

				ImGui::EndTabItem();
			}

			GUI_PopDisable(condition);
		}

		ImGui::EndTabBar();
	}
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
				&activeConfig.Actor,
				&defaultConfig.Actor,
				sizeof(Config::Actor)
			);

			memcpy
			(
				&queuedConfig.Actor,
				&defaultConfig.Actor,
				sizeof(Config::Actor)
			);

			activeConfig.removeBusyFlag = queuedConfig.removeBusyFlag = defaultConfig.removeBusyFlag;

			Actor_UpdateIndices();

			if
			(
				(g_scene == SCENE_MAIN          ) ||
				(g_scene == SCENE_MISSION_SELECT)
			)
			{
				Actor_Toggle(activeConfig.Actor.enable);
			}
		}
		ImGui::Text("");

		ImGui::PushItemWidth(200);
		// @Todo: 2.
		GUI_Slider<uint8>
		(
			"Player Count",
			queuedConfig.Actor.playerCount,
			1,
			PLAYER_COUNT
		);
		ImGui::PopItemWidth();
		ImGui::Text("");

		if (ImGui::BeginTabBar("PlayerTabs"))
		{
			for_all(uint8, playerIndex, PLAYER_COUNT)
			{
				auto condition = (playerIndex >= queuedConfig.Actor.playerCount);

				GUI_PushDisable(condition);

				if (ImGui::BeginTabItem(Actor_playerTabNames[playerIndex]))
				{
					ImGui::Text("");

					Actor_PlayerTab(playerIndex);

					ImGui::EndTabItem();
				}

				GUI_PopDisable(condition);
			}

			ImGui::EndTabBar();
		}
		GUI_SectionEnd();
		ImGui::Text("");

		GUI_Checkbox2
		(
			"Remove Busy Flag",
			activeConfig.removeBusyFlag,
			queuedConfig.removeBusyFlag
		);

		ImGui::Text("");
	}
}

#pragma endregion

#pragma region Arcade

#define Arcade_missionNames missionNames

#define Arcade_modeNames modeNames
#define Arcade_modes modes
uint8 Arcade_modeIndex = 0;

#define Arcade_floorNames floorNames

#define Arcade_meleeWeaponNamesDante meleeWeaponNamesDante
#define Arcade_meleeWeaponsDante meleeWeaponsDante
uint8 Arcade_meleeWeaponIndexDante[2] = {};

#define Arcade_rangedWeaponNamesDante rangedWeaponNamesDante
#define Arcade_rangedWeaponsDante rangedWeaponsDante
uint8 Arcade_rangedWeaponIndexDante[2] = {};

void Arcade_UpdateIndices()
{
	LogFunction();

	UpdateMapIndex
	(
		Arcade_modes,
		Arcade_modeIndex,
		activeConfig.Arcade.mode
	);

	UpdateMapIndex
	(
		Arcade_meleeWeaponsDante,
		Arcade_meleeWeaponIndexDante[0],
		activeConfig.Arcade.weapons[0]
	);

	UpdateMapIndex
	(
		Arcade_meleeWeaponsDante,
		Arcade_meleeWeaponIndexDante[1],
		activeConfig.Arcade.weapons[1]
	);

	UpdateMapIndex
	(
		Arcade_rangedWeaponsDante,
		Arcade_rangedWeaponIndexDante[0],
		activeConfig.Arcade.weapons[2]
	);

	UpdateMapIndex
	(
		Arcade_rangedWeaponsDante,
		Arcade_rangedWeaponIndexDante[1],
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
				Arcade_modes,
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
			characterNames,
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
				styleNamesDante,
				activeConfig.Arcade.style,
				queuedConfig.Arcade.style
			);
			GUI_ComboMap2
			(
				"Melee Weapon 1",
				meleeWeaponNamesDante,
				meleeWeaponsDante,
				Arcade_meleeWeaponIndexDante[0],
				activeConfig.Arcade.weapons[0],
				queuedConfig.Arcade.weapons[0]
			);
			GUI_ComboMap2
			(
				"Melee Weapon 2",
				meleeWeaponNamesDante,
				meleeWeaponsDante,
				Arcade_meleeWeaponIndexDante[1],
				activeConfig.Arcade.weapons[1],
				queuedConfig.Arcade.weapons[1]
			);
			GUI_ComboMap2
			(
				"Ranged Weapon 1",
				rangedWeaponNamesDante,
				rangedWeaponsDante,
				Arcade_rangedWeaponIndexDante[0],
				activeConfig.Arcade.weapons[2],
				queuedConfig.Arcade.weapons[2]
			);
			GUI_ComboMap2
			(
				"Ranged Weapon 2",
				rangedWeaponNamesDante,
				rangedWeaponsDante,
				Arcade_rangedWeaponIndexDante[1],
				activeConfig.Arcade.weapons[3],
				queuedConfig.Arcade.weapons[3]
			);
		}
		ImGui::PopItemWidth();

		ImGui::Text("");
	}
}

#pragma endregion

#pragma region Boss Rush

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

#pragma endregion

#pragma region Camera

export template <typename T>
void GUI_InputDefault2Camera
(
	const char * label,
	T & var,
	T & var2,
	T & var3,
	T & defaultVar,
	const T step = 1,
	const char * format = 0,
	ImGuiInputTextFlags flags = 0
)
{
	ImGui::PushItemWidth(150);
	GUI_Input
	(
		"",
		var,
		step,
		format,
		flags
	);
	ImGui::SameLine();
	GUI_InputDefault2
	(
		label,
		var2,
		var3,
		defaultVar,
		step,
		format,
		flags
	);
	ImGui::PopItemWidth();

	if constexpr (debug)
	{
		ImGui::Text("%f", var );
		ImGui::Text("%f", var2);
	}
}

void Camera()
{
	if (ImGui::CollapsingHeader("Camera"))
	{
		ImGui::Text("");

		if (GUI_ResetButton())
		{
			memcpy
			(
				&queuedConfig.Camera,
				&defaultConfig.Camera,
				sizeof(Config::Camera)
			);
			memcpy
			(
				&activeConfig.Camera,
				&queuedConfig.Camera,
				sizeof(Config::Camera)
			);

			Camera_ToggleInvertX(activeConfig.Camera.invertX);
		}
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

		[]()
		{
			if (g_scene != SCENE_GAME)
			{
				return;
			}

			IntroduceCameraData(return);

			GUI_SectionEnd();
			ImGui::Text("");

			TooltipHelper
			(
				"(?)",
				"Left: Live Right: Config"
			);
			ImGui::Text("");

			GUI_InputDefault2Camera
			(
				"Height",
				cameraData.height,
				activeConfig.Camera.height,
				queuedConfig.Camera.height,
				defaultConfig.Camera.height,
				10.0f,
				"%.0f",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			GUI_InputDefault2Camera
			(
				"Tilt",
				cameraData.tilt,
				activeConfig.Camera.tilt,
				queuedConfig.Camera.tilt,
				defaultConfig.Camera.tilt,
				0.05f,
				"%.2f",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			GUI_InputDefault2Camera
			(
				"Zoom",
				cameraData.zoom,
				activeConfig.Camera.zoom,
				queuedConfig.Camera.zoom,
				defaultConfig.Camera.zoom,
				10.0f,
				"%.0f",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			GUI_InputDefault2Camera
			(
				"Zoom Lock-On",
				cameraData.zoomLockOn,
				activeConfig.Camera.zoomLockOn,
				queuedConfig.Camera.zoomLockOn,
				defaultConfig.Camera.zoomLockOn,
				10.0f,
				"%.0f",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			ImGui::Text("");

			GUI_Checkbox2
			(
				"Apply Config",
				activeConfig.Camera.applyConfig,
				queuedConfig.Camera.applyConfig
			);
		}();

		ImGui::Text("");
	}
}

#pragma endregion

#pragma region Cosmetics

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
	LogFunction();

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
			"Requires enabled Actor module."
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
			"Requires enabled Actor module."
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

#pragma endregion

#pragma region Dante

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
			memcpy
			(
				&queuedConfig.AirHike,
				&defaultConfig.AirHike,
				sizeof(Config::AirHike)
			);
			memcpy
			(
				&activeConfig.AirHike,
				&queuedConfig.AirHike,
				sizeof(Config::AirHike)
			);

			// memcpy
			// (
			// 	&queuedConfig.Trickster,
			// 	&defaultConfig.Trickster,
			// 	sizeof(Config::Trickster)
			// );
			// memcpy
			// (
			// 	&activeConfig.Trickster,
			// 	&queuedConfig.Trickster,
			// 	sizeof(Config::Trickster)
			// );

			memcpy
			(
				&queuedConfig.Rebellion,
				&defaultConfig.Rebellion,
				sizeof(Config::Rebellion)
			);
			memcpy
			(
				&activeConfig.Rebellion,
				&queuedConfig.Rebellion,
				sizeof(Config::Rebellion)
			);

			memcpy
			(
				&queuedConfig.EbonyIvory,
				&defaultConfig.EbonyIvory,
				sizeof(Config::EbonyIvory)
			);
			memcpy
			(
				&activeConfig.EbonyIvory,
				&queuedConfig.EbonyIvory,
				sizeof(Config::EbonyIvory)
			);

			memcpy
			(
				&queuedConfig.Artemis,
				&defaultConfig.Artemis,
				sizeof(Config::Artemis)
			);
			memcpy
			(
				&activeConfig.Artemis,
				&queuedConfig.Artemis,
				sizeof(Config::Artemis)
			);

			ToggleAirHikeCoreAbility               (activeConfig.AirHike.coreAbility               );
			ToggleRebellionInfiniteSwordPierce     (activeConfig.Rebellion.infiniteSwordPierce     );
			ToggleEbonyIvoryFoursomeTime           (activeConfig.EbonyIvory.foursomeTime           );
			ToggleEbonyIvoryInfiniteRainStorm      (activeConfig.EbonyIvory.infiniteRainStorm      );
			ToggleArtemisSwapNormalShotAndMultiLock(activeConfig.Artemis.swapNormalShotAndMultiLock);
			ToggleArtemisInstantFullCharge         (activeConfig.Artemis.instantFullCharge         );
		}
		GUI_SectionEnd();
		ImGui::Text("");

		ImGui::Text("Air Hike");
		ImGui::SameLine();
		TooltipHelper
		(
			"(?)",
			"Requires enabled Actor module.\n"
			"\n"
			"Left: Human Right: Devil"
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
			ToggleAirHikeCoreAbility(activeConfig.AirHike.coreAbility);
		}

		ImGui::Text("");

		GUI_SectionEnd();
		ImGui::Text("");

		GUI_SectionStart("Rebellion");
		if
		(
			GUI_Checkbox2
			(
				"Infinite Sword Pierce",
				activeConfig.Rebellion.infiniteSwordPierce,
				queuedConfig.Rebellion.infiniteSwordPierce
			)
		)
		{
			ToggleRebellionInfiniteSwordPierce(activeConfig.Rebellion.infiniteSwordPierce);
		}

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

		if
		(
			GUI_Checkbox2
			(
				"Foursome Time",
				activeConfig.EbonyIvory.foursomeTime,
				queuedConfig.EbonyIvory.foursomeTime
			)
		)
		{
			ToggleEbonyIvoryFoursomeTime(activeConfig.EbonyIvory.foursomeTime);
		}

		if
		(
			GUI_Checkbox2
			(
				"Infinite Rain Storm",
				activeConfig.EbonyIvory.infiniteRainStorm,
				queuedConfig.EbonyIvory.infiniteRainStorm
			)
		)
		{
			ToggleEbonyIvoryInfiniteRainStorm(activeConfig.EbonyIvory.infiniteRainStorm);
		}

		GUI_SectionEnd();
		ImGui::Text("");

		// GUI_SectionStart("Shotgun");
		// ActionData<float32>("Gun Stinger Duration"    , activeConfig.Shotgun.gunStingerDuration   , defaultConfig.Shotgun.gunStingerDuration   , 1 , "%.0f");
		// ActionData<float32>("Gun Stinger Range"       , activeConfig.Shotgun.gunStingerRange      , defaultConfig.Shotgun.gunStingerRange      , 10, "%.0f");
		// ActionData<float32>("Air Gun Stinger Duration", activeConfig.Shotgun.airGunStingerDuration, defaultConfig.Shotgun.airGunStingerDuration, 1 , "%.0f");
		// ActionData<float32>("Air Gun Stinger Range"   , activeConfig.Shotgun.airGunStingerRange   , defaultConfig.Shotgun.airGunStingerRange   , 10, "%.0f");
		// GUI_SectionEnd();

		GUI_SectionStart("Artemis");

		if
		(
			GUI_Checkbox2
			(
				"Swap Normal Shot and Multi Lock",
				activeConfig.Artemis.swapNormalShotAndMultiLock,
				queuedConfig.Artemis.swapNormalShotAndMultiLock
			)
		)
		{
			ToggleArtemisSwapNormalShotAndMultiLock(activeConfig.Artemis.swapNormalShotAndMultiLock);
		}

		if
		(
			GUI_Checkbox2
			(
				"Instant Full Charge",
				activeConfig.Artemis.instantFullCharge,
				queuedConfig.Artemis.instantFullCharge
			)
		)
		{
			ToggleArtemisInstantFullCharge(activeConfig.Artemis.instantFullCharge);
		}

		ImGui::Text("");
	}
}

#pragma endregion

#pragma region Debug

void Debug()
{
	if (ImGui::CollapsingHeader("Debug"))
	{
		ImGui::Text("");
		IntroduceSessionData();
		GUI_Checkbox("One Hit Kill", sessionData.oneHitKill);
		ImGui::Text("");

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

#pragma endregion

#pragma region Mobility

void Mobility()
{
	if (ImGui::CollapsingHeader("Mobility"))
	{
		ImGui::Text("");

		TooltipHelper
		(
			"(?)",
			"Requires enabled Actor module.\n"
			"\n"
			"Left: Human Right: Devil"
		);
		ImGui::Text("");

		ActionData
		(
			"Air Hike Count",
			activeConfig.airHikeCount,
			queuedConfig.airHikeCount,
			defaultConfig.airHikeCount
		);
		ActionData
		(
			"Kick Jump Count",
			activeConfig.kickJumpCount,
			queuedConfig.kickJumpCount,
			defaultConfig.kickJumpCount
		);
		ActionData
		(
			"Wall Hike Count",
			activeConfig.wallHikeCount,
			queuedConfig.wallHikeCount,
			defaultConfig.wallHikeCount
		);
		ActionData
		(
			"Dash Count",
			activeConfig.dashCount,
			queuedConfig.dashCount,
			defaultConfig.dashCount
		);
		ActionData
		(
			"Sky Star Count",
			activeConfig.skyStarCount,
			queuedConfig.skyStarCount,
			defaultConfig.skyStarCount
		);
		ActionData
		(
			"Air Trick Count Dante",
			activeConfig.airTrickCountDante,
			queuedConfig.airTrickCountDante,
			defaultConfig.airTrickCountDante
		);
		ActionData
		(
			"Air Trick Count Vergil",
			activeConfig.airTrickCountVergil,
			queuedConfig.airTrickCountVergil,
			defaultConfig.airTrickCountVergil
		);
		ActionData
		(
			"Trick Up Count",
			activeConfig.trickUpCount,
			queuedConfig.trickUpCount,
			defaultConfig.trickUpCount
		);
		ActionData<uint8>
		(
			"Trick Down Count",
			activeConfig.trickDownCount,
			queuedConfig.trickDownCount,
			defaultConfig.trickDownCount
		);

		ImGui::Text("");
	}
}

#pragma endregion

#pragma region Other

const char * dotShadowNames[] =
{
	"Enable",
	"Disable",
	"Disable Actor Only"
};

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

		ImGui::Text("Dot Shadow");
		ImGui::SameLine();
		TooltipHelper
		(
			"(?)",
			"Requires enabled Actor module."
		);
		ImGui::Text("");

		// @Todo: Update to active.
		for_all(uint8, dotShadowIndex, countof(dotShadowNames))
		{
			GUI_RadioButton
			(
				dotShadowNames[dotShadowIndex],
				queuedConfig.dotShadow,
				dotShadowIndex
			);
		}

		GUI_SectionEnd();
		ImGui::Text("");

		GUI_SectionStart("Magic Points Depletion Values");
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
				"%.2f"
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

		if
		(
			GUI_InputDefault2
			(
				"Crazy Combo Level Multiplier",
				activeConfig.crazyComboLevelMultiplier,
				queuedConfig.crazyComboLevelMultiplier,
				defaultConfig.crazyComboLevelMultiplier
			)
		)
		{
			UpdateCrazyComboLevelMultiplier();
		}

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

#pragma endregion

#pragma region Repair

void Repair()
{
	if (ImGui::CollapsingHeader("Repair"))
	{
		ImGui::Text("");

		if (GUI_Button("Reset Weapons"))
		{
			if (!InGame())
			{
				return;
			}
			for_all(uint32, index, Actor_actorBaseAddr.count)
			{
				if (!Actor_actorBaseAddr[index])
				{
					continue;
				}
				auto & actorData = *reinterpret_cast<ActorData *>(Actor_actorBaseAddr[index]);

				switch (actorData.character)
				{
					case CHAR_DANTE:
					{
						actorData.weapons[0] = WEAPON_REBELLION;
						actorData.weapons[1] = WEAPON_CERBERUS;
						actorData.weapons[2] = WEAPON_EBONY_IVORY;
						actorData.weapons[3] = WEAPON_SHOTGUN;
						actorData.weapons[4] = WEAPON_VOID;

						break;
					}
					case CHAR_VERGIL:
					{
						actorData.weapons[0] = WEAPON_YAMATO_VERGIL;
						actorData.weapons[1] = WEAPON_BEOWULF_VERGIL;
						actorData.weapons[2] = WEAPON_YAMATO_FORCE_EDGE;
						actorData.weapons[3] = WEAPON_VOID;
						actorData.weapons[4] = WEAPON_VOID;
						
						break;
					}
				}
			}
		}

		if (GUI_Button("Reset Ranged Weapon Levels"))
		{
			if (!InGame())
			{
				return;
			}
			for_all(uint32, index, Actor_actorBaseAddr.count)
			{
				if (!Actor_actorBaseAddr[index])
				{
					continue;
				}
				auto & actorData = *reinterpret_cast<ActorData *>(Actor_actorBaseAddr[index]);

				memset(actorData.weaponLevels, 0, sizeof(actorData.weaponLevels));
			}
		}

		ImGui::Text("");
	}
}

#pragma endregion

#pragma region Remove Busy Flag

// #define RemoveBusyFlag_buttonNames buttonNames
// #define RemoveBusyFlag_buttons buttons

// uint8 RemoveBusyFlag_buttonIndex = 0;

// void RemoveBusyFlag_UpdateIndices()
// {
// 	LogFunction();

// 	UpdateMapIndex
// 	(
// 		RemoveBusyFlag_buttons,
// 		RemoveBusyFlag_buttonIndex,
// 		activeConfig.RemoveBusyFlag.button
// 	);
// }

// void RemoveBusyFlag()
// {
// 	if (ImGui::CollapsingHeader("Remove Busy Flag"))
// 	{
// 		ImGui::Text("");

// 		GUI_Checkbox2
// 		(
// 			"Enable",
// 			activeConfig.RemoveBusyFlag.enable,
// 			queuedConfig.RemoveBusyFlag.enable
// 		);
// 		ImGui::Text("");

// 		if (GUI_ResetButton())
// 		{
// 			memcpy
// 			(
// 				&queuedConfig.RemoveBusyFlag,
// 				&defaultConfig.RemoveBusyFlag,
// 				sizeof(Config::RemoveBusyFlag)
// 			);
// 			memcpy
// 			(
// 				&activeConfig.RemoveBusyFlag,
// 				&queuedConfig.RemoveBusyFlag,
// 				sizeof(Config::RemoveBusyFlag)
// 			);

// 			RemoveBusyFlag_UpdateIndices();
// 		}
// 		ImGui::Text("");

// 		ImGui::PushItemWidth(150);
// 		GUI_ComboMap2
// 		(
// 			"Button",
// 			RemoveBusyFlag_buttonNames,
// 			RemoveBusyFlag_buttons,
// 			RemoveBusyFlag_buttonIndex,
// 			activeConfig.RemoveBusyFlag.button,
// 			queuedConfig.RemoveBusyFlag.button,
// 			ImGuiComboFlags_HeightLargest
// 		);
// 		ImGui::PopItemWidth();

// 		ImGui::Text("");
// 	}
// }

#pragma endregion

#pragma region Reset Permissions

#define ResetPermissions_buttonNames buttonNames
#define ResetPermissions_buttons buttons

uint8 ResetPermissions_buttonIndex = 0;

void ResetPermissions_UpdateIndices()
{
	LogFunction();

	UpdateMapIndex
	(
		ResetPermissions_buttons,
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
			ResetPermissions_buttons,
			ResetPermissions_buttonIndex,
			activeConfig.ResetPermissions.button,
			queuedConfig.ResetPermissions.button,
			ImGuiComboFlags_HeightLargest
		);
		ImGui::PopItemWidth();

		ImGui::Text("");
	}
}

#pragma endregion

#pragma region Speed

const char * devilSpeedNamesDante[] =
{
	"Rebellion",
	"Cerberus",
	"Agni & Rudra",
	"Nevan",
	"Beowulf",
	"Sparda",
};

const char * devilSpeedNamesVergil[] =
{
	"Yamato",
	"Beowulf",
	"Yamato & Force Edge",
	"Nero Angelo Yamato",
	"Nero Angelo Beowulf",
};

// @Todo: EnterReturnsTrue.
// @Todo: Apply rounding.

template <typename T>
bool GUI_InputDefault2Speed
(
	const char * label,
	T & var,
	T & var2,
	T & defaultVar,
	const T step = 1,
	const char * format = 0,
	ImGuiInputTextFlags flags = 0
)
{
	auto update = GUI_InputDefault2
	(
		label,
		var,
		var2,
		defaultVar,
		step,
		format,
		flags
	);

	if (update)
	{
		UpdateSpeedValues();
	}

	return update;
}

void Speed()
{
	if (ImGui::CollapsingHeader("Speed"))
	{
		ImGui::Text("");

		if (GUI_ResetButton())
		{
			memcpy
			(
				&queuedConfig.Speed,
				&defaultConfig.Speed,
				sizeof(Config::Speed)
			);
			memcpy
			(
				&activeConfig.Speed,
				&queuedConfig.Speed,
				sizeof(Config::Speed)
			);

			UpdateSpeedValues();
		}
		ImGui::Text("");

		ImGui::PushItemWidth(200);

		GUI_InputDefault2Speed
		(
			"Main",
			activeConfig.Speed.main,
			queuedConfig.Speed.main,
			defaultConfig.Speed.main,
			0.1f,
			"%g",
			ImGuiInputTextFlags_EnterReturnsTrue
		);
		GUI_InputDefault2Speed
		(
			"Turbo",
			activeConfig.Speed.turbo,
			queuedConfig.Speed.turbo,
			defaultConfig.Speed.turbo,
			0.1f,
			"%g",
			ImGuiInputTextFlags_EnterReturnsTrue
		);
		GUI_InputDefault2Speed
		(
			"Enemy",
			activeConfig.Speed.enemy,
			queuedConfig.Speed.enemy,
			defaultConfig.Speed.enemy,
			0.1f,
			"%g",
			ImGuiInputTextFlags_EnterReturnsTrue
		);
		GUI_SectionEnd();
		ImGui::Text("");

		ImGui::Text("Actor");
		ImGui::SameLine();
		TooltipHelper
		(
			"(?)",
			"Requires enabled Actor module."
		);
		ImGui::Text("");

		GUI_InputDefault2Speed
		(
			"Human",
			activeConfig.Speed.human,
			queuedConfig.Speed.human,
			defaultConfig.Speed.human,
			0.1f,
			"%g",
			ImGuiInputTextFlags_EnterReturnsTrue
		);
		ImGui::Text("Devil Dante");
		for_all(uint8, index, countof(activeConfig.Speed.devilDante))
		{
			GUI_InputDefault2Speed
			(
				devilSpeedNamesDante[index],
				activeConfig.Speed.devilDante[index],
				queuedConfig.Speed.devilDante[index],
				defaultConfig.Speed.devilDante[index],
				0.1f,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
		}
		ImGui::Text("Devil Vergil");
		for_all(uint8, index, countof(activeConfig.Speed.devilVergil))
		{
			GUI_InputDefault2Speed
			(
				devilSpeedNamesVergil[index],
				activeConfig.Speed.devilVergil[index],
				queuedConfig.Speed.devilVergil[index],
				defaultConfig.Speed.devilVergil[index],
				0.1f,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
		}
		GUI_SectionEnd();
		ImGui::Text("");

		GUI_SectionStart("Quicksilver");
		GUI_InputDefault2Speed
		(
			"Actor",
			activeConfig.Speed.quicksilverActor,
			queuedConfig.Speed.quicksilverActor,
			defaultConfig.Speed.quicksilverActor,
			0.1f,
			"%g",
			ImGuiInputTextFlags_EnterReturnsTrue
		);
		GUI_InputDefault2Speed
		(
			"Enemy",
			activeConfig.Speed.quicksilverEnemy,
			queuedConfig.Speed.quicksilverEnemy,
			defaultConfig.Speed.quicksilverEnemy,
			0.1f,
			"%g",
			ImGuiInputTextFlags_EnterReturnsTrue
		);

		ImGui::PopItemWidth();

		ImGui::Text("");
	}
}

#pragma endregion

#pragma region System

const char * Graphics_vSyncNames[] =
{
	"Auto",
	"Force Off",
	"Force On",
};

const char * Sound_channelNames[MAX_CHANNEL] =
{
	"System",
	"Common",
	"Style Weapon",
	"Weapon 1",
	"Weapon 2",
	"Weapon 3",
	"Weapon 4",
	"Enemy",
	"Room",
	"Music",
	"Demo",
};

void System()
{
	if (ImGui::CollapsingHeader("System"))
	{
		ImGui::Text("");

		if (GUI_ResetButton())
		{
			memcpy
			(
				&queuedConfig.Event,
				&defaultConfig.Event,
				sizeof(Config::Event)
			);
			memcpy
			(
				&activeConfig.Event,
				&queuedConfig.Event,
				sizeof(Config::Event)
			);

			memcpy
			(
				&queuedConfig.File,
				&defaultConfig.File,
				sizeof(Config::File)
			);
			memcpy
			(
				&activeConfig.File,
				&queuedConfig.File,
				sizeof(Config::File)
			);

			memcpy
			(
				&queuedConfig.Graphics,
				&defaultConfig.Graphics,
				sizeof(Config::Graphics)
			);
			memcpy
			(
				&activeConfig.Graphics,
				&queuedConfig.Graphics,
				sizeof(Config::Graphics)
			);

			memcpy
			(
				&queuedConfig.Input,
				&defaultConfig.Input,
				sizeof(Config::Input)
			);
			memcpy
			(
				&activeConfig.Input,
				&queuedConfig.Input,
				sizeof(Config::Input)
			);

			memcpy
			(
				&queuedConfig.Window,
				&defaultConfig.Window,
				sizeof(Config::Window)
			);
			memcpy
			(
				&activeConfig.Window,
				&queuedConfig.Window,
				sizeof(Config::Window)
			);

			Event_ToggleSkipIntro(activeConfig.Event.skipIntro);
			Event_ToggleSkipCutscenes(activeConfig.Event.skipCutscenes);
			UpdateFrameRate();
			Window_ToggleForceFocus(activeConfig.Window.forceFocus);
		}
		GUI_SectionEnd();
		ImGui::Text("");

		GUI_SectionStart("Event");

		if
		(
			GUI_Checkbox2
			(
				"Skip Intro",
				activeConfig.Event.skipIntro,
				queuedConfig.Event.skipIntro
			)
		)
		{
			Event_ToggleSkipIntro(activeConfig.Event.skipIntro);
		}

		if
		(
			GUI_Checkbox2
			(
				"Skip Cutscenes",
				activeConfig.Event.skipCutscenes,
				queuedConfig.Event.skipCutscenes
			)
		)
		{
			Event_ToggleSkipCutscenes(activeConfig.Event.skipCutscenes);
		}

		GUI_SectionEnd();
		ImGui::Text("");

		GUI_SectionStart("File");
		GUI_Checkbox2
		(
			"Prefer Local Files",
			activeConfig.File.preferLocalFiles,
			queuedConfig.File.preferLocalFiles
		);
		GUI_SectionEnd();
		ImGui::Text("");

		GUI_SectionStart("Graphics");
		ImGui::PushItemWidth(150);

		if
		(
			GUI_InputDefault2
			(
				"Frame Rate",
				activeConfig.Graphics.frameRate,
				queuedConfig.Graphics.frameRate,
				defaultConfig.Graphics.frameRate,
				1.0,
				"%.2f",
				ImGuiInputTextFlags_EnterReturnsTrue
			)
		)
		{
			UpdateFrameRate();
		}

		GUI_Combo2
		(
			"V-Sync",
			Graphics_vSyncNames,
			activeConfig.Graphics.vSync,
			queuedConfig.Graphics.vSync
		);
		ImGui::PopItemWidth();
		GUI_SectionEnd();
		ImGui::Text("");

		GUI_SectionStart("Input");
		GUI_Checkbox2
		(
			"Hide Mouse Cursor",
			activeConfig.Input.hideMouseCursor,
			queuedConfig.Input.hideMouseCursor
		);
		GUI_SectionEnd();
		ImGui::Text("");

		GUI_SectionStart("Sound");

		ImGui::Text("Channel Volumes");

		ImGui::Text("");

		if (GUI_ResetButton())
		{
			CopyMemory
			(
				queuedConfig.channelVolumes,
				defaultConfig.channelVolumes,
				sizeof(queuedConfig.channelVolumes)
			);
			CopyMemory
			(
				activeConfig.channelVolumes,
				queuedConfig.channelVolumes,
				sizeof(activeConfig.channelVolumes)
			);

			UpdateVolumes();
		}

		ImGui::Text("");

		ImGui::PushItemWidth(150);

		for_all(uint8, channelIndex, MAX_CHANNEL)
		{
			if
			(
				GUI_InputDefault2
				(
					Sound_channelNames[channelIndex],
					activeConfig.channelVolumes[channelIndex],
					queuedConfig.channelVolumes[channelIndex],
					defaultConfig.channelVolumes[channelIndex],
					0.1f,
					"%g",
					ImGuiInputTextFlags_EnterReturnsTrue
				)
			)
			{
				SetVolume(channelIndex, activeConfig.channelVolumes[channelIndex]);
			}
		}




		ImGui::PopItemWidth();

		GUI_SectionEnd();
		ImGui::Text("");






		GUI_SectionStart("Window");

		if
		(
			GUI_Checkbox2
			(
				"Force Focus",
				activeConfig.Window.forceFocus,
				queuedConfig.Window.forceFocus
			)
		)
		{
			Window_ToggleForceFocus(activeConfig.Window.forceFocus);
		}

		ImGui::Text("");
	}
}

#pragma endregion

#pragma region Teleporter

void Teleporter()
{
	if (ImGui::CollapsingHeader("Teleporter"))
	{
		ImGui::Text("");

		auto Draw = []()
		{
			if (!InGame())
			{
				return false;
			}
			IntroduceEventData(return false);
			IntroduceNextEventData(return false);

			constexpr float width = 150;

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
			}
			ImGui::PopItemWidth();

			return true;
		};

		if (!Draw())
		{
			ImGui::Text("Invalid Pointer");
		}

		ImGui::Text("");
	}
}

#pragma endregion

#pragma region Training

void Training()
{
	if (ImGui::CollapsingHeader("Training"))
	{
		ImGui::Text("");

		if (GUI_ResetButton())
		{
			memcpy
			(
				&queuedConfig.Training,
				&defaultConfig.Training,
				sizeof(Config::Training)
			);
			memcpy
			(
				&activeConfig.Training,
				&queuedConfig.Training,
				sizeof(Config::Training)
			);

			Training_ToggleInfiniteHitPoints  (activeConfig.Training.infiniteHitPoints  );
			Training_ToggleInfiniteMagicPoints(activeConfig.Training.infiniteMagicPoints);
			Training_ToggleDisableTimer       (activeConfig.Training.disableTimer       );
		}
		ImGui::Text("");

		if
		(
			GUI_Checkbox2
			(
				"Infinite Hit Points",
				activeConfig.Training.infiniteHitPoints,
				queuedConfig.Training.infiniteHitPoints
			)
		)
		{
			Training_ToggleInfiniteHitPoints(activeConfig.Training.infiniteHitPoints);
		}

		if
		(
			GUI_Checkbox2
			(
				"Infinite Magic Points",
				activeConfig.Training.infiniteMagicPoints,
				queuedConfig.Training.infiniteMagicPoints
			)
		)
		{
			Training_ToggleInfiniteMagicPoints(activeConfig.Training.infiniteMagicPoints);
		}

		if
		(
			GUI_Checkbox2
			(
				"Disable Timer",
				activeConfig.Training.disableTimer,
				queuedConfig.Training.disableTimer
			)
		)
		{
			Training_ToggleDisableTimer(activeConfig.Training.disableTimer);
		}

		GUI_SectionEnd();
		ImGui::Text("");


		GUI_SectionStart("Mission Overlay");

		GUI_Checkbox2
		(
			"Enable",
			activeConfig.MissionOverlay.enable,
			queuedConfig.MissionOverlay.enable
		);
		ImGui::Text("");

		if (GUI_ResetButton())
		{
			memcpy
			(
				&queuedConfig.MissionOverlay,
				&defaultConfig.MissionOverlay,
				sizeof(queuedConfig.MissionOverlay)
			);
			memcpy
			(
				&activeConfig.MissionOverlay,
				&queuedConfig.MissionOverlay,
				sizeof(activeConfig.MissionOverlay)
			);

			ImGui::SetWindowPos
			(
				"GUI_MissionOverlay",
				ImVec2
				(
					static_cast<float>(activeConfig.MissionOverlay.x),
					static_cast<float>(activeConfig.MissionOverlay.y)
				)
			);
		}
		ImGui::Text("");

		bool condition = !activeConfig.MissionOverlay.enable;

		GUI_PushDisable(condition);

		GUI_Color2
		(
			"Color",
			activeConfig.MissionOverlay.color,
			queuedConfig.MissionOverlay.color,
			ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview
		);

		GUI_PopDisable(condition);

		ImGui::Text("");
	}
}

#pragma endregion

#pragma region Vergil

void Vergil()
{
	if (ImGui::CollapsingHeader("Vergil"))
	{
		ImGui::Text("");

		if (GUI_ResetButton())
		{
			// memcpy
			// (
			// 	&queuedConfig.DarkSlayer,
			// 	&defaultConfig.DarkSlayer,
			// 	sizeof(Config::DarkSlayer)
			// );
			// memcpy
			// (
			// 	&activeConfig.DarkSlayer,
			// 	&queuedConfig.DarkSlayer,
			// 	sizeof(Config::DarkSlayer)
			// );

			activeConfig.YamatoForceEdge.infiniteRoundTrip = queuedConfig.YamatoForceEdge.infiniteRoundTrip = defaultConfig.YamatoForceEdge.infiniteRoundTrip;
			activeConfig.SummonedSwords.chronoSwords       = queuedConfig.SummonedSwords.chronoSwords       = defaultConfig.SummonedSwords.chronoSwords;

			ToggleYamatoForceEdgeInfiniteRoundTrip(activeConfig.YamatoForceEdge.infiniteRoundTrip);
			ToggleChronoSwords                    (activeConfig.SummonedSwords.chronoSwords      );
		}
		GUI_SectionEnd();
		ImGui::Text("");



		ImGui::Text("Dark Slayer");
		ImGui::SameLine();
		TooltipHelper
		(
			"(?)",
			"Requires enabled Actor module.\n"
			"\n"
			"Left: Human Right: Devil"
		);
		ImGui::Text("");



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

#pragma endregion

#pragma region Main

bool Main_run = false;

void Main()
{
	if (!Main_run)
	{
		Main_run = true;
		ImGui::SetNextWindowSize(ImVec2(600, 650));

		if constexpr (debug)
		{
			ImGui::SetNextWindowPos(ImVec2(650, 50));
		}
		else
		{
			ImGui::SetNextWindowPos(ImVec2(0, 0));
		}

		//ImGuiIO & io = ImGui::GetIO();
		//io.FontDefault = io.Fonts->Fonts[FONT_MAIN];
		//ImGui::PushFont(io.Fonts->Fonts[FONT_OVERLAY_8 + activeConfig.Tools.Overlay.fontSizeIndex]);

		//ImGui::SetCurrentFont(io.Fonts->Fonts[FONT_OVERLAY_8]);
	}

	if (ImGui::Begin("DDMK 2.7 Mary Nightly 10 December 2020", &g_pause))
	{
		ImGui::Text("");

		if constexpr (debug)
		{
			static uint32 actorIndex = 0;
			static bool enable = false;

			GUI_Input
			(
				"actorIndex",
				actorIndex
			);
			GUI_Checkbox
			(
				"Enable",
				enable
			);
			if (GUI_Button("Toggle Actor"))
			{
				ToggleActor(actorIndex, enable);
			}
			ImGui::Text("");


			if (GUI_Button("Backup"))
			{
				Log("Backup");
				Log("dataAddr %llX", backupHelper.dataAddr);
				Log("count %u", backupHelper.count);
			}


		}

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

		Mobility();
		Other();
		Repair();
		// RemoveBusyFlag();
		ResetPermissions();
		Speed();
		System();
		Teleporter();
		Training();
		Vergil();

		// ImGui::Text("");

		// static float scale = 1.0f;

		// ImGui::PushItemWidth(150.0f);
		// if
		// (
		// 	GUI_Input
		// 	(
		// 		"Scale",
		// 		scale,
		// 		0.1f,
		// 		"%.2f",
		// 		ImGuiInputTextFlags_EnterReturnsTrue
		// 	)
		// )
		// {
		// 	ImGui::SetWindowFontScale(scale);
		// }
		// ImGui::PopItemWidth();

		ImGui::Text("");
	}
	ImGui::End();
}

#pragma endregion








void Sound()
{
	static bool run = false;
	if (!run)
	{
		run = true;

		ImGui::SetNextWindowSize(ImVec2(600, 650));
		ImGui::SetNextWindowPos(ImVec2(0, 0));
	}

	if (ImGui::Begin("Sound", &g_pause))
	{
		ImGui::Text("");



		static uint32 fmodChannelIndex = 0;
		static FMOD_CHANNEL * fmodChannelAddr = 0;
		static float volume = 1.0f;
		static FMOD_RESULT fmodResult = 0;

		ImGui::PushItemWidth(200);
		if
		(
			GUI_Input<uint32>
			(
				"FMOD Channel Index",
				fmodChannelIndex,
				1,
				"%u",
				ImGuiInputTextFlags_EnterReturnsTrue
			)
		)
		{
			fmodChannelAddr = reinterpret_cast<FMOD_CHANNEL **>(appBaseAddr + 0x5DE3E0)[fmodChannelIndex];
		}
		GUI_Input<uint64>
		(
			"FMOD Channel Address",
			*reinterpret_cast<uint64 *>(&fmodChannelAddr),
			0,
			"%llX",
			ImGuiInputTextFlags_CharsHexadecimal |
			ImGuiInputTextFlags_EnterReturnsTrue
		);
		GUI_Input<float>
		(
			"Volume",
			volume,
			0.1f,
			"%g",
			ImGuiInputTextFlags_EnterReturnsTrue
		);
		ImGui::PopItemWidth();
		ImGui::Text("");

		if (GUI_Button("SetVolume"))
		{
			fmodResult = FMOD_Channel_SetVolume
			(
				fmodChannelAddr,
				volume
			);
		}

		ImGui::Text("fmodResult %X", fmodResult);








		static byte8 * headMetadataAddr = 0;

		ImGui::PushItemWidth(200);
		GUI_Input<uint64>
		(
			"Head Metadata Address",
			*reinterpret_cast<uint64 *>(&headMetadataAddr),
			0,
			"%llX",
			ImGuiInputTextFlags_CharsHexadecimal |
			ImGuiInputTextFlags_EnterReturnsTrue
		);
		ImGui::PopItemWidth();
		ImGui::Text("");

		[&]()
		{
			if (!headMetadataAddr)
			{
				return;
			}

			auto & headMetadata = *reinterpret_cast<HeadMetadata *>(headMetadataAddr);

			auto & vagiMetadata = *reinterpret_cast<VagiMetadata *>(headMetadataAddr + headMetadata.vagiMetadataOff);






			if (ImGui::CollapsingHeader("Vagi"))
			{
				ImGui::Text("");

				ImGui::PushItemWidth(200);

				GUI_Input<uint32>
				(
					"size",
					vagiMetadata.size,
					0,
					"%X",
					ImGuiInputTextFlags_CharsHexadecimal |
					ImGuiInputTextFlags_EnterReturnsTrue
				);
				GUI_Input<uint32>
				(
					"last",
					vagiMetadata.last,
					0
				);

				ImGui::Text("");

				auto itemCount = (vagiMetadata.last + 1);

				ImGui::Text("itemCount %u", itemCount);

				for_all(uint32, itemIndex, itemCount)
				{
					auto & item = vagiMetadata.items[itemIndex];

					ImGui::Text("");

					ImGui::Text("%u", itemIndex);
					GUI_Input<uint32>
					(
						"off",
						item.off,
						0,
						"%X",
						ImGuiInputTextFlags_CharsHexadecimal |
						ImGuiInputTextFlags_EnterReturnsTrue
					);
					GUI_Input<uint32>
					(
						"size",
						item.size,
						0,
						"%X",
						ImGuiInputTextFlags_CharsHexadecimal |
						ImGuiInputTextFlags_EnterReturnsTrue
					);
					GUI_Input<uint32>
					(
						"sampleRate",
						item.sampleRate,
						1000,
						"%u",
						ImGuiInputTextFlags_EnterReturnsTrue
					);
				}

				ImGui::PopItemWidth();

				ImGui::Text("");
			}









			// ImGui::Text("%c", vagiMetadata.signature[0]);
			// ImGui::SameLine();
			// ImGui::Text("%c", vagiMetadata.signature[1]);
			// ImGui::SameLine();
			// ImGui::Text("%c", vagiMetadata.signature[2]);
			// ImGui::SameLine();
			// ImGui::Text("%c", vagiMetadata.signature[3]);



		}();

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
		Overlay2();
	}






	MissionOverlay();



	if (g_pause)
	{
		Main();

		if constexpr (debug)
		{
			Sound();
		}
	}

	[&]()
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
	}();

	// static bool enable = true;
	// ImGui::ShowDemoWindow(&enable);
}

export void GUI_Init()
{
	LogFunction();

	BuildFonts();

	Actor_UpdateIndices();
	Arcade_UpdateIndices();
	Color_UpdateValues();
	// RemoveBusyFlag_UpdateIndices();
	ResetPermissions_UpdateIndices();
}

#ifdef __GARBAGE__



	ImGui::Text("Character Count");
	GUI_Slider<uint8>
	(
		"",
		playerData.meleeWeaponCount,
		1,
		MELEE_WEAPON_COUNT_DANTE
	);




















switch (queuedConfig.Actor.system)
{
case ACTOR_SYSTEM_DEFAULT:
{
	Actor_PlayerTab(playerIndex, 0);

	break;
}
case ACTOR_SYSTEM_DOPPELGANGER:
{
	for_all(uint8, entity, MAX_ENTITY)
	{
		GUI_SectionStart(entityNames[entity]);

		Actor_PlayerTab(playerIndex, entity);

		if (entity != (MAX_ENTITY - 1))
		{
			GUI_SectionEnd();
			ImGui::Text("");
		}
	}

	break;
}
case ACTOR_SYSTEM_CHARACTER_SWITCHER:
{
	for_all(uint8, direction, MAX_DIRECTION)
	{
		auto & playerData = queuedConfig.Actor.playerData[playerIndex][direction];

		GUI_Checkbox
		(
			directionNames[direction],
			playerData.enable
		);

		if (playerData.enable)
		{
			ImGui::Text("");
		}

		Actor_PlayerTab(playerIndex, direction);

		if (direction != (MAX_DIRECTION - 1))
		{
			GUI_SectionEnd();
			ImGui::Text("");
		}
	}
	break;
}

		// for_all(uint8, systemIndex, MAX_ACTOR_SYSTEM)
		// {
		// 	if
		// 	(
		// 		GUI_RadioButton
		// 		(
		// 			Actor_systemNames[systemIndex],
		// 			queuedConfig.Actor.system,
		// 			systemIndex
		// 		)
		// 	)
		// 	{
		// 		for_all(uint8, player   , MAX_PLAYER   )
		// 		for_all(uint8, direction, MAX_DIRECTION){
		// 		{
		// 			auto & playerData = queuedConfig.Actor.playerData[player][direction];

		// 			ApplyDefaultPlayerData(playerData, direction);

		// 			Actor_UpdateIndices();
		// 		}}
		// 	}

		// 	if (systemIndex < (MAX_ACTOR_SYSTEM - 1))
		// 	{
		// 		ImGui::SameLine();
		// 	}
		// }
		// ImGui::Text("");

		// ImGui::PushItemWidth(200);
		// GUI_ComboMap
		// (
		// 	"",
		// 	Actor_systemButtonNames,
		// 	Actor_systemButtons,
		// 	Actor_systemButtonIndex,
		// 	queuedConfig.Actor.systemButton,
		// 	ImGuiComboFlags_HeightLargest
		// );
		// ImGui::PopItemWidth();
		// ImGui::Text("");


		// GUI_Checkbox
		// (
		// 	"Enable Quicksilver",
		// 	queuedConfig.Actor.enableQuicksilver
		// );

		// if (queuedConfig.Actor.system == ACTOR_SYSTEM_CHARACTER_SWITCHER)
		// {
		// 	GUI_Checkbox2
		// 	(
		// 		"Show Idle Actors",
		// 		activeConfig.Actor.showIdleActors,
		// 		queuedConfig.Actor.showIdleActors
		// 	);
		// }




		// if (GUI_Button("Lock Actor"))
		// {
		// 	auto actorBaseAddr = Actor_actorBaseAddr[actorIndex];
		// 	if (!actorBaseAddr)
		// 	{
		// 		return;
		// 	}
		// 	LockActor(actorBaseAddr);
		// }

		// if (GUI_Button("Unlock Actor"))
		// {
		// 	auto actorBaseAddr = Actor_actorBaseAddr[actorIndex];
		// 	if (!actorBaseAddr)
		// 	{
		// 		return;
		// 	}
		// 	UnlockActor(actorBaseAddr);
		// }




		// if (GUI_Button("Relocate"))
		// {
		// 	Actor_MiniToggle(enable);
		// }





		// if (GUI_Button("Style"))
		// {
		// 	auto & style = ImGui::GetStyle();

		// 	style.ScaleAllSizes(scale);
		// }

		// if (GUI_Button("SetWindotFontScale"))
		// {
		// 	ImGui::SetWindowFontScale(scale);
		// }





#endif
