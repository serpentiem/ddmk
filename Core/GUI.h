#pragma once
#include "Core.h"

#include "../ImGui/imgui.h"
#include "../ImGui/imgui_internal.h"

extern bool   GUI_hide;
extern uint32 GUI_hideTime;
extern int    GUI_id;

void GUI_Hide(uint32 milliseconds);

template <typename T>
bool GUI_Input(const char * label, T & var, bool hex = false, ImGuiInputTextFlags extraFlags = 0)
{
	bool update = false;
	char value[64];
	ImGuiInputTextFlags flags = ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_EnterReturnsTrue;
	if (hex)
	{
		if constexpr      (typematch(T, uint8  )) { sprintf(value, "%.2X", var); }
		else if constexpr (typematch(T, uint16 )) { sprintf(value, "%.4X", var); }
		else if constexpr (typematch(T, uint32 )) { sprintf(value, "%.8X", var); }
		#pragma warning(push)
		#pragma warning(disable: 4477)
		else if constexpr (typematch(T, float32)) { sprintf(value, "%.8X", var); }
		#pragma warning(pop)
		flags |= ImGuiInputTextFlags_CharsHexadecimal;
	}
	else
	{
		if constexpr      (typematch(T, uint8 )) { sprintf(value, "%u",   var); }
		else if constexpr (typematch(T, uint16)) { sprintf(value, "%u",   var); }
		else if constexpr (typematch(T, uint32)) { sprintf(value, "%u",   var); }
		else if constexpr (typematch(T, float32 )) { sprintf(value, "%.3f", var); }
		flags |= ImGuiInputTextFlags_CharsDecimal;
	}
	flags |= extraFlags;
	ImGui::PushID(GUI_id);
	GUI_id++;
	if (ImGui::InputText(label, value, sizeof(value), flags))
	{
		if (hex)
		{
			if constexpr (typematch(T, float32))
			{
				var = hexstrtof(value);
			}
			else
			{
				var = (T)strtoul(value, 0, 16);
			}
		}
		else
		{
			if constexpr (typematch(T, float32))
			{
				var = strtof(value, 0);
			}
			else
			{
				var = (T)strtoul(value, 0, 10);
			}
		}
		update = true;
	}
	ImGui::PopID();
	return update;
}
template <typename T>
bool GUI_InputEx(const char * label, T & var, T step = 1, bool hex = false, bool save = true)
{
	bool update = false;
	if (step)
	{
		ImVec2 size = ImVec2(ImGui::GetFrameHeight(), ImGui::GetFrameHeight());
		bool pushed = ImGui::GetCurrentWindow()->DC.ItemWidthStack.size() ? true : false;
		if (pushed)
		{
			ImGui::PushItemWidth(ImGui::GetCurrentWindow()->DC.ItemWidth - ((size.x + ImGui::GetStyle().ItemInnerSpacing.x) * 2));
		}
		update = GUI_Input("", var, hex);
		if (pushed)
		{
			ImGui::PopItemWidth();
		}
		ImGui::SameLine(0, ImGui::GetStyle().ItemInnerSpacing.x);
		ImGui::PushID(GUI_id);
		GUI_id++;
		if (ImGui::ButtonEx("-", size, ImGuiButtonFlags_Repeat))
		{
			var -= step;
			update = true;
		}
		ImGui::SameLine(0, ImGui::GetStyle().ItemInnerSpacing.x);
		if (ImGui::ButtonEx("+", size, ImGuiButtonFlags_Repeat))
		{
			var += step;
			update = true;
		}
		ImGui::PopID();
		ImGui::SameLine(0, ImGui::GetStyle().ItemInnerSpacing.x);
		ImGui::Text(label);
	}
	else
	{
		update = GUI_Input(label, var, hex);
	}
	if (update && save)
	{
		SaveConfig();
	}
	return update;
}
bool GUI_Slider(const char * label, uint8 & var, uint8 min, uint8 max, bool save = true);
bool GUI_Hyperlink(const char * label);
bool GUI_Checkbox(const char * label, bool & var, bool save = true);
template <typename T>
bool GUI_Combo(const char * label, const char ** items, T count, T & var, T pos = 0, bool save = true)
{
	bool update = false;
	ImGui::PushID(GUI_id);
	GUI_id++;
	if (ImGui::BeginCombo(label, items[var]))
	{
		for (T i = pos; i < count; i++)
		{
			bool selected = var == i ? true : false;
			ImGui::PushID(GUI_id);
			GUI_id++;
			if (ImGui::Selectable(items[i], &selected))
			{
				var = i;
				update = true;
			}
			ImGui::PopID();
			if (selected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}
	ImGui::PopID();
	if (update && save)
	{
		SaveConfig();
	}
	return update;
}
bool GUI_Button(const char * label, const ImVec2 & size = ImVec2());
bool GUI_ColorEdit4(const char * label, float32 * var, bool save = true);
bool GUI_ColorEdit4(float32 * var, bool save = true);












// @Todo: Look into the possibility of templates for these macros.

#define GUI_PUSH_DISABLE(condition)                                           \
if (condition)                                                                \
{                                                                             \
	ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);                       \
	ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f); \
}

#define GUI_POP_DISABLE(condition) \
if (condition)                     \
{                                  \
	ImGui::PopItemFlag();          \
	ImGui::PopStyleVar();          \
}

#define GUI_SECTION_HEADER_START(branch)                      \
GUI_Hyperlink(Locale.branch.header);                          \
ImGui::Text("");                                              \
if (GUI_Checkbox(Locale.branch.enable, Config.branch.enable)) \
{

#define GUI_SECTION_HEADER_END(branch)   \
}                                        \
ImGui::Text("");                         \
GUI_PUSH_DISABLE(!Config.branch.enable);

#define GUI_SECTION_FOOTER_START(branch)                                  \
GUI_POP_DISABLE(!Config.branch.enable);                                   \
ImGui::Text("");                                                          \
if (GUI_Button(Locale.branch.reset))                                      \
{                                                                         \
	memcpy(&Config.branch, &DefaultConfig.branch, sizeof(Config.branch)); \
	SaveConfig();

#define GUI_SECTION_FOOTER_END \
}

#define GUI_SECTION_HEADER(branch) GUI_SECTION_HEADER_START(branch) GUI_SECTION_HEADER_END(branch)
#define GUI_SECTION_FOOTER(branch) GUI_SECTION_FOOTER_START(branch) GUI_SECTION_FOOTER_END
