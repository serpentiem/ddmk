#include "GUI.h"

int GUI_id = 0;

bool GUI_Slider(const char * label, uint8 & var, uint8 min, uint8 max, bool save)
{
	bool update = false;
	bool pushed = ImGui::GetCurrentWindow()->DC.ItemWidthStack.size() ? true : false;
	float32 width = pushed ? ImGui::GetCurrentWindow()->DC.ItemWidth : 0;
	ImVec2 size;
	size.x = pushed ? width : ImGui::GetWindowSize().x;
	size.y = 19;
	ImGui::PushID(GUI_id);
	GUI_id++;
	ImGui::BeginChild(ImGui::GetID("child"), size);
	if (pushed)
	{
		ImGui::PushItemWidth(width);
	}
	uint32 _var = (uint32)var;
	uint32 _min = (uint32)min;
	uint32 _max = (uint32)max;
	if (ImGui::SliderScalar(label, ImGuiDataType_U32, &_var, &_min, &_max, "%u"))
	{
		var = (uint8)_var;
		update = true;
	}
	if (pushed)
	{
		ImGui::PopItemWidth();
	}
	if (ImGui::IsItemHovered())
	{
		if (ImGui::GetIO().MouseWheel < 0)
		{
			if (_var > _min)
			{
				var--;
				update = true;
			}
		}
		else if (ImGui::GetIO().MouseWheel > 0)
		{
			if (_var < _max)
			{
				var++;
				update = true;
			}
		}
	}
	ImGui::EndChild();
	ImGui::PopID();
	if (update && save)
	{
		SaveConfig();
	}
	return update;
}

bool GUI_Hyperlink(const char * label)
{
	bool update = false;
	ImVec2 pos = ImGui::GetCursorPos();
	ImVec2 size = ImGui::CalcTextSize(label);
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0, 0, 0, 0));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 0, 0, 0));
	ImGui::PushID(GUI_id);
	GUI_id++;
	if (ImGui::Button("", size))
	{
		update = true;
	}
	ImGui::PopID();
	ImGui::PopStyleColor(3);
	if (ImGui::IsItemHovered())
	{
		ImGuiWindow * window = ImGui::GetCurrentWindow();
		float32 x1 = window->Pos.x + ImGui::GetStyle().WindowPadding.x + 1;
		float32 x2 = window->Pos.x + ImGui::GetStyle().WindowPadding.x + ImGui::CalcTextSize(label, 0, true).x;
		const ImRect bb(ImVec2(x1, window->DC.CursorPos.y - 5), ImVec2(x2, window->DC.CursorPos.y));
		window->DrawList->AddLine(bb.Min, ImVec2(bb.Max.x, bb.Min.y), ImGui::GetColorU32(ImGuiCol_Text));
		ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
	}
	ImVec2 end = ImGui::GetCursorPos();
	ImGui::SetCursorPos(pos);
	ImGui::RenderText(ImGui::GetCurrentWindow()->DC.CursorPos, label);
	ImGui::SetCursorPos(end);
	return update;
}

bool GUI_Checkbox(const char * label, bool & var, bool save)
{
	bool update = false;
	ImGui::PushID(GUI_id);
	GUI_id++;
	if (ImGui::Checkbox(label, &var))
	{
		update = true;
	}
	ImGui::PopID();
	if (update && save)
	{
		SaveConfig();
	}
	return update;
}

bool GUI_Button(const char * label, const ImVec2 & size)
{
	bool update = false;
	ImGui::PushID(GUI_id);
	GUI_id++;
	if (ImGui::Button(label, size))
	{
		update = true;
	}
	ImGui::PopID();
	return update;
}

bool GUI_ColorEdit4(const char * label, float32 * var, bool save)
{
	bool update = false;
	ImGui::PushID(GUI_id);
	GUI_id++;
	if (ImGui::ColorEdit4(label, var, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview))
	{
		update = true;
	}
	ImGui::PopID();
	if (update && save)
	{
		SaveConfig();
	}
	return update;
}
