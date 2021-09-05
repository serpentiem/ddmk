module;
#include "../ImGui/imgui.h"

#include <stdio.h>
export module GUI;

import Core;

#include "../Core/Macros.h"

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



#pragma region Common

const char * Graphics_vSyncNames[] =
{
	"Auto",
	"Force Off",
	"Force On",
};

// const char * buttonNames[] =
// {
// 	"Nothing",
// 	"Left Trigger",
// 	"Right Trigger",
// 	"Left Shoulder",
// 	"Right Shoulder",
// 	"Y",
// 	"B",
// 	"A",
// 	"X",
// 	"Back",
// 	"Left Thumb",
// 	"Right Thumb",
// 	"Start",
// 	"Up",
// 	"Right",
// 	"Down",
// 	"Left",
// };

// byte16 buttons[] =
// {
// 	0,
// 	GAMEPAD::LEFT_TRIGGER,
// 	GAMEPAD::RIGHT_TRIGGER,
// 	GAMEPAD::LEFT_SHOULDER,
// 	GAMEPAD::RIGHT_SHOULDER,
// 	GAMEPAD::Y,
// 	GAMEPAD::B,
// 	GAMEPAD::A,
// 	GAMEPAD::X,
// 	GAMEPAD::BACK,
// 	GAMEPAD::LEFT_THUMB,
// 	GAMEPAD::RIGHT_THUMB,
// 	GAMEPAD::START,
// 	GAMEPAD::UP,
// 	GAMEPAD::RIGHT,
// 	GAMEPAD::DOWN,
// 	GAMEPAD::LEFT,
// };

// const char * missionNames[] =
// {
// 	"Prologue",
// 	"Mission 1",
// 	"Mission 2",
// 	"Mission 3",
// 	"Mission 4",
// 	"Mission 5",
// 	"Mission 6",
// 	"Mission 7",
// 	"Mission 8",
// 	"Mission 9",
// 	"Mission 10",
// 	"Mission 11",
// 	"Mission 12",
// 	"Mission 13",
// 	"Mission 14",
// 	"Mission 15",
// 	"Mission 16",
// 	"Mission 17",
// 	"Mission 18",
// 	"Mission 19",
// 	"Mission 20",
// 	"Mission 21",
// 	"Mission 22",
// 	"Mission 23",
// 	"Mission 24",
// };

// const char * modeNames[] =
// {
// 	"Easy",
// 	"Normal",
// 	"Hard",
// 	"Dante Must Die",
// };

// uint8 modes[] =
// {
// 	MODE::EASY,
// 	MODE::NORMAL,
// 	MODE::HARD,
// 	MODE::DANTE_MUST_DIE,
// };

// const char * characterNames[] =
// {
// 	"Dante",
// 	"LDK",
// 	"Super Dante",
// };

// const char * meleeWeaponNames[] =
// {
// 	"Force Edge",
// 	"Alastor",
// 	"Ifrit",
// 	"Sparda",
// };

// uint8 meleeWeapons[] =
// {
// 	WEAPON::FORCE_EDGE,
// 	WEAPON::ALASTOR,
// 	WEAPON::IFRIT,
// 	WEAPON::SPARDA,
// };

// const char * meleeWeaponFormNames[] =
// {
// 	"Default",
// 	"Sparda",
// 	"Yamato",
// };

// const char * rangedWeaponNames[] =
// {
// 	"Handgun",
// 	"Shotgun",
// 	"Grenadegun",
// 	"Nightmare Beta",
// };

// uint8 rangedWeapons[] =
// {
// 	WEAPON::HANDGUN,
// 	WEAPON::SHOTGUN,
// 	WEAPON::GRENADEGUN,
// 	WEAPON::NIGHTMARE_BETA,
// };



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

			GUI_save = true;
		}

		auto & io = ImGui::GetIO();
		ImGui::PushFont(io.Fonts->Fonts[FONT_OVERLAY_16]);

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

		//ImGui::Text("Borderless %u", IsBorderless());


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
			ImGui::Text("");
		}

		// if (activeConfig.mainOverlayData.showEventData)
		// {
		// 	[&]()
		// 	{
		// 		IntroduceSessionData(return);
		// 		IntroduceEventData(return);

		// 		ImGui::Text("event     %.8X", sessionData.event  );
		// 		ImGui::Text("track     %u"  , eventData.track    );
		// 		ImGui::Text("room      %u"  , eventData.room     );
		// 		ImGui::Text("nextTrack %u"  , eventData.nextTrack);
		// 		ImGui::Text("nextRoom  %u"  , eventData.nextRoom );
		// 	}();
		// 	ImGui::Text("");
		// }

		// if (activeConfig.mainOverlayData.showPosition)
		// {
		// 	[&]()
		// 	{
		// 		IntroduceMainActorData(actorData, return);

		// 		ImGui::Text("X        %g", actorData.position.x);
		// 		ImGui::Text("Y        %g", actorData.position.y);
		// 		ImGui::Text("Z        %g", actorData.position.z);
		// 		ImGui::Text("Rotation %g", actorData.rotation  );
		// 	}();
		// 	ImGui::Text("");
		// }

		// if constexpr (debug)
		// {
		// 	ImGui::Text("meleeWeaponIndex  %u", activeConfig.Actor.meleeWeaponIndex );
		// 	ImGui::Text("rangedWeaponIndex %u", activeConfig.Actor.rangedWeaponIndex);
		// 	ImGui::Text("");

		// 	[&]()
		// 	{
		// 		IntroduceSessionData(return);
		// 		IntroduceMainActorData(actorData, return);

		// 		ImGui::Text("state %X", sessionData.state);
		// 		ImGui::Text("");

		// 		new_for_all(index, 8)
		// 		{
		// 			ImGui::Text("state[%u] %X", index, actorData.state[index]);
		// 		}
		// 		ImGui::Text("");

		// 		ImGui::Text("state[1] %u", actorData.state[1]);
		// 		ImGui::Text("");

		// 		{
		// 			auto color = ImVec4(0, 1, 0, 1);

		// 			if (sessionData.state & 0x200)
		// 			{
		// 				color = ImVec4(1, 0, 0, 1);
		// 			}

		// 			ImGui::PushStyleColor(ImGuiCol_Text, color);

		// 			ImGui::Text("Busy");

		// 			ImGui::PopStyleColor();
		// 		}
		// 	}();
		// }
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
			GUI_InputDefault2
			(
				"Frame Rate",
				activeConfig.frameRate,
				queuedConfig.frameRate,
				defaultConfig.frameRate,
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
		//io.FontDefault = io.Fonts->Fonts[FONT_MAIN];
		//ImGui::PushFont(io.Fonts->Fonts[FONT_OVERLAY_8 + activeConfig.Tools.Overlay.fontSizeIndex]);

		//ImGui::SetCurrentFont(io.Fonts->Fonts[FONT_OVERLAY_8]);
	}

	if
	(
		ImGui::Begin
		(
			"DDMK 2.7 Lucia Nightly 5 September 2021",
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



		ImGui::Text
		(
			"If you like my work and wish to support me, consider becoming my patron.\n"
			"You can click on the button below to open my Patreon page.\n"
			"\n"
			"Cheers!"
		);
		ImGui::Text("");

		if (GUI_Button("Open Patreon Page"))
		{
			ShellExecuteA
			(
				0,
				"open",
				"https://www.patreon.com/serpentiem",
				0,
				0,
				SW_SHOW
			);
		}
		ImGui::Text("");





		Overlays();
		System();



		ImGui::Text("");
	}

	ImGui::End();
}

#pragma endregion




































export void GUI_Render()
{
	static bool run = false;

	if (!run)
	{
		run = true;

		// LogFunction();

		//CreateTextures();
	}

	GUI_id = 0;

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

		// if constexpr (debug)
		// {

		// 	MissionDataWindow();


		// 	FileDataWindow();
			
		// 	EventDataWindow();
		// 	RegionDataWindow();
		// 	SoundWindow();
		// }
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

	UpdateGlobalScale();

	// Actor_UpdateIndices();
	// Arcade_UpdateIndices();
	// MissionSelect_UpdateIndices();
}

#ifdef __GARBAGE__
#endif
