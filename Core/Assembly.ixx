#ifndef __MODULE_CORE_ASSEMBLY__
#define __MODULE_CORE_ASSEMBLY__

module;
#include "Includes.h"
export module ModuleName(Core_Assembly);

export constexpr byte8 mov_rcx_rax[] =
{
	0x48, 0x8B, 0xC8, // mov rcx,rax
};

export constexpr byte8 mov_rcx_rcx[] =
{
	0x48, 0x8B, 0xC9, // mov rcx,rcx
};

export constexpr byte8 mov_rcx_rdx[] =
{
	0x48, 0x8B, 0xCA, // mov rcx,rdx
};

export constexpr byte8 mov_rcx_rbx[] =
{
	0x48, 0x8B, 0xCB, // mov rcx,rbx
};

export constexpr byte8 mov_rcx_rsp[] =
{
	0x48, 0x8B, 0xCC, // mov rcx,rsp
};

export constexpr byte8 mov_rcx_rbp[] =
{
	0x48, 0x8B, 0xCD, // mov rcx,rbp
};

export constexpr byte8 mov_rcx_rsi[] =
{
	0x48, 0x8B, 0xCE, // mov rcx,rsi
};

export constexpr byte8 mov_rcx_rdi[] =
{
	0x48, 0x8B, 0xCF, // mov rcx,rdi
};

export constexpr byte8 mov_rcx_r8[] =
{
	0x49, 0x8B, 0xC8, // mov rcx,r8
};

export constexpr byte8 mov_rcx_r9[] =
{
	0x49, 0x8B, 0xC9, // mov rcx,r9
};

export constexpr byte8 mov_rcx_r10[] =
{
	0x49, 0x8B, 0xCA, // mov rcx,r10
};

export constexpr byte8 mov_rcx_r11[] =
{
	0x49, 0x8B, 0xCB, // mov rcx,r11
};

export constexpr byte8 mov_rcx_r12[] =
{
	0x49, 0x8B, 0xCC, // mov rcx,r12
};

export constexpr byte8 mov_rcx_r13[] =
{
	0x49, 0x8B, 0xCD, // mov rcx,r13
};

export constexpr byte8 mov_rcx_r14[] =
{
	0x49, 0x8B, 0xCE, // mov rcx,r14
};

export constexpr byte8 mov_rcx_r15[] =
{
	0x49, 0x8B, 0xCF, // mov rcx,r15
};

#endif
