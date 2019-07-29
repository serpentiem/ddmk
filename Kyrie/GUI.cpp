#include "GUI.h"

//#pragma warning(disable: 4102) // Unreferenced label.


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

ImVec2 GUI_Teleporter_size    = ImVec2(300, 300);




bool debug   = false;
//bool restart = false;


bool GUI_Teleporter_show = false;







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











void GUI_Game_Multiplayer()
{
	GUI_Hyperlink(Locale.Game.Multiplayer.header);
	ImGui::Text("");
	GUI_PUSH_DISABLE(InMission());
	{
		if (GUI_Checkbox(Locale.Game.Multiplayer.enable, Config.Game.Multiplayer.enable))
		{
			EvaluateApplicationRestart();
		}
		ImGui::Text("");
		GUI_PUSH_DISABLE(!Config.Game.Multiplayer.enable);
		{
			ImGui::PushItemWidth(100);
			GUI_Slider("", Config.Game.Multiplayer.actorCount, 1, (MAX_ACTOR - 1));
			for (uint8 i = 0; i < (MAX_ACTOR - 1); i++)
			{
				bool skip = (i >= Config.Game.Multiplayer.actorCount) ? true : false;
				GUI_PUSH_DISABLE(skip);
				GUI_Combo<uint8>
				(
					"",
					Locale.Game.Multiplayer.Character.items,
					countof(Locale.Game.Multiplayer.Character.items),
					Config.Game.Multiplayer.character[i]
				);
				ImGui::SameLine();
				GUI_InputEx<uint8>("", Config.Game.Multiplayer.costume[i]);
				GUI_POP_DISABLE(skip);
			}
			ImGui::PopItemWidth();
		}
		GUI_POP_DISABLE(!Config.Game.Multiplayer.enable);
		ImGui::Text("");
		if (GUI_Button(Locale.Game.Multiplayer.reset))
		{
			memcpy(&Config.Game.Multiplayer, &DefaultConfig.Game.Multiplayer, sizeof(Config.Game.Multiplayer));
			SaveConfig();
			EvaluateApplicationRestart();
		}
	}
	GUI_POP_DISABLE(InMission());
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

		GUI_Game_Multiplayer();
		ImGui::Text("");

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



		ImGui::Text(Locale.System.Media.header);
		ImGui::Text("");





		if (GUI_Checkbox(Locale.System.Media.skipIntro, Config.System.Media.skipIntro))
		{
			//System_Media_ToggleSkipIntro(Config.System.Media.skipIntro);
		}
		GUI_PUSH_DISABLE(!Config.System.Media.skipIntro);
		ImGui::PushItemWidth(150);
		GUI_Combo<uint32>
		(
			Locale.System.Media.skipIntroGame.label,
			Locale.System.Media.skipIntroGame.items,
			countof(Locale.System.Media.skipIntroGame.items),
			Config.System.Media.skipIntroGame
		);
		ImGui::PopItemWidth();
		GUI_POP_DISABLE(!Config.System.Media.skipIntro);










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
		
		//ImGui::Text("GUI_Tools");

		if (GUI_Hyperlink("Teleporter"))
		{
			GUI_Teleporter_show = true;
		}



	}
	ImGui::End();
	ImGui::PopStyleVar(3);
}





void GUI_Debug_Actor()
{
	GUI_Hyperlink(Locale.Debug.Actor.header);
	ImGui::Text("");
	if (GUI_Checkbox(Locale.Debug.Actor.disableIdleTimer, Config.System.Actor.disableIdleTimer))
	{
		System_Actor_ToggleDisableIdleTimer(Config.System.Actor.disableIdleTimer);
	}
}

void GUI_Debug_Fixes()
{
	GUI_Hyperlink(Locale.Debug.Fixes.header);
	ImGui::Text("");
	if (GUI_Checkbox(Locale.Debug.Fixes.replaceMemoryAllocationFunctions, Config.System.Memory.replaceAllocationFunctions))
	{
		EvaluateApplicationRestart();
	}
}

// @Todo: Add own size vars.

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
		GUI_Debug_Actor();
		ImGui::Text("");
		GUI_Debug_Fixes();
		ImGui::Text("");
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









#define GUI_InputReadOnly(label, var)                                                                                  \
{                                                                                                                      \
	char buffer[64];                                                                                                   \
	snprintf(buffer, sizeof(buffer), "%u", var);                                                                       \
	ImGui::PushID(GUI_id);                                                                                             \
	GUI_id++;                                                                                                          \
	ImGui::InputText(label, buffer, sizeof(buffer), ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_ReadOnly); \
	ImGui::PopID();                                                                                                    \
}

void GUI_Teleporter_Draw()
{
	static bool run = false;
	if (!run)
	{
		run = true;
		ImGui::SetNextWindowSize(ImVec2(GUI_Teleporter_size.x + 16, GUI_Teleporter_size.y + 16));
		ImGui::SetNextWindowPos(ImVec2(500, 500));
	}
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(1, 1));
	if (ImGui::Begin("Teleporter", &GUI_Teleporter_show, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize))
	{
		{
			if (!InGame())
			{
				goto InvalidPointer;
			}
			BYTE * addr = *(BYTE **)(appBaseAddr + 0xF59F00);
			if (!addr)
			{
				goto InvalidPointer;
			}
			uint32 currentRoom = *(uint32 *)(addr + 0x154);
			addr = *(BYTE **)(appBaseAddr + 0xF23F38);
			if (!addr)
			{
				goto InvalidPointer;
			}
			addr = *(BYTE **)(addr + 0x3830);
			if (!addr)
			{
				goto InvalidPointer;
			}
			uint32 & useDoor      = *(uint32 *)(addr + 0x84);
			uint32 & nextRoom     = *(uint32 *)(addr + 0x88);
			uint32 & nextPosition = *(uint32 *)(addr + 0x8C);
			bool   & usePosition  = *(bool   *)(addr + 0xA0);
			ImGui::PushItemWidth(100);
			ImGui::Text("Current");
			GUI_InputReadOnly("", currentRoom);
			ImGui::Text("Next");
			GUI_InputEx<uint32>("", nextRoom);
			GUI_InputEx<uint32>("", nextPosition);
			if (GUI_Button("Teleport"))
			{
				useDoor     = 1;
				usePosition = true;
			}
			ImGui::PopItemWidth();
			goto End;
		}
		InvalidPointer:
		ImGui::Text("Invalid Pointer!");
	}
	End:
	ImGui::End();
	ImGui::PopStyleVar(3);
}

#undef GUI_InputReadOnly



























// @Todo: Update Mary and Eva as well.

void DrawRestartOverlay()
{
	ImGuiIO & io = ImGui::GetIO();
	static ImVec2 size = {};
	ImVec2 position = {};
	position.x = (io.DisplaySize.x - size.x) / 2;
	position.y = (io.DisplaySize.y - size.y) / 2;
	ImGui::SetNextWindowPos(position);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(1, 1));
	if (ImGui::Begin("RestartOverlay", &restart, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_AlwaysAutoResize))
	{
		size = ImGui::GetWindowSize();
		ImGui::PushFont(io.Fonts->Fonts[FONT_RESTART]);
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 0, 0, 1));
		ImGui::Text(Locale.restart);
		ImGui::PopStyleColor();
		ImGui::PopFont();
	}
	ImGui::End();
	ImGui::PopStyleVar(3);
}






void GUI_Render()
{
	GUI_id = 0;
	if (pause)
	{
		GUI_Main_Draw();
	}

	if (GUI_Teleporter_show)
	{
		GUI_Teleporter_Draw();
	}


	if (restart)
	{
		DrawRestartOverlay();
	}

}

void GUI_Init()
{
	BuildFonts();
}


