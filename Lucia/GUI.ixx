module;
#include "../ImGui/imgui.h"
#include "../ImGui/imgui_internal.h"

#include <stdio.h>
export module GUI;

import Core;

#include "../Core/Macros.h"
#include "../Global.h"

import Vars;

import Windows;
import DXGI;
import D3D11;

import Core_GUI;



import Config;
import Global;
import Graphics;
import Window;

using namespace Windows;
using namespace DXGI;
using namespace D3D11;

#define debug false

#include "Macros.h"



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

const char * Graphics_vSyncNames[] =
{
	"Auto",
	"Force Off",
	"Force On",
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
			// ResetConfig(newMovesOverlayDataBossLady  );
			// ResetConfig(newMovesOverlayDataBossVergil);

			ImGui::SetWindowPos(mainOverlayLabel              , *reinterpret_cast<ImVec2*>(&activeConfig.mainOverlayData.pos              ));
			// ImGui::SetWindowPos(missionOverlayLabel           , *reinterpret_cast<ImVec2*>(&activeConfig.missionOverlayData.pos           ));
			// ImGui::SetWindowPos(newMovesOverlayLabelDante     , *reinterpret_cast<ImVec2*>(&activeConfig.newMovesOverlayDataDante.pos     ));
			// ImGui::SetWindowPos(newMovesOverlayLabelVergil    , *reinterpret_cast<ImVec2*>(&activeConfig.newMovesOverlayDataVergil.pos    ));
			// ImGui::SetWindowPos(newMovesOverlayLabelBossLady  , *reinterpret_cast<ImVec2*>(&activeConfig.newMovesOverlayDataBossLady.pos  ));
			// ImGui::SetWindowPos(newMovesOverlayLabelBossVergil, *reinterpret_cast<ImVec2*>(&activeConfig.newMovesOverlayDataBossVergil.pos));
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



void ToggleShow()
{
	g_show = !g_show;
}

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
		ToggleShow,
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
	// static bool run = false;

	// if (!run)
	// {
	// 	run = true;

	// 	// LogFunction();

	// 	//CreateTextures();
	// }

	::GUI::id = 0;

	MainOverlayWindow();

	// if constexpr (debug)
	// {
	// 	Overlay2Window();
	// }

	// MissionOverlayWindow();

	// NewMovesOverlayWindowDante();
	// NewMovesOverlayWindowVergil();
	// NewMovesOverlayWindowBossLady();
	// NewMovesOverlayWindowBossVergil();





	//BossVergilOverlayWindow();

	// WeaponSwitchController();





	// if (showActorWindow)
	// {
	// 	ActorWindow();
	// }



	if (g_show)
	{
		Main();

		CreditsWindow();

		// if constexpr (debug)
		// {

		// 	MissionDataWindow();


		// 	FileDataWindow();
			
		// 	EventDataWindow();
		// 	RegionDataWindow();
		// 	SoundWindow();
		// }
	}


	for_all(index, countof(keyBindings))
	{
		auto & keyBinding = keyBindings[index];

		keyBinding.Popup();
	}








	[&]()
	{
		auto & save        = GUI::save;
		auto & saveTimeout = GUI::saveTimeout;

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

	// for_all(index, 21)
	// {
	// 	Log("%.4llu %llu", index, helper[index]);
	// 	//Log("%.4llu %llu", index, helper.data[index]);
	// }




	BuildFonts();

	UpdateGlobalScale();

	// Actor_UpdateIndices();
	// Arcade_UpdateIndices();
	// MissionSelect_UpdateIndices();
}

#ifdef __GARBAGE__
#endif