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

#define mov_ecx_eax        0x8B, 0xC8 // mov ecx,eax
#define mov_ecx_ecx        0x8B, 0xC9 // mov ecx,ecx
#define mov_ecx_edx        0x8B, 0xCA // mov ecx,edx
#define mov_ecx_ebx        0x8B, 0xCB // mov ecx,ebx
#define mov_ecx_esp        0x8B, 0xCC // mov ecx,esp
#define mov_ecx_ebp        0x8B, 0xCD // mov ecx,ebp
#define mov_ecx_esi        0x8B, 0xCE // mov ecx,esi
#define mov_ecx_edi        0x8B, 0xCF // mov ecx,edi
#define mov_ecx_r8d  0x41, 0x8B, 0xC8 // mov ecx,r8d
#define mov_ecx_r9d  0x41, 0x8B, 0xC9 // mov ecx,r9d
#define mov_ecx_r10d 0x41, 0x8B, 0xCA // mov ecx,r10d
#define mov_ecx_r11d 0x41, 0x8B, 0xCB // mov ecx,r11d
#define mov_ecx_r12d 0x41, 0x8B, 0xCC // mov ecx,r12d
#define mov_ecx_r13d 0x41, 0x8B, 0xCD // mov ecx,r13d
#define mov_ecx_r14d 0x41, 0x8B, 0xCE // mov ecx,r14d
#define mov_ecx_r15d 0x41, 0x8B, 0xCF // mov ecx,r15d

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

#define mov_edx_eax        0x8B, 0xD0 // mov edx,eax
#define mov_edx_ecx        0x8B, 0xD1 // mov edx,ecx
#define mov_edx_edx        0x8B, 0xD2 // mov edx,edx
#define mov_edx_ebx        0x8B, 0xD3 // mov edx,ebx
#define mov_edx_esp        0x8B, 0xD4 // mov edx,esp
#define mov_edx_ebp        0x8B, 0xD5 // mov edx,ebp
#define mov_edx_esi        0x8B, 0xD6 // mov edx,esi
#define mov_edx_edi        0x8B, 0xD7 // mov edx,edi
#define mov_edx_r8d  0x41, 0x8B, 0xD0 // mov edx,r8d
#define mov_edx_r9d  0x41, 0x8B, 0xD1 // mov edx,r9d
#define mov_edx_r10d 0x41, 0x8B, 0xD2 // mov edx,r10d
#define mov_edx_r11d 0x41, 0x8B, 0xD3 // mov edx,r11d
#define mov_edx_r12d 0x41, 0x8B, 0xD4 // mov edx,r12d
#define mov_edx_r13d 0x41, 0x8B, 0xD5 // mov edx,r13d
#define mov_edx_r14d 0x41, 0x8B, 0xD6 // mov edx,r14d
#define mov_edx_r15d 0x41, 0x8B, 0xD7 // mov edx,r15d

#define mov_rdx_rax 0x48, 0x8B, 0xD0 // mov rdx,rax
#define mov_rdx_rcx 0x48, 0x8B, 0xD1 // mov rdx,rcx
#define mov_rdx_rdx 0x48, 0x8B, 0xD2 // mov rdx,rdx
#define mov_rdx_rbx 0x48, 0x8B, 0xD3 // mov rdx,rbx
#define mov_rdx_rsp 0x48, 0x8B, 0xD4 // mov rdx,rsp
#define mov_rdx_rbp 0x48, 0x8B, 0xD5 // mov rdx,rbp
#define mov_rdx_rsi 0x48, 0x8B, 0xD6 // mov rdx,rsi
#define mov_rdx_rdi 0x48, 0x8B, 0xD7 // mov rdx,rdi
#define mov_rdx_r8  0x49, 0x8B, 0xD0 // mov rdx,r8
#define mov_rdx_r9  0x49, 0x8B, 0xD1 // mov rdx,r9
#define mov_rdx_r10 0x49, 0x8B, 0xD2 // mov rdx,r10
#define mov_rdx_r11 0x49, 0x8B, 0xD3 // mov rdx,r11
#define mov_rdx_r12 0x49, 0x8B, 0xD4 // mov rdx,r12
#define mov_rdx_r13 0x49, 0x8B, 0xD5 // mov rdx,r13
#define mov_rdx_r14 0x49, 0x8B, 0xD6 // mov rdx,r14
#define mov_rdx_r15 0x49, 0x8B, 0xD7 // mov rdx,r15
