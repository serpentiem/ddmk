module;
#include "ThirdParty/ImGui/imgui.h"
#include "ThirdParty/ImGui/imgui_internal.h"

#include <stdio.h>
export module GUIBase;

import Core;
import Core_GUI;
import Core_ImGui;
import Core_Input;

#include "Core/Macros.h"

import Windows;
import D3D10;
import DI8;
import XI;

using namespace Windows;

import Config;
import GlobalBase;
import Global;

#define debug false



export namespaceStart(FONT);
enum
{
	DEFAULT,
	OVERLAY_8,
	OVERLAY_16,
	OVERLAY_32,
	OVERLAY_64,
	OVERLAY_128,
};
namespaceEnd();



export void BuildFonts()
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



	io.Fonts->AddFontFromFileTTF(overlayFont, 8  );
	io.Fonts->AddFontFromFileTTF(overlayFont, 16 );
	io.Fonts->AddFontFromFileTTF(overlayFont, 32 );
	io.Fonts->AddFontFromFileTTF(overlayFont, 64 );
	io.Fonts->AddFontFromFileTTF(overlayFont, 128);



	io.Fonts->Build();
}



export void UpdateGlobalScale()
{
	auto & io = ImGui::GetIO();

	io.FontGlobalScale = activeConfig.globalScale;
}

export void GUI_UpdateStyle()
{
	auto & style = ImGui::GetStyle();

	style.WindowRounding    = 7.0f;
	style.ScrollbarRounding = 9.0f;
}



export void CreditsWindow()
{
	if
	(
		!g_showMain ||
		!activeConfig.showCredits
	)
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
			ImGuiWindowFlags_NoTitleBar        |
			ImGuiWindowFlags_NoResize          |
			ImGuiWindowFlags_NoMove            |
			ImGuiWindowFlags_NoScrollbar       |
			ImGuiWindowFlags_NoScrollWithMouse |
			ImGuiWindowFlags_NoMouseInputs     |
			ImGuiWindowFlags_NoFocusOnAppearing
		)
	)
	{
		ImGui::Text("");


		constexpr float scrollSpeedY = 1.0f;
		constexpr new_size_t padding = 30;

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



export void Welcome()
{
	if (!activeConfig.welcome)
	{
		return;
	}



	static bool run = false;

	if (!run)
	{
		run = true;

		constexpr float width  = 350;
		constexpr float height = 130;

		ImGui::SetNextWindowSize(ImVec2(width, height));

		ImGui::SetNextWindowPos
		(
			ImVec2
			(
				((g_renderSize.x - width ) / 2),
				((g_renderSize.y - height) / 2)
			)
		);
	}

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);

	if
	(
		ImGui::Begin
		(
			"Welcome",
			&activeConfig.welcome,
			ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoResize   |
			ImGuiWindowFlags_NoMove     |
			ImGuiWindowFlags_NoScrollbar
		)
	)
	{
		ImGui::Text("");

		CenterText(WELCOME_TEXT);
		ImGui::Text("");

		if (CenterButton("Close"))
		{
			activeConfig.welcome = queuedConfig.welcome = false;

			SaveConfig();
		}

		ImGui::Text("");
	}

	ImGui::End();

	ImGui::PopStyleVar();
}











// @Order

export void ResetNavId()
{
	auto contextAddr = ImGui::GetCurrentContext();
	if (!contextAddr)
	{
		return;
	}
	auto & context = *contextAddr;

	context.NavId = 0;
}






export typedef void(* GamepadClose_func_t)();

export void GamepadClose
(
	bool & visible,
	bool & lastVisible,
	GamepadClose_func_t func
)
{
	auto & io = ImGui::GetIO();



	if (!ImGui::IsWindowFocused())
	{
		visible = false;

		return;
	}



	visible = io.NavVisible;

	if (lastVisible != visible)
	{
		if (io.NavInputs[ImGuiNavInput_Cancel] > 0)
		{
			return;
		}

		lastVisible = visible;
	}

	if
	(
		visible ||
		lastVisible
	)
	{
		return;
	}



	static bool execute = false; // Should be fine here, since only 1 window can be active at all times.

	if (io.NavInputs[ImGuiNavInput_Cancel] > 0)
	{
		if (execute)
		{
			execute = false;

			func();
		}
	}
	else
	{
		execute = true;
	}
}














export void OpenMain()
{
	DebugLogFunction();

	g_showMain = true;



	// Required here since g_show could be false, but we still need the data.
	// Otherwise the menu could auto-close.

	using namespace XI;

	new_XInputGetState
	(
		0,
		&state
	);

	::ImGui::XI::UpdateGamepad(&state);
}

export void CloseMain()
{
	DebugLogFunction();

	g_showMain = false;
}

export void ToggleShowMain()
{
	DebugLogFunction();

	if (!g_showMain)
	{
		OpenMain();
	}
	else
	{
		CloseMain();
	}
}







export template <typename T>
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
			ImGuiWindowFlags_NoTitleBar         |
			ImGuiWindowFlags_AlwaysAutoResize   |
			ImGuiWindowFlags_NoFocusOnAppearing
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



export template
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



export template <typename T>
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








export void HandleSaveTimer(float frameRate)
{


	using namespace GUI;



	if (saveTimer > 0)
	{
		saveTimer -= 1.0f;

		return;
	}

	saveTimer = (frameRate * (saveTimeout / 1000));

	// Log("__GUI__");



	if (save)
	{
		save = false;

		SaveConfig();
	}



}


export void HandleKeyBindings
(
	KeyBinding * keyBindings,
	new_size_t count
)
{
	for_all(index, count)
	{
		auto & keyBinding = keyBindings[index];

		keyBinding.Popup();
	}
}




















