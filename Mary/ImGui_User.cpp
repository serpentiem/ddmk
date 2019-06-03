#include "ImGui_User.h"

LPSTR CursorMap[ImGuiMouseCursor_COUNT] = {};

void ImGui::User::Init()
{
	CursorMap[ImGuiMouseCursor_Arrow]      = IDC_ARROW;
	CursorMap[ImGuiMouseCursor_TextInput]  = IDC_IBEAM;
	CursorMap[ImGuiMouseCursor_ResizeAll]  = IDC_SIZEALL;
	CursorMap[ImGuiMouseCursor_ResizeNS]   = IDC_SIZENS;
	CursorMap[ImGuiMouseCursor_ResizeEW]   = IDC_SIZEWE;
	CursorMap[ImGuiMouseCursor_ResizeNESW] = IDC_SIZENESW;
	CursorMap[ImGuiMouseCursor_ResizeNWSE] = IDC_SIZENWSE;
	CursorMap[ImGuiMouseCursor_Hand]       = IDC_HAND;
}

void ImGui::User::UpdateMouseCursor(HWND window)
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
