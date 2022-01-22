module;
#include "../ThirdParty/ImGui/imgui.h"
#include "../ThirdParty/ImGui/imgui_internal.h"

#include <stdio.h>
export module GUI;

import Core;
import Core_GUI;
import Core_ImGui;

#include "../Core/Macros.h"

import Windows;

using namespace Windows;

import GlobalBase;
import GUIBase;

import Config;
import Global;
import Graphics;
import Vars;
import Window;

#define debug true



bool visibleMain     = false;
bool lastVisibleMain = false;



#pragma region Common

const char * Graphics_vSyncNames[] =
{
	"Auto",
	"Force Off",
	"Force On",
};

#pragma endregion









#pragma region Overlays











const char * mainOverlayLabel = "MainOverlay";

void MainOverlayWindow()
{
	auto Function = [&]()
	{
		if (activeConfig.mainOverlayData.showFocus)
		{
			auto color = ImVec4(0, 1, 0, 1);
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
			ResetConfig(mainOverlayData              );
			// ResetConfig(missionOverlayData           );
			// ResetConfig(newMovesOverlayDataDante     );
			// ResetConfig(newMovesOverlayDataVergil    );
			// ResetConfig(bossLadyActionsOverlayData  );
			// ResetConfig(bossVergilActionsOverlayData);

			ImGui::SetWindowPos(mainOverlayLabel              , *reinterpret_cast<ImVec2*>(&activeConfig.mainOverlayData.pos              ));
			// ImGui::SetWindowPos(missionOverlayLabel           , *reinterpret_cast<ImVec2*>(&activeConfig.missionOverlayData.pos           ));
			// ImGui::SetWindowPos(newMovesOverlayLabelDante     , *reinterpret_cast<ImVec2*>(&activeConfig.newMovesOverlayDataDante.pos     ));
			// ImGui::SetWindowPos(newMovesOverlayLabelVergil    , *reinterpret_cast<ImVec2*>(&activeConfig.newMovesOverlayDataVergil.pos    ));
			// ImGui::SetWindowPos(newMovesOverlayLabelBossLady  , *reinterpret_cast<ImVec2*>(&activeConfig.bossLadyActionsOverlayData.pos  ));
			// ImGui::SetWindowPos(newMovesOverlayLabelBossVergil, *reinterpret_cast<ImVec2*>(&activeConfig.bossVergilActionsOverlayData.pos));
		}

		GUI_SectionEnd();
		ImGui::Text("");

		GUI_SectionStart("Main");

		MainOverlaySettings();

		// GUI_SectionEnd();
		// ImGui::Text("");



		// if constexpr (debug)
		// {
		// 	GUI_SectionStart("2");

		// 	Overlay2Settings();

		// 	GUI_SectionEnd();
		// 	ImGui::Text("");
		// }



		// GUI_SectionStart("Mission");

		// MissionOverlaySettings();

		// GUI_SectionEnd();
		// ImGui::Text("");



		// GUI_SectionStart("New Moves Dante");

		// NewMovesOverlaySettingsDante();

		// GUI_SectionEnd();
		// ImGui::Text("");



		// GUI_SectionStart("New Moves Vergil");

		// NewMovesOverlaySettingsVergil();

		// GUI_SectionEnd();
		// ImGui::Text("");



		// GUI_SectionStart("New Moves Boss Lady");

		// NewMovesOverlaySettingsBossLady();

		// GUI_SectionEnd();
		// ImGui::Text("");



		// GUI_SectionStart("New Moves Boss Vergil");

		// NewMovesOverlaySettingsBossVergil();








		ImGui::Text("");
	}
}




#pragma endregion




#pragma region System

void System()
{
	if (ImGui::CollapsingHeader("System"))
	{
		ImGui::Text("");

		if (GUI_ResetButton())
		{
			ResetConfig(frameRate);
			ResetConfig(vSync);
			UpdateFrameRate();

			ResetConfig(hideMouseCursor);

			ResetConfig(windowPosX);
			ResetConfig(windowPosY);
			ResetConfig(forceWindowFocus);
			ToggleForceWindowFocus(activeConfig.forceWindowFocus);
		}
		// GUI_SectionEnd();
		// ImGui::Text("");







		GUI_SectionEnd();
		ImGui::Text("");



		GUI_SectionStart("Graphics");

		ImGui::PushItemWidth(150);

		if (GUI_ResetButton())
		{
			ResetConfig(frameRate);
			ResetConfig(vSync);

			UpdateFrameRate();
		}
		ImGui::Text("");

		if
		(
			GUI_InputDefault2<float>
			(
				"Frame Rate",
				activeConfig.frameRate,
				queuedConfig.frameRate,
				defaultConfig.frameRate,
				1,
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






#pragma region Key Bindings



// void ToggleShow()
// {
// 	g_show = !g_show;
// }

// void ReloadRoom()
// {
// 	if (!InGame())
// 	{
// 		return;
// 	}

// 	IntroduceEventData(return);
// 	IntroduceNextEventData(return);



// 	nextEventData.room = eventData.room;
// 	nextEventData.position = g_position;


// 	nextEventData.useDoor = 1;
// 	nextEventData.usePosition = true;



// 	eventData.event = EVENT::TELEPORT;




// }




// void MoveToMainActor()
// {
// 	if
// 	(
// 		!activeConfig.Actor.enable ||
// 		!InGame()
// 	)
// 	{
// 		return;
// 	}

// 	LogFunction();

// 	IntroduceData(g_newActorData[0].baseAddr, mainActorData, PlayerActorData, return);

// 	for_each(playerIndex, 1, activeConfig.Actor.playerCount)
// 	{
// 		IntroduceData(g_newActorData[playerIndex].baseAddr, actorData, PlayerActorData, continue);

// 		actorData.position = mainActorData.position;
// 	}
// }








export KeyBinding keyBindings[] =
{
	{
		"Toggle Show",
		activeConfig.keyData[0],
		queuedConfig.keyData[0],
		defaultConfig.keyData[0],
		ToggleShowMain,
		KeyFlags_AtLeastOneKey
	},
	// {
	// 	"Reload Room",
	// 	activeConfig.keyData[1],
	// 	queuedConfig.keyData[1],
	// 	defaultConfig.keyData[1],
	// 	ReloadRoom
	// },
	// {
	// 	"Move To Main Actor",
	// 	activeConfig.keyData[2],
	// 	queuedConfig.keyData[2],
	// 	defaultConfig.keyData[2],
	// 	MoveToMainActor
	// },
};



void KeyBindings()
{
	if (ImGui::CollapsingHeader("Key Bindings"))
	{
		ImGui::Text("");

		// DescriptionHelper("");
		// ImGui::Text("");




		bool condition = false;

		for_all(index, countof(keyBindings))
		{
			auto & keyBinding = keyBindings[index];

			if (keyBinding.showPopup)
			{
				condition = true;

				break;
			}
		}

		GUI_PushDisable(condition);

		for_all(index, countof(keyBindings))
		{
			auto & keyBinding = keyBindings[index];

			keyBinding.Main();
		}

		GUI_PopDisable(condition);






		ImGui::Text("");
	}
}














#pragma endregion











#pragma region Main






void UpdateGlobalScale()
{
	auto & io = ImGui::GetIO();

	io.FontGlobalScale = activeConfig.globalScale;
}






void Main()
{



	if (!g_showMain)
	{
		return;
	}




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
		//io.FontDefault = io.Fonts->Fonts[FONT::MAIN];
		//ImGui::PushFont(io.Fonts->Fonts[FONT::OVERLAY_8 + activeConfig.Tools.Overlay.fontSizeIndex]);

		//ImGui::SetCurrentFont(io.Fonts->Fonts[FONT::OVERLAY_8]);
	}

	if
	(
		ImGui::Begin
		(
			DDMK_TITLE_LUCIA,
			//"DDMK 2.7 Lucia Nightly 5 September 2021",
			&g_showMain
		)
	)
	{
		ImGui::Text("");





		GamepadClose
		(
			visibleMain,
			lastVisibleMain,
			CloseMain
		);




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




		KeyBindings();
		Overlays();
		System();

		ImGui::Text("");

		GUI_Checkbox2
		(
			"Show Credits",
			activeConfig.showCredits,
			queuedConfig.showCredits
		);




		ImGui::Text("");
	}

	ImGui::End();
}

#pragma endregion



export void GUI_Render()
{
	::GUI::id = 0;



	Welcome();
	Main();
	CreditsWindow();



	MainOverlayWindow();



	HandleKeyBindings
	(
		keyBindings,
		countof(keyBindings)
	);



	HandleSaveTimer(activeConfig.frameRate);



	// static bool enable = true;
	// ImGui::ShowDemoWindow(&enable);
}

export void GUI_Init()
{
	LogFunction();

	BuildFonts();

	UpdateGlobalScale();

	GUI_UpdateStyle();
}
