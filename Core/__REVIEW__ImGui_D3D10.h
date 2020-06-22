// Modified from
// https://github.com/ocornut/imgui/blob/e0cab5664adf02c030f9cf2a05d2c334638a85f8/examples/imgui_impl_dx10.h

#pragma once
#include "Core.h"

#include <d3d10_1.h>
#include <d3d10.h>
#include <d3dcompiler.h>
#include "../ImGui/imgui.h"

bool ImGui_D3D10_Init(ID3D10Device * device);
void ImGui_D3D10_Shutdown();
void ImGui_D3D10_NewFrame();
void ImGui_D3D10_RenderDrawData(ImDrawData * draw_data);
void ImGui_D3D10_InvalidateDeviceObjects();
bool ImGui_D3D10_CreateDeviceObjects();
