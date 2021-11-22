module;
#include "ThirdParty/ImGui/imgui.h"
#include "ThirdParty/ImGui/imgui_internal.h"

#include <stdio.h>
export module GUIBase;

import Core;
import Core_GUI;

#include "Core/Macros.h"

import Windows;

using namespace Windows;

import Config;
import GlobalBase;

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



export void Welcome()
{
	if (!queuedConfig.welcome)
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
			&queuedConfig.welcome,
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
