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

void System_Window_Init()
{
	LogFunction();
	{
		BYTE sect0[] =
		{
			0xFF, 0x15, 0x00, 0x00, 0x00, 0x00, //call dword ptr [dmc4.exe+B73360]
		};
		FUNC func = CreateFunction(System_Window_QueueToggleBorderless, (appBaseAddr + 0x69C432), true, true, sizeof(sect0));
		memcpy(func.sect0, sect0, sizeof(sect0));
		*(BYTE **)(func.sect0 + 2) = (appBaseAddr + 0xB73360);
		WriteJump((appBaseAddr + 0x69C42C), func.addr, 1);
	}
}

void System_Window_ToggleForceFocus(bool enable)
{
	LogFunctionBool(enable);
	if (enable)
	{
		Write<BYTE>((appBaseAddr + 0x6E3231), 1);
	}
	else
	{
		Write<BYTE>((appBaseAddr + 0x6E3231), 0);
	}
}

static void ToggleBorderless(bool enable)
{
	LogFunctionBool(enable);
	if (!mainWindow)
	{
		return;
	}
	static LONG init = GetWindowLongA(mainWindow, GWL_STYLE);
	LONG style = init;
	if (enable)
	{
		style = WS_OVERLAPPED | WS_MINIMIZEBOX | WS_CLIPSIBLINGS | WS_VISIBLE;
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

static DWORD ToggleBorderlessThread(LPVOID)
{
	LogFunction();
	do
	{
		Sleep(10);
	}
	while (!GUI_hide);
	ToggleBorderless(Config.System.Window.borderless);
	return 1;
}

void System_Window_QueueToggleBorderless()
{
	LogFunction();
	GUI_Hide(1000);
	CreateThread(0, 4096, ToggleBorderlessThread, 0, 0, 0);
}
