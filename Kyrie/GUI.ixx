module;
#include "../ImGui/imgui.h"
#include "../ImGui/imgui_internal.h"

#include <stdio.h>
export module GUI;

import Core;
import Core_GUI;

#include "../Core/Macros.h"
#include "../Global.h"

import Windows;

using namespace Windows;

import Actor;
import Arcade;
import Config;
import Global;
import Graphics;
import Steam;
import Training;
import Vars;
import Window;

#define debug false



#pragma region Base

namespaceStart(FONT);
enum
{
	DEFAULT,
	MAIN,
	OVERLAY_8,
	OVERLAY_16,
	OVERLAY_32,
	OVERLAY_64,
	OVERLAY_128,
};
namespaceEnd();



void BuildFonts()
{
	auto & io = ImGui::GetIO();

	io.Fonts->AddFontDefault();

	char overlayFont[512];

	{
		char buffer[64];

		GetWindowsDirectoryA
		(
			buffer,
			sizeof(buffer)
		);

		snprintf
		(
			overlayFont,
			sizeof(overlayFont),
			"%s\\Fonts\\consola.ttf",
			buffer
		);
	}

	io.Fonts->AddFontFromFileTTF(overlayFont, 17 );
	io.Fonts->AddFontFromFileTTF(overlayFont, 8  );
	io.Fonts->AddFontFromFileTTF(overlayFont, 16 );
	io.Fonts->AddFontFromFileTTF(overlayFont, 32 );
	io.Fonts->AddFontFromFileTTF(overlayFont, 64 );
	io.Fonts->AddFontFromFileTTF(overlayFont, 128);

	io.Fonts->Build();
}

// @Merge
void TooltipHelper
(
	const char * name,
	const char * description,
	float x = 2048.0f
)
{
	ImGui::TextDisabled(name);

	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(x);
		ImGui::Text(description);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

void DescriptionHelper
(
	const char * description,
	float width = 500.0f
)
{
	ImGui::PushTextWrapPos(width);
	ImGui::Text(description);
	ImGui::PopTextWrapPos();
}

void CenterText(const char * name)
{
	float nameWidth = ImGui::CalcTextSize(name).x;
	float cursorPosX = ImGui::GetCursorPosX();
	float newCursorPosX = (cursorPosX + ((ImGui::GetWindowSize().x - nameWidth) / 2));

	ImGui::SetCursorPosX(newCursorPosX);

	ImGui::Text(name);
}

#pragma endregion

#pragma region Common


const char * playerIndexNames[] =
{
	"Player 1",
	"Player 2",
	"Player 3",
	"Player 4",
};

const char * sceneNames[] =
{
	"SCENE::MAIN",
	"SCENE::MISSION_SELECT",
	"SCENE::CUTSCENE_SELECT",
	"SCENE::MISSION_START",
	"SCENE::CUTSCENE",
	"SCENE::GAME",
	"SCENE::GAME_OVER",
	"SCENE::MISSION_RESULT",
};

const char * eventNames[] =
{
	"EVENT::MAIN",
	"EVENT::PAUSE",
	"EVENT::TELEPORT",
	"EVENT::ITEM",
	"EVENT::CUTSCENE",
};





const char * gameEnumNames[] =
{
	"GAME::NERO_DANTE",
	"GAME::VERGIL",
	"GAME::LADY_TRISH",
};



const char * gameNames[] =
{
	"Nero / Dante",
	"Vergil",
	"Trish / Lady",
};


const char * missionNames[] =
{
	"Mission Select Menu",
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

constexpr uint32 missions[] =
{
	0,
	1,
	2,
	3,
	4,
	5,
	6,
	7,
	8,
	9,
	10,
	11,
	12,
	13,
	14,
	15,
	16,
	17,
	18,
	19,
	20,
	50,
};







const char * modeEnumNames[] =
{
	"MODE::HUMAN",
	"MODE::DEVIL_HUNTER",
	"MODE::SON_OF_SPARDA",
	"MODE::DANTE_MUST_DIE",
	"MODE::LEGENDARY_DARK_KNIGHT",
};









const char * modeNames[] =
{
	"Human",
	"Devil Hunter",
	"Son of Sparda",
	"Dante Must Die",
	"Legendary Dark Knight",
	"Heaven or Hell",
	"Hell and Hell",
};

constexpr uint32 modes[] =
{
	MODE::HUMAN,
	MODE::DEVIL_HUNTER,
	MODE::SON_OF_SPARDA,
	MODE::DANTE_MUST_DIE,
	MODE::LEGENDARY_DARK_KNIGHT,
	MODE::SON_OF_SPARDA,
	MODE::SON_OF_SPARDA,
};

const char * characterNames[] =
{
	"Dante",
	"Nero",
	"Vergil",
	"Trish",
	"Lady",
};


#pragma endregion



// @Todo: Move to GUI_Base or something.

#pragma region Credits

void CreditsWindow()
{
	if (!activeConfig.showCredits)
	{
		return;
	}



	static bool  run        = false;
	static float scrollY    = 0;
	static float maxScrollY = 0;



	if (!run)
	{
		run = true;



		ImGui::SetNextWindowSize
		(
			ImVec2
			(
				g_renderSize.x,
				g_renderSize.y
			)
		);

		ImGui::SetNextWindowPos
		(
			ImVec2
			(
				0,
				0
			)
		);
	}



	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(0, 0));

	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));

	if
	(
		ImGui::Begin
		(
			"Credits",
			&activeConfig.showCredits,
			ImGuiWindowFlags_NoTitleBar  |
			ImGuiWindowFlags_NoResize    |
			ImGuiWindowFlags_NoMove      |
			ImGuiWindowFlags_NoScrollbar
		)
	)
	{
		ImGui::Text("");


		constexpr float scrollSpeedY = 1.0f;
		constexpr size_t padding = 30;

		auto & io = ImGui::GetIO();



		{
			auto window = ImGui::GetCurrentWindow();

			ImGui::BringWindowToDisplayBack(window);
		}



		maxScrollY = ImGui::GetScrollMaxY();

		if (scrollY < maxScrollY)
		{
			scrollY += (scrollSpeedY * g_frameRateMultiplier);
		}
		else
		{
			scrollY = 0;
		}



		ImGui::PushFont(io.Fonts->Fonts[FONT::OVERLAY_32]);



		for_all(index, padding)
		{
			ImGui::Text("");
		}



		CenterText("Special Thanks");
		ImGui::Text("");

		for_all(index, countof(specialNames))
		{
			auto name = specialNames[index];

			CenterText(name);
		}

		ImGui::Text("");
		ImGui::Text("");
		ImGui::Text("");



		CenterText("Gold & Platinum Patrons");
		CenterText("");

		for_all(index, countof(goldPlatinumNames))
		{
			auto name = goldPlatinumNames[index];

			CenterText(name);
		}

		ImGui::Text("");



		for_all(index, padding)
		{
			ImGui::Text("");
		}



		ImGui::PopFont();



		ImGui::Text("");
	}

	ImGui::SetScrollY(scrollY);

	ImGui::End();

	ImGui::PopStyleColor();
	ImGui::PopStyleVar(4);
}

#pragma endregion



#pragma region Actor

void Actor_PlayerTab(size_t playerIndex)
{
	auto & activePlayerData = activeConfig.Actor.playerData[playerIndex];
	auto & queuedPlayerData = queuedConfig.Actor.playerData[playerIndex];

	auto condition = (playerIndex == 0);

	GUI_PushDisable(condition);

	ImGui::PushItemWidth(200.0f);

	GUI_Combo
	(
		"Character",
		characterNames,
		queuedPlayerData.character,
		ImGuiComboFlags_HeightLargest
	);

	GUI_Input
	(
		"Costume",
		queuedPlayerData.costume
	);

	ImGui::PopItemWidth();

	GUI_PopDisable(condition);
}

void ActorSection()
{
	if (ImGui::CollapsingHeader("Actor"))
	{
		ImGui::Text("");

		DescriptionHelper("Actor spawn extension. Required for multiplayer.");
		ImGui::Text("");



		if
		(
			GUI_Checkbox
			(
				"Enable",
				queuedConfig.Actor.enable
			)
		)
		{
			if
			(
				(g_scene == SCENE::MAIN          ) ||
				(g_scene == SCENE::MISSION_SELECT)
			)
			{
				activeConfig.Actor.enable = queuedConfig.Actor.enable;

				Actor::Toggle(activeConfig.Actor.enable);
			}
		}
		ImGui::Text("");




		if (GUI_ResetButton())
		{
			CopyMemory
			(
				&queuedConfig.Actor,
				&defaultConfig.Actor,
				sizeof(queuedConfig.Actor)
			);

			if
			(
				(g_scene == SCENE::MAIN          ) ||
				(g_scene == SCENE::MISSION_SELECT)
			)
			{
				CopyMemory
				(
					&activeConfig.Actor,
					&queuedConfig.Actor,
					sizeof(activeConfig.Actor)
				);

				Actor::Toggle(activeConfig.Actor.enable);
			}
		}
		ImGui::Text("");









		ImGui::PushItemWidth(200.0f);

		GUI_Slider<size_t>
		(
			"Player Count",
			queuedConfig.Actor.playerCount,
			1,
			PLAYER::COUNT
		);
		ImGui::Text("");

		ImGui::PopItemWidth();



		if (ImGui::BeginTabBar("PlayerTabs"))
		{
			for_all(playerIndex, PLAYER::COUNT)
			{
				auto condition = (playerIndex >= queuedConfig.Actor.playerCount);

				GUI_PushDisable(condition);

				if (ImGui::BeginTabItem(playerIndexNames[playerIndex]))
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


		ImGui::PushItemWidth(200.0f);

		GUI_Combo2
		(
			"Keyboard",
			playerIndexNames,
			activeConfig.Actor.keyboard,
			queuedConfig.Actor.keyboard,
			ImGuiComboFlags_HeightLargest
		);

		ImGui::PopItemWidth();







		ImGui::Text("");
	}
}

#pragma endregion

#pragma region Arcade

uint8 Arcade_modeIndex    = 0;
uint8 Arcade_missionIndex = 0;



void Arcade_UpdateIndices()
{
	UpdateMapIndex
	(
		modes,
		Arcade_modeIndex,
		activeConfig.Arcade.mode
	);

	UpdateMapIndex
	(
		missions,
		Arcade_missionIndex,
		activeConfig.Arcade.mission
	);
}

void ArcadeSection()
{
	if (ImGui::CollapsingHeader("Arcade"))
	{
		ImGui::Text("");

		DescriptionHelper("Go to a specific point in the game. Triggered in the main menu.");
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
			Arcade::Toggle(activeConfig.Arcade.enable);
		}
		ImGui::Text("");

		if (GUI_ResetButton())
		{
			ResetConfig(Arcade);

			Arcade_UpdateIndices();

			Arcade::Toggle(activeConfig.Arcade.enable);
		}
		ImGui::Text("");



		ImGui::PushItemWidth(200);

		GUI_Combo2
		(
			"Game",
			gameNames,
			activeConfig.Arcade.game,
			queuedConfig.Arcade.game,
			ImGuiComboFlags_HeightLargest
		);

		GUI_ComboMap2
		(
			"Mission",
			missionNames,
			missions,
			Arcade_missionIndex,
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
				modeNames,
				modes,
				Arcade_modeIndex,
				activeConfig.Arcade.mode,
				queuedConfig.Arcade.mode,
				ImGuiComboFlags_HeightLargest
			);

			// Room
			{
				bool condition = activeConfig.Arcade.ignoreRoom;

				GUI_PushDisable(condition);

				GUI_InputDefault2
				(
					"Room",
					activeConfig.Arcade.room,
					queuedConfig.Arcade.room,
					defaultConfig.Arcade.room
				);

				GUI_PopDisable(condition);

				ImGui::SameLine();

				GUI_Checkbox2
				(
					"Ignore",
					activeConfig.Arcade.ignoreRoom,
					queuedConfig.Arcade.ignoreRoom
				);
			}

			// Position
			{
				bool condition = activeConfig.Arcade.ignorePosition;

				GUI_PushDisable(condition);

				GUI_InputDefault2
				(
					"Position",
					activeConfig.Arcade.position,
					queuedConfig.Arcade.position,
					defaultConfig.Arcade.position
				);

				GUI_PopDisable(condition);

				ImGui::SameLine();

				GUI_Checkbox2
				(
					"Ignore",
					activeConfig.Arcade.ignorePosition,
					queuedConfig.Arcade.ignorePosition
				);
			}
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
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);

			GUI_InputDefault2
			(
				"Magic Points",
				activeConfig.Arcade.magicPoints,
				queuedConfig.Arcade.magicPoints,
				defaultConfig.Arcade.magicPoints,
				1000.0f,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);

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
		}

		ImGui::PopItemWidth();



		ImGui::Text("");
	}
}

#pragma endregion

#pragma region Bars

const char * barsNames[PLAYER::COUNT] =
{
	"Bars1",
	"Bars2",
	"Bars3",
	"Bars4",
};

bool showBars = false;



void BarsFunction
(
	float hitPoints,
	float magicPoints,
	const char * name,
	const char * label,
	Config::BarsData & activeData,
	Config::BarsData & queuedData
)
{
	if
	(
		!showBars &&
		!activeData.enable
	)
	{
		return;
	}

	auto & activePos = *reinterpret_cast<ImVec2 *>(&activeData.pos);
	auto & queuedPos = *reinterpret_cast<ImVec2 *>(&queuedData.pos);

	auto & lastX = activeData.lastX;
	auto & lastY = activeData.lastY;

	auto & run = activeData.run;
	if (!run)
	{
		run = true;

		ImGui::SetNextWindowPos(activePos);

		lastX = static_cast<uint32>(activeData.pos.x);
		lastY = static_cast<uint32>(activeData.pos.y);
	}

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(0, 0));

	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));

	if
	(
		ImGui::Begin
		(
			label,
			&activeData.enable,
			ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize
		)
	)
	{
		activePos = queuedPos = ImGui::GetWindowPos();

		auto x = static_cast<uint32>(activeData.pos.x);
		auto y = static_cast<uint32>(activeData.pos.y);

		if
		(
			(lastX != x) ||
			(lastY != y)
		)
		{
			lastX = x;
			lastY = y;

			GUI::save = true;
		}



		ImGui::PushStyleColor
		(
			ImGuiCol_PlotHistogram,
			*reinterpret_cast<ImVec4 *>(&activeData.hitColor)
		);
		ImGui::ProgressBar
		(
			hitPoints,
			*reinterpret_cast<ImVec2 *>(&activeData.size)
		);
		ImGui::PopStyleColor();



		ImGui::PushStyleColor
		(
			ImGuiCol_PlotHistogram,
			*reinterpret_cast<ImVec4 *>(&activeData.magicColor)
		);
		ImGui::ProgressBar
		(
			magicPoints,
			*reinterpret_cast<ImVec2 *>(&activeData.size)
		);
		ImGui::PopStyleColor();



		ImGui::Text(name);
	}

	ImGui::End();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar(4);
}

void BarsSettingsFunction
(
	const char * label,
	Config::BarsData & activeData,
	Config::BarsData & queuedData,
	Config::BarsData & defaultData
)
{
	auto & activePos = *reinterpret_cast<ImVec2 *>(&activeData.pos);
	auto & queuedPos = *reinterpret_cast<ImVec2 *>(&queuedData.pos);
	auto & defaultPos = *reinterpret_cast<ImVec2 *>(&defaultData.pos);



	GUI_Checkbox2
	(
		"Enable",
		activeData.enable,
		queuedData.enable
	);
	ImGui::Text("");

	if (GUI_ResetButton())
	{
		CopyMemory
		(
			&queuedData,
			&defaultData,
			sizeof(queuedData)
		);
		CopyMemory
		(
			&activeData,
			&queuedData,
			sizeof(activeData)
		);

		ImGui::SetWindowPos(label, activePos);
	}
	ImGui::Text("");

	bool condition = !activeData.enable;

	GUI_PushDisable(condition);

	GUI_Color2
	(
		"Hit Color",
		activeData.hitColor,
		queuedData.hitColor,
		ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview
	);
	GUI_Color2
	(
		"Magic Color",
		activeData.magicColor,
		queuedData.magicColor,
		ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview
	);
	ImGui::Text("");

	ImGui::PushItemWidth(150);

	GUI_InputDefault2
	(
		"Width",
		activeData.size.x,
		queuedData.size.x,
		defaultData.size.x,
		1.0f,
		"%g",
		ImGuiInputTextFlags_EnterReturnsTrue
	);
	GUI_InputDefault2
	(
		"Height",
		activeData.size.y,
		queuedData.size.y,
		defaultData.size.y,
		1.0f,
		"%g",
		ImGuiInputTextFlags_EnterReturnsTrue
	);

	if
	(
		GUI_InputDefault2<float>
		(
			"X",
			activePos.x,
			queuedPos.x,
			defaultPos.x,
			1,
			"%g",
			ImGuiInputTextFlags_EnterReturnsTrue
		)
	)
	{
		ImGui::SetWindowPos(label, activePos);
	}
	if
	(
		GUI_InputDefault2<float>
		(
			"Y",
			activePos.y,
			queuedPos.y,
			defaultPos.y,
			1,
			"%g",
			ImGuiInputTextFlags_EnterReturnsTrue
		)
	)
	{
		ImGui::SetWindowPos(label, activePos);
	}

	ImGui::PopItemWidth();

	GUI_PopDisable(condition);
}

void Bars()
{
	if
	(
		!showBars &&
		!(
			activeConfig.Actor.enable &&
			InGame()
		)
	)
	{
		return;
	}

	size_t playerCount = (showBars) ? PLAYER::COUNT : activeConfig.Actor.playerCount;

	for_all(playerIndex, playerCount)
	{
		auto & playerData = activeConfig.Actor.playerData[playerIndex];
		auto & newActorData = g_newActorData[playerIndex];

		float hit   = 0.75f;
		float magic = 0.5f;

		[&]()
		{
			IntroduceData(newActorData.baseAddr, actorData, PlayerActorData, return);

			hit   = (actorData.hitPoints   / actorData.maxHitPoints  );
			magic = (actorData.magicPoints / actorData.maxMagicPoints);
		}();

		BarsFunction
		(
			hit,
			magic,
			playerIndexNames[playerIndex],
			barsNames[playerIndex],
			activeConfig.barsData[playerIndex],
			queuedConfig.barsData[playerIndex]
		);
	}
}

void BarsSettings()
{
	for_all(playerIndex, PLAYER::COUNT)
	{
		GUI_SectionEnd();
		ImGui::Text("");

		GUI_SectionStart(playerIndexNames[playerIndex]);

		BarsSettingsFunction
		(
			barsNames[playerIndex],
			activeConfig.barsData[playerIndex],
			queuedConfig.barsData[playerIndex],
			defaultConfig.barsData[playerIndex]
		);
	}
}

void BarsSection()
{
	if (ImGui::CollapsingHeader("Bars"))
	{
		ImGui::Text("");

		if (GUI_ResetButton())
		{
			ResetConfig(barsData);

			for_all(playerIndex, PLAYER::COUNT)
			{
				ImGui::SetWindowPos
				(
					barsNames[playerIndex],
					*reinterpret_cast<ImVec2 *>(&activeConfig.barsData[playerIndex].pos)
				);
			}
		}
		ImGui::Text("");



		GUI_Checkbox
		(
			"Show Bars",
			showBars
		);

		BarsSettings();



		ImGui::Text("");
	}
}

#pragma endregion

#pragma region Camera

void CameraSection()
{
	if (ImGui::CollapsingHeader("Camera"))
	{
		ImGui::Text("");

		if (GUI_ResetButton())
		{


		}
		ImGui::Text("");



		GUI_SectionStart("Live");

		[&]()
		{
			if (g_scene != SCENE::GAME)
			{
				return;
			}

			IntroduceCameraData(return);



			ImGui::PushItemWidth(150.0f);

			GUI_Input
			(
				"Height",
				cameraData.height,
				10.0f,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			GUI_Input
			(
				"Tilt",
				cameraData.tilt,
				0.1f,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			GUI_Input
			(
				"Distance",
				cameraData.distance,
				10.0f,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			GUI_Input
			(
				"Distance Lock-On",
				cameraData.distanceLockOn,
				10.0f,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);
			GUI_Input
			(
				"FOV",
				cameraData.fov,
				5.0f,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			);

			ImGui::PopItemWidth();
		}();



		ImGui::Text("");
	}
}

#pragma endregion

#pragma region Overlays

template <typename T>
void OverlayFunction
(
	const char * label,
	Config::OverlayData & activeData,
	Config::OverlayData & queuedData,
	T & func
)
{
	if (!activeData.enable)
	{
		return;
	}

	auto & activePos = *reinterpret_cast<ImVec2 *>(&activeData.pos);
	auto & queuedPos = *reinterpret_cast<ImVec2 *>(&queuedData.pos);

	static uint32 lastX = 0;
	static uint32 lastY = 0;

	static bool run = false;
	if (!run)
	{
		run = true;

		ImGui::SetNextWindowPos(activePos);

		lastX = static_cast<uint32>(activeData.pos.x);
		lastY = static_cast<uint32>(activeData.pos.y);
	}

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(0, 0));

	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));

	if
	(
		ImGui::Begin
		(
			label,
			&activeData.enable,
			ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize
		)
	)
	{
		activePos = queuedPos = ImGui::GetWindowPos();

		uint32 x = static_cast<uint32>(activeData.pos.x);
		uint32 y = static_cast<uint32>(activeData.pos.y);

		if
		(
			(lastX != x) ||
			(lastY != y)
		)
		{
			lastX = x;
			lastY = y;

			GUI::save = true;
		}

		auto & io = ImGui::GetIO();
		ImGui::PushFont(io.Fonts->Fonts[FONT::OVERLAY_16]);

		ImGui::PushStyleColor
		(
			ImGuiCol_Text,
			*reinterpret_cast<ImVec4 *>(&activeData.color)
		);

		func();

		ImGui::PopStyleColor();
		ImGui::PopFont();
	}

	ImGui::End();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar(4);
}

template
<
	typename T,
	typename T2
>
void OverlaySettings
(
	const char * label,
	T & activeData,
	T & queuedData,
	T & defaultData,
	T2 & func
)
{
	auto & activePos = *reinterpret_cast<ImVec2 *>(&activeData.pos);
	auto & queuedPos = *reinterpret_cast<ImVec2 *>(&queuedData.pos);
	auto & defaultPos = *reinterpret_cast<ImVec2 *>(&defaultData.pos);

	GUI_Checkbox2
	(
		"Enable",
		activeData.enable,
		queuedData.enable
	);
	ImGui::Text("");

	if (GUI_ResetButton())
	{
		CopyMemory
		(
			&queuedData,
			&defaultData,
			sizeof(queuedData)
		);
		CopyMemory
		(
			&activeData,
			&queuedData,
			sizeof(activeData)
		);

		ImGui::SetWindowPos(label, activePos);
	}
	ImGui::Text("");

	bool condition = !activeData.enable;

	GUI_PushDisable(condition);

	GUI_Color2
	(
		"Color",
		activeData.color,
		queuedData.color,
		ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview
	);
	ImGui::Text("");

	ImGui::PushItemWidth(150);

	if
	(
		GUI_InputDefault2<float>
		(
			"X",
			activePos.x,
			queuedPos.x,
			defaultPos.x,
			1,
			"%g",
			ImGuiInputTextFlags_EnterReturnsTrue
		)
	)
	{
		ImGui::SetWindowPos(label, activePos);
	}
	if
	(
		GUI_InputDefault2<float>
		(
			"Y",
			activePos.y,
			queuedPos.y,
			defaultPos.y,
			1,
			"%g",
			ImGuiInputTextFlags_EnterReturnsTrue
		)
	)
	{
		ImGui::SetWindowPos(label, activePos);
	}

	ImGui::PopItemWidth();

	func();

	GUI_PopDisable(condition);
}

template <typename T>
void OverlaySettings
(
	const char * label,
	T & activeData,
	T & queuedData,
	T & defaultData
)
{
	auto Function = [](){};

	return OverlaySettings
	(
		label,
		activeData,
		queuedData,
		defaultData,
		Function
	);
}



const char * mainOverlayLabel = "MainOverlay";

void MainOverlayWindow()
{
	auto Function = [&]()
	{
		if (activeConfig.mainOverlayData.showFocus)
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

		if (activeConfig.mainOverlayData.showFPS)
		{
			ImGui::Text("%.2f FPS", ImGui::GetIO().Framerate);
		}

		if (activeConfig.mainOverlayData.showSizes)
		{
			ImGui::Text
			(
				"g_windowSize %g %g",
				g_windowSize.x,
				g_windowSize.y
			);
			ImGui::Text
			(
				"g_clientSize %g %g",
				g_clientSize.x,
				g_clientSize.y
			);
			ImGui::Text
			(
				"g_renderSize %g %g",
				g_renderSize.x,
				g_renderSize.y
			);
		}

		if (activeConfig.mainOverlayData.showFrameRateMultiplier)
		{
			ImGui::Text("g_frameRateMultiplier %g", g_frameRateMultiplier);
		}

		if
		(
			activeConfig.mainOverlayData.showFocus               ||
			activeConfig.mainOverlayData.showFPS                 ||
			activeConfig.mainOverlayData.showSizes               ||
			activeConfig.mainOverlayData.showFrameRateMultiplier
		)
		{
			ImGui::Text("");
		}



		if (activeConfig.mainOverlayData.showEventData)
		{
			if (g_scene >= SCENE::COUNT)
			{
				ImGui::Text("Unknown");
			}
			else
			{
				ImGui::Text(sceneNames[g_scene]);
			}

			[&]()
			{
				if (g_scene != SCENE::GAME)
				{
					return;
				}

				IntroduceEventData(return);
				IntroduceNextEventData(return);

				if (eventData.event >= EVENT::COUNT)
				{
					ImGui::Text("Unknown");
				}
				else
				{
					ImGui::Text(eventNames[eventData.event]);
				}

				ImGui::Text("");

				ImGui::Text("room         %u", eventData.room        );
				ImGui::Text("nextRoom     %u", nextEventData.room    );
				ImGui::Text("nextPosition %u", nextEventData.position);
			}();

			ImGui::Text("");
		}

		[&]()
		{
			if (!activeConfig.mainOverlayData.showSpeed)
			{
				return;
			}

			auto addr = *reinterpret_cast<byte8 **>(appBaseAddr + 0xF2429C);
			if (!addr)
			{
				return;
			}
			auto & speed = *reinterpret_cast<float *>(addr + 0x7C);

			ImGui::Text("Speed %g", speed);

			ImGui::Text("");
		}();
	};

	OverlayFunction
	(
		mainOverlayLabel,
		activeConfig.mainOverlayData,
		queuedConfig.mainOverlayData,
		Function
	);
}

void MainOverlaySettings()
{
	auto Function = [&]()
	{
		GUI_Checkbox2
		(
			"Show Focus",
			activeConfig.mainOverlayData.showFocus,
			queuedConfig.mainOverlayData.showFocus
		);
		GUI_Checkbox2
		(
			"Show FPS",
			activeConfig.mainOverlayData.showFPS,
			queuedConfig.mainOverlayData.showFPS
		);
		GUI_Checkbox2
		(
			"Show Sizes",
			activeConfig.mainOverlayData.showSizes,
			queuedConfig.mainOverlayData.showSizes
		);
		GUI_Checkbox2
		(
			"Show Frame Rate Multiplier",
			activeConfig.mainOverlayData.showFrameRateMultiplier,
			queuedConfig.mainOverlayData.showFrameRateMultiplier
		);
		GUI_Checkbox2
		(
			"Show Event Data",
			activeConfig.mainOverlayData.showEventData,
			queuedConfig.mainOverlayData.showEventData
		);
		GUI_Checkbox2
		(
			"Show Speed",
			activeConfig.mainOverlayData.showSpeed,
			queuedConfig.mainOverlayData.showSpeed
		);
	};

	OverlaySettings
	(
		mainOverlayLabel,
		activeConfig.mainOverlayData,
		queuedConfig.mainOverlayData,
		defaultConfig.mainOverlayData,
		Function
	);
}



void Overlays()
{
	if (ImGui::CollapsingHeader("Overlays"))
	{
		ImGui::Text("");

		if (GUI_ResetButton())
		{
			ResetConfig(mainOverlayData);

			ImGui::SetWindowPos(mainOverlayLabel, *reinterpret_cast<ImVec2*>(&activeConfig.mainOverlayData.pos));
		}

		GUI_SectionEnd();
		ImGui::Text("");

		GUI_SectionStart("Main");

		MainOverlaySettings();

		ImGui::Text("");
	}
}

#pragma endregion

#pragma region Speed

void SpeedSection()
{
	if (ImGui::CollapsingHeader("Speed"))
	{
		ImGui::Text("");



		if (GUI_ResetButton())
		{
			ResetConfig(mainSpeed);
			ResetConfig(menuSpeed);
			ResetConfig(cutsceneSpeed);
		}
		ImGui::Text("");



		ImGui::PushItemWidth(200);

		GUI_InputDefault2
		(
			"Main",
			activeConfig.mainSpeed,
			queuedConfig.mainSpeed,
			defaultConfig.mainSpeed,
			0.1f,
			"%g",
			ImGuiInputTextFlags_EnterReturnsTrue
		);
		GUI_InputDefault2
		(
			"Menu",
			activeConfig.menuSpeed,
			queuedConfig.menuSpeed,
			defaultConfig.menuSpeed,
			0.1f,
			"%g",
			ImGuiInputTextFlags_EnterReturnsTrue
		);
		GUI_InputDefault2
		(
			"Cutscene",
			activeConfig.cutsceneSpeed,
			queuedConfig.cutsceneSpeed,
			defaultConfig.cutsceneSpeed,
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



void System()
{
	if (ImGui::CollapsingHeader("System"))
	{
		ImGui::Text("");

		if (GUI_ResetButton())
		{
			ResetConfig(skipIntro);
			ToggleSkipIntro(activeConfig.skipIntro);

			ResetConfig(hideMouseCursor);

			ResetConfig(baseFrameRate);
			ResetConfig(targetFrameRate);
			ResetConfig(vSync);
			ResetConfig(disableFilters);
			UpdateFrameRate();

			ResetConfig(windowPosX);
			ResetConfig(windowPosY);
			ResetConfig(borderless);
			ResetConfig(forceWindowFocus);
			g_update3D = true;
			ToggleForceWindowFocus(activeConfig.forceWindowFocus);
		}
		GUI_SectionEnd();
		ImGui::Text("");



		GUI_SectionStart("Event");

		if
		(
			GUI_Checkbox2
			(
				"Skip Intro",
				activeConfig.skipIntro,
				queuedConfig.skipIntro
			)
		)
		{
			ToggleSkipIntro(activeConfig.skipIntro);
		}

		GUI_SectionEnd();
		ImGui::Text("");



		GUI_SectionStart("Graphics");

		ImGui::PushItemWidth(150);

		if (GUI_ResetButton())
		{
			ResetConfig(baseFrameRate);
			ResetConfig(targetFrameRate);
			ResetConfig(vSync);
			ResetConfig(disableFilters);
			UpdateFrameRate();
		}
		ImGui::Text("");

		if
		(
			GUI_InputDefault2
			(
				"Base Frame Rate",
				activeConfig.baseFrameRate,
				queuedConfig.baseFrameRate,
				defaultConfig.baseFrameRate,
				1.0f,
				"%.2f",
				ImGuiInputTextFlags_EnterReturnsTrue
			)
		)
		{
			UpdateFrameRate();
		}

		if
		(
			GUI_InputDefault2
			(
				"Target Frame Rate",
				activeConfig.targetFrameRate,
				queuedConfig.targetFrameRate,
				defaultConfig.targetFrameRate,
				1.0f,
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
			activeConfig.vSync,
			queuedConfig.vSync
		);
		ImGui::Text("");

		ImGui::Text("Disable Filters");
		ImGui::SameLine();
		TooltipHelper
		(
			"(?)",
			"Requires restart to take effect."
		);
		ImGui::Text("");

		for_all(index, countof(filterHelpers))
		{
			auto & filterHelper = filterHelpers[index];

			GUI_Checkbox2
			(
				filterHelper.name,
				activeConfig.disableFilters[index],
				queuedConfig.disableFilters[index]
			);
		}

		ImGui::PopItemWidth();

		GUI_SectionEnd();
		ImGui::Text("");



		GUI_SectionStart("Input");

		GUI_Checkbox2
		(
			"Hide Mouse Cursor",
			activeConfig.hideMouseCursor,
			queuedConfig.hideMouseCursor
		);

		GUI_SectionEnd();
		ImGui::Text("");



		GUI_SectionStart("Window");

		ImGui::PushItemWidth(150);

		GUI_InputDefault2<int32>
		(
			"X",
			activeConfig.windowPosX,
			queuedConfig.windowPosX,
			defaultConfig.windowPosX,
			1,
			"%d",
			ImGuiInputTextFlags_EnterReturnsTrue
		);
		GUI_InputDefault2<int32>
		(
			"Y",
			activeConfig.windowPosY,
			queuedConfig.windowPosY,
			defaultConfig.windowPosY,
			1,
			"%d",
			ImGuiInputTextFlags_EnterReturnsTrue
		);

		ImGui::PopItemWidth();

		ImGui::Text("");

		if
		(
			GUI_Checkbox2
			(
				"Borderless",
				activeConfig.borderless,
				queuedConfig.borderless
			)
		)
		{
			g_update3D = true;
		}

		if
		(
			GUI_Checkbox2
			(
				"Force Focus",
				activeConfig.forceWindowFocus,
				queuedConfig.forceWindowFocus
			)
		)
		{
			ToggleForceWindowFocus(activeConfig.forceWindowFocus);
		}



		ImGui::Text("");
	}
}

#pragma endregion

#pragma region Training

void TrainingSection()
{
	if (ImGui::CollapsingHeader("Training"))
	{
		ImGui::Text("");



		if (GUI_ResetButton())
		{
			ResetConfig(infiniteHitPoints);
			ToggleInfiniteHitPoints(activeConfig.infiniteHitPoints);

			ResetConfig(infiniteMagicPoints);
			ToggleInfiniteMagicPoints(activeConfig.infiniteMagicPoints);

			ResetConfig(disableTimer);
			ToggleDisableTimer(activeConfig.disableTimer);
		}
		ImGui::Text("");



		if
		(
			GUI_Checkbox2
			(
				"Infinite Hit Points",
				activeConfig.infiniteHitPoints,
				queuedConfig.infiniteHitPoints
			)
		)
		{
			ToggleInfiniteHitPoints(activeConfig.infiniteHitPoints);
		}

		if
		(
			GUI_Checkbox2
			(
				"Infinite Magic Points",
				activeConfig.infiniteMagicPoints,
				queuedConfig.infiniteMagicPoints
			)
		)
		{
			ToggleInfiniteMagicPoints(activeConfig.infiniteMagicPoints);
		}

		if
		(
			GUI_Checkbox2
			(
				"Disable Timer",
				activeConfig.disableTimer,
				queuedConfig.disableTimer
			)
		)
		{
			ToggleDisableTimer(activeConfig.disableTimer);
		}



		ImGui::Text("");
	}
}

#pragma endregion

#pragma region Teleporter

// @Update

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
			//GUI_Input<uint32>("", eventData.position, 0, "%u", ImGuiInputTextFlags_ReadOnly);
			ImGui::Text("Next");
			GUI_Input<uint32>("", nextEventData.room    , 1, "%u", 0);
			GUI_Input<uint32>("", nextEventData.position, 1, "%u", 0);
			if (GUI_Button("Teleport", ImVec2(width, ImGui::GetFrameHeight())))
			{

				nextEventData.useDoor = 1;
				nextEventData.usePosition = true;



				eventData.event = EVENT::TELEPORT;
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







#pragma region Main




// @Move

void UpdateGlobalScale()
{
	auto & io = ImGui::GetIO();

	io.FontGlobalScale = activeConfig.globalScale;
}














void Main()
{
	static bool run = false;

	if (!run)
	{
		run = true;

		ImGui::SetNextWindowSize(ImVec2(600, 650));

		if constexpr (debug)
		{
			ImGui::SetNextWindowPos(ImVec2(950, 50));
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

	if
	(
		ImGui::Begin
		(
			DDMK_TITLE_KYRIE,
			&g_show
		)
	)
	{
		ImGui::Text("");



		ImGui::PushItemWidth(150);

		if
		(
			GUI_InputDefault2
			(
				"Global Scale",
				activeConfig.globalScale,
				queuedConfig.globalScale,
				defaultConfig.globalScale,
				0.1f,
				"%g",
				ImGuiInputTextFlags_EnterReturnsTrue
			)
		)
		{
			UpdateGlobalScale();
		}

		ImGui::PopItemWidth();

		ImGui::Text("");



		ImGui::Text(PATREON_TEXT);
		ImGui::Text("");

		if (GUI_Button("Open Patreon Page"))
		{
			ShellExecuteA
			(
				0,
				"open",
				PATREON_LINK,
				0,
				0,
				SW_SHOW
			);
		}
		ImGui::Text("");



		ActorSection();
		ArcadeSection();
		BarsSection();
		CameraSection();
		Overlays();
		SpeedSection();
		System();
		Teleporter();
		TrainingSection();

		ImGui::Text("");

		GUI_Checkbox2
		(
			"Show Credits",
			activeConfig.showCredits,
			queuedConfig.showCredits
		);









		// ImGui::PushItemWidth(200.0f);

		// GUI_Input
		// (
		// 	"scrollSpeedY",
		// 	scrollSpeedY,
		// 	0.1f,
		// 	"%g"
		// );

		// ImGui::PopItemWidth();










		ImGui::Text("");
	}

	ImGui::End();
}

#pragma endregion



export void GUI_Render()
{
	GUI_id = 0;

	MainOverlayWindow();

	Bars();




	if (g_show)
	{
		Main();


		CreditsWindow();
	}



	[&]()
	{
		using namespace GUI;

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

	UpdateGlobalScale();

	//Actor_UpdateIndices();
	Arcade_UpdateIndices();
	// MissionSelect_UpdateIndices();
}









