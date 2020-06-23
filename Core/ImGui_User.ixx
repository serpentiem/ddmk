#ifndef __MODULE_IMGUI_USER__
#define __MODULE_IMGUI_USER__

module;
#include "Core.h"

#include "../ImGui/imgui.h"
export module ModuleName(ImGui_User);

LPSTR CursorMap[ImGuiMouseCursor_COUNT] = {};

export void ImGui_User_Init()
{
	CursorMap[ImGuiMouseCursor_Arrow     ] = IDC_ARROW;
	CursorMap[ImGuiMouseCursor_TextInput ] = IDC_IBEAM;
	CursorMap[ImGuiMouseCursor_ResizeAll ] = IDC_SIZEALL;
	CursorMap[ImGuiMouseCursor_ResizeNS  ] = IDC_SIZENS;
	CursorMap[ImGuiMouseCursor_ResizeEW  ] = IDC_SIZEWE;
	CursorMap[ImGuiMouseCursor_ResizeNESW] = IDC_SIZENESW;
	CursorMap[ImGuiMouseCursor_ResizeNWSE] = IDC_SIZENWSE;
	CursorMap[ImGuiMouseCursor_Hand      ] = IDC_HAND;
}

export void ImGui_User_UpdateMouseCursor(HWND window)
{
	if (!window)
	{
		return;
	}
	ImGuiMouseCursor cursor = ImGui::GetMouseCursor();
	static ImGuiMouseCursor lastCursor = cursor;
	if (lastCursor != cursor)
	{
		lastCursor = cursor;
		if ((cursor >= 0) && (cursor < countof(CursorMap)))
		{
			HCURSOR texture = LoadCursorA(0, CursorMap[cursor]);
			SetClassLongPtrA(window, GCLP_HCURSOR, (LONG_PTR)texture);
		}
	}
}

#endif
