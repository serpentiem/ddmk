let fs = require("fs");
let vm = require("vm");

vm.runInThisContext(fs.readFileSync("dmc3_core.js", "utf8"));

ClearAll();

// #region Windows
{
console.log("Windows");

ModuleStart("Windows");

// Types
{
	let items =
	[
		[ "VOID"                  , "void"              , 0                                                ],
		[ "BOOL"                  , "int"               , 4, TypeFlags_NoLPC                               ],
		[ "BYTE"                  , "unsigned char"     , 1                                                ],
		[ "WORD"                  , "unsigned short"    , 2, TypeFlags_NoLPC                               ],
		[ "DWORD"                 , "unsigned long"     , 4, TypeFlags_NoLPC                               ],
		[ "FLOAT"                 , "float"             , 4, TypeFlags_NoLP | TypeFlags_NoLPC              ],
		[ "DOUBLE"                , "double"            , 8, TypeFlags_NoPointers                          ],
		[ "CHAR"                  , "char"              , 1, TypeFlags_NoLP | TypeFlags_NoLPC              ],
		[ "SHORT"                 , "short"             , 2, TypeFlags_NoLP | TypeFlags_NoLPC              ],
		[ "LONG"                  , "long"              , 4, TypeFlags_NoLPC                               ],
		[ "INT"                   , "int"               , 4, TypeFlags_NoLPC                               ],
		[ "WCHAR"                 , "wchar_t"           , 2, TypeFlags_NoLP                                ],
		[ "INT8"                  , "signed char"       , 1, TypeFlags_NoLP | TypeFlags_NoLPC              ],
		[ "INT16"                 , "signed short"      , 2, TypeFlags_NoLP | TypeFlags_NoLPC              ],
		[ "INT32"                 , "signed int"        , 4, TypeFlags_NoLP | TypeFlags_NoLPC              ],
		[ "INT64"                 , "signed long long"  , 8, TypeFlags_NoLP | TypeFlags_NoLPC              ],
		[ "UINT8"                 , "unsigned char"     , 1, TypeFlags_NoLP | TypeFlags_NoLPC              ],
		[ "UINT16"                , "unsigned short"    , 2, TypeFlags_NoLP | TypeFlags_NoLPC              ],
		[ "UINT32"                , "unsigned int"      , 4, TypeFlags_NoLP | TypeFlags_NoLPC              ],
		[ "UINT64"                , "unsigned long long", 8, TypeFlags_NoLP | TypeFlags_NoLPC              ],
		[ "UCHAR"                 , "unsigned char"     , 1, TypeFlags_NoLP | TypeFlags_NoLPC              ],
		[ "USHORT"                , "unsigned short"    , 2, TypeFlags_NoLP | TypeFlags_NoLPC              ],
		[ "UINT"                  , "unsigned int"      , 4, TypeFlags_NoLPC                               ],
		[ "ULONG"                 , "unsigned long"     , 4, TypeFlags_NoLP | TypeFlags_NoLPC              ],
		[ "LONGLONG"              , "long long"         , 8, TypeFlags_NoLP | TypeFlags_NoLPC              ],
		[ "ULONGLONG"             , "unsigned long long", 8, TypeFlags_NoLP | TypeFlags_NoLPC              ],
		[ "HANDLE"                , "void*"             , 8, TypeFlags_NoLPC                               ],
		[ "HINSTANCE"             , "HANDLE"            , 8, TypeFlags_NoTypeAssert | TypeFlags_NoPointers ],
		[ "HMODULE"               , "HANDLE"            , 8, TypeFlags_NoTypeAssert | TypeFlags_NoPointers ],
		[ "HWND"                  , "HANDLE"            , 8, TypeFlags_NoTypeAssert | TypeFlags_NoPointers ],
		[ "HMENU"                 , "HANDLE"            , 8, TypeFlags_NoTypeAssert | TypeFlags_NoPointers ],
		[ "HICON"                 , "HANDLE"            , 8, TypeFlags_NoTypeAssert | TypeFlags_NoPointers ],
		[ "HCURSOR"               , "HANDLE"            , 8, TypeFlags_NoTypeAssert | TypeFlags_NoPointers ],
		[ "HBRUSH"                , "HANDLE"            , 8, TypeFlags_NoTypeAssert | TypeFlags_NoPointers ],
		[ "HMONITOR"              , "HANDLE"            , 8, TypeFlags_NoTypeAssert | TypeFlags_NoPointers ],
		[ "INT_PTR"               , "long long"         , 8, TypeFlags_NoLP | TypeFlags_NoLPC              ],
		[ "UINT_PTR"              , "unsigned long long", 8, TypeFlags_NoLP | TypeFlags_NoLPC              ],
		[ "LONG_PTR"              , "long long"         , 8, TypeFlags_NoLP | TypeFlags_NoLPC              ],
		[ "ULONG_PTR"             , "unsigned long long", 8, TypeFlags_NoLP | TypeFlags_NoLPC              ],
		[ "DWORD_PTR"             , "unsigned long long", 8, TypeFlags_NoLP | TypeFlags_NoLPC              ],
		[ "SIZE_T"                , "unsigned long long", 8, TypeFlags_NoLP | TypeFlags_NoLPC              ],
		[ "HRESULT"               , "long"              , 4, TypeFlags_NoPointers                          ],
		[ "WPARAM"                , "UINT_PTR"          , 8, TypeFlags_NoPointers                          ],
		[ "LPARAM"                , "LONG_PTR"          , 8, TypeFlags_NoPointers                          ],
		[ "LRESULT"               , "LONG_PTR"          , 8, TypeFlags_NoPointers                          ],
		[ "PSTR"                  , "CHAR *"            , 8, TypeFlags_NoPointers                          ],
		[ "LPSTR"                 , "CHAR *"            , 8, TypeFlags_NoPointers                          ],
		[ "LPCSTR"                , "const CHAR *"      , 8, TypeFlags_NoPointers                          ],
		[ "PWSTR"                 , "WCHAR *"           , 8, TypeFlags_NoPointers                          ],
		[ "LPWSTR"                , "WCHAR *"           , 8, TypeFlags_NoPointers                          ],
		[ "LPCWSTR"               , "const WCHAR *"     , 8, TypeFlags_NoPointers                          ],
		[ "ATOM"                  , "WORD"              , 2, TypeFlags_NoPointers                          ],
		[ "APP_DEPRECATED_HRESULT", "HRESULT"           , 4, TypeFlags_NoPointers                          ],
		[ "HDC"                   , "HANDLE"            , 8, TypeFlags_NoTypeAssert | TypeFlags_NoPointers ],
	];

	CreateWindowsTypedefs(items);
}





// Function Types
{
	let items =
	[
		[ "FARPROC", "INT_PTR",
			[
			],
		],
		[ "WNDPROC", "LRESULT",
			[
				[ "", "HWND" ],
				[ "", "UINT" ],
				[ "", "WPARAM" ],
				[ "", "LPARAM" ],
			],
		],
		[ "PTHREAD_START_ROUTINE", "DWORD",
			[
				[ "lpThreadParameter", "LPVOID" ],
			],
		],
	];

	CreateWindowsFunctionTypedefs(items);
}

CreateWindowsTypedef
(
	"LPTHREAD_START_ROUTINE",
	"PTHREAD_START_ROUTINE",
	8,
	TypeFlags_NoPointers
);


/*





*/





// Enums
{
	let items =
	[
		[ "PAGE_NOACCESS"           , "1"         , ""       ],
		[ "PAGE_READONLY"           , "2"         , ""       ],
		[ "PAGE_READWRITE"          , "4"         , ""       ],
		[ "PAGE_WRITECOPY"          , "8"         , ""       ],
		[ "PAGE_EXECUTE"            , "0x10"      , ""       ],
		[ "PAGE_EXECUTE_READ"       , "0x20"      , ""       ],
		[ "PAGE_EXECUTE_READWRITE"  , "0x40"      , ""       ],
		[ "PAGE_EXECUTE_WRITECOPY"  , "0x80"      , ""       ],
		[ "MEM_COMMIT"              , "0x1000"    , ""       ],
		[ "MEM_RESERVE"             , "0x2000"    , ""       ],
		[ "MEM_DECOMMIT"            , "0x4000"    , ""       ],
		[ "MEM_RELEASE"             , "0x8000"    , ""       ],
		[ "MEM_FREE"                , "0x10000"   , ""       ],
		[ "GENERIC_READ"            , "0x80000000", ""       ],
		[ "GENERIC_WRITE"           , "0x40000000", ""       ],
		[ "GENERIC_EXECUTE"         , "0x20000000", ""       ],
		[ "GENERIC_ALL"             , "0x10000000", ""       ],
		[ "CREATE_NEW"              , "1"         , ""       ],
		[ "CREATE_ALWAYS"           , "2"         , ""       ],
		[ "OPEN_EXISTING"           , "3"         , ""       ],
		[ "OPEN_ALWAYS"             , "4"         , ""       ],
		[ "TRUNCATE_EXISTING"       , "5"         , ""       ],
		[ "FILE_APPEND_DATA"        , "4"         , ""       ],
		[ "FILE_ATTRIBUTE_READONLY" , "1"         , ""       ],
		[ "FILE_ATTRIBUTE_HIDDEN"   , "2"         , ""       ],
		[ "FILE_ATTRIBUTE_SYSTEM"   , "4"         , ""       ],
		[ "FILE_ATTRIBUTE_DIRECTORY", "0x10"      , ""       ],
		[ "FILE_ATTRIBUTE_ARCHIVE"  , "0x20"      , ""       ],
		[ "FILE_ATTRIBUTE_DEVICE"   , "0x40"      , ""       ],
		[ "FILE_ATTRIBUTE_NORMAL"   , "0x80"      , ""       ],
		[ "FILE_ATTRIBUTE_TEMPORARY", "0x100"     , ""       ],
		[ "FILE_BEGIN"              , "0"         , ""       ],
		[ "FILE_CURRENT"            , "1"         , ""       ],
		[ "FILE_END"                , "2"         , ""       ],
		[ "TH32CS_SNAPHEAPLIST"     , "1"         , ""       ],
		[ "TH32CS_SNAPPROCESS"      , "2"         , ""       ],
		[ "TH32CS_SNAPTHREAD"       , "4"         , ""       ],
		[ "TH32CS_SNAPMODULE"       , "8"         , ""       ],
		[ "TH32CS_SNAPMODULE32"     , "0x10"      , ""       ],
		[ "TH32CS_INHERIT"          , "0x80000000", ""       ],
		[ "INVALID_HANDLE_VALUE"    , "-1"        , "HANDLE" ],
		[ "IDC_ARROW"               , "32512"     , "LPSTR"  ],
		[ "IDC_IBEAM"               , "32513"     , "LPSTR"  ],
		[ "IDC_WAIT"                , "32514"     , "LPSTR"  ],
		[ "IDC_CROSS"               , "32515"     , "LPSTR"  ],
		[ "IDC_UPARROW"             , "32516"     , "LPSTR"  ],
		[ "IDC_SIZE"                , "32640"     , "LPSTR"  ],
		[ "IDC_ICON"                , "32641"     , "LPSTR"  ],
		[ "IDC_SIZENWSE"            , "32642"     , "LPSTR"  ],
		[ "IDC_SIZENESW"            , "32643"     , "LPSTR"  ],
		[ "IDC_SIZEWE"              , "32644"     , "LPSTR"  ],
		[ "IDC_SIZENS"              , "32645"     , "LPSTR"  ],
		[ "IDC_SIZEALL"             , "32646"     , "LPSTR"  ],
		[ "IDC_NO"                  , "32648"     , "LPSTR"  ],
		[ "IDC_HAND"                , "32649"     , "LPSTR"  ],
		[ "IDC_APPSTARTING"         , "32650"     , "LPSTR"  ],
		[ "IDC_HELP"                , "32651"     , "LPSTR"  ],
		[ "IDC_PIN"                 , "32671"     , "LPSTR"  ],
		[ "IDC_PERSON"              , "32672"     , "LPSTR"  ],
		[ "GWL_STYLE"               , "-16"       , ""       ],
		[ "GWL_EXSTYLE"             , "-20"       , ""       ],
		[ "GWL_ID"                  , "-12"       , ""       ],
		[ "GWLP_WNDPROC"            , "-4"        , ""       ],
		[ "GWLP_HINSTANCE"          , "-6"        , ""       ],
		[ "GWLP_HWNDPARENT"         , "-8"        , ""       ],
		[ "GWLP_USERDATA"           , "-21"       , ""       ],
		[ "GWLP_ID"                 , "-12"       , ""       ],
		[ "GCL_CBWNDEXTRA"          , "-18"       , ""       ],
		[ "GCL_CBCLSEXTRA"          , "-20"       , ""       ],
		[ "GCL_STYLE"               , "-26"       , ""       ],
		[ "GCW_ATOM"                , "-32"       , ""       ],
		[ "GCLP_MENUNAME"           , "-8"        , ""       ],
		[ "GCLP_HBRBACKGROUND"      , "-10"       , ""       ],
		[ "GCLP_HCURSOR"            , "-12"       , ""       ],
		[ "GCLP_HICON"              , "-14"       , ""       ],
		[ "GCLP_HMODULE"            , "-16"       , ""       ],
		[ "GCLP_WNDPROC"            , "-24"       , ""       ],
		[ "GCLP_HICONSM"            , "-34"       , ""       ],
		[ "WM_USER"                 , "0x400"     , ""       ],
		[ "S_OK"                 , "0"     , ""       ],
		[ "S_FALSE"                 , "1"     , ""       ],
		[ "WHEEL_DELTA"                 , "120"     , ""       ],
		[ "WM_SETCURSOR", "0x0020", "" ],
		[ "WM_CHAR", "0x0102", "" ],
		[ "DLL_PROCESS_DETACH", "0", "" ],
		[ "DLL_PROCESS_ATTACH", "1", "" ],
		[ "DLL_THREAD_ATTACH", "2", "" ],
		[ "DLL_THREAD_DETACH", "3", "" ],
		[ "SW_HIDE", "0", "" ],
		[ "SW_SHOWNORMAL", "1", "" ],
		[ "SW_NORMAL", "1", "" ],
		[ "SW_SHOWMINIMIZED", "2", "" ],
		[ "SW_SHOWMAXIMIZED", "3", "" ],
		[ "SW_MAXIMIZE", "3", "" ],
		[ "SW_SHOWNOACTIVATE", "4", "" ],
		[ "SW_SHOW", "5", "" ],
		[ "SW_MINIMIZE", "6", "" ],
		[ "SW_SHOWMINNOACTIVE", "7", "" ],
		[ "SW_SHOWNA", "8", "" ],
		[ "SW_RESTORE", "9", "" ],
		[ "SW_SHOWDEFAULT", "10", "" ],
		[ "SW_FORCEMINIMIZE", "11", "" ],
		[ "SW_MAX", "11", "" ],
		[ "WM_SIZE", "0x0005", "" ],
		[ "WS_OVERLAPPED", "0x00000000", "" ],
		[ "WS_POPUP", "0x80000000", "" ],
		[ "WS_CHILD", "0x40000000", "" ],
		[ "WS_MINIMIZE", "0x20000000", "" ],
		[ "WS_VISIBLE", "0x10000000", "" ],
		[ "WS_DISABLED", "0x08000000", "" ],
		[ "WS_CLIPSIBLINGS", "0x04000000", "" ],
		[ "WS_CLIPCHILDREN", "0x02000000", "" ],
		[ "WS_MAXIMIZE", "0x01000000", "" ],
		[ "WS_CAPTION", "0x00C00000", "" ],
		[ "WS_BORDER", "0x00800000", "" ],
		[ "WS_DLGFRAME", "0x00400000", "" ],
		[ "WS_VSCROLL", "0x00200000", "" ],
		[ "WS_HSCROLL", "0x00100000", "" ],
		[ "WS_SYSMENU", "0x00080000", "" ],
		[ "WS_THICKFRAME", "0x00040000", "" ],
		[ "WS_GROUP", "0x00020000", "" ],
		[ "WS_TABSTOP", "0x00010000", "" ],
		[ "WS_MINIMIZEBOX", "0x00020000", "" ],
		[ "WS_MAXIMIZEBOX", "0x00010000", "" ],
		[ "WS_TILED", "WS_OVERLAPPED", "" ],
		[ "WS_ICONIC", "WS_MINIMIZE", "" ],
		[ "WS_SIZEBOX", "WS_THICKFRAME", "" ],
		[ "WS_OVERLAPPEDWINDOW", "(WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_THICKFRAME|WS_MINIMIZEBOX|WS_MAXIMIZEBOX)", "" ],
		[ "WS_POPUPWINDOW", "(WS_POPUP|WS_BORDER|WS_SYSMENU)", "" ],
		[ "WS_CHILDWINDOW", "WS_CHILD", "" ],
		[ "WS_TILEDWINDOW", "WS_OVERLAPPEDWINDOW", "" ],
		[ "WM_STYLECHANGING", "0x007C", "" ],
		[ "WM_STYLECHANGED", "0x007D", "" ],
		[ "WM_DISPLAYCHANGE", "0x007E", "" ],
[ "WM_SHOWWINDOW", "0x0018", "" ],
	];

	CreateWindowsEnum
	(
		"",
		items
	);
}


/*


*/



// Structs

c += Tabs() + "#pragma pack(push, 1)" + NEW_LINE;
c += NEW_LINE;

// RECT
{
	let items =
	[
		[ "left", "LONG" ],
		[ "top", "LONG" ],
		[ "right", "LONG" ],
		[ "bottom", "LONG" ],
	];

	CreateWindowsTuple
	(
		"RECT",
		items
	);
}

// POINT
{
	let items =
	[
		[ "x", "LONG" ],
		[ "y", "LONG" ],
	];

	CreateWindowsTuple
	(
		"POINT",
		items,
		0,
		TypeFlags_NoLPC
	);
}

// SIZE
{
	let items =
	[
		[ "cx", "LONG" ],
		[ "cy", "LONG" ],
	];

	CreateWindowsTuple
	(
		"SIZE",
		items,
		0,
		TypeFlags_NoLPC
	);
}

// SYSTEM_INFO
{
	let items =
	[
		[ "", "union",
			[
				[ "dwOemId", "DWORD" ],
				[ "", "struct",
					[
						[ "wProcessorArchitecture", "WORD" ],
						[ "wReserved", "WORD" ],
					],
				],
			],
		],
		[ "dwPageSize", "DWORD" ],
		[ "lpMinimumApplicationAddress", "LPVOID" ],
		[ "lpMaximumApplicationAddress", "LPVOID" ],
		[ "dwActiveProcessorMask", "DWORD_PTR" ],
		[ "dwNumberOfProcessors", "DWORD" ],
		[ "dwProcessorType", "DWORD" ],
		[ "dwAllocationGranularity", "DWORD" ],
		[ "wProcessorLevel", "WORD" ],
		[ "wProcessorRevision", "WORD" ],
	];

	CreateWindowsTuple
	(
		"SYSTEM_INFO",
		items,
		0,
		TypeFlags_NoP |
		TypeFlags_NoLPC
	);
}

// MEMORY_BASIC_INFORMATION
{
	let items =
	[
		[ "BaseAddress", "PVOID" ],
		[ "AllocationBase", "PVOID" ],
		[ "AllocationProtect", "DWORD" ],
		[ "_(4)", "" ],
		[ "RegionSize", "SIZE_T" ],
		[ "State", "DWORD" ],
		[ "Protect", "DWORD" ],
		[ "Type", "DWORD" ],
		[ "_(4)", "" ],
	];

	CreateWindowsTuple
	(
		"MEMORY_BASIC_INFORMATION",
		items,
		0,
		TypeFlags_NoLP |
		TypeFlags_NoLPC
	);
}

// @Todo: Rename to MODULEENTRY32A.
// MODULEENTRY32
{
	let items =
	[
		[ "dwSize", "DWORD" ],
		[ "th32ModuleID", "DWORD" ],
		[ "th32ProcessID", "DWORD" ],
		[ "GlblcntUsage", "DWORD" ],
		[ "ProccntUsage", "DWORD" ],
		[ "_(4)", "" ],
		[ "modBaseAddr", "BYTE*" ],
		[ "modBaseSize", "DWORD" ],
		[ "_(4)", "" ],
		[ "hModule", "HMODULE" ],
		[ "szModule[256]", "char" ],
		[ "szExePath[260]", "char" ],
		[ "_(4)", "" ],
	];

	CreateWindowsTuple
	(
		"MODULEENTRY32",
		items,
		0,
		TypeFlags_NoLPC
	);
}

// MODULEENTRY32W
{
	let items =
	[
		[ "dwSize", "DWORD" ],
		[ "th32ModuleID", "DWORD" ],
		[ "th32ProcessID", "DWORD" ],
		[ "GlblcntUsage", "DWORD" ],
		[ "ProccntUsage", "DWORD" ],
		[ "_(4)", "" ],
		[ "modBaseAddr", "BYTE*" ],
		[ "modBaseSize", "DWORD" ],
		[ "_(4)", "" ],
		[ "hModule", "HMODULE" ],
		[ "szModule[256]", "WCHAR" ],
		[ "szExePath[260]", "WCHAR" ],
	];

	CreateWindowsTuple
	(
		"MODULEENTRY32W",
		items,
		0,
		TypeFlags_NoLPC
	);
}

// SECURITY_ATTRIBUTES
{
	let items =
	[
		[ "nLength", "DWORD" ],
		[ "_(4)", "" ],
		[ "lpSecurityDescriptor", "LPVOID" ],
		[ "bInheritHandle", "BOOL" ],
		[ "_(4)", "" ],
	];

	CreateWindowsTuple
	(
		"SECURITY_ATTRIBUTES",
		items,
		0,
		TypeFlags_NoLPC
	);
}

// OVERLAPPED
{
	let items =
	[
		[ "Internal", "ULONG_PTR" ],
		[ "InternalHigh", "ULONG_PTR" ],
		[ "", "union",
			[
				[ "", "struct",
					[
						[ "Offset", "DWORD" ],
						[ "OffsetHigh", "DWORD" ],
					],
				],
				[ "Pointer", "PVOID" ],
			],
		],
		[ "hEvent", "HANDLE" ],
	];

	CreateWindowsTuple
	(
		"OVERLAPPED",
		items,
		0,
		TypeFlags_NoP |
		TypeFlags_NoLPC
	);
}

// FILETIME
{
	let items =
	[
		[ "dwLowDateTime", "DWORD" ],
		[ "dwHighDateTime", "DWORD" ],
	];

	CreateWindowsTuple
	(
		"FILETIME",
		items,
		0,
		TypeFlags_NoLPC
	);
}

// BY_HANDLE_FILE_INFORMATION
{
	let items =
	[
		[ "dwFileAttributes", "DWORD" ],
		[ "ftCreationTime", "FILETIME" ],
		[ "ftLastAccessTime", "FILETIME" ],
		[ "ftLastWriteTime", "FILETIME" ],
		[ "dwVolumeSerialNumber", "DWORD" ],
		[ "nFileSizeHigh", "DWORD" ],
		[ "nFileSizeLow", "DWORD" ],
		[ "nNumberOfLinks", "DWORD" ],
		[ "nFileIndexHigh", "DWORD" ],
		[ "nFileIndexLow", "DWORD" ],
	];

	CreateWindowsTuple
	(
		"BY_HANDLE_FILE_INFORMATION",
		items,
		0,
		TypeFlags_NoLPC
	);
}

// LARGE_INTEGER
{
	let items =
	[
		[ "", "struct",
			[
				[ "LowPart", "DWORD" ],
				[ "HighPart", "LONG" ],
			],
		],
		[ "QuadPart", "LONGLONG" ],
	];

	CreateWindowsTuple
	(
		"LARGE_INTEGER",
		items,
		TupleFlags_Union,
		TypeFlags_NoLP |
		TypeFlags_NoLPC
	);
}

// SYSTEMTIME
{
	let items =
	[
		[ "wYear", "WORD" ],
		[ "wMonth", "WORD" ],
		[ "wDayOfWeek", "WORD" ],
		[ "wDay", "WORD" ],
		[ "wHour", "WORD" ],
		[ "wMinute", "WORD" ],
		[ "wSecond", "WORD" ],
		[ "wMilliseconds", "WORD" ],
	];

	CreateWindowsTuple
	(
		"SYSTEMTIME",
		items,
		0,
		TypeFlags_NoLPC
	);
}

// WNDCLASSEXA
{
	let items =
	[
		[ "cbSize", "UINT" ],
		[ "style", "UINT" ],
		[ "lpfnWndProc", "WNDPROC" ],
		[ "cbClsExtra", "int" ],
		[ "cbWndExtra", "int" ],
		[ "hInstance", "HINSTANCE" ],
		[ "hIcon", "HICON" ],
		[ "hCursor", "HCURSOR" ],
		[ "hbrBackground", "HBRUSH" ],
		[ "lpszMenuName", "LPCSTR" ],
		[ "lpszClassName", "LPCSTR" ],
		[ "hIconSm", "HICON" ],
	];

	CreateWindowsTuple
	(
		"WNDCLASSEXA",
		items,
		0,
		TypeFlags_NoLPC
	);
}

// WNDCLASSEXW
{
	let items =
	[
		[ "cbSize", "UINT" ],
		[ "style", "UINT" ],
		[ "lpfnWndProc", "WNDPROC" ],
		[ "cbClsExtra", "int" ],
		[ "cbWndExtra", "int" ],
		[ "hInstance", "HINSTANCE" ],
		[ "hIcon", "HICON" ],
		[ "hCursor", "HCURSOR" ],
		[ "hbrBackground", "HBRUSH" ],
		[ "lpszMenuName", "LPCWSTR" ],
		[ "lpszClassName", "LPCWSTR" ],
		[ "hIconSm", "HICON" ],
	];

	CreateWindowsTuple
	(
		"WNDCLASSEXW",
		items,
		0,
		TypeFlags_NoLPC
	);
}

// GUID
{
	let items =
	[
		[ "Data1", "unsigned long" ],
		[ "Data2", "unsigned short" ],
		[ "Data3", "unsigned short" ],
		[ "Data4[8]", "unsigned char" ],
	];

	CreateWindowsTuple
	(
		"GUID",
		items,
		0,
		TypeFlags_NoP
	);
}

CreateWindowsTypedef
(
	"IID",
	"GUID",
	16,
	TypeFlags_NoP |
	TypeFlags_NoLPC
);

// LUID
{
	let items =
	[
		[ "LowPart", "DWORD" ],
		[ "HighPart", "LONG" ],
	];

	CreateWindowsTuple
	(
		"LUID",
		items,
		0,
		TypeFlags_NoLP |
		TypeFlags_NoLPC
	);
}

c += Tabs() + "#pragma pack(pop)" + NEW_LINE;
c += NEW_LINE;

// Forward Declarations

{
	let names =
	[
		"IUnknown",
	];

	CreateForwardDeclarations
	(
		names,
		"struct"
	);

	CreateForwardDeclarations
	(
		names,
		"const IID",
		"extern \"C\" ",
		"IID_"
	);
}

// Functions
{
	let items =
	[
		[ "GetLastError", "DWORD",
			[
			],
			FunctionFlags_ExternC
		],
		[ "SetLastError", "void",
			[
				[ "dwErrCode", "DWORD" ],
			],
			FunctionFlags_ExternC
		],
		[ "VirtualAlloc", "LPVOID",
			[
				[ "lpAddress", "LPVOID" ],
				[ "dwSize", "SIZE_T" ],
				[ "flAllocationType", "DWORD" ],
				[ "flProtect", "DWORD" ],
			],
			FunctionFlags_ExternC
		],
		[ "VirtualProtect", "BOOL",
			[
				[ "lpAddress", "LPVOID" ],
				[ "dwSize", "SIZE_T" ],
				[ "flNewProtect", "DWORD" ],
				[ "lpflOldProtect", "PDWORD" ],
			],
			FunctionFlags_ExternC
		],
		[ "VirtualFree", "BOOL",
			[
				[ "lpAddress", "LPVOID" ],
				[ "dwSize", "SIZE_T" ],
				[ "dwFreeType", "DWORD" ],
			],
			FunctionFlags_ExternC
		],
		[ "VirtualQuery", "SIZE_T",
			[
				[ "lpAddress", "LPCVOID" ],
				[ "lpBuffer", "PMEMORY_BASIC_INFORMATION" ],
				[ "dwLength", "SIZE_T" ],
			],
			FunctionFlags_ExternC
		],
		[ "VirtualAllocEx", "LPVOID",
			[
				[ "hProcess", "HANDLE" ],
				[ "lpAddress", "LPVOID" ],
				[ "dwSize", "SIZE_T" ],
				[ "flAllocationType", "DWORD" ],
				[ "flProtect", "DWORD" ],
			],
			FunctionFlags_ExternC
		],
		[ "VirtualProtectEx", "BOOL",
			[
				[ "hProcess", "HANDLE" ],
				[ "lpAddress", "LPVOID" ],
				[ "dwSize", "SIZE_T" ],
				[ "flNewProtect", "DWORD" ],
				[ "lpflOldProtect", "PDWORD" ],
			],
			FunctionFlags_ExternC
		],
		[ "VirtualQueryEx", "SIZE_T",
			[
				[ "hProcess", "HANDLE" ],
				[ "lpAddress", "LPCVOID" ],
				[ "lpBuffer", "PMEMORY_BASIC_INFORMATION" ],
				[ "dwLength", "SIZE_T" ],
			],
			FunctionFlags_ExternC
		],
		[ "CreateFileA", "HANDLE",
			[
				[ "lpFileName", "LPCSTR" ],
				[ "dwDesiredAccess", "DWORD" ],
				[ "dwShareMode", "DWORD" ],
				[ "lpSecurityAttributes", "LPSECURITY_ATTRIBUTES" ],
				[ "dwCreationDisposition", "DWORD" ],
				[ "dwFlagsAndAttributes", "DWORD" ],
				[ "hTemplateFile", "HANDLE" ],
			],
			FunctionFlags_ExternC
		],
		[ "CreateFileW", "HANDLE",
			[
				[ "lpFileName", "LPCWSTR" ],
				[ "dwDesiredAccess", "DWORD" ],
				[ "dwShareMode", "DWORD" ],
				[ "lpSecurityAttributes", "LPSECURITY_ATTRIBUTES" ],
				[ "dwCreationDisposition", "DWORD" ],
				[ "dwFlagsAndAttributes", "DWORD" ],
				[ "hTemplateFile", "HANDLE" ],
			],
			FunctionFlags_ExternC
		],
		[ "CloseHandle", "BOOL",
			[
				[ "hObject", "HANDLE" ],
			],
			FunctionFlags_ExternC
		],
		[ "GetFileInformationByHandle", "BOOL",
			[
				[ "hFile", "HANDLE" ],
				[ "lpFileInformation", "LPBY_HANDLE_FILE_INFORMATION" ],
			],
			FunctionFlags_ExternC
		],
		[ "SetFilePointerEx", "BOOL",
			[
				[ "hFile", "HANDLE" ],
				[ "liDistanceToMove", "LARGE_INTEGER" ],
				[ "lpNewFilePointer", "PLARGE_INTEGER" ],
				[ "dwMoveMethod", "DWORD" ],
			],
			FunctionFlags_ExternC
		],
		[ "ReadFile", "BOOL",
			[
				[ "hFile", "HANDLE" ],
				[ "lpBuffer", "LPVOID" ],
				[ "nNumberOfBytesToRead", "DWORD" ],
				[ "lpNumberOfBytesRead", "LPDWORD" ],
				[ "lpOverlapped", "LPOVERLAPPED" ],
			],
			FunctionFlags_ExternC
		],
		[ "WriteFile", "BOOL",
			[
				[ "hFile", "HANDLE" ],
				[ "lpBuffer", "LPCVOID" ],
				[ "nNumberOfBytesToWrite", "DWORD" ],
				[ "lpNumberOfBytesWritten", "LPDWORD" ],
				[ "lpOverlapped", "LPOVERLAPPED" ],
			],
			FunctionFlags_ExternC
		],
		[ "CreateDirectoryA", "BOOL",
			[
				[ "lpPathName", "LPCSTR" ],
				[ "lpSecurityAttributes", "LPSECURITY_ATTRIBUTES" ],
			],
			FunctionFlags_ExternC
		],
		[ "CreateDirectoryW", "BOOL",
			[
				[ "lpPathName", "LPCWSTR" ],
				[ "lpSecurityAttributes", "LPSECURITY_ATTRIBUTES" ],
			],
			FunctionFlags_ExternC
		],
		[ "DeleteFileA", "BOOL",
			[
				[ "lpFileName", "LPCSTR" ],
			],
			FunctionFlags_ExternC
		],
		[ "DeleteFileW", "BOOL",
			[
				[ "lpFileName", "LPCWSTR" ],
			],
			FunctionFlags_ExternC
		],
		[ "OutputDebugStringA", "void",
			[
				[ "lpOutputString", "LPCSTR" ],
			],
			FunctionFlags_ExternC
		],
		[ "OutputDebugStringW", "void",
			[
				[ "lpOutputString", "LPCWSTR" ],
			],
			FunctionFlags_ExternC
		],
		[ "MessageBoxA", "int",
			[
				[ "hWnd", "HWND" ],
				[ "lpText", "LPCSTR" ],
				[ "lpCaption", "LPCSTR" ],
				[ "uType", "UINT" ],
			],
			FunctionFlags_ExternC
		],
		[ "MessageBoxW", "int",
			[
				[ "hWnd", "HWND" ],
				[ "lpText", "LPCWSTR" ],
				[ "lpCaption", "LPCWSTR" ],
				[ "uType", "UINT" ],
			],
			FunctionFlags_ExternC
		],
		[ "GetLocalTime", "void",
			[
				[ "lpSystemTime", "LPSYSTEMTIME" ],
			],
			FunctionFlags_ExternC
		],
		[ "CreateToolhelp32Snapshot", "HANDLE",
			[
				[ "dwFlags", "DWORD" ],
				[ "th32ProcessID", "DWORD" ],
			],
			FunctionFlags_ExternC
		],
		[ "Module32FirstW", "BOOL",
			[
				[ "hSnapshot", "HANDLE" ],
				[ "lpme", "LPMODULEENTRY32W" ],
			],
			FunctionFlags_ExternC
		],
		[ "Module32NextW", "BOOL",
			[
				[ "hSnapshot", "HANDLE" ],
				[ "lpme", "LPMODULEENTRY32W" ],
			],
			FunctionFlags_ExternC
		],
		[ "Module32First", "BOOL",
			[
				[ "hSnapshot", "HANDLE" ],
				[ "lpme", "LPMODULEENTRY32" ],
			],
			FunctionFlags_ExternC
		],
		[ "Module32Next", "BOOL",
			[
				[ "hSnapshot", "HANDLE" ],
				[ "lpme", "LPMODULEENTRY32" ],
			],
			FunctionFlags_ExternC
		],
		[ "GetSystemInfo", "void",
			[
				[ "lpSystemInfo", "LPSYSTEM_INFO" ],
			],
			FunctionFlags_ExternC
		],
		[ "QueryPerformanceCounter", "BOOL",
			[
				[ "lpPerformanceCount", "LARGE_INTEGER*" ],
			],
			FunctionFlags_ExternC
		],
		[ "QueryPerformanceFrequency", "BOOL",
			[
				[ "lpFrequency", "LARGE_INTEGER*" ],
			],
			FunctionFlags_ExternC
		],
		[ "ShowCursor", "int",
			[
				[ "bShow", "BOOL" ],
			],
			FunctionFlags_ExternC
		],
		[ "GetCursorPos", "BOOL",
			[
				[ "lpPoint", "LPPOINT" ],
			],
			FunctionFlags_ExternC
		],
		[ "LoadCursorA", "HCURSOR",
			[
				[ "hInstance", "HINSTANCE" ],
				[ "lpCursorName", "LPCSTR" ],
			],
			FunctionFlags_ExternC
		],
		[ "LoadCursorW", "HCURSOR",
			[
				[ "hInstance", "HINSTANCE" ],
				[ "lpCursorName", "LPCWSTR" ],
			],
			FunctionFlags_ExternC
		],
		[ "GetWindowRect", "BOOL",
			[
				[ "hWnd", "HWND" ],
				[ "lpRect", "LPRECT" ],
			],
			FunctionFlags_ExternC
		],
		[ "SetClassLongPtrA", "ULONG_PTR",
			[
				[ "hWnd", "HWND" ],
				[ "nIndex", "int" ],
				[ "dwNewLong", "LONG_PTR" ],
			],
			FunctionFlags_ExternC
		],
		[ "SetClassLongPtrW", "ULONG_PTR",
			[
				[ "hWnd", "HWND" ],
				[ "nIndex", "int" ],
				[ "dwNewLong", "LONG_PTR" ],
			],
			FunctionFlags_ExternC
		],
		[ "LoadLibraryA", "HMODULE",
			[
				[ "lpLibFileName", "LPCSTR" ],
			],
			FunctionFlags_ExternC
		],
		[ "LoadLibraryW", "HMODULE",
			[
				[ "lpLibFileName", "LPCWSTR" ],
			],
			FunctionFlags_ExternC
		],
		[ "GetProcAddress", "FARPROC",
			[
				[ "hModule", "HMODULE" ],
				[ "lpProcName", "LPCSTR" ],
			],
			FunctionFlags_ExternC
		],
		[ "ShellExecuteA", "HINSTANCE",
			[
				[ "hwnd", "HWND" ],
				[ "lpOperation", "LPCSTR" ],
				[ "lpFile", "LPCSTR" ],
				[ "lpParameters", "LPCSTR" ],
				[ "lpDirectory", "LPCSTR" ],
				[ "nShowCmd", "INT" ],
			],
			FunctionFlags_ExternC
		],
		[ "ShellExecuteW", "HINSTANCE",
			[
				[ "hwnd", "HWND" ],
				[ "lpOperation", "LPCWSTR" ],
				[ "lpFile", "LPCWSTR" ],
				[ "lpParameters", "LPCWSTR" ],
				[ "lpDirectory", "LPCWSTR" ],
				[ "nShowCmd", "INT" ],
			],
			FunctionFlags_ExternC
		],
		[ "RegisterClassExA", "ATOM",
			[
				[ "", "const WNDCLASSEXA*" ],
			],
			FunctionFlags_ExternC
		],
		[ "RegisterClassExW", "ATOM",
			[
				[ "", "const WNDCLASSEXW*" ],
			],
			FunctionFlags_ExternC
		],
		[ "CreateWindowExA", "HWND",
			[
				[ "dwExStyle", "DWORD" ],
				[ "lpClassName", "LPCSTR" ],
				[ "lpWindowName", "LPCSTR" ],
				[ "dwStyle", "DWORD" ],
				[ "X", "int" ],
				[ "Y", "int" ],
				[ "nWidth", "int" ],
				[ "nHeight", "int" ],
				[ "hWndParent", "HWND" ],
				[ "hMenu", "HMENU" ],
				[ "hInstance", "HINSTANCE" ],
				[ "lpParam", "LPVOID" ],
			],
			FunctionFlags_ExternC
		],
		[ "CreateWindowExW", "HWND",
			[
				[ "dwExStyle", "DWORD" ],
				[ "lpClassName", "LPCWSTR" ],
				[ "lpWindowName", "LPCWSTR" ],
				[ "dwStyle", "DWORD" ],
				[ "X", "int" ],
				[ "Y", "int" ],
				[ "nWidth", "int" ],
				[ "nHeight", "int" ],
				[ "hWndParent", "HWND" ],
				[ "hMenu", "HMENU" ],
				[ "hInstance", "HINSTANCE" ],
				[ "lpParam", "LPVOID" ],
			],
			FunctionFlags_ExternC
		],
		[ "ScreenToClient", "BOOL",
			[
				[ "hWnd", "HWND" ],
				[ "lpPoint", "LPPOINT" ],
			],
			FunctionFlags_ExternC
		],
		[ "PostMessageA", "BOOL",
			[
				[ "hWnd", "HWND" ],
				[ "Msg", "UINT" ],
				[ "wParam", "WPARAM" ],
				[ "lParam", "LPARAM" ],
			],
			FunctionFlags_ExternC
		],
		[ "PostMessageW", "BOOL",
			[
				[ "hWnd", "HWND" ],
				[ "Msg", "UINT" ],
				[ "wParam", "WPARAM" ],
				[ "lParam", "LPARAM" ],
			],
			FunctionFlags_ExternC
		],
		[ "SetWindowPos", "BOOL",
			[
				[ "hWnd", "HWND" ],
				[ "hWndInsertAfter", "HWND" ],
				[ "X", "int" ],
				[ "Y", "int" ],
				[ "cx", "int" ],
				[ "cy", "int" ],
				[ "uFlags", "UINT" ],
			],
			FunctionFlags_ExternC
		],
		[ "Sleep", "void",
			[
				[ "dwMilliseconds", "DWORD" ],
			],
			FunctionFlags_ExternC
		],
		[ "GetForegroundWindow", "HWND",
			[
			],
			FunctionFlags_ExternC
		],
		[ "CreateThread", "HANDLE",
			[
				[ "lpThreadAttributes", "LPSECURITY_ATTRIBUTES" ],
				[ "dwStackSize", "SIZE_T" ],
				[ "lpStartAddress", "LPTHREAD_START_ROUTINE" ],
				[ "lpParameter", "LPVOID" ],
				[ "dwCreationFlags", "DWORD" ],
				[ "lpThreadId", "LPDWORD" ],
			],
			FunctionFlags_ExternC
		],
		[ "GetWindowsDirectoryA", "UINT",
			[
				[ "lpBuffer", "LPSTR" ],
				[ "uSize", "UINT" ],
			],
			FunctionFlags_ExternC
		],
		[ "GetWindowsDirectoryW", "UINT",
			[
				[ "lpBuffer", "LPWSTR" ],
				[ "uSize", "UINT" ],
			],
			FunctionFlags_ExternC
		],
		[ "ClientToScreen", "BOOL",
			[
				[ "hWnd", "HWND" ],
				[ "lpPoint", "LPPOINT" ],
			],
			FunctionFlags_ExternC
		],
		[ "SetCursorPos", "BOOL",
			[
				[ "X", "int" ],
				[ "Y", "int" ],
			],
			FunctionFlags_ExternC
		],
		[ "GetWindowLongA", "LONG",
			[
				[ "hWnd", "HWND" ],
				[ "nIndex", "int" ],
			],
			FunctionFlags_ExternC
		],
		[ "GetWindowLongW", "LONG",
			[
				[ "hWnd", "HWND" ],
				[ "nIndex", "int" ],
			],
			FunctionFlags_ExternC
		],
		[ "SetWindowLongA", "LONG",
			[
				[ "hWnd", "HWND" ],
				[ "nIndex", "int" ],
				[ "dwNewLong", "LONG" ],
			],
			FunctionFlags_ExternC
		],
		[ "SetWindowLongW", "LONG",
			[
				[ "hWnd", "HWND" ],
				[ "nIndex", "int" ],
				[ "dwNewLong", "LONG" ],
			],
			FunctionFlags_ExternC
		],
		[ "GetWindowLongPtrA", "LONG_PTR",
			[
				[ "hWnd", "HWND" ],
				[ "nIndex", "int" ],
			],
			FunctionFlags_ExternC
		],
		[ "GetWindowLongPtrW", "LONG_PTR",
			[
				[ "hWnd", "HWND" ],
				[ "nIndex", "int" ],
			],
			FunctionFlags_ExternC
		],
		[ "SetWindowLongPtrA", "LONG_PTR",
			[
				[ "hWnd", "HWND" ],
				[ "nIndex", "int" ],
				[ "dwNewLong", "LONG_PTR" ],
			],
			FunctionFlags_ExternC
		],
		[ "SetWindowLongPtrW", "LONG_PTR",
			[
				[ "hWnd", "HWND" ],
				[ "nIndex", "int" ],
				[ "dwNewLong", "LONG_PTR" ],
			],
			FunctionFlags_ExternC
		],
		[ "GetClientRect", "BOOL",
			[
				[ "hWnd", "HWND" ],
				[ "lpRect", "LPRECT" ],
			],
			FunctionFlags_ExternC
		],
		[ "AdjustWindowRect", "BOOL",
			[
				[ "lpRect", "LPRECT" ],
				[ "dwStyle", "DWORD" ],
				[ "bMenu", "BOOL" ],
			],
			FunctionFlags_ExternC
		],
		[ "AdjustWindowRectEx", "BOOL",
			[
				[ "lpRect", "LPRECT" ],
				[ "dwStyle", "DWORD" ],
				[ "bMenu", "BOOL" ],
				[ "dwExStyle", "DWORD" ],
			],
			FunctionFlags_ExternC
		],
		[ "AdjustWindowRectExForDpi", "BOOL",
			[
				[ "lpRect", "LPRECT" ],
				[ "dwStyle", "DWORD" ],
				[ "bMenu", "BOOL" ],
				[ "dwExStyle", "DWORD" ],
				[ "dpi", "UINT" ],
			],
			FunctionFlags_ExternC
		],
	];

	CreateFunctions(items);
}




/*











*/


c += NEW_LINE;

// Function Tuples


// IUnknown
{
	let items =
	[
		[ "QueryInterface", "HRESULT",
			[
				[ "riid", "const IID&" ],
				[ "ppvObject", "void**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "AddRef", "ULONG",
			[
			],
			FunctionFlags_PureVirtual
		],
		[ "Release", "ULONG",
			[
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"IUnknown",
		items,
		[ "novtable" ]
	);
}

CreateWindowsTypedef
(
	"LPUNKNOWN",
	"IUnknown*",
	8,
	TypeFlags_NoPointers
);

c += NEW_LINE;

ModuleEnd();

CleanStream();

fs.writeFileSync("../Core/Windows.ixx", c);

// Verify

ModuleVerify();

CleanStream();

fs.writeFileSync("../verifyWindows.cpp", c);

ClearAll();
}

// #endregion

// #region DXGI
{
console.log("DXGI");

ModuleStart
(
	"DXGI",
	[
		"Windows"
	],
	[
		"Windows"
	]
);

// Forward Declarations

{
	let names =
	[
		"IDXGIObject",
		"IDXGIDeviceSubObject",
		"IDXGIResource",
		"IDXGIKeyedMutex",
		"IDXGISurface",
		"IDXGISurface1",
		"IDXGIAdapter",
		"IDXGIOutput",
		"IDXGISwapChain",
		"IDXGIFactory",
		"IDXGIDevice",
		"IDXGIFactory1",
		"IDXGIAdapter1",
		"IDXGIDevice1",
	];

	CreateForwardDeclarations
	(
		names,
		"struct"
	);

	CreateForwardDeclarations
	(
		names,
		"const IID",
		"extern \"C\" ",
		"IID_"
	);
}

// Types
{
	let items =
	[
		[ "DXGI_USAGE", "UINT", 4, TypeFlags_NoPointers ],
	];

	CreateWindowsTypedefs(items);
}

// Function Types
{
	let items =
	[
	];

	CreateWindowsFunctionTypedefs(items);
}

// Enums
{
	let items =
	[
	];

	CreateWindowsEnum
	(
		"",
		items
	);
}

// DXGI_FORMAT
{
	let items =
	[
		[ "DXGI_FORMAT_UNKNOWN", "0", "" ],
		[ "DXGI_FORMAT_R32G32B32A32_TYPELESS", "1", "" ],
		[ "DXGI_FORMAT_R32G32B32A32_FLOAT", "2", "" ],
		[ "DXGI_FORMAT_R32G32B32A32_UINT", "3", "" ],
		[ "DXGI_FORMAT_R32G32B32A32_SINT", "4", "" ],
		[ "DXGI_FORMAT_R32G32B32_TYPELESS", "5", "" ],
		[ "DXGI_FORMAT_R32G32B32_FLOAT", "6", "" ],
		[ "DXGI_FORMAT_R32G32B32_UINT", "7", "" ],
		[ "DXGI_FORMAT_R32G32B32_SINT", "8", "" ],
		[ "DXGI_FORMAT_R16G16B16A16_TYPELESS", "9", "" ],
		[ "DXGI_FORMAT_R16G16B16A16_FLOAT", "10", "" ],
		[ "DXGI_FORMAT_R16G16B16A16_UNORM", "11", "" ],
		[ "DXGI_FORMAT_R16G16B16A16_UINT", "12", "" ],
		[ "DXGI_FORMAT_R16G16B16A16_SNORM", "13", "" ],
		[ "DXGI_FORMAT_R16G16B16A16_SINT", "14", "" ],
		[ "DXGI_FORMAT_R32G32_TYPELESS", "15", "" ],
		[ "DXGI_FORMAT_R32G32_FLOAT", "16", "" ],
		[ "DXGI_FORMAT_R32G32_UINT", "17", "" ],
		[ "DXGI_FORMAT_R32G32_SINT", "18", "" ],
		[ "DXGI_FORMAT_R32G8X24_TYPELESS", "19", "" ],
		[ "DXGI_FORMAT_D32_FLOAT_S8X24_UINT", "20", "" ],
		[ "DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS", "21", "" ],
		[ "DXGI_FORMAT_X32_TYPELESS_G8X24_UINT", "22", "" ],
		[ "DXGI_FORMAT_R10G10B10A2_TYPELESS", "23", "" ],
		[ "DXGI_FORMAT_R10G10B10A2_UNORM", "24", "" ],
		[ "DXGI_FORMAT_R10G10B10A2_UINT", "25", "" ],
		[ "DXGI_FORMAT_R11G11B10_FLOAT", "26", "" ],
		[ "DXGI_FORMAT_R8G8B8A8_TYPELESS", "27", "" ],
		[ "DXGI_FORMAT_R8G8B8A8_UNORM", "28", "" ],
		[ "DXGI_FORMAT_R8G8B8A8_UNORM_SRGB", "29", "" ],
		[ "DXGI_FORMAT_R8G8B8A8_UINT", "30", "" ],
		[ "DXGI_FORMAT_R8G8B8A8_SNORM", "31", "" ],
		[ "DXGI_FORMAT_R8G8B8A8_SINT", "32", "" ],
		[ "DXGI_FORMAT_R16G16_TYPELESS", "33", "" ],
		[ "DXGI_FORMAT_R16G16_FLOAT", "34", "" ],
		[ "DXGI_FORMAT_R16G16_UNORM", "35", "" ],
		[ "DXGI_FORMAT_R16G16_UINT", "36", "" ],
		[ "DXGI_FORMAT_R16G16_SNORM", "37", "" ],
		[ "DXGI_FORMAT_R16G16_SINT", "38", "" ],
		[ "DXGI_FORMAT_R32_TYPELESS", "39", "" ],
		[ "DXGI_FORMAT_D32_FLOAT", "40", "" ],
		[ "DXGI_FORMAT_R32_FLOAT", "41", "" ],
		[ "DXGI_FORMAT_R32_UINT", "42", "" ],
		[ "DXGI_FORMAT_R32_SINT", "43", "" ],
		[ "DXGI_FORMAT_R24G8_TYPELESS", "44", "" ],
		[ "DXGI_FORMAT_D24_UNORM_S8_UINT", "45", "" ],
		[ "DXGI_FORMAT_R24_UNORM_X8_TYPELESS", "46", "" ],
		[ "DXGI_FORMAT_X24_TYPELESS_G8_UINT", "47", "" ],
		[ "DXGI_FORMAT_R8G8_TYPELESS", "48", "" ],
		[ "DXGI_FORMAT_R8G8_UNORM", "49", "" ],
		[ "DXGI_FORMAT_R8G8_UINT", "50", "" ],
		[ "DXGI_FORMAT_R8G8_SNORM", "51", "" ],
		[ "DXGI_FORMAT_R8G8_SINT", "52", "" ],
		[ "DXGI_FORMAT_R16_TYPELESS", "53", "" ],
		[ "DXGI_FORMAT_R16_FLOAT", "54", "" ],
		[ "DXGI_FORMAT_D16_UNORM", "55", "" ],
		[ "DXGI_FORMAT_R16_UNORM", "56", "" ],
		[ "DXGI_FORMAT_R16_UINT", "57", "" ],
		[ "DXGI_FORMAT_R16_SNORM", "58", "" ],
		[ "DXGI_FORMAT_R16_SINT", "59", "" ],
		[ "DXGI_FORMAT_R8_TYPELESS", "60", "" ],
		[ "DXGI_FORMAT_R8_UNORM", "61", "" ],
		[ "DXGI_FORMAT_R8_UINT", "62", "" ],
		[ "DXGI_FORMAT_R8_SNORM", "63", "" ],
		[ "DXGI_FORMAT_R8_SINT", "64", "" ],
		[ "DXGI_FORMAT_A8_UNORM", "65", "" ],
		[ "DXGI_FORMAT_R1_UNORM", "66", "" ],
		[ "DXGI_FORMAT_R9G9B9E5_SHAREDEXP", "67", "" ],
		[ "DXGI_FORMAT_R8G8_B8G8_UNORM", "68", "" ],
		[ "DXGI_FORMAT_G8R8_G8B8_UNORM", "69", "" ],
		[ "DXGI_FORMAT_BC1_TYPELESS", "70", "" ],
		[ "DXGI_FORMAT_BC1_UNORM", "71", "" ],
		[ "DXGI_FORMAT_BC1_UNORM_SRGB", "72", "" ],
		[ "DXGI_FORMAT_BC2_TYPELESS", "73", "" ],
		[ "DXGI_FORMAT_BC2_UNORM", "74", "" ],
		[ "DXGI_FORMAT_BC2_UNORM_SRGB", "75", "" ],
		[ "DXGI_FORMAT_BC3_TYPELESS", "76", "" ],
		[ "DXGI_FORMAT_BC3_UNORM", "77", "" ],
		[ "DXGI_FORMAT_BC3_UNORM_SRGB", "78", "" ],
		[ "DXGI_FORMAT_BC4_TYPELESS", "79", "" ],
		[ "DXGI_FORMAT_BC4_UNORM", "80", "" ],
		[ "DXGI_FORMAT_BC4_SNORM", "81", "" ],
		[ "DXGI_FORMAT_BC5_TYPELESS", "82", "" ],
		[ "DXGI_FORMAT_BC5_UNORM", "83", "" ],
		[ "DXGI_FORMAT_BC5_SNORM", "84", "" ],
		[ "DXGI_FORMAT_B5G6R5_UNORM", "85", "" ],
		[ "DXGI_FORMAT_B5G5R5A1_UNORM", "86", "" ],
		[ "DXGI_FORMAT_B8G8R8A8_UNORM", "87", "" ],
		[ "DXGI_FORMAT_B8G8R8X8_UNORM", "88", "" ],
		[ "DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM", "89", "" ],
		[ "DXGI_FORMAT_B8G8R8A8_TYPELESS", "90", "" ],
		[ "DXGI_FORMAT_B8G8R8A8_UNORM_SRGB", "91", "" ],
		[ "DXGI_FORMAT_B8G8R8X8_TYPELESS", "92", "" ],
		[ "DXGI_FORMAT_B8G8R8X8_UNORM_SRGB", "93", "" ],
		[ "DXGI_FORMAT_BC6H_TYPELESS", "94", "" ],
		[ "DXGI_FORMAT_BC6H_UF16", "95", "" ],
		[ "DXGI_FORMAT_BC6H_SF16", "96", "" ],
		[ "DXGI_FORMAT_BC7_TYPELESS", "97", "" ],
		[ "DXGI_FORMAT_BC7_UNORM", "98", "" ],
		[ "DXGI_FORMAT_BC7_UNORM_SRGB", "99", "" ],
		[ "DXGI_FORMAT_AYUV", "100", "" ],
		[ "DXGI_FORMAT_Y410", "101", "" ],
		[ "DXGI_FORMAT_Y416", "102", "" ],
		[ "DXGI_FORMAT_NV12", "103", "" ],
		[ "DXGI_FORMAT_P010", "104", "" ],
		[ "DXGI_FORMAT_P016", "105", "" ],
		[ "DXGI_FORMAT_420_OPAQUE", "106", "" ],
		[ "DXGI_FORMAT_YUY2", "107", "" ],
		[ "DXGI_FORMAT_Y210", "108", "" ],
		[ "DXGI_FORMAT_Y216", "109", "" ],
		[ "DXGI_FORMAT_NV11", "110", "" ],
		[ "DXGI_FORMAT_AI44", "111", "" ],
		[ "DXGI_FORMAT_IA44", "112", "" ],
		[ "DXGI_FORMAT_P8", "113", "" ],
		[ "DXGI_FORMAT_A8P8", "114", "" ],
		[ "DXGI_FORMAT_B4G4R4A4_UNORM", "115", "" ],
		[ "DXGI_FORMAT_P208", "130", "" ],
		[ "DXGI_FORMAT_V208", "131", "" ],
		[ "DXGI_FORMAT_V408", "132", "" ],
		[ "DXGI_FORMAT_FORCE_UINT", "0xffffffff", "" ],
	];

	CreateWindowsEnum
	(
		"DXGI_FORMAT",
		items
	);
}




// DXGI_MODE_SCANLINE_ORDER
{
	let items =
	[
		[ "DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED", "0", "" ],
		[ "DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE", "1", "" ],
		[ "DXGI_MODE_SCANLINE_ORDER_UPPER_FIELD_FIRST", "2", "" ],
		[ "DXGI_MODE_SCANLINE_ORDER_LOWER_FIELD_FIRST", "3", "" ],
	];

	CreateWindowsEnum
	(
		"DXGI_MODE_SCANLINE_ORDER",
		items
	);
}




// DXGI_MODE_SCALING
{
	let items =
	[
		[ "DXGI_MODE_SCALING_UNSPECIFIED", "0", "" ],
		[ "DXGI_MODE_SCALING_CENTERED", "1", "" ],
		[ "DXGI_MODE_SCALING_STRETCHED", "2", "" ],
	];

	CreateWindowsEnum
	(
		"DXGI_MODE_SCALING",
		items
	);
}


// DXGI_MODE_ROTATION
{
	let items =
	[
		[ "DXGI_MODE_ROTATION_UNSPECIFIED", "0", "" ],
		[ "DXGI_MODE_ROTATION_IDENTITY", "1", "" ],
		[ "DXGI_MODE_ROTATION_ROTATE90", "2", "" ],
		[ "DXGI_MODE_ROTATION_ROTATE180", "3", "" ],
		[ "DXGI_MODE_ROTATION_ROTATE270", "4", "" ],
	];

	CreateWindowsEnum
	(
		"DXGI_MODE_ROTATION",
		items
	);
}

// DXGI_SWAP_EFFECT
{
	let items =
	[
		[ "DXGI_SWAP_EFFECT_DISCARD", "0", "" ],
		[ "DXGI_SWAP_EFFECT_SEQUENTIAL", "1", "" ],
		[ "DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL", "3", "" ],
		[ "DXGI_SWAP_EFFECT_FLIP_DISCARD", "4", "" ],
	];

	CreateWindowsEnum
	(
		"DXGI_SWAP_EFFECT",
		items
	);
}



// DXGI_RESIDENCY
{
	let items =
	[
		[ "DXGI_RESIDENCY_FULLY_RESIDENT", "1", "" ],
		[ "DXGI_RESIDENCY_RESIDENT_IN_SHARED_MEMORY", "2", "" ],
		[ "DXGI_RESIDENCY_EVICTED_TO_DISK", "3", "" ],
	];

	CreateWindowsEnum
	(
		"DXGI_RESIDENCY",
		items
	);
}


/*


*/













// Structs

c += Tabs() + "#pragma pack(push, 1)" + NEW_LINE;
c += NEW_LINE;



// DXGI_RATIONAL
{
	let items =
	[
		[ "Numerator", "UINT" ],
		[ "Denominator", "UINT" ],
	];

	CreateWindowsTuple
	(
		"DXGI_RATIONAL",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// DXGI_SAMPLE_DESC
{
	let items =
	[
		[ "Count", "UINT" ],
		[ "Quality", "UINT" ],
	];

	CreateWindowsTuple
	(
		"DXGI_SAMPLE_DESC",
		items,
		0,
		TypeFlags_NoPointers
	);
}

// DXGI_MODE_DESC
{
	let items =
	[
		[ "Width", "UINT" ],
		[ "Height", "UINT" ],
		[ "RefreshRate", "DXGI_RATIONAL" ],
		[ "Format", "DXGI_FORMAT" ],
		[ "ScanlineOrdering", "DXGI_MODE_SCANLINE_ORDER" ],
		[ "Scaling", "DXGI_MODE_SCALING" ],
	];

	CreateWindowsTuple
	(
		"DXGI_MODE_DESC",
		items,
		0,
		TypeFlags_NoPointers
	);
}

// DXGI_SURFACE_DESC
{
	let items =
	[
		[ "Width", "UINT" ],
		[ "Height", "UINT" ],
		[ "Format", "DXGI_FORMAT" ],
		[ "SampleDesc", "DXGI_SAMPLE_DESC" ],
	];

	CreateWindowsTuple
	(
		"DXGI_SURFACE_DESC",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// DXGI_MAPPED_RECT
{
	let items =
	[
		[ "Pitch", "INT" ],
		[ "_(4)", "" ],
		[ "pBits", "BYTE*" ],
	];

	CreateWindowsTuple
	(
		"DXGI_MAPPED_RECT",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// DXGI_ADAPTER_DESC
{
	let items =
	[
		[ "Description[128]", "WCHAR" ],
		[ "VendorId", "UINT" ],
		[ "DeviceId", "UINT" ],
		[ "SubSysId", "UINT" ],
		[ "Revision", "UINT" ],
		[ "DedicatedVideoMemory", "SIZE_T" ],
		[ "DedicatedSystemMemory", "SIZE_T" ],
		[ "SharedSystemMemory", "SIZE_T" ],
		[ "AdapterLuid", "LUID" ],
	];

	CreateWindowsTuple
	(
		"DXGI_ADAPTER_DESC",
		items,
		0,
		TypeFlags_NoPointers
	);
}





// DXGI_SWAP_CHAIN_DESC
{
	let items =
	[
		[ "BufferDesc", "DXGI_MODE_DESC" ],
		[ "SampleDesc", "DXGI_SAMPLE_DESC" ],
		[ "BufferUsage", "DXGI_USAGE" ],
		[ "BufferCount", "UINT" ],
		[ "_(4)", "" ],
		[ "OutputWindow", "HWND" ],
		[ "Windowed", "BOOL" ],
		[ "SwapEffect", "DXGI_SWAP_EFFECT" ],
		[ "Flags", "UINT" ],
		[ "_(4)", "" ],
	];

	CreateWindowsTuple
	(
		"DXGI_SWAP_CHAIN_DESC",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// DXGI_FRAME_STATISTICS
{
	let items =
	[
		[ "PresentCount", "UINT" ],
		[ "PresentRefreshCount", "UINT" ],
		[ "SyncRefreshCount", "UINT" ],
		[ "_(4)", "" ],
		[ "SyncQPCTime", "LARGE_INTEGER" ],
		[ "SyncGPUTime", "LARGE_INTEGER" ],
	];

	CreateWindowsTuple
	(
		"DXGI_FRAME_STATISTICS",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// DXGI_RGB
{
	let items =
	[
		[ "Red", "float" ],
		[ "Green", "float" ],
		[ "Blue", "float" ],
	];

	CreateWindowsTuple
	(
		"DXGI_RGB",
		items,
		0,
		TypeFlags_NoPointers
	);
}

// D3DCOLORVALUE
{
	let items =
	[
		[ "r", "float" ],
		[ "g", "float" ],
		[ "b", "float" ],
		[ "a", "float" ],
	];

	CreateWindowsTuple
	(
		"D3DCOLORVALUE",
		items,
		0,
		TypeFlags_NoPointers
	);
}

CreateWindowsTypedef
(
	"DXGI_RGBA",
	"D3DCOLORVALUE",
	16,
	TypeFlags_NoPointers
);


// DXGI_GAMMA_CONTROL
{
	let items =
	[
		[ "Scale", "DXGI_RGB" ],
		[ "Offset", "DXGI_RGB" ],
		[ "GammaCurve[1025]", "DXGI_RGB" ],
	];

	CreateWindowsTuple
	(
		"DXGI_GAMMA_CONTROL",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// DXGI_GAMMA_CONTROL_CAPABILITIES
{
	let items =
	[
		[ "ScaleAndOffsetSupported", "BOOL" ],
		[ "MaxConvertedValue", "float" ],
		[ "MinConvertedValue", "float" ],
		[ "NumGammaControlPoints", "UINT" ],
		[ "ControlPointPositions[1025]", "float" ],
	];

	CreateWindowsTuple
	(
		"DXGI_GAMMA_CONTROL_CAPABILITIES",
		items,
		0,
		TypeFlags_NoPointers
	);
}

// DXGI_OUTPUT_DESC
{
	let items =
	[
		[ "DeviceName[32]", "WCHAR" ],
		[ "DesktopCoordinates", "RECT" ],
		[ "AttachedToDesktop", "BOOL" ],
		[ "Rotation", "DXGI_MODE_ROTATION" ],
		[ "Monitor", "HMONITOR" ],
	];

	CreateWindowsTuple
	(
		"DXGI_OUTPUT_DESC",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// DXGI_SHARED_RESOURCE
{
	let items =
	[
		[ "Handle", "HANDLE" ],
	];

	CreateWindowsTuple
	(
		"DXGI_SHARED_RESOURCE",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// DXGI_ADAPTER_DESC1
{
	let items =
	[
		[ "Description[128]", "WCHAR" ],
		[ "VendorId", "UINT" ],
		[ "DeviceId", "UINT" ],
		[ "SubSysId", "UINT" ],
		[ "Revision", "UINT" ],
		[ "DedicatedVideoMemory", "SIZE_T" ],
		[ "DedicatedSystemMemory", "SIZE_T" ],
		[ "SharedSystemMemory", "SIZE_T" ],
		[ "AdapterLuid", "LUID" ],
		[ "Flags", "UINT" ],
		[ "_(4)", "" ],
	];

	CreateWindowsTuple
	(
		"DXGI_ADAPTER_DESC1",
		items,
		0,
		TypeFlags_NoPointers
	);
}











c += Tabs() + "#pragma pack(pop)" + NEW_LINE;
c += NEW_LINE;

// Functions
{
	c += Tabs() + "extern \"C\"" + NEW_LINE;

	ScopeStart();

	let items =
	[
	];

	CreateFunctions(items);

	ScopeEnd();
}

c += NEW_LINE;

// Function Tuples



// IDXGIObject
{
	let items =
	[
		[ "SetPrivateData", "HRESULT",
			[
				[ "Name", "const GUID&" ],
				[ "DataSize", "UINT" ],
				[ "pData", "const void*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "SetPrivateDataInterface", "HRESULT",
			[
				[ "Name", "const GUID&" ],
				[ "pUnknown", "const IUnknown*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetPrivateData", "HRESULT",
			[
				[ "Name", "const GUID&" ],
				[ "pDataSize", "UINT*" ],
				[ "pData", "void*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetParent", "HRESULT",
			[
				[ "riid", "const IID&" ],
				[ "ppParent", "void**" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"IDXGIObject : IUnknown",
		items,
		[ "novtable" ]
	);
}






// IDXGIDeviceSubObject
{
	let items =
	[
		[ "GetDevice", "HRESULT",
			[
				[ "riid", "const IID&" ],
				[ "ppDevice", "void**" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"IDXGIDeviceSubObject : IDXGIObject",
		items,
		[ "novtable" ]
	);
}





// IDXGIResource
{
	let items =
	[
		[ "GetSharedHandle", "HRESULT",
			[
				[ "pSharedHandle", "HANDLE*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetUsage", "HRESULT",
			[
				[ "pUsage", "DXGI_USAGE*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "SetEvictionPriority", "HRESULT",
			[
				[ "EvictionPriority", "UINT" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetEvictionPriority", "HRESULT",
			[
				[ "pEvictionPriority", "UINT*" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"IDXGIResource : IDXGIDeviceSubObject",
		items,
		[ "novtable" ]
	);
}






// IDXGIKeyedMutex
{
	let items =
	[
		[ "AcquireSync", "HRESULT",
			[
				[ "Key", "UINT64" ],
				[ "dwMilliseconds", "DWORD" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "ReleaseSync", "HRESULT",
			[
				[ "Key", "UINT64" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"IDXGIKeyedMutex : IDXGIDeviceSubObject",
		items,
		[ "novtable" ]
	);
}








// IDXGISurface
{
	let items =
	[
		[ "GetDesc", "HRESULT",
			[
				[ "pDesc", "DXGI_SURFACE_DESC*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "Map", "HRESULT",
			[
				[ "pLockedRect", "DXGI_MAPPED_RECT*" ],
				[ "MapFlags", "UINT" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "Unmap", "HRESULT",
			[
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"IDXGISurface : IDXGIDeviceSubObject",
		items,
		[ "novtable" ]
	);
}















// IDXGISurface1
{
	let items =
	[
		[ "GetDC", "HRESULT",
			[
				[ "Discard", "BOOL" ],
				[ "phdc", "HDC*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "ReleaseDC", "HRESULT",
			[
				[ "pDirtyRect", "RECT*" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"IDXGISurface1 : IDXGISurface",
		items,
		[ "novtable" ]
	);
}













// IDXGIAdapter
{
	let items =
	[
		[ "EnumOutputs", "HRESULT",
			[
				[ "Output", "UINT" ],
				[ "ppOutput", "IDXGIOutput**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetDesc", "HRESULT",
			[
				[ "pDesc", "DXGI_ADAPTER_DESC*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CheckInterfaceSupport", "HRESULT",
			[
				[ "InterfaceName", "const GUID&" ],
				[ "pUMDVersion", "LARGE_INTEGER*" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"IDXGIAdapter : IDXGIObject",
		items,
		[ "novtable" ]
	);
}
















// IDXGIOutput
{
	let items =
	[
		[ "GetDesc", "HRESULT",
			[
				[ "pDesc", "DXGI_OUTPUT_DESC*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetDisplayModeList", "HRESULT",
			[
				[ "EnumFormat", "DXGI_FORMAT" ],
				[ "Flags", "UINT" ],
				[ "pNumModes", "UINT*" ],
				[ "pDesc", "DXGI_MODE_DESC*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "FindClosestMatchingMode", "HRESULT",
			[
				[ "pModeToMatch", "const DXGI_MODE_DESC*" ],
				[ "pClosestMatch", "DXGI_MODE_DESC*" ],
				[ "pConcernedDevice", "IUnknown*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "WaitForVBlank", "HRESULT",
			[
			],
			FunctionFlags_PureVirtual
		],
		[ "TakeOwnership", "HRESULT",
			[
				[ "pDevice", "IUnknown*" ],
				[ "Exclusive", "BOOL" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "ReleaseOwnership", "void",
			[
			],
			FunctionFlags_PureVirtual
		],
		[ "GetGammaControlCapabilities", "HRESULT",
			[
				[ "pGammaCaps", "DXGI_GAMMA_CONTROL_CAPABILITIES*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "SetGammaControl", "HRESULT",
			[
				[ "pArray", "const DXGI_GAMMA_CONTROL*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetGammaControl", "HRESULT",
			[
				[ "pArray", "DXGI_GAMMA_CONTROL*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "SetDisplaySurface", "HRESULT",
			[
				[ "pScanoutSurface", "IDXGISurface*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetDisplaySurfaceData", "HRESULT",
			[
				[ "pDestination", "IDXGISurface*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetFrameStatistics", "HRESULT",
			[
				[ "pStats", "DXGI_FRAME_STATISTICS*" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"IDXGIOutput : IDXGIObject",
		items,
		[ "novtable" ]
	);
}












// IDXGISwapChain
{
	let items =
	[
		[ "Present", "HRESULT",
			[
				[ "SyncInterval", "UINT" ],
				[ "Flags", "UINT" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetBuffer", "HRESULT",
			[
				[ "Buffer", "UINT" ],
				[ "riid", "const IID&" ],
				[ "ppSurface", "void**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "SetFullscreenState", "HRESULT",
			[
				[ "Fullscreen", "BOOL" ],
				[ "pTarget", "IDXGIOutput*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetFullscreenState", "HRESULT",
			[
				[ "pFullscreen", "BOOL*" ],
				[ "ppTarget", "IDXGIOutput**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetDesc", "HRESULT",
			[
				[ "pDesc", "DXGI_SWAP_CHAIN_DESC*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "ResizeBuffers", "HRESULT",
			[
				[ "BufferCount", "UINT" ],
				[ "Width", "UINT" ],
				[ "Height", "UINT" ],
				[ "NewFormat", "DXGI_FORMAT" ],
				[ "SwapChainFlags", "UINT" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "ResizeTarget", "HRESULT",
			[
				[ "pNewTargetParameters", "const DXGI_MODE_DESC*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetContainingOutput", "HRESULT",
			[
				[ "ppOutput", "IDXGIOutput**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetFrameStatistics", "HRESULT",
			[
				[ "pStats", "DXGI_FRAME_STATISTICS*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetLastPresentCount", "HRESULT",
			[
				[ "pLastPresentCount", "UINT*" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"IDXGISwapChain : IDXGIDeviceSubObject",
		items,
		[ "novtable" ]
	);
}






// IDXGIFactory
{
	let items =
	[
		[ "EnumAdapters", "HRESULT",
			[
				[ "Adapter", "UINT" ],
				[ "ppAdapter", "IDXGIAdapter**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "MakeWindowAssociation", "HRESULT",
			[
				[ "WindowHandle", "HWND" ],
				[ "Flags", "UINT" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetWindowAssociation", "HRESULT",
			[
				[ "pWindowHandle", "HWND*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CreateSwapChain", "HRESULT",
			[
				[ "pDevice", "IUnknown*" ],
				[ "pDesc", "DXGI_SWAP_CHAIN_DESC*" ],
				[ "ppSwapChain", "IDXGISwapChain**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CreateSoftwareAdapter", "HRESULT",
			[
				[ "Module", "HMODULE" ],
				[ "ppAdapter", "IDXGIAdapter**" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"IDXGIFactory : IDXGIObject",
		items,
		[ "novtable" ]
	);
}













// IDXGIDevice
{
	let items =
	[
		[ "GetAdapter", "HRESULT",
			[
				[ "pAdapter", "IDXGIAdapter**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CreateSurface", "HRESULT",
			[
				[ "pDesc", "const DXGI_SURFACE_DESC*" ],
				[ "NumSurfaces", "UINT" ],
				[ "Usage", "DXGI_USAGE" ],
				[ "pSharedResource", "const DXGI_SHARED_RESOURCE*" ],
				[ "ppSurface", "IDXGISurface**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "QueryResourceResidency", "HRESULT",
			[
				[ "ppResources", "IUnknown*const*" ],
				[ "pResidencyStatus", "DXGI_RESIDENCY*" ],
				[ "NumResources", "UINT" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "SetGPUThreadPriority", "HRESULT",
			[
				[ "Priority", "INT" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetGPUThreadPriority", "HRESULT",
			[
				[ "pPriority", "INT*" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"IDXGIDevice : IDXGIObject",
		items,
		[ "novtable" ]
	);
}











// IDXGIFactory1
{
	let items =
	[
		[ "EnumAdapters1", "HRESULT",
			[
				[ "Adapter", "UINT" ],
				[ "ppAdapter", "IDXGIAdapter1**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "IsCurrent", "BOOL",
			[
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"IDXGIFactory1 : IDXGIFactory",
		items,
		[ "novtable" ]
	);
}












// IDXGIAdapter1
{
	let items =
	[
		[ "GetDesc1", "HRESULT",
			[
				[ "pDesc", "DXGI_ADAPTER_DESC1*" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"IDXGIAdapter1 : IDXGIAdapter",
		items,
		[ "novtable" ]
	);
}











// IDXGIDevice1
{
	let items =
	[
		[ "SetMaximumFrameLatency", "HRESULT",
			[
				[ "MaxLatency", "UINT" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetMaximumFrameLatency", "HRESULT",
			[
				[ "pMaxLatency", "UINT*" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"IDXGIDevice1 : IDXGIDevice",
		items,
		[ "novtable" ]
	);
}







/*






*/











c += NEW_LINE;

ModuleEnd();

CleanStream();

fs.writeFileSync("../Core/DXGI.ixx", c);

// Verify

ModuleVerify();

CleanStream();

fs.writeFileSync("../verifyDXGI.cpp", c);

ClearAll();
}

// #endregion

// #region D3D11
{
console.log("D3D11");

ModuleStart
(
	"D3D11",
	[
		"Windows",
		"DXGI"
	],
	[
		"Windows",
		"DXGI"
	]
);



// Forward Declarations

{
	let names =
	[
		"ID3D11DeviceChild",
		"ID3D11DepthStencilState",
		"ID3D11BlendState",
		"ID3D11RasterizerState",
		"ID3D11Resource",
		"ID3D11Buffer",
		"ID3D11Texture1D",
		"ID3D11Texture2D",
		"ID3D11Texture3D",
		"ID3D11View",
		"ID3D11ShaderResourceView",
		"ID3D11RenderTargetView",
		"ID3D11DepthStencilView",
		"ID3D11UnorderedAccessView",
		"ID3D11VertexShader",
		"ID3D11HullShader",
		"ID3D11DomainShader",
		"ID3D11GeometryShader",
		"ID3D11PixelShader",
		"ID3D11ComputeShader",
		"ID3D11InputLayout",
		"ID3D11SamplerState",
		"ID3D11Asynchronous",
		"ID3D11Query",
		"ID3D11Predicate",
		"ID3D11Counter",
		"ID3D11ClassInstance",
		"ID3D11ClassLinkage",
		"ID3D11CommandList",
		"ID3D11DeviceContext",
		"ID3D11VideoDecoder",
		"ID3D11VideoProcessorEnumerator",
		"ID3D11VideoProcessor",
		"ID3D11AuthenticatedChannel",
		"ID3D11CryptoSession",
		"ID3D11VideoDecoderOutputView",
		"ID3D11VideoProcessorInputView",
		"ID3D11VideoProcessorOutputView",
		"ID3D11VideoContext",
		"ID3D11VideoDevice",
		"ID3D11Device",
		"ID3D10Blob",
		"ID3DDestructionNotifier",
	];

	CreateForwardDeclarations
	(
		names,
		"struct"
	);

	CreateForwardDeclarations
	(
		names,
		"const IID",
		"extern \"C\" ",
		"IID_"
	);
}














// Types
{
	let items =
	[
		[ "D3D11_RECT", "RECT", 16, TypeFlags_NoPointers ],
	];

	CreateWindowsTypedefs(items);
}






// Function Types
{
	let items =
	[
	];

	CreateWindowsFunctionTypedefs(items);
}

// Enums






{
	let items =
	[
		[ "D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE", "16", "" ],
	];

	CreateWindowsEnum
	(
		"",
		items
	);
}



/*








*/




















// D3D_DRIVER_TYPE
{
	let items =
	[
		[ "D3D_DRIVER_TYPE_UNKNOWN", "0", "" ],
		[ "D3D_DRIVER_TYPE_HARDWARE", "(D3D_DRIVER_TYPE_UNKNOWN+1)", "" ],
		[ "D3D_DRIVER_TYPE_REFERENCE", "(D3D_DRIVER_TYPE_HARDWARE+1)", "" ],
		[ "D3D_DRIVER_TYPE_NULL", "(D3D_DRIVER_TYPE_REFERENCE+1)", "" ],
		[ "D3D_DRIVER_TYPE_SOFTWARE", "(D3D_DRIVER_TYPE_NULL+1)", "" ],
		[ "D3D_DRIVER_TYPE_WARP", "(D3D_DRIVER_TYPE_SOFTWARE+1)", "" ],
	];

	CreateWindowsEnum
	(
		"D3D_DRIVER_TYPE",
		items
	);
}

// D3D_FEATURE_LEVEL
{
	let items =
	[
		[ "D3D_FEATURE_LEVEL_1_0_CORE", "0x1000", "" ],
		[ "D3D_FEATURE_LEVEL_9_1", "0x9100", "" ],
		[ "D3D_FEATURE_LEVEL_9_2", "0x9200", "" ],
		[ "D3D_FEATURE_LEVEL_9_3", "0x9300", "" ],
		[ "D3D_FEATURE_LEVEL_10_0", "0xa000", "" ],
		[ "D3D_FEATURE_LEVEL_10_1", "0xa100", "" ],
		[ "D3D_FEATURE_LEVEL_11_0", "0xb000", "" ],
		[ "D3D_FEATURE_LEVEL_11_1", "0xb100", "" ],
		[ "D3D_FEATURE_LEVEL_12_0", "0xc000", "" ],
		[ "D3D_FEATURE_LEVEL_12_1", "0xc100", "" ],
	];

	CreateWindowsEnum
	(
		"D3D_FEATURE_LEVEL",
		items
	);
}


// D3D_PRIMITIVE_TOPOLOGY
{
	let items =
	[
		[ "D3D_PRIMITIVE_TOPOLOGY_UNDEFINED", "0", "" ],
		[ "D3D_PRIMITIVE_TOPOLOGY_POINTLIST", "1", "" ],
		[ "D3D_PRIMITIVE_TOPOLOGY_LINELIST", "2", "" ],
		[ "D3D_PRIMITIVE_TOPOLOGY_LINESTRIP", "3", "" ],
		[ "D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST", "4", "" ],
		[ "D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP", "5", "" ],
		[ "D3D_PRIMITIVE_TOPOLOGY_LINELIST_ADJ", "10", "" ],
		[ "D3D_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ", "11", "" ],
		[ "D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ", "12", "" ],
		[ "D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ", "13", "" ],
		[ "D3D_PRIMITIVE_TOPOLOGY_1_CONTROL_POINT_PATCHLIST", "33", "" ],
		[ "D3D_PRIMITIVE_TOPOLOGY_2_CONTROL_POINT_PATCHLIST", "34", "" ],
		[ "D3D_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST", "35", "" ],
		[ "D3D_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST", "36", "" ],
		[ "D3D_PRIMITIVE_TOPOLOGY_5_CONTROL_POINT_PATCHLIST", "37", "" ],
		[ "D3D_PRIMITIVE_TOPOLOGY_6_CONTROL_POINT_PATCHLIST", "38", "" ],
		[ "D3D_PRIMITIVE_TOPOLOGY_7_CONTROL_POINT_PATCHLIST", "39", "" ],
		[ "D3D_PRIMITIVE_TOPOLOGY_8_CONTROL_POINT_PATCHLIST", "40", "" ],
		[ "D3D_PRIMITIVE_TOPOLOGY_9_CONTROL_POINT_PATCHLIST", "41", "" ],
		[ "D3D_PRIMITIVE_TOPOLOGY_10_CONTROL_POINT_PATCHLIST", "42", "" ],
		[ "D3D_PRIMITIVE_TOPOLOGY_11_CONTROL_POINT_PATCHLIST", "43", "" ],
		[ "D3D_PRIMITIVE_TOPOLOGY_12_CONTROL_POINT_PATCHLIST", "44", "" ],
		[ "D3D_PRIMITIVE_TOPOLOGY_13_CONTROL_POINT_PATCHLIST", "45", "" ],
		[ "D3D_PRIMITIVE_TOPOLOGY_14_CONTROL_POINT_PATCHLIST", "46", "" ],
		[ "D3D_PRIMITIVE_TOPOLOGY_15_CONTROL_POINT_PATCHLIST", "47", "" ],
		[ "D3D_PRIMITIVE_TOPOLOGY_16_CONTROL_POINT_PATCHLIST", "48", "" ],
		[ "D3D_PRIMITIVE_TOPOLOGY_17_CONTROL_POINT_PATCHLIST", "49", "" ],
		[ "D3D_PRIMITIVE_TOPOLOGY_18_CONTROL_POINT_PATCHLIST", "50", "" ],
		[ "D3D_PRIMITIVE_TOPOLOGY_19_CONTROL_POINT_PATCHLIST", "51", "" ],
		[ "D3D_PRIMITIVE_TOPOLOGY_20_CONTROL_POINT_PATCHLIST", "52", "" ],
		[ "D3D_PRIMITIVE_TOPOLOGY_21_CONTROL_POINT_PATCHLIST", "53", "" ],
		[ "D3D_PRIMITIVE_TOPOLOGY_22_CONTROL_POINT_PATCHLIST", "54", "" ],
		[ "D3D_PRIMITIVE_TOPOLOGY_23_CONTROL_POINT_PATCHLIST", "55", "" ],
		[ "D3D_PRIMITIVE_TOPOLOGY_24_CONTROL_POINT_PATCHLIST", "56", "" ],
		[ "D3D_PRIMITIVE_TOPOLOGY_25_CONTROL_POINT_PATCHLIST", "57", "" ],
		[ "D3D_PRIMITIVE_TOPOLOGY_26_CONTROL_POINT_PATCHLIST", "58", "" ],
		[ "D3D_PRIMITIVE_TOPOLOGY_27_CONTROL_POINT_PATCHLIST", "59", "" ],
		[ "D3D_PRIMITIVE_TOPOLOGY_28_CONTROL_POINT_PATCHLIST", "60", "" ],
		[ "D3D_PRIMITIVE_TOPOLOGY_29_CONTROL_POINT_PATCHLIST", "61", "" ],
		[ "D3D_PRIMITIVE_TOPOLOGY_30_CONTROL_POINT_PATCHLIST", "62", "" ],
		[ "D3D_PRIMITIVE_TOPOLOGY_31_CONTROL_POINT_PATCHLIST", "63", "" ],
		[ "D3D_PRIMITIVE_TOPOLOGY_32_CONTROL_POINT_PATCHLIST", "64", "" ],
	];

	CreateWindowsEnum
	(
		"D3D_PRIMITIVE_TOPOLOGY",
		items
	);
}


// D3D10_PRIMITIVE_TOPOLOGY
{
	let items =
	[
		[ "D3D10_PRIMITIVE_TOPOLOGY_UNDEFINED", "D3D_PRIMITIVE_TOPOLOGY_UNDEFINED", "" ],
		[ "D3D10_PRIMITIVE_TOPOLOGY_POINTLIST", "D3D_PRIMITIVE_TOPOLOGY_POINTLIST", "" ],
		[ "D3D10_PRIMITIVE_TOPOLOGY_LINELIST", "D3D_PRIMITIVE_TOPOLOGY_LINELIST", "" ],
		[ "D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP", "D3D_PRIMITIVE_TOPOLOGY_LINESTRIP", "" ],
		[ "D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST", "D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST", "" ],
		[ "D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP", "D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP", "" ],
		[ "D3D10_PRIMITIVE_TOPOLOGY_LINELIST_ADJ", "D3D_PRIMITIVE_TOPOLOGY_LINELIST_ADJ", "" ],
		[ "D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ", "D3D_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ", "" ],
		[ "D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ", "D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ", "" ],
		[ "D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ", "D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ", "" ],
	];

	CreateWindowsEnum
	(
		"D3D10_PRIMITIVE_TOPOLOGY",
		items
	);
}


// D3D11_PRIMITIVE_TOPOLOGY
{
	let items =
	[
		[ "D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED", "D3D_PRIMITIVE_TOPOLOGY_UNDEFINED", "" ],
		[ "D3D11_PRIMITIVE_TOPOLOGY_POINTLIST", "D3D_PRIMITIVE_TOPOLOGY_POINTLIST", "" ],
		[ "D3D11_PRIMITIVE_TOPOLOGY_LINELIST", "D3D_PRIMITIVE_TOPOLOGY_LINELIST", "" ],
		[ "D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP", "D3D_PRIMITIVE_TOPOLOGY_LINESTRIP", "" ],
		[ "D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST", "D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST", "" ],
		[ "D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP", "D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP", "" ],
		[ "D3D11_PRIMITIVE_TOPOLOGY_LINELIST_ADJ", "D3D_PRIMITIVE_TOPOLOGY_LINELIST_ADJ", "" ],
		[ "D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ", "D3D_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ", "" ],
		[ "D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ", "D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ", "" ],
		[ "D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ", "D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ", "" ],
		[ "D3D11_PRIMITIVE_TOPOLOGY_1_CONTROL_POINT_PATCHLIST", "D3D_PRIMITIVE_TOPOLOGY_1_CONTROL_POINT_PATCHLIST", "" ],
		[ "D3D11_PRIMITIVE_TOPOLOGY_2_CONTROL_POINT_PATCHLIST", "D3D_PRIMITIVE_TOPOLOGY_2_CONTROL_POINT_PATCHLIST", "" ],
		[ "D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST", "D3D_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST", "" ],
		[ "D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST", "D3D_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST", "" ],
		[ "D3D11_PRIMITIVE_TOPOLOGY_5_CONTROL_POINT_PATCHLIST", "D3D_PRIMITIVE_TOPOLOGY_5_CONTROL_POINT_PATCHLIST", "" ],
		[ "D3D11_PRIMITIVE_TOPOLOGY_6_CONTROL_POINT_PATCHLIST", "D3D_PRIMITIVE_TOPOLOGY_6_CONTROL_POINT_PATCHLIST", "" ],
		[ "D3D11_PRIMITIVE_TOPOLOGY_7_CONTROL_POINT_PATCHLIST", "D3D_PRIMITIVE_TOPOLOGY_7_CONTROL_POINT_PATCHLIST", "" ],
		[ "D3D11_PRIMITIVE_TOPOLOGY_8_CONTROL_POINT_PATCHLIST", "D3D_PRIMITIVE_TOPOLOGY_8_CONTROL_POINT_PATCHLIST", "" ],
		[ "D3D11_PRIMITIVE_TOPOLOGY_9_CONTROL_POINT_PATCHLIST", "D3D_PRIMITIVE_TOPOLOGY_9_CONTROL_POINT_PATCHLIST", "" ],
		[ "D3D11_PRIMITIVE_TOPOLOGY_10_CONTROL_POINT_PATCHLIST", "D3D_PRIMITIVE_TOPOLOGY_10_CONTROL_POINT_PATCHLIST", "" ],
		[ "D3D11_PRIMITIVE_TOPOLOGY_11_CONTROL_POINT_PATCHLIST", "D3D_PRIMITIVE_TOPOLOGY_11_CONTROL_POINT_PATCHLIST", "" ],
		[ "D3D11_PRIMITIVE_TOPOLOGY_12_CONTROL_POINT_PATCHLIST", "D3D_PRIMITIVE_TOPOLOGY_12_CONTROL_POINT_PATCHLIST", "" ],
		[ "D3D11_PRIMITIVE_TOPOLOGY_13_CONTROL_POINT_PATCHLIST", "D3D_PRIMITIVE_TOPOLOGY_13_CONTROL_POINT_PATCHLIST", "" ],
		[ "D3D11_PRIMITIVE_TOPOLOGY_14_CONTROL_POINT_PATCHLIST", "D3D_PRIMITIVE_TOPOLOGY_14_CONTROL_POINT_PATCHLIST", "" ],
		[ "D3D11_PRIMITIVE_TOPOLOGY_15_CONTROL_POINT_PATCHLIST", "D3D_PRIMITIVE_TOPOLOGY_15_CONTROL_POINT_PATCHLIST", "" ],
		[ "D3D11_PRIMITIVE_TOPOLOGY_16_CONTROL_POINT_PATCHLIST", "D3D_PRIMITIVE_TOPOLOGY_16_CONTROL_POINT_PATCHLIST", "" ],
		[ "D3D11_PRIMITIVE_TOPOLOGY_17_CONTROL_POINT_PATCHLIST", "D3D_PRIMITIVE_TOPOLOGY_17_CONTROL_POINT_PATCHLIST", "" ],
		[ "D3D11_PRIMITIVE_TOPOLOGY_18_CONTROL_POINT_PATCHLIST", "D3D_PRIMITIVE_TOPOLOGY_18_CONTROL_POINT_PATCHLIST", "" ],
		[ "D3D11_PRIMITIVE_TOPOLOGY_19_CONTROL_POINT_PATCHLIST", "D3D_PRIMITIVE_TOPOLOGY_19_CONTROL_POINT_PATCHLIST", "" ],
		[ "D3D11_PRIMITIVE_TOPOLOGY_20_CONTROL_POINT_PATCHLIST", "D3D_PRIMITIVE_TOPOLOGY_20_CONTROL_POINT_PATCHLIST", "" ],
		[ "D3D11_PRIMITIVE_TOPOLOGY_21_CONTROL_POINT_PATCHLIST", "D3D_PRIMITIVE_TOPOLOGY_21_CONTROL_POINT_PATCHLIST", "" ],
		[ "D3D11_PRIMITIVE_TOPOLOGY_22_CONTROL_POINT_PATCHLIST", "D3D_PRIMITIVE_TOPOLOGY_22_CONTROL_POINT_PATCHLIST", "" ],
		[ "D3D11_PRIMITIVE_TOPOLOGY_23_CONTROL_POINT_PATCHLIST", "D3D_PRIMITIVE_TOPOLOGY_23_CONTROL_POINT_PATCHLIST", "" ],
		[ "D3D11_PRIMITIVE_TOPOLOGY_24_CONTROL_POINT_PATCHLIST", "D3D_PRIMITIVE_TOPOLOGY_24_CONTROL_POINT_PATCHLIST", "" ],
		[ "D3D11_PRIMITIVE_TOPOLOGY_25_CONTROL_POINT_PATCHLIST", "D3D_PRIMITIVE_TOPOLOGY_25_CONTROL_POINT_PATCHLIST", "" ],
		[ "D3D11_PRIMITIVE_TOPOLOGY_26_CONTROL_POINT_PATCHLIST", "D3D_PRIMITIVE_TOPOLOGY_26_CONTROL_POINT_PATCHLIST", "" ],
		[ "D3D11_PRIMITIVE_TOPOLOGY_27_CONTROL_POINT_PATCHLIST", "D3D_PRIMITIVE_TOPOLOGY_27_CONTROL_POINT_PATCHLIST", "" ],
		[ "D3D11_PRIMITIVE_TOPOLOGY_28_CONTROL_POINT_PATCHLIST", "D3D_PRIMITIVE_TOPOLOGY_28_CONTROL_POINT_PATCHLIST", "" ],
		[ "D3D11_PRIMITIVE_TOPOLOGY_29_CONTROL_POINT_PATCHLIST", "D3D_PRIMITIVE_TOPOLOGY_29_CONTROL_POINT_PATCHLIST", "" ],
		[ "D3D11_PRIMITIVE_TOPOLOGY_30_CONTROL_POINT_PATCHLIST", "D3D_PRIMITIVE_TOPOLOGY_30_CONTROL_POINT_PATCHLIST", "" ],
		[ "D3D11_PRIMITIVE_TOPOLOGY_31_CONTROL_POINT_PATCHLIST", "D3D_PRIMITIVE_TOPOLOGY_31_CONTROL_POINT_PATCHLIST", "" ],
		[ "D3D11_PRIMITIVE_TOPOLOGY_32_CONTROL_POINT_PATCHLIST", "D3D_PRIMITIVE_TOPOLOGY_32_CONTROL_POINT_PATCHLIST", "" ],
	];

	CreateWindowsEnum
	(
		"D3D11_PRIMITIVE_TOPOLOGY",
		items
	);
}


// D3D11_RESOURCE_DIMENSION
{
	let items =
	[
		[ "D3D11_RESOURCE_DIMENSION_UNKNOWN", "0", "" ],
		[ "D3D11_RESOURCE_DIMENSION_BUFFER", "1", "" ],
		[ "D3D11_RESOURCE_DIMENSION_TEXTURE1D", "2", "" ],
		[ "D3D11_RESOURCE_DIMENSION_TEXTURE2D", "3", "" ],
		[ "D3D11_RESOURCE_DIMENSION_TEXTURE3D", "4", "" ],
	];

	CreateWindowsEnum
	(
		"D3D11_RESOURCE_DIMENSION",
		items
	);
}



// D3D11_DSV_DIMENSION
{
	let items =
	[
		[ "D3D11_DSV_DIMENSION_UNKNOWN", "0", "" ],
		[ "D3D11_DSV_DIMENSION_TEXTURE1D", "1", "" ],
		[ "D3D11_DSV_DIMENSION_TEXTURE1DARRAY", "2", "" ],
		[ "D3D11_DSV_DIMENSION_TEXTURE2D", "3", "" ],
		[ "D3D11_DSV_DIMENSION_TEXTURE2DARRAY", "4", "" ],
		[ "D3D11_DSV_DIMENSION_TEXTURE2DMS", "5", "" ],
		[ "D3D11_DSV_DIMENSION_TEXTURE2DMSARRAY", "6", "" ],
	];

	CreateWindowsEnum
	(
		"D3D11_DSV_DIMENSION",
		items
	);
}



// D3D11_RTV_DIMENSION
{
	let items =
	[
		[ "D3D11_RTV_DIMENSION_UNKNOWN", "0", "" ],
		[ "D3D11_RTV_DIMENSION_BUFFER", "1", "" ],
		[ "D3D11_RTV_DIMENSION_TEXTURE1D", "2", "" ],
		[ "D3D11_RTV_DIMENSION_TEXTURE1DARRAY", "3", "" ],
		[ "D3D11_RTV_DIMENSION_TEXTURE2D", "4", "" ],
		[ "D3D11_RTV_DIMENSION_TEXTURE2DARRAY", "5", "" ],
		[ "D3D11_RTV_DIMENSION_TEXTURE2DMS", "6", "" ],
		[ "D3D11_RTV_DIMENSION_TEXTURE2DMSARRAY", "7", "" ],
		[ "D3D11_RTV_DIMENSION_TEXTURE3D", "8", "" ],
	];

	CreateWindowsEnum
	(
		"D3D11_RTV_DIMENSION",
		items
	);
}


// D3D11_UAV_DIMENSION
{
	let items =
	[
		[ "D3D11_UAV_DIMENSION_UNKNOWN", "0", "" ],
		[ "D3D11_UAV_DIMENSION_BUFFER", "1", "" ],
		[ "D3D11_UAV_DIMENSION_TEXTURE1D", "2", "" ],
		[ "D3D11_UAV_DIMENSION_TEXTURE1DARRAY", "3", "" ],
		[ "D3D11_UAV_DIMENSION_TEXTURE2D", "4", "" ],
		[ "D3D11_UAV_DIMENSION_TEXTURE2DARRAY", "5", "" ],
		[ "D3D11_UAV_DIMENSION_TEXTURE3D", "8", "" ],
	];

	CreateWindowsEnum
	(
		"D3D11_UAV_DIMENSION",
		items
	);
}



// D3D11_USAGE
{
	let items =
	[
		[ "D3D11_USAGE_DEFAULT", "0", "" ],
		[ "D3D11_USAGE_IMMUTABLE", "1", "" ],
		[ "D3D11_USAGE_DYNAMIC", "2", "" ],
		[ "D3D11_USAGE_STAGING", "3", "" ],
	];

	CreateWindowsEnum
	(
		"D3D11_USAGE",
		items
	);
}


// D3D_SRV_DIMENSION
{
	let items =
	[
		[ "D3D_SRV_DIMENSION_UNKNOWN", "0", "" ],
		[ "D3D_SRV_DIMENSION_BUFFER", "1", "" ],
		[ "D3D_SRV_DIMENSION_TEXTURE1D", "2", "" ],
		[ "D3D_SRV_DIMENSION_TEXTURE1DARRAY", "3", "" ],
		[ "D3D_SRV_DIMENSION_TEXTURE2D", "4", "" ],
		[ "D3D_SRV_DIMENSION_TEXTURE2DARRAY", "5", "" ],
		[ "D3D_SRV_DIMENSION_TEXTURE2DMS", "6", "" ],
		[ "D3D_SRV_DIMENSION_TEXTURE2DMSARRAY", "7", "" ],
		[ "D3D_SRV_DIMENSION_TEXTURE3D", "8", "" ],
		[ "D3D_SRV_DIMENSION_TEXTURECUBE", "9", "" ],
		[ "D3D_SRV_DIMENSION_TEXTURECUBEARRAY", "10", "" ],
		[ "D3D_SRV_DIMENSION_BUFFEREX", "11", "" ],
	];

	CreateWindowsEnum
	(
		"D3D_SRV_DIMENSION",
		items
	);
}



// D3D10_SRV_DIMENSION
{
	let items =
	[
		[ "D3D10_SRV_DIMENSION_UNKNOWN", "D3D_SRV_DIMENSION_UNKNOWN", "" ],
		[ "D3D10_SRV_DIMENSION_BUFFER", "D3D_SRV_DIMENSION_BUFFER", "" ],
		[ "D3D10_SRV_DIMENSION_TEXTURE1D", "D3D_SRV_DIMENSION_TEXTURE1D", "" ],
		[ "D3D10_SRV_DIMENSION_TEXTURE1DARRAY", "D3D_SRV_DIMENSION_TEXTURE1DARRAY", "" ],
		[ "D3D10_SRV_DIMENSION_TEXTURE2D", "D3D_SRV_DIMENSION_TEXTURE2D", "" ],
		[ "D3D10_SRV_DIMENSION_TEXTURE2DARRAY", "D3D_SRV_DIMENSION_TEXTURE2DARRAY", "" ],
		[ "D3D10_SRV_DIMENSION_TEXTURE2DMS", "D3D_SRV_DIMENSION_TEXTURE2DMS", "" ],
		[ "D3D10_SRV_DIMENSION_TEXTURE2DMSARRAY", "D3D_SRV_DIMENSION_TEXTURE2DMSARRAY", "" ],
		[ "D3D10_SRV_DIMENSION_TEXTURE3D", "D3D_SRV_DIMENSION_TEXTURE3D", "" ],
		[ "D3D10_SRV_DIMENSION_TEXTURECUBE", "D3D_SRV_DIMENSION_TEXTURECUBE", "" ],
	];

	CreateWindowsEnum
	(
		"D3D10_SRV_DIMENSION",
		items
	);
}


// D3D10_1_SRV_DIMENSION
{
	let items =
	[
		[ "D3D10_1_SRV_DIMENSION_UNKNOWN", "D3D_SRV_DIMENSION_UNKNOWN", "" ],
		[ "D3D10_1_SRV_DIMENSION_BUFFER", "D3D_SRV_DIMENSION_BUFFER", "" ],
		[ "D3D10_1_SRV_DIMENSION_TEXTURE1D", "D3D_SRV_DIMENSION_TEXTURE1D", "" ],
		[ "D3D10_1_SRV_DIMENSION_TEXTURE1DARRAY", "D3D_SRV_DIMENSION_TEXTURE1DARRAY", "" ],
		[ "D3D10_1_SRV_DIMENSION_TEXTURE2D", "D3D_SRV_DIMENSION_TEXTURE2D", "" ],
		[ "D3D10_1_SRV_DIMENSION_TEXTURE2DARRAY", "D3D_SRV_DIMENSION_TEXTURE2DARRAY", "" ],
		[ "D3D10_1_SRV_DIMENSION_TEXTURE2DMS", "D3D_SRV_DIMENSION_TEXTURE2DMS", "" ],
		[ "D3D10_1_SRV_DIMENSION_TEXTURE2DMSARRAY", "D3D_SRV_DIMENSION_TEXTURE2DMSARRAY", "" ],
		[ "D3D10_1_SRV_DIMENSION_TEXTURE3D", "D3D_SRV_DIMENSION_TEXTURE3D", "" ],
		[ "D3D10_1_SRV_DIMENSION_TEXTURECUBE", "D3D_SRV_DIMENSION_TEXTURECUBE", "" ],
		[ "D3D10_1_SRV_DIMENSION_TEXTURECUBEARRAY", "D3D_SRV_DIMENSION_TEXTURECUBEARRAY", "" ],
	];

	CreateWindowsEnum
	(
		"D3D10_1_SRV_DIMENSION",
		items,
		EnumFlags_NoSizeAssert
	);
}


// D3D11_SRV_DIMENSION
{
	let items =
	[
		[ "D3D11_SRV_DIMENSION_UNKNOWN", "D3D_SRV_DIMENSION_UNKNOWN", "" ],
		[ "D3D11_SRV_DIMENSION_BUFFER", "D3D_SRV_DIMENSION_BUFFER", "" ],
		[ "D3D11_SRV_DIMENSION_TEXTURE1D", "D3D_SRV_DIMENSION_TEXTURE1D", "" ],
		[ "D3D11_SRV_DIMENSION_TEXTURE1DARRAY", "D3D_SRV_DIMENSION_TEXTURE1DARRAY", "" ],
		[ "D3D11_SRV_DIMENSION_TEXTURE2D", "D3D_SRV_DIMENSION_TEXTURE2D", "" ],
		[ "D3D11_SRV_DIMENSION_TEXTURE2DARRAY", "D3D_SRV_DIMENSION_TEXTURE2DARRAY", "" ],
		[ "D3D11_SRV_DIMENSION_TEXTURE2DMS", "D3D_SRV_DIMENSION_TEXTURE2DMS", "" ],
		[ "D3D11_SRV_DIMENSION_TEXTURE2DMSARRAY", "D3D_SRV_DIMENSION_TEXTURE2DMSARRAY", "" ],
		[ "D3D11_SRV_DIMENSION_TEXTURE3D", "D3D_SRV_DIMENSION_TEXTURE3D", "" ],
		[ "D3D11_SRV_DIMENSION_TEXTURECUBE", "D3D_SRV_DIMENSION_TEXTURECUBE", "" ],
		[ "D3D11_SRV_DIMENSION_TEXTURECUBEARRAY", "D3D_SRV_DIMENSION_TEXTURECUBEARRAY", "" ],
		[ "D3D11_SRV_DIMENSION_BUFFEREX", "D3D_SRV_DIMENSION_BUFFEREX", "" ],
	];

	CreateWindowsEnum
	(
		"D3D11_SRV_DIMENSION",
		items
	);
}


// D3D11_INPUT_CLASSIFICATION
{
	let items =
	[
		[ "D3D11_INPUT_PER_VERTEX_DATA", "0", "" ],
		[ "D3D11_INPUT_PER_INSTANCE_DATA", "1", "" ],
	];

	CreateWindowsEnum
	(
		"D3D11_INPUT_CLASSIFICATION",
		items
	);
}

// D3D11_BLEND
{
	let items =
	[
		[ "D3D11_BLEND_ZERO", "1", "" ],
		[ "D3D11_BLEND_ONE", "2", "" ],
		[ "D3D11_BLEND_SRC_COLOR", "3", "" ],
		[ "D3D11_BLEND_INV_SRC_COLOR", "4", "" ],
		[ "D3D11_BLEND_SRC_ALPHA", "5", "" ],
		[ "D3D11_BLEND_INV_SRC_ALPHA", "6", "" ],
		[ "D3D11_BLEND_DEST_ALPHA", "7", "" ],
		[ "D3D11_BLEND_INV_DEST_ALPHA", "8", "" ],
		[ "D3D11_BLEND_DEST_COLOR", "9", "" ],
		[ "D3D11_BLEND_INV_DEST_COLOR", "10", "" ],
		[ "D3D11_BLEND_SRC_ALPHA_SAT", "11", "" ],
		[ "D3D11_BLEND_BLEND_FACTOR", "14", "" ],
		[ "D3D11_BLEND_INV_BLEND_FACTOR", "15", "" ],
		[ "D3D11_BLEND_SRC1_COLOR", "16", "" ],
		[ "D3D11_BLEND_INV_SRC1_COLOR", "17", "" ],
		[ "D3D11_BLEND_SRC1_ALPHA", "18", "" ],
		[ "D3D11_BLEND_INV_SRC1_ALPHA", "19", "" ],
	];

	CreateWindowsEnum
	(
		"D3D11_BLEND",
		items
	);
}



// D3D11_BLEND_OP
{
	let items =
	[
		[ "D3D11_BLEND_OP_ADD", "1", "" ],
		[ "D3D11_BLEND_OP_SUBTRACT", "2", "" ],
		[ "D3D11_BLEND_OP_REV_SUBTRACT", "3", "" ],
		[ "D3D11_BLEND_OP_MIN", "4", "" ],
		[ "D3D11_BLEND_OP_MAX", "5", "" ],
	];

	CreateWindowsEnum
	(
		"D3D11_BLEND_OP",
		items
	);
}

// D3D11_COMPARISON_FUNC
{
	let items =
	[
		[ "D3D11_COMPARISON_NEVER", "1", "" ],
		[ "D3D11_COMPARISON_LESS", "2", "" ],
		[ "D3D11_COMPARISON_EQUAL", "3", "" ],
		[ "D3D11_COMPARISON_LESS_EQUAL", "4", "" ],
		[ "D3D11_COMPARISON_GREATER", "5", "" ],
		[ "D3D11_COMPARISON_NOT_EQUAL", "6", "" ],
		[ "D3D11_COMPARISON_GREATER_EQUAL", "7", "" ],
		[ "D3D11_COMPARISON_ALWAYS", "8", "" ],
	];

	CreateWindowsEnum
	(
		"D3D11_COMPARISON_FUNC",
		items
	);
}


// D3D11_DEPTH_WRITE_MASK
{
	let items =
	[
		[ "D3D11_DEPTH_WRITE_MASK_ZERO", "0", "" ],
		[ "D3D11_DEPTH_WRITE_MASK_ALL", "1", "" ],
	];

	CreateWindowsEnum
	(
		"D3D11_DEPTH_WRITE_MASK",
		items
	);
}


// D3D11_STENCIL_OP
{
	let items =
	[
		[ "D3D11_STENCIL_OP_KEEP", "1", "" ],
		[ "D3D11_STENCIL_OP_ZERO", "2", "" ],
		[ "D3D11_STENCIL_OP_REPLACE", "3", "" ],
		[ "D3D11_STENCIL_OP_INCR_SAT", "4", "" ],
		[ "D3D11_STENCIL_OP_DECR_SAT", "5", "" ],
		[ "D3D11_STENCIL_OP_INVERT", "6", "" ],
		[ "D3D11_STENCIL_OP_INCR", "7", "" ],
		[ "D3D11_STENCIL_OP_DECR", "8", "" ],
	];

	CreateWindowsEnum
	(
		"D3D11_STENCIL_OP",
		items
	);
}


// D3D11_FILL_MODE
{
	let items =
	[
		[ "D3D11_FILL_WIREFRAME", "2", "" ],
		[ "D3D11_FILL_SOLID", "3", "" ],
	];

	CreateWindowsEnum
	(
		"D3D11_FILL_MODE",
		items
	);
}


// D3D11_CULL_MODE
{
	let items =
	[
		[ "D3D11_CULL_NONE", "1", "" ],
		[ "D3D11_CULL_FRONT", "2", "" ],
		[ "D3D11_CULL_BACK", "3", "" ],
	];

	CreateWindowsEnum
	(
		"D3D11_CULL_MODE",
		items
	);
}


// D3D11_FILTER
{
	let items =
	[
		[ "D3D11_FILTER_MIN_MAG_MIP_POINT", "0", "" ],
		[ "D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR", "0x1", "" ],
		[ "D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT", "0x4", "" ],
		[ "D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR", "0x5", "" ],
		[ "D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT", "0x10", "" ],
		[ "D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR", "0x11", "" ],
		[ "D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT", "0x14", "" ],
		[ "D3D11_FILTER_MIN_MAG_MIP_LINEAR", "0x15", "" ],
		[ "D3D11_FILTER_ANISOTROPIC", "0x55", "" ],
		[ "D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT", "0x80", "" ],
		[ "D3D11_FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR", "0x81", "" ],
		[ "D3D11_FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT", "0x84", "" ],
		[ "D3D11_FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR", "0x85", "" ],
		[ "D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT", "0x90", "" ],
		[ "D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR", "0x91", "" ],
		[ "D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT", "0x94", "" ],
		[ "D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR", "0x95", "" ],
		[ "D3D11_FILTER_COMPARISON_ANISOTROPIC", "0xd5", "" ],
		[ "D3D11_FILTER_MINIMUM_MIN_MAG_MIP_POINT", "0x100", "" ],
		[ "D3D11_FILTER_MINIMUM_MIN_MAG_POINT_MIP_LINEAR", "0x101", "" ],
		[ "D3D11_FILTER_MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT", "0x104", "" ],
		[ "D3D11_FILTER_MINIMUM_MIN_POINT_MAG_MIP_LINEAR", "0x105", "" ],
		[ "D3D11_FILTER_MINIMUM_MIN_LINEAR_MAG_MIP_POINT", "0x110", "" ],
		[ "D3D11_FILTER_MINIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR", "0x111", "" ],
		[ "D3D11_FILTER_MINIMUM_MIN_MAG_LINEAR_MIP_POINT", "0x114", "" ],
		[ "D3D11_FILTER_MINIMUM_MIN_MAG_MIP_LINEAR", "0x115", "" ],
		[ "D3D11_FILTER_MINIMUM_ANISOTROPIC", "0x155", "" ],
		[ "D3D11_FILTER_MAXIMUM_MIN_MAG_MIP_POINT", "0x180", "" ],
		[ "D3D11_FILTER_MAXIMUM_MIN_MAG_POINT_MIP_LINEAR", "0x181", "" ],
		[ "D3D11_FILTER_MAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT", "0x184", "" ],
		[ "D3D11_FILTER_MAXIMUM_MIN_POINT_MAG_MIP_LINEAR", "0x185", "" ],
		[ "D3D11_FILTER_MAXIMUM_MIN_LINEAR_MAG_MIP_POINT", "0x190", "" ],
		[ "D3D11_FILTER_MAXIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR", "0x191", "" ],
		[ "D3D11_FILTER_MAXIMUM_MIN_MAG_LINEAR_MIP_POINT", "0x194", "" ],
		[ "D3D11_FILTER_MAXIMUM_MIN_MAG_MIP_LINEAR", "0x195", "" ],
		[ "D3D11_FILTER_MAXIMUM_ANISOTROPIC", "0x1d5", "" ],
	];

	CreateWindowsEnum
	(
		"D3D11_FILTER",
		items
	);
}

// D3D11_FILTER_TYPE
{
	let items =
	[
		[ "D3D11_FILTER_TYPE_POINT", "0", "" ],
		[ "D3D11_FILTER_TYPE_LINEAR", "1", "" ],
	];

	CreateWindowsEnum
	(
		"D3D11_FILTER_TYPE",
		items
	);
}


// D3D11_FILTER_REDUCTION_TYPE
{
	let items =
	[
		[ "D3D11_FILTER_REDUCTION_TYPE_STANDARD", "0", "" ],
		[ "D3D11_FILTER_REDUCTION_TYPE_COMPARISON", "1", "" ],
		[ "D3D11_FILTER_REDUCTION_TYPE_MINIMUM", "2", "" ],
		[ "D3D11_FILTER_REDUCTION_TYPE_MAXIMUM", "3", "" ],
	];

	CreateWindowsEnum
	(
		"D3D11_FILTER_REDUCTION_TYPE",
		items
	);
}


// D3D11_TEXTURE_ADDRESS_MODE
{
	let items =
	[
		[ "D3D11_TEXTURE_ADDRESS_WRAP", "1", "" ],
		[ "D3D11_TEXTURE_ADDRESS_MIRROR", "2", "" ],
		[ "D3D11_TEXTURE_ADDRESS_CLAMP", "3", "" ],
		[ "D3D11_TEXTURE_ADDRESS_BORDER", "4", "" ],
		[ "D3D11_TEXTURE_ADDRESS_MIRROR_ONCE", "5", "" ],
	];

	CreateWindowsEnum
	(
		"D3D11_TEXTURE_ADDRESS_MODE",
		items
	);
}

// D3D11_QUERY
{
	let items =
	[
		[ "D3D11_QUERY_EVENT", "0", "" ],
		[ "D3D11_QUERY_OCCLUSION", "(D3D11_QUERY_EVENT+1)", "" ],
		[ "D3D11_QUERY_TIMESTAMP", "(D3D11_QUERY_OCCLUSION+1)", "" ],
		[ "D3D11_QUERY_TIMESTAMP_DISJOINT", "(D3D11_QUERY_TIMESTAMP+1)", "" ],
		[ "D3D11_QUERY_PIPELINE_STATISTICS", "(D3D11_QUERY_TIMESTAMP_DISJOINT+1)", "" ],
		[ "D3D11_QUERY_OCCLUSION_PREDICATE", "(D3D11_QUERY_PIPELINE_STATISTICS+1)", "" ],
		[ "D3D11_QUERY_SO_STATISTICS", "(D3D11_QUERY_OCCLUSION_PREDICATE+1)", "" ],
		[ "D3D11_QUERY_SO_OVERFLOW_PREDICATE", "(D3D11_QUERY_SO_STATISTICS+1)", "" ],
		[ "D3D11_QUERY_SO_STATISTICS_STREAM0", "(D3D11_QUERY_SO_OVERFLOW_PREDICATE+1)", "" ],
		[ "D3D11_QUERY_SO_OVERFLOW_PREDICATE_STREAM0", "(D3D11_QUERY_SO_STATISTICS_STREAM0+1)", "" ],
		[ "D3D11_QUERY_SO_STATISTICS_STREAM1", "(D3D11_QUERY_SO_OVERFLOW_PREDICATE_STREAM0+1)", "" ],
		[ "D3D11_QUERY_SO_OVERFLOW_PREDICATE_STREAM1", "(D3D11_QUERY_SO_STATISTICS_STREAM1+1)", "" ],
		[ "D3D11_QUERY_SO_STATISTICS_STREAM2", "(D3D11_QUERY_SO_OVERFLOW_PREDICATE_STREAM1+1)", "" ],
		[ "D3D11_QUERY_SO_OVERFLOW_PREDICATE_STREAM2", "(D3D11_QUERY_SO_STATISTICS_STREAM2+1)", "" ],
		[ "D3D11_QUERY_SO_STATISTICS_STREAM3", "(D3D11_QUERY_SO_OVERFLOW_PREDICATE_STREAM2+1)", "" ],
		[ "D3D11_QUERY_SO_OVERFLOW_PREDICATE_STREAM3", "(D3D11_QUERY_SO_STATISTICS_STREAM3+1)", "" ],
	];

	CreateWindowsEnum
	(
		"D3D11_QUERY",
		items
	);
}


// D3D11_COUNTER
{
	let items =
	[
		[ "D3D11_COUNTER_DEVICE_DEPENDENT_0", "0x40000000", "" ],
	];

	CreateWindowsEnum
	(
		"D3D11_COUNTER",
		items
	);
}


// D3D11_COUNTER_TYPE
{
	let items =
	[
		[ "D3D11_COUNTER_TYPE_FLOAT32", "0", "" ],
		[ "D3D11_COUNTER_TYPE_UINT16", "(D3D11_COUNTER_TYPE_FLOAT32+1)", "" ],
		[ "D3D11_COUNTER_TYPE_UINT32", "(D3D11_COUNTER_TYPE_UINT16+1)", "" ],
		[ "D3D11_COUNTER_TYPE_UINT64", "(D3D11_COUNTER_TYPE_UINT32+1)", "" ],
	];

	CreateWindowsEnum
	(
		"D3D11_COUNTER_TYPE",
		items
	);
}


// D3D11_FEATURE
{
	let items =
	[
		[ "D3D11_FEATURE_THREADING", "0", "" ],
		[ "D3D11_FEATURE_DOUBLES", "(D3D11_FEATURE_THREADING+1)", "" ],
		[ "D3D11_FEATURE_FORMAT_SUPPORT", "(D3D11_FEATURE_DOUBLES+1)", "" ],
		[ "D3D11_FEATURE_FORMAT_SUPPORT2", "(D3D11_FEATURE_FORMAT_SUPPORT+1)", "" ],
		[ "D3D11_FEATURE_D3D10_X_HARDWARE_OPTIONS", "(D3D11_FEATURE_FORMAT_SUPPORT2+1)", "" ],
		[ "D3D11_FEATURE_D3D11_OPTIONS", "(D3D11_FEATURE_D3D10_X_HARDWARE_OPTIONS+1)", "" ],
		[ "D3D11_FEATURE_ARCHITECTURE_INFO", "(D3D11_FEATURE_D3D11_OPTIONS+1)", "" ],
		[ "D3D11_FEATURE_D3D9_OPTIONS", "(D3D11_FEATURE_ARCHITECTURE_INFO+1)", "" ],
		[ "D3D11_FEATURE_SHADER_MIN_PRECISION_SUPPORT", "(D3D11_FEATURE_D3D9_OPTIONS+1)", "" ],
		[ "D3D11_FEATURE_D3D9_SHADOW_SUPPORT", "(D3D11_FEATURE_SHADER_MIN_PRECISION_SUPPORT+1)", "" ],
		[ "D3D11_FEATURE_D3D11_OPTIONS1", "(D3D11_FEATURE_D3D9_SHADOW_SUPPORT+1)", "" ],
		[ "D3D11_FEATURE_D3D9_SIMPLE_INSTANCING_SUPPORT", "(D3D11_FEATURE_D3D11_OPTIONS1+1)", "" ],
		[ "D3D11_FEATURE_MARKER_SUPPORT", "(D3D11_FEATURE_D3D9_SIMPLE_INSTANCING_SUPPORT+1)", "" ],
		[ "D3D11_FEATURE_D3D9_OPTIONS1", "(D3D11_FEATURE_MARKER_SUPPORT+1)", "" ],
		[ "D3D11_FEATURE_D3D11_OPTIONS2", "(D3D11_FEATURE_D3D9_OPTIONS1+1)", "" ],
		[ "D3D11_FEATURE_D3D11_OPTIONS3", "(D3D11_FEATURE_D3D11_OPTIONS2+1)", "" ],
		[ "D3D11_FEATURE_GPU_VIRTUAL_ADDRESS_SUPPORT", "(D3D11_FEATURE_D3D11_OPTIONS3+1)", "" ],
		[ "D3D11_FEATURE_D3D11_OPTIONS4", "(D3D11_FEATURE_GPU_VIRTUAL_ADDRESS_SUPPORT+1)", "" ],
		[ "D3D11_FEATURE_SHADER_CACHE", "(D3D11_FEATURE_D3D11_OPTIONS4+1)", "" ],
		[ "D3D11_FEATURE_D3D11_OPTIONS5", "(D3D11_FEATURE_SHADER_CACHE+1)", "" ],
	];

	CreateWindowsEnum
	(
		"D3D11_FEATURE",
		items
	);
}

// D3D11_MAP
{
	let items =
	[
		[ "D3D11_MAP_READ", "1", "" ],
		[ "D3D11_MAP_WRITE", "2", "" ],
		[ "D3D11_MAP_READ_WRITE", "3", "" ],
		[ "D3D11_MAP_WRITE_DISCARD", "4", "" ],
		[ "D3D11_MAP_WRITE_NO_OVERWRITE", "5", "" ],
	];

	CreateWindowsEnum
	(
		"D3D11_MAP",
		items
	);
}


// D3D11_DEVICE_CONTEXT_TYPE
{
	let items =
	[
		[ "D3D11_DEVICE_CONTEXT_IMMEDIATE", "0", "" ],
		[ "D3D11_DEVICE_CONTEXT_DEFERRED", "(D3D11_DEVICE_CONTEXT_IMMEDIATE+1)", "" ],
	];

	CreateWindowsEnum
	(
		"D3D11_DEVICE_CONTEXT_TYPE",
		items
	);
}


// D3D11_VIDEO_FRAME_FORMAT
{
	let items =
	[
		[ "D3D11_VIDEO_FRAME_FORMAT_PROGRESSIVE", "0", "" ],
		[ "D3D11_VIDEO_FRAME_FORMAT_INTERLACED_TOP_FIELD_FIRST", "1", "" ],
		[ "D3D11_VIDEO_FRAME_FORMAT_INTERLACED_BOTTOM_FIELD_FIRST", "2", "" ],
	];

	CreateWindowsEnum
	(
		"D3D11_VIDEO_FRAME_FORMAT",
		items
	);
}

// D3D11_VIDEO_USAGE
{
	let items =
	[
		[ "D3D11_VIDEO_USAGE_PLAYBACK_NORMAL", "0", "" ],
		[ "D3D11_VIDEO_USAGE_OPTIMAL_SPEED", "1", "" ],
		[ "D3D11_VIDEO_USAGE_OPTIMAL_QUALITY", "2", "" ],
	];

	CreateWindowsEnum
	(
		"D3D11_VIDEO_USAGE",
		items
	);
}


// D3D11_VIDEO_PROCESSOR_FILTER
{
	let items =
	[
		[ "D3D11_VIDEO_PROCESSOR_FILTER_BRIGHTNESS", "0", "" ],
		[ "D3D11_VIDEO_PROCESSOR_FILTER_CONTRAST", "1", "" ],
		[ "D3D11_VIDEO_PROCESSOR_FILTER_HUE", "2", "" ],
		[ "D3D11_VIDEO_PROCESSOR_FILTER_SATURATION", "3", "" ],
		[ "D3D11_VIDEO_PROCESSOR_FILTER_NOISE_REDUCTION", "4", "" ],
		[ "D3D11_VIDEO_PROCESSOR_FILTER_EDGE_ENHANCEMENT", "5", "" ],
		[ "D3D11_VIDEO_PROCESSOR_FILTER_ANAMORPHIC_SCALING", "6", "" ],
		[ "D3D11_VIDEO_PROCESSOR_FILTER_STEREO_ADJUSTMENT", "7", "" ],
	];

	CreateWindowsEnum
	(
		"D3D11_VIDEO_PROCESSOR_FILTER",
		items
	);
}


// D3D11_VDOV_DIMENSION
{
	let items =
	[
		[ "D3D11_VDOV_DIMENSION_UNKNOWN", "0", "" ],
		[ "D3D11_VDOV_DIMENSION_TEXTURE2D", "1", "" ],
	];

	CreateWindowsEnum
	(
		"D3D11_VDOV_DIMENSION",
		items
	);
}


// D3D11_VPIV_DIMENSION
{
	let items =
	[
		[ "D3D11_VPIV_DIMENSION_UNKNOWN", "0", "" ],
		[ "D3D11_VPIV_DIMENSION_TEXTURE2D", "1", "" ],
	];

	CreateWindowsEnum
	(
		"D3D11_VPIV_DIMENSION",
		items
	);
}


// D3D11_VPOV_DIMENSION
{
	let items =
	[
		[ "D3D11_VPOV_DIMENSION_UNKNOWN", "0", "" ],
		[ "D3D11_VPOV_DIMENSION_TEXTURE2D", "1", "" ],
		[ "D3D11_VPOV_DIMENSION_TEXTURE2DARRAY", "2", "" ],
	];

	CreateWindowsEnum
	(
		"D3D11_VPOV_DIMENSION",
		items
	);
}


// D3D11_VIDEO_DECODER_BUFFER_TYPE
{
	let items =
	[
		[ "D3D11_VIDEO_DECODER_BUFFER_PICTURE_PARAMETERS", "0", "" ],
		[ "D3D11_VIDEO_DECODER_BUFFER_MACROBLOCK_CONTROL", "1", "" ],
		[ "D3D11_VIDEO_DECODER_BUFFER_RESIDUAL_DIFFERENCE", "2", "" ],
		[ "D3D11_VIDEO_DECODER_BUFFER_DEBLOCKING_CONTROL", "3", "" ],
		[ "D3D11_VIDEO_DECODER_BUFFER_INVERSE_QUANTIZATION_MATRIX", "4", "" ],
		[ "D3D11_VIDEO_DECODER_BUFFER_SLICE_CONTROL", "5", "" ],
		[ "D3D11_VIDEO_DECODER_BUFFER_BITSTREAM", "6", "" ],
		[ "D3D11_VIDEO_DECODER_BUFFER_MOTION_VECTOR", "7", "" ],
		[ "D3D11_VIDEO_DECODER_BUFFER_FILM_GRAIN", "8", "" ],
	];

	CreateWindowsEnum
	(
		"D3D11_VIDEO_DECODER_BUFFER_TYPE",
		items
	);
}


// D3D11_VIDEO_PROCESSOR_ALPHA_FILL_MODE
{
	let items =
	[
		[ "D3D11_VIDEO_PROCESSOR_ALPHA_FILL_MODE_OPAQUE", "0", "" ],
		[ "D3D11_VIDEO_PROCESSOR_ALPHA_FILL_MODE_BACKGROUND", "1", "" ],
		[ "D3D11_VIDEO_PROCESSOR_ALPHA_FILL_MODE_DESTINATION", "2", "" ],
		[ "D3D11_VIDEO_PROCESSOR_ALPHA_FILL_MODE_SOURCE_STREAM", "3", "" ],
	];

	CreateWindowsEnum
	(
		"D3D11_VIDEO_PROCESSOR_ALPHA_FILL_MODE",
		items
	);
}


// D3D11_VIDEO_PROCESSOR_OUTPUT_RATE
{
	let items =
	[
		[ "D3D11_VIDEO_PROCESSOR_OUTPUT_RATE_NORMAL", "0", "" ],
		[ "D3D11_VIDEO_PROCESSOR_OUTPUT_RATE_HALF", "1", "" ],
		[ "D3D11_VIDEO_PROCESSOR_OUTPUT_RATE_CUSTOM", "2", "" ],
	];

	CreateWindowsEnum
	(
		"D3D11_VIDEO_PROCESSOR_OUTPUT_RATE",
		items
	);
}



// D3D11_VIDEO_PROCESSOR_STEREO_FORMAT
{
	let items =
	[
		[ "D3D11_VIDEO_PROCESSOR_STEREO_FORMAT_MONO", "0", "" ],
		[ "D3D11_VIDEO_PROCESSOR_STEREO_FORMAT_HORIZONTAL", "1", "" ],
		[ "D3D11_VIDEO_PROCESSOR_STEREO_FORMAT_VERTICAL", "2", "" ],
		[ "D3D11_VIDEO_PROCESSOR_STEREO_FORMAT_SEPARATE", "3", "" ],
		[ "D3D11_VIDEO_PROCESSOR_STEREO_FORMAT_MONO_OFFSET", "4", "" ],
		[ "D3D11_VIDEO_PROCESSOR_STEREO_FORMAT_ROW_INTERLEAVED", "5", "" ],
		[ "D3D11_VIDEO_PROCESSOR_STEREO_FORMAT_COLUMN_INTERLEAVED", "6", "" ],
		[ "D3D11_VIDEO_PROCESSOR_STEREO_FORMAT_CHECKERBOARD", "7", "" ],
	];

	CreateWindowsEnum
	(
		"D3D11_VIDEO_PROCESSOR_STEREO_FORMAT",
		items
	);
}


// D3D11_VIDEO_PROCESSOR_STEREO_FLIP_MODE
{
	let items =
	[
		[ "D3D11_VIDEO_PROCESSOR_STEREO_FLIP_NONE", "0", "" ],
		[ "D3D11_VIDEO_PROCESSOR_STEREO_FLIP_FRAME0", "1", "" ],
		[ "D3D11_VIDEO_PROCESSOR_STEREO_FLIP_FRAME1", "2", "" ],
	];

	CreateWindowsEnum
	(
		"D3D11_VIDEO_PROCESSOR_STEREO_FLIP_MODE",
		items
	);
}


// D3D11_VIDEO_PROCESSOR_ROTATION
{
	let items =
	[
		[ "D3D11_VIDEO_PROCESSOR_ROTATION_IDENTITY", "0", "" ],
		[ "D3D11_VIDEO_PROCESSOR_ROTATION_90", "1", "" ],
		[ "D3D11_VIDEO_PROCESSOR_ROTATION_180", "2", "" ],
		[ "D3D11_VIDEO_PROCESSOR_ROTATION_270", "3", "" ],
	];

	CreateWindowsEnum
	(
		"D3D11_VIDEO_PROCESSOR_ROTATION",
		items
	);
}


// D3D11_AUTHENTICATED_CHANNEL_TYPE
{
	let items =
	[
		[ "D3D11_AUTHENTICATED_CHANNEL_D3D11", "1", "" ],
		[ "D3D11_AUTHENTICATED_CHANNEL_DRIVER_SOFTWARE", "2", "" ],
		[ "D3D11_AUTHENTICATED_CHANNEL_DRIVER_HARDWARE", "3", "" ],
	];

	CreateWindowsEnum
	(
		"D3D11_AUTHENTICATED_CHANNEL_TYPE",
		items
	);
}

// D3D11_BIND_FLAG
{
	let items =
	[
		[ "D3D11_BIND_VERTEX_BUFFER", "0x1", "" ],
		[ "D3D11_BIND_INDEX_BUFFER", "0x2", "" ],
		[ "D3D11_BIND_CONSTANT_BUFFER", "0x4", "" ],
		[ "D3D11_BIND_SHADER_RESOURCE", "0x8", "" ],
		[ "D3D11_BIND_STREAM_OUTPUT", "0x10", "" ],
		[ "D3D11_BIND_RENDER_TARGET", "0x20", "" ],
		[ "D3D11_BIND_DEPTH_STENCIL", "0x40", "" ],
		[ "D3D11_BIND_UNORDERED_ACCESS", "0x80", "" ],
		[ "D3D11_BIND_DECODER", "0x200", "" ],
		[ "D3D11_BIND_VIDEO_ENCODER", "0x400", "" ],
	];

	CreateWindowsEnum
	(
		"D3D11_BIND_FLAG",
		items
	);
}

// D3D11_CPU_ACCESS_FLAG
{
	let items =
	[
		[ "D3D11_CPU_ACCESS_WRITE", "0x10000", "" ],
		[ "D3D11_CPU_ACCESS_READ", "0x20000", "" ],
	];

	CreateWindowsEnum
	(
		"D3D11_CPU_ACCESS_FLAG",
		items
	);
}



// D3D11_COLOR_WRITE_ENABLE
{
	let items =
	[
		[ "D3D11_COLOR_WRITE_ENABLE_RED", "1", "" ],
		[ "D3D11_COLOR_WRITE_ENABLE_GREEN", "2", "" ],
		[ "D3D11_COLOR_WRITE_ENABLE_BLUE", "4", "" ],
		[ "D3D11_COLOR_WRITE_ENABLE_ALPHA", "8", "" ],
		[ "D3D11_COLOR_WRITE_ENABLE_ALL", "(((D3D11_COLOR_WRITE_ENABLE_RED|D3D11_COLOR_WRITE_ENABLE_GREEN)|D3D11_COLOR_WRITE_ENABLE_BLUE)|D3D11_COLOR_WRITE_ENABLE_ALPHA)", "" ],
	];

	CreateWindowsEnum
	(
		"D3D11_COLOR_WRITE_ENABLE",
		items
	);
}


// D3D_INCLUDE_TYPE
{
	let items =
	[
		[ "D3D_INCLUDE_LOCAL", "0", "" ],
		[ "D3D_INCLUDE_SYSTEM", "(D3D_INCLUDE_LOCAL+1)", "" ],
		[ "D3D10_INCLUDE_LOCAL", "D3D_INCLUDE_LOCAL", "" ],
		[ "D3D10_INCLUDE_SYSTEM", "D3D_INCLUDE_SYSTEM", "" ],
		[ "D3D_INCLUDE_FORCE_DWORD", "0x7fffffff", "" ],
	];

	CreateWindowsEnum
	(
		"D3D_INCLUDE_TYPE",
		items
	);
}


/*



*/













// Structs

c += Tabs() + "#pragma pack(push, 1)" + NEW_LINE;
c += NEW_LINE;




// D3D11_BUFFER_DESC
{
	let items =
	[
		[ "ByteWidth", "UINT" ],
		[ "Usage", "D3D11_USAGE" ],
		[ "BindFlags", "UINT" ],
		[ "CPUAccessFlags", "UINT" ],
		[ "MiscFlags", "UINT" ],
		[ "StructureByteStride", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_BUFFER_DESC",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// D3D11_SUBRESOURCE_DATA
{
	let items =
	[
		[ "pSysMem", "const void*" ],
		[ "SysMemPitch", "UINT" ],
		[ "SysMemSlicePitch", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_SUBRESOURCE_DATA",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// D3D11_TEXTURE1D_DESC
{
	let items =
	[
		[ "Width", "UINT" ],
		[ "MipLevels", "UINT" ],
		[ "ArraySize", "UINT" ],
		[ "Format", "DXGI_FORMAT" ],
		[ "Usage", "D3D11_USAGE" ],
		[ "BindFlags", "UINT" ],
		[ "CPUAccessFlags", "UINT" ],
		[ "MiscFlags", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_TEXTURE1D_DESC",
		items,
		0,
		TypeFlags_NoPointers
	);
}



// D3D11_TEXTURE2D_DESC
{
	let items =
	[
		[ "Width", "UINT" ],
		[ "Height", "UINT" ],
		[ "MipLevels", "UINT" ],
		[ "ArraySize", "UINT" ],
		[ "Format", "DXGI_FORMAT" ],
		[ "SampleDesc", "DXGI_SAMPLE_DESC" ],
		[ "Usage", "D3D11_USAGE" ],
		[ "BindFlags", "UINT" ],
		[ "CPUAccessFlags", "UINT" ],
		[ "MiscFlags", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_TEXTURE2D_DESC",
		items,
		0,
		TypeFlags_NoPointers
	);
}

// D3D11_TEXTURE3D_DESC
{
	let items =
	[
		[ "Width", "UINT" ],
		[ "Height", "UINT" ],
		[ "Depth", "UINT" ],
		[ "MipLevels", "UINT" ],
		[ "Format", "DXGI_FORMAT" ],
		[ "Usage", "D3D11_USAGE" ],
		[ "BindFlags", "UINT" ],
		[ "CPUAccessFlags", "UINT" ],
		[ "MiscFlags", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_TEXTURE3D_DESC",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// D3D11_BUFFER_SRV
{
	let items =
	[
		[ "", "union",
			[
				[ "FirstElement", "UINT" ],
				[ "ElementOffset", "UINT" ],
			],
		],
		[ "", "union",
			[
				[ "NumElements", "UINT" ],
				[ "ElementWidth", "UINT" ],
			],
		],
	];

	CreateWindowsTuple
	(
		"D3D11_BUFFER_SRV",
		items,
		0,
		TypeFlags_NoPointers
	);
}



// D3D11_BUFFEREX_SRV
{
	let items =
	[
		[ "FirstElement", "UINT" ],
		[ "NumElements", "UINT" ],
		[ "Flags", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_BUFFEREX_SRV",
		items,
		0,
		TypeFlags_NoPointers
	);
}



// D3D11_TEX1D_SRV
{
	let items =
	[
		[ "MostDetailedMip", "UINT" ],
		[ "MipLevels", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_TEX1D_SRV",
		items,
		0,
		TypeFlags_NoPointers
	);
}

// D3D11_TEX1D_ARRAY_SRV
{
	let items =
	[
		[ "MostDetailedMip", "UINT" ],
		[ "MipLevels", "UINT" ],
		[ "FirstArraySlice", "UINT" ],
		[ "ArraySize", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_TEX1D_ARRAY_SRV",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// D3D11_TEX2D_SRV
{
	let items =
	[
		[ "MostDetailedMip", "UINT" ],
		[ "MipLevels", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_TEX2D_SRV",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// D3D11_TEX2D_ARRAY_SRV
{
	let items =
	[
		[ "MostDetailedMip", "UINT" ],
		[ "MipLevels", "UINT" ],
		[ "FirstArraySlice", "UINT" ],
		[ "ArraySize", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_TEX2D_ARRAY_SRV",
		items,
		0,
		TypeFlags_NoPointers
	);
}

// D3D11_TEX3D_SRV
{
	let items =
	[
		[ "MostDetailedMip", "UINT" ],
		[ "MipLevels", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_TEX3D_SRV",
		items,
		0,
		TypeFlags_NoPointers
	);
}



// D3D11_TEXCUBE_SRV
{
	let items =
	[
		[ "MostDetailedMip", "UINT" ],
		[ "MipLevels", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_TEXCUBE_SRV",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// D3D11_TEXCUBE_ARRAY_SRV
{
	let items =
	[
		[ "MostDetailedMip", "UINT" ],
		[ "MipLevels", "UINT" ],
		[ "First2DArrayFace", "UINT" ],
		[ "NumCubes", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_TEXCUBE_ARRAY_SRV",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// D3D11_TEX2DMS_SRV
{
	let items =
	[
		[ "UnusedField_NothingToDefine", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_TEX2DMS_SRV",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// D3D11_TEX2DMS_ARRAY_SRV
{
	let items =
	[
		[ "FirstArraySlice", "UINT" ],
		[ "ArraySize", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_TEX2DMS_ARRAY_SRV",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// D3D11_SHADER_RESOURCE_VIEW_DESC
{
	let items =
	[
		[ "Format", "DXGI_FORMAT" ],
		[ "ViewDimension", "D3D11_SRV_DIMENSION" ],
		[ "", "union",
			[
				[ "Buffer", "D3D11_BUFFER_SRV" ],
				[ "Texture1D", "D3D11_TEX1D_SRV" ],
				[ "Texture1DArray", "D3D11_TEX1D_ARRAY_SRV" ],
				[ "Texture2D", "D3D11_TEX2D_SRV" ],
				[ "Texture2DArray", "D3D11_TEX2D_ARRAY_SRV" ],
				[ "Texture2DMS", "D3D11_TEX2DMS_SRV" ],
				[ "Texture2DMSArray", "D3D11_TEX2DMS_ARRAY_SRV" ],
				[ "Texture3D", "D3D11_TEX3D_SRV" ],
				[ "TextureCube", "D3D11_TEXCUBE_SRV" ],
				[ "TextureCubeArray", "D3D11_TEXCUBE_ARRAY_SRV" ],
				[ "BufferEx", "D3D11_BUFFEREX_SRV" ],
			],
		],
	];

	CreateWindowsTuple
	(
		"D3D11_SHADER_RESOURCE_VIEW_DESC",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// D3D11_BUFFER_UAV
{
	let items =
	[
		[ "FirstElement", "UINT" ],
		[ "NumElements", "UINT" ],
		[ "Flags", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_BUFFER_UAV",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// D3D11_TEX1D_UAV
{
	let items =
	[
		[ "MipSlice", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_TEX1D_UAV",
		items,
		0,
		TypeFlags_NoPointers
	);
}



// D3D11_TEX1D_ARRAY_UAV
{
	let items =
	[
		[ "MipSlice", "UINT" ],
		[ "FirstArraySlice", "UINT" ],
		[ "ArraySize", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_TEX1D_ARRAY_UAV",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// D3D11_TEX2D_UAV
{
	let items =
	[
		[ "MipSlice", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_TEX2D_UAV",
		items,
		0,
		TypeFlags_NoPointers
	);
}



// D3D11_TEX2D_ARRAY_UAV
{
	let items =
	[
		[ "MipSlice", "UINT" ],
		[ "FirstArraySlice", "UINT" ],
		[ "ArraySize", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_TEX2D_ARRAY_UAV",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// D3D11_TEX3D_UAV
{
	let items =
	[
		[ "MipSlice", "UINT" ],
		[ "FirstWSlice", "UINT" ],
		[ "WSize", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_TEX3D_UAV",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// D3D11_UNORDERED_ACCESS_VIEW_DESC
{
	let items =
	[
		[ "Format", "DXGI_FORMAT" ],
		[ "ViewDimension", "D3D11_UAV_DIMENSION" ],
		[ "", "union",
			[
				[ "Buffer", "D3D11_BUFFER_UAV" ],
				[ "Texture1D", "D3D11_TEX1D_UAV" ],
				[ "Texture1DArray", "D3D11_TEX1D_ARRAY_UAV" ],
				[ "Texture2D", "D3D11_TEX2D_UAV" ],
				[ "Texture2DArray", "D3D11_TEX2D_ARRAY_UAV" ],
				[ "Texture3D", "D3D11_TEX3D_UAV" ],
			],
		],
	];

	CreateWindowsTuple
	(
		"D3D11_UNORDERED_ACCESS_VIEW_DESC",
		items,
		0,
		TypeFlags_NoPointers
	);
}

// D3D11_BUFFER_RTV
{
	let items =
	[
		[ "", "union",
			[
				[ "FirstElement", "UINT" ],
				[ "ElementOffset", "UINT" ],
			],
		],
		[ "", "union",
			[
				[ "NumElements", "UINT" ],
				[ "ElementWidth", "UINT" ],
			],
		],
	];

	CreateWindowsTuple
	(
		"D3D11_BUFFER_RTV",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// D3D11_TEX1D_RTV
{
	let items =
	[
		[ "MipSlice", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_TEX1D_RTV",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// D3D11_TEX1D_ARRAY_RTV
{
	let items =
	[
		[ "MipSlice", "UINT" ],
		[ "FirstArraySlice", "UINT" ],
		[ "ArraySize", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_TEX1D_ARRAY_RTV",
		items,
		0,
		TypeFlags_NoPointers
	);
}

// D3D11_TEX2D_RTV
{
	let items =
	[
		[ "MipSlice", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_TEX2D_RTV",
		items,
		0,
		TypeFlags_NoPointers
	);
}

// D3D11_TEX2DMS_RTV
{
	let items =
	[
		[ "UnusedField_NothingToDefine", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_TEX2DMS_RTV",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// D3D11_TEX2D_ARRAY_RTV
{
	let items =
	[
		[ "MipSlice", "UINT" ],
		[ "FirstArraySlice", "UINT" ],
		[ "ArraySize", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_TEX2D_ARRAY_RTV",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// D3D11_TEX2DMS_ARRAY_RTV
{
	let items =
	[
		[ "FirstArraySlice", "UINT" ],
		[ "ArraySize", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_TEX2DMS_ARRAY_RTV",
		items,
		0,
		TypeFlags_NoPointers
	);
}

// D3D11_TEX3D_RTV
{
	let items =
	[
		[ "MipSlice", "UINT" ],
		[ "FirstWSlice", "UINT" ],
		[ "WSize", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_TEX3D_RTV",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// D3D11_RENDER_TARGET_VIEW_DESC
{
	let items =
	[
		[ "Format", "DXGI_FORMAT" ],
		[ "ViewDimension", "D3D11_RTV_DIMENSION" ],
		[ "", "union",
			[
				[ "Buffer", "D3D11_BUFFER_RTV" ],
				[ "Texture1D", "D3D11_TEX1D_RTV" ],
				[ "Texture1DArray", "D3D11_TEX1D_ARRAY_RTV" ],
				[ "Texture2D", "D3D11_TEX2D_RTV" ],
				[ "Texture2DArray", "D3D11_TEX2D_ARRAY_RTV" ],
				[ "Texture2DMS", "D3D11_TEX2DMS_RTV" ],
				[ "Texture2DMSArray", "D3D11_TEX2DMS_ARRAY_RTV" ],
				[ "Texture3D", "D3D11_TEX3D_RTV" ],
			],
		],
	];

	CreateWindowsTuple
	(
		"D3D11_RENDER_TARGET_VIEW_DESC",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// D3D11_TEX1D_DSV
{
	let items =
	[
		[ "MipSlice", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_TEX1D_DSV",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// D3D11_TEX1D_ARRAY_DSV
{
	let items =
	[
		[ "MipSlice", "UINT" ],
		[ "FirstArraySlice", "UINT" ],
		[ "ArraySize", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_TEX1D_ARRAY_DSV",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// D3D11_TEX2D_DSV
{
	let items =
	[
		[ "MipSlice", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_TEX2D_DSV",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// D3D11_TEX2D_ARRAY_DSV
{
	let items =
	[
		[ "MipSlice", "UINT" ],
		[ "FirstArraySlice", "UINT" ],
		[ "ArraySize", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_TEX2D_ARRAY_DSV",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// D3D11_TEX2DMS_DSV
{
	let items =
	[
		[ "UnusedField_NothingToDefine", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_TEX2DMS_DSV",
		items,
		0,
		TypeFlags_NoPointers
	);
}

// D3D11_TEX2DMS_ARRAY_DSV
{
	let items =
	[
		[ "FirstArraySlice", "UINT" ],
		[ "ArraySize", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_TEX2DMS_ARRAY_DSV",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// D3D11_DEPTH_STENCIL_VIEW_DESC
{
	let items =
	[
		[ "Format", "DXGI_FORMAT" ],
		[ "ViewDimension", "D3D11_DSV_DIMENSION" ],
		[ "Flags", "UINT" ],
		[ "", "union",
			[
				[ "Texture1D", "D3D11_TEX1D_DSV" ],
				[ "Texture1DArray", "D3D11_TEX1D_ARRAY_DSV" ],
				[ "Texture2D", "D3D11_TEX2D_DSV" ],
				[ "Texture2DArray", "D3D11_TEX2D_ARRAY_DSV" ],
				[ "Texture2DMS", "D3D11_TEX2DMS_DSV" ],
				[ "Texture2DMSArray", "D3D11_TEX2DMS_ARRAY_DSV" ],
			],
		],
	];

	CreateWindowsTuple
	(
		"D3D11_DEPTH_STENCIL_VIEW_DESC",
		items,
		0,
		TypeFlags_NoPointers
	);
}



// D3D11_INPUT_ELEMENT_DESC
{
	let items =
	[
		[ "SemanticName", "LPCSTR" ],
		[ "SemanticIndex", "UINT" ],
		[ "Format", "DXGI_FORMAT" ],
		[ "InputSlot", "UINT" ],
		[ "AlignedByteOffset", "UINT" ],
		[ "InputSlotClass", "D3D11_INPUT_CLASSIFICATION" ],
		[ "InstanceDataStepRate", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_INPUT_ELEMENT_DESC",
		items,
		0,
		TypeFlags_NoPointers
	);
}

// D3D11_SO_DECLARATION_ENTRY
{
	let items =
	[
		[ "Stream", "UINT" ],
		[ "_(4)", "" ],
		[ "SemanticName", "LPCSTR" ],
		[ "SemanticIndex", "UINT" ],
		[ "StartComponent", "BYTE" ],
		[ "ComponentCount", "BYTE" ],
		[ "OutputSlot", "BYTE" ],
		[ "_(1)", "" ],
	];

	CreateWindowsTuple
	(
		"D3D11_SO_DECLARATION_ENTRY",
		items,
		0,
		TypeFlags_NoPointers
	);
}

// D3D11_VIEWPORT
{
	let items =
	[
		[ "TopLeftX", "FLOAT" ],
		[ "TopLeftY", "FLOAT" ],
		[ "Width", "FLOAT" ],
		[ "Height", "FLOAT" ],
		[ "MinDepth", "FLOAT" ],
		[ "MaxDepth", "FLOAT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_VIEWPORT",
		items,
		0,
		TypeFlags_NoPointers
	);
}

// D3D11_RENDER_TARGET_BLEND_DESC
{
	let items =
	[
		[ "BlendEnable", "BOOL" ],
		[ "SrcBlend", "D3D11_BLEND" ],
		[ "DestBlend", "D3D11_BLEND" ],
		[ "BlendOp", "D3D11_BLEND_OP" ],
		[ "SrcBlendAlpha", "D3D11_BLEND" ],
		[ "DestBlendAlpha", "D3D11_BLEND" ],
		[ "BlendOpAlpha", "D3D11_BLEND_OP" ],
		[ "RenderTargetWriteMask", "UINT8" ],
		[ "_(3)", "" ],
	];

	CreateWindowsTuple
	(
		"D3D11_RENDER_TARGET_BLEND_DESC",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// D3D11_BLEND_DESC
{
	let items =
	[
		[ "AlphaToCoverageEnable", "BOOL" ],
		[ "IndependentBlendEnable", "BOOL" ],
		[ "RenderTarget[8]", "D3D11_RENDER_TARGET_BLEND_DESC" ],
	];

	CreateWindowsTuple
	(
		"D3D11_BLEND_DESC",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// D3D11_DEPTH_STENCILOP_DESC
{
	let items =
	[
		[ "StencilFailOp", "D3D11_STENCIL_OP" ],
		[ "StencilDepthFailOp", "D3D11_STENCIL_OP" ],
		[ "StencilPassOp", "D3D11_STENCIL_OP" ],
		[ "StencilFunc", "D3D11_COMPARISON_FUNC" ],
	];

	CreateWindowsTuple
	(
		"D3D11_DEPTH_STENCILOP_DESC",
		items,
		0,
		TypeFlags_NoPointers
	);
}

// D3D11_DEPTH_STENCIL_DESC
{
	let items =
	[
		[ "DepthEnable", "BOOL" ],
		[ "DepthWriteMask", "D3D11_DEPTH_WRITE_MASK" ],
		[ "DepthFunc", "D3D11_COMPARISON_FUNC" ],
		[ "StencilEnable", "BOOL" ],
		[ "StencilReadMask", "UINT8" ],
		[ "StencilWriteMask", "UINT8" ],
		[ "_(2)", "" ],
		[ "FrontFace", "D3D11_DEPTH_STENCILOP_DESC" ],
		[ "BackFace", "D3D11_DEPTH_STENCILOP_DESC" ],
	];

	CreateWindowsTuple
	(
		"D3D11_DEPTH_STENCIL_DESC",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// D3D11_RASTERIZER_DESC
{
	let items =
	[
		[ "FillMode", "D3D11_FILL_MODE" ],
		[ "CullMode", "D3D11_CULL_MODE" ],
		[ "FrontCounterClockwise", "BOOL" ],
		[ "DepthBias", "INT" ],
		[ "DepthBiasClamp", "FLOAT" ],
		[ "SlopeScaledDepthBias", "FLOAT" ],
		[ "DepthClipEnable", "BOOL" ],
		[ "ScissorEnable", "BOOL" ],
		[ "MultisampleEnable", "BOOL" ],
		[ "AntialiasedLineEnable", "BOOL" ],
	];

	CreateWindowsTuple
	(
		"D3D11_RASTERIZER_DESC",
		items,
		0,
		TypeFlags_NoPointers
	);
}

// D3D11_SAMPLER_DESC
{
	let items =
	[
		[ "Filter", "D3D11_FILTER" ],
		[ "AddressU", "D3D11_TEXTURE_ADDRESS_MODE" ],
		[ "AddressV", "D3D11_TEXTURE_ADDRESS_MODE" ],
		[ "AddressW", "D3D11_TEXTURE_ADDRESS_MODE" ],
		[ "MipLODBias", "FLOAT" ],
		[ "MaxAnisotropy", "UINT" ],
		[ "ComparisonFunc", "D3D11_COMPARISON_FUNC" ],
		[ "BorderColor[4]", "FLOAT" ],
		[ "MinLOD", "FLOAT" ],
		[ "MaxLOD", "FLOAT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_SAMPLER_DESC",
		items,
		0,
		TypeFlags_NoPointers
	);
}

// D3D11_QUERY_DESC
{
	let items =
	[
		[ "Query", "D3D11_QUERY" ],
		[ "MiscFlags", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_QUERY_DESC",
		items,
		0,
		TypeFlags_NoPointers
	);
}

// D3D11_COUNTER_DESC
{
	let items =
	[
		[ "Counter", "D3D11_COUNTER" ],
		[ "MiscFlags", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_COUNTER_DESC",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// D3D11_COUNTER_INFO
{
	let items =
	[
		[ "LastDeviceDependentCounter", "D3D11_COUNTER" ],
		[ "NumSimultaneousCounters", "UINT" ],
		[ "NumDetectableParallelUnits", "UINT8" ],
		[ "_(3)", "" ],
	];

	CreateWindowsTuple
	(
		"D3D11_COUNTER_INFO",
		items,
		0,
		TypeFlags_NoPointers
	);
}

// D3D11_MAPPED_SUBRESOURCE
{
	let items =
	[
		[ "pData", "void*" ],
		[ "RowPitch", "UINT" ],
		[ "DepthPitch", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_MAPPED_SUBRESOURCE",
		items,
		0,
		TypeFlags_NoPointers
	);
}

// D3D11_BOX
{
	let items =
	[
		[ "left", "UINT" ],
		[ "top", "UINT" ],
		[ "front", "UINT" ],
		[ "right", "UINT" ],
		[ "bottom", "UINT" ],
		[ "back", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_BOX",
		items,
		0,
		TypeFlags_NoPointers
	);
}



// D3D11_CLASS_INSTANCE_DESC
{
	let items =
	[
		[ "InstanceId", "UINT" ],
		[ "InstanceIndex", "UINT" ],
		[ "TypeId", "UINT" ],
		[ "ConstantBuffer", "UINT" ],
		[ "BaseConstantBufferOffset", "UINT" ],
		[ "BaseTexture", "UINT" ],
		[ "BaseSampler", "UINT" ],
		[ "Created", "BOOL" ],
	];

	CreateWindowsTuple
	(
		"D3D11_CLASS_INSTANCE_DESC",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// D3D11_VIDEO_DECODER_DESC
{
	let items =
	[
		[ "Guid", "GUID" ],
		[ "SampleWidth", "UINT" ],
		[ "SampleHeight", "UINT" ],
		[ "OutputFormat", "DXGI_FORMAT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_VIDEO_DECODER_DESC",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// D3D11_VIDEO_PROCESSOR_CONTENT_DESC
{
	let items =
	[
		[ "InputFrameFormat", "D3D11_VIDEO_FRAME_FORMAT" ],
		[ "InputFrameRate", "DXGI_RATIONAL" ],
		[ "InputWidth", "UINT" ],
		[ "InputHeight", "UINT" ],
		[ "OutputFrameRate", "DXGI_RATIONAL" ],
		[ "OutputWidth", "UINT" ],
		[ "OutputHeight", "UINT" ],
		[ "Usage", "D3D11_VIDEO_USAGE" ],
	];

	CreateWindowsTuple
	(
		"D3D11_VIDEO_PROCESSOR_CONTENT_DESC",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// D3D11_VIDEO_PROCESSOR_CAPS
{
	let items =
	[
		[ "DeviceCaps", "UINT" ],
		[ "FeatureCaps", "UINT" ],
		[ "FilterCaps", "UINT" ],
		[ "InputFormatCaps", "UINT" ],
		[ "AutoStreamCaps", "UINT" ],
		[ "StereoCaps", "UINT" ],
		[ "RateConversionCapsCount", "UINT" ],
		[ "MaxInputStreams", "UINT" ],
		[ "MaxStreamStates", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_VIDEO_PROCESSOR_CAPS",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// D3D11_VIDEO_PROCESSOR_RATE_CONVERSION_CAPS
{
	let items =
	[
		[ "PastFrames", "UINT" ],
		[ "FutureFrames", "UINT" ],
		[ "ProcessorCaps", "UINT" ],
		[ "ITelecineCaps", "UINT" ],
		[ "CustomRateCount", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_VIDEO_PROCESSOR_RATE_CONVERSION_CAPS",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// D3D11_VIDEO_PROCESSOR_CUSTOM_RATE
{
	let items =
	[
		[ "CustomRate", "DXGI_RATIONAL" ],
		[ "OutputFrames", "UINT" ],
		[ "InputInterlaced", "BOOL" ],
		[ "InputFramesOrFields", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_VIDEO_PROCESSOR_CUSTOM_RATE",
		items,
		0,
		TypeFlags_NoPointers
	);
}




// D3D11_VIDEO_DECODER_CONFIG
{
	let items =
	[
		[ "guidConfigBitstreamEncryption", "GUID" ],
		[ "guidConfigMBcontrolEncryption", "GUID" ],
		[ "guidConfigResidDiffEncryption", "GUID" ],
		[ "ConfigBitstreamRaw", "UINT" ],
		[ "ConfigMBcontrolRasterOrder", "UINT" ],
		[ "ConfigResidDiffHost", "UINT" ],
		[ "ConfigSpatialResid8", "UINT" ],
		[ "ConfigResid8Subtraction", "UINT" ],
		[ "ConfigSpatialHost8or9Clipping", "UINT" ],
		[ "ConfigSpatialResidInterleaved", "UINT" ],
		[ "ConfigIntraResidUnsigned", "UINT" ],
		[ "ConfigResidDiffAccelerator", "UINT" ],
		[ "ConfigHostInverseScan", "UINT" ],
		[ "ConfigSpecificIDCT", "UINT" ],
		[ "Config4GroupedCoefs", "UINT" ],
		[ "ConfigMinRenderTargetBuffCount", "USHORT" ],
		[ "ConfigDecoderSpecific", "USHORT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_VIDEO_DECODER_CONFIG",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// D3D11_TEX2D_VDOV
{
	let items =
	[
		[ "ArraySlice", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_TEX2D_VDOV",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// D3D11_VIDEO_DECODER_OUTPUT_VIEW_DESC
{
	let items =
	[
		[ "DecodeProfile", "GUID" ],
		[ "ViewDimension", "D3D11_VDOV_DIMENSION" ],
		[ "", "union",
			[
				[ "Texture2D", "D3D11_TEX2D_VDOV" ],
			],
		],
	];

	CreateWindowsTuple
	(
		"D3D11_VIDEO_DECODER_OUTPUT_VIEW_DESC",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// D3D11_TEX2D_VPIV
{
	let items =
	[
		[ "MipSlice", "UINT" ],
		[ "ArraySlice", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_TEX2D_VPIV",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// D3D11_VIDEO_PROCESSOR_INPUT_VIEW_DESC
{
	let items =
	[
		[ "FourCC", "UINT" ],
		[ "ViewDimension", "D3D11_VPIV_DIMENSION" ],
		[ "", "union",
			[
				[ "Texture2D", "D3D11_TEX2D_VPIV" ],
			],
		],
	];

	CreateWindowsTuple
	(
		"D3D11_VIDEO_PROCESSOR_INPUT_VIEW_DESC",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// D3D11_VIDEO_PROCESSOR_FILTER_RANGE
{
	let items =
	[
		[ "Minimum", "int" ],
		[ "Maximum", "int" ],
		[ "Default", "int" ],
		[ "Multiplier", "float" ],
	];

	CreateWindowsTuple
	(
		"D3D11_VIDEO_PROCESSOR_FILTER_RANGE",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// D3D11_TEX2D_VPOV
{
	let items =
	[
		[ "MipSlice", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_TEX2D_VPOV",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// D3D11_TEX2D_ARRAY_VPOV
{
	let items =
	[
		[ "MipSlice", "UINT" ],
		[ "FirstArraySlice", "UINT" ],
		[ "ArraySize", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_TEX2D_ARRAY_VPOV",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// D3D11_VIDEO_PROCESSOR_OUTPUT_VIEW_DESC
{
	let items =
	[
		[ "ViewDimension", "D3D11_VPOV_DIMENSION" ],
		[ "", "union",
			[
				[ "Texture2D", "D3D11_TEX2D_VPOV" ],
				[ "Texture2DArray", "D3D11_TEX2D_ARRAY_VPOV" ],
			],
		],
	];

	CreateWindowsTuple
	(
		"D3D11_VIDEO_PROCESSOR_OUTPUT_VIEW_DESC",
		items,
		0,
		TypeFlags_NoPointers
	);
}

// D3D11_ENCRYPTED_BLOCK_INFO
{
	let items =
	[
		[ "NumEncryptedBytesAtBeginning", "UINT" ],
		[ "NumBytesInSkipPattern", "UINT" ],
		[ "NumBytesInEncryptPattern", "UINT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_ENCRYPTED_BLOCK_INFO",
		items,
		0,
		TypeFlags_NoPointers
	);
}

// D3D11_VIDEO_DECODER_BUFFER_DESC
{
	let items =
	[
		[ "BufferType", "D3D11_VIDEO_DECODER_BUFFER_TYPE" ],
		[ "BufferIndex", "UINT" ],
		[ "DataOffset", "UINT" ],
		[ "DataSize", "UINT" ],
		[ "FirstMBaddress", "UINT" ],
		[ "NumMBsInBuffer", "UINT" ],
		[ "Width", "UINT" ],
		[ "Height", "UINT" ],
		[ "Stride", "UINT" ],
		[ "ReservedBits", "UINT" ],
		[ "pIV", "void*" ],
		[ "IVSize", "UINT" ],
		[ "PartialEncryption", "BOOL" ],
		[ "EncryptedBlockInfo", "D3D11_ENCRYPTED_BLOCK_INFO" ],
		[ "_(4)", "" ],
	];

	CreateWindowsTuple
	(
		"D3D11_VIDEO_DECODER_BUFFER_DESC",
		items,
		0,
		TypeFlags_NoPointers
	);
}

// D3D11_VIDEO_DECODER_EXTENSION
{
	let items =
	[
		[ "Function", "UINT" ],
		[ "_(4)", "" ],
		[ "pPrivateInputData", "void*" ],
		[ "PrivateInputDataSize", "UINT" ],
		[ "_(4)", "" ],
		[ "pPrivateOutputData", "void*" ],
		[ "PrivateOutputDataSize", "UINT" ],
		[ "ResourceCount", "UINT" ],
		[ "ppResourceList", "ID3D11Resource**" ],
	];

	CreateWindowsTuple
	(
		"D3D11_VIDEO_DECODER_EXTENSION",
		items,
		0,
		TypeFlags_NoPointers
	);
}



// D3D11_VIDEO_COLOR_RGBA
{
	let items =
	[
		[ "R", "float" ],
		[ "G", "float" ],
		[ "B", "float" ],
		[ "A", "float" ],
	];

	CreateWindowsTuple
	(
		"D3D11_VIDEO_COLOR_RGBA",
		items,
		0,
		TypeFlags_NoPointers
	);
}

// D3D11_VIDEO_COLOR_YCbCrA
{
	let items =
	[
		[ "Y", "float" ],
		[ "Cb", "float" ],
		[ "Cr", "float" ],
		[ "A", "float" ],
	];

	CreateWindowsTuple
	(
		"D3D11_VIDEO_COLOR_YCbCrA",
		items,
		0,
		TypeFlags_NoPointers
	);
}

// D3D11_VIDEO_COLOR
{
	let items =
	[
		[ "", "union",
			[
				[ "YCbCr", "D3D11_VIDEO_COLOR_YCbCrA" ],
				[ "RGBA", "D3D11_VIDEO_COLOR_RGBA" ],
			],
		],
	];

	CreateWindowsTuple
	(
		"D3D11_VIDEO_COLOR",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// D3D11_VIDEO_PROCESSOR_COLOR_SPACE
{
	let items =
	[
		[ "_(4)", "" ],
	];

	// let items =
	// [
	// 	[ "Usage", "UINT" ],
	// 	[ "RGB_Range", "UINT" ],
	// 	[ "YCbCr_Matrix", "UINT" ],
	// 	[ "YCbCr_xvYCC", "UINT" ],
	// 	[ "Nominal_Range", "UINT" ],
	// 	[ "Reserved", "UINT" ],
	// ];

	// let items =
	// [
	// 	[ "Usage_1", "UINT" ],
	// 	[ "RGB_Range_1", "UINT" ],
	// 	[ "YCbCr_Matrix_1", "UINT" ],
	// 	[ "YCbCr_xvYCC_1", "UINT" ],
	// 	[ "Nominal_Range_2", "UINT" ],
	// 	[ "Reserved_26", "UINT" ],
	// ];

	CreateWindowsTuple
	(
		"D3D11_VIDEO_PROCESSOR_COLOR_SPACE",
		items,
		0,
		TypeFlags_NoPointers
	);
}


// D3D11_VIDEO_PROCESSOR_STREAM
{
	let items =
	[
		[ "Enable", "BOOL" ],
		[ "OutputIndex", "UINT" ],
		[ "InputFrameOrField", "UINT" ],
		[ "PastFrames", "UINT" ],
		[ "FutureFrames", "UINT" ],
		[ "_(4)", "" ],
		[ "ppPastSurfaces", "ID3D11VideoProcessorInputView**" ],
		[ "pInputSurface", "ID3D11VideoProcessorInputView*" ],
		[ "ppFutureSurfaces", "ID3D11VideoProcessorInputView**" ],
		[ "ppPastSurfacesRight", "ID3D11VideoProcessorInputView**" ],
		[ "pInputSurfaceRight", "ID3D11VideoProcessorInputView*" ],
		[ "ppFutureSurfacesRight", "ID3D11VideoProcessorInputView**" ],
	];

	CreateWindowsTuple
	(
		"D3D11_VIDEO_PROCESSOR_STREAM",
		items,
		0,
		TypeFlags_NoPointers
	);
}

// D3D11_OMAC
{
	let items =
	[
		[ "Omac[16]", "BYTE" ],
	];

	CreateWindowsTuple
	(
		"D3D11_OMAC",
		items,
		0,
		TypeFlags_NoPointers
	);
}

// D3D11_AUTHENTICATED_CONFIGURE_OUTPUT
{
	let items =
	[
		[ "omac", "D3D11_OMAC" ],
		[ "ConfigureType", "GUID" ],
		[ "hChannel", "HANDLE" ],
		[ "SequenceNumber", "UINT" ],
		[ "ReturnCode", "HRESULT" ],
	];

	CreateWindowsTuple
	(
		"D3D11_AUTHENTICATED_CONFIGURE_OUTPUT",
		items,
		0,
		TypeFlags_NoPointers
	);
}

// D3D11_VIDEO_CONTENT_PROTECTION_CAPS
{
	let items =
	[
		[ "Caps", "UINT" ],
		[ "KeyExchangeTypeCount", "UINT" ],
		[ "BlockAlignmentSize", "UINT" ],
		[ "_(4)", "" ],
		[ "ProtectedMemorySize", "ULONGLONG" ],
	];

	CreateWindowsTuple
	(
		"D3D11_VIDEO_CONTENT_PROTECTION_CAPS",
		items,
		0,
		TypeFlags_NoPointers
	);
}



// D3D_SHADER_MACRO
{
	let items =
	[
		[ "Name", "LPCSTR" ],
		[ "Definition", "LPCSTR" ],
	];

	CreateWindowsTuple
	(
		"D3D_SHADER_MACRO",
		items,
		0,
		TypeFlags_NoP |
		TypeFlags_NoLPC
	);
}


/*





*/
















c += Tabs() + "#pragma pack(pop)" + NEW_LINE;
c += NEW_LINE;

// Functions
{
	c += Tabs() + "extern \"C\"" + NEW_LINE;

	ScopeStart();

	let items =
	[
	];

	CreateFunctions(items);

	ScopeEnd();
}

c += NEW_LINE;


/*




*/




// Function Types
{
	let items =
	[
		[ "PFN_DESTRUCTION_CALLBACK", "void",
			[
				[ "pData", "void*" ],
			],
		],
	];

	CreateWindowsFunctionTypedefs(items);
}






















// Function Tuples

// ID3D11DeviceChild
{
	let items =
	[
		[ "GetDevice", "void",
			[
				[ "ppDevice", "ID3D11Device**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetPrivateData", "HRESULT",
			[
				[ "guid", "const GUID&" ],
				[ "pDataSize", "UINT*" ],
				[ "pData", "void*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "SetPrivateData", "HRESULT",
			[
				[ "guid", "const GUID&" ],
				[ "DataSize", "UINT" ],
				[ "pData", "const void*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "SetPrivateDataInterface", "HRESULT",
			[
				[ "guid", "const GUID&" ],
				[ "pData", "const IUnknown*" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"ID3D11DeviceChild : IUnknown",
		items,
		[ "novtable" ]
	);
}





// ID3D11DepthStencilState
{
	let items =
	[
		[ "GetDesc", "void",
			[
				[ "pDesc", "D3D11_DEPTH_STENCIL_DESC*" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"ID3D11DepthStencilState : ID3D11DeviceChild",
		items,
		[ "novtable" ]
	);
}






// ID3D11BlendState
{
	let items =
	[
		[ "GetDesc", "void",
			[
				[ "pDesc", "D3D11_BLEND_DESC*" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"ID3D11BlendState : ID3D11DeviceChild",
		items,
		[ "novtable" ]
	);
}






// ID3D11RasterizerState
{
	let items =
	[
		[ "GetDesc", "void",
			[
				[ "pDesc", "D3D11_RASTERIZER_DESC*" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"ID3D11RasterizerState : ID3D11DeviceChild",
		items,
		[ "novtable" ]
	);
}







// ID3D11Resource
{
	let items =
	[
		[ "GetType", "void",
			[
				[ "pResourceDimension", "D3D11_RESOURCE_DIMENSION*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "SetEvictionPriority", "void",
			[
				[ "EvictionPriority", "UINT" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetEvictionPriority", "UINT",
			[
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"ID3D11Resource : ID3D11DeviceChild",
		items,
		[ "novtable" ]
	);
}























// ID3D11Buffer
{
	let items =
	[
		[ "GetDesc", "void",
			[
				[ "pDesc", "D3D11_BUFFER_DESC*" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"ID3D11Buffer : ID3D11Resource",
		items,
		[ "novtable" ]
	);
}








// ID3D11Texture1D
{
	let items =
	[
		[ "GetDesc", "void",
			[
				[ "pDesc", "D3D11_TEXTURE1D_DESC*" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"ID3D11Texture1D : ID3D11Resource",
		items,
		[ "novtable" ]
	);
}






// ID3D11Texture2D
{
	let items =
	[
		[ "GetDesc", "void",
			[
				[ "pDesc", "D3D11_TEXTURE2D_DESC*" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"ID3D11Texture2D : ID3D11Resource",
		items,
		[ "novtable" ]
	);
}







// ID3D11Texture3D
{
	let items =
	[
		[ "GetDesc", "void",
			[
				[ "pDesc", "D3D11_TEXTURE3D_DESC*" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"ID3D11Texture3D : ID3D11Resource",
		items,
		[ "novtable" ]
	);
}






// ID3D11View
{
	let items =
	[
		[ "GetResource", "void",
			[
				[ "ppResource", "ID3D11Resource**" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"ID3D11View : ID3D11DeviceChild",
		items,
		[ "novtable" ]
	);
}





// ID3D11ShaderResourceView
{
	let items =
	[
		[ "GetDesc", "void",
			[
				[ "pDesc", "D3D11_SHADER_RESOURCE_VIEW_DESC*" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"ID3D11ShaderResourceView : ID3D11View",
		items,
		[ "novtable" ]
	);
}











// ID3D11RenderTargetView
{
	let items =
	[
		[ "GetDesc", "void",
			[
				[ "pDesc", "D3D11_RENDER_TARGET_VIEW_DESC*" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"ID3D11RenderTargetView : ID3D11View",
		items,
		[ "novtable" ]
	);
}





// ID3D11DepthStencilView
{
	let items =
	[
		[ "GetDesc", "void",
			[
				[ "pDesc", "D3D11_DEPTH_STENCIL_VIEW_DESC*" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"ID3D11DepthStencilView : ID3D11View",
		items,
		[ "novtable" ]
	);
}













// ID3D11UnorderedAccessView
{
	let items =
	[
		[ "GetDesc", "void",
			[
				[ "pDesc", "D3D11_UNORDERED_ACCESS_VIEW_DESC*" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"ID3D11UnorderedAccessView : ID3D11View",
		items,
		[ "novtable" ]
	);
}





// ID3D11VertexShader
{
	let items =
	[
	];

	CreateWindowsFunctionTuple
	(
		"ID3D11VertexShader : ID3D11DeviceChild",
		items,
		[ "novtable" ]
	);
}














// ID3D11HullShader
{
	let items =
	[
	];

	CreateWindowsFunctionTuple
	(
		"ID3D11HullShader : ID3D11DeviceChild",
		items,
		[ "novtable" ]
	);
}














// ID3D11DomainShader
{
	let items =
	[
	];

	CreateWindowsFunctionTuple
	(
		"ID3D11DomainShader : ID3D11DeviceChild",
		items,
		[ "novtable" ]
	);
}















// ID3D11GeometryShader
{
	let items =
	[
	];

	CreateWindowsFunctionTuple
	(
		"ID3D11GeometryShader : ID3D11DeviceChild",
		items,
		[ "novtable" ]
	);
}





// ID3D11PixelShader
{
	let items =
	[
	];

	CreateWindowsFunctionTuple
	(
		"ID3D11PixelShader : ID3D11DeviceChild",
		items,
		[ "novtable" ]
	);
}





// ID3D11ComputeShader
{
	let items =
	[
	];

	CreateWindowsFunctionTuple
	(
		"ID3D11ComputeShader : ID3D11DeviceChild",
		items,
		[ "novtable" ]
	);
}







// ID3D11InputLayout
{
	let items =
	[
	];

	CreateWindowsFunctionTuple
	(
		"ID3D11InputLayout : ID3D11DeviceChild",
		items,
		[ "novtable" ]
	);
}





// ID3D11SamplerState
{
	let items =
	[
		[ "GetDesc", "void",
			[
				[ "pDesc", "D3D11_SAMPLER_DESC*" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"ID3D11SamplerState : ID3D11DeviceChild",
		items,
		[ "novtable" ]
	);
}






// ID3D11Asynchronous
{
	let items =
	[
		[ "GetDataSize", "UINT",
			[
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"ID3D11Asynchronous : ID3D11DeviceChild",
		items,
		[ "novtable" ]
	);
}






// ID3D11Query
{
	let items =
	[
		[ "GetDesc", "void",
			[
				[ "pDesc", "D3D11_QUERY_DESC*" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"ID3D11Query : ID3D11Asynchronous",
		items,
		[ "novtable" ]
	);
}





// ID3D11Predicate
{
	let items =
	[
	];

	CreateWindowsFunctionTuple
	(
		"ID3D11Predicate : ID3D11Query",
		items,
		[ "novtable" ]
	);
}






// ID3D11Counter
{
	let items =
	[
		[ "GetDesc", "void",
			[
				[ "pDesc", "D3D11_COUNTER_DESC*" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"ID3D11Counter : ID3D11Asynchronous",
		items,
		[ "novtable" ]
	);
}






// ID3D11ClassInstance
{
	let items =
	[
		[ "GetClassLinkage", "void",
			[
				[ "ppLinkage", "ID3D11ClassLinkage**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetDesc", "void",
			[
				[ "pDesc", "D3D11_CLASS_INSTANCE_DESC*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetInstanceName", "void",
			[
				[ "pInstanceName", "LPSTR" ],
				[ "pBufferLength", "SIZE_T*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetTypeName", "void",
			[
				[ "pTypeName", "LPSTR" ],
				[ "pBufferLength", "SIZE_T*" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"ID3D11ClassInstance : ID3D11DeviceChild",
		items,
		[ "novtable" ]
	);
}






// ID3D11ClassLinkage
{
	let items =
	[
		[ "GetClassInstance", "HRESULT",
			[
				[ "pClassInstanceName", "LPCSTR" ],
				[ "InstanceIndex", "UINT" ],
				[ "ppInstance", "ID3D11ClassInstance**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CreateClassInstance", "HRESULT",
			[
				[ "pClassTypeName", "LPCSTR" ],
				[ "ConstantBufferOffset", "UINT" ],
				[ "ConstantVectorOffset", "UINT" ],
				[ "TextureOffset", "UINT" ],
				[ "SamplerOffset", "UINT" ],
				[ "ppInstance", "ID3D11ClassInstance**" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"ID3D11ClassLinkage : ID3D11DeviceChild",
		items,
		[ "novtable" ]
	);
}






// ID3D11CommandList
{
	let items =
	[
		[ "GetContextFlags", "UINT",
			[
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"ID3D11CommandList : ID3D11DeviceChild",
		items,
		[ "novtable" ]
	);
}






// ID3D11DeviceContext
{
	let items =
	[
		[ "VSSetConstantBuffers", "void",
			[
				[ "StartSlot", "UINT" ],
				[ "NumBuffers", "UINT" ],
				[ "ppConstantBuffers", "ID3D11Buffer*const*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "PSSetShaderResources", "void",
			[
				[ "StartSlot", "UINT" ],
				[ "NumViews", "UINT" ],
				[ "ppShaderResourceViews", "ID3D11ShaderResourceView*const*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "PSSetShader", "void",
			[
				[ "pPixelShader", "ID3D11PixelShader*" ],
				[ "ppClassInstances", "ID3D11ClassInstance*const*" ],
				[ "NumClassInstances", "UINT" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "PSSetSamplers", "void",
			[
				[ "StartSlot", "UINT" ],
				[ "NumSamplers", "UINT" ],
				[ "ppSamplers", "ID3D11SamplerState*const*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VSSetShader", "void",
			[
				[ "pVertexShader", "ID3D11VertexShader*" ],
				[ "ppClassInstances", "ID3D11ClassInstance*const*" ],
				[ "NumClassInstances", "UINT" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "DrawIndexed", "void",
			[
				[ "IndexCount", "UINT" ],
				[ "StartIndexLocation", "UINT" ],
				[ "BaseVertexLocation", "INT" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "Draw", "void",
			[
				[ "VertexCount", "UINT" ],
				[ "StartVertexLocation", "UINT" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "Map", "HRESULT",
			[
				[ "pResource", "ID3D11Resource*" ],
				[ "Subresource", "UINT" ],
				[ "MapType", "D3D11_MAP" ],
				[ "MapFlags", "UINT" ],
				[ "pMappedResource", "D3D11_MAPPED_SUBRESOURCE*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "Unmap", "void",
			[
				[ "pResource", "ID3D11Resource*" ],
				[ "Subresource", "UINT" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "PSSetConstantBuffers", "void",
			[
				[ "StartSlot", "UINT" ],
				[ "NumBuffers", "UINT" ],
				[ "ppConstantBuffers", "ID3D11Buffer*const*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "IASetInputLayout", "void",
			[
				[ "pInputLayout", "ID3D11InputLayout*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "IASetVertexBuffers", "void",
			[
				[ "StartSlot", "UINT" ],
				[ "NumBuffers", "UINT" ],
				[ "ppVertexBuffers", "ID3D11Buffer*const*" ],
				[ "pStrides", "const UINT*" ],
				[ "pOffsets", "const UINT*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "IASetIndexBuffer", "void",
			[
				[ "pIndexBuffer", "ID3D11Buffer*" ],
				[ "Format", "DXGI_FORMAT" ],
				[ "Offset", "UINT" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "DrawIndexedInstanced", "void",
			[
				[ "IndexCountPerInstance", "UINT" ],
				[ "InstanceCount", "UINT" ],
				[ "StartIndexLocation", "UINT" ],
				[ "BaseVertexLocation", "INT" ],
				[ "StartInstanceLocation", "UINT" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "DrawInstanced", "void",
			[
				[ "VertexCountPerInstance", "UINT" ],
				[ "InstanceCount", "UINT" ],
				[ "StartVertexLocation", "UINT" ],
				[ "StartInstanceLocation", "UINT" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GSSetConstantBuffers", "void",
			[
				[ "StartSlot", "UINT" ],
				[ "NumBuffers", "UINT" ],
				[ "ppConstantBuffers", "ID3D11Buffer*const*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GSSetShader", "void",
			[
				[ "pShader", "ID3D11GeometryShader*" ],
				[ "ppClassInstances", "ID3D11ClassInstance*const*" ],
				[ "NumClassInstances", "UINT" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "IASetPrimitiveTopology", "void",
			[
				[ "Topology", "D3D11_PRIMITIVE_TOPOLOGY" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VSSetShaderResources", "void",
			[
				[ "StartSlot", "UINT" ],
				[ "NumViews", "UINT" ],
				[ "ppShaderResourceViews", "ID3D11ShaderResourceView*const*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VSSetSamplers", "void",
			[
				[ "StartSlot", "UINT" ],
				[ "NumSamplers", "UINT" ],
				[ "ppSamplers", "ID3D11SamplerState*const*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "Begin", "void",
			[
				[ "pAsync", "ID3D11Asynchronous*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "End", "void",
			[
				[ "pAsync", "ID3D11Asynchronous*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetData", "HRESULT",
			[
				[ "pAsync", "ID3D11Asynchronous*" ],
				[ "pData", "void*" ],
				[ "DataSize", "UINT" ],
				[ "GetDataFlags", "UINT" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "SetPredication", "void",
			[
				[ "pPredicate", "ID3D11Predicate*" ],
				[ "PredicateValue", "BOOL" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GSSetShaderResources", "void",
			[
				[ "StartSlot", "UINT" ],
				[ "NumViews", "UINT" ],
				[ "ppShaderResourceViews", "ID3D11ShaderResourceView*const*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GSSetSamplers", "void",
			[
				[ "StartSlot", "UINT" ],
				[ "NumSamplers", "UINT" ],
				[ "ppSamplers", "ID3D11SamplerState*const*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "OMSetRenderTargets", "void",
			[
				[ "NumViews", "UINT" ],
				[ "ppRenderTargetViews", "ID3D11RenderTargetView*const*" ],
				[ "pDepthStencilView", "ID3D11DepthStencilView*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "OMSetRenderTargetsAndUnorderedAccessViews", "void",
			[
				[ "NumRTVs", "UINT" ],
				[ "ppRenderTargetViews", "ID3D11RenderTargetView*const*" ],
				[ "pDepthStencilView", "ID3D11DepthStencilView*" ],
				[ "UAVStartSlot", "UINT" ],
				[ "NumUAVs", "UINT" ],
				[ "ppUnorderedAccessViews", "ID3D11UnorderedAccessView*const*" ],
				[ "pUAVInitialCounts", "const UINT*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "OMSetBlendState", "void",
			[
				[ "pBlendState", "ID3D11BlendState*" ],
				[ "BlendFactor[4]", "const FLOAT" ],
				[ "SampleMask", "UINT" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "OMSetDepthStencilState", "void",
			[
				[ "pDepthStencilState", "ID3D11DepthStencilState*" ],
				[ "StencilRef", "UINT" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "SOSetTargets", "void",
			[
				[ "NumBuffers", "UINT" ],
				[ "ppSOTargets", "ID3D11Buffer*const*" ],
				[ "pOffsets", "const UINT*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "DrawAuto", "void",
			[
			],
			FunctionFlags_PureVirtual
		],
		[ "DrawIndexedInstancedIndirect", "void",
			[
				[ "pBufferForArgs", "ID3D11Buffer*" ],
				[ "AlignedByteOffsetForArgs", "UINT" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "DrawInstancedIndirect", "void",
			[
				[ "pBufferForArgs", "ID3D11Buffer*" ],
				[ "AlignedByteOffsetForArgs", "UINT" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "Dispatch", "void",
			[
				[ "ThreadGroupCountX", "UINT" ],
				[ "ThreadGroupCountY", "UINT" ],
				[ "ThreadGroupCountZ", "UINT" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "DispatchIndirect", "void",
			[
				[ "pBufferForArgs", "ID3D11Buffer*" ],
				[ "AlignedByteOffsetForArgs", "UINT" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "RSSetState", "void",
			[
				[ "pRasterizerState", "ID3D11RasterizerState*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "RSSetViewports", "void",
			[
				[ "NumViewports", "UINT" ],
				[ "pViewports", "const D3D11_VIEWPORT*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "RSSetScissorRects", "void",
			[
				[ "NumRects", "UINT" ],
				[ "pRects", "const D3D11_RECT*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CopySubresourceRegion", "void",
			[
				[ "pDstResource", "ID3D11Resource*" ],
				[ "DstSubresource", "UINT" ],
				[ "DstX", "UINT" ],
				[ "DstY", "UINT" ],
				[ "DstZ", "UINT" ],
				[ "pSrcResource", "ID3D11Resource*" ],
				[ "SrcSubresource", "UINT" ],
				[ "pSrcBox", "const D3D11_BOX*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CopyResource", "void",
			[
				[ "pDstResource", "ID3D11Resource*" ],
				[ "pSrcResource", "ID3D11Resource*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "UpdateSubresource", "void",
			[
				[ "pDstResource", "ID3D11Resource*" ],
				[ "DstSubresource", "UINT" ],
				[ "pDstBox", "const D3D11_BOX*" ],
				[ "pSrcData", "const void*" ],
				[ "SrcRowPitch", "UINT" ],
				[ "SrcDepthPitch", "UINT" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CopyStructureCount", "void",
			[
				[ "pDstBuffer", "ID3D11Buffer*" ],
				[ "DstAlignedByteOffset", "UINT" ],
				[ "pSrcView", "ID3D11UnorderedAccessView*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "ClearRenderTargetView", "void",
			[
				[ "pRenderTargetView", "ID3D11RenderTargetView*" ],
				[ "ColorRGBA[4]", "const FLOAT" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "ClearUnorderedAccessViewUint", "void",
			[
				[ "pUnorderedAccessView", "ID3D11UnorderedAccessView*" ],
				[ "Values[4]", "const UINT" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "ClearUnorderedAccessViewFloat", "void",
			[
				[ "pUnorderedAccessView", "ID3D11UnorderedAccessView*" ],
				[ "Values[4]", "const FLOAT" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "ClearDepthStencilView", "void",
			[
				[ "pDepthStencilView", "ID3D11DepthStencilView*" ],
				[ "ClearFlags", "UINT" ],
				[ "Depth", "FLOAT" ],
				[ "Stencil", "UINT8" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GenerateMips", "void",
			[
				[ "pShaderResourceView", "ID3D11ShaderResourceView*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "SetResourceMinLOD", "void",
			[
				[ "pResource", "ID3D11Resource*" ],
				[ "MinLOD", "FLOAT" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetResourceMinLOD", "FLOAT",
			[
				[ "pResource", "ID3D11Resource*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "ResolveSubresource", "void",
			[
				[ "pDstResource", "ID3D11Resource*" ],
				[ "DstSubresource", "UINT" ],
				[ "pSrcResource", "ID3D11Resource*" ],
				[ "SrcSubresource", "UINT" ],
				[ "Format", "DXGI_FORMAT" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "ExecuteCommandList", "void",
			[
				[ "pCommandList", "ID3D11CommandList*" ],
				[ "RestoreContextState", "BOOL" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "HSSetShaderResources", "void",
			[
				[ "StartSlot", "UINT" ],
				[ "NumViews", "UINT" ],
				[ "ppShaderResourceViews", "ID3D11ShaderResourceView*const*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "HSSetShader", "void",
			[
				[ "pHullShader", "ID3D11HullShader*" ],
				[ "ppClassInstances", "ID3D11ClassInstance*const*" ],
				[ "NumClassInstances", "UINT" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "HSSetSamplers", "void",
			[
				[ "StartSlot", "UINT" ],
				[ "NumSamplers", "UINT" ],
				[ "ppSamplers", "ID3D11SamplerState*const*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "HSSetConstantBuffers", "void",
			[
				[ "StartSlot", "UINT" ],
				[ "NumBuffers", "UINT" ],
				[ "ppConstantBuffers", "ID3D11Buffer*const*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "DSSetShaderResources", "void",
			[
				[ "StartSlot", "UINT" ],
				[ "NumViews", "UINT" ],
				[ "ppShaderResourceViews", "ID3D11ShaderResourceView*const*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "DSSetShader", "void",
			[
				[ "pDomainShader", "ID3D11DomainShader*" ],
				[ "ppClassInstances", "ID3D11ClassInstance*const*" ],
				[ "NumClassInstances", "UINT" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "DSSetSamplers", "void",
			[
				[ "StartSlot", "UINT" ],
				[ "NumSamplers", "UINT" ],
				[ "ppSamplers", "ID3D11SamplerState*const*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "DSSetConstantBuffers", "void",
			[
				[ "StartSlot", "UINT" ],
				[ "NumBuffers", "UINT" ],
				[ "ppConstantBuffers", "ID3D11Buffer*const*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CSSetShaderResources", "void",
			[
				[ "StartSlot", "UINT" ],
				[ "NumViews", "UINT" ],
				[ "ppShaderResourceViews", "ID3D11ShaderResourceView*const*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CSSetUnorderedAccessViews", "void",
			[
				[ "StartSlot", "UINT" ],
				[ "NumUAVs", "UINT" ],
				[ "ppUnorderedAccessViews", "ID3D11UnorderedAccessView*const*" ],
				[ "pUAVInitialCounts", "const UINT*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CSSetShader", "void",
			[
				[ "pComputeShader", "ID3D11ComputeShader*" ],
				[ "ppClassInstances", "ID3D11ClassInstance*const*" ],
				[ "NumClassInstances", "UINT" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CSSetSamplers", "void",
			[
				[ "StartSlot", "UINT" ],
				[ "NumSamplers", "UINT" ],
				[ "ppSamplers", "ID3D11SamplerState*const*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CSSetConstantBuffers", "void",
			[
				[ "StartSlot", "UINT" ],
				[ "NumBuffers", "UINT" ],
				[ "ppConstantBuffers", "ID3D11Buffer*const*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VSGetConstantBuffers", "void",
			[
				[ "StartSlot", "UINT" ],
				[ "NumBuffers", "UINT" ],
				[ "ppConstantBuffers", "ID3D11Buffer**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "PSGetShaderResources", "void",
			[
				[ "StartSlot", "UINT" ],
				[ "NumViews", "UINT" ],
				[ "ppShaderResourceViews", "ID3D11ShaderResourceView**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "PSGetShader", "void",
			[
				[ "ppPixelShader", "ID3D11PixelShader**" ],
				[ "ppClassInstances", "ID3D11ClassInstance**" ],
				[ "pNumClassInstances", "UINT*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "PSGetSamplers", "void",
			[
				[ "StartSlot", "UINT" ],
				[ "NumSamplers", "UINT" ],
				[ "ppSamplers", "ID3D11SamplerState**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VSGetShader", "void",
			[
				[ "ppVertexShader", "ID3D11VertexShader**" ],
				[ "ppClassInstances", "ID3D11ClassInstance**" ],
				[ "pNumClassInstances", "UINT*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "PSGetConstantBuffers", "void",
			[
				[ "StartSlot", "UINT" ],
				[ "NumBuffers", "UINT" ],
				[ "ppConstantBuffers", "ID3D11Buffer**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "IAGetInputLayout", "void",
			[
				[ "ppInputLayout", "ID3D11InputLayout**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "IAGetVertexBuffers", "void",
			[
				[ "StartSlot", "UINT" ],
				[ "NumBuffers", "UINT" ],
				[ "ppVertexBuffers", "ID3D11Buffer**" ],
				[ "pStrides", "UINT*" ],
				[ "pOffsets", "UINT*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "IAGetIndexBuffer", "void",
			[
				[ "pIndexBuffer", "ID3D11Buffer**" ],
				[ "Format", "DXGI_FORMAT*" ],
				[ "Offset", "UINT*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GSGetConstantBuffers", "void",
			[
				[ "StartSlot", "UINT" ],
				[ "NumBuffers", "UINT" ],
				[ "ppConstantBuffers", "ID3D11Buffer**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GSGetShader", "void",
			[
				[ "ppGeometryShader", "ID3D11GeometryShader**" ],
				[ "ppClassInstances", "ID3D11ClassInstance**" ],
				[ "pNumClassInstances", "UINT*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "IAGetPrimitiveTopology", "void",
			[
				[ "pTopology", "D3D11_PRIMITIVE_TOPOLOGY*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VSGetShaderResources", "void",
			[
				[ "StartSlot", "UINT" ],
				[ "NumViews", "UINT" ],
				[ "ppShaderResourceViews", "ID3D11ShaderResourceView**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VSGetSamplers", "void",
			[
				[ "StartSlot", "UINT" ],
				[ "NumSamplers", "UINT" ],
				[ "ppSamplers", "ID3D11SamplerState**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetPredication", "void",
			[
				[ "ppPredicate", "ID3D11Predicate**" ],
				[ "pPredicateValue", "BOOL*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GSGetShaderResources", "void",
			[
				[ "StartSlot", "UINT" ],
				[ "NumViews", "UINT" ],
				[ "ppShaderResourceViews", "ID3D11ShaderResourceView**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GSGetSamplers", "void",
			[
				[ "StartSlot", "UINT" ],
				[ "NumSamplers", "UINT" ],
				[ "ppSamplers", "ID3D11SamplerState**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "OMGetRenderTargets", "void",
			[
				[ "NumViews", "UINT" ],
				[ "ppRenderTargetViews", "ID3D11RenderTargetView**" ],
				[ "ppDepthStencilView", "ID3D11DepthStencilView**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "OMGetRenderTargetsAndUnorderedAccessViews", "void",
			[
				[ "NumRTVs", "UINT" ],
				[ "ppRenderTargetViews", "ID3D11RenderTargetView**" ],
				[ "ppDepthStencilView", "ID3D11DepthStencilView**" ],
				[ "UAVStartSlot", "UINT" ],
				[ "NumUAVs", "UINT" ],
				[ "ppUnorderedAccessViews", "ID3D11UnorderedAccessView**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "OMGetBlendState", "void",
			[
				[ "ppBlendState", "ID3D11BlendState**" ],
				[ "BlendFactor[4]", "FLOAT" ],
				[ "pSampleMask", "UINT*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "OMGetDepthStencilState", "void",
			[
				[ "ppDepthStencilState", "ID3D11DepthStencilState**" ],
				[ "pStencilRef", "UINT*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "SOGetTargets", "void",
			[
				[ "NumBuffers", "UINT" ],
				[ "ppSOTargets", "ID3D11Buffer**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "RSGetState", "void",
			[
				[ "ppRasterizerState", "ID3D11RasterizerState**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "RSGetViewports", "void",
			[
				[ "pNumViewports", "UINT*" ],
				[ "pViewports", "D3D11_VIEWPORT*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "RSGetScissorRects", "void",
			[
				[ "pNumRects", "UINT*" ],
				[ "pRects", "D3D11_RECT*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "HSGetShaderResources", "void",
			[
				[ "StartSlot", "UINT" ],
				[ "NumViews", "UINT" ],
				[ "ppShaderResourceViews", "ID3D11ShaderResourceView**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "HSGetShader", "void",
			[
				[ "ppHullShader", "ID3D11HullShader**" ],
				[ "ppClassInstances", "ID3D11ClassInstance**" ],
				[ "pNumClassInstances", "UINT*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "HSGetSamplers", "void",
			[
				[ "StartSlot", "UINT" ],
				[ "NumSamplers", "UINT" ],
				[ "ppSamplers", "ID3D11SamplerState**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "HSGetConstantBuffers", "void",
			[
				[ "StartSlot", "UINT" ],
				[ "NumBuffers", "UINT" ],
				[ "ppConstantBuffers", "ID3D11Buffer**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "DSGetShaderResources", "void",
			[
				[ "StartSlot", "UINT" ],
				[ "NumViews", "UINT" ],
				[ "ppShaderResourceViews", "ID3D11ShaderResourceView**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "DSGetShader", "void",
			[
				[ "ppDomainShader", "ID3D11DomainShader**" ],
				[ "ppClassInstances", "ID3D11ClassInstance**" ],
				[ "pNumClassInstances", "UINT*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "DSGetSamplers", "void",
			[
				[ "StartSlot", "UINT" ],
				[ "NumSamplers", "UINT" ],
				[ "ppSamplers", "ID3D11SamplerState**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "DSGetConstantBuffers", "void",
			[
				[ "StartSlot", "UINT" ],
				[ "NumBuffers", "UINT" ],
				[ "ppConstantBuffers", "ID3D11Buffer**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CSGetShaderResources", "void",
			[
				[ "StartSlot", "UINT" ],
				[ "NumViews", "UINT" ],
				[ "ppShaderResourceViews", "ID3D11ShaderResourceView**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CSGetUnorderedAccessViews", "void",
			[
				[ "StartSlot", "UINT" ],
				[ "NumUAVs", "UINT" ],
				[ "ppUnorderedAccessViews", "ID3D11UnorderedAccessView**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CSGetShader", "void",
			[
				[ "ppComputeShader", "ID3D11ComputeShader**" ],
				[ "ppClassInstances", "ID3D11ClassInstance**" ],
				[ "pNumClassInstances", "UINT*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CSGetSamplers", "void",
			[
				[ "StartSlot", "UINT" ],
				[ "NumSamplers", "UINT" ],
				[ "ppSamplers", "ID3D11SamplerState**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CSGetConstantBuffers", "void",
			[
				[ "StartSlot", "UINT" ],
				[ "NumBuffers", "UINT" ],
				[ "ppConstantBuffers", "ID3D11Buffer**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "ClearState", "void",
			[
			],
			FunctionFlags_PureVirtual
		],
		[ "Flush", "void",
			[
			],
			FunctionFlags_PureVirtual
		],
		[ "GetType", "D3D11_DEVICE_CONTEXT_TYPE",
			[
			],
			FunctionFlags_PureVirtual
		],
		[ "GetContextFlags", "UINT",
			[
			],
			FunctionFlags_PureVirtual
		],
		[ "FinishCommandList", "HRESULT",
			[
				[ "RestoreDeferredContextState", "BOOL" ],
				[ "ppCommandList", "ID3D11CommandList**" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"ID3D11DeviceContext : ID3D11DeviceChild",
		items,
		[ "novtable" ]
	);
}





// ID3D11VideoDecoder
{
	let items =
	[
		[ "GetCreationParameters", "HRESULT",
			[
				[ "pVideoDesc", "D3D11_VIDEO_DECODER_DESC*" ],
				[ "pConfig", "D3D11_VIDEO_DECODER_CONFIG*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetDriverHandle", "HRESULT",
			[
				[ "pDriverHandle", "HANDLE*" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"ID3D11VideoDecoder : ID3D11DeviceChild",
		items,
		[ "novtable" ]
	);
}





// ID3D11VideoProcessorEnumerator
{
	let items =
	[
		[ "GetVideoProcessorContentDesc", "HRESULT",
			[
				[ "pContentDesc", "D3D11_VIDEO_PROCESSOR_CONTENT_DESC*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CheckVideoProcessorFormat", "HRESULT",
			[
				[ "Format", "DXGI_FORMAT" ],
				[ "pFlags", "UINT*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetVideoProcessorCaps", "HRESULT",
			[
				[ "pCaps", "D3D11_VIDEO_PROCESSOR_CAPS*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetVideoProcessorRateConversionCaps", "HRESULT",
			[
				[ "TypeIndex", "UINT" ],
				[ "pCaps", "D3D11_VIDEO_PROCESSOR_RATE_CONVERSION_CAPS*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetVideoProcessorCustomRate", "HRESULT",
			[
				[ "TypeIndex", "UINT" ],
				[ "CustomRateIndex", "UINT" ],
				[ "pRate", "D3D11_VIDEO_PROCESSOR_CUSTOM_RATE*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetVideoProcessorFilterRange", "HRESULT",
			[
				[ "Filter", "D3D11_VIDEO_PROCESSOR_FILTER" ],
				[ "pRange", "D3D11_VIDEO_PROCESSOR_FILTER_RANGE*" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"ID3D11VideoProcessorEnumerator : ID3D11DeviceChild",
		items,
		[ "novtable" ]
	);
}





// ID3D11VideoProcessor
{
	let items =
	[
		[ "GetContentDesc", "void",
			[
				[ "pDesc", "D3D11_VIDEO_PROCESSOR_CONTENT_DESC*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetRateConversionCaps", "void",
			[
				[ "pCaps", "D3D11_VIDEO_PROCESSOR_RATE_CONVERSION_CAPS*" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"ID3D11VideoProcessor : ID3D11DeviceChild",
		items,
		[ "novtable" ]
	);
}





// ID3D11AuthenticatedChannel
{
	let items =
	[
		[ "GetCertificateSize", "HRESULT",
			[
				[ "pCertificateSize", "UINT*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetCertificate", "HRESULT",
			[
				[ "CertificateSize", "UINT" ],
				[ "pCertificate", "BYTE*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetChannelHandle", "void",
			[
				[ "pChannelHandle", "HANDLE*" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"ID3D11AuthenticatedChannel : ID3D11DeviceChild",
		items,
		[ "novtable" ]
	);
}





// ID3D11CryptoSession
{
	let items =
	[
		[ "GetCryptoType", "void",
			[
				[ "pCryptoType", "GUID*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetDecoderProfile", "void",
			[
				[ "pDecoderProfile", "GUID*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetCertificateSize", "HRESULT",
			[
				[ "pCertificateSize", "UINT*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetCertificate", "HRESULT",
			[
				[ "CertificateSize", "UINT" ],
				[ "pCertificate", "BYTE*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetCryptoSessionHandle", "void",
			[
				[ "pCryptoSessionHandle", "HANDLE*" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"ID3D11CryptoSession : ID3D11DeviceChild",
		items,
		[ "novtable" ]
	);
}





// ID3D11VideoDecoderOutputView
{
	let items =
	[
		[ "GetDesc", "void",
			[
				[ "pDesc", "D3D11_VIDEO_DECODER_OUTPUT_VIEW_DESC*" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"ID3D11VideoDecoderOutputView : ID3D11View",
		items,
		[ "novtable" ]
	);
}





// ID3D11VideoProcessorInputView
{
	let items =
	[
		[ "GetDesc", "void",
			[
				[ "pDesc", "D3D11_VIDEO_PROCESSOR_INPUT_VIEW_DESC*" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"ID3D11VideoProcessorInputView : ID3D11View",
		items,
		[ "novtable" ]
	);
}





// ID3D11VideoProcessorOutputView
{
	let items =
	[
		[ "GetDesc", "void",
			[
				[ "pDesc", "D3D11_VIDEO_PROCESSOR_OUTPUT_VIEW_DESC*" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"ID3D11VideoProcessorOutputView : ID3D11View",
		items,
		[ "novtable" ]
	);
}





// ID3D11VideoContext
{
	let items =
	[
		[ "GetDecoderBuffer", "HRESULT",
			[
				[ "pDecoder", "ID3D11VideoDecoder*" ],
				[ "Type", "D3D11_VIDEO_DECODER_BUFFER_TYPE" ],
				[ "pBufferSize", "UINT*" ],
				[ "ppBuffer", "void**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "ReleaseDecoderBuffer", "HRESULT",
			[
				[ "pDecoder", "ID3D11VideoDecoder*" ],
				[ "Type", "D3D11_VIDEO_DECODER_BUFFER_TYPE" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "DecoderBeginFrame", "HRESULT",
			[
				[ "pDecoder", "ID3D11VideoDecoder*" ],
				[ "pView", "ID3D11VideoDecoderOutputView*" ],
				[ "ContentKeySize", "UINT" ],
				[ "pContentKey", "const void*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "DecoderEndFrame", "HRESULT",
			[
				[ "pDecoder", "ID3D11VideoDecoder*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "SubmitDecoderBuffers", "HRESULT",
			[
				[ "pDecoder", "ID3D11VideoDecoder*" ],
				[ "NumBuffers", "UINT" ],
				[ "pBufferDesc", "const D3D11_VIDEO_DECODER_BUFFER_DESC*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "DecoderExtension", "APP_DEPRECATED_HRESULT",
			[
				[ "pDecoder", "ID3D11VideoDecoder*" ],
				[ "pExtensionData", "const D3D11_VIDEO_DECODER_EXTENSION*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VideoProcessorSetOutputTargetRect", "void",
			[
				[ "pVideoProcessor", "ID3D11VideoProcessor*" ],
				[ "Enable", "BOOL" ],
				[ "pRect", "const RECT*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VideoProcessorSetOutputBackgroundColor", "void",
			[
				[ "pVideoProcessor", "ID3D11VideoProcessor*" ],
				[ "YCbCr", "BOOL" ],
				[ "pColor", "const D3D11_VIDEO_COLOR*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VideoProcessorSetOutputColorSpace", "void",
			[
				[ "pVideoProcessor", "ID3D11VideoProcessor*" ],
				[ "pColorSpace", "const D3D11_VIDEO_PROCESSOR_COLOR_SPACE*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VideoProcessorSetOutputAlphaFillMode", "void",
			[
				[ "pVideoProcessor", "ID3D11VideoProcessor*" ],
				[ "AlphaFillMode", "D3D11_VIDEO_PROCESSOR_ALPHA_FILL_MODE" ],
				[ "StreamIndex", "UINT" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VideoProcessorSetOutputConstriction", "void",
			[
				[ "pVideoProcessor", "ID3D11VideoProcessor*" ],
				[ "Enable", "BOOL" ],
				[ "Size", "SIZE" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VideoProcessorSetOutputStereoMode", "void",
			[
				[ "pVideoProcessor", "ID3D11VideoProcessor*" ],
				[ "Enable", "BOOL" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VideoProcessorSetOutputExtension", "APP_DEPRECATED_HRESULT",
			[
				[ "pVideoProcessor", "ID3D11VideoProcessor*" ],
				[ "pExtensionGuid", "const GUID*" ],
				[ "DataSize", "UINT" ],
				[ "pData", "void*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VideoProcessorGetOutputTargetRect", "void",
			[
				[ "pVideoProcessor", "ID3D11VideoProcessor*" ],
				[ "Enabled", "BOOL*" ],
				[ "pRect", "RECT*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VideoProcessorGetOutputBackgroundColor", "void",
			[
				[ "pVideoProcessor", "ID3D11VideoProcessor*" ],
				[ "pYCbCr", "BOOL*" ],
				[ "pColor", "D3D11_VIDEO_COLOR*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VideoProcessorGetOutputColorSpace", "void",
			[
				[ "pVideoProcessor", "ID3D11VideoProcessor*" ],
				[ "pColorSpace", "D3D11_VIDEO_PROCESSOR_COLOR_SPACE*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VideoProcessorGetOutputAlphaFillMode", "void",
			[
				[ "pVideoProcessor", "ID3D11VideoProcessor*" ],
				[ "pAlphaFillMode", "D3D11_VIDEO_PROCESSOR_ALPHA_FILL_MODE*" ],
				[ "pStreamIndex", "UINT*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VideoProcessorGetOutputConstriction", "void",
			[
				[ "pVideoProcessor", "ID3D11VideoProcessor*" ],
				[ "pEnabled", "BOOL*" ],
				[ "pSize", "SIZE*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VideoProcessorGetOutputStereoMode", "void",
			[
				[ "pVideoProcessor", "ID3D11VideoProcessor*" ],
				[ "pEnabled", "BOOL*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VideoProcessorGetOutputExtension", "APP_DEPRECATED_HRESULT",
			[
				[ "pVideoProcessor", "ID3D11VideoProcessor*" ],
				[ "pExtensionGuid", "const GUID*" ],
				[ "DataSize", "UINT" ],
				[ "pData", "void*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VideoProcessorSetStreamFrameFormat", "void",
			[
				[ "pVideoProcessor", "ID3D11VideoProcessor*" ],
				[ "StreamIndex", "UINT" ],
				[ "FrameFormat", "D3D11_VIDEO_FRAME_FORMAT" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VideoProcessorSetStreamColorSpace", "void",
			[
				[ "pVideoProcessor", "ID3D11VideoProcessor*" ],
				[ "StreamIndex", "UINT" ],
				[ "pColorSpace", "const D3D11_VIDEO_PROCESSOR_COLOR_SPACE*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VideoProcessorSetStreamOutputRate", "void",
			[
				[ "pVideoProcessor", "ID3D11VideoProcessor*" ],
				[ "StreamIndex", "UINT" ],
				[ "OutputRate", "D3D11_VIDEO_PROCESSOR_OUTPUT_RATE" ],
				[ "RepeatFrame", "BOOL" ],
				[ "pCustomRate", "const DXGI_RATIONAL*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VideoProcessorSetStreamSourceRect", "void",
			[
				[ "pVideoProcessor", "ID3D11VideoProcessor*" ],
				[ "StreamIndex", "UINT" ],
				[ "Enable", "BOOL" ],
				[ "pRect", "const RECT*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VideoProcessorSetStreamDestRect", "void",
			[
				[ "pVideoProcessor", "ID3D11VideoProcessor*" ],
				[ "StreamIndex", "UINT" ],
				[ "Enable", "BOOL" ],
				[ "pRect", "const RECT*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VideoProcessorSetStreamAlpha", "void",
			[
				[ "pVideoProcessor", "ID3D11VideoProcessor*" ],
				[ "StreamIndex", "UINT" ],
				[ "Enable", "BOOL" ],
				[ "Alpha", "FLOAT" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VideoProcessorSetStreamPalette", "void",
			[
				[ "pVideoProcessor", "ID3D11VideoProcessor*" ],
				[ "StreamIndex", "UINT" ],
				[ "Count", "UINT" ],
				[ "pEntries", "const UINT*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VideoProcessorSetStreamPixelAspectRatio", "void",
			[
				[ "pVideoProcessor", "ID3D11VideoProcessor*" ],
				[ "StreamIndex", "UINT" ],
				[ "Enable", "BOOL" ],
				[ "pSourceAspectRatio", "const DXGI_RATIONAL*" ],
				[ "pDestinationAspectRatio", "const DXGI_RATIONAL*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VideoProcessorSetStreamLumaKey", "void",
			[
				[ "pVideoProcessor", "ID3D11VideoProcessor*" ],
				[ "StreamIndex", "UINT" ],
				[ "Enable", "BOOL" ],
				[ "Lower", "FLOAT" ],
				[ "Upper", "FLOAT" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VideoProcessorSetStreamStereoFormat", "void",
			[
				[ "pVideoProcessor", "ID3D11VideoProcessor*" ],
				[ "StreamIndex", "UINT" ],
				[ "Enable", "BOOL" ],
				[ "Format", "D3D11_VIDEO_PROCESSOR_STEREO_FORMAT" ],
				[ "LeftViewFrame0", "BOOL" ],
				[ "BaseViewFrame0", "BOOL" ],
				[ "FlipMode", "D3D11_VIDEO_PROCESSOR_STEREO_FLIP_MODE" ],
				[ "MonoOffset", "int" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VideoProcessorSetStreamAutoProcessingMode", "void",
			[
				[ "pVideoProcessor", "ID3D11VideoProcessor*" ],
				[ "StreamIndex", "UINT" ],
				[ "Enable", "BOOL" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VideoProcessorSetStreamFilter", "void",
			[
				[ "pVideoProcessor", "ID3D11VideoProcessor*" ],
				[ "StreamIndex", "UINT" ],
				[ "Filter", "D3D11_VIDEO_PROCESSOR_FILTER" ],
				[ "Enable", "BOOL" ],
				[ "Level", "int" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VideoProcessorSetStreamExtension", "APP_DEPRECATED_HRESULT",
			[
				[ "pVideoProcessor", "ID3D11VideoProcessor*" ],
				[ "StreamIndex", "UINT" ],
				[ "pExtensionGuid", "const GUID*" ],
				[ "DataSize", "UINT" ],
				[ "pData", "void*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VideoProcessorGetStreamFrameFormat", "void",
			[
				[ "pVideoProcessor", "ID3D11VideoProcessor*" ],
				[ "StreamIndex", "UINT" ],
				[ "pFrameFormat", "D3D11_VIDEO_FRAME_FORMAT*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VideoProcessorGetStreamColorSpace", "void",
			[
				[ "pVideoProcessor", "ID3D11VideoProcessor*" ],
				[ "StreamIndex", "UINT" ],
				[ "pColorSpace", "D3D11_VIDEO_PROCESSOR_COLOR_SPACE*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VideoProcessorGetStreamOutputRate", "void",
			[
				[ "pVideoProcessor", "ID3D11VideoProcessor*" ],
				[ "StreamIndex", "UINT" ],
				[ "pOutputRate", "D3D11_VIDEO_PROCESSOR_OUTPUT_RATE*" ],
				[ "pRepeatFrame", "BOOL*" ],
				[ "pCustomRate", "DXGI_RATIONAL*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VideoProcessorGetStreamSourceRect", "void",
			[
				[ "pVideoProcessor", "ID3D11VideoProcessor*" ],
				[ "StreamIndex", "UINT" ],
				[ "pEnabled", "BOOL*" ],
				[ "pRect", "RECT*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VideoProcessorGetStreamDestRect", "void",
			[
				[ "pVideoProcessor", "ID3D11VideoProcessor*" ],
				[ "StreamIndex", "UINT" ],
				[ "pEnabled", "BOOL*" ],
				[ "pRect", "RECT*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VideoProcessorGetStreamAlpha", "void",
			[
				[ "pVideoProcessor", "ID3D11VideoProcessor*" ],
				[ "StreamIndex", "UINT" ],
				[ "pEnabled", "BOOL*" ],
				[ "pAlpha", "FLOAT*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VideoProcessorGetStreamPalette", "void",
			[
				[ "pVideoProcessor", "ID3D11VideoProcessor*" ],
				[ "StreamIndex", "UINT" ],
				[ "Count", "UINT" ],
				[ "pEntries", "UINT*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VideoProcessorGetStreamPixelAspectRatio", "void",
			[
				[ "pVideoProcessor", "ID3D11VideoProcessor*" ],
				[ "StreamIndex", "UINT" ],
				[ "pEnabled", "BOOL*" ],
				[ "pSourceAspectRatio", "DXGI_RATIONAL*" ],
				[ "pDestinationAspectRatio", "DXGI_RATIONAL*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VideoProcessorGetStreamLumaKey", "void",
			[
				[ "pVideoProcessor", "ID3D11VideoProcessor*" ],
				[ "StreamIndex", "UINT" ],
				[ "pEnabled", "BOOL*" ],
				[ "pLower", "FLOAT*" ],
				[ "pUpper", "FLOAT*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VideoProcessorGetStreamStereoFormat", "void",
			[
				[ "pVideoProcessor", "ID3D11VideoProcessor*" ],
				[ "StreamIndex", "UINT" ],
				[ "pEnable", "BOOL*" ],
				[ "pFormat", "D3D11_VIDEO_PROCESSOR_STEREO_FORMAT*" ],
				[ "pLeftViewFrame0", "BOOL*" ],
				[ "pBaseViewFrame0", "BOOL*" ],
				[ "pFlipMode", "D3D11_VIDEO_PROCESSOR_STEREO_FLIP_MODE*" ],
				[ "MonoOffset", "int*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VideoProcessorGetStreamAutoProcessingMode", "void",
			[
				[ "pVideoProcessor", "ID3D11VideoProcessor*" ],
				[ "StreamIndex", "UINT" ],
				[ "pEnabled", "BOOL*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VideoProcessorGetStreamFilter", "void",
			[
				[ "pVideoProcessor", "ID3D11VideoProcessor*" ],
				[ "StreamIndex", "UINT" ],
				[ "Filter", "D3D11_VIDEO_PROCESSOR_FILTER" ],
				[ "pEnabled", "BOOL*" ],
				[ "pLevel", "int*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VideoProcessorGetStreamExtension", "APP_DEPRECATED_HRESULT",
			[
				[ "pVideoProcessor", "ID3D11VideoProcessor*" ],
				[ "StreamIndex", "UINT" ],
				[ "pExtensionGuid", "const GUID*" ],
				[ "DataSize", "UINT" ],
				[ "pData", "void*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VideoProcessorBlt", "HRESULT",
			[
				[ "pVideoProcessor", "ID3D11VideoProcessor*" ],
				[ "pView", "ID3D11VideoProcessorOutputView*" ],
				[ "OutputFrame", "UINT" ],
				[ "StreamCount", "UINT" ],
				[ "pStreams", "const D3D11_VIDEO_PROCESSOR_STREAM*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "NegotiateCryptoSessionKeyExchange", "HRESULT",
			[
				[ "pCryptoSession", "ID3D11CryptoSession*" ],
				[ "DataSize", "UINT" ],
				[ "pData", "void*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "EncryptionBlt", "void",
			[
				[ "pCryptoSession", "ID3D11CryptoSession*" ],
				[ "pSrcSurface", "ID3D11Texture2D*" ],
				[ "pDstSurface", "ID3D11Texture2D*" ],
				[ "IVSize", "UINT" ],
				[ "pIV", "void*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "DecryptionBlt", "void",
			[
				[ "pCryptoSession", "ID3D11CryptoSession*" ],
				[ "pSrcSurface", "ID3D11Texture2D*" ],
				[ "pDstSurface", "ID3D11Texture2D*" ],
				[ "pEncryptedBlockInfo", "D3D11_ENCRYPTED_BLOCK_INFO*" ],
				[ "ContentKeySize", "UINT" ],
				[ "pContentKey", "const void*" ],
				[ "IVSize", "UINT" ],
				[ "pIV", "void*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "StartSessionKeyRefresh", "void",
			[
				[ "pCryptoSession", "ID3D11CryptoSession*" ],
				[ "RandomNumberSize", "UINT" ],
				[ "pRandomNumber", "void*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "FinishSessionKeyRefresh", "void",
			[
				[ "pCryptoSession", "ID3D11CryptoSession*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetEncryptionBltKey", "HRESULT",
			[
				[ "pCryptoSession", "ID3D11CryptoSession*" ],
				[ "KeySize", "UINT" ],
				[ "pReadbackKey", "void*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "NegotiateAuthenticatedChannelKeyExchange", "HRESULT",
			[
				[ "pChannel", "ID3D11AuthenticatedChannel*" ],
				[ "DataSize", "UINT" ],
				[ "pData", "void*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "QueryAuthenticatedChannel", "HRESULT",
			[
				[ "pChannel", "ID3D11AuthenticatedChannel*" ],
				[ "InputSize", "UINT" ],
				[ "pInput", "const void*" ],
				[ "OutputSize", "UINT" ],
				[ "pOutput", "void*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "ConfigureAuthenticatedChannel", "HRESULT",
			[
				[ "pChannel", "ID3D11AuthenticatedChannel*" ],
				[ "InputSize", "UINT" ],
				[ "pInput", "const void*" ],
				[ "pOutput", "D3D11_AUTHENTICATED_CONFIGURE_OUTPUT*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VideoProcessorSetStreamRotation", "void",
			[
				[ "pVideoProcessor", "ID3D11VideoProcessor*" ],
				[ "StreamIndex", "UINT" ],
				[ "Enable", "BOOL" ],
				[ "Rotation", "D3D11_VIDEO_PROCESSOR_ROTATION" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "VideoProcessorGetStreamRotation", "void",
			[
				[ "pVideoProcessor", "ID3D11VideoProcessor*" ],
				[ "StreamIndex", "UINT" ],
				[ "pEnable", "BOOL*" ],
				[ "pRotation", "D3D11_VIDEO_PROCESSOR_ROTATION*" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"ID3D11VideoContext : ID3D11DeviceChild",
		items,
		[ "novtable" ]
	);
}





// ID3D11VideoDevice
{
	let items =
	[
		[ "CreateVideoDecoder", "HRESULT",
			[
				[ "pVideoDesc", "const D3D11_VIDEO_DECODER_DESC*" ],
				[ "pConfig", "const D3D11_VIDEO_DECODER_CONFIG*" ],
				[ "ppDecoder", "ID3D11VideoDecoder**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CreateVideoProcessor", "HRESULT",
			[
				[ "pEnum", "ID3D11VideoProcessorEnumerator*" ],
				[ "RateConversionIndex", "UINT" ],
				[ "ppVideoProcessor", "ID3D11VideoProcessor**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CreateAuthenticatedChannel", "HRESULT",
			[
				[ "ChannelType", "D3D11_AUTHENTICATED_CHANNEL_TYPE" ],
				[ "ppAuthenticatedChannel", "ID3D11AuthenticatedChannel**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CreateCryptoSession", "HRESULT",
			[
				[ "pCryptoType", "const GUID*" ],
				[ "pDecoderProfile", "const GUID*" ],
				[ "pKeyExchangeType", "const GUID*" ],
				[ "ppCryptoSession", "ID3D11CryptoSession**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CreateVideoDecoderOutputView", "HRESULT",
			[
				[ "pResource", "ID3D11Resource*" ],
				[ "pDesc", "const D3D11_VIDEO_DECODER_OUTPUT_VIEW_DESC*" ],
				[ "ppVDOVView", "ID3D11VideoDecoderOutputView**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CreateVideoProcessorInputView", "HRESULT",
			[
				[ "pResource", "ID3D11Resource*" ],
				[ "pEnum", "ID3D11VideoProcessorEnumerator*" ],
				[ "pDesc", "const D3D11_VIDEO_PROCESSOR_INPUT_VIEW_DESC*" ],
				[ "ppVPIView", "ID3D11VideoProcessorInputView**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CreateVideoProcessorOutputView", "HRESULT",
			[
				[ "pResource", "ID3D11Resource*" ],
				[ "pEnum", "ID3D11VideoProcessorEnumerator*" ],
				[ "pDesc", "const D3D11_VIDEO_PROCESSOR_OUTPUT_VIEW_DESC*" ],
				[ "ppVPOView", "ID3D11VideoProcessorOutputView**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CreateVideoProcessorEnumerator", "HRESULT",
			[
				[ "pDesc", "const D3D11_VIDEO_PROCESSOR_CONTENT_DESC*" ],
				[ "ppEnum", "ID3D11VideoProcessorEnumerator**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetVideoDecoderProfileCount", "UINT",
			[
			],
			FunctionFlags_PureVirtual
		],
		[ "GetVideoDecoderProfile", "HRESULT",
			[
				[ "Index", "UINT" ],
				[ "pDecoderProfile", "GUID*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CheckVideoDecoderFormat", "HRESULT",
			[
				[ "pDecoderProfile", "const GUID*" ],
				[ "Format", "DXGI_FORMAT" ],
				[ "pSupported", "BOOL*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetVideoDecoderConfigCount", "HRESULT",
			[
				[ "pDesc", "const D3D11_VIDEO_DECODER_DESC*" ],
				[ "pCount", "UINT*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetVideoDecoderConfig", "HRESULT",
			[
				[ "pDesc", "const D3D11_VIDEO_DECODER_DESC*" ],
				[ "Index", "UINT" ],
				[ "pConfig", "D3D11_VIDEO_DECODER_CONFIG*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetContentProtectionCaps", "HRESULT",
			[
				[ "pCryptoType", "const GUID*" ],
				[ "pDecoderProfile", "const GUID*" ],
				[ "pCaps", "D3D11_VIDEO_CONTENT_PROTECTION_CAPS*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CheckCryptoKeyExchange", "HRESULT",
			[
				[ "pCryptoType", "const GUID*" ],
				[ "pDecoderProfile", "const GUID*" ],
				[ "Index", "UINT" ],
				[ "pKeyExchangeType", "GUID*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "SetPrivateData", "HRESULT",
			[
				[ "guid", "const GUID&" ],
				[ "DataSize", "UINT" ],
				[ "pData", "const void*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "SetPrivateDataInterface", "HRESULT",
			[
				[ "guid", "const GUID&" ],
				[ "pData", "const IUnknown*" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"ID3D11VideoDevice : IUnknown",
		items,
		[ "novtable" ]
	);
}





// ID3D11Device
{
	let items =
	[
		[ "CreateBuffer", "HRESULT",
			[
				[ "pDesc", "const D3D11_BUFFER_DESC*" ],
				[ "pInitialData", "const D3D11_SUBRESOURCE_DATA*" ],
				[ "ppBuffer", "ID3D11Buffer**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CreateTexture1D", "HRESULT",
			[
				[ "pDesc", "const D3D11_TEXTURE1D_DESC*" ],
				[ "pInitialData", "const D3D11_SUBRESOURCE_DATA*" ],
				[ "ppTexture1D", "ID3D11Texture1D**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CreateTexture2D", "HRESULT",
			[
				[ "pDesc", "const D3D11_TEXTURE2D_DESC*" ],
				[ "pInitialData", "const D3D11_SUBRESOURCE_DATA*" ],
				[ "ppTexture2D", "ID3D11Texture2D**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CreateTexture3D", "HRESULT",
			[
				[ "pDesc", "const D3D11_TEXTURE3D_DESC*" ],
				[ "pInitialData", "const D3D11_SUBRESOURCE_DATA*" ],
				[ "ppTexture3D", "ID3D11Texture3D**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CreateShaderResourceView", "HRESULT",
			[
				[ "pResource", "ID3D11Resource*" ],
				[ "pDesc", "const D3D11_SHADER_RESOURCE_VIEW_DESC*" ],
				[ "ppSRView", "ID3D11ShaderResourceView**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CreateUnorderedAccessView", "HRESULT",
			[
				[ "pResource", "ID3D11Resource*" ],
				[ "pDesc", "const D3D11_UNORDERED_ACCESS_VIEW_DESC*" ],
				[ "ppUAView", "ID3D11UnorderedAccessView**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CreateRenderTargetView", "HRESULT",
			[
				[ "pResource", "ID3D11Resource*" ],
				[ "pDesc", "const D3D11_RENDER_TARGET_VIEW_DESC*" ],
				[ "ppRTView", "ID3D11RenderTargetView**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CreateDepthStencilView", "HRESULT",
			[
				[ "pResource", "ID3D11Resource*" ],
				[ "pDesc", "const D3D11_DEPTH_STENCIL_VIEW_DESC*" ],
				[ "ppDepthStencilView", "ID3D11DepthStencilView**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CreateInputLayout", "HRESULT",
			[
				[ "pInputElementDescs", "const D3D11_INPUT_ELEMENT_DESC*" ],
				[ "NumElements", "UINT" ],
				[ "pShaderBytecodeWithInputSignature", "const void*" ],
				[ "BytecodeLength", "SIZE_T" ],
				[ "ppInputLayout", "ID3D11InputLayout**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CreateVertexShader", "HRESULT",
			[
				[ "pShaderBytecode", "const void*" ],
				[ "BytecodeLength", "SIZE_T" ],
				[ "pClassLinkage", "ID3D11ClassLinkage*" ],
				[ "ppVertexShader", "ID3D11VertexShader**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CreateGeometryShader", "HRESULT",
			[
				[ "pShaderBytecode", "const void*" ],
				[ "BytecodeLength", "SIZE_T" ],
				[ "pClassLinkage", "ID3D11ClassLinkage*" ],
				[ "ppGeometryShader", "ID3D11GeometryShader**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CreateGeometryShaderWithStreamOutput", "HRESULT",
			[
				[ "pShaderBytecode", "const void*" ],
				[ "BytecodeLength", "SIZE_T" ],
				[ "pSODeclaration", "const D3D11_SO_DECLARATION_ENTRY*" ],
				[ "NumEntries", "UINT" ],
				[ "pBufferStrides", "const UINT*" ],
				[ "NumStrides", "UINT" ],
				[ "RasterizedStream", "UINT" ],
				[ "pClassLinkage", "ID3D11ClassLinkage*" ],
				[ "ppGeometryShader", "ID3D11GeometryShader**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CreatePixelShader", "HRESULT",
			[
				[ "pShaderBytecode", "const void*" ],
				[ "BytecodeLength", "SIZE_T" ],
				[ "pClassLinkage", "ID3D11ClassLinkage*" ],
				[ "ppPixelShader", "ID3D11PixelShader**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CreateHullShader", "HRESULT",
			[
				[ "pShaderBytecode", "const void*" ],
				[ "BytecodeLength", "SIZE_T" ],
				[ "pClassLinkage", "ID3D11ClassLinkage*" ],
				[ "ppHullShader", "ID3D11HullShader**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CreateDomainShader", "HRESULT",
			[
				[ "pShaderBytecode", "const void*" ],
				[ "BytecodeLength", "SIZE_T" ],
				[ "pClassLinkage", "ID3D11ClassLinkage*" ],
				[ "ppDomainShader", "ID3D11DomainShader**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CreateComputeShader", "HRESULT",
			[
				[ "pShaderBytecode", "const void*" ],
				[ "BytecodeLength", "SIZE_T" ],
				[ "pClassLinkage", "ID3D11ClassLinkage*" ],
				[ "ppComputeShader", "ID3D11ComputeShader**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CreateClassLinkage", "HRESULT",
			[
				[ "ppLinkage", "ID3D11ClassLinkage**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CreateBlendState", "HRESULT",
			[
				[ "pBlendStateDesc", "const D3D11_BLEND_DESC*" ],
				[ "ppBlendState", "ID3D11BlendState**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CreateDepthStencilState", "HRESULT",
			[
				[ "pDepthStencilDesc", "const D3D11_DEPTH_STENCIL_DESC*" ],
				[ "ppDepthStencilState", "ID3D11DepthStencilState**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CreateRasterizerState", "HRESULT",
			[
				[ "pRasterizerDesc", "const D3D11_RASTERIZER_DESC*" ],
				[ "ppRasterizerState", "ID3D11RasterizerState**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CreateSamplerState", "HRESULT",
			[
				[ "pSamplerDesc", "const D3D11_SAMPLER_DESC*" ],
				[ "ppSamplerState", "ID3D11SamplerState**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CreateQuery", "HRESULT",
			[
				[ "pQueryDesc", "const D3D11_QUERY_DESC*" ],
				[ "ppQuery", "ID3D11Query**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CreatePredicate", "HRESULT",
			[
				[ "pPredicateDesc", "const D3D11_QUERY_DESC*" ],
				[ "ppPredicate", "ID3D11Predicate**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CreateCounter", "HRESULT",
			[
				[ "pCounterDesc", "const D3D11_COUNTER_DESC*" ],
				[ "ppCounter", "ID3D11Counter**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CreateDeferredContext", "HRESULT",
			[
				[ "ContextFlags", "UINT" ],
				[ "ppDeferredContext", "ID3D11DeviceContext**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "OpenSharedResource", "HRESULT",
			[
				[ "hResource", "HANDLE" ],
				[ "ReturnedInterface", "const IID&" ],
				[ "ppResource", "void**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CheckFormatSupport", "HRESULT",
			[
				[ "Format", "DXGI_FORMAT" ],
				[ "pFormatSupport", "UINT*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CheckMultisampleQualityLevels", "HRESULT",
			[
				[ "Format", "DXGI_FORMAT" ],
				[ "SampleCount", "UINT" ],
				[ "pNumQualityLevels", "UINT*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CheckCounterInfo", "void",
			[
				[ "pCounterInfo", "D3D11_COUNTER_INFO*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CheckCounter", "HRESULT",
			[
				[ "pDesc", "const D3D11_COUNTER_DESC*" ],
				[ "pType", "D3D11_COUNTER_TYPE*" ],
				[ "pActiveCounters", "UINT*" ],
				[ "szName", "LPSTR" ],
				[ "pNameLength", "UINT*" ],
				[ "szUnits", "LPSTR" ],
				[ "pUnitsLength", "UINT*" ],
				[ "szDescription", "LPSTR" ],
				[ "pDescriptionLength", "UINT*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CheckFeatureSupport", "HRESULT",
			[
				[ "Feature", "D3D11_FEATURE" ],
				[ "pFeatureSupportData", "void*" ],
				[ "FeatureSupportDataSize", "UINT" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetPrivateData", "HRESULT",
			[
				[ "guid", "const GUID&" ],
				[ "pDataSize", "UINT*" ],
				[ "pData", "void*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "SetPrivateData", "HRESULT",
			[
				[ "guid", "const GUID&" ],
				[ "DataSize", "UINT" ],
				[ "pData", "const void*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "SetPrivateDataInterface", "HRESULT",
			[
				[ "guid", "const GUID&" ],
				[ "pData", "const IUnknown*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetFeatureLevel", "D3D_FEATURE_LEVEL",
			[
			],
			FunctionFlags_PureVirtual
		],
		[ "GetCreationFlags", "UINT",
			[
			],
			FunctionFlags_PureVirtual
		],
		[ "GetDeviceRemovedReason", "HRESULT",
			[
			],
			FunctionFlags_PureVirtual
		],
		[ "GetImmediateContext", "void",
			[
				[ "ppImmediateContext", "ID3D11DeviceContext**" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "SetExceptionMode", "HRESULT",
			[
				[ "RaiseFlags", "UINT" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetExceptionMode", "UINT",
			[
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"ID3D11Device : IUnknown",
		items,
		[ "novtable" ]
	);
}




// ID3D10Blob
{
	let items =
	[
		[ "GetBufferPointer", "LPVOID",
			[
			],
			FunctionFlags_PureVirtual
		],
		[ "GetBufferSize", "SIZE_T",
			[
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"ID3D10Blob : IUnknown",
		items,
		[ "novtable" ]
	);
}

CreateWindowsTypedef
(
	"ID3DBlob",
	"ID3D10Blob",
	8,
	TypeFlags_NoPointers
);



/*



*/




// ID3DDestructionNotifier
{
	let items =
	[
		[ "RegisterDestructionCallback", "HRESULT",
			[
				[ "callbackFn", "PFN_DESTRUCTION_CALLBACK" ],
				[ "pData", "void*" ],
				[ "pCallbackID", "UINT*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "UnregisterDestructionCallback", "HRESULT",
			[
				[ "callbackID", "UINT" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"ID3DDestructionNotifier : IUnknown",
		items,
		[ "novtable" ]
	);
}



// ID3DInclude
{
	let items =
	[
		[ "Open", "HRESULT",
			[
				[ "IncludeType", "D3D_INCLUDE_TYPE" ],
				[ "pFileName", "LPCSTR" ],
				[ "pParentData", "LPCVOID" ],
				[ "ppData", "LPCVOID*" ],
				[ "pBytes", "UINT*" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "Close", "HRESULT",
			[
				[ "pData", "LPCVOID" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"ID3DInclude",
		items,
		[ "novtable" ]
	);
}


/*




*/

















// Functions
{
	let items =
	[
		[ "D3D11CreateDeviceAndSwapChain", "HRESULT",
			[
				[ "pAdapter", "IDXGIAdapter*" ],
				[ "DriverType", "D3D_DRIVER_TYPE" ],
				[ "Software", "HMODULE" ],
				[ "Flags", "UINT" ],
				[ "pFeatureLevels", "const D3D_FEATURE_LEVEL*" ],
				[ "FeatureLevels", "UINT" ],
				[ "SDKVersion", "UINT" ],
				[ "pSwapChainDesc", "const DXGI_SWAP_CHAIN_DESC*" ],
				[ "ppSwapChain", "IDXGISwapChain**" ],
				[ "ppDevice", "ID3D11Device**" ],
				[ "pFeatureLevel", "D3D_FEATURE_LEVEL*" ],
				[ "ppImmediateContext", "ID3D11DeviceContext**" ],
			],
			FunctionFlags_ExternC
		],
		[ "D3DCompile", "HRESULT",
			[
				[ "pSrcData", "LPCVOID" ],
				[ "SrcDataSize", "SIZE_T" ],
				[ "pSourceName", "LPCSTR" ],
				[ "pDefines", "const D3D_SHADER_MACRO*" ],
				[ "pInclude", "ID3DInclude*" ],
				[ "pEntrypoint", "LPCSTR" ],
				[ "pTarget", "LPCSTR" ],
				[ "Flags1", "UINT" ],
				[ "Flags2", "UINT" ],
				[ "ppCode", "ID3DBlob**" ],
				[ "ppErrorMsgs", "ID3DBlob**" ],
			],
			FunctionFlags_ExternC
		],
	];

	CreateFunctions(items);

	// ScopeEnd();
}


/*








*/
















c += NEW_LINE;

ModuleEnd();

CleanStream();

fs.writeFileSync("../Core/D3D11.ixx", c);

// Verify

ModuleVerify();

CleanStream();

fs.writeFileSync("../verifyD3D11.cpp", c);

ClearAll();
}

// #endregion

// #region DI8
{
console.log("DI8");

ModuleStart
(
	"DI8",
	[
		"Windows"
	],
	[
		"Windows"
	]
);

// Forward Declarations

{
	let names =
	[
		"IDirectInput8A",
		"IDirectInput8W",
		"IDirectInputDevice8A",
		"IDirectInputDevice8W",
		"IDirectInputEffect",
	];

	CreateForwardDeclarations
	(
		names,
		"struct"
	);

	CreateForwardDeclarations
	(
		names,
		"const GUID",
		"extern \"C\" ",
		"IID_"
	);
}

{
	let names =
	[
		"XAxis",
		"YAxis",
		"ZAxis",
		"RxAxis",
		"RyAxis",
		"RzAxis",
		"Slider",
		"Button",
		"Key",
		"POV",
		"Unknown",
		"SysMouse",
		"SysKeyboard",
		"Joystick",
		"SysMouseEm",
		"SysMouseEm2",
		"SysKeyboardEm",
		"SysKeyboardEm2",
		"ConstantForce",
		"RampForce",
		"Square",
		"Sine",
		"Triangle",
		"SawtoothUp",
		"SawtoothDown",
		"Spring",
		"Damper",
		"Inertia",
		"Friction",
		"CustomForce",
	];

	CreateForwardDeclarations
	(
		names,
		"const GUID",
		"extern \"C\" ",
		"GUID_"
	);
}
















// Types
{
	let items =
	[
		[ "LPDIRECTINPUTDEVICE8A", "IDirectInputDevice8A*", 8, TypeFlags_NoPointers ],
		[ "LPDIRECTINPUTDEVICE8W", "IDirectInputDevice8W*", 8, TypeFlags_NoPointers ],
		[ "LPDIRECTINPUTEFFECT"  , "IDirectInputEffect*"  , 8, TypeFlags_NoPointers ],
		[ "D3DCOLOR"             , "DWORD"                , 4, TypeFlags_NoPointers ],
	];

	CreateWindowsTypedefs(items);
}

// Enums
// {
// 	let items =
// 	[
// 	];

// 	CreateWindowsEnum
// 	(
// 		"",
// 		items
// 	);
// }




{
	let items =
	[
		[ "DIK_ESCAPE", "0x01", "" ],
		[ "DIK_1", "0x02", "" ],
		[ "DIK_2", "0x03", "" ],
		[ "DIK_3", "0x04", "" ],
		[ "DIK_4", "0x05", "" ],
		[ "DIK_5", "0x06", "" ],
		[ "DIK_6", "0x07", "" ],
		[ "DIK_7", "0x08", "" ],
		[ "DIK_8", "0x09", "" ],
		[ "DIK_9", "0x0A", "" ],
		[ "DIK_0", "0x0B", "" ],
		[ "DIK_MINUS", "0x0C", "" ],
		[ "DIK_EQUALS", "0x0D", "" ],
		[ "DIK_BACK", "0x0E", "" ],
		[ "DIK_TAB", "0x0F", "" ],
		[ "DIK_Q", "0x10", "" ],
		[ "DIK_W", "0x11", "" ],
		[ "DIK_E", "0x12", "" ],
		[ "DIK_R", "0x13", "" ],
		[ "DIK_T", "0x14", "" ],
		[ "DIK_Y", "0x15", "" ],
		[ "DIK_U", "0x16", "" ],
		[ "DIK_I", "0x17", "" ],
		[ "DIK_O", "0x18", "" ],
		[ "DIK_P", "0x19", "" ],
		[ "DIK_LBRACKET", "0x1A", "" ],
		[ "DIK_RBRACKET", "0x1B", "" ],
		[ "DIK_RETURN", "0x1C", "" ],
		[ "DIK_LCONTROL", "0x1D", "" ],
		[ "DIK_A", "0x1E", "" ],
		[ "DIK_S", "0x1F", "" ],
		[ "DIK_D", "0x20", "" ],
		[ "DIK_F", "0x21", "" ],
		[ "DIK_G", "0x22", "" ],
		[ "DIK_H", "0x23", "" ],
		[ "DIK_J", "0x24", "" ],
		[ "DIK_K", "0x25", "" ],
		[ "DIK_L", "0x26", "" ],
		[ "DIK_SEMICOLON", "0x27", "" ],
		[ "DIK_APOSTROPHE", "0x28", "" ],
		[ "DIK_GRAVE", "0x29", "" ],
		[ "DIK_LSHIFT", "0x2A", "" ],
		[ "DIK_BACKSLASH", "0x2B", "" ],
		[ "DIK_Z", "0x2C", "" ],
		[ "DIK_X", "0x2D", "" ],
		[ "DIK_C", "0x2E", "" ],
		[ "DIK_V", "0x2F", "" ],
		[ "DIK_B", "0x30", "" ],
		[ "DIK_N", "0x31", "" ],
		[ "DIK_M", "0x32", "" ],
		[ "DIK_COMMA", "0x33", "" ],
		[ "DIK_PERIOD", "0x34", "" ],
		[ "DIK_SLASH", "0x35", "" ],
		[ "DIK_RSHIFT", "0x36", "" ],
		[ "DIK_MULTIPLY", "0x37", "" ],
		[ "DIK_LMENU", "0x38", "" ],
		[ "DIK_SPACE", "0x39", "" ],
		[ "DIK_CAPITAL", "0x3A", "" ],
		[ "DIK_F1", "0x3B", "" ],
		[ "DIK_F2", "0x3C", "" ],
		[ "DIK_F3", "0x3D", "" ],
		[ "DIK_F4", "0x3E", "" ],
		[ "DIK_F5", "0x3F", "" ],
		[ "DIK_F6", "0x40", "" ],
		[ "DIK_F7", "0x41", "" ],
		[ "DIK_F8", "0x42", "" ],
		[ "DIK_F9", "0x43", "" ],
		[ "DIK_F10", "0x44", "" ],
		[ "DIK_NUMLOCK", "0x45", "" ],
		[ "DIK_SCROLL", "0x46", "" ],
		[ "DIK_NUMPAD7", "0x47", "" ],
		[ "DIK_NUMPAD8", "0x48", "" ],
		[ "DIK_NUMPAD9", "0x49", "" ],
		[ "DIK_SUBTRACT", "0x4A", "" ],
		[ "DIK_NUMPAD4", "0x4B", "" ],
		[ "DIK_NUMPAD5", "0x4C", "" ],
		[ "DIK_NUMPAD6", "0x4D", "" ],
		[ "DIK_ADD", "0x4E", "" ],
		[ "DIK_NUMPAD1", "0x4F", "" ],
		[ "DIK_NUMPAD2", "0x50", "" ],
		[ "DIK_NUMPAD3", "0x51", "" ],
		[ "DIK_NUMPAD0", "0x52", "" ],
		[ "DIK_DECIMAL", "0x53", "" ],
		[ "DIK_OEM_102", "0x56", "" ],
		[ "DIK_F11", "0x57", "" ],
		[ "DIK_F12", "0x58", "" ],
		[ "DIK_F13", "0x64", "" ],
		[ "DIK_F14", "0x65", "" ],
		[ "DIK_F15", "0x66", "" ],
		[ "DIK_KANA", "0x70", "" ],
		[ "DIK_ABNT_C1", "0x73", "" ],
		[ "DIK_CONVERT", "0x79", "" ],
		[ "DIK_NOCONVERT", "0x7B", "" ],
		[ "DIK_YEN", "0x7D", "" ],
		[ "DIK_ABNT_C2", "0x7E", "" ],
		[ "DIK_NUMPADEQUALS", "0x8D", "" ],
		[ "DIK_PREVTRACK", "0x90", "" ],
		[ "DIK_AT", "0x91", "" ],
		[ "DIK_COLON", "0x92", "" ],
		[ "DIK_UNDERLINE", "0x93", "" ],
		[ "DIK_KANJI", "0x94", "" ],
		[ "DIK_STOP", "0x95", "" ],
		[ "DIK_AX", "0x96", "" ],
		[ "DIK_UNLABELED", "0x97", "" ],
		[ "DIK_NEXTTRACK", "0x99", "" ],
		[ "DIK_NUMPADENTER", "0x9C", "" ],
		[ "DIK_RCONTROL", "0x9D", "" ],
		[ "DIK_MUTE", "0xA0", "" ],
		[ "DIK_CALCULATOR", "0xA1", "" ],
		[ "DIK_PLAYPAUSE", "0xA2", "" ],
		[ "DIK_MEDIASTOP", "0xA4", "" ],
		[ "DIK_VOLUMEDOWN", "0xAE", "" ],
		[ "DIK_VOLUMEUP", "0xB0", "" ],
		[ "DIK_WEBHOME", "0xB2", "" ],
		[ "DIK_NUMPADCOMMA", "0xB3", "" ],
		[ "DIK_DIVIDE", "0xB5", "" ],
		[ "DIK_SYSRQ", "0xB7", "" ],
		[ "DIK_RMENU", "0xB8", "" ],
		[ "DIK_PAUSE", "0xC5", "" ],
		[ "DIK_HOME", "0xC7", "" ],
		[ "DIK_UP", "0xC8", "" ],
		[ "DIK_PRIOR", "0xC9", "" ],
		[ "DIK_LEFT", "0xCB", "" ],
		[ "DIK_RIGHT", "0xCD", "" ],
		[ "DIK_END", "0xCF", "" ],
		[ "DIK_DOWN", "0xD0", "" ],
		[ "DIK_NEXT", "0xD1", "" ],
		[ "DIK_INSERT", "0xD2", "" ],
		[ "DIK_DELETE", "0xD3", "" ],
		[ "DIK_LWIN", "0xDB", "" ],
		[ "DIK_RWIN", "0xDC", "" ],
		[ "DIK_APPS", "0xDD", "" ],
		[ "DIK_POWER", "0xDE", "" ],
		[ "DIK_SLEEP", "0xDF", "" ],
		[ "DIK_WAKE", "0xE3", "" ],
		[ "DIK_WEBSEARCH", "0xE5", "" ],
		[ "DIK_WEBFAVORITES", "0xE6", "" ],
		[ "DIK_WEBREFRESH", "0xE7", "" ],
		[ "DIK_WEBSTOP", "0xE8", "" ],
		[ "DIK_WEBFORWARD", "0xE9", "" ],
		[ "DIK_WEBBACK", "0xEA", "" ],
		[ "DIK_MYCOMPUTER", "0xEB", "" ],
		[ "DIK_MAIL", "0xEC", "" ],
		[ "DIK_MEDIASELECT", "0xED", "" ],
		[ "DIK_BACKSPACE", "DIK_BACK", "" ],
		[ "DIK_NUMPADSTAR", "DIK_MULTIPLY", "" ],
		[ "DIK_LALT", "DIK_LMENU", "" ],
		[ "DIK_CAPSLOCK", "DIK_CAPITAL", "" ],
		[ "DIK_NUMPADMINUS", "DIK_SUBTRACT", "" ],
		[ "DIK_NUMPADPLUS", "DIK_ADD", "" ],
		[ "DIK_NUMPADPERIOD", "DIK_DECIMAL", "" ],
		[ "DIK_NUMPADSLASH", "DIK_DIVIDE", "" ],
		[ "DIK_RALT", "DIK_RMENU", "" ],
		[ "DIK_UPARROW", "DIK_UP", "" ],
		[ "DIK_PGUP", "DIK_PRIOR", "" ],
		[ "DIK_LEFTARROW", "DIK_LEFT", "" ],
		[ "DIK_RIGHTARROW", "DIK_RIGHT", "" ],
		[ "DIK_DOWNARROW", "DIK_DOWN", "" ],
		[ "DIK_PGDN", "DIK_NEXT", "" ],
		[ "DIK_CIRCUMFLEX", "DIK_PREVTRACK", "" ],

		[ "DISCL_EXCLUSIVE", "0x00000001", "" ],
		[ "DISCL_NONEXCLUSIVE", "0x00000002", "" ],
		[ "DISCL_FOREGROUND", "0x00000004", "" ],
		[ "DISCL_BACKGROUND", "0x00000008", "" ],
		[ "DISCL_NOWINKEY", "0x00000010", "" ],


		[ "DI_OK", "S_OK", "" ],


	];

	CreateWindowsEnum
	(
		"",
		items
	);
}










/*




*/













// Structs

c += Tabs() + "#pragma pack(push, 1)" + NEW_LINE;
c += NEW_LINE;



// DIMOUSESTATE
{
	let items =
	[
		[ "lX", "LONG" ],
		[ "lY", "LONG" ],
		[ "lZ", "LONG" ],
		[ "rgbButtons[4]", "BYTE" ],
	];

	CreateWindowsTuple
	(
		"DIMOUSESTATE",
		items,
		0,
		TypeFlags_NoP |
		TypeFlags_NoLPC
	);
}


// DIMOUSESTATE2
{
	let items =
	[
		[ "lX", "LONG" ],
		[ "lY", "LONG" ],
		[ "lZ", "LONG" ],
		[ "rgbButtons[8]", "BYTE" ],
	];

	CreateWindowsTuple
	(
		"DIMOUSESTATE2",
		items,
		0,
		TypeFlags_NoP |
		TypeFlags_NoLPC
	);
}

// DIDEVCAPS
{
	let items =
	[
		[ "dwSize", "DWORD" ],
		[ "dwFlags", "DWORD" ],
		[ "dwDevType", "DWORD" ],
		[ "dwAxes", "DWORD" ],
		[ "dwButtons", "DWORD" ],
		[ "dwPOVs", "DWORD" ],
		[ "dwFFSamplePeriod", "DWORD" ],
		[ "dwFFMinTimeResolution", "DWORD" ],
		[ "dwFirmwareRevision", "DWORD" ],
		[ "dwHardwareRevision", "DWORD" ],
		[ "dwFFDriverVersion", "DWORD" ],
	];

	CreateWindowsTuple
	(
		"DIDEVCAPS",
		items,
		0,
		TypeFlags_NoP |
		TypeFlags_NoLPC
	);
}


// DIOBJECTDATAFORMAT
{
	let items =
	[
		[ "pguid", "const GUID*" ],
		[ "dwOfs", "DWORD" ],
		[ "dwType", "DWORD" ],
		[ "dwFlags", "DWORD" ],
		[ "_(4)", "" ],
	];

	CreateWindowsTuple
	(
		"DIOBJECTDATAFORMAT",
		items,
		0,
		TypeFlags_NoP
	);
}

// DIDATAFORMAT
{
	let items =
	[
		[ "dwSize", "DWORD" ],
		[ "dwObjSize", "DWORD" ],
		[ "dwFlags", "DWORD" ],
		[ "dwDataSize", "DWORD" ],
		[ "dwNumObjs", "DWORD" ],
		[ "_(4)", "" ],
		[ "rgodf", "LPDIOBJECTDATAFORMAT" ],
	];

	CreateWindowsTuple
	(
		"DIDATAFORMAT",
		items,
		0,
		TypeFlags_NoP
	);
}

{
	let names =
	[
		"c_dfDIMouse",
		"c_dfDIMouse2",
		"c_dfDIKeyboard",
		"c_dfDIJoystick",
		"c_dfDIJoystick2",
	];

	CreateForwardDeclarations
	(
		names,
		"const DIDATAFORMAT",
		"extern \"C\" "
	);
}





/*






*/




// DIPROPHEADER
{
	let items =
	[
		[ "dwSize", "DWORD" ],
		[ "dwHeaderSize", "DWORD" ],
		[ "dwObj", "DWORD" ],
		[ "dwHow", "DWORD" ],
	];

	CreateWindowsTuple
	(
		"DIPROPHEADER",
		items,
		0,
		TypeFlags_NoP
	);
}


// DIDEVICEOBJECTINSTANCEA
{
	let items =
	[
		[ "dwSize", "DWORD" ],
		[ "guidType", "GUID" ],
		[ "dwOfs", "DWORD" ],
		[ "dwType", "DWORD" ],
		[ "dwFlags", "DWORD" ],
		[ "tszName[260]", "CHAR" ],
		[ "dwFFMaxForce", "DWORD" ],
		[ "dwFFForceResolution", "DWORD" ],
		[ "wCollectionNumber", "WORD" ],
		[ "wDesignatorIndex", "WORD" ],
		[ "wUsagePage", "WORD" ],
		[ "wUsage", "WORD" ],
		[ "dwDimension", "DWORD" ],
		[ "wExponent", "WORD" ],
		[ "wReportId", "WORD" ],
	];

	CreateWindowsTuple
	(
		"DIDEVICEOBJECTINSTANCEA",
		items,
		0,
		TypeFlags_NoP
	);
}


// DIDEVICEOBJECTINSTANCEW
{
	let items =
	[
		[ "dwSize", "DWORD" ],
		[ "guidType", "GUID" ],
		[ "dwOfs", "DWORD" ],
		[ "dwType", "DWORD" ],
		[ "dwFlags", "DWORD" ],
		[ "tszName[260]", "WCHAR" ],
		[ "dwFFMaxForce", "DWORD" ],
		[ "dwFFForceResolution", "DWORD" ],
		[ "wCollectionNumber", "WORD" ],
		[ "wDesignatorIndex", "WORD" ],
		[ "wUsagePage", "WORD" ],
		[ "wUsage", "WORD" ],
		[ "dwDimension", "DWORD" ],
		[ "wExponent", "WORD" ],
		[ "wReportId", "WORD" ],
	];

	CreateWindowsTuple
	(
		"DIDEVICEOBJECTINSTANCEW",
		items,
		0,
		TypeFlags_NoP
	);
}

















// DIDEVICEOBJECTDATA
{
	let items =
	[
		[ "dwOfs", "DWORD" ],
		[ "dwData", "DWORD" ],
		[ "dwTimeStamp", "DWORD" ],
		[ "dwSequence", "DWORD" ],
		[ "uAppData", "UINT_PTR" ],
	];

	CreateWindowsTuple
	(
		"DIDEVICEOBJECTDATA",
		items,
		0,
		TypeFlags_NoP
	);
}


// DIDEVICEINSTANCEA
{
	let items =
	[
		[ "dwSize", "DWORD" ],
		[ "guidInstance", "GUID" ],
		[ "guidProduct", "GUID" ],
		[ "dwDevType", "DWORD" ],
		[ "tszInstanceName[260]", "CHAR" ],
		[ "tszProductName[260]", "CHAR" ],
		[ "guidFFDriver", "GUID" ],
		[ "wUsagePage", "WORD" ],
		[ "wUsage", "WORD" ],
	];

	CreateWindowsTuple
	(
		"DIDEVICEINSTANCEA",
		items,
		0,
		TypeFlags_NoP
	);
}

// DIDEVICEINSTANCEW
{
	let items =
	[
		[ "dwSize", "DWORD" ],
		[ "guidInstance", "GUID" ],
		[ "guidProduct", "GUID" ],
		[ "dwDevType", "DWORD" ],
		[ "tszInstanceName[260]", "WCHAR" ],
		[ "tszProductName[260]", "WCHAR" ],
		[ "guidFFDriver", "GUID" ],
		[ "wUsagePage", "WORD" ],
		[ "wUsage", "WORD" ],
	];

	CreateWindowsTuple
	(
		"DIDEVICEINSTANCEW",
		items,
		0,
		TypeFlags_NoP
	);
}


// DIENVELOPE
{
	let items =
	[
		[ "dwSize", "DWORD" ],
		[ "dwAttackLevel", "DWORD" ],
		[ "dwAttackTime", "DWORD" ],
		[ "dwFadeLevel", "DWORD" ],
		[ "dwFadeTime", "DWORD" ],
	];

	CreateWindowsTuple
	(
		"DIENVELOPE",
		items,
		0,
		TypeFlags_NoP
	);
}


// DIEFFECT
{
	let items =
	[
		[ "dwSize", "DWORD" ],
		[ "dwFlags", "DWORD" ],
		[ "dwDuration", "DWORD" ],
		[ "dwSamplePeriod", "DWORD" ],
		[ "dwGain", "DWORD" ],
		[ "dwTriggerButton", "DWORD" ],
		[ "dwTriggerRepeatInterval", "DWORD" ],
		[ "cAxes", "DWORD" ],
		[ "rgdwAxes", "LPDWORD" ],
		[ "rglDirection", "LPLONG" ],
		[ "lpEnvelope", "LPDIENVELOPE" ],
		[ "cbTypeSpecificParams", "DWORD" ],
		[ "_(4)", "" ],
		[ "lpvTypeSpecificParams", "LPVOID" ],
		[ "dwStartDelay", "DWORD" ],
		[ "_(4)", "" ],
	];

	CreateWindowsTuple
	(
		"DIEFFECT",
		items,
		0,
		TypeFlags_NoP
	);
}

// DIFILEEFFECT
{
	let items =
	[
		[ "dwSize", "DWORD" ],
		[ "GuidEffect", "GUID" ],
		[ "_(4)", "" ],
		[ "lpDiEffect", "LPCDIEFFECT" ],
		[ "szFriendlyName[260]", "CHAR" ],
		[ "_(4)", "" ],
	];

	CreateWindowsTuple
	(
		"DIFILEEFFECT",
		items,
		0,
		TypeFlags_NoP
	);
}


// DIEFFESCAPE
{
	let items =
	[
		[ "dwSize", "DWORD" ],
		[ "dwCommand", "DWORD" ],
		[ "lpvInBuffer", "LPVOID" ],
		[ "cbInBuffer", "DWORD" ],
		[ "_(4)", "" ],
		[ "lpvOutBuffer", "LPVOID" ],
		[ "cbOutBuffer", "DWORD" ],
		[ "_(4)", "" ],
	];

	CreateWindowsTuple
	(
		"DIEFFESCAPE",
		items,
		0,
		TypeFlags_NoP |
		TypeFlags_NoLPC
	);
}


// DIEFFECTINFOA
{
	let items =
	[
		[ "dwSize", "DWORD" ],
		[ "guid", "GUID" ],
		[ "dwEffType", "DWORD" ],
		[ "dwStaticParams", "DWORD" ],
		[ "dwDynamicParams", "DWORD" ],
		[ "tszName[260]", "CHAR" ],
	];

	CreateWindowsTuple
	(
		"DIEFFECTINFOA",
		items,
		0,
		TypeFlags_NoP
	);
}

// DIEFFECTINFOW
{
	let items =
	[
		[ "dwSize", "DWORD" ],
		[ "guid", "GUID" ],
		[ "dwEffType", "DWORD" ],
		[ "dwStaticParams", "DWORD" ],
		[ "dwDynamicParams", "DWORD" ],
		[ "tszName[260]", "WCHAR" ],
	];

	CreateWindowsTuple
	(
		"DIEFFECTINFOW",
		items,
		0,
		TypeFlags_NoP
	);
}


// DIACTIONA
{
	let items =
	[
		[ "uAppData", "UINT_PTR" ],
		[ "dwSemantic", "DWORD" ],
		[ "dwFlags", "DWORD" ],
		[ "", "union",
			[
				[ "lptszActionName", "LPCSTR" ],
				[ "uResIdString", "UINT" ],
			],
		],
		[ "guidInstance", "GUID" ],
		[ "dwObjID", "DWORD" ],
		[ "dwHow", "DWORD" ],
	];

	CreateWindowsTuple
	(
		"DIACTIONA",
		items,
		0,
		TypeFlags_NoP
	);
}

// DIACTIONW
{
	let items =
	[
		[ "uAppData", "UINT_PTR" ],
		[ "dwSemantic", "DWORD" ],
		[ "dwFlags", "DWORD" ],
		[ "", "union",
			[
				[ "lptszActionName", "LPCWSTR" ],
				[ "uResIdString", "UINT" ],
			],
		],
		[ "guidInstance", "GUID" ],
		[ "dwObjID", "DWORD" ],
		[ "dwHow", "DWORD" ],
	];

	CreateWindowsTuple
	(
		"DIACTIONW",
		items,
		0,
		TypeFlags_NoP
	);
}

// DIACTIONFORMATA
{
	let items =
	[
		[ "dwSize", "DWORD" ],
		[ "dwActionSize", "DWORD" ],
		[ "dwDataSize", "DWORD" ],
		[ "dwNumActions", "DWORD" ],
		[ "rgoAction", "LPDIACTIONA" ],
		[ "guidActionMap", "GUID" ],
		[ "dwGenre", "DWORD" ],
		[ "dwBufferSize", "DWORD" ],
		[ "lAxisMin", "LONG" ],
		[ "lAxisMax", "LONG" ],
		[ "hInstString", "HINSTANCE" ],
		[ "ftTimeStamp", "FILETIME" ],
		[ "dwCRC", "DWORD" ],
		[ "tszActionMap[260]", "CHAR" ],
	];

	CreateWindowsTuple
	(
		"DIACTIONFORMATA",
		items,
		0,
		TypeFlags_NoP
	);
}


// DIACTIONFORMATW
{
	let items =
	[
		[ "dwSize", "DWORD" ],
		[ "dwActionSize", "DWORD" ],
		[ "dwDataSize", "DWORD" ],
		[ "dwNumActions", "DWORD" ],
		[ "rgoAction", "LPDIACTIONW" ],
		[ "guidActionMap", "GUID" ],
		[ "dwGenre", "DWORD" ],
		[ "dwBufferSize", "DWORD" ],
		[ "lAxisMin", "LONG" ],
		[ "lAxisMax", "LONG" ],
		[ "hInstString", "HINSTANCE" ],
		[ "ftTimeStamp", "FILETIME" ],
		[ "dwCRC", "DWORD" ],
		[ "tszActionMap[260]", "WCHAR" ],
		[ "_(4)", "" ],
	];

	CreateWindowsTuple
	(
		"DIACTIONFORMATW",
		items,
		0,
		TypeFlags_NoP
	);
}



// DIDEVICEIMAGEINFOA
{
	let items =
	[
		[ "tszImagePath[260]", "CHAR" ],
		[ "dwFlags", "DWORD" ],
		[ "dwViewID", "DWORD" ],
		[ "rcOverlay", "RECT" ],
		[ "dwObjID", "DWORD" ],
		[ "dwcValidPts", "DWORD" ],
		[ "rgptCalloutLine[5]", "POINT" ],
		[ "rcCalloutRect", "RECT" ],
		[ "dwTextAlign", "DWORD" ],
	];

	CreateWindowsTuple
	(
		"DIDEVICEIMAGEINFOA",
		items,
		0,
		TypeFlags_NoP
	);
}

// DIDEVICEIMAGEINFOW
{
	let items =
	[
		[ "tszImagePath[260]", "WCHAR" ],
		[ "dwFlags", "DWORD" ],
		[ "dwViewID", "DWORD" ],
		[ "rcOverlay", "RECT" ],
		[ "dwObjID", "DWORD" ],
		[ "dwcValidPts", "DWORD" ],
		[ "rgptCalloutLine[5]", "POINT" ],
		[ "rcCalloutRect", "RECT" ],
		[ "dwTextAlign", "DWORD" ],
	];

	CreateWindowsTuple
	(
		"DIDEVICEIMAGEINFOW",
		items,
		0,
		TypeFlags_NoP
	);
}






// DIDEVICEIMAGEINFOHEADERA
{
	let items =
	[
		[ "dwSize", "DWORD" ],
		[ "dwSizeImageInfo", "DWORD" ],
		[ "dwcViews", "DWORD" ],
		[ "dwcButtons", "DWORD" ],
		[ "dwcAxes", "DWORD" ],
		[ "dwcPOVs", "DWORD" ],
		[ "dwBufferSize", "DWORD" ],
		[ "dwBufferUsed", "DWORD" ],
		[ "lprgImageInfoArray", "LPDIDEVICEIMAGEINFOA" ],
	];

	CreateWindowsTuple
	(
		"DIDEVICEIMAGEINFOHEADERA",
		items,
		0,
		TypeFlags_NoP
	);
}


// DIDEVICEIMAGEINFOHEADERW
{
	let items =
	[
		[ "dwSize", "DWORD" ],
		[ "dwSizeImageInfo", "DWORD" ],
		[ "dwcViews", "DWORD" ],
		[ "dwcButtons", "DWORD" ],
		[ "dwcAxes", "DWORD" ],
		[ "dwcPOVs", "DWORD" ],
		[ "dwBufferSize", "DWORD" ],
		[ "dwBufferUsed", "DWORD" ],
		[ "lprgImageInfoArray", "LPDIDEVICEIMAGEINFOW" ],
	];

	CreateWindowsTuple
	(
		"DIDEVICEIMAGEINFOHEADERW",
		items,
		0,
		TypeFlags_NoP
	);
}



// DICOLORSET
{
	let items =
	[
		[ "dwSize", "DWORD" ],
		[ "cTextFore", "D3DCOLOR" ],
		[ "cTextHighlight", "D3DCOLOR" ],
		[ "cCalloutLine", "D3DCOLOR" ],
		[ "cCalloutHighlight", "D3DCOLOR" ],
		[ "cBorder", "D3DCOLOR" ],
		[ "cControlFill", "D3DCOLOR" ],
		[ "cHighlightFill", "D3DCOLOR" ],
		[ "cAreaFill", "D3DCOLOR" ],
	];

	CreateWindowsTuple
	(
		"DICOLORSET",
		items,
		0,
		TypeFlags_NoP
	);
}









// DICONFIGUREDEVICESPARAMSA
{
	let items =
	[
		[ "dwSize", "DWORD" ],
		[ "dwcUsers", "DWORD" ],
		[ "lptszUserNames", "LPSTR" ],
		[ "dwcFormats", "DWORD" ],
		[ "_(4)", "" ],
		[ "lprgFormats", "LPDIACTIONFORMATA" ],
		[ "hwnd", "HWND" ],
		[ "dics", "DICOLORSET" ],
		[ "_(4)", "" ],
		[ "lpUnkDDSTarget", "IUnknown*" ],
	];

	CreateWindowsTuple
	(
		"DICONFIGUREDEVICESPARAMSA",
		items,
		0,
		TypeFlags_NoP
	);
}


// DICONFIGUREDEVICESPARAMSW
{
	let items =
	[
		[ "dwSize", "DWORD" ],
		[ "dwcUsers", "DWORD" ],
		[ "lptszUserNames", "LPWSTR" ],
		[ "dwcFormats", "DWORD" ],
		[ "_(4)", "" ],
		[ "lprgFormats", "LPDIACTIONFORMATW" ],
		[ "hwnd", "HWND" ],
		[ "dics", "DICOLORSET" ],
		[ "_(4)", "" ],
		[ "lpUnkDDSTarget", "IUnknown*" ],
	];

	CreateWindowsTuple
	(
		"DICONFIGUREDEVICESPARAMSW",
		items,
		0,
		TypeFlags_NoP
	);
}


/*



*/































c += Tabs() + "#pragma pack(pop)" + NEW_LINE;
c += NEW_LINE;




// Function Types
{
	let items =
	[
		[ "LPDIENUMDEVICESCALLBACKA", "BOOL",
			[
				[ "", "LPCDIDEVICEINSTANCEA" ],
				[ "", "LPVOID" ],
			],
		],
		[ "LPDIENUMDEVICESCALLBACKW", "BOOL",
			[
				[ "", "LPCDIDEVICEINSTANCEW" ],
				[ "", "LPVOID" ],
			],
		],
		[ "LPDICONFIGUREDEVICESCALLBACK", "BOOL",
			[
				[ "", "IUnknown*" ],
				[ "", "LPVOID" ],
			],
		],
		[ "LPDIENUMDEVICESBYSEMANTICSCBA", "BOOL",
			[
				[ "", "LPCDIDEVICEINSTANCEA" ],
				[ "", "LPDIRECTINPUTDEVICE8A" ],
				[ "", "DWORD" ],
				[ "", "DWORD" ],
				[ "", "LPVOID" ],
			],
		],
		[ "LPDIENUMDEVICESBYSEMANTICSCBW", "BOOL",
			[
				[ "", "LPCDIDEVICEINSTANCEW" ],
				[ "", "LPDIRECTINPUTDEVICE8W" ],
				[ "", "DWORD" ],
				[ "", "DWORD" ],
				[ "", "LPVOID" ],
			],
		],
		[ "LPDIENUMDEVICEOBJECTSCALLBACKA", "BOOL",
			[
				[ "", "LPCDIDEVICEOBJECTINSTANCEA" ],
				[ "", "LPVOID" ],
			],
		],
		[ "LPDIENUMDEVICEOBJECTSCALLBACKW", "BOOL",
			[
				[ "", "LPCDIDEVICEOBJECTINSTANCEW" ],
				[ "", "LPVOID" ],
			],
		],
		[ "LPDIENUMEFFECTSCALLBACKA", "BOOL",
			[
				[ "", "LPCDIEFFECTINFOA" ],
				[ "", "LPVOID" ],
			],
		],
		[ "LPDIENUMEFFECTSCALLBACKW", "BOOL",
			[
				[ "", "LPCDIEFFECTINFOW" ],
				[ "", "LPVOID" ],
			],
		],
		[ "LPDIENUMCREATEDEFFECTOBJECTSCALLBACK", "BOOL",
			[
				[ "", "LPDIRECTINPUTEFFECT" ],
				[ "", "LPVOID" ],
			],
		],
		[ "LPDIENUMEFFECTSINFILECALLBACK", "BOOL",
			[
				[ "", "LPCDIFILEEFFECT" ],
				[ "", "LPVOID" ],
			],
		],
	];

	CreateWindowsFunctionTypedefs(items);
}


































c += NEW_LINE;

// Function Tuples

// IDirectInput8A
{
	let items =
	[
		[ "CreateDevice", "HRESULT",
			[
				[ "", "const GUID&" ],
				[ "", "LPDIRECTINPUTDEVICE8A*" ],
				[ "", "LPUNKNOWN" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "EnumDevices", "HRESULT",
			[
				[ "", "DWORD" ],
				[ "", "LPDIENUMDEVICESCALLBACKA" ],
				[ "", "LPVOID" ],
				[ "", "DWORD" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetDeviceStatus", "HRESULT",
			[
				[ "", "const GUID&" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "RunControlPanel", "HRESULT",
			[
				[ "", "HWND" ],
				[ "", "DWORD" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "Initialize", "HRESULT",
			[
				[ "", "HINSTANCE" ],
				[ "", "DWORD" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "FindDevice", "HRESULT",
			[
				[ "", "const GUID&" ],
				[ "", "LPCSTR" ],
				[ "", "LPGUID" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "EnumDevicesBySemantics", "HRESULT",
			[
				[ "", "LPCSTR" ],
				[ "", "LPDIACTIONFORMATA" ],
				[ "", "LPDIENUMDEVICESBYSEMANTICSCBA" ],
				[ "", "LPVOID" ],
				[ "", "DWORD" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "ConfigureDevices", "HRESULT",
			[
				[ "", "LPDICONFIGUREDEVICESCALLBACK" ],
				[ "", "LPDICONFIGUREDEVICESPARAMSA" ],
				[ "", "DWORD" ],
				[ "", "LPVOID" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"IDirectInput8A : IUnknown",
		items,
		[ "novtable" ]
	);
}




// IDirectInput8W
{
	let items =
	[
		[ "CreateDevice", "HRESULT",
			[
				[ "", "const GUID&" ],
				[ "", "LPDIRECTINPUTDEVICE8W*" ],
				[ "", "LPUNKNOWN" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "EnumDevices", "HRESULT",
			[
				[ "", "DWORD" ],
				[ "", "LPDIENUMDEVICESCALLBACKW" ],
				[ "", "LPVOID" ],
				[ "", "DWORD" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetDeviceStatus", "HRESULT",
			[
				[ "", "const GUID&" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "RunControlPanel", "HRESULT",
			[
				[ "", "HWND" ],
				[ "", "DWORD" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "Initialize", "HRESULT",
			[
				[ "", "HINSTANCE" ],
				[ "", "DWORD" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "FindDevice", "HRESULT",
			[
				[ "", "const GUID&" ],
				[ "", "LPCWSTR" ],
				[ "", "LPGUID" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "EnumDevicesBySemantics", "HRESULT",
			[
				[ "", "LPCWSTR" ],
				[ "", "LPDIACTIONFORMATW" ],
				[ "", "LPDIENUMDEVICESBYSEMANTICSCBW" ],
				[ "", "LPVOID" ],
				[ "", "DWORD" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "ConfigureDevices", "HRESULT",
			[
				[ "", "LPDICONFIGUREDEVICESCALLBACK" ],
				[ "", "LPDICONFIGUREDEVICESPARAMSW" ],
				[ "", "DWORD" ],
				[ "", "LPVOID" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"IDirectInput8W : IUnknown",
		items,
		[ "novtable" ]
	);
}












// IDirectInputDevice8A
{
	let items =
	[
		[ "GetCapabilities", "HRESULT",
			[
				[ "", "LPDIDEVCAPS" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "EnumObjects", "HRESULT",
			[
				[ "", "LPDIENUMDEVICEOBJECTSCALLBACKA" ],
				[ "", "LPVOID" ],
				[ "", "DWORD" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetProperty", "HRESULT",
			[
				[ "", "const GUID&" ],
				[ "", "LPDIPROPHEADER" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "SetProperty", "HRESULT",
			[
				[ "", "const GUID&" ],
				[ "", "LPCDIPROPHEADER" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "Acquire", "HRESULT",
			[
			],
			FunctionFlags_PureVirtual
		],
		[ "Unacquire", "HRESULT",
			[
			],
			FunctionFlags_PureVirtual
		],
		[ "GetDeviceState", "HRESULT",
			[
				[ "", "DWORD" ],
				[ "", "LPVOID" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetDeviceData", "HRESULT",
			[
				[ "", "DWORD" ],
				[ "", "LPDIDEVICEOBJECTDATA" ],
				[ "", "LPDWORD" ],
				[ "", "DWORD" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "SetDataFormat", "HRESULT",
			[
				[ "", "LPCDIDATAFORMAT" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "SetEventNotification", "HRESULT",
			[
				[ "", "HANDLE" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "SetCooperativeLevel", "HRESULT",
			[
				[ "", "HWND" ],
				[ "", "DWORD" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetObjectInfo", "HRESULT",
			[
				[ "", "LPDIDEVICEOBJECTINSTANCEA" ],
				[ "", "DWORD" ],
				[ "", "DWORD" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetDeviceInfo", "HRESULT",
			[
				[ "", "LPDIDEVICEINSTANCEA" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "RunControlPanel", "HRESULT",
			[
				[ "", "HWND" ],
				[ "", "DWORD" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "Initialize", "HRESULT",
			[
				[ "", "HINSTANCE" ],
				[ "", "DWORD" ],
				[ "", "const GUID&" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CreateEffect", "HRESULT",
			[
				[ "", "const GUID&" ],
				[ "", "LPCDIEFFECT" ],
				[ "", "LPDIRECTINPUTEFFECT*" ],
				[ "", "LPUNKNOWN" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "EnumEffects", "HRESULT",
			[
				[ "", "LPDIENUMEFFECTSCALLBACKA" ],
				[ "", "LPVOID" ],
				[ "", "DWORD" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetEffectInfo", "HRESULT",
			[
				[ "", "LPDIEFFECTINFOA" ],
				[ "", "const GUID&" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetForceFeedbackState", "HRESULT",
			[
				[ "", "LPDWORD" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "SendForceFeedbackCommand", "HRESULT",
			[
				[ "", "DWORD" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "EnumCreatedEffectObjects", "HRESULT",
			[
				[ "", "LPDIENUMCREATEDEFFECTOBJECTSCALLBACK" ],
				[ "", "LPVOID" ],
				[ "", "DWORD" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "Escape", "HRESULT",
			[
				[ "", "LPDIEFFESCAPE" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "Poll", "HRESULT",
			[
			],
			FunctionFlags_PureVirtual
		],
		[ "SendDeviceData", "HRESULT",
			[
				[ "", "DWORD" ],
				[ "", "LPCDIDEVICEOBJECTDATA" ],
				[ "", "LPDWORD" ],
				[ "", "DWORD" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "EnumEffectsInFile", "HRESULT",
			[
				[ "", "LPCSTR" ],
				[ "", "LPDIENUMEFFECTSINFILECALLBACK" ],
				[ "", "LPVOID" ],
				[ "", "DWORD" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "WriteEffectToFile", "HRESULT",
			[
				[ "", "LPCSTR" ],
				[ "", "DWORD" ],
				[ "", "LPDIFILEEFFECT" ],
				[ "", "DWORD" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "BuildActionMap", "HRESULT",
			[
				[ "", "LPDIACTIONFORMATA" ],
				[ "", "LPCSTR" ],
				[ "", "DWORD" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "SetActionMap", "HRESULT",
			[
				[ "", "LPDIACTIONFORMATA" ],
				[ "", "LPCSTR" ],
				[ "", "DWORD" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetImageInfo", "HRESULT",
			[
				[ "", "LPDIDEVICEIMAGEINFOHEADERA" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"IDirectInputDevice8A : IUnknown",
		items,
		[ "novtable" ]
	);
}









// IDirectInputDevice8W
{
	let items =
	[
		[ "GetCapabilities", "HRESULT",
			[
				[ "", "LPDIDEVCAPS" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "EnumObjects", "HRESULT",
			[
				[ "", "LPDIENUMDEVICEOBJECTSCALLBACKW" ],
				[ "", "LPVOID" ],
				[ "", "DWORD" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetProperty", "HRESULT",
			[
				[ "", "const GUID&" ],
				[ "", "LPDIPROPHEADER" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "SetProperty", "HRESULT",
			[
				[ "", "const GUID&" ],
				[ "", "LPCDIPROPHEADER" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "Acquire", "HRESULT",
			[
			],
			FunctionFlags_PureVirtual
		],
		[ "Unacquire", "HRESULT",
			[
			],
			FunctionFlags_PureVirtual
		],
		[ "GetDeviceState", "HRESULT",
			[
				[ "", "DWORD" ],
				[ "", "LPVOID" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetDeviceData", "HRESULT",
			[
				[ "", "DWORD" ],
				[ "", "LPDIDEVICEOBJECTDATA" ],
				[ "", "LPDWORD" ],
				[ "", "DWORD" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "SetDataFormat", "HRESULT",
			[
				[ "", "LPCDIDATAFORMAT" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "SetEventNotification", "HRESULT",
			[
				[ "", "HANDLE" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "SetCooperativeLevel", "HRESULT",
			[
				[ "", "HWND" ],
				[ "", "DWORD" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetObjectInfo", "HRESULT",
			[
				[ "", "LPDIDEVICEOBJECTINSTANCEW" ],
				[ "", "DWORD" ],
				[ "", "DWORD" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetDeviceInfo", "HRESULT",
			[
				[ "", "LPDIDEVICEINSTANCEW" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "RunControlPanel", "HRESULT",
			[
				[ "", "HWND" ],
				[ "", "DWORD" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "Initialize", "HRESULT",
			[
				[ "", "HINSTANCE" ],
				[ "", "DWORD" ],
				[ "", "const GUID&" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "CreateEffect", "HRESULT",
			[
				[ "", "const GUID&" ],
				[ "", "LPCDIEFFECT" ],
				[ "", "LPDIRECTINPUTEFFECT*" ],
				[ "", "LPUNKNOWN" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "EnumEffects", "HRESULT",
			[
				[ "", "LPDIENUMEFFECTSCALLBACKW" ],
				[ "", "LPVOID" ],
				[ "", "DWORD" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetEffectInfo", "HRESULT",
			[
				[ "", "LPDIEFFECTINFOW" ],
				[ "", "const GUID&" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetForceFeedbackState", "HRESULT",
			[
				[ "", "LPDWORD" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "SendForceFeedbackCommand", "HRESULT",
			[
				[ "", "DWORD" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "EnumCreatedEffectObjects", "HRESULT",
			[
				[ "", "LPDIENUMCREATEDEFFECTOBJECTSCALLBACK" ],
				[ "", "LPVOID" ],
				[ "", "DWORD" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "Escape", "HRESULT",
			[
				[ "", "LPDIEFFESCAPE" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "Poll", "HRESULT",
			[
			],
			FunctionFlags_PureVirtual
		],
		[ "SendDeviceData", "HRESULT",
			[
				[ "", "DWORD" ],
				[ "", "LPCDIDEVICEOBJECTDATA" ],
				[ "", "LPDWORD" ],
				[ "", "DWORD" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "EnumEffectsInFile", "HRESULT",
			[
				[ "", "LPCWSTR" ],
				[ "", "LPDIENUMEFFECTSINFILECALLBACK" ],
				[ "", "LPVOID" ],
				[ "", "DWORD" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "WriteEffectToFile", "HRESULT",
			[
				[ "", "LPCWSTR" ],
				[ "", "DWORD" ],
				[ "", "LPDIFILEEFFECT" ],
				[ "", "DWORD" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "BuildActionMap", "HRESULT",
			[
				[ "", "LPDIACTIONFORMATW" ],
				[ "", "LPCWSTR" ],
				[ "", "DWORD" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "SetActionMap", "HRESULT",
			[
				[ "", "LPDIACTIONFORMATW" ],
				[ "", "LPCWSTR" ],
				[ "", "DWORD" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetImageInfo", "HRESULT",
			[
				[ "", "LPDIDEVICEIMAGEINFOHEADERW" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"IDirectInputDevice8W : IUnknown",
		items,
		[ "novtable" ]
	);
}



















// IDirectInputEffect
{
	let items =
	[
		[ "Initialize", "HRESULT",
			[
				[ "", "HINSTANCE" ],
				[ "", "DWORD" ],
				[ "", "const GUID&" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetEffectGuid", "HRESULT",
			[
				[ "", "LPGUID" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "GetParameters", "HRESULT",
			[
				[ "", "LPDIEFFECT" ],
				[ "", "DWORD" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "SetParameters", "HRESULT",
			[
				[ "", "LPCDIEFFECT" ],
				[ "", "DWORD" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "Start", "HRESULT",
			[
				[ "", "DWORD" ],
				[ "", "DWORD" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "Stop", "HRESULT",
			[
			],
			FunctionFlags_PureVirtual
		],
		[ "GetEffectStatus", "HRESULT",
			[
				[ "", "LPDWORD" ],
			],
			FunctionFlags_PureVirtual
		],
		[ "Download", "HRESULT",
			[
			],
			FunctionFlags_PureVirtual
		],
		[ "Unload", "HRESULT",
			[
			],
			FunctionFlags_PureVirtual
		],
		[ "Escape", "HRESULT",
			[
				[ "", "LPDIEFFESCAPE" ],
			],
			FunctionFlags_PureVirtual
		],
	];

	CreateWindowsFunctionTuple
	(
		"IDirectInputEffect : IUnknown",
		items,
		[ "novtable" ]
	);
}





// Functions
{
	let items =
	[
		[ "DirectInput8Create", "HRESULT",
			[
				[ "hinst", "HINSTANCE" ],
				[ "dwVersion", "DWORD" ],
				[ "riidltf", "const IID&" ],
				[ "ppvOut", "LPVOID*" ],
				[ "punkOuter", "LPUNKNOWN" ],
			],
			FunctionFlags_ExternC
		],
	];

	CreateFunctions(items);
}













c += NEW_LINE;

ModuleEnd();

CleanStream();

fs.writeFileSync("../Core/DI8.ixx", c);

// Verify

ModuleVerify();

CleanStream();

fs.writeFileSync("../verifyDI8.cpp", c);

ClearAll();
}

// #endregion

// #region XI
{
console.log("XI");

ModuleStart
(
	"XI",
	[
		"Windows"
	],
	[
		"Windows"
	]
);

// Types
{
	let items =
	[
	];

	CreateWindowsTypedefs(items);
}

// Function Types
{
	let items =
	[
	];

	CreateWindowsFunctionTypedefs(items);
}

// Enums
{
	let items =
	[
	];

	CreateWindowsEnum
	(
		"",
		items
	);
}

// Structs

c += Tabs() + "#pragma pack(push, 1)" + NEW_LINE;
c += NEW_LINE;



// XINPUT_GAMEPAD
{
	let items =
	[
		[ "wButtons", "WORD" ],
		[ "bLeftTrigger", "BYTE" ],
		[ "bRightTrigger", "BYTE" ],
		[ "sThumbLX", "SHORT" ],
		[ "sThumbLY", "SHORT" ],
		[ "sThumbRX", "SHORT" ],
		[ "sThumbRY", "SHORT" ],
	];

	CreateWindowsTuple
	(
		"XINPUT_GAMEPAD",
		items,
		0,
		TypeFlags_NoLP |
		TypeFlags_NoLPC
	);
}

// XINPUT_STATE
{
	let items =
	[
		[ "dwPacketNumber", "DWORD" ],
		[ "Gamepad", "XINPUT_GAMEPAD" ],
	];

	CreateWindowsTuple
	(
		"XINPUT_STATE",
		items,
		0,
		TypeFlags_NoLP |
		TypeFlags_NoLPC
	);
}



// XINPUT_VIBRATION
{
	let items =
	[
		[ "wLeftMotorSpeed", "WORD" ],
		[ "wRightMotorSpeed", "WORD" ],
	];

	CreateWindowsTuple
	(
		"XINPUT_VIBRATION",
		items,
		0,
		TypeFlags_NoLP |
		TypeFlags_NoLPC
	);
}


// XINPUT_CAPABILITIES
{
	let items =
	[
		[ "Type", "BYTE" ],
		[ "SubType", "BYTE" ],
		[ "Flags", "WORD" ],
		[ "Gamepad", "XINPUT_GAMEPAD" ],
		[ "Vibration", "XINPUT_VIBRATION" ],
	];

	CreateWindowsTuple
	(
		"XINPUT_CAPABILITIES",
		items,
		0,
		TypeFlags_NoLP |
		TypeFlags_NoLPC
	);
}


// XINPUT_BATTERY_INFORMATION
{
	let items =
	[
		[ "BatteryType", "BYTE" ],
		[ "BatteryLevel", "BYTE" ],
	];

	CreateWindowsTuple
	(
		"XINPUT_BATTERY_INFORMATION",
		items,
		0,
		TypeFlags_NoLP |
		TypeFlags_NoLPC
	);
}



// XINPUT_KEYSTROKE
{
	let items =
	[
		[ "VirtualKey", "WORD" ],
		[ "Unicode", "WCHAR" ],
		[ "Flags", "WORD" ],
		[ "UserIndex", "BYTE" ],
		[ "HidCode", "BYTE" ],
	];

	CreateWindowsTuple
	(
		"XINPUT_KEYSTROKE",
		items,
		0,
		TypeFlags_NoLP |
		TypeFlags_NoLPC
	);
}



/*







*/










c += Tabs() + "#pragma pack(pop)" + NEW_LINE;
c += NEW_LINE;

// Functions
{
	let items =
	[
		[ "XInputGetState", "DWORD",
			[
				[ "dwUserIndex", "DWORD" ],
				[ "pState", "XINPUT_STATE*" ],
			],
		],
		[ "XInputSetState", "DWORD",
			[
				[ "dwUserIndex", "DWORD" ],
				[ "pVibration", "XINPUT_VIBRATION*" ],
			],
		],
		[ "XInputGetCapabilities", "DWORD",
			[
				[ "dwUserIndex", "DWORD" ],
				[ "dwFlags", "DWORD" ],
				[ "pCapabilities", "XINPUT_CAPABILITIES*" ],
			],
		],
		[ "XInputEnable", "void",
			[
				[ "enable", "BOOL" ],
			],
		],
		[ "XInputGetAudioDeviceIds", "DWORD",
			[
				[ "dwUserIndex", "DWORD" ],
				[ "pRenderDeviceId", "LPWSTR" ],
				[ "pRenderCount", "UINT*" ],
				[ "pCaptureDeviceId", "LPWSTR" ],
				[ "pCaptureCount", "UINT*" ],
			],
		],
		[ "XInputGetBatteryInformation", "DWORD",
			[
				[ "dwUserIndex", "DWORD" ],
				[ "devType", "BYTE" ],
				[ "pBatteryInformation", "XINPUT_BATTERY_INFORMATION*" ],
			],
		],
		[ "XInputGetKeystroke", "DWORD",
			[
				[ "dwUserIndex", "DWORD" ],
				[ "dwReserved", "DWORD" ],
				[ "pKeystroke", "PXINPUT_KEYSTROKE" ],
			],
		],


	];

	CreateFunctions
	(
		items,
		"extern \"C\" "
	);
}

/*


*/



// Function Tuples

c += NEW_LINE;

ModuleEnd();

CleanStream();

fs.writeFileSync("../Core/XI.ixx", c);

// Verify

ModuleVerify();

CleanStream();

fs.writeFileSync("../verifyXI.cpp", c);

ClearAll();
}

// #endregion
