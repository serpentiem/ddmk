#include "Window.h"

uint32 System_Window_width  = 0;
uint32 System_Window_height = 0;

void System_Window_UpdateSize(uint32 width, uint32 height)
{
	Log("%s %u %u", FUNC_NAME, width, height);
	System_Window_width  = width;
	System_Window_height = height;
	ImGui::GetIO().DisplaySize = ImVec2((float32)width, (float32)height);
}

void System_Window_ToggleBorderless(bool enable)
{
	Log("%s %u", FUNC_NAME, enable);
	if (!mainWindow)
	{
		return;
	}
	static LONG init = GetWindowLongA(mainWindow, GWL_STYLE);
	LONG style = init;
	if (enable)
	{
		style = WS_VISIBLE | WS_CLIPSIBLINGS;
	}
	SetWindowLongA(mainWindow, GWL_STYLE, style);
	POINT point = {};
	GetWindowPos(mainWindow, &point);
	RECT rect = {};
	rect.right = System_Window_width;
	rect.bottom = System_Window_height;
	AdjustWindowRect(&rect, style, 0);
	MoveWindow(mainWindow, point.x, point.y, (rect.right - rect.left), (rect.bottom - rect.top), 0);
}

void System_Window_Init()
{
	LogFunction();
	{
		BYTE sect0[] =
		{
			0xFF, 0x15, 0x00, 0x00, 0x00, 0x00, //call dword ptr [dmc4.exe+B73360]
		};
		BYTE sect1[] =
		{
			0xB8, 0x00, 0x00, 0x00, 0x00, //mov eax,&Config.System.Window.borderless
			0x0F, 0xB6, 0x00,             //movzx eax,byte ptr [eax]
			0x50,                         //push eax
		};
		FUNC func = CreateFunction(System_Window_ToggleBorderless, (appBaseAddr + 0x69C432), true, true, sizeof(sect0), sizeof(sect1));
		memcpy(func.sect0, sect0, sizeof(sect0));
		memcpy(func.sect1, sect1, sizeof(sect1));
		*(BYTE **)(func.sect0 + 2) = (appBaseAddr + 0xB73360);
		*(bool **)(func.sect1 + 1) = &Config.System.Window.borderless;
		WriteJump((appBaseAddr + 0x69C42C), func.addr, 1);
	}
}
