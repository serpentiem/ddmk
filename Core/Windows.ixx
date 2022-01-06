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

export module Windows;

export namespaceStart(Windows);

#ifdef _WIN64

#pragma region x86_64

// VOID

typedef void VOID;
typedef VOID * PVOID;
typedef VOID * LPVOID;
typedef const VOID * LPCVOID;

static_assert(TypeMatch<VOID, void>::value);
static_assert(TypeMatch<PVOID, VOID *>::value);
static_assert(TypeMatch<LPVOID, VOID *>::value);
static_assert(TypeMatch<LPCVOID, const VOID *>::value);

static_assert(sizeof(PVOID) == 8);
static_assert(sizeof(LPVOID) == 8);
static_assert(sizeof(LPCVOID) == 8);

// BOOL

typedef int BOOL;
typedef BOOL * PBOOL;
typedef BOOL * LPBOOL;

static_assert(TypeMatch<BOOL, int>::value);
static_assert(TypeMatch<PBOOL, BOOL *>::value);
static_assert(TypeMatch<LPBOOL, BOOL *>::value);

static_assert(sizeof(BOOL) == 4);
static_assert(sizeof(PBOOL) == 8);
static_assert(sizeof(LPBOOL) == 8);

// BYTE

typedef unsigned char BYTE;
typedef BYTE * PBYTE;
typedef BYTE * LPBYTE;
typedef const BYTE * LPCBYTE;

static_assert(TypeMatch<BYTE, unsigned char>::value);
static_assert(TypeMatch<PBYTE, BYTE *>::value);
static_assert(TypeMatch<LPBYTE, BYTE *>::value);
static_assert(TypeMatch<LPCBYTE, const BYTE *>::value);

static_assert(sizeof(BYTE) == 1);
static_assert(sizeof(PBYTE) == 8);
static_assert(sizeof(LPBYTE) == 8);
static_assert(sizeof(LPCBYTE) == 8);

// WORD

typedef unsigned short WORD;
typedef WORD * PWORD;
typedef WORD * LPWORD;

static_assert(TypeMatch<WORD, unsigned short>::value);
static_assert(TypeMatch<PWORD, WORD *>::value);
static_assert(TypeMatch<LPWORD, WORD *>::value);

static_assert(sizeof(WORD) == 2);
static_assert(sizeof(PWORD) == 8);
static_assert(sizeof(LPWORD) == 8);

// DWORD

typedef unsigned long DWORD;
typedef DWORD * PDWORD;
typedef DWORD * LPDWORD;

static_assert(TypeMatch<DWORD, unsigned long>::value);
static_assert(TypeMatch<PDWORD, DWORD *>::value);
static_assert(TypeMatch<LPDWORD, DWORD *>::value);

static_assert(sizeof(DWORD) == 4);
static_assert(sizeof(PDWORD) == 8);
static_assert(sizeof(LPDWORD) == 8);

// FLOAT

typedef float FLOAT;
typedef FLOAT * PFLOAT;

static_assert(TypeMatch<FLOAT, float>::value);
static_assert(TypeMatch<PFLOAT, FLOAT *>::value);

static_assert(sizeof(FLOAT) == 4);
static_assert(sizeof(PFLOAT) == 8);

// DOUBLE

typedef double DOUBLE;

static_assert(TypeMatch<DOUBLE, double>::value);

static_assert(sizeof(DOUBLE) == 8);

// CHAR

typedef char CHAR;
typedef CHAR * PCHAR;

static_assert(TypeMatch<CHAR, char>::value);
static_assert(TypeMatch<PCHAR, CHAR *>::value);

static_assert(sizeof(CHAR) == 1);
static_assert(sizeof(PCHAR) == 8);

// SHORT

typedef short SHORT;
typedef SHORT * PSHORT;

static_assert(TypeMatch<SHORT, short>::value);
static_assert(TypeMatch<PSHORT, SHORT *>::value);

static_assert(sizeof(SHORT) == 2);
static_assert(sizeof(PSHORT) == 8);

// LONG

typedef long LONG;
typedef LONG * PLONG;
typedef LONG * LPLONG;

static_assert(TypeMatch<LONG, long>::value);
static_assert(TypeMatch<PLONG, LONG *>::value);
static_assert(TypeMatch<LPLONG, LONG *>::value);

static_assert(sizeof(LONG) == 4);
static_assert(sizeof(PLONG) == 8);
static_assert(sizeof(LPLONG) == 8);

// INT

typedef int INT;
typedef INT * PINT;
typedef INT * LPINT;

static_assert(TypeMatch<INT, int>::value);
static_assert(TypeMatch<PINT, INT *>::value);
static_assert(TypeMatch<LPINT, INT *>::value);

static_assert(sizeof(INT) == 4);
static_assert(sizeof(PINT) == 8);
static_assert(sizeof(LPINT) == 8);

// WCHAR

typedef wchar_t WCHAR;
typedef WCHAR * PWCHAR;
typedef const WCHAR * LPCWCHAR;

static_assert(TypeMatch<WCHAR, wchar_t>::value);
static_assert(TypeMatch<PWCHAR, WCHAR *>::value);
static_assert(TypeMatch<LPCWCHAR, const WCHAR *>::value);

static_assert(sizeof(WCHAR) == 2);
static_assert(sizeof(PWCHAR) == 8);
static_assert(sizeof(LPCWCHAR) == 8);

// INT8

typedef signed char INT8;
typedef INT8 * PINT8;

static_assert(TypeMatch<INT8, signed char>::value);
static_assert(TypeMatch<PINT8, INT8 *>::value);

static_assert(sizeof(INT8) == 1);
static_assert(sizeof(PINT8) == 8);

// INT16

typedef signed short INT16;
typedef INT16 * PINT16;

static_assert(TypeMatch<INT16, signed short>::value);
static_assert(TypeMatch<PINT16, INT16 *>::value);

static_assert(sizeof(INT16) == 2);
static_assert(sizeof(PINT16) == 8);

// INT32

typedef signed int INT32;
typedef INT32 * PINT32;

static_assert(TypeMatch<INT32, signed int>::value);
static_assert(TypeMatch<PINT32, INT32 *>::value);

static_assert(sizeof(INT32) == 4);
static_assert(sizeof(PINT32) == 8);

// INT64

typedef signed long long INT64;
typedef INT64 * PINT64;

static_assert(TypeMatch<INT64, signed long long>::value);
static_assert(TypeMatch<PINT64, INT64 *>::value);

static_assert(sizeof(INT64) == 8);
static_assert(sizeof(PINT64) == 8);

// UINT8

typedef unsigned char UINT8;
typedef UINT8 * PUINT8;

static_assert(TypeMatch<UINT8, unsigned char>::value);
static_assert(TypeMatch<PUINT8, UINT8 *>::value);

static_assert(sizeof(UINT8) == 1);
static_assert(sizeof(PUINT8) == 8);

// UINT16

typedef unsigned short UINT16;
typedef UINT16 * PUINT16;

static_assert(TypeMatch<UINT16, unsigned short>::value);
static_assert(TypeMatch<PUINT16, UINT16 *>::value);

static_assert(sizeof(UINT16) == 2);
static_assert(sizeof(PUINT16) == 8);

// UINT32

typedef unsigned int UINT32;
typedef UINT32 * PUINT32;

static_assert(TypeMatch<UINT32, unsigned int>::value);
static_assert(TypeMatch<PUINT32, UINT32 *>::value);

static_assert(sizeof(UINT32) == 4);
static_assert(sizeof(PUINT32) == 8);

// UINT64

typedef unsigned long long UINT64;
typedef UINT64 * PUINT64;

static_assert(TypeMatch<UINT64, unsigned long long>::value);
static_assert(TypeMatch<PUINT64, UINT64 *>::value);

static_assert(sizeof(UINT64) == 8);
static_assert(sizeof(PUINT64) == 8);

// UCHAR

typedef unsigned char UCHAR;
typedef UCHAR * PUCHAR;

static_assert(TypeMatch<UCHAR, unsigned char>::value);
static_assert(TypeMatch<PUCHAR, UCHAR *>::value);

static_assert(sizeof(UCHAR) == 1);
static_assert(sizeof(PUCHAR) == 8);

// USHORT

typedef unsigned short USHORT;
typedef USHORT * PUSHORT;

static_assert(TypeMatch<USHORT, unsigned short>::value);
static_assert(TypeMatch<PUSHORT, USHORT *>::value);

static_assert(sizeof(USHORT) == 2);
static_assert(sizeof(PUSHORT) == 8);

// UINT

typedef unsigned int UINT;
typedef UINT * PUINT;
typedef UINT * LPUINT;

static_assert(TypeMatch<UINT, unsigned int>::value);
static_assert(TypeMatch<PUINT, UINT *>::value);
static_assert(TypeMatch<LPUINT, UINT *>::value);

static_assert(sizeof(UINT) == 4);
static_assert(sizeof(PUINT) == 8);
static_assert(sizeof(LPUINT) == 8);

// ULONG

typedef unsigned long ULONG;
typedef ULONG * PULONG;

static_assert(TypeMatch<ULONG, unsigned long>::value);
static_assert(TypeMatch<PULONG, ULONG *>::value);

static_assert(sizeof(ULONG) == 4);
static_assert(sizeof(PULONG) == 8);

// LONGLONG

typedef long long LONGLONG;
typedef LONGLONG * PLONGLONG;

static_assert(TypeMatch<LONGLONG, long long>::value);
static_assert(TypeMatch<PLONGLONG, LONGLONG *>::value);

static_assert(sizeof(LONGLONG) == 8);
static_assert(sizeof(PLONGLONG) == 8);

// ULONGLONG

typedef unsigned long long ULONGLONG;
typedef ULONGLONG * PULONGLONG;

static_assert(TypeMatch<ULONGLONG, unsigned long long>::value);
static_assert(TypeMatch<PULONGLONG, ULONGLONG *>::value);

static_assert(sizeof(ULONGLONG) == 8);
static_assert(sizeof(PULONGLONG) == 8);

// INT_PTR

typedef long long INT_PTR;
typedef INT_PTR * PINT_PTR;

static_assert(TypeMatch<INT_PTR, long long>::value);
static_assert(TypeMatch<PINT_PTR, INT_PTR *>::value);

static_assert(sizeof(INT_PTR) == 8);
static_assert(sizeof(PINT_PTR) == 8);

// UINT_PTR

typedef unsigned long long UINT_PTR;
typedef UINT_PTR * PUINT_PTR;

static_assert(TypeMatch<UINT_PTR, unsigned long long>::value);
static_assert(TypeMatch<PUINT_PTR, UINT_PTR *>::value);

static_assert(sizeof(UINT_PTR) == 8);
static_assert(sizeof(PUINT_PTR) == 8);

// LONG_PTR

typedef long long LONG_PTR;
typedef LONG_PTR * PLONG_PTR;

static_assert(TypeMatch<LONG_PTR, long long>::value);
static_assert(TypeMatch<PLONG_PTR, LONG_PTR *>::value);

static_assert(sizeof(LONG_PTR) == 8);
static_assert(sizeof(PLONG_PTR) == 8);

// ULONG_PTR

typedef unsigned long long ULONG_PTR;
typedef ULONG_PTR * PULONG_PTR;

static_assert(TypeMatch<ULONG_PTR, unsigned long long>::value);
static_assert(TypeMatch<PULONG_PTR, ULONG_PTR *>::value);

static_assert(sizeof(ULONG_PTR) == 8);
static_assert(sizeof(PULONG_PTR) == 8);

// DWORD_PTR

typedef unsigned long long DWORD_PTR;
typedef DWORD_PTR * PDWORD_PTR;

static_assert(TypeMatch<DWORD_PTR, unsigned long long>::value);
static_assert(TypeMatch<PDWORD_PTR, DWORD_PTR *>::value);

static_assert(sizeof(DWORD_PTR) == 8);
static_assert(sizeof(PDWORD_PTR) == 8);

// SIZE_T

typedef unsigned long long SIZE_T;
typedef SIZE_T * PSIZE_T;

static_assert(TypeMatch<SIZE_T, unsigned long long>::value);
static_assert(TypeMatch<PSIZE_T, SIZE_T *>::value);

static_assert(sizeof(SIZE_T) == 8);
static_assert(sizeof(PSIZE_T) == 8);

// HANDLE

typedef void* HANDLE;
typedef HANDLE * PHANDLE;
typedef HANDLE * LPHANDLE;

static_assert(TypeMatch<HANDLE, void*>::value);
static_assert(TypeMatch<PHANDLE, HANDLE *>::value);
static_assert(TypeMatch<LPHANDLE, HANDLE *>::value);

static_assert(sizeof(HANDLE) == 8);
static_assert(sizeof(PHANDLE) == 8);
static_assert(sizeof(LPHANDLE) == 8);

// HINSTANCE

typedef HANDLE HINSTANCE;

static_assert(sizeof(HINSTANCE) == 8);

// HMODULE

typedef HANDLE HMODULE;

static_assert(sizeof(HMODULE) == 8);

// HWND

typedef HANDLE HWND;

static_assert(sizeof(HWND) == 8);

// HMENU

typedef HANDLE HMENU;

static_assert(sizeof(HMENU) == 8);

// HICON

typedef HANDLE HICON;

static_assert(sizeof(HICON) == 8);

// HCURSOR

typedef HANDLE HCURSOR;

static_assert(sizeof(HCURSOR) == 8);

// HBRUSH

typedef HANDLE HBRUSH;

static_assert(sizeof(HBRUSH) == 8);

// HMONITOR

typedef HANDLE HMONITOR;

static_assert(sizeof(HMONITOR) == 8);

// HRESULT

typedef long HRESULT;

static_assert(TypeMatch<HRESULT, long>::value);

static_assert(sizeof(HRESULT) == 4);

// WPARAM

typedef UINT_PTR WPARAM;

static_assert(TypeMatch<WPARAM, UINT_PTR>::value);

static_assert(sizeof(WPARAM) == 8);

// LPARAM

typedef LONG_PTR LPARAM;

static_assert(TypeMatch<LPARAM, LONG_PTR>::value);

static_assert(sizeof(LPARAM) == 8);

// LRESULT

typedef LONG_PTR LRESULT;

static_assert(TypeMatch<LRESULT, LONG_PTR>::value);

static_assert(sizeof(LRESULT) == 8);

// PSTR

typedef CHAR * PSTR;

static_assert(TypeMatch<PSTR, CHAR *>::value);

static_assert(sizeof(PSTR) == 8);

// LPSTR

typedef CHAR * LPSTR;

static_assert(TypeMatch<LPSTR, CHAR *>::value);

static_assert(sizeof(LPSTR) == 8);

// LPCSTR

typedef const CHAR * LPCSTR;

static_assert(TypeMatch<LPCSTR, const CHAR *>::value);

static_assert(sizeof(LPCSTR) == 8);

// PWSTR

typedef WCHAR * PWSTR;

static_assert(TypeMatch<PWSTR, WCHAR *>::value);

static_assert(sizeof(PWSTR) == 8);

// LPWSTR

typedef WCHAR * LPWSTR;

static_assert(TypeMatch<LPWSTR, WCHAR *>::value);

static_assert(sizeof(LPWSTR) == 8);

// LPCWSTR

typedef const WCHAR * LPCWSTR;

static_assert(TypeMatch<LPCWSTR, const WCHAR *>::value);

static_assert(sizeof(LPCWSTR) == 8);

// ATOM

typedef WORD ATOM;

static_assert(TypeMatch<ATOM, WORD>::value);

static_assert(sizeof(ATOM) == 2);

// HDC

typedef HANDLE HDC;

static_assert(sizeof(HDC) == 8);

// FARPROC

typedef INT_PTR(* FARPROC)();

static_assert(sizeof(FARPROC) == 8);

// WNDPROC

typedef LRESULT(* WNDPROC)
(
	HWND,
	UINT,
	WPARAM,
	LPARAM
);

static_assert(sizeof(WNDPROC) == 8);

// PTHREAD_START_ROUTINE

typedef DWORD(* PTHREAD_START_ROUTINE)(LPVOID lpThreadParameter);

static_assert(sizeof(PTHREAD_START_ROUTINE) == 8);

// LPTHREAD_START_ROUTINE

typedef PTHREAD_START_ROUTINE LPTHREAD_START_ROUTINE;

static_assert(TypeMatch<LPTHREAD_START_ROUTINE, PTHREAD_START_ROUTINE>::value);

static_assert(sizeof(LPTHREAD_START_ROUTINE) == 8);

enum
{
	PAGE_NOACCESS=1,
	PAGE_READONLY=2,
	PAGE_READWRITE=4,
	PAGE_WRITECOPY=8,
	PAGE_EXECUTE=0x10,
	PAGE_EXECUTE_READ=0x20,
	PAGE_EXECUTE_READWRITE=0x40,
	PAGE_EXECUTE_WRITECOPY=0x80,
	MEM_COMMIT=0x1000,
	MEM_RESERVE=0x2000,
	MEM_DECOMMIT=0x4000,
	MEM_RELEASE=0x8000,
	MEM_FREE=0x10000,
	GENERIC_READ=0x80000000,
	GENERIC_WRITE=0x40000000,
	GENERIC_EXECUTE=0x20000000,
	GENERIC_ALL=0x10000000,
	CREATE_NEW=1,
	CREATE_ALWAYS=2,
	OPEN_EXISTING=3,
	OPEN_ALWAYS=4,
	TRUNCATE_EXISTING=5,
	FILE_APPEND_DATA=4,
	FILE_ATTRIBUTE_READONLY=1,
	FILE_ATTRIBUTE_HIDDEN=2,
	FILE_ATTRIBUTE_SYSTEM=4,
	FILE_ATTRIBUTE_DIRECTORY=0x10,
	FILE_ATTRIBUTE_ARCHIVE=0x20,
	FILE_ATTRIBUTE_DEVICE=0x40,
	FILE_ATTRIBUTE_NORMAL=0x80,
	FILE_ATTRIBUTE_TEMPORARY=0x100,
	FILE_BEGIN=0,
	FILE_CURRENT=1,
	FILE_END=2,
	TH32CS_SNAPHEAPLIST=1,
	TH32CS_SNAPPROCESS=2,
	TH32CS_SNAPTHREAD=4,
	TH32CS_SNAPMODULE=8,
	TH32CS_SNAPMODULE32=0x10,
	TH32CS_INHERIT=0x80000000,
	GWL_STYLE=-16,
	GWL_EXSTYLE=-20,
	GWL_ID=-12,
	GWLP_WNDPROC=-4,
	GWLP_HINSTANCE=-6,
	GWLP_HWNDPARENT=-8,
	GWLP_USERDATA=-21,
	GWLP_ID=-12,
	GCL_CBWNDEXTRA=-18,
	GCL_CBCLSEXTRA=-20,
	GCL_STYLE=-26,
	GCW_ATOM=-32,
	GCLP_MENUNAME=-8,
	GCLP_HBRBACKGROUND=-10,
	GCLP_HCURSOR=-12,
	GCLP_HICON=-14,
	GCLP_HMODULE=-16,
	GCLP_WNDPROC=-24,
	GCLP_HICONSM=-34,
	WM_USER=0x400,
	S_OK=0,
	S_FALSE=1,
	WHEEL_DELTA=120,
	WM_SETCURSOR=0x0020,
	WM_CHAR=0x0102,
	DLL_PROCESS_DETACH=0,
	DLL_PROCESS_ATTACH=1,
	DLL_THREAD_ATTACH=2,
	DLL_THREAD_DETACH=3,
	SW_HIDE=0,
	SW_SHOWNORMAL=1,
	SW_NORMAL=1,
	SW_SHOWMINIMIZED=2,
	SW_SHOWMAXIMIZED=3,
	SW_MAXIMIZE=3,
	SW_SHOWNOACTIVATE=4,
	SW_SHOW=5,
	SW_MINIMIZE=6,
	SW_SHOWMINNOACTIVE=7,
	SW_SHOWNA=8,
	SW_RESTORE=9,
	SW_SHOWDEFAULT=10,
	SW_FORCEMINIMIZE=11,
	SW_MAX=11,
	WM_SIZE=0x0005,
	WS_OVERLAPPED=0x00000000,
	WS_POPUP=0x80000000,
	WS_CHILD=0x40000000,
	WS_MINIMIZE=0x20000000,
	WS_VISIBLE=0x10000000,
	WS_DISABLED=0x08000000,
	WS_CLIPSIBLINGS=0x04000000,
	WS_CLIPCHILDREN=0x02000000,
	WS_MAXIMIZE=0x01000000,
	WS_CAPTION=0x00C00000,
	WS_BORDER=0x00800000,
	WS_DLGFRAME=0x00400000,
	WS_VSCROLL=0x00200000,
	WS_HSCROLL=0x00100000,
	WS_SYSMENU=0x00080000,
	WS_THICKFRAME=0x00040000,
	WS_GROUP=0x00020000,
	WS_TABSTOP=0x00010000,
	WS_MINIMIZEBOX=0x00020000,
	WS_MAXIMIZEBOX=0x00010000,
	WS_TILED=0x00000000,
	WS_ICONIC=0x20000000,
	WS_SIZEBOX=0x00040000,
	WS_OVERLAPPEDWINDOW=0x00CF0000,
	WS_POPUPWINDOW=0x80880000,
	WS_CHILDWINDOW=0x40000000,
	WS_TILEDWINDOW=0x00CF0000,
	WM_STYLECHANGING=0x007C,
	WM_STYLECHANGED=0x007D,
	WM_DISPLAYCHANGE=0x007E,
	WM_SHOWWINDOW=0x0018,
};

const auto INVALID_HANDLE_VALUE = reinterpret_cast<HANDLE>(-1);
const auto IDC_ARROW = reinterpret_cast<LPSTR>(32512);
const auto IDC_IBEAM = reinterpret_cast<LPSTR>(32513);
const auto IDC_WAIT = reinterpret_cast<LPSTR>(32514);
const auto IDC_CROSS = reinterpret_cast<LPSTR>(32515);
const auto IDC_UPARROW = reinterpret_cast<LPSTR>(32516);
const auto IDC_SIZE = reinterpret_cast<LPSTR>(32640);
const auto IDC_ICON = reinterpret_cast<LPSTR>(32641);
const auto IDC_SIZENWSE = reinterpret_cast<LPSTR>(32642);
const auto IDC_SIZENESW = reinterpret_cast<LPSTR>(32643);
const auto IDC_SIZEWE = reinterpret_cast<LPSTR>(32644);
const auto IDC_SIZENS = reinterpret_cast<LPSTR>(32645);
const auto IDC_SIZEALL = reinterpret_cast<LPSTR>(32646);
const auto IDC_NO = reinterpret_cast<LPSTR>(32648);
const auto IDC_HAND = reinterpret_cast<LPSTR>(32649);
const auto IDC_APPSTARTING = reinterpret_cast<LPSTR>(32650);
const auto IDC_HELP = reinterpret_cast<LPSTR>(32651);
const auto IDC_PIN = reinterpret_cast<LPSTR>(32671);
const auto IDC_PERSON = reinterpret_cast<LPSTR>(32672);

#pragma pack(push, 1)

// RECT

struct RECT
{
	LONG left; // 0
	LONG top; // 4
	LONG right; // 8
	LONG bottom; // 0xC
};

static_assert(TypeMatch<decltype(RECT::left), LONG>::value);
static_assert(TypeMatch<decltype(RECT::top), LONG>::value);
static_assert(TypeMatch<decltype(RECT::right), LONG>::value);
static_assert(TypeMatch<decltype(RECT::bottom), LONG>::value);

static_assert(offsetof(RECT, left) == 0);
static_assert(offsetof(RECT, top) == 4);
static_assert(offsetof(RECT, right) == 8);
static_assert(offsetof(RECT, bottom) == 0xC);

static_assert(sizeof(RECT) == 16);

typedef RECT * PRECT;
typedef RECT * LPRECT;
typedef const RECT * LPCRECT;

static_assert(TypeMatch<PRECT, RECT *>::value);
static_assert(TypeMatch<LPRECT, RECT *>::value);
static_assert(TypeMatch<LPCRECT, const RECT *>::value);

static_assert(sizeof(PRECT) == 8);
static_assert(sizeof(LPRECT) == 8);
static_assert(sizeof(LPCRECT) == 8);

// POINT

struct POINT
{
	LONG x; // 0
	LONG y; // 4
};

static_assert(TypeMatch<decltype(POINT::x), LONG>::value);
static_assert(TypeMatch<decltype(POINT::y), LONG>::value);

static_assert(offsetof(POINT, x) == 0);
static_assert(offsetof(POINT, y) == 4);

static_assert(sizeof(POINT) == 8);

typedef POINT * PPOINT;
typedef POINT * LPPOINT;

static_assert(TypeMatch<PPOINT, POINT *>::value);
static_assert(TypeMatch<LPPOINT, POINT *>::value);

static_assert(sizeof(PPOINT) == 8);
static_assert(sizeof(LPPOINT) == 8);

// SIZE

struct SIZE
{
	LONG cx; // 0
	LONG cy; // 4
};

static_assert(TypeMatch<decltype(SIZE::cx), LONG>::value);
static_assert(TypeMatch<decltype(SIZE::cy), LONG>::value);

static_assert(offsetof(SIZE, cx) == 0);
static_assert(offsetof(SIZE, cy) == 4);

static_assert(sizeof(SIZE) == 8);

typedef SIZE * PSIZE;
typedef SIZE * LPSIZE;

static_assert(TypeMatch<PSIZE, SIZE *>::value);
static_assert(TypeMatch<LPSIZE, SIZE *>::value);

static_assert(sizeof(PSIZE) == 8);
static_assert(sizeof(LPSIZE) == 8);

// SYSTEM_INFO

struct SYSTEM_INFO
{
	union
	{
		DWORD dwOemId; // 0
		struct
		{
			WORD wProcessorArchitecture; // 0
			WORD wReserved; // 2
		}; // 0
	}; // 0
	DWORD dwPageSize; // 4
	LPVOID lpMinimumApplicationAddress; // 8
	LPVOID lpMaximumApplicationAddress; // 0x10
	DWORD_PTR dwActiveProcessorMask; // 0x18
	DWORD dwNumberOfProcessors; // 0x20
	DWORD dwProcessorType; // 0x24
	DWORD dwAllocationGranularity; // 0x28
	WORD wProcessorLevel; // 0x2C
	WORD wProcessorRevision; // 0x2E
};

static_assert(TypeMatch<decltype(SYSTEM_INFO::dwOemId), DWORD>::value);
static_assert(TypeMatch<decltype(SYSTEM_INFO::wProcessorArchitecture), WORD>::value);
static_assert(TypeMatch<decltype(SYSTEM_INFO::wReserved), WORD>::value);
static_assert(TypeMatch<decltype(SYSTEM_INFO::dwPageSize), DWORD>::value);
static_assert(TypeMatch<decltype(SYSTEM_INFO::lpMinimumApplicationAddress), LPVOID>::value);
static_assert(TypeMatch<decltype(SYSTEM_INFO::lpMaximumApplicationAddress), LPVOID>::value);
static_assert(TypeMatch<decltype(SYSTEM_INFO::dwActiveProcessorMask), DWORD_PTR>::value);
static_assert(TypeMatch<decltype(SYSTEM_INFO::dwNumberOfProcessors), DWORD>::value);
static_assert(TypeMatch<decltype(SYSTEM_INFO::dwProcessorType), DWORD>::value);
static_assert(TypeMatch<decltype(SYSTEM_INFO::dwAllocationGranularity), DWORD>::value);
static_assert(TypeMatch<decltype(SYSTEM_INFO::wProcessorLevel), WORD>::value);
static_assert(TypeMatch<decltype(SYSTEM_INFO::wProcessorRevision), WORD>::value);

static_assert(offsetof(SYSTEM_INFO, dwOemId) == 0);
static_assert(offsetof(SYSTEM_INFO, wProcessorArchitecture) == 0);
static_assert(offsetof(SYSTEM_INFO, wReserved) == 2);
static_assert(offsetof(SYSTEM_INFO, dwPageSize) == 4);
static_assert(offsetof(SYSTEM_INFO, lpMinimumApplicationAddress) == 8);
static_assert(offsetof(SYSTEM_INFO, lpMaximumApplicationAddress) == 0x10);
static_assert(offsetof(SYSTEM_INFO, dwActiveProcessorMask) == 0x18);
static_assert(offsetof(SYSTEM_INFO, dwNumberOfProcessors) == 0x20);
static_assert(offsetof(SYSTEM_INFO, dwProcessorType) == 0x24);
static_assert(offsetof(SYSTEM_INFO, dwAllocationGranularity) == 0x28);
static_assert(offsetof(SYSTEM_INFO, wProcessorLevel) == 0x2C);
static_assert(offsetof(SYSTEM_INFO, wProcessorRevision) == 0x2E);

static_assert(sizeof(SYSTEM_INFO) == 48);

typedef SYSTEM_INFO * LPSYSTEM_INFO;

static_assert(TypeMatch<LPSYSTEM_INFO, SYSTEM_INFO *>::value);

static_assert(sizeof(LPSYSTEM_INFO) == 8);

// MEMORY_BASIC_INFORMATION

struct MEMORY_BASIC_INFORMATION
{
	PVOID BaseAddress; // 0
	PVOID AllocationBase; // 8
	DWORD AllocationProtect; // 0x10
	_(4);
	SIZE_T RegionSize; // 0x18
	DWORD State; // 0x20
	DWORD Protect; // 0x24
	DWORD Type; // 0x28
	_(4);
};

static_assert(TypeMatch<decltype(MEMORY_BASIC_INFORMATION::BaseAddress), PVOID>::value);
static_assert(TypeMatch<decltype(MEMORY_BASIC_INFORMATION::AllocationBase), PVOID>::value);
static_assert(TypeMatch<decltype(MEMORY_BASIC_INFORMATION::AllocationProtect), DWORD>::value);
static_assert(TypeMatch<decltype(MEMORY_BASIC_INFORMATION::RegionSize), SIZE_T>::value);
static_assert(TypeMatch<decltype(MEMORY_BASIC_INFORMATION::State), DWORD>::value);
static_assert(TypeMatch<decltype(MEMORY_BASIC_INFORMATION::Protect), DWORD>::value);
static_assert(TypeMatch<decltype(MEMORY_BASIC_INFORMATION::Type), DWORD>::value);

static_assert(offsetof(MEMORY_BASIC_INFORMATION, BaseAddress) == 0);
static_assert(offsetof(MEMORY_BASIC_INFORMATION, AllocationBase) == 8);
static_assert(offsetof(MEMORY_BASIC_INFORMATION, AllocationProtect) == 0x10);
static_assert(offsetof(MEMORY_BASIC_INFORMATION, RegionSize) == 0x18);
static_assert(offsetof(MEMORY_BASIC_INFORMATION, State) == 0x20);
static_assert(offsetof(MEMORY_BASIC_INFORMATION, Protect) == 0x24);
static_assert(offsetof(MEMORY_BASIC_INFORMATION, Type) == 0x28);

static_assert(sizeof(MEMORY_BASIC_INFORMATION) == 48);

typedef MEMORY_BASIC_INFORMATION * PMEMORY_BASIC_INFORMATION;

static_assert(TypeMatch<PMEMORY_BASIC_INFORMATION, MEMORY_BASIC_INFORMATION *>::value);

static_assert(sizeof(PMEMORY_BASIC_INFORMATION) == 8);

// MODULEENTRY32

struct MODULEENTRY32
{
	DWORD dwSize; // 0
	DWORD th32ModuleID; // 4
	DWORD th32ProcessID; // 8
	DWORD GlblcntUsage; // 0xC
	DWORD ProccntUsage; // 0x10
	_(4);
	BYTE* modBaseAddr; // 0x18
	DWORD modBaseSize; // 0x20
	_(4);
	HMODULE hModule; // 0x28
	char szModule[256]; // 0x30
	char szExePath[260]; // 0x130
	_(4);
};

static_assert(TypeMatch<decltype(MODULEENTRY32::dwSize), DWORD>::value);
static_assert(TypeMatch<decltype(MODULEENTRY32::th32ModuleID), DWORD>::value);
static_assert(TypeMatch<decltype(MODULEENTRY32::th32ProcessID), DWORD>::value);
static_assert(TypeMatch<decltype(MODULEENTRY32::GlblcntUsage), DWORD>::value);
static_assert(TypeMatch<decltype(MODULEENTRY32::ProccntUsage), DWORD>::value);
static_assert(TypeMatch<decltype(MODULEENTRY32::modBaseAddr), BYTE*>::value);
static_assert(TypeMatch<decltype(MODULEENTRY32::modBaseSize), DWORD>::value);
static_assert(TypeMatch<decltype(MODULEENTRY32::hModule), HMODULE>::value);
static_assert(TypeMatch<decltype(MODULEENTRY32::szModule), char[256]>::value);
static_assert(TypeMatch<decltype(MODULEENTRY32::szExePath), char[260]>::value);

static_assert(offsetof(MODULEENTRY32, dwSize) == 0);
static_assert(offsetof(MODULEENTRY32, th32ModuleID) == 4);
static_assert(offsetof(MODULEENTRY32, th32ProcessID) == 8);
static_assert(offsetof(MODULEENTRY32, GlblcntUsage) == 0xC);
static_assert(offsetof(MODULEENTRY32, ProccntUsage) == 0x10);
static_assert(offsetof(MODULEENTRY32, modBaseAddr) == 0x18);
static_assert(offsetof(MODULEENTRY32, modBaseSize) == 0x20);
static_assert(offsetof(MODULEENTRY32, hModule) == 0x28);
static_assert(offsetof(MODULEENTRY32, szModule) == 0x30);
static_assert(offsetof(MODULEENTRY32, szExePath) == 0x130);

static_assert(sizeof(MODULEENTRY32) == 568);

typedef MODULEENTRY32 * PMODULEENTRY32;
typedef MODULEENTRY32 * LPMODULEENTRY32;

static_assert(TypeMatch<PMODULEENTRY32, MODULEENTRY32 *>::value);
static_assert(TypeMatch<LPMODULEENTRY32, MODULEENTRY32 *>::value);

static_assert(sizeof(PMODULEENTRY32) == 8);
static_assert(sizeof(LPMODULEENTRY32) == 8);

// MODULEENTRY32W

struct MODULEENTRY32W
{
	DWORD dwSize; // 0
	DWORD th32ModuleID; // 4
	DWORD th32ProcessID; // 8
	DWORD GlblcntUsage; // 0xC
	DWORD ProccntUsage; // 0x10
	_(4);
	BYTE* modBaseAddr; // 0x18
	DWORD modBaseSize; // 0x20
	_(4);
	HMODULE hModule; // 0x28
	WCHAR szModule[256]; // 0x30
	WCHAR szExePath[260]; // 0x230
};

static_assert(TypeMatch<decltype(MODULEENTRY32W::dwSize), DWORD>::value);
static_assert(TypeMatch<decltype(MODULEENTRY32W::th32ModuleID), DWORD>::value);
static_assert(TypeMatch<decltype(MODULEENTRY32W::th32ProcessID), DWORD>::value);
static_assert(TypeMatch<decltype(MODULEENTRY32W::GlblcntUsage), DWORD>::value);
static_assert(TypeMatch<decltype(MODULEENTRY32W::ProccntUsage), DWORD>::value);
static_assert(TypeMatch<decltype(MODULEENTRY32W::modBaseAddr), BYTE*>::value);
static_assert(TypeMatch<decltype(MODULEENTRY32W::modBaseSize), DWORD>::value);
static_assert(TypeMatch<decltype(MODULEENTRY32W::hModule), HMODULE>::value);
static_assert(TypeMatch<decltype(MODULEENTRY32W::szModule), WCHAR[256]>::value);
static_assert(TypeMatch<decltype(MODULEENTRY32W::szExePath), WCHAR[260]>::value);

static_assert(offsetof(MODULEENTRY32W, dwSize) == 0);
static_assert(offsetof(MODULEENTRY32W, th32ModuleID) == 4);
static_assert(offsetof(MODULEENTRY32W, th32ProcessID) == 8);
static_assert(offsetof(MODULEENTRY32W, GlblcntUsage) == 0xC);
static_assert(offsetof(MODULEENTRY32W, ProccntUsage) == 0x10);
static_assert(offsetof(MODULEENTRY32W, modBaseAddr) == 0x18);
static_assert(offsetof(MODULEENTRY32W, modBaseSize) == 0x20);
static_assert(offsetof(MODULEENTRY32W, hModule) == 0x28);
static_assert(offsetof(MODULEENTRY32W, szModule) == 0x30);
static_assert(offsetof(MODULEENTRY32W, szExePath) == 0x230);

static_assert(sizeof(MODULEENTRY32W) == 1080);

typedef MODULEENTRY32W * PMODULEENTRY32W;
typedef MODULEENTRY32W * LPMODULEENTRY32W;

static_assert(TypeMatch<PMODULEENTRY32W, MODULEENTRY32W *>::value);
static_assert(TypeMatch<LPMODULEENTRY32W, MODULEENTRY32W *>::value);

static_assert(sizeof(PMODULEENTRY32W) == 8);
static_assert(sizeof(LPMODULEENTRY32W) == 8);

// SECURITY_ATTRIBUTES

struct SECURITY_ATTRIBUTES
{
	DWORD nLength; // 0
	_(4);
	LPVOID lpSecurityDescriptor; // 8
	BOOL bInheritHandle; // 0x10
	_(4);
};

static_assert(TypeMatch<decltype(SECURITY_ATTRIBUTES::nLength), DWORD>::value);
static_assert(TypeMatch<decltype(SECURITY_ATTRIBUTES::lpSecurityDescriptor), LPVOID>::value);
static_assert(TypeMatch<decltype(SECURITY_ATTRIBUTES::bInheritHandle), BOOL>::value);

static_assert(offsetof(SECURITY_ATTRIBUTES, nLength) == 0);
static_assert(offsetof(SECURITY_ATTRIBUTES, lpSecurityDescriptor) == 8);
static_assert(offsetof(SECURITY_ATTRIBUTES, bInheritHandle) == 0x10);

static_assert(sizeof(SECURITY_ATTRIBUTES) == 24);

typedef SECURITY_ATTRIBUTES * PSECURITY_ATTRIBUTES;
typedef SECURITY_ATTRIBUTES * LPSECURITY_ATTRIBUTES;

static_assert(TypeMatch<PSECURITY_ATTRIBUTES, SECURITY_ATTRIBUTES *>::value);
static_assert(TypeMatch<LPSECURITY_ATTRIBUTES, SECURITY_ATTRIBUTES *>::value);

static_assert(sizeof(PSECURITY_ATTRIBUTES) == 8);
static_assert(sizeof(LPSECURITY_ATTRIBUTES) == 8);

// OVERLAPPED

struct OVERLAPPED
{
	ULONG_PTR Internal; // 0
	ULONG_PTR InternalHigh; // 8
	union
	{
		struct
		{
			DWORD Offset; // 0x10
			DWORD OffsetHigh; // 0x14
		}; // 0x10
		PVOID Pointer; // 0x10
	}; // 0x10
	HANDLE hEvent; // 0x18
};

static_assert(TypeMatch<decltype(OVERLAPPED::Internal), ULONG_PTR>::value);
static_assert(TypeMatch<decltype(OVERLAPPED::InternalHigh), ULONG_PTR>::value);
static_assert(TypeMatch<decltype(OVERLAPPED::Offset), DWORD>::value);
static_assert(TypeMatch<decltype(OVERLAPPED::OffsetHigh), DWORD>::value);
static_assert(TypeMatch<decltype(OVERLAPPED::Pointer), PVOID>::value);
static_assert(TypeMatch<decltype(OVERLAPPED::hEvent), HANDLE>::value);

static_assert(offsetof(OVERLAPPED, Internal) == 0);
static_assert(offsetof(OVERLAPPED, InternalHigh) == 8);
static_assert(offsetof(OVERLAPPED, Offset) == 0x10);
static_assert(offsetof(OVERLAPPED, OffsetHigh) == 0x14);
static_assert(offsetof(OVERLAPPED, Pointer) == 0x10);
static_assert(offsetof(OVERLAPPED, hEvent) == 0x18);

static_assert(sizeof(OVERLAPPED) == 32);

typedef OVERLAPPED * LPOVERLAPPED;

static_assert(TypeMatch<LPOVERLAPPED, OVERLAPPED *>::value);

static_assert(sizeof(LPOVERLAPPED) == 8);

// FILETIME

struct FILETIME
{
	DWORD dwLowDateTime; // 0
	DWORD dwHighDateTime; // 4
};

static_assert(TypeMatch<decltype(FILETIME::dwLowDateTime), DWORD>::value);
static_assert(TypeMatch<decltype(FILETIME::dwHighDateTime), DWORD>::value);

static_assert(offsetof(FILETIME, dwLowDateTime) == 0);
static_assert(offsetof(FILETIME, dwHighDateTime) == 4);

static_assert(sizeof(FILETIME) == 8);

typedef FILETIME * PFILETIME;
typedef FILETIME * LPFILETIME;

static_assert(TypeMatch<PFILETIME, FILETIME *>::value);
static_assert(TypeMatch<LPFILETIME, FILETIME *>::value);

static_assert(sizeof(PFILETIME) == 8);
static_assert(sizeof(LPFILETIME) == 8);

// BY_HANDLE_FILE_INFORMATION

struct BY_HANDLE_FILE_INFORMATION
{
	DWORD dwFileAttributes; // 0
	FILETIME ftCreationTime; // 4
	FILETIME ftLastAccessTime; // 0xC
	FILETIME ftLastWriteTime; // 0x14
	DWORD dwVolumeSerialNumber; // 0x1C
	DWORD nFileSizeHigh; // 0x20
	DWORD nFileSizeLow; // 0x24
	DWORD nNumberOfLinks; // 0x28
	DWORD nFileIndexHigh; // 0x2C
	DWORD nFileIndexLow; // 0x30
};

static_assert(TypeMatch<decltype(BY_HANDLE_FILE_INFORMATION::dwFileAttributes), DWORD>::value);
static_assert(TypeMatch<decltype(BY_HANDLE_FILE_INFORMATION::ftCreationTime), FILETIME>::value);
static_assert(TypeMatch<decltype(BY_HANDLE_FILE_INFORMATION::ftLastAccessTime), FILETIME>::value);
static_assert(TypeMatch<decltype(BY_HANDLE_FILE_INFORMATION::ftLastWriteTime), FILETIME>::value);
static_assert(TypeMatch<decltype(BY_HANDLE_FILE_INFORMATION::dwVolumeSerialNumber), DWORD>::value);
static_assert(TypeMatch<decltype(BY_HANDLE_FILE_INFORMATION::nFileSizeHigh), DWORD>::value);
static_assert(TypeMatch<decltype(BY_HANDLE_FILE_INFORMATION::nFileSizeLow), DWORD>::value);
static_assert(TypeMatch<decltype(BY_HANDLE_FILE_INFORMATION::nNumberOfLinks), DWORD>::value);
static_assert(TypeMatch<decltype(BY_HANDLE_FILE_INFORMATION::nFileIndexHigh), DWORD>::value);
static_assert(TypeMatch<decltype(BY_HANDLE_FILE_INFORMATION::nFileIndexLow), DWORD>::value);

static_assert(offsetof(BY_HANDLE_FILE_INFORMATION, dwFileAttributes) == 0);
static_assert(offsetof(BY_HANDLE_FILE_INFORMATION, ftCreationTime) == 4);
static_assert(offsetof(BY_HANDLE_FILE_INFORMATION, ftLastAccessTime) == 0xC);
static_assert(offsetof(BY_HANDLE_FILE_INFORMATION, ftLastWriteTime) == 0x14);
static_assert(offsetof(BY_HANDLE_FILE_INFORMATION, dwVolumeSerialNumber) == 0x1C);
static_assert(offsetof(BY_HANDLE_FILE_INFORMATION, nFileSizeHigh) == 0x20);
static_assert(offsetof(BY_HANDLE_FILE_INFORMATION, nFileSizeLow) == 0x24);
static_assert(offsetof(BY_HANDLE_FILE_INFORMATION, nNumberOfLinks) == 0x28);
static_assert(offsetof(BY_HANDLE_FILE_INFORMATION, nFileIndexHigh) == 0x2C);
static_assert(offsetof(BY_HANDLE_FILE_INFORMATION, nFileIndexLow) == 0x30);

static_assert(sizeof(BY_HANDLE_FILE_INFORMATION) == 52);

typedef BY_HANDLE_FILE_INFORMATION * PBY_HANDLE_FILE_INFORMATION;
typedef BY_HANDLE_FILE_INFORMATION * LPBY_HANDLE_FILE_INFORMATION;

static_assert(TypeMatch<PBY_HANDLE_FILE_INFORMATION, BY_HANDLE_FILE_INFORMATION *>::value);
static_assert(TypeMatch<LPBY_HANDLE_FILE_INFORMATION, BY_HANDLE_FILE_INFORMATION *>::value);

static_assert(sizeof(PBY_HANDLE_FILE_INFORMATION) == 8);
static_assert(sizeof(LPBY_HANDLE_FILE_INFORMATION) == 8);

// LARGE_INTEGER

union LARGE_INTEGER
{
	struct
	{
		DWORD LowPart; // 0
		LONG HighPart; // 4
	}; // 0
	LONGLONG QuadPart; // 0
};

static_assert(TypeMatch<decltype(LARGE_INTEGER::LowPart), DWORD>::value);
static_assert(TypeMatch<decltype(LARGE_INTEGER::HighPart), LONG>::value);
static_assert(TypeMatch<decltype(LARGE_INTEGER::QuadPart), LONGLONG>::value);

static_assert(offsetof(LARGE_INTEGER, LowPart) == 0);
static_assert(offsetof(LARGE_INTEGER, HighPart) == 4);
static_assert(offsetof(LARGE_INTEGER, QuadPart) == 0);

static_assert(sizeof(LARGE_INTEGER) == 8);

typedef LARGE_INTEGER * PLARGE_INTEGER;

static_assert(TypeMatch<PLARGE_INTEGER, LARGE_INTEGER *>::value);

static_assert(sizeof(PLARGE_INTEGER) == 8);

// SYSTEMTIME

struct SYSTEMTIME
{
	WORD wYear; // 0
	WORD wMonth; // 2
	WORD wDayOfWeek; // 4
	WORD wDay; // 6
	WORD wHour; // 8
	WORD wMinute; // 0xA
	WORD wSecond; // 0xC
	WORD wMilliseconds; // 0xE
};

static_assert(TypeMatch<decltype(SYSTEMTIME::wYear), WORD>::value);
static_assert(TypeMatch<decltype(SYSTEMTIME::wMonth), WORD>::value);
static_assert(TypeMatch<decltype(SYSTEMTIME::wDayOfWeek), WORD>::value);
static_assert(TypeMatch<decltype(SYSTEMTIME::wDay), WORD>::value);
static_assert(TypeMatch<decltype(SYSTEMTIME::wHour), WORD>::value);
static_assert(TypeMatch<decltype(SYSTEMTIME::wMinute), WORD>::value);
static_assert(TypeMatch<decltype(SYSTEMTIME::wSecond), WORD>::value);
static_assert(TypeMatch<decltype(SYSTEMTIME::wMilliseconds), WORD>::value);

static_assert(offsetof(SYSTEMTIME, wYear) == 0);
static_assert(offsetof(SYSTEMTIME, wMonth) == 2);
static_assert(offsetof(SYSTEMTIME, wDayOfWeek) == 4);
static_assert(offsetof(SYSTEMTIME, wDay) == 6);
static_assert(offsetof(SYSTEMTIME, wHour) == 8);
static_assert(offsetof(SYSTEMTIME, wMinute) == 0xA);
static_assert(offsetof(SYSTEMTIME, wSecond) == 0xC);
static_assert(offsetof(SYSTEMTIME, wMilliseconds) == 0xE);

static_assert(sizeof(SYSTEMTIME) == 16);

typedef SYSTEMTIME * PSYSTEMTIME;
typedef SYSTEMTIME * LPSYSTEMTIME;

static_assert(TypeMatch<PSYSTEMTIME, SYSTEMTIME *>::value);
static_assert(TypeMatch<LPSYSTEMTIME, SYSTEMTIME *>::value);

static_assert(sizeof(PSYSTEMTIME) == 8);
static_assert(sizeof(LPSYSTEMTIME) == 8);

// WNDCLASSEXA

struct WNDCLASSEXA
{
	UINT cbSize; // 0
	UINT style; // 4
	WNDPROC lpfnWndProc; // 8
	int cbClsExtra; // 0x10
	int cbWndExtra; // 0x14
	HINSTANCE hInstance; // 0x18
	HICON hIcon; // 0x20
	HCURSOR hCursor; // 0x28
	HBRUSH hbrBackground; // 0x30
	LPCSTR lpszMenuName; // 0x38
	LPCSTR lpszClassName; // 0x40
	HICON hIconSm; // 0x48
};

static_assert(TypeMatch<decltype(WNDCLASSEXA::cbSize), UINT>::value);
static_assert(TypeMatch<decltype(WNDCLASSEXA::style), UINT>::value);
static_assert(TypeMatch<decltype(WNDCLASSEXA::lpfnWndProc), WNDPROC>::value);
static_assert(TypeMatch<decltype(WNDCLASSEXA::cbClsExtra), int>::value);
static_assert(TypeMatch<decltype(WNDCLASSEXA::cbWndExtra), int>::value);
static_assert(TypeMatch<decltype(WNDCLASSEXA::hInstance), HINSTANCE>::value);
static_assert(TypeMatch<decltype(WNDCLASSEXA::hIcon), HICON>::value);
static_assert(TypeMatch<decltype(WNDCLASSEXA::hCursor), HCURSOR>::value);
static_assert(TypeMatch<decltype(WNDCLASSEXA::hbrBackground), HBRUSH>::value);
static_assert(TypeMatch<decltype(WNDCLASSEXA::lpszMenuName), LPCSTR>::value);
static_assert(TypeMatch<decltype(WNDCLASSEXA::lpszClassName), LPCSTR>::value);
static_assert(TypeMatch<decltype(WNDCLASSEXA::hIconSm), HICON>::value);

static_assert(offsetof(WNDCLASSEXA, cbSize) == 0);
static_assert(offsetof(WNDCLASSEXA, style) == 4);
static_assert(offsetof(WNDCLASSEXA, lpfnWndProc) == 8);
static_assert(offsetof(WNDCLASSEXA, cbClsExtra) == 0x10);
static_assert(offsetof(WNDCLASSEXA, cbWndExtra) == 0x14);
static_assert(offsetof(WNDCLASSEXA, hInstance) == 0x18);
static_assert(offsetof(WNDCLASSEXA, hIcon) == 0x20);
static_assert(offsetof(WNDCLASSEXA, hCursor) == 0x28);
static_assert(offsetof(WNDCLASSEXA, hbrBackground) == 0x30);
static_assert(offsetof(WNDCLASSEXA, lpszMenuName) == 0x38);
static_assert(offsetof(WNDCLASSEXA, lpszClassName) == 0x40);
static_assert(offsetof(WNDCLASSEXA, hIconSm) == 0x48);

static_assert(sizeof(WNDCLASSEXA) == 80);

typedef WNDCLASSEXA * PWNDCLASSEXA;
typedef WNDCLASSEXA * LPWNDCLASSEXA;

static_assert(TypeMatch<PWNDCLASSEXA, WNDCLASSEXA *>::value);
static_assert(TypeMatch<LPWNDCLASSEXA, WNDCLASSEXA *>::value);

static_assert(sizeof(PWNDCLASSEXA) == 8);
static_assert(sizeof(LPWNDCLASSEXA) == 8);

// WNDCLASSEXW

struct WNDCLASSEXW
{
	UINT cbSize; // 0
	UINT style; // 4
	WNDPROC lpfnWndProc; // 8
	int cbClsExtra; // 0x10
	int cbWndExtra; // 0x14
	HINSTANCE hInstance; // 0x18
	HICON hIcon; // 0x20
	HCURSOR hCursor; // 0x28
	HBRUSH hbrBackground; // 0x30
	LPCWSTR lpszMenuName; // 0x38
	LPCWSTR lpszClassName; // 0x40
	HICON hIconSm; // 0x48
};

static_assert(TypeMatch<decltype(WNDCLASSEXW::cbSize), UINT>::value);
static_assert(TypeMatch<decltype(WNDCLASSEXW::style), UINT>::value);
static_assert(TypeMatch<decltype(WNDCLASSEXW::lpfnWndProc), WNDPROC>::value);
static_assert(TypeMatch<decltype(WNDCLASSEXW::cbClsExtra), int>::value);
static_assert(TypeMatch<decltype(WNDCLASSEXW::cbWndExtra), int>::value);
static_assert(TypeMatch<decltype(WNDCLASSEXW::hInstance), HINSTANCE>::value);
static_assert(TypeMatch<decltype(WNDCLASSEXW::hIcon), HICON>::value);
static_assert(TypeMatch<decltype(WNDCLASSEXW::hCursor), HCURSOR>::value);
static_assert(TypeMatch<decltype(WNDCLASSEXW::hbrBackground), HBRUSH>::value);
static_assert(TypeMatch<decltype(WNDCLASSEXW::lpszMenuName), LPCWSTR>::value);
static_assert(TypeMatch<decltype(WNDCLASSEXW::lpszClassName), LPCWSTR>::value);
static_assert(TypeMatch<decltype(WNDCLASSEXW::hIconSm), HICON>::value);

static_assert(offsetof(WNDCLASSEXW, cbSize) == 0);
static_assert(offsetof(WNDCLASSEXW, style) == 4);
static_assert(offsetof(WNDCLASSEXW, lpfnWndProc) == 8);
static_assert(offsetof(WNDCLASSEXW, cbClsExtra) == 0x10);
static_assert(offsetof(WNDCLASSEXW, cbWndExtra) == 0x14);
static_assert(offsetof(WNDCLASSEXW, hInstance) == 0x18);
static_assert(offsetof(WNDCLASSEXW, hIcon) == 0x20);
static_assert(offsetof(WNDCLASSEXW, hCursor) == 0x28);
static_assert(offsetof(WNDCLASSEXW, hbrBackground) == 0x30);
static_assert(offsetof(WNDCLASSEXW, lpszMenuName) == 0x38);
static_assert(offsetof(WNDCLASSEXW, lpszClassName) == 0x40);
static_assert(offsetof(WNDCLASSEXW, hIconSm) == 0x48);

static_assert(sizeof(WNDCLASSEXW) == 80);

typedef WNDCLASSEXW * PWNDCLASSEXW;
typedef WNDCLASSEXW * LPWNDCLASSEXW;

static_assert(TypeMatch<PWNDCLASSEXW, WNDCLASSEXW *>::value);
static_assert(TypeMatch<LPWNDCLASSEXW, WNDCLASSEXW *>::value);

static_assert(sizeof(PWNDCLASSEXW) == 8);
static_assert(sizeof(LPWNDCLASSEXW) == 8);

// GUID

struct GUID
{
	unsigned long Data1; // 0
	unsigned short Data2; // 4
	unsigned short Data3; // 6
	unsigned char Data4[8]; // 8
};

static_assert(TypeMatch<decltype(GUID::Data1), unsigned long>::value);
static_assert(TypeMatch<decltype(GUID::Data2), unsigned short>::value);
static_assert(TypeMatch<decltype(GUID::Data3), unsigned short>::value);
static_assert(TypeMatch<decltype(GUID::Data4), unsigned char[8]>::value);

static_assert(offsetof(GUID, Data1) == 0);
static_assert(offsetof(GUID, Data2) == 4);
static_assert(offsetof(GUID, Data3) == 6);
static_assert(offsetof(GUID, Data4) == 8);

static_assert(sizeof(GUID) == 16);

typedef GUID * LPGUID;
typedef const GUID * LPCGUID;

static_assert(TypeMatch<LPGUID, GUID *>::value);
static_assert(TypeMatch<LPCGUID, const GUID *>::value);

static_assert(sizeof(LPGUID) == 8);
static_assert(sizeof(LPCGUID) == 8);

// LUID

struct LUID
{
	DWORD LowPart; // 0
	LONG HighPart; // 4
};

static_assert(TypeMatch<decltype(LUID::LowPart), DWORD>::value);
static_assert(TypeMatch<decltype(LUID::HighPart), LONG>::value);

static_assert(offsetof(LUID, LowPart) == 0);
static_assert(offsetof(LUID, HighPart) == 4);

static_assert(sizeof(LUID) == 8);

typedef LUID * PLUID;

static_assert(TypeMatch<PLUID, LUID *>::value);

static_assert(sizeof(PLUID) == 8);

// IID

typedef GUID IID;
typedef IID * LPIID;

static_assert(TypeMatch<IID, GUID>::value);
static_assert(TypeMatch<LPIID, IID *>::value);

static_assert(sizeof(IID) == 16);
static_assert(sizeof(LPIID) == 8);

#pragma pack(pop)

struct IUnknown;

extern "C" const IID IID_IUnknown;

extern "C" DWORD GetLastError();
extern "C" void SetLastError(DWORD dwErrCode);
extern "C" LPVOID VirtualAlloc
(
	LPVOID lpAddress,
	SIZE_T dwSize,
	DWORD flAllocationType,
	DWORD flProtect
);
extern "C" BOOL VirtualProtect
(
	LPVOID lpAddress,
	SIZE_T dwSize,
	DWORD flNewProtect,
	PDWORD lpflOldProtect
);
extern "C" BOOL VirtualFree
(
	LPVOID lpAddress,
	SIZE_T dwSize,
	DWORD dwFreeType
);
extern "C" SIZE_T VirtualQuery
(
	LPCVOID lpAddress,
	PMEMORY_BASIC_INFORMATION lpBuffer,
	SIZE_T dwLength
);
extern "C" LPVOID VirtualAllocEx
(
	HANDLE hProcess,
	LPVOID lpAddress,
	SIZE_T dwSize,
	DWORD flAllocationType,
	DWORD flProtect
);
extern "C" BOOL VirtualProtectEx
(
	HANDLE hProcess,
	LPVOID lpAddress,
	SIZE_T dwSize,
	DWORD flNewProtect,
	PDWORD lpflOldProtect
);
extern "C" SIZE_T VirtualQueryEx
(
	HANDLE hProcess,
	LPCVOID lpAddress,
	PMEMORY_BASIC_INFORMATION lpBuffer,
	SIZE_T dwLength
);
extern "C" HANDLE CreateFileA
(
	LPCSTR lpFileName,
	DWORD dwDesiredAccess,
	DWORD dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD dwCreationDisposition,
	DWORD dwFlagsAndAttributes,
	HANDLE hTemplateFile
);
extern "C" HANDLE CreateFileW
(
	LPCWSTR lpFileName,
	DWORD dwDesiredAccess,
	DWORD dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD dwCreationDisposition,
	DWORD dwFlagsAndAttributes,
	HANDLE hTemplateFile
);
extern "C" BOOL CloseHandle(HANDLE hObject);
extern "C" BOOL GetFileInformationByHandle
(
	HANDLE hFile,
	LPBY_HANDLE_FILE_INFORMATION lpFileInformation
);
extern "C" BOOL SetFilePointerEx
(
	HANDLE hFile,
	LARGE_INTEGER liDistanceToMove,
	PLARGE_INTEGER lpNewFilePointer,
	DWORD dwMoveMethod
);
extern "C" BOOL ReadFile
(
	HANDLE hFile,
	LPVOID lpBuffer,
	DWORD nNumberOfBytesToRead,
	LPDWORD lpNumberOfBytesRead,
	LPOVERLAPPED lpOverlapped
);
extern "C" BOOL WriteFile
(
	HANDLE hFile,
	LPCVOID lpBuffer,
	DWORD nNumberOfBytesToWrite,
	LPDWORD lpNumberOfBytesWritten,
	LPOVERLAPPED lpOverlapped
);
extern "C" BOOL CreateDirectoryA
(
	LPCSTR lpPathName,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes
);
extern "C" BOOL CreateDirectoryW
(
	LPCWSTR lpPathName,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes
);
extern "C" BOOL DeleteFileA(LPCSTR lpFileName);
extern "C" BOOL DeleteFileW(LPCWSTR lpFileName);
extern "C" void OutputDebugStringA(LPCSTR lpOutputString);
extern "C" void OutputDebugStringW(LPCWSTR lpOutputString);
extern "C" int MessageBoxA
(
	HWND hWnd,
	LPCSTR lpText,
	LPCSTR lpCaption,
	UINT uType
);
extern "C" int MessageBoxW
(
	HWND hWnd,
	LPCWSTR lpText,
	LPCWSTR lpCaption,
	UINT uType
);
extern "C" void GetLocalTime(LPSYSTEMTIME lpSystemTime);
extern "C" HANDLE CreateToolhelp32Snapshot
(
	DWORD dwFlags,
	DWORD th32ProcessID
);
extern "C" BOOL Module32FirstW
(
	HANDLE hSnapshot,
	LPMODULEENTRY32W lpme
);
extern "C" BOOL Module32NextW
(
	HANDLE hSnapshot,
	LPMODULEENTRY32W lpme
);
extern "C" BOOL Module32First
(
	HANDLE hSnapshot,
	LPMODULEENTRY32 lpme
);
extern "C" BOOL Module32Next
(
	HANDLE hSnapshot,
	LPMODULEENTRY32 lpme
);
extern "C" void GetSystemInfo(LPSYSTEM_INFO lpSystemInfo);
extern "C" BOOL QueryPerformanceCounter(LARGE_INTEGER* lpPerformanceCount);
extern "C" BOOL QueryPerformanceFrequency(LARGE_INTEGER* lpFrequency);
extern "C" int ShowCursor(BOOL bShow);
extern "C" BOOL GetCursorPos(LPPOINT lpPoint);
extern "C" HCURSOR LoadCursorA
(
	HINSTANCE hInstance,
	LPCSTR lpCursorName
);
extern "C" HCURSOR LoadCursorW
(
	HINSTANCE hInstance,
	LPCWSTR lpCursorName
);
extern "C" BOOL GetWindowRect
(
	HWND hWnd,
	LPRECT lpRect
);
extern "C" DWORD SetClassLongA
(
	HWND hWnd,
	int nIndex,
	LONG dwNewLong
);
extern "C" DWORD SetClassLongW
(
	HWND hWnd,
	int nIndex,
	LONG dwNewLong
);
extern "C" ULONG_PTR SetClassLongPtrA
(
	HWND hWnd,
	int nIndex,
	LONG_PTR dwNewLong
);
extern "C" ULONG_PTR SetClassLongPtrW
(
	HWND hWnd,
	int nIndex,
	LONG_PTR dwNewLong
);
extern "C" HMODULE LoadLibraryA(LPCSTR lpLibFileName);
extern "C" HMODULE LoadLibraryW(LPCWSTR lpLibFileName);
extern "C" FARPROC GetProcAddress
(
	HMODULE hModule,
	LPCSTR lpProcName
);
extern "C" HINSTANCE ShellExecuteA
(
	HWND hwnd,
	LPCSTR lpOperation,
	LPCSTR lpFile,
	LPCSTR lpParameters,
	LPCSTR lpDirectory,
	INT nShowCmd
);
extern "C" HINSTANCE ShellExecuteW
(
	HWND hwnd,
	LPCWSTR lpOperation,
	LPCWSTR lpFile,
	LPCWSTR lpParameters,
	LPCWSTR lpDirectory,
	INT nShowCmd
);
extern "C" ATOM RegisterClassExA(const WNDCLASSEXA*);
extern "C" ATOM RegisterClassExW(const WNDCLASSEXW*);
extern "C" HWND CreateWindowExA
(
	DWORD dwExStyle,
	LPCSTR lpClassName,
	LPCSTR lpWindowName,
	DWORD dwStyle,
	int X,
	int Y,
	int nWidth,
	int nHeight,
	HWND hWndParent,
	HMENU hMenu,
	HINSTANCE hInstance,
	LPVOID lpParam
);
extern "C" HWND CreateWindowExW
(
	DWORD dwExStyle,
	LPCWSTR lpClassName,
	LPCWSTR lpWindowName,
	DWORD dwStyle,
	int X,
	int Y,
	int nWidth,
	int nHeight,
	HWND hWndParent,
	HMENU hMenu,
	HINSTANCE hInstance,
	LPVOID lpParam
);
extern "C" BOOL ScreenToClient
(
	HWND hWnd,
	LPPOINT lpPoint
);
extern "C" BOOL PostMessageA
(
	HWND hWnd,
	UINT Msg,
	WPARAM wParam,
	LPARAM lParam
);
extern "C" BOOL PostMessageW
(
	HWND hWnd,
	UINT Msg,
	WPARAM wParam,
	LPARAM lParam
);
extern "C" BOOL SetWindowPos
(
	HWND hWnd,
	HWND hWndInsertAfter,
	int X,
	int Y,
	int cx,
	int cy,
	UINT uFlags
);
extern "C" void Sleep(DWORD dwMilliseconds);
extern "C" HWND GetForegroundWindow();
extern "C" HANDLE CreateThread
(
	LPSECURITY_ATTRIBUTES lpThreadAttributes,
	SIZE_T dwStackSize,
	LPTHREAD_START_ROUTINE lpStartAddress,
	LPVOID lpParameter,
	DWORD dwCreationFlags,
	LPDWORD lpThreadId
);
extern "C" UINT GetWindowsDirectoryA
(
	LPSTR lpBuffer,
	UINT uSize
);
extern "C" UINT GetWindowsDirectoryW
(
	LPWSTR lpBuffer,
	UINT uSize
);
extern "C" BOOL ClientToScreen
(
	HWND hWnd,
	LPPOINT lpPoint
);
extern "C" BOOL SetCursorPos
(
	int X,
	int Y
);
extern "C" LONG GetWindowLongA
(
	HWND hWnd,
	int nIndex
);
extern "C" LONG GetWindowLongW
(
	HWND hWnd,
	int nIndex
);
extern "C" LONG SetWindowLongA
(
	HWND hWnd,
	int nIndex,
	LONG dwNewLong
);
extern "C" LONG SetWindowLongW
(
	HWND hWnd,
	int nIndex,
	LONG dwNewLong
);
extern "C" LONG_PTR GetWindowLongPtrA
(
	HWND hWnd,
	int nIndex
);
extern "C" LONG_PTR GetWindowLongPtrW
(
	HWND hWnd,
	int nIndex
);
extern "C" LONG_PTR SetWindowLongPtrA
(
	HWND hWnd,
	int nIndex,
	LONG_PTR dwNewLong
);
extern "C" LONG_PTR SetWindowLongPtrW
(
	HWND hWnd,
	int nIndex,
	LONG_PTR dwNewLong
);
extern "C" BOOL GetClientRect
(
	HWND hWnd,
	LPRECT lpRect
);
extern "C" BOOL AdjustWindowRect
(
	LPRECT lpRect,
	DWORD dwStyle,
	BOOL bMenu
);
extern "C" BOOL AdjustWindowRectEx
(
	LPRECT lpRect,
	DWORD dwStyle,
	BOOL bMenu,
	DWORD dwExStyle
);
extern "C" BOOL AdjustWindowRectExForDpi
(
	LPRECT lpRect,
	DWORD dwStyle,
	BOOL bMenu,
	DWORD dwExStyle,
	UINT dpi
);
extern "C" HWND GetFocus();
extern "C" BOOL MoveWindow
(
	HWND hWnd,
	int X,
	int Y,
	int nWidth,
	int nHeight,
	BOOL bRepaint
);
extern "C" UINT GetSystemDirectoryA
(
	LPSTR lpBuffer,
	UINT uSize
);
extern "C" UINT GetSystemDirectoryW
(
	LPWSTR lpBuffer,
	UINT uSize
);

// IUnknown

struct __declspec(novtable) IUnknown
{
	virtual HRESULT QueryInterface
	(
		const IID& riid,
		void** ppvObject
	) = 0;
	virtual ULONG AddRef() = 0;
	virtual ULONG Release() = 0;
};

static_assert(sizeof(IUnknown) == 8);

// LPUNKNOWN

typedef IUnknown* LPUNKNOWN;

static_assert(TypeMatch<LPUNKNOWN, IUnknown*>::value);

static_assert(sizeof(LPUNKNOWN) == 8);

#pragma endregion

#else

#pragma region x86_32

// VOID

typedef void VOID;
typedef VOID * PVOID;
typedef VOID * LPVOID;
typedef const VOID * LPCVOID;

static_assert(TypeMatch<VOID, void>::value);
static_assert(TypeMatch<PVOID, VOID *>::value);
static_assert(TypeMatch<LPVOID, VOID *>::value);
static_assert(TypeMatch<LPCVOID, const VOID *>::value);

static_assert(sizeof(PVOID) == 4);
static_assert(sizeof(LPVOID) == 4);
static_assert(sizeof(LPCVOID) == 4);

// BOOL

typedef int BOOL;
typedef BOOL * PBOOL;
typedef BOOL * LPBOOL;

static_assert(TypeMatch<BOOL, int>::value);
static_assert(TypeMatch<PBOOL, BOOL *>::value);
static_assert(TypeMatch<LPBOOL, BOOL *>::value);

static_assert(sizeof(BOOL) == 4);
static_assert(sizeof(PBOOL) == 4);
static_assert(sizeof(LPBOOL) == 4);

// BYTE

typedef unsigned char BYTE;
typedef BYTE * PBYTE;
typedef BYTE * LPBYTE;
typedef const BYTE * LPCBYTE;

static_assert(TypeMatch<BYTE, unsigned char>::value);
static_assert(TypeMatch<PBYTE, BYTE *>::value);
static_assert(TypeMatch<LPBYTE, BYTE *>::value);
static_assert(TypeMatch<LPCBYTE, const BYTE *>::value);

static_assert(sizeof(BYTE) == 1);
static_assert(sizeof(PBYTE) == 4);
static_assert(sizeof(LPBYTE) == 4);
static_assert(sizeof(LPCBYTE) == 4);

// WORD

typedef unsigned short WORD;
typedef WORD * PWORD;
typedef WORD * LPWORD;

static_assert(TypeMatch<WORD, unsigned short>::value);
static_assert(TypeMatch<PWORD, WORD *>::value);
static_assert(TypeMatch<LPWORD, WORD *>::value);

static_assert(sizeof(WORD) == 2);
static_assert(sizeof(PWORD) == 4);
static_assert(sizeof(LPWORD) == 4);

// DWORD

typedef unsigned long DWORD;
typedef DWORD * PDWORD;
typedef DWORD * LPDWORD;

static_assert(TypeMatch<DWORD, unsigned long>::value);
static_assert(TypeMatch<PDWORD, DWORD *>::value);
static_assert(TypeMatch<LPDWORD, DWORD *>::value);

static_assert(sizeof(DWORD) == 4);
static_assert(sizeof(PDWORD) == 4);
static_assert(sizeof(LPDWORD) == 4);

// FLOAT

typedef float FLOAT;
typedef FLOAT * PFLOAT;

static_assert(TypeMatch<FLOAT, float>::value);
static_assert(TypeMatch<PFLOAT, FLOAT *>::value);

static_assert(sizeof(FLOAT) == 4);
static_assert(sizeof(PFLOAT) == 4);

// DOUBLE

typedef double DOUBLE;

static_assert(TypeMatch<DOUBLE, double>::value);

static_assert(sizeof(DOUBLE) == 8);

// CHAR

typedef char CHAR;
typedef CHAR * PCHAR;

static_assert(TypeMatch<CHAR, char>::value);
static_assert(TypeMatch<PCHAR, CHAR *>::value);

static_assert(sizeof(CHAR) == 1);
static_assert(sizeof(PCHAR) == 4);

// SHORT

typedef short SHORT;
typedef SHORT * PSHORT;

static_assert(TypeMatch<SHORT, short>::value);
static_assert(TypeMatch<PSHORT, SHORT *>::value);

static_assert(sizeof(SHORT) == 2);
static_assert(sizeof(PSHORT) == 4);

// LONG

typedef long LONG;
typedef LONG * PLONG;
typedef LONG * LPLONG;

static_assert(TypeMatch<LONG, long>::value);
static_assert(TypeMatch<PLONG, LONG *>::value);
static_assert(TypeMatch<LPLONG, LONG *>::value);

static_assert(sizeof(LONG) == 4);
static_assert(sizeof(PLONG) == 4);
static_assert(sizeof(LPLONG) == 4);

// INT

typedef int INT;
typedef INT * PINT;
typedef INT * LPINT;

static_assert(TypeMatch<INT, int>::value);
static_assert(TypeMatch<PINT, INT *>::value);
static_assert(TypeMatch<LPINT, INT *>::value);

static_assert(sizeof(INT) == 4);
static_assert(sizeof(PINT) == 4);
static_assert(sizeof(LPINT) == 4);

// WCHAR

typedef wchar_t WCHAR;
typedef WCHAR * PWCHAR;
typedef const WCHAR * LPCWCHAR;

static_assert(TypeMatch<WCHAR, wchar_t>::value);
static_assert(TypeMatch<PWCHAR, WCHAR *>::value);
static_assert(TypeMatch<LPCWCHAR, const WCHAR *>::value);

static_assert(sizeof(WCHAR) == 2);
static_assert(sizeof(PWCHAR) == 4);
static_assert(sizeof(LPCWCHAR) == 4);

// INT8

typedef signed char INT8;
typedef INT8 * PINT8;

static_assert(TypeMatch<INT8, signed char>::value);
static_assert(TypeMatch<PINT8, INT8 *>::value);

static_assert(sizeof(INT8) == 1);
static_assert(sizeof(PINT8) == 4);

// INT16

typedef signed short INT16;
typedef INT16 * PINT16;

static_assert(TypeMatch<INT16, signed short>::value);
static_assert(TypeMatch<PINT16, INT16 *>::value);

static_assert(sizeof(INT16) == 2);
static_assert(sizeof(PINT16) == 4);

// INT32

typedef signed int INT32;
typedef INT32 * PINT32;

static_assert(TypeMatch<INT32, signed int>::value);
static_assert(TypeMatch<PINT32, INT32 *>::value);

static_assert(sizeof(INT32) == 4);
static_assert(sizeof(PINT32) == 4);

// INT64

typedef signed long long INT64;
typedef INT64 * PINT64;

static_assert(TypeMatch<INT64, signed long long>::value);
static_assert(TypeMatch<PINT64, INT64 *>::value);

static_assert(sizeof(INT64) == 8);
static_assert(sizeof(PINT64) == 4);

// UINT8

typedef unsigned char UINT8;
typedef UINT8 * PUINT8;

static_assert(TypeMatch<UINT8, unsigned char>::value);
static_assert(TypeMatch<PUINT8, UINT8 *>::value);

static_assert(sizeof(UINT8) == 1);
static_assert(sizeof(PUINT8) == 4);

// UINT16

typedef unsigned short UINT16;
typedef UINT16 * PUINT16;

static_assert(TypeMatch<UINT16, unsigned short>::value);
static_assert(TypeMatch<PUINT16, UINT16 *>::value);

static_assert(sizeof(UINT16) == 2);
static_assert(sizeof(PUINT16) == 4);

// UINT32

typedef unsigned int UINT32;
typedef UINT32 * PUINT32;

static_assert(TypeMatch<UINT32, unsigned int>::value);
static_assert(TypeMatch<PUINT32, UINT32 *>::value);

static_assert(sizeof(UINT32) == 4);
static_assert(sizeof(PUINT32) == 4);

// UINT64

typedef unsigned long long UINT64;
typedef UINT64 * PUINT64;

static_assert(TypeMatch<UINT64, unsigned long long>::value);
static_assert(TypeMatch<PUINT64, UINT64 *>::value);

static_assert(sizeof(UINT64) == 8);
static_assert(sizeof(PUINT64) == 4);

// UCHAR

typedef unsigned char UCHAR;
typedef UCHAR * PUCHAR;

static_assert(TypeMatch<UCHAR, unsigned char>::value);
static_assert(TypeMatch<PUCHAR, UCHAR *>::value);

static_assert(sizeof(UCHAR) == 1);
static_assert(sizeof(PUCHAR) == 4);

// USHORT

typedef unsigned short USHORT;
typedef USHORT * PUSHORT;

static_assert(TypeMatch<USHORT, unsigned short>::value);
static_assert(TypeMatch<PUSHORT, USHORT *>::value);

static_assert(sizeof(USHORT) == 2);
static_assert(sizeof(PUSHORT) == 4);

// UINT

typedef unsigned int UINT;
typedef UINT * PUINT;
typedef UINT * LPUINT;

static_assert(TypeMatch<UINT, unsigned int>::value);
static_assert(TypeMatch<PUINT, UINT *>::value);
static_assert(TypeMatch<LPUINT, UINT *>::value);

static_assert(sizeof(UINT) == 4);
static_assert(sizeof(PUINT) == 4);
static_assert(sizeof(LPUINT) == 4);

// ULONG

typedef unsigned long ULONG;
typedef ULONG * PULONG;

static_assert(TypeMatch<ULONG, unsigned long>::value);
static_assert(TypeMatch<PULONG, ULONG *>::value);

static_assert(sizeof(ULONG) == 4);
static_assert(sizeof(PULONG) == 4);

// LONGLONG

typedef long long LONGLONG;
typedef LONGLONG * PLONGLONG;

static_assert(TypeMatch<LONGLONG, long long>::value);
static_assert(TypeMatch<PLONGLONG, LONGLONG *>::value);

static_assert(sizeof(LONGLONG) == 8);
static_assert(sizeof(PLONGLONG) == 4);

// ULONGLONG

typedef unsigned long long ULONGLONG;
typedef ULONGLONG * PULONGLONG;

static_assert(TypeMatch<ULONGLONG, unsigned long long>::value);
static_assert(TypeMatch<PULONGLONG, ULONGLONG *>::value);

static_assert(sizeof(ULONGLONG) == 8);
static_assert(sizeof(PULONGLONG) == 4);

// INT_PTR

typedef int INT_PTR;
typedef INT_PTR * PINT_PTR;

static_assert(TypeMatch<INT_PTR, int>::value);
static_assert(TypeMatch<PINT_PTR, INT_PTR *>::value);

static_assert(sizeof(INT_PTR) == 4);
static_assert(sizeof(PINT_PTR) == 4);

// UINT_PTR

typedef unsigned int UINT_PTR;
typedef UINT_PTR * PUINT_PTR;

static_assert(TypeMatch<UINT_PTR, unsigned int>::value);
static_assert(TypeMatch<PUINT_PTR, UINT_PTR *>::value);

static_assert(sizeof(UINT_PTR) == 4);
static_assert(sizeof(PUINT_PTR) == 4);

// LONG_PTR

typedef long LONG_PTR;
typedef LONG_PTR * PLONG_PTR;

static_assert(TypeMatch<LONG_PTR, long>::value);
static_assert(TypeMatch<PLONG_PTR, LONG_PTR *>::value);

static_assert(sizeof(LONG_PTR) == 4);
static_assert(sizeof(PLONG_PTR) == 4);

// ULONG_PTR

typedef unsigned long ULONG_PTR;
typedef ULONG_PTR * PULONG_PTR;

static_assert(TypeMatch<ULONG_PTR, unsigned long>::value);
static_assert(TypeMatch<PULONG_PTR, ULONG_PTR *>::value);

static_assert(sizeof(ULONG_PTR) == 4);
static_assert(sizeof(PULONG_PTR) == 4);

// DWORD_PTR

typedef unsigned long DWORD_PTR;
typedef DWORD_PTR * PDWORD_PTR;

static_assert(TypeMatch<DWORD_PTR, unsigned long>::value);
static_assert(TypeMatch<PDWORD_PTR, DWORD_PTR *>::value);

static_assert(sizeof(DWORD_PTR) == 4);
static_assert(sizeof(PDWORD_PTR) == 4);

// SIZE_T

typedef unsigned long SIZE_T;
typedef SIZE_T * PSIZE_T;

static_assert(TypeMatch<SIZE_T, unsigned long>::value);
static_assert(TypeMatch<PSIZE_T, SIZE_T *>::value);

static_assert(sizeof(SIZE_T) == 4);
static_assert(sizeof(PSIZE_T) == 4);

// HANDLE

typedef void* HANDLE;
typedef HANDLE * PHANDLE;
typedef HANDLE * LPHANDLE;

static_assert(TypeMatch<HANDLE, void*>::value);
static_assert(TypeMatch<PHANDLE, HANDLE *>::value);
static_assert(TypeMatch<LPHANDLE, HANDLE *>::value);

static_assert(sizeof(HANDLE) == 4);
static_assert(sizeof(PHANDLE) == 4);
static_assert(sizeof(LPHANDLE) == 4);

// HINSTANCE

typedef HANDLE HINSTANCE;

static_assert(sizeof(HINSTANCE) == 4);

// HMODULE

typedef HANDLE HMODULE;

static_assert(sizeof(HMODULE) == 4);

// HWND

typedef HANDLE HWND;

static_assert(sizeof(HWND) == 4);

// HMENU

typedef HANDLE HMENU;

static_assert(sizeof(HMENU) == 4);

// HICON

typedef HANDLE HICON;

static_assert(sizeof(HICON) == 4);

// HCURSOR

typedef HANDLE HCURSOR;

static_assert(sizeof(HCURSOR) == 4);

// HBRUSH

typedef HANDLE HBRUSH;

static_assert(sizeof(HBRUSH) == 4);

// HMONITOR

typedef HANDLE HMONITOR;

static_assert(sizeof(HMONITOR) == 4);

// HRESULT

typedef long HRESULT;

static_assert(TypeMatch<HRESULT, long>::value);

static_assert(sizeof(HRESULT) == 4);

// WPARAM

typedef UINT_PTR WPARAM;

static_assert(TypeMatch<WPARAM, UINT_PTR>::value);

static_assert(sizeof(WPARAM) == 4);

// LPARAM

typedef LONG_PTR LPARAM;

static_assert(TypeMatch<LPARAM, LONG_PTR>::value);

static_assert(sizeof(LPARAM) == 4);

// LRESULT

typedef LONG_PTR LRESULT;

static_assert(TypeMatch<LRESULT, LONG_PTR>::value);

static_assert(sizeof(LRESULT) == 4);

// PSTR

typedef CHAR * PSTR;

static_assert(TypeMatch<PSTR, CHAR *>::value);

static_assert(sizeof(PSTR) == 4);

// LPSTR

typedef CHAR * LPSTR;

static_assert(TypeMatch<LPSTR, CHAR *>::value);

static_assert(sizeof(LPSTR) == 4);

// LPCSTR

typedef const CHAR * LPCSTR;

static_assert(TypeMatch<LPCSTR, const CHAR *>::value);

static_assert(sizeof(LPCSTR) == 4);

// PWSTR

typedef WCHAR * PWSTR;

static_assert(TypeMatch<PWSTR, WCHAR *>::value);

static_assert(sizeof(PWSTR) == 4);

// LPWSTR

typedef WCHAR * LPWSTR;

static_assert(TypeMatch<LPWSTR, WCHAR *>::value);

static_assert(sizeof(LPWSTR) == 4);

// LPCWSTR

typedef const WCHAR * LPCWSTR;

static_assert(TypeMatch<LPCWSTR, const WCHAR *>::value);

static_assert(sizeof(LPCWSTR) == 4);

// ATOM

typedef WORD ATOM;

static_assert(TypeMatch<ATOM, WORD>::value);

static_assert(sizeof(ATOM) == 2);

// HDC

typedef HANDLE HDC;

static_assert(sizeof(HDC) == 4);

// FARPROC

typedef INT_PTR(__stdcall * FARPROC)();

static_assert(sizeof(FARPROC) == 4);

// WNDPROC

typedef LRESULT(__stdcall * WNDPROC)
(
	HWND,
	UINT,
	WPARAM,
	LPARAM
);

static_assert(sizeof(WNDPROC) == 4);

// PTHREAD_START_ROUTINE

typedef DWORD(__stdcall * PTHREAD_START_ROUTINE)(LPVOID lpThreadParameter);

static_assert(sizeof(PTHREAD_START_ROUTINE) == 4);

// LPTHREAD_START_ROUTINE

typedef PTHREAD_START_ROUTINE LPTHREAD_START_ROUTINE;

static_assert(TypeMatch<LPTHREAD_START_ROUTINE, PTHREAD_START_ROUTINE>::value);

static_assert(sizeof(LPTHREAD_START_ROUTINE) == 4);

enum
{
	PAGE_NOACCESS=1,
	PAGE_READONLY=2,
	PAGE_READWRITE=4,
	PAGE_WRITECOPY=8,
	PAGE_EXECUTE=0x10,
	PAGE_EXECUTE_READ=0x20,
	PAGE_EXECUTE_READWRITE=0x40,
	PAGE_EXECUTE_WRITECOPY=0x80,
	MEM_COMMIT=0x1000,
	MEM_RESERVE=0x2000,
	MEM_DECOMMIT=0x4000,
	MEM_RELEASE=0x8000,
	MEM_FREE=0x10000,
	GENERIC_READ=0x80000000,
	GENERIC_WRITE=0x40000000,
	GENERIC_EXECUTE=0x20000000,
	GENERIC_ALL=0x10000000,
	CREATE_NEW=1,
	CREATE_ALWAYS=2,
	OPEN_EXISTING=3,
	OPEN_ALWAYS=4,
	TRUNCATE_EXISTING=5,
	FILE_APPEND_DATA=4,
	FILE_ATTRIBUTE_READONLY=1,
	FILE_ATTRIBUTE_HIDDEN=2,
	FILE_ATTRIBUTE_SYSTEM=4,
	FILE_ATTRIBUTE_DIRECTORY=0x10,
	FILE_ATTRIBUTE_ARCHIVE=0x20,
	FILE_ATTRIBUTE_DEVICE=0x40,
	FILE_ATTRIBUTE_NORMAL=0x80,
	FILE_ATTRIBUTE_TEMPORARY=0x100,
	FILE_BEGIN=0,
	FILE_CURRENT=1,
	FILE_END=2,
	TH32CS_SNAPHEAPLIST=1,
	TH32CS_SNAPPROCESS=2,
	TH32CS_SNAPTHREAD=4,
	TH32CS_SNAPMODULE=8,
	TH32CS_SNAPMODULE32=0x10,
	TH32CS_INHERIT=0x80000000,
	GWL_STYLE=-16,
	GWL_EXSTYLE=-20,
	GWL_ID=-12,
	GWLP_WNDPROC=-4,
	GWLP_HINSTANCE=-6,
	GWLP_HWNDPARENT=-8,
	GWLP_USERDATA=-21,
	GWLP_ID=-12,
	GCL_CBWNDEXTRA=-18,
	GCL_CBCLSEXTRA=-20,
	GCL_STYLE=-26,
	GCW_ATOM=-32,
	GCLP_MENUNAME=-8,
	GCLP_HBRBACKGROUND=-10,
	GCLP_HCURSOR=-12,
	GCLP_HICON=-14,
	GCLP_HMODULE=-16,
	GCLP_WNDPROC=-24,
	GCLP_HICONSM=-34,
	WM_USER=0x400,
	S_OK=0,
	S_FALSE=1,
	WHEEL_DELTA=120,
	WM_SETCURSOR=0x0020,
	WM_CHAR=0x0102,
	DLL_PROCESS_DETACH=0,
	DLL_PROCESS_ATTACH=1,
	DLL_THREAD_ATTACH=2,
	DLL_THREAD_DETACH=3,
	SW_HIDE=0,
	SW_SHOWNORMAL=1,
	SW_NORMAL=1,
	SW_SHOWMINIMIZED=2,
	SW_SHOWMAXIMIZED=3,
	SW_MAXIMIZE=3,
	SW_SHOWNOACTIVATE=4,
	SW_SHOW=5,
	SW_MINIMIZE=6,
	SW_SHOWMINNOACTIVE=7,
	SW_SHOWNA=8,
	SW_RESTORE=9,
	SW_SHOWDEFAULT=10,
	SW_FORCEMINIMIZE=11,
	SW_MAX=11,
	WM_SIZE=0x0005,
	WS_OVERLAPPED=0x00000000,
	WS_POPUP=0x80000000,
	WS_CHILD=0x40000000,
	WS_MINIMIZE=0x20000000,
	WS_VISIBLE=0x10000000,
	WS_DISABLED=0x08000000,
	WS_CLIPSIBLINGS=0x04000000,
	WS_CLIPCHILDREN=0x02000000,
	WS_MAXIMIZE=0x01000000,
	WS_CAPTION=0x00C00000,
	WS_BORDER=0x00800000,
	WS_DLGFRAME=0x00400000,
	WS_VSCROLL=0x00200000,
	WS_HSCROLL=0x00100000,
	WS_SYSMENU=0x00080000,
	WS_THICKFRAME=0x00040000,
	WS_GROUP=0x00020000,
	WS_TABSTOP=0x00010000,
	WS_MINIMIZEBOX=0x00020000,
	WS_MAXIMIZEBOX=0x00010000,
	WS_TILED=0x00000000,
	WS_ICONIC=0x20000000,
	WS_SIZEBOX=0x00040000,
	WS_OVERLAPPEDWINDOW=0x00CF0000,
	WS_POPUPWINDOW=0x80880000,
	WS_CHILDWINDOW=0x40000000,
	WS_TILEDWINDOW=0x00CF0000,
	WM_STYLECHANGING=0x007C,
	WM_STYLECHANGED=0x007D,
	WM_DISPLAYCHANGE=0x007E,
	WM_SHOWWINDOW=0x0018,
};

const auto INVALID_HANDLE_VALUE = reinterpret_cast<HANDLE>(-1);
const auto IDC_ARROW = reinterpret_cast<LPSTR>(32512);
const auto IDC_IBEAM = reinterpret_cast<LPSTR>(32513);
const auto IDC_WAIT = reinterpret_cast<LPSTR>(32514);
const auto IDC_CROSS = reinterpret_cast<LPSTR>(32515);
const auto IDC_UPARROW = reinterpret_cast<LPSTR>(32516);
const auto IDC_SIZE = reinterpret_cast<LPSTR>(32640);
const auto IDC_ICON = reinterpret_cast<LPSTR>(32641);
const auto IDC_SIZENWSE = reinterpret_cast<LPSTR>(32642);
const auto IDC_SIZENESW = reinterpret_cast<LPSTR>(32643);
const auto IDC_SIZEWE = reinterpret_cast<LPSTR>(32644);
const auto IDC_SIZENS = reinterpret_cast<LPSTR>(32645);
const auto IDC_SIZEALL = reinterpret_cast<LPSTR>(32646);
const auto IDC_NO = reinterpret_cast<LPSTR>(32648);
const auto IDC_HAND = reinterpret_cast<LPSTR>(32649);
const auto IDC_APPSTARTING = reinterpret_cast<LPSTR>(32650);
const auto IDC_HELP = reinterpret_cast<LPSTR>(32651);
const auto IDC_PIN = reinterpret_cast<LPSTR>(32671);
const auto IDC_PERSON = reinterpret_cast<LPSTR>(32672);

#pragma pack(push, 1)

// RECT

struct RECT
{
	LONG left; // 0
	LONG top; // 4
	LONG right; // 8
	LONG bottom; // 0xC
};

static_assert(TypeMatch<decltype(RECT::left), LONG>::value);
static_assert(TypeMatch<decltype(RECT::top), LONG>::value);
static_assert(TypeMatch<decltype(RECT::right), LONG>::value);
static_assert(TypeMatch<decltype(RECT::bottom), LONG>::value);

static_assert(offsetof(RECT, left) == 0);
static_assert(offsetof(RECT, top) == 4);
static_assert(offsetof(RECT, right) == 8);
static_assert(offsetof(RECT, bottom) == 0xC);

static_assert(sizeof(RECT) == 16);

typedef RECT * PRECT;
typedef RECT * LPRECT;
typedef const RECT * LPCRECT;

static_assert(TypeMatch<PRECT, RECT *>::value);
static_assert(TypeMatch<LPRECT, RECT *>::value);
static_assert(TypeMatch<LPCRECT, const RECT *>::value);

static_assert(sizeof(PRECT) == 4);
static_assert(sizeof(LPRECT) == 4);
static_assert(sizeof(LPCRECT) == 4);

// POINT

struct POINT
{
	LONG x; // 0
	LONG y; // 4
};

static_assert(TypeMatch<decltype(POINT::x), LONG>::value);
static_assert(TypeMatch<decltype(POINT::y), LONG>::value);

static_assert(offsetof(POINT, x) == 0);
static_assert(offsetof(POINT, y) == 4);

static_assert(sizeof(POINT) == 8);

typedef POINT * PPOINT;
typedef POINT * LPPOINT;

static_assert(TypeMatch<PPOINT, POINT *>::value);
static_assert(TypeMatch<LPPOINT, POINT *>::value);

static_assert(sizeof(PPOINT) == 4);
static_assert(sizeof(LPPOINT) == 4);

// SIZE

struct SIZE
{
	LONG cx; // 0
	LONG cy; // 4
};

static_assert(TypeMatch<decltype(SIZE::cx), LONG>::value);
static_assert(TypeMatch<decltype(SIZE::cy), LONG>::value);

static_assert(offsetof(SIZE, cx) == 0);
static_assert(offsetof(SIZE, cy) == 4);

static_assert(sizeof(SIZE) == 8);

typedef SIZE * PSIZE;
typedef SIZE * LPSIZE;

static_assert(TypeMatch<PSIZE, SIZE *>::value);
static_assert(TypeMatch<LPSIZE, SIZE *>::value);

static_assert(sizeof(PSIZE) == 4);
static_assert(sizeof(LPSIZE) == 4);

// SYSTEM_INFO

struct SYSTEM_INFO
{
	union
	{
		DWORD dwOemId; // 0
		struct
		{
			WORD wProcessorArchitecture; // 0
			WORD wReserved; // 2
		}; // 0
	}; // 0
	DWORD dwPageSize; // 4
	LPVOID lpMinimumApplicationAddress; // 8
	LPVOID lpMaximumApplicationAddress; // 0xC
	DWORD_PTR dwActiveProcessorMask; // 0x10
	DWORD dwNumberOfProcessors; // 0x14
	DWORD dwProcessorType; // 0x18
	DWORD dwAllocationGranularity; // 0x1C
	WORD wProcessorLevel; // 0x20
	WORD wProcessorRevision; // 0x22
};

static_assert(TypeMatch<decltype(SYSTEM_INFO::dwOemId), DWORD>::value);
static_assert(TypeMatch<decltype(SYSTEM_INFO::wProcessorArchitecture), WORD>::value);
static_assert(TypeMatch<decltype(SYSTEM_INFO::wReserved), WORD>::value);
static_assert(TypeMatch<decltype(SYSTEM_INFO::dwPageSize), DWORD>::value);
static_assert(TypeMatch<decltype(SYSTEM_INFO::lpMinimumApplicationAddress), LPVOID>::value);
static_assert(TypeMatch<decltype(SYSTEM_INFO::lpMaximumApplicationAddress), LPVOID>::value);
static_assert(TypeMatch<decltype(SYSTEM_INFO::dwActiveProcessorMask), DWORD_PTR>::value);
static_assert(TypeMatch<decltype(SYSTEM_INFO::dwNumberOfProcessors), DWORD>::value);
static_assert(TypeMatch<decltype(SYSTEM_INFO::dwProcessorType), DWORD>::value);
static_assert(TypeMatch<decltype(SYSTEM_INFO::dwAllocationGranularity), DWORD>::value);
static_assert(TypeMatch<decltype(SYSTEM_INFO::wProcessorLevel), WORD>::value);
static_assert(TypeMatch<decltype(SYSTEM_INFO::wProcessorRevision), WORD>::value);

static_assert(offsetof(SYSTEM_INFO, dwOemId) == 0);
static_assert(offsetof(SYSTEM_INFO, wProcessorArchitecture) == 0);
static_assert(offsetof(SYSTEM_INFO, wReserved) == 2);
static_assert(offsetof(SYSTEM_INFO, dwPageSize) == 4);
static_assert(offsetof(SYSTEM_INFO, lpMinimumApplicationAddress) == 8);
static_assert(offsetof(SYSTEM_INFO, lpMaximumApplicationAddress) == 0xC);
static_assert(offsetof(SYSTEM_INFO, dwActiveProcessorMask) == 0x10);
static_assert(offsetof(SYSTEM_INFO, dwNumberOfProcessors) == 0x14);
static_assert(offsetof(SYSTEM_INFO, dwProcessorType) == 0x18);
static_assert(offsetof(SYSTEM_INFO, dwAllocationGranularity) == 0x1C);
static_assert(offsetof(SYSTEM_INFO, wProcessorLevel) == 0x20);
static_assert(offsetof(SYSTEM_INFO, wProcessorRevision) == 0x22);

static_assert(sizeof(SYSTEM_INFO) == 36);

typedef SYSTEM_INFO * LPSYSTEM_INFO;

static_assert(TypeMatch<LPSYSTEM_INFO, SYSTEM_INFO *>::value);

static_assert(sizeof(LPSYSTEM_INFO) == 4);

// MEMORY_BASIC_INFORMATION

struct MEMORY_BASIC_INFORMATION
{
	PVOID BaseAddress; // 0
	PVOID AllocationBase; // 4
	DWORD AllocationProtect; // 8
	SIZE_T RegionSize; // 0xC
	DWORD State; // 0x10
	DWORD Protect; // 0x14
	DWORD Type; // 0x18
};

static_assert(TypeMatch<decltype(MEMORY_BASIC_INFORMATION::BaseAddress), PVOID>::value);
static_assert(TypeMatch<decltype(MEMORY_BASIC_INFORMATION::AllocationBase), PVOID>::value);
static_assert(TypeMatch<decltype(MEMORY_BASIC_INFORMATION::AllocationProtect), DWORD>::value);
static_assert(TypeMatch<decltype(MEMORY_BASIC_INFORMATION::RegionSize), SIZE_T>::value);
static_assert(TypeMatch<decltype(MEMORY_BASIC_INFORMATION::State), DWORD>::value);
static_assert(TypeMatch<decltype(MEMORY_BASIC_INFORMATION::Protect), DWORD>::value);
static_assert(TypeMatch<decltype(MEMORY_BASIC_INFORMATION::Type), DWORD>::value);

static_assert(offsetof(MEMORY_BASIC_INFORMATION, BaseAddress) == 0);
static_assert(offsetof(MEMORY_BASIC_INFORMATION, AllocationBase) == 4);
static_assert(offsetof(MEMORY_BASIC_INFORMATION, AllocationProtect) == 8);
static_assert(offsetof(MEMORY_BASIC_INFORMATION, RegionSize) == 0xC);
static_assert(offsetof(MEMORY_BASIC_INFORMATION, State) == 0x10);
static_assert(offsetof(MEMORY_BASIC_INFORMATION, Protect) == 0x14);
static_assert(offsetof(MEMORY_BASIC_INFORMATION, Type) == 0x18);

static_assert(sizeof(MEMORY_BASIC_INFORMATION) == 28);

typedef MEMORY_BASIC_INFORMATION * PMEMORY_BASIC_INFORMATION;

static_assert(TypeMatch<PMEMORY_BASIC_INFORMATION, MEMORY_BASIC_INFORMATION *>::value);

static_assert(sizeof(PMEMORY_BASIC_INFORMATION) == 4);

// MODULEENTRY32

struct MODULEENTRY32
{
	DWORD dwSize; // 0
	DWORD th32ModuleID; // 4
	DWORD th32ProcessID; // 8
	DWORD GlblcntUsage; // 0xC
	DWORD ProccntUsage; // 0x10
	BYTE* modBaseAddr; // 0x14
	DWORD modBaseSize; // 0x18
	HMODULE hModule; // 0x1C
	char szModule[256]; // 0x20
	char szExePath[260]; // 0x120
};

static_assert(TypeMatch<decltype(MODULEENTRY32::dwSize), DWORD>::value);
static_assert(TypeMatch<decltype(MODULEENTRY32::th32ModuleID), DWORD>::value);
static_assert(TypeMatch<decltype(MODULEENTRY32::th32ProcessID), DWORD>::value);
static_assert(TypeMatch<decltype(MODULEENTRY32::GlblcntUsage), DWORD>::value);
static_assert(TypeMatch<decltype(MODULEENTRY32::ProccntUsage), DWORD>::value);
static_assert(TypeMatch<decltype(MODULEENTRY32::modBaseAddr), BYTE*>::value);
static_assert(TypeMatch<decltype(MODULEENTRY32::modBaseSize), DWORD>::value);
static_assert(TypeMatch<decltype(MODULEENTRY32::hModule), HMODULE>::value);
static_assert(TypeMatch<decltype(MODULEENTRY32::szModule), char[256]>::value);
static_assert(TypeMatch<decltype(MODULEENTRY32::szExePath), char[260]>::value);

static_assert(offsetof(MODULEENTRY32, dwSize) == 0);
static_assert(offsetof(MODULEENTRY32, th32ModuleID) == 4);
static_assert(offsetof(MODULEENTRY32, th32ProcessID) == 8);
static_assert(offsetof(MODULEENTRY32, GlblcntUsage) == 0xC);
static_assert(offsetof(MODULEENTRY32, ProccntUsage) == 0x10);
static_assert(offsetof(MODULEENTRY32, modBaseAddr) == 0x14);
static_assert(offsetof(MODULEENTRY32, modBaseSize) == 0x18);
static_assert(offsetof(MODULEENTRY32, hModule) == 0x1C);
static_assert(offsetof(MODULEENTRY32, szModule) == 0x20);
static_assert(offsetof(MODULEENTRY32, szExePath) == 0x120);

static_assert(sizeof(MODULEENTRY32) == 548);

typedef MODULEENTRY32 * PMODULEENTRY32;
typedef MODULEENTRY32 * LPMODULEENTRY32;

static_assert(TypeMatch<PMODULEENTRY32, MODULEENTRY32 *>::value);
static_assert(TypeMatch<LPMODULEENTRY32, MODULEENTRY32 *>::value);

static_assert(sizeof(PMODULEENTRY32) == 4);
static_assert(sizeof(LPMODULEENTRY32) == 4);

// MODULEENTRY32W

struct MODULEENTRY32W
{
	DWORD dwSize; // 0
	DWORD th32ModuleID; // 4
	DWORD th32ProcessID; // 8
	DWORD GlblcntUsage; // 0xC
	DWORD ProccntUsage; // 0x10
	BYTE* modBaseAddr; // 0x14
	DWORD modBaseSize; // 0x18
	HMODULE hModule; // 0x1C
	WCHAR szModule[256]; // 0x20
	WCHAR szExePath[260]; // 0x220
};

static_assert(TypeMatch<decltype(MODULEENTRY32W::dwSize), DWORD>::value);
static_assert(TypeMatch<decltype(MODULEENTRY32W::th32ModuleID), DWORD>::value);
static_assert(TypeMatch<decltype(MODULEENTRY32W::th32ProcessID), DWORD>::value);
static_assert(TypeMatch<decltype(MODULEENTRY32W::GlblcntUsage), DWORD>::value);
static_assert(TypeMatch<decltype(MODULEENTRY32W::ProccntUsage), DWORD>::value);
static_assert(TypeMatch<decltype(MODULEENTRY32W::modBaseAddr), BYTE*>::value);
static_assert(TypeMatch<decltype(MODULEENTRY32W::modBaseSize), DWORD>::value);
static_assert(TypeMatch<decltype(MODULEENTRY32W::hModule), HMODULE>::value);
static_assert(TypeMatch<decltype(MODULEENTRY32W::szModule), WCHAR[256]>::value);
static_assert(TypeMatch<decltype(MODULEENTRY32W::szExePath), WCHAR[260]>::value);

static_assert(offsetof(MODULEENTRY32W, dwSize) == 0);
static_assert(offsetof(MODULEENTRY32W, th32ModuleID) == 4);
static_assert(offsetof(MODULEENTRY32W, th32ProcessID) == 8);
static_assert(offsetof(MODULEENTRY32W, GlblcntUsage) == 0xC);
static_assert(offsetof(MODULEENTRY32W, ProccntUsage) == 0x10);
static_assert(offsetof(MODULEENTRY32W, modBaseAddr) == 0x14);
static_assert(offsetof(MODULEENTRY32W, modBaseSize) == 0x18);
static_assert(offsetof(MODULEENTRY32W, hModule) == 0x1C);
static_assert(offsetof(MODULEENTRY32W, szModule) == 0x20);
static_assert(offsetof(MODULEENTRY32W, szExePath) == 0x220);

static_assert(sizeof(MODULEENTRY32W) == 1064);

typedef MODULEENTRY32W * PMODULEENTRY32W;
typedef MODULEENTRY32W * LPMODULEENTRY32W;

static_assert(TypeMatch<PMODULEENTRY32W, MODULEENTRY32W *>::value);
static_assert(TypeMatch<LPMODULEENTRY32W, MODULEENTRY32W *>::value);

static_assert(sizeof(PMODULEENTRY32W) == 4);
static_assert(sizeof(LPMODULEENTRY32W) == 4);

// SECURITY_ATTRIBUTES

struct SECURITY_ATTRIBUTES
{
	DWORD nLength; // 0
	LPVOID lpSecurityDescriptor; // 4
	BOOL bInheritHandle; // 8
};

static_assert(TypeMatch<decltype(SECURITY_ATTRIBUTES::nLength), DWORD>::value);
static_assert(TypeMatch<decltype(SECURITY_ATTRIBUTES::lpSecurityDescriptor), LPVOID>::value);
static_assert(TypeMatch<decltype(SECURITY_ATTRIBUTES::bInheritHandle), BOOL>::value);

static_assert(offsetof(SECURITY_ATTRIBUTES, nLength) == 0);
static_assert(offsetof(SECURITY_ATTRIBUTES, lpSecurityDescriptor) == 4);
static_assert(offsetof(SECURITY_ATTRIBUTES, bInheritHandle) == 8);

static_assert(sizeof(SECURITY_ATTRIBUTES) == 12);

typedef SECURITY_ATTRIBUTES * PSECURITY_ATTRIBUTES;
typedef SECURITY_ATTRIBUTES * LPSECURITY_ATTRIBUTES;

static_assert(TypeMatch<PSECURITY_ATTRIBUTES, SECURITY_ATTRIBUTES *>::value);
static_assert(TypeMatch<LPSECURITY_ATTRIBUTES, SECURITY_ATTRIBUTES *>::value);

static_assert(sizeof(PSECURITY_ATTRIBUTES) == 4);
static_assert(sizeof(LPSECURITY_ATTRIBUTES) == 4);

// OVERLAPPED

struct OVERLAPPED
{
	ULONG_PTR Internal; // 0
	ULONG_PTR InternalHigh; // 4
	union
	{
		struct
		{
			DWORD Offset; // 8
			DWORD OffsetHigh; // 0xC
		}; // 8
		PVOID Pointer; // 8
	}; // 8
	HANDLE hEvent; // 0x10
};

static_assert(TypeMatch<decltype(OVERLAPPED::Internal), ULONG_PTR>::value);
static_assert(TypeMatch<decltype(OVERLAPPED::InternalHigh), ULONG_PTR>::value);
static_assert(TypeMatch<decltype(OVERLAPPED::Offset), DWORD>::value);
static_assert(TypeMatch<decltype(OVERLAPPED::OffsetHigh), DWORD>::value);
static_assert(TypeMatch<decltype(OVERLAPPED::Pointer), PVOID>::value);
static_assert(TypeMatch<decltype(OVERLAPPED::hEvent), HANDLE>::value);

static_assert(offsetof(OVERLAPPED, Internal) == 0);
static_assert(offsetof(OVERLAPPED, InternalHigh) == 4);
static_assert(offsetof(OVERLAPPED, Offset) == 8);
static_assert(offsetof(OVERLAPPED, OffsetHigh) == 0xC);
static_assert(offsetof(OVERLAPPED, Pointer) == 8);
static_assert(offsetof(OVERLAPPED, hEvent) == 0x10);

static_assert(sizeof(OVERLAPPED) == 20);

typedef OVERLAPPED * LPOVERLAPPED;

static_assert(TypeMatch<LPOVERLAPPED, OVERLAPPED *>::value);

static_assert(sizeof(LPOVERLAPPED) == 4);

// FILETIME

struct FILETIME
{
	DWORD dwLowDateTime; // 0
	DWORD dwHighDateTime; // 4
};

static_assert(TypeMatch<decltype(FILETIME::dwLowDateTime), DWORD>::value);
static_assert(TypeMatch<decltype(FILETIME::dwHighDateTime), DWORD>::value);

static_assert(offsetof(FILETIME, dwLowDateTime) == 0);
static_assert(offsetof(FILETIME, dwHighDateTime) == 4);

static_assert(sizeof(FILETIME) == 8);

typedef FILETIME * PFILETIME;
typedef FILETIME * LPFILETIME;

static_assert(TypeMatch<PFILETIME, FILETIME *>::value);
static_assert(TypeMatch<LPFILETIME, FILETIME *>::value);

static_assert(sizeof(PFILETIME) == 4);
static_assert(sizeof(LPFILETIME) == 4);

// BY_HANDLE_FILE_INFORMATION

struct BY_HANDLE_FILE_INFORMATION
{
	DWORD dwFileAttributes; // 0
	FILETIME ftCreationTime; // 4
	FILETIME ftLastAccessTime; // 0xC
	FILETIME ftLastWriteTime; // 0x14
	DWORD dwVolumeSerialNumber; // 0x1C
	DWORD nFileSizeHigh; // 0x20
	DWORD nFileSizeLow; // 0x24
	DWORD nNumberOfLinks; // 0x28
	DWORD nFileIndexHigh; // 0x2C
	DWORD nFileIndexLow; // 0x30
};

static_assert(TypeMatch<decltype(BY_HANDLE_FILE_INFORMATION::dwFileAttributes), DWORD>::value);
static_assert(TypeMatch<decltype(BY_HANDLE_FILE_INFORMATION::ftCreationTime), FILETIME>::value);
static_assert(TypeMatch<decltype(BY_HANDLE_FILE_INFORMATION::ftLastAccessTime), FILETIME>::value);
static_assert(TypeMatch<decltype(BY_HANDLE_FILE_INFORMATION::ftLastWriteTime), FILETIME>::value);
static_assert(TypeMatch<decltype(BY_HANDLE_FILE_INFORMATION::dwVolumeSerialNumber), DWORD>::value);
static_assert(TypeMatch<decltype(BY_HANDLE_FILE_INFORMATION::nFileSizeHigh), DWORD>::value);
static_assert(TypeMatch<decltype(BY_HANDLE_FILE_INFORMATION::nFileSizeLow), DWORD>::value);
static_assert(TypeMatch<decltype(BY_HANDLE_FILE_INFORMATION::nNumberOfLinks), DWORD>::value);
static_assert(TypeMatch<decltype(BY_HANDLE_FILE_INFORMATION::nFileIndexHigh), DWORD>::value);
static_assert(TypeMatch<decltype(BY_HANDLE_FILE_INFORMATION::nFileIndexLow), DWORD>::value);

static_assert(offsetof(BY_HANDLE_FILE_INFORMATION, dwFileAttributes) == 0);
static_assert(offsetof(BY_HANDLE_FILE_INFORMATION, ftCreationTime) == 4);
static_assert(offsetof(BY_HANDLE_FILE_INFORMATION, ftLastAccessTime) == 0xC);
static_assert(offsetof(BY_HANDLE_FILE_INFORMATION, ftLastWriteTime) == 0x14);
static_assert(offsetof(BY_HANDLE_FILE_INFORMATION, dwVolumeSerialNumber) == 0x1C);
static_assert(offsetof(BY_HANDLE_FILE_INFORMATION, nFileSizeHigh) == 0x20);
static_assert(offsetof(BY_HANDLE_FILE_INFORMATION, nFileSizeLow) == 0x24);
static_assert(offsetof(BY_HANDLE_FILE_INFORMATION, nNumberOfLinks) == 0x28);
static_assert(offsetof(BY_HANDLE_FILE_INFORMATION, nFileIndexHigh) == 0x2C);
static_assert(offsetof(BY_HANDLE_FILE_INFORMATION, nFileIndexLow) == 0x30);

static_assert(sizeof(BY_HANDLE_FILE_INFORMATION) == 52);

typedef BY_HANDLE_FILE_INFORMATION * PBY_HANDLE_FILE_INFORMATION;
typedef BY_HANDLE_FILE_INFORMATION * LPBY_HANDLE_FILE_INFORMATION;

static_assert(TypeMatch<PBY_HANDLE_FILE_INFORMATION, BY_HANDLE_FILE_INFORMATION *>::value);
static_assert(TypeMatch<LPBY_HANDLE_FILE_INFORMATION, BY_HANDLE_FILE_INFORMATION *>::value);

static_assert(sizeof(PBY_HANDLE_FILE_INFORMATION) == 4);
static_assert(sizeof(LPBY_HANDLE_FILE_INFORMATION) == 4);

// LARGE_INTEGER

union LARGE_INTEGER
{
	struct
	{
		DWORD LowPart; // 0
		LONG HighPart; // 4
	}; // 0
	LONGLONG QuadPart; // 0
};

static_assert(TypeMatch<decltype(LARGE_INTEGER::LowPart), DWORD>::value);
static_assert(TypeMatch<decltype(LARGE_INTEGER::HighPart), LONG>::value);
static_assert(TypeMatch<decltype(LARGE_INTEGER::QuadPart), LONGLONG>::value);

static_assert(offsetof(LARGE_INTEGER, LowPart) == 0);
static_assert(offsetof(LARGE_INTEGER, HighPart) == 4);
static_assert(offsetof(LARGE_INTEGER, QuadPart) == 0);

static_assert(sizeof(LARGE_INTEGER) == 8);

typedef LARGE_INTEGER * PLARGE_INTEGER;

static_assert(TypeMatch<PLARGE_INTEGER, LARGE_INTEGER *>::value);

static_assert(sizeof(PLARGE_INTEGER) == 4);

// SYSTEMTIME

struct SYSTEMTIME
{
	WORD wYear; // 0
	WORD wMonth; // 2
	WORD wDayOfWeek; // 4
	WORD wDay; // 6
	WORD wHour; // 8
	WORD wMinute; // 0xA
	WORD wSecond; // 0xC
	WORD wMilliseconds; // 0xE
};

static_assert(TypeMatch<decltype(SYSTEMTIME::wYear), WORD>::value);
static_assert(TypeMatch<decltype(SYSTEMTIME::wMonth), WORD>::value);
static_assert(TypeMatch<decltype(SYSTEMTIME::wDayOfWeek), WORD>::value);
static_assert(TypeMatch<decltype(SYSTEMTIME::wDay), WORD>::value);
static_assert(TypeMatch<decltype(SYSTEMTIME::wHour), WORD>::value);
static_assert(TypeMatch<decltype(SYSTEMTIME::wMinute), WORD>::value);
static_assert(TypeMatch<decltype(SYSTEMTIME::wSecond), WORD>::value);
static_assert(TypeMatch<decltype(SYSTEMTIME::wMilliseconds), WORD>::value);

static_assert(offsetof(SYSTEMTIME, wYear) == 0);
static_assert(offsetof(SYSTEMTIME, wMonth) == 2);
static_assert(offsetof(SYSTEMTIME, wDayOfWeek) == 4);
static_assert(offsetof(SYSTEMTIME, wDay) == 6);
static_assert(offsetof(SYSTEMTIME, wHour) == 8);
static_assert(offsetof(SYSTEMTIME, wMinute) == 0xA);
static_assert(offsetof(SYSTEMTIME, wSecond) == 0xC);
static_assert(offsetof(SYSTEMTIME, wMilliseconds) == 0xE);

static_assert(sizeof(SYSTEMTIME) == 16);

typedef SYSTEMTIME * PSYSTEMTIME;
typedef SYSTEMTIME * LPSYSTEMTIME;

static_assert(TypeMatch<PSYSTEMTIME, SYSTEMTIME *>::value);
static_assert(TypeMatch<LPSYSTEMTIME, SYSTEMTIME *>::value);

static_assert(sizeof(PSYSTEMTIME) == 4);
static_assert(sizeof(LPSYSTEMTIME) == 4);

// WNDCLASSEXA

struct WNDCLASSEXA
{
	UINT cbSize; // 0
	UINT style; // 4
	WNDPROC lpfnWndProc; // 8
	int cbClsExtra; // 0xC
	int cbWndExtra; // 0x10
	HINSTANCE hInstance; // 0x14
	HICON hIcon; // 0x18
	HCURSOR hCursor; // 0x1C
	HBRUSH hbrBackground; // 0x20
	LPCSTR lpszMenuName; // 0x24
	LPCSTR lpszClassName; // 0x28
	HICON hIconSm; // 0x2C
};

static_assert(TypeMatch<decltype(WNDCLASSEXA::cbSize), UINT>::value);
static_assert(TypeMatch<decltype(WNDCLASSEXA::style), UINT>::value);
static_assert(TypeMatch<decltype(WNDCLASSEXA::lpfnWndProc), WNDPROC>::value);
static_assert(TypeMatch<decltype(WNDCLASSEXA::cbClsExtra), int>::value);
static_assert(TypeMatch<decltype(WNDCLASSEXA::cbWndExtra), int>::value);
static_assert(TypeMatch<decltype(WNDCLASSEXA::hInstance), HINSTANCE>::value);
static_assert(TypeMatch<decltype(WNDCLASSEXA::hIcon), HICON>::value);
static_assert(TypeMatch<decltype(WNDCLASSEXA::hCursor), HCURSOR>::value);
static_assert(TypeMatch<decltype(WNDCLASSEXA::hbrBackground), HBRUSH>::value);
static_assert(TypeMatch<decltype(WNDCLASSEXA::lpszMenuName), LPCSTR>::value);
static_assert(TypeMatch<decltype(WNDCLASSEXA::lpszClassName), LPCSTR>::value);
static_assert(TypeMatch<decltype(WNDCLASSEXA::hIconSm), HICON>::value);

static_assert(offsetof(WNDCLASSEXA, cbSize) == 0);
static_assert(offsetof(WNDCLASSEXA, style) == 4);
static_assert(offsetof(WNDCLASSEXA, lpfnWndProc) == 8);
static_assert(offsetof(WNDCLASSEXA, cbClsExtra) == 0xC);
static_assert(offsetof(WNDCLASSEXA, cbWndExtra) == 0x10);
static_assert(offsetof(WNDCLASSEXA, hInstance) == 0x14);
static_assert(offsetof(WNDCLASSEXA, hIcon) == 0x18);
static_assert(offsetof(WNDCLASSEXA, hCursor) == 0x1C);
static_assert(offsetof(WNDCLASSEXA, hbrBackground) == 0x20);
static_assert(offsetof(WNDCLASSEXA, lpszMenuName) == 0x24);
static_assert(offsetof(WNDCLASSEXA, lpszClassName) == 0x28);
static_assert(offsetof(WNDCLASSEXA, hIconSm) == 0x2C);

static_assert(sizeof(WNDCLASSEXA) == 48);

typedef WNDCLASSEXA * PWNDCLASSEXA;
typedef WNDCLASSEXA * LPWNDCLASSEXA;

static_assert(TypeMatch<PWNDCLASSEXA, WNDCLASSEXA *>::value);
static_assert(TypeMatch<LPWNDCLASSEXA, WNDCLASSEXA *>::value);

static_assert(sizeof(PWNDCLASSEXA) == 4);
static_assert(sizeof(LPWNDCLASSEXA) == 4);

// WNDCLASSEXW

struct WNDCLASSEXW
{
	UINT cbSize; // 0
	UINT style; // 4
	WNDPROC lpfnWndProc; // 8
	int cbClsExtra; // 0xC
	int cbWndExtra; // 0x10
	HINSTANCE hInstance; // 0x14
	HICON hIcon; // 0x18
	HCURSOR hCursor; // 0x1C
	HBRUSH hbrBackground; // 0x20
	LPCWSTR lpszMenuName; // 0x24
	LPCWSTR lpszClassName; // 0x28
	HICON hIconSm; // 0x2C
};

static_assert(TypeMatch<decltype(WNDCLASSEXW::cbSize), UINT>::value);
static_assert(TypeMatch<decltype(WNDCLASSEXW::style), UINT>::value);
static_assert(TypeMatch<decltype(WNDCLASSEXW::lpfnWndProc), WNDPROC>::value);
static_assert(TypeMatch<decltype(WNDCLASSEXW::cbClsExtra), int>::value);
static_assert(TypeMatch<decltype(WNDCLASSEXW::cbWndExtra), int>::value);
static_assert(TypeMatch<decltype(WNDCLASSEXW::hInstance), HINSTANCE>::value);
static_assert(TypeMatch<decltype(WNDCLASSEXW::hIcon), HICON>::value);
static_assert(TypeMatch<decltype(WNDCLASSEXW::hCursor), HCURSOR>::value);
static_assert(TypeMatch<decltype(WNDCLASSEXW::hbrBackground), HBRUSH>::value);
static_assert(TypeMatch<decltype(WNDCLASSEXW::lpszMenuName), LPCWSTR>::value);
static_assert(TypeMatch<decltype(WNDCLASSEXW::lpszClassName), LPCWSTR>::value);
static_assert(TypeMatch<decltype(WNDCLASSEXW::hIconSm), HICON>::value);

static_assert(offsetof(WNDCLASSEXW, cbSize) == 0);
static_assert(offsetof(WNDCLASSEXW, style) == 4);
static_assert(offsetof(WNDCLASSEXW, lpfnWndProc) == 8);
static_assert(offsetof(WNDCLASSEXW, cbClsExtra) == 0xC);
static_assert(offsetof(WNDCLASSEXW, cbWndExtra) == 0x10);
static_assert(offsetof(WNDCLASSEXW, hInstance) == 0x14);
static_assert(offsetof(WNDCLASSEXW, hIcon) == 0x18);
static_assert(offsetof(WNDCLASSEXW, hCursor) == 0x1C);
static_assert(offsetof(WNDCLASSEXW, hbrBackground) == 0x20);
static_assert(offsetof(WNDCLASSEXW, lpszMenuName) == 0x24);
static_assert(offsetof(WNDCLASSEXW, lpszClassName) == 0x28);
static_assert(offsetof(WNDCLASSEXW, hIconSm) == 0x2C);

static_assert(sizeof(WNDCLASSEXW) == 48);

typedef WNDCLASSEXW * PWNDCLASSEXW;
typedef WNDCLASSEXW * LPWNDCLASSEXW;

static_assert(TypeMatch<PWNDCLASSEXW, WNDCLASSEXW *>::value);
static_assert(TypeMatch<LPWNDCLASSEXW, WNDCLASSEXW *>::value);

static_assert(sizeof(PWNDCLASSEXW) == 4);
static_assert(sizeof(LPWNDCLASSEXW) == 4);

// GUID

struct GUID
{
	unsigned long Data1; // 0
	unsigned short Data2; // 4
	unsigned short Data3; // 6
	unsigned char Data4[8]; // 8
};

static_assert(TypeMatch<decltype(GUID::Data1), unsigned long>::value);
static_assert(TypeMatch<decltype(GUID::Data2), unsigned short>::value);
static_assert(TypeMatch<decltype(GUID::Data3), unsigned short>::value);
static_assert(TypeMatch<decltype(GUID::Data4), unsigned char[8]>::value);

static_assert(offsetof(GUID, Data1) == 0);
static_assert(offsetof(GUID, Data2) == 4);
static_assert(offsetof(GUID, Data3) == 6);
static_assert(offsetof(GUID, Data4) == 8);

static_assert(sizeof(GUID) == 16);

typedef GUID * LPGUID;
typedef const GUID * LPCGUID;

static_assert(TypeMatch<LPGUID, GUID *>::value);
static_assert(TypeMatch<LPCGUID, const GUID *>::value);

static_assert(sizeof(LPGUID) == 4);
static_assert(sizeof(LPCGUID) == 4);

// LUID

struct LUID
{
	DWORD LowPart; // 0
	LONG HighPart; // 4
};

static_assert(TypeMatch<decltype(LUID::LowPart), DWORD>::value);
static_assert(TypeMatch<decltype(LUID::HighPart), LONG>::value);

static_assert(offsetof(LUID, LowPart) == 0);
static_assert(offsetof(LUID, HighPart) == 4);

static_assert(sizeof(LUID) == 8);

typedef LUID * PLUID;

static_assert(TypeMatch<PLUID, LUID *>::value);

static_assert(sizeof(PLUID) == 4);

// IID

typedef GUID IID;
typedef IID * LPIID;

static_assert(TypeMatch<IID, GUID>::value);
static_assert(TypeMatch<LPIID, IID *>::value);

static_assert(sizeof(IID) == 16);
static_assert(sizeof(LPIID) == 4);

#pragma pack(pop)

struct IUnknown;

extern "C" const IID IID_IUnknown;

extern "C" DWORD __stdcall GetLastError();
extern "C" void __stdcall SetLastError(DWORD dwErrCode);
extern "C" LPVOID __stdcall VirtualAlloc
(
	LPVOID lpAddress,
	SIZE_T dwSize,
	DWORD flAllocationType,
	DWORD flProtect
);
extern "C" BOOL __stdcall VirtualProtect
(
	LPVOID lpAddress,
	SIZE_T dwSize,
	DWORD flNewProtect,
	PDWORD lpflOldProtect
);
extern "C" BOOL __stdcall VirtualFree
(
	LPVOID lpAddress,
	SIZE_T dwSize,
	DWORD dwFreeType
);
extern "C" SIZE_T __stdcall VirtualQuery
(
	LPCVOID lpAddress,
	PMEMORY_BASIC_INFORMATION lpBuffer,
	SIZE_T dwLength
);
extern "C" LPVOID __stdcall VirtualAllocEx
(
	HANDLE hProcess,
	LPVOID lpAddress,
	SIZE_T dwSize,
	DWORD flAllocationType,
	DWORD flProtect
);
extern "C" BOOL __stdcall VirtualProtectEx
(
	HANDLE hProcess,
	LPVOID lpAddress,
	SIZE_T dwSize,
	DWORD flNewProtect,
	PDWORD lpflOldProtect
);
extern "C" SIZE_T __stdcall VirtualQueryEx
(
	HANDLE hProcess,
	LPCVOID lpAddress,
	PMEMORY_BASIC_INFORMATION lpBuffer,
	SIZE_T dwLength
);
extern "C" HANDLE __stdcall CreateFileA
(
	LPCSTR lpFileName,
	DWORD dwDesiredAccess,
	DWORD dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD dwCreationDisposition,
	DWORD dwFlagsAndAttributes,
	HANDLE hTemplateFile
);
extern "C" HANDLE __stdcall CreateFileW
(
	LPCWSTR lpFileName,
	DWORD dwDesiredAccess,
	DWORD dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD dwCreationDisposition,
	DWORD dwFlagsAndAttributes,
	HANDLE hTemplateFile
);
extern "C" BOOL __stdcall CloseHandle(HANDLE hObject);
extern "C" BOOL __stdcall GetFileInformationByHandle
(
	HANDLE hFile,
	LPBY_HANDLE_FILE_INFORMATION lpFileInformation
);
extern "C" BOOL __stdcall SetFilePointerEx
(
	HANDLE hFile,
	LARGE_INTEGER liDistanceToMove,
	PLARGE_INTEGER lpNewFilePointer,
	DWORD dwMoveMethod
);
extern "C" BOOL __stdcall ReadFile
(
	HANDLE hFile,
	LPVOID lpBuffer,
	DWORD nNumberOfBytesToRead,
	LPDWORD lpNumberOfBytesRead,
	LPOVERLAPPED lpOverlapped
);
extern "C" BOOL __stdcall WriteFile
(
	HANDLE hFile,
	LPCVOID lpBuffer,
	DWORD nNumberOfBytesToWrite,
	LPDWORD lpNumberOfBytesWritten,
	LPOVERLAPPED lpOverlapped
);
extern "C" BOOL __stdcall CreateDirectoryA
(
	LPCSTR lpPathName,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes
);
extern "C" BOOL __stdcall CreateDirectoryW
(
	LPCWSTR lpPathName,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes
);
extern "C" BOOL __stdcall DeleteFileA(LPCSTR lpFileName);
extern "C" BOOL __stdcall DeleteFileW(LPCWSTR lpFileName);
extern "C" void __stdcall OutputDebugStringA(LPCSTR lpOutputString);
extern "C" void __stdcall OutputDebugStringW(LPCWSTR lpOutputString);
extern "C" int __stdcall MessageBoxA
(
	HWND hWnd,
	LPCSTR lpText,
	LPCSTR lpCaption,
	UINT uType
);
extern "C" int __stdcall MessageBoxW
(
	HWND hWnd,
	LPCWSTR lpText,
	LPCWSTR lpCaption,
	UINT uType
);
extern "C" void __stdcall GetLocalTime(LPSYSTEMTIME lpSystemTime);
extern "C" HANDLE __stdcall CreateToolhelp32Snapshot
(
	DWORD dwFlags,
	DWORD th32ProcessID
);
extern "C" BOOL __stdcall Module32FirstW
(
	HANDLE hSnapshot,
	LPMODULEENTRY32W lpme
);
extern "C" BOOL __stdcall Module32NextW
(
	HANDLE hSnapshot,
	LPMODULEENTRY32W lpme
);
extern "C" BOOL __stdcall Module32First
(
	HANDLE hSnapshot,
	LPMODULEENTRY32 lpme
);
extern "C" BOOL __stdcall Module32Next
(
	HANDLE hSnapshot,
	LPMODULEENTRY32 lpme
);
extern "C" void __stdcall GetSystemInfo(LPSYSTEM_INFO lpSystemInfo);
extern "C" BOOL __stdcall QueryPerformanceCounter(LARGE_INTEGER* lpPerformanceCount);
extern "C" BOOL __stdcall QueryPerformanceFrequency(LARGE_INTEGER* lpFrequency);
extern "C" int __stdcall ShowCursor(BOOL bShow);
extern "C" BOOL __stdcall GetCursorPos(LPPOINT lpPoint);
extern "C" HCURSOR __stdcall LoadCursorA
(
	HINSTANCE hInstance,
	LPCSTR lpCursorName
);
extern "C" HCURSOR __stdcall LoadCursorW
(
	HINSTANCE hInstance,
	LPCWSTR lpCursorName
);
extern "C" BOOL __stdcall GetWindowRect
(
	HWND hWnd,
	LPRECT lpRect
);
extern "C" DWORD __stdcall SetClassLongA
(
	HWND hWnd,
	int nIndex,
	LONG dwNewLong
);
extern "C" DWORD __stdcall SetClassLongW
(
	HWND hWnd,
	int nIndex,
	LONG dwNewLong
);
extern "C" ULONG_PTR __stdcall SetClassLongPtrA
(
	HWND hWnd,
	int nIndex,
	LONG_PTR dwNewLong
);
extern "C" ULONG_PTR __stdcall SetClassLongPtrW
(
	HWND hWnd,
	int nIndex,
	LONG_PTR dwNewLong
);
extern "C" HMODULE __stdcall LoadLibraryA(LPCSTR lpLibFileName);
extern "C" HMODULE __stdcall LoadLibraryW(LPCWSTR lpLibFileName);
extern "C" FARPROC __stdcall GetProcAddress
(
	HMODULE hModule,
	LPCSTR lpProcName
);
extern "C" HINSTANCE __stdcall ShellExecuteA
(
	HWND hwnd,
	LPCSTR lpOperation,
	LPCSTR lpFile,
	LPCSTR lpParameters,
	LPCSTR lpDirectory,
	INT nShowCmd
);
extern "C" HINSTANCE __stdcall ShellExecuteW
(
	HWND hwnd,
	LPCWSTR lpOperation,
	LPCWSTR lpFile,
	LPCWSTR lpParameters,
	LPCWSTR lpDirectory,
	INT nShowCmd
);
extern "C" ATOM __stdcall RegisterClassExA(const WNDCLASSEXA*);
extern "C" ATOM __stdcall RegisterClassExW(const WNDCLASSEXW*);
extern "C" HWND __stdcall CreateWindowExA
(
	DWORD dwExStyle,
	LPCSTR lpClassName,
	LPCSTR lpWindowName,
	DWORD dwStyle,
	int X,
	int Y,
	int nWidth,
	int nHeight,
	HWND hWndParent,
	HMENU hMenu,
	HINSTANCE hInstance,
	LPVOID lpParam
);
extern "C" HWND __stdcall CreateWindowExW
(
	DWORD dwExStyle,
	LPCWSTR lpClassName,
	LPCWSTR lpWindowName,
	DWORD dwStyle,
	int X,
	int Y,
	int nWidth,
	int nHeight,
	HWND hWndParent,
	HMENU hMenu,
	HINSTANCE hInstance,
	LPVOID lpParam
);
extern "C" BOOL __stdcall ScreenToClient
(
	HWND hWnd,
	LPPOINT lpPoint
);
extern "C" BOOL __stdcall PostMessageA
(
	HWND hWnd,
	UINT Msg,
	WPARAM wParam,
	LPARAM lParam
);
extern "C" BOOL __stdcall PostMessageW
(
	HWND hWnd,
	UINT Msg,
	WPARAM wParam,
	LPARAM lParam
);
extern "C" BOOL __stdcall SetWindowPos
(
	HWND hWnd,
	HWND hWndInsertAfter,
	int X,
	int Y,
	int cx,
	int cy,
	UINT uFlags
);
extern "C" void __stdcall Sleep(DWORD dwMilliseconds);
extern "C" HWND __stdcall GetForegroundWindow();
extern "C" HANDLE __stdcall CreateThread
(
	LPSECURITY_ATTRIBUTES lpThreadAttributes,
	SIZE_T dwStackSize,
	LPTHREAD_START_ROUTINE lpStartAddress,
	LPVOID lpParameter,
	DWORD dwCreationFlags,
	LPDWORD lpThreadId
);
extern "C" UINT __stdcall GetWindowsDirectoryA
(
	LPSTR lpBuffer,
	UINT uSize
);
extern "C" UINT __stdcall GetWindowsDirectoryW
(
	LPWSTR lpBuffer,
	UINT uSize
);
extern "C" BOOL __stdcall ClientToScreen
(
	HWND hWnd,
	LPPOINT lpPoint
);
extern "C" BOOL __stdcall SetCursorPos
(
	int X,
	int Y
);
extern "C" LONG __stdcall GetWindowLongA
(
	HWND hWnd,
	int nIndex
);
extern "C" LONG __stdcall GetWindowLongW
(
	HWND hWnd,
	int nIndex
);
extern "C" LONG __stdcall SetWindowLongA
(
	HWND hWnd,
	int nIndex,
	LONG dwNewLong
);
extern "C" LONG __stdcall SetWindowLongW
(
	HWND hWnd,
	int nIndex,
	LONG dwNewLong
);
extern "C" LONG_PTR __stdcall GetWindowLongPtrA
(
	HWND hWnd,
	int nIndex
);
extern "C" LONG_PTR __stdcall GetWindowLongPtrW
(
	HWND hWnd,
	int nIndex
);
extern "C" LONG_PTR __stdcall SetWindowLongPtrA
(
	HWND hWnd,
	int nIndex,
	LONG_PTR dwNewLong
);
extern "C" LONG_PTR __stdcall SetWindowLongPtrW
(
	HWND hWnd,
	int nIndex,
	LONG_PTR dwNewLong
);
extern "C" BOOL __stdcall GetClientRect
(
	HWND hWnd,
	LPRECT lpRect
);
extern "C" BOOL __stdcall AdjustWindowRect
(
	LPRECT lpRect,
	DWORD dwStyle,
	BOOL bMenu
);
extern "C" BOOL __stdcall AdjustWindowRectEx
(
	LPRECT lpRect,
	DWORD dwStyle,
	BOOL bMenu,
	DWORD dwExStyle
);
extern "C" BOOL __stdcall AdjustWindowRectExForDpi
(
	LPRECT lpRect,
	DWORD dwStyle,
	BOOL bMenu,
	DWORD dwExStyle,
	UINT dpi
);
extern "C" HWND __stdcall GetFocus();
extern "C" BOOL __stdcall MoveWindow
(
	HWND hWnd,
	int X,
	int Y,
	int nWidth,
	int nHeight,
	BOOL bRepaint
);
extern "C" UINT __stdcall GetSystemDirectoryA
(
	LPSTR lpBuffer,
	UINT uSize
);
extern "C" UINT __stdcall GetSystemDirectoryW
(
	LPWSTR lpBuffer,
	UINT uSize
);

// IUnknown

struct __declspec(novtable) IUnknown
{
	virtual HRESULT __stdcall QueryInterface
	(
		const IID& riid,
		void** ppvObject
	) = 0;
	virtual ULONG __stdcall AddRef() = 0;
	virtual ULONG __stdcall Release() = 0;
};

static_assert(sizeof(IUnknown) == 4);

// LPUNKNOWN

typedef IUnknown* LPUNKNOWN;

static_assert(TypeMatch<LPUNKNOWN, IUnknown*>::value);

static_assert(sizeof(LPUNKNOWN) == 4);

#pragma endregion

#endif

namespaceEnd();
