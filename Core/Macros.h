// @Todo: Update.

#ifdef offsetof
#undef offsetof
#endif
#ifndef __INTELLISENSE__
#define offsetof(s, m) __builtin_offsetof(s, m)
#else
#define offsetof(s, m) reinterpret_cast<uint32>(&(*reinterpret_cast<s *>(0)).m)
#endif

#define for_each(type, name, start, end, ...) for (type name = start; name < end; name++ __VA_OPT__(,) __VA_ARGS__)
#define for_all(type, name, end, ...) for_each(type, name, 0, end __VA_OPT__(,) __VA_ARGS__)

#define HoboBreak() MessageBoxA(0, "break1", 0, 0); MessageBoxA(0, "break2", 0, 0)

#define FUNC_NAME __FUNCTION__

#define LogFunction(...) LogFunctionHelper(FUNC_NAME __VA_OPT__(,) __VA_ARGS__)

#define PrintFunction(...) PrintFunctionHelper(FUNC_NAME __VA_OPT__(,) __VA_ARGS__)

// #define LogFunctionStart() Log("%s Start", FUNC_NAME)
// #define LogFunctionEnd() Log("%s End", FUNC_NAME)

#define _Prep_Merge(a, b) a##b
#define Prep_Merge(a, b) _Prep_Merge(a, b)

#define mov_rcx_rax 0x48, 0x8B, 0xC8 // mov rcx,rax
#define mov_rcx_rcx 0x48, 0x8B, 0xC9 // mov rcx,rcx
#define mov_rcx_rdx 0x48, 0x8B, 0xCA // mov rcx,rdx
#define mov_rcx_rbx 0x48, 0x8B, 0xCB // mov rcx,rbx
#define mov_rcx_rsp 0x48, 0x8B, 0xCC // mov rcx,rsp
#define mov_rcx_rbp 0x48, 0x8B, 0xCD // mov rcx,rbp
#define mov_rcx_rsi 0x48, 0x8B, 0xCE // mov rcx,rsi
#define mov_rcx_rdi 0x48, 0x8B, 0xCF // mov rcx,rdi
#define mov_rcx_r8  0x49, 0x8B, 0xC8 // mov rcx,r8
#define mov_rcx_r9  0x49, 0x8B, 0xC9 // mov rcx,r9
#define mov_rcx_r10 0x49, 0x8B, 0xCA // mov rcx,r10
#define mov_rcx_r11 0x49, 0x8B, 0xCB // mov rcx,r11
#define mov_rcx_r12 0x49, 0x8B, 0xCC // mov rcx,r12
#define mov_rcx_r13 0x49, 0x8B, 0xCD // mov rcx,r13
#define mov_rcx_r14 0x49, 0x8B, 0xCE // mov rcx,r14
#define mov_rcx_r15 0x49, 0x8B, 0xCF // mov rcx,r15


// @Todo: Add ecx.

