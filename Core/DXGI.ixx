module;

#pragma warning(disable: 5202)

typedef unsigned char byte8;

template
<
	typename T1,
	typename T2
>
struct TypeMatch
{
	static constexpr bool value = false;
};

template <typename T>
struct TypeMatch<T, T>
{
	static constexpr bool value = true;
};

#define offsetof(s, m) __builtin_offsetof(s, m)

#define _Prep_Merge(a, b) a##b
#define Prep_Merge(a, b) _Prep_Merge(a, b)

#define _(size) struct { byte8 Prep_Merge(padding_, __LINE__)[size]; }

#define namespaceStart(name) namespace name {
#define namespaceEnd() }

export module DXGI;

import Windows;

using namespace Windows;

export namespaceStart(DXGI);

#ifdef _WIN64

#pragma region x86_64

struct IDXGIObject;
struct IDXGIDeviceSubObject;
struct IDXGIResource;
struct IDXGIKeyedMutex;
struct IDXGISurface;
struct IDXGISurface1;
struct IDXGIAdapter;
struct IDXGIOutput;
struct IDXGISwapChain;
struct IDXGIFactory;
struct IDXGIDevice;
struct IDXGIFactory1;
struct IDXGIAdapter1;
struct IDXGIDevice1;

extern "C" const IID IID_IDXGIObject;
extern "C" const IID IID_IDXGIDeviceSubObject;
extern "C" const IID IID_IDXGIResource;
extern "C" const IID IID_IDXGIKeyedMutex;
extern "C" const IID IID_IDXGISurface;
extern "C" const IID IID_IDXGISurface1;
extern "C" const IID IID_IDXGIAdapter;
extern "C" const IID IID_IDXGIOutput;
extern "C" const IID IID_IDXGISwapChain;
extern "C" const IID IID_IDXGIFactory;
extern "C" const IID IID_IDXGIDevice;
extern "C" const IID IID_IDXGIFactory1;
extern "C" const IID IID_IDXGIAdapter1;
extern "C" const IID IID_IDXGIDevice1;

// DXGI_USAGE

typedef UINT DXGI_USAGE;

static_assert(TypeMatch<DXGI_USAGE, UINT>::value);

static_assert(sizeof(DXGI_USAGE) == 4);

// DXGI_FORMAT

enum DXGI_FORMAT
{
	DXGI_FORMAT_UNKNOWN=0,
	DXGI_FORMAT_R32G32B32A32_TYPELESS=1,
	DXGI_FORMAT_R32G32B32A32_FLOAT=2,
	DXGI_FORMAT_R32G32B32A32_UINT=3,
	DXGI_FORMAT_R32G32B32A32_SINT=4,
	DXGI_FORMAT_R32G32B32_TYPELESS=5,
	DXGI_FORMAT_R32G32B32_FLOAT=6,
	DXGI_FORMAT_R32G32B32_UINT=7,
	DXGI_FORMAT_R32G32B32_SINT=8,
	DXGI_FORMAT_R16G16B16A16_TYPELESS=9,
	DXGI_FORMAT_R16G16B16A16_FLOAT=10,
	DXGI_FORMAT_R16G16B16A16_UNORM=11,
	DXGI_FORMAT_R16G16B16A16_UINT=12,
	DXGI_FORMAT_R16G16B16A16_SNORM=13,
	DXGI_FORMAT_R16G16B16A16_SINT=14,
	DXGI_FORMAT_R32G32_TYPELESS=15,
	DXGI_FORMAT_R32G32_FLOAT=16,
	DXGI_FORMAT_R32G32_UINT=17,
	DXGI_FORMAT_R32G32_SINT=18,
	DXGI_FORMAT_R32G8X24_TYPELESS=19,
	DXGI_FORMAT_D32_FLOAT_S8X24_UINT=20,
	DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS=21,
	DXGI_FORMAT_X32_TYPELESS_G8X24_UINT=22,
	DXGI_FORMAT_R10G10B10A2_TYPELESS=23,
	DXGI_FORMAT_R10G10B10A2_UNORM=24,
	DXGI_FORMAT_R10G10B10A2_UINT=25,
	DXGI_FORMAT_R11G11B10_FLOAT=26,
	DXGI_FORMAT_R8G8B8A8_TYPELESS=27,
	DXGI_FORMAT_R8G8B8A8_UNORM=28,
	DXGI_FORMAT_R8G8B8A8_UNORM_SRGB=29,
	DXGI_FORMAT_R8G8B8A8_UINT=30,
	DXGI_FORMAT_R8G8B8A8_SNORM=31,
	DXGI_FORMAT_R8G8B8A8_SINT=32,
	DXGI_FORMAT_R16G16_TYPELESS=33,
	DXGI_FORMAT_R16G16_FLOAT=34,
	DXGI_FORMAT_R16G16_UNORM=35,
	DXGI_FORMAT_R16G16_UINT=36,
	DXGI_FORMAT_R16G16_SNORM=37,
	DXGI_FORMAT_R16G16_SINT=38,
	DXGI_FORMAT_R32_TYPELESS=39,
	DXGI_FORMAT_D32_FLOAT=40,
	DXGI_FORMAT_R32_FLOAT=41,
	DXGI_FORMAT_R32_UINT=42,
	DXGI_FORMAT_R32_SINT=43,
	DXGI_FORMAT_R24G8_TYPELESS=44,
	DXGI_FORMAT_D24_UNORM_S8_UINT=45,
	DXGI_FORMAT_R24_UNORM_X8_TYPELESS=46,
	DXGI_FORMAT_X24_TYPELESS_G8_UINT=47,
	DXGI_FORMAT_R8G8_TYPELESS=48,
	DXGI_FORMAT_R8G8_UNORM=49,
	DXGI_FORMAT_R8G8_UINT=50,
	DXGI_FORMAT_R8G8_SNORM=51,
	DXGI_FORMAT_R8G8_SINT=52,
	DXGI_FORMAT_R16_TYPELESS=53,
	DXGI_FORMAT_R16_FLOAT=54,
	DXGI_FORMAT_D16_UNORM=55,
	DXGI_FORMAT_R16_UNORM=56,
	DXGI_FORMAT_R16_UINT=57,
	DXGI_FORMAT_R16_SNORM=58,
	DXGI_FORMAT_R16_SINT=59,
	DXGI_FORMAT_R8_TYPELESS=60,
	DXGI_FORMAT_R8_UNORM=61,
	DXGI_FORMAT_R8_UINT=62,
	DXGI_FORMAT_R8_SNORM=63,
	DXGI_FORMAT_R8_SINT=64,
	DXGI_FORMAT_A8_UNORM=65,
	DXGI_FORMAT_R1_UNORM=66,
	DXGI_FORMAT_R9G9B9E5_SHAREDEXP=67,
	DXGI_FORMAT_R8G8_B8G8_UNORM=68,
	DXGI_FORMAT_G8R8_G8B8_UNORM=69,
	DXGI_FORMAT_BC1_TYPELESS=70,
	DXGI_FORMAT_BC1_UNORM=71,
	DXGI_FORMAT_BC1_UNORM_SRGB=72,
	DXGI_FORMAT_BC2_TYPELESS=73,
	DXGI_FORMAT_BC2_UNORM=74,
	DXGI_FORMAT_BC2_UNORM_SRGB=75,
	DXGI_FORMAT_BC3_TYPELESS=76,
	DXGI_FORMAT_BC3_UNORM=77,
	DXGI_FORMAT_BC3_UNORM_SRGB=78,
	DXGI_FORMAT_BC4_TYPELESS=79,
	DXGI_FORMAT_BC4_UNORM=80,
	DXGI_FORMAT_BC4_SNORM=81,
	DXGI_FORMAT_BC5_TYPELESS=82,
	DXGI_FORMAT_BC5_UNORM=83,
	DXGI_FORMAT_BC5_SNORM=84,
	DXGI_FORMAT_B5G6R5_UNORM=85,
	DXGI_FORMAT_B5G5R5A1_UNORM=86,
	DXGI_FORMAT_B8G8R8A8_UNORM=87,
	DXGI_FORMAT_B8G8R8X8_UNORM=88,
	DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM=89,
	DXGI_FORMAT_B8G8R8A8_TYPELESS=90,
	DXGI_FORMAT_B8G8R8A8_UNORM_SRGB=91,
	DXGI_FORMAT_B8G8R8X8_TYPELESS=92,
	DXGI_FORMAT_B8G8R8X8_UNORM_SRGB=93,
	DXGI_FORMAT_BC6H_TYPELESS=94,
	DXGI_FORMAT_BC6H_UF16=95,
	DXGI_FORMAT_BC6H_SF16=96,
	DXGI_FORMAT_BC7_TYPELESS=97,
	DXGI_FORMAT_BC7_UNORM=98,
	DXGI_FORMAT_BC7_UNORM_SRGB=99,
	DXGI_FORMAT_AYUV=100,
	DXGI_FORMAT_Y410=101,
	DXGI_FORMAT_Y416=102,
	DXGI_FORMAT_NV12=103,
	DXGI_FORMAT_P010=104,
	DXGI_FORMAT_P016=105,
	DXGI_FORMAT_420_OPAQUE=106,
	DXGI_FORMAT_YUY2=107,
	DXGI_FORMAT_Y210=108,
	DXGI_FORMAT_Y216=109,
	DXGI_FORMAT_NV11=110,
	DXGI_FORMAT_AI44=111,
	DXGI_FORMAT_IA44=112,
	DXGI_FORMAT_P8=113,
	DXGI_FORMAT_A8P8=114,
	DXGI_FORMAT_B4G4R4A4_UNORM=115,
	DXGI_FORMAT_P208=130,
	DXGI_FORMAT_V208=131,
	DXGI_FORMAT_V408=132,
	DXGI_FORMAT_FORCE_UINT=0xffffffff,
};

// DXGI_MODE_SCANLINE_ORDER

enum DXGI_MODE_SCANLINE_ORDER
{
	DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED=0,
	DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE=1,
	DXGI_MODE_SCANLINE_ORDER_UPPER_FIELD_FIRST=2,
	DXGI_MODE_SCANLINE_ORDER_LOWER_FIELD_FIRST=3,
};

// DXGI_MODE_SCALING

enum DXGI_MODE_SCALING
{
	DXGI_MODE_SCALING_UNSPECIFIED=0,
	DXGI_MODE_SCALING_CENTERED=1,
	DXGI_MODE_SCALING_STRETCHED=2,
};

// DXGI_MODE_ROTATION

enum DXGI_MODE_ROTATION
{
	DXGI_MODE_ROTATION_UNSPECIFIED=0,
	DXGI_MODE_ROTATION_IDENTITY=1,
	DXGI_MODE_ROTATION_ROTATE90=2,
	DXGI_MODE_ROTATION_ROTATE180=3,
	DXGI_MODE_ROTATION_ROTATE270=4,
};

// DXGI_SWAP_EFFECT

enum DXGI_SWAP_EFFECT
{
	DXGI_SWAP_EFFECT_DISCARD=0,
	DXGI_SWAP_EFFECT_SEQUENTIAL=1,
	DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL=3,
	DXGI_SWAP_EFFECT_FLIP_DISCARD=4,
};

// DXGI_RESIDENCY

enum DXGI_RESIDENCY
{
	DXGI_RESIDENCY_FULLY_RESIDENT=1,
	DXGI_RESIDENCY_RESIDENT_IN_SHARED_MEMORY=2,
	DXGI_RESIDENCY_EVICTED_TO_DISK=3,
};

#pragma pack(push, 1)

// DXGI_RATIONAL

struct DXGI_RATIONAL
{
	UINT Numerator; // 0
	UINT Denominator; // 4
};

static_assert(TypeMatch<decltype(DXGI_RATIONAL::Numerator), UINT>::value);
static_assert(TypeMatch<decltype(DXGI_RATIONAL::Denominator), UINT>::value);

static_assert(offsetof(DXGI_RATIONAL, Numerator) == 0);
static_assert(offsetof(DXGI_RATIONAL, Denominator) == 4);

static_assert(sizeof(DXGI_RATIONAL) == 8);

// DXGI_SAMPLE_DESC

struct DXGI_SAMPLE_DESC
{
	UINT Count; // 0
	UINT Quality; // 4
};

static_assert(TypeMatch<decltype(DXGI_SAMPLE_DESC::Count), UINT>::value);
static_assert(TypeMatch<decltype(DXGI_SAMPLE_DESC::Quality), UINT>::value);

static_assert(offsetof(DXGI_SAMPLE_DESC, Count) == 0);
static_assert(offsetof(DXGI_SAMPLE_DESC, Quality) == 4);

static_assert(sizeof(DXGI_SAMPLE_DESC) == 8);

// DXGI_MODE_DESC

struct DXGI_MODE_DESC
{
	UINT Width; // 0
	UINT Height; // 4
	DXGI_RATIONAL RefreshRate; // 8
	DXGI_FORMAT Format; // 0x10
	DXGI_MODE_SCANLINE_ORDER ScanlineOrdering; // 0x14
	DXGI_MODE_SCALING Scaling; // 0x18
};

static_assert(TypeMatch<decltype(DXGI_MODE_DESC::Width), UINT>::value);
static_assert(TypeMatch<decltype(DXGI_MODE_DESC::Height), UINT>::value);
static_assert(TypeMatch<decltype(DXGI_MODE_DESC::RefreshRate), DXGI_RATIONAL>::value);
static_assert(TypeMatch<decltype(DXGI_MODE_DESC::Format), DXGI_FORMAT>::value);
static_assert(TypeMatch<decltype(DXGI_MODE_DESC::ScanlineOrdering), DXGI_MODE_SCANLINE_ORDER>::value);
static_assert(TypeMatch<decltype(DXGI_MODE_DESC::Scaling), DXGI_MODE_SCALING>::value);

static_assert(offsetof(DXGI_MODE_DESC, Width) == 0);
static_assert(offsetof(DXGI_MODE_DESC, Height) == 4);
static_assert(offsetof(DXGI_MODE_DESC, RefreshRate) == 8);
static_assert(offsetof(DXGI_MODE_DESC, Format) == 0x10);
static_assert(offsetof(DXGI_MODE_DESC, ScanlineOrdering) == 0x14);
static_assert(offsetof(DXGI_MODE_DESC, Scaling) == 0x18);

static_assert(sizeof(DXGI_MODE_DESC) == 28);

// DXGI_SURFACE_DESC

struct DXGI_SURFACE_DESC
{
	UINT Width; // 0
	UINT Height; // 4
	DXGI_FORMAT Format; // 8
	DXGI_SAMPLE_DESC SampleDesc; // 0xC
};

static_assert(TypeMatch<decltype(DXGI_SURFACE_DESC::Width), UINT>::value);
static_assert(TypeMatch<decltype(DXGI_SURFACE_DESC::Height), UINT>::value);
static_assert(TypeMatch<decltype(DXGI_SURFACE_DESC::Format), DXGI_FORMAT>::value);
static_assert(TypeMatch<decltype(DXGI_SURFACE_DESC::SampleDesc), DXGI_SAMPLE_DESC>::value);

static_assert(offsetof(DXGI_SURFACE_DESC, Width) == 0);
static_assert(offsetof(DXGI_SURFACE_DESC, Height) == 4);
static_assert(offsetof(DXGI_SURFACE_DESC, Format) == 8);
static_assert(offsetof(DXGI_SURFACE_DESC, SampleDesc) == 0xC);

static_assert(sizeof(DXGI_SURFACE_DESC) == 20);

// DXGI_MAPPED_RECT

struct DXGI_MAPPED_RECT
{
	INT Pitch; // 0
	_(4);
	BYTE* pBits; // 8
};

static_assert(TypeMatch<decltype(DXGI_MAPPED_RECT::Pitch), INT>::value);
static_assert(TypeMatch<decltype(DXGI_MAPPED_RECT::pBits), BYTE*>::value);

static_assert(offsetof(DXGI_MAPPED_RECT, Pitch) == 0);
static_assert(offsetof(DXGI_MAPPED_RECT, pBits) == 8);

static_assert(sizeof(DXGI_MAPPED_RECT) == 16);

// DXGI_ADAPTER_DESC

struct DXGI_ADAPTER_DESC
{
	WCHAR Description[128]; // 0
	UINT VendorId; // 0x100
	UINT DeviceId; // 0x104
	UINT SubSysId; // 0x108
	UINT Revision; // 0x10C
	SIZE_T DedicatedVideoMemory; // 0x110
	SIZE_T DedicatedSystemMemory; // 0x118
	SIZE_T SharedSystemMemory; // 0x120
	LUID AdapterLuid; // 0x128
};

static_assert(TypeMatch<decltype(DXGI_ADAPTER_DESC::Description), WCHAR[128]>::value);
static_assert(TypeMatch<decltype(DXGI_ADAPTER_DESC::VendorId), UINT>::value);
static_assert(TypeMatch<decltype(DXGI_ADAPTER_DESC::DeviceId), UINT>::value);
static_assert(TypeMatch<decltype(DXGI_ADAPTER_DESC::SubSysId), UINT>::value);
static_assert(TypeMatch<decltype(DXGI_ADAPTER_DESC::Revision), UINT>::value);
static_assert(TypeMatch<decltype(DXGI_ADAPTER_DESC::DedicatedVideoMemory), SIZE_T>::value);
static_assert(TypeMatch<decltype(DXGI_ADAPTER_DESC::DedicatedSystemMemory), SIZE_T>::value);
static_assert(TypeMatch<decltype(DXGI_ADAPTER_DESC::SharedSystemMemory), SIZE_T>::value);
static_assert(TypeMatch<decltype(DXGI_ADAPTER_DESC::AdapterLuid), LUID>::value);

static_assert(offsetof(DXGI_ADAPTER_DESC, Description) == 0);
static_assert(offsetof(DXGI_ADAPTER_DESC, VendorId) == 0x100);
static_assert(offsetof(DXGI_ADAPTER_DESC, DeviceId) == 0x104);
static_assert(offsetof(DXGI_ADAPTER_DESC, SubSysId) == 0x108);
static_assert(offsetof(DXGI_ADAPTER_DESC, Revision) == 0x10C);
static_assert(offsetof(DXGI_ADAPTER_DESC, DedicatedVideoMemory) == 0x110);
static_assert(offsetof(DXGI_ADAPTER_DESC, DedicatedSystemMemory) == 0x118);
static_assert(offsetof(DXGI_ADAPTER_DESC, SharedSystemMemory) == 0x120);
static_assert(offsetof(DXGI_ADAPTER_DESC, AdapterLuid) == 0x128);

static_assert(sizeof(DXGI_ADAPTER_DESC) == 304);

// DXGI_SWAP_CHAIN_DESC

struct DXGI_SWAP_CHAIN_DESC
{
	DXGI_MODE_DESC BufferDesc; // 0
	DXGI_SAMPLE_DESC SampleDesc; // 0x1C
	DXGI_USAGE BufferUsage; // 0x24
	UINT BufferCount; // 0x28
	_(4);
	HWND OutputWindow; // 0x30
	BOOL Windowed; // 0x38
	DXGI_SWAP_EFFECT SwapEffect; // 0x3C
	UINT Flags; // 0x40
	_(4);
};

static_assert(TypeMatch<decltype(DXGI_SWAP_CHAIN_DESC::BufferDesc), DXGI_MODE_DESC>::value);
static_assert(TypeMatch<decltype(DXGI_SWAP_CHAIN_DESC::SampleDesc), DXGI_SAMPLE_DESC>::value);
static_assert(TypeMatch<decltype(DXGI_SWAP_CHAIN_DESC::BufferUsage), DXGI_USAGE>::value);
static_assert(TypeMatch<decltype(DXGI_SWAP_CHAIN_DESC::BufferCount), UINT>::value);
static_assert(TypeMatch<decltype(DXGI_SWAP_CHAIN_DESC::OutputWindow), HWND>::value);
static_assert(TypeMatch<decltype(DXGI_SWAP_CHAIN_DESC::Windowed), BOOL>::value);
static_assert(TypeMatch<decltype(DXGI_SWAP_CHAIN_DESC::SwapEffect), DXGI_SWAP_EFFECT>::value);
static_assert(TypeMatch<decltype(DXGI_SWAP_CHAIN_DESC::Flags), UINT>::value);

static_assert(offsetof(DXGI_SWAP_CHAIN_DESC, BufferDesc) == 0);
static_assert(offsetof(DXGI_SWAP_CHAIN_DESC, SampleDesc) == 0x1C);
static_assert(offsetof(DXGI_SWAP_CHAIN_DESC, BufferUsage) == 0x24);
static_assert(offsetof(DXGI_SWAP_CHAIN_DESC, BufferCount) == 0x28);
static_assert(offsetof(DXGI_SWAP_CHAIN_DESC, OutputWindow) == 0x30);
static_assert(offsetof(DXGI_SWAP_CHAIN_DESC, Windowed) == 0x38);
static_assert(offsetof(DXGI_SWAP_CHAIN_DESC, SwapEffect) == 0x3C);
static_assert(offsetof(DXGI_SWAP_CHAIN_DESC, Flags) == 0x40);

static_assert(sizeof(DXGI_SWAP_CHAIN_DESC) == 72);

// DXGI_FRAME_STATISTICS

struct DXGI_FRAME_STATISTICS
{
	UINT PresentCount; // 0
	UINT PresentRefreshCount; // 4
	UINT SyncRefreshCount; // 8
	_(4);
	LARGE_INTEGER SyncQPCTime; // 0x10
	LARGE_INTEGER SyncGPUTime; // 0x18
};

static_assert(TypeMatch<decltype(DXGI_FRAME_STATISTICS::PresentCount), UINT>::value);
static_assert(TypeMatch<decltype(DXGI_FRAME_STATISTICS::PresentRefreshCount), UINT>::value);
static_assert(TypeMatch<decltype(DXGI_FRAME_STATISTICS::SyncRefreshCount), UINT>::value);
static_assert(TypeMatch<decltype(DXGI_FRAME_STATISTICS::SyncQPCTime), LARGE_INTEGER>::value);
static_assert(TypeMatch<decltype(DXGI_FRAME_STATISTICS::SyncGPUTime), LARGE_INTEGER>::value);

static_assert(offsetof(DXGI_FRAME_STATISTICS, PresentCount) == 0);
static_assert(offsetof(DXGI_FRAME_STATISTICS, PresentRefreshCount) == 4);
static_assert(offsetof(DXGI_FRAME_STATISTICS, SyncRefreshCount) == 8);
static_assert(offsetof(DXGI_FRAME_STATISTICS, SyncQPCTime) == 0x10);
static_assert(offsetof(DXGI_FRAME_STATISTICS, SyncGPUTime) == 0x18);

static_assert(sizeof(DXGI_FRAME_STATISTICS) == 32);

// DXGI_RGB

struct DXGI_RGB
{
	float Red; // 0
	float Green; // 4
	float Blue; // 8
};

static_assert(TypeMatch<decltype(DXGI_RGB::Red), float>::value);
static_assert(TypeMatch<decltype(DXGI_RGB::Green), float>::value);
static_assert(TypeMatch<decltype(DXGI_RGB::Blue), float>::value);

static_assert(offsetof(DXGI_RGB, Red) == 0);
static_assert(offsetof(DXGI_RGB, Green) == 4);
static_assert(offsetof(DXGI_RGB, Blue) == 8);

static_assert(sizeof(DXGI_RGB) == 12);

// D3DCOLORVALUE

struct D3DCOLORVALUE
{
	float r; // 0
	float g; // 4
	float b; // 8
	float a; // 0xC
};

static_assert(TypeMatch<decltype(D3DCOLORVALUE::r), float>::value);
static_assert(TypeMatch<decltype(D3DCOLORVALUE::g), float>::value);
static_assert(TypeMatch<decltype(D3DCOLORVALUE::b), float>::value);
static_assert(TypeMatch<decltype(D3DCOLORVALUE::a), float>::value);

static_assert(offsetof(D3DCOLORVALUE, r) == 0);
static_assert(offsetof(D3DCOLORVALUE, g) == 4);
static_assert(offsetof(D3DCOLORVALUE, b) == 8);
static_assert(offsetof(D3DCOLORVALUE, a) == 0xC);

static_assert(sizeof(D3DCOLORVALUE) == 16);

// DXGI_GAMMA_CONTROL

struct DXGI_GAMMA_CONTROL
{
	DXGI_RGB Scale; // 0
	DXGI_RGB Offset; // 0xC
	DXGI_RGB GammaCurve[1025]; // 0x18
};

static_assert(TypeMatch<decltype(DXGI_GAMMA_CONTROL::Scale), DXGI_RGB>::value);
static_assert(TypeMatch<decltype(DXGI_GAMMA_CONTROL::Offset), DXGI_RGB>::value);
static_assert(TypeMatch<decltype(DXGI_GAMMA_CONTROL::GammaCurve), DXGI_RGB[1025]>::value);

static_assert(offsetof(DXGI_GAMMA_CONTROL, Scale) == 0);
static_assert(offsetof(DXGI_GAMMA_CONTROL, Offset) == 0xC);
static_assert(offsetof(DXGI_GAMMA_CONTROL, GammaCurve) == 0x18);

static_assert(sizeof(DXGI_GAMMA_CONTROL) == 12324);

// DXGI_GAMMA_CONTROL_CAPABILITIES

struct DXGI_GAMMA_CONTROL_CAPABILITIES
{
	BOOL ScaleAndOffsetSupported; // 0
	float MaxConvertedValue; // 4
	float MinConvertedValue; // 8
	UINT NumGammaControlPoints; // 0xC
	float ControlPointPositions[1025]; // 0x10
};

static_assert(TypeMatch<decltype(DXGI_GAMMA_CONTROL_CAPABILITIES::ScaleAndOffsetSupported), BOOL>::value);
static_assert(TypeMatch<decltype(DXGI_GAMMA_CONTROL_CAPABILITIES::MaxConvertedValue), float>::value);
static_assert(TypeMatch<decltype(DXGI_GAMMA_CONTROL_CAPABILITIES::MinConvertedValue), float>::value);
static_assert(TypeMatch<decltype(DXGI_GAMMA_CONTROL_CAPABILITIES::NumGammaControlPoints), UINT>::value);
static_assert(TypeMatch<decltype(DXGI_GAMMA_CONTROL_CAPABILITIES::ControlPointPositions), float[1025]>::value);

static_assert(offsetof(DXGI_GAMMA_CONTROL_CAPABILITIES, ScaleAndOffsetSupported) == 0);
static_assert(offsetof(DXGI_GAMMA_CONTROL_CAPABILITIES, MaxConvertedValue) == 4);
static_assert(offsetof(DXGI_GAMMA_CONTROL_CAPABILITIES, MinConvertedValue) == 8);
static_assert(offsetof(DXGI_GAMMA_CONTROL_CAPABILITIES, NumGammaControlPoints) == 0xC);
static_assert(offsetof(DXGI_GAMMA_CONTROL_CAPABILITIES, ControlPointPositions) == 0x10);

static_assert(sizeof(DXGI_GAMMA_CONTROL_CAPABILITIES) == 4116);

// DXGI_OUTPUT_DESC

struct DXGI_OUTPUT_DESC
{
	WCHAR DeviceName[32]; // 0
	RECT DesktopCoordinates; // 0x40
	BOOL AttachedToDesktop; // 0x50
	DXGI_MODE_ROTATION Rotation; // 0x54
	HMONITOR Monitor; // 0x58
};

static_assert(TypeMatch<decltype(DXGI_OUTPUT_DESC::DeviceName), WCHAR[32]>::value);
static_assert(TypeMatch<decltype(DXGI_OUTPUT_DESC::DesktopCoordinates), RECT>::value);
static_assert(TypeMatch<decltype(DXGI_OUTPUT_DESC::AttachedToDesktop), BOOL>::value);
static_assert(TypeMatch<decltype(DXGI_OUTPUT_DESC::Rotation), DXGI_MODE_ROTATION>::value);
static_assert(TypeMatch<decltype(DXGI_OUTPUT_DESC::Monitor), HMONITOR>::value);

static_assert(offsetof(DXGI_OUTPUT_DESC, DeviceName) == 0);
static_assert(offsetof(DXGI_OUTPUT_DESC, DesktopCoordinates) == 0x40);
static_assert(offsetof(DXGI_OUTPUT_DESC, AttachedToDesktop) == 0x50);
static_assert(offsetof(DXGI_OUTPUT_DESC, Rotation) == 0x54);
static_assert(offsetof(DXGI_OUTPUT_DESC, Monitor) == 0x58);

static_assert(sizeof(DXGI_OUTPUT_DESC) == 96);

// DXGI_SHARED_RESOURCE

struct DXGI_SHARED_RESOURCE
{
	HANDLE Handle; // 0
};

static_assert(TypeMatch<decltype(DXGI_SHARED_RESOURCE::Handle), HANDLE>::value);

static_assert(offsetof(DXGI_SHARED_RESOURCE, Handle) == 0);

static_assert(sizeof(DXGI_SHARED_RESOURCE) == 8);

// DXGI_ADAPTER_DESC1

struct DXGI_ADAPTER_DESC1
{
	WCHAR Description[128]; // 0
	UINT VendorId; // 0x100
	UINT DeviceId; // 0x104
	UINT SubSysId; // 0x108
	UINT Revision; // 0x10C
	SIZE_T DedicatedVideoMemory; // 0x110
	SIZE_T DedicatedSystemMemory; // 0x118
	SIZE_T SharedSystemMemory; // 0x120
	LUID AdapterLuid; // 0x128
	UINT Flags; // 0x130
	_(4);
};

static_assert(TypeMatch<decltype(DXGI_ADAPTER_DESC1::Description), WCHAR[128]>::value);
static_assert(TypeMatch<decltype(DXGI_ADAPTER_DESC1::VendorId), UINT>::value);
static_assert(TypeMatch<decltype(DXGI_ADAPTER_DESC1::DeviceId), UINT>::value);
static_assert(TypeMatch<decltype(DXGI_ADAPTER_DESC1::SubSysId), UINT>::value);
static_assert(TypeMatch<decltype(DXGI_ADAPTER_DESC1::Revision), UINT>::value);
static_assert(TypeMatch<decltype(DXGI_ADAPTER_DESC1::DedicatedVideoMemory), SIZE_T>::value);
static_assert(TypeMatch<decltype(DXGI_ADAPTER_DESC1::DedicatedSystemMemory), SIZE_T>::value);
static_assert(TypeMatch<decltype(DXGI_ADAPTER_DESC1::SharedSystemMemory), SIZE_T>::value);
static_assert(TypeMatch<decltype(DXGI_ADAPTER_DESC1::AdapterLuid), LUID>::value);
static_assert(TypeMatch<decltype(DXGI_ADAPTER_DESC1::Flags), UINT>::value);

static_assert(offsetof(DXGI_ADAPTER_DESC1, Description) == 0);
static_assert(offsetof(DXGI_ADAPTER_DESC1, VendorId) == 0x100);
static_assert(offsetof(DXGI_ADAPTER_DESC1, DeviceId) == 0x104);
static_assert(offsetof(DXGI_ADAPTER_DESC1, SubSysId) == 0x108);
static_assert(offsetof(DXGI_ADAPTER_DESC1, Revision) == 0x10C);
static_assert(offsetof(DXGI_ADAPTER_DESC1, DedicatedVideoMemory) == 0x110);
static_assert(offsetof(DXGI_ADAPTER_DESC1, DedicatedSystemMemory) == 0x118);
static_assert(offsetof(DXGI_ADAPTER_DESC1, SharedSystemMemory) == 0x120);
static_assert(offsetof(DXGI_ADAPTER_DESC1, AdapterLuid) == 0x128);
static_assert(offsetof(DXGI_ADAPTER_DESC1, Flags) == 0x130);

static_assert(sizeof(DXGI_ADAPTER_DESC1) == 312);

// DXGI_RGBA

typedef D3DCOLORVALUE DXGI_RGBA;

static_assert(TypeMatch<DXGI_RGBA, D3DCOLORVALUE>::value);

static_assert(sizeof(DXGI_RGBA) == 16);

#pragma pack(pop)

// IDXGIObject

struct __declspec(novtable) IDXGIObject : IUnknown
{
	virtual HRESULT SetPrivateData
	(
		const GUID& Name,
		UINT DataSize,
		const void* pData
	) = 0;
	virtual HRESULT SetPrivateDataInterface
	(
		const GUID& Name,
		const IUnknown* pUnknown
	) = 0;
	virtual HRESULT GetPrivateData
	(
		const GUID& Name,
		UINT* pDataSize,
		void* pData
	) = 0;
	virtual HRESULT GetParent
	(
		const IID& riid,
		void** ppParent
	) = 0;
};

static_assert(sizeof(IDXGIObject) == 8);

// IDXGIDeviceSubObject

struct __declspec(novtable) IDXGIDeviceSubObject : IDXGIObject
{
	virtual HRESULT GetDevice
	(
		const IID& riid,
		void** ppDevice
	) = 0;
};

static_assert(sizeof(IDXGIDeviceSubObject) == 8);

// IDXGIResource

struct __declspec(novtable) IDXGIResource : IDXGIDeviceSubObject
{
	virtual HRESULT GetSharedHandle(HANDLE* pSharedHandle) = 0;
	virtual HRESULT GetUsage(DXGI_USAGE* pUsage) = 0;
	virtual HRESULT SetEvictionPriority(UINT EvictionPriority) = 0;
	virtual HRESULT GetEvictionPriority(UINT* pEvictionPriority) = 0;
};

static_assert(sizeof(IDXGIResource) == 8);

// IDXGIKeyedMutex

struct __declspec(novtable) IDXGIKeyedMutex : IDXGIDeviceSubObject
{
	virtual HRESULT AcquireSync
	(
		UINT64 Key,
		DWORD dwMilliseconds
	) = 0;
	virtual HRESULT ReleaseSync(UINT64 Key) = 0;
};

static_assert(sizeof(IDXGIKeyedMutex) == 8);

// IDXGISurface

struct __declspec(novtable) IDXGISurface : IDXGIDeviceSubObject
{
	virtual HRESULT GetDesc(DXGI_SURFACE_DESC* pDesc) = 0;
	virtual HRESULT Map
	(
		DXGI_MAPPED_RECT* pLockedRect,
		UINT MapFlags
	) = 0;
	virtual HRESULT Unmap() = 0;
};

static_assert(sizeof(IDXGISurface) == 8);

// IDXGISurface1

struct __declspec(novtable) IDXGISurface1 : IDXGISurface
{
	virtual HRESULT GetDC
	(
		BOOL Discard,
		HDC* phdc
	) = 0;
	virtual HRESULT ReleaseDC(RECT* pDirtyRect) = 0;
};

static_assert(sizeof(IDXGISurface1) == 8);

// IDXGIAdapter

struct __declspec(novtable) IDXGIAdapter : IDXGIObject
{
	virtual HRESULT EnumOutputs
	(
		UINT Output,
		IDXGIOutput** ppOutput
	) = 0;
	virtual HRESULT GetDesc(DXGI_ADAPTER_DESC* pDesc) = 0;
	virtual HRESULT CheckInterfaceSupport
	(
		const GUID& InterfaceName,
		LARGE_INTEGER* pUMDVersion
	) = 0;
};

static_assert(sizeof(IDXGIAdapter) == 8);

// IDXGIOutput

struct __declspec(novtable) IDXGIOutput : IDXGIObject
{
	virtual HRESULT GetDesc(DXGI_OUTPUT_DESC* pDesc) = 0;
	virtual HRESULT GetDisplayModeList
	(
		DXGI_FORMAT EnumFormat,
		UINT Flags,
		UINT* pNumModes,
		DXGI_MODE_DESC* pDesc
	) = 0;
	virtual HRESULT FindClosestMatchingMode
	(
		const DXGI_MODE_DESC* pModeToMatch,
		DXGI_MODE_DESC* pClosestMatch,
		IUnknown* pConcernedDevice
	) = 0;
	virtual HRESULT WaitForVBlank() = 0;
	virtual HRESULT TakeOwnership
	(
		IUnknown* pDevice,
		BOOL Exclusive
	) = 0;
	virtual void ReleaseOwnership() = 0;
	virtual HRESULT GetGammaControlCapabilities(DXGI_GAMMA_CONTROL_CAPABILITIES* pGammaCaps) = 0;
	virtual HRESULT SetGammaControl(const DXGI_GAMMA_CONTROL* pArray) = 0;
	virtual HRESULT GetGammaControl(DXGI_GAMMA_CONTROL* pArray) = 0;
	virtual HRESULT SetDisplaySurface(IDXGISurface* pScanoutSurface) = 0;
	virtual HRESULT GetDisplaySurfaceData(IDXGISurface* pDestination) = 0;
	virtual HRESULT GetFrameStatistics(DXGI_FRAME_STATISTICS* pStats) = 0;
};

static_assert(sizeof(IDXGIOutput) == 8);

// IDXGISwapChain

struct __declspec(novtable) IDXGISwapChain : IDXGIDeviceSubObject
{
	virtual HRESULT Present
	(
		UINT SyncInterval,
		UINT Flags
	) = 0;
	virtual HRESULT GetBuffer
	(
		UINT Buffer,
		const IID& riid,
		void** ppSurface
	) = 0;
	virtual HRESULT SetFullscreenState
	(
		BOOL Fullscreen,
		IDXGIOutput* pTarget
	) = 0;
	virtual HRESULT GetFullscreenState
	(
		BOOL* pFullscreen,
		IDXGIOutput** ppTarget
	) = 0;
	virtual HRESULT GetDesc(DXGI_SWAP_CHAIN_DESC* pDesc) = 0;
	virtual HRESULT ResizeBuffers
	(
		UINT BufferCount,
		UINT Width,
		UINT Height,
		DXGI_FORMAT NewFormat,
		UINT SwapChainFlags
	) = 0;
	virtual HRESULT ResizeTarget(const DXGI_MODE_DESC* pNewTargetParameters) = 0;
	virtual HRESULT GetContainingOutput(IDXGIOutput** ppOutput) = 0;
	virtual HRESULT GetFrameStatistics(DXGI_FRAME_STATISTICS* pStats) = 0;
	virtual HRESULT GetLastPresentCount(UINT* pLastPresentCount) = 0;
};

static_assert(sizeof(IDXGISwapChain) == 8);

// IDXGIFactory

struct __declspec(novtable) IDXGIFactory : IDXGIObject
{
	virtual HRESULT EnumAdapters
	(
		UINT Adapter,
		IDXGIAdapter** ppAdapter
	) = 0;
	virtual HRESULT MakeWindowAssociation
	(
		HWND WindowHandle,
		UINT Flags
	) = 0;
	virtual HRESULT GetWindowAssociation(HWND* pWindowHandle) = 0;
	virtual HRESULT CreateSwapChain
	(
		IUnknown* pDevice,
		DXGI_SWAP_CHAIN_DESC* pDesc,
		IDXGISwapChain** ppSwapChain
	) = 0;
	virtual HRESULT CreateSoftwareAdapter
	(
		HMODULE Module,
		IDXGIAdapter** ppAdapter
	) = 0;
};

static_assert(sizeof(IDXGIFactory) == 8);

// IDXGIDevice

struct __declspec(novtable) IDXGIDevice : IDXGIObject
{
	virtual HRESULT GetAdapter(IDXGIAdapter** pAdapter) = 0;
	virtual HRESULT CreateSurface
	(
		const DXGI_SURFACE_DESC* pDesc,
		UINT NumSurfaces,
		DXGI_USAGE Usage,
		const DXGI_SHARED_RESOURCE* pSharedResource,
		IDXGISurface** ppSurface
	) = 0;
	virtual HRESULT QueryResourceResidency
	(
		IUnknown*const* ppResources,
		DXGI_RESIDENCY* pResidencyStatus,
		UINT NumResources
	) = 0;
	virtual HRESULT SetGPUThreadPriority(INT Priority) = 0;
	virtual HRESULT GetGPUThreadPriority(INT* pPriority) = 0;
};

static_assert(sizeof(IDXGIDevice) == 8);

// IDXGIFactory1

struct __declspec(novtable) IDXGIFactory1 : IDXGIFactory
{
	virtual HRESULT EnumAdapters1
	(
		UINT Adapter,
		IDXGIAdapter1** ppAdapter
	) = 0;
	virtual BOOL IsCurrent() = 0;
};

static_assert(sizeof(IDXGIFactory1) == 8);

// IDXGIAdapter1

struct __declspec(novtable) IDXGIAdapter1 : IDXGIAdapter
{
	virtual HRESULT GetDesc1(DXGI_ADAPTER_DESC1* pDesc) = 0;
};

static_assert(sizeof(IDXGIAdapter1) == 8);

// IDXGIDevice1

struct __declspec(novtable) IDXGIDevice1 : IDXGIDevice
{
	virtual HRESULT SetMaximumFrameLatency(UINT MaxLatency) = 0;
	virtual HRESULT GetMaximumFrameLatency(UINT* pMaxLatency) = 0;
};

static_assert(sizeof(IDXGIDevice1) == 8);

#pragma endregion

#else

#pragma region x86_32

struct IDXGIObject;
struct IDXGIDeviceSubObject;
struct IDXGIResource;
struct IDXGIKeyedMutex;
struct IDXGISurface;
struct IDXGISurface1;
struct IDXGIAdapter;
struct IDXGIOutput;
struct IDXGISwapChain;
struct IDXGIFactory;
struct IDXGIDevice;
struct IDXGIFactory1;
struct IDXGIAdapter1;
struct IDXGIDevice1;

extern "C" const IID IID_IDXGIObject;
extern "C" const IID IID_IDXGIDeviceSubObject;
extern "C" const IID IID_IDXGIResource;
extern "C" const IID IID_IDXGIKeyedMutex;
extern "C" const IID IID_IDXGISurface;
extern "C" const IID IID_IDXGISurface1;
extern "C" const IID IID_IDXGIAdapter;
extern "C" const IID IID_IDXGIOutput;
extern "C" const IID IID_IDXGISwapChain;
extern "C" const IID IID_IDXGIFactory;
extern "C" const IID IID_IDXGIDevice;
extern "C" const IID IID_IDXGIFactory1;
extern "C" const IID IID_IDXGIAdapter1;
extern "C" const IID IID_IDXGIDevice1;

// DXGI_USAGE

typedef UINT DXGI_USAGE;

static_assert(TypeMatch<DXGI_USAGE, UINT>::value);

static_assert(sizeof(DXGI_USAGE) == 4);

// DXGI_FORMAT

enum DXGI_FORMAT
{
	DXGI_FORMAT_UNKNOWN=0,
	DXGI_FORMAT_R32G32B32A32_TYPELESS=1,
	DXGI_FORMAT_R32G32B32A32_FLOAT=2,
	DXGI_FORMAT_R32G32B32A32_UINT=3,
	DXGI_FORMAT_R32G32B32A32_SINT=4,
	DXGI_FORMAT_R32G32B32_TYPELESS=5,
	DXGI_FORMAT_R32G32B32_FLOAT=6,
	DXGI_FORMAT_R32G32B32_UINT=7,
	DXGI_FORMAT_R32G32B32_SINT=8,
	DXGI_FORMAT_R16G16B16A16_TYPELESS=9,
	DXGI_FORMAT_R16G16B16A16_FLOAT=10,
	DXGI_FORMAT_R16G16B16A16_UNORM=11,
	DXGI_FORMAT_R16G16B16A16_UINT=12,
	DXGI_FORMAT_R16G16B16A16_SNORM=13,
	DXGI_FORMAT_R16G16B16A16_SINT=14,
	DXGI_FORMAT_R32G32_TYPELESS=15,
	DXGI_FORMAT_R32G32_FLOAT=16,
	DXGI_FORMAT_R32G32_UINT=17,
	DXGI_FORMAT_R32G32_SINT=18,
	DXGI_FORMAT_R32G8X24_TYPELESS=19,
	DXGI_FORMAT_D32_FLOAT_S8X24_UINT=20,
	DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS=21,
	DXGI_FORMAT_X32_TYPELESS_G8X24_UINT=22,
	DXGI_FORMAT_R10G10B10A2_TYPELESS=23,
	DXGI_FORMAT_R10G10B10A2_UNORM=24,
	DXGI_FORMAT_R10G10B10A2_UINT=25,
	DXGI_FORMAT_R11G11B10_FLOAT=26,
	DXGI_FORMAT_R8G8B8A8_TYPELESS=27,
	DXGI_FORMAT_R8G8B8A8_UNORM=28,
	DXGI_FORMAT_R8G8B8A8_UNORM_SRGB=29,
	DXGI_FORMAT_R8G8B8A8_UINT=30,
	DXGI_FORMAT_R8G8B8A8_SNORM=31,
	DXGI_FORMAT_R8G8B8A8_SINT=32,
	DXGI_FORMAT_R16G16_TYPELESS=33,
	DXGI_FORMAT_R16G16_FLOAT=34,
	DXGI_FORMAT_R16G16_UNORM=35,
	DXGI_FORMAT_R16G16_UINT=36,
	DXGI_FORMAT_R16G16_SNORM=37,
	DXGI_FORMAT_R16G16_SINT=38,
	DXGI_FORMAT_R32_TYPELESS=39,
	DXGI_FORMAT_D32_FLOAT=40,
	DXGI_FORMAT_R32_FLOAT=41,
	DXGI_FORMAT_R32_UINT=42,
	DXGI_FORMAT_R32_SINT=43,
	DXGI_FORMAT_R24G8_TYPELESS=44,
	DXGI_FORMAT_D24_UNORM_S8_UINT=45,
	DXGI_FORMAT_R24_UNORM_X8_TYPELESS=46,
	DXGI_FORMAT_X24_TYPELESS_G8_UINT=47,
	DXGI_FORMAT_R8G8_TYPELESS=48,
	DXGI_FORMAT_R8G8_UNORM=49,
	DXGI_FORMAT_R8G8_UINT=50,
	DXGI_FORMAT_R8G8_SNORM=51,
	DXGI_FORMAT_R8G8_SINT=52,
	DXGI_FORMAT_R16_TYPELESS=53,
	DXGI_FORMAT_R16_FLOAT=54,
	DXGI_FORMAT_D16_UNORM=55,
	DXGI_FORMAT_R16_UNORM=56,
	DXGI_FORMAT_R16_UINT=57,
	DXGI_FORMAT_R16_SNORM=58,
	DXGI_FORMAT_R16_SINT=59,
	DXGI_FORMAT_R8_TYPELESS=60,
	DXGI_FORMAT_R8_UNORM=61,
	DXGI_FORMAT_R8_UINT=62,
	DXGI_FORMAT_R8_SNORM=63,
	DXGI_FORMAT_R8_SINT=64,
	DXGI_FORMAT_A8_UNORM=65,
	DXGI_FORMAT_R1_UNORM=66,
	DXGI_FORMAT_R9G9B9E5_SHAREDEXP=67,
	DXGI_FORMAT_R8G8_B8G8_UNORM=68,
	DXGI_FORMAT_G8R8_G8B8_UNORM=69,
	DXGI_FORMAT_BC1_TYPELESS=70,
	DXGI_FORMAT_BC1_UNORM=71,
	DXGI_FORMAT_BC1_UNORM_SRGB=72,
	DXGI_FORMAT_BC2_TYPELESS=73,
	DXGI_FORMAT_BC2_UNORM=74,
	DXGI_FORMAT_BC2_UNORM_SRGB=75,
	DXGI_FORMAT_BC3_TYPELESS=76,
	DXGI_FORMAT_BC3_UNORM=77,
	DXGI_FORMAT_BC3_UNORM_SRGB=78,
	DXGI_FORMAT_BC4_TYPELESS=79,
	DXGI_FORMAT_BC4_UNORM=80,
	DXGI_FORMAT_BC4_SNORM=81,
	DXGI_FORMAT_BC5_TYPELESS=82,
	DXGI_FORMAT_BC5_UNORM=83,
	DXGI_FORMAT_BC5_SNORM=84,
	DXGI_FORMAT_B5G6R5_UNORM=85,
	DXGI_FORMAT_B5G5R5A1_UNORM=86,
	DXGI_FORMAT_B8G8R8A8_UNORM=87,
	DXGI_FORMAT_B8G8R8X8_UNORM=88,
	DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM=89,
	DXGI_FORMAT_B8G8R8A8_TYPELESS=90,
	DXGI_FORMAT_B8G8R8A8_UNORM_SRGB=91,
	DXGI_FORMAT_B8G8R8X8_TYPELESS=92,
	DXGI_FORMAT_B8G8R8X8_UNORM_SRGB=93,
	DXGI_FORMAT_BC6H_TYPELESS=94,
	DXGI_FORMAT_BC6H_UF16=95,
	DXGI_FORMAT_BC6H_SF16=96,
	DXGI_FORMAT_BC7_TYPELESS=97,
	DXGI_FORMAT_BC7_UNORM=98,
	DXGI_FORMAT_BC7_UNORM_SRGB=99,
	DXGI_FORMAT_AYUV=100,
	DXGI_FORMAT_Y410=101,
	DXGI_FORMAT_Y416=102,
	DXGI_FORMAT_NV12=103,
	DXGI_FORMAT_P010=104,
	DXGI_FORMAT_P016=105,
	DXGI_FORMAT_420_OPAQUE=106,
	DXGI_FORMAT_YUY2=107,
	DXGI_FORMAT_Y210=108,
	DXGI_FORMAT_Y216=109,
	DXGI_FORMAT_NV11=110,
	DXGI_FORMAT_AI44=111,
	DXGI_FORMAT_IA44=112,
	DXGI_FORMAT_P8=113,
	DXGI_FORMAT_A8P8=114,
	DXGI_FORMAT_B4G4R4A4_UNORM=115,
	DXGI_FORMAT_P208=130,
	DXGI_FORMAT_V208=131,
	DXGI_FORMAT_V408=132,
	DXGI_FORMAT_FORCE_UINT=0xffffffff,
};

// DXGI_MODE_SCANLINE_ORDER

enum DXGI_MODE_SCANLINE_ORDER
{
	DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED=0,
	DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE=1,
	DXGI_MODE_SCANLINE_ORDER_UPPER_FIELD_FIRST=2,
	DXGI_MODE_SCANLINE_ORDER_LOWER_FIELD_FIRST=3,
};

// DXGI_MODE_SCALING

enum DXGI_MODE_SCALING
{
	DXGI_MODE_SCALING_UNSPECIFIED=0,
	DXGI_MODE_SCALING_CENTERED=1,
	DXGI_MODE_SCALING_STRETCHED=2,
};

// DXGI_MODE_ROTATION

enum DXGI_MODE_ROTATION
{
	DXGI_MODE_ROTATION_UNSPECIFIED=0,
	DXGI_MODE_ROTATION_IDENTITY=1,
	DXGI_MODE_ROTATION_ROTATE90=2,
	DXGI_MODE_ROTATION_ROTATE180=3,
	DXGI_MODE_ROTATION_ROTATE270=4,
};

// DXGI_SWAP_EFFECT

enum DXGI_SWAP_EFFECT
{
	DXGI_SWAP_EFFECT_DISCARD=0,
	DXGI_SWAP_EFFECT_SEQUENTIAL=1,
	DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL=3,
	DXGI_SWAP_EFFECT_FLIP_DISCARD=4,
};

// DXGI_RESIDENCY

enum DXGI_RESIDENCY
{
	DXGI_RESIDENCY_FULLY_RESIDENT=1,
	DXGI_RESIDENCY_RESIDENT_IN_SHARED_MEMORY=2,
	DXGI_RESIDENCY_EVICTED_TO_DISK=3,
};

#pragma pack(push, 1)

// DXGI_RATIONAL

struct DXGI_RATIONAL
{
	UINT Numerator; // 0
	UINT Denominator; // 4
};

static_assert(TypeMatch<decltype(DXGI_RATIONAL::Numerator), UINT>::value);
static_assert(TypeMatch<decltype(DXGI_RATIONAL::Denominator), UINT>::value);

static_assert(offsetof(DXGI_RATIONAL, Numerator) == 0);
static_assert(offsetof(DXGI_RATIONAL, Denominator) == 4);

static_assert(sizeof(DXGI_RATIONAL) == 8);

// DXGI_SAMPLE_DESC

struct DXGI_SAMPLE_DESC
{
	UINT Count; // 0
	UINT Quality; // 4
};

static_assert(TypeMatch<decltype(DXGI_SAMPLE_DESC::Count), UINT>::value);
static_assert(TypeMatch<decltype(DXGI_SAMPLE_DESC::Quality), UINT>::value);

static_assert(offsetof(DXGI_SAMPLE_DESC, Count) == 0);
static_assert(offsetof(DXGI_SAMPLE_DESC, Quality) == 4);

static_assert(sizeof(DXGI_SAMPLE_DESC) == 8);

// DXGI_MODE_DESC

struct DXGI_MODE_DESC
{
	UINT Width; // 0
	UINT Height; // 4
	DXGI_RATIONAL RefreshRate; // 8
	DXGI_FORMAT Format; // 0x10
	DXGI_MODE_SCANLINE_ORDER ScanlineOrdering; // 0x14
	DXGI_MODE_SCALING Scaling; // 0x18
};

static_assert(TypeMatch<decltype(DXGI_MODE_DESC::Width), UINT>::value);
static_assert(TypeMatch<decltype(DXGI_MODE_DESC::Height), UINT>::value);
static_assert(TypeMatch<decltype(DXGI_MODE_DESC::RefreshRate), DXGI_RATIONAL>::value);
static_assert(TypeMatch<decltype(DXGI_MODE_DESC::Format), DXGI_FORMAT>::value);
static_assert(TypeMatch<decltype(DXGI_MODE_DESC::ScanlineOrdering), DXGI_MODE_SCANLINE_ORDER>::value);
static_assert(TypeMatch<decltype(DXGI_MODE_DESC::Scaling), DXGI_MODE_SCALING>::value);

static_assert(offsetof(DXGI_MODE_DESC, Width) == 0);
static_assert(offsetof(DXGI_MODE_DESC, Height) == 4);
static_assert(offsetof(DXGI_MODE_DESC, RefreshRate) == 8);
static_assert(offsetof(DXGI_MODE_DESC, Format) == 0x10);
static_assert(offsetof(DXGI_MODE_DESC, ScanlineOrdering) == 0x14);
static_assert(offsetof(DXGI_MODE_DESC, Scaling) == 0x18);

static_assert(sizeof(DXGI_MODE_DESC) == 28);

// DXGI_SURFACE_DESC

struct DXGI_SURFACE_DESC
{
	UINT Width; // 0
	UINT Height; // 4
	DXGI_FORMAT Format; // 8
	DXGI_SAMPLE_DESC SampleDesc; // 0xC
};

static_assert(TypeMatch<decltype(DXGI_SURFACE_DESC::Width), UINT>::value);
static_assert(TypeMatch<decltype(DXGI_SURFACE_DESC::Height), UINT>::value);
static_assert(TypeMatch<decltype(DXGI_SURFACE_DESC::Format), DXGI_FORMAT>::value);
static_assert(TypeMatch<decltype(DXGI_SURFACE_DESC::SampleDesc), DXGI_SAMPLE_DESC>::value);

static_assert(offsetof(DXGI_SURFACE_DESC, Width) == 0);
static_assert(offsetof(DXGI_SURFACE_DESC, Height) == 4);
static_assert(offsetof(DXGI_SURFACE_DESC, Format) == 8);
static_assert(offsetof(DXGI_SURFACE_DESC, SampleDesc) == 0xC);

static_assert(sizeof(DXGI_SURFACE_DESC) == 20);

// DXGI_MAPPED_RECT

struct DXGI_MAPPED_RECT
{
	INT Pitch; // 0
	BYTE* pBits; // 4
};

static_assert(TypeMatch<decltype(DXGI_MAPPED_RECT::Pitch), INT>::value);
static_assert(TypeMatch<decltype(DXGI_MAPPED_RECT::pBits), BYTE*>::value);

static_assert(offsetof(DXGI_MAPPED_RECT, Pitch) == 0);
static_assert(offsetof(DXGI_MAPPED_RECT, pBits) == 4);

static_assert(sizeof(DXGI_MAPPED_RECT) == 8);

// DXGI_ADAPTER_DESC

struct DXGI_ADAPTER_DESC
{
	WCHAR Description[128]; // 0
	UINT VendorId; // 0x100
	UINT DeviceId; // 0x104
	UINT SubSysId; // 0x108
	UINT Revision; // 0x10C
	SIZE_T DedicatedVideoMemory; // 0x110
	SIZE_T DedicatedSystemMemory; // 0x114
	SIZE_T SharedSystemMemory; // 0x118
	LUID AdapterLuid; // 0x11C
};

static_assert(TypeMatch<decltype(DXGI_ADAPTER_DESC::Description), WCHAR[128]>::value);
static_assert(TypeMatch<decltype(DXGI_ADAPTER_DESC::VendorId), UINT>::value);
static_assert(TypeMatch<decltype(DXGI_ADAPTER_DESC::DeviceId), UINT>::value);
static_assert(TypeMatch<decltype(DXGI_ADAPTER_DESC::SubSysId), UINT>::value);
static_assert(TypeMatch<decltype(DXGI_ADAPTER_DESC::Revision), UINT>::value);
static_assert(TypeMatch<decltype(DXGI_ADAPTER_DESC::DedicatedVideoMemory), SIZE_T>::value);
static_assert(TypeMatch<decltype(DXGI_ADAPTER_DESC::DedicatedSystemMemory), SIZE_T>::value);
static_assert(TypeMatch<decltype(DXGI_ADAPTER_DESC::SharedSystemMemory), SIZE_T>::value);
static_assert(TypeMatch<decltype(DXGI_ADAPTER_DESC::AdapterLuid), LUID>::value);

static_assert(offsetof(DXGI_ADAPTER_DESC, Description) == 0);
static_assert(offsetof(DXGI_ADAPTER_DESC, VendorId) == 0x100);
static_assert(offsetof(DXGI_ADAPTER_DESC, DeviceId) == 0x104);
static_assert(offsetof(DXGI_ADAPTER_DESC, SubSysId) == 0x108);
static_assert(offsetof(DXGI_ADAPTER_DESC, Revision) == 0x10C);
static_assert(offsetof(DXGI_ADAPTER_DESC, DedicatedVideoMemory) == 0x110);
static_assert(offsetof(DXGI_ADAPTER_DESC, DedicatedSystemMemory) == 0x114);
static_assert(offsetof(DXGI_ADAPTER_DESC, SharedSystemMemory) == 0x118);
static_assert(offsetof(DXGI_ADAPTER_DESC, AdapterLuid) == 0x11C);

static_assert(sizeof(DXGI_ADAPTER_DESC) == 292);

// DXGI_SWAP_CHAIN_DESC

struct DXGI_SWAP_CHAIN_DESC
{
	DXGI_MODE_DESC BufferDesc; // 0
	DXGI_SAMPLE_DESC SampleDesc; // 0x1C
	DXGI_USAGE BufferUsage; // 0x24
	UINT BufferCount; // 0x28
	HWND OutputWindow; // 0x2C
	BOOL Windowed; // 0x30
	DXGI_SWAP_EFFECT SwapEffect; // 0x34
	UINT Flags; // 0x38
};

static_assert(TypeMatch<decltype(DXGI_SWAP_CHAIN_DESC::BufferDesc), DXGI_MODE_DESC>::value);
static_assert(TypeMatch<decltype(DXGI_SWAP_CHAIN_DESC::SampleDesc), DXGI_SAMPLE_DESC>::value);
static_assert(TypeMatch<decltype(DXGI_SWAP_CHAIN_DESC::BufferUsage), DXGI_USAGE>::value);
static_assert(TypeMatch<decltype(DXGI_SWAP_CHAIN_DESC::BufferCount), UINT>::value);
static_assert(TypeMatch<decltype(DXGI_SWAP_CHAIN_DESC::OutputWindow), HWND>::value);
static_assert(TypeMatch<decltype(DXGI_SWAP_CHAIN_DESC::Windowed), BOOL>::value);
static_assert(TypeMatch<decltype(DXGI_SWAP_CHAIN_DESC::SwapEffect), DXGI_SWAP_EFFECT>::value);
static_assert(TypeMatch<decltype(DXGI_SWAP_CHAIN_DESC::Flags), UINT>::value);

static_assert(offsetof(DXGI_SWAP_CHAIN_DESC, BufferDesc) == 0);
static_assert(offsetof(DXGI_SWAP_CHAIN_DESC, SampleDesc) == 0x1C);
static_assert(offsetof(DXGI_SWAP_CHAIN_DESC, BufferUsage) == 0x24);
static_assert(offsetof(DXGI_SWAP_CHAIN_DESC, BufferCount) == 0x28);
static_assert(offsetof(DXGI_SWAP_CHAIN_DESC, OutputWindow) == 0x2C);
static_assert(offsetof(DXGI_SWAP_CHAIN_DESC, Windowed) == 0x30);
static_assert(offsetof(DXGI_SWAP_CHAIN_DESC, SwapEffect) == 0x34);
static_assert(offsetof(DXGI_SWAP_CHAIN_DESC, Flags) == 0x38);

static_assert(sizeof(DXGI_SWAP_CHAIN_DESC) == 60);

// DXGI_FRAME_STATISTICS

struct DXGI_FRAME_STATISTICS
{
	UINT PresentCount; // 0
	UINT PresentRefreshCount; // 4
	UINT SyncRefreshCount; // 8
	_(4);
	LARGE_INTEGER SyncQPCTime; // 0x10
	LARGE_INTEGER SyncGPUTime; // 0x18
};

static_assert(TypeMatch<decltype(DXGI_FRAME_STATISTICS::PresentCount), UINT>::value);
static_assert(TypeMatch<decltype(DXGI_FRAME_STATISTICS::PresentRefreshCount), UINT>::value);
static_assert(TypeMatch<decltype(DXGI_FRAME_STATISTICS::SyncRefreshCount), UINT>::value);
static_assert(TypeMatch<decltype(DXGI_FRAME_STATISTICS::SyncQPCTime), LARGE_INTEGER>::value);
static_assert(TypeMatch<decltype(DXGI_FRAME_STATISTICS::SyncGPUTime), LARGE_INTEGER>::value);

static_assert(offsetof(DXGI_FRAME_STATISTICS, PresentCount) == 0);
static_assert(offsetof(DXGI_FRAME_STATISTICS, PresentRefreshCount) == 4);
static_assert(offsetof(DXGI_FRAME_STATISTICS, SyncRefreshCount) == 8);
static_assert(offsetof(DXGI_FRAME_STATISTICS, SyncQPCTime) == 0x10);
static_assert(offsetof(DXGI_FRAME_STATISTICS, SyncGPUTime) == 0x18);

static_assert(sizeof(DXGI_FRAME_STATISTICS) == 32);

// DXGI_RGB

struct DXGI_RGB
{
	float Red; // 0
	float Green; // 4
	float Blue; // 8
};

static_assert(TypeMatch<decltype(DXGI_RGB::Red), float>::value);
static_assert(TypeMatch<decltype(DXGI_RGB::Green), float>::value);
static_assert(TypeMatch<decltype(DXGI_RGB::Blue), float>::value);

static_assert(offsetof(DXGI_RGB, Red) == 0);
static_assert(offsetof(DXGI_RGB, Green) == 4);
static_assert(offsetof(DXGI_RGB, Blue) == 8);

static_assert(sizeof(DXGI_RGB) == 12);

// D3DCOLORVALUE

struct D3DCOLORVALUE
{
	float r; // 0
	float g; // 4
	float b; // 8
	float a; // 0xC
};

static_assert(TypeMatch<decltype(D3DCOLORVALUE::r), float>::value);
static_assert(TypeMatch<decltype(D3DCOLORVALUE::g), float>::value);
static_assert(TypeMatch<decltype(D3DCOLORVALUE::b), float>::value);
static_assert(TypeMatch<decltype(D3DCOLORVALUE::a), float>::value);

static_assert(offsetof(D3DCOLORVALUE, r) == 0);
static_assert(offsetof(D3DCOLORVALUE, g) == 4);
static_assert(offsetof(D3DCOLORVALUE, b) == 8);
static_assert(offsetof(D3DCOLORVALUE, a) == 0xC);

static_assert(sizeof(D3DCOLORVALUE) == 16);

// DXGI_GAMMA_CONTROL

struct DXGI_GAMMA_CONTROL
{
	DXGI_RGB Scale; // 0
	DXGI_RGB Offset; // 0xC
	DXGI_RGB GammaCurve[1025]; // 0x18
};

static_assert(TypeMatch<decltype(DXGI_GAMMA_CONTROL::Scale), DXGI_RGB>::value);
static_assert(TypeMatch<decltype(DXGI_GAMMA_CONTROL::Offset), DXGI_RGB>::value);
static_assert(TypeMatch<decltype(DXGI_GAMMA_CONTROL::GammaCurve), DXGI_RGB[1025]>::value);

static_assert(offsetof(DXGI_GAMMA_CONTROL, Scale) == 0);
static_assert(offsetof(DXGI_GAMMA_CONTROL, Offset) == 0xC);
static_assert(offsetof(DXGI_GAMMA_CONTROL, GammaCurve) == 0x18);

static_assert(sizeof(DXGI_GAMMA_CONTROL) == 12324);

// DXGI_GAMMA_CONTROL_CAPABILITIES

struct DXGI_GAMMA_CONTROL_CAPABILITIES
{
	BOOL ScaleAndOffsetSupported; // 0
	float MaxConvertedValue; // 4
	float MinConvertedValue; // 8
	UINT NumGammaControlPoints; // 0xC
	float ControlPointPositions[1025]; // 0x10
};

static_assert(TypeMatch<decltype(DXGI_GAMMA_CONTROL_CAPABILITIES::ScaleAndOffsetSupported), BOOL>::value);
static_assert(TypeMatch<decltype(DXGI_GAMMA_CONTROL_CAPABILITIES::MaxConvertedValue), float>::value);
static_assert(TypeMatch<decltype(DXGI_GAMMA_CONTROL_CAPABILITIES::MinConvertedValue), float>::value);
static_assert(TypeMatch<decltype(DXGI_GAMMA_CONTROL_CAPABILITIES::NumGammaControlPoints), UINT>::value);
static_assert(TypeMatch<decltype(DXGI_GAMMA_CONTROL_CAPABILITIES::ControlPointPositions), float[1025]>::value);

static_assert(offsetof(DXGI_GAMMA_CONTROL_CAPABILITIES, ScaleAndOffsetSupported) == 0);
static_assert(offsetof(DXGI_GAMMA_CONTROL_CAPABILITIES, MaxConvertedValue) == 4);
static_assert(offsetof(DXGI_GAMMA_CONTROL_CAPABILITIES, MinConvertedValue) == 8);
static_assert(offsetof(DXGI_GAMMA_CONTROL_CAPABILITIES, NumGammaControlPoints) == 0xC);
static_assert(offsetof(DXGI_GAMMA_CONTROL_CAPABILITIES, ControlPointPositions) == 0x10);

static_assert(sizeof(DXGI_GAMMA_CONTROL_CAPABILITIES) == 4116);

// DXGI_OUTPUT_DESC

struct DXGI_OUTPUT_DESC
{
	WCHAR DeviceName[32]; // 0
	RECT DesktopCoordinates; // 0x40
	BOOL AttachedToDesktop; // 0x50
	DXGI_MODE_ROTATION Rotation; // 0x54
	HMONITOR Monitor; // 0x58
};

static_assert(TypeMatch<decltype(DXGI_OUTPUT_DESC::DeviceName), WCHAR[32]>::value);
static_assert(TypeMatch<decltype(DXGI_OUTPUT_DESC::DesktopCoordinates), RECT>::value);
static_assert(TypeMatch<decltype(DXGI_OUTPUT_DESC::AttachedToDesktop), BOOL>::value);
static_assert(TypeMatch<decltype(DXGI_OUTPUT_DESC::Rotation), DXGI_MODE_ROTATION>::value);
static_assert(TypeMatch<decltype(DXGI_OUTPUT_DESC::Monitor), HMONITOR>::value);

static_assert(offsetof(DXGI_OUTPUT_DESC, DeviceName) == 0);
static_assert(offsetof(DXGI_OUTPUT_DESC, DesktopCoordinates) == 0x40);
static_assert(offsetof(DXGI_OUTPUT_DESC, AttachedToDesktop) == 0x50);
static_assert(offsetof(DXGI_OUTPUT_DESC, Rotation) == 0x54);
static_assert(offsetof(DXGI_OUTPUT_DESC, Monitor) == 0x58);

static_assert(sizeof(DXGI_OUTPUT_DESC) == 92);

// DXGI_SHARED_RESOURCE

struct DXGI_SHARED_RESOURCE
{
	HANDLE Handle; // 0
};

static_assert(TypeMatch<decltype(DXGI_SHARED_RESOURCE::Handle), HANDLE>::value);

static_assert(offsetof(DXGI_SHARED_RESOURCE, Handle) == 0);

static_assert(sizeof(DXGI_SHARED_RESOURCE) == 4);

// DXGI_ADAPTER_DESC1

struct DXGI_ADAPTER_DESC1
{
	WCHAR Description[128]; // 0
	UINT VendorId; // 0x100
	UINT DeviceId; // 0x104
	UINT SubSysId; // 0x108
	UINT Revision; // 0x10C
	SIZE_T DedicatedVideoMemory; // 0x110
	SIZE_T DedicatedSystemMemory; // 0x114
	SIZE_T SharedSystemMemory; // 0x118
	LUID AdapterLuid; // 0x11C
	UINT Flags; // 0x124
};

static_assert(TypeMatch<decltype(DXGI_ADAPTER_DESC1::Description), WCHAR[128]>::value);
static_assert(TypeMatch<decltype(DXGI_ADAPTER_DESC1::VendorId), UINT>::value);
static_assert(TypeMatch<decltype(DXGI_ADAPTER_DESC1::DeviceId), UINT>::value);
static_assert(TypeMatch<decltype(DXGI_ADAPTER_DESC1::SubSysId), UINT>::value);
static_assert(TypeMatch<decltype(DXGI_ADAPTER_DESC1::Revision), UINT>::value);
static_assert(TypeMatch<decltype(DXGI_ADAPTER_DESC1::DedicatedVideoMemory), SIZE_T>::value);
static_assert(TypeMatch<decltype(DXGI_ADAPTER_DESC1::DedicatedSystemMemory), SIZE_T>::value);
static_assert(TypeMatch<decltype(DXGI_ADAPTER_DESC1::SharedSystemMemory), SIZE_T>::value);
static_assert(TypeMatch<decltype(DXGI_ADAPTER_DESC1::AdapterLuid), LUID>::value);
static_assert(TypeMatch<decltype(DXGI_ADAPTER_DESC1::Flags), UINT>::value);

static_assert(offsetof(DXGI_ADAPTER_DESC1, Description) == 0);
static_assert(offsetof(DXGI_ADAPTER_DESC1, VendorId) == 0x100);
static_assert(offsetof(DXGI_ADAPTER_DESC1, DeviceId) == 0x104);
static_assert(offsetof(DXGI_ADAPTER_DESC1, SubSysId) == 0x108);
static_assert(offsetof(DXGI_ADAPTER_DESC1, Revision) == 0x10C);
static_assert(offsetof(DXGI_ADAPTER_DESC1, DedicatedVideoMemory) == 0x110);
static_assert(offsetof(DXGI_ADAPTER_DESC1, DedicatedSystemMemory) == 0x114);
static_assert(offsetof(DXGI_ADAPTER_DESC1, SharedSystemMemory) == 0x118);
static_assert(offsetof(DXGI_ADAPTER_DESC1, AdapterLuid) == 0x11C);
static_assert(offsetof(DXGI_ADAPTER_DESC1, Flags) == 0x124);

static_assert(sizeof(DXGI_ADAPTER_DESC1) == 296);

// DXGI_RGBA

typedef D3DCOLORVALUE DXGI_RGBA;

static_assert(TypeMatch<DXGI_RGBA, D3DCOLORVALUE>::value);

static_assert(sizeof(DXGI_RGBA) == 16);

#pragma pack(pop)

// IDXGIObject

struct __declspec(novtable) IDXGIObject : IUnknown
{
	virtual HRESULT __stdcall SetPrivateData
	(
		const GUID& Name,
		UINT DataSize,
		const void* pData
	) = 0;
	virtual HRESULT __stdcall SetPrivateDataInterface
	(
		const GUID& Name,
		const IUnknown* pUnknown
	) = 0;
	virtual HRESULT __stdcall GetPrivateData
	(
		const GUID& Name,
		UINT* pDataSize,
		void* pData
	) = 0;
	virtual HRESULT __stdcall GetParent
	(
		const IID& riid,
		void** ppParent
	) = 0;
};

static_assert(sizeof(IDXGIObject) == 4);

// IDXGIDeviceSubObject

struct __declspec(novtable) IDXGIDeviceSubObject : IDXGIObject
{
	virtual HRESULT __stdcall GetDevice
	(
		const IID& riid,
		void** ppDevice
	) = 0;
};

static_assert(sizeof(IDXGIDeviceSubObject) == 4);

// IDXGIResource

struct __declspec(novtable) IDXGIResource : IDXGIDeviceSubObject
{
	virtual HRESULT __stdcall GetSharedHandle(HANDLE* pSharedHandle) = 0;
	virtual HRESULT __stdcall GetUsage(DXGI_USAGE* pUsage) = 0;
	virtual HRESULT __stdcall SetEvictionPriority(UINT EvictionPriority) = 0;
	virtual HRESULT __stdcall GetEvictionPriority(UINT* pEvictionPriority) = 0;
};

static_assert(sizeof(IDXGIResource) == 4);

// IDXGIKeyedMutex

struct __declspec(novtable) IDXGIKeyedMutex : IDXGIDeviceSubObject
{
	virtual HRESULT __stdcall AcquireSync
	(
		UINT64 Key,
		DWORD dwMilliseconds
	) = 0;
	virtual HRESULT __stdcall ReleaseSync(UINT64 Key) = 0;
};

static_assert(sizeof(IDXGIKeyedMutex) == 4);

// IDXGISurface

struct __declspec(novtable) IDXGISurface : IDXGIDeviceSubObject
{
	virtual HRESULT __stdcall GetDesc(DXGI_SURFACE_DESC* pDesc) = 0;
	virtual HRESULT __stdcall Map
	(
		DXGI_MAPPED_RECT* pLockedRect,
		UINT MapFlags
	) = 0;
	virtual HRESULT __stdcall Unmap() = 0;
};

static_assert(sizeof(IDXGISurface) == 4);

// IDXGISurface1

struct __declspec(novtable) IDXGISurface1 : IDXGISurface
{
	virtual HRESULT __stdcall GetDC
	(
		BOOL Discard,
		HDC* phdc
	) = 0;
	virtual HRESULT __stdcall ReleaseDC(RECT* pDirtyRect) = 0;
};

static_assert(sizeof(IDXGISurface1) == 4);

// IDXGIAdapter

struct __declspec(novtable) IDXGIAdapter : IDXGIObject
{
	virtual HRESULT __stdcall EnumOutputs
	(
		UINT Output,
		IDXGIOutput** ppOutput
	) = 0;
	virtual HRESULT __stdcall GetDesc(DXGI_ADAPTER_DESC* pDesc) = 0;
	virtual HRESULT __stdcall CheckInterfaceSupport
	(
		const GUID& InterfaceName,
		LARGE_INTEGER* pUMDVersion
	) = 0;
};

static_assert(sizeof(IDXGIAdapter) == 4);

// IDXGIOutput

struct __declspec(novtable) IDXGIOutput : IDXGIObject
{
	virtual HRESULT __stdcall GetDesc(DXGI_OUTPUT_DESC* pDesc) = 0;
	virtual HRESULT __stdcall GetDisplayModeList
	(
		DXGI_FORMAT EnumFormat,
		UINT Flags,
		UINT* pNumModes,
		DXGI_MODE_DESC* pDesc
	) = 0;
	virtual HRESULT __stdcall FindClosestMatchingMode
	(
		const DXGI_MODE_DESC* pModeToMatch,
		DXGI_MODE_DESC* pClosestMatch,
		IUnknown* pConcernedDevice
	) = 0;
	virtual HRESULT __stdcall WaitForVBlank() = 0;
	virtual HRESULT __stdcall TakeOwnership
	(
		IUnknown* pDevice,
		BOOL Exclusive
	) = 0;
	virtual void __stdcall ReleaseOwnership() = 0;
	virtual HRESULT __stdcall GetGammaControlCapabilities(DXGI_GAMMA_CONTROL_CAPABILITIES* pGammaCaps) = 0;
	virtual HRESULT __stdcall SetGammaControl(const DXGI_GAMMA_CONTROL* pArray) = 0;
	virtual HRESULT __stdcall GetGammaControl(DXGI_GAMMA_CONTROL* pArray) = 0;
	virtual HRESULT __stdcall SetDisplaySurface(IDXGISurface* pScanoutSurface) = 0;
	virtual HRESULT __stdcall GetDisplaySurfaceData(IDXGISurface* pDestination) = 0;
	virtual HRESULT __stdcall GetFrameStatistics(DXGI_FRAME_STATISTICS* pStats) = 0;
};

static_assert(sizeof(IDXGIOutput) == 4);

// IDXGISwapChain

struct __declspec(novtable) IDXGISwapChain : IDXGIDeviceSubObject
{
	virtual HRESULT __stdcall Present
	(
		UINT SyncInterval,
		UINT Flags
	) = 0;
	virtual HRESULT __stdcall GetBuffer
	(
		UINT Buffer,
		const IID& riid,
		void** ppSurface
	) = 0;
	virtual HRESULT __stdcall SetFullscreenState
	(
		BOOL Fullscreen,
		IDXGIOutput* pTarget
	) = 0;
	virtual HRESULT __stdcall GetFullscreenState
	(
		BOOL* pFullscreen,
		IDXGIOutput** ppTarget
	) = 0;
	virtual HRESULT __stdcall GetDesc(DXGI_SWAP_CHAIN_DESC* pDesc) = 0;
	virtual HRESULT __stdcall ResizeBuffers
	(
		UINT BufferCount,
		UINT Width,
		UINT Height,
		DXGI_FORMAT NewFormat,
		UINT SwapChainFlags
	) = 0;
	virtual HRESULT __stdcall ResizeTarget(const DXGI_MODE_DESC* pNewTargetParameters) = 0;
	virtual HRESULT __stdcall GetContainingOutput(IDXGIOutput** ppOutput) = 0;
	virtual HRESULT __stdcall GetFrameStatistics(DXGI_FRAME_STATISTICS* pStats) = 0;
	virtual HRESULT __stdcall GetLastPresentCount(UINT* pLastPresentCount) = 0;
};

static_assert(sizeof(IDXGISwapChain) == 4);

// IDXGIFactory

struct __declspec(novtable) IDXGIFactory : IDXGIObject
{
	virtual HRESULT __stdcall EnumAdapters
	(
		UINT Adapter,
		IDXGIAdapter** ppAdapter
	) = 0;
	virtual HRESULT __stdcall MakeWindowAssociation
	(
		HWND WindowHandle,
		UINT Flags
	) = 0;
	virtual HRESULT __stdcall GetWindowAssociation(HWND* pWindowHandle) = 0;
	virtual HRESULT __stdcall CreateSwapChain
	(
		IUnknown* pDevice,
		DXGI_SWAP_CHAIN_DESC* pDesc,
		IDXGISwapChain** ppSwapChain
	) = 0;
	virtual HRESULT __stdcall CreateSoftwareAdapter
	(
		HMODULE Module,
		IDXGIAdapter** ppAdapter
	) = 0;
};

static_assert(sizeof(IDXGIFactory) == 4);

// IDXGIDevice

struct __declspec(novtable) IDXGIDevice : IDXGIObject
{
	virtual HRESULT __stdcall GetAdapter(IDXGIAdapter** pAdapter) = 0;
	virtual HRESULT __stdcall CreateSurface
	(
		const DXGI_SURFACE_DESC* pDesc,
		UINT NumSurfaces,
		DXGI_USAGE Usage,
		const DXGI_SHARED_RESOURCE* pSharedResource,
		IDXGISurface** ppSurface
	) = 0;
	virtual HRESULT __stdcall QueryResourceResidency
	(
		IUnknown*const* ppResources,
		DXGI_RESIDENCY* pResidencyStatus,
		UINT NumResources
	) = 0;
	virtual HRESULT __stdcall SetGPUThreadPriority(INT Priority) = 0;
	virtual HRESULT __stdcall GetGPUThreadPriority(INT* pPriority) = 0;
};

static_assert(sizeof(IDXGIDevice) == 4);

// IDXGIFactory1

struct __declspec(novtable) IDXGIFactory1 : IDXGIFactory
{
	virtual HRESULT __stdcall EnumAdapters1
	(
		UINT Adapter,
		IDXGIAdapter1** ppAdapter
	) = 0;
	virtual BOOL __stdcall IsCurrent() = 0;
};

static_assert(sizeof(IDXGIFactory1) == 4);

// IDXGIAdapter1

struct __declspec(novtable) IDXGIAdapter1 : IDXGIAdapter
{
	virtual HRESULT __stdcall GetDesc1(DXGI_ADAPTER_DESC1* pDesc) = 0;
};

static_assert(sizeof(IDXGIAdapter1) == 4);

// IDXGIDevice1

struct __declspec(novtable) IDXGIDevice1 : IDXGIDevice
{
	virtual HRESULT __stdcall SetMaximumFrameLatency(UINT MaxLatency) = 0;
	virtual HRESULT __stdcall GetMaximumFrameLatency(UINT* pMaxLatency) = 0;
};

static_assert(sizeof(IDXGIDevice1) == 4);

#pragma endregion

#endif

namespaceEnd();
