module;
#include "../ThirdParty/ImGui/imgui.h"
#include "../ThirdParty/ImGui/imgui_internal.h"
export module Core_ImGui;

import Core;

#include "Macros.h"

import Windows;
import DXGI;
import D3D10;
import D3D11;
import DI8;

using namespace Windows;
using namespace DXGI;
using namespace DI8;

#define debug false

namespaceStart(ImGui);

#pragma region Windows

LPSTR cursorMap[ImGuiMouseCursor_COUNT] =
{
	reinterpret_cast<LPSTR>(IDC_ARROW),
	reinterpret_cast<LPSTR>(IDC_IBEAM),
	reinterpret_cast<LPSTR>(IDC_SIZEALL),
	reinterpret_cast<LPSTR>(IDC_SIZENS),
	reinterpret_cast<LPSTR>(IDC_SIZEWE),
	reinterpret_cast<LPSTR>(IDC_SIZENESW),
	reinterpret_cast<LPSTR>(IDC_SIZENWSE),
	reinterpret_cast<LPSTR>(IDC_HAND),
	reinterpret_cast<LPSTR>(IDC_NO),
};

constexpr uint32 cursorMapItemCount = static_cast<uint32>(countof(cursorMap));

export void UpdateMouseCursor(HWND windowHandle)
{
	if (!windowHandle)
	{
		return;
	}

	auto cursor = static_cast<uint32>(GetMouseCursor());
	if (cursor >= cursorMapItemCount)
	{
		cursor = 0;
	}

	static auto lastCursor = cursor;

	if (lastCursor != cursor)
	{
		lastCursor = cursor;

		auto texture =
		LoadCursorA
		(
			0,
			cursorMap[cursor]
		);


		#ifdef _WIN64
		SetClassLongPtrA
		#else
		SetClassLongA
		#endif
		(
			windowHandle,
			GCLP_HCURSOR,
			reinterpret_cast<LONG_PTR>(texture)
		);
	}
}

#pragma endregion

#pragma region D3D10

namespaceStart(D3D10);

using namespace ::D3D10;

ID3D10Device*g_pd3dDevice=NULL;

IDXGIFactory*g_pFactory=NULL;
ID3D10Buffer*g_pVB=NULL;
ID3D10Buffer*g_pIB=NULL;
ID3D10Blob*g_pVertexShaderBlob=NULL;
ID3D10VertexShader*g_pVertexShader=NULL;
ID3D10InputLayout*g_pInputLayout=NULL;
ID3D10Buffer*g_pVertexConstantBuffer=NULL;
ID3D10Blob*g_pPixelShaderBlob=NULL;
ID3D10PixelShader*g_pPixelShader=NULL;
ID3D10SamplerState*g_pFontSampler=NULL;
ID3D10ShaderResourceView*g_pFontTextureView=NULL;
ID3D10RasterizerState*g_pRasterizerState=NULL;
ID3D10BlendState*g_pBlendState=NULL;
ID3D10DepthStencilState*g_pDepthStencilState=NULL;
int g_VertexBufferSize=5000;
int g_IndexBufferSize=10000;

struct VERTEX_CONSTANT_BUFFER
{
	float mvp[4][4];
};

export void RenderDrawData(ImDrawData*draw_data)
{
	ID3D10Device*ctx=g_pd3dDevice;
	if(!g_pVB||g_VertexBufferSize < draw_data->TotalVtxCount)
	{
	if(g_pVB){g_pVB->Release();g_pVB=NULL;}
	g_VertexBufferSize=draw_data->TotalVtxCount+5000;
	D3D10_BUFFER_DESC desc;
	SetMemory(&desc,0,sizeof(D3D10_BUFFER_DESC));
	desc.Usage=D3D10_USAGE_DYNAMIC;
	desc.ByteWidth=g_VertexBufferSize*sizeof(ImDrawVert);
	desc.BindFlags=D3D10_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags=D3D10_CPU_ACCESS_WRITE;
	desc.MiscFlags=0;
	if(ctx->CreateBuffer(&desc,NULL,&g_pVB)< 0)
	return;
	}
	if(!g_pIB||g_IndexBufferSize < draw_data->TotalIdxCount)
	{
	if(g_pIB){g_pIB->Release();g_pIB=NULL;}
	g_IndexBufferSize=draw_data->TotalIdxCount+10000;
	D3D10_BUFFER_DESC desc;
	SetMemory(&desc,0,sizeof(D3D10_BUFFER_DESC));
	desc.Usage=D3D10_USAGE_DYNAMIC;
	desc.ByteWidth=g_IndexBufferSize*sizeof(ImDrawIdx);
	desc.BindFlags=D3D10_BIND_INDEX_BUFFER;
	desc.CPUAccessFlags=D3D10_CPU_ACCESS_WRITE;
	if(ctx->CreateBuffer(&desc,NULL,&g_pIB)< 0)
	return;
	}
	ImDrawVert*vtx_dst=NULL;
	ImDrawIdx*idx_dst=NULL;
	g_pVB->Map(D3D10_MAP_WRITE_DISCARD,0,(void**)&vtx_dst);
	g_pIB->Map(D3D10_MAP_WRITE_DISCARD,0,(void**)&idx_dst);
	for(int n=0;n < draw_data->CmdListsCount;n++)
	{
	const ImDrawList*cmd_list=draw_data->CmdLists[n];
	CopyMemory(vtx_dst,cmd_list->VtxBuffer.Data,cmd_list->VtxBuffer.Size*sizeof(ImDrawVert));
	CopyMemory(idx_dst,cmd_list->IdxBuffer.Data,cmd_list->IdxBuffer.Size*sizeof(ImDrawIdx));
	vtx_dst+=cmd_list->VtxBuffer.Size;
	idx_dst+=cmd_list->IdxBuffer.Size;
	}
	g_pVB->Unmap();
	g_pIB->Unmap();
	{
	void*mapped_resource;
	if(g_pVertexConstantBuffer->Map(D3D10_MAP_WRITE_DISCARD,0,&mapped_resource)!=S_OK)
	return;
	VERTEX_CONSTANT_BUFFER*constant_buffer=(VERTEX_CONSTANT_BUFFER*)mapped_resource;
	float L=draw_data->DisplayPos.x;
	float R=draw_data->DisplayPos.x+draw_data->DisplaySize.x;
	float T=draw_data->DisplayPos.y;
	float B=draw_data->DisplayPos.y+draw_data->DisplaySize.y;
	float mvp[4][4]=
	{
	{2.0f/(R-L),0.0f,0.0f,0.0f},
	{0.0f,2.0f/(T-B),0.0f,0.0f},
	{0.0f,0.0f,0.5f,0.0f},
	{(R+L)/(L-R),(T+B)/(B-T),0.5f,1.0f},
	};
	CopyMemory(&constant_buffer->mvp,mvp,sizeof(mvp));
	g_pVertexConstantBuffer->Unmap();
	}
	struct BACKUP_DX10_STATE
	{
	UINT ScissorRectsCount,ViewportsCount;
	D3D10_RECT ScissorRects[D3D10_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE];
	D3D10_VIEWPORT Viewports[D3D10_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE];
	ID3D10RasterizerState*RS;
	ID3D10BlendState*BlendState;
	FLOAT BlendFactor[4];
	UINT SampleMask;
	UINT StencilRef;
	ID3D10DepthStencilState*DepthStencilState;
	ID3D10ShaderResourceView*PSShaderResource;
	ID3D10SamplerState*PSSampler;
	ID3D10PixelShader*PS;
	ID3D10VertexShader*VS;
	D3D10_PRIMITIVE_TOPOLOGY PrimitiveTopology;
	ID3D10Buffer*IndexBuffer,*VertexBuffer,*VSConstantBuffer;
	UINT IndexBufferOffset,VertexBufferStride,VertexBufferOffset;
	DXGI_FORMAT IndexBufferFormat;
	ID3D10InputLayout*InputLayout;
	};
	BACKUP_DX10_STATE old;
	old.ScissorRectsCount=old.ViewportsCount=D3D10_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE;
	ctx->RSGetScissorRects(&old.ScissorRectsCount,old.ScissorRects);
	ctx->RSGetViewports(&old.ViewportsCount,old.Viewports);
	ctx->RSGetState(&old.RS);
	ctx->OMGetBlendState(&old.BlendState,old.BlendFactor,&old.SampleMask);
	ctx->OMGetDepthStencilState(&old.DepthStencilState,&old.StencilRef);
	ctx->PSGetShaderResources(0,1,&old.PSShaderResource);
	ctx->PSGetSamplers(0,1,&old.PSSampler);
	ctx->PSGetShader(&old.PS);
	ctx->VSGetShader(&old.VS);
	ctx->VSGetConstantBuffers(0,1,&old.VSConstantBuffer);
	ctx->IAGetPrimitiveTopology(&old.PrimitiveTopology);
	ctx->IAGetIndexBuffer(&old.IndexBuffer,&old.IndexBufferFormat,&old.IndexBufferOffset);
	ctx->IAGetVertexBuffers(0,1,&old.VertexBuffer,&old.VertexBufferStride,&old.VertexBufferOffset);
	ctx->IAGetInputLayout(&old.InputLayout);
	D3D10_VIEWPORT vp;
	SetMemory(&vp,0,sizeof(D3D10_VIEWPORT));
	vp.Width=(UINT)draw_data->DisplaySize.x;
	vp.Height=(UINT)draw_data->DisplaySize.y;
	vp.MinDepth=0.0f;
	vp.MaxDepth=1.0f;
	vp.TopLeftX=vp.TopLeftY=0;
	ctx->RSSetViewports(1,&vp);
	unsigned int stride=sizeof(ImDrawVert);
	unsigned int offset=0;
	ctx->IASetInputLayout(g_pInputLayout);
	ctx->IASetVertexBuffers(0,1,&g_pVB,&stride,&offset);
	ctx->IASetIndexBuffer(g_pIB,sizeof(ImDrawIdx)==2 ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT,0);
	ctx->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	ctx->VSSetShader(g_pVertexShader);
	ctx->VSSetConstantBuffers(0,1,&g_pVertexConstantBuffer);
	ctx->PSSetShader(g_pPixelShader);
	ctx->PSSetSamplers(0,1,&g_pFontSampler);
	const float blend_factor[4]={0.f,0.f,0.f,0.f};
	ctx->OMSetBlendState(g_pBlendState,blend_factor,0xffffffff);
	ctx->OMSetDepthStencilState(g_pDepthStencilState,0);
	ctx->RSSetState(g_pRasterizerState);
	int vtx_offset=0;
	int idx_offset=0;
	ImVec2 pos=draw_data->DisplayPos;
	for(int n=0;n < draw_data->CmdListsCount;n++)
	{
	const ImDrawList*cmd_list=draw_data->CmdLists[n];
	for(int cmd_i=0;cmd_i < cmd_list->CmdBuffer.Size;cmd_i++)
	{
	const ImDrawCmd*pcmd=&cmd_list->CmdBuffer[cmd_i];
	if(pcmd->UserCallback)
	{
	pcmd->UserCallback(cmd_list,pcmd);
	}
	else
	{
	const D3D10_RECT r={(LONG)(pcmd->ClipRect.x-pos.x),(LONG)(pcmd->ClipRect.y-pos.y),(LONG)(pcmd->ClipRect.z-pos.x),(LONG)(pcmd->ClipRect.w-pos.y)};
	ctx->RSSetScissorRects(1,&r);
	ID3D10ShaderResourceView*texture_srv=(ID3D10ShaderResourceView*)pcmd->TextureId;
	ctx->PSSetShaderResources(0,1,&texture_srv);
	ctx->DrawIndexed(pcmd->ElemCount,idx_offset,vtx_offset);
	}
	idx_offset+=pcmd->ElemCount;
	}
	vtx_offset+=cmd_list->VtxBuffer.Size;
	}
	ctx->RSSetScissorRects(old.ScissorRectsCount,old.ScissorRects);
	ctx->RSSetViewports(old.ViewportsCount,old.Viewports);
	ctx->RSSetState(old.RS);if(old.RS)old.RS->Release();
	ctx->OMSetBlendState(old.BlendState,old.BlendFactor,old.SampleMask);if(old.BlendState)old.BlendState->Release();
	ctx->OMSetDepthStencilState(old.DepthStencilState,old.StencilRef);if(old.DepthStencilState)old.DepthStencilState->Release();
	ctx->PSSetShaderResources(0,1,&old.PSShaderResource);if(old.PSShaderResource)old.PSShaderResource->Release();
	ctx->PSSetSamplers(0,1,&old.PSSampler);if(old.PSSampler)old.PSSampler->Release();
	ctx->PSSetShader(old.PS);if(old.PS)old.PS->Release();
	ctx->VSSetShader(old.VS);if(old.VS)old.VS->Release();
	ctx->VSSetConstantBuffers(0,1,&old.VSConstantBuffer);if(old.VSConstantBuffer)old.VSConstantBuffer->Release();
	ctx->IASetPrimitiveTopology(old.PrimitiveTopology);
	ctx->IASetIndexBuffer(old.IndexBuffer,old.IndexBufferFormat,old.IndexBufferOffset);if(old.IndexBuffer)old.IndexBuffer->Release();
	ctx->IASetVertexBuffers(0,1,&old.VertexBuffer,&old.VertexBufferStride,&old.VertexBufferOffset);if(old.VertexBuffer)old.VertexBuffer->Release();
	ctx->IASetInputLayout(old.InputLayout);if(old.InputLayout)old.InputLayout->Release();
}

void CreateFontsTexture()
{
	ImGuiIO&io=ImGui::GetIO();
	unsigned char*pixels;
	int width,height;
	io.Fonts->GetTexDataAsRGBA32(&pixels,&width,&height);
	{
	D3D10_TEXTURE2D_DESC desc;
	SetMemory(&desc,0,sizeof(desc));
	desc.Width=width;
	desc.Height=height;
	desc.MipLevels=1;
	desc.ArraySize=1;
	desc.Format=DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count=1;
	desc.Usage=D3D10_USAGE_DEFAULT;
	desc.BindFlags=D3D10_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags=0;
	ID3D10Texture2D*pTexture=NULL;
	D3D10_SUBRESOURCE_DATA subResource;
	subResource.pSysMem=pixels;
	subResource.SysMemPitch=desc.Width*4;
	subResource.SysMemSlicePitch=0;
	g_pd3dDevice->CreateTexture2D(&desc,&subResource,&pTexture);
	D3D10_SHADER_RESOURCE_VIEW_DESC srv_desc;
	SetMemory(&srv_desc,0,sizeof(srv_desc));
	srv_desc.Format=DXGI_FORMAT_R8G8B8A8_UNORM;
	srv_desc.ViewDimension=D3D10_SRV_DIMENSION_TEXTURE2D;
	srv_desc.Texture2D.MipLevels=desc.MipLevels;
	srv_desc.Texture2D.MostDetailedMip=0;
	g_pd3dDevice->CreateShaderResourceView(pTexture,&srv_desc,&g_pFontTextureView);
	pTexture->Release();
	}
	io.Fonts->TexID=(ImTextureID)g_pFontTextureView;
	{
	D3D10_SAMPLER_DESC desc;
	SetMemory(&desc,0,sizeof(desc));
	desc.Filter=D3D10_FILTER_MIN_MAG_MIP_LINEAR;
	desc.AddressU=D3D10_TEXTURE_ADDRESS_WRAP;
	desc.AddressV=D3D10_TEXTURE_ADDRESS_WRAP;
	desc.AddressW=D3D10_TEXTURE_ADDRESS_WRAP;
	desc.MipLODBias=0.f;
	desc.ComparisonFunc=D3D10_COMPARISON_ALWAYS;
	desc.MinLOD=0.f;
	desc.MaxLOD=0.f;
	g_pd3dDevice->CreateSamplerState(&desc,&g_pFontSampler);
	}
}

export void InvalidateDeviceObjects()
{
	if(!g_pd3dDevice)
	return;
	if(g_pFontSampler){g_pFontSampler->Release();g_pFontSampler=NULL;}
	if(g_pFontTextureView){g_pFontTextureView->Release();g_pFontTextureView=NULL;ImGui::GetIO().Fonts->TexID=NULL;}
	if(g_pIB){g_pIB->Release();g_pIB=NULL;}
	if(g_pVB){g_pVB->Release();g_pVB=NULL;}
	if(g_pBlendState){g_pBlendState->Release();g_pBlendState=NULL;}
	if(g_pDepthStencilState){g_pDepthStencilState->Release();g_pDepthStencilState=NULL;}
	if(g_pRasterizerState){g_pRasterizerState->Release();g_pRasterizerState=NULL;}
	if(g_pPixelShader){g_pPixelShader->Release();g_pPixelShader=NULL;}
	if(g_pPixelShaderBlob){g_pPixelShaderBlob->Release();g_pPixelShaderBlob=NULL;}
	if(g_pVertexConstantBuffer){g_pVertexConstantBuffer->Release();g_pVertexConstantBuffer=NULL;}
	if(g_pInputLayout){g_pInputLayout->Release();g_pInputLayout=NULL;}
	if(g_pVertexShader){g_pVertexShader->Release();g_pVertexShader=NULL;}
	if(g_pVertexShaderBlob){g_pVertexShaderBlob->Release();g_pVertexShaderBlob=NULL;}
}

export bool CreateDeviceObjects()
{
	if(!g_pd3dDevice)
	return false;
	if(g_pFontSampler)
	InvalidateDeviceObjects();
	{
	const char*vertexShader=
	"cbuffer vertexBuffer : register(b0)\
	{\
	float4x4 ProjectionMatrix;\
	};\
	struct VS_INPUT\
	{\
	float2 pos : POSITION;\
	float4 col : COLOR0;\
	float2 uv : TEXCOORD0;\
	};\
	\
	struct PS_INPUT\
	{\
	float4 pos : SV_POSITION;\
	float4 col : COLOR0;\
	float2 uv : TEXCOORD0;\
	};\
	\
	PS_INPUT main(VS_INPUT input)\
	{\
	PS_INPUT output;\
	output.pos=mul(ProjectionMatrix,float4(input.pos.xy,0.f,1.f));\
	output.col=input.col;\
	output.uv=input.uv;\
	return output;\
	}";
	D3DCompile(vertexShader,strlen(vertexShader),NULL,NULL,NULL,"main","vs_4_0",0,0,&g_pVertexShaderBlob,NULL);
	if(g_pVertexShaderBlob==NULL)
	return false;
	if(g_pd3dDevice->CreateVertexShader((DWORD*)g_pVertexShaderBlob->GetBufferPointer(),g_pVertexShaderBlob->GetBufferSize(),&g_pVertexShader)!=S_OK)
	return false;
	D3D10_INPUT_ELEMENT_DESC local_layout[]=
	{
	{"POSITION",0,DXGI_FORMAT_R32G32_FLOAT,0,(size_t)(&((ImDrawVert*)0)->pos),D3D10_INPUT_PER_VERTEX_DATA,0},
	{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,(size_t)(&((ImDrawVert*)0)->uv),D3D10_INPUT_PER_VERTEX_DATA,0},
	{"COLOR",0,DXGI_FORMAT_R8G8B8A8_UNORM,0,(size_t)(&((ImDrawVert*)0)->col),D3D10_INPUT_PER_VERTEX_DATA,0},
	};
	if(g_pd3dDevice->CreateInputLayout(local_layout,3,g_pVertexShaderBlob->GetBufferPointer(),g_pVertexShaderBlob->GetBufferSize(),&g_pInputLayout)!=S_OK)
	return false;
	{
	D3D10_BUFFER_DESC desc;
	desc.ByteWidth=sizeof(VERTEX_CONSTANT_BUFFER);
	desc.Usage=D3D10_USAGE_DYNAMIC;
	desc.BindFlags=D3D10_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags=D3D10_CPU_ACCESS_WRITE;
	desc.MiscFlags=0;
	g_pd3dDevice->CreateBuffer(&desc,NULL,&g_pVertexConstantBuffer);
	}
	}
	{
	const char*pixelShader=
	"struct PS_INPUT\
	{\
	float4 pos : SV_POSITION;\
	float4 col : COLOR0;\
	float2 uv : TEXCOORD0;\
	};\
	sampler sampler0;\
	Texture2D texture0;\
	\
	float4 main(PS_INPUT input): SV_Target\
	{\
	float4 out_col=input.col*texture0.Sample(sampler0,input.uv);\
	return out_col;\
	}";
	D3DCompile(pixelShader,strlen(pixelShader),NULL,NULL,NULL,"main","ps_4_0",0,0,&g_pPixelShaderBlob,NULL);
	if(g_pPixelShaderBlob==NULL)
	return false;
	if(g_pd3dDevice->CreatePixelShader((DWORD*)g_pPixelShaderBlob->GetBufferPointer(),g_pPixelShaderBlob->GetBufferSize(),&g_pPixelShader)!=S_OK)
	return false;
	}
	{
	D3D10_BLEND_DESC desc;
	SetMemory(&desc,0,sizeof(desc));
	desc.AlphaToCoverageEnable=false;
	desc.BlendEnable[0]=true;
	desc.SrcBlend=D3D10_BLEND_SRC_ALPHA;
	desc.DestBlend=D3D10_BLEND_INV_SRC_ALPHA;
	desc.BlendOp=D3D10_BLEND_OP_ADD;
	desc.SrcBlendAlpha=D3D10_BLEND_INV_SRC_ALPHA;
	desc.DestBlendAlpha=D3D10_BLEND_ZERO;
	desc.BlendOpAlpha=D3D10_BLEND_OP_ADD;
	desc.RenderTargetWriteMask[0]=D3D10_COLOR_WRITE_ENABLE_ALL;
	g_pd3dDevice->CreateBlendState(&desc,&g_pBlendState);
	}
	{
	D3D10_RASTERIZER_DESC desc;
	SetMemory(&desc,0,sizeof(desc));
	desc.FillMode=D3D10_FILL_SOLID;
	desc.CullMode=D3D10_CULL_NONE;
	desc.ScissorEnable=true;
	desc.DepthClipEnable=true;
	g_pd3dDevice->CreateRasterizerState(&desc,&g_pRasterizerState);
	}
	{
	D3D10_DEPTH_STENCIL_DESC desc;
	SetMemory(&desc,0,sizeof(desc));
	desc.DepthEnable=false;
	desc.DepthWriteMask=D3D10_DEPTH_WRITE_MASK_ALL;
	desc.DepthFunc=D3D10_COMPARISON_ALWAYS;
	desc.StencilEnable=false;
	desc.FrontFace.StencilFailOp=desc.FrontFace.StencilDepthFailOp=desc.FrontFace.StencilPassOp=D3D10_STENCIL_OP_KEEP;
	desc.FrontFace.StencilFunc=D3D10_COMPARISON_ALWAYS;
	desc.BackFace=desc.FrontFace;
	g_pd3dDevice->CreateDepthStencilState(&desc,&g_pDepthStencilState);
	}
	CreateFontsTexture();
	return true;
}

export bool Init(ID3D10Device*device)
{
	IDXGIDevice*pDXGIDevice=NULL;
	IDXGIAdapter*pDXGIAdapter=NULL;
	IDXGIFactory*pFactory=NULL;
	// if(device->QueryInterface(IID_PPV_ARGS(&pDXGIDevice))==S_OK)
	// if(pDXGIDevice->GetParent(IID_PPV_ARGS(&pDXGIAdapter))==S_OK)
	// if(pDXGIAdapter->GetParent(IID_PPV_ARGS(&pFactory))==S_OK)
	{
	g_pd3dDevice=device;
	g_pFactory=pFactory;
	}
	if(pDXGIDevice)pDXGIDevice->Release();
	if(pDXGIAdapter)pDXGIAdapter->Release();
	return true;
}

export void Shutdown()
{
	InvalidateDeviceObjects();
	if(g_pFactory){g_pFactory->Release();g_pFactory=NULL;}
	g_pd3dDevice=NULL;
}

export void NewFrame()
{
	if(!g_pFontSampler)
	CreateDeviceObjects();
}

namespaceEnd();

#pragma endregion

#pragma region D3D11

namespaceStart(D3D11);

using namespace ::D3D11;

ID3D11Device*g_pd3dDevice=NULL;
ID3D11DeviceContext*g_pd3dDeviceContext=NULL;
IDXGIFactory*g_pFactory=NULL;
ID3D11Buffer*g_pVB=NULL;
ID3D11Buffer*g_pIB=NULL;
ID3D10Blob*g_pVertexShaderBlob=NULL;
ID3D11VertexShader*g_pVertexShader=NULL;
ID3D11InputLayout*g_pInputLayout=NULL;
ID3D11Buffer*g_pVertexConstantBuffer=NULL;
ID3D10Blob*g_pPixelShaderBlob=NULL;
ID3D11PixelShader*g_pPixelShader=NULL;
ID3D11SamplerState*g_pFontSampler=NULL;
ID3D11ShaderResourceView*g_pFontTextureView=NULL;
ID3D11RasterizerState*g_pRasterizerState=NULL;
ID3D11BlendState*g_pBlendState=NULL;
ID3D11DepthStencilState*g_pDepthStencilState=NULL;
int g_VertexBufferSize=5000;
int g_IndexBufferSize=10000;

struct VERTEX_CONSTANT_BUFFER
{
	float mvp[4][4];
};

export void RenderDrawData(ImDrawData*draw_data)
{
	ID3D11DeviceContext*ctx=g_pd3dDeviceContext;
	if(!g_pVB||g_VertexBufferSize < draw_data->TotalVtxCount)
	{
	if(g_pVB){g_pVB->Release();g_pVB=NULL;}
	g_VertexBufferSize=draw_data->TotalVtxCount+5000;
	D3D11_BUFFER_DESC desc;
	SetMemory(&desc,0,sizeof(D3D11_BUFFER_DESC));
	desc.Usage=D3D11_USAGE_DYNAMIC;
	desc.ByteWidth=g_VertexBufferSize*sizeof(ImDrawVert);
	desc.BindFlags=D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags=D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags=0;
	if(g_pd3dDevice->CreateBuffer(&desc,NULL,&g_pVB)< 0)
	return;
	}
	if(!g_pIB||g_IndexBufferSize < draw_data->TotalIdxCount)
	{
	if(g_pIB){g_pIB->Release();g_pIB=NULL;}
	g_IndexBufferSize=draw_data->TotalIdxCount+10000;
	D3D11_BUFFER_DESC desc;
	SetMemory(&desc,0,sizeof(D3D11_BUFFER_DESC));
	desc.Usage=D3D11_USAGE_DYNAMIC;
	desc.ByteWidth=g_IndexBufferSize*sizeof(ImDrawIdx);
	desc.BindFlags=D3D11_BIND_INDEX_BUFFER;
	desc.CPUAccessFlags=D3D11_CPU_ACCESS_WRITE;
	if(g_pd3dDevice->CreateBuffer(&desc,NULL,&g_pIB)< 0)
	return;
	}
	D3D11_MAPPED_SUBRESOURCE vtx_resource,idx_resource;
	if(ctx->Map(g_pVB,0,D3D11_MAP_WRITE_DISCARD,0,&vtx_resource)!=S_OK)
	return;
	if(ctx->Map(g_pIB,0,D3D11_MAP_WRITE_DISCARD,0,&idx_resource)!=S_OK)
	return;
	ImDrawVert*vtx_dst=(ImDrawVert*)vtx_resource.pData;
	ImDrawIdx*idx_dst=(ImDrawIdx*)idx_resource.pData;
	for(int n=0;n < draw_data->CmdListsCount;n++)
	{
	const ImDrawList*cmd_list=draw_data->CmdLists[n];
	CopyMemory(vtx_dst,cmd_list->VtxBuffer.Data,cmd_list->VtxBuffer.Size*sizeof(ImDrawVert));
	CopyMemory(idx_dst,cmd_list->IdxBuffer.Data,cmd_list->IdxBuffer.Size*sizeof(ImDrawIdx));
	vtx_dst+=cmd_list->VtxBuffer.Size;
	idx_dst+=cmd_list->IdxBuffer.Size;
	}
	ctx->Unmap(g_pVB,0);
	ctx->Unmap(g_pIB,0);
	{
	D3D11_MAPPED_SUBRESOURCE mapped_resource;
	if(ctx->Map(g_pVertexConstantBuffer,0,D3D11_MAP_WRITE_DISCARD,0,&mapped_resource)!=S_OK)
	return;
	VERTEX_CONSTANT_BUFFER*constant_buffer=(VERTEX_CONSTANT_BUFFER*)mapped_resource.pData;
	float L=draw_data->DisplayPos.x;
	float R=draw_data->DisplayPos.x+draw_data->DisplaySize.x;
	float T=draw_data->DisplayPos.y;
	float B=draw_data->DisplayPos.y+draw_data->DisplaySize.y;
	float mvp[4][4]=
	{
	{2.0f/(R-L),0.0f,0.0f,0.0f},
	{0.0f,2.0f/(T-B),0.0f,0.0f},
	{0.0f,0.0f,0.5f,0.0f},
	{(R+L)/(L-R),(T+B)/(B-T),0.5f,1.0f},
	};
	CopyMemory(&constant_buffer->mvp,mvp,sizeof(mvp));
	ctx->Unmap(g_pVertexConstantBuffer,0);
	}
	struct BACKUP_DX11_STATE
	{
	UINT ScissorRectsCount,ViewportsCount;
	D3D11_RECT ScissorRects[D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE];
	D3D11_VIEWPORT Viewports[D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE];
	ID3D11RasterizerState*RS;
	ID3D11BlendState*BlendState;
	FLOAT BlendFactor[4];
	UINT SampleMask;
	UINT StencilRef;
	ID3D11DepthStencilState*DepthStencilState;
	ID3D11ShaderResourceView*PSShaderResource;
	ID3D11SamplerState*PSSampler;
	ID3D11PixelShader*PS;
	ID3D11VertexShader*VS;
	UINT PSInstancesCount,VSInstancesCount;
	ID3D11ClassInstance*PSInstances[256],*VSInstances[256];
	D3D11_PRIMITIVE_TOPOLOGY PrimitiveTopology;
	ID3D11Buffer*IndexBuffer,*VertexBuffer,*VSConstantBuffer;
	UINT IndexBufferOffset,VertexBufferStride,VertexBufferOffset;
	DXGI_FORMAT IndexBufferFormat;
	ID3D11InputLayout*InputLayout;
	};
	BACKUP_DX11_STATE old;
	old.ScissorRectsCount=old.ViewportsCount=D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE;
	ctx->RSGetScissorRects(&old.ScissorRectsCount,old.ScissorRects);
	ctx->RSGetViewports(&old.ViewportsCount,old.Viewports);
	ctx->RSGetState(&old.RS);
	ctx->OMGetBlendState(&old.BlendState,old.BlendFactor,&old.SampleMask);
	ctx->OMGetDepthStencilState(&old.DepthStencilState,&old.StencilRef);
	ctx->PSGetShaderResources(0,1,&old.PSShaderResource);
	ctx->PSGetSamplers(0,1,&old.PSSampler);
	old.PSInstancesCount=old.VSInstancesCount=256;
	ctx->PSGetShader(&old.PS,old.PSInstances,&old.PSInstancesCount);
	ctx->VSGetShader(&old.VS,old.VSInstances,&old.VSInstancesCount);
	ctx->VSGetConstantBuffers(0,1,&old.VSConstantBuffer);
	ctx->IAGetPrimitiveTopology(&old.PrimitiveTopology);
	ctx->IAGetIndexBuffer(&old.IndexBuffer,&old.IndexBufferFormat,&old.IndexBufferOffset);
	ctx->IAGetVertexBuffers(0,1,&old.VertexBuffer,&old.VertexBufferStride,&old.VertexBufferOffset);
	ctx->IAGetInputLayout(&old.InputLayout);
	D3D11_VIEWPORT vp;
	SetMemory(&vp,0,sizeof(D3D11_VIEWPORT));
	vp.Width=draw_data->DisplaySize.x;
	vp.Height=draw_data->DisplaySize.y;
	vp.MinDepth=0.0f;
	vp.MaxDepth=1.0f;
	vp.TopLeftX=vp.TopLeftY=0;
	ctx->RSSetViewports(1,&vp);
	unsigned int stride=sizeof(ImDrawVert);
	unsigned int offset=0;
	ctx->IASetInputLayout(g_pInputLayout);
	ctx->IASetVertexBuffers(0,1,&g_pVB,&stride,&offset);
	ctx->IASetIndexBuffer(g_pIB,sizeof(ImDrawIdx)==2 ? DXGI_FORMAT_R16_UINT : DXGI_FORMAT_R32_UINT,0);
	ctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	ctx->VSSetShader(g_pVertexShader,NULL,0);
	ctx->VSSetConstantBuffers(0,1,&g_pVertexConstantBuffer);
	ctx->PSSetShader(g_pPixelShader,NULL,0);
	ctx->PSSetSamplers(0,1,&g_pFontSampler);
	const float blend_factor[4]={0.f,0.f,0.f,0.f};
	ctx->OMSetBlendState(g_pBlendState,blend_factor,0xffffffff);
	ctx->OMSetDepthStencilState(g_pDepthStencilState,0);
	ctx->RSSetState(g_pRasterizerState);
	int vtx_offset=0;
	int idx_offset=0;
	ImVec2 pos=draw_data->DisplayPos;
	for(int n=0;n < draw_data->CmdListsCount;n++)
	{
	const ImDrawList*cmd_list=draw_data->CmdLists[n];
	for(int cmd_i=0;cmd_i < cmd_list->CmdBuffer.Size;cmd_i++)
	{
	const ImDrawCmd*pcmd=&cmd_list->CmdBuffer[cmd_i];
	if(pcmd->UserCallback)
	{
	pcmd->UserCallback(cmd_list,pcmd);
	}
	else
	{
	const D3D11_RECT r={(LONG)(pcmd->ClipRect.x-pos.x),(LONG)(pcmd->ClipRect.y-pos.y),(LONG)(pcmd->ClipRect.z-pos.x),(LONG)(pcmd->ClipRect.w-pos.y)};
	ctx->RSSetScissorRects(1,&r);
	ID3D11ShaderResourceView*texture_srv=(ID3D11ShaderResourceView*)pcmd->TextureId;
	ctx->PSSetShaderResources(0,1,&texture_srv);
	ctx->DrawIndexed(pcmd->ElemCount,idx_offset,vtx_offset);
	}
	idx_offset+=pcmd->ElemCount;
	}
	vtx_offset+=cmd_list->VtxBuffer.Size;
	}





	ctx->RSSetScissorRects(old.ScissorRectsCount,old.ScissorRects);
	ctx->RSSetViewports(old.ViewportsCount,old.Viewports);
	ctx->RSSetState(old.RS);if(old.RS)old.RS->Release();
	ctx->OMSetBlendState(old.BlendState,old.BlendFactor,old.SampleMask);if(old.BlendState)old.BlendState->Release();
	ctx->OMSetDepthStencilState(old.DepthStencilState,old.StencilRef);if(old.DepthStencilState)old.DepthStencilState->Release();
	ctx->PSSetShaderResources(0,1,&old.PSShaderResource);if(old.PSShaderResource)old.PSShaderResource->Release();
	ctx->PSSetSamplers(0,1,&old.PSSampler);if(old.PSSampler)old.PSSampler->Release();
	ctx->PSSetShader(old.PS,old.PSInstances,old.PSInstancesCount);if(old.PS)old.PS->Release();
	for(UINT i=0;i < old.PSInstancesCount;i++)if(old.PSInstances[i])old.PSInstances[i]->Release();
	ctx->VSSetShader(old.VS,old.VSInstances,old.VSInstancesCount);if(old.VS)old.VS->Release();
	ctx->VSSetConstantBuffers(0,1,&old.VSConstantBuffer);if(old.VSConstantBuffer)old.VSConstantBuffer->Release();
	for(UINT i=0;i < old.VSInstancesCount;i++)if(old.VSInstances[i])old.VSInstances[i]->Release();
	ctx->IASetPrimitiveTopology(old.PrimitiveTopology);
	ctx->IASetIndexBuffer(old.IndexBuffer,old.IndexBufferFormat,old.IndexBufferOffset);if(old.IndexBuffer)old.IndexBuffer->Release();
	ctx->IASetVertexBuffers(0,1,&old.VertexBuffer,&old.VertexBufferStride,&old.VertexBufferOffset);if(old.VertexBuffer)old.VertexBuffer->Release();
	ctx->IASetInputLayout(old.InputLayout);if(old.InputLayout)old.InputLayout->Release();
}





void CreateFontsTexture()
{
	ImGuiIO&io=ImGui::GetIO();
	unsigned char*pixels;
	int width,height;
	io.Fonts->GetTexDataAsRGBA32(&pixels,&width,&height);
	{
	D3D11_TEXTURE2D_DESC desc;
	SetMemory(&desc,0,sizeof(desc));
	desc.Width=width;
	desc.Height=height;
	desc.MipLevels=1;
	desc.ArraySize=1;
	desc.Format=DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count=1;
	desc.Usage=D3D11_USAGE_DEFAULT;
	desc.BindFlags=D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags=0;
	ID3D11Texture2D*pTexture=NULL;
	D3D11_SUBRESOURCE_DATA subResource;
	subResource.pSysMem=pixels;
	subResource.SysMemPitch=desc.Width*4;
	subResource.SysMemSlicePitch=0;
	g_pd3dDevice->CreateTexture2D(&desc,&subResource,&pTexture);
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	SetMemory(&srvDesc,0,sizeof(srvDesc));
	srvDesc.Format=DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension=D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels=desc.MipLevels;
	srvDesc.Texture2D.MostDetailedMip=0;
	g_pd3dDevice->CreateShaderResourceView(pTexture,&srvDesc,&g_pFontTextureView);
	pTexture->Release();
	}
	io.Fonts->TexID=(ImTextureID)g_pFontTextureView;
	{
	D3D11_SAMPLER_DESC desc;
	SetMemory(&desc,0,sizeof(desc));
	desc.Filter=D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	desc.AddressU=D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressV=D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressW=D3D11_TEXTURE_ADDRESS_WRAP;
	desc.MipLODBias=0.f;
	desc.ComparisonFunc=D3D11_COMPARISON_ALWAYS;
	desc.MinLOD=0.f;
	desc.MaxLOD=0.f;
	g_pd3dDevice->CreateSamplerState(&desc,&g_pFontSampler);
	}
}

export void InvalidateDeviceObjects()
{
	if(!g_pd3dDevice)
	return;
	if(g_pFontSampler){g_pFontSampler->Release();g_pFontSampler=NULL;}
	if(g_pFontTextureView){g_pFontTextureView->Release();g_pFontTextureView=NULL;ImGui::GetIO().Fonts->TexID=NULL;}
	if(g_pIB){g_pIB->Release();g_pIB=NULL;}
	if(g_pVB){g_pVB->Release();g_pVB=NULL;}
	if(g_pBlendState){g_pBlendState->Release();g_pBlendState=NULL;}
	if(g_pDepthStencilState){g_pDepthStencilState->Release();g_pDepthStencilState=NULL;}
	if(g_pRasterizerState){g_pRasterizerState->Release();g_pRasterizerState=NULL;}
	if(g_pPixelShader){g_pPixelShader->Release();g_pPixelShader=NULL;}
	if(g_pPixelShaderBlob){g_pPixelShaderBlob->Release();g_pPixelShaderBlob=NULL;}
	if(g_pVertexConstantBuffer){g_pVertexConstantBuffer->Release();g_pVertexConstantBuffer=NULL;}
	if(g_pInputLayout){g_pInputLayout->Release();g_pInputLayout=NULL;}
	if(g_pVertexShader){g_pVertexShader->Release();g_pVertexShader=NULL;}
	if(g_pVertexShaderBlob){g_pVertexShaderBlob->Release();g_pVertexShaderBlob=NULL;}
}

export bool CreateDeviceObjects()
{
	if(!g_pd3dDevice)
	return false;
	if(g_pFontSampler)
	InvalidateDeviceObjects();
	{
	static const char*vertexShader=
	"cbuffer vertexBuffer : register(b0)\
	{\
	float4x4 ProjectionMatrix;\
	};\
	struct VS_INPUT\
	{\
	float2 pos : POSITION;\
	float4 col : COLOR0;\
	float2 uv : TEXCOORD0;\
	};\
	\
	struct PS_INPUT\
	{\
	float4 pos : SV_POSITION;\
	float4 col : COLOR0;\
	float2 uv : TEXCOORD0;\
	};\
	\
	PS_INPUT main(VS_INPUT input)\
	{\
	PS_INPUT output;\
	output.pos=mul(ProjectionMatrix,float4(input.pos.xy,0.f,1.f));\
	output.col=input.col;\
	output.uv=input.uv;\
	return output;\
	}";
	D3DCompile(vertexShader,strlen(vertexShader),NULL,NULL,NULL,"main","vs_4_0",0,0,&g_pVertexShaderBlob,NULL);
	if(g_pVertexShaderBlob==NULL)
	return false;
	if(g_pd3dDevice->CreateVertexShader((byte32*)g_pVertexShaderBlob->GetBufferPointer(),g_pVertexShaderBlob->GetBufferSize(),NULL,&g_pVertexShader)!=S_OK)
	return false;
	D3D11_INPUT_ELEMENT_DESC local_layout[]=
	{
	{"POSITION",0,DXGI_FORMAT_R32G32_FLOAT,0,(size_t)(&((ImDrawVert*)0)->pos),D3D11_INPUT_PER_VERTEX_DATA,0},
	{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,(size_t)(&((ImDrawVert*)0)->uv),D3D11_INPUT_PER_VERTEX_DATA,0},
	{"COLOR",0,DXGI_FORMAT_R8G8B8A8_UNORM,0,(size_t)(&((ImDrawVert*)0)->col),D3D11_INPUT_PER_VERTEX_DATA,0},
	};
	if(g_pd3dDevice->CreateInputLayout(local_layout,3,g_pVertexShaderBlob->GetBufferPointer(),g_pVertexShaderBlob->GetBufferSize(),&g_pInputLayout)!=S_OK)
	return false;
	{
	D3D11_BUFFER_DESC desc;
	desc.ByteWidth=sizeof(VERTEX_CONSTANT_BUFFER);
	desc.Usage=D3D11_USAGE_DYNAMIC;
	desc.BindFlags=D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags=D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags=0;
	g_pd3dDevice->CreateBuffer(&desc,NULL,&g_pVertexConstantBuffer);
	}
	}
	{
	static const char*pixelShader=
	"struct PS_INPUT\
	{\
	float4 pos : SV_POSITION;\
	float4 col : COLOR0;\
	float2 uv : TEXCOORD0;\
	};\
	sampler sampler0;\
	Texture2D texture0;\
	\
	float4 main(PS_INPUT input): SV_Target\
	{\
	float4 out_col=input.col*texture0.Sample(sampler0,input.uv);\
	return out_col;\
	}";
	D3DCompile(pixelShader,strlen(pixelShader),NULL,NULL,NULL,"main","ps_4_0",0,0,&g_pPixelShaderBlob,NULL);
	if(g_pPixelShaderBlob==NULL)
	return false;
	if(g_pd3dDevice->CreatePixelShader((byte32*)g_pPixelShaderBlob->GetBufferPointer(),g_pPixelShaderBlob->GetBufferSize(),NULL,&g_pPixelShader)!=S_OK)
	return false;
	}
	{
	D3D11_BLEND_DESC desc;
	SetMemory(&desc,0,sizeof(desc));
	desc.AlphaToCoverageEnable=false;
	desc.RenderTarget[0].BlendEnable=true;
	desc.RenderTarget[0].SrcBlend=D3D11_BLEND_SRC_ALPHA;
	desc.RenderTarget[0].DestBlend=D3D11_BLEND_INV_SRC_ALPHA;
	desc.RenderTarget[0].BlendOp=D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].SrcBlendAlpha=D3D11_BLEND_INV_SRC_ALPHA;
	desc.RenderTarget[0].DestBlendAlpha=D3D11_BLEND_ZERO;
	desc.RenderTarget[0].BlendOpAlpha=D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].RenderTargetWriteMask=D3D11_COLOR_WRITE_ENABLE_ALL;
	g_pd3dDevice->CreateBlendState(&desc,&g_pBlendState);
	}
	{
	D3D11_RASTERIZER_DESC desc;
	SetMemory(&desc,0,sizeof(desc));
	desc.FillMode=D3D11_FILL_SOLID;
	desc.CullMode=D3D11_CULL_NONE;
	desc.ScissorEnable=true;
	desc.DepthClipEnable=true;
	g_pd3dDevice->CreateRasterizerState(&desc,&g_pRasterizerState);
	}
	{
	D3D11_DEPTH_STENCIL_DESC desc;
	SetMemory(&desc,0,sizeof(desc));
	desc.DepthEnable=false;
	desc.DepthWriteMask=D3D11_DEPTH_WRITE_MASK_ALL;
	desc.DepthFunc=D3D11_COMPARISON_ALWAYS;
	desc.StencilEnable=false;
	desc.FrontFace.StencilFailOp=desc.FrontFace.StencilDepthFailOp=desc.FrontFace.StencilPassOp=D3D11_STENCIL_OP_KEEP;
	desc.FrontFace.StencilFunc=D3D11_COMPARISON_ALWAYS;
	desc.BackFace=desc.FrontFace;
	g_pd3dDevice->CreateDepthStencilState(&desc,&g_pDepthStencilState);
	}
	CreateFontsTexture();
	return true;
}

export bool Init(ID3D11Device*device,ID3D11DeviceContext*device_context)
{
	IDXGIDevice*pDXGIDevice=NULL;
	IDXGIAdapter*pDXGIAdapter=NULL;
	IDXGIFactory*pFactory=NULL;
	{
	g_pd3dDevice=device;
	g_pd3dDeviceContext=device_context;
	g_pFactory=pFactory;
	}
	if(pDXGIDevice)pDXGIDevice->Release();
	if(pDXGIAdapter)pDXGIAdapter->Release();
	return true;
}

export void Shutdown()
{
	InvalidateDeviceObjects();
	if(g_pFactory){g_pFactory->Release();g_pFactory=NULL;}
	g_pd3dDevice=NULL;
	g_pd3dDeviceContext=NULL;
}

export void NewFrame()
{
	if(!g_pFontSampler)
	CreateDeviceObjects();
}

namespaceEnd();

#pragma endregion

#pragma region DI8

namespaceStart(DI8);

export void Init()
{
	LogFunction();

	auto & io = GetIO();

	io.KeyMap[ImGuiKey_Tab       ] = KEY::TAB;
	io.KeyMap[ImGuiKey_LeftArrow ] = KEY::LEFT;
	io.KeyMap[ImGuiKey_RightArrow] = KEY::RIGHT;
	io.KeyMap[ImGuiKey_UpArrow   ] = KEY::UP;
	io.KeyMap[ImGuiKey_DownArrow ] = KEY::DOWN;
	io.KeyMap[ImGuiKey_PageUp    ] = KEY::PAGE_UP;
	io.KeyMap[ImGuiKey_PageDown  ] = KEY::PAGE_DOWN;
	io.KeyMap[ImGuiKey_Home      ] = KEY::HOME;
	io.KeyMap[ImGuiKey_End       ] = KEY::END;
	io.KeyMap[ImGuiKey_Insert    ] = KEY::INSERT;
	io.KeyMap[ImGuiKey_Delete    ] = KEY::DELETE;
	io.KeyMap[ImGuiKey_Backspace ] = KEY::BACKSPACE;
	io.KeyMap[ImGuiKey_Space     ] = KEY::SPACE;
	io.KeyMap[ImGuiKey_Enter     ] = KEY::ENTER;
	io.KeyMap[ImGuiKey_Escape    ] = KEY::ESCAPE;
	io.KeyMap[ImGuiKey_A         ] = KEY::A;
	io.KeyMap[ImGuiKey_C         ] = KEY::C;
	io.KeyMap[ImGuiKey_V         ] = KEY::V;
	io.KeyMap[ImGuiKey_X         ] = KEY::X;
	io.KeyMap[ImGuiKey_Y         ] = KEY::Y;
	io.KeyMap[ImGuiKey_Z         ] = KEY::Z;
}

// @Update
export void UpdateKeyboard(byte8 * state)
{
	auto & io = GetIO();

	io.KeyCtrl  = ((state[KEY::LEFT_CONTROL] & 0x80) || (state[KEY::RIGHT_CONTROL] & 0x80)) ? true : false;
	io.KeyShift = ((state[KEY::LEFT_SHIFT  ] & 0x80) || (state[KEY::RIGHT_SHIFT  ] & 0x80)) ? true : false;
	io.KeyAlt   = ((state[KEY::LEFT_ALT    ] & 0x80) || (state[KEY::RIGHT_ALT    ] & 0x80)) ? true : false;

	SetMemory
	(
		io.KeysDown,
		0,
		256
	);

	old_for_all(uint32, index, 256)
	{
		if (state[index] & 0x80)
		{
			io.KeysDown[index] = true;
		}
	}
}

export vec2 mousePositionMultiplier =
{
	1,
	1
};




export void UpdateMouse
(
	HWND windowHandle,
	DIMOUSESTATE2 * state
)
{
	if
	(
		!windowHandle ||
		(GetForegroundWindow() != appWindow)
	)
	{
		return;
	}

	auto & io = GetIO();

	POINT pos = {};

	GetCursorPos(&pos);

	ScreenToClient(windowHandle, &pos);

	io.MousePos = ImVec2
	(
		static_cast<float>(pos.x),
		static_cast<float>(pos.y)
	);

	io.MousePos.x *= mousePositionMultiplier.x;
	io.MousePos.y *= mousePositionMultiplier.y;

	for_all(index, countof(io.MouseDown))
	{
		io.MouseDown[index] = (state->rgbButtons[index]) ? true : false;
	}

	io.MouseWheel += (static_cast<float>(state->lZ) / static_cast<float>(WHEEL_DELTA));
}

namespaceEnd();

#pragma endregion

export void UpdateDisplaySize
(
	uint32 width,
	uint32 height
)
{
	Log
	(
		"%s %u %u",
		FUNC_NAME,
		width,
		height
	);

	auto & io = GetIO();

	io.DisplaySize.x = static_cast<float>(width  + 1920);
	io.DisplaySize.y = static_cast<float>(height + 1080);
}

namespaceEnd();
