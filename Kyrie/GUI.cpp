#include "GUI.h"


enum TAB_
{
	TAB_GAME,
	TAB_SYSTEM,
	TAB_TOOLS,
	TAB_DEBUG,
	MAX_TAB,
	TAB_VOID,
};


enum FONT_
{
	FONT_DEFAULT,
	FONT_RESTART,
	FONT_OVERLAY_8,
	FONT_OVERLAY_16,
	FONT_OVERLAY_24,
	FONT_OVERLAY_32,
	FONT_OVERLAY_40,
	FONT_OVERLAY_48,
	FONT_OVERLAY_56,
	FONT_OVERLAY_64,
};

#define OVERLAY_FONT "C:\\Windows\\Fonts\\consola.ttf"

















uint8 activeTab = TAB_VOID;

ImVec2 GUI_Game_size          = ImVec2(500, 500);
ImVec2 GUI_System_size        = ImVec2(300, 418);
ImVec2 GUI_Tools_size         = ImVec2(300, 300);
ImVec2 GUI_Debug_size         = ImVec2(300, 300);

bool debug   = false;
bool restart = false;










inline void BuildFonts()
{
	ImGuiIO & io = ImGui::GetIO();
	io.Fonts->AddFontDefault();
	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\consola.ttf", 128);
	io.Fonts->AddFontFromFileTTF(OVERLAY_FONT, 8);
	io.Fonts->AddFontFromFileTTF(OVERLAY_FONT, 16);
	io.Fonts->AddFontFromFileTTF(OVERLAY_FONT, 24);
	io.Fonts->AddFontFromFileTTF(OVERLAY_FONT, 32);
	io.Fonts->AddFontFromFileTTF(OVERLAY_FONT, 40);
	io.Fonts->AddFontFromFileTTF(OVERLAY_FONT, 48);
	io.Fonts->AddFontFromFileTTF(OVERLAY_FONT, 56);
	io.Fonts->AddFontFromFileTTF(OVERLAY_FONT, 64);
	io.Fonts->Build();
}

















void GUI_Game_Draw()
{
	static bool run = false;
	if (!run)
	{
		run = true;
		ImGui::SetNextWindowSize(ImVec2(GUI_Game_size.x + 16, GUI_Game_size.y + 16));
		ImGui::SetNextWindowPos(ImVec2(0, 25));
	}
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(1, 1));
	if (ImGui::Begin("GUI_Game", &pause, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
	{
		ImGui::Text("GUI_Game");
	}
	ImGui::End();
	ImGui::PopStyleVar(3);
}


void GUI_System_Draw()
{
	static bool run = false;
	if (!run)
	{
		run = true;
		ImGui::SetNextWindowSize(ImVec2(GUI_System_size.x + 16, GUI_System_size.y + 16));
		ImGui::SetNextWindowPos(ImVec2(0, 25));
	}
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(1, 1));
	if (ImGui::Begin("GUI_System", &pause, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
	{
		ImGui::Text("GUI_System");
	}
	ImGui::End();
	ImGui::PopStyleVar(3);
}


void GUI_Tools_Draw()
{
	static bool run = false;
	if (!run)
	{
		run = true;
		ImGui::SetNextWindowSize(ImVec2(GUI_Tools_size.x + 16, GUI_Tools_size.y + 16));
		ImGui::SetNextWindowPos(ImVec2(0, 25));
	}
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(1, 1));
	if (ImGui::Begin("GUI_Tools", &pause, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
	{
		
		ImGui::Text("GUI_Tools");

	}
	ImGui::End();
	ImGui::PopStyleVar(3);
}


void GUI_Debug_Draw()
{
	static bool run = false;
	if (!run)
	{
		run = true;
		ImGui::SetNextWindowSize(ImVec2(GUI_Tools_size.x + 16, GUI_Tools_size.y + 16));
		ImGui::SetNextWindowPos(ImVec2(0, 25));
	}
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(1, 1));
	if (ImGui::Begin("GUI_Debug", &pause, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
	{
		ImGui::Text("GUI_Debug");
	}
	ImGui::End();
	ImGui::PopStyleVar(3);
}



void GUI_Main_Tab(const char * str, uint8 index)
{
	ImVec2 pos = ImGui::GetCursorPos();
	bool selected = activeTab == index ? true : false;
	ImVec2 size = ImVec2(100, 20);
	ImGui::PushID(GUI_id);
	GUI_id++;
	if (ImGui::Selectable("", &selected, 0, size))
	{
		activeTab = activeTab == index ? TAB_VOID : index;
	}
	ImGui::PopID();
	ImVec2 len = ImGui::CalcTextSize(str);
	if ((uint32)len.x % 2)
	{
		len.x += 1.0f;
	}
	if ((uint32)len.y % 2)
	{
		len.y += 1.0f;
	}
	float32 x = pos.x + ((size.x - len.x) / 2);
	float32 y = pos.y + ((size.y - len.y) / 2);
	ImGui::SetCursorPos(ImVec2(x, y));
	ImGui::RenderText(ImGui::GetCurrentWindow()->DC.CursorPos, str);
	ImGui::SetCursorPos(ImVec2(pos.x + size.x + 8.0f, pos.y));
}

void GUI_Main_Draw()
{
	static bool run = false;
	if (!run)
	{
		run = true;
		ImGui::SetNextWindowSize(ImVec2((float32)System_Window_width, 25));
		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::GetStyle().ScrollbarRounding = 0;
	}
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(1, 1));
	if (ImGui::Begin("GUI_Main", &pause, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
	{
		ImGui::SetCursorPos(ImVec2(4, 2));
		for (uint8 i = 0; i < MAX_TAB; i++)
		{
			GUI_Main_Tab(Locale.Main.label[i], i);
		}
		ImGui::SetCursorPos(ImVec2(0, 24));
		ImGui::Separator();
		ImGui::End();
	}
	ImGui::PopStyleVar(4);
	switch (activeTab)
	{
	case TAB_GAME:
		GUI_Game_Draw();
		break;
	case TAB_SYSTEM:
		GUI_System_Draw();
		break;
	case TAB_TOOLS:
		GUI_Tools_Draw();
		break;
	case TAB_DEBUG:
		GUI_Debug_Draw();
		break;
	}
}






void GUI_Render()
{
	GUI_id = 0;
	if (pause)
	{
		GUI_Main_Draw();
	}
}

void GUI_Init()
{
	BuildFonts();
}


