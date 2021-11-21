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
	//MAIN,
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

	// io.Fonts->AddFontFromFileTTF(overlayFont, 13 );
	// io.Fonts->AddFontFromFileTTF(overlayFont, 17 );
	io.Fonts->AddFontFromFileTTF(overlayFont, 8  );
	io.Fonts->AddFontFromFileTTF(overlayFont, 16 );
	io.Fonts->AddFontFromFileTTF(overlayFont, 32 );
	io.Fonts->AddFontFromFileTTF(overlayFont, 64 );
	io.Fonts->AddFontFromFileTTF(overlayFont, 128);





	// const char * locations[] =
	// {
	// 	"C:/Windows/Fonts/consola.ttf",
	// 	"C:/Users/serpentiem/source/repos/ddmk/ThirdParty/ImGui/misc/fonts/Cousine-Regular.ttf",
	// 	"C:/Users/serpentiem/source/repos/ddmk/ThirdParty/ImGui/misc/fonts/DroidSans.ttf",
	// 	"C:/Users/serpentiem/source/repos/ddmk/ThirdParty/ImGui/misc/fonts/Karla-Regular.ttf",
	// 	"C:/Users/serpentiem/source/repos/ddmk/ThirdParty/ImGui/misc/fonts/Roboto-Medium.ttf",
	// };

	// for_all(locationIndex, countof(locations))
	// {
	// 	auto location = locations[locationIndex];

	// 	for_all(index, 10)
	// 	{
	// 		io.Fonts->AddFontFromFileTTF(location, static_cast<float>(13 + index));
	// 	}
	// }
















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
			ImGuiWindowFlags_NoMouseInputs
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
