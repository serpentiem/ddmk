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

export module DI8;

import Windows;

using namespace Windows;

export namespaceStart(DI8);

#ifdef _WIN64

#pragma region x86_64

struct IDirectInput8A;
struct IDirectInput8W;
struct IDirectInputDevice8A;
struct IDirectInputDevice8W;
struct IDirectInputEffect;

extern "C" const GUID IID_IDirectInput8A;
extern "C" const GUID IID_IDirectInput8W;
extern "C" const GUID IID_IDirectInputDevice8A;
extern "C" const GUID IID_IDirectInputDevice8W;
extern "C" const GUID IID_IDirectInputEffect;

extern "C" const GUID GUID_XAxis;
extern "C" const GUID GUID_YAxis;
extern "C" const GUID GUID_ZAxis;
extern "C" const GUID GUID_RxAxis;
extern "C" const GUID GUID_RyAxis;
extern "C" const GUID GUID_RzAxis;
extern "C" const GUID GUID_Slider;
extern "C" const GUID GUID_Button;
extern "C" const GUID GUID_Key;
extern "C" const GUID GUID_POV;
extern "C" const GUID GUID_Unknown;
extern "C" const GUID GUID_SysMouse;
extern "C" const GUID GUID_SysKeyboard;
extern "C" const GUID GUID_Joystick;
extern "C" const GUID GUID_SysMouseEm;
extern "C" const GUID GUID_SysMouseEm2;
extern "C" const GUID GUID_SysKeyboardEm;
extern "C" const GUID GUID_SysKeyboardEm2;
extern "C" const GUID GUID_ConstantForce;
extern "C" const GUID GUID_RampForce;
extern "C" const GUID GUID_Square;
extern "C" const GUID GUID_Sine;
extern "C" const GUID GUID_Triangle;
extern "C" const GUID GUID_SawtoothUp;
extern "C" const GUID GUID_SawtoothDown;
extern "C" const GUID GUID_Spring;
extern "C" const GUID GUID_Damper;
extern "C" const GUID GUID_Inertia;
extern "C" const GUID GUID_Friction;
extern "C" const GUID GUID_CustomForce;

// LPDIRECTINPUTDEVICE8A

typedef IDirectInputDevice8A* LPDIRECTINPUTDEVICE8A;

static_assert(TypeMatch<LPDIRECTINPUTDEVICE8A, IDirectInputDevice8A*>::value);

static_assert(sizeof(LPDIRECTINPUTDEVICE8A) == 8);

// LPDIRECTINPUTDEVICE8W

typedef IDirectInputDevice8W* LPDIRECTINPUTDEVICE8W;

static_assert(TypeMatch<LPDIRECTINPUTDEVICE8W, IDirectInputDevice8W*>::value);

static_assert(sizeof(LPDIRECTINPUTDEVICE8W) == 8);

// LPDIRECTINPUTEFFECT

typedef IDirectInputEffect* LPDIRECTINPUTEFFECT;

static_assert(TypeMatch<LPDIRECTINPUTEFFECT, IDirectInputEffect*>::value);

static_assert(sizeof(LPDIRECTINPUTEFFECT) == 8);

// D3DCOLOR

typedef DWORD D3DCOLOR;

static_assert(TypeMatch<D3DCOLOR, DWORD>::value);

static_assert(sizeof(D3DCOLOR) == 4);

enum
{
	DI_OK=0,
	DISCL_EXCLUSIVE=0x00000001,
	DISCL_NONEXCLUSIVE=0x00000002,
	DISCL_FOREGROUND=0x00000004,
	DISCL_BACKGROUND=0x00000008,
	DISCL_NOWINKEY=0x00000010,
	DIERR_OLDDIRECTINPUTVERSION=0x8007047E,
	DIERR_BETADIRECTINPUTVERSION=0x80070481,
	DIERR_BADDRIVERVER=0x80070077,
	DIERR_DEVICENOTREG=0x80040154,
	DIERR_NOTFOUND=0x80070002,
	DIERR_OBJECTNOTFOUND=0x80070002,
	DIERR_INVALIDPARAM=0x80070057,
	DIERR_NOINTERFACE=0x80004002,
	DIERR_GENERIC=0x80004005,
	DIERR_OUTOFMEMORY=0x8007000E,
	DIERR_UNSUPPORTED=0x80004001,
	DIERR_NOTINITIALIZED=0x80070015,
	DIERR_ALREADYINITIALIZED=0x800704DF,
	DIERR_NOAGGREGATION=0x80040110,
	DIERR_OTHERAPPHASPRIO=0x80070005,
	DIERR_INPUTLOST=0x8007001E,
	DIERR_ACQUIRED=0x800700AA,
	DIERR_NOTACQUIRED=0x8007000C,
	DIERR_READONLY=0x80070005,
	DIERR_HANDLEEXISTS=0x80070005,
	DIERR_INSUFFICIENTPRIVS=0x80040200,
	DIERR_DEVICEFULL=0x80040201,
	DIERR_MOREDATA=0x80040202,
	DIERR_NOTDOWNLOADED=0x80040203,
	DIERR_HASEFFECTS=0x80040204,
	DIERR_NOTEXCLUSIVEACQUIRED=0x80040205,
	DIERR_INCOMPLETEEFFECT=0x80040206,
	DIERR_NOTBUFFERED=0x80040207,
	DIERR_EFFECTPLAYING=0x80040208,
	DIERR_UNPLUGGED=0x80040209,
	DIERR_REPORTFULL=0x8004020A,
	DIERR_MAPFILEFAIL=0x8004020B,
	DIDEVTYPE_HID=0x10000,
	DI8DEVCLASS_ALL=0,
	DI8DEVCLASS_DEVICE=1,
	DI8DEVCLASS_POINTER=2,
	DI8DEVCLASS_KEYBOARD=3,
	DI8DEVCLASS_GAMECTRL=4,
	DI8DEVTYPE_DEVICE=0x11,
	DI8DEVTYPE_MOUSE=0x12,
	DI8DEVTYPE_KEYBOARD=0x13,
	DI8DEVTYPE_JOYSTICK=0x14,
	DI8DEVTYPE_GAMEPAD=0x15,
	DI8DEVTYPE_DRIVING=0x16,
	DI8DEVTYPE_FLIGHT=0x17,
	DI8DEVTYPE_1STPERSON=0x18,
	DI8DEVTYPE_DEVICECTRL=0x19,
	DI8DEVTYPE_SCREENPOINTER=0x1A,
	DI8DEVTYPE_REMOTE=0x1B,
	DI8DEVTYPE_SUPPLEMENTAL=0x1C,
	DIEDFL_ALLDEVICES=0x00000000,
	DIEDFL_ATTACHEDONLY=0x00000001,
	DIEDFL_FORCEFEEDBACK=0x00000100,
	DIEDFL_INCLUDEALIASES=0x00010000,
	DIEDFL_INCLUDEPHANTOMS=0x00020000,
	DIEDFL_INCLUDEHIDDEN=0x00040000,
	DIENUM_STOP=0,
	DIENUM_CONTINUE=1,
};

#pragma pack(push, 1)

// DIMOUSESTATE

struct DIMOUSESTATE
{
	LONG lX; // 0
	LONG lY; // 4
	LONG lZ; // 8
	BYTE rgbButtons[4]; // 0xC
};

static_assert(TypeMatch<decltype(DIMOUSESTATE::lX), LONG>::value);
static_assert(TypeMatch<decltype(DIMOUSESTATE::lY), LONG>::value);
static_assert(TypeMatch<decltype(DIMOUSESTATE::lZ), LONG>::value);
static_assert(TypeMatch<decltype(DIMOUSESTATE::rgbButtons), BYTE[4]>::value);

static_assert(offsetof(DIMOUSESTATE, lX) == 0);
static_assert(offsetof(DIMOUSESTATE, lY) == 4);
static_assert(offsetof(DIMOUSESTATE, lZ) == 8);
static_assert(offsetof(DIMOUSESTATE, rgbButtons) == 0xC);

static_assert(sizeof(DIMOUSESTATE) == 16);

typedef DIMOUSESTATE * LPDIMOUSESTATE;

static_assert(TypeMatch<LPDIMOUSESTATE, DIMOUSESTATE *>::value);

static_assert(sizeof(LPDIMOUSESTATE) == 8);

// DIMOUSESTATE2

struct DIMOUSESTATE2
{
	LONG lX; // 0
	LONG lY; // 4
	LONG lZ; // 8
	BYTE rgbButtons[8]; // 0xC
};

static_assert(TypeMatch<decltype(DIMOUSESTATE2::lX), LONG>::value);
static_assert(TypeMatch<decltype(DIMOUSESTATE2::lY), LONG>::value);
static_assert(TypeMatch<decltype(DIMOUSESTATE2::lZ), LONG>::value);
static_assert(TypeMatch<decltype(DIMOUSESTATE2::rgbButtons), BYTE[8]>::value);

static_assert(offsetof(DIMOUSESTATE2, lX) == 0);
static_assert(offsetof(DIMOUSESTATE2, lY) == 4);
static_assert(offsetof(DIMOUSESTATE2, lZ) == 8);
static_assert(offsetof(DIMOUSESTATE2, rgbButtons) == 0xC);

static_assert(sizeof(DIMOUSESTATE2) == 20);

typedef DIMOUSESTATE2 * LPDIMOUSESTATE2;

static_assert(TypeMatch<LPDIMOUSESTATE2, DIMOUSESTATE2 *>::value);

static_assert(sizeof(LPDIMOUSESTATE2) == 8);

// DIDEVCAPS

struct DIDEVCAPS
{
	DWORD dwSize; // 0
	DWORD dwFlags; // 4
	DWORD dwDevType; // 8
	DWORD dwAxes; // 0xC
	DWORD dwButtons; // 0x10
	DWORD dwPOVs; // 0x14
	DWORD dwFFSamplePeriod; // 0x18
	DWORD dwFFMinTimeResolution; // 0x1C
	DWORD dwFirmwareRevision; // 0x20
	DWORD dwHardwareRevision; // 0x24
	DWORD dwFFDriverVersion; // 0x28
};

static_assert(TypeMatch<decltype(DIDEVCAPS::dwSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVCAPS::dwFlags), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVCAPS::dwDevType), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVCAPS::dwAxes), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVCAPS::dwButtons), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVCAPS::dwPOVs), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVCAPS::dwFFSamplePeriod), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVCAPS::dwFFMinTimeResolution), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVCAPS::dwFirmwareRevision), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVCAPS::dwHardwareRevision), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVCAPS::dwFFDriverVersion), DWORD>::value);

static_assert(offsetof(DIDEVCAPS, dwSize) == 0);
static_assert(offsetof(DIDEVCAPS, dwFlags) == 4);
static_assert(offsetof(DIDEVCAPS, dwDevType) == 8);
static_assert(offsetof(DIDEVCAPS, dwAxes) == 0xC);
static_assert(offsetof(DIDEVCAPS, dwButtons) == 0x10);
static_assert(offsetof(DIDEVCAPS, dwPOVs) == 0x14);
static_assert(offsetof(DIDEVCAPS, dwFFSamplePeriod) == 0x18);
static_assert(offsetof(DIDEVCAPS, dwFFMinTimeResolution) == 0x1C);
static_assert(offsetof(DIDEVCAPS, dwFirmwareRevision) == 0x20);
static_assert(offsetof(DIDEVCAPS, dwHardwareRevision) == 0x24);
static_assert(offsetof(DIDEVCAPS, dwFFDriverVersion) == 0x28);

static_assert(sizeof(DIDEVCAPS) == 44);

typedef DIDEVCAPS * LPDIDEVCAPS;

static_assert(TypeMatch<LPDIDEVCAPS, DIDEVCAPS *>::value);

static_assert(sizeof(LPDIDEVCAPS) == 8);

// DIOBJECTDATAFORMAT

struct DIOBJECTDATAFORMAT
{
	const GUID* pguid; // 0
	DWORD dwOfs; // 8
	DWORD dwType; // 0xC
	DWORD dwFlags; // 0x10
	_(4);
};

static_assert(TypeMatch<decltype(DIOBJECTDATAFORMAT::pguid), const GUID*>::value);
static_assert(TypeMatch<decltype(DIOBJECTDATAFORMAT::dwOfs), DWORD>::value);
static_assert(TypeMatch<decltype(DIOBJECTDATAFORMAT::dwType), DWORD>::value);
static_assert(TypeMatch<decltype(DIOBJECTDATAFORMAT::dwFlags), DWORD>::value);

static_assert(offsetof(DIOBJECTDATAFORMAT, pguid) == 0);
static_assert(offsetof(DIOBJECTDATAFORMAT, dwOfs) == 8);
static_assert(offsetof(DIOBJECTDATAFORMAT, dwType) == 0xC);
static_assert(offsetof(DIOBJECTDATAFORMAT, dwFlags) == 0x10);

static_assert(sizeof(DIOBJECTDATAFORMAT) == 24);

typedef DIOBJECTDATAFORMAT * LPDIOBJECTDATAFORMAT;
typedef const DIOBJECTDATAFORMAT * LPCDIOBJECTDATAFORMAT;

static_assert(TypeMatch<LPDIOBJECTDATAFORMAT, DIOBJECTDATAFORMAT *>::value);
static_assert(TypeMatch<LPCDIOBJECTDATAFORMAT, const DIOBJECTDATAFORMAT *>::value);

static_assert(sizeof(LPDIOBJECTDATAFORMAT) == 8);
static_assert(sizeof(LPCDIOBJECTDATAFORMAT) == 8);

// DIDATAFORMAT

struct DIDATAFORMAT
{
	DWORD dwSize; // 0
	DWORD dwObjSize; // 4
	DWORD dwFlags; // 8
	DWORD dwDataSize; // 0xC
	DWORD dwNumObjs; // 0x10
	_(4);
	LPDIOBJECTDATAFORMAT rgodf; // 0x18
};

static_assert(TypeMatch<decltype(DIDATAFORMAT::dwSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIDATAFORMAT::dwObjSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIDATAFORMAT::dwFlags), DWORD>::value);
static_assert(TypeMatch<decltype(DIDATAFORMAT::dwDataSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIDATAFORMAT::dwNumObjs), DWORD>::value);
static_assert(TypeMatch<decltype(DIDATAFORMAT::rgodf), LPDIOBJECTDATAFORMAT>::value);

static_assert(offsetof(DIDATAFORMAT, dwSize) == 0);
static_assert(offsetof(DIDATAFORMAT, dwObjSize) == 4);
static_assert(offsetof(DIDATAFORMAT, dwFlags) == 8);
static_assert(offsetof(DIDATAFORMAT, dwDataSize) == 0xC);
static_assert(offsetof(DIDATAFORMAT, dwNumObjs) == 0x10);
static_assert(offsetof(DIDATAFORMAT, rgodf) == 0x18);

static_assert(sizeof(DIDATAFORMAT) == 32);

typedef DIDATAFORMAT * LPDIDATAFORMAT;
typedef const DIDATAFORMAT * LPCDIDATAFORMAT;

static_assert(TypeMatch<LPDIDATAFORMAT, DIDATAFORMAT *>::value);
static_assert(TypeMatch<LPCDIDATAFORMAT, const DIDATAFORMAT *>::value);

static_assert(sizeof(LPDIDATAFORMAT) == 8);
static_assert(sizeof(LPCDIDATAFORMAT) == 8);

// DIPROPHEADER

struct DIPROPHEADER
{
	DWORD dwSize; // 0
	DWORD dwHeaderSize; // 4
	DWORD dwObj; // 8
	DWORD dwHow; // 0xC
};

static_assert(TypeMatch<decltype(DIPROPHEADER::dwSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIPROPHEADER::dwHeaderSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIPROPHEADER::dwObj), DWORD>::value);
static_assert(TypeMatch<decltype(DIPROPHEADER::dwHow), DWORD>::value);

static_assert(offsetof(DIPROPHEADER, dwSize) == 0);
static_assert(offsetof(DIPROPHEADER, dwHeaderSize) == 4);
static_assert(offsetof(DIPROPHEADER, dwObj) == 8);
static_assert(offsetof(DIPROPHEADER, dwHow) == 0xC);

static_assert(sizeof(DIPROPHEADER) == 16);

typedef DIPROPHEADER * LPDIPROPHEADER;
typedef const DIPROPHEADER * LPCDIPROPHEADER;

static_assert(TypeMatch<LPDIPROPHEADER, DIPROPHEADER *>::value);
static_assert(TypeMatch<LPCDIPROPHEADER, const DIPROPHEADER *>::value);

static_assert(sizeof(LPDIPROPHEADER) == 8);
static_assert(sizeof(LPCDIPROPHEADER) == 8);

// DIDEVICEOBJECTINSTANCEA

struct DIDEVICEOBJECTINSTANCEA
{
	DWORD dwSize; // 0
	GUID guidType; // 4
	DWORD dwOfs; // 0x14
	DWORD dwType; // 0x18
	DWORD dwFlags; // 0x1C
	CHAR tszName[260]; // 0x20
	DWORD dwFFMaxForce; // 0x124
	DWORD dwFFForceResolution; // 0x128
	WORD wCollectionNumber; // 0x12C
	WORD wDesignatorIndex; // 0x12E
	WORD wUsagePage; // 0x130
	WORD wUsage; // 0x132
	DWORD dwDimension; // 0x134
	WORD wExponent; // 0x138
	WORD wReportId; // 0x13A
};

static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEA::dwSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEA::guidType), GUID>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEA::dwOfs), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEA::dwType), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEA::dwFlags), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEA::tszName), CHAR[260]>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEA::dwFFMaxForce), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEA::dwFFForceResolution), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEA::wCollectionNumber), WORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEA::wDesignatorIndex), WORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEA::wUsagePage), WORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEA::wUsage), WORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEA::dwDimension), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEA::wExponent), WORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEA::wReportId), WORD>::value);

static_assert(offsetof(DIDEVICEOBJECTINSTANCEA, dwSize) == 0);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEA, guidType) == 4);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEA, dwOfs) == 0x14);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEA, dwType) == 0x18);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEA, dwFlags) == 0x1C);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEA, tszName) == 0x20);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEA, dwFFMaxForce) == 0x124);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEA, dwFFForceResolution) == 0x128);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEA, wCollectionNumber) == 0x12C);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEA, wDesignatorIndex) == 0x12E);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEA, wUsagePage) == 0x130);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEA, wUsage) == 0x132);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEA, dwDimension) == 0x134);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEA, wExponent) == 0x138);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEA, wReportId) == 0x13A);

static_assert(sizeof(DIDEVICEOBJECTINSTANCEA) == 316);

typedef DIDEVICEOBJECTINSTANCEA * LPDIDEVICEOBJECTINSTANCEA;
typedef const DIDEVICEOBJECTINSTANCEA * LPCDIDEVICEOBJECTINSTANCEA;

static_assert(TypeMatch<LPDIDEVICEOBJECTINSTANCEA, DIDEVICEOBJECTINSTANCEA *>::value);
static_assert(TypeMatch<LPCDIDEVICEOBJECTINSTANCEA, const DIDEVICEOBJECTINSTANCEA *>::value);

static_assert(sizeof(LPDIDEVICEOBJECTINSTANCEA) == 8);
static_assert(sizeof(LPCDIDEVICEOBJECTINSTANCEA) == 8);

// DIDEVICEOBJECTINSTANCEW

struct DIDEVICEOBJECTINSTANCEW
{
	DWORD dwSize; // 0
	GUID guidType; // 4
	DWORD dwOfs; // 0x14
	DWORD dwType; // 0x18
	DWORD dwFlags; // 0x1C
	WCHAR tszName[260]; // 0x20
	DWORD dwFFMaxForce; // 0x228
	DWORD dwFFForceResolution; // 0x22C
	WORD wCollectionNumber; // 0x230
	WORD wDesignatorIndex; // 0x232
	WORD wUsagePage; // 0x234
	WORD wUsage; // 0x236
	DWORD dwDimension; // 0x238
	WORD wExponent; // 0x23C
	WORD wReportId; // 0x23E
};

static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEW::dwSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEW::guidType), GUID>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEW::dwOfs), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEW::dwType), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEW::dwFlags), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEW::tszName), WCHAR[260]>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEW::dwFFMaxForce), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEW::dwFFForceResolution), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEW::wCollectionNumber), WORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEW::wDesignatorIndex), WORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEW::wUsagePage), WORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEW::wUsage), WORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEW::dwDimension), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEW::wExponent), WORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEW::wReportId), WORD>::value);

static_assert(offsetof(DIDEVICEOBJECTINSTANCEW, dwSize) == 0);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEW, guidType) == 4);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEW, dwOfs) == 0x14);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEW, dwType) == 0x18);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEW, dwFlags) == 0x1C);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEW, tszName) == 0x20);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEW, dwFFMaxForce) == 0x228);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEW, dwFFForceResolution) == 0x22C);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEW, wCollectionNumber) == 0x230);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEW, wDesignatorIndex) == 0x232);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEW, wUsagePage) == 0x234);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEW, wUsage) == 0x236);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEW, dwDimension) == 0x238);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEW, wExponent) == 0x23C);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEW, wReportId) == 0x23E);

static_assert(sizeof(DIDEVICEOBJECTINSTANCEW) == 576);

typedef DIDEVICEOBJECTINSTANCEW * LPDIDEVICEOBJECTINSTANCEW;
typedef const DIDEVICEOBJECTINSTANCEW * LPCDIDEVICEOBJECTINSTANCEW;

static_assert(TypeMatch<LPDIDEVICEOBJECTINSTANCEW, DIDEVICEOBJECTINSTANCEW *>::value);
static_assert(TypeMatch<LPCDIDEVICEOBJECTINSTANCEW, const DIDEVICEOBJECTINSTANCEW *>::value);

static_assert(sizeof(LPDIDEVICEOBJECTINSTANCEW) == 8);
static_assert(sizeof(LPCDIDEVICEOBJECTINSTANCEW) == 8);

// DIDEVICEOBJECTDATA

struct DIDEVICEOBJECTDATA
{
	DWORD dwOfs; // 0
	DWORD dwData; // 4
	DWORD dwTimeStamp; // 8
	DWORD dwSequence; // 0xC
	UINT_PTR uAppData; // 0x10
};

static_assert(TypeMatch<decltype(DIDEVICEOBJECTDATA::dwOfs), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTDATA::dwData), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTDATA::dwTimeStamp), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTDATA::dwSequence), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTDATA::uAppData), UINT_PTR>::value);

static_assert(offsetof(DIDEVICEOBJECTDATA, dwOfs) == 0);
static_assert(offsetof(DIDEVICEOBJECTDATA, dwData) == 4);
static_assert(offsetof(DIDEVICEOBJECTDATA, dwTimeStamp) == 8);
static_assert(offsetof(DIDEVICEOBJECTDATA, dwSequence) == 0xC);
static_assert(offsetof(DIDEVICEOBJECTDATA, uAppData) == 0x10);

static_assert(sizeof(DIDEVICEOBJECTDATA) == 24);

typedef DIDEVICEOBJECTDATA * LPDIDEVICEOBJECTDATA;
typedef const DIDEVICEOBJECTDATA * LPCDIDEVICEOBJECTDATA;

static_assert(TypeMatch<LPDIDEVICEOBJECTDATA, DIDEVICEOBJECTDATA *>::value);
static_assert(TypeMatch<LPCDIDEVICEOBJECTDATA, const DIDEVICEOBJECTDATA *>::value);

static_assert(sizeof(LPDIDEVICEOBJECTDATA) == 8);
static_assert(sizeof(LPCDIDEVICEOBJECTDATA) == 8);

// DIDEVICEINSTANCEA

struct DIDEVICEINSTANCEA
{
	DWORD dwSize; // 0
	GUID guidInstance; // 4
	GUID guidProduct; // 0x14
	DWORD dwDevType; // 0x24
	CHAR tszInstanceName[260]; // 0x28
	CHAR tszProductName[260]; // 0x12C
	GUID guidFFDriver; // 0x230
	WORD wUsagePage; // 0x240
	WORD wUsage; // 0x242
};

static_assert(TypeMatch<decltype(DIDEVICEINSTANCEA::dwSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEINSTANCEA::guidInstance), GUID>::value);
static_assert(TypeMatch<decltype(DIDEVICEINSTANCEA::guidProduct), GUID>::value);
static_assert(TypeMatch<decltype(DIDEVICEINSTANCEA::dwDevType), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEINSTANCEA::tszInstanceName), CHAR[260]>::value);
static_assert(TypeMatch<decltype(DIDEVICEINSTANCEA::tszProductName), CHAR[260]>::value);
static_assert(TypeMatch<decltype(DIDEVICEINSTANCEA::guidFFDriver), GUID>::value);
static_assert(TypeMatch<decltype(DIDEVICEINSTANCEA::wUsagePage), WORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEINSTANCEA::wUsage), WORD>::value);

static_assert(offsetof(DIDEVICEINSTANCEA, dwSize) == 0);
static_assert(offsetof(DIDEVICEINSTANCEA, guidInstance) == 4);
static_assert(offsetof(DIDEVICEINSTANCEA, guidProduct) == 0x14);
static_assert(offsetof(DIDEVICEINSTANCEA, dwDevType) == 0x24);
static_assert(offsetof(DIDEVICEINSTANCEA, tszInstanceName) == 0x28);
static_assert(offsetof(DIDEVICEINSTANCEA, tszProductName) == 0x12C);
static_assert(offsetof(DIDEVICEINSTANCEA, guidFFDriver) == 0x230);
static_assert(offsetof(DIDEVICEINSTANCEA, wUsagePage) == 0x240);
static_assert(offsetof(DIDEVICEINSTANCEA, wUsage) == 0x242);

static_assert(sizeof(DIDEVICEINSTANCEA) == 580);

typedef DIDEVICEINSTANCEA * LPDIDEVICEINSTANCEA;
typedef const DIDEVICEINSTANCEA * LPCDIDEVICEINSTANCEA;

static_assert(TypeMatch<LPDIDEVICEINSTANCEA, DIDEVICEINSTANCEA *>::value);
static_assert(TypeMatch<LPCDIDEVICEINSTANCEA, const DIDEVICEINSTANCEA *>::value);

static_assert(sizeof(LPDIDEVICEINSTANCEA) == 8);
static_assert(sizeof(LPCDIDEVICEINSTANCEA) == 8);

// DIDEVICEINSTANCEW

struct DIDEVICEINSTANCEW
{
	DWORD dwSize; // 0
	GUID guidInstance; // 4
	GUID guidProduct; // 0x14
	DWORD dwDevType; // 0x24
	WCHAR tszInstanceName[260]; // 0x28
	WCHAR tszProductName[260]; // 0x230
	GUID guidFFDriver; // 0x438
	WORD wUsagePage; // 0x448
	WORD wUsage; // 0x44A
};

static_assert(TypeMatch<decltype(DIDEVICEINSTANCEW::dwSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEINSTANCEW::guidInstance), GUID>::value);
static_assert(TypeMatch<decltype(DIDEVICEINSTANCEW::guidProduct), GUID>::value);
static_assert(TypeMatch<decltype(DIDEVICEINSTANCEW::dwDevType), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEINSTANCEW::tszInstanceName), WCHAR[260]>::value);
static_assert(TypeMatch<decltype(DIDEVICEINSTANCEW::tszProductName), WCHAR[260]>::value);
static_assert(TypeMatch<decltype(DIDEVICEINSTANCEW::guidFFDriver), GUID>::value);
static_assert(TypeMatch<decltype(DIDEVICEINSTANCEW::wUsagePage), WORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEINSTANCEW::wUsage), WORD>::value);

static_assert(offsetof(DIDEVICEINSTANCEW, dwSize) == 0);
static_assert(offsetof(DIDEVICEINSTANCEW, guidInstance) == 4);
static_assert(offsetof(DIDEVICEINSTANCEW, guidProduct) == 0x14);
static_assert(offsetof(DIDEVICEINSTANCEW, dwDevType) == 0x24);
static_assert(offsetof(DIDEVICEINSTANCEW, tszInstanceName) == 0x28);
static_assert(offsetof(DIDEVICEINSTANCEW, tszProductName) == 0x230);
static_assert(offsetof(DIDEVICEINSTANCEW, guidFFDriver) == 0x438);
static_assert(offsetof(DIDEVICEINSTANCEW, wUsagePage) == 0x448);
static_assert(offsetof(DIDEVICEINSTANCEW, wUsage) == 0x44A);

static_assert(sizeof(DIDEVICEINSTANCEW) == 1100);

typedef DIDEVICEINSTANCEW * LPDIDEVICEINSTANCEW;
typedef const DIDEVICEINSTANCEW * LPCDIDEVICEINSTANCEW;

static_assert(TypeMatch<LPDIDEVICEINSTANCEW, DIDEVICEINSTANCEW *>::value);
static_assert(TypeMatch<LPCDIDEVICEINSTANCEW, const DIDEVICEINSTANCEW *>::value);

static_assert(sizeof(LPDIDEVICEINSTANCEW) == 8);
static_assert(sizeof(LPCDIDEVICEINSTANCEW) == 8);

// DIENVELOPE

struct DIENVELOPE
{
	DWORD dwSize; // 0
	DWORD dwAttackLevel; // 4
	DWORD dwAttackTime; // 8
	DWORD dwFadeLevel; // 0xC
	DWORD dwFadeTime; // 0x10
};

static_assert(TypeMatch<decltype(DIENVELOPE::dwSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIENVELOPE::dwAttackLevel), DWORD>::value);
static_assert(TypeMatch<decltype(DIENVELOPE::dwAttackTime), DWORD>::value);
static_assert(TypeMatch<decltype(DIENVELOPE::dwFadeLevel), DWORD>::value);
static_assert(TypeMatch<decltype(DIENVELOPE::dwFadeTime), DWORD>::value);

static_assert(offsetof(DIENVELOPE, dwSize) == 0);
static_assert(offsetof(DIENVELOPE, dwAttackLevel) == 4);
static_assert(offsetof(DIENVELOPE, dwAttackTime) == 8);
static_assert(offsetof(DIENVELOPE, dwFadeLevel) == 0xC);
static_assert(offsetof(DIENVELOPE, dwFadeTime) == 0x10);

static_assert(sizeof(DIENVELOPE) == 20);

typedef DIENVELOPE * LPDIENVELOPE;
typedef const DIENVELOPE * LPCDIENVELOPE;

static_assert(TypeMatch<LPDIENVELOPE, DIENVELOPE *>::value);
static_assert(TypeMatch<LPCDIENVELOPE, const DIENVELOPE *>::value);

static_assert(sizeof(LPDIENVELOPE) == 8);
static_assert(sizeof(LPCDIENVELOPE) == 8);

// DIEFFECT

struct DIEFFECT
{
	DWORD dwSize; // 0
	DWORD dwFlags; // 4
	DWORD dwDuration; // 8
	DWORD dwSamplePeriod; // 0xC
	DWORD dwGain; // 0x10
	DWORD dwTriggerButton; // 0x14
	DWORD dwTriggerRepeatInterval; // 0x18
	DWORD cAxes; // 0x1C
	LPDWORD rgdwAxes; // 0x20
	LPLONG rglDirection; // 0x28
	LPDIENVELOPE lpEnvelope; // 0x30
	DWORD cbTypeSpecificParams; // 0x38
	_(4);
	LPVOID lpvTypeSpecificParams; // 0x40
	DWORD dwStartDelay; // 0x48
	_(4);
};

static_assert(TypeMatch<decltype(DIEFFECT::dwSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIEFFECT::dwFlags), DWORD>::value);
static_assert(TypeMatch<decltype(DIEFFECT::dwDuration), DWORD>::value);
static_assert(TypeMatch<decltype(DIEFFECT::dwSamplePeriod), DWORD>::value);
static_assert(TypeMatch<decltype(DIEFFECT::dwGain), DWORD>::value);
static_assert(TypeMatch<decltype(DIEFFECT::dwTriggerButton), DWORD>::value);
static_assert(TypeMatch<decltype(DIEFFECT::dwTriggerRepeatInterval), DWORD>::value);
static_assert(TypeMatch<decltype(DIEFFECT::cAxes), DWORD>::value);
static_assert(TypeMatch<decltype(DIEFFECT::rgdwAxes), LPDWORD>::value);
static_assert(TypeMatch<decltype(DIEFFECT::rglDirection), LPLONG>::value);
static_assert(TypeMatch<decltype(DIEFFECT::lpEnvelope), LPDIENVELOPE>::value);
static_assert(TypeMatch<decltype(DIEFFECT::cbTypeSpecificParams), DWORD>::value);
static_assert(TypeMatch<decltype(DIEFFECT::lpvTypeSpecificParams), LPVOID>::value);
static_assert(TypeMatch<decltype(DIEFFECT::dwStartDelay), DWORD>::value);

static_assert(offsetof(DIEFFECT, dwSize) == 0);
static_assert(offsetof(DIEFFECT, dwFlags) == 4);
static_assert(offsetof(DIEFFECT, dwDuration) == 8);
static_assert(offsetof(DIEFFECT, dwSamplePeriod) == 0xC);
static_assert(offsetof(DIEFFECT, dwGain) == 0x10);
static_assert(offsetof(DIEFFECT, dwTriggerButton) == 0x14);
static_assert(offsetof(DIEFFECT, dwTriggerRepeatInterval) == 0x18);
static_assert(offsetof(DIEFFECT, cAxes) == 0x1C);
static_assert(offsetof(DIEFFECT, rgdwAxes) == 0x20);
static_assert(offsetof(DIEFFECT, rglDirection) == 0x28);
static_assert(offsetof(DIEFFECT, lpEnvelope) == 0x30);
static_assert(offsetof(DIEFFECT, cbTypeSpecificParams) == 0x38);
static_assert(offsetof(DIEFFECT, lpvTypeSpecificParams) == 0x40);
static_assert(offsetof(DIEFFECT, dwStartDelay) == 0x48);

static_assert(sizeof(DIEFFECT) == 80);

typedef DIEFFECT * LPDIEFFECT;
typedef const DIEFFECT * LPCDIEFFECT;

static_assert(TypeMatch<LPDIEFFECT, DIEFFECT *>::value);
static_assert(TypeMatch<LPCDIEFFECT, const DIEFFECT *>::value);

static_assert(sizeof(LPDIEFFECT) == 8);
static_assert(sizeof(LPCDIEFFECT) == 8);

// DIFILEEFFECT

struct DIFILEEFFECT
{
	DWORD dwSize; // 0
	GUID GuidEffect; // 4
	_(4);
	LPCDIEFFECT lpDiEffect; // 0x18
	CHAR szFriendlyName[260]; // 0x20
	_(4);
};

static_assert(TypeMatch<decltype(DIFILEEFFECT::dwSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIFILEEFFECT::GuidEffect), GUID>::value);
static_assert(TypeMatch<decltype(DIFILEEFFECT::lpDiEffect), LPCDIEFFECT>::value);
static_assert(TypeMatch<decltype(DIFILEEFFECT::szFriendlyName), CHAR[260]>::value);

static_assert(offsetof(DIFILEEFFECT, dwSize) == 0);
static_assert(offsetof(DIFILEEFFECT, GuidEffect) == 4);
static_assert(offsetof(DIFILEEFFECT, lpDiEffect) == 0x18);
static_assert(offsetof(DIFILEEFFECT, szFriendlyName) == 0x20);

static_assert(sizeof(DIFILEEFFECT) == 296);

typedef DIFILEEFFECT * LPDIFILEEFFECT;
typedef const DIFILEEFFECT * LPCDIFILEEFFECT;

static_assert(TypeMatch<LPDIFILEEFFECT, DIFILEEFFECT *>::value);
static_assert(TypeMatch<LPCDIFILEEFFECT, const DIFILEEFFECT *>::value);

static_assert(sizeof(LPDIFILEEFFECT) == 8);
static_assert(sizeof(LPCDIFILEEFFECT) == 8);

// DIEFFESCAPE

struct DIEFFESCAPE
{
	DWORD dwSize; // 0
	DWORD dwCommand; // 4
	LPVOID lpvInBuffer; // 8
	DWORD cbInBuffer; // 0x10
	_(4);
	LPVOID lpvOutBuffer; // 0x18
	DWORD cbOutBuffer; // 0x20
	_(4);
};

static_assert(TypeMatch<decltype(DIEFFESCAPE::dwSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIEFFESCAPE::dwCommand), DWORD>::value);
static_assert(TypeMatch<decltype(DIEFFESCAPE::lpvInBuffer), LPVOID>::value);
static_assert(TypeMatch<decltype(DIEFFESCAPE::cbInBuffer), DWORD>::value);
static_assert(TypeMatch<decltype(DIEFFESCAPE::lpvOutBuffer), LPVOID>::value);
static_assert(TypeMatch<decltype(DIEFFESCAPE::cbOutBuffer), DWORD>::value);

static_assert(offsetof(DIEFFESCAPE, dwSize) == 0);
static_assert(offsetof(DIEFFESCAPE, dwCommand) == 4);
static_assert(offsetof(DIEFFESCAPE, lpvInBuffer) == 8);
static_assert(offsetof(DIEFFESCAPE, cbInBuffer) == 0x10);
static_assert(offsetof(DIEFFESCAPE, lpvOutBuffer) == 0x18);
static_assert(offsetof(DIEFFESCAPE, cbOutBuffer) == 0x20);

static_assert(sizeof(DIEFFESCAPE) == 40);

typedef DIEFFESCAPE * LPDIEFFESCAPE;

static_assert(TypeMatch<LPDIEFFESCAPE, DIEFFESCAPE *>::value);

static_assert(sizeof(LPDIEFFESCAPE) == 8);

// DIEFFECTINFOA

struct DIEFFECTINFOA
{
	DWORD dwSize; // 0
	GUID guid; // 4
	DWORD dwEffType; // 0x14
	DWORD dwStaticParams; // 0x18
	DWORD dwDynamicParams; // 0x1C
	CHAR tszName[260]; // 0x20
};

static_assert(TypeMatch<decltype(DIEFFECTINFOA::dwSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIEFFECTINFOA::guid), GUID>::value);
static_assert(TypeMatch<decltype(DIEFFECTINFOA::dwEffType), DWORD>::value);
static_assert(TypeMatch<decltype(DIEFFECTINFOA::dwStaticParams), DWORD>::value);
static_assert(TypeMatch<decltype(DIEFFECTINFOA::dwDynamicParams), DWORD>::value);
static_assert(TypeMatch<decltype(DIEFFECTINFOA::tszName), CHAR[260]>::value);

static_assert(offsetof(DIEFFECTINFOA, dwSize) == 0);
static_assert(offsetof(DIEFFECTINFOA, guid) == 4);
static_assert(offsetof(DIEFFECTINFOA, dwEffType) == 0x14);
static_assert(offsetof(DIEFFECTINFOA, dwStaticParams) == 0x18);
static_assert(offsetof(DIEFFECTINFOA, dwDynamicParams) == 0x1C);
static_assert(offsetof(DIEFFECTINFOA, tszName) == 0x20);

static_assert(sizeof(DIEFFECTINFOA) == 292);

typedef DIEFFECTINFOA * LPDIEFFECTINFOA;
typedef const DIEFFECTINFOA * LPCDIEFFECTINFOA;

static_assert(TypeMatch<LPDIEFFECTINFOA, DIEFFECTINFOA *>::value);
static_assert(TypeMatch<LPCDIEFFECTINFOA, const DIEFFECTINFOA *>::value);

static_assert(sizeof(LPDIEFFECTINFOA) == 8);
static_assert(sizeof(LPCDIEFFECTINFOA) == 8);

// DIEFFECTINFOW

struct DIEFFECTINFOW
{
	DWORD dwSize; // 0
	GUID guid; // 4
	DWORD dwEffType; // 0x14
	DWORD dwStaticParams; // 0x18
	DWORD dwDynamicParams; // 0x1C
	WCHAR tszName[260]; // 0x20
};

static_assert(TypeMatch<decltype(DIEFFECTINFOW::dwSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIEFFECTINFOW::guid), GUID>::value);
static_assert(TypeMatch<decltype(DIEFFECTINFOW::dwEffType), DWORD>::value);
static_assert(TypeMatch<decltype(DIEFFECTINFOW::dwStaticParams), DWORD>::value);
static_assert(TypeMatch<decltype(DIEFFECTINFOW::dwDynamicParams), DWORD>::value);
static_assert(TypeMatch<decltype(DIEFFECTINFOW::tszName), WCHAR[260]>::value);

static_assert(offsetof(DIEFFECTINFOW, dwSize) == 0);
static_assert(offsetof(DIEFFECTINFOW, guid) == 4);
static_assert(offsetof(DIEFFECTINFOW, dwEffType) == 0x14);
static_assert(offsetof(DIEFFECTINFOW, dwStaticParams) == 0x18);
static_assert(offsetof(DIEFFECTINFOW, dwDynamicParams) == 0x1C);
static_assert(offsetof(DIEFFECTINFOW, tszName) == 0x20);

static_assert(sizeof(DIEFFECTINFOW) == 552);

typedef DIEFFECTINFOW * LPDIEFFECTINFOW;
typedef const DIEFFECTINFOW * LPCDIEFFECTINFOW;

static_assert(TypeMatch<LPDIEFFECTINFOW, DIEFFECTINFOW *>::value);
static_assert(TypeMatch<LPCDIEFFECTINFOW, const DIEFFECTINFOW *>::value);

static_assert(sizeof(LPDIEFFECTINFOW) == 8);
static_assert(sizeof(LPCDIEFFECTINFOW) == 8);

// DIACTIONA

struct DIACTIONA
{
	UINT_PTR uAppData; // 0
	DWORD dwSemantic; // 8
	DWORD dwFlags; // 0xC
	union
	{
		LPCSTR lptszActionName; // 0x10
		UINT uResIdString; // 0x10
	}; // 0x10
	GUID guidInstance; // 0x18
	DWORD dwObjID; // 0x28
	DWORD dwHow; // 0x2C
};

static_assert(TypeMatch<decltype(DIACTIONA::uAppData), UINT_PTR>::value);
static_assert(TypeMatch<decltype(DIACTIONA::dwSemantic), DWORD>::value);
static_assert(TypeMatch<decltype(DIACTIONA::dwFlags), DWORD>::value);
static_assert(TypeMatch<decltype(DIACTIONA::lptszActionName), LPCSTR>::value);
static_assert(TypeMatch<decltype(DIACTIONA::uResIdString), UINT>::value);
static_assert(TypeMatch<decltype(DIACTIONA::guidInstance), GUID>::value);
static_assert(TypeMatch<decltype(DIACTIONA::dwObjID), DWORD>::value);
static_assert(TypeMatch<decltype(DIACTIONA::dwHow), DWORD>::value);

static_assert(offsetof(DIACTIONA, uAppData) == 0);
static_assert(offsetof(DIACTIONA, dwSemantic) == 8);
static_assert(offsetof(DIACTIONA, dwFlags) == 0xC);
static_assert(offsetof(DIACTIONA, lptszActionName) == 0x10);
static_assert(offsetof(DIACTIONA, uResIdString) == 0x10);
static_assert(offsetof(DIACTIONA, guidInstance) == 0x18);
static_assert(offsetof(DIACTIONA, dwObjID) == 0x28);
static_assert(offsetof(DIACTIONA, dwHow) == 0x2C);

static_assert(sizeof(DIACTIONA) == 48);

typedef DIACTIONA * LPDIACTIONA;
typedef const DIACTIONA * LPCDIACTIONA;

static_assert(TypeMatch<LPDIACTIONA, DIACTIONA *>::value);
static_assert(TypeMatch<LPCDIACTIONA, const DIACTIONA *>::value);

static_assert(sizeof(LPDIACTIONA) == 8);
static_assert(sizeof(LPCDIACTIONA) == 8);

// DIACTIONW

struct DIACTIONW
{
	UINT_PTR uAppData; // 0
	DWORD dwSemantic; // 8
	DWORD dwFlags; // 0xC
	union
	{
		LPCWSTR lptszActionName; // 0x10
		UINT uResIdString; // 0x10
	}; // 0x10
	GUID guidInstance; // 0x18
	DWORD dwObjID; // 0x28
	DWORD dwHow; // 0x2C
};

static_assert(TypeMatch<decltype(DIACTIONW::uAppData), UINT_PTR>::value);
static_assert(TypeMatch<decltype(DIACTIONW::dwSemantic), DWORD>::value);
static_assert(TypeMatch<decltype(DIACTIONW::dwFlags), DWORD>::value);
static_assert(TypeMatch<decltype(DIACTIONW::lptszActionName), LPCWSTR>::value);
static_assert(TypeMatch<decltype(DIACTIONW::uResIdString), UINT>::value);
static_assert(TypeMatch<decltype(DIACTIONW::guidInstance), GUID>::value);
static_assert(TypeMatch<decltype(DIACTIONW::dwObjID), DWORD>::value);
static_assert(TypeMatch<decltype(DIACTIONW::dwHow), DWORD>::value);

static_assert(offsetof(DIACTIONW, uAppData) == 0);
static_assert(offsetof(DIACTIONW, dwSemantic) == 8);
static_assert(offsetof(DIACTIONW, dwFlags) == 0xC);
static_assert(offsetof(DIACTIONW, lptszActionName) == 0x10);
static_assert(offsetof(DIACTIONW, uResIdString) == 0x10);
static_assert(offsetof(DIACTIONW, guidInstance) == 0x18);
static_assert(offsetof(DIACTIONW, dwObjID) == 0x28);
static_assert(offsetof(DIACTIONW, dwHow) == 0x2C);

static_assert(sizeof(DIACTIONW) == 48);

typedef DIACTIONW * LPDIACTIONW;
typedef const DIACTIONW * LPCDIACTIONW;

static_assert(TypeMatch<LPDIACTIONW, DIACTIONW *>::value);
static_assert(TypeMatch<LPCDIACTIONW, const DIACTIONW *>::value);

static_assert(sizeof(LPDIACTIONW) == 8);
static_assert(sizeof(LPCDIACTIONW) == 8);

// DIACTIONFORMATA

struct DIACTIONFORMATA
{
	DWORD dwSize; // 0
	DWORD dwActionSize; // 4
	DWORD dwDataSize; // 8
	DWORD dwNumActions; // 0xC
	LPDIACTIONA rgoAction; // 0x10
	GUID guidActionMap; // 0x18
	DWORD dwGenre; // 0x28
	DWORD dwBufferSize; // 0x2C
	LONG lAxisMin; // 0x30
	LONG lAxisMax; // 0x34
	HINSTANCE hInstString; // 0x38
	FILETIME ftTimeStamp; // 0x40
	DWORD dwCRC; // 0x48
	CHAR tszActionMap[260]; // 0x4C
};

static_assert(TypeMatch<decltype(DIACTIONFORMATA::dwSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATA::dwActionSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATA::dwDataSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATA::dwNumActions), DWORD>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATA::rgoAction), LPDIACTIONA>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATA::guidActionMap), GUID>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATA::dwGenre), DWORD>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATA::dwBufferSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATA::lAxisMin), LONG>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATA::lAxisMax), LONG>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATA::hInstString), HINSTANCE>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATA::ftTimeStamp), FILETIME>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATA::dwCRC), DWORD>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATA::tszActionMap), CHAR[260]>::value);

static_assert(offsetof(DIACTIONFORMATA, dwSize) == 0);
static_assert(offsetof(DIACTIONFORMATA, dwActionSize) == 4);
static_assert(offsetof(DIACTIONFORMATA, dwDataSize) == 8);
static_assert(offsetof(DIACTIONFORMATA, dwNumActions) == 0xC);
static_assert(offsetof(DIACTIONFORMATA, rgoAction) == 0x10);
static_assert(offsetof(DIACTIONFORMATA, guidActionMap) == 0x18);
static_assert(offsetof(DIACTIONFORMATA, dwGenre) == 0x28);
static_assert(offsetof(DIACTIONFORMATA, dwBufferSize) == 0x2C);
static_assert(offsetof(DIACTIONFORMATA, lAxisMin) == 0x30);
static_assert(offsetof(DIACTIONFORMATA, lAxisMax) == 0x34);
static_assert(offsetof(DIACTIONFORMATA, hInstString) == 0x38);
static_assert(offsetof(DIACTIONFORMATA, ftTimeStamp) == 0x40);
static_assert(offsetof(DIACTIONFORMATA, dwCRC) == 0x48);
static_assert(offsetof(DIACTIONFORMATA, tszActionMap) == 0x4C);

static_assert(sizeof(DIACTIONFORMATA) == 336);

typedef DIACTIONFORMATA * LPDIACTIONFORMATA;
typedef const DIACTIONFORMATA * LPCDIACTIONFORMATA;

static_assert(TypeMatch<LPDIACTIONFORMATA, DIACTIONFORMATA *>::value);
static_assert(TypeMatch<LPCDIACTIONFORMATA, const DIACTIONFORMATA *>::value);

static_assert(sizeof(LPDIACTIONFORMATA) == 8);
static_assert(sizeof(LPCDIACTIONFORMATA) == 8);

// DIACTIONFORMATW

struct DIACTIONFORMATW
{
	DWORD dwSize; // 0
	DWORD dwActionSize; // 4
	DWORD dwDataSize; // 8
	DWORD dwNumActions; // 0xC
	LPDIACTIONW rgoAction; // 0x10
	GUID guidActionMap; // 0x18
	DWORD dwGenre; // 0x28
	DWORD dwBufferSize; // 0x2C
	LONG lAxisMin; // 0x30
	LONG lAxisMax; // 0x34
	HINSTANCE hInstString; // 0x38
	FILETIME ftTimeStamp; // 0x40
	DWORD dwCRC; // 0x48
	WCHAR tszActionMap[260]; // 0x4C
	_(4);
};

static_assert(TypeMatch<decltype(DIACTIONFORMATW::dwSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATW::dwActionSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATW::dwDataSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATW::dwNumActions), DWORD>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATW::rgoAction), LPDIACTIONW>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATW::guidActionMap), GUID>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATW::dwGenre), DWORD>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATW::dwBufferSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATW::lAxisMin), LONG>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATW::lAxisMax), LONG>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATW::hInstString), HINSTANCE>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATW::ftTimeStamp), FILETIME>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATW::dwCRC), DWORD>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATW::tszActionMap), WCHAR[260]>::value);

static_assert(offsetof(DIACTIONFORMATW, dwSize) == 0);
static_assert(offsetof(DIACTIONFORMATW, dwActionSize) == 4);
static_assert(offsetof(DIACTIONFORMATW, dwDataSize) == 8);
static_assert(offsetof(DIACTIONFORMATW, dwNumActions) == 0xC);
static_assert(offsetof(DIACTIONFORMATW, rgoAction) == 0x10);
static_assert(offsetof(DIACTIONFORMATW, guidActionMap) == 0x18);
static_assert(offsetof(DIACTIONFORMATW, dwGenre) == 0x28);
static_assert(offsetof(DIACTIONFORMATW, dwBufferSize) == 0x2C);
static_assert(offsetof(DIACTIONFORMATW, lAxisMin) == 0x30);
static_assert(offsetof(DIACTIONFORMATW, lAxisMax) == 0x34);
static_assert(offsetof(DIACTIONFORMATW, hInstString) == 0x38);
static_assert(offsetof(DIACTIONFORMATW, ftTimeStamp) == 0x40);
static_assert(offsetof(DIACTIONFORMATW, dwCRC) == 0x48);
static_assert(offsetof(DIACTIONFORMATW, tszActionMap) == 0x4C);

static_assert(sizeof(DIACTIONFORMATW) == 600);

typedef DIACTIONFORMATW * LPDIACTIONFORMATW;
typedef const DIACTIONFORMATW * LPCDIACTIONFORMATW;

static_assert(TypeMatch<LPDIACTIONFORMATW, DIACTIONFORMATW *>::value);
static_assert(TypeMatch<LPCDIACTIONFORMATW, const DIACTIONFORMATW *>::value);

static_assert(sizeof(LPDIACTIONFORMATW) == 8);
static_assert(sizeof(LPCDIACTIONFORMATW) == 8);

// DIDEVICEIMAGEINFOA

struct DIDEVICEIMAGEINFOA
{
	CHAR tszImagePath[260]; // 0
	DWORD dwFlags; // 0x104
	DWORD dwViewID; // 0x108
	RECT rcOverlay; // 0x10C
	DWORD dwObjID; // 0x11C
	DWORD dwcValidPts; // 0x120
	POINT rgptCalloutLine[5]; // 0x124
	RECT rcCalloutRect; // 0x14C
	DWORD dwTextAlign; // 0x15C
};

static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOA::tszImagePath), CHAR[260]>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOA::dwFlags), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOA::dwViewID), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOA::rcOverlay), RECT>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOA::dwObjID), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOA::dwcValidPts), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOA::rgptCalloutLine), POINT[5]>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOA::rcCalloutRect), RECT>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOA::dwTextAlign), DWORD>::value);

static_assert(offsetof(DIDEVICEIMAGEINFOA, tszImagePath) == 0);
static_assert(offsetof(DIDEVICEIMAGEINFOA, dwFlags) == 0x104);
static_assert(offsetof(DIDEVICEIMAGEINFOA, dwViewID) == 0x108);
static_assert(offsetof(DIDEVICEIMAGEINFOA, rcOverlay) == 0x10C);
static_assert(offsetof(DIDEVICEIMAGEINFOA, dwObjID) == 0x11C);
static_assert(offsetof(DIDEVICEIMAGEINFOA, dwcValidPts) == 0x120);
static_assert(offsetof(DIDEVICEIMAGEINFOA, rgptCalloutLine) == 0x124);
static_assert(offsetof(DIDEVICEIMAGEINFOA, rcCalloutRect) == 0x14C);
static_assert(offsetof(DIDEVICEIMAGEINFOA, dwTextAlign) == 0x15C);

static_assert(sizeof(DIDEVICEIMAGEINFOA) == 352);

typedef DIDEVICEIMAGEINFOA * LPDIDEVICEIMAGEINFOA;
typedef const DIDEVICEIMAGEINFOA * LPCDIDEVICEIMAGEINFOA;

static_assert(TypeMatch<LPDIDEVICEIMAGEINFOA, DIDEVICEIMAGEINFOA *>::value);
static_assert(TypeMatch<LPCDIDEVICEIMAGEINFOA, const DIDEVICEIMAGEINFOA *>::value);

static_assert(sizeof(LPDIDEVICEIMAGEINFOA) == 8);
static_assert(sizeof(LPCDIDEVICEIMAGEINFOA) == 8);

// DIDEVICEIMAGEINFOW

struct DIDEVICEIMAGEINFOW
{
	WCHAR tszImagePath[260]; // 0
	DWORD dwFlags; // 0x208
	DWORD dwViewID; // 0x20C
	RECT rcOverlay; // 0x210
	DWORD dwObjID; // 0x220
	DWORD dwcValidPts; // 0x224
	POINT rgptCalloutLine[5]; // 0x228
	RECT rcCalloutRect; // 0x250
	DWORD dwTextAlign; // 0x260
};

static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOW::tszImagePath), WCHAR[260]>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOW::dwFlags), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOW::dwViewID), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOW::rcOverlay), RECT>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOW::dwObjID), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOW::dwcValidPts), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOW::rgptCalloutLine), POINT[5]>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOW::rcCalloutRect), RECT>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOW::dwTextAlign), DWORD>::value);

static_assert(offsetof(DIDEVICEIMAGEINFOW, tszImagePath) == 0);
static_assert(offsetof(DIDEVICEIMAGEINFOW, dwFlags) == 0x208);
static_assert(offsetof(DIDEVICEIMAGEINFOW, dwViewID) == 0x20C);
static_assert(offsetof(DIDEVICEIMAGEINFOW, rcOverlay) == 0x210);
static_assert(offsetof(DIDEVICEIMAGEINFOW, dwObjID) == 0x220);
static_assert(offsetof(DIDEVICEIMAGEINFOW, dwcValidPts) == 0x224);
static_assert(offsetof(DIDEVICEIMAGEINFOW, rgptCalloutLine) == 0x228);
static_assert(offsetof(DIDEVICEIMAGEINFOW, rcCalloutRect) == 0x250);
static_assert(offsetof(DIDEVICEIMAGEINFOW, dwTextAlign) == 0x260);

static_assert(sizeof(DIDEVICEIMAGEINFOW) == 612);

typedef DIDEVICEIMAGEINFOW * LPDIDEVICEIMAGEINFOW;
typedef const DIDEVICEIMAGEINFOW * LPCDIDEVICEIMAGEINFOW;

static_assert(TypeMatch<LPDIDEVICEIMAGEINFOW, DIDEVICEIMAGEINFOW *>::value);
static_assert(TypeMatch<LPCDIDEVICEIMAGEINFOW, const DIDEVICEIMAGEINFOW *>::value);

static_assert(sizeof(LPDIDEVICEIMAGEINFOW) == 8);
static_assert(sizeof(LPCDIDEVICEIMAGEINFOW) == 8);

// DIDEVICEIMAGEINFOHEADERA

struct DIDEVICEIMAGEINFOHEADERA
{
	DWORD dwSize; // 0
	DWORD dwSizeImageInfo; // 4
	DWORD dwcViews; // 8
	DWORD dwcButtons; // 0xC
	DWORD dwcAxes; // 0x10
	DWORD dwcPOVs; // 0x14
	DWORD dwBufferSize; // 0x18
	DWORD dwBufferUsed; // 0x1C
	LPDIDEVICEIMAGEINFOA lprgImageInfoArray; // 0x20
};

static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOHEADERA::dwSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOHEADERA::dwSizeImageInfo), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOHEADERA::dwcViews), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOHEADERA::dwcButtons), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOHEADERA::dwcAxes), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOHEADERA::dwcPOVs), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOHEADERA::dwBufferSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOHEADERA::dwBufferUsed), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOHEADERA::lprgImageInfoArray), LPDIDEVICEIMAGEINFOA>::value);

static_assert(offsetof(DIDEVICEIMAGEINFOHEADERA, dwSize) == 0);
static_assert(offsetof(DIDEVICEIMAGEINFOHEADERA, dwSizeImageInfo) == 4);
static_assert(offsetof(DIDEVICEIMAGEINFOHEADERA, dwcViews) == 8);
static_assert(offsetof(DIDEVICEIMAGEINFOHEADERA, dwcButtons) == 0xC);
static_assert(offsetof(DIDEVICEIMAGEINFOHEADERA, dwcAxes) == 0x10);
static_assert(offsetof(DIDEVICEIMAGEINFOHEADERA, dwcPOVs) == 0x14);
static_assert(offsetof(DIDEVICEIMAGEINFOHEADERA, dwBufferSize) == 0x18);
static_assert(offsetof(DIDEVICEIMAGEINFOHEADERA, dwBufferUsed) == 0x1C);
static_assert(offsetof(DIDEVICEIMAGEINFOHEADERA, lprgImageInfoArray) == 0x20);

static_assert(sizeof(DIDEVICEIMAGEINFOHEADERA) == 40);

typedef DIDEVICEIMAGEINFOHEADERA * LPDIDEVICEIMAGEINFOHEADERA;
typedef const DIDEVICEIMAGEINFOHEADERA * LPCDIDEVICEIMAGEINFOHEADERA;

static_assert(TypeMatch<LPDIDEVICEIMAGEINFOHEADERA, DIDEVICEIMAGEINFOHEADERA *>::value);
static_assert(TypeMatch<LPCDIDEVICEIMAGEINFOHEADERA, const DIDEVICEIMAGEINFOHEADERA *>::value);

static_assert(sizeof(LPDIDEVICEIMAGEINFOHEADERA) == 8);
static_assert(sizeof(LPCDIDEVICEIMAGEINFOHEADERA) == 8);

// DIDEVICEIMAGEINFOHEADERW

struct DIDEVICEIMAGEINFOHEADERW
{
	DWORD dwSize; // 0
	DWORD dwSizeImageInfo; // 4
	DWORD dwcViews; // 8
	DWORD dwcButtons; // 0xC
	DWORD dwcAxes; // 0x10
	DWORD dwcPOVs; // 0x14
	DWORD dwBufferSize; // 0x18
	DWORD dwBufferUsed; // 0x1C
	LPDIDEVICEIMAGEINFOW lprgImageInfoArray; // 0x20
};

static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOHEADERW::dwSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOHEADERW::dwSizeImageInfo), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOHEADERW::dwcViews), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOHEADERW::dwcButtons), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOHEADERW::dwcAxes), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOHEADERW::dwcPOVs), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOHEADERW::dwBufferSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOHEADERW::dwBufferUsed), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOHEADERW::lprgImageInfoArray), LPDIDEVICEIMAGEINFOW>::value);

static_assert(offsetof(DIDEVICEIMAGEINFOHEADERW, dwSize) == 0);
static_assert(offsetof(DIDEVICEIMAGEINFOHEADERW, dwSizeImageInfo) == 4);
static_assert(offsetof(DIDEVICEIMAGEINFOHEADERW, dwcViews) == 8);
static_assert(offsetof(DIDEVICEIMAGEINFOHEADERW, dwcButtons) == 0xC);
static_assert(offsetof(DIDEVICEIMAGEINFOHEADERW, dwcAxes) == 0x10);
static_assert(offsetof(DIDEVICEIMAGEINFOHEADERW, dwcPOVs) == 0x14);
static_assert(offsetof(DIDEVICEIMAGEINFOHEADERW, dwBufferSize) == 0x18);
static_assert(offsetof(DIDEVICEIMAGEINFOHEADERW, dwBufferUsed) == 0x1C);
static_assert(offsetof(DIDEVICEIMAGEINFOHEADERW, lprgImageInfoArray) == 0x20);

static_assert(sizeof(DIDEVICEIMAGEINFOHEADERW) == 40);

typedef DIDEVICEIMAGEINFOHEADERW * LPDIDEVICEIMAGEINFOHEADERW;
typedef const DIDEVICEIMAGEINFOHEADERW * LPCDIDEVICEIMAGEINFOHEADERW;

static_assert(TypeMatch<LPDIDEVICEIMAGEINFOHEADERW, DIDEVICEIMAGEINFOHEADERW *>::value);
static_assert(TypeMatch<LPCDIDEVICEIMAGEINFOHEADERW, const DIDEVICEIMAGEINFOHEADERW *>::value);

static_assert(sizeof(LPDIDEVICEIMAGEINFOHEADERW) == 8);
static_assert(sizeof(LPCDIDEVICEIMAGEINFOHEADERW) == 8);

// DICOLORSET

struct DICOLORSET
{
	DWORD dwSize; // 0
	D3DCOLOR cTextFore; // 4
	D3DCOLOR cTextHighlight; // 8
	D3DCOLOR cCalloutLine; // 0xC
	D3DCOLOR cCalloutHighlight; // 0x10
	D3DCOLOR cBorder; // 0x14
	D3DCOLOR cControlFill; // 0x18
	D3DCOLOR cHighlightFill; // 0x1C
	D3DCOLOR cAreaFill; // 0x20
};

static_assert(TypeMatch<decltype(DICOLORSET::dwSize), DWORD>::value);
static_assert(TypeMatch<decltype(DICOLORSET::cTextFore), D3DCOLOR>::value);
static_assert(TypeMatch<decltype(DICOLORSET::cTextHighlight), D3DCOLOR>::value);
static_assert(TypeMatch<decltype(DICOLORSET::cCalloutLine), D3DCOLOR>::value);
static_assert(TypeMatch<decltype(DICOLORSET::cCalloutHighlight), D3DCOLOR>::value);
static_assert(TypeMatch<decltype(DICOLORSET::cBorder), D3DCOLOR>::value);
static_assert(TypeMatch<decltype(DICOLORSET::cControlFill), D3DCOLOR>::value);
static_assert(TypeMatch<decltype(DICOLORSET::cHighlightFill), D3DCOLOR>::value);
static_assert(TypeMatch<decltype(DICOLORSET::cAreaFill), D3DCOLOR>::value);

static_assert(offsetof(DICOLORSET, dwSize) == 0);
static_assert(offsetof(DICOLORSET, cTextFore) == 4);
static_assert(offsetof(DICOLORSET, cTextHighlight) == 8);
static_assert(offsetof(DICOLORSET, cCalloutLine) == 0xC);
static_assert(offsetof(DICOLORSET, cCalloutHighlight) == 0x10);
static_assert(offsetof(DICOLORSET, cBorder) == 0x14);
static_assert(offsetof(DICOLORSET, cControlFill) == 0x18);
static_assert(offsetof(DICOLORSET, cHighlightFill) == 0x1C);
static_assert(offsetof(DICOLORSET, cAreaFill) == 0x20);

static_assert(sizeof(DICOLORSET) == 36);

typedef DICOLORSET * LPDICOLORSET;
typedef const DICOLORSET * LPCDICOLORSET;

static_assert(TypeMatch<LPDICOLORSET, DICOLORSET *>::value);
static_assert(TypeMatch<LPCDICOLORSET, const DICOLORSET *>::value);

static_assert(sizeof(LPDICOLORSET) == 8);
static_assert(sizeof(LPCDICOLORSET) == 8);

// DICONFIGUREDEVICESPARAMSA

struct DICONFIGUREDEVICESPARAMSA
{
	DWORD dwSize; // 0
	DWORD dwcUsers; // 4
	LPSTR lptszUserNames; // 8
	DWORD dwcFormats; // 0x10
	_(4);
	LPDIACTIONFORMATA lprgFormats; // 0x18
	HWND hwnd; // 0x20
	DICOLORSET dics; // 0x28
	_(4);
	IUnknown* lpUnkDDSTarget; // 0x50
};

static_assert(TypeMatch<decltype(DICONFIGUREDEVICESPARAMSA::dwSize), DWORD>::value);
static_assert(TypeMatch<decltype(DICONFIGUREDEVICESPARAMSA::dwcUsers), DWORD>::value);
static_assert(TypeMatch<decltype(DICONFIGUREDEVICESPARAMSA::lptszUserNames), LPSTR>::value);
static_assert(TypeMatch<decltype(DICONFIGUREDEVICESPARAMSA::dwcFormats), DWORD>::value);
static_assert(TypeMatch<decltype(DICONFIGUREDEVICESPARAMSA::lprgFormats), LPDIACTIONFORMATA>::value);
static_assert(TypeMatch<decltype(DICONFIGUREDEVICESPARAMSA::hwnd), HWND>::value);
static_assert(TypeMatch<decltype(DICONFIGUREDEVICESPARAMSA::dics), DICOLORSET>::value);
static_assert(TypeMatch<decltype(DICONFIGUREDEVICESPARAMSA::lpUnkDDSTarget), IUnknown*>::value);

static_assert(offsetof(DICONFIGUREDEVICESPARAMSA, dwSize) == 0);
static_assert(offsetof(DICONFIGUREDEVICESPARAMSA, dwcUsers) == 4);
static_assert(offsetof(DICONFIGUREDEVICESPARAMSA, lptszUserNames) == 8);
static_assert(offsetof(DICONFIGUREDEVICESPARAMSA, dwcFormats) == 0x10);
static_assert(offsetof(DICONFIGUREDEVICESPARAMSA, lprgFormats) == 0x18);
static_assert(offsetof(DICONFIGUREDEVICESPARAMSA, hwnd) == 0x20);
static_assert(offsetof(DICONFIGUREDEVICESPARAMSA, dics) == 0x28);
static_assert(offsetof(DICONFIGUREDEVICESPARAMSA, lpUnkDDSTarget) == 0x50);

static_assert(sizeof(DICONFIGUREDEVICESPARAMSA) == 88);

typedef DICONFIGUREDEVICESPARAMSA * LPDICONFIGUREDEVICESPARAMSA;
typedef const DICONFIGUREDEVICESPARAMSA * LPCDICONFIGUREDEVICESPARAMSA;

static_assert(TypeMatch<LPDICONFIGUREDEVICESPARAMSA, DICONFIGUREDEVICESPARAMSA *>::value);
static_assert(TypeMatch<LPCDICONFIGUREDEVICESPARAMSA, const DICONFIGUREDEVICESPARAMSA *>::value);

static_assert(sizeof(LPDICONFIGUREDEVICESPARAMSA) == 8);
static_assert(sizeof(LPCDICONFIGUREDEVICESPARAMSA) == 8);

// DICONFIGUREDEVICESPARAMSW

struct DICONFIGUREDEVICESPARAMSW
{
	DWORD dwSize; // 0
	DWORD dwcUsers; // 4
	LPWSTR lptszUserNames; // 8
	DWORD dwcFormats; // 0x10
	_(4);
	LPDIACTIONFORMATW lprgFormats; // 0x18
	HWND hwnd; // 0x20
	DICOLORSET dics; // 0x28
	_(4);
	IUnknown* lpUnkDDSTarget; // 0x50
};

static_assert(TypeMatch<decltype(DICONFIGUREDEVICESPARAMSW::dwSize), DWORD>::value);
static_assert(TypeMatch<decltype(DICONFIGUREDEVICESPARAMSW::dwcUsers), DWORD>::value);
static_assert(TypeMatch<decltype(DICONFIGUREDEVICESPARAMSW::lptszUserNames), LPWSTR>::value);
static_assert(TypeMatch<decltype(DICONFIGUREDEVICESPARAMSW::dwcFormats), DWORD>::value);
static_assert(TypeMatch<decltype(DICONFIGUREDEVICESPARAMSW::lprgFormats), LPDIACTIONFORMATW>::value);
static_assert(TypeMatch<decltype(DICONFIGUREDEVICESPARAMSW::hwnd), HWND>::value);
static_assert(TypeMatch<decltype(DICONFIGUREDEVICESPARAMSW::dics), DICOLORSET>::value);
static_assert(TypeMatch<decltype(DICONFIGUREDEVICESPARAMSW::lpUnkDDSTarget), IUnknown*>::value);

static_assert(offsetof(DICONFIGUREDEVICESPARAMSW, dwSize) == 0);
static_assert(offsetof(DICONFIGUREDEVICESPARAMSW, dwcUsers) == 4);
static_assert(offsetof(DICONFIGUREDEVICESPARAMSW, lptszUserNames) == 8);
static_assert(offsetof(DICONFIGUREDEVICESPARAMSW, dwcFormats) == 0x10);
static_assert(offsetof(DICONFIGUREDEVICESPARAMSW, lprgFormats) == 0x18);
static_assert(offsetof(DICONFIGUREDEVICESPARAMSW, hwnd) == 0x20);
static_assert(offsetof(DICONFIGUREDEVICESPARAMSW, dics) == 0x28);
static_assert(offsetof(DICONFIGUREDEVICESPARAMSW, lpUnkDDSTarget) == 0x50);

static_assert(sizeof(DICONFIGUREDEVICESPARAMSW) == 88);

typedef DICONFIGUREDEVICESPARAMSW * LPDICONFIGUREDEVICESPARAMSW;
typedef const DICONFIGUREDEVICESPARAMSW * LPCDICONFIGUREDEVICESPARAMSW;

static_assert(TypeMatch<LPDICONFIGUREDEVICESPARAMSW, DICONFIGUREDEVICESPARAMSW *>::value);
static_assert(TypeMatch<LPCDICONFIGUREDEVICESPARAMSW, const DICONFIGUREDEVICESPARAMSW *>::value);

static_assert(sizeof(LPDICONFIGUREDEVICESPARAMSW) == 8);
static_assert(sizeof(LPCDICONFIGUREDEVICESPARAMSW) == 8);

// DIJOYSTATE

struct DIJOYSTATE
{
	LONG lX; // 0
	LONG lY; // 4
	LONG lZ; // 8
	LONG lRx; // 0xC
	LONG lRy; // 0x10
	LONG lRz; // 0x14
	LONG rglSlider[2]; // 0x18
	DWORD rgdwPOV[4]; // 0x20
	BYTE rgbButtons[32]; // 0x30
};

static_assert(TypeMatch<decltype(DIJOYSTATE::lX), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE::lY), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE::lZ), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE::lRx), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE::lRy), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE::lRz), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE::rglSlider), LONG[2]>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE::rgdwPOV), DWORD[4]>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE::rgbButtons), BYTE[32]>::value);

static_assert(offsetof(DIJOYSTATE, lX) == 0);
static_assert(offsetof(DIJOYSTATE, lY) == 4);
static_assert(offsetof(DIJOYSTATE, lZ) == 8);
static_assert(offsetof(DIJOYSTATE, lRx) == 0xC);
static_assert(offsetof(DIJOYSTATE, lRy) == 0x10);
static_assert(offsetof(DIJOYSTATE, lRz) == 0x14);
static_assert(offsetof(DIJOYSTATE, rglSlider) == 0x18);
static_assert(offsetof(DIJOYSTATE, rgdwPOV) == 0x20);
static_assert(offsetof(DIJOYSTATE, rgbButtons) == 0x30);

static_assert(sizeof(DIJOYSTATE) == 80);

typedef DIJOYSTATE * LPDIJOYSTATE;

static_assert(TypeMatch<LPDIJOYSTATE, DIJOYSTATE *>::value);

static_assert(sizeof(LPDIJOYSTATE) == 8);

// DIJOYSTATE2

struct DIJOYSTATE2
{
	LONG lX; // 0
	LONG lY; // 4
	LONG lZ; // 8
	LONG lRx; // 0xC
	LONG lRy; // 0x10
	LONG lRz; // 0x14
	LONG rglSlider[2]; // 0x18
	DWORD rgdwPOV[4]; // 0x20
	BYTE rgbButtons[128]; // 0x30
	LONG lVX; // 0xB0
	LONG lVY; // 0xB4
	LONG lVZ; // 0xB8
	LONG lVRx; // 0xBC
	LONG lVRy; // 0xC0
	LONG lVRz; // 0xC4
	LONG rglVSlider[2]; // 0xC8
	LONG lAX; // 0xD0
	LONG lAY; // 0xD4
	LONG lAZ; // 0xD8
	LONG lARx; // 0xDC
	LONG lARy; // 0xE0
	LONG lARz; // 0xE4
	LONG rglASlider[2]; // 0xE8
	LONG lFX; // 0xF0
	LONG lFY; // 0xF4
	LONG lFZ; // 0xF8
	LONG lFRx; // 0xFC
	LONG lFRy; // 0x100
	LONG lFRz; // 0x104
	LONG rglFSlider[2]; // 0x108
};

static_assert(TypeMatch<decltype(DIJOYSTATE2::lX), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lY), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lZ), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lRx), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lRy), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lRz), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::rglSlider), LONG[2]>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::rgdwPOV), DWORD[4]>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::rgbButtons), BYTE[128]>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lVX), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lVY), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lVZ), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lVRx), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lVRy), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lVRz), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::rglVSlider), LONG[2]>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lAX), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lAY), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lAZ), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lARx), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lARy), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lARz), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::rglASlider), LONG[2]>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lFX), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lFY), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lFZ), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lFRx), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lFRy), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lFRz), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::rglFSlider), LONG[2]>::value);

static_assert(offsetof(DIJOYSTATE2, lX) == 0);
static_assert(offsetof(DIJOYSTATE2, lY) == 4);
static_assert(offsetof(DIJOYSTATE2, lZ) == 8);
static_assert(offsetof(DIJOYSTATE2, lRx) == 0xC);
static_assert(offsetof(DIJOYSTATE2, lRy) == 0x10);
static_assert(offsetof(DIJOYSTATE2, lRz) == 0x14);
static_assert(offsetof(DIJOYSTATE2, rglSlider) == 0x18);
static_assert(offsetof(DIJOYSTATE2, rgdwPOV) == 0x20);
static_assert(offsetof(DIJOYSTATE2, rgbButtons) == 0x30);
static_assert(offsetof(DIJOYSTATE2, lVX) == 0xB0);
static_assert(offsetof(DIJOYSTATE2, lVY) == 0xB4);
static_assert(offsetof(DIJOYSTATE2, lVZ) == 0xB8);
static_assert(offsetof(DIJOYSTATE2, lVRx) == 0xBC);
static_assert(offsetof(DIJOYSTATE2, lVRy) == 0xC0);
static_assert(offsetof(DIJOYSTATE2, lVRz) == 0xC4);
static_assert(offsetof(DIJOYSTATE2, rglVSlider) == 0xC8);
static_assert(offsetof(DIJOYSTATE2, lAX) == 0xD0);
static_assert(offsetof(DIJOYSTATE2, lAY) == 0xD4);
static_assert(offsetof(DIJOYSTATE2, lAZ) == 0xD8);
static_assert(offsetof(DIJOYSTATE2, lARx) == 0xDC);
static_assert(offsetof(DIJOYSTATE2, lARy) == 0xE0);
static_assert(offsetof(DIJOYSTATE2, lARz) == 0xE4);
static_assert(offsetof(DIJOYSTATE2, rglASlider) == 0xE8);
static_assert(offsetof(DIJOYSTATE2, lFX) == 0xF0);
static_assert(offsetof(DIJOYSTATE2, lFY) == 0xF4);
static_assert(offsetof(DIJOYSTATE2, lFZ) == 0xF8);
static_assert(offsetof(DIJOYSTATE2, lFRx) == 0xFC);
static_assert(offsetof(DIJOYSTATE2, lFRy) == 0x100);
static_assert(offsetof(DIJOYSTATE2, lFRz) == 0x104);
static_assert(offsetof(DIJOYSTATE2, rglFSlider) == 0x108);

static_assert(sizeof(DIJOYSTATE2) == 272);

typedef DIJOYSTATE2 * LPDIJOYSTATE2;

static_assert(TypeMatch<LPDIJOYSTATE2, DIJOYSTATE2 *>::value);

static_assert(sizeof(LPDIJOYSTATE2) == 8);

#pragma pack(pop)

extern "C" const DIDATAFORMAT c_dfDIMouse;
extern "C" const DIDATAFORMAT c_dfDIMouse2;
extern "C" const DIDATAFORMAT c_dfDIKeyboard;
extern "C" const DIDATAFORMAT c_dfDIJoystick;
extern "C" const DIDATAFORMAT c_dfDIJoystick2;

// LPDIENUMDEVICESCALLBACKA

typedef BOOL(* LPDIENUMDEVICESCALLBACKA)
(
	LPCDIDEVICEINSTANCEA,
	LPVOID
);

static_assert(sizeof(LPDIENUMDEVICESCALLBACKA) == 8);

// LPDIENUMDEVICESCALLBACKW

typedef BOOL(* LPDIENUMDEVICESCALLBACKW)
(
	LPCDIDEVICEINSTANCEW,
	LPVOID
);

static_assert(sizeof(LPDIENUMDEVICESCALLBACKW) == 8);

// LPDICONFIGUREDEVICESCALLBACK

typedef BOOL(* LPDICONFIGUREDEVICESCALLBACK)
(
	IUnknown*,
	LPVOID
);

static_assert(sizeof(LPDICONFIGUREDEVICESCALLBACK) == 8);

// LPDIENUMDEVICESBYSEMANTICSCBA

typedef BOOL(* LPDIENUMDEVICESBYSEMANTICSCBA)
(
	LPCDIDEVICEINSTANCEA,
	LPDIRECTINPUTDEVICE8A,
	DWORD,
	DWORD,
	LPVOID
);

static_assert(sizeof(LPDIENUMDEVICESBYSEMANTICSCBA) == 8);

// LPDIENUMDEVICESBYSEMANTICSCBW

typedef BOOL(* LPDIENUMDEVICESBYSEMANTICSCBW)
(
	LPCDIDEVICEINSTANCEW,
	LPDIRECTINPUTDEVICE8W,
	DWORD,
	DWORD,
	LPVOID
);

static_assert(sizeof(LPDIENUMDEVICESBYSEMANTICSCBW) == 8);

// LPDIENUMDEVICEOBJECTSCALLBACKA

typedef BOOL(* LPDIENUMDEVICEOBJECTSCALLBACKA)
(
	LPCDIDEVICEOBJECTINSTANCEA,
	LPVOID
);

static_assert(sizeof(LPDIENUMDEVICEOBJECTSCALLBACKA) == 8);

// LPDIENUMDEVICEOBJECTSCALLBACKW

typedef BOOL(* LPDIENUMDEVICEOBJECTSCALLBACKW)
(
	LPCDIDEVICEOBJECTINSTANCEW,
	LPVOID
);

static_assert(sizeof(LPDIENUMDEVICEOBJECTSCALLBACKW) == 8);

// LPDIENUMEFFECTSCALLBACKA

typedef BOOL(* LPDIENUMEFFECTSCALLBACKA)
(
	LPCDIEFFECTINFOA,
	LPVOID
);

static_assert(sizeof(LPDIENUMEFFECTSCALLBACKA) == 8);

// LPDIENUMEFFECTSCALLBACKW

typedef BOOL(* LPDIENUMEFFECTSCALLBACKW)
(
	LPCDIEFFECTINFOW,
	LPVOID
);

static_assert(sizeof(LPDIENUMEFFECTSCALLBACKW) == 8);

// LPDIENUMCREATEDEFFECTOBJECTSCALLBACK

typedef BOOL(* LPDIENUMCREATEDEFFECTOBJECTSCALLBACK)
(
	LPDIRECTINPUTEFFECT,
	LPVOID
);

static_assert(sizeof(LPDIENUMCREATEDEFFECTOBJECTSCALLBACK) == 8);

// LPDIENUMEFFECTSINFILECALLBACK

typedef BOOL(* LPDIENUMEFFECTSINFILECALLBACK)
(
	LPCDIFILEEFFECT,
	LPVOID
);

static_assert(sizeof(LPDIENUMEFFECTSINFILECALLBACK) == 8);

// IDirectInput8A

struct __declspec(novtable) IDirectInput8A : IUnknown
{
	virtual HRESULT CreateDevice
	(
		const GUID&,
		LPDIRECTINPUTDEVICE8A*,
		LPUNKNOWN
	) = 0;
	virtual HRESULT EnumDevices
	(
		DWORD,
		LPDIENUMDEVICESCALLBACKA,
		LPVOID,
		DWORD
	) = 0;
	virtual HRESULT GetDeviceStatus(const GUID&) = 0;
	virtual HRESULT RunControlPanel
	(
		HWND,
		DWORD
	) = 0;
	virtual HRESULT Initialize
	(
		HINSTANCE,
		DWORD
	) = 0;
	virtual HRESULT FindDevice
	(
		const GUID&,
		LPCSTR,
		LPGUID
	) = 0;
	virtual HRESULT EnumDevicesBySemantics
	(
		LPCSTR,
		LPDIACTIONFORMATA,
		LPDIENUMDEVICESBYSEMANTICSCBA,
		LPVOID,
		DWORD
	) = 0;
	virtual HRESULT ConfigureDevices
	(
		LPDICONFIGUREDEVICESCALLBACK,
		LPDICONFIGUREDEVICESPARAMSA,
		DWORD,
		LPVOID
	) = 0;
};

static_assert(sizeof(IDirectInput8A) == 8);

// IDirectInput8W

struct __declspec(novtable) IDirectInput8W : IUnknown
{
	virtual HRESULT CreateDevice
	(
		const GUID&,
		LPDIRECTINPUTDEVICE8W*,
		LPUNKNOWN
	) = 0;
	virtual HRESULT EnumDevices
	(
		DWORD,
		LPDIENUMDEVICESCALLBACKW,
		LPVOID,
		DWORD
	) = 0;
	virtual HRESULT GetDeviceStatus(const GUID&) = 0;
	virtual HRESULT RunControlPanel
	(
		HWND,
		DWORD
	) = 0;
	virtual HRESULT Initialize
	(
		HINSTANCE,
		DWORD
	) = 0;
	virtual HRESULT FindDevice
	(
		const GUID&,
		LPCWSTR,
		LPGUID
	) = 0;
	virtual HRESULT EnumDevicesBySemantics
	(
		LPCWSTR,
		LPDIACTIONFORMATW,
		LPDIENUMDEVICESBYSEMANTICSCBW,
		LPVOID,
		DWORD
	) = 0;
	virtual HRESULT ConfigureDevices
	(
		LPDICONFIGUREDEVICESCALLBACK,
		LPDICONFIGUREDEVICESPARAMSW,
		DWORD,
		LPVOID
	) = 0;
};

static_assert(sizeof(IDirectInput8W) == 8);

// IDirectInputDevice8A

struct __declspec(novtable) IDirectInputDevice8A : IUnknown
{
	virtual HRESULT GetCapabilities(LPDIDEVCAPS) = 0;
	virtual HRESULT EnumObjects
	(
		LPDIENUMDEVICEOBJECTSCALLBACKA,
		LPVOID,
		DWORD
	) = 0;
	virtual HRESULT GetProperty
	(
		const GUID&,
		LPDIPROPHEADER
	) = 0;
	virtual HRESULT SetProperty
	(
		const GUID&,
		LPCDIPROPHEADER
	) = 0;
	virtual HRESULT Acquire() = 0;
	virtual HRESULT Unacquire() = 0;
	virtual HRESULT GetDeviceState
	(
		DWORD,
		LPVOID
	) = 0;
	virtual HRESULT GetDeviceData
	(
		DWORD,
		LPDIDEVICEOBJECTDATA,
		LPDWORD,
		DWORD
	) = 0;
	virtual HRESULT SetDataFormat(LPCDIDATAFORMAT) = 0;
	virtual HRESULT SetEventNotification(HANDLE) = 0;
	virtual HRESULT SetCooperativeLevel
	(
		HWND,
		DWORD
	) = 0;
	virtual HRESULT GetObjectInfo
	(
		LPDIDEVICEOBJECTINSTANCEA,
		DWORD,
		DWORD
	) = 0;
	virtual HRESULT GetDeviceInfo(LPDIDEVICEINSTANCEA) = 0;
	virtual HRESULT RunControlPanel
	(
		HWND,
		DWORD
	) = 0;
	virtual HRESULT Initialize
	(
		HINSTANCE,
		DWORD,
		const GUID&
	) = 0;
	virtual HRESULT CreateEffect
	(
		const GUID&,
		LPCDIEFFECT,
		LPDIRECTINPUTEFFECT*,
		LPUNKNOWN
	) = 0;
	virtual HRESULT EnumEffects
	(
		LPDIENUMEFFECTSCALLBACKA,
		LPVOID,
		DWORD
	) = 0;
	virtual HRESULT GetEffectInfo
	(
		LPDIEFFECTINFOA,
		const GUID&
	) = 0;
	virtual HRESULT GetForceFeedbackState(LPDWORD) = 0;
	virtual HRESULT SendForceFeedbackCommand(DWORD) = 0;
	virtual HRESULT EnumCreatedEffectObjects
	(
		LPDIENUMCREATEDEFFECTOBJECTSCALLBACK,
		LPVOID,
		DWORD
	) = 0;
	virtual HRESULT Escape(LPDIEFFESCAPE) = 0;
	virtual HRESULT Poll() = 0;
	virtual HRESULT SendDeviceData
	(
		DWORD,
		LPCDIDEVICEOBJECTDATA,
		LPDWORD,
		DWORD
	) = 0;
	virtual HRESULT EnumEffectsInFile
	(
		LPCSTR,
		LPDIENUMEFFECTSINFILECALLBACK,
		LPVOID,
		DWORD
	) = 0;
	virtual HRESULT WriteEffectToFile
	(
		LPCSTR,
		DWORD,
		LPDIFILEEFFECT,
		DWORD
	) = 0;
	virtual HRESULT BuildActionMap
	(
		LPDIACTIONFORMATA,
		LPCSTR,
		DWORD
	) = 0;
	virtual HRESULT SetActionMap
	(
		LPDIACTIONFORMATA,
		LPCSTR,
		DWORD
	) = 0;
	virtual HRESULT GetImageInfo(LPDIDEVICEIMAGEINFOHEADERA) = 0;
};

static_assert(sizeof(IDirectInputDevice8A) == 8);

// IDirectInputDevice8W

struct __declspec(novtable) IDirectInputDevice8W : IUnknown
{
	virtual HRESULT GetCapabilities(LPDIDEVCAPS) = 0;
	virtual HRESULT EnumObjects
	(
		LPDIENUMDEVICEOBJECTSCALLBACKW,
		LPVOID,
		DWORD
	) = 0;
	virtual HRESULT GetProperty
	(
		const GUID&,
		LPDIPROPHEADER
	) = 0;
	virtual HRESULT SetProperty
	(
		const GUID&,
		LPCDIPROPHEADER
	) = 0;
	virtual HRESULT Acquire() = 0;
	virtual HRESULT Unacquire() = 0;
	virtual HRESULT GetDeviceState
	(
		DWORD,
		LPVOID
	) = 0;
	virtual HRESULT GetDeviceData
	(
		DWORD,
		LPDIDEVICEOBJECTDATA,
		LPDWORD,
		DWORD
	) = 0;
	virtual HRESULT SetDataFormat(LPCDIDATAFORMAT) = 0;
	virtual HRESULT SetEventNotification(HANDLE) = 0;
	virtual HRESULT SetCooperativeLevel
	(
		HWND,
		DWORD
	) = 0;
	virtual HRESULT GetObjectInfo
	(
		LPDIDEVICEOBJECTINSTANCEW,
		DWORD,
		DWORD
	) = 0;
	virtual HRESULT GetDeviceInfo(LPDIDEVICEINSTANCEW) = 0;
	virtual HRESULT RunControlPanel
	(
		HWND,
		DWORD
	) = 0;
	virtual HRESULT Initialize
	(
		HINSTANCE,
		DWORD,
		const GUID&
	) = 0;
	virtual HRESULT CreateEffect
	(
		const GUID&,
		LPCDIEFFECT,
		LPDIRECTINPUTEFFECT*,
		LPUNKNOWN
	) = 0;
	virtual HRESULT EnumEffects
	(
		LPDIENUMEFFECTSCALLBACKW,
		LPVOID,
		DWORD
	) = 0;
	virtual HRESULT GetEffectInfo
	(
		LPDIEFFECTINFOW,
		const GUID&
	) = 0;
	virtual HRESULT GetForceFeedbackState(LPDWORD) = 0;
	virtual HRESULT SendForceFeedbackCommand(DWORD) = 0;
	virtual HRESULT EnumCreatedEffectObjects
	(
		LPDIENUMCREATEDEFFECTOBJECTSCALLBACK,
		LPVOID,
		DWORD
	) = 0;
	virtual HRESULT Escape(LPDIEFFESCAPE) = 0;
	virtual HRESULT Poll() = 0;
	virtual HRESULT SendDeviceData
	(
		DWORD,
		LPCDIDEVICEOBJECTDATA,
		LPDWORD,
		DWORD
	) = 0;
	virtual HRESULT EnumEffectsInFile
	(
		LPCWSTR,
		LPDIENUMEFFECTSINFILECALLBACK,
		LPVOID,
		DWORD
	) = 0;
	virtual HRESULT WriteEffectToFile
	(
		LPCWSTR,
		DWORD,
		LPDIFILEEFFECT,
		DWORD
	) = 0;
	virtual HRESULT BuildActionMap
	(
		LPDIACTIONFORMATW,
		LPCWSTR,
		DWORD
	) = 0;
	virtual HRESULT SetActionMap
	(
		LPDIACTIONFORMATW,
		LPCWSTR,
		DWORD
	) = 0;
	virtual HRESULT GetImageInfo(LPDIDEVICEIMAGEINFOHEADERW) = 0;
};

static_assert(sizeof(IDirectInputDevice8W) == 8);

// IDirectInputEffect

struct __declspec(novtable) IDirectInputEffect : IUnknown
{
	virtual HRESULT Initialize
	(
		HINSTANCE,
		DWORD,
		const GUID&
	) = 0;
	virtual HRESULT GetEffectGuid(LPGUID) = 0;
	virtual HRESULT GetParameters
	(
		LPDIEFFECT,
		DWORD
	) = 0;
	virtual HRESULT SetParameters
	(
		LPCDIEFFECT,
		DWORD
	) = 0;
	virtual HRESULT Start
	(
		DWORD,
		DWORD
	) = 0;
	virtual HRESULT Stop() = 0;
	virtual HRESULT GetEffectStatus(LPDWORD) = 0;
	virtual HRESULT Download() = 0;
	virtual HRESULT Unload() = 0;
	virtual HRESULT Escape(LPDIEFFESCAPE) = 0;
};

static_assert(sizeof(IDirectInputEffect) == 8);

extern "C" HRESULT DirectInput8Create
(
	HINSTANCE hinst,
	DWORD dwVersion,
	const IID& riidltf,
	LPVOID* ppvOut,
	LPUNKNOWN punkOuter
);
#pragma endregion

#else

#pragma region x86_32

struct IDirectInput8A;
struct IDirectInput8W;
struct IDirectInputDevice8A;
struct IDirectInputDevice8W;
struct IDirectInputEffect;

extern "C" const GUID IID_IDirectInput8A;
extern "C" const GUID IID_IDirectInput8W;
extern "C" const GUID IID_IDirectInputDevice8A;
extern "C" const GUID IID_IDirectInputDevice8W;
extern "C" const GUID IID_IDirectInputEffect;

extern "C" const GUID GUID_XAxis;
extern "C" const GUID GUID_YAxis;
extern "C" const GUID GUID_ZAxis;
extern "C" const GUID GUID_RxAxis;
extern "C" const GUID GUID_RyAxis;
extern "C" const GUID GUID_RzAxis;
extern "C" const GUID GUID_Slider;
extern "C" const GUID GUID_Button;
extern "C" const GUID GUID_Key;
extern "C" const GUID GUID_POV;
extern "C" const GUID GUID_Unknown;
extern "C" const GUID GUID_SysMouse;
extern "C" const GUID GUID_SysKeyboard;
extern "C" const GUID GUID_Joystick;
extern "C" const GUID GUID_SysMouseEm;
extern "C" const GUID GUID_SysMouseEm2;
extern "C" const GUID GUID_SysKeyboardEm;
extern "C" const GUID GUID_SysKeyboardEm2;
extern "C" const GUID GUID_ConstantForce;
extern "C" const GUID GUID_RampForce;
extern "C" const GUID GUID_Square;
extern "C" const GUID GUID_Sine;
extern "C" const GUID GUID_Triangle;
extern "C" const GUID GUID_SawtoothUp;
extern "C" const GUID GUID_SawtoothDown;
extern "C" const GUID GUID_Spring;
extern "C" const GUID GUID_Damper;
extern "C" const GUID GUID_Inertia;
extern "C" const GUID GUID_Friction;
extern "C" const GUID GUID_CustomForce;

// LPDIRECTINPUTDEVICE8A

typedef IDirectInputDevice8A* LPDIRECTINPUTDEVICE8A;

static_assert(TypeMatch<LPDIRECTINPUTDEVICE8A, IDirectInputDevice8A*>::value);

static_assert(sizeof(LPDIRECTINPUTDEVICE8A) == 4);

// LPDIRECTINPUTDEVICE8W

typedef IDirectInputDevice8W* LPDIRECTINPUTDEVICE8W;

static_assert(TypeMatch<LPDIRECTINPUTDEVICE8W, IDirectInputDevice8W*>::value);

static_assert(sizeof(LPDIRECTINPUTDEVICE8W) == 4);

// LPDIRECTINPUTEFFECT

typedef IDirectInputEffect* LPDIRECTINPUTEFFECT;

static_assert(TypeMatch<LPDIRECTINPUTEFFECT, IDirectInputEffect*>::value);

static_assert(sizeof(LPDIRECTINPUTEFFECT) == 4);

// D3DCOLOR

typedef DWORD D3DCOLOR;

static_assert(TypeMatch<D3DCOLOR, DWORD>::value);

static_assert(sizeof(D3DCOLOR) == 4);

enum
{
	DI_OK=0,
	DISCL_EXCLUSIVE=0x00000001,
	DISCL_NONEXCLUSIVE=0x00000002,
	DISCL_FOREGROUND=0x00000004,
	DISCL_BACKGROUND=0x00000008,
	DISCL_NOWINKEY=0x00000010,
	DIERR_OLDDIRECTINPUTVERSION=0x8007047E,
	DIERR_BETADIRECTINPUTVERSION=0x80070481,
	DIERR_BADDRIVERVER=0x80070077,
	DIERR_DEVICENOTREG=0x80040154,
	DIERR_NOTFOUND=0x80070002,
	DIERR_OBJECTNOTFOUND=0x80070002,
	DIERR_INVALIDPARAM=0x80070057,
	DIERR_NOINTERFACE=0x80004002,
	DIERR_GENERIC=0x80004005,
	DIERR_OUTOFMEMORY=0x8007000E,
	DIERR_UNSUPPORTED=0x80004001,
	DIERR_NOTINITIALIZED=0x80070015,
	DIERR_ALREADYINITIALIZED=0x800704DF,
	DIERR_NOAGGREGATION=0x80040110,
	DIERR_OTHERAPPHASPRIO=0x80070005,
	DIERR_INPUTLOST=0x8007001E,
	DIERR_ACQUIRED=0x800700AA,
	DIERR_NOTACQUIRED=0x8007000C,
	DIERR_READONLY=0x80070005,
	DIERR_HANDLEEXISTS=0x80070005,
	DIERR_INSUFFICIENTPRIVS=0x80040200,
	DIERR_DEVICEFULL=0x80040201,
	DIERR_MOREDATA=0x80040202,
	DIERR_NOTDOWNLOADED=0x80040203,
	DIERR_HASEFFECTS=0x80040204,
	DIERR_NOTEXCLUSIVEACQUIRED=0x80040205,
	DIERR_INCOMPLETEEFFECT=0x80040206,
	DIERR_NOTBUFFERED=0x80040207,
	DIERR_EFFECTPLAYING=0x80040208,
	DIERR_UNPLUGGED=0x80040209,
	DIERR_REPORTFULL=0x8004020A,
	DIERR_MAPFILEFAIL=0x8004020B,
	DIDEVTYPE_HID=0x10000,
	DI8DEVCLASS_ALL=0,
	DI8DEVCLASS_DEVICE=1,
	DI8DEVCLASS_POINTER=2,
	DI8DEVCLASS_KEYBOARD=3,
	DI8DEVCLASS_GAMECTRL=4,
	DI8DEVTYPE_DEVICE=0x11,
	DI8DEVTYPE_MOUSE=0x12,
	DI8DEVTYPE_KEYBOARD=0x13,
	DI8DEVTYPE_JOYSTICK=0x14,
	DI8DEVTYPE_GAMEPAD=0x15,
	DI8DEVTYPE_DRIVING=0x16,
	DI8DEVTYPE_FLIGHT=0x17,
	DI8DEVTYPE_1STPERSON=0x18,
	DI8DEVTYPE_DEVICECTRL=0x19,
	DI8DEVTYPE_SCREENPOINTER=0x1A,
	DI8DEVTYPE_REMOTE=0x1B,
	DI8DEVTYPE_SUPPLEMENTAL=0x1C,
	DIEDFL_ALLDEVICES=0x00000000,
	DIEDFL_ATTACHEDONLY=0x00000001,
	DIEDFL_FORCEFEEDBACK=0x00000100,
	DIEDFL_INCLUDEALIASES=0x00010000,
	DIEDFL_INCLUDEPHANTOMS=0x00020000,
	DIEDFL_INCLUDEHIDDEN=0x00040000,
	DIENUM_STOP=0,
	DIENUM_CONTINUE=1,
};

#pragma pack(push, 1)

// DIMOUSESTATE

struct DIMOUSESTATE
{
	LONG lX; // 0
	LONG lY; // 4
	LONG lZ; // 8
	BYTE rgbButtons[4]; // 0xC
};

static_assert(TypeMatch<decltype(DIMOUSESTATE::lX), LONG>::value);
static_assert(TypeMatch<decltype(DIMOUSESTATE::lY), LONG>::value);
static_assert(TypeMatch<decltype(DIMOUSESTATE::lZ), LONG>::value);
static_assert(TypeMatch<decltype(DIMOUSESTATE::rgbButtons), BYTE[4]>::value);

static_assert(offsetof(DIMOUSESTATE, lX) == 0);
static_assert(offsetof(DIMOUSESTATE, lY) == 4);
static_assert(offsetof(DIMOUSESTATE, lZ) == 8);
static_assert(offsetof(DIMOUSESTATE, rgbButtons) == 0xC);

static_assert(sizeof(DIMOUSESTATE) == 16);

typedef DIMOUSESTATE * LPDIMOUSESTATE;

static_assert(TypeMatch<LPDIMOUSESTATE, DIMOUSESTATE *>::value);

static_assert(sizeof(LPDIMOUSESTATE) == 4);

// DIMOUSESTATE2

struct DIMOUSESTATE2
{
	LONG lX; // 0
	LONG lY; // 4
	LONG lZ; // 8
	BYTE rgbButtons[8]; // 0xC
};

static_assert(TypeMatch<decltype(DIMOUSESTATE2::lX), LONG>::value);
static_assert(TypeMatch<decltype(DIMOUSESTATE2::lY), LONG>::value);
static_assert(TypeMatch<decltype(DIMOUSESTATE2::lZ), LONG>::value);
static_assert(TypeMatch<decltype(DIMOUSESTATE2::rgbButtons), BYTE[8]>::value);

static_assert(offsetof(DIMOUSESTATE2, lX) == 0);
static_assert(offsetof(DIMOUSESTATE2, lY) == 4);
static_assert(offsetof(DIMOUSESTATE2, lZ) == 8);
static_assert(offsetof(DIMOUSESTATE2, rgbButtons) == 0xC);

static_assert(sizeof(DIMOUSESTATE2) == 20);

typedef DIMOUSESTATE2 * LPDIMOUSESTATE2;

static_assert(TypeMatch<LPDIMOUSESTATE2, DIMOUSESTATE2 *>::value);

static_assert(sizeof(LPDIMOUSESTATE2) == 4);

// DIDEVCAPS

struct DIDEVCAPS
{
	DWORD dwSize; // 0
	DWORD dwFlags; // 4
	DWORD dwDevType; // 8
	DWORD dwAxes; // 0xC
	DWORD dwButtons; // 0x10
	DWORD dwPOVs; // 0x14
	DWORD dwFFSamplePeriod; // 0x18
	DWORD dwFFMinTimeResolution; // 0x1C
	DWORD dwFirmwareRevision; // 0x20
	DWORD dwHardwareRevision; // 0x24
	DWORD dwFFDriverVersion; // 0x28
};

static_assert(TypeMatch<decltype(DIDEVCAPS::dwSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVCAPS::dwFlags), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVCAPS::dwDevType), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVCAPS::dwAxes), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVCAPS::dwButtons), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVCAPS::dwPOVs), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVCAPS::dwFFSamplePeriod), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVCAPS::dwFFMinTimeResolution), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVCAPS::dwFirmwareRevision), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVCAPS::dwHardwareRevision), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVCAPS::dwFFDriverVersion), DWORD>::value);

static_assert(offsetof(DIDEVCAPS, dwSize) == 0);
static_assert(offsetof(DIDEVCAPS, dwFlags) == 4);
static_assert(offsetof(DIDEVCAPS, dwDevType) == 8);
static_assert(offsetof(DIDEVCAPS, dwAxes) == 0xC);
static_assert(offsetof(DIDEVCAPS, dwButtons) == 0x10);
static_assert(offsetof(DIDEVCAPS, dwPOVs) == 0x14);
static_assert(offsetof(DIDEVCAPS, dwFFSamplePeriod) == 0x18);
static_assert(offsetof(DIDEVCAPS, dwFFMinTimeResolution) == 0x1C);
static_assert(offsetof(DIDEVCAPS, dwFirmwareRevision) == 0x20);
static_assert(offsetof(DIDEVCAPS, dwHardwareRevision) == 0x24);
static_assert(offsetof(DIDEVCAPS, dwFFDriverVersion) == 0x28);

static_assert(sizeof(DIDEVCAPS) == 44);

typedef DIDEVCAPS * LPDIDEVCAPS;

static_assert(TypeMatch<LPDIDEVCAPS, DIDEVCAPS *>::value);

static_assert(sizeof(LPDIDEVCAPS) == 4);

// DIOBJECTDATAFORMAT

struct DIOBJECTDATAFORMAT
{
	const GUID* pguid; // 0
	DWORD dwOfs; // 4
	DWORD dwType; // 8
	DWORD dwFlags; // 0xC
};

static_assert(TypeMatch<decltype(DIOBJECTDATAFORMAT::pguid), const GUID*>::value);
static_assert(TypeMatch<decltype(DIOBJECTDATAFORMAT::dwOfs), DWORD>::value);
static_assert(TypeMatch<decltype(DIOBJECTDATAFORMAT::dwType), DWORD>::value);
static_assert(TypeMatch<decltype(DIOBJECTDATAFORMAT::dwFlags), DWORD>::value);

static_assert(offsetof(DIOBJECTDATAFORMAT, pguid) == 0);
static_assert(offsetof(DIOBJECTDATAFORMAT, dwOfs) == 4);
static_assert(offsetof(DIOBJECTDATAFORMAT, dwType) == 8);
static_assert(offsetof(DIOBJECTDATAFORMAT, dwFlags) == 0xC);

static_assert(sizeof(DIOBJECTDATAFORMAT) == 16);

typedef DIOBJECTDATAFORMAT * LPDIOBJECTDATAFORMAT;
typedef const DIOBJECTDATAFORMAT * LPCDIOBJECTDATAFORMAT;

static_assert(TypeMatch<LPDIOBJECTDATAFORMAT, DIOBJECTDATAFORMAT *>::value);
static_assert(TypeMatch<LPCDIOBJECTDATAFORMAT, const DIOBJECTDATAFORMAT *>::value);

static_assert(sizeof(LPDIOBJECTDATAFORMAT) == 4);
static_assert(sizeof(LPCDIOBJECTDATAFORMAT) == 4);

// DIDATAFORMAT

struct DIDATAFORMAT
{
	DWORD dwSize; // 0
	DWORD dwObjSize; // 4
	DWORD dwFlags; // 8
	DWORD dwDataSize; // 0xC
	DWORD dwNumObjs; // 0x10
	LPDIOBJECTDATAFORMAT rgodf; // 0x14
};

static_assert(TypeMatch<decltype(DIDATAFORMAT::dwSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIDATAFORMAT::dwObjSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIDATAFORMAT::dwFlags), DWORD>::value);
static_assert(TypeMatch<decltype(DIDATAFORMAT::dwDataSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIDATAFORMAT::dwNumObjs), DWORD>::value);
static_assert(TypeMatch<decltype(DIDATAFORMAT::rgodf), LPDIOBJECTDATAFORMAT>::value);

static_assert(offsetof(DIDATAFORMAT, dwSize) == 0);
static_assert(offsetof(DIDATAFORMAT, dwObjSize) == 4);
static_assert(offsetof(DIDATAFORMAT, dwFlags) == 8);
static_assert(offsetof(DIDATAFORMAT, dwDataSize) == 0xC);
static_assert(offsetof(DIDATAFORMAT, dwNumObjs) == 0x10);
static_assert(offsetof(DIDATAFORMAT, rgodf) == 0x14);

static_assert(sizeof(DIDATAFORMAT) == 24);

typedef DIDATAFORMAT * LPDIDATAFORMAT;
typedef const DIDATAFORMAT * LPCDIDATAFORMAT;

static_assert(TypeMatch<LPDIDATAFORMAT, DIDATAFORMAT *>::value);
static_assert(TypeMatch<LPCDIDATAFORMAT, const DIDATAFORMAT *>::value);

static_assert(sizeof(LPDIDATAFORMAT) == 4);
static_assert(sizeof(LPCDIDATAFORMAT) == 4);

// DIPROPHEADER

struct DIPROPHEADER
{
	DWORD dwSize; // 0
	DWORD dwHeaderSize; // 4
	DWORD dwObj; // 8
	DWORD dwHow; // 0xC
};

static_assert(TypeMatch<decltype(DIPROPHEADER::dwSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIPROPHEADER::dwHeaderSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIPROPHEADER::dwObj), DWORD>::value);
static_assert(TypeMatch<decltype(DIPROPHEADER::dwHow), DWORD>::value);

static_assert(offsetof(DIPROPHEADER, dwSize) == 0);
static_assert(offsetof(DIPROPHEADER, dwHeaderSize) == 4);
static_assert(offsetof(DIPROPHEADER, dwObj) == 8);
static_assert(offsetof(DIPROPHEADER, dwHow) == 0xC);

static_assert(sizeof(DIPROPHEADER) == 16);

typedef DIPROPHEADER * LPDIPROPHEADER;
typedef const DIPROPHEADER * LPCDIPROPHEADER;

static_assert(TypeMatch<LPDIPROPHEADER, DIPROPHEADER *>::value);
static_assert(TypeMatch<LPCDIPROPHEADER, const DIPROPHEADER *>::value);

static_assert(sizeof(LPDIPROPHEADER) == 4);
static_assert(sizeof(LPCDIPROPHEADER) == 4);

// DIDEVICEOBJECTINSTANCEA

struct DIDEVICEOBJECTINSTANCEA
{
	DWORD dwSize; // 0
	GUID guidType; // 4
	DWORD dwOfs; // 0x14
	DWORD dwType; // 0x18
	DWORD dwFlags; // 0x1C
	CHAR tszName[260]; // 0x20
	DWORD dwFFMaxForce; // 0x124
	DWORD dwFFForceResolution; // 0x128
	WORD wCollectionNumber; // 0x12C
	WORD wDesignatorIndex; // 0x12E
	WORD wUsagePage; // 0x130
	WORD wUsage; // 0x132
	DWORD dwDimension; // 0x134
	WORD wExponent; // 0x138
	WORD wReportId; // 0x13A
};

static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEA::dwSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEA::guidType), GUID>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEA::dwOfs), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEA::dwType), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEA::dwFlags), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEA::tszName), CHAR[260]>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEA::dwFFMaxForce), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEA::dwFFForceResolution), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEA::wCollectionNumber), WORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEA::wDesignatorIndex), WORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEA::wUsagePage), WORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEA::wUsage), WORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEA::dwDimension), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEA::wExponent), WORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEA::wReportId), WORD>::value);

static_assert(offsetof(DIDEVICEOBJECTINSTANCEA, dwSize) == 0);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEA, guidType) == 4);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEA, dwOfs) == 0x14);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEA, dwType) == 0x18);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEA, dwFlags) == 0x1C);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEA, tszName) == 0x20);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEA, dwFFMaxForce) == 0x124);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEA, dwFFForceResolution) == 0x128);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEA, wCollectionNumber) == 0x12C);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEA, wDesignatorIndex) == 0x12E);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEA, wUsagePage) == 0x130);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEA, wUsage) == 0x132);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEA, dwDimension) == 0x134);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEA, wExponent) == 0x138);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEA, wReportId) == 0x13A);

static_assert(sizeof(DIDEVICEOBJECTINSTANCEA) == 316);

typedef DIDEVICEOBJECTINSTANCEA * LPDIDEVICEOBJECTINSTANCEA;
typedef const DIDEVICEOBJECTINSTANCEA * LPCDIDEVICEOBJECTINSTANCEA;

static_assert(TypeMatch<LPDIDEVICEOBJECTINSTANCEA, DIDEVICEOBJECTINSTANCEA *>::value);
static_assert(TypeMatch<LPCDIDEVICEOBJECTINSTANCEA, const DIDEVICEOBJECTINSTANCEA *>::value);

static_assert(sizeof(LPDIDEVICEOBJECTINSTANCEA) == 4);
static_assert(sizeof(LPCDIDEVICEOBJECTINSTANCEA) == 4);

// DIDEVICEOBJECTINSTANCEW

struct DIDEVICEOBJECTINSTANCEW
{
	DWORD dwSize; // 0
	GUID guidType; // 4
	DWORD dwOfs; // 0x14
	DWORD dwType; // 0x18
	DWORD dwFlags; // 0x1C
	WCHAR tszName[260]; // 0x20
	DWORD dwFFMaxForce; // 0x228
	DWORD dwFFForceResolution; // 0x22C
	WORD wCollectionNumber; // 0x230
	WORD wDesignatorIndex; // 0x232
	WORD wUsagePage; // 0x234
	WORD wUsage; // 0x236
	DWORD dwDimension; // 0x238
	WORD wExponent; // 0x23C
	WORD wReportId; // 0x23E
};

static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEW::dwSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEW::guidType), GUID>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEW::dwOfs), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEW::dwType), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEW::dwFlags), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEW::tszName), WCHAR[260]>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEW::dwFFMaxForce), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEW::dwFFForceResolution), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEW::wCollectionNumber), WORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEW::wDesignatorIndex), WORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEW::wUsagePage), WORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEW::wUsage), WORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEW::dwDimension), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEW::wExponent), WORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTINSTANCEW::wReportId), WORD>::value);

static_assert(offsetof(DIDEVICEOBJECTINSTANCEW, dwSize) == 0);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEW, guidType) == 4);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEW, dwOfs) == 0x14);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEW, dwType) == 0x18);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEW, dwFlags) == 0x1C);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEW, tszName) == 0x20);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEW, dwFFMaxForce) == 0x228);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEW, dwFFForceResolution) == 0x22C);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEW, wCollectionNumber) == 0x230);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEW, wDesignatorIndex) == 0x232);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEW, wUsagePage) == 0x234);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEW, wUsage) == 0x236);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEW, dwDimension) == 0x238);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEW, wExponent) == 0x23C);
static_assert(offsetof(DIDEVICEOBJECTINSTANCEW, wReportId) == 0x23E);

static_assert(sizeof(DIDEVICEOBJECTINSTANCEW) == 576);

typedef DIDEVICEOBJECTINSTANCEW * LPDIDEVICEOBJECTINSTANCEW;
typedef const DIDEVICEOBJECTINSTANCEW * LPCDIDEVICEOBJECTINSTANCEW;

static_assert(TypeMatch<LPDIDEVICEOBJECTINSTANCEW, DIDEVICEOBJECTINSTANCEW *>::value);
static_assert(TypeMatch<LPCDIDEVICEOBJECTINSTANCEW, const DIDEVICEOBJECTINSTANCEW *>::value);

static_assert(sizeof(LPDIDEVICEOBJECTINSTANCEW) == 4);
static_assert(sizeof(LPCDIDEVICEOBJECTINSTANCEW) == 4);

// DIDEVICEOBJECTDATA

struct DIDEVICEOBJECTDATA
{
	DWORD dwOfs; // 0
	DWORD dwData; // 4
	DWORD dwTimeStamp; // 8
	DWORD dwSequence; // 0xC
	UINT_PTR uAppData; // 0x10
};

static_assert(TypeMatch<decltype(DIDEVICEOBJECTDATA::dwOfs), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTDATA::dwData), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTDATA::dwTimeStamp), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTDATA::dwSequence), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEOBJECTDATA::uAppData), UINT_PTR>::value);

static_assert(offsetof(DIDEVICEOBJECTDATA, dwOfs) == 0);
static_assert(offsetof(DIDEVICEOBJECTDATA, dwData) == 4);
static_assert(offsetof(DIDEVICEOBJECTDATA, dwTimeStamp) == 8);
static_assert(offsetof(DIDEVICEOBJECTDATA, dwSequence) == 0xC);
static_assert(offsetof(DIDEVICEOBJECTDATA, uAppData) == 0x10);

static_assert(sizeof(DIDEVICEOBJECTDATA) == 20);

typedef DIDEVICEOBJECTDATA * LPDIDEVICEOBJECTDATA;
typedef const DIDEVICEOBJECTDATA * LPCDIDEVICEOBJECTDATA;

static_assert(TypeMatch<LPDIDEVICEOBJECTDATA, DIDEVICEOBJECTDATA *>::value);
static_assert(TypeMatch<LPCDIDEVICEOBJECTDATA, const DIDEVICEOBJECTDATA *>::value);

static_assert(sizeof(LPDIDEVICEOBJECTDATA) == 4);
static_assert(sizeof(LPCDIDEVICEOBJECTDATA) == 4);

// DIDEVICEINSTANCEA

struct DIDEVICEINSTANCEA
{
	DWORD dwSize; // 0
	GUID guidInstance; // 4
	GUID guidProduct; // 0x14
	DWORD dwDevType; // 0x24
	CHAR tszInstanceName[260]; // 0x28
	CHAR tszProductName[260]; // 0x12C
	GUID guidFFDriver; // 0x230
	WORD wUsagePage; // 0x240
	WORD wUsage; // 0x242
};

static_assert(TypeMatch<decltype(DIDEVICEINSTANCEA::dwSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEINSTANCEA::guidInstance), GUID>::value);
static_assert(TypeMatch<decltype(DIDEVICEINSTANCEA::guidProduct), GUID>::value);
static_assert(TypeMatch<decltype(DIDEVICEINSTANCEA::dwDevType), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEINSTANCEA::tszInstanceName), CHAR[260]>::value);
static_assert(TypeMatch<decltype(DIDEVICEINSTANCEA::tszProductName), CHAR[260]>::value);
static_assert(TypeMatch<decltype(DIDEVICEINSTANCEA::guidFFDriver), GUID>::value);
static_assert(TypeMatch<decltype(DIDEVICEINSTANCEA::wUsagePage), WORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEINSTANCEA::wUsage), WORD>::value);

static_assert(offsetof(DIDEVICEINSTANCEA, dwSize) == 0);
static_assert(offsetof(DIDEVICEINSTANCEA, guidInstance) == 4);
static_assert(offsetof(DIDEVICEINSTANCEA, guidProduct) == 0x14);
static_assert(offsetof(DIDEVICEINSTANCEA, dwDevType) == 0x24);
static_assert(offsetof(DIDEVICEINSTANCEA, tszInstanceName) == 0x28);
static_assert(offsetof(DIDEVICEINSTANCEA, tszProductName) == 0x12C);
static_assert(offsetof(DIDEVICEINSTANCEA, guidFFDriver) == 0x230);
static_assert(offsetof(DIDEVICEINSTANCEA, wUsagePage) == 0x240);
static_assert(offsetof(DIDEVICEINSTANCEA, wUsage) == 0x242);

static_assert(sizeof(DIDEVICEINSTANCEA) == 580);

typedef DIDEVICEINSTANCEA * LPDIDEVICEINSTANCEA;
typedef const DIDEVICEINSTANCEA * LPCDIDEVICEINSTANCEA;

static_assert(TypeMatch<LPDIDEVICEINSTANCEA, DIDEVICEINSTANCEA *>::value);
static_assert(TypeMatch<LPCDIDEVICEINSTANCEA, const DIDEVICEINSTANCEA *>::value);

static_assert(sizeof(LPDIDEVICEINSTANCEA) == 4);
static_assert(sizeof(LPCDIDEVICEINSTANCEA) == 4);

// DIDEVICEINSTANCEW

struct DIDEVICEINSTANCEW
{
	DWORD dwSize; // 0
	GUID guidInstance; // 4
	GUID guidProduct; // 0x14
	DWORD dwDevType; // 0x24
	WCHAR tszInstanceName[260]; // 0x28
	WCHAR tszProductName[260]; // 0x230
	GUID guidFFDriver; // 0x438
	WORD wUsagePage; // 0x448
	WORD wUsage; // 0x44A
};

static_assert(TypeMatch<decltype(DIDEVICEINSTANCEW::dwSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEINSTANCEW::guidInstance), GUID>::value);
static_assert(TypeMatch<decltype(DIDEVICEINSTANCEW::guidProduct), GUID>::value);
static_assert(TypeMatch<decltype(DIDEVICEINSTANCEW::dwDevType), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEINSTANCEW::tszInstanceName), WCHAR[260]>::value);
static_assert(TypeMatch<decltype(DIDEVICEINSTANCEW::tszProductName), WCHAR[260]>::value);
static_assert(TypeMatch<decltype(DIDEVICEINSTANCEW::guidFFDriver), GUID>::value);
static_assert(TypeMatch<decltype(DIDEVICEINSTANCEW::wUsagePage), WORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEINSTANCEW::wUsage), WORD>::value);

static_assert(offsetof(DIDEVICEINSTANCEW, dwSize) == 0);
static_assert(offsetof(DIDEVICEINSTANCEW, guidInstance) == 4);
static_assert(offsetof(DIDEVICEINSTANCEW, guidProduct) == 0x14);
static_assert(offsetof(DIDEVICEINSTANCEW, dwDevType) == 0x24);
static_assert(offsetof(DIDEVICEINSTANCEW, tszInstanceName) == 0x28);
static_assert(offsetof(DIDEVICEINSTANCEW, tszProductName) == 0x230);
static_assert(offsetof(DIDEVICEINSTANCEW, guidFFDriver) == 0x438);
static_assert(offsetof(DIDEVICEINSTANCEW, wUsagePage) == 0x448);
static_assert(offsetof(DIDEVICEINSTANCEW, wUsage) == 0x44A);

static_assert(sizeof(DIDEVICEINSTANCEW) == 1100);

typedef DIDEVICEINSTANCEW * LPDIDEVICEINSTANCEW;
typedef const DIDEVICEINSTANCEW * LPCDIDEVICEINSTANCEW;

static_assert(TypeMatch<LPDIDEVICEINSTANCEW, DIDEVICEINSTANCEW *>::value);
static_assert(TypeMatch<LPCDIDEVICEINSTANCEW, const DIDEVICEINSTANCEW *>::value);

static_assert(sizeof(LPDIDEVICEINSTANCEW) == 4);
static_assert(sizeof(LPCDIDEVICEINSTANCEW) == 4);

// DIENVELOPE

struct DIENVELOPE
{
	DWORD dwSize; // 0
	DWORD dwAttackLevel; // 4
	DWORD dwAttackTime; // 8
	DWORD dwFadeLevel; // 0xC
	DWORD dwFadeTime; // 0x10
};

static_assert(TypeMatch<decltype(DIENVELOPE::dwSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIENVELOPE::dwAttackLevel), DWORD>::value);
static_assert(TypeMatch<decltype(DIENVELOPE::dwAttackTime), DWORD>::value);
static_assert(TypeMatch<decltype(DIENVELOPE::dwFadeLevel), DWORD>::value);
static_assert(TypeMatch<decltype(DIENVELOPE::dwFadeTime), DWORD>::value);

static_assert(offsetof(DIENVELOPE, dwSize) == 0);
static_assert(offsetof(DIENVELOPE, dwAttackLevel) == 4);
static_assert(offsetof(DIENVELOPE, dwAttackTime) == 8);
static_assert(offsetof(DIENVELOPE, dwFadeLevel) == 0xC);
static_assert(offsetof(DIENVELOPE, dwFadeTime) == 0x10);

static_assert(sizeof(DIENVELOPE) == 20);

typedef DIENVELOPE * LPDIENVELOPE;
typedef const DIENVELOPE * LPCDIENVELOPE;

static_assert(TypeMatch<LPDIENVELOPE, DIENVELOPE *>::value);
static_assert(TypeMatch<LPCDIENVELOPE, const DIENVELOPE *>::value);

static_assert(sizeof(LPDIENVELOPE) == 4);
static_assert(sizeof(LPCDIENVELOPE) == 4);

// DIEFFECT

struct DIEFFECT
{
	DWORD dwSize; // 0
	DWORD dwFlags; // 4
	DWORD dwDuration; // 8
	DWORD dwSamplePeriod; // 0xC
	DWORD dwGain; // 0x10
	DWORD dwTriggerButton; // 0x14
	DWORD dwTriggerRepeatInterval; // 0x18
	DWORD cAxes; // 0x1C
	LPDWORD rgdwAxes; // 0x20
	LPLONG rglDirection; // 0x24
	LPDIENVELOPE lpEnvelope; // 0x28
	DWORD cbTypeSpecificParams; // 0x2C
	LPVOID lpvTypeSpecificParams; // 0x30
	DWORD dwStartDelay; // 0x34
};

static_assert(TypeMatch<decltype(DIEFFECT::dwSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIEFFECT::dwFlags), DWORD>::value);
static_assert(TypeMatch<decltype(DIEFFECT::dwDuration), DWORD>::value);
static_assert(TypeMatch<decltype(DIEFFECT::dwSamplePeriod), DWORD>::value);
static_assert(TypeMatch<decltype(DIEFFECT::dwGain), DWORD>::value);
static_assert(TypeMatch<decltype(DIEFFECT::dwTriggerButton), DWORD>::value);
static_assert(TypeMatch<decltype(DIEFFECT::dwTriggerRepeatInterval), DWORD>::value);
static_assert(TypeMatch<decltype(DIEFFECT::cAxes), DWORD>::value);
static_assert(TypeMatch<decltype(DIEFFECT::rgdwAxes), LPDWORD>::value);
static_assert(TypeMatch<decltype(DIEFFECT::rglDirection), LPLONG>::value);
static_assert(TypeMatch<decltype(DIEFFECT::lpEnvelope), LPDIENVELOPE>::value);
static_assert(TypeMatch<decltype(DIEFFECT::cbTypeSpecificParams), DWORD>::value);
static_assert(TypeMatch<decltype(DIEFFECT::lpvTypeSpecificParams), LPVOID>::value);
static_assert(TypeMatch<decltype(DIEFFECT::dwStartDelay), DWORD>::value);

static_assert(offsetof(DIEFFECT, dwSize) == 0);
static_assert(offsetof(DIEFFECT, dwFlags) == 4);
static_assert(offsetof(DIEFFECT, dwDuration) == 8);
static_assert(offsetof(DIEFFECT, dwSamplePeriod) == 0xC);
static_assert(offsetof(DIEFFECT, dwGain) == 0x10);
static_assert(offsetof(DIEFFECT, dwTriggerButton) == 0x14);
static_assert(offsetof(DIEFFECT, dwTriggerRepeatInterval) == 0x18);
static_assert(offsetof(DIEFFECT, cAxes) == 0x1C);
static_assert(offsetof(DIEFFECT, rgdwAxes) == 0x20);
static_assert(offsetof(DIEFFECT, rglDirection) == 0x24);
static_assert(offsetof(DIEFFECT, lpEnvelope) == 0x28);
static_assert(offsetof(DIEFFECT, cbTypeSpecificParams) == 0x2C);
static_assert(offsetof(DIEFFECT, lpvTypeSpecificParams) == 0x30);
static_assert(offsetof(DIEFFECT, dwStartDelay) == 0x34);

static_assert(sizeof(DIEFFECT) == 56);

typedef DIEFFECT * LPDIEFFECT;
typedef const DIEFFECT * LPCDIEFFECT;

static_assert(TypeMatch<LPDIEFFECT, DIEFFECT *>::value);
static_assert(TypeMatch<LPCDIEFFECT, const DIEFFECT *>::value);

static_assert(sizeof(LPDIEFFECT) == 4);
static_assert(sizeof(LPCDIEFFECT) == 4);

// DIFILEEFFECT

struct DIFILEEFFECT
{
	DWORD dwSize; // 0
	GUID GuidEffect; // 4
	LPCDIEFFECT lpDiEffect; // 0x14
	CHAR szFriendlyName[260]; // 0x18
};

static_assert(TypeMatch<decltype(DIFILEEFFECT::dwSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIFILEEFFECT::GuidEffect), GUID>::value);
static_assert(TypeMatch<decltype(DIFILEEFFECT::lpDiEffect), LPCDIEFFECT>::value);
static_assert(TypeMatch<decltype(DIFILEEFFECT::szFriendlyName), CHAR[260]>::value);

static_assert(offsetof(DIFILEEFFECT, dwSize) == 0);
static_assert(offsetof(DIFILEEFFECT, GuidEffect) == 4);
static_assert(offsetof(DIFILEEFFECT, lpDiEffect) == 0x14);
static_assert(offsetof(DIFILEEFFECT, szFriendlyName) == 0x18);

static_assert(sizeof(DIFILEEFFECT) == 284);

typedef DIFILEEFFECT * LPDIFILEEFFECT;
typedef const DIFILEEFFECT * LPCDIFILEEFFECT;

static_assert(TypeMatch<LPDIFILEEFFECT, DIFILEEFFECT *>::value);
static_assert(TypeMatch<LPCDIFILEEFFECT, const DIFILEEFFECT *>::value);

static_assert(sizeof(LPDIFILEEFFECT) == 4);
static_assert(sizeof(LPCDIFILEEFFECT) == 4);

// DIEFFESCAPE

struct DIEFFESCAPE
{
	DWORD dwSize; // 0
	DWORD dwCommand; // 4
	LPVOID lpvInBuffer; // 8
	DWORD cbInBuffer; // 0xC
	LPVOID lpvOutBuffer; // 0x10
	DWORD cbOutBuffer; // 0x14
};

static_assert(TypeMatch<decltype(DIEFFESCAPE::dwSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIEFFESCAPE::dwCommand), DWORD>::value);
static_assert(TypeMatch<decltype(DIEFFESCAPE::lpvInBuffer), LPVOID>::value);
static_assert(TypeMatch<decltype(DIEFFESCAPE::cbInBuffer), DWORD>::value);
static_assert(TypeMatch<decltype(DIEFFESCAPE::lpvOutBuffer), LPVOID>::value);
static_assert(TypeMatch<decltype(DIEFFESCAPE::cbOutBuffer), DWORD>::value);

static_assert(offsetof(DIEFFESCAPE, dwSize) == 0);
static_assert(offsetof(DIEFFESCAPE, dwCommand) == 4);
static_assert(offsetof(DIEFFESCAPE, lpvInBuffer) == 8);
static_assert(offsetof(DIEFFESCAPE, cbInBuffer) == 0xC);
static_assert(offsetof(DIEFFESCAPE, lpvOutBuffer) == 0x10);
static_assert(offsetof(DIEFFESCAPE, cbOutBuffer) == 0x14);

static_assert(sizeof(DIEFFESCAPE) == 24);

typedef DIEFFESCAPE * LPDIEFFESCAPE;

static_assert(TypeMatch<LPDIEFFESCAPE, DIEFFESCAPE *>::value);

static_assert(sizeof(LPDIEFFESCAPE) == 4);

// DIEFFECTINFOA

struct DIEFFECTINFOA
{
	DWORD dwSize; // 0
	GUID guid; // 4
	DWORD dwEffType; // 0x14
	DWORD dwStaticParams; // 0x18
	DWORD dwDynamicParams; // 0x1C
	CHAR tszName[260]; // 0x20
};

static_assert(TypeMatch<decltype(DIEFFECTINFOA::dwSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIEFFECTINFOA::guid), GUID>::value);
static_assert(TypeMatch<decltype(DIEFFECTINFOA::dwEffType), DWORD>::value);
static_assert(TypeMatch<decltype(DIEFFECTINFOA::dwStaticParams), DWORD>::value);
static_assert(TypeMatch<decltype(DIEFFECTINFOA::dwDynamicParams), DWORD>::value);
static_assert(TypeMatch<decltype(DIEFFECTINFOA::tszName), CHAR[260]>::value);

static_assert(offsetof(DIEFFECTINFOA, dwSize) == 0);
static_assert(offsetof(DIEFFECTINFOA, guid) == 4);
static_assert(offsetof(DIEFFECTINFOA, dwEffType) == 0x14);
static_assert(offsetof(DIEFFECTINFOA, dwStaticParams) == 0x18);
static_assert(offsetof(DIEFFECTINFOA, dwDynamicParams) == 0x1C);
static_assert(offsetof(DIEFFECTINFOA, tszName) == 0x20);

static_assert(sizeof(DIEFFECTINFOA) == 292);

typedef DIEFFECTINFOA * LPDIEFFECTINFOA;
typedef const DIEFFECTINFOA * LPCDIEFFECTINFOA;

static_assert(TypeMatch<LPDIEFFECTINFOA, DIEFFECTINFOA *>::value);
static_assert(TypeMatch<LPCDIEFFECTINFOA, const DIEFFECTINFOA *>::value);

static_assert(sizeof(LPDIEFFECTINFOA) == 4);
static_assert(sizeof(LPCDIEFFECTINFOA) == 4);

// DIEFFECTINFOW

struct DIEFFECTINFOW
{
	DWORD dwSize; // 0
	GUID guid; // 4
	DWORD dwEffType; // 0x14
	DWORD dwStaticParams; // 0x18
	DWORD dwDynamicParams; // 0x1C
	WCHAR tszName[260]; // 0x20
};

static_assert(TypeMatch<decltype(DIEFFECTINFOW::dwSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIEFFECTINFOW::guid), GUID>::value);
static_assert(TypeMatch<decltype(DIEFFECTINFOW::dwEffType), DWORD>::value);
static_assert(TypeMatch<decltype(DIEFFECTINFOW::dwStaticParams), DWORD>::value);
static_assert(TypeMatch<decltype(DIEFFECTINFOW::dwDynamicParams), DWORD>::value);
static_assert(TypeMatch<decltype(DIEFFECTINFOW::tszName), WCHAR[260]>::value);

static_assert(offsetof(DIEFFECTINFOW, dwSize) == 0);
static_assert(offsetof(DIEFFECTINFOW, guid) == 4);
static_assert(offsetof(DIEFFECTINFOW, dwEffType) == 0x14);
static_assert(offsetof(DIEFFECTINFOW, dwStaticParams) == 0x18);
static_assert(offsetof(DIEFFECTINFOW, dwDynamicParams) == 0x1C);
static_assert(offsetof(DIEFFECTINFOW, tszName) == 0x20);

static_assert(sizeof(DIEFFECTINFOW) == 552);

typedef DIEFFECTINFOW * LPDIEFFECTINFOW;
typedef const DIEFFECTINFOW * LPCDIEFFECTINFOW;

static_assert(TypeMatch<LPDIEFFECTINFOW, DIEFFECTINFOW *>::value);
static_assert(TypeMatch<LPCDIEFFECTINFOW, const DIEFFECTINFOW *>::value);

static_assert(sizeof(LPDIEFFECTINFOW) == 4);
static_assert(sizeof(LPCDIEFFECTINFOW) == 4);

// DIACTIONA

struct DIACTIONA
{
	UINT_PTR uAppData; // 0
	DWORD dwSemantic; // 4
	DWORD dwFlags; // 8
	union
	{
		LPCSTR lptszActionName; // 0xC
		UINT uResIdString; // 0xC
	}; // 0xC
	GUID guidInstance; // 0x10
	DWORD dwObjID; // 0x20
	DWORD dwHow; // 0x24
};

static_assert(TypeMatch<decltype(DIACTIONA::uAppData), UINT_PTR>::value);
static_assert(TypeMatch<decltype(DIACTIONA::dwSemantic), DWORD>::value);
static_assert(TypeMatch<decltype(DIACTIONA::dwFlags), DWORD>::value);
static_assert(TypeMatch<decltype(DIACTIONA::lptszActionName), LPCSTR>::value);
static_assert(TypeMatch<decltype(DIACTIONA::uResIdString), UINT>::value);
static_assert(TypeMatch<decltype(DIACTIONA::guidInstance), GUID>::value);
static_assert(TypeMatch<decltype(DIACTIONA::dwObjID), DWORD>::value);
static_assert(TypeMatch<decltype(DIACTIONA::dwHow), DWORD>::value);

static_assert(offsetof(DIACTIONA, uAppData) == 0);
static_assert(offsetof(DIACTIONA, dwSemantic) == 4);
static_assert(offsetof(DIACTIONA, dwFlags) == 8);
static_assert(offsetof(DIACTIONA, lptszActionName) == 0xC);
static_assert(offsetof(DIACTIONA, uResIdString) == 0xC);
static_assert(offsetof(DIACTIONA, guidInstance) == 0x10);
static_assert(offsetof(DIACTIONA, dwObjID) == 0x20);
static_assert(offsetof(DIACTIONA, dwHow) == 0x24);

static_assert(sizeof(DIACTIONA) == 40);

typedef DIACTIONA * LPDIACTIONA;
typedef const DIACTIONA * LPCDIACTIONA;

static_assert(TypeMatch<LPDIACTIONA, DIACTIONA *>::value);
static_assert(TypeMatch<LPCDIACTIONA, const DIACTIONA *>::value);

static_assert(sizeof(LPDIACTIONA) == 4);
static_assert(sizeof(LPCDIACTIONA) == 4);

// DIACTIONW

struct DIACTIONW
{
	UINT_PTR uAppData; // 0
	DWORD dwSemantic; // 4
	DWORD dwFlags; // 8
	union
	{
		LPCWSTR lptszActionName; // 0xC
		UINT uResIdString; // 0xC
	}; // 0xC
	GUID guidInstance; // 0x10
	DWORD dwObjID; // 0x20
	DWORD dwHow; // 0x24
};

static_assert(TypeMatch<decltype(DIACTIONW::uAppData), UINT_PTR>::value);
static_assert(TypeMatch<decltype(DIACTIONW::dwSemantic), DWORD>::value);
static_assert(TypeMatch<decltype(DIACTIONW::dwFlags), DWORD>::value);
static_assert(TypeMatch<decltype(DIACTIONW::lptszActionName), LPCWSTR>::value);
static_assert(TypeMatch<decltype(DIACTIONW::uResIdString), UINT>::value);
static_assert(TypeMatch<decltype(DIACTIONW::guidInstance), GUID>::value);
static_assert(TypeMatch<decltype(DIACTIONW::dwObjID), DWORD>::value);
static_assert(TypeMatch<decltype(DIACTIONW::dwHow), DWORD>::value);

static_assert(offsetof(DIACTIONW, uAppData) == 0);
static_assert(offsetof(DIACTIONW, dwSemantic) == 4);
static_assert(offsetof(DIACTIONW, dwFlags) == 8);
static_assert(offsetof(DIACTIONW, lptszActionName) == 0xC);
static_assert(offsetof(DIACTIONW, uResIdString) == 0xC);
static_assert(offsetof(DIACTIONW, guidInstance) == 0x10);
static_assert(offsetof(DIACTIONW, dwObjID) == 0x20);
static_assert(offsetof(DIACTIONW, dwHow) == 0x24);

static_assert(sizeof(DIACTIONW) == 40);

typedef DIACTIONW * LPDIACTIONW;
typedef const DIACTIONW * LPCDIACTIONW;

static_assert(TypeMatch<LPDIACTIONW, DIACTIONW *>::value);
static_assert(TypeMatch<LPCDIACTIONW, const DIACTIONW *>::value);

static_assert(sizeof(LPDIACTIONW) == 4);
static_assert(sizeof(LPCDIACTIONW) == 4);

// DIACTIONFORMATA

struct DIACTIONFORMATA
{
	DWORD dwSize; // 0
	DWORD dwActionSize; // 4
	DWORD dwDataSize; // 8
	DWORD dwNumActions; // 0xC
	LPDIACTIONA rgoAction; // 0x10
	GUID guidActionMap; // 0x14
	DWORD dwGenre; // 0x24
	DWORD dwBufferSize; // 0x28
	LONG lAxisMin; // 0x2C
	LONG lAxisMax; // 0x30
	HINSTANCE hInstString; // 0x34
	FILETIME ftTimeStamp; // 0x38
	DWORD dwCRC; // 0x40
	CHAR tszActionMap[260]; // 0x44
};

static_assert(TypeMatch<decltype(DIACTIONFORMATA::dwSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATA::dwActionSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATA::dwDataSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATA::dwNumActions), DWORD>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATA::rgoAction), LPDIACTIONA>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATA::guidActionMap), GUID>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATA::dwGenre), DWORD>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATA::dwBufferSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATA::lAxisMin), LONG>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATA::lAxisMax), LONG>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATA::hInstString), HINSTANCE>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATA::ftTimeStamp), FILETIME>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATA::dwCRC), DWORD>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATA::tszActionMap), CHAR[260]>::value);

static_assert(offsetof(DIACTIONFORMATA, dwSize) == 0);
static_assert(offsetof(DIACTIONFORMATA, dwActionSize) == 4);
static_assert(offsetof(DIACTIONFORMATA, dwDataSize) == 8);
static_assert(offsetof(DIACTIONFORMATA, dwNumActions) == 0xC);
static_assert(offsetof(DIACTIONFORMATA, rgoAction) == 0x10);
static_assert(offsetof(DIACTIONFORMATA, guidActionMap) == 0x14);
static_assert(offsetof(DIACTIONFORMATA, dwGenre) == 0x24);
static_assert(offsetof(DIACTIONFORMATA, dwBufferSize) == 0x28);
static_assert(offsetof(DIACTIONFORMATA, lAxisMin) == 0x2C);
static_assert(offsetof(DIACTIONFORMATA, lAxisMax) == 0x30);
static_assert(offsetof(DIACTIONFORMATA, hInstString) == 0x34);
static_assert(offsetof(DIACTIONFORMATA, ftTimeStamp) == 0x38);
static_assert(offsetof(DIACTIONFORMATA, dwCRC) == 0x40);
static_assert(offsetof(DIACTIONFORMATA, tszActionMap) == 0x44);

static_assert(sizeof(DIACTIONFORMATA) == 328);

typedef DIACTIONFORMATA * LPDIACTIONFORMATA;
typedef const DIACTIONFORMATA * LPCDIACTIONFORMATA;

static_assert(TypeMatch<LPDIACTIONFORMATA, DIACTIONFORMATA *>::value);
static_assert(TypeMatch<LPCDIACTIONFORMATA, const DIACTIONFORMATA *>::value);

static_assert(sizeof(LPDIACTIONFORMATA) == 4);
static_assert(sizeof(LPCDIACTIONFORMATA) == 4);

// DIACTIONFORMATW

struct DIACTIONFORMATW
{
	DWORD dwSize; // 0
	DWORD dwActionSize; // 4
	DWORD dwDataSize; // 8
	DWORD dwNumActions; // 0xC
	LPDIACTIONW rgoAction; // 0x10
	GUID guidActionMap; // 0x14
	DWORD dwGenre; // 0x24
	DWORD dwBufferSize; // 0x28
	LONG lAxisMin; // 0x2C
	LONG lAxisMax; // 0x30
	HINSTANCE hInstString; // 0x34
	FILETIME ftTimeStamp; // 0x38
	DWORD dwCRC; // 0x40
	WCHAR tszActionMap[260]; // 0x44
};

static_assert(TypeMatch<decltype(DIACTIONFORMATW::dwSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATW::dwActionSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATW::dwDataSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATW::dwNumActions), DWORD>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATW::rgoAction), LPDIACTIONW>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATW::guidActionMap), GUID>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATW::dwGenre), DWORD>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATW::dwBufferSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATW::lAxisMin), LONG>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATW::lAxisMax), LONG>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATW::hInstString), HINSTANCE>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATW::ftTimeStamp), FILETIME>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATW::dwCRC), DWORD>::value);
static_assert(TypeMatch<decltype(DIACTIONFORMATW::tszActionMap), WCHAR[260]>::value);

static_assert(offsetof(DIACTIONFORMATW, dwSize) == 0);
static_assert(offsetof(DIACTIONFORMATW, dwActionSize) == 4);
static_assert(offsetof(DIACTIONFORMATW, dwDataSize) == 8);
static_assert(offsetof(DIACTIONFORMATW, dwNumActions) == 0xC);
static_assert(offsetof(DIACTIONFORMATW, rgoAction) == 0x10);
static_assert(offsetof(DIACTIONFORMATW, guidActionMap) == 0x14);
static_assert(offsetof(DIACTIONFORMATW, dwGenre) == 0x24);
static_assert(offsetof(DIACTIONFORMATW, dwBufferSize) == 0x28);
static_assert(offsetof(DIACTIONFORMATW, lAxisMin) == 0x2C);
static_assert(offsetof(DIACTIONFORMATW, lAxisMax) == 0x30);
static_assert(offsetof(DIACTIONFORMATW, hInstString) == 0x34);
static_assert(offsetof(DIACTIONFORMATW, ftTimeStamp) == 0x38);
static_assert(offsetof(DIACTIONFORMATW, dwCRC) == 0x40);
static_assert(offsetof(DIACTIONFORMATW, tszActionMap) == 0x44);

static_assert(sizeof(DIACTIONFORMATW) == 588);

typedef DIACTIONFORMATW * LPDIACTIONFORMATW;
typedef const DIACTIONFORMATW * LPCDIACTIONFORMATW;

static_assert(TypeMatch<LPDIACTIONFORMATW, DIACTIONFORMATW *>::value);
static_assert(TypeMatch<LPCDIACTIONFORMATW, const DIACTIONFORMATW *>::value);

static_assert(sizeof(LPDIACTIONFORMATW) == 4);
static_assert(sizeof(LPCDIACTIONFORMATW) == 4);

// DIDEVICEIMAGEINFOA

struct DIDEVICEIMAGEINFOA
{
	CHAR tszImagePath[260]; // 0
	DWORD dwFlags; // 0x104
	DWORD dwViewID; // 0x108
	RECT rcOverlay; // 0x10C
	DWORD dwObjID; // 0x11C
	DWORD dwcValidPts; // 0x120
	POINT rgptCalloutLine[5]; // 0x124
	RECT rcCalloutRect; // 0x14C
	DWORD dwTextAlign; // 0x15C
};

static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOA::tszImagePath), CHAR[260]>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOA::dwFlags), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOA::dwViewID), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOA::rcOverlay), RECT>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOA::dwObjID), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOA::dwcValidPts), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOA::rgptCalloutLine), POINT[5]>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOA::rcCalloutRect), RECT>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOA::dwTextAlign), DWORD>::value);

static_assert(offsetof(DIDEVICEIMAGEINFOA, tszImagePath) == 0);
static_assert(offsetof(DIDEVICEIMAGEINFOA, dwFlags) == 0x104);
static_assert(offsetof(DIDEVICEIMAGEINFOA, dwViewID) == 0x108);
static_assert(offsetof(DIDEVICEIMAGEINFOA, rcOverlay) == 0x10C);
static_assert(offsetof(DIDEVICEIMAGEINFOA, dwObjID) == 0x11C);
static_assert(offsetof(DIDEVICEIMAGEINFOA, dwcValidPts) == 0x120);
static_assert(offsetof(DIDEVICEIMAGEINFOA, rgptCalloutLine) == 0x124);
static_assert(offsetof(DIDEVICEIMAGEINFOA, rcCalloutRect) == 0x14C);
static_assert(offsetof(DIDEVICEIMAGEINFOA, dwTextAlign) == 0x15C);

static_assert(sizeof(DIDEVICEIMAGEINFOA) == 352);

typedef DIDEVICEIMAGEINFOA * LPDIDEVICEIMAGEINFOA;
typedef const DIDEVICEIMAGEINFOA * LPCDIDEVICEIMAGEINFOA;

static_assert(TypeMatch<LPDIDEVICEIMAGEINFOA, DIDEVICEIMAGEINFOA *>::value);
static_assert(TypeMatch<LPCDIDEVICEIMAGEINFOA, const DIDEVICEIMAGEINFOA *>::value);

static_assert(sizeof(LPDIDEVICEIMAGEINFOA) == 4);
static_assert(sizeof(LPCDIDEVICEIMAGEINFOA) == 4);

// DIDEVICEIMAGEINFOW

struct DIDEVICEIMAGEINFOW
{
	WCHAR tszImagePath[260]; // 0
	DWORD dwFlags; // 0x208
	DWORD dwViewID; // 0x20C
	RECT rcOverlay; // 0x210
	DWORD dwObjID; // 0x220
	DWORD dwcValidPts; // 0x224
	POINT rgptCalloutLine[5]; // 0x228
	RECT rcCalloutRect; // 0x250
	DWORD dwTextAlign; // 0x260
};

static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOW::tszImagePath), WCHAR[260]>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOW::dwFlags), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOW::dwViewID), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOW::rcOverlay), RECT>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOW::dwObjID), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOW::dwcValidPts), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOW::rgptCalloutLine), POINT[5]>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOW::rcCalloutRect), RECT>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOW::dwTextAlign), DWORD>::value);

static_assert(offsetof(DIDEVICEIMAGEINFOW, tszImagePath) == 0);
static_assert(offsetof(DIDEVICEIMAGEINFOW, dwFlags) == 0x208);
static_assert(offsetof(DIDEVICEIMAGEINFOW, dwViewID) == 0x20C);
static_assert(offsetof(DIDEVICEIMAGEINFOW, rcOverlay) == 0x210);
static_assert(offsetof(DIDEVICEIMAGEINFOW, dwObjID) == 0x220);
static_assert(offsetof(DIDEVICEIMAGEINFOW, dwcValidPts) == 0x224);
static_assert(offsetof(DIDEVICEIMAGEINFOW, rgptCalloutLine) == 0x228);
static_assert(offsetof(DIDEVICEIMAGEINFOW, rcCalloutRect) == 0x250);
static_assert(offsetof(DIDEVICEIMAGEINFOW, dwTextAlign) == 0x260);

static_assert(sizeof(DIDEVICEIMAGEINFOW) == 612);

typedef DIDEVICEIMAGEINFOW * LPDIDEVICEIMAGEINFOW;
typedef const DIDEVICEIMAGEINFOW * LPCDIDEVICEIMAGEINFOW;

static_assert(TypeMatch<LPDIDEVICEIMAGEINFOW, DIDEVICEIMAGEINFOW *>::value);
static_assert(TypeMatch<LPCDIDEVICEIMAGEINFOW, const DIDEVICEIMAGEINFOW *>::value);

static_assert(sizeof(LPDIDEVICEIMAGEINFOW) == 4);
static_assert(sizeof(LPCDIDEVICEIMAGEINFOW) == 4);

// DIDEVICEIMAGEINFOHEADERA

struct DIDEVICEIMAGEINFOHEADERA
{
	DWORD dwSize; // 0
	DWORD dwSizeImageInfo; // 4
	DWORD dwcViews; // 8
	DWORD dwcButtons; // 0xC
	DWORD dwcAxes; // 0x10
	DWORD dwcPOVs; // 0x14
	DWORD dwBufferSize; // 0x18
	DWORD dwBufferUsed; // 0x1C
	LPDIDEVICEIMAGEINFOA lprgImageInfoArray; // 0x20
};

static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOHEADERA::dwSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOHEADERA::dwSizeImageInfo), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOHEADERA::dwcViews), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOHEADERA::dwcButtons), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOHEADERA::dwcAxes), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOHEADERA::dwcPOVs), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOHEADERA::dwBufferSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOHEADERA::dwBufferUsed), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOHEADERA::lprgImageInfoArray), LPDIDEVICEIMAGEINFOA>::value);

static_assert(offsetof(DIDEVICEIMAGEINFOHEADERA, dwSize) == 0);
static_assert(offsetof(DIDEVICEIMAGEINFOHEADERA, dwSizeImageInfo) == 4);
static_assert(offsetof(DIDEVICEIMAGEINFOHEADERA, dwcViews) == 8);
static_assert(offsetof(DIDEVICEIMAGEINFOHEADERA, dwcButtons) == 0xC);
static_assert(offsetof(DIDEVICEIMAGEINFOHEADERA, dwcAxes) == 0x10);
static_assert(offsetof(DIDEVICEIMAGEINFOHEADERA, dwcPOVs) == 0x14);
static_assert(offsetof(DIDEVICEIMAGEINFOHEADERA, dwBufferSize) == 0x18);
static_assert(offsetof(DIDEVICEIMAGEINFOHEADERA, dwBufferUsed) == 0x1C);
static_assert(offsetof(DIDEVICEIMAGEINFOHEADERA, lprgImageInfoArray) == 0x20);

static_assert(sizeof(DIDEVICEIMAGEINFOHEADERA) == 36);

typedef DIDEVICEIMAGEINFOHEADERA * LPDIDEVICEIMAGEINFOHEADERA;
typedef const DIDEVICEIMAGEINFOHEADERA * LPCDIDEVICEIMAGEINFOHEADERA;

static_assert(TypeMatch<LPDIDEVICEIMAGEINFOHEADERA, DIDEVICEIMAGEINFOHEADERA *>::value);
static_assert(TypeMatch<LPCDIDEVICEIMAGEINFOHEADERA, const DIDEVICEIMAGEINFOHEADERA *>::value);

static_assert(sizeof(LPDIDEVICEIMAGEINFOHEADERA) == 4);
static_assert(sizeof(LPCDIDEVICEIMAGEINFOHEADERA) == 4);

// DIDEVICEIMAGEINFOHEADERW

struct DIDEVICEIMAGEINFOHEADERW
{
	DWORD dwSize; // 0
	DWORD dwSizeImageInfo; // 4
	DWORD dwcViews; // 8
	DWORD dwcButtons; // 0xC
	DWORD dwcAxes; // 0x10
	DWORD dwcPOVs; // 0x14
	DWORD dwBufferSize; // 0x18
	DWORD dwBufferUsed; // 0x1C
	LPDIDEVICEIMAGEINFOW lprgImageInfoArray; // 0x20
};

static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOHEADERW::dwSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOHEADERW::dwSizeImageInfo), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOHEADERW::dwcViews), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOHEADERW::dwcButtons), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOHEADERW::dwcAxes), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOHEADERW::dwcPOVs), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOHEADERW::dwBufferSize), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOHEADERW::dwBufferUsed), DWORD>::value);
static_assert(TypeMatch<decltype(DIDEVICEIMAGEINFOHEADERW::lprgImageInfoArray), LPDIDEVICEIMAGEINFOW>::value);

static_assert(offsetof(DIDEVICEIMAGEINFOHEADERW, dwSize) == 0);
static_assert(offsetof(DIDEVICEIMAGEINFOHEADERW, dwSizeImageInfo) == 4);
static_assert(offsetof(DIDEVICEIMAGEINFOHEADERW, dwcViews) == 8);
static_assert(offsetof(DIDEVICEIMAGEINFOHEADERW, dwcButtons) == 0xC);
static_assert(offsetof(DIDEVICEIMAGEINFOHEADERW, dwcAxes) == 0x10);
static_assert(offsetof(DIDEVICEIMAGEINFOHEADERW, dwcPOVs) == 0x14);
static_assert(offsetof(DIDEVICEIMAGEINFOHEADERW, dwBufferSize) == 0x18);
static_assert(offsetof(DIDEVICEIMAGEINFOHEADERW, dwBufferUsed) == 0x1C);
static_assert(offsetof(DIDEVICEIMAGEINFOHEADERW, lprgImageInfoArray) == 0x20);

static_assert(sizeof(DIDEVICEIMAGEINFOHEADERW) == 36);

typedef DIDEVICEIMAGEINFOHEADERW * LPDIDEVICEIMAGEINFOHEADERW;
typedef const DIDEVICEIMAGEINFOHEADERW * LPCDIDEVICEIMAGEINFOHEADERW;

static_assert(TypeMatch<LPDIDEVICEIMAGEINFOHEADERW, DIDEVICEIMAGEINFOHEADERW *>::value);
static_assert(TypeMatch<LPCDIDEVICEIMAGEINFOHEADERW, const DIDEVICEIMAGEINFOHEADERW *>::value);

static_assert(sizeof(LPDIDEVICEIMAGEINFOHEADERW) == 4);
static_assert(sizeof(LPCDIDEVICEIMAGEINFOHEADERW) == 4);

// DICOLORSET

struct DICOLORSET
{
	DWORD dwSize; // 0
	D3DCOLOR cTextFore; // 4
	D3DCOLOR cTextHighlight; // 8
	D3DCOLOR cCalloutLine; // 0xC
	D3DCOLOR cCalloutHighlight; // 0x10
	D3DCOLOR cBorder; // 0x14
	D3DCOLOR cControlFill; // 0x18
	D3DCOLOR cHighlightFill; // 0x1C
	D3DCOLOR cAreaFill; // 0x20
};

static_assert(TypeMatch<decltype(DICOLORSET::dwSize), DWORD>::value);
static_assert(TypeMatch<decltype(DICOLORSET::cTextFore), D3DCOLOR>::value);
static_assert(TypeMatch<decltype(DICOLORSET::cTextHighlight), D3DCOLOR>::value);
static_assert(TypeMatch<decltype(DICOLORSET::cCalloutLine), D3DCOLOR>::value);
static_assert(TypeMatch<decltype(DICOLORSET::cCalloutHighlight), D3DCOLOR>::value);
static_assert(TypeMatch<decltype(DICOLORSET::cBorder), D3DCOLOR>::value);
static_assert(TypeMatch<decltype(DICOLORSET::cControlFill), D3DCOLOR>::value);
static_assert(TypeMatch<decltype(DICOLORSET::cHighlightFill), D3DCOLOR>::value);
static_assert(TypeMatch<decltype(DICOLORSET::cAreaFill), D3DCOLOR>::value);

static_assert(offsetof(DICOLORSET, dwSize) == 0);
static_assert(offsetof(DICOLORSET, cTextFore) == 4);
static_assert(offsetof(DICOLORSET, cTextHighlight) == 8);
static_assert(offsetof(DICOLORSET, cCalloutLine) == 0xC);
static_assert(offsetof(DICOLORSET, cCalloutHighlight) == 0x10);
static_assert(offsetof(DICOLORSET, cBorder) == 0x14);
static_assert(offsetof(DICOLORSET, cControlFill) == 0x18);
static_assert(offsetof(DICOLORSET, cHighlightFill) == 0x1C);
static_assert(offsetof(DICOLORSET, cAreaFill) == 0x20);

static_assert(sizeof(DICOLORSET) == 36);

typedef DICOLORSET * LPDICOLORSET;
typedef const DICOLORSET * LPCDICOLORSET;

static_assert(TypeMatch<LPDICOLORSET, DICOLORSET *>::value);
static_assert(TypeMatch<LPCDICOLORSET, const DICOLORSET *>::value);

static_assert(sizeof(LPDICOLORSET) == 4);
static_assert(sizeof(LPCDICOLORSET) == 4);

// DICONFIGUREDEVICESPARAMSA

struct DICONFIGUREDEVICESPARAMSA
{
	DWORD dwSize; // 0
	DWORD dwcUsers; // 4
	LPSTR lptszUserNames; // 8
	DWORD dwcFormats; // 0xC
	LPDIACTIONFORMATA lprgFormats; // 0x10
	HWND hwnd; // 0x14
	DICOLORSET dics; // 0x18
	IUnknown* lpUnkDDSTarget; // 0x3C
};

static_assert(TypeMatch<decltype(DICONFIGUREDEVICESPARAMSA::dwSize), DWORD>::value);
static_assert(TypeMatch<decltype(DICONFIGUREDEVICESPARAMSA::dwcUsers), DWORD>::value);
static_assert(TypeMatch<decltype(DICONFIGUREDEVICESPARAMSA::lptszUserNames), LPSTR>::value);
static_assert(TypeMatch<decltype(DICONFIGUREDEVICESPARAMSA::dwcFormats), DWORD>::value);
static_assert(TypeMatch<decltype(DICONFIGUREDEVICESPARAMSA::lprgFormats), LPDIACTIONFORMATA>::value);
static_assert(TypeMatch<decltype(DICONFIGUREDEVICESPARAMSA::hwnd), HWND>::value);
static_assert(TypeMatch<decltype(DICONFIGUREDEVICESPARAMSA::dics), DICOLORSET>::value);
static_assert(TypeMatch<decltype(DICONFIGUREDEVICESPARAMSA::lpUnkDDSTarget), IUnknown*>::value);

static_assert(offsetof(DICONFIGUREDEVICESPARAMSA, dwSize) == 0);
static_assert(offsetof(DICONFIGUREDEVICESPARAMSA, dwcUsers) == 4);
static_assert(offsetof(DICONFIGUREDEVICESPARAMSA, lptszUserNames) == 8);
static_assert(offsetof(DICONFIGUREDEVICESPARAMSA, dwcFormats) == 0xC);
static_assert(offsetof(DICONFIGUREDEVICESPARAMSA, lprgFormats) == 0x10);
static_assert(offsetof(DICONFIGUREDEVICESPARAMSA, hwnd) == 0x14);
static_assert(offsetof(DICONFIGUREDEVICESPARAMSA, dics) == 0x18);
static_assert(offsetof(DICONFIGUREDEVICESPARAMSA, lpUnkDDSTarget) == 0x3C);

static_assert(sizeof(DICONFIGUREDEVICESPARAMSA) == 64);

typedef DICONFIGUREDEVICESPARAMSA * LPDICONFIGUREDEVICESPARAMSA;
typedef const DICONFIGUREDEVICESPARAMSA * LPCDICONFIGUREDEVICESPARAMSA;

static_assert(TypeMatch<LPDICONFIGUREDEVICESPARAMSA, DICONFIGUREDEVICESPARAMSA *>::value);
static_assert(TypeMatch<LPCDICONFIGUREDEVICESPARAMSA, const DICONFIGUREDEVICESPARAMSA *>::value);

static_assert(sizeof(LPDICONFIGUREDEVICESPARAMSA) == 4);
static_assert(sizeof(LPCDICONFIGUREDEVICESPARAMSA) == 4);

// DICONFIGUREDEVICESPARAMSW

struct DICONFIGUREDEVICESPARAMSW
{
	DWORD dwSize; // 0
	DWORD dwcUsers; // 4
	LPWSTR lptszUserNames; // 8
	DWORD dwcFormats; // 0xC
	LPDIACTIONFORMATW lprgFormats; // 0x10
	HWND hwnd; // 0x14
	DICOLORSET dics; // 0x18
	IUnknown* lpUnkDDSTarget; // 0x3C
};

static_assert(TypeMatch<decltype(DICONFIGUREDEVICESPARAMSW::dwSize), DWORD>::value);
static_assert(TypeMatch<decltype(DICONFIGUREDEVICESPARAMSW::dwcUsers), DWORD>::value);
static_assert(TypeMatch<decltype(DICONFIGUREDEVICESPARAMSW::lptszUserNames), LPWSTR>::value);
static_assert(TypeMatch<decltype(DICONFIGUREDEVICESPARAMSW::dwcFormats), DWORD>::value);
static_assert(TypeMatch<decltype(DICONFIGUREDEVICESPARAMSW::lprgFormats), LPDIACTIONFORMATW>::value);
static_assert(TypeMatch<decltype(DICONFIGUREDEVICESPARAMSW::hwnd), HWND>::value);
static_assert(TypeMatch<decltype(DICONFIGUREDEVICESPARAMSW::dics), DICOLORSET>::value);
static_assert(TypeMatch<decltype(DICONFIGUREDEVICESPARAMSW::lpUnkDDSTarget), IUnknown*>::value);

static_assert(offsetof(DICONFIGUREDEVICESPARAMSW, dwSize) == 0);
static_assert(offsetof(DICONFIGUREDEVICESPARAMSW, dwcUsers) == 4);
static_assert(offsetof(DICONFIGUREDEVICESPARAMSW, lptszUserNames) == 8);
static_assert(offsetof(DICONFIGUREDEVICESPARAMSW, dwcFormats) == 0xC);
static_assert(offsetof(DICONFIGUREDEVICESPARAMSW, lprgFormats) == 0x10);
static_assert(offsetof(DICONFIGUREDEVICESPARAMSW, hwnd) == 0x14);
static_assert(offsetof(DICONFIGUREDEVICESPARAMSW, dics) == 0x18);
static_assert(offsetof(DICONFIGUREDEVICESPARAMSW, lpUnkDDSTarget) == 0x3C);

static_assert(sizeof(DICONFIGUREDEVICESPARAMSW) == 64);

typedef DICONFIGUREDEVICESPARAMSW * LPDICONFIGUREDEVICESPARAMSW;
typedef const DICONFIGUREDEVICESPARAMSW * LPCDICONFIGUREDEVICESPARAMSW;

static_assert(TypeMatch<LPDICONFIGUREDEVICESPARAMSW, DICONFIGUREDEVICESPARAMSW *>::value);
static_assert(TypeMatch<LPCDICONFIGUREDEVICESPARAMSW, const DICONFIGUREDEVICESPARAMSW *>::value);

static_assert(sizeof(LPDICONFIGUREDEVICESPARAMSW) == 4);
static_assert(sizeof(LPCDICONFIGUREDEVICESPARAMSW) == 4);

// DIJOYSTATE

struct DIJOYSTATE
{
	LONG lX; // 0
	LONG lY; // 4
	LONG lZ; // 8
	LONG lRx; // 0xC
	LONG lRy; // 0x10
	LONG lRz; // 0x14
	LONG rglSlider[2]; // 0x18
	DWORD rgdwPOV[4]; // 0x20
	BYTE rgbButtons[32]; // 0x30
};

static_assert(TypeMatch<decltype(DIJOYSTATE::lX), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE::lY), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE::lZ), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE::lRx), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE::lRy), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE::lRz), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE::rglSlider), LONG[2]>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE::rgdwPOV), DWORD[4]>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE::rgbButtons), BYTE[32]>::value);

static_assert(offsetof(DIJOYSTATE, lX) == 0);
static_assert(offsetof(DIJOYSTATE, lY) == 4);
static_assert(offsetof(DIJOYSTATE, lZ) == 8);
static_assert(offsetof(DIJOYSTATE, lRx) == 0xC);
static_assert(offsetof(DIJOYSTATE, lRy) == 0x10);
static_assert(offsetof(DIJOYSTATE, lRz) == 0x14);
static_assert(offsetof(DIJOYSTATE, rglSlider) == 0x18);
static_assert(offsetof(DIJOYSTATE, rgdwPOV) == 0x20);
static_assert(offsetof(DIJOYSTATE, rgbButtons) == 0x30);

static_assert(sizeof(DIJOYSTATE) == 80);

typedef DIJOYSTATE * LPDIJOYSTATE;

static_assert(TypeMatch<LPDIJOYSTATE, DIJOYSTATE *>::value);

static_assert(sizeof(LPDIJOYSTATE) == 4);

// DIJOYSTATE2

struct DIJOYSTATE2
{
	LONG lX; // 0
	LONG lY; // 4
	LONG lZ; // 8
	LONG lRx; // 0xC
	LONG lRy; // 0x10
	LONG lRz; // 0x14
	LONG rglSlider[2]; // 0x18
	DWORD rgdwPOV[4]; // 0x20
	BYTE rgbButtons[128]; // 0x30
	LONG lVX; // 0xB0
	LONG lVY; // 0xB4
	LONG lVZ; // 0xB8
	LONG lVRx; // 0xBC
	LONG lVRy; // 0xC0
	LONG lVRz; // 0xC4
	LONG rglVSlider[2]; // 0xC8
	LONG lAX; // 0xD0
	LONG lAY; // 0xD4
	LONG lAZ; // 0xD8
	LONG lARx; // 0xDC
	LONG lARy; // 0xE0
	LONG lARz; // 0xE4
	LONG rglASlider[2]; // 0xE8
	LONG lFX; // 0xF0
	LONG lFY; // 0xF4
	LONG lFZ; // 0xF8
	LONG lFRx; // 0xFC
	LONG lFRy; // 0x100
	LONG lFRz; // 0x104
	LONG rglFSlider[2]; // 0x108
};

static_assert(TypeMatch<decltype(DIJOYSTATE2::lX), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lY), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lZ), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lRx), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lRy), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lRz), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::rglSlider), LONG[2]>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::rgdwPOV), DWORD[4]>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::rgbButtons), BYTE[128]>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lVX), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lVY), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lVZ), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lVRx), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lVRy), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lVRz), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::rglVSlider), LONG[2]>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lAX), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lAY), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lAZ), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lARx), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lARy), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lARz), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::rglASlider), LONG[2]>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lFX), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lFY), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lFZ), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lFRx), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lFRy), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::lFRz), LONG>::value);
static_assert(TypeMatch<decltype(DIJOYSTATE2::rglFSlider), LONG[2]>::value);

static_assert(offsetof(DIJOYSTATE2, lX) == 0);
static_assert(offsetof(DIJOYSTATE2, lY) == 4);
static_assert(offsetof(DIJOYSTATE2, lZ) == 8);
static_assert(offsetof(DIJOYSTATE2, lRx) == 0xC);
static_assert(offsetof(DIJOYSTATE2, lRy) == 0x10);
static_assert(offsetof(DIJOYSTATE2, lRz) == 0x14);
static_assert(offsetof(DIJOYSTATE2, rglSlider) == 0x18);
static_assert(offsetof(DIJOYSTATE2, rgdwPOV) == 0x20);
static_assert(offsetof(DIJOYSTATE2, rgbButtons) == 0x30);
static_assert(offsetof(DIJOYSTATE2, lVX) == 0xB0);
static_assert(offsetof(DIJOYSTATE2, lVY) == 0xB4);
static_assert(offsetof(DIJOYSTATE2, lVZ) == 0xB8);
static_assert(offsetof(DIJOYSTATE2, lVRx) == 0xBC);
static_assert(offsetof(DIJOYSTATE2, lVRy) == 0xC0);
static_assert(offsetof(DIJOYSTATE2, lVRz) == 0xC4);
static_assert(offsetof(DIJOYSTATE2, rglVSlider) == 0xC8);
static_assert(offsetof(DIJOYSTATE2, lAX) == 0xD0);
static_assert(offsetof(DIJOYSTATE2, lAY) == 0xD4);
static_assert(offsetof(DIJOYSTATE2, lAZ) == 0xD8);
static_assert(offsetof(DIJOYSTATE2, lARx) == 0xDC);
static_assert(offsetof(DIJOYSTATE2, lARy) == 0xE0);
static_assert(offsetof(DIJOYSTATE2, lARz) == 0xE4);
static_assert(offsetof(DIJOYSTATE2, rglASlider) == 0xE8);
static_assert(offsetof(DIJOYSTATE2, lFX) == 0xF0);
static_assert(offsetof(DIJOYSTATE2, lFY) == 0xF4);
static_assert(offsetof(DIJOYSTATE2, lFZ) == 0xF8);
static_assert(offsetof(DIJOYSTATE2, lFRx) == 0xFC);
static_assert(offsetof(DIJOYSTATE2, lFRy) == 0x100);
static_assert(offsetof(DIJOYSTATE2, lFRz) == 0x104);
static_assert(offsetof(DIJOYSTATE2, rglFSlider) == 0x108);

static_assert(sizeof(DIJOYSTATE2) == 272);

typedef DIJOYSTATE2 * LPDIJOYSTATE2;

static_assert(TypeMatch<LPDIJOYSTATE2, DIJOYSTATE2 *>::value);

static_assert(sizeof(LPDIJOYSTATE2) == 4);

#pragma pack(pop)

extern "C" const DIDATAFORMAT c_dfDIMouse;
extern "C" const DIDATAFORMAT c_dfDIMouse2;
extern "C" const DIDATAFORMAT c_dfDIKeyboard;
extern "C" const DIDATAFORMAT c_dfDIJoystick;
extern "C" const DIDATAFORMAT c_dfDIJoystick2;

// LPDIENUMDEVICESCALLBACKA

typedef BOOL(__stdcall * LPDIENUMDEVICESCALLBACKA)
(
	LPCDIDEVICEINSTANCEA,
	LPVOID
);

static_assert(sizeof(LPDIENUMDEVICESCALLBACKA) == 4);

// LPDIENUMDEVICESCALLBACKW

typedef BOOL(__stdcall * LPDIENUMDEVICESCALLBACKW)
(
	LPCDIDEVICEINSTANCEW,
	LPVOID
);

static_assert(sizeof(LPDIENUMDEVICESCALLBACKW) == 4);

// LPDICONFIGUREDEVICESCALLBACK

typedef BOOL(__stdcall * LPDICONFIGUREDEVICESCALLBACK)
(
	IUnknown*,
	LPVOID
);

static_assert(sizeof(LPDICONFIGUREDEVICESCALLBACK) == 4);

// LPDIENUMDEVICESBYSEMANTICSCBA

typedef BOOL(__stdcall * LPDIENUMDEVICESBYSEMANTICSCBA)
(
	LPCDIDEVICEINSTANCEA,
	LPDIRECTINPUTDEVICE8A,
	DWORD,
	DWORD,
	LPVOID
);

static_assert(sizeof(LPDIENUMDEVICESBYSEMANTICSCBA) == 4);

// LPDIENUMDEVICESBYSEMANTICSCBW

typedef BOOL(__stdcall * LPDIENUMDEVICESBYSEMANTICSCBW)
(
	LPCDIDEVICEINSTANCEW,
	LPDIRECTINPUTDEVICE8W,
	DWORD,
	DWORD,
	LPVOID
);

static_assert(sizeof(LPDIENUMDEVICESBYSEMANTICSCBW) == 4);

// LPDIENUMDEVICEOBJECTSCALLBACKA

typedef BOOL(__stdcall * LPDIENUMDEVICEOBJECTSCALLBACKA)
(
	LPCDIDEVICEOBJECTINSTANCEA,
	LPVOID
);

static_assert(sizeof(LPDIENUMDEVICEOBJECTSCALLBACKA) == 4);

// LPDIENUMDEVICEOBJECTSCALLBACKW

typedef BOOL(__stdcall * LPDIENUMDEVICEOBJECTSCALLBACKW)
(
	LPCDIDEVICEOBJECTINSTANCEW,
	LPVOID
);

static_assert(sizeof(LPDIENUMDEVICEOBJECTSCALLBACKW) == 4);

// LPDIENUMEFFECTSCALLBACKA

typedef BOOL(__stdcall * LPDIENUMEFFECTSCALLBACKA)
(
	LPCDIEFFECTINFOA,
	LPVOID
);

static_assert(sizeof(LPDIENUMEFFECTSCALLBACKA) == 4);

// LPDIENUMEFFECTSCALLBACKW

typedef BOOL(__stdcall * LPDIENUMEFFECTSCALLBACKW)
(
	LPCDIEFFECTINFOW,
	LPVOID
);

static_assert(sizeof(LPDIENUMEFFECTSCALLBACKW) == 4);

// LPDIENUMCREATEDEFFECTOBJECTSCALLBACK

typedef BOOL(__stdcall * LPDIENUMCREATEDEFFECTOBJECTSCALLBACK)
(
	LPDIRECTINPUTEFFECT,
	LPVOID
);

static_assert(sizeof(LPDIENUMCREATEDEFFECTOBJECTSCALLBACK) == 4);

// LPDIENUMEFFECTSINFILECALLBACK

typedef BOOL(__stdcall * LPDIENUMEFFECTSINFILECALLBACK)
(
	LPCDIFILEEFFECT,
	LPVOID
);

static_assert(sizeof(LPDIENUMEFFECTSINFILECALLBACK) == 4);

// IDirectInput8A

struct __declspec(novtable) IDirectInput8A : IUnknown
{
	virtual HRESULT __stdcall CreateDevice
	(
		const GUID&,
		LPDIRECTINPUTDEVICE8A*,
		LPUNKNOWN
	) = 0;
	virtual HRESULT __stdcall EnumDevices
	(
		DWORD,
		LPDIENUMDEVICESCALLBACKA,
		LPVOID,
		DWORD
	) = 0;
	virtual HRESULT __stdcall GetDeviceStatus(const GUID&) = 0;
	virtual HRESULT __stdcall RunControlPanel
	(
		HWND,
		DWORD
	) = 0;
	virtual HRESULT __stdcall Initialize
	(
		HINSTANCE,
		DWORD
	) = 0;
	virtual HRESULT __stdcall FindDevice
	(
		const GUID&,
		LPCSTR,
		LPGUID
	) = 0;
	virtual HRESULT __stdcall EnumDevicesBySemantics
	(
		LPCSTR,
		LPDIACTIONFORMATA,
		LPDIENUMDEVICESBYSEMANTICSCBA,
		LPVOID,
		DWORD
	) = 0;
	virtual HRESULT __stdcall ConfigureDevices
	(
		LPDICONFIGUREDEVICESCALLBACK,
		LPDICONFIGUREDEVICESPARAMSA,
		DWORD,
		LPVOID
	) = 0;
};

static_assert(sizeof(IDirectInput8A) == 4);

// IDirectInput8W

struct __declspec(novtable) IDirectInput8W : IUnknown
{
	virtual HRESULT __stdcall CreateDevice
	(
		const GUID&,
		LPDIRECTINPUTDEVICE8W*,
		LPUNKNOWN
	) = 0;
	virtual HRESULT __stdcall EnumDevices
	(
		DWORD,
		LPDIENUMDEVICESCALLBACKW,
		LPVOID,
		DWORD
	) = 0;
	virtual HRESULT __stdcall GetDeviceStatus(const GUID&) = 0;
	virtual HRESULT __stdcall RunControlPanel
	(
		HWND,
		DWORD
	) = 0;
	virtual HRESULT __stdcall Initialize
	(
		HINSTANCE,
		DWORD
	) = 0;
	virtual HRESULT __stdcall FindDevice
	(
		const GUID&,
		LPCWSTR,
		LPGUID
	) = 0;
	virtual HRESULT __stdcall EnumDevicesBySemantics
	(
		LPCWSTR,
		LPDIACTIONFORMATW,
		LPDIENUMDEVICESBYSEMANTICSCBW,
		LPVOID,
		DWORD
	) = 0;
	virtual HRESULT __stdcall ConfigureDevices
	(
		LPDICONFIGUREDEVICESCALLBACK,
		LPDICONFIGUREDEVICESPARAMSW,
		DWORD,
		LPVOID
	) = 0;
};

static_assert(sizeof(IDirectInput8W) == 4);

// IDirectInputDevice8A

struct __declspec(novtable) IDirectInputDevice8A : IUnknown
{
	virtual HRESULT __stdcall GetCapabilities(LPDIDEVCAPS) = 0;
	virtual HRESULT __stdcall EnumObjects
	(
		LPDIENUMDEVICEOBJECTSCALLBACKA,
		LPVOID,
		DWORD
	) = 0;
	virtual HRESULT __stdcall GetProperty
	(
		const GUID&,
		LPDIPROPHEADER
	) = 0;
	virtual HRESULT __stdcall SetProperty
	(
		const GUID&,
		LPCDIPROPHEADER
	) = 0;
	virtual HRESULT __stdcall Acquire() = 0;
	virtual HRESULT __stdcall Unacquire() = 0;
	virtual HRESULT __stdcall GetDeviceState
	(
		DWORD,
		LPVOID
	) = 0;
	virtual HRESULT __stdcall GetDeviceData
	(
		DWORD,
		LPDIDEVICEOBJECTDATA,
		LPDWORD,
		DWORD
	) = 0;
	virtual HRESULT __stdcall SetDataFormat(LPCDIDATAFORMAT) = 0;
	virtual HRESULT __stdcall SetEventNotification(HANDLE) = 0;
	virtual HRESULT __stdcall SetCooperativeLevel
	(
		HWND,
		DWORD
	) = 0;
	virtual HRESULT __stdcall GetObjectInfo
	(
		LPDIDEVICEOBJECTINSTANCEA,
		DWORD,
		DWORD
	) = 0;
	virtual HRESULT __stdcall GetDeviceInfo(LPDIDEVICEINSTANCEA) = 0;
	virtual HRESULT __stdcall RunControlPanel
	(
		HWND,
		DWORD
	) = 0;
	virtual HRESULT __stdcall Initialize
	(
		HINSTANCE,
		DWORD,
		const GUID&
	) = 0;
	virtual HRESULT __stdcall CreateEffect
	(
		const GUID&,
		LPCDIEFFECT,
		LPDIRECTINPUTEFFECT*,
		LPUNKNOWN
	) = 0;
	virtual HRESULT __stdcall EnumEffects
	(
		LPDIENUMEFFECTSCALLBACKA,
		LPVOID,
		DWORD
	) = 0;
	virtual HRESULT __stdcall GetEffectInfo
	(
		LPDIEFFECTINFOA,
		const GUID&
	) = 0;
	virtual HRESULT __stdcall GetForceFeedbackState(LPDWORD) = 0;
	virtual HRESULT __stdcall SendForceFeedbackCommand(DWORD) = 0;
	virtual HRESULT __stdcall EnumCreatedEffectObjects
	(
		LPDIENUMCREATEDEFFECTOBJECTSCALLBACK,
		LPVOID,
		DWORD
	) = 0;
	virtual HRESULT __stdcall Escape(LPDIEFFESCAPE) = 0;
	virtual HRESULT __stdcall Poll() = 0;
	virtual HRESULT __stdcall SendDeviceData
	(
		DWORD,
		LPCDIDEVICEOBJECTDATA,
		LPDWORD,
		DWORD
	) = 0;
	virtual HRESULT __stdcall EnumEffectsInFile
	(
		LPCSTR,
		LPDIENUMEFFECTSINFILECALLBACK,
		LPVOID,
		DWORD
	) = 0;
	virtual HRESULT __stdcall WriteEffectToFile
	(
		LPCSTR,
		DWORD,
		LPDIFILEEFFECT,
		DWORD
	) = 0;
	virtual HRESULT __stdcall BuildActionMap
	(
		LPDIACTIONFORMATA,
		LPCSTR,
		DWORD
	) = 0;
	virtual HRESULT __stdcall SetActionMap
	(
		LPDIACTIONFORMATA,
		LPCSTR,
		DWORD
	) = 0;
	virtual HRESULT __stdcall GetImageInfo(LPDIDEVICEIMAGEINFOHEADERA) = 0;
};

static_assert(sizeof(IDirectInputDevice8A) == 4);

// IDirectInputDevice8W

struct __declspec(novtable) IDirectInputDevice8W : IUnknown
{
	virtual HRESULT __stdcall GetCapabilities(LPDIDEVCAPS) = 0;
	virtual HRESULT __stdcall EnumObjects
	(
		LPDIENUMDEVICEOBJECTSCALLBACKW,
		LPVOID,
		DWORD
	) = 0;
	virtual HRESULT __stdcall GetProperty
	(
		const GUID&,
		LPDIPROPHEADER
	) = 0;
	virtual HRESULT __stdcall SetProperty
	(
		const GUID&,
		LPCDIPROPHEADER
	) = 0;
	virtual HRESULT __stdcall Acquire() = 0;
	virtual HRESULT __stdcall Unacquire() = 0;
	virtual HRESULT __stdcall GetDeviceState
	(
		DWORD,
		LPVOID
	) = 0;
	virtual HRESULT __stdcall GetDeviceData
	(
		DWORD,
		LPDIDEVICEOBJECTDATA,
		LPDWORD,
		DWORD
	) = 0;
	virtual HRESULT __stdcall SetDataFormat(LPCDIDATAFORMAT) = 0;
	virtual HRESULT __stdcall SetEventNotification(HANDLE) = 0;
	virtual HRESULT __stdcall SetCooperativeLevel
	(
		HWND,
		DWORD
	) = 0;
	virtual HRESULT __stdcall GetObjectInfo
	(
		LPDIDEVICEOBJECTINSTANCEW,
		DWORD,
		DWORD
	) = 0;
	virtual HRESULT __stdcall GetDeviceInfo(LPDIDEVICEINSTANCEW) = 0;
	virtual HRESULT __stdcall RunControlPanel
	(
		HWND,
		DWORD
	) = 0;
	virtual HRESULT __stdcall Initialize
	(
		HINSTANCE,
		DWORD,
		const GUID&
	) = 0;
	virtual HRESULT __stdcall CreateEffect
	(
		const GUID&,
		LPCDIEFFECT,
		LPDIRECTINPUTEFFECT*,
		LPUNKNOWN
	) = 0;
	virtual HRESULT __stdcall EnumEffects
	(
		LPDIENUMEFFECTSCALLBACKW,
		LPVOID,
		DWORD
	) = 0;
	virtual HRESULT __stdcall GetEffectInfo
	(
		LPDIEFFECTINFOW,
		const GUID&
	) = 0;
	virtual HRESULT __stdcall GetForceFeedbackState(LPDWORD) = 0;
	virtual HRESULT __stdcall SendForceFeedbackCommand(DWORD) = 0;
	virtual HRESULT __stdcall EnumCreatedEffectObjects
	(
		LPDIENUMCREATEDEFFECTOBJECTSCALLBACK,
		LPVOID,
		DWORD
	) = 0;
	virtual HRESULT __stdcall Escape(LPDIEFFESCAPE) = 0;
	virtual HRESULT __stdcall Poll() = 0;
	virtual HRESULT __stdcall SendDeviceData
	(
		DWORD,
		LPCDIDEVICEOBJECTDATA,
		LPDWORD,
		DWORD
	) = 0;
	virtual HRESULT __stdcall EnumEffectsInFile
	(
		LPCWSTR,
		LPDIENUMEFFECTSINFILECALLBACK,
		LPVOID,
		DWORD
	) = 0;
	virtual HRESULT __stdcall WriteEffectToFile
	(
		LPCWSTR,
		DWORD,
		LPDIFILEEFFECT,
		DWORD
	) = 0;
	virtual HRESULT __stdcall BuildActionMap
	(
		LPDIACTIONFORMATW,
		LPCWSTR,
		DWORD
	) = 0;
	virtual HRESULT __stdcall SetActionMap
	(
		LPDIACTIONFORMATW,
		LPCWSTR,
		DWORD
	) = 0;
	virtual HRESULT __stdcall GetImageInfo(LPDIDEVICEIMAGEINFOHEADERW) = 0;
};

static_assert(sizeof(IDirectInputDevice8W) == 4);

// IDirectInputEffect

struct __declspec(novtable) IDirectInputEffect : IUnknown
{
	virtual HRESULT __stdcall Initialize
	(
		HINSTANCE,
		DWORD,
		const GUID&
	) = 0;
	virtual HRESULT __stdcall GetEffectGuid(LPGUID) = 0;
	virtual HRESULT __stdcall GetParameters
	(
		LPDIEFFECT,
		DWORD
	) = 0;
	virtual HRESULT __stdcall SetParameters
	(
		LPCDIEFFECT,
		DWORD
	) = 0;
	virtual HRESULT __stdcall Start
	(
		DWORD,
		DWORD
	) = 0;
	virtual HRESULT __stdcall Stop() = 0;
	virtual HRESULT __stdcall GetEffectStatus(LPDWORD) = 0;
	virtual HRESULT __stdcall Download() = 0;
	virtual HRESULT __stdcall Unload() = 0;
	virtual HRESULT __stdcall Escape(LPDIEFFESCAPE) = 0;
};

static_assert(sizeof(IDirectInputEffect) == 4);

extern "C" HRESULT __stdcall DirectInput8Create
(
	HINSTANCE hinst,
	DWORD dwVersion,
	const IID& riidltf,
	LPVOID* ppvOut,
	LPUNKNOWN punkOuter
);
#pragma endregion

#endif

namespaceEnd();
