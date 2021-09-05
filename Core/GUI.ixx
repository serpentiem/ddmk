

// @Todo: namespace + uint64 indices
// @Todo: uint64 UpdateMapIndex + add UpdateMapIndices
// @Todo: Scaling support.



module;
#include "../ImGui/imgui.h"
#include "../ImGui/imgui_internal.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"
export module Core_GUI;

import Core;

#include "Macros.h"

import Windows;
import DXGI;
import D3D11;

using namespace Windows;
using namespace DXGI;
using namespace D3D11;

#define debug false








export int     GUI_id          = 0;
export bool    GUI_save        = false;
export float GUI_saveTimeout = 0;

template <typename T>
struct GetImGuiDataType
{
	static constexpr ImGuiDataType value =
	(TypeMatch<T, int8  >::value) ? ImGuiDataType_S8     :
	(TypeMatch<T, int16 >::value) ? ImGuiDataType_S16    :
	(TypeMatch<T, int32 >::value) ? ImGuiDataType_S32    :
	(TypeMatch<T, int64 >::value) ? ImGuiDataType_S64    :
	(TypeMatch<T, uint8 >::value) ? ImGuiDataType_U8     :
	(TypeMatch<T, uint16>::value) ? ImGuiDataType_U16    :
	(TypeMatch<T, uint32>::value) ? ImGuiDataType_U32    :
	(TypeMatch<T, uint64>::value) ? ImGuiDataType_U64    :
	(TypeMatch<T, float >::value) ? ImGuiDataType_Float  :
	(TypeMatch<T, double>::value) ? ImGuiDataType_Double :
	(TypeMatch<T, bool  >::value) ? ImGuiDataType_U8     :
	0;
};



export enum
{
	SectionFlags_NoNewLine = 1 << 0,
};










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

export bool GUI_ResetButton()
{
	auto update = GUI_Button("Reset");

	if (update)
	{
		GUI_save = true;
	}

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

export bool GUI_Checkbox2
(
	const char * label,
	bool & var,
	bool & var2
)
{
	auto update = GUI_Checkbox
	(
		label,
		var2
	);

	if (update)
	{
		var = var2;
	}

	return update;
}

// @Todo: Extend.
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
		GetImGuiDataType<T>::value,
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
bool GUI_Input2
(
	const char * label,
	T & var,
	T & var2,
	T step = 1,
	const char * format = 0,
	ImGuiInputTextFlags flags = 0
)
{
	auto update = GUI_Input
	(
		label,
		var2,
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
bool GUI_InputDefault
(
	const char * label,
	T & var,
	T & defaultVar,
	const T step = 1,
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
		GetImGuiDataType<T>::value,
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
bool GUI_InputDefault2
(
	const char * label,
	T & var,
	T & var2,
	T & defaultVar,
	const T step = 1,
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
		GetImGuiDataType<T>::value,
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

export template <typename T>
bool GUI_Slider2
(
	const char * label,
	T & var,
	T & var2,
	const T min,
	const T max
)
{
	auto update = GUI_Slider
	(
		label,
		var2,
		min,
		max
	);

	if (update)
	{
		var = var2;
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
		old_for_all(varType, index, count)
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

export template
<
	typename varType,
	uint8 count
>
bool GUI_Combo2
(
	const char * label,
	const char *(&names)[count],
	varType & var,
	varType & var2,
	ImGuiComboFlags flags = 0
)
{
	auto update = GUI_Combo
	(
		label,
		names,
		var2,
		flags
	);

	if (update)
	{
		var = var2;
	}

	return update;
}

export template
<
	typename varType,
	uint8 mapItemCount
>
bool GUI_ComboMap
(
	const char * label,
	const char *(&names)[mapItemCount], // @Todo: Use mapItemNames.
	const varType(&map)[mapItemCount], // @Todo: Use mapItems.
	uint8 & index,
	varType & var,
	ImGuiComboFlags flags = 0
)
{
	bool update = false;
	GUI_PushId();
	if (ImGui::BeginCombo(label, names[index], flags))
	{
		old_for_all(uint8, mapIndex, mapItemCount) // @Todo: mapItemIndex.
		{
			auto & mapItem = map[mapIndex];
			bool selected = (mapIndex == index) ? true : false; // @Todo: Redundant.
			// @Todo: Remove Push and Pop.
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

	if constexpr (debug)
	{
		ImGui::Text("value %u", var  );
		ImGui::Text("index %u", index);
	}

	return update;
}

export template
<
	typename varType,
	uint8 mapItemCount
>
bool GUI_ComboMap2
(
	const char * label,
	const char *(&names)[mapItemCount],
	const varType(&map)[mapItemCount],
	uint8 & index,
	varType & var,
	varType & var2,
	ImGuiComboFlags flags = 0
)
{
	auto update = GUI_ComboMap
	(
		label,
		names,
		map,
		index,
		var2,
		flags
	);

	if (update)
	{
		var = var2;
	}

	return update;
}

export inline void GUI_SectionStart(const char * label)
{
	ImGui::Text(label);
	ImGui::Text("");
}

export inline void GUI_SectionEnd(byte64 flags = 0)
{
	if (!(flags & SectionFlags_NoNewLine))
	{
		ImGui::Text("");
	}

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

export bool GUI_ColorEdit4
(
	const char * label,
	uint8(&var)[4],
	float(&var2)[4],
	ImGuiColorEditFlags flags = 0
)
{
	bool update = false;

	GUI_PushId();
	if (ImGui::ColorEdit4(label, var2, flags))
	{
		update = true;

		old_for_all(uint8, index, 4)
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
	float(&var2)[4]
)
{
	return GUI_ColorEdit4(label, var, var2, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview);
}

export bool GUI_Color2
(
	const char * label,
	uint8(&var)[4],
	uint8(&var2)[4],
	float(&var3)[4]
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
	float(&vars2)[count][4]
)
{
	bool update = false;
	auto & style = ImGui::GetStyle();

	old_for_all(uint8, index, count)
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
bool GUI_ColorPalette2
(
	const char * label,
	uint8(&vars)[count][4],
	uint8(&vars2)[count][4],
	float(&vars3)[count][4]
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

// @Todo: Create RadioButton2.
export template <typename varType>
bool GUI_RadioButton
(
	const char * label,
	varType & var,
	varType value
)
{
	bool update = false;

	GUI_PushId();

	bool selected = (var == value);

	if (ImGui::RadioButton(label, selected))
	{
		update = true;
		var = value;
	}

	GUI_PopId();

	return update;
}






export bool GUI_Color
(
	const char * label,
	float(&var)[4],
	ImGuiColorEditFlags flags = 0
)
{
	GUI_PushId();

	auto update = ImGui::ColorEdit4
	(
		label,
		var,
		flags
	);

	GUI_PopId();

	if (update)
	{
		GUI_save = true;
	}

	if constexpr (debug)
	{
		ImGui::Text("var[0] %f", var[0]);
		ImGui::Text("var[1] %f", var[1]);
		ImGui::Text("var[2] %f", var[2]);
		ImGui::Text("var[3] %f", var[3]);
	}

	return update;
}







export bool GUI_Color2
(
	const char * label,
	float(&var)[4],
	float(&var2)[4],
	ImGuiColorEditFlags flags = 0
)
{
	auto update = GUI_Color
	(
		label,
		var2,
		flags
	);

	if (update)
	{
		memcpy(var, var2, sizeof(var));
	}

	return update;
}











export ID3D11ShaderResourceView * CreateTexture
(
	const char * filename,
	ID3D11Device * device
)
{
	void * addr   = 0;
	int    width  = 0;
	int    height = 0;

	D3D11_TEXTURE2D_DESC            textureDesc            = {};
	D3D11_SUBRESOURCE_DATA          subresourceData        = {};
	ID3D11Texture2D *               texture                = 0;
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc = {};
	ID3D11ShaderResourceView *      shaderResourceView     = 0;

	addr = stbi_load
	(
		filename,
		&width,
		&height,
		0,
		4
	);

	if (!addr)
	{
		return 0;
	}

	textureDesc.Width            = width;
	textureDesc.Height           = height;
	textureDesc.MipLevels        = 1;
	textureDesc.ArraySize        = 1;
	textureDesc.Format           = DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.Usage            = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags        = D3D11_BIND_SHADER_RESOURCE;

	subresourceData.pSysMem     = addr;
	subresourceData.SysMemPitch = (textureDesc.Width * 4);

	device->CreateTexture2D
	(
		&textureDesc,
		&subresourceData,
		&texture
	);

	shaderResourceViewDesc.Format              = DXGI_FORMAT_R8G8B8A8_UNORM;
	shaderResourceViewDesc.ViewDimension       = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MipLevels = textureDesc.MipLevels;

	device->CreateShaderResourceView
	(
		texture,
		&shaderResourceViewDesc,
		&shaderResourceView
	);

	texture->Release();

	stbi_image_free(addr);

	return shaderResourceView;
}

































#ifdef __GARBAGE__
#endif
