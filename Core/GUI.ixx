#ifndef __MODULE_CORE_GUI__
#define __MODULE_CORE_GUI__

module;
#include "Core.h"

#include "../ImGui/imgui.h"
#include "../ImGui/imgui_internal.h"
export module ModuleName(Core_GUI);

//constexpr bool debug = true;

#define debug true


export int     GUI_id          = 0;
export bool    GUI_save        = false;
export float32 GUI_saveTimeout = 0;

export inline void GUI_PushId()
{
	ImGui::PushID(GUI_id);
	GUI_id++;
}

export inline void GUI_PopId()
{
	ImGui::PopID();
}

export bool GUI_Button
(
	const char * label,
	const ImVec2 & size = ImVec2(0, 0)
)
{
	GUI_PushId();
	auto update = ImGui::Button(label, size);
	GUI_PopId();
	return update;
}

export bool GUI_Checkbox
(
	const char * label,
	bool & var
)
{
	GUI_PushId();
	auto update = ImGui::Checkbox(label, &var);
	GUI_PopId();

	if (update)
	{
		GUI_save = true;
	}

	return update;
}

export bool GUI_Checkbox
(
	const char * label,
	bool & var,
	bool & var2
)
{
	auto update = GUI_Checkbox(label, var2);

	if (update)
	{
		var = var2;
	}

	return update;
}

export template <typename T>
bool GUI_Input
(
	const char * label,
	T & var,
	T step = 1,
	const char * format = 0,
	ImGuiInputTextFlags flags = 0
)
{
	GUI_PushId();
	auto update = ImGui::InputScalar
	(
		label,
		(TypeMatch<T, uint8  >::value) ? ImGuiDataType_U8    :
		(TypeMatch<T, uint16 >::value) ? ImGuiDataType_U16   :
		(TypeMatch<T, uint32 >::value) ? ImGuiDataType_U32   :
		(TypeMatch<T, uint64 >::value) ? ImGuiDataType_U64   :
		(TypeMatch<T, float32>::value) ? ImGuiDataType_Float :
		0,
		&var,
		(step == 0) ? 0 : &step,
		(step == 0) ? 0 : &step,
		format,
		flags
	);
	GUI_PopId();

	if (update)
	{
		GUI_save = true;
	}

	return update;
}

export template <typename T>
bool GUI_InputDefault
(
	const char * label,
	T & var,
	T & defaultVar,
	T step = 1,
	const char * format = 0,
	ImGuiInputTextFlags flags = 0
)
{
	auto & window = *ImGui::GetCurrentWindow();
	auto & style = ImGui::GetStyle();

	auto buttonSize = ImVec2(ImGui::GetFrameHeight(), ImGui::GetFrameHeight());

	auto itemWidth = window.DC.ItemWidth;

	if (window.DC.ItemWidthStack.Size > 0)
	{
		window.DC.ItemWidth -= (buttonSize.x + style.ItemInnerSpacing.x);
		window.DC.ItemWidthStack.back() = window.DC.ItemWidth;
	}

	GUI_PushId();
	auto update = ImGui::InputScalar
	(
		"",
		(TypeMatch<T, uint8  >::value) ? ImGuiDataType_U8    :
		(TypeMatch<T, uint16 >::value) ? ImGuiDataType_U16   :
		(TypeMatch<T, uint32 >::value) ? ImGuiDataType_U32   :
		(TypeMatch<T, uint64 >::value) ? ImGuiDataType_U64   :
		(TypeMatch<T, float32>::value) ? ImGuiDataType_Float :
		0,
		&var,
		(step == 0) ? 0 : &step,
		(step == 0) ? 0 : &step,
		format,
		flags
	);
	GUI_PopId();

	ImGui::SameLine(0, style.ItemInnerSpacing.x);
	if (GUI_Button("D", buttonSize))
	{
		update = true;
		var = defaultVar;
	}

	ImGui::SameLine(0, style.ItemInnerSpacing.x);
	ImGui::Text(label);

	if (window.DC.ItemWidthStack.Size > 0)
	{
		window.DC.ItemWidth = itemWidth;
		window.DC.ItemWidthStack.back() = window.DC.ItemWidth;
	}

	if (update)
	{
		GUI_save = true;
	}

	return update;
}

export template <typename T>
bool GUI_InputDefault
(
	const char * label,
	T & var,
	T & var2,
	T & defaultVar,
	T step = 1,
	const char * format = 0,
	ImGuiInputTextFlags flags = 0
)
{
	auto update = GUI_InputDefault
	(
		label,
		var2,
		defaultVar,
		step,
		format,
		flags
	);

	if (update)
	{
		var = var2;
	}

	return update;
}

export template <typename T>
bool GUI_Slider
(
	const char * label,
	T & var,
	const T min,
	const T max
)
{
	ImGuiWindow * window = ImGui::GetCurrentWindow();
	ImGuiIO & io = ImGui::GetIO();

	GUI_PushId();
	auto update = ImGui::SliderScalar
	(
		label,
		(TypeMatch<T, uint8  >::value) ? ImGuiDataType_U8    :
		(TypeMatch<T, uint16 >::value) ? ImGuiDataType_U16   :
		(TypeMatch<T, uint32 >::value) ? ImGuiDataType_U32   :
		(TypeMatch<T, uint64 >::value) ? ImGuiDataType_U64   :
		(TypeMatch<T, float32>::value) ? ImGuiDataType_Float :
		0,
		&var,
		&min,
		&max,
		"%u"
	);
	if (ImGui::IsItemHovered())
	{
		window->Flags |= ImGuiWindowFlags_NoScrollbar;
		window->Flags |= ImGuiWindowFlags_NoScrollWithMouse;
		if (io.MouseWheel < 0)
		{
			if (var > min)
			{
				var--;
				update = true;
			}
		}
		else if (io.MouseWheel > 0)
		{
			if (var < max)
			{
				var++;
				update = true;
			}
		}
	}
	GUI_PopId();

	if (update)
	{
		GUI_save = true;
	}

	return update;
}

export bool GUI_Selectable
(
	const char * label,
	bool * selected,
	ImGuiSelectableFlags flags = 0
)
{
	GUI_PushId();
	auto update = ImGui::Selectable(label, selected, flags);
	GUI_PopId();
	return update;
}

export template
<
	typename varType,
	uint8 count
>
bool GUI_Combo
(
	const char * label,
	const char *(&names)[count],
	varType & var,
	ImGuiComboFlags flags = 0
)
{
	bool update = false;
	GUI_PushId();
	if (ImGui::BeginCombo(label, names[var], flags))
	{
		for_all(varType, index, count)
		{
			bool selected = (index == var) ? true : false;
			GUI_PushId();
			if (GUI_Selectable(names[index], &selected))
			{
				update = true;
				var = index;
			}
			GUI_PopId();
		}
		ImGui::EndCombo();
	}
	GUI_PopId();

	if (update)
	{
		GUI_save = true;
	}

	return update;
}

// @Todo: Update names. Prefer items and itemIndex.
export template
<
	typename varType,
	uint8 mapItemCount
>
bool GUI_ComboMap
(
	const char * label,
	const char *(&names)[mapItemCount],
	varType(&map)[mapItemCount],
	uint8 & index,
	varType & var,
	ImGuiComboFlags flags = 0
)
{
	bool update = false;
	GUI_PushId();
	if (ImGui::BeginCombo(label, names[index], flags))
	{
		for_all(uint8, mapIndex, mapItemCount)
		{
			auto & mapItem = map[mapIndex];
			bool selected = (mapIndex == index) ? true : false;
			GUI_PushId();
			if (GUI_Selectable(names[mapIndex], &selected))
			{
				update = true;
				index = mapIndex;
				var = mapItem;
			}
			GUI_PopId();
		}
		ImGui::EndCombo();
	}
	GUI_PopId();

	if (update)
	{
		GUI_save = true;
	}

	return update;
}

//export template
//<
//	typename varType,
//	uint8 mapItemCount
//>
//void GUI_UpdateComboMapIndex
//(
//	varType(&map)[mapItemCount],
//	uint8 & index,
//	varType & var
//)
//{
//	for_all(uint8, mapIndex, mapItemCount)
//	{
//		auto & mapItem = map[mapIndex];
//		if (mapItem == var)
//		{
//			index = mapIndex;
//			break;
//		}
//	}
//}

export inline void GUI_SectionStart(const char * label)
{
	ImGui::Text(label);
	ImGui::Text("");
}

export inline void GUI_SectionEnd()
{
	ImGui::Text("");
	ImGui::Separator();
}

export inline void GUI_PushDisable(bool condition)
{
	if (condition)
	{
		ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
	}
}

export inline void GUI_PopDisable(bool condition)
{
	if (condition)
	{
		ImGui::PopStyleVar();
		ImGui::PopItemFlag();
	}
}

//export bool GUI_ColorEdit4
//(
//	const char * label,
//	float32(&var)[4],
//	ImGuiColorEditFlags flags = 0
//)
//{
//	bool update = false;
//
//	GUI_PushId();
//	if (ImGui::ColorEdit4(label, var, flags))
//	{
//		update = true;
//	}
//	GUI_PopId();
//
//	if (update)
//	{
//		GUI_save = true;
//	}
//
//	return update;
//}

export bool GUI_ColorEdit4
(
	const char * label,
	uint8(&var)[4],
	float32(&var2)[4],
	ImGuiColorEditFlags flags = 0
)
{
	bool update = false;

	GUI_PushId();
	if (ImGui::ColorEdit4(label, var2, flags))
	{
		update = true;

		for_all(uint8, index, 4)
		{
			var[index] = static_cast<uint8>(var2[index] * 255);
		}
	}
	GUI_PopId();

	if (update)
	{
		GUI_save = true;
	}

	if constexpr (debug)
	{
		ImGui::Text("");
		ImGui::Text("var [0] %u", var [0]);
		ImGui::Text("var [1] %u", var [1]);
		ImGui::Text("var [2] %u", var [2]);
		ImGui::Text("var [3] %u", var [3]);
		ImGui::Text("var2[0] %f", var2[0]);
		ImGui::Text("var2[1] %f", var2[1]);
		ImGui::Text("var2[2] %f", var2[2]);
		ImGui::Text("var2[3] %f", var2[3]);
		ImGui::Text("");
	}

	return update;
}

export bool GUI_Color
(
	const char * label,
	uint8(&var)[4],
	float32(&var2)[4]
)
{
	return GUI_ColorEdit4(label, var, var2, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview);
}

export bool GUI_Color
(
	const char * label,
	uint8(&var)[4],
	uint8(&var2)[4],
	float32(&var3)[4]
)
{
	auto update = GUI_Color
	(
		label,
		var2,
		var3
	);

	if (update)
	{
		memcpy(var, var2, sizeof(var2));

		if constexpr (debug)
		{
			Log("GUI_Color memcpy size %u", sizeof(var2));
		}
	}

	return update;
}

export template<uint8 count>
bool GUI_ColorPalette
(
	const char * label,
	uint8(&vars)[count][4],
	float32(&vars2)[count][4]
)
{
	bool update = false;
	auto & style = ImGui::GetStyle();

	for_all(uint8, index, count)
	{
		if (GUI_ColorEdit4("", vars[index], vars2[index], ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreview))
		{
			update = true;
		}

		ImGui::SameLine(0, style.ItemInnerSpacing.x);
	}

	ImGui::Text(label);

	return update;
}

export template<uint8 count>
bool GUI_ColorPalette
(
	const char * label,
	uint8(&vars)[count][4],
	uint8(&vars2)[count][4],
	float32(&vars3)[count][4]
)
{
	auto update = GUI_ColorPalette
	(
		label,
		vars2,
		vars3
	);

	if (update)
	{
		memcpy(vars, vars2, sizeof(vars2));

		if constexpr (debug)
		{
			Log("GUI_ColorPalette memcpy size %u", sizeof(vars2));
		}
	}

	return update;
}

#endif
