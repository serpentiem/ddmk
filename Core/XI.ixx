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

export module XI;

import Windows;

using namespace Windows;

export namespaceStart(XI);

#ifdef _WIN64

#pragma region x86_64

enum
{
	XINPUT_GAMEPAD_DPAD_UP=0x0001,
	XINPUT_GAMEPAD_DPAD_DOWN=0x0002,
	XINPUT_GAMEPAD_DPAD_LEFT=0x0004,
	XINPUT_GAMEPAD_DPAD_RIGHT=0x0008,
	XINPUT_GAMEPAD_START=0x0010,
	XINPUT_GAMEPAD_BACK=0x0020,
	XINPUT_GAMEPAD_LEFT_THUMB=0x0040,
	XINPUT_GAMEPAD_RIGHT_THUMB=0x0080,
	XINPUT_GAMEPAD_LEFT_SHOULDER=0x0100,
	XINPUT_GAMEPAD_RIGHT_SHOULDER=0x0200,
	XINPUT_GAMEPAD_A=0x1000,
	XINPUT_GAMEPAD_B=0x2000,
	XINPUT_GAMEPAD_X=0x4000,
	XINPUT_GAMEPAD_Y=0x8000,
	XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE=7849,
	XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE=8689,
	XINPUT_GAMEPAD_TRIGGER_THRESHOLD=30,
};

#pragma pack(push, 1)

// XINPUT_GAMEPAD

struct XINPUT_GAMEPAD
{
	WORD wButtons; // 0
	BYTE bLeftTrigger; // 2
	BYTE bRightTrigger; // 3
	SHORT sThumbLX; // 4
	SHORT sThumbLY; // 6
	SHORT sThumbRX; // 8
	SHORT sThumbRY; // 0xA
};

static_assert(TypeMatch<decltype(XINPUT_GAMEPAD::wButtons), WORD>::value);
static_assert(TypeMatch<decltype(XINPUT_GAMEPAD::bLeftTrigger), BYTE>::value);
static_assert(TypeMatch<decltype(XINPUT_GAMEPAD::bRightTrigger), BYTE>::value);
static_assert(TypeMatch<decltype(XINPUT_GAMEPAD::sThumbLX), SHORT>::value);
static_assert(TypeMatch<decltype(XINPUT_GAMEPAD::sThumbLY), SHORT>::value);
static_assert(TypeMatch<decltype(XINPUT_GAMEPAD::sThumbRX), SHORT>::value);
static_assert(TypeMatch<decltype(XINPUT_GAMEPAD::sThumbRY), SHORT>::value);

static_assert(offsetof(XINPUT_GAMEPAD, wButtons) == 0);
static_assert(offsetof(XINPUT_GAMEPAD, bLeftTrigger) == 2);
static_assert(offsetof(XINPUT_GAMEPAD, bRightTrigger) == 3);
static_assert(offsetof(XINPUT_GAMEPAD, sThumbLX) == 4);
static_assert(offsetof(XINPUT_GAMEPAD, sThumbLY) == 6);
static_assert(offsetof(XINPUT_GAMEPAD, sThumbRX) == 8);
static_assert(offsetof(XINPUT_GAMEPAD, sThumbRY) == 0xA);

static_assert(sizeof(XINPUT_GAMEPAD) == 12);

typedef XINPUT_GAMEPAD * PXINPUT_GAMEPAD;

static_assert(TypeMatch<PXINPUT_GAMEPAD, XINPUT_GAMEPAD *>::value);

static_assert(sizeof(PXINPUT_GAMEPAD) == 8);

// XINPUT_STATE

struct XINPUT_STATE
{
	DWORD dwPacketNumber; // 0
	XINPUT_GAMEPAD Gamepad; // 4
};

static_assert(TypeMatch<decltype(XINPUT_STATE::dwPacketNumber), DWORD>::value);
static_assert(TypeMatch<decltype(XINPUT_STATE::Gamepad), XINPUT_GAMEPAD>::value);

static_assert(offsetof(XINPUT_STATE, dwPacketNumber) == 0);
static_assert(offsetof(XINPUT_STATE, Gamepad) == 4);

static_assert(sizeof(XINPUT_STATE) == 16);

typedef XINPUT_STATE * PXINPUT_STATE;

static_assert(TypeMatch<PXINPUT_STATE, XINPUT_STATE *>::value);

static_assert(sizeof(PXINPUT_STATE) == 8);

// XINPUT_VIBRATION

struct XINPUT_VIBRATION
{
	WORD wLeftMotorSpeed; // 0
	WORD wRightMotorSpeed; // 2
};

static_assert(TypeMatch<decltype(XINPUT_VIBRATION::wLeftMotorSpeed), WORD>::value);
static_assert(TypeMatch<decltype(XINPUT_VIBRATION::wRightMotorSpeed), WORD>::value);

static_assert(offsetof(XINPUT_VIBRATION, wLeftMotorSpeed) == 0);
static_assert(offsetof(XINPUT_VIBRATION, wRightMotorSpeed) == 2);

static_assert(sizeof(XINPUT_VIBRATION) == 4);

typedef XINPUT_VIBRATION * PXINPUT_VIBRATION;

static_assert(TypeMatch<PXINPUT_VIBRATION, XINPUT_VIBRATION *>::value);

static_assert(sizeof(PXINPUT_VIBRATION) == 8);

// XINPUT_CAPABILITIES

struct XINPUT_CAPABILITIES
{
	BYTE Type; // 0
	BYTE SubType; // 1
	WORD Flags; // 2
	XINPUT_GAMEPAD Gamepad; // 4
	XINPUT_VIBRATION Vibration; // 0x10
};

static_assert(TypeMatch<decltype(XINPUT_CAPABILITIES::Type), BYTE>::value);
static_assert(TypeMatch<decltype(XINPUT_CAPABILITIES::SubType), BYTE>::value);
static_assert(TypeMatch<decltype(XINPUT_CAPABILITIES::Flags), WORD>::value);
static_assert(TypeMatch<decltype(XINPUT_CAPABILITIES::Gamepad), XINPUT_GAMEPAD>::value);
static_assert(TypeMatch<decltype(XINPUT_CAPABILITIES::Vibration), XINPUT_VIBRATION>::value);

static_assert(offsetof(XINPUT_CAPABILITIES, Type) == 0);
static_assert(offsetof(XINPUT_CAPABILITIES, SubType) == 1);
static_assert(offsetof(XINPUT_CAPABILITIES, Flags) == 2);
static_assert(offsetof(XINPUT_CAPABILITIES, Gamepad) == 4);
static_assert(offsetof(XINPUT_CAPABILITIES, Vibration) == 0x10);

static_assert(sizeof(XINPUT_CAPABILITIES) == 20);

typedef XINPUT_CAPABILITIES * PXINPUT_CAPABILITIES;

static_assert(TypeMatch<PXINPUT_CAPABILITIES, XINPUT_CAPABILITIES *>::value);

static_assert(sizeof(PXINPUT_CAPABILITIES) == 8);

// XINPUT_BATTERY_INFORMATION

struct XINPUT_BATTERY_INFORMATION
{
	BYTE BatteryType; // 0
	BYTE BatteryLevel; // 1
};

static_assert(TypeMatch<decltype(XINPUT_BATTERY_INFORMATION::BatteryType), BYTE>::value);
static_assert(TypeMatch<decltype(XINPUT_BATTERY_INFORMATION::BatteryLevel), BYTE>::value);

static_assert(offsetof(XINPUT_BATTERY_INFORMATION, BatteryType) == 0);
static_assert(offsetof(XINPUT_BATTERY_INFORMATION, BatteryLevel) == 1);

static_assert(sizeof(XINPUT_BATTERY_INFORMATION) == 2);

typedef XINPUT_BATTERY_INFORMATION * PXINPUT_BATTERY_INFORMATION;

static_assert(TypeMatch<PXINPUT_BATTERY_INFORMATION, XINPUT_BATTERY_INFORMATION *>::value);

static_assert(sizeof(PXINPUT_BATTERY_INFORMATION) == 8);

// XINPUT_KEYSTROKE

struct XINPUT_KEYSTROKE
{
	WORD VirtualKey; // 0
	WCHAR Unicode; // 2
	WORD Flags; // 4
	BYTE UserIndex; // 6
	BYTE HidCode; // 7
};

static_assert(TypeMatch<decltype(XINPUT_KEYSTROKE::VirtualKey), WORD>::value);
static_assert(TypeMatch<decltype(XINPUT_KEYSTROKE::Unicode), WCHAR>::value);
static_assert(TypeMatch<decltype(XINPUT_KEYSTROKE::Flags), WORD>::value);
static_assert(TypeMatch<decltype(XINPUT_KEYSTROKE::UserIndex), BYTE>::value);
static_assert(TypeMatch<decltype(XINPUT_KEYSTROKE::HidCode), BYTE>::value);

static_assert(offsetof(XINPUT_KEYSTROKE, VirtualKey) == 0);
static_assert(offsetof(XINPUT_KEYSTROKE, Unicode) == 2);
static_assert(offsetof(XINPUT_KEYSTROKE, Flags) == 4);
static_assert(offsetof(XINPUT_KEYSTROKE, UserIndex) == 6);
static_assert(offsetof(XINPUT_KEYSTROKE, HidCode) == 7);

static_assert(sizeof(XINPUT_KEYSTROKE) == 8);

typedef XINPUT_KEYSTROKE * PXINPUT_KEYSTROKE;

static_assert(TypeMatch<PXINPUT_KEYSTROKE, XINPUT_KEYSTROKE *>::value);

static_assert(sizeof(PXINPUT_KEYSTROKE) == 8);

#pragma pack(pop)

extern "C" DWORD XInputGetState
(
	DWORD dwUserIndex,
	XINPUT_STATE* pState
);
extern "C" DWORD XInputSetState
(
	DWORD dwUserIndex,
	XINPUT_VIBRATION* pVibration
);
extern "C" DWORD XInputGetCapabilities
(
	DWORD dwUserIndex,
	DWORD dwFlags,
	XINPUT_CAPABILITIES* pCapabilities
);
extern "C" void XInputEnable(BOOL enable);
extern "C" DWORD XInputGetAudioDeviceIds
(
	DWORD dwUserIndex,
	LPWSTR pRenderDeviceId,
	UINT* pRenderCount,
	LPWSTR pCaptureDeviceId,
	UINT* pCaptureCount
);
extern "C" DWORD XInputGetBatteryInformation
(
	DWORD dwUserIndex,
	BYTE devType,
	XINPUT_BATTERY_INFORMATION* pBatteryInformation
);
extern "C" DWORD XInputGetKeystroke
(
	DWORD dwUserIndex,
	DWORD dwReserved,
	PXINPUT_KEYSTROKE pKeystroke
);
#pragma endregion

#else

#pragma region x86_32

enum
{
	XINPUT_GAMEPAD_DPAD_UP=0x0001,
	XINPUT_GAMEPAD_DPAD_DOWN=0x0002,
	XINPUT_GAMEPAD_DPAD_LEFT=0x0004,
	XINPUT_GAMEPAD_DPAD_RIGHT=0x0008,
	XINPUT_GAMEPAD_START=0x0010,
	XINPUT_GAMEPAD_BACK=0x0020,
	XINPUT_GAMEPAD_LEFT_THUMB=0x0040,
	XINPUT_GAMEPAD_RIGHT_THUMB=0x0080,
	XINPUT_GAMEPAD_LEFT_SHOULDER=0x0100,
	XINPUT_GAMEPAD_RIGHT_SHOULDER=0x0200,
	XINPUT_GAMEPAD_A=0x1000,
	XINPUT_GAMEPAD_B=0x2000,
	XINPUT_GAMEPAD_X=0x4000,
	XINPUT_GAMEPAD_Y=0x8000,
	XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE=7849,
	XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE=8689,
	XINPUT_GAMEPAD_TRIGGER_THRESHOLD=30,
};

#pragma pack(push, 1)

// XINPUT_GAMEPAD

struct XINPUT_GAMEPAD
{
	WORD wButtons; // 0
	BYTE bLeftTrigger; // 2
	BYTE bRightTrigger; // 3
	SHORT sThumbLX; // 4
	SHORT sThumbLY; // 6
	SHORT sThumbRX; // 8
	SHORT sThumbRY; // 0xA
};

static_assert(TypeMatch<decltype(XINPUT_GAMEPAD::wButtons), WORD>::value);
static_assert(TypeMatch<decltype(XINPUT_GAMEPAD::bLeftTrigger), BYTE>::value);
static_assert(TypeMatch<decltype(XINPUT_GAMEPAD::bRightTrigger), BYTE>::value);
static_assert(TypeMatch<decltype(XINPUT_GAMEPAD::sThumbLX), SHORT>::value);
static_assert(TypeMatch<decltype(XINPUT_GAMEPAD::sThumbLY), SHORT>::value);
static_assert(TypeMatch<decltype(XINPUT_GAMEPAD::sThumbRX), SHORT>::value);
static_assert(TypeMatch<decltype(XINPUT_GAMEPAD::sThumbRY), SHORT>::value);

static_assert(offsetof(XINPUT_GAMEPAD, wButtons) == 0);
static_assert(offsetof(XINPUT_GAMEPAD, bLeftTrigger) == 2);
static_assert(offsetof(XINPUT_GAMEPAD, bRightTrigger) == 3);
static_assert(offsetof(XINPUT_GAMEPAD, sThumbLX) == 4);
static_assert(offsetof(XINPUT_GAMEPAD, sThumbLY) == 6);
static_assert(offsetof(XINPUT_GAMEPAD, sThumbRX) == 8);
static_assert(offsetof(XINPUT_GAMEPAD, sThumbRY) == 0xA);

static_assert(sizeof(XINPUT_GAMEPAD) == 12);

typedef XINPUT_GAMEPAD * PXINPUT_GAMEPAD;

static_assert(TypeMatch<PXINPUT_GAMEPAD, XINPUT_GAMEPAD *>::value);

static_assert(sizeof(PXINPUT_GAMEPAD) == 4);

// XINPUT_STATE

struct XINPUT_STATE
{
	DWORD dwPacketNumber; // 0
	XINPUT_GAMEPAD Gamepad; // 4
};

static_assert(TypeMatch<decltype(XINPUT_STATE::dwPacketNumber), DWORD>::value);
static_assert(TypeMatch<decltype(XINPUT_STATE::Gamepad), XINPUT_GAMEPAD>::value);

static_assert(offsetof(XINPUT_STATE, dwPacketNumber) == 0);
static_assert(offsetof(XINPUT_STATE, Gamepad) == 4);

static_assert(sizeof(XINPUT_STATE) == 16);

typedef XINPUT_STATE * PXINPUT_STATE;

static_assert(TypeMatch<PXINPUT_STATE, XINPUT_STATE *>::value);

static_assert(sizeof(PXINPUT_STATE) == 4);

// XINPUT_VIBRATION

struct XINPUT_VIBRATION
{
	WORD wLeftMotorSpeed; // 0
	WORD wRightMotorSpeed; // 2
};

static_assert(TypeMatch<decltype(XINPUT_VIBRATION::wLeftMotorSpeed), WORD>::value);
static_assert(TypeMatch<decltype(XINPUT_VIBRATION::wRightMotorSpeed), WORD>::value);

static_assert(offsetof(XINPUT_VIBRATION, wLeftMotorSpeed) == 0);
static_assert(offsetof(XINPUT_VIBRATION, wRightMotorSpeed) == 2);

static_assert(sizeof(XINPUT_VIBRATION) == 4);

typedef XINPUT_VIBRATION * PXINPUT_VIBRATION;

static_assert(TypeMatch<PXINPUT_VIBRATION, XINPUT_VIBRATION *>::value);

static_assert(sizeof(PXINPUT_VIBRATION) == 4);

// XINPUT_CAPABILITIES

struct XINPUT_CAPABILITIES
{
	BYTE Type; // 0
	BYTE SubType; // 1
	WORD Flags; // 2
	XINPUT_GAMEPAD Gamepad; // 4
	XINPUT_VIBRATION Vibration; // 0x10
};

static_assert(TypeMatch<decltype(XINPUT_CAPABILITIES::Type), BYTE>::value);
static_assert(TypeMatch<decltype(XINPUT_CAPABILITIES::SubType), BYTE>::value);
static_assert(TypeMatch<decltype(XINPUT_CAPABILITIES::Flags), WORD>::value);
static_assert(TypeMatch<decltype(XINPUT_CAPABILITIES::Gamepad), XINPUT_GAMEPAD>::value);
static_assert(TypeMatch<decltype(XINPUT_CAPABILITIES::Vibration), XINPUT_VIBRATION>::value);

static_assert(offsetof(XINPUT_CAPABILITIES, Type) == 0);
static_assert(offsetof(XINPUT_CAPABILITIES, SubType) == 1);
static_assert(offsetof(XINPUT_CAPABILITIES, Flags) == 2);
static_assert(offsetof(XINPUT_CAPABILITIES, Gamepad) == 4);
static_assert(offsetof(XINPUT_CAPABILITIES, Vibration) == 0x10);

static_assert(sizeof(XINPUT_CAPABILITIES) == 20);

typedef XINPUT_CAPABILITIES * PXINPUT_CAPABILITIES;

static_assert(TypeMatch<PXINPUT_CAPABILITIES, XINPUT_CAPABILITIES *>::value);

static_assert(sizeof(PXINPUT_CAPABILITIES) == 4);

// XINPUT_BATTERY_INFORMATION

struct XINPUT_BATTERY_INFORMATION
{
	BYTE BatteryType; // 0
	BYTE BatteryLevel; // 1
};

static_assert(TypeMatch<decltype(XINPUT_BATTERY_INFORMATION::BatteryType), BYTE>::value);
static_assert(TypeMatch<decltype(XINPUT_BATTERY_INFORMATION::BatteryLevel), BYTE>::value);

static_assert(offsetof(XINPUT_BATTERY_INFORMATION, BatteryType) == 0);
static_assert(offsetof(XINPUT_BATTERY_INFORMATION, BatteryLevel) == 1);

static_assert(sizeof(XINPUT_BATTERY_INFORMATION) == 2);

typedef XINPUT_BATTERY_INFORMATION * PXINPUT_BATTERY_INFORMATION;

static_assert(TypeMatch<PXINPUT_BATTERY_INFORMATION, XINPUT_BATTERY_INFORMATION *>::value);

static_assert(sizeof(PXINPUT_BATTERY_INFORMATION) == 4);

// XINPUT_KEYSTROKE

struct XINPUT_KEYSTROKE
{
	WORD VirtualKey; // 0
	WCHAR Unicode; // 2
	WORD Flags; // 4
	BYTE UserIndex; // 6
	BYTE HidCode; // 7
};

static_assert(TypeMatch<decltype(XINPUT_KEYSTROKE::VirtualKey), WORD>::value);
static_assert(TypeMatch<decltype(XINPUT_KEYSTROKE::Unicode), WCHAR>::value);
static_assert(TypeMatch<decltype(XINPUT_KEYSTROKE::Flags), WORD>::value);
static_assert(TypeMatch<decltype(XINPUT_KEYSTROKE::UserIndex), BYTE>::value);
static_assert(TypeMatch<decltype(XINPUT_KEYSTROKE::HidCode), BYTE>::value);

static_assert(offsetof(XINPUT_KEYSTROKE, VirtualKey) == 0);
static_assert(offsetof(XINPUT_KEYSTROKE, Unicode) == 2);
static_assert(offsetof(XINPUT_KEYSTROKE, Flags) == 4);
static_assert(offsetof(XINPUT_KEYSTROKE, UserIndex) == 6);
static_assert(offsetof(XINPUT_KEYSTROKE, HidCode) == 7);

static_assert(sizeof(XINPUT_KEYSTROKE) == 8);

typedef XINPUT_KEYSTROKE * PXINPUT_KEYSTROKE;

static_assert(TypeMatch<PXINPUT_KEYSTROKE, XINPUT_KEYSTROKE *>::value);

static_assert(sizeof(PXINPUT_KEYSTROKE) == 4);

#pragma pack(pop)

extern "C" DWORD __stdcall XInputGetState
(
	DWORD dwUserIndex,
	XINPUT_STATE* pState
);
extern "C" DWORD __stdcall XInputSetState
(
	DWORD dwUserIndex,
	XINPUT_VIBRATION* pVibration
);
extern "C" DWORD __stdcall XInputGetCapabilities
(
	DWORD dwUserIndex,
	DWORD dwFlags,
	XINPUT_CAPABILITIES* pCapabilities
);
extern "C" void __stdcall XInputEnable(BOOL enable);
extern "C" DWORD __stdcall XInputGetAudioDeviceIds
(
	DWORD dwUserIndex,
	LPWSTR pRenderDeviceId,
	UINT* pRenderCount,
	LPWSTR pCaptureDeviceId,
	UINT* pCaptureCount
);
extern "C" DWORD __stdcall XInputGetBatteryInformation
(
	DWORD dwUserIndex,
	BYTE devType,
	XINPUT_BATTERY_INFORMATION* pBatteryInformation
);
extern "C" DWORD __stdcall XInputGetKeystroke
(
	DWORD dwUserIndex,
	DWORD dwReserved,
	PXINPUT_KEYSTROKE pKeystroke
);
#pragma endregion

#endif

namespaceEnd();
