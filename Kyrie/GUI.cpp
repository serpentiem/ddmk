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




bool debug   = true;
//bool restart = false;


bool GUI_Teleporter_show = false;
bool GUI_Speed_show      = false;








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


























//uint32 hideMilliseconds = 0;
//uint32 hideTime = 0;
//uint32 * hideTimeAddr = 0;
//
//static DWORD HideThread(void * parameter)
//{
//	uint32 ms = *(uint32 *)parameter;
//	Log("hiding for %u", ms);
//	delete parameter;
//	return 1;
//}
//
//static void GUI_Hide(uint32 milliseconds)
//{
//	uint32 * addr = new uint32;
//	*addr = milliseconds;
//	CreateThread(0, 4096, HideThread, addr, 0, 0);
//}




















void GUI_Game_Arcade()
{
	static bool run = false;
	if (!run)
	{
		run = true;
		for (uint8 i = 0; i < countof(Game_Arcade_missionMap); i++)
		{
			if (Config.Game.Arcade.mission == Game_Arcade_missionMap[i])
			{
				Game_Arcade_missionIndex = i;
				break;
			}
		}
		for (uint8 i = 0; i < countof(Game_Arcade_modeMap); i++)
		{
			if (Config.Game.Arcade.mode == Game_Arcade_modeMap[i])
			{
				Game_Arcade_modeIndex = i;
				break;
			}
		}
	}
	GUI_SECTION_HEADER_START(Game.Arcade);
	Game_Arcade_Toggle(Config.Game.Arcade.enable);
	GUI_SECTION_HEADER_END(Game.Arcade);
	ImGui::PushItemWidth(200);
	GUI_Combo<uint32>
	(
		Locale.Game.Arcade.Game.label,
		Locale.Game.Arcade.Game.items,
		countof(Locale.Game.Arcade.Game.items),
		Config.Game.Arcade.game
	);
	if (GUI_Combo<uint8>
	(
		Locale.Game.Arcade.Mission.label,
		Locale.Game.Arcade.Mission.items,
		countof(Locale.Game.Arcade.Mission.items),
		Game_Arcade_missionIndex,
		0,
		false
	))
	{
		Config.Game.Arcade.mission = Game_Arcade_missionMap[Game_Arcade_missionIndex];
		SaveConfig();
	}
	if (debug)
	{
		ImGui::Text("index   %u", Game_Arcade_missionIndex);
		ImGui::Text("true id %u", Config.Game.Arcade.mission);
	}
	if (GUI_Combo<uint8>
	(
		Locale.Game.Arcade.Mode.label,
		Locale.Game.Arcade.Mode.items,
		countof(Locale.Game.Arcade.Mode.items),
		Game_Arcade_modeIndex,
		0,
		false
	))
	{
		Config.Game.Arcade.mode = Game_Arcade_modeMap[Game_Arcade_modeIndex];
		SaveConfig();
	}
	if (debug)
	{
		ImGui::Text("index   %u", Game_Arcade_modeIndex);
		ImGui::Text("true id %u", Config.Game.Arcade.mode);
	}





	if (GUI_InputEx<uint32>(Locale.Game.Arcade.room, Config.Game.Arcade.room))
	{
		//UpdateMissionStartMapTables();
		//UpdateMissionStartPositions();
	}
	ImGui::SameLine();
	GUI_Checkbox(Locale.Game.Arcade.ignoreRoom, Config.Game.Arcade.ignoreRoom);


	/*

	call

	//add esp,4









	
	
	
	*/


	if (GUI_InputEx<uint32>(Locale.Game.Arcade.position, Config.Game.Arcade.position))
	{
		//UpdateMissionStartPositions();
	}
	ImGui::SameLine();
	GUI_Checkbox(Locale.Game.Arcade.ignorePosition, Config.Game.Arcade.ignorePosition);









	GUI_Combo<uint8>
	(
		Locale.Game.Arcade.Character.label,
		Locale.Game.Arcade.Character.items,
		countof(Locale.Game.Arcade.Character.items),
		Config.Game.Arcade.character
	);


	GUI_InputEx<uint32>(Locale.Game.Arcade.costume, Config.Game.Arcade.costume);




	GUI_InputEx<float32>(Locale.Game.Arcade.hitPoints  , Config.Game.Arcade.hitPoints  , 1000);
	GUI_InputEx<float32>(Locale.Game.Arcade.magicPoints, Config.Game.Arcade.magicPoints, 1000);



	ImGui::PopItemWidth();
	GUI_SECTION_FOOTER_START(Game.Arcade);
	run = false;
	GUI_SECTION_FOOTER_END;
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
	}
	GUI_POP_DISABLE(InMission());
	ImGui::Text("");
	ImGui::PushItemWidth(208);
	if (GUI_Combo<uint8>
	(
		Locale.Game.Multiplayer.KeyboardActor.label,
		Locale.Game.Multiplayer.KeyboardActor.items,
		countof(Locale.Game.Multiplayer.KeyboardActor.items),
		Config.Game.Multiplayer.keyboardActor
	))
	{
		System_Input_UpdateKeyboardAddr();
	}
	ImGui::PopItemWidth();
	ImGui::Text("");
	GUI_PUSH_DISABLE(InMission());
	{
		if (GUI_Button(Locale.Game.Multiplayer.reset))
		{
			memcpy(&Config.Game.Multiplayer, &DefaultConfig.Game.Multiplayer, sizeof(Config.Game.Multiplayer));
			SaveConfig();
			EvaluateApplicationRestart();
		}
	}
	GUI_POP_DISABLE(InMission());
}

void GUI_Game_Training()
{
	GUI_SECTION_HEADER_START(Game.Training);
	if (Config.Game.Training.enable)
	{
		Game_Training_ToggleInfiniteHitPoints   ( Config.Game.Training.infiniteHitPoints   );
		Game_Training_ToggleInfiniteMagicPoints ( Config.Game.Training.infiniteMagicPoints );
		Game_Training_ToggleDisableTimer        ( Config.Game.Training.disableTimer        );
	}
	else
	{
		Game_Training_ToggleInfiniteHitPoints   ( DefaultConfig.Game.Training.infiniteHitPoints   );
		Game_Training_ToggleInfiniteMagicPoints ( DefaultConfig.Game.Training.infiniteMagicPoints );
		Game_Training_ToggleDisableTimer        ( DefaultConfig.Game.Training.disableTimer        );
	}
	GUI_SECTION_HEADER_END(Game.Training);
	if (GUI_Checkbox(Locale.Game.Training.infiniteHitPoints, Config.Game.Training.infiniteHitPoints))
	{
		Game_Training_ToggleInfiniteHitPoints(Config.Game.Training.infiniteHitPoints);
	}
	if (GUI_Checkbox(Locale.Game.Training.infiniteMagicPoints, Config.Game.Training.infiniteMagicPoints))
	{
		Game_Training_ToggleInfiniteMagicPoints(Config.Game.Training.infiniteMagicPoints);
	}
	if (GUI_Checkbox(Locale.Game.Training.disableTimer, Config.Game.Training.disableTimer))
	{
		Game_Training_ToggleDisableTimer(Config.Game.Training.disableTimer);
	}
	GUI_SECTION_FOOTER_START(Game.Training);
	Game_Training_ToggleInfiniteHitPoints   ( DefaultConfig.Game.Training.infiniteHitPoints   );
	Game_Training_ToggleInfiniteMagicPoints ( DefaultConfig.Game.Training.infiniteMagicPoints );
	Game_Training_ToggleDisableTimer        ( DefaultConfig.Game.Training.disableTimer        );
	GUI_SECTION_FOOTER_END;
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
		GUI_Game_Arcade();
		ImGui::Text("");
		GUI_Game_Multiplayer();
		ImGui::Text("");
		GUI_Game_Training();
		ImGui::Text("");
	}
	ImGui::End();
	ImGui::PopStyleVar(3);
}






//void GUI_System_Media()
//{
//	GUI_Hyperlink(Locale.System.Media.header);
//	ImGui::Text("");
//	if (GUI_Checkbox(Locale.System.Media.skipIntro, Config.System.Media.skipIntro))
//	{
//		System_Event_EvaluateToggleReplaceAutosaveStart();
//	}
//}

//void GUI_System_Speed()
//{
//	GUI_Hyperlink(Locale.System.Speed.header);
//	ImGui::Text("");
//	ImGui::PushItemWidth(150);
//	GUI_InputEx<float>(Locale.System.Speed.global, Config.System.Speed.global, 0.1f);
//	GUI_InputEx<float>(Locale.System.Speed.menu, Config.System.Speed.menu, 0.1f);
//	ImGui::PopItemWidth();
//	ImGui::Text("");
//	if (GUI_Button(Locale.System.Speed.reset))
//	{
//		memcpy(&Config.System.Speed, &DefaultConfig.System.Speed, sizeof(Config.System.Speed));
//		SaveConfig();
//	}
//}



// @Todo: Create Speed Tool, reorganize GUI!



void GUI_System_Actor()
{
	GUI_Hyperlink("Actor");
	ImGui::Text("");
	if (GUI_Checkbox("Disable Idle Timer", Config.System.Actor.disableIdleTimer))
	{
		System_Actor_ToggleDisableIdleTimer(Config.System.Actor.disableIdleTimer);
	}
}

void GUI_System_Event()
{
	GUI_Hyperlink("Event");
	ImGui::Text("");
	if (GUI_Checkbox("Skip Intro", Config.System.Event.skipIntro))
	{
		System_Event_ToggleSkipIntro(Config.System.Event.skipIntro);
	}
}

void GUI_System_Memory()
{
	GUI_Hyperlink("Memory");
	ImGui::Text("");
	if (GUI_Checkbox("Replace Allocation Functions", Config.System.Memory.replaceAllocationFunctions))
	{
		EvaluateApplicationRestart();
	}
}

void GUI_System_Window()
{
	GUI_Hyperlink(Locale.System.Window.header);
	ImGui::Text("");
	if (GUI_Checkbox(Locale.System.Window.forceFocus, Config.System.Window.forceFocus))
	{
		System_Window_ToggleForceFocus(Config.System.Window.forceFocus);
	}
	if (GUI_Checkbox(Locale.System.Window.borderless, Config.System.Window.borderless))
	{
		System_Window_QueueToggleBorderless();
	}
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
		GUI_System_Actor();
		ImGui::Text("");
		GUI_System_Event();
		ImGui::Text("");
		GUI_System_Memory();
		ImGui::Text("");
		GUI_System_Window();
		ImGui::Text("");
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
		if (GUI_Hyperlink("Teleporter"))
		{
			GUI_Teleporter_show = true;
		}


		if (GUI_Hyperlink("Speed"))
		{
			GUI_Speed_show = true;
		}






	}
	ImGui::End();
	ImGui::PopStyleVar(3);
}








//
//
//
//void GUI_Debug_Fixes()
//{
//	GUI_Hyperlink(Locale.Debug.Fixes.header);
//	ImGui::Text("");
//	if (GUI_Checkbox(Locale.Debug.Fixes.replaceMemoryAllocationFunctions, Config.System.Memory.replaceAllocationFunctions))
//	{
//		EvaluateApplicationRestart();
//	}
//}
//
//void GUI_Debug_Timers()
//{
//	GUI_Hyperlink(Locale.Debug.Timers.header);
//	ImGui::Text("");
//	if (GUI_Checkbox(Locale.Debug.Timers.disableActorIdleTimer, Config.System.Actor.disableIdleTimer))
//	{
//		System_Actor_ToggleDisableIdleTimer(Config.System.Actor.disableIdleTimer);
//	}
//	if (GUI_Checkbox(Locale.Debug.Timers.disableAutosaveMenuTimer, Config.System.Menu.Autosave.disableTimer))
//	{
//		System_Menu_Autosave_ToggleDisableTimer(Config.System.Menu.Autosave.disableTimer);
//	}
//	if (GUI_Checkbox(Locale.Debug.Timers.disableMainMenuTimer, Config.System.Menu.Main.disableTimer))
//	{
//		System_Menu_Main_ToggleDisableTimer(Config.System.Menu.Main.disableTimer);
//	}
//}
//
//









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
		ImGui::Text("Obsolete");
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















void GUI_Speed_Draw()
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
	if (ImGui::Begin("Speed", &GUI_Speed_show, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::PushItemWidth(200);
		GUI_InputEx<float>("Global", Config.Speed.global, 0.1f);
		GUI_InputEx<float>("Menu"  , Config.Speed.menu  , 0.1f);
		ImGui::PopItemWidth();
		ImGui::Text("");
		if (GUI_Button("Reset"))
		{
			memcpy(&Config.Speed, &DefaultConfig.Speed, sizeof(Config.Speed));
			SaveConfig();
		}
	}
	ImGui::End();
	ImGui::PopStyleVar(3);
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


	if (GUI_hide)
	{
		return;
	}



	GUI_id = 0;






	if (pause)
	{
		GUI_Main_Draw();
	}

	if (GUI_Teleporter_show)
	{
		GUI_Teleporter_Draw();
	}

	if (GUI_Speed_show)
	{
		GUI_Speed_Draw();
	}



	if (restart)
	{
		DrawRestartOverlay();
	}


	//if (GUI_hide)
	//{
	//	return;
	//}



}

void GUI_Init()
{
	BuildFonts();
}


