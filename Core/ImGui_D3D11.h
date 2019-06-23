// Modified from
// https://github.com/ocornut/imgui/blob/e0cab5664adf02c030f9cf2a05d2c334638a85f8/examples/imgui_impl_dx11.h

#pragma once
#include "Core.h"
#include "../Windows/Windows.h"
#include "../ImGui/imgui.h"
#include <d3d11.h>
#include <d3dcompiler.h>

bool ImGui_D3D11_Init(ID3D11Device * device, ID3D11DeviceContext * device_context);
void ImGui_D3D11_Shutdown();
void ImGui_D3D11_NewFrame();
void ImGui_D3D11_RenderDrawData(ImDrawData * draw_data);
void ImGui_D3D11_InvalidateDeviceObjects();
bool ImGui_D3D11_CreateDeviceObjects();
